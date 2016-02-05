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

#include <rkrellmStats.h>
#include <rkrellmDisplay.h>

void graph_disk(WINDOW *win){
 
  sg_disk_io_stats *disks;	
  sg_fs_stats *fs;	

  char disk_str[80], disk_per_str[10];
  int disk_count, part_count;
  long long total_read_bytes, total_write_bytes;
  int maxy, maxx;
  int i, disk_index;
  WINDOW *disk1_win, *disk2_win, *disk_total_win;
  WINDOW *part_win[PART_MAX_COUNT];
  char disk_head_str[20];
  double disk_percent;
  double disk_ranges[3];
  long long part_size, part_used, part_avail;
  char part_size_ch, part_used_ch, part_avail_ch;
  long long read_bytes, write_bytes;
  char read_bytes_ch, write_bytes_ch;

  disk_ranges[0] = DISK_RANGE_LOW;
  disk_ranges[1] = DISK_RANGE_MEDIUM;
  disk_ranges[2] = DISK_RANGE_HIGH;

  total_read_bytes = 0;
  total_write_bytes = 0;
  disk_index = 0;
  
  for(i = 0 ; i < 19; i++ ){
    disk1_vals[i] = disk1_vals[i+1]; 
    disk2_vals[i] = disk2_vals[i+1]; 
    disk_total_vals[i] = disk_total_vals[i+1]; 
  }
  
  disks = get_disk_info(&disk_count);
  fs = get_fs_info(&part_count);

  /*no reason to do this twice*/
  if(!screen_init){
    disks = get_disk_info(&disk_count);
    wclear(win);
    box(win, 0, 0);
  }
  wCenterTitleTop(win, "Disk Info");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  getmaxyx(win, maxy, maxx);

  disk1_vals[19] = disks->read_bytes + disks->write_bytes;

  read_bytes = disks->read_bytes;
  write_bytes = disks->write_bytes;

  format_int_size(&read_bytes, &read_bytes_ch, 4);
  format_int_size(&write_bytes, &write_bytes_ch, 4);
  
  sprintf(disk_head_str, "%s:%4lld%c/%4lld%c", 
		  disks->disk_name, 
		  read_bytes, 
		  read_bytes_ch, 
		  write_bytes,
		  write_bytes_ch);
  total_read_bytes += disks->read_bytes;
  total_write_bytes += disks->write_bytes;


  /* Create the disk1 graph window*/
  disk1_win = subwin(win, DISK1_GRAPH_Y_SIZE, DISK1_GRAPH_X_SIZE, DISK1_GRAPH_Y_POS, DISK1_GRAPH_X_POS);
  wattrset(disk1_win, COLOR_PAIR(BLUE_BLACK));
  histo_graph(disk1_win, disk_head_str, disk1_vals, disk_ranges);
  touchwin(disk1_win);
  wnoutrefresh(disk1_win);

  disks++;
  
  disk2_vals[19] = disks->read_bytes + disks->write_bytes;

  read_bytes = disks->read_bytes;
  write_bytes = disks->write_bytes;

  format_int_size(&read_bytes, &read_bytes_ch, 4);
  format_int_size(&write_bytes, &write_bytes_ch, 4);

  sprintf(disk_head_str, "%s:%4lld%c/%4lld%c", 
		  disks->disk_name, 
		  read_bytes, 
		  read_bytes_ch, 
		  write_bytes,
		  write_bytes_ch);
  total_read_bytes += disks->read_bytes;
  total_write_bytes += disks->write_bytes;

  /* Create the disk2 graph window*/
  disk2_win = subwin(win, DISK2_GRAPH_Y_SIZE, DISK2_GRAPH_X_SIZE, DISK2_GRAPH_Y_POS, DISK2_GRAPH_X_POS);
  wattrset(disk2_win, COLOR_PAIR(BLUE_BLACK));
  histo_graph(disk2_win, disk_head_str, disk2_vals, disk_ranges);
  touchwin(disk2_win);
  wnoutrefresh(disk2_win);

  disk_total_vals[19] = total_read_bytes + total_write_bytes;
  
  read_bytes = total_read_bytes;
  write_bytes = total_write_bytes;

  format_int_size(&read_bytes, &read_bytes_ch, 4);
  format_int_size(&write_bytes, &write_bytes_ch, 4);
  
  sprintf(disk_head_str, "Total:%4lld%c/%4lld%c", 
		  read_bytes, 
		  read_bytes_ch, 
		  write_bytes,
		  write_bytes_ch);

  /* Create the disk_total graph window*/
  disk_total_win = subwin(win, DISK_TOTAL_GRAPH_Y_SIZE, DISK_TOTAL_GRAPH_X_SIZE, DISK_TOTAL_GRAPH_Y_POS, DISK_TOTAL_GRAPH_X_POS);
  wattrset(disk_total_win, COLOR_PAIR(BLUE_BLACK));
  histo_graph(disk_total_win, disk_head_str, disk_total_vals, disk_ranges);
  touchwin(disk_total_win);
  wnoutrefresh(disk_total_win);

  /*partition detials*/
  mvwaddstr(win, 14, 1, "Dev Name              Type      Mnt Point         Size    Used   Avail ");
  mvwhline(win, 15, 1, 0, 72);

  for(i = 0; i < PART_MAX_COUNT && i < part_count; i++){

    part_size = fs->size;
    part_used = fs->used;
    part_avail = fs->avail;

    format_int_size(&part_size, &part_size_ch, 5);
    format_int_size(&part_used, &part_used_ch, 5);
    format_int_size(&part_avail, &part_avail_ch, 5);

    sprintf(disk_str, "%-20s  %-8s  %-8s        %5lld%c  %5lld%c  %5lld%c", 
		    fs->device_name,
                    fs->fs_type, 
		    fs->mnt_point, 
		    part_size,
		    part_size_ch,
		    part_used,
		    part_used_ch,
		    part_avail,
		    part_avail_ch);
    mvwaddstr(win, (disk_index*3)+16, 1, disk_str);
    disk_percent = 100 * ((float)fs->used/(float)fs->size);
    sprintf(disk_per_str, "%5.2f%%", disk_percent);
    part_win[i] = subwin(win, PART_GRAPH_Y_SIZE, PART_GRAPH_X_SIZE, PART_GRAPH_Y_POS + (i * 3), PART_GRAPH_X_POS);
    wattrset(part_win[i], COLOR_PAIR(BLUE_BLACK));
    percent_graph(part_win[i], disk_percent, disk_per_str);
    touchwin(part_win[i]);
    wnoutrefresh(part_win[i]);
    fs++;
    disk_index++;
  }

  touchwin(win);
  wnoutrefresh(win);

  return;
}
