/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simple.c
 * Author: thecarisma
 *
 * Created on April 12, 2018, 04:22 AM
 */

#include "./includes/simple.h"

int WINAPI WinMain ( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	simple_state_main(__argc,__argv);
	return 0;
}
