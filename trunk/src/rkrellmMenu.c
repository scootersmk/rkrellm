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
#include <panel.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <rkrellmDisplay.h>
#include <rkrellmStats.h>

/*Main menu*/
/*Contents:
 * - Update interval
 * - Color choices
 * - Enabled windows
 * - Window size  
 * */
/*
char *choices1[] = {
  "1 second",
  "5 second",
  "10 second",
  "15 seconds",
  "Don't update",
  (char*)NULL,
};

char *choices2[] = {
  "blue/yellow(default)",
  "red/yellow",
  "green/yellow",
  "green/red",
  "green/blue",
  (char*)NULL,
};

char *choices3[] = {
  "Maximized(default)",
  "blah",
  "blah",
  "blah",
  "blah",
  (char*)NULL,
};
*/
void config_main(WINDOW *win){
	
  int c;
//  int i;
  int lines, cols;
  /*
  WINDOW *windows[3];
  PANEL *panels[3];
  MENU *menus[3];
  PANEL *top;
  ITEM **items1;
  ITEM **items2;
  ITEM **items3;
  */

  lines = 10;
  cols = 40;

  /*
  items1 = (ITEM**)malloc(sizeof(ITEM*) * 6);
  items2 = (ITEM**)malloc(sizeof(ITEM*) * 6);
  items3 = (ITEM**)malloc(sizeof(ITEM*) * 6);

  for(i = 0; i < 6; i++){
    items1[i] = new_item(choices1[i], choices1[i]);
    items2[i] = new_item(choices2[i], choices2[i]);
    items3[i] = new_item(choices3[i], choices3[i]);
  } 
  */

  wclear(win);
  wtimeout(win, -1);

  box(win, 0, 0);
  wCenterTitleTop(win, "Main Configuration");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  touchwin(win);
  wnoutrefresh(win);

  /*
  menus[0] = new_menu((ITEM **)items1);
  windows[0] = newwin(10, 40, 2, 2);
  keypad(windows[0], TRUE);
  set_menu_win(menus[0], windows[0]);
  set_menu_sub(menus[0], derwin(windows[0], 6, 38, 3, 1));
  set_menu_mark(menus[0], " * ");
  wattrset(windows[0], COLOR_PAIR(BLUE_BLACK));
  mvwprintw(windows[0], 1, 0, "Update Interval");
  mvwhline(windows[0], 2, 0, ACS_HLINE, 40);
  wnoutrefresh(windows[0]);
  post_menu(menus[0]);
  wnoutrefresh(windows[0]);
  
  menus[1] = new_menu((ITEM **)items2);
  windows[1] = newwin(10, 40, 14, 2);
  keypad(windows[1], TRUE);
  set_menu_win(menus[1], windows[1]);
  set_menu_sub(menus[1], derwin(windows[1], 6, 38, 3, 1));
  set_menu_mark(menus[1], " * ");
  wattrset(windows[1], COLOR_PAIR(BLUE_BLACK));
  mvwprintw(windows[1], 1, 0, "Color Scheme");
  mvwhline(windows[1], 2, 0, ACS_HLINE, 40);
  wnoutrefresh(windows[1]);
  post_menu(menus[1]);
  wnoutrefresh(windows[1]);

  menus[2] = new_menu((ITEM **)items3);
  windows[2] = newwin(10, 40, 26, 2);
  keypad(windows[2], TRUE);
  set_menu_win(menus[2], windows[2]);
  set_menu_sub(menus[2], derwin(windows[2], 6, 38, 3, 1));
  set_menu_mark(menus[2], " * ");
  wattrset(windows[2], COLOR_PAIR(BLUE_BLACK));
  mvwprintw(windows[2], 1, 0, "Window Size");
  mvwhline(windows[2], 2, 0, ACS_HLINE, 40);
  wnoutrefresh(windows[2]);
  post_menu(menus[2]);
  wnoutrefresh(windows[2]);

  panels[0] = new_panel(windows[1]);
  panels[1] = new_panel(windows[0]);
  panels[2] = new_panel(windows[2]);
  

  set_panel_userptr(panels[0], panels[1]);
  set_panel_userptr(panels[1], panels[2]);
  set_panel_userptr(panels[2], panels[0]);

  update_panels();
  */

  doupdate();

  //top = panels[2];
  while((c = getch()) != 'q'){
  /*
	  
    top = (PANEL *)panel_userptr(top);
    switch(c){
	    case 9:
		    top_panel(top);
		    break;
	    case KEY_DOWN:
		      menu_driver(menus[0], REQ_DOWN_ITEM);
		      wnoutrefresh(windows[0]);
		    break;
	    case KEY_UP:
		      menu_driver(menus[0], REQ_UP_ITEM);
		      wnoutrefresh(windows[0]);
		    break;
			    
    }	  

   update_panels();
    doupdate();
  */
  } 
  return;

}

void help_menu(WINDOW *win){
	
  char c;
  int i;
  i = 1;
  c = ' ';

  wclear(win);
  box(win, 0, 0);
  wCenterTitleTop(win, "Help Menu");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  mvwaddstr(win, i++, 2, "List of available commands in main window:");
  mvwaddstr(win, i++, 2, " ");
  mvwaddstr(win, i++, 2, "Key  Description");
  mvwaddstr(win, i++, 2, "-------------------------------------------");
  mvwaddstr(win, i++, 2, "0    Main configuration menu");
  mvwaddstr(win, i++, 2, "1    General window configuration menu");
  mvwaddstr(win, i++, 2, "2    Memory window configuration menu");
  mvwaddstr(win, i++, 2, "3    Load window configuration menu");
  mvwaddstr(win, i++, 2, "4    User window configuration menu");
  mvwaddstr(win, i++, 2, "5    Process window configuration menu");
  mvwaddstr(win, i++, 2, "6    Disk window configuration menu");
  mvwaddstr(win, i++, 2, "7    Network window configuration menu");
  mvwaddstr(win, i++, 2, "?    This menu");
  mvwaddstr(win, i++, 2, " ");
  mvwaddstr(win, i++, 2, "q    Closes any window");
  touchwin(win);
  wnoutrefresh(win);
  doupdate();
  while((c = getch()) != 'q'){
  } 
  return;

}

/*general menu*/
/*Contents:
 * - Domain name(so hostname will be FQDN)
 * -   
 */
void general_menu(WINDOW *win){
  char c;
  c = ' ';

  wclear(win);
  box(win, 0, 0);
  wCenterTitleTop(win, "Main Configuration");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  touchwin(win);
  wnoutrefresh(win);
  doupdate();
  while((c = getch()) != 'q'){
  } 
  return;


}

/*memory menu*/
/*Contents:
 * - Graph colors
 * -   
 */
void memory_menu(WINDOW *win){
  char c;
  c = ' ';

  wclear(win);
  box(win, 0, 0);
  wCenterTitleTop(win, "Memeory Configuration");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  touchwin(win);
  wnoutrefresh(win);
  doupdate();
  while((c = getch()) != 'q'){
  } 
  return;


}

/*load menu*/
/*Contents:
 * - Graph threshold values
 * - Graph threshold colors
 * -   
 */
void load_menu(WINDOW *win){
  char c;
  c = ' ';

  wclear(win);
  box(win, 0, 0);
  wCenterTitleTop(win, "Load Configuration");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  touchwin(win);
  wnoutrefresh(win);
  doupdate();
  while((c = getch()) != 'q'){
  } 
  return;


}

/*user menu*/
/*Contents:
 * - Show max users(changeable?)
 * - Sort method (alpha, anti-alpha, count)   
 * - Username filter???  
 */
void user_menu(WINDOW *win){
  char c;
  c = ' ';

  wclear(win);
  box(win, 0, 0);
  wCenterTitleTop(win, "User Configuration");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  touchwin(win);
  wnoutrefresh(win);
  doupdate();
  while((c = getch()) != 'q'){
  } 
  return;


}

/*proc menu*/
/*Contents:
 * - Sort method (alpha, anti-alpha, CPU, memory, time?)   
 * - Username filter???  
 * - pid/ppid filter???  
 */
void proc_menu(WINDOW *win){
  char c;
  c = ' ';

  wclear(win);
  box(win, 0, 0);
  wCenterTitleTop(win, "Proccess Configuration");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  touchwin(win);
  wnoutrefresh(win);
  doupdate();
  while((c = getch()) != 'q'){
  } 
  return;


}

/*disk menu*/
/*Contents:
 * - Show max disks(changeable?)
 * - Show max partitions(changeable?)
 * - Disk graph threshold values
 * - Disk graph threshold colors
 * - Partition graph colors
 * - Disk filter???  
 * - Partition filter???  
 * - 
 */
void disk_menu(WINDOW *win){
  char c;
  c = ' ';

  wclear(win);
  box(win, 0, 0);
  wCenterTitleTop(win, "Disk Configuration");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  touchwin(win);
  wnoutrefresh(win);
  doupdate();
  while((c = getch()) != 'q'){
  } 
  return;


}

/*network menu*/
/*Contents:
 * - Show max interfaces(changeable?)
 * - Net graph threshold values
 * - Net graph threshold colors
 */
void net_menu(WINDOW *win){
  char c;
  c = ' ';

  wclear(win);
  box(win, 0, 0);
  wCenterTitleTop(win, "Network Configuration");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  touchwin(win);
  wnoutrefresh(win);
  doupdate();
  while((c = getch()) != 'q'){
  } 
  return;


}
