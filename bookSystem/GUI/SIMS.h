#include "extgraph.h"
#include "gcalloc.h"
#include "genlib.h"
#include "graphics.h"
#include "random.h"
#include "simpio.h"
#include "strlib.h"
#include "imgui.h"
#include "dataDeal.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define BOARDWIDTH 10 /* 图书管理系统界面的宽度 */ 
#define BOARDHEIGHT 6 /* 图书管理系统界面的高度 */
#define WELCOMEWINDOW 1 /* 欢迎界面 */
#define LOGINWINDOW 2 /* 登陆界面 */ 
#define ADMINWINDOW 3 /* 管理员界面 */ 
#define USERWINDOW 4 /*用户界面*/
#define SIZEOFARRAY 40 
#define SWAP_LIMIT 512
#define DATABASE "databaseName"

/*枚举类型*/ 
typedef enum {
	SignUp_pop=32,
	Search_pop,
	Server_CONNECT,
	File_EXIT,
    Book_NEW,
    Book_COPY,
    Book_SEARCH,
    Book_MODIFY,
    Book_DELETE,
    Book_COUNT,
    Book_BORROW,
    Book_RETURN,
    User_CHECK,
    User_SEARCH,
    User_MODIFY,
    User_DELETE,
    User_RANK,
	User_COUNT,
	User_CENTER,
	User_LOGIN,
    Help_ABOUT,
    Help_USAGE,
	Book_SEARCH_pop,
	Book_MODIFY_pop,
	Book_COUNT_pop,
	User_COUNT_pop,
	User_COUNTBorrow_pop,
	User_SEARCH_pop,
	User_MODIFY_pop,
	Searchchoice_pop
}Function_CHOICE; 

/*StatusBar的状态枚举*/
typedef enum{
	LoginSuccess=1,//成功登录 
	UserNameNotFind,//未找到用户名 
	DeniedPermission,//注册权限不足
	AuthorizeFail,// 管理账户认证失败
	PasswordError,//密码错误 
	SignUpSuccess,//注册成功 
	RepeatedUserName,//用户名已试用 
	InsecurePassword,//密码强度太弱  
	NFSuccess,//新建文件 
	NFFail,
	OFSuccess,//打开文件 
	FileNotFind,
	SFSuccess,//保存文件 
	SFFail,
	CFSuccess,//关闭文件 
	BookNotFind,
	UnmatchedIDName,//
	NBSuccess,//新增书籍 
	NBFail,
	CBSuccess,//复制书籍 
	SBSuccess,//查阅书籍 
	MBSuccess,//修改书籍 
	DBSuccess,//删除书籍 
	COBSucess,//统计 
	BorrowSuccess,//借阅 
	BookUnavailable,//无库存 
	ReturnSuccess,//归还 
	BookOverdue,//超过还书期限去人工服务处缴逾期费用 
	UserNotfind,//关于User的操作如果是失败的话就应该只有找不到用户和id用户名不匹配两种问题 
	UnmatchedUIDName, 
	SearchUserSuccess,
	ModifyUserSuccess,
	DeleteUserSuccess,
	CountUserSuccess		
}Status_CHOICE; 

void InitializeUserBoard(); /* 初始化用户界面 */
void InitializeAdminBoard(); /* 初始化管理员界面 */
void WelcomeBoard(); /* 显示欢迎界面 */ 
void LoginBoard(); /* 登录界面 */ 
void Refresh(); /* 刷新界面函数 */
void drawthebackground(); /*画背景函数*/
void StatusBar(); /*状态栏函数*/ 
void ToolBar(); /*图标工具栏*/ 
void KeyboardEventProcess(int key,int event); /* 键盘消息回调函数 */
void MouseEventProcess(int x, int y, int button, int event); /* 鼠标消息回调函数 */
void CharEventProcess(char c); /* 字符消息回调函数 */
void RespondMenuEvent(); /* 响应菜单事件 */ 

void drawSignUppop();
void drawSearchpop(); 
void drawSearchchoicepop();
void ConnectServer();
void CountTheBook();
void NewTheBook();
void CopyTheBook();
void SearchSpecificBook();
void SearchBookpop();
void ModifyTheBook();
void ModifyBookpop();
void DeleteTheBook();
void CountBooks();
void CountBookPop();
void BorrowTheBook();
void ReturnTheBook();
void CheckUserStatus();
void SearchUserInfo();
void SearchUserInfopop();
void CountBorrowHistory();
void ModifyUserInfo();
void ModifyUserInfoPop();
void DeleteUserInfo();
void CountUserInfo();
void CountUserInfopop(); 
void UserInfoRank();
void DisplayUserInfo();
void AboutHelp();
void UsageHelp();
void DisplayNothing();
void Display();
void DisplayClear(void);


char NFtextbuf[SIZEOFARRAY];
char OFtextbuf[SIZEOFARRAY];
char searchtext[SIZEOFARRAY];
