#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mongoose.h"
#include "identify.h"
#include "cJSON.h"

#define DATABASE_NAME "booksystem"

#define LISTEN_PORT "8888"



static const struct mg_str getMethod = MG_MK_STR("GET");
static const struct mg_str postMethod = MG_MK_STR("POST");

static const struct mg_str apiUserLogIn = MG_MK_STR("/users/login");
static const struct mg_str apiGetUserInfo = MG_MK_STR("/users/getsingle");
static const struct mg_str apiGetAllUserInfo = MG_MK_STR("/users/getall");
static const struct mg_str apiUserModify = MG_MK_STR("/users/modify");
static const struct mg_str apiCreateNewUser = MG_MK_STR("/users/create");

static const struct mg_str apiGetBooksByCategory = MG_MK_STR("/books/getbycat");
static const struct mg_str apiGetAllBooksInfo = MG_MK_STR("/books/getall");
static const struct mg_str apiGetBookInfo = MG_MK_STR("/books/getsingle");
static const struct mg_str apiCreateNewBook = MG_MK_STR("/books/create");
static const struct mg_str apiBookModify = MG_MK_STR("/books/modify");

static const struct mg_str apiGetAllBookRecords = MG_MK_STR("/records/getall");
static const struct mg_str apiGetBookRecordsByUser = MG_MK_STR("/records/getbyuser");
static const struct mg_str apiBorrowBook = MG_MK_STR("/records/borrow");
static const struct mg_str apiReturnBook = MG_MK_STR("/records/return");

char *usersToJson(USERS *users);
char *booksToJson(BOOKS *books);
char *recordsToJson(BOOKSTATE *records);
USERS *jsonToUsers(const char *data);
BOOKS *jsonToBooks(const char *data);
BOOKSTATE *jsonToRecords(const char *data);
