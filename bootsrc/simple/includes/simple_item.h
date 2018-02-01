/* Copyright (c) 2013-2017 Mahmoud Fayed <msfclipper@yahoo.com> */
#ifndef simple_item_h
#define simple_item_h
/* Data */
typedef struct Item {
	/* Item Type */
	unsigned int nType:3  ;
	/* The number type, 0 = Nothing , 1 = int , 2 = double */
	unsigned int NumberFlag:2  ;
	/*
	**  what is the type of the object that the pointer refer to 
	**  Used when putting the item in the stack to refer to list or listitem 
	*/
	unsigned int nObjectType:2  ;
	/* Data */
	union {
		struct Stsimple *pStsimple  ;
		double dNumber  ;
		int iNumber  ;
		void *pPointer  ;
		struct List *pList  ;
		void (*pFunc)(void *) ;
	} data ;
	/* Garbage Collector Data (Reference Counting) */
	GCData gc  ;
} Item ;
/* Constants */
#define ITEMTYPE_NOTHING 0
#define ITEMTYPE_STRING 1
#define ITEMTYPE_NUMBER 2
#define ITEMTYPE_POINTER 3
#define ITEMTYPE_LIST 4
#define ITEMTYPE_FUNCPOINTER 5
#define ITEM_NUMBERFLAG_NOTHING 0
#define ITEM_NUMBERFLAG_INT 1
#define ITEM_NUMBERFLAG_DOUBLE 2
/* Functions */

RING_API Item * simple_item_new_gc ( void *pState,int ItemType ) ;

RING_API Item * simple_item_delete_gc ( void *pState,Item *pItem ) ;

RING_API void simple_item_settype_gc ( void *pState,Item *pItem,int ItemType ) ;

RING_API void simple_item_print ( Item *pItem ) ;

RING_API void simple_item_content_delete_gc ( void *pState,Item *pItem ) ;
/*
**  Functions to deal with array of items 
**  int 
*/

RING_API void simple_itemarray_setint_gc ( void *pState,Item pList[], int index ,int number ) ;
/* Pointers */

RING_API void simple_itemarray_setpointer_gc ( void *pState,Item pList[], int index ,void *pValue ) ;
/* double */

RING_API void simple_itemarray_setdouble_gc ( void *pState,Item pList[], int index ,double number ) ;
/* Stsimple */

RING_API void simple_itemarray_setstsimple_gc ( void *pState,Item pList[], int index ,const char *str ) ;

RING_API void simple_itemarray_setstsimple2_gc ( void *pState,Item pList[], int index ,const char *str,int nStrSize ) ;
/* Functions to deal with one item */

RING_API void simple_item_setstsimple_gc ( void *pState,Item *pItem,const char *cStr ) ;

RING_API void simple_item_setdouble_gc ( void *pState,Item *pItem,double x ) ;

RING_API void simple_item_setpointer_gc ( void *pState,Item *pItem,void *pValue ) ;

RING_API void simple_item_setint_gc ( void *pState,Item *pItem,int x ) ;

RING_API void simple_item_setstsimple2_gc ( void *pState,Item *pItem,const char *cStr,int nStrSize ) ;
/* Macro */
#define simple_item_getstsimple(x) x->data.pStsimple
#define simple_item_getnumber(x) x->data.dNumber
#define simple_item_getdouble(x) x->data.dNumber
#define simple_item_getint(x) x->data.iNumber
#define simple_item_getlist(x) x->data.pList
#define simple_item_getpointer(x) x->data.pPointer
#define simple_item_gettype(x) x->nType
#define simple_itemarray_getint(pList,index) ( pList[index].data.iNumber )
#define simple_itemarray_getpointer(pList,index) ( pList[index].data.pPointer )
#define simple_itemarray_getdouble(pList,index) pList[index].data.dNumber
#define simple_itemarray_getstsimple(pList,index) simple_stsimple_get(pList[index].data.pStsimple )
#define simple_itemarray_getstsimplesize(pList,index) simple_stsimple_size(pList[index].data.pStsimple )
/* Check */
#define simple_itemarray_isstsimple(pList,index) (pList[index].nType == ITEMTYPE_STRING)
#define simple_itemarray_isnumber(pList,index) (pList[index].nType == ITEMTYPE_NUMBER)
#define simple_itemarray_ispointer(pList,index) (pList[index].nType == ITEMTYPE_POINTER)
#define simple_item_isstsimple(x) (x->nType == ITEMTYPE_STRING)
#define simple_item_islist(x) (x->nType == ITEMTYPE_LIST)
#define simple_item_isdouble(x) ( (x->nType == ITEMTYPE_NUMBER) && ( x->NumberFlag == ITEM_NUMBERFLAG_DOUBLE ) )
/* Functions without state pointer */

RING_API Item * simple_item_new ( int ItemType ) ;

RING_API Item * simple_item_delete ( Item *pItem ) ;

RING_API void simple_item_settype ( Item *pItem,int ItemType ) ;

RING_API void simple_item_content_delete ( Item *pItem ) ;
/*
**  Functions to deal with array of items 
**  int 
*/

RING_API void simple_itemarray_setint ( Item pList[], int index ,int number ) ;
/* Pointers */

RING_API void simple_itemarray_setpointer ( Item pList[], int index ,void *pValue ) ;
/* double */

RING_API void simple_itemarray_setdouble ( Item pList[], int index ,double number ) ;
/* Stsimple */

RING_API void simple_itemarray_setstsimple ( Item pList[], int index ,const char *str ) ;

RING_API void simple_itemarray_setstsimple2 ( Item pList[], int index ,const char *str,int nStrSize ) ;
/* Functions to deal with one item */

RING_API void simple_item_setstsimple ( Item *pItem,const char *cStr ) ;

RING_API void simple_item_setdouble ( Item *pItem,double x ) ;

RING_API void simple_item_setpointer ( Item *pItem,void *pValue ) ;

RING_API void simple_item_setint ( Item *pItem,int x ) ;

RING_API void simple_item_setstsimple2 ( Item *pItem,const char *cStr,int nStrSize ) ;
#endif