
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   archiver.c
 * Author: thecarisma
 *
 * Created on February 11, 2018, 3:27 PM
 */

#include "../../../simple/includes/simple.h"
#include "zip.h"
#include "archiver.h"

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
    #define SIMPLE_API
#else
    //  do nothing and hope for the best?
    #define SIMPLE_API
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

SIMPLE_API void init_simple_module(SimpleState *sState)
{   
    /** ZIP **/
    register_block("__open_zip",open_zip_file);
    register_block("__open_zip_entry",open_zip_entry_file);
    register_block("__write_zip_entry",write_zip_entry_file);
    register_block("__fwrite_zip_entry",fwrite_zip_entry_file);
    register_block("__read_zip_entry",read_zip_entry_file);
    register_block("__fread_zip_entry",fread_zip_entry_file);
    register_block("__close_zip_entry",close_zip_entry_file);
    register_block("__extract_zip",extract_zip_file);
    register_block("__close_zip",close_zip_file);
    register_block("__total_zip_file_count",total_zip_file_count);
    register_block("__zip_entry_by_index",zip_entry_by_index);
    register_block("__extract_zip_entry",extract_zip_entry);
    /** TAR **/
}

ZIP_T *zip_openfile(const char *zip_file, const char *open_mode) {
    return zip_open(zip_file, ZIP_DEFAULT_COMPRESSION_LEVEL, open_mode[0]);
}

void open_zip_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	SIMPLE_API_RETCPOINTER(zip_openfile(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRING(2)),"SIMPLE_T");
}

void open_zip_entry_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISPOINTER(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	SIMPLE_API_RETNUMBER(zip_entry_open((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"),SIMPLE_API_GETSTRING(2)));
}

void write_zip_entry_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISPOINTER(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISNUMBER(3) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	SIMPLE_API_RETNUMBER(zip_entry_write((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"),SIMPLE_API_GETSTRING(2), (int) SIMPLE_API_GETNUMBER(3)));
}

void fwrite_zip_entry_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISPOINTER(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	SIMPLE_API_RETNUMBER(zip_entry_fwrite((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"),SIMPLE_API_GETSTRING(2)));
}

void read_zip_entry_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISPOINTER(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISPOINTER(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISPOINTER(3) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	SIMPLE_API_RETNUMBER(zip_entry_read((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"),(void *) SIMPLE_API_GETCPOINTER(2,"void"),(size_t *) SIMPLE_API_GETCPOINTER(3,"size_t")));
}

void fread_zip_entry_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISPOINTER(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	SIMPLE_API_RETNUMBER(zip_entry_fread((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"),SIMPLE_API_GETSTRING(2)));
}

void close_zip_entry_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISPOINTER(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	SIMPLE_API_RETNUMBER(zip_entry_close((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T")));
}

int on_extract_entry(const char *zip_file, void *arg) {
    return 0;
}

void zip_extract_all(const char *zip_file, const char *destination_folder) {
    int arg = 2;
    zip_extract(zip_file,destination_folder, on_extract_entry, &arg);
}

void extract_zip_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	zip_extract_all(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRING(2));
}

void close_zip_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISPOINTER(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	zip_close((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"));
}

int zip_files_count(ZIP_T *zip) {
	/*return mz_zip_reader_get_num_files((mz_zip_archive *) zip);*/
}


void total_zip_file_count ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISPOINTER(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	SIMPLE_API_RETNUMBER(zip_files_count((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T")));
}

const char *zip_entry_name_by_index(ZIP_T *zip,int index) {
    /*mz_zip_archive_file_stat info;
    if (!mz_zip_reader_file_stat((mz_zip_archive *) zip, index-1, &info)) {
        return NULL;
    }	
    return info.m_filename ;*/
}


void zip_entry_by_index ( void *pointer )
{
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( ! SIMPLE_API_ISPOINTER(1) ) {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
    if ( ! SIMPLE_API_ISNUMBER(2) ) {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
    SIMPLE_API_RETSTRING(zip_entry_name_by_index((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"), (int ) SIMPLE_API_GETNUMBER(2)));
}

static size_t on_extract(void *arg, unsigned long long offset, const void *data,size_t size) {
    struct buffer_t *buf = (struct buffer_t *) arg;
    buf->data = realloc(buf->data, buf->size + size + 1);
    assert(NULL != buf->data);

    memcpy(&(buf->data[buf->size]), data, size);
    buf->size += size;
    buf->data[buf->size] = 0;
    return size;
}

void extract_zip_entry ( void *pointer )
{
    const char *cZIPFile;
    const char *cFile;
    struct buffer_t buf = {0};

    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    if ( ! SIMPLE_API_ISSTRING(1) ) {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
    if ( ! SIMPLE_API_ISSTRING(2) ) {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }

    cZIPFile = SIMPLE_API_GETSTRING(1);
    cFile    = SIMPLE_API_GETSTRING(2);

    zip = zip_open(cZIPFile, 0, 'r');
    {
        zip_entry_open(zip, cFile);
        {
            zip_entry_extract(zip, on_extract, &buf);
        }
        zip_entry_close(zip);
    }
    zip_close(zip);

    SIMPLE_API_RETSTRING2(buf.data,buf.size);

    free(buf.data);
}
