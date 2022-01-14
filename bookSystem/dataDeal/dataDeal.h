#include<stdbool.h>
#include"netClient.h"
typedef struct BOOKAMOUNT{    /*����ͼ������Ľ�����Ϣ*/
	char *category;           /*ͼ������*/
	int TotalBooks;           /*������*/
	int TotalBorrowed;        /*������*/
	struct BOOAMOUNT *next;   /*��һ�����*/
}BOOKAMOUNT; 
 
/////////////////////////////////////////////////////////////////////////////////////////////
/*����ģ��*/
 
/*
 *��id�Ų����鼮
 *ʹ��getBookInfo()���������һ�����������鼮��Ϣ��BOOKS���ָ��  
 */

/*
 *��booknameģ������
 *�ú�������һ����������ؼ��ֵ���������Ľ�������ͷָ��
 *��ͷָ��ΪNULL˵��δ�ҵ� 
 *�����ڵõ��Ľ��������ʹ�ú�ʹ��freeAllBooks()�����ͷ�����
 */
BOOKS *searchbook_name(char *databaseName,char *bookname);

/*
 *��authorsģ������
 *�ú�������һ����������ؼ��ֵ����ߵ���Ľ�������ͷָ��
 *��ͷָ��ΪNULL˵��δ�ҵ� 
 *�����ڵõ��Ľ��������ʹ�ú�ʹ��freeAllBooks()�����ͷ�����
 */
BOOKS *searchbook_authors(char *databaseName,char *authors); 

/*
 *��keywordsģ������
 *�ú�������һ����������ؼ��ֵĹؼ��ʵ���Ľ�������ͷָ��
 *��ͷָ��ΪNULL˵��δ�ҵ� 
 *�����ڵõ��Ľ��������ʹ�ú�ʹ��freeAllBooks()�����ͷ�����
 */
BOOKS *searchbook_keywords(char *databaseName,char *keywords);

/*
 *���鼮�������
 *��������Ҫ����databaseName(ǰ�˵���ʱ��������char��ָ��)����������鼮id
 *��󷵻�һ��BOOKSTATE����ָ��
 *����ʹ����Ϻ� 
 */
BOOKSTATE *searchbookstate(char *databaseName,char *id);

/*
 *���û���Ϣ
 *ʹ��AU_getUSERInfo()������ȡһ��USERSָ��
 *ʹ����Ϻ���freeSingleUser()�����ͷ� 
 */

/*
 *���û�������Ϣ
 *ʹ��AU_getBookRecordsByUser()������ȡһ��BOOKSTATE���ͷ���ָ�� 
 */

//////////////////////////////////////////////////////////////////////////////////////
/*ͳ��ģ��*/
/*
 *ͳ�����ݿ���ͼ������
 *�������ݿ���(ǰ�˵���ʱ��������char��ָ��)
 *�������������鼮������ 
 */
int CountTotalBook(char *databaseName); 

/*
 *ͳ�����ݿ���ͼ���ܽ�����
 *����һ�����ݿ���(ǰ�˵���ʱ��������char��ָ��)��һ����ʼ����Ա����Ϣ���ָ��
 *���ظ����ݿ�������ͼ���е�ǰ����������� 
 */
int CountTotalBorrowed(char *databaseName); 

/*ͳ�Ʋ�ͬ���ͼ��Ľ������
 *��Ҫ��ʼ����Ա�����֤�Ի�ȡ������Ϣ
 *����һ�����ݿ���(ǰ�˵���ʱ��������char��ָ��)��һ����ʼ����Ա����Ϣ���ָ��
 *����һ�����в�ͬ����鼮�������������ͷָ��
 *����ʹ�������ݺ���freeBookAmount()�ͷŵõ��Ľ��ָ�� 
 */
BOOKAMOUNT *BorrowedInfo(char *databaseName); 

//////////////////////////////////////////////////////////////////////////////////////
/*����ģ��*/

/*
 *[Warning]:������ʱ����Ĳ���ͷ�������м����ַ���ܻᵼ����Ϣ��ʧ 
 */

/*���鼮��Ϣ��������*/
/*
 *���������(�ݰ�����)
 *�ú�������һ�������ͷ����ַ�����䰴��Ž�������
 *���ظı�˳��������ͷָ�� 
 */
BOOKS *rank_id(BOOKS *bookhead);

/*
 *��ͼ��������(�ݰ�����)
 *�ú�������һ�������ͷ����ַ�����䰴������������
 *���ظı�˳��������ͷָ�� 
 */ 
BOOKS *rank_bookname(BOOKS *bookhead);

/*
 *����һ��������(�ݰ�����)
 *Ҫ��ÿ�����ߵ����������ҽ���һ���ո� 
 *�ú�������һ�������ͷ����ַ�����䰴��һ���߽�������
 *���ظı�˳��������ͷָ�� 
 */ 
BOOKS *rank_firstauthor(BOOKS *bookhead);

/*���û�������������*/
/*
 *���û�id����
 *����һ�����ݿ���(ǰ�˵���ʱ��������char��ָ��)�͵�ǰ�����û���USERS���ָ��
 *��Ϊ����Ա�ſɲ������������������ͷ���ָ��
 *�ǹ���Ա�����򷵻�NULL 
 */
USERS *rank_userid(char *databaseName,USERS *admin);
 
/*
 *���û�������
 *����һ�����ݿ���(ǰ�˵���ʱ��������char��ָ��)�͵�ǰ�����û���USERS���ָ��
 *��Ϊ����Ա�ſɲ������������������ͷ���ָ��
 *�ǹ���Ա�����򷵻�NULL 
 */
USERS *rank_username(char *databaseName,USERS *admin);

 /*
 *���û���������
 *����һ�����ݿ���(ǰ�˵���ʱ��������char��ָ��)�͵�ǰ�����û���USERS���ָ��
 *��Ϊ����Ա�ſɲ������������������ͷ���ָ��
 *�ǹ���Ա�����򷵻�NULL 
 */
USERS *rank_userdepart(char *databaseName,USERS *admin);

//////////////////////////////////////////////////////////////////////////////////// 
/*��������*/

/*�ж��Ƿ���Ŀ���ַ����������Ӵ��������ַ�����ͬ��ֻ��һ����ĸ��ͬ*/ 
bool cmp_keywords(char *key,char *target);

/*�˺������ڽ�����book�ڵ�����ݸ��Ƶ�һ���µĽڵ�*/
BOOKS* copybooknode(BOOKS *ptr); 

/*�˺�����һ��BOOKSTATE�������ݸ��Ƶ�һ���½��Ľ����*/
BOOKSTATE *copystatenode(BOOKSTATE *ptr);

/*ͳ�Ʋ�ͬ���ͼ��Ľ������ʱ�ͷ���BOOKAMOUNT�������ĺ���*/
int freeBookAmount(BOOKAMOUNT *BorrowedInfo);

////////////////////////////////////////////////////////////////////////////////////// 
/*netClient�к�������*/

#ifndef IDENTIFY
/*ͷ�ļ�����*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mongoose.h"
#include "cJSON.h"

/*�궨��*/
/*function userLogIn*/
#define LOG_IN_SUCCESS 0
#define USERNAME_NOT_FOUND 1
#define PASSWORDS_ERROR 2
/*operation result*/
#define SUCCESS 0   /*�����ɹ�*/
#define AUTHORIZE_FAILED 1 /*�����֤ʧ��*/
#define PERMISSION_DENIED 2  /*Ȩ����֤ʧ��*/
#define USERNAME_REPEATED 3 /*�û��Ѵ���*/
/*function modify*/
#define DELETEMODE  0   /*ɾ��ģʽ*/
#define UPDATEMODE  1   /*����ģʽ*/
/*function borrow book*/
#define NO_BOOK_LEFT 4    /*�����޿�棬����ʧ��*/
/*net function*/
#define SERVER_ADDRESS "localhost:8888"
#define POST_HEADER ""

/*��������*/

/*���ݿ��ʼ������*/
/*-------------*/
#ifndef DATASTORE_DATABASE
int isDatabaseInit(char *databaseName);  /*������ݿ��Ƿ��Ѿ���ʼ�������Ѿ���ʼ�����򷵻�1����δ��ʼ�����򷵻�0*/
int initDatabase(char *databaseName);    /*��ʼ�����ݿⲢ������Ӧ���ݱ�*/
#endif
#define DATASTORE_DATABASE


/*��������ຯ��*/
#ifndef DATASTORE_MEMORY
int freeSingleUser(USERS *user);    /*�ͷŵ���USERS�ڵ�*/
int freeAllUsers(USERS *users);     /*�ͷ�һ��USERS����*/
int freeSingleBook(BOOKS *book); /*�ͷŵ���BOOKS�ڵ�*/
int freeAllBooks(BOOKS *books);  /*�ͷ�һ��BOOKS����*/
int freeSingleBookRecord(BOOKSTATE *record); /*�ͷŵ���BOOKSTATE�ڵ�*/
int freeAllBookRecords(BOOKSTATE *bookRecords);  /*�ͷ�һ��BOOKSTATE����*/
#endif
#define DATASTORE_MEMORY


/*�û���غ���*/
/*-------------*/

/*
    �˺������ڽ����û����������ƥ�������
    ���û������ڣ��򷵻غ� USERNAME_NOT_FOUND
    ����������򷵻غ� PASSWORDS_ERROR
    ���û�����������ƥ�䣬�򷵻غ� LOG_IN_SUCCESS
    ���У����������е� char *databaseName ����ָ����⣨���ݿ⣩
*/
int userLogIn(char *databaseName, char *username, char *passwords);  /*�û���½��֤*/

/*
    �˺�������һ�� USERS ָ�룬���д�������ѯ�û����û���Ϣ

    ��ͨ�û����ܲ�ѯ�Լ����û���Ϣ
    ����Ա���Բ�ѯ����һ���û���Ϣ
    ���������У�USERS *logInUser��logInUser->username��logInUser->passwords �������ܡ�Ϊ��ָ��
    ����
    1��logInUser�е��û��������벻ƥ��
    2����ͨ�û���ͼ��ѯ�Ǳ�����Ϣ
    �������᷵��һ����ָ��
    ����
    1����ѯ���û�������
    �򷵻ؽ���� id ��ֵΪ-1
    
    [NOTE]��Ϊ�˱����ڴ�й©������ʹ����Ϻ���� freeSingleUser �����ֶ��ͷŷ���ָ��
*/
USERS *AU_getUserInfo(char *databaseName, char *username, USERS *logInUser); /*��Ȩ�޿��Ƶ��û���Ϣ��ȡ����*/

/*
    �˺�������һ�� USERS ָ�룬ָ��һ�������������û���Ϣ�����ͷ���
    ֻ�й���Ա���Ե����������������ͨ�û����ô˺�������˺������᷵��һ����ָ�루NULL��

    [NOTE]��Ϊ�˱����ڴ�й©������ʹ����Ϻ���� freeAllUsers �����ֶ��ͷ�����
*/
USERS *AU_getAllUserInfo(char *databaseName, USERS *logInUser);  /*��Ȩ�޿��Ƶ������û���Ϣ��ȡ����*/

/*
    �˺��������޸ġ�ɾ��ĳ���ض��û�
    ��ͨ�û������޸ġ�ɾ���Լ����˻�������Ա��������
    ��logInUser���û��������벻ƥ�䣬�������غ� AUTHORIZE_FAILED
    ����ͨ�û���ͼ�޸������û�����Ϣ���������غ� PERMISSION_DENIED
    ���к������� int opcode �����˺�������Ϊ��
    1���� DELETEMODE
    ɾ��ģʽ��ɾ���������� USERS *userToBeModified �� username ��ָ����û������û�����Ϊɾ�����ݣ�
    2���� UPDATEMODE
    ����ģʽ��ʹ�ú������� USERS *userToBeModified �����ṩ����Ϣ���� id ��ָ����û�����id��Ϊ�������ݣ�
    [NOTE]��id �ֶ���Ϊ�����ǲ��ɸ��ģ������ظ���
    [NOTE]��regtime �ֶκ� username �ֶν��ᱻ���ԣ����û���ע��ʱ����û����޷����ģ�

    �������ɹ����������غ� SUCCESS
*/
int AU_userModify(char *databaseName, int opcode, USERS *userToBeModified, USERS *logInUser);    /*��Ȩ�޿��Ƶ��޸ġ�ɾ���û�*/

/*
    �˺������ڴ���һ�����û�
    ��ͨ�û���δ��¼�û����ܴ�����ͨ�û��˻�
    ����Ա�����˻���������
    ����ͨ�û���δ��¼�û���ͼ��������Ա�˻����������غ� PERMISSION_DENIED
    ���������û����û����Ѿ����ڣ��������غ� USERNAME_REPEATED
    ������Ա�˻������֤ʧ�ܣ��������غ� AUTHORIZE_FAILED
    �������û��ɹ����������غ� SUCCESS

    [NOTE]�����û�δ��¼�����봫��һ����ָ�루NULL������������ USERS *admin 
    [NOTE]���������û� USERS *newUser �е� id regtime �ֶν��ᱻ���ԣ��Զ����ɣ�
*/
int AU_createNewUser(char *databaseName, USERS *newUser, USERS *admin);  /*��Ȩ�޿��ƴ������û�*/


/*ͼ����غ���*/
/*-------------*/
#ifndef DATASTORE_BOOKS
BOOKS *getAllBooksInfo(char *databaseName);  /*��ȡ�����鼮��Ϣ*/

/*
    ͨ��bookID����ȡָ���鼮��Ϣ
*/
BOOKS *getBookInfo(char *databaseName, char *bookID);  /*��ȡָ���鼮��Ϣ*/

/*
    �������ȡ�鼮��Ϣ
*/
BOOKS *getBooksByCategory(char *databaseName, char *categoryName);   /*�������ȡ�鼮��Ϣ*/
#endif
#define DATASTORE_BOOKS

/*
    ������Ա�ɴ����µ��鼮
    ������Ա�����֤ʧ�ܣ��������غ� AUTHORIZE_FAILED
    ����ͨ�û���ͼ���ô˺������������غ� PERMISSION_DENIED
    [NOTE]���������鼮ʱ���������� BOOKS *newBook �е� id regtime �ֶν��ᱻ���ԣ��Զ����ɣ�
    [NOTE]������ʹ�� id �ֶ���Ϊ��������ͼ���������ǲ�Ψһ�ģ��������������ɲ�ͬ����������ͬ���飩

    �������ɹ����������غ� SUCCESS
*/
int AU_createNewBook(char *databaseName, BOOKS *newBook, USERS *admin);   /*��Ȩ�޹��������鼮*/

/*
    ������Ա���޸ġ�ɾ���鼮
    ������Ա�����֤ʧ�ܣ��������غ� AUTHORIZE_FAILED
    ����ͨ�û���ͼ���ô˺������������غ� PERMISSION_DENIED
    ͬ AU_userModify �������ƣ��亯������ int opcode �����˺�������Ϊ��
    1���� DELETEMODE
    ɾ��ģʽ��ɾ���������� BOOKS *book �� id ��ָ����鼮����id��Ϊɾ�����ݣ�
    2���� UPDATEMODE
    ����ģʽ��ʹ�ú������� BOOKS *book �����ṩ����Ϣ���� id ��ָ����鼮����id��Ϊ�������ݣ�
    [NOTE]��id �ֶ���Ϊ�����ǲ��ɸ��ģ������ظ���
    [NOTE]��regtime �ֶν��ᱻ���ԣ���ͼ������ʱ���޷����ģ�

    �������ɹ����������غ� SUCCESS
*/
int AU_bookModify(char *databaseName, int opcode, BOOKS *book, USERS *admin); /*��Ȩ�޹����޸ġ�ɾ���鼮*/


/*���ļ�¼��غ���*/
/*-------------*/

/*
    �˺�������һ��BOOKSTATEָ�룬ָ��һ����������ͼ����ļ�¼�����ͷ�ڵ�
    ֻ�й���Ա���Ե����������������ͨ�û����ô˺�������˺������᷵��һ����ָ�루NULL��

    [NOTE]��Ϊ�˱����ڴ�й©������ʹ����Ϻ���� freeAllBookRecords �����ֶ��ͷŷ���ָ��
*/
BOOKSTATE *AU_getAllBookRecords(char *databaseName, USERS *admin);  /*��Ȩ�޹����ѯ���н��ļ�¼*/

/*
    �˺�������һ��BOOKSTATEָ�룬ָ��һ������ĳ��ָ���û����н��ļ�¼�����ͷ�ڵ�
    ��ͨ�û����ܲ�ѯ�Լ��Ľ��ļ�¼������Ա��������
    ����
    1��logInUser�е��û��������벻ƥ��
    2����ͨ�û���ͼ��ѯ�Ǳ��˽��ļ�¼
    3�����û��޽��ļ�¼
    �������᷵��һ����ָ��
*/
BOOKSTATE *AU_getBookRecordsByUser(char *databaseName, char *username, USERS *logInUser);   /*��Ȩ�޹����ѯָ���û��Ľ��ļ�¼*/

/*
    �˺���������ɽ���ͼ��Ĳ���
    ���û����û��������벻ƥ�䣬�������غ� AUTHORIZE_FAILED
    ��ͼ�����޿��ɹ����ģ��������غ� NO_BOOK_LEFT
    �����ĳɹ�����
    1��bookToBeBorrowed �� quantity�����������������ֵ������1��isborrowed������������������ֵ������1
    2��logInUser �� borrowedbooks���û��ѽ��鼮��������ֵ������1
    3���������غ� SUCCESS
*/
int borrowBook(char *databaseName, BOOKS *bookToBeBorrowed, USERS *logInUser);  /*����ͼ��*/

/*
    �˺���������ɹ黹ͼ��Ĳ���
    ���û����û��������벻ƥ�䣬�������غ� AUTHORIZE_FAILED
    ���黹�ɹ�,��
    1��bookToBeBorrowed �� quantity�����������������ֵ������1��isborrowed������������������ֵ������1
    2��logInUser �� borrowedbooks���û��ѽ��鼮��������ֵ������1
    3���������غ� SUCCESS
*/
int returnBook(char *databaseName, BOOKS *bookToBeReturned, USERS *logInUser);  /*�黹ͼ��*/
#endif
#define IDENTIFY
