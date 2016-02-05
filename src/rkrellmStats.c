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
#include <rkrellmStats.h>

/*initalizes statgrab*/
void initialize_statgrab(){

  /* Initialise statgrab */
  sg_init();

  /* Drop setuid/setgid privileges. */
  if (sg_drop_privileges() != 0) {
    fprintf(stderr,"Error. Failed to drop privileges");
    exit(1);
  }

  return;
}

/*retrieves general info about the system*/
sg_host_info *get_general_info(){

  sg_host_info *general_stats;

  general_stats = sg_get_host_info();

  if(general_stats == NULL){
    fprintf(stderr, "Failed to get os stats\n");
    exit(1);
  }

  return general_stats;
}

sg_user_stats *get_user_info(){
  sg_user_stats *users;

  users = sg_get_user_stats();

  if( users == NULL ){
    fprintf(stderr, "Failed to get user stats\n");	  
    exit(1);
  }

  return users;
}

sg_mem_stats *get_mem_info(){

  sg_mem_stats *memory;
  
  memory = sg_get_mem_stats();

  if( memory == NULL ){
    fprintf(stderr, "Failed to get memory stats\n");	  
    exit(1);
  }

  return memory;  
}

sg_swap_stats *get_swap_info(){

  sg_swap_stats *swap;

  swap = sg_get_swap_stats();

  if( swap == NULL ){
    fprintf(stderr, "Failed to get swap stats\n");	  
    exit(1);
  }

  return swap;  
 
}

sg_load_stats *get_load_info(){
  sg_load_stats *load;

  load = sg_get_load_stats();
  if(load == NULL){
    fprintf(stderr, "Failed to get load stats\n");	  
    exit(1);
  }

  return load;

}

sg_disk_io_stats *get_disk_info(int *num_disks){

  sg_disk_io_stats *disk;
  
  disk = sg_get_disk_io_stats_diff(num_disks);
  if(disk == NULL){
    fprintf(stderr, "Failed to get disk stats\n");	  
    exit(1);
  }

  return disk;
}

sg_fs_stats *get_fs_info(int *num_parts){

  sg_fs_stats *fs;

  fs = sg_get_fs_stats(num_parts);
  if(fs == NULL){
    fprintf(stderr, "Failed to get fs stats\n");	  
    exit(1);
  }

  return fs;
}

/*retreives network IO info about the system*/
sg_network_io_stats *get_net_info(int *num_interfaces){

  sg_network_io_stats *net;

  net = sg_get_network_io_stats_diff(num_interfaces);
  if(net == NULL){
    fprintf(stderr, "Failed to get net information\n"); 
    exit(1);
  }

  return net;
}

/*retreives network interface info about the system*/
sg_network_iface_stats *get_net_interface_info(int *num_interfaces){

  sg_network_iface_stats *net_if;

  net_if = sg_get_network_iface_stats(num_interfaces);
  if(net_if == NULL){
    fprintf(stderr, "Failed to get net_if information\n"); 
    exit(1);
  }

  return net_if;
}

/*retreives general process info about the system*/
sg_process_count *get_process_count_info(void){
  
  sg_process_count *process_count;
  
  process_count = sg_get_process_count();
  if(process_count == NULL){
    fprintf(stderr, "Failed to get process count information\n"); 
    exit(1);
  }

  return process_count;  
}

/*retreives detailed process info about the system*/
sg_process_stats *get_process_info(int *num_processes){
  
  sg_process_stats *process_stats;
  
  process_stats = sg_get_process_stats(num_processes);
  if(process_stats == NULL){
    fprintf(stderr, "Failed to get process stat information\n"); 
    exit(1);
  }

  return process_stats;  
}

/*retreives acpi battery info about the system(LINUX ONLY so far...)*/
sg_battery_stats *get_battery_info(){
  char battery_info_file[50];
  char battery_state_file[50];
  char ac_adaptor_state_file[50];
  char *buf, str[128];
  FILE *fp;
  sg_battery_stats *battery_stats;

  battery_stats = (sg_battery_stats*)malloc(sizeof(sg_battery_stats));

  buf = (char*)malloc(sizeof(char)*128);

  sprintf(battery_info_file, "%s/info", RTFM_BATTERY_DIR);
  sprintf(battery_state_file, "%s/state", RTFM_BATTERY_DIR);
  sprintf(ac_adaptor_state_file, "%s/state", RTFM_AC_ADAPTOR_DIR);

  if((fp = fopen(battery_state_file, "r")) == NULL){
    fprintf(stderr, "error opening file: %s\n", battery_state_file);
    exit(1);
  }
  while((buf = fgets(buf, 128, fp)) != NULL){
    if(sscanf(buf, "present: %s", str) == 1){
      if(strcmp(str, "yes") == 0){
        battery_stats->battery_state = 1;
      }
      else{
        battery_stats->battery_state = 0;
      }
      continue;
    }
    if(sscanf(buf, "charging state: %s", str) == 1){
      if(strcmp(str, "charging") == 0){
	battery_stats->charge_state = 1;
      }
      if(strcmp(str, "discharging") == 0){
	battery_stats->charge_state = 2;
      }
      if(strcmp(str, "unknown") == 0){
	battery_stats->charge_state = -1;
      }
      continue;
    }
    if(sscanf(buf, "remaining capacity: %d", 
			    &battery_stats->remaining_capacity) == 1){
      continue;
    }
  }
  fclose(fp);
  
  free(buf);
  buf = (char*)malloc(sizeof(char)*128);
  
  if((fp = fopen(battery_info_file, "r")) == NULL){
    fprintf(stderr, "error opening file: %s\n", battery_info_file);
    exit(1);
  }
  while((buf = fgets(buf, 128, fp)) != NULL){
    if(sscanf(buf, "design capacity: %d", &battery_stats->capacity) == 1){
      continue;
    }
  }
  fclose(fp);
  
  free(buf);
  buf = (char*)malloc(sizeof(char)*128);
  
  if((fp = fopen(ac_adaptor_state_file, "r")) == NULL){
    fprintf(stderr, "error opening file: %s\n", ac_adaptor_state_file);
    exit(1);
  }
  while((buf = fgets(buf, 128, fp)) != NULL){
    if(sscanf(buf, "state: %s", str) == 1){
      if(strcmp(str, "on-line") == 0){
	battery_stats->ac_state = 1;
      }
      else{
	battery_stats->ac_state = 0;
      }
      continue;
    }
  }
  fclose(fp);
  free(buf);

  return battery_stats;
}
