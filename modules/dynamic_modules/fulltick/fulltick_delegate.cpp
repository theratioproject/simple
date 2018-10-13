
extern "C" {
	#include "../../../simple/includes/simple.h"
	
}

#include "fulltick.h"

class CallbackStruct
{
public:
  void *pointer;
  String *block;
  Fl_Widget *widget;
  CallbackStruct( void *the_pointer, String *the_block, Fl_Widget *the_widget);

};

class MyWindow : public Fl_Window {
  int handle(int);
public:
  MyWindow(int w, int h, const char *t=0L)
    : Fl_Window( w, h, t ) { }
};

static void SimpleCallBack(Fl_Widget*, void* callback_struct) ;

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