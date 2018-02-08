
/* 
	Copyright (c) 2017-2018 Azeez Adewale <azeezadewale98@gmail.com"> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple.h
 * Author: thecarisma
 *
 * Created on July 10, 2017, 1:10 PM
 */

/*
**  Include Files 
*/
#include "../includes/simple.h"
/* Define Functions */

void simple_objfile_writefile ( SimpleState *sState )
{
	FILE *fObj;
	char cFileName[400]  ;
	/* Create File */
	sprintf( cFileName , "%splex" , simple_list_getstring(sState->files_list,1) ) ;
        //printf("TO COMPLEX : %s", change_file_ext(simple_list_getstring(sState->files_list,1), "complex"));
	fObj = fopen(cFileName , "w+b" );
	fprintf( fObj , "# Simple Object File\n"  ) ;
	fprintf( fObj , "# Version 1.1\n"  ) ;
	/* Write Functions Lists */
	fprintf( fObj , "# Functions List\n"  ) ;
	simple_objfile_writelist(sState->blocks_map,fObj);
	/* Write Classes List */
	fprintf( fObj , "# Classes List\n"  ) ;
	simple_objfile_writelist(sState->classes_map,fObj);
	/* Write Moduless */
	fprintf( fObj , "# Moduless List\n"  ) ;
	simple_objfile_writelist(sState->modules_map,fObj);
	/* Write Code */
	fprintf( fObj , "# Program Code\n"  ) ;
	simple_objfile_writelist(sState->pSimpleGenCode,fObj);
	/* Close File */
	fprintf( fObj , "# End of File\n"  ) ;
	fclose( fObj ) ;
}

void simple_objfile_writelist ( List *list,FILE *fObj )
{
	List *list2  ;
	int x,x2  ;
	char *cString  ;
	char cKey[11]  ;
	strcpy(cKey,"ringstring");
	fprintf( fObj , "{\n"  ) ;
	/* Write List Items */
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		list2 = simple_list_getlist(list,x);
		fprintf( fObj , "[T]\n"  ) ;
		for ( x2 = 1 ; x2 <= simple_list_getsize(list2) ; x2++ ) {
			if ( simple_list_isstring(list2,x2) ) {
				fprintf( fObj , "[S][%d]" , simple_list_getstringsize(list2,x2) ) ;
				/* Encrypt String */
				cString = simple_list_getstring(list2,x2) ;
				simple_objfile_xorstring(cString,simple_list_getstringsize(list2,x2),cKey,10);
				fwrite( simple_list_getstring(list2,x2) , 1 , simple_list_getstringsize(list2,x2) , fObj );
				/* Decrypt String */
				simple_objfile_xorstring(cString,simple_list_getstringsize(list2,x2),cKey,10);
				fprintf( fObj , "\n"  ) ;
			}
			else if ( simple_list_isint(list2,x2) ) {
				fprintf( fObj , "[I]%d\n" , simple_list_getint(list2,x2) ) ;
			}
			else if ( simple_list_isdouble(list2,x2) ) {
				fprintf( fObj , "[D]%f\n" , simple_list_getdouble(list2,x2) ) ;
			}
			else if ( simple_list_ispointer(list2,x2) ) {
				fprintf( fObj , "[P]%p\n" , (void *) simple_list_getpointer(list2,x2) ) ;
			}
			else if ( simple_list_islist(list2,x2) ) {
				fprintf( fObj , "[L]\n"  ) ;
				simple_objfile_writelist(simple_list_getlist(list2,x2) ,fObj);
			}
		}
		fprintf( fObj , "[E]\n"  ) ;
	}
	fprintf( fObj , "}\n"  ) ;
}

int simple_objfile_readfile ( SimpleState *sState,char *cFileName )
{
	return simple_objfile_readfromsource(sState,cFileName,SIMPLE_OBJFILE_READFROMFILE) ;
}

int simple_objfile_readstring ( SimpleState *sState,char *cString )
{
	return simple_objfile_readfromsource(sState,cString,SIMPLE_OBJFILE_READFROMSTRING) ;
}

int simple_objfile_readfromsource ( SimpleState *sState,char *cSource,int nSource )
{
	List *listFunctions, *listClasses, *listModuless, *listCode, *listStack  ;
	/* Create Lists */
	listFunctions = simple_list_new_gc(sState,0);
	listClasses = simple_list_new_gc(sState,0);
	listModuless = simple_list_new_gc(sState,0);
	listCode = simple_list_new_gc(sState,0);
	listStack = simple_list_new_gc(sState,0);
	/* Process Content (File or String) */
	if ( nSource == SIMPLE_OBJFILE_READFROMFILE ) {
		if ( ! simple_objfile_processfile(sState,cSource,listFunctions, listClasses, listModuless, listCode, listStack) ) {
			return 0 ;
		}
	}
	else if ( nSource ==SIMPLE_OBJFILE_READFROMSTRING ) {
		if ( ! simple_objfile_processstring(sState,cSource,listFunctions, listClasses, listModuless, listCode, listStack) ) {
			return 0 ;
		}
	}
	simple_list_delete(listStack);
	/* Update Simple State */
	#ifdef DEBUG_OBJFILE
	puts("Old Code List ");
	simple_list_print(sState->pSimpleGenCode);
	#endif
	/* Update Lists */
	sState->blocks_map = listFunctions ;
	sState->classes_map = listClasses ;
	sState->modules_map = listModuless ;
	sState->pSimpleGenCode = listCode ;
	#ifdef DEBUG_OBJFILE
	puts("Update Done! ");
	puts("New Code List ");
	simple_list_print(sState->pSimpleGenCode);
	#endif
	/* Update Classes Pointers */
	simple_objfile_updateclassespointers(sState);
	return 1 ;
}

int simple_objfile_processfile ( SimpleState *sState,char *cFileName,List *listFunctions,List  *listClasses,List  *listModuless,List  *listCode,List  *listStack )
{
	FILE *fObj;
	signed char c  ;
	int nActiveList,nValue,nBraceEnd  ;
	double dValue  ;
	char *cString  ;
	char cKey[11]  ;
	char cFileType[100]  ;
	strcpy(cKey,"ringstring");
	List *list  ;
	/* Set Active List (1=functions 2=classes 3=moduless 4=code) */
	nActiveList = 0 ;
	nBraceEnd = 0 ;
	list = NULL ;
	/* Open File */
	fObj = fopen(cFileName , "rb" );
	if ( fObj==NULL ) {
		printf( "Can't open file %s \n  ",cFileName ) ;
		return 0 ;
	}
	fread( cFileType , 1 , 18 , fObj );
	cFileType[18] = '\0' ;
	if ( strcmp(cFileType,"# Simple Object File") != 0 ) {
		printf( "The file type is not correct - the VM expect a ring object file\n" ) ;
		return 0 ;
	}
	c = getc(fObj);
	fread( cFileType , 1 , 13 , fObj );
	cFileType[13] = '\0' ;
	if ( strcmp(cFileType,"# Version 1.1") != 0 ) {
		printf( "The file version is not correct - the VM expect a ring object file version 1.1\n" ) ;
		return 0 ;
	}
	/* Process File */
	c = getc(fObj);
	while ( c != EOF ) {
		/* Check Char */
		switch ( c ) {
			case '#' :
				/* Read Line */
				while ( c != '\n' ) {
					c = getc(fObj);
					#ifdef DEBUG_OBJFILE
					printf( "%c  ",c ) ;
					#endif
				}
				#ifdef DEBUG_OBJFILE
				puts("Read Comment ! ");
				#endif
				break ;
			case '{' :
				nActiveList++ ;
				switch ( nActiveList ) {
					case 1 :
						list = listFunctions ;
						break ;
					case 2 :
						list = listClasses ;
						break ;
					case 3 :
						list = listModuless ;
						break ;
					case 4 :
						list = listCode ;
						break ;
				}
				break ;
			case '[' :
				c = getc(fObj);
				switch ( c ) {
					case 'S' :
						c = getc(fObj);
						fscanf( fObj , "[%d]" , &nValue ) ;
						cString = (char *) simple_state_malloc(sState,nValue+1);
						fread( cString , 1 , nValue , fObj );
						cString[nValue] = '\0' ;
						/* Decrypt String */
						simple_objfile_xorstring(cString,nValue,cKey,10);
						simple_list_addstring2_gc(sState,list,cString,nValue);
						simple_state_free(sState,cString);
						#ifdef DEBUG_OBJFILE
						printf( "Read String %s Size %d \n",cString,nValue ) ;
						#endif
						break ;
					case 'I' :
						c = getc(fObj);
						fscanf( fObj , "%d" , &nValue ) ;
						simple_list_addint_gc(sState,list,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Number %d \n  ",nValue ) ;
						#endif
						break ;
					case 'D' :
						c = getc(fObj);
						fscanf( fObj , "%lf" , &dValue ) ;
						simple_list_adddouble_gc(sState,list,dValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Double %d  \n",dValue ) ;
						#endif
						break ;
					case 'P' :
						simple_list_addpointer_gc(sState,list,NULL);
						/* Read Line */
						while ( c != '\n' ) {
							c = getc(fObj);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read Pointer ");
						#endif
						break ;
					case 'T' :
						simple_list_addpointer_gc(sState,listStack,list);
						list = simple_list_newlist_gc(sState,list);
						/* Read Line */
						while ( c != '\n' ) {
							c = getc(fObj);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read T ");
						#endif
						break ;
					case 'E' :
						list = (List *) simple_list_getpointer(listStack,simple_list_getsize(listStack)) ;
						simple_list_deletelastitem(listStack);
						/* Read Line */
						while ( c != '\n' ) {
							c = getc(fObj);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read E ");
						#endif
						break ;
					case 'L' :
						/* Read Until { */
						while ( c != '{' ) {
							c = getc(fObj);
						}
						simple_list_addpointer_gc(sState,listStack,list);
						list = simple_list_newlist_gc(sState,list);
						nBraceEnd++ ;
						#ifdef DEBUG_OBJFILE
						puts("Read L ");
						#endif
						break ;
				}
				break ;
			case '}' :
				if ( nBraceEnd ) {
					list = (List *) simple_list_getpointer(listStack,simple_list_getsize(listStack)) ;
					simple_list_deletelastitem(listStack);
					nBraceEnd-- ;
					#ifdef DEBUG_OBJFILE
					puts("Read } ");
					#endif
				}
				break ;
		}
		c = getc(fObj);
	}
	/* Close File */
	fclose( fObj ) ;
	return 1 ;
}

int simple_objfile_processstring ( SimpleState *sState,char *cContent,List *listFunctions,List  *listClasses,List  *listModuless,List  *listCode,List  *listStack )
{
	signed char c  ;
	int nActiveList,nValue,nBraceEnd  ;
	double dValue  ;
	char *cString, *cData  ;
	char cKey[11]  ;
	char cFileType[100]  ;
	strcpy(cKey,"ringstring");
	List *list  ;
	/* Set Active List (1=functions 2=classes 3=moduless 4=code) */
	nActiveList = 0 ;
	nBraceEnd = 0 ;
	list = NULL ;
	cData = cContent ;
	/* Check Type and Version */
	simple_objfile_readc(sState,&cData,cFileType,18);
	cFileType[18] = '\0' ;
	if ( strcmp(cFileType,"# Simple Object File") != 0 ) {
		printf( "The file type is not correct - the VM expect a ring object file\n" ) ;
		return 0 ;
	}
	c = simple_objfile_getc(sState,&cData);
	simple_objfile_readc(sState,&cData,cFileType,13);
	cFileType[13] = '\0' ;
	if ( strcmp(cFileType,"# Version 1.1") != 0 ) {
		printf( "The file version is not correct - the VM expect a ring object file version 1.1\n" ) ;
		return 0 ;
	}
	/* Process Content */
	c = simple_objfile_getc(sState,&cData);
	while ( c != EOF ) {
		/* Check Char */
		switch ( c ) {
			case '#' :
				/* Read Line */
				while ( c != '\n' ) {
					c = simple_objfile_getc(sState,&cData);
					#ifdef DEBUG_OBJFILE
					printf( "%c  ",c ) ;
					#endif
				}
				#ifdef DEBUG_OBJFILE
				puts("Read Comment ! ");
				#endif
				break ;
			case '{' :
				nActiveList++ ;
				switch ( nActiveList ) {
					case 1 :
						list = listFunctions ;
						break ;
					case 2 :
						list = listClasses ;
						break ;
					case 3 :
						list = listModuless ;
						break ;
					case 4 :
						list = listCode ;
						break ;
				}
				break ;
			case '[' :
				c = simple_objfile_getc(sState,&cData);
				switch ( c ) {
					case 'S' :
						c = simple_objfile_getc(sState,&cData);
						sscanf(cData,"[%d]",&nValue);
						/* Pass Letters */
						c = ' ' ;
						while ( c != ']' ) {
							c = simple_objfile_getc(sState,&cData);
						}
						cString = (char *) simple_state_malloc(sState,nValue+1);
						simple_objfile_readc(sState,&cData,cString,nValue);
						cString[nValue] = '\0' ;
						/* Decrypt String */
						simple_objfile_xorstring(cString,nValue,cKey,10);
						simple_list_addstring2_gc(sState,list,cString,nValue);
						simple_state_free(sState,cString);
						#ifdef DEBUG_OBJFILE
						printf( "Read String %s Size %d \n",cString,nValue ) ;
						#endif
						break ;
					case 'I' :
						c = simple_objfile_getc(sState,&cData);
						sscanf(cData,"%d",&nValue);
						/* Pass Letters */
						c = '0' ;
						while ( isdigit(c) || c=='.' ) {
							c = simple_objfile_getc(sState,&cData);
						}
						cData-- ;
						simple_list_addint_gc(sState,list,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Number %d \n  ",nValue ) ;
						#endif
						break ;
					case 'D' :
						c = simple_objfile_getc(sState,&cData);
						sscanf(cData,"%lf",&dValue);
						/* Pass Letters */
						c = '0' ;
						while ( isdigit(c) || c=='.' ) {
							c = simple_objfile_getc(sState,&cData);
						}
						cData-- ;
						simple_list_adddouble_gc(sState,list,dValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Double %d  \n",dValue ) ;
						#endif
						break ;
					case 'P' :
						simple_list_addpointer_gc(sState,list,NULL);
						/* Read Line */
						while ( c != '\n' ) {
							c = simple_objfile_getc(sState,&cData);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read Pointer ");
						#endif
						break ;
					case 'T' :
						simple_list_addpointer_gc(sState,listStack,list);
						list = simple_list_newlist_gc(sState,list);
						/* Read Line */
						while ( c != '\n' ) {
							c = simple_objfile_getc(sState,&cData);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read T ");
						#endif
						break ;
					case 'E' :
						list = (List *) simple_list_getpointer(listStack,simple_list_getsize(listStack)) ;
						simple_list_deletelastitem(listStack);
						/* Read Line */
						while ( c != '\n' ) {
							c = simple_objfile_getc(sState,&cData);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read E ");
						#endif
						break ;
					case 'L' :
						/* Read Until { */
						while ( c != '{' ) {
							c = simple_objfile_getc(sState,&cData);
						}
						simple_list_addpointer_gc(sState,listStack,list);
						list = simple_list_newlist_gc(sState,list);
						nBraceEnd++ ;
						#ifdef DEBUG_OBJFILE
						puts("Read L ");
						#endif
						break ;
				}
				break ;
			case '}' :
				if ( nBraceEnd ) {
					list = (List *) simple_list_getpointer(listStack,simple_list_getsize(listStack)) ;
					simple_list_deletelastitem(listStack);
					nBraceEnd-- ;
					#ifdef DEBUG_OBJFILE
					puts("Read } ");
					#endif
				}
				break ;
		}
		c = simple_objfile_getc(sState,&cData);
	}
	return 1 ;
}

void simple_objfile_updateclassespointers ( SimpleState *sState )
{
	int x,x2,x3,x4,lFound  ;
	List *list, *list2, *list3  ;
	const char *cString  ;
	char cModulesName[400]  ;
	char cClassName[400]  ;
	/* Update Class Pointer in Code */
	lFound = 0 ;
	for ( x = 1 ; x <= simple_list_getsize(sState->pSimpleGenCode) ; x++ ) {
		list = simple_list_getlist(sState->pSimpleGenCode,x);
		if ( simple_list_getint(list,1) == ICO_NEWCLASS ) {
			cString = simple_list_getstring(list,2);
			for ( x2 = 1 ; x2 <= simple_list_getsize(sState->classes_map) ; x2++ ) {
				list2 = simple_list_getlist(sState->classes_map,x2);
				if ( strcmp(cString,simple_list_getstring(list2,1)) == 0 ) {
					lFound = 0 ;
					simple_list_setpointer_gc(sState,list,3,list2);
					#ifdef DEBUG_OBJFILE
					puts("Pointer Updated ");
					#endif
					break ;
				}
			}
			/* If we can't find the list (the class is inside a modules) */
			if ( lFound == 0 ) {
				simple_list_setpointer_gc(sState,list,3,NULL);
			}
		}
	}
	/*
	**  Update Class Pointers in Classes Map when the class belong to a Modules 
	**  This updates works when the class name is : modulesname.classname 
	*/
	for ( x = 1 ; x <= simple_list_getsize(sState->classes_map) ; x++ ) {
		list = simple_list_getlist(sState->classes_map,x);
		cString = simple_list_getstring(list,1);
		if ( simple_list_getstringsize(list,1)  > 400 ) {
			/* Avoid large names - we have limits (400 letters per modules name - 400 letters for class name) */
			continue ;
		}
		for ( x2 = simple_list_getstringsize(list,1) - 1 ; x2 >= 0 ; x2-- ) {
			if ( cString[x2] == '.' ) {
				/*
				**  Now we have a class name stored as modulesname.classname 
				**  Get Modules Name 
				*/
				for ( x3 = 0 ; x3 < x2 ; x3++ ) {
					cModulesName[x3] = cString[x3] ;
				}
				cModulesName[x2] = '\0' ;
				#ifdef DEBUG_OBJFILE
				printf( "Modules Name %s \n  ",cModulesName ) ;
				#endif
				/* Get Class Name */
				for ( x3 = x2+1 ; x3 <= simple_list_getstringsize(list,1) - 1 ; x3++ ) {
					cClassName[x3-x2-1] = cString[x3] ;
				}
				cClassName[simple_list_getstringsize(list,1) - 1 - x2] = '\0' ;
				#ifdef DEBUG_OBJFILE
				printf( "Class Name %s \n  ",cClassName ) ;
				#endif
				/* Get The Modules List */
				for ( x3 = 1 ; x3 <= simple_list_getsize(sState->modules_map) ; x3++ ) {
					list2 = simple_list_getlist(sState->modules_map,x3);
					if ( strcmp(simple_list_getstring(list2,1),cModulesName) == 0 ) {
						/* Get The Class List */
						list2 = simple_list_getlist(list2,2);
						for ( x4 = 1 ; x4 <= simple_list_getsize(list2) ; x4++ ) {
							list3 = simple_list_getlist(list2,x4);
							if ( strcmp(simple_list_getstring(list3,1),cClassName) == 0 ) {
								/* Now We have the Class - Update Pointer */
								simple_list_setpointer_gc(sState,list,2,(void *) list3);
								break ;
							}
						}
						break ;
					}
				}
			}
		}
	}
	/* Update Modules Pointers in Moduless Classes */
	for ( x = 1 ; x <= simple_list_getsize(sState->modules_map) ; x++ ) {
		list = simple_list_getlist(sState->modules_map,x);
		/* Get The Class List */
		list2 = simple_list_getlist(list,2);
		for ( x2 = 1 ; x2 <= simple_list_getsize(list2) ; x2++ ) {
			list3 = simple_list_getlist(list2,x2);
			simple_list_setpointer_gc(sState,list3,SIMPLE_CLASSMAP_POINTERTOMODULE,list);
		}
	}
}

void simple_objfile_xorstring ( char *cString,int nStringSize,char *cKey,int nKeySize )
{
	int x  ;
	for ( x = 1 ; x <= nStringSize ; x++ ) {
		cString[x-1] = cString[x-1] ^ cKey[(x-1)%nKeySize] ;
	}
}

void simple_objfile_readc ( SimpleState *sState,char **cSource,char *cDest,int nCount )
{
	int x  ;
	char *cData  ;
	cData = *cSource ;
	for ( x = 0 ; x < nCount ; x++ ) {
		cDest[x] = cData[x] ;
	}
	*cSource += nCount ;
	cDest[nCount] = '\0' ;
}

char simple_objfile_getc ( SimpleState *sState,char **cSource )
{
	char c  ;
	char *cData  ;
	cData = *cSource ;
	c = cData[0] ;
	*cSource+=1 ;
	return c ;
}
