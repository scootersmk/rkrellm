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
 * PROGRAM WIDE SETTINGS
 * */
/*y-dim size of histo graphs*/
#define GRAPH_SIZE 10

/*number of elements in the windows array */
#define WINDOW_COUNT 8

/*Maximum scale of histo graphs*/
#define SCALE_MAX 10

/*Number of data points per each histo graph*/
#define DATA_COUNT 20

/*
 * GENERAL WINDOW 
 */
#define GENERAL_X_SIZE 47
#define GENERAL_Y_SIZE 9
#define GENERAL_X_POS 1
#define GENERAL_Y_POS 1

/*
 * CONFIG WINDOW
 * */
#define MENU_X_SIZE 70
#define MENU_Y_SIZE 50
#define MENU_X_POS 0
#define MENU_Y_POS 0


/*
 * MEMORY WINDOW
 */
#define MEM_X_SIZE 47
#define MEM_Y_SIZE 9
#define MEM_X_POS 48
#define MEM_Y_POS 1

#define MEM_TOTAL_GRAPH_X_SIZE 45
#define MEM_TOTAL_GRAPH_Y_SIZE 1
#define MEM_TOTAL_GRAPH_X_POS 49
#define MEM_TOTAL_GRAPH_Y_POS 8

#define MEM_MAIN_GRAPH_X_SIZE 45
#define MEM_MAIN_GRAPH_Y_SIZE 1
#define MEM_MAIN_GRAPH_X_POS 49
#define MEM_MAIN_GRAPH_Y_POS 4

#define MEM_SWAP_GRAPH_X_SIZE 45
#define MEM_SWAP_GRAPH_Y_SIZE 1
#define MEM_SWAP_GRAPH_X_POS 49
#define MEM_SWAP_GRAPH_Y_POS 6

/*
 * LOAD WINDOW
 */
#define LOAD_X_SIZE 74
#define LOAD_Y_SIZE 14
#define LOAD_X_POS 95
#define LOAD_Y_POS 1

#define LOAD1_GRAPH_X_SIZE 22
#define LOAD1_GRAPH_Y_SIZE 12
#define LOAD1_GRAPH_X_POS 98
#define LOAD1_GRAPH_Y_POS 2

#define LOAD5_GRAPH_X_SIZE 22
#define LOAD5_GRAPH_Y_SIZE 12
#define LOAD5_GRAPH_X_POS 122
#define LOAD5_GRAPH_Y_POS 2

#define LOAD15_GRAPH_X_SIZE 22
#define LOAD15_GRAPH_Y_SIZE 12
#define LOAD15_GRAPH_X_POS 146
#define LOAD15_GRAPH_Y_POS 2

/*Graph threshold ranges*/
#define LOAD_RANGE_LOW 0.25
#define LOAD_RANGE_MEDIUM 0.75
#define LOAD_RANGE_HIGH 1.0

/*
 * USER WINDOW
 */
#define USER_X_SIZE 18
#define USER_Y_SIZE 14
#define USER_X_POS 1
#define USER_Y_POS 10

/*
 * PROC WINDOW
 */
#define PROC_X_SIZE 76
#define PROC_Y_SIZE 14
#define PROC_X_POS 19
#define PROC_Y_POS 10

/*
 * DISK WINDOW
 */
/*Sizes without Battery Enabled*/
#define DISK_X_SIZE 74
#define DISK_Y_SIZE 40 
#define DISK_X_POS 95
#define DISK_Y_POS 15

/* Sizes with Battery Enabled*/
/*
#define DISK_X_SIZE 74
#define DISK_Y_SIZE 34 
#define DISK_X_POS 95
#define DISK_Y_POS 15
*/

#define DISK1_GRAPH_X_SIZE 22
#define DISK1_GRAPH_Y_SIZE 12
#define DISK1_GRAPH_X_POS 98
#define DISK1_GRAPH_Y_POS 16

#define DISK2_GRAPH_X_SIZE 22
#define DISK2_GRAPH_Y_SIZE 12
#define DISK2_GRAPH_X_POS 122
#define DISK2_GRAPH_Y_POS 16

#define DISK_TOTAL_GRAPH_X_SIZE 22
#define DISK_TOTAL_GRAPH_Y_SIZE 12
#define DISK_TOTAL_GRAPH_X_POS 146
#define DISK_TOTAL_GRAPH_Y_POS 16

#define PART_GRAPH_X_SIZE 72
#define PART_GRAPH_Y_SIZE 1
#define PART_GRAPH_X_POS 96
#define PART_GRAPH_Y_POS 32

#define DISK_RANGE_LOW 0.25
#define DISK_RANGE_MEDIUM 0.75
#define DISK_RANGE_HIGH 1.0

#define PART_MAX_COUNT 8 
#define PART_DEV_LENGTH 20
#define PART_MNT_LENGTH 18
#define PART_TYPE_LENGTH 8
#define PART_SIZE_LENGTH 5
#define PART_AVAIL_LENGTH 5
#define PART_USED_LENGTH 5

/*
 * NET WINDOW
 */
#define NET_X_SIZE 94
#define NET_Y_SIZE 31
#define NET_X_POS 1
#define NET_Y_POS 24

#define NET1_IN_GRAPH_X_SIZE 22
#define NET1_IN_GRAPH_Y_SIZE 12
#define NET1_IN_GRAPH_X_POS 3
#define NET1_IN_GRAPH_Y_POS 25

#define NET1_OUT_GRAPH_X_SIZE 22
#define NET1_OUT_GRAPH_Y_SIZE 12
#define NET1_OUT_GRAPH_X_POS 25
#define NET1_OUT_GRAPH_Y_POS 25

#define NET2_IN_GRAPH_X_SIZE 22
#define NET2_IN_GRAPH_Y_SIZE 12
#define NET2_IN_GRAPH_X_POS 49
#define NET2_IN_GRAPH_Y_POS 25

#define NET2_OUT_GRAPH_X_SIZE 22
#define NET2_OUT_GRAPH_Y_SIZE 12
#define NET2_OUT_GRAPH_X_POS 71
#define NET2_OUT_GRAPH_Y_POS 25

#define NET3_IN_GRAPH_X_SIZE 22
#define NET3_IN_GRAPH_Y_SIZE 12
#define NET3_IN_GRAPH_X_POS 3
#define NET3_IN_GRAPH_Y_POS 42

#define NET3_OUT_GRAPH_X_SIZE 22
#define NET3_OUT_GRAPH_Y_SIZE 12
#define NET3_OUT_GRAPH_X_POS 25
#define NET3_OUT_GRAPH_Y_POS 42

#define NET_TOTAL_IN_GRAPH_X_SIZE 22
#define NET_TOTAL_IN_GRAPH_Y_SIZE 12
#define NET_TOTAL_IN_GRAPH_X_POS 49
#define NET_TOTAL_IN_GRAPH_Y_POS 42

#define NET_TOTAL_OUT_GRAPH_X_SIZE 22
#define NET_TOTAL_OUT_GRAPH_Y_SIZE 12
#define NET_TOTAL_OUT_GRAPH_X_POS 71
#define NET_TOTAL_OUT_GRAPH_Y_POS 42

#define NET_RANGE_LOW 0.25
#define NET_RANGE_MEDIUM 0.75
#define NET_RANGE_HIGH 1.0

/*
 * BATTERY WINDOW
 */
#define BATTERY_X_SIZE 74
#define BATTERY_Y_SIZE 6 
#define BATTERY_X_POS 95
#define BATTERY_Y_POS 49

#define BATTERY_GRAPH_X_SIZE 72 
#define BATTERY_GRAPH_Y_SIZE 4 
#define BATTERY_GRAPH_X_POS 96
#define BATTERY_GRAPH_Y_POS 50

