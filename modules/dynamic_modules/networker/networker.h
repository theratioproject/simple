
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
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

