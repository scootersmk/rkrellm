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
						
void graph_mem(WINDOW *win){

  sg_mem_stats *memory;
  sg_swap_stats *swap;

  int maxy, maxx;
  char mem_str[40], swap_str[40];
  char mem_per[10], swap_per[10], total_per[10];
  double mem_percent, swap_percent, total_used, total_percent, total;
  WINDOW *mem_main_win, *mem_swap_win, *mem_total_win;

  /*no reason to do this twice*/
  if(!screen_init){
    wclear(win);
    box(win, 0, 0);
  }
  wCenterTitleTop(win, "Memory Info");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  getmaxyx(win, maxy, maxx);
  
  
  memory = get_mem_info();
  swap = get_swap_info();

  mem_percent = 100 * ((float)memory->used / (float)memory->total);
  swap_percent =100 * ((float)swap->used / (float)swap->total);
  total_used = (float)swap->used + (float)memory->used;
  total = (float)swap->total + (float)memory->total;
  total_percent = 100 * (total_used / total);
  snprintf(mem_per, sizeof(mem_per), "%5.2f%%", mem_percent);
  snprintf(swap_per, sizeof(swap_per), "%5.2f%%", swap_percent);
  snprintf(total_per, sizeof(total_per), "%5.2f%%", total_percent);

  snprintf(mem_str, sizeof(mem_str), "Mem\t%lldM\t%lldM\t%lldM\t%lldM", 
		  (long long)memory->cache/(1024*1024), 
		  (long long)memory->used/(1024*1024), 
		  (long long)memory->free/(1024*1024), 
		  (long long)memory->total/(1024*1024));
  
  snprintf(swap_str, sizeof(swap_str), "Swap\t\t%lldM\t%lldM\t%lldM", 
		  (long long)swap->used/(1024*1024), 
		  (long long)swap->free/(1024*1024), 
		  (long long)swap->total/(1024*1024));
  mvwaddstr(win, 1, 1, "   \tCache\tUsed\tFree\tTotal");
  mvwaddstr(win, 2, 1, mem_str);
  
  /* Create the total memory graph window*/
  mem_main_win = subwin(win, MEM_MAIN_GRAPH_Y_SIZE, MEM_MAIN_GRAPH_X_SIZE, MEM_MAIN_GRAPH_Y_POS, MEM_MAIN_GRAPH_X_POS);
  wattrset(mem_main_win, COLOR_PAIR(BLUE_BLACK));
  percent_graph(mem_main_win, mem_percent, mem_per);
  touchwin(mem_main_win);
  wnoutrefresh(mem_main_win);

  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  mvwaddstr(win, 4, 1, swap_str);
  
  /* Create the total memory graph window*/
  mem_swap_win = subwin(win, MEM_SWAP_GRAPH_Y_SIZE, MEM_SWAP_GRAPH_X_SIZE, MEM_SWAP_GRAPH_Y_POS, MEM_SWAP_GRAPH_X_POS);
  wattrset(mem_swap_win, COLOR_PAIR(BLUE_BLACK));
  percent_graph(mem_swap_win, swap_percent, swap_per);
  touchwin(mem_swap_win);
  wnoutrefresh(mem_swap_win);

  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  mvwaddstr(win, 6, 1, "Total");


  /* Create the total memory graph window*/
  mem_total_win = subwin(win, MEM_TOTAL_GRAPH_Y_SIZE, MEM_TOTAL_GRAPH_X_SIZE, MEM_TOTAL_GRAPH_Y_POS, MEM_TOTAL_GRAPH_X_POS);
  wattrset(mem_total_win, COLOR_PAIR(BLUE_BLACK));
  percent_graph(mem_total_win, total_percent, total_per);
  touchwin(mem_total_win);
  wnoutrefresh(mem_total_win);

  touchwin(win);
  wnoutrefresh(win);
  return;
}
