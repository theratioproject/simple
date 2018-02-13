
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


#ifndef simple_hashtable_h
#define simple_hashtable_h
/* Data */
typedef struct HashItem {
	char  *cKey  ;
	char nItemType  ;
	union HashValue {
		int nIndex  ;
		void *pValue  ;
	} HashValue ;
	struct HashItem *pNext  ;
} HashItem ;
typedef struct HashTable {
	HashItem **pArray  ;
	int nItems  ;
	int nLinkedLists  ;
	int nRebuildSize  ;
} HashTable ;
/* Functions */

HashTable * simple_hashtable_new_gc ( void *pState ) ;

unsigned int simple_hashtable_hashkey ( HashTable *pHashTable,const char *cKey ) ;

HashItem * simple_hashtable_newitem_gc ( void *pState,HashTable *pHashTable,const char *cKey ) ;

void simple_hashtable_newnumber_gc ( void *pState,HashTable *pHashTable,const char *cKey,int x ) ;

void simple_hashtable_newpointer_gc ( void *pState,HashTable *pHashTable,const char *cKey,void *x ) ;

HashItem * simple_hashtable_finditem ( HashTable *pHashTable,const char *cKey ) ;

int simple_hashtable_findnumber ( HashTable *pHashTable,const char *cKey ) ;

void * simple_hashtable_findpointer ( HashTable *pHashTable,const char *cKey ) ;

void simple_hashtable_deleteitem_gc ( void *pState,HashTable *pHashTable,const char *cKey ) ;

HashTable * simple_hashtable_delete_gc ( void *pState,HashTable *pHashTable ) ;

void simple_hashtable_print ( HashTable *pHashTable ) ;

void simple_hashtable_test ( void ) ;

void simple_hashtable_rebuild_gc ( void *pState,HashTable *pHashTable ) ;
/* Macro */
#define SIMPLE_HASHITEMTYPE_NOTYPE 0
#define SIMPLE_HASHITEMTYPE_NUMBER 1
#define SIMPLE_HASHITEMTYPE_POINTER 2
/* Functions without the State pointer */

HashTable * simple_hashtable_new ( void ) ;

HashItem * simple_hashtable_newitem ( HashTable *pHashTable,const char *cKey ) ;

void simple_hashtable_deleteitem ( HashTable *pHashTable,const char *cKey ) ;

HashTable * simple_hashtable_delete ( HashTable *pHashTable ) ;

void simple_hashtable_rebuild ( HashTable *pHashTable ) ;

void simple_hashtable_newnumber ( HashTable *pHashTable,const char *cKey,int x ) ;

void simple_hashtable_newpointer ( HashTable *pHashTable,const char *cKey,void *x ) ;

/* Data */
typedef struct PoolData {
	union PoolDataTypes {
		String vString  ;
		Item vItem  ;
		Items vItems  ;
		List vList  ;
		HashTable vHashTable  ;
		HashItem vHashItem  ;
		char vChar[64]  ;
	} PoolDataTypes ;
	struct PoolData *pNext  ;
} PoolData ;
typedef struct PoolManager {
	PoolData *pCurrentItem  ;
	void *pBlockStart  ;
	void *pBlockEnd  ;
} PoolManager ;
/* Macro */
#define SIMPLE_POOLMANAGER_ITEMSINBLOCK 10000
#define SIMPLE_POOLMANAGER_ITEMSIZE 64
#define SIMPLE_USEPOOLMANAGER 0
#endif
