/*
--------[NOTE]--------
非上层模块（身份验证模块）请**不要**直接调用本层函数
--------[NOTE]--------
*/

#ifndef DATASTORE

/*头文件包含*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include "sqlite3.h"
// #include "cJSON.h"

/*宏定义*/
/*function userModify/bookModify/borrowModify*/
#define DELETEMODE  0   /*删除模式*/
#define UPDATEMODE  1   /*更新模式*/

#define INSTRUCTION_LIMIT 4096  /*SQL指令长度限制*/
#define BORROW_TIME 30          /*借书时长设置（天）*/
#define SUCCESS 0

/*数据结构定义*/
#ifndef DATASTORE_STRUCT
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


/*函数声明*/

/*链表操作类函数*/
/*-------------*/
#ifndef DATASTORE_MEMORY
int freeSingleUser(USERS *user);    /*释放单个USERS节点*/
int freeAllUsers(USERS *users);     /*释放一个USERS链表*/
int freeSingleBook(BOOKS *book); /*释放单个BOOKS节点*/
int freeAllBooks(BOOKS *books);  /*释放一个BOOKS链表*/
int freeSingleBookRecord(BOOKSTATE *record); /*释放单个BOOKSTATE节点*/
int freeAllBookRecords(BOOKSTATE *bookRecords);  /*释放一个BOOKSTATE链表*/
#endif
#define DATASTORE_MEMORY


/*数据库初始化函数*/
/*-------------*/
#ifndef DATASTORE_DATABASE
int isDatabaseInit(char *databaseName);  /*检查数据库是否已经初始化。若已经初始化，则返回1；若未初始化，则返回0*/
int initDatabase(char *databaseName);    /*初始化数据库并创建相应数据表*/
#endif
#define DATASTORE_DATABASE


/*用户相关函数*/
/*-------------*/
int getUserInfoCallback(void *results,int colNumber,char **queryResult,char **colName);   /*获取指定用户信息的回调函数*/
USERS* getUserInfo(char *databaseName, char *username);    /*获取指定用户信息*/
int createNewUser(char *databaseName, USERS *newUser);  /*创建新用户*/
int userModify(char *databaseName, int opcode, USERS *user);    /*修改、删除用户*/
int getAllUserInfoCallback(void *results, int colNumber, char **queryResult, char **colName);    /*处理所有用户信息的回调函数*/
USERS *getAllUserInfo(char *databaseName);   /*获取所有用户信息*/


/*图书相关函数*/
/*-------------*/
int getAllBooksInfoCallback(void *results, int colNumber, char **queryResult, char **colName);    /*处理所有书籍信息的回调函数*/
int getBookInfoCallback(void *results, int colNumber, char **queryResult, char **colName);    /*处理指定书籍信息的回调函数*/
#ifndef DATASTORE_BOOKS
BOOKS *getAllBooksInfo(char *databaseName);  /*获取所有书籍信息*/
BOOKS *getBookInfo(char *databaseName, char *bookID);  /*获取指定书籍信息*/
BOOKS *getBooksByCategory(char *databaseName, char *categoryName);   /*按分类获取书籍信息*/
#endif
#define DATASTORE_BOOKS
int getBooksByCategoryCallback(void *results, int colNumber, char **queryResult, char **colName);    /*按分类获取书籍信息的回调函数*/
int createNewBook(char *databaseName, BOOKS *newBook);   /*创建新书籍*/
int bookModify(char *databaseName, int opcode, BOOKS *book); /*修改、删除书籍*/


/*借阅记录相关函数*/
/*-------------*/
BOOKSTATE *getBookRecordsByUser(char *databaseName, USERS *user);   /*查询指定用户的借阅记录*/
int getAllBorrowInfoCallback(void *results, int colNumber, char **queryResult, char **colName);   /*处理所有借阅记录的回调函数*/
BOOKSTATE *getAllBorrowInfo(char *databaseName); /*获取所有借阅记录*/
int getBorrowInfoCallback(void *results, int colNumber, char **queryResult, char **colName);  /*处理指定借阅记录的回调函数*/
BOOKSTATE *getBorrowInfo(char *databaseName, int borrowID);    /*获取指定借阅记录*/
int createNewBorrow(char *databaseName, BOOKSTATE *newBorrow);   /*创建新的借阅记录*/
int borrowModify(char *databaseName, int opcode, BOOKSTATE *borrow); /*修改、删除借阅记录*/
BOOKSTATE *borrowRecordLocation(char *databaseName, BOOKS *book, USERS *user);   /*定位借阅记录*/


/*其它辅助函数*/
/*-------------*/
char *specificTime(int offset);  /*获取偏移了指定天数（int offset）后的系统日期*/
#endif
#define DATASTORE