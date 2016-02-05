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

/* system includes */
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>

/* custom includes */
#include <rkrellmError.h>
#include <rkrellmDisplay.h>

int main(int argc, char **argv){
  
  char c;
  //int i;
  WINDOW *windows[WINDOW_COUNT];

  /*Option Flags*/
  int cflag, hflag, oflag, vflag, dflag, gflag, mflag, nflag, pflag, rflag, uflag; 
  int Dflag, Gflag, Mflag, Nflag, Pflag, Rflag, Vflag, Uflag;
  
  c = ' ';
  /*Declace windows to be used*/
  /*
  WINDOW *main_win; 	0 
  WINDOW *general_win;	1
  WINDOW *user_win;	2
  WINDOW *disk_win;	3
  WINDOW *mem_win; 	4
  WINDOW *load_win;	5
  WINDOW *net_win;	6
  WINDOW *proc_win;	7
  WINDOW *batt_win;	8
   */

  /*allocate memory more array of main windows and the menu window*/
  /*
  WINDOW **windows;
  windows = (WINDOW**)malloc(sizeof(WINDOW*) * WINDOW_COUNT);
  for(i = 0; i < WINDOW_COUNT; i++){
    windows[i] = (WINDOW*)malloc(sizeof(WINDOW));
  } 
  */
  WINDOW *menu_window;
  menu_window = NULL;

  /*Initialize option flags*/
  cflag = 0;
  hflag = 0;
  oflag = 0;
  vflag = 0;
  dflag = 0;
  gflag = 0;
  mflag = 0;
  nflag = 0;
  pflag = 0;
  rflag = 0;
  uflag = 0;
  Vflag = 0;
  Dflag = 0;
  Gflag = 0;
  Mflag = 0;
  Nflag = 0;
  Pflag = 0;
  Rflag = 0;
  Uflag = 0;


  /*Getopt is teh bestest*/
  while (( c = getopt( argc, argv, "cdghmnopruv")) != -1) {
    switch (c) {
      case 'c':
	cflag = 1;
	break;
      case 'd': 
	dflag = 1;
	break;
      case 'g':
	gflag = 1;
	break;
      case 'h':
	hflag = 1;
	break;
      case 'm':	
	mflag = 1;
	break;
      case 'n':	
	nflag = 1;
	break;
      case 'o':
	oflag = 1;
	break;
      case 'p':
	pflag = 1;
	break;
      case 'r':	
	rflag = 1;
	break;
      case 'u':
	uflag = 1;
	break;
      case 'v':
	vflag = 1;
	break;
      case '?':
	if (isprint(optopt)){
	  fprintf(stderr, "Unknown Option '-%c' \n", optopt);
	  rkrellmUsage();
	  exit(1);
	}
	else{
	  fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
	  rkrellmUsage();
	  exit(1);
	}
      default:
	rkrellmUsage();
	exit(1);
    }
  }

  if(hflag){
    rkrellmUsage();
    exit(0);
  }
  if(vflag){
    rkrellmVersion();
    exit(0);
  }

  /*Initial setup of the screen*/
  if(setup_screen(windows) != 0){
    exit(1);
  }

  /*Main loop, when c is matched the menu_screen funtion runs
   * then when that completes we setup the screen like new with 
   * setup_screen(), if no match, continue to update*/
  while((c = getch()) != 'q'){
    switch(c){
      case '?':  
	if(menu_screen(menu_window, c) != 0){
	  exit(1);
	}      
        if(setup_screen(windows) != 0){
          exit(1);
        }
	break;
      case '0':  
	if(menu_screen(menu_window, c) != 0){
	  exit(1);
	}      
        if(setup_screen(windows) != 0){
          exit(1);
        }
	break;
      case '1':  
	if(menu_screen(menu_window, c) != 0){
	  exit(1);
	}      
        if(setup_screen(windows) != 0){
          exit(1);
        }
	break;
      case '2':  
	if(menu_screen(menu_window, c) != 0){
	  exit(1);
	}      
        if(setup_screen(windows) != 0){
          exit(1);
        }
	break;
      case '3':  
	if(menu_screen(menu_window, c) != 0){
	  exit(1);
	}      
        if(setup_screen(windows) != 0){
          exit(1);
        }
	break;
      case '4':  
	if(menu_screen(menu_window, c) != 0){
	  exit(1);
	}      
        if(setup_screen(windows) != 0){
          exit(1);
        }
	break;
      case '5':  
	if(menu_screen(menu_window, c) != 0){
	  exit(1);
	}      
        if(setup_screen(windows) != 0){
          exit(1);
        }
	break;
      case '6':  
	if(menu_screen(menu_window, c) != 0){
	  exit(1);
	}      
        if(setup_screen(windows) != 0){
          exit(1);
        }
	break;
      default:
        if(update_screen(windows) != 0){
          exit(1);
        }
    }	  
  }

  /*retore the terminal to a usable stated*/
  endwin();

  /*clean up memory that we mallocked*/
  /*
  for(i = 0; i < WINDOW_COUNT; i++){
    free(windows[i]);
  } 
  */
  //free(windows);
  //free(menu_window);

  return 0;
}


