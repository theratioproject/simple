
#include "fulltick.h"



extern "C" {

SIMPLE_API void init_simple_module(SimpleState *sState)
{
    init_full_tick(sState);
}

}

void *CallbackStruct::_sState = NULL;
bool CallbackStruct::ret_evt_to_fl = true;

/** the callback delegate for the fulltick library **/
void SimpleCallBack(Fl_Widget*, void* ptr_index) {
    char code_block[30];
    snprintf(code_block, sizeof(code_block), "__fltk_current_widget_id=%i ", (int)(size_t)ptr_index);
    simple_vm_runcode(((SimpleState *)CallbackStruct::_sState)->vm, code_block); 
    simple_vm_callblock(((SimpleState *)CallbackStruct::_sState)->vm,"__fltk_widget_callback");
}

/** the menu callback delegate for the fulltick library **/
void SimpleMenuCallBack(Fl_Widget*, void* ptr_index) {
    char code_block[30];
    snprintf(code_block, sizeof(code_block), "__fltk_current_menu_index=%i ", (int)(size_t)ptr_index);
    simple_vm_runcode(((SimpleState *)CallbackStruct::_sState)->vm, code_block); 
    simple_vm_callblock(((SimpleState *)CallbackStruct::_sState)->vm,"__fltk_widget_menu_callback");
}

/*
	We change the entire event_dispatch for the library
	Handle this function with care. PLEASE.
	Also handle event in the FApp file in the
	fulltick module
	
	80 character is wide enough to contain the variables 
	and it values 
*/
int simple_Fl_Event_Dispatch(int event, Fl_Window *window) {
    char code_block[80];
    snprintf(code_block, sizeof(code_block), "__fltk_current_event=%i __fltk_current_pointer=`%p`", event, (void*)window); //printf("%p\n",(void*)window);
    simple_vm_runcode(((SimpleState *)CallbackStruct::_sState)->vm, code_block); 
    simple_vm_callblock(((SimpleState *)CallbackStruct::_sState)->vm,"__fltk_handle");//this line is crucial to our events
    if (CallbackStruct::ret_evt_to_fl == true)
        return Fl::handle_(event, window);
    return 0;
}

#ifdef _WIN32
#define SIMPLE_API __declspec(dllexport)
#else
#if defined(_MSC_VER)
//  Microsoft
    #define SIMPLE_API __declspec(dllexport)
    #define SIMPLE_API __declspec(dllimport)
#elif defined(__GNUC__)
//  GCC
#define SIMPLE_API __attribute__((visibility("default")))
#else
//  do nothing and hope for the best?
    #define SIMPLE_API
    #define SIMPLE_API
    #pragma warning Unknown dynamic link import/export semantics.
#endif
#endif

/* CUSTOM */
SIMPLE_BLOCK(fltk_FL_WINDOW)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(FL_WINDOW,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_FL_DOUBLE_WINDOW)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(FL_DOUBLE_WINDOW,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_window_to_widget)
{
    Fl_Window* point1 ;
    Fl_Widget* wi;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1, "SMOOTHC_FLTK");
    wi = point1;
    SIMPLE_API_RETCPOINTER(wi,"SMOOTHC_FLTK");
}

/* SMOOTHC EXPORTED */
SIMPLE_BLOCK(fltk_fl_filename_name)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETSTRING(fl_filename_name(str1));
}

SIMPLE_BLOCK(fltk_fl_filename_ext)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETSTRING(fl_filename_ext(str1));
}

SIMPLE_BLOCK(fltk_fl_filename_setext)
{
    char* str1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETSTRING(fl_filename_setext(str1,num2,str3));
}

SIMPLE_BLOCK(fltk_fl_filename_expand)
{
    char* str1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETNUMBER(fl_filename_expand(str1,num2,str3));
}

SIMPLE_BLOCK(fltk_fl_filename_absolute)
{
    char* str1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETNUMBER(fl_filename_absolute(str1,num2,str3));
}

SIMPLE_BLOCK(fltk_fl_filename_relative)
{
    char* str1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETNUMBER(fl_filename_relative(str1,num2,str3));
}

SIMPLE_BLOCK(fltk_fl_filename_match)
{
    const char* str1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(fl_filename_match(str1,str2));
}

SIMPLE_BLOCK(fltk_fl_filename_isdir)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETNUMBER(fl_filename_isdir(str1));
}

SIMPLE_BLOCK(fltk_fl_filename_setext_1)
{
    char* str1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETSTRING(fl_filename_setext(str1,str2));
}

SIMPLE_BLOCK(fltk_fl_filename_expand_1)
{
    char* str1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(fl_filename_expand(str1,str2));
}

SIMPLE_BLOCK(fltk_fl_filename_absolute_1)
{
    char* str1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(fl_filename_absolute(str1,str2));
}

SIMPLE_BLOCK(fltk_fl_filename_relative_1)
{
    char* str1;
    int num2;
    const char* str3;
    const char* str4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    SIMPLE_API_RETNUMBER(fl_filename_relative(str1,num2,str3,str4));
}

SIMPLE_BLOCK(fltk_fl_filename_relative_2)
{
    char* str1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(fl_filename_relative(str1,str2));
}

SIMPLE_BLOCK(fltk_fl_filename_list)
{
    const char* str1;
    struct dirent *** point2;
    Fl_File_Sort_F * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    point2 = (struct dirent ***) SIMPLE_API_GETCPOINTER2POINTER(2,"SMOOTHC_FLTK");
    point3 = (Fl_File_Sort_F *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(fl_filename_list(str1,point2,point3));
}

SIMPLE_BLOCK(fltk_fl_filename_free_list)
{
    struct dirent *** point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (struct dirent ***) SIMPLE_API_GETCPOINTER2POINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    fl_filename_free_list(point1,num2);
}

SIMPLE_BLOCK(fltk_fl_open_uri)
{
    const char* str1;
    char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(fl_open_uri(str1,str2,num3));
}

SIMPLE_BLOCK(fltk_fl_decode_uri)
{
    char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (char*)  SIMPLE_API_GETSTRING(1);
    fl_decode_uri(str1);
}

SIMPLE_BLOCK(fltk_FL_NO_EVENT)
{
    SIMPLE_API_RETNUMBER(FL_NO_EVENT);
}

SIMPLE_BLOCK(fltk_FL_PUSH)
{
    SIMPLE_API_RETNUMBER(FL_PUSH);
}

SIMPLE_BLOCK(fltk_FL_RELEASE)
{
    SIMPLE_API_RETNUMBER(FL_RELEASE);
}

SIMPLE_BLOCK(fltk_FL_ENTER)
{
    SIMPLE_API_RETNUMBER(FL_ENTER);
}

SIMPLE_BLOCK(fltk_FL_LEAVE)
{
    SIMPLE_API_RETNUMBER(FL_LEAVE);
}

SIMPLE_BLOCK(fltk_FL_DRAG)
{
    SIMPLE_API_RETNUMBER(FL_DRAG);
}

SIMPLE_BLOCK(fltk_FL_FOCUS)
{
    SIMPLE_API_RETNUMBER(FL_FOCUS);
}

SIMPLE_BLOCK(fltk_FL_UNFOCUS)
{
    SIMPLE_API_RETNUMBER(FL_UNFOCUS);
}

SIMPLE_BLOCK(fltk_FL_KEYDOWN)
{
    SIMPLE_API_RETNUMBER(FL_KEYDOWN);
}

SIMPLE_BLOCK(fltk_FL_KEYBOARD)
{
    SIMPLE_API_RETNUMBER(FL_KEYBOARD);
}

SIMPLE_BLOCK(fltk_FL_KEYUP)
{
    SIMPLE_API_RETNUMBER(FL_KEYUP);
}

SIMPLE_BLOCK(fltk_FL_CLOSE)
{
    SIMPLE_API_RETNUMBER(FL_CLOSE);
}

SIMPLE_BLOCK(fltk_FL_MOVE)
{
    SIMPLE_API_RETNUMBER(FL_MOVE);
}

SIMPLE_BLOCK(fltk_FL_SHORTCUT)
{
    SIMPLE_API_RETNUMBER(FL_SHORTCUT);
}

SIMPLE_BLOCK(fltk_FL_DEACTIVATE)
{
    SIMPLE_API_RETNUMBER(FL_DEACTIVATE);
}

SIMPLE_BLOCK(fltk_FL_ACTIVATE)
{
    SIMPLE_API_RETNUMBER(FL_ACTIVATE);
}

SIMPLE_BLOCK(fltk_FL_HIDE)
{
    SIMPLE_API_RETNUMBER(FL_HIDE);
}

SIMPLE_BLOCK(fltk_FL_SHOW)
{
    SIMPLE_API_RETNUMBER(FL_SHOW);
}

SIMPLE_BLOCK(fltk_FL_PASTE)
{
    SIMPLE_API_RETNUMBER(FL_PASTE);
}

SIMPLE_BLOCK(fltk_FL_SELECTIONCLEAR)
{
    SIMPLE_API_RETNUMBER(FL_SELECTIONCLEAR);
}

SIMPLE_BLOCK(fltk_FL_MOUSEWHEEL)
{
    SIMPLE_API_RETNUMBER(FL_MOUSEWHEEL);
}

SIMPLE_BLOCK(fltk_FL_DND_ENTER)
{
    SIMPLE_API_RETNUMBER(FL_DND_ENTER);
}

SIMPLE_BLOCK(fltk_FL_DND_DRAG)
{
    SIMPLE_API_RETNUMBER(FL_DND_DRAG);
}

SIMPLE_BLOCK(fltk_FL_DND_LEAVE)
{
    SIMPLE_API_RETNUMBER(FL_DND_LEAVE);
}

SIMPLE_BLOCK(fltk_FL_DND_RELEASE)
{
    SIMPLE_API_RETNUMBER(FL_DND_RELEASE);
}

SIMPLE_BLOCK(fltk_FL_SCREEN_CONFIGURATION_CHANGED)
{
    SIMPLE_API_RETNUMBER(FL_SCREEN_CONFIGURATION_CHANGED);
}

SIMPLE_BLOCK(fltk_FL_FULLSCREEN)
{
    SIMPLE_API_RETNUMBER(FL_FULLSCREEN);
}

SIMPLE_BLOCK(fltk_FL_ZOOM_GESTURE)
{
    SIMPLE_API_RETNUMBER(FL_ZOOM_GESTURE);
}

SIMPLE_BLOCK(fltk_FL_WHEN_NEVER)
{
    SIMPLE_API_RETNUMBER(FL_WHEN_NEVER);
}

SIMPLE_BLOCK(fltk_FL_WHEN_CHANGED)
{
    SIMPLE_API_RETNUMBER(FL_WHEN_CHANGED);
}

SIMPLE_BLOCK(fltk_FL_WHEN_NOT_CHANGED)
{
    SIMPLE_API_RETNUMBER(FL_WHEN_NOT_CHANGED);
}

SIMPLE_BLOCK(fltk_FL_WHEN_RELEASE)
{
    SIMPLE_API_RETNUMBER(FL_WHEN_RELEASE);
}

SIMPLE_BLOCK(fltk_FL_WHEN_RELEASE_ALWAYS)
{
    SIMPLE_API_RETNUMBER(FL_WHEN_RELEASE_ALWAYS);
}

SIMPLE_BLOCK(fltk_FL_WHEN_ENTER_KEY)
{
    SIMPLE_API_RETNUMBER(FL_WHEN_ENTER_KEY);
}

SIMPLE_BLOCK(fltk_FL_WHEN_ENTER_KEY_ALWAYS)
{
    SIMPLE_API_RETNUMBER(FL_WHEN_ENTER_KEY_ALWAYS);
}

SIMPLE_BLOCK(fltk_FL_WHEN_ENTER_KEY_CHANGED)
{
    SIMPLE_API_RETNUMBER(FL_WHEN_ENTER_KEY_CHANGED);
}

SIMPLE_BLOCK(fltk_FL_NO_BOX)
{
    SIMPLE_API_RETNUMBER(FL_NO_BOX);
}

SIMPLE_BLOCK(fltk_FL_FLAT_BOX)
{
    SIMPLE_API_RETNUMBER(FL_FLAT_BOX);
}

SIMPLE_BLOCK(fltk_FL_UP_BOX)
{
    SIMPLE_API_RETNUMBER(FL_UP_BOX);
}

SIMPLE_BLOCK(fltk_FL_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(FL_DOWN_BOX);
}

SIMPLE_BLOCK(fltk_FL_UP_FRAME)
{
    SIMPLE_API_RETNUMBER(FL_UP_FRAME);
}

SIMPLE_BLOCK(fltk_FL_DOWN_FRAME)
{
    SIMPLE_API_RETNUMBER(FL_DOWN_FRAME);
}

SIMPLE_BLOCK(fltk_FL_THIN_UP_BOX)
{
    SIMPLE_API_RETNUMBER(FL_THIN_UP_BOX);
}

SIMPLE_BLOCK(fltk_FL_THIN_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(FL_THIN_DOWN_BOX);
}

SIMPLE_BLOCK(fltk_FL_THIN_UP_FRAME)
{
    SIMPLE_API_RETNUMBER(FL_THIN_UP_FRAME);
}

SIMPLE_BLOCK(fltk_FL_THIN_DOWN_FRAME)
{
    SIMPLE_API_RETNUMBER(FL_THIN_DOWN_FRAME);
}

SIMPLE_BLOCK(fltk_FL_ENGRAVED_BOX)
{
    SIMPLE_API_RETNUMBER(FL_ENGRAVED_BOX);
}

SIMPLE_BLOCK(fltk_FL_EMBOSSED_BOX)
{
    SIMPLE_API_RETNUMBER(FL_EMBOSSED_BOX);
}

SIMPLE_BLOCK(fltk_FL_ENGRAVED_FRAME)
{
    SIMPLE_API_RETNUMBER(FL_ENGRAVED_FRAME);
}

SIMPLE_BLOCK(fltk_FL_EMBOSSED_FRAME)
{
    SIMPLE_API_RETNUMBER(FL_EMBOSSED_FRAME);
}

SIMPLE_BLOCK(fltk_FL_BORDER_BOX)
{
    SIMPLE_API_RETNUMBER(FL_BORDER_BOX);
}

SIMPLE_BLOCK(fltk__FL_SHADOW_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_SHADOW_BOX);
}

SIMPLE_BLOCK(fltk_FL_BORDER_FRAME)
{
    SIMPLE_API_RETNUMBER(FL_BORDER_FRAME);
}

SIMPLE_BLOCK(fltk__FL_SHADOW_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_SHADOW_FRAME);
}

SIMPLE_BLOCK(fltk__FL_ROUNDED_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_ROUNDED_BOX);
}

SIMPLE_BLOCK(fltk__FL_RSHADOW_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_RSHADOW_BOX);
}

SIMPLE_BLOCK(fltk__FL_ROUNDED_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_ROUNDED_FRAME);
}

SIMPLE_BLOCK(fltk__FL_RFLAT_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_RFLAT_BOX);
}

SIMPLE_BLOCK(fltk__FL_ROUND_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_ROUND_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_ROUND_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_ROUND_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_DIAMOND_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_DIAMOND_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_DIAMOND_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_DIAMOND_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_OVAL_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_OVAL_BOX);
}

SIMPLE_BLOCK(fltk__FL_OSHADOW_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_OSHADOW_BOX);
}

SIMPLE_BLOCK(fltk__FL_OVAL_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_OVAL_FRAME);
}

SIMPLE_BLOCK(fltk__FL_OFLAT_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_OFLAT_BOX);
}

SIMPLE_BLOCK(fltk__FL_PLASTIC_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_PLASTIC_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_PLASTIC_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_PLASTIC_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_PLASTIC_UP_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_PLASTIC_UP_FRAME);
}

SIMPLE_BLOCK(fltk__FL_PLASTIC_DOWN_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_PLASTIC_DOWN_FRAME);
}

SIMPLE_BLOCK(fltk__FL_PLASTIC_THIN_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_PLASTIC_THIN_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_PLASTIC_THIN_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_PLASTIC_THIN_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_PLASTIC_ROUND_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_PLASTIC_ROUND_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_PLASTIC_ROUND_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_PLASTIC_ROUND_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_GTK_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_GTK_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_GTK_UP_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_UP_FRAME);
}

SIMPLE_BLOCK(fltk__FL_GTK_DOWN_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_DOWN_FRAME);
}

SIMPLE_BLOCK(fltk__FL_GTK_THIN_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_THIN_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_GTK_THIN_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_THIN_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_GTK_THIN_UP_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_THIN_UP_FRAME);
}

SIMPLE_BLOCK(fltk__FL_GTK_THIN_DOWN_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_THIN_DOWN_FRAME);
}

SIMPLE_BLOCK(fltk__FL_GTK_ROUND_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_ROUND_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_GTK_ROUND_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GTK_ROUND_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_GLEAM_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GLEAM_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_GLEAM_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GLEAM_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_GLEAM_UP_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_GLEAM_UP_FRAME);
}

SIMPLE_BLOCK(fltk__FL_GLEAM_DOWN_FRAME)
{
    SIMPLE_API_RETNUMBER(_FL_GLEAM_DOWN_FRAME);
}

SIMPLE_BLOCK(fltk__FL_GLEAM_THIN_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GLEAM_THIN_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_GLEAM_THIN_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GLEAM_THIN_DOWN_BOX);
}

SIMPLE_BLOCK(fltk__FL_GLEAM_ROUND_UP_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GLEAM_ROUND_UP_BOX);
}

SIMPLE_BLOCK(fltk__FL_GLEAM_ROUND_DOWN_BOX)
{
    SIMPLE_API_RETNUMBER(_FL_GLEAM_ROUND_DOWN_BOX);
}

SIMPLE_BLOCK(fltk_fl_define_FL_ROUND_UP_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_ROUND_UP_BOX());
}

SIMPLE_BLOCK(fltk_fl_define_FL_SHADOW_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_SHADOW_BOX());
}

SIMPLE_BLOCK(fltk_fl_define_FL_ROUNDED_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_ROUNDED_BOX());
}

SIMPLE_BLOCK(fltk_fl_define_FL_RFLAT_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_RFLAT_BOX());
}

SIMPLE_BLOCK(fltk_fl_define_FL_RSHADOW_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_RSHADOW_BOX());
}

SIMPLE_BLOCK(fltk_fl_define_FL_DIAMOND_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_DIAMOND_BOX());
}

SIMPLE_BLOCK(fltk_fl_define_FL_OVAL_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_OVAL_BOX());
}

SIMPLE_BLOCK(fltk_fl_define_FL_PLASTIC_UP_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_PLASTIC_UP_BOX());
}

SIMPLE_BLOCK(fltk_fl_define_FL_GTK_UP_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_GTK_UP_BOX());
}

SIMPLE_BLOCK(fltk_fl_define_FL_GLEAM_UP_BOX)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_GLEAM_UP_BOX());
}

SIMPLE_BLOCK(fltk_fl_box)
{
    Fl_Boxtype num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_box(num1));
}

SIMPLE_BLOCK(fltk_fl_down)
{
    Fl_Boxtype num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_down(num1));
}

SIMPLE_BLOCK(fltk_fl_frame)
{
    Fl_Boxtype num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_frame(num1));
}

SIMPLE_BLOCK(fltk_FL_NORMAL_LABEL)
{
    SIMPLE_API_RETNUMBER(FL_NORMAL_LABEL);
}

SIMPLE_BLOCK(fltk_FL_NO_LABEL)
{
    SIMPLE_API_RETNUMBER(FL_NO_LABEL);
}

SIMPLE_BLOCK(fltk__FL_SHADOW_LABEL)
{
    SIMPLE_API_RETNUMBER(_FL_SHADOW_LABEL);
}

SIMPLE_BLOCK(fltk__FL_ENGRAVED_LABEL)
{
    SIMPLE_API_RETNUMBER(_FL_ENGRAVED_LABEL);
}

SIMPLE_BLOCK(fltk__FL_EMBOSSED_LABEL)
{
    SIMPLE_API_RETNUMBER(_FL_EMBOSSED_LABEL);
}

SIMPLE_BLOCK(fltk__FL_MULTI_LABEL)
{
    SIMPLE_API_RETNUMBER(_FL_MULTI_LABEL);
}

SIMPLE_BLOCK(fltk__FL_ICON_LABEL)
{
    SIMPLE_API_RETNUMBER(_FL_ICON_LABEL);
}

SIMPLE_BLOCK(fltk__FL_IMAGE_LABEL)
{
    SIMPLE_API_RETNUMBER(_FL_IMAGE_LABEL);
}

SIMPLE_BLOCK(fltk_fl_define_FL_SHADOW_LABEL)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_SHADOW_LABEL());
}

SIMPLE_BLOCK(fltk_fl_define_FL_ENGRAVED_LABEL)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_ENGRAVED_LABEL());
}

SIMPLE_BLOCK(fltk_fl_define_FL_EMBOSSED_LABEL)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_define_FL_EMBOSSED_LABEL());
}

SIMPLE_BLOCK(fltk_FL_ALIGN_CENTER)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_CENTER);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_TOP)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_TOP);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_BOTTOM)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_BOTTOM);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_LEFT)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_LEFT);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_RIGHT)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_RIGHT);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_INSIDE)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_INSIDE);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_TEXT_OVER_IMAGE)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_TEXT_OVER_IMAGE);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_IMAGE_OVER_TEXT)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_IMAGE_OVER_TEXT);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_CLIP)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_CLIP);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_WRAP)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_WRAP);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_IMAGE_NEXT_TO_TEXT)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_IMAGE_NEXT_TO_TEXT);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_TEXT_NEXT_TO_IMAGE)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_TEXT_NEXT_TO_IMAGE);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_IMAGE_BACKDROP)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_IMAGE_BACKDROP);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_TOP_LEFT)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_TOP_LEFT);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_TOP_RIGHT)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_TOP_RIGHT);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_BOTTOM_LEFT)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_BOTTOM_LEFT);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_BOTTOM_RIGHT)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_BOTTOM_RIGHT);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_LEFT_TOP)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_LEFT_TOP);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_RIGHT_TOP)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_RIGHT_TOP);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_LEFT_BOTTOM)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_LEFT_BOTTOM);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_RIGHT_BOTTOM)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_RIGHT_BOTTOM);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_NOWRAP)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_NOWRAP);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_POSITION_MASK)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_POSITION_MASK);
}

SIMPLE_BLOCK(fltk_FL_ALIGN_IMAGE_MASK)
{
    SIMPLE_API_RETNUMBER(FL_ALIGN_IMAGE_MASK);
}

SIMPLE_BLOCK(fltk_FL_HELVETICA)
{
    SIMPLE_API_RETNUMBER(FL_HELVETICA);
}

SIMPLE_BLOCK(fltk_FL_HELVETICA_BOLD)
{
    SIMPLE_API_RETNUMBER(FL_HELVETICA_BOLD);
}

SIMPLE_BLOCK(fltk_FL_HELVETICA_ITALIC)
{
    SIMPLE_API_RETNUMBER(FL_HELVETICA_ITALIC);
}

SIMPLE_BLOCK(fltk_FL_HELVETICA_BOLD_ITALIC)
{
    SIMPLE_API_RETNUMBER(FL_HELVETICA_BOLD_ITALIC);
}

SIMPLE_BLOCK(fltk_FL_COURIER)
{
    SIMPLE_API_RETNUMBER(FL_COURIER);
}

SIMPLE_BLOCK(fltk_FL_COURIER_BOLD)
{
    SIMPLE_API_RETNUMBER(FL_COURIER_BOLD);
}

SIMPLE_BLOCK(fltk_FL_COURIER_ITALIC)
{
    SIMPLE_API_RETNUMBER(FL_COURIER_ITALIC);
}

SIMPLE_BLOCK(fltk_FL_COURIER_BOLD_ITALIC)
{
    SIMPLE_API_RETNUMBER(FL_COURIER_BOLD_ITALIC);
}

SIMPLE_BLOCK(fltk_FL_TIMES)
{
    SIMPLE_API_RETNUMBER(FL_TIMES);
}

SIMPLE_BLOCK(fltk_FL_TIMES_BOLD)
{
    SIMPLE_API_RETNUMBER(FL_TIMES_BOLD);
}

SIMPLE_BLOCK(fltk_FL_TIMES_ITALIC)
{
    SIMPLE_API_RETNUMBER(FL_TIMES_ITALIC);
}

SIMPLE_BLOCK(fltk_FL_TIMES_BOLD_ITALIC)
{
    SIMPLE_API_RETNUMBER(FL_TIMES_BOLD_ITALIC);
}

SIMPLE_BLOCK(fltk_FL_SYMBOL)
{
    SIMPLE_API_RETNUMBER(FL_SYMBOL);
}

SIMPLE_BLOCK(fltk_FL_SCREEN)
{
    SIMPLE_API_RETNUMBER(FL_SCREEN);
}

SIMPLE_BLOCK(fltk_FL_SCREEN_BOLD)
{
    SIMPLE_API_RETNUMBER(FL_SCREEN_BOLD);
}

SIMPLE_BLOCK(fltk_FL_ZAPF_DINGBATS)
{
    SIMPLE_API_RETNUMBER(FL_ZAPF_DINGBATS);
}

SIMPLE_BLOCK(fltk_FL_FREE_FONT)
{
    SIMPLE_API_RETNUMBER(FL_FREE_FONT);
}

SIMPLE_BLOCK(fltk_FL_BOLD)
{
    SIMPLE_API_RETNUMBER(FL_BOLD);
}

SIMPLE_BLOCK(fltk_FL_ITALIC)
{
    SIMPLE_API_RETNUMBER(FL_ITALIC);
}

SIMPLE_BLOCK(fltk_FL_BOLD_ITALIC)
{
    SIMPLE_API_RETNUMBER(FL_BOLD_ITALIC);
}

SIMPLE_BLOCK(fltk_FL_NORMAL_SIZE)
{
    SIMPLE_API_RETNUMBER(FL_NORMAL_SIZE);
}

SIMPLE_BLOCK(fltk_FL_FOREGROUND_COLOR)
{
    SIMPLE_API_RETNUMBER(FL_FOREGROUND_COLOR);
}

SIMPLE_BLOCK(fltk_FL_BACKGROUND2_COLOR)
{
    SIMPLE_API_RETNUMBER(FL_BACKGROUND2_COLOR);
}

SIMPLE_BLOCK(fltk_FL_INACTIVE_COLOR)
{
    SIMPLE_API_RETNUMBER(FL_INACTIVE_COLOR);
}

SIMPLE_BLOCK(fltk_FL_SELECTION_COLOR)
{
    SIMPLE_API_RETNUMBER(FL_SELECTION_COLOR);
}

SIMPLE_BLOCK(fltk_FL_GRAY0)
{
    SIMPLE_API_RETNUMBER(FL_GRAY0);
}

SIMPLE_BLOCK(fltk_FL_DARK3)
{
    SIMPLE_API_RETNUMBER(FL_DARK3);
}

SIMPLE_BLOCK(fltk_FL_DARK2)
{
    SIMPLE_API_RETNUMBER(FL_DARK2);
}

SIMPLE_BLOCK(fltk_FL_DARK1)
{
    SIMPLE_API_RETNUMBER(FL_DARK1);
}

SIMPLE_BLOCK(fltk_FL_BACKGROUND_COLOR)
{
    SIMPLE_API_RETNUMBER(FL_BACKGROUND_COLOR);
}

SIMPLE_BLOCK(fltk_FL_LIGHT1)
{
    SIMPLE_API_RETNUMBER(FL_LIGHT1);
}

SIMPLE_BLOCK(fltk_FL_LIGHT2)
{
    SIMPLE_API_RETNUMBER(FL_LIGHT2);
}

SIMPLE_BLOCK(fltk_FL_LIGHT3)
{
    SIMPLE_API_RETNUMBER(FL_LIGHT3);
}

SIMPLE_BLOCK(fltk_FL_BLACK)
{
    SIMPLE_API_RETNUMBER(FL_BLACK);
}

SIMPLE_BLOCK(fltk_FL_RED)
{
    SIMPLE_API_RETNUMBER(FL_RED);
}

SIMPLE_BLOCK(fltk_FL_GREEN)
{
    SIMPLE_API_RETNUMBER(FL_GREEN);
}

SIMPLE_BLOCK(fltk_FL_YELLOW)
{
    SIMPLE_API_RETNUMBER(FL_YELLOW);
}

SIMPLE_BLOCK(fltk_FL_BLUE)
{
    SIMPLE_API_RETNUMBER(FL_BLUE);
}

SIMPLE_BLOCK(fltk_FL_MAGENTA)
{
    SIMPLE_API_RETNUMBER(FL_MAGENTA);
}

SIMPLE_BLOCK(fltk_FL_CYAN)
{
    SIMPLE_API_RETNUMBER(FL_CYAN);
}

SIMPLE_BLOCK(fltk_FL_DARK_RED)
{
    SIMPLE_API_RETNUMBER(FL_DARK_RED);
}

SIMPLE_BLOCK(fltk_FL_DARK_GREEN)
{
    SIMPLE_API_RETNUMBER(FL_DARK_GREEN);
}

SIMPLE_BLOCK(fltk_FL_DARK_YELLOW)
{
    SIMPLE_API_RETNUMBER(FL_DARK_YELLOW);
}

SIMPLE_BLOCK(fltk_FL_DARK_BLUE)
{
    SIMPLE_API_RETNUMBER(FL_DARK_BLUE);
}

SIMPLE_BLOCK(fltk_FL_DARK_MAGENTA)
{
    SIMPLE_API_RETNUMBER(FL_DARK_MAGENTA);
}

SIMPLE_BLOCK(fltk_FL_DARK_CYAN)
{
    SIMPLE_API_RETNUMBER(FL_DARK_CYAN);
}

SIMPLE_BLOCK(fltk_FL_WHITE)
{
    SIMPLE_API_RETNUMBER(FL_WHITE);
}

SIMPLE_BLOCK(fltk_fl_inactive)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_inactive(num1));
}

SIMPLE_BLOCK(fltk_fl_contrast)
{
    Fl_Color num1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(fl_contrast(num1,num2));
}

SIMPLE_BLOCK(fltk_fl_color_average)
{
    Fl_Color num1;
    Fl_Color num2;
    float num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (float) (float) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(fl_color_average(num1,num2,num3));
}

SIMPLE_BLOCK(fltk_fl_lighter)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_lighter(num1));
}

SIMPLE_BLOCK(fltk_fl_darker)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_darker(num1));
}

SIMPLE_BLOCK(fltk_fl_rgb_color)
{
    uchar num1;
    uchar num2;
    uchar num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (uchar) SIMPLE_API_GETNUMBER(1);
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    num3 = (uchar) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(fl_rgb_color(num1,num2,num3));
}

SIMPLE_BLOCK(fltk_fl_rgb_color_1)
{
    uchar num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (uchar) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_rgb_color(num1));
}

SIMPLE_BLOCK(fltk_fl_gray_ramp)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_gray_ramp(num1));
}

SIMPLE_BLOCK(fltk_fl_color_cube)
{
    int num1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(fl_color_cube(num1,num2,num3));
}

#ifndef FL_DOXYGEN
SIMPLE_BLOCK(fltk_fl_Fl_e_number)
{
    SIMPLE_API_RETNUMBER(Fl::e_number);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_x)
{
    SIMPLE_API_RETNUMBER(Fl::e_x);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_x_1)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::e_x = num1;
}

SIMPLE_BLOCK(fltk_fl_Fl_e_y)
{
    SIMPLE_API_RETNUMBER(Fl::e_y);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_y_1)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::e_y = num1;
}

SIMPLE_BLOCK(fltk_fl_Fl_e_x_root)
{
    SIMPLE_API_RETNUMBER(Fl::e_x_root);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_y_root)
{
    SIMPLE_API_RETNUMBER(Fl::e_y_root);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_dx)
{
    SIMPLE_API_RETNUMBER(Fl::e_dx);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_dy)
{
    SIMPLE_API_RETNUMBER(Fl::e_dy);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_state)
{
    SIMPLE_API_RETNUMBER(Fl::e_state);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_clicks)
{
    SIMPLE_API_RETNUMBER(Fl::e_clicks);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_is_click)
{
    SIMPLE_API_RETNUMBER(Fl::e_is_click);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_keysym)
{
    SIMPLE_API_RETNUMBER(Fl::e_keysym);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_text)
{
    SIMPLE_API_RETSTRING(Fl::e_text);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_length)
{
    SIMPLE_API_RETNUMBER(Fl::e_length);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_clipboard_data)
{
    SIMPLE_API_RETCPOINTER(Fl::e_clipboard_data,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_e_clipboard_type)
{
    SIMPLE_API_RETSTRING(Fl::e_clipboard_type);
}

SIMPLE_BLOCK(fltk_fl_Fl_e_dispatch)
{
    SIMPLE_API_RETCPOINTER(Fl::e_dispatch,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_belowmouse_)
{
    SIMPLE_API_RETCPOINTER(Fl::belowmouse_,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_pushed_)
{
    SIMPLE_API_RETCPOINTER(Fl::pushed_, "SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_set_pushed_)
{
    Fl_Widget* point1;
    if (SIMPLE_API_PARACOUNT != 1) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return;
    }
    point1 = (Fl_Widget*)SIMPLE_API_GETCPOINTER(1, "SMOOTHC_FLTK");
    Fl_Tooltip::current(point1);
    Fl::pushed_ = point1;
}

SIMPLE_BLOCK(fltk_fl_Fl_focus_)
{
    SIMPLE_API_RETCPOINTER(Fl::focus_,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_damage_)
{
    SIMPLE_API_RETNUMBER(Fl::damage_);
}

SIMPLE_BLOCK(fltk_fl_Fl_selection_owner_)
{
    SIMPLE_API_RETCPOINTER(Fl::selection_owner_,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_modal_)
{
    SIMPLE_API_RETCPOINTER(Fl::modal_,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_grab_)
{
    SIMPLE_API_RETCPOINTER(Fl::grab_,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_compose_state)
{
    SIMPLE_API_RETNUMBER(Fl::compose_state);
}

SIMPLE_BLOCK(fltk_fl_Fl_call_screen_init)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::call_screen_init();
}

#ifdef __APPLE__
SIMPLE_BLOCK(fltk_fl_Fl_reset_marked_text)
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	Fl::reset_marked_text();
}

SIMPLE_BLOCK(fltk_fl_Fl_insertion_point_location)
{
	int num1;
	int num2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	Fl::insertion_point_location(num1,num2,num3);
}
#endif
#endif

SIMPLE_BLOCK(fltk_fl_Fl_damage)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::damage(num1);
}

SIMPLE_BLOCK(fltk_fl_OPTION_ARROW_FOCUS)
{
    SIMPLE_API_RETNUMBER(Fl::OPTION_ARROW_FOCUS);
}

SIMPLE_BLOCK(fltk_fl_OPTION_VISIBLE_FOCUS)
{
    SIMPLE_API_RETNUMBER(Fl::OPTION_VISIBLE_FOCUS);
}

SIMPLE_BLOCK(fltk_fl_OPTION_DND_TEXT)
{
    SIMPLE_API_RETNUMBER(Fl::OPTION_DND_TEXT);
}

SIMPLE_BLOCK(fltk_fl_OPTION_SHOW_TOOLTIPS)
{
    SIMPLE_API_RETNUMBER(Fl::OPTION_SHOW_TOOLTIPS);
}

SIMPLE_BLOCK(fltk_fl_OPTION_FNFC_USES_GTK)
{
    SIMPLE_API_RETNUMBER(Fl::OPTION_FNFC_USES_GTK);
}

SIMPLE_BLOCK(fltk_fl_Fl_option)
{
    Fl::Fl_Option num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl::Fl_Option) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::option(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_option_1)
{
    Fl::Fl_Option num1;
    bool num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (Fl::Fl_Option) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (bool) (int) SIMPLE_API_GETNUMBER(2);
    Fl::option(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_Fl_awake_ring_size_)
{
    SIMPLE_API_RETNUMBER(Fl::awake_ring_size_);
}

SIMPLE_BLOCK(fltk_fl_Fl_awake_ring_head_)
{
    SIMPLE_API_RETNUMBER(Fl::awake_ring_head_);
}

SIMPLE_BLOCK(fltk_fl_Fl_awake_ring_tail_)
{
    SIMPLE_API_RETNUMBER(Fl::awake_ring_tail_);
}

SIMPLE_BLOCK(fltk_fl_Fl_scheme_)
{
    SIMPLE_API_RETSTRING(Fl::scheme_);
}

SIMPLE_BLOCK(fltk_fl_Fl_scheme_bg_)
{
    SIMPLE_API_RETCPOINTER(Fl::scheme_bg_,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_e_original_keysym)
{
    SIMPLE_API_RETNUMBER(Fl::e_original_keysym);
}

SIMPLE_BLOCK(fltk_fl_Fl_scrollbar_size_)
{
    SIMPLE_API_RETNUMBER(Fl::scrollbar_size_);
}

SIMPLE_BLOCK(fltk_fl_Fl_add_awake_handler_)
{
    Fl_Awake_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Awake_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::add_awake_handler_(point1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_get_awake_handler_)
{
    Fl_Awake_Handler* point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Awake_Handler*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::get_awake_handler_(*point1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_version)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::version());
}

SIMPLE_BLOCK(fltk_fl_Fl_api_version)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::api_version());
}

SIMPLE_BLOCK(fltk_fl_Fl_abi_version)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::abi_version());
}

SIMPLE_BLOCK(fltk_fl_Fl_abi_check)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::abi_check(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_arg)
{
    int num1;
    char* * point2;
    int* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (char* *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::arg(num1,point2,*point3));
}

SIMPLE_BLOCK(fltk_fl_Fl_args)
{
    int num1;
    char* * point2;
    int* point3;
    Fl_Args_Handler point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (char* *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (Fl_Args_Handler) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::args(num1,point2,*point3,point4));
}

SIMPLE_BLOCK(fltk_fl_Fl_args_1)
{
    int num1;
    char* * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (char* *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::args(num1,point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_help)
{
    SIMPLE_API_RETCPOINTER(Fl::help,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_display)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    Fl::display(str1);
}

SIMPLE_BLOCK(fltk_fl_Fl_visual)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::visual(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_gl_visual)
{
    int num1;
    int * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
#ifdef gl_visual
    SIMPLE_API_RETNUMBER(Fl::gl_visual(num1,point2));
#else
    SIMPLE_API_RETNUMBER((int)0);
#endif
}

SIMPLE_BLOCK(fltk_fl_Fl_own_colormap)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::own_colormap();
}

SIMPLE_BLOCK(fltk_fl_Fl_get_system_colors)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::get_system_colors();
}

SIMPLE_BLOCK(fltk_fl_Fl_foreground)
{
    uchar num1;
    uchar num2;
    uchar num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (uchar) SIMPLE_API_GETNUMBER(1);
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    num3 = (uchar) SIMPLE_API_GETNUMBER(3);
    Fl::foreground(num1,num2,num3);
}

SIMPLE_BLOCK(fltk_fl_Fl_background)
{
    uchar num1;
    uchar num2;
    uchar num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (uchar) SIMPLE_API_GETNUMBER(1);
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    num3 = (uchar) SIMPLE_API_GETNUMBER(3);
    Fl::background(num1,num2,num3);
}

SIMPLE_BLOCK(fltk_fl_Fl_background2)
{
    uchar num1;
    uchar num2;
    uchar num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (uchar) SIMPLE_API_GETNUMBER(1);
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    num3 = (uchar) SIMPLE_API_GETNUMBER(3);
    Fl::background2(num1,num2,num3);
}

SIMPLE_BLOCK(fltk_fl_Fl_scheme)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETNUMBER(Fl::scheme(str1));
}

SIMPLE_BLOCK(fltk_fl_Fl_scheme_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETSTRING(Fl::scheme());
}

SIMPLE_BLOCK(fltk_fl_Fl_is_scheme)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETNUMBER(Fl::is_scheme(str1));
}

SIMPLE_BLOCK(fltk_fl_Fl_reload_scheme)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::reload_scheme());
}

SIMPLE_BLOCK(fltk_fl_Fl_scrollbar_size)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::scrollbar_size());
}

SIMPLE_BLOCK(fltk_fl_Fl_scrollbar_size_1)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::scrollbar_size(num1);
}

SIMPLE_BLOCK(fltk_fl_Fl_wait)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::wait());
}

SIMPLE_BLOCK(fltk_fl_Fl_wait_1)
{
    double num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::wait(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_check)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::check());
}

SIMPLE_BLOCK(fltk_fl_Fl_ready)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::ready());
}

SIMPLE_BLOCK(fltk_fl_Fl_run)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::run());
}

SIMPLE_BLOCK(fltk_fl_Fl_readqueue)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl::readqueue(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_add_timeout)
{
    double num1;
    Fl_Timeout_Handler point2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Timeout_Handler) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    Fl::add_timeout(num1,point2,point3);
}

SIMPLE_BLOCK(fltk_fl_Fl_repeat_timeout)
{
    double num1;
    Fl_Timeout_Handler point2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Timeout_Handler) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    Fl::repeat_timeout(num1,point2,point3);
}

SIMPLE_BLOCK(fltk_fl_Fl_has_timeout)
{
    Fl_Timeout_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Timeout_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::has_timeout(point1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_remove_timeout)
{
    Fl_Timeout_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Timeout_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::remove_timeout(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_add_check)
{
    Fl_Timeout_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Timeout_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::add_check(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_has_check)
{
    Fl_Timeout_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Timeout_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::has_check(point1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_remove_check)
{
    Fl_Timeout_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Timeout_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::remove_check(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_add_fd)
{
    int num1;
    int num2;
    Fl_FD_Handler point3;
    void* point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (Fl_FD_Handler) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (void*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    Fl::add_fd(num1,num2,point3,point4);
}

SIMPLE_BLOCK(fltk_fl_Fl_add_fd_1)
{
    int num1;
    Fl_FD_Handler point2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_FD_Handler) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    Fl::add_fd(num1,point2,point3);
}

SIMPLE_BLOCK(fltk_fl_Fl_remove_fd)
{
    int num1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    Fl::remove_fd(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_Fl_remove_fd_1)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::remove_fd(num1);
}

SIMPLE_BLOCK(fltk_fl_Fl_add_idle)
{
    Fl_Idle_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Idle_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::add_idle(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_has_idle)
{
    Fl_Idle_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Idle_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::has_idle(point1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_remove_idle)
{
    Fl_Idle_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Idle_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::remove_idle(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_damage_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::damage());
}

SIMPLE_BLOCK(fltk_fl_Fl_redraw)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::redraw();
}

SIMPLE_BLOCK(fltk_fl_Fl_flush)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::flush();
}

SIMPLE_BLOCK(fltk_fl_Fl_first_window)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl::first_window(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_first_window_1)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::first_window(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_next_window)
{
    const Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (const Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(Fl::next_window(point1),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_modal)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl::modal(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_grab)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl::grab(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_grab_1)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::grab(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_event)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_x)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_x());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_y)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_y());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_x_root)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_x_root());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_y_root)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_y_root());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_dx)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_dx());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_dy)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_dy());
}

SIMPLE_BLOCK(fltk_fl_Fl_get_mouse)
{
    int * point1;
    int * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::get_mouse(*point1,*point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_event_clicks)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_clicks());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_clicks_1)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::event_clicks(num1);
}

SIMPLE_BLOCK(fltk_fl_Fl_event_is_click)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_is_click());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_is_click_1)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::event_is_click(num1);
}

SIMPLE_BLOCK(fltk_fl_Fl_event_button)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_button());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_state)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_state());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_state_1)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::event_state(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_event_key)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_key());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_original_key)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_original_key());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_key_1)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::event_key(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_get_key)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::get_key(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_event_text)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETSTRING(Fl::event_text());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_length)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_length());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_clipboard)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::event_clipboard();
}

SIMPLE_BLOCK(fltk_fl_Fl_event_clipboard_type)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETSTRING(Fl::event_clipboard_type());
}

SIMPLE_BLOCK(fltk_fl_Fl_compose)
{
    int * point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::compose(*point1));
}

SIMPLE_BLOCK(fltk_fl_Fl_compose_reset)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::compose_reset();
}

SIMPLE_BLOCK(fltk_fl_Fl_event_inside)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETNUMBER(Fl::event_inside(num1,num2,num3,num4));
}

SIMPLE_BLOCK(fltk_fl_Fl_event_inside_1)
{
    const Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (const Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::event_inside(point1));
}

SIMPLE_BLOCK(fltk_fl_Fl_test_shortcut)
{
    Fl_Shortcut num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Shortcut) (unsigned int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::test_shortcut(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_enable_im)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::enable_im();
}

SIMPLE_BLOCK(fltk_fl_Fl_disable_im)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::disable_im();
}

SIMPLE_BLOCK(fltk_fl_Fl_handle)
{
    int num1;
    Fl_Window* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Window*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::handle(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_handle_)
{
    int num1;
    Fl_Window* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Window*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::handle_(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_belowmouse)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl::belowmouse(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_belowmouse_1)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::belowmouse(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_pushed)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl::pushed(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_pushed_1)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::pushed(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_focus)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl::focus(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_focus_1)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::focus(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_add_handler)
{
    Fl_Event_Handler point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Event_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::add_handler(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_remove_handler)
{
    Fl_Event_Handler point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Event_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::remove_handler(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_add_system_handler)
{
    Fl_System_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_System_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::add_system_handler(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_remove_system_handler)
{
    Fl_System_Handler point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_System_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::remove_system_handler(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_event_dispatch)
{
    CallbackStruct::_sState = ((VM*)pointer)->sState;
    int num1;
    if (SIMPLE_API_PARACOUNT != 1) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return;
    }
    num1 = (int) SIMPLE_API_GETNUMBER(1);
    if (num1 == 0) {
        CallbackStruct::ret_evt_to_fl = false;
    }
    Fl::event_dispatch(simple_Fl_Event_Dispatch);
}

SIMPLE_BLOCK(fltk_fl_Fl_event_dispatch_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl::event_dispatch(),"SMOOTHC_FLTK");
}

#if FLTK_ABI_VERSION >= 10303 || defined(FL_DOXYGEN)
SIMPLE_BLOCK(fltk_fl_Fl_copy)
{
	const char* str1;
	int num2;
	int num3;
	const char* str4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	str1 = (const char*)  SIMPLE_API_GETSTRING(1);
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	str4 = (const char*)  SIMPLE_API_GETSTRING(4);
	Fl::copy(str1,num2,num3,str4);
}
#else

SIMPLE_BLOCK(fltk_fl_Fl_copy_1)
{
    const char* str1;
    int num2;
    int num3;
    const char* str4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    Fl::copy(str1,num2,num3,str4);
}

SIMPLE_BLOCK(fltk_fl_Fl_copy_2)
{
    const char* str1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    Fl::copy(str1,num2,num3);
}
#endif

#if !(defined(__APPLE__) || defined(WIN32) || defined(FL_DOXYGEN)) && defined(copy_image)
SIMPLE_BLOCK(fltk_fl_Fl_copy_image)
{
	const unsigned char* point1;
	int num2;
	int num3;
	int num4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	point1 = (const unsigned char*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
	Fl::copy_image(point1,num2,num3,num4);
}
#endif

#if FLTK_ABI_VERSION >= 10303 || defined(FL_DOXYGEN)
SIMPLE_BLOCK(fltk_fl_Fl_paste)
{
	Fl_Widget * point1;
	int num2;
	const char* str3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	str3 = (const char*)  SIMPLE_API_GETSTRING(3);
	Fl::paste(*point1,num2,str3);
}
#else

SIMPLE_BLOCK(fltk_fl_Fl_paste_1)
{
    Fl_Widget * point1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    Fl::paste(*point1,num2,str3);
}

SIMPLE_BLOCK(fltk_fl_Fl_paste_2)
{
    Fl_Widget * point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    Fl::paste(*point1,num2);
}
#endif

SIMPLE_BLOCK(fltk_fl_Fl_add_clipboard_notify)
{
    Fl_Clipboard_Notify_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Clipboard_Notify_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::add_clipboard_notify(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_remove_clipboard_notify)
{
    Fl_Clipboard_Notify_Handler point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Clipboard_Notify_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::remove_clipboard_notify(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_clipboard_contains)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETNUMBER(Fl::clipboard_contains(str1));
}

SIMPLE_BLOCK(fltk_fl_Fl_clipboard_plain_text)
{
    SIMPLE_API_RETSTRING(Fl::clipboard_plain_text);
}

SIMPLE_BLOCK(fltk_fl_Fl_clipboard_image)
{
    SIMPLE_API_RETSTRING(Fl::clipboard_image);
}

SIMPLE_BLOCK(fltk_fl_Fl_dnd)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::dnd());
}

SIMPLE_BLOCK(fltk_fl_Fl_selection_owner)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl::selection_owner(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_selection_owner_1)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::selection_owner(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_selection)
{
    Fl_Widget * point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    Fl::selection(*point1,str2,num3);
}

SIMPLE_BLOCK(fltk_fl_Fl_paste_3)
{
    Fl_Widget * point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::paste(*point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_x)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::x());
}

SIMPLE_BLOCK(fltk_fl_Fl_y)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::y());
}

SIMPLE_BLOCK(fltk_fl_Fl_w)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::w());
}

SIMPLE_BLOCK(fltk_fl_Fl_h)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::h());
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_count)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::screen_count());
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_xywh)
{
    int * point1;
    int * point2;
    int * point3;
    int * point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    Fl::screen_xywh(*point1,*point2,*point3,*point4);
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_xywh_1)
{
    int * point1;
    int * point2;
    int * point3;
    int * point4;
    int num5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    Fl::screen_xywh(*point1,*point2,*point3,*point4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_xywh_2)
{
    int * point1;
    int * point2;
    int * point3;
    int * point4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    Fl::screen_xywh(*point1,*point2,*point3,*point4,num5);
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_xywh_3)
{
    int * point1;
    int * point2;
    int * point3;
    int * point4;
    int num5;
    int num6;
    int num7;
    int num8;
    if ( SIMPLE_API_PARACOUNT != 8 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
        return ;
    }
    point1 = (int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    num8 = (int) (int) SIMPLE_API_GETNUMBER(8);
    Fl::screen_xywh(*point1,*point2,*point3,*point4,num5,num6,num7,num8);
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_num)
{
    int num1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(Fl::screen_num(num1,num2));
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_num_1)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETNUMBER(Fl::screen_num(num1,num2,num3,num4));
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_dpi)
{
    float * point1;
    float * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (float *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (float *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    Fl::screen_dpi(*point1,*point2,num3);
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_work_area)
{
    int * point1;
    int * point2;
    int * point3;
    int * point4;
    int num5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    Fl::screen_work_area(*point1,*point2,*point3,*point4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_work_area_1)
{
    int * point1;
    int * point2;
    int * point3;
    int * point4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    Fl::screen_work_area(*point1,*point2,*point3,*point4,num5);
}

SIMPLE_BLOCK(fltk_fl_Fl_screen_work_area_2)
{
    int * point1;
    int * point2;
    int * point3;
    int * point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    Fl::screen_work_area(*point1,*point2,*point3,*point4);
}

SIMPLE_BLOCK(fltk_fl_Fl_set_color)
{
    Fl_Color num1;
    uchar num2;
    uchar num3;
    uchar num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    num3 = (uchar) SIMPLE_API_GETNUMBER(3);
    num4 = (uchar) SIMPLE_API_GETNUMBER(4);
    Fl::set_color(num1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_Fl_set_color_1)
{
    Fl_Color num1;
    unsigned num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (unsigned) (int) SIMPLE_API_GETNUMBER(2);
    Fl::set_color(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_Fl_get_color)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::get_color(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_get_color_1)
{
    Fl_Color num1;
    uchar * point2;
    uchar * point3;
    uchar * point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (uchar *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (uchar *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (uchar *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    Fl::get_color(num1,*point2,*point3,*point4);
}

SIMPLE_BLOCK(fltk_fl_Fl_free_color)
{
    Fl_Color num1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    Fl::free_color(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_Fl_get_font)
{
    Fl_Font num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETSTRING(Fl::get_font(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_get_font_name)
{
    Fl_Font num1;
    int* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(Fl::get_font_name(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_get_font_sizes)
{
    Fl_Font num1;
    int* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::get_font_sizes(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_set_font)
{
    Fl_Font num1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    Fl::set_font(num1,str2);
}

SIMPLE_BLOCK(fltk_fl_Fl_set_font_1)
{
    Fl_Font num1;
    Fl_Font num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    Fl::set_font(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_Fl_set_fonts)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETNUMBER(Fl::set_fonts(str1));
}

SIMPLE_BLOCK(fltk_fl_Fl_set_labeltype)
{
    Fl_Labeltype num1;
    Fl_Label_Draw_F* point2;
    Fl_Label_Measure_F* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (Fl_Labeltype) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Label_Draw_F*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (Fl_Label_Measure_F*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    Fl::set_labeltype(num1,point2,point3);
}

#ifdef set_labeltype
SIMPLE_BLOCK(fltk_fl_Fl_set_labeltype_1)
{
	Fl_Labeltype num1;
	Fl_Labeltype num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	num1 = (Fl_Labeltype) (int) SIMPLE_API_GETNUMBER(1);
	num2 = (Fl_Labeltype) (int) SIMPLE_API_GETNUMBER(2);
	Fl::set_labeltype(num1,num2);
}
#endif

SIMPLE_BLOCK(fltk_fl_Fl_get_boxtype)
{
    Fl_Boxtype num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETCPOINTER(Fl::get_boxtype(num1),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_set_boxtype)
{
    Fl_Boxtype num1;
    Fl_Box_Draw_F* point2;
    uchar num3;
    uchar num4;
    uchar num5;
    uchar num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Box_Draw_F*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (uchar) SIMPLE_API_GETNUMBER(3);
    num4 = (uchar) SIMPLE_API_GETNUMBER(4);
    num5 = (uchar) SIMPLE_API_GETNUMBER(5);
    num6 = (uchar) SIMPLE_API_GETNUMBER(6);
    Fl::set_boxtype(num1,point2,num3,num4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_Fl_set_boxtype_1)
{
    Fl_Boxtype num1;
    Fl_Boxtype num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(2);
    Fl::set_boxtype(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_Fl_box_dx)
{
    Fl_Boxtype num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::box_dx(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_box_dy)
{
    Fl_Boxtype num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::box_dy(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_box_dw)
{
    Fl_Boxtype num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::box_dw(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_box_dh)
{
    Fl_Boxtype num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::box_dh(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_draw_box_active)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::draw_box_active());
}

SIMPLE_BLOCK(fltk_fl_Fl_box_color)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(Fl::box_color(num1));
}

SIMPLE_BLOCK(fltk_fl_Fl_set_box_color)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    Fl::set_box_color(num1);
}

SIMPLE_BLOCK(fltk_fl_Fl_set_abort)
{
    Fl_Abort_Handler point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Abort_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::set_abort(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_default_atclose)
{
    Fl_Window* point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl::default_atclose(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_Fl_set_atclose)
{
    Fl_Atclose_Handler point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Atclose_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::set_atclose(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_event_shift)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_shift());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_ctrl)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_ctrl());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_command)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_command());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_alt)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_alt());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_buttons)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_buttons());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_button1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_button1());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_button2)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_button2());
}

SIMPLE_BLOCK(fltk_fl_Fl_event_button3)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::event_button3());
}

SIMPLE_BLOCK(fltk_fl_Fl_set_idle)
{
    Fl_Old_Idle_Handler point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Old_Idle_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::set_idle(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_grab_2)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::grab(*point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_release)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::release();
}

SIMPLE_BLOCK(fltk_fl_Fl_visible_focus)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::visible_focus(num1);
}

SIMPLE_BLOCK(fltk_fl_Fl_visible_focus_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::visible_focus());
}

SIMPLE_BLOCK(fltk_fl_Fl_dnd_text_ops)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::dnd_text_ops(num1);
}

SIMPLE_BLOCK(fltk_fl_Fl_dnd_text_ops_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::dnd_text_ops());
}

SIMPLE_BLOCK(fltk_fl_Fl_lock)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::lock());
}

SIMPLE_BLOCK(fltk_fl_Fl_unlock)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::unlock();
}

SIMPLE_BLOCK(fltk_fl_Fl_awake)
{
    void* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (void*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::awake(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_awake_1)
{
    Fl_Awake_Handler point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Awake_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl::awake(point1,point2));
}

SIMPLE_BLOCK(fltk_fl_Fl_thread_message)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::thread_message();
}

SIMPLE_BLOCK(fltk_fl_Fl_delete_widget)
{
    Fl_Widget * point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::delete_widget(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_do_widget_deletion)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl::do_widget_deletion();
}

SIMPLE_BLOCK(fltk_fl_Fl_watch_widget_pointer)
{
    Fl_Widget * point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::watch_widget_pointer(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_release_widget_pointer)
{
    Fl_Widget * point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::release_widget_pointer(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_clear_widget_pointer)
{
    const Fl_Widget  * point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (const Fl_Widget  *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl::clear_widget_pointer(point1);
}

SIMPLE_BLOCK(fltk_fl_Fl_use_high_res_GL)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl::use_high_res_GL(num1);
}

SIMPLE_BLOCK(fltk_fl_Fl_use_high_res_GL_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl::use_high_res_GL());
}

#ifdef FLTK_HAVE_CAIRO
SIMPLE_BLOCK(fltk_fl_Fl_cairo_make_current)
{
	Fl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(Fl::cairo_make_current(point1),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_cairo_autolink_context)
{
	bool num1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	num1 = (bool) (int) SIMPLE_API_GETNUMBER(1);
	Fl::cairo_autolink_context(num1);
}

SIMPLE_BLOCK(fltk_fl_Fl_cairo_autolink_context_1)
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETNUMBER(Fl::cairo_autolink_context());
}

SIMPLE_BLOCK(fltk_fl_Fl_cairo_cc)
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETCPOINTER(Fl::cairo_cc(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_Fl_cairo_cc_1)
{
	struct cairo_t * point1;
	bool num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (struct cairo_t *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (bool) (int) SIMPLE_API_GETNUMBER(2);
	Fl::cairo_cc(point1,num2);
}
#endif

/* Fl_Wiget_Tracker */
SIMPLE_BLOCK(fltk_fl_widget_tracker_Fl_Widget_Tracker)
{
    Fl_Widget * point2;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point2 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(new Fl_Widget_Tracker(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_tracker_widget)
{
    Fl_Widget_Tracker* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget_Tracker*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->widget(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_tracker_deleted)
{
    Fl_Widget_Tracker* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget_Tracker*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->deleted());
}

SIMPLE_BLOCK(fltk_fl_widget_tracker_exists)
{
    Fl_Widget_Tracker* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget_Tracker*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->exists());
}

/* Fl_Adjuster */
SIMPLE_BLOCK(fltk_fl_adjuster_Fl_Adjuster)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Adjuster(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_adjuster_soft)
{
    Fl_Adjuster* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Adjuster*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->soft(num2);
}

SIMPLE_BLOCK(fltk_fl_adjuster_soft_1)
{
    Fl_Adjuster* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Adjuster*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->soft());
}

/* fl_ask */
SIMPLE_BLOCK(fltk_FL_BEEP_DEFAULT)
{
    SIMPLE_API_RETNUMBER(FL_BEEP_DEFAULT);
}

SIMPLE_BLOCK(fltk_FL_BEEP_MESSAGE)
{
    SIMPLE_API_RETNUMBER(FL_BEEP_MESSAGE);
}

SIMPLE_BLOCK(fltk_FL_BEEP_ERROR)
{
    SIMPLE_API_RETNUMBER(FL_BEEP_ERROR);
}

SIMPLE_BLOCK(fltk_FL_BEEP_QUESTION)
{
    SIMPLE_API_RETNUMBER(FL_BEEP_QUESTION);
}

SIMPLE_BLOCK(fltk_FL_BEEP_PASSWORD)
{
    SIMPLE_API_RETNUMBER(FL_BEEP_PASSWORD);
}

SIMPLE_BLOCK(fltk_fl_beep)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    fl_beep(num1);
}

SIMPLE_BLOCK(fltk_fl_message)
{
    const char* str1;
    void * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    point2 = (void *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    fl_message(str1,point2);
}

SIMPLE_BLOCK(fltk_fl_alert)
{
    const char* str1;
    void * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    point2 = (void *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    fl_alert(str1,point2);
}

SIMPLE_BLOCK(fltk_fl_ask)
{
    const char* str1;
    void * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    point2 = (void *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(fl_ask(str1,point2));
}

SIMPLE_BLOCK(fltk_fl_choice)
{
    const char* str1;
    const char* str2;
    const char* str3;
    const char* str4;
    void * point5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    point5 = (void *) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(fl_choice(str1,str2,str3,str4,point5));
}

SIMPLE_BLOCK(fltk_fl_input)
{
    const char* str1;
    const char* str2;
    void * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point3 = (void *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(fl_input(str1,str2,point3));
}

SIMPLE_BLOCK(fltk_fl_password)
{
    const char* str1;
    const char* str2;
    void * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point3 = (void *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(fl_password(str1,str2,point3));
}

SIMPLE_BLOCK(fltk_fl_message_icon)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(fl_message_icon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_message_font_)
{
    SIMPLE_API_RETCPOINTER(fl_message_font_,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_message_size_)
{
    SIMPLE_API_RETCPOINTER(fl_message_size_,"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_message_font)
{
    Fl_Font point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    fl_message_font(point1,point2);
}

/* Fl_Bitmap */
SIMPLE_BLOCK(fltk_fl_bitmap_Fl_Bitmap)
{
    const uchar* point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point2 = (const uchar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(new Fl_Bitmap(point2,num3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_bitmap_Fl_Bitmap_1)
{
    const char* str2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str2 = (const char*)  SIMPLE_API_GETSTRING(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(new Fl_Bitmap(str2,num3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_bitmap_copy)
{
    Fl_Bitmap* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Bitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->copy(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_bitmap_copy_1)
{
    Fl_Bitmap* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Bitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->copy(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_bitmap_draw)
{
    Fl_Bitmap* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Bitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    point1->draw(num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_bitmap_draw_1)
{
    Fl_Bitmap* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Bitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->draw(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_bitmap_label)
{
    Fl_Bitmap* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Bitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->label(point2);
}

SIMPLE_BLOCK(fltk_fl_bitmap_label_1)
{
    Fl_Bitmap* point1;
    Fl_Menu_Item* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Bitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Menu_Item*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->label(point2);
}

SIMPLE_BLOCK(fltk_fl_bitmap_uncache)
{
    Fl_Bitmap* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Bitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->uncache();
}

/* Fl_BMP_Image */
#ifdef Fl_BMP_Image
SIMPLE_BLOCK(fltk_fl_bmp_image_Fl_BMP_Image)
{
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	str2 = (const char*)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETCPOINTER(new Fl_BMP_Image(str2),"SMOOTHC_FLTK");
}
#endif

/* Fl_Box */
SIMPLE_BLOCK(fltk_fl_box_Fl_Box)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(5))->str ;
    SIMPLE_API_RETCPOINTER(new Fl_Box(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_box_Fl_Box_1)
{
    Fl_Boxtype point2;
    int num3;
    int num4;
    int num5;
    int num6;
    const char* str7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point2 = (Fl_Boxtype)(int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    str7 = (const char*)  SIMPLE_API_GETSTRING(7);
    SIMPLE_API_RETCPOINTER(new Fl_Box(point2,num3,num4,num5,num6,str7),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_box_handle)
{
    Fl_Box* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Box*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

/* Fl_Browser */
SIMPLE_BLOCK(fltk_fl_browser_remove)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->remove(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_add)
{
    Fl_Browser* point1;
    const char* str2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->add(str2,point3);
}

SIMPLE_BLOCK(fltk_fl_browser_insert)
{
    Fl_Browser* point1;
    int num2;
    const char* str3;
    void* point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point4 = (void*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point1->insert(num2,str3,point4);
}

SIMPLE_BLOCK(fltk_fl_browser_move)
{
    Fl_Browser* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->move(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_browser_load)
{
    Fl_Browser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->load(str2));
}

SIMPLE_BLOCK(fltk_fl_browser_swap)
{
    Fl_Browser* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->swap(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_browser_clear)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_browser_size)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->size());
}

SIMPLE_BLOCK(fltk_fl_browser_size_1)
{
    Fl_Browser* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->size(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_browser_textsize)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->textsize());
}

SIMPLE_BLOCK(fltk_fl_browser_textsize_1)
{
    Fl_Browser* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_browser_topline)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->topline());
}

SIMPLE_BLOCK(fltk_fl_browser_TOP)
{
    SIMPLE_API_RETNUMBER(Fl_Browser::TOP);
}

SIMPLE_BLOCK(fltk_fl_browser_BOTTOM)
{
    SIMPLE_API_RETNUMBER(Fl_Browser::BOTTOM);
}

SIMPLE_BLOCK(fltk_fl_browser_MIDDLE)
{
    SIMPLE_API_RETNUMBER(Fl_Browser::MIDDLE);
}

SIMPLE_BLOCK(fltk_fl_browser_lineposition)
{
    Fl_Browser* point1;
    int num2;
    Fl_Browser::Fl_Line_Position num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (Fl_Browser::Fl_Line_Position) (int) SIMPLE_API_GETNUMBER(3);
    point1->lineposition(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_browser_topline_1)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->topline(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_bottomline)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->bottomline(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_middleline)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->middleline(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_select)
{
    Fl_Browser* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->select(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_browser_selected)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->selected(num2));
}

SIMPLE_BLOCK(fltk_fl_browser_show)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->show(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_show_1)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show();
}

SIMPLE_BLOCK(fltk_fl_browser_hide)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->hide(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_hide_1)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->hide();
}

SIMPLE_BLOCK(fltk_fl_browser_visible)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->visible(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_value)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_value_1)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->value(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_text)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->text(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_text_1)
{
    Fl_Browser* point1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point1->text(num2,str3);
}

SIMPLE_BLOCK(fltk_fl_browser_data)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->data(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_data_1)
{
    Fl_Browser* point1;
    int num2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->data(num2,point3);
}

SIMPLE_BLOCK(fltk_fl_browser_Fl_Browser)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Browser(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_format_char)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->format_char(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_format_char_1)
{
    Fl_Browser* point1;
    char num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (char) (char) SIMPLE_API_GETNUMBER(2);
    point1->format_char(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_column_char)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->column_char(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_column_char_1)
{
    Fl_Browser* point1;
    char num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (char) (char) SIMPLE_API_GETNUMBER(2);
    point1->column_char(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_column_widths)
{
    Fl_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->column_widths(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_column_widths_1)
{
    Fl_Browser* point1;
    const int* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->column_widths(point2);
}

SIMPLE_BLOCK(fltk_fl_browser_displayed)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->displayed(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_make_visible)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->make_visible(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_icon)
{
    Fl_Browser* point1;
    int num2;
    Fl_Image* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (Fl_Image*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->icon(num2,point3);
}

SIMPLE_BLOCK(fltk_fl_browser_icon_1)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->icon(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser_remove_icon)
{
    Fl_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->remove_icon(num2);
}

SIMPLE_BLOCK(fltk_fl_browser_replace)
{
    Fl_Browser* point1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point1->replace(num2,str3);
}

SIMPLE_BLOCK(fltk_fl_browser_display)
{
    Fl_Browser* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->display(num2,num3);
}

/* Fl_Browser_ */
SIMPLE_BLOCK(fltk_fl_browser__handle)
{
    Fl_Browser_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_browser__resize)
{
    Fl_Browser_* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_browser__deselect)
{
    Fl_Browser_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->deselect(num2));
}

SIMPLE_BLOCK(fltk_fl_browser__position)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->position(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser__position_1)
{
    Fl_Browser_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->position(num2);
}

SIMPLE_BLOCK(fltk_fl_browser__hposition)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->hposition(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser__hposition_1)
{
    Fl_Browser_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->hposition(num2);
}

SIMPLE_BLOCK(fltk_fl_browser__display)
{
    Fl_Browser_* point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->display(point2);
}

SIMPLE_BLOCK(fltk_fl_browser__HORIZONTAL)
{
    SIMPLE_API_RETNUMBER(Fl_Browser_::HORIZONTAL);
}

SIMPLE_BLOCK(fltk_fl_browser__VERTICAL)
{
    SIMPLE_API_RETNUMBER(Fl_Browser_::VERTICAL);
}

SIMPLE_BLOCK(fltk_fl_browser__BOTH)
{
    SIMPLE_API_RETNUMBER(Fl_Browser_::BOTH);
}

SIMPLE_BLOCK(fltk_fl_browser__ALWAYS_ON)
{
    SIMPLE_API_RETNUMBER(Fl_Browser_::ALWAYS_ON);
}

SIMPLE_BLOCK(fltk_fl_browser__HORIZONTAL_ALWAYS)
{
    SIMPLE_API_RETNUMBER(Fl_Browser_::HORIZONTAL_ALWAYS);
}

SIMPLE_BLOCK(fltk_fl_browser__VERTICAL_ALWAYS)
{
    SIMPLE_API_RETNUMBER(Fl_Browser_::VERTICAL_ALWAYS);
}

SIMPLE_BLOCK(fltk_fl_browser__BOTH_ALWAYS)
{
    SIMPLE_API_RETNUMBER(Fl_Browser_::BOTH_ALWAYS);
}

SIMPLE_BLOCK(fltk_fl_browser__has_scrollbar)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->has_scrollbar(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser__has_scrollbar_1)
{
    Fl_Browser_* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->has_scrollbar(num2);
}

SIMPLE_BLOCK(fltk_fl_browser__textfont)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser__textfont_1)
{
    Fl_Browser_* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_browser__textsize)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser__textsize_1)
{
    Fl_Browser_* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_browser__textcolor)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser__textcolor_1)
{
    Fl_Browser_* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_browser__scrollbar_size)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->scrollbar_size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser__scrollbar_size_1)
{
    Fl_Browser_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->scrollbar_size(num2);
}

SIMPLE_BLOCK(fltk_fl_browser__scrollbar_width)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->scrollbar_width(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_browser__scrollbar_width_1)
{
    Fl_Browser_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->scrollbar_width(num2);
}

SIMPLE_BLOCK(fltk_fl_browser__scrollbar_right)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->scrollbar_right();
}

SIMPLE_BLOCK(fltk_fl_browser__scrollbar_left)
{
    Fl_Browser_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->scrollbar_left();
}

SIMPLE_BLOCK(fltk_fl_browser__sort)
{
    Fl_Browser_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Browser_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->sort(num2);
}

/* Fl_Button */

SIMPLE_BLOCK(fltk_fl_old_shortcut)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETCPOINTER(fl_old_shortcut(str1),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_button_handle)
{
    Fl_Button* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_button_Fl_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    Fl_Button *fl_button;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(5))->str;
    fl_button = new Fl_Button(num2, num3, num4, num5, str6) ;

    SIMPLE_API_RETCPOINTER(fl_button,"SMOOTHC_FLTK");
}

/*int Fl_Button::handle(int event) {
	printf("Yes event : %i \n",event);
	return 0;
} */

SIMPLE_BLOCK(fltk_fl_button_value)
{
    Fl_Button* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->value(num2));
}

SIMPLE_BLOCK(fltk_fl_button_value_1)
{
    Fl_Button* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->value());
}

SIMPLE_BLOCK(fltk_fl_button_set)
{
    Fl_Button* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->set());
}

SIMPLE_BLOCK(fltk_fl_button_clear)
{
    Fl_Button* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->clear());
}

SIMPLE_BLOCK(fltk_fl_button_setonly)
{
    Fl_Button* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->setonly();
}

SIMPLE_BLOCK(fltk_fl_button_shortcut)
{
    Fl_Button* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->shortcut());
}

SIMPLE_BLOCK(fltk_fl_button_shortcut_1)
{
    Fl_Button* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->shortcut(num2);
}

SIMPLE_BLOCK(fltk_fl_button_down_box)
{
    Fl_Button* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->down_box(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_button_down_box_1)
{
    Fl_Button* point1;
    Fl_Boxtype point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(2);
    point1->down_box(point2);
}

SIMPLE_BLOCK(fltk_fl_button_shortcut_2)
{
    Fl_Button* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->shortcut(str2);
}

SIMPLE_BLOCK(fltk_fl_button_down_color)
{
    Fl_Button* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->down_color(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_button_down_color_1)
{
    Fl_Button* point1;
    unsigned num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (unsigned) (int) SIMPLE_API_GETNUMBER(2);
    point1->down_color(num2);
}

/* Fl_Cairo */
#ifdef FLTK_HAVE_CAIRO
SIMPLE_BLOCK(fltk_fl_cairo_state_Fl_Cairo_State)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	SIMPLE_API_RETCPOINTER(new Fl_Cairo_State(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_cairo_state_cc)
{
	Fl_Cairo_State* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Cairo_State*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->cc(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_cairo_state_autolink)
{
	Fl_Cairo_State* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Cairo_State*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->autolink(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_cairo_state_cc_1)
{
	Fl_Cairo_State* point1;
	cairo_t* point2;
	bool num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Cairo_State*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (cairo_t*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	num3 = (bool) (int) SIMPLE_API_GETNUMBER(3);
	point1->cc(point2,num3);
}

SIMPLE_BLOCK(fltk_fl_cairo_state_autolink_1)
{
	Fl_Cairo_State* point1;
	bool num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Cairo_State*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (bool) (int) SIMPLE_API_GETNUMBER(2);
	point1->autolink(num2);
}

SIMPLE_BLOCK(fltk_fl_cairo_state_window)
{
	Fl_Cairo_State* point1;
	void* point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Cairo_State*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point1->window(point2);
}

SIMPLE_BLOCK(fltk_fl_cairo_state_window_1)
{
	Fl_Cairo_State* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Cairo_State*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->window(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_cairo_state_gc)
{
	Fl_Cairo_State* point1;
	void* point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Cairo_State*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point1->gc(point2);
}

SIMPLE_BLOCK(fltk_fl_cairo_state_gc_1)
{
	Fl_Cairo_State* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Cairo_State*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->gc(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_cairo_window_Fl_Cairo_Window)
{
	int num2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	SIMPLE_API_RETCPOINTER(new Fl_Cairo_Window(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_cairo_window_set_draw_cb)
{
	Fl_Cairo_Window* point1;
	cairo_draw_cb point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Cairo_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (cairo_draw_cb) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point1->set_draw_cb(point2);
}
#endif

/* Fl_Chart */
SIMPLE_BLOCK(fltk_fl_chart_Fl_Chart)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Chart(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_chart_clear)
{
    Fl_Chart* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_chart_add)
{
    Fl_Chart* point1;
    double num2;
    const char* str3;
    unsigned num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    num4 = (unsigned) (int) SIMPLE_API_GETNUMBER(4);
    point1->add(num2,str3,num4);
}

SIMPLE_BLOCK(fltk_fl_chart_insert)
{
    Fl_Chart* point1;
    int num2;
    double num3;
    const char* str4;
    unsigned num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    num5 = (unsigned) (int) SIMPLE_API_GETNUMBER(5);
    point1->insert(num2,num3,str4,num5);
}

SIMPLE_BLOCK(fltk_fl_chart_replace)
{
    Fl_Chart* point1;
    int num2;
    double num3;
    const char* str4;
    unsigned num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    num5 = (unsigned) (int) SIMPLE_API_GETNUMBER(5);
    point1->replace(num2,num3,str4,num5);
}

SIMPLE_BLOCK(fltk_fl_chart_bounds)
{
    Fl_Chart* point1;
    double * point2;
    double * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (double *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (double *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->bounds(point2,point3);
}

SIMPLE_BLOCK(fltk_fl_chart_bounds_1)
{
    Fl_Chart* point1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point1->bounds(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_chart_size)
{
    Fl_Chart* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_chart_size_1)
{
    Fl_Chart* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->size(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_chart_maxsize)
{
    Fl_Chart* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->maxsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_chart_maxsize_1)
{
    Fl_Chart* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->maxsize(num2);
}

SIMPLE_BLOCK(fltk_fl_chart_textfont)
{
    Fl_Chart* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_chart_textfont_1)
{
    Fl_Chart* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_chart_textsize)
{
    Fl_Chart* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_chart_textsize_1)
{
    Fl_Chart* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_chart_textcolor)
{
    Fl_Chart* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_chart_textcolor_1)
{
    Fl_Chart* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_chart_autosize)
{
    Fl_Chart* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->autosize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_chart_autosize_1)
{
    Fl_Chart* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Chart*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->autosize(num2);
}

/* Fl_Check_Browser */
SIMPLE_BLOCK(fltk_fl_check_browser_Fl_Check_Browser)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Check_Browser(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_check_browser_add_1)
{
    Fl_Check_Browser* point1;
    char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->add(str2));
}

SIMPLE_BLOCK(fltk_fl_check_browser_add_2)
{
    Fl_Check_Browser* point1;
    char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->add(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_check_browser_remove)
{
    Fl_Check_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->remove(num2));
}

SIMPLE_BLOCK(fltk_fl_check_browser_add_3)
{
    Fl_Check_Browser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->add(str2));
}

SIMPLE_BLOCK(fltk_fl_check_browser_add_4)
{
    Fl_Check_Browser* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->add(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_check_browser_clear_1)
{
    Fl_Check_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_check_browser_nitems)
{
    Fl_Check_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->nitems(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_check_browser_nchecked)
{
    Fl_Check_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->nchecked(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_check_browser_checked)
{
    Fl_Check_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->checked(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_check_browser_checked_1)
{
    Fl_Check_Browser* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->checked(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_check_browser_set_checked)
{
    Fl_Check_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->set_checked(num2);
}

SIMPLE_BLOCK(fltk_fl_check_browser_check_all)
{
    Fl_Check_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->check_all();
}

SIMPLE_BLOCK(fltk_fl_check_browser_check_none)
{
    Fl_Check_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->check_none();
}

SIMPLE_BLOCK(fltk_fl_check_browser_value)
{
    Fl_Check_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_check_browser_text)
{
    Fl_Check_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Check_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETSTRING(point1->text(num2));
}

/* Fl_Check_Button */
SIMPLE_BLOCK(fltk_fl_check_button_Fl_Check_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Check_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_choice_handle)
{
    Fl_Choice* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

/* Fl_Choice */
SIMPLE_BLOCK(fltk_fl_choice_Fl_Choice)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Choice(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_choice_value_1)
{
    Fl_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_choice_value_2)
{
    Fl_Choice* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->value(num2));
}

SIMPLE_BLOCK(fltk_fl_choice_value_3)
{
    Fl_Choice* point1;
    const Fl_Menu_Item* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Menu_Item*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->value(point2));
}

/* Fl_Clock_Output */
SIMPLE_BLOCK(fltk_fl_clock_output_Fl_Clock_Output)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Clock_Output(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_clock_output_value)
{
    Fl_Clock_Output* point1;
    ulong point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Clock_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (ulong) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->value(point2);
}

SIMPLE_BLOCK(fltk_fl_clock_output_value_1)
{
    Fl_Clock_Output* point1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Clock_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->value(num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_clock_output_value_2)
{
    Fl_Clock_Output* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Clock_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_clock_output_hour)
{
    Fl_Clock_Output* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Clock_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->hour(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_clock_output_minute)
{
    Fl_Clock_Output* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Clock_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->minute(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_clock_output_second)
{
    Fl_Clock_Output* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Clock_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->second(),"SMOOTHC_FLTK");
}

/* Fl_Clock */
SIMPLE_BLOCK(fltk_fl_clock_handle)
{
    Fl_Clock* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Clock*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_clock_Fl_Clock)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Clock(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_clock_Fl_Clock_1)
{
    uchar num2;
    int num3;
    int num4;
    int num5;
    int num6;
    const char* str7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    str7 = (const char*)  SIMPLE_API_GETSTRING(7);
    SIMPLE_API_RETCPOINTER(new Fl_Clock(num2,num3,num4,num5,num6,str7),"SMOOTHC_FLTK");
}

/* Flcc_HueBox */
SIMPLE_BLOCK(fltk_flcc_huebox_handle_1)
{
    Flcc_HueBox* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Flcc_HueBox*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_flcc_huebox_Flcc_HueBox)
{
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    SIMPLE_API_RETCPOINTER(new Flcc_HueBox(num2,num3,num4,num5),"SMOOTHC_FLTK");
}

/* Flcc_ValueBox */
SIMPLE_BLOCK(fltk_flcc_valuebox_handle_2)
{
    Flcc_ValueBox* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Flcc_ValueBox*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_flcc_valuebox_Flcc_ValueBox)
{
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    SIMPLE_API_RETCPOINTER(new Flcc_ValueBox(num2,num3,num4,num5),"SMOOTHC_FLTK");
}

/* Flcc_Value_Input */
SIMPLE_BLOCK(fltk_flcc_value_input_format)
{
    Flcc_Value_Input* point1;
    char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Flcc_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->format(str2));
}

SIMPLE_BLOCK(fltk_flcc_value_input_Flcc_Value_Input)
{
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    SIMPLE_API_RETCPOINTER(new Flcc_Value_Input(num2,num3,num4,num5),"SMOOTHC_FLTK");
}

/* Fl_Color_Chooser */
SIMPLE_BLOCK(fltk_fl_color_chooser_mode)
{
    Fl_Color_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->mode());
}

SIMPLE_BLOCK(fltk_fl_color_chooser_mode_1)
{
    Fl_Color_Chooser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->mode(num2);
}

SIMPLE_BLOCK(fltk_fl_color_chooser_hue)
{
    Fl_Color_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->hue());
}

SIMPLE_BLOCK(fltk_fl_color_chooser_saturation)
{
    Fl_Color_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->saturation());
}

SIMPLE_BLOCK(fltk_fl_color_chooser_value_3)
{
    Fl_Color_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->value());
}

SIMPLE_BLOCK(fltk_fl_color_chooser_r)
{
    Fl_Color_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->r());
}

SIMPLE_BLOCK(fltk_fl_color_chooser_g)
{
    Fl_Color_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->g());
}

SIMPLE_BLOCK(fltk_fl_color_chooser_b)
{
    Fl_Color_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->b());
}

SIMPLE_BLOCK(fltk_fl_color_chooser_hsv)
{
    Fl_Color_Chooser* point1;
    double num2;
    double num3;
    double num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    num4 = (double) (double) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETNUMBER(point1->hsv(num2,num3,num4));
}

SIMPLE_BLOCK(fltk_fl_color_chooser_rgb)
{
    Fl_Color_Chooser* point1;
    double num2;
    double num3;
    double num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Color_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    num4 = (double) (double) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETNUMBER(point1->rgb(num2,num3,num4));
}

SIMPLE_BLOCK(fltk_fl_color_chooser_Fl_Color_Chooser_hsv2rgb)
{
    double num1;
    double num2;
    double num3;
    double* point4;
    double* point5;
    double* point6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point4 = (double*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (double*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    point6 = (double*) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    Fl_Color_Chooser::hsv2rgb(num1,num2,num3,*point4,*point5,*point6);
}

SIMPLE_BLOCK(fltk_fl_color_chooser_Fl_Color_Chooser_rgb2hsv)
{
    double num1;
    double num2;
    double num3;
    double* point4;
    double* point5;
    double* point6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point4 = (double*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (double*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    point6 = (double*) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    Fl_Color_Chooser::rgb2hsv(num1,num2,num3,*point4,*point5,*point6);
}

SIMPLE_BLOCK(fltk_fl_color_chooser_Fl_Color_Chooser)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Color_Chooser(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_color_chooser_fl_color_chooser)
{
    const char* str2;
    double* point3;
    double* point4;
    double* point5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point3 = (double*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (double*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (double*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    SIMPLE_API_RETNUMBER(fl_color_chooser(str2,*point3,*point4,*point5,num6));
}

SIMPLE_BLOCK(fltk_fl_color_chooser_fl_color_chooser_1)
{
    const char* str2;
    uchar* point3;
    uchar* point4;
    uchar* point5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point3 = (uchar*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (uchar*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (uchar*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    SIMPLE_API_RETNUMBER(fl_color_chooser(str2,*point3,*point4,*point5,num6));
}

/* Fl_Copy_Surface */
#ifdef Fl_Copy_Surface::class_id
/*SIMPLE_BLOCK(fltk_fl_copy_surface_Fl_Copy_Surface_class_id)
{
	SIMPLE_API_RETSTRING(Fl_Copy_Surface::class_id);
}

SIMPLE_BLOCK(fltk_fl_copy_surface_class_name)
{
	Fl_Copy_Surface* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Copy_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETSTRING(point1->class_name());
} */
#endif

SIMPLE_BLOCK(fltk_fl_copy_surface_Fl_Copy_Surface)
{
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(new Fl_Copy_Surface(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_copy_surface_set_current)
{
    Fl_Copy_Surface* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Copy_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_current();
}

SIMPLE_BLOCK(fltk_fl_copy_surface_draw)
{
    Fl_Copy_Surface* point1;
    Fl_Widget* point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Copy_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->draw(point2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_copy_surface_draw_decorated_window)
{
    Fl_Copy_Surface* point1;
    Fl_Window* point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Copy_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Window*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->draw_decorated_window(point2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_copy_surface_w)
{
    Fl_Copy_Surface* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Copy_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->w());
}

SIMPLE_BLOCK(fltk_fl_copy_surface_h)
{
    Fl_Copy_Surface* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Copy_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->h());
}

/* Fl_Quartz_Surface_ */
#if defined(__APPLE__)
/*SIMPLE_BLOCK(fltk_fl_quartz_surface__class_name_1)
{
	Fl_Quartz_Surface_* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Quartz_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETSTRING(point1->class_name());
} */

SIMPLE_BLOCK(fltk_fl_quartz_surface__Fl_Quartz_Surface_)
{
	int num2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	SIMPLE_API_RETCPOINTER(new Fl_Quartz_Surface_(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_quartz_surface__printable_rect)
{
	Fl_Quartz_Surface_* point1;
	int * point2;
	int * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Quartz_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->printable_rect(point2,point3));
}

/* Fl_GDI_Surface_ */
#elif defined(WIN32)
/*SIMPLE_BLOCK(fltk_fl_gdi_surface__class_name_2)
{
	Fl_GDI_Surface_* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_GDI_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETSTRING(point1->class_name());
}*/

SIMPLE_BLOCK(fltk_fl_gdi_surface__Fl_GDI_Surface_)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	SIMPLE_API_RETCPOINTER(new Fl_GDI_Surface_(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_gdi_surface__translate)
{
	Fl_GDI_Surface_* point1;
	int num2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_GDI_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	point1->translate(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_gdi_surface__untranslate)
{
	Fl_GDI_Surface_* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_GDI_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->untranslate();
}

#elif !defined(FL_DOXYGEN) and !defined(__ANDROID__)
/* SIMPLE_BLOCK(fltk_fl_xlib_surface__class_name_3)
{
	Fl_Xlib_Surface_* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Xlib_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETSTRING(point1->class_name());
} */

SIMPLE_BLOCK(fltk_fl_xlib_surface__Fl_Xlib_Surface_)
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(new Fl_Xlib_Surface_(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_xlib_surface__translate_1)
{
    Fl_Xlib_Surface_* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Xlib_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->translate(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_xlib_surface__untranslate_1)
{
    Fl_Xlib_Surface_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Xlib_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->untranslate();
}
#endif

/* Fl_Counter */
SIMPLE_BLOCK(fltk_fl_counter_handle_3)
{
    Fl_Counter* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_counter_Fl_Counter)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Counter(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_counter_lstep)
{
    Fl_Counter* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->lstep(num2);
}

SIMPLE_BLOCK(fltk_fl_counter_step)
{
    Fl_Counter* point1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point1->step(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_counter_step_1)
{
    Fl_Counter* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->step(num2);
}

SIMPLE_BLOCK(fltk_fl_counter_step_2)
{
    Fl_Counter* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->step());
}

SIMPLE_BLOCK(fltk_fl_counter_textfont)
{
    Fl_Counter* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_counter_textfont_1)
{
    Fl_Counter* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_counter_textsize)
{
    Fl_Counter* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_counter_textsize_1)
{
    Fl_Counter* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_counter_textcolor)
{
    Fl_Counter* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_counter_textcolor_1)
{
    Fl_Counter* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Counter*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

#ifdef WIN32
#elif defined(__APPLE__)
SIMPLE_BLOCK(fltk_fl_quartz_line_width_)
{
	SIMPLE_API_RETNUMBER(fl_quartz_line_width_);
}
#endif

/* Fl_Device */
#ifndef __ANDROID__
/*SIMPLE_BLOCK(fltk_fl_device_Fl_Device_class_id)
{
	SIMPLE_API_RETSTRING(Fl_Device::class_id);
} */

/*SIMPLE_BLOCK(fltk_fl_device_class_name)
{
	Fl_Device* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETSTRING(point1->class_name());
} */
#endif

/* Fl_Dial */
SIMPLE_BLOCK(fltk_fl_dial_handle)
{
    Fl_Dial* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Dial*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_dial_Fl_Dial)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Dial(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_dial_angle1)
{
    Fl_Dial* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Dial*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->angle1(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_dial_angle1_1)
{
    Fl_Dial* point1;
    short point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Dial*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (short) (int) SIMPLE_API_GETNUMBER(2);
    point1->angle1(point2);
}

SIMPLE_BLOCK(fltk_fl_dial_angle2)
{
    Fl_Dial* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Dial*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->angle2(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_dial_angle2_1)
{
    Fl_Dial* point1;
    short point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Dial*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (short) (int) SIMPLE_API_GETNUMBER(2);
    point1->angle2(point2);
}

SIMPLE_BLOCK(fltk_fl_dial_angles)
{
    Fl_Dial* point1;
    short point2;
    short point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Dial*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (short) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (short) (int) SIMPLE_API_GETNUMBER(3);
    point1->angles(point2,point3);
}

/* Fl_Double_Window */
SIMPLE_BLOCK(fltk_fl_double_window_show)
{
    Fl_Double_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Double_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show();
}

SIMPLE_BLOCK(fltk_fl_double_window_show_1)
{
    Fl_Double_Window* point1;
    int num2;
    char* * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Double_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (char* *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->show(num2,point3);
}

SIMPLE_BLOCK(fltk_fl_double_window_flush)
{
    Fl_Double_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Double_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->flush();
}

SIMPLE_BLOCK(fltk_fl_double_window_resize)
{
    Fl_Double_Window* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Double_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_double_window_hide)
{
    Fl_Double_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Double_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->hide();
}

SIMPLE_BLOCK(fltk_fl_double_window_Fl_Double_Window)
{
    int num2;
    int num3;
    const char* str4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    SIMPLE_API_RETCPOINTER(new Fl_Double_Window(num2,num3,str4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_double_window_Fl_Double_Window_1)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Double_Window(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* fl_draw */
SIMPLE_BLOCK(fltk_fl_draw_shortcut)
{
    SIMPLE_API_RETNUMBER(fl_draw_shortcut);
}

SIMPLE_BLOCK(fltk_fl_color)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    fl_color(num1);
}

SIMPLE_BLOCK(fltk_fl_color_1)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    fl_color(num1);
}

SIMPLE_BLOCK(fltk_fl_color_2)
{
    uchar num1;
    uchar num2;
    uchar num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (uchar) SIMPLE_API_GETNUMBER(1);
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    num3 = (uchar) SIMPLE_API_GETNUMBER(3);
    fl_color(num1,num2,num3);
}

SIMPLE_BLOCK(fltk_fl_color_3)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_color());
}

SIMPLE_BLOCK(fltk_fl_push_clip)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_push_clip(num1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_push_no_clip)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_push_no_clip();
}

SIMPLE_BLOCK(fltk_fl_pop_clip)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_pop_clip();
}

SIMPLE_BLOCK(fltk_fl_not_clipped)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETNUMBER(fl_not_clipped(num1,num2,num3,num4));
}

SIMPLE_BLOCK(fltk_fl_clip_box)
{
    int point1;
    int num2;
    int num3;
    int num4;
    int* point5;
    int* point6;
    int* point7;
    int* point8;
    if ( SIMPLE_API_PARACOUNT != 8 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
        return ;
    }
    point1 = (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point5 = (int*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    point6 = (int*) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    point7 = (int*) SIMPLE_API_GETCPOINTER(7,"SMOOTHC_FLTK");
    point8 = (int*) SIMPLE_API_GETCPOINTER(8,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(fl_clip_box(point1,num2,num3,num4,*point5,*point6,*point7,*point8));
}

SIMPLE_BLOCK(fltk_fl_restore_clip)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_restore_clip();
}

SIMPLE_BLOCK(fltk_fl_clip_region)
{
    Fl_Region point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Region) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    fl_clip_region(point1);
}

SIMPLE_BLOCK(fltk_fl_clip_region_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(fl_clip_region(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_point)
{
    int num1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    fl_point(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_line_style)
{
    int num1;
    int num2;
    char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (char*)  SIMPLE_API_GETSTRING(3);
    fl_line_style(num1,num2,str3);
}

SIMPLE_BLOCK(fltk_FL_SOLID)
{
    SIMPLE_API_RETNUMBER(FL_SOLID);
}

SIMPLE_BLOCK(fltk_FL_DASH)
{
    SIMPLE_API_RETNUMBER(FL_DASH);
}

SIMPLE_BLOCK(fltk_FL_DOT)
{
    SIMPLE_API_RETNUMBER(FL_DOT);
}

SIMPLE_BLOCK(fltk_FL_DASHDOT)
{
    SIMPLE_API_RETNUMBER(FL_DASHDOT);
}

SIMPLE_BLOCK(fltk_FL_DASHDOTDOT)
{
    SIMPLE_API_RETNUMBER(FL_DASHDOTDOT);
}

SIMPLE_BLOCK(fltk_FL_CAP_FLAT)
{
    SIMPLE_API_RETNUMBER(FL_CAP_FLAT);
}

SIMPLE_BLOCK(fltk_FL_CAP_ROUND)
{
    SIMPLE_API_RETNUMBER(FL_CAP_ROUND);
}

SIMPLE_BLOCK(fltk_FL_CAP_SQUARE)
{
    SIMPLE_API_RETNUMBER(FL_CAP_SQUARE);
}

SIMPLE_BLOCK(fltk_FL_JOIN_MITER)
{
    SIMPLE_API_RETNUMBER(FL_JOIN_MITER);
}

SIMPLE_BLOCK(fltk_FL_JOIN_ROUND)
{
    SIMPLE_API_RETNUMBER(FL_JOIN_ROUND);
}

SIMPLE_BLOCK(fltk_FL_JOIN_BEVEL)
{
    SIMPLE_API_RETNUMBER(FL_JOIN_BEVEL);
}

SIMPLE_BLOCK(fltk_fl_rect)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_rect(num1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_rect_1)
{
    int num1;
    int num2;
    int num3;
    int num4;
    Fl_Color num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(5);
    fl_rect(num1,num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_rectf)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_rectf(num1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_rectf_1)
{
    int num1;
    int num2;
    int num3;
    int num4;
    Fl_Color num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(5);
    fl_rectf(num1,num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_rectf_2)
{
    int num1;
    int num2;
    int num3;
    int num4;
    uchar num5;
    uchar num6;
    uchar num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (uchar) SIMPLE_API_GETNUMBER(5);
    num6 = (uchar) SIMPLE_API_GETNUMBER(6);
    num7 = (uchar) SIMPLE_API_GETNUMBER(7);
    fl_rectf(num1,num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_line)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_line(num1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_line_1)
{
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    fl_line(num1,num2,num3,num4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_loop)
{
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    fl_loop(num1,num2,num3,num4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_loop_1)
{
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    int num8;
    if ( SIMPLE_API_PARACOUNT != 8 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    num8 = (int) (int) SIMPLE_API_GETNUMBER(8);
    fl_loop(num1,num2,num3,num4,num5,num6,num7,num8);
}

SIMPLE_BLOCK(fltk_fl_polygon)
{
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    fl_polygon(num1,num2,num3,num4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_polygon_1)
{
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    int num8;
    if ( SIMPLE_API_PARACOUNT != 8 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    num8 = (int) (int) SIMPLE_API_GETNUMBER(8);
    fl_polygon(num1,num2,num3,num4,num5,num6,num7,num8);
}

SIMPLE_BLOCK(fltk_fl_xyline)
{
    int num1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    fl_xyline(num1,num2,num3);
}

SIMPLE_BLOCK(fltk_fl_xyline_1)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_xyline(num1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_xyline_2)
{
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    fl_xyline(num1,num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_yxline)
{
    int num1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    fl_yxline(num1,num2,num3);
}

SIMPLE_BLOCK(fltk_fl_yxline_1)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_yxline(num1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_yxline_2)
{
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    fl_yxline(num1,num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_arc)
{
    int num1;
    int num2;
    int num3;
    int num4;
    double num5;
    double num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (double) (double) SIMPLE_API_GETNUMBER(5);
    num6 = (double) (double) SIMPLE_API_GETNUMBER(6);
    fl_arc(num1,num2,num3,num4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_pie)
{
    int num1;
    int num2;
    int num3;
    int num4;
    double num5;
    double num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (double) (double) SIMPLE_API_GETNUMBER(5);
    num6 = (double) (double) SIMPLE_API_GETNUMBER(6);
    fl_pie(num1,num2,num3,num4,num5,num6);
}

#ifdef fl_chord
SIMPLE_BLOCK(fltk_fl_chord)
{
	int num1;
	int num2;
	int num3;
	int num4;
	double num5;
	double num6;
	if ( SIMPLE_API_PARACOUNT != 6 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
	num5 = (double) (double) SIMPLE_API_GETNUMBER(5);
	num6 = (double) (double) SIMPLE_API_GETNUMBER(6);
	fl_chord(num1,num2,num3,num4,num5,num6);
}
#endif

SIMPLE_BLOCK(fltk_fl_push_matrix)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_push_matrix();
}

SIMPLE_BLOCK(fltk_fl_pop_matrix)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_pop_matrix();
}

SIMPLE_BLOCK(fltk_fl_scale)
{
    double num1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    fl_scale(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_scale_1)
{
    double num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    fl_scale(num1);
}

SIMPLE_BLOCK(fltk_fl_translate)
{
    double num1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    fl_translate(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_rotate)
{
    double num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    fl_rotate(num1);
}

SIMPLE_BLOCK(fltk_fl_mult_matrix)
{
    double num1;
    double num2;
    double num3;
    double num4;
    double num5;
    double num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    num4 = (double) (double) SIMPLE_API_GETNUMBER(4);
    num5 = (double) (double) SIMPLE_API_GETNUMBER(5);
    num6 = (double) (double) SIMPLE_API_GETNUMBER(6);
    fl_mult_matrix(num1,num2,num3,num4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_begin_points)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_begin_points();
}

SIMPLE_BLOCK(fltk_fl_begin_line)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_begin_line();
}

SIMPLE_BLOCK(fltk_fl_begin_loop)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_begin_loop();
}

SIMPLE_BLOCK(fltk_fl_begin_polygon)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_begin_polygon();
}

SIMPLE_BLOCK(fltk_fl_vertex)
{
    double num1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    fl_vertex(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_curve)
{
    double num1;
    double num2;
    double num3;
    double num4;
    double num5;
    double num6;
    double num7;
    double num8;
    if ( SIMPLE_API_PARACOUNT != 8 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    num4 = (double) (double) SIMPLE_API_GETNUMBER(4);
    num5 = (double) (double) SIMPLE_API_GETNUMBER(5);
    num6 = (double) (double) SIMPLE_API_GETNUMBER(6);
    num7 = (double) (double) SIMPLE_API_GETNUMBER(7);
    num8 = (double) (double) SIMPLE_API_GETNUMBER(8);
    fl_curve(num1,num2,num3,num4,num5,num6,num7,num8);
}

SIMPLE_BLOCK(fltk_fl_arc_1)
{
    double num1;
    double num2;
    double num3;
    double num4;
    double num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    num4 = (double) (double) SIMPLE_API_GETNUMBER(4);
    num5 = (double) (double) SIMPLE_API_GETNUMBER(5);
    fl_arc(num1,num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_circle)
{
    double num1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    fl_circle(num1,num2,num3);
}

SIMPLE_BLOCK(fltk_fl_end_points)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_end_points();
}

SIMPLE_BLOCK(fltk_fl_end_line)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_end_line();
}

SIMPLE_BLOCK(fltk_fl_end_loop)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_end_loop();
}

SIMPLE_BLOCK(fltk_fl_end_polygon)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_end_polygon();
}

SIMPLE_BLOCK(fltk_fl_begin_complex_polygon)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_begin_complex_polygon();
}

SIMPLE_BLOCK(fltk_fl_gap)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_gap();
}

SIMPLE_BLOCK(fltk_fl_end_complex_polygon)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_end_complex_polygon();
}

SIMPLE_BLOCK(fltk_fl_transform_x)
{
    double num1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(fl_transform_x(num1,num2));
}

SIMPLE_BLOCK(fltk_fl_transform_y)
{
    double num1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(fl_transform_y(num1,num2));
}

SIMPLE_BLOCK(fltk_fl_transform_dx)
{
    double num1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(fl_transform_dx(num1,num2));
}

SIMPLE_BLOCK(fltk_fl_transform_dy)
{
    double num1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(fl_transform_dy(num1,num2));
}

SIMPLE_BLOCK(fltk_fl_transformed_vertex)
{
    double num1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    fl_transformed_vertex(num1,num2);
}

SIMPLE_BLOCK(fltk_fl_font)
{
    Fl_Font point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    fl_font(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_font_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(fl_font(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_size)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(fl_size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_height)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_height());
}

SIMPLE_BLOCK(fltk_fl_height_1)
{
    int num1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(fl_height(num1,num2));
}

SIMPLE_BLOCK(fltk_fl_descent)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_descent());
}

SIMPLE_BLOCK(fltk_fl_width)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETNUMBER(fl_width(str1));
}

SIMPLE_BLOCK(fltk_fl_width_1)
{
    const char* str1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(fl_width(str1,num2));
}

SIMPLE_BLOCK(fltk_fl_width_2)
{
    unsigned int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (unsigned int) (unsigned int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_width(num1));
}

SIMPLE_BLOCK(fltk_fl_text_extents)
{
    const char* str1;
    int* point2;
    int* point3;
    int* point4;
    int* point5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (int*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    fl_text_extents(str1,*point2,*point3,*point4,*point5);
}

SIMPLE_BLOCK(fltk_fl_text_extents_1)
{
    const char* str1;
    int num2;
    int* point3;
    int* point4;
    int* point5;
    int* point6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (int*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    point6 = (int*) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    fl_text_extents(str1,num2,*point3,*point4,*point5,*point6);
}

#ifdef fl_latin1_to_local
SIMPLE_BLOCK(fltk_fl_latin1_to_local)
{
	const char* str1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char*)  SIMPLE_API_GETSTRING(1);
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETSTRING(fl_latin1_to_local(str1,num2));
}
#endif

#ifdef fl_local_to_latin1
SIMPLE_BLOCK(fltk_fl_local_to_latin1)
{
	const char* str1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char*)  SIMPLE_API_GETSTRING(1);
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETSTRING(fl_local_to_latin1(str1,num2));
}
#endif

#ifdef fltk_fl_mac_roman_to_local
SIMPLE_BLOCK(fltk_fl_mac_roman_to_local)
{
	const char* str1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char*)  SIMPLE_API_GETSTRING(1);
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETSTRING(fl_mac_roman_to_local(str1,num2));
}
#endif

#ifdef fltk_fl_local_to_mac_roman
SIMPLE_BLOCK(fltk_fl_local_to_mac_roman)
{
	const char* str1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str1 = (const char*)  SIMPLE_API_GETSTRING(1);
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETSTRING(fl_local_to_mac_roman(str1,num2));
}
#endif

SIMPLE_BLOCK(fltk_fl_draw)
{
    const char* str1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    fl_draw(str1,num2,num3);
}

SIMPLE_BLOCK(fltk_fl_draw_1)
{
    int num1;
    const char* str2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_draw(num1,str2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_draw_2)
{
    const char* str1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_draw(str1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_draw_3)
{
    int num1;
    const char* str2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    fl_draw(num1,str2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_rtl_draw)
{
    const char* str1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_rtl_draw(str1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_measure)
{
    const char* str1;
    int* point2;
    int* point3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_measure(str1,*point2,*point3,num4);
}

SIMPLE_BLOCK(fltk_fl_draw_4)
{
    const char* str1;
    int num2;
    int num3;
    int num4;
    int num5;
    Fl_Align point6;
    Fl_Image* point7;
    int num8;
    if ( SIMPLE_API_PARACOUNT != 8 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point6 = (Fl_Align) (int) SIMPLE_API_GETNUMBER(6);
    point7 = (Fl_Image*) SIMPLE_API_GETCPOINTER(7,"SMOOTHC_FLTK");
    num8 = (int) (int) SIMPLE_API_GETNUMBER(8);
    fl_draw(str1,num2,num3,num4,num5,point6,point7,num8);
}

SIMPLE_BLOCK(fltk_fl_frame1)
{
    const char* str1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    fl_frame(str1,num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_frame2)
{
    const char* str1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    fl_frame2(str1,num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_draw_box)
{
    Fl_Boxtype point1;
    int num2;
    int num3;
    int num4;
    int num5;
    Fl_Color num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(6);
    fl_draw_box(point1,num2,num3,num4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_draw_image)
{
    const uchar* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (const uchar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    fl_draw_image(point1,num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_draw_image_mono)
{
    const uchar* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (const uchar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    fl_draw_image_mono(point1,num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_draw_image_1)
{
    Fl_Draw_Image_Cb point1;
    void* point2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Draw_Image_Cb) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    fl_draw_image(point1,point2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_draw_image_mono_1)
{
    Fl_Draw_Image_Cb point1;
    void* point2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Draw_Image_Cb) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    fl_draw_image_mono(point1,point2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_can_do_alpha_blending)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(fl_can_do_alpha_blending());
}

SIMPLE_BLOCK(fltk_fl_measure_pixmap_1)
{
    const char* * point1;
    int * point2;
    int * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (const char* *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(fl_measure_pixmap(point1,*point2,*point3));
}

SIMPLE_BLOCK(fltk_fl_shortcut_label)
{
    unsigned int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (unsigned int) (unsigned int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETSTRING(fl_shortcut_label(num1));
}

SIMPLE_BLOCK(fltk_fl_shortcut_label_1)
{
    unsigned int num1;
    const char* * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (unsigned int) (unsigned int) SIMPLE_API_GETNUMBER(1);
    point2 = (const char* *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(fl_shortcut_label(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_old_shortcut_draw)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETNUMBER(fl_old_shortcut(str1));
}

SIMPLE_BLOCK(fltk_fl_overlay_rect)
{
    int num1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    fl_overlay_rect(num1,num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_overlay_clear)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_overlay_clear();
}

SIMPLE_BLOCK(fltk_fl_cursor)
{
    Fl_Cursor point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = Fl_Cursor ((int) SIMPLE_API_GETNUMBER(1));
    fl_cursor(point1);
}

SIMPLE_BLOCK(fltk_fl_cursor_1)
{
    Fl_Cursor point1;
    Fl_Color num2;
    Fl_Color num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Cursor) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(3);
    fl_cursor(point1,num2,num3);
}

SIMPLE_BLOCK(fltk_fl_expand_text)
{
    const char* str1;
    char* str2;
    int num3;
    double num4;
    int* point5;
    double * point6;
    int num7;
    int num8;
    if ( SIMPLE_API_PARACOUNT != 8 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (double) (double) SIMPLE_API_GETNUMBER(4);
    point5 = (int*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    point6 = (double *) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    num8 = (int) (int) SIMPLE_API_GETNUMBER(8);
    SIMPLE_API_RETSTRING(fl_expand_text(str1,str2,num3,num4,*point5,*point6,num7,num8));
}

#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_set_status)
{
	int num1;
	int num2;
	int num3;
	int num4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
	fl_set_status(num1,num2,num3,num4);
}
#endif

SIMPLE_BLOCK(fltk_fl_set_spot)
{
    int num1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    Fl_Window * point7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    point7 = (Fl_Window *) SIMPLE_API_GETCPOINTER(7,"SMOOTHC_FLTK");
    fl_set_spot(num1,num2,num3,num4,num5,num6,point7);
}

SIMPLE_BLOCK(fltk_fl_reset_spot)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_reset_spot();
}

SIMPLE_BLOCK(fltk_fl_draw_symbol)
{
    const char* str1;
    int num2;
    int num3;
    int num4;
    int num5;
    Fl_Color num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(6);
    SIMPLE_API_RETNUMBER(fl_draw_symbol(str1,num2,num3,num4,num5,num6));
}

/* Fl_File_Browser */
SIMPLE_BLOCK(fltk_fl_file_browser_DIRECTORIES)
{
    SIMPLE_API_RETNUMBER(Fl_File_Browser::DIRECTORIES);
}

SIMPLE_BLOCK(fltk_fl_file_browser_Fl_File_Browser)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_File_Browser(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_browser_iconsize)
{
    Fl_File_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->iconsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_browser_iconsize_1)
{
    Fl_File_Browser* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->iconsize(num2);
}

SIMPLE_BLOCK(fltk_fl_file_browser_filter)
{
    Fl_File_Browser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->filter(str2);
}

SIMPLE_BLOCK(fltk_fl_file_browser_filter_1)
{
    Fl_File_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->filter(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_browser_load)
{
    Fl_File_Browser* point1;
    const char* str2;
    Fl_File_Sort_F * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_File_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point3 = (Fl_File_Sort_F *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->load(str2,point3));
}

SIMPLE_BLOCK(fltk_fl_file_browser_textsize)
{
    Fl_File_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_browser_textsize_1)
{
    Fl_File_Browser* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_file_browser_filetype)
{
    Fl_File_Browser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->filetype(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_browser_filetype_1)
{
    Fl_File_Browser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Browser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->filetype(num2);
}

/* Fl_File_Chooser */
SIMPLE_BLOCK(fltk_fl_file_chooser_SINGLE)
{
    SIMPLE_API_RETNUMBER(Fl_File_Chooser::SINGLE);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_MULTI)
{
    SIMPLE_API_RETNUMBER(Fl_File_Chooser::MULTI);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_CREATE)
{
    SIMPLE_API_RETNUMBER(Fl_File_Chooser::CREATE);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_DIRECTORY)
{
    SIMPLE_API_RETNUMBER(Fl_File_Chooser::DIRECTORY);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser)
{
    const char* str2;
    const char* str3;
    int num4;
    const char* str5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str5 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_File_Chooser(str2,str3,num4,str5),"SMOOTHC_FLTK");
}

/*
SIMPLE_BLOCK(fltk_fl_file_chooser_callback)
{
	Fl_File_Chooser* point1;
	void* point2;
	void* point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	point1->callback(point2,point3);
}
*/

SIMPLE_BLOCK(fltk_fl_file_chooser_color)
{
    Fl_File_Chooser* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->color(num2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_color_1)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->color());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_count)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->count());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_directory)
{
    Fl_File_Chooser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->directory(str2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_directory_1)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->directory());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_filter_2)
{
    Fl_File_Chooser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->filter(str2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_filter_3)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->filter());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_filter_value)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->filter_value());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_filter_value_1)
{
    Fl_File_Chooser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->filter_value(num2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_hide)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->hide();
}

SIMPLE_BLOCK(fltk_fl_file_chooser_iconsize_2)
{
    Fl_File_Chooser* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->iconsize(num2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_iconsize_3)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->iconsize());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_label)
{
    Fl_File_Chooser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->label(str2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_label_1)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->label());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_ok_label)
{
    Fl_File_Chooser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->ok_label(str2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_ok_label_1)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->ok_label());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_preview)
{
    Fl_File_Chooser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->preview(num2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_preview_1)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->preview(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_chooser_rescan)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->rescan();
}

SIMPLE_BLOCK(fltk_fl_file_chooser_rescan_keep_filename)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->rescan_keep_filename();
}

SIMPLE_BLOCK(fltk_fl_file_chooser_show)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show();
}

SIMPLE_BLOCK(fltk_fl_file_chooser_shown)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->shown());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_textcolor)
{
    Fl_File_Chooser* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_textcolor_1)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->textcolor());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_textfont)
{
    Fl_File_Chooser* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_textfont_1)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_chooser_textsize_2)
{
    Fl_File_Chooser* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_textsize_3)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_chooser_type)
{
    Fl_File_Chooser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->type(num2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_type_1)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->type());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_user_data)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->user_data();
}

SIMPLE_BLOCK(fltk_fl_file_chooser_user_data_1)
{
    Fl_File_Chooser* point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->user_data(point2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_value)
{
    Fl_File_Chooser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETSTRING(point1->value(num2));
}

SIMPLE_BLOCK(fltk_fl_file_chooser_value_1)
{
    Fl_File_Chooser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->value(str2);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_visible)
{
    Fl_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->visible());
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_add_favorites_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::add_favorites_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_all_files_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::all_files_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_custom_filter_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::custom_filter_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_existing_file_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::existing_file_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_favorites_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::favorites_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_filename_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::filename_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_filesystems_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::filesystems_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_manage_favorites_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::manage_favorites_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_new_directory_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::new_directory_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_new_directory_tooltip)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::new_directory_tooltip);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_preview_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::preview_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_save_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::save_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_show_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::show_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_Fl_File_Chooser_hidden_label)
{
    SIMPLE_API_RETSTRING(Fl_File_Chooser::hidden_label);
}

SIMPLE_BLOCK(fltk_fl_file_chooser_add_extra)
{
    Fl_File_Chooser* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->add_extra(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_chooser_fl_file_chooser_ok_label)
{
    const char* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point2 = (const char*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    fl_file_chooser_ok_label(point2);
}

/* Fl_File_Icon */
SIMPLE_BLOCK(fltk_fl_file_icon_ANY)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::ANY);
}

SIMPLE_BLOCK(fltk_fl_file_icon_PLAIN)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::PLAIN);
}

SIMPLE_BLOCK(fltk_fl_file_icon_FIFO)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::FIFO);
}

SIMPLE_BLOCK(fltk_fl_file_icon_DEVICE)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::DEVICE);
}

SIMPLE_BLOCK(fltk_fl_file_icon_LINK)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::LINK);
}

SIMPLE_BLOCK(fltk_fl_file_icon_END)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::END);
}

SIMPLE_BLOCK(fltk_fl_file_icon_COLOR)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::COLOR);
}

SIMPLE_BLOCK(fltk_fl_file_icon_LINE)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::LINE);
}

SIMPLE_BLOCK(fltk_fl_file_icon_CLOSEDLINE)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::CLOSEDLINE);
}

SIMPLE_BLOCK(fltk_fl_file_icon_POLYGON)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::POLYGON);
}

SIMPLE_BLOCK(fltk_fl_file_icon_OUTLINEPOLYGON)
{
    SIMPLE_API_RETNUMBER(Fl_File_Icon::OUTLINEPOLYGON);
}

SIMPLE_BLOCK(fltk_fl_file_icon_Fl_File_Icon)
{
    const char* str2;
    int num3;
    int num4;
    short * point5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point5 = (short *) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(new Fl_File_Icon(str2,num3,num4,point5),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_icon_add)
{
    Fl_File_Icon* point1;
    short point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (short) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->add(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_icon_add_color)
{
    Fl_File_Icon* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->add_color(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_icon_add_vertex)
{
    Fl_File_Icon* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->add_vertex(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_icon_add_vertex_1)
{
    Fl_File_Icon* point1;
    float num2;
    float num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (float) (float) SIMPLE_API_GETNUMBER(2);
    num3 = (float) (float) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->add_vertex(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_icon_clear)
{
    Fl_File_Icon* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_file_icon_draw)
{
    Fl_File_Icon* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    Fl_Color num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    point1->draw(num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_file_icon_label)
{
    Fl_File_Icon* point1;
    Fl_Widget * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->label(point2);
}

SIMPLE_BLOCK(fltk_fl_file_icon_Fl_File_Icon_labeltype)
{
    const Fl_Label * point1;
    int num2;
    int num3;
    int num4;
    int num5;
    Fl_Align point6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (const Fl_Label *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point6 = (Fl_Align) (int) SIMPLE_API_GETNUMBER(6);
    Fl_File_Icon::labeltype(point1,num2,num3,num4,num5,point6);
}

#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_file_icon_load)
{
	Fl_File_Icon* point1;
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	str2 = (const char*)  SIMPLE_API_GETSTRING(2);
	point1->load(str2);
}

SIMPLE_BLOCK(fltk_fl_file_icon_load_fti)
{
	Fl_File_Icon* point1;
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	str2 = (const char*)  SIMPLE_API_GETSTRING(2);
	SIMPLE_API_RETNUMBER(point1->load_fti(str2));
}

SIMPLE_BLOCK(fltk_fl_file_icon_load_image)
{
	Fl_File_Icon* point1;
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	str2 = (const char*)  SIMPLE_API_GETSTRING(2);
	SIMPLE_API_RETNUMBER(point1->load_image(str2));
}
#endif

SIMPLE_BLOCK(fltk_fl_file_icon_next)
{
    Fl_File_Icon* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->next(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_icon_pattern)
{
    Fl_File_Icon* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->pattern());
}

SIMPLE_BLOCK(fltk_fl_file_icon_size)
{
    Fl_File_Icon* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->size());
}

SIMPLE_BLOCK(fltk_fl_file_icon_type)
{
    Fl_File_Icon* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->type());
}

SIMPLE_BLOCK(fltk_fl_file_icon_value)
{
    Fl_File_Icon* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Icon*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_icon_Fl_File_Icon_find)
{
    const char* str1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(Fl_File_Icon::find(str1,num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_icon_Fl_File_Icon_first)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl_File_Icon::first(),"SMOOTHC_FLTK");
}

#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_file_icon_Fl_File_Icon_load_system_icons)
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	Fl_File_Icon::load_system_icons();
}
#endif

/* Fl_File_Input */
SIMPLE_BLOCK(fltk_fl_file_input_Fl_File_Input)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_File_Input(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_file_input_handle)
{
    Fl_File_Input* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_file_input_down_box)
{
    Fl_File_Input* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->down_box());
}

SIMPLE_BLOCK(fltk_fl_file_input_down_box_1)
{
    Fl_File_Input* point1;
    Fl_Boxtype point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(2);
    point1->down_box(point2);
}

SIMPLE_BLOCK(fltk_fl_file_input_errorcolor)
{
    Fl_File_Input* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->errorcolor());
}

SIMPLE_BLOCK(fltk_fl_file_input_errorcolor_1)
{
    Fl_File_Input* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->errorcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_file_input_value_1)
{
    Fl_File_Input* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_File_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->value(str2));
}

SIMPLE_BLOCK(fltk_fl_file_input_value_2)
{
    Fl_File_Input* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_File_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->value(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_file_input_value_3)
{
    Fl_File_Input* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_File_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->value());
}

/* Fl_Fill_Dial */
SIMPLE_BLOCK(fltk_fl_fill_dial_Fl_Fill_Dial)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Fill_Dial(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Fill_Slider */
SIMPLE_BLOCK(fltk_fl_fill_slider_Fl_Fill_Slider)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Fill_Slider(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Float_Input */
SIMPLE_BLOCK(fltk_fl_float_input_Fl_Float_Input)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Float_Input(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_FormsBitmap */
#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_formsbitmap_Fl_FormsBitmap)
{
	Fl_Boxtype point2;
	int num3;
	int num4;
	int num5;
	int num6;
	const char* str7;
	if ( SIMPLE_API_PARACOUNT != 7 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
		return ;
	}
	point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
	num6 = (int) (int) SIMPLE_API_GETNUMBER(5);
	str7 = (const char*)  SIMPLE_API_GETSTRING(6);
	SIMPLE_API_RETCPOINTER(new Fl_FormsBitmap(point2,num3,num4,num5,num6,str7),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_formsbitmap_set)
{
	Fl_FormsBitmap* point1;
	int num2;
	int num3;
	const uchar* point4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	point1 = (Fl_FormsBitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	point4 = (const uchar*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
	point1->set(num2,num3,point4);
}

SIMPLE_BLOCK(fltk_fl_formsbitmap_bitmap)
{
	Fl_FormsBitmap* point1;
	Fl_Bitmap * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_FormsBitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Bitmap *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point1->bitmap(point2);
}

SIMPLE_BLOCK(fltk_fl_formsbitmap_bitmap_1)
{
	Fl_FormsBitmap* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_FormsBitmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->bitmap(),"SMOOTHC_FLTK");
}

/* Fl_FormsPixmap */
SIMPLE_BLOCK(fltk_fl_formspixmap_Fl_FormsPixmap)
{
	Fl_Boxtype point2;
	int num3;
	int num4;
	int num5;
	int num6;
	const char* str7;
	if ( SIMPLE_API_PARACOUNT != 7 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
		return ;
	}
	point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(1);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
	num6 = (int) (int) SIMPLE_API_GETNUMBER(5);
	str7 = (const char*)  SIMPLE_API_GETSTRING(6);
	SIMPLE_API_RETCPOINTER(new Fl_FormsPixmap(point2,num3,num4,num5,num6,str7),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_formspixmap_set_1)
{
	char * const * str1 ;
	Fl_FormsPixmap* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_FormsPixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	str1 = (char * const *) SIMPLE_API_GETSTRING(2);
	point1->set(str1);
}
#endif

SIMPLE_BLOCK(fltk_fl_formspixmap_Pixmap)
{
    Fl_FormsPixmap* point1;
    Fl_Pixmap * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_FormsPixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Pixmap *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->Pixmap(point2);
}

SIMPLE_BLOCK(fltk_fl_formspixmap_Pixmap_1)
{
    Fl_FormsPixmap* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_FormsPixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->Pixmap(),"SMOOTHC_FLTK");
}

/* Fl_Free */
SIMPLE_BLOCK(fltk_fl_free_handle)
{
    Fl_Free* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Free*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_free_Fl_Free)
{
	uchar num2;
	int num3;
	int num4;
	int num5;
	int num6;
	const char* str7;
	FL_HANDLEPTR point8;
	if ( SIMPLE_API_PARACOUNT != 8 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
		return ;
	}
	num2 = (uchar) SIMPLE_API_GETNUMBER(1);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
	num6 = (int) (int) SIMPLE_API_GETNUMBER(5);
	str7 = (const char*)  SIMPLE_API_GETSTRING(6);
	point8 = (FL_HANDLEPTR) SIMPLE_API_GETCPOINTER(7,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(new Fl_Free(num2,num3,num4,num5,num6,str7,point8),"SMOOTHC_FLTK");
}
#endif

/* Fl_GIF_Image */
#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_gif_image_Fl_GIF_Image)
{
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str2 = (const char*)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETCPOINTER(new Fl_GIF_Image(str2),"SMOOTHC_FLTK");
}
#endif

/* Fl_Gl_Window */
#ifdef SIMPLE_FLTK_USE_FLTKGL
SIMPLE_BLOCK(fltk_fl_gl_window_show)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->show();
}

SIMPLE_BLOCK(fltk_fl_gl_window_show_1)
{
	Fl_Gl_Window* point1;
	int num2;
	char* * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point3 = (char* *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	point1->show(num2,point3);
}

SIMPLE_BLOCK(fltk_fl_gl_window_flush)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->flush();
}

SIMPLE_BLOCK(fltk_fl_gl_window_hide)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->hide();
}

SIMPLE_BLOCK(fltk_fl_gl_window_resize)
{
	Fl_Gl_Window* point1;
	int num2;
	int num3;
	int num4;
	int num5;
	if ( SIMPLE_API_PARACOUNT != 5 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
	num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
	point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_gl_window_handle_1)
{
	Fl_Gl_Window* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_gl_window_valid)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->valid(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_gl_window_valid_1)
{
	Fl_Gl_Window* point1;
	char num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (char) (char) SIMPLE_API_GETNUMBER(2);
	point1->valid(num2);
}

SIMPLE_BLOCK(fltk_fl_gl_window_invalidate)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->invalidate();
}

SIMPLE_BLOCK(fltk_fl_gl_window_context_valid)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->context_valid(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_gl_window_context_valid_1)
{
	Fl_Gl_Window* point1;
	char num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (char) (char) SIMPLE_API_GETNUMBER(2);
	point1->context_valid(num2);
}

SIMPLE_BLOCK(fltk_fl_gl_window_Fl_Gl_Window_can_do_1)
{
	int num1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
	SIMPLE_API_RETNUMBER(Fl_Gl_Window::can_do(num1));
}

SIMPLE_BLOCK(fltk_fl_gl_window_Fl_Gl_Window_can_do_2)
{
	const int * point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (const int *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(Fl_Gl_Window::can_do(point1));
}

SIMPLE_BLOCK(fltk_fl_gl_window_can_do)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->can_do());
}

SIMPLE_BLOCK(fltk_fl_gl_window_mode_1)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->mode(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_gl_window_mode_2)
{
	Fl_Gl_Window* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETNUMBER(point1->mode(num2));
}

SIMPLE_BLOCK(fltk_fl_gl_window_mode_3)
{
	Fl_Gl_Window* point1;
	const int * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (const int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->mode(point2));
}

SIMPLE_BLOCK(fltk_fl_gl_window_context)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->context();
}

SIMPLE_BLOCK(fltk_fl_gl_window_context_1)
{
	Fl_Gl_Window* point1;
	void* point2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	point1->context(point2,num3);
}

SIMPLE_BLOCK(fltk_fl_gl_window_make_current)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->make_current();
}

SIMPLE_BLOCK(fltk_fl_gl_window_swap_buffers)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->swap_buffers();
}

SIMPLE_BLOCK(fltk_fl_gl_window_ortho)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->ortho();
}

SIMPLE_BLOCK(fltk_fl_gl_window_can_do_overlay)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->can_do_overlay());
}

SIMPLE_BLOCK(fltk_fl_gl_window_redraw_overlay)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->redraw_overlay();
}

SIMPLE_BLOCK(fltk_fl_gl_window_hide_overlay)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->hide_overlay();
}

SIMPLE_BLOCK(fltk_fl_gl_window_make_overlay_current)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->make_overlay_current();
}

SIMPLE_BLOCK(fltk_fl_gl_window_as_gl_window)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->as_gl_window(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_gl_window_pixels_per_unit)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->pixels_per_unit());
}

SIMPLE_BLOCK(fltk_fl_gl_window_pixels_per_unit_1)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->pixels_per_unit());
}

SIMPLE_BLOCK(fltk_fl_gl_window_pixel_w)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->pixel_w());
}

SIMPLE_BLOCK(fltk_fl_gl_window_pixel_h)
{
	Fl_Gl_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Gl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->pixel_h());
}

SIMPLE_BLOCK(fltk_fl_gl_window_Fl_Gl_Window)
{
	int num2;
	int num3;
	const char* str4;
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
		return ;
	}
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
	str4 = (const char*)  SIMPLE_API_GETSTRING(3);
	SIMPLE_API_RETCPOINTER(new Fl_Gl_Window(num2,num3,str4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_gl_window_Fl_Gl_Window_1)
{
	int num2;
	int num3;
	int num4;
	int num5;
	const char* str6;
	if ( SIMPLE_API_PARACOUNT != 6 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
		return ;
	}
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
	num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
	str6 = (const char*)  SIMPLE_API_GETSTRING(6);
	SIMPLE_API_RETCPOINTER(new Fl_Gl_Window(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}
#endif

/* Fl_Group */
SIMPLE_BLOCK(fltk_fl_group_handle)
{
    Fl_Group* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_group_begin)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->begin();
}

SIMPLE_BLOCK(fltk_fl_group_end)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->end();
}

SIMPLE_BLOCK(fltk_fl_group_Fl_Group_current)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl_Group::current(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_group_Fl_Group_current_1)
{
    Fl_Group * point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl_Group::current(point1);
}

SIMPLE_BLOCK(fltk_fl_group_children)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->children(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_group_child)
{
    Fl_Group* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->child(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_group_find)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->find(point2));
}

SIMPLE_BLOCK(fltk_fl_group_find_1)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->find(*point2));
}

SIMPLE_BLOCK(fltk_fl_group_array)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->array(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_group_resize)
{
    Fl_Group* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_group_Fl_Group_1)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(5))->str ;
    SIMPLE_API_RETCPOINTER(new Fl_Group(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_group_add)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->add(*point2);
}

SIMPLE_BLOCK(fltk_fl_group_add_1)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->add(point2);
}

SIMPLE_BLOCK(fltk_fl_group_insert)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->insert(*point2,num3);
}

SIMPLE_BLOCK(fltk_fl_group_insert_1)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    Fl_Widget* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->insert(*point2,point3);
}

SIMPLE_BLOCK(fltk_fl_group_remove)
{
    Fl_Group* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->remove(num2);
}

SIMPLE_BLOCK(fltk_fl_group_remove_1)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->remove(*point2);
}

SIMPLE_BLOCK(fltk_fl_group_remove_2)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->remove(point2);
}

SIMPLE_BLOCK(fltk_fl_group_clear)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_group_resizable)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->resizable(*point2);
}

SIMPLE_BLOCK(fltk_fl_group_not_resizable)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->resizable(0);
}

SIMPLE_BLOCK(fltk_fl_group_resizable_1)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->resizable(point2);
}

SIMPLE_BLOCK(fltk_fl_group_resizable_2)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->resizable(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_group_add_resizable)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->add_resizable(*point2);
}

SIMPLE_BLOCK(fltk_fl_group_init_sizes)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->init_sizes();
}

SIMPLE_BLOCK(fltk_fl_group_clip_children)
{
    Fl_Group* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->clip_children(num2);
}

SIMPLE_BLOCK(fltk_fl_group_clip_children_1)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->clip_children());
}

SIMPLE_BLOCK(fltk_fl_group_as_group)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->as_group(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_group_focus)
{
    Fl_Group* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->focus(point2);
}

SIMPLE_BLOCK(fltk_fl_group__ddfdesign_kludge)
{
    Fl_Group* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->_ddfdesign_kludge(),"SMOOTHC_FLTK");
}

#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_group_forms_end)
{
	Fl_Group* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Group*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->forms_end();
}
#endif

/* Fl_End */
SIMPLE_BLOCK(fltk_fl_end_Fl_End)
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(new Fl_End(),"SMOOTHC_FLTK");
}

/* Help_Dialog */
#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_help_dialog_Fl_Help_Dialog)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	SIMPLE_API_RETCPOINTER(new Fl_Help_Dialog(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_dialog_h)
{
	Fl_Help_Dialog* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->h());
}

SIMPLE_BLOCK(fltk_fl_help_dialog_hide)
{
	Fl_Help_Dialog* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->hide();
}

SIMPLE_BLOCK(fltk_fl_help_dialog_load)
{
	Fl_Help_Dialog* point1;
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	str2 = (const char*)  SIMPLE_API_GETSTRING(2);
	point1->load(str2);
}

SIMPLE_BLOCK(fltk_fl_help_dialog_position)
{
	Fl_Help_Dialog* point1;
	int num2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	point1->position(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_help_dialog_resize_1)
{
	Fl_Help_Dialog* point1;
	int num2;
	int num3;
	int num4;
	int num5;
	if ( SIMPLE_API_PARACOUNT != 5 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
	num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
	point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_help_dialog_show)
{
	Fl_Help_Dialog* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->show();
}

SIMPLE_BLOCK(fltk_fl_help_dialog_show_1)
{
	Fl_Help_Dialog* point1;
	int num2;
	char* * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point3 = (char* *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	point1->show(num2,point3);
}

SIMPLE_BLOCK(fltk_fl_help_dialog_textsize)
{
	Fl_Help_Dialog* point1;
	Fl_Fontsize point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
	point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_help_dialog_textsize_1)
{
	Fl_Help_Dialog* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_dialog_topline)
{
	Fl_Help_Dialog* point1;
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	str2 = (const char*)  SIMPLE_API_GETSTRING(2);
	point1->topline(str2);
}

SIMPLE_BLOCK(fltk_fl_help_dialog_topline_1)
{
	Fl_Help_Dialog* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point1->topline(num2);
}

SIMPLE_BLOCK(fltk_fl_help_dialog_value)
{
	Fl_Help_Dialog* point1;
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	str2 = (const char*)  SIMPLE_API_GETSTRING(2);
	point1->value(str2);
}

SIMPLE_BLOCK(fltk_fl_help_dialog_value_1)
{
	Fl_Help_Dialog* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_dialog_visible)
{
	Fl_Help_Dialog* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->visible());
}

SIMPLE_BLOCK(fltk_fl_help_dialog_w)
{
	Fl_Help_Dialog* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->w());
}

SIMPLE_BLOCK(fltk_fl_help_dialog_x)
{
	Fl_Help_Dialog* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->x());
}

SIMPLE_BLOCK(fltk_fl_help_dialog_y)
{
	Fl_Help_Dialog* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Help_Dialog*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->y());
}
#endif

/* Fl_Help_View */
SIMPLE_BLOCK(fltk_MAX_FL_HELP_FS_ELTS)
{
    SIMPLE_API_RETNUMBER(MAX_FL_HELP_FS_ELTS);
}

#if FLTK_ABI_VERSION >= 10303
SIMPLE_BLOCK(fltk_fl_help_view_handle_1)
{
	Fl_Help_View* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETNUMBER(point1->handle(num2));
}
#endif

SIMPLE_BLOCK(fltk_fl_help_view_Fl_Help_View)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Help_View(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_directory)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->directory(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_filename)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->filename(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_find_2)
{
    Fl_Help_View* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->find(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_help_view_link)
{
    Fl_Help_View* point1;
    Fl_Help_Func * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Help_Func *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->link(point2);
}

SIMPLE_BLOCK(fltk_fl_help_view_load_1)
{
    Fl_Help_View* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->load(str2));
}

SIMPLE_BLOCK(fltk_fl_help_view_resize_2)
{
    Fl_Help_View* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_help_view_size)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_size_1)
{
    Fl_Help_View* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->size(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_help_view_textcolor)
{
    Fl_Help_View* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_help_view_textcolor_1)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_textfont)
{
    Fl_Help_View* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_help_view_textfont_1)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_textsize_2)
{
    Fl_Help_View* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_help_view_textsize_3)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_title)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->title());
}

SIMPLE_BLOCK(fltk_fl_help_view_topline_2)
{
    Fl_Help_View* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->topline(str2);
}

SIMPLE_BLOCK(fltk_fl_help_view_topline_3)
{
    Fl_Help_View* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->topline(num2);
}

SIMPLE_BLOCK(fltk_fl_help_view_topline_4)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->topline(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_leftline)
{
    Fl_Help_View* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->leftline(num2);
}

SIMPLE_BLOCK(fltk_fl_help_view_leftline_1)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->leftline(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_value_2)
{
    Fl_Help_View* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->value(str2);
}

SIMPLE_BLOCK(fltk_fl_help_view_value_3)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_clear_selection)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_selection();
}

SIMPLE_BLOCK(fltk_fl_help_view_select_all)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->select_all();
}

SIMPLE_BLOCK(fltk_fl_help_view_scrollbar_size)
{
    Fl_Help_View* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->scrollbar_size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_help_view_scrollbar_size_1)
{
    Fl_Help_View* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Help_View*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->scrollbar_size(num2);
}

/* Fl_Hold_Browser */
SIMPLE_BLOCK(fltk_fl_hold_browser_Fl_Hold_Browser)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Hold_Browser(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Hor_Fill_Slider */
SIMPLE_BLOCK(fltk_fl_hor_fill_slider_Fl_Hor_Fill_Slider)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Hor_Fill_Slider(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Hor_Nice_Slider */
SIMPLE_BLOCK(fltk_fl_hor_nice_slider_Fl_Hor_Nice_Slider)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Hor_Nice_Slider(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Hor_Slider */
SIMPLE_BLOCK(fltk_fl_hor_slider_Fl_Hor_Slider)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Hor_Slider(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Hor_Value_Slider */
SIMPLE_BLOCK(fltk_fl_hor_value_slider_Fl_Hor_Value_Slider)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Hor_Value_Slider(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Image */
SIMPLE_BLOCK(fltk_FL_RGB_SCALING_NEAREST)
{
    SIMPLE_API_RETNUMBER(FL_RGB_SCALING_NEAREST);
}

SIMPLE_BLOCK(fltk_fl_image_Fl_Image_ERR_NO_IMAGE)
{
    SIMPLE_API_RETNUMBER(Fl_Image::ERR_NO_IMAGE);
}

SIMPLE_BLOCK(fltk_fl_image_Fl_Image_ERR_FILE_ACCESS)
{
    SIMPLE_API_RETNUMBER(Fl_Image::ERR_FILE_ACCESS);
}

SIMPLE_BLOCK(fltk_fl_image_Fl_Image_ERR_FORMAT)
{
    SIMPLE_API_RETNUMBER(Fl_Image::ERR_FORMAT);
}

SIMPLE_BLOCK(fltk_fl_image_w)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->w(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_h)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->h(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_d)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->d(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_ld)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->ld(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_count)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->count(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_data)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->data(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_fail)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->fail());
}

SIMPLE_BLOCK(fltk_fl_image_Fl_Image)
{
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(new Fl_Image(num2,num3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_copy)
{
    Fl_Image* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->copy(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_copy_1)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->copy(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_color_average)
{
    Fl_Image* point1;
    Fl_Color num2;
    float num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (float) (float) SIMPLE_API_GETNUMBER(3);
    point1->color_average(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_image_inactive)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->inactive();
}

SIMPLE_BLOCK(fltk_fl_image_desaturate)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->desaturate();
}

SIMPLE_BLOCK(fltk_fl_image_label)
{
    Fl_Image* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->label(point2);
}

SIMPLE_BLOCK(fltk_fl_image_label_1)
{
    Fl_Image* point1;
    Fl_Menu_Item* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Menu_Item*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->label(point2);
}

SIMPLE_BLOCK(fltk_fl_image_draw)
{
    Fl_Image* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    point1->draw(num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_image_draw_1)
{
    Fl_Image* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->draw(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_image_uncache)
{
    Fl_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->uncache();
}

SIMPLE_BLOCK(fltk_fl_image_Fl_Image_RGB_scaling)
{
    Fl_RGB_Scaling num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_RGB_Scaling) (int) SIMPLE_API_GETNUMBER(1);
    Fl_Image::RGB_scaling(num1);
}

SIMPLE_BLOCK(fltk_fl_image_Fl_Image_RGB_scaling_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Image::RGB_scaling());
}

/* Fl_RGB_Image */
SIMPLE_BLOCK(fltk_fl_rgb_image_Fl_RGB_Image)
{
    const uchar* point2;
    int num3;
    int num4;
    int num5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point2 = (const uchar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(5);
    SIMPLE_API_RETCPOINTER(new Fl_RGB_Image(point2,num3,num4,num5,num6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_rgb_image_Fl_RGB_Image_1)
{
    const Fl_Pixmap * point2;
    Fl_Color num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point2 = (const Fl_Pixmap *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num3 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(new Fl_RGB_Image(point2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_rgb_image_copy_2)
{
    Fl_RGB_Image* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->copy(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_rgb_image_copy_3)
{
    Fl_RGB_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->copy(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_rgb_image_color_average_1)
{
    Fl_RGB_Image* point1;
    Fl_Color num2;
    float num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (float) (float) SIMPLE_API_GETNUMBER(3);
    point1->color_average(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_rgb_image_desaturate_1)
{
    Fl_RGB_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->desaturate();
}

SIMPLE_BLOCK(fltk_fl_rgb_image_draw_2)
{
    Fl_RGB_Image* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    point1->draw(num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_rgb_image_draw_3)
{
    Fl_RGB_Image* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->draw(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_rgb_image_label_2)
{
    Fl_RGB_Image* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->label(point2);
}

SIMPLE_BLOCK(fltk_fl_rgb_image_label_3)
{
    Fl_RGB_Image* point1;
    Fl_Menu_Item* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Menu_Item*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->label(point2);
}

SIMPLE_BLOCK(fltk_fl_rgb_image_uncache_1)
{
    Fl_RGB_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->uncache();
}

SIMPLE_BLOCK(fltk_fl_rgb_image_Fl_RGB_Image_max_size)
{
    size_t num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (size_t) (size_t) SIMPLE_API_GETNUMBER(1);
    Fl_RGB_Image::max_size(num1);
}

SIMPLE_BLOCK(fltk_fl_rgb_image_Fl_RGB_Image_max_size_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_RGB_Image::max_size());
}

/* Fl_Image_Surface */
#ifdef Fl_Image_Surface::class_id
/* SIMPLE_BLOCK(fltk_fl_image_surface_Fl_Image_Surface_class_id)
{
	SIMPLE_API_RETSTRING(Fl_Image_Surface::class_id);
} */
#endif

/*SIMPLE_BLOCK(fltk_fl_image_surface_class_name)
{
	Fl_Image_Surface* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Image_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETSTRING(point1->class_name());
} */

SIMPLE_BLOCK(fltk_fl_image_surface_Fl_Image_Surface)
{
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(new Fl_Image_Surface(num2,num3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_surface_Fl_Image_Surface_1)
{
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(new Fl_Image_Surface(num2,num3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_surface_Fl_Image_Surface_2)
{
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(new Fl_Image_Surface(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_surface_set_current)
{
    Fl_Image_Surface* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_current();
}

SIMPLE_BLOCK(fltk_fl_image_surface_draw_4)
{
    Fl_Image_Surface* point1;
    Fl_Widget* point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Image_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->draw(point2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_image_surface_draw_decorated_window)
{
    Fl_Image_Surface* point1;
    Fl_Window* point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Image_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Window*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->draw_decorated_window(point2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_image_surface_image)
{
    Fl_Image_Surface* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->image(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_image_surface_highres_image)
{
    Fl_Image_Surface* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Image_Surface*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->highres_image(),"SMOOTHC_FLTK");
}

#ifdef __APPLE__
/*SIMPLE_BLOCK(fltk_fl_quartz_flipped_surface__class_name_1)
{
	Fl_Quartz_Flipped_Surface_* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Quartz_Flipped_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETSTRING(point1->class_name());
} */

SIMPLE_BLOCK(fltk_fl_quartz_flipped_surface__Fl_Quartz_Flipped_Surface_)
{
	int num2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETCPOINTER(new Fl_Quartz_Flipped_Surface_(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_quartz_flipped_surface__translate)
{
	Fl_Quartz_Flipped_Surface_* point1;
	int num2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Quartz_Flipped_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	point1->translate(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_quartz_flipped_surface__untranslate)
{
	Fl_Quartz_Flipped_Surface_* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Quartz_Flipped_Surface_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->untranslate();
}
#endif

/* Fl_Input_ */
SIMPLE_BLOCK(fltk_fl_input_handle)
{
    Fl_Input* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_input_Fl_Input)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Input(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input__resize)
{
    Fl_Input_* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_input__value)
{
    Fl_Input_* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->value(str2));
}

SIMPLE_BLOCK(fltk_fl_input__value_1)
{
    Fl_Input_* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->value(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_input__static_value)
{
    Fl_Input_* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->static_value(str2));
}

SIMPLE_BLOCK(fltk_fl_input__static_value_1)
{
    Fl_Input_* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->static_value(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_input__value_2)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->value());
}

SIMPLE_BLOCK(fltk_fl_input__index)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->index(num2));
}

SIMPLE_BLOCK(fltk_fl_input__size)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input__size_1)
{
    Fl_Input_* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->size(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_input__maximum_size)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->maximum_size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input__maximum_size_1)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->maximum_size(num2);
}

SIMPLE_BLOCK(fltk_fl_input__position)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->position());
}

SIMPLE_BLOCK(fltk_fl_input__mark)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->mark());
}

SIMPLE_BLOCK(fltk_fl_input__position_1)
{
    Fl_Input_* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->position(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_input__position_2)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->position(num2));
}

SIMPLE_BLOCK(fltk_fl_input__mark_1)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->mark(num2));
}

SIMPLE_BLOCK(fltk_fl_input__replace)
{
    Fl_Input_* point1;
    int num2;
    int num3;
    const char* str4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    SIMPLE_API_RETNUMBER(point1->replace(num2,num3,str4,num5));
}

SIMPLE_BLOCK(fltk_fl_input__cut)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->cut());
}

SIMPLE_BLOCK(fltk_fl_input__cut_1)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->cut(num2));
}

SIMPLE_BLOCK(fltk_fl_input__cut_2)
{
    Fl_Input_* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->cut(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_input__insert)
{
    Fl_Input_* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->insert(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_input__copy_4)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->copy(num2));
}

SIMPLE_BLOCK(fltk_fl_input__undo)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->undo());
}

SIMPLE_BLOCK(fltk_fl_input__copy_cuts)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->copy_cuts());
}

SIMPLE_BLOCK(fltk_fl_input__shortcut)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->shortcut(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input__shortcut_1)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->shortcut(num2);
}

SIMPLE_BLOCK(fltk_fl_input__textfont)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input__textfont_1)
{
    Fl_Input_* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_input__textsize)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input__textsize_1)
{
    Fl_Input_* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_input__textcolor)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input__textcolor_1)
{
    Fl_Input_* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_input__cursor_color)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->cursor_color());
}

SIMPLE_BLOCK(fltk_fl_input__cursor_color_1)
{
    Fl_Input_* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->cursor_color(num2);
}

SIMPLE_BLOCK(fltk_fl_input__input_type)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->input_type(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input__input_type_1)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->input_type(num2);
}

SIMPLE_BLOCK(fltk_fl_input__readonly)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->readonly());
}

SIMPLE_BLOCK(fltk_fl_input__readonly_1)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->readonly(num2);
}

SIMPLE_BLOCK(fltk_fl_input__wrap)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->wrap(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input__wrap_1)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->wrap(num2);
}

SIMPLE_BLOCK(fltk_fl_input__tab_nav)
{
    Fl_Input_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->tab_nav(num2);
}

SIMPLE_BLOCK(fltk_fl_input__tab_nav_1)
{
    Fl_Input_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->tab_nav(),"SMOOTHC_FLTK");
}

/* Fl_Input_Choice */
SIMPLE_BLOCK(fltk_fl_input_choice_add)
{
    Fl_Input_Choice* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->add(str2);
}

SIMPLE_BLOCK(fltk_fl_input_choice_changed)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->changed(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input_choice_clear_changed)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_changed();
}

SIMPLE_BLOCK(fltk_fl_input_choice_set_changed)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_changed();
}

SIMPLE_BLOCK(fltk_fl_input_choice_clear)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_input_choice_down_box)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->down_box(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input_choice_down_box_1)
{
    Fl_Input_Choice* point1;
    Fl_Boxtype point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(2);
    point1->down_box(point2);
}

SIMPLE_BLOCK(fltk_fl_input_choice_menu)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->menu(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input_choice_menu_1)
{
    Fl_Input_Choice* point1;
    const Fl_Menu_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Menu_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->menu(point2);
}

SIMPLE_BLOCK(fltk_fl_input_choice_resize_1)
{
    Fl_Input_Choice* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_input_choice_textcolor_2)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input_choice_textcolor_3)
{
    Fl_Input_Choice* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_input_choice_textfont_2)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input_choice_textfont_3)
{
    Fl_Input_Choice* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_input_choice_textsize_2)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input_choice_textsize_3)
{
    Fl_Input_Choice* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_input_choice_value_3)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input_choice_value_4)
{
    Fl_Input_Choice* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->value(str2);
}

SIMPLE_BLOCK(fltk_fl_input_choice_value_5)
{
    Fl_Input_Choice* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->value(num2);
}

SIMPLE_BLOCK(fltk_fl_input_choice_menubutton)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->menubutton(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_input_choice_input)
{
    Fl_Input_Choice* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Input_Choice*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->input(),"SMOOTHC_FLTK");
}

/* Fl_Int_Input */
SIMPLE_BLOCK(fltk_fl_int_input_Fl_Int_Input)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Int_Input(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_JPEG_Image */
#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_jpeg_image_Fl_JPEG_Image)
{
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str2 = (const char*)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETCPOINTER(new Fl_JPEG_Image(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_jpeg_image_Fl_JPEG_Image_1)
{
	const char* str2;
	const unsigned char* point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	str2 = (const char*)  SIMPLE_API_GETSTRING(1);
	point3 = (const unsigned char*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(new Fl_JPEG_Image(str2,point3),"SMOOTHC_FLTK");
}
#endif

/* Fl_Light_Button */
SIMPLE_BLOCK(fltk_fl_light_button_handle_1)
{
    Fl_Light_Button* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Light_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_light_button_Fl_Light_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Light_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Line_Dial */
SIMPLE_BLOCK(fltk_fl_line_dial_Fl_Line_Dial)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Line_Dial(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Menu_ */
SIMPLE_BLOCK(fltk_fl_menu__picked)
{
    Fl_Menu_* point1;
    const Fl_Menu_Item* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Menu_Item*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->picked(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__find_item)
{
    Fl_Menu_* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->find_item(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__find_item_1)
{
    Fl_Menu_* point1;
    Fl_Callback* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Callback*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->find_item(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__find_index)
{
    Fl_Menu_* point1;
    char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->find_index(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__find_index_1)
{
    Fl_Menu_* point1;
    Fl_Menu_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Menu_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->find_index(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__find_index_2)
{
    Fl_Menu_* point1;
    Fl_Callback * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Callback *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->find_index(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__test_shortcut)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->test_shortcut(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__global)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->global();
}

SIMPLE_BLOCK(fltk_fl_menu__menu)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->menu(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__menu_1)
{
    Fl_Menu_* point1;
    const Fl_Menu_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Menu_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->menu(point2);
}

SIMPLE_BLOCK(fltk_fl_menu__copy_4)
{
    Fl_Menu_* point1;
    const Fl_Menu_Item * point2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Menu_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->copy(point2,point3);
}

SIMPLE_BLOCK(fltk_fl_menu__insert)
{
    Fl_Menu_* point1;
    int num2;
    const char* str3;
    int num4;
    //Fl_Callback* point5;
    //void* point6;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    //point5 = (Fl_Callback*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    //point6 = (void*) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    SIMPLE_API_RETNUMBER(point1->insert(num2,str3,num4,SimpleMenuCallBack,(void*)num6,num7));
}

SIMPLE_BLOCK(fltk_fl_menu__add)
{
    Fl_Menu_* point1;
    const char* str2;
    int num3;
    //Fl_Callback* point4;
    //void* point5;
    int num5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    //point4 = (Fl_Callback*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    //point5 = (void*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    SIMPLE_API_RETNUMBER(point1->add(str2,num3,SimpleMenuCallBack,(void*)num5,num6));
}

SIMPLE_BLOCK(fltk_fl_menu__add_1)
{
    Fl_Menu_* point1;
    const char* str2;
    const char* str3;
    //Fl_Callback* point4;
    //void* point5;
    int num5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    //point4 = (Fl_Callback*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    //point5 = (void*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    SIMPLE_API_RETNUMBER(point1->add(str2,str3,SimpleMenuCallBack,(void*)num5,num6));
}

SIMPLE_BLOCK(fltk_fl_menu__insert_1)
{
    Fl_Menu_* point1;
    int num2;
    const char* str3;
    const char* str4;
    Fl_Callback* point5;
    void* point6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    point5 = (Fl_Callback*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    point6 = (void*) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    SIMPLE_API_RETNUMBER(point1->insert(num2,str3,str4,point5,point6,num7));
}

SIMPLE_BLOCK(fltk_fl_menu__add_2)
{
    Fl_Menu_* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->add(str2));
}

SIMPLE_BLOCK(fltk_fl_menu__size)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__size_1)
{
    Fl_Menu_* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->size(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_menu__clear)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_menu__clear_submenu)
{
    Fl_Menu_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->clear_submenu(num2));
}

SIMPLE_BLOCK(fltk_fl_menu__replace)
{
    Fl_Menu_* point1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point1->replace(num2,str3);
}

SIMPLE_BLOCK(fltk_fl_menu__remove)
{
    Fl_Menu_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->remove(num2);
}

SIMPLE_BLOCK(fltk_fl_menu__shortcut)
{
    Fl_Menu_* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->shortcut(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_menu__mode)
{
    Fl_Menu_* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->mode(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_menu__mode_1)
{
    Fl_Menu_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->mode(num2));
}

SIMPLE_BLOCK(fltk_fl_menu__mvalue)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->mvalue(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__value)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__value_1)
{
    Fl_Menu_* point1;
    const Fl_Menu_Item* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Menu_Item*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->value(point2));
}

SIMPLE_BLOCK(fltk_fl_menu__value_2)
{
    Fl_Menu_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->value(num2));
}

SIMPLE_BLOCK(fltk_fl_menu__text)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->text(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__text_1)
{
    Fl_Menu_* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->text(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__textfont)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->textfont());
}

SIMPLE_BLOCK(fltk_fl_menu__textfont_1)
{
    Fl_Menu_* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_menu__textsize)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->textsize());
}

SIMPLE_BLOCK(fltk_fl_menu__textsize_1)
{
    Fl_Menu_* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) int SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_menu__textcolor)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->textcolor());
}

SIMPLE_BLOCK(fltk_fl_menu__textcolor_1)
{
    Fl_Menu_* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_menu__down_box)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->down_box(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu__down_box_1)
{
    Fl_Menu_* point1;
    Fl_Boxtype point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(2);
    point1->down_box(point2);
}

SIMPLE_BLOCK(fltk_fl_menu__down_color)
{
    Fl_Menu_* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->down_color());
}

SIMPLE_BLOCK(fltk_fl_menu__down_color_1)
{
    Fl_Menu_* point1;
    unsigned num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (unsigned) (int) SIMPLE_API_GETNUMBER(2);
    point1->down_color(num2);
}

SIMPLE_BLOCK(fltk_fl_menu__setonly)
{
    Fl_Menu_* point1;
    Fl_Menu_Item* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Menu_Item*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->setonly(point2);
}

/* Fl_Menu_Bar */
SIMPLE_BLOCK(fltk_fl_menu_bar_handle)
{
    Fl_Menu_Bar* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_menu_bar_Fl_Menu_Bar)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Menu_Bar(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Menu_Button */
SIMPLE_BLOCK(fltk_fl_menu_button_POPUP1)
{
    SIMPLE_API_RETNUMBER(Fl_Menu_Button::POPUP1);
}

SIMPLE_BLOCK(fltk_fl_menu_button_POPUP2)
{
    SIMPLE_API_RETNUMBER(Fl_Menu_Button::POPUP2);
}

SIMPLE_BLOCK(fltk_fl_menu_button_POPUP12)
{
    SIMPLE_API_RETNUMBER(Fl_Menu_Button::POPUP12);
}

SIMPLE_BLOCK(fltk_fl_menu_button_POPUP3)
{
    SIMPLE_API_RETNUMBER(Fl_Menu_Button::POPUP3);
}

SIMPLE_BLOCK(fltk_fl_menu_button_POPUP13)
{
    SIMPLE_API_RETNUMBER(Fl_Menu_Button::POPUP13);
}

SIMPLE_BLOCK(fltk_fl_menu_button_POPUP23)
{
    SIMPLE_API_RETNUMBER(Fl_Menu_Button::POPUP23);
}

SIMPLE_BLOCK(fltk_fl_menu_button_handle_1)
{
    Fl_Menu_Button* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Menu_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_menu_button_popup)
{
    Fl_Menu_Button* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->popup(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu_button_Fl_Menu_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Menu_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_FL_MENU_INACTIVE)
{
    SIMPLE_API_RETNUMBER(FL_MENU_INACTIVE);
}

SIMPLE_BLOCK(fltk_FL_MENU_TOGGLE)
{
    SIMPLE_API_RETNUMBER(FL_MENU_TOGGLE);
}

SIMPLE_BLOCK(fltk_FL_MENU_VALUE)
{
    SIMPLE_API_RETNUMBER(FL_MENU_VALUE);
}

SIMPLE_BLOCK(fltk_FL_MENU_RADIO)
{
    SIMPLE_API_RETNUMBER(FL_MENU_RADIO);
}

SIMPLE_BLOCK(fltk_FL_MENU_INVISIBLE)
{
    SIMPLE_API_RETNUMBER(FL_MENU_INVISIBLE);
}

SIMPLE_BLOCK(fltk_FL_SUBMENU_POINTER)
{
    SIMPLE_API_RETNUMBER(FL_SUBMENU_POINTER);
}

SIMPLE_BLOCK(fltk_FL_SUBMENU)
{
    SIMPLE_API_RETNUMBER(FL_SUBMENU);
}

SIMPLE_BLOCK(fltk_FL_MENU_DIVIDER)
{
    SIMPLE_API_RETNUMBER(FL_MENU_DIVIDER);
}

SIMPLE_BLOCK(fltk_FL_MENU_HORIZONTAL)
{
    SIMPLE_API_RETNUMBER(FL_MENU_HORIZONTAL);
}

SIMPLE_BLOCK(fltk_fl_old_shortcut_menu)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETCPOINTER(fl_old_shortcut(str1),"SMOOTHC_FLTK");
}

/* Fl_Menu_Window */
SIMPLE_BLOCK(fltk_fl_menu_window_show)
{
    Fl_Menu_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show();
}

SIMPLE_BLOCK(fltk_fl_menu_window_erase)
{
    Fl_Menu_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->erase();
}

SIMPLE_BLOCK(fltk_fl_menu_window_flush)
{
    Fl_Menu_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->flush();
}

SIMPLE_BLOCK(fltk_fl_menu_window_hide)
{
    Fl_Menu_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->hide();
}

SIMPLE_BLOCK(fltk_fl_menu_window_overlay)
{
    Fl_Menu_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->overlay());
}

SIMPLE_BLOCK(fltk_fl_menu_window_set_overlay)
{
    Fl_Menu_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_overlay();
}

SIMPLE_BLOCK(fltk_fl_menu_window_clear_overlay)
{
    Fl_Menu_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Menu_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_overlay();
}

SIMPLE_BLOCK(fltk_fl_menu_window_Fl_Menu_Window)
{
    int num2;
    int num3;
    const char* str4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str4 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETCPOINTER(new Fl_Menu_Window(num2,num3,str4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_menu_window_Fl_Menu_Window_1)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Menu_Window(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Multiline_Input */
SIMPLE_BLOCK(fltk_fl_multiline_input_Fl_Multiline_Input)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Multiline_Input(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Multiline_Output */
SIMPLE_BLOCK(fltk_fl_multiline_output_Fl_Multiline_Output)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Multiline_Output(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Multi_Browser */
SIMPLE_BLOCK(fltk_fl_multi_browser_Fl_Multi_Browser)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Multi_Browser(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Native_File */
SIMPLE_BLOCK(fltk_fl_native_file_chooser_BROWSE_FILE)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::BROWSE_FILE);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_BROWSE_DIRECTORY)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_BROWSE_MULTI_FILE)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::BROWSE_MULTI_FILE);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_BROWSE_MULTI_DIRECTORY)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::BROWSE_MULTI_DIRECTORY);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_BROWSE_SAVE_FILE)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_NO_OPTIONS)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::NO_OPTIONS);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_SAVEAS_CONFIRM)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::SAVEAS_CONFIRM);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_NEW_FOLDER)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::NEW_FOLDER);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_PREVIEW)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::PREVIEW);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_USE_FILTER_EXT)
{
    SIMPLE_API_RETNUMBER(Fl_Native_File_Chooser::USE_FILTER_EXT);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_Fl_Native_File_Chooser_file_exists_message)
{
    SIMPLE_API_RETSTRING(Fl_Native_File_Chooser::file_exists_message);
}

#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_native_file_chooser_Fl_Native_File_Chooser)
{
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
	SIMPLE_API_RETCPOINTER(new Fl_Native_File_Chooser(num2),"SMOOTHC_FLTK");
}
#endif

SIMPLE_BLOCK(fltk_fl_native_file_chooser_type)
{
    Fl_Native_File_Chooser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->type(num2);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_type_1)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->type(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_options)
{
    Fl_Native_File_Chooser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->options(num2);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_options_1)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->options(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_count)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->count(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_filename)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->filename(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_filename_1)
{
    Fl_Native_File_Chooser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->filename(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_directory)
{
    Fl_Native_File_Chooser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->directory(str2);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_directory_1)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->directory(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_title)
{
    Fl_Native_File_Chooser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->title(str2);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_title_1)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->title(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_filter)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->filter(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_filter_1)
{
    Fl_Native_File_Chooser* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->filter(str2);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_filters)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->filters(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_filter_value)
{
    Fl_Native_File_Chooser* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->filter_value(num2);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_filter_value_1)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->filter_value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_preset_file)
{
    Fl_Native_File_Chooser* point1;
    const char* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const char*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->preset_file(point2);
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_preset_file_1)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->preset_file(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_errmsg)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->errmsg(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_native_file_chooser_show)
{
    Fl_Native_File_Chooser* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Native_File_Chooser*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->show());
}

/* Fl_Nice_Slider */
SIMPLE_BLOCK(fltk_fl_nice_slider_Fl_Nice_Slider)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Nice_Slider(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Output */
SIMPLE_BLOCK(fltk_fl_output_Fl_Output)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Output(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Overlay_Window */
SIMPLE_BLOCK(fltk_fl_overlay_window_show)
{
    Fl_Overlay_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Overlay_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show();
}

SIMPLE_BLOCK(fltk_fl_overlay_window_flush)
{
    Fl_Overlay_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Overlay_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->flush();
}

SIMPLE_BLOCK(fltk_fl_overlay_window_hide)
{
    Fl_Overlay_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Overlay_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->hide();
}

SIMPLE_BLOCK(fltk_fl_overlay_window_resize)
{
    Fl_Overlay_Window* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Overlay_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_overlay_window_can_do_overlay)
{
    Fl_Overlay_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Overlay_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->can_do_overlay());
}

SIMPLE_BLOCK(fltk_fl_overlay_window_redraw_overlay)
{
    Fl_Overlay_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Overlay_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->redraw_overlay();
}

SIMPLE_BLOCK(fltk_fl_overlay_window_show_1)
{
    Fl_Overlay_Window* point1;
    int num2;
    char* * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Overlay_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (char* *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->show(num2,point3);
}

/* Fl_Pack */
SIMPLE_BLOCK(fltk_fl_pack_VERTICAL)
{
    SIMPLE_API_RETNUMBER(Fl_Pack::VERTICAL);
}

SIMPLE_BLOCK(fltk_fl_pack_HORIZONTAL)
{
    SIMPLE_API_RETNUMBER(Fl_Pack::HORIZONTAL);
}

SIMPLE_BLOCK(fltk_fl_pack_Fl_Pack)
{
    int num2;
    int num3;
    int point4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point4 = (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Pack(num2,num3,point4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_pack_spacing)
{
    Fl_Pack* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Pack*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->spacing(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_pack_spacing_1)
{
    Fl_Pack* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Pack*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->spacing(num2);
}

SIMPLE_BLOCK(fltk_fl_pack_horizontal)
{
    Fl_Pack* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Pack*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->horizontal(),"SMOOTHC_FLTK");
}

/* Fl_Paged_Device */
SIMPLE_BLOCK(fltk_fl_paged_device_A0)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A0);
}

SIMPLE_BLOCK(fltk_fl_paged_device_A1)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A1);
}

SIMPLE_BLOCK(fltk_fl_paged_device_A2)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A2);
}

SIMPLE_BLOCK(fltk_fl_paged_device_A3)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A3);
}

SIMPLE_BLOCK(fltk_fl_paged_device_A4)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A4);
}

SIMPLE_BLOCK(fltk_fl_paged_device_A5)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A5);
}

SIMPLE_BLOCK(fltk_fl_paged_device_A6)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A6);
}

SIMPLE_BLOCK(fltk_fl_paged_device_A7)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A7);
}

SIMPLE_BLOCK(fltk_fl_paged_device_A8)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A8);
}

SIMPLE_BLOCK(fltk_fl_paged_device_A9)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::A9);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B0)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B0);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B1)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B1);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B2)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B2);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B3)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B3);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B4)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B4);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B5)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B5);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B6)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B6);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B7)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B7);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B8)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B8);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B9)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B9);
}

SIMPLE_BLOCK(fltk_fl_paged_device_B10)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::B10);
}

SIMPLE_BLOCK(fltk_fl_paged_device_C5E)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::C5E);
}

SIMPLE_BLOCK(fltk_fl_paged_device_DLE)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::DLE);
}

SIMPLE_BLOCK(fltk_fl_paged_device_EXECUTIVE)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::EXECUTIVE);
}

SIMPLE_BLOCK(fltk_fl_paged_device_FOLIO)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::FOLIO);
}

SIMPLE_BLOCK(fltk_fl_paged_device_LEDGER)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::LEDGER);
}

SIMPLE_BLOCK(fltk_fl_paged_device_LEGAL)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::LEGAL);
}

SIMPLE_BLOCK(fltk_fl_paged_device_LETTER)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::LETTER);
}

SIMPLE_BLOCK(fltk_fl_paged_device_TABLOID)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::TABLOID);
}

SIMPLE_BLOCK(fltk_fl_paged_device_ENVELOPE)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::ENVELOPE);
}

SIMPLE_BLOCK(fltk_fl_paged_device_MEDIA)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::MEDIA);
}

SIMPLE_BLOCK(fltk_fl_paged_device_PORTRAIT)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::PORTRAIT);
}

SIMPLE_BLOCK(fltk_fl_paged_device_LANDSCAPE)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::LANDSCAPE);
}

SIMPLE_BLOCK(fltk_fl_paged_device_REVERSED)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::REVERSED);
}

SIMPLE_BLOCK(fltk_fl_paged_device_ORIENTATION)
{
    SIMPLE_API_RETNUMBER(Fl_Paged_Device::ORIENTATION);
}

/* SIMPLE_BLOCK(fltk_fl_paged_device_Fl_Paged_Device_class_id)
{
	SIMPLE_API_RETSTRING(Fl_Paged_Device::class_id);
} */

/*SIMPLE_BLOCK(fltk_fl_paged_device_class_name)
{
	Fl_Paged_Device* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETSTRING(point1->class_name());
}*/

SIMPLE_BLOCK(fltk_fl_paged_device_start_job)
{
    Fl_Paged_Device* point1;
    int num2;
    int * point3;
    int * point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->start_job(num2,point3,point4));
}

SIMPLE_BLOCK(fltk_fl_paged_device_start_page)
{
    Fl_Paged_Device* point1;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->start_page());
}

SIMPLE_BLOCK(fltk_fl_paged_device_printable_rect)
{
    Fl_Paged_Device* point1;
    int * point2;
    int * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->printable_rect(point2,point3));
}

SIMPLE_BLOCK(fltk_fl_paged_device_margins)
{
    Fl_Paged_Device* point1;
    int * point2;
    int * point3;
    int * point4;
    int * point5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (int *) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    point1->margins(point2,point3,point4,point5);
}

SIMPLE_BLOCK(fltk_fl_paged_device_origin)
{
    Fl_Paged_Device* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->origin(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_paged_device_origin_1)
{
    Fl_Paged_Device* point1;
    int * point2;
    int * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->origin(point2,point3);
}

SIMPLE_BLOCK(fltk_fl_paged_device_scale)
{
    Fl_Paged_Device* point1;
    float num2;
    float num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (float) (float) SIMPLE_API_GETNUMBER(2);
    num3 = (float) (float) SIMPLE_API_GETNUMBER(3);
    point1->scale(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_paged_device_rotate)
{
    Fl_Paged_Device* point1;
    float num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (float) (float) SIMPLE_API_GETNUMBER(2);
    point1->rotate(num2);
}

SIMPLE_BLOCK(fltk_fl_paged_device_translate)
{
    Fl_Paged_Device* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->translate(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_paged_device_untranslate)
{
    Fl_Paged_Device* point1;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->untranslate();
}

SIMPLE_BLOCK(fltk_fl_paged_device_print_widget)
{
    Fl_Paged_Device* point1;
    Fl_Widget* point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->print_widget(point2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_paged_device_print_window)
{
    Fl_Paged_Device* point1;
    Fl_Window * point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Window *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->print_window(point2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_paged_device_print_window_part)
{
    Fl_Paged_Device* point1;
    Fl_Window * point2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    int num8;
    if ( SIMPLE_API_PARACOUNT != 8 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
        return ;
    }
    point1 = (Fl_Paged_Device*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Window *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    num8 = (int) (int) SIMPLE_API_GETNUMBER(8);
    point1->print_window_part(point2,num3,num4,num5,num6,num7,num8);
}

/* Fl_Pixmap */
SIMPLE_BLOCK(fltk_fl_pixmap_Fl_Pixmap)
{
    const char*  * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point2 = (const char*  *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(new Fl_Pixmap(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_pixmap_Fl_Pixmap_1)
{
    const uchar*  * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point2 = (const uchar*  *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(new Fl_Pixmap(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_pixmap_Fl_Pixmap_2)
{
    const char*  * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point2 = (const char*  *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(new Fl_Pixmap(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_pixmap_Fl_Pixmap_3)
{
    const uchar*  * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point2 = (const uchar*  *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(new Fl_Pixmap(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_pixmap_copy)
{
    Fl_Pixmap* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Pixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->copy(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_pixmap_copy_1)
{
    Fl_Pixmap* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Pixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->copy(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_pixmap_color_average)
{
    Fl_Pixmap* point1;
    Fl_Color num2;
    float num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Pixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (float) (float) SIMPLE_API_GETNUMBER(3);
    point1->color_average(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_pixmap_desaturate)
{
    Fl_Pixmap* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Pixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->desaturate();
}

SIMPLE_BLOCK(fltk_fl_pixmap_draw)
{
    Fl_Pixmap* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Pixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    point1->draw(num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_pixmap_draw_1)
{
    Fl_Pixmap* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Pixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->draw(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_pixmap_label)
{
    Fl_Pixmap* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Pixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->label(point2);
}

SIMPLE_BLOCK(fltk_fl_pixmap_label_1)
{
    Fl_Pixmap* point1;
    Fl_Menu_Item* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Pixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Menu_Item*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->label(point2);
}

SIMPLE_BLOCK(fltk_fl_pixmap_uncache)
{
    Fl_Pixmap* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Pixmap*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->uncache();
}

/* Fl_Plugin */
SIMPLE_BLOCK(fltk_fl_plugin_Fl_Plugin)
{
    const char* str2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str2 = (const char*)  SIMPLE_API_GETSTRING(1);
    str3 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(new Fl_Plugin(str2,str3),"SMOOTHC_FLTK");
}

/* Fl_Plugin_Manager */
SIMPLE_BLOCK(fltk_fl_plugin_manager_Fl_Plugin_Manager)
{
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str2 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETCPOINTER(new Fl_Plugin_Manager(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_plugin_manager_plugins)
{
    Fl_Plugin_Manager* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Plugin_Manager*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->plugins());
}

SIMPLE_BLOCK(fltk_fl_plugin_manager_plugin)
{
    Fl_Plugin_Manager* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Plugin_Manager*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->plugin(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_plugin_manager_plugin_1)
{
    Fl_Plugin_Manager* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Plugin_Manager*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->plugin(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_plugin_manager_Fl_Plugin_Manager_removePlugin)
{
    Fl_Preferences::ID point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Preferences::ID) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl_Plugin_Manager::removePlugin(point1);
}

SIMPLE_BLOCK(fltk_fl_plugin_manager_Fl_Plugin_Manager_load)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETNUMBER(Fl_Plugin_Manager::load(str1));
}

SIMPLE_BLOCK(fltk_fl_plugin_manager_Fl_Plugin_Manager_loadAll)
{
    const char* str1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(Fl_Plugin_Manager::loadAll(str1,str2));
}

/* Fl_PNG_Image */
#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_png_image_Fl_PNG_Image)
{
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str2 = (const char*)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETCPOINTER(new Fl_PNG_Image(str2),"SMOOTHC_FLTK");
}

/* Fl_PNM_Image */
SIMPLE_BLOCK(fltk_fl_pnm_image_Fl_PNM_Image)
{
	const char* str2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	str2 = (const char*)  SIMPLE_API_GETSTRING(1);
	SIMPLE_API_RETCPOINTER(new Fl_PNM_Image(str2),"SMOOTHC_FLTK");
}
#endif

/* Fl_Positioner */
SIMPLE_BLOCK(fltk_fl_positioner_handle)
{
    Fl_Positioner* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_positioner_Fl_Positioner)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Positioner(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_positioner_xvalue)
{
    Fl_Positioner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->xvalue());
}

SIMPLE_BLOCK(fltk_fl_positioner_yvalue)
{
    Fl_Positioner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->yvalue());
}

SIMPLE_BLOCK(fltk_fl_positioner_xvalue_1)
{
    Fl_Positioner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->xvalue(num2));
}

SIMPLE_BLOCK(fltk_fl_positioner_yvalue_1)
{
    Fl_Positioner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->yvalue(num2));
}

SIMPLE_BLOCK(fltk_fl_positioner_value)
{
    Fl_Positioner* point1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->value(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_positioner_xbounds)
{
    Fl_Positioner* point1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point1->xbounds(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_positioner_xminimum)
{
    Fl_Positioner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->xminimum());
}

SIMPLE_BLOCK(fltk_fl_positioner_xminimum_1)
{
    Fl_Positioner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->xminimum(num2);
}

SIMPLE_BLOCK(fltk_fl_positioner_xmaximum)
{
    Fl_Positioner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->xmaximum());
}

SIMPLE_BLOCK(fltk_fl_positioner_xmaximum_1)
{
    Fl_Positioner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->xmaximum(num2);
}

SIMPLE_BLOCK(fltk_fl_positioner_ybounds)
{
    Fl_Positioner* point1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point1->ybounds(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_positioner_yminimum)
{
    Fl_Positioner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->yminimum());
}

SIMPLE_BLOCK(fltk_fl_positioner_yminimum_1)
{
    Fl_Positioner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->yminimum(num2);
}

SIMPLE_BLOCK(fltk_fl_positioner_ymaximum)
{
    Fl_Positioner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->ymaximum());
}

SIMPLE_BLOCK(fltk_fl_positioner_ymaximum_1)
{
    Fl_Positioner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->ymaximum(num2);
}

SIMPLE_BLOCK(fltk_fl_positioner_xstep)
{
    Fl_Positioner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->xstep(num2);
}

SIMPLE_BLOCK(fltk_fl_positioner_ystep)
{
    Fl_Positioner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Positioner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->ystep(num2);
}

/* Fl_Progress */
SIMPLE_BLOCK(fltk_fl_progress_Fl_Progress)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Progress(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_progress_maximum)
{
    Fl_Progress* point1;
    float num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Progress*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (float) (float) SIMPLE_API_GETNUMBER(2);
    point1->maximum(num2);
}

SIMPLE_BLOCK(fltk_fl_progress_maximum_1)
{
    Fl_Progress* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Progress*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->maximum());
}

SIMPLE_BLOCK(fltk_fl_progress_minimum)
{
    Fl_Progress* point1;
    float num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Progress*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (float) (float) SIMPLE_API_GETNUMBER(2);
    point1->minimum(num2);
}

SIMPLE_BLOCK(fltk_fl_progress_minimum_1)
{
    Fl_Progress* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Progress*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->minimum());
}

SIMPLE_BLOCK(fltk_fl_progress_value)
{
    Fl_Progress* point1;
    float num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Progress*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (float) (float) SIMPLE_API_GETNUMBER(2);
    point1->value(num2);
}

/* Fl_Radio_Button */
SIMPLE_BLOCK(fltk_fl_radio_button_Fl_Radio_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Radio_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Radio_Light_Button */
SIMPLE_BLOCK(fltk_fl_radio_light_button_Fl_Radio_Light_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Radio_Light_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Radio_Round_Button */
SIMPLE_BLOCK(fltk_fl_radio_round_button_Fl_Radio_Round_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Radio_Round_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Repeat_Button */
SIMPLE_BLOCK(fltk_fl_repeat_button_handle)
{
    Fl_Repeat_Button* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Repeat_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_repeat_button_Fl_Repeat_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Repeat_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_repeat_button_deactivate)
{
    Fl_Repeat_Button* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Repeat_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->deactivate();
}

/* Fl_Return_Button */
SIMPLE_BLOCK(fltk_fl_return_button_handle_1)
{
    Fl_Return_Button* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Return_Button*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_return_button_Fl_Return_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Return_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Roller */
SIMPLE_BLOCK(fltk_fl_roller_handle_2)
{
    Fl_Roller* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Roller*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_roller_Fl_Roller)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Roller(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Round_Button */
SIMPLE_BLOCK(fltk_fl_round_button_Fl_Round_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Round_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Round_Clock */
SIMPLE_BLOCK(fltk_fl_round_clock_Fl_Round_Clock)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Round_Clock(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}
SIMPLE_BLOCK(fltk_fl_progress_value_1)
{
    Fl_Progress* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Progress*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->value());
}

/* Fl_Scroll */
SIMPLE_BLOCK(fltk_fl_scroll_resize)
{
    Fl_Scroll* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Scroll*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_scroll_handle)
{
    Fl_Scroll* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Scroll*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_scroll_HORIZONTAL)
{
    SIMPLE_API_RETNUMBER(Fl_Scroll::HORIZONTAL);
}

SIMPLE_BLOCK(fltk_fl_scroll_VERTICAL)
{
    SIMPLE_API_RETNUMBER(Fl_Scroll::VERTICAL);
}

SIMPLE_BLOCK(fltk_fl_scroll_BOTH)
{
    SIMPLE_API_RETNUMBER(Fl_Scroll::BOTH);
}

SIMPLE_BLOCK(fltk_fl_scroll_ALWAYS_ON)
{
    SIMPLE_API_RETNUMBER(Fl_Scroll::ALWAYS_ON);
}

SIMPLE_BLOCK(fltk_fl_scroll_HORIZONTAL_ALWAYS)
{
    SIMPLE_API_RETNUMBER(Fl_Scroll::HORIZONTAL_ALWAYS);
}

SIMPLE_BLOCK(fltk_fl_scroll_VERTICAL_ALWAYS)
{
    SIMPLE_API_RETNUMBER(Fl_Scroll::VERTICAL_ALWAYS);
}

SIMPLE_BLOCK(fltk_fl_scroll_BOTH_ALWAYS)
{
    SIMPLE_API_RETNUMBER(Fl_Scroll::BOTH_ALWAYS);
}

SIMPLE_BLOCK(fltk_fl_scroll_xposition)
{
    Fl_Scroll* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Scroll*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->xposition(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_scroll_yposition)
{
    Fl_Scroll* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Scroll*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->yposition(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_scroll_scroll_to)
{
    Fl_Scroll* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Scroll*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->scroll_to(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_scroll_clear)
{
    Fl_Scroll* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Scroll*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_scroll_scrollbar_size)
{
    Fl_Scroll* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Scroll*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->scrollbar_size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_scroll_scrollbar_size_1)
{
    Fl_Scroll* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Scroll*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->scrollbar_size(num2);
}

/* Fl_Scrollbar */
SIMPLE_BLOCK(fltk_fl_scrollbar_Fl_Scrollbar)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Scrollbar(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_scrollbar_handle_1)
{
    Fl_Scrollbar* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Scrollbar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_scrollbar_value)
{
    Fl_Scrollbar* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Scrollbar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_scrollbar_value_1)
{
    Fl_Scrollbar* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Scrollbar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->value(num2));
}

SIMPLE_BLOCK(fltk_fl_scrollbar_value_2)
{
    Fl_Scrollbar* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Scrollbar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    SIMPLE_API_RETNUMBER(point1->value(num2,num3,num4,num5));
}

SIMPLE_BLOCK(fltk_fl_scrollbar_linesize)
{
    Fl_Scrollbar* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Scrollbar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linesize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_scrollbar_linesize_1)
{
    Fl_Scrollbar* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Scrollbar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->linesize(num2);
}

/* Fl_Secret_Input */
SIMPLE_BLOCK(fltk_fl_secret_input_Fl_Secret_Input)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Secret_Input(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Secret_Input */
SIMPLE_BLOCK(fltk_fl_secret_input_handle_2)
{
    Fl_Secret_Input* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Secret_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_select_browser_Fl_Select_Browser)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Select_Browser(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Shared_Image */
SIMPLE_BLOCK(fltk_fl_shared_image_name)
{
    Fl_Shared_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->name());
}

SIMPLE_BLOCK(fltk_fl_shared_image_refcount)
{
    Fl_Shared_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->refcount());
}

SIMPLE_BLOCK(fltk_fl_shared_image_release)
{
    Fl_Shared_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->release();
}

SIMPLE_BLOCK(fltk_fl_shared_image_reload)
{
    Fl_Shared_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->reload();
}

SIMPLE_BLOCK(fltk_fl_shared_image_copy)
{
    Fl_Shared_Image* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->copy(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_shared_image_copy_1)
{
    Fl_Shared_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->copy(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_shared_image_color_average)
{
    Fl_Shared_Image* point1;
    Fl_Color num2;
    float num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (float) (float) SIMPLE_API_GETNUMBER(3);
    point1->color_average(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_shared_image_desaturate)
{
    Fl_Shared_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->desaturate();
}

SIMPLE_BLOCK(fltk_fl_shared_image_draw)
{
    Fl_Shared_Image* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    point1->draw(num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_shared_image_draw_1)
{
    Fl_Shared_Image* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->draw(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_shared_image_scale)
{
    Fl_Shared_Image* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->scale(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_shared_image_uncache)
{
    Fl_Shared_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Shared_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->uncache();
}

SIMPLE_BLOCK(fltk_fl_shared_image_Fl_Shared_Image_find)
{
    const char* str1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(Fl_Shared_Image::find(str1,num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_shared_image_Fl_Shared_Image_get)
{
    const char* str1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(Fl_Shared_Image::get(str1,num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_shared_image_Fl_Shared_Image_get_1)
{
    Fl_RGB_Image * point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_RGB_Image *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(Fl_Shared_Image::get(point1,num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_shared_image_Fl_Shared_Image_images)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl_Shared_Image::images(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_shared_image_Fl_Shared_Image_num_images)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Shared_Image::num_images());
}

SIMPLE_BLOCK(fltk_fl_shared_image_Fl_Shared_Image_add_handler)
{
    Fl_Shared_Handler point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Shared_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl_Shared_Image::add_handler(point1);
}

SIMPLE_BLOCK(fltk_fl_shared_image_Fl_Shared_Image_remove_handler)
{
    Fl_Shared_Handler point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Shared_Handler) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl_Shared_Image::remove_handler(point1);
}

SIMPLE_BLOCK(fltk_fl_shared_image_Fl_Shared_Image_scaling_algorithm)
{
    Fl_RGB_Scaling* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_RGB_Scaling*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl_Shared_Image::scaling_algorithm(*point1);
}

SIMPLE_BLOCK(fltk_fl_show_colormap)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(fl_show_colormap(num1));
}

/* Fl_Simple_Counter */
SIMPLE_BLOCK(fltk_fl_simple_counter_Fl_Simple_Counter)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Simple_Counter(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Single_Window */
SIMPLE_BLOCK(fltk_fl_single_window_show)
{
    Fl_Single_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Single_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show();
}

SIMPLE_BLOCK(fltk_fl_single_window_show_1)
{
    Fl_Single_Window* point1;
    int num2;
    char* * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Single_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (char* *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->show(num2,point3);
}

SIMPLE_BLOCK(fltk_fl_single_window_Fl_Single_Window)
{
    int num2;
    int num3;
    const char* str4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str4 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETCPOINTER(new Fl_Single_Window(num2,num3,str4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_single_window_Fl_Single_Window_1)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Single_Window(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

#ifdef Fl_Single_Window::make_current
SIMPLE_BLOCK(fltk_fl_single_window_make_current)
{
	Fl_Single_Window* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Single_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->make_current());
}
#endif

/* Fl_Slider */
SIMPLE_BLOCK(fltk_fl_slider_handle_3)
{
    Fl_Slider* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_slider_Fl_Slider)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Slider(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_slider_Fl_Slider_1)
{
    uchar num2;
    int num3;
    int num4;
    int num5;
    int num6;
    const char* str7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    num2 = (uchar) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str7 = (const char*)  SIMPLE_API_GETSTRING(6);
    SIMPLE_API_RETCPOINTER(new Fl_Slider(num2,num3,num4,num5,num6,str7),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_slider_scrollvalue)
{
    Fl_Slider* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    SIMPLE_API_RETNUMBER(point1->scrollvalue(num2,num3,num4,num5));
}

SIMPLE_BLOCK(fltk_fl_slider_bounds)
{
    Fl_Slider* point1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point1->bounds(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_slider_slider_size)
{
    Fl_Slider* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->slider_size());
}

SIMPLE_BLOCK(fltk_fl_slider_slider_size_1)
{
    Fl_Slider* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->slider_size(num2);
}

SIMPLE_BLOCK(fltk_fl_slider_slider)
{
    Fl_Slider* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->slider(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_slider_slider_1)
{
    Fl_Slider* point1;
    Fl_Boxtype point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(2);
    point1->slider(point2);
}

/* Fl_Spinner */
SIMPLE_BLOCK(fltk_fl_spinner_Fl_Spinner)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Spinner(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_spinner_format)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->format());
}

SIMPLE_BLOCK(fltk_fl_spinner_format_1)
{
    Fl_Spinner* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->format(str2);
}

SIMPLE_BLOCK(fltk_fl_spinner_handle_4)
{
    Fl_Spinner* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_spinner_maxinum)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
#ifndef __ANDROID__
    SIMPLE_API_RETNUMBER(point1->maxinum());
#else
    SIMPLE_API_RETNUMBER(point1->maximum());
#endif
}

SIMPLE_BLOCK(fltk_fl_spinner_maximum)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->maximum());
}

SIMPLE_BLOCK(fltk_fl_spinner_maximum_1)
{
    Fl_Spinner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->maximum(num2);
}

SIMPLE_BLOCK(fltk_fl_spinner_mininum)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
#ifndef __ANDROID__
    SIMPLE_API_RETNUMBER(point1->mininum());
#else
    SIMPLE_API_RETNUMBER(point1->minimum());
#endif
}

SIMPLE_BLOCK(fltk_fl_spinner_minimum)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->minimum());
}

SIMPLE_BLOCK(fltk_fl_spinner_minimum_1)
{
    Fl_Spinner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->minimum(num2);
}

SIMPLE_BLOCK(fltk_fl_spinner_range)
{
    Fl_Spinner* point1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point1->range(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_spinner_resize_1)
{
    Fl_Spinner* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_spinner_step)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->step());
}

SIMPLE_BLOCK(fltk_fl_spinner_step_1)
{
    Fl_Spinner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->step(num2);
}

SIMPLE_BLOCK(fltk_fl_spinner_textcolor)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_spinner_textcolor_1)
{
    Fl_Spinner* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_spinner_textfont)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_spinner_textfont_1)
{
    Fl_Spinner* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_spinner_textsize)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_spinner_textsize_1)
{
    Fl_Spinner* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_spinner_type)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->type(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_spinner_type_1)
{
    Fl_Spinner* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->type(num2);
}

SIMPLE_BLOCK(fltk_fl_spinner_value_3)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->value());
}

SIMPLE_BLOCK(fltk_fl_spinner_value_4)
{
    Fl_Spinner* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->value(num2);
}

SIMPLE_BLOCK(fltk_fl_spinner_color)
{
    Fl_Spinner* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->color(num2);
}

SIMPLE_BLOCK(fltk_fl_spinner_color_1)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->color(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_spinner_selection_color)
{
    Fl_Spinner* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->selection_color(num2);
}

SIMPLE_BLOCK(fltk_fl_spinner_selection_color_1)
{
    Fl_Spinner* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Spinner*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->selection_color(),"SMOOTHC_FLTK");
}

/* Fl_Sys_Menu_Bar */
SIMPLE_BLOCK(fltk_fl_sys_menu_bar_Fl_Sys_Menu_Bar)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Sys_Menu_Bar(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_menu)
{
    Fl_Sys_Menu_Bar* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->menu(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_menu_1)
{
    Fl_Sys_Menu_Bar* point1;
    const Fl_Menu_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Menu_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->menu(point2);
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_add)
{
    Fl_Sys_Menu_Bar* point1;
    const char* str2;
    int num3;
    Fl_Callback* point4;
    void* point5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point4 = (Fl_Callback*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (void*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    SIMPLE_API_RETNUMBER(point1->add(str2,num3,point4,point5,num6));
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_add_1)
{
    Fl_Sys_Menu_Bar* point1;
    const char* str2;
    const char* str3;
    Fl_Callback* point4;
    void* point5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point4 = (Fl_Callback*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (void*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    SIMPLE_API_RETNUMBER(point1->add(str2,str3,point4,point5,num6));
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_add_2)
{
    Fl_Sys_Menu_Bar* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->add(str2));
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_insert)
{
    Fl_Sys_Menu_Bar* point1;
    int num2;
    const char* str3;
    int num4;
    Fl_Callback * point5;
    void* point6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point5 = (Fl_Callback *) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    point6 = (void*) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    SIMPLE_API_RETNUMBER(point1->insert(num2,str3,num4,point5,point6,num7));
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_insert_1)
{
    Fl_Sys_Menu_Bar* point1;
    int num2;
    const char* str3;
    const char* str4;
    Fl_Callback * point5;
    void* point6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    point5 = (Fl_Callback *) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    point6 = (void*) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    SIMPLE_API_RETNUMBER(point1->insert(num2,str3,str4,point5,point6,num7));
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_remove)
{
    Fl_Sys_Menu_Bar* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->remove(num2);
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_replace)
{
    Fl_Sys_Menu_Bar* point1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point1->replace(num2,str3);
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_clear_1)
{
    Fl_Sys_Menu_Bar* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_clear_submenu)
{
    Fl_Sys_Menu_Bar* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->clear_submenu(num2));
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_global)
{
    Fl_Sys_Menu_Bar* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->global();
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_mode)
{
    Fl_Sys_Menu_Bar* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Sys_Menu_Bar*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->mode(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_sys_menu_bar_Fl_Sys_Menu_Bar_1)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Sys_Menu_Bar(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Tabs */

SIMPLE_BLOCK(fltk_fl_tabs_handle)
{
    Fl_Tabs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tabs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_tabs_value)
{
    Fl_Tabs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tabs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tabs_value_1)
{
    Fl_Tabs* point1;
    Fl_Widget * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tabs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->value(point2));
}

SIMPLE_BLOCK(fltk_fl_tabs_push)
{
    Fl_Tabs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tabs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->push(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tabs_push_1)
{
    Fl_Tabs* point1;
    Fl_Widget * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tabs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->push(point2));
}

SIMPLE_BLOCK(fltk_fl_tabs_Fl_Tabs)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Tabs(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tabs_which)
{
    Fl_Tabs* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tabs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->which(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tabs_client_area)
{
    Fl_Tabs* point1;
    int * point2;
    int * point3;
    int * point4;
    int * point5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Tabs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (int *) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    point1->client_area(*point2,*point3,*point4,*point5,num6);
}

/* Fl_Text_Selection */
SIMPLE_BLOCK(fltk_fl_text_selection_set)
{
    Fl_Text_Selection* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Selection*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->set(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_text_selection_update)
{
    Fl_Text_Selection* point1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Selection*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->update(num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_text_selection_start)
{
    Fl_Text_Selection* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Selection*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->start(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_selection_end)
{
    Fl_Text_Selection* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Selection*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->end(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_selection_selected)
{
    Fl_Text_Selection* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Selection*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->selected(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_selection_selected_1)
{
    Fl_Text_Selection* point1;
    bool num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Selection*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (bool) (int) SIMPLE_API_GETNUMBER(2);
    point1->selected(num2);
}

SIMPLE_BLOCK(fltk_fl_text_selection_includes)
{
    Fl_Text_Selection* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Selection*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->includes(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_selection_position)
{
    Fl_Text_Selection* point1;
    int* point2;
    int* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Selection*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->position(point2,point3),"SMOOTHC_FLTK");
}

/* Fl_Text_Buffer */
SIMPLE_BLOCK(fltk_fl_text_buffer_Fl_Text_Buffer)
{
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(new Fl_Text_Buffer(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_length)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->length(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_text)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->text());
}

SIMPLE_BLOCK(fltk_fl_text_buffer_text_1)
{
    Fl_Text_Buffer* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->text(str2);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_text_range)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETSTRING(point1->text_range(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_char_at)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->char_at(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_byte_at)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->byte_at(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_address)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->address(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_address_1)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETSTRING(point1->address(num2));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_insert)
{
    Fl_Text_Buffer* point1;
    int num2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point1->insert(num2,str3);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_append)
{
    Fl_Text_Buffer* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->append(str2);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_remove)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->remove(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_replace)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    const char* str4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    str4 = (const char*)  SIMPLE_API_GETSTRING(4);
    point1->replace(num2,num3,str4);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_copy)
{
    Fl_Text_Buffer* point1;
    Fl_Text_Buffer* point2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->copy(point2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_undo)
{
    Fl_Text_Buffer* point1;
    int * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->undo(point2));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_canUndo)
{
    Fl_Text_Buffer* point1;
    char num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (char) (char) SIMPLE_API_GETNUMBER(2);
    point1->canUndo(num2);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_insertfile)
{
    Fl_Text_Buffer* point1;
    const char* str2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETNUMBER(point1->insertfile(str2,num3,num4));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_appendfile)
{
    Fl_Text_Buffer* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->appendfile(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_loadfile)
{
    Fl_Text_Buffer* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->loadfile(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_outputfile)
{
    Fl_Text_Buffer* point1;
    const char* str2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    SIMPLE_API_RETNUMBER(point1->outputfile(str2,num3,num4,num5));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_savefile)
{
    Fl_Text_Buffer* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->savefile(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_tab_distance)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->tab_distance(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_tab_distance_1)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->tab_distance(num2);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_select)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->select(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_selected)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->selected(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_unselect)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->unselect();
}

SIMPLE_BLOCK(fltk_fl_text_buffer_selection_position)
{
    Fl_Text_Buffer* point1;
    int* point2;
    int* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->selection_position(point2,point3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_selection_text)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->selection_text());
}

SIMPLE_BLOCK(fltk_fl_text_buffer_remove_selection)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->remove_selection();
}

SIMPLE_BLOCK(fltk_fl_text_buffer_replace_selection)
{
    Fl_Text_Buffer* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->replace_selection(str2);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_secondary_select)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->secondary_select(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_secondary_selected)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->secondary_selected());
}

SIMPLE_BLOCK(fltk_fl_text_buffer_secondary_unselect)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->secondary_unselect();
}

SIMPLE_BLOCK(fltk_fl_text_buffer_secondary_selection_position)
{
    Fl_Text_Buffer* point1;
    int* point2;
    int* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->secondary_selection_position(point2,point3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_secondary_selection_text)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->secondary_selection_text());
}

SIMPLE_BLOCK(fltk_fl_text_buffer_remove_secondary_selection)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->remove_secondary_selection();
}

SIMPLE_BLOCK(fltk_fl_text_buffer_replace_secondary_selection)
{
    Fl_Text_Buffer* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->replace_secondary_selection(str2);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_highlight)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->highlight(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_highlight_1)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->highlight());
}

SIMPLE_BLOCK(fltk_fl_text_buffer_unhighlight)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->unhighlight();
}

SIMPLE_BLOCK(fltk_fl_text_buffer_highlight_position)
{
    Fl_Text_Buffer* point1;
    int* point2;
    int* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->highlight_position(point2,point3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_highlight_text)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->highlight_text());
}

SIMPLE_BLOCK(fltk_fl_text_buffer_add_modify_callback)
{
    Fl_Text_Buffer* point1;
    Fl_Text_Modify_Cb point2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Modify_Cb) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->add_modify_callback(point2,point3);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_remove_modify_callback)
{
    Fl_Text_Buffer* point1;
    Fl_Text_Modify_Cb point2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Modify_Cb) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->remove_modify_callback(point2,point3);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_call_modify_callbacks)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->call_modify_callbacks();
}

SIMPLE_BLOCK(fltk_fl_text_buffer_add_predelete_callback)
{
    Fl_Text_Buffer* point1;
    Fl_Text_Predelete_Cb point2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Predelete_Cb) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->add_predelete_callback(point2,point3);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_remove_predelete_callback)
{
    Fl_Text_Buffer* point1;
    Fl_Text_Predelete_Cb point2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Predelete_Cb) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->remove_predelete_callback(point2,point3);
}

SIMPLE_BLOCK(fltk_fl_text_buffer_call_predelete_callbacks)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->call_predelete_callbacks();
}

SIMPLE_BLOCK(fltk_fl_text_buffer_line_text)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETSTRING(point1->line_text(num2));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_line_start)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->line_start(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_line_end)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->line_end(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_word_start)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->word_start(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_word_end)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->word_end(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_count_displayed_characters)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->count_displayed_characters(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_skip_displayed_characters)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->skip_displayed_characters(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_count_lines)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->count_lines(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_skip_lines)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->skip_lines(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_rewind_lines)
{
    Fl_Text_Buffer* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->rewind_lines(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_text_buffer_findchar_forward)
{
    Fl_Text_Buffer* point1;
    int num2;
    unsigned num3;
    int* point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (unsigned) (int) SIMPLE_API_GETNUMBER(3);
    point4 = (int*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->findchar_forward(num2,num3,point4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_findchar_backward)
{
    Fl_Text_Buffer* point1;
    int num2;
    unsigned int num3;
    int* point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (unsigned int) (unsigned int) SIMPLE_API_GETNUMBER(3);
    point4 = (int*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->findchar_backward(num2,num3,point4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_primary_selection)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->primary_selection(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_primary_selection_1)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->primary_selection(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_secondary_selection)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->secondary_selection(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_highlight_selection)
{
    Fl_Text_Buffer* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->highlight_selection(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_prev_char)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->prev_char(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_prev_char_clipped)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->prev_char_clipped(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_next_char)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->next_char(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_next_char_clipped)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->next_char_clipped(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_utf8_align)
{
    Fl_Text_Buffer* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->utf8_align(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_buffer_Fl_Text_Buffer_file_encoding_warning_message)
{
    SIMPLE_API_RETSTRING(Fl_Text_Buffer::file_encoding_warning_message);
}

/* Fl_Text_Display */
SIMPLE_BLOCK(fltk_fl_text_display_NORMAL_CURSOR)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::NORMAL_CURSOR);
}

SIMPLE_BLOCK(fltk_fl_text_display_CARET_CURSOR)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::CARET_CURSOR);
}

SIMPLE_BLOCK(fltk_fl_text_display_DIM_CURSOR)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::DIM_CURSOR);
}

SIMPLE_BLOCK(fltk_fl_text_display_BLOCK_CURSOR)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::BLOCK_CURSOR);
}

SIMPLE_BLOCK(fltk_fl_text_display_HEAVY_CURSOR)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::HEAVY_CURSOR);
}

SIMPLE_BLOCK(fltk_fl_text_display_CURSOR_POS)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::CURSOR_POS);
}

SIMPLE_BLOCK(fltk_fl_text_display_DRAG_NONE)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::DRAG_NONE);
}

SIMPLE_BLOCK(fltk_fl_text_display_DRAG_START_DND)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::DRAG_START_DND);
}

SIMPLE_BLOCK(fltk_fl_text_display_DRAG_CHAR)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::DRAG_CHAR);
}

SIMPLE_BLOCK(fltk_fl_text_display_DRAG_WORD)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::DRAG_WORD);
}

SIMPLE_BLOCK(fltk_fl_text_display_DRAG_LINE)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::DRAG_LINE);
}

SIMPLE_BLOCK(fltk_fl_text_display_WRAP_NONE)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::WRAP_NONE);
}

SIMPLE_BLOCK(fltk_fl_text_display_WRAP_AT_COLUMN)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::WRAP_AT_COLUMN);
}

SIMPLE_BLOCK(fltk_fl_text_display_WRAP_AT_PIXEL)
{
    SIMPLE_API_RETNUMBER(Fl_Text_Display::WRAP_AT_PIXEL);
}

#ifdef Fl_Text_Display::fl_text_drag_me
SIMPLE_BLOCK(fltk_fl_text_display_fl_text_drag_me)
{
	Fl_Text_Display* point1;
	int num2;
	Fl_Text_Display* point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point3 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	point1->fl_text_drag_me(num2,point3);
}
#endif

SIMPLE_BLOCK(fltk_fl_text_display_handle_1)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_text_display_buffer)
{
    Fl_Text_Display* point1;
    Fl_Text_Buffer* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->buffer(point2);
}

SIMPLE_BLOCK(fltk_fl_text_display_buffer_1)
{
    Fl_Text_Display* point1;
    Fl_Text_Buffer* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Buffer*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->buffer(*point2);
}

SIMPLE_BLOCK(fltk_fl_text_display_buffer_2)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->buffer(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_redisplay_range)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->redisplay_range(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_text_display_scroll)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->scroll(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_text_display_insert)
{
    Fl_Text_Display* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->insert(str2);
}

SIMPLE_BLOCK(fltk_fl_text_display_overstrike)
{
    Fl_Text_Display* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->overstrike(str2);
}

SIMPLE_BLOCK(fltk_fl_text_display_insert_position)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->insert_position(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_insert_position_1)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->insert_position(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_position_to_xy)
{
    Fl_Text_Display* point1;
    int num2;
    int* point3;
    int* point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (int*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->position_to_xy(num2,point3,point4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_in_selection)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->in_selection(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_show_insert_position)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show_insert_position();
}

SIMPLE_BLOCK(fltk_fl_text_display_move_right)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->move_right());
}

SIMPLE_BLOCK(fltk_fl_text_display_move_left)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->move_left());
}

SIMPLE_BLOCK(fltk_fl_text_display_move_up)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->move_up());
}

SIMPLE_BLOCK(fltk_fl_text_display_move_down)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->move_down());
}

SIMPLE_BLOCK(fltk_fl_text_display_count_lines)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    bool num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (bool) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETCPOINTER(point1->count_lines(num2,num3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_line_start)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->line_start(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_line_end)
{
    Fl_Text_Display* point1;
    int num2;
    bool num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (bool) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->line_end(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_skip_lines)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    bool num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (bool) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETNUMBER(point1->skip_lines(num2,num3,num4));
}

SIMPLE_BLOCK(fltk_fl_text_display_rewind_lines)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->rewind_lines(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_text_display_next_word)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->next_word();
}

SIMPLE_BLOCK(fltk_fl_text_display_previous_word)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->previous_word();
}

SIMPLE_BLOCK(fltk_fl_text_display_show_cursor)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->show_cursor(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_hide_cursor)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->hide_cursor();
}

SIMPLE_BLOCK(fltk_fl_text_display_cursor_style)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->cursor_style(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_cursor_color)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->cursor_color());
}

SIMPLE_BLOCK(fltk_fl_text_display_cursor_color_1)
{
    Fl_Text_Display* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->cursor_color(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_scrollbar_width)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->scrollbar_width(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_scrollbar_width_1)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->scrollbar_width(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_scrollbar_align)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->scrollbar_align(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_scrollbar_align_1)
{
    Fl_Text_Display* point1;
    Fl_Align point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Align) (int) SIMPLE_API_GETNUMBER(2);
    point1->scrollbar_align(point2);
}

SIMPLE_BLOCK(fltk_fl_text_display_word_start)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->word_start(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_word_end)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->word_end(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_highlight_data)
{
    Fl_Text_Display* point1;
    Fl_Text_Buffer * point2;
    const Fl_Text_Display::Style_Table_Entry * point3;
    int num4;
    char num5;
    Fl_Text_Display::Unfinished_Style_Cb point6;
    void* point7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Buffer *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (const Fl_Text_Display::Style_Table_Entry *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (char) (char) SIMPLE_API_GETNUMBER(5);
    point6 = (Fl_Text_Display::Unfinished_Style_Cb) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
    point7 = (void*) SIMPLE_API_GETCPOINTER(7,"SMOOTHC_FLTK");
    point1->highlight_data(point2,point3,num4,num5,point6,point7);
}

SIMPLE_BLOCK(fltk_fl_text_display_position_style)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETCPOINTER(point1->position_style(num2,num3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_shortcut)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->shortcut(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_shortcut_1)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->shortcut(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_textfont)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_textfont_1)
{
    Fl_Text_Display* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_text_display_textsize)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_textsize_1)
{
    Fl_Text_Display* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_text_display_textcolor)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_textcolor_1)
{
    Fl_Text_Display* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_wrapped_column)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->wrapped_column(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_wrapped_row)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->wrapped_row(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_wrap_mode)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->wrap_mode(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_text_display_resize)
{
    Fl_Text_Display* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_text_display_x_to_col)
{
    Fl_Text_Display* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->x_to_col(num2));
}

SIMPLE_BLOCK(fltk_fl_text_display_col_to_x)
{
    Fl_Text_Display* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->col_to_x(num2));
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_width)
{
    Fl_Text_Display* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->linenumber_width(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_width_1)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linenumber_width(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_font)
{
    Fl_Text_Display* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->linenumber_font(point2);
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_font_1)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linenumber_font(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_size)
{
    Fl_Text_Display* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->linenumber_size(point2);
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_size_1)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linenumber_size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_fgcolor)
{
    Fl_Text_Display* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->linenumber_fgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_fgcolor_1)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linenumber_fgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_bgcolor)
{
    Fl_Text_Display* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->linenumber_bgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_bgcolor_1)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linenumber_bgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_align)
{
    Fl_Text_Display* point1;
    Fl_Align point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Align) (int) SIMPLE_API_GETNUMBER(2);
    point1->linenumber_align(point2);
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_align_1)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linenumber_align(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_format)
{
    Fl_Text_Display* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->linenumber_format(str2);
}

SIMPLE_BLOCK(fltk_fl_text_display_linenumber_format_1)
{
    Fl_Text_Display* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Display*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linenumber_format(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Text_Editor(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_editor_handle_2)
{
    Fl_Text_Editor* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_insert_mode)
{
    Fl_Text_Editor* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->insert_mode(num2);
}

SIMPLE_BLOCK(fltk_fl_text_editor_insert_mode_1)
{
    Fl_Text_Editor* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->insert_mode());
}

#if FLTK_ABI_VERSION >= 10304
SIMPLE_BLOCK(fltk_fl_text_editor_tab_nav)
{
	Fl_Text_Editor* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point1->tab_nav(num2);
}

SIMPLE_BLOCK(fltk_fl_text_editor_tab_nav_1)
{
	Fl_Text_Editor* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->tab_nav());
}
#endif

SIMPLE_BLOCK(fltk_fl_text_editor_add_key_binding)
{
    Fl_Text_Editor* point1;
    int num2;
    int num3;
    Fl_Text_Editor::Key_Func point4;
    Fl_Text_Editor::Key_Binding** point5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point4 = (Fl_Text_Editor::Key_Func) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point5 = (Fl_Text_Editor::Key_Binding**) SIMPLE_API_GETCPOINTER2POINTER(5,"SMOOTHC_FLTK");
    point1->add_key_binding(num2,num3,point4,point5);
}

SIMPLE_BLOCK(fltk_fl_text_editor_add_key_binding_1)
{
    Fl_Text_Editor* point1;
    int num2;
    int num3;
    Fl_Text_Editor::Key_Func point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point4 = (Fl_Text_Editor::Key_Func) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    point1->add_key_binding(num2,num3,point4);
}

SIMPLE_BLOCK(fltk_fl_text_editor_remove_key_binding)
{
    Fl_Text_Editor* point1;
    int num2;
    int num3;
    Fl_Text_Editor::Key_Binding** point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point4 = (Fl_Text_Editor::Key_Binding**) SIMPLE_API_GETCPOINTER2POINTER(4,"SMOOTHC_FLTK");
    point1->remove_key_binding(num2,num3,point4);
}

SIMPLE_BLOCK(fltk_fl_text_editor_remove_key_binding_1)
{
    Fl_Text_Editor* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->remove_key_binding(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_text_editor_remove_all_key_bindings)
{
    Fl_Text_Editor* point1;
    Fl_Text_Editor::Key_Binding** point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Editor::Key_Binding**) SIMPLE_API_GETCPOINTER2POINTER(2,"SMOOTHC_FLTK");
    point1->remove_all_key_bindings(point2);
}

SIMPLE_BLOCK(fltk_fl_text_editor_remove_all_key_bindings_1)
{
    Fl_Text_Editor* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->remove_all_key_bindings();
}

SIMPLE_BLOCK(fltk_fl_text_editor_add_default_key_bindings)
{
    Fl_Text_Editor* point1;
    Fl_Text_Editor::Key_Binding** point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Editor::Key_Binding**) SIMPLE_API_GETCPOINTER2POINTER(2,"SMOOTHC_FLTK");
    point1->add_default_key_bindings(point2);
}

SIMPLE_BLOCK(fltk_fl_text_editor_bound_key_function)
{
    Fl_Text_Editor* point1;
    int num2;
    int num3;
    Fl_Text_Editor::Key_Binding* point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point4 = (Fl_Text_Editor::Key_Binding*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->bound_key_function(num2,num3,point4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_editor_bound_key_function_1)
{
    Fl_Text_Editor* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->bound_key_function(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_editor_bound_key_function_2)
{
    Fl_Text_Editor* point1;
    int num2;
    int num3;
    Fl_Text_Editor::Key_Binding* point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point4 = (Fl_Text_Editor::Key_Binding*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->bound_key_function(num2,num3,point4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_editor_bound_key_function_3)
{
    Fl_Text_Editor* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->bound_key_function(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_text_editor_default_key_function)
{
    Fl_Text_Editor* point1;
    Fl_Text_Editor::Key_Func point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Text_Editor::Key_Func) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->default_key_function(point2);
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_default)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_default(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_ignore)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_ignore(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_backspace)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_backspace(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_enter)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_enter(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_move)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_move(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_shift_move)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_shift_move(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_ctrl_move)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_ctrl_move(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_c_s_move)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_c_s_move(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_meta_move)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_meta_move(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_m_s_move)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_m_s_move(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_home)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_home(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_end)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_end(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_left)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_left(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_up)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_up(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_right)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_right(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_down)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_down(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_page_up)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_page_up(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_page_down)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_page_down(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_insert)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_insert(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_delete)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_delete(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_copy)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_copy(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_cut)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_cut(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_paste)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_paste(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_select_all)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_select_all(num1,point2));
}

SIMPLE_BLOCK(fltk_fl_text_editor_Fl_Text_Editor_kf_undo)
{
    int num1;
    Fl_Text_Editor* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (Fl_Text_Editor*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(Fl_Text_Editor::kf_undo(num1,point2));
}

/* Fl_Tile */
SIMPLE_BLOCK(fltk_fl_tile_handle)
{
    Fl_Tile* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tile*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_tile_Fl_Tile)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Tile(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tile_resize)
{
    Fl_Tile* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Tile*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_tile_position)
{
    Fl_Tile* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Tile*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->position(num2,num3,num4,num5);
}

/* Fl_Tiled_Image */
SIMPLE_BLOCK(fltk_fl_tiled_image_Fl_Tiled_Image)
{
    Fl_Image * point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point2 = (Fl_Image *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(new Fl_Tiled_Image(point2,num3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tiled_image_copy)
{
    Fl_Tiled_Image* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tiled_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->copy(num2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tiled_image_copy_1)
{
    Fl_Tiled_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tiled_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->copy(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tiled_image_color_average)
{
    Fl_Tiled_Image* point1;
    Fl_Color num2;
    float num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tiled_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (float) (float) SIMPLE_API_GETNUMBER(3);
    point1->color_average(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_tiled_image_desaturate)
{
    Fl_Tiled_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tiled_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->desaturate();
}

SIMPLE_BLOCK(fltk_fl_tiled_image_draw)
{
    Fl_Tiled_Image* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    point1 = (Fl_Tiled_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    point1->draw(num2,num3,num4,num5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_tiled_image_draw_1)
{
    Fl_Tiled_Image* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tiled_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->draw(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_tiled_image_image)
{
    Fl_Tiled_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tiled_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->image(),"SMOOTHC_FLTK");
}

/* Fl_Timer */
#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_timer_handle_1)
{
	Fl_Timer* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Timer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_timer_Fl_Timer)
{
	uchar num2;
	int num3;
	int num4;
	int num5;
	int num6;
	const char* str7;
	if ( SIMPLE_API_PARACOUNT != 7 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
		return ;
	}
	num2 = (uchar) SIMPLE_API_GETNUMBER(1);
	num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
	num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
	num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
	num6 = (int) (int) SIMPLE_API_GETNUMBER(5);
	str7 = (const char*)  SIMPLE_API_GETSTRING(6);
	SIMPLE_API_RETCPOINTER(new Fl_Timer(num2,num3,num4,num5,num6,str7),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_timer_value)
{
	Fl_Timer* point1;
	double num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Timer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
	point1->value(num2);
}

SIMPLE_BLOCK(fltk_fl_timer_value_1)
{
	Fl_Timer* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Timer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->value());
}

SIMPLE_BLOCK(fltk_fl_timer_direction)
{
	Fl_Timer* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Timer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->direction(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_timer_direction_1)
{
	Fl_Timer* point1;
	char num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Timer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (char) (char) SIMPLE_API_GETNUMBER(2);
	point1->direction(num2);
}

SIMPLE_BLOCK(fltk_fl_timer_suspended)
{
	Fl_Timer* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Timer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->suspended(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_timer_suspended_1)
{
	Fl_Timer* point1;
	char num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Timer*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (char) (char) SIMPLE_API_GETNUMBER(2);
	point1->suspended(num2);
}
#endif

/* Fl_Toggle_Button */
SIMPLE_BLOCK(fltk_fl_toggle_button_Fl_Toggle_Button)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Toggle_Button(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

/* Fl_Tooltip */
SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_delay)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::delay());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_delay_1)
{
    float num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (float) (float) SIMPLE_API_GETNUMBER(1);
    Fl_Tooltip::delay(num1);
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_hoverdelay)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::hoverdelay());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_hoverdelay_1)
{
    float num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (float) (float) SIMPLE_API_GETNUMBER(1);
    Fl_Tooltip::hoverdelay(num1);
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_enabled)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::enabled());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_enable)
{
    int num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    Fl_Tooltip::enable(num1);
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_disable)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    Fl_Tooltip::disable();
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_enter_area)
{
    Fl_Widget* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    str6 = (const char*)  SIMPLE_API_GETSTRING(6);
    Fl_Tooltip::enter_area(point1,num2,num3,num4,num5,str6);
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_current)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl_Tooltip::current(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_current_1)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl_Tooltip::current(point1);
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_font)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl_Tooltip::font(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_font_1)
{
    Fl_Font point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(1);
    Fl_Tooltip::font(point1);
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_size)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl_Tooltip::size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_size_1)
{
    Fl_Fontsize point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(1);
    Fl_Tooltip::size(point1);
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_color)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::color());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_color_1)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    Fl_Tooltip::color(num1);
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_textcolor)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::textcolor());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_textcolor_1)
{
    Fl_Color num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(1);
    Fl_Tooltip::textcolor(num1);
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_margin_width)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::margin_width());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_margin_width_1)
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    Fl_Tooltip::margin_width();
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_margin_height)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::margin_height());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_margin_height_1)
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    Fl_Tooltip::margin_height();
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_wrap_width)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::wrap_width());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_wrap_width_1)
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    Fl_Tooltip::wrap_width();
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_margin_width_2)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::margin_width());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_margin_height_2)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::margin_height());
}

SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_wrap_width_2)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETNUMBER(Fl_Tooltip::wrap_width());
}

#ifdef __APPLE__
SIMPLE_BLOCK(fltk_fl_tooltip_Fl_Tooltip_current_window)
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
		return ;
	}
	SIMPLE_API_RETCPOINTER(Fl_Tooltip::current_window(),"SMOOTHC_FLTK");
}
#endif

/* Fl_Tree */
SIMPLE_BLOCK(fltk_FL_TREE_REASON_NONE)
{
    SIMPLE_API_RETNUMBER(FL_TREE_REASON_NONE);
}

SIMPLE_BLOCK(fltk_FL_TREE_REASON_SELECTED)
{
    SIMPLE_API_RETNUMBER(FL_TREE_REASON_SELECTED);
}

SIMPLE_BLOCK(fltk_FL_TREE_REASON_DESELECTED)
{
    SIMPLE_API_RETNUMBER(FL_TREE_REASON_DESELECTED);
}

#if FLTK_ABI_VERSION >= 10301
SIMPLE_BLOCK(fltk_FL_TREE_REASON_RESELECTED)
{
	SIMPLE_API_RETNUMBER(FL_TREE_REASON_RESELECTED);
}
#endif

SIMPLE_BLOCK(fltk_FL_TREE_REASON_OPENED)
{
    SIMPLE_API_RETNUMBER(FL_TREE_REASON_OPENED);
}

SIMPLE_BLOCK(fltk_FL_TREE_REASON_CLOSED)
{
    SIMPLE_API_RETNUMBER(FL_TREE_REASON_CLOSED);
}

SIMPLE_BLOCK(fltk_fl_tree_Fl_Tree)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Tree(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_handle)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_tree_draw)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->draw();
}

SIMPLE_BLOCK(fltk_fl_tree_show_self)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show_self();
}

SIMPLE_BLOCK(fltk_fl_tree_resize)
{
    Fl_Tree* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_tree_root_label)
{
    Fl_Tree* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->root_label(str2);
}

SIMPLE_BLOCK(fltk_fl_tree_root)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->root(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_root_1)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->root(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->prefs();
}

SIMPLE_BLOCK(fltk_fl_tree_add)
{
    Fl_Tree* point1;
    const char* str2;
    Fl_Tree_Item * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point3 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->add(str2,point3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_add_1)
{
    Fl_Tree* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->add(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_add_2)
{
    Fl_Tree* point1;
    const char* str2;
    Fl_Tree_Item * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point3 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->add(str2,point3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_add_3)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETCPOINTER(point1->add(point2,str3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_insert_above)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETCPOINTER(point1->insert_above(point2,str3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_insert)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    const char* str3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETCPOINTER(point1->insert(point2,str3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_remove)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->remove(point2));
}

SIMPLE_BLOCK(fltk_fl_tree_clear)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_tree_clear_children)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->clear_children(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_find_item)
{
    Fl_Tree* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->find_item(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_find_item_1)
{
    Fl_Tree* point1;
    char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->find_item(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_pathname)
{
    Fl_Tree* point1;
    char* str2;
    int num3;
    Fl_Tree_Item * point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point4 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_pathname(str2,num3,point4),"SMOOTHC_FLTK");
}

#if FLTK_ABI_VERSION >= 10303
SIMPLE_BLOCK(fltk_fl_tree_find_clicked)
{
	Fl_Tree* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETCPOINTER(point1->find_clicked(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_find_clicked_1)
{
	Fl_Tree* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETCPOINTER(point1->find_clicked(num2),"SMOOTHC_FLTK");
}
#else

SIMPLE_BLOCK(fltk_fl_tree_find_clicked_2)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->find_clicked(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_clicked_3)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_clicked(),"SMOOTHC_FLTK");
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_first)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->first(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_first_visible)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->first_visible(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_first_visible_item)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->first_visible_item(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_next)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->next(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prev)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->prev(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_last)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->last(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_last_visible)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->last_visible(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_last_visible_item)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->last_visible_item(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_first_selected_item)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->first_selected_item(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_last_selected_item)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->last_selected_item(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_next_item)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    bool num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (bool) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETCPOINTER(point1->next_item(point2,num3,num4),"SMOOTHC_FLTK");
}

#if FLTK_ABI_VERSION >= 10303
SIMPLE_BLOCK(fltk_fl_tree_next_selected_item)
{
	Fl_Tree* point1;
	Fl_Tree_Item * point2;
	int num3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
	SIMPLE_API_RETCPOINTER(point1->next_selected_item(point2,num3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_get_selected_items)
{
	Fl_Tree* point1;
	Fl_Tree_Item_Array * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Tree_Item_Array *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	SIMPLE_API_RETNUMBER(point1->get_selected_items(*point2));
}
#else

SIMPLE_BLOCK(fltk_fl_tree_next_selected_item_1)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->next_selected_item(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_next_selected_item_2)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETCPOINTER(point1->next_selected_item(point2,num3),"SMOOTHC_FLTK");
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_open)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->open(point2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_open_1)
{
    Fl_Tree* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->open(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_open_toggle)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->open_toggle(point2,num3);
}

SIMPLE_BLOCK(fltk_fl_tree_close)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->close(point2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_close_1)
{
    Fl_Tree* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->close(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_is_open)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_open(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_is_open_1)
{
    Fl_Tree* point1;
    char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->is_open(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_is_close)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_close(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_is_close_1)
{
    Fl_Tree* point1;
    char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->is_close(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_select)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->select(point2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_select_1)
{
    Fl_Tree* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->select(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_select_toggle)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->select_toggle(point2,num3);
}

SIMPLE_BLOCK(fltk_fl_tree_deselect)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->deselect(point2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_deselect_1)
{
    Fl_Tree* point1;
    const char* str2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->deselect(str2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_deselect_all)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->deselect_all(point2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_select_only)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->select_only(point2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_select_all)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->select_all(point2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_extend_selection_dir)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    Fl_Tree_Item * point3;
    int num4;
    int num5;
    bool num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (bool) (int) SIMPLE_API_GETNUMBER(6);
    SIMPLE_API_RETNUMBER(point1->extend_selection_dir(point2,point3,num4,num5,num6));
}

#if FLTK_ABI_VERSION >= 10303
SIMPLE_BLOCK(fltk_fl_tree_extend_selection)
{
	Fl_Tree* point1;
	Fl_Tree_Item * point2;
	Fl_Tree_Item * point3;
	int num4;
	bool num5;
	if ( SIMPLE_API_PARACOUNT != 5 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point3 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
	num5 = (bool) (int) SIMPLE_API_GETNUMBER(5);
	SIMPLE_API_RETNUMBER(point1->extend_selection(point2,point3,num4,num5));
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_set_item_focus)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->set_item_focus(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_get_item_focus)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->get_item_focus(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_is_selected)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_selected(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_is_selected_1)
{
    Fl_Tree* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->is_selected(str2));
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelfont_tree)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_labelfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelfont_tree_1)
{
    Fl_Tree* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->item_labelfont(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelsize_tree)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_labelsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelsize_tree_1)
{
    Fl_Tree* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->item_labelsize(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelfgcolor_tree)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_labelfgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelfgcolor_tree_1)
{
    Fl_Tree* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->item_labelfgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelbgcolor_tree)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_labelbgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelbgcolor_tree_1)
{
    Fl_Tree* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->item_labelbgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_connectorcolor)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->connectorcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_connectorcolor_1)
{
    Fl_Tree* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->connectorcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_marginleft)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->marginleft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_marginleft_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->marginleft(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_margintop)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->margintop(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_margintop_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->margintop(num2);
}

#if FLTK_ABI_VERSION >= 10301
SIMPLE_BLOCK(fltk_fl_tree_marginbottom)
{
	Fl_Tree* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->marginbottom(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_marginbottom_1)
{
	Fl_Tree* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point1->marginbottom(num2);
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_linespacing)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linespacing(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_linespacing_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->linespacing(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_openchild_marginbottom)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->openchild_marginbottom(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_openchild_marginbottom_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->openchild_marginbottom(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_usericonmarginleft)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->usericonmarginleft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_usericonmarginleft_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->usericonmarginleft(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_labelmarginleft)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelmarginleft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_labelmarginleft_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelmarginleft(num2);
}

#if FLTK_ABI_VERSION >= 10301
SIMPLE_BLOCK(fltk_fl_tree_widgetmarginleft)
{
	Fl_Tree* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->widgetmarginleft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_widgetmarginleft_1)
{
	Fl_Tree* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point1->widgetmarginleft(num2);
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_connectorwidth)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->connectorwidth(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_connectorwidth_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->connectorwidth(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_usericon)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->usericon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_usericon_1)
{
    Fl_Tree* point1;
    Fl_Image * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->usericon(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_openicon)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->openicon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_openicon_1)
{
    Fl_Tree* point1;
    Fl_Image * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->openicon(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_closeicon)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->closeicon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_closeicon_1)
{
    Fl_Tree* point1;
    Fl_Image * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->closeicon(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_showcollapse)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->showcollapse(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_showcollapse_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->showcollapse(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_showroot)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->showroot(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_showroot_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->showroot(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_connectorstyle)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->connectorstyle(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_connectorstyle_1)
{
    Fl_Tree* point1;
    Fl_Tree_Connector point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Connector) (int) SIMPLE_API_GETNUMBER(2);
    point1->connectorstyle(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_sortorder)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->sortorder(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_sortorder_1)
{
    Fl_Tree* point1;
    Fl_Tree_Sort point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Sort) (int) SIMPLE_API_GETNUMBER(2);
    point1->sortorder(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_selectbox)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->selectbox(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_selectbox_1)
{
    Fl_Tree* point1;
    Fl_Boxtype point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(2);
    point1->selectbox(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_selectmode)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->selectmode(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_selectmode_1)
{
    Fl_Tree* point1;
    Fl_Tree_Select point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Select) (int) SIMPLE_API_GETNUMBER(2);
    point1->selectmode(point2);
}

#if FLTK_ABI_VERSION >= 10301
SIMPLE_BLOCK(fltk_fl_tree_item_reselect_mode)
{
	Fl_Tree* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->item_reselect_mode(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_reselect_mode_1)
{
	Fl_Tree* point1;
	Fl_Tree_Item_Reselect_Mode point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Tree_Item_Reselect_Mode) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point1->item_reselect_mode(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_draw_mode)
{
	Fl_Tree* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->item_draw_mode(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_draw_mode_1)
{
	Fl_Tree* point1;
	Fl_Tree_Item_Draw_Mode point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Tree_Item_Draw_Mode) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point1->item_draw_mode(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_draw_mode_2)
{
	Fl_Tree* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point1->item_draw_mode(num2);
}
#endif

#if FLTK_ABI_VERSION >= 10303
SIMPLE_BLOCK(fltk_fl_tree_calc_dimensions)
{
	Fl_Tree* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->calc_dimensions();
}

SIMPLE_BLOCK(fltk_fl_tree_calc_tree)
{
	Fl_Tree* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->calc_tree();
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_recalc_tree)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->recalc_tree();
}

SIMPLE_BLOCK(fltk_fl_tree_displayed)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->displayed(point2));
}

SIMPLE_BLOCK(fltk_fl_tree_show_item)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->show_item(point2,num3);
}

SIMPLE_BLOCK(fltk_fl_tree_show_item_1)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->show_item(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_show_item_top)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->show_item_top(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_show_item_middle)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->show_item_middle(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_show_item_bottom)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->show_item_bottom(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_display)
{
    Fl_Tree* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->display(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_vposition)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->vposition(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_vposition_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->vposition(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_hposition)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->hposition(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_hposition_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->hposition(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_is_scrollbar)
{
    Fl_Tree* point1;
    Fl_Widget * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->is_scrollbar(point2));
}

SIMPLE_BLOCK(fltk_fl_tree_scrollbar_size)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->scrollbar_size(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_scrollbar_size_1)
{
    Fl_Tree* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->scrollbar_size(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_is_vscroll_visible)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_vscroll_visible(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_is_hscroll_visible)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_hscroll_visible(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_callback_item)
{
    Fl_Tree* point1;
    Fl_Tree_Item* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->callback_item(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_callback_item_1)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->callback_item(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_callback_reason)
{
    Fl_Tree* point1;
    Fl_Tree_Reason num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Tree_Reason) (int) SIMPLE_API_GETNUMBER(2);
    point1->callback_reason(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_callback_reason_1)
{
    Fl_Tree* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->callback_reason(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_load)
{
    Fl_Tree* point1;
    Fl_Preferences* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Preferences*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->load(*point2);
}

/* Fl_Tree_Item */
SIMPLE_BLOCK(fltk_fl_tree_item_Fl_Tree_Item)
{
    const Fl_Tree_Prefs * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point2 = (const Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(new Fl_Tree_Item(*point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_Fl_Tree_Item_2)
{
    const Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point2 = (const Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(new Fl_Tree_Item(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_x)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->x(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_y)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->y(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_w)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->w(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_h)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->h(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_label_x)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->label_x(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_label_y)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->label_y(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_label_w)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->label_w(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_label_h)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->label_h(),"SMOOTHC_FLTK");
}

#if FLTK_ABI_VERSION >= 10303
SIMPLE_BLOCK(fltk_fl_tree_item_draw_item_content)
{
	Fl_Tree_Item* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	SIMPLE_API_RETNUMBER(point1->draw_item_content(num2));
}

SIMPLE_BLOCK(fltk_fl_tree_item_draw)
{
	Fl_Tree_Item* point1;
	int num2;
	int * point3;
	int num4;
	Fl_Tree_Item * point5;
	int * point6;
	int num7;
	int num8;
	if ( SIMPLE_API_PARACOUNT != 8 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
		return ;
	}
	point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
	point5 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
	point6 = (int *) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
	num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
	num8 = (int) (int) SIMPLE_API_GETNUMBER(8);
	point1->draw(num2,*point3,num4,point5,*point6,num7,num8);
}
c

SIMPLE_BLOCK(fltk_fl_tree_item_draw_1)
{
	Fl_Tree_Item* point1;
	int num2;
	int * point3;
	int num4;
	Fl_Widget * point5;
	Fl_Tree_Item * point6;
	const Fl_Tree_Prefs * point7;
	int num8;
	if ( SIMPLE_API_PARACOUNT != 8 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
		return ;
	}
	point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point3 = (int *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
	point5 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
	point6 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(6,"SMOOTHC_FLTK");
	point7 = (const Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(7,"SMOOTHC_FLTK");
	num8 = (int) (int) SIMPLE_API_GETNUMBER(8);
	point1->draw(num2,*point3,num4,point5,point6,*point7,num8);
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_item_label)
{
    Fl_Tree_Item* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->label(str2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_label_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->label(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_user_data)
{
    Fl_Tree_Item* point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->user_data(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_user_data_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->user_data();
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelfont)
{
    Fl_Tree_Item* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelfont(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelfont_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelsize)
{
    Fl_Tree_Item* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelsize(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelsize_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelfgcolor)
{
    Fl_Tree_Item* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelfgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelfgcolor_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelfgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelcolor)
{
    Fl_Tree_Item* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelcolor_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelbgcolor)
{
    Fl_Tree_Item* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelbgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_labelbgcolor_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelbgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_widget_1)
{
    Fl_Tree_Item* point1;
    Fl_Widget * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->widget(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_widget_2)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->widget(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_children_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->children(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_child)
{
    Fl_Tree_Item* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->child(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_child_1)
{
    Fl_Tree_Item* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->child(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_has_children)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->has_children(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_find_child)
{
    Fl_Tree_Item* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->find_child(str2));
}

SIMPLE_BLOCK(fltk_fl_tree_item_find_child_1)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->find_child(point2));
}

SIMPLE_BLOCK(fltk_fl_tree_item_remove_child)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->remove_child(point2));
}

SIMPLE_BLOCK(fltk_fl_tree_item_remove_child_1)
{
    Fl_Tree_Item* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->remove_child(str2));
}

SIMPLE_BLOCK(fltk_fl_tree_item_clear_children)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_children();
}

SIMPLE_BLOCK(fltk_fl_tree_item_swap_children)
{
    Fl_Tree_Item* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->swap_children(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_tree_item_swap_children_1)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Item * point2;
    Fl_Tree_Item * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->swap_children(point2,point3));
}

SIMPLE_BLOCK(fltk_fl_tree_item_find_child_item)
{
    Fl_Tree_Item* point1;
    char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->find_child_item(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_find_child_item_1)
{
    Fl_Tree_Item* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETCPOINTER(point1->find_child_item(str2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_find_child_item_2)
{
    Fl_Tree_Item* point1;
    char* * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (char* *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->find_child_item(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_find_child_item_3)
{
    Fl_Tree_Item* point1;
    char* * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (char* *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->find_child_item(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_find_item)
{
    Fl_Tree_Item* point1;
    char* * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (char* *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->find_item(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_find_item_1)
{
    Fl_Tree_Item* point1;
    char* * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (char* *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->find_item(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_add)
{
    Fl_Tree_Item* point1;
    const Fl_Tree_Prefs * point2;
    const char* str3;
    Fl_Tree_Item * point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point4 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->add(*point2,str3,point4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_add_1)
{
    Fl_Tree_Item* point1;
    const Fl_Tree_Prefs * point2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETCPOINTER(point1->add(*point2,str3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_add_2)
{
    Fl_Tree_Item* point1;
    const Fl_Tree_Prefs * point2;
    char* * point3;
    Fl_Tree_Item * point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (char* *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->add(*point2,point3,point4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_add_3)
{
    Fl_Tree_Item* point1;
    const Fl_Tree_Prefs * point2;
    char* * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (char* *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->add(*point2,point3),"SMOOTHC_FLTK");
}

#if FLTK_ABI_VERSION >= 10303
SIMPLE_BLOCK(fltk_fl_tree_item_replace)
{
	Fl_Tree_Item* point1;
	Fl_Tree_Item * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->replace(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_replace_child)
{
	Fl_Tree_Item* point1;
	Fl_Tree_Item * point2;
	Fl_Tree_Item * point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point3 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->replace_child(point2,point3),"SMOOTHC_FLTK");
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_item_insert)
{
    Fl_Tree_Item* point1;
    const Fl_Tree_Prefs * point2;
    const char* str3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETCPOINTER(point1->insert(*point2,str3,num4),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_insert_above)
{
    Fl_Tree_Item* point1;
    const Fl_Tree_Prefs * point2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    SIMPLE_API_RETCPOINTER(point1->insert_above(*point2,str3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_deparent)
{
    Fl_Tree_Item* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETCPOINTER(point1->deparent(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_reparent)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->reparent(point2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_item_move)
{
    Fl_Tree_Item* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->move(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_item_move_1)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Item * point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETNUMBER(point1->move(point2,num3,num4));
}

SIMPLE_BLOCK(fltk_fl_tree_item_move_above)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->move_above(point2));
}

SIMPLE_BLOCK(fltk_fl_tree_item_move_below)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->move_below(point2));
}

SIMPLE_BLOCK(fltk_fl_tree_item_move_into)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Item * point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->move_into(point2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_item_depth)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->depth(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_prev)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->prev(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_next)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->next(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_next_sibling)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->next_sibling(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_prev_sibling)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->prev_sibling(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_update_prev_next)
{
    Fl_Tree_Item* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->update_prev_next(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_next_displayed)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Prefs * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->next_displayed(*point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_prev_displayed)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Prefs * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->prev_displayed(*point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_next_visible)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Prefs * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->next_visible(*point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_prev_visible)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Prefs * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Prefs *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->prev_visible(*point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_parent)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->parent(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_parent_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->parent(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_parent_2)
{
    Fl_Tree_Item* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->parent(point2);
}

#if FLTK_ABI_VERSION >= 10304
SIMPLE_BLOCK(fltk_fl_tree_item_tree_1)
{
	Fl_Tree_Item* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->tree(),"SMOOTHC_FLTK");
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_item_open)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->open();
}

SIMPLE_BLOCK(fltk_fl_tree_item_close)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->close();
}

SIMPLE_BLOCK(fltk_fl_tree_item_is_open)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_open(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_is_close)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_close(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_open_toggle)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->open_toggle();
}

SIMPLE_BLOCK(fltk_fl_tree_item_select)
{
    Fl_Tree_Item* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->select(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_select_toggle)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->select_toggle();
}

SIMPLE_BLOCK(fltk_fl_tree_item_select_all)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->select_all());
}

SIMPLE_BLOCK(fltk_fl_tree_item_deselect)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->deselect();
}

SIMPLE_BLOCK(fltk_fl_tree_item_deselect_all)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->deselect_all());
}

SIMPLE_BLOCK(fltk_fl_tree_item_is_selected)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_selected(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_activate)
{
    Fl_Tree_Item* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->activate(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_deactivate)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->deactivate();
}

SIMPLE_BLOCK(fltk_fl_tree_item_is_activated)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_activated(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_is_active)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_active(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_visible)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->visible(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_is_visible)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_visible(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_visible_r)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->visible_r());
}

SIMPLE_BLOCK(fltk_fl_tree_item_usericon)
{
    Fl_Tree_Item* point1;
    Fl_Image * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->usericon(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_usericon_1)
{
    Fl_Tree_Item* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->usericon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_Fl_Tree_Item_Array)
{
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETCPOINTER(new Fl_Tree_Item_Array(num2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_Fl_Tree_Item_Array_1)
{
    const Fl_Tree_Item_Array * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point2 = (const Fl_Tree_Item_Array *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(new Fl_Tree_Item_Array(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_total)
{
    Fl_Tree_Item_Array* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->total(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_swap)
{
    Fl_Tree_Item_Array* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->swap(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_swap_1)
{
    Fl_Tree_Item_Array* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->swap(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_move_2)
{
    Fl_Tree_Item_Array* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->move(num2,num3));
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_deparent_1)
{
    Fl_Tree_Item_Array* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->deparent(num2));
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_reparent_1)
{
    Fl_Tree_Item_Array* point1;
    Fl_Tree_Item * point2;
    Fl_Tree_Item * point3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    SIMPLE_API_RETNUMBER(point1->reparent(point2,point3,num4));
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_clear)
{
    Fl_Tree_Item_Array* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear();
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_add_4)
{
    Fl_Tree_Item_Array* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->add(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_insert_1)
{
    Fl_Tree_Item_Array* point1;
    int num2;
    Fl_Tree_Item * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->insert(num2,point3);
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_replace_1)
{
    Fl_Tree_Item_Array* point1;
    int num2;
    Fl_Tree_Item * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->replace(num2,point3);
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_remove)
{
    Fl_Tree_Item_Array* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->remove(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_remove_1)
{
    Fl_Tree_Item_Array* point1;
    Fl_Tree_Item * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->remove(point2));
}

#if FLTK_ABI_VERSION >= 10303
SIMPLE_BLOCK(fltk_fl_tree_item_array_manage_item_destroy)
{
	Fl_Tree_Item_Array* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point1->manage_item_destroy(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_item_array_manage_item_destroy_1)
{
	Fl_Tree_Item_Array* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Item_Array*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->manage_item_destroy(),"SMOOTHC_FLTK");
}
#endif

SIMPLE_BLOCK(fltk_FL_TREE_SORT_NONE)
{
    SIMPLE_API_RETNUMBER(FL_TREE_SORT_NONE);
}

SIMPLE_BLOCK(fltk_FL_TREE_SORT_ASCENDING)
{
    SIMPLE_API_RETNUMBER(FL_TREE_SORT_ASCENDING);
}

SIMPLE_BLOCK(fltk_FL_TREE_SORT_DESCENDING)
{
    SIMPLE_API_RETNUMBER(FL_TREE_SORT_DESCENDING);
}

SIMPLE_BLOCK(fltk_FL_TREE_CONNECTOR_NONE)
{
    SIMPLE_API_RETNUMBER(FL_TREE_CONNECTOR_NONE);
}

SIMPLE_BLOCK(fltk_FL_TREE_CONNECTOR_DOTTED)
{
    SIMPLE_API_RETNUMBER(FL_TREE_CONNECTOR_DOTTED);
}

SIMPLE_BLOCK(fltk_FL_TREE_CONNECTOR_SOLID)
{
    SIMPLE_API_RETNUMBER(FL_TREE_CONNECTOR_SOLID);
}

SIMPLE_BLOCK(fltk_FL_TREE_SELECT_NONE)
{
    SIMPLE_API_RETNUMBER(FL_TREE_SELECT_NONE);
}

SIMPLE_BLOCK(fltk_FL_TREE_SELECT_SINGLE)
{
    SIMPLE_API_RETNUMBER(FL_TREE_SELECT_SINGLE);
}

SIMPLE_BLOCK(fltk_FL_TREE_SELECT_MULTI)
{
    SIMPLE_API_RETNUMBER(FL_TREE_SELECT_MULTI);
}

SIMPLE_BLOCK(fltk_FL_TREE_SELECT_SINGLE_DRAGGABLE)
{
    SIMPLE_API_RETNUMBER(FL_TREE_SELECT_SINGLE_DRAGGABLE);
}

/* Fl_Tree_Prefs */
SIMPLE_BLOCK(fltk_fl_tree_prefs_Fl_Tree_Prefs)
{
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(new Fl_Tree_Prefs(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelfont)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_labelfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelfont_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->item_labelfont(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelsize)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_labelsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelsize_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->item_labelsize(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelfgcolor)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_labelfgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelfgcolor_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->item_labelfgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelbgcolor)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_labelbgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelbgcolor_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->item_labelbgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelbgcolor_2)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->item_labelbgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_labelbgcolor_3)
{
    Fl_Tree_Prefs* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->item_labelbgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelfont_2)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelfont_3)
{
    Fl_Tree_Prefs* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelfont(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelsize_2)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelsize_3)
{
    Fl_Tree_Prefs* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelsize(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelfgcolor_2)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelfgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelfgcolor_3)
{
    Fl_Tree_Prefs* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelfgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelbgcolor_2)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelbgcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelbgcolor_3)
{
    Fl_Tree_Prefs* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelbgcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_marginleft)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->marginleft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_marginleft_1)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->marginleft(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_margintop)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->margintop(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_margintop_1)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->margintop(num2);
}

#if FLTK_ABI_VERSION >= 10301
SIMPLE_BLOCK(fltk_fl_tree_prefs_marginbottom)
{
	Fl_Tree_Prefs* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->marginbottom(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_marginbottom_1)
{
	Fl_Tree_Prefs* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point1->marginbottom(num2);
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_prefs_openchild_marginbottom)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->openchild_marginbottom(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_openchild_marginbottom_1)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->openchild_marginbottom(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_usericonmarginleft)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->usericonmarginleft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_usericonmarginleft_1)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->usericonmarginleft(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelmarginleft)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelmarginleft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_labelmarginleft_1)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelmarginleft(num2);
}

#if FLTK_ABI_VERSION >= 10301
SIMPLE_BLOCK(fltk_fl_tree_prefs_widgetmarginleft)
{
	Fl_Tree_Prefs* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->widgetmarginleft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_widgetmarginleft_1)
{
	Fl_Tree_Prefs* point1;
	int num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
	point1->widgetmarginleft(num2);
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_prefs_linespacing)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->linespacing(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_linespacing_1)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->linespacing(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_connectorcolor)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->connectorcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_connectorcolor_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->connectorcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_connectorstyle)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->connectorstyle(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_connectorstyle_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Tree_Connector num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Tree_Connector) (int) SIMPLE_API_GETNUMBER(2);
    point1->connectorstyle(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_connectorstyle_2)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->connectorstyle(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_connectorwidth)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->connectorwidth(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_connectorwidth_1)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->connectorwidth(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_openicon)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->openicon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_openicon_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Image * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->openicon(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_closeicon)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->closeicon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_closeicon_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Image * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->closeicon(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_usericon_2)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->usericon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_usericon_3)
{
    Fl_Tree_Prefs* point1;
    Fl_Image * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->usericon(point2);
}

#if FLTK_ABI_VERSION >= 10304
SIMPLE_BLOCK(fltk_fl_tree_prefs_opendeicon)
{
	Fl_Tree_Prefs* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->opendeicon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_closedeicon)
{
	Fl_Tree_Prefs* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->closedeicon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_userdeicon)
{
	Fl_Tree_Prefs* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->userdeicon(),"SMOOTHC_FLTK");
}
#endif

SIMPLE_BLOCK(fltk_fl_tree_prefs_showcollapse)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->showcollapse(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_showcollapse_1)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->showcollapse(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_sortorder)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->sortorder(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_sortorder_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Tree_Sort num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Tree_Sort) (int) SIMPLE_API_GETNUMBER(2);
    point1->sortorder(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_selectbox)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->selectbox(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_selectbox_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Boxtype point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(2);
    point1->selectbox(point2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_showroot)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->showroot(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_showroot_1)
{
    Fl_Tree_Prefs* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->showroot(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_selectmode)
{
    Fl_Tree_Prefs* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->selectmode(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_selectmode_1)
{
    Fl_Tree_Prefs* point1;
    Fl_Tree_Select num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Tree_Select) (int) SIMPLE_API_GETNUMBER(2);
    point1->selectmode(num2);
}

#if FLTK_ABI_VERSION >= 10301
SIMPLE_BLOCK(fltk_fl_tree_prefs_item_reselect_mode)
{
	Fl_Tree_Prefs* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->item_reselect_mode(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_reselect_mode_1)
{
	Fl_Tree_Prefs* point1;
	Fl_Tree_Prefs::Fl_Tree_Item_Reselect_Mode num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (Fl_Tree_Item_Reselect_Mode) (int) SIMPLE_API_GETNUMBER(2);
	point1->item_reselect_mode(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_draw_mode)
{
	Fl_Tree_Prefs* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->item_draw_mode(),"SMOOTHC_FLTK");
}
#endif

#if FLTK_ABI_VERSION >= 10303
SIMPLE_BLOCK(fltk_fl_tree_prefs_item_draw_mode_1)
{
	Fl_Tree_Prefs* point1;
	Fl_Tree_Item_Draw_Mode num2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	num2 = (Fl_Tree_Item_Draw_Mode) (int) SIMPLE_API_GETNUMBER(2);
	point1->item_draw_mode(num2);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_draw_callback)
{
	Fl_Tree_Prefs* point1;
	Fl_Tree_Item_Draw_Callback * point2;
	void* point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Tree_Item_Draw_Callback *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	point1->item_draw_callback(point2,point3);
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_draw_callback_1)
{
	Fl_Tree_Prefs* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	SIMPLE_API_RETCPOINTER(point1->item_draw_callback(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_item_draw_user_data)
{
	Fl_Tree_Prefs* point1;
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point1->item_draw_user_data();
}

SIMPLE_BLOCK(fltk_fl_tree_prefs_do_item_draw_callback)
{
	Fl_Tree_Prefs* point1;
	Fl_Tree_Item * point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (Fl_Tree_Prefs*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (Fl_Tree_Item *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point1->do_item_draw_callback(point2);
}
#endif

/* Fl_Valuator */
SIMPLE_BLOCK(fltk_fl_valuator_bounds)
{
    Fl_Valuator* point1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point1->bounds(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_valuator_minimum)
{
    Fl_Valuator* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->minimum());
}

SIMPLE_BLOCK(fltk_fl_valuator_minimum_1)
{
    Fl_Valuator* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->minimum(num2);
}

SIMPLE_BLOCK(fltk_fl_valuator_maximum)
{
    Fl_Valuator* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->maximum());
}

SIMPLE_BLOCK(fltk_fl_valuator_maximum_1)
{
    Fl_Valuator* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->maximum(num2);
}

SIMPLE_BLOCK(fltk_fl_valuator_range)
{
    Fl_Valuator* point1;
    double num2;
    double num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (double) (double) SIMPLE_API_GETNUMBER(3);
    point1->range(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_valuator_step)
{
    Fl_Valuator* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->step(num2);
}

SIMPLE_BLOCK(fltk_fl_valuator_step_1)
{
    Fl_Valuator* point1;
    double num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->step(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_valuator_step_2)
{
    Fl_Valuator* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    point1->step(num2);
}

SIMPLE_BLOCK(fltk_fl_valuator_step_3)
{
    Fl_Valuator* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->step());
}

SIMPLE_BLOCK(fltk_fl_valuator_precision)
{
    Fl_Valuator* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->precision(num2);
}

SIMPLE_BLOCK(fltk_fl_valuator_value)
{
    Fl_Valuator* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->value());
}

SIMPLE_BLOCK(fltk_fl_valuator_value_1)
{
    Fl_Valuator* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->value(num2));
}

SIMPLE_BLOCK(fltk_fl_valuator_format)
{
    Fl_Valuator* point1;
    char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (char*)  SIMPLE_API_GETSTRING(2);
    SIMPLE_API_RETNUMBER(point1->format(str2));
}

SIMPLE_BLOCK(fltk_fl_valuator_round)
{
    Fl_Valuator* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->round(num2));
}

SIMPLE_BLOCK(fltk_fl_valuator_clamp)
{
    Fl_Valuator* point1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->clamp(num2));
}

SIMPLE_BLOCK(fltk_fl_valuator_increment)
{
    Fl_Valuator* point1;
    double num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Valuator*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    SIMPLE_API_RETNUMBER(point1->increment(num2,num3));
}

/* Fl_Value_Input */
SIMPLE_BLOCK(fltk_fl_value_input_handle)
{
    Fl_Value_Input* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_value_input_resize)
{
    Fl_Value_Input* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_value_input_Fl_Value_Input)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Value_Input(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_input_soft)
{
    Fl_Value_Input* point1;
    char num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (char) (char) SIMPLE_API_GETNUMBER(2);
    point1->soft(num2);
}

SIMPLE_BLOCK(fltk_fl_value_input_soft_1)
{
    Fl_Value_Input* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->soft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_input_shortcut)
{
    Fl_Value_Input* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->shortcut(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_input_shortcut_1)
{
    Fl_Value_Input* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->shortcut(num2);
}

SIMPLE_BLOCK(fltk_fl_value_input_textfont)
{
    Fl_Value_Input* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_input_textfont_1)
{
    Fl_Value_Input* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_value_input_textsize)
{
    Fl_Value_Input* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_input_textsize_1)
{
    Fl_Value_Input* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_value_input_textcolor)
{
    Fl_Value_Input* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_input_textcolor_1)
{
    Fl_Value_Input* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_value_input_cursor_color)
{
    Fl_Value_Input* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->cursor_color());
}

SIMPLE_BLOCK(fltk_fl_value_input_cursor_color_1)
{
    Fl_Value_Input* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Input*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->cursor_color(num2);
}

SIMPLE_BLOCK(fltk_fl_value_output_handle_1)
{
    Fl_Value_Output* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

/* Fl_Value_Output */
SIMPLE_BLOCK(fltk_fl_value_output_Fl_Value_Output)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Value_Output(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_output_soft_2)
{
    Fl_Value_Output* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->soft(num2);
}

SIMPLE_BLOCK(fltk_fl_value_output_soft_3)
{
    Fl_Value_Output* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->soft(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_output_textfont_2)
{
    Fl_Value_Output* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_output_textfont_3)
{
    Fl_Value_Output* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_value_output_textsize_2)
{
    Fl_Value_Output* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_output_textsize_3)
{
    Fl_Value_Output* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_value_output_textcolor_2)
{
    Fl_Value_Output* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_output_textcolor_3)
{
    Fl_Value_Output* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Output*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

/* Fl_Value_Slider */
SIMPLE_BLOCK(fltk_fl_value_slider_handle_2)
{
    Fl_Value_Slider* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_value_slider_Fl_Value_Slider)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Value_Slider(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_slider_textfont_4)
{
    Fl_Value_Slider* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_slider_textfont_5)
{
    Fl_Value_Slider* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->textfont(point2);
}

SIMPLE_BLOCK(fltk_fl_value_slider_textsize_4)
{
    Fl_Value_Slider* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_slider_textsize_5)
{
    Fl_Value_Slider* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->textsize(point2);
}

SIMPLE_BLOCK(fltk_fl_value_slider_textcolor_4)
{
    Fl_Value_Slider* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Value_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->textcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_value_slider_textcolor_5)
{
    Fl_Value_Slider* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Value_Slider*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->textcolor(num2);
}

/* Fl_Widget */
SIMPLE_BLOCK(fltk_fl_widget_handle)
{
    Fl_Widget* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_widget_is_label_copied)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->is_label_copied(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_parent)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->parent(), "SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_parent_1)
{
    Fl_Widget* point1;
    Fl_Group* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Group*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->parent(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_type)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->type());
}

SIMPLE_BLOCK(fltk_fl_widget_type_1)
{
    Fl_Widget* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->type(num2);
}

SIMPLE_BLOCK(fltk_fl_widget_x)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->x());
}

SIMPLE_BLOCK(fltk_fl_widget_y)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->y());
}

SIMPLE_BLOCK(fltk_fl_widget_w)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->w(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_h)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->h(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_resize)
{
    Fl_Widget* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_widget_damage_resize)
{
    Fl_Widget* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    SIMPLE_API_RETNUMBER(point1->damage_resize(num2,num3,num4,num5));
}

SIMPLE_BLOCK(fltk_fl_widget_position)
{
    Fl_Widget* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->position(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_widget_size)
{
    Fl_Widget* point1;
    int num2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->size(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_widget_align)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->align(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_align_1)
{
    Fl_Widget* point1;
    Fl_Align point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Align)(int) SIMPLE_API_GETNUMBER(2);
    point1->align(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_box)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->box());
}

SIMPLE_BLOCK(fltk_fl_widget_box_1)
{
    Fl_Widget* point1;
    Fl_Boxtype point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Boxtype) (int) SIMPLE_API_GETNUMBER(2);
    point1->box(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_color)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->color(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_color_1)
{
    Fl_Widget* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->color(num2);
}

SIMPLE_BLOCK(fltk_fl_widget_selection_color)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->selection_color(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_selection_color_1)
{
    Fl_Widget* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->selection_color(num2);
}

SIMPLE_BLOCK(fltk_fl_widget_color_2)
{
    Fl_Widget* point1;
    Fl_Color num2;
    Fl_Color num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(3);
    point1->color(num2,num3);
}

SIMPLE_BLOCK(fltk_fl_widget_label)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETSTRING(point1->label());
}

SIMPLE_BLOCK(fltk_fl_widget_label_1)
{
    Fl_Widget* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->label(str2);
}

SIMPLE_BLOCK(fltk_fl_widget_copy_label)
{
    Fl_Widget* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->copy_label(str2);
}

SIMPLE_BLOCK(fltk_fl_widget_label_2)
{
    Fl_Widget* point1;
    Fl_Labeltype point2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Labeltype) (int) SIMPLE_API_GETNUMBER(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point1->label(point2,str3);
}

SIMPLE_BLOCK(fltk_fl_widget_labeltype)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labeltype(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_labeltype_1)
{
    Fl_Widget* point1;
    Fl_Labeltype point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Labeltype) (int) SIMPLE_API_GETNUMBER(2);
    point1->labeltype(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_labelcolor)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelcolor(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_labelcolor_1)
{
    Fl_Widget* point1;
    Fl_Color num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (Fl_Color) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelcolor(num2);
}

SIMPLE_BLOCK(fltk_fl_widget_labelfont)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelfont(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_labelfont_1)
{
    Fl_Widget* point1;
    Fl_Font point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Font) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelfont(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_labelsize)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->labelsize(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_labelsize_1)
{
    Fl_Widget* point1;
    Fl_Fontsize point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Fontsize) (int) SIMPLE_API_GETNUMBER(2);
    point1->labelsize(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_image)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->image(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_image_1)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->image(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_image_2)
{
    Fl_Widget* point1;
    Fl_Image* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->image(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_image_3)
{
    Fl_Widget* point1;
    Fl_Image* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->image(*point2);
}

SIMPLE_BLOCK(fltk_fl_widget_deimage)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->deimage(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_deimage_1)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->deimage(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_deimage_2)
{
    Fl_Widget* point1;
    Fl_Image* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->deimage(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_deimage_3)
{
    Fl_Widget* point1;
    Fl_Image* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Image*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->deimage(*point2);
}

SIMPLE_BLOCK(fltk_fl_widget_tooltip)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->tooltip(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_tooltip_1)
{
    Fl_Widget* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->tooltip(str2);
}

SIMPLE_BLOCK(fltk_fl_widget_copy_tooltip)
{
    Fl_Widget* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->copy_tooltip(str2);
}

SIMPLE_BLOCK(fltk_fl_widget_callback)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->callback(),"SMOOTHC_FLTK");
}

/*
	To be deprecated as soon as the Callback class has been created and exported
*/
SIMPLE_BLOCK(fltk_fl_widget_callback_on_onlick)
{
    Fl_Widget* point1;
    int int2 ;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    int2 = (int) SIMPLE_API_GETNUMBER(2);
    point1->callback(SimpleCallBack,(void*)int2);
}

SIMPLE_BLOCK(fltk_fl_widget_callback_1)
{
    Fl_Widget* point1;
    Fl_Callback* point2;
    void* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Callback*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (void*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->callback(point2,point3);
}

SIMPLE_BLOCK(fltk_fl_widget_callback_2)
{
    Fl_Widget* point1;
    Fl_Callback* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Callback*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->callback(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_callback_3)
{
    Fl_Widget* point1;
    Fl_Callback0* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Callback0*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->callback(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_callback_4)
{
    Fl_Widget* point1;
    Fl_Callback1* point2;
    long num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Callback1*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (long) (long) SIMPLE_API_GETNUMBER(3);
    point1->callback(point2,num3);
}

SIMPLE_BLOCK(fltk_fl_widget_user_data)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->user_data();
}

SIMPLE_BLOCK(fltk_fl_widget_user_data_1)
{
    Fl_Widget* point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->user_data(point2);
}

SIMPLE_BLOCK(fltk_fl_widget_argument)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->argument());
}

SIMPLE_BLOCK(fltk_fl_widget_argument_1)
{
    Fl_Widget* point1;
    long num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (long) (long) SIMPLE_API_GETNUMBER(2);
    point1->argument(num2);
}

SIMPLE_BLOCK(fltk_fl_widget_when)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->when(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_when_1)
{
    Fl_Widget* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->when(num2);
}

SIMPLE_BLOCK(fltk_fl_widget_visible)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->visible(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_visible_r)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->visible_r());
}

SIMPLE_BLOCK(fltk_fl_widget_show)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show();
}

SIMPLE_BLOCK(fltk_fl_widget_hide)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->hide();
}

SIMPLE_BLOCK(fltk_fl_widget_set_visible)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_visible();
}

SIMPLE_BLOCK(fltk_fl_widget_clear_visible)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_visible();
}

SIMPLE_BLOCK(fltk_fl_widget_active)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->active(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_active_r)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->active_r());
}

SIMPLE_BLOCK(fltk_fl_widget_activate)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->activate();
}

SIMPLE_BLOCK(fltk_fl_widget_deactivate)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->deactivate();
}

SIMPLE_BLOCK(fltk_fl_widget_output)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->output(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_set_output)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_output();
}

SIMPLE_BLOCK(fltk_fl_widget_clear_output)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_output();
}

SIMPLE_BLOCK(fltk_fl_widget_takesevents)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->takesevents());
}

SIMPLE_BLOCK(fltk_fl_widget_changed)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->changed(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_set_changed)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_changed();
}

SIMPLE_BLOCK(fltk_fl_widget_clear_changed)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_changed();
}

SIMPLE_BLOCK(fltk_fl_widget_clear_active)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_active();
}

SIMPLE_BLOCK(fltk_fl_widget_set_active)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_active();
}

SIMPLE_BLOCK(fltk_fl_widget_take_focus)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->take_focus());
}

SIMPLE_BLOCK(fltk_fl_widget_set_visible_focus)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_visible_focus();
}

SIMPLE_BLOCK(fltk_fl_widget_clear_visible_focus)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_visible_focus();
}

SIMPLE_BLOCK(fltk_fl_widget_visible_focus)
{
    Fl_Widget* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->visible_focus(num2);
}

SIMPLE_BLOCK(fltk_fl_widget_visible_focus_1)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->visible_focus());
}

SIMPLE_BLOCK(fltk_fl_widget_Fl_Widget_default_callback)
{
    Fl_Widget * point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl_Widget::default_callback(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_widget_do_callback)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->do_callback();
}

SIMPLE_BLOCK(fltk_fl_widget_do_callback_1)
{
    Fl_Widget* point1;
    Fl_Widget* point2;
    long num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (long) (long) SIMPLE_API_GETNUMBER(3);
    point1->do_callback(point2,num3);
}

SIMPLE_BLOCK(fltk_fl_widget_test_shortcut)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->test_shortcut());
}

SIMPLE_BLOCK(fltk_fl_widget_Fl_Widget_label_shortcut)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETNUMBER(Fl_Widget::label_shortcut(str1));
}

SIMPLE_BLOCK(fltk_fl_widget_Fl_Widget_test_shortcut)
{
    const char* str1;
    bool num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    num2 = (bool) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(Fl_Widget::test_shortcut(str1,num2));
}

SIMPLE_BLOCK(fltk_fl_widget__set_fullscreen)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->_set_fullscreen();
}

SIMPLE_BLOCK(fltk_fl_widget__clear_fullscreen)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->_clear_fullscreen();
}

SIMPLE_BLOCK(fltk_fl_widget_contains)
{
    Fl_Widget* point1;
    Fl_Widget * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->contains(point2));
}

SIMPLE_BLOCK(fltk_fl_widget_inside)
{
    Fl_Widget* point1;
    Fl_Widget* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->inside(point2),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_redraw)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->redraw();
}

SIMPLE_BLOCK(fltk_fl_widget_redraw_label)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->redraw_label();
}

SIMPLE_BLOCK(fltk_fl_widget_damage)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->damage(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_clear_damage)
{
    Fl_Widget* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->clear_damage(num2);
}

SIMPLE_BLOCK(fltk_fl_widget_damage_1)
{
    Fl_Widget* point1;
    uchar num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    point1->damage(num2);
}

SIMPLE_BLOCK(fltk_fl_widget_damage_2)
{
    Fl_Widget* point1;
    uchar num2;
    int num3;
    int num4;
    int num5;
    int num6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (uchar) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    point1->damage(num2,num3,num4,num5,num6);
}

SIMPLE_BLOCK(fltk_fl_widget_draw_label)
{
    Fl_Widget* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    Fl_Align point6;
    if ( SIMPLE_API_PARACOUNT != 6 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS6PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point6 = (Fl_Align) (int) SIMPLE_API_GETNUMBER(6);
    point1->draw_label(num2,num3,num4,num5,point6);
}

//TODO : return calculated width and height in list
SIMPLE_BLOCK(fltk_fl_widget_measure_label)
{
    Fl_Widget* point1;
    int* point2;
    int* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->measure_label(*point2,*point3);
}

SIMPLE_BLOCK(fltk_fl_widget_window)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->window(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_top_window)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->top_window(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_top_window_offset)
{
    Fl_Widget* point1;
    int* point2;
    int* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (int*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point3 = (int*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->top_window_offset(*point2,*point3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_as_group)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->as_group(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_as_window)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->as_window(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_as_gl_window)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->as_gl_window(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_use_accents_menu)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->use_accents_menu());
}

SIMPLE_BLOCK(fltk_fl_widget_color2)
{
    Fl_Widget* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->color2(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_widget_color2_1)
{
    Fl_Widget* point1;
    unsigned num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Widget*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (unsigned) (int) SIMPLE_API_GETNUMBER(2);
    point1->color2(num2);
}

/* Fl_Window */
SIMPLE_BLOCK(fltk_fl_window_shape)
{
    Fl_Window* point1;
    const Fl_Image* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Image*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->shape(point2);
}

SIMPLE_BLOCK(fltk_fl_window_shape_1)
{
    Fl_Window* point1;
    const Fl_Image* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Image*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->shape(*point2);
}

SIMPLE_BLOCK(fltk_fl_window_Fl_Window)
{
    int num2;
    int num3;
    const char* str4;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    str4 = (const char*)  simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(3))->str;
    SIMPLE_API_RETCPOINTER(new Fl_Window(num2,num3,str4),"SMOOTHC_FLTK");

}

SIMPLE_BLOCK(fltk_fl_window_Fl_Window_1)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(5))->str;
    SIMPLE_API_RETCPOINTER(new Fl_Window(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_handle)
{
    Fl_Window* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(point1->handle(num2));
}

SIMPLE_BLOCK(fltk_fl_window_resize)
{
    Fl_Window* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->resize(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_window_border)
{
    Fl_Window* point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point1->border(num2);
}

SIMPLE_BLOCK(fltk_fl_window_clear_border)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_border();
}

SIMPLE_BLOCK(fltk_fl_window_border_1)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->border(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_set_override)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_override();
}

SIMPLE_BLOCK(fltk_fl_window_override)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->override(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_set_modal)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_modal();
}

SIMPLE_BLOCK(fltk_fl_window_modal)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->modal());
}

SIMPLE_BLOCK(fltk_fl_window_set_non_modal)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_non_modal();
}

SIMPLE_BLOCK(fltk_fl_window_non_modal)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->non_modal(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_clear_modal_states)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->clear_modal_states();
}

SIMPLE_BLOCK(fltk_fl_window_set_menu_window)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_menu_window();
}

SIMPLE_BLOCK(fltk_fl_window_menu_window)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->menu_window(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_set_tooltip_window)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->set_tooltip_window();
}

SIMPLE_BLOCK(fltk_fl_window_tooltip_window)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->tooltip_window());
}

SIMPLE_BLOCK(fltk_fl_window_hotspot)
{
    Fl_Window* point1;
    int num2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->hotspot(num2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_window_hotspot_1)
{
    Fl_Window* point1;
    const Fl_Widget* point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->hotspot(point2,num3);
}

SIMPLE_BLOCK(fltk_fl_window_hotspot_2)
{
    Fl_Window* point1;
    const Fl_Widget* point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_Widget*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->hotspot(*point2,num3);
}

SIMPLE_BLOCK(fltk_fl_window_free_position)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->free_position();
}

SIMPLE_BLOCK(fltk_fl_window_size_range)
{
    Fl_Window* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    int num6;
    int num7;
    int num8;
    if ( SIMPLE_API_PARACOUNT != 8 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS8PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    num8 = (int) (int) SIMPLE_API_GETNUMBER(8);
    point1->size_range(num2,num3,num4,num5,num6,num7,num8);
}

SIMPLE_BLOCK(fltk_fl_window_label)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->label(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_iconlabel)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->iconlabel(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_label_1)
{
    Fl_Window* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->label(str2);
}

SIMPLE_BLOCK(fltk_fl_window_iconlabel_1)
{
    Fl_Window* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->iconlabel(str2);
}

SIMPLE_BLOCK(fltk_fl_window_label_2)
{
    Fl_Window* point1;
    const char* str2;
    const char* str3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    str3 = (const char*)  SIMPLE_API_GETSTRING(3);
    point1->label(str2,str3);
}

SIMPLE_BLOCK(fltk_fl_window_copy_label)
{
    Fl_Window* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->copy_label(str2);
}

SIMPLE_BLOCK(fltk_fl_window_Fl_Window_default_xclass)
{
    const char* str1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str1 = (const char*)  SIMPLE_API_GETSTRING(1);
    Fl_Window::default_xclass(str1);
}

SIMPLE_BLOCK(fltk_fl_window_Fl_Window_default_xclass_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETSTRING(Fl_Window::default_xclass());
}

SIMPLE_BLOCK(fltk_fl_window_xclass)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->xclass(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_xclass_1)
{
    Fl_Window* point1;
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    str2 = (const char*)  SIMPLE_API_GETSTRING(2);
    point1->xclass(str2);
}

SIMPLE_BLOCK(fltk_fl_window_Fl_Window_default_icon)
{
    const Fl_RGB_Image* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (const Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    Fl_Window::default_icon(point1);
}

SIMPLE_BLOCK(fltk_fl_window_Fl_Window_default_icons)
{
    const Fl_RGB_Image** point1;
    int num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (const Fl_RGB_Image**) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    Fl_Window::default_icons(point1,num2);
}

SIMPLE_BLOCK(fltk_fl_window_icon)
{
    Fl_Window* point1;
    const Fl_RGB_Image* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->icon(point2);
}

SIMPLE_BLOCK(fltk_fl_window_icons)
{
    Fl_Window* point1;
    const Fl_RGB_Image** point2;
    int num3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_RGB_Image**) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    point1->icons(point2,num3);
}

#ifdef _WIN32
SIMPLE_BLOCK(fltk_fl_window_Fl_Window_default_icons_1)
{
	HICON point1;
	HICON point2;
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
		return ;
	}
	point1 = (HICON) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (HICON) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	Fl_Window::default_icons(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_window_icons_1)
{
	Fl_Window* point1;
	HICON point2;
	HICON point3;
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
		return ;
	}
	point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (HICON) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	point3 = (HICON) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
	point1->icons(point2,point3);
}
#endif

SIMPLE_BLOCK(fltk_fl_window_icon_1)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->icon(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_icon_2)
{
    Fl_Window* point1;
    const void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->icon(point2);
}

SIMPLE_BLOCK(fltk_fl_window_shown)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->shown());
}

SIMPLE_BLOCK(fltk_fl_window_show)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->show();
}

SIMPLE_BLOCK(fltk_fl_window_hide)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->hide();
}

SIMPLE_BLOCK(fltk_fl_window_show_1)
{
    Fl_Window* point1;
    int num2;
    char* * point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (char* *) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point1->show(num2,point3);
}

SIMPLE_BLOCK(fltk_fl_window_wait_for_expose)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->wait_for_expose();
}

SIMPLE_BLOCK(fltk_fl_window_fullscreen)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->fullscreen();
}

SIMPLE_BLOCK(fltk_fl_window_fullscreen_off)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->fullscreen_off();
}

SIMPLE_BLOCK(fltk_fl_window_fullscreen_off_1)
{
    Fl_Window* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->fullscreen_off(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_window_fullscreen_active)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->fullscreen_active(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_fullscreen_screens)
{
    Fl_Window* point1;
    int num2;
    int num3;
    int num4;
    int num5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
    point1->fullscreen_screens(num2,num3,num4,num5);
}

SIMPLE_BLOCK(fltk_fl_window_iconize)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->iconize();
}

SIMPLE_BLOCK(fltk_fl_window_x_root)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->x_root());
}

SIMPLE_BLOCK(fltk_fl_window_y_root)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->y_root());
}

SIMPLE_BLOCK(fltk_fl_window_Fl_Window_current)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(Fl_Window::current(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_make_current)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->make_current();
}

SIMPLE_BLOCK(fltk_fl_window_as_window)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->as_window(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_window_cursor)
{
    Fl_Window* point1;
    Fl_Cursor point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Cursor) (int) SIMPLE_API_GETNUMBER(2);
    point1->cursor(point2);
}

SIMPLE_BLOCK(fltk_fl_window_cursor_1)
{
    Fl_Window* point1;
    const Fl_RGB_Image* point2;
    int num3;
    int num4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (const Fl_RGB_Image*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point1->cursor(point2,num3,num4);
}

SIMPLE_BLOCK(fltk_fl_window_default_cursor)
{
    Fl_Window* point1;
    Fl_Cursor point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Cursor) (int) SIMPLE_API_GETNUMBER(2);
    point1->default_cursor(point2);
}

SIMPLE_BLOCK(fltk_fl_window_Fl_Window_default_callback)
{
    Fl_Window* point1;
    void* point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (void*) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    Fl_Window::default_callback(point1,point2);
}

SIMPLE_BLOCK(fltk_fl_window_decorated_w)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->decorated_w());
}

SIMPLE_BLOCK(fltk_fl_window_decorated_h)
{
    Fl_Window* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Window*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETNUMBER(point1->decorated_h());
}

/* Fl_Wizard */
SIMPLE_BLOCK(fltk_fl_wizard_Fl_Wizard)
{
    int num2;
    int num3;
    int num4;
    int num5;
    const char* str6;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num2 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num5 = (int) (int) SIMPLE_API_GETNUMBER(4);
    str6 = (const char*)  SIMPLE_API_GETSTRING(5);
    SIMPLE_API_RETCPOINTER(new Fl_Wizard(num2,num3,num4,num5,str6),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_wizard_next)
{
    Fl_Wizard* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Wizard*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->next();
}

SIMPLE_BLOCK(fltk_fl_wizard_prev)
{
    Fl_Wizard* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Wizard*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point1->prev();
}

SIMPLE_BLOCK(fltk_fl_wizard_value)
{
    Fl_Wizard* point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Wizard*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(point1->value(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_wizard_value_1)
{
    Fl_Wizard* point1;
    Fl_Widget * point2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    point1 = (Fl_Wizard*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    point2 = (Fl_Widget *) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
    point1->value(point2);
}

/* Fl_XBM_Image */
SIMPLE_BLOCK(fltk_fl_xbm_image_Fl_XBM_Image)
{
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    str2 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETCPOINTER(new Fl_XBM_Image(str2),"SMOOTHC_FLTK");
}

/* Fl_XPM_Image */
SIMPLE_BLOCK(fltk_fl_xpm_image_Fl_XPM_Image)
{
    const char* str2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    str2 = (const char*)  SIMPLE_API_GETSTRING(1);
    SIMPLE_API_RETCPOINTER(new Fl_XPM_Image(str2),"SMOOTHC_FLTK");
}

#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_initialize)
{
	int* point1;
	char** point2;
	const char* str3;
	FL_CMD_OPT* point4;
	int num5;
	if ( SIMPLE_API_PARACOUNT != 5 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
		return ;
	}
	point1 = (int*) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
	point2 = (char**) SIMPLE_API_GETCPOINTER(2,"SMOOTHC_FLTK");
	str3 = (const char*)  SIMPLE_API_GETSTRING(3);
	point4 = (FL_CMD_OPT*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
	num5 = (int) (int) SIMPLE_API_GETNUMBER(5);
	fl_initialize(point1,point2,str3,point4,num5);
}
#endif

SIMPLE_BLOCK(fltk_fl_finish)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    fl_finish();
}

SIMPLE_BLOCK(fltk_fl_add_io_callback)
{
    int num1;
    short point2;
    FL_IO_CALLBACK point3;
    void* point4;
    if ( SIMPLE_API_PARACOUNT != 4 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS4PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    point2 = (short) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (FL_IO_CALLBACK) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    point4 = (void*) SIMPLE_API_GETCPOINTER(4,"SMOOTHC_FLTK");
    fl_add_io_callback(num1,point2,point3,point4);
}

/* fl_math */
#ifdef USE_MATH_NAMES
SIMPLE_BLOCK(fltk_rint)
{
    double num1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    SIMPLE_API_RETNUMBER(rint(num1));
}

SIMPLE_BLOCK(fltk_copysign)
{
    double num1;
    double num2;
    if ( SIMPLE_API_PARACOUNT != 2 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS2PARA);
        return ;
    }
    num1 = (double) (double) SIMPLE_API_GETNUMBER(1);
    num2 = (double) (double) SIMPLE_API_GETNUMBER(2);
    SIMPLE_API_RETNUMBER(copysign(num1,num2));
}
#endif

/* x.H */
#ifndef __ANDROID__
SIMPLE_BLOCK(fltk_fl_gc)
{
	SIMPLE_API_RETCPOINTER(fl_gc,"SMOOTHC_FLTK");
}
#endif

SIMPLE_BLOCK(fltk_fl_window)
{
    #ifdef __APPLE__
        SIMPLE_API_RETCPOINTER(NULL,"SMOOTHC_FLTK");
    #else
        SIMPLE_API_RETCPOINTER(fl_window,"SMOOTHC_FLTK");
    #endif
}

SIMPLE_BLOCK(fltk_fl_clip_region_x)
{
    Fl_Region point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Region) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    fl_clip_region(point1);
}

SIMPLE_BLOCK(fltk_fl_clip_region_x_1)
{
    if ( SIMPLE_API_PARACOUNT != 0 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS0PARA);
        return ;
    }
    SIMPLE_API_RETCPOINTER(fl_clip_region(),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_copy_offscreen)
{
    int num1;
    int num2;
    int num3;
    int num4;
    Fl_Offscreen point5;
    int num6;
    int num7;
    if ( SIMPLE_API_PARACOUNT != 7 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS7PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point5 = (Fl_Offscreen) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    num6 = (int) (int) SIMPLE_API_GETNUMBER(6);
    num7 = (int) (int) SIMPLE_API_GETNUMBER(7);
    fl_copy_offscreen(num1,num2,num3,num4,point5,num6,num7);
}

SIMPLE_BLOCK(fltk_fl_create_bitmask)
{
    int num1;
    int num2;
    const uchar* point3;
    if ( SIMPLE_API_PARACOUNT != 3 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS3PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    point3 = (const uchar*) SIMPLE_API_GETCPOINTER(3,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(fl_create_bitmask(num1,num2,point3),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_create_alphamask)
{
    int num1;
    int num2;
    int num3;
    int num4;
    const uchar* point5;
    if ( SIMPLE_API_PARACOUNT != 5 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS5PARA);
        return ;
    }
    num1 = (int) (int) SIMPLE_API_GETNUMBER(1);
    num2 = (int) (int) SIMPLE_API_GETNUMBER(2);
    num3 = (int) (int) SIMPLE_API_GETNUMBER(3);
    num4 = (int) (int) SIMPLE_API_GETNUMBER(4);
    point5 = (const uchar*) SIMPLE_API_GETCPOINTER(5,"SMOOTHC_FLTK");
    SIMPLE_API_RETCPOINTER(fl_create_alphamask(num1,num2,num3,num4,point5),"SMOOTHC_FLTK");
}

SIMPLE_BLOCK(fltk_fl_delete_bitmask)
{
    Fl_Bitmask point1;
    if ( SIMPLE_API_PARACOUNT != 1 ) {
        SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
        return ;
    }
    point1 = (Fl_Bitmask) SIMPLE_API_GETCPOINTER(1,"SMOOTHC_FLTK");
    fl_delete_bitmask(point1);
}
SIMPLE_API void init_full_tick(SimpleState *sState)
{
    /* CUSTOM */
    register_block("__FL_WINDOW",fltk_FL_WINDOW);
    register_block("__FL_DOUBLE_WINDOW",fltk_FL_DOUBLE_WINDOW);
    register_block("__fl_window_to_widget",fltk_window_to_widget);
    /* SMOOTHC EXPORTED */
    register_block("__fl_filename_name",fltk_fl_filename_name);
    register_block("__fl_filename_ext",fltk_fl_filename_ext);
    register_block("__fl_filename_setext",fltk_fl_filename_setext);
    register_block("__fl_filename_expand",fltk_fl_filename_expand);
    register_block("__fl_filename_absolute",fltk_fl_filename_absolute);
    register_block("__fl_filename_relative",fltk_fl_filename_relative);
    register_block("__fl_filename_match",fltk_fl_filename_match);
    register_block("__fl_filename_isdir",fltk_fl_filename_isdir);
    register_block("__fl_filename_setext_1",fltk_fl_filename_setext_1);
    register_block("__fl_filename_expand_1",fltk_fl_filename_expand_1);
    register_block("__fl_filename_absolute_1",fltk_fl_filename_absolute_1);
    register_block("__fl_filename_relative_1",fltk_fl_filename_relative_1);
    register_block("__fl_filename_relative_2",fltk_fl_filename_relative_2);
    register_block("__fl_filename_list",fltk_fl_filename_list);
    register_block("__fl_filename_free_list",fltk_fl_filename_free_list);
    register_block("__fl_open_uri",fltk_fl_open_uri);
    register_block("__fl_decode_uri",fltk_fl_decode_uri);
    register_block("__FL_NO_EVENT",fltk_FL_NO_EVENT);
    register_block("__FL_PUSH",fltk_FL_PUSH);
    register_block("__FL_RELEASE",fltk_FL_RELEASE);
    register_block("__FL_ENTER",fltk_FL_ENTER);
    register_block("__FL_LEAVE",fltk_FL_LEAVE);
    register_block("__FL_DRAG",fltk_FL_DRAG);
    register_block("__FL_FOCUS",fltk_FL_FOCUS);
    register_block("__FL_UNFOCUS",fltk_FL_UNFOCUS);
    register_block("__FL_KEYDOWN",fltk_FL_KEYDOWN);
    register_block("__FL_KEYBOARD",fltk_FL_KEYBOARD);
    register_block("__FL_KEYUP",fltk_FL_KEYUP);
    register_block("__FL_CLOSE",fltk_FL_CLOSE);
    register_block("__FL_MOVE",fltk_FL_MOVE);
    register_block("__FL_SHORTCUT",fltk_FL_SHORTCUT);
    register_block("__FL_DEACTIVATE",fltk_FL_DEACTIVATE);
    register_block("__FL_ACTIVATE",fltk_FL_ACTIVATE);
    register_block("__FL_HIDE",fltk_FL_HIDE);
    register_block("__FL_SHOW",fltk_FL_SHOW);
    register_block("__FL_PASTE",fltk_FL_PASTE);
    register_block("__FL_SELECTIONCLEAR",fltk_FL_SELECTIONCLEAR);
    register_block("__FL_MOUSEWHEEL",fltk_FL_MOUSEWHEEL);
    register_block("__FL_DND_ENTER",fltk_FL_DND_ENTER);
    register_block("__FL_DND_DRAG",fltk_FL_DND_DRAG);
    register_block("__FL_DND_LEAVE",fltk_FL_DND_LEAVE);
    register_block("__FL_DND_RELEASE",fltk_FL_DND_RELEASE);
    register_block("__FL_SCREEN_CONFIGURATION_CHANGED",fltk_FL_SCREEN_CONFIGURATION_CHANGED);
    register_block("__FL_FULLSCREEN",fltk_FL_FULLSCREEN);
    register_block("__FL_ZOOM_GESTURE",fltk_FL_ZOOM_GESTURE);
    register_block("__FL_WHEN_NEVER",fltk_FL_WHEN_NEVER);
    register_block("__FL_WHEN_CHANGED",fltk_FL_WHEN_CHANGED);
    register_block("__FL_WHEN_NOT_CHANGED",fltk_FL_WHEN_NOT_CHANGED);
    register_block("__FL_WHEN_RELEASE",fltk_FL_WHEN_RELEASE);
    register_block("__FL_WHEN_RELEASE_ALWAYS",fltk_FL_WHEN_RELEASE_ALWAYS);
    register_block("__FL_WHEN_ENTER_KEY",fltk_FL_WHEN_ENTER_KEY);
    register_block("__FL_WHEN_ENTER_KEY_ALWAYS",fltk_FL_WHEN_ENTER_KEY_ALWAYS);
    register_block("__FL_WHEN_ENTER_KEY_CHANGED",fltk_FL_WHEN_ENTER_KEY_CHANGED);
    register_block("__FL_NO_BOX",fltk_FL_NO_BOX);
    register_block("__FL_FLAT_BOX",fltk_FL_FLAT_BOX);
    register_block("__FL_UP_BOX",fltk_FL_UP_BOX);
    register_block("__FL_DOWN_BOX",fltk_FL_DOWN_BOX);
    register_block("__FL_UP_FRAME",fltk_FL_UP_FRAME);
    register_block("__FL_DOWN_FRAME",fltk_FL_DOWN_FRAME);
    register_block("__FL_THIN_UP_BOX",fltk_FL_THIN_UP_BOX);
    register_block("__FL_THIN_DOWN_BOX",fltk_FL_THIN_DOWN_BOX);
    register_block("__FL_THIN_UP_FRAME",fltk_FL_THIN_UP_FRAME);
    register_block("__FL_THIN_DOWN_FRAME",fltk_FL_THIN_DOWN_FRAME);
    register_block("__FL_ENGRAVED_BOX",fltk_FL_ENGRAVED_BOX);
    register_block("__FL_EMBOSSED_BOX",fltk_FL_EMBOSSED_BOX);
    register_block("__FL_ENGRAVED_FRAME",fltk_FL_ENGRAVED_FRAME);
    register_block("__FL_EMBOSSED_FRAME",fltk_FL_EMBOSSED_FRAME);
    register_block("__FL_BORDER_BOX",fltk_FL_BORDER_BOX);
    register_block("___FL_SHADOW_BOX",fltk__FL_SHADOW_BOX);
    register_block("__FL_BORDER_FRAME",fltk_FL_BORDER_FRAME);
    register_block("___FL_SHADOW_FRAME",fltk__FL_SHADOW_FRAME);
    register_block("___FL_ROUNDED_BOX",fltk__FL_ROUNDED_BOX);
    register_block("___FL_RSHADOW_BOX",fltk__FL_RSHADOW_BOX);
    register_block("___FL_ROUNDED_FRAME",fltk__FL_ROUNDED_FRAME);
    register_block("___FL_RFLAT_BOX",fltk__FL_RFLAT_BOX);
    register_block("___FL_ROUND_UP_BOX",fltk__FL_ROUND_UP_BOX);
    register_block("___FL_ROUND_DOWN_BOX",fltk__FL_ROUND_DOWN_BOX);
    register_block("___FL_DIAMOND_UP_BOX",fltk__FL_DIAMOND_UP_BOX);
    register_block("___FL_DIAMOND_DOWN_BOX",fltk__FL_DIAMOND_DOWN_BOX);
    register_block("___FL_OVAL_BOX",fltk__FL_OVAL_BOX);
    register_block("___FL_OSHADOW_BOX",fltk__FL_OSHADOW_BOX);
    register_block("___FL_OVAL_FRAME",fltk__FL_OVAL_FRAME);
    register_block("___FL_OFLAT_BOX",fltk__FL_OFLAT_BOX);
    register_block("___FL_PLASTIC_UP_BOX",fltk__FL_PLASTIC_UP_BOX);
    register_block("___FL_PLASTIC_DOWN_BOX",fltk__FL_PLASTIC_DOWN_BOX);
    register_block("___FL_PLASTIC_UP_FRAME",fltk__FL_PLASTIC_UP_FRAME);
    register_block("___FL_PLASTIC_DOWN_FRAME",fltk__FL_PLASTIC_DOWN_FRAME);
    register_block("___FL_PLASTIC_THIN_UP_BOX",fltk__FL_PLASTIC_THIN_UP_BOX);
    register_block("___FL_PLASTIC_THIN_DOWN_BOX",fltk__FL_PLASTIC_THIN_DOWN_BOX);
    register_block("___FL_PLASTIC_ROUND_UP_BOX",fltk__FL_PLASTIC_ROUND_UP_BOX);
    register_block("___FL_PLASTIC_ROUND_DOWN_BOX",fltk__FL_PLASTIC_ROUND_DOWN_BOX);
    register_block("___FL_GTK_UP_BOX",fltk__FL_GTK_UP_BOX);
    register_block("___FL_GTK_DOWN_BOX",fltk__FL_GTK_DOWN_BOX);
    register_block("___FL_GTK_UP_FRAME",fltk__FL_GTK_UP_FRAME);
    register_block("___FL_GTK_DOWN_FRAME",fltk__FL_GTK_DOWN_FRAME);
    register_block("___FL_GTK_THIN_UP_BOX",fltk__FL_GTK_THIN_UP_BOX);
    register_block("___FL_GTK_THIN_DOWN_BOX",fltk__FL_GTK_THIN_DOWN_BOX);
    register_block("___FL_GTK_THIN_UP_FRAME",fltk__FL_GTK_THIN_UP_FRAME);
    register_block("___FL_GTK_THIN_DOWN_FRAME",fltk__FL_GTK_THIN_DOWN_FRAME);
    register_block("___FL_GTK_ROUND_UP_BOX",fltk__FL_GTK_ROUND_UP_BOX);
    register_block("___FL_GTK_ROUND_DOWN_BOX",fltk__FL_GTK_ROUND_DOWN_BOX);
    register_block("___FL_GLEAM_UP_BOX",fltk__FL_GLEAM_UP_BOX);
    register_block("___FL_GLEAM_DOWN_BOX",fltk__FL_GLEAM_DOWN_BOX);
    register_block("___FL_GLEAM_UP_FRAME",fltk__FL_GLEAM_UP_FRAME);
    register_block("___FL_GLEAM_DOWN_FRAME",fltk__FL_GLEAM_DOWN_FRAME);
    register_block("___FL_GLEAM_THIN_UP_BOX",fltk__FL_GLEAM_THIN_UP_BOX);
    register_block("___FL_GLEAM_THIN_DOWN_BOX",fltk__FL_GLEAM_THIN_DOWN_BOX);
    register_block("___FL_GLEAM_ROUND_UP_BOX",fltk__FL_GLEAM_ROUND_UP_BOX);
    register_block("___FL_GLEAM_ROUND_DOWN_BOX",fltk__FL_GLEAM_ROUND_DOWN_BOX);
    register_block("__fl_define_FL_ROUND_UP_BOX",fltk_fl_define_FL_ROUND_UP_BOX);
    register_block("__fl_define_FL_SHADOW_BOX",fltk_fl_define_FL_SHADOW_BOX);
    register_block("__fl_define_FL_ROUNDED_BOX",fltk_fl_define_FL_ROUNDED_BOX);
    register_block("__fl_define_FL_RFLAT_BOX",fltk_fl_define_FL_RFLAT_BOX);
    register_block("__fl_define_FL_RSHADOW_BOX",fltk_fl_define_FL_RSHADOW_BOX);
    register_block("__fl_define_FL_DIAMOND_BOX",fltk_fl_define_FL_DIAMOND_BOX);
    register_block("__fl_define_FL_OVAL_BOX",fltk_fl_define_FL_OVAL_BOX);
    register_block("__fl_define_FL_PLASTIC_UP_BOX",fltk_fl_define_FL_PLASTIC_UP_BOX);
    register_block("__fl_define_FL_GTK_UP_BOX",fltk_fl_define_FL_GTK_UP_BOX);
    register_block("__fl_define_FL_GLEAM_UP_BOX",fltk_fl_define_FL_GLEAM_UP_BOX);
    register_block("__fl_box",fltk_fl_box);
    register_block("__fl_down",fltk_fl_down);
    register_block("__fl_frame",fltk_fl_frame);
    register_block("__FL_NORMAL_LABEL",fltk_FL_NORMAL_LABEL);
    register_block("__FL_NO_LABEL",fltk_FL_NO_LABEL);
    register_block("___FL_SHADOW_LABEL",fltk__FL_SHADOW_LABEL);
    register_block("___FL_ENGRAVED_LABEL",fltk__FL_ENGRAVED_LABEL);
    register_block("___FL_EMBOSSED_LABEL",fltk__FL_EMBOSSED_LABEL);
    register_block("___FL_MULTI_LABEL",fltk__FL_MULTI_LABEL);
    register_block("___FL_ICON_LABEL",fltk__FL_ICON_LABEL);
    register_block("___FL_IMAGE_LABEL",fltk__FL_IMAGE_LABEL);
    register_block("__fl_define_FL_SHADOW_LABEL",fltk_fl_define_FL_SHADOW_LABEL);
    register_block("__fl_define_FL_ENGRAVED_LABEL",fltk_fl_define_FL_ENGRAVED_LABEL);
    register_block("__fl_define_FL_EMBOSSED_LABEL",fltk_fl_define_FL_EMBOSSED_LABEL);
    register_block("__FL_ALIGN_CENTER",fltk_FL_ALIGN_CENTER);
    register_block("__FL_ALIGN_TOP",fltk_FL_ALIGN_TOP);
    register_block("__FL_ALIGN_BOTTOM",fltk_FL_ALIGN_BOTTOM);
    register_block("__FL_ALIGN_LEFT",fltk_FL_ALIGN_LEFT);
    register_block("__FL_ALIGN_RIGHT",fltk_FL_ALIGN_RIGHT);
    register_block("__FL_ALIGN_INSIDE",fltk_FL_ALIGN_INSIDE);
    register_block("__FL_ALIGN_TEXT_OVER_IMAGE",fltk_FL_ALIGN_TEXT_OVER_IMAGE);
    register_block("__FL_ALIGN_IMAGE_OVER_TEXT",fltk_FL_ALIGN_IMAGE_OVER_TEXT);
    register_block("__FL_ALIGN_CLIP",fltk_FL_ALIGN_CLIP);
    register_block("__FL_ALIGN_WRAP",fltk_FL_ALIGN_WRAP);
    register_block("__FL_ALIGN_IMAGE_NEXT_TO_TEXT",fltk_FL_ALIGN_IMAGE_NEXT_TO_TEXT);
    register_block("__FL_ALIGN_TEXT_NEXT_TO_IMAGE",fltk_FL_ALIGN_TEXT_NEXT_TO_IMAGE);
    register_block("__FL_ALIGN_IMAGE_BACKDROP",fltk_FL_ALIGN_IMAGE_BACKDROP);
    register_block("__FL_ALIGN_TOP_LEFT",fltk_FL_ALIGN_TOP_LEFT);
    register_block("__FL_ALIGN_TOP_RIGHT",fltk_FL_ALIGN_TOP_RIGHT);
    register_block("__FL_ALIGN_BOTTOM_LEFT",fltk_FL_ALIGN_BOTTOM_LEFT);
    register_block("__FL_ALIGN_BOTTOM_RIGHT",fltk_FL_ALIGN_BOTTOM_RIGHT);
    register_block("__FL_ALIGN_LEFT_TOP",fltk_FL_ALIGN_LEFT_TOP);
    register_block("__FL_ALIGN_RIGHT_TOP",fltk_FL_ALIGN_RIGHT_TOP);
    register_block("__FL_ALIGN_LEFT_BOTTOM",fltk_FL_ALIGN_LEFT_BOTTOM);
    register_block("__FL_ALIGN_RIGHT_BOTTOM",fltk_FL_ALIGN_RIGHT_BOTTOM);
    register_block("__FL_ALIGN_NOWRAP",fltk_FL_ALIGN_NOWRAP);
    register_block("__FL_ALIGN_POSITION_MASK",fltk_FL_ALIGN_POSITION_MASK);
    register_block("__FL_ALIGN_IMAGE_MASK",fltk_FL_ALIGN_IMAGE_MASK);
    register_block("__FL_HELVETICA",fltk_FL_HELVETICA);
    register_block("__FL_HELVETICA_BOLD",fltk_FL_HELVETICA_BOLD);
    register_block("__FL_HELVETICA_ITALIC",fltk_FL_HELVETICA_ITALIC);
    register_block("__FL_HELVETICA_BOLD_ITALIC",fltk_FL_HELVETICA_BOLD_ITALIC);
    register_block("__FL_COURIER",fltk_FL_COURIER);
    register_block("__FL_COURIER_BOLD",fltk_FL_COURIER_BOLD);
    register_block("__FL_COURIER_ITALIC",fltk_FL_COURIER_ITALIC);
    register_block("__FL_COURIER_BOLD_ITALIC",fltk_FL_COURIER_BOLD_ITALIC);
    register_block("__FL_TIMES",fltk_FL_TIMES);
    register_block("__FL_TIMES_BOLD",fltk_FL_TIMES_BOLD);
    register_block("__FL_TIMES_ITALIC",fltk_FL_TIMES_ITALIC);
    register_block("__FL_TIMES_BOLD_ITALIC",fltk_FL_TIMES_BOLD_ITALIC);
    register_block("__FL_SYMBOL",fltk_FL_SYMBOL);
    register_block("__FL_SCREEN",fltk_FL_SCREEN);
    register_block("__FL_SCREEN_BOLD",fltk_FL_SCREEN_BOLD);
    register_block("__FL_ZAPF_DINGBATS",fltk_FL_ZAPF_DINGBATS);
    register_block("__FL_FREE_FONT",fltk_FL_FREE_FONT);
    register_block("__FL_BOLD",fltk_FL_BOLD);
    register_block("__FL_ITALIC",fltk_FL_ITALIC);
    register_block("__FL_BOLD_ITALIC",fltk_FL_BOLD_ITALIC);
    register_block("__FL_NORMAL_SIZE",fltk_FL_NORMAL_SIZE);
    register_block("__FL_FOREGROUND_COLOR",fltk_FL_FOREGROUND_COLOR);
    register_block("__FL_BACKGROUND2_COLOR",fltk_FL_BACKGROUND2_COLOR);
    register_block("__FL_INACTIVE_COLOR",fltk_FL_INACTIVE_COLOR);
    register_block("__FL_SELECTION_COLOR",fltk_FL_SELECTION_COLOR);
    register_block("__FL_GRAY0",fltk_FL_GRAY0);
    register_block("__FL_DARK3",fltk_FL_DARK3);
    register_block("__FL_DARK2",fltk_FL_DARK2);
    register_block("__FL_DARK1",fltk_FL_DARK1);
    register_block("__FL_BACKGROUND_COLOR",fltk_FL_BACKGROUND_COLOR);
    register_block("__FL_LIGHT1",fltk_FL_LIGHT1);
    register_block("__FL_LIGHT2",fltk_FL_LIGHT2);
    register_block("__FL_LIGHT3",fltk_FL_LIGHT3);
    register_block("__FL_BLACK",fltk_FL_BLACK);
    register_block("__FL_RED",fltk_FL_RED);
    register_block("__FL_GREEN",fltk_FL_GREEN);
    register_block("__FL_YELLOW",fltk_FL_YELLOW);
    register_block("__FL_BLUE",fltk_FL_BLUE);
    register_block("__FL_MAGENTA",fltk_FL_MAGENTA);
    register_block("__FL_CYAN",fltk_FL_CYAN);
    register_block("__FL_DARK_RED",fltk_FL_DARK_RED);
    register_block("__FL_DARK_GREEN",fltk_FL_DARK_GREEN);
    register_block("__FL_DARK_YELLOW",fltk_FL_DARK_YELLOW);
    register_block("__FL_DARK_BLUE",fltk_FL_DARK_BLUE);
    register_block("__FL_DARK_MAGENTA",fltk_FL_DARK_MAGENTA);
    register_block("__FL_DARK_CYAN",fltk_FL_DARK_CYAN);
    register_block("__FL_WHITE",fltk_FL_WHITE);
    register_block("__fl_inactive",fltk_fl_inactive);
    register_block("__fl_contrast",fltk_fl_contrast);
    register_block("__fl_color_average",fltk_fl_color_average);
    register_block("__fl_lighter",fltk_fl_lighter);
    register_block("__fl_darker",fltk_fl_darker);
    register_block("__fl_rgb_color",fltk_fl_rgb_color);
    register_block("__fl_rgb_color_1",fltk_fl_rgb_color_1);
    register_block("__fl_gray_ramp",fltk_fl_gray_ramp);
    register_block("__fl_color_cube",fltk_fl_color_cube);
    /* FL */
#ifndef FL_DOXYGEN
    register_block("__Fl_Fl_e_number",fltk_fl_Fl_e_number);
    register_block("__Fl_Fl_e_x",fltk_fl_Fl_e_x);
    register_block("__Fl_Fl_e_x_1",fltk_fl_Fl_e_x_1);
    register_block("__Fl_Fl_e_y",fltk_fl_Fl_e_y);
    register_block("__Fl_Fl_e_y_1",fltk_fl_Fl_e_y_1);
    register_block("__Fl_Fl_e_x_root",fltk_fl_Fl_e_x_root);
    register_block("__Fl_Fl_e_y_root",fltk_fl_Fl_e_y_root);
    register_block("__Fl_Fl_e_dx",fltk_fl_Fl_e_dx);
    register_block("__Fl_Fl_e_dy",fltk_fl_Fl_e_dy);
    register_block("__Fl_Fl_e_state",fltk_fl_Fl_e_state);
    register_block("__Fl_Fl_e_clicks",fltk_fl_Fl_e_clicks);
    register_block("__Fl_Fl_e_is_click",fltk_fl_Fl_e_is_click);
    register_block("__Fl_Fl_e_keysym",fltk_fl_Fl_e_keysym);
    register_block("__Fl_Fl_e_text",fltk_fl_Fl_e_text);
    register_block("__Fl_Fl_e_length",fltk_fl_Fl_e_length);
    register_block("__Fl_Fl_e_clipboard_data",fltk_fl_Fl_e_clipboard_data);
    register_block("__Fl_Fl_e_clipboard_type",fltk_fl_Fl_e_clipboard_type);
    register_block("__Fl_Fl_e_dispatch",fltk_fl_Fl_e_dispatch);
    register_block("__Fl_Fl_belowmouse_",fltk_fl_Fl_belowmouse_);
    register_block("__Fl_Fl_pushed_", fltk_fl_Fl_pushed_);
    register_block("__Fl_Fl_set_pushed_", fltk_fl_Fl_set_pushed_);
    register_block("__Fl_Fl_focus_",fltk_fl_Fl_focus_);
    register_block("__Fl_Fl_damage_",fltk_fl_Fl_damage_);
    register_block("__Fl_Fl_selection_owner_",fltk_fl_Fl_selection_owner_);
    register_block("__Fl_Fl_modal_",fltk_fl_Fl_modal_);
    register_block("__Fl_Fl_grab_",fltk_fl_Fl_grab_);
    register_block("__Fl_Fl_compose_state",fltk_fl_Fl_compose_state);
    register_block("__Fl_Fl_call_screen_init",fltk_fl_Fl_call_screen_init);
#ifdef __APPLE__
    register_block("__Fl_Fl_reset_marked_text",fltk_fl_Fl_reset_marked_text);
	register_block("__Fl_Fl_insertion_point_location",fltk_fl_Fl_insertion_point_location);
#endif
#endif
    register_block("__Fl_Fl_damage",fltk_fl_Fl_damage);
    register_block("__Fl_OPTION_ARROW_FOCUS",fltk_fl_OPTION_ARROW_FOCUS);
    register_block("__Fl_OPTION_VISIBLE_FOCUS",fltk_fl_OPTION_VISIBLE_FOCUS);
    register_block("__Fl_OPTION_DND_TEXT",fltk_fl_OPTION_DND_TEXT);
    register_block("__Fl_OPTION_SHOW_TOOLTIPS",fltk_fl_OPTION_SHOW_TOOLTIPS);
    register_block("__Fl_OPTION_FNFC_USES_GTK",fltk_fl_OPTION_FNFC_USES_GTK);
    register_block("__Fl_Fl_option",fltk_fl_Fl_option);
    register_block("__Fl_Fl_option_1",fltk_fl_Fl_option_1);
    register_block("__Fl_Fl_awake_ring_size_",fltk_fl_Fl_awake_ring_size_);
    register_block("__Fl_Fl_awake_ring_head_",fltk_fl_Fl_awake_ring_head_);
    register_block("__Fl_Fl_awake_ring_tail_",fltk_fl_Fl_awake_ring_tail_);
    register_block("__Fl_Fl_scheme_",fltk_fl_Fl_scheme_);
    register_block("__Fl_Fl_scheme_bg_",fltk_fl_Fl_scheme_bg_);
    register_block("__Fl_Fl_e_original_keysym",fltk_fl_Fl_e_original_keysym);
    register_block("__Fl_Fl_scrollbar_size_",fltk_fl_Fl_scrollbar_size_);
    register_block("__Fl_Fl_add_awake_handler_",fltk_fl_Fl_add_awake_handler_);
    register_block("__Fl_Fl_get_awake_handler_",fltk_fl_Fl_get_awake_handler_);
    register_block("__Fl_Fl_version",fltk_fl_Fl_version);
    register_block("__Fl_Fl_api_version",fltk_fl_Fl_api_version);
    register_block("__Fl_Fl_abi_version",fltk_fl_Fl_abi_version);
    register_block("__Fl_Fl_abi_check",fltk_fl_Fl_abi_check);
    register_block("__Fl_Fl_arg",fltk_fl_Fl_arg);
    register_block("__Fl_Fl_args",fltk_fl_Fl_args);
    register_block("__Fl_Fl_args_1",fltk_fl_Fl_args_1);
    register_block("__Fl_Fl_help",fltk_fl_Fl_help);
    register_block("__Fl_Fl_display",fltk_fl_Fl_display);
    register_block("__Fl_Fl_visual",fltk_fl_Fl_visual);
    register_block("__Fl_Fl_gl_visual",fltk_fl_Fl_gl_visual);
    register_block("__Fl_Fl_own_colormap",fltk_fl_Fl_own_colormap);
    register_block("__Fl_Fl_get_system_colors",fltk_fl_Fl_get_system_colors);
    register_block("__Fl_Fl_foreground",fltk_fl_Fl_foreground);
    register_block("__Fl_Fl_background",fltk_fl_Fl_background);
    register_block("__Fl_Fl_background2",fltk_fl_Fl_background2);
    register_block("__Fl_Fl_scheme",fltk_fl_Fl_scheme);
    register_block("__Fl_Fl_scheme_1",fltk_fl_Fl_scheme_1);
    register_block("__Fl_Fl_is_scheme",fltk_fl_Fl_is_scheme);
    register_block("__Fl_Fl_reload_scheme",fltk_fl_Fl_reload_scheme);
    register_block("__Fl_Fl_scrollbar_size",fltk_fl_Fl_scrollbar_size);
    register_block("__Fl_Fl_scrollbar_size_1",fltk_fl_Fl_scrollbar_size_1);
    register_block("__Fl_Fl_wait",fltk_fl_Fl_wait);
    register_block("__Fl_Fl_wait_1",fltk_fl_Fl_wait_1);
    register_block("__Fl_Fl_check",fltk_fl_Fl_check);
    register_block("__Fl_Fl_ready",fltk_fl_Fl_ready);
    register_block("__Fl_Fl_run",fltk_fl_Fl_run);
    register_block("__Fl_Fl_readqueue",fltk_fl_Fl_readqueue);
    register_block("__Fl_Fl_add_timeout",fltk_fl_Fl_add_timeout);
    register_block("__Fl_Fl_repeat_timeout",fltk_fl_Fl_repeat_timeout);
    register_block("__Fl_Fl_has_timeout",fltk_fl_Fl_has_timeout);
    register_block("__Fl_Fl_remove_timeout",fltk_fl_Fl_remove_timeout);
    register_block("__Fl_Fl_add_check",fltk_fl_Fl_add_check);
    register_block("__Fl_Fl_has_check",fltk_fl_Fl_has_check);
    register_block("__Fl_Fl_remove_check",fltk_fl_Fl_remove_check);
    register_block("__Fl_Fl_add_fd",fltk_fl_Fl_add_fd);
    register_block("__Fl_Fl_add_fd_1",fltk_fl_Fl_add_fd_1);
    register_block("__Fl_Fl_remove_fd",fltk_fl_Fl_remove_fd);
    register_block("__Fl_Fl_remove_fd_1",fltk_fl_Fl_remove_fd_1);
    register_block("__Fl_Fl_add_idle",fltk_fl_Fl_add_idle);
    register_block("__Fl_Fl_has_idle",fltk_fl_Fl_has_idle);
    register_block("__Fl_Fl_remove_idle",fltk_fl_Fl_remove_idle);
    register_block("__Fl_Fl_damage_1",fltk_fl_Fl_damage_1);
    register_block("__Fl_Fl_redraw",fltk_fl_Fl_redraw);
    register_block("__Fl_Fl_flush",fltk_fl_Fl_flush);
    register_block("__Fl_Fl_first_window",fltk_fl_Fl_first_window);
    register_block("__Fl_Fl_first_window_1",fltk_fl_Fl_first_window_1);
    register_block("__Fl_Fl_next_window",fltk_fl_Fl_next_window);
    register_block("__Fl_Fl_modal",fltk_fl_Fl_modal);
    register_block("__Fl_Fl_grab",fltk_fl_Fl_grab);
    register_block("__Fl_Fl_grab_1",fltk_fl_Fl_grab_1);
    register_block("__Fl_Fl_event",fltk_fl_Fl_event);
    register_block("__Fl_Fl_event_x",fltk_fl_Fl_event_x);
    register_block("__Fl_Fl_event_y",fltk_fl_Fl_event_y);
    register_block("__Fl_Fl_event_x_root",fltk_fl_Fl_event_x_root);
    register_block("__Fl_Fl_event_y_root",fltk_fl_Fl_event_y_root);
    register_block("__Fl_Fl_event_dx",fltk_fl_Fl_event_dx);
    register_block("__Fl_Fl_event_dy",fltk_fl_Fl_event_dy);
    register_block("__Fl_Fl_get_mouse",fltk_fl_Fl_get_mouse);
    register_block("__Fl_Fl_event_clicks",fltk_fl_Fl_event_clicks);
    register_block("__Fl_Fl_event_clicks_1",fltk_fl_Fl_event_clicks_1);
    register_block("__Fl_Fl_event_is_click",fltk_fl_Fl_event_is_click);
    register_block("__Fl_Fl_event_is_click_1",fltk_fl_Fl_event_is_click_1);
    register_block("__Fl_Fl_event_button",fltk_fl_Fl_event_button);
    register_block("__Fl_Fl_event_state",fltk_fl_Fl_event_state);
    register_block("__Fl_Fl_event_state_1",fltk_fl_Fl_event_state_1);
    register_block("__Fl_Fl_event_key",fltk_fl_Fl_event_key);
    register_block("__Fl_Fl_event_original_key",fltk_fl_Fl_event_original_key);
    register_block("__Fl_Fl_event_key_1",fltk_fl_Fl_event_key_1);
    register_block("__Fl_Fl_get_key",fltk_fl_Fl_get_key);
    register_block("__Fl_Fl_event_text",fltk_fl_Fl_event_text);
    register_block("__Fl_Fl_event_length",fltk_fl_Fl_event_length);
    register_block("__Fl_Fl_event_clipboard",fltk_fl_Fl_event_clipboard);
    register_block("__Fl_Fl_event_clipboard_type",fltk_fl_Fl_event_clipboard_type);
    register_block("__Fl_Fl_compose",fltk_fl_Fl_compose);
    register_block("__Fl_Fl_compose_reset",fltk_fl_Fl_compose_reset);
    register_block("__Fl_Fl_event_inside",fltk_fl_Fl_event_inside);
    register_block("__Fl_Fl_event_inside_1",fltk_fl_Fl_event_inside_1);
    register_block("__Fl_Fl_test_shortcut",fltk_fl_Fl_test_shortcut);
    register_block("__Fl_Fl_enable_im",fltk_fl_Fl_enable_im);
    register_block("__Fl_Fl_disable_im",fltk_fl_Fl_disable_im);
    register_block("__Fl_Fl_handle",fltk_fl_Fl_handle);
    register_block("__Fl_Fl_handle_",fltk_fl_Fl_handle_);
    register_block("__Fl_Fl_belowmouse",fltk_fl_Fl_belowmouse);
    register_block("__Fl_Fl_belowmouse_1",fltk_fl_Fl_belowmouse_1);
    register_block("__Fl_Fl_pushed",fltk_fl_Fl_pushed);
    register_block("__Fl_Fl_pushed_1",fltk_fl_Fl_pushed_1);
    register_block("__Fl_Fl_focus",fltk_fl_Fl_focus);
    register_block("__Fl_Fl_focus_1",fltk_fl_Fl_focus_1);
    register_block("__Fl_Fl_add_handler",fltk_fl_Fl_add_handler);
    register_block("__Fl_Fl_remove_handler",fltk_fl_Fl_remove_handler);
    register_block("__Fl_Fl_add_system_handler",fltk_fl_Fl_add_system_handler);
    register_block("__Fl_Fl_remove_system_handler",fltk_fl_Fl_remove_system_handler);
    register_block("__Fl_Fl_event_dispatch",fltk_fl_Fl_event_dispatch);
    register_block("__Fl_Fl_event_dispatch_1",fltk_fl_Fl_event_dispatch_1);
#if FLTK_ABI_VERSION >= 10303 || defined(FL_DOXYGEN)
    register_block("__Fl_Fl_copy",fltk_fl_Fl_copy);
#else
    register_block("__Fl_Fl_copy_1",fltk_fl_Fl_copy_1);
    register_block("__Fl_Fl_copy_2",fltk_fl_Fl_copy_2);
#endif
#if !(defined(__APPLE__) || defined(WIN32) || defined(FL_DOXYGEN)) && defined(copy_image)
    register_block("__Fl_Fl_copy_image",fltk_fl_Fl_copy_image);
#endif
#if FLTK_ABI_VERSION >= 10303 || defined(FL_DOXYGEN)
    register_block("__Fl_Fl_paste",fltk_fl_Fl_paste);
#else
    register_block("__Fl_Fl_paste_1",fltk_fl_Fl_paste_1);
    register_block("__Fl_Fl_paste_2",fltk_fl_Fl_paste_2);
#endif
    register_block("__Fl_Fl_add_clipboard_notify",fltk_fl_Fl_add_clipboard_notify);
    register_block("__Fl_Fl_remove_clipboard_notify",fltk_fl_Fl_remove_clipboard_notify);
    register_block("__Fl_Fl_clipboard_contains",fltk_fl_Fl_clipboard_contains);
    register_block("__Fl_Fl_clipboard_plain_text",fltk_fl_Fl_clipboard_plain_text);
    register_block("__Fl_Fl_clipboard_image",fltk_fl_Fl_clipboard_image);
    register_block("__Fl_Fl_dnd",fltk_fl_Fl_dnd);
    register_block("__Fl_Fl_selection_owner",fltk_fl_Fl_selection_owner);
    register_block("__Fl_Fl_selection_owner_1",fltk_fl_Fl_selection_owner_1);
    register_block("__Fl_Fl_selection",fltk_fl_Fl_selection);
    register_block("__Fl_Fl_paste_3",fltk_fl_Fl_paste_3);
    register_block("__Fl_Fl_x",fltk_fl_Fl_x);
    register_block("__Fl_Fl_y",fltk_fl_Fl_y);
    register_block("__Fl_Fl_w",fltk_fl_Fl_w);
    register_block("__Fl_Fl_h",fltk_fl_Fl_h);
    register_block("__Fl_Fl_screen_count",fltk_fl_Fl_screen_count);
    register_block("__Fl_Fl_screen_xywh",fltk_fl_Fl_screen_xywh);
    register_block("__Fl_Fl_screen_xywh_1",fltk_fl_Fl_screen_xywh_1);
    register_block("__Fl_Fl_screen_xywh_2",fltk_fl_Fl_screen_xywh_2);
    register_block("__Fl_Fl_screen_xywh_3",fltk_fl_Fl_screen_xywh_3);
    register_block("__Fl_Fl_screen_num",fltk_fl_Fl_screen_num);
    register_block("__Fl_Fl_screen_num_1",fltk_fl_Fl_screen_num_1);
    register_block("__Fl_Fl_screen_dpi",fltk_fl_Fl_screen_dpi);
    register_block("__Fl_Fl_screen_work_area",fltk_fl_Fl_screen_work_area);
    register_block("__Fl_Fl_screen_work_area_1",fltk_fl_Fl_screen_work_area_1);
    register_block("__Fl_Fl_screen_work_area_2",fltk_fl_Fl_screen_work_area_2);
    register_block("__Fl_Fl_set_color",fltk_fl_Fl_set_color);
    register_block("__Fl_Fl_set_color_1",fltk_fl_Fl_set_color_1);
    register_block("__Fl_Fl_get_color",fltk_fl_Fl_get_color);
    register_block("__Fl_Fl_get_color_1",fltk_fl_Fl_get_color_1);
    register_block("__Fl_Fl_free_color",fltk_fl_Fl_free_color);
    register_block("__Fl_Fl_get_font",fltk_fl_Fl_get_font);
    register_block("__Fl_Fl_get_font_name",fltk_fl_Fl_get_font_name);
    register_block("__Fl_Fl_get_font_sizes",fltk_fl_Fl_get_font_sizes);
    register_block("__Fl_Fl_set_font",fltk_fl_Fl_set_font);
    register_block("__Fl_Fl_set_font_1",fltk_fl_Fl_set_font_1);
    register_block("__Fl_Fl_set_fonts",fltk_fl_Fl_set_fonts);
    register_block("__Fl_Fl_set_labeltype",fltk_fl_Fl_set_labeltype);
#ifdef set_labeltype
    register_block("__Fl_Fl_set_labeltype_1",fltk_fl_Fl_set_labeltype_1);
#endif
    register_block("__Fl_Fl_get_boxtype",fltk_fl_Fl_get_boxtype);
    register_block("__Fl_Fl_set_boxtype",fltk_fl_Fl_set_boxtype);
    register_block("__Fl_Fl_set_boxtype_1",fltk_fl_Fl_set_boxtype_1);
    register_block("__Fl_Fl_box_dx",fltk_fl_Fl_box_dx);
    register_block("__Fl_Fl_box_dy",fltk_fl_Fl_box_dy);
    register_block("__Fl_Fl_box_dw",fltk_fl_Fl_box_dw);
    register_block("__Fl_Fl_box_dh",fltk_fl_Fl_box_dh);
    register_block("__Fl_Fl_draw_box_active",fltk_fl_Fl_draw_box_active);
    register_block("__Fl_Fl_box_color",fltk_fl_Fl_box_color);
    register_block("__Fl_Fl_set_box_color",fltk_fl_Fl_set_box_color);
    register_block("__Fl_Fl_set_abort",fltk_fl_Fl_set_abort);
    register_block("__Fl_Fl_default_atclose",fltk_fl_Fl_default_atclose);
    register_block("__Fl_Fl_set_atclose",fltk_fl_Fl_set_atclose);
    register_block("__Fl_Fl_event_shift",fltk_fl_Fl_event_shift);
    register_block("__Fl_Fl_event_ctrl",fltk_fl_Fl_event_ctrl);
    register_block("__Fl_Fl_event_command",fltk_fl_Fl_event_command);
    register_block("__Fl_Fl_event_alt",fltk_fl_Fl_event_alt);
    register_block("__Fl_Fl_event_buttons",fltk_fl_Fl_event_buttons);
    register_block("__Fl_Fl_event_button1",fltk_fl_Fl_event_button1);
    register_block("__Fl_Fl_event_button2",fltk_fl_Fl_event_button2);
    register_block("__Fl_Fl_event_button3",fltk_fl_Fl_event_button3);
    register_block("__Fl_Fl_set_idle",fltk_fl_Fl_set_idle);
    register_block("__Fl_Fl_grab_2",fltk_fl_Fl_grab_2);
    register_block("__Fl_Fl_release",fltk_fl_Fl_release);
    register_block("__Fl_Fl_visible_focus",fltk_fl_Fl_visible_focus);
    register_block("__Fl_Fl_visible_focus_1",fltk_fl_Fl_visible_focus_1);
    register_block("__Fl_Fl_dnd_text_ops",fltk_fl_Fl_dnd_text_ops);
    register_block("__Fl_Fl_dnd_text_ops_1",fltk_fl_Fl_dnd_text_ops_1);
    register_block("__Fl_Fl_lock",fltk_fl_Fl_lock);
    register_block("__Fl_Fl_unlock",fltk_fl_Fl_unlock);
    register_block("__Fl_Fl_awake",fltk_fl_Fl_awake);
    register_block("__Fl_Fl_awake_1",fltk_fl_Fl_awake_1);
    register_block("__Fl_Fl_thread_message",fltk_fl_Fl_thread_message);
    register_block("__Fl_Fl_delete_widget",fltk_fl_Fl_delete_widget);
    register_block("__Fl_Fl_do_widget_deletion",fltk_fl_Fl_do_widget_deletion);
    register_block("__Fl_Fl_watch_widget_pointer",fltk_fl_Fl_watch_widget_pointer);
    register_block("__Fl_Fl_release_widget_pointer",fltk_fl_Fl_release_widget_pointer);
    register_block("__Fl_Fl_clear_widget_pointer",fltk_fl_Fl_clear_widget_pointer);
    register_block("__Fl_Fl_use_high_res_GL",fltk_fl_Fl_use_high_res_GL);
    register_block("__Fl_Fl_use_high_res_GL_1",fltk_fl_Fl_use_high_res_GL_1);
#ifdef FLTK_HAVE_CAIRO
    register_block("__Fl_Fl_cairo_make_current",fltk_fl_Fl_cairo_make_current);
	register_block("__Fl_Fl_cairo_autolink_context",fltk_fl_Fl_cairo_autolink_context);
	register_block("__Fl_Fl_cairo_autolink_context_1",fltk_fl_Fl_cairo_autolink_context_1);
	register_block("__Fl_Fl_cairo_cc",fltk_fl_Fl_cairo_cc);
	register_block("__Fl_Fl_cairo_cc_1",fltk_fl_Fl_cairo_cc_1);
#endif
    /* Fl_Adjuster */
    register_block("__Fl_Widget_Tracker",fltk_fl_widget_tracker_Fl_Widget_Tracker);
    register_block("__Fl_Widget_Tracker_widget",fltk_fl_widget_tracker_widget);
    register_block("__Fl_Widget_Tracker_deleted",fltk_fl_widget_tracker_deleted);
    register_block("__Fl_Widget_Tracker_exists",fltk_fl_widget_tracker_exists);
    register_block("__Fl_Adjuster",fltk_fl_adjuster_Fl_Adjuster);
    register_block("__Fl_Adjuster_soft",fltk_fl_adjuster_soft);
    register_block("__Fl_Adjuster_soft_1",fltk_fl_adjuster_soft_1);
    /* fl_ask */
    register_block("__FL_BEEP_DEFAULT",fltk_FL_BEEP_DEFAULT);
    register_block("__FL_BEEP_MESSAGE",fltk_FL_BEEP_MESSAGE);
    register_block("__FL_BEEP_ERROR",fltk_FL_BEEP_ERROR);
    register_block("__FL_BEEP_QUESTION",fltk_FL_BEEP_QUESTION);
    register_block("__FL_BEEP_PASSWORD",fltk_FL_BEEP_PASSWORD);
    register_block("__fl_beep",fltk_fl_beep);
    register_block("__fl_message",fltk_fl_message);
    register_block("__fl_alert",fltk_fl_alert);
    register_block("__fl_ask",fltk_fl_ask);
    register_block("__fl_choice",fltk_fl_choice);
    register_block("__fl_input",fltk_fl_input);
    register_block("__fl_password",fltk_fl_password);
    register_block("__fl_message_icon",fltk_fl_message_icon);
    register_block("__fl_message_font_",fltk_fl_message_font_);
    register_block("__fl_message_size_",fltk_fl_message_size_);
    register_block("__fl_message_font",fltk_fl_message_font);
    /* Fl_Bitmap */
    register_block("__Fl_Bitmap",fltk_fl_bitmap_Fl_Bitmap);
    register_block("__Fl_Bitmap_1",fltk_fl_bitmap_Fl_Bitmap_1);
    register_block("__Fl_Bitmap_copy",fltk_fl_bitmap_copy);
    register_block("__Fl_Bitmap_copy_1",fltk_fl_bitmap_copy_1);
    register_block("__Fl_Bitmap_draw",fltk_fl_bitmap_draw);
    register_block("__Fl_Bitmap_draw_1",fltk_fl_bitmap_draw_1);
    register_block("__Fl_Bitmap_label",fltk_fl_bitmap_label);
    register_block("__Fl_Bitmap_label_1",fltk_fl_bitmap_label_1);
    register_block("__Fl_Bitmap_uncache",fltk_fl_bitmap_uncache);
    /* Fl_BMP_Image */
#ifdef Fl_BMP_Image
    register_block("__Fl_BMP_Image",fltk_fl_bmp_image_Fl_BMP_Image);
#endif
    /* Fl_Box*/
    register_block("__Fl_Box",fltk_fl_box_Fl_Box);
    register_block("__Fl_Box_1",fltk_fl_box_Fl_Box_1);
    register_block("__Fl_Box_handle",fltk_fl_box_handle);
    /* Fl_Browser */
    register_block("__Fl_Browser_remove",fltk_fl_browser_remove);
    register_block("__Fl_Browser_add",fltk_fl_browser_add);
    register_block("__Fl_Browser_insert",fltk_fl_browser_insert);
    register_block("__Fl_Browser_move",fltk_fl_browser_move);
    register_block("__Fl_Browser_load",fltk_fl_browser_load);
    register_block("__Fl_Browser_swap",fltk_fl_browser_swap);
    register_block("__Fl_Browser_clear",fltk_fl_browser_clear);
    register_block("__Fl_Browser_size",fltk_fl_browser_size);
    register_block("__Fl_Browser_size_1",fltk_fl_browser_size_1);
    register_block("__Fl_Browser_textsize",fltk_fl_browser_textsize);
    register_block("__Fl_Browser_textsize_1",fltk_fl_browser_textsize_1);
    register_block("__Fl_Browser_topline",fltk_fl_browser_topline);
    register_block("__Fl_Browser_TOP",fltk_fl_browser_TOP);
    register_block("__Fl_Browser_BOTTOM",fltk_fl_browser_BOTTOM);
    register_block("__Fl_Browser_MIDDLE",fltk_fl_browser_MIDDLE);
    register_block("__Fl_Browser_lineposition",fltk_fl_browser_lineposition);
    register_block("__Fl_Browser_topline_1",fltk_fl_browser_topline_1);
    register_block("__Fl_Browser_bottomline",fltk_fl_browser_bottomline);
    register_block("__Fl_Browser_middleline",fltk_fl_browser_middleline);
    register_block("__Fl_Browser_select",fltk_fl_browser_select);
    register_block("__Fl_Browser_selected",fltk_fl_browser_selected);
    register_block("__Fl_Browser_show",fltk_fl_browser_show);
    register_block("__Fl_Browser_show_1",fltk_fl_browser_show_1);
    register_block("__Fl_Browser_hide",fltk_fl_browser_hide);
    register_block("__Fl_Browser_hide_1",fltk_fl_browser_hide_1);
    register_block("__Fl_Browser_visible",fltk_fl_browser_visible);
    register_block("__Fl_Browser_value",fltk_fl_browser_value);
    register_block("__Fl_Browser_value_1",fltk_fl_browser_value_1);
    register_block("__Fl_Browser_text",fltk_fl_browser_text);
    register_block("__Fl_Browser_text_1",fltk_fl_browser_text_1);
    register_block("__Fl_Browser_data",fltk_fl_browser_data);
    register_block("__Fl_Browser_data_1",fltk_fl_browser_data_1);
    register_block("__Fl_Browser",fltk_fl_browser_Fl_Browser);
    register_block("__Fl_Browser_format_char",fltk_fl_browser_format_char);
    register_block("__Fl_Browser_format_char_1",fltk_fl_browser_format_char_1);
    register_block("__Fl_Browser_column_char",fltk_fl_browser_column_char);
    register_block("__Fl_Browser_column_char_1",fltk_fl_browser_column_char_1);
    register_block("__Fl_Browser_column_widths",fltk_fl_browser_column_widths);
    register_block("__Fl_Browser_column_widths_1",fltk_fl_browser_column_widths_1);
    register_block("__Fl_Browser_displayed",fltk_fl_browser_displayed);
    register_block("__Fl_Browser_make_visible",fltk_fl_browser_make_visible);
    register_block("__Fl_Browser_icon",fltk_fl_browser_icon);
    register_block("__Fl_Browser_icon_1",fltk_fl_browser_icon_1);
    register_block("__Fl_Browser_remove_icon",fltk_fl_browser_remove_icon);
    register_block("__Fl_Browser_replace",fltk_fl_browser_replace);
    register_block("__Fl_Browser_display",fltk_fl_browser_display);
    /* Fl_Browser_ */
    register_block("__Fl_Browser__handle",fltk_fl_browser__handle);
    register_block("__Fl_Browser__resize",fltk_fl_browser__resize);
    register_block("__Fl_Browser__deselect",fltk_fl_browser__deselect);
    register_block("__Fl_Browser__position",fltk_fl_browser__position);
    register_block("__Fl_Browser__position_1",fltk_fl_browser__position_1);
    register_block("__Fl_Browser__hposition",fltk_fl_browser__hposition);
    register_block("__Fl_Browser__hposition_1",fltk_fl_browser__hposition_1);
    register_block("__Fl_Browser__display",fltk_fl_browser__display);
    register_block("__Fl_Browser__HORIZONTAL",fltk_fl_browser__HORIZONTAL);
    register_block("__Fl_Browser__VERTICAL",fltk_fl_browser__VERTICAL);
    register_block("__Fl_Browser__BOTH",fltk_fl_browser__BOTH);
    register_block("__Fl_Browser__ALWAYS_ON",fltk_fl_browser__ALWAYS_ON);
    register_block("__Fl_Browser__HORIZONTAL_ALWAYS",fltk_fl_browser__HORIZONTAL_ALWAYS);
    register_block("__Fl_Browser__VERTICAL_ALWAYS",fltk_fl_browser__VERTICAL_ALWAYS);
    register_block("__Fl_Browser__BOTH_ALWAYS",fltk_fl_browser__BOTH_ALWAYS);
    register_block("__Fl_Browser__has_scrollbar",fltk_fl_browser__has_scrollbar);
    register_block("__Fl_Browser__has_scrollbar_1",fltk_fl_browser__has_scrollbar_1);
    register_block("__Fl_Browser__textfont",fltk_fl_browser__textfont);
    register_block("__Fl_Browser__textfont_1",fltk_fl_browser__textfont_1);
    register_block("__Fl_Browser__textsize",fltk_fl_browser__textsize);
    register_block("__Fl_Browser__textsize_1",fltk_fl_browser__textsize_1);
    register_block("__Fl_Browser__textcolor",fltk_fl_browser__textcolor);
    register_block("__Fl_Browser__textcolor_1",fltk_fl_browser__textcolor_1);
    register_block("__Fl_Browser__scrollbar_size",fltk_fl_browser__scrollbar_size);
    register_block("__Fl_Browser__scrollbar_size_1",fltk_fl_browser__scrollbar_size_1);
    register_block("__Fl_Browser__scrollbar_width",fltk_fl_browser__scrollbar_width);
    register_block("__Fl_Browser__scrollbar_width_1",fltk_fl_browser__scrollbar_width_1);
    register_block("__Fl_Browser__scrollbar_right",fltk_fl_browser__scrollbar_right);
    register_block("__Fl_Browser__scrollbar_left",fltk_fl_browser__scrollbar_left);
    register_block("__Fl_Browser__sort",fltk_fl_browser__sort);
    /* Fl_Button */
    register_block("__fl_old_shortcut",fltk_fl_old_shortcut);
    register_block("__Fl_Button_handle",fltk_fl_button_handle);
    register_block("__Fl_Button",fltk_fl_button_Fl_Button);
    register_block("__Fl_Button_value",fltk_fl_button_value);
    register_block("__Fl_Button_value_1",fltk_fl_button_value_1);
    register_block("__Fl_Button_set",fltk_fl_button_set);
    register_block("__Fl_Button_clear",fltk_fl_button_clear);
    register_block("__Fl_Button_setonly",fltk_fl_button_setonly);
    register_block("__Fl_Button_shortcut",fltk_fl_button_shortcut);
    register_block("__Fl_Button_shortcut_1",fltk_fl_button_shortcut_1);
    register_block("__Fl_Button_down_box",fltk_fl_button_down_box);
    register_block("__Fl_Button_down_box_1",fltk_fl_button_down_box_1);
    register_block("__Fl_Button_shortcut_2",fltk_fl_button_shortcut_2);
    register_block("__Fl_Button_down_color",fltk_fl_button_down_color);
    register_block("__Fl_Button_down_color_1",fltk_fl_button_down_color_1);
#ifdef FLTK_HAVE_CAIRO
    register_block("__Fl_Cairo_State",fltk_fl_cairo_state_Fl_Cairo_State);
	register_block("__Fl_Cairo_State_cc",fltk_fl_cairo_state_cc);
	register_block("__Fl_Cairo_State_autolink",fltk_fl_cairo_state_autolink);
	register_block("__Fl_Cairo_State_cc_1",fltk_fl_cairo_state_cc_1);
	register_block("__Fl_Cairo_State_autolink_1",fltk_fl_cairo_state_autolink_1);
	register_block("__Fl_Cairo_State_window",fltk_fl_cairo_state_window);
	register_block("__Fl_Cairo_State_window_1",fltk_fl_cairo_state_window_1);
	register_block("__Fl_Cairo_State_gc",fltk_fl_cairo_state_gc);
	register_block("__Fl_Cairo_State_gc_1",fltk_fl_cairo_state_gc_1);
	register_block("__Fl_Cairo_Window",fltk_fl_cairo_window_Fl_Cairo_Window);
	register_block("__Fl_Cairo_Window_set_draw_cb",fltk_fl_cairo_window_set_draw_cb);
#endif
    /* Fl_Chart */
    register_block("__Fl_Chart",fltk_fl_chart_Fl_Chart);
    register_block("__Fl_Chart_clear",fltk_fl_chart_clear);
    register_block("__Fl_Chart_add",fltk_fl_chart_add);
    register_block("__Fl_Chart_insert",fltk_fl_chart_insert);
    register_block("__Fl_Chart_replace",fltk_fl_chart_replace);
    register_block("__Fl_Chart_bounds",fltk_fl_chart_bounds);
    register_block("__Fl_Chart_bounds_1",fltk_fl_chart_bounds_1);
    register_block("__Fl_Chart_size",fltk_fl_chart_size);
    register_block("__Fl_Chart_size_1",fltk_fl_chart_size_1);
    register_block("__Fl_Chart_maxsize",fltk_fl_chart_maxsize);
    register_block("__Fl_Chart_maxsize_1",fltk_fl_chart_maxsize_1);
    register_block("__Fl_Chart_textfont",fltk_fl_chart_textfont);
    register_block("__Fl_Chart_textfont_1",fltk_fl_chart_textfont_1);
    register_block("__Fl_Chart_textsize",fltk_fl_chart_textsize);
    register_block("__Fl_Chart_textsize_1",fltk_fl_chart_textsize_1);
    register_block("__Fl_Chart_textcolor",fltk_fl_chart_textcolor);
    register_block("__Fl_Chart_textcolor_1",fltk_fl_chart_textcolor_1);
    register_block("__Fl_Chart_autosize",fltk_fl_chart_autosize);
    register_block("__Fl_Chart_autosize_1",fltk_fl_chart_autosize_1);
    /* Fl_Check_Browser */
    register_block("__Fl_Check_Browser",fltk_fl_check_browser_Fl_Check_Browser);
    register_block("__Fl_Check_Browser_add_1",fltk_fl_check_browser_add_1);
    register_block("__Fl_Check_Browser_add_2",fltk_fl_check_browser_add_2);
    register_block("__Fl_Check_Browser_remove",fltk_fl_check_browser_remove);
    register_block("__Fl_Check_Browser_add_3",fltk_fl_check_browser_add_3);
    register_block("__Fl_Check_Browser_add_4",fltk_fl_check_browser_add_4);
    register_block("__Fl_Check_Browser_clear_1",fltk_fl_check_browser_clear_1);
    register_block("__Fl_Check_Browser_nitems",fltk_fl_check_browser_nitems);
    register_block("__Fl_Check_Browser_nchecked",fltk_fl_check_browser_nchecked);
    register_block("__Fl_Check_Browser_checked",fltk_fl_check_browser_checked);
    register_block("__Fl_Check_Browser_checked_1",fltk_fl_check_browser_checked_1);
    register_block("__Fl_Check_Browser_set_checked",fltk_fl_check_browser_set_checked);
    register_block("__Fl_Check_Browser_check_all",fltk_fl_check_browser_check_all);
    register_block("__Fl_Check_Browser_check_none",fltk_fl_check_browser_check_none);
    register_block("__Fl_Check_Browser_value",fltk_fl_check_browser_value);
    register_block("__Fl_Check_Browser_text",fltk_fl_check_browser_text);
    /* Fl_Check_Button */
    register_block("__Fl_Check_Button",fltk_fl_check_button_Fl_Check_Button);
    register_block("__Fl_Choice_handle",fltk_fl_choice_handle);
    /* Fl_Choice */
    register_block("__Fl_Choice",fltk_fl_choice_Fl_Choice);
    register_block("__Fl_Choice_value_1",fltk_fl_choice_value_1);
    register_block("__Fl_Choice_value_2",fltk_fl_choice_value_2);
    register_block("__Fl_Choice_value_3",fltk_fl_choice_value_3);
    /* Fl_Clock_Output */
    register_block("__Fl_Clock_Output",fltk_fl_clock_output_Fl_Clock_Output);
    register_block("__Fl_Clock_Output_value",fltk_fl_clock_output_value);
    register_block("__Fl_Clock_Output_value_1",fltk_fl_clock_output_value_1);
    register_block("__Fl_Clock_Output_value_2",fltk_fl_clock_output_value_2);
    register_block("__Fl_Clock_Output_hour",fltk_fl_clock_output_hour);
    register_block("__Fl_Clock_Output_minute",fltk_fl_clock_output_minute);
    /* Fl_Clock */
    register_block("__Fl_Clock_Output_second",fltk_fl_clock_output_second);
    register_block("__Fl_Clock_handle",fltk_fl_clock_handle);
    register_block("__Fl_Clock",fltk_fl_clock_Fl_Clock);
    register_block("__Fl_Clock_1",fltk_fl_clock_Fl_Clock_1);
    /* Flcc_HueBox */
    register_block("__Flcc_HueBox_handle_1",fltk_flcc_huebox_handle_1);
    register_block("__Flcc_HueBox",fltk_flcc_huebox_Flcc_HueBox);
    /* Flcc_ValueBox */
    register_block("__Flcc_ValueBox_handle_2",fltk_flcc_valuebox_handle_2);
    register_block("__Flcc_ValueBox",fltk_flcc_valuebox_Flcc_ValueBox);
    register_block("__Flcc_Value_Input_format",fltk_flcc_value_input_format);
    register_block("__Flcc_Value_Input",fltk_flcc_value_input_Flcc_Value_Input);
    /* Fl_Color_Chooser */
    register_block("__Fl_Color_Chooser_mode",fltk_fl_color_chooser_mode);
    register_block("__Fl_Color_Chooser_mode_1",fltk_fl_color_chooser_mode_1);
    register_block("__Fl_Color_Chooser_hue",fltk_fl_color_chooser_hue);
    register_block("__Fl_Color_Chooser_saturation",fltk_fl_color_chooser_saturation);
    register_block("__Fl_Color_Chooser_value_3",fltk_fl_color_chooser_value_3);
    register_block("__Fl_Color_Chooser_r",fltk_fl_color_chooser_r);
    register_block("__Fl_Color_Chooser_g",fltk_fl_color_chooser_g);
    register_block("__Fl_Color_Chooser_b",fltk_fl_color_chooser_b);
    register_block("__Fl_Color_Chooser_hsv",fltk_fl_color_chooser_hsv);
    register_block("__Fl_Color_Chooser_rgb",fltk_fl_color_chooser_rgb);
    register_block("__Fl_Color_Chooser_Fl_Color_Chooser_hsv2rgb",fltk_fl_color_chooser_Fl_Color_Chooser_hsv2rgb);
    register_block("__Fl_Color_Chooser_Fl_Color_Chooser_rgb2hsv",fltk_fl_color_chooser_Fl_Color_Chooser_rgb2hsv);
    register_block("__Fl_Color_Chooser",fltk_fl_color_chooser_Fl_Color_Chooser);
    register_block("__Fl_Color_Chooser_fl_color_chooser",fltk_fl_color_chooser_fl_color_chooser);
    register_block("__Fl_Color_Chooser_fl_color_chooser_1",fltk_fl_color_chooser_fl_color_chooser_1);
    /* Fl_Copy_Surface */
#ifdef Fl_Copy_Surface::class_id
    //register_block("__Fl_Copy_Surface_Fl_Copy_Surface_class_id",fltk_fl_copy_surface_Fl_Copy_Surface_class_id);
	//register_block("__Fl_Copy_Surface_class_name",fltk_fl_copy_surface_class_name);
#endif
    register_block("__Fl_Copy_Surface",fltk_fl_copy_surface_Fl_Copy_Surface);
    register_block("__Fl_Copy_Surface_set_current",fltk_fl_copy_surface_set_current);
    register_block("__Fl_Copy_Surface_draw",fltk_fl_copy_surface_draw);
    register_block("__Fl_Copy_Surface_draw_decorated_window",fltk_fl_copy_surface_draw_decorated_window);
    register_block("__Fl_Copy_Surface_w",fltk_fl_copy_surface_w);
    register_block("__Fl_Copy_Surface_h",fltk_fl_copy_surface_h);
    /* Fl_Quartz_Surface_ */
#if defined(__APPLE__)
    //register_block("__Fl_Quartz_Surface__class_name_1",fltk_fl_quartz_surface__class_name_1);
	register_block("__Fl_Quartz_Surface_",fltk_fl_quartz_surface__Fl_Quartz_Surface_);
	register_block("__Fl_Quartz_Surface__printable_rect",fltk_fl_quartz_surface__printable_rect);
	/* Fl_GDI_Surface */
#elif defined(WIN32)
    //register_block("__Fl_GDI_Surface__class_name_2",fltk_fl_gdi_surface__class_name_2);
	register_block("__Fl_GDI_Surface_",fltk_fl_gdi_surface__Fl_GDI_Surface_);
	register_block("__Fl_GDI_Surface__translate",fltk_fl_gdi_surface__translate);
	register_block("__Fl_GDI_Surface__untranslate",fltk_fl_gdi_surface__untranslate);
	/* Fl_Xlib_Surface_ */
#elif !defined(FL_DOXYGEN) and !defined(__ANDROID__)
    //register_block("__Fl_Xlib_Surface__class_name_3",fltk_fl_xlib_surface__class_name_3);
    register_block("__Fl_Xlib_Surface_",fltk_fl_xlib_surface__Fl_Xlib_Surface_);
    register_block("__Fl_Xlib_Surface__translate_1",fltk_fl_xlib_surface__translate_1);
    register_block("__Fl_Xlib_Surface__untranslate_1",fltk_fl_xlib_surface__untranslate_1);
#endif
    /* Fl_Counter */
    register_block("__Fl_Counter_handle_3",fltk_fl_counter_handle_3);
    register_block("__Fl_Counter",fltk_fl_counter_Fl_Counter);
    register_block("__Fl_Counter_lstep",fltk_fl_counter_lstep);
    register_block("__Fl_Counter_step",fltk_fl_counter_step);
    register_block("__Fl_Counter_step_1",fltk_fl_counter_step_1);
    register_block("__Fl_Counter_step_2",fltk_fl_counter_step_2);
    register_block("__Fl_Counter_textfont",fltk_fl_counter_textfont);
    register_block("__Fl_Counter_textfont_1",fltk_fl_counter_textfont_1);
    register_block("__Fl_Counter_textsize",fltk_fl_counter_textsize);
    register_block("__Fl_Counter_textsize_1",fltk_fl_counter_textsize_1);
    register_block("__Fl_Counter_textcolor",fltk_fl_counter_textcolor);
    register_block("__Fl_Counter_textcolor_1",fltk_fl_counter_textcolor_1);
#ifdef WIN32
#elif defined(__APPLE__)
    register_block("__fl_quartz_line_width_",fltk_fl_quartz_line_width_);
#endif
    /* Fl_Device */
#ifndef __ANDROID__
    //register_block("__Fl_Device_Fl_Device_class_id",fltk_fl_device_Fl_Device_class_id);
	//register_block("__Fl_Device_class_name",fltk_fl_device_class_name);
#endif
    /* Fl_Dial */
    register_block("__Fl_Dial_handle",fltk_fl_dial_handle);
    register_block("__Fl_Dial",fltk_fl_dial_Fl_Dial);
    register_block("__Fl_Dial_angle1",fltk_fl_dial_angle1);
    register_block("__Fl_Dial_angle1_1",fltk_fl_dial_angle1_1);
    register_block("__Fl_Dial_angle2",fltk_fl_dial_angle2);
    register_block("__Fl_Dial_angle2_1",fltk_fl_dial_angle2_1);
    register_block("__Fl_Dial_angles",fltk_fl_dial_angles);
    /* Fl_Double_Window */
    register_block("__Fl_Double_Window_show",fltk_fl_double_window_show);
    register_block("__Fl_Double_Window_show_1",fltk_fl_double_window_show_1);
    register_block("__Fl_Double_Window_flush",fltk_fl_double_window_flush);
    register_block("__Fl_Double_Window_resize",fltk_fl_double_window_resize);
    register_block("__Fl_Double_Window_hide",fltk_fl_double_window_hide);
    register_block("__Fl_Double_Window",fltk_fl_double_window_Fl_Double_Window);
    register_block("__Fl_Double_Window_1",fltk_fl_double_window_Fl_Double_Window_1);
    /* fl_draw */
    register_block("__fl_draw_shortcut",fltk_fl_draw_shortcut);
    register_block("__fl_color",fltk_fl_color);
    register_block("__fl_color_1",fltk_fl_color_1);
    register_block("__fl_color_2",fltk_fl_color_2);
    register_block("__fl_color_3",fltk_fl_color_3);
    register_block("__fl_push_clip",fltk_fl_push_clip);
    register_block("__fl_push_no_clip",fltk_fl_push_no_clip);
    register_block("__fl_pop_clip",fltk_fl_pop_clip);
    register_block("__fl_not_clipped",fltk_fl_not_clipped);
    register_block("__fl_clip_box",fltk_fl_clip_box);
    register_block("__fl_restore_clip",fltk_fl_restore_clip);
    register_block("__fl_clip_region",fltk_fl_clip_region);
    register_block("__fl_clip_region_1",fltk_fl_clip_region_1);
    register_block("__fl_point",fltk_fl_point);
    register_block("__fl_line_style",fltk_fl_line_style);
    register_block("__FL_SOLID",fltk_FL_SOLID);
    register_block("__FL_DASH",fltk_FL_DASH);
    register_block("__FL_DOT",fltk_FL_DOT);
    register_block("__FL_DASHDOT",fltk_FL_DASHDOT);
    register_block("__FL_DASHDOTDOT",fltk_FL_DASHDOTDOT);
    register_block("__FL_CAP_FLAT",fltk_FL_CAP_FLAT);
    register_block("__FL_CAP_ROUND",fltk_FL_CAP_ROUND);
    register_block("__FL_CAP_SQUARE",fltk_FL_CAP_SQUARE);
    register_block("__FL_JOIN_MITER",fltk_FL_JOIN_MITER);
    register_block("__FL_JOIN_ROUND",fltk_FL_JOIN_ROUND);
    register_block("__FL_JOIN_BEVEL",fltk_FL_JOIN_BEVEL);
    register_block("__fl_rect",fltk_fl_rect);
    register_block("__fl_rect_1",fltk_fl_rect_1);
    register_block("__fl_rectf",fltk_fl_rectf);
    register_block("__fl_rectf_1",fltk_fl_rectf_1);
    register_block("__fl_rectf_2",fltk_fl_rectf_2);
    register_block("__fl_line",fltk_fl_line);
    register_block("__fl_line_1",fltk_fl_line_1);
    register_block("__fl_loop",fltk_fl_loop);
    register_block("__fl_loop_1",fltk_fl_loop_1);
    register_block("__fl_polygon",fltk_fl_polygon);
    register_block("__fl_polygon_1",fltk_fl_polygon_1);
    register_block("__fl_xyline",fltk_fl_xyline);
    register_block("__fl_xyline_1",fltk_fl_xyline_1);
    register_block("__fl_xyline_2",fltk_fl_xyline_2);
    register_block("__fl_yxline",fltk_fl_yxline);
    register_block("__fl_yxline_1",fltk_fl_yxline_1);
    register_block("__fl_yxline_2",fltk_fl_yxline_2);
    register_block("__fl_arc",fltk_fl_arc);
    register_block("__fl_pie",fltk_fl_pie);
#ifdef fl_chord
    register_block("__fl_chord",fltk_fl_chord);
#endif
    register_block("__fl_push_matrix",fltk_fl_push_matrix);
    register_block("__fl_pop_matrix",fltk_fl_pop_matrix);
    register_block("__fl_scale",fltk_fl_scale);
    register_block("__fl_scale_1",fltk_fl_scale_1);
    register_block("__fl_translate",fltk_fl_translate);
    register_block("__fl_rotate",fltk_fl_rotate);
    register_block("__fl_mult_matrix",fltk_fl_mult_matrix);
    register_block("__fl_begin_points",fltk_fl_begin_points);
    register_block("__fl_begin_line",fltk_fl_begin_line);
    register_block("__fl_begin_loop",fltk_fl_begin_loop);
    register_block("__fl_begin_polygon",fltk_fl_begin_polygon);
    register_block("__fl_vertex",fltk_fl_vertex);
    register_block("__fl_curve",fltk_fl_curve);
    register_block("__fl_arc_1",fltk_fl_arc_1);
    register_block("__fl_circle",fltk_fl_circle);
    register_block("__fl_end_points",fltk_fl_end_points);
    register_block("__fl_end_line",fltk_fl_end_line);
    register_block("__fl_end_loop",fltk_fl_end_loop);
    register_block("__fl_end_polygon",fltk_fl_end_polygon);
    register_block("__fl_begin_complex_polygon",fltk_fl_begin_complex_polygon);
    register_block("__fl_gap",fltk_fl_gap);
    register_block("__fl_end_complex_polygon",fltk_fl_end_complex_polygon);
    register_block("__fl_transform_x",fltk_fl_transform_x);
    register_block("__fl_transform_y",fltk_fl_transform_y);
    register_block("__fl_transform_dx",fltk_fl_transform_dx);
    register_block("__fl_transform_dy",fltk_fl_transform_dy);
    register_block("__fl_transformed_vertex",fltk_fl_transformed_vertex);
    register_block("__fl_font",fltk_fl_font);
    register_block("__fl_font_1",fltk_fl_font_1);
    register_block("__fl_size",fltk_fl_size);
    register_block("__fl_height",fltk_fl_height);
    register_block("__fl_height_1",fltk_fl_height_1);
    register_block("__fl_descent",fltk_fl_descent);
    register_block("__fl_width",fltk_fl_width);
    register_block("__fl_width_1",fltk_fl_width_1);
    register_block("__fl_width_2",fltk_fl_width_2);
    register_block("__fl_text_extents",fltk_fl_text_extents);
    register_block("__fl_text_extents_1",fltk_fl_text_extents_1);
#ifdef fl_latin1_to_local
    register_block("__fl_latin1_to_local",fltk_fl_latin1_to_local);
#endif
#ifdef fl_local_to_latin1
    register_block("__fl_local_to_latin1",fltk_fl_local_to_latin1);
#endif
#ifdef fltk_fl_mac_roman_to_local
    register_block("__fl_mac_roman_to_local",fltk_fl_mac_roman_to_local);
#endif
#ifdef fl_local_to_mac_roman
    register_block("__fl_local_to_mac_roman",fltk_fl_local_to_mac_roman);
#endif
    register_block("__fl_draw",fltk_fl_draw);
    register_block("__fl_draw_1",fltk_fl_draw_1);
    register_block("__fl_draw_2",fltk_fl_draw_2);
    register_block("__fl_draw_3",fltk_fl_draw_3);
    register_block("__fl_rtl_draw",fltk_fl_rtl_draw);
    register_block("__fl_measure",fltk_fl_measure);
    register_block("__fl_draw_4",fltk_fl_draw_4);
    register_block("__fl_frame1",fltk_fl_frame1);
    register_block("__fl_frame2",fltk_fl_frame2);
    register_block("__fl_draw_box",fltk_fl_draw_box);
    register_block("__fl_draw_image",fltk_fl_draw_image);
    register_block("__fl_draw_image_mono",fltk_fl_draw_image_mono);
    register_block("__fl_draw_image_1",fltk_fl_draw_image_1);
    register_block("__fl_draw_image_mono_1",fltk_fl_draw_image_mono_1);
    register_block("__fl_can_do_alpha_blending",fltk_fl_can_do_alpha_blending);
    register_block("__fl_measure_pixmap_1",fltk_fl_measure_pixmap_1);
    register_block("__fl_shortcut_label",fltk_fl_shortcut_label);
    register_block("__fl_shortcut_label_1",fltk_fl_shortcut_label_1);
    register_block("__fl_old_shortcut_draw",fltk_fl_old_shortcut_draw);
    register_block("__fl_overlay_rect",fltk_fl_overlay_rect);
    register_block("__fl_overlay_clear",fltk_fl_overlay_clear);
    register_block("__fl_cursor",fltk_fl_cursor);
    register_block("__fl_cursor_1",fltk_fl_cursor_1);
    register_block("__fl_expand_text",fltk_fl_expand_text);
#ifndef __ANDROID__
    register_block("__fl_set_status",fltk_fl_set_status);
#endif
    register_block("__fl_set_spot",fltk_fl_set_spot);
    register_block("__fl_reset_spot",fltk_fl_reset_spot);
    register_block("__fl_draw_symbol",fltk_fl_draw_symbol);
    /* Fl_File_Browser */
    register_block("__Fl_File_Browser_DIRECTORIES",fltk_fl_file_browser_DIRECTORIES);
    register_block("__Fl_File_Browser",fltk_fl_file_browser_Fl_File_Browser);
    register_block("__Fl_File_Browser_iconsize",fltk_fl_file_browser_iconsize);
    register_block("__Fl_File_Browser_iconsize_1",fltk_fl_file_browser_iconsize_1);
    register_block("__Fl_File_Browser_filter",fltk_fl_file_browser_filter);
    register_block("__Fl_File_Browser_filter_1",fltk_fl_file_browser_filter_1);
    register_block("__Fl_File_Browser_load",fltk_fl_file_browser_load);
    register_block("__Fl_File_Browser_textsize",fltk_fl_file_browser_textsize);
    register_block("__Fl_File_Browser_textsize_1",fltk_fl_file_browser_textsize_1);
    register_block("__Fl_File_Browser_filetype",fltk_fl_file_browser_filetype);
    register_block("__Fl_File_Browser_filetype_1",fltk_fl_file_browser_filetype_1);
    /* Fl_File_Chooser */
    register_block("__Fl_File_Chooser_SINGLE",fltk_fl_file_chooser_SINGLE);
    register_block("__Fl_File_Chooser_MULTI",fltk_fl_file_chooser_MULTI);
    register_block("__Fl_File_Chooser_CREATE",fltk_fl_file_chooser_CREATE);
    register_block("__Fl_File_Chooser_DIRECTORY",fltk_fl_file_chooser_DIRECTORY);
    register_block("__Fl_File_Chooser",fltk_fl_file_chooser_Fl_File_Chooser);
    register_block("__Fl_File_Chooser_color",fltk_fl_file_chooser_color);
    register_block("__Fl_File_Chooser_color_1",fltk_fl_file_chooser_color_1);
    register_block("__Fl_File_Chooser_count",fltk_fl_file_chooser_count);
    register_block("__Fl_File_Chooser_directory",fltk_fl_file_chooser_directory);
    register_block("__Fl_File_Chooser_directory_1",fltk_fl_file_chooser_directory_1);
    register_block("__Fl_File_Chooser_filter_2",fltk_fl_file_chooser_filter_2);
    register_block("__Fl_File_Chooser_filter_3",fltk_fl_file_chooser_filter_3);
    register_block("__Fl_File_Chooser_filter_value",fltk_fl_file_chooser_filter_value);
    register_block("__Fl_File_Chooser_filter_value_1",fltk_fl_file_chooser_filter_value_1);
    register_block("__Fl_File_Chooser_hide",fltk_fl_file_chooser_hide);
    register_block("__Fl_File_Chooser_iconsize_2",fltk_fl_file_chooser_iconsize_2);
    register_block("__Fl_File_Chooser_iconsize_3",fltk_fl_file_chooser_iconsize_3);
    register_block("__Fl_File_Chooser_label",fltk_fl_file_chooser_label);
    register_block("__Fl_File_Chooser_label_1",fltk_fl_file_chooser_label_1);
    register_block("__Fl_File_Chooser_ok_label",fltk_fl_file_chooser_ok_label);
    register_block("__Fl_File_Chooser_ok_label_1",fltk_fl_file_chooser_ok_label_1);
    register_block("__Fl_File_Chooser_preview",fltk_fl_file_chooser_preview);
    register_block("__Fl_File_Chooser_preview_1",fltk_fl_file_chooser_preview_1);
    register_block("__Fl_File_Chooser_rescan",fltk_fl_file_chooser_rescan);
    register_block("__Fl_File_Chooser_rescan_keep_filename",fltk_fl_file_chooser_rescan_keep_filename);
    register_block("__Fl_File_Chooser_show",fltk_fl_file_chooser_show);
    register_block("__Fl_File_Chooser_shown",fltk_fl_file_chooser_shown);
    register_block("__Fl_File_Chooser_textcolor",fltk_fl_file_chooser_textcolor);
    register_block("__Fl_File_Chooser_textcolor_1",fltk_fl_file_chooser_textcolor_1);
    register_block("__Fl_File_Chooser_textfont",fltk_fl_file_chooser_textfont);
    register_block("__Fl_File_Chooser_textfont_1",fltk_fl_file_chooser_textfont_1);
    register_block("__Fl_File_Chooser_textsize_2",fltk_fl_file_chooser_textsize_2);
    register_block("__Fl_File_Chooser_textsize_3",fltk_fl_file_chooser_textsize_3);
    register_block("__Fl_File_Chooser_type",fltk_fl_file_chooser_type);
    register_block("__Fl_File_Chooser_type_1",fltk_fl_file_chooser_type_1);
    register_block("__Fl_File_Chooser_user_data",fltk_fl_file_chooser_user_data);
    register_block("__Fl_File_Chooser_user_data_1",fltk_fl_file_chooser_user_data_1);
    register_block("__Fl_File_Chooser_value",fltk_fl_file_chooser_value);
    register_block("__Fl_File_Chooser_value_1",fltk_fl_file_chooser_value_1);
    register_block("__Fl_File_Chooser_visible",fltk_fl_file_chooser_visible);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_add_favorites_label",fltk_fl_file_chooser_Fl_File_Chooser_add_favorites_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_all_files_label",fltk_fl_file_chooser_Fl_File_Chooser_all_files_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_custom_filter_label",fltk_fl_file_chooser_Fl_File_Chooser_custom_filter_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_existing_file_label",fltk_fl_file_chooser_Fl_File_Chooser_existing_file_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_favorites_label",fltk_fl_file_chooser_Fl_File_Chooser_favorites_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_filename_label",fltk_fl_file_chooser_Fl_File_Chooser_filename_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_filesystems_label",fltk_fl_file_chooser_Fl_File_Chooser_filesystems_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_manage_favorites_label",fltk_fl_file_chooser_Fl_File_Chooser_manage_favorites_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_new_directory_label",fltk_fl_file_chooser_Fl_File_Chooser_new_directory_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_new_directory_tooltip",fltk_fl_file_chooser_Fl_File_Chooser_new_directory_tooltip);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_preview_label",fltk_fl_file_chooser_Fl_File_Chooser_preview_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_save_label",fltk_fl_file_chooser_Fl_File_Chooser_save_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_show_label",fltk_fl_file_chooser_Fl_File_Chooser_show_label);
    register_block("__Fl_File_Chooser_Fl_File_Chooser_hidden_label",fltk_fl_file_chooser_Fl_File_Chooser_hidden_label);
    register_block("__Fl_File_Chooser_add_extra",fltk_fl_file_chooser_add_extra);
    register_block("__Fl_File_Chooser_fl_file_chooser_ok_label",fltk_fl_file_chooser_fl_file_chooser_ok_label);
    /* Fl_File_Icon */
    register_block("__Fl_File_Icon_ANY",fltk_fl_file_icon_ANY);
    register_block("__Fl_File_Icon_PLAIN",fltk_fl_file_icon_PLAIN);
    register_block("__Fl_File_Icon_FIFO",fltk_fl_file_icon_FIFO);
    register_block("__Fl_File_Icon_DEVICE",fltk_fl_file_icon_DEVICE);
    register_block("__Fl_File_Icon_LINK",fltk_fl_file_icon_LINK);
    register_block("__Fl_File_Icon_END",fltk_fl_file_icon_END);
    register_block("__Fl_File_Icon_COLOR",fltk_fl_file_icon_COLOR);
    register_block("__Fl_File_Icon_LINE",fltk_fl_file_icon_LINE);
    register_block("__Fl_File_Icon_CLOSEDLINE",fltk_fl_file_icon_CLOSEDLINE);
    register_block("__Fl_File_Icon_POLYGON",fltk_fl_file_icon_POLYGON);
    register_block("__Fl_File_Icon_OUTLINEPOLYGON",fltk_fl_file_icon_OUTLINEPOLYGON);
    register_block("__Fl_File_Icon",fltk_fl_file_icon_Fl_File_Icon);
    register_block("__Fl_File_Icon_add",fltk_fl_file_icon_add);
    register_block("__Fl_File_Icon_add_color",fltk_fl_file_icon_add_color);
    register_block("__Fl_File_Icon_add_vertex",fltk_fl_file_icon_add_vertex);
    register_block("__Fl_File_Icon_add_vertex_1",fltk_fl_file_icon_add_vertex_1);
    register_block("__Fl_File_Icon_clear",fltk_fl_file_icon_clear);
    register_block("__Fl_File_Icon_draw",fltk_fl_file_icon_draw);
    register_block("__Fl_File_Icon_label",fltk_fl_file_icon_label);
    register_block("__Fl_File_Icon_Fl_File_Icon_labeltype",fltk_fl_file_icon_Fl_File_Icon_labeltype);
#ifndef __ANDROID__
    register_block("__Fl_File_Icon_load",fltk_fl_file_icon_load);
	register_block("__Fl_File_Icon_load_fti",fltk_fl_file_icon_load_fti);
	register_block("__Fl_File_Icon_load_image",fltk_fl_file_icon_load_image);
#endif
    register_block("__Fl_File_Icon_next",fltk_fl_file_icon_next);
    register_block("__Fl_File_Icon_pattern",fltk_fl_file_icon_pattern);
    register_block("__Fl_File_Icon_size",fltk_fl_file_icon_size);
    register_block("__Fl_File_Icon_type",fltk_fl_file_icon_type);
    register_block("__Fl_File_Icon_value",fltk_fl_file_icon_value);
    register_block("__Fl_File_Icon_Fl_File_Icon_find",fltk_fl_file_icon_Fl_File_Icon_find);
    register_block("__Fl_File_Icon_Fl_File_Icon_first",fltk_fl_file_icon_Fl_File_Icon_first);
#ifndef __ANDROID__
    register_block("__Fl_File_Icon_Fl_File_Icon_load_system_icons",fltk_fl_file_icon_Fl_File_Icon_load_system_icons);
#endif
    /* Fl_File_Input */
    register_block("__Fl_File_Input",fltk_fl_file_input_Fl_File_Input);
    register_block("__Fl_File_Input_handle",fltk_fl_file_input_handle);
    register_block("__Fl_File_Input_down_box",fltk_fl_file_input_down_box);
    register_block("__Fl_File_Input_down_box_1",fltk_fl_file_input_down_box_1);
    register_block("__Fl_File_Input_errorcolor",fltk_fl_file_input_errorcolor);
    register_block("__Fl_File_Input_errorcolor_1",fltk_fl_file_input_errorcolor_1);
    register_block("__Fl_File_Input_value_1",fltk_fl_file_input_value_1);
    register_block("__Fl_File_Input_value_2",fltk_fl_file_input_value_2);
    register_block("__Fl_File_Input_value_3",fltk_fl_file_input_value_3);
    /* Fl_Fill_Dial */
    register_block("__Fl_Fill_Dial",fltk_fl_fill_dial_Fl_Fill_Dial);
    /* Fl_Fill_Slider */
    register_block("__Fl_Fill_Slider",fltk_fl_fill_slider_Fl_Fill_Slider);
    /* Fl_Float_Input */
    register_block("__Fl_Float_Input",fltk_fl_float_input_Fl_Float_Input);
    /* Fl_FormsBitmap */
#ifndef __ANDROID__
    register_block("__Fl_FormsBitmap",fltk_fl_formsbitmap_Fl_FormsBitmap);
	register_block("__Fl_FormsBitmap_set",fltk_fl_formsbitmap_set);
	register_block("__Fl_FormsBitmap_bitmap",fltk_fl_formsbitmap_bitmap);
	register_block("__Fl_FormsBitmap_bitmap_1",fltk_fl_formsbitmap_bitmap_1);
	/* Fl_FormsPixmap */
	register_block("__Fl_FormsPixmap",fltk_fl_formspixmap_Fl_FormsPixmap);
	register_block("__Fl_FormsPixmap_set_1",fltk_fl_formspixmap_set_1);
	register_block("__Fl_FormsPixmap_Pixmap",fltk_fl_formspixmap_Pixmap);
	register_block("__Fl_FormsPixmap_Pixmap_1",fltk_fl_formspixmap_Pixmap_1);
#endif
    /* Fl_Free */
    register_block("__Fl_Free_handle",fltk_fl_free_handle);
#ifndef __ANDROID__
    register_block("__Fl_Free",fltk_fl_free_Fl_Free);
#endif
    /* Fl_GIF_Image */
#ifndef __ANDROID__
    register_block("__Fl_GIF_Image",fltk_fl_gif_image_Fl_GIF_Image);
#endif
    /* Fl_Gl_Window */
#ifdef SIMPLE_FLTK_USE_FLTKGL
    register_block("__Fl_Gl_Window_show",fltk_fl_gl_window_show);
	register_block("__Fl_Gl_Window_show_1",fltk_fl_gl_window_show_1);
	register_block("__Fl_Gl_Window_flush",fltk_fl_gl_window_flush);
	register_block("__Fl_Gl_Window_hide",fltk_fl_gl_window_hide);
	register_block("__Fl_Gl_Window_resize",fltk_fl_gl_window_resize);
	register_block("__Fl_Gl_Window_handle_1",fltk_fl_gl_window_handle_1);
	register_block("__Fl_Gl_Window_valid",fltk_fl_gl_window_valid);
	register_block("__Fl_Gl_Window_valid_1",fltk_fl_gl_window_valid_1);
	register_block("__Fl_Gl_Window_invalidate",fltk_fl_gl_window_invalidate);
	register_block("__Fl_Gl_Window_context_valid",fltk_fl_gl_window_context_valid);
	register_block("__Fl_Gl_Window_context_valid_1",fltk_fl_gl_window_context_valid_1);
	register_block("__Fl_Gl_Window_Fl_Gl_Window_can_do_1",fltk_fl_gl_window_Fl_Gl_Window_can_do_1);
	register_block("__Fl_Gl_Window_Fl_Gl_Window_can_do_2",fltk_fl_gl_window_Fl_Gl_Window_can_do_2);
	register_block("__Fl_Gl_Window_can_do",fltk_fl_gl_window_can_do);
	register_block("__Fl_Gl_Window_mode_1",fltk_fl_gl_window_mode_1);
	register_block("__Fl_Gl_Window_mode_2",fltk_fl_gl_window_mode_2);
	register_block("__Fl_Gl_Window_mode_3",fltk_fl_gl_window_mode_3);
	register_block("__Fl_Gl_Window_context",fltk_fl_gl_window_context);
	register_block("__Fl_Gl_Window_context_1",fltk_fl_gl_window_context_1);
	register_block("__Fl_Gl_Window_make_current",fltk_fl_gl_window_make_current);
	register_block("__Fl_Gl_Window_swap_buffers",fltk_fl_gl_window_swap_buffers);
	register_block("__Fl_Gl_Window_can_do_overlay",fltk_fl_gl_window_can_do_overlay);
	register_block("__Fl_Gl_Window_redraw_overlay",fltk_fl_gl_window_redraw_overlay);
	register_block("__Fl_Gl_Window_hide_overlay",fltk_fl_gl_window_hide_overlay);
	register_block("__Fl_Gl_Window_make_overlay_current",fltk_fl_gl_window_make_overlay_current);
	register_block("__Fl_Gl_Window_as_gl_window",fltk_fl_gl_window_as_gl_window);
	register_block("__Fl_Gl_Window_pixels_per_unit",fltk_fl_gl_window_pixels_per_unit);
	register_block("__Fl_Gl_Window_pixels_per_unit_1",fltk_fl_gl_window_pixels_per_unit_1);
	register_block("__Fl_Gl_Window_pixel_w",fltk_fl_gl_window_pixel_w);
	register_block("__Fl_Gl_Window_pixel_h",fltk_fl_gl_window_pixel_h);
	register_block("__Fl_Gl_Window",fltk_fl_gl_window_Fl_Gl_Window);
	register_block("__Fl_Gl_Window_1",fltk_fl_gl_window_Fl_Gl_Window_1);
#endif
    /* Fl_Group */
    register_block("__Fl_Group_handle",fltk_fl_group_handle);
    register_block("__Fl_Group_begin",fltk_fl_group_begin);
    register_block("__Fl_Group_end",fltk_fl_group_end);
    register_block("__Fl_Group_Fl_Group_current",fltk_fl_group_Fl_Group_current);
    register_block("__Fl_Group_Fl_Group_current_1",fltk_fl_group_Fl_Group_current_1);
    register_block("__Fl_Group_children",fltk_fl_group_children);
    register_block("__Fl_Group_child",fltk_fl_group_child);
    register_block("__Fl_Group_find",fltk_fl_group_find);
    register_block("__Fl_Group_find_1",fltk_fl_group_find_1);
    register_block("__Fl_Group_array",fltk_fl_group_array);
    register_block("__Fl_Group_resize",fltk_fl_group_resize);
    register_block("__Fl_Group_1",fltk_fl_group_Fl_Group_1);
    register_block("__Fl_Group_add",fltk_fl_group_add);
    register_block("__Fl_Group_add_1",fltk_fl_group_add_1);
    register_block("__Fl_Group_insert",fltk_fl_group_insert);
    register_block("__Fl_Group_insert_1",fltk_fl_group_insert_1);
    register_block("__Fl_Group_remove",fltk_fl_group_remove);
    register_block("__Fl_Group_remove_1",fltk_fl_group_remove_1);
    register_block("__Fl_Group_remove_2",fltk_fl_group_remove_2);
    register_block("__Fl_Group_clear",fltk_fl_group_clear);
    register_block("__Fl_Group_resizable",fltk_fl_group_resizable);
    register_block("__Fl_Group_not_resizable",fltk_fl_group_not_resizable);
    register_block("__Fl_Group_resizable_1",fltk_fl_group_resizable_1);
    register_block("__Fl_Group_resizable_2",fltk_fl_group_resizable_2);
    register_block("__Fl_Group_add_resizable",fltk_fl_group_add_resizable);
    register_block("__Fl_Group_init_sizes",fltk_fl_group_init_sizes);
    register_block("__Fl_Group_clip_children",fltk_fl_group_clip_children);
    register_block("__Fl_Group_clip_children_1",fltk_fl_group_clip_children_1);
    register_block("__Fl_Group_as_group",fltk_fl_group_as_group);
    register_block("__Fl_Group_focus",fltk_fl_group_focus);
    register_block("__Fl_Group__ddfdesign_kludge",fltk_fl_group__ddfdesign_kludge);
#ifndef __ANDROID__
    register_block("__Fl_Group_forms_end",fltk_fl_group_forms_end);
#endif
    /* Fl_End */
    register_block("__Fl_End",fltk_fl_end_Fl_End);
    /* Help_Dialog */
#ifndef __ANDROID__
    register_block("__Fl_Help_Dialog",fltk_fl_help_dialog_Fl_Help_Dialog);
	register_block("__Fl_Help_Dialog_h",fltk_fl_help_dialog_h);
	register_block("__Fl_Help_Dialog_hide",fltk_fl_help_dialog_hide);
	register_block("__Fl_Help_Dialog_load",fltk_fl_help_dialog_load);
	register_block("__Fl_Help_Dialog_position",fltk_fl_help_dialog_position);
	register_block("__Fl_Help_Dialog_resize_1",fltk_fl_help_dialog_resize_1);
	register_block("__Fl_Help_Dialog_show",fltk_fl_help_dialog_show);
	register_block("__Fl_Help_Dialog_show_1",fltk_fl_help_dialog_show_1);
	register_block("__Fl_Help_Dialog_textsize",fltk_fl_help_dialog_textsize);
	register_block("__Fl_Help_Dialog_textsize_1",fltk_fl_help_dialog_textsize_1);
	register_block("__Fl_Help_Dialog_topline",fltk_fl_help_dialog_topline);
	register_block("__Fl_Help_Dialog_topline_1",fltk_fl_help_dialog_topline_1);
	register_block("__Fl_Help_Dialog_value",fltk_fl_help_dialog_value);
	register_block("__Fl_Help_Dialog_value_1",fltk_fl_help_dialog_value_1);
	register_block("__Fl_Help_Dialog_visible",fltk_fl_help_dialog_visible);
	register_block("__Fl_Help_Dialog_w",fltk_fl_help_dialog_w);
	register_block("__Fl_Help_Dialog_x",fltk_fl_help_dialog_x);
	register_block("__Fl_Help_Dialog_y",fltk_fl_help_dialog_y);
#endif
    /* Fl_Help_View */
#if FLTK_ABI_VERSION >= 10303
    register_block("__Fl_Help_View_handle_1",fltk_fl_help_view_handle_1);
#endif
    register_block("__MAX_FL_HELP_FS_ELTS",fltk_MAX_FL_HELP_FS_ELTS);
    register_block("__Fl_Help_View",fltk_fl_help_view_Fl_Help_View);
    register_block("__Fl_Help_View_directory",fltk_fl_help_view_directory);
    register_block("__Fl_Help_View_filename",fltk_fl_help_view_filename);
    register_block("__Fl_Help_View_find_2",fltk_fl_help_view_find_2);
    register_block("__Fl_Help_View_link",fltk_fl_help_view_link);
    register_block("__Fl_Help_View_load_1",fltk_fl_help_view_load_1);
    register_block("__Fl_Help_View_resize_2",fltk_fl_help_view_resize_2);
    register_block("__Fl_Help_View_size",fltk_fl_help_view_size);
    register_block("__Fl_Help_View_size_1",fltk_fl_help_view_size_1);
    register_block("__Fl_Help_View_textcolor",fltk_fl_help_view_textcolor);
    register_block("__Fl_Help_View_textcolor_1",fltk_fl_help_view_textcolor_1);
    register_block("__Fl_Help_View_textfont",fltk_fl_help_view_textfont);
    register_block("__Fl_Help_View_textfont_1",fltk_fl_help_view_textfont_1);
    register_block("__Fl_Help_View_textsize_2",fltk_fl_help_view_textsize_2);
    register_block("__Fl_Help_View_textsize_3",fltk_fl_help_view_textsize_3);
    register_block("__Fl_Help_View_title",fltk_fl_help_view_title);
    register_block("__Fl_Help_View_topline_2",fltk_fl_help_view_topline_2);
    register_block("__Fl_Help_View_topline_3",fltk_fl_help_view_topline_3);
    register_block("__Fl_Help_View_topline_4",fltk_fl_help_view_topline_4);
    register_block("__Fl_Help_View_leftline",fltk_fl_help_view_leftline);
    register_block("__Fl_Help_View_leftline_1",fltk_fl_help_view_leftline_1);
    register_block("__Fl_Help_View_value_2",fltk_fl_help_view_value_2);
    register_block("__Fl_Help_View_value_3",fltk_fl_help_view_value_3);
    register_block("__Fl_Help_View_clear_selection",fltk_fl_help_view_clear_selection);
    register_block("__Fl_Help_View_select_all",fltk_fl_help_view_select_all);
    register_block("__Fl_Help_View_scrollbar_size",fltk_fl_help_view_scrollbar_size);
    register_block("__Fl_Help_View_scrollbar_size_1",fltk_fl_help_view_scrollbar_size_1);
    /* Fl_Hold_Browser */
    register_block("__Fl_Hold_Browser",fltk_fl_hold_browser_Fl_Hold_Browser);
    /* Fl_Hor_Fill_Slider */
    register_block("__Fl_Hor_Fill_Slider",fltk_fl_hor_fill_slider_Fl_Hor_Fill_Slider);
    /* Fl_Hor_Nice_Slider */
    register_block("__Fl_Hor_Nice_Slider",fltk_fl_hor_nice_slider_Fl_Hor_Nice_Slider);
    /* Fl_Hor_Slider */
    register_block("__Fl_Hor_Slider",fltk_fl_hor_slider_Fl_Hor_Slider);
    /* Fl_Hor_Value_Slider */
    register_block("__Fl_Hor_Value_Slider",fltk_fl_hor_value_slider_Fl_Hor_Value_Slider);
    /* Fl_Image */
    register_block("__FL_RGB_SCALING_NEAREST",fltk_FL_RGB_SCALING_NEAREST);
    register_block("__Fl_Image_Fl_Image_ERR_NO_IMAGE",fltk_fl_image_Fl_Image_ERR_NO_IMAGE);
    register_block("__Fl_Image_Fl_Image_ERR_FILE_ACCESS",fltk_fl_image_Fl_Image_ERR_FILE_ACCESS);
    register_block("__Fl_Image_Fl_Image_ERR_FORMAT",fltk_fl_image_Fl_Image_ERR_FORMAT);
    register_block("__Fl_Image_w",fltk_fl_image_w);
    register_block("__Fl_Image_h",fltk_fl_image_h);
    register_block("__Fl_Image_d",fltk_fl_image_d);
    register_block("__Fl_Image_ld",fltk_fl_image_ld);
    register_block("__Fl_Image_count",fltk_fl_image_count);
    register_block("__Fl_Image_data",fltk_fl_image_data);
    register_block("__Fl_Image_fail",fltk_fl_image_fail);
    register_block("__Fl_Image",fltk_fl_image_Fl_Image);
    register_block("__Fl_Image_copy",fltk_fl_image_copy);
    register_block("__Fl_Image_copy_1",fltk_fl_image_copy_1);
    register_block("__Fl_Image_color_average",fltk_fl_image_color_average);
    register_block("__Fl_Image_inactive",fltk_fl_image_inactive);
    register_block("__Fl_Image_desaturate",fltk_fl_image_desaturate);
    register_block("__Fl_Image_label",fltk_fl_image_label);
    register_block("__Fl_Image_label_1",fltk_fl_image_label_1);
    register_block("__Fl_Image_draw",fltk_fl_image_draw);
    register_block("__Fl_Image_draw_1",fltk_fl_image_draw_1);
    register_block("__Fl_Image_uncache",fltk_fl_image_uncache);
    register_block("__Fl_Image_Fl_Image_RGB_scaling",fltk_fl_image_Fl_Image_RGB_scaling);
    register_block("__Fl_Image_Fl_Image_RGB_scaling_1",fltk_fl_image_Fl_Image_RGB_scaling_1);
    /* Fl_RGB_Image */
    register_block("__Fl_RGB_Image",fltk_fl_rgb_image_Fl_RGB_Image);
    register_block("__Fl_RGB_Image_1",fltk_fl_rgb_image_Fl_RGB_Image_1);
    register_block("__Fl_RGB_Image_copy_2",fltk_fl_rgb_image_copy_2);
    register_block("__Fl_RGB_Image_copy_3",fltk_fl_rgb_image_copy_3);
    register_block("__Fl_RGB_Image_color_average_1",fltk_fl_rgb_image_color_average_1);
    register_block("__Fl_RGB_Image_desaturate_1",fltk_fl_rgb_image_desaturate_1);
    register_block("__Fl_RGB_Image_draw_2",fltk_fl_rgb_image_draw_2);
    register_block("__Fl_RGB_Image_draw_3",fltk_fl_rgb_image_draw_3);
    register_block("__Fl_RGB_Image_label_2",fltk_fl_rgb_image_label_2);
    register_block("__Fl_RGB_Image_label_3",fltk_fl_rgb_image_label_3);
    register_block("__Fl_RGB_Image_uncache_1",fltk_fl_rgb_image_uncache_1);
    register_block("__Fl_RGB_Image_Fl_RGB_Image_max_size",fltk_fl_rgb_image_Fl_RGB_Image_max_size);
    register_block("__Fl_RGB_Image_Fl_RGB_Image_max_size_1",fltk_fl_rgb_image_Fl_RGB_Image_max_size_1);
    /* Fl_Image_Surface */
#ifdef Fl_Image_Surface::class_id
    //register_block("__Fl_Image_Surface_Fl_Image_Surface_class_id",fltk_fl_image_surface_Fl_Image_Surface_class_id);
#endif
    //register_block("__Fl_Image_Surface_class_name",fltk_fl_image_surface_class_name);
    register_block("__Fl_Image_Surface",fltk_fl_image_surface_Fl_Image_Surface);
    register_block("__Fl_Image_Surface_1",fltk_fl_image_surface_Fl_Image_Surface_1);
    register_block("__Fl_Image_Surface_2",fltk_fl_image_surface_Fl_Image_Surface_2);
    register_block("__Fl_Image_Surface_set_current",fltk_fl_image_surface_set_current);
    register_block("__Fl_Image_Surface_draw_4",fltk_fl_image_surface_draw_4);
    register_block("__Fl_Image_Surface_draw_decorated_window",fltk_fl_image_surface_draw_decorated_window);
    register_block("__Fl_Image_Surface_image",fltk_fl_image_surface_image);
    register_block("__Fl_Image_Surface_highres_image",fltk_fl_image_surface_highres_image);
#ifdef __APPLE__
    //register_block("__Fl_Quartz_Flipped_Surface__class_name_1",fltk_fl_quartz_flipped_surface__class_name_1);
	register_block("__Fl_Quartz_Flipped_Surface_",fltk_fl_quartz_flipped_surface__Fl_Quartz_Flipped_Surface_);
	register_block("__Fl_Quartz_Flipped_Surface__translate",fltk_fl_quartz_flipped_surface__translate);
	register_block("__Fl_Quartz_Flipped_Surface__untranslate",fltk_fl_quartz_flipped_surface__untranslate);
#endif
    /* Fl_Input_ */
    register_block("__Fl_Input_handle",fltk_fl_input_handle);
    register_block("__Fl_Input",fltk_fl_input_Fl_Input);
    register_block("__Fl_Input__resize",fltk_fl_input__resize);
    register_block("__Fl_Input__value",fltk_fl_input__value);
    register_block("__Fl_Input__value_1",fltk_fl_input__value_1);
    register_block("__Fl_Input__static_value",fltk_fl_input__static_value);
    register_block("__Fl_Input__static_value_1",fltk_fl_input__static_value_1);
    register_block("__Fl_Input__value_2",fltk_fl_input__value_2);
    register_block("__Fl_Input__index",fltk_fl_input__index);
    register_block("__Fl_Input__size",fltk_fl_input__size);
    register_block("__Fl_Input__size_1",fltk_fl_input__size_1);
    register_block("__Fl_Input__maximum_size",fltk_fl_input__maximum_size);
    register_block("__Fl_Input__maximum_size_1",fltk_fl_input__maximum_size_1);
    register_block("__Fl_Input__position",fltk_fl_input__position);
    register_block("__Fl_Input__mark",fltk_fl_input__mark);
    register_block("__Fl_Input__position_1",fltk_fl_input__position_1);
    register_block("__Fl_Input__position_2",fltk_fl_input__position_2);
    register_block("__Fl_Input__mark_1",fltk_fl_input__mark_1);
    register_block("__Fl_Input__replace",fltk_fl_input__replace);
    register_block("__Fl_Input__cut",fltk_fl_input__cut);
    register_block("__Fl_Input__cut_1",fltk_fl_input__cut_1);
    register_block("__Fl_Input__cut_2",fltk_fl_input__cut_2);
    register_block("__Fl_Input__insert",fltk_fl_input__insert);
    register_block("__Fl_Input__copy_4",fltk_fl_input__copy_4);
    register_block("__Fl_Input__undo",fltk_fl_input__undo);
    register_block("__Fl_Input__copy_cuts",fltk_fl_input__copy_cuts);
    register_block("__Fl_Input__shortcut",fltk_fl_input__shortcut);
    register_block("__Fl_Input__shortcut_1",fltk_fl_input__shortcut_1);
    register_block("__Fl_Input__textfont",fltk_fl_input__textfont);
    register_block("__Fl_Input__textfont_1",fltk_fl_input__textfont_1);
    register_block("__Fl_Input__textsize",fltk_fl_input__textsize);
    register_block("__Fl_Input__textsize_1",fltk_fl_input__textsize_1);
    register_block("__Fl_Input__textcolor",fltk_fl_input__textcolor);
    register_block("__Fl_Input__textcolor_1",fltk_fl_input__textcolor_1);
    register_block("__Fl_Input__cursor_color",fltk_fl_input__cursor_color);
    register_block("__Fl_Input__cursor_color_1",fltk_fl_input__cursor_color_1);
    register_block("__Fl_Input__input_type",fltk_fl_input__input_type);
    register_block("__Fl_Input__input_type_1",fltk_fl_input__input_type_1);
    register_block("__Fl_Input__readonly",fltk_fl_input__readonly);
    register_block("__Fl_Input__readonly_1",fltk_fl_input__readonly_1);
    register_block("__Fl_Input__wrap",fltk_fl_input__wrap);
    register_block("__Fl_Input__wrap_1",fltk_fl_input__wrap_1);
    register_block("__Fl_Input__tab_nav",fltk_fl_input__tab_nav);
    register_block("__Fl_Input__tab_nav_1",fltk_fl_input__tab_nav_1);
    /* Fl_Input_Choice */
    register_block("__Fl_Input_Choice_add",fltk_fl_input_choice_add);
    register_block("__Fl_Input_Choice_changed",fltk_fl_input_choice_changed);
    register_block("__Fl_Input_Choice_clear_changed",fltk_fl_input_choice_clear_changed);
    register_block("__Fl_Input_Choice_set_changed",fltk_fl_input_choice_set_changed);
    register_block("__Fl_Input_Choice_clear",fltk_fl_input_choice_clear);
    register_block("__Fl_Input_Choice_down_box",fltk_fl_input_choice_down_box);
    register_block("__Fl_Input_Choice_down_box_1",fltk_fl_input_choice_down_box_1);
    register_block("__Fl_Input_Choice_menu",fltk_fl_input_choice_menu);
    register_block("__Fl_Input_Choice_menu_1",fltk_fl_input_choice_menu_1);
    register_block("__Fl_Input_Choice_resize_1",fltk_fl_input_choice_resize_1);
    register_block("__Fl_Input_Choice_textcolor_2",fltk_fl_input_choice_textcolor_2);
    register_block("__Fl_Input_Choice_textcolor_3",fltk_fl_input_choice_textcolor_3);
    register_block("__Fl_Input_Choice_textfont_2",fltk_fl_input_choice_textfont_2);
    register_block("__Fl_Input_Choice_textfont_3",fltk_fl_input_choice_textfont_3);
    register_block("__Fl_Input_Choice_textsize_2",fltk_fl_input_choice_textsize_2);
    register_block("__Fl_Input_Choice_textsize_3",fltk_fl_input_choice_textsize_3);
    register_block("__Fl_Input_Choice_value_3",fltk_fl_input_choice_value_3);
    register_block("__Fl_Input_Choice_value_4",fltk_fl_input_choice_value_4);
    register_block("__Fl_Input_Choice_value_5",fltk_fl_input_choice_value_5);
    register_block("__Fl_Input_Choice_menubutton",fltk_fl_input_choice_menubutton);
    register_block("__Fl_Input_Choice_input",fltk_fl_input_choice_input);
    /* Fl_Int_Input */
    register_block("__Fl_Int_Input",fltk_fl_int_input_Fl_Int_Input);
    /* Fl_JPEG_Image */
#ifndef __ANDROID__
    register_block("__Fl_JPEG_Image",fltk_fl_jpeg_image_Fl_JPEG_Image);
	register_block("__Fl_JPEG_Image_1",fltk_fl_jpeg_image_Fl_JPEG_Image_1);
#endif
    /* Fl_Light_Button */
    register_block("__Fl_Light_Button_handle_1",fltk_fl_light_button_handle_1);
    register_block("__Fl_Light_Button",fltk_fl_light_button_Fl_Light_Button);
    /* Fl_Line_Dial */
    register_block("__Fl_Line_Dial",fltk_fl_line_dial_Fl_Line_Dial);
    /* Fl_Menu_ */
    register_block("__Fl_Menu__picked",fltk_fl_menu__picked);
    register_block("__Fl_Menu__find_item",fltk_fl_menu__find_item);
    register_block("__Fl_Menu__find_item_1",fltk_fl_menu__find_item_1);
    register_block("__Fl_Menu__find_index",fltk_fl_menu__find_index);
    register_block("__Fl_Menu__find_index_1",fltk_fl_menu__find_index_1);
    register_block("__Fl_Menu__find_index_2",fltk_fl_menu__find_index_2);
    register_block("__Fl_Menu__test_shortcut",fltk_fl_menu__test_shortcut);
    register_block("__Fl_Menu__global",fltk_fl_menu__global);
    register_block("__Fl_Menu__menu",fltk_fl_menu__menu);
    register_block("__Fl_Menu__menu_1",fltk_fl_menu__menu_1);
    register_block("__Fl_Menu__copy_4",fltk_fl_menu__copy_4);
    register_block("__Fl_Menu__insert",fltk_fl_menu__insert);
    register_block("__Fl_Menu__add",fltk_fl_menu__add);
    register_block("__Fl_Menu__add_1",fltk_fl_menu__add_1);
    register_block("__Fl_Menu__insert_1",fltk_fl_menu__insert_1);
    register_block("__Fl_Menu__add_2",fltk_fl_menu__add_2);
    register_block("__Fl_Menu__size",fltk_fl_menu__size);
    register_block("__Fl_Menu__size_1",fltk_fl_menu__size_1);
    register_block("__Fl_Menu__clear",fltk_fl_menu__clear);
    register_block("__Fl_Menu__clear_submenu",fltk_fl_menu__clear_submenu);
    register_block("__Fl_Menu__replace",fltk_fl_menu__replace);
    register_block("__Fl_Menu__remove",fltk_fl_menu__remove);
    register_block("__Fl_Menu__shortcut",fltk_fl_menu__shortcut);
    register_block("__Fl_Menu__mode",fltk_fl_menu__mode);
    register_block("__Fl_Menu__mode_1",fltk_fl_menu__mode_1);
    register_block("__Fl_Menu__mvalue",fltk_fl_menu__mvalue);
    register_block("__Fl_Menu__value",fltk_fl_menu__value);
    register_block("__Fl_Menu__value_1",fltk_fl_menu__value_1);
    register_block("__Fl_Menu__value_2",fltk_fl_menu__value_2);
    register_block("__Fl_Menu__text",fltk_fl_menu__text);
    register_block("__Fl_Menu__text_1",fltk_fl_menu__text_1);
    register_block("__Fl_Menu__textfont",fltk_fl_menu__textfont);
    register_block("__Fl_Menu__textfont_1",fltk_fl_menu__textfont_1);
    register_block("__Fl_Menu__textsize",fltk_fl_menu__textsize);
    register_block("__Fl_Menu__textsize_1",fltk_fl_menu__textsize_1);
    register_block("__Fl_Menu__textcolor",fltk_fl_menu__textcolor);
    register_block("__Fl_Menu__textcolor_1",fltk_fl_menu__textcolor_1);
    register_block("__Fl_Menu__down_box",fltk_fl_menu__down_box);
    register_block("__Fl_Menu__down_box_1",fltk_fl_menu__down_box_1);
    register_block("__Fl_Menu__down_color",fltk_fl_menu__down_color);
    register_block("__Fl_Menu__down_color_1",fltk_fl_menu__down_color_1);
    register_block("__Fl_Menu__setonly",fltk_fl_menu__setonly);
    /* Fl_Menu_Bar */
    register_block("__Fl_Menu_Bar_handle",fltk_fl_menu_bar_handle);
    register_block("__Fl_Menu_Bar",fltk_fl_menu_bar_Fl_Menu_Bar);
    /* Fl_Menu_Button */
    register_block("__Fl_Menu_Button_POPUP1",fltk_fl_menu_button_POPUP1);
    register_block("__Fl_Menu_Button_POPUP2",fltk_fl_menu_button_POPUP2);
    register_block("__Fl_Menu_Button_POPUP12",fltk_fl_menu_button_POPUP12);
    register_block("__Fl_Menu_Button_POPUP3",fltk_fl_menu_button_POPUP3);
    register_block("__Fl_Menu_Button_POPUP13",fltk_fl_menu_button_POPUP13);
    register_block("__Fl_Menu_Button_POPUP23",fltk_fl_menu_button_POPUP23);
    register_block("__Fl_Menu_Button_handle_1",fltk_fl_menu_button_handle_1);
    register_block("__Fl_Menu_Button_popup",fltk_fl_menu_button_popup);
    register_block("__Fl_Menu_Button",fltk_fl_menu_button_Fl_Menu_Button);
    register_block("__FL_MENU_INACTIVE",fltk_FL_MENU_INACTIVE);
    register_block("__FL_MENU_TOGGLE",fltk_FL_MENU_TOGGLE);
    register_block("__FL_MENU_VALUE",fltk_FL_MENU_VALUE);
    register_block("__FL_MENU_RADIO",fltk_FL_MENU_RADIO);
    register_block("__FL_MENU_INVISIBLE",fltk_FL_MENU_INVISIBLE);
    register_block("__FL_SUBMENU_POINTER",fltk_FL_SUBMENU_POINTER);
    register_block("__FL_SUBMENU",fltk_FL_SUBMENU);
    register_block("__FL_MENU_DIVIDER",fltk_FL_MENU_DIVIDER);
    register_block("__FL_MENU_HORIZONTAL",fltk_FL_MENU_HORIZONTAL);
    register_block("__fl_old_shortcut_menu",fltk_fl_old_shortcut_menu);
    /* Fl_Menu_Window */
    register_block("__Fl_Menu_Window_show",fltk_fl_menu_window_show);
    register_block("__Fl_Menu_Window_erase",fltk_fl_menu_window_erase);
    register_block("__Fl_Menu_Window_flush",fltk_fl_menu_window_flush);
    register_block("__Fl_Menu_Window_hide",fltk_fl_menu_window_hide);
    register_block("__Fl_Menu_Window_overlay",fltk_fl_menu_window_overlay);
    register_block("__Fl_Menu_Window_set_overlay",fltk_fl_menu_window_set_overlay);
    register_block("__Fl_Menu_Window_clear_overlay",fltk_fl_menu_window_clear_overlay);
    register_block("__Fl_Menu_Window",fltk_fl_menu_window_Fl_Menu_Window);
    register_block("__Fl_Menu_Window_1",fltk_fl_menu_window_Fl_Menu_Window_1);
    /* Fl_Multiline_Input */
    register_block("__Fl_Multiline_Input",fltk_fl_multiline_input_Fl_Multiline_Input);
    /* Fl_Multiline_Output */
    register_block("__Fl_Multiline_Output",fltk_fl_multiline_output_Fl_Multiline_Output);
    /* Fl_Multi_Browser */
    register_block("__Fl_Multi_Browser",fltk_fl_multi_browser_Fl_Multi_Browser);
    /* Fl_Native_File */
    register_block("__Fl_Native_File_Chooser_BROWSE_FILE",fltk_fl_native_file_chooser_BROWSE_FILE);
    register_block("__Fl_Native_File_Chooser_BROWSE_DIRECTORY",fltk_fl_native_file_chooser_BROWSE_DIRECTORY);
    register_block("__Fl_Native_File_Chooser_BROWSE_MULTI_FILE",fltk_fl_native_file_chooser_BROWSE_MULTI_FILE);
    register_block("__Fl_Native_File_Chooser_BROWSE_MULTI_DIRECTORY",fltk_fl_native_file_chooser_BROWSE_MULTI_DIRECTORY);
    register_block("__Fl_Native_File_Chooser_BROWSE_SAVE_FILE",fltk_fl_native_file_chooser_BROWSE_SAVE_FILE);
    register_block("__Fl_Native_File_Chooser_NO_OPTIONS",fltk_fl_native_file_chooser_NO_OPTIONS);
    register_block("__Fl_Native_File_Chooser_SAVEAS_CONFIRM",fltk_fl_native_file_chooser_SAVEAS_CONFIRM);
    register_block("__Fl_Native_File_Chooser_NEW_FOLDER",fltk_fl_native_file_chooser_NEW_FOLDER);
    register_block("__Fl_Native_File_Chooser_PREVIEW",fltk_fl_native_file_chooser_PREVIEW);
    register_block("__Fl_Native_File_Chooser_USE_FILTER_EXT",fltk_fl_native_file_chooser_USE_FILTER_EXT);
    register_block("__Fl_Native_File_Chooser_Fl_Native_File_Chooser_file_exists_message",fltk_fl_native_file_chooser_Fl_Native_File_Chooser_file_exists_message);
#ifndef __ANDROID__
    register_block("__Fl_Native_File_Chooser",fltk_fl_native_file_chooser_Fl_Native_File_Chooser);
#endif
    register_block("__Fl_Native_File_Chooser_type",fltk_fl_native_file_chooser_type);
    register_block("__Fl_Native_File_Chooser_type_1",fltk_fl_native_file_chooser_type_1);
    register_block("__Fl_Native_File_Chooser_options",fltk_fl_native_file_chooser_options);
    register_block("__Fl_Native_File_Chooser_options_1",fltk_fl_native_file_chooser_options_1);
    register_block("__Fl_Native_File_Chooser_count",fltk_fl_native_file_chooser_count);
    register_block("__Fl_Native_File_Chooser_filename",fltk_fl_native_file_chooser_filename);
    register_block("__Fl_Native_File_Chooser_filename_1",fltk_fl_native_file_chooser_filename_1);
    register_block("__Fl_Native_File_Chooser_directory",fltk_fl_native_file_chooser_directory);
    register_block("__Fl_Native_File_Chooser_directory_1",fltk_fl_native_file_chooser_directory_1);
    register_block("__Fl_Native_File_Chooser_title",fltk_fl_native_file_chooser_title);
    register_block("__Fl_Native_File_Chooser_title_1",fltk_fl_native_file_chooser_title_1);
    register_block("__Fl_Native_File_Chooser_filter",fltk_fl_native_file_chooser_filter);
    register_block("__Fl_Native_File_Chooser_filter_1",fltk_fl_native_file_chooser_filter_1);
    register_block("__Fl_Native_File_Chooser_filters",fltk_fl_native_file_chooser_filters);
    register_block("__Fl_Native_File_Chooser_filter_value",fltk_fl_native_file_chooser_filter_value);
    register_block("__Fl_Native_File_Chooser_filter_value_1",fltk_fl_native_file_chooser_filter_value_1);
    register_block("__Fl_Native_File_Chooser_preset_file",fltk_fl_native_file_chooser_preset_file);
    register_block("__Fl_Native_File_Chooser_preset_file_1",fltk_fl_native_file_chooser_preset_file_1);
    register_block("__Fl_Native_File_Chooser_errmsg",fltk_fl_native_file_chooser_errmsg);
    register_block("__Fl_Native_File_Chooser_show",fltk_fl_native_file_chooser_show);
    /* Fl_Nice_Slider */
    register_block("__Fl_Nice_Slider",fltk_fl_nice_slider_Fl_Nice_Slider);
    /* Fl_Output */
    register_block("__Fl_Output",fltk_fl_output_Fl_Output);
    /* Fl_Overlay_Window */
    register_block("__Fl_Overlay_Window_show",fltk_fl_overlay_window_show);
    register_block("__Fl_Overlay_Window_flush",fltk_fl_overlay_window_flush);
    register_block("__Fl_Overlay_Window_hide",fltk_fl_overlay_window_hide);
    register_block("__Fl_Overlay_Window_resize",fltk_fl_overlay_window_resize);
    register_block("__Fl_Overlay_Window_can_do_overlay",fltk_fl_overlay_window_can_do_overlay);
    register_block("__Fl_Overlay_Window_redraw_overlay",fltk_fl_overlay_window_redraw_overlay);
    register_block("__Fl_Overlay_Window_show_1",fltk_fl_overlay_window_show_1);
    /* Fl_Pack */
    register_block("__Fl_Pack_VERTICAL",fltk_fl_pack_VERTICAL);
    register_block("__Fl_Pack_HORIZONTAL",fltk_fl_pack_HORIZONTAL);
    register_block("__Fl_Pack",fltk_fl_pack_Fl_Pack);
    register_block("__Fl_Pack_spacing",fltk_fl_pack_spacing);
    register_block("__Fl_Pack_spacing_1",fltk_fl_pack_spacing_1);
    register_block("__Fl_Pack_horizontal",fltk_fl_pack_horizontal);
    /* Fl_Paged_Device */
    register_block("__Fl_Paged_Device_A0",fltk_fl_paged_device_A0);
    register_block("__Fl_Paged_Device_A1",fltk_fl_paged_device_A1);
    register_block("__Fl_Paged_Device_A2",fltk_fl_paged_device_A2);
    register_block("__Fl_Paged_Device_A3",fltk_fl_paged_device_A3);
    register_block("__Fl_Paged_Device_A4",fltk_fl_paged_device_A4);
    register_block("__Fl_Paged_Device_A5",fltk_fl_paged_device_A5);
    register_block("__Fl_Paged_Device_A6",fltk_fl_paged_device_A6);
    register_block("__Fl_Paged_Device_A7",fltk_fl_paged_device_A7);
    register_block("__Fl_Paged_Device_A8",fltk_fl_paged_device_A8);
    register_block("__Fl_Paged_Device_A9",fltk_fl_paged_device_A9);
    register_block("__Fl_Paged_Device_B0",fltk_fl_paged_device_B0);
    register_block("__Fl_Paged_Device_B1",fltk_fl_paged_device_B1);
    register_block("__Fl_Paged_Device_B2",fltk_fl_paged_device_B2);
    register_block("__Fl_Paged_Device_B3",fltk_fl_paged_device_B3);
    register_block("__Fl_Paged_Device_B4",fltk_fl_paged_device_B4);
    register_block("__Fl_Paged_Device_B5",fltk_fl_paged_device_B5);
    register_block("__Fl_Paged_Device_B6",fltk_fl_paged_device_B6);
    register_block("__Fl_Paged_Device_B7",fltk_fl_paged_device_B7);
    register_block("__Fl_Paged_Device_B8",fltk_fl_paged_device_B8);
    register_block("__Fl_Paged_Device_B9",fltk_fl_paged_device_B9);
    register_block("__Fl_Paged_Device_B10",fltk_fl_paged_device_B10);
    register_block("__Fl_Paged_Device_C5E",fltk_fl_paged_device_C5E);
    register_block("__Fl_Paged_Device_DLE",fltk_fl_paged_device_DLE);
    register_block("__Fl_Paged_Device_EXECUTIVE",fltk_fl_paged_device_EXECUTIVE);
    register_block("__Fl_Paged_Device_FOLIO",fltk_fl_paged_device_FOLIO);
    register_block("__Fl_Paged_Device_LEDGER",fltk_fl_paged_device_LEDGER);
    register_block("__Fl_Paged_Device_LEGAL",fltk_fl_paged_device_LEGAL);
    register_block("__Fl_Paged_Device_LETTER",fltk_fl_paged_device_LETTER);
    register_block("__Fl_Paged_Device_TABLOID",fltk_fl_paged_device_TABLOID);
    register_block("__Fl_Paged_Device_ENVELOPE",fltk_fl_paged_device_ENVELOPE);
    register_block("__Fl_Paged_Device_MEDIA",fltk_fl_paged_device_MEDIA);
    register_block("__Fl_Paged_Device_PORTRAIT",fltk_fl_paged_device_PORTRAIT);
    register_block("__Fl_Paged_Device_LANDSCAPE",fltk_fl_paged_device_LANDSCAPE);
    register_block("__Fl_Paged_Device_REVERSED",fltk_fl_paged_device_REVERSED);
    register_block("__Fl_Paged_Device_ORIENTATION",fltk_fl_paged_device_ORIENTATION);
    //register_block("__Fl_Paged_Device_Fl_Paged_Device_class_id",fltk_fl_paged_device_Fl_Paged_Device_class_id);
    //register_block("__Fl_Paged_Device_class_name",fltk_fl_paged_device_class_name);
    register_block("__Fl_Paged_Device_start_job",fltk_fl_paged_device_start_job);
    register_block("__Fl_Paged_Device_start_page",fltk_fl_paged_device_start_page);
    register_block("__Fl_Paged_Device_printable_rect",fltk_fl_paged_device_printable_rect);
    register_block("__Fl_Paged_Device_margins",fltk_fl_paged_device_margins);
    register_block("__Fl_Paged_Device_origin",fltk_fl_paged_device_origin);
    register_block("__Fl_Paged_Device_origin_1",fltk_fl_paged_device_origin_1);
    register_block("__Fl_Paged_Device_scale",fltk_fl_paged_device_scale);
    register_block("__Fl_Paged_Device_rotate",fltk_fl_paged_device_rotate);
    register_block("__Fl_Paged_Device_translate",fltk_fl_paged_device_translate);
    register_block("__Fl_Paged_Device_untranslate",fltk_fl_paged_device_untranslate);
    register_block("__Fl_Paged_Device_print_widget",fltk_fl_paged_device_print_widget);
    register_block("__Fl_Paged_Device_print_window",fltk_fl_paged_device_print_window);
    register_block("__Fl_Paged_Device_print_window_part",fltk_fl_paged_device_print_window_part);
    /* Fl_Pixmap */
    register_block("__Fl_Pixmap",fltk_fl_pixmap_Fl_Pixmap);
    register_block("__Fl_Pixmap_1",fltk_fl_pixmap_Fl_Pixmap_1);
    register_block("__Fl_Pixmap_2",fltk_fl_pixmap_Fl_Pixmap_2);
    register_block("__Fl_Pixmap_3",fltk_fl_pixmap_Fl_Pixmap_3);
    register_block("__Fl_Pixmap_copy",fltk_fl_pixmap_copy);
    register_block("__Fl_Pixmap_copy_1",fltk_fl_pixmap_copy_1);
    register_block("__Fl_Pixmap_color_average",fltk_fl_pixmap_color_average);
    register_block("__Fl_Pixmap_desaturate",fltk_fl_pixmap_desaturate);
    register_block("__Fl_Pixmap_draw",fltk_fl_pixmap_draw);
    register_block("__Fl_Pixmap_draw_1",fltk_fl_pixmap_draw_1);
    register_block("__Fl_Pixmap_label",fltk_fl_pixmap_label);
    register_block("__Fl_Pixmap_label_1",fltk_fl_pixmap_label_1);
    register_block("__Fl_Pixmap_uncache",fltk_fl_pixmap_uncache);
    /* Fl_Plugin */
    register_block("__Fl_Plugin",fltk_fl_plugin_Fl_Plugin);
    /* Fl_Plugin_Manager */
    register_block("__Fl_Plugin_Manager",fltk_fl_plugin_manager_Fl_Plugin_Manager);
    register_block("__Fl_Plugin_Manager_plugins",fltk_fl_plugin_manager_plugins);
    register_block("__Fl_Plugin_Manager_plugin",fltk_fl_plugin_manager_plugin);
    register_block("__Fl_Plugin_Manager_plugin_1",fltk_fl_plugin_manager_plugin_1);
    register_block("__Fl_Plugin_Manager_Fl_Plugin_Manager_removePlugin",fltk_fl_plugin_manager_Fl_Plugin_Manager_removePlugin);
    register_block("__Fl_Plugin_Manager_Fl_Plugin_Manager_load",fltk_fl_plugin_manager_Fl_Plugin_Manager_load);
    register_block("__Fl_Plugin_Manager_Fl_Plugin_Manager_loadAll",fltk_fl_plugin_manager_Fl_Plugin_Manager_loadAll);
    /* Fl_PNG_Image */
#ifndef __ANDROID__
    register_block("__Fl_PNG_Image",fltk_fl_png_image_Fl_PNG_Image);
	/* Fl_PNM_Image */
	register_block("__Fl_PNM_Image",fltk_fl_pnm_image_Fl_PNM_Image);
#endif
    /* Fl_Positioner */
    register_block("__Fl_Positioner_handle",fltk_fl_positioner_handle);
    register_block("__Fl_Positioner",fltk_fl_positioner_Fl_Positioner);
    register_block("__Fl_Positioner_xvalue",fltk_fl_positioner_xvalue);
    register_block("__Fl_Positioner_yvalue",fltk_fl_positioner_yvalue);
    register_block("__Fl_Positioner_xvalue_1",fltk_fl_positioner_xvalue_1);
    register_block("__Fl_Positioner_yvalue_1",fltk_fl_positioner_yvalue_1);
    register_block("__Fl_Positioner_value",fltk_fl_positioner_value);
    register_block("__Fl_Positioner_xbounds",fltk_fl_positioner_xbounds);
    register_block("__Fl_Positioner_xminimum",fltk_fl_positioner_xminimum);
    register_block("__Fl_Positioner_xminimum_1",fltk_fl_positioner_xminimum_1);
    register_block("__Fl_Positioner_xmaximum",fltk_fl_positioner_xmaximum);
    register_block("__Fl_Positioner_xmaximum_1",fltk_fl_positioner_xmaximum_1);
    register_block("__Fl_Positioner_ybounds",fltk_fl_positioner_ybounds);
    register_block("__Fl_Positioner_yminimum",fltk_fl_positioner_yminimum);
    register_block("__Fl_Positioner_yminimum_1",fltk_fl_positioner_yminimum_1);
    register_block("__Fl_Positioner_ymaximum",fltk_fl_positioner_ymaximum);
    register_block("__Fl_Positioner_ymaximum_1",fltk_fl_positioner_ymaximum_1);
    register_block("__Fl_Positioner_xstep",fltk_fl_positioner_xstep);
    register_block("__Fl_Positioner_ystep",fltk_fl_positioner_ystep);
    /* Fl_Progress */
    register_block("__Fl_Progress",fltk_fl_progress_Fl_Progress);
    register_block("__Fl_Progress_maximum",fltk_fl_progress_maximum);
    register_block("__Fl_Progress_maximum_1",fltk_fl_progress_maximum_1);
    register_block("__Fl_Progress_minimum",fltk_fl_progress_minimum);
    register_block("__Fl_Progress_minimum_1",fltk_fl_progress_minimum_1);
    register_block("__Fl_Progress_value",fltk_fl_progress_value);
    register_block("__Fl_Progress_value_1",fltk_fl_progress_value_1);
    /* Fl_Radio_Button */
    register_block("__Fl_Radio_Button",fltk_fl_radio_button_Fl_Radio_Button);
    /* Fl_Radio_Light_Button */
    register_block("__Fl_Radio_Light_Button",fltk_fl_radio_light_button_Fl_Radio_Light_Button);
    /* Fl_Radio_Round_Button */
    register_block("__Fl_Radio_Round_Button",fltk_fl_radio_round_button_Fl_Radio_Round_Button);
    /* Fl_Repeat_Button */
    register_block("__Fl_Repeat_Button_handle",fltk_fl_repeat_button_handle);
    register_block("__Fl_Repeat_Button",fltk_fl_repeat_button_Fl_Repeat_Button);
    register_block("__Fl_Repeat_Button_deactivate",fltk_fl_repeat_button_deactivate);
    /* Fl_Return_Button */
    register_block("__Fl_Return_Button_handle_1",fltk_fl_return_button_handle_1);
    register_block("__Fl_Return_Button",fltk_fl_return_button_Fl_Return_Button);
    /* Fl_Roller */
    register_block("__Fl_Roller_handle_2",fltk_fl_roller_handle_2);
    register_block("__Fl_Roller",fltk_fl_roller_Fl_Roller);
    /* Fl_Round_Button */
    register_block("__Fl_Round_Button",fltk_fl_round_button_Fl_Round_Button);
    /* Fl_Round_Clock */
    register_block("__Fl_Round_Clock",fltk_fl_round_clock_Fl_Round_Clock);
    /* Fl_Scroll */
    register_block("__Fl_Scroll_resize",fltk_fl_scroll_resize);
    register_block("__Fl_Scroll_handle",fltk_fl_scroll_handle);
    register_block("__Fl_Scroll_HORIZONTAL",fltk_fl_scroll_HORIZONTAL);
    register_block("__Fl_Scroll_VERTICAL",fltk_fl_scroll_VERTICAL);
    register_block("__Fl_Scroll_BOTH",fltk_fl_scroll_BOTH);
    register_block("__Fl_Scroll_ALWAYS_ON",fltk_fl_scroll_ALWAYS_ON);
    register_block("__Fl_Scroll_HORIZONTAL_ALWAYS",fltk_fl_scroll_HORIZONTAL_ALWAYS);
    register_block("__Fl_Scroll_VERTICAL_ALWAYS",fltk_fl_scroll_VERTICAL_ALWAYS);
    register_block("__Fl_Scroll_BOTH_ALWAYS",fltk_fl_scroll_BOTH_ALWAYS);
    register_block("__Fl_Scroll_xposition",fltk_fl_scroll_xposition);
    register_block("__Fl_Scroll_yposition",fltk_fl_scroll_yposition);
    register_block("__Fl_Scroll_scroll_to",fltk_fl_scroll_scroll_to);
    register_block("__Fl_Scroll_clear",fltk_fl_scroll_clear);
    register_block("__Fl_Scroll_scrollbar_size",fltk_fl_scroll_scrollbar_size);
    register_block("__Fl_Scroll_scrollbar_size_1",fltk_fl_scroll_scrollbar_size_1);
    /* Fl_Scrollbar */
    register_block("__Fl_Scrollbar",fltk_fl_scrollbar_Fl_Scrollbar);
    register_block("__Fl_Scrollbar_handle_1",fltk_fl_scrollbar_handle_1);
    register_block("__Fl_Scrollbar_value",fltk_fl_scrollbar_value);
    register_block("__Fl_Scrollbar_value_1",fltk_fl_scrollbar_value_1);
    register_block("__Fl_Scrollbar_value_2",fltk_fl_scrollbar_value_2);
    register_block("__Fl_Scrollbar_linesize",fltk_fl_scrollbar_linesize);
    register_block("__Fl_Scrollbar_linesize_1",fltk_fl_scrollbar_linesize_1);
    /* Fl_Secret_Input */
    register_block("__Fl_Secret_Input",fltk_fl_secret_input_Fl_Secret_Input);
    register_block("__Fl_Secret_Input_handle_2",fltk_fl_secret_input_handle_2);
    /* Fl_Select_Browser */
    register_block("__Fl_Select_Browser",fltk_fl_select_browser_Fl_Select_Browser);
    /* Fl_Shared_Image */
    register_block("__Fl_Shared_Image_name",fltk_fl_shared_image_name);
    register_block("__Fl_Shared_Image_refcount",fltk_fl_shared_image_refcount);
    register_block("__Fl_Shared_Image_release",fltk_fl_shared_image_release);
    register_block("__Fl_Shared_Image_reload",fltk_fl_shared_image_reload);
    register_block("__Fl_Shared_Image_copy",fltk_fl_shared_image_copy);
    register_block("__Fl_Shared_Image_copy_1",fltk_fl_shared_image_copy_1);
    register_block("__Fl_Shared_Image_color_average",fltk_fl_shared_image_color_average);
    register_block("__Fl_Shared_Image_desaturate",fltk_fl_shared_image_desaturate);
    register_block("__Fl_Shared_Image_draw",fltk_fl_shared_image_draw);
    register_block("__Fl_Shared_Image_draw_1",fltk_fl_shared_image_draw_1);
    register_block("__Fl_Shared_Image_scale",fltk_fl_shared_image_scale);
    register_block("__Fl_Shared_Image_uncache",fltk_fl_shared_image_uncache);
    register_block("__Fl_Shared_Image_Fl_Shared_Image_find",fltk_fl_shared_image_Fl_Shared_Image_find);
    register_block("__Fl_Shared_Image_Fl_Shared_Image_get",fltk_fl_shared_image_Fl_Shared_Image_get);
    register_block("__Fl_Shared_Image_Fl_Shared_Image_get_1",fltk_fl_shared_image_Fl_Shared_Image_get_1);
    register_block("__Fl_Shared_Image_Fl_Shared_Image_images",fltk_fl_shared_image_Fl_Shared_Image_images);
    register_block("__Fl_Shared_Image_Fl_Shared_Image_num_images",fltk_fl_shared_image_Fl_Shared_Image_num_images);
    register_block("__Fl_Shared_Image_Fl_Shared_Image_add_handler",fltk_fl_shared_image_Fl_Shared_Image_add_handler);
    register_block("__Fl_Shared_Image_Fl_Shared_Image_remove_handler",fltk_fl_shared_image_Fl_Shared_Image_remove_handler);
    register_block("__Fl_Shared_Image_Fl_Shared_Image_scaling_algorithm",fltk_fl_shared_image_Fl_Shared_Image_scaling_algorithm);
    register_block("__fl_show_colormap",fltk_fl_show_colormap);
    /* Fl_Simple_Counter */
    register_block("__Fl_Simple_Counter",fltk_fl_simple_counter_Fl_Simple_Counter);
    /* Fl_Single_Window */
    register_block("__Fl_Single_Window_show",fltk_fl_single_window_show);
    register_block("__Fl_Single_Window_show_1",fltk_fl_single_window_show_1);
    register_block("__Fl_Single_Window",fltk_fl_single_window_Fl_Single_Window);
    register_block("__Fl_Single_Window_1",fltk_fl_single_window_Fl_Single_Window_1);
#ifdef Fl_Single_Window::make_current
    register_block("__Fl_Single_Window_make_current",fltk_fl_single_window_make_current);
#endif
    /* Fl_Slider */
    register_block("__Fl_Slider_handle_3",fltk_fl_slider_handle_3);
    register_block("__Fl_Slider",fltk_fl_slider_Fl_Slider);
    register_block("__Fl_Slider_1",fltk_fl_slider_Fl_Slider_1);
    register_block("__Fl_Slider_scrollvalue",fltk_fl_slider_scrollvalue);
    register_block("__Fl_Slider_bounds",fltk_fl_slider_bounds);
    register_block("__Fl_Slider_slider_size",fltk_fl_slider_slider_size);
    register_block("__Fl_Slider_slider_size_1",fltk_fl_slider_slider_size_1);
    register_block("__Fl_Slider_slider",fltk_fl_slider_slider);
    register_block("__Fl_Slider_slider_1",fltk_fl_slider_slider_1);
    /* Fl_Spinner */
    register_block("__Fl_Spinner",fltk_fl_spinner_Fl_Spinner);
    register_block("__Fl_Spinner_format",fltk_fl_spinner_format);
    register_block("__Fl_Spinner_format_1",fltk_fl_spinner_format_1);
    register_block("__Fl_Spinner_handle_4",fltk_fl_spinner_handle_4);
    register_block("__Fl_Spinner_maxinum",fltk_fl_spinner_maxinum);
    register_block("__Fl_Spinner_maximum",fltk_fl_spinner_maximum);
    register_block("__Fl_Spinner_maximum_1",fltk_fl_spinner_maximum_1);
    register_block("__Fl_Spinner_mininum",fltk_fl_spinner_mininum);
    register_block("__Fl_Spinner_minimum",fltk_fl_spinner_minimum);
    register_block("__Fl_Spinner_minimum_1",fltk_fl_spinner_minimum_1);
    register_block("__Fl_Spinner_range",fltk_fl_spinner_range);
    register_block("__Fl_Spinner_resize_1",fltk_fl_spinner_resize_1);
    register_block("__Fl_Spinner_step",fltk_fl_spinner_step);
    register_block("__Fl_Spinner_step_1",fltk_fl_spinner_step_1);
    register_block("__Fl_Spinner_textcolor",fltk_fl_spinner_textcolor);
    register_block("__Fl_Spinner_textcolor_1",fltk_fl_spinner_textcolor_1);
    register_block("__Fl_Spinner_textfont",fltk_fl_spinner_textfont);
    register_block("__Fl_Spinner_textfont_1",fltk_fl_spinner_textfont_1);
    register_block("__Fl_Spinner_textsize",fltk_fl_spinner_textsize);
    register_block("__Fl_Spinner_textsize_1",fltk_fl_spinner_textsize_1);
    register_block("__Fl_Spinner_type",fltk_fl_spinner_type);
    register_block("__Fl_Spinner_type_1",fltk_fl_spinner_type_1);
    register_block("__Fl_Spinner_value_3",fltk_fl_spinner_value_3);
    register_block("__Fl_Spinner_value_4",fltk_fl_spinner_value_4);
    register_block("__Fl_Spinner_color",fltk_fl_spinner_color);
    register_block("__Fl_Spinner_color_1",fltk_fl_spinner_color_1);
    register_block("__Fl_Spinner_selection_color",fltk_fl_spinner_selection_color);
    register_block("__Fl_Spinner_selection_color_1",fltk_fl_spinner_selection_color_1);
    /* Fl_Sys_Menu_Bar */
    register_block("__Fl_Sys_Menu_Bar",fltk_fl_sys_menu_bar_Fl_Sys_Menu_Bar);
    register_block("__Fl_Sys_Menu_Bar_menu",fltk_fl_sys_menu_bar_menu);
    register_block("__Fl_Sys_Menu_Bar_menu_1",fltk_fl_sys_menu_bar_menu_1);
    register_block("__Fl_Sys_Menu_Bar_add",fltk_fl_sys_menu_bar_add);
    register_block("__Fl_Sys_Menu_Bar_add_1",fltk_fl_sys_menu_bar_add_1);
    register_block("__Fl_Sys_Menu_Bar_add_2",fltk_fl_sys_menu_bar_add_2);
    register_block("__Fl_Sys_Menu_Bar_insert",fltk_fl_sys_menu_bar_insert);
    register_block("__Fl_Sys_Menu_Bar_insert_1",fltk_fl_sys_menu_bar_insert_1);
    register_block("__Fl_Sys_Menu_Bar_remove",fltk_fl_sys_menu_bar_remove);
    register_block("__Fl_Sys_Menu_Bar_replace",fltk_fl_sys_menu_bar_replace);
    register_block("__Fl_Sys_Menu_Bar_clear_1",fltk_fl_sys_menu_bar_clear_1);
    register_block("__Fl_Sys_Menu_Bar_clear_submenu",fltk_fl_sys_menu_bar_clear_submenu);
    register_block("__Fl_Sys_Menu_Bar_global",fltk_fl_sys_menu_bar_global);
    register_block("__Fl_Sys_Menu_Bar_mode",fltk_fl_sys_menu_bar_mode);
    register_block("__Fl_Sys_Menu_Bar_1",fltk_fl_sys_menu_bar_Fl_Sys_Menu_Bar_1);
    /* Fl_Tabs */
    register_block("__Fl_Tabs_handle",fltk_fl_tabs_handle);
    register_block("__Fl_Tabs_value",fltk_fl_tabs_value);
    register_block("__Fl_Tabs_value_1",fltk_fl_tabs_value_1);
    register_block("__Fl_Tabs_push",fltk_fl_tabs_push);
    register_block("__Fl_Tabs_push_1",fltk_fl_tabs_push_1);
    register_block("__Fl_Tabs",fltk_fl_tabs_Fl_Tabs);
    register_block("__Fl_Tabs_which",fltk_fl_tabs_which);
    register_block("__Fl_Tabs_client_area",fltk_fl_tabs_client_area);
    /* Fl_Text_Selection */
    register_block("__Fl_Text_Selection_set",fltk_fl_text_selection_set);
    register_block("__Fl_Text_Selection_update",fltk_fl_text_selection_update);
    register_block("__Fl_Text_Selection_start",fltk_fl_text_selection_start);
    register_block("__Fl_Text_Selection_end",fltk_fl_text_selection_end);
    register_block("__Fl_Text_Selection_selected",fltk_fl_text_selection_selected);
    register_block("__Fl_Text_Selection_selected_1",fltk_fl_text_selection_selected_1);
    register_block("__Fl_Text_Selection_includes",fltk_fl_text_selection_includes);
    register_block("__Fl_Text_Selection_position",fltk_fl_text_selection_position);
    /* Fl_Text_Buffer */
    register_block("__Fl_Text_Buffer",fltk_fl_text_buffer_Fl_Text_Buffer);
    register_block("__Fl_Text_Buffer_length",fltk_fl_text_buffer_length);
    register_block("__Fl_Text_Buffer_text",fltk_fl_text_buffer_text);
    register_block("__Fl_Text_Buffer_text_1",fltk_fl_text_buffer_text_1);
    register_block("__Fl_Text_Buffer_text_range",fltk_fl_text_buffer_text_range);
    register_block("__Fl_Text_Buffer_char_at",fltk_fl_text_buffer_char_at);
    register_block("__Fl_Text_Buffer_byte_at",fltk_fl_text_buffer_byte_at);
    register_block("__Fl_Text_Buffer_address",fltk_fl_text_buffer_address);
    register_block("__Fl_Text_Buffer_address_1",fltk_fl_text_buffer_address_1);
    register_block("__Fl_Text_Buffer_insert",fltk_fl_text_buffer_insert);
    register_block("__Fl_Text_Buffer_append",fltk_fl_text_buffer_append);
    register_block("__Fl_Text_Buffer_remove",fltk_fl_text_buffer_remove);
    register_block("__Fl_Text_Buffer_replace",fltk_fl_text_buffer_replace);
    register_block("__Fl_Text_Buffer_copy",fltk_fl_text_buffer_copy);
    register_block("__Fl_Text_Buffer_undo",fltk_fl_text_buffer_undo);
    register_block("__Fl_Text_Buffer_canUndo",fltk_fl_text_buffer_canUndo);
    register_block("__Fl_Text_Buffer_insertfile",fltk_fl_text_buffer_insertfile);
    register_block("__Fl_Text_Buffer_appendfile",fltk_fl_text_buffer_appendfile);
    register_block("__Fl_Text_Buffer_loadfile",fltk_fl_text_buffer_loadfile);
    register_block("__Fl_Text_Buffer_outputfile",fltk_fl_text_buffer_outputfile);
    register_block("__Fl_Text_Buffer_savefile",fltk_fl_text_buffer_savefile);
    register_block("__Fl_Text_Buffer_tab_distance",fltk_fl_text_buffer_tab_distance);
    register_block("__Fl_Text_Buffer_tab_distance_1",fltk_fl_text_buffer_tab_distance_1);
    register_block("__Fl_Text_Buffer_select",fltk_fl_text_buffer_select);
    register_block("__Fl_Text_Buffer_selected",fltk_fl_text_buffer_selected);
    register_block("__Fl_Text_Buffer_unselect",fltk_fl_text_buffer_unselect);
    register_block("__Fl_Text_Buffer_selection_position",fltk_fl_text_buffer_selection_position);
    register_block("__Fl_Text_Buffer_selection_text",fltk_fl_text_buffer_selection_text);
    register_block("__Fl_Text_Buffer_remove_selection",fltk_fl_text_buffer_remove_selection);
    register_block("__Fl_Text_Buffer_replace_selection",fltk_fl_text_buffer_replace_selection);
    register_block("__Fl_Text_Buffer_secondary_select",fltk_fl_text_buffer_secondary_select);
    register_block("__Fl_Text_Buffer_secondary_selected",fltk_fl_text_buffer_secondary_selected);
    register_block("__Fl_Text_Buffer_secondary_unselect",fltk_fl_text_buffer_secondary_unselect);
    register_block("__Fl_Text_Buffer_secondary_selection_position",fltk_fl_text_buffer_secondary_selection_position);
    register_block("__Fl_Text_Buffer_secondary_selection_text",fltk_fl_text_buffer_secondary_selection_text);
    register_block("__Fl_Text_Buffer_remove_secondary_selection",fltk_fl_text_buffer_remove_secondary_selection);
    register_block("__Fl_Text_Buffer_replace_secondary_selection",fltk_fl_text_buffer_replace_secondary_selection);
    register_block("__Fl_Text_Buffer_highlight",fltk_fl_text_buffer_highlight);
    register_block("__Fl_Text_Buffer_highlight_1",fltk_fl_text_buffer_highlight_1);
    register_block("__Fl_Text_Buffer_unhighlight",fltk_fl_text_buffer_unhighlight);
    register_block("__Fl_Text_Buffer_highlight_position",fltk_fl_text_buffer_highlight_position);
    register_block("__Fl_Text_Buffer_highlight_text",fltk_fl_text_buffer_highlight_text);
    register_block("__Fl_Text_Buffer_add_modify_callback",fltk_fl_text_buffer_add_modify_callback);
    register_block("__Fl_Text_Buffer_remove_modify_callback",fltk_fl_text_buffer_remove_modify_callback);
    register_block("__Fl_Text_Buffer_call_modify_callbacks",fltk_fl_text_buffer_call_modify_callbacks);
    register_block("__Fl_Text_Buffer_add_predelete_callback",fltk_fl_text_buffer_add_predelete_callback);
    register_block("__Fl_Text_Buffer_remove_predelete_callback",fltk_fl_text_buffer_remove_predelete_callback);
    register_block("__Fl_Text_Buffer_call_predelete_callbacks",fltk_fl_text_buffer_call_predelete_callbacks);
    register_block("__Fl_Text_Buffer_line_text",fltk_fl_text_buffer_line_text);
    register_block("__Fl_Text_Buffer_line_start",fltk_fl_text_buffer_line_start);
    register_block("__Fl_Text_Buffer_line_end",fltk_fl_text_buffer_line_end);
    register_block("__Fl_Text_Buffer_word_start",fltk_fl_text_buffer_word_start);
    register_block("__Fl_Text_Buffer_word_end",fltk_fl_text_buffer_word_end);
    register_block("__Fl_Text_Buffer_count_displayed_characters",fltk_fl_text_buffer_count_displayed_characters);
    register_block("__Fl_Text_Buffer_skip_displayed_characters",fltk_fl_text_buffer_skip_displayed_characters);
    register_block("__Fl_Text_Buffer_count_lines",fltk_fl_text_buffer_count_lines);
    register_block("__Fl_Text_Buffer_skip_lines",fltk_fl_text_buffer_skip_lines);
    register_block("__Fl_Text_Buffer_rewind_lines",fltk_fl_text_buffer_rewind_lines);
    register_block("__Fl_Text_Buffer_findchar_forward",fltk_fl_text_buffer_findchar_forward);
    register_block("__Fl_Text_Buffer_findchar_backward",fltk_fl_text_buffer_findchar_backward);
    register_block("__Fl_Text_Buffer_primary_selection",fltk_fl_text_buffer_primary_selection);
    register_block("__Fl_Text_Buffer_primary_selection_1",fltk_fl_text_buffer_primary_selection_1);
    register_block("__Fl_Text_Buffer_secondary_selection",fltk_fl_text_buffer_secondary_selection);
    register_block("__Fl_Text_Buffer_highlight_selection",fltk_fl_text_buffer_highlight_selection);
    register_block("__Fl_Text_Buffer_prev_char",fltk_fl_text_buffer_prev_char);
    register_block("__Fl_Text_Buffer_prev_char_clipped",fltk_fl_text_buffer_prev_char_clipped);
    register_block("__Fl_Text_Buffer_next_char",fltk_fl_text_buffer_next_char);
    register_block("__Fl_Text_Buffer_next_char_clipped",fltk_fl_text_buffer_next_char_clipped);
    register_block("__Fl_Text_Buffer_utf8_align",fltk_fl_text_buffer_utf8_align);
    register_block("__Fl_Text_Buffer_Fl_Text_Buffer_file_encoding_warning_message",fltk_fl_text_buffer_Fl_Text_Buffer_file_encoding_warning_message);
    /* Fl_Text_Display */
    register_block("__Fl_Text_Display_NORMAL_CURSOR",fltk_fl_text_display_NORMAL_CURSOR);
    register_block("__Fl_Text_Display_CARET_CURSOR",fltk_fl_text_display_CARET_CURSOR);
    register_block("__Fl_Text_Display_DIM_CURSOR",fltk_fl_text_display_DIM_CURSOR);
    register_block("__Fl_Text_Display_BLOCK_CURSOR",fltk_fl_text_display_BLOCK_CURSOR);
    register_block("__Fl_Text_Display_HEAVY_CURSOR",fltk_fl_text_display_HEAVY_CURSOR);
    register_block("__Fl_Text_Display_CURSOR_POS",fltk_fl_text_display_CURSOR_POS);
    register_block("__Fl_Text_Display_DRAG_NONE",fltk_fl_text_display_DRAG_NONE);
    register_block("__Fl_Text_Display_DRAG_START_DND",fltk_fl_text_display_DRAG_START_DND);
    register_block("__Fl_Text_Display_DRAG_CHAR",fltk_fl_text_display_DRAG_CHAR);
    register_block("__Fl_Text_Display_DRAG_WORD",fltk_fl_text_display_DRAG_WORD);
    register_block("__Fl_Text_Display_DRAG_LINE",fltk_fl_text_display_DRAG_LINE);
    register_block("__Fl_Text_Display_WRAP_NONE",fltk_fl_text_display_WRAP_NONE);
    register_block("__Fl_Text_Display_WRAP_AT_COLUMN",fltk_fl_text_display_WRAP_AT_COLUMN);
    register_block("__Fl_Text_Display_WRAP_AT_PIXEL",fltk_fl_text_display_WRAP_AT_PIXEL);
    register_block("__Fl_Text_Display_handle_1",fltk_fl_text_display_handle_1);
    register_block("__Fl_Text_Display_buffer",fltk_fl_text_display_buffer);
    register_block("__Fl_Text_Display_buffer_1",fltk_fl_text_display_buffer_1);
    register_block("__Fl_Text_Display_buffer_2",fltk_fl_text_display_buffer_2);
    register_block("__Fl_Text_Display_redisplay_range",fltk_fl_text_display_redisplay_range);
    register_block("__Fl_Text_Display_scroll",fltk_fl_text_display_scroll);
    register_block("__Fl_Text_Display_insert",fltk_fl_text_display_insert);
    register_block("__Fl_Text_Display_overstrike",fltk_fl_text_display_overstrike);
    register_block("__Fl_Text_Display_insert_position",fltk_fl_text_display_insert_position);
    register_block("__Fl_Text_Display_insert_position_1",fltk_fl_text_display_insert_position_1);
    register_block("__Fl_Text_Display_position_to_xy",fltk_fl_text_display_position_to_xy);
    register_block("__Fl_Text_Display_in_selection",fltk_fl_text_display_in_selection);
    register_block("__Fl_Text_Display_show_insert_position",fltk_fl_text_display_show_insert_position);
    register_block("__Fl_Text_Display_move_right",fltk_fl_text_display_move_right);
    register_block("__Fl_Text_Display_move_left",fltk_fl_text_display_move_left);
    register_block("__Fl_Text_Display_move_up",fltk_fl_text_display_move_up);
    register_block("__Fl_Text_Display_move_down",fltk_fl_text_display_move_down);
    register_block("__Fl_Text_Display_count_lines",fltk_fl_text_display_count_lines);
    register_block("__Fl_Text_Display_line_start",fltk_fl_text_display_line_start);
    register_block("__Fl_Text_Display_line_end",fltk_fl_text_display_line_end);
    register_block("__Fl_Text_Display_skip_lines",fltk_fl_text_display_skip_lines);
    register_block("__Fl_Text_Display_rewind_lines",fltk_fl_text_display_rewind_lines);
    register_block("__Fl_Text_Display_next_word",fltk_fl_text_display_next_word);
    register_block("__Fl_Text_Display_previous_word",fltk_fl_text_display_previous_word);
    register_block("__Fl_Text_Display_show_cursor",fltk_fl_text_display_show_cursor);
    register_block("__Fl_Text_Display_hide_cursor",fltk_fl_text_display_hide_cursor);
    register_block("__Fl_Text_Display_cursor_style",fltk_fl_text_display_cursor_style);
    register_block("__Fl_Text_Display_cursor_color",fltk_fl_text_display_cursor_color);
    register_block("__Fl_Text_Display_cursor_color_1",fltk_fl_text_display_cursor_color_1);
    register_block("__Fl_Text_Display_scrollbar_width",fltk_fl_text_display_scrollbar_width);
    register_block("__Fl_Text_Display_scrollbar_width_1",fltk_fl_text_display_scrollbar_width_1);
    register_block("__Fl_Text_Display_scrollbar_align",fltk_fl_text_display_scrollbar_align);
    register_block("__Fl_Text_Display_scrollbar_align_1",fltk_fl_text_display_scrollbar_align_1);
    register_block("__Fl_Text_Display_word_start",fltk_fl_text_display_word_start);
    register_block("__Fl_Text_Display_word_end",fltk_fl_text_display_word_end);
    register_block("__Fl_Text_Display_highlight_data",fltk_fl_text_display_highlight_data);
    register_block("__Fl_Text_Display_position_style",fltk_fl_text_display_position_style);
    register_block("__Fl_Text_Display_shortcut",fltk_fl_text_display_shortcut);
    register_block("__Fl_Text_Display_shortcut_1",fltk_fl_text_display_shortcut_1);
    register_block("__Fl_Text_Display_textfont",fltk_fl_text_display_textfont);
    register_block("__Fl_Text_Display_textfont_1",fltk_fl_text_display_textfont_1);
    register_block("__Fl_Text_Display_textsize",fltk_fl_text_display_textsize);
    register_block("__Fl_Text_Display_textsize_1",fltk_fl_text_display_textsize_1);
    register_block("__Fl_Text_Display_textcolor",fltk_fl_text_display_textcolor);
    register_block("__Fl_Text_Display_textcolor_1",fltk_fl_text_display_textcolor_1);
    register_block("__Fl_Text_Display_wrapped_column",fltk_fl_text_display_wrapped_column);
    register_block("__Fl_Text_Display_wrapped_row",fltk_fl_text_display_wrapped_row);
    register_block("__Fl_Text_Display_wrap_mode",fltk_fl_text_display_wrap_mode);
    register_block("__Fl_Text_Display_resize",fltk_fl_text_display_resize);
    register_block("__Fl_Text_Display_x_to_col",fltk_fl_text_display_x_to_col);
    register_block("__Fl_Text_Display_col_to_x",fltk_fl_text_display_col_to_x);
    register_block("__Fl_Text_Display_linenumber_width",fltk_fl_text_display_linenumber_width);
    register_block("__Fl_Text_Display_linenumber_width_1",fltk_fl_text_display_linenumber_width_1);
    register_block("__Fl_Text_Display_linenumber_font",fltk_fl_text_display_linenumber_font);
    register_block("__Fl_Text_Display_linenumber_font_1",fltk_fl_text_display_linenumber_font_1);
    register_block("__Fl_Text_Display_linenumber_size",fltk_fl_text_display_linenumber_size);
    register_block("__Fl_Text_Display_linenumber_size_1",fltk_fl_text_display_linenumber_size_1);
    register_block("__Fl_Text_Display_linenumber_fgcolor",fltk_fl_text_display_linenumber_fgcolor);
    register_block("__Fl_Text_Display_linenumber_fgcolor_1",fltk_fl_text_display_linenumber_fgcolor_1);
    register_block("__Fl_Text_Display_linenumber_bgcolor",fltk_fl_text_display_linenumber_bgcolor);
    register_block("__Fl_Text_Display_linenumber_bgcolor_1",fltk_fl_text_display_linenumber_bgcolor_1);
    register_block("__Fl_Text_Display_linenumber_align",fltk_fl_text_display_linenumber_align);
    register_block("__Fl_Text_Display_linenumber_align_1",fltk_fl_text_display_linenumber_align_1);
    register_block("__Fl_Text_Display_linenumber_format",fltk_fl_text_display_linenumber_format);
    register_block("__Fl_Text_Display_linenumber_format_1",fltk_fl_text_display_linenumber_format_1);
    /* Fl_Text_Editor */
    register_block("__Fl_Text_Editor",fltk_fl_text_editor_Fl_Text_Editor);
    register_block("__Fl_Text_Editor_handle_2",fltk_fl_text_editor_handle_2);
    register_block("__Fl_Text_Editor_insert_mode",fltk_fl_text_editor_insert_mode);
    register_block("__Fl_Text_Editor_insert_mode_1",fltk_fl_text_editor_insert_mode_1);
    register_block("__Fl_Text_Editor_add_key_binding",fltk_fl_text_editor_add_key_binding);
    register_block("__Fl_Text_Editor_add_key_binding_1",fltk_fl_text_editor_add_key_binding_1);
    register_block("__Fl_Text_Editor_remove_key_binding",fltk_fl_text_editor_remove_key_binding);
    register_block("__Fl_Text_Editor_remove_key_binding_1",fltk_fl_text_editor_remove_key_binding_1);
    register_block("__Fl_Text_Editor_remove_all_key_bindings",fltk_fl_text_editor_remove_all_key_bindings);
    register_block("__Fl_Text_Editor_remove_all_key_bindings_1",fltk_fl_text_editor_remove_all_key_bindings_1);
    register_block("__Fl_Text_Editor_add_default_key_bindings",fltk_fl_text_editor_add_default_key_bindings);
    register_block("__Fl_Text_Editor_bound_key_function",fltk_fl_text_editor_bound_key_function);
    register_block("__Fl_Text_Editor_bound_key_function_1",fltk_fl_text_editor_bound_key_function_1);
    register_block("__Fl_Text_Editor_bound_key_function_2",fltk_fl_text_editor_bound_key_function_2);
    register_block("__Fl_Text_Editor_bound_key_function_3",fltk_fl_text_editor_bound_key_function_3);
    register_block("__Fl_Text_Editor_default_key_function",fltk_fl_text_editor_default_key_function);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_default",fltk_fl_text_editor_Fl_Text_Editor_kf_default);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_ignore",fltk_fl_text_editor_Fl_Text_Editor_kf_ignore);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_backspace",fltk_fl_text_editor_Fl_Text_Editor_kf_backspace);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_enter",fltk_fl_text_editor_Fl_Text_Editor_kf_enter);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_move",fltk_fl_text_editor_Fl_Text_Editor_kf_move);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_shift_move",fltk_fl_text_editor_Fl_Text_Editor_kf_shift_move);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_ctrl_move",fltk_fl_text_editor_Fl_Text_Editor_kf_ctrl_move);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_c_s_move",fltk_fl_text_editor_Fl_Text_Editor_kf_c_s_move);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_meta_move",fltk_fl_text_editor_Fl_Text_Editor_kf_meta_move);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_m_s_move",fltk_fl_text_editor_Fl_Text_Editor_kf_m_s_move);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_home",fltk_fl_text_editor_Fl_Text_Editor_kf_home);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_end",fltk_fl_text_editor_Fl_Text_Editor_kf_end);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_left",fltk_fl_text_editor_Fl_Text_Editor_kf_left);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_up",fltk_fl_text_editor_Fl_Text_Editor_kf_up);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_right",fltk_fl_text_editor_Fl_Text_Editor_kf_right);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_down",fltk_fl_text_editor_Fl_Text_Editor_kf_down);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_page_up",fltk_fl_text_editor_Fl_Text_Editor_kf_page_up);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_page_down",fltk_fl_text_editor_Fl_Text_Editor_kf_page_down);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_insert",fltk_fl_text_editor_Fl_Text_Editor_kf_insert);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_delete",fltk_fl_text_editor_Fl_Text_Editor_kf_delete);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_copy",fltk_fl_text_editor_Fl_Text_Editor_kf_copy);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_cut",fltk_fl_text_editor_Fl_Text_Editor_kf_cut);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_paste",fltk_fl_text_editor_Fl_Text_Editor_kf_paste);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_select_all",fltk_fl_text_editor_Fl_Text_Editor_kf_select_all);
    register_block("__Fl_Text_Editor_Fl_Text_Editor_kf_undo",fltk_fl_text_editor_Fl_Text_Editor_kf_undo);
    /* Fl_Tile */
    register_block("__Fl_Tile_handle",fltk_fl_tile_handle);
    register_block("__Fl_Tile",fltk_fl_tile_Fl_Tile);
    register_block("__Fl_Tile_resize",fltk_fl_tile_resize);
    register_block("__Fl_Tile_position",fltk_fl_tile_position);
    /* Fl_Tiled_Image */
    register_block("__Fl_Tiled_Image",fltk_fl_tiled_image_Fl_Tiled_Image);
    register_block("__Fl_Tiled_Image_copy",fltk_fl_tiled_image_copy);
    register_block("__Fl_Tiled_Image_copy_1",fltk_fl_tiled_image_copy_1);
    register_block("__Fl_Tiled_Image_color_average",fltk_fl_tiled_image_color_average);
    register_block("__Fl_Tiled_Image_desaturate",fltk_fl_tiled_image_desaturate);
    register_block("__Fl_Tiled_Image_draw",fltk_fl_tiled_image_draw);
    register_block("__Fl_Tiled_Image_draw_1",fltk_fl_tiled_image_draw_1);
    register_block("__Fl_Tiled_Image_image",fltk_fl_tiled_image_image);
    /* Fl_Timer */
#ifndef __ANDROID__
    register_block("__Fl_Timer_handle_1",fltk_fl_timer_handle_1);
	register_block("__Fl_Timer",fltk_fl_timer_Fl_Timer);
	register_block("__Fl_Timer_value",fltk_fl_timer_value);
	register_block("__Fl_Timer_value_1",fltk_fl_timer_value_1);
	register_block("__Fl_Timer_direction",fltk_fl_timer_direction);
	register_block("__Fl_Timer_direction_1",fltk_fl_timer_direction_1);
	register_block("__Fl_Timer_suspended",fltk_fl_timer_suspended);
	register_block("__Fl_Timer_suspended_1",fltk_fl_timer_suspended_1);
#endif
    /* Fl_Toggle_Button */
    register_block("__Fl_Toggle_Button",fltk_fl_toggle_button_Fl_Toggle_Button);
    /* Fl_Tooltip */
    register_block("__Fl_Tooltip_Fl_Tooltip_delay",fltk_fl_tooltip_Fl_Tooltip_delay);
    register_block("__Fl_Tooltip_Fl_Tooltip_delay_1",fltk_fl_tooltip_Fl_Tooltip_delay_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_hoverdelay",fltk_fl_tooltip_Fl_Tooltip_hoverdelay);
    register_block("__Fl_Tooltip_Fl_Tooltip_hoverdelay_1",fltk_fl_tooltip_Fl_Tooltip_hoverdelay_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_enabled",fltk_fl_tooltip_Fl_Tooltip_enabled);
    register_block("__Fl_Tooltip_Fl_Tooltip_enable",fltk_fl_tooltip_Fl_Tooltip_enable);
    register_block("__Fl_Tooltip_Fl_Tooltip_disable",fltk_fl_tooltip_Fl_Tooltip_disable);
    register_block("__Fl_Tooltip_Fl_Tooltip_enter_area",fltk_fl_tooltip_Fl_Tooltip_enter_area);
    register_block("__Fl_Tooltip_Fl_Tooltip_current",fltk_fl_tooltip_Fl_Tooltip_current);
    register_block("__Fl_Tooltip_Fl_Tooltip_current_1",fltk_fl_tooltip_Fl_Tooltip_current_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_font",fltk_fl_tooltip_Fl_Tooltip_font);
    register_block("__Fl_Tooltip_Fl_Tooltip_font_1",fltk_fl_tooltip_Fl_Tooltip_font_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_size",fltk_fl_tooltip_Fl_Tooltip_size);
    register_block("__Fl_Tooltip_Fl_Tooltip_size_1",fltk_fl_tooltip_Fl_Tooltip_size_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_color",fltk_fl_tooltip_Fl_Tooltip_color);
    register_block("__Fl_Tooltip_Fl_Tooltip_color_1",fltk_fl_tooltip_Fl_Tooltip_color_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_textcolor",fltk_fl_tooltip_Fl_Tooltip_textcolor);
    register_block("__Fl_Tooltip_Fl_Tooltip_textcolor_1",fltk_fl_tooltip_Fl_Tooltip_textcolor_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_margin_width",fltk_fl_tooltip_Fl_Tooltip_margin_width);
    register_block("__Fl_Tooltip_Fl_Tooltip_margin_width_1",fltk_fl_tooltip_Fl_Tooltip_margin_width_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_margin_height",fltk_fl_tooltip_Fl_Tooltip_margin_height);
    register_block("__Fl_Tooltip_Fl_Tooltip_margin_height_1",fltk_fl_tooltip_Fl_Tooltip_margin_height_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_wrap_width",fltk_fl_tooltip_Fl_Tooltip_wrap_width);
    register_block("__Fl_Tooltip_Fl_Tooltip_wrap_width_1",fltk_fl_tooltip_Fl_Tooltip_wrap_width_1);
    register_block("__Fl_Tooltip_Fl_Tooltip_margin_width_2",fltk_fl_tooltip_Fl_Tooltip_margin_width_2);
    register_block("__Fl_Tooltip_Fl_Tooltip_margin_height_2",fltk_fl_tooltip_Fl_Tooltip_margin_height_2);
    register_block("__Fl_Tooltip_Fl_Tooltip_wrap_width_2",fltk_fl_tooltip_Fl_Tooltip_wrap_width_2);
#ifdef __APPLE__
    register_block("__Fl_Tooltip_Fl_Tooltip_current_window",fltk_fl_tooltip_Fl_Tooltip_current_window);
#endif
    /* Fl_Tree */
    register_block("__FL_TREE_REASON_NONE",fltk_FL_TREE_REASON_NONE);
    register_block("__FL_TREE_REASON_SELECTED",fltk_FL_TREE_REASON_SELECTED);
    register_block("__FL_TREE_REASON_DESELECTED",fltk_FL_TREE_REASON_DESELECTED);
#if FLTK_ABI_VERSION >= 10301
    register_block("__FL_TREE_REASON_RESELECTED",fltk_FL_TREE_REASON_RESELECTED);
#endif
    register_block("__FL_TREE_REASON_OPENED",fltk_FL_TREE_REASON_OPENED);
    register_block("__FL_TREE_REASON_CLOSED",fltk_FL_TREE_REASON_CLOSED);
    register_block("__Fl_Tree",fltk_fl_tree_Fl_Tree);
    register_block("__Fl_Tree_handle",fltk_fl_tree_handle);
    register_block("__Fl_Tree_draw",fltk_fl_tree_draw);
    register_block("__Fl_Tree_show_self",fltk_fl_tree_show_self);
    register_block("__Fl_Tree_resize",fltk_fl_tree_resize);
    register_block("__Fl_Tree_root_label",fltk_fl_tree_root_label);
    register_block("__Fl_Tree_root",fltk_fl_tree_root);
    register_block("__Fl_Tree_root_1",fltk_fl_tree_root_1);
    register_block("__Fl_Tree_prefs",fltk_fl_tree_prefs);
    register_block("__Fl_Tree_add",fltk_fl_tree_add);
    register_block("__Fl_Tree_add_1",fltk_fl_tree_add_1);
    register_block("__Fl_Tree_add_2",fltk_fl_tree_add_2);
    register_block("__Fl_Tree_add_3",fltk_fl_tree_add_3);
    register_block("__Fl_Tree_insert_above",fltk_fl_tree_insert_above);
    register_block("__Fl_Tree_insert",fltk_fl_tree_insert);
    register_block("__Fl_Tree_remove",fltk_fl_tree_remove);
    register_block("__Fl_Tree_clear",fltk_fl_tree_clear);
    register_block("__Fl_Tree_clear_children",fltk_fl_tree_clear_children);
    register_block("__Fl_Tree_find_item",fltk_fl_tree_find_item);
    register_block("__Fl_Tree_find_item_1",fltk_fl_tree_find_item_1);
    register_block("__Fl_Tree_item_pathname",fltk_fl_tree_item_pathname);
#if FLTK_ABI_VERSION >= 10303
    register_block("__Fl_Tree_find_clicked",fltk_fl_tree_find_clicked);
	register_block("__Fl_Tree_find_clicked_1",fltk_fl_tree_find_clicked_1);
#else
    register_block("__Fl_Tree_find_clicked_2",fltk_fl_tree_find_clicked_2);
    register_block("__Fl_Tree_item_clicked_3",fltk_fl_tree_item_clicked_3);
#endif
    register_block("__Fl_Tree_first",fltk_fl_tree_first);
    register_block("__Fl_Tree_first_visible",fltk_fl_tree_first_visible);
    register_block("__Fl_Tree_first_visible_item",fltk_fl_tree_first_visible_item);
    register_block("__Fl_Tree_next",fltk_fl_tree_next);
    register_block("__Fl_Tree_prev",fltk_fl_tree_prev);
    register_block("__Fl_Tree_last",fltk_fl_tree_last);
    register_block("__Fl_Tree_last_visible",fltk_fl_tree_last_visible);
    register_block("__Fl_Tree_last_visible_item",fltk_fl_tree_last_visible_item);
    register_block("__Fl_Tree_first_selected_item",fltk_fl_tree_first_selected_item);
    register_block("__Fl_Tree_last_selected_item",fltk_fl_tree_last_selected_item);
    register_block("__Fl_Tree_next_item",fltk_fl_tree_next_item);
#if FLTK_ABI_VERSION >= 10303
    register_block("__Fl_Tree_next_selected_item",fltk_fl_tree_next_selected_item);
	register_block("__Fl_Tree_get_selected_items",fltk_fl_tree_get_selected_items);
#else
    register_block("__Fl_Tree_next_selected_item_1",fltk_fl_tree_next_selected_item_1);
    register_block("__Fl_Tree_next_selected_item_2",fltk_fl_tree_next_selected_item_2);
#endif
    register_block("__Fl_Tree_open",fltk_fl_tree_open);
    register_block("__Fl_Tree_open_1",fltk_fl_tree_open_1);
    register_block("__Fl_Tree_open_toggle",fltk_fl_tree_open_toggle);
    register_block("__Fl_Tree_close",fltk_fl_tree_close);
    register_block("__Fl_Tree_close_1",fltk_fl_tree_close_1);
    register_block("__Fl_Tree_is_open",fltk_fl_tree_is_open);
    register_block("__Fl_Tree_is_open_1",fltk_fl_tree_is_open_1);
    register_block("__Fl_Tree_is_close",fltk_fl_tree_is_close);
    register_block("__Fl_Tree_is_close_1",fltk_fl_tree_is_close_1);
    register_block("__Fl_Tree_select",fltk_fl_tree_select);
    register_block("__Fl_Tree_select_1",fltk_fl_tree_select_1);
    register_block("__Fl_Tree_select_toggle",fltk_fl_tree_select_toggle);
    register_block("__Fl_Tree_deselect",fltk_fl_tree_deselect);
    register_block("__Fl_Tree_deselect_1",fltk_fl_tree_deselect_1);
    register_block("__Fl_Tree_deselect_all",fltk_fl_tree_deselect_all);
    register_block("__Fl_Tree_select_only",fltk_fl_tree_select_only);
    register_block("__Fl_Tree_select_all",fltk_fl_tree_select_all);
    register_block("__Fl_Tree_extend_selection_dir",fltk_fl_tree_extend_selection_dir);
#if FLTK_ABI_VERSION >= 10303
    register_block("__Fl_Tree_extend_selection",fltk_fl_tree_extend_selection);
#endif
    register_block("__Fl_Tree_set_item_focus",fltk_fl_tree_set_item_focus);
    register_block("__Fl_Tree_get_item_focus",fltk_fl_tree_get_item_focus);
    register_block("__Fl_Tree_is_selected",fltk_fl_tree_is_selected);
    register_block("__Fl_Tree_is_selected_1",fltk_fl_tree_is_selected_1);
    register_block("__Fl_Tree_item_labelfont_tree",fltk_fl_tree_item_labelfont_tree);
    register_block("__Fl_Tree_item_labelfont_tree_1",fltk_fl_tree_item_labelfont_tree_1);
    register_block("__Fl_Tree_item_labelsize_tree",fltk_fl_tree_item_labelsize_tree);
    register_block("__Fl_Tree_item_labelsize_tree_1",fltk_fl_tree_item_labelsize_tree_1);
    register_block("__Fl_Tree_item_labelfgcolor_tree",fltk_fl_tree_item_labelfgcolor_tree);
    register_block("__Fl_Tree_item_labelfgcolor_tree_1",fltk_fl_tree_item_labelfgcolor_tree_1);
    register_block("__Fl_Tree_item_labelbgcolor_tree",fltk_fl_tree_item_labelbgcolor_tree);
    register_block("__Fl_Tree_item_labelbgcolor_tree_1",fltk_fl_tree_item_labelbgcolor_tree_1);
    register_block("__Fl_Tree_connectorcolor",fltk_fl_tree_connectorcolor);
    register_block("__Fl_Tree_connectorcolor_1",fltk_fl_tree_connectorcolor_1);
    register_block("__Fl_Tree_marginleft",fltk_fl_tree_marginleft);
    register_block("__Fl_Tree_marginleft_1",fltk_fl_tree_marginleft_1);
    register_block("__Fl_Tree_margintop",fltk_fl_tree_margintop);
    register_block("__Fl_Tree_margintop_1",fltk_fl_tree_margintop_1);
#if FLTK_ABI_VERSION >= 10301
    register_block("__Fl_Tree_marginbottom",fltk_fl_tree_marginbottom);
	register_block("__Fl_Tree_marginbottom_1",fltk_fl_tree_marginbottom_1);
#endif
    register_block("__Fl_Tree_linespacing",fltk_fl_tree_linespacing);
    register_block("__Fl_Tree_linespacing_1",fltk_fl_tree_linespacing_1);
    register_block("__Fl_Tree_openchild_marginbottom",fltk_fl_tree_openchild_marginbottom);
    register_block("__Fl_Tree_openchild_marginbottom_1",fltk_fl_tree_openchild_marginbottom_1);
    register_block("__Fl_Tree_usericonmarginleft",fltk_fl_tree_usericonmarginleft);
    register_block("__Fl_Tree_usericonmarginleft_1",fltk_fl_tree_usericonmarginleft_1);
    register_block("__Fl_Tree_labelmarginleft",fltk_fl_tree_labelmarginleft);
    register_block("__Fl_Tree_labelmarginleft_1",fltk_fl_tree_labelmarginleft_1);
#if FLTK_ABI_VERSION >= 10301
    register_block("__Fl_Tree_widgetmarginleft",fltk_fl_tree_widgetmarginleft);
	register_block("__Fl_Tree_widgetmarginleft_1",fltk_fl_tree_widgetmarginleft_1);
#endif
    register_block("__Fl_Tree_connectorwidth",fltk_fl_tree_connectorwidth);
    register_block("__Fl_Tree_connectorwidth_1",fltk_fl_tree_connectorwidth_1);
    register_block("__Fl_Tree_usericon",fltk_fl_tree_usericon);
    register_block("__Fl_Tree_usericon_1",fltk_fl_tree_usericon_1);
    register_block("__Fl_Tree_openicon",fltk_fl_tree_openicon);
    register_block("__Fl_Tree_openicon_1",fltk_fl_tree_openicon_1);
    register_block("__Fl_Tree_closeicon",fltk_fl_tree_closeicon);
    register_block("__Fl_Tree_closeicon_1",fltk_fl_tree_closeicon_1);
    register_block("__Fl_Tree_showcollapse",fltk_fl_tree_showcollapse);
    register_block("__Fl_Tree_showcollapse_1",fltk_fl_tree_showcollapse_1);
    register_block("__Fl_Tree_showroot",fltk_fl_tree_showroot);
    register_block("__Fl_Tree_showroot_1",fltk_fl_tree_showroot_1);
    register_block("__Fl_Tree_connectorstyle",fltk_fl_tree_connectorstyle);
    register_block("__Fl_Tree_connectorstyle_1",fltk_fl_tree_connectorstyle_1);
    register_block("__Fl_Tree_sortorder",fltk_fl_tree_sortorder);
    register_block("__Fl_Tree_sortorder_1",fltk_fl_tree_sortorder_1);
    register_block("__Fl_Tree_selectbox",fltk_fl_tree_selectbox);
    register_block("__Fl_Tree_selectbox_1",fltk_fl_tree_selectbox_1);
    register_block("__Fl_Tree_selectmode",fltk_fl_tree_selectmode);
    register_block("__Fl_Tree_selectmode_1",fltk_fl_tree_selectmode_1);
#if FLTK_ABI_VERSION >= 10301
    register_block("__Fl_Tree_item_reselect_mode",fltk_fl_tree_item_reselect_mode);
	register_block("__Fl_Tree_item_reselect_mode_1",fltk_fl_tree_item_reselect_mode_1);
	register_block("__Fl_Tree_item_draw_mode",fltk_fl_tree_item_draw_mode);
	register_block("__Fl_Tree_item_draw_mode_1",fltk_fl_tree_item_draw_mode_1);
	register_block("__Fl_Tree_item_draw_mode_2",fltk_fl_tree_item_draw_mode_2);
#endif
#if FLTK_ABI_VERSION >= 10303
    register_block("__Fl_Tree_calc_dimensions",fltk_fl_tree_calc_dimensions);
	register_block("__Fl_Tree_calc_tree",fltk_fl_tree_calc_tree);
#endif
    register_block("__Fl_Tree_recalc_tree",fltk_fl_tree_recalc_tree);
    register_block("__Fl_Tree_displayed",fltk_fl_tree_displayed);
    register_block("__Fl_Tree_show_item",fltk_fl_tree_show_item);
    register_block("__Fl_Tree_show_item_1",fltk_fl_tree_show_item_1);
    register_block("__Fl_Tree_show_item_top",fltk_fl_tree_show_item_top);
    register_block("__Fl_Tree_show_item_middle",fltk_fl_tree_show_item_middle);
    register_block("__Fl_Tree_show_item_bottom",fltk_fl_tree_show_item_bottom);
    register_block("__Fl_Tree_display",fltk_fl_tree_display);
    register_block("__Fl_Tree_vposition",fltk_fl_tree_vposition);
    register_block("__Fl_Tree_vposition_1",fltk_fl_tree_vposition_1);
    register_block("__Fl_Tree_hposition",fltk_fl_tree_hposition);
    register_block("__Fl_Tree_hposition_1",fltk_fl_tree_hposition_1);
    register_block("__Fl_Tree_is_scrollbar",fltk_fl_tree_is_scrollbar);
    register_block("__Fl_Tree_scrollbar_size",fltk_fl_tree_scrollbar_size);
    register_block("__Fl_Tree_scrollbar_size_1",fltk_fl_tree_scrollbar_size_1);
    register_block("__Fl_Tree_is_vscroll_visible",fltk_fl_tree_is_vscroll_visible);
    register_block("__Fl_Tree_is_hscroll_visible",fltk_fl_tree_is_hscroll_visible);
    register_block("__Fl_Tree_callback_item",fltk_fl_tree_callback_item);
    register_block("__Fl_Tree_callback_item_1",fltk_fl_tree_callback_item_1);
    register_block("__Fl_Tree_callback_reason",fltk_fl_tree_callback_reason);
    register_block("__Fl_Tree_callback_reason_1",fltk_fl_tree_callback_reason_1);
    register_block("__Fl_Tree_load",fltk_fl_tree_load);
    /* Fl_Tree_Item */
    register_block("__Fl_Tree_Item_2",fltk_fl_tree_item_Fl_Tree_Item_2);
    register_block("__Fl_Tree_Item_x",fltk_fl_tree_item_x);
    register_block("__Fl_Tree_Item_y",fltk_fl_tree_item_y);
    register_block("__Fl_Tree_Item_w",fltk_fl_tree_item_w);
    register_block("__Fl_Tree_Item_h",fltk_fl_tree_item_h);
    register_block("__Fl_Tree_Item_label_x",fltk_fl_tree_item_label_x);
    register_block("__Fl_Tree_Item_label_y",fltk_fl_tree_item_label_y);
    register_block("__Fl_Tree_Item_label_w",fltk_fl_tree_item_label_w);
    register_block("__Fl_Tree_Item_label_h",fltk_fl_tree_item_label_h);
#if FLTK_ABI_VERSION >= 10303
    register_block("__Fl_Tree_Item_draw_item_content",fltk_fl_tree_item_draw_item_content);
	register_block("__Fl_Tree_Item_draw",fltk_fl_tree_item_draw);
#endif
    register_block("__Fl_Tree_Item_label",fltk_fl_tree_item_label);
    register_block("__Fl_Tree_Item_label_1",fltk_fl_tree_item_label_1);
    register_block("__Fl_Tree_Item_user_data",fltk_fl_tree_item_user_data);
    register_block("__Fl_Tree_Item_user_data_1",fltk_fl_tree_item_user_data_1);
    register_block("__Fl_Tree_Item_labelfont",fltk_fl_tree_item_labelfont);
    register_block("__Fl_Tree_Item_labelfont_1",fltk_fl_tree_item_labelfont_1);
    register_block("__Fl_Tree_Item_labelsize",fltk_fl_tree_item_labelsize);
    register_block("__Fl_Tree_Item_labelsize_1",fltk_fl_tree_item_labelsize_1);
    register_block("__Fl_Tree_Item_labelfgcolor",fltk_fl_tree_item_labelfgcolor);
    register_block("__Fl_Tree_Item_labelfgcolor_1",fltk_fl_tree_item_labelfgcolor_1);
    register_block("__Fl_Tree_Item_labelcolor",fltk_fl_tree_item_labelcolor);
    register_block("__Fl_Tree_Item_labelcolor_1",fltk_fl_tree_item_labelcolor_1);
    register_block("__Fl_Tree_Item_labelbgcolor",fltk_fl_tree_item_labelbgcolor);
    register_block("__Fl_Tree_Item_labelbgcolor_1",fltk_fl_tree_item_labelbgcolor_1);
    register_block("__Fl_Tree_Item_widget_1",fltk_fl_tree_item_widget_1);
    register_block("__Fl_Tree_Item_widget_2",fltk_fl_tree_item_widget_2);
    register_block("__Fl_Tree_Item_children_1",fltk_fl_tree_item_children_1);
    register_block("__Fl_Tree_Item_child",fltk_fl_tree_item_child);
    register_block("__Fl_Tree_Item_child_1",fltk_fl_tree_item_child_1);
    register_block("__Fl_Tree_Item_has_children",fltk_fl_tree_item_has_children);
    register_block("__Fl_Tree_Item_find_child",fltk_fl_tree_item_find_child);
    register_block("__Fl_Tree_Item_find_child_1",fltk_fl_tree_item_find_child_1);
    register_block("__Fl_Tree_Item_remove_child",fltk_fl_tree_item_remove_child);
    register_block("__Fl_Tree_Item_remove_child_1",fltk_fl_tree_item_remove_child_1);
    register_block("__Fl_Tree_Item_clear_children",fltk_fl_tree_item_clear_children);
    register_block("__Fl_Tree_Item_swap_children",fltk_fl_tree_item_swap_children);
    register_block("__Fl_Tree_Item_swap_children_1",fltk_fl_tree_item_swap_children_1);
    register_block("__Fl_Tree_Item_find_child_item",fltk_fl_tree_item_find_child_item);
    register_block("__Fl_Tree_Item_find_child_item_1",fltk_fl_tree_item_find_child_item_1);
    register_block("__Fl_Tree_Item_find_child_item_2",fltk_fl_tree_item_find_child_item_2);
    register_block("__Fl_Tree_Item_find_child_item_3",fltk_fl_tree_item_find_child_item_3);
    register_block("__Fl_Tree_Item_find_item",fltk_fl_tree_item_find_item);
    register_block("__Fl_Tree_Item_find_item_1",fltk_fl_tree_item_find_item_1);
    register_block("__Fl_Tree_Item_add",fltk_fl_tree_item_add);
    register_block("__Fl_Tree_Item_add_1",fltk_fl_tree_item_add_1);
    register_block("__Fl_Tree_Item_add_2",fltk_fl_tree_item_add_2);
    register_block("__Fl_Tree_Item_add_3",fltk_fl_tree_item_add_3);
#if FLTK_ABI_VERSION >= 10303
    register_block("__Fl_Tree_Item_replace",fltk_fl_tree_item_replace);
	register_block("__Fl_Tree_Item_replace_child",fltk_fl_tree_item_replace_child);
#endif
    register_block("__Fl_Tree_Item_insert",fltk_fl_tree_item_insert);
    register_block("__Fl_Tree_Item_insert_above",fltk_fl_tree_item_insert_above);
    register_block("__Fl_Tree_Item_deparent",fltk_fl_tree_item_deparent);
    register_block("__Fl_Tree_Item_reparent",fltk_fl_tree_item_reparent);
    register_block("__Fl_Tree_Item_move",fltk_fl_tree_item_move);
    register_block("__Fl_Tree_Item_move_1",fltk_fl_tree_item_move_1);
    register_block("__Fl_Tree_Item_move_above",fltk_fl_tree_item_move_above);
    register_block("__Fl_Tree_Item_move_below",fltk_fl_tree_item_move_below);
    register_block("__Fl_Tree_Item_move_into",fltk_fl_tree_item_move_into);
    register_block("__Fl_Tree_Item_depth",fltk_fl_tree_item_depth);
    register_block("__Fl_Tree_Item_prev",fltk_fl_tree_item_prev);
    register_block("__Fl_Tree_Item_next",fltk_fl_tree_item_next);
    register_block("__Fl_Tree_Item_next_sibling",fltk_fl_tree_item_next_sibling);
    register_block("__Fl_Tree_Item_prev_sibling",fltk_fl_tree_item_prev_sibling);
    register_block("__Fl_Tree_Item_update_prev_next",fltk_fl_tree_item_update_prev_next);
    register_block("__Fl_Tree_Item_next_displayed",fltk_fl_tree_item_next_displayed);
    register_block("__Fl_Tree_Item_prev_displayed",fltk_fl_tree_item_prev_displayed);
    register_block("__Fl_Tree_Item_next_visible",fltk_fl_tree_item_next_visible);
    register_block("__Fl_Tree_Item_prev_visible",fltk_fl_tree_item_prev_visible);
    register_block("__Fl_Tree_Item_parent",fltk_fl_tree_item_parent);
    register_block("__Fl_Tree_Item_parent_1",fltk_fl_tree_item_parent_1);
    register_block("__Fl_Tree_Item_parent_2",fltk_fl_tree_item_parent_2);
#if FLTK_ABI_VERSION >= 10304
    register_block("__Fl_Tree_Item_tree_1",fltk_fl_tree_item_tree_1);
#endif
    register_block("__Fl_Tree_Item_open",fltk_fl_tree_item_open);
    register_block("__Fl_Tree_Item_close",fltk_fl_tree_item_close);
    register_block("__Fl_Tree_Item_is_open",fltk_fl_tree_item_is_open);
    register_block("__Fl_Tree_Item_is_close",fltk_fl_tree_item_is_close);
    register_block("__Fl_Tree_Item_open_toggle",fltk_fl_tree_item_open_toggle);
    register_block("__Fl_Tree_Item_select",fltk_fl_tree_item_select);
    register_block("__Fl_Tree_Item_select_toggle",fltk_fl_tree_item_select_toggle);
    register_block("__Fl_Tree_Item_select_all",fltk_fl_tree_item_select_all);
    register_block("__Fl_Tree_Item_deselect",fltk_fl_tree_item_deselect);
    register_block("__Fl_Tree_Item_deselect_all",fltk_fl_tree_item_deselect_all);
    register_block("__Fl_Tree_Item_is_selected",fltk_fl_tree_item_is_selected);
    register_block("__Fl_Tree_Item_activate",fltk_fl_tree_item_activate);
    register_block("__Fl_Tree_Item_deactivate",fltk_fl_tree_item_deactivate);
    register_block("__Fl_Tree_Item_is_activated",fltk_fl_tree_item_is_activated);
    register_block("__Fl_Tree_Item_is_active",fltk_fl_tree_item_is_active);
    register_block("__Fl_Tree_Item_visible",fltk_fl_tree_item_visible);
    register_block("__Fl_Tree_Item_is_visible",fltk_fl_tree_item_is_visible);
    register_block("__Fl_Tree_Item_visible_r",fltk_fl_tree_item_visible_r);
    register_block("__Fl_Tree_Item_usericon",fltk_fl_tree_item_usericon);
    register_block("__Fl_Tree_Item_usericon_1",fltk_fl_tree_item_usericon_1);
    register_block("__Fl_Tree_Item_Array",fltk_fl_tree_item_array_Fl_Tree_Item_Array);
    register_block("__Fl_Tree_Item_Array_1",fltk_fl_tree_item_array_Fl_Tree_Item_Array_1);
    register_block("__Fl_Tree_Item_Array_total",fltk_fl_tree_item_array_total);
    register_block("__Fl_Tree_Item_Array_swap",fltk_fl_tree_item_array_swap);
    register_block("__Fl_Tree_Item_Array_swap_1",fltk_fl_tree_item_array_swap_1);
    register_block("__Fl_Tree_Item_Array_move_2",fltk_fl_tree_item_array_move_2);
    register_block("__Fl_Tree_Item_Array_deparent_1",fltk_fl_tree_item_array_deparent_1);
    register_block("__Fl_Tree_Item_Array_reparent_1",fltk_fl_tree_item_array_reparent_1);
    register_block("__Fl_Tree_Item_Array_clear",fltk_fl_tree_item_array_clear);
    register_block("__Fl_Tree_Item_Array_add_4",fltk_fl_tree_item_array_add_4);
    register_block("__Fl_Tree_Item_Array_insert_1",fltk_fl_tree_item_array_insert_1);
    register_block("__Fl_Tree_Item_Array_replace_1",fltk_fl_tree_item_array_replace_1);
    register_block("__Fl_Tree_Item_Array_remove",fltk_fl_tree_item_array_remove);
    register_block("__Fl_Tree_Item_Array_remove_1",fltk_fl_tree_item_array_remove_1);
#if FLTK_ABI_VERSION >= 10303
    register_block("__Fl_Tree_Item_Array_manage_item_destroy",fltk_fl_tree_item_array_manage_item_destroy);
	register_block("__Fl_Tree_Item_Array_manage_item_destroy_1",fltk_fl_tree_item_array_manage_item_destroy_1);
#endif
    register_block("__FL_TREE_SORT_NONE",fltk_FL_TREE_SORT_NONE);
    register_block("__FL_TREE_SORT_ASCENDING",fltk_FL_TREE_SORT_ASCENDING);
    register_block("__FL_TREE_SORT_DESCENDING",fltk_FL_TREE_SORT_DESCENDING);
    register_block("__FL_TREE_CONNECTOR_NONE",fltk_FL_TREE_CONNECTOR_NONE);
    register_block("__FL_TREE_CONNECTOR_DOTTED",fltk_FL_TREE_CONNECTOR_DOTTED);
    register_block("__FL_TREE_CONNECTOR_SOLID",fltk_FL_TREE_CONNECTOR_SOLID);
    register_block("__FL_TREE_SELECT_NONE",fltk_FL_TREE_SELECT_NONE);
    register_block("__FL_TREE_SELECT_SINGLE",fltk_FL_TREE_SELECT_SINGLE);
    register_block("__FL_TREE_SELECT_MULTI",fltk_FL_TREE_SELECT_MULTI);
    register_block("__FL_TREE_SELECT_SINGLE_DRAGGABLE",fltk_FL_TREE_SELECT_SINGLE_DRAGGABLE);
    /* Fl_Tree_Prefs */
    register_block("__Fl_Tree_Prefs",fltk_fl_tree_prefs_Fl_Tree_Prefs);
    register_block("__Fl_Tree_Prefs_item_labelfont",fltk_fl_tree_prefs_item_labelfont);
    register_block("__Fl_Tree_Prefs_item_labelfont_1",fltk_fl_tree_prefs_item_labelfont_1);
    register_block("__Fl_Tree_Prefs_item_labelsize",fltk_fl_tree_prefs_item_labelsize);
    register_block("__Fl_Tree_Prefs_item_labelsize_1",fltk_fl_tree_prefs_item_labelsize_1);
    register_block("__Fl_Tree_Prefs_item_labelfgcolor",fltk_fl_tree_prefs_item_labelfgcolor);
    register_block("__Fl_Tree_Prefs_item_labelfgcolor_1",fltk_fl_tree_prefs_item_labelfgcolor_1);
    register_block("__Fl_Tree_Prefs_item_labelbgcolor",fltk_fl_tree_prefs_item_labelbgcolor);
    register_block("__Fl_Tree_Prefs_item_labelbgcolor_1",fltk_fl_tree_prefs_item_labelbgcolor_1);
    register_block("__Fl_Tree_Prefs_item_labelbgcolor_2",fltk_fl_tree_prefs_item_labelbgcolor_2);
    register_block("__Fl_Tree_Prefs_item_labelbgcolor_3",fltk_fl_tree_prefs_item_labelbgcolor_3);
    register_block("__Fl_Tree_Prefs_labelfont_2",fltk_fl_tree_prefs_labelfont_2);
    register_block("__Fl_Tree_Prefs_labelfont_3",fltk_fl_tree_prefs_labelfont_3);
    register_block("__Fl_Tree_Prefs_labelsize_2",fltk_fl_tree_prefs_labelsize_2);
    register_block("__Fl_Tree_Prefs_labelsize_3",fltk_fl_tree_prefs_labelsize_3);
    register_block("__Fl_Tree_Prefs_labelfgcolor_2",fltk_fl_tree_prefs_labelfgcolor_2);
    register_block("__Fl_Tree_Prefs_labelfgcolor_3",fltk_fl_tree_prefs_labelfgcolor_3);
    register_block("__Fl_Tree_Prefs_labelbgcolor_2",fltk_fl_tree_prefs_labelbgcolor_2);
    register_block("__Fl_Tree_Prefs_labelbgcolor_3",fltk_fl_tree_prefs_labelbgcolor_3);
    register_block("__Fl_Tree_Prefs_marginleft",fltk_fl_tree_prefs_marginleft);
    register_block("__Fl_Tree_Prefs_marginleft_1",fltk_fl_tree_prefs_marginleft_1);
    register_block("__Fl_Tree_Prefs_margintop",fltk_fl_tree_prefs_margintop);
    register_block("__Fl_Tree_Prefs_margintop_1",fltk_fl_tree_prefs_margintop_1);
#if FLTK_ABI_VERSION >= 10301
    register_block("__Fl_Tree_Prefs_marginbottom",fltk_fl_tree_prefs_marginbottom);
	register_block("__Fl_Tree_Prefs_marginbottom_1",fltk_fl_tree_prefs_marginbottom_1);
#endif
    register_block("__Fl_Tree_Prefs_openchild_marginbottom",fltk_fl_tree_prefs_openchild_marginbottom);
    register_block("__Fl_Tree_Prefs_openchild_marginbottom_1",fltk_fl_tree_prefs_openchild_marginbottom_1);
    register_block("__Fl_Tree_Prefs_usericonmarginleft",fltk_fl_tree_prefs_usericonmarginleft);
    register_block("__Fl_Tree_Prefs_usericonmarginleft_1",fltk_fl_tree_prefs_usericonmarginleft_1);
    register_block("__Fl_Tree_Prefs_labelmarginleft",fltk_fl_tree_prefs_labelmarginleft);
    register_block("__Fl_Tree_Prefs_labelmarginleft_1",fltk_fl_tree_prefs_labelmarginleft_1);
#if FLTK_ABI_VERSION >= 10301
    register_block("__Fl_Tree_Prefs_widgetmarginleft",fltk_fl_tree_prefs_widgetmarginleft);
	register_block("__Fl_Tree_Prefs_widgetmarginleft_1",fltk_fl_tree_prefs_widgetmarginleft_1);
#endif
    register_block("__Fl_Tree_Prefs_linespacing",fltk_fl_tree_prefs_linespacing);
    register_block("__Fl_Tree_Prefs_linespacing_1",fltk_fl_tree_prefs_linespacing_1);
    register_block("__Fl_Tree_Prefs_connectorcolor",fltk_fl_tree_prefs_connectorcolor);
    register_block("__Fl_Tree_Prefs_connectorcolor_1",fltk_fl_tree_prefs_connectorcolor_1);
    register_block("__Fl_Tree_Prefs_connectorstyle",fltk_fl_tree_prefs_connectorstyle);
    register_block("__Fl_Tree_Prefs_connectorstyle_1",fltk_fl_tree_prefs_connectorstyle_1);
    register_block("__Fl_Tree_Prefs_connectorstyle_2",fltk_fl_tree_prefs_connectorstyle_2);
    register_block("__Fl_Tree_Prefs_connectorwidth",fltk_fl_tree_prefs_connectorwidth);
    register_block("__Fl_Tree_Prefs_connectorwidth_1",fltk_fl_tree_prefs_connectorwidth_1);
    register_block("__Fl_Tree_Prefs_openicon",fltk_fl_tree_prefs_openicon);
    register_block("__Fl_Tree_Prefs_openicon_1",fltk_fl_tree_prefs_openicon_1);
    register_block("__Fl_Tree_Prefs_closeicon",fltk_fl_tree_prefs_closeicon);
    register_block("__Fl_Tree_Prefs_closeicon_1",fltk_fl_tree_prefs_closeicon_1);
    register_block("__Fl_Tree_Prefs_usericon_2",fltk_fl_tree_prefs_usericon_2);
    register_block("__Fl_Tree_Prefs_usericon_3",fltk_fl_tree_prefs_usericon_3);
#if FLTK_ABI_VERSION >= 10304
    register_block("__Fl_Tree_Prefs_opendeicon",fltk_fl_tree_prefs_opendeicon);
	register_block("__Fl_Tree_Prefs_closedeicon",fltk_fl_tree_prefs_closedeicon);
	register_block("__Fl_Tree_Prefs_userdeicon",fltk_fl_tree_prefs_userdeicon);
#endif
    register_block("__Fl_Tree_Prefs_showcollapse",fltk_fl_tree_prefs_showcollapse);
    register_block("__Fl_Tree_Prefs_showcollapse_1",fltk_fl_tree_prefs_showcollapse_1);
    register_block("__Fl_Tree_Prefs_sortorder",fltk_fl_tree_prefs_sortorder);
    register_block("__Fl_Tree_Prefs_sortorder_1",fltk_fl_tree_prefs_sortorder_1);
    register_block("__Fl_Tree_Prefs_selectbox",fltk_fl_tree_prefs_selectbox);
    register_block("__Fl_Tree_Prefs_selectbox_1",fltk_fl_tree_prefs_selectbox_1);
    register_block("__Fl_Tree_Prefs_showroot",fltk_fl_tree_prefs_showroot);
    register_block("__Fl_Tree_Prefs_showroot_1",fltk_fl_tree_prefs_showroot_1);
    register_block("__Fl_Tree_Prefs_selectmode",fltk_fl_tree_prefs_selectmode);
    register_block("__Fl_Tree_Prefs_selectmode_1",fltk_fl_tree_prefs_selectmode_1);
#if FLTK_ABI_VERSION >= 10301
    register_block("__Fl_Tree_Prefs_item_reselect_mode",fltk_fl_tree_prefs_item_reselect_mode);
	register_block("__Fl_Tree_Prefs_item_reselect_mode_1",fltk_fl_tree_prefs_item_reselect_mode_1);
	register_block("__Fl_Tree_Prefs_item_draw_mode",fltk_fl_tree_prefs_item_draw_mode);
	register_block("__Fl_Tree_Prefs_item_draw_mode_1",fltk_fl_tree_prefs_item_draw_mode_1);
#endif
#if FLTK_ABI_VERSION >= 10303
    register_block("__Fl_Tree_Prefs_item_draw_callback",fltk_fl_tree_prefs_item_draw_callback);
	register_block("__Fl_Tree_Prefs_item_draw_callback_1",fltk_fl_tree_prefs_item_draw_callback_1);
	register_block("__Fl_Tree_Prefs_item_draw_user_data",fltk_fl_tree_prefs_item_draw_user_data);
	register_block("__Fl_Tree_Prefs_do_item_draw_callback",fltk_fl_tree_prefs_do_item_draw_callback);
#endif
    /* Fl_Valuator */
    register_block("__Fl_Valuator_bounds",fltk_fl_valuator_bounds);
    register_block("__Fl_Valuator_minimum",fltk_fl_valuator_minimum);
    register_block("__Fl_Valuator_minimum_1",fltk_fl_valuator_minimum_1);
    register_block("__Fl_Valuator_maximum",fltk_fl_valuator_maximum);
    register_block("__Fl_Valuator_maximum_1",fltk_fl_valuator_maximum_1);
    register_block("__Fl_Valuator_range",fltk_fl_valuator_range);
    register_block("__Fl_Valuator_step",fltk_fl_valuator_step);
    register_block("__Fl_Valuator_step_1",fltk_fl_valuator_step_1);
    register_block("__Fl_Valuator_step_2",fltk_fl_valuator_step_2);
    register_block("__Fl_Valuator_step_3",fltk_fl_valuator_step_3);
    register_block("__Fl_Valuator_precision",fltk_fl_valuator_precision);
    register_block("__Fl_Valuator_value",fltk_fl_valuator_value);
    register_block("__Fl_Valuator_value_1",fltk_fl_valuator_value_1);
    register_block("__Fl_Valuator_format",fltk_fl_valuator_format);
    register_block("__Fl_Valuator_round",fltk_fl_valuator_round);
    register_block("__Fl_Valuator_clamp",fltk_fl_valuator_clamp);
    register_block("__Fl_Valuator_increment",fltk_fl_valuator_increment);
    /* Fl_Value_Input */
    register_block("__Fl_Value_Input_handle",fltk_fl_value_input_handle);
    register_block("__Fl_Value_Input_resize",fltk_fl_value_input_resize);
    register_block("__Fl_Value_Input",fltk_fl_value_input_Fl_Value_Input);
    register_block("__Fl_Value_Input_soft",fltk_fl_value_input_soft);
    register_block("__Fl_Value_Input_soft_1",fltk_fl_value_input_soft_1);
    register_block("__Fl_Value_Input_shortcut",fltk_fl_value_input_shortcut);
    register_block("__Fl_Value_Input_shortcut_1",fltk_fl_value_input_shortcut_1);
    register_block("__Fl_Value_Input_textfont",fltk_fl_value_input_textfont);
    register_block("__Fl_Value_Input_textfont_1",fltk_fl_value_input_textfont_1);
    register_block("__Fl_Value_Input_textsize",fltk_fl_value_input_textsize);
    register_block("__Fl_Value_Input_textsize_1",fltk_fl_value_input_textsize_1);
    register_block("__Fl_Value_Input_textcolor",fltk_fl_value_input_textcolor);
    register_block("__Fl_Value_Input_textcolor_1",fltk_fl_value_input_textcolor_1);
    register_block("__Fl_Value_Input_cursor_color",fltk_fl_value_input_cursor_color);
    register_block("__Fl_Value_Input_cursor_color_1",fltk_fl_value_input_cursor_color_1);
    register_block("__Fl_Value_Output_handle_1",fltk_fl_value_output_handle_1);
    /* Fl_Value_Output */
    register_block("__Fl_Value_Output",fltk_fl_value_output_Fl_Value_Output);
    register_block("__Fl_Value_Output_soft_2",fltk_fl_value_output_soft_2);
    register_block("__Fl_Value_Output_soft_3",fltk_fl_value_output_soft_3);
    register_block("__Fl_Value_Output_textfont_2",fltk_fl_value_output_textfont_2);
    register_block("__Fl_Value_Output_textfont_3",fltk_fl_value_output_textfont_3);
    register_block("__Fl_Value_Output_textsize_2",fltk_fl_value_output_textsize_2);
    register_block("__Fl_Value_Output_textsize_3",fltk_fl_value_output_textsize_3);
    register_block("__Fl_Value_Output_textcolor_2",fltk_fl_value_output_textcolor_2);
    register_block("__Fl_Value_Output_textcolor_3",fltk_fl_value_output_textcolor_3);
    /* Fl_Value_Slider */
    register_block("__Fl_Value_Slider_handle_2",fltk_fl_value_slider_handle_2);
    register_block("__Fl_Value_Slider",fltk_fl_value_slider_Fl_Value_Slider);
    register_block("__Fl_Value_Slider_textfont_4",fltk_fl_value_slider_textfont_4);
    register_block("__Fl_Value_Slider_textfont_5",fltk_fl_value_slider_textfont_5);
    register_block("__Fl_Value_Slider_textsize_4",fltk_fl_value_slider_textsize_4);
    register_block("__Fl_Value_Slider_textsize_5",fltk_fl_value_slider_textsize_5);
    register_block("__Fl_Value_Slider_textcolor_4",fltk_fl_value_slider_textcolor_4);
    register_block("__Fl_Value_Slider_textcolor_5",fltk_fl_value_slider_textcolor_5);
    /* Fl_Widget */
    register_block("__Fl_Widget_handle",fltk_fl_widget_handle);
    register_block("__Fl_Widget_is_label_copied",fltk_fl_widget_is_label_copied);
    register_block("__Fl_Widget_parent",fltk_fl_widget_parent);
    register_block("__Fl_Widget_parent_1",fltk_fl_widget_parent_1);
    register_block("__Fl_Widget_type",fltk_fl_widget_type);
    register_block("__Fl_Widget_type_1",fltk_fl_widget_type_1);
    register_block("__Fl_Widget_x",fltk_fl_widget_x);
    register_block("__Fl_Widget_y",fltk_fl_widget_y);
    register_block("__Fl_Widget_w",fltk_fl_widget_w);
    register_block("__Fl_Widget_h",fltk_fl_widget_h);
    register_block("__Fl_Widget_resize",fltk_fl_widget_resize);
    register_block("__Fl_Widget_damage_resize",fltk_fl_widget_damage_resize);
    register_block("__Fl_Widget_position",fltk_fl_widget_position);
    register_block("__Fl_Widget_size",fltk_fl_widget_size);
    register_block("__Fl_Widget_align",fltk_fl_widget_align);
    register_block("__Fl_Widget_align_1",fltk_fl_widget_align_1);
    register_block("__Fl_Widget_box",fltk_fl_widget_box);
    register_block("__Fl_Widget_box_1",fltk_fl_widget_box_1);
    register_block("__Fl_Widget_color",fltk_fl_widget_color);
    register_block("__Fl_Widget_color_1",fltk_fl_widget_color_1);
    register_block("__Fl_Widget_selection_color",fltk_fl_widget_selection_color);
    register_block("__Fl_Widget_selection_color_1",fltk_fl_widget_selection_color_1);
    register_block("__Fl_Widget_color_2",fltk_fl_widget_color_2);
    register_block("__Fl_Widget_label",fltk_fl_widget_label);
    register_block("__Fl_Widget_label_1",fltk_fl_widget_label_1);
    register_block("__Fl_Widget_copy_label",fltk_fl_widget_copy_label);
    register_block("__Fl_Widget_label_2",fltk_fl_widget_label_2);
    register_block("__Fl_Widget_labeltype",fltk_fl_widget_labeltype);
    register_block("__Fl_Widget_labeltype_1",fltk_fl_widget_labeltype_1);
    register_block("__Fl_Widget_labelcolor",fltk_fl_widget_labelcolor);
    register_block("__Fl_Widget_labelcolor_1",fltk_fl_widget_labelcolor_1);
    register_block("__Fl_Widget_labelfont",fltk_fl_widget_labelfont);
    register_block("__Fl_Widget_labelfont_1",fltk_fl_widget_labelfont_1);
    register_block("__Fl_Widget_labelsize",fltk_fl_widget_labelsize);
    register_block("__Fl_Widget_labelsize_1",fltk_fl_widget_labelsize_1);
    register_block("__Fl_Widget_image",fltk_fl_widget_image);
    register_block("__Fl_Widget_image_1",fltk_fl_widget_image_1);
    register_block("__Fl_Widget_image_2",fltk_fl_widget_image_2);
    register_block("__Fl_Widget_image_3",fltk_fl_widget_image_3);
    register_block("__Fl_Widget_deimage",fltk_fl_widget_deimage);
    register_block("__Fl_Widget_deimage_1",fltk_fl_widget_deimage_1);
    register_block("__Fl_Widget_deimage_2",fltk_fl_widget_deimage_2);
    register_block("__Fl_Widget_deimage_3",fltk_fl_widget_deimage_3);
    register_block("__Fl_Widget_tooltip",fltk_fl_widget_tooltip);
    register_block("__Fl_Widget_tooltip_1",fltk_fl_widget_tooltip_1);
    register_block("__Fl_Widget_copy_tooltip",fltk_fl_widget_copy_tooltip);
    register_block("__Fl_Widget_callback_on_onlick",fltk_fl_widget_callback_on_onlick);
    register_block("__Fl_Widget_callback",fltk_fl_widget_callback);
    register_block("__Fl_Widget_callback_1",fltk_fl_widget_callback_1);
    register_block("__Fl_Widget_callback_2",fltk_fl_widget_callback_2);
    register_block("__Fl_Widget_callback_3",fltk_fl_widget_callback_3);
    register_block("__Fl_Widget_callback_4",fltk_fl_widget_callback_4);
    register_block("__Fl_Widget_user_data",fltk_fl_widget_user_data);
    register_block("__Fl_Widget_user_data_1",fltk_fl_widget_user_data_1);
    register_block("__Fl_Widget_argument",fltk_fl_widget_argument);
    register_block("__Fl_Widget_argument_1",fltk_fl_widget_argument_1);
    register_block("__Fl_Widget_when",fltk_fl_widget_when);
    register_block("__Fl_Widget_when_1",fltk_fl_widget_when_1);
    register_block("__Fl_Widget_visible",fltk_fl_widget_visible);
    register_block("__Fl_Widget_visible_r",fltk_fl_widget_visible_r);
    register_block("__Fl_Widget_show",fltk_fl_widget_show);
    register_block("__Fl_Widget_hide",fltk_fl_widget_hide);
    register_block("__Fl_Widget_set_visible",fltk_fl_widget_set_visible);
    register_block("__Fl_Widget_clear_visible",fltk_fl_widget_clear_visible);
    register_block("__Fl_Widget_active",fltk_fl_widget_active);
    register_block("__Fl_Widget_active_r",fltk_fl_widget_active_r);
    register_block("__Fl_Widget_activate",fltk_fl_widget_activate);
    register_block("__Fl_Widget_deactivate",fltk_fl_widget_deactivate);
    register_block("__Fl_Widget_output",fltk_fl_widget_output);
    register_block("__Fl_Widget_set_output",fltk_fl_widget_set_output);
    register_block("__Fl_Widget_clear_output",fltk_fl_widget_clear_output);
    register_block("__Fl_Widget_takesevents",fltk_fl_widget_takesevents);
    register_block("__Fl_Widget_changed",fltk_fl_widget_changed);
    register_block("__Fl_Widget_set_changed",fltk_fl_widget_set_changed);
    register_block("__Fl_Widget_clear_changed",fltk_fl_widget_clear_changed);
    register_block("__Fl_Widget_clear_active",fltk_fl_widget_clear_active);
    register_block("__Fl_Widget_set_active",fltk_fl_widget_set_active);
    register_block("__Fl_Widget_take_focus",fltk_fl_widget_take_focus);
    register_block("__Fl_Widget_set_visible_focus",fltk_fl_widget_set_visible_focus);
    register_block("__Fl_Widget_clear_visible_focus",fltk_fl_widget_clear_visible_focus);
    register_block("__Fl_Widget_visible_focus",fltk_fl_widget_visible_focus);
    register_block("__Fl_Widget_visible_focus_1",fltk_fl_widget_visible_focus_1);
    register_block("__Fl_Widget_Fl_Widget_default_callback",fltk_fl_widget_Fl_Widget_default_callback);
    register_block("__Fl_Widget_do_callback",fltk_fl_widget_do_callback);
    register_block("__Fl_Widget_do_callback_1",fltk_fl_widget_do_callback_1);
    register_block("__Fl_Widget_test_shortcut",fltk_fl_widget_test_shortcut);
    register_block("__Fl_Widget_Fl_Widget_label_shortcut",fltk_fl_widget_Fl_Widget_label_shortcut);
    register_block("__Fl_Widget_Fl_Widget_test_shortcut",fltk_fl_widget_Fl_Widget_test_shortcut);
    register_block("__Fl_Widget__set_fullscreen",fltk_fl_widget__set_fullscreen);
    register_block("__Fl_Widget__clear_fullscreen",fltk_fl_widget__clear_fullscreen);
    register_block("__Fl_Widget_contains",fltk_fl_widget_contains);
    register_block("__Fl_Widget_inside",fltk_fl_widget_inside);
    register_block("__Fl_Widget_redraw",fltk_fl_widget_redraw);
    register_block("__Fl_Widget_redraw_label",fltk_fl_widget_redraw_label);
    register_block("__Fl_Widget_damage",fltk_fl_widget_damage);
    register_block("__Fl_Widget_clear_damage",fltk_fl_widget_clear_damage);
    register_block("__Fl_Widget_damage_1",fltk_fl_widget_damage_1);
    register_block("__Fl_Widget_damage_2",fltk_fl_widget_damage_2);
    register_block("__Fl_Widget_draw_label",fltk_fl_widget_draw_label);
    register_block("__Fl_Widget_measure_label",fltk_fl_widget_measure_label);
    register_block("__Fl_Widget_window",fltk_fl_widget_window);
    register_block("__Fl_Widget_top_window",fltk_fl_widget_top_window);
    register_block("__Fl_Widget_top_window_offset",fltk_fl_widget_top_window_offset);
    register_block("__Fl_Widget_as_group",fltk_fl_widget_as_group);
    register_block("__Fl_Widget_as_window",fltk_fl_widget_as_window);
    register_block("__Fl_Widget_as_gl_window",fltk_fl_widget_as_gl_window);
    register_block("__Fl_Widget_use_accents_menu",fltk_fl_widget_use_accents_menu);
    register_block("__Fl_Widget_color2",fltk_fl_widget_color2);
    register_block("__Fl_Widget_color2_1",fltk_fl_widget_color2_1);
    /* Fl_Window */
    register_block("__Fl_Window_shape",fltk_fl_window_shape);
    register_block("__Fl_Window_shape_1",fltk_fl_window_shape_1);
    register_block("__Fl_Window",fltk_fl_window_Fl_Window);
    register_block("__Fl_Window_1",fltk_fl_window_Fl_Window_1);
    register_block("__Fl_Window_handle",fltk_fl_window_handle);
    register_block("__Fl_Window_resize",fltk_fl_window_resize);
    register_block("__Fl_Window_border",fltk_fl_window_border);
    register_block("__Fl_Window_clear_border",fltk_fl_window_clear_border);
    register_block("__Fl_Window_border_1",fltk_fl_window_border_1);
    register_block("__Fl_Window_set_override",fltk_fl_window_set_override);
    register_block("__Fl_Window_override",fltk_fl_window_override);
    register_block("__Fl_Window_set_modal",fltk_fl_window_set_modal);
    register_block("__Fl_Window_modal",fltk_fl_window_modal);
    register_block("__Fl_Window_set_non_modal",fltk_fl_window_set_non_modal);
    register_block("__Fl_Window_non_modal",fltk_fl_window_non_modal);
    register_block("__Fl_Window_clear_modal_states",fltk_fl_window_clear_modal_states);
    register_block("__Fl_Window_set_menu_window",fltk_fl_window_set_menu_window);
    register_block("__Fl_Window_menu_window",fltk_fl_window_menu_window);
    register_block("__Fl_Window_set_tooltip_window",fltk_fl_window_set_tooltip_window);
    register_block("__Fl_Window_tooltip_window",fltk_fl_window_tooltip_window);
    register_block("__Fl_Window_hotspot",fltk_fl_window_hotspot);
    register_block("__Fl_Window_hotspot_1",fltk_fl_window_hotspot_1);
    register_block("__Fl_Window_hotspot_2",fltk_fl_window_hotspot_2);
    register_block("__Fl_Window_free_position",fltk_fl_window_free_position);
    register_block("__Fl_Window_size_range",fltk_fl_window_size_range);
    register_block("__Fl_Window_label",fltk_fl_window_label);
    register_block("__Fl_Window_iconlabel",fltk_fl_window_iconlabel);
    register_block("__Fl_Window_label_1",fltk_fl_window_label_1);
    register_block("__Fl_Window_iconlabel_1",fltk_fl_window_iconlabel_1);
    register_block("__Fl_Window_label_2",fltk_fl_window_label_2);
    register_block("__Fl_Window_copy_label",fltk_fl_window_copy_label);
    register_block("__Fl_Window_Fl_Window_default_xclass",fltk_fl_window_Fl_Window_default_xclass);
    register_block("__Fl_Window_Fl_Window_default_xclass_1",fltk_fl_window_Fl_Window_default_xclass_1);
    register_block("__Fl_Window_xclass",fltk_fl_window_xclass);
    register_block("__Fl_Window_xclass_1",fltk_fl_window_xclass_1);
    register_block("__Fl_Window_Fl_Window_default_icon",fltk_fl_window_Fl_Window_default_icon);
    register_block("__Fl_Window_Fl_Window_default_icons",fltk_fl_window_Fl_Window_default_icons);
    register_block("__Fl_Window_icon",fltk_fl_window_icon);
    register_block("__Fl_Window_icons",fltk_fl_window_icons);
#ifdef _WIN32
    register_block("__Fl_Window_Fl_Window_default_icons_1",fltk_fl_window_Fl_Window_default_icons_1);
	register_block("__Fl_Window_icons_1",fltk_fl_window_icons_1);
#endif
    register_block("__Fl_Window_icon_1",fltk_fl_window_icon_1);
    register_block("__Fl_Window_icon_2",fltk_fl_window_icon_2);
    register_block("__Fl_Window_shown",fltk_fl_window_shown);
    register_block("__Fl_Window_show",fltk_fl_window_show);
    register_block("__Fl_Window_hide",fltk_fl_window_hide);
    register_block("__Fl_Window_show_1",fltk_fl_window_show_1);
    register_block("__Fl_Window_wait_for_expose",fltk_fl_window_wait_for_expose);
    register_block("__Fl_Window_fullscreen",fltk_fl_window_fullscreen);
    register_block("__Fl_Window_fullscreen_off",fltk_fl_window_fullscreen_off);
    register_block("__Fl_Window_fullscreen_off_1",fltk_fl_window_fullscreen_off_1);
    register_block("__Fl_Window_fullscreen_active",fltk_fl_window_fullscreen_active);
    register_block("__Fl_Window_fullscreen_screens",fltk_fl_window_fullscreen_screens);
    register_block("__Fl_Window_iconize",fltk_fl_window_iconize);
    register_block("__Fl_Window_x_root",fltk_fl_window_x_root);
    register_block("__Fl_Window_y_root",fltk_fl_window_y_root);
    register_block("__Fl_Window_Fl_Window_current",fltk_fl_window_Fl_Window_current);
    register_block("__Fl_Window_make_current",fltk_fl_window_make_current);
    register_block("__Fl_Window_as_window",fltk_fl_window_as_window);
    register_block("__Fl_Window_cursor",fltk_fl_window_cursor);
    register_block("__Fl_Window_cursor_1",fltk_fl_window_cursor_1);
    register_block("__Fl_Window_default_cursor",fltk_fl_window_default_cursor);
    register_block("__Fl_Window_Fl_Window_default_callback",fltk_fl_window_Fl_Window_default_callback);
    register_block("__Fl_Window_decorated_w",fltk_fl_window_decorated_w);
    register_block("__Fl_Window_decorated_h",fltk_fl_window_decorated_h);
    /* Fl_Wizard */
    register_block("__Fl_Wizard",fltk_fl_wizard_Fl_Wizard);
    register_block("__Fl_Wizard_next",fltk_fl_wizard_next);
    register_block("__Fl_Wizard_prev",fltk_fl_wizard_prev);
    register_block("__Fl_Wizard_value",fltk_fl_wizard_value);
    register_block("__Fl_Wizard_value_1",fltk_fl_wizard_value_1);
    /* Fl_XBM_Image */
    register_block("__Fl_XBM_Image",fltk_fl_xbm_image_Fl_XBM_Image);
    /* Fl_XPM_Image */
    register_block("__Fl_XPM_Image",fltk_fl_xpm_image_Fl_XPM_Image);
#ifndef __ANDROID__
    register_block("__fl_initialize",fltk_fl_initialize);
#endif
    register_block("__fl_finish",fltk_fl_finish);
    register_block("__fl_add_io_callback",fltk_fl_add_io_callback);
    /* fl_math */
#ifdef USE_MATH_NAMES
    register_block("__rint",fltk_rint);
    register_block("__copysign",fltk_copysign);
#endif
    /* x.H */
#ifndef __ANDROID__
    register_block("__fl_gc",fltk_fl_gc);
#endif
    register_block("__fl_window",fltk_fl_window);
    register_block("__fl_clip_region_x",fltk_fl_clip_region_x);
    register_block("__fl_clip_region_x_1",fltk_fl_clip_region_x_1);
    register_block("__fl_copy_offscreen",fltk_fl_copy_offscreen);
    register_block("__fl_create_bitmask",fltk_fl_create_bitmask);
    register_block("__fl_create_alphamask",fltk_fl_create_alphamask);
    register_block("__fl_delete_bitmask",fltk_fl_delete_bitmask);
}


