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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
						
#include <rkrellmDisplay.h>
#include <rkrellmStats.h>

/*Clears the screen*/
void clrscr(void){
  int y, x, maxy, maxx;
  getmaxyx(stdscr, maxy, maxx);
  for(y=0; y < maxy; y++)
    for(x=0; x < maxx; x++)
      mvaddch(y, x, ' ');
  return;
}

void wCenterTitleTop(WINDOW *pwin, const char * title){
  int x, maxy, maxx, stringsize;
  getmaxyx(pwin, maxy, maxx);
  stringsize = 2 + strlen(title);
  x = (maxx - stringsize)/2;
  mvwaddch(pwin, 0, x, ACS_RTEE);
  waddstr(pwin, title);
  waddch(pwin, ACS_LTEE);
  return;
}

void wCenterTitleBottom(WINDOW *pwin, const char * title){
  int x, maxy, maxx, stringsize;
  getmaxyx(pwin, maxy, maxx);
  stringsize = 2 + strlen(title);
  x = (maxx - stringsize)/2;
  mvwaddch(pwin, maxy - 1, x, ACS_RTEE);
  waddstr(pwin, title);
  waddch(pwin, ACS_LTEE);
  return;
}

int setup_screen(WINDOW **windows){
  /*
  WINDOW *main_win; 	0 
  WINDOW *general_win;	1
  WINDOW *user_win;	2
  WINDOW *disk_win;	3
  WINDOW *mem_win; 	4
  WINDOW *load_win;	5
  WINDOW *net_win;	6
  WINDOW *proc_win;	7
  WINDOW *battery_win;	8
   */
  
  int ymax, xmax;

  screen_init = 0;
  
  /*Initialize statgrab*/
  initialize_statgrab();

  
  /*Initialize the screen*/
  initscr();

  /*disable return key making new lines*/
  nonl();
  /*disable character buffering*/
  cbreak();
  /*disable echoing of typed characters*/
  noecho();
  /*only block for 1 second*/
  timeout(1000);
  /*enables special function keys*/
  keypad(stdscr, TRUE);

  /*Check to make sure that the terminal size is big enough*/
  /*ymax= 56 xmax= 170 //my testing size */
  getmaxyx(stdscr, ymax, xmax);
  if (ymax < 56 || xmax < 170) {
    fprintf(stdout, "Terminal size too small\n");
    return 1;
  } 

  /*Setup terminal colors*/
  start_color();
  init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
  init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
  init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
  init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
  init_pair(BLUE_YELLOW, COLOR_BLUE, COLOR_YELLOW);
  init_pair(YELLOW_BLUE, COLOR_YELLOW, COLOR_BLUE);
  init_pair(YELLOW_GREEN, COLOR_YELLOW, COLOR_GREEN);
  init_pair(YELLOW_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(YELLOW_RED, COLOR_YELLOW, COLOR_RED);
  init_pair(RED_GREEN, COLOR_RED, COLOR_GREEN);
  wrefresh(stdscr);

  /* Create main window */
  windows[0] = newwin(ymax, xmax, 0,0);
  wattrset(windows[0], COLOR_PAIR(BLUE_BLACK));
  box(windows[0], 0, 0);
  wCenterTitleTop(windows[0], "Ratpoison and Terminal-Friendly Monitor");
  wCenterTitleBottom(windows[0], "Press ? for help ---- Press q to quit");
  touchwin(windows[0]);
  wnoutrefresh(windows[0]);

  /* Create the general window */  
  windows[1] = newwin(GENERAL_Y_SIZE, GENERAL_X_SIZE, 
		  		GENERAL_Y_POS, GENERAL_X_POS);
  wattrset(windows[1], COLOR_PAIR(BLUE_BLACK));
  graph_general(windows[1]);
  touchwin(windows[1]);
  wnoutrefresh(windows[1]);

  /* Create the user window*/
  windows[2] = newwin(USER_Y_SIZE, USER_X_SIZE, USER_Y_POS, USER_X_POS);
  wattrset(windows[2], COLOR_PAIR(BLUE_BLACK));
  graph_user(windows[2]);
  touchwin(windows[2]);
  wnoutrefresh(windows[2]);
  
  /* Create the disk window*/
  windows[3] = newwin(DISK_Y_SIZE, DISK_X_SIZE, DISK_Y_POS, DISK_X_POS);
  wattrset(windows[3], COLOR_PAIR(BLUE_BLACK));
  graph_disk(windows[3]);
  touchwin(windows[3]);
  wnoutrefresh(windows[3]);

  /* Create the memory window*/
  windows[4] = newwin(MEM_Y_SIZE, MEM_X_SIZE, MEM_Y_POS, MEM_X_POS);
  wattrset(windows[4], COLOR_PAIR(BLUE_BLACK));
  graph_mem(windows[4]);
  touchwin(windows[4]);
  wnoutrefresh(windows[4]);
  
  /* Create the network window*/
  windows[6] = newwin(NET_Y_SIZE, NET_X_SIZE, NET_Y_POS, NET_X_POS);
  wattrset(windows[6], COLOR_PAIR(BLUE_BLACK));
  graph_net(windows[6]);
  touchwin(windows[6]);
  wnoutrefresh(windows[6]);

  /* Create the load window*/
  windows[5] = newwin(LOAD_Y_SIZE, LOAD_X_SIZE, LOAD_Y_POS, LOAD_X_POS);
  wattrset(windows[5], COLOR_PAIR(BLUE_BLACK));
  graph_load(windows[5]);
  touchwin(windows[5]);
  wnoutrefresh(windows[5]);

  /* Create the process window*/
  windows[7] = newwin(PROC_Y_SIZE, PROC_X_SIZE, PROC_Y_POS, PROC_X_POS);
  wattrset(windows[7], COLOR_PAIR(BLUE_BLACK));
  graph_proc(windows[7]);
  touchwin(windows[7]);
  wnoutrefresh(windows[7]);
  
  /* Create the battery window*/
  /*
  windows[8] = newwin(BATTERY_Y_SIZE, BATTERY_X_SIZE, BATTERY_Y_POS, BATTERY_X_POS);
  wattrset(windows[8], COLOR_PAIR(BLUE_BLACK));
  graph_battery(windows[8]);
  touchwin(windows[8]);
  wnoutrefresh(windows[8]);
  */

  /*apply changes to actual screen*/
  doupdate();
  
  /*used by other graph funtions to determine 
   * if they are being run for the first time or not*/
  screen_init = 1;

  return 0;
}

/*updates the screen*/
int update_screen(WINDOW **windows){
  
  /*update general window*/
  wattrset(windows[1], COLOR_PAIR(BLUE_BLACK));
  graph_general(windows[1]);
  touchwin(windows[1]);
  wnoutrefresh(windows[1]);
  
  /* Create the user window*/
  wattrset(windows[2], COLOR_PAIR(BLUE_BLACK));
  graph_user(windows[2]);
  touchwin(windows[2]);
  wnoutrefresh(windows[2]);
  
  /* Create the disk window*/
  wattrset(windows[3], COLOR_PAIR(BLUE_BLACK));
  graph_disk(windows[3]);
  touchwin(windows[3]);
  wnoutrefresh(windows[3]);
  
  /* Create the memory window*/
  wattrset(windows[4], COLOR_PAIR(BLUE_BLACK));
  graph_mem(windows[4]);
  touchwin(windows[4]);
  wnoutrefresh(windows[4]);
  
  /* Create the network window*/
  wattrset(windows[6], COLOR_PAIR(BLUE_BLACK));
  graph_net(windows[6]);
  touchwin(windows[6]);
  wnoutrefresh(windows[6]);

  /* Create the load window*/
  wattrset(windows[5], COLOR_PAIR(BLUE_BLACK));
  graph_load(windows[5]);
  touchwin(windows[5]);
  wnoutrefresh(windows[5]);

  /* Create the process window*/
  wattrset(windows[7], COLOR_PAIR(BLUE_BLACK));
  graph_proc(windows[7]);
  touchwin(windows[7]);
  wnoutrefresh(windows[7]);
  
  /* Create the battery window*/
  /*
  wattrset(windows[8], COLOR_PAIR(BLUE_BLACK));
  graph_battery(windows[8]);
  touchwin(windows[8]);
  wnoutrefresh(windows[8]);
  */

  /*apply changes to actual screen*/
  doupdate();

  return 0;
}

int menu_screen(WINDOW *win, char c){
  
  win = newwin(MENU_Y_SIZE, MENU_X_SIZE, MENU_Y_POS, MENU_X_POS);
  wattrset(win, COLOR_PAIR(BLUE_BLACK));
  switch(c){
    case '?':
      help_menu(win);
      break;
    case '0':
      config_main(win);
      break;
  }
  return 0;
}



/*prototype for a percentage graph*/
void percent_graph(WINDOW *win, double per, char *per_str){

  int maxy, maxx;
  int i;
  
  getmaxyx(win, maxy, maxx);
  wattrset(win, COLOR_PAIR(BLUE_BLACK));
  mvwaddch(win, 0, 0, ACS_RTEE);
  wattrset(win, COLOR_PAIR(YELLOW_BLUE));
  for(i = 0; i < maxx - 4; i++){
    if( per >= ((i + 1)*100)/(maxx-4)){
      wattrset(win, COLOR_PAIR(YELLOW_BLUE));
      if(i < strlen(per_str)){
        waddch(win, per_str[i]);
      }	  
      else{
        waddch(win, ' ');
      }
    }	  
    else{
      wattrset(win, COLOR_PAIR(YELLOW_BLACK));
      if(i < strlen(per_str)){
        waddch(win, per_str[i]);
      }	  
      else{
        waddch(win, ' ');
      }
    }
  }

  wattrset(win, COLOR_PAIR(BLUE_BLACK));
  mvwaddch(win, 0, maxx-1, ACS_LTEE);
  touchwin(win);
  wnoutrefresh(win);

  return;
}

/*prototype for a percentage graph*/
void percent_graph_battery(WINDOW *win, double per, char *per_str){

  int maxy, maxx;
  int i;
  
  //wclear(win);
  getmaxyx(win, maxy, maxx);
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  mvwaddch(win, 1, 0, ACS_VLINE);
  mvwaddch(win, 2, 0, ACS_VLINE);
  mvwaddch(win, 0, 0, ACS_ULCORNER);
  mvwaddch(win, 3, 0, ACS_LLCORNER);
  mvwhline(win, 0, 1, 0, maxx - 2);
  wattrset(win, COLOR_PAIR(YELLOW_BLUE));
  for(i = 0; i < maxx - 4; i++){
    if( per >= ((i + 1)*100)/(maxx-4)){
      wattrset(win, COLOR_PAIR(YELLOW_BLUE));
      if(i < strlen(per_str)){
        mvwaddch(win, 1, i + 1, per_str[i]);
        mvwaddch(win, 2, i + 1, ' ');
      }	  
      else{
        mvwaddch(win, 1, i + 1, ' ');
        mvwaddch(win, 2, i + 1, ' ');
      }
    }	  
    else{
      wattrset(win, COLOR_PAIR(YELLOW_BLACK));
      if(i < strlen(per_str)){
        mvwaddch(win, 1, i + 1, per_str[i]);
        mvwaddch(win, 2, i + 1, ' ');
      }	  
      else{
        mvwaddch(win, 1, i + 1, ' ');
        mvwaddch(win, 2, i + 1, ' ');
      }
    }
  }

  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  mvwaddch(win, 0, maxx-1, ACS_URCORNER);
  mvwaddch(win, 1, maxx-1, ACS_LTEE);
  mvwaddch(win, 2, maxx-1, ACS_LTEE);
  mvwaddch(win, 3, maxx-1, ACS_LRCORNER);
  mvwhline(win, 3, 1, 0, maxx - 2);
  touchwin(win);
  wnoutrefresh(win);

  return;
}

/*prototype for a historical re-scaling graph*/
void histo_graph(WINDOW *win, char *title, double data[], double ranges[]){

  int maxy, maxx;
  double data_max;
  int i, j, k;
  double data_scaled[20];
  char max_str[20];

  /*find maximum data value*/
  data_max = data[0];
  for(i = 1; i < DATA_COUNT; i++){
    if(data[i] > data_max){
      data_max = data[i];
    }
  }

  /*scale data based on ranges given*/
  /*
  if(data_max <= ranges[1]){
    data_max = ranges[1];
  }
  */
  //if(data_max <= ranges[2] && data_max > ranges[1]){
  if(data_max <= ranges[2]){
    data_max = ranges[2];
  }

  /*Scale data to the graph*/
  for(i = 0; i < DATA_COUNT; i++){
      data_scaled[i] = ( data[i] * SCALE_MAX ) / data_max;
  }

  snprintf(max_str, sizeof(max_str), " max=%4.2lf ", data_max);

  //wclear(win);
  box(win, 0, 0);
  wCenterTitleBottom(win, max_str);
  wCenterTitleTop(win, title);
  getmaxyx(win, maxy, maxx);
  for(i = 1; i < DATA_COUNT + 1; i++){
    for(j = SCALE_MAX; j > 0; j--){
      k = 11 - j;	    
      if(data_scaled[i - 1] >= k ){
        if(data[i - 1] > ranges[2] ){
  	  wattrset(win, COLOR_PAIR(YELLOW_RED));
          mvwaddch(win, j, i, ' ');
	  continue;
	}
        if(data[i - 1] <= ranges[2] && data[i - 1] > ranges[1]){
  	  wattrset(win, COLOR_PAIR(YELLOW_YELLOW));
          mvwaddch(win, j, i, ' ');
	  continue;
        }
        if(data[i - 1] <= ranges[1] && data[i - 1] > ranges[0]){
  	  wattrset(win, COLOR_PAIR(YELLOW_GREEN));
          mvwaddch(win, j, i, ' ');
	  continue;
        }
        if(data[i - 1] <= ranges[0] ){
	  wattrset(win, COLOR_PAIR(YELLOW_BLUE));
          mvwaddch(win, j, i, ' ');
	  continue;
        }
      }
      else{
  	wattrset(win, COLOR_PAIR(YELLOW_BLACK));
        mvwaddch(win, j, i, ' ');
      }
    }    
  }
  touchwin(win);
  wnoutrefresh(win);
  return;
}

void format_int_size(long long *num, char *c, int length){
  int i;

  long long max;

  int FITS;

  max = 1; 

  for(i = 0; i < length; i++){
    max = max * 10;
  }

  FITS = 0;

  *c = 'b';

  if(*num >= max ){
    *c = 'k';
    *num = *num / 1024;
  }
  else{
    return;
  }
  if(*num >= max ){
    *c = 'm'; 
    *num = *num / 1024;
  }
  else{
    return;
  }
  if(*num >= max ){
    *c = 'g';
    *num = *num / 1024;
  }
  else{
    return;
  }
  return;
}

void format_int_count(long long *num, char *c, int length){
  int i;

  long long max;

  int FITS;

  max = 1; 

  for(i = 0; i < length; i++){
    max = max * 10;
  }

  FITS = 0;

  *c = ' ';

  if(*num >= max ){
    *c = 'K';
    *num = *num / 1000;
  }
  else{
    return;
  }
  if(*num >= max ){
    *c = 'M'; 
    *num = *num / 1000;
  }
  else{
    return;
  }
  if(*num >= max ){
    *c = 'G';
    *num = *num / 1000;
  }
  else{
    return;
  }
  return;
}
