/*	############################################################
	# @(#) sty.c
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
	############################################################	*/

#ifndef ID_STY_C
#define ID_STY_C
const char *id_sty_c= "@(#) sty.c       31.07.1998";
#endif

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portab.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "chr.h"
#include "msg.h"
#include "str.h"
#include "udo.h"

#include "export.h"
#include "sty.h"

/*	############################################################
	# lokale Variablen und Prototypen
	############################################################	*/
LOCAL const char	*stylemagic=	"(!";

LOCAL char VERB_ON[8];
LOCAL char VERB_OFF[8];

LOCAL void footnote2ascii ( char *s );


/*	############################################################
	#
	# Stilumwandlungen
	#
	############################################################	*/
LOCAL void footnote2ascii ( char *s )
{
	qreplace_all(s, FOOT_ON, STYLELEN, " (", 2);
	qreplace_all(s, FOOT_OFF, STYLELEN, ")", 1);
}	/* footnote2ascii */


GLOBAL void del_footnotes ( char *s )
{
	char *ptr;

	if ( (ptr=strstr(s, stylemagic))==NULL )
	{	return;
	}
	
	qdelete_all(ptr, CMD_FOOT_ON, CMD_STYLELEN);
	qdelete_all(ptr, CMD_FOOT_OFF, CMD_STYLELEN);
}


GLOBAL void del_internal_footnotes ( char *s )
{
	char *ptr;

	if ( (ptr=strstr(s, STYLEMAGIC))==NULL )
	{	return;
	}
	
	delete_all(ptr, FOOT_ON);
	delete_all(ptr, FOOT_OFF);
}

GLOBAL void del_html_styles ( char *s )
{
	qdelete_all(s, "<b>", 3);
	qdelete_all(s, "</b>", 4);
	qdelete_all(s, "<i>", 3);
	qdelete_all(s, "</i>", 4);
	qdelete_all(s, "<u>", 3);
	qdelete_all(s, "</u>", 4);
	qdelete_all(s, "<tt>", 4);
	qdelete_all(s, "</tt>", 5);
	/* New in V6.5.9 [NHz] */
	qdelete_all(s, "<strong>", 8);
	qdelete_all(s, "</strong>", 9);
	qdelete_all(s, "<em>", 4);
	qdelete_all(s, "</em>", 5);
	qdelete_all(s, "<kbd>", 5);
	qdelete_all(s, "</kbd>", 6);
	qdelete_all(s, "<span style=\"text-decoration: underline;\">", 42);
	qdelete_all(s, "</span>", 7);
}

GLOBAL void del_internal_styles ( char *s )
{
	char *ptr;

	if ( (ptr=strstr(s, STYLEMAGIC))==NULL )
	{	return;
	}

	qdelete_all(ptr, BOLD_ON, STYLELEN);
	qdelete_all(ptr, BOLD_OFF, STYLELEN);
	qdelete_all(ptr, ITALIC_ON, STYLELEN);
	qdelete_all(ptr, ITALIC_OFF, STYLELEN);
	qdelete_all(ptr, UNDER_ON, STYLELEN);
	qdelete_all(ptr, UNDER_OFF, STYLELEN);
	qdelete_all(ptr, TWRITER_ON, STYLELEN);
	qdelete_all(ptr, TWRITER_OFF, STYLELEN);
	qdelete_all(ptr, VERB_ON, STYLELEN);
	qdelete_all(ptr, VERB_OFF, STYLELEN);
	
}	/* del_internal_styles */


GLOBAL void c_pch_styles ( char *s )
{
	if ( strstr(s, STYLEMAGIC)==NULL )
	{	return;
	}

	footnote2ascii(s);

#if 0
	delete_all(s, VERB_ON);
	delete_all(s, VERB_OFF);
#endif
	
	del_internal_styles(s);

}	/* c_pch_styles */


GLOBAL void c_rtf_styles ( char *s )
{
	char *ptr;
	char fs[20];
	int l;

	if ( (ptr=strstr(s, STYLEMAGIC))==NULL )
	{	return;
	}

	qreplace_all(ptr, BOLD_ON, STYLELEN, "{\\b ", 4);
	qreplace_all(ptr, BOLD_OFF, STYLELEN, "}", 1);
	qreplace_all(ptr, ITALIC_ON, STYLELEN, "{\\i ", 4);
	qreplace_all(ptr, ITALIC_OFF, STYLELEN, "}", 1);
	qreplace_all(ptr, UNDER_ON, STYLELEN, "{\\ul ", 5);
	qreplace_all(ptr, UNDER_OFF, STYLELEN, "}", 1);
	sprintf(fs, "{\\f1\\fs%d ", iDocMonofontSize);
	l = (int) strlen(fs);
	qreplace_all(ptr, VERB_ON, STYLELEN, fs, l);
	qreplace_all(ptr, VERB_OFF, STYLELEN, "}", 1);
	qreplace_all(ptr, TWRITER_ON, STYLELEN, fs, l);
	qreplace_all(ptr, TWRITER_OFF, STYLELEN, "}", 1);
	qreplace_all(ptr, FOOT_ON, STYLELEN, "{\\chftn{\\footnote\\chftn{\\fs14  ", 31);	/* r5pl9 */
	qreplace_all(ptr, FOOT_OFF, STYLELEN, "}}}", 3);

	del_internal_styles(s);
}	/* c_rtf_styles */


GLOBAL void c_win_styles ( char *s )
{
	char *ptr;
	char fs[20];
	int l;
	
	if ( (ptr=strstr(s, STYLEMAGIC))==NULL )
	{	return;
	}

	qreplace_all(ptr, BOLD_ON, STYLELEN, "{\\b ", 4);
	qreplace_all(ptr, BOLD_OFF, STYLELEN, "}", 1);
	qreplace_all(ptr, ITALIC_ON, STYLELEN, "{\\i ", 4);
	qreplace_all(ptr, ITALIC_OFF, STYLELEN, "}", 1);
	qreplace_all(ptr, UNDER_ON, STYLELEN, "{\\ul ", 5);
	qreplace_all(ptr, UNDER_OFF, STYLELEN, "}", 1);
	sprintf(fs, "{\\f1\\fs%d ", iDocMonofontSize);
	l = (int) strlen(fs);
	qreplace_all(ptr, VERB_ON, STYLELEN, fs, l);
	qreplace_all(ptr, VERB_OFF, STYLELEN, "}", 1);
	qreplace_all(ptr, TWRITER_ON, STYLELEN, fs, l);
	qreplace_all(ptr, TWRITER_OFF, STYLELEN, "}", 1);

	footnote2ascii(s);

	del_internal_styles(s);
}	/* c_win_styles */




GLOBAL void c_internal_styles ( char *s )
{
	char	*ptr;	/*r6pl5: schon gefunden, also als Start benutzen */
	char	tex_verb_on[16];
	char	tex_verb_off[16];

	if ( (ptr=strstr(s, STYLEMAGIC))==NULL )
	{	return;
	}
	
	if (no_effects)
	{	del_internal_styles(s);
	}

	switch (desttype)
	{
		case TOTEX:
		case TOPDL:
			qreplace_all(ptr, BOLD_ON, STYLELEN, "\\textbf{", 8);
			qreplace_all(ptr, BOLD_OFF, STYLELEN, "}", 1);
			qreplace_all(ptr, ITALIC_ON, STYLELEN, "\\textit{", 8);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN, "}", 1);
			qreplace_all(ptr, TWRITER_ON, STYLELEN, "\\texttt{", 8);
			qreplace_all(ptr, TWRITER_OFF, STYLELEN, "}", 1);
			qreplace_all(ptr, UNDER_ON, STYLELEN, "\\underline{", 11);
			qreplace_all(ptr, UNDER_OFF, STYLELEN, "}", 1);
			sprintf(tex_verb_on, "\\verb%c", cTexVerb);
			sprintf(tex_verb_off, "%c", cTexVerb);
			replace_all(ptr, VERB_ON, tex_verb_on);
			replace_all(ptr, VERB_OFF, tex_verb_off);
			replace_all(ptr, FOOT_ON, "\\footnote{");
			replace_all(ptr, FOOT_OFF, "}");
			del_internal_styles(s);
			break;
		case TOLYX:
			replace_all(ptr, BOLD_ON, "\\series"INDENT_S"bold"INDENT_S);
			replace_all(ptr, BOLD_OFF, "\\series"INDENT_S"default"INDENT_S);
			replace_all(ptr, ITALIC_ON, "\\shape"INDENT_S"italic"INDENT_S);
			replace_all(ptr, ITALIC_OFF, "\\shape"INDENT_S"default"INDENT_S);
			replace_all(ptr, TWRITER_ON, "\\family"INDENT_S"typewriter"INDENT_S);
			replace_all(ptr, TWRITER_OFF, "\\family"INDENT_S"default"INDENT_S);
			replace_all(ptr, UNDER_ON, "\\bar"INDENT_S"under"INDENT_S);
			replace_all(ptr, UNDER_OFF, "\\bar"INDENT_S"default"INDENT_S);
			replace_all(ptr, VERB_ON, "\\family"INDENT_S"typewriter"INDENT_S);
			replace_all(ptr, VERB_OFF, "\\family"INDENT_S"default"INDENT_S);
			replace_all(ptr, FOOT_ON, "\n\\begin_float"INDENT_S"footnote\n\\layout"INDENT_S"Standard\n\n");
			replace_all(ptr, FOOT_OFF, "\n\\end_float\n\\layout"INDENT_S"Standard\n");
			del_internal_styles(s);
			break;
		case TOINF:
			qreplace_all(ptr, BOLD_ON, STYLELEN,		"@strong{",		8);
			qreplace_all(ptr, BOLD_OFF, STYLELEN,		"}",			1);
			qreplace_all(ptr, ITALIC_ON, STYLELEN,		"@emph{",		6);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN,		"}", 1);
			qreplace_all(ptr, FOOT_ON, STYLELEN,		" @footnote{",	11);
			qreplace_all(ptr, FOOT_OFF, STYLELEN,		"};",			2);
			qreplace_all(ptr, TWRITER_ON, STYLELEN,		"@code{",		6);
			qreplace_all(ptr, TWRITER_OFF, STYLELEN,	"}",			1);
			qreplace_all(ptr, VERB_ON, STYLELEN,		"@code{",		6);
			qreplace_all(ptr, VERB_OFF, STYLELEN,		"}",			1);
			del_internal_styles(s);
			break;
		case TOTVH:
#if 0
			delete_all(s, VERB_ON);
			delete_all(s, VERB_OFF);
#endif
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TOSTG:
			qreplace_all(ptr, BOLD_ON, STYLELEN,	"@{B}", 4);
			qreplace_all(ptr, BOLD_OFF, STYLELEN,	"@{b}", 4);
			qreplace_all(ptr, ITALIC_ON, STYLELEN,	"@{I}", 4);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN,	"@{i}", 4);
			qreplace_all(ptr, UNDER_ON, STYLELEN,	"@{U}", 4);
			qreplace_all(ptr, UNDER_OFF, STYLELEN,	"@{u}", 4);
#if 0
			delete_all(s, VERB_ON);
			delete_all(s, VERB_OFF);
#endif
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TOAMG:
			qreplace_all(ptr, BOLD_ON, STYLELEN,	"@{B}", 4);
			qreplace_all(ptr, BOLD_OFF, STYLELEN,	"@{UB}", 5);
			qreplace_all(ptr, ITALIC_ON, STYLELEN,	"@{I}", 4);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN,	"@{UI}", 5);
			qreplace_all(ptr, UNDER_ON, STYLELEN,	"@{U}", 4);
			qreplace_all(ptr, UNDER_OFF, STYLELEN,	"@{UU}", 5);
#if 0
			delete_all(s, VERB_ON);
			delete_all(s, VERB_OFF);
#endif
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TOASC:
			qreplace_all(ptr, BOLD_ON, STYLELEN,	"*", 1);
			qreplace_all(ptr, BOLD_OFF, STYLELEN,	"*", 1);
			qreplace_all(ptr, ITALIC_ON, STYLELEN,	"/", 1);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN,	"/", 1);
			qreplace_all(ptr, UNDER_ON, STYLELEN,	"_", 1);
			qreplace_all(ptr, UNDER_OFF, STYLELEN,	"_", 1);
#if 0
			delete_all(s, VERB_ON);
			delete_all(s, VERB_OFF);
#endif
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TODRC:
			qreplace_all(ptr, BOLD_ON, STYLELEN,	sDrcBcolor, 2);
			qreplace_all(ptr, BOLD_OFF, STYLELEN,	"\003@", 2);
			qreplace_all(ptr, ITALIC_ON, STYLELEN,	sDrcIcolor, 2);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN,	"\003@", 2);
			qreplace_all(ptr, UNDER_ON, STYLELEN,	sDrcUcolor, 2);
			qreplace_all(ptr, UNDER_OFF, STYLELEN,	"\003@", 2);
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TOSRC:
		case TOSRP:
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TOMAN:
			c_man_styles(s);
#if 0
			delete_all(s, VERB_ON);
			delete_all(s, VERB_OFF);
#endif
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TONRO:
			qreplace_all(ptr, BOLD_ON, STYLELEN, "\n.B ", 4);
			qreplace_all(ptr, BOLD_OFF, STYLELEN, "\n", 1);
			qreplace_all(ptr, ITALIC_ON, STYLELEN, "\n.I ", 4);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN, "\n", 1);
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TOPCH:
#if 0
			delete_all(s, VERB_ON);
			delete_all(s, VERB_OFF);
#endif
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TOHTM:
		case TOMHH:
			/* Changed in V6.5.9 [NHz] */
			if(html_doctype >= XHTML_STRICT)
			{
				qreplace_all(ptr, BOLD_ON, STYLELEN,		"<strong>", 8);
				qreplace_all(ptr, BOLD_OFF, STYLELEN,		"</strong>", 9);
				qreplace_all(ptr, ITALIC_ON, STYLELEN,	"<em>", 4);
				qreplace_all(ptr, ITALIC_OFF, STYLELEN,	"</em>", 5);
				qreplace_all(ptr, UNDER_ON, STYLELEN,		"<span style=\"text-decoration: underline;\">", 42);
				qreplace_all(ptr, UNDER_OFF, STYLELEN,	"</span>", 7);
				qreplace_all(ptr, VERB_ON, STYLELEN,		"<kbd>", 5);
				qreplace_all(ptr, VERB_OFF, STYLELEN,		"</kbd>", 6);
				qreplace_all(ptr, TWRITER_ON, STYLELEN,	"<kbd>", 5);
				qreplace_all(ptr, TWRITER_OFF, STYLELEN,	"</kbd>", 6);
			}
			else
			{
				qreplace_all(ptr, BOLD_ON, STYLELEN,		"<b>", 3);
				qreplace_all(ptr, BOLD_OFF, STYLELEN,		"</b>", 4);
				qreplace_all(ptr, ITALIC_ON, STYLELEN,	"<i>", 3);
				qreplace_all(ptr, ITALIC_OFF, STYLELEN,	"</i>", 4);
				qreplace_all(ptr, UNDER_ON, STYLELEN,		"<u>", 3);
				qreplace_all(ptr, UNDER_OFF, STYLELEN,	"</u>", 4);
				qreplace_all(ptr, VERB_ON, STYLELEN,		"<tt>", 4);
				qreplace_all(ptr, VERB_OFF, STYLELEN,		"</tt>", 5);
				qreplace_all(ptr, TWRITER_ON, STYLELEN,	"<tt>", 4);
				qreplace_all(ptr, TWRITER_OFF, STYLELEN,	"</tt>", 5);
			}
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TOHPH:
			replace_all(s, ITALIC_ON, "<emph>");
			replace_all(s, ITALIC_OFF, "<\\emph>");
			replace_all(s, VERB_ON, "<ex>");
			replace_all(s, VERB_OFF, "<\\ex>");
			replace_all(s, TWRITER_ON, "<ex>");
			replace_all(s, TWRITER_OFF, "<\\ex>");
			footnote2ascii(s);
			del_internal_styles(s);
			break;
		case TOLDS:
			qreplace_all(ptr, BOLD_ON, STYLELEN,		"<bf>", 4);
			qreplace_all(ptr, BOLD_OFF, STYLELEN,		"</bf>", 5);
			qreplace_all(ptr, ITALIC_ON, STYLELEN,	"<em>", 4);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN,	"</em>", 5);
			qreplace_all(ptr, VERB_ON, STYLELEN,		"<tt>", 4);
			qreplace_all(ptr, VERB_OFF, STYLELEN,		"</tt>", 5);
			qreplace_all(ptr, TWRITER_ON, STYLELEN,	"<tt>", 4);
			qreplace_all(ptr, TWRITER_OFF, STYLELEN,	"</tt>", 5);
			qreplace_all(ptr, FOOT_ON, STYLELEN,		"<footnote>", 10);
			qreplace_all(ptr, FOOT_OFF, STYLELEN,		"</footnote>", 11);
			footnote2ascii(s);
			del_internal_styles(s);
			break;

		case TOIPF:
			qreplace_all(ptr, BOLD_ON, STYLELEN, ":hp2.", 5);
			qreplace_all(ptr, BOLD_OFF, STYLELEN, ":ehp2.", 6);
			qreplace_all(ptr, ITALIC_ON, STYLELEN, ":hp1.", 5);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN, ":ehp1.", 6);
			qreplace_all(ptr, TWRITER_ON, STYLELEN, "", 0);	/* <???> */
			qreplace_all(ptr, TWRITER_OFF, STYLELEN, "", 0);	/* <???> */
			qreplace_all(ptr, UNDER_ON, STYLELEN, ":hp5.", 5);
			qreplace_all(ptr, UNDER_OFF, STYLELEN, ":ehp5.", 6);
			footnote2ascii(s);
			del_internal_styles(s);
			break;
			
		case TOKPS:
			qreplace_all(ptr, BOLD_ON, STYLELEN,		") udoshow Bon (", 15);
			qreplace_all(ptr, BOLD_OFF, STYLELEN,		") udoshow Boff (", 16);
			qreplace_all(ptr, ITALIC_ON, STYLELEN,		") udoshow Ion (", 15);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN,		") udoshow Ioff (", 16);
			qreplace_all(ptr, UNDER_ON, STYLELEN,		") udoshow Uon (", 15);
			qreplace_all(ptr, UNDER_OFF, STYLELEN,		") udoshow Uoff (", 16);
			qreplace_all(ptr, VERB_ON, STYLELEN,		") udoshow Von (", 15);
			qreplace_all(ptr, VERB_OFF, STYLELEN,		") udoshow Voff (", 16);
			qreplace_all(ptr, TWRITER_ON, STYLELEN,		") udoshow Von (", 15);
			qreplace_all(ptr, TWRITER_OFF, STYLELEN,	") udoshow Voff (", 16);
			/* New in r6pl15 */
			qreplace_all(ptr, FOOT_ON, STYLELEN,		") udoshow (", 11);
			qreplace_all(ptr, FOOT_OFF, STYLELEN,		") footnote (", 12);
/*			footnote2ascii(s);*/
			del_internal_styles(s);
			break;
	}

}	/*c_internal_styles*/



GLOBAL void c_styles ( char *s )
{
	char *ptr;

	if ( (ptr=strstr(s, stylemagic))==NULL )
	{	return;
	}

	qreplace_all(ptr, CMD_BOLD_ON, CMD_STYLELEN,		BOLD_ON, STYLELEN);
	qreplace_all(ptr, CMD_BOLD_OFF, CMD_STYLELEN,		BOLD_OFF, STYLELEN);
	qreplace_all(ptr, CMD_ITALIC_ON, CMD_STYLELEN,		ITALIC_ON, STYLELEN);
	qreplace_all(ptr, CMD_ITALIC_OFF, CMD_STYLELEN,		ITALIC_OFF, STYLELEN);
	qreplace_all(ptr, CMD_UNDER_ON, CMD_STYLELEN,		UNDER_ON, STYLELEN);
	qreplace_all(ptr, CMD_UNDER_OFF, CMD_STYLELEN, 		UNDER_OFF, STYLELEN);
	qreplace_all(ptr, CMD_VERB_ON, CMD_STYLELEN,		VERB_ON, STYLELEN);
	qreplace_all(ptr, CMD_VERB_OFF, CMD_STYLELEN, 		VERB_OFF, STYLELEN);
	qreplace_all(ptr, CMD_FOOT_ON, CMD_STYLELEN, 		FOOT_ON, STYLELEN);
	qreplace_all(ptr, CMD_FOOT_OFF, CMD_STYLELEN, 		FOOT_OFF, STYLELEN);
	qreplace_all(ptr, CMD_TWRITER_ON, CMD_STYLELEN, 	TWRITER_ON, STYLELEN);
	qreplace_all(ptr, CMD_TWRITER_OFF, CMD_STYLELEN,	TWRITER_OFF, STYLELEN);
	
}	/* c_styles */


/*	############################################################
	#
	# Styleflags setzen und checken. Beim Setzen wird ein String
	# mit UDO-internen Styles erwartet! (siehe styles.h)
	#
	############################################################	*/
GLOBAL void check_styles ( char *s )
{
	char *ptr, *found;

	
	if (s[0]==EOS)	/* Leerer String? */
	{	return;
	}
	
	found= strstr(s, STYLEMAGIC);
	
	if (found==NULL)
	{	return;
	}
	
	/* ptr zeigt jeweils auf das erste Zeichen des Stylemagic \033\001 */
	/* UDO ersetzt Befehle wie (!B) zunaechst durch eigene Escape-Befehle */
	/* ESC-001-xxx-ESC, wobei xxx den jeweiligen Stil angibt */

	do
	{
		ptr= found;
		
		switch (ptr[2])
		{	case C_BOLD_ON:
				if (styleflag.bold)			error_still_active(CMD_BOLD_ON);
				styleflag.bold= TRUE;
				break;
			case C_BOLD_OFF:
				if (!styleflag.bold)		error_not_active(CMD_BOLD_ON);
				styleflag.bold= FALSE;
				break;
			case C_FOOT_ON:
				if (styleflag.footnote)		error_still_active(CMD_FOOT_ON);
				styleflag.footnote= TRUE;
				break;
			case C_FOOT_OFF:
				if (!styleflag.footnote)	error_not_active(CMD_FOOT_ON);
				styleflag.footnote= FALSE;
				break;
			case C_ITALIC_ON:
				if (styleflag.italic)		error_still_active(CMD_ITALIC_ON);
				styleflag.italic= TRUE;
				break;
			case C_ITALIC_OFF:
				if (!styleflag.italic)		error_not_active(CMD_ITALIC_ON);
				styleflag.italic= FALSE;
				break;
			case C_UNDER_ON:
				if (styleflag.underlined)	error_still_active(CMD_UNDER_ON);
				styleflag.underlined= TRUE;
				break;
			case C_UNDER_OFF:
				if (!styleflag.underlined)	error_not_active(CMD_UNDER_ON);
				styleflag.underlined= FALSE;
				break;
			case C_VERB_ON:
				if (styleflag.verbatim)		error_still_active(CMD_VERB_ON);
				styleflag.verbatim= TRUE;
				break;
			case C_VERB_OFF:
				if (!styleflag.verbatim)	error_not_active(CMD_VERB_ON);
				styleflag.verbatim= FALSE;
				break;
			case C_TWRITER_ON:
				if (styleflag.twriter)		error_still_active(CMD_TWRITER_ON);
				styleflag.twriter= TRUE;
				break;
			case C_TWRITER_OFF:
				if (!styleflag.twriter)		error_not_active(CMD_TWRITER_ON);
				styleflag.twriter= FALSE;
				break;
		}	/* switch ptr[0] */

		found= strstr(ptr+1, STYLEMAGIC);

	}	while ( found!=NULL );

		
} /* check_styles */


GLOBAL void check_styleflags ( void )
{
	if (styleflag.bold)			error_still_active(CMD_BOLD_ON);
	if (styleflag.footnote)		error_still_active(CMD_FOOT_ON);
	if (styleflag.italic)		error_still_active(CMD_ITALIC_ON);
	if (styleflag.twriter)		error_still_active(CMD_TWRITER_ON);
	if (styleflag.underlined)	error_still_active(CMD_UNDER_ON);
	if (styleflag.verbatim)		error_still_active(CMD_VERB_ON);

}	/* check_styleflags */


GLOBAL void check_verb_style ( void )	/* Pl13 */
{
	if ((desttype==TOTEX || desttype==TOPDL) && styleflag.verbatim)
	{	warning_split_verb();
	}
	
}	/* check_verb_style */


/* Der DRC verwirft am Ende einer Zeile die Schriftarten. */
/* Daher muessen sie am Anfang der nachsten Zeile wieder ausgegeben werden */

GLOBAL void check_styles_drc_next_line ( void )
{
	if (styleflag.bold)			out(sDrcBcolor);
	if (styleflag.italic)		out(sDrcIcolor);
	if (styleflag.underlined)	out(sDrcUcolor);
}

GLOBAL void check_styles_asc_last_line ( char *s )
{
	if (styleflag.bold)			strcat(s, "*");
	if (styleflag.italic)		strcat(s, "/");
	if (styleflag.underlined)	strcat(s, "_");
}

GLOBAL void check_styles_asc_next_line ( void )
{
	if (styleflag.bold)			out("*");
	if (styleflag.italic)		out("/");
	if (styleflag.underlined)	out("_");
}

/*	############################################################
	# Modulinit
	############################################################	*/
GLOBAL void init_module_sty ( void )
{
	strcpy(STYLEMAGIC, ESC_STYLE_MAGIC);

	sprintf(BOLD_ON,		"%s%c\033", ESC_STYLE_MAGIC, C_BOLD_ON);
	sprintf(BOLD_OFF,		"%s%c\033", ESC_STYLE_MAGIC, C_BOLD_OFF);
	sprintf(ITALIC_ON,		"%s%c\033", ESC_STYLE_MAGIC, C_ITALIC_ON);
	sprintf(ITALIC_OFF,		"%s%c\033", ESC_STYLE_MAGIC, C_ITALIC_OFF);
	sprintf(FOOT_ON,		"%s%c\033", ESC_STYLE_MAGIC, C_FOOT_ON);
	sprintf(FOOT_OFF,		"%s%c\033", ESC_STYLE_MAGIC, C_FOOT_OFF);
	sprintf(UNDER_ON,		"%s%c\033", ESC_STYLE_MAGIC, C_UNDER_ON);
	sprintf(UNDER_OFF,		"%s%c\033", ESC_STYLE_MAGIC, C_UNDER_OFF);
	sprintf(VERB_ON,		"%s%c\033", ESC_STYLE_MAGIC, C_VERB_ON);
	sprintf(VERB_OFF,		"%s%c\033", ESC_STYLE_MAGIC, C_VERB_OFF);
	sprintf(TWRITER_ON,		"%s%c\033", ESC_STYLE_MAGIC, C_TWRITER_ON);
	sprintf(TWRITER_OFF,	"%s%c\033", ESC_STYLE_MAGIC, C_TWRITER_OFF);

	strcpy(sDrcBcolor, "\003O");
	strcpy(sDrcIcolor, "\003O");
	strcpy(sDrcUcolor, "\003O");
}

/*	############################################################
	# sty.c
	############################################################	*/

