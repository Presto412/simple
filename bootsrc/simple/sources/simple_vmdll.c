/* Copyright (c) 2013-2018 Mahmoud Fayed <msfclipper@yahoo.com> */
#include "../includes/ring.h"
#include "../includes/ring_vmdll.h"
/* Functions */

void ring_vm_dll_loadfunctions ( RingState *pRingState )
{
	ring_vm_funcregister("loadlib",ring_vm_dll_loadlib);
	ring_vm_funcregister("closelib",ring_vm_dll_closelib);
}

void ring_vm_dll_loadlib ( void *pPointer )
{
	LpHandleType handle  ;
	const char *cDLL  ;
	loadlibfuncptr pFunc  ;
	VM *pVM  ;
	RingState *pRingState  ;
	pVM = (VM *) pPointer ;
	pRingState = pVM->pRingState ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		cDLL = SIMPLE_API_GETSTRING(1);
		handle = LoadDLL(cDLL);
		if ( handle == NULL ) {
			printf( "\nLibrary File : %s",SIMPLE_API_GETSTRING(1) ) ;
			SIMPLE_API_ERROR(SIMPLE_VM_ERROR_LIBLOADERROR);
			return ;
		}
		pFunc = (loadlibfuncptr) GetDLLFunc(handle, "ringlib_init") ;
		if ( pFunc == NULL ) {
			printf( "\nLibrary File : %s",SIMPLE_API_GETSTRING(1) ) ;
			SIMPLE_API_ERROR("The dynamic library doesn't contain the ringlib_init() function!");
			return ;
		}
		ring_list_deletearray_gc(pRingState,pRingState->pRingCFunctions);
		(*pFunc)(pRingState) ;
		ring_list_genarray_gc(pRingState,pRingState->pRingCFunctions);
		ring_list_genhashtable2_gc(pRingState,pRingState->pRingCFunctions);
		SIMPLE_API_RETCPOINTER(handle,"DLL");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

void ring_vm_dll_closelib ( void *pPointer )
{
	LpHandleType handle  ;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		handle = SIMPLE_API_GETCPOINTER(1,"DLL") ;
		CloseDLL(handle);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}
