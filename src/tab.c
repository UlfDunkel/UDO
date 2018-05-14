/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : tab.c
*  Symbol prefix: tab
*
*  Description  : Tabellensatz (seit Release 4 Version 0.42)
*
*  Copyright    : 1995-2001 Dirk Hagedorn
*  Open Source  : since 2001
*
*                 This program is free software; you can redistribute it and/or
*                 modify it under the terms of the GNU General Public License
*                 as published by the Free Software Foundation; either version 2
*                 of the License, or (at your option) any later version.
*
*                 This program is distributed in the hope that it will be useful,
*                 but WITHOUT ANY WARRANTY; without even the implied warranty of
*                 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*                 GNU General Public License for more details.
*
*                 You should have received a copy of the GNU General Public License
*                 along with this program; if not, write to the Free Software
*                 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
*-------------------------------------------------------------------------------
*
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Norbert Hanz (NHz), Ulf Dunkel (fd), Gerhard Stoll (ggs)
*  Write access : NHz, fd, ggs
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : ???
*
*-------------------------------------------------------------------------------
*  History:
*
*  1995:
*    DH  Jan xx: introduced
*  2001:
*    DH  Oct 02: last DH version
*  2008:
*    fd  Nov 28: MAX_CELLS_LEN increased from 1024 to 4096
*  2010:
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*    fd  Feb 17: umlaute2sys() merged into recode_chrtab()
*    fd  Feb 25: - file tidied up
*                - table_add_line() handled Universal Characters now
*    fd  Feb 27: table_output_html(): additional feed before table output when
*                  inside other environments
*    ggs Feb 27: MAX_TAB_H increased from 600 to 700
*    fd  Mar 04: table_output_html(): bEnvShort[] -> bEnvCompressed[]
*    ggs Mar 21: table_output_general(): In ST-Guide the lines will be display
*                  if the with is greater than zDocParwidth.
*    ggs Apr 06: Rename MAX_TAB_W -> MAX_TAB_ROWS
*                table_add_line() is a little bit faster now.
*    ggs Apr 21: convert_table_caption(): Use MAXTABCAPTION for the string define
*    fd  May 21: new: label* | l*  (#90)
*  2013:
*    tho Jun 21: dynamically allocate table.caption
*  2013:
*    fd  Oct 23: HTML output now supports HTML5
*  2014:
*    fd  Jun 25: table_output_html() must not output multiple CSS class definitions in HTML5
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udoport.h"
#include "version.h"
#include "constant.h"
#include "udointl.h"
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
#include "lang.h"
#include "udomem.h"

#include "export.h"
#include "tab.h"





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define MAX_TAB_H        2048			/* max. Hoehe einer Tabelle */
#define MAX_TAB_W          64           /* max. Spalten einer Tabelle */
#define MAX_TAB_LABEL      10           /* max. Anzahl der hinter einanderfolgenden Labels */
#define TAB_LEFT            0           /* Spalte linksbuendig */
#define TAB_CENTER          1           /* Spalte zentriert */
#define TAB_RIGHT           2           /* Spalte rechtsbuendig */
#define TAB_TOP             3
#define TAB_BOTTOM          4


struct table_cell {
	char *text;
	int colspan;
	int halign;
	int valign;
	struct rgb_and_color bg;
};

struct table_row
{
	struct table_cell cell[MAX_TAB_W];				/* text of a cell */
	int horizontal_bar;
	int num_labels;						/* how many labels are used */
	char *label[MAX_TAB_LABEL];			/* for labels */
};

struct table
{
	int width;							/* max number of columns in any row */
	int height;							/* number of rows */
	struct table_row row[MAX_TAB_H];
	int col_justification[MAX_TAB_W];	/* justification of columns, specified in !begin_table */
	size_t cell_width[MAX_TAB_W];		/* width of the columns, as toklen() */
	int vertical_bar[MAX_TAB_W + 1];	/* number of vertical lines to put before column */
	char *caption;						/* Tabellen-Ueberschrift */
	_BOOL caption_visible;				/* wether caption appears in list_of_tables */
	int toplines;						/* horizontal bar above table? */
};

LOCAL int tab_counter;					/* Tabellen-Zaehler                     */

static struct table table;




/*******************************************************************************
*
*     FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  table_reset():
*     resets all table arrays
*
*  Return:
*     -
*
******************************************|************************************/

static void table_reset(void)
{
	int x, y;

	table.width = 0;
	table.height = 0;

	for (y = 0; y < MAX_TAB_H; y++)
	{
		for (x = 0; x < MAX_TAB_W; x++)
		{
			if (table.row[y].cell[x].text != NULL)
			{
				free(table.row[y].cell[x].text);
				table.row[y].cell[x].text = NULL;
			}
			table.row[y].cell[x].halign = TAB_CENTER;
			table.row[y].cell[x].valign = TAB_TOP;
			table.row[y].cell[x].colspan = 0;
			table.row[y].cell[x].bg.rgb.set = FALSE;
			table.row[y].cell[x].bg.color = BC_NONE;
		}

		table.row[y].horizontal_bar = 0;
		table.row[y].num_labels = 0;

		for (x = 0; x < MAX_TAB_LABEL; x++)
		{
			if (table.row[y].label[x] != NULL)
			{
				free(table.row[y].label[x]);
				table.row[y].label[x] = NULL;
			}
		}
	}

	for (x = 0; x < MAX_TAB_W; x++)
	{
		table.cell_width[x] = 0;
		table.vertical_bar[x] = 0;
		table.col_justification[x] = TAB_LEFT;
	}
	table.vertical_bar[MAX_TAB_W] = 0;

	table.toplines = 0;

	free(table.caption);
	table.caption = NULL;
	table.caption_visible = FALSE;
}





/*******************************************************************************
*
*  convert_table_caption():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void convert_table_caption(const _BOOL visible)
{
	char n[LINELEN + 1];

	tokcpy2(n, sizeof(n));

	convert_tilde(n);
	delete_all_divis(n);
	replace_udo_quotes(n);
	replace_placeholders(n);

	free(table.caption);
	table.caption = strdup(n);
	table.caption_visible = visible;
}





/*******************************************************************************
*
*	c_table_caption():
*		wrapper for convert_table_caption()
*
*	Return:
*		-
*
******************************************|************************************/

GLOBAL void c_table_caption(void)
{
	convert_table_caption(TRUE);
}





/*******************************************************************************
*
*	c_table_caption_nonr():
*		wrapper for convert_table_caption()
*
*	Return:
*		-
*
******************************************|************************************/

GLOBAL void c_table_caption_nonr(void)
{
	convert_table_caption(FALSE);
}





/*******************************************************************************
*
*	table_get_header():
*		??? (description missing)
*
*	Return:
*		-
*
******************************************|************************************/

GLOBAL void table_get_header(char *s)
{
	size_t i;
	int column, t;
	char n[128];						/* contains [|l|l], etc. */

	table_reset();
	str2tok(s);

	if (token_counter > 0)
		um_strcpy(n, token[1], 128, CMD_BEGIN_TABLE);

	table.toplines = 0;
	if (token_counter > 1 && !no_table_lines)
	{
		for (t = 2; t < token_counter; t++)
			if (strcmp(token[2], "!hline") == 0)
				table.toplines++;
	}

	token_reset();

	column = 0;
	for (i = 0; i < strlen(n); i++)
	{
		if (n[i] == '|' && !no_table_lines)
		{
			table.vertical_bar[column]++;
		} else if (n[i] == 'l')
		{
			if (column >= MAX_TAB_W)
			{
				error_message(_("too many columns used"));
			} else
			{
				table.col_justification[column] = TAB_LEFT;
				column++;
			}
		} else if (n[i] == 'c')
		{
			if (column >= MAX_TAB_W)
			{
				error_message(_("too many columns used"));
			} else
			{
				table.col_justification[column] = TAB_CENTER;
				column++;
			}
		} else if (n[i] == 'r')
		{
			if (column >= MAX_TAB_W)
			{
				error_message(_("too many columns used"));
			} else
			{
				table.col_justification[column] = TAB_RIGHT;
				column++;
			}
		}
	}
}





/*******************************************************************************
*
*	test_for_addition():
*		??? (description missing)
*
*	Return:
*		-
*
******************************************|************************************/

LOCAL void test_for_addition(char *cell, int y, int x)
{
	char *found2, *tok;
	size_t clen;

	/* remove leading [ */
	if (cell[0] == '[')
		cell = &cell[1];
	clen = strlen(cell);
	if (clen == 0)
		return;

	/* remove tailing ] */
	if (cell[clen - 1] == ']')
		cell[clen - 1] = EOS;
	if (cell[0] == 0)
		return;

	/* Now we have to see, if there are entries */
	tok = strtok(cell, " ,\t");			/* whitespace, colon, or tab are separators */
	while (tok)
	{
		found2 = strstr(tok, "COLS=");
		if (found2 != NULL)
			table.row[y].cell[x].colspan = atoi(found2 + 5);

		found2 = strstr(tok, "BGC=");
		if (found2 != NULL)
		{
			found2 += 4;
			get_html_color_or_rgb(found2, &table.row[y].cell[x].bg);
		}

		found2 = strstr(tok, "HA=");
		if (found2 != NULL)
		{
			found2 += 3;
			if (strcmp(found2, "left") == 0)
				table.row[y].cell[x].halign = TAB_LEFT;
			else if (strcmp(found2, "center") == 0)
				table.row[y].cell[x].halign = TAB_CENTER;
			else if (strcmp(found2, "right") == 0)
				table.row[y].cell[x].halign = TAB_RIGHT;
			else
				error_message(_("invalid column alignment '%s'"), found2);
		}

		found2 = strstr(tok, "VA=");
		if (found2 != NULL)
		{
			found2 += 3;
			if (strcmp(found2, "top") == 0)
				table.row[y].cell[x].valign = TAB_TOP;
			else if (strcmp(found2, "center") == 0)
				table.row[y].cell[x].valign = TAB_CENTER;
			else if (strcmp(found2, "bottom") == 0)
				table.row[y].cell[x].valign = TAB_BOTTOM;
			else
				error_message(_("invalid column alignment '%s'"), found2);
		}

		tok = strtok(NULL, " ,\t");
	}
}





/*******************************************************************************
*
*	table_add_line():
*		??? (description missing)
*
*	Return:
*		-
*
******************************************|************************************/

GLOBAL _BOOL table_add_line(char *s)
{
	char *ptr;
	int x;
	size_t sl;							/* strlen */
	size_t tl;							/* toklen */
	int cells_counter;
#ifdef __TOS__
	static
#endif
	char cells[MAX_TAB_W][LINELEN];
	int y;
	
	del_whitespaces(s);

	/* Leerzeilen und Kommentare nicht bearbeiten */
	if (s[0] == EOS || s[0] == '#')
		return TRUE;

	if (table.height >= MAX_TAB_H)
	{
		error_message(_("too many rows used"));
		s[0] = EOS;
		return FALSE;
	}
	y = table.height;

	if (strncmp(s, "!label*", 7) == 0 ||
		strncmp(s, "!label", 6) == 0 ||
		strncmp(s, "!l* ", 4) == 0 ||
		strncmp(s, "!l ", 3) == 0)
	{
		if (table.row[y].num_labels >= MAX_TAB_LABEL)
		{
			error_message(_("too many labels used in table"));
			s[0] = EOS;
			return FALSE;
		}

		sl = strlen(s);
		ptr = (char *) (malloc(sl + 2));

		if (ptr == NULL)
		{
			return FALSE;
		}

		strcpy(ptr, s);

		table.row[y].label[table.row[y].num_labels] = ptr;
		table.row[y].num_labels++;

		return TRUE;
	}

	/* Zeile enthaelt nur !hline */
	if (strcmp(s, "!hline") == 0)
	{
		if (!no_table_lines)
		{
			if (y == 0)
				warning_message(_("!hline for the first table line has to be placed in the table header"));
			else
				table.row[y - 1].horizontal_bar++;
		}
		return TRUE;
	}

	/* Nun aus der Zeile die Felder auslesen */
	replace_char(s, '\t', ' ');

	/* FIXME: should actually be c_divis(), with appropiate str2silben() when writing the cell contents */
	qdelete_all(s, "!-", 2);

	if (no_umlaute)
		recode_chrtab(s, CHRTAB_ASCII);

	auto_quote_chars(s, FALSE);
	switch (desttype)
	{
	case TOSTG:
	case TOAMG:
		replace_1at_by_2at(s);
		break;
	}
	
	c_commands_inside(s, TRUE);

	replace_macros(s);
	c_divis(s);
	c_vars(s);
	c_tilde(s);
	c_styles(s);
	check_styles(s);
	replace_defines(s);
	c_commands_inside(s, FALSE);

	ptr = s;
	cells_counter = 0;
	sl = 0;
	memset(cells, 0, sizeof(cells));
	while (ptr[0] != EOS)
	{
		if (ptr[0] == '!' && ptr[1] == '!')
		{
			cells_counter++;
			ptr++;
			sl = 0;
		} else
		{
			if (cells_counter >= MAX_TAB_W)
			{
				error_message(_("too many columns used"));
			} else if (sl + 1 < LINELEN)
			{
				chrcat(cells[cells_counter], ptr[0]);
				sl++;
			} else
			{
				error_message(_("table cell contains too many characters"));
				return FALSE;
			}
		}
		ptr++;
	}

	if (sl != 0)
	{
		cells_counter++;
	}
	
	if (cells_counter > MAX_TAB_W)
	{
		error_message(_("too many columns used"));
		cells_counter = MAX_TAB_W;
	}

	if (cells_counter > table.width)
		table.width = cells_counter;

	/* Zeilenzaehler hochsetzen */
	table.height++;

	for (x = 0; x < cells_counter; x++)
	{
		char *found;
		
		replace_udo_quotes(cells[x]);
		del_whitespaces(cells[x]);
		table.row[y].cell[x].halign = table.col_justification[x];
		table.row[y].cell[x].valign = TAB_TOP;
		table.row[y].cell[x].colspan = 0;
		table.row[y].cell[x].bg.rgb.set = FALSE;
		table.row[y].cell[x].bg.color = BC_NONE;
		found = strstr(cells[x], "!?");
		if (found != NULL)
		{
			*found = '\0';
			del_whitespaces(cells[x]);
			found += 2;
			test_for_addition(found, y, x);
		}
		tl = toklen(cells[x]);
		sl = strlen(cells[x]);
		if (tl > table.cell_width[x] && table.row[y].cell[x].colspan < 2)
			table.cell_width[x] = tl;

		ptr = (char *) malloc(sl + 2);
		if (ptr == NULL)
		{
			return FALSE;
		}
		strcpy(ptr, cells[x]);
		table.row[y].cell[x].text = ptr;
	}

	return TRUE;
}


LOCAL void get_table_alignment(_BOOL * inside_left, _BOOL * inside_center, _BOOL * inside_right)
{
	int j;

	*inside_left = FALSE;
	*inside_center = FALSE;
	*inside_right = FALSE;
	for (j = iEnvLevel; j > 0; j--)
	{
		if (iEnvType[iEnvLevel] == ENV_LEFT)
		{
			*inside_left = TRUE;
			break;
		}
		if (iEnvType[iEnvLevel] == ENV_CENT)
		{
			*inside_center = TRUE;
			break;
		}
		if (iEnvType[iEnvLevel] == ENV_RIGH)
		{
			*inside_right = TRUE;
			break;
		}
	}
	if (!(*inside_center) && !(*inside_right) && !(*inside_left))
	{
		switch (table_alignment)
		{
		case ALIGN_CENT:
			*inside_center = TRUE;
			break;
		case ALIGN_RIGH:
			*inside_right = TRUE;
			break;
		default:
			*inside_left = TRUE;
			break;
		}
	}
}



LOCAL void tab_label_output(int y)
{
	int i;

	for (i = 0; i < table.row[y].num_labels; i++)
	{
		if (table.row[y].label[i] != NULL)
		{
			str2tok(table.row[y].label[i]);

			if (token_counter > 0)
				c_label();
		}
		token_reset();
	}
}



/*******************************************************************************
*
*	table_output_lyx():
*		??? (description missing)
*
*	Return:
*		-
*
******************************************|************************************/

LOCAL void table_output_lyx(void)
{
	int y, x;
	_BOOL bl, bt, bb, br;				/* Flags fuer Linien */
	char f[LINELEN], alignOn[64];
	_BOOL inside_center, inside_right, inside_left;

	get_table_alignment(&inside_left, &inside_center, &inside_right);

	alignOn[0] = EOS;
	if (inside_center)
		strcpy(alignOn, " center");
	if (inside_right)
		strcpy(alignOn, " right");

	outln("\\layout Standard");
	voutlnf("\\added_space_top 0.30 \\added_space_bottom 0.30 \\align %s", alignOn);
	outln("\\begin_inset  Tabular");
	voutlnf("<lyxtabular version=\"3\" rows=\"%d\" columns=\"%d\">", table.height, table.width);
	outln("<features>");
	/* Fuer jede Tabellenspalte eine Zeile ausgeben, in der Flags stehen, */
	/* die angeben, ob dort linke und rechte Linien benutzt werden. */
	for (x = 0; x < table.width; x++)
	{
		bl = table.vertical_bar[x] > 0;

		if (x == (table.width - 1))
		{
			br = table.vertical_bar[x + 1] > 0;
		} else
		{
			br = FALSE;
		}

		switch (table.col_justification[x])
		{
		case TAB_CENTER:
			strcpy(alignOn, "center");
			break;
		case TAB_RIGHT:
			strcpy(alignOn, "right");
			break;
		default:
			strcpy(alignOn, "left");
			break;
		}

		voutlnf("<column alignment=\"%s\" valignment=\"top\" leftline=\"%s\" rightline=\"%s\" width=\"0\">",
				alignOn, bl ? "true" : "false", br ? "true" : "false");
	}

	for (y = 0; y < table.height; y++)
	{
		tab_label_output(y);
		if (y == 0)
		{
			bt = table.toplines > 0;
			bb = table.row[0].horizontal_bar > 0;
		} else
		{
			bt = table.row[y - 1].horizontal_bar > 0;
			bb = table.row[y    ].horizontal_bar > 0;
		}

		voutlnf("<row topline=\"%s\" bottomline=\"%s\">", bt ? "true" : "false", bb ? "true" : "false");
		for (x = 0; x < table.width; x++)
		{
			outln("<cell>");
			outln("\\begin_inset Text");
			outln("");
			outln("\\layout Standard");
			outln("");
			if (table.row[y].cell[x].text != NULL)
			{
				strcpy(f, table.row[y].cell[x].text);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				c_internal_styles(f);
				replace_placeholders(f);
				indent2space(f);
				outln(f);
			}
			outln("\\end_inset");
			outln("</cell>");
		}
		outln("</row>");
	}
	outln("</lyxtabular>");
	outln("");
	outln("\\end_inset");
	outln("");
	if (table.caption != NULL)
	{
		outln("\\begin_inset Float table");
		outln("wide false");
		outln("collapsed false");
		outln("");
		outln("\\layout Caption");
		outln("");
		outln(table.caption);
		outln("\\end_inset");
	}
	outln("\\layout Standard");
	outln("");
}





/*******************************************************************************
*
*	table_output_rtf():
*		??? (description missing)
*
*	Return:
*		-
*
******************************************|************************************/

LOCAL void table_output_rtf(void)
{
	int y, x, i, cellx, indent, charw;
	char f[LINELEN], cx[512];

	indent = strlen_indent();

	if (bDocRtfKeepTablesOn)
		outln("{\\keep\\keepn");
	else
		outln("{\\keep");

	charw = iDocCharwidth;

	for (y = 0; y < table.height; y++)
	{
		tab_label_output(y);
		outln("\\trowd");
		cellx = 0;
		if (indent > 0)
		{
			cellx = indent;
			voutlnf("\\cellx%d", cellx);
		}

		for (i = 0; i < table.width; i++)
		{
			f[0] = EOS;
			if (table.vertical_bar[i] > 0)
				strcat(f, "\\clbrdrl\\brdrs");
			if (table.vertical_bar[i + 1] > 0)
				strcat(f, "\\clbrdrr\\brdrs");
			if (table.row[y].horizontal_bar > 0)
				strcat(f, "\\clbrdrb\\brdrs");
			if ((y == 0 && table.toplines > 0) || (y > 0 && table.row[y - 1].horizontal_bar > 0))
				strcat(f, "\\clbrdrt\\brdrs");

			cellx += ((int) table.cell_width[i] * charw);
			sprintf(cx, "\\cellx%d", cellx);
			voutlnf("%s%s", f, cx);
		}

		out("\\intbl");
		if (indent > 0)
			out("\\ql \\cell");

		for (x = 0; x < table.width; x++)
		{
			switch (table.col_justification[x])
			{
			case TAB_CENTER:
				out("\\qc ");
				break;
			case TAB_RIGHT:
				out("\\qr ");
				break;
			default:
				out("\\ql ");
				break;
			}

			if (table.row[y].cell[x].text != NULL)
			{
				strcpy(f, table.row[y].cell[x].text);
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
	}

	outln("\\trowd\\pard");
	outln("}\\par\\pard");

	if (table.caption != NULL)
	{
		c_rtf_quotes(table.caption);
		out("{\\keep\\trowd");
		if (indent > 0)
			voutlnf("\\cellx%d", indent);
		outln(cx);						/* Noch von oben definiert */
		out("\\intbl");

		if (indent > 0)
			out("\\ql \\cell");

		if (table.caption_visible)
		{
			sprintf(f,
					"\\qc %s {\\field{\\*\\fldinst { SEQ Tabelle \\\\* ARABIC }}{\\fldrslt %d}}: %s\\cell\\row\\pard",
					get_lang()->table, tab_counter, table.caption);
		} else
		{
			sprintf(f, "\\qc %s\\cell\\row\\pard", table.caption);
		}
		outln(f);
		outln("\\trowd\\pard");
		outln("}\\par\\pard");
	}
}





/*******************************************************************************
*
*	table_output_win():
*		??? (description missing)
*
*	Return:
*		-
*
******************************************|************************************/

LOCAL void table_output_win(void)
{
	int y, x, i, cellx, indent, charw;
	char f[LINELEN];
	char cx[512], ci[512];

	indent = strlen_indent();
	cellx = 0;
	outln("{\\keep\\trowd");

	charw = iDocCharwidth;

	if (indent > 0)
	{
		cellx = indent;
		sprintf(ci, "\\cellx%d", cellx);	/* ci wird unten noch benoetigt! */
		outln(ci);
	}

	for (i = 0; i < table.width; i++)
	{
		cellx += ((int) table.cell_width[i] * charw);
		sprintf(cx, "\\cellx%d", cellx);	/* cx wird unten noch benoetig! */
		outln(cx);
	}

	for (y = 0; y < table.height; y++)
	{
		tab_label_output(y);
		out("\\intbl");
		if (indent > 0)
			out("\\ql \\cell");
		if (table.toplines > 0)
			out("{\\box");

		for (x = 0; x < table.width; x++)
		{
			switch (table.col_justification[x])
			{
			case TAB_CENTER:
				out("\\qc ");
				break;
			case TAB_RIGHT:
				out("\\qr ");
				break;
			default:
				out("\\ql ");
				break;
			}

			if (table.row[y].cell[x].text != NULL)
			{
				strcpy(f, table.row[y].cell[x].text);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				auto_references(f, FALSE, "", 0, 0);
				c_win_styles(f);
				replace_placeholders(f);
				out(f);
			}
			out("\\cell");
		}

		if (table.toplines > 0)
			outln("\\row\\pard}");
		else
			outln("\\row");
	}

	outln("\\trowd\\pard");
	outln("}\\par\\pard");

	if (table.caption != NULL)
	{
		out("{\\keep\\trowd");
		if (indent > 0)
			out(ci);					/* Noch von oben definiert */
		outln(cx);						/* Noch von oben definiert */
		out("\\intbl");
		if (indent > 0)
			out("\\ql \\cell");

		if (table.caption_visible)
		{
			sprintf(f, "\\qc %s %d: %s\\cell\\row\\pard", get_lang()->table, tab_counter, table.caption);
		} else
		{
			sprintf(f, "\\qc %s\\cell\\row\\pard", table.caption);
		}
		outln(f);
		outln("\\trowd\\pard");
		outln("}\\par\\pard");
	}
}





/*******************************************************************************
*
*	table_output_html():
*		nomen est omen
*
*	Return:
*		-
*
******************************************|************************************/

LOCAL void table_output_html(void)
{
	int y, x;
	char f[LINELEN], alignOn[64];
	_BOOL inside_center, inside_right, inside_left;
	_BOOL inside_env;

	get_table_alignment(&inside_left, &inside_center, &inside_right);
	inside_env = (iItemLevel > 0 || iEnumLevel > 0 || iDescLevel > 0 || iListLevel > 0);

	strcpy(alignOn, "left");
	if (inside_center)
		strcpy(alignOn, "center");
	if (inside_right)
		strcpy(alignOn, "right");

	if (inside_env)						/* we're inside another environment! */
	{
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:
		case ENV_ENUM:
		case ENV_LIST:
			if (bEnvCompressed[iEnvLevel])
			{
				outln(xhtml_br);
			} else
			{
				out(xhtml_br);
				outln(xhtml_br);
			}
			break;

		case ENV_DESC:
			break;						/* we're fine in description environments (so far ;-)) */
		}
	}
	voutf("<div align=\"%s\">", alignOn);

	if (table.toplines > 0)
	{
		outln("<table border=\"1\" frame=\"box\" class=\"UDO_env_table\">");
	} else
	{
		outln("<table border=\"0\" class=\"UDO_env_table\">");
	}

	if (table.caption != NULL)
	{
		if (table.caption_visible)
		{
			voutlnf("<caption align=\"bottom\">%s %d: %s</caption>", get_lang()->table, tab_counter, table.caption);
		} else
		{
			voutlnf("<caption align=\"bottom\">%s</caption>", table.caption);
		}
	}

	for (y = 0; y < table.height; y++)
	{
		outln("<tr>");
		for (x = 0; x < table.width; x++)
		{
			char *cell;
			char addition[512];
			const char *color;
			
			/* addition takes the extra options per cell, so it needs to be cleaned */
			addition[0] = EOS;
			if (table.row[y].cell[x].colspan > 0)
				sprintf(addition + strlen(addition), " colspan=\"%d\"", table.row[y].cell[x].colspan);
			color = html_color_string(&table.row[y].cell[x].bg.rgb);
			if (*color)
				sprintf(addition + strlen(addition), " bgcolor=\"%s\"", color);

			/* some tables have empty cells, so always check before using table cell entries */
			cell = table.row[y].cell[x].text;

			/* Everything not set in test_for_addition is now set here */
			switch (table.row[y].cell[x].halign)
			{
			case TAB_CENTER:
				strcat(addition, " align=\"center\"");
				break;
			case TAB_RIGHT:
				strcat(addition, " align=\"right\"");
				break;
			default:
				strcat(addition, " align=\"left\"");
				break;
			}

			switch (table.row[y].cell[x].valign)
			{
			case TAB_CENTER:
				strcat(addition, " valign=\"center\"");
				break;
			case TAB_BOTTOM:
				strcat(addition, " valign=\"bottom\"");
				break;
			default:
				strcat(addition, " valign=\"top\"");
				break;
			}
			voutf("  <td%s>", addition);

			out(sHtmlPropfontStart);
			if (cell != NULL)
			{
				strcpy(f, cell);
				c_internal_styles(f);
				auto_references(f, FALSE, "", 0, 0);
				replace_placeholders(f);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				out(f);
			}

			/* If there is a colspan, we need to supress empty cols */
			if (table.row[y].cell[x].colspan > 0)
				x = x + table.row[y].cell[x].colspan - 1;

			out(sHtmlPropfontEnd);
			outln("</td>");
		}
		outln("</tr>");

		tab_label_output(y);
	}

	outln("</table>");
	outln("</div>");
}





/*******************************************************************************
*
*	table_output_tex():
*		??? (description missing)
*
*	Return:
*		-
*
******************************************|************************************/

LOCAL void table_output_tex(void)
{
	int y, x, i;
	char f[LINELEN];
	char alignOn[64], alignOff[64];
	_BOOL inside_center, inside_right, inside_left;

	get_table_alignment(&inside_left, &inside_center, &inside_right);

	alignOn[0] = alignOff[0] = EOS;
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

	if (table.caption != NULL)
		outln("\\begin{table}[htb]");

	outln(alignOn);

	out("\\begin{tabular}{");
	for (x = 0; x < table.width; x++)
	{
		if (table.vertical_bar[x] > 0)
		{
			for (i = 1; i <= table.vertical_bar[x]; i++)
				out("|");
		}
		switch (table.col_justification[x])
		{
		case TAB_CENTER:
			out("c");
			break;
		case TAB_RIGHT:
			out("r");
			break;
		default:
			out("l");
			break;
		}
	}
	if (table.vertical_bar[table.width] > 0)
	{
		for (i = 1; i <= table.vertical_bar[table.width]; i++)
			out("|");
	}

	out("}");

	if (table.toplines > 0)
	{
		for (y = 1; y <= table.toplines; y++)
			out(" \\hline");
	}
	outln("");

	for (y = 0; y < table.height; y++)
	{
		tab_label_output(y);
		for (x = 0; x < table.width; x++)
		{
			if (table.row[y].cell[x].text != NULL)
			{
				strcpy(f, table.row[y].cell[x].text);
				c_internal_styles(f);
				replace_placeholders(f);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				indent2space(f);
				out(f);
			}
			if (x != (table.width - 1))
				out(" & ");
		}

		out(" \\\\");

		if (table.row[y].horizontal_bar > 0)
			out(" \\hline");
		outln("");
	}

	outln("\\end{tabular}");

	if (table.caption != NULL)
		voutlnf("\\caption{%s}", table.caption);

	outln(alignOff);

	if (table.caption != NULL)
		outln("\\end{table}");
}





/*******************************************************************************
*
*  table_output_ipf():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void table_output_ipf(void)
{
	int y, x, i;
	char f[LINELEN];
	char cx[512];

	f[0] = EOS;
	for (i = 0; i < table.width; i++)
	{
		sprintf(cx, "%lu ", (unsigned long) table.cell_width[i]);
		strcat(f, cx);
	}
	del_whitespaces(f);
	voutlnf(":table cols='%s'.", f);

	for (y = 0; y < table.height; y++)
	{
		tab_label_output(y);
		outln(":row.");
		for (x = 0; x < table.width; x++)
		{
#if 0
			switch (table.col_justification[x])
			{
			case TAB_CENTER:
				out("\\qc ");
				break;
			case TAB_RIGHT:
				out("\\qr ");
				break;
			default:
				out("\\ql ");
				break;
			}
#endif

			if (table.row[y].cell[x].text != NULL)
			{
				strcpy(f, table.row[y].cell[x].text);
				c_internal_styles(f);
				auto_references(f, FALSE, "", 0, 0);
				replace_placeholders(f);
				replace_udo_tilde(f);
				replace_udo_nbsp(f);
				voutlnf(":c.%s", f);
			} else
			{
				outln(":c.");
			}
		}
	}

	outln(":etable.");
}





/*******************************************************************************
*
*  table_output_general():
*     Output a table for formats which are not specially treated by
*     one of the functions above (mostly ASCII based formats)
*  These include:
*     TOASC
*     TOMAN
*     TOSTG
*     TORTF (when !rtf_no_tables was specified)
*     TOPCH
*     TOINF
*     TOTVH
*     TOLDS
*     TONRO
*     TOSRC
*     TOSRP
*     TODRC
*     TOKPS
*     TOAMG
*
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void table_output_general(void)
{
	int y, x, i, offset, indent = 0, y_stg;
	char s[LINELEN];
	char f[LINELEN];
	char hl[3][512];
	char hl_l[3][2], hl_c[3][2], hl_v[3][2], hl_r[3][2];
	char space[50];
	char vc_l[2], vc_m[2], vc_r[2];
	size_t tl, add, twidth, toffset, isl;
	_BOOL tortf, tosrc, ansichars, align_caption;
	_BOOL inside_center, inside_right, inside_left;
	size_t cell_width;
	
	get_table_alignment(&inside_left, &inside_center, &inside_right);

	if (inside_left)
		indent = strlen_indent();


	/* If the table is inside an environment */
	space[0] = EOS;
	if (indent > 0)
	{
		for (i = 0; i < indent; i++)
			strcat(space, " ");
	}

	tortf = tosrc = FALSE;
	switch (desttype)
	{
	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		tortf = TRUE;
		break;
	case TOSRC:
	case TOSRP:
		tosrc = TRUE;
		break;
	}

	ansichars = FALSE;

	if (use_ansi_tables)
	{
		if (desttype != TOWIN && desttype != TOWH4 && desttype != TOAQV && desttype != TORTF && desttype != TOINF)
			ansichars = TRUE;
	}

	if (tortf || desttype == TOINF || desttype == TOLDS)
	{
		output_begin_verbatim(NULL);
	}

	/* outln(""); */
	if (tosrc)
		outln(sSrcRemOn);

	toffset = 1;
	y_stg = -1;
	if ((desttype == TOSTG || desttype == TOAMG) && !ansichars)
	{
		/* Tabellenbreite fuer den ST-Guide berechnen und in <hl[1]> */
		/* den Befehl zum Zeichnen von horizontalen Linien einsetzen */
		twidth = 0;
		for (x = 0; x < table.width; x++)
			twidth += table.cell_width[x] + 2;

		if (twidth <= zDocParwidth)
		{
			if (inside_center)
				toffset = (zDocParwidth - twidth) / 2 + 1;
			if (inside_right)
				toffset = zDocParwidth - twidth + 1;
			if (indent > 0)
				toffset = indent + 1;
		} else
		{
			if (indent > 0)
				toffset = indent + 1;
		}

		if (twidth > 126)
		{
			/*
			 * this code was intended to draw horizontal lines for STG that are
			 * longer than 126 chars, but it does not work:
			 * the x-offset to specify the starting position is also
			 * limited to 126 :-(
			 */
#if 0
			int j;
			
			i = (int) twidth;
			twidth = 126;

			sprintf(hl[1], "@line %d %d 0", (int) toffset, (int) twidth);

			i -= 126;
			x = (int) toffset + 126;

			while (i > 0)
			{
				if (i > 126)
					twidth = 126;
				else
					twidth = i;

				j = (int) strlen(hl[1]);

				sprintf(&hl[1][j], "\n@line %d %d 0", (int) x, (int) twidth);

				i -= (int) twidth;
				x += (int) twidth;

				if (x > 255)			/* Max X-Position       */
					break;
			}
#else
			int warn = table.toplines > 0;
			
			for (y = 0; y < table.height; y++)
				if (table.row[y].horizontal_bar > 0)
					warn = TRUE;
			if (warn)
				warning_message(_("horizontal table lines will be truncated"));
			sprintf(hl[1], "@line %d %d 0", (int) toffset, 126);
#endif
		} else
		{
			sprintf(hl[1], "@line %d %d 0", (int) toffset, (int) twidth);
		}
		strcpy(hl[0], hl[1]);
		strcpy(hl[2], hl[1]);

		/* Befehle fuer vertikale Linien erzeugen */
		for (x = 0; x <= table.width; x++)
		{
			if (table.vertical_bar[x] > 0)
			{
				y_stg = 0;
			}
		}

		strcpy(vc_l, "");
		strcpy(vc_m, "");
		strcpy(vc_r, "");

		if (table.toplines > 0)
			outln(hl[1]);
	} else
	{
		/* Zeichen fuer die Trennlinie(n) setzen        */
		/* Bei MSDOS wird der Grafikzeichensatz benutzt */

		if (ansichars)
		{
			strcpy(hl_l[0], "\311");	/*  ||= *//* Top */
			strcpy(hl_r[0], "\273");	/*  =|| */
			strcpy(hl_v[0], "\321");	/*  =|= */
			strcpy(hl_c[0], "\315");	/*  =   */
			strcpy(hl_l[1], "\307");	/* ||-  *//* Middle */
			strcpy(hl_r[1], "\266");	/* -||  */
			strcpy(hl_v[1], "\305");	/* -|-  */
			strcpy(hl_c[1], "\304");	/*  -   */
			strcpy(hl_l[2], "\310");	/* ||=  *//* Bottom */
			strcpy(hl_r[2], "\274");	/* =||  */
			strcpy(hl_v[2], "\317");	/* =|= */
			strcpy(hl_c[2], "\315");	/*  =   */

			strcpy(vc_l, "\272");
			strcpy(vc_m, "\263");
			strcpy(vc_r, "\272");
		} else
		{
			strcpy(hl_l[0], "+");		/* Top */
			strcpy(hl_r[0], "+");
			strcpy(hl_v[0], "+");
			strcpy(hl_c[0], "-");
			strcpy(hl_l[1], "+");		/* Middle */
			strcpy(hl_r[1], "+");
			strcpy(hl_v[1], "+");
			strcpy(hl_c[1], "-");
			strcpy(hl_l[2], "+");		/* Bottom */
			strcpy(hl_r[2], "+");
			strcpy(hl_v[2], "+");
			strcpy(hl_c[2], "-");

			strcpy(vc_l, "|");
			strcpy(vc_m, "|");
			strcpy(vc_r, "|");
		}

		/* ------------------------------- */
		/* Trennlinie(n) zusammenstellen   */
		/* 0 = top, 1 = middle, 2 = bottom */
		/* ------------------------------- */

		for (y = 0; y < 3; y++)
		{
			hl[y][0] = EOS;

			strcat(hl[y], space);

			/* Begin of a table-line in postscript */
			if (desttype == TOKPS)
				strcat(hl[y], "Von (");

			for (x = 0; x < table.width; x++)
			{
				if (table.vertical_bar[x] > 0)
				{
					if (x == 0)
					{
						for (i = 1; i <= table.vertical_bar[x]; i++)
							strcat(hl[y], hl_l[y]);
					} else
					{
						for (i = 1; i <= table.vertical_bar[x]; i++)
						{
							strcat(hl[y], hl_v[y]);
						}
					}
				}

				strcat(hl[y], hl_c[y]);

				for (isl = 1; isl <= table.cell_width[x]; isl++)
				{
					strcat(hl[y], hl_c[y]);
				}

				strcat(hl[y], hl_c[y]);
			}

			if (table.vertical_bar[table.width] > 0)
			{
				for (i = 1; i <= table.vertical_bar[table.width]; i++)
				{
					if (i == table.vertical_bar[table.width])
					{
						strcat(hl[y], hl_r[y]);
					} else
					{
						strcat(hl[y], hl_v[y]);
					}
				}
			}

			/* Conclusion of a table-line in postscript */
			if (desttype == TOKPS)
				strcat(hl[y], ") udoshow newline Voff");

			if (inside_center)
			{
				/* Linie fuer den Rest zentrieren */
				stringcenter(hl[y], zDocParwidth);
			}
			if (inside_right)
			{
				/* Linie fuer den Rest ausrichten */
				strright(hl[y], zDocParwidth);
			}
			if (tortf)
				strcat(hl[y], "\\par");
			if (tosrc)
				strinsert(hl[y], "    ");
		}


		/* obere Tabellenlinien ausgeben */
		if (table.toplines > 0)
		{
			for (i = 1; i <= table.toplines; i++)
			{
				if (i == 1)
					outln(hl[0]);
				else
					outln(hl[1]);
			}
		}
	}

	for (y = 0; y < table.height; y++)
	{
		s[0] = EOS;
		if (y == y_stg)
		{
			/* ST-Guide kann nur Linien mit einer Laenge von 254 Zeilen */
			/* zeichen. Deshalb wird hier eine Anschlussline gezeichnet */
			int h_stg;
			
			offset = (int) toffset;

			h_stg = table.height - y_stg;
			if (h_stg > 254)
				h_stg = 254;

			for (x = 0; x <= table.width; x++)
			{
				if (table.vertical_bar[x] > 0)
				{
					voutlnf("@line %d 0 %d", offset, h_stg);
				}
				offset += (int) table.cell_width[x];
				offset += 2;
			}
			y_stg += h_stg;
		}

		strcat(s, space);

		for (x = 0; x < table.width; x++)
		{
			if (table.vertical_bar[x] > 0)
			{
				for (i = 1; i <= table.vertical_bar[x]; i++)
				{
					strcat(s, x == 0 ? vc_l : vc_m);
				}
			}

			strcat(s, " ");

			f[0] = EOS;
			if (table.row[y].cell[x].text != NULL)
			{
				strcpy(f, table.row[y].cell[x].text);
			}

			add = 0;
			cell_width = table.cell_width[x];
			if (table.row[y].cell[x].colspan > 0)
			{
				for (i = 1; i < (table.row[y].cell[x].colspan - 1); i++)
					cell_width += table.cell_width[x + i];
			}
			
			switch (table.col_justification[x])
			{
			case TAB_CENTER:
				stringcenter(f, (int) cell_width);
				strcat(s, f);
				tl = toklen(f);
				if (cell_width > tl)
					add = cell_width - tl;
				if (add > 0)
					for (isl = 0; isl < add; isl++)
						strcat(s, " ");
				break;

			case TAB_RIGHT:
				tl = toklen(f);
				if (cell_width > tl)
					add = cell_width - tl;
				if (add > 0)
					for (isl = 0; isl < add; isl++)
						strcat(s, " ");
				strcat(s, f);
				break;

			default:					/* TAB_LEFT */
				strcat(s, f);
				tl = toklen(f);
				if (cell_width > tl)
					add = cell_width - tl;
				if (add > 0)
					for (isl = 0; isl < add; isl++)
						strcat(s, " ");
				break;
			}

			strcat(s, " ");
			if (table.row[y].cell[x].colspan > 0)
				x += (table.row[y].cell[x].colspan - 1);
		}

		if (table.vertical_bar[table.width] > 0)
		{
			for (i = 1; i <= table.vertical_bar[table.width]; i++)
			{
				strcat(s, i == table.vertical_bar[table.width] ? vc_r : vc_m);
			}
		}

		if (inside_center)
			stringcenter(s, zDocParwidth);

		if (inside_right)
			strright(s, zDocParwidth);

		c_internal_styles(s);
		replace_placeholders(s);
		replace_udo_tilde(s);
		replace_udo_nbsp(s);

		if (tortf)
			strcat(s, "\\par");
		if (tosrc)
			strinsert(s, "   ");

		/* Begin of a table-line in postscript */
		if (desttype == TOKPS)
		{
			replace_all(s, "(", "\\(");
			replace_all(s, ")", "\\)");
			voutlnf(s, "Von (%s) udoshow newline Voff\n", s);
		} else
		{
			outln(s);
		}

		if (table.row[y].horizontal_bar > 0)
		{
			for (i = 1; i <= table.row[y].horizontal_bar; i++)
			{
				if (y == (table.height - 1) && i == table.row[y].horizontal_bar)
				{
					outln(hl[2]);
				} else
				{
					outln(hl[1]);
				}
			}
		}

		tab_label_output(y);
	}

	if (tosrc)
		outln(sSrcRemOff);

	if (table.caption != NULL)
	{
		if (tortf)
			outln(rtf_par);
		else
			outln("");

		/* Caption wird wie bei LaTeX nur zentriert, wenn sie  */
		/* kuerzer als die Absatzbreite ist.                        */
		token_reset();
		align_caption = (strlen(table.caption) < zDocParwidth);

		if (align_caption)
		{
			s[0] = EOS;
			if (inside_center)
				strcpy(s, CMD_BEGIN_CENTER);
			if (inside_right)
				strcpy(s, CMD_BEGIN_RIGHT);
			tokenize(s);

			/*
			 * FIXME: will treat text as if it appeared in input file,
			 * but lang.table has already been converted to destination
			 * format, and table.caption has already been tokenized
			 */
			if (table.caption_visible)
				sprintf(s, "%s %d: %s", get_lang()->table, tab_counter, table.caption);
			else
				strcpy(s, table.caption);

			tokenize(s);

			s[0] = EOS;
			if (inside_center)
				strcpy(s, CMD_END_CENTER);
			if (inside_right)
				strcpy(s, CMD_END_RIGHT);
			tokenize(s);
			token_output(TRUE, TRUE);
		} else
		{
			if (table.caption_visible)
				sprintf(s, "%s %d: %s", get_lang()->table, tab_counter, table.caption);
			else
				strcpy(s, table.caption);
			/*
			 * FIXME: will treat text as if it appeared in input file,
			 * but lang.table has already been converted to destination
			 * format, and table.caption has already been tokenized
			 */
			tokenize(s);
			token_output(TRUE, TRUE);
		}
	}

	if (tortf)
		outln(rtf_par);

	if (tortf || desttype == TOINF || desttype == TOLDS)
		output_end_verbatim();
}





/*******************************************************************************
*
*  table_output():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void table_output(void)
{
	tab_counter++;

	switch (desttype)
	{
	case TOHTM:
	case TOMHH:
	case TOHAH:
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
			table_output_general();
		else
			table_output_rtf();
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
	token_reset();
	check_styleflags();
}





/*******************************************************************************
*
*  set_table_counter():
*     Tabellen-Zaehler veraendern
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_table_counter(const int i)
{
	tab_counter = i - 1;
	if (tab_counter < 0)
		tab_counter = 0;
}





/*******************************************************************************
*
*  set_table_alignment():
*     set table alignment :-)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_table_alignment(void)
{
	char s[256];

	tokcpy2(s, sizeof(s));

	if (strcmp(s, "center") == 0)
	{
		table_alignment = ALIGN_CENT;
		return;
	}

	if (strcmp(s, "left") == 0)
	{
		table_alignment = ALIGN_LEFT;
		return;
	}

	if (strcmp(s, "right") == 0)
	{
		table_alignment = ALIGN_RIGH;
		return;
	}
	error_message(_("invalid table_alignment '%s'"), s);
}





/*******************************************************************************
*
*  init_module_tab():
*     init tab module
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_tab(void)
{
	tab_counter = 0;
	table.caption = NULL;
	table.caption_visible = FALSE;
}
