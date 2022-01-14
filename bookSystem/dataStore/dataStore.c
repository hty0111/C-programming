#include "dataStore.h"
/*数据库初始化函数*/
/*-------------*/
int isDatabaseInit(char *databaseName)  /*检查数据库是否已经初始化。若已经初始化，则返回1；若未初始化，则返回0*/
{
    FILE *fp = fopen(databaseName,"r");
    if(fp == NULL)  
    {
        return 0;
    }
    fclose(fp);
    return 1;
}
int initDatabase(char *databaseName)    /*初始化数据库并创建相应数据表*/
{
    /*打开日志文件*/
    FILE *fp = fopen("dataBase.log","a+");
    /*建立数据库连接*/
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg=NULL;
    int sqlState;
    /*创建数据表所需要的SQL语句*/
    /*用户表创建*/
    char *initUser = "DROP TABLE IF EXISTS userinfo;CREATE TABLE userinfo (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,username text,passwords text,gender text,department text,borrowedbooks int DEFAULT 0,mode varchar(32) NOT NULL,regtime TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";
    //书籍状态表创建
    char *initBookState = "DROP TABLE IF EXISTS bookstate;CREATE TABLE bookstate(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,userid int NOT NULL,bookid text NOT NULL,borrowdate text NOT NULL,duedate text NOT NULL,terminated int);";
    /*默认图书库创建*/
    char *defaultBookLibrary = "DROP TABLE IF EXISTS books_default;CREATE TABLE books_default(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,bookname text,keywords text,authors text,publisher text,pubtime varchar(50),quantity int,isborrowed int,category text,regtime TIMESTAMP DEFAULT CURRENT_TIMESTAMP);";
    /*创建数据表*/
    sqlState = sqlite3_exec(db,initUser,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    sqlState = sqlite3_exec(db,initBookState,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    sqlState = sqlite3_exec(db,defaultBookLibrary,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*创建初始管理员*/
    char *admin = "INSERT INTO userinfo (username, passwords, gender, department, mode) VALUES('admin','admin','admin','admin','ADMIN');";
    sqlState = sqlite3_exec(db,admin,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    return 0;
}
/*-------------*/
/*数据库初始化函数*/



/*用户相关函数*/
/*-------------*/
int getUserInfoCallback(void *results,int colNumber,char **queryResult,char **colName)   /*获取指定用户信息的回调函数*/
{
    /*指针类型转换*/
    USERS *flag = (USERS*)results;
    /*申请内存空间*/
    flag->username = calloc(sizeof(char),strlen(queryResult[1])+1);
    flag->passwords = calloc(sizeof(char),strlen(queryResult[2])+1);
    flag->gender = calloc(sizeof(char),strlen(queryResult[3])+1);
    flag->department = calloc(sizeof(char),strlen(queryResult[4])+1);
    flag->mode = calloc(sizeof(char),strlen(queryResult[6])+1);
    flag->regtime = calloc(sizeof(char),strlen(queryResult[7])+1);
    /*拷贝用户信息*/
    flag->id = atoi(queryResult[0]);
    strcpy(flag->username,queryResult[1]);
    strcpy(flag->passwords,queryResult[2]);
    strcpy(flag->gender,queryResult[3]);
    strcpy(flag->department,queryResult[4]);
    flag->borrowedbooks = atoi(queryResult[5]);
    strcpy(flag->mode,queryResult[6]);
    strcpy(flag->regtime,queryResult[7]);
    flag->next = NULL;
    return SQLITE_OK;
}
USERS* getUserInfo(char *databaseName, char *username)    /*获取指定用户信息*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    /*创建指针*/
    USERS *results = calloc(sizeof(USERS),1);
    results->next = NULL;
    results->id = -1;
    results->username = NULL;
    results->passwords = NULL;
    results->gender = NULL;
    results->department = NULL;
    results->mode = NULL;
    results->regtime = NULL;
    char *errMsg;
    int sqlState;
    /*准备查询语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"SELECT * FROM userinfo WHERE username = '%s';",username);
    /*查询字段*/
    sqlState = sqlite3_exec(db,queryString,getUserInfoCallback,(void*)results,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回查询结果*/
    return results;
}
int createNewUser(char *databaseName, USERS *newUser)  /*创建新用户*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备插入语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"INSERT INTO userinfo (username, passwords, gender, department, mode) VALUES('%s','%s','%s','%s','%s');",newUser->username,newUser->passwords,newUser->gender,newUser->department,newUser->mode);
    /*执行插入语句*/
    sqlState = sqlite3_exec(db,queryString,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回执行结果（用于判断是否成功）*/
    return sqlState;
}
int userModify(char *databaseName, int opcode, USERS *user)    /*修改、删除用户*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    char queryString[INSTRUCTION_LIMIT]={};
    /*准备相应语句*/
    switch(opcode)
    {
        case DELETEMODE:    /*删除用户*/
            /*准备删除语句*/
            sprintf(queryString,"DELETE FROM userinfo WHERE username = '%s';",user->username);
        break;
        case UPDATEMODE:    /*更改用户信息*/
            /*准备更新语句*/
            sprintf(queryString,"UPDATE userinfo SET username = '%s', passwords = '%s', gender = '%s', department = '%s', borrowedbooks = '%d', mode = '%s' WHERE id = '%d';",user->username,user->passwords,user->gender,user->department,user->borrowedbooks,user->mode,user->id);
        break;
    }
    /*执行相应操作*/
    sqlState = sqlite3_exec(db,queryString,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回执行结果（用于判断是否成功）*/
    return sqlState;
}
int getAllUserInfoCallback(void *results, int colNumber, char **queryResult, char **colName)    /*处理所有用户信息的回调函数*/
{
    /*指针类型转换*/
    USERS *flag = (USERS*)results;
    /*寻找末尾节点*/
    while(flag->next != NULL)   flag = flag->next;
    /*追加新节点*/
    flag->next = calloc(sizeof(USERS),1);
    flag = flag->next;
    flag->username = calloc(sizeof(char),strlen(queryResult[1])+1);
    flag->passwords = calloc(sizeof(char),strlen(queryResult[2])+1);
    flag->gender = calloc(sizeof(char),strlen(queryResult[3])+1);
    flag->department = calloc(sizeof(char),strlen(queryResult[4])+1);
    flag->mode = calloc(sizeof(char),strlen(queryResult[6])+1);
    flag->regtime = calloc(sizeof(char),strlen(queryResult[7])+1);
    /*拷贝用户信息*/
    flag->id = atoi(queryResult[0]);
    strcpy(flag->username,queryResult[1]);
    strcpy(flag->passwords,queryResult[2]);
    strcpy(flag->gender,queryResult[3]);
    strcpy(flag->department,queryResult[4]);
    flag->borrowedbooks = atoi(queryResult[5]);
    strcpy(flag->mode,queryResult[6]);
    strcpy(flag->regtime,queryResult[7]);
    flag->next = NULL;
    return SQLITE_OK;
}
USERS *getAllUserInfo(char *databaseName)   /*获取所有用户信息*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备查询语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"SELECT * FROM userinfo");
    /*建立链表头*/
    USERS *results = calloc(sizeof(USERS),1);
    results->next = NULL;
    /*查询用户信息*/
    sqlState = sqlite3_exec(db,queryString,getAllUserInfoCallback,(void*)results,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*处理链表（替换头节点）*/
    USERS *temp = results;
    results = results->next;
    if(temp != NULL) free(temp);
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回查询结果*/
    return results;
}
int freeSingleUser(USERS *user) /*释放单个USERS节点*/
{
    if(user->username != NULL) free(user->username);
    if(user->passwords != NULL) free(user->passwords);
    if(user->gender != NULL) free(user->gender);
    if(user->department != NULL) free(user->department);
    if(user->mode != NULL) free(user->mode);
    if(user->regtime != NULL) free(user->regtime);
    if(user != NULL) free(user);
    return SUCCESS;
}
int freeAllUsers(USERS *users)  /*释放一个USERS链表*/
{
    USERS *temp = users;
    while(users != NULL)
    {
        users = users->next;
        freeSingleUser(temp);
        temp = users;
    }
    return SUCCESS;
}
/*-------------*/
/*用户相关函数*/


/*图书相关函数*/
/*-------------*/

int getAllBooksInfoCallback(void *results, int colNumber, char **queryResult, char **colName)    /*处理所有书籍信息的回调函数*/
{
    /*指针类型转换*/
    BOOKS *flag = (BOOKS*)results;
    /*寻找末尾节点*/
    while(flag->next != NULL)   flag = flag->next;
    /*追加新节点*/
    flag->next = calloc(sizeof(BOOKS),1);
    flag = flag->next;
    flag->id = calloc(sizeof(char),strlen(queryResult[0])+1);
    flag->bookname = calloc(sizeof(char),strlen(queryResult[1])+1);
    flag->keywords = calloc(sizeof(char),strlen(queryResult[2])+1);
    flag->authors = calloc(sizeof(char),strlen(queryResult[3])+1);
    flag->publisher = calloc(sizeof(char),strlen(queryResult[4])+1);
    flag->pubtime = calloc(sizeof(char),strlen(queryResult[5])+1);
    flag->category = calloc(sizeof(char),strlen(queryResult[8])+1);
    flag->regtime = calloc(sizeof(char),strlen(queryResult[9])+1);
    /*拷贝书籍信息*/
    strcpy(flag->id,queryResult[0]);
    strcpy(flag->bookname,queryResult[1]);
    strcpy(flag->keywords,queryResult[2]);
    strcpy(flag->authors,queryResult[3]);
    strcpy(flag->publisher,queryResult[4]);
    strcpy(flag->pubtime,queryResult[5]);
    flag->quantity = atoi(queryResult[6]);
    flag->isborrowed = atoi(queryResult[7]);
    strcpy(flag->category,queryResult[8]);
    strcpy(flag->regtime,queryResult[9]);
    flag->next = NULL;
    return SQLITE_OK;
}
BOOKS *getAllBooksInfo(char *databaseName)  /*获取所有书籍信息*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备查询语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"SELECT * FROM books_default");
    /*建立链表头*/
    BOOKS *results = calloc(sizeof(BOOKS),1);
    results->next = NULL;
    /*查询书籍信息*/
    sqlState = sqlite3_exec(db,queryString,getAllBooksInfoCallback,(void*)results,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*处理链表（替换头节点）*/
    BOOKS *temp = results;
    results = results->next;
    if(temp != NULL) free(temp);
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回查询结果*/
    return results;
}
int getBookInfoCallback(void *results, int colNumber, char **queryResult, char **colName)    /*处理指定书籍信息的回调函数*/
{
    /*指针类型转换*/
    BOOKS *flag = (BOOKS*)results;
    /*申请内存空间*/
    flag->id = calloc(sizeof(char),strlen(queryResult[0])+1);
    flag->bookname = calloc(sizeof(char),strlen(queryResult[1])+1);
    flag->keywords = calloc(sizeof(char),strlen(queryResult[2])+1);
    flag->authors = calloc(sizeof(char),strlen(queryResult[3])+1);
    flag->publisher = calloc(sizeof(char),strlen(queryResult[4])+1);
    flag->pubtime = calloc(sizeof(char),strlen(queryResult[5])+1);
    flag->category = calloc(sizeof(char),strlen(queryResult[8])+1);
    flag->regtime = calloc(sizeof(char),strlen(queryResult[9])+1);
    /*拷贝书籍信息*/
    strcpy(flag->id,queryResult[0]);
    strcpy(flag->bookname,queryResult[1]);
    strcpy(flag->keywords,queryResult[2]);
    strcpy(flag->authors,queryResult[3]);
    strcpy(flag->publisher,queryResult[4]);
    strcpy(flag->pubtime,queryResult[5]);
    flag->quantity = atoi(queryResult[6]);
    flag->isborrowed = atoi(queryResult[7]);
    strcpy(flag->category,queryResult[8]);
    strcpy(flag->regtime,queryResult[9]);
    flag->next = NULL;
    return SQLITE_OK;
}
BOOKS *getBookInfo(char *databaseName, char *bookID)  /*获取指定书籍信息*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    BOOKS *result = calloc(sizeof(BOOKS),1);
    result->id = NULL;
    char *errMsg;
    int sqlState;
    /*准备查询语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"SELECT * FROM books_default WHERE id = '%s'",bookID);
    /*查询书籍信息*/
    sqlState = sqlite3_exec(db,queryString,getBookInfoCallback,(void*)result,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*结果处理*/
    if(result->id == NULL)
    {
        if(result != NULL) free(result);
        result = NULL;
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回查询结果*/
    return result;
}
BOOKS *getBooksByCategory(char *databaseName, char *categoryName)   /*按分类获取书籍信息*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备查询语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"SELECT * FROM books_default WHERE category = '%s'",categoryName);
    /*建立链表头*/
    BOOKS *results = calloc(sizeof(BOOKS),1);
    results->next = NULL;
    /*查询书籍信息*/
    sqlState = sqlite3_exec(db,queryString,getAllBooksInfoCallback,(void*)results,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*处理链表（替换头节点）*/
    BOOKS *temp = results;
    results = results->next;
    if(temp != NULL) free(temp);
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回查询结果*/
    return results;
}
int createNewBook(char *databaseName, BOOKS *newBook)   /*创建新书籍*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备插入语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"INSERT INTO books_default (bookname,keywords,authors,publisher,pubtime,quantity,isborrowed,category) VALUES('%s','%s','%s','%s','%s','%d','%d','%s');",newBook->bookname,newBook->keywords,newBook->authors,newBook->publisher,newBook->pubtime,newBook->quantity,newBook->isborrowed,newBook->category);
    /*执行插入语句*/
    sqlState = sqlite3_exec(db,queryString,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回执行结果（用于判断是否成功）*/
    return sqlState;
}
int bookModify(char *databaseName, int opcode, BOOKS *book) /*修改、删除书籍*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    char queryString[INSTRUCTION_LIMIT]={};
    /*准备相应语句*/
    switch(opcode)
    {
        case DELETEMODE:    /*删除书籍*/
            /*准备删除语句*/
            sprintf(queryString,"DELETE FROM books_default WHERE id = '%s';",book->id);
        break;
        case UPDATEMODE:    /*更改书籍信息*/
            /*准备更新语句*/
            sprintf(queryString,"UPDATE books_default SET bookname = '%s', keywords = '%s', authors = '%s', publisher = '%s', pubtime = '%s', quantity = '%d', isborrowed = '%d', category = '%s' WHERE id = '%s';",book->bookname,book->keywords,book->authors,book->publisher,book->pubtime,book->quantity,book->isborrowed,book->category,book->id);
        break;
    }
    /*执行相应操作*/
    sqlState = sqlite3_exec(db,queryString,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回执行结果（用于判断是否成功）*/
    return sqlState;
}
int freeSingleBook(BOOKS *book) /*释放单个BOOKS节点*/
{
    if(book->id != NULL) free(book->id);
    if(book->bookname != NULL) free(book->bookname);
    if(book->keywords != NULL) free(book->keywords);
    if(book->authors != NULL) free(book->authors);
    if(book->publisher != NULL) free(book->publisher);
    if(book->pubtime != NULL) free(book->pubtime);
    if(book->category != NULL) free(book->category);
    if(book->regtime != NULL) free(book->regtime);
    if(book != NULL) free(book);
    return SUCCESS;
}
int freeAllBooks(BOOKS *books)  /*释放一个BOOKS链表*/
{
    BOOKS *temp = books;
    while(books != NULL)
    {
        books = books->next;
        freeSingleBook(temp);
        temp = books;
    }
    return SUCCESS;
}
/*-------------*/
/*图书相关函数*/


/*借阅记录相关函数*/
/*-------------*/
int getAllBorrowInfoCallback(void *results, int colNumber, char **queryResult, char **colName)   /*处理所有借阅记录的回调函数*/
{
    /*指针类型转换*/
    BOOKSTATE *flag = (BOOKSTATE*)results;
    /*寻找末尾节点*/
    while(flag->next != NULL)   flag = flag->next;
    /*追加新节点*/
    flag->next = calloc(sizeof(BOOKSTATE),1);
    flag = flag->next;
    flag->bookid = calloc(sizeof(char),strlen(queryResult[2])+1);
    flag->borrowdate = calloc(sizeof(char),strlen(queryResult[3])+1);
    flag->duedate = calloc(sizeof(char),strlen(queryResult[4])+1);
    /*拷贝借阅记录*/
    flag->id = atoi(queryResult[0]);
    flag->userid = atoi(queryResult[1]);
    strcpy(flag->bookid,queryResult[2]);
    strcpy(flag->borrowdate,queryResult[3]);
    strcpy(flag->duedate,queryResult[4]);
    flag->terminated = atoi(queryResult[5]);
    flag->next = NULL;
    return SQLITE_OK;
}
BOOKSTATE *getAllBorrowInfo(char *databaseName) /*获取所有借阅记录*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备查询语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"SELECT * FROM bookstate;");
    /*建立链表头*/
    BOOKSTATE *results = calloc(sizeof(BOOKSTATE),1);
    results->next = NULL;
    /*查询用户信息*/
    sqlState = sqlite3_exec(db,queryString,getAllBorrowInfoCallback,(void*)results,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*处理链表（替换头节点）*/
    BOOKSTATE *temp = results;
    results = results->next;
    if(temp != NULL) free(temp);
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回查询结果*/
    return results;
}
int getBorrowInfoCallback(void *results, int colNumber, char **queryResult, char **colName)  /*处理指定借阅记录的回调函数*/
{
    /*指针类型转换*/
    BOOKSTATE *flag = (BOOKSTATE*)results;
    /*申请内存空间*/
    flag->bookid = calloc(sizeof(char),strlen(queryResult[2])+1);
    flag->borrowdate = calloc(sizeof(char),strlen(queryResult[3])+1);
    flag->duedate = calloc(sizeof(char),strlen(queryResult[4])+1);
    /*拷贝借阅记录*/
    flag->id = atoi(queryResult[0]);
    flag->userid = atoi(queryResult[1]);
    strcpy(flag->bookid,queryResult[2]);
    strcpy(flag->borrowdate,queryResult[3]);
    strcpy(flag->duedate,queryResult[4]);
    flag->terminated = atoi(queryResult[5]);
    flag->next = NULL;
    return SQLITE_OK;
}
BOOKSTATE *getBorrowInfo(char *databaseName, int borrowID)    /*获取指定借阅记录*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备查询语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"SELECT * FROM bookstate WHERE id = '%d';",borrowID);
    /*建立链表头*/
    BOOKSTATE *results = calloc(sizeof(BOOKSTATE),1);
    results->next = NULL;
    results->id = -1;
    /*查询用户信息*/
    sqlState = sqlite3_exec(db,queryString,getBorrowInfoCallback,(void*)results,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*结果处理*/
    if(results->id == -1)   /*借阅记录不存在*/
    {
        if(results != NULL) free(results);
        results = NULL;
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回查询结果*/
    return results;
}
int createNewBorrow(char *databaseName, BOOKSTATE *newBorrow)   /*创建新的借阅记录*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备插入语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    /*生成借阅日期、归还日期*/
    char borrowDate[64]={};
    char dueDate[64]={};
    strcpy(borrowDate,specificTime(0));
    strcpy(dueDate,specificTime(BORROW_TIME));
    sprintf(queryString,"INSERT INTO bookstate (userid,bookid,borrowdate,duedate,terminated) VALUES('%d','%s','%s','%s',0);",newBorrow->userid,newBorrow->bookid,borrowDate,dueDate);
    /*执行插入语句*/
    sqlState = sqlite3_exec(db,queryString,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回执行结果（用于判断是否成功）*/
    return sqlState;
}
int borrowModify(char *databaseName, int opcode, BOOKSTATE *borrow) /*修改、删除借阅记录*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    char queryString[INSTRUCTION_LIMIT]={};
    /*准备相应语句*/
    switch(opcode)
    {
        case DELETEMODE:    /*删除借阅记录*/
            /*准备删除语句*/
            sprintf(queryString,"DELETE FROM bookstate WHERE id = '%d';",borrow->id);
        break;
        case UPDATEMODE:    /*更新借阅记录*/
            /*准备更新语句*/
            sprintf(queryString,"UPDATE bookstate SET terminated = '%d' WHERE id = '%d';",borrow->terminated,borrow->id);
        break;
    }
    /*执行相应操作*/
    sqlState = sqlite3_exec(db,queryString,NULL,NULL,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回执行结果（用于判断是否成功）*/
    return sqlState;
}
BOOKSTATE *getBookRecordsByUser(char *databaseName, USERS *user)   /*查询指定用户的借阅记录*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备查询语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"SELECT * FROM bookstate WHERE userid = '%d';",user->id);
    /*建立链表头*/
    BOOKSTATE *results = calloc(sizeof(BOOKSTATE),1);
    results->next = NULL;
    /*查询书籍信息*/
    sqlState = sqlite3_exec(db,queryString,getAllBorrowInfoCallback,(void*)results,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*处理链表（替换头节点）*/
    BOOKSTATE *temp = results;
    results = results->next;
    if(temp != NULL) free(temp);
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回查询结果*/
    return results;
}
BOOKSTATE *borrowRecordLocation(char *databaseName, BOOKS *book, USERS *user)   /*定位借阅记录*/
{
    /*建立连接*/
    FILE *fp = fopen("dataBase.log","a+");
    sqlite3 *db;
    sqlite3_open(databaseName,&db);
    char *errMsg;
    int sqlState;
    /*准备查询语句*/
    char queryString[INSTRUCTION_LIMIT]={};
    sprintf(queryString,"SELECT * FROM bookstate WHERE userid = '%d' AND bookid = '%s' AND terminated = 0;",user->id,book->id);
    /*建立链表头*/
    BOOKSTATE *results = calloc(sizeof(BOOKSTATE),1);
    results->next = NULL;
    results->id = -1;
    /*查询用户信息*/
    sqlState = sqlite3_exec(db,queryString,getBorrowInfoCallback,(void*)results,&errMsg);
    if(sqlState != SQLITE_OK)   /*错误处理*/
    {
        fprintf(fp,"[EROOR]:%s\n",errMsg);
        sqlite3_free(errMsg);
    }
    /*结果处理*/
    if(results->id == -1)   /*借阅记录不存在*/
    {
        freeSingleBookRecord(results);
        results = NULL;
    }
    /*关闭连接*/
    fclose(fp);
    sqlite3_close(db);
    /*返回查询结果*/
    return results;
}
int freeSingleBookRecord(BOOKSTATE *record) /*释放单个BOOKSTATE节点*/
{
    if(record->bookid != NULL) free(record->bookid);
    if(record->borrowdate != NULL) free(record->borrowdate);
    if(record->duedate != NULL) free(record->duedate);
    if(record != NULL) free(record);
    return SUCCESS;
}
int freeAllBookRecords(BOOKSTATE *records)  /*释放一个BOOKSTATE链表*/
{
    BOOKSTATE *temp = records;
    while(records != NULL)
    {
        records = records->next;
        freeSingleBookRecord(temp);
        temp = records;
    }
    return SUCCESS;
}
/*-------------*/
/*借阅记录相关函数*/

/*其它辅助函数*/
/*-------------*/
char *specificTime(int offset)  /*获取偏移了指定天数（int offset）后的系统日期*/
{
    time_t currentTimeSeconds = time(NULL);
    time_t offsetTimeSeconds = currentTimeSeconds + offset*24*3600;
    return ctime(&offsetTimeSeconds);
}
/*-------------*/
/*其它辅助函数*/