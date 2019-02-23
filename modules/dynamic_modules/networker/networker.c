
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   networker.c
 * Author: thecarisma
 *
 * Created on February 12, 2018, 2:18 AM
 */

#include "../../../simple/include/simple.h"
#include <curl/curl.h>
#include "networker.h"

#ifdef _WIN32
	#define SIMPLE_API __declspec(dllexport)
#else
#if defined(_MSC_VER)
    //  Microsoft 
    #define SIMPLE_API __declspec(dllexport)
#elif defined(__GNUC__)
    //  GCC
    #define SIMPLE_API __attribute__((visibility("default")))
#else
    //  do nothing and hope for the best?
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

SIMPLE_API void init_simple_module(SimpleState *sState)
{   
    /* CURL */
    register_block("__curl_easy_init",curl_init);
    register_block("__curl_easy_perform",curl_perform);
    register_block("__curl_easy_string_perform",curl_string_perform);
    register_block("__curl_easy_cleanup",curl_cleanup);
    register_block("__curl_easy_setopt",curl_setopt);
    register_block("__new_curl_list",new_curl_list);
    register_block("__free_curl_list",free_curl_list);
    register_block("__curl_list_append",curl_list_append);
    register_block("__curl_list_free_all",curl_list_free_all);
    
    /* DOWNLOAD/MAIL */
    register_block("__curl_download",curl_download);
}

void curl_init ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    SIMPLE_API_RETCPOINTER(curl_easy_init(),"SIMPLE_CURL");
}

void curl_perform ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        CURLcode *curl_code ; 
        curl_code = (CURLcode *) simple_state_malloc(((VM *) pointer)->sState,sizeof(CURLcode)) ;
        *curl_code = curl_easy_perform((CURL *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL"));
        SIMPLE_API_RETCPOINTER(curl_code,"SIMPLE_CURL_CODE");    
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
}

size_t simple_get_curl_data ( void *buffer, size_t size, size_t mem_size, void *string )
{
	simple_string_add2(string,buffer,size*mem_size);
	return size*mem_size ;
}

void curl_string_perform ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        String *string = simple_string_new("");
        CURL *curl = (CURL *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL") ;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,simple_get_curl_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,string);
        curl_easy_perform(curl);
        SIMPLE_API_RETSTRING2(simple_string_get(string),simple_string_size(string));
        simple_string_delete(string);
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
}

void curl_cleanup ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        curl_easy_cleanup((CURL *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL_CODE"));
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
}

void curl_setopt ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && !SIMPLE_API_ISNUMBER(4)) {
        CURLcode *curl_code ; 
        curl_code = (CURLcode *) simple_state_malloc(((VM *) pointer)->sState,sizeof(CURLcode)) ;
        *curl_code = curl_easy_setopt((CURL *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL"), (CURLoption ) SIMPLE_API_GETNUMBER(2), (int) SIMPLE_API_GETNUMBER(3));
        SIMPLE_API_RETCPOINTER(curl_code,"SIMPLE_CURL_CODE");
    } else if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISSTRING(3) && SIMPLE_API_ISSTRING(4)) {
        CURLcode *curl_code ; 
        curl_code = (CURLcode *) simple_state_malloc(((VM *) pointer)->sState,sizeof(CURLcode)) ;
        *curl_code = curl_easy_setopt((CURL *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL"), (CURLoption ) SIMPLE_API_GETNUMBER(2), SIMPLE_API_GETSTRING(3));
        SIMPLE_API_RETCPOINTER(curl_code,"SIMPLE_CURL_CODE");
    } else if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISPOINTER(3) && SIMPLE_API_ISNUMBER(4) && SIMPLE_API_GETNUMBER(4) == 1 ) {
        CURLcode *curl_code ; 
        curl_code = (CURLcode *) simple_state_malloc(((VM *) pointer)->sState,sizeof(CURLcode)) ;
        *curl_code = curl_easy_setopt((CURL *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL"), (CURLoption ) SIMPLE_API_GETNUMBER(2), (CURL_LIST *) SIMPLE_API_GETCPOINTER(3,"SIMPLE_CURL_LIST"));
        SIMPLE_API_RETCPOINTER(curl_code,"SIMPLE_CURL_CODE");
    } else if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISPOINTER(3) ) {
        CURLcode *curl_code ; 
        curl_code = (CURLcode *) simple_state_malloc(((VM *) pointer)->sState,sizeof(CURLcode)) ;
        *curl_code = curl_easy_setopt((CURL *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL"), (CURLoption ) SIMPLE_API_GETNUMBER(2), (void *) SIMPLE_API_GETCPOINTER(3,"void")); 
        SIMPLE_API_RETCPOINTER(curl_code,"SIMPLE_CURL_CODE");
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
}

void new_curl_list ( void *pointer )
{
    
    if ( SIMPLE_API_PARACOUNT == 0 ) {
        CURL_LIST *curl_list = (CURL_LIST *) simple_state_malloc(((VM *) pointer)->sState,sizeof(CURL_LIST)); 
        if (curl_list == NULL ) {
            SIMPLE_API_ERROR(SIMPLE_OOM);
            return ;
        } else {
            SIMPLE_API_RETCPOINTER(curl_list,"SIMPLE_CURL_LIST");
        }
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
}

void free_curl_list ( void *pointer )
{
    
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        CURL_LIST *curl_list = (CURL_LIST *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL_LIST"); ; 
        if (curl_list != NULL ) {
            simple_state_free(((VM *) pointer)->sState,curl_list) ;
            SIMPLE_API_SETNULLPOINTER(1);
            return ;
        }
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
}

void curl_list_append ( void *pointer )
{
    
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
        SIMPLE_API_RETCPOINTER(curl_slist_append((CURL_LIST *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL_LIST"),SIMPLE_API_GETSTRING(2)),"SIMPLE_CURL_LIST");
        return ;
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
}

void curl_list_free_all ( void *pointer )
{
    
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
        curl_slist_free_all((CURL_LIST *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_CURL_LIST"));
        return ;
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
}

void curl_download ( void *pointer )
{
	CURL *curl  ;
	CURLcode res  ;
	String *string  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	curl = curl_easy_init();
	if ( curl ) {
		string = simple_string_new_gc(((VM *) pointer)->sState,"");
		curl_easy_setopt(curl, CURLOPT_URL,SIMPLE_API_GETSTRING(1));
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,1);
		curl_easy_setopt(curl, CURLOPT_NOSIGNAL,1);
		curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING,"");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,simple_get_curl_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA,string);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		SIMPLE_API_RETSTRING2(simple_string_get(string),simple_string_size(string));
		simple_string_delete_gc(((VM *) pointer)->sState,string);
	}
}
