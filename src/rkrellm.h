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

#ifndef _RTFM_H_
#define _RTFM_H_

/*Current version number*/
#define RTFM_VERSION "0.0.1alpha"

/*Default configuration file location*/
#ifndef RTFM_DEF_CONF
#define RTFM_DEF_CONF "~/.rkrellm" 
#endif

/*Directory where there linux acpi battery info lives*/
#ifndef RTFM_BATTERY_DIR 
#define RTFM_BATTERY_DIR "/proc/acpi/battery/CMB1"
#endif

/*Directory where there linux acpi ac_adaptor info lives*/
#ifndef RTFM_AC_ADAPTOR_DIR
#define RTFM_AC_ADAPTOR_DIR "/proc/acpi/ac_adapter/AC"
#endif

/*Default update times for each section */
/*
#ifndef RTFM_DEF_DISK
#define RTFM_DEF_DISK 60
#endif
#ifndef RTFM_DEF_GEN
#define RTFM_DEF_GEN 60
#endif
#ifndef RTFM_DEF_MEM
#define RTFM_DEF_MEM 60
#endif
#ifndef RTFM_DEF_NET
#define RTFM_DEF_NET 60
#endif
#ifndef RTFM_DEF_CPU
#define RTFM_DEF_CPU 60
#endif
#ifndef RTFM_DEF_RUN
#define RTFM_DEF_RUN 60
#endif
#ifndef RTFM_DEF_USER
#define RTFM_DEF_USER 60
#endif
*/

/*Which features are enabled(enabled = 1, diabled = 0)*/
#ifndef RTFM_OPT_DISK
#define RTFM_OPT_DISK 1
#endif
#ifndef RTFM_OPT_GEN
#define RTFM_OPT_GEN 1
#endif
#ifndef RTFM_OPT_MEM
#define RTFM_OPT_MEM 1
#endif
#ifndef RTFM_OPT_NET
#define RTFM_OPT_NET 1
#endif
#ifndef RTFM_OPT_CPU
#define RTFM_OPT_CPU 1
#endif
#ifndef RTFM_OPT_RUN
#define RTFM_OPT_RUN 1
#endif
#ifndef RTFM_OPT_USER
#define RTFM_OPT_USER 1
#endif
#ifndef RTFM_OPT_BATTERY
#define RTFM_OPT_BATTERY 1
#endif
#ifndef RTFM_OPT_ONCE
#define RTFM_OPT_ONCE 0
#endif
#ifndef RTFM_OPT_VER
#define RTFM_OPT_VER 0
#endif

#endif


