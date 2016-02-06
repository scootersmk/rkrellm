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


void graph_proc(WINDOW *win){

  int maxy, maxx;
  char general_str[74];
  char process_str[74];
  sg_process_count *process_count;
  sg_process_stats *process_stats;
  sg_process_stats **top_procs;
  int num_processes;
  int xpos;
  int tmp, days, hours, minutes, seconds;
  int i, j, k;
  long long mem_size, mem_res;
  char mem_size_ch, mem_res_ch;

  /*no reason to do this twice*/
  if(!screen_init){
    wclear(win);
    box(win, 0, 0);
  }
  wCenterTitleTop(win, "Process Info");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  getmaxyx(win, maxy, maxx);

  process_count = get_process_count_info();
  process_stats = get_process_info(&num_processes);

  top_procs = (sg_process_stats**)malloc(sizeof(sg_process_stats*) * 8);
  /*
  for(i = 0 ; i < 8; i++){
    top_procs[i] = (sg_process_stats*)malloc(sizeof(sg_process_stats));
  }
  */
  /*
  for(i = 0; i < 60; i++){
    process_stats++;	  
  }
  for(i = 0; i < 8; i++){
    if(i != 0){
      process_stats++;  
    }
    top_procs[i] = process_stats;
  }
  */

  for(i = 0; i < num_processes; i++){
    if(i != 0){
      process_stats++;  
    }
    if(i < 8){
      top_procs[i] = process_stats; 
    }
    else{
      for(j = 0; j < 8; j++){
        if(top_procs[j] == NULL){
          top_procs[j] = process_stats;
          j = 8;
        } 
        else if( process_stats->cpu_percent > top_procs[j]->cpu_percent){
          for(k = 7; k > j; k--){
            top_procs[k] = top_procs[k-1];
	  }
          top_procs[j] = process_stats; 
	  j = 8;
        }
      }
    }
  }
  

  /* display general process information(count, types, etc...)*/
  snprintf(general_str, sizeof(general_str), "Total:%4d  Running:%4d  Sleeping:%4d Stopped:%4d  Zombie:%4d",
		  process_count->total, 
		  process_count->running, 
		  process_count->sleeping, 
		  process_count->stopped, 
		  process_count->zombie);

  mvwaddstr(win, 1, 1, general_str);
  mvwaddstr(win, 3, 1, " uid   pid   ppid    time     cpu  mem  size  nice  st  name          ");
  mvwhline(win, 4, 1, 0, 73);
  for(xpos = 5 ; xpos < 13; xpos++){

    tmp = (int)top_procs[xpos - 5]->time_spent;

    days = 0;	    
    hours = 0;
    minutes = 0;
    seconds = 0;
    if(tmp == 0){	    
      days = tmp / 86400;
      tmp = tmp - ( days * 86400);
    }
    if(tmp == 0){	    
      hours = tmp / 3600;
      tmp = tmp - ( hours * 3600);
    }
    if(tmp == 0){	    
      minutes = tmp / 60;
      tmp = tmp - ( minutes * 60);
      seconds = tmp;
    }

    mem_size = top_procs[xpos - 5]->proc_size;
    mem_res = top_procs[xpos - 5]->proc_resident;

    format_int_size(&mem_size, &mem_size_ch, 3);
    format_int_size(&mem_res, &mem_res_ch, 3);
	 
    snprintf(process_str, sizeof(process_str), 
		  "%5d %5d %5d  %02d:%02d:%02d  %3.0lf%%  %3lld%c  %3lld%c %3d   %d   %-15s",
		  top_procs[xpos - 5]->uid, 
		  top_procs[xpos - 5]->pid, 
		  top_procs[xpos - 5]->parent,
		  hours, 
		  minutes, 
		  seconds, 
		  top_procs[xpos - 5]->cpu_percent,
		  mem_res,
		  mem_res_ch,
		  mem_size,
		  mem_size_ch,
		  top_procs[xpos - 5]->nice, 
		  top_procs[xpos - 5]->state, 
		  top_procs[xpos - 5]->process_name);
		  
    mvwaddnstr(win, xpos, 1, process_str, -1);
  }
  touchwin(win);
  wnoutrefresh(win);
  free(top_procs);

  return;
}
						
