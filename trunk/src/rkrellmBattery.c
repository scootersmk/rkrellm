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

#include <ncurses.h>
#include <stdlib.h>

#include <rkrellmStats.h>
#include <rkrellmDisplay.h>

void graph_battery(WINDOW *win){

  int maxy, maxx;
  sg_battery_stats *battery_info;
  WINDOW *graph_win;
  double battery_percent;
  char battery_str[20];

  /*no reason to do this twice*/
  if(!screen_init){
    wclear(win);
    //box(win, 0, 0);
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);
  }
  wCenterTitleTop(win, "Battery Info");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  getmaxyx(win, maxy, maxx);

  battery_info = get_battery_info();
  if(battery_info == NULL){
    fprintf(stderr, "Error getting battery info. Exiting...\n");
    exit(1);
  }

  battery_percent = 
	  100 * ((float)battery_info->remaining_capacity/(float)battery_info->capacity);
  sprintf(battery_str, " %5.2f%%", battery_percent);
  graph_win = subwin(win, BATTERY_GRAPH_Y_SIZE, BATTERY_GRAPH_X_SIZE, BATTERY_GRAPH_Y_POS, BATTERY_GRAPH_X_POS);
  wattrset(graph_win, COLOR_PAIR(BLUE_BLACK));
  percent_graph_battery(graph_win, battery_percent, battery_str);
  touchwin(graph_win);
  wnoutrefresh(graph_win);

  touchwin(win);
  wnoutrefresh(win);

  return;
}
						
