/*	######################################################################
	# @(#) gui.h
	# @(#)
	# @(#) Copyright (c) 1995-2001 by Dirk Hagedorn
	# @(#) Dirk Hagedorn (udo@dirk-hagedorn.de)
	#
	# This program is free software; you can redistribute it and/or
	# modify it under the terms of the GNU General Public License
	# as published by the Free Software Foundation; either version 2
	# of the License, or (at your option) any later version.
	# 
	# This program is distributed in the hope that it will be useful,
	# but WITHOUT ANY WARRANTY; without even the implied warranty of
	# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	# GNU General Public License for more details.
	# 
	# You should have received a copy of the GNU General Public License
	# along with this program; if not, write to the Free Software
	# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
	# 
	# @(#) Diese Routinen muessen vom GUI zur Verfuegung gestellt werden
	######################################################################	*/

/*	######################################################################
	# Variablen
	######################################################################	*/
GLOBAL BOOLEAN no_stderr_output;


/*	######################################################################
	# Funktionen
	######################################################################	*/

GLOBAL void show_status_info ( const char *s);
GLOBAL void show_status_loginfo ( const char *s);
GLOBAL void show_status_node ( const char *s );
GLOBAL void show_status_file_1 ( const char *s );
GLOBAL void show_status_file_2 ( const char *s );
GLOBAL void show_status_percent ( const int percent );
GLOBAL void show_status_pass ( const char *s );
GLOBAL void show_status_udo2udo ( const char *s );
GLOBAL void show_status_errors ( void );

GLOBAL void show_logln_message ( const char *s );

GLOBAL void warning_err_logfile ( void );
GLOBAL void warning_err_treefile ( void );
GLOBAL void warning_err_uprfile ( void );
GLOBAL void warning_err_hypfile ( void );
GLOBAL void warning_err_idxfile ( void );
GLOBAL void warning_err_destination ( void );
GLOBAL void multitasking_interrupt ( void );
GLOBAL void unregistered_copyright ( void );
GLOBAL void cursor_working ( void );
GLOBAL void cursor_active ( void );
GLOBAL BOOLEAN break_action ( void );


/*	######################################################################
	# gui.h
	######################################################################	*/
