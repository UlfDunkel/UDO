/*	############################################################
	# @(#) tab.h
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
	############################################################	*/

/*	############################################################
	# globale Variablen
	############################################################	*/

/*	############################################################
	# globale Funktionen
	############################################################	*/
GLOBAL void table_reset ( void );
GLOBAL void c_table_caption ( void );
GLOBAL void c_table_caption_nonr ( void );
GLOBAL void table_get_header ( char *s );

GLOBAL BOOLEAN table_add_line ( char *s );
GLOBAL void table_output ( void );

GLOBAL void set_table_counter ( const int i );

GLOBAL void set_table_alignment ( void );

GLOBAL void init_module_tab ( void );

/*	############################################################
	# tab.h
	############################################################	*/

