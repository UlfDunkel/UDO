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
#include "time.h" /* New in V6.5.9 [NHz] */
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

	/* New in V6.5.9 [NHz] */	
	qdelete_all(ptr, INSERT_ON, STYLELEN);
	qdelete_all(ptr, INSERT_OFF, STYLELEN);
	qdelete_all(ptr, DELETED_ON, STYLELEN);
	qdelete_all(ptr, DELETED_OFF, STYLELEN);

	/* New in V6.5.9 [NHz] */
	qdelete_all(ptr, COLOR_BLACK, STYLELEN);
	qdelete_all(ptr, COLOR_SILVER, STYLELEN);
	qdelete_all(ptr, COLOR_GRAY, STYLELEN);
	qdelete_all(ptr, COLOR_WHITE, STYLELEN);
	qdelete_all(ptr, COLOR_MAROON, STYLELEN);
	qdelete_all(ptr, COLOR_RED, STYLELEN);
	qdelete_all(ptr, COLOR_PURPLE, STYLELEN);
	qdelete_all(ptr, COLOR_FUCHSIA, STYLELEN);
	qdelete_all(ptr, COLOR_GREEN, STYLELEN);
	qdelete_all(ptr, COLOR_LIME, STYLELEN);
	qdelete_all(ptr, COLOR_OLIVE, STYLELEN);
	qdelete_all(ptr, COLOR_YELLOW, STYLELEN);
	qdelete_all(ptr, COLOR_NAVY, STYLELEN);
	qdelete_all(ptr, COLOR_BLUE, STYLELEN);
	qdelete_all(ptr, COLOR_TEAL, STYLELEN);
	qdelete_all(ptr, COLOR_AQUA, STYLELEN);
	qdelete_all(ptr, COLOR_OFF, STYLELEN);
	
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
	
	/* New in V6.5.9 [NHz] */
	qreplace_all(s, DELETED_ON, STYLELEN, "[", 1);
	qreplace_all(s, DELETED_OFF, STYLELEN, "]", 1);

	del_internal_styles(s);

}	/* c_pch_styles */


GLOBAL void c_rtf_styles ( char *s )
{
	char *ptr, time_insert[40], time_delete[40]; /* New in V6.5.9 [NHz] */
	char fs[20];
	int l;
	long time; /* New in V6.5.9 [NHz] */

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

	/* New in V6.5.9 [NHz] */
	time=(long)(iDateMin + (iDateHour << 6) + (iDateDay << 11) + ((long)iDateMonth << 16) + ((long)(iDateYear-1900) << 20));
	sprintf(time_insert, "{\\revised\\revauth1\\revdttm%ld ", time);
	sprintf(time_delete, "{\\deleted\\revauthdel1\\revdttm%ld ", time);
	qreplace_all(ptr, INSERT_ON, STYLELEN, time_insert, 36);
	qreplace_all(ptr, INSERT_OFF, STYLELEN, "}", 1);
	qreplace_all(ptr, DELETED_ON, STYLELEN, time_delete, 39);
	qreplace_all(ptr, DELETED_OFF, STYLELEN, "}", 1);

	/* New in V6.5.9 [NHz] */
	qreplace_all(ptr, COLOR_BLACK, STYLELEN, "{\\cf1 ", 6);
	qreplace_all(ptr, COLOR_SILVER, STYLELEN, "{\\cf2 ", 6);
	qreplace_all(ptr, COLOR_GRAY, STYLELEN, "{\\cf3 ", 6);
	qreplace_all(ptr, COLOR_WHITE, STYLELEN, "{\\cf4 ", 6);
	qreplace_all(ptr, COLOR_MAROON, STYLELEN, "{\\cf5 ", 6);
	qreplace_all(ptr, COLOR_RED, STYLELEN, "{\\cf6 ", 6);
	qreplace_all(ptr, COLOR_PURPLE, STYLELEN, "{\\cf7 ", 6);
	qreplace_all(ptr, COLOR_FUCHSIA, STYLELEN, "{\\cf8 ", 6);
	qreplace_all(ptr, COLOR_GREEN, STYLELEN, "{\\cf9 ", 6);
	qreplace_all(ptr, COLOR_LIME, STYLELEN, "{\\cf10 ", 7);
	qreplace_all(ptr, COLOR_OLIVE, STYLELEN, "{\\cf11 ", 7);
	qreplace_all(ptr, COLOR_YELLOW, STYLELEN, "{\\cf12 ", 7);
	qreplace_all(ptr, COLOR_NAVY, STYLELEN, "{\\cf13 ", 7);
	qreplace_all(ptr, COLOR_BLUE, STYLELEN, "{\\cf14 ", 7);
	qreplace_all(ptr, COLOR_TEAL, STYLELEN, "{\\cf15 ", 7);
	qreplace_all(ptr, COLOR_AQUA, STYLELEN, "{\\cf16 ", 7);
	qreplace_all(ptr, COLOR_OFF, STYLELEN, "}", 1);

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

	/* New in V6.5.9 [NHz] */
	qreplace_all(ptr, INSERT_ON, STYLELEN, "{\\cf6 ", 6);
	qreplace_all(ptr, INSERT_OFF, STYLELEN, "}", 1);
	qreplace_all(ptr, DELETED_ON, STYLELEN, "{\\strike ", 9);
	qreplace_all(ptr, DELETED_OFF, STYLELEN, "}", 1);

	/* New in V6.5.8 [NHz] */
	qreplace_all(ptr, COLOR_BLACK, STYLELEN, "{\\cf1 ", 6);
	qreplace_all(ptr, COLOR_SILVER, STYLELEN, "{\\cf2 ", 6);
	qreplace_all(ptr, COLOR_GRAY, STYLELEN, "{\\cf3 ", 6);
	qreplace_all(ptr, COLOR_WHITE, STYLELEN, "{\\cf4 ", 6);
	qreplace_all(ptr, COLOR_MAROON, STYLELEN, "{\\cf5 ", 6);
	qreplace_all(ptr, COLOR_RED, STYLELEN, "{\\cf6 ", 6);
	qreplace_all(ptr, COLOR_PURPLE, STYLELEN, "{\\cf7 ", 6);
	qreplace_all(ptr, COLOR_FUCHSIA, STYLELEN, "{\\cf8 ", 6);
	qreplace_all(ptr, COLOR_GREEN, STYLELEN, "{\\cf9 ", 6);
	qreplace_all(ptr, COLOR_LIME, STYLELEN, "{\\cf10 ", 7);
	qreplace_all(ptr, COLOR_OLIVE, STYLELEN, "{\\cf11 ", 7);
	qreplace_all(ptr, COLOR_YELLOW, STYLELEN, "{\\cf12 ", 7);
	qreplace_all(ptr, COLOR_NAVY, STYLELEN, "{\\cf13 ", 7);
	qreplace_all(ptr, COLOR_BLUE, STYLELEN, "{\\cf14 ", 7);
	qreplace_all(ptr, COLOR_TEAL, STYLELEN, "{\\cf15 ", 7);
	qreplace_all(ptr, COLOR_AQUA, STYLELEN, "{\\cf16 ", 7);
	qreplace_all(ptr, COLOR_OFF, STYLELEN, "}", 1);

	del_internal_styles(s);
}	/* c_win_styles */




GLOBAL void c_internal_styles ( char *s )
{
	char time_insert[1024], time_delete[1024]; /* New in V6.5.9 [NHz] */
	char this_time[40], cite[1024], change_date[26];
	long lang_insert, lang_delete;
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

			/* New in V6.5.9 [NHz], fuer TeX gibt es vielleicht eine bessere
			Moeglichkeit eingefuegte und geloeschte Text zu kennzeichnen */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

			del_internal_styles(s);
			break;
		case TOTVH:
#if 0
			delete_all(s, VERB_ON);
			delete_all(s, VERB_OFF);
#endif
			footnote2ascii(s);

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "@{G}", 4);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "@{g}", 4);

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "@{G}", 4);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "@{UG}", 5);

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, COLOR_BLACK, STYLELEN, "", 0);
			qreplace_all(ptr, COLOR_SILVER, STYLELEN, "\003G", 2);
			qreplace_all(ptr, COLOR_GRAY, STYLELEN, "\003H", 2);
			qreplace_all(ptr, COLOR_WHITE, STYLELEN, "\003O", 2);
			qreplace_all(ptr, COLOR_MAROON, STYLELEN, "\003D", 2);
			qreplace_all(ptr, COLOR_RED, STYLELEN, "\003L", 2);
			qreplace_all(ptr, COLOR_PURPLE, STYLELEN, "\003E", 2);
			qreplace_all(ptr, COLOR_FUCHSIA, STYLELEN, "\003M", 2);
			qreplace_all(ptr, COLOR_GREEN, STYLELEN, "\003B", 2);
			qreplace_all(ptr, COLOR_LIME, STYLELEN, "\003J", 2);
			qreplace_all(ptr, COLOR_OLIVE, STYLELEN, "\003J", 2);
			qreplace_all(ptr, COLOR_YELLOW, STYLELEN, "\003N", 2);
			qreplace_all(ptr, COLOR_NAVY, STYLELEN, "\003A", 2);
			qreplace_all(ptr, COLOR_BLUE, STYLELEN, "\003I", 2);
			qreplace_all(ptr, COLOR_TEAL, STYLELEN, "\003B", 2);
			qreplace_all(ptr, COLOR_AQUA, STYLELEN, "\003C", 2);
			qreplace_all(ptr, COLOR_OFF, STYLELEN, "\003@", 7);

			del_internal_styles(s);
			break;
		case TOSRC:
		case TOSRP:
			footnote2ascii(s);

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

			del_internal_styles(s);
			break;
		case TOMAN:
			c_man_styles(s);
#if 0
			delete_all(s, VERB_ON);
			delete_all(s, VERB_OFF);
#endif
			footnote2ascii(s);

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

			del_internal_styles(s);
			break;
		case TONRO:
			qreplace_all(ptr, BOLD_ON, STYLELEN, "\n.B ", 4);
			qreplace_all(ptr, BOLD_OFF, STYLELEN, "\n", 1);
			qreplace_all(ptr, ITALIC_ON, STYLELEN, "\n.I ", 4);
			qreplace_all(ptr, ITALIC_OFF, STYLELEN, "\n", 1);
			footnote2ascii(s);

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

			del_internal_styles(s);
			break;
		case TOPCH:
#if 0
			delete_all(s, VERB_ON);
			delete_all(s, VERB_OFF);
#endif
			footnote2ascii(s);

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

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

			/* New in V6.5.9 [NHz] */
			change_date[0] = EOS;

			if(change_date[0] == EOS)
			{
				char zone[10]="+00:00";
				time_t uhrzeit;
				int hour_local, min_local, mday_local, min_utc, hour_utc, mday_utc;
				int hours, minutes;
			
				if(strcmp(html_header_date_zone, "") >0)
					um_strcpy(zone, html_header_date_zone, 9, "output_html_meta1");
				else
				{
					time(&uhrzeit);
					mday_local = localtime(&uhrzeit)->tm_mday;
					mday_utc = gmtime(&uhrzeit)->tm_mday;
					hour_local = localtime(&uhrzeit)->tm_hour;
					hour_utc = gmtime(&uhrzeit)->tm_hour;
					min_local = localtime(&uhrzeit)->tm_min;
					min_utc = gmtime(&uhrzeit)->tm_min;
		
					if(min_local < min_utc)	/* special for countries with "broken times" (e.g. Iran +03:30) */
					{
						if(mday_local != mday_utc)	/* if different days over midnight */
							hours = hour_local - hour_utc - 1 + 24;
						else
							hours = hour_local - hour_utc - 1;
						minutes = min_utc - min_local;
					}
					else
					{
						if(mday_local != mday_utc)	/* if different days over midnight */
							hours = hour_local - hour_utc + 24;
						else
							hours = hour_local - hour_utc;
						minutes = min_local - min_utc;
					}
		
					sprintf(zone, "%+03d:%02d", hours, minutes);
				}
				sprintf(this_time, " datetime=\"%d-%02d-%02dT%02d:%02d:%02d%s\"", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin, iDateSec, zone);
			}
		
			sprintf(cite, " cite=\"%s\"", "http://www.udo-open-source.org");

			sprintf(time_insert, "<ins%s%s>", cite, this_time);
			lang_insert = strlen(time_insert);
			sprintf(time_delete, "<del%s%s>", cite, this_time);
			lang_delete = strlen(time_delete);
			qreplace_all(ptr, INSERT_ON, STYLELEN, time_insert, lang_insert);
			qreplace_all(ptr, INSERT_OFF, STYLELEN, "</ins>", 6);
			qreplace_all(ptr, DELETED_ON, STYLELEN, time_delete, lang_delete);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "</del>", 6);
		
			/* New in V6.5.9 [NHz] */
			if(html_doctype==HTML_OLD)
			{
				qreplace_all(ptr, COLOR_BLACK, STYLELEN, "<font color=\"#000000\">", 22);
				qreplace_all(ptr, COLOR_SILVER, STYLELEN, "<font color=\"#C0C0C0\">", 22);
				qreplace_all(ptr, COLOR_GRAY, STYLELEN, "<font color=\"#808080\">", 22);
				qreplace_all(ptr, COLOR_WHITE, STYLELEN, "<font color=\"#FFFFFF\">", 22);
				qreplace_all(ptr, COLOR_MAROON, STYLELEN, "<font color=\"#800000\">", 22);
				qreplace_all(ptr, COLOR_RED, STYLELEN, "<font color=\"#FF0000\">", 22);
				qreplace_all(ptr, COLOR_PURPLE, STYLELEN, "<font color=\"#800080\">", 22);
				qreplace_all(ptr, COLOR_FUCHSIA, STYLELEN, "<font color=\"#FF00FF\">", 22);
				qreplace_all(ptr, COLOR_GREEN, STYLELEN, "<font color=\"#008000\">", 22);
				qreplace_all(ptr, COLOR_LIME, STYLELEN, "<font color=\"#00FF00\">", 22);
				qreplace_all(ptr, COLOR_OLIVE, STYLELEN, "<font color=\"#808000\">", 22);
				qreplace_all(ptr, COLOR_YELLOW, STYLELEN, "<font color=\"#FFFF00\">", 22);
				qreplace_all(ptr, COLOR_NAVY, STYLELEN, "<font color=\"#000080\">", 22);
				qreplace_all(ptr, COLOR_BLUE, STYLELEN, "<font color=\"#0000FF\">", 22);
				qreplace_all(ptr, COLOR_TEAL, STYLELEN, "<font color=\"#008080\">", 22);
				qreplace_all(ptr, COLOR_AQUA, STYLELEN, "<font color=\"#00FFFF\">", 22);
				qreplace_all(ptr, COLOR_OFF, STYLELEN, "</font>", 7);
			}
			else
			{
				qreplace_all(ptr, COLOR_BLACK, STYLELEN, "<span style=\"color: black;\">", 28);
				qreplace_all(ptr, COLOR_SILVER, STYLELEN, "<span style=\"color: silver;\">", 29);
				qreplace_all(ptr, COLOR_GRAY, STYLELEN, "<span style=\"color: gray;\">", 27);
				qreplace_all(ptr, COLOR_WHITE, STYLELEN, "<span style=\"color: white;\">", 28);
				qreplace_all(ptr, COLOR_MAROON, STYLELEN, "<span style=\"color: maroon;\">", 29);
				qreplace_all(ptr, COLOR_RED, STYLELEN, "<span style=\"color: red;\">", 26);
				qreplace_all(ptr, COLOR_PURPLE, STYLELEN, "<span style=\"color: purple;\">", 29);
				qreplace_all(ptr, COLOR_FUCHSIA, STYLELEN, "<span style=\"color: fuchsia;\">", 30);
				qreplace_all(ptr, COLOR_GREEN, STYLELEN, "<span style=\"color: green;\">", 28);
				qreplace_all(ptr, COLOR_LIME, STYLELEN, "<span style=\"color: lime;\">", 27);
				qreplace_all(ptr, COLOR_OLIVE, STYLELEN, "<span style=\"color: olive;\">", 28);
				qreplace_all(ptr, COLOR_YELLOW, STYLELEN, "<span style=\"color: yellow;\">", 29);
				qreplace_all(ptr, COLOR_NAVY, STYLELEN, "<span style=\"color: navy;\">", 27);
				qreplace_all(ptr, COLOR_BLUE, STYLELEN, "<span style=\"color: blue;\">", 27);
				qreplace_all(ptr, COLOR_TEAL, STYLELEN, "<span style=\"color: teal;\">", 27);
				qreplace_all(ptr, COLOR_AQUA, STYLELEN, "<span style=\"color: aqua;\">", 27);
				qreplace_all(ptr, COLOR_OFF, STYLELEN, "</span>", 7);
			}

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, DELETED_ON, STYLELEN, "[", 1);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, "]", 1);

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

			/* New in V6.5.9 [NHz] */
			qreplace_all(ptr, INSERT_ON, STYLELEN, ") udoshow currentrgbcolor 1 0 0 setrgbcolor (", 45);
			qreplace_all(ptr, INSERT_OFF, STYLELEN, ") udoshow setrgbcolor (", 23);
			qreplace_all(ptr, DELETED_ON, STYLELEN, ") udoshow Son (", 15);
			qreplace_all(ptr, DELETED_OFF, STYLELEN, ") udoshow Soff (", 16);

			/* New in V6.5.8 [NHz] */
			qreplace_all(ptr, COLOR_BLACK, STYLELEN, ") udoshow 0 0 0 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_SILVER, STYLELEN, ") udoshow 0 0 0 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_GRAY, STYLELEN, ") udoshow 0 0 0 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_WHITE, STYLELEN, ") udoshow 1 1 1 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_MAROON, STYLELEN, ") udoshow 1 0 0.3 setrgbcolor (", 31);
			qreplace_all(ptr, COLOR_RED, STYLELEN, ") udoshow 1 0 0 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_PURPLE, STYLELEN, ") udoshow 1 0 1 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_FUCHSIA, STYLELEN, ") udoshow 1 0 1 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_GREEN, STYLELEN, ") udoshow 0 1 0 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_LIME, STYLELEN, ") udoshow 0 0.7 0 setrgbcolor (", 31);
			qreplace_all(ptr, COLOR_OLIVE, STYLELEN, ") udoshow 1 1 0.5 setrgbcolor (", 31);
			qreplace_all(ptr, COLOR_YELLOW, STYLELEN, ") udoshow 1 1 0 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_NAVY, STYLELEN, ") udoshow 0 0 1 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_BLUE, STYLELEN, ") udoshow 0 0 1 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_TEAL, STYLELEN, ") udoshow 0 0.3 1 setrgbcolor (", 31);
			qreplace_all(ptr, COLOR_AQUA, STYLELEN, ") udoshow 0 1 1 setrgbcolor (", 29);
			qreplace_all(ptr, COLOR_OFF, STYLELEN, ") udoshow bcr bcg bcb setrgbcolor (", 35);

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
	/* New in V6.5.9 [NHz] */	
	qreplace_all(ptr, CMD_INSERT_ON, 6, 	INSERT_ON, STYLELEN);
	qreplace_all(ptr, CMD_INSERT_OFF, 6,	INSERT_OFF, STYLELEN);
	qreplace_all(ptr, CMD_DELETED_ON, 6, 	DELETED_ON, STYLELEN);
	qreplace_all(ptr, CMD_DELETED_OFF, 6,	DELETED_OFF, STYLELEN);
	/* New in V6.5.9 [NHz] */	
	qreplace_all(ptr, CMD_COLOR_BLACK, 8, 	COLOR_BLACK, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_SILVER, 9, 	COLOR_SILVER, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_GRAY, 7, 	COLOR_GRAY, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_WHITE, 8, 	COLOR_WHITE, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_MAROON, 9, 	COLOR_MAROON, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_RED, 6, 	COLOR_RED, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_PURPLE, 9, 	COLOR_PURPLE, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_FUCHSIA, 10, 	COLOR_FUCHSIA, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_GREEN, 8, 	COLOR_GREEN, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_LIME, 7, 	COLOR_LIME, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_OLIVE, 8, 	COLOR_OLIVE, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_YELLOW, 9, 	COLOR_YELLOW, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_NAVY, 7, 	COLOR_NAVY, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_BLUE, 7, 	COLOR_BLUE, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_TEAL, 7, 	COLOR_TEAL, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_AQUA, 7, 	COLOR_AQUA, STYLELEN);
	qreplace_all(ptr, CMD_COLOR_OFF, 9, 	COLOR_OFF, STYLELEN);

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
			/* New in V6.5.9 [NHz] */
			case C_INSERT_ON:
				if (styleflag.insert)		error_still_active(CMD_INSERT_ON);
				styleflag.insert= TRUE;
				break;
			case C_INSERT_OFF:
				if (!styleflag.insert)		error_not_active(CMD_INSERT_ON);
				styleflag.insert= FALSE;
				break;
			case C_DELETED_ON:
				if (styleflag.deleted)		error_still_active(CMD_DELETED_ON);
				styleflag.deleted= TRUE;
				break;
			case C_DELETED_OFF:
				if (!styleflag.deleted)		error_not_active(CMD_DELETED_ON);
				styleflag.deleted= FALSE;
				break;
			/* New in V6.5.9 [NHz] */
			case C_COLOR_BLACK:
			case C_COLOR_SILVER:
			case C_COLOR_GRAY:
			case C_COLOR_WHITE:
			case C_COLOR_MAROON:
			case C_COLOR_RED:
			case C_COLOR_PURPLE:
			case C_COLOR_FUCHSIA:
			case C_COLOR_GREEN:
			case C_COLOR_LIME:
			case C_COLOR_OLIVE:
			case C_COLOR_YELLOW:
			case C_COLOR_NAVY:
			case C_COLOR_BLUE:
			case C_COLOR_TEAL:
			case C_COLOR_AQUA:
				if (styleflag.colour)		error_still_active("Farbe");
				styleflag.colour= TRUE;
				break;
			case C_COLOR_OFF:
				if (!styleflag.colour)		error_not_active("Farbe");
				styleflag.colour= FALSE;
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
	/* New in V6.5.9 [NHz] */
	if (styleflag.insert)		error_still_active(CMD_INSERT_ON);
	if (styleflag.deleted)		error_still_active(CMD_DELETED_ON);
	/* New in V6.5.9 [NHz] */
	if (styleflag.colour)		error_still_active(CMD_COLOR_OFF);

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
	/* New in V6.5.9 [NHz] */
	sprintf(INSERT_ON,		"%s%c\033", ESC_STYLE_MAGIC, C_INSERT_ON);
	sprintf(INSERT_OFF,	"%s%c\033", ESC_STYLE_MAGIC, C_INSERT_OFF);
	sprintf(DELETED_ON,		"%s%c\033", ESC_STYLE_MAGIC, C_DELETED_ON);
	sprintf(DELETED_OFF,	"%s%c\033", ESC_STYLE_MAGIC, C_DELETED_OFF);
	/* New in V6.5.9 [NHz] */
	sprintf(COLOR_BLACK,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_BLACK);
	sprintf(COLOR_SILVER,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_SILVER);
	sprintf(COLOR_GRAY,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_GRAY);
	sprintf(COLOR_WHITE,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_WHITE);
	sprintf(COLOR_MAROON,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_MAROON);
	sprintf(COLOR_RED,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_RED);
	sprintf(COLOR_PURPLE,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_PURPLE);
	sprintf(COLOR_FUCHSIA,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_FUCHSIA);
	sprintf(COLOR_GREEN,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_GREEN);
	sprintf(COLOR_LIME,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_LIME);
	sprintf(COLOR_OLIVE,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_OLIVE);
	sprintf(COLOR_YELLOW,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_YELLOW);
	sprintf(COLOR_NAVY,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_NAVY);
	sprintf(COLOR_BLUE,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_BLUE);
	sprintf(COLOR_TEAL,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_TEAL);
	sprintf(COLOR_AQUA,		"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_AQUA);
	sprintf(COLOR_OFF,	"%s%c\033", ESC_STYLE_MAGIC, C_COLOR_OFF);

	strcpy(sDrcBcolor, "\003O");
	strcpy(sDrcIcolor, "\003O");
	strcpy(sDrcUcolor, "\003O");
}

/*	############################################################
	# sty.c
	############################################################	*/

