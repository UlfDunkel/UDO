/*	############################################################
	# @(#) str.h
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
	# Typen
	############################################################	*/

/*	############################################################
	# Variablen
	############################################################	*/

/*	############################################################
	# Funktionen
	############################################################	*/

GLOBAL char *chrcat (char *dest, const char c);
GLOBAL char *strinsert ( char *string, const char *insert);

GLOBAL void replace_char ( char *string, const char *replace, const char *by );

GLOBAL int replace_once ( char *source, const char *replace, const char *by);
GLOBAL int replace_last ( char *source, const char *replace, const char *by);
GLOBAL int replace_all ( char *source, const char *replace, const char *by);

GLOBAL int qreplace_once ( char *source, const char *replace, const size_t rlen, const char *by, const size_t blen);
GLOBAL int qreplace_last ( char *source, const char *replace, const size_t rlen, const char *by, const size_t blen);
GLOBAL int qreplace_all ( char *source, const char *replace, const size_t rlen, const char *by, const size_t blen);

GLOBAL int delete_once ( char *source, const char *delete );
GLOBAL int delete_last ( char *source, const char *delete );
GLOBAL int delete_all ( char *source, const char *delete );

GLOBAL int qdelete_once ( char *source, const char *delete, const size_t dlen );
GLOBAL int qdelete_last ( char *source, const char *delete, const size_t dlen );
GLOBAL int qdelete_all ( char *source, const char *delete, const size_t dlen );


GLOBAL void del_right_spaces ( char *s );
GLOBAL void del_whitespaces ( char *s);

GLOBAL size_t get_brackets_ptr ( char *s, char **cont, char **data );
GLOBAL char *get_8bit_ptr ( char *s );
GLOBAL char *get_section_ptr ( char *s );
GLOBAL char *get_1stchar_ptr ( char *s );

GLOBAL void tabs2spaces (char *s, const int tw);
GLOBAL char *itoroman ( int value, char *string );
GLOBAL void my_strupr ( char *string );
GLOBAL void my_strlwr ( char *string );
GLOBAL int my_stricmp ( const char *s1, const char *s2 );

/*	############################################################
	# str.h
	############################################################	*/

