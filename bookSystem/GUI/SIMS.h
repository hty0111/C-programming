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

#define BOARDWIDTH 10 /* ͼ�����ϵͳ����Ŀ�� */ 
#define BOARDHEIGHT 6 /* ͼ�����ϵͳ����ĸ߶� */
#define WELCOMEWINDOW 1 /* ��ӭ���� */
#define LOGINWINDOW 2 /* ��½���� */ 
#define ADMINWINDOW 3 /* ����Ա���� */ 
#define USERWINDOW 4 /*�û�����*/
#define SIZEOFARRAY 40 
#define SWAP_LIMIT 512
#define DATABASE "databaseName"

/*ö������*/ 
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

/*StatusBar��״̬ö��*/
typedef enum{
	LoginSuccess=1,//�ɹ���¼ 
	UserNameNotFind,//δ�ҵ��û��� 
	DeniedPermission,//ע��Ȩ�޲���
	AuthorizeFail,// �����˻���֤ʧ��
	PasswordError,//������� 
	SignUpSuccess,//ע��ɹ� 
	RepeatedUserName,//�û��������� 
	InsecurePassword,//����ǿ��̫��  
	NFSuccess,//�½��ļ� 
	NFFail,
	OFSuccess,//���ļ� 
	FileNotFind,
	SFSuccess,//�����ļ� 
	SFFail,
	CFSuccess,//�ر��ļ� 
	BookNotFind,
	UnmatchedIDName,//
	NBSuccess,//�����鼮 
	NBFail,
	CBSuccess,//�����鼮 
	SBSuccess,//�����鼮 
	MBSuccess,//�޸��鼮 
	DBSuccess,//ɾ���鼮 
	COBSucess,//ͳ�� 
	BorrowSuccess,//���� 
	BookUnavailable,//�޿�� 
	ReturnSuccess,//�黹 
	BookOverdue,//������������ȥ�˹����񴦽����ڷ��� 
	UserNotfind,//����User�Ĳ��������ʧ�ܵĻ���Ӧ��ֻ���Ҳ����û���id�û�����ƥ���������� 
	UnmatchedUIDName, 
	SearchUserSuccess,
	ModifyUserSuccess,
	DeleteUserSuccess,
	CountUserSuccess		
}Status_CHOICE; 

void InitializeUserBoard(); /* ��ʼ���û����� */
void InitializeAdminBoard(); /* ��ʼ������Ա���� */
void WelcomeBoard(); /* ��ʾ��ӭ���� */ 
void LoginBoard(); /* ��¼���� */ 
void Refresh(); /* ˢ�½��溯�� */
void drawthebackground(); /*����������*/
void StatusBar(); /*״̬������*/ 
void ToolBar(); /*ͼ�깤����*/ 
void KeyboardEventProcess(int key,int event); /* ������Ϣ�ص����� */
void MouseEventProcess(int x, int y, int button, int event); /* �����Ϣ�ص����� */
void CharEventProcess(char c); /* �ַ���Ϣ�ص����� */
void RespondMenuEvent(); /* ��Ӧ�˵��¼� */ 

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
