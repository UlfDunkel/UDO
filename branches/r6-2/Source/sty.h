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
}	STYLEFLAG;

#endif /* UDO_STY_H */

/*	############################################################
	# Platzhalter-Konstanten
	# \011 und \012 duerfen aus mir momentan nicht erfindlichen
	# Gruenden nicht benutzt werden.
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

