#include "netClient.h"
char SERVER_ADDRESS[256] = DEFAULT_ADDRESS;
static void apiUserLogInCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    int *result = calloc(sizeof(int),1);
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            *result = atoi((hm->body).p);
            nc->mgr->user_data = (void*)result;
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
int userLogIn(char *databaseName, char *username, char *passwords)  /*用户登陆验证*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiUserLogIn.p);
    USERS *user = calloc(sizeof(USERS),1);
    user->id = 0;
    user->username = calloc(sizeof(char),1);
    user->passwords = calloc(sizeof(char),1);
    user->gender = NULL;
    user->department = NULL;
    user->borrowedbooks = 0;
    user->mode = NULL;
    user->regtime = NULL;
    user->next = NULL;
    strcpy(user->username,username);
    strcpy(user->passwords,passwords);
    char *sendData = usersToJson(user);
    mg_connect_http(&mgr,apiUserLogInCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    int result = mgr.user_data==NULL?-1:*((int*)mgr.user_data);
    free(mgr.user_data);
    mg_mgr_free(&mgr);
    free(sendData);
    freeSingleUser(user);
    return result;
}

static void apiGetUserInfoCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            if(memcmp((hm->body).p,"[",1))
            {
                nc->mgr->user_data = NULL;
            }
            else
            {
                USERS *result = jsonToUsers((hm->body).p);
                nc->mgr->user_data = (void*)result;
            }
            isClosed = 1; 
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
USERS *AU_getUserInfo(char *databaseName, char *username, USERS *logInUser) /*带权限控制的用户信息获取函数*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiGetUserInfo.p);
    USERS *user = calloc(sizeof(USERS),1);
    user->id = 0;
    user->username = calloc(sizeof(char),1);
    user->passwords = NULL;
    user->gender = NULL;
    user->department = NULL;
    user->borrowedbooks = 0;
    user->mode = NULL;
    user->regtime = NULL;
    strcpy(user->username,username);
    user->next = logInUser;
    char *sendData = usersToJson(user);
    mg_connect_http(&mgr,apiGetUserInfoCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    USERS *result = (USERS*)mgr.user_data;
    mg_mgr_free(&mgr);
    free(sendData);
    freeSingleUser(user);
    return result;
}

static void apiGetAllUserInfoCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            if(memcmp("[",(hm->body).p,1))
            {
                nc->mgr->user_data = NULL;
            }
            else
            {
                USERS *result = jsonToUsers((hm->body).p);
                nc->mgr->user_data = (void*)result;
            }
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
USERS *AU_getAllUserInfo(char *databaseName, USERS *logInUser)  /*带权限控制的所有用户信息获取函数*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiGetAllUserInfo.p);
    char *sendData = usersToJson(logInUser);
    mg_connect_http(&mgr,apiGetAllUserInfoCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    USERS *result = (USERS*)mgr.user_data;
    mg_mgr_free(&mgr);
    free(sendData);
    return result;
}
static void apiUserModifyCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    int *result = calloc(sizeof(int),1);
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            *result = atoi((hm->body).p);
            nc->mgr->user_data = (void*)result;
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
int AU_userModify(char *databaseName, int opcode, USERS *userToBeModified, USERS *logInUser)    /*带权限控制的修改、删除用户*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiUserModify.p);
    cJSON *data = cJSON_CreateArray();
    cJSON_AddItemToArray(data,cJSON_CreateNumber(opcode));
    char *user1 = usersToJson(userToBeModified);
    char *user2 = usersToJson(logInUser);
    cJSON *array1 = cJSON_Parse(user1);
    cJSON *array2 = cJSON_Parse(user2);
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(array1,0));
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(array2,0));
    char *sendData = cJSON_PrintUnformatted(data);
    mg_connect_http(&mgr,apiUserModifyCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    int result = mgr.user_data==NULL?-1:*((int*)mgr.user_data);
    free(mgr.user_data);
    free(user1);
    free(user2);
    free(sendData);
    cJSON_Delete(data);
    mg_mgr_free(&mgr);
    return result;
}
static void apiCreateNewUserCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    int *result = calloc(sizeof(int),1);
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            *result = atoi((hm->body).p);
            nc->mgr->user_data = (void*)result;
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
int AU_createNewUser(char *databaseName, USERS *newUser, USERS *admin)  /*带权限控制创建新用户*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiCreateNewUser.p);
    newUser->next = admin;
    char *sendData = usersToJson(newUser);
    mg_connect_http(&mgr,apiCreateNewUserCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    int result = mgr.user_data==NULL?-1:*((int*)mgr.user_data);
    free(mgr.user_data);
    free(sendData);
    mg_mgr_free(&mgr);
    return result;
}

static void apiGetAllBooksInfoCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            if(memcmp("[",(hm->body).p,1))
            {
                nc->mgr->user_data = NULL;
            }
            else
            {
                BOOKS *result = jsonToBooks((hm->body).p);
                nc->mgr->user_data = (void*)result;
            }
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
BOOKS *getAllBooksInfo(char *databaseName)  /*获取所有书籍信息*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiGetAllBooksInfo.p);
    char *sendData = databaseName;
    mg_connect_http(&mgr,apiGetAllBooksInfoCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    BOOKS *result = (BOOKS*)mgr.user_data;
    mg_mgr_free(&mgr);
    return result;
}

static void apiGetBooksByCategoryCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            if(memcmp("[",(hm->body).p,1))
            {
                nc->mgr->user_data = NULL;
            }
            else
            {
                BOOKS *result = jsonToBooks((hm->body).p);
                nc->mgr->user_data = (void*)result;
            }
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
BOOKS *getBooksByCategory(char *databaseName, char *categoryName)   /*按分类获取书籍信息*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiGetBooksByCategory.p);
    char *sendData = categoryName;
    mg_connect_http(&mgr,apiGetBooksByCategoryCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    BOOKS *result = (BOOKS*)mgr.user_data;
    mg_mgr_free(&mgr);
    return result;
}

static void apiGetBookInfoCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            if(memcmp("[",(hm->body).p,1))
            {
                nc->mgr->user_data = NULL;
            }
            else
            {
                BOOKS *result = jsonToBooks((hm->body).p);
                nc->mgr->user_data = (void*)result;
            }
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
BOOKS *getBookInfo(char *databaseName, char *bookID)  /*获取指定书籍信息*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiGetBookInfo.p);
    char *sendData = bookID;
    mg_connect_http(&mgr,apiGetBookInfoCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    BOOKS *result = (BOOKS*)mgr.user_data;
    mg_mgr_free(&mgr);
    return result;
}

static void apiCreateNewBookCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    int *result = calloc(sizeof(int),1);
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            *result = atoi((hm->body).p);
            nc->mgr->user_data = (void*)result;
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
int AU_createNewBook(char *databaseName, BOOKS *newBook, USERS *admin)   /*带权限管理创建新书籍*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiCreateNewBook.p);
    cJSON *data = cJSON_CreateArray();
    char *s1 = booksToJson(newBook);
    char *s2 = usersToJson(admin);
    cJSON *data1 = cJSON_Parse(s1);
    cJSON *data2 = cJSON_Parse(s2);
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(data1,0));
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(data2,0));
    char *sendData = cJSON_PrintUnformatted(data);
    mg_connect_http(&mgr,apiCreateNewBookCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    int result = mgr.user_data==NULL?-1:*((int*)mgr.user_data);
    free(mgr.user_data);
    free(s1);
    free(s2);
    free(sendData);
    cJSON_Delete(data);
    mg_mgr_free(&mgr);
    return result;
}

static void apiBookModifyCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    int *result = calloc(sizeof(int),1);
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            *result = atoi((hm->body).p);
            nc->mgr->user_data = (void*)result;
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
int AU_bookModify(char *databaseName, int opcode, BOOKS *book, USERS *admin) /*带权限管理修改、删除书籍*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiBookModify.p);
    cJSON *data = cJSON_CreateArray();
    cJSON_AddItemToArray(data,cJSON_CreateNumber(opcode));
    char *s1 = booksToJson(book);
    char *s2 = usersToJson(admin);
    cJSON *array1 = cJSON_Parse(s1);
    cJSON *array2 = cJSON_Parse(s2);
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(array1,0));
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(array2,0));
    char *sendData = cJSON_PrintUnformatted(data);
    mg_connect_http(&mgr,apiBookModifyCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    int result = mgr.user_data==NULL?-1:*((int*)mgr.user_data);
    free(mgr.user_data);
    free(s1);
    free(s2);
    free(sendData);
    cJSON_Delete(data);
    mg_mgr_free(&mgr);
    return result;
}

static void apiGetAllBookRecordsCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            if(memcmp("[",(hm->body).p,1))
            {
                nc->mgr->user_data = NULL;
            }
            else
            {
                BOOKSTATE *result = jsonToRecords((hm->body).p);
                nc->mgr->user_data = (void*)result;
            }
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
BOOKSTATE *AU_getAllBookRecords(char *databaseName, USERS *admin)  /*带权限管理查询所有借阅记录*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiGetAllBookRecords.p);
    char *sendData = usersToJson(admin);
    mg_connect_http(&mgr,apiGetAllBookRecordsCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    BOOKSTATE *result = (BOOKSTATE*)mgr.user_data;
    mg_mgr_free(&mgr);
    free(sendData);
    return result;
}

static void apiGetBookRecordsByUserCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            if(memcmp("[",(hm->body).p,1))
            {
                nc->mgr->user_data = NULL;
            }
            else
            {
                BOOKSTATE *result = jsonToRecords((hm->body).p);
                nc->mgr->user_data = (void*)result;
            }
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
BOOKSTATE *AU_getBookRecordsByUser(char *databaseName, char *username, USERS *logInUser)   /*带权限管理查询指定用户的借阅记录*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiGetBookRecordsByUser.p);
    USERS *user = calloc(sizeof(USERS),1);
    user->id = 0;
    user->username = calloc(sizeof(char),1);
    user->passwords = NULL;
    user->gender = NULL;
    user->department = NULL;
    user->borrowedbooks = 0;
    user->mode = NULL;
    user->regtime = NULL;
    strcpy(user->username,username);
    user->next = logInUser;
    char *sendData = usersToJson(user);
    mg_connect_http(&mgr,apiGetBookRecordsByUserCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    BOOKSTATE *result = (BOOKSTATE*)mgr.user_data;
    mg_mgr_free(&mgr);
    free(sendData);
    freeSingleUser(user);
    return result;
}

static void apiBorrowBookCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    int *result = calloc(sizeof(int),1);
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            *result = atoi((hm->body).p);
            nc->mgr->user_data = (void*)result;
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
int borrowBook(char *databaseName, BOOKS *bookToBeBorrowed, USERS *logInUser)  /*借阅图书*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiBorrowBook.p);
    cJSON *data = cJSON_CreateArray();
    char *s1 = booksToJson(bookToBeBorrowed);
    char *s2 = usersToJson(logInUser);
    cJSON *data1 = cJSON_Parse(s1);
    cJSON *data2 = cJSON_Parse(s2);
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(data1,0));
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(data2,0));
    char *sendData = cJSON_PrintUnformatted(data);
    mg_connect_http(&mgr,apiBorrowBookCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    int result = mgr.user_data==NULL?-1:*((int*)mgr.user_data);
    free(mgr.user_data);
    free(s1);
    free(s2);
    free(sendData);
    cJSON_Delete(data);
    mg_mgr_free(&mgr);
    if(result == SUCCESS)
    {
        bookToBeBorrowed->isborrowed += 1;
        bookToBeBorrowed->quantity -= 1;
        logInUser->borrowedbooks  += 1;
    }
    return result;
}

static void apiReturnBookCallback(struct mg_connection *nc, int ev, void *ev_data)
{
    struct http_message *hm = (struct http_message *) ev_data;
    int *result = calloc(sizeof(int),1);
    switch(ev)
    {
        case MG_EV_HTTP_REPLY:
        {
            *result = atoi((hm->body).p);
            nc->mgr->user_data = (void*)result;
            isClosed = 1;
        }
        break;
        case MG_EV_CLOSE:
        isClosed = 1;
        break;
        default:
        break;
    }
}
int returnBook(char *databaseName, BOOKS *bookToBeReturned, USERS *logInUser)  /*归还图书*/
{
    isClosed = 0;
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    char address[256]={};
    strcat(address,SERVER_ADDRESS);
    strcat(address,apiReturnBook.p);
    cJSON *data = cJSON_CreateArray();
    char *s1 = booksToJson(bookToBeReturned);
    char *s2 = usersToJson(logInUser);
    cJSON *data1 = cJSON_Parse(s1);
    cJSON *data2 = cJSON_Parse(s2);
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(data1,0));
    cJSON_AddItemToArray(data,cJSON_GetArrayItem(data2,0));
    char *sendData = cJSON_PrintUnformatted(data);
    mg_connect_http(&mgr,apiReturnBookCallback,address,NULL,sendData);
    while (isClosed == 0) 
    {
        mg_mgr_poll(&mgr, 1000);
    }
    int result = mgr.user_data==NULL?-1:*((int*)mgr.user_data);
    free(mgr.user_data);
    free(s1);
    free(s2);
    free(sendData);
    cJSON_Delete(data);
    mg_mgr_free(&mgr);
    if(result == SUCCESS)
    {
        bookToBeReturned->isborrowed -= 1;
        bookToBeReturned->quantity += 1;
        logInUser->borrowedbooks  -= 1;
    }
    return result;
}


int freeSingleUser(USERS *user) /*释放单个USERS节点*/
{
    free(user->username);
    free(user->passwords);
    free(user->gender);
    free(user->department);
    free(user->mode);
    free(user->regtime);
    free(user);
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

int freeSingleBook(BOOKS *book) /*释放单个BOOKS节点*/
{
    free(book->id);
    free(book->bookname);
    free(book->keywords);
    free(book->authors);
    free(book->publisher);
    free(book->pubtime);
    free(book->category);
    free(book->regtime);
    free(book);
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

int freeSingleBookRecord(BOOKSTATE *record) /*释放单个BOOKSTATE节点*/
{
    free(record->bookid);
    free(record->borrowdate);
    free(record->duedate);
    free(record);
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

char *usersToJson(USERS *users)
{
  cJSON *data;
  data = cJSON_CreateArray();
  while(users != NULL)
  {
    cJSON *temp;
    cJSON_AddItemToArray(data,temp = cJSON_CreateObject());
    cJSON_AddNumberToObject(temp,"id",users->id);
    cJSON_AddStringToObject(temp,"username",users->username==NULL?"NULL":users->username);
    cJSON_AddStringToObject(temp,"passwords",users->passwords==NULL?"NULL":users->passwords);
    cJSON_AddStringToObject(temp,"gender",users->gender==NULL?"NULL":users->gender);
    cJSON_AddStringToObject(temp,"department",users->department==NULL?"NULL":users->department);
    cJSON_AddNumberToObject(temp,"borrowedbooks",users->borrowedbooks);
    cJSON_AddStringToObject(temp,"mode",users->mode==NULL?"NULL":users->mode);
    cJSON_AddStringToObject(temp,"regtime",users->regtime==NULL?"NULL":users->regtime);
    users = users->next;
  }
  char *s = cJSON_PrintUnformatted(data);
  cJSON_Delete(data);
  return s;
}

char *booksToJson(BOOKS *books)
{
  cJSON *data;
  data = cJSON_CreateArray();
  while(books != NULL)
  {
    cJSON *temp;
    cJSON_AddItemToArray(data,temp = cJSON_CreateObject());
    cJSON_AddStringToObject(temp,"id",books->id==NULL?"NULL":books->id);
    cJSON_AddStringToObject(temp,"bookname",books->bookname==NULL?"NULL":books->bookname);
    cJSON_AddStringToObject(temp,"keywords",books->keywords==NULL?"NULL":books->keywords);
    cJSON_AddStringToObject(temp,"authors",books->authors==NULL?"NULL":books->authors);
    cJSON_AddStringToObject(temp,"publisher",books->publisher==NULL?"NULL":books->publisher);
    cJSON_AddStringToObject(temp,"pubtime",books->pubtime==NULL?"NULL":books->pubtime);
    cJSON_AddNumberToObject(temp,"quantity",books->quantity);
    cJSON_AddNumberToObject(temp,"isborrowed",books->isborrowed);
    cJSON_AddStringToObject(temp,"category",books->category==NULL?"NULL":books->category);
    cJSON_AddStringToObject(temp,"regtime",books->regtime==NULL?"NULL":books->regtime);
    books = books->next;
  }
  char *s = cJSON_PrintUnformatted(data);
  cJSON_Delete(data);
  return s;
}

char *recordsToJson(BOOKSTATE *records)
{
  cJSON *data;
  data = cJSON_CreateArray();
  while(records != NULL)
  {
    cJSON *temp;
    cJSON_AddItemToArray(data,temp = cJSON_CreateObject());
    cJSON_AddNumberToObject(temp,"id",records->id);
    cJSON_AddNumberToObject(temp,"userid",records->userid);
    cJSON_AddStringToObject(temp,"bookid",records->bookid==NULL?"NULL":records->bookid);
    cJSON_AddStringToObject(temp,"borrowdate",records->borrowdate==NULL?"NULL":records->borrowdate);
    cJSON_AddStringToObject(temp,"duedate",records->duedate==NULL?"NULL":records->duedate);
    cJSON_AddNumberToObject(temp,"terminated",records->terminated);
    records = records->next;
  }
  char *s = cJSON_PrintUnformatted(data);
  cJSON_Delete(data);
  return s;
}

USERS *jsonToUsers(const char *data)
{
  USERS *head = calloc(sizeof(USERS),1);
  USERS *present = head;
  head->next = NULL;
  cJSON *array = cJSON_Parse(data);
  int size = cJSON_GetArraySize(array);
  for(int i=0;i<size;i++)
  {
    present->next = calloc(sizeof(USERS),1);
    present = present->next;
    cJSON *temp = cJSON_GetArrayItem(array,i);
    present->username = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"username")->valuestring)+1);
    present->passwords = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"passwords")->valuestring)+1);
    present->gender = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"gender")->valuestring)+1);
    present->department = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"department")->valuestring)+1);
    present->mode = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"mode")->valuestring)+1);
    present->regtime = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"regtime")->valuestring)+1);
    present->id = cJSON_GetObjectItem(temp,"id")->valueint;
    strcpy(present->username,cJSON_GetObjectItem(temp,"username")->valuestring);
    strcpy(present->passwords,cJSON_GetObjectItem(temp,"passwords")->valuestring);
    strcpy(present->gender,cJSON_GetObjectItem(temp,"gender")->valuestring);
    strcpy(present->department,cJSON_GetObjectItem(temp,"department")->valuestring);
    present->borrowedbooks = cJSON_GetObjectItem(temp,"borrowedbooks")->valueint;
    strcpy(present->mode,cJSON_GetObjectItem(temp,"mode")->valuestring);
    strcpy(present->regtime,cJSON_GetObjectItem(temp,"regtime")->valuestring);
    present->next = NULL;
  }
  present = head->next;
  free(head);
  cJSON_Delete(array);
  return present;
}

BOOKS *jsonToBooks(const char *data)
{
  BOOKS *head = calloc(sizeof(BOOKS),1);
  BOOKS *present = head;
  present->next = NULL;
  cJSON *array = cJSON_Parse(data);
  int size = cJSON_GetArraySize(array);
  for(int i=0;i<size;i++)
  {
    present->next = calloc(sizeof(BOOKS),1);
    present = present->next;
    cJSON *temp = cJSON_GetArrayItem(array,i);
    present->id = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"id")->valuestring)+1);
    present->bookname = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"bookname")->valuestring)+1);
    present->keywords = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"keywords")->valuestring)+1);
    present->authors = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"authors")->valuestring)+1);
    present->publisher = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"publisher")->valuestring)+1);
    present->pubtime = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"pubtime")->valuestring)+1);
    present->category = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"category")->valuestring)+1);
    present->regtime = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"regtime")->valuestring)+1);
    strcpy(present->id,cJSON_GetObjectItem(temp,"id")->valuestring);
    strcpy(present->bookname,cJSON_GetObjectItem(temp,"bookname")->valuestring);
    strcpy(present->keywords,cJSON_GetObjectItem(temp,"keywords")->valuestring);
    strcpy(present->authors,cJSON_GetObjectItem(temp,"authors")->valuestring);
    strcpy(present->publisher,cJSON_GetObjectItem(temp,"publisher")->valuestring);
    strcpy(present->pubtime,cJSON_GetObjectItem(temp,"pubtime")->valuestring);
    present->quantity = cJSON_GetObjectItem(temp,"quantity")->valueint;
    present->isborrowed = cJSON_GetObjectItem(temp,"isborrowed")->valueint;
    strcpy(present->category,cJSON_GetObjectItem(temp,"category")->valuestring);
    strcpy(present->regtime,cJSON_GetObjectItem(temp,"regtime")->valuestring);
    present->next = NULL;
  }
  present = head->next;
  free(head);
  cJSON_Delete(array);
  return present;
}

BOOKSTATE *jsonToRecords(const char *data)
{
  BOOKSTATE *head = calloc(sizeof(BOOKSTATE),1);
  BOOKSTATE *present = head;
  present->next = NULL;
  cJSON *array = cJSON_Parse(data);
  int size = cJSON_GetArraySize(array);
  for(int i=0;i<size;i++)
  {
    present->next = calloc(sizeof(BOOKSTATE),1);
    present = present->next;
    cJSON *temp = cJSON_GetArrayItem(array,i);
    present->bookid = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"bookid")->valuestring)+1);
    present->borrowdate = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"borrowdate")->valuestring)+1);
    present->duedate = calloc(sizeof(char),strlen(cJSON_GetObjectItem(temp,"duedate")->valuestring)+1);
    present->id = cJSON_GetObjectItem(temp,"id")->valueint;
    present->userid = cJSON_GetObjectItem(temp,"userid")->valueint;
    strcpy(present->bookid,cJSON_GetObjectItem(temp,"bookid")->valuestring);
    strcpy(present->borrowdate,cJSON_GetObjectItem(temp,"borrowdate")->valuestring);
    strcpy(present->duedate,cJSON_GetObjectItem(temp,"duedate")->valuestring);
    present->terminated = cJSON_GetObjectItem(temp,"terminated")->valueint;
    present->next = NULL;
  }
  present = head->next;
  free(head);
  cJSON_Delete(array);
  return present;
}