#include"dataDeal.h"

////////////////////////////////////////////////////////////////////////////////////////////////
/*检索模块*/

/*
 *按id号查找书籍
 *使用getBookInfo()函数来获得一个含有所查书籍信息的BOOKS结点指针  
 */


/*按bookname模糊查找*/
BOOKS *searchbook_name(char *databaseName,char *bookname){  //传入数据库名和需检索的书名 
	BOOKS *result_head,*result_tail,*p,*ptr,*bookhead;
	bookhead=getAllBooksInfo(databaseName);    //获取所查询数据库的书籍信息头结点
	ptr=bookhead;
	result_head=result_tail=NULL;
	int i;
	bool flag;
	/*精确查找优先*/
	i=0;
	while(ptr!=NULL){
		if(strcmp(bookname,ptr->bookname)==0){  //找到符合要求的结点时复制并连接到新结果链表上 
			p=copybooknode(ptr);
			p->next=NULL;
			if(result_head==NULL){
				result_head=p;
			}
			else{
				result_tail->next=p;
			}
			result_tail=p;
		}
		i++;         //记录结点个数  
		ptr=ptr->next;
	} 
	/*
	 *记录是否在本次调用中被检索到过 
	 *opr[i]为1时说明检索到过
	 *每个opr[i]对应一个BOOKS结点 
	 */
	int *opr;
	opr=(int*)calloc(i,sizeof(int));       //分配与当前结点个数对应的内存 
	ptr=bookhead;
	i=0;
	while(ptr!=NULL){
		if(strcmp(bookname,ptr->bookname)==0){  //找到符合精确查找要求的结点时标记为检索到过 
			opr[i]=1; 
		}
		i++;
		ptr=ptr->next;
	}
	/*空格分割关键词查找*/
	char *keyword;
	int start,end;               //记录一个单词第一个和最后一个字母的位置 
	int j=0,k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //用于表示是否满足条件 
		while(bookname[i]!='\0'){
			if(bookname[i]>='A'&&bookname[i]<='Z'||bookname[i]>='a'&&bookname[i]<='z'){
				if(bookname[i+1]>='A'&&bookname[i+1]||bookname[i+1]>='a'&&bookname[i+1]<='z')i++;
				else{               //如果下一个字符不是字母说明一个单词结束
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //复制从start到end的关键词到keyword指向的字符串 
						keyword[j]=bookname[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->bookname);      //比对关键词和书名 
					free(keyword);                                 //每个关键词比对完以后将分配的内存释放 
					i++;
				}
				if(flag)break;                                     //一旦有一个结点满足条件就认为找到了 
			}
			else{
				if(bookname[i+1]>='A'&&bookname[i+1]||bookname[i+1]>='a'&&bookname[i+1]<='z'){
					start=i+1;      //当前不是字母但下一个是则记下一个位置为start 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //满足条件且在之前的查找中未找到过时，添加此结点 
			opr[k]=1;
			p=copybooknode(ptr);    //复制一个新结点 
			p->next=NULL;
			if(result_head==NULL){
				result_head=p;
			}
			else{
				result_tail->next=p;
			}
			result_tail=p;
		}
		k++;
		ptr=ptr->next;
	} 
	/*连续模糊查找*/
	ptr=bookhead;
	i=0;
	while(ptr!=NULL){
		flag=(strstr(ptr->bookname,bookname)!=NULL);  //判断该结点的BOOK的书名是否含有所输关键词 若有则flag=TRUE 
		if(flag&&opr[i]==0){        //满足条件且在之前的查找中未找到过时添加此结点 
			opr[i]=1;
			p=copybooknode(ptr);    //复制ptr指向的结点 
			p->next=NULL;
			if(result_head==NULL){
				result_head=p;
			}
			else{
				result_tail->next=p;
			}
			result_tail=p;
		}
		i++;
		ptr=ptr->next;
	}
	free(opr);                         //一次完整的检索结束，立即释放opr的内存 
	return result_head;
}

/*按作者的模糊查找*/
BOOKS *searchbook_authors(char *databaseName,char *authors){  //传入数据库名和需检索的作者名 
	BOOKS *result_head,*result_tail,*p,*ptr,*bookhead;
	bookhead=getAllBooksInfo(databaseName);    //获取所查询数据库的书籍信息头结点 
	ptr=bookhead;
	result_head=result_tail=NULL;
	int i=0;
	bool flag;
	/*精确查找优先*/
	while(ptr!=NULL){
		if(strcmp(authors,ptr->authors)==0){  //找到符合要求的结点时复制并连接到结果链表上 
			p=copybooknode(ptr); 
			p->next=NULL;
			if(result_head==NULL){
				result_head=p;
			}
			else{
				result_tail->next=p;
			}
			result_tail=p;
		}
		i++;
		ptr=ptr->next;
	}
	/*
	 *记录是否在本次调用中被检索到过 
	 *opr[i]为1时说明检索到过
	 *每个opr[i]对应一个BOOKS结点 
	 */
	int *opr;
	opr=(int*)calloc(i,sizeof(int));       //分配与当前结点个数对应的内存 
	ptr=bookhead;
	i=0;
	while(ptr!=NULL){
		if(strcmp(authors,ptr->authors)==0){  //找到符合精确查找要求的结点时标记为检索到过 
			opr[i]=1; 
		}
		i++;
		ptr=ptr->next;
	}
	/*逐个作者查找*/
	char *keyword;
	int start,end;               //记录一个单词第一个和最后一个字母的位置 
	int j=0,k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //用于表示是否满足条件 
		while(authors[i]!='\0'){
			if(authors[i]>='A'&&authors[i]<='Z'||authors[i]>='a'&&authors[i]<='z'){
				if(authors[i+1]>='A'&&authors[i+1]||authors[i+1]>='a'&&authors[i+1]<='z')i++;
				else{               //如果下一个字符不是字母说明一个单词结束
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //复制从start到end的关键词到keyword指向的字符串 
						keyword[j]=authors[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->authors);      //比对关键词和作者 
					free(keyword);                                 //每个关键词比对完以后将分配的内存释放 
					i++;
				}
				if(flag)break;                                     //一旦有一个结点满足条件就认为找到了 
			}
			else{
				if(authors[i+1]>='A'&&authors[i+1]||authors[i+1]>='a'&&authors[i+1]<='z'){
					start=i+1;      //当前不是字母但下一个是则记下一个位置为start 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //满足条件且在之前的查找中未找到过时，添加此结点 
			opr[k]=1;
			p=copybooknode(ptr);    //复制一个新结点 
			p->next=NULL;
			if(result_head==NULL){
				result_head=p;
			}
			else{
				result_tail->next=p;
			}
			result_tail=p;
		}
		k++;
		ptr=ptr->next;
	} 
	/*空格分割关键词查找*/
	k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //用于表示是否满足条件 
		while(authors[i]!='\0'){
			if(authors[i]>='A'&&authors[i]<='Z'||authors[i]>='a'&&authors[i]<='z'){
				if(authors[i+1]>='A'&&authors[i+1]||authors[i+1]>='a'&&authors[i+1]<='z')i++;
				else{               //如果下一个字符不是字母说明一个单词结束
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //复制从start到end的关键词到keyword指向的字符串 
						keyword[j]=authors[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->authors);      //比对关键词和作者 
					free(keyword);                                 //每个关键词比对完以后将分配的内存释放 
					i++;
				}
				if(flag)break;                                     //一旦有一个结点满足条件就认为找到了 
			}
			else{
				if(authors[i+1]>='A'&&authors[i+1]||authors[i+1]>='a'&&authors[i+1]<='z'){
					start=i+1;      //当前不是字母但下一个是则记下一个位置为start 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //满足条件且在之前的查找中未找到过时，添加此结点 
			opr[k]=1;
			p=copybooknode(ptr);    //复制一个新结点 
			p->next=NULL;
			if(result_head==NULL){
				result_head=p;
			}
			else{
				result_tail->next=p;
			}
			result_tail=p;
		}
		k++;
		ptr=ptr->next;
	} 
	free(opr);                         //一次完整的检索结束，立即释放opr的内存 
	return result_head;
}

/*按关键词的模糊查找*/
BOOKS *searchbook_keywords(char *databaseName,char *keywords){  //传入数据库名和需检索的关键词 
	BOOKS *result_head,*result_tail,*p,*ptr,*bookhead;
	bookhead=getAllBooksInfo(databaseName);    //获取所查询数据库的书籍信息头结点
	ptr=bookhead;
	result_head=result_tail=NULL;
	int i=0;
	bool flag;
	/*精确查找优先*/
	while(ptr!=NULL){
		if(strcmp(keywords,ptr->keywords)==0){  //找到符合要求的结点时复制并连接到新结果链表上 
			p=copybooknode(ptr);
			p->next=NULL;
			if(result_head==NULL){
				result_head=p;
			}
			else{
				result_tail->next=p;
			}
			result_tail=p;
		}
		i++;
		ptr=ptr->next;
	}
	/*
	 *记录是否在本次调用中被检索到过 
	 *opr[i]为1时说明检索到过
	 *每个opr[i]对应一个BOOKS结点 
	 */
	int *opr;
	opr=(int*)calloc(i,sizeof(int));       //分配与当前结点个数对应的内存 
	ptr=bookhead;
	i=0;
	while(ptr!=NULL){
		if(strcmp(keywords,ptr->keywords)==0){  //找到符合精确查找要求的结点时标记为检索到过 
			opr[i]=1;
		}
		i++;
		ptr=ptr->next;
	}
	/*逐个关键词查找*/
	char *keyword;
	int start,end;               //记录一个单词第一个和最后一个字母的位置 
	int j=0,k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //用于表示是否满足条件 
		while(keywords[i]!='\0'){
			if(keywords[i]>='A'&&keywords[i]<='Z'||keywords[i]>='a'&&keywords[i]<='z'){
				if(keywords[i+1]>='A'&&keywords[i+1]||keywords[i+1]>='a'&&keywords[i+1]<='z')i++;
				else{               //如果下一个字符不是字母说明一个单词结束
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //复制从start到end的关键词到keyword指向的字符串 
						keyword[j]=keywords[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->keywords);      //比对关键词和输入的关键字 
					free(keyword);                                 //每个关键词比对完以后将分配的内存释放 
					i++;
				}
				if(flag)break;                                     //一旦有一个结点满足条件就认为找到了 
			}
			else{
				if(keywords[i+1]>='A'&&keywords[i+1]||keywords[i+1]>='a'&&keywords[i+1]<='z'){
					start=i+1;      //当前不是字母但下一个是则记下一个位置为start 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //满足条件且在之前的查找中未找到过时，添加此结点 
			opr[k]=1;
			p=copybooknode(ptr);    //复制一个新结点 
			p->next=NULL;
			if(result_head==NULL){
				result_head=p;
			}
			else{
				result_tail->next=p;
			}
			result_tail=p;
		}
		k++;
		ptr=ptr->next;
	} 
	/*空格分割关键词查找*/
	k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //用于表示是否满足条件 
		while(keywords[i]!='\0'){
			if(keywords[i]>='A'&&keywords[i]<='Z'||keywords[i]>='a'&&keywords[i]<='z'){
				if(keywords[i+1]>='A'&&keywords[i+1]||keywords[i+1]>='a'&&keywords[i+1]<='z')i++;
				else{               //如果下一个字符不是字母说明一个单词结束
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //复制从start到end的关键词到keyword指向的字符串 
						keyword[j]=keywords[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->keywords);      //比对关键词和输入的关键字 
					free(keyword);                                 //每个关键词比对完以后将分配的内存释放 
					i++;
				}
				if(flag)break;                                     //一旦有一个结点满足条件就认为找到了 
			}
			else{
				if(keywords[i+1]>='A'&&keywords[i+1]||keywords[i+1]>='a'&&keywords[i+1]<='z'){
					start=i+1;      //当前不是字母但下一个是则记下一个位置为start 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //满足条件且在之前的查找中未找到过时，添加此结点 
			opr[k]=1;
			p=copybooknode(ptr);    //复制一个新结点 
			p->next=NULL;
			if(result_head==NULL){
				result_head=p;
			}
			else{
				result_tail->next=p;
			}
			result_tail=p;
		}
		k++;
		ptr=ptr->next;
	} 
	free(opr);                         //一次完整的检索结束，立即释放opr的内存 
	return result_head;
}

/*查书籍借阅情况*/
BOOKSTATE *searchbookstate(char *databaseName,char *id){  //传入数据库名和用户输入的要检索的书籍id 
	BOOKSTATE *ptr,*result_state,*statehead;
	/*建立一个空的USERS结点，用于匹配AU_getAllBookRecords的函数接口*/
	USERS *admin;
	admin=(USERS*)calloc(1,sizeof(USERS));
	statehead=AU_getAllBookRecords(databaseName,admin);   //获取当前被借阅书籍的BOOKSTATE表头结点 
	result_state=NULL;
	ptr=statehead;
	while(ptr!=NULL){
		if(strcmp(ptr->bookid,id)==0){    //若id相同，复制一个BOOKSTATE结点 
			result_state=copystatenode(ptr); 
			break;
		}
		ptr=ptr->next;
	}
	return result_state;
} 

/*
 *查用户信息
 *使用AU_getUSERInfo()函数获取一个USERS指针
 */


/*
 *查用户借阅信息
 *使用AU_getBookRecordsByUser()函数获取一个BOOKSTATE表的头结点指针  
 */

////////////////////////////////////////////////////////////////////////////////////// 
/*统计模块*/

/*统计数据库中图书总量*/
int CountTotalBook(char *databaseName){
	BOOKS *bookhead,*ptr;
	int count=0;           //用于计数 
	bookhead=getAllBooksInfo(databaseName);
	ptr=bookhead;
	while(ptr!=NULL){
		count++;                //统计总量，每个BOOKS结点对应一本书 
		ptr=ptr->next;
	}
	return count;
} 

/*统计数据库中图书总借阅量*/
int CountTotalBorrowed(char *databaseName){
	BOOKSTATE *statehead,*ptr;
	/*建立一个空的USERS结点，用于匹配AU_getAllBookRecords的函数接口*/
	USERS *admin;
	admin=(USERS*)calloc(1,sizeof(USERS));
	int count=0;           //用于计数 
	statehead=AU_getAllBookRecords(databaseName,admin);
	ptr=statehead;
	while(ptr!=NULL){
		count++;                //统计总借阅量，每个BOOKSTATE结点对应一本书 
		ptr=ptr->next;
	}
	return count;
} 

/*统计不同类别图书的借阅情况*/
BOOKAMOUNT *BorrowedInfo(char *databaseName){
	BOOKAMOUNT *head,*tail,*p;    //用于新建链表
	head=tail=NULL;
	BOOKS *bookhead,*ptr;         //用于遍历BOOKS表 
	bookhead=getAllBooksInfo(databaseName);
	ptr=bookhead;
	int count=0;                    //用于记录某种类有多少藏书量 
	if(ptr!=NULL){
		p=(BOOKAMOUNT*)malloc(sizeof(BOOKAMOUNT));      //建立头结点 
		head=p;
		p->next=NULL; 
		p->category=(char*)calloc(strlen(ptr->category),sizeof(char));  //为新的结点中的category分配内存 
		strcpy(head->category,ptr->category);           //直接复制第一种类别 
		p->TotalBorrowed=0;                         //借阅量先初始化为0 
		ptr=ptr->next;
		count++; 
		tail=p; 
	}
	while(ptr!=NULL){
		if(strcmp(tail->category,ptr->category)==0){    //若当前遍历到的图书种类和前一个相同则继续找 
			count++;
			ptr=ptr->next;
		}
		else{                                           //若找到一个不同于前一种类的则新建一个结点并复制其类别 
			p=(BOOKAMOUNT*)malloc(sizeof(BOOKAMOUNT));
			p->category=(char*)calloc(strlen(ptr->category),sizeof(char));  //为新的结点中的category分配内存
			strcpy(p->category,ptr->category);          //复制新的类别 
			tail->TotalBooks=count;                     //将当前累积的同类书的数量赋值给前一个结点
			p->TotalBorrowed=0;                     //借阅量先初始化为0 
			p->next=NULL; 
			tail->next=p;
			tail=p;
			count=1;                                    //计数器计1 
			ptr=ptr->next;
		}
	}
	if(count!=0){                                       //若是在计数时遇到ptr=NULL而退出循环则需追加一次赋值 
		tail->TotalBooks=count;
	}
	/*计算每个种类的书的借阅量*/
	BOOKSTATE *statehead,*qtr;
	BOOKS *find;                                      //用于记录每个BOOKSTATE对应的BOOKS结点 
	/*建立一个空的USERS结点，用于匹配AU_getAllBookRecords的函数接口*/
	USERS *admin;
	admin=(USERS*)calloc(1,sizeof(USERS));
	statehead=AU_getAllBookRecords(databaseName,admin);
	qtr=statehead;
	while(qtr!=NULL){
		find=getBookInfo(databaseName,qtr->bookid);
		p=head; 
		while(p!=NULL){
			if(strcmp(p->category,find->category)==0){
				(p->TotalBorrowed)++;                  //找到一次该种类的被借阅书籍则该种书籍借阅总量加一 
				break;
			}
			p=p->next;                                 //不是该种类则继续往后找 
		} 
		qtr=qtr->next;       //找下一本被借阅的书籍的种类 
	} 
	return head; 
} 

//////////////////////////////////////////////////////////////////////////////////////
/*排序模块*/

/*对书籍信息进行排序*/
/*按书号排序(暂按升序)*/ 
BOOKS *rank_id(BOOKS *bookhead){
	BOOKS *p1,*p2,*tail=NULL;              /*tail用于记录从链表尾开始的冒泡完成的位置*/ 
	p1=(BOOKS*)malloc(sizeof(BOOKS));      /*分配一个BOOKS结点的内存*/ 
	p1->next=bookhead;                     /*建立一个表头节点*/ 
	bookhead=p1;
	while(bookhead->next!=tail){           /*下一个结点地址若和tail重合说明已经冒泡结束*/
		p1=bookhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(strcmp(p1->next->id,p2->next->id)>0){   /*若链表数据不符合升序则交换结点位置*/
				p1->next=p2->next;
				p2->next=p2->next->next;
				p1->next->next=p2;
				p1=p1->next;
			}
			else{
				p1=p2;
				p2=p1->next;
			}
		}
		tail=p2;                            /*每冒泡一趟都将p2的最终位置记为tail*/
	}
	p1=bookhead;                            /*释放表头结点*/ 
	bookhead=bookhead->next;
	free(p1);
	return bookhead;                        /*返回新的链表头结点*/
}

/*按图书名排序(暂按升序)*/ 
BOOKS *rank_bookname(BOOKS *bookhead){
	BOOKS *p1,*p2,*tail=NULL;              /*tail用于记录从链表尾开始的冒泡完成的位置*/ 
	p1=(BOOKS*)malloc(sizeof(BOOKS));      /*分配一个BOOKS结点的内存*/ 
	p1->next=bookhead;                     /*建立一个表头节点*/ 
	bookhead=p1;
	while(bookhead->next!=tail){           /*下一个结点地址若和tail重合说明已经冒泡结束*/
		p1=bookhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(strcmp(p1->next->bookname,p2->next->bookname)>0){   /*若链表数据不符合升序则交换结点位置*/
				p1->next=p2->next;
				p2->next=p2->next->next;
				p1->next->next=p2;
				p1=p1->next;
			}
			else{
				p1=p2;
				p2=p1->next;
			}
		}
		tail=p2;                            /*每冒泡一趟都将p2的最终位置记为tail*/
	}
	p1=bookhead;                            /*释放表头结点*/ 
	bookhead=bookhead->next;
	free(p1);
	return bookhead;                        /*返回新的链表头结点*/
}

/*
 *按第一作者排序(暂按升序)
 *要求每个作者的名字中有且仅有一个空格 
 */ 
BOOKS *rank_firstauthor(BOOKS *bookhead){
	BOOKS *p1,*p2,*tail=NULL;              /*tail用于记录从链表尾开始的冒泡完成的位置*/ 
	p1=(BOOKS*)malloc(sizeof(BOOKS));      /*分配一个BOOKS结点的内存*/ 
	p1->next=bookhead;                     /*建立一个表头节点*/ 
	bookhead=p1;
	int i;
	char *s1=NULL,*s2=NULL;                /*用于存储两个第一作者字符串 */
	while(bookhead->next!=tail){           /*下一个结点地址若和tail重合说明已经冒泡结束*/
		p1=bookhead;
		p2=p1->next;
		while(p2->next!=tail){
			/*找出前一个结点的第一作者*/
			i=0;
			while(*(p1->next->bookname+i)!=' '){//允许被空格打断一次 
				while(*(p1->next->bookname+i)!=' ')i++;//记录需要分配的内存长度 
				i++;
			}
			s1=(char*)calloc(i+1,sizeof(char));
			i=0;
			while(*(p1->next->bookname+i)!=' '){
				while(*(p1->next->bookname+i)!=' '){
					s1[i]=*(p1->next->bookname+i);//将第一作者的名字赋值给s1对应字符串 
					i++;
				}
				s1[i]=*(p1->next->bookname+i);
				i++;
			}
			s1[i]='\0';
			/*找出后一个结点的第一作者*/
			i=0;
			while(*(p2->next->bookname+i)!=' '){//允许被空格打断一次 
				while(*(p2->next->bookname+i)!=' ')i++;//记录需要分配的内存长度
				i++;
			}
			s2=(char*)calloc(i+1,sizeof(char));
			i=0;
			while(*(p2->next->bookname+i)!=' '){
				while(*(p2->next->bookname+i)!=' '){
					s2[i]=*(p2->next->bookname+i);//将第一作者的名字赋值给s2对应字符串 
					i++;
				}
				s2[i]=*(p2->next->bookname+i);
				i++;
			}
			s2[i]='\0';
			/*让前两者的第一作者进行比较*/
			if(strcmp(s1,s2)>0){       /*若不符合升序则交换结点位置*/
				p1->next=p2->next;
				p2->next=p2->next->next;
				p1->next->next=p2;
				p1=p1->next;
			}
			else{
				p1=p2;
				p2=p1->next;
			}
			/*使用完后释放内存*/
			free(s1);
			free(s2);
		}
		tail=p2;                            /*每冒泡一趟都将p2的最终位置记为tail*/
	}
	p1=bookhead;                            /*释放表头结点*/
	bookhead=bookhead->next;
	free(p1);
	return bookhead;                        /*返回新的链表头结点*/
}

/*对用户信息进行排序*/ 
/*按用户id升序*/
USERS *rank_userid(char *databaseName,USERS *admin){
	USERS *userhead,*p1,*p2,*tail=NULL;              /*tail用于记录从链表尾开始的冒泡完成的位置*/ 
	userhead=AU_getAllUserInfo(databaseName,admin);  /*获取一个USERS信息链表的头结点*/
	p1=(USERS*)malloc(sizeof(USERS));                /*分配一个USERS结点的内存*/ 
	p1->next=userhead;                               /*建立一个表头节点*/
	userhead=p1;
	while(userhead->next!=tail){                     /*下一个结点地址若和tail重合说明已经冒泡结束*/
		p1=userhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(p1->next->id>p2->next->id){   /*若链表数据不符合升序则交换结点位置*/
				p1->next=p2->next;
				p2->next=p2->next->next;
				p1->next->next=p2;
				p1=p1->next;
			}
			else{
				p1=p2;
				p2=p1->next;
			}
		}
		tail=p2;                            /*每冒泡一趟都将p2的最终位置记为tail*/
	}
	p1=userhead;                            /*释放表头结点*/ 
	userhead=userhead->next;
	free(p1);
	return userhead;                        /*返回新的链表头结点*/
} 

/*按用户名排序*/
USERS *rank_username(char *databaseName,USERS *admin){
	USERS *userhead,*p1,*p2,*tail=NULL;              /*tail用于记录从链表尾开始的冒泡完成的位置*/
	userhead=AU_getAllUserInfo(databaseName,admin);  /*获取一个USERS信息链表的头结点*/
	p1=(USERS*)malloc(sizeof(USERS));                /*分配一个USERS结点的内存*/ 
	p1->next=userhead;                               /*建立一个表头节点*/
	userhead=p1;
	while(userhead->next!=tail){                     /*下一个结点地址若和tail重合说明已经冒泡结束*/
		p1=userhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(strcmp(p1->next->username,p2->next->username)>0){   /*若链表数据不符合升序则交换结点位置*/
				p1->next=p2->next;
				p2->next=p2->next->next;
				p1->next->next=p2;
				p1=p1->next;
			}
			else{
				p1=p2;
				p2=p1->next;
			}
		}
		tail=p2;                            /*每冒泡一趟都将p2的最终位置记为tail*/
	}
	p1=userhead;                            /*释放表头结点*/ 
	userhead=userhead->next;
	free(p1);
	return userhead;                        /*返回新的链表头结点*/
} 

/*按用户部门升序*/
USERS *rank_userdepart(char *databaseName,USERS *admin){
	USERS *userhead,*p1,*p2,*tail=NULL;              /*tail用于记录从链表尾开始的冒泡完成的位置*/
	userhead=AU_getAllUserInfo(databaseName,admin);  /*获取一个USERS信息链表的头结点*/
	p1=(USERS*)malloc(sizeof(USERS));                /*分配一个USERS结点的内存*/ 
	p1->next=userhead;                               /*建立一个表头节点*/
	userhead=p1;
	while(userhead->next!=tail){                     /*下一个结点地址若和tail重合说明已经冒泡结束*/
		p1=userhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(strcmp(p1->next->department,p2->next->department)>0){   /*若链表数据不符合升序则交换结点位置*/
				p1->next=p2->next;
				p2->next=p2->next->next;
				p1->next->next=p2;
				p1=p1->next;
			}
			else{
				p1=p2;
				p2=p1->next;
			}
		}
		tail=p2;                            /*每冒泡一趟都将p2的最终位置记为tail*/
	}
	p1=userhead;                            /*释放表头结点*/ 
	userhead=userhead->next;
	free(p1);
	return userhead;                        /*返回新的链表头结点*/
} 

///////////////////////////////////////////////////////////////////////////////////
/*其它函数*/

/*判断是否有目标字符串的连续子串与输入字符串相同或只有一个字母不同*/ 
bool cmp_keywords(char *key,char *target){
	char *p,*q;           /*用于处理输入的字符串和目标字符串*/ 
	int i,j;
	int sign;             /*用于标记字母不同的次数*/
	bool flag;            /*用于返回判断结果*/ 
	q=target;
	p=key;
	j=0;
	while(q[j]!='\0'){    /*仅当目标字符串扫描到尾部时停止*/
		i=0;
		flag=true;       /*事先置为true*/
		sign=0;           /*每次比较sign置0*/
		while(p[i]!='\0'){/*当输入的字符串扫描到尾部时停止*/
			if(q[j+i]=='\0'){/*当目标字符串到了结尾就停止比较*/
				flag=false;
				break;
			} 
			if(q[j+i]!=p[i]){
				sign++;   /*如果有一个字母不相同就标记一次*/
				if(sign==2){/*如果两个字母不同就认为不相同*/
					flag=false;
					break;
				}
			}
			i++;
		}
		if(flag)break;   /*一旦出现一次遍历后flag仍为true的情况说明存在这样的子串*/
		j++;
	}
	return flag;
}

/*此函数用于将单个book节点的内容复制到一个新的节点*/
BOOKS* copybooknode(BOOKS *ptr){
	BOOKS *newbooknode=NULL;
	newbooknode=(BOOKS*)malloc(sizeof(BOOKS));
	int j;
	/*copy bookid*/
	j=0;
	while(*(ptr->id+j)!='\0')j++;
	newbooknode->id=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->id+j)!='\0'){
		*(newbooknode->id+j)=*(ptr->id+j);
		j++;
	}
	*(newbooknode->id+j)='\0';
	/*copy bookname*/
	j=0;
	while(*(ptr->bookname+j)!='\0')j++;
	newbooknode->bookname=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->bookname+j)!='\0'){
		*(newbooknode->bookname+j)=*(ptr->bookname+j);
		j++;
	}
	*(newbooknode->bookname+j)='\0';
	/*copy bookkeywords*/
	j=0;
	while(*(ptr->keywords+j)!='\0')j++;
	newbooknode->keywords=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->keywords+j)!='\0'){
		*(newbooknode->keywords+j)=*(ptr->keywords+j);
		j++;
	}
	*(newbooknode->keywords+j)='\0';
	/*copy bookauthors*/
	j=0;
	while(*(ptr->authors+j)!='\0')j++;
	newbooknode->authors=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->authors+j)!='\0'){
		*(newbooknode->authors+j)=*(ptr->authors+j);
		j++;
	}
	*(newbooknode->authors+j)='\0';
	/*copy bookpublisher*/
	j=0;
	while(*(ptr->publisher+j)!='\0')j++;
	newbooknode->publisher=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->publisher+j)!='\0'){
		*(newbooknode->publisher+j)=*(ptr->publisher+j);
		j++;
	}
	*(newbooknode->publisher+j)='\0';
	/*copy bookpubtime*/
	j=0;
	while(*(ptr->pubtime+j)!='\0')j++;
	newbooknode->pubtime=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->pubtime+j)!='\0'){
		*(newbooknode->pubtime+j)=*(ptr->pubtime+j);
		j++;
	}
	*(newbooknode->pubtime+j)='\0';
	/*copy 库存数量*/
	newbooknode->quantity=ptr->quantity;
	/*copy 出借数量*/
	newbooknode->isborrowed=ptr->isborrowed; 
	/*copy category*/
	j=0;
	while(*(ptr->category+j)!='\0')j++;
	newbooknode->category=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->category+j)!='\0'){
		*(newbooknode->category+j)=*(ptr->category+j);
		j++;
	}
	*(newbooknode->category+j)='\0';
	/*copy bookregtime*/
	j=0;
	while(*(ptr->regtime+j)!='\0')j++;
	newbooknode->regtime=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->regtime+j)!='\0'){
		*(newbooknode->regtime+j)=*(ptr->regtime+j);
		j++;
	}
	*(newbooknode->regtime+j)='\0';
	/*copy next*/
	newbooknode->next=NULL;
	return newbooknode;
}

/*此函数将一个BOOKSTATE结点的内容复制到一个新建的结点中*/
BOOKSTATE *copystatenode(BOOKSTATE *ptr){
	BOOKSTATE *newstatenode=NULL;
	newstatenode=(BOOKSTATE*)malloc(sizeof(BOOKSTATE));
	int j;
	/*copy id*/
	newstatenode->id=ptr->id;
	/*copy userid*/
	newstatenode->userid=ptr->userid;
	/*copy bookid*/
	j=0;
	while(*(ptr->bookid+j)!='\0')j++;
	newstatenode->bookid=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->bookid+j)!='\0'){
		*(newstatenode->bookid+j)=*(ptr->bookid+j);
		j++;
	}
	*(newstatenode->bookid+j)='\0';
	/*copy borrowdate*/
	j=0;
	while(*(ptr->borrowdate+j)!='\0')j++;
	newstatenode->borrowdate=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->borrowdate+j)!='\0'){
		*(newstatenode->borrowdate+j)=*(ptr->borrowdate+j);
		j++;
	}
	*(newstatenode->borrowdate+j)='\0';
	/*copy duedate*/
	j=0;
	while(*(ptr->duedate+j)!='\0')j++;
	newstatenode->duedate=(char*)calloc(j,sizeof(char));
	j=0;
	while(*(ptr->duedate+j)!='\0'){
		*(newstatenode->duedate+j)=*(ptr->duedate+j);
		j++;
	}
	*(newstatenode->duedate+j)='\0';
	/*copy terminated*/
	newstatenode->terminated=ptr->terminated;
	/*copy next*/
	newstatenode->next=NULL;
	return newstatenode;
} 

/*统计不同类别图书的借阅情况时释放其BOOKAMOUNT结果链表的函数*/
int freeBookAmount(BOOKAMOUNT *input){
	BOOKAMOUNT *ptr,*qtr;
	ptr=qtr=input;
	if(ptr!=NULL)free(ptr->category);
	while(ptr!=NULL){
		qtr=ptr->next;
		if(qtr!=NULL)free(qtr->category);
		free(ptr);
		ptr=qtr;
	}
	return SUCCESS;
}

/* 
int main(){
	return 0;
}
*/
