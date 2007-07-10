/*	############################################################
	# @(#) sty.h
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

#ifndef UDO_STY_H
#define UDO_STY_H

/*	--------------------------------------------------
	diverse Flags fuer die Stilueberpruefung
	--------------------------------------------------	*/
typedef struct _styleflag
{
	BOOLEAN bold;
	BOOLEAN	footnote;
	BOOLEAN italic;
	BOOLEAN underlined;
	BOOLEAN verbatim;
	BOOLEAN twriter;
	/* New in V6.5.9 [NHz] */
	BOOLEAN insert;
	BOOLEAN deleted;
	/* New in V6.5.9 [NHz] */
	BOOLEAN colour;
	/* New in V6.5.20 [GS] */
	BOOLEAN sup;
	BOOLEAN sub;
}	STYLEFLAG;

#endif /* UDO_STY_H */

/*	############################################################
	# Platzhalter-Konstanten
	# \011 und \012 duerfen aus mir momentan nicht erfindlichen
	# Gruenden nicht benutzt werden.
	# Dies gilt auch fÅr \018, \019, \025, \027, \030, \038,
	# \039 und \042 [NHz]
	############################################################	*/

#define	STYLELEN		4

#define	C_BOLD_ON		'\001'
#define	C_BOLD_OFF		'\002'
#define	C_ITALIC_ON		'\003'
#define	C_ITALIC_OFF	'\004'
#define	C_FOOT_ON		'\005'
#define	C_FOOT_OFF		'\006'
#define	C_UNDER_ON		'\007'
#define	C_UNDER_OFF		'\010'
#define	C_VERB_ON		'\013'
#define	C_VERB_OFF		'\014'
#define	C_TWRITER_ON	'\015'
#define	C_TWRITER_OFF	'\016'
/* New in V6.5.9 [NHz] */
#define	C_INSERT_ON	    '\017'
#define	C_INSERT_OFF	'\020'
#define	C_DELETED_ON	'\021'
#define	C_DELETED_OFF	'\022'
/* New in V6.5.9 [NHz] */
#define	C_COLOR_BLACK	'\023'
#define	C_COLOR_SILVER	'\024'
#define	C_COLOR_GRAY	'\026'
#define	C_COLOR_WHITE	'\031'
#define	C_COLOR_MAROON	'\032'
#define	C_COLOR_RED  	'\033'
#define	C_COLOR_PURPLE	'\034'
#define	C_COLOR_FUCHSIA	'\035'
#define	C_COLOR_GREEN	'\036'
#define	C_COLOR_LIME	'\037'
#define	C_COLOR_OLIVE	'\040'
#define	C_COLOR_YELLOW	'\041'
#define	C_COLOR_NAVY	'\043'
#define	C_COLOR_BLUE	'\044'
#define	C_COLOR_TEAL	'\045'
#define	C_COLOR_AQUA	'\046'
#define	C_COLOR_OFF	    '\047'
/* New in V6.5.20 [GS] */
#define	C_SUP_ON	    '\048'
#define	C_SUP_OFF	    '\049'
#define	C_SUB_ON	    '\050'
#define	C_SUB_OFF	    '\051'


/*	############################################################
	# globale Variablen
	############################################################	*/
GLOBAL STYLEFLAG	styleflag;	/* Flags fuer die Stilpaare		*/

GLOBAL char STYLEMAGIC[8];
GLOBAL char BOLD_ON[8],		BOLD_OFF[8];
GLOBAL char FOOT_ON[8],		FOOT_OFF[8];
GLOBAL char ITALIC_ON[8],	ITALIC_OFF[8];
GLOBAL char TWRITER_ON[8],	TWRITER_OFF[8];
GLOBAL char UNDER_ON[8],	UNDER_OFF[8];
/* New in V6.5.9 [NHz] */
GLOBAL char INSERT_ON[8],	INSERT_OFF[8];
GLOBAL char DELETED_ON[8],	DELETED_OFF[8];
/* New in V6.5.9 [NHz] */
GLOBAL char COLOR_BLACK[8],	COLOR_SILVER[8],
COLOR_GRAY[8],	COLOR_WHITE[8],	COLOR_MAROON[8],
COLOR_RED[8],	COLOR_PURPLE[8],	COLOR_FUCHSIA[8],
COLOR_GREEN[8],	COLOR_LIME[8],	COLOR_OLIVE[8],
COLOR_YELLOW[8],	COLOR_NAVY[8],	COLOR_BLUE[8],
COLOR_TEAL[8],	COLOR_AQUA[8],	COLOR_OFF[8];
/* New in V6.5.20 [GS] */
GLOBAL char SUP_ON[8],	SUP_OFF[8];
GLOBAL char SUB_ON[8],	SUB_OFF[8];



/*	############################################################
	# globale Funktionen
	############################################################	*/
GLOBAL void del_footnotes ( char *s );
GLOBAL void del_internal_footnotes ( char *s );
GLOBAL void del_html_styles ( char *s );
GLOBAL void del_internal_styles ( char *s );

GLOBAL void c_pch_styles ( char *s );
GLOBAL void c_rtf_styles ( char *s );
GLOBAL void c_win_styles ( char *s );
GLOBAL void c_internal_styles ( char *s );
GLOBAL void c_styles ( char *s );

GLOBAL void check_styles ( char *s );
GLOBAL void check_styleflags ( void );
GLOBAL void check_verb_style ( void );

GLOBAL void check_styles_drc_next_line ( void );
GLOBAL void check_styles_asc_last_line ( char *s );
GLOBAL void check_styles_asc_next_line ( void );

GLOBAL void init_module_sty ( void );


/*	############################################################
	# sty.h
	############################################################	*/