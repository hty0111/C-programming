//！本工程中所有文本框输入除修改界面的弹出窗口外，一开始都是空白状态，而修改的弹出窗口都要显示需要修改的那个数据 
#include "SIMS.h" 
int MouseAction=0;
int WindowNum=WELCOMEWINDOW;//初始界面为欢迎界面 
int IfFlag=0;//初始显示状态为默认值 
int STATUS=0;//初始状态栏为空 
int pIfFlag;
//模糊搜索栏 
BOOKS *BookResult=NULL;//仅用于储存检索返回的结果指针 
USERS *UserResult=NULL;//仅用于储存检索返回的结果指针

BOOKS *BookInfo=NULL;
BOOKSTATE *BookCurrentState;
USERS *UserInfo=NULL;

char userinfoIdSwap[SWAP_LIMIT];
char userinfoUsernameSwap[SWAP_LIMIT];
char userinfoPasswordsSwap[SWAP_LIMIT];
char userinfoGenderSwap[SWAP_LIMIT];
char userinfoDepartmentSwap[SWAP_LIMIT];
char userinfoBorrowedbooksSwap[SWAP_LIMIT];
char userinfoModeSwap[SWAP_LIMIT];
char userinfoRegtimeSwap[SWAP_LIMIT];

char bookinfoIdSwap[SWAP_LIMIT];
char bookinfoBooknameSwap[SWAP_LIMIT];
char bookinfoKeywordsSwap[SWAP_LIMIT];
char bookinfoAuthorsSwap[SWAP_LIMIT];
char bookinfoPublisherSwap[SWAP_LIMIT];
char bookinfoPubtimeSwap[SWAP_LIMIT];
char bookinfoQuantitySwap[SWAP_LIMIT];
char bookinfoIsborrowedSwap[SWAP_LIMIT];
char bookinfoCategorySwap[SWAP_LIMIT];
char bookinfoRegtimeSwap[SWAP_LIMIT];

char stateinfoIdSwap[SWAP_LIMIT];
char stateinfoUseridSwap[SWAP_LIMIT];
char stateinfoBookidSwap[SWAP_LIMIT];
char stateinfoBorrowdateSwap[SWAP_LIMIT];
char stateinfoDuedataSwap[SWAP_LIMIT];
char stateinfoTerminatedSwap[SWAP_LIMIT];

char amountCategorySwap[SWAP_LIMIT];
char amountTotalbooksSwap[SWAP_LIMIT];
char amountTotalborrowedSwap[SWAP_LIMIT];

extern char SERVER_ADDRESS[256];

/*搜索栏输入之后，选择是根据什么进行搜索*/ 
void drawSearchchoicepop(){
	double x,y,w,hx,hs;
	x=3;
	y=3;
	w=3.5;
	hx=1;
	hs=0.3;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);	
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);	
	SetPenColor("Black");
	drawRectangle(x,y+hx,w,hs,0);	
	MovePen(x+0.1,y+hx+0.1);
	SetPenColor("Black");
	drawLabel(x+0.2,y+0.5,"请根据输入内容选择搜索方式：");
	if(BookResult!=NULL){
		freeAllBooks(BookResult);    //如果BookResult有指向的内存空间则释放
		BookResult=NULL; 
	}
	if(button(GenUIID(0),x+0.2,y+0.1,0.6,0.25,"按书号")){
		BookResult=getBookInfo(DATABASE,searchtext);     //返回查到的书籍信息到全局指针变量 
		IfFlag=Search_pop; //后端按照书号查找，查找完毕之后跳转到Search_pop界面 
	}
	if(button(GenUIID(0),x+0.2+0.65,y+0.1,0.6,0.25,"按书名")){
		BookResult=searchbook_name(DATABASE,searchtext);     //返回查到的书籍信息到全局指针变量
		IfFlag=Search_pop; // 后端按照书名查找，查找完毕之后跳转到Search_pop界面 
	}
	if(button(GenUIID(0),x+0.2+1.3,y+0.1,0.6,0.25,"按作者")){
		BookResult=searchbook_authors(DATABASE,searchtext);     //返回查到的书籍信息到全局指针变量
		IfFlag=Search_pop; //后端按照作者查找，查找完毕之后跳转到Search_pop界面 
	}
	if(button(GenUIID(0),x+0.2+0.65*3,y+0.1,0.6,0.25,"按关键词")){
		BookResult=searchbook_keywords(DATABASE,searchtext);     //返回查到的书籍信息到全局指针变量
		IfFlag=Search_pop; //后端按照关键词查找，查找完毕之后跳转到Search_pop界面 
	}	
}

/*Search_pop界面，用于显示搜索结果 */ 
void drawSearchpop()
{
	double x,y,w,hx,hs,d;
	x=0.3;
	y=0.6;
	w=9.4;
	hx=4.4;
	hs=0.4;
	d=0.22;
	SetPointSize(1);
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"搜索结果");
	drawLabel(x+0.1,y+hx-0.2,"排序方式："); 
	if(button(GenUIID(0),x+0.9,y+hx-0.26,0.52,0.23,"按书名")){
		BookResult=rank_bookname(BookResult); //后端按照书名排序并返回给全局指针变量 
	} 
	if(button(GenUIID(0),x+1.5,y+hx-0.26,0.52,0.23,"按书号")){
		BookResult=rank_id(BookResult); //后端按照书号排序并返回给全局指针变量 
	} 
	if(button(GenUIID(0),x+2.1,y+hx-0.26,0.86,0.23,"按第一作者")){
		BookResult=rank_firstauthor(BookResult); //后端按照第一作者排序并返回给全局指针变量 
	}
	SetPenColor("MidnightBlue");
	drawRectangle(x+0.1,y+0.1,w-0.2,hx-0.4,0);
	drawRectangle(x+0.1,y+0.1,w-0.2,0.4,0);
	drawLabel(x+0.4,y+hx-0.5,"书名");
	drawLabel(x+1.5,y+hx-0.5,"书号");
	drawLabel(x+2.6,y+hx-0.5,"作者");
	drawLabel(x+3.8,y+hx-0.5,"关键词");
	drawLabel(x+5,y+hx-0.5,"类别"); 
	drawLabel(x+6.2,y+hx-0.5,"出版商");
	drawLabel(x+7.4,y+hx-0.5,"出版时间");
	drawLabel(x+8.6,y+hx-0.5,"库存数量");
	BOOKS *ptr;          //用于遍历结果链表 
	int count=0;         //用于计数 
	ptr=BookResult;
	while(ptr!=NULL){      //逐条输出查找结果 
		/*将当前结点处的书籍信息存入缓存区*/ 
		strcpy(bookinfoBooknameSwap,ptr->bookname);
		strcpy(bookinfoIdSwap,ptr->id);
		strcpy(bookinfoAuthorsSwap,ptr->authors);
		strcpy(bookinfoKeywordsSwap,ptr->keywords);
		strcpy(bookinfoCategorySwap,ptr->category);
		strcpy(bookinfoPublisherSwap,ptr->publisher);
		strcpy(bookinfoPubtimeSwap,ptr->pubtime);
		sprintf(bookinfoQuantitySwap,"%d",ptr->quantity);
		/*从缓存区输出结果（输出书名的x坐标应该是x+0.2，后面根据上面标题依此类推）*/
		/*此处补充界面输出的代码*/ 
		drawLabel(x+0.2,y+hx-0.5-0.25-d*count,bookinfoBooknameSwap);
		drawLabel(x+1.3,y+hx-0.5-0.25-d*count,bookinfoIdSwap);
		drawLabel(x+2.4,y+hx-0.5-0.25-d*count,bookinfoAuthorsSwap);
		drawLabel(x+3.6,y+hx-0.5-0.25-d*count,bookinfoKeywordsSwap);
		drawLabel(x+4.8,y+hx-0.5-0.25-d*count,bookinfoCategorySwap);
		drawLabel(x+6,y+hx-0.5-0.25-d*count,bookinfoPublisherSwap);
		drawLabel(x+7.2,y+hx-0.5-0.25-d*count,bookinfoPubtimeSwap);
		drawLabel(x+8.4,y+hx-0.5-0.25-d*count,bookinfoQuantitySwap);
		count++;
		ptr=ptr->next; 
	}
	drawLabel(x+0.3,y+0.25,"共");
	//这里向界面输出有count条结果 
	char* countfinal;
	sprintf(countfinal, "%d", count);
	drawLabel(x+0.5,y+0.25,countfinal);
	drawLabel(x+0.7,y+0.25,"条相关结果");	
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=Searchchoice_pop; 
		/*清除缓存区*/
		bookinfoBooknameSwap[0]='\0';
		bookinfoIdSwap[0]='\0';
		bookinfoAuthorsSwap[0]='\0';
		bookinfoKeywordsSwap[0]='\0';
		bookinfoCategorySwap[0]='\0';
		bookinfoPublisherSwap[0]='\0';
		bookinfoPubtimeSwap[0]='\0';
		bookinfoQuantitySwap[0]='\0';
	}		
} 
/*菜单服务器连接*/ 
void ConnectServer()
{
	double x,y,w,hx,hs;
	x=3;
	y=3;
	w=3.5;
	hx=1;
	hs=0.3;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);	
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);	
	SetPenColor("Black");
	drawRectangle(x,y+hx,w,hs,0);	
	MovePen(x+0.1,y+hx+0.1);
	SetPenColor("Black");
	DrawTextString("输入服务器地址：");
	textbox(GenUIID(0),x+0.2,y+0.5,w-0.2*2,0.4,SERVER_ADDRESS, sizeof(SERVER_ADDRESS));
	if(button(GenUIID(0),x+0.2+w-0.2*2-0.6,y+0.1,0.6,0.27,"确认")){
	IfFlag = 0;
	MouseAction = 0; 
	}
}
/*新增图书信息*/ 
void NewTheBook()
{
	double x,y,d,w,h;
	x=3.25;
	y=4.75;
	d=0.5;
	w=2;
	h=0.25;
	SetPointSize(14);
	SetPenColor("Black");
	drawLabel(x,y,"书 名 ");
	drawLabel(x,y-d,"作 者 ");
	drawLabel(x,y-2*d,"关键词 ");
	drawLabel(x,y-3*d,"类 别 ");
	drawLabel(x,y-4*d,"出版社 ");
	drawLabel(x,y-5*d,"出版日期");
	drawLabel(x,y-6*d,"库存数量"); 
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.07,w,h,bookinfoBooknameSwap,sizeof(bookinfoBooknameSwap));
	textbox(GenUIID(0),x+1,y-0.07-d,w,h,bookinfoAuthorsSwap,sizeof(bookinfoAuthorsSwap));
	textbox(GenUIID(0),x+1,y-0.07-d*2,w,h,bookinfoKeywordsSwap,sizeof(bookinfoKeywordsSwap));
	textbox(GenUIID(0),x+1,y-0.07-d*3,w,h,bookinfoCategorySwap,sizeof(bookinfoCategorySwap));
	textbox(GenUIID(0),x+1,y-0.07-d*4,w,h,bookinfoPublisherSwap,sizeof(bookinfoPublisherSwap));
	textbox(GenUIID(0),x+1,y-0.07-d*5,w,h,bookinfoPubtimeSwap,sizeof(bookinfoPubtimeSwap));
	textbox(GenUIID(0),x+1,y-0.07-d*6,w,h,bookinfoQuantitySwap,sizeof(bookinfoQuantitySwap));
	if(button(GenUIID(0),x+1.4,y-d*7-0.2,1,0.35,"保 存")){ 
		//后端这里写保存的函数，将上面的id，bookname，keywords，authors，category，publisher，pubtime，quantity保存到后端的数据层 
		//新建成功则StatusBar=NBSuccess,失败则NBFail 
		BOOKS *input=NULL;
		input=(BOOKS*)calloc(1,sizeof(BOOKS));
		input->id=bookinfoIdSwap;
		input->bookname=bookinfoBooknameSwap;
		input->keywords=bookinfoKeywordsSwap;
		input->authors=bookinfoAuthorsSwap;
		input->publisher=bookinfoPublisherSwap;
		input->pubtime=bookinfoPubtimeSwap;
		input->category=bookinfoCategorySwap;
		input->quantity=atoi(bookinfoQuantitySwap);
		int result;
		result=AU_createNewBook(DATABASE,input,UserInfo);
		input=NULL;             //保存完后指针重新置空 
		if(result==AUTHORIZE_FAILED){    //管理员身份认证失败 
			STATUS=NBFail; 
		}
		else if(result==PERMISSION_DENIED){   //权限不足 
			STATUS=NBFail;
		}
		else if(result==SUCCESS){      //创建成功 
			STATUS=NBSuccess;
		}
		/*清除缓存区*/
		bookinfoBooknameSwap[0]='\0';
		bookinfoIdSwap[0]='\0';
		bookinfoAuthorsSwap[0]='\0';
		bookinfoKeywordsSwap[0]='\0';
		bookinfoCategorySwap[0]='\0';
		bookinfoPublisherSwap[0]='\0';
		bookinfoPubtimeSwap[0]='\0';
		bookinfoQuantitySwap[0]='\0';
	}
}
/*复制图书信息*/ 
void CopyTheBook()
{
	double x,y,d,w,h;
	x=3.25;
	y=3.5;
	d=0.6;
	w=2;
	h=0.35;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y-0.3,"书 号");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-d*2,1,0.35,"复 制")){
		//后端查找与输入的书号一致的信息，复制, 书号改变
		BOOKS *input=NULL;
		input=getBookInfo(DATABASE,bookinfoIdSwap); 
		int result;
		result=AU_createNewBook(DATABASE,input,UserInfo);
		input=NULL;             //保存完后指针重新置空 
		if(result==AUTHORIZE_FAILED){    //管理员身份认证失败 
			STATUS=AuthorizeFail; 
		}
		else if(result==PERMISSION_DENIED){   //权限不足 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){      //复制成功 
			STATUS=CBSuccess;
		}
		/*清除缓存区*/
		bookinfoIdSwap[0]='\0';
	}
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"＊请输入您所要复制的书籍信息的书号");
}
/*精确搜索功能*/ 
void SearchSpecificBook()
{
	double x,y,d,w,h;
	x=3.25;
	y=3.5;
	d=0.6;
	w=2;
	h=0.35;
	SetPointSize(20);
	drawLabel(x,y-0.3,"书 号");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-d*2,1,0.35,"查 询")){
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);//后端查找与输入的书号一致的信息
		strcpy(bookinfoBooknameSwap,BookInfo->bookname);
		strcpy(bookinfoAuthorsSwap,BookInfo->authors);
		strcpy(bookinfoKeywordsSwap,BookInfo->keywords);
		strcpy(bookinfoPublisherSwap,BookInfo->publisher);
		strcpy(bookinfoPubtimeSwap,BookInfo->pubtime);
		strcpy(bookinfoCategorySwap,BookInfo->category);
		strcpy(bookinfoRegtimeSwap,BookInfo->regtime);
		sprintf(bookinfoQuantitySwap,"%d",BookInfo->quantity);
		sprintf(bookinfoIsborrowedSwap,"%d",BookInfo->isborrowed);
		IfFlag=Book_SEARCH_pop;//通过SearchBookpop显示 
	}
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"＊请输入您想要查询的书号");
} 
/*精确搜索结果弹窗*/ 
void SearchBookpop()
{
	double x,y,w,hs,hx,d;
	x=2.1;
	y=1.0;
	w=6;
	hs=0.4;
	hx=3.5;
	d=0.5;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"书籍信息"); 
	drawLabel(x+0.5,y+3,"书 号");drawLabel(x+1.3,y+3,bookinfoIdSwap);
	drawLabel(x+3.5,y+3,"书 名");drawLabel(x+4.3,y+3,bookinfoBooknameSwap);
	drawLabel(x+0.5,y+3-d,"作 者");drawLabel(x+1.3,y+3-d,bookinfoAuthorsSwap);
	drawLabel(x+3.5,y+3-d,"类 别");drawLabel(x+4.3,y+3-d,bookinfoCategorySwap);
	drawLabel(x+0.5,y+3-d*2,"关键词");drawLabel(x+1.3,y+3-d*2,bookinfoKeywordsSwap);
	drawLabel(x+3.5,y+3-d*2,"出版社");drawLabel(x+4.3,y+3-d*2,bookinfoPublisherSwap);
	drawLabel(x+0.5,y+3-d*3,"出版日期");drawLabel(x+1.3,y+3-d*3,bookinfoPubtimeSwap);
	drawLabel(x+3.5,y+3-d*3,"入库时间");drawLabel(x+4.3,y+3-d*3,bookinfoRegtimeSwap);
	drawLabel(x+0.5,y+3-d*4,"库存数量");drawLabel(x+1.3,y+3-d*4,bookinfoQuantitySwap);
	drawLabel(x+3.5,y+3-d*4,"出借数量");drawLabel(x+4.3,y+3-d*4,bookinfoIsborrowedSwap);
	if(button(GenUIID(0),x+2.6,y+0.4,0.8,0.25,"完  成")){
		IfFlag=Book_SEARCH;
		/*清除缓存区*/
		bookinfoBooknameSwap[0]='\0';
		bookinfoIdSwap[0]='\0';
		bookinfoAuthorsSwap[0]='\0';
		bookinfoKeywordsSwap[0]='\0';
		bookinfoCategorySwap[0]='\0';
		bookinfoPublisherSwap[0]='\0';
		bookinfoPubtimeSwap[0]='\0';
		bookinfoRegtimeSwap[0]='\0';
		bookinfoQuantitySwap[0]='\0';
		bookinfoIsborrowedSwap[0]='\0';
	}
} 
/*修改图书信息*/ 
void ModifyTheBook()
{
	double x,y,d,w,h;
	x=3.25;
	y=3.5;
	d=0.6;
	w=2;
	h=0.35;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y-0.3,"书 号");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-d*2,1,0.35,"修 改")){
		IfFlag=Book_MODIFY_pop; 
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);//根据用户输入的书号，在链表中找到它，并将该图书信息结构的值赋给全局变量BookInfo 
	}	 
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"＊请输入您所要修改的书籍信息的书号");
}
/*修改图书信息弹窗*/ 
void ModifyBookpop()
{
	double x,y,w,hs,hx,d;
	x=2.1;
	y=1.0;
	w=6;
	hs=0.4;
	hx=3.5;
	d=0.5;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"修改书籍信息"); 
	drawLabel(x+0.5,y+3,"书 号");drawLabel(x+1.3,y+3,bookinfoIdSwap);
	drawLabel(x+3.5,y+3,"书 名");textbox(GenUIID(0),x+4.3,y+3-0.07,1.2,0.25,bookinfoBooknameSwap,sizeof(bookinfoBooknameSwap));
	drawLabel(x+0.5,y+3-d,"作 者");textbox(GenUIID(0),x+1.3,y+3-0.07-d,1.2,0.25,bookinfoAuthorsSwap,sizeof(bookinfoAuthorsSwap));
	drawLabel(x+3.5,y+3-d,"类 别");textbox(GenUIID(0),x+4.3,y+3-0.07-d,1.2,0.25,bookinfoCategorySwap,sizeof(bookinfoCategorySwap));
	drawLabel(x+0.5,y+3-d*2,"关键词");textbox(GenUIID(0),x+1.3,y+3-0.07-d*2,1.2,0.25,bookinfoKeywordsSwap,sizeof(bookinfoKeywordsSwap));
	drawLabel(x+3.5,y+3-d*2,"出版社");textbox(GenUIID(0),x+4.3,y+3-0.07-d*2,1.2,0.25,bookinfoPublisherSwap,sizeof(bookinfoPublisherSwap));
	drawLabel(x+0.5,y+3-d*3,"出版日期");textbox(GenUIID(0),x+1.3,y+3-0.07-d*3,1.2,0.25,bookinfoPubtimeSwap,sizeof(bookinfoPubtimeSwap));
	drawLabel(x+3.5,y+3-d*3,"入库时间");drawLabel(x+4.3,y+3-d*3,bookinfoRegtimeSwap);
	drawLabel(x+0.5,y+3-d*4,"库存数量");textbox(GenUIID(0),x+1.3,y+3-0.07-d*4,1.2,0.25,bookinfoQuantitySwap,sizeof(bookinfoQuantitySwap));
	drawLabel(x+3.5,y+3-d*4,"出借数量");textbox(GenUIID(0),x+4.3,y+3-0.07-d*4,1.2,0.25,bookinfoIsborrowedSwap,sizeof(bookinfoIsborrowedSwap));
	/*一开始就显示修改前的信息*/
	strcpy(bookinfoBooknameSwap,BookInfo->bookname);
	strcpy(bookinfoAuthorsSwap,BookInfo->authors);
	strcpy(bookinfoCategorySwap,BookInfo->category);
	strcpy(bookinfoKeywordsSwap,BookInfo->keywords);
	strcpy(bookinfoPublisherSwap,BookInfo->publisher);
	strcpy(bookinfoPubtimeSwap,BookInfo->pubtime);
	sprintf(bookinfoQuantitySwap,"%d",BookInfo->quantity);
	sprintf(bookinfoIsborrowedSwap,"%d",BookInfo->isborrowed);
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=Book_MODIFY;
		/*清除缓存区*/
		bookinfoBooknameSwap[0]='\0';
		bookinfoIdSwap[0]='\0';
		bookinfoAuthorsSwap[0]='\0';
		bookinfoKeywordsSwap[0]='\0';
		bookinfoCategorySwap[0]='\0';
		bookinfoPublisherSwap[0]='\0';
		bookinfoPubtimeSwap[0]='\0';
		bookinfoRegtimeSwap[0]='\0';
		bookinfoQuantitySwap[0]='\0';
		bookinfoIsborrowedSwap[0]='\0';
	}
	if(button(GenUIID(0),x+2.6,y+0.4,0.8,0.25,"确  认")){
		//后端：修改书本信息 ，此处界面一开始应该在文本框中显示未修改前的信息，由上一步修改按钮给BookInfo赋值达到目的，修改后BookInfo值清零 
		/*把修改后的信息从缓存区赋值给BookInfo*/
		strcpy(BookInfo->bookname,bookinfoBooknameSwap);
		strcpy(BookInfo->authors,bookinfoAuthorsSwap);
		strcpy(BookInfo->category,bookinfoCategorySwap);
		strcpy(BookInfo->keywords,bookinfoKeywordsSwap);
		strcpy(BookInfo->publisher,bookinfoPublisherSwap);
		strcpy(BookInfo->pubtime,bookinfoPubtimeSwap);
		BookInfo->quantity=atoi(bookinfoQuantitySwap);
		BookInfo->isborrowed=atoi(bookinfoIsborrowedSwap);
		int result;      //储存修改操作结果
		result=AU_bookModify(DATABASE,UPDATEMODE,BookInfo,UserInfo);
		if(result==AUTHORIZE_FAILED){    //管理员身份认证失败 
			STATUS=AuthorizeFail; 
		}
		else if(result==PERMISSION_DENIED){   //权限不足 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){      //修改成功 
			STATUS=MBSuccess;
		}
		/*清除缓存区*/
		bookinfoBooknameSwap[0]='\0';
		bookinfoIdSwap[0]='\0';
		bookinfoAuthorsSwap[0]='\0';
		bookinfoKeywordsSwap[0]='\0';
		bookinfoCategorySwap[0]='\0';
		bookinfoPublisherSwap[0]='\0';
		bookinfoPubtimeSwap[0]='\0';
		bookinfoRegtimeSwap[0]='\0';
		bookinfoQuantitySwap[0]='\0';
		bookinfoIsborrowedSwap[0]='\0';
	}
}
/*删除图书信息*/ 
void DeleteTheBook()
{
	double x,y,d,w,h;
	x=3.25;
	y=3.5;
	d=0.6;
	w=2;
	h=0.35;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y-0.3,"书 号");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-d*2,1,0.35,"删 除")){
		/*后端查找与输入的书号一致的信息，并将其删除 */
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);
		int result;      //储存删除操作结果
		result=AU_bookModify(DATABASE,DELETEMODE,BookInfo,UserInfo);
		if(result==AUTHORIZE_FAILED){    //管理员身份认证失败 
			STATUS=AuthorizeFail; 
		}
		else if(result==PERMISSION_DENIED){   //权限不足 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){      //删除成功 
			STATUS=MBSuccess;
		}
		/*清除缓存区*/
		bookinfoIdSwap[0]='\0';
	}	 
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"＊请输入您所要删除书籍的书号");
}
/*书籍统计功能*/ 
void CountTheBook()
{
	double x,y,w,hs,hx,d;
	static char *TotalBookAmount = NULL;
	static char *TotalBorrowAmount = NULL;
	if(pIfFlag != IfFlag)
	{
		if(TotalBookAmount != NULL) free(TotalBookAmount);
		if(TotalBorrowAmount != NULL) free(TotalBorrowAmount);
		TotalBookAmount=(char*)calloc(SIZEOFARRAY,sizeof(char));
		TotalBorrowAmount=(char*)calloc(SIZEOFARRAY,sizeof(char));
		sprintf(TotalBookAmount,"%d",CountTotalBook(DATABASE));//藏书总量 
		sprintf(TotalBorrowAmount,"%d",CountTotalBorrowed(DATABASE));//被借总量 
	}
	x=2.5;
	y=0.5;
	w=5;
	hs=0.4;
	hx=4.5;
	d=0.22;//课程+成绩一行的高度，例如输出时第一行y+hx-0.6-d,第二行就是y+hx-0.6-2*d，按照类别 藏书量 借阅次数输出 
	SetPointSize(1);
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"统计结果");
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0; 
		MouseAction=0;   //恢复初始状态 
	}
	SetPenColor("MidnightBlue");
	drawRectangle(x+0.1,y+0.1,w-0.2,hx-0.2,0);
	drawRectangle(x+0.1,y+0.1,w-0.2,0.4,0);
	drawLabel(x+0.5,y+hx-0.5,"书籍类别");
	drawLabel(x+2.3,y+hx-0.5,"藏书量");
	drawLabel(x+3.6,y+hx-0.5,"借阅次数");
	drawLabel(x+0.3,y+0.25,"总藏书量：");
	drawLabel(x+2.5,y+0.25,"总借阅量："); 
	BOOKAMOUNT *ptr;          //用于遍历结果链表 
	static BOOKAMOUNT *head = NULL;         //用于标记头结点 
	if(pIfFlag != IfFlag)
	{
		if(head != NULL) freeBookAmount(head);
		head=BorrowedInfo(DATABASE);
	}
	ptr=head;
    int count=1;
	while(ptr!=NULL){      //逐条输出查找结果 
		/*将当前结点处单个图书种类的借阅信息存入缓存区*/ 
		strcpy(amountCategorySwap,ptr->category);
		sprintf(amountTotalbooksSwap,"%d",ptr->TotalBooks);
		sprintf(amountTotalborrowedSwap,"%d",ptr->TotalBorrowed);
		/*从缓存区输出结果*/
		/*此处补充界面输出的代码*/ /*按照类别 藏书量 借阅次数输出*/
        drawLabel(x+0.3,y+hx-0.6-d*count,amountCategorySwap);
        drawLabel(x+2.1,y+hx-0.6-d*count,amountTotalbooksSwap);
        drawLabel(x+3.4,y+hx-0.6-d*count,amountTotalborrowedSwap);
		ptr=ptr->next; 
        count++;
	}
	SetPenColor("Black");
	drawLabel(x+1.1,y+0.25,TotalBookAmount);
	drawLabel(x+3.3,y+0.25,TotalBorrowAmount);
	/*清理缓存区*/
	amountCategorySwap[0]='\0';
	amountTotalbooksSwap[0]='\0';
	amountTotalborrowedSwap[0]='\0';
	pIfFlag = IfFlag;
}

/*借阅书籍*/ 
void BorrowTheBook()
{
	double x,y,d,w,h;
	x=3;
	y=3.5;
	d=0.8;
	w=2.3;
	h=0.4;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y-0.3,"书 号");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"借 阅")){
		/*借阅成功StatusBar=BorrowSuccess,失败BorrowFail(无库存）*/
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);
		int result;      //储存借阅操作结果
		result=borrowBook(DATABASE,BookInfo,UserInfo);
		if(result==AUTHORIZE_FAILED){    //密码错误 
			STATUS=PasswordError; 
		}
		else if(result==NO_BOOK_LEFT){   //图书无库存 
			STATUS=BookUnavailable;
		}
		else if(result==SUCCESS){      //借阅成功 
			STATUS=BorrowSuccess;
		}
		BookInfo=NULL;     //操作完成后置NULL 
		/*清除缓存区*/
		bookinfoIdSwap[0]='\0';
	}
}
/*归还书籍*/ 
void ReturnTheBook(){
	double x,y,d,w,h;
	x=3;
	y=3.5;
	d=0.8;
	w=2.3;
	h=0.4;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y-0.3,"书 号");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"还 书")){
		/*后端还书代码，BookInfo，BOOKSTATE的更新*/
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);
		int result;      //储存归还操作结果
		result=returnBook(DATABASE,BookInfo,UserInfo);
		if(result==AUTHORIZE_FAILED){    //密码错误
			STATUS=PasswordError; 
		}
		else if(result==SUCCESS){      //归还成功 
			STATUS=ReturnSuccess;
		}
		BookInfo=NULL;    //操作成功以后置NULL 
		/*清除缓存区*/
		bookinfoIdSwap[0]='\0';
	}
}
/*用户审核*/ 
void CheckUserStatus()
{
	double x,y,d,w,h;
	x=4.4;
	y=2.85;
	d=0.8;
	w=2.3;
	h=0.4;
	SetPenColor("Black");
	drawLabel(x,y,"当前是管理员状态");
}
/*搜索用户信息*/ 
void SearchUserInfo()
{
	double x,y,d,w,h;
	x=3;
	y=3.5;
	d=0.8;
	w=2.3;
	h=0.4;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y,"ID");
	drawLabel(x,y-d,"用户名");
	SetPointSize(1);
	textbox(GenUIID(0),x+1.3,y-0.1,w,h,userinfoIdSwap,sizeof(userinfoIdSwap)); 
	textbox(GenUIID(0),x+1.3,y-0.1-d,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"搜 索")){
		IfFlag=User_SEARCH_pop; 
		/*根据输入的ID和用户名查询对应的UserInfo，在用户搜索的两个pop界面里面都用同样的UserInfo*/
		if(userinfoUsernameSwap!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
			UserResult=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
		if(UserResult!=NULL&&UserResult->id!=-1){
			if(UserResult->id==atoi(userinfoIdSwap)){   //如果输入的用户名与id一致对应则继续 
				STATUS=SearchUserSuccess;          //搜索成功 
				strcpy(userinfoModeSwap,UserResult->mode);
				strcpy(userinfoGenderSwap,UserResult->gender);
				strcpy(userinfoDepartmentSwap,UserResult->department);
				strcpy(userinfoRegtimeSwap,UserResult->regtime);
				sprintf(userinfoBorrowedbooksSwap,"%d",UserResult->borrowedbooks);
			}
			else{     //用户名和id不匹配 
				STATUS=UnmatchedUIDName; 
			}
			if(UserResult!=NULL){    //用户不存在 
				STATUS=UserNotfind;
			}
		}
		else{       //身份认证失败 
			STATUS=AuthorizeFail; 
		} 
	}
	SetPenColor("Gray");
	drawLabel(x,y-1.7-0.25,"＊请输入您所要查询的用户名或ID");
}
/*搜索用户信息结果弹窗*/ 
void SearchUserInfopop(){
	double x,y,w,hs,hx,d;
	x=2.1;
	y=1.5;
	w=6;
	hs=0.4;
	hx=3;
	d=0.5;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"用户信息——");drawLabel(x+1.1,y+hx+0.15,userinfoModeSwap); 
	drawLabel(x+0.5,y+1.9,"ID");drawLabel(x+1.3,y+1.9,userinfoIdSwap);
	drawLabel(x+3.5,y+1.9,"用户名");drawLabel(x+4.3,y+1.9,userinfoUsernameSwap);
	drawLabel(x+0.5,y+1.9-d,"性 别");drawLabel(x+1.3,y+1.9-d,userinfoGenderSwap);
	drawLabel(x+3.5,y+1.9-d,"单 位");drawLabel(x+4.3,y+1.9-d,userinfoDepartmentSwap);
	drawLabel(x+0.5,y+1.9-d*2,"已借数量");drawLabel(x+1.3,y+1.9-2*d,userinfoBorrowedbooksSwap);
	drawLabel(x+3.5,y+1.9-2*d,"注册时间");drawLabel(x+4.3,y+1.9-2*d,userinfoRegtimeSwap);
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=User_SEARCH;
		/*清除缓存区*/
		userinfoIdSwap[0]='\0';
		userinfoUsernameSwap[0]='\0';
		userinfoGenderSwap[0]='\0';
		userinfoDepartmentSwap[0]='\0';
		userinfoModeSwap[0]='\0';
		userinfoBorrowedbooksSwap[0]='\0';
		userinfoRegtimeSwap[0]='\0';
	}
	if(button(GenUIID(0),x+1.0,y+0.3,1.2,0.25,"用户借阅信息")){
		IfFlag=User_COUNTBorrow_pop;//后端调用用户借阅历史，显示在弹出的窗口中 
	} 
	if(button(GenUIID(0),x+4.25,y+0.3,0.65,0.25,"完 成")){
		IfFlag=User_SEARCH;
		/*清除缓存区*/
		userinfoIdSwap[0]='\0';
		userinfoUsernameSwap[0]='\0';
		userinfoGenderSwap[0]='\0';
		userinfoDepartmentSwap[0]='\0';
		userinfoModeSwap[0]='\0';
		userinfoBorrowedbooksSwap[0]='\0';
		userinfoRegtimeSwap[0]='\0';
	} 	
}
/*用户借阅信息*/ 
void CountBorrowHistory(){
	double x,y,w,hs,hx,d;
	x=2;
	y=0.5;
	w=6;
	hs=0.4;
	hx=4.5;
	d=0.22;//书名+归还时间一行的高度，例如输出时第一行y+hx-0.6-d,第二行就是y+hx-0.6-2*d, 显示时还没还的书在上面，然后按照借阅日期排序 
	SetPointSize(1);
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"借阅历史");
	drawLabel(x+0.1,y+hx-0.2,"ID："); 
	drawLabel(x+0.1+0.2,y+hx-0.2,userinfoIdSwap);
	drawLabel(x+2,y+hx-0.2,"用户名：");
	drawLabel(x+2.8,y+hx-0.2,userinfoUsernameSwap);
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=User_SEARCH_pop;
	}
	SetPenColor("MidnightBlue");
	drawRectangle(x+0.1,y+0.1,w-0.2,hx-0.4,0);
	drawRectangle(x+0.1,y+0.1,w-0.2,0.4,0);
	drawLabel(x+0.5,y+hx-0.5,"书号");
	drawLabel(x+2.8,y+hx-0.5,"借阅时间");
	drawLabel(x+5.1,y+hx-0.5,"归还时间");//如果还没还就显示“未归还 ” 
	BOOKSTATE *ptr;          //用于遍历结果链表 
	int count=0;         //用于计数 
	BookCurrentState=AU_getBookRecordsByUser(DATABASE,userinfoUsernameSwap,UserInfo); 
	ptr=BookCurrentState;
	if(ptr!=NULL){
		while(ptr!=NULL){      //逐条输出借阅历史
			/*将当前结点处的借阅历史存入缓存区*/ 
			strcpy(stateinfoBookidSwap,ptr->bookid);
			strcpy(stateinfoBorrowdateSwap,ptr->borrowdate);
			strcpy(stateinfoDuedataSwap,ptr->duedate);
			/*从缓存区输出结果*/
			/*此处补充界面输出的代码*/ 
			drawLabel(x+0.3,y+hx-0.5-0.22-d*count,stateinfoBookidSwap);
			drawLabel(x+2.6,y+hx-0.5-0.22-d*count,stateinfoBorrowdateSwap);
			drawLabel(x+4.9,y+hx-0.5-0.22-d*count,stateinfoDuedataSwap);
			count++;
			ptr=ptr->next; 
		}
	}
	drawLabel(x+0.3,y+0.25,"未还数量：");
	USERS *temp=NULL;        //储存待查的用户的信息结点 
	if(UserInfo!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
		temp=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
	if(temp!=NULL&&temp->id!=-1){
		sprintf(userinfoBorrowedbooksSwap,"%d",temp->borrowedbooks);
		drawLabel(x+1.1,y+0.25,userinfoBorrowedbooksSwap);        //显示需查询的用户的图书未还数量 
		if(temp!=NULL)freeSingleUser(temp);       //使用完毕，若不是NULL则释放内存 
	}
	SetPenColor("Black");
}
/*修改用户信息*/ 
void ModifyUserInfo()
{
	double x,y,d,w,h;
	x=3;
	y=3.5;
	d=0.8;
	w=2.3;
	h=0.4;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y,"ID");
	drawLabel(x,y-d,"用户名");
	SetPointSize(1);
	textbox(GenUIID(0),x+1.3,y-0.1,w,h,userinfoIdSwap,sizeof(userinfoIdSwap)); 
	textbox(GenUIID(0),x+1.3,y-0.1-d,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"修 改")){
		IfFlag=User_MODIFY_pop; 
		/*后端：根据输入的ID和用户名查询对应的UserInfo*/
		if(userinfoUsernameSwap!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
			UserResult=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
		if(UserResult!=NULL&&UserResult->id!=-1){
			if(UserResult->id==atoi(userinfoIdSwap)){   //如果输入的用户名与id一致对应则继续 
				STATUS=SearchUserSuccess;          //搜索成功 
				strcpy(userinfoModeSwap,UserResult->mode);
				strcpy(userinfoGenderSwap,UserResult->gender);
				strcpy(userinfoDepartmentSwap,UserResult->department);
				sprintf(userinfoBorrowedbooksSwap,"%d",UserResult->borrowedbooks);
			}
			else{     //用户名和id不匹配 
				STATUS=UnmatchedUIDName; 
			}
			if(UserResult!=NULL){    //用户不存在 
				STATUS=UserNotfind;
			}
		}
		else{       //身份认证失败 
			STATUS=AuthorizeFail; 
		} 
	}
	SetPenColor("Gray");
	drawLabel(x,y-1.7-0.25,"＊请输入您所要修改的用户名或ID");
}
/*修改用户信息编辑窗口*/ 
void ModifyUserInfoPop(){
	double x,y,w,hs,hx,d;
	x=3.6;
	y=0.8;
	w=3;
	hs=0.4;
	hx=4.0;
	d=0.5;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"修 改"); 
	drawLabel(x+0.5,y+0.9+d*5,"用户名");//默认不可重复 
	drawLabel(x+0.5,y+0.9+d*4,"密 码");
	drawLabel(x+0.5,y+0.9+d*3,"性 别");
	drawLabel(x+0.5,y+0.9+2*d,"单 位");
	drawLabel(x+0.5,y+0.9+1*d,"权 限");
	SetPenColor("Gray");
	drawLabel(x+0.2,y+0.9+0.15,"*权限填写“学生”或者“管理员”"); 
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*5,1.2,0.25,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*4,1.2,0.25,userinfoPasswordsSwap,sizeof(userinfoPasswordsSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*3,1.2,0.25,userinfoGenderSwap,sizeof(userinfoGenderSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*2,1.2,0.25,userinfoDepartmentSwap,sizeof(userinfoDepartmentSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*1,1.2,0.25,userinfoModeSwap,sizeof(userinfoModeSwap));
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=User_MODIFY;//点右上角 ×关闭弹窗 
		/*清除缓存区*/
		userinfoIdSwap[0]='\0';
		userinfoUsernameSwap[0]='\0';
		userinfoGenderSwap[0]='\0';
		userinfoDepartmentSwap[0]='\0';
		userinfoModeSwap[0]='\0';
		userinfoBorrowedbooksSwap[0]='\0';
		userinfoRegtimeSwap[0]='\0';
	}
	if(button(GenUIID(0),x+1.25,y+0.3,0.65,0.25,"确认修改")){
		/*后端：更新修改后的用户信息*/ 
		int result;       //用于储存修改操作的结果 
		result=AU_userModify(DATABASE,UPDATEMODE,UserResult,UserInfo);
		if(result==AUTHORIZE_FAILED){    //密码错误 
			STATUS=PasswordError;
		} 
		else if(result==PERMISSION_DENIED){   //权限不足 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){    //修改成功 
			STATUS=ModifyUserSuccess; 
		}
		/*清除缓存区*/
		userinfoIdSwap[0]='\0';
		userinfoUsernameSwap[0]='\0';
		userinfoGenderSwap[0]='\0';
		userinfoDepartmentSwap[0]='\0';
		userinfoModeSwap[0]='\0';
		userinfoBorrowedbooksSwap[0]='\0';
		userinfoRegtimeSwap[0]='\0';
		/*change end*/
	}
} 
/*删除用户信息*/ 
void DeleteUserInfo()
{
	double x,y,d,w,h;
	x=3;
	y=3.5;
	d=0.8;
	w=2.3;
	h=0.4;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y,"ID");
	drawLabel(x,y-d,"用户名");
	SetPointSize(1);
	textbox(GenUIID(0),x+1.3,y-0.1,w,h,userinfoIdSwap,sizeof(userinfoIdSwap)); 
	textbox(GenUIID(0),x+1.3,y-0.1-d,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"删 除")){
		/*后端查找与输入的ID和用户名一致的信息，并删除*/
		if(userinfoUsernameSwap!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
			UserResult=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
		if(UserResult!=NULL&&UserResult->id!=-1){
			if(UserResult->id==atoi(userinfoIdSwap)){   //如果输入的用户名与id一致对应则继续 
				STATUS=SearchUserSuccess;          //搜索成功 
			}
			else{     //用户名和id不匹配 
				STATUS=UnmatchedUIDName; 
			}
			if(UserResult!=NULL){    //用户不存在 
				STATUS=UserNotfind;
			}
		}
		else{       //身份认证失败 
			STATUS=AuthorizeFail; 
		} 
		int result;       //用于储存修改操作的结果 
		result=AU_userModify(DATABASE,DELETEMODE,UserResult,UserInfo);
		if(result==AUTHORIZE_FAILED){    //密码错误 
			STATUS=PasswordError;
		} 
		else if(result==PERMISSION_DENIED){   //权限不足 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){    //修改成功 
			STATUS=DeleteUserSuccess; 
		}
		/*清除缓存区*/
		userinfoIdSwap[0]='\0';
		userinfoUsernameSwap[0]='\0';
		userinfoGenderSwap[0]='\0';
		userinfoDepartmentSwap[0]='\0';
		userinfoModeSwap[0]='\0';
		userinfoBorrowedbooksSwap[0]='\0';
		userinfoRegtimeSwap[0]='\0';
	}
	SetPenColor("Gray");
	drawLabel(x,y-1.7-0.25,"＊请输入您所要删除的用户的ID和用户名");
}
/*用户排序*/
void UserInfoRank()
{
	double x,y,w,hs,hx,d;
	x=2;
	y=0.5;
	w=6;
	hs=0.4;
	hx=4.5;
	d=0.22;//输出时第一行y+hx-0.6-d,第二行就是y+hx-0.6-2*d 
	SetPointSize(1);
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"用户信息");
	drawLabel(x+0.1,y+hx-0.2,"排序方式："); 
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0;
		MouseAction=0; 
	}
	if(button(GenUIID(0),x+0.9,y+hx-0.26,0.52,0.23,"按ID")){
		;//按ID排序 
	} 
	if(button(GenUIID(0),x+1.5,y+hx-0.26,0.52,0.23,"按姓名")){
		;//按排序 
	} 
	if(button(GenUIID(0),x+2.1,y+hx-0.26,0.52,0.23,"按部门")){
		;//按工作单位排序 
	} 
	SetPenColor("MidnightBlue");
	drawRectangle(x+0.1,y+0.1,w-0.2,hx-0.4,0);
	drawLabel(x+0.5,y+hx-0.5,"ID");
	// drawLabel(x+0.2,y+hx-0.6-d*count,"ID");
	drawLabel(x+2.8,y+hx-0.5,"姓名");
	// drawLabel(x+0.2,y+hx-0.6-d*count,"姓名");
	drawLabel(x+4.7,y+0.25,"部门"); 
	// drawLabel(x+0.2,y+hx-0.6-d*count,"部门");
	SetPenColor("Black");
}
/*统计用户借阅数据*/ 
void CountUserInfo(){
	double x,y,d,w,h;
	x=3;
	y=3.5;
	d=0.8;
	w=2.3;
	h=0.4;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y,"ID");
	drawLabel(x,y-d,"用户名");
	SetPointSize(1);
	textbox(GenUIID(0),x+1.3,y-0.1,w,h,userinfoIdSwap,sizeof(userinfoIdSwap)); 
	textbox(GenUIID(0),x+1.3,y-0.1-d,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	if(button(GenUIID(0),x+0.9,y-1.7,2,0.35,"查看统计数据")){
		IfFlag=User_COUNT_pop; 
		/*后端：根据输入的ID和用户名查询对应的UserInfo*/
		if(userinfoUsernameSwap!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
			UserResult=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
		if(UserResult!=NULL&&UserResult->id!=-1){
			if(UserResult->id==atoi(userinfoIdSwap)){   //如果输入的用户名与id一致对应则继续 
				STATUS=SearchUserSuccess;          //搜索成功 
			}
			else{     //用户名和id不匹配 
				STATUS=UnmatchedUIDName; 
			}
			if(UserResult!=NULL){    //用户不存在 
				STATUS=UserNotfind;
			}
		}
		else{       //身份认证失败 
			STATUS=AuthorizeFail; 
		} 
	}
	SetPenColor("Gray");
	drawLabel(x,y-1.7-0.25,"＊请输入您所要统计的用户的ID和用户名");
}
/*用户借阅数据结果*/ 
void CountUserInfopop(){
	double x,y,w,hs,hx,d;
	char* TotalBorrowed;//借阅总数 
	char* MonthlyFrequency;//月频率 
	char* YearlyFrequency;//年频率
	x=2.1;
	y=0.6;
	w=6;
	hs=0.4;
	hx=4.4;
	d=0.5;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"用户统计 ID：");
	drawLabel(x+1.3,y+hx+0.15,userinfoIdSwap);
	drawLabel(x+2.5,y+hx+0.15,"用户名：");
	drawLabel(x+3.3,y+hx+0.15,userinfoUsernameSwap);
	drawLabel(x+0.5,y+3.9,"借阅总数：");drawLabel(x+1.5,y+3.9,TotalBorrowed);
	drawLabel(x+3.5,y+3.9,"未还数量：");drawLabel(x+4.5,y+3.9,userinfoBorrowedbooksSwap);
	drawLabel(x+0.5,y+3.9-d,"月借阅频率：");drawLabel(x+1.5,y+3.9-d,MonthlyFrequency);
	drawLabel(x+3.5,y+3.9-d,"年借阅频率：");drawLabel(x+4.5,y+3.9-d,YearlyFrequency);
	drawLabel(x+0.5,y+3.9-d*2,"借阅书籍类别排行：");
	drawLabel(x+2.8,y+3.9-d*2,"1.");//后端写上排序结果（只列举前三名），与序号相同，x坐标为x+3.0 
	drawLabel(x+2.8,y+3.9-d*3,"2.");
	drawLabel(x+2.8,y+3.9-d*4,"3.");
	if(button(GenUIID(0),x+2.7,y+0.3,0.65,0.25,"关 闭")){
		IfFlag=User_COUNT;//点击关闭弹窗 
	}	
}
/*用户个人中心*/ 
void DisplayUserInfo()
{
	double x,y,w,hs,hx,d;
	x=2.1;
	y=1.5;
	w=6;
	hs=0.4;
	hx=3;
	d=0.5;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"个人中心");drawLabel(x+1.1,y+hx+0.15,userinfoModeSwap); 
	drawLabel(x+0.5,y+1.9,"ID");drawLabel(x+1.3,y+1.9,userinfoIdSwap);
	drawLabel(x+3.5,y+1.9,"用户名");drawLabel(x+4.3,y+1.9,userinfoUsernameSwap);
	drawLabel(x+0.5,y+1.9-d,"性 别");drawLabel(x+1.3,y+1.9-d,userinfoGenderSwap);
	drawLabel(x+3.5,y+1.9-d,"单 位");drawLabel(x+4.3,y+1.9-d,userinfoDepartmentSwap);
	drawLabel(x+0.5,y+1.9-d*2,"已借数量");drawLabel(x+1.3,y+1.9-2*d,userinfoBorrowedbooksSwap);
	drawLabel(x+3.5,y+1.9-2*d,"注册时间");drawLabel(x+4.3,y+1.9-2*d,userinfoRegtimeSwap);
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0; 
		MouseAction=0;
	} 
	if(button(GenUIID(0),x+1.0,y+0.3,1.2,0.25,"用户借阅信息")){
		IfFlag=User_COUNTBorrow_pop;//后端调用用户借阅历史，显示在弹出的窗口中 
	} 
	if(button(GenUIID(0),x+4.25,y+0.3,0.65,0.25,"修 改")){
		IfFlag=User_MODIFY_pop;
	}
}
/*关于本软件*/ 
void AboutHelp()
{
	double x,y,w,hs,hx,d;
	x=3;
	y=0.6;
	w=4;
	hs=0.4;
	hx=4.4;
	d=0.5;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"关于本软件");
	drawLabel(4.2, y+1.6,"Version 0.99 Beta");
	drawLabel(4.6, y+1.6+d, "版本说明");
	drawLabel(4.4, y+1.6+2*d,"图书管理系统"); 
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0;
		MouseAction=0;//点右上角 ×关闭弹窗 
	}	
}
/*使用方法*/ 
void UsageHelp()
{
	double x,y,w,hs,hx,d;
	x=3;
	y=0.6;
	w=4;
	hs=0.4;
	hx=4.4;
	d=0.3;
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"使用方法");
	drawLabel(x+0.2,y+hx-0.6,"1. 若您正在使用自行编译的客户端，");
	drawLabel(x+0.5,y+hx-0.6-1*d,"请确保您的服务端(Server)已启动");
	drawLabel(x+0.2,y+hx-0.6-2*d,"2. 若在使用过程中出现未响应和闪退的情况，");
	drawLabel(x+0.5,y+hx-0.6-3*d,"请耐心等待或重启程序");
	drawLabel(x+0.2,y+hx-0.6-4*d,"3. 如有更多疑问请邮件联系xxxx@xx.xx");
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0;
		MouseAction=0;//点右上角 ×关闭弹窗 
	}
}
/*默认什么都不显示的界面*/ 
void DisplayNothing()
{
	;
} 

