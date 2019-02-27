
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   networker.h
 * Author: thecarisma
 *
 * Created on February 12, 2018, 2:17 AM
 */

#ifndef NETWORKER_H
#define NETWORKER_H

//we don't want openssl to stop build
#if !defined(__imp___acrt_iob_func) && defined(_WIN32)
FILE * __cdecl __imp___acrt_iob_func(int index)
{
	#ifdef __iob_func
		return &__iob_func()[index] ;
	#else
		switch (index) {
			case 0:
				return stdin;
				break;
			case 1:
				return stdout;
				break;
			case 2:
				return stderr;
				break;
			default:
				return stdout;
				break;
		}
	#endif
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
typedef struct curl_slist CURL_LIST ;
SIMPLE_API void init_simple_module(SimpleState *sState) ;

void curl_init ( void *pointer ) ;
void curl_perform ( void *pointer ) ;
void curl_string_perform ( void *pointer ) ;
void curl_cleanup ( void *pointer ) ;
void curl_setopt ( void *pointer ) ;
void new_curl_list ( void *pointer ) ;
void free_curl_list ( void *pointer ) ;
void curl_list_append ( void *pointer ) ;
void curl_list_free_all ( void *pointer ) ;
void curl_download ( void *pointer ) ;


#ifdef __cplusplus
}
#endif

#endif /* NETWORKER_H */

