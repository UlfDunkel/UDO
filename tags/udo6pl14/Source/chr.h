/*	############################################################
	# @(#) chr.h
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

#ifndef __UDOCHR__
#define	__UDOCHR__

#define	TTF_REGULAR	0
#define	TTF_BOLD	1
#define	TTF_ITALIC	2

#define	TTF_ARIAL	0
#define	TTF_TIMES	1
#define	TTF_COURIER	2

#define	TTF_10PT	0
#define	TTF_11PT	1

#endif	/* __UDOCHR__ */


/*	############################################################
	# Variablen
	############################################################	*/


/*	############################################################
	# Funktionen
	############################################################	*/
GLOBAL void convert_sz ( char *s );

GLOBAL void recode ( char *zeile, int char_set );

GLOBAL void uni2ascii ( char *s );

GLOBAL void win2sys ( char *s );
GLOBAL void html2sys ( char *s );
GLOBAL void ansi2dos ( char *s );
GLOBAL int calc_ttf_twip ( const char *s, const int font, const int style );

GLOBAL void replace_udo_quotes ( char *s );
GLOBAL void replace_all_copyright (char *s);

GLOBAL void delete_all_divis (char *s);

GLOBAL void indent2space ( char * s);
GLOBAL void space2indent ( char * s);
GLOBAL void nbsp2space ( char * s);
GLOBAL void space2nbsp ( char * s);

GLOBAL void umlaute2ascii(char *s);

GLOBAL void label2tex ( char *s );
GLOBAL void label2html ( char *s );

GLOBAL void node2winhelp (char *n);
GLOBAL void node2WinAutoID (char *id, const char *n);
GLOBAL void node2NrWinhelp ( char *s, int i);
GLOBAL void alias2NrWinhelp ( char *s, int i);
GLOBAL void label2NrWinhelp ( char *s, int i);

GLOBAL void node2NrIPF ( char *s, int i);
GLOBAL void alias2NrIPF ( char *s, int i);
GLOBAL void label2NrIPF ( char *s, int i);

GLOBAL void node2pchelp (char *n);

GLOBAL void node2stg(char *s);
GLOBAL void index2stg(char *s);
GLOBAL void replace_2at_by_1at ( char *s );
GLOBAL void replace_1at_by_2at ( char *s );

GLOBAL void node2vision (char *n);
GLOBAL void node2texinfo (char *s);

GLOBAL void c_umlaute (char *s);

GLOBAL void c_tilde (char *s);
GLOBAL void replace_udo_tilde ( char * s);
GLOBAL void replace_udo_nbsp ( char * s);
GLOBAL void convert_tilde ( char *s );

GLOBAL void c_divis (char *s);

GLOBAL void winspecials2ascii ( char *s );
GLOBAL void c_rtf_quotes ( char *s );
GLOBAL void c_vars (char *s);

GLOBAL void c_man_styles ( char *s );

GLOBAL void auto_quote_chars ( char *s, BOOLEAN all );
GLOBAL void auto_quote_texindex ( char *s );
GLOBAL void auto_quote_linedraw ( char *s );

GLOBAL void init_module_chars ( void );

/*	############################################################
	# chr.h
	############################################################	*/

