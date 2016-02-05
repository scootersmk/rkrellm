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

#include <statgrab.h>

/*initalizes statgrab*/
void initialize_statgrab();

/*retrieves general info about the system*/
sg_host_info *get_general_info();

/*retrieves current user info*/
sg_user_stats *get_user_info();

/*retrieves disk information,
 * takes an integer disk_count that will get the
 * number of disks*/
//sg_disk_io_stats *get_disk_info(int & disk_count);

/*retrieves memory info about the system*/
sg_mem_stats *get_mem_info();

/*retrieves swap info about the system*/
sg_swap_stats *get_swap_info();

/*retrieves load info about the system*/
sg_load_stats *get_load_info();

/*retrieves disk info about the system*/
sg_disk_io_stats *get_disk_info(int *num_disks);

/*retrieves filesystem info about the system*/
sg_fs_stats *get_fs_info(int *num_parts);

/*retreives network IO info about the system*/
sg_network_io_stats *get_net_info(int *num_interfaces);

/*retreives network interface info about the system*/
sg_network_iface_stats *get_net_interface_info(int *num_interfaces);

/*retreives general process info about the system*/
sg_process_count *get_process_count_info(void);

/*retreives detailed process info about the system*/
sg_process_stats *get_process_info(int *num_processes);

typedef struct{
  int battery_state; /*1 for present, 0 for not present*/
  int ac_state; /*1 for present, 0 for not present*/
  int charge_state; /* 1 for charging		
		      2 for discharging
		      -1 unknown state
		    */
  int capacity; /*design capacity*/
  int remaining_capacity; 
} sg_battery_stats;

/*retreives acpi battery info about the system(LINUX ONLY so far...)*/
sg_battery_stats *get_battery_info();
