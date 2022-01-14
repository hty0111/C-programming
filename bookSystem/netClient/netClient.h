
#ifndef DATASTORE_STRUCT
/*数据结构定义*/
typedef struct USERS{       /*用户信息*/
    int id;                 /*唯一识别号（ID）*/
    char *username;         /*用户名（可保证不重复）*/
    char *passwords;        /*密码*/
    char *gender;           /*性别*/
    char *department;       /*部门*/
    int borrowedbooks;      /*已借书籍数量*/
    char *mode;             /*权限（“ADMIN“代表管理员，”USER“代表普通用户）*/
    char *regtime;          /*注册时间（自动生成）*/
    struct USERS *next;     /*下一个节点*/
} USERS;
typedef struct BOOKS{       /*单个书库的书籍信息*/
    char *id;               /*唯一识别号（ID）*/
    char *bookname;         /*书名*/
    char *keywords;         /*关键词（以逗号分隔，末尾无逗号）*/
    char *authors;          /*作者（以逗号分隔，末尾无逗号）*/
    char *publisher;        /*出版商*/
    char *pubtime;          /*出版时间*/
    int quantity;           /*库存数量*/
    int isborrowed;         /*出借数量*/
    char *category;         /*图书种类（书库）*/
    char *regtime;          /*入库时间（自动生成）*/
    struct BOOKS *next;     /*下一个节点*/
} BOOKS;
typedef struct BOOKSTATE{   /*当前出借书籍信息*/
    int id;                 /*唯一识别号（ID）*/
    int userid;             /*借书人ID号*/
    char *bookid;           /*出借书籍ID号*/
    char *borrowdate;       /*出借日期*/
    char *duedate;          /*最晚归还日期*/
    int terminated;         /*是否已经归还（未归还：0，已归还1）*/
    struct BOOKSTATE *next; /*下一个节点*/
} BOOKSTATE;
#endif
#define DATASTORE_STRUCT

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
#define DEFAULT_ADDRESS "127.0.0.1:8888"
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


static const struct mg_str getMethod = MG_MK_STR("GET");
static const struct mg_str postMethod = MG_MK_STR("POST");

static const struct mg_str apiUserLogIn = MG_MK_STR("/users/login/");
static const struct mg_str apiGetUserInfo = MG_MK_STR("/users/getsingle/");
static const struct mg_str apiGetAllUserInfo = MG_MK_STR("/users/getall/");
static const struct mg_str apiUserModify = MG_MK_STR("/users/modify/");
static const struct mg_str apiCreateNewUser = MG_MK_STR("/users/create/");

static const struct mg_str apiGetBooksByCategory = MG_MK_STR("/books/getbycat/");
static const struct mg_str apiGetAllBooksInfo = MG_MK_STR("/books/getall/");
static const struct mg_str apiGetBookInfo = MG_MK_STR("/books/getsingle/");
static const struct mg_str apiCreateNewBook = MG_MK_STR("/books/create/");
static const struct mg_str apiBookModify = MG_MK_STR("/books/modify/");

static const struct mg_str apiGetAllBookRecords = MG_MK_STR("/records/getall/");
static const struct mg_str apiGetBookRecordsByUser = MG_MK_STR("/records/getbyuser/");
static const struct mg_str apiBorrowBook = MG_MK_STR("/records/borrow/");
static const struct mg_str apiReturnBook = MG_MK_STR("/records/return/");

static int isClosed;

char *usersToJson(USERS *users);
char *booksToJson(BOOKS *books);
char *recordsToJson(BOOKSTATE *records);
USERS *jsonToUsers(const char *data);
BOOKS *jsonToBooks(const char *data);
BOOKSTATE *jsonToRecords(const char *data);