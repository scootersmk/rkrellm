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
#include <rkrellm.h>
#include <rkrellmError.h>

/* Prints the usage info to stderr */
void rkrellmUsage(){

  fprintf(stderr, "usage: rkrellm [options]\n");	
  fprintf(stderr, "options:\n");	
  /*
  fprintf(stderr, "\t-c file\tspecify the configuration file to use(default: %s)\n", RTFM_DEF_CONF);	
  if(RTFM_OPT_DISK){
    fprintf(stderr, "\t-d n\tspecify time(in seconds) between disk info updates(default: %d)\n", RTFM_DEF_DISK);	
  }
  if(RTFM_OPT_GEN){
    fprintf(stderr, "\t-g n\tspecify time(in seconds) between generl info updates(default: %d)\n", RTFM_DEF_GEN);	
  }
  */
  fprintf(stderr, "\t-h\tprint this help message\n");	
  /*
  if(RTFM_OPT_MEM){
    fprintf(stderr, "\t-m n\tspecify time(in seconds) between memory info updates(default: %d)\n", RTFM_DEF_MEM);	
  }
  if(RTFM_OPT_NET){
    fprintf(stderr, "\t-n n\tspecify time(in seconds) between network info updates(default: %d)\n", RTFM_DEF_NET);	
  }
  if(RTFM_OPT_ONCE){
    fprintf(stderr, "\t-o\tonly run get info once(no updates)\n");	
  }
  if(RTFM_OPT_CPU){
    fprintf(stderr, "\t-p n\tspecify time(in seconds) between processor info updates(default: %d)\n", RTFM_DEF_CPU);	
  }
  if(RTFM_OPT_RUN){
    fprintf(stderr, "\t-r n\tspecify time(in seconds) between running process info updates(default: %d)\n", RTFM_DEF_RUN);	
  }
  if(RTFM_OPT_USER){
    fprintf(stderr, "\t-u n\tspecify time(in seconds) between user info updates(default: %d)\n", RTFM_DEF_USER);	
  }
  */
  fprintf(stderr, "\t-v\tprint the version number and exit\n");	
  /*
  if(RTFM_OPT_DISK){
    fprintf(stderr, "\t-D\tonly display disk info\n");	
  }
  if(RTFM_OPT_GEN){
    fprintf(stderr, "\t-G\tonly display general info\n");	
  }
  if(RTFM_OPT_MEM){
    fprintf(stderr, "\t-M\tonly display memory info\n");	
  }
  if(RTFM_OPT_NET){
    fprintf(stderr, "\t-N\tonly display network info\n");	
  }
  if(RTFM_OPT_CPU){
    fprintf(stderr, "\t-P\tonly display processor info\n");	
  }
  if(RTFM_OPT_RUN){
    fprintf(stderr, "\t-R\tonly display running process info\n");	
  }
  if(RTFM_OPT_USER){
    fprintf(stderr, "\t-U\tonly display user info\n\n");	
  }
  if(RTFM_OPT_VER){
    fprintf(stderr, "\t-V\textremely verbose(debug info) printed to stderr\n\n");	
  }
  */
	
  rkrellmVersion();

  return;
}

/* Prints out the version information */
void rkrellmVersion(){

  fprintf(stderr, "rkrellm version %s\n", RTFM_VERSION);
  fprintf(stderr, "Written by Scott M. Koch\n\n");
  fprintf(stderr, "This is free software; see the source for copying conditions.  There is NO\n");
  fprintf(stderr, "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
  
  return;
}


						
