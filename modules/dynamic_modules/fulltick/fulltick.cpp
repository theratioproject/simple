#include "fulltick_delegate.cpp"

/** the callback class for fulltick library **/
CallbackStruct::CallbackStruct(void *the_pointer, String *the_block, Fl_Widget *the_widget) {
	pointer = the_pointer ;
	block = the_block ;
	widget = the_widget ;
}

/** the callback delegate for the fulltick library **/
static void SimpleCallBack(Fl_Widget*, void* callback_struct) {
	CallbackStruct *cbs = (CallbackStruct *) callback_struct ; 
	simple_vm_runcode((VM *) cbs->pointer,simple_string_get(cbs->block));
}

/** might be needed later for key listeners **/
int MyWindow::handle(int msg) {
  return msg;
}

extern "C" {

	SIMPLE_API void init_simple_module(SimpleState *sState)
	{
		init_full_tick(sState);
	}

}

SIMPLE_BLOCK(test_gui)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(SIMPLE_API_MISS1PARA);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) ) {
		Fl_Window *window = new Fl_Window(340,180);
		Fl_Box *box = new Fl_Box(20,40,300,100,SIMPLE_API_GETSTRING(1));
		box->box(FL_UP_BOX);
		box->labelfont(FL_BOLD+FL_ITALIC);
		box->labelsize(36);
		box->labeltype(FL_SHADOW_LABEL);
		window->end();
		window->show();
		int ret = Fl::run();
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/** FAPP **/

SIMPLE_BLOCK(run_fulltick)
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(FULLTICK_NOPARAM);
		return ;
	} SIMPLE_API_RETNUMBER(Fl::run()); 
}

SIMPLE_BLOCK(set_scheme)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	} 
	if ( SIMPLE_API_ISSTRING(1) ) {
		Fl::scheme(simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(1))->str);
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	} 
}

/** FWIDGETS **/

SIMPLE_BLOCK(resizable_object)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISPOINTER(2) ) {
		Fl_Group * group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		Fl_Widget * widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(2,"SIMPLE_FLTK_");
		group->resizable(widget); 
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_widget_background)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Widget *window = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		window->color(((Fl_Color) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_label_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Widget *window = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		window->labelcolor(((Fl_Color) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_label_size)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Widget *window = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		window->labelsize((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_label_type)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Widget *widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (_FL_SHADOW_LABEL == ((Fl_Labeltype)(int)SIMPLE_API_GETNUMBER(2)))
			widget->labeltype(FL_SHADOW_LABEL);
		else if ((FL_NORMAL_LABEL == ((Fl_Labeltype)(int)SIMPLE_API_GETNUMBER(2))))
			widget->labeltype(FL_SYMBOL_LABEL);
		else if ((_FL_ENGRAVED_LABEL == ((Fl_Labeltype)(int)SIMPLE_API_GETNUMBER(2))))
			widget->labeltype(FL_ENGRAVED_LABEL);
		else if ((_FL_EMBOSSED_LABEL == ((Fl_Labeltype)(int)SIMPLE_API_GETNUMBER(2))))
			widget->labeltype(FL_EMBOSSED_LABEL);
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_label_font)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Widget *window = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		window->labelfont((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_label)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_Widget *window = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		window->copy_label(SIMPLE_API_GETSTRING(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_size)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		Fl_Widget *window = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		window->size((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_tooltip)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	} 
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_Widget *window = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		String* tooltip = simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(2));
		window->tooltip(tooltip->str);
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_visibility)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	} 
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Widget *object = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (SIMPLE_API_GETNUMBER(2) == 0) {
			object->hide();
		} else if (SIMPLE_API_GETNUMBER(2) == 1) {
			object->show();
		} else if (SIMPLE_API_GETNUMBER(2) == 2) {
			Fl_Window* object = (Fl_Window* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
			object->iconize();
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(on_click)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) ) {
		Fl_Widget *widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		String * str = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(2)); 
		CallbackStruct *cbs = new CallbackStruct(pointer, str, widget);
		widget->callback(SimpleCallBack,cbs);
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(activate_deactivate_widget)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Widget *widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (SIMPLE_API_GETNUMBER(2) == 1) {
			widget->activate();
		} else {
			widget->deactivate();
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(add_widget)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) && SIMPLE_API_ISCPOINTER(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Group *window = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ( (int)SIMPLE_API_GETNUMBER(3) == 1) {
			window->add_resizable(*((Fl_Group* ) SIMPLE_API_GETCPOINTER(2,"SIMPLE_FLTK_")));
		} else {
			window->add(((Fl_Group* ) SIMPLE_API_GETCPOINTER(2,"SIMPLE_FLTK_")));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(redraw_widget)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) ) {
		Fl_Widget *widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->redraw();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(redraw_widget_parent)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) ) {
		Fl_Widget *widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->parent()->redraw();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(get_parent_widget)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) ) {
		Fl_Widget *widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		Fl_Widget *parent_widget = widget->parent();
		SIMPLE_API_RETCPOINTER(parent_widget,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_position)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		Fl_Widget *widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->position((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(widget_box)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Widget *widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(2)==-1) {
			SIMPLE_API_RETNUMBER(widget->box());
		} else {
			widget->box(((Fl_Boxtype)(int)SIMPLE_API_GETNUMBER(2)));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/** FWINDOW **/

SIMPLE_BLOCK(init_window)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING6PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISSTRING(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Window *window = new Fl_Window((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2), simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(3))->str);
		if (SIMPLE_API_GETNUMBER(4) == 1) 
		{
			Fl_Window& reswindow = *window; reswindow.resizable(&reswindow);
		} 
		window->end();
		SIMPLE_API_RETCPOINTER(window,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(show_window)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) ) {
		Fl_Window& window = *((Fl_Window* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"));
		window.show();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(full_screen)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2)) {
		Fl_Window *window = (Fl_Window* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(2) == 1 ) {
			window->fullscreen();
		} else {
			window->fullscreen_off();
		}
		
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(window_border)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2)) {
		Fl_Window *window = (Fl_Window* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		window->border((int)SIMPLE_API_GETNUMBER(2));
		int windowx = window->x(), windowy = window->y();
		 window->hide(); window->show(); window->position(windowx, windowy);
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_window_icon)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Window *window = (Fl_Window* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		//window->icon((char*)LoadIcon(fl_display, MAKEINTRESOURCE(101)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/** FBOX/FPANEL **/

SIMPLE_BLOCK(init_box)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Box *box = new Fl_Box((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(box,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(set_box_type)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Box *box = ((Fl_Box* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"));
		box->box((Fl_Boxtype)(int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/** GROUP **/

SIMPLE_BLOCK(init_group)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Group *group = new Fl_Group((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(group,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(group_begin)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		group->begin();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(group_children)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(2)==-1) {
			SIMPLE_API_RETNUMBER(group->children());
		} else {
			SIMPLE_API_RETCPOINTER(group->child((int)SIMPLE_API_GETNUMBER(2)),"SIMPLE_FLTK_");
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(group_clear)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		group->clear();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(group_clip_children)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(2)==-1) {
			SIMPLE_API_RETNUMBER(group->clip_children());
		} else {
			group->clip_children((int)SIMPLE_API_GETNUMBER(2));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(group_end)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		group->end();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(group_find)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISPOINTER(2) ) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETNUMBER(group->find((Fl_Widget* ) SIMPLE_API_GETCPOINTER(2,"SIMPLE_FLTK_"))-1);
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(group_focus)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISPOINTER(2) ) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		group->focus((Fl_Widget* ) SIMPLE_API_GETCPOINTER(2,"SIMPLE_FLTK_"));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(group_init_sizes)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		group->init_sizes();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(group_insert)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISPOINTER(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(3)==-1) {
			group->insert(*((Fl_Widget* ) SIMPLE_API_GETCPOINTER(2,"SIMPLE_FLTK_")),(Fl_Widget* ) SIMPLE_API_GETCPOINTER(4,"SIMPLE_FLTK_"));
		} else {
			group->insert(*((Fl_Widget* ) SIMPLE_API_GETCPOINTER(2,"SIMPLE_FLTK_")),(int)SIMPLE_API_GETNUMBER(3));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(group_remove)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2)) {
		Fl_Group *group = (Fl_Group* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(2)==-1) {
			group->remove((Fl_Widget* ) SIMPLE_API_GETCPOINTER(3,"SIMPLE_FLTK_"));
		} else {
			group->remove((int)SIMPLE_API_GETNUMBER(2));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/** FLABEL **/

SIMPLE_BLOCK(set_size_with_label)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Widget *widget = (Fl_Widget* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		int wi=0, hi=0; fl_font(widget->labelfont(), widget->labelsize()); 
		fl_measure(widget->label(), wi,hi);
		widget->size(wi+(int)SIMPLE_API_GETNUMBER(2),hi+(int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/** FBUTTON (s) **/

SIMPLE_BLOCK(init_button)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Button *button = new Fl_Button((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(button,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_return_button)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Return_Button *button = new Fl_Return_Button((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(button,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_repeat_button)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Repeat_Button *button = new Fl_Repeat_Button((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(button,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_light_button)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Light_Button *button = new Fl_Light_Button((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(button,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_round_button)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Round_Button *button = new Fl_Round_Button((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(button,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_check_button)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Check_Button *button = new Fl_Check_Button((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(button,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_toggle_button)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Toggle_Button *button = new Fl_Toggle_Button((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(button,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(set_button_down_box)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Button *box = ((Fl_Button* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"));
		box->down_box((Fl_Boxtype)(int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(set_button_down_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Button *button = (Fl_Button* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		button->down_color(((Fl_Color) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_button_only)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Button *button = (Fl_Button* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		button->setonly();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_button_shortcut)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Button *button = (Fl_Button* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (((int)SIMPLE_API_GETNUMBER(2)) == 1) {
			button->shortcut(((int)SIMPLE_API_GETNUMBER(3)));
		} else {
			button->shortcut(((char *)SIMPLE_API_GETSTRING(3)));
		}
		
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(set_button_value)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Button *button = (Fl_Button* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		button->value(((int) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(get_button_value)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Button *button = (Fl_Button* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETNUMBER(button->value());
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/** FINPUT/FTEXT (s) **/

SIMPLE_BLOCK(init_input)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Input *input = new Fl_Input((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(input,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_float_input)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Float_Input *input = new Fl_Float_Input((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(input,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_int_input)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Int_Input *input = new Fl_Int_Input((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(input,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_secret_input)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Secret_Input *input = new Fl_Secret_Input((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(input,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_multiline_input)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Multiline_Input *input = new Fl_Multiline_Input((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(input,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(input_copy)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (SIMPLE_API_GETNUMBER(3) == 1) {
			SIMPLE_API_RETNUMBER(input->copy((int)SIMPLE_API_GETNUMBER(2)));
		} else {
			SIMPLE_API_RETNUMBER(input->copy_cuts());
		}
		
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(input_cut)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (SIMPLE_API_GETNUMBER(4) == 1) {
			SIMPLE_API_RETNUMBER(input->cut()); 
		} else if (SIMPLE_API_GETNUMBER(4) == 2) {
			SIMPLE_API_RETNUMBER(input->cut((int)SIMPLE_API_GETNUMBER(2)));
		} else {
			SIMPLE_API_RETNUMBER(input->cut((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3)));
		}
		
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(set_input_cursor_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->cursor_color(((Fl_Color) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(get_input_index)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETSTRING((const char*)input->index((int) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_insert)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(3) == -1) {
			input->insert((const char*) SIMPLE_API_GETSTRING(2));
		} else { 
			input->insert((const char*) SIMPLE_API_GETSTRING(2), (int)SIMPLE_API_GETNUMBER(3));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_mark)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(3) == 1) {
			SIMPLE_API_RETNUMBER(input->mark());
		} else { 
			SIMPLE_API_RETNUMBER(input->mark((int)SIMPLE_API_GETNUMBER(2)));
		}
		
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_maximum_size)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2)) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->maximum_size((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_position)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(4) == 1) {
			SIMPLE_API_RETNUMBER(input->position());
		} else if ((int)SIMPLE_API_GETNUMBER(4) == 0)  { 
			SIMPLE_API_RETNUMBER(input->position((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3)));
		} else {
			SIMPLE_API_RETNUMBER(input->position((int)SIMPLE_API_GETNUMBER(2)));
		}
		
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_read_only)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2)) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->readonly((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_replace)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISSTRING(4)) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->replace((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),SIMPLE_API_GETSTRING(4));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_shortcut)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->shortcut(((int)SIMPLE_API_GETNUMBER(2)));		
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_size)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETNUMBER(input->size());		
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_static_value)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->static_value(SIMPLE_API_GETSTRING(2));		
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_tab_nav)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->tab_nav((int)SIMPLE_API_GETNUMBER(2));		
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_text_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->textcolor(((Fl_Color) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_text_font)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->textfont((Fl_Font)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_text_size)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->textsize((Fl_Fontsize)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_value)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISSTRING(3)) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (((int)SIMPLE_API_GETNUMBER(2)) == 1) {
			SIMPLE_API_RETSTRING(input->value());
		} else {
			input->value(SIMPLE_API_GETSTRING(3));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_undo)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1)  ) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		input->undo();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(input_wrap)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Input_ *input = (Fl_Input_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (((int)SIMPLE_API_GETNUMBER(2)) == 1) {
			SIMPLE_API_RETNUMBER(input->wrap());
		} else {
			input->wrap((int)SIMPLE_API_GETNUMBER(3));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/** FMENU/FMENUBAR **/

SIMPLE_BLOCK(init_menu_bar)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Menu_Bar *menu_bar = new Fl_Menu_Bar((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(menu_bar,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(init_menu_button)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Menu_Button *menu_button = new Fl_Menu_Button((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(menu_button,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_add)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		menu->add(SIMPLE_API_GETSTRING(2),0, 0, 0, ((int)SIMPLE_API_GETNUMBER(3)));
		
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_clear)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (((int)SIMPLE_API_GETNUMBER(2)) == 1) {
			menu->clear_submenu(((int)SIMPLE_API_GETNUMBER(3)));
		} else {
			menu->clear();
		}
		
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_down_box)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		menu->down_box((Fl_Boxtype)(int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_selection_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		menu->down_color((Fl_Color)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_find_menu_item)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		Fl_Menu_Item *menu_item = (Fl_Menu_Item*)menu->find_item(SIMPLE_API_GETSTRING(2)) ;
		SIMPLE_API_RETCPOINTER(menu_item,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_global)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		menu->global();
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_insert)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISSTRING(3)) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		menu->insert((int)SIMPLE_API_GETNUMBER(2),SIMPLE_API_GETSTRING(3),0,0);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_selected_menu_item_value)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		char picked[80];
		menu->item_pathname(picked, sizeof(picked)-1);
		SIMPLE_API_RETSTRING(picked);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_mode)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		if (((int)SIMPLE_API_GETNUMBER(3)) == -101) {
			SIMPLE_API_RETNUMBER(menu->mode(((int)SIMPLE_API_GETNUMBER(2))));
		} else {
			menu->mode(((int)SIMPLE_API_GETNUMBER(2)), (int) SIMPLE_API_GETNUMBER(3));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_last_selected_menu_item)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		SIMPLE_API_RETCPOINTER((Fl_Menu_Item*)menu->mvalue(),"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_remove)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		menu->remove((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_replace)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISSTRING(3)) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		menu->replace((int)SIMPLE_API_GETNUMBER(2),SIMPLE_API_GETSTRING(3));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_setonly)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISPOINTER(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		Fl_Menu_Item *menuitem = (Fl_Menu_Item* ) SIMPLE_API_GETCPOINTER(2,"SIMPLE_FLTK_"); 
		menu->setonly(menuitem);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_shortcut)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		menu->shortcut((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_size)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		SIMPLE_API_RETNUMBER(menu->size());
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_text)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		if (((int)SIMPLE_API_GETNUMBER(2)) == -101) {
			SIMPLE_API_RETSTRING(menu->text());
		} else {
			SIMPLE_API_RETSTRING(menu->text((int)SIMPLE_API_GETNUMBER(2)));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_text_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		menu->textcolor(((Fl_Color) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_text_font)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		menu->textfont((Fl_Font)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_text_size)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		menu->textsize((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(menu_value)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Menu_ *menu = (Fl_Menu_* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(2)==-1) {
			SIMPLE_API_RETNUMBER(menu->value());
		} else if ((int)SIMPLE_API_GETNUMBER(2)==-101) {
			SIMPLE_API_RETNUMBER(menu->value(((Fl_Menu_Item* ) SIMPLE_API_GETCPOINTER(3,"SIMPLE_FLTK_"))));
		} else {
			SIMPLE_API_RETNUMBER(menu->value((int)SIMPLE_API_GETNUMBER(2)));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/** FMENUITEM **/

SIMPLE_BLOCK(menu_item_callback)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISCPOINTER(1) ) {
		Fl_Menu_Item *menuitem = (Fl_Menu_Item* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		String * str = simple_string_new_gc(((VM *) pointer)->sState,SIMPLE_API_GETSTRING(2)); 
		CallbackStruct *cbs = new CallbackStruct(pointer, str, (Fl_Widget*) menuitem);
		menuitem->callback(SimpleCallBack,cbs);
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/** BROWSERS(LISTBOX) **/

SIMPLE_BLOCK(listbox_type)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Browser *widget = (Fl_Browser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->type((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(listbox_value)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Browser *widget = (Fl_Browser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(2) == 1) {
			widget->value((int)SIMPLE_API_GETNUMBER(3) + 1);
		} else {
			SIMPLE_API_RETNUMBER(widget->value() - 1);
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(listbox_text)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Browser *widget = (Fl_Browser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (widget->text((int)SIMPLE_API_GETNUMBER(2) + 1)==NULL){
			SIMPLE_API_RETSTRING("");
		} else {
			SIMPLE_API_RETSTRING(widget->text((int)SIMPLE_API_GETNUMBER(2) + 1));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/** FILEBROWSER **/

SIMPLE_BLOCK(init_file_listbox)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_File_Browser *widget = new Fl_File_Browser((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(widget,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_listbox_load)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_File_Browser *widget = (Fl_File_Browser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->load(SIMPLE_API_GETSTRING(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(file_listbox_file_type)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_File_Browser *widget = (Fl_File_Browser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->filetype((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(file_listbox_filter)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_File_Browser *widget = (Fl_File_Browser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->filter(SIMPLE_API_GETSTRING(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(file_listbox_icon_size)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_File_Browser *widget = (Fl_File_Browser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->iconsize((uchar)(int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/** FILECHOOSER**/

SIMPLE_BLOCK(init_file_chooser)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISSTRING(1) && SIMPLE_API_ISSTRING(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISSTRING(4)) {
		Fl_File_Chooser *widget = new Fl_File_Chooser(SIMPLE_API_GETSTRING(1),SIMPLE_API_GETSTRING(2),(int)SIMPLE_API_GETNUMBER(3),simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(4))->str);
		SIMPLE_API_RETCPOINTER(widget,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(show_file_chooser)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1)) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->show(); Fl::wait();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(file_chooser_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		widget->textcolor(((Fl_Color) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_count)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		SIMPLE_API_RETNUMBER(widget->count());
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_directory)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		widget->directory(SIMPLE_API_GETSTRING(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_filter)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISSTRING(3) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		if ((int)SIMPLE_API_GETNUMBER(2) == -1) {
			SIMPLE_API_RETNUMBER(widget->filter_value());
		} else if ((int)SIMPLE_API_GETNUMBER(2) == -2){
			widget->filter(SIMPLE_API_GETSTRING(3));
		} else {
			widget->filter_value((int)SIMPLE_API_GETNUMBER(2));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(hide_file_chooser)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		widget->hide();
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_iconsize)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		widget->iconsize((uchar)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_label)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		widget->label(simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(2))->str);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_ok_label)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		widget->ok_label(simple_string_new_gc(((VM*)pointer)->sState,SIMPLE_API_GETSTRING(2))->str);
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_preview)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		widget->preview((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_rescan)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		widget->rescan();
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_is_shown)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		SIMPLE_API_RETNUMBER(widget->shown());
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_wait)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		while(widget->shown()){ Fl::wait(); }
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_value)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	} 
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2)) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		if ((int)SIMPLE_API_GETNUMBER(2)==1) {
			widget->value(SIMPLE_API_GETSTRING(3));
		} else {
			if (widget->value()==NULL){
				SIMPLE_API_RETSTRING("");
			} else {
				SIMPLE_API_RETSTRING(widget->value());
			}
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(file_chooser_get_directory)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_File_Chooser *widget = (Fl_File_Chooser* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		SIMPLE_API_RETSTRING(widget->directory());
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/* FTEXTDISPLAY */

SIMPLE_BLOCK(init_text_display)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Text_Display *widget = new Fl_Text_Display((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(widget,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(text_display_buffer)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISPOINTER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		widget->buffer((Fl_Text_Buffer*)SIMPLE_API_GETCPOINTER(2,"SIMPLE_FLTK_"));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(text_display_column_to_x)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3)) {
		Fl_Text_Display *widget = (Fl_Text_Display* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		if ((int)SIMPLE_API_GETNUMBER(2)==1) {
			SIMPLE_API_RETNUMBER(widget->col_to_x(SIMPLE_API_GETNUMBER(3)));
		} else {
			SIMPLE_API_RETNUMBER((int)widget->x_to_col(SIMPLE_API_GETNUMBER(3)));
		}
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(text_display_count_lines)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Text_Display *widget = (Fl_Text_Display* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		bool condition = false ;
		if ((int)SIMPLE_API_GETNUMBER(4)==1) {
			condition = true ;
		} 
		SIMPLE_API_RETNUMBER(widget->count_lines((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),condition));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_BLOCK(text_display_cursor_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->cursor_color(((Fl_Color) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_cursor_style)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->cursor_style(((int) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_cursor_visibility)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(2)==-1) {
			widget->hide_cursor();
		} else {
			widget->show_cursor(((int)SIMPLE_API_GETNUMBER(2)));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_in_selection)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) &&  SIMPLE_API_ISNUMBER(3)) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETNUMBER(widget->in_selection(((int)SIMPLE_API_GETNUMBER(2)),((int)SIMPLE_API_GETNUMBER(3))));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_insert)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) &&  SIMPLE_API_ISSTRING(3)) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(2)==-1) {
			widget->insert(SIMPLE_API_GETSTRING(3));
		} else if ((int)SIMPLE_API_GETNUMBER(2)==-2) {
			SIMPLE_API_RETNUMBER(widget->insert_position());
		} else {
			widget->insert_position((int)SIMPLE_API_GETNUMBER(2));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_line_start_end)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) &&  SIMPLE_API_ISNUMBER(3)) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if ((int)SIMPLE_API_GETNUMBER(3)==-1) {
			SIMPLE_API_RETNUMBER(widget->line_start((int)SIMPLE_API_GETNUMBER(2)));
		} else {
			bool condition = false ;
			if ((int)SIMPLE_API_GETNUMBER(3)==1) {
				condition = true ;
			}
			SIMPLE_API_RETNUMBER(widget->line_end((int)SIMPLE_API_GETNUMBER(2),condition));
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_line_number_align)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->linenumber_align(((Fl_Align) ((int)SIMPLE_API_GETNUMBER(2))));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_line_number_bg_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->linenumber_bgcolor(((Fl_Color) (int)SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_line_number_fg_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->linenumber_fgcolor(((Fl_Color) (int)SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_line_number_font)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->linenumber_font(((Fl_Font) (int)SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_line_number_format)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->linenumber_format(SIMPLE_API_GETSTRING(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_line_number_font_size)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->linenumber_size(((Fl_Fontsize) (int)SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_line_number_width)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->linenumber_width(((int) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_move)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		if (((int) SIMPLE_API_GETNUMBER(2))==1) {
			widget->move_down();
		} else if (((int) SIMPLE_API_GETNUMBER(2))==2) {
			widget->move_left();
		} else if (((int) SIMPLE_API_GETNUMBER(2))==3) {
			widget->move_right();
		} else {
			widget->move_up();
		}
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_next_word)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->next_word();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_overstrike)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->overstrike(SIMPLE_API_GETSTRING(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_position_style)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETNUMBER(widget->position_style((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_position_to_xy)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		int *x = 0 ; x += + (int)SIMPLE_API_GETNUMBER(3)  ;
		int *y = 0 ; y += + (int)SIMPLE_API_GETNUMBER(4)  ;
		SIMPLE_API_RETNUMBER(widget->position_to_xy((int)SIMPLE_API_GETNUMBER(2),x,y));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_previous_word)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->previous_word();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_redisplay_range)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->redisplay_range((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_rewind_lines)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->rewind_lines((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_scroll)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->scroll((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_scroll_bar_align)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->scrollbar_align(((Fl_Align) ((int)SIMPLE_API_GETNUMBER(2))));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_scroll_bar_width)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->scrollbar_width((int)SIMPLE_API_GETNUMBER(2));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_show_insert_position)
{
	if ( SIMPLE_API_PARACOUNT != 1 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING1PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->show_insert_position();
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_skip_lines)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		bool condition = false ;
		if ((int)SIMPLE_API_GETNUMBER(4)==1) {
			condition = true ;
		}
		SIMPLE_API_RETNUMBER(widget->skip_lines((int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),condition));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_text_color)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->textcolor(((Fl_Color) (int)SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_text_font)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->textfont(((Fl_Font) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_text_font_size)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->textsize(((Fl_Fontsize) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_word_end)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETNUMBER(widget->word_end(((int) SIMPLE_API_GETNUMBER(2))));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_word_start)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETNUMBER(widget->word_start(((int) SIMPLE_API_GETNUMBER(2))));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_wrap_mode)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		widget->wrap_mode((int) SIMPLE_API_GETNUMBER(2),(int) SIMPLE_API_GETNUMBER(3));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_wrapped_column)
{
	if ( SIMPLE_API_PARACOUNT != 3 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING3PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETNUMBER(widget->wrapped_column((int) SIMPLE_API_GETNUMBER(2),(int) SIMPLE_API_GETNUMBER(3)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

SIMPLE_BLOCK(text_display_wrapped_row)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISNUMBER(2) ) {
		Fl_Text_Display *widget = (Fl_Text_Display * ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_");
		SIMPLE_API_RETNUMBER(widget->wrapped_row((int) SIMPLE_API_GETNUMBER(2)));
	} else {
		SIMPLE_API_ERROR(FULLTICK_WRONGPARAM);
	}
}

/* FTEXTEDITOR */

SIMPLE_BLOCK(init_text_editor)
{
	if ( SIMPLE_API_PARACOUNT != 4 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	if ( SIMPLE_API_ISNUMBER(1) && SIMPLE_API_ISNUMBER(2) && SIMPLE_API_ISNUMBER(3) && SIMPLE_API_ISNUMBER(4)) {
		Fl_Text_Editor *widget = new Fl_Text_Editor((int)SIMPLE_API_GETNUMBER(1),(int)SIMPLE_API_GETNUMBER(2),(int)SIMPLE_API_GETNUMBER(3),(int)SIMPLE_API_GETNUMBER(4));
		SIMPLE_API_RETCPOINTER(widget,"SIMPLE_FLTK_");
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

/* FTEXTBUFFER */

SIMPLE_BLOCK(init_text_buffer)
{
	if ( SIMPLE_API_PARACOUNT != 0 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING4PARAM);
		return ;
	}
	Fl_Text_Buffer *buff = new Fl_Text_Buffer();
	SIMPLE_API_RETCPOINTER(buff,"SIMPLE_FLTK_");
}

SIMPLE_BLOCK(text_buffer_text)
{
	if ( SIMPLE_API_PARACOUNT != 2 ) {
		SIMPLE_API_ERROR(FULLTICK_MISING2PARAM);
		return ;
	}
	if ( SIMPLE_API_ISPOINTER(1) && SIMPLE_API_ISSTRING(2) ) {
		Fl_Text_Buffer *buffer = (Fl_Text_Buffer* ) SIMPLE_API_GETCPOINTER(1,"SIMPLE_FLTK_"); 
		buffer->text(SIMPLE_API_GETSTRING(2));
	} else {
		SIMPLE_API_ERROR(SIMPLE_API_BADPARATYPE);
	}
}

SIMPLE_API void init_full_tick(SimpleState *sState) 
{
	register_block("__test_gui",test_gui);

	/** FAPP **/
	register_block("__run_fulltick",run_fulltick);
	register_block("__set_scheme",set_scheme);

	/** FWIDGETS **/
	register_block("__resizable",resizable_object);
	register_block("__set_bg",set_widget_background);
	register_block("__set_label",set_label);
	register_block("__set_label_color",set_label_color);
	register_block("__set_label_size",set_label_size);
	register_block("__set_label_type",set_label_type);
	register_block("__set_label_font",set_label_font);
	register_block("__set_size",set_size);
	register_block("__set_position",set_position);
	register_block("__set_tooltip",set_tooltip);
	register_block("__set_visibility",set_visibility);
	register_block("__on_click",on_click);
	register_block("__add_widget",add_widget);
	register_block("__activate_deactivate_widget",activate_deactivate_widget);
	register_block("__redraw_widget",redraw_widget);
	register_block("__redraw_widget_parent",redraw_widget_parent);
	register_block("__get_parent_widget",get_parent_widget);
	register_block("__widget_box",widget_box);

	/** WINDOW **/
	register_block("__init_window",init_window);
	register_block("__show_window",show_window);
	register_block("__full_screen",full_screen);
	register_block("__window_border",window_border);
	register_block("__set_window_icon",set_window_icon);

	/** BOX/PANEL **/
	register_block("__init_box",init_box);
	register_block("__set_box_type",set_box_type);

	/** GROUP **/
	register_block("__init_group",init_group);
	register_block("__group_begin",group_begin);
	register_block("__group_children",group_children);
	register_block("__group_clear",group_clear);
	register_block("__group_clip_children",group_clip_children);
	register_block("__group_end",group_end);
	register_block("__group_find",group_find);
	register_block("__group_focus",group_focus);
	register_block("__group_init_sizes",group_init_sizes);
	register_block("__group_insert",group_insert);
	register_block("__group_remove",group_remove);
	register_block("__group_resize",resizable_object);

	/** LABEL **/
	register_block("__set_size_with_label",set_size_with_label);

	/** FBUTTON (s) **/
	register_block("__init_button",init_button);
	register_block("__init_return_button",init_return_button);
	register_block("__init_repeat_button",init_repeat_button);
	register_block("__init_light_button",init_light_button);
	register_block("__init_round_button",init_round_button);
	register_block("__init_check_button",init_check_button);
	register_block("__init_toggle_button",init_toggle_button);
	register_block("__set_button_down_box",set_button_down_box);
	register_block("__set_button_down_color",set_button_down_color);
	register_block("__set_button_only",set_button_only);
	register_block("__set_button_shortcut",set_button_shortcut);
	register_block("__set_button_value",set_button_value);
	register_block("__get_button_value",get_button_value);

	/** INPUT/FTEXT (s) **/
	register_block("__init_input",init_input);
	register_block("__init_float_input",init_float_input);
	register_block("__init_int_input",init_int_input);
	register_block("__init_secret_input",init_secret_input);
	register_block("__init_multiline_input",init_multiline_input);
	register_block("__input_copy",input_copy);
	register_block("__input_cut",input_cut);
	register_block("__set_input_cursor_color",set_input_cursor_color);
	register_block("__get_input_index",get_input_index);
	register_block("__input_insert",input_insert);
	register_block("__input_mark",input_mark);
	register_block("__input_maximum_size",input_maximum_size);
	register_block("__input_position",input_position);
	register_block("__input_read_only",input_read_only);
	register_block("__input_replace",input_replace);
	register_block("__input_shortcut",input_shortcut);
	register_block("__input_size",input_size);
	register_block("__input_static_value",input_static_value);
	register_block("__input_tab_nav",input_tab_nav);
	register_block("__input_text_color",input_text_color);
	register_block("__input_text_font",input_text_font);
	register_block("__input_text_size",input_text_size);
	register_block("__input_value",input_value);
	register_block("__input_undo",input_undo);
	register_block("__input_wrap",input_wrap);

	/** MENU/MENUBAR **/
	register_block("__init_menu_bar",init_menu_bar);
	register_block("__init_menu_button",init_menu_button);
	register_block("__menu_add",menu_add);
	register_block("__menu_clear",menu_clear);
	register_block("__menu_down_box",menu_down_box);
	register_block("__menu_selection_color",menu_selection_color);
	register_block("__menu_find_menu_item",menu_find_menu_item);
	register_block("__menu_global",menu_global);
	register_block("__menu_insert",menu_insert);
	register_block("__menu_selected_menu_item_value",menu_selected_menu_item_value);
	register_block("__menu_mode",menu_mode);
	register_block("__menu_last_selected_menu_item",menu_last_selected_menu_item);
	register_block("__menu_remove",menu_remove);
	register_block("__menu_replace",menu_replace);
	register_block("__menu_setonly",menu_setonly);
	register_block("__menu_shortcut",menu_shortcut);
	register_block("__menu_size",menu_size);
	register_block("__menu_text",menu_text);
	register_block("__menu_text_color",menu_text_color);
	register_block("__menu_text_font",menu_text_font);
	register_block("__menu_text_size",menu_text_size);
	register_block("__menu_value",menu_value);

	/** MENUITEM **/
	register_block("__menu_item_callback",menu_item_callback);

	/** BROWSERS(LISTBOX) **/
	register_block("__listbox_type",listbox_type);
	register_block("__listbox_value",listbox_value);
	register_block("__listbox_text",listbox_text);

	/** FILEBROWSER **/
	register_block("__init_file_listbox",init_file_listbox);
	register_block("__file_listbox_load",file_listbox_load);
	register_block("__file_listbox_file_type",file_listbox_file_type);
	register_block("__file_listbox_filter",file_listbox_filter);
	register_block("__file_listbox_icon_size",file_listbox_icon_size);

	/** FILECHOOSER **/
	register_block("__init_file_chooser",init_file_chooser);
	register_block("__show_file_chooser",show_file_chooser);
	register_block("__file_chooser_color",file_chooser_color);
	register_block("__file_chooser_count",file_chooser_count);
	register_block("__file_chooser_directory",file_chooser_directory);
	register_block("__file_chooser_filter",file_chooser_filter);
	register_block("__hide_file_chooser",hide_file_chooser);
	register_block("__file_chooser_iconsize",file_chooser_iconsize);
	register_block("__file_chooser_label",file_chooser_label);
	register_block("__file_chooser_ok_label",file_chooser_ok_label);
	register_block("__file_chooser_preview",file_chooser_preview);
	register_block("__file_chooser_rescan",file_chooser_rescan);
	register_block("__file_chooser_is_shown",file_chooser_is_shown);
	register_block("__file_chooser_wait",file_chooser_wait);
	register_block("__file_chooser_value",file_chooser_value);
	register_block("__file_chooser_get_directory",file_chooser_get_directory);

	/** FTEXTDISPLAY **/
	register_block("__init_text_display",init_text_display);
	register_block("__text_display_buffer",text_display_buffer);
	register_block("__text_display_scroll_bar_width",text_display_scroll_bar_width);
	register_block("__text_display_column_to_x",text_display_column_to_x);
	register_block("__text_display_count_lines",text_display_count_lines);
	register_block("__text_display_cursor_color",text_display_cursor_color);
	register_block("__text_display_cursor_style",text_display_cursor_style);
	register_block("__text_display_cursor_visibility",text_display_cursor_visibility);
	register_block("__text_display_in_selection",text_display_in_selection);
	register_block("__text_display_insert",text_display_insert);
	register_block("__text_display_line_start_end",text_display_line_start_end);
	register_block("__text_display_line_number_width",text_display_line_number_width);
	register_block("__text_display_line_number_align",text_display_line_number_align);
	register_block("__text_display_line_number_bg_color",text_display_line_number_bg_color);
	register_block("__text_display_line_number_fg_color",text_display_line_number_fg_color); 
	register_block("__text_display_line_number_font",text_display_line_number_font); 
	register_block("__text_display_line_number_format",text_display_line_number_format); 
	register_block("__text_display_line_number_font_size",text_display_line_number_font_size); 
	register_block("__text_display_move",text_display_move); 
	register_block("__text_display_next_word",text_display_next_word); 
	register_block("__text_display_overstrike",text_display_overstrike); 
	register_block("__text_display_position_style",text_display_position_style); 
	register_block("__text_display_position_to_xy",text_display_position_to_xy); 
	register_block("__text_display_previous_word",text_display_previous_word);
	register_block("__text_display_redisplay_range",text_display_redisplay_range); 
	//before this
	register_block("__text_display_text_color",text_display_text_color); 

	/** FTEXTEDITOR **/
	register_block("__init_text_editor",init_text_editor);

	/** FTEXTBUFFER **/
	register_block("__init_text_buffer",init_text_buffer);
	register_block("__text_buffer_text",text_buffer_text);

}