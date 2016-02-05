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

/*
 * NOTES
  -OS_version field currently disabled because it is too long.  
*/

#include <ncurses.h>

#include <rkrellmStats.h>
#include <rkrellmDisplay.h>

void graph_general(WINDOW *win){
  int maxy, maxx;
  sg_host_info *general_info;
  char uptime_str[20];
  int tmp, days, hours, minutes, seconds;
  
  /*no reason to do this twice*/
  if(!screen_init){
    wclear(win);
    box(win, 0, 0);
  }
  wCenterTitleTop(win, "General Info");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  getmaxyx(win, maxy, maxx);
  general_info = get_general_info(); 

  days = (long long)general_info->uptime / 86400;
  tmp = (long long)general_info->uptime - ( days * 86400);
  hours = tmp / 3600;
  tmp = tmp - ( hours * 3600);
  minutes = tmp / 60;
  tmp = tmp - ( minutes * 60);
  seconds = tmp;

  sprintf(uptime_str, "%d days, %.2d:%.2d:%.2d    ", 
		  days, 
		  hours, 
		  minutes,
		  seconds);
  
  mvwaddstr(win, 1, 1, "OS Name: ");
  waddstr(win, general_info->os_name);
  
  mvwaddstr(win, 2, 1, "OS Release: ");
  waddstr(win, general_info->os_release);
  
  mvwaddstr(win, 3, 1, "OS Version: ");
  waddnstr(win, general_info->os_version, 33);
  
  mvwaddstr(win, 4, 1, "Platform: ");
  waddstr(win, general_info->platform);

  mvwaddstr(win, 5, 1, "Hostname: ");
  waddstr(win, general_info->hostname);
  
  mvwaddstr(win, 6, 1, "Uptime: ");
  waddstr(win, uptime_str);
  
  touchwin(win);
  wnoutrefresh(win);
  return;
}
