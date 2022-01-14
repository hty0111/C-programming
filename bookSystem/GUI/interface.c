#include "SIMS.h"
extern int MouseAction;
extern int WindowNum;//��ʼ����Ϊ��ӭ���� 
extern int IfFlag;//��ʼ��ʾ״̬ΪĬ��ֵ 
extern int STATUS;//��ʼ״̬��Ϊ�� 
extern BOOKS *BookInfo;
extern BOOKSTATE *BookCurrentState;
extern USERS *UserInfo;

extern char userinfoIdSwap[SWAP_LIMIT];
extern char userinfoUsernameSwap[SWAP_LIMIT];
extern char userinfoPasswordsSwap[SWAP_LIMIT];
extern char userinfoGenderSwap[SWAP_LIMIT];
extern char userinfoDepartmentSwap[SWAP_LIMIT];
extern char userinfoBorrowedbooksSwap[SWAP_LIMIT];
extern char userinfoModeSwap[SWAP_LIMIT];
extern char userinfoRegtimeSwap[SWAP_LIMIT];

extern char bookinfoIdSwap[SWAP_LIMIT];
extern char bookinfoBooknameSwap[SWAP_LIMIT];
extern char bookinfoKeywordsSwap[SWAP_LIMIT];
extern char bookinfoAuthorsSwap[SWAP_LIMIT];
extern char bookinfoPublisherSwap[SWAP_LIMIT];
extern char bookinfoPubtimeSwap[SWAP_LIMIT];
extern char bookinfoQuantitySwap[SWAP_LIMIT];
extern char bookinfoIsborrowedSwap[SWAP_LIMIT];
extern char bookinfoCategorySwap[SWAP_LIMIT];
extern char bookinfoRegtimeSwap[SWAP_LIMIT];

extern char stateinfoIdSwap[SWAP_LIMIT];
extern char stateinfoUseridSwap[SWAP_LIMIT];
extern char stateinfoBookidSwap[SWAP_LIMIT];
extern char stateinfoBorrowdateSwap[SWAP_LIMIT];
extern char stateinfoDuedataSwap[SWAP_LIMIT];
extern char stateinfoTerminatedSwap[SWAP_LIMIT];

extern char amountCategorySwap[SWAP_LIMIT];
extern char amountTotalbooksSwap[SWAP_LIMIT];
extern char amountTotalborrowedSwap[SWAP_LIMIT];

void Main()
{
	/*��ʼ�����ں�ͼ��ϵͳ*/ 
	SetWindowTitle("ͼ�����ϵͳ");
	SetWindowSize(BOARDWIDTH,BOARDHEIGHT);//���ô��ڴ�С 
	InitGraphics();
	WindowNum = WELCOMEWINDOW;//��ʼ����Ϊ��ӭ���� 
	if(WELCOMEWINDOW==WindowNum){
		 WelcomeBoard();//��ӭ���� 
	}
	else if(LOGINWINDOW==WindowNum){
		LoginBoard();//��½���� 
	}
	else if(ADMINWINDOW==WindowNum){
		 InitializeAdminBoard();              
         RespondMenuEvent();	//����Ա���� 
	} 
	else if(USERWINDOW==WindowNum){
		 InitializeUserBoard();              
         RespondMenuEvent();    //�û����� 
	}
   
    /*ע��ʱ����Ӧ����*/ 
	registerCharEvent(CharEventProcess); /*�ַ�*/ 
	registerKeyboardEvent(KeyboardEventProcess);/*����*/ 
	registerMouseEvent(MouseEventProcess);      /*���*/ 
}

/*����ҳ��*/ 
void WelcomeBoard()
{
	double x=0.1;
    double y=0.1;
	SetPenColor("White");
	drawRectangle(0,0,BOARDWIDTH,BOARDHEIGHT,1);
	SetPenColor("Seashell");
    drawRectangle(1,3,7.7,1.5,1);
	SetPenSize(250);
    SetPenColor("Dark Gray");
    MovePen(x+0.4,BOARDHEIGHT*1.0/2+0.4);
    DrawArc(0.4,0,90);
    MovePen(x+0.4,BOARDHEIGHT*1.0/2+0.4);
    DrawArc(0.4,0,-90);
    SetPenSize(180);
    SetPenColor("IndianRed2");
    MovePen(x+3.3,BOARDHEIGHT*1.0/2+0.4);
    DrawArc(3.3,0,90);
    MovePen(x+3.3,BOARDHEIGHT*1.0/2+0.4);
    DrawArc(3.3,0,-90);
    SetPenSize(1);
	SetPenColor("Black");
    SetPenSize(3);
    MovePen(x+0.4,y);
    DrawLine(BOARDWIDTH-2*x-0.8,0);
    DrawLine(0,0.3);
    DrawLine(0.4,0);
    DrawLine(0,-0.3);
    DrawLine(-0.3,0);
    DrawLine(0,0.4);
    DrawLine(0.3,0);
    MovePen(x+0.4,BOARDHEIGHT-y);
    DrawLine(BOARDWIDTH-2*x-0.8,0);
    DrawLine(0,-0.3);
    DrawLine(0.4,0);
    DrawLine(0,0.3);
    DrawLine(-0.3,0);
    DrawLine(0,-0.4);
    DrawLine(0.3,0);
    MovePen(x,y+0.4);
    DrawLine(0,BOARDHEIGHT-2*y-0.8);
    DrawLine(0.3,0);
    DrawLine(0,0.4);
    DrawLine(-0.3,0);
    DrawLine(0,-0.3);
    DrawLine(0.4,0);
    DrawLine(0,0.3);  
    MovePen(BOARDWIDTH-x,y+0.4);
    DrawLine(0,BOARDHEIGHT-2*y-0.8);
    MovePen(x,y+0.4);
    DrawLine(0.3,0);
    DrawLine(0,-0.4);
    DrawLine(-0.3,0);
    DrawLine(0,0.3);
    DrawLine(0.4,0);
    DrawLine(0,-0.3);
    SetPenSize(2.5);
    MovePen(x+0.15,y+0.15+1);
    DrawLine(0,-1);
    DrawLine(1.5,0); 
	MovePen(x+0.15,BOARDHEIGHT-y-0.15-1);
    DrawLine(0,1);
    DrawLine(1.5,0);
	MovePen(BOARDWIDTH-x-0.15-1.5,BOARDHEIGHT-y-0.15);
    DrawLine(1.5,0);
    DrawLine(0,-1);  
	MovePen(BOARDWIDTH-x-0.15-1.5,y+0.15);
    DrawLine(1.5,0);
    DrawLine(0,1); 
    SetPenColor("White");
    SetPenSize(15);
    drawRectangle(0,0,BOARDWIDTH,BOARDHEIGHT,0);
    SetPenSize(1);
    SetPointSize(65);
    SetPenColor("Gray");
    drawLabel(2.4+0.05,3.5-0.05,"ͼ�����ϵͳ");
    SetPointSize(60);
    SetPenColor("Firebrick1");
    drawLabel(2.4+0.03,3.5,"ͼ�����ϵͳ");
    drawLabel(2.4-0.03,3.5,"ͼ�����ϵͳ");
    drawLabel(2.4,3.5+0.03,"ͼ�����ϵͳ");
    drawLabel(2.4,3.5-0.03,"ͼ�����ϵͳ");
    drawLabel(2.4+0.02,3.5+0.02,"ͼ�����ϵͳ");
    drawLabel(2.4+0.02,3.5-0.02,"ͼ�����ϵͳ");
    drawLabel(2.4-0.02,3.5+0.02,"ͼ�����ϵͳ");
    drawLabel(2.4-0.02,3.5-0.02,"ͼ�����ϵͳ");
    SetPenColor("White");
    drawLabel(2.4,3.5,"ͼ�����ϵͳ"); 
    drawLabel(2.4+0.01,3.5,"ͼ�����ϵͳ");
    drawLabel(2.4-0.01,3.5,"ͼ�����ϵͳ");
    drawLabel(2.4,3.5+0.01,"ͼ�����ϵͳ");
    drawLabel(2.4,3.5-0.01,"ͼ�����ϵͳ");//ͼ�����ϵͳ���������� 
    SetPenColor("Seashell");
    drawRectangle(3.4,1.6,2.8,0.5,1);
	SetPointSize(23); 
	if(button(GenUIID(0),3.3,1.5,3,0.7,"��      ��")){
		WindowNum=LOGINWINDOW; //�������֮����ת�����½���� 
	}
	SetPointSize(1); 
}

/*��¼����*/
void LoginBoard(){
	double x,y,d,w,h;
	x=3.25;
	y=4;
	d=0.6;
	w=2;
	h=0.35;
	drawthebackground();
	StatusBar();
	SetPointSize(20);
	SetPenColor("Black");
	drawLabel(x,y,"�û���");
	drawLabel(x,y-d,"�� ��");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap)); 
	textbox(GenUIID(0),x+1,y-0.1-d,w,h,userinfoPasswordsSwap,sizeof(userinfoPasswordsSwap));
	if(button(GenUIID(0),x+0.6,y-d*2,1,0.35,"��  ¼")){
		/*��˼����½�˺������Ƿ�һ�£��Ƿ��ǹ���Աģʽ��
		����ǹ���Աģʽ WindowNum=ADMINWINDOW, ѧ��ģʽ WindowNum=USERWINDOW
		��������Ϣ��֤ʧ�ܣ�������Ӧָʾ,��д�� StatusBar����*/ 
		int result;             //���������֤��� 
		result=userLogIn(DATABASE,userinfoUsernameSwap,userinfoPasswordsSwap);
		drawLabel(x,y-d*2-0.25,userinfoUsernameSwap);
		if(result==LOG_IN_SUCCESS){   //��¼�ɹ� 
			STATUS=LoginSuccess;
			if(UserInfo!=NULL)freeSingleUser(UserInfo);   //���ͷ���һ���û�����Ϣ�ڴ� 
			UserInfo=(USERS*)calloc(1,sizeof(USERS));     //����һ���û���Ϣ�������û��������� 
			UserInfo->username=(char*)calloc(SWAP_LIMIT,sizeof(char));
			UserInfo->passwords=(char*)calloc(SWAP_LIMIT,sizeof(char)); 
			strcpy(UserInfo->username,userinfoUsernameSwap);
			strcpy(UserInfo->passwords,userinfoPasswordsSwap);
			USERS *temp=UserInfo;
			UserInfo=AU_getUserInfo(DATABASE,UserInfo->username,UserInfo);   //��ȡ��ǰ��¼�û�����Ϣ 
			freeSingleUser(temp);      //�ͷŵ���ʱ��¼�û���������ڴ� 
			if(strcmp(UserInfo->mode,"ADMIN")==0)WindowNum=ADMINWINDOW;   //���ݵõ����û������Ϣ�жϽ���ʲô���� 
			else WindowNum=USERWINDOW; 
		}
		else if(result==PASSWORDS_ERROR){    //������� 
			STATUS=PasswordError;
		}
		else if(result==USERNAME_NOT_FOUND){    //�û��������� 
			STATUS=UserNotfind;
		}
		/*change begin*/
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
	if(button(GenUIID(0),x+2.2,y-d*2,1,0.35,"ע  ��")){
		IfFlag=SignUp_pop;//���ע����룬ע��ɹ�֮���������˺�����ֱ�ӵ�¼ 
	}	 	 
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"�������û��ͼ�����ϵͳ�˺ţ���ע��");		
} 
 
/*Admin��ʼ����*/ 
void InitializeAdminBoard()
{ 
  double x=0.1;
  double y=0.1;
  double w=1.15;
  double wlist=1.15;
  double h=0.35;
  int file_choice,book_choice,borrowreturn_choice,user_choice,help_choice; 
  drawthebackground();
  StatusBar();
  ToolBar();
  static char *file_labels[]={"����",
  "�޸�",//�޸ķ����� 
  "�ر�" //�˳����� 
  };
  static char *book_labels[]={"ͼ��",
  "����ͼ����Ϣ",
  "����ͼ����Ϣ", 
  "����ͼ����Ϣ",//��Ϊ������Ŀ�в˵�ϵͳͼ�鲿�ֵ���ʾ 
  "�޸�ͼ����Ϣ",
  "ɾ��ͼ����Ϣ",
  "ͼ����Ϣͳ��" 
  };
  static char *borrowreturn_labels[]={"ͼ��軹",
  "�����鼮",
  "�黹�鼮",
  };
  static char *user_labels[]={"�û�", 
  "��� | F1", 
  "���� | F2 ",
  "�޸� | F3 ",
  "ɾ�� | F4", 
  "�û�����ͳ��",
  "ע�� | F5" 
  };//�������е�½ע���Ѿ��ڽ���ϵͳ֮����ɣ�����ע������ 
  static char *help_labels[]={"����",
  "���ڱ����",
  "ʹ�÷���"
  }; 
  
  file_choice=menuList(GenUIID(0),x,BOARDHEIGHT-y-h,w,wlist,h,file_labels,sizeof(file_labels)/sizeof(file_labels[0]));
  book_choice=menuList(GenUIID(0),x+w,BOARDHEIGHT-y-h,w,wlist,h,book_labels,sizeof(book_labels)/sizeof(book_labels[0]));
  borrowreturn_choice=menuList(GenUIID(0),x+w*2,BOARDHEIGHT-y-h,w,wlist,h,borrowreturn_labels,sizeof(borrowreturn_labels)/sizeof(borrowreturn_labels[0]));
  user_choice=menuList(GenUIID(0),x+w*3,BOARDHEIGHT-y-h,w,wlist,h,user_labels,sizeof(user_labels)/sizeof(user_labels[0]));
  help_choice=menuList(GenUIID(0),x+w*4,BOARDHEIGHT-y-h,w,wlist,h,help_labels,sizeof(help_labels)/sizeof(help_labels[0]));
  textbox(GenUIID(0),x+w*5,BOARDHEIGHT-y-h,3*w,h,searchtext,sizeof(searchtext));
  if(button(GenUIID(0),x+8*w,BOARDHEIGHT-y-h,0.6,h,"����")){
	IfFlag=Searchchoice_pop; //��˲��Ҵ��� 
	}
  
  if(0<file_choice){
  	switch(file_choice){
  		case 1://������޸ġ����޸ķ����� 
  			MouseAction=Server_CONNECT;
  			IfFlag=MouseAction;
  			break;
  		case 2://������رա����˳�ϵͳ 
   			exit(-1); 		  			  			
	  }
  }
  if(0<book_choice){
  	switch(book_choice){
  		case 1:
  			MouseAction=Book_NEW;//����ͼ����Ϣ�������������ݲ˵�˳������ 
  			IfFlag=MouseAction;
  			break;
  		case 2:
		  	MouseAction=Book_COPY;
   			IfFlag=MouseAction;
  			break;   
  		case 3:
   			MouseAction=Book_SEARCH;
   			IfFlag=MouseAction;
  			break; 
  		case 4:
   			MouseAction=Book_MODIFY;
   			IfFlag=MouseAction;
  			break; 
  		case 5:
   			MouseAction=Book_DELETE;
   			IfFlag=MouseAction;
  			break; 	
		case 6:
			MouseAction=Book_COUNT;
   			IfFlag=MouseAction;
  			break; 		  			  			
	  }
  }
  if(0<borrowreturn_choice){
  	switch(borrowreturn_choice){
  		case 1://���� 
  			MouseAction=Book_BORROW;
  			IfFlag=MouseAction;
  			break;
  		case 2://���� 
   			MouseAction=Book_RETURN;
   			IfFlag=MouseAction;
  			break; 		  			
	  }
  }
  if(0<user_choice){
  	switch(user_choice){//�û����� 
  		case 1:
  			MouseAction=User_CHECK;
  			IfFlag=MouseAction;
  			break;
  		case 2:
   			MouseAction=User_SEARCH;
   			IfFlag=MouseAction;
  			break; 
  		case 3:
   			MouseAction=User_MODIFY;
   			IfFlag=MouseAction;
  			break; 	
		case 4:
			MouseAction=User_DELETE;
			IfFlag=MouseAction;
			break;
		case 5:
			MouseAction=User_COUNT;
			IfFlag=MouseAction;
			break;	
		case 6:
			WindowNum=LOGINWINDOW;
			//����ͷ�һ��UserInfo	  LoginBoard();			  			
	  }
  }
  if(0<help_choice){
  	switch(help_choice){
  		case 1:
  			MouseAction=Help_ABOUT;
  			IfFlag=MouseAction;
  			break;
  		case 2:
   			MouseAction=Help_USAGE;
   			IfFlag=MouseAction;
  			break; 		  			  			
	  }
  } 
}

/*User��ʼ����*/
/*�ǹ���Ա�˻����ܲ����ļ����������������ơ��޸ġ�ɾ����ͳ��ͼ���ļ�������ɾ�����*/ 
void InitializeUserBoard()
{ 
  double x=0.1;
  double y=0.1;
  double w=1.15;
  double wlist=1.15;
  double h=0.35;
  int file_choice,book_choice,borrowreturn_choice,user_choice,help_choice; 
  drawthebackground();
  StatusBar();
  ToolBar();
  static char *file_labels[]={"���",
  "�˳�" 
  };
  static char *book_labels[]={"ͼ��",
  "����ͼ����Ϣ",//��Ϊ������Ŀ�в˵�ϵͳͼ�鲿�ֵ���ʾ 
  };
  static char *borrowreturn_labels[]={"ͼ��軹",
  "�����鼮",
  "�黹�鼮",
  };
  static char *user_labels[]={"�û�",  
  "�޸�",
  "��������", 
  "ע��" 
  };//�������е�½ע���Ѿ��ڽ���ϵͳ֮����ɣ�����ע������ 
  static char *help_labels[]={"����",
  "���ڱ����",
  "ʹ�÷���"
  }; 
  
  file_choice=menuList(GenUIID(0),x,BOARDHEIGHT-y-h,w,wlist,h,file_labels,sizeof(file_labels)/sizeof(file_labels[0]));
  book_choice=menuList(GenUIID(0),x+w,BOARDHEIGHT-y-h,w,wlist,h,book_labels,sizeof(book_labels)/sizeof(book_labels[0]));
  borrowreturn_choice=menuList(GenUIID(0),x+w*2,BOARDHEIGHT-y-h,w,wlist,h,borrowreturn_labels,sizeof(borrowreturn_labels)/sizeof(borrowreturn_labels[0]));
  user_choice=menuList(GenUIID(0),x+w*3,BOARDHEIGHT-y-h,w,wlist,h,user_labels,sizeof(user_labels)/sizeof(user_labels[0]));
  help_choice=menuList(GenUIID(0),x+w*4,BOARDHEIGHT-y-h,w,wlist,h,help_labels,sizeof(help_labels)/sizeof(help_labels[0]));
  textbox(GenUIID(0),x+w*5,BOARDHEIGHT-y-h,3*w,h,searchtext,sizeof(searchtext));
  if(button(GenUIID(0),x+8*w,BOARDHEIGHT-y-h,0.6,h,"����")){
	IfFlag=Searchchoice_pop; //��˲��Ҵ��� 
	}
  
  if(0<file_choice){
  	switch(file_choice){ 
  		case 1://�����˳� 
   			exit(-1); 			  			  			
	  }
  }
  if(0<book_choice){
  	switch(book_choice){//���� 
  		case 1:
  			MouseAction=Book_SEARCH;
   			IfFlag=MouseAction;
  			break; 	  			  			
	  }
  }
  if(0<borrowreturn_choice){
  	switch(borrowreturn_choice){//�軹�� 
  		case 1:
  			MouseAction=Book_BORROW;
  			IfFlag=MouseAction;
  			break;
  		case 2:
   			MouseAction=Book_RETURN;
   			IfFlag=MouseAction;
  			break; 		  			
	  }
  }
  if(0<user_choice){
  	switch(user_choice){//�û����� 
  		case 1:
  			MouseAction=User_MODIFY;
   			IfFlag=MouseAction;
  			break; 	
  		case 2:
   			MouseAction=User_CENTER;
   			IfFlag=MouseAction;
  			break; 
  		case 3:
   			WindowNum=LOGINWINDOW;
			//����ͷ�һ��UserInfo	 		LoginBoard();	    			  			
	  }
  }
  if(0<help_choice){
  	switch(help_choice){//���� 
  		case 1:
  			MouseAction=Help_ABOUT;
  			IfFlag=MouseAction;
  			break;
  		case 2:
   			MouseAction=Help_USAGE;
   			IfFlag=MouseAction;
  			break; 		  			  			
	  }
  } 
}


void RespondMenuEvent()
{
	switch(MouseAction){
		case Server_CONNECT://�޸ķ����� 
			ConnectServer();
			break;
		case Book_NEW://�½�ͼ����Ϣ 
			NewTheBook();
			break;
		case Book_COPY://����ͼ����Ϣ 
			CopyTheBook();
			break;
		case Book_SEARCH://�����鼮 
			SearchSpecificBook();//��ģ��������ͬ������������ǲ����ض��鼮����Ϣ 
			break;
		case Book_MODIFY://�޸�ͼ����Ϣ 
			ModifyTheBook();
			break;
		case Book_DELETE://ɾ���鼮��Ϣ 
			DeleteTheBook();
			break;
		case Book_COUNT://ͳ���鼮��Ϣ 
			CountTheBook(); 
			break;
		case Book_BORROW://���� 
			BorrowTheBook();
			break;
		case Book_RETURN://���� 
			ReturnTheBook();
			break;
        case User_CHECK://�û���� 
        	CheckUserStatus();
        	break;
        case User_SEARCH://�û����� 
        	SearchUserInfo();
        	break;
        case User_MODIFY://�޸��û���Ϣ 
        	ModifyUserInfo();
        	break;
        case User_DELETE://ɾ���û���Ϣ 
        	DeleteUserInfo();
        	break;
        case User_COUNT://ͳ���û���Ϣ 
        	CountUserInfo();
        	break;
        case User_CENTER://�������� 
        	DisplayUserInfo();
        	break;
        case Help_ABOUT://���ڱ���� 
        	AboutHelp();
        	break;
        case Help_USAGE://ʹ���ֲ� 
        	UsageHelp();
        	break; 
        case 0://Ĭ��״̬ 
			DisplayNothing(); 
			break;
	}
}
/*������*/ 
void drawthebackground()
{
  double x=0.1;
  double y=0.1;
  double w=1.15;
  double h=0.35;
  SetPenColor("White");
  drawRectangle(0,0,BOARDWIDTH,BOARDHEIGHT,1); 
  SetPenSize(80); 
  SetPenColor("Light Gray");
  MovePen(3.5,BOARDHEIGHT-y-0.3);
  DrawLine(-4,-4);
  MovePen(3,BOARDHEIGHT-y);
  DrawLine(-4,-4);
  SetPenSize(60); 
  MovePen(BOARDWIDTH-4.5,-1);
  DrawLine(5,5);
  SetPenSize(85); 
  SetPenColor("White");
  MovePen(3,BOARDHEIGHT-y-0.35);
  DrawLine(-4,-4);
  MovePen(2.5,BOARDHEIGHT-y);
  DrawLine(-4,-4);
  SetPenColor("IndianRed2");
  SetPenSize(100);
  MovePen(2.4,BOARDHEIGHT-y-0.35);
  DrawLine(-2,-2);
  MovePen(1.7,BOARDHEIGHT-y);
  DrawLine(-2,-2);
  MovePen(0.8,BOARDHEIGHT-y);
  DrawLine(-2,-2);
  MovePen(BOARDWIDTH-3,-1);
  DrawLine(2.5,2.5);
  DrawLine(0.6,-0.6);
  DrawLine(-1,-1);
  SetPenColor("White");
  SetPenSize(15);
  drawRectangle(0,0,BOARDWIDTH,BOARDHEIGHT,0);
  SetPenSize(1);
  SetPenColor("WhiteSmoke");
  drawRectangle(x,BOARDHEIGHT-y-h,BOARDWIDTH-2*x,h,1);
  SetPenColor("Black");
  SetPenSize(2);
  drawRectangle(x,y,BOARDWIDTH-2*x,BOARDHEIGHT-2*y,0);
  MovePen(x,BOARDHEIGHT-y-h);
  DrawLine(BOARDWIDTH-2*x,0);
  SetPenSize(1);
}
/*ͼ�깤����*/ 
void ToolBar(){
	double x=0.1;
  	double y=0.1;
    double wi=0.35;
  	double h=0.35;
  	setButtonColors("Light Gray", "MidnightBlue", "Light Gray", "MidnightBlue", 1);
  	if(button(GenUIID(0),x,y,wi,h,"B")){
		IfFlag=Book_BORROW; 
	} 
	setButtonColors("Light Gray", "MidnightBlue", "Light Gray", "MidnightBlue", 1);
	if(button(GenUIID(0),x+wi,y,wi,h,"R")){
		IfFlag=Book_RETURN; 
	}
	setButtonColors("Light Gray", "MidnightBlue", "Light Gray", "MidnightBlue", 1);
	if(button(GenUIID(0),x+wi*2,y,wi,h,"S")){
		IfFlag=Book_SEARCH; 
	}
	setButtonColors("Light Gray", "MidnightBlue", "Light Gray", "MidnightBlue", 1);
	if(button(GenUIID(0),x+wi*3,y,wi,h,"M")){
		IfFlag=User_MODIFY; 
	}
	setButtonColors("Light Gray", "MidnightBlue", "Light Gray", "MidnightBlue", 1);
	if(button(GenUIID(0),x+wi*4,y,wi,h,"H")){
		IfFlag=Help_USAGE; 
	}	 
} 
/*״̬��*/ 
void StatusBar(){
	double x=0.1;
  	double y=0.1;
    double w=BOARDWIDTH-2*x-0.35*5;
  	double h=0.35;
  	SetPenColor("WhiteSmoke");
	drawRectangle(x,y,BOARDWIDTH-2*x,h,1);
	SetPenColor("Black");
	drawRectangle(x,y,BOARDWIDTH-2*x,h,0);
	drawRectangle(x+0.35*5,y,w,h,0);
	switch(STATUS){
		case LoginSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"��¼�ɹ���");
			break;
		/*case UserNameNotFind:
		 	drawLabel(x+0.35*5+0.1,y+0.15,"δ�ҵ��û�����");
		 	break; �������ͺ�����û����������� ����ɾ��*/ 
		case PasswordError:
			drawLabel(x+0.35*5+0.1,y+0.15,"�������");
			break;
		case SignUpSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"ע��ɹ���");
			break;
		case RepeatedUserName:
			drawLabel(x+0.35*5+0.1,y+0.15,"�û����Ѵ��ڣ�");
			break;
		case InsecurePassword:
			drawLabel(x+0.35*5+0.1,y+0.15,"����ǿ�ȹ�����");
			break;
		case NFSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"�½��ļ��ɹ���");
			break;
		case NFFail:
			drawLabel(x+0.35*5+0.1,y+0.15,"�½��ļ�ʧ�ܣ�");
			break;
		case OFSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"�ļ��򿪳ɹ���");
			break;
		case FileNotFind:
			drawLabel(x+0.35*5+0.1,y+0.15,"δ�ҵ����ļ���");
			break;
		case SFSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"�ļ�����ɹ���");
			break;
		case SFFail:
			drawLabel(x+0.35*5+0.1,y+0.15,"�ļ�����ʧ�ܣ�");
			break;
		case CFSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"�ļ��ѹرգ�");
			break;
		case BookNotFind:
			drawLabel(x+0.35*5+0.1,y+0.15,"δ�ҵ���ͼ�飡");
			break;
		case UnmatchedIDName:
			drawLabel(x+0.35*5+0.1,y+0.15,"�����������ƥ�䣡");
			break;
		case NBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"����ͼ��ɹ���");
			break;
		case NBFail:
			drawLabel(x+0.35*5+0.1,y+0.15,"ͼ����Ϣ���������޷�������⣡");
			break;
		case CBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"ͼ����Ϣ�Ѹ��Ʋ��ɹ�����������У�");
			break;
		case SBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"����ͼ��������ʾ��");
			break;
		case MBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"�޸�ͼ����Ϣ�ɹ���");
			break;
		case DBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"ɾ��ͼ����Ϣ�ɹ���");
			break;
		case COBSucess:
			drawLabel(x+0.35*5+0.1,y+0.15,"ͼ���Ѱ��շ��ࡢ��ͨ��Ϣͳ�ƣ�");
			break;
		case BorrowSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"���ĳɹ�������30���ڹ黹�����򽫰���0.2Ԫ/����ȡ���ڷ��á�");
			break;
		case BookUnavailable:
			drawLabel(x+0.35*5+0.1,y+0.15,"��治�㣡");
			break;
		case ReturnSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"����ɹ���");
			break;
		case BookOverdue:
			drawLabel(x+0.35*5+0.1,y+0.15,"�ѳ����黹���ޣ������˹�����̨�������ڷ���");//֧�����������ʱ��Ļ����������Զ�ɨ��ɷѣ��Ҿ��Ȱ����˹���д�� 
			break;
		case UserNotfind:
			drawLabel(x+0.35*5+0.1,y+0.15,"�û������ڣ�");
			break;
		case UnmatchedUIDName:
			drawLabel(x+0.35*5+0.1,y+0.15,"�û�����ID��ƥ�䣡");
			break;
		case SearchUserSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"�����û��ɹ���");
			break;
		case ModifyUserSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"�޸��û���Ϣ�ɹ���");
			break;
		case DeleteUserSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"ɾ���û���Ϣ�ɹ���");
			break;
		case CountUserSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"����ʾ�û�ͳ����Ϣ��");
			break;
		case DeniedPermission:
			drawLabel(x+0.35*5+0.1,y+0.15,"ע��Ȩ�޲��㣡");
			break;
		case AuthorizeFail:
		    drawLabel(x+0.35*5+0.1,y+0.15,"�����˻���֤ʧ�ܣ�");
			break; 
		default:
			drawLabel(x+0.35*5+0.1,y+0.15,"Copyright @ 2020 Group 26(Haoyuan MA, Yongqi ZHAO, Xinguo FANG) All Rights Reserved");
		 	break;
	}
}

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); /*��ȡ�����Ϣ*/ 
    Display();	/*ˢ�½�����ʾ*/ 
}

void CharEventProcess(char ch)
{
	uiGetChar(ch); /*�ַ�����*/ 
	textbox(GenUIID(0),3+0.2,3+0.5,3.5-0.2*2,0.4,NFtextbuf, sizeof(NFtextbuf));
	DisplayClear();
	textbox(GenUIID(0),3+0.2,3+0.5,3.5-0.2*2,0.4,NFtextbuf, sizeof(NFtextbuf));
	Display(); /*ˢ�½�����ʾ*/ 
}

void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key,event); 
    switch (event) {
	 	case KEY_DOWN:
			 switch (key) {
			     case VK_F1:/*F1�û����*/
					 IfFlag=User_CHECK;
					 Display();
					 break; 
			     case VK_F2:/*F2�û�����*/
			     	 IfFlag=User_SEARCH;
			     	 Display();
                     break;
                 case VK_F3:/*F3�û��޸�*/
			     	 IfFlag=User_MODIFY;
			     	 Display();
                     break;  
				 case VK_F4:/*F4�û�ɾ��*/
			     	 IfFlag=User_DELETE;
			     	 Display();
                     break; 
				case VK_F5:/*F5�û�ע��*/
			     	 WindowNum=LOGINWINDOW;
			     	 IfFlag=0;
			     	 Display();
                     break; 
			}
        case KEY_UP:
		break;
		}
    Display(); /*ˢ�½�����ʾ*/
}

void Display()
{
	DisplayClear();
	if(WELCOMEWINDOW==WindowNum){
		 WelcomeBoard();
	}
	else if(LOGINWINDOW==WindowNum){
		LoginBoard();
	}
	else if(ADMINWINDOW==WindowNum){
		 InitializeAdminBoard();              
         RespondMenuEvent();	
	} 
	else if(USERWINDOW==WindowNum){
		 InitializeUserBoard();              
         RespondMenuEvent();
	}
	switch(IfFlag){
		case 0:
        	DisplayNothing();
            break;
		case SignUp_pop:
			drawSignUppop(); 
			break;
		case Searchchoice_pop:
			drawSearchchoicepop();
			break; 
		case Search_pop:
			drawSearchpop(); 
			break;
		case Server_CONNECT:
			ConnectServer();
			break;
		case Book_NEW:
			NewTheBook();
			break;
		case Book_COPY:
			CopyTheBook();
			break;
		case Book_SEARCH:
			SearchSpecificBook();
			break;
		case Book_SEARCH_pop:
			SearchBookpop();
			break;
		case Book_MODIFY:
			ModifyTheBook();
			break;
		case Book_MODIFY_pop:
			ModifyBookpop();
			break;
		case Book_DELETE:
			DeleteTheBook();
			break;
		case Book_BORROW:
			BorrowTheBook();
			break;
		case Book_RETURN:
			ReturnTheBook();
			break;
        case User_LOGIN:
        	LoginBoard();
        	break;
        case User_CHECK:
        	CheckUserStatus();
        	break;
        case User_SEARCH:
        	SearchUserInfo();
        	break;
        case User_SEARCH_pop:
        	SearchUserInfopop();
        	break;
        case User_COUNTBorrow_pop:
			CountBorrowHistory();
			break; 
        case User_MODIFY:
        	ModifyUserInfo();
        	break;
        case User_MODIFY_pop:
        	ModifyUserInfoPop();
        	break;
        case User_DELETE:
        	DeleteUserInfo();
        	break;
        case User_COUNT:
        	CountUserInfo();
        	break;
        case User_COUNT_pop:
			CountUserInfopop(); 
			break; 
        case User_CENTER:
        	DisplayUserInfo();
        	break;
        case Help_ABOUT:
        	AboutHelp();
        	break;
        case Help_USAGE:
        	UsageHelp();
        	break; 
    }
}

/*������ע��ҳ��*/
void drawSignUppop()
{
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
	drawLabel(x+0.1,y+hx+0.15,"ע ��"); 
	drawLabel(x+0.5,y+0.9+d*5,"�û���");//Ĭ�ϲ����ظ� 
	drawLabel(x+0.5,y+0.9+d*4,"�� ��");//�������벻���ܵĻ�������������һ��ȷ������ 
	drawLabel(x+0.5,y+0.9+d*3,"�� ��");
	drawLabel(x+0.5,y+0.9+2*d,"�� λ");
	drawLabel(x+0.5,y+0.9+1*d,"Ȩ ��");
	SetPenColor("Gray");
	drawLabel(x+0.2,y+0.9+0.15,"*Ȩ����дUSER����ADMIN"); 
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*5,1.2,0.25,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*4,1.2,0.25,userinfoPasswordsSwap,sizeof(userinfoPasswordsSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*3,1.2,0.25,userinfoGenderSwap,sizeof(userinfoGenderSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*2,1.2,0.25,userinfoDepartmentSwap,sizeof(userinfoDepartmentSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*1,1.2,0.25,userinfoModeSwap,sizeof(userinfoModeSwap));
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=User_LOGIN;//�����Ͻ� ���رյ��� 
	}
	if(button(GenUIID(0),x+1.15,y+0.3,0.8,0.25,"ȷ��ע��")){
		/*��ˣ�ע���û���Ϣ����¼ */
		USERS *temp;
		temp=(USERS*)calloc(1,sizeof(USERS));     //����һ���û���Ϣ�������û��������� 
		temp->username=(char*)calloc(SWAP_LIMIT,sizeof(char));
		temp->passwords=(char*)calloc(SWAP_LIMIT,sizeof(char));
		temp->gender=(char*)calloc(SWAP_LIMIT,sizeof(char));
		temp->department=(char*)calloc(SWAP_LIMIT,sizeof(char));
		temp->mode=(char*)calloc(SWAP_LIMIT,sizeof(char));
		strcpy(temp->username,userinfoUsernameSwap);
		strcpy(temp->passwords,userinfoPasswordsSwap);
		strcpy(temp->gender,userinfoGenderSwap);
		strcpy(temp->department,userinfoDepartmentSwap);
		strcpy(temp->mode,userinfoModeSwap);
		int result;        //��¼ע���� 
		result=AU_createNewUser(DATABASE,temp,UserInfo);     //���յ�ǰ�û���Ȩ���½��û�
		if(result==SUCCESS){     //ע��ɹ�
			STATUS=SignUpSuccess; 
			freeSingleUser(UserInfo);       //�ͷ�ԭ����¼�û�����Ϣ�ڴ� 
			UserInfo=temp;             //ָ���µĽ�� 
			if(UserInfo->mode=="ADMIN")WindowNum=ADMINWINDOW;   //�������ȷ������Ľ��� 
			else WindowNum=USERWINDOW; 
		}
		else if(result==PERMISSION_DENIED){    //ע��Ȩ�޲��� 
			STATUS=DeniedPermission;
		}
		else if(result==USERNAME_REPEATED){     //�û����Ѵ��� 
			STATUS=RepeatedUserName; 
		}
		else if(result==AUTHORIZE_FAILED){      //����Ա�˻���֤ʧ�� 
			STATUS=AuthorizeFail;
		}
		/*change begin*/
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

