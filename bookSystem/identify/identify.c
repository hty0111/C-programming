#include "identify.h"
#include "dataStore.h"


/*用户相关函数*/
/*-------------*/
int userLogIn(char *databaseName, char *username, char *passwords)  /*用户登陆验证*/
{
    /*查询用户信息*/
    int resultState = 0;
    USERS *queryResult = getUserInfo(databaseName,username);
    if(queryResult->id == -1)    resultState = USERNAME_NOT_FOUND;  /*用户不存在*/
    else if(strcmp(queryResult->passwords,passwords) != 0)   resultState = PASSWORDS_ERROR; /*密码错误*/
    else resultState = LOG_IN_SUCCESS;  /*登陆成功*/
    freeSingleUser(queryResult);    /*释放用户信息*/
    return resultState; /*返回登陆结果*/
}
USERS *AU_getUserInfo(char *databaseName, char *username, USERS *logInUser) /*带权限控制的用户信息获取函数*/
{
    int isAuthorized = userLogIn(databaseName,logInUser->username,logInUser->passwords);    /*身份认证*/
    if(isAuthorized != LOG_IN_SUCCESS)  return NULL;    /*身份认证失败*/
    int isSelf = !strcmp(username,logInUser->username); /*请求的用户信息是否属于用户本身*/
    if(isSelf)  return getUserInfo(databaseName,username);  /*返回结果*/
    int isAdmin = !strcmp("ADMIN",logInUser->mode);  /*权限认证*/
    if(!isAdmin)    return NULL;    /*权限认证失败*/
    return getUserInfo(databaseName,username);  /*返回结果*/
}
USERS *AU_getAllUserInfo(char *databaseName, USERS *logInUser)  /*带权限控制的所有用户信息获取函数*/
{
    int isAuthorized = userLogIn(databaseName,logInUser->username,logInUser->passwords);    /*身份认证*/
    if(isAuthorized != LOG_IN_SUCCESS)  return NULL;    /*身份认证失败*/
    int isAdmin = !strcmp("ADMIN",logInUser->mode);  /*权限认证*/
    if(!isAdmin)    return NULL;    /*权限认证失败*/
    return getAllUserInfo(databaseName);    /*返回结果*/
}
int AU_userModify(char *databaseName, int opcode, USERS *userToBeModified, USERS *logInUser)    /*带权限控制的修改、删除用户*/
{
    int isAuthorized = userLogIn(databaseName,logInUser->username,logInUser->passwords);    /*身份认证*/
    if(isAuthorized != LOG_IN_SUCCESS)  return AUTHORIZE_FAILED;    /*身份认证失败*/
    int isSelf = !strcmp(userToBeModified->username,logInUser->username);   /*请求修改的用户是否为用户本身*/
    if(isSelf)  return userModify(databaseName,opcode,userToBeModified);    /*执行相应操作并返回操作结果*/
    int isAdmin = !strcmp("ADMIN",logInUser->mode);  /*权限认证*/
    if(!isAdmin)    return PERMISSION_DENIED;    /*权限认证失败*/
    return userModify(databaseName,opcode,userToBeModified);    /*执行相应操作并返回操作结果*/
}
int AU_createNewUser(char *databaseName, USERS *newUser, USERS *admin)  /*带权限控制创建新用户*/
{
    /*普通用户不允许创建管理员*/
    if((admin == NULL||strcmp(admin->mode,"ADMIN")) && !strcmp(newUser->mode,"ADMIN"))  return PERMISSION_DENIED;
    if(admin != NULL && !strcmp(newUser->mode,"ADMIN")) /*管理员身份认证*/
    {
        int isAuthorized = userLogIn(databaseName,admin->username,admin->passwords);    /*身份认证*/
        if(isAuthorized != LOG_IN_SUCCESS)  return AUTHORIZE_FAILED;    /*身份认证失败*/
    }
    /*判断待创建用户的用户名是否已经存在*/
    if(userLogIn(databaseName,newUser->username,newUser->passwords) != USERNAME_NOT_FOUND)  return USERNAME_REPEATED;
    return createNewUser(databaseName,newUser); /*创建新用户并返回操作结果*/
}

/*-------------*/
/*用户相关函数*/


/*图书相关函数*/
/*-------------*/
int AU_createNewBook(char *databaseName, BOOKS *newBook, USERS *admin)   /*带权限管理创建新书籍*/
{
    if(admin == NULL||strcmp(admin->mode,"ADMIN"))  return PERMISSION_DENIED;   /*普通用户不允许创建书籍*/
    int isAuthorized = userLogIn(databaseName,admin->username,admin->passwords); /*身份认证*/
    if(isAuthorized != LOG_IN_SUCCESS)  return AUTHORIZE_FAILED;    /*身份认证失败*/
    return createNewBook(databaseName,newBook); /*创建新书籍并返回操作结果*/
}
int AU_bookModify(char *databaseName, int opcode, BOOKS *book, USERS *admin) /*带权限管理修改、删除书籍*/
{
    if(admin == NULL||strcmp(admin->mode,"ADMIN"))  return PERMISSION_DENIED;   /*普通用户不允许修改、创建书籍*/
    int isAuthorized = userLogIn(databaseName,admin->username,admin->passwords); /*身份认证*/
    if(isAuthorized != LOG_IN_SUCCESS)  return AUTHORIZE_FAILED;    /*身份认证失败*/
    return bookModify(databaseName,opcode,book);    /*修改书籍并返回操作结果*/
}
/*-------------*/
/*图书相关函数*/


/*借阅记录相关函数*/
/*-------------*/
BOOKSTATE *AU_getAllBookRecords(char *databaseName, USERS *admin)  /*带权限管理查询所有借阅记录*/
{
    return getAllBorrowInfo(databaseName);  /*返回查询结果*/
}
BOOKSTATE *AU_getBookRecordsByUser(char *databaseName, char *username, USERS *logInUser)   /*带权限管理查询指定用户的借阅记录*/
{
    if((logInUser == NULL||strcmp(logInUser->mode,"ADMIN")) && strcmp(logInUser->username,username))  return NULL; /*普通用户不允许查询它人的借阅记录*/
    int isAuthorized = userLogIn(databaseName,logInUser->username,logInUser->passwords); /*身份认证*/
    if(isAuthorized != LOG_IN_SUCCESS)  return NULL;    /*身份认证失败*/
    /*查询借阅记录并返回查询结果*/
    USERS *user = getUserInfo(databaseName,username);
    BOOKSTATE *result = getBookRecordsByUser(databaseName,user);
    freeSingleUser(user);
    return result;
}
int borrowBook(char *databaseName, BOOKS *bookToBeBorrowed, USERS *logInUser)  /*借阅图书*/
{
    BOOKS *remote = getBookInfo(databaseName,bookToBeBorrowed->id);
    int isAuthorized = userLogIn(databaseName,logInUser->username,logInUser->passwords); /*身份认证*/
    if(isAuthorized != LOG_IN_SUCCESS)  return AUTHORIZE_FAILED;    /*身份认证失败*/
    if(remote == NULL || remote->quantity <= 0) return NO_BOOK_LEFT;        /*此书已无库存*/
    /*用户信息&书籍信息更新*/
    bookToBeBorrowed->isborrowed += 1;
    bookToBeBorrowed->quantity -= 1;
    logInUser->borrowedbooks += 1;
    bookModify(databaseName,UPDATEMODE,bookToBeBorrowed);
    userModify(databaseName,UPDATEMODE,logInUser);
    /*创建借阅记录*/
    BOOKSTATE newBorrow;
    newBorrow.userid = logInUser->id;
    newBorrow.bookid = calloc(sizeof(char),strlen(bookToBeBorrowed->id)+1);
    strcpy(newBorrow.bookid,bookToBeBorrowed->id);
    int sqlState = createNewBorrow(databaseName,&newBorrow);
    if(newBorrow.bookid != NULL) free(newBorrow.bookid);
    freeSingleBook(remote);
    /*返回操作结果*/
    return sqlState;
}
int returnBook(char *databaseName, BOOKS *bookToBeReturned, USERS *logInUser)  /*归还图书*/
{
    int isAuthorized = userLogIn(databaseName,logInUser->username,logInUser->passwords); /*身份认证*/
    if(isAuthorized != LOG_IN_SUCCESS)  return AUTHORIZE_FAILED;    /*身份认证失败*/
    /*用户信息&书籍信息更新*/
    BOOKSTATE *record = borrowRecordLocation(databaseName,bookToBeReturned,logInUser);
    if(record == NULL) return SUCCESS;
    bookToBeReturned->isborrowed -= 1;
    bookToBeReturned->quantity += 1;
    logInUser->borrowedbooks -= 1;
    bookModify(databaseName,UPDATEMODE,bookToBeReturned);
    userModify(databaseName,UPDATEMODE,logInUser);
    /*更新借阅记录*/
    record->terminated = 1;
    int sqlState = borrowModify(databaseName,UPDATEMODE,record);
    freeSingleBookRecord(record);
    return sqlState;
}
/*-------------*/
/*借阅记录相关函数*/