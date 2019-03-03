

#include "../../../simple/include/simple.h"
#include "sqlite3.h"

#if defined(__linux__) && defined(__x86_64__)
#include <stddef.h>
#include <stdarg.h>
asm(".symver fcntl64, fcntl@GLIBC_2.2.5");

void *__wrap_fcntl64(int fd, int cmd, va_list argp){
    return fcntl64(fd, cmd, argp);
}
#endif

#ifdef _WIN32
    #define SIMPLE_API __declspec(dllexport)
#else
#if defined(_MSC_VER)
    //  Microsoft 
    #define SIMPLE_API __declspec(dllexport)
    #define SIMPLE_API __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define SIMPLE_API __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define SIMPLE_API
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

int sqlite_exec_callback ( void *data, int argc, char **argv, char **ColName )
{
    List *list, *list2  ;
    int x  ;
    list = (List *) data ;
    list = simple_list_newlist(list);
    for ( x = 0 ; x < argc ; x++ ) {
        list2 = simple_list_newlist(list);
        simple_list_addstring(list2,ColName[x]);
        simple_list_addstring(list2,argv[x] ? argv[x] : "NULL");
    }
    return 0 ;
}

SIMPLE_BLOCK(sqlite_sqlite3_exec)
{
    sqlite3 *_sqlite  ;
    int rc  ;
    List *list  ;
    char *errMsg  ;
    errMsg = NULL ;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
        _sqlite = (sqlite3 *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE") ;
        if ( _sqlite == NULL ) {
            return ;
        }
        if ( _sqlite ) {
            list = SIMPLE_API_NEWLIST ;
            rc = sqlite3_exec(_sqlite,SIMPLE_API_GETSTRING(2),sqlite_exec_callback,(void *) list,&errMsg);
            SIMPLE_API_RETLIST(list);
        }
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}


SIMPLE_BLOCK(init_sqlite3) 
{
	sqlite3* sqlite36226;	
	SIMPLE_API_RETCPOINTER(sqlite36226,"SMOOTHC_SQLITE");
}

SIMPLE_BLOCK(init_sqlite3_stmt) 
{
	sqlite3_stmt* sqlite3_stmt3868;	
	SIMPLE_API_RETCPOINTER(sqlite3_stmt3868,"SMOOTHC_SQLITE");
}

SIMPLE_BLOCK(init_sqlite3_context) 
{
	sqlite3_context* sqlite3_context3897;	
	SIMPLE_API_RETCPOINTER(sqlite3_context3897,"SMOOTHC_SQLITE");
}

SIMPLE_BLOCK(sqlite_sqlite3_close) 
{
	sqlite3* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_close(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_close_v2) 
{
	sqlite3* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_close_v2(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_open) 
{
	const char * str1;
	sqlite3 ** point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	point2 = (sqlite3 **) SIMPLE_API_GETCPOINTER2POINTER(2,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_open(str1,point2));
}

SIMPLE_BLOCK(sqlite_sqlite3_open16) 
{
	const void * point1;
	sqlite3 ** point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (const void *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	point2 = (sqlite3 **) SIMPLE_API_GETCPOINTER2POINTER(2,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_open16(point1,point2));
}

SIMPLE_BLOCK(sqlite_sqlite3_open_v2) 
{
	const char * str1;
	sqlite3 ** point2;
	int num3;
	const char * str4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	point2 = (sqlite3 **) SIMPLE_API_GETCPOINTER2POINTER(2,"SMOOTHC_SQLITE");
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	str4 = (const char *)  SIMPLE_API_GETSTRING(4);
	SIMPLE_API_RETNUMBER(sqlite3_open_v2(str1,point2,num3,str4));
}

SIMPLE_BLOCK(sqlite_sqlite3_errcode) 
{
	sqlite3 * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3 *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_errcode(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_extended_errcode) 
{
	sqlite3 * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3 *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_extended_errcode(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_errmsg) 
{
	sqlite3* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETSTRING(sqlite3_errmsg(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_errmsg16) 
{
	sqlite3* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	sqlite3_errmsg16(point1);
}

SIMPLE_BLOCK(sqlite_sqlite3_errstr) 
{
	int num1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	SIMPLE_API_RETSTRING(sqlite3_errstr(num1));
}

SIMPLE_BLOCK(sqlite_sqlite3_initialize) 
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETNUMBER(sqlite3_initialize());
}

SIMPLE_BLOCK(sqlite_sqlite3_shutdown) 
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETNUMBER(sqlite3_shutdown());
}

SIMPLE_BLOCK(sqlite_sqlite3_os_init) 
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETNUMBER(sqlite3_os_init());
}

SIMPLE_BLOCK(sqlite_sqlite3_os_end) 
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETNUMBER(sqlite3_os_end());
}

SIMPLE_BLOCK(sqlite_sqlite3_extended_result_codes) 
{
	sqlite3* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETNUMBER(sqlite3_extended_result_codes(point1,num2));
}

SIMPLE_BLOCK(sqlite_sqlite3_last_insert_rowid) 
{
	sqlite3* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_last_insert_rowid(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_changes) 
{
	sqlite3* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_changes(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_total_changes) 
{
	sqlite3* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_total_changes(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_interrupt) 
{
	sqlite3* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	sqlite3_interrupt(point1);
}

SIMPLE_BLOCK(sqlite_sqlite3_complete) 
{
	const char * str1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETNUMBER(sqlite3_complete(str1));
}

SIMPLE_BLOCK(sqlite_sqlite3_complete16) 
{
	const void * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (const void *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_complete16(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_busy_timeout) 
{
	sqlite3* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETNUMBER(sqlite3_busy_timeout(point1,num2));
}

SIMPLE_BLOCK(sqlite_sqlite3_malloc) 
{
	int num1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	sqlite3_malloc(num1);
}

SIMPLE_BLOCK(sqlite_sqlite3_free) 
{
	void* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (void*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	sqlite3_free(point1);
}

SIMPLE_BLOCK(sqlite_sqlite3_memory_used) 
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETNUMBER(sqlite3_memory_used());
}

SIMPLE_BLOCK(sqlite_sqlite3_memory_highwater) 
{
	int num1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	SIMPLE_API_RETNUMBER(sqlite3_memory_highwater(num1));
}

SIMPLE_BLOCK(sqlite_sqlite3_uri_parameter) 
{
	const char * str1;
	const char * str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	SIMPLE_API_RETSTRING(sqlite3_uri_parameter(str1,str2));
}

SIMPLE_BLOCK(sqlite_sqlite3_uri_boolean) 
{
	const char * str1;
	const char * str2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	str1 = (const char *)  SIMPLE_API_GETSTRING(1);
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	SIMPLE_API_RETNUMBER(sqlite3_uri_boolean(str1,str2,num3));
}

SIMPLE_BLOCK(sqlite_sqlite3_uri_int64) 
{
	const char* str1;
	const char* str2;
	sqlite3_int64 num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	str1 = (const char*)  SIMPLE_API_GETSTRING(1);
	str2 = (const char*)  SIMPLE_API_GETSTRING(2);
	num3 = (sqlite3_int64) SIMPLE_API_GETNUMBER(3);
	SIMPLE_API_RETNUMBER(sqlite3_uri_int64(str1,str2,num3));
}

SIMPLE_BLOCK(sqlite_sqlite3_limit) 
{
	sqlite3* point1;
	int num2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (sqlite3*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	SIMPLE_API_RETNUMBER(sqlite3_limit(point1,num2,num3));
}

SIMPLE_BLOCK(sqlite_sqlite3_prepare) 
{
	sqlite3 * point1;
	const char * str2;
	int num3;
	sqlite3_stmt ** point4;
	const char ** point5;
	if ( SIMPLE_API_PARACOUNT != 5 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
		return ;
	}
	point1 = (sqlite3 *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	point4 = (sqlite3_stmt **) SIMPLE_API_GETCPOINTER2POINTER(4,"SMOOTHC_SQLITE");
	point5 = (const char **) SIMPLE_API_GETCPOINTER2POINTER(5,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_prepare(point1,str2,num3,point4,point5));
}

SIMPLE_BLOCK(sqlite_sqlite3_prepare_v2) 
{
	sqlite3 * point1;
	const char * str2;
	int num3;
	sqlite3_stmt ** point4;
	const char ** point5;
	if ( SIMPLE_API_PARACOUNT != 5 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
		return ;
	}
	point1 = (sqlite3 *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	str2 = (const char *)  SIMPLE_API_GETSTRING(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	point4 = (sqlite3_stmt **) SIMPLE_API_GETCPOINTER2POINTER(4,"SMOOTHC_SQLITE");
	point5 = (const char **) SIMPLE_API_GETCPOINTER2POINTER(5,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_prepare_v2(point1,str2,num3,point4,point5));
}

SIMPLE_BLOCK(sqlite_sqlite3_prepare16) 
{
	sqlite3 * point1;
	const void * point2;
	int num3;
	sqlite3_stmt ** point4;
	const void ** point5;
	if ( SIMPLE_API_PARACOUNT != 5 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
		return ;
	}
	point1 = (sqlite3 *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	point2 = (const void *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_SQLITE");
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	point4 = (sqlite3_stmt **) SIMPLE_API_GETCPOINTER2POINTER(4,"SMOOTHC_SQLITE");
	point5 = (const void **) SIMPLE_API_GETCPOINTER2POINTER(5,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_prepare16(point1,point2,num3,point4,point5));
}

SIMPLE_BLOCK(sqlite_sqlite3_prepare16_v2) 
{
	sqlite3 * point1;
	const void * point2;
	int num3;
	sqlite3_stmt ** point4;
	const void ** point5;
	if ( SIMPLE_API_PARACOUNT != 5 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
		return ;
	}
	point1 = (sqlite3 *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	point2 = (const void *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_SQLITE");
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	point4 = (sqlite3_stmt **) SIMPLE_API_GETCPOINTER2POINTER(4,"SMOOTHC_SQLITE");
	point5 = (const void **) SIMPLE_API_GETCPOINTER2POINTER(5,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_prepare16_v2(point1,point2,num3,point4,point5));
}

SIMPLE_BLOCK(sqlite_sqlite3_sql) 
{
	sqlite3_stmt * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3_stmt *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETSTRING(sqlite3_sql(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_stmt_readonly) 
{
	sqlite3_stmt * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3_stmt *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_stmt_readonly(point1));
}

SIMPLE_BLOCK(sqlite_sqlite3_stmt_busy) 
{
	sqlite3_stmt* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (sqlite3_stmt*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_SQLITE");
	SIMPLE_API_RETNUMBER(sqlite3_stmt_busy(point1));
}

SIMPLE_BLOCK(sqlite_SQLITE_OK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_OK);
}

SIMPLE_BLOCK(sqlite_SQLITE_ERROR) 
{
	SIMPLE_API_RETNUMBER(SQLITE_ERROR);
}

SIMPLE_BLOCK(sqlite_SQLITE_INTERNAL) 
{
	SIMPLE_API_RETNUMBER(SQLITE_INTERNAL);
}

SIMPLE_BLOCK(sqlite_SQLITE_PERM) 
{
	SIMPLE_API_RETNUMBER(SQLITE_PERM);
}

SIMPLE_BLOCK(sqlite_SQLITE_ABORT) 
{
	SIMPLE_API_RETNUMBER(SQLITE_ABORT);
}

SIMPLE_BLOCK(sqlite_SQLITE_BUSY) 
{
	SIMPLE_API_RETNUMBER(SQLITE_BUSY);
}

SIMPLE_BLOCK(sqlite_SQLITE_LOCKED) 
{
	SIMPLE_API_RETNUMBER(SQLITE_LOCKED);
}

SIMPLE_BLOCK(sqlite_SQLITE_NOMEM) 
{
	SIMPLE_API_RETNUMBER(SQLITE_NOMEM);
}

SIMPLE_BLOCK(sqlite_SQLITE_READONLY) 
{
	SIMPLE_API_RETNUMBER(SQLITE_READONLY);
}

SIMPLE_BLOCK(sqlite_SQLITE_INTERRUPT) 
{
	SIMPLE_API_RETNUMBER(SQLITE_INTERRUPT);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR);
}

SIMPLE_BLOCK(sqlite_SQLITE_CORRUPT) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CORRUPT);
}

SIMPLE_BLOCK(sqlite_SQLITE_NOTFOUND) 
{
	SIMPLE_API_RETNUMBER(SQLITE_NOTFOUND);
}

SIMPLE_BLOCK(sqlite_SQLITE_FULL) 
{
	SIMPLE_API_RETNUMBER(SQLITE_FULL);
}

SIMPLE_BLOCK(sqlite_SQLITE_CANTOPEN) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CANTOPEN);
}

SIMPLE_BLOCK(sqlite_SQLITE_PROTOCOL) 
{
	SIMPLE_API_RETNUMBER(SQLITE_PROTOCOL);
}

SIMPLE_BLOCK(sqlite_SQLITE_EMPTY) 
{
	SIMPLE_API_RETNUMBER(SQLITE_EMPTY);
}

SIMPLE_BLOCK(sqlite_SQLITE_SCHEMA) 
{
	SIMPLE_API_RETNUMBER(SQLITE_SCHEMA);
}

SIMPLE_BLOCK(sqlite_SQLITE_TOOBIG) 
{
	SIMPLE_API_RETNUMBER(SQLITE_TOOBIG);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT);
}

SIMPLE_BLOCK(sqlite_SQLITE_MISMATCH) 
{
	SIMPLE_API_RETNUMBER(SQLITE_MISMATCH);
}

SIMPLE_BLOCK(sqlite_SQLITE_MISUSE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_MISUSE);
}

SIMPLE_BLOCK(sqlite_SQLITE_NOLFS) 
{
	SIMPLE_API_RETNUMBER(SQLITE_NOLFS);
}

SIMPLE_BLOCK(sqlite_SQLITE_AUTH) 
{
	SIMPLE_API_RETNUMBER(SQLITE_AUTH);
}

SIMPLE_BLOCK(sqlite_SQLITE_FORMAT) 
{
	SIMPLE_API_RETNUMBER(SQLITE_FORMAT);
}

SIMPLE_BLOCK(sqlite_SQLITE_RANGE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_RANGE);
}

SIMPLE_BLOCK(sqlite_SQLITE_NOTADB) 
{
	SIMPLE_API_RETNUMBER(SQLITE_NOTADB);
}

SIMPLE_BLOCK(sqlite_SQLITE_NOTICE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_NOTICE);
}

SIMPLE_BLOCK(sqlite_SQLITE_WARNING) 
{
	SIMPLE_API_RETNUMBER(SQLITE_WARNING);
}

SIMPLE_BLOCK(sqlite_SQLITE_ROW) 
{
	SIMPLE_API_RETNUMBER(SQLITE_ROW);
}

SIMPLE_BLOCK(sqlite_SQLITE_DONE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_DONE);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_READ) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_READ);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_SHORT_READ) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_SHORT_READ);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_WRITE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_WRITE);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_FSYNC) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_FSYNC);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_DIR_FSYNC) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_DIR_FSYNC);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_TRUNCATE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_TRUNCATE);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_FSTAT) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_FSTAT);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_UNLOCK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_UNLOCK);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_RDLOCK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_RDLOCK);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_DELETE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_DELETE);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_BLOCKED) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_BLOCKED);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_NOMEM) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_NOMEM);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_ACCESS) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_ACCESS);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_CHECKRESERVEDLOCK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_CHECKRESERVEDLOCK);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_LOCK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_LOCK);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_CLOSE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_CLOSE);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_DIR_CLOSE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_DIR_CLOSE);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_SHMOPEN) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_SHMOPEN);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_SHMSIZE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_SHMSIZE);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_SHMLOCK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_SHMLOCK);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_SHMMAP) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_SHMMAP);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_SEEK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_SEEK);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_DELETE_NOENT) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_DELETE_NOENT);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_MMAP) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_MMAP);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_GETTEMPPATH) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_GETTEMPPATH);
}

SIMPLE_BLOCK(sqlite_SQLITE_IOERR_CONVPATH) 
{
	SIMPLE_API_RETNUMBER(SQLITE_IOERR_CONVPATH);
}

SIMPLE_BLOCK(sqlite_SQLITE_LOCKED_SHAREDCACHE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_LOCKED_SHAREDCACHE);
}

SIMPLE_BLOCK(sqlite_SQLITE_BUSY_RECOVERY) 
{
	SIMPLE_API_RETNUMBER(SQLITE_BUSY_RECOVERY);
}

SIMPLE_BLOCK(sqlite_SQLITE_BUSY_SNAPSHOT) 
{
	SIMPLE_API_RETNUMBER(SQLITE_BUSY_SNAPSHOT);
}

SIMPLE_BLOCK(sqlite_SQLITE_CANTOPEN_NOTEMPDIR) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CANTOPEN_NOTEMPDIR);
}

SIMPLE_BLOCK(sqlite_SQLITE_CANTOPEN_ISDIR) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CANTOPEN_ISDIR);
}

SIMPLE_BLOCK(sqlite_SQLITE_CANTOPEN_FULLPATH) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CANTOPEN_FULLPATH);
}

SIMPLE_BLOCK(sqlite_SQLITE_CANTOPEN_CONVPATH) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CANTOPEN_CONVPATH);
}

SIMPLE_BLOCK(sqlite_SQLITE_CORRUPT_VTAB) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CORRUPT_VTAB);
}

SIMPLE_BLOCK(sqlite_SQLITE_READONLY_RECOVERY) 
{
	SIMPLE_API_RETNUMBER(SQLITE_READONLY_RECOVERY);
}

SIMPLE_BLOCK(sqlite_SQLITE_READONLY_CANTLOCK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_READONLY_CANTLOCK);
}

SIMPLE_BLOCK(sqlite_SQLITE_READONLY_ROLLBACK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_READONLY_ROLLBACK);
}

SIMPLE_BLOCK(sqlite_SQLITE_READONLY_DBMOVED) 
{
	SIMPLE_API_RETNUMBER(SQLITE_READONLY_DBMOVED);
}

SIMPLE_BLOCK(sqlite_SQLITE_ABORT_ROLLBACK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_ABORT_ROLLBACK);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_CHECK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_CHECK);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_COMMITHOOK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_COMMITHOOK);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_FOREIGNKEY) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_FOREIGNKEY);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_FUNCTION) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_FUNCTION);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_NOTNULL) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_NOTNULL);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_PRIMARYKEY) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_PRIMARYKEY);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_TRIGGER) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_TRIGGER);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_UNIQUE) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_UNIQUE);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_VTAB) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_VTAB);
}

SIMPLE_BLOCK(sqlite_SQLITE_CONSTRAINT_ROWID) 
{
	SIMPLE_API_RETNUMBER(SQLITE_CONSTRAINT_ROWID);
}

SIMPLE_BLOCK(sqlite_SQLITE_NOTICE_RECOVER_WAL) 
{
	SIMPLE_API_RETNUMBER(SQLITE_NOTICE_RECOVER_WAL);
}

SIMPLE_BLOCK(sqlite_SQLITE_NOTICE_RECOVER_ROLLBACK) 
{
	SIMPLE_API_RETNUMBER(SQLITE_NOTICE_RECOVER_ROLLBACK);
}

SIMPLE_BLOCK(sqlite_SQLITE_WARNING_AUTOINDEX) 
{
	SIMPLE_API_RETNUMBER(SQLITE_WARNING_AUTOINDEX);
}

SIMPLE_BLOCK(sqlite_SQLITE_AUTH_USER) 
{
	SIMPLE_API_RETNUMBER(SQLITE_AUTH_USER);
}

SIMPLE_API void init_simple_module(SimpleState *sState)
{
	register_block("__init_sqlite3",init_sqlite3);
	register_block("__init_sqlite3_stmt",init_sqlite3_stmt);
	register_block("__init_sqlite3_context",init_sqlite3_context);
	register_block("__sqlite3_close",sqlite_sqlite3_close);
	register_block("__sqlite3_close_v2",sqlite_sqlite3_close_v2);
	register_block("__sqlite3_open",sqlite_sqlite3_open);
	register_block("__sqlite3_open16",sqlite_sqlite3_open16);
	register_block("__sqlite3_open_v2",sqlite_sqlite3_open_v2);
	register_block("__sqlite3_errcode",sqlite_sqlite3_errcode);
	register_block("__sqlite3_extended_errcode",sqlite_sqlite3_extended_errcode);
	register_block("__sqlite3_errmsg",sqlite_sqlite3_errmsg);
	register_block("__sqlite3_errmsg16",sqlite_sqlite3_errmsg16);
	register_block("__sqlite3_errstr",sqlite_sqlite3_errstr);
	register_block("__sqlite3_initialize",sqlite_sqlite3_initialize);
	register_block("__sqlite3_shutdown",sqlite_sqlite3_shutdown);
	register_block("__sqlite3_os_init",sqlite_sqlite3_os_init);
	register_block("__sqlite3_os_end",sqlite_sqlite3_os_end);
	register_block("__sqlite3_extended_result_codes",sqlite_sqlite3_extended_result_codes);
	register_block("__sqlite3_last_insert_rowid",sqlite_sqlite3_last_insert_rowid);
	register_block("__sqlite3_changes",sqlite_sqlite3_changes);
	register_block("__sqlite3_total_changes",sqlite_sqlite3_total_changes);
	register_block("__sqlite3_interrupt",sqlite_sqlite3_interrupt);
	register_block("__sqlite3_complete",sqlite_sqlite3_complete);
	register_block("__sqlite3_complete16",sqlite_sqlite3_complete16);
	register_block("__sqlite3_busy_timeout",sqlite_sqlite3_busy_timeout);
	register_block("__sqlite3_malloc",sqlite_sqlite3_malloc);
	register_block("__sqlite3_free",sqlite_sqlite3_free);
	register_block("__sqlite3_memory_used",sqlite_sqlite3_memory_used);
	register_block("__sqlite3_memory_highwater",sqlite_sqlite3_memory_highwater);
	register_block("__sqlite3_uri_parameter",sqlite_sqlite3_uri_parameter);
	register_block("__sqlite3_uri_boolean",sqlite_sqlite3_uri_boolean);
	register_block("__sqlite3_uri_int64",sqlite_sqlite3_uri_int64);
	register_block("__sqlite3_limit",sqlite_sqlite3_limit);
	register_block("__sqlite3_prepare",sqlite_sqlite3_prepare);
	register_block("__sqlite3_prepare_v2",sqlite_sqlite3_prepare_v2);
	register_block("__sqlite3_prepare16",sqlite_sqlite3_prepare16);
	register_block("__sqlite3_prepare16_v2",sqlite_sqlite3_prepare16_v2);
	register_block("__sqlite3_sql",sqlite_sqlite3_sql);
	register_block("__sqlite3_stmt_readonly",sqlite_sqlite3_stmt_readonly);
	register_block("__sqlite3_stmt_busy",sqlite_sqlite3_stmt_busy);
	register_block("__SQLITE_OK",sqlite_SQLITE_OK);
	register_block("__SQLITE_ERROR",sqlite_SQLITE_ERROR);
	register_block("__SQLITE_INTERNAL",sqlite_SQLITE_INTERNAL);
	register_block("__SQLITE_PERM",sqlite_SQLITE_PERM);
	register_block("__SQLITE_ABORT",sqlite_SQLITE_ABORT);
	register_block("__SQLITE_BUSY",sqlite_SQLITE_BUSY);
	register_block("__SQLITE_LOCKED",sqlite_SQLITE_LOCKED);
	register_block("__SQLITE_NOMEM",sqlite_SQLITE_NOMEM);
	register_block("__SQLITE_READONLY",sqlite_SQLITE_READONLY);
	register_block("__SQLITE_INTERRUPT",sqlite_SQLITE_INTERRUPT);
	register_block("__SQLITE_IOERR",sqlite_SQLITE_IOERR);
	register_block("__SQLITE_CORRUPT",sqlite_SQLITE_CORRUPT);
	register_block("__SQLITE_NOTFOUND",sqlite_SQLITE_NOTFOUND);
	register_block("__SQLITE_FULL",sqlite_SQLITE_FULL);
	register_block("__SQLITE_CANTOPEN",sqlite_SQLITE_CANTOPEN);
	register_block("__SQLITE_PROTOCOL",sqlite_SQLITE_PROTOCOL);
	register_block("__SQLITE_EMPTY",sqlite_SQLITE_EMPTY);
	register_block("__SQLITE_SCHEMA",sqlite_SQLITE_SCHEMA);
	register_block("__SQLITE_TOOBIG",sqlite_SQLITE_TOOBIG);
	register_block("__SQLITE_CONSTRAINT",sqlite_SQLITE_CONSTRAINT);
	register_block("__SQLITE_MISMATCH",sqlite_SQLITE_MISMATCH);
	register_block("__SQLITE_MISUSE",sqlite_SQLITE_MISUSE);
	register_block("__SQLITE_NOLFS",sqlite_SQLITE_NOLFS);
	register_block("__SQLITE_AUTH",sqlite_SQLITE_AUTH);
	register_block("__SQLITE_FORMAT",sqlite_SQLITE_FORMAT);
	register_block("__SQLITE_RANGE",sqlite_SQLITE_RANGE);
	register_block("__SQLITE_NOTADB",sqlite_SQLITE_NOTADB);
	register_block("__SQLITE_NOTICE",sqlite_SQLITE_NOTICE);
	register_block("__SQLITE_WARNING",sqlite_SQLITE_WARNING);
	register_block("__SQLITE_ROW",sqlite_SQLITE_ROW);
	register_block("__SQLITE_DONE",sqlite_SQLITE_DONE);
	register_block("__SQLITE_IOERR_READ",sqlite_SQLITE_IOERR_READ);
	register_block("__SQLITE_IOERR_SHORT_READ",sqlite_SQLITE_IOERR_SHORT_READ);
	register_block("__SQLITE_IOERR_WRITE",sqlite_SQLITE_IOERR_WRITE);
	register_block("__SQLITE_IOERR_FSYNC",sqlite_SQLITE_IOERR_FSYNC);
	register_block("__SQLITE_IOERR_DIR_FSYNC",sqlite_SQLITE_IOERR_DIR_FSYNC);
	register_block("__SQLITE_IOERR_TRUNCATE",sqlite_SQLITE_IOERR_TRUNCATE);
	register_block("__SQLITE_IOERR_FSTAT",sqlite_SQLITE_IOERR_FSTAT);
	register_block("__SQLITE_IOERR_UNLOCK",sqlite_SQLITE_IOERR_UNLOCK);
	register_block("__SQLITE_IOERR_RDLOCK",sqlite_SQLITE_IOERR_RDLOCK);
	register_block("__SQLITE_IOERR_DELETE",sqlite_SQLITE_IOERR_DELETE);
	register_block("__SQLITE_IOERR_BLOCKED",sqlite_SQLITE_IOERR_BLOCKED);
	register_block("__SQLITE_IOERR_NOMEM",sqlite_SQLITE_IOERR_NOMEM);
	register_block("__SQLITE_IOERR_ACCESS",sqlite_SQLITE_IOERR_ACCESS);
	register_block("__SQLITE_IOERR_CHECKRESERVEDLOCK",sqlite_SQLITE_IOERR_CHECKRESERVEDLOCK);
	register_block("__SQLITE_IOERR_LOCK",sqlite_SQLITE_IOERR_LOCK);
	register_block("__SQLITE_IOERR_CLOSE",sqlite_SQLITE_IOERR_CLOSE);
	register_block("__SQLITE_IOERR_DIR_CLOSE",sqlite_SQLITE_IOERR_DIR_CLOSE);
	register_block("__SQLITE_IOERR_SHMOPEN",sqlite_SQLITE_IOERR_SHMOPEN);
	register_block("__SQLITE_IOERR_SHMSIZE",sqlite_SQLITE_IOERR_SHMSIZE);
	register_block("__SQLITE_IOERR_SHMLOCK",sqlite_SQLITE_IOERR_SHMLOCK);
	register_block("__SQLITE_IOERR_SHMMAP",sqlite_SQLITE_IOERR_SHMMAP);
	register_block("__SQLITE_IOERR_SEEK",sqlite_SQLITE_IOERR_SEEK);
	register_block("__SQLITE_IOERR_DELETE_NOENT",sqlite_SQLITE_IOERR_DELETE_NOENT);
	register_block("__SQLITE_IOERR_MMAP",sqlite_SQLITE_IOERR_MMAP);
	register_block("__SQLITE_IOERR_GETTEMPPATH",sqlite_SQLITE_IOERR_GETTEMPPATH);
	register_block("__SQLITE_IOERR_CONVPATH",sqlite_SQLITE_IOERR_CONVPATH);
	register_block("__SQLITE_LOCKED_SHAREDCACHE",sqlite_SQLITE_LOCKED_SHAREDCACHE);
	register_block("__SQLITE_BUSY_RECOVERY",sqlite_SQLITE_BUSY_RECOVERY);
	register_block("__SQLITE_BUSY_SNAPSHOT",sqlite_SQLITE_BUSY_SNAPSHOT);
	register_block("__SQLITE_CANTOPEN_NOTEMPDIR",sqlite_SQLITE_CANTOPEN_NOTEMPDIR);
	register_block("__SQLITE_CANTOPEN_ISDIR",sqlite_SQLITE_CANTOPEN_ISDIR);
	register_block("__SQLITE_CANTOPEN_FULLPATH",sqlite_SQLITE_CANTOPEN_FULLPATH);
	register_block("__SQLITE_CANTOPEN_CONVPATH",sqlite_SQLITE_CANTOPEN_CONVPATH);
	register_block("__SQLITE_CORRUPT_VTAB",sqlite_SQLITE_CORRUPT_VTAB);
	register_block("__SQLITE_READONLY_RECOVERY",sqlite_SQLITE_READONLY_RECOVERY);
	register_block("__SQLITE_READONLY_CANTLOCK",sqlite_SQLITE_READONLY_CANTLOCK);
	register_block("__SQLITE_READONLY_ROLLBACK",sqlite_SQLITE_READONLY_ROLLBACK);
	register_block("__SQLITE_READONLY_DBMOVED",sqlite_SQLITE_READONLY_DBMOVED);
	register_block("__SQLITE_ABORT_ROLLBACK",sqlite_SQLITE_ABORT_ROLLBACK);
	register_block("__SQLITE_CONSTRAINT_CHECK",sqlite_SQLITE_CONSTRAINT_CHECK);
	register_block("__SQLITE_CONSTRAINT_COMMITHOOK",sqlite_SQLITE_CONSTRAINT_COMMITHOOK);
	register_block("__SQLITE_CONSTRAINT_FOREIGNKEY",sqlite_SQLITE_CONSTRAINT_FOREIGNKEY);
	register_block("__SQLITE_CONSTRAINT_FUNCTION",sqlite_SQLITE_CONSTRAINT_FUNCTION);
	register_block("__SQLITE_CONSTRAINT_NOTNULL",sqlite_SQLITE_CONSTRAINT_NOTNULL);
	register_block("__SQLITE_CONSTRAINT_PRIMARYKEY",sqlite_SQLITE_CONSTRAINT_PRIMARYKEY);
	register_block("__SQLITE_CONSTRAINT_TRIGGER",sqlite_SQLITE_CONSTRAINT_TRIGGER);
	register_block("__SQLITE_CONSTRAINT_UNIQUE",sqlite_SQLITE_CONSTRAINT_UNIQUE);
	register_block("__SQLITE_CONSTRAINT_VTAB",sqlite_SQLITE_CONSTRAINT_VTAB);
	register_block("__SQLITE_CONSTRAINT_ROWID",sqlite_SQLITE_CONSTRAINT_ROWID);
	register_block("__SQLITE_NOTICE_RECOVER_WAL",sqlite_SQLITE_NOTICE_RECOVER_WAL);
	register_block("__SQLITE_NOTICE_RECOVER_ROLLBACK",sqlite_SQLITE_NOTICE_RECOVER_ROLLBACK);
	register_block("__SQLITE_WARNING_AUTOINDEX",sqlite_SQLITE_WARNING_AUTOINDEX);
	register_block("__SQLITE_AUTH_USER",sqlite_SQLITE_AUTH_USER);
	register_block("__sqlite3_exec",sqlite_sqlite3_exec);
}

