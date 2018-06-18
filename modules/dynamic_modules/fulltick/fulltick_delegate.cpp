
extern "C" {
	#include "../../../simple/src/includes/simple.h"
	
}

#include "fulltick.h"

/*
	JUNK YARD
	----------------------------------------------------------------------
	int handle(int e) {
		return (e == FL_SHORTCUT); // eat all keystrokes
	}
	Fl::add_handler(handle);
	-----------------------------------------------------------------------
	if ( simple_vm_exec((VM *) cbs->pointer,cbs->block->str) == 0 ) {
		((VM *) cbs->pointer)->nEvalCalledFromSimpleCode = 0 ;
	}
	simple_string_delete_gc(((VM *) cbs->pointer)->sState,cbs->block);
	-----------------------------------------------------------------------

*/