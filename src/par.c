/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : par.c
*  Symbol prefix: par
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
*  Description  : ???
*
*-------------------------------------------------------------------------------
*
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*    fd  Feb 05: - file partly reformatted, TAB-free now
*                - replace_placeholders(): issue #12 fixed
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 24: replace_placeholders() debugged
*    fd  Feb 25: replace_placeholders() debugged
*    fd  Feb 26: replace_placeholders() debugged
*    fd  May 17: add_macro(): auto_quote_chars() faded
*    fd  May 19: file tidied up
*    fd  May 25: c_url() + c_xlink() now support target & class [feature request #89 solved]
*    fd  May 26: extract_parameters() + get_parameters() debugged
*  2013
*    ggs Sep 29: extract_parameters looks now for the ')'
*    fd  Oct 23: c_ilink() + c_internal_image() support HTML5
*    fd  Oct 31: c_internal_image() supports PNG images
*    tho Dec 03: c_xlink() now support target for ST-Guide
*    tho Dec 03: c_url() now generates rx-command for ST-Guide
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
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "udoport.h"
#include "constant.h"
#include "udo_type.h"
#include "udointl.h"
#include "commands.h"
#include "chr.h"
#include "file.h"
#include "msg.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"
#include "upr.h"
#include "img.h"
#include "lang.h"
#include "udomem.h"

#include "export.h"
#include "par.h"





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

/*
 * # placeholder per paragraph.
 * limited only by encoding in add_placeholder()
 * (3 * 6 bits = 2 ^ 18)
 */
#define  MAXPHOLDS      0x40000L

/*
 * # special commands per paragraph.
 * limited only by encoding in add_speccmd()
 * (3 * 6 bits = 2 ^ 18)
 */
#define MAXSPECCMDS     0x40000L

#define MAX_PARAMETERS  9				/* # of macro parameters */
#define HYPHEN_LEN        128			/* length of a word */
#define MACRO_NAME_LEN     64			/* length of a macro name */
#define MACRO_CONT_LEN   4096			/* length of a macro content */
#define DEFINE_NAME_LEN    64			/* length of a definition name */
#define DEFINE_CONT_LEN  4096			/* length of a definition content */





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _hyphen					/* hyphenated word */
{
	char hyphen[HYPHEN_LEN + 1];		/* word with hyphen marks */
	char solo[HYPHEN_LEN + 1];			/* same word, but without !- */
} HYPHEN;


typedef struct _macros					/* !macro structur */
{
	char *name;							/* macro name */
	char *entry;						/* macro content */
	_BOOL vars;							/* optional parameters */
} MACROS;


typedef struct _defs					/* !define structure */
{
	char *name;							/* definition name, formatted as (!%s) */
	char *entry;						/* definition content */
	_BOOL vars;							/* optional parameters */
} DEFS;


typedef struct _placeholder				/* general placeholder */
{
	char magic[7];						/* a control magic <ESC><0xB0 + nr> */
	char *entry;						/* the whole command */
	char *text;							/* text only (required by toklen()) */
} PLACEHOLDER;


typedef struct _speccmd					/* special format command placeholder */
{
	char magic[7];						/* a control magic <ESC><0xB0 + nr> */
	char *entry;						/* the whole command */
} SPECCMD;






/*******************************************************************************
*
*     LOCAL VARIABLES
*
******************************************|************************************/

LOCAL char Param[MAX_PARAMETERS + 1][1024];
LOCAL char Space[MAX_PARAMETERS + 1][64];

LOCAL HYPHEN **hyphen;					/* Array mit Zeigern auf Trennregeln */
LOCAL size_t hyphen_alloc;				/* size of allocated hyphen array */

LOCAL MACROS **macros;					/* Array auf Zeiger mit Makros */
LOCAL size_t macros_alloc;				/* size of allocated macro array */

LOCAL DEFS **defs;						/* Array auf Zeiger mit defines */
LOCAL size_t defs_alloc;				/* size of allocated defines array */

   /* --- Platzhalter --- */
LOCAL PLACEHOLDER *phold;				/* array of placeholders */
LOCAL size_t phold_alloc;				/* size of array */
LOCAL size_t phold_counter;				/* # of used placeholders */

LOCAL SPECCMD *speccmd;
LOCAL size_t speccmd_alloc;
LOCAL size_t speccmd_counter;

LOCAL unsigned char const encode_chars[64] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
	'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
	'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z', '#', '='
};

LOCAL int decode_chars[128];
LOCAL char const macro_allowed_name[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";



/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  del_param_quotes():
*     delete quotes in parameter strings
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void del_param_quotes(char *s)
{
	qreplace_all(s, "!)", 2, ")", 1);
	qreplace_all(s, "!]", 2, "]", 1);
}





/*******************************************************************************
*
*  get_nr_of_parameters():
*     get # of parameter blocks of command blocks in round brackets
*
*     which are formatted like this: (!command [p1] [p2] [...])
*     or even like this: (!command[p1][p2][..])
*
*  Out:
*     # of parameter blocks
*
******************************************|************************************/

LOCAL int get_nr_of_parameters(const char *cmd, const char *s)
{
	int count = 0;						/* # of found parameters */
	char *pos;
	char search[128];					/* buffer for search string */

	sprintf(search, "(!%s", cmd);		/* create search string, e.g. "(!raw" */

	if ((pos = strstr(s, search)) == NULL)
		return 0;

	/* skip command */
	pos += strlen(search);
	/* check if macro name really ends here,
	   and don't try to replace (!xlink ...) by (!x ...)
	 */
	if (strchr(macro_allowed_name, pos[0]) != NULL)
		return 0;

	/* find first uncasted closing bracket */
	while (pos[0] != ')' || (pos[0] == ')' && pos[-1] == '!'))
	{
		switch (pos[0])
		{
		case EOS:						/* not allowed: command block has a line break! */
			error_unexpected_eol();
			return 0;
		case ']':						/* parameter found? */
			if (pos[-1] != '!')			/* if ] wasn't casted by ! ... */
				count++;				/* yes, parameter found */
			break;
		}
		pos++;							/* next char */
	}

	return count;
}





/*******************************************************************************
*
*  reset_parameters():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void reset_parameters(void)
{
	int i;

	for (i = 0; i < MAX_PARAMETERS; i++)
	{
		Param[i][0] = EOS;
		Space[i][0] = EOS;
	}
}





/*******************************************************************************
*
*  extract_parameters():
*     extract parameters from a string
*
* @in: complete line
* @cmd: command without "(!": link, plink, xlink
* @min: minimum # of expected parameters
* @max: maximum # of expected parameters
*
*  Notes:
*     The string has to have the syntax "(!command [text] <[text] [...]>)".
*
*  Return:
*     # of parameters
*
******************************************|************************************/

LOCAL int extract_parameters(const char *s, const char *cmd, int count)
{
	int i;								/* # of found parameters */
	char *pos, search[128];				/* string buffer */

	sprintf(search, "(!%s", cmd);

	if ((pos = strstr(s, search)) == NULL)
		return 0;

	reset_parameters();

	pos += strlen(search);

	i = 0;

	while (i < count)
	{
		/* Anfang "[" des Parameters bestimmen */
		/* und die Zeichen ermitteln, die bis dahin */
		/* im Quelltext auftauchen */
		while (pos[0] != '[' && pos[0] != EOS)
		{
			chrcat(Space[i], pos[0]);
			pos++;
		}

		if (pos[0] == EOS)
		{
			error_unexpected_eol();
			return 0;
		}

		/* Pointer auf erstes Zeichen des Parameters setzen */
		/* und bis zur naechsten Klammer lesen, die nicht */
		/* duch ein Ausrufungszeichen gequotet ist. */
		pos++;

		while ((pos[0] != ']' || (pos[0] == ']' && pos[-1] == '!')) && (pos[0] != EOS))
		{
			chrcat(Param[i + 1], pos[0]);
			pos++;
		}

		if (pos[0] == EOS)
		{
			error_unexpected_eol();
			return 0;
		}

		pos++;
		i++;
	}

	/* Zeichen lesen, die bis zum Ende des Kommandos auftauchen */
	while (pos[0] != ')' && pos[0] != EOS)
	{
		chrcat(Space[count], pos[0]);
		pos++;
	}
	if (pos[0] == EOS)
	{
		error_unexpected_eol();
		return 0;
	}

	return i;
}





/*******************************************************************************
*
*  get_parameters():
*     get parameters from a string
*
* @in: complete line
* @cmd: command without "(!": link, plink, xlink
* @min: minimum # of expected parameters
* @max: maximum # of expected parameters
*
*  Return:
*     # of parameters
*
******************************************|************************************/

LOCAL int get_parameters(const char *s, const char *search, int min, int max)
{
	int i, params;

	params = get_nr_of_parameters(search, s);

	if (params == 0)
		return 0;
	if (params < min || params > max)
		return params;

	params = extract_parameters(s, search, params);

	if (params == 0)
		return 0;

	sprintf(Param[0], "(!%s%s", search, Space[0]);

	if (params > 0)
	{
		for (i = 1; i <= params; i++)
		{
			strcat(Param[0], "[");
			strcat(Param[0], Param[i]);
			strcat(Param[0], "]");
			strcat(Param[0], Space[i]);

			del_param_quotes(Param[i]);
		}
	}

	strcat(Param[0], ")");

	return params;
}





/*******************************************************************************
*
*  adjust_params_inside():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void adjust_params_inside(char *s)
{
	replace_macros(s);
	c_divis(s);
	c_vars(s);
	c_styles(s);
}





/*******************************************************************************
*
*  convert_link_lds():
*     convert a link command into LDS format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_lds(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char s_entry[1024];
	char old_entry[1024];
	char *ptr;
	_BOOL flag;

	strcpy(s_entry, p2);
	c_tilde(s_entry);
	replace_udo_quotes(s_entry);

	convert_tilde(p1);
	convert_tilde(p2);

	replace_udo_quotes(p1);
	replace_udo_quotes(p2);

	strcpy(old_entry, p2);

	/* auch Links innerhalb der Seite ermoeglichen */
	gen_references(s_entry, TRUE, "", 0, 0);

	/* Trick: Schauen, ob nun "> im Eintrag steht und dann */
	/* ab dort den Link einsetzen. */
	flag = FALSE;
	if ((ptr = strstr(s_entry, "name=\"")) != NULL)
		flag = replace_once(ptr, old_entry, p1);

	if (!flag)
	{
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}





/*******************************************************************************
*
*  convert_link_stg():
*     convert a link command into STG format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_stg(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char nodename[256];
	char s_entry[256];
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;

	c_tilde(p2);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	replace_udo_tilde(p2);
	replace_udo_nbsp(p2);

	convert_tilde(p1);
	replace_udo_quotes(p1);

	if (flag)
	{
		node2stg(p1);
		node2stg(p2);
		node2stg(nodename);

		/* links auf gleiche node mag ST-Guide nicht */
		if (isnode && is_current_node(ti))
		{
			strcpy(s_entry, p1);
		} else
		{
			if (!isnode)				/* Links auf Labels sind etwas besonderes */
			{
				/* AmigaGuide does not have labels or aliases */
				if (desttype == TOAMG)
				{
					strcpy(s_entry, p1);
					warning_message(_("AmigaGuide cannot link to label '%s'"), link);
				} else
				{
					sprintf(s_entry, "@{\"%s\" LINK \"%s\" \"%s\"}", p1, nodename, p2);
				}
			} else
			{
				sprintf(s_entry, "@{\"%s\" LINK \"%s\"}", p1, p2);
			}
		}
	} else
	{
		/*
		 * Allow links to Index page. It is not generated
		 * by UDO and therefore not found as link destination.
		 * Also allow explicit links to Main, which is a label
		 * generated by HCP, or an alias generated by UDO
		 * if !tableofcontents was used.
		 */
		if ((!no_index && strcmp(p2, "Index") == 0) || strcmp(p2, "Main") == 0)
		{
			sprintf(s_entry, "@{\"%s\" LINK \"%s\"}", p1, p2);
		} else
		{
			/* Node, Alias or Label undefined */
			error_undefined_link(link);
			strcpy(s_entry, p1);
		}
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}





/*******************************************************************************
*
*  convert_link_pch():
*     convert a link command into PureC format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_pch(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char nodename[256];
	char s_entry[256];
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;

	c_tilde(p2);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	replace_udo_tilde(p2);
	replace_udo_nbsp(p2);

	convert_tilde(p1);
	replace_udo_quotes(p1);

	if (flag)
	{
		node2pchelp(p2);
		sprintf(s_entry, "\\link(\"%s\")%s\\#", p2, p1);
	} else
	{
		/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}





/*******************************************************************************
*
*  convert_link_tex():
*     convert a link command into TeX format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_tex(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char *s_entry;
	LABIDX li;
	TOCIDX ti;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;
	char nodename[256];
	_BOOL ret;

	convert_tilde(p2);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	label2tex(p2);
	convert_tilde(p1);
	replace_udo_quotes(p1);

	if (flag)
	{
		s_entry = um_strdup_printf("%s (%s \\ref{%s})", p1, get_lang()->see, p2);
	} else
	{
		/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		s_entry = strdup(p1);
	}

	ret = insert_placeholder(s, p0, s_entry, p1);
	free(s_entry);
	return ret;
}





/*******************************************************************************
*
*  convert_link_pdf():
*     convert a link command into PDF format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_pdf(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char nodename[256];
	char s_entry[256];
	TOCIDX ti;
	LABIDX li;
	int dest;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;

	c_tilde(p2);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	convert_tilde(p1);
	replace_udo_quotes(p1);

	if (flag)
	{
		if (isnode)
			dest = getLabelIndexFromTocIndex(&li, ti);
		else
			dest = li;

		sprintf(s_entry, "{\\leavevmode\\pdfstartlink goto num %u %s\\pdfendlink}", dest, p1);
	} else								/* Node, Alias oder Label nicht definiert */
	{
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}





/*******************************************************************************
*
*  convert_link_lyx():
*     convert a link command into LaTeX format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_lyx(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char s_entry[1024];
	LABIDX li;
	TOCIDX ti;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;
	char nodename[256];

	convert_tilde(p2);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	label2lyx(p2);

	if (flag)
	{
		sprintf(s_entry, "%s (%s\n\\begin_inset LatexCommand \\ref{%s}\n\n\\end_inset\n\n)", p1, get_lang()->see, p2);
	} else
	{
		/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}





/*******************************************************************************
*
*  convert_link_tvh():
*     convert a link command into TurboVisionHelp format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_tvh(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char s_entry[1024];
	LABIDX li;
	TOCIDX ti;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;
	char nodename[256];

	c_tilde(p2);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	if (flag)
	{
		node2vision(p2);
		sprintf(s_entry, "{%s:%s}", p1, p2);
	} else
	{
		/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}





/*******************************************************************************
*
*  convert_link_info():
*     convert a link command into TeXinfo format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_info(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char nodename[256];
	char s_entry[256];
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;

	c_tilde(p2);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	convert_tilde(p1);
	replace_udo_quotes(p1);
	qreplace_all(p1, "*", 1, "\\*", 2);

	replace_udo_tilde(p2);
	replace_udo_nbsp(p2);
	node2texinfo(p2);

	if (flag)
	{
		if (isnode)
			strcpy(nodename, p2);
		else
			node2texinfo(nodename);
		sprintf(s_entry, "%s (@pxref{%s})", p1, nodename);
	} else
	{
		/* Node, Alias oder Label nicht definiert */
		if (!no_index && bCalledIndex && use_udo_index && strcmp(p2, "Index") == 0)
		{
			/*
			 * Allow links to Index page. It is automatically generated
			 * by UDO and therefore not found as link destination
			 */
			sprintf(s_entry, "%s (@pxref{%s})", p1, get_lang()->index);
		} else
		{
			error_undefined_link(link);
			strcpy(s_entry, p1);
		}
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}





/*******************************************************************************
*
*  convert_link_ipf():
*     convert a link command into IPF format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_ipf(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char nodename[256];
	char s_entry[256];
	char s_id[256];
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;

	c_tilde(p2);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	convert_tilde(p1);
	replace_udo_quotes(p1);

	if (flag)
	{
		getLabelIndexFromTocIndex(&li, ti);
		node2NrIPF(s_id, li);
		sprintf(s_entry, ":link reftype=hd refid=%s.%s:elink.", s_id, p1);
	} else
	{
		/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}





/*******************************************************************************
*
*  convert_link_ps():
*     ??? (description)
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_ps(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char nodename[256];
	char s_entry[256];
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;

	c_tilde(p2);
	replace_udo_quotes(p2);

	/* Internal Link for Postscript */
	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	convert_tilde(p1);

	if (flag)
	{
		replace_udo_quotes(p1);

		replace_all(p1, "(", "\\(");
		replace_all(p1, ")", "\\)");

		qreplace_all(p1, KPSPC_S, KPSPC_S_LEN, ")", 1);
		qreplace_all(p1, KPSPO_S, KPSPO_S_LEN, "(", 1);
		node2postscript(p2, KPS_NAMEDEST);
		sprintf(s_entry, ") udoshow (%s) /%s 0 255 0 Link (", p1, p2);
	} else
	{
		/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}





/*******************************************************************************
*
*  convert_link_etc():
*     convert a link command into RTF? format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_etc(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char nodename[256];
	char s_entry[256];
	char lq[16], rq[16];
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;

	c_tilde(p2);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	replace_udo_tilde(p2);
	replace_udo_nbsp(p2);

	convert_tilde(p1);
	replace_udo_quotes(p1);

	if (flag)
	{
		if (no_links)
		{
			strcpy(s_entry, p1);
		} else
		{
			if (desttype == TORTF)		/* die richtigen benutzen */
			{
				strcpy(lq, "\\ldblquote ");
				strcpy(rq, "\\rdblquote");
			} else
			{
				strcpy(lq, "\"");
				strcpy(rq, "\"");
			}

			if (!isnode)
			{
				/* Links auf Labels sind etwas besonderes */
				sprintf(s_entry, "%s (%s %s%s%s)", p1, get_lang()->see, lq, nodename, rq);
			} else
			{
				sprintf(s_entry, "%s (%s %s%s%s)", p1, get_lang()->see, lq, p2, rq);
			}
		}
	}

	if (!flag)
	{
		/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}

	if (insert_placeholder(s, p0, s_entry, p1))
		return TRUE;

	return FALSE;
}



/*******************************************************************************
*
*  convert_link_win():
*     convert a link command into WinHelp/WinHelp4 format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_win(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char s_entry[1024];
	char nodename[1024];
	_BOOL flag;
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;

	strcpy(s_entry, p2);
	c_tilde(s_entry);
	replace_udo_quotes(s_entry);

	convert_tilde(p1);
	convert_tilde(p2);
	replace_udo_quotes(p1);
	replace_udo_quotes(p2);
	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	if (flag)
	{
		if (no_links)
		{
			strcpy(s_entry, p1);
		} else
		{
#if 0
			replace_udo_tilde(nodename);
			replace_udo_nbsp(nodename);
			if (isnode)
				node2NrWinhelp(ref, li);
			else if (isalias)
				alias2NrWinhelp(ref, li);
			else
				label2NrWinhelp(ref, li);
			if (ispopup)
			{
				sprintf(s_entry, "{\\ul %s}{\\v %s}", nodename, ref);
			} else
			{
				sprintf(s_entry, "{\\uldb %s}{\\v %s}", nodename, ref);
			}
#else
			string2reference(s_entry, p1, li, TRUE, "", 0, 0);
#endif
		}
	} else
	{
		/*
		 * Allow links to Index page. It is not generated
		 * by UDO and therefore not found as link destination.
		 */
		if ((!no_index && bCalledIndex && strcmp(p2, "Index") == 0))
		{
			sprintf(s_entry, "{\\uldb %s}{\\v !JumpKeyword(`')}", p1);
		} else
		{
			/* Node, Alias or Label undefined */
			error_undefined_link(link);
			strcpy(s_entry, p1);
		}
	}
	return insert_placeholder(s, p0, s_entry, p1);
}




/*******************************************************************************
*
*  convert_link_html():
*     convert a link command into HTML format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL _BOOL convert_link_html(char *s, const char *p0, char *p1, char *p2, const char *link)
{
	char s_entry[1024];
	char nodename[1024];
	_BOOL flag;
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;

	strcpy(s_entry, p2);
	c_tilde(s_entry);
	replace_udo_quotes(s_entry);

	convert_tilde(p1);
	convert_tilde(p2);
	replace_udo_quotes(p1);
	replace_udo_quotes(p2);

	flag = is_node_link(p2, nodename, &ti, &isnode, &isalias, &ispopup, &li);

	if (flag)
	{
		if (no_links)
		{
			strcpy(s_entry, p1);
		} else
		{
			string2reference(s_entry, p1, li, TRUE, "", 0, 0);
		}
	} else
	{
		if (desttype != TOMHH && use_udo_index && !no_index && bCalledIndex && !no_links && strcmp(p2, "Index") == 0)
		{
			sprintf(s_entry, "<a href=\"%s%s\">%s</a>", sDocHtmlIndexudo, outfile.suff, get_lang()->index);
		} else
		{
			error_undefined_link(link);
			strcpy(s_entry, p1);
		}
	}

	return insert_placeholder(s, p0, s_entry, p1);
}


/*******************************************************************************
*
*  c_link():
*     convert a link command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_link(char *s, _BOOL inside_b4_macro)
{
	int pnr = 0;
	_BOOL linkerror;
	char link[1024];
	char nodename[256];
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL flag;
	_BOOL uses_default;
	
	linkerror = FALSE;
	while (!linkerror && (pnr = get_parameters(s, "link", 2, 2)) == 2)
	{
		del_whitespaces(Param[1]);
		del_whitespaces(Param[2]);

		/* Wird ein leerer Parameter benutzt, den */
		/* den ersten auch als zweiten verwenden. */
		uses_default = FALSE;
		if (Param[2][0] == EOS)
		{
			strcpy(Param[2], Param[1]);
			uses_default = TRUE;
		}
		strcpy(link, Param[2]);

		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(Param[2], TRUE);
			}

			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}
		
		if (uses_default)
		{
			flag = is_node_link(Param[2], nodename, &ti, &isnode, &isalias, &ispopup, &li);
			if (flag && isnode && toc_table[ti]->nodetitle != toc_table[ti]->nodename)
			{
				strcpy(Param[1], toc_table[ti]->nodetitle);
				if (inside_b4_macro)
				{
					if (desttype != TOSTG)
						auto_quote_chars(Param[1], TRUE);
					adjust_params_inside(Param[1]);
				}
			}
		}
		
		switch (desttype)
		{
		case TOHAH:
		case TOHTM:
		case TOMHH:
			linkerror = !convert_link_html(s, Param[0], Param[1], Param[2], link);
			break;

		case TOWIN:
		case TOWH4:
		case TOAQV:
			linkerror = !convert_link_win(s, Param[0], Param[1], Param[2], link);
			break;

		case TOLDS:
			linkerror = !convert_link_lds(s, Param[0], Param[1], Param[2], link);
			break;

		case TOSTG:
		case TOAMG:
			linkerror = !convert_link_stg(s, Param[0], Param[1], Param[2], link);
			break;

		case TOTEX:
			linkerror = !convert_link_tex(s, Param[0], Param[1], Param[2], link);
			break;

		case TOPDL:
			linkerror = !convert_link_pdf(s, Param[0], Param[1], Param[2], link);
			break;

		case TOLYX:
			linkerror = !convert_link_lyx(s, Param[0], Param[1], Param[2], link);
			break;

		case TOTVH:
			linkerror = !convert_link_tvh(s, Param[0], Param[1], Param[2], link);
			break;

		case TOPCH:
			linkerror = !convert_link_pch(s, Param[0], Param[1], Param[2], link);
			break;

		case TOINF:
			linkerror = !convert_link_info(s, Param[0], Param[1], Param[2], link);
			break;

		case TOIPF:
			linkerror = !convert_link_ipf(s, Param[0], Param[1], Param[2], link);
			break;

		case TOKPS:
			linkerror = !convert_link_ps(s, Param[0], Param[1], Param[2], link);
			break;

		default:
			linkerror = !convert_link_etc(s, Param[0], Param[1], Param[2], link);
			break;
		}
	}

	if (linkerror)
	{
		replace_once(s, Param[0], Param[1]);
		error_replace_param("!link");
	}

	if (pnr != 0 && pnr != 2)
		error_wrong_nr_parameters("!link");
}





/*******************************************************************************
*
*  c_url():
*     convert a url command into its target format
*
*  Notes:
*     The command (!url) supports up to four parameters:
*     1) the readable title for the URL
*     2) the URL
*     4) a target
*     3) a class name (to be referenced in any CSS definition)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_url(char *s, _BOOL inside_b4_macro)
{
	int pnr = 0;
	int url_len;
	int i;
	char *s_entry;
	char url_rtf[2048];
	char rtf0[4];
	_BOOL linkerror = FALSE;
	char *target;
	char *css_class;

	static char const rtf1[] = "00d0c9ea79f9bace118c8200aa004ba90b0200000003000000";
	static char const rtf2[] = "e0c9ea79f9bace118c8200aa004ba90b";
	static char const rtf3[] = "000000";
	static char const rtf4[] = "0000";

	while (!linkerror && (pnr = get_parameters(s, "url", 2, 4)) >= 2)
	{
		del_whitespaces(Param[1]);		/* adjust URL */

		/* if title is empty, use URL as title */
		if (Param[2][0] == EOS)
			strcpy(Param[2], Param[1]);

		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
				auto_quote_chars(Param[1], TRUE);

			adjust_params_inside(Param[1]);
		}

		if (no_urls)
		{
			replace_all(s, Param[0], Param[1]);
		} else
		{
			switch (desttype)
			{
			case TOSTG:
			case TOAMG:
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);

				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[1]);

				node2stg(Param[2]);
				node2stg(Param[1]);

				s_entry = um_strdup_printf("@{\"%s\" RX \"%s\"}", Param[1], Param[2]);
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				break;

			case TOHAH:
			case TOHTM:
			case TOMHH:
				convert_tilde(Param[1]);
				replace_udo_quotes(Param[4]);
				replace_udo_quotes(Param[3]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[1]);

				if (Param[4][0] != EOS)	/* CSS class used */
					css_class = um_strdup_printf(" class=\"%s\"", Param[4]);
				else
					css_class = strdup("");

				if (Param[3][0] != EOS)	/* target used */
					target = um_strdup_printf(" target=\"%s\"", Param[3]);
				else if (html_frames_layout)
					target = um_strdup_printf(" target=\"%s\"", "_top");
				else
					target = strdup("");

				s_entry = um_strdup_printf("<a href=\"%s\"%s%s>%s</a>", Param[2], target, css_class, Param[1]);
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				free(target);
				free(css_class);
				break;

			case TOKPS:
				convert_tilde(Param[1]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[1]);

				c_divis(Param[1]);

				node2postscript(Param[1], KPS_CONTENT);
				replace_all(Param[1], KPSPO_S, "(");
				replace_all(Param[1], KPSPC_S, ")");
				s_entry = um_strdup_printf(") udoshow (%s) (%s) 0 0 255 WebLink (", Param[1], Param[2]);
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				convert_tilde(Param[1]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[1]);
				s_entry =
					um_strdup_printf("{\\uldb %s}{\\v !ShellExecuteA(0, \"open\", \"%s\", \"\", \"\", 1)}", Param[1],
									 Param[2]);
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				break;

			case TORTF:
				convert_tilde(Param[1]);
				c_rtf_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[1]);

				auto_quote_chars(Param[2], TRUE);
				url_len = (int) strlen(Param[2]);

				rtf0[0] = EOS;
				url_rtf[0] = EOS;

				for (i = 0; i < url_len; i++)
				{
					if (Param[2][i] == '\\')
					{
						i += 2;
						rtf0[0] = EOS;
						strncpy(rtf0, Param[2] + i, 2);
						i++;
					} else
					{
						sprintf(rtf0, "%x", (int) Param[2][i]);
					}
					strcat(url_rtf, rtf0);
					strcat(url_rtf, "00");
				}

				s_entry =
					um_strdup_printf
					("{\\field{\\*\\fldinst {HYPERLINK \"%s\"}{{\\*\\datafield %s%s%x%s%s%s}}}\n{\\fldrslt {\\cs15\\ul\\cf2 %s}}}",
					 Param[2], rtf1, rtf2, (url_len + 1) * 2, rtf3, url_rtf, rtf4, Param[1]);
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				break;

			case TOINF:
				convert_tilde(Param[1]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				s_entry = um_strdup_printf("@uref{%s, %s}", Param[2], Param[1]);
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				break;

			default:
				convert_tilde(Param[1]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				linkerror = !insert_placeholder(s, Param[0], Param[1], Param[1]);
				break;
			}
		}
	}

	if (linkerror)
	{
		replace_once(s, Param[0], Param[1]);
		error_replace_param("!url");
	}

	if (pnr != 0 && pnr != 2)
		error_wrong_nr_parameters("!url");
}





/*******************************************************************************
*
*  c_xlink():
*     convert an xlink command into its target format
*
*  Notes:
*     The command (!xlink) supports up to four parameters:
*     1) the readable title for the URL
*     2) the URL
*     4) a target
*     3) a class name (to be referenced in any CSS definition)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_xlink(char *s, _BOOL inside_b4_macro)
{
	int pnr = 0;
	char *s_entry;
	char wnode[1024];
	char wfile[1024];
	char *ptr;
	_BOOL linkerror = FALSE;
	char *target;
	char *css_class;

	while (!linkerror && (pnr = get_parameters(s, "xlink", 2, 4)) >= 2)
	{
		del_whitespaces(Param[1]);

		/* Wird ein leerer Parameter benutzt, dann den ersten auch als zweiten verwenden. */
		if (Param[2][0] == EOS)
			strcpy(Param[2], Param[1]);

		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
				auto_quote_chars(Param[1], TRUE);

			adjust_params_inside(Param[1]);
		}

		if (no_xlinks)
		{
			replace_all(s, Param[0], Param[1]);
		} else
		{
			switch (desttype)
			{
			case TOSTG:
			case TOAMG:
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);

				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[1]);

				node2stg(Param[2]);
				node2stg(Param[1]);

				{
					const char *cmd;

					if (strcmp(Param[3], "_new") == 0 || strcmp(Param[3], "_blank") == 0)
						cmd = "ALINK";
					else
						cmd = "LINK";
					s_entry = um_strdup_printf("@{\"%s\" %s \"%s\"}", Param[1], cmd, Param[2]);
				}
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				break;

			case TOHAH:
			case TOHTM:
			case TOMHH:
				convert_tilde(Param[1]);
				replace_udo_quotes(Param[4]);
				replace_udo_quotes(Param[3]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[1]);

				if (Param[4][0] != EOS)	/* CSS class used */
					css_class = um_strdup_printf(" class=\"%s\"", Param[4]);
				else
					css_class = strdup("");

				if (Param[3][0] != EOS)	/* target used */
					target = um_strdup_printf(" target=\"%s\"", Param[3]);
				else if (html_frames_layout)
					target = um_strdup_printf(" target=\"%s\"", "_top");
				else
					target = strdup("");

				s_entry = um_strdup_printf("<a href=\"%s\"%s%s>%s</a>", Param[2], target, css_class, Param[1]);
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				free(target);
				free(css_class);
				/*
				 * alternative for htmlhelp:
				 *
				 <OBJECT id=hhctrl type="application/x-oleobject"
				 classid="clsid:adb880a6-d8ff-11cf-9377-00aa003b7a11"
				 codebase="hhctrl.ocx"
				 >
				 <PARAM name="Command" value="KLink">
				 <PARAM name="Button" value="Text:buttontext">
				 <PARAM name="Item1" value="reflink.chm">
				 <PARAM name="Item2" value="keyword">
				 </OBJECT>
				 */
				break;

			case TOLDS:
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);

				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);

				s_entry = um_strdup_printf("<htmlurl url=\"%s\" name=\"%s\">", Param[2], Param[1]);
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				break;

			case TOPCH:
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);

				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);

				s_entry = um_strdup_printf("\\#%s\\#", Param[1]);
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);

				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);

				ptr = strrchr(Param[2], '@');
				if (ptr != NULL)
				{
					ptr[0] = EOS;
					strcpy(wnode, Param[2]);
					strcpy(wfile, ptr + 1);

					if (wnode[0] != EOS && wfile[0] != EOS)
					{
						node2winhelp(wnode);
						s_entry = um_strdup_printf("{\\uldb %s}{\\v %s@%s}", Param[1], wnode, wfile);
						linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
						free(s_entry);
					} else
					{
						if (wnode[0] != EOS)
						{
							error_message(_("xlink needs WinHelp destination topic"));
							linkerror = !replace_once(s, Param[0], Param[1]);
						}

						if (wfile[0] != EOS)
						{
							error_message(_("xlink needs WinHelp destination file"));
							linkerror = !replace_once(s, Param[0], Param[1]);
						}
					}
				} else
				{
					error_message(_("use (!xlink [text] [topic@foo.hlp])"));
					linkerror = !replace_once(s, Param[0], Param[1]);
				}
				break;

			case TOKPS:
				convert_tilde(Param[1]);

				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[1]);
				c_divis(Param[1]);
				auto_quote_chars(Param[1], TRUE);

				s_entry = um_strdup_printf(") udoshow (%s) (%s) %s 255 0 0 FileLink (", Param[1], Param[2], "/Null");
				linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
				free(s_entry);
				break;

			default:
				convert_tilde(Param[1]);

				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);

				linkerror = !insert_placeholder(s, Param[0], Param[1], Param[1]);
				break;
			}
		}
	}

	if (linkerror)
	{
		replace_once(s, Param[0], Param[1]);
		error_replace_param("!xlink");
	}

	if (pnr != 0 && pnr != 2)
		error_wrong_nr_parameters("!xlink");
}





/*******************************************************************************
*
*  c_ilink():
*     convert an ilink command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_ilink(char *s, const _BOOL inside_b4_macro)
{
	int pnr = 0;
	char s_entry[1024];
	char *img_entry;
	char old_entry[1024];
	char link[1024];
	char *ptr;
	_BOOL flag;
	_BOOL linkerror;
	TOCIDX ti;
	LABIDX li;
	_BOOL isnode;
	_BOOL isalias;
	_BOOL ispopup;
	_BOOL uses_default;
	char nodename[256];

	linkerror = FALSE;
	while (!linkerror && (pnr = get_parameters(s, "ilink", 3, 3)) == 3)
	{
		del_whitespaces(Param[1]);
		del_whitespaces(Param[2]);
		del_whitespaces(Param[3]);

		uses_default = FALSE;
		if (Param[3][0] == EOS)
		{
			strcpy(Param[3], Param[2]);
			uses_default = TRUE;
		}
		strcpy(link, Param[3]);
		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[2], TRUE);
				auto_quote_chars(Param[3], TRUE);
			}

			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
			adjust_params_inside(Param[3]);
		}

		fsplit(Param[1], tmp_driv, tmp_path, tmp_name, tmp_suff);

		replace_udo_quotes(Param[2]);
		replace_udo_quotes(Param[3]);

		if (uses_default)
		{
			flag = is_node_link(Param[3], nodename, &ti, &isnode, &isalias, &ispopup, &li);
			if (flag && isnode && toc_table[ti]->nodetitle != toc_table[ti]->nodename)
			{
				strcpy(Param[1], toc_table[ti]->nodetitle);
				if (inside_b4_macro)
				{
					if (desttype != TOSTG)
						auto_quote_chars(Param[1], TRUE);
					adjust_params_inside(Param[1]);
					replace_udo_quotes(Param[1]);
				}
			}
		}
		
		switch (desttype)
		{
		case TOHAH:
		case TOHTM:
		case TOMHH:
			strcpy(tmp_suff, sDocImgSuffix);
			sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
			replace_char(Param[1], '\\', '/');

			strcpy(s_entry, Param[3]);
			c_tilde(s_entry);
			replace_udo_quotes(s_entry);

			convert_tilde(Param[2]);
			convert_tilde(Param[3]);
			replace_udo_quotes(Param[2]);
			replace_udo_quotes(Param[3]);
			strcpy(old_entry, Param[3]);

			/* auch innerhalb des Nodes linken (TRUE)! */
			gen_references(s_entry, TRUE, "", 0, 0);

			/* Trick/Hack: Schauen, ob nun "> im Eintrag steht und dann */
			/* ab dort den Image-Eintrag setzen. */

			flag = FALSE;
			if ((ptr = strstr(s_entry, "\">")) != NULL)
			{
				if (no_images)
				{
					img_entry = strdup(Param[2]);
				} else
				{
					char border[20];

					strcpy(border, " border=\"0\"");
#if 0
					if (html_doctype == HTML5)
						*border = EOS;
#endif
					img_entry = um_strdup_printf("<img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s>",
												 Param[1], Param[2], Param[2], border, xhtml_closer);
				}
				flag = replace_once(ptr, old_entry, img_entry);
				free(img_entry);
			}

			if (!flag)
			{
				error_undefined_link(link);
				strcpy(s_entry, Param[2]);
			}

			linkerror = !insert_placeholder(s, Param[0], s_entry, Param[2]);
			break;

		case TOWIN:
		case TOWH4:
		case TOAQV:
			strcpy(tmp_suff, ".bmp");
			sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
			replace_char(Param[1], '\\', '/');

			strcpy(s_entry, Param[3]);
			c_tilde(s_entry);
			replace_udo_quotes(s_entry);

			convert_tilde(Param[2]);
			convert_tilde(Param[3]);
			replace_udo_quotes(Param[2]);
			replace_udo_quotes(Param[3]);
			strcpy(old_entry, Param[3]);

			/* auch innerhalb des Nodes linken (TRUE)! */
			gen_references(s_entry, TRUE, "", 0, 0);

			/* Trick: Schauen, ob nun {\uldb im Eintrag steht und dann */
			/* ab dort den Image-Text einsetzen. */
			flag = FALSE;
			if ((ptr = strstr(s_entry, "{\\uldb")) != NULL)
			{
				if (no_images)
				{
					img_entry = strdup(Param[2]);
				} else
				{
					img_entry = um_strdup_printf("\\{bmc %s\\}", Param[1]);
				}
				flag = replace_once(ptr, old_entry, img_entry);
				free(img_entry);
			}

			if (!flag)
			{
				error_undefined_link(link);
				strcpy(s_entry, Param[2]);
			}

			linkerror = !insert_placeholder(s, Param[0], s_entry, Param[2]);
			break;

		case TOLDS:
			linkerror = !convert_link_lds(s, Param[0], Param[2], Param[3], link);
			break;

		case TOSTG:
		case TOAMG:
			linkerror = !convert_link_stg(s, Param[0], Param[2], Param[3], link);
			break;

		case TOTEX:
		case TOPDL:
			linkerror = !convert_link_tex(s, Param[0], Param[2], Param[3], link);
			break;

		case TOLYX:
			linkerror = !convert_link_lyx(s, Param[0], Param[2], Param[3], link);
			break;

		case TOTVH:
			linkerror = !convert_link_tvh(s, Param[0], Param[2], Param[3], link);
			break;

		case TOKPS:
			linkerror = !convert_link_ps(s, Param[0], Param[2], Param[3], link);
			break;

		default:
			linkerror = !convert_link_etc(s, Param[0], Param[2], Param[3], link);
			break;
		}
	}

	if (linkerror)
	{
		replace_once(s, Param[0], Param[2]);
		error_replace_param("!ilink");
	}

	if (pnr != 0 && pnr != 3)
		error_wrong_nr_parameters("!ilink");
}





/*******************************************************************************
*
*  c_plink():
*     convert a plink command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_plink(char *s, const _BOOL inside_b4_macro)
{
	int pnr = 0;
	char *s_entry;
	char n[512];
	_BOOL linkerror = FALSE;

	while (!linkerror && (pnr = get_parameters(s, "plink", 2, 2)) == 2)
	{
		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(Param[2], TRUE);
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		switch (desttype)
		{
		case TOTEX:
			label2tex(Param[2]);
			s_entry =
				um_strdup_printf("%s (%s %s \\pageref{%s})", Param[1], get_lang()->see, get_lang()->page, Param[2]);
			linkerror = !replace_once(s, Param[0], s_entry);
			free(s_entry);
			break;

		case TOPDL:
			linkerror = !convert_link_pdf(s, Param[0], Param[1], Param[2], Param[2]);
			break;

		case TOLYX:
			label2lyx(Param[2]);
			s_entry = um_strdup_printf("%s (%s %s \\begin_inset LatexCommand \\pageref{%s}\\end_inset)",
									   Param[1], get_lang()->see, get_lang()->page, Param[2]);
			if (!insert_placeholder(s, Param[0], s_entry, s_entry))
			{
				linkerror = TRUE;
				replace_once(s, Param[0], s_entry);
			}
			free(s_entry);
			break;

		case TORTF:
			um_strcpy(n, Param[2], 512, "c_plink[1]");
			node2winhelp(n);

			s_entry = um_strdup_printf("%s (%s %s {\\field{\\*\\fldinst {PAGEREF %s }}{\\fldrslt {\\lang1024 x}}})",
									   Param[1], get_lang()->see, get_lang()->page, n);
			linkerror = !replace_once(s, Param[0], s_entry);
			free(s_entry);
			break;

		default:
			linkerror = !replace_once(s, Param[0], Param[1]);
			break;
		}
	}

	if (pnr != 0 && pnr != 2)
		error_wrong_nr_parameters("!plink");

	if (linkerror)
		error_replace_param("!plink");
}





/*******************************************************************************
*
*  c_plabel():
*     convert a label command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_plabel(char *s, const _BOOL inside_b4_macro)
{
	int pnr = 0;
	char *s_entry;
	char n[512];
	_BOOL linkerror = FALSE;

	while (!linkerror && (pnr = get_parameters(s, "label", 2, 2)) == 2)
	{
		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(Param[2], TRUE);
			}

			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		switch (desttype)
		{
		case TORTF:
			um_strcpy(n, Param[2], 512, "c_plabel[1]");
			node2winhelp(n);
			s_entry = um_strdup_printf("{\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}", n, Param[1], n);
			linkerror = !replace_once(s, Param[0], s_entry);
			free(s_entry);
			break;

		default:
			linkerror = !replace_once(s, Param[0], Param[1]);
			break;
		}
	}

	if (pnr != 0 && pnr != 2)
		error_wrong_nr_parameters("!label");

	if (linkerror)
		error_replace_param("!label");
}





/*******************************************************************************
*
*  c_nolink():
*     convert a nolink command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_nolink(char *s, const _BOOL inside_b4_macro)
{
	int pnr = 0;
	char s_entry[1024];
	_BOOL linkerror = FALSE;

	while (!linkerror && (pnr = get_parameters(s, "nolink", 1, 1)) == 1)
	{
		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(Param[2], TRUE);
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		switch (desttype)
		{
		case TOSTG:
		case TOAMG:
			sprintf(s_entry, "@{\"%s\" ignore}", Param[1]);
			if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
			{
				linkerror = TRUE;
				replace_once(s, Param[0], Param[1]);
			}
			break;

		default:
			if (!insert_placeholder(s, Param[0], Param[1], Param[1]))
			{
				linkerror = TRUE;
				replace_once(s, Param[0], Param[1]);
			}
			break;
		}
	}

	if (pnr != 0 && pnr != 1)
		error_wrong_nr_parameters("!nolink");

	if (linkerror)
		error_replace_param("!nolink");
}





/*******************************************************************************
*
*  c_comment():
*     convert a comment command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_comment(char *s, const _BOOL inside_b4_macro)
{
	int pnr = 0;
	char *s_entry;
	_BOOL linkerror = FALSE;

	while (!linkerror && (pnr = get_parameters(s, "comment", 1, 1)) == 1)
	{
		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(Param[2], TRUE);
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		switch (desttype)
		{
		case TOHAH:
		case TOHTM:
		case TOMHH:
			s_entry = um_strdup_printf("<!-- %s -->", Param[1]);
			if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
			{
				linkerror = TRUE;
				replace_once(s, Param[0], Param[1]);
			}
			free(s_entry);
			break;

		case TOSRC:
		case TOSRP:
			s_entry = um_strdup_printf("%s %s %s", sSrcRemOn, Param[1], sSrcRemOff);
			if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
			{
				linkerror = TRUE;
				replace_once(s, Param[0], Param[1]);
			}
			free(s_entry);
			break;

		case TOWIN:
		case TOWH4:
		case TORTF:
		case TOAQV:
			s_entry = um_strdup_printf("{\\*\\%s}", Param[1]);
			if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
			{
				linkerror = TRUE;
				replace_once(s, Param[0], Param[1]);
			}
			free(s_entry);
			break;

		default:
			if (use_comments)
			{
				s_entry = um_strdup_printf("(%s)", Param[1]);
				if (!replace_once(s, Param[0], s_entry))
				{
					linkerror = TRUE;
					replace_once(s, Param[0], Param[1]);
				}
				free(s_entry);
			} else
			{
				if (!delete_once(s, Param[0]))
					linkerror = TRUE;
			}
			break;
		}
	}

	if (pnr != 0 && pnr != 1)
		error_wrong_nr_parameters("comment");

	if (linkerror)
		error_replace_param("comment");
}





/*******************************************************************************
*
*  c_index():
*     convert an index command into its target format
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL c_index(char *s, const _BOOL inside_b4_macro)
{
	char s_tidx[1024];
	char *s_entry;
	char keyword[1024];
	_BOOL ret = TRUE;

	if (get_parameters(s, "index", 1, 1) > 0)
	{
		strcpy(s_tidx, Param[1]);

		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(s_tidx, TRUE);
			}
			adjust_params_inside(Param[1]);
		}

		/* Set index in project file */
		if (bUseUPRfile)
			save_upr_entry_index(1, sCurrFileName, Param[1], uiCurrFileLine);

		if (no_index)
		{
			ret = replace_once(s, Param[0], Param[1]);
		} else
		{
			bCalledIndex = TRUE;
			switch (desttype)
			{
			case TOTEX:
			case TOPDL:
				auto_quote_texindex(s_tidx);
				s_entry = um_strdup_printf("\\index{%s}", s_tidx);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOLYX:
				auto_quote_texindex(s_tidx);
				s_entry =
					um_strdup_printf("\n\\begin_inset" INDENT_S "LatexCommand" INDENT_S "\\index{%s}\n\\end_inset\n\n",
									 s_tidx);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TORTF:
				s_entry = um_strdup_printf("{\\xe\\v %s}", Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				convert_tilde(Param[1]);
				del_internal_styles(Param[1]);
				replace_udo_quotes(Param[1]);
				strcpy(keyword, Param[1]);
				winspecials2ascii(keyword);
				s_entry = um_strdup_printf("{K{\\footnote K %s}}", keyword);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOSTG:
			case TOAMG:
				delete_all_divis(Param[1]);
				convert_tilde(Param[1]);
				del_internal_styles(Param[1]);
				replace_udo_quotes(Param[1]);
				if (iUdopass == PASS2 && bInsideDocument)
				{
					index2stg(Param[1]);
					voutlnf("@index \"%s\"", Param[1]);
				}
				ret = delete_once(s, Param[0]);
				break;

			case TOINF:
				if (iUdopass == PASS2 && bInsideDocument)
				{
					voutlnf("@cindex %s", Param[1]);
					add_idxlist_item(Param[1], "", "");
				}
				ret = delete_once(s, Param[0]);
				break;

			case TOHPH:
				s_entry = um_strdup_printf("<idx>%s<\\idx>", Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOASC:
				delete_all_divis(Param[1]);
				convert_tilde(Param[1]);
				replace_udo_quotes(Param[1]);
				if (iUdopass == PASS2)
					add_idxlist_item(Param[1], "", "");
				ret = delete_once(s, Param[0]);
				break;

			case TOHAH:
			case TOMHH:
				if (iUdopass == PASS2 && bInsideDocument)
					output_htmlhelp_index(1, Param[1], "", "");
				ret = delete_once(s, Param[0]);
				break;

			default:
				ret = delete_once(s, Param[0]);
				break;
			}
		}
	}

	if (!ret)
	{
		error_replace_param("!index");
		return FALSE;
	}

	return TRUE;
}





/*******************************************************************************
*
*  c_single_index():
*     ??? (description)
*
*  Notes:
*     Die Nummer des Pass wird geprueft, damit bei Formaten, die die
*     Indexbefehle direkt ausgeben, nicht am Anfang der Zieldatei die
*     gesamten Indizes landen.
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL c_single_index(char *s, const _BOOL inside_b4_macro)
{
	char s_tidx[1024];
	char *s_entry;
	char keyword[1024];
	_BOOL ret = TRUE;

	if (get_parameters(s, "idx", 1, 1) > 0)
	{
		strcpy(s_tidx, Param[1]);

		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(s_tidx, TRUE);
			}
			adjust_params_inside(Param[1]);
		}

		/* Set index in project file */
		if (bUseUPRfile)
			save_upr_entry_index(1, sCurrFileName, Param[1], uiCurrFileLine);

		if (no_index)
		{
			ret = replace_once(s, Param[0], Param[1]);
		} else
		{
			bCalledIndex = TRUE;
			switch (desttype)
			{
			case TOTEX:
			case TOPDL:
				auto_quote_texindex(s_tidx);
				s_entry = um_strdup_printf("%s\\index{%s}", Param[1], s_tidx);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOLYX:
				auto_quote_texindex(s_tidx);
				s_entry =
					um_strdup_printf("%s\n\\begin_inset" INDENT_S "LatexCommand" INDENT_S
									 "\\index{%s}\n\\end_inset\n\n", Param[1], s_tidx);
				ret = replace_once(s, Param[0], s_entry);
				free(s_entry);
				break;

			case TORTF:
				s_entry = um_strdup_printf("{\\xe\\v %s}%s", Param[1], Param[1]);
				ret = replace_once(s, Param[0], s_entry);
				free(s_entry);
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				convert_tilde(Param[1]);
				del_internal_styles(Param[1]);
				replace_udo_quotes(Param[1]);
				strcpy(keyword, Param[1]);
				winspecials2ascii(keyword);
				s_entry = um_strdup_printf("{K{\\footnote K %s}}%s", keyword, Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOSTG:
			case TOAMG:
				delete_all_divis(Param[1]);
				convert_tilde(Param[1]);
				del_internal_styles(Param[1]);
				replace_udo_quotes(Param[1]);
				if (iUdopass == PASS2 && bInsideDocument)
				{
					index2stg(Param[1]);
					voutlnf("@index \"%s\"", Param[1]);
				}
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOINF:
				if (iUdopass == PASS2 && bInsideDocument)
				{
					voutlnf("@cindex %s", Param[1]);
					add_idxlist_item(Param[1], "", "");
				}
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOHPH:
				s_entry = um_strdup_printf("<idx>%s<\\idx>%s", Param[1], Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOASC:
				delete_all_divis(Param[1]);
				convert_tilde(Param[1]);
				replace_udo_quotes(Param[1]);
				if (iUdopass == PASS2)
					add_idxlist_item(Param[1], "", "");
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOHAH:
			case TOMHH:
				if (iUdopass == PASS2 && bInsideDocument)
					output_htmlhelp_index(1, Param[1], "", "");
				ret = replace_once(s, Param[0], Param[1]);
				break;

			default:
				ret = replace_once(s, Param[0], Param[1]);
				break;
			}
		}
	}

	if (!ret)
	{
		error_replace_param("!idx");
		return FALSE;
	}

	return TRUE;
}





/*******************************************************************************
*
*  c_double_index():
*     ??? (description)
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL c_double_index(char *s, const _BOOL inside_b4_macro)
{
	char *s_entry;
	_BOOL ret = TRUE;

	if (get_parameters(s, "idx", 2, 2))
	{
		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(Param[2], TRUE);
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		/* Set index in project file */
		if (bUseUPRfile)
		{
			char *upr_entry;

			upr_entry = um_strdup_printf("%s:%s", Param[1], Param[2]);
			save_upr_entry_index(2, sCurrFileName, upr_entry, uiCurrFileLine);
			free(upr_entry);
		}

		if (no_index)
		{
			ret = replace_once(s, Param[0], Param[1]);
		} else
		{
			bCalledIndex = TRUE;

			switch (desttype)
			{
			case TOTEX:
			case TOPDL:
				auto_quote_texindex(Param[2]);
				s_entry = um_strdup_printf("%s\\index{%s}", Param[1], Param[2]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOLYX:
				auto_quote_texindex(Param[2]);
				s_entry =
					um_strdup_printf("%s\n\\begin_inset" INDENT_S "LatexCommand" INDENT_S
									 "\\index{%s}\n\\end_inset\n\n", Param[1], Param[2]);
				ret = replace_once(s, Param[0], s_entry);
				free(s_entry);
				break;

			case TORTF:
				s_entry = um_strdup_printf("{\\xe\\v %s}%s", Param[2], Param[1]);
				ret = replace_once(s, Param[0], s_entry);
				free(s_entry);
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				del_internal_styles(Param[1]);
				del_internal_styles(Param[2]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				winspecials2ascii(Param[2]);
				s_entry = um_strdup_printf("{K{\\footnote K %s}}%s", Param[2], Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOSTG:
			case TOAMG:
				delete_all_divis(Param[1]);
				delete_all_divis(Param[2]);
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				del_internal_styles(Param[1]);
				del_internal_styles(Param[2]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				if (iUdopass == PASS2 && bInsideDocument)
				{
					index2stg(Param[2]);
					voutlnf("@index \"%s\"", Param[2]);
				}
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOINF:
				if (iUdopass == PASS2 && bInsideDocument)
				{
					voutlnf("@cindex %s", Param[2]);
					add_idxlist_item(Param[2], "", "");
				}
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOHPH:
				s_entry = um_strdup_printf("<idx>%s<\\idx>%s", Param[2], Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOASC:
				delete_all_divis(Param[1]);
				delete_all_divis(Param[2]);
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				if (iUdopass == PASS2)
					add_idxlist_item(Param[2], "", "");
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOHAH:
			case TOMHH:
				if (iUdopass == PASS2 && bInsideDocument)
					output_htmlhelp_index(1, Param[2], "", "");
				ret = replace_once(s, Param[0], Param[1]);
				break;

			default:
				ret = replace_once(s, Param[0], Param[1]);
				break;
			}
		}
	}

	if (!ret)
	{
		error_replace_param("!idx");
		return FALSE;
	}

	return TRUE;
}





/*******************************************************************************
*
*  c_tripple_index():
*     ??? (description)
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL c_tripple_index(char *s, const _BOOL inside_b4_macro)
{
	char *s_entry;
	_BOOL ret = TRUE;

	if (get_parameters(s, "idx", 3, 3))
	{
		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(Param[2], TRUE);
				auto_quote_chars(Param[3], TRUE);
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
			adjust_params_inside(Param[3]);
		}

		/* Set index in project file */
		if (bUseUPRfile)
		{
			char *upr_entry;

			upr_entry = um_strdup_printf("%s:%s:%s", Param[1], Param[2], Param[3]);
			save_upr_entry_index(3, sCurrFileName, upr_entry, uiCurrFileLine);
			free(upr_entry);
		}

		if (no_index)
		{
			ret = replace_once(s, Param[0], Param[1]);
		} else
		{
			bCalledIndex = TRUE;

			switch (desttype)
			{
			case TOTEX:
			case TOPDL:
				auto_quote_texindex(Param[2]);
				auto_quote_texindex(Param[3]);
				if (use_mirrored_indices)
				{
					s_entry = um_strdup_printf("%s\\index{%s!%s}\\index{%s!%s}",
											   Param[1], Param[2], Param[3], Param[3], Param[2]);
				} else
				{
					s_entry = um_strdup_printf("%s\\index{%s!%s}", Param[1], Param[2], Param[3]);
				}
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOLYX:
				auto_quote_texindex(Param[2]);
				auto_quote_texindex(Param[3]);
				if (use_mirrored_indices)
					s_entry =
						um_strdup_printf("%s\n\\begin_inset" INDENT_S "LatexCommand" INDENT_S
										 "\\index{%s!%s}\n\\end_inset\n\n\\begin_inset" INDENT_S "LatexCommand" INDENT_S
										 "\\index{%s!%s}\n\\end_inset\n\n", Param[1], Param[2], Param[3], Param[3],
										 Param[2]);
				else
					s_entry =
						um_strdup_printf("%s\n\\begin_inset" INDENT_S "LatexCommand" INDENT_S
										 "\\index{%s!%s}\n\\end_inset\n\n", Param[1], Param[2], Param[3]);
				ret = replace_once(s, Param[0], s_entry);
				free(s_entry);
				break;

			case TORTF:
				if (use_mirrored_indices)
				{
					s_entry = um_strdup_printf("{\\xe\\v %s\\:%s}{\\xe\\v %s\\:%s}%s",
											   Param[2], Param[3], Param[3], Param[2], Param[1]);
				} else
				{
					s_entry = um_strdup_printf("{\\xe\\v %s\\:%s}%s", Param[2], Param[3], Param[1]);
				}
				ret = replace_once(s, Param[0], s_entry);
				free(s_entry);
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				convert_tilde(Param[3]);
				del_internal_styles(Param[1]);
				del_internal_styles(Param[2]);
				del_internal_styles(Param[3]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[3]);
				winspecials2ascii(Param[2]);
				winspecials2ascii(Param[3]);
				if (use_mirrored_indices)
				{
					s_entry = um_strdup_printf("{K{\\footnote K %s, %s}}{K{\\footnote K %s, %s}}%s",
											   Param[2], Param[3], Param[3], Param[2], Param[1]);
				} else
				{
					s_entry = um_strdup_printf("{K{\\footnote K %s, %s}}%s", Param[2], Param[3], Param[1]);
				}
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOSTG:
			case TOAMG:
				delete_all_divis(Param[1]);
				delete_all_divis(Param[2]);
				delete_all_divis(Param[3]);
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				convert_tilde(Param[3]);
				del_internal_styles(Param[1]);
				del_internal_styles(Param[2]);
				del_internal_styles(Param[3]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[3]);
				if (iUdopass == PASS2 && bInsideDocument)
				{
					index2stg(Param[2]);
					index2stg(Param[3]);
					voutlnf("@index \"%s, %s\"", Param[2], Param[3]);
					if (use_mirrored_indices)
						voutlnf("@index \"%s, %s\"", Param[3], Param[2]);
				}
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOINF:
				if (iUdopass == PASS2 && bInsideDocument)
				{
					voutlnf("@cindex %s, %s", Param[2], Param[3]);
					add_idxlist_item(Param[2], Param[3], "");
					if (use_mirrored_indices)
					{
						voutlnf("@cindex %s, %s", Param[3], Param[2]);
						add_idxlist_item(Param[3], Param[2], "");
					}
				}
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOHPH:
				s_entry = um_strdup_printf("<idx>%s, %s<\\idx>%s", Param[2], Param[3], Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOASC:
				delete_all_divis(Param[1]);
				delete_all_divis(Param[2]);
				delete_all_divis(Param[3]);
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				convert_tilde(Param[3]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[3]);
				if (iUdopass == PASS2)
				{
					add_idxlist_item(Param[2], Param[3], "");
					if (use_mirrored_indices)
						add_idxlist_item(Param[3], Param[2], "");
				}
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOHAH:
			case TOMHH:
				if (iUdopass == PASS2 && bInsideDocument)
					output_htmlhelp_index(2, Param[2], Param[3], "");
				ret = replace_once(s, Param[0], Param[1]);
				break;

			default:
				ret = replace_once(s, Param[0], Param[1]);
				break;
			}
		}
	}

	if (!ret)
	{
		error_replace_param("!idx");
		return FALSE;
	}

	return TRUE;
}





/*******************************************************************************
*
*  c_quadruple_index():
*     ??? (description)
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL c_quadruple_index(char *s, const _BOOL inside_b4_macro)
{
	char *s_entry;
	_BOOL ret = TRUE;

	if (get_parameters(s, "idx", 4, 4))
	{
		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[1], TRUE);
				auto_quote_chars(Param[2], TRUE);
				auto_quote_chars(Param[3], TRUE);
				auto_quote_chars(Param[4], TRUE);
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
			adjust_params_inside(Param[3]);
			adjust_params_inside(Param[4]);
		}

		/* Set index in project file */
		if (bUseUPRfile)
		{
			char *upr_entry;

			upr_entry = um_strdup_printf("%s:%s:%s:%s", Param[1], Param[2], Param[3], Param[4]);
			save_upr_entry_index(4, sCurrFileName, upr_entry, uiCurrFileLine);
			free(upr_entry);
		}

		if (no_index)
		{
			ret = replace_once(s, Param[0], Param[1]);
		} else
		{
			bCalledIndex = TRUE;

			switch (desttype)
			{
			case TOTEX:
			case TOPDL:
				auto_quote_texindex(Param[2]);
				auto_quote_texindex(Param[3]);
				auto_quote_texindex(Param[4]);
				s_entry = um_strdup_printf("%s\\index{%s!%s!%s}", Param[1], Param[2], Param[3], Param[4]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOLYX:
				auto_quote_texindex(Param[2]);
				auto_quote_texindex(Param[3]);
				auto_quote_texindex(Param[4]);
				s_entry =
					um_strdup_printf("%s\n\\begin_inset" INDENT_S "LatexCommand" INDENT_S
									 "\\index{%s!%s!%s}\n\\end_inset\n\n", Param[1], Param[2], Param[3], Param[4]);
				ret = replace_once(s, Param[0], s_entry);
				free(s_entry);
				break;

			case TORTF:
				s_entry = um_strdup_printf("{\\xe\\v %s\\:%s\\:%s}%s", Param[2], Param[3], Param[4], Param[1]);
				ret = replace_once(s, Param[0], s_entry);
				free(s_entry);
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				convert_tilde(Param[3]);
				convert_tilde(Param[4]);
				del_internal_styles(Param[1]);
				del_internal_styles(Param[2]);
				del_internal_styles(Param[3]);
				del_internal_styles(Param[4]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[3]);
				replace_udo_quotes(Param[4]);
				winspecials2ascii(Param[2]);
				winspecials2ascii(Param[3]);
				winspecials2ascii(Param[4]);

				s_entry = um_strdup_printf("{K{\\footnote K %s, %s, %s}}%s", Param[2], Param[3], Param[4], Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOSTG:
			case TOAMG:
				delete_all_divis(Param[1]);
				delete_all_divis(Param[2]);
				delete_all_divis(Param[3]);
				delete_all_divis(Param[4]);
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				convert_tilde(Param[3]);
				convert_tilde(Param[4]);
				del_internal_styles(Param[1]);
				del_internal_styles(Param[2]);
				del_internal_styles(Param[3]);
				del_internal_styles(Param[4]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[3]);
				replace_udo_quotes(Param[4]);

				if (iUdopass == PASS2 && bInsideDocument)
				{
					index2stg(Param[2]);
					index2stg(Param[3]);
					index2stg(Param[4]);
					voutlnf("@index \"%s, %s, %s\"", Param[2], Param[3], Param[4]);
				}
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOINF:
				if (iUdopass == PASS2 && bInsideDocument)
				{
					voutlnf("@cindex %s, %s, %s", Param[2], Param[3], Param[4]);
					add_idxlist_item(Param[2], Param[3], Param[4]);
				}
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOHPH:
				s_entry = um_strdup_printf("<idx>%s, %s, %s<\\idx>%s", Param[2], Param[3], Param[4], Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, s_entry))
				{
					ret = FALSE;
					replace_once(s, Param[0], s_entry);
				}
				free(s_entry);
				break;

			case TOASC:
				delete_all_divis(Param[1]);
				delete_all_divis(Param[2]);
				delete_all_divis(Param[3]);
				delete_all_divis(Param[4]);
				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				convert_tilde(Param[3]);
				convert_tilde(Param[4]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[3]);
				replace_udo_quotes(Param[4]);
				if (iUdopass == PASS2)
					add_idxlist_item(Param[2], Param[3], Param[4]);
				ret = replace_once(s, Param[0], Param[1]);
				break;

			case TOHAH:
			case TOMHH:
				if (iUdopass == PASS2 && bInsideDocument)
					output_htmlhelp_index(3, Param[2], Param[3], Param[4]);
				ret = replace_once(s, Param[0], Param[1]);
				break;

			default:
				ret = replace_once(s, Param[0], Param[1]);
				break;
			}
		}
	}

	if (!ret)
	{
		error_replace_param("!idx");
		return FALSE;
	}

	return TRUE;
}





/*******************************************************************************
*
*  c_internal_time():
*     convert a time command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_internal_time(char *s, const _BOOL inside_b4_macro)
{
	char str[1024];
	_BOOL flag;
	time_t uhrzeit;
	struct tm *timeptr;

	flag = FALSE;
	while (!flag && (get_parameters(s, "time", 1, 1) == 1))
	{
		if (inside_b4_macro)
			adjust_params_inside(Param[1]);

		time(&uhrzeit);
		timeptr = localtime(&uhrzeit);

		if (strlen(&Param[1][0]) > 1000)
			strcpy(str, "time parameter too long");
		else
			strftime(str, sizeof(str), Param[1], timeptr);

		flag = !insert_placeholder(s, Param[0], str, Param[1]);
	}

	if (flag)
	{
		replace_once(s, Param[0], Param[1]);
		error_replace_param("!time");
	}
}





/*******************************************************************************
*
*  c_internal_image():
*     convert an img command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_internal_image(char *s, const _BOOL inside_b4_macro)
{
	int pnr = 0;
	char *s_entry;
	char sGifSize[80];
	char sGifName[512];
	_BOOL flag;
	_UWORD uiW, uiH, bitcnt;

	flag = FALSE;
	while (!flag && (pnr = get_parameters(s, "img", 2, 3)) >= 2)
	{
		if (inside_b4_macro)
		{
			if (desttype != TOSTG)
			{
				auto_quote_chars(Param[2], TRUE);
				auto_quote_chars(Param[3], TRUE);
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
			adjust_params_inside(Param[3]);
		}

		fsplit(Param[1], tmp_driv, tmp_path, tmp_name, tmp_suff);

		replace_udo_quotes(Param[2]);
		replace_udo_quotes(Param[3]);

		switch (desttype)
		{
		case TOHAH:
		case TOHTM:
		case TOMHH:
			strcpy(tmp_suff, sDocImgSuffix);
			sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
			path_adjust_separator(Param[1]);
			sGifSize[0] = EOS;
			strcpy(sGifName, Param[1]);
			get_picture_size(sGifName, NULL, &uiW, &uiH, &bitcnt);
			if (uiW != 0 && uiH != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}

			replace_char(Param[1], '\\', '/');
			if (no_images)
			{
				s_entry = strdup(Param[2]);
			} else
			{
				char border[20];

				strcpy(border, " border=\"0\"");
#if 0
				if (html_doctype == HTML5)
					*border = EOS;
#endif
				if (Param[3][0] == EOS)
					strcpy(Param[3], Param[2]);
				s_entry = um_strdup_printf("<img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s>",
										   Param[1], Param[2], Param[3], border, sGifSize, xhtml_closer);
			}
			flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
			free(s_entry);
			break;

		case TOHPH:
			strcpy(tmp_suff, sDocImgSuffix);
			sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
			replace_char(Param[1], '\\', '/');
			if (no_images)
			{
				s_entry = strdup(Param[2]);
			} else
			{
				s_entry = um_strdup_printf("<graphic>%s<\\graphic>", Param[1]);
			}
			flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
			free(s_entry);
			break;

		case TOWIN:
		case TOWH4:
		case TOAQV:
			strcpy(tmp_suff, ".bmp");
			sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
			replace_char(Param[1], '\\', '/');
			if (no_images)
			{
				s_entry = strdup(Param[2]);
			} else
			{
				s_entry = um_strdup_printf(" \\{bmc %s\\}", Param[1]);
			}
			flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
			free(s_entry);
			break;

		case TOIPF:
			strcpy(tmp_suff, ".bmp");
			sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
			if (no_images)
			{
				s_entry = strdup(Param[2]);
			} else
			{
				s_entry = um_strdup_printf("\n:artwork runin name='%s'.\n", Param[1]);
			}
			flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
			free(s_entry);
			break;

		case TORTF:
			flag = !insert_placeholder(s, Param[0], "", Param[2]);
			break;

		case TOKPS:
			s_entry = strdup(Param[2]);
			replace_all(s_entry, KPSPC_S, ")");
			replace_all(s_entry, KPSPO_S, "(");
			flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
			free(s_entry);
			break;

		default:
			flag = !insert_placeholder(s, Param[0], Param[2], Param[2]);
			break;
		}
	}

	if (flag)
	{
		replace_once(s, Param[0], Param[2]);
		error_replace_param("!img");
	}

	if (pnr != 0 && pnr < 2)
		error_wrong_nr_parameters("!img");
}





/*******************************************************************************
*
*  c_single_raw():
*     convert a raw command into its target format
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL c_single_raw(char *s, const _BOOL inside_b4_macro)
{
	_BOOL flag;

	UNUSED(inside_b4_macro);
	if (get_parameters(s, "raw", 1, 1))
	{
		flag = insert_placeholder(s, Param[0], Param[1], Param[1]);

		if (!flag)
		{
			replace_once(s, Param[0], Param[1]);
			error_replace_param("!raw");
			return FALSE;
		}

	}

	return TRUE;
}





/*******************************************************************************
*
*  c_double_raw():
*     convert a raw command into its target format
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL c_double_raw(char *s, const _BOOL inside_b4_macro)
{
	_BOOL flag;

	UNUSED(inside_b4_macro);
	if (get_parameters(s, "raw", 2, 2))
	{
		if (str_for_desttype(Param[1], TRUE) > 0)
		{
			flag = insert_placeholder(s, Param[0], Param[2], Param[2]);
			if (!flag)
			{
				delete_once(s, Param[0]);
				error_replace_param("!raw");
				return FALSE;
			}
		} else
		{
			delete_once(s, Param[0]);
		}
	}

	return TRUE;
}





/*******************************************************************************
*
*  c_internal_raw():
*     handle conversion of raw commands
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_internal_raw(char *s, const _BOOL inside_b4_macro)
{
	int nr;
	_BOOL flag;

	if (strstr(s, "(!raw") == NULL)
		return;

	do
	{
		nr = get_nr_of_parameters("raw", s);

		switch (nr)
		{
		case 0:
			flag = FALSE;
			break;
		case 1:
			flag = c_single_raw(s, inside_b4_macro);
			break;
		case 2:
			flag = c_double_raw(s, inside_b4_macro);
			break;
		default:
			error_wrong_nr_parameters("!raw");
			flag = FALSE;
			break;
		}
	} while (flag);
}





/*******************************************************************************
*
*  md_uses_parameters():
*     check if macro or definition uses parameters
*
*  Return:
*     FALSE: doesn't use parameters
*     TRUE : uses parametes
*
******************************************|************************************/

LOCAL _BOOL md_uses_parameters(const char *s)
{
	if (strstr(s, "(!0)") != NULL)
		return TRUE;

	if (strstr(s, "(!1)") != NULL)
		return TRUE;

	if (strstr(s, "(!2)") != NULL)
		return TRUE;

	if (strstr(s, "(!3)") != NULL)
		return TRUE;

	if (strstr(s, "(!4)") != NULL)
		return TRUE;

	if (strstr(s, "(!5)") != NULL)
		return TRUE;

	if (strstr(s, "(!6)") != NULL)
		return TRUE;

	if (strstr(s, "(!7)") != NULL)
		return TRUE;

	if (strstr(s, "(!8)") != NULL)
		return TRUE;

	if (strstr(s, "(!9)") != NULL)
		return TRUE;

	return FALSE;
}










/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  replace_variables():
*     adjust macros and definitions which contain variables
*
*  Example:
*     !macro Maus (!1) (!2) @ (!3), (!1)_(!2)@(!3).maus.de
*     MausNet:   (!Maus [Dirk] [Hagedorn] [MK2])
*
*     cmd   = Maus
*     entry = (!1) (!2) @ (!3), (!1)_(!2)@(!3).maus.de
*     s     = string with macro
*
*     -->
*     MausNet: Dirk Hagedorn @ MK2, Dirk_Hagedorn@MK2.maus.de
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void replace_variables(char *s, const char *cmd, const char *entry)
{
	int parms, i;
	char p[16];
	char without[128];
	char *ptr;
	_BOOL flag;

	/* (!macro) vorher loeschen */
	sprintf(without, "(!%s)", cmd);
	delete_all(s, without);

	flag = TRUE;
	while (flag && (parms = get_nr_of_parameters(cmd, s)) > 0)
	{
		if (parms > MAX_PARAMETERS)
		{
			error_message(_("too many parameters used"));
			return;
		}

		get_parameters(s, cmd, parms, parms);

		ptr = strstr(s, Param[0]);

		if (replace_all(ptr, Param[0], entry))
		{
			qdelete_all(ptr, "(!0)", 4);
			for (i = 0; i < MAX_PARAMETERS; i++)
			{
				sprintf(p, "(!%d)", i + 1);
				if (parms > i)
				{
					auto_quote_chars(Param[i + 1], TRUE);
					replace_all(ptr, p, Param[i + 1]);
				} else
				{
					qdelete_all(ptr, p, 4);
				}
			}
		} else
		{
			flag = FALSE;
		}
	}

	if (!flag)
	{
		sprintf(without, "!%s", cmd);
		error_replace_param(without);
	}
}





/*******************************************************************************
*
*  reset_speccmds():
*     remove special format command placeholders from the text
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void reset_speccmds(void)
{
	size_t i;

	for (i = 0; i < speccmd_counter; i++)
	{
		if (speccmd[i].entry != NULL)
		{
			free(speccmd[i].entry);
			speccmd[i].entry = NULL;
		}
		speccmd[i].magic[0] = EOS;
	}

	speccmd_counter = 0;
}





/*******************************************************************************
*
*  add_speccmd():
*     insert special format commands into the text as placeholders
*
*  Notes:
*     These format commands don't contain visible text!
*
*  Return:
*      TRUE: ???
*     FALSE: failure
*
******************************************|************************************/

GLOBAL _BOOL add_speccmd(const char *entry)
{
	char *ptr;
	size_t counter;
	unsigned char c1, c2, c3;
	SPECCMD *new_speccmd;

	counter = speccmd_counter;
	if (counter >= MAXSPECCMDS)
		return FALSE;

	/*
	 * when encoding, be sure not to generate
	 * \033, '~' or \177 characters,
	 * or any sequence of characters that
	 * might me interpreted as an UDO command
	 */
	c1 = encode_chars[((counter >> 12) & 0x3f)];
	c2 = encode_chars[((counter >> 6) & 0x3f)];
	c3 = encode_chars[((counter) & 0x3f)];

	if (counter >= speccmd_alloc)
	{
		size_t new_alloc = speccmd_alloc + 100;

		new_speccmd = (SPECCMD *) realloc(speccmd, new_alloc * sizeof(SPECCMD));
		if (new_speccmd == NULL)
		{
			return FALSE;
		}
		speccmd = new_speccmd;
		speccmd_alloc = new_alloc;
	}
	ptr = strdup(entry);
	if (ptr == NULL)
	{
		return FALSE;
	}

	sprintf(speccmd[counter].magic, "\033%c%c%c%c\033", C_SPECCMD_MAGIC, c1, c2, c3);

	speccmd[counter].entry = ptr;

	speccmd_counter++;

	return TRUE;
}





/*******************************************************************************
*
*  insert_speccmd():
*     insert special format command placeholders into the text
*
*  Notes:
*     These format commands don't contain visible text!
*
*  Return:
*      TRUE: ???
*     FALSE: failure
*
******************************************|************************************/

GLOBAL _BOOL insert_speccmd(char *s, const char *rep, const char *entry)
{
	if (add_speccmd(entry))
	{
		if (replace_once(s, rep, speccmd[speccmd_counter - 1].magic))
			return TRUE;
	}
	return FALSE;
}





/*******************************************************************************
*
*  replace_speccmds():
*     replace special format command placeholders in the text
*
*  Notes:
*     These format commands don't contain visible text!
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_speccmds(char *s)
{
	register size_t i;
	size_t replaced;

	if (speccmd_counter > 0)
	{
		if (strstr(s, ESC_SPECCMD_MAGIC) == NULL)
			return;

		replaced = 0;
		/* Rueckwaerts ersetzen, da ein Platzhalter auch in */
		/* einem Platzhalter stecken kann! */
		for (i = speccmd_counter; i > 0;)
		{
			--i;
			if (replace_once(s, speccmd[i].magic, speccmd[i].entry))
			{
				speccmd[i].magic[0] = EOS;
				replaced++;
			}
		}
		if (replaced == speccmd_counter)
			reset_speccmds();
	}
}





/*******************************************************************************
*
*  reset_placeholders():
*     handle links and other internal commands
*
*  Notes:
*     This has to be done BEFORE the tokenization takes place!
*
*  Format:
*     (!link [text] [destination])
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void reset_placeholders(void)
{
	size_t i;

	for (i = 0; i < phold_counter; i++)
	{
#if 0
		/* fuer debug-zwecke: */
		if (phold[i].magic[0] != EOS)
		{
			char s[1024];

			_UWORD c1,
			 c2,
			 c3;

			_UWORD j;

			c1 = decode_chars[phold[i].magic[2]];
			c2 = decode_chars[phold[i].magic[3]];
			c3 = decode_chars[phold[i].magic[4]];
			j = (((c1 << 6) + c2) << 6) + c3;
			warning_message(_("not replaced %3lu:%3lu: %c%c%c %s %s\n"), i, j, phold[i].magic[2], phold[i].magic[3],
							phold[i].magic[4], phold[i].entry, phold[i].text);
		}
#endif
		if (phold[i].entry != NULL)
		{
			free(phold[i].entry);
			phold[i].entry = NULL;
		}

		if (phold[i].text != NULL)
		{
			free(phold[i].text);
			phold[i].text = NULL;
		}
	}
	phold_counter = 0;
}





/*******************************************************************************
*
*  add_placeholder():
*     ??? (description missing)
*
*  Return:
*      TRUE: everything's fine
*     FALSE: error
*
******************************************|************************************/

GLOBAL _BOOL add_placeholder(const char *entry, const char *rawtext)
{
	char *eptr, *tptr;
	unsigned char c1, c2, c3;
	size_t counter;
	PLACEHOLDER *new_phold;
	PLACEHOLDER *p;

	counter = phold_counter;
	if (counter >= MAXPHOLDS)
		return FALSE;
	/*
	 * when encoding, be sure not to generate
	 * \033, '~' or \177 characters,
	 * or any sequence of characters that
	 * might be interpreted as an UDO command
	 */
	c1 = encode_chars[((counter >> 12) & 0x3f)];
	c2 = encode_chars[((counter >> 6) & 0x3f)];
	c3 = encode_chars[((counter) & 0x3f)];
	if (counter >= phold_alloc)
	{
		size_t new_alloc = phold_alloc + 100;

		new_phold = (PLACEHOLDER *) realloc(phold, new_alloc * sizeof(PLACEHOLDER));
		if (new_phold == NULL)
		{
			return FALSE;
		}
		phold = new_phold;
		phold_alloc = new_alloc;
	}
	eptr = strdup(entry);
	if (eptr == NULL)
	{
		return FALSE;
	}

	tptr = strdup(rawtext);
	if (tptr == NULL)
	{
		free(eptr);
		return FALSE;
	}

	p = &phold[counter];
	p->magic[0] = '\033';
	p->magic[1] = C_PHOLD_MAGIC;
	p->magic[2] = c1;
	p->magic[3] = c2;
	p->magic[4] = c3;
	p->magic[5] = '\033';
	p->magic[6] = '\0';

	p->entry = eptr;
	p->text = tptr;

	phold_counter++;
	return TRUE;
}





/*******************************************************************************
*
*  insert_placeholder():
*     replace text for inline commands
*
*  @s: the string to replace in
*  @rep: the complete to command to replace
*  @entry: the format specific command to be inserted later
*  @text: the visible text that results from the command
*
*  Return:
*      TRUE: everything's fine
*     FALSE: error
*
******************************************|************************************/

GLOBAL _BOOL insert_placeholder(char *s, const char *rep, const char *entry, const char *rawtext)
{
	if (add_placeholder(entry, rawtext))
	{
		if (replace_once(s, rep, phold[phold_counter - 1].magic))
			return TRUE;
	}

	return FALSE;
}





/*******************************************************************************
*
*  replace_placeholders():
*     replace the internal placeholder commands by human-readable content
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_placeholders(char *s)
{
	register size_t i;
	size_t replaced = 0;

	if (phold_counter > 0)
	{
		if (strstr(s, ESC_PHOLD_MAGIC) == NULL)
			return;

		/* Rueckwaerts ersetzen, da ein Platzhalter auch in */
		/* einem Platzhalter stecken kann! */
		for (i = phold_counter; i > 0;)
		{
			--i;
			if (replace_once(s, phold[i].magic, phold[i].entry))
			{
				phold[i].magic[0] = EOS;
				replaced++;
			}
		}
		if (replaced == phold_counter)
			reset_placeholders();
	}
}





/*******************************************************************************
*
*  replace_placeholders_text():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_placeholders_text(char *s)
{
	register size_t i;

	if (phold_counter > 0)
	{
		if (strstr(s, ESC_PHOLD_MAGIC) == NULL)
			return;

		for (i = 0; i < phold_counter; i++)
			replace_once(s, phold[i].magic, phold[i].text);
	}
}





/*******************************************************************************
*
*  pholdlen():
*     return length of placeholder text
*
*  return:
*     length of placeholder text
*     0
*
******************************************|************************************/

GLOBAL size_t pholdlen(const char *ptr)
{
	size_t c1, c2, c3;
	size_t i;

	c1 = decode_chars[(unsigned char) ptr[0]];
	c2 = decode_chars[(unsigned char) ptr[1]];
	c3 = decode_chars[(unsigned char) ptr[2]];
	i = (((c1 << 6) + c2) << 6) + c3;

	if (i < phold_counter)
	{
		if (phold[i].text != NULL)
		{
			return strlen(phold[i].text);
		}
	}

	return 0;
}





/*******************************************************************************
*
*  c_internal_index():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_internal_index(char *s, const _BOOL inside_b4_macro)
{
	int nr;
	_BOOL flag;
	_BOOL has_idx, has_index;

	has_idx = strstr(s, "(!idx") != NULL;
	has_index = strstr(s, "(!index") != NULL;

	if (has_idx)
	{
		do
		{
			nr = get_nr_of_parameters(CMD_IDX, s);
			switch (nr)
			{
			case 0:
				flag = FALSE;
				break;
			case 1:
				flag = c_single_index(s, inside_b4_macro);
				break;
			case 2:
				flag = c_double_index(s, inside_b4_macro);
				break;
			case 3:
				flag = c_tripple_index(s, inside_b4_macro);
				break;
			case 4:
				flag = c_quadruple_index(s, inside_b4_macro);
				break;
			default:
				error_wrong_nr_parameters("!idx");
				flag = FALSE;
				break;
			}
		} while (flag == TRUE);
	}

	if (has_index)
	{
		do
		{
			nr = get_nr_of_parameters("index", s);
			switch (nr)
			{
			case 0:
				flag = FALSE;
				break;
			case 1:
				flag = c_index(s, inside_b4_macro);
				break;
			default:
				error_wrong_nr_parameters("!index");
				flag = FALSE;
				break;
			}
		} while (flag == TRUE);
	}
}


/*******************************************************************************
*
*  c_commands_inside():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_commands_inside(char *s, const _BOOL inside_b4_macro)
{
	if (strstr(s, "(!") == NULL)
		return;

	c_link(s, inside_b4_macro);
	c_url(s, inside_b4_macro);
	c_xlink(s, inside_b4_macro);
	c_ilink(s, inside_b4_macro);
	c_plink(s, inside_b4_macro);
	c_plabel(s, inside_b4_macro);
	c_nolink(s, inside_b4_macro);
	c_comment(s, inside_b4_macro);
	c_internal_index(s, inside_b4_macro);
	c_internal_time(s, inside_b4_macro);
	c_internal_image(s, inside_b4_macro);
	c_internal_raw(s, inside_b4_macro);
	if (!inside_b4_macro && (s[0] != META_C || s[1] == QUOTE_C))
		c_footnotes(s);
}





/*******************************************************************************
*
*  replace_hyphens():
*     replace word with hyphenated word in document
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_hyphens(char *s)
{
	size_t h;							/* hyphen index */

	for (h = 0; h < hyphen_counter; h++)
	{
		if (hyphen[h] != NULL)
		{
			replace_all(s, hyphen[h]->solo, hyphen[h]->hyphen);
		}
	}
}





/*******************************************************************************
*
*  add_hyphen():
*     add hyphen to list of hyphens
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void add_hyphen(void)
{
	HYPHEN *p;
	HYPHEN **new_hyphen;

	if (token_counter <= 1)
	{
		error_missing_parameter("!hyphen");
		return;
	}

	switch (desttype)
	{
	case TOWIN:
	case TOWH4:
	case TOAQV:
	case TORTF:
	case TOHAH:
	case TOHTM:
	case TOMHH:
		return;							/* these formats don't support hyphenation rules (yet) */
	}

	if (hyphen_counter >= hyphen_alloc)
	{
		size_t new_alloc = hyphen_alloc + 100;

		new_hyphen = (HYPHEN **) realloc(hyphen, new_alloc * sizeof(HYPHEN *));
		if (new_hyphen == NULL)
		{
			return;
		}
		hyphen = new_hyphen;
		hyphen_alloc = new_alloc;
	}

	p = (HYPHEN *) malloc(sizeof(HYPHEN));
	if (p == NULL)						/* no free memory? */
	{
		return;
	}

	tokcpy2(p->hyphen, HYPHEN_LEN + 1);	/* copy   hyphenated word */
	tokcpy2(p->solo, HYPHEN_LEN + 1);	/* buffer hyphenated word */

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		/* Die Tokens sind leider vorher schon durch c_vars gelaufen */
		/* Dabei wurden auch (!ck) usw. bereits in "ck umgewandelt */
		/* Problem: replace_hyphens() findet Dru"cker dann nicht */
		qdelete_all(p->solo, "\\-", 2);
		break;

	default:
		delete_all_divis(p->solo);
		break;
	}

	hyphen[hyphen_counter] = p;
	hyphen_counter++;
}





/*******************************************************************************
*
*  sort_hyphens():
*     sort list of hyphens, such that longer matches get replaced first
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL int hyphen_compare(const void *_p, const void *_q)
{
	const HYPHEN *p = *((const HYPHEN * const *) _p);
	const HYPHEN *q = *((const HYPHEN * const *) _q);
	size_t l1, l2;

	l1 = strlen(p->hyphen);
	l2 = strlen(q->hyphen);
	if (l1 < l2)
		return 1;
	if (l1 > l2)
		return -1;
	return strcmp(p->hyphen, q->hyphen);
}


void sort_hyphens(void)
{
	if (hyphen_counter > 1)
		qsort(hyphen, hyphen_counter, sizeof(HYPHEN *), hyphen_compare);
}


/*******************************************************************************
*
*  replace_macros():
*     replace macro (!%s) with macro content in document
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_macros(char *s)
{
	_UWORD i;

	if (strstr(s, "(!") == NULL)
		return;

	for (i = 0; i < macro_counter; i++)
	{
		if (macros[i] != NULL)			/* valid macro */
		{
			if (macros[i]->vars)		/* replace by macro content with parameters */
				replace_variables(s, macros[i]->name, macros[i]->entry);
			else						/* replace by macro content */
				replace_all(s, macros[i]->name, macros[i]->entry);
		}
	}
}



LOCAL _BOOL check_macro_name(const char *name)
{
	while (*name != EOS)
	{
		if (strchr(macro_allowed_name, *name) == NULL)
		{
			error_message(_("%x not allowed in macro name"), (unsigned char) (*name));
			return FALSE;
		}
		name++;
	}
	return TRUE;
}


GLOBAL _BOOL is_internal_name(const char *name)
{
	if (strcmp(name, "V") == 0 ||
		strcmp(name, "v") == 0 ||
		strcmp(name, "U") == 0 ||
		strcmp(name, "u") == 0 ||
		strcmp(name, "I") == 0 ||
		strcmp(name, "i") == 0 ||
		strcmp(name, "T") == 0 ||
		strcmp(name, "t") == 0 ||
		strcmp(name, "B") == 0 ||
		strcmp(name, "b") == 0 ||
		strcmp(name, "N") == 0 ||
		strcmp(name, "n") == 0 ||
		strcmp(name, "G") == 0 ||
		strcmp(name, "g") == 0 ||
		strcmp(name, "S") == 0 ||
		strcmp(name, "s") == 0 ||
		strcmp(name, "O") == 0 ||
		strcmp(name, "o") == 0 ||
		strcmp(name, "SUB") == 0 ||
		strcmp(name, "sub") == 0 ||
		strcmp(name, "SUP") == 0 ||
		strcmp(name, "sup") == 0 ||
		strcmp(name, "DEL") == 0 ||
		strcmp(name, "del") == 0 ||
		strcmp(name, "INS") == 0 ||
		strcmp(name, "ins") == 0 ||
		strcmp(name, "link") == 0 ||
		strcmp(name, "url") == 0 ||
		strcmp(name, "plink") == 0 ||
		strcmp(name, "xlink") == 0 ||
		strcmp(name, "ilink") == 0 ||
		strcmp(name, "label") == 0 ||
		strcmp(name, "nolink") == 0 ||
		strcmp(name, "comment") == 0 ||
		strcmp(name, "idx") == 0 ||
		strcmp(name, "index") == 0 ||
		strcmp(name, "time") == 0 ||
		strcmp(name, "today") == 0 ||
		strcmp(name, "short_today") == 0 ||
		strcmp(name, "image") == 0 ||
		strcmp(name, "img") == 0 ||
		strcmp(name, "raw") == 0 ||
		strcmp(name, "nl") == 0 ||
		strcmp(name, "registered") == 0 ||
		strcmp(name, "copyright") == 0 ||
		strcmp(name, "tm") == 0 ||
		strcmp(name, "reg") == 0 ||
		strcmp(name, "deg") == 0 ||
		strcmp(name, "pound") == 0 ||
		strcmp(name, "alpha") == 0 ||
		strcmp(name, "beta") == 0 ||
		strcmp(name, "euro") == 0 ||
		strcmp(name, "grin") == 0 ||
		strcmp(name, "LaTeX") == 0 ||
		strcmp(name, "LaTeXe") == 0 ||
		strcmp(name, "TeX") == 0 ||
		strcmp(name, "aqua") == 0 ||
		strcmp(name, "black") == 0 ||
		strcmp(name, "blue") == 0 ||
		strcmp(name, "coloff") == 0 ||
		strcmp(name, "fuchsia") == 0 ||
		strcmp(name, "gray") == 0 ||
		strcmp(name, "green") == 0 ||
		strcmp(name, "lime") == 0 ||
		strcmp(name, "maroon") == 0 ||
		strcmp(name, "navy") == 0 ||
		strcmp(name, "olive") == 0 ||
		strcmp(name, "purple") == 0 ||
		strcmp(name, "red") == 0 ||
		strcmp(name, "silver") == 0 ||
		strcmp(name, "teal") == 0 ||
		strcmp(name, "white") == 0 ||
		strcmp(name, "yellow") == 0 ||
		strcmp(name, "laugh") == 0)
		return TRUE;
	return FALSE;
}


/*******************************************************************************
*
*  add_macro():
*     add macro to list of macros
*  Notes:
*     The "!macro ..." data which are handled here can be found in token[].
*
*  Return:
*     FALSE: error
*     TRUE : macro has been added successfully
*
******************************************|************************************/

GLOBAL _BOOL add_macro(void)
{
	int i;
	MACROS *p;
	char *entry;
	MACROS **new_macros;
	size_t name_len;
	size_t entry_len;

	if (token_counter <= 1)				/* only "!macro" in the line? */
	{
		error_missing_parameter(CMD_MACRO);
		return FALSE;
	}

	name_len = strlen(token[1]) + 1;
	if (name_len > MACRO_NAME_LEN)		/* macro name too long? */
	{
		error_message(_("macro name longer than %d characters"), MACRO_NAME_LEN);
		return FALSE;
	}
	if (!check_macro_name(token[1]))
		return FALSE;
	if (is_internal_name(token[1]))
		warning_message(_("redefining internal command (!%s)"), token[1]);

	if (macro_counter >= macros_alloc)
	{
		size_t new_alloc = macros_alloc + 100;

		new_macros = (MACROS **) realloc(macros, new_alloc * sizeof(MACROS *));
		if (new_macros == NULL)
		{
			return FALSE;
		}
		macros = new_macros;
		macros_alloc = new_alloc;
	}

	entry_len = 0;
	for (i = 2; i < token_counter; i++)
	{
		entry_len += strlen(token[i]);
		if (i < token_counter - 1)
		{
			entry_len += 1;
		}
	}
	if (entry_len > MACRO_CONT_LEN)		/* macro content too long? */
	{
		error_message(_("macro contents longer than %d characters"), MACRO_CONT_LEN);
		return FALSE;
	}

	entry_len = MACRO_CONT_LEN;
	entry = (char *) malloc((entry_len + 1) * sizeof(*entry));
	if (entry == NULL)
	{
		return FALSE;
	}

	entry[0] = EOS;
	for (i = 2; i < token_counter; i++)
	{
		strcat(entry, token[i]);
		if (i < (token_counter - 1))
		{
			strcat(entry, " ");
		}
	}

	/*
	 * FIXME: die folgenden routinen koennen immer
	 * noch einen buffer overrun verursachen
	 */
	auto_quote_chars(entry, FALSE);
	replace_macros(entry);				/* macros may use macros - resolve them here */
	replace_defines(entry);				/* macros may use defines - resolve them here */

	c_divis(entry);
	c_vars(entry);

	entry_len = strlen(entry);
	entry = (char *) realloc(entry, (entry_len + 1) * sizeof(*entry));

	/* create space for a macro */
	p = (MACROS *) malloc(sizeof(MACROS));
	if (p == NULL)						/* no free memory! */
	{
		return FALSE;
	}

	/* copy collected content to structure */
	p->entry = entry;

	/* copy name to structure */
	p->name = (char *) malloc((name_len + 4) * sizeof(*p->name));
	if (p->name == NULL)
	{
		free(p->entry);
		free(p);
		return FALSE;
	}

	if (md_uses_parameters(p->entry))	/* macro uses parameters */
	{
		strcpy(p->name, token[1]);
		p->vars = TRUE;
	} else								/* normal macro */
	{
		sprintf(p->name, "(!%s)", token[1]);
		token[1][0] = EOS;
		p->vars = FALSE;
	}

	macros[macro_counter] = p;
	macro_counter++;

	return TRUE;
}





/*******************************************************************************
*
*  replace_defines():
*     replace definition (!%s) with definition content in document
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_defines(char *s)
{
	_UWORD i;

	if (strstr(s, "(!") == NULL)
		return;

	for (i = 0; i < define_counter; i++)
	{
		if (defs[i] != NULL)			/* valid definition */
		{
			if (defs[i]->vars)			/* replace by content with parameters */
				replace_variables(s, defs[i]->name, defs[i]->entry);
			else						/* replace by content */
				replace_all(s, defs[i]->name, defs[i]->entry);
		}
	}
}





/*******************************************************************************
*
*  add_define():
*     add definition to list of definitions
*
*  Notes:
*     The "!define ..." data which are handled here can be found in token[].
*
*  Return:
*     FALSE: error
*     TRUE : definition has been added successfully
*
******************************************|************************************/

GLOBAL _BOOL add_define(void)
{
	int i;
	DEFS *p;
	char *entry;
	size_t entry_len;
	size_t name_len;
	DEFS **new_defs;

	if (token_counter <= 1)				/* only "!define" in the line? */
	{
		error_missing_parameter(CMD_DEFINE);
		return FALSE;
	}

	name_len = strlen(token[1]) + 1;
	if (name_len > DEFINE_NAME_LEN)
	{
		error_message(_("definition name longer than %d characters"), DEFINE_NAME_LEN);
		return FALSE;
	}
	if (!check_macro_name(token[1]))
		return FALSE;
	if (is_internal_name(token[1]))
		warning_message(_("redefining internal command (!%s)"), token[1]);

	if (define_counter >= defs_alloc)
	{
		size_t new_alloc = defs_alloc + 100;

		new_defs = (DEFS **) realloc(defs, new_alloc * sizeof(DEFS *));
		if (new_defs == NULL)
		{
			return FALSE;
		}
		defs = new_defs;
		defs_alloc = new_alloc;
	}

	entry_len = 0;
	for (i = 2; i < token_counter; i++)
	{
		entry_len += strlen(token[i]);
		if (i < token_counter - 1)
		{
			entry_len += 1;
		}
	}

	/* muss leider erstmal drin bleiben, da
	 * sonst lokale buffer ueberschrieben werden */
	if (entry_len > DEFINE_CONT_LEN)
	{
		error_message(_("definition contents longer than %d characters"), DEFINE_CONT_LEN);
		return FALSE;
	}

	entry = (char *) malloc((entry_len + 1) * sizeof(*entry));
	if (entry == NULL)
	{
		return FALSE;
	}

	entry[0] = EOS;
	for (i = 2; i < token_counter; i++)
	{
		strcat(entry, token[i]);
		if (i < (token_counter - 1))
		{
			strcat(entry, " ");
		}
	}

	p = (DEFS *) malloc(sizeof(DEFS));

	if (p == NULL)
	{
		free(entry);
		return FALSE;
	}

	p->entry = entry;

	p->name = (char *) malloc((name_len + 4) * sizeof(char));
	if (p->name == NULL)
	{
		free(p->entry);
		free(p);
		return FALSE;
	}

	/* Schauen, ob der !define Parameter enthalten soll */

	if (md_uses_parameters(p->entry))	/* definition uses parameters */
	{
		/* Definition mit Parametern */
		strcpy(p->name, token[1]);
		p->vars = TRUE;
	} else								/* normal definition */
	{
		/* normale Definition */
		sprintf(p->name, "(!%s)", token[1]);
		token[1][0] = EOS;
		p->vars = FALSE;
	}

	defs[define_counter] = p;
	define_counter++;

	return TRUE;
}


static void free_def(size_t d)
{
	if (defs[d] != NULL)
	{
		free(defs[d]->name);
		free(defs[d]->entry);
		free(defs[d]);
		defs[d] = NULL;
	}
}


GLOBAL _BOOL del_define(void)
{
	_UWORD i;

	if (token_counter <= 1)				/* only "!define" in the line? */
	{
		error_missing_parameter(CMD_UNDEF);
		return FALSE;
	}
	if (!check_macro_name(token[1]))
		return FALSE;
	for (i = 0; i < define_counter; i++)
	{
		if (defs[i] != NULL)
		{
			if (strcmp(token[1], defs[i]->name) == 0)
			{
				free_def(i);
				return TRUE;
			}
		}
	}
	if (is_internal_name(token[1]))
	{
		error_message(_("internal command (!%s) cannot be undefined"), token[1]);
		return FALSE;
	}
	return FALSE;
}



/*******************************************************************************
*
*  replace_udo_quotes():
*     quote UDO commands in text environment
*
*  Example:
*     !node -> !/node
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_udo_quotes(char *s)
{
	const char *found;

	found = strstr(s, "(!");
	while (found != NULL)
	{
		if (found[2] != '/')
		{
			char name[MACRO_NAME_LEN + 1];

			int i;

			for (i = 0; i < MACRO_NAME_LEN; i++)
			{
				if (found[2 + i] == '\\' && (desttype == TOTEX || desttype == TOPDL))
					found++;
				if (found[2 + i] == EOS)
					break;
				if (strchr(macro_allowed_name, found[2 + i]) == NULL)
					break;
				name[i] = found[2 + i];
			}
			name[i] = EOS;
			/*
			 * FIXME: this check for internal commands should not be here.
			 * internal commands should be handled *BEFORE* the quotes
			 * are removed. Apparently, this is not the case in a lot of
			 * places however.
			 */
			if (*name && !is_internal_name(name))
				warning_message(_("possibly undefined macro: %s"), name);
		}
		found = strstr(found + 2, "(!");
	}
	qreplace_all(s, "!/", 2, "!", 1);
}





/*******************************************************************************
*
*  init_module_par():
*     initialize all arrays used in this module
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_par(void)
{
	int i;

	for (i = 0; i < 64; i++)
		decode_chars[encode_chars[i]] = i;

	/* first of all, everything should be empty */
	phold_counter = 0;
	phold_alloc = 0;
	phold = NULL;

	speccmd_counter = 0;
	speccmd_alloc = 0;
	speccmd = NULL;

	hyphen_counter = 0;
	hyphen_alloc = 0;
	hyphen = NULL;

	macro_counter = 0;
	macros_alloc = 0;
	macros = NULL;

	define_counter = 0;
	defs_alloc = 0;
	defs = NULL;
}





/*******************************************************************************
*
*  exit_module_par():
*     release all arrays used in this module
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void exit_module_par(void)
{
	size_t d;

	for (d = 0; d < macro_counter; d++)
	{
		free(macros[d]->name);
		free(macros[d]->entry);
		free(macros[d]);
	}
	if (macros != NULL)
	{
		free(macros);
		macros = NULL;
	}
	macros_alloc = 0;
	macro_counter = 0;

	for (d = 0; d < define_counter; d++)
	{
		free_def(d);
	}
	if (defs != NULL)
	{
		free(defs);
		defs = NULL;
	}
	defs_alloc = 0;
	define_counter = 0;

	for (d = 0; d < hyphen_counter; d++)
	{
		free(hyphen[d]);
	}
	if (hyphen != NULL)
	{
		free(hyphen);
		hyphen = NULL;
	}
	hyphen_counter = 0;
	hyphen_alloc = 0;

	reset_placeholders();
	if (phold != NULL)
	{
		free(phold);
		phold = NULL;
	}
	phold_alloc = 0;

	reset_speccmds();
	if (speccmd != NULL)
	{
		free(speccmd);
		speccmd = NULL;
	}
	speccmd_alloc = 0;
}
