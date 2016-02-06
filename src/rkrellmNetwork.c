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

						
void graph_net(WINDOW *win){

  int i;
  int maxy, maxx, interfaces, interfaces1;
  WINDOW *net_in_win[3], *net_out_win[3];
  WINDOW *net_total_in_win, *net_total_out_win;
  char net1_str[90], net_total_str[90];
  sg_network_io_stats *net;
  sg_network_iface_stats *net_if;
  long long tx_total, rx_total;
  long long ipackets_total, opackets_total;
  long long ierrors_total, oerrors_total;
  long long  collisions_total;
  double net_ranges[3];

  long long tx, rx, ipackets, opackets, ierrors, oerrors, collisions;
  char tx_ch, rx_ch, ipackets_ch, opackets_ch, ierrors_ch, oerrors_ch, collisions_ch;

  net_ranges[0] = NET_RANGE_LOW;
  net_ranges[1] = NET_RANGE_MEDIUM;
  net_ranges[2] = NET_RANGE_HIGH;

  tx_total = 0;
  rx_total = 0;
  ipackets_total = 0;
  opackets_total = 0;
  ierrors_total = 0;
  oerrors_total = 0;
  collisions_total = 0;

  for(i = 0 ; i < 19; i++ ){
    net1_in_vals[i] = net1_in_vals[i+1]; 
    net1_out_vals[i] = net1_out_vals[i+1]; 
    net2_in_vals[i] = net2_in_vals[i+1]; 
    net2_out_vals[i] = net2_out_vals[i+1]; 
    net3_in_vals[i] = net3_in_vals[i+1]; 
    net3_out_vals[i] = net3_out_vals[i+1]; 
    net_total_in_vals[i] = net_total_in_vals[i+1]; 
    net_total_out_vals[i] = net_total_out_vals[i+1]; 
  }
  
  //The first call is pointless
  net = get_net_info(&interfaces);
  net_if = get_net_interface_info(&interfaces1);

  /*no reason to do this twice*/
  if(!screen_init){
    net = get_net_info(&interfaces);
    wclear(win);
    box(win, 0, 0);
  }
  wCenterTitleTop(win, "Network Info");
  wattrset(win, COLOR_PAIR(YELLOW_BLACK));
  getmaxyx(win, maxy, maxx);

  mvwaddstr(win, 13,1, "Int         tx/rx          pckts.(in/out)      errs.    colls.    speed  dupl.  up");
  
  for(i = 0; i < 3 && i < interfaces1 ; i++){

    switch(i){
      case 0:
        net1_in_vals[19] = net->rx; 
        net1_out_vals[19] = net->tx;

        /* Create the net1 in graph window*/
        net_in_win[0] = subwin(win, NET1_IN_GRAPH_Y_SIZE, NET1_IN_GRAPH_X_SIZE, NET1_IN_GRAPH_Y_POS, NET1_IN_GRAPH_X_POS);
        wattrset(net_in_win[0], COLOR_PAIR(BLUE_BLACK));
        histo_graph(net_in_win[0], net->interface_name, net1_in_vals, net_ranges);
        touchwin(net_in_win[0]);
        wnoutrefresh(net_in_win[0]);
  
        /* Create the net1 out graph window*/
        net_out_win[0] = subwin(win, NET1_OUT_GRAPH_Y_SIZE, NET1_OUT_GRAPH_X_SIZE, NET1_OUT_GRAPH_Y_POS, NET1_OUT_GRAPH_X_POS);
        wattrset(net_out_win[0], COLOR_PAIR(BLUE_BLACK));
        histo_graph(net_out_win[0], net->interface_name, net1_out_vals, net_ranges);
        touchwin(net_out_win[0]);
        wnoutrefresh(net_out_win[0]);

	break;

      case 1:
        net2_in_vals[19] = net->rx; 
        net2_out_vals[19] = net->tx;

        /* Create the net2 in graph window*/
        net_in_win[1] = subwin(win, NET2_IN_GRAPH_Y_SIZE, NET2_IN_GRAPH_X_SIZE, NET2_IN_GRAPH_Y_POS, NET2_IN_GRAPH_X_POS);
        wattrset(net_in_win[1], COLOR_PAIR(BLUE_BLACK));
        histo_graph(net_in_win[1], net->interface_name, net2_in_vals, net_ranges);
        touchwin(net_in_win[1]);
        wnoutrefresh(net_in_win[1]);
  
        /* Create the net2 out graph window*/
        net_out_win[1] = subwin(win, NET2_OUT_GRAPH_Y_SIZE, NET2_OUT_GRAPH_X_SIZE, NET2_OUT_GRAPH_Y_POS, NET2_OUT_GRAPH_X_POS);
        wattrset(net_out_win[1], COLOR_PAIR(BLUE_BLACK));
        histo_graph(net_out_win[1], net->interface_name, net2_out_vals, net_ranges);
        touchwin(net_out_win[1]);
        wnoutrefresh(net_out_win[1]);

	break;

      case 2:
        net3_in_vals[19] = net->rx;
        net3_out_vals[19] = net->tx;

        /* Create the net3 in graph window*/
        net_in_win[2] = subwin(win, NET3_IN_GRAPH_Y_SIZE, NET3_IN_GRAPH_X_SIZE, NET3_IN_GRAPH_Y_POS, NET3_IN_GRAPH_X_POS);
        wattrset(net_in_win[2], COLOR_PAIR(BLUE_BLACK));
        histo_graph(net_in_win[2], net->interface_name, net3_in_vals, net_ranges);
        touchwin(net_in_win[2]);
        wnoutrefresh(net_in_win[2]);
  
        /* Create the net3 out graph window*/
        net_out_win[2] = subwin(win, NET3_OUT_GRAPH_Y_SIZE, NET3_OUT_GRAPH_X_SIZE, NET3_OUT_GRAPH_Y_POS, NET3_OUT_GRAPH_X_POS);
        wattrset(net_out_win[2], COLOR_PAIR(BLUE_BLACK));
        histo_graph(net_out_win[2], net->interface_name, net3_out_vals, net_ranges);
        touchwin(net_out_win[2]);
        wnoutrefresh(net_out_win[2]);
  
	break;
    }	  
   
    tx = net->tx; 
    rx = net->rx;
    ipackets = net->ipackets; 
    opackets = net->opackets;
    ierrors = net->ierrors;
    oerrors = net->oerrors;
    collisions = net->collisions;

    format_int_size(&tx, &tx_ch, 6);
    format_int_size(&rx, &rx_ch, 6);
    format_int_count(&ipackets, &ipackets_ch, 6);
    format_int_count(&opackets, &opackets_ch, 6);
    format_int_count(&ierrors, &ierrors_ch, 3);
    format_int_count(&oerrors, &oerrors_ch, 3);
    format_int_count(&collisions, &collisions_ch, 3);
  
    snprintf(net1_str, sizeof(net1_str), "%s\t%6lld%c/%6lld%c   %6lld%c/%6lld%c    %3lld%c/%3lld%c     %3lld%c     %3d      ", 
		  net->interface_name, 
		  tx, 
		  tx_ch, 
		  rx,
		  rx_ch,
		  ipackets, 
		  ipackets_ch, 
		  opackets,
		  opackets_ch,
		  ierrors, 
		  ierrors_ch, 
		  oerrors,
		  oerrors_ch,
		  collisions,
		  collisions_ch,
		  net_if->speed);
    mvwaddstr(win,14+i,1, net1_str);

    tx_total += net->tx;
    rx_total += net->rx;
    ipackets_total += net->ipackets;
    opackets_total += net->opackets;
    ierrors_total += net->ierrors;
    oerrors_total += net->oerrors;
    collisions_total += net->collisions;
  
  
    net++;
    net_if++;
  
  }
  net_total_in_vals[19] = rx_total;
  net_total_out_vals[19] = tx_total;
  
  /* Create the net3 in graph window*/
  net_total_in_win = subwin(win, NET_TOTAL_IN_GRAPH_Y_SIZE, NET_TOTAL_IN_GRAPH_X_SIZE, NET_TOTAL_IN_GRAPH_Y_POS, NET_TOTAL_IN_GRAPH_X_POS);
  wattrset(net_total_in_win, COLOR_PAIR(BLUE_BLACK));
  histo_graph(net_total_in_win, "Total - in" , net_total_in_vals, net_ranges);
  touchwin(net_total_in_win);
  wnoutrefresh(net_total_in_win);
  
  /* Create the net3 out graph window*/
  net_total_out_win = subwin(win, NET_TOTAL_OUT_GRAPH_Y_SIZE, NET_TOTAL_OUT_GRAPH_X_SIZE, NET_TOTAL_OUT_GRAPH_Y_POS, NET_TOTAL_OUT_GRAPH_X_POS);
  wattrset(net_total_out_win, COLOR_PAIR(BLUE_BLACK));
  histo_graph(net_total_out_win, "Total - out", net_total_out_vals, net_ranges);
  touchwin(net_total_out_win);
  wnoutrefresh(net_total_out_win);
  
  tx = tx_total; 
  rx = rx_total;
  ipackets = ipackets_total; 
  opackets = opackets_total;
  ierrors = ierrors_total;
  oerrors = oerrors_total;
  collisions = collisions_total;

  format_int_size(&tx, &tx_ch, 6);
  format_int_size(&rx, &rx_ch, 6);
  format_int_count(&ipackets, &ipackets_ch, 6);
  format_int_count(&opackets, &opackets_ch, 6);
  format_int_count(&ierrors, &ierrors_ch, 3);
  format_int_count(&oerrors, &oerrors_ch, 3);
  format_int_count(&collisions, &collisions_ch, 3);
  
  snprintf(net_total_str, sizeof(net_total_str), "Total\t%6lld%c/%6lld%c   %6lld%c/%6lld%c    %3lld%c/%3lld%c     %3lld%c      ", 
		  tx, 
		  tx_ch, 
		  rx,
		  rx_ch,
		  ipackets, 
		  ipackets_ch, 
		  opackets,
		  opackets_ch,
		  ierrors, 
		  ierrors_ch, 
		  oerrors,
		  oerrors_ch,
		  collisions,
		  collisions_ch);
  mvwaddstr(win,17,1, net_total_str);

  return;
}
