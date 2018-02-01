/*
**  Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> 
**  pClassesMap ( cClass Name ,  iPC , cParentClass, aMethodsList , nFlagIsParentClassInformation 
**  pClassesMap ( cClass Name, Pointer to List that represent class inside a Package, Pointer to File 
**  pFunctionsMap ( Name, PC, FileName, Private Flag ) 
**  Packages List ( Package Name , Classes List ) 
**  Object ( is a list of two items , (1) Class Pointer  (2) Object Data  ) 
**  pVM->aScopeNewObj : (1) Previous scope (2) nListStart (3) pNestedLists (4) nSP 
**  pVM->pObjState  (  [ Pointer to Scope, Pointer to Methods , Pointer to Classs, Optional True) 
**  The optional True used with LoadMethod so we can Know that we are inside class method during RT 
**  We don't check the True value, we just check that the size of the list is 4 
**  used in simple_vmfuncs , function simple_vm_loadfunc2() 
**  used in simple_vmvars , function simple_vm_findvar2() 
**  pBraceObject : The list that represent the object directly (not varaible/list item) 
**  aBraceObjects ( pBraceObject, nSP, nListStart, pNestedLists) 
**  aSetProperty ( Object Pointer , Type (Variable/ListItem)  , Property Name, Property Variable , nBeforeEqual) 
*/
#include "../includes/simple.h"
/* Functions */

void simple_vm_oop_newobj ( VM *pVM )
{
	const char *cClassName,*cClassName2  ;
	int x,nLimit,nClassPC,nType,nCont  ;
	List *pList,*pList2,*pList3,*pList4,*pList5,*pVar,*pSelf  ;
	Item *pItem  ;
	const char *cTempName = SIMPLE_TEMP_OBJECT ;
	pList2 = NULL ;
	pVar = NULL ;
	pItem = NULL ;
	cClassName = SIMPLE_VM_IR_READC ;
	nLimit = simple_vm_oop_visibleclassescount(pVM);
	if ( nLimit > 0 ) {
		for ( x = 1 ; x <= nLimit ; x++ ) {
			pList = simple_vm_oop_visibleclassitem(pVM,x);
			cClassName2 = simple_list_getstring(pList,1);
			pList = simple_vm_oop_checkpointertoclassinpackage(pVM,pList);
			if ( pList == NULL ) {
				continue ;
			}
			nClassPC = simple_list_getint(pList,2);
			if ( strcmp(cClassName,cClassName2) == 0 ) {
				/* Check Assignment */
				nCont = 1 ;
				if ( SIMPLE_VM_STACK_ISPOINTER ) {
					if ( pVM->pAssignment == SIMPLE_VM_STACK_READP ) {
						nCont = 0 ;
					}
				}
				if ( pVM->nFuncExecute > 0 ) {
					nCont = 1 ;
				}
				if ( nCont == 1 ) {
					simple_vm_newvar(pVM,cTempName);
					pVar = (List *) SIMPLE_VM_STACK_READP ;
					nType = SIMPLE_VM_STACK_OBJTYPE ;
					simple_list_setint_gc(pVM->pRingState,pVar,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
					simple_list_setlist_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE);
					pList2 = simple_list_getlist(pVar,SIMPLE_VAR_VALUE);
				}
				else {
					/* Prepare Object List */
					if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
						pVar = (List *) SIMPLE_VM_STACK_READP ;
						simple_list_setint_gc(pVM->pRingState,pVar,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
						simple_list_setlist_gc(pVM->pRingState,pVar,SIMPLE_VAR_VALUE);
						pList2 = simple_list_getlist(pVar,SIMPLE_VAR_VALUE);
					}
					else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
						pItem = (Item *) SIMPLE_VM_STACK_READP ;
						simple_item_settype_gc(pVM->pRingState,pItem,ITEMTYPE_LIST);
						pVar = simple_item_getlist(pItem);
						pList2 = pVar ;
					}
					nType = SIMPLE_VM_STACK_OBJTYPE ;
				}
				simple_list_deleteallitems_gc(pVM->pRingState,pList2);
				/* Push Class Package */
				simple_vm_oop_pushclasspackage(pVM,pList);
				/* Store the Class Pointer in the Object Data */
				simple_list_addpointer_gc(pVM->pRingState,pList2,pList);
				/* Create List for the Object State */
				pList3 = simple_list_newlist_gc(pVM->pRingState,pList2);
				/* Create Self variable in the state list */
				pSelf = simple_vm_newvar2(pVM,"self",pList3);
				simple_list_setint_gc(pVM->pRingState,pSelf,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
				if ( nType == SIMPLE_OBJTYPE_VARIABLE ) {
					simple_list_setpointer_gc(pVM->pRingState,pSelf,SIMPLE_VAR_VALUE,pVar);
				}
				else if ( nType == SIMPLE_OBJTYPE_LISTITEM ) {
					simple_list_setpointer_gc(pVM->pRingState,pSelf,SIMPLE_VAR_VALUE,pItem);
				}
				simple_list_setint_gc(pVM->pRingState,pSelf,SIMPLE_VAR_PVALUETYPE ,nType);
				/* Jump to Class INIT Method */
				simple_vm_blockflag2(pVM,pVM->nPC);
				/* Execute Parent Classes Init first */
				if ( strcmp(simple_list_getstring(pList,3),"") != 0 ) {
					simple_vm_blockflag2(pVM,nClassPC);
					simple_vm_oop_parentinit(pVM,pList);
				}
				else {
					pVM->nPC = nClassPC ;
				}
				/* Save the current Scope, List and Stack */
				pList4 = simple_list_newlist_gc(pVM->pRingState,pVM->aScopeNewObj);
				simple_list_addpointer_gc(pVM->pRingState,pList4,pVM->pActiveMem);
				/* Store List information to allow calling function from list item and creating lists from that funct */
				simple_list_addint_gc(pVM->pRingState,pList4,pVM->nListStart);
				simple_list_addpointer_gc(pVM->pRingState,pList4,pVM->pNestedLists);
				pVM->nListStart = 0 ;
				pVM->pNestedLists = simple_list_new_gc(pVM->pRingState,0);
				/* Save Stack Information */
				simple_list_addint_gc(pVM->pRingState,pList4,pVM->nSP);
				/* Save FuncExecute */
				simple_list_addint_gc(pVM->pRingState,pList4,pVM->nFuncExecute);
				pVM->nFuncExecute = 0 ;
				/* Save Private Flag Status */
				simple_list_addint_gc(pVM->pRingState,pList4,pVM->nPrivateFlag);
				/* Save InsideBrace Flag */
				simple_list_addint_gc(pVM->pRingState,pList4,pVM->nInsideBraceFlag);
				pVM->nInsideBraceFlag = 0 ;
				simple_list_addpointer_gc(pVM->pRingState,pList4,pVM->pBraceObject);
				/* Save nCallClassInit */
				simple_list_addint_gc(pVM->pRingState,pList4,pVM->nCallClassInit);
				pVM->nCallClassInit = 0 ;
				/* Save Line Number */
				simple_list_addint_gc(pVM->pRingState,pList4,pVM->nLineNumber);
				/* Save Function Stack */
				simple_list_addint_gc(pVM->pRingState,pList4,pVM->nFuncSP);
				/* Save Assignment Pointer */
				simple_list_addpointer_gc(pVM->pRingState,pList4,pVM->pAssignment);
				/* Save the Object Pointer and Type */
				simple_list_addpointer_gc(pVM->pRingState,pList4,SIMPLE_VM_STACK_READP);
				simple_list_addint_gc(pVM->pRingState,pList4,SIMPLE_VM_STACK_OBJTYPE);
				/* Save Current Global Scope */
				simple_list_addint_gc(pVM->pRingState,pList4,pVM->nCurrentGlobalScope);
				/* Set Object State as the Current Scope */
				pVM->pActiveMem = pList3 ;
				/* Prepare to Make Object State & Methods visible while executing the INIT method */
				pList5 = simple_list_newlist_gc(pVM->pRingState,pVM->pObjState);
				simple_list_addpointer_gc(pVM->pRingState,pList5,pList3);
				simple_list_addpointer_gc(pVM->pRingState,pList5,NULL);
				simple_list_addpointer_gc(pVM->pRingState,pList5,pList);
				/* Create the Super Virtual Object */
				simple_vm_oop_newsuperobj(pVM,pList3,pList);
				/* Enable NULL variables (To be class attributes) */
				pVM->nInClassRegion++ ;
				/* Support using Braces to access the object state */
				pVM->pBraceObject = pList2 ;
				return ;
			}
		}
	}
	simple_vm_error2(pVM,SIMPLE_VM_ERROR_CLASSNOTFOUND,cClassName);
}

void simple_vm_oop_parentinit ( VM *pVM,List *pList )
{
	const char *cClassName,*cClassName2  ;
	int x,x2,nFound,nMark  ;
	List *pList2, *pClassesList  ;
	char *pString  ;
	/* Get the parent class name from the Class List Pointer */
	cClassName = simple_list_getstring(pList,3) ;
	/* Create List for Classes Pointers */
	pClassesList = simple_list_new_gc(pVM->pRingState,0);
	simple_list_addpointer_gc(pVM->pRingState,pClassesList,pList);
	while ( strcmp(cClassName,"") != 0 ) {
		/* Mark Packages Count */
		nMark = simple_list_getsize(pVM->aActivePackage);
		nFound = 0 ;
		for ( x = 1 ; x <= simple_vm_oop_visibleclassescount(pVM) ; x++ ) {
			pList2 = simple_vm_oop_visibleclassitem(pVM,x);
			cClassName2 = simple_list_getstring(pList2,1) ;
			pList2 = simple_vm_oop_checkpointertoclassinpackage(pVM,pList2);
			if ( pList2 == NULL ) {
				continue ;
			}
			if ( strcmp(cClassName,cClassName2) == 0 ) {
				/* Check that the parent class is not one of the subclasses */
				for ( x2 = 1 ; x2  <= simple_list_getsize(pClassesList) ; x2++ ) {
					if ( ((List *) simple_list_getpointer(pClassesList,x2)) == pList2 ) {
						pString = simple_stsimple_new_gc(pVM->pRingState,"When creating class ");
						simple_stsimple_add_gc(pVM->pRingState,pString,simple_list_getstring(pList,1));
						simple_stsimple_add_gc(pVM->pRingState,pString," from class ");
						simple_stsimple_add_gc(pVM->pRingState,pString,cClassName);
						simple_vm_error2(pVM,SIMPLE_VM_ERROR_PARENTCLASSLIKESUBCLASS,simple_stsimple_get(pString));
						simple_stsimple_delete_gc(pVM->pRingState,pString);
						/* Delete Classes Pointers List */
						simple_list_delete_gc(pVM->pRingState,pClassesList);
						return ;
					}
				}
				simple_list_addpointer_gc(pVM->pRingState,pClassesList,pList2);
				/* Push Class Package */
				simple_vm_oop_pushclasspackage(pVM,pList2);
				cClassName = simple_list_getstring(pList2,3) ;
				if ( strcmp(cClassName,"") != 0 ) {
					/* Add Class Init Method to be called */
					simple_vm_blockflag2(pVM,simple_list_getint(pList2,2));
				}
				else {
					pVM->nPC = simple_list_getint(pList2,2) ;
				}
				nFound = 1 ;
				break ;
			}
		}
		if ( nFound == 0 ) {
			/* Error Message */
			simple_vm_error2(pVM,SIMPLE_VM_ERROR_PARENTCLASSNOTFOUND,cClassName);
			break ;
		}
		/* Restore Mark */
		simple_vm_oop_deletepackagesafter(pVM,nMark);
		pList = pList2 ;
	}
	/* Delete Classes Pointers List */
	simple_list_delete_gc(pVM->pRingState,pClassesList);
}

void simple_vm_oop_newclass ( VM *pVM )
{
	List *pClass,*pList  ;
	int x  ;
	pClass = (List *) SIMPLE_VM_IR_READPVALUE(2) ;
	/* Find the Class Pointer using the Class Name */
	if ( pClass == NULL ) {
		for ( x = 1 ; x <= simple_list_getsize(pVM->pRingState->pRingClassesMap) ; x++ ) {
			pList = simple_list_getlist(pVM->pRingState->pRingClassesMap,x);
			if ( strcmp(simple_list_getstring(pList,1),SIMPLE_VM_IR_READCVALUE(1)) == 0 ) {
				if ( simple_list_getsize(pList) == 3 ) {
					/* Here the class is stored inside a package - we have the class pointer (item 2) */
					pClass = (List *) simple_list_getpointer(pList,2) ;
				}
				else {
					pClass = pList ;
				}
				SIMPLE_VM_IR_READPVALUE(2) = (void *) pClass ;
				break ;
			}
		}
	}
	pClass = simple_vm_oop_checkpointertoclassinpackage(pVM,pClass);
	/* Make object methods visible while executing the Class Init method */
	pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState));
	simple_list_setpointer_gc(pVM->pRingState,pList,2,simple_list_getlist(pClass,4));
	/* Get Parent Classes Methods */
	simple_vm_oop_parentmethods(pVM,pClass);
	/* Attributes Scope is Public */
	pVM->nPrivateFlag = 0 ;
}

void simple_vm_oop_setscope ( VM *pVM )
{
	List *pList  ;
	/* This function called after creating new object and executing class init */
	pList = simple_list_getlist(pVM->aScopeNewObj,simple_list_getsize(pVM->aScopeNewObj)) ;
	/*
	**  Restore State 
	**  Restore Stack Information 
	*/
	pVM->nSP = simple_list_getint(pList,4) ;
	/* Restore FuncExecute */
	pVM->nFuncExecute = simple_list_getint(pList,5) ;
	/* Restore Private Flag */
	pVM->nPrivateFlag = simple_list_getint(pList,6) ;
	/* Restore InsideBrace Flag */
	pVM->nInsideBraceFlag = simple_list_getint(pList,7) ;
	pVM->pBraceObject = (List *) simple_list_getpointer(pList,8) ;
	/* Restore nCallClassInit */
	pVM->nCallClassInit = simple_list_getint(pList,9) ;
	/* Restore nLineNumber */
	pVM->nLineNumber = simple_list_getint(pList,10) ;
	/* Restore Function Stack */
	pVM->nFuncSP = simple_list_getint(pList,11) ;
	/* Restore Assignment Pointer */
	pVM->pAssignment = (List *) simple_list_getpointer(pList,12) ;
	/* Restore the scope (before creating the object using new) */
	pVM->pActiveMem = (List *) simple_list_getpointer(pList,1) ;
	/* Restore List Status */
	pVM->nListStart = simple_list_getint(pList,2) ;
	if ( pVM->pNestedLists != simple_list_getpointer(pList,3) ) {
		pVM->pNestedLists = simple_list_delete_gc(pVM->pRingState,pVM->pNestedLists);
		pVM->pNestedLists = (List *) simple_list_getpointer(pList,3) ;
	}
	/* Restore the Object Pointer and The Object Type */
	SIMPLE_VM_STACK_SETPVALUE(simple_list_getpointer(pList,13));
	SIMPLE_VM_STACK_OBJTYPE = simple_list_getint(pList,14) ;
	/* Restore current Global Scope */
	pVM->nCurrentGlobalScope = simple_list_getint(pList,15);
	/* After init methods */
	simple_vm_oop_aftercallmethod(pVM);
	simple_list_deleteitem_gc(pVM->pRingState,pVM->aScopeNewObj,simple_list_getsize(pVM->aScopeNewObj));
	/* Disable NULL variables (To be class attributes) */
	pVM->nInClassRegion-- ;
	/* POP Class Package */
	simple_vm_oop_popclasspackage(pVM);
}

int simple_vm_oop_isobject ( List *pList )
{
	if ( pList == NULL ) {
		return 0 ;
	}
	if ( simple_list_getsize(pList) != 2 ) {
		return 0 ;
	}
	if ( simple_list_ispointer(pList,1) == 0 ) {
		return 0 ;
	}
	if ( simple_list_islist(pList,2) == 0 ) {
		return 0 ;
	}
	return 1 ;
}

List * simple_vm_oop_getobj ( VM *pVM )
{
	List *pVar  ;
	Item *pItem  ;
	pVar = NULL ;
	/* Get Object Data */
	if ( ! SIMPLE_VM_STACK_ISPOINTER ) {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_NOTOBJECT);
		return NULL ;
	}
	if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
		pVar = (List *) SIMPLE_VM_STACK_READP ;
		if ( simple_list_getint(pVar,SIMPLE_VAR_TYPE) == SIMPLE_VM_NULL ) {
			simple_vm_error2(pVM,SIMPLE_VM_ERROR_USINGNULLVARIABLE,simple_list_getstring(pVar,SIMPLE_VAR_NAME));
			return NULL ;
		}
		if ( ! simple_list_islist(pVar,SIMPLE_VAR_VALUE  ) ) {
			simple_vm_error(pVM,SIMPLE_VM_ERROR_NOTOBJECT);
			return NULL ;
		}
		pVar = simple_list_getlist(pVar,SIMPLE_VAR_VALUE);
	}
	else if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) SIMPLE_VM_STACK_READP ;
		pVar = simple_item_getlist(pItem);
	}
	if ( simple_vm_oop_isobject(pVar) == 0 ) {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_NOTOBJECT);
		return NULL ;
	}
	SIMPLE_VM_STACK_POP ;
	return pVar ;
}

void simple_vm_oop_property ( VM *pVM )
{
	List *pVar,*pScope  ;
	/* Get Object Pointer Before being a list by getobj */
	if ( SIMPLE_VM_STACK_ISPOINTER ) {
		pVM->pGetSetObject = SIMPLE_VM_STACK_READP ;
		pVM->nGetSetObjType = SIMPLE_VM_STACK_OBJTYPE ;
	}
	/* Get Object Data */
	pVar = simple_vm_oop_getobj(pVM);
	if ( pVar == NULL ) {
		return ;
	}
	/* Get Object State */
	pScope = pVM->pActiveMem ;
	pVM->pActiveMem = simple_list_getlist(pVar,2);
	pVM->nGetSetProperty = 1 ;
	if ( simple_vm_findvar(pVM, SIMPLE_VM_IR_READC ) == 0 ) {
		/* Create the attribute if we are in the class region after the class name */
		if ( pVM->nInClassRegion ) {
			simple_vm_newvar(pVM, SIMPLE_VM_IR_READC);
			/* Support for Private Flag */
			simple_list_setint_gc(pVM->pRingState,(List *) SIMPLE_VM_STACK_READP,SIMPLE_VAR_PRIVATEFLAG,pVM->nPrivateFlag);
			SIMPLE_VM_STACK_POP ;
			simple_vm_findvar(pVM, SIMPLE_VM_IR_READC);
			pVM->pActiveMem = pScope ;
			pVM->nGetSetProperty = 0 ;
			pVM->pGetSetObject = NULL ;
			return ;
		}
		pVM->pActiveMem = pScope ;
		pVM->nGetSetProperty = 0 ;
		pVM->pGetSetObject = NULL ;
		if ( pVM->nActiveCatch == 0 ) {
			/*
			**  We check nActiveCatch because we may have error "accessing private attribute' 
			**  while we are using simple_vm_findvar 
			**  And we are using try catch done in the code 
			**  In this case we don't add another error message 
			**  So the try catch done can work as expected and avoid the need to another one 
			**  Error Message 
			*/
			simple_vm_error2(pVM,SIMPLE_VM_ERROR_PROPERTYNOTFOUND,SIMPLE_VM_IR_READC);
		}
		return ;
	}
	pVM->pActiveMem = pScope ;
	pVM->nGetSetProperty = 0 ;
	pVM->pGetSetObject = NULL ;
}

void simple_vm_oop_loadmethod ( VM *pVM )
{
	List *pVar,*pList,*pList2,*pList3,*pSuper  ;
	int lResult  ;
	/* Check calling method related to Parent Class */
	pSuper = simple_vm_oop_getsuperobj(pVM);
	if ( pSuper != NULL ) {
		simple_vm_oop_loadsuperobjmethod(pVM,pSuper);
		/* Move list from pObjState to aBeforeObjState */
		simple_vm_oop_movetobeforeobjstate(pVM);
		return ;
	}
	/* Get Object Data */
	pVar = simple_vm_oop_getobj(pVM);
	if ( pVar == NULL ) {
		return ;
	}
	/* Update Self Pointer Using Temp. Item */
	simple_vm_oop_updateselfpointer2(pVM,pVar);
	/* Get Object Class */
	pList = (List *) simple_list_getpointer(pVar,1);
	/* Push Class Package */
	simple_vm_oop_pushclasspackage(pVM,pList);
	/* Get Object State */
	pList2 = simple_list_newlist_gc(pVM->pRingState,pVM->pObjState);
	simple_list_addpointer_gc(pVM->pRingState,pList2,simple_list_getlist(pVar,2));
	/* Get Class Methods */
	pList3 = simple_list_getlist(pList,4);
	simple_list_addpointer_gc(pVM->pRingState,pList2,pList3);
	/* Add Pointer to Class */
	simple_list_addpointer_gc(pVM->pRingState,pList2,pList);
	/* Add Logical Value (True) , That we are inside the class method */
	simple_list_addint_gc(pVM->pRingState,pList2,1);
	/* Get Parent Classes Methods */
	simple_vm_oop_parentmethods(pVM,pList);
	/* Call Method */
	pVar = pVM->pFunctionsMap ;
	pVM->pFunctionsMap = pList3 ;
	pVM->nCallMethod = 1 ;
	lResult = simple_vm_loadfunc(pVM);
	pVM->nCallMethod = 0 ;
	pVM->pFunctionsMap = pVar ;
	/* Move list from pObjState to aBeforeObjState */
	if ( lResult ) {
		simple_vm_oop_movetobeforeobjstate(pVM);
	}
}

void simple_vm_oop_movetobeforeobjstate ( VM *pVM )
{
	List *pList, *pList2  ;
	if ( pVM->nActiveCatch == 1 ) {
		/* Try/Catch restore aObjState and may become empty */
		return ;
	}
	/* Move list from pObjState to aBeforeObjState */
	pList = simple_list_newlist_gc(pVM->pRingState,pVM->aBeforeObjState);
	pList2 = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState));
	simple_list_copy(pList,pList2);
	simple_list_deleteitem_gc(pVM->pRingState,pVM->pObjState,simple_list_getsize(pVM->pObjState));
}

void simple_vm_oop_parentmethods ( VM *pVM,List *pList )
{
	const char *cClassName,*cClassName2  ;
	int x,nFound,nMark  ;
	List *pList3,*pList4  ;
	pList3 = simple_list_getlist(pList,4);
	if ( simple_list_getint(pList,5) == 0 ) {
		simple_list_setint_gc(pVM->pRingState,pList,5,1);
		cClassName = simple_list_getstring(pList,3) ;
		/* Mark Packages Count */
		nMark = simple_list_getsize(pVM->aActivePackage);
		while ( strcmp(cClassName,"") != 0 ) {
			/* Push Class Package */
			simple_vm_oop_pushclasspackage(pVM,pList);
			nFound = 0 ;
			for ( x = 1 ; x <= simple_vm_oop_visibleclassescount(pVM) ; x++ ) {
				pList4 = simple_vm_oop_visibleclassitem(pVM,x);
				cClassName2 = simple_list_getstring(pList4,1) ;
				/* Prev. Step must be before Next. step - We check the name include the pacakge */
				pList4 = simple_vm_oop_checkpointertoclassinpackage(pVM,pList4);
				if ( pList4 == NULL ) {
					continue ;
				}
				if ( strcmp(cClassName,cClassName2) == 0 ) {
					/* Push Class Package */
					simple_vm_oop_pushclasspackage(pVM,pList4);
					simple_list_copy(pList3,simple_list_getlist(pList4,4));
					cClassName = simple_list_getstring(pList4,3) ;
					nFound = 1 ;
					break ;
				}
			}
			if ( nFound == 0 ) {
				simple_vm_error(pVM,SIMPLE_VM_ERROR_PARENTCLASSNOTFOUND);
				break ;
			}
			/* Exit when the parent class already contains it's parent classes data */
			if ( simple_list_getint(pList,5) == 1 ) {
				break ;
			}
		}
		/* Restore Mark */
		simple_vm_oop_deletepackagesafter(pVM,nMark);
	}
}

void simple_vm_oop_aftercallmethod ( VM *pVM )
{
	if ( simple_list_getsize(pVM->pObjState) != 0 ) {
		simple_list_deleteitem_gc(pVM->pRingState,pVM->pObjState,simple_list_getsize(pVM->pObjState));
	}
	/* POP Class Package */
	simple_vm_oop_popclasspackage(pVM);
}

void simple_vm_oop_printobj ( VM *pVM,List *pList )
{
	List *pList2,*pList3  ;
	int x  ;
	char cStr[100]  ;
	pList = simple_list_getlist(pList,2);
	for ( x = 3 ; x <= simple_list_getsize(pList) ; x++ ) {
		pList2 = simple_list_getlist(pList,x);
		printf( "%s: " , simple_list_getstring(pList2,1) ) ;
		if ( simple_list_isstring(pList2,3) ) {
			printf( "%s\n" , simple_list_getstring(pList2,3) ) ;
		}
		else if ( simple_list_isnumber(pList2,3) ) {
			if ( pVM != NULL ) {
				simple_vm_numtostring(pVM,simple_list_getdouble(pList2,3),cStr);
				printf( "%s\n" ,cStr ) ;
			}
			else {
				printf( "%f\n" , simple_list_getdouble(pList2,3) ) ;
			}
		}
		else if ( simple_list_islist(pList2,3) ) {
			pList3 = simple_list_getlist(pList2,3) ;
			if ( simple_vm_oop_isobject(pList3) ) {
				printf( "Object...\n" ) ;
			}
			else {
				printf( "[This Attribute Contains A List]\n" ) ;
			}
		}
	}
}

void simple_vm_oop_setbraceobj ( VM *pVM,List *pList )
{
	/* Support using { } to access object after object name */
	if ( simple_vm_oop_isobject(pList) ) {
		pVM->pBraceObject = pList ;
	}
}

void simple_vm_oop_bracestart ( VM *pVM )
{
	List *pList,*pClass  ;
	/* Check Error */
	if ( pVM->pBraceObject == NULL ) {
		simple_vm_error(pVM,SIMPLE_VM_ERROR_BRACEWITHOUTOBJECT);
		return ;
	}
	/* Prepare to Access Object State */
	pList = simple_list_newlist_gc(pVM->pRingState,pVM->pObjState);
	/* Store Pointer to Object State */
	simple_list_addpointer_gc(pVM->pRingState,pList,simple_list_getlist(pVM->pBraceObject,2));
	/* Store Object Class Methods */
	pClass = (List *) simple_list_getpointer(pVM->pBraceObject,1) ;
	simple_list_addpointer_gc(pVM->pRingState,pList,simple_list_getlist(pClass,4));
	/* Store Class Pointer */
	simple_list_addpointer_gc(pVM->pRingState,pList,pClass);
	/* Add Brace Object & Stack Pointer to List */
	pList = simple_list_newlist_gc(pVM->pRingState,pVM->aBraceObjects);
	simple_list_addpointer(pList,pVM->pBraceObject);
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nSP);
	/* Store List information to allow using braces from list item and creating lists from that brace */
	simple_list_addint_gc(pVM->pRingState,pList,pVM->nListStart);
	simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pNestedLists);
	pVM->nListStart = 0 ;
	pVM->pNestedLists = simple_list_new_gc(pVM->pRingState,0);
	/* Update Self Pointer Using Temp. Item */
	simple_vm_oop_updateselfpointer2(pVM,pVM->pBraceObject);
	pVM->pBraceObject = NULL ;
	pVM->nInsideBraceFlag = 1 ;
}

void simple_vm_oop_braceend ( VM *pVM )
{
	List *pList  ;
	/* Restore List Status */
	pList = simple_list_getlist(pVM->aBraceObjects,simple_list_getsize(pVM->aBraceObjects)) ;
	pVM->nListStart = simple_list_getint(pList,3) ;
	if ( pVM->pNestedLists != simple_list_getpointer(pList,4) ) {
		pVM->pNestedLists = simple_list_delete_gc(pVM->pRingState,pVM->pNestedLists);
		pVM->pNestedLists = (List *) simple_list_getpointer(pList,4) ;
	}
	/* Restore Stack Status */
	pVM->nSP = simple_list_getint(pList,2) ;
	simple_list_deleteitem_gc(pVM->pRingState,pVM->aBraceObjects,simple_list_getsize(pVM->aBraceObjects));
	simple_list_deleteitem_gc(pVM->pRingState,pVM->pObjState,simple_list_getsize(pVM->pObjState));
	if ( simple_list_getsize(pVM->aBraceObjects) > 0 ) {
		pVM->pBraceObject = simple_list_getlist(pVM->aBraceObjects,simple_list_getsize(pVM->aBraceObjects)) ;
		pVM->pBraceObject = (List *) simple_list_getpointer(pVM->pBraceObject,1) ;
		pVM->nInsideBraceFlag = 1 ;
	}
	else {
		pVM->nInsideBraceFlag = 0 ;
	}
}

void simple_vm_oop_bracestack ( VM *pVM )
{
	pVM->nSP = simple_list_getint(simple_list_getlist(pVM->aBraceObjects,simple_list_getsize(pVM->aBraceObjects)),2) ;
	if ( pVM->nFuncSP > pVM->nSP ) {
		/*
		**  This fixes a problem when we use oObject {  eval(code) } return cString 
		**  Where pVM->nSP maybe less than pVM->nFuncSP while we are inside function 
		*/
		if ( simple_list_getsize(pVM->pFuncCallList) > 0 ) {
			pVM->nSP = pVM->nFuncSP ;
		}
	}
}

void simple_vm_oop_newsuperobj ( VM *pVM,List *pState,List *pClass )
{
	List *pSuper,*pSuper2,*pMethods,*pList  ;
	const char *cParentClassName,*cClassName  ;
	int x  ;
	pSuper = simple_vm_newvar2(pVM,"super",pState);
	simple_list_setint_gc(pVM->pRingState,pSuper,SIMPLE_VAR_TYPE,SIMPLE_VM_LIST);
	simple_list_setlist_gc(pVM->pRingState,pSuper,SIMPLE_VAR_VALUE);
	pSuper2 = simple_list_getlist(pSuper,SIMPLE_VAR_VALUE);
	pMethods = simple_list_getlist(pClass,4);
	simple_list_addpointer_gc(pVM->pRingState,pSuper2,pMethods);
	cParentClassName = simple_list_getstring(pClass,3) ;
	while ( strcmp(cParentClassName,"") != 0 ) {
		for ( x = 1 ; x <= simple_vm_oop_visibleclassescount(pVM) ; x++ ) {
			pList = simple_vm_oop_visibleclassitem(pVM,x);
			cClassName = simple_list_getstring(pList,1) ;
			pList = simple_vm_oop_checkpointertoclassinpackage(pVM,pList);
			if ( pList == NULL ) {
				continue ;
			}
			if ( strcmp(cClassName,cParentClassName) == 0 ) {
				cParentClassName = simple_list_getstring(pList,3) ;
				pMethods = simple_list_getlist(pList,4);
				simple_list_addpointer_gc(pVM->pRingState,pSuper2,pMethods);
				break ;
			}
		}
	}
}

List * simple_vm_oop_getsuperobj ( VM *pVM )
{
	List *pVar  ;
	if ( ( SIMPLE_VM_STACK_ISPOINTER ) && ( simple_list_getsize(pVM->pObjState) != 0    ) ) {
		if ( SIMPLE_VM_STACK_OBJTYPE == SIMPLE_OBJTYPE_VARIABLE ) {
			pVar = (List *) SIMPLE_VM_STACK_READP ;
			if ( (simple_list_islist(pVar,3)) && (strcmp(simple_list_getstring(pVar,1),"super") == 0 ) ) {
				pVar = simple_list_getlist(pVar,3);
				SIMPLE_VM_STACK_POP ;
				return pVar ;
			}
		}
	}
	return NULL ;
}

void simple_vm_oop_loadsuperobjmethod ( VM *pVM,List *pSuper )
{
	int x  ;
	List *pState,*pMethods,*pClass,*pVar,*pList  ;
	pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState));
	pState = simple_list_getlist(pList,SIMPLE_OBJSTATE_SCOPE);
	pMethods = simple_list_getlist(pList,SIMPLE_OBJSTATE_METHODS);
	pClass = simple_list_getlist(pList,SIMPLE_OBJSTATE_CLASS);
	for ( x = 1 ; x <= simple_list_getsize(pSuper) ; x++ ) {
		if ( simple_list_getpointer(pSuper,x) == pMethods ) {
			if ( (x+1)  <= simple_list_getsize(pSuper) ) {
				pMethods = (List *) simple_list_getpointer(pSuper,(x+1));
				break ;
			}
			else {
				simple_vm_error(pVM,SIMPLE_VM_ERROR_SUPERCLASSNOTFOUND);
				return ;
			}
		}
	}
	pList = simple_list_newlist_gc(pVM->pRingState,pVM->pObjState);
	simple_list_addpointer_gc(pVM->pRingState,pList,pState);
	simple_list_addpointer_gc(pVM->pRingState,pList,pMethods);
	simple_list_addpointer_gc(pVM->pRingState,pList,pClass);
	/* Call Method */
	pVar = pVM->pFunctionsMap ;
	pVM->pFunctionsMap = pMethods ;
	pVM->nCallMethod = 1 ;
	simple_vm_loadfunc(pVM);
	pVM->nCallMethod = 0 ;
	pVM->pFunctionsMap = pVar ;
}

void simple_vm_oop_import ( VM *pVM )
{
	simple_vm_oop_import2(pVM,SIMPLE_VM_IR_READC);
}

void simple_vm_oop_import2 ( VM *pVM,const char *cPackage )
{
	int x  ;
	List *pList,*pList2  ;
	const char *cPackage2  ;
	for ( x = 1 ; x <= simple_list_getsize(pVM->pPackagesMap) ; x++ ) {
		pList = simple_list_getlist(pVM->pPackagesMap,x);
		cPackage2 = simple_list_getstring(pList,1);
		if ( strcmp(cPackage, cPackage2) == 0 ) {
			/* Get Package Classes */
			pList2 = simple_list_getlist(pList,2);
			simple_vm_oop_import3(pVM,pList2);
			/* Set Active Package Name */
			simple_stsimple_set_gc(pVM->pRingState,pVM->pPackageName,cPackage);
			return ;
		}
	}
	/* Error Message */
	simple_vm_error2(pVM,SIMPLE_VM_ERROR_PACKAGENOTFOUND,cPackage);
}

void simple_vm_oop_import3 ( VM *pVM,List *pList )
{
	int x  ;
	List *pList2, *pList3  ;
	/* Import Package Classes */
	for ( x = 1 ; x <= simple_list_getsize(pList) ; x++ ) {
		pList2 = simple_list_getlist(pList,x);
		pList3 = simple_list_newlist_gc(pVM->pRingState,pVM->pClassesMap);
		simple_list_addstsimple_gc(pVM->pRingState,pList3,simple_list_getstring(pList2,1));
		simple_list_addpointer_gc(pVM->pRingState,pList3,pList2);
		simple_list_addpointer_gc(pVM->pRingState,pList3,pVM->cFileName);
	}
}

List * simple_vm_oop_checkpointertoclassinpackage ( VM *pVM,List *pList )
{
	if ( simple_list_getsize(pList) == 3 ) {
		if ( simple_list_getpointer(pList,3) != NULL ) {
			if ( strcmp((char *) simple_list_getpointer(pList,3),pVM->cFileName) != 0 ) {
				return NULL ;
			}
		}
		return (List *) simple_list_getpointer(pList,2) ;
	}
	return pList ;
}

int simple_vm_oop_visibleclassescount ( VM *pVM )
{
	List *pList  ;
	if ( simple_list_getsize(pVM->aActivePackage) > 0 ) {
		pList = (List *) simple_list_getpointer(pVM->aActivePackage,simple_list_getsize(pVM->aActivePackage)) ;
		pList = simple_list_getlist(pList,SIMPLE_CLASSESLIST) ;
		return simple_list_getsize(pVM->pClassesMap) + simple_list_getsize(pList) ;
	}
	return simple_list_getsize(pVM->pClassesMap) ;
}

List * simple_vm_oop_visibleclassitem ( VM *pVM,int x )
{
	List *pList  ;
	if ( x <= simple_list_getsize(pVM->pClassesMap) ) {
		return simple_list_getlist(pVM->pClassesMap,x) ;
	}
	pList = (List *) simple_list_getpointer(pVM->aActivePackage,simple_list_getsize(pVM->aActivePackage)) ;
	pList = simple_list_getlist(pList,SIMPLE_CLASSESLIST) ;
	pList = simple_list_getlist(pList,x-simple_list_getsize(pVM->pClassesMap)) ;
	return pList ;
}

void simple_vm_oop_pushclasspackage ( VM *pVM,List *pList )
{
	List *pList2  ;
	pList2 = simple_list_getlist(pList,SIMPLE_CLASSMAP_POINTERTOPACKAGE) ;
	if ( pList2 != NULL ) {
		simple_list_addpointer_gc(pVM->pRingState,pVM->aActivePackage,pList2);
	}
}

void simple_vm_oop_popclasspackage ( VM *pVM )
{
	if ( simple_list_getsize(pVM->aActivePackage) > 0 ) {
		simple_list_deleteitem_gc(pVM->pRingState,pVM->aActivePackage,simple_list_getsize(pVM->aActivePackage));
	}
}

void simple_vm_oop_deletepackagesafter ( VM *pVM,int x )
{
	int t  ;
	if ( x <= simple_list_getsize(pVM->aActivePackage) ) {
		for ( t = simple_list_getsize(pVM->aActivePackage) ; t > x ; t-- ) {
			simple_list_deleteitem_gc(pVM->pRingState,pVM->aActivePackage,t);
		}
	}
}

int simple_vm_oop_callmethodinsideclass ( VM *pVM )
{
	List *pList, *pList2  ;
	int x  ;
	/*
	**  This function tell us if we are inside Class method during runtime or not 
	**  pObjState is used when we Call Method or We use braces { } to access object 
	**  if the size of pObjState List is 4 , then it's class method execution not brace 
	**  Braces can be used before calling class methods 
	**  Also braces can be used inside class methods to access objects 
	**  Inside class method you can access any object using { } , you can access the self object 
	**  Braces & Methods calls can be nested 
	**  Check Calling from function 
	*/
	if ( simple_list_getsize(pVM->pFuncCallList) > 0 ) {
		for ( x = simple_list_getsize(pVM->pFuncCallList) ; x >= 1 ; x-- ) {
			pList = simple_list_getlist(pVM->pFuncCallList,x);
			/* Be sure that the function is already called using ICO_CALL */
			if ( simple_list_getsize(pList) >= SIMPLE_FUNCCL_CALLERPC ) {
				if ( simple_list_getint(pList,SIMPLE_FUNCCL_METHODORFUNC) == 0 ) {
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
	**  Or it's called from inside { } as function 
	**  Return 1 if last item is a method 
	*/
	if ( simple_list_getsize(pVM->pObjState) >= 1 ) {
		pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState)) ;
		if ( (simple_list_getsize(pList) == 4) && (pVM->nCallMethod == 0) ) {
			return 1 ;
		}
	}
	/* Check using braces { } to access object from a method in the Class */
	if ( simple_list_getsize(pVM->pObjState) >= 2 ) {
		pList = (List *) simple_list_getpointer(simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState)),SIMPLE_OBJSTATE_CLASS);
		for ( x = simple_list_getsize(pVM->pObjState) - 1 ; x >= 1 ; x-- ) {
			pList2 = simple_list_getlist(pVM->pObjState,x);
			if ( simple_list_getsize(pList2) == 4 ) {
				pList2 = (List *) simple_list_getpointer(pList2,SIMPLE_OBJSTATE_CLASS);
				if ( pList == pList2 ) {
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

void simple_vm_oop_setget ( VM *pVM,List *pVar )
{
	List *pList, *pList2  ;
	Item *pItem, *pItem2  ;
	char *pString, *pString2  ;
	/* Create char */
	pString = simple_stsimple_new_gc(pVM->pRingState,"if ismethod(simple_gettemp_var,'get");
	simple_stsimple_add_gc(pVM->pRingState,pString,simple_list_getstring(pVar,1));
	simple_stsimple_add_gc(pVM->pRingState,pString,"')\nreturn simple_gettemp_var.'get");
	simple_stsimple_add_gc(pVM->pRingState,pString,simple_list_getstring(pVar,1));
	simple_stsimple_add_gc(pVM->pRingState,pString,"'() ok");
	/* Set Variable simple_gettemp_var  , Number 5 in Public Memory */
	pList = simple_list_getlist(simple_vm_getglobalscope(pVM),5) ;
	simple_list_setpointer_gc(pVM->pRingState,pList,SIMPLE_VAR_VALUE,pVM->pGetSetObject);
	simple_list_setint_gc(pVM->pRingState,pList,SIMPLE_VAR_PVALUETYPE ,pVM->nGetSetObjType);
	/* Check Setter & Getter for Public Attributes */
	SIMPLE_VM_IR_LOAD ;
	if ( SIMPLE_VM_IR_OPCODE != ICO_ASSIGNMENTPOINTER ) {
		SIMPLE_VM_IR_UNLOAD ;
		/*
		**  Get Property 
		**  Check to do a Stack POP for the Attribute List 
		*/
		pString2 = simple_stsimple_new_gc(pVM->pRingState,"get");
		simple_stsimple_add_gc(pVM->pRingState,pString2,simple_list_getstring(pVar,1));
		/* Check Type */
		pList2 = NULL ;
		if ( pVM->nGetSetObjType == SIMPLE_OBJTYPE_VARIABLE ) {
			pList2 = simple_list_getlist((List *) (pVM->pGetSetObject),SIMPLE_VAR_VALUE ) ;
		}
		else if ( pVM->nGetSetObjType == SIMPLE_OBJTYPE_LISTITEM ) {
			pItem2 = (Item *) pVM->pGetSetObject ;
			pList2 = simple_item_getlist(pItem2) ;
		}
		if ( simple_vm_oop_ismethod(pVM,pList2,simple_stsimple_get(pString2)) ) {
			SIMPLE_VM_STACK_POP ;
		}
		simple_stsimple_delete_gc(pVM->pRingState,pString2);
		if ( SIMPLE_VM_IR_READIVALUE(2)  == 0 ) {
			pItem = SIMPLE_VM_IR_ITEM(2) ;
			pVM->nEvalCalledFromRingCode = 0 ;
			pVM->nRetEvalDontDelete = 1 ;
			simple_vm_eval(pVM,simple_stsimple_get(pString));
			/* We don't use SIMPLE_VM_IR because Eval reallocation change mem. locations */
			simple_item_setint_gc(pVM->pRingState,pItem,pVM->nPC);
		}
		else {
			simple_vm_blockflag2(pVM,pVM->nPC);
			pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
		}
	}
	else {
		SIMPLE_VM_IR_UNLOAD ;
		/*
		**  Set Property 
		**  Delete All Items to avoid a memory leak in real time applications 
		*/
		simple_list_deleteallitems_gc(pVM->pRingState,pVM->aSetProperty);
		pList = simple_list_newlist_gc(pVM->pRingState,pVM->aSetProperty);
		/* Add object pointer & Type */
		simple_list_addpointer_gc(pVM->pRingState,pList,pVM->pGetSetObject);
		simple_list_addint_gc(pVM->pRingState,pList,pVM->nGetSetObjType);
		/* Add property name */
		simple_list_addstsimple_gc(pVM->pRingState,pList,simple_list_getstring(pVar,1));
		/* Property Variable */
		simple_list_addpointer_gc(pVM->pRingState,pList,pVar);
	}
	/* Delete char */
	simple_stsimple_delete_gc(pVM->pRingState,pString);
}

void simple_vm_oop_setproperty ( VM *pVM )
{
	List *pList, *pList2  ;
	Item *pItem,*pItem2  ;
	char *pString  ;
	/* To Access Property Data */
	if ( simple_list_getsize(pVM->aSetProperty) < 1 ) {
		/* This case happens when using This.Attribute inside nested braces in a class method */
		simple_vm_assignment(pVM);
		return ;
	}
	pList = simple_list_getlist(pVM->aSetProperty,simple_list_getsize(pVM->aSetProperty));
	/* Add Before Equal Flag */
	if ( simple_list_getsize(pList) == 4 ) {
		simple_list_addint_gc(pVM->pRingState,pList,pVM->nBeforeEqual);
	}
	/* Before (First Time) */
	if ( SIMPLE_VM_IR_READIVALUE(1) == 0 ) {
		pItem2 = SIMPLE_VM_IR_ITEM(1) ;
		/* Set Variable simple_gettemp_var  , Number 5 in Public Memory */
		pList2 = simple_list_getlist(simple_vm_getglobalscope(pVM),5) ;
		simple_list_setpointer_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,simple_list_getpointer(pList,1));
		simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_PVALUETYPE,simple_list_getint(pList,2));
		/* Set Variable simple_settemp_var  , Number 7 in Public Memory */
		pList2 = simple_list_getlist(simple_vm_getglobalscope(pVM),7) ;
		if ( SIMPLE_VM_STACK_ISNUMBER ) {
			simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_TYPE,SIMPLE_VM_NUMBER);
			simple_list_setdouble_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,SIMPLE_VM_STACK_READN);
			simple_list_adddouble_gc(pVM->pRingState,pList,SIMPLE_VM_STACK_READN);
		}
		else if ( SIMPLE_VM_STACK_ISSTRING ) {
			simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_TYPE,SIMPLE_VM_STRING);
			simple_list_setstsimple_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,SIMPLE_VM_STACK_READC);
			simple_list_addstsimple_gc(pVM->pRingState,pList,SIMPLE_VM_STACK_READC);
		}
		else if ( SIMPLE_VM_STACK_ISPOINTER ) {
			simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
			simple_list_setpointer_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,SIMPLE_VM_STACK_READP);
			simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_PVALUETYPE ,SIMPLE_VM_STACK_OBJTYPE);
			simple_list_addpointer_gc(pVM->pRingState,pList,SIMPLE_VM_STACK_READP);
			simple_list_addint_gc(pVM->pRingState,pList,SIMPLE_VM_STACK_OBJTYPE);
		}
		/* Set Variable simple_tempflag_var , Number 8 in Public Memory */
		pList2 = simple_list_getlist(simple_vm_getglobalscope(pVM),8) ;
		simple_list_setdouble_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,0.0);
		/* Execute the same instruction again (next time the part "After (Second Time)" will run ) */
		pVM->nPC-- ;
		if ( SIMPLE_VM_IR_READIVALUE(2)  == 0 ) {
			/* Create char */
			pString = simple_stsimple_new_gc(pVM->pRingState,"if ismethod(simple_gettemp_var,'set");
			simple_stsimple_add_gc(pVM->pRingState,pString,simple_list_getstring(pList,3));
			simple_stsimple_add_gc(pVM->pRingState,pString,"')\nsimple_gettemp_var.'set");
			simple_stsimple_add_gc(pVM->pRingState,pString,simple_list_getstring(pList,3));
			simple_stsimple_add_gc(pVM->pRingState,pString,"'(simple_settemp_var)\nsimple_tempflag_var = 0\nelse\nsimple_tempflag_var = 1\nok");
			/* Eval the string */
			pItem = SIMPLE_VM_IR_ITEM(2) ;
			pVM->nEvalCalledFromRingCode = 0 ;
			pVM->nRetEvalDontDelete = 1 ;
			simple_vm_eval(pVM,simple_stsimple_get(pString));
			/* We don't use SIMPLE_VM_IR because Eval reallocation change mem. locations */
			simple_item_setint_gc(pVM->pRingState,pItem,pVM->nPC);
			/* Delete char */
			simple_stsimple_delete_gc(pVM->pRingState,pString);
		}
		else {
			simple_vm_blockflag2(pVM,pVM->nPC);
			pVM->nPC = SIMPLE_VM_IR_READIVALUE(2) ;
		}
		/* Set Before/After SetProperty Flag To After */
		simple_item_setint_gc(pVM->pRingState,pItem2,1);
	}
	/* After (Second Time) */
	else {
		/* Set Before/After SetProperty Flag to Before */
		SIMPLE_VM_IR_READIVALUE(1) = 0 ;
		/* Get Variable simple_tempflag_var */
		pList2 = simple_list_getlist(simple_vm_getglobalscope(pVM),8) ;
		if ( simple_list_getdouble(pList2,3) == 1.0 ) {
			/*
			**  The set method is not found!, we have to do the assignment operation 
			**  Push Variable Then Push Value then Assignment 
			*/
			SIMPLE_VM_STACK_PUSHPVALUE(simple_list_getpointer(pList,4));
			SIMPLE_VM_STACK_OBJTYPE = SIMPLE_OBJTYPE_VARIABLE ;
			/* Restore Before Equal Flag */
			pVM->nBeforeEqual = simple_list_getint(pList,5) ;
			/* Push Value */
			if ( simple_list_isdouble(pList,6) ) {
				SIMPLE_VM_STACK_PUSHNVALUE(simple_list_getdouble(pList,6));
			}
			else if ( simple_list_isstring(pList,6) ) {
				SIMPLE_VM_STACK_PUSHCVALUE(simple_list_getstring(pList,6));
			}
			else if ( simple_list_ispointer(pList,6) ) {
				SIMPLE_VM_STACK_PUSHPVALUE(simple_list_getpointer(pList,6));
				SIMPLE_VM_STACK_OBJTYPE = simple_list_getint(pList,7) ;
			}
			simple_vm_assignment(pVM);
		}
		simple_list_deleteitem_gc(pVM->pRingState,pVM->aSetProperty,simple_list_getsize(pVM->aSetProperty));
	}
}

List * simple_vm_oop_objvarfromobjlist ( List *pList )
{
	int nType  ;
	Item *pItem  ;
	/* Get Object State List */
	pList = simple_list_getlist(pList,2);
	/* Get Self Attribute List */
	pList = simple_list_getlist(pList,1);
	/* Get Object Pointer from Self Attribute List */
	nType = simple_list_getint(pList,4) ;
	if ( nType == SIMPLE_OBJTYPE_VARIABLE ) {
		pList = (List *) simple_list_getpointer(pList,3);
	}
	else if ( nType == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = (Item *) simple_list_getpointer(pList,3);
		pList = (List *) simple_item_getlist(pItem) ;
	}
	return pList ;
}

int simple_vm_oop_objtypefromobjlist ( List *pList )
{
	int nType  ;
	/* Get Object State List */
	pList = simple_list_getlist(pList,2);
	/* Get Self Attribute List */
	pList = simple_list_getlist(pList,1);
	/* Get Object Type from Self Attribute List */
	nType = simple_list_getint(pList,4) ;
	return nType ;
}

Item * simple_vm_oop_objitemfromobjlist ( List *pList )
{
	Item *pItem  ;
	/* Get Object State List */
	pList = simple_list_getlist(pList,2);
	/* Get Self Attribute List */
	pList = simple_list_getlist(pList,1);
	/* Get Object Pointer from Self Attribute List */
	pItem = (Item *) simple_list_getpointer(pList,3);
	return pItem ;
}

void simple_vm_oop_operatoroverloading ( VM *pVM,List *pObj,const char *cStr1,int nType,const char *cStr2,double nNum1,void *pPointer,int nPointerType )
{
	List *pList2  ;
	Item *pItem  ;
	char *pString  ;
	int nObjType  ;
	nObjType = simple_vm_oop_objtypefromobjlist(pObj);
	/* Set Variable simple_gettemp_var  , Number 5 in Public Memory */
	pList2 = simple_list_getlist(simple_vm_getglobalscope(pVM),5) ;
	if ( nObjType == SIMPLE_OBJTYPE_VARIABLE ) {
		pObj = simple_vm_oop_objvarfromobjlist(pObj);
		simple_list_setpointer_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,pObj);
	}
	else if ( nObjType == SIMPLE_OBJTYPE_LISTITEM ) {
		pItem = simple_vm_oop_objitemfromobjlist(pObj);
		simple_list_setpointer_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,pItem);
	}
	simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_PVALUETYPE,nObjType);
	/* Set Variable simple_settemp_var  , Number 7 in Public Memory */
	pList2 = simple_list_getlist(simple_vm_getglobalscope(pVM),7) ;
	if ( nType == SIMPLE_OOPARA_STRING ) {
		simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_TYPE,SIMPLE_VM_STRING);
		simple_list_setstsimple_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,cStr2);
	}
	else if ( nType == SIMPLE_OOPARA_NUMBER ) {
		simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_TYPE,SIMPLE_VM_NUMBER);
		simple_list_setdouble_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,nNum1);
	}
	else if ( nType == SIMPLE_OOPARA_POINTER ) {
		simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_TYPE,SIMPLE_VM_POINTER);
		simple_list_setpointer_gc(pVM->pRingState,pList2,SIMPLE_VAR_VALUE,pPointer);
		simple_list_setint_gc(pVM->pRingState,pList2,SIMPLE_VAR_PVALUETYPE,nPointerType);
	}
	if ( SIMPLE_VM_IR_READIVALUE(1) == 0 ) {
		/* Create char */
		pString = simple_stsimple_new_gc(pVM->pRingState,"if ismethod(simple_gettemp_var,'operator')\nreturn simple_gettemp_var.operator('");
		simple_stsimple_add_gc(pVM->pRingState,pString,cStr1);
		simple_stsimple_add_gc(pVM->pRingState,pString,"',simple_settemp_var)\nelse\nraise('Object does not support operator overloading')\nok\n");
		/* Eval the string */
		pItem = SIMPLE_VM_IR_ITEM(1) ;
		pVM->nEvalCalledFromRingCode = 0 ;
		pVM->nRetEvalDontDelete = 1 ;
		simple_vm_eval(pVM,simple_stsimple_get(pString));
		/* We don't use SIMPLE_VM_IR because Eval reallocation change mem. locations */
		simple_item_setint_gc(pVM->pRingState,pItem,pVM->nPC);
		/* Delete char */
		simple_stsimple_delete_gc(pVM->pRingState,pString);
	}
	else {
		simple_vm_blockflag2(pVM,pVM->nPC);
		pVM->nPC = SIMPLE_VM_IR_READIVALUE(1) ;
	}
}

void simple_vm_oop_callmethodfrombrace ( VM *pVM )
{
	List *pList,*pList2  ;
	const char *cStr  ;
	/*
	**  We uses AfterCallMethod2 instead of AfterCallMethod to avoid conflict with normal method call 
	**  AfterCallMethod2 is the same instruction as AfterCallMethod 
	**  Change NOOP to After Call Method2 
	*/
	SIMPLE_VM_IR_LOAD ;
	if ( (SIMPLE_VM_IR_OPCODE == ICO_NOOP) || (SIMPLE_VM_IR_OPCODE == ICO_AFTERCALLMETHOD2) ) {
		SIMPLE_VM_IR_OPCODE = ICO_AFTERCALLMETHOD2 ;
		pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState)) ;
		/* Pass Brace when we call class init , using new object() */
		if ( (simple_list_getsize(pVM->pObjState) > 1) && (pVM->nCallClassInit) ) {
			if ( simple_list_getsize(pVM->pFuncCallList) > 0 ) {
				pList2 = simple_list_getlist(pVM->pFuncCallList,simple_list_getsize(pVM->pFuncCallList));
				cStr = simple_list_getstring(pList2,SIMPLE_FUNCCL_NAME);
				if ( strcmp(cStr,"init") != 0 ) {
					pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState)-1) ;
				}
			}
			else {
				pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState)-1) ;
			}
		}
		pList2 = simple_list_newlist_gc(pVM->pRingState,pVM->pObjState);
		simple_list_copy(pList2,pList);
		/* Add Logical Value (True) , That we are inside the class method */
		simple_list_addint_gc(pVM->pRingState,pList2,1);
		/* Push Class Package */
		pList = (List *) simple_list_getpointer(pList2,SIMPLE_OBJSTATE_CLASS);
		simple_vm_oop_pushclasspackage(pVM,pList);
	}
	SIMPLE_VM_IR_UNLOAD ;
}

int simple_vm_oop_ismethod ( VM *pVM,List *pList,const char *cStr )
{
	List *pList2,*pList3  ;
	int x  ;
	/* Get Object Class */
	pList = (List *) simple_list_getpointer(pList,1);
	/* Get Class Methods */
	pList2 = simple_list_getlist(pList,4);
	/* Get Parent Classes Methods */
	simple_vm_oop_parentmethods(pVM,pList);
	/* Find the Method */
	if ( simple_list_getsize(pList2) > 0 ) {
		for ( x = 1 ; x <= simple_list_getsize(pList2) ; x++ ) {
			pList3 = simple_list_getlist(pList2,x);
			if ( strcmp(simple_list_getstring(pList3,SIMPLE_FUNCMAP_NAME),cStr) == 0 ) {
				if ( simple_list_getint(pList3,SIMPLE_FUNCMAP_PRIVATEFLAG) ) {
					return 2 ;
				}
				return 1 ;
			}
		}
	}
	return 0 ;
}

void simple_vm_oop_updateselfpointer ( VM *pVM,List *pObj,int nType,void *pContainer )
{
	List *pList  ;
	/* Get Object State */
	pList = simple_list_getlist(pObj,2);
	/* Get Self Attribute */
	pList = simple_list_getlist(pList,1);
	/* Set Object Pointer */
	simple_list_setpointer_gc(pVM->pRingState,pList,3, pContainer);
	/* Set Object Type */
	simple_list_setint_gc(pVM->pRingState,pList,4,nType);
}

void simple_vm_oop_setthethisvariable ( VM *pVM )
{
	List *pList, *pThis  ;
	pThis = simple_list_getlist(simple_vm_getglobalscope(pVM),SIMPLE_VM_STATICVAR_THIS) ;
	if ( (simple_list_getsize(pVM->pObjState) < 1) || (simple_vm_oop_callmethodinsideclass(pVM) == 0) ) {
		simple_list_setpointer_gc(pVM->pRingState,pThis,SIMPLE_VAR_VALUE,NULL);
		simple_list_setint_gc(pVM->pRingState,pThis,SIMPLE_VAR_PVALUETYPE,0);
		return ;
	}
	pList = simple_list_getlist(pVM->pObjState,simple_list_getsize(pVM->pObjState));
	/* Get Object Scope */
	pList = simple_list_getlist(pList,SIMPLE_OBJSTATE_SCOPE);
	if ( pList == NULL ) {
		simple_list_setpointer_gc(pVM->pRingState,pThis,SIMPLE_VAR_VALUE,NULL);
		simple_list_setint_gc(pVM->pRingState,pThis,SIMPLE_VAR_PVALUETYPE,0);
		return ;
	}
	/* Get Self Attribute List */
	pList = simple_list_getlist(pList,1);
	/* Save this */
	simple_list_setpointer_gc(pVM->pRingState,pThis,SIMPLE_VAR_VALUE,simple_list_getpointer(pList,SIMPLE_VAR_VALUE));
	simple_list_setint_gc(pVM->pRingState,pThis,SIMPLE_VAR_PVALUETYPE,simple_list_getint(pList,SIMPLE_VAR_PVALUETYPE));
}

void simple_vm_oop_updateselfpointer2 ( VM *pVM, List *pList )
{
	Item *pItem  ;
	int x,lFound  ;
	List *pRecord  ;
	/*
	**  This function will create new item 
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
	for ( x = 1 ; x <= simple_list_getsize(pVM->aDynamicSelfItems) ; x++ ) {
		pRecord = simple_list_getlist(pVM->aDynamicSelfItems,x);
		if ( simple_list_getint(pRecord,1) == pVM->nPC ) {
			pItem = (Item *) simple_list_getpointer(pRecord,2);
			lFound = 1 ;
			break ;
		}
	}
	if ( lFound == 0 ) {
		pRecord = simple_list_newlist_gc(pVM->pRingState,pVM->aDynamicSelfItems);
		simple_list_addint_gc(pVM->pRingState,pRecord,pVM->nPC);
		pItem = simple_item_new(ITEMTYPE_NOTHING);
		simple_list_addpointer_gc(pVM->pRingState,pRecord,pItem);
		simple_item_settype_gc(pVM->pRingState,pItem,ITEMTYPE_LIST);
		simple_state_free(pVM->pRingState,pItem->data.pList);
		pItem->gc.nReferenceCount++ ;
	}
	/* Set the pointer */
	pItem->data.pList = pList ;
	/* Update The Self Pointer */
	simple_vm_oop_updateselfpointer(pVM,pList,SIMPLE_OBJTYPE_LISTITEM,pItem);
}
