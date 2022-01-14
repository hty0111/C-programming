#include "netServer.h"

static int has_prefix(const struct mg_str *uri, const struct mg_str *prefix) {
  return uri->len > prefix->len && memcmp(uri->p, prefix->p, prefix->len) == 0;
} /*辅助函数，用于判断网络请求的前缀*/

static int is_equal(const struct mg_str *s1, const struct mg_str *s2) {
  return s1->len == s2->len && memcmp(s1->p, s2->p, s2->len) == 0;
} /*辅助函数，用于判断网络请求的前缀*/

/*
  netServer的回调函数，用于处理各类请求
*/
static void ev_handler(struct mg_connection *nc, int ev, void *ev_data){
    static const struct mg_str test = MG_MK_STR("/print");
    struct http_message *httpMessage = (struct http_message *) ev_data;
    switch(ev)
    {
        case MG_EV_HTTP_REQUEST:  /*接收到HTTP请求*/
        {
            if(is_equal(&(httpMessage->method),&postMethod))   /*POST请求*/
            {
                if(has_prefix(&(httpMessage->uri),&test))   /*API for post test*/
                {
                    printf("test success!\n");
                    mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",25,"Welcome to use booksystem");
                    break;
                }
                if(has_prefix(&(httpMessage->uri),&apiUserLogIn))   /*用户登录使用的API*/
                {
                  /*数据处理*/
                  USERS *user = jsonToUsers((httpMessage->body).p);
                  int result = userLogIn(DATABASE_NAME,user->username,user->passwords);
                  char number[64]={};
                  sprintf(number,"%d",result);
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(number),number);
                  freeAllUsers(user);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiGetUserInfo)) /*获取单个用户信息的API*/
                {
                  /*数据处理*/
                  USERS *user = jsonToUsers((httpMessage->body).p);
                  USERS *result = AU_getUserInfo(DATABASE_NAME,user->username,user->next);
                  char *results;
                  if(result == NULL)
                  {
                    results = calloc(sizeof(char),5);
                    strcpy(results,"NULL");
                  }
                  else
                  {
                    results = usersToJson(result);
                  }
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(results),results);
                  free(results);
                  freeAllUsers(result);
                  freeAllUsers(user);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiGetAllUserInfo))  /*获取所有用户信息的API*/
                {
                  /*数据处理*/
                  USERS *user = jsonToUsers((httpMessage->body).p);
                  USERS *result = AU_getAllUserInfo(DATABASE_NAME,user);
                  char *results;
                  if(result == NULL)
                  {
                    results = calloc(sizeof(char),5);
                    strcpy(results,"NULL");
                  }
                  else
                  {
                    results = usersToJson(result);
                  }
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(results),results);
                  free(results);
                  freeAllUsers(result);
                  freeAllUsers(user);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiUserModify))  /*修改、删除用户的API*/
                {
                  /*数据处理*/
                  cJSON *temp = cJSON_Parse((httpMessage->body).p);
                  int opcode = cJSON_GetArrayItem(temp,0)->valueint;
                  cJSON_DeleteItemFromArray(temp,0);
                  char *mid = cJSON_PrintUnformatted(temp);
                  USERS *user = jsonToUsers(mid);
                  int result = AU_userModify(DATABASE_NAME,opcode,user,user->next);
                  char number[64]={};
                  sprintf(number,"%d",result);
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(number),number);
                  free(mid);
                  cJSON_Delete(temp);
                  freeAllUsers(user);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiCreateNewUser)) /*创建新用户的API*/
                {
                  /*数据处理*/
                  USERS *user = jsonToUsers((httpMessage->body).p);
                  int result = AU_createNewUser(DATABASE_NAME,user,user->next);
                  char number[64]={};
                  sprintf(number,"%d",result);
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(number),number);
                  freeAllUsers(user);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiGetBooksByCategory))  /*按分类获取书籍信息的API*/
                {
                  /*数据处理*/
                  BOOKS *book = getBooksByCategory(DATABASE_NAME,(httpMessage->body).p);
                  char *results;
                  if(book == NULL)
                  {
                    results = calloc(sizeof(char),5);
                    strcpy(results,"NULL");
                  }
                  else
                  {
                    results = booksToJson(book);
                  }
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(results),results);
                  free(results);
                  freeAllBooks(book);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiGetAllBooksInfo)) /*获取所有书籍信息的API*/
                {
                  /*数据处理*/
                  BOOKS *book = getAllBooksInfo(DATABASE_NAME);
                  char *results;
                  if(book == NULL)
                  {
                    results = calloc(sizeof(char),5);
                    strcpy(results,"NULL");
                  }
                  else
                  {
                    results = booksToJson(book);
                  }
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(results),results);
                  free(results);
                  freeAllBooks(book);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiGetBookInfo)) /*获取单个书籍信息的API*/
                {
                  /*数据处理*/
                  BOOKS *book = getBookInfo(DATABASE_NAME,(httpMessage->body).p);
                  char *results;
                  if(book == NULL)
                  {
                    results = calloc(sizeof(char),5);
                    strcpy(results,"NULL");
                  }
                  else
                  {
                    results = booksToJson(book);
                  }
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(results),results);
                  free(results);
                  freeAllBooks(book);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiCreateNewBook)) /*创建新书籍的API*/
                {
                  /*数据处理*/
                  cJSON *data = cJSON_Parse((httpMessage->body).p);
                  cJSON *data1 = cJSON_CreateArray();
                  char *s1 = cJSON_PrintUnformatted(cJSON_GetArrayItem(data,0));
                  cJSON *t1 = cJSON_Parse(s1);
                  free(s1);
                  cJSON_AddItemToArray(data1,t1);
                  char *temp = cJSON_PrintUnformatted(data1);
                  BOOKS *book = jsonToBooks(temp);
                  free(temp);
                  cJSON_Delete(data1);
                  cJSON *data2 = cJSON_CreateArray();
                  s1 = cJSON_PrintUnformatted(cJSON_GetArrayItem(data,1));
                  cJSON *t2 = cJSON_Parse(s1);
                  free(s1);
                  cJSON_AddItemToArray(data2,t2);
                  temp = cJSON_PrintUnformatted(data2);
                  USERS *user = jsonToUsers(temp);
                  free(temp);
                  cJSON_Delete(data2);
                  int result = AU_createNewBook(DATABASE_NAME,book,user);
                  char number[64]={};
                  sprintf(number,"%d",result);
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(number),number);
                  freeSingleBook(book);
                  freeSingleUser(user);
                  cJSON_Delete(data);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiBookModify))  /*修改、删除书籍的API*/
                {
                  /*数据处理*/
                  cJSON *data = cJSON_Parse((httpMessage->body).p);
                  int opcode = cJSON_GetArrayItem(data,0)->valueint;
                  cJSON_DeleteItemFromArray(data,0);
                  cJSON *data1 = cJSON_CreateArray();
                  char *s1 = cJSON_PrintUnformatted(cJSON_GetArrayItem(data,0));
                  cJSON *t1 = cJSON_Parse(s1);
                  free(s1);
                  cJSON_AddItemToArray(data1,t1);
                  char *temp = cJSON_PrintUnformatted(data1);
                  BOOKS *book = jsonToBooks(temp);
                  free(temp);
                  cJSON_Delete(data1);
                  cJSON *data2 = cJSON_CreateArray();
                  s1 = cJSON_PrintUnformatted(cJSON_GetArrayItem(data,1));
                  cJSON *t2 = cJSON_Parse(s1);
                  free(s1);
                  cJSON_AddItemToArray(data2,t2);
                  temp = cJSON_PrintUnformatted(data2);
                  USERS *user = jsonToUsers(temp);
                  free(temp);
                  cJSON_Delete(data2);
                  int result = AU_bookModify(DATABASE_NAME,opcode,book,user);
                  char number[64]={};
                  sprintf(number,"%d",result);
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(number),number);
                  freeSingleBook(book);
                  freeSingleUser(user);
                  cJSON_Delete(data);
                  break;
                }
                if(has_prefix(&(httpMessage->uri),&apiGetAllBookRecords)) /*获取所有借阅记录的API*/
                {
                  /*数据处理*/
                  USERS *user = jsonToUsers((httpMessage->body).p);
                  BOOKSTATE *records = AU_getAllBookRecords(DATABASE_NAME,user);
                  char *results;
                  if(records == NULL)
                  {
                    results = calloc(sizeof(char),5);
                    strcpy(results,"NULL");
                  }
                  else
                  {
                    results = recordsToJson(records);
                  }
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(results),results);
                  free(results);
                  freeSingleUser(user);
                  freeAllBookRecords(records);
                  break;
                } 
                if(has_prefix(&(httpMessage->uri),&apiGetBookRecordsByUser))  /*按用户获取借阅记录的API*/
                {
                  /*数据处理*/
                  USERS *user = jsonToUsers((httpMessage->body).p);                  
                  BOOKSTATE *records = AU_getBookRecordsByUser(DATABASE_NAME,user->username,user->next);
                  char *results;
                  if(records == NULL)
                  {
                    results = calloc(sizeof(char),5);
                    strcpy(results,"NULL");
                  }
                  else
                  {
                    results = recordsToJson(records);
                  }
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(results),results);
                  free(results);
                  freeAllUsers(user);
                  freeAllBookRecords(records);
                  break;
                } 
                if(has_prefix(&(httpMessage->uri),&apiBorrowBook))  /*借阅书籍的API*/
                {
                  /*数据处理*/
                  cJSON *data = cJSON_Parse((httpMessage->body).p);
                  cJSON *data1 = cJSON_CreateArray();
                  char *s1 = cJSON_PrintUnformatted(cJSON_GetArrayItem(data,0));
                  cJSON *t1 = cJSON_Parse(s1);
                  free(s1);
                  cJSON_AddItemToArray(data1,t1);
                  char *temp = cJSON_PrintUnformatted(data1);
                  BOOKS *book = jsonToBooks(temp);
                  free(temp);
                  cJSON_Delete(data1);
                  cJSON *data2 = cJSON_CreateArray();
                  s1 = cJSON_PrintUnformatted(cJSON_GetArrayItem(data,1));
                  cJSON *t2 = cJSON_Parse(s1);
                  free(s1);
                  cJSON_AddItemToArray(data2,t2);
                  temp = cJSON_PrintUnformatted(data2);
                  USERS *user = jsonToUsers(temp);
                  free(temp);
                  cJSON_Delete(data2);
                  int result = borrowBook(DATABASE_NAME,book,user);
                  char number[64]={};
                  sprintf(number,"%d",result);
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(number),number);
                  freeSingleBook(book);
                  freeSingleUser(user);
                  cJSON_Delete(data);
                  break;
                } 
                if(has_prefix(&(httpMessage->uri),&apiReturnBook))  /*归还书籍的API*/
                {
                  /*数据处理*/
                  cJSON *data = cJSON_Parse((httpMessage->body).p);
                  cJSON *data1 = cJSON_CreateArray();
                  char *s1 = cJSON_PrintUnformatted(cJSON_GetArrayItem(data,0));
                  cJSON *t1 = cJSON_Parse(s1);
                  free(s1);
                  cJSON_AddItemToArray(data1,t1);
                  char *temp = cJSON_PrintUnformatted(data1);
                  BOOKS *book = jsonToBooks(temp);
                  free(temp);
                  cJSON_Delete(data1);
                  cJSON *data2 = cJSON_CreateArray();
                  s1 = cJSON_PrintUnformatted(cJSON_GetArrayItem(data,1));
                  cJSON *t2 = cJSON_Parse(s1);
                  free(s1);
                  cJSON_AddItemToArray(data2,t2);
                  temp = cJSON_PrintUnformatted(data2);
                  USERS *user = jsonToUsers(temp);
                  free(temp);
                  cJSON_Delete(data2);
                  int result = returnBook(DATABASE_NAME,book,user);
                  char number[64]={};
                  sprintf(number,"%d",result);
                  /*发送响应*/
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(number),number);
                  freeSingleBook(book);
                  freeSingleUser(user);
                  cJSON_Delete(data);
                  break;
                }           
            }
            else if(is_equal(&(httpMessage->method),&getMethod))  /*GET请求*/
            {
              if(has_prefix(&(httpMessage->uri),&test)) /*API for test*/
                {
                    printf("test success!\n");
                    mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",25,"Welcome to use booksystem");
                    break;
                }
              if(has_prefix(&(httpMessage->uri),&apiGetAllBooksInfo)) /*API for test*/
                {
                  BOOKS *book = getAllBooksInfo(DATABASE_NAME);
                  char *results;
                  if(book == NULL)
                  {
                    results = calloc(sizeof(char),5);
                    strcpy(results,"NULL");
                  }
                  else
                  {
                    results = booksToJson(book);
                  }
                  mg_printf(nc,"HTTP/1.1 200 OK\r\n""Content-Type: text/plain\r\n""Content-Length: %d\r\n\r\n%s",(int)strlen(results),results);
                  free(results);
                  freeAllBooks(book);
                  break;
                }
            }
        }
        break;
        default:
        break;
    }
}
int main(void)
{
    /*初始化数据库*/
    if(!isDatabaseInit(DATABASE_NAME))  initDatabase(DATABASE_NAME);
    struct mg_mgr mgr;
    struct mg_connection *nc;
    /*设置连接参数*/
    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, LISTEN_PORT, ev_handler);
    mg_set_protocol_http_websocket(nc);
    printf("The server is running at port : %s\n",LISTEN_PORT);
    /*监听端口*/
    while (1) {
    mg_mgr_poll(&mgr, 1000);
  }
    mg_mgr_free(&mgr);
    return 0;
}

char *usersToJson(USERS *users) /*辅助函数，用于数据预处理*/
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

char *booksToJson(BOOKS *books) /*辅助函数，用于数据预处理*/
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

char *recordsToJson(BOOKSTATE *records) /*辅助函数，用于数据预处理*/
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

USERS *jsonToUsers(const char *data)  /*辅助函数，用于数据预处理*/
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

BOOKS *jsonToBooks(const char *data)  /*辅助函数，用于数据预处理*/
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

BOOKSTATE *jsonToRecords(const char *data)  /*辅助函数，用于数据预处理*/
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