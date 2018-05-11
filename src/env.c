/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : env.c
*  Symbol prefix: env
*
*  Description  : This module handles the environment routines which manage the 
*                 output of various environments and prepare them for 
*                 token_output().
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
*  Co-Authors   : Ulf Dunkel (fd), Gerhard Stoll (ggs), Manfred Guentner (mg)
*  Write access : fd, ggs, mg
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2008:
*    fd  Nov 14: indexudo.html now capitalizes the A-Z jump labels (issue #76 solved)
*  2009:
*    ggs Jan 11: Bullet for the !begin_itemize, will always use in ST-Guide
*    fd  Jun 04: !docinfo [translator] introduced
*    fd  Jun 08: TAB -> '   '
*  2010:
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*    fd  Feb 03: file reformatted and tidied up
*    fd  Feb 05: c_end_enumerate() outputs an empty HTML code line (for readability)
*    fd  Feb 08: issue #79 fixed (weird empty lines on "!autoref []" in description environments
*    fd  Feb 17: win2sys() -> recode_chrtab()
*    fd  Feb 23: UDO_PL -> UDO_BUILD (no more patchlevels)
*    fd  Feb 27: HTML output for ENV_DESC, ENV_LIST + other environments adjusted
*    fd  Mar 01: new: use_short_itemizes
*                     use_short_enumerates
*                     use_short_descriptions
*                     use_short_lists
*    fd  Mar 03: c_begin_enumerate(): linefeed in front of <ol>
*    fd  Mar 04: great renaming:
*                - use_short_envs         -> use_compressed_envs
*                - use_short_descriptions -> use_short_descriptions
*                - use_short_enumerates   -> use_short_enumerates
*                - use_short_itemizes     -> use_short_itemizes
*                - use_short_lists        -> use_short_lists
*                - bEnvShort[]            -> bEnvCompressed[]
*                - set_env_short()        -> set_env_compressed()
*                The old commands are still available!
*    fd  Mar 05: c_begin_document() debugged for titdat content
*    ggs Apr 04: c_begin_list() delete compressed and no_compressed
*    ggs Apr 12: c_begin_list() test the compressed and not only short
*    ggs Apr 21: c_begin_list(): The [] are not always necessary
*    fd  May 19: c_begin_list() reformatted
*    fd  May 20: c_item() debugged for description item output in RTF & KPS
*    fd  Sep 03: c_end_itemize()/c_end_enumerate() no longer keep bParagraphOpen TRUE
*  2011:
*    fd  Feb 18: c_begin_document() writes Unicode information ("\uc0") for RTF [#95]
*    mg  Jul 27: enhancements for NROFF
*    mg  Aug 02: more enhancements for NROFF
*  2012:
*    fd  Apr 24: c_begin_enumerate() handles optional enumeration start number parameter
*  2013:
*    fd  Oct 23: HTML output supports HTML5
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
#include "udo_type.h"
#include "udointl.h"
#include "commands.h"
#include "abo.h"
#include "cfg.h"
#include "chr.h"
#include "file.h"
#include "img.h"
#include "msg.h"
#include "par.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "tp.h"
#include "udo.h"
#include "gui.h"
#include "lang.h"

#include "export.h"
#include "env.h"
#include "udo2ps.h"
#include "udo2pdf.h"





/*******************************************************************************
*
*     UNINITIALIZED VARIABLES
*
******************************************|************************************/

LOCAL int env_kind[MAXENVLEVEL + 1];	/* Art der Umgebung (LIST_BOLD, ... */
LOCAL int enum_count[MAXENVLEVEL + 1];	/* Item-Zaehler fuer enumerate */

LOCAL int cent_level;					/* Zaehler fuer center-Umgebungen */
LOCAL int flushright_level;				/* Zaehler fuer flushright-Umgebungen */
LOCAL int flushleft_level;				/* Zaehler fuer flushleft-Umgebungen */
LOCAL int quot_level;					/* Zaehler fuer quote-Umgebungen */

LOCAL char itemchar[MAXENVLEVEL + 1][64];	/* Zeichen fuer Itemize-Umgebung */


LOCAL _BOOL bCalledBeginAppendix;
LOCAL _BOOL bCalledEndAppendix;

LOCAL int pre_linedraw_charset;

LOCAL const PAPERFORMAT paperSize[MAXPAPERSIZE] = {
	{ "A3PORTRAIT",  2970, 4200,  842, 1191, 1136, 85,  780, 72, 0, 0, FALSE },
	{ "A3LANDSCAPE", 4200, 2970, 1191,  842,  780, 72, 1119, 72, 0, 0, TRUE },
	{ "A4PORTRAIT",  2100, 2970,  595,  842,  780, 85,  540, 72, 0, 0, FALSE },
	{ "A4LANDSCAPE", 2970, 2100,  842,  595,  530, 72,  770, 72, 0, 0, TRUE },
	{ "A5PORTRAIT",  1485, 2100,  421,  595,  530, 85,  366, 72, 0, 0, FALSE },
	{ "A5LANDSCAPE", 2100, 1485,  595,  421,  356, 72,  523, 72, 0, 0, TRUE }
};





/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*     CONTROL ROUTINES
*
******************************************|************************************/

_BOOL has_flag_compressed(void)
{
	int i;

	for (i = 1; i < token_counter; i++)
	{
		if (strcmp(token[i], "!compressed") == 0 ||
			strcmp(token[i], "!short") == 0)
			return TRUE;
	}
	return FALSE;
}

/*******************************************************************************
*
*  set_env_compressed():
*     set the compressed flag for environments
*
*  Notes:
*     Basically, all environments which support the !compressed attribute, are set 
*     to be output "splendid", not "compressed" (aka "short"). 
*
*     Environments which currently support the compressed flag, are:
*     ENV_DESC, ENV_ENUM, ENV_ITEM, ENV_LIST
*
*     Here are two examples which show the difference:
*
*     Example A: itemize environment, splendid (default)
*
*     Source:                      Output (target HTML):
*     --------------------------------------------------
*     !begin_itemize               <ul>
*     !item Test                   <li><p>Test</p></li>
*     !item Foo                    <li><p>Foo</p></li>
*     !item Bar                    <li><p>Bar</p></li>
*     !end_itemize                 </ul>
*
*     Example B: itemize environment, compressed (using local attibute !compressed)
*
*     Source:                      Output (target HTML):
*     --------------------------------------------------
*     !begin_itemize !compressed   <ul>
*     !item Test                   <li>Test</li>
*     !item Foo                    <li>Foo</li>
*     !item Bar                    <li>Bar</li>
*     !end_itemize                 </ul>
*
*     You can define all supported environments to be output compressed, by using
*     !use_compressed_envs (was !use_short_envs) in the preamble.
*
*     Or you can define compressed environments more precisely by using one of 
*     these commands:
*
*     !use_compressed_descriptions (was !use_short_descriptions)
*     !use_compressed_enumerates   (was !use_short_enumerates)
*     !use_compressed_itemizes     (was !use_short_itemizes)
*     !use_compressed_lists        (was !use_short_lists)
*
*     When you're going to nest such an environment in another environment,
*     the compressed flag of the outer environment is inherited by default.
*
*     If you want to suppress this inherit, use the environment attribute
*     !not_compressed in the inner environment.
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void set_env_compressed(const int el, const char *s)
{
	if (strstr(s, "!not_compressed"))	/* don't inherit compressed flag from outer environment */
	{
		bEnvCompressed[el] = FALSE;
		return;
	}

	if (use_compressed_envs)			/* this is the big general switch */
	{
		bEnvCompressed[el] = TRUE;
		return;
	}
	/* check single environment switches */
	if ((use_compressed_itemizes) && (iEnvType[el] == ENV_ITEM))
	{
		bEnvCompressed[el] = TRUE;
		return;
	} else if ((use_compressed_enumerates) && (iEnvType[el] == ENV_ENUM))
	{
		bEnvCompressed[el] = TRUE;
		return;
	} else if ((use_compressed_descriptions) && (iEnvType[el] == ENV_DESC))
	{
		bEnvCompressed[el] = TRUE;
		return;
	} else if ((use_compressed_lists) && (iEnvType[el] == ENV_LIST))
	{
		bEnvCompressed[el] = TRUE;
		return;
	}


	bEnvCompressed[el] = FALSE;			/* splendid by default */

	if (strstr(s, "!short"))			/* check local attributes */
	{
		warning_message(_("'!short' is a deprecated attribute for environments. Please use '!compressed' instead."));
		bEnvCompressed[el] = TRUE;
	} else if (strstr(s, "!compressed") != NULL)
	{
		bEnvCompressed[el] = TRUE;
	} else if (strchr(s, '!') != NULL)
	{
		warning_message(_("unrecognized option '%s'"), s);
	}

	if (!bEnvCompressed[el])			/* inherit compressed attribute by default */
	{
		if (el > 1 && bEnvCompressed[el - 1])
		{
			bEnvCompressed[el] = TRUE;
		}
	}
}





/*******************************************************************************
*
*  check_iEnvLevel():
*     check if maximum evironment level depth has been exceeded
*
*  Return:
*     TRUE: all OK
*    FALSE: max. depth exceeded
*
******************************************|************************************/

LOCAL _BOOL check_iEnvLevel(void)
{
	if (iEnvLevel >= MAXENVLEVEL - 1)
	{
		error_message(_("too many environments used"));
		return FALSE;
	}

	return TRUE;
}





/*******************************************************************************
*
*  check_env_end():
*     check if !end_* fits to last !begin_*
*
*  Notes:
*     Environments have to be closed properly, e.g. 
*     !end_itemize has to follow !begin_itemize, not another !begin_*.
*     When e.g. !end_enumerate follows !begin_itemize, an error message
*     has to be thrown.
*
*  Parameters:
*     etype:   ENV_ITEM, ENV_ENUM etc.
*     ekind:   LIST_NORMAL, LIST_BOLD etc.
*     ecomm:   used command (for error message)
*
*  Return:
*     TRUE: all OK
*    FALSE: wrong !end_*
*
******************************************|************************************/

LOCAL _BOOL check_env_end(int etype, int ekind)
{
	if (iEnvLevel <= 0 || iEnvType[iEnvLevel] != etype || (etype == ENV_LIST && env_kind[iEnvLevel] != ekind))
	{
		switch (etype)
		{
		case ENV_ITEM:
			error_end_without_begin(CMD_END_ITEMIZE, CMD_BEGIN_ITEMIZE);
			break;

		case ENV_ENUM:
			error_end_without_begin(CMD_END_ENUMERATE, CMD_BEGIN_ENUMERATE);
			break;

		case ENV_DESC:
			error_end_without_begin(CMD_END_DESCRIPTION, CMD_BEGIN_DESCRIPTION);
			break;

		case ENV_LIST:
			switch (ekind)
			{
			case LIST_BOLD:
				error_end_without_begin(CMD_END_BLIST, CMD_BEGIN_BLIST);
				break;

			case LIST_ITALIC:
				error_end_without_begin(CMD_END_ILIST, CMD_BEGIN_ILIST);
				break;

			case LIST_TYPEWRITER:
				error_end_without_begin(CMD_END_TLIST, CMD_BEGIN_TLIST);
				break;

			default:
				error_end_without_begin(CMD_END_XLIST, CMD_BEGIN_XLIST);
				break;
			}
			break;
		}
		return FALSE;
	}

	return TRUE;
}





/*******************************************************************************
*
*  check_environments_node():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void check_environments_node(void)
{
	int i;

	if (iEnvLevel <= 0)
		return;

	for (i = iEnvLevel; i >= 1; i--)
	{
		switch (iEnvType[i])
		{
		case ENV_ITEM:
			error_missing_end(CMD_END_ITEMIZE);
			break;

		case ENV_DESC:
			error_missing_end(CMD_END_DESCRIPTION);
			break;

		case ENV_ENUM:
			error_missing_end(CMD_END_ENUMERATE);
			break;

		case ENV_LIST:
			switch (env_kind[iEnvLevel])
			{
			case LIST_BOLD:
				error_missing_end(CMD_END_BLIST);
				break;

			case LIST_ITALIC:
				error_missing_end(CMD_END_ILIST);
				break;

			case LIST_TYPEWRITER:
				error_missing_end(CMD_END_TLIST);
				break;

			default:
				error_missing_end(CMD_END_XLIST);
				break;
			}
			break;

		case ENV_QUOT:
			error_missing_end(CMD_END_QUOTE);
			break;

		case ENV_CENT:
			error_missing_end(CMD_END_CENTER);
			break;

		case ENV_RIGH:
			error_missing_end(CMD_END_RIGHT);
			break;

		case ENV_LEFT:
			error_missing_end(CMD_END_LEFT);
			break;
		}
	}


	/* --- Noch begonnene Umgebungen automatisch beenden --- */

	for (i = iEnvLevel; i >= 1; i--)
	{
		switch (iEnvType[i])
		{
		case ENV_ITEM:
			c_end_itemize();
			break;

		case ENV_DESC:
			c_end_description();
			break;

		case ENV_ENUM:
			c_end_enumerate();
			break;

		case ENV_QUOT:
			c_end_quote();
			break;

		case ENV_CENT:
			c_end_center();
			break;

		case ENV_RIGH:
			c_end_flushright();
			break;

		case ENV_LEFT:
			c_end_flushleft();
			break;

		case ENV_LIST:
			switch (env_kind[iEnvLevel])
			{
			case LIST_BOLD:
				c_end_blist();
				break;

			case LIST_ITALIC:
				c_end_ilist();
				break;

			case LIST_TYPEWRITER:
				c_end_tlist();
				break;

			default:
				c_end_xlist();
				break;
			}
			break;
		}
	}
}





/*******************************************************************************
*
*  end_env_output_line():
*     output empty line after end of compressed environment
*
*  Notes:
*     Falls eine Umgebung beendet wird, die komprimiert dargestellt werden soll, 
*     so muss eine Leerzeile ausgegeben werden, da dies nicht in token_output() 
*     geschieht, da ja dort die Umgebung noch aktiv ist, wenn die letzte Zeile 
*     des Absatzes ausgegeben wird. Verstanden? ;-)
* 
*     Aber die Leerzeile darf nur dann ausgegeben werden, wenn nicht noch eine 
*     uebergeordnete komprimierte Umgebung vorhanden ist.
*
*     iEnvLevel cannot be used here, because it has already been decreased in the
*     relevant !end_* routines.
*
*  Parameters:
*     el:   environment level to check
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void end_env_output_line(const int el)
{
	_BOOL flag = FALSE;

	switch (el)
	{
	case 0:							/* only possible on output_end_verbatim() */
		if (iEnvLevel == 0 || (iEnvLevel > 0 && !bEnvCompressed[iEnvLevel]))
			flag = TRUE;
		break;

	case 1:							/* Letzte Umgebung, also Leerzeile, falls komprimiert */
		flag = bEnvCompressed[el];
		break;

	default:							/* Leerzeile nur dann ausgeben, falls die aeussere   */
		/* Umgebung nicht komprimiert ist UND die aktuelle   */
		/* nicht komprimiert ist.                     */
		if (bEnvCompressed[el] && !bEnvCompressed[el - 1])
			flag = TRUE;
		break;
	}

	if (flag)
	{
		switch (desttype)
		{
		case TOWIN:
		case TOWH4:
		case TOAQV:
		case TORTF:
			outln("\\par");
			break;

		case TOHAH:
		case TOHTM:
		case TOMHH:
			break;

		case TOIPF:
			/* Hier keine Leerzeile */
			break;

		case TONRO:
			outln(".fi");
			break;

		case TOKPS:
			outln("newline");
			break;

		case TOUDO:
			break;

		default:
			outln("");
			break;
		}
	}
}





/*******************************************************************************
*
*     HELP ROUTINES
*
******************************************|************************************/

/*******************************************************************************
*
*  itoenum():
*     get number for enumerate environment
*
*  Notes:
*     The number depends on the environment level and item counter.
*
*     TeX-like:
*        2.
*       (b)
*       ii.
*        B.
*        3.
*       (c)
*
*  Parameters:
*     level:   enumeration level
*     count:   item counter
*     string:  string buffer
*
*  Return:
*     formatted number string
*
******************************************|************************************/

LOCAL char *itoenum(int level, int *count, char *string)
{
	switch (level)
	{
	case 1:
	case 5:
		sprintf(string, "%d.", *count);
		break;

	case 2:
	case 6:
		/* Buchstabenbereich checken */
		if (*count > 26)
		{
			error_item_many_enum();
			*count = 1;
		}
		sprintf(string, "(%c)", 'a' - 1 + *count);
		break;

	case 3:
		itoroman(*count, string);
		strcat(string, ".");
		break;

	case 4:
		/* Buchstabenbereich checken */
		if (*count > 26)
		{
			error_item_many_enum();
			*count = 1;
		}
		sprintf(string, "%c.", 'A' - 1 + *count);
		break;
	}

	return string;
}





/*******************************************************************************
*
*  output_begin_verbatim():
*     begin verbatim environment
*
*  Notes:
*     The routine is called by pass2() and c_include_verbatim().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_begin_verbatim(const char *css_class)
{
	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		switch (iDocVerbatimSize)
		{
		case VERB_TINY:
			outln("\\begin{tiny}");
			break;

		case VERB_SMALL:
			outln("\\begin{scriptsize}");
			break;

		case VERB_LARGE:
			outln("\\begin{large}");
			break;

		case VERB_HUGE:
			outln("\\begin{huge}");
			break;
		}
		outln("\\begin{verbatim}");
		break;

	case TOLYX:
		outln("\\layout LyX-Code");
		switch (iDocVerbatimSize)
		{
		case VERB_TINY:
			outln("\\size tiny");
			break;
		case VERB_SMALL:
			outln("\\size small");
			break;
		case VERB_LARGE:
			outln("\\size large");
			break;
		case VERB_HUGE:
			outln("\\size huge");
			break;
		}
		break;

	case TOINF:
		outln("@example");
		break;

	case TOIPF:
		outln(":xmp.");
		break;

	case TOAQV:
	case TOWIN:
	case TOWH4:
		out(win_verb_on);
		switch (iDocVerbatimSize)
		{
		case VERB_TINY:
			voutf("\\fs%d", iDocMonofontSize - 10);
			break;

		case VERB_SMALL:
			voutf("\\fs%d", iDocMonofontSize - 6);
			break;

		case VERB_NORMAL:
			voutf("\\fs%d", iDocMonofontSize - 2);
			break;

		case VERB_LARGE:
			voutf("\\fs%d", iDocMonofontSize + 2);
			break;

		case VERB_HUGE:
			voutf("\\fs%d", iDocMonofontSize + 6);
			break;
		}
		out(" ");
		break;

	case TORTF:
		out(rtf_pardplain);
		out(rtf_verb);
		switch (iDocVerbatimSize)
		{
		case VERB_TINY:
			voutf("\\fs%d ", iDocMonofontSize - 8);
			break;

		case VERB_SMALL:
			voutf("\\fs%d ", iDocMonofontSize - 4);
			break;

		case VERB_NORMAL:
			voutf("\\fs%d ", iDocMonofontSize);
			break;

		case VERB_LARGE:
			voutf("\\fs%d ", iDocMonofontSize + 4);
			break;

		case VERB_HUGE:
			voutf("\\fs%d ", iDocMonofontSize + 8);
			break;
		}
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (sDocVerbatimBackColor.rgb.set)
		{
			voutlnf("<table width=\"100%%\" bgcolor=\"%s\" class=\"%s\"><tr><td>%s",
					html_color_string(&sDocVerbatimBackColor.rgb), css_class, sHtmlMonofontStart);
		}
		switch (iDocVerbatimSize)
		{
		case VERB_TINY:
			outln("<font size=-2>");
			break;

		case VERB_SMALL:
			outln("<font size=-1>");
			break;

		case VERB_LARGE:
			outln("<font size=+1>");
			break;

		case VERB_HUGE:
			outln("<font size=+2>");
			break;
		}
		out("<pre>");
		break;

	case TONRO:
		outln(".nf");
		break;

	case TOLDS:
		outln("<verb>");
		break;

	case TOHPH:
		outln("<ex>");
		break;

	case TOKPS:
		outln("Von");
		break;

	case TOSRC:
	case TOSRP:
		outln(sSrcRemOn);
		break;

	case TOUDO:
		outln("!begin_verbatim");
		break;
	}
}





/*******************************************************************************
*
*  output_end_verbatim():
*     end verbatim environment
*
*  Notes:
*     The routine is called by pass2() and c_include_verbatim().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_end_verbatim(void)
{
	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\end{verbatim}");
		switch (iDocVerbatimSize)
		{
		case VERB_TINY:
			outln("\\end{tiny}");
			break;

		case VERB_SMALL:
			outln("\\end{scriptsize}");
			break;

		case VERB_LARGE:
			outln("\\end{large}");
			break;

		case VERB_HUGE:
			outln("\\end{huge}");
			break;
		}
		break;

	case TOLYX:
		outln("\\layout Standard");
		break;

	case TOINF:
		outln("@end example");
		break;

	case TOIPF:
		outln(":exmp.");
		break;

	case TOAQV:
	case TOWIN:
	case TOWH4:
		outln(win_verb_off);
		break;

	case TORTF:
		outln(rtf_pardplain);
		voutlnf("%s\\fs%d", rtf_norm, iDocPropfontSize);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		outln("</pre>");
		switch (iDocVerbatimSize)
		{
		case VERB_TINY:
			outln("</font>");
			break;

		case VERB_SMALL:
			outln("</font>");
			break;

		case VERB_LARGE:
			outln("</font>");
			break;

		case VERB_HUGE:
			outln("</font>");
			break;
		}

		if (sDocVerbatimBackColor.rgb.set)
		{
			voutlnf("%s</td></tr></table>", sHtmlMonofontEnd);
		}
		break;

	case TOLDS:
		outln("</verb>");
		break;

	case TOHPH:
		outln("<\\ex>");
		break;

	case TOKPS:
		outln("Voff");
		break;

	case TOSRC:
	case TOSRP:
		outln(sSrcRemOff);
		break;

	case TOUDO:
		outln("!end_verbatim");
		break;

	default:
		break;
	}

	end_env_output_line(0);
}





/*******************************************************************************
*
*  output_begin_preformatted():
*     begin preformatted environment
*
*  Notes:
*     The routine is called by pass2()().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_begin_preformatted(void)
{
	switch (desttype)
	{
	case TOUDO:
		outln("!begin_preformatted");
		break;
	default:
		output_begin_verbatim("UDO_env_preformatted");
		break;
	}
}


/*******************************************************************************
*
*  output_end_preformatted():
*     begin preformatted environment
*
*  Notes:
*     The routine is called by pass2()().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_end_preformatted(void)
{
	switch (desttype)
	{
	case TOUDO:
		outln("!end_preformatted");
		break;
	default:
		output_end_verbatim();
		break;
	}
}

/*******************************************************************************
*
*  output_begin_linedraw():
*     begin linedraw environment
*
*  Notes:
*     The routine is called by pass2() and c_include_linedraw().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_begin_linedraw(void)
{
	switch (desttype)
	{
	case TORTF:
		out(rtf_pardplain);
		out(rtf_linedraw);

		switch (iDocLinedrawSize)
		{
		case VERB_TINY:
			voutf("\\fs%d ", iDocMonofontSize - 8);
			break;
		case VERB_SMALL:
			voutf("\\fs%d ", iDocMonofontSize - 4);
			break;
		case VERB_NORMAL:
			voutf("\\fs%d ", iDocMonofontSize);
			break;
		case VERB_LARGE:
			voutf("\\fs%d ", iDocMonofontSize + 4);
			break;
		case VERB_HUGE:
			voutf("\\fs%d ", iDocMonofontSize + 8);
			break;
		}
		pre_linedraw_charset = iCharset;
		break;

	case TOUDO:
		outln("!begin_linedraw");
		break;

	default:
		pre_linedraw_charset = iCharset;
		iCharset = CODE_437;
		output_begin_verbatim("UDO_env_linedraw");
		break;
	}
}





/*******************************************************************************
*
*  output_end_linedraw():
*     end linedraw environment
*
*  Notes:
*     The routine is called by pass2() and c_include_linedraw().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_end_linedraw(void)
{
	switch (desttype)
	{
	case TOUDO:
		outln("!end_linedraw");
		break;

	default:
		output_end_verbatim();
		iCharset = pre_linedraw_charset;
		break;
	}
}





/*******************************************************************************
*
*  output_begin_sourcecode():
*     begin sourcecode environment
*
*  Notes:
*     The routine is called by pass2() and c_include_src().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_begin_sourcecode(void)
{
	switch (desttype)
	{
	case TOSRC:
	case TOSRP:
		break;

	case TOUDO:
		outln("!begin_sourcecode");
		break;

	default:
		if (!no_sourcecode)
		{
			c_begin_quote();
			output_begin_verbatim("UDO_env_sourcecode");
		}
		break;
	}
}





/*******************************************************************************
*
*  output_end_sourcecode():
*     end sourcecode environment
*
*  Notes:
*     The routine is called by pass2() and c_include_src().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_end_sourcecode(void)
{
	switch (desttype)
	{
	case TOSRC:
	case TOSRP:
		outln("");
		break;
	case TOUDO:
		outln("!end_sourcecode");
		break;
	default:
		if (!no_sourcecode)
		{
			output_end_verbatim();
			c_end_quote();
		}
		break;
	}
}





/*******************************************************************************
*
*  output_begin_comment():
*     begin comment environment
*
*  Notes:
*     The routine is called by pass2() and c_include_comment().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_begin_comment(void)
{
	switch (desttype)
	{
	case TOUDO:
		outln(CMD_BEGIN_COMMENT);
		break;
	}
}





/*******************************************************************************
*
*  output_end_comment():
*     end comment environment
*
*  Notes:
*     The routine is called by pass2() and c_include_comment().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_end_comment(void)
{
	switch (desttype)
	{
	case TOUDO:
		outln(CMD_END_COMMENT);
		break;
	}
}





/*******************************************************************************
*
*  strcat_blanks():
*     concatenate <count> spaces to <string>
*
*  Return:
*     enhanced string
*
******************************************|************************************/

LOCAL char *strcat_blanks(char *string, int count)
{
	char li[128];

	switch (desttype)
	{
	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		sprintf(li, "\\li%d", count);	/* count entspricht tics! */
		strcat(string, li);
		break;

	default:
		/* count entspricht Anzahl an Leerzeichen */
		if (use_justification)
			memset(li, INDENT_C, (size_t) count);
		else
			memset(li, ' ', (size_t) count);

		li[count] = EOS;
		strcat(string, li);
		break;
	}

	return string;
}





/*******************************************************************************
*
*  strlen_prev_indent():
*     find length of string to be indented
*
*  Notes:
*     For RTF, it is the value used for \li...
*
*  Return:
*     # of spaces to indent
*
******************************************|************************************/

int strlen_prev_indent(void)
{
	int i, il;

	il = 0;

	for (i = 0; i < iEnvLevel; i++)
	{
		il += iEnvIndent[i];
	}

	return il;
}





/*******************************************************************************
*
*  strlen_indent():
*     find length of string to be indented
*
*  Notes:
*     For RTF, it is the value used for \li...
*
*  Return:
*     # of spaces to indent
*
******************************************|************************************/

GLOBAL int strlen_indent(void)
{
	int i, il;

	il = 0;

	for (i = 0; i <= iEnvLevel; i++)
	{
		il += iEnvIndent[i];
	}

	return il;
}





/*******************************************************************************
*
*  strcat_prev_indent():
*     concatenate spaces to <s> for the previous environment
*
*  Notes:
*     For RTF, a numeric value is used instead of spaces!
*     See the difference to strcat_indent(): < instead of <=
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void strcat_prev_indent(char *s)
{
	int il;
	char sil[64];

	il = strlen_prev_indent();

	if (il == 0)
		return;

	switch (desttype)
	{
	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		sprintf(sil, "\\li%d", il);
		strcat(s, sil);
		break;

	case TOASC:
	case TODRC:
	case TOMAN:
	case TOSTG:
	case TOAMG:
	case TOPCH:
	case TOTVH:
		strcat_blanks(s, il);
		break;

	case TOIPF:						/* <???> */
		break;
	}
}





/*******************************************************************************
*
*  strcat_indent():
*     concatenate spaces to <s> for the previous environment
*
*  Notes:
*     For RTF, a numeric value is used instead of spaces!
*     See the difference to strcat_prev_indent(): <= instead of <
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void strcat_indent(char *s)
{
	int il;
	char sil[64];

	il = strlen_indent();

	if (il == 0)
		return;

	switch (desttype)
	{
	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		sprintf(sil, "\\li%d", il);
		strcat(s, sil);

		if (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT)
			strcat(s, "\\qc");
		else
			strcat(s, "\\qj");

		strcat(s, " ");
		break;

	case TOASC:
	case TODRC:
	case TOMAN:
	case TOSTG:
	case TOAMG:
	case TOPCH:
	case TOTVH:
		strcat_blanks(s, il);
		break;

	case TOIPF:						/* <???> */
		break;
	}
}





/*******************************************************************************
*
*  strcpy_prev_indent():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void strcpy_prev_indent(char *s)
{
	s[0] = EOS;
	strcat_prev_indent(s);
}





/*******************************************************************************
*
*  strcpy_indent():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void strcpy_indent(char *s)
{
	s[0] = EOS;
	strcat_indent(s);
}





/*******************************************************************************
*
*     QUOTES
*
******************************************|************************************/

/*******************************************************************************
*
*  c_begin_quote():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_quote(void)
{
	char quote[1024];
	char *ptr;
	char title[512];
	int j, k;
	size_t len;

	if (!check_iEnvLevel())
		return;

	iEnvLevel++;

	iEnvType[iEnvLevel] = ENV_QUOT;
	env_kind[iEnvLevel] = 0;
	iEnvIndent[iEnvLevel] = 0;
	bEnv1stItem[iEnvLevel] = TRUE;
	bEnv1stPara[iEnvLevel] = TRUE;

	set_env_compressed(iEnvLevel, token[1]);

	quot_level++;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\begin{quote}");
		break;

	case TOLYX:
		outln("\\layout Quote");
		break;

	case TOINF:
		outln("@quotation");
		break;

	case TONRO:
		outln(".RS");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		um_strcpy(quote, "<blockquote", ArraySize(quote), "!c_begin_quote");

		if (token[1][0] == '[')
		{
			token[token_counter - 1][strlen(token[token_counter - 1]) - 1] = EOS;

			for (j = 1; j < token_counter; j++)
			{
				ptr = strstr(token[j], "id=");

				if (ptr != NULL)
				{
					ptr += 3;
					len = strcspn(ptr, " ");

					um_strcat(quote, " id=\"", ArraySize(quote), "!c_begin_quote");
					um_strncat(quote, ptr, len, ArraySize(quote), "!c_begin_quote");
					um_strcat(quote, "\"", ArraySize(quote), "c_begin_quote");
				}

				ptr = strstr(token[j], "class=");

				if (ptr != NULL)
				{
					ptr += 6;
					len = strcspn(ptr, " ");

					um_strcat(quote, " class=\"", ArraySize(quote), "!c_begin_quote");
					um_strncat(quote, ptr, len, ArraySize(quote), "!c_begin_quote");
					um_strcat(quote, "\"", ArraySize(quote), "!c_begin_quote");
				}

				ptr = strstr(token[j], "cite=");

				if (ptr != NULL)
				{
					ptr += 5;
					len = strcspn(ptr, " ");

					um_strcat(quote, " cite=\"", ArraySize(quote), "!c_begin_quote");
					um_strncat(quote, ptr, len, ArraySize(quote), "!c_begin_quote");
					um_strcat(quote, "\"", ArraySize(quote), "!c_begin_quote");
				}

				ptr = strstr(token[j], "lang=");

				if (ptr != NULL)
				{
					ptr += 5;
					len = strcspn(ptr, " ");

					um_strcat(quote, " lang=\"", ArraySize(quote), "!c_begin_quote");
					um_strncat(quote, ptr, len, ArraySize(quote), "!c_begin_quote");
					um_strcat(quote, "\"", ArraySize(quote), "!c_begin_quote");
				}

				ptr = strstr(token[j], "title=");

				if (ptr != NULL)
				{
					um_strcat(quote, " title=\"", ArraySize(quote), "!c_begin_quote");

					ptr += 6;
					if (ptr[0] == '\'')
					{
						um_strcpy(title, ptr + 1, ArraySize(title), "!c_begin_quote");

						len = strlen(title);

						if (title[len - 1] == '\'')
							goto no_blanks;

						k = j;

						do
						{
							k++;
							um_strcat(title, " ", ArraySize(title), "!c_begin_quote");
							um_strcat(title, token[k], ArraySize(title), "!c_begin_quote");
						} while (strrchr(token[k], '\'') == NULL);

						len = strlen(title);

					  no_blanks:
						title[len - 1] = EOS;

						um_strncat(quote, title, len, ArraySize(quote), "!c_begin_quote");
					} else
					{
						len = strcspn(ptr, " ");
						um_strncat(quote, ptr, len, ArraySize(quote), "!c_begin_quote");
					}

					um_strcat(quote, "\"", ArraySize(quote), "!c_begin_quote");
				}
			}
		}

		um_strcat(quote, ">", ArraySize(quote), "!c_begin_quote");
		outln(quote);
/*    outln("<blockquote>");
*/
		break;

	case TOLDS:
		/* siehe token_output() */
		break;

	case TOIPF:
		voutlnf(":lm margin=%d.", quot_level * ENV_IND_ASC_QUOT + 1);
		break;
	}

	switch (desttype)
	{
	case TORTF:
		iEnvIndent[iEnvLevel] = ENV_IND_RTF_QUOT;
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		iEnvIndent[iEnvLevel] = ENV_IND_WIN_QUOT;
		break;

	default:
		iEnvIndent[iEnvLevel] = ENV_IND_ASC_QUOT;
		break;
	}
}





/*******************************************************************************
*
*  c_end_quote():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_quote(void)
{
	if (iEnvLevel == 0 || iEnvType[iEnvLevel] != ENV_QUOT)
		error_end_without_begin(CMD_END_QUOTE, CMD_BEGIN_QUOTE);

	if (iEnvLevel > 0)
	{
		iEnvIndent[iEnvLevel] = 0;
		iEnvLevel--;
	}

	if (quot_level > 0)
	{
		quot_level--;
	}

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\end{quote}");
		outln("");
		break;

	case TOLYX:
		outln("\\layout Standard");
		break;

	case TOINF:
		outln("@end quotation");
		break;

	case TONRO:
		outln(".RE");
		break;

	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		if (quot_level == 0)
		{
			outln("\\li0\\ri0\\fi0 ");
		}
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		outln("</blockquote>");
		break;

	case TOLDS:
		/* siehe token_output() */
		break;

	case TOIPF:
		voutlnf(":lm margin=%d.", quot_level * ENV_IND_ASC_QUOT + 1);
		break;
	}
}





/*******************************************************************************
*
*     CENTER ENVIRONMENT
*    (centered text)
*
******************************************|************************************/

/*******************************************************************************
*
*  c_begin_center():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_center(void)
{
	if (!check_iEnvLevel())
		return;

	iEnvLevel++;

	iEnvType[iEnvLevel] = ENV_CENT;
	env_kind[iEnvLevel] = 0;
	iEnvIndent[iEnvLevel] = 0;
	bEnv1stItem[iEnvLevel] = TRUE;
	bEnv1stPara[iEnvLevel] = TRUE;

	/*
	 * !compressed (was !short) verbieten, da UDO dann nur Schrott erzeugt
	 * und eine Anpassung unheimlich problematisch ist
	 */
	switch (desttype)
	{
	case TOHTM:
	case TOMHH:
	case TOHAH:
		bEnvCompressed[iEnvLevel] = FALSE;
		break;

	default:
		set_env_compressed(iEnvLevel, token[1]);
		break;
	}

	cent_level++;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\begin{center}");
		break;

	case TOIPF:
		outln(":lines align=center.");
		break;

	case TONRO:
		outln(".ad c");
		break;

	case TOLYX:
		outln("\\layout Standard");
		outln("\\align center");
		break;
	}
}

/*******************************************************************************
*
*  c_end_center():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_center(void)
{
	if (iEnvLevel == 0 || iEnvType[iEnvLevel] != ENV_CENT)
		error_end_without_begin(CMD_END_CENTER, CMD_BEGIN_CENTER);

	if (iEnvLevel > 0)
	{
		iEnvIndent[iEnvLevel] = 0;
		iEnvLevel--;
	}

	if (cent_level > 0)
		cent_level--;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\end{center}");
		outln("");
		break;

	case TOIPF:
		outln(":elines.");
		break;

	case TONRO:
		outln(".na");
		break;

	case TOLYX:
		outln("\\layout Standard");
		break;
	}
}





/*******************************************************************************
*
*     RIGHT ENVIRONMENT
*    (right-justified text)
*
******************************************|************************************/

/*******************************************************************************
*
*  c_begin_flushright():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_flushright(void)
{
	if (!check_iEnvLevel())
		return;

	iEnvLevel++;

	iEnvType[iEnvLevel] = ENV_RIGH;
	env_kind[iEnvLevel] = 0;
	iEnvIndent[iEnvLevel] = 0;
	bEnv1stItem[iEnvLevel] = TRUE;
	bEnv1stPara[iEnvLevel] = TRUE;

	/*
	 * !compressed (was !short) verbieten, da UDO dann nur Schrott erzeugt
	 * und eine Anpassung unheimlich problematisch ist
	 */
	switch (desttype)
	{
	case TOHTM:
	case TOMHH:
	case TOHAH:
		bEnvCompressed[iEnvLevel] = FALSE;
		break;

	default:
		set_env_compressed(iEnvLevel, token[1]);
		break;
	}

	flushright_level++;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\begin{flushright}");
		break;

	case TOLYX:
		outln("\\layout Standard");
		outln("\\align right");
		break;

	case TONRO:
		outln(".ad r");
		break;

	case TOINF:
		outln("@flushright");
		outln("");
		break;

	case TOIPF:
		outln(":lines align=right.");
		break;
	}
}





/*******************************************************************************
*
*  c_end_flushright():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_flushright(void)
{
	if (iEnvLevel == 0 || iEnvType[iEnvLevel] != ENV_RIGH)
		error_end_without_begin(CMD_END_RIGHT, CMD_BEGIN_RIGHT);

	if (iEnvLevel > 0)
	{
		iEnvIndent[iEnvLevel] = 0;
		iEnvLevel--;
	}

	if (flushright_level > 0)
		flushright_level--;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\end{flushright}");
		outln("");
		break;

	case TOLYX:
		outln("\\layout Standard");
		break;

	case TOINF:
		outln("@end flushright");
		outln("");
		break;

	case TONRO:
		outln(".na");
		break;

	case TOIPF:
		outln(":elines.");
		break;
	}
}





/*******************************************************************************
*
*     LEFT ENVIRONMENT
*    (left-justified text)
*
******************************************|************************************/

/*******************************************************************************
*
*  c_begin_flushleft():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_flushleft(void)
{
	if (!check_iEnvLevel())
		return;

	iEnvLevel++;

	iEnvType[iEnvLevel] = ENV_LEFT;
	env_kind[iEnvLevel] = 0;
	iEnvIndent[iEnvLevel] = 0;
	bEnv1stItem[iEnvLevel] = TRUE;
	bEnv1stPara[iEnvLevel] = TRUE;

	/*
	 * !compressed (was !short) verbieten, da UDO dann nur Schrott erzeugt
	 * und eine Anpassung unheimlich problematisch ist
	 */
	switch (desttype)
	{
	case TOHTM:
	case TOMHH:
	case TOHAH:
		bEnvCompressed[iEnvLevel] = FALSE;
		break;

	default:
		set_env_compressed(iEnvLevel, token[1]);
		break;
	}

	flushleft_level++;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\begin{flushleft}");
		break;

	case TOLYX:
		outln("\\layout Standard");
		outln("\\align left");
		break;

	case TONRO:
		outln(".ad l");
		break;

	case TOINF:
		outln("@flushleft");
		outln("");
		break;

	case TOIPF:
		outln(":lines align=left.");
		break;
	}
}





/*******************************************************************************
*
*  c_end_flushleft():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_flushleft(void)
{
	if (iEnvLevel == 0 || iEnvType[iEnvLevel] != ENV_LEFT)
		error_end_without_begin(CMD_END_LEFT, CMD_BEGIN_LEFT);

	if (iEnvLevel > 0)
	{
		iEnvIndent[iEnvLevel] = 0;
		iEnvLevel--;
	}

	if (flushleft_level > 0)
		flushleft_level--;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\end{flushleft}");
		outln("");
		break;
	case TOLYX:
		outln("\\layout Standard");
		break;
	case TOINF:
		outln("@end flushleft");
		outln("");
		break;
	case TONRO:
		outln(".na");
		break;
	case TOIPF:
		outln(":elines.");
		break;
	}
}





/*******************************************************************************
*
*  c_begin_itemize():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_itemize(void)
{
	if (!check_iEnvLevel())
		return;

	iEnvLevel++;

	iEnvType[iEnvLevel] = ENV_ITEM;
	env_kind[iEnvLevel] = 0;
	iEnvIndent[iEnvLevel] = 0;
	bEnv1stItem[iEnvLevel] = TRUE;
	bEnv1stPara[iEnvLevel] = TRUE;

	set_env_compressed(iEnvLevel, token[1]);

	iItemLevel++;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\begin{itemize}");
		if (bEnvCompressed[iEnvLevel])
		{
			outln("\\itemsep 0pt");
			outln("\\parsep 0pt");
			outln("\\parskip 0pt");
		}
		break;

	case TOLYX:
		if (iEnvLevel > 1)
			outln("\\begin_deeper");
		break;

	case TOINF:
		out("@itemize ");
		switch (iItemLevel)
		{
		case 1:
		case 3:
			outln("@bullet");
			break;
		case 2:
		case 4:
			outln("@minus");
			break;
		}
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (bParagraphOpen)				/* paragraph still open?!? */
		{
			if (!bEnvCompressed[iEnvLevel])	/* no compressed environment */
			{
				/* we're in a list environment: */
				if ((iEnvLevel > 1) && (iEnvType[iEnvLevel - 1] != ENV_LIST))
				{
					outln("</p>\n");	/* close previous paragraph first */
				} else
				{
					outln("\n");
				}
			}
		}

		bParagraphOpen = FALSE;

		outln("<ul>");
		break;

	case TOHPH:
		outln("<list>");
		break;

	case TOLDS:
		outln("<itemize>");
		break;

	case TOIPF:
		if (bEnvCompressed[iEnvLevel])
			outln(":ul compact.");
		else
			outln(":ul.");
		break;

	case TOKPS:
		voutlnf("/off%d (000) addStrSpaceLeft", iEnvLevel);
		break;
	}

	switch (desttype)
	{
	case TORTF:
		iEnvIndent[iEnvLevel] = ENV_IND_RTF_ITEM;
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		iEnvIndent[iEnvLevel] = ENV_IND_WIN_ITEM;
		break;

	default:
		iEnvIndent[iEnvLevel] = ENV_IND_ASC_ITEM;
		break;
	}
}





/*******************************************************************************
*
*  c_begin_enumerate():
*     starts enumeration environment output
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_enumerate(void)
{
	char sNumStart[256];				/* buffer for tokens */
	int numStart;						/* buffer for enumeration start value */

	if (!check_iEnvLevel())
		return;

	tokcpy2(sNumStart, 256);			/* get optional enumeration start value */

	numStart = atoi(sNumStart);

	iEnvLevel++;

	iEnvType[iEnvLevel] = ENV_ENUM;
	env_kind[iEnvLevel] = 0;
	enum_count[iEnvLevel] = numStart;
	iEnvIndent[iEnvLevel] = 0;
	bEnv1stItem[iEnvLevel] = TRUE;
	bEnv1stPara[iEnvLevel] = TRUE;

	set_env_compressed(iEnvLevel, token[1]);

	iEnumLevel++;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\begin{enumerate}");
		if (bEnvCompressed[iEnvLevel])
		{
			outln("\\itemsep 0pt");
			outln("\\parsep 0pt");
			outln("\\parskip 0pt");
		}
		break;

	case TOLYX:
		if (iEnvLevel > 1)
			outln("\\begin_deeper");
		break;

	case TOINF:
		out("@enumerate ");
		switch (iEnumLevel)
		{
		case 1:
			outln("1");
			break;

		case 2:
			outln("a");
			break;

		case 3:
			outln("1");
			break;

		case 4:
			outln("A");
			break;
		}
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (bParagraphOpen)				/* paragraph still open?!? */
		{
			if (!bEnvCompressed[iEnvLevel])	/* no compressed environment */
			{
				switch (iEnvType[iEnvLevel])
				{
				case ENV_DESC:
					outln("</p>\n");	/* close previous paragraph first */
					break;

				case ENV_LIST:
					outln("</p>");		/* close previous paragraph first */
					break;

				default:
					out("</p>");		/* close previous paragraph first */
					break;
				}
			}
		}

		bParagraphOpen = FALSE;

		out("\n<ol class=\"UDO_env_enumerate\"");

		switch (iEnumLevel)				/* HTML 3.2 Moeglichkeiten nutzen */
		{
		case 1:
		case 5:
			break;

		case 2:
		case 6:
			outln(" type=a");
			break;

		case 3:
			outln(" type=i");
			break;

		case 4:
			outln(" type=A");
			break;
		}

		if (numStart)					/* add start value, if required */
		{
			voutf(" start=\"%d\"", numStart);
		}

		outln(">");
		break;

	case TOHPH:
		outln("<list>");
		break;

	case TOLDS:
		outln("<enum>");
		break;

	case TOIPF:
		if (bEnvCompressed[iEnvLevel])
			outln(":ol compact.");
		else
			outln(":ol.");
		break;

	case TOKPS:
		voutlnf("/off%d (000) addStrSpaceLeft", iEnvLevel);
		break;
	}

	switch (desttype)
	{
	case TORTF:
		iEnvIndent[iEnvLevel] = ENV_IND_RTF_ENUM;
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		iEnvIndent[iEnvLevel] = ENV_IND_WIN_ENUM;
		break;

	default:
		if (iEnumLevel == 3)
			iEnvIndent[iEnvLevel] = 4 + ENV_IND_ASC_ENUM;
		else
			iEnvIndent[iEnvLevel] = ENV_IND_ASC_ENUM;
		break;
	}
}





/*******************************************************************************
*
*  c_begin_description():
*     output begin of description environment
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_description(void)
{
	if (!check_iEnvLevel())
		return;

	iEnvLevel++;

	iEnvType[iEnvLevel] = ENV_DESC;
	env_kind[iEnvLevel] = 0;
	iEnvIndent[iEnvLevel] = 0;
	bEnv1stItem[iEnvLevel] = TRUE;
	bEnv1stPara[iEnvLevel] = TRUE;

	set_env_compressed(iEnvLevel, token[1]);

	iDescLevel++;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\begin{description}");
		if (bEnvCompressed[iEnvLevel])
		{
			outln("\\itemsep 0pt");
			outln("\\parsep 0pt");
			outln("\\parskip 0pt");
		}
		break;

	case TOLYX:
		if (iEnvLevel > 1)
			outln("\\begin_deeper");
		break;

	case TOINF:
		outln("@table @strong");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		outln("<dl class=\"UDO_env_description\">");
		bParagraphOpen = FALSE;			/* <p> not opened yet! */
		break;

	case TOHPH:
		outln("<list>");
		break;

	case TOLDS:
		outln("<descrip>");
		break;

	case TOIPF:
		if (bEnvCompressed[iEnvLevel])
			outln(":dl compact break=none tsize=4.");
		else
			outln(":dl break=none tsize=4.");
		break;

	case TOKPS:
		outln("Bon");
		outln("/offDesc (000000) addStrSpaceLeft");
		outln("Boff");
		outln("description");
		break;
	}

	switch (desttype)
	{
	case TORTF:
		iEnvIndent[iEnvLevel] = ENV_IND_RTF_DESC;
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		iEnvIndent[iEnvLevel] = ENV_IND_WIN_DESC;
		break;

	default:
		iEnvIndent[iEnvLevel] = ENV_IND_ASC_DESC;
		break;
	}
}





/*******************************************************************************
*
*  c_begin_list():
*     output begin of a list
*
*  Notes:
*     Supported lists are LIST_... (CONSTANT.H).
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_begin_list(int listkind, const char *css_class)
{
	char sWidth[256];					/* buffer for tokens */
	char sCompressed[256];				/* buffer for compare strings */
	char *ptr;
	int ll;

	if (!check_iEnvLevel())
		return;

	switch (desttype)
	{
	case TOLDS:
	case TOHPH:
	case TONRO:
		c_begin_description();
		return;

	case TOHTM:
	case TOHAH:
		if (html_no_xlist)
		{
			c_begin_description();
			return;
		}
		break;
	}

	iEnvLevel++;

	iEnvType[iEnvLevel] = ENV_LIST;
	env_kind[iEnvLevel] = listkind;
	iEnvIndent[iEnvLevel] = 0;
	bEnv1stItem[iEnvLevel] = TRUE;
	bEnv1stPara[iEnvLevel] = TRUE;

	iListLevel++;

	/* get additional token and check for "!short", "!compressed" and "!not_compressed" */
	/* "!short" is deprecated and throws a warning in set_env_compressed() */

	sCompressed[0] = EOS;				/* clear buffer string */
	token[0][0] = EOS;					/* skip first token */
	tokcpy2(sWidth, ArraySize(sWidth));	/* get second token */

	delete_once(sWidth, "[");			/* remove brackets (if any) */
	delete_last(sWidth, "]");

	if ((ptr = strstr(sWidth, "!short")) != NULL)
	{
		/* --- check if user used !short at the beginning by mistake --- */

		strcpy(sCompressed, "!short");	/* for set_env_compressed() */

		if (ptr == sWidth)				/* identical? */
		{
			/* "!short" found at the beginning - which is wrong! */

			/* also remove the additional space, added by tokcpy2() */
			if (!delete_once(sWidth, "!short "))
				delete_once(sWidth, "!short");
		} else							/* not found at the beginning */
		{
			delete_last(sWidth, " !short");	/* remove from the end */
		}
	} else if ((ptr = strstr(sWidth, "!compressed")) != NULL)
	{
		/* --- check if user used !compressed at the beginning by mistake --- */

		/* for set_env_compressed() */
		strcpy(sCompressed, "!compressed");

		if (ptr == sWidth)			/* identical? */
		{
			/* "!compressed" found at the beginning - which is wrong! */

			/* also remove the additional space, added by tokcpy2() */
			if (!delete_once(sWidth, "!compressed "))
				delete_once(sWidth, "!compressed");
		} else						/* not found at the beginning */
		{
			/* remove from the end */
			delete_last(sWidth, " !compressed");
		}
	} else if ((ptr = strstr(sWidth, "!not_compressed")) != NULL)
	{
		/* --- check if user used !not_compressed at the beginning by mistake --- */

		/* for set_env_compressed() */
		strcpy(sCompressed, "!not_compressed");

		if (ptr == sWidth)		/* identical? */
		{
			/* "!not_compressed" found at the beginning - which is wrong! */

			/* also remove the additional space, added by tokcpy2() */
			if (!delete_once(sWidth, "!not_compressed "))
				delete_once(sWidth, "!not_compressed");
		} else					/* not found at the beginning */
		{
			/* remove from the end */
			delete_last(sWidth, " !not_compressed");
		}
	} else if ((ptr = strchr(sWidth, '!')) != NULL)
	{
		warning_message(_("unrecognized option '%s'"), ptr);
	}

	del_internal_styles(sWidth);
	qdelete_all(sWidth, "!-", 2);
	replace_udo_quotes(sWidth);

	/* check the compressed flag */
	set_env_compressed(iEnvLevel, sCompressed);

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		switch (listkind)
		{
		case LIST_BOLD:
			out("\\begin{blist}");
			break;

		case LIST_ITALIC:
			out("\\begin{ilist}");
			break;

		case LIST_TYPEWRITER:
			out("\\begin{tlist}");
			break;

		default:
			out("\\begin{xlist}");
			break;
		}

		voutlnf("{%s}", sWidth);

		if (bEnvCompressed[iEnvLevel])
		{
			outln("\\itemsep 0pt");
			outln("\\parsep 0pt");
			outln("\\parskip 0pt");
		}
		break;

	case TOLYX:
		if (iEnvLevel > 1)
			outln("\\begin_deeper");
		break;

	case TOINF:
		outln("@table @asis");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		voutlnf("<table class=\"%s\">", css_class);
		break;

	case TOSTG:
	case TOAMG:
	case TOASC:
	case TODRC:
	case TOMAN:
	case TOPCH:
	case TOTVH:
		ll = (int) strlen(sWidth);
		iEnvIndent[iEnvLevel] = ll + (iListLevel == 1 ? 3 : 2);
		break;

	case TOKPS:
		ll = (int) strlen(sWidth);
		iEnvIndent[iEnvLevel] = ll + 3;
		{
			char space[50];

			int i;

			space[0] = EOS;
			for (i = 0; i < iEnvIndent[iEnvLevel]; i++)
				strcat(space, "0");
			switch (listkind)
			{
			case LIST_BOLD:
				outln("Bon");
				break;

			case LIST_ITALIC:
				outln("Ion");
				break;

			case LIST_TYPEWRITER:
				outln("Von");
				break;
			}
			outln("/offCount offCount 1 add def");
			outln("/offCountS offCount 4 add def");
			voutlnf("offList offCount get (%s00) addStrSpaceLeft", space);

			switch (listkind)
			{
			case LIST_BOLD:
				outln("Boff");
				break;

			case LIST_ITALIC:
				outln("Ioff");
				break;

			case LIST_TYPEWRITER:
				outln("Voff");
				break;
			}
		}
		break;

	case TOIPF:
		if (bEnvCompressed[iEnvLevel])
			voutlnf(":dl compact break=none tsize=%d.", (int) strlen(sWidth) + 4);
		else
			voutlnf(":dl break=none tsize=%d.", (int) strlen(sWidth) + 4);
		break;

	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		recode_chrtab(sWidth, CHRTAB_ANSI);

		ll = (int) toklen(sWidth);

		if (desttype == TORTF)
		{
			iEnvIndent[iEnvLevel] = ll * iDocCharwidth;
		} else
		{
#if 1
			iEnvIndent[iEnvLevel] = ll * iDocCharwidth;
#else
			switch (listkind)
			{
			case LIST_BOLD:
				ll = calc_ttf_twip(sWidth, TTF_TIMES, TTF_BOLD);
				break;

			case LIST_ITALIC:
				ll = calc_ttf_twip(sWidth, TTF_TIMES, TTF_ITALIC);
				break;

			case LIST_TYPEWRITER:
				ll = calc_ttf_twip(sWidth, TTF_COURIER, TTF_REGULAR);
				break;

			default:
				ll = calc_ttf_twip(sWidth, TTF_TIMES, TTF_REGULAR);
				break;
			}
			iEnvIndent[iEnvLevel] = ll;
#endif
		}
		break;
	}
}





/*******************************************************************************
*
*  c_begin_xlist():
*     wrapper for c_begin_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_xlist(void)
{
	c_begin_list(LIST_NORMAL, "UDO_env_xlist");
}





/*******************************************************************************
*
*  c_begin_blist():
*     wrapper for c_begin_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_blist(void)
{
	c_begin_list(LIST_BOLD, "UDO_env_blist");
}





/*******************************************************************************
*
*  c_begin_ilist():
*     wrapper for c_begin_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_ilist(void)
{
	c_begin_list(LIST_ITALIC, "UDO_env_ilist");
}





/*******************************************************************************
*
*  c_begin_tlist():
*     wrapper for c_begin_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_tlist(void)
{
	c_begin_list(LIST_TYPEWRITER, "UDO_env_tlist");
}





/*******************************************************************************
*
*  add_description():
*     get the content of !item [...] and copy it into 1st token, ] included
*
*  Notes:
*     Gesucht wird die erste eckige Klammer, die nicht durch ein ! gequotet wird.
*
*     fast komplett neu, wegen Quotefunktion
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void add_description(void)
{
	int i;
	size_t sl;
	_BOOL finished = FALSE;
	_BOOL no_bracket;
	char *found;
	char *ptr;

	sl = strlen(token[1]);

	/* Alles im ersten Token? */
	if (sl > 1 && token[1][sl - 1] == ']' && token[1][sl - 2] != '!')
	{
		replace_all(token[1], "!]", "]");
		um_strcat(token[0], token[1], MAX_TOKEN_LEN + 1, "add_description [1]");
		token[1][0] = EOS;
		return;
	}


	/* Die Sache sieht komplizierter aus, da der Item-Inhalt */
	/* ueber mehrere Tokens verteilt ist */

	no_bracket = TRUE;
	i = 1;

	while ((!finished) && (i < token_counter))
	{
		if (token[i][0] != EOS)
		{
			if ((found = strchr(token[i], ']')) == NULL)
			{
				um_strcat(token[0], token[i], MAX_TOKEN_LEN + 1, "add_description [2]");
				um_strcat(token[0], " ", MAX_TOKEN_LEN + 1, "add_description [3]");
				token[i][0] = EOS;
				i++;
			} else
			{
				while (found != NULL && found[-1] == '!')
				{
					found--;
					delete_once(found, "!");
					ptr = found + 1;
					found = strchr(ptr, ']');
				}

				if (found == NULL)
				{
					/* wie oben */
					um_strcat(token[0], token[i], MAX_TOKEN_LEN + 1, "add_description [4]");
					um_strcat(token[0], " ", MAX_TOKEN_LEN + 1, "add_description [5]");
					token[i][0] = EOS;
					i++;
				} else
				{
					um_strcat(token[0], token[i], MAX_TOKEN_LEN + 1, "add_description [6]");
					token[i][0] = EOS;
					finished = TRUE;
					no_bracket = FALSE;
				}
			}
		} else
		{
			finished = TRUE;
		}
	}

	/* Warnung ausgeben, falls keine (nicht-quotierte) "]" gefunden wurde */

	if (no_bracket)
	{
		error_unexpected_eol();
	}
}





/*******************************************************************************
*
*  c_item():
*     format an item
*
*  Notes:
*     The first char of token[0] HAS TO BE a space, or token_output() has
*     difficulties to properly output the stuff.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_item(void)
{
	char s[MAX_TOKEN_LEN + 512];
	char li[128];
	char ri[128];
	char sBig[MAX_TOKEN_LEN + 100];
	char sTemp[MAX_TOKEN_LEN + 1];
	char sAdd[128];
	size_t tl, sl, i;
	int ll, lp;

	if (iEnvLevel == 0 || (iEnvType[iEnvLevel] != ENV_ITEM && iEnvType[iEnvLevel] != ENV_ENUM && iEnvType[iEnvLevel] != ENV_DESC && iEnvType[iEnvLevel] != ENV_LIST))
		error_message(_("'!item' outside environment"));

	bEnv1stPara[iEnvLevel] = TRUE;

	tokens_contain_item = TRUE;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		strcpy(token[0], "\\item");
		switch (iEnvType[iEnvLevel])
		{
		case ENV_DESC:
		case ENV_LIST:
			if (token[1][0] == '[')
				add_description();
			break;
		}
		break;

	case TOLYX:
		token[0][0] = EOS;
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:
			outln("\\layout Itemize");
			outln("");
			break;

		case ENV_ENUM:
			outln("\\layout Enumerate");
			outln("");
			break;

		case ENV_DESC:
			outln("\\layout Description");
			outln("");
			break;

		case ENV_LIST:
			outln("\\layout List");
			outln("");
			break;
		}

		switch (iEnvType[iEnvLevel])
		{
		case ENV_DESC:
			if (token[1][0] == '[')
			{
				add_description();
				delete_once(token[0], "[");
				delete_last(token[0], "]");
			}
			space2nbsp(token[0]);
			break;

		case ENV_LIST:
			if (token[1][0] == '[')
			{
				add_description();
				delete_once(token[0], "[");
				delete_last(token[0], "]");
			}
			space2nbsp(token[0]);

			switch (env_kind[iEnvLevel])
			{
			case LIST_BOLD:
				strinsert(token[0], "\\series bold ");
				um_strcat(token[0], "\\series default ", MAX_TOKEN_LEN + 1, "c_item[2]");
				break;

			case LIST_ITALIC:
				strinsert(token[0], "\\shape italic ");
				um_strcat(token[0], "\\shape default ", MAX_TOKEN_LEN + 1, "c_item[3]");
				break;

			case LIST_TYPEWRITER:
				strinsert(token[0], "\\family typewriter ");
				um_strcat(token[0], "\\family default ", MAX_TOKEN_LEN + 1, "!item");
				break;
			}
			break;
		}
		break;

	case TOINF:
		strcpy(token[0], "@item ");
		switch (iEnvType[iEnvLevel])
		{
		case ENV_DESC:
		case ENV_LIST:
			if (token[1][0] == '[')
			{
				add_description();
				delete_once(token[0], "[");
				delete_last(token[0], "]");
			}
			um_strcat(token[0], "\n", MAX_TOKEN_LEN + 1, "c_item[5]");
			break;
		}
		break;

	case TOSTG:
	case TOAMG:
	case TOASC:
	case TODRC:
	case TOMAN:
	case TOPCH:
	case TOTVH:
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:
			token[0][0] = EOS;
			tl = strlen_indent();
			if (tl > 1)
			{
				memset(sAdd, ' ', (size_t) (tl - 1));
				sAdd[tl - 1] = EOS;
				um_strcat(token[0], sAdd, MAX_TOKEN_LEN + 1, "c_item[6]");
				token[0][tl - 2] = itemchar[iItemLevel][0];
			}
			break;

		case ENV_ENUM:
			enum_count[iEnvLevel]++;
			itoenum(iEnumLevel, &(enum_count[iEnvLevel]), s);
			sl = strlen(s);
			token[0][0] = EOS;
			tl = strlen_indent();

			if (tl > 1)
			{
				memset(sAdd, ' ', (size_t) (tl - 1));
				sAdd[tl - 1] = EOS;
				um_strcat(token[0], sAdd, MAX_TOKEN_LEN + 1, "c_item[7]");
				for (i = 0; i < sl; i++)
				{
					token[0][tl - sl - 1 + i] = s[i];
				}
			}
			break;

		case ENV_DESC:
			token[0][0] = EOS;
			strcpy_prev_indent(li);
			if (token[1][0] == '[')
			{
				add_description();

				if (desttype == TOSTG && bDocAutorefItemsOff)
				{
					delete_once(token[0], "[");
					delete_last(token[0], "]");
					del_internal_styles(token[0]);
					strcpy(sTemp, token[0]);
					replace_all(sTemp, "\"", "\\\"");
					sprintf(sBig, "@{B}@{\"%s\" ignore}@{b}", sTemp);

					if (insert_placeholder(sBig, sBig, sBig, token[0]))
						sprintf(token[0], " %s%s", li, sBig);
					else
						token[0][0] = EOS;
				} else
				{
					replace_once(token[0], "[", BOLD_ON);
					replace_last(token[0], "]", BOLD_OFF);
					strinsert(token[0], li);
					strinsert(token[0], " ");
				}
			}
			break;

		case ENV_LIST:
			token[0][0] = EOS;
			if (token[1][0] == '[')
			{
				add_description();
				delete_once(token[0], "[");
				delete_last(token[0], "]");
			}

			ri[0] = EOS;
			ll = iEnvIndent[iEnvLevel] - (iListLevel == 1 ? 2 : 1);

			tl = toklen(token[0]);

			sAdd[0] = EOS;

			if (((int) tl) < ll)
			{
				memset(sAdd, ' ', (size_t) (ll - tl));
				sAdd[ll - tl] = EOS;
				/* sAdd wird weiter unten hinzugefuegt */
			}

			strcpy_prev_indent(li);

			/* Hier fuer den ST-Guide noch !autoref_items supporten */
			if (desttype == TOSTG && bDocAutorefItemsOff)
			{
				del_internal_styles(token[0]);
				strcpy(sTemp, token[0]);
				replace_all(sTemp, "\"", "\\\"");
				sprintf(sBig, "@{\"%s\" ignore}", sTemp);

				switch (env_kind[iEnvLevel])
				{
				case LIST_BOLD:
					strinsert(sBig, "@{B}");
					strcat(sBig, "@{b}");
					break;

				case LIST_ITALIC:
					strinsert(sBig, "@{I}");
					strcat(sBig, "@{i}");
					break;
				}

				if (insert_placeholder(sBig, sBig, sBig, token[0]))
				{
					strcat(sBig, ri);
					strinsert(sBig, li);
					strcat(sBig, sAdd);
				} else
				{
					token[0][0] = EOS;
				}

				um_strcpy(token[0], sBig, MAX_TOKEN_LEN + 1, "c_item[12]");
			} else
			{
				switch (env_kind[iEnvLevel])
				{
				case LIST_BOLD:
					sprintf(s, "%s%s%s%s%s", li, BOLD_ON, token[0], BOLD_OFF, ri);
					break;

				case LIST_ITALIC:
					sprintf(s, "%s%s%s%s%s", li, ITALIC_ON, token[0], ITALIC_OFF, ri);
					break;

				default:
					sprintf(s, "%s%s%s", li, token[0], ri);
					break;
				}

				um_strcpy(token[0], s, MAX_TOKEN_LEN + 1, "c_item[13]");
				um_strcat(token[0], sAdd, MAX_TOKEN_LEN + 1, "c_item[14]");
			}
			if (token[0][0] != EOS && iListLevel == 1)
				strinsert(token[0], " ");

			break;
		}

		if (use_justification)
		{
			space2indent(token[0]);
		}
		break;

	case TONRO:
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:
			strcpy(token[0], ".TP\n.B o\n");
			break;

		case ENV_ENUM:
			enum_count[iEnvLevel]++;
			itoenum(iEnumLevel, &(enum_count[iEnvLevel]), s);
			sprintf(token[0], ".TP\n.B %s\n", s);
			break;

		case ENV_DESC:
			strcpy(token[0], ".TP\n");
			if (token[1][0] == '[')
			{
				add_description();
				replace_once(token[0], "[", ".B ");
				replace_last(token[0], "]", "\n");
			}
			break;
		}
		break;

	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:
			ll = strlen_indent();
			sprintf(sBig, "\\pard\\ \\tqr\\tx%d\\tx%d\\li%d\\fi-%d\\qj\\tab %s\\tab", ll - 167, ll, ll, ll,
					itemchar[iItemLevel]);
			break;

		case ENV_ENUM:
			enum_count[iEnvLevel]++;
			ll = strlen_indent();
			itoenum(iEnumLevel, &(enum_count[iEnvLevel]), s);
			sprintf(sBig, "\\pard\\tqr\\tx%d\\tx%d\\li%d\\fi-%d\\qj\\tab %s\\tab", ll - 167, ll, ll, ll, s);
			break;

		case ENV_DESC:
			token[0][0] = EOS;
			sBig[0] = EOS;
			if (token[1][0] == '[')		/* there is a description title! */
			{
				add_description();
				replace_once(token[0], "[", BOLD_ON);
				replace_last(token[0], "]", BOLD_OFF);
				um_strcpy(sBig, token[0], ArraySize(sBig), "c_item[17]");

				if (desttype == TORTF)	/* RTF formatting: "{<descriptionTitle>\par }" */
				{
					c_rtf_styles(sBig);
					c_rtf_quotes(sBig);
					replace_udo_quotes(sBig);
				} else
				{
					c_win_styles(sBig);
					replace_udo_quotes(sBig);
					if (!bDocAutorefItemsOff)
					{
						auto_references(sBig, FALSE, "", 0, 0);
					}
				}
			}

			ll = strlen_indent();
			strcpy(sTemp, sBig);

			/* output adjustment for description: */
			/* "\\pard"   = reset paragraph parameters */
			/* "\\qj"     = justified alignment */
			/* "\\fi-xxx" = first line (left) indent */
			/* "\\lixxx"  = left indent of paragraph */

			/* output description title: */
			/* "%s"       = description title */

			/* output paragraph adjustment for description content: */
			/* "\\pard"   = reset paragraph parameters */
			/* "\\qj"     = justified alignment */
			/* "\\lixxx"  = left indent of paragraph */
			sprintf(sBig, "\\pard\\qj\\fi-%d\\li%d %s\\pard\\qj\\li%d ", 567, ll, sTemp, ll);
			break;

		case ENV_LIST:
			token[0][0] = EOS;
			sBig[0] = EOS;
			if (token[1][0] == '[')
			{
				add_description();
				delete_once(token[0], "[");
				delete_last(token[0], "]");
				um_strcpy(sBig, token[0], ArraySize(sBig), "c_item[18]");
				if (desttype == TORTF)
				{
					c_rtf_styles(sBig);
					c_rtf_quotes(sBig);
					replace_udo_quotes(sBig);
				} else
				{
					c_win_styles(sBig);
					replace_udo_quotes(sBig);
					if (!bDocAutorefItemsOff)
					{
						auto_references(sBig, FALSE, "", 0, 0);
					}
				}
			}
			ll = strlen_indent();

			if (iEnvLevel > 1)
			{
#if 1
				lp = ll - strlen_prev_indent();
#else
				if (iEnvType[iEnvLevel - 1] == ENV_LIST)
					lp = ll - strlen_prev_indent();
				else
					lp = ll - iEnvIndent[iEnvLevel - 1];
#endif
			} else
			{
				lp = ll;
			}

			strcpy(sTemp, sBig);

			switch (env_kind[iEnvLevel])
			{
			case LIST_NORMAL:
				sprintf(sBig, "\\pard\\li%d\\fi-%d\\tx%d\\qj %s\\tab", ll, lp, ll, sTemp);
				break;

			case LIST_BOLD:
				sprintf(sBig, "\\pard\\li%d\\fi-%d\\tx%d\\qj {\\b %s}\\tab", ll, lp, ll, sTemp);
				break;

			case LIST_ITALIC:
				sprintf(sBig, "\\pard\\li%d\\fi-%d\\tx%d\\qj {\\i %s}\\tab", ll, lp, ll, sTemp);
				break;

			case LIST_TYPEWRITER:
				sprintf(sBig, "\\pard\\li%d\\fi-%d\\tx%d\\qj {\\f1 %s}\\tab", ll, lp, ll, sTemp);
				break;
			}
			break;
		}

		if (insert_placeholder(sBig, sBig, sBig, sBig))
		{
			um_strcpy(token[0], sBig, MAX_TOKEN_LEN + 1, "c_item[19]");
		} else
		{
			token[0][0] = EOS;
		}
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:					/* <ul> list item */
		case ENV_ENUM:					/* <ol> list item */
			if (!bEnv1stItem[iEnvLevel])	/* not the first <li>? */
			{
				if (!bEnvCompressed[iEnvLevel])
					out("</p>");

				outln("</li>");
			}
			strcpy(sBig, "<li>");
			if (!bEnvCompressed[iEnvLevel])
				strcat(sBig, "<p>");	/* output <p> */

			bEnv1stPara[iEnvLevel] = TRUE;	/* 1st paragraph */
			break;

		case ENV_DESC:
			if (!bEnv1stItem[iEnvLevel])	/* handle still open <dd> tag first: */
			{
				if (bParagraphOpen)		/* paragraph still open? */
				{
					/* additional linefeed? */
					if (bEnvCompressed[iEnvLevel])
						outln(xhtml_br);
					else				/* close paragraph */
						outln("</p>\n");
				}

				bParagraphOpen = FALSE;

				outln("</dd>");			/* close previous <dd> tag */
			}

			token[0][0] = EOS;
			sBig[0] = EOS;

			if (token[1][0] == '[')
			{
				add_description();
				replace_once(token[0], "[", BOLD_ON);
				replace_last(token[0], "]", BOLD_OFF);
				um_strcpy(sBig, token[0], ArraySize(sBig), "c_item[20]");
				replace_udo_quotes(sBig);

				if (!bDocAutorefItemsOff)
					auto_references(sBig, FALSE, "", 0, 0);

				c_internal_styles(sBig);
				strinsert(sBig, "<dt>");
				um_strcat(sBig, "</dt>\n<dd>\n", ArraySize(sBig), "c_item[21]");
			} else
			{
				strcpy(sBig, "<dt>&nbsp;</dt>\n<dd>\n");
			}

			if (!bEnvCompressed[iEnvLevel])
			{
				um_strcat(sBig, "<p>", ArraySize(sBig), "c_item[22]");
				bParagraphOpen = TRUE;
			}

			bEnv1stPara[iEnvLevel] = TRUE;
			break;

		case ENV_LIST:
			token[0][0] = EOS;
			sBig[0] = EOS;

			if (!bEnv1stItem[iEnvLevel])
			{
				voutlnf("%s</td></tr>\n", sHtmlPropfontEnd);
				bParagraphOpen = FALSE;
			}

			if (token[1][0] == '[')
			{
				add_description();

				switch (env_kind[iEnvLevel])
				{
				case LIST_NORMAL:
					delete_once(token[0], "[");
					delete_last(token[0], "]");
					break;

				case LIST_BOLD:
					replace_once(token[0], "[", BOLD_ON);
					replace_last(token[0], "]", BOLD_OFF);
					break;

				case LIST_ITALIC:
					replace_once(token[0], "[", ITALIC_ON);
					replace_last(token[0], "]", ITALIC_OFF);
					break;

				case LIST_TYPEWRITER:
					replace_once(token[0], "[", TWRITER_ON);
					replace_last(token[0], "]", TWRITER_OFF);
					break;
				}

				um_strcpy(sBig, token[0], ArraySize(sBig), "c_item[23]");
				replace_udo_quotes(sBig);

				if (!bDocAutorefItemsOff)
					auto_references(sBig, FALSE, "", 0, 0);

				c_internal_styles(sBig);
				strinsert(sBig, sHtmlPropfontStart);
#if 0
				if (html_doctype == HTML5)
				{
					strinsert(sBig, "<tr><td class=\"UDO_td_nowrap UDO_td_valign_top\">");
				} else
#endif
				{
					strinsert(sBig, "<tr><td nowrap=\"nowrap\" valign=\"top\">");
				}
				strcat(sBig, sHtmlPropfontEnd);

#if 0
				if (html_doctype == HTML5)
				{
					strcat(sBig, "</td>\n<td class=\"UDO_td_valign_top\">");
				} else
#endif
				{
					strcat(sBig, "</td>\n<td valign=\"top\">");
				}
				strcat(sBig, sHtmlPropfontStart);
			} else
			{
				sprintf(sBig, "<tr><td>&nbsp;</td>\n<td>%s", sHtmlPropfontStart);
			}

			/* bParagraphOpen = TRUE; */
			break;
		}

		if (insert_placeholder(sBig, sBig, sBig, sBig))
		{
			um_strcpy(token[0], sBig, MAX_TOKEN_LEN + 1, "c_item[24]");
		} else
		{
			token[0][0] = EOS;
		}
		break;

	case TOLDS:
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:
		case ENV_ENUM:
			strcpy(token[0], "<item>");
			break;

		case ENV_DESC:
			token[0][0] = EOS;

			if (token[1][0] == '[')
			{
				add_description();
				delete_once(token[0], "[");
				delete_last(token[0], "]");
				strinsert(token[0], "<tag>");
				um_strcat(token[0], "</tag>", MAX_TOKEN_LEN + 1, "c_item[26]");
			} else
			{
				strcpy(token[0], "<tag> </tag>");
			}
			break;

		case ENV_LIST:					/* Hier genau wie bei ASCII */
			strcpy(token[0], " ");

			if (token[1][0] == '[')
			{
				add_description();
				delete_once(token[0], "[");
				delete_last(token[0], "]");
			}

			ll = iEnvIndent[iEnvLevel] - 2;	/* Die 2 Leerzeichen Ausgleich oben hier beruecksichtigen! */
			tl = toklen(token[0]);

			while ((int) tl <= ll)
			{
				um_strcat(token[0], " ", MAX_TOKEN_LEN + 1, "c_item[29]");
				tl++;
			}

			strcpy_prev_indent(li);
			strinsert(token[0], li);
			break;
		}
		break;

	case TOHPH:
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:
		case ENV_ENUM:
			strcpy(token[0], "<item>");
			break;

		case ENV_DESC:
			strcpy(token[0], "<item>");

			if (token[1][0] == '[')
			{
				add_description();
				replace_once(token[0], "[", "<emph>");
				replace_last(token[0], "]", "<\\emph>");
			} else
			{
				strcpy(token[0], "<item>");
			}
			break;

		case ENV_LIST:					/* Hier genau wie bei ASCII */
			strcpy(token[0], " ");

			if (token[1][0] == '[')
			{
				add_description();
				delete_once(token[0], "[");
				delete_last(token[0], "]");
			}

			ll = iEnvIndent[iEnvLevel] - 2;	/* Die 2 Leerzeichen Ausgleich oben hier beruecksichtigen! */
			tl = toklen(token[0]);

			while ((int) tl <= ll)
			{
				um_strcat(token[0], " ", MAX_TOKEN_LEN + 1, "c_item[35]");
				tl++;
			}

			strcpy_prev_indent(li);
			strinsert(token[0], li);
			break;
		}
		break;

	case TOIPF:
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:
		case ENV_ENUM:
			strcpy(token[0], ":li.");
			break;

		case ENV_DESC:
			strcpy(token[0], ":dt.");

			if (token[1][0] == '[')
			{
				add_description();
				replace_once(token[0], "[", BOLD_ON);
				replace_last(token[0], "]", BOLD_OFF);
			}
			um_strcat(token[0], "\n:dd.", MAX_TOKEN_LEN + 1, "c_item[38]");
			break;

		case ENV_LIST:
			strcpy(token[0], ":dt.");

			if (token[1][0] == '[')
			{
				add_description();

				switch (env_kind[iEnvLevel])
				{
				case LIST_NORMAL:
					delete_once(token[0], "[");
					delete_last(token[0], "]");
					break;

				case LIST_BOLD:
					replace_once(token[0], "[", BOLD_ON);
					replace_last(token[0], "]", BOLD_OFF);
					break;

				case LIST_ITALIC:
					replace_once(token[0], "[", ITALIC_ON);
					replace_last(token[0], "]", ITALIC_OFF);
					break;

				case LIST_TYPEWRITER:
					replace_once(token[0], "[", TWRITER_ON);
					replace_last(token[0], "]", TWRITER_OFF);
					break;
				}
			}

			um_strcat(token[0], "\n:dd.", MAX_TOKEN_LEN + 1, "c_item[40]");
			break;
		}
		break;

	case TOKPS:
		switch (iEnvType[iEnvLevel])
		{
		case ENV_ITEM:
			strcpy(token[0], itemchar[iItemLevel]);
			break;

		case ENV_ENUM:
			enum_count[iEnvLevel]++;
			itoenum(iEnumLevel, &(enum_count[iEnvLevel]), s);
			sprintf(token[0], "%s\n%s%d.%s off%d writeBeforeLeft\n%s", KPSPC_S, KPSPO_S, enum_count[iEnvLevel], KPSPC_S,
					iEnvLevel, KPSPO_S);
			break;

		case ENV_DESC:
			token[0][0] = EOS;
			strcpy_prev_indent(li);

			if (token[1][0] == '[')		/* there is a description title! */
			{
				add_description();

				ri[0] = EOS;
				ll = iEnvIndent[iEnvLevel] - 2;
				tl = toklen(token[0]);

				sAdd[0] = EOS;

				if (((int) tl) < ll)
				{
					/* sAdd will be added later (see below) */
					memset(sAdd, ' ', (size_t) (ll - tl));
					sAdd[ll - tl] = EOS;
				}

				delete_once(token[0], "[");
				delete_last(token[0], "]");
				/* KPSPC_S           = ")" */
				/* KPSPO_S           = "(" */
				/* token[0]          = description title */
				/* "Bon"             = Bold style on */
				/* "Boff"            = Bold style off */
				/* "offDesc"         = ??? */
				/* "writeBeforeLeft" = ??? */
				/* "newline"         = newline :-) */

				sprintf(s, "%s udoshow Bon %s%s%s offDesc writeBeforeLeft Boff %s", KPSPC_S, KPSPO_S, token[0], KPSPC_S,
						KPSPO_S);
				um_strcpy(token[0], s, MAX_TOKEN_LEN + 1, "!item");
				um_strcat(token[0], sAdd, MAX_TOKEN_LEN + 1, "!item");
			}
			break;

		case ENV_LIST:
			token[0][0] = EOS;

			if (token[1][0] == '[')
			{
				add_description();
				delete_once(token[0], "[");
				delete_last(token[0], "]");
			}

			ri[0] = EOS;

			ll = iEnvIndent[iEnvLevel] - 2;
			tl = toklen(token[0]);

			sAdd[0] = EOS;

			if (((int) tl) < ll)
			{
				memset(sAdd, ' ', (size_t) (ll - tl));
				sAdd[ll - tl] = EOS;
				/* sAdd wird weiter unten hinzugefuegt */
			}

			strcpy_prev_indent(li);

			switch (env_kind[iEnvLevel])
			{
			case LIST_BOLD:
				sprintf(s, "%s udoshow Bon %s%s%s offList offCountS get writeBeforeLeft Boff %s", KPSPC_S, KPSPO_S,
						token[0], KPSPC_S, KPSPO_S);
				break;
			case LIST_ITALIC:
				sprintf(s, "%s udoshow Ion %s%s%s offList offCountS get writeBeforeLeft Ioff %s", KPSPC_S, KPSPO_S,
						token[0], KPSPC_S, KPSPO_S);
				break;
			case LIST_TYPEWRITER:
				sprintf(s, "%s udoshow Von %s%s%s offList offCountS get writeBeforeLeft Voff  %s", KPSPC_S, KPSPO_S,
						token[0], KPSPC_S, KPSPO_S);
				break;
			default:
				sprintf(s, "%s udoshow %s%s%s offList offCountS get writeBeforeLeft %s", KPSPC_S, KPSPO_S, token[0],
						KPSPC_S, KPSPO_S);
				break;
			}

			um_strcpy(token[0], s, MAX_TOKEN_LEN + 1, "!item");
			um_strcat(token[0], sAdd, MAX_TOKEN_LEN + 1, "!item");
			break;
		}

		if (use_justification)
		{
			space2indent(token[0]);
		}
		break;
	}

	bEnv1stItem[iEnvLevel] = FALSE;
}





/*******************************************************************************
*
*  c_end_list():
*     This function outputs the end of a list environment.
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_end_list(int listkind)
{
	switch (desttype)
	{
	case TOLDS:
	case TOHPH:
	case TONRO:
		c_end_description();
		return;

	case TOHTM:
	case TOHAH:
		if (html_no_xlist)
		{
			c_end_description();
			return;
		}
		break;
	}

	switch (listkind)
	{
	case LIST_BOLD:
		check_env_end(ENV_LIST, listkind);
		break;

	case LIST_ITALIC:
		check_env_end(ENV_LIST, listkind);
		break;

	case LIST_TYPEWRITER:
		check_env_end(ENV_LIST, listkind);
		break;

	default:
		check_env_end(ENV_LIST, listkind);
		break;
	}

	if (iListLevel == 0)
	{
		switch (listkind)
		{
		case LIST_BOLD:
			error_end_without_begin(CMD_END_BLIST, CMD_BEGIN_BLIST);
			break;

		case LIST_ITALIC:
			error_end_without_begin(CMD_END_ILIST, CMD_BEGIN_ILIST);
			break;

		case LIST_TYPEWRITER:
			error_end_without_begin(CMD_END_TLIST, CMD_BEGIN_TLIST);
			break;

		default:
			error_end_without_begin(CMD_END_XLIST, CMD_BEGIN_XLIST);
			break;
		}
	}

	if (iEnvLevel > 0)
	{
		iEnvIndent[iEnvLevel] = 0;
		iEnvLevel--;
	}

	if (iListLevel > 0)
	{
		iListLevel--;
	}

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		switch (listkind)
		{
		case LIST_BOLD:
			outln("\\end{blist}");
			break;

		case LIST_ITALIC:
			outln("\\end{ilist}");
			break;

		case LIST_TYPEWRITER:
			outln("\\end{tlist}");
			break;

		default:
			outln("\\end{xlist}");
			break;
		}
		outln("");
		break;

	case TOLYX:
		if (iEnvLevel > 0)
			outln("\\end_deeper");
		break;

	case TOINF:
		outln("@end table");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		voutlnf("%s", sHtmlPropfontEnd);

		if (bParagraphOpen)
			if (!bEnvCompressed[iEnvLevel])
				out("</p>");
		outln("</td></tr>\n</table>\n");
		bParagraphOpen = FALSE;
		break;

	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		if (iEnvLevel == 0)
			outln("\\pard\\");
		break;

	case TOIPF:
		outln(":edl.");
		break;

	case TOKPS:
/*    outln("offList subOffFromLeft");
*/
		outln("offList offCountS get subOffFromLeft");
		outln("/offCount offCount 1 sub def");
		outln("/offCountS offCount 4 add def");
		break;
	}

	end_env_output_line(iEnvLevel + 1);
}





/*******************************************************************************
*
*  c_end_xlist():
*     wrapper for c_end_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_xlist(void)
{
	c_end_list(LIST_NORMAL);
}





/*******************************************************************************
*
*  c_end_blist():
*     wrapper for c_end_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_blist(void)
{
	c_end_list(LIST_BOLD);
}





/*******************************************************************************
*
*  c_end_ilist():
*     wrapper for c_end_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_ilist(void)
{
	c_end_list(LIST_ITALIC);
}





/*******************************************************************************
*
*  c_end_tlist():
*     wrapper for c_end_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_tlist(void)
{
	c_end_list(LIST_TYPEWRITER);
}





/*******************************************************************************
*
*  c_end_description():
*     output a description environment's end data
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_description(void)
{
	check_env_end(ENV_DESC, 0);

	if (iEnvLevel > 0)
	{
		iEnvIndent[iEnvLevel] = 0;
		iEnvLevel--;
	}

	if (iDescLevel > 0)
	{
		iDescLevel--;
	}

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\end{description}");
		outln("");
		break;

	case TOLYX:
		if (iEnvLevel > 0)
			outln("\\end_deeper");
		break;

	case TOINF:
		outln("@end table");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (bParagraphOpen)
		{
			/* check previous environment */
			if (bEnvCompressed[iEnvLevel + 1])
				outln(xhtml_br);
			else
				outln("</p>");
			outln("");
		}

		bParagraphOpen = FALSE;

		if (!bEnv1stItem[iEnvLevel + 1])
			outln("</dd>");
		outln("</dl>");
		break;

	case TOHPH:
		outln("<\\list>");
		break;

	case TOLDS:
		outln("</descrip>");
		break;

	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		if (iEnvLevel == 0)
			outln("\\pard\\");
		break;

	case TOIPF:
		outln(":edl.");
		break;

	case TOKPS:
		outln("description");
		outln("offDesc subOffFromLeft");
		break;
	}

	end_env_output_line(iEnvLevel + 1);
}





/*******************************************************************************
*
*  c_end_enumerate():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_enumerate(void)
{
	check_env_end(ENV_ENUM, 0);

	if (iEnvLevel > 0)
	{
		iEnvIndent[iEnvLevel] = 0;
		iEnvLevel--;
	}

	if (iEnumLevel > 0)
	{
		iEnumLevel--;
	}

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\end{enumerate}");
		outln("");
		break;

	case TOLYX:
		if (iEnvLevel > 0)
			outln("\\end_deeper");
		break;

	case TOINF:
		outln("@end enumerate");
		outln("");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (!bEnvCompressed[iEnvLevel + 1])
			out("</p>");
		outln("</li>");
		outln("</ol>\n");
		bParagraphOpen = FALSE;			/* no additional </p> in ENV_DESC */
		break;

	case TOHPH:
		outln("<\\list>");
		break;

	case TOLDS:
		outln("</enum>");
		break;

	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		if (iEnvLevel == 0)
			outln("\\pard\\");
		break;

	case TOIPF:
		outln(":eol.");
		break;

	case TOKPS:
		voutlnf("off%d subOffFromLeft", iEnvLevel + 1);
		outln("newline");
		break;
	}

	end_env_output_line(iEnvLevel + 1);
}





/*******************************************************************************
*
*  c_end_itemize():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_itemize(void)
{
	check_env_end(ENV_ITEM, 0);

	if (iEnvLevel > 0)
	{
		iEnvIndent[iEnvLevel] = 0;
		iEnvLevel--;
	}

	if (iItemLevel > 0)
	{
		iItemLevel--;
	}

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\end{itemize}");
		outln("");
		break;

	case TOLYX:
		if (iEnvLevel > 0)
			outln("\\end_deeper");
		break;

	case TOINF:
		outln("@end itemize");
		outln("");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (!bEnvCompressed[iEnvLevel + 1])
			out("</p>");
		outln("</li>");
		outln("</ul>\n");
		bParagraphOpen = FALSE;			/* no additional </p> in ENV_DESC */
		break;

	case TOHPH:
		outln("<\\list>");
		break;

	case TOLDS:
		outln("</itemize>");
		break;

	case TORTF:
	case TOAQV:
	case TOWIN:
	case TOWH4:
		if (iEnvLevel == 0)
			outln("\\pard\\");
		break;

	case TOIPF:
		outln(":eul.");
		break;

	case TOKPS:
		voutlnf("off%d subOffFromLeft", iEnvLevel + 1);
		outln("newline");
		break;
	}

	end_env_output_line(iEnvLevel + 1);
}





/*******************************************************************************
*
*  output_tex_environments():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_tex_environments(void)
{
	outln("");

	outln("\\def\\hidelink#1{}");
	outln("");

	outln("\\begin{document}");
	outln("");

	outln("\\newenvironment{xlist}[1]{\\begin{list}{}{\\settowidth{\\labelwidth}{#1}");
	outln("  \\setlength{\\leftmargin}{\\labelwidth} \\addtolength{\\leftmargin}{\\labelsep}");
	outln("  \\setlength{\\parsep}{0.5ex plus0.2ex minus0.2ex}");
	outln("  \\setlength{\\itemsep}{0.3ex}");
	outln("  \\renewcommand{\\makelabel}[1]{##1\\hfill}}}{\\end{list}}");
	outln("");

	outln("\\newenvironment{blist}[1]{\\begin{list}{}{\\settowidth{\\labelwidth}{{\\bf #1}}");
	outln("  \\setlength{\\leftmargin}{\\labelwidth} \\addtolength{\\leftmargin}{\\labelsep}");
	outln("  \\setlength{\\parsep}{0.5ex plus0.2ex minus0.2ex}");
	outln("  \\setlength{\\itemsep}{0.3ex}");
	outln("  \\renewcommand{\\makelabel}[1]{{\\bf ##1}\\hfill}}}{\\end{list}}");
	outln("");

	outln("\\newenvironment{ilist}[1]{\\begin{list}{}{\\settowidth{\\labelwidth}{{\\it #1}}");
	outln("  \\setlength{\\leftmargin}{\\labelwidth} \\addtolength{\\leftmargin}{\\labelsep}");
	outln("  \\setlength{\\parsep}{0.5ex plus0.2ex minus0.2ex}");
	outln("  \\setlength{\\itemsep}{0.3ex}");
	outln("  \\renewcommand{\\makelabel}[1]{{\\it ##1}\\hfill}}}{\\end{list}}");
	outln("");

	outln("\\newenvironment{tlist}[1]{\\begin{list}{}{\\settowidth{\\labelwidth}{{\\tt #1}}");
	outln("  \\setlength{\\leftmargin}{\\labelwidth} \\addtolength{\\leftmargin}{\\labelsep}");
	outln("  \\setlength{\\parsep}{0.5ex plus0.2ex minus0.2ex}");
	outln("  \\setlength{\\itemsep}{0.3ex}");
	outln("  \\renewcommand{\\makelabel}[1]{{\\tt ##1}\\hfill}}}{\\end{list}}");
	outln("");

	outln("");

	outln("\\makeatletter");
	outln("\\@ifundefined{LaTeXe}%");
	outln("  {\\def\\LaTeXe{{\\protect\\LaTeX{}2${}_{\\textstyle\\varepsilon}$}}");
	outln("   \\def\\textbf#1{{\\bf #1}}");
	outln("   \\def\\textit#1{{\\it #1}}");
	outln("   \\def\\texttt#1{{\\tt #1}}");
	outln("  }");
	outln("  {\\def\\underlined#1{\\relax}");
	outln("  }");
	outln("\\makeatother");
	outln("");

	outln("");
}





/*******************************************************************************
*
*  output_rtf_colortbl():
*     output the RTF color table
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_rtf_colortbl(void)
{
	outln("{\\colortbl;");				/* \cf0:  default */
	outln("\\red0\\green0\\blue0;");	/* \cf1:  black */
	outln("\\red192\\green192\\blue192;");	/* \cf2:  silver */
	outln("\\red128\\green128\\blue128;");	/* \cf3:  gray */
	outln("\\red255\\green255\\blue255;");	/* \cf4:  white */
	outln("\\red128\\green0\\blue0;");	/* \cf5:  maroon */
	outln("\\red255\\green0\\blue0;");	/* \cf6:  red */
	outln("\\red128\\green0\\blue128;");	/* \cf7:  purple */
	outln("\\red255\\green0\\blue255;");	/* \cf8:  fuchsia */
	outln("\\red0\\green128\\blue0;");	/* \cf9:  green */
	outln("\\red0\\green255\\blue0;");	/* \cf10: lime */
	outln("\\red128\\green128\\blue0;");	/* \cf11: olive */
	outln("\\red255\\green255\\blue0;");	/* \cf12: yellow */
	outln("\\red0\\green0\\blue128;");	/* \cf13: navy */
	outln("\\red0\\green0\\blue255;");	/* \cf14: blue */
	outln("\\red0\\green128\\blue128;");	/* \cf15: teal */
	outln("\\red0\\green255\\blue255;");	/* \cf16: aqua */

	if (sDocColour[0] != EOS)
		outln(sDocColour);

	outln("}");
}





/*******************************************************************************
*
*  c_begin_document():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_document(void)
{
	char s[512];
	int i;

	if (bCalledBeginDocument)
	{
		error_called_twice(CMD_BEGIN_DOCUMENT);
		return;
	}

	bInsideDocument = TRUE;

	switch (desttype)
	{
	case TOPDL:
		outln("\\pdfinfo {");
		if (titdat.title != NULL)
			voutlnf("  /Title (%s)", titdat.title);
		if (titdat.author != NULL)
			voutlnf("  /Author (%s)", titdat.author);

		voutlnf("  /Creator (UDO %s)", UDO_VERSION_STRING_OS);
		voutlnf("  /CreationDate (D:%d%02d%02d%02d%02d%02d)", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin,
				iDateSec);
		voutlnf("  /ModDate (D:%d%02d%02d%02d%02d%02d)", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin,
				iDateSec);

		if (titdat.description != NULL)
			voutlnf("  /Subject (%s)", titdat.description);

		if (titdat.keywords != NULL)
			voutlnf("  /Keywords (%s)", titdat.keywords);

		outln("}");

		outln("");
		outln("% \\realbackslash is an actual character `\\' with catcode other, and");
		outln("% \\doublebackslash is two of them (for the pdf outlines).");
		outln("{\\catcode`\\@=0 \\catcode`\\\\=12 @gdef@realbackslash{\\} @gdef@doublebackslash{\\\\}}");
		outln("");

		output_tex_environments();
		break;

	case TOTEX:
		output_tex_environments();
		break;

	case TOLYX:
		break;

	case TOINF:
		outln("\\input texinfo @c-*-texinfo-*-");
		voutlnf("@documentlanguage %s", get_lang()->html_lang);
		outln("@c %**start of header");
		voutlnf("@setfilename %s.info", outfile.name);
		strcpy(s, titleprogram);
		auto_quote_chars(s, TRUE);

		if (s[0] == EOS)
			strcpy(s, get_lang()->unknown);
		voutlnf("@settitle %s", s);
		outln("@c %**end of header");
		break;

	case TOMAN:
		man_headline();
		break;

	case TONRO:
		sprintf(s, ".TH ");

		if (titdat.program != NULL)
			strcat(s, titdat.program);
		else
			strcat(s, get_lang()->unknown);

		if (sDocNroffType[0] != EOS)
		{
			strcat(s, " ");
			strcat(s, sDocNroffType);
		} else
		{
			strcat(s, " 1");
		}

		strcat(s, " \"");

		if (titdat.date != NULL)
			strcat(s, titdat.date);
		else
			strcat(s, get_lang()->today);

		strcat(s, "\"");

		if (titdat.author != NULL)
		{
			strcat(s, " \"");
			strcat(s, titdat.author);
			strcat(s, "\"");
		}
		outln(s);
		break;

	case TOSTG:
	case TOAMG:
		if (titdat.stg_database != NULL)
		{
			if (*titdat.stg_database != EOS)
				voutlnf("@database \"%s\"", titdat.stg_database);
		} else if (titleprogram[0] != EOS)
		{
			voutlnf("@database \"%s\"", titleprogram);
		} else
		{
			voutlnf("@database \"%s\"", get_lang()->unknown);
		}

		if (titdat.author != NULL)
		{
			voutlnf("@author \"%s\"", titdat.author);
		}

		if (titdat.version != NULL)
		{
			if (titdat.date != NULL)
				voutlnf("@$VER: %s (%s)", titdat.version, titdat.date);
			else
				voutlnf("@$VER: %s", titdat.version);
		} else
		{
			if (titdat.date != NULL)
				voutlnf("@$VER: %s", titdat.date);
		}

		voutlnf("@width %d", (int) zDocParwidth);

		if (uses_maketitle)
		{
			voutlnf("@default \"%s\"", get_lang()->title);
		} else
		{
			if (uses_tableofcontents)
				outln("@default \"Main\"");
		}
		outln("");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (titdat.htmltitle != NULL && titdat.htmltitle[0] != EOS)
		{
			output_html_header(titdat.htmltitle);
		} else
		{
			if (titleprogram[0] != EOS)
			{
				output_html_header(titleprogram);
			} else
			{
				output_html_header(get_lang()->unknown);
			}
		}
		html_headline();
		break;

	case TORTF:
		/* RTF-HEADER */
		if (sDocPropfont[0] == EOS)
			strcpy(sDocPropfont, "Times New Roman");

		if (sDocMonofont[0] == EOS)
			strcpy(sDocMonofont, "Courier New");

		outln("{\\rtf1\\ansi");
		outln("{\\fonttbl");
		voutlnf("{\\f0\\froman\\fcharset0 %s;}", sDocPropfont);
		voutlnf("{\\f1\\fmodern\\fcharset0 %s;}", sDocMonofont);
		outln("{\\f2\\fmodern\\fcharset2 MS LineDraw;}");
		outln("{\\f3\\ftech\\fcharset2 Symbol;}");
		outln("}");
		outln("{\\stylesheet");

		if (sDocPropfontSize[0] != EOS)
			iDocPropfontSize = atoi(sDocPropfontSize) * 2;
		else
			iDocPropfontSize = 11 * 2;	/* Times New Roman 11pt */

		if (sDocMonofontSize[0] != EOS)
			iDocMonofontSize = atoi(sDocMonofontSize) * 2;
		else
			iDocMonofontSize = 10 * 2;	/* Courier New 10pt */

		/* Size of nodes */
		for (i = 0; i < TOC_MAXDEPTH + 1; i++)
		{
			if (laydat.nodesize[i] != 0)
				laydat.nodesize[i] *= 2;
			else
				laydat.nodesize[i] = iDocPropfontSize + rtf_structure_height[i];
		}

		voutlnf("{%s\\fs%d\\snext0 Normal;}", rtf_norm, iDocPropfontSize);
		voutlnf("{%s\\fs%d\\snext1 Verbatim;}", rtf_verb, iDocMonofontSize);

		voutlnf("{%s\\fs%d\\snext2 Chapter;}", rtf_chapt, laydat.nodesize[0]);
		voutlnf("{%s\\fs%d\\snext3 Node1;}", rtf_node1, laydat.nodesize[TOC_NODE1 + 1]);
		voutlnf("{%s\\fs%d\\snext4 Node2;}", rtf_node2, laydat.nodesize[TOC_NODE2 + 1]);
		voutlnf("{%s\\fs%d\\snext5 Node3;}", rtf_node3, laydat.nodesize[TOC_NODE3 + 1]);
		voutlnf("{%s\\fs%d\\snext6 Node4;}", rtf_node4, laydat.nodesize[TOC_NODE4 + 1]);
		voutlnf("{%s\\fs%d\\snext7 Node5;}", rtf_node5, laydat.nodesize[TOC_NODE5 + 1]);
		voutlnf("{%s\\fs%d\\snext8 Node6;}", rtf_node6, laydat.nodesize[TOC_NODE6 + 1]);
		voutlnf("{%s\\fs%d\\snext9 Node7;}", rtf_node7, laydat.nodesize[TOC_NODE7 + 1]);
		voutlnf("{%s\\fs%d\\snext10 Node8;}", rtf_node8, laydat.nodesize[TOC_NODE8 + 1]);
		voutlnf("{%s\\fs%d\\snext11 Node9;}", rtf_node9, laydat.nodesize[TOC_NODE9 + 1]);

		voutlnf("{%s\\fs%d\\snext12 Chapter*;}", rtf_inv_chapt, laydat.nodesize[0]);
		voutlnf("{%s\\fs%d\\snext13 Node1*;}", rtf_inv_node1, laydat.nodesize[TOC_NODE1 + 1]);
		voutlnf("{%s\\fs%d\\snext14 Node2*;}", rtf_inv_node2, laydat.nodesize[TOC_NODE2 + 1]);
		voutlnf("{%s\\fs%d\\snext15 Node3*;}", rtf_inv_node3, laydat.nodesize[TOC_NODE3 + 1]);
		voutlnf("{%s\\fs%d\\snext16 Node4*;}", rtf_inv_node4, laydat.nodesize[TOC_NODE4 + 1]);
		voutlnf("{%s\\fs%d\\snext17 Node5*;}", rtf_inv_node5, laydat.nodesize[TOC_NODE5 + 1]);
		voutlnf("{%s\\fs%d\\snext18 Node6*;}", rtf_inv_node6, laydat.nodesize[TOC_NODE6 + 1]);
		voutlnf("{%s\\fs%d\\snext19 Node7*;}", rtf_inv_node7, laydat.nodesize[TOC_NODE7 + 1]);
		voutlnf("{%s\\fs%d\\snext20 Node8*;}", rtf_inv_node8, laydat.nodesize[TOC_NODE8 + 1]);
		voutlnf("{%s\\fs%d\\snext21 Node9*;}", rtf_inv_node9, laydat.nodesize[TOC_NODE9 + 1]);

		voutlnf("{%s\\fs%d\\snext23 LineDraw;}", rtf_linedraw, iDocMonofontSize);
		voutlnf("{\\*\\cs24\\snext24 Footnote Characters;}");
		voutlnf("{\\*\\cs25\\snext25{\\*\\updnprop5801}\\up10 Footnote anchor;}");
		outln("}");

		output_rtf_colortbl();

		outln("\\paperw11904\\paperh16836");
		outln("\\margl1134\\margr1134\\margt1984\\margb1984");

		outln("\\pgnstart1\\ftnbj\\ftnrestart\\facingp\\margmirror\\makeback\\widowctrl");
		outln("\\sectd\\pgndec\\headery1134\\footery1134\\cols1\\colsx567\\pgndec");

		outln("{\\*\\revtbl ");
		outln("{Unknown;}");
		voutlnf("{UDO %s;}", UDO_VERSION_STRING_OS);
		outln("}");

		voutlnf("\\f0\\fs%d", iDocPropfontSize);

		if (!check_output_raw_header())
		{
			if (titleprogram[0] != EOS)
			{
				if (!no_headlines)
				{
					voutlnf("{\\headerl\\pard\\plain\\pard\\tqr\\tx9636\\f0\\fs%d {\\i %s \\chpgn\\tab %s}\\par}",
							iDocPropfontSize, get_lang()->page, titleprogram);
					voutlnf("{\\headerr\\pard\\plain\\pard\\tqr\\tx9636\\f0\\fs%d {\\i %s\\tab %s \\chpgn}\\par}",
							iDocPropfontSize, titleprogram, get_lang()->page);
				}
			}
		}

		outln("{\\info");

		/* ---- \author ---- */
		s[0] = EOS;
		if (titdat.author != NULL)
		{
			strcpy(s, titdat.author);
		} else
		{
			if (config.bRegistered)
			{
				strcpy(s, config.strUserName);
				auto_quote_chars(s, TRUE);
			}
		}
		if (s[0] != EOS)
			voutlnf("{\\author %s}", s);

		/* ---- \title ---- */
		if (titleprogram[0] != EOS)
			voutlnf("{\\title %s}", titleprogram);

		/* ---- \description ---- */
		if (titdat.description != NULL)
		{
			if (titdat.description[0] != EOS)
				voutlnf("{\\subject %s}", titdat.description);
		}

		/* ---- \keywords ---- */
		if (titdat.keywords != NULL)
		{
			if (titdat.keywords[0] != EOS)
				voutlnf("{\\keywords %s}", titdat.keywords);
		}

		/* ---- \company ---- */
		if (titdat.company != NULL)
		{
			if (titdat.company[0] != EOS)
				voutlnf("{\\*\\company %s}", titdat.company);
		}

		/* ---- \category ---- */
		if (titdat.category != NULL)
		{
			if (titdat.category[0] != EOS)
				voutlnf("{\\*\\category %s}", titdat.category);
		}

		/* ---- \translator ---- */
		if (titdat.translator != NULL)
		{
			if (titdat.translator[0] != EOS)
				voutlnf("{\\*\\translator %s}", titdat.translator);
		}

		/* ---- \distributor ---- */
		if (titdat.distributor != NULL)
		{
			if (titdat.distributor[0] != EOS)
				voutlnf("{\\*\\distributor %s}", titdat.distributor);
		}

		/* ---- About UDO ---- */
		voutlnf("{\\doccomm UDO %s, %s %s}", UDO_VERSION_STRING_OS, compile_date, compile_time);

		/* ---- Erstellungsdatum & Sonstiges ---- */
		voutlnf("{\\creatim\\yr%d\\mo%d\\dy%d\\hr%d\\min%d}", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin);
		outln("{\\version1}{\\nofpages0}{\\nofwords0}{\\nofchars0}{\\edmins0}");
		outln("}");

		outln(rtf_pardplain);

		if (iEncodingTarget == CODE_UTF8)	/* UTF-8 output? */
			outln("\\uc0");				/* tell RTF that there is no (!) ANSI char behind Unicode char! */

		voutlnf("%s\\fs%d", rtf_norm, iDocPropfontSize);
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		if (sDocPropfont[0] == EOS)
		{
			/* MS Sans Serif is Bitmap font and looks ugly in larger sizes */
			strcpy(sDocPropfont, /* desttype == TOWH4 ? "MS Sans Serif" : */ "Times New Roman");
		}

		if (sDocMonofont[0] == EOS)
		{
			strcpy(sDocMonofont, "Courier New");
		}

		outln("{\\rtf1\\ansi \\deff0");
		outln("{\\fonttbl");
		voutlnf("{\\f0\\froman %s;}", sDocPropfont);
		voutlnf("{\\f1\\fmodern %s;}", sDocMonofont);
		outln("{\\f2\\fmodern\\fcharset2 MS LineDraw;}");
		outln("{\\f3\\ftech\\fcharset2 Symbol;}");
		outln("}");

		output_rtf_colortbl();

		if (sDocPropfontSize[0] != EOS)
			iDocPropfontSize = atoi(sDocPropfontSize) * 2;
		else if (desttype == TOWH4)
			iDocPropfontSize = 8 * 2;	/* MS Sans Serif 8pt */
		else
			iDocPropfontSize = 11 * 2;	/* Times New Roman 11pt */
		voutlnf("\\f0\\fs%d", iDocPropfontSize);

		if (sDocMonofontSize[0] != EOS)
			iDocMonofontSize = atoi(sDocMonofontSize) * 2;
		else
			iDocMonofontSize = 10 * 2;	/* Courier New 10pt */

		if (sDocTextColor.color != BC_NONE)
			outln(udocolor[sDocTextColor.color].wintext);
		break;

	case TOLDS:
		outln("<!doctype linuxdoc system>");
		outln("");
		if (use_style_book)
		{
			outln("<book>");
			outln("");
		} else
		{
			outln("<article>");
			outln("");
		}

		if (titleprogram[0] != EOS)
			voutlnf("<title>%s", titleprogram);

		if (titdat.author != NULL || address_counter > 0)
		{
			out("<author>");
			if (titdat.author != NULL)
				out(titdat.author);
			if (address_counter > 0)
			{
				for (i = 1; i <= address_counter; i++)
				{
					if (titdat.address[i] != NULL)
					{
						out(", ");
						out(titdat.address[i]);
					}
				}
			}
			outln("");
		}

		if (titdat.date != NULL)
			voutlnf("<date>%s", titdat.date);
		break;

	case TOHPH:
		outln("<helpvolume>");
		outln("<metainfo>");

		if (titleprogram[0] != EOS)
		{
			voutlnf("<title>%s", titleprogram);
		}

		outln("<\\metainfo>");
		break;

	case TOIPF:
		outln(":userdoc.");
		outln(":docprof toc=1234.");
		if (titleprogram[0] != EOS)
			voutlnf(":title.%s", titleprogram);
		else
			voutlnf(":title.%s", get_lang()->unknown);
		break;

	case TOKPS:
		/* Size of nodes */
		for (i = 0; i < TOC_MAXDEPTH + 1; i++)
		{
			if (laydat.nodesize[i] == 0)
				laydat.nodesize[i] = laydat.propfontsize + kps_structure_height[i];
		}

		outln(UDO2PS);					/* in udo2ps.h definiert (c) by Christian Krueger und Norbert Hanz */
		outln(UDO2PDF);					/* in udo2pdf.h definiert (c) by Norbert Hanz */
#if 0									/* now uses default from abo.c */
		outln(destlang == TOGER ? UDO2PDF_aboutudo_ger : UDO2PDF_aboutudo_eng);
#endif

		if (laydat.paper != NULL)
		{
			for (i = 0; i < MAXPAPERSIZE; i++)
			{
				if (strcmp(laydat.paper, paperSize[i].paper) == 0)
				{
					voutlnf("<< /PageSize [ %d %d ] >> setpagedevice", paperSize[i].width_pt, paperSize[i].height_pt);
					voutlnf("/cctopmargin   %d def", paperSize[i].margintop_pt);
					voutlnf("/ccleftmargin  %d def", paperSize[i].marginleft_pt);
					voutlnf("/ccrightmargin %d def", paperSize[i].marginright_pt);
					voutlnf("/cclowermargin %d def", paperSize[i].marginbottom_pt);
					outln("/topmargin      cctopmargin 20 sub def");
					outln("/lowermargin    cclowermargin def");
					outln("/rightmargin    ccrightmargin def");
					outln("/leftmargin     ccleftmargin def");
				}
			}
		}

/*    outln("/topmargin    792 def");
      outln("/lowermargin   72 def");
      outln("/rightmargin  540 def");
      outln("/leftmargin    90 def");
*/
		outln("/linespacing  1.5 def");
		outln("0 0 0 setBaseColor");
		outln("setup");

		if (strstr(laydat.propfontname, "Helvetica") != NULL ||
			strstr(laydat.propfontname, "Arial") != NULL || strstr(laydat.propfontname, "sans-serif") != NULL)
			voutlnf("/basefont %d def", 1);

		voutlnf("/fontsize %d def", laydat.propfontsize);
		outln("basefont setBaseFont");

		if (titdat.title != NULL && titdat.program != NULL)
			voutlnf("/Titeltext (%s %s) def", titdat.title, titdat.program);
		else if (titdat.title != NULL)
			voutlnf("/Titeltext (%s) def", titdat.title);
		else if (titdat.program != NULL)
			voutlnf("/Titeltext (%s) def", titdat.program);
		else
			voutlnf("/Titeltext () def");

		if (titdat.author != NULL)
			voutlnf("/FootAuthor (\\251 %s) def", titdat.author);
		else
			outln("/FootAuthor () def");

		/* Document info */
		if (titdat.title != NULL && titdat.program != NULL)
			voutlnf("[ /Title (%s %s)", titdat.title, titdat.program);
		else if (titdat.title != NULL)
			voutlnf("[ /Title (%s)", titdat.title);
		else if (titdat.program != NULL)
			voutlnf("[ /Title (%s)", titdat.program);
		else
			outln("[ /Title ()");

		voutlnf("  /Author (%s)", titdat.author ? titdat.author : "");
		voutlnf("  /Subject (%s)", titdat.description ? titdat.description : "");
		voutlnf("  /Keywords (%s)", titdat.keywords ? titdat.keywords : "");

		voutlnf("  /Creator (UDO %s)", UDO_VERSION_STRING_OS);
		voutlnf("  /CreationDate (D:%d%02d%02d%02d%02d%02d)", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin,
				iDateSec);
		voutlnf("  /ModDate (D:%d%02d%02d%02d%02d%02d)", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin,
				iDateSec);
		outln("/DOCINFO pdfmark");
		outln("");

		/* How to open a PDF-document */
		voutlnf("%s %s %s %s %s %s HowToOpen\n",
				laydat.pagemode,
				laydat.openpage, laydat.hidetoolbar, laydat.hidemenubar, laydat.viewerpreferences, laydat.fitwindow);
		bookmarks_ps();
		break;
	}

	bCalledBeginDocument = TRUE;
}





/*******************************************************************************
*
*  c_end_document():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_document(void)
{
	if (bCalledEndDocument)
	{
		error_called_twice(CMD_END_DOCUMENT);
		return;
	}

	if (bCalledBeginDocument && !bInsideDocument)
	{
		error_end_without_begin(CMD_END_DOCUMENT, CMD_BEGIN_DOCUMENT);
	}

	check_styleflags();
	check_endnode();

	if (use_about_udo)
	{
		output_about_udo();
		check_endnode();
	}

	switch (desttype)
	{
	case TOHTM:
	case TOHAH:
		if (!no_index && use_udo_index)
		{
			save_html_index();
			check_endnode();
		}
		html_bottomline();
		break;
	}

	if (bInsideAppendix)
	{
		if (!bCalledEndAppendix)
			error_missing_end(CMD_END_APPENDIX);
		bInsideAppendix = FALSE;

		switch (desttype)
		{
		case TOTEX:
		case TOPDL:
			outln("\\end{appendix}");
			outln("");
			break;

		case TOLYX:
			break;

		default:
			outln("");
			break;
		}
	}

	print_index();

	bInsideDocument = FALSE;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\end{document}");
		outln("");
		break;

	case TOLYX:
		break;

	case TOINF:
		if (called_tableofcontents)
		{
			outln("@iftex");
			outln("@shortcontents");
			outln("@contents");
			outln("@end iftex");
		}
		outln("@bye");
		break;

	case TOMAN:
		if (iManPageLength > 0)
		{
			if (iManPageLines < iManPageLength)
			{
				man_bottomline();
			}
		}
		break;

	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		outln("}");
		outln("");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		voutlnf("%s", sHtmlPropfontEnd);
		check_output_raw_footer(TRUE);
		outln("\n</body>");
		outln("</html>");
		break;

	case TOLDS:
		if (use_style_book)
		{
			outln("</book>");
			outln("");
		} else
		{
			outln("</article>");
			outln("");
		}
		break;

	case TOHPH:
		outln("<\\helpvolume>");
		break;

	case TOSRC:
	case TOSRP:
		if (use_about_udo)
		{
			char n[128];

			memset(n, '#', 62);
			n[62] = EOS;
			outln("");
			voutlnf("%s  %s", sSrcRemOn, n);
			voutlnf("    # @(#) %s%s - made with UDO %s", outfile.name, outfile.suff, UDO_VERSION_STRING_OS);
			voutlnf("    %s %s", n, sSrcRemOff);
		}
		break;

	case TODRC:
		outln("%%");
		break;

	case TOIPF:
		outln(":euserdoc.");
		break;

	case TOKPS:
		outln("newpage");
#if 0									/* now uses default from abo.c */
		if (use_about_udo)
		{
			outln("/NodeName (About UDO) def");
			outln("/acty acty 50 sub def");
			outln("actx acty moveto");
			voutlnf("(%s) (%s) (%s) %s", UDO_VERSION_STRING, UDO_OS, UDO_URL, destlang == TOGER ? "aboutUDO_ger" : "aboutUDO_eng");
			outln("newpage");
		}
#endif
		break;
	}

	bCalledEndDocument = TRUE;
}





/*******************************************************************************
*
*  c_begin_appendix():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_appendix(void)
{
	if (bCalledBeginAppendix)
	{
		error_called_twice(CMD_BEGIN_APPENDIX);
		return;
	}

	bInsideAppendix = TRUE;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\begin{appendix}");
		break;

	case TOLYX:
		outln("\\start_of_appendix");
		break;

	default:
		outln("");
		break;
	}

	bCalledBeginAppendix = TRUE;
	toc_pass2_begin_appendix();
}





/*******************************************************************************
*
*  c_end_appendix():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_appendix(void)
{
	if (bCalledEndAppendix)
	{
		error_called_twice(CMD_END_APPENDIX);
		return;
	}

	if (!bInsideAppendix)
	{
		error_end_without_begin(CMD_END_APPENDIX, CMD_BEGIN_APPENDIX);
	}

	/* Sonst nichts ausgeben, der Rest wird in c_end_document erledigt! */

	bCalledEndAppendix = TRUE;
}





/*******************************************************************************
*
*  init_module_env():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_env(void)
{
	int i;

	for (i = 0; i <= MAXENVLEVEL; i++)
	{
		bEnvCompressed[i] = FALSE;
		bEnv1stItem[i] = TRUE;
		bEnv1stPara[i] = TRUE;
		iEnvType[i] = 0;
		env_kind[i] = 0;
	}

	iEnvLevel = 0;
	iItemLevel = 0;
	iEnumLevel = 0;
	iDescLevel = 0;
	quot_level = 0;
	iListLevel = 0;
	cent_level = 0;

	flushright_level = 0;
	flushleft_level = 0;

	bCalledBeginDocument = FALSE;
	bCalledEndDocument = FALSE;
	bCalledBeginAppendix = FALSE;
	bCalledEndAppendix = FALSE;
}





/*******************************************************************************
*
*  init_env_itemchar():
*     initialize 'bullet' characters for itemize environment
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_env_itemchar(void)
{
	switch (desttype)
	{
	case TOSTG:
	case TOAMG:
	case TOASC:
	case TODRC:
	case TOMAN:
	case TONRO:
	case TOPCH:
	case TOTVH:
		strcpy(itemchar[1], ".");

		if (!no_umlaute)
		{
			if (desttype == TOSTG)
			{
				strcpy(itemchar[1], "\371");
			} else
			{
#ifdef __TOS__
				strcpy(itemchar[1], "\371");
#endif
#ifdef __NEXTSTEP__
				strcpy(itemchar[1], "\367");
#endif
#ifdef __HPUX_ROMAN8__
				strcpy(itemchar[1], "\374");
#endif
#if defined(__MACOS__) || defined(__MACOSX__) || defined(__BEOS__)
				strcpy(itemchar[1], "\245");
#endif
			}
		}
		strcpy(itemchar[2], "-");
		strcpy(itemchar[3], "*");
		strcpy(itemchar[4], ".");
		strcpy(itemchar[5], itemchar[1]);
		strcpy(itemchar[6], itemchar[2]);
		break;

	case TORTF:
		strcpy(itemchar[1], "\\bullet");
		strcpy(itemchar[2], "-");
		strcpy(itemchar[3], "*");
		strcpy(itemchar[4], ".");
		strcpy(itemchar[5], itemchar[1]);
		strcpy(itemchar[6], itemchar[2]);
		break;

	case TOWIN:
	case TOAQV:
		/* FIXME: UTF8 */
		strcpy(itemchar[1], "{\\f3 \\'B7}");
		strcpy(itemchar[2], "\\'96");
		strcpy(itemchar[3], "\\'95");
		strcpy(itemchar[4], ".");
		strcpy(itemchar[5], itemchar[1]);
		strcpy(itemchar[6], itemchar[2]);
		break;

	case TOWH4:
		/* FIXME: UTF8 */
		strcpy(itemchar[1], "{\\f3 \\'B7}");
		strcpy(itemchar[2], "-");
		strcpy(itemchar[3], "\\'95");
		strcpy(itemchar[4], ".");
		strcpy(itemchar[5], itemchar[1]);
		strcpy(itemchar[6], itemchar[2]);
		break;

	case TOKPS:
		sprintf(itemchar[1], "%s\n/bullet off1 writeBulletLeft\n%s", KPSPC_S, KPSPO_S);
		sprintf(itemchar[2], "%s\n/endash off1 writeBulletLeft\n%s", KPSPC_S, KPSPO_S);
		sprintf(itemchar[3], "%s\n/asterix off1 writeBulletLeft\n%s", KPSPC_S, KPSPO_S);
		sprintf(itemchar[4], "%s\n/periodcentered off1 writeBulletLeft\n%s", KPSPC_S, KPSPO_S);
		strcpy(itemchar[5], itemchar[1]);
		strcpy(itemchar[6], itemchar[2]);
		break;
	}
}
