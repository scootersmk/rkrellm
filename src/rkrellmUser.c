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
#include <string.h>
#include <stdlib.h>

#include <rkrellmStats.h>
#include <rkrellmDisplay.h>


void graph_user(WINDOW *win){
  sg_user_stats *users;
  int maxy, maxx, count, i, j, found, index;
  char user_count_str[20];
  char user_str[20];
  char *str, *tok;
  char **list;
  int *shells;

  /*no reason to do this twice*/
  if(!screen_init){
    wclear(win);
    box(win, 0, 0);
  }
  wCenterTitleTop(win, "User Info");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  getmaxyx(win, maxy, maxx);

  /*get the user info from statgram*/
  users = get_user_info();
  
  /*total count of users(repeats allowed)*/
  count = users->num_entries;
  
  list = (char **)malloc(sizeof(char *) * count);
  if(list == NULL){
    perror("Mallocing list");
    exit(1);
  }
  shells = (int *)malloc(sizeof(int) * count);
  if(shells == NULL){
    perror("Mallocing shells");
    exit(1);
  }
  for(i = 0; i < count; i++){
    shells[i] = 0;
  } 

  /*the next free index in the list and shells array
   * and this will also correspond to the number of *unique* 
   * user names*/
  index = 0;

  /*for each user in the user_list string check to see if 
   * that user is already in the list. If they are, increment 
   * that user's shell count. If not, add the user to the end 
   * of the list*/
  for( i = 0, str = users->name_list; ; i++, str = NULL ){
    tok = strtok(str, " ");
    if( tok == NULL){
      break;
    }
    found = 0;
    for(j = 0; j < index; j++){
      if(strcmp(tok, list[j]) == 0){
        found = 1;
	shells[j]++;
	break;
      }
    }
    if(found == 0){
        list[index] = (char*)malloc(sizeof(char)*(strlen(tok) + 1));
	snprintf(list[index], sizeof(list[index]), "%s", tok);
	shells[index]++;
	index++;
    }
  } 

  snprintf(user_count_str, sizeof(user_count_str), "%d", 
		  index);
  mvwaddstr(win, 1, 1, "# of users: ");
  waddstr(win, user_count_str);
  mvwaddstr(win, 2, 1, "Users: ");
  i = 0;
  while( i < maxy - 4 ){
    if(i < index ){
      snprintf(user_str, sizeof(user_str), "%s %d", list[i], shells[i]); 
      mvwaddstr(win, i+3, 2, user_str);    
      i++;
    }	  
    else{
      mvwaddstr(win, i+3, 2, "               ");    
      i++;
    }
  }
  touchwin(win);
  wnoutrefresh(win);

  for(i = 0; i < index; i++){
    free(list[i]); 
  }

  free(list);
  free(shells);

  return;
}
