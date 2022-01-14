#include"dataDeal.h"

////////////////////////////////////////////////////////////////////////////////////////////////
/*����ģ��*/

/*
 *��id�Ų����鼮
 *ʹ��getBookInfo()���������һ�����������鼮��Ϣ��BOOKS���ָ��  
 */


/*��booknameģ������*/
BOOKS *searchbook_name(char *databaseName,char *bookname){  //�������ݿ���������������� 
	BOOKS *result_head,*result_tail,*p,*ptr,*bookhead;
	bookhead=getAllBooksInfo(databaseName);    //��ȡ����ѯ���ݿ���鼮��Ϣͷ���
	ptr=bookhead;
	result_head=result_tail=NULL;
	int i;
	bool flag;
	/*��ȷ��������*/
	i=0;
	while(ptr!=NULL){
		if(strcmp(bookname,ptr->bookname)==0){  //�ҵ�����Ҫ��Ľ��ʱ���Ʋ����ӵ��½�������� 
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
		i++;         //��¼������  
		ptr=ptr->next;
	} 
	/*
	 *��¼�Ƿ��ڱ��ε����б��������� 
	 *opr[i]Ϊ1ʱ˵����������
	 *ÿ��opr[i]��Ӧһ��BOOKS��� 
	 */
	int *opr;
	opr=(int*)calloc(i,sizeof(int));       //�����뵱ǰ��������Ӧ���ڴ� 
	ptr=bookhead;
	i=0;
	while(ptr!=NULL){
		if(strcmp(bookname,ptr->bookname)==0){  //�ҵ����Ͼ�ȷ����Ҫ��Ľ��ʱ���Ϊ�������� 
			opr[i]=1; 
		}
		i++;
		ptr=ptr->next;
	}
	/*�ո�ָ�ؼ��ʲ���*/
	char *keyword;
	int start,end;               //��¼һ�����ʵ�һ�������һ����ĸ��λ�� 
	int j=0,k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //���ڱ�ʾ�Ƿ��������� 
		while(bookname[i]!='\0'){
			if(bookname[i]>='A'&&bookname[i]<='Z'||bookname[i]>='a'&&bookname[i]<='z'){
				if(bookname[i+1]>='A'&&bookname[i+1]||bookname[i+1]>='a'&&bookname[i+1]<='z')i++;
				else{               //�����һ���ַ�������ĸ˵��һ�����ʽ���
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //���ƴ�start��end�Ĺؼ��ʵ�keywordָ����ַ��� 
						keyword[j]=bookname[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->bookname);      //�ȶԹؼ��ʺ����� 
					free(keyword);                                 //ÿ���ؼ��ʱȶ����Ժ󽫷�����ڴ��ͷ� 
					i++;
				}
				if(flag)break;                                     //һ����һ�����������������Ϊ�ҵ��� 
			}
			else{
				if(bookname[i+1]>='A'&&bookname[i+1]||bookname[i+1]>='a'&&bookname[i+1]<='z'){
					start=i+1;      //��ǰ������ĸ����һ���������һ��λ��Ϊstart 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //������������֮ǰ�Ĳ�����δ�ҵ���ʱ����Ӵ˽�� 
			opr[k]=1;
			p=copybooknode(ptr);    //����һ���½�� 
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
	/*����ģ������*/
	ptr=bookhead;
	i=0;
	while(ptr!=NULL){
		flag=(strstr(ptr->bookname,bookname)!=NULL);  //�жϸý���BOOK�������Ƿ�������ؼ��� ������flag=TRUE 
		if(flag&&opr[i]==0){        //������������֮ǰ�Ĳ�����δ�ҵ���ʱ��Ӵ˽�� 
			opr[i]=1;
			p=copybooknode(ptr);    //����ptrָ��Ľ�� 
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
	free(opr);                         //һ�������ļ��������������ͷ�opr���ڴ� 
	return result_head;
}

/*�����ߵ�ģ������*/
BOOKS *searchbook_authors(char *databaseName,char *authors){  //�������ݿ������������������ 
	BOOKS *result_head,*result_tail,*p,*ptr,*bookhead;
	bookhead=getAllBooksInfo(databaseName);    //��ȡ����ѯ���ݿ���鼮��Ϣͷ��� 
	ptr=bookhead;
	result_head=result_tail=NULL;
	int i=0;
	bool flag;
	/*��ȷ��������*/
	while(ptr!=NULL){
		if(strcmp(authors,ptr->authors)==0){  //�ҵ�����Ҫ��Ľ��ʱ���Ʋ����ӵ���������� 
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
	 *��¼�Ƿ��ڱ��ε����б��������� 
	 *opr[i]Ϊ1ʱ˵����������
	 *ÿ��opr[i]��Ӧһ��BOOKS��� 
	 */
	int *opr;
	opr=(int*)calloc(i,sizeof(int));       //�����뵱ǰ��������Ӧ���ڴ� 
	ptr=bookhead;
	i=0;
	while(ptr!=NULL){
		if(strcmp(authors,ptr->authors)==0){  //�ҵ����Ͼ�ȷ����Ҫ��Ľ��ʱ���Ϊ�������� 
			opr[i]=1; 
		}
		i++;
		ptr=ptr->next;
	}
	/*������߲���*/
	char *keyword;
	int start,end;               //��¼һ�����ʵ�һ�������һ����ĸ��λ�� 
	int j=0,k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //���ڱ�ʾ�Ƿ��������� 
		while(authors[i]!='\0'){
			if(authors[i]>='A'&&authors[i]<='Z'||authors[i]>='a'&&authors[i]<='z'){
				if(authors[i+1]>='A'&&authors[i+1]||authors[i+1]>='a'&&authors[i+1]<='z')i++;
				else{               //�����һ���ַ�������ĸ˵��һ�����ʽ���
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //���ƴ�start��end�Ĺؼ��ʵ�keywordָ����ַ��� 
						keyword[j]=authors[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->authors);      //�ȶԹؼ��ʺ����� 
					free(keyword);                                 //ÿ���ؼ��ʱȶ����Ժ󽫷�����ڴ��ͷ� 
					i++;
				}
				if(flag)break;                                     //һ����һ�����������������Ϊ�ҵ��� 
			}
			else{
				if(authors[i+1]>='A'&&authors[i+1]||authors[i+1]>='a'&&authors[i+1]<='z'){
					start=i+1;      //��ǰ������ĸ����һ���������һ��λ��Ϊstart 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //������������֮ǰ�Ĳ�����δ�ҵ���ʱ����Ӵ˽�� 
			opr[k]=1;
			p=copybooknode(ptr);    //����һ���½�� 
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
	/*�ո�ָ�ؼ��ʲ���*/
	k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //���ڱ�ʾ�Ƿ��������� 
		while(authors[i]!='\0'){
			if(authors[i]>='A'&&authors[i]<='Z'||authors[i]>='a'&&authors[i]<='z'){
				if(authors[i+1]>='A'&&authors[i+1]||authors[i+1]>='a'&&authors[i+1]<='z')i++;
				else{               //�����һ���ַ�������ĸ˵��һ�����ʽ���
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //���ƴ�start��end�Ĺؼ��ʵ�keywordָ����ַ��� 
						keyword[j]=authors[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->authors);      //�ȶԹؼ��ʺ����� 
					free(keyword);                                 //ÿ���ؼ��ʱȶ����Ժ󽫷�����ڴ��ͷ� 
					i++;
				}
				if(flag)break;                                     //һ����һ�����������������Ϊ�ҵ��� 
			}
			else{
				if(authors[i+1]>='A'&&authors[i+1]||authors[i+1]>='a'&&authors[i+1]<='z'){
					start=i+1;      //��ǰ������ĸ����һ���������һ��λ��Ϊstart 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //������������֮ǰ�Ĳ�����δ�ҵ���ʱ����Ӵ˽�� 
			opr[k]=1;
			p=copybooknode(ptr);    //����һ���½�� 
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
	free(opr);                         //һ�������ļ��������������ͷ�opr���ڴ� 
	return result_head;
}

/*���ؼ��ʵ�ģ������*/
BOOKS *searchbook_keywords(char *databaseName,char *keywords){  //�������ݿ�����������Ĺؼ��� 
	BOOKS *result_head,*result_tail,*p,*ptr,*bookhead;
	bookhead=getAllBooksInfo(databaseName);    //��ȡ����ѯ���ݿ���鼮��Ϣͷ���
	ptr=bookhead;
	result_head=result_tail=NULL;
	int i=0;
	bool flag;
	/*��ȷ��������*/
	while(ptr!=NULL){
		if(strcmp(keywords,ptr->keywords)==0){  //�ҵ�����Ҫ��Ľ��ʱ���Ʋ����ӵ��½�������� 
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
	 *��¼�Ƿ��ڱ��ε����б��������� 
	 *opr[i]Ϊ1ʱ˵����������
	 *ÿ��opr[i]��Ӧһ��BOOKS��� 
	 */
	int *opr;
	opr=(int*)calloc(i,sizeof(int));       //�����뵱ǰ��������Ӧ���ڴ� 
	ptr=bookhead;
	i=0;
	while(ptr!=NULL){
		if(strcmp(keywords,ptr->keywords)==0){  //�ҵ����Ͼ�ȷ����Ҫ��Ľ��ʱ���Ϊ�������� 
			opr[i]=1;
		}
		i++;
		ptr=ptr->next;
	}
	/*����ؼ��ʲ���*/
	char *keyword;
	int start,end;               //��¼һ�����ʵ�һ�������һ����ĸ��λ�� 
	int j=0,k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //���ڱ�ʾ�Ƿ��������� 
		while(keywords[i]!='\0'){
			if(keywords[i]>='A'&&keywords[i]<='Z'||keywords[i]>='a'&&keywords[i]<='z'){
				if(keywords[i+1]>='A'&&keywords[i+1]||keywords[i+1]>='a'&&keywords[i+1]<='z')i++;
				else{               //�����һ���ַ�������ĸ˵��һ�����ʽ���
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //���ƴ�start��end�Ĺؼ��ʵ�keywordָ����ַ��� 
						keyword[j]=keywords[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->keywords);      //�ȶԹؼ��ʺ�����Ĺؼ��� 
					free(keyword);                                 //ÿ���ؼ��ʱȶ����Ժ󽫷�����ڴ��ͷ� 
					i++;
				}
				if(flag)break;                                     //һ����һ�����������������Ϊ�ҵ��� 
			}
			else{
				if(keywords[i+1]>='A'&&keywords[i+1]||keywords[i+1]>='a'&&keywords[i+1]<='z'){
					start=i+1;      //��ǰ������ĸ����һ���������һ��λ��Ϊstart 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //������������֮ǰ�Ĳ�����δ�ҵ���ʱ����Ӵ˽�� 
			opr[k]=1;
			p=copybooknode(ptr);    //����һ���½�� 
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
	/*�ո�ָ�ؼ��ʲ���*/
	k=0;
	ptr=bookhead;
	while(ptr!=NULL){
		start=end=0;
		i=0;
		flag=false;                  //���ڱ�ʾ�Ƿ��������� 
		while(keywords[i]!='\0'){
			if(keywords[i]>='A'&&keywords[i]<='Z'||keywords[i]>='a'&&keywords[i]<='z'){
				if(keywords[i+1]>='A'&&keywords[i+1]||keywords[i+1]>='a'&&keywords[i+1]<='z')i++;
				else{               //�����һ���ַ�������ĸ˵��һ�����ʽ���
					end=i; 
					keyword=(char*)calloc(end-start+2,sizeof(char));
					j=0;
					while(j<end-start){                         //���ƴ�start��end�Ĺؼ��ʵ�keywordָ����ַ��� 
						keyword[j]=keywords[start+j];
						j++;
					}
					keyword[j]='\0';
					flag=cmp_keywords(keyword,ptr->keywords);      //�ȶԹؼ��ʺ�����Ĺؼ��� 
					free(keyword);                                 //ÿ���ؼ��ʱȶ����Ժ󽫷�����ڴ��ͷ� 
					i++;
				}
				if(flag)break;                                     //һ����һ�����������������Ϊ�ҵ��� 
			}
			else{
				if(keywords[i+1]>='A'&&keywords[i+1]||keywords[i+1]>='a'&&keywords[i+1]<='z'){
					start=i+1;      //��ǰ������ĸ����һ���������һ��λ��Ϊstart 
				}
				i++;
			}
		}
		if(flag&&opr[k]==0){    //������������֮ǰ�Ĳ�����δ�ҵ���ʱ����Ӵ˽�� 
			opr[k]=1;
			p=copybooknode(ptr);    //����һ���½�� 
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
	free(opr);                         //һ�������ļ��������������ͷ�opr���ڴ� 
	return result_head;
}

/*���鼮�������*/
BOOKSTATE *searchbookstate(char *databaseName,char *id){  //�������ݿ������û������Ҫ�������鼮id 
	BOOKSTATE *ptr,*result_state,*statehead;
	/*����һ���յ�USERS��㣬����ƥ��AU_getAllBookRecords�ĺ����ӿ�*/
	USERS *admin;
	admin=(USERS*)calloc(1,sizeof(USERS));
	statehead=AU_getAllBookRecords(databaseName,admin);   //��ȡ��ǰ�������鼮��BOOKSTATE��ͷ��� 
	result_state=NULL;
	ptr=statehead;
	while(ptr!=NULL){
		if(strcmp(ptr->bookid,id)==0){    //��id��ͬ������һ��BOOKSTATE��� 
			result_state=copystatenode(ptr); 
			break;
		}
		ptr=ptr->next;
	}
	return result_state;
} 

/*
 *���û���Ϣ
 *ʹ��AU_getUSERInfo()������ȡһ��USERSָ��
 */


/*
 *���û�������Ϣ
 *ʹ��AU_getBookRecordsByUser()������ȡһ��BOOKSTATE���ͷ���ָ��  
 */

////////////////////////////////////////////////////////////////////////////////////// 
/*ͳ��ģ��*/

/*ͳ�����ݿ���ͼ������*/
int CountTotalBook(char *databaseName){
	BOOKS *bookhead,*ptr;
	int count=0;           //���ڼ��� 
	bookhead=getAllBooksInfo(databaseName);
	ptr=bookhead;
	while(ptr!=NULL){
		count++;                //ͳ��������ÿ��BOOKS����Ӧһ���� 
		ptr=ptr->next;
	}
	return count;
} 

/*ͳ�����ݿ���ͼ���ܽ�����*/
int CountTotalBorrowed(char *databaseName){
	BOOKSTATE *statehead,*ptr;
	/*����һ���յ�USERS��㣬����ƥ��AU_getAllBookRecords�ĺ����ӿ�*/
	USERS *admin;
	admin=(USERS*)calloc(1,sizeof(USERS));
	int count=0;           //���ڼ��� 
	statehead=AU_getAllBookRecords(databaseName,admin);
	ptr=statehead;
	while(ptr!=NULL){
		count++;                //ͳ���ܽ�������ÿ��BOOKSTATE����Ӧһ���� 
		ptr=ptr->next;
	}
	return count;
} 

/*ͳ�Ʋ�ͬ���ͼ��Ľ������*/
BOOKAMOUNT *BorrowedInfo(char *databaseName){
	BOOKAMOUNT *head,*tail,*p;    //�����½�����
	head=tail=NULL;
	BOOKS *bookhead,*ptr;         //���ڱ���BOOKS�� 
	bookhead=getAllBooksInfo(databaseName);
	ptr=bookhead;
	int count=0;                    //���ڼ�¼ĳ�����ж��ٲ����� 
	if(ptr!=NULL){
		p=(BOOKAMOUNT*)malloc(sizeof(BOOKAMOUNT));      //����ͷ��� 
		head=p;
		p->next=NULL; 
		p->category=(char*)calloc(strlen(ptr->category),sizeof(char));  //Ϊ�µĽ���е�category�����ڴ� 
		strcpy(head->category,ptr->category);           //ֱ�Ӹ��Ƶ�һ����� 
		p->TotalBorrowed=0;                         //�������ȳ�ʼ��Ϊ0 
		ptr=ptr->next;
		count++; 
		tail=p; 
	}
	while(ptr!=NULL){
		if(strcmp(tail->category,ptr->category)==0){    //����ǰ��������ͼ�������ǰһ����ͬ������� 
			count++;
			ptr=ptr->next;
		}
		else{                                           //���ҵ�һ����ͬ��ǰһ��������½�һ����㲢��������� 
			p=(BOOKAMOUNT*)malloc(sizeof(BOOKAMOUNT));
			p->category=(char*)calloc(strlen(ptr->category),sizeof(char));  //Ϊ�µĽ���е�category�����ڴ�
			strcpy(p->category,ptr->category);          //�����µ���� 
			tail->TotalBooks=count;                     //����ǰ�ۻ���ͬ�����������ֵ��ǰһ�����
			p->TotalBorrowed=0;                     //�������ȳ�ʼ��Ϊ0 
			p->next=NULL; 
			tail->next=p;
			tail=p;
			count=1;                                    //��������1 
			ptr=ptr->next;
		}
	}
	if(count!=0){                                       //�����ڼ���ʱ����ptr=NULL���˳�ѭ������׷��һ�θ�ֵ 
		tail->TotalBooks=count;
	}
	/*����ÿ���������Ľ�����*/
	BOOKSTATE *statehead,*qtr;
	BOOKS *find;                                      //���ڼ�¼ÿ��BOOKSTATE��Ӧ��BOOKS��� 
	/*����һ���յ�USERS��㣬����ƥ��AU_getAllBookRecords�ĺ����ӿ�*/
	USERS *admin;
	admin=(USERS*)calloc(1,sizeof(USERS));
	statehead=AU_getAllBookRecords(databaseName,admin);
	qtr=statehead;
	while(qtr!=NULL){
		find=getBookInfo(databaseName,qtr->bookid);
		p=head; 
		while(p!=NULL){
			if(strcmp(p->category,find->category)==0){
				(p->TotalBorrowed)++;                  //�ҵ�һ�θ�����ı������鼮������鼮����������һ 
				break;
			}
			p=p->next;                                 //���Ǹ���������������� 
		} 
		qtr=qtr->next;       //����һ�������ĵ��鼮������ 
	} 
	return head; 
} 

//////////////////////////////////////////////////////////////////////////////////////
/*����ģ��*/

/*���鼮��Ϣ��������*/
/*���������(�ݰ�����)*/ 
BOOKS *rank_id(BOOKS *bookhead){
	BOOKS *p1,*p2,*tail=NULL;              /*tail���ڼ�¼������β��ʼ��ð����ɵ�λ��*/ 
	p1=(BOOKS*)malloc(sizeof(BOOKS));      /*����һ��BOOKS�����ڴ�*/ 
	p1->next=bookhead;                     /*����һ����ͷ�ڵ�*/ 
	bookhead=p1;
	while(bookhead->next!=tail){           /*��һ������ַ����tail�غ�˵���Ѿ�ð�ݽ���*/
		p1=bookhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(strcmp(p1->next->id,p2->next->id)>0){   /*���������ݲ����������򽻻����λ��*/
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
		tail=p2;                            /*ÿð��һ�˶���p2������λ�ü�Ϊtail*/
	}
	p1=bookhead;                            /*�ͷű�ͷ���*/ 
	bookhead=bookhead->next;
	free(p1);
	return bookhead;                        /*�����µ�����ͷ���*/
}

/*��ͼ��������(�ݰ�����)*/ 
BOOKS *rank_bookname(BOOKS *bookhead){
	BOOKS *p1,*p2,*tail=NULL;              /*tail���ڼ�¼������β��ʼ��ð����ɵ�λ��*/ 
	p1=(BOOKS*)malloc(sizeof(BOOKS));      /*����һ��BOOKS�����ڴ�*/ 
	p1->next=bookhead;                     /*����һ����ͷ�ڵ�*/ 
	bookhead=p1;
	while(bookhead->next!=tail){           /*��һ������ַ����tail�غ�˵���Ѿ�ð�ݽ���*/
		p1=bookhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(strcmp(p1->next->bookname,p2->next->bookname)>0){   /*���������ݲ����������򽻻����λ��*/
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
		tail=p2;                            /*ÿð��һ�˶���p2������λ�ü�Ϊtail*/
	}
	p1=bookhead;                            /*�ͷű�ͷ���*/ 
	bookhead=bookhead->next;
	free(p1);
	return bookhead;                        /*�����µ�����ͷ���*/
}

/*
 *����һ��������(�ݰ�����)
 *Ҫ��ÿ�����ߵ����������ҽ���һ���ո� 
 */ 
BOOKS *rank_firstauthor(BOOKS *bookhead){
	BOOKS *p1,*p2,*tail=NULL;              /*tail���ڼ�¼������β��ʼ��ð����ɵ�λ��*/ 
	p1=(BOOKS*)malloc(sizeof(BOOKS));      /*����һ��BOOKS�����ڴ�*/ 
	p1->next=bookhead;                     /*����һ����ͷ�ڵ�*/ 
	bookhead=p1;
	int i;
	char *s1=NULL,*s2=NULL;                /*���ڴ洢������һ�����ַ��� */
	while(bookhead->next!=tail){           /*��һ������ַ����tail�غ�˵���Ѿ�ð�ݽ���*/
		p1=bookhead;
		p2=p1->next;
		while(p2->next!=tail){
			/*�ҳ�ǰһ�����ĵ�һ����*/
			i=0;
			while(*(p1->next->bookname+i)!=' '){//�����ո���һ�� 
				while(*(p1->next->bookname+i)!=' ')i++;//��¼��Ҫ������ڴ泤�� 
				i++;
			}
			s1=(char*)calloc(i+1,sizeof(char));
			i=0;
			while(*(p1->next->bookname+i)!=' '){
				while(*(p1->next->bookname+i)!=' '){
					s1[i]=*(p1->next->bookname+i);//����һ���ߵ����ָ�ֵ��s1��Ӧ�ַ��� 
					i++;
				}
				s1[i]=*(p1->next->bookname+i);
				i++;
			}
			s1[i]='\0';
			/*�ҳ���һ�����ĵ�һ����*/
			i=0;
			while(*(p2->next->bookname+i)!=' '){//�����ո���һ�� 
				while(*(p2->next->bookname+i)!=' ')i++;//��¼��Ҫ������ڴ泤��
				i++;
			}
			s2=(char*)calloc(i+1,sizeof(char));
			i=0;
			while(*(p2->next->bookname+i)!=' '){
				while(*(p2->next->bookname+i)!=' '){
					s2[i]=*(p2->next->bookname+i);//����һ���ߵ����ָ�ֵ��s2��Ӧ�ַ��� 
					i++;
				}
				s2[i]=*(p2->next->bookname+i);
				i++;
			}
			s2[i]='\0';
			/*��ǰ���ߵĵ�һ���߽��бȽ�*/
			if(strcmp(s1,s2)>0){       /*�������������򽻻����λ��*/
				p1->next=p2->next;
				p2->next=p2->next->next;
				p1->next->next=p2;
				p1=p1->next;
			}
			else{
				p1=p2;
				p2=p1->next;
			}
			/*ʹ������ͷ��ڴ�*/
			free(s1);
			free(s2);
		}
		tail=p2;                            /*ÿð��һ�˶���p2������λ�ü�Ϊtail*/
	}
	p1=bookhead;                            /*�ͷű�ͷ���*/
	bookhead=bookhead->next;
	free(p1);
	return bookhead;                        /*�����µ�����ͷ���*/
}

/*���û���Ϣ��������*/ 
/*���û�id����*/
USERS *rank_userid(char *databaseName,USERS *admin){
	USERS *userhead,*p1,*p2,*tail=NULL;              /*tail���ڼ�¼������β��ʼ��ð����ɵ�λ��*/ 
	userhead=AU_getAllUserInfo(databaseName,admin);  /*��ȡһ��USERS��Ϣ�����ͷ���*/
	p1=(USERS*)malloc(sizeof(USERS));                /*����һ��USERS�����ڴ�*/ 
	p1->next=userhead;                               /*����һ����ͷ�ڵ�*/
	userhead=p1;
	while(userhead->next!=tail){                     /*��һ������ַ����tail�غ�˵���Ѿ�ð�ݽ���*/
		p1=userhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(p1->next->id>p2->next->id){   /*���������ݲ����������򽻻����λ��*/
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
		tail=p2;                            /*ÿð��һ�˶���p2������λ�ü�Ϊtail*/
	}
	p1=userhead;                            /*�ͷű�ͷ���*/ 
	userhead=userhead->next;
	free(p1);
	return userhead;                        /*�����µ�����ͷ���*/
} 

/*���û�������*/
USERS *rank_username(char *databaseName,USERS *admin){
	USERS *userhead,*p1,*p2,*tail=NULL;              /*tail���ڼ�¼������β��ʼ��ð����ɵ�λ��*/
	userhead=AU_getAllUserInfo(databaseName,admin);  /*��ȡһ��USERS��Ϣ�����ͷ���*/
	p1=(USERS*)malloc(sizeof(USERS));                /*����һ��USERS�����ڴ�*/ 
	p1->next=userhead;                               /*����һ����ͷ�ڵ�*/
	userhead=p1;
	while(userhead->next!=tail){                     /*��һ������ַ����tail�غ�˵���Ѿ�ð�ݽ���*/
		p1=userhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(strcmp(p1->next->username,p2->next->username)>0){   /*���������ݲ����������򽻻����λ��*/
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
		tail=p2;                            /*ÿð��һ�˶���p2������λ�ü�Ϊtail*/
	}
	p1=userhead;                            /*�ͷű�ͷ���*/ 
	userhead=userhead->next;
	free(p1);
	return userhead;                        /*�����µ�����ͷ���*/
} 

/*���û���������*/
USERS *rank_userdepart(char *databaseName,USERS *admin){
	USERS *userhead,*p1,*p2,*tail=NULL;              /*tail���ڼ�¼������β��ʼ��ð����ɵ�λ��*/
	userhead=AU_getAllUserInfo(databaseName,admin);  /*��ȡһ��USERS��Ϣ�����ͷ���*/
	p1=(USERS*)malloc(sizeof(USERS));                /*����һ��USERS�����ڴ�*/ 
	p1->next=userhead;                               /*����һ����ͷ�ڵ�*/
	userhead=p1;
	while(userhead->next!=tail){                     /*��һ������ַ����tail�غ�˵���Ѿ�ð�ݽ���*/
		p1=userhead;
		p2=p1->next;
		while(p2->next!=tail){
			if(strcmp(p1->next->department,p2->next->department)>0){   /*���������ݲ����������򽻻����λ��*/
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
		tail=p2;                            /*ÿð��һ�˶���p2������λ�ü�Ϊtail*/
	}
	p1=userhead;                            /*�ͷű�ͷ���*/ 
	userhead=userhead->next;
	free(p1);
	return userhead;                        /*�����µ�����ͷ���*/
} 

///////////////////////////////////////////////////////////////////////////////////
/*��������*/

/*�ж��Ƿ���Ŀ���ַ����������Ӵ��������ַ�����ͬ��ֻ��һ����ĸ��ͬ*/ 
bool cmp_keywords(char *key,char *target){
	char *p,*q;           /*���ڴ���������ַ�����Ŀ���ַ���*/ 
	int i,j;
	int sign;             /*���ڱ����ĸ��ͬ�Ĵ���*/
	bool flag;            /*���ڷ����жϽ��*/ 
	q=target;
	p=key;
	j=0;
	while(q[j]!='\0'){    /*����Ŀ���ַ���ɨ�赽β��ʱֹͣ*/
		i=0;
		flag=true;       /*������Ϊtrue*/
		sign=0;           /*ÿ�αȽ�sign��0*/
		while(p[i]!='\0'){/*��������ַ���ɨ�赽β��ʱֹͣ*/
			if(q[j+i]=='\0'){/*��Ŀ���ַ������˽�β��ֹͣ�Ƚ�*/
				flag=false;
				break;
			} 
			if(q[j+i]!=p[i]){
				sign++;   /*�����һ����ĸ����ͬ�ͱ��һ��*/
				if(sign==2){/*���������ĸ��ͬ����Ϊ����ͬ*/
					flag=false;
					break;
				}
			}
			i++;
		}
		if(flag)break;   /*һ������һ�α�����flag��Ϊtrue�����˵�������������Ӵ�*/
		j++;
	}
	return flag;
}

/*�˺������ڽ�����book�ڵ�����ݸ��Ƶ�һ���µĽڵ�*/
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
	/*copy �������*/
	newbooknode->quantity=ptr->quantity;
	/*copy ��������*/
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

/*�˺�����һ��BOOKSTATE�������ݸ��Ƶ�һ���½��Ľ����*/
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

/*ͳ�Ʋ�ͬ���ͼ��Ľ������ʱ�ͷ���BOOKAMOUNT�������ĺ���*/
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
