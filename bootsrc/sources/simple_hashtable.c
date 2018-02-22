
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

#include "../includes/simple.h"
/* Blocks */

HashTable * simple_hashtable_new_gc ( void *pState )
{
	HashTable *pHashTable  ;
	pHashTable = (HashTable *) simple_state_malloc(pState,sizeof(HashTable));
	if ( pHashTable == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	pHashTable->nItems = 0 ;
	pHashTable->nLinkedLists = 10 ;
	pHashTable->nRebuildSize = 7 ;
	pHashTable->pArray = (HashItem **) simple_state_calloc(pState,pHashTable->nLinkedLists,sizeof(HashItem *));
	if ( pHashTable->pArray == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	return pHashTable ;
}

unsigned int simple_hashtable_hashkey ( HashTable *pHashTable,const char *cKey )
{
	unsigned int nIndex  ;
	nIndex = simple_murmur3_32(cKey,strlen(cKey),0);
	nIndex = nIndex % pHashTable->nLinkedLists ;
	return nIndex ;
}

HashItem * simple_hashtable_newitem_gc ( void *pState,HashTable *pHashTable,const char *cKey )
{
	unsigned int nIndex  ;
	HashItem *pItem  ;
	nIndex = simple_hashtable_hashkey(pHashTable,cKey);
	if ( pHashTable->pArray[nIndex]   == NULL ) {
		pHashTable->pArray[nIndex] = (HashItem *) simple_state_malloc(pState,sizeof(HashItem));
		pItem = pHashTable->pArray[nIndex] ;
	}
	else {
		pItem = pHashTable->pArray[nIndex] ;
		/* Find Position of the HashItem */
		while ( pItem->pNext != NULL ) {
			pItem = pItem->pNext ;
		}
		pItem->pNext = (HashItem *) simple_state_malloc(pState,sizeof(HashItem));
		pItem = pItem->pNext ;
	}
	if ( pItem == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	/* Store Copy from The Key */
	pItem->cKey = strdup(cKey) ;
	/* Item type will be determined from the caller */
	pItem->nItemType = SIMPLE_HASHITEMTYPE_NOTYPE ;
	pItem->pNext = NULL ;
	/* Increase Items Count */
	pHashTable->nItems++ ;
	return pItem ;
}

void simple_hashtable_newnumber_gc ( void *pState,HashTable *pHashTable,const char *cKey,int x )
{
	HashItem *pItem  ;
	pItem = simple_hashtable_newitem_gc(pState,pHashTable,cKey);
	pItem->nItemType = SIMPLE_HASHITEMTYPE_NUMBER ;
	pItem->HashValue.nIndex = x ;
	/* Check Rebuilding the HashTable */
	simple_hashtable_rebuild_gc(pState,pHashTable);
}

void simple_hashtable_newpointer_gc ( void *pState,HashTable *pHashTable,const char *cKey,void *x )
{
	HashItem *pItem  ;
	pItem = simple_hashtable_newitem_gc(pState,pHashTable,cKey);
	pItem->nItemType = SIMPLE_HASHITEMTYPE_POINTER ;
	pItem->HashValue.pValue = x ;
	/* Check Rebuilding the HashTable */
	simple_hashtable_rebuild_gc(pState,pHashTable);
}

HashItem * simple_hashtable_finditem ( HashTable *pHashTable,const char *cKey )
{
	int nIndex  ;
	HashItem *pItem  ;
	nIndex = simple_hashtable_hashkey(pHashTable,cKey);
	pItem = pHashTable->pArray[nIndex] ;
	while ( pItem != NULL ) {
		/* Check Key */
		if ( strcmp(pItem->cKey,cKey) == 0 ) {
			return pItem ;
		}
		pItem = pItem->pNext ;
	}
	return NULL ;
}

int simple_hashtable_findnumber ( HashTable *pHashTable,const char *cKey )
{
	HashItem *pItem  ;
	pItem = simple_hashtable_finditem(pHashTable,cKey);
	if ( pItem != NULL ) {
		return pItem->HashValue.nIndex ;
	}
	return 0 ;
}

void * simple_hashtable_findpointer ( HashTable *pHashTable,const char *cKey )
{
	HashItem *pItem  ;
	pItem = simple_hashtable_finditem(pHashTable,cKey);
	if ( pItem != NULL ) {
		return pItem->HashValue.pValue ;
	}
	return NULL ;
}

void simple_hashtable_deleteitem_gc ( void *pState,HashTable *pHashTable,const char *cKey )
{
	int nIndex  ;
	HashItem *pItem, *pPrevItem  ;
	nIndex = simple_hashtable_hashkey(pHashTable,cKey);
	pItem = pHashTable->pArray[nIndex] ;
	pPrevItem = NULL ;
	while ( pItem != NULL ) {
		/* Check Key */
		if ( strcmp(pItem->cKey,cKey) == 0 ) {
			if ( pPrevItem == NULL ) {
				pHashTable->pArray[nIndex] = pItem->pNext ;
			}
			else {
				pPrevItem->pNext = pItem->pNext ;
			}
			simple_state_free(pState,pItem->cKey);
			simple_state_free(pState,pItem);
			return ;
		}
		pPrevItem = pItem ;
		pItem = pItem->pNext ;
	}
}

HashTable * simple_hashtable_delete_gc ( void *pState,HashTable *pHashTable )
{
	int x  ;
	HashItem *pItem,*pItem2  ;
	if ( pHashTable == NULL ) {
		return NULL ;
	}
	for ( x = 0 ; x < pHashTable->nLinkedLists ; x++ ) {
		pItem = pHashTable->pArray[x] ;
		while ( pItem != NULL ) {
			pItem2 = pItem->pNext ;
			simple_state_free(pState,pItem->cKey);
			simple_state_free(pState,pItem);
			pItem = pItem2 ;
		}
	}
	simple_state_free(pState,pHashTable->pArray);
	simple_state_free(pState,pHashTable);
	return NULL ;
}

void simple_hashtable_rebuild_gc ( void *pState,HashTable *pHashTable )
{
	HashItem **pArray  ;
	int nLinkedLists,x  ;
	HashItem *pItem,*pItem2  ;
	if ( pHashTable->nItems != pHashTable->nRebuildSize ) {
		return ;
	}
	pArray = pHashTable->pArray ;
	nLinkedLists = pHashTable->nLinkedLists ;
	pHashTable->nRebuildSize *= 10 ;
	pHashTable->nLinkedLists *= 10 ;
	pHashTable->pArray = (HashItem **) simple_state_calloc(pState,pHashTable->nLinkedLists,sizeof(HashItem *));
	if ( pHashTable->pArray == NULL ) {
		printf( SIMPLE_OOM ) ;
		exit(0);
	}
	for ( x = 0 ; x < nLinkedLists ; x++ ) {
		pItem = pArray[x] ;
		while ( pItem != NULL ) {
			/* Rehash the item */
			if ( pItem->nItemType == SIMPLE_HASHITEMTYPE_NUMBER ) {
				simple_hashtable_newnumber(pHashTable,pItem->cKey,pItem->HashValue.nIndex);
			}
			else if ( pItem->nItemType == SIMPLE_HASHITEMTYPE_POINTER ) {
				simple_hashtable_newpointer(pHashTable,pItem->cKey,pItem->HashValue.pValue);
			}
			pItem2 = pItem->pNext ;
			simple_state_free(pState,pItem->cKey);
			simple_state_free(pState,pItem);
			pItem = pItem2 ;
		}
	}
	simple_state_free(pState,pArray);
}

void simple_hashtable_print ( HashTable *pHashTable )
{
	int x  ;
	HashItem *pItem  ;
	for ( x = 0 ; x < pHashTable->nLinkedLists ; x++ ) {
		pItem = pHashTable->pArray[x] ;
		while ( pItem != NULL ) {
			/* Print Item Data */
			printf( "\n LinkedList (%d) : Key (%s) \n",x,pItem->cKey ) ;
			pItem = pItem->pNext ;
		}
	}
}

void simple_hashtable_test ( void )
{
	HashTable *pHashTable  ;
	char str[20]  ;
	int x  ;
	puts("\nSimple - HashTable Test");
	pHashTable = simple_hashtable_new();
	puts("\nCreate HashTable Items ");
	/* Add Items */
	simple_hashtable_newnumber(pHashTable,"one",1);
	simple_hashtable_newnumber(pHashTable,"two",2);
	simple_hashtable_newnumber(pHashTable,"three",3);
	simple_hashtable_newnumber(pHashTable,"four",4);
	simple_hashtable_newnumber(pHashTable,"five",5);
	simple_hashtable_newnumber(pHashTable,"six",6);
	simple_hashtable_newnumber(pHashTable,"seven",7);
	simple_hashtable_newnumber(pHashTable,"eight",8);
	simple_hashtable_newnumber(pHashTable,"nine",9);
	simple_hashtable_newnumber(pHashTable,"ten",10);
	simple_hashtable_newpointer(pHashTable,"mypointer",str);
	for ( x = 1 ; x <= 100 ; x++ ) {
		sprintf( str , "test%d" , x ) ;
		simple_hashtable_newnumber(pHashTable,str,x);
	}
	puts("\nPrint HashTable Items ");
	simple_hashtable_print(pHashTable);
	puts("\nFind Items ");
	printf( "\n Item : one - nIndex : %d",simple_hashtable_findnumber(pHashTable,"one") ) ;
	printf( "\n Item : five - nIndex : %d",simple_hashtable_findnumber(pHashTable,"five") ) ;
	printf( "\n Item : two - nIndex : %d",simple_hashtable_findnumber(pHashTable,"two") ) ;
	printf( "\n Item : four - nIndex : %d",simple_hashtable_findnumber(pHashTable,"four") ) ;
	printf( "\n Item : three - nIndex : %d",simple_hashtable_findnumber(pHashTable,"three") ) ;
	simple_hashtable_deleteitem(pHashTable,"three");
	printf( "\n Item : three After Delete - nIndex : %d",simple_hashtable_findnumber(pHashTable,"three") ) ;
	printf( "\n Item : mypointer - pointer : %s ",(char *) simple_hashtable_findpointer(pHashTable,"mypointer") ) ;
	puts("\nDelete HashTable ");
	simple_hashtable_delete(pHashTable);
	puts("\nEnd of HashTable Test ");
	exit(0);
}
/* Blocks without the State pointer */

HashTable * simple_hashtable_new ( void )
{
	return simple_hashtable_new_gc(NULL) ;
}

HashItem * simple_hashtable_newitem ( HashTable *pHashTable,const char *cKey )
{
	return simple_hashtable_newitem_gc(NULL,pHashTable,cKey) ;
}

void simple_hashtable_deleteitem ( HashTable *pHashTable,const char *cKey )
{
	simple_hashtable_deleteitem_gc(NULL,pHashTable,cKey);
}

HashTable * simple_hashtable_delete ( HashTable *pHashTable )
{
	return simple_hashtable_delete_gc(NULL,pHashTable) ;
}

void simple_hashtable_rebuild ( HashTable *pHashTable )
{
	simple_hashtable_rebuild_gc(NULL,pHashTable);
}

void simple_hashtable_newnumber ( HashTable *pHashTable,const char *cKey,int x )
{
	simple_hashtable_newnumber_gc(NULL,pHashTable,cKey,x);
}

void simple_hashtable_newpointer ( HashTable *pHashTable,const char *cKey,void *x )
{
	simple_hashtable_newpointer_gc(NULL,pHashTable,cKey,x);
}
