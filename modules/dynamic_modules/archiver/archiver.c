
/* 
    Copyright (c) 2016-2018 Azeez Adewale <azeezadewale98@gmail.com> 
    MIT License Copyright (c) 2018 simple 

*/

/* 
 * File:   archiver.c
 * Author: thecarisma
 *
 * Created on February 11, 2018, 3:27 PM
 */

#include "../../../simple/include/simple.h"
#include "zip.c"
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
    register_block("__ZIP_DEFAULT_COMPRESSION_LEVEL",zip_ZIP_DEFAULT_COMPRESSION_LEVEL);
    register_block("__open_zip",open_zip_file);
    register_block("__extract_zip",extract_zip_file);
    register_block("__close_zip",close_zip_file);
    register_block("__total_zip_file_count",total_zip_file_count);
	/** ZIP ENTRY **/
    register_block("__open_zip_entry",open_zip_entry_file);
    register_block("__write_zip_entry",write_zip_entry_file);
    register_block("__fwrite_zip_entry",fwrite_zip_entry_file);
    register_block("__read_zip_entry",read_zip_entry_file);
    register_block("__fread_zip_entry",fread_zip_entry_file);
    register_block("__close_zip_entry",close_zip_entry_file);
    register_block("__zip_entry_by_index",zip_entry_by_index);
    register_block("__extract_zip_entry",extract_zip_entry);
    register_block("__zip_entry_stat_info",zip_entry_stat_info);
    register_block("__zip_entry_name_by_index",zip_entry_name_by_index);
	
    /** TAR **/
}

void zip_ZIP_DEFAULT_COMPRESSION_LEVEL ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETNUMBER(ZIP_DEFAULT_COMPRESSION_LEVEL);
}

void open_zip_file ( void *pointer )
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	SIMPLE_API_IGNORECPOINTERTYPE ;
	if ( ! SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISNUMBER(2) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	if ( ! SIMPLE_API_ISSTRING(3) ) {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
		return ;
	}
	SIMPLE_API_RETCPOINTER(zip_open(SIMPLE_API_GETSTRING(1),(int)SIMPLE_API_GETNUMBER(2),(const char*)SIMPLE_API_GETSTRING(3)[0]),"SIMPLE_T");
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
	SIMPLE_API_RETNUMBER(zip_entry_write((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"),(const char *)SIMPLE_API_GETSTRING(2), (size_t) SIMPLE_API_GETNUMBER(3)));
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
	return mz_zip_reader_get_num_files((mz_zip_archive *) zip);
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

char *___zip_entry_name_by_index(ZIP_T *zip,int index) {
    mz_zip_archive_file_stat info;
    if (!mz_zip_reader_file_stat((mz_zip_archive *) zip, index, &info)) {
        return NULL;
    }	
	printf(" passed %s \n",info.m_filename);
    return info.m_filename ;
}

void zip_entry_stat_info(void *pointer)
{
	VM* vm;
    mz_zip_archive_file_stat info;
	List *list, *list2, *list3;
	int index ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    SIMPLE_API_IGNORECPOINTERTYPE ;
    if ( ! SIMPLE_API_ISPOINTER(1) ) {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
    if ( ! SIMPLE_API_ISNUMBER(2) && !SIMPLE_API_ISSTRING(2)) {
        SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
        return ;
    }
	if (SIMPLE_API_ISNUMBER(2)) {
		index = SIMPLE_API_GETNUMBER(2);
	}
	else {
		index = mz_zip_reader_locate_file((mz_zip_archive *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"), SIMPLE_API_GETSTRING(2), NULL, 0);
	}
    if (!mz_zip_reader_file_stat((mz_zip_archive *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"), index, &info)) {
        SIMPLE_API_RETSTRING("");
		return ;
    }	
	vm = (VM*) pointer;
	list = SIMPLE_API_NEWLIST;
	simple_list_adddouble_gc(vm->sState,list,info.m_file_index); 		/* m_file_index */
	simple_list_adddouble_gc(vm->sState,list,info.m_central_dir_ofs); 	/* m_central_dir_ofs */
	simple_list_adddouble_gc(vm->sState,list,info.m_version_made_by); 	/* m_version_made_by */
	simple_list_adddouble_gc(vm->sState,list,info.m_version_needed); 	/* m_version_needed */
	simple_list_adddouble_gc(vm->sState,list,info.m_bit_flag); 			/* m_bit_flag */
	simple_list_adddouble_gc(vm->sState,list,info.m_method); 			/* m_method */
	#ifndef MINIZ_NO_TIME
		list2 = SIMPLE_API_NEWLIST ;
		simple_list_addpointer_gc(vm->sState,list2,info.m_time);
		simple_list_addstring_gc(vm->sState,list2,"SIMPLE_LANG_TIME_");
		simple_list_addint_gc(vm->sState,list2,2);
		list3 = simple_list_newlist_gc(vm->sState,list);
		simple_list_copy_gc(vm->sState,list3,list2);					/* m_time *///"SIMPLE_LANG_TIME_"
	#endif
	simple_list_adddouble_gc(vm->sState,list,info.m_crc32); 			/* m_crc32 */
	simple_list_adddouble_gc(vm->sState,list,info.m_comp_size); 		/* m_comp_size */
	simple_list_adddouble_gc(vm->sState,list,info.m_uncomp_size); 		/* m_uncomp_size */
	simple_list_adddouble_gc(vm->sState,list,info.m_internal_attr); 	/* m_internal_attr */
	simple_list_adddouble_gc(vm->sState,list,info.m_external_attr); 	/* m_external_attr */
	simple_list_adddouble_gc(vm->sState,list,info.m_local_header_ofs); 	/* m_local_header_ofs */
	simple_list_adddouble_gc(vm->sState,list,info.m_comment_size); 		/* m_comment_size */
	simple_list_addstring_gc(vm->sState,list,info.m_filename); 			/* m_filename */
	simple_list_addstring_gc(vm->sState,list,info.m_comment); 			/* m_comment */
	SIMPLE_API_RETLIST(list);
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
    SIMPLE_API_RETSTRING(___zip_entry_name_by_index((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"), (int ) SIMPLE_API_GETNUMBER(2)));
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
	struct zip_t *zip;
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

void zip_entry_name_by_index(void *pointer)
{
	const char* name ;
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
	name = ___zip_entry_name_by_index((ZIP_T *) SIMPLE_API_GETCPOINTER(1,"SIMPLE_T"),SIMPLE_API_GETNUMBER(2));
	printf("done here too %s\n", name);
	SIMPLE_API_RETSTRING(name);
	printf("ok ");
	return ;
}

