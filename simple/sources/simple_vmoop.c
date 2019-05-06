/*
**  pClassesMap ( cClass Name ,  iPC , cParentClass, aMethodsList , nFlagIsParentClassInformation 
**  pClassesMap ( cClass Name, Pointer to List that represent class inside a Modules, Pointer to File 
**  pBlocksMap ( Name, PC, FileName, Private Flag ) 
**  Moduless List ( Modules Name , Classes List ) 
**  Object ( is a list of two items , (1) Class Pointer  (2) Object Data  ) 
**  vm->aScopeNewObj : (1) Previous scope (2) nListStart (3) pNestedLists (4) nsp 
**  vm->pObjState  (  [ Pointer to Scope, Pointer to Methods , Pointer to Classs, Optional True) 
**  The optional True used with LoadMethod so we can Know that we are inside class method during RT 
**  We don't check the True value, we just check that the size of the list is 4 
**  used in simple_vmblocks , block simple_vm_loadblock2() 
**  used in simple_vmvars , block simple_vm_findvar2() 
**  pBraceObject : The list that represent the object directly (not varaible/list item) 
**  aBraceObjects ( pBraceObject, nsp, nListStart, pNestedLists) 
**  aSetProperty ( Object Pointer , Type (Variable/ListItem)  , Property Name, Property Variable , nBeforeEqual) 
*/
#include "../include/simple.h"
/* Blocks */

SIMPLE_API void simple_vm_oop_newobj ( VM *vm )
{
	const char *cClassName,*cClassName2  ;
	int x,nLimit,nClassPC,nType,nCont  ;
	List *list,*list2,*list3,*list4,*list5,*var,*pSelf  ;
	Item *pItem  ;
	const char *cTempName = SIMPLE_TEMP_OBJECT ;
	list2 = NULL ;
	var = NULL ;
	pItem = NULL ;
	cClassName = SIMPLE_VM_IR_READC ;
	nLimit = simple_vm_oop_visibleclassescount(vm);
	if ( nLimit > 0 ) {
		for ( x = 1 ; x <= nLimit ; x++ ) {
			list = simple_vm_oop_visibleclassitem(vm,x);
			cClassName2 = simple_list_getstring(list,1);
			list = simple_vm_oop_checkpointertoclassinmodules(vm,list);
			if ( list == NULL ) {
				continue ;
			}
			nClassPC = simple_list_getint(list,2);
			if ( strcmp(cClassName,cClassName2) == 0/* || 1 */) {
				/* Check Assignment */
				nCont = 1 ;
				if ( SIMPLE_VM_STACK_ISPOINTER ) {
					if ( vm->pAssignment == SIMPLE_VM_STACK_READP ) {
						nCont = 0 ;
					}
				}
				if ( vm->nBlockExecute > 0 ) {
					nCont = 1 ;
				}
				if ( nCont == 1 ) {
					simple_vm_newvar(vm,cTempName);
					var = (List *) SIMPLE_VM_STACK_READP ;
					nType = SIMPLE_VM_STACK_OBJTYPE ;
					simple_list_setint_gc(vm->sState,var,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
					simple_list_setlist_gc(vm->sState,var,SIMPLE_VAR_VALUE);
					list2 = simple_list_getlist(var,SIMPLE_VAR_VALUE);
				}
				else {
					/* Prepare Object List */
					if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
						var = (List *) SIMPLE_VM_STACK_READP ;
						simple_list_setint_gc(vm->sState,var,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
						simple_list_setlist_gc(vm->sState,var,SIMPLE_VAR_VALUE);
						list2 = simple_list_getlist(var,SIMPLE_VAR_VALUE);
					}
					else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
						pItem = (Item *) SIMPLE_VM_STACK_READP ;
						simple_item_settype_gc(vm->sState,pItem,ITEMTYPE_LIST);
						var = simple_item_getlist(pItem);
						list2 = var ;
					}
					nType = SIMPLE_VM_STACK_OBJTYPE ;
				}
				simple_list_deleteallitems_gc(vm->sState,list2);
				/* Push Class Modules */
				simple_vm_oop_pushclassmodules(vm,list);
				/* Store the Class Pointer in the Object Data */
				simple_list_addpointer_gc(vm->sState,list2,list);
				/* Create List for the Object State */
				list3 = simple_list_newlist_gc(vm->sState,list2);
				/* Create Self variable in the state list */
				pSelf = simple_vm_newvar2(vm,"self",list3);
				simple_list_setint_gc(vm->sState,pSelf,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
				if ( nType == SIMPLE_OBJTYPE_VARIABLE ) {
					simple_list_setpointer_gc(vm->sState,pSelf,SIMPLE_VAR_VALUE,var);
				}
				else if ( nType == SIMPLE_OBJTYPE_LISTITEM ) {
					simple_list_setpointer_gc(vm->sState,pSelf,SIMPLE_VAR_VALUE,pItem);
				}
				simple_list_setint_gc(vm->sState,pSelf,SIMPLE_VAR_PVALUETYPE ,nType);
				/* Jump to Class INIT Method */
				simple_vm_blockflag2(vm,vm->nPC);
				/* Execute Parent Classes Init first */
				if ( strcmp(simple_list_getstring(list,3),"") != 0 ) {
					simple_vm_blockflag2(vm,nClassPC);
					simple_vm_oop_parentinit(vm,list);
				}
				else {
					vm->nPC = nClassPC ;
				}
				/* Save the current Scope, List and Stack */
				list4 = simple_list_newlist_gc(vm->sState,vm->aScopeNewObj);
				simple_list_addpointer_gc(vm->sState,list4,vm->pActiveMem);
				/* Store List information to allow calling block from list item and creating lists from that blockt */
				simple_list_addint_gc(vm->sState,list4,vm->nListStart);
				simple_list_addpointer_gc(vm->sState,list4,vm->pNestedLists);
				vm->nListStart = 0 ;
				vm->pNestedLists = simple_list_new_gc(vm->sState,0);
				/* Save Stack Information */
				simple_list_addint_gc(vm->sState,list4,vm->nsp);
				/* Save BlockExecute */
				simple_list_addint_gc(vm->sState,list4,vm->nBlockExecute);
				vm->nBlockExecute = 0 ;
				/* Save Private Flag Status */
				simple_list_addint_gc(vm->sState,list4,vm->nPrivateFlag);
				/* Save InsideBrace Flag */
				simple_list_addint_gc(vm->sState,list4,vm->nInsideBraceFlag);
				vm->nInsideBraceFlag = 0 ;
				simple_list_addpointer_gc(vm->sState,list4,vm->pBraceObject);
				/* Save nCallClassInit */
				simple_list_addint_gc(vm->sState,list4,vm->nCallClassInit);
				vm->nCallClassInit = 0 ;
				/* Save Line Number */
				simple_list_addint_gc(vm->sState,list4,vm->nLineNumber);
				/* Save Block Stack */
				simple_list_addint_gc(vm->sState,list4,vm->nBlockSP);
				/* Save Assignment Pointer */
				simple_list_addpointer_gc(vm->sState,list4,vm->pAssignment);
				/* Save the Object Pointer and Type */
				simple_list_addpointer_gc(vm->sState,list4,SIMPLE_VM_STACK_READP);
				simple_list_addint_gc(vm->sState,list4,SIMPLE_VM_STACK_OBJTYPE);
				/* Save Current Global Scope */
				simple_list_addint_gc(vm->sState,list4,vm->nCurrentGlobalScope);
				/* Save Final Flag Status */
				simple_list_addint_gc(vm->sState,list4,vm->finalFlag);
				/* Set Object State as the Current Scope */
				vm->pActiveMem = list3 ;
				/* Prepare to Make Object State & Methods visible while executing the INIT method */
				list5 = simple_list_newlist_gc(vm->sState,vm->pObjState);
				simple_list_addpointer_gc(vm->sState,list5,list3);
				simple_list_addpointer_gc(vm->sState,list5,NULL);
				simple_list_addpointer_gc(vm->sState,list5,list);
				/* Create the Super Virtual Object */
				simple_vm_oop_newsuperobj(vm,list3,list);
				/* Enable NULL variables (To be class attributes) */
				vm->within_class++ ;
				/* Support using Braces to access the object state */
				vm->pBraceObject = list2 ;
				return ;
			}
		}
	}
	simple_vm_error2(vm,SIMPLE_VM_ERROR_CLASSNOTFOUND,cClassName);
}

SIMPLE_API void simple_vm_oop_parentinit ( VM *vm,List *list )
{
	const char *cClassName,*cClassName2  ;
	int x,x2,nFound,nMark  ;
	List *list2, *pClassesList  ;
	String *string  ;
	/* Get the parent class name from the Class List Pointer */
	cClassName = simple_list_getstring(list,3) ;
	/* Create List for Classes Pointers */
	pClassesList = simple_list_new_gc(vm->sState,0);
	simple_list_addpointer_gc(vm->sState,pClassesList,list);
	while ( strcmp(cClassName,"") != 0 ) {
		/* Mark Moduless Count */
		nMark = simple_list_getsize(vm->aActiveModules);
		nFound = 0 ;
		for ( x = 1 ; x <= simple_vm_oop_visibleclassescount(vm) ; x++ ) {
			list2 = simple_vm_oop_visibleclassitem(vm,x);
			cClassName2 = simple_list_getstring(list2,1) ;
			list2 = simple_vm_oop_checkpointertoclassinmodules(vm,list2);
			if ( list2 == NULL ) {
				continue ;
			}
			if ( strcmp(cClassName,cClassName2) == 0 ) {
				/* Check that the parent class is not one of the subclasses */
				for ( x2 = 1 ; x2  <= simple_list_getsize(pClassesList) ; x2++ ) {
					if ( ((List *) simple_list_getpointer(pClassesList,x2)) == list2 ) {
						string = simple_string_new_gc(vm->sState,"When creating class ");
						simple_string_add_gc(vm->sState,string,simple_list_getstring(list,1));
						simple_string_add_gc(vm->sState,string," from class ");
						simple_string_add_gc(vm->sState,string,cClassName);
						simple_vm_error2(vm,SIMPLE_VM_ERROR_PARENTCLASSLIKESUBCLASS,simple_string_get(string));
						simple_string_delete_gc(vm->sState,string);
						/* Delete Classes Pointers List */
						simple_list_delete_gc(vm->sState,pClassesList);
						return ;
					}
				}
				simple_list_addpointer_gc(vm->sState,pClassesList,list2);
				/* Push Class Modules */
				simple_vm_oop_pushclassmodules(vm,list2);
				cClassName = simple_list_getstring(list2,3) ;
				if ( strcmp(cClassName,"") != 0 ) {
					/* Add Class Init Method to be called */
					simple_vm_blockflag2(vm,simple_list_getint(list2,2));
				}
				else {
					vm->nPC = simple_list_getint(list2,2) ;
				}
				nFound = 1 ;
				break ;
			}
		}
		if ( nFound == 0 ) {
			/* Error Message */
			simple_vm_error2(vm,SIMPLE_VM_ERROR_PARENTCLASSNOTFOUND,cClassName);
			break ;
		}
		/* Restore Mark */
		simple_vm_oop_deletemodulessafter(vm,nMark);
		list = list2 ;
	}
	/* Delete Classes Pointers List */
	simple_list_delete_gc(vm->sState,pClassesList);
}

SIMPLE_API void simple_vm_oop_newclass ( VM *vm )
{
	List *pClass,*list  ;
	char class_name[400]  ;
	int x  ;
	pClass = (List *) SIMPLE_VM_IR_READPVALUE(2) ;
	/* Find the Class Pointer using the Class Name */
	if ( pClass == NULL ) {
		for ( x = 1 ; x <= simple_list_getsize(vm->sState->classes_map) ; x++ ) {
			list = simple_list_getlist(vm->sState->classes_map,x);
			if ( strcmp(simple_list_getstring(list,1),SIMPLE_VM_IR_READCVALUE(1)) == 0) {
				if ( simple_list_getsize(list) == 3 ) {
					/* Here the class is stored inside a modules - we have the class pointer (item 2) */
					pClass = (List *) simple_list_getpointer(list,2) ;
				}
				else {
					pClass = list ;
				}
				SIMPLE_VM_IR_READPVALUE(2) = (void *) pClass ;
				break ;
			}
		}
	}
	
	/* Find the Class Pointer using the Class Name for complex file*/
	if ( pClass == NULL ) {
		for ( x = 1 ; x <= simple_list_getsize(vm->sState->classes_map) ; x++ ) {
			list = simple_list_getlist(vm->sState->classes_map,x);
			last_text_after_char(class_name,simple_list_getstring(list,1),'.');
			if (strcmp(class_name,SIMPLE_VM_IR_READCVALUE(1)) == 0) {
				if ( simple_list_getsize(list) == 3 ) {
					/* Here the class is stored inside a modules - we have the class pointer (item 2) */
					pClass = (List *) simple_list_getpointer(list,2) ;
				}
				else {
					pClass = list ;
				}
				SIMPLE_VM_IR_READPVALUE(2) = (void *) pClass ;
				break ;
			}
		}
	}
	pClass = simple_vm_oop_checkpointertoclassinmodules(vm,pClass);
	/* Make object methods visible while executing the Class Init method */
	list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState));
	simple_list_setpointer_gc(vm->sState,list,2,simple_list_getlist(pClass,4));
	/* Get Parent Classes Methods */
	simple_vm_oop_parentmethods(vm,pClass);
	/* Attributes Scope is Public */
	vm->nPrivateFlag = 0 ;
	/* Not Final */
	vm->finalFlag = 0 ;
}

SIMPLE_API void simple_vm_oop_setscope ( VM *vm )
{
	List *list  ;
	/* This block called after creating new object and executing class init */
	list = simple_list_getlist(vm->aScopeNewObj,simple_list_getsize(vm->aScopeNewObj)) ;
	/*
	**  Restore State 
	**  Restore Stack Information 
	*/
	vm->nsp = simple_list_getint(list,4) ;
	/* Restore BlockExecute */
	vm->nBlockExecute = simple_list_getint(list,5) ;
	/* Restore Private Flag */
	vm->nPrivateFlag = simple_list_getint(list,6) ;
	/* Restore InsideBrace Flag */
	vm->nInsideBraceFlag = simple_list_getint(list,7) ;
	vm->pBraceObject = (List *) simple_list_getpointer(list,8) ;
	/* Restore nCallClassInit */
	vm->nCallClassInit = simple_list_getint(list,9) ;
	/* Restore nLineNumber */
	vm->nLineNumber = simple_list_getint(list,10) ;
	/* Restore Block Stack */
	vm->nBlockSP = simple_list_getint(list,11) ;
	/* Restore Assignment Pointer */
	vm->pAssignment = (List *) simple_list_getpointer(list,12) ;
	/* Restore the scope (before creating the object using new) */
	vm->pActiveMem = (List *) simple_list_getpointer(list,1) ;
	/* Restore List Status */
	vm->nListStart = simple_list_getint(list,2) ;
	if ( vm->pNestedLists != simple_list_getpointer(list,3) ) {
		vm->pNestedLists = simple_list_delete_gc(vm->sState,vm->pNestedLists);
		vm->pNestedLists = (List *) simple_list_getpointer(list,3) ;
	}
	/* Restore the Object Pointer and The Object Type */
	SIMPLE_VM_STACK_SETPVALUE(simple_list_getpointer(list,13));
	SIMPLE_VM_STACK_OBJTYPE = simple_list_getint(list,14) ;
	/* Restore current Global Scope */
	vm->nCurrentGlobalScope = simple_list_getint(list,15);
	/* Restore current Final flag */
	vm->finalFlag = simple_list_getint(list,16);
	/* After init methods */
	simple_vm_oop_aftercallmethod(vm);
	simple_list_deleteitem_gc(vm->sState,vm->aScopeNewObj,simple_list_getsize(vm->aScopeNewObj));
	/* Disable NULL variables (To be class attributes) */
	vm->within_class-- ;
	/* POP Class Modules */
	simple_vm_oop_popclassmodules(vm);
}

SIMPLE_API int simple_vm_oop_isobject ( List *list )
{
	if ( list == NULL ) {
		return 0 ;
	}
	if ( simple_list_getsize(list) != 2 ) {
		return 0 ;
	}
	if ( simple_list_ispointer(list,1) == 0 ) {
		return 0 ;
	}
	if ( simple_list_islist(list,2) == 0 ) {
		return 0 ;
	}
	return 1 ;
}

List * simple_vm_oop_getobj ( VM *vm )
{
	List *var  ;
	Item *pItem  ;
	var = NULL ;
	/* Get Object Data */
	if ( ! SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_NOTOBJECT);
		return NULL ;
	}
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		var = (List *) SIMPLE_VM_STACK_READP ;
		if ( simple_list_getint(var,SIMPLE_VAR_TYPE) == SIMPLE_VM_NULL ) {
			simple_vm_error2(vm,SIMPLE_VM_ERROR_USINGNULLVARIABLE,simple_list_getstring(var,SIMPLE_VAR_NAME));
			return NULL ;
		}
		if ( ! simple_list_islist(var,SIMPLE_VAR_VALUE  ) ) {
			simple_vm_error(vm,SIMPLE_VM_ERROR_NOTOBJECT);
			return NULL ;
		}
		var = simple_list_getlist(var,SIMPLE_VAR_VALUE);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		var = simple_item_getlist(pItem);
	}
	if ( simple_vm_oop_isobject(var) == 0 ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_NOTOBJECT);
		return NULL ;
	}
	SIMPLE_VM_STACK_POP ;
	return var ;
}

SIMPLE_API void simple_vm_oop_property ( VM *vm )
{
	List *var,*pScope  ;
	/* Get Object Pointer Before being a list by getobj */
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		vm->pGetSetObject = SIMPLE_VM_STACK_READP ;
		vm->nGetSetObjType = SIMPLE_VM_STACK_OBJTYPE ;
	}
	/* Get Object Data */
	var = simple_vm_oop_getobj(vm);
	if ( var == NULL ) {
		return ;
	}
	/* Get Object State */
	pScope = vm->pActiveMem ;
	vm->pActiveMem = simple_list_getlist(var,2);
	vm->nGetSetProperty = 1 ;
	if ( simple_vm_findvar(vm, SIMPLE_VM_IR_READC ) == 0 ) {
		/* Create the attribute if we are in the class region after the class name */
		if ( vm->within_class ) {
			simple_vm_newvar(vm, SIMPLE_VM_IR_READC);
			/* Support for Private Flag */
			simple_list_setint_gc(vm->sState,(List *) SIMPLE_VM_STACK_READP,SIMPLE_VAR_PRIVATEFLAG,vm->nPrivateFlag);
			SIMPLE_VM_STACK_POP ;
			simple_vm_findvar(vm, SIMPLE_VM_IR_READC);
			vm->pActiveMem = pScope ;
			vm->nGetSetProperty = 0 ;
			vm->pGetSetObject = NULL ;
			return ;
		}
		vm->pActiveMem = pScope ;
		vm->nGetSetProperty = 0 ;
		vm->pGetSetObject = NULL ;
		if ( vm->nActiveCatch == 0 ) {
			/*
			**  We check nActiveCatch because we may have error "accessing private attribute' 
			**  while we are using simple_vm_findvar 
			**  And we are using try catch finally in the code 
			**  In this case we don't add another error message 
			**  So the try catch finally can work as expected and avoid the need to another one 
			**  Error Message 
			*/
			simple_vm_error2(vm,SIMPLE_VM_ERROR_PROPERTYNOTFOUND,SIMPLE_VM_IR_READC);
		}
		return ;
	}
	vm->pActiveMem = pScope ;
	vm->nGetSetProperty = 0 ;
	vm->pGetSetObject = NULL ;
}

SIMPLE_API void simple_vm_oop_loadmethod ( VM *vm )
{
	List *var,*list,*list2,*list3,*pSuper  ;
	int lResult  ;
	/* Check calling method related to Parent Class */
	pSuper = simple_vm_oop_getsuperobj(vm);
	if ( pSuper != NULL ) {
		simple_vm_oop_loadsuperobjmethod(vm,pSuper);
		/* Move list from pObjState to aBeforeObjState */
		simple_vm_oop_movetobeforeobjstate(vm);
		return ;
	}
	/* Get Object Data */
	var = simple_vm_oop_getobj(vm);
	if ( var == NULL ) {
		return ;
	}
	/* Update Self Pointer Using Temp. Item */
	simple_vm_oop_updateselfpointer2(vm,var);
	/* Get Object Class */
	list = (List *) simple_list_getpointer(var,1);
	/* Push Class Modules */
	simple_vm_oop_pushclassmodules(vm,list);
	/* Get Object State */
	list2 = simple_list_newlist_gc(vm->sState,vm->pObjState);
	simple_list_addpointer_gc(vm->sState,list2,simple_list_getlist(var,2));
	/* Get Class Methods */
	list3 = simple_list_getlist(list,4);
	simple_list_addpointer_gc(vm->sState,list2,list3);
	/* Add Pointer to Class */
	simple_list_addpointer_gc(vm->sState,list2,list);
	/* Add Logical Value (True) , That we are inside the class method */
	simple_list_addint_gc(vm->sState,list2,1);
	/* Get Parent Classes Methods */
	simple_vm_oop_parentmethods(vm,list);
	/* Call Method */
	var = vm->pBlocksMap ;
	vm->pBlocksMap = list3 ;
	vm->nCallMethod = 1 ;
	lResult = simple_vm_loadblock(vm);
	vm->nCallMethod = 0 ;
	vm->pBlocksMap = var ;
	/* Move list from pObjState to aBeforeObjState */
	if ( lResult ) {
		simple_vm_oop_movetobeforeobjstate(vm);
	}
}

SIMPLE_API void simple_vm_oop_movetobeforeobjstate ( VM *vm )
{
	List *list, *list2  ;
	if ( vm->nActiveCatch == 1 ) {
		/* Try/Catch restore aObjState and may become empty */
		return ;
	}
	/* Move list from pObjState to aBeforeObjState */
	list = simple_list_newlist_gc(vm->sState,vm->aBeforeObjState);
	list2 = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState));
	simple_list_copy(list,list2);
	simple_list_deleteitem_gc(vm->sState,vm->pObjState,simple_list_getsize(vm->pObjState));
}

SIMPLE_API void simple_vm_oop_parentmethods ( VM *vm,List *list )
{
	const char *cClassName,*cClassName2  ;
	int x,nFound,nMark  ;
	List *list3,*list4  ;
	list3 = simple_list_getlist(list,4);
	if ( simple_list_getint(list,5) == 0 ) {
		simple_list_setint_gc(vm->sState,list,5,1);
		cClassName = simple_list_getstring(list,3) ;
		/* Mark Moduless Count */
		nMark = simple_list_getsize(vm->aActiveModules);
		while ( strcmp(cClassName,"") != 0 ) {
			/* Push Class Modules */
			simple_vm_oop_pushclassmodules(vm,list);
			nFound = 0 ;
			for ( x = 1 ; x <= simple_vm_oop_visibleclassescount(vm) ; x++ ) {
				list4 = simple_vm_oop_visibleclassitem(vm,x);
				cClassName2 = simple_list_getstring(list4,1) ;
				/* Prev. Step must be before Next. step - We check the name include the pacakge */
				list4 = simple_vm_oop_checkpointertoclassinmodules(vm,list4);
				if ( list4 == NULL ) {
					continue ;
				}
				if ( strcmp(cClassName,cClassName2) == 0 ) {
					/* Push Class Modules */
					simple_vm_oop_pushclassmodules(vm,list4);
					simple_list_copy(list3,simple_list_getlist(list4,4));
					cClassName = simple_list_getstring(list4,3) ;
					nFound = 1 ;
					break ;
				}
			}
			if ( nFound == 0 ) {
				simple_vm_error(vm,SIMPLE_VM_ERROR_PARENTCLASSNOTFOUND);
				break ;
			}
			/* Exit when the parent class already contains it's parent classes data */
			if ( simple_list_getint(list,5) == 1 ) {
				break ;
			}
		}
		/* Restore Mark */
		simple_vm_oop_deletemodulessafter(vm,nMark);
	}
}

SIMPLE_API void simple_vm_oop_aftercallmethod ( VM *vm )
{
	if ( simple_list_getsize(vm->pObjState) != 0 ) {
		simple_list_deleteitem_gc(vm->sState,vm->pObjState,simple_list_getsize(vm->pObjState));
	}
	/* POP Class Modules */
	simple_vm_oop_popclassmodules(vm);
}

SIMPLE_API void simple_vm_oop_printobj ( VM *vm,List *list )
{
	List *list2,*list3  ;
	int x  ;
	char cStr[100]  ;
	list = simple_list_getlist(list,2);
	for ( x = 3 ; x <= simple_list_getsize(list) ; x++ ) {
		list2 = simple_list_getlist(list,x);
		printf( "%s: " , simple_list_getstring(list2,1) ) ;
		if ( simple_list_isstring(list2,3) ) {
			printf( "%s\n" , simple_list_getstring(list2,3) ) ;
		}
		else if ( simple_list_isnumber(list2,3) ) {
			if ( vm != NULL ) {
				simple_vm_numtostring(vm,simple_list_getdouble(list2,3),cStr);
				printf( "%s\n" ,cStr ) ;
			}
			else {
				printf( "%f\n" , simple_list_getdouble(list2,3) ) ;
			}
		}
		else if ( simple_list_islist(list2,3) ) {
			list3 = simple_list_getlist(list2,3) ;
			if ( simple_vm_oop_isobject(list3) ) {
				printf( "Object...\n" ) ;
			}
			else {
				printf( "[This Attribute Contains A List]\n" ) ;
			}
		}
	}
}

SIMPLE_API void simple_vm_oop_setbraceobj ( VM *vm,List *list )
{
	/* Support using { } to access object after object name */
	if ( simple_vm_oop_isobject(list) ) {
		vm->pBraceObject = list ;
	}
}

SIMPLE_API void simple_vm_oop_bracestart ( VM *vm )
{
	List *list,*pClass  ;
	/* Check Error */
	if ( vm->pBraceObject == NULL ) {
		simple_vm_error(vm,SIMPLE_VM_ERROR_BRACEWITHOUTOBJECT);
		return ;
	}
	/* Prepare to Access Object State */
	list = simple_list_newlist_gc(vm->sState,vm->pObjState);
	/* Store Pointer to Object State */
	simple_list_addpointer_gc(vm->sState,list,simple_list_getlist(vm->pBraceObject,2));
	/* Store Object Class Methods */
	pClass = (List *) simple_list_getpointer(vm->pBraceObject,1) ;
	simple_list_addpointer_gc(vm->sState,list,simple_list_getlist(pClass,4));
	/* Store Class Pointer */
	simple_list_addpointer_gc(vm->sState,list,pClass);
	/* Add Brace Object & Stack Pointer to List */
	list = simple_list_newlist_gc(vm->sState,vm->aBraceObjects);
	simple_list_addpointer(list,vm->pBraceObject);
	simple_list_addint_gc(vm->sState,list,vm->nsp);
	/* Store List information to allow using braces from list item and creating lists from that brace */
	simple_list_addint_gc(vm->sState,list,vm->nListStart);
	simple_list_addpointer_gc(vm->sState,list,vm->pNestedLists);
	vm->nListStart = 0 ;
	vm->pNestedLists = simple_list_new_gc(vm->sState,0);
	/* Update Self Pointer Using Temp. Item */
	simple_vm_oop_updateselfpointer2(vm,vm->pBraceObject);
	vm->pBraceObject = NULL ;
	vm->nInsideBraceFlag = 1 ;
}

SIMPLE_API void simple_vm_oop_braceend ( VM *vm )
{
	List *list  ;
	/* Restore List Status */
	list = simple_list_getlist(vm->aBraceObjects,simple_list_getsize(vm->aBraceObjects)) ;
	vm->nListStart = simple_list_getint(list,3) ;
	if ( vm->pNestedLists != simple_list_getpointer(list,4) ) {
		vm->pNestedLists = simple_list_delete_gc(vm->sState,vm->pNestedLists);
		vm->pNestedLists = (List *) simple_list_getpointer(list,4) ;
	}
	/* Restore Stack Status */
	vm->nsp = simple_list_getint(list,2) ;
	simple_list_deleteitem_gc(vm->sState,vm->aBraceObjects,simple_list_getsize(vm->aBraceObjects));
	simple_list_deleteitem_gc(vm->sState,vm->pObjState,simple_list_getsize(vm->pObjState));
	if ( simple_list_getsize(vm->aBraceObjects) > 0 ) {
		vm->pBraceObject = simple_list_getlist(vm->aBraceObjects,simple_list_getsize(vm->aBraceObjects)) ;
		vm->pBraceObject = (List *) simple_list_getpointer(vm->pBraceObject,1) ;
		vm->nInsideBraceFlag = 1 ;
	}
	else {
		vm->nInsideBraceFlag = 0 ;
	}
}

SIMPLE_API void simple_vm_oop_bracestack ( VM *vm )
{
	vm->nsp = simple_list_getint(simple_list_getlist(vm->aBraceObjects,simple_list_getsize(vm->aBraceObjects)),2) ;
	if ( vm->nBlockSP > vm->nsp ) {
		/*
		**  This fixes a problem when we use oObject {  executeCode(code) } return string 
		**  Where vm->nsp maybe less than vm->nBlockSP while we are inside block 
		*/
		if ( simple_list_getsize(vm->pBlockCallList) > 0 ) {
			vm->nsp = vm->nBlockSP ;
		}
	}
}

SIMPLE_API void simple_vm_oop_newsuperobj ( VM *vm,List *pState,List *pClass )
{
	List *pSuper,*pSuper2,*pMethods,*list  ;
	const char *cParentClassName,*cClassName  ;
	int x  ;
	pSuper = simple_vm_newvar2(vm,"super",pState);
	simple_list_setint_gc(vm->sState,pSuper,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(vm->sState,pSuper,SIMPLE_VAR_VALUE);
	pSuper2 = simple_list_getlist(pSuper,SIMPLE_VAR_VALUE);
	pMethods = simple_list_getlist(pClass,4);
	simple_list_addpointer_gc(vm->sState,pSuper2,pMethods);
	cParentClassName = simple_list_getstring(pClass,3) ;
	while ( strcmp(cParentClassName,"") != 0 ) {
		for ( x = 1 ; x <= simple_vm_oop_visibleclassescount(vm) ; x++ ) {
			list = simple_vm_oop_visibleclassitem(vm,x);
			cClassName = simple_list_getstring(list,1) ;
			list = simple_vm_oop_checkpointertoclassinmodules(vm,list);
			if ( list == NULL ) {
				continue ;
			}
			if ( strcmp(cClassName,cParentClassName) == 0 ) {
				cParentClassName = simple_list_getstring(list,3) ;
				pMethods = simple_list_getlist(list,4);
				simple_list_addpointer_gc(vm->sState,pSuper2,pMethods);
				break ;
			}
		}
	}
}

List * simple_vm_oop_getsuperobj ( VM *vm )
{
	List *var  ;
	if ( ( SIMPLE_VM_STACK_ISPOINTER ) && ( simple_list_getsize(vm->pObjState) != 0    ) ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			var = (List *) SIMPLE_VM_STACK_READP ;
			if ( (simple_list_islist(var,3)) && (strcmp(simple_list_getstring(var,1),"super") == 0 ) ) {
				var = simple_list_getlist(var,3);
				SIMPLE_VM_STACK_POP ;
				return var ;
			}
		}
	}
	return NULL ;
}

SIMPLE_API void simple_vm_oop_loadsuperobjmethod ( VM *vm,List *pSuper )
{
	int x  ;
	List *pState,*pMethods,*pClass,*var,*list  ;
	list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState));
	pState = simple_list_getlist(list,SIMPLE_OBJSTATE_SCOPE);
	pMethods = simple_list_getlist(list,SIMPLE_OBJSTATE_METHODS);
	pClass = simple_list_getlist(list,SIMPLE_OBJSTATE_CLASS);
	for ( x = 1 ; x <= simple_list_getsize(pSuper) ; x++ ) {
		if ( simple_list_getpointer(pSuper,x) == pMethods ) {
			if ( (x+1)  <= simple_list_getsize(pSuper) ) {
				pMethods = (List *) simple_list_getpointer(pSuper,(x+1));
				break ;
			}
			else {
				simple_vm_error(vm,SIMPLE_VM_ERROR_SUPERCLASSNOTFOUND);
				return ;
			}
		}
	}
	list = simple_list_newlist_gc(vm->sState,vm->pObjState);
	simple_list_addpointer_gc(vm->sState,list,pState);
	simple_list_addpointer_gc(vm->sState,list,pMethods);
	simple_list_addpointer_gc(vm->sState,list,pClass);
	/* Call Method */
	var = vm->pBlocksMap ;
	vm->pBlocksMap = pMethods ;
	vm->nCallMethod = 1 ;
	simple_vm_loadblock(vm);
	vm->nCallMethod = 0 ;
	vm->pBlocksMap = var ;
}

SIMPLE_API void simple_vm_oop_import ( VM *vm )
{
	simple_vm_oop_import2(vm,SIMPLE_VM_IR_READC);
}

SIMPLE_API void simple_vm_oop_import2 ( VM *vm,const char *cModules )
{
	int x  ;
	List *list,*list2  ;
	const char *cModules2  ;
	for ( x = 1 ; x <= simple_list_getsize(vm->pModulessMap) ; x++ ) {
		list = simple_list_getlist(vm->pModulessMap,x);
		cModules2 = simple_list_getstring(list,1);
		if ( strcmp(cModules, cModules2) == 0 ) {
			/* Get Modules Classes */
			list2 = simple_list_getlist(list,2);
			simple_vm_oop_import3(vm,list2);
			/* Set Active Modules Name */
			simple_string_set_gc(vm->sState,vm->pModulesName,cModules);
			return ;
		}
	}
	/* Error Message */
	simple_vm_error2(vm,SIMPLE_VM_ERROR_MODULENOTFOUND,cModules);
}

SIMPLE_API void simple_vm_oop_import3 ( VM *vm,List *list )
{
	int x  ;
	List *list2, *list3  ;
	/* Import Modules Classes */
	for ( x = 1 ; x <= simple_list_getsize(list) ; x++ ) {
		list2 = simple_list_getlist(list,x);
		list3 = simple_list_newlist_gc(vm->sState,vm->pClassesMap);
		simple_list_addstring_gc(vm->sState,list3,simple_list_getstring(list2,1));
		simple_list_addpointer_gc(vm->sState,list3,list2);
		simple_list_addpointer_gc(vm->sState,list3,vm->file_name);
	}
}

List * simple_vm_oop_checkpointertoclassinmodules ( VM *vm,List *list )
{
	if ( simple_list_getsize(list) == 3 ) {
		if ( simple_list_getpointer(list,3) != NULL ) {
			if ( strcmp((char *) simple_list_getpointer(list,3),vm->file_name) != 0 ) {
				return NULL ;
			}
		}
		return (List *) simple_list_getpointer(list,2) ;
	}
	return list ;
}

int simple_vm_oop_visibleclassescount ( VM *vm )
{
	List *list  ;
	if ( simple_list_getsize(vm->aActiveModules) > 0 ) {
		list = (List *) simple_list_getpointer(vm->aActiveModules,simple_list_getsize(vm->aActiveModules)) ;
		list = simple_list_getlist(list,SIMPLE_CLASSESLIST) ;
		return simple_list_getsize(vm->pClassesMap) + simple_list_getsize(list) ;
	}
	return simple_list_getsize(vm->pClassesMap) ;
}

List * simple_vm_oop_visibleclassitem ( VM *vm,int x )
{
	List *list  ;
	if ( x <= simple_list_getsize(vm->pClassesMap) ) {
		return simple_list_getlist(vm->pClassesMap,x) ;
	}
	list = (List *) simple_list_getpointer(vm->aActiveModules,simple_list_getsize(vm->aActiveModules)) ;
	list = simple_list_getlist(list,SIMPLE_CLASSESLIST) ;
	list = simple_list_getlist(list,x-simple_list_getsize(vm->pClassesMap)) ;
	return list ;
}

SIMPLE_API void simple_vm_oop_pushclassmodules ( VM *vm,List *list )
{
	List *list2  ;
	list2 = simple_list_getlist(list,SIMPLE_CLASSMAP_POINTERTOMODULE) ;
	if ( list2 != NULL ) {
		simple_list_addpointer_gc(vm->sState,vm->aActiveModules,list2);
	}
}

SIMPLE_API void simple_vm_oop_popclassmodules ( VM *vm )
{
	if ( simple_list_getsize(vm->aActiveModules) > 0 ) {
		simple_list_deleteitem_gc(vm->sState,vm->aActiveModules,simple_list_getsize(vm->aActiveModules));
	}
}

SIMPLE_API void simple_vm_oop_deletemodulessafter ( VM *vm,int x )
{
	int t  ;
	if ( x <= simple_list_getsize(vm->aActiveModules) ) {
		for ( t = simple_list_getsize(vm->aActiveModules) ; t > x ; t-- ) {
			simple_list_deleteitem_gc(vm->sState,vm->aActiveModules,t);
		}
	}
}

int simple_vm_oop_callmethodinsideclass ( VM *vm )
{
	List *list, *list2  ;
	int x  ;
	/*
	**  This block tell us if we are inside Class method during runtime or not 
	**  pObjState is used when we Call Method or We use braces { } to access object 
	**  if the size of pObjState List is 4 , then it's class method execution not brace 
	**  Braces can be used before calling class methods 
	**  Also braces can be used inside class methods to access objects 
	**  Inside class method you can access any object using { } , you can access the self object 
	**  Braces & Methods calls can be nested 
	**  Check Calling from block 
	*/
	if ( simple_list_getsize(vm->pBlockCallList) > 0 ) {
		for ( x = simple_list_getsize(vm->pBlockCallList) ; x >= 1 ; x-- ) {
			list = simple_list_getlist(vm->pBlockCallList,x);
			/* Be sure that the block is already called using ICO_CALL */
			if ( simple_list_getsize(list) >= SIMPLE_BLOCKCL_CALLERPC ) {
				if ( simple_list_getint(list,SIMPLE_BLOCKCL_METHODORBLOCK) == 0 ) {
					return 0 ;
				}
				else {
					break ;
				}
			}
		}
	}
	/*
	**  pObjState can know about method call if it's called using callmethod 
	**  Or it's called from inside { } as block 
	**  Return 1 if last item is a method 
	*/
	if ( simple_list_getsize(vm->pObjState) >= 1 ) {
		list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState)) ;
		if ( (simple_list_getsize(list) == 4) && (vm->nCallMethod == 0) ) {
			return 1 ;
		}
	}
	/* Check using braces { } to access object from a method in the Class */
	if ( simple_list_getsize(vm->pObjState) >= 2 ) {
		list = (List *) simple_list_getpointer(simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState)),SIMPLE_OBJSTATE_CLASS);
		for ( x = simple_list_getsize(vm->pObjState) - 1 ; x >= 1 ; x-- ) {
			list2 = simple_list_getlist(vm->pObjState,x);
			if ( simple_list_getsize(list2) == 4 ) {
				list2 = (List *) simple_list_getpointer(list2,SIMPLE_OBJSTATE_CLASS);
				if ( list == list2 ) {
					return 1 ;
				}
				else {
					break ;
				}
			}
		}
	}
	return 0 ;
}

SIMPLE_API void simple_vm_oop_setget ( VM *vm,List *var )
{
	List *list, *list2  ;
	Item *pItem, *pItem2  ;
	String *string, *pString2  ;
	/* Create String */
	string = simple_string_new_gc(vm->sState,"if HasBlock(simple_gettemp_var,'Get");
	simple_string_add_gc(vm->sState,string,simple_list_getstring(var,1));
	simple_string_add_gc(vm->sState,string,"')\nreturn simple_gettemp_var.'Get");
	simple_string_add_gc(vm->sState,string,simple_list_getstring(var,1));
	simple_string_add_gc(vm->sState,string,"'() end");
	/* Set Variable simple_gettemp_var  , Number 5 in Public Memory */
	list = simple_list_getlist(simple_vm_getglobalscope(vm),5) ;
	simple_list_setpointer_gc(vm->sState,list,SIMPLE_VAR_VALUE,vm->pGetSetObject);
	simple_list_setint_gc(vm->sState,list,SIMPLE_VAR_PVALUETYPE ,vm->nGetSetObjType);
	/* Check Setter & Getter for Public Attributes */
	SIMPLE_VM_IR_LOAD ;
	if ( SIMPLE_VM_IR_OPCODE != ICO_ASSIGNMENTPOINTER ) {
		SIMPLE_VM_IR_UNLOAD ;
		/*
		**  Get Property 
		**  Check to do a Stack POP for the Attribute List 
		*/
		pString2 = simple_string_new_gc(vm->sState,"Get");
		simple_string_add_gc(vm->sState,pString2,simple_list_getstring(var,1));
		/* Check Type */
		list2 = NULL ;
		if ( vm->nGetSetObjType == SIMPLE_OBJTYPE_VARIABLE ) {
			list2 = simple_list_getlist((List *) (vm->pGetSetObject),SIMPLE_VAR_VALUE ) ;
		}
		else if ( vm->nGetSetObjType == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem2 = (Item *) vm->pGetSetObject ;
			list2 = simple_item_getlist(pItem2) ;
		}
		if ( simple_vm_oop_isblock(vm,list2,simple_string_get(pString2)) ) {
			SIMPLE_VM_STACK_POP ;
		}
		simple_string_delete_gc(vm->sState,pString2);
		if ( SIMPLE_VM_IR_READIVALUE(2)  == 0 ) {
			pItem = SIMPLE_VM_IR_ITEM(2) ;
			vm->nEvalCalledFromSimpleCode = 0 ;
			vm->nRetEvalDontDelete = 1 ;
			simple_vm_exec(vm,simple_string_get(string));
			/* We don't use SIMPLE_VM_IR because Eval reallocation change mem. locations */
			simple_item_setint_gc(vm->sState,pItem,vm->nPC);
		}
		else {
			simple_vm_blockflag2(vm,vm->nPC);
			vm->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
		}
	}
	else {
		SIMPLE_VM_IR_UNLOAD ;
		/*
		**  Set Property 
		**  Delete All Items to avoid a memory leak in real time applications 
		*/
		simple_list_deleteallitems_gc(vm->sState,vm->aSetProperty);
		list = simple_list_newlist_gc(vm->sState,vm->aSetProperty);
		/* Add object pointer & Type */
		simple_list_addpointer_gc(vm->sState,list,vm->pGetSetObject);
		simple_list_addint_gc(vm->sState,list,vm->nGetSetObjType);
		/* Add property name */
		simple_list_addstring_gc(vm->sState,list,simple_list_getstring(var,1));
		/* Property Variable */
		simple_list_addpointer_gc(vm->sState,list,var);
	}
	/* Delete String */
	simple_string_delete_gc(vm->sState,string);
}

SIMPLE_API void simple_vm_oop_setproperty ( VM *vm )
{
	List *list, *list2  ;
	Item *pItem,*pItem2  ;
	String *string  ;
	/* To Access Property Data */
	if ( simple_list_getsize(vm->aSetProperty) < 1 ) {
		/* This case happens when using This.Attribute inside nested braces in a class method */
		simple_vm_assignment(vm);
		return ;
	}
	list = simple_list_getlist(vm->aSetProperty,simple_list_getsize(vm->aSetProperty));
	/* Add Before Equal Flag */
	if ( simple_list_getsize(list) == 4 ) {
		simple_list_addint_gc(vm->sState,list,vm->nBeforeEqual);
	}
	/* Before (First Time) */
	if ( SIMPLE_VM_IR_READIVALUE(1) == 0 ) {
		pItem2 = SIMPLE_VM_IR_ITEM(1) ;
		/* Set Variable simple_gettemp_var  , Number 5 in Public Memory */
		list2 = simple_list_getlist(simple_vm_getglobalscope(vm),5) ;
		simple_list_setpointer_gc(vm->sState,list2,SIMPLE_VAR_VALUE,simple_list_getpointer(list,1));
		simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_PVALUETYPE,simple_list_getint(list,2));
		/* Set Variable simple_settemp_var  , Number 7 in Public Memory */
		list2 = simple_list_getlist(simple_vm_getglobalscope(vm),7) ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_TYPE,SIMPLE_VM_NUMBER);
			simple_list_setdouble_gc(vm->sState,list2,SIMPLE_VAR_VALUE,SIMPLE_VM_STACK_READN);
			simple_list_adddouble_gc(vm->sState,list,SIMPLE_VM_STACK_READN);
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_TYPE,SIMPLE_VM_STRING);
			simple_list_setstring_gc(vm->sState,list2,SIMPLE_VAR_VALUE,SIMPLE_VM_STACK_READC);
			simple_list_addstring_gc(vm->sState,list,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
			simple_list_setpointer_gc(vm->sState,list2,SIMPLE_VAR_VALUE,SIMPLE_VM_STACK_READP);
			simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_PVALUETYPE ,SIMPLE_VM_STACK_OBJTYPE);
			simple_list_addpointer_gc(vm->sState,list,SIMPLE_VM_STACK_READP);
			simple_list_addint_gc(vm->sState,list,SIMPLE_VM_STACK_OBJTYPE);
		}
		/* Set Variable simple_tempflag_var , Number 8 in Public Memory */
		list2 = simple_list_getlist(simple_vm_getglobalscope(vm),8) ;
		simple_list_setdouble_gc(vm->sState,list2,SIMPLE_VAR_VALUE,0.0);
		/* Execute the same instruction again (next time the part "After (Second Time)" will run ) */
		vm->nPC-- ;
		if ( SIMPLE_VM_IR_READIVALUE(2)  == 0 ) {
			/* Create String */
			string = simple_string_new_gc(vm->sState,"if HasBlock(simple_gettemp_var,'Set");
			simple_string_add_gc(vm->sState,string,simple_list_getstring(list,3));
			simple_string_add_gc(vm->sState,string,"')\nsimple_gettemp_var.'Set");
			simple_string_add_gc(vm->sState,string,simple_list_getstring(list,3));
			simple_string_add_gc(vm->sState,string,"'(simple_settemp_var)\nsimple_tempflag_var = 0\nelse\nsimple_tempflag_var = 1\nend");
			/* Eval the string */
			pItem = SIMPLE_VM_IR_ITEM(2) ;
			vm->nEvalCalledFromSimpleCode = 0 ;
			vm->nRetEvalDontDelete = 1 ;
			simple_vm_exec(vm,simple_string_get(string));
			/* We don't use SIMPLE_VM_IR because Eval reallocation change mem. locations */
			simple_item_setint_gc(vm->sState,pItem,vm->nPC);
			/* Delete String */
			simple_string_delete_gc(vm->sState,string);
		}
		else {
			simple_vm_blockflag2(vm,vm->nPC);
			vm->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
		}
		/* Set Before/After SetProperty Flag To After */
		simple_item_setint_gc(vm->sState,pItem2,1);
	}
	/* After (Second Time) */
	else {
		/* Set Before/After SetProperty Flag to Before */
		SIMPLE_VM_IR_READIVALUE(1) = 0 ;
		/* Get Variable simple_tempflag_var */
		list2 = simple_list_getlist(simple_vm_getglobalscope(vm),8) ;
		if ( simple_list_getdouble(list2,3) == 1.0 ) {
			/*
			**  The set method is not found!, we have to do the assignment operation 
			**  Push Variable Then Push Value then Assignment 
			*/
			SIMPLE_VM_STACK_PUSHPVALUE(simple_list_getpointer(list,4));
			SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
			/* Restore Before Equal Flag */
			vm->nBeforeEqual = simple_list_getint(list,5) ;
			/* Push Value */
			if ( simple_list_isdouble(list,6) ) {
				SIMPLE_VM_STACK_PUSHNVALUE(simple_list_getdouble(list,6));
			}
			else if ( simple_list_isstring(list,6) ) {
				SIMPLE_VM_STACK_PUSHCVALUE(simple_list_getstring(list,6));
			}
			else if ( simple_list_ispointer(list,6) ) {
				SIMPLE_VM_STACK_PUSHPVALUE(simple_list_getpointer(list,6));
				SIMPLE_VM_STACK_OBJTYPE = simple_list_getint(list,7) ;
			}
			simple_vm_assignment(vm);
		}
		simple_list_deleteitem_gc(vm->sState,vm->aSetProperty,simple_list_getsize(vm->aSetProperty));
	}
}

List * simple_vm_oop_objvarfromobjlist ( List *list )
{
	int nType  ;
	Item *pItem  ;
	/* Get Object State List */
	list = simple_list_getlist(list,2);
	/* Get Self Attribute List */
	list = simple_list_getlist(list,1);
	/* Get Object Pointer from Self Attribute List */
	nType = simple_list_getint(list,4) ;
	if ( nType == SIMPLE_OBJTYPE_VARIABLE ) {
		list = (List *) simple_list_getpointer(list,3);
	}
	else if ( nType == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) simple_list_getpointer(list,3);
		list = (List *) simple_item_getlist(pItem) ;
	}
	return list ;
}

int simple_vm_oop_objtypefromobjlist ( List *list )
{
	int nType  ;
	/* Get Object State List */
	list = simple_list_getlist(list,2);
	/* Get Self Attribute List */
	list = simple_list_getlist(list,1);
	/* Get Object Type from Self Attribute List */
	nType = simple_list_getint(list,4) ;
	return nType ;
}

Item * simple_vm_oop_objitemfromobjlist ( List *list )
{
	Item *pItem  ;
	/* Get Object State List */
	list = simple_list_getlist(list,2);
	/* Get Self Attribute List */
	list = simple_list_getlist(list,1);
	/* Get Object Pointer from Self Attribute List */
	pItem = (Item *) simple_list_getpointer(list,3);
	return pItem ;
}

SIMPLE_API void simple_vm_oop_operatoroverloading ( VM *vm,List *pObj,const char *string_one,int nType,const char *cStr2,double nNum1,void *pointer,int nPointerType )
{
	List *list2  ;
	Item *pItem  ;
	String *string  ;
	int nObjType  ;
	nObjType = simple_vm_oop_objtypefromobjlist(pObj);
	/* Set Variable simple_gettemp_var  , Number 5 in Public Memory */
	list2 = simple_list_getlist(simple_vm_getglobalscope(vm),5) ;
	if ( nObjType == SIMPLE_OBJTYPE_VARIABLE ) {
		pObj = simple_vm_oop_objvarfromobjlist(pObj);
		simple_list_setpointer_gc(vm->sState,list2,SIMPLE_VAR_VALUE,pObj);
	}
	else if ( nObjType == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = simple_vm_oop_objitemfromobjlist(pObj);
		simple_list_setpointer_gc(vm->sState,list2,SIMPLE_VAR_VALUE,pItem);
	}
	simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_PVALUETYPE,nObjType);
	/* Set Variable simple_settemp_var  , Number 7 in Public Memory */
	list2 = simple_list_getlist(simple_vm_getglobalscope(vm),7) ;
	if ( nType == SIMPLE_OOPARA_STRING ) {
		simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_TYPE,SIMPLE_VM_STRING);
		simple_list_setstring_gc(vm->sState,list2,SIMPLE_VAR_VALUE,cStr2);
	}
	else if ( nType == SIMPLE_OOPARA_NUMBER ) {
		simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_TYPE,SIMPLE_VM_NUMBER);
		simple_list_setdouble_gc(vm->sState,list2,SIMPLE_VAR_VALUE,nNum1);
	}
	else if ( nType == SIMPLE_OOPARA_POINTER ) {
		simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
		simple_list_setpointer_gc(vm->sState,list2,SIMPLE_VAR_VALUE,pointer);
		simple_list_setint_gc(vm->sState,list2,SIMPLE_VAR_PVALUETYPE,nPointerType);
	}
	if ( SIMPLE_VM_IR_READIVALUE(1) == 0 ) {
		/* Create String */
		string = simple_string_new_gc(vm->sState,"if HasBlock(simple_gettemp_var,'Operator')\nreturn simple_gettemp_var.Operator('");
		simple_string_add_gc(vm->sState,string,string_one);
		simple_string_add_gc(vm->sState,string,"',simple_settemp_var)\nelse\n__throw('Object does not support Operator overloading')\nend\n");
		/* Eval the string */
		pItem = SIMPLE_VM_IR_ITEM(1) ;
		vm->nEvalCalledFromSimpleCode = 0 ;
		vm->nRetEvalDontDelete = 1 ;
		simple_vm_exec(vm,simple_string_get(string));
		/* We don't use SIMPLE_VM_IR because Eval reallocation change mem. locations */
		simple_item_setint_gc(vm->sState,pItem,vm->nPC);
		/* Delete String */
		simple_string_delete_gc(vm->sState,string);
	}
	else {
		simple_vm_blockflag2(vm,vm->nPC);
		vm->nPC = SIMPLE_VM_IR_READIVALUE(1) ;
	}
}

SIMPLE_API void simple_vm_oop_callmethodfrombrace ( VM *vm )
{
	List *list,*list2  ;
	const char *cStr  ;
	/*
	**  We uses AfterCallMethod2 instead of AfterCallMethod to avoid conflict with normal method call 
	**  AfterCallMethod2 is the same instruction as AfterCallMethod 
	**  Change NOOP to After Call Method2 
	*/
	SIMPLE_VM_IR_LOAD ;
	if ( (SIMPLE_VM_IR_OPCODE == ICO_NOOP) || (SIMPLE_VM_IR_OPCODE == ICO_AFTERCALLMETHOD2) ) {
		SIMPLE_VM_IR_OPCODE = ICO_AFTERCALLMETHOD2 ;
		list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState)) ;
		/* Pass Brace when we call class Init , using new object() */
		if ( (simple_list_getsize(vm->pObjState) > 1) && (vm->nCallClassInit) ) {
			if ( simple_list_getsize(vm->pBlockCallList) > 0 ) {
				list2 = simple_list_getlist(vm->pBlockCallList,simple_list_getsize(vm->pBlockCallList));
				cStr = simple_list_getstring(list2,SIMPLE_BLOCKCL_NAME);
				if ( strcmp(cStr,"Init") != 0 ) {
					list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState)-1) ;
				}
			}
			else {
				list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState)-1) ;
			}
		}
		list2 = simple_list_newlist_gc(vm->sState,vm->pObjState);
		simple_list_copy(list2,list);
		/* Add Logical Value (True) , That we are inside the class method */
		simple_list_addint_gc(vm->sState,list2,1);
		/* Push Class Modules */
		list = (List *) simple_list_getpointer(list2,SIMPLE_OBJSTATE_CLASS);
		simple_vm_oop_pushclassmodules(vm,list);
	}
	SIMPLE_VM_IR_UNLOAD ;
}

int simple_vm_oop_isblock ( VM *vm,List *list,const char *cStr )
{
	List *list2,*list3  ;
	int x  ;
	/* Get Object Class */
	list = (List *) simple_list_getpointer(list,1);
	/* Get Class Methods */
	list2 = simple_list_getlist(list,4);
	/* Get Parent Classes Methods */
	simple_vm_oop_parentmethods(vm,list);
	/* Find the Method */
	if ( simple_list_getsize(list2) > 0 ) {
		for ( x = 1 ; x <= simple_list_getsize(list2) ; x++ ) {
			list3 = simple_list_getlist(list2,x);
			if ( strcmp(simple_list_getstring(list3,SIMPLE_BLOCKMAP_NAME),cStr) == 0 ) {
				if ( simple_list_getint(list3,SIMPLE_BLOCKMAP_PRIVATEFLAG) ) {
					return 2 ;
				}
				return 1 ;
			}
		}
	}
	return 0 ;
}

SIMPLE_API void simple_vm_oop_updateselfpointer ( VM *vm,List *pObj,int nType,void *pContainer )
{
	List *list  ;
	/* Get Object State */
	list = simple_list_getlist(pObj,2);
	/* Get Self Attribute */
	list = simple_list_getlist(list,1);
	/* Set Object Pointer */
	simple_list_setpointer_gc(vm->sState,list,3, pContainer);
	/* Set Object Type */
	simple_list_setint_gc(vm->sState,list,4,nType);
}

SIMPLE_API void simple_vm_oop_setthethisvariable ( VM *vm )
{
	List *list, *pThis  ;
	pThis = simple_list_getlist(simple_vm_getglobalscope(vm),SIMPLE_VM_STATICVAR_THIS) ;
	if ( (simple_list_getsize(vm->pObjState) < 1) || (simple_vm_oop_callmethodinsideclass(vm) == 0) ) {
		simple_list_setpointer_gc(vm->sState,pThis,SIMPLE_VAR_VALUE,NULL);
		simple_list_setint_gc(vm->sState,pThis,SIMPLE_VAR_PVALUETYPE,0);
		return ;
	}
	list = simple_list_getlist(vm->pObjState,simple_list_getsize(vm->pObjState));
	/* Get Object Scope */
	list = simple_list_getlist(list,SIMPLE_OBJSTATE_SCOPE);
	if ( list == NULL ) {
		simple_list_setpointer_gc(vm->sState,pThis,SIMPLE_VAR_VALUE,NULL);
		simple_list_setint_gc(vm->sState,pThis,SIMPLE_VAR_PVALUETYPE,0);
		return ;
	}
	/* Get Self Attribute List */
	list = simple_list_getlist(list,1);
	/* Save this */
	simple_list_setpointer_gc(vm->sState,pThis,SIMPLE_VAR_VALUE,simple_list_getpointer(list,SIMPLE_VAR_VALUE));
	simple_list_setint_gc(vm->sState,pThis,SIMPLE_VAR_PVALUETYPE,simple_list_getint(list,SIMPLE_VAR_PVALUETYPE));
}

SIMPLE_API void simple_vm_oop_updateselfpointer2 ( VM *vm, List *list )
{
	Item *pItem  ;
	int x,lFound  ;
	List *pRecord  ;
	/*
	**  This block will create new item 
	**  Then Add the Object List Pointer to this temp item 
	**  Then update the self pointer to use this item pointer 
	**  This fix the self pointer before usage using braces { } or methods calls 
	**  This is important because there are use cases where updateselfpointer is not enough 
	**  So we need updateselfpointer2 to avoid dangling pointer problems as a result of 
	**  Self pointer that point to deleted items/variables/objects 
	**  Create The Temp. Item 
	**  Try to find the item, or create it if it's not found 
	*/
	lFound = 0 ;
	for ( x = 1 ; x <= simple_list_getsize(vm->aDynamicSelfItems) ; x++ ) {
		pRecord = simple_list_getlist(vm->aDynamicSelfItems,x);
		if ( simple_list_getint(pRecord,1) == vm->nPC ) {
			pItem = (Item *) simple_list_getpointer(pRecord,2);
			lFound = 1 ;
			break ;
		}
	}
	if ( lFound == 0 ) {
		pRecord = simple_list_newlist_gc(vm->sState,vm->aDynamicSelfItems);
		simple_list_addint_gc(vm->sState,pRecord,vm->nPC);
		pItem = simple_item_new(ITEMTYPE_NOTHING);
		simple_list_addpointer_gc(vm->sState,pRecord,pItem);
		simple_item_settype_gc(vm->sState,pItem,ITEMTYPE_LIST);
		simple_state_free(vm->sState,pItem->data.list);
		pItem->gc.nReferenceCount++ ;
	}
	/* Set the pointer */
	pItem->data.list = list ;
	/* Update The Self Pointer */
	simple_vm_oop_updateselfpointer(vm,list,SIMPLE_OBJTYPE_LISTITEM,pItem);
}
