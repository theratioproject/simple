
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   security.h
 * Author: thecarisma
 *
 * Created on February 18, 2018, 11:53 AM
 */

#ifndef SECURITY_H
#define SECURITY_H

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

/* Android Build currently Not Supported */
#ifdef __ANDROID__
#else
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

SIMPLE_API void init_simple_module(SimpleState *sState) ;

void security_lib_hash ( void *pointer ) ;

void security_lib_md5 ( void *pointer ) ;

void security_lib_SHA1 ( void *pointer ) ;

void security_lib_sha256 ( void *pointer ) ;

void security_lib_sha512 ( void *pointer ) ;

void security_lib_sha384 ( void *pointer ) ;

void security_lib_sha224 ( void *pointer ) ;

void security_lib_randbytes ( void *pointer ) ;

void security_lib_encrypt ( void *pointer ) ;

void security_lib_decrypt ( void *pointer ) ;

#ifdef __cplusplus
}
#endif

#endif /* SECURITY_H */

