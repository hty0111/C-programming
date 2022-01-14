#include "SIMS.h"
extern int MouseAction;
extern int WindowNum;//初始界面为欢迎界面 
extern int IfFlag;//初始显示状态为默认值 
extern int STATUS;//初始状态栏为空 
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
	/*初始化窗口和图形系统*/ 
	SetWindowTitle("图书管理系统");
	SetWindowSize(BOARDWIDTH,BOARDHEIGHT);//设置窗口大小 
	InitGraphics();
	WindowNum = WELCOMEWINDOW;//初始窗口为欢迎界面 
	if(WELCOMEWINDOW==WindowNum){
		 WelcomeBoard();//欢迎界面 
	}
	else if(LOGINWINDOW==WindowNum){
		LoginBoard();//登陆界面 
	}
	else if(ADMINWINDOW==WindowNum){
		 InitializeAdminBoard();              
         RespondMenuEvent();	//管理员界面 
	} 
	else if(USERWINDOW==WindowNum){
		 InitializeUserBoard();              
         RespondMenuEvent();    //用户界面 
	}
   
    /*注册时间响应函数*/ 
	registerCharEvent(CharEventProcess); /*字符*/ 
	registerKeyboardEvent(KeyboardEventProcess);/*键盘*/ 
	registerMouseEvent(MouseEventProcess);      /*鼠标*/ 
}

/*启动页面*/ 
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
    drawLabel(2.4+0.05,3.5-0.05,"图书管理系统");
    SetPointSize(60);
    SetPenColor("Firebrick1");
    drawLabel(2.4+0.03,3.5,"图书管理系统");
    drawLabel(2.4-0.03,3.5,"图书管理系统");
    drawLabel(2.4,3.5+0.03,"图书管理系统");
    drawLabel(2.4,3.5-0.03,"图书管理系统");
    drawLabel(2.4+0.02,3.5+0.02,"图书管理系统");
    drawLabel(2.4+0.02,3.5-0.02,"图书管理系统");
    drawLabel(2.4-0.02,3.5+0.02,"图书管理系统");
    drawLabel(2.4-0.02,3.5-0.02,"图书管理系统");
    SetPenColor("White");
    drawLabel(2.4,3.5,"图书管理系统"); 
    drawLabel(2.4+0.01,3.5,"图书管理系统");
    drawLabel(2.4-0.01,3.5,"图书管理系统");
    drawLabel(2.4,3.5+0.01,"图书管理系统");
    drawLabel(2.4,3.5-0.01,"图书管理系统");//图书管理系统标题艺术字 
    SetPenColor("Seashell");
    drawRectangle(3.4,1.6,2.8,0.5,1);
	SetPointSize(23); 
	if(button(GenUIID(0),3.3,1.5,3,0.7,"进      入")){
		WindowNum=LOGINWINDOW; //点击进入之后跳转进入登陆界面 
	}
	SetPointSize(1); 
}

/*登录界面*/
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
	drawLabel(x,y,"用户名");
	drawLabel(x,y-d,"密 码");
	SetPointSize(1);
	textbox(GenUIID(0),x+1,y-0.1,w,h,userinfoUsernameSwap,sizeof(userinfoUsernameSwap)); 
	textbox(GenUIID(0),x+1,y-0.1-d,w,h,userinfoPasswordsSwap,sizeof(userinfoPasswordsSwap));
	if(button(GenUIID(0),x+0.6,y-d*2,1,0.35,"登  录")){
		/*后端检验登陆账号密码是否一致，是否是管理员模式，
		如果是管理员模式 WindowNum=ADMINWINDOW, 学生模式 WindowNum=USERWINDOW
		如果身份信息验证失败，弹出相应指示,可写在 StatusBar里面*/ 
		int result;             //储存身份验证结果 
		result=userLogIn(DATABASE,userinfoUsernameSwap,userinfoPasswordsSwap);
		drawLabel(x,y-d*2-0.25,userinfoUsernameSwap);
		if(result==LOG_IN_SUCCESS){   //登录成功 
			STATUS=LoginSuccess;
			if(UserInfo!=NULL)freeSingleUser(UserInfo);   //先释放上一个用户的信息内存 
			UserInfo=(USERS*)calloc(1,sizeof(USERS));     //创建一个用户信息结点存入用户名和密码 
			UserInfo->username=(char*)calloc(SWAP_LIMIT,sizeof(char));
			UserInfo->passwords=(char*)calloc(SWAP_LIMIT,sizeof(char)); 
			strcpy(UserInfo->username,userinfoUsernameSwap);
			strcpy(UserInfo->passwords,userinfoPasswordsSwap);
			USERS *temp=UserInfo;
			UserInfo=AU_getUserInfo(DATABASE,UserInfo->username,UserInfo);   //获取当前登录用户的信息 
			freeSingleUser(temp);      //释放登入时记录用户名密码的内存 
			if(strcmp(UserInfo->mode,"ADMIN")==0)WindowNum=ADMINWINDOW;   //根据得到的用户身份信息判断进入什么界面 
			else WindowNum=USERWINDOW; 
		}
		else if(result==PASSWORDS_ERROR){    //密码错误 
			STATUS=PasswordError;
		}
		else if(result==USERNAME_NOT_FOUND){    //用户名不存在 
			STATUS=UserNotfind;
		}
		/*change begin*/
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
	if(button(GenUIID(0),x+2.2,y-d*2,1,0.35,"注  册")){
		IfFlag=SignUp_pop;//后端注册代码，注册成功之后无需输账号密码直接登录 
	}	 	 
	SetPenColor("Gray");
	drawLabel(x,y-d*2-0.25,"＊如果您没有图书管理系统账号，请注册");		
} 
 
/*Admin初始界面*/ 
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
  static char *file_labels[]={"连接",
  "修改",//修改服务器 
  "关闭" //退出程序 
  };
  static char *book_labels[]={"图书",
  "新增图书信息",
  "复制图书信息", 
  "查阅图书信息",//即为考评项目中菜单系统图书部分的显示 
  "修改图书信息",
  "删除图书信息",
  "图书信息统计" 
  };
  static char *borrowreturn_labels[]={"图书借还",
  "借阅书籍",
  "归还书籍",
  };
  static char *user_labels[]={"用户", 
  "审核 | F1", 
  "查找 | F2 ",
  "修改 | F3 ",
  "删除 | F4", 
  "用户数据统计",
  "注销 | F5" 
  };//考评项中登陆注册已经在进入系统之后完成，新增注销功能 
  static char *help_labels[]={"帮助",
  "关于本软件",
  "使用方法"
  }; 
  
  file_choice=menuList(GenUIID(0),x,BOARDHEIGHT-y-h,w,wlist,h,file_labels,sizeof(file_labels)/sizeof(file_labels[0]));
  book_choice=menuList(GenUIID(0),x+w,BOARDHEIGHT-y-h,w,wlist,h,book_labels,sizeof(book_labels)/sizeof(book_labels[0]));
  borrowreturn_choice=menuList(GenUIID(0),x+w*2,BOARDHEIGHT-y-h,w,wlist,h,borrowreturn_labels,sizeof(borrowreturn_labels)/sizeof(borrowreturn_labels[0]));
  user_choice=menuList(GenUIID(0),x+w*3,BOARDHEIGHT-y-h,w,wlist,h,user_labels,sizeof(user_labels)/sizeof(user_labels[0]));
  help_choice=menuList(GenUIID(0),x+w*4,BOARDHEIGHT-y-h,w,wlist,h,help_labels,sizeof(help_labels)/sizeof(help_labels[0]));
  textbox(GenUIID(0),x+w*5,BOARDHEIGHT-y-h,3*w,h,searchtext,sizeof(searchtext));
  if(button(GenUIID(0),x+8*w,BOARDHEIGHT-y-h,0.6,h,"搜索")){
	IfFlag=Searchchoice_pop; //后端查找代码 
	}
  
  if(0<file_choice){
  	switch(file_choice){
  		case 1://点击“修改”，修改服务器 
  			MouseAction=Server_CONNECT;
  			IfFlag=MouseAction;
  			break;
  		case 2://点击“关闭”，退出系统 
   			exit(-1); 		  			  			
	  }
  }
  if(0<book_choice){
  	switch(book_choice){
  		case 1:
  			MouseAction=Book_NEW;//新增图书信息，后面的情况根据菜单顺序类推 
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
  		case 1://借书 
  			MouseAction=Book_BORROW;
  			IfFlag=MouseAction;
  			break;
  		case 2://还书 
   			MouseAction=Book_RETURN;
   			IfFlag=MouseAction;
  			break; 		  			
	  }
  }
  if(0<user_choice){
  	switch(user_choice){//用户操作 
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
			//后端释放一下UserInfo	  LoginBoard();			  			
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

/*User初始界面*/
/*非管理员账户不能操作文件，不能新增、复制、修改、删除、统计图书文件，不能删除审核*/ 
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
  static char *file_labels[]={"软件",
  "退出" 
  };
  static char *book_labels[]={"图书",
  "查阅图书信息",//即为考评项目中菜单系统图书部分的显示 
  };
  static char *borrowreturn_labels[]={"图书借还",
  "借阅书籍",
  "归还书籍",
  };
  static char *user_labels[]={"用户",  
  "修改",
  "个人中心", 
  "注销" 
  };//考评项中登陆注册已经在进入系统之后完成，新增注销功能 
  static char *help_labels[]={"帮助",
  "关于本软件",
  "使用方法"
  }; 
  
  file_choice=menuList(GenUIID(0),x,BOARDHEIGHT-y-h,w,wlist,h,file_labels,sizeof(file_labels)/sizeof(file_labels[0]));
  book_choice=menuList(GenUIID(0),x+w,BOARDHEIGHT-y-h,w,wlist,h,book_labels,sizeof(book_labels)/sizeof(book_labels[0]));
  borrowreturn_choice=menuList(GenUIID(0),x+w*2,BOARDHEIGHT-y-h,w,wlist,h,borrowreturn_labels,sizeof(borrowreturn_labels)/sizeof(borrowreturn_labels[0]));
  user_choice=menuList(GenUIID(0),x+w*3,BOARDHEIGHT-y-h,w,wlist,h,user_labels,sizeof(user_labels)/sizeof(user_labels[0]));
  help_choice=menuList(GenUIID(0),x+w*4,BOARDHEIGHT-y-h,w,wlist,h,help_labels,sizeof(help_labels)/sizeof(help_labels[0]));
  textbox(GenUIID(0),x+w*5,BOARDHEIGHT-y-h,3*w,h,searchtext,sizeof(searchtext));
  if(button(GenUIID(0),x+8*w,BOARDHEIGHT-y-h,0.6,h,"搜索")){
	IfFlag=Searchchoice_pop; //后端查找代码 
	}
  
  if(0<file_choice){
  	switch(file_choice){ 
  		case 1://程序退出 
   			exit(-1); 			  			  			
	  }
  }
  if(0<book_choice){
  	switch(book_choice){//搜书 
  		case 1:
  			MouseAction=Book_SEARCH;
   			IfFlag=MouseAction;
  			break; 	  			  			
	  }
  }
  if(0<borrowreturn_choice){
  	switch(borrowreturn_choice){//借还书 
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
  	switch(user_choice){//用户操作 
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
			//后端释放一下UserInfo	 		LoginBoard();	    			  			
	  }
  }
  if(0<help_choice){
  	switch(help_choice){//帮助 
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
		case Server_CONNECT://修改服务器 
			ConnectServer();
			break;
		case Book_NEW://新建图书信息 
			NewTheBook();
			break;
		case Book_COPY://复制图书信息 
			CopyTheBook();
			break;
		case Book_SEARCH://搜索书籍 
			SearchSpecificBook();//与模糊搜索不同，这里的搜索是查阅特定书籍的信息 
			break;
		case Book_MODIFY://修改图书信息 
			ModifyTheBook();
			break;
		case Book_DELETE://删除书籍信息 
			DeleteTheBook();
			break;
		case Book_COUNT://统计书籍信息 
			CountTheBook(); 
			break;
		case Book_BORROW://借书 
			BorrowTheBook();
			break;
		case Book_RETURN://还书 
			ReturnTheBook();
			break;
        case User_CHECK://用户审核 
        	CheckUserStatus();
        	break;
        case User_SEARCH://用户搜索 
        	SearchUserInfo();
        	break;
        case User_MODIFY://修改用户信息 
        	ModifyUserInfo();
        	break;
        case User_DELETE://删除用户信息 
        	DeleteUserInfo();
        	break;
        case User_COUNT://统计用户信息 
        	CountUserInfo();
        	break;
        case User_CENTER://个人中心 
        	DisplayUserInfo();
        	break;
        case Help_ABOUT://关于本软件 
        	AboutHelp();
        	break;
        case Help_USAGE://使用手册 
        	UsageHelp();
        	break; 
        case 0://默认状态 
			DisplayNothing(); 
			break;
	}
}
/*画背景*/ 
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
/*图标工具栏*/ 
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
/*状态栏*/ 
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
			drawLabel(x+0.35*5+0.1,y+0.15,"登录成功！");
			break;
		/*case UserNameNotFind:
		 	drawLabel(x+0.35*5+0.1,y+0.15,"未找到用户名！");
		 	break; 这里好像和后面的用户不存在类似 可以删掉*/ 
		case PasswordError:
			drawLabel(x+0.35*5+0.1,y+0.15,"密码错误！");
			break;
		case SignUpSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"注册成功！");
			break;
		case RepeatedUserName:
			drawLabel(x+0.35*5+0.1,y+0.15,"用户名已存在！");
			break;
		case InsecurePassword:
			drawLabel(x+0.35*5+0.1,y+0.15,"密码强度过弱！");
			break;
		case NFSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"新建文件成功！");
			break;
		case NFFail:
			drawLabel(x+0.35*5+0.1,y+0.15,"新建文件失败！");
			break;
		case OFSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"文件打开成功！");
			break;
		case FileNotFind:
			drawLabel(x+0.35*5+0.1,y+0.15,"未找到该文件！");
			break;
		case SFSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"文件保存成功！");
			break;
		case SFFail:
			drawLabel(x+0.35*5+0.1,y+0.15,"文件保存失败！");
			break;
		case CFSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"文件已关闭！");
			break;
		case BookNotFind:
			drawLabel(x+0.35*5+0.1,y+0.15,"未找到该图书！");
			break;
		case UnmatchedIDName:
			drawLabel(x+0.35*5+0.1,y+0.15,"书号与书名不匹配！");
			break;
		case NBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"新增图书成功！");
			break;
		case NBFail:
			drawLabel(x+0.35*5+0.1,y+0.15,"图书信息不完整，无法加入书库！");
			break;
		case CBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"图书信息已复制并成功新增到书库中！");
			break;
		case SBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"查阅图书结果已显示！");
			break;
		case MBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"修改图书信息成功！");
			break;
		case DBSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"删除图书信息成功！");
			break;
		case COBSucess:
			drawLabel(x+0.35*5+0.1,y+0.15,"图书已按照分类、流通信息统计！");
			break;
		case BorrowSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"借阅成功！请在30天内归还，否则将按照0.2元/天收取逾期费用。");
			break;
		case BookUnavailable:
			drawLabel(x+0.35*5+0.1,y+0.15,"库存不足！");
			break;
		case ReturnSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"还书成功！");
			break;
		case BookOverdue:
			drawLabel(x+0.35*5+0.1,y+0.15,"已超过归还期限，请至人工服务台缴纳逾期费用");//支付这里如果有时间的话可以做成自动扫码缴费，我就先按照人工的写了 
			break;
		case UserNotfind:
			drawLabel(x+0.35*5+0.1,y+0.15,"用户不存在！");
			break;
		case UnmatchedUIDName:
			drawLabel(x+0.35*5+0.1,y+0.15,"用户名和ID不匹配！");
			break;
		case SearchUserSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"搜索用户成功！");
			break;
		case ModifyUserSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"修改用户信息成功！");
			break;
		case DeleteUserSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"删除用户信息成功！");
			break;
		case CountUserSuccess:
			drawLabel(x+0.35*5+0.1,y+0.15,"已显示用户统计信息！");
			break;
		case DeniedPermission:
			drawLabel(x+0.35*5+0.1,y+0.15,"注册权限不足！");
			break;
		case AuthorizeFail:
		    drawLabel(x+0.35*5+0.1,y+0.15,"管理账户认证失败！");
			break; 
		default:
			drawLabel(x+0.35*5+0.1,y+0.15,"Copyright @ 2020 Group 26(Haoyuan MA, Yongqi ZHAO, Xinguo FANG) All Rights Reserved");
		 	break;
	}
}

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); /*获取鼠标信息*/ 
    Display();	/*刷新界面显示*/ 
}

void CharEventProcess(char ch)
{
	uiGetChar(ch); /*字符输入*/ 
	textbox(GenUIID(0),3+0.2,3+0.5,3.5-0.2*2,0.4,NFtextbuf, sizeof(NFtextbuf));
	DisplayClear();
	textbox(GenUIID(0),3+0.2,3+0.5,3.5-0.2*2,0.4,NFtextbuf, sizeof(NFtextbuf));
	Display(); /*刷新界面显示*/ 
}

void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key,event); 
    switch (event) {
	 	case KEY_DOWN:
			 switch (key) {
			     case VK_F1:/*F1用户审核*/
					 IfFlag=User_CHECK;
					 Display();
					 break; 
			     case VK_F2:/*F2用户查找*/
			     	 IfFlag=User_SEARCH;
			     	 Display();
                     break;
                 case VK_F3:/*F3用户修改*/
			     	 IfFlag=User_MODIFY;
			     	 Display();
                     break;  
				 case VK_F4:/*F4用户删除*/
			     	 IfFlag=User_DELETE;
			     	 Display();
                     break; 
				case VK_F5:/*F5用户注销*/
			     	 WindowNum=LOGINWINDOW;
			     	 IfFlag=0;
			     	 Display();
                     break; 
			}
        case KEY_UP:
		break;
		}
    Display(); /*刷新界面显示*/
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

/*弹出的注册页面*/
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
	drawLabel(x+0.1,y+hx+0.15,"注 册"); 
	drawLabel(x+0.5,y+0.9+d*5,"用户名");//默认不可重复 
	drawLabel(x+0.5,y+0.9+d*4,"密 码");//密码输入不加密的话，无需再输入一次确认密码 
	drawLabel(x+0.5,y+0.9+d*3,"性 别");
	drawLabel(x+0.5,y+0.9+2*d,"单 位");
	drawLabel(x+0.5,y+0.9+1*d,"权 限");
	SetPenColor("Gray");
	drawLabel(x+0.2,y+0.9+0.15,"*权限填写USER或者ADMIN"); 
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*5,1.2,0.25,userinfoUsernameSwap,sizeof(userinfoUsernameSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*4,1.2,0.25,userinfoPasswordsSwap,sizeof(userinfoPasswordsSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*3,1.2,0.25,userinfoGenderSwap,sizeof(userinfoGenderSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*2,1.2,0.25,userinfoDepartmentSwap,sizeof(userinfoDepartmentSwap));
	textbox(GenUIID(0),x+1.3,y+0.9-0.07+d*1,1.2,0.25,userinfoModeSwap,sizeof(userinfoModeSwap));
	if(button(GenUIID(0),x+w-0.3,y+hx+0.1,0.2,0.2,"X")){
		IfFlag=User_LOGIN;//点右上角 ×关闭弹窗 
	}
	if(button(GenUIID(0),x+1.15,y+0.3,0.8,0.25,"确认注册")){
		/*后端：注册用户信息并登录 */
		USERS *temp;
		temp=(USERS*)calloc(1,sizeof(USERS));     //创建一个用户信息结点存入用户名和密码 
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
		int result;        //记录注册结果 
		result=AU_createNewUser(DATABASE,temp,UserInfo);     //按照当前用户的权限新建用户
		if(result==SUCCESS){     //注册成功
			STATUS=SignUpSuccess; 
			freeSingleUser(UserInfo);       //释放原来登录用户的信息内存 
			UserInfo=temp;             //指向新的结点 
			if(UserInfo->mode=="ADMIN")WindowNum=ADMINWINDOW;   //根据身份确定进入的界面 
			else WindowNum=USERWINDOW; 
		}
		else if(result==PERMISSION_DENIED){    //注册权限不足 
			STATUS=DeniedPermission;
		}
		else if(result==USERNAME_REPEATED){     //用户名已存在 
			STATUS=RepeatedUserName; 
		}
		else if(result==AUTHORIZE_FAILED){      //管理员账户认证失败 
			STATUS=AuthorizeFail;
		}
		/*change begin*/
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

