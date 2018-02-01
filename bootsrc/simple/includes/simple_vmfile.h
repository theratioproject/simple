/* Copyright (c) 2013-2016 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_vmfile_h
#define simple_vmfile_h
/* Functions */

void simple_vm_file_loadfunctions ( RingState *pRingState ) ;

void simple_vm_file_fopen ( void *pPointer ) ;

void simple_vm_file_fclose ( void *pPointer ) ;

void simple_vm_file_fflush ( void *pPointer ) ;

void simple_vm_file_freopen ( void *pPointer ) ;

void simple_vm_file_tempfile ( void *pPointer ) ;

void simple_vm_file_tempname ( void *pPointer ) ;

void simple_vm_file_fseek ( void *pPointer ) ;

void simple_vm_file_ftell ( void *pPointer ) ;

void simple_vm_file_rewind ( void *pPointer ) ;

void simple_vm_file_fgetpos ( void *pPointer ) ;

void simple_vm_file_fsetpos ( void *pPointer ) ;

void simple_vm_file_clearerr ( void *pPointer ) ;

void simple_vm_file_feof ( void *pPointer ) ;

void simple_vm_file_ferror ( void *pPointer ) ;

void simple_vm_file_perror ( void *pPointer ) ;

void simple_vm_file_rename ( void *pPointer ) ;

void simple_vm_file_remove ( void *pPointer ) ;

void simple_vm_file_fgetc ( void *pPointer ) ;

void simple_vm_file_fgets ( void *pPointer ) ;

void simple_vm_file_fputc ( void *pPointer ) ;

void simple_vm_file_fputs ( void *pPointer ) ;

void simple_vm_file_ungetc ( void *pPointer ) ;

void simple_vm_file_fread ( void *pPointer ) ;

void simple_vm_file_fwrite ( void *pPointer ) ;

void simple_vm_file_dir ( void *pPointer ) ;

void simple_vm_file_read ( void *pPointer ) ;

void simple_vm_file_write ( void *pPointer ) ;

void simple_vm_file_fexists ( void *pPointer ) ;
/* Number & Bytes */

void simple_vm_file_int2bytes ( void *pPointer ) ;

void simple_vm_file_float2bytes ( void *pPointer ) ;

void simple_vm_file_double2bytes ( void *pPointer ) ;

void simple_vm_file_bytes2int ( void *pPointer ) ;

void simple_vm_file_bytes2float ( void *pPointer ) ;

void simple_vm_file_bytes2double ( void *pPointer ) ;
/* Constants */
#define RING_VM_FILE_BUFFERSIZE "Buffer size must be >= 1"
#define RING_VM_POINTER_FILE "file"
#define RING_VM_POINTER_FILEPOS "filepos"
#define RING_API_BADDIRECTORY "Error, Couldn't open the directory"
/* Data */
typedef union Ring_uData {
	int iNumber  ;
	float fNumber  ;
	double dNumber  ;
	char cBytes[4]  ;
	char cBytesDouble[8]  ;
} Ring_uData ;
#endif
