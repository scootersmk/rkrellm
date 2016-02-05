/*
rkrellm - a _R_atpoison and _T_erminal _F_riendly _M_onitoring application
Copyright (C) 2005 Scott M. Koch

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*Include installed library related header files*/
#include <ncurses.h>
#include <statgrab.h>

/*Include various display parameter specific header files*/
#include <rkrellmDisplayColors.h>
#include <rkrellmDisplaySizes.h>

/*Include various section specific header files*/
#include <rkrellmGeneral.h>
#include <rkrellmDisk.h>
#include <rkrellmUser.h>
#include <rkrellmProc.h>
#include <rkrellmLoad.h>
#include <rkrellmMemory.h>
#include <rkrellmNetwork.h>
#include <rkrellmMenu.h>
#ifdef RTFM_BATTERY
#include <rkrellmBattery.h>
#endif

/*Tells graph functions whether they are being run for the first time or not*/
int screen_init;

/*Various display functions*/

/*Clears the screen*/
void clrscr(void);

/*Places a title(centered) at the top of a window */
void wCenterTitleTop(WINDOW *pwin, const char * title);

/*Places a title(centered) at the bottom of a window*/
void wCenterTitleBottom(WINDOW *pwin, const char * title);

/*creates a graph in a window using the values in the percentage array*/
void graph(WINDOW *win, int max);

/*updates a graph with a new value*/
void update_graph(WINDOW *win, int data[], int new_val);

/*sets up the screen*/
int setup_screen(WINDOW **windows);

/*updates the screen*/
int update_screen(WINDOW **windows);

/*sets up the menu related screens*/
int menu_screen(WINDOW *win, char c);

/*prototype for a percentage graph*/
void percent_graph(WINDOW *win, double per, char *per_str);

/*prototype for a percentage graph, customized for battery info*/
void percent_graph_battery(WINDOW *win, double per, char *per_str);

/*prototype for a historical re-scaling graph*/
void histo_graph(WINDOW *win, char *title, double data[], double ranges[]);

/*format decimals so they take up only length number of spaces(for size values)*/
void format_int_space(long long  *num, char *c, int length);

/*format decimals so they take up only length number of spaces(for count values)*/
void format_int_count(long long  *num, char *c, int length);

/*format decimals so they take up only length number of spaces(for count values)*/
void format_int_size(long long *num, char *c, int length);
