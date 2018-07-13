
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   parser.c
 * Author: Azeez Adewale
 *
 * Created on February 26, 2018, 6:53 PM
 */

#include "../../../simple/includes/simple.h"
#include "parser.h"
#include <stdint.h>
#include "includes/json.h"

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
    register_block("__test_json_c",test_json_c);
    register_block("__init_json_c",init_json_c);
    register_block("__json_c_object_get_type",json_c_object_get_type);
    register_block("__json_c_type_to_name",json_c_type_to_name);
    register_block("__json_c_object_object_get",json_c_object_object_get);
    register_block("__json_c_object_object_get_id",json_c_object_object_get_id);
    register_block("__json_c_object_to_json_string",json_c_object_to_json_string);
    register_block("__json_c_object_get_string",json_c_object_get_string);
    register_block("__json_c_object_get_number",json_c_object_get_number);
    register_block("__json_c_object_get_decimal",json_c_object_get_decimal);
    register_block("__json_c_object_get_boolean",json_c_object_get_boolean);
    register_block("__json_c_object_length",json_c_object_length);
}

void print_hex( const char* s) 
{
        const char *iter = s;
        unsigned char ch;
        while ((ch = *iter++) != 0) {
           if( ',' != ch)
            printf("%hhx ", ch);
           else
            printf( ",");
        }
        printf("\n");
}

void test_json_c ( void *pointer )
{
	int strings_match,retval;
    const char *input = "\"\\ud840\\udd26,\\ud840\\udd27,\\ud800\\udd26,\\ud800\\udd27\"";
    const char *expected = "\xF0\xA0\x84\xA6,\xF0\xA0\x84\xA7,\xF0\x90\x84\xA6,\xF0\x90\x84\xA7";
    struct json_object *parse_result = json_tokener_parse((char*)input);
    const char *unjson = json_object_get_string(parse_result);

    printf("input: %s\n", input);

    strings_match = !strcmp( expected, unjson);
	retval = 0;
    if (strings_match) {
        printf("JSON parse result is correct: %s\n", unjson);
        printf("PASS\n");
    } else {
        printf("JSON parse result doesn't match expected string\n");
        printf("expected string bytes: ");
        print_hex( expected);
        printf("parsed string bytes:   ");
        print_hex( unjson);
        printf("FAIL\n");
        retval = 1;
    }
	json_object_put(parse_result);
	//return retval;
}

void init_json_c ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    if ( SIMPLE_API_ISSTRING(1) ) {
        struct json_object *new_obj = json_tokener_parse(SIMPLE_API_GETSTRING(1));
        SIMPLE_API_RETCPOINTER(new_obj, "SIMPLE_JSON_C");
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_object_get_type ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        SIMPLE_API_RETNUMBER(json_object_get_type((json_object*) SIMPLE_API_GETCPOINTER(1, "SIMPLE_JSON_C")));
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_type_to_name ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISNUMBER(1) ) {
        SIMPLE_API_RETSTRING(json_type_to_name(SIMPLE_API_GETNUMBER(1)));
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_object_object_get ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2)) {
        struct json_object *new_obj = json_object_object_get(((json_object*) SIMPLE_API_GETCPOINTER(1, "SIMPLE_JSON_C")), SIMPLE_API_GETSTRING(2));
        SIMPLE_API_RETCPOINTER(new_obj, "SIMPLE_JSON_C");
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_object_object_get_id ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2)) {
        struct json_object *obj = (json_object*) SIMPLE_API_GETCPOINTER(1, "SIMPLE_JSON_C") ;
        json_object *new_obj = json_object_array_get_idx(obj, SIMPLE_API_GETNUMBER(2));
        SIMPLE_API_RETCPOINTER(obj, "SIMPLE_JSON_C");
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_object_to_json_string ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        struct json_object *obj = (json_object*) SIMPLE_API_GETCPOINTER(1, "SIMPLE_JSON_C");
        SIMPLE_API_RETSTRING(json_object_to_json_string(obj));
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_object_get_string ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        struct json_object *obj = (json_object*) SIMPLE_API_GETCPOINTER(1, "SIMPLE_JSON_C");
        SIMPLE_API_RETSTRING(json_object_get_string(obj));
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_object_get_number ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        struct json_object *obj = (json_object*) SIMPLE_API_GETCPOINTER(1, "SIMPLE_JSON_C");
        SIMPLE_API_RETNUMBER(json_object_get_int64(obj));
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_object_get_decimal ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        struct json_object *obj = (json_object*) SIMPLE_API_GETCPOINTER(1, "SIMPLE_JSON_C");
        SIMPLE_API_RETNUMBER(json_object_get_double(obj));
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_object_get_boolean ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        struct json_object *obj = (json_object*) SIMPLE_API_GETCPOINTER(1, "SIMPLE_JSON_C");
        SIMPLE_API_RETNUMBER(json_object_get_boolean(obj));
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}

void json_c_object_length ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( SIMPLE_API_ISPOINTER(1) ) {
        struct json_object *obj = (json_object*) SIMPLE_API_GETCPOINTER(1, "SIMPLE_JSON_C");
        SIMPLE_API_RETNUMBER(json_object_array_length(obj));
    } else {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
    }
}
