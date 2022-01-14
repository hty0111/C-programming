#include<stdbool.h>
#include"netClient.h"
typedef struct BOOKAMOUNT{    /*单个图书种类的借阅信息*/
	char *category;           /*图书种类*/
	int TotalBooks;           /*藏书量*/
	int TotalBorrowed;        /*借阅量*/
	struct BOOAMOUNT *next;   /*下一个结点*/
}BOOKAMOUNT; 
 
/////////////////////////////////////////////////////////////////////////////////////////////
/*检索模块*/
 
/*
 *按id号查找书籍
 *使用getBookInfo()函数来获得一个含有所查书籍信息的BOOKS结点指针  
 */

/*
 *按bookname模糊查找
 *该函数返回一个含有所输关键字的书名的书的结果链表的头指针
 *若头指针为NULL说明未找到 
 *建议在得到的结果链表不再使用后使用freeAllBooks()函数释放链表
 */
BOOKS *searchbook_name(char *databaseName,char *bookname);

/*
 *按authors模糊查找
 *该函数返回一个含有所输关键字的作者的书的结果链表的头指针
 *若头指针为NULL说明未找到 
 *建议在得到的结果链表不再使用后使用freeAllBooks()函数释放链表
 */
BOOKS *searchbook_authors(char *databaseName,char *authors); 

/*
 *按keywords模糊查找
 *该函数返回一个含有所输关键字的关键词的书的结果链表的头指针
 *若头指针为NULL说明未找到 
 *建议在得到的结果链表不再使用后使用freeAllBooks()函数释放链表
 */
BOOKS *searchbook_keywords(char *databaseName,char *keywords);

/*
 *查书籍借阅情况
 *本函数需要传入databaseName(前端调用时传入任意char型指针)和需检索的书籍id
 *最后返回一个BOOKSTATE结点的指针
 *请在使用完毕后 
 */
BOOKSTATE *searchbookstate(char *databaseName,char *id);

/*
 *查用户信息
 *使用AU_getUSERInfo()函数获取一个USERS指针
 *使用完毕后用freeSingleUser()函数释放 
 */

/*
 *查用户借阅信息
 *使用AU_getBookRecordsByUser()函数获取一个BOOKSTATE表的头结点指针 
 */

//////////////////////////////////////////////////////////////////////////////////////
/*统计模块*/
/*
 *统计数据库中图书总量
 *传入数据库名(前端调用时传入任意char型指针)
 *返回其中所有书籍总数量 
 */
int CountTotalBook(char *databaseName); 

/*
 *统计数据库中图书总借阅量
 *传入一个数据库名(前端调用时传入任意char型指针)和一个初始管理员的信息结点指针
 *返回该数据库中所有图书中当前被借出的总量 
 */
int CountTotalBorrowed(char *databaseName); 

/*统计不同类别图书的借阅情况
 *需要初始管理员身份验证以获取数据信息
 *传入一个数据库名(前端调用时传入任意char型指针)和一个初始管理员的信息结点指针
 *返回一个含有不同类别书籍借阅量的链表的头指针
 *请在使用完数据后用freeBookAmount()释放得到的结果指针 
 */
BOOKAMOUNT *BorrowedInfo(char *databaseName); 

//////////////////////////////////////////////////////////////////////////////////////
/*排序模块*/

/*
 *[Warning]:若排序时传入的不是头结点而是中间结点地址可能会导致信息丢失 
 */

/*对书籍信息进行排序*/
/*
 *按书号排序(暂按升序)
 *该函数读入一个链表的头结点地址，对其按书号进行排序
 *返回改变顺序后的链表头指针 
 */
BOOKS *rank_id(BOOKS *bookhead);

/*
 *按图书名排序(暂按升序)
 *该函数读入一个链表的头结点地址，对其按书名进行排序
 *返回改变顺序后的链表头指针 
 */ 
BOOKS *rank_bookname(BOOKS *bookhead);

/*
 *按第一作者排序(暂按升序)
 *要求每个作者的名字中有且仅有一个空格 
 *该函数读入一个链表的头结点地址，对其按第一作者进行排序
 *返回改变顺序后的链表头指针 
 */ 
BOOKS *rank_firstauthor(BOOKS *bookhead);

/*对用户参数进行排序*/
/*
 *按用户id升序
 *读入一个数据库名(前端调用时传入任意char型指针)和当前操作用户的USERS结点指针
 *若为管理员才可操作，返回排序后链表头结点指针
 *非管理员调用则返回NULL 
 */
USERS *rank_userid(char *databaseName,USERS *admin);
 
/*
 *按用户名升序
 *读入一个数据库名(前端调用时传入任意char型指针)和当前操作用户的USERS结点指针
 *若为管理员才可操作，返回排序后链表头结点指针
 *非管理员调用则返回NULL 
 */
USERS *rank_username(char *databaseName,USERS *admin);

 /*
 *按用户部门升序
 *读入一个数据库名(前端调用时传入任意char型指针)和当前操作用户的USERS结点指针
 *若为管理员才可操作，返回排序后链表头结点指针
 *非管理员调用则返回NULL 
 */
USERS *rank_userdepart(char *databaseName,USERS *admin);

//////////////////////////////////////////////////////////////////////////////////// 
/*其它函数*/

/*判断是否有目标字符串的连续子串与输入字符串相同或只有一个字母不同*/ 
bool cmp_keywords(char *key,char *target);

/*此函数用于将单个book节点的内容复制到一个新的节点*/
BOOKS* copybooknode(BOOKS *ptr); 

/*此函数将一个BOOKSTATE结点的内容复制到一个新建的结点中*/
BOOKSTATE *copystatenode(BOOKSTATE *ptr);

/*统计不同类别图书的借阅情况时释放其BOOKAMOUNT结果链表的函数*/
int freeBookAmount(BOOKAMOUNT *BorrowedInfo);

////////////////////////////////////////////////////////////////////////////////////// 
/*netClient中函数声明*/

#ifndef IDENTIFY
/*头文件包含*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mongoose.h"
#include "cJSON.h"

/*宏定义*/
/*function userLogIn*/
#define LOG_IN_SUCCESS 0
#define USERNAME_NOT_FOUND 1
#define PASSWORDS_ERROR 2
/*operation result*/
#define SUCCESS 0   /*操作成功*/
#define AUTHORIZE_FAILED 1 /*身份认证失败*/
#define PERMISSION_DENIED 2  /*权限认证失败*/
#define USERNAME_REPEATED 3 /*用户已存在*/
/*function modify*/
#define DELETEMODE  0   /*删除模式*/
#define UPDATEMODE  1   /*更新模式*/
/*function borrow book*/
#define NO_BOOK_LEFT 4    /*此书无库存，借阅失败*/
/*net function*/
#define SERVER_ADDRESS "localhost:8888"
#define POST_HEADER ""

/*函数声明*/

/*数据库初始化函数*/
/*-------------*/
#ifndef DATASTORE_DATABASE
int isDatabaseInit(char *databaseName);  /*检查数据库是否已经初始化。若已经初始化，则返回1；若未初始化，则返回0*/
int initDatabase(char *databaseName);    /*初始化数据库并创建相应数据表*/
#endif
#define DATASTORE_DATABASE


/*链表操作类函数*/
#ifndef DATASTORE_MEMORY
int freeSingleUser(USERS *user);    /*释放单个USERS节点*/
int freeAllUsers(USERS *users);     /*释放一个USERS链表*/
int freeSingleBook(BOOKS *book); /*释放单个BOOKS节点*/
int freeAllBooks(BOOKS *books);  /*释放一个BOOKS链表*/
int freeSingleBookRecord(BOOKSTATE *record); /*释放单个BOOKSTATE节点*/
int freeAllBookRecords(BOOKSTATE *bookRecords);  /*释放一个BOOKSTATE链表*/
#endif
#define DATASTORE_MEMORY


/*用户相关函数*/
/*-------------*/

/*
    此函数用于进行用户名和密码的匹配操作：
    若用户不存在，则返回宏 USERNAME_NOT_FOUND
    若密码错误，则返回宏 PASSWORDS_ERROR
    若用户名和密码相匹配，则返回宏 LOG_IN_SUCCESS
    其中，函数参数中的 char *databaseName 用于指定书库（数据库）
*/
int userLogIn(char *databaseName, char *username, char *passwords);  /*用户登陆验证*/

/*
    此函数返回一个 USERS 指针，其中带有所查询用户的用户信息

    普通用户仅能查询自己的用户信息
    管理员可以查询任意一个用户信息
    函数参数中，USERS *logInUser、logInUser->username、logInUser->passwords 均【不能】为空指针
    若：
    1）logInUser中的用户名和密码不匹配
    2）普通用户试图查询非本人信息
    则函数将会返回一个空指针
    若：
    1）查询的用户不存在
    则返回结果中 id 的值为-1
    
    [NOTE]：为了避免内存泄漏，请在使用完毕后调用 freeSingleUser 函数手动释放返回指针
*/
USERS *AU_getUserInfo(char *databaseName, char *username, USERS *logInUser); /*带权限控制的用户信息获取函数*/

/*
    此函数返回一个 USERS 指针，指向一个包含有所有用户信息链表的头结点
    只有管理员可以调用这个函数，若普通用户调用此函数，则此函数将会返回一个空指针（NULL）

    [NOTE]：为了避免内存泄漏，请在使用完毕后调用 freeAllUsers 函数手动释放链表
*/
USERS *AU_getAllUserInfo(char *databaseName, USERS *logInUser);  /*带权限控制的所有用户信息获取函数*/

/*
    此函数用于修改、删除某个特定用户
    普通用户仅能修改、删除自己的账户，管理员不受限制
    若logInUser的用户名和密码不匹配，则函数返回宏 AUTHORIZE_FAILED
    若普通用户试图修改其它用户的信息，则函数返回宏 PERMISSION_DENIED
    其中函数参数 int opcode 决定了函数的行为：
    1）宏 DELETEMODE
    删除模式，删除函数参数 USERS *userToBeModified 中 username 所指向的用户（以用户名作为删除依据）
    2）宏 UPDATEMODE
    更新模式，使用函数参数 USERS *userToBeModified 中所提供的信息更新 id 所指向的用户（以id作为更新依据）
    [NOTE]：id 字段作为主键是不可更改，不可重复的
    [NOTE]：regtime 字段和 username 字段将会被忽略（即用户的注册时间和用户名无法更改）

    若操作成功，则函数返回宏 SUCCESS
*/
int AU_userModify(char *databaseName, int opcode, USERS *userToBeModified, USERS *logInUser);    /*带权限控制的修改、删除用户*/

/*
    此函数用于创建一个新用户
    普通用户或未登录用户仅能创建普通用户账户
    管理员创建账户不受限制
    若普通用户或未登录用户试图创建管理员账户，则函数返回宏 PERMISSION_DENIED
    若待创建用户的用户名已经存在，则函数返回宏 USERNAME_REPEATED
    若管理员账户身份认证失败，则函数返回宏 AUTHORIZE_FAILED
    若创建用户成功，则函数返回宏 SUCCESS

    [NOTE]：若用户未登录，则请传递一个空指针（NULL）给函数参数 USERS *admin 
    [NOTE]：待创建用户 USERS *newUser 中的 id regtime 字段将会被忽略（自动生成）
*/
int AU_createNewUser(char *databaseName, USERS *newUser, USERS *admin);  /*带权限控制创建新用户*/


/*图书相关函数*/
/*-------------*/
#ifndef DATASTORE_BOOKS
BOOKS *getAllBooksInfo(char *databaseName);  /*获取所有书籍信息*/

/*
    通过bookID来获取指定书籍信息
*/
BOOKS *getBookInfo(char *databaseName, char *bookID);  /*获取指定书籍信息*/

/*
    按分类获取书籍信息
*/
BOOKS *getBooksByCategory(char *databaseName, char *categoryName);   /*按分类获取书籍信息*/
#endif
#define DATASTORE_BOOKS

/*
    仅管理员可创建新的书籍
    若管理员身份认证失败，则函数返回宏 AUTHORIZE_FAILED
    若普通用户试图调用此函数，则函数返回宏 PERMISSION_DENIED
    [NOTE]：创建新书籍时，函数参数 BOOKS *newBook 中的 id regtime 字段将会被忽略（自动生成）
    [NOTE]：由于使用 id 字段作为主键，故图书名可以是不唯一的（类似于生活中由不同出版社出版的同名书）

    若操作成功，则函数返回宏 SUCCESS
*/
int AU_createNewBook(char *databaseName, BOOKS *newBook, USERS *admin);   /*带权限管理创建新书籍*/

/*
    仅管理员可修改、删除书籍
    若管理员身份认证失败，则函数返回宏 AUTHORIZE_FAILED
    若普通用户试图调用此函数，则函数返回宏 PERMISSION_DENIED
    同 AU_userModify 函数类似，其函数参数 int opcode 决定了函数的行为：
    1）宏 DELETEMODE
    删除模式，删除函数参数 BOOKS *book 中 id 所指向的书籍（以id作为删除依据）
    2）宏 UPDATEMODE
    更新模式，使用函数参数 BOOKS *book 中所提供的信息更新 id 所指向的书籍（以id作为更新依据）
    [NOTE]：id 字段作为主键是不可更改，不可重复的
    [NOTE]：regtime 字段将会被忽略（即图书的入库时间无法更改）

    若操作成功，则函数返回宏 SUCCESS
*/
int AU_bookModify(char *databaseName, int opcode, BOOKS *book, USERS *admin); /*带权限管理修改、删除书籍*/


/*借阅记录相关函数*/
/*-------------*/

/*
    此函数返回一个BOOKSTATE指针，指向一个带有所有图书借阅记录链表的头节点
    只有管理员可以调用这个函数，若普通用户调用此函数，则此函数将会返回一个空指针（NULL）

    [NOTE]：为了避免内存泄漏，请在使用完毕后调用 freeAllBookRecords 函数手动释放返回指针
*/
BOOKSTATE *AU_getAllBookRecords(char *databaseName, USERS *admin);  /*带权限管理查询所有借阅记录*/

/*
    此函数返回一个BOOKSTATE指针，指向一个带有某个指定用户所有借阅记录链表的头节点
    普通用户仅能查询自己的借阅记录，管理员不受限制
    若：
    1）logInUser中的用户名和密码不匹配
    2）普通用户试图查询非本人借阅记录
    3）此用户无借阅记录
    则函数将会返回一个空指针
*/
BOOKSTATE *AU_getBookRecordsByUser(char *databaseName, char *username, USERS *logInUser);   /*带权限管理查询指定用户的借阅记录*/

/*
    此函数用于完成借阅图书的操作
    若用户的用户名和密码不匹配，则函数返回宏 AUTHORIZE_FAILED
    若图书已无库存可供借阅，则函数返回宏 NO_BOOK_LEFT
    若借阅成功，则：
    1）bookToBeBorrowed 中 quantity（库存数量）变量的值将被减1，isborrowed（出借数量）变量的值将被加1
    2）logInUser 中 borrowedbooks（用户已借书籍）变量的值将被加1
    3）函数返回宏 SUCCESS
*/
int borrowBook(char *databaseName, BOOKS *bookToBeBorrowed, USERS *logInUser);  /*借阅图书*/

/*
    此函数用于完成归还图书的操作
    若用户的用户名和密码不匹配，则函数返回宏 AUTHORIZE_FAILED
    若归还成功,则：
    1）bookToBeBorrowed 中 quantity（库存数量）变量的值将被加1，isborrowed（出借数量）变量的值将被减1
    2）logInUser 中 borrowedbooks（用户已借书籍）变量的值将被减1
    3）函数返回宏 SUCCESS
*/
int returnBook(char *databaseName, BOOKS *bookToBeReturned, USERS *logInUser);  /*归还图书*/
#endif
#define IDENTIFY
