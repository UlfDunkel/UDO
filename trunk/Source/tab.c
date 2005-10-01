/*	############################################################
	# @(#) tab.c
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

#ifndef ID_TAB_C
#define ID_TAB_C
const char *id_tab_c= "@(#) tab.c       01.02.2004";
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
#include "env.h"
#include "msg.h"
#include "par.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"
#include "gui.h"

#include "export.h"
#include "tab.h"
#include "udomem.h"

/*	############################################################
	# lokale Variablen
	############################################################	*/
#define	MAX_CELLS_LEN	1024	/* max. Zeichenanzahl einer Zelle */

#define MAX_TAB_H		512		/* max. Hoehe einer Tabelle */
#define MAX_TAB_W		64		/* max. Breite einer Tabelle */
#define MAX_TAB_LABEL	10		/* max. Anzahl der hinter einanderfolgenden Labels */
#define	TAB_LEFT		0		/* Spalte linksbuendig */
#define	TAB_CENTER		1		/* Spalte zentriert */
#define	TAB_RIGHT		2		/* Spalte rechtsbuendig */

#define	MAXTABCAPTION	1024	/* max. Laenge einer Ueberschrift */

LOCAL int		tab_counter;						/* Tabellen-Zaehler			*/
LOCAL int		tab_w, tab_h;						/* Spalten und Zeilen		*/
LOCAL char		tab_caption[MAXTABCAPTION+1];		/* Tabellen-Ueberschrift	*/
LOCAL BOOLEAN	tab_caption_visible;				/* Im Tabellenverzeichnis?	*/
LOCAL char		*tab_cell[MAX_TAB_H+1][MAX_TAB_W+1]; /* Zeiger auf Feldtext		*/
LOCAL size_t	tab_cell_w[MAX_TAB_W+1];			/* Breiten der Spalten		*/
LOCAL int		tab_vert[MAX_TAB_W+1];				/* Vertikale Linien, wo?	*/
LOCAL int		tab_hori[MAX_TAB_H+1];				/* Horiz. Linien, wo?		*/
LOCAL int		tab_just[MAX_TAB_H+1];				/* Spaltenausrichtung		*/
LOCAL int		tab_toplines;						/* Oben Linie(n)?			*/
LOCAL int		tab_label[MAX_TAB_H+1];				/* Label, wo?				*/
LOCAL char		*tab_label_cell[MAX_TAB_H+1][MAX_TAB_LABEL];	/* Labeltext	*/

LOCAL char		cells[MAX_TAB_W+1][MAX_CELLS_LEN];	/* Puffer fuer Zellen		*/
LOCAL int		cells_counter;						/* Anzahl Zellen von Zeilen	*/

#define TAB_ADDITION_LEN	512
LOCAL char addition[TAB_ADDITION_LEN]="";
LOCAL BOOLEAN addition_has_align;
LOCAL BOOLEAN addition_has_valign;
LOCAL int addition_col_offset;


/*	############################################################
	# lokale Prototypen
	############################################################	*/
LOCAL void cells_reset ( void );

LOCAL void convert_table_caption ( const BOOLEAN visible );
LOCAL void table_output_lyx ( void );
LOCAL void table_output_ipf ( void );
LOCAL void table_output_win ( void );
LOCAL void table_output_rtf ( void );
LOCAL void table_output_html ( void );
LOCAL void table_output_tex ( void );
LOCAL void table_output_general ( void );


/*	############################################################
	#
	#
	# Tabellensatz (seit Release 4 Version 0.42)
	#
	#
	############################################################	*/
/*	------------------------------------------------------------
	cells_reset() loescht das cells[]-Feld.
	------------------------------------------------------------	*/
LOCAL void cells_reset ( void )
{
	register int i;

	for (i=0; i<=cells_counter; cells[i++][0]= EOS) ;
	cells_counter= 0;
}	/*cells_reset*/


GLOBAL void table_reset ( void )
{
	int x, y;
	
	tab_w= -1;
	tab_h= -1;
	
	for (y=0; y<MAX_TAB_H; y++)
	{	for (x=0; x<MAX_TAB_W; x++)
		{	if (tab_cell[y][x]!=NULL)
			{	um_free(tab_cell[y][x]);
				tab_cell[y][x]= NULL;
			}
		}
		tab_hori[y]= 0;
		tab_just[y]= TAB_LEFT;
		tab_label[y]= 0;
		for (x=0; x<MAX_TAB_LABEL; x++)
		{	if ( tab_label_cell[y][x] != NULL )
			{	um_free( tab_label_cell[y][x] );
				tab_label_cell[y][x] = NULL;
			}
		}

	}
	
	for (x=0; x<MAX_TAB_W; x++)
	{	tab_cell_w[x]= 0;
		tab_vert[x]= 0;
	}
	
	tab_toplines= 0;
	
}	/* table_reset */


LOCAL void convert_table_caption ( const BOOLEAN visible )
{
	char n[512];
	
	tokcpy2(n, 512);

	tab_caption[0]= EOS;	
	strncat(tab_caption, n, MAXTABCAPTION);

	convert_tilde(tab_caption);
	delete_all_divis(tab_caption);
	replace_udo_quotes(tab_caption);
	replace_placeholders(tab_caption);
	
	tab_caption_visible= visible;
		
}	/* convert_table_caption */


GLOBAL void c_table_caption ( void )
{
	convert_table_caption(TRUE);
}

GLOBAL void c_table_caption_nonr ( void )
{
	convert_table_caption(FALSE);
}

GLOBAL void table_get_header ( char *s )
{
	size_t	i;
	int column, t;
	char n[128];		/* beinhaltet [|l|l] etc. */
	
	str2tok(s);
	
	if (token_counter>0)
	{	um_strcpy(n, token[1], 128, "table_get_header[1]");
	}
	
	tab_toplines= 0;
	if (token_counter>1 && !no_table_lines)
	{	for (t=2; t<token_counter; t++)
		if (strcmp(token[2], "!hline")==0)
		{	tab_toplines++;
		}
	}
	
	token_reset();

	qdelete_all(n, "[", 1);
	qdelete_all(n, "]", 1);

	if (n[0]==EOS)
	{	return;
	}

	column= 0;
	for (i=0; i<strlen(n); i++)
	{	if (n[i]=='|' && !no_table_lines)
		{	tab_vert[column]++;
		}	else
		if (n[i]=='l')
		{	tab_just[column]= TAB_LEFT;
			column++;
		}	else
		if (n[i]=='c')
		{	tab_just[column]= TAB_CENTER;
			column++;
		}	else
		if (n[i]=='r')
		{	tab_just[column]= TAB_RIGHT;
			column++;
		}
	}
	
}	/* table_get_header */


GLOBAL BOOLEAN table_add_line ( char *s )
{
	char	*ptr;
	int		i, x;
	size_t	sl, tl;		/* strlen & toklen */

	del_whitespaces(s);

    /* Leerzeilen  und Kommentare nicht bearbeiten */
    if ( s[0]==EOS || s[0] == '#')
	{	return TRUE;
	}

	if ( tab_h >= MAX_TAB_H )
	{	error_table_height();
		s[0]= EOS;
		return FALSE;
	}

	if ((strncmp(s, "!label", 6 )==0 || strncmp(s, "!l ", 3) == 0) )
	{
		if ( tab_label[tab_h] >= MAX_TAB_LABEL )
		{	error_table_label();
			s[0]= EOS;
			return FALSE;
		}
		sl = strlen ( s );
		ptr= (char *) (um_malloc(sl+2));
		if (ptr==NULL)
		{	error_malloc_failed();
			return FALSE;
		}
		strcpy(ptr, s);
		tab_label_cell[tab_h][tab_label[tab_h]]= ptr;
		tab_label[tab_h]++;
		return TRUE;
	}

	/* Alte Zellen leeren */
	cells_reset();

	/* Zeile enthaelt nur !hline */
	if (strcmp(s, "!hline")==0)
	{	if (!no_table_lines)
		{	tab_hori[tab_h]++;
		}
		return TRUE;
	}


	/* Nun aus der Zeile die Felder auslesen */
	replace_char(s, "\t", " ");
	qdelete_all(s, "!-", 2);

	if (no_umlaute) umlaute2ascii(s);
	replace_macros(s);
		
	if (desttype!=TOTEX && desttype!=TOPDL)
	{	c_styles(s);
		check_styles(s);
	}

	switch (desttype)
	{
		case TOASC:
		case TODRC:
		case TOPCH:
		case TOMAN:
		case TOSTG:
		case TOAMG:
		case TOTVH:
		case TOSRC:
		case TOSRP:
		case TOIPF:
			c_commands_inside(s, FALSE);
			c_vars(s);
			replace_defines(s);
#if 0
			replace_udo_quotes(s);
#endif
			break;
	}
		
	c_tilde(s);

	ptr= s;
	cells_counter= 0;
	sl= 0;
	
	while ( ptr[0]!=EOS )
	{
		if (ptr[0]=='!' && ptr[1]=='!')
		{
			cells_counter++;
			ptr++;		/* PL14: +=1 statt += 2 */
			sl= 0;
		}
		else
		{
			if (sl+1<MAX_CELLS_LEN)
			{
				chrcat(cells[cells_counter], ptr[0]);
				sl++;
			}
			else
			{
				error_table_cell_width();	/*r6pl2: Laenge testen und meckern */
				return FALSE;
			}
		}
		ptr++;
	}

	for (i=0; i<=cells_counter; i++) del_whitespaces(cells[i]) ;	
	
	if ( cells_counter > MAX_TAB_W )
	{	error_table_width();
	}
	
	if ( cells_counter > tab_w )
	{	tab_w= cells_counter;
	}

	/* Zeilenzaehler hochsetzen */
	tab_h++;

	for (x=0; x<MAX_TAB_W; x++)
	{	if (x<=cells_counter)
		{
			tl= toklen(cells[x]);
			sl= strlen(cells[x]);
			if (tl>tab_cell_w[x])
			{	tab_cell_w[x]= tl;
			}
	
			ptr= (char *) (um_malloc(sl+2));
			if (ptr==NULL)
			{	error_malloc_failed();
				return FALSE;
			}
			strcpy(ptr, cells[x]);
			tab_cell[tab_h][x]= ptr;
		}
	}
	
	cells_reset();

	return TRUE;
}	/* table_add_line */



LOCAL void table_output_lyx ( void )
{
	int		y, x, i;
	BOOLEAN	bl, bt, bb, br;				/* Flags fuer Linien */
	char f[512], alignOn[64];
	BOOLEAN inside_center, inside_right, inside_left;

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);
	inside_left= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_LEFT);

	if (!inside_center && !inside_right && !inside_left)
	{
		switch (table_alignment)	/*r6pl9*/
		{
			case ALIGN_CENT:
				inside_center= TRUE;	break;
			case ALIGN_RIGH:
				inside_right= TRUE;		break;
		}
	}

	alignOn[0]= EOS;
	if (inside_center)	strcpy(alignOn, " center");
	if (inside_right)	strcpy(alignOn, " right");

	outln("\\layout Standard");
	voutlnf("\\added_space_top 0.30 \\added_space_bottom 0.30 \\align %s \\LyXTable", alignOn);
	outln("multicol2");
	voutlnf("%d %d", tab_h+1, tab_w+1);

	/* Fuer jede Tabellenzeile eine Zeile ausgeben, in der Flags stehen,	*/
	/* die angeben, ob dort obere und untere Linien benutzt werden.			*/

	for (y=0; y<=tab_h; y++)
	{
		if ( y==0 )
		{	bt= (tab_toplines>0);
			bb= (tab_hori[0]>0);
		}
		else
		{	bt= (tab_hori[y-1]>0);
			bb= (tab_hori[y]>0);
		}

		voutlnf("%d %d", bt, bb);
	}
	
	/*	Pro Spalte eine Zeile ausgeben. Beispiel:
		8 1 1
	        +---- rechts eine Linie?
		  +------ links eine Linie?
		+-------- Ausrichtung? (2=links, 8=zentriert, 4=rechts)
	*/
	
	for (x=0; x<=tab_w; x++)
	{
		bl= (tab_vert[x]>0);

		if (x==tab_w)
		{	br= (tab_vert[x+1]>0);
		}
		else
		{	br= FALSE;
		}
	
		switch(tab_just[x])
		{	case TAB_CENTER:	i= 8;	break;
			case TAB_RIGHT:		i= 4;	break;
			default:			i= 2;	break;
		}
		
		voutlnf("%d %d %d", i, bl, br);
	}
	
	/*	Pro Spalte eine Zeile ausgeben. Beispiel:
		0 8 1 1
		      +---- rechts eine Linie?
		    +------ links eine Linie?
		  +-------- Ausrichtung? (2=links, 8=zentriert, 4=rechts)
		+---------- immer 0
	*/
	
	for (x=0; x<=tab_w; x++)
	{
		switch(tab_just[x])
		{	case TAB_CENTER:	i= 8;	break;
			case TAB_RIGHT:		i= 4;	break;
			default:			i= 2;	break;
		}
		
		voutlnf("0 %d 1 1", i);
	}

#if 0
	/* Jetzt noch fuer jede Spalte 0 8 1 1 ausgeben, warum auch immer */
	for (x=0; x<=tab_w; x++)
	{	outln("0 8 1 1");
	}
#endif
	
	for (y=0; y<=tab_h; y++)
	{
		for (x=0; x<=tab_w; x++)
		{
			if ( tab_cell[y][x]!=NULL )
			{	strcpy(f, tab_cell[y][x]);
				auto_quote_chars(f, FALSE);
				c_vars(f);
				c_commands_inside(f, FALSE);
				replace_defines(f);
				replace_udo_quotes(f);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				c_internal_styles(f);
				replace_placeholders(f);
				indent2space(f);
				out(f);
			}
			
			if ( y!=tab_h || x!=tab_w)
			{	outln("\\newline");
			}
		}
	    if (tab_label[y]>0)
	    {	for (i=0; i<tab_label[y]; i++)
	    	{	if ( tab_label_cell[y][i] != NULL )
	       		{	str2tok(tab_label_cell[y][i]);
					if (token_counter>0)
						c_label();
				}
				token_reset();
	        }
	    }
	}
	
	if (tab_caption[0]!=EOS)
	{	outln("\\layout Standard");
		outln("\\align center");
		if (tab_caption_visible)
		{	sprintf(f, "%s %d: %s", lang.table, tab_counter, tab_caption);
		}
		else
		{	sprintf(f, "%s", tab_caption);
		}
    	outln(f);
    	outln("\\layout Standard");
    	outln("");
    }
                                	
}	/* table_output_lyx */


LOCAL void table_output_rtf ( void )
{
	int		y, x, i, cellx, indent, charw;
	char	f[512], cx[512];

	indent=strlen_indent();

	if (bDocRtfKeepTablesOn)
	{	outln("{\\keep\\keepn");
	}
	else
	{	outln("{\\keep");
	}

	charw= iDocCharwidth;

	for (y=0; y<=tab_h; y++)
	{
		outln("\\trowd");
		cellx= 0;
		if (indent>0)
		{	cellx= indent;
			voutlnf("\\cellx%d", cellx);
		}

		for (i=0; i<=tab_w; i++)
		{	f[0]= EOS;
			if (tab_vert[i]>0)
			{	strcat(f, "\\clbrdrl\\brdrs");
			}
			if ( tab_vert[i+1]>0 )
			{	strcat(f, "\\clbrdrr\\brdrs");
			}

			if (tab_hori[y]>0)
			{	strcat(f, "\\clbrdrb\\brdrs");
			}
			
			if ( (y==0 && tab_toplines>0) || (y>0 && tab_hori[y-1]>0) )
			{	strcat(f, "\\clbrdrt\\brdrs");
			}
			
			cellx+= ( (int) tab_cell_w[i] * charw );
			sprintf(cx, "\\cellx%d", cellx);
			voutlnf("%s%s", f, cx);
		}

		out("\\intbl");
		if (indent>0)
		{	out("\\ql \\cell");
		}

		for (x=0; x<=tab_w; x++)
		{	switch(tab_just[x])
			{	case TAB_CENTER:	out("\\qc ");	break;
				case TAB_RIGHT:		out("\\qr ");	break;
				default:			out("\\ql ");	break;
			}
			if ( tab_cell[y][x]!=NULL )
			{	strcpy(f, tab_cell[y][x]);
				auto_quote_chars(f, FALSE);
				c_vars(f);
				c_commands_inside(f, FALSE);
				replace_defines(f);
				replace_udo_quotes(f);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				c_rtf_styles(f);
				replace_placeholders(f);
				c_rtf_quotes(f);
				out(f);
			}
			out("\\cell");
		}
		outln("\\row");

	    if (tab_label[y]>0)
	    {	for (i=0; i<tab_label[y]; i++)
	    	{	if ( tab_label_cell[y][i] != NULL )
	       		{	str2tok(tab_label_cell[y][i]);
					if (token_counter>0)
						c_label();
				}
				token_reset();
	        }
	    }
	}
	
	outln("\\trowd\\pard");
	outln("}\\par\\pard");

	if (tab_caption[0]!=EOS)
	{	c_rtf_quotes(tab_caption);	/* r6pl7 */
		out("{\\keep\\trowd");
		if (indent>0)
		{	voutlnf("\\cellx%d", indent);
		}
		outln(cx);	/* Noch von oben definiert */
		out("\\intbl");
		if (indent>0)
		{	out("\\ql \\cell");
		}
		if (tab_caption_visible)
		/* Changed in r6.3pl3 [NHz] */
		{	sprintf(f, "\\qc %s {\\field{\\*\\fldinst { SEQ Tabelle \\\\* ARABIC }}{\\fldrslt %d}}: %s\\cell\\row\\pard",
							lang.table, tab_counter, tab_caption);
		} /* added closing bracket in order to get this compiled in MXVC++ r6.3.4 [vj] */
		else
		{	sprintf(f, "\\qc %s\\cell\\row\\pard", tab_caption);
		}
		outln(f);
		outln("\\trowd\\pard");
		outln("}\\par\\pard");
	}

}	/* table_output_rtf */



LOCAL void table_output_win ( void )
{
	int		y, x, i, cellx, indent, charw;
	char	f[512], cx[512], ci[512];

	indent=strlen_indent();
	cellx= 0;
	outln("{\\keep\\trowd");

	charw= iDocCharwidth;

	if (indent>0)
	{	cellx= indent;
		sprintf(ci, "\\cellx%d", cellx);	/* ci wird unten noch benoetigt! */
		outln(ci);
	}

	for (i=0; i<=tab_w; i++)
	{	cellx+= ( (int) tab_cell_w[i] * charw );
		sprintf(cx, "\\cellx%d", cellx);	/* cx wird unten noch benoetig! */
		outln(cx);
	}


	for (y=0; y<=tab_h; y++)
	{
		out("\\intbl");
		if (indent>0)
		{	out("\\ql \\cell");
		}
		if (tab_toplines>0)
		{	out("{\\box");
		}
		for (x=0; x<=tab_w; x++)
		{	switch(tab_just[x])
			{	case TAB_CENTER:	out("\\qc ");	break;
				case TAB_RIGHT:		out("\\qr ");	break;
				default:			out("\\ql ");	break;
			}
			if ( tab_cell[y][x]!=NULL )
			{	strcpy(f, tab_cell[y][x]);
				auto_quote_chars(f, FALSE);
				c_vars(f);
				c_commands_inside(f, FALSE);
				replace_defines(f);
				replace_udo_quotes(f);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				c_win_styles(f);
				auto_references(f, FALSE, "", 0, 0);
				replace_placeholders(f);
				out(f);
			}
			out("\\cell");
		}

		if (tab_toplines>0)
		{	outln("\\row\\pard}");
		}
		else
		{	outln("\\row");
		}

	    if (tab_label[y]>0)
	    {	for (i=0; i<tab_label[y]; i++)
	    	{	if ( tab_label_cell[y][i] != NULL )
	       		{	str2tok(tab_label_cell[y][i]);
					if (token_counter>0)
						c_label();
				}
				token_reset();
	        }
	    }
	}
	
	outln("\\trowd\\pard");
	outln("}\\par\\pard");

	if (tab_caption[0]!=EOS)
	{	out("{\\keep\\trowd");
		if (indent>0)
		{	out(ci);	/* Noch von oben definiert */
		}
		outln(cx);	/* Noch von oben definiert */
		out("\\intbl");
		if (indent>0)
		{	out("\\ql \\cell");
		}
		if (tab_caption_visible)
		{	sprintf(f, "\\qc %s %d: %s\\cell\\row\\pard",
							lang.table, tab_counter, tab_caption);
		}
		else
		{	sprintf(f, "\\qc %s\\cell\\row\\pard", tab_caption);
		}
		outln(f);
		outln("\\trowd\\pard");
		outln("}\\par\\pard");
	}

}	/* table_output_win */

LOCAL void test_for_addition(char *cell)
{
	char *found2 = NULL, *tok = NULL;
	size_t clen;

	if (cell[0]=='[') cell=&cell[1]; /* Eat leading [ */
	clen=strlen(cell); /* Get length of Cell */
	if (clen==0) return; /* Empty string? -> Return */
	if (cell[clen-1]==']') cell[clen-1]=EOS; /* Eat tailing ] */
	if (cell[0]==0) return; /* Empty string? -> Return */
	/* Now we have to see, if there are entries */
	tok = strtok(cell, " ,\t"); /* The whitespace, colon, or tab are seperators */
	while(tok)
	{
		found2 = strstr(tok, "COLS=");
		if(found2 != NULL)
		{	um_strcat(addition, " colspan=\"", TAB_ADDITION_LEN, "test_for_addition[1]");
			addition_col_offset=atoi(found2+5);
			um_strncat(addition, found2+5, 2L, TAB_ADDITION_LEN, "test_for_addition[2]");
			um_strcat(addition, "\"", TAB_ADDITION_LEN, "test_for_addition[3]");
		}

		found2 = strstr(tok, "BGC=");
		if(found2 != NULL)
		{	um_strcat(addition, " bgcolor=\"", TAB_ADDITION_LEN, "test_for_addition[4]");
			um_strcat(addition, found2+4, TAB_ADDITION_LEN, "test_for_addition[5]");
			um_strcat(addition, "\"", TAB_ADDITION_LEN, "test_for_addition[6]");
		}

		found2 = strstr(tok, "HA=");
		if(found2 != NULL)
		{	um_strcat(addition, " align=\"", TAB_ADDITION_LEN, "test_for_addition[7]");
			um_strcat(addition, found2+3, TAB_ADDITION_LEN, "test_for_addition[8]");
			um_strcat(addition, "\"", TAB_ADDITION_LEN, "test_for_addition[9]");
			addition_has_align=TRUE;
		}

		found2 = strstr(tok, "VA=");
		if (found2 != NULL)
		{
			um_strcat(addition, " valign=\"", TAB_ADDITION_LEN, "test_for_addition[10]");
			um_strcat(addition, found2+3, TAB_ADDITION_LEN, "test_for_addition[11]");
			um_strcat(addition, "\"", TAB_ADDITION_LEN, "test_for_addition[12]");
			addition_has_valign=TRUE;
		}

		tok = strtok(NULL, ",");
	}
}	/* test_for_addition */

LOCAL void table_output_html ( void )
{
	int		y, x, i;
	char	f[LINELEN], alignOn[64]; /* r6.3.18[vj]: f is now LINELEN chars long instead of 512 */
	char	token_buffer[LINELEN];	 /* v6.5.3[vj]: New buffer needed for table extension */
	BOOLEAN inside_center, inside_right, inside_left;

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);
	inside_left= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_LEFT);

	if (!inside_center && !inside_right && !inside_left)
	{
		switch (table_alignment)	/*r6pl9*/
		{
			case ALIGN_CENT:	inside_center= TRUE;	break;
			case ALIGN_RIGH:	inside_right= TRUE;		break;
		}
	}

	strcpy(alignOn, "left");
	if (inside_center)	um_strcpy(alignOn, "center", 64, "table_output_html[1]");
	if (inside_right)	um_strcpy(alignOn, "right", 64, "table_output_html[2]");

	voutf("<div align=\"%s\">", alignOn);

	if (tab_toplines>0)
	{	outln("<table border=\"1\" frame=\"box\">");
	}
	else
	{	outln("<table border=\"0\">");
	}

	if (tab_caption[0]!=EOS)
	{
		if (tab_caption_visible)
		{	voutlnf("<caption align=\"bottom\">%s %d: %s</caption>", lang.table, tab_counter, tab_caption);
		}
		else
		{	voutlnf("<caption align=\"bottom\">%s</caption>", tab_caption);
		}
	}

	for (y=0; y<=tab_h; y++)
	{	outln("<tr>");
		for (x=0; x<=tab_w; x++)
		{	/* New in r6pl16 [NHz] */

			char *found = NULL; /*, *token = NULL;*/
			size_t tokposition;

			addition[0] = EOS; /* addition takes the extra options per cell, so it needs to be cleaned */
			token_buffer[0] = EOS; /* This is the buffer where we keep the per cell format information */
			/* This BOOLEAN flags are possibly set in test_for_addition */
			addition_has_align=FALSE;
			addition_has_valign=FALSE;
			addition_col_offset=0;

			/* some tables have empty cells, so always check befor using tab_cell entries */
			if (tab_cell[y][x]!=NULL)
			    found = strstr(tab_cell[y][x], "!?");

			if(found != NULL)
			{
				tokposition=strcspn(tab_cell[y][x], "!");
				um_strncpy(token_buffer, tab_cell[y][x], tokposition, MAX_TOKEN_LEN+1, "table_output_html[3]"); /* <???> Pufferüberlauf möglich? Wie groß kann hier token wirklich sein? */
				token_buffer[tokposition]=EOS;

				del_whitespaces (token_buffer); /* Delete Whitespaces before checking for additions */
				test_for_addition(token_buffer);

				tab_cell[y][x] = found+2;

			}

			/*switch(tab_just[x])
			{	case TAB_CENTER:	voutf("  <td align=\"center\" valign=\"top\"%s>", addition);	break;
				case TAB_RIGHT:		voutf("  <td align=\"right\" valign=\"top\"%s>", addition);	break;
				default:			voutf("  <td align=\"left\" valign=\"top\"%s>", addition);	break;
			}*/
			/* Everything not set in test_for_addition is now set here */
			switch(tab_just[x])
			{	case TAB_CENTER:	if (!addition_has_align) um_strcat(addition, " align=\"center\"", TAB_ADDITION_LEN, "table_output_html[3-1-0]");
									if (!addition_has_valign) um_strcat(addition, " valign=\"top\"", TAB_ADDITION_LEN, "table_output_html[3-1-1]");
									break;
				case TAB_RIGHT:		if (!addition_has_align) um_strcat(addition, " align=\"right\"", TAB_ADDITION_LEN, "table_output_html[3-1-2]");
									if (!addition_has_valign) um_strcat(addition, " valign=\"top\"", TAB_ADDITION_LEN, "table_output_html[3-1-3]");
									break;
				default:			if (!addition_has_align) um_strcat(addition, " align=\"left\"", TAB_ADDITION_LEN, "table_output_html[3-1-4]");
									if (!addition_has_valign) um_strcat(addition, " valign=\"top\"", TAB_ADDITION_LEN, "table_output_html[3-1-5]");
									break;
			}
			voutf("  <td%s>", addition);
			/* If there is a colspan, we need to supress empty cols */
			if (addition_col_offset>0) x=x+addition_col_offset-1;
			out(sHtmlPropfontStart);
			if ( tab_cell[y][x]!=NULL )
			{	um_strcpy(f, tab_cell[y][x], LINELEN, "table_output_html[4]");
				auto_quote_chars(f, FALSE);
				replace_defines(f);
				c_commands_inside(f, FALSE);
				replace_udo_quotes(f);
				c_vars(f);
				c_internal_styles(f);
				auto_references(f, FALSE, "", 0, 0);	/* PL7 <???> */
				replace_placeholders(f);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				out(f);
			}
			out(sHtmlPropfontEnd);
			outln("</td>");	/* PL14: "</td>" statt " " */
		}
		outln("</tr>");		/* PL14: "</tr>" statt "" */

	    if (tab_label[y]>0)
	    {	for (i=0; i<tab_label[y]; i++)
	    	{	if ( tab_label_cell[y][i] != NULL )
	       		{	str2tok(tab_label_cell[y][i]);
					if (token_counter>0)
						c_label();
				}
				token_reset();
	        }
	    }
	}


	outln("</table></div>");

}	/* table_output_html */


LOCAL void table_output_tex ( void )
{
	int		y, x, i;
	char	f[512], alignOn[64], alignOff[64];
	BOOLEAN inside_center, inside_right, inside_left;

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);
	inside_left= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_LEFT);

	if (!inside_center && !inside_right && !inside_left)
	{
		switch (table_alignment)	/*r6pl9*/
		{
			case ALIGN_CENT:
				inside_center= TRUE;	break;
			case ALIGN_RIGH:
				inside_right= TRUE;		break;
		}
	}

	alignOn[0]= alignOff[0]= EOS;
	if (inside_center)
	{
		strcpy(alignOn, "\\begin{center}");
		strcpy(alignOff, "\\end{center}");
	}
	if (inside_right)
	{
		strcpy(alignOn, "\\begin{flushright}");
		strcpy(alignOff, "\\end{flushright}");
	}

#if 1
	if (tab_caption[0]!=EOS)	/* PL7 */
	{	outln("\\begin{table}[htb]");
	}
#else
	outln("\\begin{table}[htb]");
#endif
	
	outln(alignOn);

	out("\\begin{tabular}{");
	for (x=0; x<=tab_w; x++)
	{	if (tab_vert[x]>0)
		{	for (i=1; i<=tab_vert[x]; i++) out("|") ;
		}
		switch(tab_just[x])
		{	case TAB_CENTER:	out("c");	break;
			case TAB_RIGHT:		out("r");	break;
			default:			out("l");	break;
		}
	}
	if (tab_vert[tab_w+1]>0)
	{	for (i=1; i<=tab_vert[tab_w+1]; i++) out("|") ;
	}
	out("}");

	if (tab_toplines>0)	
	{	for (y=1; y<=tab_toplines; y++)
		{	out(" \\hline");
		}
	}
	outln("");

	for (y=0; y<=tab_h; y++)
	{	for (x=0; x<=tab_w; x++)
		{	if ( tab_cell[y][x]!=NULL )
			{	strcpy(f, tab_cell[y][x]);
				auto_quote_chars(f, FALSE);
				c_styles(f);
				check_styles(f);
				replace_defines(f);
				c_commands_inside(f, FALSE);
				c_vars(f);
				replace_udo_quotes(f);
				c_internal_styles(f);
				replace_placeholders(f);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				indent2space(f);
				out(f);
			}
			if (x!=tab_w)
			{	out(" & ");
			}
		}
		out(" \\\\");
		if (tab_hori[y]>0)
		{	out(" \\hline");
		}
		outln("");

	    if (tab_label[y]>0)
	    {	for (i=0; i<tab_label[y]; i++)
	    	{	if ( tab_label_cell[y][i] != NULL )
	       		{	str2tok(tab_label_cell[y][i]);
					if (token_counter>0)
						c_label();
				}
				token_reset();
	        }
	    }
	}

	outln("\\end{tabular}");

	if (tab_caption[0]!=EOS)
	{	voutlnf("\\caption{%s}", tab_caption);
	}

	outln(alignOff);

#if 1
	if (tab_caption[0]!=EOS)	/* PL7 */
	{	outln("\\end{table}");
	}
#else
	outln("\\end{table}");
#endif

}	/* table_output_tex */


LOCAL void table_output_ipf ( void )
{
	int		y, x, i/*, cellx, indent, charw*/;
	char	f[512], cx[512]/*, ci[512]*/;

	f[0]= EOS;
	for (i=0; i<=tab_w; i++)
	{
#ifdef UM_PRINTF_USE_LD
		sprintf(cx, "%u ", tab_cell_w[i]);
#else
		sprintf(cx, "%lu ", tab_cell_w[i]);
#endif
		strcat(f, cx);
	}
	del_whitespaces(f);
	voutlnf(":table cols='%s'.", f);


	for (y=0; y<=tab_h; y++)
	{
		outln(":row.");
		for (x=0; x<=tab_w; x++)
		{
#if 0
			switch(tab_just[x])
			{	case TAB_CENTER:	out("\\qc ");	break;
				case TAB_RIGHT:		out("\\qr ");	break;
				default:			out("\\ql ");	break;
			}
#endif
			if ( tab_cell[y][x]!=NULL )
			{	strcpy(f, tab_cell[y][x]);
				auto_quote_chars(f, FALSE);
				replace_defines(f);
				c_commands_inside(f, FALSE);
				replace_udo_quotes(f);
				c_vars(f);
				c_internal_styles(f);
				auto_references(f, FALSE, "", 0, 0);
				replace_placeholders(f);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				voutlnf(":c.%s", f);
			}
			else
			{	outln(":c.");
			}
		}

	}

	outln(":etable.");
	
}	/* table_output_ipf */


LOCAL void table_output_general ( void )
{
    int     y, x, i, j, offset, indent=0, y_stg;
    char    s[512], f[512], stg_vl[32];
    char    hl[3][512], space[50];
    char    hl_l[3][2], hl_c[3][2], hl_v[3][2], hl_r[3][2];
    char    vc_l[2], vc_m[2], vc_r[2];
    size_t  tl, add, twidth, toffset=1, isl;
    BOOLEAN tortf, tosrc, ansichars, align_caption;
    BOOLEAN inside_center, inside_right, inside_left;

    inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);
    inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);
    inside_left= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_LEFT);

    /* New in r6pl15 [NHz] */
    for(j=1;j<=iEnvLevel;j++)
    {
        if(iEnvType[j] == ENV_CENT)
            inside_center = TRUE;
        if(iEnvType[j] == ENV_RIGH)
            inside_right = TRUE;
        if(iEnvType[j] == ENV_LEFT)
            inside_left = TRUE;
    }

    if (!inside_center && !inside_right && !inside_left)
    {
        switch (table_alignment)    /*r6pl9*/
        {
            case ALIGN_CENT:
                inside_center= TRUE;    break;
            case ALIGN_RIGH:
                inside_right= TRUE;     break;
            default:
                indent=strlen_indent(); break;
        }
    }
    /* New in r6pl15 [NHz] */
    else if(inside_left == TRUE)
        indent=strlen_indent();

    /* New in r6pl15 [NHz] */
    /* If the table is inside an environment */
    space[0] = EOS;
    if(indent > 0)
    {
        for(i=0;i<indent;i++)
            strcat(space, " ");
    }

    
    /* PL7: MAXZEILE durch zDocParwidth ersetzt */
    
    tortf= (desttype==TORTF || desttype==TOWIN || desttype==TOWH4 || desttype==TOAQV);
    tosrc= (desttype==TOSRC || desttype==TOSRP);


    ansichars= FALSE;

    if (use_ansi_tables)
    {
       if (desttype!=TOWIN && desttype!=TOWH4 && desttype!=TOAQV && desttype!=TORTF && desttype!=TOINF)
        {   ansichars= TRUE;
        }
    }
    
    if (tortf || desttype==TOINF || desttype==TOLDS)
    {   output_begin_verbatim();
    }

    outln("");
    
    if (tosrc)
    {   outln(sSrcRemOn);
    }

    if ((desttype==TOSTG || desttype==TOAMG) && !ansichars)
    {   /* Tabellenbreite fuer den ST-Guide berechnen und in <hl[1]> */
        /* den Befehl zum Zeichnen von horizontalen Linien einsetzen */
        twidth= 0;
        toffset= 1;
        for (x=0; x<=tab_w; x++)    twidth+= ((int) tab_cell_w[x]+2) ;
        if (twidth<=zDocParwidth)
        {
            if (inside_center)
            {   toffset= (zDocParwidth-twidth)/2 + 1;
            }
            if (inside_right)
            {   toffset= zDocParwidth-twidth+1;
            }
            if (indent > 0)
            {   toffset= indent+1;
            }
        }
        if ( twidth > 126 )				/* ST-Guide kennt Linien nur mit einer 	*/
        {								/* Breite von max 126 Zeichen		 	*/
        	i = (int) twidth;
        	twidth = 126;
   	        sprintf(hl[1], "@line %d %d 0", (int) toffset, (int) twidth);
			i -= 126;
			x = (int)toffset + 126;
			while ( i > 0 )
			{
				if ( i > 126 )
					twidth = 126;
				else
					twidth = i;
				j = (int)strlen ( hl[1] );
		        sprintf(&hl[1][j], "\n@line %d %d 0", (int) x, (int) twidth);
				i -= (int)twidth;
				x += (int)twidth;
				if ( x > 255 )			/* Max X-Position	*/
					break;
			}
        }
        else
	        sprintf(hl[1], "@line %d %d 0", (int) toffset, (int) twidth);
        strcpy(hl[0], hl[1]);
        strcpy(hl[2], hl[1]);

        /* Befehle fuer vertikale Linien erzeugen */
        offset= (int) toffset;
        for (x=0; x<=tab_w; x++)
        {   if (tab_vert[x]>0)
            {
                if( tab_h>253 )
                   sprintf(stg_vl, "@line %d 0 %d", offset, 254);
                else
                	sprintf(stg_vl, "@line %d 0 %d", offset, tab_h+1);
                outln(stg_vl);
            }
            offset+= (int) tab_cell_w[x];
            offset+= 2;
        }
        if (tab_vert[tab_w+1]>0)
        {
            if( tab_h>253 )
            	sprintf(stg_vl, "@line %d 0 %d", offset, 254);
            else
            	sprintf(stg_vl, "@line %d 0 %d", offset, tab_h+1);
            outln(stg_vl);
        }
        strcpy(vc_l, "");
        strcpy(vc_m, "");
        strcpy(vc_r, "");
        if (tab_toplines>0)
        {   outln(hl[1]);
        }
    }
    else
    {   /* Zeichen fuer die Trennlinie(n) setzen        */
        /* Bei MSDOS wird der Grafikzeichensatz benutzt */

        if (ansichars)
        {   strcpy(hl_l[0], "\311");    /*  ||= */  /* Top */
            strcpy(hl_r[0], "\273");    /*  =|| */
            strcpy(hl_v[0], "\321");    /*  =|= */
            strcpy(hl_c[0], "\315");    /*  =   */
            strcpy(hl_l[1], "\307");    /* ||-  */  /* Middle */
            strcpy(hl_r[1], "\266");    /* -||  */
            strcpy(hl_v[1], "\305");    /*  -|- */
            strcpy(hl_c[1], "\304");    /*  -   */
            strcpy(hl_l[2], "\310");    /* ||=  */  /* Bottom */
            strcpy(hl_r[2], "\274");    /* =||  */
            strcpy(hl_v[2], "\317");    /*  =|= */
            strcpy(hl_c[2], "\315");    /*  =   */

            strcpy(vc_l, "\272");
            strcpy(vc_m, "\263");
            strcpy(vc_r, "\272");
        }
        else
        {   strcpy(hl_l[0], "+");   /* Top */
            strcpy(hl_r[0], "+");
            strcpy(hl_v[0], "+");
            strcpy(hl_c[0], "-");
            strcpy(hl_l[1], "+");   /* Middle */
            strcpy(hl_r[1], "+");
            strcpy(hl_v[1], "+");
            strcpy(hl_c[1], "-");
            strcpy(hl_l[2], "+");   /* Bottom */
            strcpy(hl_r[2], "+");
            strcpy(hl_v[2], "+");
            strcpy(hl_c[2], "-");

            strcpy(vc_l, "|");
            strcpy(vc_m, "|");
            strcpy(vc_r, "|");
        }

        /* ----------------------------- */
        /* Trennlinie(n) zusammenstellen */
        /* 0= top, 1=middle, 2=bottom    */
        /* ----------------------------- */

        for (y=0; y<3; y++)
        {   
            hl[y][0]= EOS;

            /* New in r6pl15 [NHz] */
            strcat(hl[y], space);

            /* New in r6pl15 [NHz] */
            /* Begin of a table-line in postscript */
            if (desttype==TOKPS)
                strcat(hl[y], "Von (");

            for (x=0; x<=tab_w; x++)
            {   if (tab_vert[x]>0)
                {   if (x==0)
                    {   for (i=1; i<=tab_vert[x]; i++)
                        {   strcat(hl[y], hl_l[y]);
                        }
                    }
                    else
                    {   for (i=1; i<=tab_vert[x]; i++)
                        {   strcat(hl[y], hl_v[y]);
                        }
                    }
                }
                strcat(hl[y], hl_c[y]);
                for (isl=1; isl<=tab_cell_w[x]; isl++)
                {   strcat(hl[y], hl_c[y]);
                }
                strcat(hl[y], hl_c[y]);
            }
            if (tab_vert[tab_w+1]>0)
            {   for (i=1; i<=tab_vert[tab_w+1]; i++)
                {   if (i==tab_vert[tab_w+1])
                    {   strcat(hl[y], hl_r[y]);
                    }
                    else
                    {   strcat(hl[y], hl_v[y]);
                    }
                }
            }
            
            /* New in r6pl15 [NHz] */
            /* Conclusion of a table-line in postscript */
            if (desttype==TOKPS)
                strcat(hl[y], ") udoshow newline Voff");

            if (inside_center)
            {   stringcenter(hl[y], zDocParwidth);  /* Linie fuer den Rest zentrieren */
            }
            if (inside_right)
            {   strright(hl[y], zDocParwidth);      /* Linie fuer den Rest ausrichten */
            }
            if (tortf)  strcat(hl[y], "\\par");
            if (tosrc)  strinsert(hl[y], "    ");
        }


        /* obere Tabellenlinien ausgeben */     
        if (tab_toplines>0)
        {   for (i=1; i<=tab_toplines; i++)
            {   if (i==1)
                {   outln(hl[0]);
                }
                else
                {   outln(hl[1]);
                }
            }
        }
    }
    

    for( y=0, y_stg=0 ; y<=tab_h ; y++, y_stg++ )
    {   s[0]= EOS;
			
        if ( y_stg > 253 && (desttype==TOSTG || desttype==TOAMG) && !ansichars)
        {
            /* ST-Guide kann nur Linien mit einer Laenge von 254 Zeilen */
            /* zeichen. Deshalb wird hier eine Anschlussline gezeichnet */
        
            offset= (int) toffset;
            y_stg = tab_h - y;
            if ( y_stg > 253 )
                y_stg = 253;
            for (x=0; x<=tab_w; x++)
            {   if (tab_vert[x]>0)
                {   sprintf(stg_vl, "@line %d 0 %d", offset, y_stg+1);
                    outln(stg_vl);
                }
                offset+= (int) tab_cell_w[x];
                offset+= 2;
            }
        
            if (tab_vert[tab_w+1]>0)
            {   sprintf(stg_vl, "@line %d 0 %d", offset, y_stg+1);
            }
            outln(stg_vl);
            
            y_stg = 0;
        }
        
        /* New in r6pl15 [NHz] */
        strcat(s, space);

        /* New in r6pl15 [NHz] */
        /* Begin of a table-line in postscript */
        if (desttype==TOKPS)
            strcat(s, "Von (");

        for (x=0; x<=tab_w; x++)
        {
            if (tab_vert[x]>0)
            {   for (i=1; i<=tab_vert[x]; i++)
                {   (x==0) ? strcat(s, vc_l) : strcat(s, vc_m);
                }
            }

            strcat(s, " ");

            f[0]= EOS;
            if (tab_cell[y][x]!=NULL)
            {   strcpy(f, tab_cell[y][x]);
            }

            add= 0;

						/* New in V6.5.11 [NHz] */
						if(desttype==TOKPS)
						{
							c_vars(f);
							c_commands_inside(f, FALSE);
							replace_all(s, "[", "\\[");
							replace_all(s, "]", "\\]");
							replace_all(s, "(", "\\(");
							replace_all(s, ")", "\\)");
						}

            switch(tab_just[x])
            {   case TAB_CENTER:
                    stringcenter(f, ((int) tab_cell_w[x]) );
                    strcat(s, f);
                    tl= toklen(f);
                    if (tab_cell_w[x] > tl) add=tab_cell_w[x]-tl;
                    if (add>0)  for (isl=0; isl<add; isl++) strcat(s, " ") ;
                    break;
                case TAB_RIGHT:
                    tl=toklen(f);
                    if (tab_cell_w[x] > tl) add=tab_cell_w[x]-tl;
                    if (add>0)  for (isl=0; isl<add; isl++) strcat(s, " ") ;
                    strcat(s, f);
                    break;
                default:    /* TAB_LEFT */
                    strcat(s, f);
                    tl=toklen(f);
                    if (tab_cell_w[x] > tl) add=tab_cell_w[x]-tl;
                    if (add>0)  for (isl=0; isl<add; isl++) strcat(s, " ") ;
                    break;
            }
            
            strcat(s, " ");
        }   /* for x */
        
        if (tab_vert[tab_w+1]>0)
        {   for (i=1; i<=tab_vert[tab_w+1]; i++)
            {   (i==tab_vert[tab_w+1]) ? strcat(s, vc_r) : strcat(s, vc_m);
            }
        }

        /* Changed in r6pl16 [NHz] */
				/* Displaced because of a bug */
        /* Conclusion of a table-line in postscript */
        if (desttype==TOKPS)
            strcat(s, ") udoshow newline Voff");

        if (inside_center)
        {   stringcenter(s, zDocParwidth);
        }

        if (inside_right)
        {   strright(s, zDocParwidth);
        }

			/* Changed in r6pl15 [NHz] */
			/* Parenthesis of table lines would be quoted \( */
        if(desttype != TOKPS)
            auto_quote_chars(s, FALSE);
        switch(desttype)
        {
            case TOWIN:
            case TOWH4:
            case TOAQV:
            case TORTF:
            case TOLDS: /* PL8 */
                c_vars(s);
                c_commands_inside(s, FALSE);
                break;
        }
        replace_defines(s);
        replace_udo_quotes(s);
        switch (desttype)
        {   case TOWIN:
            case TOWH4:
            case TOAQV: c_win_styles(s);        break;
            case TORTF: c_rtf_styles(s);        break;
            case TOLDS: del_internal_styles(s); break;  /* PL15*/
            default:    c_internal_styles(s);
        }
        replace_placeholders(s);
        replace_udo_tilde(s);
        replace_udo_nbsp(s);

        if (tortf)  strcat(s, "\\par");
        if (tosrc)  strinsert(s, "    ");

        outln(s);
        
        if (tab_hori[y]>0)
        {   for (i=1; i<=tab_hori[y]; i++)
            {   if (y==tab_h && i==tab_hori[y])
                {   outln(hl[2]);
                }
                else
                {   outln(hl[1]);
                }
            }
        }

	    if (tab_label[y]>0)
	    {	for (i=0; i<tab_label[y]; i++)
	    	{	if ( tab_label_cell[y][i] != NULL )
	       		{	str2tok(tab_label_cell[y][i]);
					if (token_counter>0)
						c_label();
				}
				token_reset();
	        }
	    }
    }   /* for y */

    if (tosrc)
    {   outln(sSrcRemOff);
    }

    if (tab_caption[0]!=EOS)
    {   if (tortf)
        {   outln(rtf_par);
        }
        else
        {   outln("");
        }
        
        /* PL7: Caption wird wie bei LaTeX nur zentriert, wenn sie  */
        /* kuerzer als die Absatzbreite ist.                        */
        
        token_reset();
        align_caption= (strlen(tab_caption)<zDocParwidth);

        if (align_caption)
        {   s[0]= EOS;
            if (inside_center)  strcpy(s, CMD_BEGIN_CENTER);
            if (inside_right)   strcpy(s, CMD_BEGIN_RIGHT);
            tokenize(s);
            if (tab_caption_visible)
            {   sprintf(s, "%s %d: %s", lang.table, tab_counter, tab_caption);
            }
            else
            {   strcpy(s, tab_caption);
            }
            tokenize(s);
            s[0]= EOS;
            if (inside_center)  strcpy(s, CMD_END_CENTER);
            if (inside_right)   strcpy(s, CMD_END_RIGHT);
            tokenize(s);
            token_output(TRUE);
        }
        else
        {
            if (tab_caption_visible)
            {   sprintf(s, "%s %d: %s", lang.table, tab_counter, tab_caption);
            }
            else
            {   strcpy(s, tab_caption);
            }
            tokenize(s);
            token_output(TRUE);
        }
    }

    if (tortf)
    {   outln(rtf_par);
    }

    if (tortf || desttype==TOINF || desttype==TOLDS)
    {   output_end_verbatim();
    }

}   /* table_output_general */



GLOBAL void table_output ( void )
{
	tab_counter++;
	
	switch (desttype)
	{	case TOHTM:
		case TOMHH:
			table_output_html();
			break;
		case TOTEX:
		case TOPDL:
			table_output_tex();	
			break;
		case TOAQV:
		case TOWIN:
		case TOWH4:
			table_output_win();
			break;
		case TORTF:
			if (bDocNoTables)
			{	table_output_general();
			}
			else
			{	table_output_rtf();
			}
			break;
		case TOLYX:
			table_output_lyx();
			break;
		case TOIPF:
			table_output_ipf();
			break;
		default:
			table_output_general();
			break;
	}
	
	table_reset();
	tab_caption[0]= EOS;
	tab_caption_visible= FALSE;
	token_reset();
	check_styleflags();

}	/* table_output */


/*	############################################################
	# Tabellen-Zaehler veraendern
	############################################################	*/
GLOBAL void set_table_counter ( const int i )
{
	tab_counter= i-1;
	if (tab_counter<0)
	{	tab_counter= 0;
	}
}


/*	############################################################
	# Diverses
	############################################################	*/
GLOBAL void set_table_alignment ( void )
{
	char s[256];

	tokcpy2(s, 256);

	if (strstr(s, "center")!=NULL)
	{	table_alignment= ALIGN_CENT;
		return;
	}

	if (strstr(s, "left")!=NULL)
	{	table_alignment= ALIGN_LEFT;
		return;
	}

	if (strstr(s, "right")!=NULL)
	{	table_alignment= ALIGN_RIGH;
		return;
	}

}	/* set_table_alignment */


/*	############################################################
	# Modulinit
	############################################################	*/

GLOBAL void init_module_tab ( void )
{
	tab_counter=		0;
	tab_caption[0]=		EOS;
	tab_caption_visible= FALSE;
}

/*	############################################################
	# tab.c
	############################################################	*/
