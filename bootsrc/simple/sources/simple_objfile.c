/*
**  Copyright (c) 2013-2017 Mahmoud Fayed <msfclipper@yahoo.com> 
**  Include Files 
*/
#include "../includes/simple.h"
/* Define Functions */

void simple_objfile_writefile ( RingState *pRingState )
{
	FILE *fObj;
	char cFileName[400]  ;
	/* Create File */
	sprintf( cFileName , "%so" , simple_list_getstring(pRingState->pRingFilesList,1) ) ;
	fObj = fopen(cFileName , "w+b" );
	fprintf( fObj , "# Ring Object File\n"  ) ;
	fprintf( fObj , "# Version 1.1\n"  ) ;
	/* Write Functions Lists */
	fprintf( fObj , "# Functions List\n"  ) ;
	simple_objfile_writelist(pRingState->pRingFunctionsMap,fObj);
	/* Write Classes List */
	fprintf( fObj , "# Classes List\n"  ) ;
	simple_objfile_writelist(pRingState->pRingClassesMap,fObj);
	/* Write Packages */
	fprintf( fObj , "# Packages List\n"  ) ;
	simple_objfile_writelist(pRingState->pRingPackagesMap,fObj);
	/* Write Code */
	fprintf( fObj , "# Program Code\n"  ) ;
	simple_objfile_writelist(pRingState->pRingGenCode,fObj);
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

int simple_objfile_readfile ( RingState *pRingState,char *cFileName )
{
	return simple_objfile_readfromsource(pRingState,cFileName,SIMPLE_OBJFILE_READFROMFILE) ;
}

int simple_objfile_readstring ( RingState *pRingState,char *cString )
{
	return simple_objfile_readfromsource(pRingState,cString,SIMPLE_OBJFILE_READFROMSTSIMPLE) ;
}

int simple_objfile_readfromsource ( RingState *pRingState,char *cSource,int nSource )
{
	List *pListFunctions, *pListClasses, *pListPackages, *pListCode, *pListStack  ;
	/* Create Lists */
	pListFunctions = simple_list_new_gc(pRingState,0);
	pListClasses = simple_list_new_gc(pRingState,0);
	pListPackages = simple_list_new_gc(pRingState,0);
	pListCode = simple_list_new_gc(pRingState,0);
	pListStack = simple_list_new_gc(pRingState,0);
	/* Process Content (File or String) */
	if ( nSource == SIMPLE_OBJFILE_READFROMFILE ) {
		if ( ! simple_objfile_processfile(pRingState,cSource,pListFunctions, pListClasses, pListPackages, pListCode, pListStack) ) {
			return 0 ;
		}
	}
	else if ( nSource ==SIMPLE_OBJFILE_READFROMSTSIMPLE ) {
		if ( ! simple_objfile_processstring(pRingState,cSource,pListFunctions, pListClasses, pListPackages, pListCode, pListStack) ) {
			return 0 ;
		}
	}
	simple_list_delete(pListStack);
	/* Update Ring State */
	#ifdef DEBUG_OBJFILE
	puts("Old Code List ");
	simple_list_print(pRingState->pRingGenCode);
	#endif
	/* Update Lists */
	pRingState->pRingFunctionsMap = pListFunctions ;
	pRingState->pRingClassesMap = pListClasses ;
	pRingState->pRingPackagesMap = pListPackages ;
	pRingState->pRingGenCode = pListCode ;
	#ifdef DEBUG_OBJFILE
	puts("Update Done! ");
	puts("New Code List ");
	simple_list_print(pRingState->pRingGenCode);
	#endif
	/* Update Classes Pointers */
	simple_objfile_updateclassespointers(pRingState);
	return 1 ;
}

int simple_objfile_processfile ( RingState *pRingState,char *cFileName,List *pListFunctions,List  *pListClasses,List  *pListPackages,List  *pListCode,List  *pListStack )
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
	/* Set Active List (1=functions 2=classes 3=packages 4=code) */
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
	if ( strcmp(cFileType,"# Ring Object File") != 0 ) {
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
						pList = pListPackages ;
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
						cString = (char *) simple_state_malloc(pRingState,nValue+1);
						fread( cString , 1 , nValue , fObj );
						cString[nValue] = '\0' ;
						/* Decrypt String */
						simple_objfile_xorstring(cString,nValue,cKey,10);
						simple_list_addstring2_gc(pRingState,pList,cString,nValue);
						simple_state_free(pRingState,cString);
						#ifdef DEBUG_OBJFILE
						printf( "Read String %s Size %d \n",cString,nValue ) ;
						#endif
						break ;
					case 'I' :
						c = getc(fObj);
						fscanf( fObj , "%d" , &nValue ) ;
						simple_list_addint_gc(pRingState,pList,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Number %d \n  ",nValue ) ;
						#endif
						break ;
					case 'D' :
						c = getc(fObj);
						fscanf( fObj , "%lf" , &dValue ) ;
						simple_list_adddouble_gc(pRingState,pList,dValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Double %d  \n",dValue ) ;
						#endif
						break ;
					case 'P' :
						simple_list_addpointer_gc(pRingState,pList,NULL);
						/* Read Line */
						while ( c != '\n' ) {
							c = getc(fObj);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read Pointer ");
						#endif
						break ;
					case 'T' :
						simple_list_addpointer_gc(pRingState,pListStack,pList);
						pList = simple_list_newlist_gc(pRingState,pList);
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
						simple_list_addpointer_gc(pRingState,pListStack,pList);
						pList = simple_list_newlist_gc(pRingState,pList);
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

int simple_objfile_processstring ( RingState *pRingState,char *cContent,List *pListFunctions,List  *pListClasses,List  *pListPackages,List  *pListCode,List  *pListStack )
{
	signed char c  ;
	int nActiveList,nValue,nBraceEnd  ;
	double dValue  ;
	char *cString, *cData  ;
	char cKey[11]  ;
	char cFileType[100]  ;
	strcpy(cKey,"ringstring");
	List *pList  ;
	/* Set Active List (1=functions 2=classes 3=packages 4=code) */
	nActiveList = 0 ;
	nBraceEnd = 0 ;
	pList = NULL ;
	cData = cContent ;
	/* Check Type and Version */
	simple_objfile_readc(pRingState,&cData,cFileType,18);
	cFileType[18] = '\0' ;
	if ( strcmp(cFileType,"# Ring Object File") != 0 ) {
		printf( "The file type is not correct - the VM expect a ring object file\n" ) ;
		return 0 ;
	}
	c = simple_objfile_getc(pRingState,&cData);
	simple_objfile_readc(pRingState,&cData,cFileType,13);
	cFileType[13] = '\0' ;
	if ( strcmp(cFileType,"# Version 1.1") != 0 ) {
		printf( "The file version is not correct - the VM expect a ring object file version 1.1\n" ) ;
		return 0 ;
	}
	/* Process Content */
	c = simple_objfile_getc(pRingState,&cData);
	while ( c != EOF ) {
		/* Check Char */
		switch ( c ) {
			case '#' :
				/* Read Line */
				while ( c != '\n' ) {
					c = simple_objfile_getc(pRingState,&cData);
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
						pList = pListPackages ;
						break ;
					case 4 :
						pList = pListCode ;
						break ;
				}
				break ;
			case '[' :
				c = simple_objfile_getc(pRingState,&cData);
				switch ( c ) {
					case 'S' :
						c = simple_objfile_getc(pRingState,&cData);
						sscanf(cData,"[%d]",&nValue);
						/* Pass Letters */
						c = ' ' ;
						while ( c != ']' ) {
							c = simple_objfile_getc(pRingState,&cData);
						}
						cString = (char *) simple_state_malloc(pRingState,nValue+1);
						simple_objfile_readc(pRingState,&cData,cString,nValue);
						cString[nValue] = '\0' ;
						/* Decrypt String */
						simple_objfile_xorstring(cString,nValue,cKey,10);
						simple_list_addstring2_gc(pRingState,pList,cString,nValue);
						simple_state_free(pRingState,cString);
						#ifdef DEBUG_OBJFILE
						printf( "Read String %s Size %d \n",cString,nValue ) ;
						#endif
						break ;
					case 'I' :
						c = simple_objfile_getc(pRingState,&cData);
						sscanf(cData,"%d",&nValue);
						/* Pass Letters */
						c = '0' ;
						while ( isdigit(c) || c=='.' ) {
							c = simple_objfile_getc(pRingState,&cData);
						}
						cData-- ;
						simple_list_addint_gc(pRingState,pList,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Number %d \n  ",nValue ) ;
						#endif
						break ;
					case 'D' :
						c = simple_objfile_getc(pRingState,&cData);
						sscanf(cData,"%lf",&dValue);
						/* Pass Letters */
						c = '0' ;
						while ( isdigit(c) || c=='.' ) {
							c = simple_objfile_getc(pRingState,&cData);
						}
						cData-- ;
						simple_list_adddouble_gc(pRingState,pList,dValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Double %d  \n",dValue ) ;
						#endif
						break ;
					case 'P' :
						simple_list_addpointer_gc(pRingState,pList,NULL);
						/* Read Line */
						while ( c != '\n' ) {
							c = simple_objfile_getc(pRingState,&cData);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read Pointer ");
						#endif
						break ;
					case 'T' :
						simple_list_addpointer_gc(pRingState,pListStack,pList);
						pList = simple_list_newlist_gc(pRingState,pList);
						/* Read Line */
						while ( c != '\n' ) {
							c = simple_objfile_getc(pRingState,&cData);
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
							c = simple_objfile_getc(pRingState,&cData);
						}
						#ifdef DEBUG_OBJFILE
						puts("Read E ");
						#endif
						break ;
					case 'L' :
						/* Read Until { */
						while ( c != '{' ) {
							c = simple_objfile_getc(pRingState,&cData);
						}
						simple_list_addpointer_gc(pRingState,pListStack,pList);
						pList = simple_list_newlist_gc(pRingState,pList);
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
		c = simple_objfile_getc(pRingState,&cData);
	}
	return 1 ;
}

void simple_objfile_updateclassespointers ( RingState *pRingState )
{
	int x,x2,x3,x4,lFound  ;
	List *pList, *pList2, *pList3  ;
	const char *cString  ;
	char cPackageName[400]  ;
	char cClassName[400]  ;
	/* Update Class Pointer in Code */
	lFound = 0 ;
	for ( x = 1 ; x <= simple_list_getsize(pRingState->pRingGenCode) ; x++ ) {
		pList = simple_list_getlist(pRingState->pRingGenCode,x);
		if ( simple_list_getint(pList,1) == ICO_NEWCLASS ) {
			cString = simple_list_getstring(pList,2);
			for ( x2 = 1 ; x2 <= simple_list_getsize(pRingState->pRingClassesMap) ; x2++ ) {
				pList2 = simple_list_getlist(pRingState->pRingClassesMap,x2);
				if ( strcmp(cString,simple_list_getstring(pList2,1)) == 0 ) {
					lFound = 0 ;
					simple_list_setpointer_gc(pRingState,pList,3,pList2);
					#ifdef DEBUG_OBJFILE
					puts("Pointer Updated ");
					#endif
					break ;
				}
			}
			/* If we can't find the list (the class is inside a package) */
			if ( lFound == 0 ) {
				simple_list_setpointer_gc(pRingState,pList,3,NULL);
			}
		}
	}
	/*
	**  Update Class Pointers in Classes Map when the class belong to a Package 
	**  This updates works when the class name is : packagename.classname 
	*/
	for ( x = 1 ; x <= simple_list_getsize(pRingState->pRingClassesMap) ; x++ ) {
		pList = simple_list_getlist(pRingState->pRingClassesMap,x);
		cString = simple_list_getstring(pList,1);
		if ( simple_list_getstringsize(pList,1)  > 400 ) {
			/* Avoid large names - we have limits (400 letters per package name - 400 letters for class name) */
			continue ;
		}
		for ( x2 = simple_list_getstringsize(pList,1) - 1 ; x2 >= 0 ; x2-- ) {
			if ( cString[x2] == '.' ) {
				/*
				**  Now we have a class name stored as packagename.classname 
				**  Get Package Name 
				*/
				for ( x3 = 0 ; x3 < x2 ; x3++ ) {
					cPackageName[x3] = cString[x3] ;
				}
				cPackageName[x2] = '\0' ;
				#ifdef DEBUG_OBJFILE
				printf( "Package Name %s \n  ",cPackageName ) ;
				#endif
				/* Get Class Name */
				for ( x3 = x2+1 ; x3 <= simple_list_getstringsize(pList,1) - 1 ; x3++ ) {
					cClassName[x3-x2-1] = cString[x3] ;
				}
				cClassName[simple_list_getstringsize(pList,1) - 1 - x2] = '\0' ;
				#ifdef DEBUG_OBJFILE
				printf( "Class Name %s \n  ",cClassName ) ;
				#endif
				/* Get The Package List */
				for ( x3 = 1 ; x3 <= simple_list_getsize(pRingState->pRingPackagesMap) ; x3++ ) {
					pList2 = simple_list_getlist(pRingState->pRingPackagesMap,x3);
					if ( strcmp(simple_list_getstring(pList2,1),cPackageName) == 0 ) {
						/* Get The Class List */
						pList2 = simple_list_getlist(pList2,2);
						for ( x4 = 1 ; x4 <= simple_list_getsize(pList2) ; x4++ ) {
							pList3 = simple_list_getlist(pList2,x4);
							if ( strcmp(simple_list_getstring(pList3,1),cClassName) == 0 ) {
								/* Now We have the Class - Update Pointer */
								simple_list_setpointer_gc(pRingState,pList,2,(void *) pList3);
								break ;
							}
						}
						break ;
					}
				}
			}
		}
	}
	/* Update Package Pointers in Packages Classes */
	for ( x = 1 ; x <= simple_list_getsize(pRingState->pRingPackagesMap) ; x++ ) {
		pList = simple_list_getlist(pRingState->pRingPackagesMap,x);
		/* Get The Class List */
		pList2 = simple_list_getlist(pList,2);
		for ( x2 = 1 ; x2 <= simple_list_getsize(pList2) ; x2++ ) {
			pList3 = simple_list_getlist(pList2,x2);
			simple_list_setpointer_gc(pRingState,pList3,SIMPLE_CLASSMAP_POINTERTOPACKAGE,pList);
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

void simple_objfile_readc ( RingState *pRingState,char **cSource,char *cDest,int nCount )
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

char simple_objfile_getc ( RingState *pRingState,char **cSource )
{
	char c  ;
	char *cData  ;
	cData = *cSource ;
	c = cData[0] ;
	*cSource+=1 ;
	return c ;
}
