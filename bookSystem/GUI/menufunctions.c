//���������������ı���������޸Ľ���ĵ��������⣬һ��ʼ���ǿհ�״̬�����޸ĵĵ������ڶ�Ҫ��ʾ��Ҫ�޸ĵ��Ǹ����� 
#include "SIMS.h" 
int MouseAction=0;
int WindowNum=WELCOMEWINDOW;//��ʼ����Ϊ��ӭ���� 
int IfFlag=0;//��ʼ��ʾ״̬ΪĬ��ֵ 
int STATUS=0;//��ʼ״̬��Ϊ�� 
int pIfFlag;
//ģ�������� 
BOOKS *BookResult=NULL;//�����ڴ���������صĽ��ָ�� 
USERS *UserResult=NULL;//�����ڴ���������صĽ��ָ��

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

/*����������֮��ѡ���Ǹ���ʲô��������*/ 
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
	drawLabel(x+0.2,y+0.5,"�������������ѡ��������ʽ��");
	if(BookResult!=NULL){
		freeAllBooks(BookResult);    //���BookResult��ָ����ڴ�ռ����ͷ�
		BookResult=NULL; 
	}
	if(button(GenUIID(0),x+0.2,y+0.1,0.6,0.25,"�����")){
		BookResult=getBookInfo(DATABASE,searchtext);     //���ز鵽���鼮��Ϣ��ȫ��ָ����� 
		IfFlag=Search_pop; //��˰�����Ų��ң��������֮����ת��Search_pop���� 
	}
	if(button(GenUIID(0),x+0.2+0.65,y+0.1,0.6,0.25,"������")){
		BookResult=searchbook_name(DATABASE,searchtext);     //���ز鵽���鼮��Ϣ��ȫ��ָ�����
		IfFlag=Search_pop; // ��˰����������ң��������֮����ת��Search_pop���� 
	}
	if(button(GenUIID(0),x+0.2+1.3,y+0.1,0.6,0.25,"������")){
		BookResult=searchbook_authors(DATABASE,searchtext);     //���ز鵽���鼮��Ϣ��ȫ��ָ�����
		IfFlag=Search_pop; //��˰������߲��ң��������֮����ת��Search_pop���� 
	}
	if(button(GenUIID(0),x+0.2+0.65*3,y+0.1,0.6,0.25,"���ؼ���")){
		BookResult=searchbook_keywords(DATABASE,searchtext);     //���ز鵽���鼮��Ϣ��ȫ��ָ�����
		IfFlag=Search_pop; //��˰��չؼ��ʲ��ң��������֮����ת��Search_pop���� 
	}	
}

/*Search_pop���棬������ʾ������� */ 
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
	drawLabel(x+0.1,y+hx+0.15,"�������");
	drawLabel(x+0.1,y+hx-0.2,"����ʽ��"); 
	if(button(GenUIID(0),x+0.9,y+hx-0.26,0.52,0.23,"������")){
		BookResult=rank_bookname(BookResult); //��˰����������򲢷��ظ�ȫ��ָ����� 
	} 
	if(button(GenUIID(0),x+1.5,y+hx-0.26,0.52,0.23,"�����")){
		BookResult=rank_id(BookResult); //��˰���������򲢷��ظ�ȫ��ָ����� 
	} 
	if(button(GenUIID(0),x+2.1,y+hx-0.26,0.86,0.23,"����һ����")){
		BookResult=rank_firstauthor(BookResult); //��˰��յ�һ�������򲢷��ظ�ȫ��ָ����� 
	}
	SetPenColor("MidnightBlue");
	drawRectangle(x+0.1,y+0.1,w-0.2,hx-0.4,0);
	drawRectangle(x+0.1,y+0.1,w-0.2,0.4,0);
	drawLabel(x+0.4,y+hx-0.5,"����");
	drawLabel(x+1.5,y+hx-0.5,"���");
	drawLabel(x+2.6,y+hx-0.5,"����");
	drawLabel(x+3.8,y+hx-0.5,"�ؼ���");
	drawLabel(x+5,y+hx-0.5,"���"); 
	drawLabel(x+6.2,y+hx-0.5,"������");
	drawLabel(x+7.4,y+hx-0.5,"����ʱ��");
	drawLabel(x+8.6,y+hx-0.5,"�������");
	BOOKS *ptr;          //���ڱ���������� 
	int count=0;         //���ڼ��� 
	ptr=BookResult;
	while(ptr!=NULL){      //����������ҽ�� 
		/*����ǰ��㴦���鼮��Ϣ���뻺����*/ 
		strcpy(bookinfoBooknameSwap,ptr->bookname);
		strcpy(bookinfoIdSwap,ptr->id);
		strcpy(bookinfoAuthorsSwap,ptr->authors);
		strcpy(bookinfoKeywordsSwap,ptr->keywords);
		strcpy(bookinfoCategorySwap,ptr->category);
		strcpy(bookinfoPublisherSwap,ptr->publisher);
		strcpy(bookinfoPubtimeSwap,ptr->pubtime);
		sprintf(bookinfoQuantitySwap,"%d",ptr->quantity);
		/*�ӻ����������������������x����Ӧ����x+0.2�����������������������ƣ�*/
		/*�˴������������Ĵ���*/ 
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
	drawLabel(x+0.3,y+0.25,"��");
	//��������������count����� 
	char* countfinal;
	sprintf(countfinal, "%d", count);
	drawLabel(x+0.5,y+0.25,countfinal);
	drawLabel(x+0.7,y+0.25,"����ؽ��");	
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=Searchchoice_pop; 
		/*���������*/
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
/*�˵�����������*/ 
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
	DrawTextString("�����������ַ��");
	textbox(GenUIID(0),x+0.2,y+0.5,w-0.2*2,0.4,SERVER_ADDRESS, sizeof(SERVER_ADDRESS));
	if(button(GenUIID(0),x+0.2+w-0.2*2-0.6,y+0.1,0.6,0.27,"ȷ��")){
	IfFlag = 0;
	MouseAction = 0; 
	}
}
/*����ͼ����Ϣ*/ 
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
	drawLabel(x,y,"�� �� ");
	drawLabel(x,y-d,"�� �� ");
	drawLabel(x,y-2*d,"�ؼ��� ");
	drawLabel(x,y-3*d,"�� �� ");
	drawLabel(x,y-4*d,"������ ");
	drawLabel(x,y-5*d,"��������");
	drawLabel(x,y-6*d,"�������"); 
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.07,w,h,bookinfoBooknameSwap,sizeof(bookinfoBooknameSwap));
	textbox(GenUIID(0),x+1,y-0.07-d,w,h,bookinfoAuthorsSwap,sizeof(bookinfoAuthorsSwap));
	textbox(GenUIID(0),x+1,y-0.07-d*2,w,h,bookinfoKeywordsSwap,sizeof(bookinfoKeywordsSwap));
	textbox(GenUIID(0),x+1,y-0.07-d*3,w,h,bookinfoCategorySwap,sizeof(bookinfoCategorySwap));
	textbox(GenUIID(0),x+1,y-0.07-d*4,w,h,bookinfoPublisherSwap,sizeof(bookinfoPublisherSwap));
	textbox(GenUIID(0),x+1,y-0.07-d*5,w,h,bookinfoPubtimeSwap,sizeof(bookinfoPubtimeSwap));
	textbox(GenUIID(0),x+1,y-0.07-d*6,w,h,bookinfoQuantitySwap,sizeof(bookinfoQuantitySwap));
	if(button(GenUIID(0),x+1.4,y-d*7-0.2,1,0.35,"�� ��")){ 
		//�������д����ĺ������������id��bookname��keywords��authors��category��publisher��pubtime��quantity���浽��˵����ݲ� 
		//�½��ɹ���StatusBar=NBSuccess,ʧ����NBFail 
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
		input=NULL;             //�������ָ�������ÿ� 
		if(result==AUTHORIZE_FAILED){    //����Ա�����֤ʧ�� 
			STATUS=NBFail; 
		}
		else if(result==PERMISSION_DENIED){   //Ȩ�޲��� 
			STATUS=NBFail;
		}
		else if(result==SUCCESS){      //�����ɹ� 
			STATUS=NBSuccess;
		}
		/*���������*/
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
/*����ͼ����Ϣ*/ 
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
	drawLabel(x,y-0.3,"�� ��");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-d*2,1,0.35,"�� ��")){
		//��˲�������������һ�µ���Ϣ������, ��Ÿı�
		BOOKS *input=NULL;
		input=getBookInfo(DATABASE,bookinfoIdSwap); 
		int result;
		result=AU_createNewBook(DATABASE,input,UserInfo);
		input=NULL;             //�������ָ�������ÿ� 
		if(result==AUTHORIZE_FAILED){    //����Ա�����֤ʧ�� 
			STATUS=AuthorizeFail; 
		}
		else if(result==PERMISSION_DENIED){   //Ȩ�޲��� 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){      //���Ƴɹ� 
			STATUS=CBSuccess;
		}
		/*���������*/
		bookinfoIdSwap[0]='\0';
	}
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"������������Ҫ���Ƶ��鼮��Ϣ�����");
}
/*��ȷ��������*/ 
void SearchSpecificBook()
{
	double x,y,d,w,h;
	x=3.25;
	y=3.5;
	d=0.6;
	w=2;
	h=0.35;
	SetPointSize(20);
	drawLabel(x,y-0.3,"�� ��");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-d*2,1,0.35,"�� ѯ")){
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);//��˲�������������һ�µ���Ϣ
		strcpy(bookinfoBooknameSwap,BookInfo->bookname);
		strcpy(bookinfoAuthorsSwap,BookInfo->authors);
		strcpy(bookinfoKeywordsSwap,BookInfo->keywords);
		strcpy(bookinfoPublisherSwap,BookInfo->publisher);
		strcpy(bookinfoPubtimeSwap,BookInfo->pubtime);
		strcpy(bookinfoCategorySwap,BookInfo->category);
		strcpy(bookinfoRegtimeSwap,BookInfo->regtime);
		sprintf(bookinfoQuantitySwap,"%d",BookInfo->quantity);
		sprintf(bookinfoIsborrowedSwap,"%d",BookInfo->isborrowed);
		IfFlag=Book_SEARCH_pop;//ͨ��SearchBookpop��ʾ 
	}
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"������������Ҫ��ѯ�����");
} 
/*��ȷ�����������*/ 
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
	drawLabel(x+0.1,y+hx+0.15,"�鼮��Ϣ"); 
	drawLabel(x+0.5,y+3,"�� ��");drawLabel(x+1.3,y+3,bookinfoIdSwap);
	drawLabel(x+3.5,y+3,"�� ��");drawLabel(x+4.3,y+3,bookinfoBooknameSwap);
	drawLabel(x+0.5,y+3-d,"�� ��");drawLabel(x+1.3,y+3-d,bookinfoAuthorsSwap);
	drawLabel(x+3.5,y+3-d,"�� ��");drawLabel(x+4.3,y+3-d,bookinfoCategorySwap);
	drawLabel(x+0.5,y+3-d*2,"�ؼ���");drawLabel(x+1.3,y+3-d*2,bookinfoKeywordsSwap);
	drawLabel(x+3.5,y+3-d*2,"������");drawLabel(x+4.3,y+3-d*2,bookinfoPublisherSwap);
	drawLabel(x+0.5,y+3-d*3,"��������");drawLabel(x+1.3,y+3-d*3,bookinfoPubtimeSwap);
	drawLabel(x+3.5,y+3-d*3,"���ʱ��");drawLabel(x+4.3,y+3-d*3,bookinfoRegtimeSwap);
	drawLabel(x+0.5,y+3-d*4,"�������");drawLabel(x+1.3,y+3-d*4,bookinfoQuantitySwap);
	drawLabel(x+3.5,y+3-d*4,"��������");drawLabel(x+4.3,y+3-d*4,bookinfoIsborrowedSwap);
	if(button(GenUIID(0),x+2.6,y+0.4,0.8,0.25,"��  ��")){
		IfFlag=Book_SEARCH;
		/*���������*/
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
/*�޸�ͼ����Ϣ*/ 
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
	drawLabel(x,y-0.3,"�� ��");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-d*2,1,0.35,"�� ��")){
		IfFlag=Book_MODIFY_pop; 
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);//�����û��������ţ����������ҵ�����������ͼ����Ϣ�ṹ��ֵ����ȫ�ֱ���BookInfo 
	}	 
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"������������Ҫ�޸ĵ��鼮��Ϣ�����");
}
/*�޸�ͼ����Ϣ����*/ 
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
	drawLabel(x+0.1,y+hx+0.15,"�޸��鼮��Ϣ"); 
	drawLabel(x+0.5,y+3,"�� ��");drawLabel(x+1.3,y+3,bookinfoIdSwap);
	drawLabel(x+3.5,y+3,"�� ��");textbox(GenUIID(0),x+4.3,y+3-0.07,1.2,0.25,bookinfoBooknameSwap,sizeof(bookinfoBooknameSwap));
	drawLabel(x+0.5,y+3-d,"�� ��");textbox(GenUIID(0),x+1.3,y+3-0.07-d,1.2,0.25,bookinfoAuthorsSwap,sizeof(bookinfoAuthorsSwap));
	drawLabel(x+3.5,y+3-d,"�� ��");textbox(GenUIID(0),x+4.3,y+3-0.07-d,1.2,0.25,bookinfoCategorySwap,sizeof(bookinfoCategorySwap));
	drawLabel(x+0.5,y+3-d*2,"�ؼ���");textbox(GenUIID(0),x+1.3,y+3-0.07-d*2,1.2,0.25,bookinfoKeywordsSwap,sizeof(bookinfoKeywordsSwap));
	drawLabel(x+3.5,y+3-d*2,"������");textbox(GenUIID(0),x+4.3,y+3-0.07-d*2,1.2,0.25,bookinfoPublisherSwap,sizeof(bookinfoPublisherSwap));
	drawLabel(x+0.5,y+3-d*3,"��������");textbox(GenUIID(0),x+1.3,y+3-0.07-d*3,1.2,0.25,bookinfoPubtimeSwap,sizeof(bookinfoPubtimeSwap));
	drawLabel(x+3.5,y+3-d*3,"���ʱ��");drawLabel(x+4.3,y+3-d*3,bookinfoRegtimeSwap);
	drawLabel(x+0.5,y+3-d*4,"�������");textbox(GenUIID(0),x+1.3,y+3-0.07-d*4,1.2,0.25,bookinfoQuantitySwap,sizeof(bookinfoQuantitySwap));
	drawLabel(x+3.5,y+3-d*4,"��������");textbox(GenUIID(0),x+4.3,y+3-0.07-d*4,1.2,0.25,bookinfoIsborrowedSwap,sizeof(bookinfoIsborrowedSwap));
	/*һ��ʼ����ʾ�޸�ǰ����Ϣ*/
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
		/*���������*/
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
	if(button(GenUIID(0),x+2.6,y+0.4,0.8,0.25,"ȷ  ��")){
		//��ˣ��޸��鱾��Ϣ ���˴�����һ��ʼӦ�����ı�������ʾδ�޸�ǰ����Ϣ������һ���޸İ�ť��BookInfo��ֵ�ﵽĿ�ģ��޸ĺ�BookInfoֵ���� 
		/*���޸ĺ����Ϣ�ӻ�������ֵ��BookInfo*/
		strcpy(BookInfo->bookname,bookinfoBooknameSwap);
		strcpy(BookInfo->authors,bookinfoAuthorsSwap);
		strcpy(BookInfo->category,bookinfoCategorySwap);
		strcpy(BookInfo->keywords,bookinfoKeywordsSwap);
		strcpy(BookInfo->publisher,bookinfoPublisherSwap);
		strcpy(BookInfo->pubtime,bookinfoPubtimeSwap);
		BookInfo->quantity=atoi(bookinfoQuantitySwap);
		BookInfo->isborrowed=atoi(bookinfoIsborrowedSwap);
		int result;      //�����޸Ĳ������
		result=AU_bookModify(DATABASE,UPDATEMODE,BookInfo,UserInfo);
		if(result==AUTHORIZE_FAILED){    //����Ա�����֤ʧ�� 
			STATUS=AuthorizeFail; 
		}
		else if(result==PERMISSION_DENIED){   //Ȩ�޲��� 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){      //�޸ĳɹ� 
			STATUS=MBSuccess;
		}
		/*���������*/
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
/*ɾ��ͼ����Ϣ*/ 
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
	drawLabel(x,y-0.3,"�� ��");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-d*2,1,0.35,"ɾ ��")){
		/*��˲�������������һ�µ���Ϣ��������ɾ�� */
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);
		int result;      //����ɾ���������
		result=AU_bookModify(DATABASE,DELETEMODE,BookInfo,UserInfo);
		if(result==AUTHORIZE_FAILED){    //����Ա�����֤ʧ�� 
			STATUS=AuthorizeFail; 
		}
		else if(result==PERMISSION_DENIED){   //Ȩ�޲��� 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){      //ɾ���ɹ� 
			STATUS=MBSuccess;
		}
		/*���������*/
		bookinfoIdSwap[0]='\0';
	}	 
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"������������Ҫɾ���鼮�����");
}
/*�鼮ͳ�ƹ���*/ 
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
		sprintf(TotalBookAmount,"%d",CountTotalBook(DATABASE));//�������� 
		sprintf(TotalBorrowAmount,"%d",CountTotalBorrowed(DATABASE));//�������� 
	}
	x=2.5;
	y=0.5;
	w=5;
	hs=0.4;
	hx=4.5;
	d=0.22;//�γ�+�ɼ�һ�еĸ߶ȣ��������ʱ��һ��y+hx-0.6-d,�ڶ��о���y+hx-0.6-2*d��������� ������ ���Ĵ������ 
	SetPointSize(1);
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"ͳ�ƽ��");
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0; 
		MouseAction=0;   //�ָ���ʼ״̬ 
	}
	SetPenColor("MidnightBlue");
	drawRectangle(x+0.1,y+0.1,w-0.2,hx-0.2,0);
	drawRectangle(x+0.1,y+0.1,w-0.2,0.4,0);
	drawLabel(x+0.5,y+hx-0.5,"�鼮���");
	drawLabel(x+2.3,y+hx-0.5,"������");
	drawLabel(x+3.6,y+hx-0.5,"���Ĵ���");
	drawLabel(x+0.3,y+0.25,"�ܲ�������");
	drawLabel(x+2.5,y+0.25,"�ܽ�������"); 
	BOOKAMOUNT *ptr;          //���ڱ���������� 
	static BOOKAMOUNT *head = NULL;         //���ڱ��ͷ��� 
	if(pIfFlag != IfFlag)
	{
		if(head != NULL) freeBookAmount(head);
		head=BorrowedInfo(DATABASE);
	}
	ptr=head;
    int count=1;
	while(ptr!=NULL){      //����������ҽ�� 
		/*����ǰ��㴦����ͼ������Ľ�����Ϣ���뻺����*/ 
		strcpy(amountCategorySwap,ptr->category);
		sprintf(amountTotalbooksSwap,"%d",ptr->TotalBooks);
		sprintf(amountTotalborrowedSwap,"%d",ptr->TotalBorrowed);
		/*�ӻ�����������*/
		/*�˴������������Ĵ���*/ /*������� ������ ���Ĵ������*/
        drawLabel(x+0.3,y+hx-0.6-d*count,amountCategorySwap);
        drawLabel(x+2.1,y+hx-0.6-d*count,amountTotalbooksSwap);
        drawLabel(x+3.4,y+hx-0.6-d*count,amountTotalborrowedSwap);
		ptr=ptr->next; 
        count++;
	}
	SetPenColor("Black");
	drawLabel(x+1.1,y+0.25,TotalBookAmount);
	drawLabel(x+3.3,y+0.25,TotalBorrowAmount);
	/*��������*/
	amountCategorySwap[0]='\0';
	amountTotalbooksSwap[0]='\0';
	amountTotalborrowedSwap[0]='\0';
	pIfFlag = IfFlag;
}

/*�����鼮*/ 
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
	drawLabel(x,y-0.3,"�� ��");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"�� ��")){
		/*���ĳɹ�StatusBar=BorrowSuccess,ʧ��BorrowFail(�޿�棩*/
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);
		int result;      //������Ĳ������
		result=borrowBook(DATABASE,BookInfo,UserInfo);
		if(result==AUTHORIZE_FAILED){    //������� 
			STATUS=PasswordError; 
		}
		else if(result==NO_BOOK_LEFT){   //ͼ���޿�� 
			STATUS=BookUnavailable;
		}
		else if(result==SUCCESS){      //���ĳɹ� 
			STATUS=BorrowSuccess;
		}
		BookInfo=NULL;     //������ɺ���NULL 
		/*���������*/
		bookinfoIdSwap[0]='\0';
	}
}
/*�黹�鼮*/ 
void ReturnTheBook(){
	double x,y,d,w,h;
	x=3;
	y=3.5;
	d=0.8;
	w=2.3;
	h=0.4;
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y-0.3,"�� ��");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1-0.3,w,h,bookinfoIdSwap,sizeof(bookinfoIdSwap)); 
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"�� ��")){
		/*��˻�����룬BookInfo��BOOKSTATE�ĸ���*/
		BookInfo=getBookInfo(DATABASE,bookinfoIdSwap);
		int result;      //����黹�������
		result=returnBook(DATABASE,BookInfo,UserInfo);
		if(result==AUTHORIZE_FAILED){    //�������
			STATUS=PasswordError; 
		}
		else if(result==SUCCESS){      //�黹�ɹ� 
			STATUS=ReturnSuccess;
		}
		BookInfo=NULL;    //�����ɹ��Ժ���NULL 
		/*���������*/
		bookinfoIdSwap[0]='\0';
	}
}
/*�û����*/ 
void CheckUserStatus()
{
	double x,y,d,w,h;
	x=4.4;
	y=2.85;
	d=0.8;
	w=2.3;
	h=0.4;
	SetPenColor("Black");
	drawLabel(x,y,"��ǰ�ǹ���Ա״̬");
}
/*�����û���Ϣ*/ 
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
	drawLabel(x,y-d,"�û���");
	SetPointSize(1);
	textbox(GenUIID(0),x+1.3,y-0.1,w,h,userinfoIdSwap,sizeof(userinfoIdSwap)); 
	textbox(GenUIID(0),x+1.3,y-0.1-d,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"�� ��")){
		IfFlag=User_SEARCH_pop; 
		/*���������ID���û�����ѯ��Ӧ��UserInfo�����û�����������pop�������涼��ͬ����UserInfo*/
		if(userinfoUsernameSwap!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
			UserResult=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
		if(UserResult!=NULL&&UserResult->id!=-1){
			if(UserResult->id==atoi(userinfoIdSwap)){   //���������û�����idһ�¶�Ӧ����� 
				STATUS=SearchUserSuccess;          //�����ɹ� 
				strcpy(userinfoModeSwap,UserResult->mode);
				strcpy(userinfoGenderSwap,UserResult->gender);
				strcpy(userinfoDepartmentSwap,UserResult->department);
				strcpy(userinfoRegtimeSwap,UserResult->regtime);
				sprintf(userinfoBorrowedbooksSwap,"%d",UserResult->borrowedbooks);
			}
			else{     //�û�����id��ƥ�� 
				STATUS=UnmatchedUIDName; 
			}
			if(UserResult!=NULL){    //�û������� 
				STATUS=UserNotfind;
			}
		}
		else{       //�����֤ʧ�� 
			STATUS=AuthorizeFail; 
		} 
	}
	SetPenColor("Gray");
	drawLabel(x,y-1.7-0.25,"������������Ҫ��ѯ���û�����ID");
}
/*�����û���Ϣ�������*/ 
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
	drawLabel(x+0.1,y+hx+0.15,"�û���Ϣ����");drawLabel(x+1.1,y+hx+0.15,userinfoModeSwap); 
	drawLabel(x+0.5,y+1.9,"ID");drawLabel(x+1.3,y+1.9,userinfoIdSwap);
	drawLabel(x+3.5,y+1.9,"�û���");drawLabel(x+4.3,y+1.9,userinfoUsernameSwap);
	drawLabel(x+0.5,y+1.9-d,"�� ��");drawLabel(x+1.3,y+1.9-d,userinfoGenderSwap);
	drawLabel(x+3.5,y+1.9-d,"�� λ");drawLabel(x+4.3,y+1.9-d,userinfoDepartmentSwap);
	drawLabel(x+0.5,y+1.9-d*2,"�ѽ�����");drawLabel(x+1.3,y+1.9-2*d,userinfoBorrowedbooksSwap);
	drawLabel(x+3.5,y+1.9-2*d,"ע��ʱ��");drawLabel(x+4.3,y+1.9-2*d,userinfoRegtimeSwap);
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=User_SEARCH;
		/*���������*/
		userinfoIdSwap[0]='\0';
		userinfoUsernameSwap[0]='\0';
		userinfoGenderSwap[0]='\0';
		userinfoDepartmentSwap[0]='\0';
		userinfoModeSwap[0]='\0';
		userinfoBorrowedbooksSwap[0]='\0';
		userinfoRegtimeSwap[0]='\0';
	}
	if(button(GenUIID(0),x+1.0,y+0.3,1.2,0.25,"�û�������Ϣ")){
		IfFlag=User_COUNTBorrow_pop;//��˵����û�������ʷ����ʾ�ڵ����Ĵ����� 
	} 
	if(button(GenUIID(0),x+4.25,y+0.3,0.65,0.25,"�� ��")){
		IfFlag=User_SEARCH;
		/*���������*/
		userinfoIdSwap[0]='\0';
		userinfoUsernameSwap[0]='\0';
		userinfoGenderSwap[0]='\0';
		userinfoDepartmentSwap[0]='\0';
		userinfoModeSwap[0]='\0';
		userinfoBorrowedbooksSwap[0]='\0';
		userinfoRegtimeSwap[0]='\0';
	} 	
}
/*�û�������Ϣ*/ 
void CountBorrowHistory(){
	double x,y,w,hs,hx,d;
	x=2;
	y=0.5;
	w=6;
	hs=0.4;
	hx=4.5;
	d=0.22;//����+�黹ʱ��һ�еĸ߶ȣ��������ʱ��һ��y+hx-0.6-d,�ڶ��о���y+hx-0.6-2*d, ��ʾʱ��û�����������棬Ȼ���ս����������� 
	SetPointSize(1);
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"������ʷ");
	drawLabel(x+0.1,y+hx-0.2,"ID��"); 
	drawLabel(x+0.1+0.2,y+hx-0.2,userinfoIdSwap);
	drawLabel(x+2,y+hx-0.2,"�û�����");
	drawLabel(x+2.8,y+hx-0.2,userinfoUsernameSwap);
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=User_SEARCH_pop;
	}
	SetPenColor("MidnightBlue");
	drawRectangle(x+0.1,y+0.1,w-0.2,hx-0.4,0);
	drawRectangle(x+0.1,y+0.1,w-0.2,0.4,0);
	drawLabel(x+0.5,y+hx-0.5,"���");
	drawLabel(x+2.8,y+hx-0.5,"����ʱ��");
	drawLabel(x+5.1,y+hx-0.5,"�黹ʱ��");//�����û������ʾ��δ�黹 �� 
	BOOKSTATE *ptr;          //���ڱ���������� 
	int count=0;         //���ڼ��� 
	BookCurrentState=AU_getBookRecordsByUser(DATABASE,userinfoUsernameSwap,UserInfo); 
	ptr=BookCurrentState;
	if(ptr!=NULL){
		while(ptr!=NULL){      //�������������ʷ
			/*����ǰ��㴦�Ľ�����ʷ���뻺����*/ 
			strcpy(stateinfoBookidSwap,ptr->bookid);
			strcpy(stateinfoBorrowdateSwap,ptr->borrowdate);
			strcpy(stateinfoDuedataSwap,ptr->duedate);
			/*�ӻ�����������*/
			/*�˴������������Ĵ���*/ 
			drawLabel(x+0.3,y+hx-0.5-0.22-d*count,stateinfoBookidSwap);
			drawLabel(x+2.6,y+hx-0.5-0.22-d*count,stateinfoBorrowdateSwap);
			drawLabel(x+4.9,y+hx-0.5-0.22-d*count,stateinfoDuedataSwap);
			count++;
			ptr=ptr->next; 
		}
	}
	drawLabel(x+0.3,y+0.25,"δ��������");
	USERS *temp=NULL;        //���������û�����Ϣ��� 
	if(UserInfo!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
		temp=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
	if(temp!=NULL&&temp->id!=-1){
		sprintf(userinfoBorrowedbooksSwap,"%d",temp->borrowedbooks);
		drawLabel(x+1.1,y+0.25,userinfoBorrowedbooksSwap);        //��ʾ���ѯ���û���ͼ��δ������ 
		if(temp!=NULL)freeSingleUser(temp);       //ʹ����ϣ�������NULL���ͷ��ڴ� 
	}
	SetPenColor("Black");
}
/*�޸��û���Ϣ*/ 
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
	drawLabel(x,y-d,"�û���");
	SetPointSize(1);
	textbox(GenUIID(0),x+1.3,y-0.1,w,h,userinfoIdSwap,sizeof(userinfoIdSwap)); 
	textbox(GenUIID(0),x+1.3,y-0.1-d,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"�� ��")){
		IfFlag=User_MODIFY_pop; 
		/*��ˣ����������ID���û�����ѯ��Ӧ��UserInfo*/
		if(userinfoUsernameSwap!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
			UserResult=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
		if(UserResult!=NULL&&UserResult->id!=-1){
			if(UserResult->id==atoi(userinfoIdSwap)){   //���������û�����idһ�¶�Ӧ����� 
				STATUS=SearchUserSuccess;          //�����ɹ� 
				strcpy(userinfoModeSwap,UserResult->mode);
				strcpy(userinfoGenderSwap,UserResult->gender);
				strcpy(userinfoDepartmentSwap,UserResult->department);
				sprintf(userinfoBorrowedbooksSwap,"%d",UserResult->borrowedbooks);
			}
			else{     //�û�����id��ƥ�� 
				STATUS=UnmatchedUIDName; 
			}
			if(UserResult!=NULL){    //�û������� 
				STATUS=UserNotfind;
			}
		}
		else{       //�����֤ʧ�� 
			STATUS=AuthorizeFail; 
		} 
	}
	SetPenColor("Gray");
	drawLabel(x,y-1.7-0.25,"������������Ҫ�޸ĵ��û�����ID");
}
/*�޸��û���Ϣ�༭����*/ 
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
	drawLabel(x+0.1,y+hx+0.15,"�� ��"); 
	drawLabel(x+0.5,y+0.9+d*5,"�û���");//Ĭ�ϲ����ظ� 
	drawLabel(x+0.5,y+0.9+d*4,"�� ��");
	drawLabel(x+0.5,y+0.9+d*3,"�� ��");
	drawLabel(x+0.5,y+0.9+2*d,"�� λ");
	drawLabel(x+0.5,y+0.9+1*d,"Ȩ ��");
	SetPenColor("Gray");
	drawLabel(x+0.2,y+0.9+0.15,"*Ȩ����д��ѧ�������ߡ�����Ա��"); 
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*5,1.2,0.25,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*4,1.2,0.25,userinfoPasswordsSwap,sizeof(userinfoPasswordsSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*3,1.2,0.25,userinfoGenderSwap,sizeof(userinfoGenderSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*2,1.2,0.25,userinfoDepartmentSwap,sizeof(userinfoDepartmentSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*1,1.2,0.25,userinfoModeSwap,sizeof(userinfoModeSwap));
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=User_MODIFY;//�����Ͻ� ���رյ��� 
		/*���������*/
		userinfoIdSwap[0]='\0';
		userinfoUsernameSwap[0]='\0';
		userinfoGenderSwap[0]='\0';
		userinfoDepartmentSwap[0]='\0';
		userinfoModeSwap[0]='\0';
		userinfoBorrowedbooksSwap[0]='\0';
		userinfoRegtimeSwap[0]='\0';
	}
	if(button(GenUIID(0),x+1.25,y+0.3,0.65,0.25,"ȷ���޸�")){
		/*��ˣ������޸ĺ���û���Ϣ*/ 
		int result;       //���ڴ����޸Ĳ����Ľ�� 
		result=AU_userModify(DATABASE,UPDATEMODE,UserResult,UserInfo);
		if(result==AUTHORIZE_FAILED){    //������� 
			STATUS=PasswordError;
		} 
		else if(result==PERMISSION_DENIED){   //Ȩ�޲��� 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){    //�޸ĳɹ� 
			STATUS=ModifyUserSuccess; 
		}
		/*���������*/
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
/*ɾ���û���Ϣ*/ 
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
	drawLabel(x,y-d,"�û���");
	SetPointSize(1);
	textbox(GenUIID(0),x+1.3,y-0.1,w,h,userinfoIdSwap,sizeof(userinfoIdSwap)); 
	textbox(GenUIID(0),x+1.3,y-0.1-d,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	if(button(GenUIID(0),x+1.4,y-1.7,1,0.35,"ɾ ��")){
		/*��˲����������ID���û���һ�µ���Ϣ����ɾ��*/
		if(userinfoUsernameSwap!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
			UserResult=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
		if(UserResult!=NULL&&UserResult->id!=-1){
			if(UserResult->id==atoi(userinfoIdSwap)){   //���������û�����idһ�¶�Ӧ����� 
				STATUS=SearchUserSuccess;          //�����ɹ� 
			}
			else{     //�û�����id��ƥ�� 
				STATUS=UnmatchedUIDName; 
			}
			if(UserResult!=NULL){    //�û������� 
				STATUS=UserNotfind;
			}
		}
		else{       //�����֤ʧ�� 
			STATUS=AuthorizeFail; 
		} 
		int result;       //���ڴ����޸Ĳ����Ľ�� 
		result=AU_userModify(DATABASE,DELETEMODE,UserResult,UserInfo);
		if(result==AUTHORIZE_FAILED){    //������� 
			STATUS=PasswordError;
		} 
		else if(result==PERMISSION_DENIED){   //Ȩ�޲��� 
			STATUS=AuthorizeFail;
		}
		else if(result==SUCCESS){    //�޸ĳɹ� 
			STATUS=DeleteUserSuccess; 
		}
		/*���������*/
		userinfoIdSwap[0]='\0';
		userinfoUsernameSwap[0]='\0';
		userinfoGenderSwap[0]='\0';
		userinfoDepartmentSwap[0]='\0';
		userinfoModeSwap[0]='\0';
		userinfoBorrowedbooksSwap[0]='\0';
		userinfoRegtimeSwap[0]='\0';
	}
	SetPenColor("Gray");
	drawLabel(x,y-1.7-0.25,"������������Ҫɾ�����û���ID���û���");
}
/*�û�����*/
void UserInfoRank()
{
	double x,y,w,hs,hx,d;
	x=2;
	y=0.5;
	w=6;
	hs=0.4;
	hx=4.5;
	d=0.22;//���ʱ��һ��y+hx-0.6-d,�ڶ��о���y+hx-0.6-2*d 
	SetPointSize(1);
	SetPenColor("Ivory");
	drawRectangle(x,y,w,hx,1);
	SetPenColor("Gray");
	drawRectangle(x,y+hx,w,hs,1);
	SetPenColor("Black");
	drawRectangle(x,y,w,hx,0);
	drawRectangle(x,y+hx,w,hs,0);
	drawLabel(x+0.1,y+hx+0.15,"�û���Ϣ");
	drawLabel(x+0.1,y+hx-0.2,"����ʽ��"); 
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0;
		MouseAction=0; 
	}
	if(button(GenUIID(0),x+0.9,y+hx-0.26,0.52,0.23,"��ID")){
		;//��ID���� 
	} 
	if(button(GenUIID(0),x+1.5,y+hx-0.26,0.52,0.23,"������")){
		;//������ 
	} 
	if(button(GenUIID(0),x+2.1,y+hx-0.26,0.52,0.23,"������")){
		;//��������λ���� 
	} 
	SetPenColor("MidnightBlue");
	drawRectangle(x+0.1,y+0.1,w-0.2,hx-0.4,0);
	drawLabel(x+0.5,y+hx-0.5,"ID");
	// drawLabel(x+0.2,y+hx-0.6-d*count,"ID");
	drawLabel(x+2.8,y+hx-0.5,"����");
	// drawLabel(x+0.2,y+hx-0.6-d*count,"����");
	drawLabel(x+4.7,y+0.25,"����"); 
	// drawLabel(x+0.2,y+hx-0.6-d*count,"����");
	SetPenColor("Black");
}
/*ͳ���û���������*/ 
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
	drawLabel(x,y-d,"�û���");
	SetPointSize(1);
	textbox(GenUIID(0),x+1.3,y-0.1,w,h,userinfoIdSwap,sizeof(userinfoIdSwap)); 
	textbox(GenUIID(0),x+1.3,y-0.1-d,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	if(button(GenUIID(0),x+0.9,y-1.7,2,0.35,"�鿴ͳ������")){
		IfFlag=User_COUNT_pop; 
		/*��ˣ����������ID���û�����ѯ��Ӧ��UserInfo*/
		if(userinfoUsernameSwap!=NULL&&UserInfo->username!=NULL&&UserInfo->passwords!=NULL)
			UserResult=AU_getUserInfo(DATABASE,userinfoUsernameSwap,UserInfo);
		if(UserResult!=NULL&&UserResult->id!=-1){
			if(UserResult->id==atoi(userinfoIdSwap)){   //���������û�����idһ�¶�Ӧ����� 
				STATUS=SearchUserSuccess;          //�����ɹ� 
			}
			else{     //�û�����id��ƥ�� 
				STATUS=UnmatchedUIDName; 
			}
			if(UserResult!=NULL){    //�û������� 
				STATUS=UserNotfind;
			}
		}
		else{       //�����֤ʧ�� 
			STATUS=AuthorizeFail; 
		} 
	}
	SetPenColor("Gray");
	drawLabel(x,y-1.7-0.25,"������������Ҫͳ�Ƶ��û���ID���û���");
}
/*�û��������ݽ��*/ 
void CountUserInfopop(){
	double x,y,w,hs,hx,d;
	char* TotalBorrowed;//�������� 
	char* MonthlyFrequency;//��Ƶ�� 
	char* YearlyFrequency;//��Ƶ��
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
	drawLabel(x+0.1,y+hx+0.15,"�û�ͳ�� ID��");
	drawLabel(x+1.3,y+hx+0.15,userinfoIdSwap);
	drawLabel(x+2.5,y+hx+0.15,"�û�����");
	drawLabel(x+3.3,y+hx+0.15,userinfoUsernameSwap);
	drawLabel(x+0.5,y+3.9,"����������");drawLabel(x+1.5,y+3.9,TotalBorrowed);
	drawLabel(x+3.5,y+3.9,"δ��������");drawLabel(x+4.5,y+3.9,userinfoBorrowedbooksSwap);
	drawLabel(x+0.5,y+3.9-d,"�½���Ƶ�ʣ�");drawLabel(x+1.5,y+3.9-d,MonthlyFrequency);
	drawLabel(x+3.5,y+3.9-d,"�����Ƶ�ʣ�");drawLabel(x+4.5,y+3.9-d,YearlyFrequency);
	drawLabel(x+0.5,y+3.9-d*2,"�����鼮������У�");
	drawLabel(x+2.8,y+3.9-d*2,"1.");//���д����������ֻ�о�ǰ���������������ͬ��x����Ϊx+3.0 
	drawLabel(x+2.8,y+3.9-d*3,"2.");
	drawLabel(x+2.8,y+3.9-d*4,"3.");
	if(button(GenUIID(0),x+2.7,y+0.3,0.65,0.25,"�� ��")){
		IfFlag=User_COUNT;//����رյ��� 
	}	
}
/*�û���������*/ 
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
	drawLabel(x+0.1,y+hx+0.15,"��������");drawLabel(x+1.1,y+hx+0.15,userinfoModeSwap); 
	drawLabel(x+0.5,y+1.9,"ID");drawLabel(x+1.3,y+1.9,userinfoIdSwap);
	drawLabel(x+3.5,y+1.9,"�û���");drawLabel(x+4.3,y+1.9,userinfoUsernameSwap);
	drawLabel(x+0.5,y+1.9-d,"�� ��");drawLabel(x+1.3,y+1.9-d,userinfoGenderSwap);
	drawLabel(x+3.5,y+1.9-d,"�� λ");drawLabel(x+4.3,y+1.9-d,userinfoDepartmentSwap);
	drawLabel(x+0.5,y+1.9-d*2,"�ѽ�����");drawLabel(x+1.3,y+1.9-2*d,userinfoBorrowedbooksSwap);
	drawLabel(x+3.5,y+1.9-2*d,"ע��ʱ��");drawLabel(x+4.3,y+1.9-2*d,userinfoRegtimeSwap);
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0; 
		MouseAction=0;
	} 
	if(button(GenUIID(0),x+1.0,y+0.3,1.2,0.25,"�û�������Ϣ")){
		IfFlag=User_COUNTBorrow_pop;//��˵����û�������ʷ����ʾ�ڵ����Ĵ����� 
	} 
	if(button(GenUIID(0),x+4.25,y+0.3,0.65,0.25,"�� ��")){
		IfFlag=User_MODIFY_pop;
	}
}
/*���ڱ����*/ 
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
	drawLabel(x+0.1,y+hx+0.15,"���ڱ����");
	drawLabel(4.2, y+1.6,"Version 0.99 Beta");
	drawLabel(4.6, y+1.6+d, "�汾˵��");
	drawLabel(4.4, y+1.6+2*d,"ͼ�����ϵͳ"); 
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0;
		MouseAction=0;//�����Ͻ� ���رյ��� 
	}	
}
/*ʹ�÷���*/ 
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
	drawLabel(x+0.1,y+hx+0.15,"ʹ�÷���");
	drawLabel(x+0.2,y+hx-0.6,"1. ��������ʹ�����б���Ŀͻ��ˣ�");
	drawLabel(x+0.5,y+hx-0.6-1*d,"��ȷ�����ķ����(Server)������");
	drawLabel(x+0.2,y+hx-0.6-2*d,"2. ����ʹ�ù����г���δ��Ӧ�����˵������");
	drawLabel(x+0.5,y+hx-0.6-3*d,"�����ĵȴ�����������");
	drawLabel(x+0.2,y+hx-0.6-4*d,"3. ���и����������ʼ���ϵxxxx@xx.xx");
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=0;
		MouseAction=0;//�����Ͻ� ���رյ��� 
	}
}
/*Ĭ��ʲô������ʾ�Ľ���*/ 
void DisplayNothing()
{
	;
} 

