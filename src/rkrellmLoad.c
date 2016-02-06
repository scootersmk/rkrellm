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

#include <rkrellmStats.h>
#include <rkrellmDisplay.h>

						

void graph_load(WINDOW *win){

  int i;
  int maxy, maxx;
  WINDOW *load1_win, *load5_win, *load15_win;
  char load1_head_str[20], load5_head_str[20], load15_head_str[20];
  sg_load_stats *load;
  double load_ranges[3];

  load_ranges[0] = LOAD_RANGE_LOW;
  load_ranges[1] = LOAD_RANGE_MEDIUM;
  load_ranges[2] = LOAD_RANGE_HIGH;

  
  for(i = 0 ; i < 19; i++ ){
    load1_vals[i] = load1_vals[i+1]; 
    load5_vals[i] = load5_vals[i+1]; 
    load15_vals[i] = load15_vals[i+1]; 
  }
  

  load = get_load_info();

  load1_vals[19] = load->min1; 
  load5_vals[19] =  load->min5; 
  load15_vals[19] = load->min15; 

  /*no reason to do this twice*/
  if(!screen_init){
    wclear(win);
    box(win, 0, 0);
  }
  wCenterTitleTop(win, "Load Info");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  getmaxyx(win, maxy, maxx);
 

  snprintf(load1_head_str, sizeof(load1_head_str), "1minute: %5.2f", 
		  load->min1);

  /* Create the load1 graph window*/
  load1_win = subwin(win, LOAD1_GRAPH_Y_SIZE, LOAD1_GRAPH_X_SIZE, LOAD1_GRAPH_Y_POS, LOAD1_GRAPH_X_POS);
  wattrset(load1_win, COLOR_PAIR(BLUE_BLACK));
  histo_graph(load1_win, load1_head_str, load1_vals, load_ranges);
  touchwin(load1_win);
  wnoutrefresh(load1_win);

  snprintf(load5_head_str, sizeof(load5_head_str), "5minutes: %5.2f", 
		  load->min5);

  /* Create the load2 graph window*/
  load5_win = subwin(win, LOAD5_GRAPH_Y_SIZE, LOAD5_GRAPH_X_SIZE, LOAD5_GRAPH_Y_POS, LOAD5_GRAPH_X_POS);
  wattrset(load5_win, COLOR_PAIR(BLUE_BLACK));
  histo_graph(load5_win, load5_head_str, load5_vals, load_ranges);
  touchwin(load5_win);
  wnoutrefresh(load5_win);
  
  snprintf(load15_head_str, sizeof(load15_head_str), "15minutes: %5.2f", 
		  load->min15);

  /* Create the load_total graph window*/
  load15_win = subwin(win, LOAD15_GRAPH_Y_SIZE, LOAD15_GRAPH_X_SIZE, LOAD15_GRAPH_Y_POS, LOAD15_GRAPH_X_POS);
  wattrset(load15_win, COLOR_PAIR(BLUE_BLACK));
  histo_graph(load15_win, load15_head_str, load15_vals, load_ranges);
  touchwin(load15_win);

  touchwin(win);
  wnoutrefresh(win);

  return;
}
