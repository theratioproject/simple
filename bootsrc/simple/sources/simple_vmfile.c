/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/ring.h"
#include <sys/types.h>
#ifdef _WIN32
/* Windows Only */
#include <windows.h>
#else
#include <sys/stat.h>
#include <dirent.h>
#endif
/* Functions */

void ring_vm_file_loadfunctions ( RingState *pRingState )
{
	ring_vm_funcregister("fopen",ring_vm_file_fopen);
	ring_vm_funcregister("fclose",ring_vm_file_fclose);
	ring_vm_funcregister("fflush",ring_vm_file_fflush);
	ring_vm_funcregister("freopen",ring_vm_file_freopen);
	ring_vm_funcregister("tempfile",ring_vm_file_tempfile);
	ring_vm_funcregister("tempname",ring_vm_file_tempname);
	ring_vm_funcregister("fseek",ring_vm_file_fseek);
	ring_vm_funcregister("ftell",ring_vm_file_ftell);
	ring_vm_funcregister("rewind",ring_vm_file_rewind);
	ring_vm_funcregister("fgetpos",ring_vm_file_fgetpos);
	ring_vm_funcregister("fsetpos",ring_vm_file_fsetpos);
	ring_vm_funcregister("clearerr",ring_vm_file_clearerr);
	ring_vm_funcregister("feof",ring_vm_file_feof);
	ring_vm_funcregister("ferror",ring_vm_file_ferror);
	ring_vm_funcregister("perror",ring_vm_file_perror);
	ring_vm_funcregister("rename",ring_vm_file_rename);
	ring_vm_funcregister("remove",ring_vm_file_remove);
	ring_vm_funcregister("fgetc",ring_vm_file_fgetc);
	ring_vm_funcregister("fgets",ring_vm_file_fgets);
	ring_vm_funcregister("fputc",ring_vm_file_fputc);
	ring_vm_funcregister("fputs",ring_vm_file_fputs);
	ring_vm_funcregister("ungetc",ring_vm_file_ungetc);
	ring_vm_funcregister("fread",ring_vm_file_fread);
	ring_vm_funcregister("fwrite",ring_vm_file_fwrite);
	ring_vm_funcregister("dir",ring_vm_file_dir);
	ring_vm_funcregister("read",ring_vm_file_read);
	ring_vm_funcregister("write",ring_vm_file_write);
	ring_vm_funcregister("fexists",ring_vm_file_fexists);
	ring_vm_funcregister("int2bytes",ring_vm_file_int2bytes);
	ring_vm_funcregister("float2bytes",ring_vm_file_float2bytes);
	ring_vm_funcregister("double2bytes",ring_vm_file_double2bytes);
	ring_vm_funcregister("bytes2int",ring_vm_file_bytes2int);
	ring_vm_funcregister("bytes2float",ring_vm_file_bytes2float);
	ring_vm_funcregister("bytes2double",ring_vm_file_bytes2double);
}

void ring_vm_file_fopen ( void *pPointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) ) {
		fp = fopen(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRING(2));
		SIMPLE_API_RETCPOINTER(fp,SIMPLE_VM_POINTER_FILE);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fclose ( void *pPointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			SIMPLE_API_RETNUMBER(fclose(fp));
			SIMPLE_API_SETNULLPOINTER(1);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fflush ( void *pPointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			SIMPLE_API_RETNUMBER(fflush(fp));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_freopen ( void *pPointer )
{
	FILE *fp  ;
	FILE *fp2  ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISPOINTER(3) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(3,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			fp2 = freopen(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRING(2),fp);
			SIMPLE_API_RETCPOINTER(fp2,SIMPLE_VM_POINTER_FILE);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_tempfile ( void *pPointer )
{
	FILE *fp  ;
	fp = tmpfile();
	SIMPLE_API_RETCPOINTER(fp,SIMPLE_VM_POINTER_FILE);
}

void ring_vm_file_tempname ( void *pPointer )
{
	#ifdef _WIN32
	/* Windows */
	char _tmpfile[20]  ;
	//errno_t error  ;
	//error = tmpnam_s(_tmpfile,20);
	//if ( error ) {
	//	SIMPLE_API_ERROR(SIMPLE_VM_ERROR_TEMPFILENAME);
	//}
	//else {
		SIMPLE_API_RETSTRING(_tmpfile);
	//}
	/* Mac OS X */
	#elif __MACH__
	SIMPLE_API_RETSTRING(tmpnam(NULL));
	/* Linux */
	#else
	char _tmpfile[20] = "/tmp/ringtempXXXXXX" ;
	SIMPLE_API_RETSTRING(mkdtemp(_tmpfile));
	#endif
}

void ring_vm_file_fseek ( void *pPointer )
{
	int nResult  ;
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			nResult = fseek(fp,SIMPLE_API_GETNUMBER(2),SIMPLE_API_GETNUMBER(3));
			SIMPLE_API_RETNUMBER(nResult);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_ftell ( void *pPointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			SIMPLE_API_RETNUMBER(ftell(fp));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_rewind ( void *pPointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			rewind(fp);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fgetpos ( void *pPointer )
{
	fpos_t *pos  ;
	int nResult  ;
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			pos = NULL ;
			nResult = fgetpos(fp,pos);
			if ( nResult == 0 ) {
				SIMPLE_API_RETCPOINTER(pos,SIMPLE_VM_POINTER_FILEPOS);
			} else {
				SIMPLE_API_RETNUMBER(nResult);
			}
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fsetpos ( void *pPointer )
{
	int nResult  ;
	FILE *fp  ;
	fpos_t *pos  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISPOINTER(2) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		pos = (fpos_t *) SIMPLE_API_GETCPOINTER(2,SIMPLE_VM_POINTER_FILEPOS) ;
		if ( (fp != NULL)  && (pos != NULL) ) {
			nResult = fsetpos(fp,pos);
			SIMPLE_API_RETNUMBER(nResult);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_clearerr ( void *pPointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			clearerr(fp);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_feof ( void *pPointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			SIMPLE_API_RETNUMBER(feof(fp));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_ferror ( void *pPointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			SIMPLE_API_RETNUMBER(ferror(fp));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_perror ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		perror(SIMPLE_API_GETSTRING(1));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_rename ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) ) {
		rename(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRING(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_remove ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		remove(SIMPLE_API_GETSTRING(1));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fgetc ( void *pPointer )
{
	int c  ;
	char cStr[2]  ;
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			c = fgetc(fp);
			if ( c != EOF ) {
				cStr[0] = c ;
				cStr[1] = '\0' ;
				SIMPLE_API_RETSTRING(cStr);
			} else {
				SIMPLE_API_RETNUMBER(c);
			}
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fgets ( void *pPointer )
{
	char *cStr  ;
	int nSize  ;
	FILE *fp  ;
	char *cResult  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			nSize = SIMPLE_API_GETNUMBER(2) ;
			if ( nSize < 1 ) {
				SIMPLE_API_ERROR(SIMPLE_VM_FILE_BUFFERSIZE);
				return ;
			}
			nSize++ ;
			cStr = (char *) ring_state_malloc(((VM *) pPointer)->pRingState,nSize);
			if ( cStr == NULL ) {
				SIMPLE_API_ERROR(SIMPLE_OOM);
				return ;
			}
			cResult = fgets(cStr,nSize,fp);
			if ( cResult != NULL ) {
				SIMPLE_API_RETSTRING(cStr);
			} else {
				SIMPLE_API_RETNUMBER(0);
			}
			ring_state_free(((VM *) pPointer)->pRingState,cStr);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fputc ( void *pPointer )
{
	int c  ;
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			c = fputc(SIMPLE_API_GETSTRING(2)[0],fp);
			if ( c != EOF ) {
				SIMPLE_API_RETNUMBER(1);
			} else {
				SIMPLE_API_RETNUMBER(0);
			}
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fputs ( void *pPointer )
{
	int c  ;
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			c = fputs(SIMPLE_API_GETSTRING(2),fp);
			if ( c != EOF ) {
				SIMPLE_API_RETNUMBER(1);
			} else {
				SIMPLE_API_RETNUMBER(0);
			}
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_ungetc ( void *pPointer )
{
	int c  ;
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			c = ungetc(SIMPLE_API_GETSTRING(2)[0],fp);
			if ( c != EOF ) {
				SIMPLE_API_RETNUMBER(1);
			} else {
				SIMPLE_API_RETNUMBER(0);
			}
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fread ( void *pPointer )
{
	char *cStr  ;
	int nSize  ;
	int nResult  ;
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			nSize = SIMPLE_API_GETNUMBER(2) ;
			if ( nSize < 1 ) {
				SIMPLE_API_ERROR(SIMPLE_VM_FILE_BUFFERSIZE);
				return ;
			}
			cStr = (char *) ring_state_malloc(((VM *) pPointer)->pRingState,nSize);
			if ( cStr == NULL ) {
				SIMPLE_API_ERROR(SIMPLE_OOM);
				return ;
			}
			nResult = fread(cStr,1,nSize,fp);
			if ( nResult == 0 ) {
				SIMPLE_API_RETNUMBER(nResult);
			} else {
				SIMPLE_API_RETSTRING2(cStr,nResult);
			}
			ring_state_free(((VM *) pPointer)->pRingState,cStr);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fwrite ( void *pPointer )
{
	int nResult  ;
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		fp = (FILE *) SIMPLE_API_GETCPOINTER(1,SIMPLE_VM_POINTER_FILE) ;
		if ( fp != NULL ) {
			nResult = fwrite(SIMPLE_API_GETSTRING(2),1,SIMPLE_API_GETSTRINGSIZE(2) ,fp);
			SIMPLE_API_RETNUMBER(nResult);
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_dir ( void *pPointer )
{
	const char *cStr  ;
	List *pList, *pList2  ;
	#ifdef _WIN32
	/* Windows Only */
	WIN32_FIND_DATA fdFile  ;
	HANDLE hFind  ;
	String *pString  ;
	#else
	DIR *pDir  ;
	struct dirent *pDirent  ;
	struct stat st  ;
	#endif
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cStr = SIMPLE_API_GETSTRING(1);
		pList = SIMPLE_API_NEWLIST ;
		#ifdef _WIN32
		/* Windows Only */
		pString = ring_string_new_gc(((VM *) pPointer)->pRingState,cStr);
		ring_string_add_gc(((VM *) pPointer)->pRingState,pString,"\\*.*");
		cStr = ring_string_get(pString);
		if ( ! ((hFind = FindFirstFile(cStr, &fdFile)) == INVALID_HANDLE_VALUE) ) {
			do {
				if ( strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0 ) {
					pList2 = ring_list_newlist_gc(((VM *) pPointer)->pRingState,pList);
					ring_list_addstring_gc(((VM *) pPointer)->pRingState,pList2,fdFile.cFileName);
					if ( fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) {
						ring_list_adddouble_gc(((VM *) pPointer)->pRingState,pList2,1);
					} else {
						ring_list_adddouble_gc(((VM *) pPointer)->pRingState,pList2,0);
					}
				}
			} while (FindNextFile(hFind, &fdFile))  ;
			SIMPLE_API_RETLIST(pList);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADDIRECTORY);
		}
		ring_string_delete_gc(((VM *) pPointer)->pRingState,pString);
		#else
		pDir = opendir(cStr);
		if ( pDir != NULL ) {
			while ( (pDirent = readdir(pDir)) ) {
				pList2 = ring_list_newlist_gc(((VM *) pPointer)->pRingState,pList);
				ring_list_addstring_gc(((VM *) pPointer)->pRingState,pList2,pDirent->d_name);
				stat(pDirent->d_name,&st);
				if ( S_ISDIR(st.st_mode) ) {
					ring_list_adddouble_gc(((VM *) pPointer)->pRingState,pList2,1);
				} else {
					ring_list_adddouble_gc(((VM *) pPointer)->pRingState,pList2,0);
				}
			}
			closedir(pDir);
			SIMPLE_API_RETLIST(pList);
		} else {
			SIMPLE_API_ERROR(SIMPLE_API_BADDIRECTORY);
		}
		#endif
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_read ( void *pPointer )
{
	FILE *fp  ;
	long int nSize  ;
	char *cBuffer  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		fp = fopen(SIMPLE_API_GETSTRING(1) , "rb" );
		if ( fp == NULL ) {
			SIMPLE_API_ERROR(SIMPLE_VM_ERROR_CANTOPENFILE);
			return ;
		}
		fseek( fp , 0 , SEEK_END );
		nSize = ftell(fp);
		fseek( fp , 0 , SEEK_SET );
		cBuffer = (char *) ring_state_malloc(((VM *) pPointer)->pRingState,nSize);
		if ( cBuffer == NULL ) {
			SIMPLE_API_ERROR(SIMPLE_OOM);
			return ;
		}
		fread( cBuffer , 1 , nSize , fp );
		fclose( fp ) ;
		SIMPLE_API_RETSTRING2(cBuffer,nSize);
		ring_state_free(((VM *) pPointer)->pRingState,cBuffer);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_write ( void *pPointer )
{
	FILE *fp  ;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if ( SIMPLE_API_ISSTRING(2) ) {
			fp = fopen(SIMPLE_API_GETSTRING(1) , "w+b" );
			if ( fp == NULL ) {
				SIMPLE_API_ERROR(SIMPLE_VM_ERROR_CANTOPENFILE);
				return ;
			}
			fwrite( SIMPLE_API_GETSTRING(2) , SIMPLE_API_GETSTRINGSIZE(2) , 1 , fp );
			fclose( fp ) ;
		} else {
			SIMPLE_API_ERROR("Error in second parameter, Function requires string !");
			return ;
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_fexists ( void *pPointer )
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		SIMPLE_API_RETNUMBER(ring_fexists(SIMPLE_API_GETSTRING(1)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
/* Number & Bytes */

void ring_vm_file_int2bytes ( void *pPointer )
{
	Ring_uData uData  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		uData.iNumber = (int) SIMPLE_API_GETNUMBER(1) ;
		SIMPLE_API_RETSTRING2(uData.cBytes,4);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_float2bytes ( void *pPointer )
{
	Ring_uData uData  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		uData.fNumber = (float) SIMPLE_API_GETNUMBER(1) ;
		SIMPLE_API_RETSTRING2(uData.cBytes,4);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_double2bytes ( void *pPointer )
{
	Ring_uData uData  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) ) {
		uData.dNumber = SIMPLE_API_GETNUMBER(1) ;
		SIMPLE_API_RETSTRING2(uData.cBytesDouble,8);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_file_bytes2int ( void *pPointer )
{
	Ring_uData uData  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if ( SIMPLE_API_GETSTRINGSIZE(1) == 4 ) {
			uData.cBytes[0] = SIMPLE_API_GETSTRING(1)[0] ;
			uData.cBytes[1] = SIMPLE_API_GETSTRING(1)[1] ;
			uData.cBytes[2] = SIMPLE_API_GETSTRING(1)[2] ;
			uData.cBytes[3] = SIMPLE_API_GETSTRING(1)[3] ;
			SIMPLE_API_RETNUMBER((double) uData.iNumber);
			return ;
		}
	}
	SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
}

void ring_vm_file_bytes2float ( void *pPointer )
{
	Ring_uData uData  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if ( SIMPLE_API_GETSTRINGSIZE(1) == 4 ) {
			uData.cBytes[0] = SIMPLE_API_GETSTRING(1)[0] ;
			uData.cBytes[1] = SIMPLE_API_GETSTRING(1)[1] ;
			uData.cBytes[2] = SIMPLE_API_GETSTRING(1)[2] ;
			uData.cBytes[3] = SIMPLE_API_GETSTRING(1)[3] ;
			SIMPLE_API_RETNUMBER((double) uData.fNumber);
			return ;
		}
	}
	SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
}

void ring_vm_file_bytes2double ( void *pPointer )
{
	Ring_uData uData  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		if ( SIMPLE_API_GETSTRINGSIZE(1) == 8 ) {
			uData.cBytesDouble[0] = SIMPLE_API_GETSTRING(1)[0] ;
			uData.cBytesDouble[1] = SIMPLE_API_GETSTRING(1)[1] ;
			uData.cBytesDouble[2] = SIMPLE_API_GETSTRING(1)[2] ;
			uData.cBytesDouble[3] = SIMPLE_API_GETSTRING(1)[3] ;
			uData.cBytesDouble[4] = SIMPLE_API_GETSTRING(1)[4] ;
			uData.cBytesDouble[5] = SIMPLE_API_GETSTRING(1)[5] ;
			uData.cBytesDouble[6] = SIMPLE_API_GETSTRING(1)[6] ;
			uData.cBytesDouble[7] = SIMPLE_API_GETSTRING(1)[7] ;
			SIMPLE_API_RETNUMBER(uData.dNumber);
			return ;
		}
	}
	SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
}
