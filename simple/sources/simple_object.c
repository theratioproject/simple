
/* 
	Copyright (c) 2018 Azeez Adewale <azeezadewale98@gmail.com> 
	MIT License Copyright (c) 2017 simple 

*/

/* 
 * File:   simple_object.c
 * Author: Azeez Adewale
 *
 * Created on January 11, 2019, 10:45 AM
 */


#include "../include/simple.h"

void simple_object_writefile ( SimpleState *sState )
{
	FILE *fp;
	char file_name[400];
	/* Create File */
	remove_file_ext(file_name,sState->main_file_path);
	sprintf(file_name,"%s.complex",file_name) ;
	fp = fopen(file_name , "w+b");
	fprintf( fp , "%s\n", SIMPLE_OBJECT_HEAD) ;
	/* Write Blocks Lists */
	simple_object_writelist(sState->blocks_map,fp);
	/* Write Classes List */
	simple_object_writelist(sState->classes_map,fp);
	/* Write Modules */
	simple_object_writelist(sState->modules_map,fp);
	/* Write Code */
	simple_object_writelist(sState->generated_code,fp);
	#ifdef DEBUG_OBJFILE
	simple_list_print(sState->generated_code);
	#endif
	/* Close File */
	fclose( fp ) ;
}

void simple_object_writelist ( List *pList,FILE *fp )
{
	List *pList2  ;
	int x,x2  ;
	char *string  ;
	fprintf( fp , "{"  ) ;
	/* Write List Items */
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		pList2 = simple_list_getlist(pList,x);
		fprintf( fp , "("  ) ;
		for ( x2 = 1 ; x2 <= simple_list_getsize(pList2) ; x2++ ) {
			if ( simple_list_isstring(pList2,x2) ) {
				fprintf( fp , "[S][%d]" , simple_list_getstringsize(pList2,x2) ) ;
				/* Encrypt String */
				string = simple_list_getstring(pList2,x2) ;
				simple_object_xorstring(string,simple_list_getstringsize(pList2,x2),SIMPLE_OBJECT_KEY,SIMPLE_OBJECT_KEY_SIZE);
				fwrite( simple_list_getstring(pList2,x2), 1, simple_list_getstringsize(pList2,x2) , fp );
				/* Decrypt String */
				simple_object_xorstring(string,simple_list_getstringsize(pList2,x2),SIMPLE_OBJECT_KEY,SIMPLE_OBJECT_KEY_SIZE);
			}
			else if ( simple_list_isint(pList2,x2) ) {
				fprintf( fp , "[I]%d" , simple_list_getint(pList2,x2) ) ;
			}
			else if ( simple_list_isdouble(pList2,x2) ) {
				fprintf( fp , "[D]%f" , simple_list_getdouble(pList2,x2) ) ;
			}
			else if ( simple_list_ispointer(pList2,x2) ) {
				fprintf( fp , "[P]%p" , (void *) simple_list_getpointer(pList2,x2) ) ;
			}
			else if ( simple_list_islist(pList2,x2) ) {
				fprintf( fp , "[L]"  ) ;
				simple_object_writelist(simple_list_getlist(pList2,x2) ,fp);
			}
		}
		fprintf( fp , ")"  ) ;
	}
	fprintf( fp , "}\n"  ) ;
}

int simple_object_readfile ( SimpleState *sState,char *file_name )
{
	return simple_object_readfromsource(sState,file_name,SIMPLE_OBJECT_FROMFILE) ;
}

int simple_object_readstring ( SimpleState *sState,char *string )
{
	return simple_object_readfromsource(sState,string,SIMPLE_OBJECT_FROMSTRING) ;
}

int simple_object_readfromsource ( SimpleState *sState,char *source,int source_type )
{
	List *blocks_list, *classes_list, *modules_list, *code_list, *stack_list  ;
	/* Create Lists */
	blocks_list = simple_list_new_gc(sState,0);
	classes_list = simple_list_new_gc(sState,0);
	modules_list = simple_list_new_gc(sState,0);
	code_list = simple_list_new_gc(sState,0);
	stack_list = simple_list_new_gc(sState,0);
	/* Process Content (File or String) */
	if ( source_type == SIMPLE_OBJECT_FROMFILE ) {
		if ( ! simple_object_processfile(sState,source,blocks_list, classes_list, modules_list, code_list, stack_list) ) {
			return 0 ;
		}
	}
	else if ( source_type ==SIMPLE_OBJECT_FROMSTRING ) {
		if ( ! simple_object_processstring(sState,source,blocks_list, classes_list, modules_list, code_list, stack_list) ) {
			return 0 ;
		}
	}
	simple_list_delete_gc(sState,stack_list);
	/* Update Simple State */
	/* Update Lists */ 
	sState->blocks_map = blocks_list ;
	sState->classes_map = classes_list ;
	sState->modules_map = modules_list ;
	sState->generated_code = code_list ;
	#ifdef DEBUG_OBJFILE
	puts("New Code List ");
	simple_list_print(sState->blocks_map); printf("\n");
	simple_list_print(sState->classes_map); printf("\n");
	simple_list_print(sState->modules_map);  printf("\n");
	simple_list_print(sState->generated_code);  printf("\n");
	#endif
	/* Update Classes Pointers */
	simple_object_updatepointers(sState);
	return 1 ;
}

int simple_object_processfile ( SimpleState *sState,char *file_name,List *blocks_list,List  *classes_list,List  *modules_list,List  *code_list,List  *stack_list )
{
	FILE *fp;
	signed char c  ;
	int nActiveList,nValue,nBraceEnd  ;
	double dValue  ;
	char *string  ;
	char cFileType[100]  ;
	List *pList  ;
	/* Set Active List (1=functions 2=classes 3=packages 4=code) */
	nActiveList = 0 ;
	nBraceEnd = 0 ;
	pList = NULL ;
	/* Open File */
	fp = fopen(file_name , "rb" );
	if ( fp==NULL ) {
		printf( "Can't open file %s \n  ",file_name ) ;
		return 0 ;
	}
	fread( cFileType , 1 , 12 , fp );
	cFileType[SIMPLE_OBJECT_HEAD_SIZE] = '\0' ;
	if ( strcmp(cFileType,SIMPLE_OBJECT_HEAD) != 0 ) {
		printf( "The file is not a valid simple-lang object file\n" ) ;
		return 0 ;
	}
	/* Process File */
	c = getc(fp);
	while ( c != EOF ) {
		/* Check Char */
		switch ( c ) {
			case '{' :
				nActiveList++ ;
				switch ( nActiveList ) {
					case 1 :
						pList = blocks_list ;
						break ;
					case 2 :
						pList = classes_list ;
						break ;
					case 3 :
						pList = modules_list ;
						break ;
					case 4 :
						pList = code_list ;
						break ;
				}
				break ;
			case '(' :
				simple_list_addpointer_gc(sState,stack_list,pList);
				pList = simple_list_newlist_gc(sState,pList);
				#ifdef DEBUG_OBJFILE
				puts("Read ( ");
				#endif
				break ;
			case '[' :
				c = getc(fp);
				switch ( c ) {
					case 'S' :
						c = getc(fp);
						fscanf( fp , "[%d]" , &nValue ) ;
						string = (char *) simple_state_malloc(sState,nValue+1);
						fread( string , 1 , nValue , fp );
						string[nValue] = '\0' ;
						/* Decrypt String */
						simple_object_xorstring(string,nValue,SIMPLE_OBJECT_KEY,SIMPLE_OBJECT_KEY_SIZE);
						simple_list_addstring2_gc(sState,pList,string,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read String %s Size %d \n",string,nValue ) ;
						#endif
						simple_state_free(sState,string);
						break ;
					case 'I' :
						c = getc(fp);
						fscanf( fp , "%d" , &nValue ) ;
						simple_list_addint_gc(sState,pList,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Number %d \n  ",nValue ) ;
						#endif
						break ;
					case 'D' :
						c = getc(fp);
						fscanf( fp , "%lf" , &dValue ) ;
						simple_list_adddouble_gc(sState,pList,dValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Double %d  \n",dValue ) ;
						#endif
						break ;
					case 'P' :
						simple_list_addpointer_gc(sState,pList,NULL);
						/* Read Line */
						#ifdef DEBUG_OBJFILE
						puts("Read Pointer ");
						#endif
						break ;
					case 'L' :
						/* Read Until { */
						while ( c != '{' ) {
							c = getc(fp);
						}
						simple_list_addpointer_gc(sState,stack_list,pList);
						pList = simple_list_newlist_gc(sState,pList);
						nBraceEnd++ ;
						#ifdef DEBUG_OBJFILE
						puts("Read L ");
						#endif
						break ;
				}
				break ;
			case ')' :
				pList = (List *) simple_list_getpointer(stack_list,simple_list_getsize(stack_list)) ;
				simple_list_deletelastitem_gc(sState,stack_list);
				#ifdef DEBUG_OBJFILE
				puts("Read ) ");
				#endif
				break ;
			case '}' :
				if ( nBraceEnd ) {
					pList = (List *) simple_list_getpointer(stack_list,simple_list_getsize(stack_list)) ;
					simple_list_deletelastitem_gc(sState,stack_list);
					nBraceEnd-- ;
					#ifdef DEBUG_OBJFILE
					puts("Read } ");
					#endif
				}
				break ;
		}
		c = getc(fp);
	}
	/* Close File */
	fclose( fp ) ;
	return 1 ;
}

//TODO : below
int simple_object_processstring ( SimpleState *sState,char *content,List *blocks_list,List  *classes_list,List  *modules_list,List  *code_list,List  *stack_list )
{
	signed char c  ;
	int nActiveList,nValue,nBraceEnd  ;
	double dValue  ;
	char *string, *cData  ;
	char cFileType[100]  ;
	List *pList  ;
	/* Set Active List (1=blocks 2=classes 3=packages 4=code) */
	nActiveList = 0 ;
	nBraceEnd = 0 ;
	pList = NULL ;
	cData = content ;
	#ifdef DEBUG_OBJFILE
	printf("Object String Size %i\n", strlen(cData));
	#endif
	/* Check Type and Version */
	simple_object_readc(sState,&cData,cFileType,12);
	cFileType[SIMPLE_OBJECT_HEAD_SIZE] = '\0' ;
	if ( strcmp(cFileType,SIMPLE_OBJECT_HEAD) != 0 ) {
		printf( "The file is not a valid simple-lang object file\n" ) ;
		return 0 ;
	}
	/* Process Content */
	c = simple_object_getc(sState,&cData);
	while ( c != EOF && strlen(cData) > 0 ) {
		//printf("%c %i ",c,strlen(cData));
		/* Check Char */
		switch ( c ) {
			case '{' :
				nActiveList++ ;
				switch ( nActiveList ) {
					case 1 :
						pList = blocks_list ;
						break ;
					case 2 :
						pList = classes_list ;
						break ;
					case 3 :
						pList = modules_list ;
						break ;
					case 4 :
						pList = code_list ;
						break ;
				}
				break ;
			case '(' :
				simple_list_addpointer_gc(sState,stack_list,pList);
				pList = simple_list_newlist_gc(sState,pList);
				#ifdef DEBUG_OBJFILE
				printf("Read ( %c\n", c);
				#endif
				break ;
			case '[' :
				c = simple_object_getc(sState,&cData);
				switch ( c ) {
					case 'S' :
						c = simple_object_getc(sState,&cData);
						sscanf(cData,"[%d]",&nValue);
						/* Pass Letters */
						c = ' ' ;
						while ( c != ']' ) {
							c = simple_object_getc(sState,&cData);
						}
						string = (char *) simple_state_malloc(sState,nValue+1);
						simple_object_readc(sState,&cData,string,nValue);
						string[nValue] = '\0' ;
						/* Decrypt String */
						simple_object_xorstring(string,nValue,SIMPLE_OBJECT_KEY,SIMPLE_OBJECT_KEY_SIZE);
						simple_list_addstring2_gc(sState,pList,string,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read String %s Size %d \n",string,nValue ) ;
						#endif
						simple_state_free(sState,string);
						break ;
					case 'I' :
						c = simple_object_getc(sState,&cData);
						sscanf(cData,"%d",&nValue);
						/* Pass Letters */
						c = '0' ;
						while ( isdigit(c) || c=='.' ) {
							c = simple_object_getc(sState,&cData);
						}
						cData-- ;
						simple_list_addint_gc(sState,pList,nValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Number %d \n  ",nValue ) ;
						#endif
						break ;
					case 'D' :
						c = simple_object_getc(sState,&cData);
						sscanf(cData,"%lf",&dValue);
						/* Pass Letters */
						c = '0' ;
						while ( isdigit(c) || c=='.' ) {
							c = simple_object_getc(sState,&cData);
						}
						cData-- ;
						simple_list_adddouble_gc(sState,pList,dValue);
						#ifdef DEBUG_OBJFILE
						printf( "Read Double %d  \n",dValue ) ;
						#endif
						break ;
					case 'P' :
						simple_list_addpointer_gc(sState,pList,NULL);
						/* Read Line */
						#ifdef DEBUG_OBJFILE
						puts("Read Pointer ");
						#endif
						break ;
					case 'L' :
						/* Read Until { */
						while ( c != '{' ) {
							c = simple_object_getc(sState,&cData);
						}
						simple_list_addpointer_gc(sState,stack_list,pList);
						pList = simple_list_newlist_gc(sState,pList);
						nBraceEnd++ ;
						#ifdef DEBUG_OBJFILE
						puts("Read L ");
						#endif
						break ;
				}
				break ;
			case ')' :
				pList = (List *) simple_list_getpointer(stack_list,simple_list_getsize(stack_list)) ;
				simple_list_deletelastitem_gc(sState,stack_list);
				#ifdef DEBUG_OBJFILE
				puts("Read ) ");
				#endif
				break ;
			case '}' :
				if ( nBraceEnd ) {
					pList = (List *) simple_list_getpointer(stack_list,simple_list_getsize(stack_list)) ;
					simple_list_deletelastitem_gc(sState,stack_list);
					nBraceEnd-- ;
					#ifdef DEBUG_OBJFILE
					puts("Read } ");
					#endif
				}
				break ;
		}
		c = simple_object_getc(sState,&cData);
		//printf("%c ",c);
	}
	return 1 ;
}

void simple_object_updatepointers ( SimpleState *sState )
{
	int x,x2,x3,x4,lFound  ;
	List *pList, *pList2, *pList3  ;
	const char *string  ;
	char module_name[400]  ;
	char class_name[400]  ;
	/* Update Class Pointer in Code */
	lFound = 0 ;
	for ( x = 1 ; x <= simple_list_getsize(sState->generated_code) ; x++ ) {
		pList = simple_list_getlist(sState->generated_code,x);
		if ( simple_list_getint(pList,1) == ICO_NEWCLASS ) {
			string = simple_list_getstring(pList,2);
			for ( x2 = 1 ; x2 <= simple_list_getsize(sState->classes_map) ; x2++ ) {
				pList2 = simple_list_getlist(sState->classes_map,x2);
				if ( strcmp(string,simple_list_getstring(pList2,1)) == 0 ) {
					lFound = 0 ;
					simple_list_setpointer_gc(sState,pList,3,pList2);
					#ifdef DEBUG_OBJFILE
					puts("Pointer Updated ");
					#endif
					break ;
				}
			}
			/* If we can't find the list (the class is inside a module) */
			if ( lFound == 0 ) {
				simple_list_setpointer_gc(sState,pList,3,NULL);
			}
		}
	}
	/*
	**  Update Class Pointers in Classes Map when the class belong to a Module 
	**  This updates works when the class name is : modulename.classname 
	*/
	for ( x = 1 ; x <= simple_list_getsize(sState->classes_map) ; x++ ) {
		pList = simple_list_getlist(sState->classes_map,x);
		string = simple_list_getstring(pList,1);
		if ( simple_list_getstringsize(pList,1)  > 400 ) {
			/* Avoid large names - we have limits (400 letters per module name - 400 letters for class name) */
			continue ;
		}
		for ( x2 = simple_list_getstringsize(pList,1) - 1 ; x2 >= 0 ; x2-- ) {
			if ( string[x2] == '.' ) {
				/*
				**  Now we have a class name stored as modulename.classname 
				**  Get Module Name 
				*/
				for ( x3 = 0 ; x3 < x2 ; x3++ ) {
					module_name[x3] = string[x3] ;
				}
				module_name[x2] = '\0' ;
				#ifdef DEBUG_OBJFILE
				printf( "Module Name %s \n",module_name ) ;
				#endif
				/* Get Class Name */
				for ( x3 = x2+1 ; x3 <= simple_list_getstringsize(pList,1) - 1 ; x3++ ) {
					class_name[x3-x2-1] = string[x3] ;
				}
				class_name[simple_list_getstringsize(pList,1) - 1 - x2] = '\0' ;
				#ifdef DEBUG_OBJFILE
				printf( "Class Name %s \n",class_name ) ;
				#endif
				/* Get The Module List */
				for ( x3 = 1 ; x3 <= simple_list_getsize(sState->modules_map) ; x3++ ) {
					pList2 = simple_list_getlist(sState->modules_map,x3);
					if ( strcmp(simple_list_getstring(pList2,1),module_name) == 0 ) {
						/* Get The Class List */
						pList2 = simple_list_getlist(pList2,2);
						for ( x4 = 1 ; x4 <= simple_list_getsize(pList2) ; x4++ ) {
							pList3 = simple_list_getlist(pList2,x4);
							#ifdef DEBUG_OBJFILE
							printf("ModuleName=%s,ClassName=%s\n",module_name,simple_list_getstring(pList3,1)) ;
							#endif
							if ( strcmp(simple_list_getstring(pList3,1),class_name) == 0 ) {
								/* Now We have the Class - Update Pointer */
								simple_list_setpointer_gc(sState,pList,2,(void *) pList3);
								break ;
							}
						}
						break ;
					}
				}
			}
		}
	}
	/* Update Module Pointers in Modules Classes */
	for ( x = 1 ; x <= simple_list_getsize(sState->modules_map) ; x++ ) {
		pList = simple_list_getlist(sState->modules_map,x);
		/* Get The Class List */
		pList2 = simple_list_getlist(pList,2);
		for ( x2 = 1 ; x2 <= simple_list_getsize(pList2) ; x2++ ) {
			pList3 = simple_list_getlist(pList2,x2);
			simple_list_setpointer_gc(sState,pList3,SIMPLE_CLASSMAP_POINTERTOMODULE,pList);
		}
	}
}

void simple_object_xorstring ( char *string,int string_size,char *key,int key_size )
{
	int x  ;
	for ( x = 1 ; x <= string_size ; x++ ) {
		string[x-1] = string[x-1] ^ key[(x-1)%key_size] ;
	}
}

void simple_object_readc ( SimpleState *sState,char **source,char *dest,int count )
{
	int x  ;
	char *cData  ;
	cData = *source ;
	for ( x = 0 ; x < count ; x++ ) {
		dest[x] = cData[x] ;
	}
	*source += count ;
	dest[count] = '\0' ;
}

char simple_object_getc ( SimpleState *sState,char **source )
{
	char c  ;
	char *cData  ;
	cData = *source ;
	c = cData[0] ;
	*source+=1 ;
	return c ;
}
