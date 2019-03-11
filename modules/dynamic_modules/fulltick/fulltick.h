
#ifndef FULLTICK_H
#define FULLTICK_H

//#define __ANDROID__
// USE_OPENGL
#include <FL/abi-version.h>
#include <FL/filename.H>
#include <FL/fl_utf8.h>
#include <FL/fl_types.h>
#include <Fl/Enumerations.H>
#include <FL/Fl.H>
#include <FL/Fl_Adjuster.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Bitmap.H>
#include <FL/Fl_BMP_Image.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Browser.H>
#include <FL/Fl_Browser_.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Cairo.H>
#include <FL/Fl_Cairo_Window.H>
#include <FL/Fl_Chart.H>
#include <FL/Fl_Check_Browser.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Clock.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_Copy_Surface.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Device.H>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Export.H>
#include <FL/Fl_File_Browser.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_File_Icon.H>
#include <FL/Fl_File_Input.H>
#include <FL/Fl_Fill_Dial.H>
#include <FL/Fl_Fill_Slider.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_FormsBitmap.H>
#include <FL/Fl_FormsPixmap.H>
#include <FL/Fl_Free.H>
#include <FL/Fl_GIF_Image.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Help_Dialog.H>
#include <FL/Fl_Help_View.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Hor_Fill_Slider.H>
#include <FL/Fl_Hor_Nice_Slider.H>
#include <FL/Fl_Hor_Slider.H>
#include <FL/Fl_Hor_Value_Slider.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Image_Surface.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Input_.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Line_Dial.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Menu_.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Window.H>
#include <FL/fl_message.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/Fl_Multi_Browser.H>
#include <FL/Fl_Multi_Label.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Nice_Slider.H>
#include <FL/Fl_Object.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Overlay_Window.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Paged_Device.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Plugin.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_PNM_Image.H>
#include <FL/Fl_Positioner.H>
#include <FL/Fl_PostScript.H>
#include <FL/Fl_Preferences.H>
#include <FL/Fl_Printer.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Radio_Button.H>
#include <FL/Fl_Radio_Light_Button.H>
#include <FL/Fl_Radio_Round_Button.H>
#include <FL/Fl_Repeat_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_Roller.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Round_Clock.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/fl_show_colormap.H>
#include <FL/fl_show_input.H>
#include <FL/Fl_Simple_Counter.H>
#include <FL/Fl_Single_Window.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Spinner.H>
#include <FL/Fl_Sys_Menu_Bar.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Tile.H>
#include <FL/Fl_Tiled_Image.H>
#include <FL/Fl_Timer.H>
#include <FL/Fl_Toggle_Button.H>
#include <FL/Fl_Toggle_Light_Button.H>
#include <FL/Fl_Toggle_Round_Button.H>
#include <FL/Fl_Tooltip.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Tree_Item.H>
#include <FL/Fl_Tree_Item_Array.H>
#include <FL/Fl_Tree_Prefs.H>
#include <FL/Fl_Valuator.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_XBM_Image.H>
#include <FL/Fl_XPM_Image.H>
#include <FL/forms.H>
#ifdef USE_OPENGL
#include <FL/gl.H>
#include <FL/gl2opengl.H>
#include <FL/glu.H>
#include <FL/glut.H>
#include <FL/gl_draw.H>
#endif
#ifdef USE_MATH_NAMES
//#include <FL/math.H>
//#include <FL/names.H>
#endif
#include <FL/x.H>

#ifndef free_color
#define free_color(x,y) get_color(x) //we don't need it now
#endif

extern "C" {
	#include "../../../simple/include/simple.h"
	SIMPLE_API void init_full_tick(SimpleState *sState);
}

class CallbackStruct
{
public:
	static void *_sState;
	static bool ret_evt_to_fl;

};

static void SimpleCallBack(Fl_Widget*, int ptr_index) ;
static void SimpleMenuCallBack(Fl_Widget*, int ptr_index) ;

#endif //FULLTICK_H
