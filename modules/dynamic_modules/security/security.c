
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   security.c
 * Author: thecarisma
 *
 * Created on February 18, 2018, 11:48 AM
 */

#include "../../../simple/includes/simple.h"
#include "./openssl/md5.h"
#include "openssl/sha.h"
#include "openssl/evp.h"
#include "openssl/rand.h"
#include "security.h"

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
    register_block("__hash",security_lib_hash);
    register_block("__md5",security_lib_md5);
    register_block("__sha1",security_lib_sha1);
    register_block("__sha256",security_lib_sha256);
    register_block("__sha512",security_lib_sha512);
    register_block("__sha384",security_lib_sha384);
    register_block("__sha224",security_lib_sha224);
    register_block("__encrypt",security_lib_encrypt);
    register_block("__decrypt",security_lib_decrypt);
    register_block("__randbytes",security_lib_randbytes);
}

void security_lib_hash ( void *pointer )
{
	unsigned char digest[16]  ;
	char string[33]  ;
	int x,size  ;
	char *cInput  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cInput = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		for ( x = 0 ; x < 16 ; x++ ) {
			sprintf( &string[x*2] , "%02x" , (unsigned int) digest[x] ) ;
		}
		SIMPLE_API_RETSTRING(string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void security_lib_md5 ( void *pointer )
{
	unsigned char digest[16]  ;
	char string[33]  ;
	int x,size  ;
	char *cInput  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cInput = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		MD5((unsigned char *) cInput, size, (unsigned char *) &digest);
		for ( x = 0 ; x < 16 ; x++ ) {
			sprintf( &string[x*2] , "%02x" , (unsigned int) digest[x] ) ;
		}
		SIMPLE_API_RETSTRING(string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void security_lib_sha1 ( void *pointer )
{
	unsigned char digest[SHA_DIGEST_LENGTH]  ;
	char string[SHA_DIGEST_LENGTH*2+1]  ;
	int x,size  ;
	char *cInput  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cInput = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		SHA1((unsigned char *) cInput, size, (unsigned char *) &digest);
		for ( x = 0 ; x < SHA_DIGEST_LENGTH ; x++ ) {
			sprintf( &string[x*2] , "%02x" , (unsigned int) digest[x] ) ;
		}
		SIMPLE_API_RETSTRING(string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void security_lib_sha256 ( void *pointer )
{
	unsigned char digest[SHA256_DIGEST_LENGTH]  ;
	char string[SHA256_DIGEST_LENGTH*2+1]  ;
	int x,size  ;
	char *cInput  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cInput = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		SHA256((unsigned char *) cInput, size, (unsigned char *) &digest);
		for ( x = 0 ; x < SHA256_DIGEST_LENGTH ; x++ ) {
			sprintf( &string[x*2] , "%02x" , (unsigned int) digest[x] ) ;
		}
		SIMPLE_API_RETSTRING(string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void security_lib_sha512 ( void *pointer )
{
	unsigned char digest[SHA512_DIGEST_LENGTH]  ;
	char string[SHA512_DIGEST_LENGTH*2+1]  ;
	int x,size  ;
	char *cInput  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cInput = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		SHA512((unsigned char *) cInput, size, (unsigned char *) &digest);
		for ( x = 0 ; x < SHA512_DIGEST_LENGTH ; x++ ) {
			sprintf( &string[x*2] , "%02x" , (unsigned int) digest[x] ) ;
		}
		SIMPLE_API_RETSTRING(string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void security_lib_sha384 ( void *pointer )
{
	unsigned char digest[SHA384_DIGEST_LENGTH]  ;
	char string[SHA384_DIGEST_LENGTH*2+1]  ;
	int x,size  ;
	char *cInput  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cInput = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		SHA384((unsigned char *) cInput, size, (unsigned char *) &digest);
		for ( x = 0 ; x < SHA384_DIGEST_LENGTH ; x++ ) {
			sprintf( &string[x*2] , "%02x" , (unsigned int) digest[x] ) ;
		}
		SIMPLE_API_RETSTRING(string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void security_lib_sha224 ( void *pointer )
{
	unsigned char digest[SHA224_DIGEST_LENGTH]  ;
	char string[SHA224_DIGEST_LENGTH*2+1]  ;
	int x,size  ;
	char *cInput  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cInput = SIMPLE_API_GETSTRING(1) ;
		size = SIMPLE_API_GETSTRINGSIZE(1) ;
		SHA224((unsigned char *) cInput, size, (unsigned char *) &digest);
		for ( x = 0 ; x < SHA224_DIGEST_LENGTH ; x++ ) {
			sprintf( &string[x*2] , "%02x" , (unsigned int) digest[x] ) ;
		}
		SIMPLE_API_RETSTRING(string);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void security_lib_randbytes ( void *pointer ) 
{
	unsigned char *str  ;
	int nNum1  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		nNum1 = (int) SIMPLE_API_GETNUMBER(1) ;
		if ( nNum1 > 0 ) {
			str =  malloc(nNum1+1) ;
			if ( RAND_bytes(str,nNum1) ) {
				SIMPLE_API_RETSTRING2((const char *) str,nNum1);
			}
			else {
				SIMPLE_API_RETNUMBER(0);
			}
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void security_lib_encrypt ( void *pointer )
{
	unsigned char *in, *out, *key, *iv  ;
	int nSize,buflen, tmplen, nSize2  ;
	EVP_CIPHER_CTX *ctx  ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISSTRING(3) ) {
		in = (unsigned char *) SIMPLE_API_GETSTRING(1) ;
		key = (unsigned char *) SIMPLE_API_GETSTRING(2) ;
		iv = (unsigned char *) SIMPLE_API_GETSTRING(3) ;
		nSize = SIMPLE_API_GETSTRINGSIZE(1) ;
		out = (unsigned char *) malloc(nSize*2) ;
		ctx = EVP_CIPHER_CTX_new();
		if ( ctx == NULL ) {
			printf( SIMPLE_OOM ) ;
			return ;
		}
		EVP_EncryptInit_ex(ctx, EVP_bf_cbc(), NULL, key, iv);
		if ( !EVP_EncryptUpdate(ctx, out, &buflen, in, nSize) ) {
			free( out ) ;
			EVP_CIPHER_CTX_free(ctx);
			return ;
		}
		if ( !EVP_EncryptFinal_ex(ctx, out + buflen, &tmplen) ) {
			free( out ) ;
			EVP_CIPHER_CTX_free(ctx);
			return ;
		}
		nSize2 = buflen + tmplen ;
		SIMPLE_API_RETSTRING2((const char *) out,nSize2);
		EVP_CIPHER_CTX_free(ctx);
		free( out ) ;
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void security_lib_decrypt ( void *pointer )
{
	unsigned char *in, *out, *key, *iv  ;
	int nSize,buflen, tmplen, nSize2  ;
	EVP_CIPHER_CTX *ctx  ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARACOUNT);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISSTRING(3) ) {
		in = (unsigned char *) SIMPLE_API_GETSTRING(1) ;
		key = (unsigned char *) SIMPLE_API_GETSTRING(2) ;
		iv = (unsigned char *) SIMPLE_API_GETSTRING(3) ;
		nSize = SIMPLE_API_GETSTRINGSIZE(1) ;
		out = (unsigned char *) malloc(nSize*2) ;
		ctx = EVP_CIPHER_CTX_new();
		if ( ctx == NULL ) {
			printf( SIMPLE_OOM ) ;
			return ;
		}
		EVP_DecryptInit_ex(ctx, EVP_bf_cbc(), NULL, key, iv);
		if ( !EVP_DecryptUpdate(ctx, out, &buflen, in, nSize) ) {
			free( out ) ;
			EVP_CIPHER_CTX_free(ctx);
			return ;
		}
		if ( !EVP_DecryptFinal_ex(ctx, out + buflen, &tmplen) ) {
			free( out ) ;
			EVP_CIPHER_CTX_free(ctx);
			return ;
		}
		nSize2 = buflen + tmplen ;
		SIMPLE_API_RETSTRING2((const char *) out,nSize2);
		EVP_CIPHER_CTX_free(ctx);
		free( out ) ;
	}
	else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
