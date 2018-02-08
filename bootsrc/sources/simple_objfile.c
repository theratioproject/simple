
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

void simple_objfile_writefile ( SimpleState *state )
{
	FILE *fObj;
	char cFileName[400]  ;
	/* Create File */
	sprintf( cFileName , "%splex" , simple_list_getstring(state->pSimpleFilesList,1) ) ;
        //printf("TO COMPLEX : %s", change_file_ext(simple_list_getstring(state->pSimpleFilesList,1), "complex"));
	fObj = fopen(cFileName , "w+b" );
	fprintf( fObj , "# Simple Object File\n"  ) ;
	fprintf( fObj , "# Version 1.1\n"  ) ;
	/* Write Functions Lists */
	fprintf( fObj , "# Functions List\n"  ) ;
	simple_objfile_writelist(state->pSimpleFunctionsMap,fObj);
	/* Write Classes List */
	fprintf( fObj , "# Classes List\n"  ) ;
	simple_objfile_writelist(state->pSimpleClassesMap,fObj);
	/* Write Moduless */
	fprintf( fObj , "# Moduless List\n"  ) ;
	simple_objfile_writelist(state->pSimpleModulessMap,fObj);
	/* Write Code */
	fprintf( fObj , "# Program Code\n"  ) ;
	simple_objfile_writelist(state->pSimpleGenCode,fObj);
	/* Close File */
	fprintf( fObj , "# End of File\n"  ) ;
	fclose( fObj ) ;
}

void simple_objfile_writelist ( List *pList,FILE *fObj )
{
	List *pList2  ;
	int x,x2  ;
	char *cString  ;
	char cKey[11]  ;
	strcpy(cKey,"ringstring");
	fprintf( fObj , "{\n"  ) ;
	/* Write List Items */
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		pList2 = simple_list_getlist(pList,x);
		fprintf( fObj , "[T]\n"  ) ;
		for ( x2 = 1 ; x2 <= simple_list_getsize(pList2) ; x2++ ) {
			if ( simple_list_isstring(pList2,x2) ) {
				fprintf( fObj , "[S][%d]" , simple_list_getstringsize(pList2,x2) ) ;
				/* Encrypt String */
				cString = simple_list_getstring(pList2,x2) ;
				simple_objfile_xorstring(cString,simple_list_getstringsize(pList2,x2),cKey,10);
				fwrite( simple_list_getstring(pList2,x2) , 1 , simple_list_getstringsize(pList2,x2) , fObj );
				/* Decrypt String */
				simple_objfile_xorstring(cString,simple_list_getstringsize(pList2,x2),cKey,10);
				fprintf( fObj , "\n"  ) ;
			}
			else if ( simple_list_isint(pList2,x2) ) {
				fprintf( fObj , "[I]%d\n" , simple_list_getint(pList2,x2) ) ;
			}
			else if ( simple_list_isdouble(pList2,x2) ) {
				fprintf( fObj , "[D]%f\n" , simple_list_getdouble(pList2,x2) ) ;
			}
			else if ( simple_list_ispointer(pList2,x2) ) {
				fprintf( fObj , "[P]%p\n" , (void *) simple_list_getpointer(pList2,x2) ) ;
			}
			else if ( simple_list_islist(pList2,x2) ) {
				fprintf( fObj , "[L]\n"  ) ;
				simple_objfile_writelist(simple_list_getlist(pList2,x2) ,fObj);
			}
		}
		fprintf( fObj , "[E]\n"  ) ;
	}
	fprintf( fObj , "}\n"  ) ;
}

int simple_objfile_readfile ( SimpleState *state,char *cFileName )
{
	return simple_objfile_readfromsource(state,cFileName,SIMPLE_OBJFILE_READFROMFILE) ;
}

int simple_objfile_readstring ( SimpleState *state,char *cString )
{
	return simple_objfile_readfromsource(state,cString,SIMPLE_OBJFILE_READFROMSTRING) ;
}

int simple_objfile_readfromsource ( SimpleState *state,char *cSource,int nSource )
{
	List *pListFunctions, *pListClasses, *pListModuless, *pListCode, *pListStack  ;
	/* Create Lists */
	pListFunctions = simple_list_new_gc(state,0);
	pListClasses = simple_list_new_gc(state,0);
	pListModuless = simple_list_new_gc(state,0);
	pListCode = simple_list_new_gc(state,0);
	pListStack = simple_list_new_gc(state,0);
	/* Process Content (File or String) */
	if ( nSource == SIMPLE_OBJFILE_READFROMFILE ) {
		if ( ! simple_objfile_processfile(state,cSource,pListFunctions, pListClasses, pListModuless, pListCode, pListStack) ) {
			return 0 ;
		}
	}
	else if ( nSource ==SIMPLE_OBJFILE_READFROMSTRING ) {
		if ( ! simple_objfile_processstring(state,cSource,pListFunctions, pListClasses, pListModuless, pListCode, pListStack) ) {
			return 0 ;
		}
	}
	simple_list_delete(pListStack);
	/* Update Simple State */
	#ifdef DEBUG_OBJFILE
	puts("Old Code List ");
	simple_list_print(state->pSimpleGenCode);
	#endif
	/* Update Lists */
	state->pSimpleFunctionsMap = pListFunctions ;
	state->pSimpleClassesMap = pListClasses ;
	state->pSimpleModulessMap = pListModuless ;
	state->pSimpleGenCode = pListCode ;
	#ifdef DEBUG_OBJFILE
	puts("Update Done! ");
	puts("New Code List ");
	simple_list_print(state->pSimpleGenCode);
	#endif
	/* Update Classes Pointers */
	simple_objfile_updateclassespointers(state);
	return 1 ;
}

int simple_objfile_processfile ( SimpleState *state,char *cFileName,List *pListFunctions,List  *pListClasses,List  *pListModuless,List  *pListCode,List  *pListStack )
{
	FILE *fObj;
	signed char c  ;
	int nActiveList,nValue,nBraceEnd  ;
	double dValue  ;
	char *cString  ;
	char cKey[11]  ;
	char cFileType[100]  ;
	strcpy(cKey,"ringstring");
	List *pList  ;
	/* Set Active List (1=functions 2=classes 3=moduless 4=code) */
	nActiveList = 0 ;
	nBraceEnd = 0 ;
	pList = NULL ;
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
						pList = pListFunctions ;
						break ;
					case 2 :
						pList = pListClasses ;
						break ;
					case 3 :
						pList = pListModuless ;
						break ;
					case 4 :
						pList = pListCode ;
						break ;
				}
				break ;
			case '[' :
				c = getc(fObj);
				switch ( c ) {
					case 'S' :
						c = getc(fObj);
						fscanf( fObj , "[%d]" , &nValue ) ;
						cString = (char *) simple_state_malloc(state,nValue+1);
						fread( cString , 1 , nValue , fObj );
						cString[nValue] = '\0' ;
						/* Decrypt String */
						simple_objfile_xorstring(cString,nValue,cKey,10);
						simple_list_addstring2_gc(state,pList,cString,nValue);
						simple_state_free(state,cString);
						#ifdef DEBUG_OBJFILE
						printf( "Read String %s Size %d \n",cString,nValue ) ;
						#endif
						break ;
					case 'I' :
						c = getc(fObj);
						fscanf( fObj , "%d" , &nValue ) ;
						simple_list_addint_gc(state,pList,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Number %d \n  ",nValue ) ;
						#endif
						break ;
					case 'D' :
						c = getc(fObj);
						fscanf( fObj , "%lf" , &dValue ) ;
						simple_list_adddouble_gc(state,pList,dValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Double %d  \n",dValue ) ;
						#endif
						break ;
					case 'P' :
						simple_list_addpointer_gc(state,pList,NULL);
						/* Read Line */
						while ( c != '\n' ) {
							c = getc(fObj);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read Pointer ");
						#endif
						break ;
					case 'T' :
						simple_list_addpointer_gc(state,pListStack,pList);
						pList = simple_list_newlist_gc(state,pList);
						/* Read Line */
						while ( c != '\n' ) {
							c = getc(fObj);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read T ");
						#endif
						break ;
					case 'E' :
						pList = (List *) simple_list_getpointer(pListStack,simple_list_getsize(pListStack)) ;
						simple_list_deletelastitem(pListStack);
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
						simple_list_addpointer_gc(state,pListStack,pList);
						pList = simple_list_newlist_gc(state,pList);
						nBraceEnd++ ;
						#ifdef DEBUG_OBJFILE
						puts("Read L ");
						#endif
						break ;
				}
				break ;
			case '}' :
				if ( nBraceEnd ) {
					pList = (List *) simple_list_getpointer(pListStack,simple_list_getsize(pListStack)) ;
					simple_list_deletelastitem(pListStack);
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

int simple_objfile_processstring ( SimpleState *state,char *cContent,List *pListFunctions,List  *pListClasses,List  *pListModuless,List  *pListCode,List  *pListStack )
{
	signed char c  ;
	int nActiveList,nValue,nBraceEnd  ;
	double dValue  ;
	char *cString, *cData  ;
	char cKey[11]  ;
	char cFileType[100]  ;
	strcpy(cKey,"ringstring");
	List *pList  ;
	/* Set Active List (1=functions 2=classes 3=moduless 4=code) */
	nActiveList = 0 ;
	nBraceEnd = 0 ;
	pList = NULL ;
	cData = cContent ;
	/* Check Type and Version */
	simple_objfile_readc(state,&cData,cFileType,18);
	cFileType[18] = '\0' ;
	if ( strcmp(cFileType,"# Simple Object File") != 0 ) {
		printf( "The file type is not correct - the VM expect a ring object file\n" ) ;
		return 0 ;
	}
	c = simple_objfile_getc(state,&cData);
	simple_objfile_readc(state,&cData,cFileType,13);
	cFileType[13] = '\0' ;
	if ( strcmp(cFileType,"# Version 1.1") != 0 ) {
		printf( "The file version is not correct - the VM expect a ring object file version 1.1\n" ) ;
		return 0 ;
	}
	/* Process Content */
	c = simple_objfile_getc(state,&cData);
	while ( c != EOF ) {
		/* Check Char */
		switch ( c ) {
			case '#' :
				/* Read Line */
				while ( c != '\n' ) {
					c = simple_objfile_getc(state,&cData);
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
						pList = pListFunctions ;
						break ;
					case 2 :
						pList = pListClasses ;
						break ;
					case 3 :
						pList = pListModuless ;
						break ;
					case 4 :
						pList = pListCode ;
						break ;
				}
				break ;
			case '[' :
				c = simple_objfile_getc(state,&cData);
				switch ( c ) {
					case 'S' :
						c = simple_objfile_getc(state,&cData);
						sscanf(cData,"[%d]",&nValue);
						/* Pass Letters */
						c = ' ' ;
						while ( c != ']' ) {
							c = simple_objfile_getc(state,&cData);
						}
						cString = (char *) simple_state_malloc(state,nValue+1);
						simple_objfile_readc(state,&cData,cString,nValue);
						cString[nValue] = '\0' ;
						/* Decrypt String */
						simple_objfile_xorstring(cString,nValue,cKey,10);
						simple_list_addstring2_gc(state,pList,cString,nValue);
						simple_state_free(state,cString);
						#ifdef DEBUG_OBJFILE
						printf( "Read String %s Size %d \n",cString,nValue ) ;
						#endif
						break ;
					case 'I' :
						c = simple_objfile_getc(state,&cData);
						sscanf(cData,"%d",&nValue);
						/* Pass Letters */
						c = '0' ;
						while ( isdigit(c) || c=='.' ) {
							c = simple_objfile_getc(state,&cData);
						}
						cData-- ;
						simple_list_addint_gc(state,pList,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Number %d \n  ",nValue ) ;
						#endif
						break ;
					case 'D' :
						c = simple_objfile_getc(state,&cData);
						sscanf(cData,"%lf",&dValue);
						/* Pass Letters */
						c = '0' ;
						while ( isdigit(c) || c=='.' ) {
							c = simple_objfile_getc(state,&cData);
						}
						cData-- ;
						simple_list_adddouble_gc(state,pList,dValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Double %d  \n",dValue ) ;
						#endif
						break ;
					case 'P' :
						simple_list_addpointer_gc(state,pList,NULL);
						/* Read Line */
						while ( c != '\n' ) {
							c = simple_objfile_getc(state,&cData);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read Pointer ");
						#endif
						break ;
					case 'T' :
						simple_list_addpointer_gc(state,pListStack,pList);
						pList = simple_list_newlist_gc(state,pList);
						/* Read Line */
						while ( c != '\n' ) {
							c = simple_objfile_getc(state,&cData);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read T ");
						#endif
						break ;
					case 'E' :
						pList = (List *) simple_list_getpointer(pListStack,simple_list_getsize(pListStack)) ;
						simple_list_deletelastitem(pListStack);
						/* Read Line */
						while ( c != '\n' ) {
							c = simple_objfile_getc(state,&cData);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read E ");
						#endif
						break ;
					case 'L' :
						/* Read Until { */
						while ( c != '{' ) {
							c = simple_objfile_getc(state,&cData);
						}
						simple_list_addpointer_gc(state,pListStack,pList);
						pList = simple_list_newlist_gc(state,pList);
						nBraceEnd++ ;
						#ifdef DEBUG_OBJFILE
						puts("Read L ");
						#endif
						break ;
				}
				break ;
			case '}' :
				if ( nBraceEnd ) {
					pList = (List *) simple_list_getpointer(pListStack,simple_list_getsize(pListStack)) ;
					simple_list_deletelastitem(pListStack);
					nBraceEnd-- ;
					#ifdef DEBUG_OBJFILE
					puts("Read } ");
					#endif
				}
				break ;
		}
		c = simple_objfile_getc(state,&cData);
	}
	return 1 ;
}

void simple_objfile_updateclassespointers ( SimpleState *state )
{
	int x,x2,x3,x4,lFound  ;
	List *pList, *pList2, *pList3  ;
	const char *cString  ;
	char cModulesName[400]  ;
	char cClassName[400]  ;
	/* Update Class Pointer in Code */
	lFound = 0 ;
	for ( x = 1 ; x <= simple_list_getsize(state->pSimpleGenCode) ; x++ ) {
		pList = simple_list_getlist(state->pSimpleGenCode,x);
		if ( simple_list_getint(pList,1) == ICO_NEWCLASS ) {
			cString = simple_list_getstring(pList,2);
			for ( x2 = 1 ; x2 <= simple_list_getsize(state->pSimpleClassesMap) ; x2++ ) {
				pList2 = simple_list_getlist(state->pSimpleClassesMap,x2);
				if ( strcmp(cString,simple_list_getstring(pList2,1)) == 0 ) {
					lFound = 0 ;
					simple_list_setpointer_gc(state,pList,3,pList2);
					#ifdef DEBUG_OBJFILE
					puts("Pointer Updated ");
					#endif
					break ;
				}
			}
			/* If we can't find the list (the class is inside a modules) */
			if ( lFound == 0 ) {
				simple_list_setpointer_gc(state,pList,3,NULL);
			}
		}
	}
	/*
	**  Update Class Pointers in Classes Map when the class belong to a Modules 
	**  This updates works when the class name is : modulesname.classname 
	*/
	for ( x = 1 ; x <= simple_list_getsize(state->pSimpleClassesMap) ; x++ ) {
		pList = simple_list_getlist(state->pSimpleClassesMap,x);
		cString = simple_list_getstring(pList,1);
		if ( simple_list_getstringsize(pList,1)  > 400 ) {
			/* Avoid large names - we have limits (400 letters per modules name - 400 letters for class name) */
			continue ;
		}
		for ( x2 = simple_list_getstringsize(pList,1) - 1 ; x2 >= 0 ; x2-- ) {
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
				for ( x3 = x2+1 ; x3 <= simple_list_getstringsize(pList,1) - 1 ; x3++ ) {
					cClassName[x3-x2-1] = cString[x3] ;
				}
				cClassName[simple_list_getstringsize(pList,1) - 1 - x2] = '\0' ;
				#ifdef DEBUG_OBJFILE
				printf( "Class Name %s \n  ",cClassName ) ;
				#endif
				/* Get The Modules List */
				for ( x3 = 1 ; x3 <= simple_list_getsize(state->pSimpleModulessMap) ; x3++ ) {
					pList2 = simple_list_getlist(state->pSimpleModulessMap,x3);
					if ( strcmp(simple_list_getstring(pList2,1),cModulesName) == 0 ) {
						/* Get The Class List */
						pList2 = simple_list_getlist(pList2,2);
						for ( x4 = 1 ; x4 <= simple_list_getsize(pList2) ; x4++ ) {
							pList3 = simple_list_getlist(pList2,x4);
							if ( strcmp(simple_list_getstring(pList3,1),cClassName) == 0 ) {
								/* Now We have the Class - Update Pointer */
								simple_list_setpointer_gc(state,pList,2,(void *) pList3);
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
	for ( x = 1 ; x <= simple_list_getsize(state->pSimpleModulessMap) ; x++ ) {
		pList = simple_list_getlist(state->pSimpleModulessMap,x);
		/* Get The Class List */
		pList2 = simple_list_getlist(pList,2);
		for ( x2 = 1 ; x2 <= simple_list_getsize(pList2) ; x2++ ) {
			pList3 = simple_list_getlist(pList2,x2);
			simple_list_setpointer_gc(state,pList3,SIMPLE_CLASSMAP_POINTERTOMODULE,pList);
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

void simple_objfile_readc ( SimpleState *state,char **cSource,char *cDest,int nCount )
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

char simple_objfile_getc ( SimpleState *state,char **cSource )
{
	char c  ;
	char *cData  ;
	cData = *cSource ;
	c = cData[0] ;
	*cSource+=1 ;
	return c ;
}
