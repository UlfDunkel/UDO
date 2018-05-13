/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : toc.c
*  Symbol prefix: toc
*
*  Description  : This module contains routines which handle chapters, labels, aliases,
*                 table of contents and automatic referencing.
*
*                 Please find a detailed description of all variables in
*                 init_module_toc().
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
*  Co-Authors   : Ulf Dunkel (fd), Martin Elsaesser (ME), Gerhard Stoll (ggs)
*  Write access : fd, ME, ggs
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
*    fd  May 26: closing bracket in <br%s> added
*    fd  Dec 15: do_toptoc() creates a link to the Index page now (should be formatted using CSS commands)
*  2010:
*    fd  Jan 20: - file partly reformatted
*                - save_html_index() now converts labels using label2html()
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*    fd  Jan 24: html_footer() handles all 16 combinations of 
*                  webmasterurl, webmastername, webmastermailurl, webmasteremail
*    fd  Jan 25: save_html_index() does no longer list the indexudo page in itself
*    fd  Feb 03: c_label(): issue #84 fixed
*    fd  Feb 04: - c_label(): decision for <dd> now depends on bDescDDOpen
*                - more functions tidied up and reformatted
*    fd  Feb 05: - init_new_toc_entry(): toc_table[] structure cleared before usage
*                - set_html_keywords(): now uses MAX_TOKEN_LEN, to avoid issues in str2tok
*                - save_html_index(): Index jump line output fixed
*    fd  Feb 06: make_node(): usage of set_inside_node1() generalized
*    fd  Feb 08: - toc_output(): <br> not allowed outside of <li></li>
*                - make_node(): usage of set_inside_node1() restored
*    fd  Feb 09: - toc_output(): rewritten for HTML output (issue #85 fixed)
*                - save_html_index() debugged: (char)thisc
*                - init_toc_forms_numbers(): HTML format strings changed to avoid leading ' '
*                - toc_output() + its sub functions adjusted, using TOCL_HTM / TOCL_TEX
*                - save_html_index(): sorting fixed
*    fd  Feb 12: some octal chars resolved into constant macros
*    fd  Feb 16: CODE_CP1250_lig, sort_CODE_CP1250 added
*    fd  Feb 17: - CODE_437_lig[], sort_CODE_437[] + CODE_850_lig[], sort_CODE_850[] added
*                - CODE_HP_lig[] + sort_CODE_HP[] added
*                - CODE_NEXT_lig[] + sort_CODE_NEXT[] added
*                - win2sys() -> recode_chrtab()
*    fd  Feb 18: - str_UTF_sort_cmp()
*                - save_html_index() uses a new approach with flattened HTML_INDEX.sortname
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 23: - UDO_PL -> UDO_BUILD (no more patchlevels)
*                - unicode2char() adjusted, using ^string instead of local string
*    fd  Mar 01: html_footer(): changes from (ME) reverted - see discussion in UDO_DEV
*    fd  Mar 02: - html_footer(): notes added and mailto: handling enhanced
*                - webmastername    -> domain_name
*                - webmasterurl     -> domain_link
*                - webmasteremail   -> contact_name
*                - webmastermailurl -> contact_link
*    ME  Mar 03: - html_footer(): ..._link strings are complete URL
*                - if contact_link is empty, contact_name is not used to generate
*                  a "mailto:"-link. If the contact_name should be a link, the target
*                  has to be put into contact_link - there was one case in which
*                  contact_name without contact_link generated a link!
*                - use of contact_link for HTML the entries <link rev="made"> and
*                  <link rev="author"> if available
*    ME  Mar 04: - the chars uf lang.today are now quoted to the HTML-Chars
*                  ("M„rz" -> "M&auml;rz") in html_footer()
*    fd  Mar 12: bookmarks_ps(): ugly typo fixed (warned by Linux gcc)
*    ggs Apr 20: c_label: Labels will print out not only in description environment
*    ggs Apr 21: use_short_tocs -> use_compressed_tocs
*    fd  May 17: init_toc_forms_numbers() must no longer close </li> for HTML
*    fd  May 18: - output_html_doctype() no longer writes iso-8859-1 hard-coded
*                - output_html_meta() no longer writes iso-8859-1 hard-coded
*    fd  May 21: add_label(): supports "!label*" which must not be listed in index (#90)
*    ggs Aug 18: get_html_filename: New Parameter, which tells if a page is merged
*    fd  Sep 09: <a name>%s</a> changed to <a name></a>%s to avoid empty links
*  2011:
*    fd  Jan 29: HTML navigation bar output using GIF images no longer writes linefeeds
*                 in order to prevent gaps between images, so you can use images in
*                 segmented control style now.
*    fd  Feb 14: - add_...node_to_toc() merged into add_nodetype_to_toc()
*                - toc_begin_node() adjusted to handle calls from UDO.C
*                - add_nodetype_to_toc() enhanced
*                - all set_html_...() functions moved from TOC to TOC_HTML
*    fd  Feb 15: - more sources tidied up
*                - all *apx_output() functions merged into *toc_output() functions,
*                    which finally outputs the same proper HTML list formattings
*                - bookmarks_ps() simplified
*    fd  Feb 16: - make_*node() functions reformatted
*                - all make_*node() functions merged into new make_nodetype() function
*                - all set_inside_node*() functions merged into new set_inside_node() function
*    fd  Feb 17: - flag typos fixed
*                - all *toc_output() functions merged into toc_output() function
*                - all do_*toc() functions merged into do_toc() function
*                - save_htmlhelp_contents() adjusted for TOC_NODE5
*                - remaining functions reformatted
*                - more function descriptions added
*                - TOC output debugged
*    fd  Feb 19: c_tableofcontents(): tableofcontents command fixed for TeX ("\" -> "\\")
*    fd  Oct 07: toc_output(): avoid unwanted output of \end{itemize} in TeX
*  2013:
*    fd  Oct 23: HTML output now supports HTML5
*    fd  Nov 02: HTML5 output of <img> tags cleaned
*    tho Dec 04: WinHelp4: links to pnodes should now be displayed in a popup
*  2014:
*    ggs Apr 20: Add Node6
*    fd  Jun 20: HTML output of navigation bars now writes UDO_nav_xx IDs to anchors
*    fd  Sep 10: HTML TOC output for 6. level debugged (no longer doubles single 6th level entries in TOC)
*    fd  Oct 08: - HTML headlines|bottomlines output now creates unique UDO_nav_xx IDs
*                - HTML 5 no longer outputs <link rev='made'> and <meta name='Email'>
*                - string2reference() debugged: don't create IDs without name
*  2017:
*    fd  Feb 08: using lang.copyright
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
#include <time.h>
#include <ctype.h>
#include "udoport.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "udointl.h"
#include "commands.h"
#include "abo.h"
#include "chr.h"
#include "env.h"
#include "file.h"
#include "img.h"
#include "msg.h"
#include "par.h"
#include "str.h"
#include "sty.h"
#include "udo.h"
#include "upr.h"
#include "gui.h"
#include "debug.h"
#include "cfg.h"
#include "udomem.h"
#include "lang.h"

#include "export.h"
#include "toc.h"
#include "tp.h"
#if USE_KWSET
#include "kwset.h"
static kwset_t kwset;
#endif





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#if USE_NAME_HASH
#define HASH_SIZE 9973
LOCAL LABEL *hash[HASH_SIZE];
#endif

/*
 * max. references per paragraph,
 * only limited by encoding in add_placeholder()
 * (3 * 6 bits = 2 ^ 18)
 */
#define MAXREFERENCES       0x40000L




/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define TOCL_NONE  0
#define TOCL_HTM   1					/* used for use_toc_list_commands */
#define TOCL_TEX   2					/* dito */





/*******************************************************************************
*
*     LOCAL CONSTANTS
*
******************************************|************************************/

LOCAL const char *FRAME_NAME_TOC = "UDOtoc";
LOCAL const char *FRAME_NAME_CON = "UDOcon";

LOCAL const char *FRAME_FILE_TOC = "00toc";
LOCAL const char *FRAME_FILE_CON = "00con";

LOCAL const char *HTML_LABEL_CONTENTS = "UDOTOC";





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _reference				/* auto-reference placeholders */
{
	char magic[7];						/* Eine Steuermarke <ESC><0x80+nr> */
	char entry[MAX_TOKEN_LEN * 2];		/* ergibt max. 256 Zeichen */
} REFERENCE;


typedef struct _hmtl_index				/* index output for HTML */
{
	TOCIDX toc_index;					/* # of found label for TOC */
	_BOOL is_node;						/* the label is the caption (?) */
	char tocname[512];					/* label or node name */
	char sortname[512];					/* 'flattened' label or node name */
	_UWORD codepoint;					/* Unicode codepoint for sorting purposes */
} HTML_INDEX;

typedef struct _tWinMapData
{
	char remOn[16],						/* start of comment */
	 remOff[16];						/* end of comment */
	char cmd[32];						/* #define const */
	char varOp[16];						/*  = */
	char hexPre[16],					/* 0x $ */
	 hexSuf[16];						/* ; */
	char compiler[32];					/* C, Pascal, Visual-Basic, ... */
} tWinMapData;

typedef struct _hmtl_idx
{
	TOCIDX toc_index;
	_BOOL is_node;						/* the label is the caption (?) */
	char tocname[512];
} HTML_IDX;





/*******************************************************************************
*
*     LOCAL VARIABLES
*
******************************************|************************************/

LOCAL _BOOL toc_available;				/* Inhaltsverzeichnis existiert */
LOCAL _BOOL apx_available;				/* Anhang existiert */
LOCAL _BOOL head_foot;					/* TRUE: HEAD output, FALSE: FOOT */

LOCAL TOCIDX p1_toc_alloc;				/* # of TOC entries allocated in pass 1 */

LOCAL TOCTYPE p1_toctype;				/* Typ des aktuellen Kapitels */
LOCAL TOCTYPE p2_toctype;				/* Typ des aktuellen Kapitels */

LOCAL LABEL **label_table;				/* Array mit Zeigern auf Labels */
LOCAL LABIDX p1_lab_counter;			/* used labels, pass 1; contains last used slot # (1 less than number of entries) */
LOCAL LABIDX p2_lab_counter;			/* used labels, pass 2; contains last used slot # (1 less than number of entries) */
LOCAL LABIDX p1_lab_alloc;				/* # of allocated labels */

LOCAL REFERENCE *refs;					/* Referenzen */
LOCAL size_t refs_counter;				/* # of used references */
LOCAL size_t refs_alloc;				/* # of allocated references */

LOCAL TOCIDX p1_toc_n[TOC_MAXDEPTH];	/* absolut */
LOCAL TOCIDX p1_apx_n[TOC_MAXDEPTH];
LOCAL TOCIDX p1_toc_nr[TOC_MAXDEPTH];	/* Anzeige */
LOCAL TOCIDX p1_apx_nr[TOC_MAXDEPTH];

LOCAL TOCIDX p2_toc_n[TOC_MAXDEPTH];
LOCAL TOCIDX p2_apx_n[TOC_MAXDEPTH];

LOCAL TOCIDX last_n_index[TOC_MAXDEPTH];	/* toc_table[]-Indizes fuer Titelzeilen */

LOCAL TOCTYPE active_nodetype;			/* Flag fuer check_endnode() */

LOCAL const char *form_t_numbers[TOC_MAXDEPTH][TOC_MAXDEPTH];
LOCAL const char *form_t_nonumbers[TOC_MAXDEPTH][TOC_MAXDEPTH];

LOCAL const char *toc_list_top;
LOCAL const char *toc_list_end;
LOCAL int use_toc_list_commands;

LOCAL char allowed_next_chars[256];
LOCAL char allowed_prev_chars[256];

LOCAL char footer_buffer[512];			/* Puffer fuer den Footer */

LOCAL char html_target[64];

LOCAL char encode_chars[64] = {
	'0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
	'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
	'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
	'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
	'u', 'v', 'w', 'x', 'y', 'z', '#', '='
};

LOCAL const char *const tex_structure_names[TOC_MAXDEPTH + 1] = {
	"chapter",
	"section",
	"subsection",
	"subsubsection",
	"paragraph",
	"subparagraph",
	"subsubparagraph",
	"subsubsubparagraph",
	"subsubsubsubparagraph",
	"subsubsubsubsubparagraph"
};

LOCAL const char *const lyx_structure_names[TOC_MAXDEPTH + 1] = {
	"Chapter",
	"Section",
	"Subsection",
	"Subsubsection",
	"Paragraph",
	"Subparagraph",
	"Subparagraph",
	"Subparagraph",
	"Subparagraph",
	"Subparagraph"
};

LOCAL char info_structure_names[TOC_MAXDEPTH][2][2][18] = {
	{ { "chapter", "chapheading"}, {"appendix", "appendix" } },
	{ { "section", "heading"}, {"appendixsec", "appendixsec" } },
	{ { "subsection", "subheading"}, {"appendixsubsec", "appendixsubsec" } },
	{ { "subsubsection", "subsubheading"}, {"appendixsubsubsec", "appendixsubsubsec" } },
	{ { "subsubsection", "subsubheading"}, {"appendixsubsubsec", "appendixsubsubsec" } },
	{ { "subsubsection", "subsubheading"}, {"appendixsubsubsec", "appendixsubsubsec" } },
	{ { "subsubsection", "subsubheading"}, {"appendixsubsubsec", "appendixsubsubsec" } },
	{ { "subsubsection", "subsubheading"}, {"appendixsubsubsec", "appendixsubsubsec" } },
	{ { "subsubsection", "subsubheading"}, {"appendixsubsubsec", "appendixsubsubsec" } }
};

GLOBAL char asc_structure_chars[TOC_MAXDEPTH] = { '*', '=', '-', '\0', '\0', '\0', '\0', '\0', '\0' };

GLOBAL int kps_structure_height[TOC_MAXDEPTH + 1] = { 14, 7, 3, 0, 0, 0, 0, 0, 0, 0 };

LOCAL long drc_structure_numbers[TOC_MAXDEPTH] = { 0, 10, 100, 1000, 10000, 100000L, 1000000L, 10000000L, 100000000L };

LOCAL char src_structure_chars[TOC_MAXDEPTH] = { '#', '*', '=', '-', '-', '-', '-', '-', '-' };

GLOBAL int rtf_structure_height[TOC_MAXDEPTH + 1] = { 28, 14, 6, 0, 0, 0, 0, 0, 0, 0 };
LOCAL char rtf_structure_names[TOC_MAXDEPTH + 1][2][32] = {
	{ rtf_chapt, rtf_inv_chapt },
	{ rtf_node1, rtf_inv_node1 },
	{ rtf_node2, rtf_inv_node2 },
	{ rtf_node3, rtf_inv_node3 },
	{ rtf_node4, rtf_inv_node4 },
	{ rtf_node5, rtf_inv_node5 },
	{ rtf_node6, rtf_inv_node6 },
	{ rtf_node7, rtf_inv_node7 },
	{ rtf_node8, rtf_inv_node8 },
	{ rtf_node9, rtf_inv_node9 }
};

LOCAL char const lds_structure_names[TOC_MAXDEPTH + 1][8] = {
	"chapter",
	"sect",
	"sect1",
	"sect2",
	"sect3",
	"sect4",
	"sect5",
	"sect6",
	"sect7",
	"sect8"
};

LOCAL const char *const html_structure_names[TOC_MAXDEPTH] = {
	"chapter",
	"section",
	"subsection",
	"appendix",
	"",
	"",
	"",
	"",
	""
};

LOCAL char const hph_structure_names[TOC_MAXDEPTH + 1][8] = {
	"chapter",
	"s1",
	"s2",
	"s3",
	"s4",
	"s5",
	"s6",
	"s7",
	"s8",
	"s9"
};






/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

LOCAL void do_toptoc(const TOCTYPE current_node, _BOOL popup);





/*******************************************************************************
*
*     LOCAL PROCEDURES
*
******************************************|************************************/

#if USE_NAME_HASH
LOCAL _UWORD hash_val(const char *name)
{
	_UWORD val;

	val = 0;
	while (*name != '\0')
	{
		val += (_UWORD) (unsigned char) (*name);
		name++;
	}
	return val % HASH_SIZE;
}
#endif /* USE_NAME_HASH */




/*******************************************************************************
*
*  is_node_link():
*     Zu welchem Node gehoert ein Label (fuer ST-Guide, Texinfo, Pure-C-Help)
*
* @link: link text name
* @node: node name which uses this label
* @ti: TOC index of node/label/alias
* @isnode: TRUE: is node, FALSE: is label or alias
* @isalias TRUE: is alias, FALSE: is label
* @ispopup: TRUE: is a popup
* @li: LAB index of node/label/alias
*
* @Return:
*      TRUE: label exists
*     FALSE: label doesn't exist
*
******************************************|************************************/

GLOBAL _BOOL is_node_link(const char *link, char *node, TOCIDX *ti, _BOOL *isnode, _BOOL *isalias, _BOOL *ispopup, LABIDX *li)
{
	_BOOL ret = FALSE;

	node[0] = EOS;
	*isnode = FALSE;
	*isalias = FALSE;
	*ispopup = FALSE;

	if (link[0] == EOS)
	{
		return FALSE;
	}

#if USE_NAME_HASH
	{
		_UWORD hash_index;
		LABEL *l;

		hash_index = hash_val(link);
		l = hash[hash_index];
		while (l != NULL)
		{
			if (strcmp(l->name, link) == 0)
			{
				*isnode = l->is_node;
				*isalias = l->is_alias;
				*ispopup = l->is_popup;
				*li = l->labindex;
				*ti = l->tocindex;
				l->referenced = TRUE;
				strcpy(node, toc_table[*ti]->nodename);
				ret = TRUE;
				break;
			}
			l = l->next_hash;
		}
	}
#else
	{
		LABIDX i;

		for (i = 1; i <= p1_lab_counter; i++)
		{
			if (strcmp(label_table[i]->name, link) == 0)
			{
				*isnode = label_table[i]->is_node;
				*isalias = label_table[i]->is_alias;
				*ispopup = label_table[i]->is_popup;
				*li = i;
				*ti = label_table[i]->tocindex;
				label_table[i]->referenced = TRUE;
				strcpy(node, toc_table[*ti]->nodename);
				ret = TRUE;
				break;
			}
		}
	}
#endif

	return ret;
}





/*******************************************************************************
*
*  getLabelIndexFromTocIndex():
*     ??? (description missing)
*
*  return:
*     ???
*
******************************************|************************************/

GLOBAL LABIDX getLabelIndexFromTocIndex(LABIDX * li, const TOCIDX ti)
{
	*li = toc_table[ti]->labindex;
	return *li;
}





/*******************************************************************************
*
*  output_helpid():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_helpid(TOCIDX tocindex)
{
	char s[256];

	s[0] = '\0';
	if (toc_table[tocindex]->helpid != NULL)
	{
		strcpy(s, toc_table[tocindex]->helpid);
	} else if (use_auto_helpids)
	{
		node2WinAutoID(s, toc_table[tocindex]->nodename);
	}
	if (s[0] != '\0')
	{
		switch (desttype)
		{
		case TOSTG:
		case TOAMG:
			voutlnf("@alias \"%s\"", s);
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			voutlnf("#{\\footnote # %s}", s);
			break;
		case TOHAH:
		case TOHTM:
		case TOMHH:
			label2html(s);
			voutlnf("<a %s=\"%s\"></a>", xhtml_id_attr, s);
			break;
		case TOLDS:
			voutlnf("<label id=\"%s\">", s);
			break;
		case TOTEX:
			voutlnf("\\label{%s}", s);
			break;
		case TOPDL:
			voutlnf("\\label{%s}", s);
			break;
		case TOLYX:
			voutlnf("\\begin_inset LatexCommand \\label{%s}", s);
			voutlnf("\\end_inset");
			break;
		}
	}
}





/*******************************************************************************
*
*  output_aliasses():
*     output aliasses of a chapter
*
*  Note:
*     Diese muessen nach der Node-Angabe erfolgen.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_aliasses(void)
{
	register LABIDX i;
	LABIDX start;
	char s[MAX_LABEL_LEN * 2 + 1];
	char keyword[MAX_LABEL_LEN * 2 + 1];

	/* Fuer Pure C Help und Turbo Vision Help werden die Aliasse zusammen */
	/* mit *nodes ausgegeben */

	start = toc_table[p2_toc_counter]->labindex;

	if (start == 0)
		return;

	for (i = start; i <= p1_lab_counter; i++)
	{
		LABEL *l = label_table[i];

		/* aktuellen Zaehler mit Alias-Zugehoerigkeit vergleichen */
		if (l->is_alias && p2_toc_counter == l->tocindex)
		{
			switch (desttype)
			{
			case TOSTG:
				strcpy(s, l->name);
				node2stg(s);
				convert_tilde(s);
				voutlnf("@alias \"%s\"", s);
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				strcpy(s, l->name);
				del_internal_styles(s);
				convert_tilde(s);
				if (use_alias_inside_index && !no_index)
				{
					strcpy(keyword, s);
					winspecials2ascii(keyword);
					voutlnf("K{\\footnote K %s}", keyword);
				}
				alias2NrWinhelp(s, i);
				voutlnf("#{\\footnote # %s}", s);
				if (bDocWinOldKeywords)
				{
					strcpy(s, l->name);
					del_internal_styles(s);
					node2winhelp(s);
					voutlnf("#{\\footnote # %s}", s);
				}
				break;

			case TORTF:
				strcpy(s, l->name);
				del_internal_styles(s);
				convert_tilde(s);
				if (use_alias_inside_index && !no_index)
				{
					strcpy(keyword, s);
					winspecials2ascii(keyword);
					voutlnf("{\\xe\\v %s}", keyword);
				}
				break;

			case TOHAH:
			case TOHTM:
			case TOMHH:
				strcpy(s, l->name);
				convert_tilde(s);
				if (!l->is_node && l->is_alias)
					recode_chrtab(s, CHRTAB_HTML);
				label2html(s);
				voutlnf("<a %s=\"%s\"></a>", xhtml_id_attr, s);
				break;

			case TOLDS:
				strcpy(s, l->name);
				convert_tilde(s);
				voutlnf("<label id=\"%s\">", s);
				break;

			case TOTEX:
				strcpy(s, l->name);
				convert_tilde(s);
				label2tex(s);
				voutlnf("\\label{%s}", s);
				break;

			case TOPDL:
				strcpy(s, l->name);
				convert_tilde(s);
				label2tex(s);
				voutlnf("\\label{%s}", s);
				voutlnf("\\pdfdest num %u fitbh", l->labindex);
				break;

			case TOLYX:
				strcpy(s, l->name);
				convert_tilde(s);
				label2lyx(s);
				voutlnf("\\begin_inset LatexCommand \\label{%s}", s);
				voutlnf("\\end_inset");
				break;
			}
		}
	}

	/* Jump-ID ausgeben */
	output_helpid(p2_toc_counter);
}



/*******************************************************************************
*
*  reset_refs():
*     allgemeine Referenz-Routinen
*
*  Bei Formaten, bei denen Nodes und Labels selbstaendig referenziert werden muessen,
*  koennen folgende Routinen benutzt werden.
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void reset_refs(void)
{
	register size_t i;

	for (i = 0; i < refs_counter; i++)
	{
		refs[i].entry[0] = EOS;
		refs[i].magic[0] = EOS;
	}

	refs_counter = 0;
}





/*******************************************************************************
*
*  add_ref():
*     ??? (description missing)
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL add_ref(const char *r)
{
	size_t counter;
	unsigned char c1, c2, c3;
	REFERENCE *new_refs;

	counter = refs_counter;
	if (counter >= MAXREFERENCES)
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
	if (counter >= refs_alloc)
	{
		size_t new_alloc = refs_alloc + 100;

		new_refs = (REFERENCE *) realloc(refs, new_alloc * sizeof(REFERENCE));
		if (new_refs == NULL)
		{
			return FALSE;
		}
		refs = new_refs;
		refs_alloc = new_alloc;
	}

	sprintf(refs[counter].magic, "\033%c%c%c%c\033", C_REF_MAGIC, c1, c2, c3);
	strcpy(refs[counter].entry, r);

	refs_counter++;

	return TRUE;
}




/*******************************************************************************
*
*  replace_refs():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void replace_refs(char *s)
{
	register size_t i;

	for (i = 0; i < refs_counter; i++)
	{
		replace_once(s, refs[i].magic, refs[i].entry);
	}
}





/*******************************************************************************
*
*  string2reference():
* @ref: the reference to create
* @display: the string to display
* @li: the index of the label
* @for_toc: TRUE if for any table-of-contents
* @pic: constant for GUI navigation image, e.g. GIF_UP_NAME
* @uiW: GUI navigation image width
* @uiH: GUInavigation image height
*
*     ??? (description missing)
*
******************************************|************************************/

GLOBAL void string2reference(char *ref, const char *display, const LABIDX li, const _BOOL for_toc,
							 const char *pic, const _UWORD uiW, const _UWORD uiH)
{
	char s[512];
	char n[512];
	char sNoSty[512];
	char hfn[MYFILE_FULL_LEN + 1];
	char sGifSize[80];
	char sIDName[40];					/* string buffer for anchor ID name, e.g. "id=\"UDO_nav_lf\" " */
	char d[1024];
	TOCIDX ti;
	TOCIDX ui;
	_BOOL same_file = FALSE;			/* TRUE: reference is in same file */
	char *htmlfilename;
	char suff[MYFILE_SUFF_LEN + 1];
	LABEL *l;
	int level;
	_BOOL do_ins;

	l = label_table[li];
	if (l->is_node && display == l->name && toc_table[l->tocindex]->nodetitle != toc_table[l->tocindex]->nodename)
		display = toc_table[l->tocindex]->nodetitle;

	strcpy(n, l->name);
	replace_udo_tilde(n);
	replace_udo_nbsp(n);

	strcpy(d, display);
	replace_udo_tilde(d);
	replace_udo_nbsp(d);

	switch (desttype)
	{
	case TOWIN:
	case TOWH4:
	case TOAQV:
		if (l->is_node)
		{
			node2NrWinhelp(s, l->labindex);
		} else if (l->is_alias)
		{
			alias2NrWinhelp(s, l->labindex);
		} else
		{
			label2NrWinhelp(s, l->labindex);
		}
		if (l->is_popup)
		{
			sprintf(ref, "{\\uldb %s}{\\v ! PopupId(`', `%s')}", d, s);
		} else
		{
			sprintf(ref, "{\\uldb %s}{\\v %s}", d, s);
		}
		break;

	case TOIPF:
		if (l->is_node)
		{
			node2NrIPF(s, l->labindex);
		} else
		{
			ui = l->tocindex;
			node2NrIPF(s, toc_table[ui]->labindex);
		}
		sprintf(ref, ":link refid=%s reftype=hd.%s:elink.", s, d);
		break;

	case TOSTG:
		if (l->ignore_links || display != l->name)
		{
			node2stg(n);
			sprintf(ref, "@{\"%s\" link \"%s\"}", d, n);
		} else
		{
			strcpy(ref, d);
			replace_1at_by_2at(ref);
		}
		break;

	case TOAMG:
		if (l->is_node)
		{
			strcpy(n, l->name);
		} else
		{
			ti = l->tocindex;
			strcpy(n, label_table[toc_table[ti]->labindex]->name);
		}
		replace_udo_tilde(n);
		replace_udo_nbsp(n);
		node2stg(n);
		sprintf(ref, "@{\"%s\" link \"%s\"}", d, n);
		break;

	case TOTVH:
		node2vision(d);
		sprintf(ref, "{%s:%s}", n, d);
		break;

	case TOPCH:
		if (strchr(n, '"') != NULL)
		{
			strcpy(s, n);
			node2pchelp(s);
			sprintf(ref, "\\link(\"%s\")%s\\#", s, d);
		} else
		{
			sprintf(ref, "\\#%s\\#", n);
		}
		if (!for_toc)
		{
			/*
			 * Referenz als Platzhalter anlegen, damit der
			 * Blocksatz korrekt wird.
			 */
			insert_placeholder(ref, ref, ref, n);
		}
		break;

	case TOLDS:
		/* ??? was ist mit '"' im nodenamen oder Text? */
		sprintf(ref, "<ref id=\"%s\" name=\"%s\">", n, d);
		break;

	case TOINF:
		node2texinfo(n);
		qreplace_all(d, "*", 1, "\\*", 2);
		sprintf(ref, "%s (@pxref{%s})", d, n);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (!strcmp(pic, GIF_UP_NAME))
			sprintf(sIDName, " %s=\"UDO_nav_up", xhtml_id_attr);
		else if (!strcmp(pic, GIF_LF_NAME))
			sprintf(sIDName, " %s=\"UDO_nav_lf", xhtml_id_attr);
		else if (!strcmp(pic, GIF_RG_NAME))
			sprintf(sIDName, " %s=\"UDO_nav_rg", xhtml_id_attr);
		else
			sIDName[0] = 0;				/* empty C string */

		/* mark ID as unique */
		if (sIDName[0] != '\0')
		{
			if (head_foot)
				strcat(sIDName, "_HEAD\"");
			else
				strcat(sIDName, "_FOOT\"");
		}

		strcpy(sNoSty, n);
		del_html_styles(sNoSty);
		label2html(sNoSty);

		ti = l->tocindex;

		/* Hier auch das Mergen beachten! */
		ui = ti;						/* upper index = toc_table index */
		for (level = TOC_MAXDEPTH - 1; level >= TOC_NODE2; level--)
			if (html_merge_node[level] && toc_table[ti]->toctype == level)
				ui = toc_table[ti]->up_n_index[level - 1];
		if (html_merge_node[TOC_NODE1])
			ui = 0;

		if (ui == 0 && strcmp(l->name, "Main") != 0)
		{
			strcpy(hfn, outfile.name);
			htmlfilename = hfn;
		} else
		{
			sprintf(hfn, "%s%s", html_name_prefix, toc_table[ui]->filename);
			htmlfilename = hfn;
		}

		/* Feststellen, ob die Referenz im gleichen File liegt */
		if (strcmp(htmlfilename, outfile.name) == 0)
		{
			same_file = TRUE;
		}

		if (strchr(htmlfilename, '.') != NULL)
			strcpy(suff, "");
		else
			strcpy(suff, outfile.suff);

		if (pic[0] != EOS)				/* GUI navigation */
		{
			/* Fuer Kopf- oder Fusszeile */
			if (no_images)
			{
				if (l->is_node || l->is_alias)
				{
					sprintf(ref, "<a%s href=\"%s%s\"%s>%s</a>", sIDName, htmlfilename, suff, html_target, d);
				} else
				{
					sprintf(ref, "<a%s href=\"%s%s#%s\"%s>%s</a>", sIDName, htmlfilename, suff, sNoSty, html_target, d);
				}
			} else
			{
				char border[20];

				strcpy(border, " border=\"0\"");
#if 0
				if (html_doctype == HTML5)
					border[0] = EOS;
#endif
				sGifSize[0] = EOS;
				if (uiW != 0 && uiH != 0)
				{
					sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
				}
				if (l->is_node || l->is_alias)
				{
					sprintf(ref, "<a%s href=\"%s%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s>%s</a>",
							sIDName, htmlfilename, suff, html_target, pic, n, n, border, sGifSize, xhtml_closer, d);
				} else
				{
					sprintf(ref, "<a%s href=\"%s%s#%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s>%s</a>",
							sIDName, htmlfilename, suff, sNoSty, html_target, pic, n, n, border, sGifSize, xhtml_closer,
							d);
				}
			}
		} else
		{
			if (l->is_node || l->is_alias)
			{
				if (same_file)
				{
					sprintf(ref, "<a%s href=\"#%s\"%s>%s</a>", sIDName, sNoSty, html_target, d);
				} else
				{
					/*
					 * Hier muss noch unterschieden werden, wenn
					 * gemerged wird. Dann ein # einfuegen!
					 * ti oben bereits aus tocindex gesetzt
					 */
					do_ins = FALSE;
					for (level = TOC_NODE2; level < TOC_MAXDEPTH; level++)
						if (html_merge_node[level] && toc_table[ti]->n[level] != 0)
							do_ins = TRUE;
					if (do_ins)
					{
						sprintf(ref, "<a%s href=\"%s%s#%s\"%s>%s</a>",
								sIDName, htmlfilename, suff, sNoSty, html_target, d);
					} else
					{
						sprintf(ref, "<a%s href=\"%s%s\"%s>%s</a>", sIDName, htmlfilename, suff, html_target, d);
					}
				}
			} else
			{
				sprintf(ref, "<a%s href=\"%s%s#%s\"%s>%s</a>", sIDName, htmlfilename, suff, sNoSty, html_target, d);
			}
		}
		break;

	case TOTEX:
		strcpy(ref, d);
		break;

	case TOPDL:
		sprintf(ref, "{\\leavevmode\\pdfstartlink goto num %u %s\\pdfendlink}", l->labindex, d);
		break;

	case TOKPS:
		if (strpbrk(n, " :;\\()/") != NULL)
		{
			strcpy(s, n);
			node2postscript(n, KPS_CONTENT);
			node2postscript(s, KPS_NAMEDEST);
			sprintf(ref, " (%s) /%s 0 0 0 Link", n, s);
		} else
		{
			sprintf(ref, " (%s) /%s 0 0 0 Link", n, n);
		}

		if (!for_toc)
		{
			/* Referenz als Platzhalter anlegen, damit der */
			/* Blocksatz korrekt wird. */
			insert_placeholder(ref, ref, ref, n);
		}
		break;

	default:
		strcpy(ref, d);
		break;
	}
}


/*******************************************************************************
*
*  auto_references():
*     generate automatic references, depending on the setting of !autoref
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void auto_references(char *s, const _BOOL for_toc, const char *pic, const _UWORD uiWidth, const _UWORD uiHeight)
{
	if (desttype == TOINF && !for_toc)
	{
		/* Automatische Referenzen werden nur fuer Inhaltsverzeichnisse */
		/* gesetzt. Andere Referenzen muessen wie bei TeX mit !link */
		/* manuell erzeugt werden! */
		return;
	}

	if (!bDocAutorefOff)
	{
		gen_references(s, for_toc, pic, uiWidth, uiHeight);
	}
}


/*******************************************************************************
*
*  gen_references():
*     generate automatic references, independant on the setting of !autoref
*     used for example in TOCs and in (!link)-commands
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void gen_references(char *s, const _BOOL for_toc, const char *pic, const _UWORD uiWidth, const _UWORD uiHeight)
{
	register LABIDX i;
	char the_ref[512], *pos, *found_pos, *searchpos;
	unsigned char nextchar, prevchar;
	LABIDX found_lab;
	size_t found_len, ll;
	_BOOL ref_it;
	_BOOL found_one;
	LABEL *labptr;
	size_t total_len;
	size_t search_len;

	reset_refs();

	do
	{
		found_lab = 0;
		found_pos = s;

		total_len = strlen(s);

#if USE_KWSET
		if (!config.bNoFastAutoref && kwset != NULL)
		{
			size_t offset;

			struct kwsmatch kwsmatch;

			searchpos = s;
			search_len = total_len;
			do
			{
				offset = kwsexec(kwset, searchpos, search_len, &kwsmatch);

				if (offset != (size_t) - 1)
				{
					pos = searchpos + offset;
					nextchar = pos[kwsmatch.size[0]];
					if (pos == s)
						prevchar = EOS;
					else
						prevchar = pos[-1];

					if (allowed_prev_chars[prevchar] && allowed_next_chars[nextchar])
					{
						found_lab = kwsmatch.index + 1;
						/* found_len = kwsmatch.size[0]; */
						found_pos = pos;
						found_one = FALSE;
					} else
					{
						searchpos = pos + 1;
						search_len = total_len - (searchpos - s);;
						found_one = TRUE;
					}
				} else
				{
					found_one = FALSE;
				}
			} while (found_one);
		} else
#endif
		{
			found_len = 0;
			for (i = 1; i <= p1_lab_counter; i++)
			{
				labptr = label_table[i];
				if (for_toc || (!for_toc && !labptr->ignore_links))
				{
					searchpos = s;
					search_len = total_len;

					do
					{
						if (labptr->len == search_len)
						{
							if (strcmp(labptr->name, searchpos) == 0)
							{
								pos = searchpos;
							} else
							{
								pos = NULL;
							}
						} else if (labptr->len > search_len)
						{
							pos = NULL;
						} else
						{
							char *ptr;
							_BOOL ignore_it;

							ptr = searchpos;

							while ((pos = strstr(ptr, labptr->name)) != NULL)
							{
								ignore_it = FALSE;

								if ((pos - 2) >= s)
								{
									if (pos[-2] == '\033' && pos[-1] < '\010')
									{
										ptr = pos + 2;
										ignore_it = TRUE;
									}
								}

								if (!ignore_it)
								{
									break;
								}
							}
						}

						if (pos != NULL)
						{
							ll = labptr->len;

							found_one = TRUE;
							if (ll > found_len)
							{
								nextchar = pos[ll];
								if (pos == s)
								{
									prevchar = EOS;
								} else
								{
									prevchar = pos[-1];
								}

								if (allowed_prev_chars[prevchar] && allowed_next_chars[nextchar])
								{
									found_lab = labptr->labindex;
									found_len = ll;
									found_pos = pos;
									found_one = FALSE;	/* um innere schleife zu beenden */
								} else
								{
									searchpos = pos + 1;
									search_len = total_len - (searchpos - s);;
								}
							} else
							{
								searchpos = pos + 1;
								search_len = total_len - (searchpos - s);;
							}
						} else
						{
							/* pos == NULL */
							found_one = FALSE;
						}

					} while (found_one);

				}

			}
		}

		if (found_lab != 0)
		{
			LABEL *l = label_table[found_lab];
			
			ref_it = TRUE;
			l->referenced = TRUE;

			/* Hier dafuer sorgen, dass nicht innerhalb eines Nodes */
			/* referenziert wird, wenn man nicht im Inhaltsverzeichnis ist */

			if (!for_toc)
			{
				if (p2_toc_counter == l->tocindex)
				{
					ref_it = FALSE;
				}
			}
			if (!for_toc && l->ignore_links)
				ref_it = FALSE;

			if (ref_it)
			{
				string2reference(the_ref, l->name, found_lab, for_toc, pic, uiWidth, uiHeight);
				add_ref(the_ref);
			} else
			{
				add_ref(l->name);
			}

			replace_once(found_pos, l->name, refs[refs_counter - 1].magic);
		}

	} while (found_lab != 0);

	replace_refs(s);
}



/*******************************************************************************
*
*  output_raw_file():
*     read raw file and output it unchanged
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL output_raw_file(const char *filename)
{
	MYTEXTFILE *file;
	char s[LINELEN + 1];
	char old_filename[MYFILE_FULL_LEN];
	char tmp_filename[MYFILE_FULL_LEN];
	size_t len;

	um_strcpy(old_filename, filename, ArraySize(old_filename), "output_raw_file[1]");
	um_strcpy(tmp_filename, filename, ArraySize(tmp_filename), "output_raw_file[2]");

	build_include_filename(tmp_filename, infile.full, "");

	file = myTextOpen(tmp_filename);

	if (file == NULL)
	{
		strcpy(tmp_filename, old_filename);
		file = myTextOpen(tmp_filename);
	}

	if (file == NULL)
		return FALSE;

	while (myTextGetline(s, LINELEN, file))
	{
		len = strlen(s);
		while (len > 0 && (((_UBYTE) s[len - 1]) <= 32))
		{
			s[len - 1] = EOS;
			len--;
		}
		replace_macros(s);
		outln(s);
	}

	myTextClose(file);

	return TRUE;
}





/*******************************************************************************
*
*  check_output_raw_header():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL _BOOL check_output_raw_header(void)
{
	if (!toc_table[p2_toc_counter]->ignore_raw_header)
	{
		if (toc_table[p2_toc_counter]->raw_header_filename != 0)
		{
			return output_raw_file(file_lookup(toc_table[p2_toc_counter]->raw_header_filename));
		} else
		{
			if (sDocRawHeaderFilename != 0)
			{
				return output_raw_file(file_lookup(sDocRawHeaderFilename));
			}
		}
	}
	return FALSE;
}





/*******************************************************************************
*
*  check_output_raw_footer():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL _BOOL check_output_raw_footer(_BOOL lastNode)
{
	TOCIDX offset = 1;

	if (lastNode)
		offset = 0;

	/* p2_toc_counter bereits hochgezaehlt, daher 1 abziehen, */
	/* aber nur dann, wenn es nicht der letzte Node ist (bei */
	/* !end_document tritt das auf) */

	if (!toc_table[p2_toc_counter - offset]->ignore_raw_footer)
	{
		if (toc_table[p2_toc_counter - offset]->raw_footer_filename != 0)
		{
			return output_raw_file(file_lookup(toc_table[p2_toc_counter - offset]->raw_footer_filename));
		} else
		{
			if (sDocRawFooterFilename != 0)
			{
				return output_raw_file(file_lookup(sDocRawFooterFilename));
			}
		}
	}

	return FALSE;
}





/*******************************************************************************
*
*  man_headline():
*     Topline fuer die formatierte ASCII-Ausgabe
*
*  Note:
*     darf NICHT outln() aufrufen, da sonst Rekursion!
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void man_headline(void)
{
	char n[512];
	char s1[512];
	size_t spaces, s1l;

	if (no_headlines)
		return;

	if (titdat.program == NULL)
		return;

	if (sDocManType[0] != EOS)
		sprintf(s1, "%s%s(%s)%s", BOLD_ON, titdat.program, sDocManType, BOLD_OFF);
	else
		sprintf(s1, "%s%s%s", BOLD_ON, titdat.program, BOLD_OFF);

	s1l = strlen(s1) - strlen(BOLD_ON) - strlen(BOLD_OFF);

	spaces = zDocParwidth - 2 * s1l;

	sprintf(n, "%s%*s%-*s", s1, (int) spaces, "", (int) s1l, s1);

	c_internal_styles(n);

	fprintf(outfile.file, " %s\n\n", n);
	outlines += 2;

	iManPageLines = 2;
}





/*******************************************************************************
*
*  man_bottomline():
*     Bottomline fuer die formatierte ASCII-Ausgabe
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void man_bottomline(void)
{
	char n[256];

	sprintf(n, "- %d -", iManPagePages + 1);
	strcenter(n, zDocParwidth);
	fprintf(outfile.file, "\n%s\n\n", n);
	outlines += 3;
}





/*******************************************************************************
*
*  stg_headline():
*     Topline fuer den ST-Guide
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void stg_headline(const char *numbers, const char *nodename, _BOOL popup)
{
	char n[512], s[512];
	size_t i, sooft;
	size_t platz_links;
	size_t sl;
	TOCITEM *toc = toc_table[p2_toc_counter];
	const char *toptitle;
	TOCTYPE d;
	
	do_toptoc(toc->toctype, popup);

	if (no_headlines)
		return;

	strcpy(s, numbers);

	if (s[0] != EOS)
		um_strcat(s, " ", ArraySize(s), "!stg_headline");

	if (nodename[0] == EOS)
		tokcat(s, ArraySize(s));
	else
		um_strcat(s, nodename, ArraySize(s), "!stg_headline");

	replace_udo_quotes(s);
	delete_all_divis(s);

	toptitle = titdat.program;
	d = toc->toctype;
	if (d != TOC_TOC)
	{
		for (; d >= TOC_NODE1; d--)
		{
			if (last_n_index[d] != 0 && toc_table[last_n_index[d]]->toptitle)
			{
				toptitle = toc_table[last_n_index[d]]->toptitle;
				/*
				 * empty top_title suppresses header line completely
				 */
				if (*toptitle == '\0')
					return;
				break;
			}
		}
	}
		
	if (toptitle != NULL)
		sl = strlen(toptitle);
	else
		sl = 0;

	platz_links = zDocParwidth - sl - 1;

	if (toklen(s) > platz_links)
	{
		n[0] = EOS;
		strncat(n, s, platz_links - 4);
		strcat(n, "... ");
	} else
	{
		strcpy(n, s);
		sooft = zDocParwidth - toklen(s) - sl;

		for (i = 0; i < sooft; i++)
			strcat(n, " ");
	}

	if (toptitle != NULL)
		strcat(n, toptitle);

	c_internal_styles(n);
	replace_udo_tilde(n);
	replace_udo_nbsp(n);
	replace_1at_by_2at(n);

	if (desttype == TOSTG)
		voutlnf("@{U}%s@{u}", n);
	else
		voutlnf("@{U}%s@{UU}", n);

	outln("");
}





/*******************************************************************************
*
*  stg_header():
*     output header for ST-Guide
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void stg_header(const char *numbers, const char *nodename, _BOOL is_popup)
{
	TOCIDX ti;
	_BOOL flag;

	output_aliasses();

	ti = p2_toc_counter;

	if (toc_table[ti]->ignore_links)
		outln("@noref");

	if (use_chapter_images && toc_table[ti]->image != NULL)
	{
		c_begin_center();
		flag = c_img_output(toc_table[ti]->image, "", FALSE, TRUE);
		c_end_center();
		if (flag)
			return;
	}

	if (!is_popup)
		stg_headline(numbers, nodename, is_popup);
}





/*******************************************************************************
*
*  pch_headline():
*     output topline for PC-HELP
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void pch_headline(const char *s)
{
	char n[512];
	size_t i, sooft, platz_links, pl;
	GLOBAL TOCITEM *toc = toc_table[p2_toc_counter];
	const char *toptitle;
	TOCTYPE d;

	if (no_headlines)
		return;

	toptitle = titdat.program;
	d = toc->toctype;
	if (d != TOC_TOC)
	{
		for (; d >= TOC_NODE1; d--)
		{
			if (last_n_index[d] != 0 && toc_table[last_n_index[d]]->toptitle)
			{
				toptitle = toc_table[last_n_index[d]]->toptitle;
				break;
			}
		}
	}
		
	pl = 0;
	if (toptitle != NULL)
		pl = strlen(toptitle);

	platz_links = zDocParwidth - pl - 1;

	if (strlen(s) > platz_links)
	{
		n[0] = EOS;
		strncat(n, s, platz_links - 3);
		strcat(n, "...");
	} else
	{
		strcpy(n, s);
		sooft = zDocParwidth - strlen(s) - pl;

		for (i = 0; i < sooft; i++)
		{
			strcat(n, " ");
		}
	}

	/* program name specified? */
	if (toptitle != NULL)
	{
		if (uses_tableofcontents && toptitle == titdat.program)
		{
			strcat(n, PCH_LINK);
			strcat(n, toptitle);
			strcat(n, PCH_LINK);
		} else
		{
			strcat(n, toptitle);
		}
	}

	replace_udo_quotes(n);
	delete_all_divis(n);
	c_internal_styles(n);
	replace_udo_tilde(n);
	replace_udo_nbsp(n);

	outln(n);
	output_ascii_line("-", zDocParwidth);
}





/*******************************************************************************
*
*  pch_bottomline():
*     output bottomline for PC-HELP
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void pch_bottomline(void)
{
	TOCIDX ci, pi, ni, ui;
	char s[256];
	const char *upname, *uptitle, *prevname, *prevtitle, *nextname, *nexttitle;

	if (no_bottomlines)
		return;

	upname = prevname = nextname = uptitle = prevtitle = nexttitle = NULL;

	if (uses_tableofcontents)
	{
		upname = uptitle = get_lang()->contents;
		prevname = prevtitle = get_lang()->contents;
	}

	ci = p2_toc_counter;
	pi = toc_table[ci]->prev_index;
	ni = toc_table[ci]->next_index;

	if (toc_table[ci]->toctype >= TOC_NODE2 && toc_table[ci]->toctype < TOC_MAXDEPTH)
		ui = toc_table[ci]->up_n_index[toc_table[ci]->toctype - 1];
	else
		ui = 0;
	if (ui != 0)
	{
		upname = toc_table[ui]->nodename;
		uptitle = toc_table[ui]->nodetitle;
	}
	if (pi != 0)
	{
		prevname = toc_table[pi]->nodename;
		prevtitle = toc_table[pi]->nodetitle;
	}
	if (ni != 0)
	{
		nextname = toc_table[ni]->nodename;
		nexttitle = toc_table[ni]->nodetitle;
	}
	
	output_ascii_line("-", zDocParwidth);

	if (upname != NULL)
	{
		if (strchr(upname, '"') != NULL || upname != uptitle)
		{
			strcpy(s, uptitle);
			node2pchelp(s);
			voutlnf("[^^^^] \\link(\"%s\")%s\\# ", s, upname);
		} else
		{
			voutlnf("[^^^^] \\#%s\\#", upname);
		}
	}

	if (prevname != NULL)
	{
		if (strchr(prevname, '"') != NULL ||prevname != prevtitle)
		{
			strcpy(s, prevname);
			node2pchelp(s);
			voutlnf("[<<<<] \\link(\"%s\")%s\\# ", s, prevtitle);
		} else
		{
			voutlnf("[<<<<] \\#%s\\#", prevname);
		}
	}

	if (nextname != NULL)
	{
		if (nextname[0] != EOS)
		{
			if (strchr(nextname, '"') != NULL || nextname != nexttitle)
			{
				strcpy(s, nextname);
				node2pchelp(s);
				voutlnf("[>>>>] \\link(\"%s\")%s\\# ", s, nexttitle);
			} else
			{
				voutlnf("[>>>>] \\#%s\\#", nextname);
			}
		}
	}

	outln("");
}





/*******************************************************************************
*
*  output_pch_header():
*     output header for PC-HELP
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_pch_header(const char *numbers, const char *name, _BOOL popup)
{
	char n[256], q[256];
	LABIDX start;
	register LABIDX i;

	outln("");
	outln("screen(");

	start = toc_table[p2_toc_counter]->labindex;

	for (i = start; i <= p1_lab_counter; i++)
	{
		if (label_table[i]->tocindex == p2_toc_counter)
		{
			strcpy(q, label_table[i]->name);
			node2pchelp(q);
			sprintf(n, "  capsensitive(\"%s\")", q);

			if (i + 1 <= p1_lab_counter)
			{
				if (label_table[i + 1]->tocindex == p2_toc_counter)
				{
					strcat(n, ",");
				}
			}

			replace_all_copyright(n);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);
			outln(n);
		} else
		{
			if (label_table[i]->tocindex > p2_toc_counter)
			{
				break;
			}
		}
	}

	outln(")");

	do_toptoc(toc_table[p2_toc_counter]->toctype, popup);

	sprintf(n, "%s%s", numbers, name);
	pch_headline(n);
	outln("");
}





/*******************************************************************************
*
*  tvh_headline():
*     Headline fuer Turbo-Vision-Help
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void tvh_headline(const char *s)
{
	char n[256];
	size_t nl;

	sprintf(n, " %s \334", s);
	outln(n);
	nl = strlen(n);

	strcpy(n, "  ");
	while (strlen(n) < nl)
	{
		strcat(n, "\337");
	}
	outln(n);
	outln("");
}





/*******************************************************************************
*
*  tvh_bottomline():
*     output bottomline for Turbo-Vision-Help
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void tvh_bottomline(void)
{
	TOCIDX ci, pi, ni, ui;
	char up[256], pp[256], np[256];
	char up2[256], pp2[256], np2[256];

	if (no_bottomlines)
		return;

	c_hline();

	strcpy(up, get_lang()->contents);
	strcpy(pp, get_lang()->contents);
	np[0] = EOS;

	ci = p2_toc_counter;
	pi = toc_table[ci]->prev_index;
	ni = toc_table[ci]->next_index;

	if (toc_table[ci]->toctype >= TOC_NODE2 && toc_table[ci]->toctype < TOC_MAXDEPTH)
		ui = toc_table[ci]->up_n_index[toc_table[ci]->toctype - 1];
	else
		ui = 0;
	if (ui != 0)
		strcpy(up, toc_table[ui]->nodename);
	if (pi != 0)
		strcpy(pp, toc_table[pi]->nodename);
	if (ni != 0)
		strcpy(np, toc_table[ni]->nodename);

	strcpy(up2, up);
	node2vision(up2);
	strcpy(pp2, pp);
	node2vision(pp2);
	strcpy(np2, np);
	node2vision(np2);

	voutlnf("  { \036 :%s}", up2);
	voutf(" {%s:%s}", "\021\304", pp2);

	if (np[0] != EOS)
		voutlnf("\301{%s:%s}", "\304\020", np2);
	else
		outln("\331");

	outln("");
}





/*******************************************************************************
*
*  output_vision_header():
*     create header for Turbo-Vision-Help node
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_vision_header(const char *numbers, const char *name)
{
	char n[512];
	char l[512];
	register LABIDX i;
	size_t nl;

	strcpy(n, ".topic ");

	for (i = 1; i <= p1_lab_counter; i++)
	{
		if (label_table[i]->tocindex == p2_toc_counter)
		{
			strcpy(l, label_table[i]->name);
			node2vision(l);
			strcat(n, l);
			strcat(n, ",");
		} else if (label_table[i]->tocindex > p2_toc_counter)
		{
			break;
		}
	}

	/* Letztes Komma im .topic entfernen */
	nl = strlen(n);
	if (n[nl - 1] == ',')
	{
		n[nl - 1] = EOS;
	}
	outln(n);

	sprintf(n, "%s%s", numbers, name);
	tvh_headline(n);
}





/*******************************************************************************
*
*  output_texinfo_node():
*     output nodeline for TeXinfo
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_texinfo_node(const char *name)
{
	TOCIDX ci, pi, ni, ui;
	char n[512];
	char pp[256];
	char np[256];
	char up[256];

	strcpy(n, name);
	strcpy(up, "Top");
	strcpy(np, "");
	strcpy(pp, "Top");

	ci = p2_toc_counter;
	pi = toc_table[ci]->prev_index;
	ni = toc_table[ci]->next_index;
	if (toc_table[ci]->toctype >= TOC_NODE2 && toc_table[ci]->toctype < TOC_MAXDEPTH)
		ui = toc_table[ci]->up_n_index[toc_table[ci]->toctype - 1];
	else
		ui = 0;
	if (ui != 0)
		strcpy(up, toc_table[ui]->nodename);
	if (pi != 0)
		strcpy(pp, toc_table[pi]->nodename);
	if (ni != 0)
		strcpy(np, toc_table[ni]->nodename);

	node2texinfo(n);
	node2texinfo(np);
	node2texinfo(pp);
	node2texinfo(up);

	outln("");
	voutlnf("@node %s, %s, %s, %s", n, np, pp, up);
}





/*******************************************************************************
*
*  win_headline():
*     output topline for WinHelp
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void win_headline(char *name, _BOOL popup)
{
	char fs[32];
	TOCIDX ti;

	ti = p2_toc_counter;

	if (use_chapter_images)
	{
		if (toc_table[ti]->image != NULL)
		{
			c_begin_center();
			c_bmp_output(toc_table[ti]->image, "", FALSE);
			c_end_center();
			return;
		}
	}

	/* supress headlines if requested */
	if (no_headlines || toc_table[ti]->ignore_headline || (no_popup_headlines && popup))
		return;

	c_win_styles(name);

	if (!popup)
		outln("\\keepn");

	do_toptoc(toc_table[ti]->toctype, popup);

	sprintf(fs, "\\fs%d", iDocPropfontSize + rtf_structure_height[TOC_NODE1 + 1]);

	if (popup)
		/* voutlnf("{%s{\\b %s}}\\par\\pard\\par", fs, name) */ ;
	else
		voutlnf("{%s{\\b\\sa20\\sb20 %s}}\\par\\pard\\par", fs, name);
}



LOCAL void enable_win_button(const char *button, _BOOL enable, const char *nodename)
{
	char hlp_name[256];

	if (enable)
	{
		if (desttype == TOAQV)
		{
			strcpy(hlp_name, "qchPath");
		} else
		{
			strcpy(hlp_name, "`'");
		}
		voutlnf("!{\\footnote ! EnableButton(\"%s\");", button);
		voutlnf("ChangeButtonBinding(\"%s\", \"JumpID(%s, `%s') \") }", button, hlp_name, nodename);
	} else
	{
		voutlnf("!{\\footnote ! DisableButton(\"%s\") }", button);
	}
}


LOCAL void check_win_buttons(TOCIDX ci)
{
	int i;

	for (i = 0; i < iNumWinButtons; i++)
	{
		if (sDocWinButtonName[i][0] != '\0')
		{
			if (toc_table[ci]->win_button[i] != NULL)
			{
				char s[512];
				TOCIDX ti;
				LABIDX li;
				_BOOL isnode;
				_BOOL isalias;
				_BOOL ispopup;

				if (is_node_link(toc_table[ci]->win_button[i], s, &ti, &isnode, &isalias, &ispopup, &li))
				{
					if (desttype == TOWIN || desttype == TOWH4 || desttype == TOAQV)
					{
						if (isnode)
						{
							node2NrWinhelp(s, li);
						} else if (isalias)
						{
							alias2NrWinhelp(s, li);
						} else
						{
							label2NrWinhelp(s, li);
						}
						enable_win_button(sDocWinButtonName[i], TRUE, s);
					}
				} else
				{
					error_undefined_link(toc_table[ci]->win_button[i]);
				}
			} else
			{
				if (desttype == TOWIN || desttype == TOWH4 || desttype == TOAQV)
					enable_win_button(sDocWinButtonName[i], FALSE, NULL);
			}
		}
	}
}


/*******************************************************************************
*
*  output_win_header():
*     output header for WinHelp
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_win_header(const char *name, const _BOOL invisible)
{
	char n[512];
	char f[512];
	TOCIDX ci, ui;

	strcpy(n, name);
	del_internal_styles(n);

	outln("{");

	if (use_nodes_inside_index && !no_index && !toc_table[p2_toc_counter]->ignore_index)
	{
		strcpy(f, n);
		winspecials2ascii(f);
		voutlnf("K{\\footnote K %s}", f);
	}

	if (bDocWinOldKeywords)
	{
		strcpy(f, n);
		node2winhelp(f);
		voutlnf("#{\\footnote # %s}", f);
	}

	node2NrWinhelp(f, toc_table[p2_toc_counter]->labindex);
	voutlnf("#{\\footnote # %s}", f);
	if (toc_table[p2_toc_counter]->mapping != 0)
		voutlnf("#{\\footnote # %u}", toc_table[p2_toc_counter]->mapping);
	voutlnf("${\\footnote $ %s}", n);

	if (!no_buttons)
	{
		if (!invisible)					/* versteckte Kapitel nicht mit in die Browse-Sequence einbinden */
			outln(win_browse);

		ci = p2_toc_counter;
		if (toc_table[ci]->toctype >= TOC_NODE2 && toc_table[ci]->toctype < TOC_MAXDEPTH)
			ui = toc_table[ci]->up_n_index[toc_table[ci]->toctype - 1];
		else
			ui = 0;
		if (ui == 0)
		{
			if (called_tableofcontents)
			{
				node2NrWinhelp(n, 0);
				enable_win_button("BTN_UP", TRUE, n);
			} else
			{
				enable_win_button("BTN_UP", FALSE, NULL);
			}
		} else
		{
			node2NrWinhelp(n, toc_table[ui]->labindex);
			enable_win_button("BTN_UP", TRUE, n);
		}
		check_win_buttons(ci);
	}
}





/*******************************************************************************
*
*  get_html_filename():
*     get filename for HTML according to current node
*
*  Note:
*     UDO splittet die Files selbstaendig und benoetigt u.a. fuer die
*     Referenzen einen eindeutigen Dateinamen. Daher gelangen die Nummern
*     der Kapitel in den Dateinamen. Problem: Ab Kapitel 255 ist's mit der
*     Eindeutigkeit vorbei. Zurueckgeliefert wird nur der Name, kein Suffix
*
*  return:
*     -
*
******************************************|************************************/

LOCAL char *get_html_filename(const TOCIDX tocindex, char *s)
{
	char tmp_n[TOC_MAXDEPTH][MYFILE_NAME_LEN + 1];
	TOCIDX ti;
	int hexwidth;
	int i;

#if USE_LONG_FILENAMES
	if (!bForceShort)
		hexwidth = 3;					/* -> 001002003004005.html */
	else
		hexwidth = 2;					/* -> 0102030405.htm */
#else
	if (bForceLong)
		hexwidth = 3;					/* -> 001002003004005.html */
	else
		hexwidth = 2;					/* -> 0102030405.htm */
#endif

	ti = tocindex;

	if (outfile.file != stdout || (bTestmode && outfile.full[0] != EOS))
	{
		for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
			tmp_n[i][0] = EOS;

		if (html_merge_node[TOC_NODE1])	/* Nodes nicht splitten */
		{
			strcpy(tmp_n[TOC_NODE1], outfile.name);	/* Verweis auf Hauptfile */
		} else
		{
			ti = tocindex;				/* default */
			/* Nur zum Debuggen */
			ASSERT(ti <= p1_toc_counter);
			ASSERT(toc_table[ti] != NULL);

			if (html_merge_node[toc_table[tocindex]->toctype])
				ti = toc_table[tocindex]->up_n_index[toc_table[tocindex]->toctype - 1];

			if (toc_table[ti]->filename[0] != EOS)
			{
				/*
				 * commented out, since it will
				 * change the output filename of
				 * all subsequent nodes
				 */
#if 0
				{
					char dummy[MYFILE_PATH_LEN + 1],
					 name[MYFILE_NAME_LEN + 1],
					 suff[MYFILE_SUFF_LEN + 1];

					fsplit(toc_table[ti]->filename, dummy, dummy, name, suff);

					if (strcmp(suff, ""))
						sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, name, suff);
					else
						sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);
				}
#endif
				strcpy(tmp_n[TOC_NODE1], toc_table[ti]->filename);
			} else
			{
				if (toc_table[ti]->appendix)
				{
					sprintf(tmp_n[TOC_NODE1], "_%c", 'a' + toc_table[ti]->n[TOC_NODE1] - 1);
				} else if (toc_table[ti]->n[TOC_NODE1] == 0)
				{
					strcpy(tmp_n[TOC_NODE1], old_outfile.name);
				} else
				{
					sprintf(tmp_n[TOC_NODE1], "%0*x", hexwidth, toc_table[ti]->n[TOC_NODE1]);
				}
				for (i = TOC_NODE2; i < TOC_MAXDEPTH; i++)
					if (toc_table[ti]->n[i] != 0 && !html_merge_node[i])
						sprintf(tmp_n[i], "%0*x", hexwidth, toc_table[ti]->n[i]);
				if (toc_table[ti]->n[TOC_NODE5] > 0 && !html_merge_node[TOC_NODE5] && hexwidth == 2)
				{
					tmp_n[TOC_NODE5][0] = EOS;
					sprintf(tmp_n[TOC_NODE4], "%0*x", hexwidth, toc_table[ti]->n[TOC_NODE5] + 100);
				}
			}
		}

		s[0] = EOS;
		for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
			strcat(s, tmp_n[i]);
	} else
	{
#if USE_LONG_FILENAMES
		if (!bForceShort)
			strcpy(s, "stdout.html");
		else
			strcpy(s, "stdout.htm");
#else
		if (bForceLong)
			strcpy(s, "stdout.html");
		else
			strcpy(s, "stdout.htm");
#endif
	}

	if (s[0] == EOS)
	{
		fprintf(stderr, _("! empty filename: %d,%d,%d,%d,%d,%d,%d,%d,%d (%d)\n"),
				toc_table[ti]->n[TOC_NODE1],
				toc_table[ti]->n[TOC_NODE2],
				toc_table[ti]->n[TOC_NODE3],
				toc_table[ti]->n[TOC_NODE4],
				toc_table[ti]->n[TOC_NODE5],
				toc_table[ti]->n[TOC_NODE6],
				toc_table[ti]->n[TOC_NODE7],
				toc_table[ti]->n[TOC_NODE8],
				toc_table[ti]->n[TOC_NODE9],
				toc_table[ti]->appendix);
		fprintf(stderr, _("! using 'error' instead\n"));
		fprintf(stderr, _("! please inform the author (%s)!\n"), UDO_URL);
		strcpy(s, "error");
	}

	return s;
}




/*******************************************************************************
*
*  html_make_file():
*     create new HTML file and output header and meta information
*
*  Note:
*     wird nur fuer das jeweils aktuelle Kapitel aufgerufen
*     (durch html_new_file())
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL html_make_file(void)
{
	if (outfile.name[0] == EOS)
		return FALSE;

	if (bOutOpened)
	{
		fclose(outfile.file);			/* close the already opened file */
		bOutOpened = FALSE;
	}
#if 0
	if (html_use_folders)
	{
		if (toc_table[ti]->dirname != 0)
			sprintf(outfile.path, "%s%s", old_outfile.path, file_lookup(toc_table[ti]->dirname));
		else
			sprintf(outfile.path, "%s%04X", old_outfile.path, toc_table[ti]->n[TOC_NODE1]);

		if (toc_table[ti]->toctype == TOC_NODE1)
		{
			/* Verzeichnis anlegen, falls nicht vorhanden */
			if (toc_table[ti]->n[TOC_NODE2] == 0 && toc_table[ti]->n[TOC_NODE3] == 0
				&& toc_table[ti]->n[TOC_NODE4] == 0)
			{
				char sDir[512];

				sprintf(sDir, "%s%s", outfile.driv, outfile.path);
				my_mkdir(sDir);
			}
		}

		strcat(outfile.path, "\\");
	}
#endif
	{
		char dummy[MYFILE_PATH_LEN + 1],
		 name[MYFILE_NAME_LEN + 1],
		 suff[MYFILE_SUFF_LEN + 1];

		fsplit(outfile.name, dummy, dummy, name, suff);

		if (strcmp(suff, ""))
		{
			sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, name, suff);
		} else
			sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);
	}

	if (!bTestmode)
	{
		outfile.file = myFwopen(outfile.full, TOHTM);

		if (!outfile.file)
		{
			error_open_outfile(outfile.full);
			warning_err_destination();
			bErrorDetected = TRUE;
			bFatalErrorDetected = TRUE;
			return FALSE;
		}

		bOutOpened = TRUE;
		save_upr_entry_outfile(outfile.full);
	}

	return TRUE;
}



/*******************************************************************************
*
*  convert_toc_item():
*     remove all formatting stuff from a node name
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void convert_toc_item(TOCITEM *t)
{
	/* conversion should only be done once */
	if (!t->converted)
	{
		replace_macros(t->nodename);
		c_internal_styles(t->nodename);
		replace_udo_quotes(t->nodename);
		delete_all_divis(t->nodename);
		replace_udo_tilde(t->nodename);
		replace_udo_nbsp(t->nodename);
		
		if (t->nodename != t->nodetitle)
		{
			replace_macros(t->nodetitle);
			c_internal_styles(t->nodetitle);
			replace_udo_quotes(t->nodetitle);
			delete_all_divis(t->nodetitle);
			replace_udo_tilde(t->nodetitle);
			replace_udo_nbsp(t->nodetitle);
		}
		
		t->converted = TRUE;
	}
}




/*******************************************************************************
*
*  toc_link_output():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void toc_link_output(int depth)
{
	register TOCIDX i;
	char *htmlfilename, hfn[512], suff[12];
	char sTarget[512] = "\0";
	_BOOL genlink;
	char numbers[10 * TOC_MAXDEPTH];
	TOCTYPE d;

	if (html_frames_layout)
		sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);

	for (i = 1; i <= p1_toc_counter; i++)
	{
		if (toc_table[i] != NULL && !toc_table[i]->invisible)
		{
			convert_toc_item(toc_table[i]);

			if (toc_table[i]->n[TOC_NODE1] != 0)
			{
				if ((toc_table[i]->toctype == depth) && !(toc_table[i]->appendix))
				{
					if (depth == TOC_NODE1)
						genlink = TRUE;
					else
						genlink =
							toc_table[toc_table[i]->up_n_index[depth - 1]]->nr[depth - 1] ==
							toc_table[last_n_index[depth - 1]]->nr[depth - 1]
							&& toc_table[i]->up_n_index[depth - 1] == last_n_index[depth - 1];
					if (genlink)
					{
						sprintf(hfn, "%s%s", html_name_prefix, toc_table[i]->filename);
						htmlfilename = hfn;

						/* Feststellen, ob die Referenz im gleichen File liegt */
						if (html_merge_node[depth] == FALSE && strcmp(htmlfilename, outfile.name) != 0 &&
							html_structure_names[depth][0] != EOS)
						{
							if (strchr(htmlfilename, '.') != NULL)
								strcpy(suff, "");
							else
								strcpy(suff, outfile.suff);

							if (no_numbers)
							{
								numbers[0] = EOS;
							} else
							{
								sprintf(numbers, "%d", toc_table[i]->nr[TOC_NODE1] + toc_offset[TOC_NODE1]);
								for (d = TOC_NODE2; d <= depth; d++)
								{
									sprintf(numbers + strlen(numbers), ".%d", toc_table[i]->nr[d] + toc_offset[d]);
								}
								strcat(numbers, " ");
							}
							voutlnf("<link rel=\"%s\" href=\"%s%s\"%s title=\"%s%s\"%s>", html_structure_names[depth],
									htmlfilename, suff, sTarget, numbers, toc_table[i]->nodetitle, xhtml_closer);
						}
					}
				}

			}
		}
	}
}





/*******************************************************************************
*
*  output_html_meta():
*     output HTML meta data in the HTML head section
*
*  <???> <meta name="Subject" content="...">
*  <???> <meta name="Modification-Date" content="...">
*  <???> <meta name="Expiration-Date" content="...">
*  <???> <meta name="Language" content="...">
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_html_meta(_BOOL keywords)
{
	TOCIDX ti;
	TOCIDX i;
	int j, k;
	LABIDX li;
	STYLE *styleptr;
	SCRIPT *scriptptr;
	char s[512];						/* buffer for charset and label name */
	char htmlname[512];
	char sTarget[512];
	char backpage[256];
	char href[256];
	char alt[256];
	char *tok;

	/* get right charset name */
	strcpy(s, chr_codepage_charset_name(iEncodingTarget));

	voutlnf("<meta http-equiv=\"Content-Type\" content=\"text/html;charset=%s\"%s>", s, xhtml_closer);

#if 0
	if (html_doctype != HTML5)
#endif
	{
		voutlnf("<meta http-equiv=\"Content-Language\" content=\"%s\"%s>", get_lang()->html_lang, xhtml_closer);
		voutlnf("<meta http-equiv=\"Content-Style-Type\" content=\"text/css\"%s>", xhtml_closer);
		voutlnf("<meta http-equiv=\"Content-Script-Type\" content=\"text/javascript\"%s>", xhtml_closer);
	}

	if (html_header_date)
	{
		char zone[20];
		time_t uhrzeit;
		int hour_local, min_local, mday_local, min_utc,	hour_utc, mday_utc;
		int hours, minutes;

		if (html_header_date_zone[0] != EOS)
		{
			strcpy(zone, html_header_date_zone);
		} else
		{
			time(&uhrzeit);
			mday_local = localtime(&uhrzeit)->tm_mday;
			mday_utc = gmtime(&uhrzeit)->tm_mday;
			hour_local = localtime(&uhrzeit)->tm_hour;
			hour_utc = gmtime(&uhrzeit)->tm_hour;
			min_local = localtime(&uhrzeit)->tm_min;
			min_utc = gmtime(&uhrzeit)->tm_min;

			if (min_local < min_utc)	/* special for countries with "broken times" (e.g. Iran +03:30) */
			{
				if (mday_local != mday_utc)	/* if different days over midnight */
					hours = hour_local - hour_utc - 1 + 24;
				else
					hours = hour_local - hour_utc - 1;
				minutes = min_utc - min_local;
			} else
			{
				if (mday_local != mday_utc)	/* if different days over midnight */
					hours = hour_local - hour_utc + 24;
				else
					hours = hour_local - hour_utc;
				minutes = min_local - min_utc;
			}

			sprintf(zone, "%+03d:%02d", hours, minutes);
		}
		voutlnf("<meta name=\"date\" content=\"%d-%02d-%02dT%02d:%02d:%02d%s\"%s>",
				iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin, iDateSec, zone, xhtml_closer);
	}

	voutlnf("<meta name=\"Generator\" content=\"UDO %s\"%s>", UDO_VERSION_STRING_OS, xhtml_closer);

	if (titdat.author != NULL)
	{
		voutlnf("<meta name=\"Author\" content=\"%s\"%s>", titdat.author, xhtml_closer);
	}

	ti = p2_toc_counter;
	if (keywords)
	{
		if (toc_table[ti]->keywords != NULL)
		{
			voutlnf("<meta name=\"Keywords\" content=\"%s\"%s>", toc_table[ti]->keywords, xhtml_closer);
		} else if (titdat.keywords != NULL)
		{
			voutlnf("<meta name=\"Keywords\" content=\"%s\"%s>", titdat.keywords, xhtml_closer);
		}

		if (toc_table[ti]->description != NULL)
		{
			voutlnf("<meta name=\"Description\" content=\"%s\"%s>", toc_table[ti]->description, xhtml_closer);
		} else if (titdat.description != NULL)
		{
			voutlnf("<meta name=\"Description\" content=\"%s\"%s>", titdat.description, xhtml_closer);
		}

		if (toc_table[ti]->robots != NULL)
		{
			voutlnf("<meta name=\"robots\" content=\"%s\"%s>", toc_table[ti]->robots, xhtml_closer);
		} else if (titdat.robots != NULL)
		{
			voutlnf("<meta name=\"robots\" content=\"%s\"%s>", titdat.robots, xhtml_closer);
		}
	}

	if (titdat.contact_name != NULL)
	{
		if (html_doctype != HTML5)
			voutlnf("<meta name=\"Email\" content=\"%s\"%s>", titdat.contact_name, xhtml_closer);
		if (titdat.contact_link == NULL)
		{
			if (html_doctype != HTML5)
				voutlnf("<link rev=\"made\" href=\"mailto:%s\" title=\"E-Mail\"%s>", titdat.contact_name, xhtml_closer);
			voutlnf("<link rel=\"author\" href=\"mailto:%s\" title=\"E-Mail\"%s>", titdat.contact_name, xhtml_closer);
		}
	}
	if (titdat.contact_link != NULL)
	{
		if (html_doctype != HTML5)
			voutlnf("<link rev=\"made\" href=\"%s\" title=\"E-Mail\"%s>", titdat.contact_link, xhtml_closer);
		voutlnf("<link rel=\"author\" href=\"%s\" title=\"E-Mail\"%s>", titdat.contact_link, xhtml_closer);
	}

	*sTarget = '\0';
	if (html_frames_layout)
	{
		sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
	}

	if (html_header_links & HTML_HEADER_LINKS_CHAPTER)
	{
		TOCTYPE d;

		for (d = TOC_NODE1; d < TOC_MAXDEPTH; d++)
			toc_link_output(d);
	}

	if (html_header_links & HTML_HEADER_LINKS_NAVIGATION)
	{
		if (old_outfile.name[0] != EOS)
		{
			/* Feststellen, ob die Referenz im gleichen File liegt */
			if (strcmp(old_outfile.name, outfile.name) != 0)
			{
				voutlnf("<link rel=\"start\" href=\"%s%s\"%s title=\"%s\"%s>", old_outfile.name, outfile.suff, sTarget,
						get_lang()->html_start, xhtml_closer);

				/* Special for CAB */
				voutlnf("<link rel=\"home\" href=\"%s%s\"%s title=\"%s\"%s>", old_outfile.name, outfile.suff, sTarget,
						get_lang()->html_start, xhtml_closer);

				if (uses_tableofcontents)
				{
					voutlnf("<link rel=\"contents\" href=\"%s%s#%s\"%s title=\"%s\"%s>",
							old_outfile.name, outfile.suff, HTML_LABEL_CONTENTS, sTarget, get_lang()->contents,
							xhtml_closer);

					/* Special for CAB */
					voutlnf("<link rel=\"toc\" href=\"%s%s#%s\"%s title=\"%s\"%s>",
							old_outfile.name, outfile.suff, HTML_LABEL_CONTENTS, sTarget, get_lang()->contents,
							xhtml_closer);
				}
			}
		}

		/* Andere moegliche Angaben laut SelfHTML 6.0:
		 * <link rev="relation" href="http://www.autorshome.de/" title="Autoren-Homepage">
		 * <link rel="index" href="stichwrt.htm" title="Stichwortverzeichnis">
		 * <link rel="glossary" href="glossar.htm" title="Begriffs-Glossar">
		 * <link rel="copyright" href="rechte.htm" title="Copyright">
		 * <link rel="next" href="augsburg.htm" title="naechste Seite">
		 * <link rel="previous" href="aachen.htm" title="vorherige Seite">
		 * <link rel="help" href="hilfe.htm" title="Orientierungshilfe">
		 * <link rel="bookmark" href="hinweis.htm" title="Neuorientierung">
		 */

		/* Output of Link-Rel 'up' */
		/* is going to same place than !html_backpage */

		if (sDocHtmlBackpage[0] != EOS)
		{
			strcpy(backpage, sDocHtmlBackpage);
			tok = strtok(backpage, "\'");
			strcpy(href, tok);
			del_right_spaces(href);
			tok = strtok(NULL, "\'");
			if (tok != NULL)
			{
				strcpy(alt, tok);
				auto_quote_chars(alt, TRUE);
			} else
				strcpy(alt, href);
			/* Special for CAB */
			voutlnf("<link rel=\"up\" href=\"%s\" title=\"%s\"%s>", href, alt, xhtml_closer);
		}

		/* Output of Link-Rel 'first' */
		i = toc_table[ti]->prev_index;
		if (i > 0 && p1_toc_counter >= 1 && toc_table[1] != NULL)
		{
			/* First Node -> No Link */
			li = toc_table[1]->labindex;

			strcpy(s, label_table[li]->name);
			get_html_filename(label_table[li]->tocindex, htmlname);

			/* Special for CAB */
			if (strchr(htmlname, '.') != NULL)
				voutlnf("<link rel=\"first\" href=\"%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname, sTarget, s,
						xhtml_closer);
			else
				voutlnf("<link rel=\"first\" href=\"%s%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname,
						outfile.suff, sTarget, s, xhtml_closer);
		}

		/* Output of Link-Rel 'prev' */
		if (i > 0)
		{
			li = toc_table[i]->labindex;
			strcpy(s, label_table[li]->name);
			get_html_filename(label_table[li]->tocindex, htmlname);

			if (strchr(htmlname, '.') != NULL)
			{
				voutlnf("<link rel=\"prev\" href=\"%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname, sTarget, s,
						xhtml_closer);
				/* Special for CAB */
				voutlnf("<link rel=\"previous\" href=\"%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname, sTarget,
						s, xhtml_closer);
			} else
			{
				voutlnf("<link rel=\"prev\" href=\"%s%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname,
						outfile.suff, sTarget, s, xhtml_closer);
				/* Special for CAB */
				voutlnf("<link rel=\"previous\" href=\"%s%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname,
						outfile.suff, sTarget, s, xhtml_closer);
			}
		}

		/* Output of Link-Rel 'next' */
		i = toc_table[ti]->next_index;
		if (i > 1)
		{
			li = toc_table[i]->labindex;
			strcpy(s, label_table[li]->name);
			get_html_filename(label_table[li]->tocindex, htmlname);
			if (strchr(htmlname, '.') != NULL)
				voutlnf("<link rel=\"next\" href=\"%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname, sTarget, s,
						xhtml_closer);
			else
				voutlnf("<link rel=\"next\" href=\"%s%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname,
						outfile.suff, sTarget, s, xhtml_closer);
		}

		/* Output of Link-Rel 'last' */
		if (i > 1)
		{
			if (use_about_udo)
			{
				li = toc_table[p1_toc_counter]->labindex;
				li--;
			} else
				li = toc_table[p1_toc_counter]->labindex;

			strcpy(s, label_table[li]->name);
			get_html_filename(label_table[li]->tocindex, htmlname);

			/* Special for CAB */
			if (strchr(htmlname, '.') != NULL)
				voutlnf("<link rel=\"last\" href=\"%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname, sTarget, s,
						xhtml_closer);
			else
				voutlnf("<link rel=\"last\" href=\"%s%s%s\"%s title=\"%s\"%s>", html_name_prefix, htmlname,
						outfile.suff, sTarget, s, xhtml_closer);
		}
	}

	/* Output of Link-Rel 'copyright' */
	/* Link shows to 'About UDO'; maybe changed in future times */
	if (use_about_udo)
	{
		li = toc_table[p1_toc_counter]->labindex;
		strcpy(s, label_table[li]->name);
		get_html_filename(label_table[li]->tocindex, htmlname);

		if (strcmp(htmlname, outfile.name) != 0)
			voutlnf("<link rel=\"copyright\" href=\"%s%s\"%s title=\"%s\"%s>", htmlname, outfile.suff, sTarget, s,
					xhtml_closer);
	}

	/* Link for overall javascript files */
	for (j = 0; j < sDocScript.count; j++)
	{
		scriptptr = sDocScript.script[j];
		voutlnf("<script language=\"JavaScript\" type=\"text/javascript\" src=\"%s\"></script>",
				file_lookup(scriptptr->filename));
	}

	/* Link for file-related javascript files */
	for (j = 0; j < toc_table[ti]->scripts.count; j++)
	{
		_BOOL duplicate = FALSE;

		scriptptr = toc_table[ti]->scripts.script[j];

		for (k = 0; !duplicate && k < sDocScript.count; k++)
			if (sDocScript.script[k]->filename == scriptptr->filename)
				duplicate = TRUE;
		if (!duplicate)
			voutlnf("<script language=\"JavaScript\" type=\"text/javascript\" src=\"%s\"></script>",
					file_lookup(scriptptr->filename));
	}

	/* Link for overall stylesheet-files */
	for (j = 0; j < sDocStyle.count; j++)
	{
		styleptr = sDocStyle.style[j];

		voutlnf("<link rel=\"%sstylesheet\" type=\"text/css\" href=\"%s\"%s%s%s%s%s%s>",
				styleptr->alternate ? "alternate " : "",
				file_lookup(styleptr->filename),
				styleptr->media ? "media=\"" : "",
				styleptr->media ? styleptr->media : "",
				styleptr->media ? "\"" : "",
				styleptr->title ? "title=\"" : "", styleptr->title ? styleptr->title : "", styleptr->title ? "\"" : "");
	}

	/* Link for file-related stylesheet files */
	for (j = 0; j < toc_table[ti]->styles.count; j++)
	{
		_BOOL duplicate = FALSE;

		styleptr = toc_table[ti]->styles.style[j];

		for (k = 0; !duplicate && k < sDocStyle.count; k++)
			if (sDocStyle.style[k]->filename == styleptr->filename)
				duplicate = TRUE;
		if (!duplicate)
			voutlnf("<link rel=\"%sstylesheet\" type=\"text/css\" href=\"%s\"%s%s%s%s%s%s>",
					styleptr->alternate ? "alternate " : "",
					file_lookup(styleptr->filename),
					styleptr->media ? "media=\"" : "",
					styleptr->media ? styleptr->media : "",
					styleptr->media ? "\"" : "",
					styleptr->title ? "title=\"" : "",
					styleptr->title ? styleptr->title : "", styleptr->title ? "\"" : "");
	}

	/* Link for overall FavIcon */
	if (sDocFavIcon != 0)
		voutlnf("<link rel=\"shortcut icon\" href=\"%s\"%s>", file_lookup(sDocFavIcon), xhtml_closer);

	if (toc_table[p2_toc_counter]->bgsound != 0)
		voutlnf("<bgsound src=\"%s\">", file_lookup(toc_table[p2_toc_counter]->bgsound));
}





/*******************************************************************************
*
*  output_html_doctype():
*     output HTML doctype in HTML header
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_html_doctype(void)
{
	const char *s;

	/* get right charset name */
	s = chr_codepage_charset_name(iEncodingTarget);

	switch (html_doctype)
	{
	case HTML_OLD:
		outln("<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">");
		break;
	case HTML_STRICT:
		outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"");
		outln("        \"http://www.w3.org/TR/html4/strict.dtd\">");
		break;
	case HTML_TRANS:
		outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"");
		outln("        \"http://www.w3.org/TR/html4/loose.dtd\">");
		break;
	case HTML5:
		outln("<!DOCTYPE html>");
		break;
	case XHTML_STRICT:
		voutlnf("<?xml version=\"1.0\" encoding=\"%s\"?>", s);
		outln("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"");
		outln("        \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
		break;
	case XHTML_TRANS:
		voutlnf("<?xml version=\"1.0\" encoding=\"%s\"?>", s);
		outln("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"");
		outln("        \"http://www.w3.org/TR/xhtml1/DTD/xhtm1-transitional.dtd\">");
		break;
	}

	if (!html_header_date)
		voutlnf("<!-- last modified on %s -->", get_lang()->short_today);
}





/*******************************************************************************
*
*  html_new_file():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL _BOOL html_new_file(void)
{
	char t[512];
	char xml_lang[80];
	const char *xml_ns;

	if (outfile.file == stdout && !bTestmode)
		return TRUE;

	/* Bisherige Datei erst einmal schliessen */
	check_endnode();

	voutf("%s", sHtmlPropfontEnd);
	check_output_raw_footer(FALSE);
	outln("</body>");
	outln("</html>");

	/* Dateinamen der neuen Datei ermitteln */
#if 1
	sprintf(outfile.name, "%s%s", html_name_prefix, toc_table[p2_toc_counter]->filename);
#else
	strcpy(outfile.name, toc_table[p2_toc_counter]->filename);
#endif

	if (!html_make_file())
		return FALSE;

	output_html_doctype();

	/* Header anlegen, Aktueller Node ist bekannt */
	if (html_doctype >= XHTML_STRICT)
	{
		sprintf(xml_lang, " xml:lang=\"%s\"", get_lang()->html_lang);
		xml_ns = " xmlns=\"http://www.w3.org/1999/xhtml\"";
	} else
	{
		xml_lang[0] = EOS;
		xml_ns = "";
	}

	voutlnf("<html%s lang=\"%s\"%s>", xml_ns, get_lang()->html_lang, xml_lang);
	outln("<head>");
	outln("<title>");

	if (desttype == TOHTM || desttype == TOHAH)
	{
		if (titdat.htmltitle != NULL && titdat.htmltitle[0] != EOS)
		{
			strcpy(t, titdat.htmltitle);
		} else
		{
			strcpy(t, titleprogram);
		}
	} else
	{
		t[0] = EOS;
	}

	if (toc_table[p2_toc_counter] != NULL)
	{
		if (t[0] != EOS)
		{
			strcat(t, ": ");
		}
		strcat(t, toc_table[p2_toc_counter]->nodetitle);
	}
	outln(t);

	outln("</title>");
	output_html_meta(TRUE);
	outln("</head>");

	if (toc_table[p2_toc_counter] != NULL)
	{
		out("<body style=\"position: relative;\"");

		if (toc_table[p2_toc_counter]->backimage != 0)
		{
			voutf(" background=\"%s\"", file_lookup(toc_table[p2_toc_counter]->backimage));
		}

		if (toc_table[p2_toc_counter]->backcolor.set)
		{
			voutf(" bgcolor=\"%s\"", html_color_string(&toc_table[p2_toc_counter]->backcolor));
		}

		if (toc_table[p2_toc_counter]->textcolor.set)
		{
			voutf(" text=\"%s\"", html_color_string(&toc_table[p2_toc_counter]->textcolor));
		}

		if (toc_table[p2_toc_counter]->linkcolor.set)
		{
			voutf(" link=\"%s\"", html_color_string(&toc_table[p2_toc_counter]->linkcolor));
		}

		if (toc_table[p2_toc_counter]->alinkcolor.set)
		{
			voutf(" alink=\"%s\"", html_color_string(&toc_table[p2_toc_counter]->alinkcolor));
		}

		if (toc_table[p2_toc_counter]->vlinkcolor.set)
		{
			voutf(" vlink=\"%s\"", html_color_string(&toc_table[p2_toc_counter]->vlinkcolor));
		}

		outln(">");
	} else
	{
		outln("<body>");
	}

	check_output_raw_header();

	outln(sHtmlPropfontStart);

	output_aliasses();

	if (desttype == TOHTM || desttype == TOHAH)
		html_headline();
	else
		hh_headline();

	return TRUE;
}





/*******************************************************************************
*
*  output_html_header():
*     Wird nur fuer die Titelseite/Inhaltsverzeichnis benutzt
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void output_html_header(const char *t)
{
	char xml_lang[80];
	const char *xml_ns;

	output_html_doctype();

	if (html_doctype >= XHTML_STRICT)
	{
		sprintf(xml_lang, " xml:lang=\"%s\"", get_lang()->html_lang);
		xml_ns = " xmlns=\"http://www.w3.org/1999/xhtml\"";
	} else
	{
		xml_lang[0] = EOS;
		xml_ns = "";
	}

	voutlnf("<html%s lang=\"%s\"%s>", xml_ns, get_lang()->html_lang, xml_lang);
	outln("<head>");
	outln("<title>");
	outln(t);
	outln("</title>");

	if (desttype == TOHAH)
	{
		if (titdat.appletitle != NULL)
			voutlnf("<meta name=\"AppleTitle\" content=\"%s\"%s>", titdat.appletitle, xhtml_closer);

		if (titdat.appleicon != NULL)
			voutlnf("<meta name=\"AppleIcon\" content=\"%s\"%s>", titdat.appleicon, xhtml_closer);
	}

	output_html_meta(TRUE);				/* auch Keywords auf der ersten Seite erlauben */
	outln("</head>");

	out("<body style=\"position: relative;\"");

	if (sDocBackImage != 0)
	{
		if (!no_images)
		{
			voutf(" background=\"%s\"", file_lookup(sDocBackImage));
		}
	}

	if (sDocBackColor.rgb.set)
	{
		voutf(" bgcolor=\"%s\"", html_color_string(&sDocBackColor.rgb));
	}

	if (sDocTextColor.rgb.set)
	{
		voutf(" text=\"%s\"", html_color_string(&sDocTextColor.rgb));
	}

	if (sDocLinkColor.rgb.set)
	{
		voutf(" link=\"%s\"", html_color_string(&sDocLinkColor.rgb));
	}

	if (sDocAlinkColor.rgb.set)
	{
		voutf(" alink=\"%s\"", html_color_string(&sDocAlinkColor.rgb));
	}

	if (sDocVlinkColor.rgb.set)
	{
		voutf(" vlink=\"%s\"", html_color_string(&sDocVlinkColor.rgb));
	}

	voutlnf(">");
	check_output_raw_header();

	voutlnf("%s", sHtmlPropfontStart);
}





/*******************************************************************************
*
*  get_giflink_data():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void get_giflink_data(const int index, const char **name, _UWORD * width, _UWORD * height)
{
	*width = *height = 0;

	switch (index)
	{
	case GIF_HM_INDEX:					/* Home */
		*name = GIF_HM_NAME;
		*width = uiGifHmWidth;
		*height = uiGifHmHeight;
		break;
	case GIF_UP_INDEX:					/* Up */
		*name = GIF_UP_NAME;
		*width = uiGifUpWidth;
		*height = uiGifUpHeight;
		break;
	case GIF_LF_INDEX:					/* Left */
		*name = GIF_LF_NAME;
		*width = uiGifLfWidth;
		*height = uiGifLfHeight;
		break;
	case GIF_RG_INDEX:					/* Right */
		*name = GIF_RG_NAME;
		*width = uiGifRgWidth;
		*height = uiGifRgHeight;
		break;
	case GIF_NOHM_INDEX:				/* Home (disabled) */
		*name = GIF_NOHM_NAME;
		*width = uiGifNoHmWidth;
		*height = uiGifNoHmHeight;
		break;
	case GIF_NOUP_INDEX:				/* Up (disabled) */
		*name = GIF_NOUP_NAME;
		*width = uiGifNoUpWidth;
		*height = uiGifNoUpHeight;
		break;
	case GIF_NOLF_INDEX:				/* Left (disabled) */
		*name = GIF_NOLF_NAME;
		*width = uiGifNoLfWidth;
		*height = uiGifNoLfHeight;
		break;
	case GIF_NORG_INDEX:				/* Right (disabled) */
		*name = GIF_NORG_NAME;
		*width = uiGifNoRgWidth;
		*height = uiGifNoRgHeight;
		break;
	case GIF_GER_INDEX:				/* German */
		*name = GIF_GER_NAME;
		*width = uiGifGerWidth;
		*height = uiGifGerHeight;
		break;
	case GIF_ENG_INDEX:				/* English */
		*name = GIF_ENG_NAME;
		*width = uiGifEngWidth;
		*height = uiGifEngHeight;
		break;
	}
}


/*******************************************************************************
*
*  html_index_giflink():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_index_giflink(const int idxEnabled, const int idxDisabled, const char *sep, _BOOL head)
{
	char sTarget[64];
	char *sFile;
	char sGifSize[80];
	const char *sGifName;
	_UWORD uiW, uiH;
	const char *sIDName;					/* anchor ID name */

	sTarget[0] = sGifSize[0] = EOS;

	if (html_frames_layout)
	{
		sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
		sFile = um_strdup_printf("%s%s%s", html_name_prefix, FRAME_FILE_CON, outfile.suff);
	} else
	{
		sTarget[0] = EOS;
		sFile = um_strdup_printf("%s%s", old_outfile.name, old_outfile.suff);
	}

	if (uses_tableofcontents)
	{
		/* mark ID as unique */
		if (head)
			sIDName = "UDO_nav_up_HEAD";
		else
			sIDName = "UDO_nav_up_FOOT";

		if (no_images)
		{
			voutlnf("%s<a %s=\"%s\" href=\"%s#%s\"%s>%s</a>",
					sep, xhtml_id_attr, sIDName, sFile, HTML_LABEL_CONTENTS, sTarget,
					" ^^^" /* get_lang()->contents */ );
		} else
		{
			char border[20];

			strcpy(border, " border=\"0\"");
#if 0
			if (html_doctype == HTML5)
				border[0] = EOS;
#endif
			get_giflink_data(idxEnabled, &sGifName, &uiW, &uiH);
			sGifSize[0] = EOS;
			if (uiW != 0 && uiH != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<a %s=\"%s\" href=\"%s#%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s></a>",
					xhtml_id_attr, sIDName, sFile, HTML_LABEL_CONTENTS, sTarget, sGifName, get_lang()->contents,
					get_lang()->contents, border, sGifSize, xhtml_closer);
		}
	} else
	{
		if (no_images)
		{
			voutlnf("%s ^^^", sep);
		} else
		{
			char border[20];

			strcpy(border, " border=\"0\"");
#if 0
			if (html_doctype == HTML5)
				border[0] = EOS;
#endif
			get_giflink_data(idxDisabled, &sGifName, &uiW, &uiH);
			sGifSize[0] = EOS;
			if (uiW != 0 && uiH != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifName, border, sGifSize, xhtml_closer);
		}
	}
	free(sFile);
}



/*******************************************************************************
*
*  html_home_giflink():
*     create and output HOME link for HTML navigation bar
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_home_giflink(const int idxEnabled, const int idxDisabled, const char *sep, _BOOL head)
{
	char sTarget[64];
	char *sFile;
	char sGifSize[128];
	const char *sGifName;
	const char *sIDName;					/* anchor ID name */
	_UWORD uiW, uiH;

	switch (idxEnabled)
	{
	case GIF_HM_INDEX:
		sIDName = head ? "UDO_nav_hm_HEAD" : "UDO_nav_hm_FOOT";
		break;

	case GIF_LF_INDEX:
		sIDName = head ? "UDO_nav_lf_HEAD" : "UDO_nav_lf_FOOT";
		break;

	case GIF_RG_INDEX:
		sIDName = head ? "UDO_nav_rg_HEAD" : "UDO_nav_rg_FOOT";
		break;

	default:
		sIDName = head ? "UDO_nav_up_HEAD" : "UDO_nav_up_FOOT";
		break;
	}

	if (toc_table[p2_toc_counter]->toctype == TOC_TOC)
	{
		/* Im Inhaltsverzeichnis Link auf !html_backpage mit Home-Symbol */
		sTarget[0] = EOS;

		if (html_frames_layout)
			sprintf(sTarget, " target=\"_top\"");

		if (no_images)
		{
			voutlnf("%s%s", sep, get_lang()->html_home);
		} else
		{
			char border[20];

			strcpy(border, " border=\"0\"");
#if 0
			if (html_doctype == HTML5)
				border[0] = EOS;
#endif
			/* Button disabled ausgeben */
			get_giflink_data(idxDisabled, &sGifName, &uiW, &uiH);
			sGifSize[0] = EOS;
			if (uiW != 0 && uiH != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s>",
					sGifName, get_lang()->html_home, get_lang()->html_home, border, sGifSize, xhtml_closer);
		}
	} else
	{
		if (html_frames_layout)
		{
			sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
			sFile = um_strdup_printf("%s%s%s", html_name_prefix, FRAME_FILE_CON, outfile.suff);
		} else
		{
			sTarget[0] = EOS;
			sFile = um_strdup_printf("%s%s", old_outfile.name, old_outfile.suff);
		}

		if (no_images)
		{
			voutlnf("%s<a %s=\"%s\" href=\"%s\"%s>%s</a>", sep, xhtml_id_attr, sIDName, sFile, sTarget,
					get_lang()->html_home);
		} else
		{
			char border[20];

			strcpy(border, " border=\"0\"");
#if 0
			if (html_doctype == HTML5)
				border[0] = EOS;
#endif
			get_giflink_data(idxEnabled, &sGifName, &uiW, &uiH);
			sGifSize[0] = EOS;
			if (uiW != 0 && uiH != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<a %s=\"%s\" href=\"%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s></a>",
					xhtml_id_attr, sIDName, sFile, sTarget, sGifName, get_lang()->html_home, get_lang()->html_home,
					border, sGifSize, xhtml_closer);
		}
		free(sFile);
	}
}





/*******************************************************************************
*
*  html_back_giflink():
*     create and output link to 'back page' for HTML navigation bar
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_back_giflink(const int idxEnabled, const int idxDisabled, const char *sep, _BOOL head)
{
	char target[64];
	char backpage[256];
	char href[256];
	char alt[256];
	char *tok;
	char sGifSize[128];
	const char *sGifName;
	const char *sIDName;					/* anchor ID name */
	_UWORD uiW, uiH;

	switch (idxEnabled)
	{
	case GIF_HM_INDEX:
		sIDName = head ? "UDO_nav_hm_HEAD" : "UDO_nav_hm_FOOT";
		break;

	case GIF_LF_INDEX:
		sIDName = head ? "UDO_nav_lf_HEAD" : "UDO_nav_lf_FOOT";
		break;

	case GIF_RG_INDEX:
		sIDName = head ? "UDO_nav_rg_HEAD" : "UDO_nav_rg_FOOT";
		break;

	default:
		sIDName = head ? "UDO_nav_up_HEAD" : "UDO_nav_up_FOOT";
		break;
	}

	target[0] = EOS;

	if (sDocHtmlBackpage[0] != EOS)
	{
		strcpy(backpage, sDocHtmlBackpage);
		tok = strtok(backpage, "\'");
		strcpy(href, tok);
		del_right_spaces(href);
		tok = strtok(NULL, "\'");

		if (tok != NULL)
		{
			strcpy(alt, tok);
			auto_quote_chars(alt, TRUE);
		} else
			strcpy(alt, href);

		if (html_frames_layout)
		{
			sprintf(target, " target=\"_top\"");
		}

		if (no_images)
		{
			voutlnf("%s<a %s=\"%s\" href=\"%s\"%s>%s</a>", sep, xhtml_id_attr, sIDName, href, target, alt);
		} else
		{
			char border[20];

			strcpy(border, " border=\"0\"");
#if 0
			if (html_doctype == HTML5)
				border[0] = EOS;
#endif
			get_giflink_data(idxEnabled, &sGifName, &uiW, &uiH);
			sGifSize[0] = EOS;
			if (uiW != 0 && uiH != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<a %s=\"%s\" href=\"%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s></a>",
					xhtml_id_attr, sIDName, href, target, sGifName, alt, alt, border, sGifSize, xhtml_closer);
		}
	} else
	{
		if (no_images)
		{
			voutlnf("%s^^^", sep);
		} else
		{
			char border[20];

			strcpy(border, " border=\"0\"");
#if 0
			if (html_doctype == HTML5)
				border[0] = EOS;
#endif
			/* Disabled Button ausgeben */
			get_giflink_data(idxDisabled, &sGifName, &uiW, &uiH);
			sGifSize[0] = EOS;
			if (uiW != 0 && uiH != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifName, border, sGifSize, xhtml_closer);
		}
	}
}



/*******************************************************************************
*
*  html_hb_line():
*     create and output HTML head and bottom bar lines
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_hb_line(_BOOL head)
{
	TOCIDX i;
	TOCIDX ti;
	LABIDX li;
	char s[512];
	char anchor[512];
	char sGifSize[128];
	char sTarget[64];
	const char *colptr;
	const char *sGifFile;
	_BOOL for_main_file;
	_UWORD uiW, uiH;
	TOCTYPE level, d;

	/* set global flag */
	head_foot = head;

	/* Herausfinden, fuer welchen Node die Kopf- und Fusszeile */
	/* ausgegeben werden soll. Beim Mergen ist der Index nicht */
	/* immer gleich dem Nodezaehler im 2. Durchlauf! */

	/* Um das Tildenproblem zu loesen, muss ueber label_table[] */
	/* gegangen werden, da nur dort die Tilden noch nicht */
	/* bearbeitet wurden und nur so die Referenzen fuer die */
	/* Kopfzeilen gefunden werden! */

	ti = p2_toc_counter;

	if (ti != 0)
	{
		for (level = TOC_MAXDEPTH - 1; level >= TOC_NODE2; level--)
		{
			if (html_merge_node[level])
			{
				ti = last_n_index[level - 1];
				for (d = level - 1; d >= TOC_NODE2; d--)
					if (ti == 0)
						ti = last_n_index[d - 1];
			}
		}
		if (html_merge_node[TOC_NODE1])
		{
			ti = 0;
		}
	}

	for_main_file = (toc_table[ti]->toctype == TOC_TOC);

	/* ------------------------------------------- */
	/* ignore_headline/ignore_bottomline testen    */
	/* ------------------------------------------- */

	if (head && toc_table[ti]->ignore_headline)
		return;

	if (!head && toc_table[ti]->ignore_bottomline)
		return;

	if (!head)
	{
		if (!html_modern_layout && !html_frames_layout)
		{
			if (!((no_footers || toc_table[ti]->ignore_footer) && (no_bottomlines || toc_table[ti]->ignore_bottomline)))
			{
				outln(xhtml_hr);
				outln("");
			}
		}
	}
#if 1
	colptr = NULL;
	if (html_modern_layout)
		colptr = html_color_string(&html_modern_backcolor);
	if (html_frames_layout)
		colptr = html_color_string(&html_frames_backcolor);

	if (colptr)
	{
		s[0] = EOS;
		if (colptr[0] != EOS)
		{
			sprintf(s, " bgcolor=\"%s\"", colptr);
		}
		voutlnf("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\"%s>", s);
		voutlnf("<tr>");
#if 0
		if (html_doctype == HTML5)
		{
			voutlnf("<td class=\"UDO_td_valign_top\">");
		} else
#endif
		{
			voutlnf("<td valign=\"top\">");
		}
	}
#endif

	/* ------------------------------------------------ */
	/* Verweis auf die Homepage erzeugen                */
	/* ------------------------------------------------ */
	html_home_giflink(GIF_HM_INDEX, GIF_NOHM_INDEX, "[ ", head);

	/* ------------------------------------------------ */
	/* Verweis auf das uebergeordnete Kapitel erzeugen  */
	/* ------------------------------------------------ */
	switch (toc_table[ti]->toctype)
	{
	case TOC_NONE:						/* hmm... */
		break;

	case TOC_TOC:						/* Verweis auf Backpage erzeugen */
		html_back_giflink(GIF_UP_INDEX, GIF_NOUP_INDEX, "| ", head);
		break;

	case TOC_NODE1:					/* Weiter nach oben geht es nicht */
		/* Verweis auf index.htm erzeugen */
		html_index_giflink(GIF_UP_INDEX, GIF_NOUP_INDEX, "| ", head);
		break;

	default:							/* Verweis auf aktuellen !node */
		li = toc_table[last_n_index[toc_table[ti]->toctype - 1]]->labindex;
		strcpy(s, label_table[li]->name);
		string2reference(anchor, label_table[li]->name, li, TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
		replace_once(s, label_table[li]->name, anchor);
		if (no_images)
		{
			/* replace_once(s, ">", ">^^^ "); */
			replace_once(s, label_table[li]->name, " ^^^");
			strinsert(s, "| ");
		}
		outln(s);
		break;
	}

	/* --------------------------------------------------- */
	/* Verweis auf die vorherige Seite erzeugen            */
	/* default:            das letzte Kapitel              */
	/* !html_merge_node1:  kein Aufruf dieser Routine      */
	/* !html_merge_node2:  der letzte !node                */
	/* !html_merge_node3:  der letzte !subnode             */
	/* !html_merge_node4:  der letzte !subsubnode          */
	/* !html_merge_node5:  der letzte !subsubsubnode       */
	/* !html_merge_node6:  der letzte !subsubsubsubnode    */
	/* --------------------------------------------------- */
	if (for_main_file)
	{
		/* Deaktivierten Link/Bild ausgeben */
		if (no_images)
		{
			outln("| &lt;&lt;&lt;");
		} else
		{
			char border[20];

			strcpy(border, " border=\"0\"");
#if 0
			if (html_doctype == HTML5)
				border[0] = EOS;
#endif
			get_giflink_data(GIF_NOLF_INDEX, &sGifFile, &uiW, &uiH);
			sGifSize[0] = EOS;
			if (uiW != 0 && uiH != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifFile, border, sGifSize, xhtml_closer);
		}
	} else
	{
		i = toc_table[ti]->prev_index;

		if (i == 0)
		{
			/* Erster Node -> Zurueck zum Hauptfile */
			html_home_giflink(GIF_LF_INDEX, GIF_NOLF_INDEX, "| ", head);
		} else
		{
			if (i != 0)
			{
				li = toc_table[i]->labindex;
				strcpy(s, label_table[li]->name);
				string2reference(anchor, label_table[li]->name, li, TRUE, GIF_LF_NAME, uiGifLfWidth, uiGifLfHeight);
				replace_once(s, label_table[li]->name, anchor);
				if (no_images)
				{
					replace_once(s, label_table[li]->name, " &lt;&lt;&lt;");
					strinsert(s, "| ");
				}
				outln(s);
			} else
			{
				/* disabled nach links */
				if (no_images)
				{
					outln("| &lt;&lt;&lt;");
				} else
				{
					char border[20];

					strcpy(border, " border=\"0\"");
#if 0
					if (html_doctype == HTML5)
						border[0] = EOS;
#endif
					get_giflink_data(GIF_NOLF_INDEX, &sGifFile, &uiW, &uiH);
					sGifSize[0] = EOS;
					if (uiW != 0 && uiH != 0)
					{
						sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
					}
					voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifFile, border, sGifSize, xhtml_closer);
				}
			}
		}
	}

	/* ------------------------------------------- */
	/* Verweis auf die nachfolgende Seite erzeugen */
	/* ------------------------------------------- */
	i = 0;

	if (for_main_file)
	{
		if (p1_toc_counter != 0 && !html_merge_node[TOC_NODE1])
		{
			i = 1;
		}
	} else
	{
		i = toc_table[ti]->next_index;
		if (i != 0)
		{
			for (d = TOC_NODE2; d < TOC_MAXDEPTH; d++)
			{
				if (html_merge_node[d])
				{
					if (!(toc_table[i]->toctype >= TOC_NODE1 && toc_table[i]->toctype < d))
						i = 0;
					break;
				}
			}
		}
	}

	if (i != 0)
	{
		li = toc_table[i]->labindex;
		strcpy(s, label_table[li]->name);
		string2reference(anchor, label_table[li]->name, li, TRUE, GIF_RG_NAME, uiGifRgWidth, uiGifRgHeight);
		replace_once(s, label_table[li]->name, anchor);
		if (no_images)
		{
			replace_once(s, label_table[li]->name, " &gt;&gt;&gt;");
			strinsert(s, "| ");
		}
		outln(s);
	} else
	{
		/* disabled nach rechts */
		if (no_images)
		{
			outln("| &gt;&gt;&gt;");
		} else
		{
			char border[20];

			strcpy(border, " border=\"0\"");
#if 0
			if (html_doctype == HTML5)
				border[0] = EOS;
#endif
			get_giflink_data(GIF_NORG_INDEX, &sGifFile, &uiW, &uiH);
			sGifSize[0] = EOS;
			if (uiW != 0 && uiH != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifFile, border, sGifSize, xhtml_closer);
		}
	}

	if (html_modern_layout || html_frames_layout)
	{
		if (iDocHtmlSwitchLanguage >= 0 && sDocHtmlSwitchLanguage[0] != EOS)
		{
#if 0
			if (html_doctype == HTML5)
			{
				outln("</td><td class=\"UDO_td_valign_top UDO_td_align_right\">");
			} else
#endif
			{
				outln("</td><td valign=\"top\" align=\"right\">");
			}
			if (no_images)
			{
				switch (iDocHtmlSwitchLanguage)
				{
				case TOGER:
					voutlnf("<a href=\"%s\">Deutsch</a>", sDocHtmlSwitchLanguage);
					break;
				case TOENG:
					voutlnf("<a href=\"%s\">English</a>", sDocHtmlSwitchLanguage);
					break;
				}
			} else
			{
				char border[20];

				strcpy(border, " border=\"0\"");
#if 0
				if (html_doctype == HTML5)
					border[0] = EOS;
#endif
				if (html_frames_layout)
				{
					strcpy(sTarget, " target=\"_top\"");
				} else
				{
					sTarget[0] = EOS;
				}

				sGifSize[0] = EOS;

				switch (iDocHtmlSwitchLanguage)
				{
				case TOGER:
					get_giflink_data(GIF_GER_INDEX, &sGifFile, &uiW, &uiH);
					if (uiW != 0 && uiH != 0)
					{
						sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
					}
					voutlnf
						("<a href=\"%s\"%s><img src=\"%s\" alt=\"Deutsch\" title=\"Deutsche Version dieses Dokuments\"%s%s%s></a>",
						 sDocHtmlSwitchLanguage, sTarget, sGifFile, border, sGifSize, xhtml_closer);
					break;

				case TOENG:
					get_giflink_data(GIF_ENG_INDEX, &sGifFile, &uiW, &uiH);
					if (uiW != 0 && uiH != 0)
					{
						sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
					}
					voutlnf
						("<a href=\"%s\"%s><img src=\"%s\" alt=\"English\" title=\"English version of this document\"%s%s%s></a>",
						 sDocHtmlSwitchLanguage, sTarget, sGifFile, border, sGifSize, xhtml_closer);
					break;
				}
			}
		}
	}
#if 1
	if (html_modern_layout || html_frames_layout)
	{
		outln("</td></tr></table>");
	}
#endif

	if (no_images)
	{
		outln("]");
	}

	if (head)
	{
		if (!html_modern_layout && !html_frames_layout)
		{
			outln("");
			outln(xhtml_hr);
			outln("");
		}
	}
}



/*******************************************************************************
*
*  html_node_bar_modern():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_node_bar_modern(void)
{
	register TOCIDX i;
	LABIDX li;
	_UWORD uiW, uiH;
	char the_ref[1024];
	char *ptr;
	const char *ptrImg;
	const char *noImg = "";
	char sGifSize[80];
	char sAlignOn[128];
	char sAlignOff[128];
	char border[20];

	sGifSize[0] = EOS;

	strcpy(border, " border=\"0\"");
#if 0
	if (html_doctype == HTML5)
		border[0] = EOS;
#endif

#if 1
	voutlnf("<table %s=\"UDO_menu\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"%s\">", xhtml_id_attr,
			html_modern_width);

	switch (html_modern_alignment)
	{
	case ALIGN_LEFT:
		sprintf(sAlignOn, "<tr><td>%s", sHtmlPropfontStart);
		sprintf(sAlignOff, "%s</td></tr>", sHtmlPropfontEnd);
		break;
	case ALIGN_CENT:
#if 0
		if (html_doctype == HTML5)
		{
			sprintf(sAlignOn, "<tr><td class=\"UDO_td_align_center\">%s", sHtmlPropfontStart);
		} else
#endif
		{
			sprintf(sAlignOn, "<tr><td align=\"center\">%s", sHtmlPropfontStart);
		}
		sprintf(sAlignOff, "%s</td></tr>", sHtmlPropfontEnd);
		break;
	case ALIGN_RIGH:
#if 0
		if (html_doctype == HTML5)
		{
			sprintf(sAlignOn, "<tr><td class=\"UDO_td_align_right\">%s", sHtmlPropfontStart);
		} else
#endif
		{
			sprintf(sAlignOn, "<tr><td align=\"right\">%s", sHtmlPropfontStart);
		}
		sprintf(sAlignOff, "%s</td></tr>", sHtmlPropfontEnd);
		break;
	}
#else
	strcpy(sAlignOn, "<center>");
	strcpy(sAlignOff, "</center>");
#endif

	if (p2_toc_counter == 0 && titdat.authoricon_active != NULL)
	{
		if (titdat.authoriconActiveWidth != 0 && titdat.authoriconActiveHeight != 0)
			sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconActiveWidth,
					titdat.authoriconActiveHeight);
		voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" alt=\"\" title=\"\"%s%s%s></a>%s", sAlignOn, old_outfile.name,
				outfile.suff, titdat.authoricon_active, border, sGifSize, xhtml_closer, sAlignOff);
	} else
	{
		if (titdat.authoricon != NULL)
		{
			if (titdat.authoriconWidth != 0 && titdat.authoriconHeight != 0)
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconWidth, titdat.authoriconHeight);
			voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" alt=\"\" title=\"\"%s%s%s></a>%s",
					sAlignOn, old_outfile.name, outfile.suff, titdat.authoricon, border, sGifSize, xhtml_closer,
					sAlignOff);
		}
	}

	if (toc_table[0]->icon != NULL)
	{
		ptrImg = noImg;
		uiW = uiH = 0;

		if (toc_table[0]->icon != NULL)
		{
			ptrImg = toc_table[0]->icon;
			uiW = toc_table[0]->uiIconWidth;
			uiH = toc_table[0]->uiIconHeight;
		}

		if (toc_table[0]->icon_active != NULL)
		{
			if (p2_toc_counter == 0)
			{
				ptrImg = toc_table[0]->icon_active;
				uiW = toc_table[0]->uiIconActiveWidth;
				uiH = toc_table[0]->uiIconActiveHeight;
			}
		}

		if (ptrImg != noImg)
		{
			sGifSize[0] = EOS;

			if (uiW != 0 && uiH != 0)
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" alt=\"\" title=\"\"%s%s%s></a>%s",
					sAlignOn, old_outfile.name, outfile.suff, ptrImg, border, sGifSize, xhtml_closer, sAlignOff);
		}
	}

	for (i = 1; i <= p1_toc_counter; i++)
	{
		if (toc_table[i] != NULL)
		{
			if (toc_table[i]->toctype == TOC_NODE1 && !toc_table[i]->invisible)
			{
				convert_toc_item(toc_table[i]);
				li = toc_table[i]->labindex;

				ptrImg = noImg;
				uiW = uiH = 0;

				if (toc_table[i]->icon != NULL)
				{
					ptrImg = toc_table[i]->icon;
					uiW = toc_table[i]->uiIconWidth;
					uiH = toc_table[i]->uiIconHeight;
				}

				if (toc_table[i]->icon_active != NULL)
				{
					if (toc_table[i]->n[TOC_NODE1] == p2_toc_n[TOC_NODE1])
					{
						ptrImg = toc_table[i]->icon_active;
						uiW = toc_table[i]->uiIconActiveWidth;
						uiH = toc_table[i]->uiIconActiveHeight;
					}
				}

				string2reference(the_ref, label_table[li]->name, li, FALSE, ptrImg, uiW, uiH);

				if (ptrImg != noImg && toc_table[i]->icon_text != NULL)
				{
					ptr = strstr(the_ref, "</a>");

					if (ptr != NULL)
					{
						strinsert(ptr, toc_table[i]->icon_text);
						strinsert(ptr, xhtml_br);
					}
				}
				voutlnf("%s%s%s", sAlignOn, the_ref, sAlignOff);
			}
		} else
		{
			break;
		}
	}
	outln("</table>");
}





/*******************************************************************************
*
*  html_node_bar_frames():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_node_bar_frames(void)
{
	register TOCIDX i;
	LABIDX li;
	_UWORD uiW, uiH;
	char the_ref[1024];
	char *ptr;
	char sGifSize[80];
	const char *ptrImg;
	char alignOn[128];
	char alignOff[128];
	char divOn[40];
	char divOff[40];
	char rowOn[16];
	char rowOff[16];
	const char *noImg = "";
	char border[20];

	strcpy(border, " border=\"0\"");
#if 0
	if (html_doctype == HTML5)
		border[0] = EOS;
#endif

	switch (html_frames_position)
	{
	case POS_LEFT:
	case POS_RIGHT:
		divOn[0] = divOff[0] = rowOn[0] = rowOff[0] = EOS;

		switch (html_frames_alignment)
		{
		case ALIGN_LEFT:
			sprintf(alignOn, "<tr><td>%s", sHtmlPropfontStart);
			sprintf(alignOff, "%s</td></tr>", sHtmlPropfontEnd);
			break;
		case ALIGN_CENT:
#if 0
			if (html_doctype == HTML5)
			{
				sprintf(alignOn, "<tr><td class=\"UDO_td_align_center\">%s", sHtmlPropfontStart);
			} else
#endif
			{
				sprintf(alignOn, "<tr><td align=\"center\">%s", sHtmlPropfontStart);
			}
			sprintf(alignOff, "%s</td></tr>", sHtmlPropfontEnd);
			break;
		case ALIGN_RIGH:
#if 0
			if (html_doctype == HTML5)
			{
				sprintf(alignOn, "<tr><td class=\"UDO_td_align_right\">%s", sHtmlPropfontStart);
			} else
#endif
			{
				sprintf(alignOn, "<tr><td align=\"right\">%s", sHtmlPropfontStart);
			}
			sprintf(alignOff, "%s</td></tr>", sHtmlPropfontEnd);
			break;
		}
		outln(divOn);
		outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\">");
		outln(rowOn);
		break;

	default:
#if 0
		if (html_doctype == HTML5)
		{
			sprintf(alignOn, "<td class=\"td_nowrap\">%s", sHtmlPropfontStart);
		} else
#endif
		{
			sprintf(alignOn, "<td nowrap=\"nowrap\">%s", sHtmlPropfontStart);
		}
		sprintf(alignOff, "%s</td>", sHtmlPropfontEnd);
		strcpy(rowOn, "<tr>");
		strcpy(rowOff, "</tr>");
		switch (html_frames_alignment)
		{
		case ALIGN_LEFT:
			divOn[0] = EOS;
			divOff[0] = EOS;
			break;
		case ALIGN_CENT:
#if 0
			if (html_doctype == HTML5)
			{
				strcpy(divOn, "<div class=\"UDO_div_align_center\">");
			} else
#endif
			{
				strcpy(divOn, "<div align=\"center\">");
			}
			strcpy(divOff, "</div>");
			break;
		case ALIGN_RIGH:
#if 0
			if (html_doctype == HTML5)
			{
				strcpy(divOn, "<div class=\"UDO_div_align_right\">");
			} else
#endif
			{
				strcpy(divOn, "<div align=\"right\">");
			}
			strcpy(divOff, "</div>");
			break;
		}
		outln(divOn);
		outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">");
		outln(rowOn);
		break;
	}

	if (titdat.authoricon != NULL)
	{
		sGifSize[0] = EOS;
		if (titdat.authoriconWidth != 0 && titdat.authoriconHeight != 0)
			sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconWidth, titdat.authoriconHeight);
		voutlnf("%s<a href=\"%s%s%s\" target=\"%s\"><img src=\"%s%s\" alt=\"\" title=\"\"%s%s%s></a>%s",
				alignOn, html_name_prefix, FRAME_FILE_CON, outfile.suff,
				FRAME_NAME_CON, titdat.authoricon, "" /*sDocImgSuffix */ , border, sGifSize, xhtml_closer, alignOff);
	}

	for (i = 1; i <= p1_toc_counter; i++)
	{
		if (toc_table[i] != NULL)
		{
			if (toc_table[i]->toctype == TOC_NODE1 && !toc_table[i]->invisible)
			{
				convert_toc_item(toc_table[i]);
				li = toc_table[i]->labindex;

				ptrImg = noImg;
				uiW = uiH = 0;

				if (toc_table[i]->icon != NULL)
				{
					ptrImg = toc_table[i]->icon;
					uiW = toc_table[i]->uiIconWidth;
					uiH = toc_table[i]->uiIconHeight;
				}

				if (toc_table[i]->icon_active != NULL)
				{
					if (toc_table[i]->n[TOC_NODE1] == p2_toc_n[TOC_NODE1])
					{
						ptrImg = toc_table[i]->icon_active;
						uiW = toc_table[i]->uiIconActiveWidth;
						uiH = toc_table[i]->uiIconActiveHeight;
					}
				}

				string2reference(the_ref, label_table[li]->name, li, FALSE, ptrImg, uiW, uiH);

				/* Im Inhaltsverzeichnis DARF nicht <a href="#..."> stehen! */
				/* kleiner Zwischenhack, da Frames mit gemergten Nodes wohl */
				/* niemand ernsthaft verwenden werden wird. */

				ptr = strstr(the_ref, "href=\"#");
				if (ptr != NULL)
				{
					ptr += 6;
					strinsert(ptr, outfile.suff);
					strinsert(ptr, FRAME_FILE_CON);
					strinsert(ptr, html_name_prefix);
				}

				if (ptrImg != noImg && toc_table[i]->icon_text != NULL)
				{
					ptr = strstr(the_ref, "</a>");
					if (ptr != NULL)
					{
						strinsert(ptr, toc_table[i]->icon_text);
						strinsert(ptr, xhtml_br);
					}
				}
				voutlnf("%s%s%s", alignOn, the_ref, alignOff);
			}
		} else
		{
			break;
		}
	}
	outln(rowOff);
	outln("</table>");
	outln(divOff);
}





/*******************************************************************************
*
*  html_save_frameset():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html_save_frameset(void)
{
	char add[1024];
	char add2[256];
	char s[512];
	char f1[512];
	char f2[512];
	const char *html_lang = get_lang()->html_lang;
	
	if (html_doctype >= XHTML_STRICT)
	{
		outln("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Frameset//EN\"");
		outln("        \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd\">");
		voutlnf("<html lang=\"%s\" xml:lang=\"%s\">", html_lang, html_lang);
	} else if (html_doctype >= HTML_STRICT)
	{
		outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Frameset//EN\"");
		outln("        \"http://www.w3.org/TR/html4/frameset.dtd\">");
		voutlnf("<html lang=\"%s\">", html_lang);
	} else
	{
		output_html_doctype();
		voutlnf("<html lang=\"%s\">", html_lang);
	}

	outln("<head>");
	output_html_meta(TRUE);

	if (titdat.htmltitle != NULL && titdat.htmltitle[0] != EOS)
	{
		voutlnf("<title>%s</title>", titdat.htmltitle);
	} else
	{
		voutlnf("<title>%s</title>", titleprogram);
	}

	outln("</head>");

	add[0] = EOS;
	if (html_frames_noborder)
		strcat(add, " border=\"0\" frameborder=\"0\" framespacing=\"0\"");

	add2[0] = EOS;
	if (html_frames_noresize)
		strcat(add2, " noresize=\"noresize\"");
	if (html_frames_noscroll)
		strcat(add2, " scrolling=\"no\"");

	if (html_frames_toc_title == NULL)
	{
		sprintf(f1, "<frame src=\"%s%s%s\" %s=\"%s\" marginwidth=\"0\" marginheight=\"0\"%s%s>",
				html_name_prefix, FRAME_FILE_TOC, outfile.suff, xhtml_id_attr, FRAME_NAME_TOC, add2, xhtml_closer);
	} else
	{
		sprintf(f1, "<frame src=\"%s%s%s\" %s=\"%s\" marginwidth=\"0\" marginheight=\"0\" title=\"%s\"%s%s>",
				html_name_prefix, FRAME_FILE_TOC, outfile.suff, xhtml_id_attr, FRAME_NAME_TOC, html_frames_toc_title, add2,
				xhtml_closer);
	}

	if (html_frames_con_title == NULL)
	{
		sprintf(f2, "<frame src=\"%s%s%s\" %s=\"%s\" marginwidth=\"0\" marginheight=\"0\"%s>",
				html_name_prefix, FRAME_FILE_CON, outfile.suff, xhtml_id_attr, FRAME_NAME_CON, xhtml_closer);
	} else
	{
		sprintf(f2, "<frame src=\"%s%s%s\" %s=\"%s\" marginwidth=\"0\" marginheight=\"0\" title=\"%s\"%s>",
				html_name_prefix, FRAME_FILE_CON, outfile.suff, xhtml_id_attr, FRAME_NAME_CON, html_frames_con_title, xhtml_closer);
	}

	switch (html_frames_position)
	{
	case POS_LEFT:
		voutlnf("<frameset cols=\"%s,*\"%s>", html_frames_width, add);
		outln(f1);
		outln(f2);
		break;
	case POS_RIGHT:
		voutlnf("<frameset cols=\"*,%s\"%s>", html_frames_width, add);
		outln(f2);
		outln(f1);
		break;
	case POS_TOP:
		voutlnf("<frameset rows=\"%s,*\"%s>", html_frames_height, add);
		outln(f1);
		outln(f2);
		break;
	case POS_BOTTOM:
		voutlnf("<frameset rows=\"*,%s\"%s>", html_frames_height, add);
		outln(f2);
		outln(f1);
		break;
	}

	outln("</frameset>");

	/* Noframes for browsers who do not know frames */
	outln("<noframes>");
	c_maketitle();

	c_tableofcontents();

	/* Set both to FALSE in order that the title page and the
	   table of contents will be written in the frame again */

	called_maketitle = FALSE;
	called_tableofcontents = FALSE;
	outln("</noframes>");
	outln("</html>");

	/* Das Inhaltverzeichnis fuer den linken Frame ausgeben */

#if 1
	sprintf(outfile.name, "%s%s", html_name_prefix, FRAME_FILE_TOC);
#else
	strcpy(outfile.name, FRAME_FILE_TOC);
#endif

	if (!html_make_file())
		return;

	output_html_doctype();
	outln("<html>");
	outln("<head>");
	voutlnf("<title>%s</title>", get_lang()->contents);
	output_html_meta(FALSE);
	outln("</head>");
	add[0] = EOS;

	if (html_frames_backimage != 0)
	{
		sprintf(s, " background=\"%s\"", file_lookup(html_frames_backimage));
		strcat(add, s);
	}

	if (html_frames_backcolor.set)
	{
		sprintf(s, " bgcolor=\"%s\"", html_color_string(&html_frames_backcolor));
		strcat(add, s);
	}

	if (html_frames_linkcolor.set)
	{
		sprintf(s, " link=\"%s\"", html_color_string(&html_frames_linkcolor));
		strcat(add, s);
	}

	if (html_frames_alinkcolor.set)
	{
		sprintf(s, " alink=\"%s\"", html_color_string(&html_frames_alinkcolor));
		strcat(add, s);
	}

	if (html_frames_vlinkcolor.set)
	{
		sprintf(s, " vlink=\"%s\"", html_color_string(&html_frames_vlinkcolor));
		strcat(add, s);
	}

	voutlnf("<body%s class=\"frame_toc\">", add);

	outln(sHtmlPropfontStart);
	html_node_bar_frames();
	voutlnf("%s", sHtmlPropfontEnd);
	outln("</body>");
	outln("</html>");

	/* Neue Datei fuer das erste Kapitel anlegen */

	sprintf(outfile.name, "%s%s", html_name_prefix, FRAME_FILE_CON);
	html_make_file();
}





/*******************************************************************************
*
*  html_headline():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html_headline(void)
{
	char bgCmd[512];

	if (html_modern_layout)
	{
		bgCmd[0] = EOS;

		if (html_modern_backimage != 0)
			sprintf(bgCmd, " background=\"%s\"", file_lookup(html_modern_backimage));

		outln("<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" width=\"100%\">");
		outln("<tr>");

		if (html_modern_backcolor.set)
		{
#if 0
			if (html_doctype == HTML5)
			{
				voutlnf("<td class=\"UDO_td_valign_top\" width=\"%s\" bgcolor=\"%s\"%s>%s",
						html_modern_width, html_color_string(&html_modern_backcolor), bgCmd, sHtmlPropfontStart);
			} else
#endif
			{
				voutlnf("<td valign=\"top\" width=\"%s\" bgcolor=\"%s\"%s>%s",
						html_modern_width, html_color_string(&html_modern_backcolor), bgCmd, sHtmlPropfontStart);
			}
		} else
		{
#if 0
			if (html_doctype == HTML5)
			{
				voutlnf("<td class=\"UDO_td_valign_top\" width=\"%s\"%s>%s",
						html_modern_width, bgCmd, sHtmlPropfontStart);
			} else
#endif
			{
				voutlnf("<td valign=\"top\" width=\"%s\"%s>%s", html_modern_width, bgCmd, sHtmlPropfontStart);
			}
		}

		html_node_bar_modern();
		voutlnf("%s</td>", sHtmlPropfontEnd);
#if 0
		if (html_doctype == HTML5)
		{
			voutlnf("<td class=\"UDO_td_valign_top\" width=\"100%%\">%s", sHtmlPropfontStart);
		} else
#endif
		{
			voutlnf("<td valign=\"top\" width=\"100%%\">%s", sHtmlPropfontStart);
		}
	}

	if (!no_headlines)
		html_hb_line(TRUE);

	if (html_modern_layout || html_frames_layout)
	{
		outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\">");
		outln("<tr>");
#if 0
		if (html_doctype == HTML5)
		{
			voutlnf("<td class=\"UDO_td_valign_top\" width=\"8\">&nbsp;</td>");
			voutlnf("<td class=\"UDO_td_valign_top\" width=\"100%%\">%s", sHtmlPropfontStart);
		} else
#endif
		{
			voutlnf("<td valign=\"top\" width=\"8\">&nbsp;</td>");
			voutlnf("<td valign=\"top\" width=\"100%%\">%s", sHtmlPropfontStart);
		}
	}
}



/*******************************************************************************
*
*  html_bottomline():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html_bottomline(void)
{
	if (html_modern_layout)
	{
		voutlnf("%s", sHtmlPropfontEnd);
		html_footer();
#if 1
		outln("</td></tr></table>");
#endif
		if (!no_bottomlines)
			html_hb_line(FALSE);
		voutlnf("%s</td></tr>", sHtmlPropfontEnd);
		outln("</table>");
		return;
	}

	if (html_frames_layout)
	{
		voutlnf("%s", sHtmlPropfontEnd);
		html_footer();
#if 1
		outln("</td></tr></table>");
#endif
		if (!no_bottomlines)
			html_hb_line(FALSE);
		return;
	}

	html_footer();
	if (!no_bottomlines)
		html_hb_line(FALSE);
}



/*******************************************************************************
*
*  html_footer():
*     outputs address segment with copyright notes webmaster URL, and email
*
*  Notes:
*     This function reacts on the existance and content of the following !docinfo
*     parameters:
*
*     !docinfo [domain_link]    e.g. "http://www.mydomain.com"
*     !docinfo [domain_name]    e.g. "My Domain"
*     !docinfo [contact_link]   e.g. "mailto:webmaster@mydomain.com"
*     !docinfo [contact_name]   e.g. "Webmaster"
*
*
*     When [domain_link] and [domain_name] are available, the URL link is 
*     formatted like this: 
*     '<a href="[domain_link]">[domain_name]</a>'
*
*     When only [domain_link] is available, it is repeated in the visible link:
*     '<a href="[domain_link]">[domain_link]</a>'
*
*     When only [domain_name] is available, no link is created but the
*     [domain_name] is output as simple text in the HTML footer.
*
*
*     When [contact_link] and [contact_name] are available, the email URL 
*     link is formatted like this:
*     '<a href="mailto:[contact_link]">[contact_name]</a>
*
*     When only [contact_link] is available, it is repeated in the visible 
*     email link:
*     '<a href="mailto:[contact_link]">[contact_link]</a>
*
*     When only [contact_name] is available, no link is created but the
*     [contact_name] is output as simple text in the HTML footer.
*
*
*  Special feature:
*     Chances are that someone wants to use a web URL instead of an email address
*     [contact_link]. Today, many web users try to avoid having their email
*     address being placed visibly in web pages, to let email addresses harvester 
*     bots not find their email addresses for spam purposes. To avoid the complexity
*     to distinguish mail addresses from URLs and to give the user full control over
*     the output, the contact_link is used as it was set by
*     !docinfo [contact_link]. So mail addresses must be set as
*     "mailto:webmaster@example.com".
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html_footer(void)
{
	_BOOL has_counter;
	_BOOL has_main_counter;
	char s[512];
	int has_content = 0;

	has_counter = toc_table[p2_toc_counter]->counter_command != 0;
	has_main_counter = sCounterCommand != 0;

	if (!has_counter && !has_main_counter)
		if (no_footers || toc_table[p2_toc_counter]->ignore_footer)
			return;

	if (titdat.domain_link != NULL)
		has_content = 0x1000;

	if (titdat.domain_name != NULL)
		has_content += 0x0100;

	if (titdat.contact_link != NULL)
		has_content += 0x0010;

	if (titdat.contact_name != NULL)
		has_content += 0x0001;

	/* draw a horizontal line */
	if (has_counter || has_main_counter || has_content)
	{
		outln(xhtml_hr);
		outln("");
	}

	/* Counterkommando ausgeben */
	if (has_counter)
	{
		outln(file_lookup(toc_table[p2_toc_counter]->counter_command));
	} else if (has_main_counter)
	{
		outln(file_lookup(sCounterCommand));
	}

	if (no_footers)
		return;

	if (footer_buffer[0] != EOS)
	{
		outln(footer_buffer);
		return;
	}

	if (!has_content)
	{
		no_footers = TRUE;
		return;
	}

	/* output address segment */
	sprintf(footer_buffer, "<address>%s%s &copy; ", sHtmlPropfontStart, get_lang()->copyright);

	s[0] = EOS;							/* clear buffer */

	switch (has_content)
	{
	case 0x1111:						/* domain_link + domain_name + contact_link + contact_name */
		sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"%s\">%s</a>)",
				titdat.domain_link, titdat.domain_name, titdat.contact_link, titdat.contact_name);
		break;

	case 0x1110:						/* domain_link + domain_name + contact_link               */
		sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"%s\">%s</a>)",
				titdat.domain_link, titdat.domain_name, titdat.contact_link, titdat.contact_link);
		break;

	case 0x1101:						/* domain_link + domain_name                + contact_name */
		sprintf(s, "<a href=\"%s\">%s</a> (%s)", titdat.domain_link, titdat.domain_name, titdat.contact_name);
		break;

	case 0x1100:						/* domain_link + domain_name                               */
		sprintf(s, "<a href=\"%s\">%s</a>", titdat.domain_link, titdat.domain_name);
		break;

	case 0x1011:						/* domain_link               + contact_link + contact_name */
		sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"%s\">%s</a>)",
				titdat.domain_link, titdat.domain_link, titdat.contact_link, titdat.contact_name);
		break;

	case 0x1010:						/* domain_link               + contact_link                */
		sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"%s\">%s</a>)",
				titdat.domain_link, titdat.domain_link, titdat.contact_link, titdat.contact_link);
		break;

	case 0x1001:						/* domain_link                              + contact_name */
		sprintf(s, "<a href=\"%s\">%s</a> (%s)", titdat.domain_link, titdat.domain_link, titdat.contact_name);
		break;

	case 0x1000:						/* domain_link                                             */
		sprintf(s, "<a href=\"%s\">%s</a>", titdat.domain_link, titdat.domain_link);
		break;

	case 0x0111:						/*               domain_name + contact_link + contact_name */
		sprintf(s, "%s (<a href=\"%s\">%s</a>)", titdat.domain_name, titdat.contact_link, titdat.contact_name);
		break;

	case 0x0110:						/*               domain_name + contact_link                */
		sprintf(s, "%s (<a href=\"%s\">%s</a>)", titdat.domain_name, titdat.contact_link, titdat.contact_link);
		break;

	case 0x0101:						/*               domain_name                + contact_name */
		sprintf(s, "%s (%s)", titdat.domain_name, titdat.contact_name);
		break;

	case 0x0100:						/*               domain_name                               */
		sprintf(s, "%s", titdat.domain_name);
		break;

	case 0x0011:						/*                             contact_link + contact_name */
		sprintf(s, "<a href=\"%s\">%s</a>", titdat.contact_link, titdat.contact_name);
		break;

	case 0x0010:						/*                             contact_link                */
		sprintf(s, "<a href=\"%s\">%s</a>", titdat.contact_link, titdat.contact_link);
		break;

	case 0x0001:						/*                                            contact_name */
		sprintf(s, "%s", titdat.contact_name);
		break;
	}

	strcat(footer_buffer, s);

	if (html_doctype < XHTML_STRICT)
		strcat(footer_buffer, "<br>\n");
	else
		strcat(footer_buffer, "<br />\n");

	strcat(footer_buffer, get_lang()->update);
	strcat(footer_buffer, " ");
	strcat(footer_buffer, get_lang()->today);
	strcat(footer_buffer, sHtmlPropfontEnd);
	strcat(footer_buffer, "</address>\n");

	outln(footer_buffer);
}



/*******************************************************************************
*
*  comp_index_html():
*     Compares two index entries.
*
*  return:
*     -1: s1  < s2
*      0: s1 == s2
*      1: s1  > s2
*
******************************************|************************************/

LOCAL int comp_index_html(const void *_p1, const void *_p2)
{
	char p1_tocname[512];				/* buffer for 1st entry name in TOC */
	char p2_tocname[512];				/* buffer for 2nd entry name in TOC */

	/* cast the pointers to right structure */
	const HTML_INDEX *p1 = (const HTML_INDEX *) _p1;
	const HTML_INDEX *p2 = (const HTML_INDEX *) _p2;

	strcpy(p1_tocname, p1->sortname);	/* copy the entry names */
	strcpy(p2_tocname, p2->sortname);

	if (!html_ignore_8bit)
	{
		recode_chrtab(p1_tocname, CHRTAB_HTML);
		recode_chrtab(p2_tocname, CHRTAB_HTML);
	}
#if 0

	/* fd:2010-02-18: no longer required as we flatten HTML_INDEX.sortname first! */

	switch (iEncodingTarget)
	{
	case CODE_UTF8:					/* n-byte encodings */
		return str_UTF_sort_cmp(p1_tocname, p2_tocname);

	default:							/* 1-byte encodings */
		return str_sort_cmp(p1_tocname, p2_tocname);
	}
#endif

	return str_sort_cmp(p1_tocname, p2_tocname);
}



void toc_mark_index_referenced(void)
{
	/*
	 * mark labels as referenced if they would go into the index,
	 * even if we don't generate one for this format
	 */
	if (bCheckMisc)
	{
		LABIDX j;

		for (j = 1; j <= p1_lab_counter; j++)
		{
			if (label_table[j] != NULL && label_table[j]->ignore_index == FALSE)
				label_table[j]->referenced = TRUE;
		}
	}
}


/*******************************************************************************
*
*  save_html_index():
*     This functions creates a temporary index file for HTML index generation.
*
*  return:
*     FALSE on errors
*     TRUE  if index could be saved
*
******************************************|************************************/

GLOBAL _BOOL save_html_index(void)
{
	FILE *uif;							/* temporary index file */
	size_t i;
	LABIDX j;
	int html_merge;
	size_t num_index;					/* # of entries in index file */
	HTML_INDEX *html_index;
	_UWORD thisc;						/* single char for comparison */
	_UWORD lastc;						/* last char from comparison */
	char htmlname[512];
	char dummy[512];
	char suff[100];
	char cLabel[512];
	char *tocname;
	char jumplist[4096];				/* buffer string for A-Z navigation bar */
	char thisc_char[42];				/* buffer string for converted thisc */
	char thisc_label[42];				/* buffer string for HTML convenient converted thisc */
	TOCTYPE d;
	LABEL *l;
	num_index = 0;						/* first we count how much entries we need */

	for (j = 1; j <= p1_lab_counter; j++)	/* check all collected labels */
	{
		if ((l = label_table[j]) != NULL && l->ignore_index == FALSE)
			num_index++;
	}

	if (num_index == 0)					/* index file will not be created */
		return FALSE;

	uif = udofile_tmpname("_udoind");	/* create temp. file name */

	if (!uif)							/* no file pointer */
		return FALSE;

	fprintf(uif, "!newpage\n");			/* output index page stuff in UDO format */
	fprintf(uif, "!sloppy\n\n");
	fprintf(uif, "!node* %s\n", get_lang()->index);
	fprintf(uif, "!html_name %s\n", sDocHtmlIndexudo);

	if (!bDocAutorefOff)				/* don't auto-reference the index page! */
		fprintf(uif, "!autoref [off]\n");

	/* we need memory */
	html_index = (HTML_INDEX *) malloc(num_index * sizeof(HTML_INDEX));

	if (html_index == NULL)				/* fatal error! */
	{
		fclose(uif);
		error_malloc_failed(num_index * sizeof(HTML_INDEX));
		return FALSE;
	}


	/* --- create index array --- */

	num_index = 0;

	for (j = 1; j <= p1_lab_counter; j++)
	{
		if ((l = label_table[j]) != NULL && l->ignore_index == FALSE)
		{
			l->referenced = TRUE;
			html_index[num_index].toc_index = l->tocindex;
			html_index[num_index].is_node = l->is_node;

			/* set ^ to name field in structure */
			tocname = html_index[num_index].tocname;
			strcpy(tocname, l->name);	/* copy name to structure */

			replace_macros(tocname);
			c_internal_styles(tocname);
			delete_all_divis(tocname);
			replace_udo_tilde(tocname);
			replace_udo_nbsp(tocname);
			del_html_styles(tocname);

			/* copy the name as we are going to flatten it */
			strcpy(html_index[num_index].sortname, tocname);

			/* get character for sorting purposes */
			html_index[num_index].codepoint = str_flatten(html_index[num_index].sortname);

			num_index++;
			/* ignore Table of Contents! */
			if (strcmp(tocname, HTML_LABEL_CONTENTS) == 0)
				num_index--;
			/* ignore indexudo page! */
			if (strcmp(tocname, get_lang()->index) == 0)
				num_index--;
		}
	}


	/* --- sort the index (by HTML_INDEX.sortname!) --- */

	qsort(html_index, num_index, sizeof(HTML_INDEX), comp_index_html);


	/* --- create index A-Z jumplist --- */

	lastc = EOS;						/* clear buffer for last character */

	strcpy(jumplist, "<div class=\"UDO_index_list\">\n");

	for (i = 0; i < num_index; i++)
	{
		thisc = html_index[i].codepoint;

		unicode2char(thisc, thisc_label);
		strcpy(thisc_char, thisc_label);	/* just convert it once, we need it often */

		label2html(thisc_label);		/* convert critical characters to HTML standards */

		if (thisc != lastc)
		{
			/* set anchor entry for index A-Z list */
			if (lastc == EOS)
				sprintf(dummy, "<a href=\"#%s\">%s</a>\n", thisc_label, thisc_char);
			else
				sprintf(dummy, " | <a href=\"#%s\">%s</a>\n", thisc_label, thisc_char);

			strcat(jumplist, dummy);

			lastc = thisc;
		}
	}

	strcat(jumplist, "</div>  <!-- UDO_index_list -->\n");


	/* --- output index --- */

	fprintf(uif, "!begin_raw\n");

	fprintf(uif, "%s", jumplist);		/* output A-Z jumplist */

	lastc = EOS;						/* reset buffer for last character */

	for (i = 0; i < num_index; i++)
	{
		thisc = html_index[i].codepoint;

		unicode2char(thisc, thisc_label);
		strcpy(thisc_char, thisc_label);	/* just convert it once, we need it often */

		label2html(thisc_label);		/* convert critical characters to HTML standards */

		if (thisc != lastc)
		{
			if (lastc != EOS)			/* close previous character group of index entries */
				fprintf(uif, "</p>\n");

			/* start index group */
			fprintf(uif, "\n<p class=\"UDO_index_group\">\n");

			if (num_index > 100)		/* set jump entry for index A-Z list */
			{
				fprintf(uif, "<span class=\"UDO_index_name\"><a %s=\"%s\"></a>%s</span>%s\n",
						xhtml_id_attr, thisc_label, thisc_char, xhtml_br);
			} else
				fprintf(uif, "<a %s=\"%s\"></a>\n", xhtml_id_attr, thisc_label);

			lastc = thisc;
		}

		strcpy(dummy, html_index[i].tocname);

		if (!html_ignore_8bit)
			recode_chrtab(dummy, CHRTAB_HTML);	/* convert HTML characters to system characters  */

		get_html_filename(html_index[i].toc_index, htmlname);

		html_merge = FALSE;
		for (d = TOC_NODE1; d <= toc_table[html_index[i].toc_index]->toctype; d++)
			if (html_merge_node[d])
				html_merge = TRUE;

		if (html_index[i].is_node)		/* this index entry points to another file */
		{
			fsplit(htmlname, dummy, dummy, dummy, suff);

			strcpy(cLabel, html_index[i].tocname);
			label2html(cLabel);

			if (suff[0] == EOS)
			{
				if (html_merge)
				{
					fprintf(uif, "<a href=\"%s%s#%s\">%s</a>", htmlname, outfile.suff, cLabel, html_index[i].tocname);
				} else
				{
					fprintf(uif, "<a href=\"%s%s\">%s</a>", htmlname, outfile.suff, html_index[i].tocname);
				}
			} else
			{
				if (html_merge)
				{
					fprintf(uif, "<a href=\"%s#%s\">%s</a>", htmlname, cLabel, html_index[i].tocname);
				} else
				{
					fprintf(uif, "<a href=\"%s\">%s</a>", htmlname, html_index[i].tocname);
				}
			}
			fprintf(uif, "%s\n", HTML_BR);	/* end the entry line */
		} else							/* this index entry is a label in another file */
		{
			strcpy(cLabel, html_index[i].tocname);

			if (!no_index && use_label_inside_index)
			{
				label2html(cLabel);

				fprintf(uif, "<a href=\"%s%s#%s\">%s</a>", htmlname, outfile.suff, cLabel, html_index[i].tocname);

				fprintf(uif, "%s\n", HTML_BR);	/* end the entry line */
			}
		}
	}

	fprintf(uif, "</p>\n\n");

	fprintf(uif, "%s", jumplist);		/* repeat A-Z jumplist */

	fprintf(uif, "!end_raw\n");

	fclose(uif);

	token_reset();

	strcpy(token[0], "!include");		/* sollte safe sein, da ein Token auf jeden Fall so lang werden kann :-) [vj] */

	um_strcpy(token[1], udofile.full, MAX_TOKEN_LEN + 1, "save_html_index [2]");

	token_counter = 2;

	c_include();

/* printf("%s\n", udofile.full); */
	remove(udofile.full);

	free((void *) html_index);

	return TRUE;
}





/*******************************************************************************
*
*  add_pass1_index_udo():
*     ???
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void add_pass1_index_udo(void)
{
	save_html_index();
	token_reset();
}





/*******************************************************************************
*
*  hh_headline():
*     ???
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void hh_headline(void)
{
#if 0
	if (!no_headlines)
		html_hb_line(TRUE);
#endif
}





/*******************************************************************************
*
*  hh_bottomline():
*     ???
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void hh_bottomline(void)
{
#if 0
	if (!no_bottomlines)
		html_hb_line(FALSE);
#endif
}



LOCAL void print_indent(FILE * file, int level)
{
	int i;

	for (i = 0; i < level; i++)
		fprintf(file, "\t");
}




/*******************************************************************************
*
*  print_htmlhelp_contents():
*     ???
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void print_htmlhelp_contents(FILE * file, int indent, const TOCIDX ti)
{
	char filename[MYFILE_FULL_LEN];
	char tocname[MAX_NODE_LEN + 1];

	if (ti != 0)
	{
		get_html_filename(ti, filename);
		strcpy(tocname, toc_table[ti]->nodetitle);
	} else
	{
		strcpy(filename, old_outfile.name);
		tocname[0] = EOS;
		if (tocname[0] == EOS && titleprogram[0] != EOS)
			strcpy(tocname, titleprogram);
		if (tocname[0] == EOS && called_tableofcontents)
			strcpy(tocname, get_lang()->contents);
		if (tocname[0] == EOS && called_maketitle)
			strcpy(tocname, get_lang()->title);
	}
	del_html_styles(tocname);

	print_indent(file, indent);
	fprintf(file, "<LI> <OBJECT type=\"text/sitemap\">\n");
	print_indent(file, indent + 1);
	fprintf(file, "<param name=\"Name\" value=\"%s\">\n", tocname);
	print_indent(file, indent + 1);
	fprintf(file, "<param name=\"Local\" value=\"%s%s\">\n", filename, outfile.suff);
	print_indent(file, indent);
	fprintf(file, "</OBJECT></LI>\n");
}





/*******************************************************************************
*
*  save_htmlhelp_contents():
*     ???
*
*  return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

GLOBAL _BOOL save_htmlhelp_contents(const char *filename)
{
	FILE *file;
	register TOCIDX i;
	int last_depth;
	_BOOL inApx = FALSE;
	int d;

	file = myFwopen(filename, FTHHC);

	if (file == NULL)
		return FALSE;

	save_upr_entry_outfile(filename);

	fprintf(file, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n");
	fprintf(file, "<HTML>\n");
	fprintf(file, "<HEAD>\n");
	fprintf(file, "<meta name=\"GENERATOR\" content=\"UDO %s\">\n", UDO_VERSION_STRING_OS);
	fprintf(file, "<!-- Sitemap 1.0 -->\n");
	fprintf(file, "</HEAD>\n");
	fprintf(file, "<BODY>\n");

	fprintf(file, "<UL>\n");
	print_htmlhelp_contents(file, 1, 0);	/* Eintrag fuer erste Seite */
	fprintf(file, "</UL>\n");

	last_depth = TOC_NODE1 - 1;

	for (i = 1; i <= p1_toc_counter; i++)
	{
		if (toc_table[i] != NULL && !toc_table[i]->invisible)
		{
			convert_toc_item(toc_table[i]);

			if (!inApx && toc_table[i]->appendix)
			{
				char linkfilename[512];

				for (d = last_depth; d >= TOC_NODE1; d--)
				{
					print_indent(file, d);
					fprintf(file, "</UL>\n");
				}
				inApx = TRUE;
				last_depth = TOC_NODE1 - 1;

				fprintf(file, "<UL>\n");
				print_indent(file, 1);
				fprintf(file, "<LI> <OBJECT type=\"text/sitemap\">\n");
				print_indent(file, 1);
				fprintf(file, "\t<param name=\"Name\" value=\"%s\">\n", get_lang()->appendix);
				print_indent(file, 1);
				get_html_filename(i, linkfilename);
				fprintf(file, "\t<param name=\"Local\" value=\"%s%s\">\n", linkfilename, outfile.suff);
				print_indent(file, 1);
				fprintf(file, "</OBJECT></LI>\n");
			}

			if (toc_table[i]->n[TOC_NODE1] != 0)
			{
				for (d = last_depth; d > toc_table[i]->toctype; d--)
				{
					print_indent(file, d + inApx);
					fprintf(file, "</UL>\n");
				}
				for (d = last_depth; d < toc_table[i]->toctype; d++)
				{
					print_indent(file, d + 1 + inApx);
					fprintf(file, "<UL>\n");
				}
				last_depth = toc_table[i]->toctype;
				print_htmlhelp_contents(file, last_depth - TOC_NODE1 + 1 + inApx, i);
			}
		}
	}

	for (d = last_depth + inApx; d >= TOC_NODE1; d--)
	{
		print_indent(file, d);
		fprintf(file, "</UL>\n");
	}

	fprintf(file, "</BODY>\n");
	fprintf(file, "</HTML>\n");

	fclose(file);

	return TRUE;
}





/*******************************************************************************
*
*  comp_index():
*     compares two index entries
*
*  return:
*     < 0, when s1 is smaller than s2
*     = 0, when s1 and s2 are identical
*     > 0, when s1 is greater than s2
*
******************************************|************************************/

LOCAL int comp_index(const void *_p1, const void *_p2)
{
	const HTML_IDX *p1 = (const HTML_IDX *) _p1;
	const HTML_IDX *p2 = (const HTML_IDX *) _p2;

	return strcmp(p1->tocname, p2->tocname);
}





/*******************************************************************************
*
*  save_htmlhelp_index():
*     ???
*
*  return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

GLOBAL _BOOL save_htmlhelp_index(const char *filename)
{
	FILE *file;
	size_t i;
	LABIDX j;
	size_t num_index;
	HTML_IDX *html_index;
	char htmlname[MYFILE_FULL_LEN];
	char *tocname;
	char cLabel[512];
	int html_merge;
	TOCTYPE d;
	LABEL *l;

	if (no_index)
		return FALSE;					/* Index-File wird nicht gewuenscht */

	/* erstmal zaehlen wieviel wir brauchen */
	num_index = 0;
	for (j = 1; j <= p1_lab_counter; j++)
		if ((l = label_table[j]) != NULL && !l->ignore_index)
			num_index++;

	if (num_index == 0)
		return FALSE;					/* Index-File wird nicht gebraucht */

	file = myFwopen(filename, FTHHK);

	if (file == NULL)
		return FALSE;

	html_index = (HTML_IDX *) malloc(num_index * sizeof(HTML_IDX));
	if (html_index == NULL)
	{
		fclose(file);
		error_malloc_failed(num_index * sizeof(HTML_IDX));
		return FALSE;
	}

	save_upr_entry_outfile(filename);

	fprintf(file, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n");
	fprintf(file, "<HTML>\n");
	fprintf(file, "<HEAD>\n");
	fprintf(file, "<meta name=\"GENERATOR\" content=\"UDO %s\">\n", UDO_VERSION_STRING_OS);
	if (titdat.author != NULL)
		fprintf(file, "<meta name=\"Author\" content=\"%s\">\n", titdat.author);
	fprintf(file, "<!-- Sitemap 1.0 -->\n");
	fprintf(file, "</HEAD>\n");
	fprintf(file, "<BODY>\n");
	fprintf(file, "<UL>\n");

	/* array aufbauen.. */
	num_index = 0;
	for (j = 1; j <= p1_lab_counter; j++)
	{
		if ((l = label_table[j]) != NULL && !l->ignore_index)
		{
			l->referenced = TRUE;
			html_index[num_index].toc_index = l->tocindex;
			html_index[num_index].is_node = l->is_node;
			tocname = html_index[num_index].tocname;
			strcpy(tocname, l->name);
			replace_macros(tocname);
			c_internal_styles(tocname);
/*       replace_udo_quotes(tocname); */
			delete_all_divis(tocname);
			replace_udo_tilde(tocname);
			replace_udo_nbsp(tocname);
			del_html_styles(tocname);
			/*
			 * if label was a nodename,
			 * then recoding did already occur, and we must not do
			 * it again, otherwise the '&' in entity names would be replaced
			 * by '&amp;'
			 * If it was from !index however,
			 * we must recode here. sigh.
			 */
			if (!l->is_node && l->is_alias)
				recode_chrtab(tocname, CHRTAB_HTML);
			num_index++;
		}
	}

	show_status_info(_("Sorting index..."));
	/* ..sortieren */
	qsort(html_index, num_index, sizeof(HTML_IDX), comp_index);

	/* ..und ausgeben */
	for (i = 0; i < num_index; i++)
	{
		get_html_filename(html_index[i].toc_index, htmlname);

		html_merge = FALSE;
		for (d = TOC_NODE1; d <= toc_table[html_index[i].toc_index]->toctype; d++)
			if (html_merge_node[d])
				html_merge = TRUE;

		if (html_merge || !html_index[i].is_node)
		{
			strcpy(cLabel, html_index[i].tocname);
			label2html(cLabel);
			fprintf(file,
					"<LI> <OBJECT type=\"text/sitemap\"> <param name=\"Name\" value=\"%s\"> <param name=\"Local\" value=\"%s%s#%s\"> </OBJECT> </LI>\n",
					html_index[i].tocname, htmlname, outfile.suff, cLabel);
		} else
		{
			fprintf(file,
					"<LI> <OBJECT type=\"text/sitemap\"> <param name=\"Name\" value=\"%s\"> <param name=\"Local\" value=\"%s%s\"> </OBJECT> </LI>\n",
					html_index[i].tocname, htmlname, outfile.suff);
		}
	}

	fprintf(file, "</UL>\n");
	fprintf(file, "</BODY>\n");
	fprintf(file, "</HTML>\n");
	fclose(file);

	free(html_index);

	return TRUE;
}










/*******************************************************************************
*
*     CHAPTER COMMANDS
*
******************************************|************************************/

/*******************************************************************************
*
*  set_inside_node():
*     sets active_nodetype variable
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void set_inside_node(TOCTYPE nodetype)
{
	active_nodetype = nodetype;
}





/*******************************************************************************
*
*  make_node():
*     handle start of a new node of the requested depth during pass2()
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void make_node(TOCTYPE currdepth, const _BOOL popup, _BOOL invisible)
{
	char n[512];
	char k[512];
	char name[512];
	char stgname[512];
	char hx_start[16];
	char hx_end[16];
	char numbers[512];
	char nameNoSty[512];
	char sTemp[512];
	char map[64];
	char sGifSize[80];
	char nodename[512];
	const char *toptitle = NULL;

	TOCIDX chapter;
	TOCIDX nr1;
	_BOOL flag;
	_BOOL do_index;
	TOCTYPE d;
	TOCIDX ui;
	char border[20];
	TOCITEM *toc;
	
	strcpy(border, " border=\"0\"");
#if 0
	if (html_doctype == HTML5)
		border[0] = EOS;
#endif

	ASSERT(p2_toc_counter < p1_toc_counter);
	if (p2_toc_counter >= p1_toc_counter)
	{
		bBreakInside = TRUE;
		return;
	}
	
	tokcpy2(name, ArraySize(name));
	strcpy(stgname, name);

	if (name[0] == EOS)
	{
		error_missing_parameter("!node");
		return;
	}

	ASSERT(p2_lab_counter < p1_lab_counter);
	p2_lab_counter++;
	p2_toctype = currdepth;

	if ((desttype == TOHTM || desttype == TOHAH) && !html_merge_node[currdepth])
	{
		check_endnode();
		html_bottomline();
	}

	if (desttype == TOMHH)
	{
		check_endnode();
		hh_bottomline();
	}

	/* Texinfo kennt keine versteckten Kapitel */
	if (desttype == TOINF)
		invisible = FALSE;

	check_styles(name);
	c_styles(name);

	switch (desttype)
	{
	case TOWIN:
	case TOWH4:
	case TOAQV:
		c_win_styles(name);
		break;
	case TORTF:
		c_rtf_styles(name);
		c_rtf_quotes(name);
		break;
	default:
		c_internal_styles(name);
		break;
	}

	replace_udo_quotes(name);
	delete_all_divis(name);
	replace_udo_tilde(name);
	replace_udo_nbsp(name);

	check_endnode();
	check_styleflags();
	check_environments_node();

	if (bInsideAppendix)
	{
		p2_apx_n[currdepth]++;
		for (d = currdepth + 1; d < TOC_MAXDEPTH; d++)
			p2_apx_n[d] = 0;
	} else
	{
		p2_toc_n[currdepth]++;
		for (d = currdepth + 1; d < TOC_MAXDEPTH; d++)
			p2_toc_n[d] = 0;
	}

	p2_toc_counter++;
	toc = toc_table[p2_toc_counter];

	last_n_index[currdepth] = p2_toc_counter;
	for (d = currdepth + 1; d < TOC_MAXDEPTH; d++)
		last_n_index[d] = 0;

	nr1 = toc->nr[TOC_NODE1];
	chapter = bInsideAppendix ? nr1 : nr1 + toc_offset[TOC_NODE1];

	n[0] = EOS;
	numbers[0] = EOS;

	if (!invisible)
	{
		if (bInsideAppendix)
		{
			sprintf(numbers, "%c", 'A' + nr1 - 1);
		} else
		{
			sprintf(numbers, "%d", chapter);
		}
		for (d = TOC_NODE2; d <= currdepth; d++)
			sprintf(numbers + strlen(numbers), ".%d", toc->nr[d] + toc_offset[d]);
	} else
	{
		strcpy(numbers, "*");
	}

	if (bVerbose)
	{
		char sInfMsg[256];

		sprintf(sInfMsg, "[%s] ", numbers);
		show_status_node(sInfMsg, name);
	}

	if (no_numbers || invisible)
		numbers[0] = EOS;
	else
		strcat(numbers, " ");

	strcpy(current_chapter_name, name);
	strcpy(current_chapter_nr, numbers);

	do_index = (use_nodes_inside_index && !no_index && !toc->ignore_index);

	if (desttype != TOWIN && desttype != TOWH4 && desttype != TOAQV && bCheckMisc)
		check_win_buttons(p2_toc_counter);

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		set_inside_node(currdepth);
		outln("");
		if (use_style_book || currdepth >= TOC_MAXDEPTH)
			voutlnf("\\%s%s{%s}", tex_structure_names[currdepth], invisible ? "*" : "", name);
		else
			voutlnf("\\%s%s{%s}", tex_structure_names[currdepth + 1], invisible ? "*" : "", name);
		label2tex(name);
		voutlnf("\\label{%s}", name);
		if (desttype == TOPDL)
		{
			voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
			/*
			 * The node name here has already been translated to TeX
			 * (i.e. transformed by c_vars()).
			 * The text argument to \pdfoutline however is directly written to the PDF output and thus
			 * may not contain any TeX commands.
			 * That includes specials like \LaTeX as well as any
			 * sequences from character encoding like {\"a"}
			 */
			strcpy(name, stgname);
			delete_all_divis(name);
			del_internal_styles(name);
			replace_udo_quotes(name);
			qreplace_all(name, TILDE_S, TILDE_S_LEN, "~", 1);
			replace_udo_nbsp(name);
			replace_all(name, "\\ldots{}", "...");
			replace_all(name, "-{}-{}-", "---");
			replace_all(name, "-{}-", "--");
			replace_all(name, "\\verb/;-)/", ";-");
			replace_all(name, "\\verb/:-)/", ":-)");
			replace_all(name, "\\TeX{}", "TeX");
			replace_all(name, "\\LaTeX{}", "LaTeX");
			replace_all(name, "\\LaTeXe{}", "LaTeXe");
			replace_all(name, "\\copyright{}", "\033\003AAA\033");
			replace_all(name, "\\textregistered{}", "\033\003AAB\033");
			replace_all(name, "$\\alpha$", "alpha");
			replace_all(name, "$\\beta$", "beta");
			replace_all(name, "\\euro{}", "\033\003AAC\033");
			replace_all(name, "\\pounds{}", "\033\003AAD\033");
			replace_all(name, "\\texttrademark{}", "\033\003AAE\033");
			replace_all(name, "$^{o}$", get_lang()->degree);
			replace_all(name, "{\\\"a}", "ä");
			replace_all(name, "{\\\"o}", "ö");
			replace_all(name, "{\\\"u}", "ü");
			replace_all(name, "{\\\"A}", "Ä");
			replace_all(name, "{\\\"O}", "Ö");
			replace_all(name, "{\\\"U}", "Ü");
			replace_all(name, "{\\\"O}", "Ö");
			replace_all(name, "{\\ss}", "ß");
			replace_all(name, "``", "`");
			replace_all(name, "\"`", "`");
			replace_all(name, "''", "'");
			replace_all(name, "\"'", "'");
			replace_all(name, "\\symbol{34}\\symbol{34}", "\"\"");
			replace_all(name, "\\symbol{39}\\symbol{39}", "''");
			replace_all(name, "{\\symbol{34}}", "\"");
			replace_all(name, "$\\backslash$", "\\");
			replace_all(name, "\\_", "_");
			replace_all(name, "\\$", "$");
			replace_all(name, "\\#", "#");
			replace_all(name, "\\%", "%");
			replace_all(name, "\\&", "&");
			replace_all(name, "$<$", "<");
			replace_all(name, "$>$", ">");
			replace_all(name, "$\\mid$", "|");
			replace_all(name, "{\\symbol{94}}", "^");
			replace_all(name, "{\\symbol{96}}", "`");
			replace_all(name, "\\{", "{");
			replace_all(name, "\\}", "}");
			replace_all(name, "%", "\\%");
			replace_all(name, "~", " ");
			replace_all(name, "\\", "\\doublebackslash%\n");
			replace_all(name, "(", "\\realbackslash(%\n");
			replace_all(name, ")", "\\realbackslash)%\n");
			replace_all(name, "\033\003AAA\033", "\\251");	/* copyright */
			replace_all(name, "\033\003AAB\033", "\\256");	/* registered */
			replace_all(name, "\033\003AAC\033", "\\244");	/* euro */
			replace_all(name, "\033\003AAD\033", "\\243");	/* pounds */
			replace_all(name, "\033\003AAE\033", "\\231");	/* trademark */

			voutlnf("\\pdfoutline goto num %d count %d {(%s)}", p2_lab_counter, toc->num_children,
					name);
		}
		output_aliasses();
		break;

	case TOLYX:
		set_inside_node(currdepth);
		out("\\layout ");
		if (use_style_book || currdepth >= TOC_MAXDEPTH)
			voutlnf("%s%s", lyx_structure_names[currdepth], invisible ? "*" : "");
		else
			voutlnf("%s%s", lyx_structure_names[currdepth + 1], invisible ? "*" : "");
		indent2space(name);
		outln(name);
		outln("");
		output_aliasses();
		label2lyx(name);
		voutlnf("\\begin_inset LatexCommand \\label{%s}", name);
		voutlnf("\\end_inset");
		break;

	case TOINF:
		set_inside_node(currdepth);
		output_texinfo_node(name);
		voutlnf("@%s %s", info_structure_names[currdepth][bInsideAppendix][invisible], name);
		break;

	case TOTVH:
		set_inside_node(currdepth);
		if (numbers[0] != EOS)
			strcat(numbers, " ");
		output_vision_header(numbers, name);
		break;

	case TOSTG:
		stg_out_endnode();
		set_inside_node(currdepth);
		node2stg(name);

		if (!do_index)
			outln("@indexoff");

		if (popup)
			voutlnf("@pnode \"%s\"", name);
		else
			voutlnf("@node \"%s\"", name);
		if (toc->nodetitle != toc->nodename)
		{
			strcpy(stgname, toc->nodetitle);
			voutlnf("@title \"%s\"", stgname);
		}

		if (!do_index)
			outln("@indexon");

		if (!popup)
		{
			if (currdepth == TOC_NODE1)
			{
				if (called_tableofcontents)
					outln("@toc \"Main\"");
			} else
			{
				ui = toc->up_n_index[currdepth - 1];
				if (ui != 0)
				{
					strcpy(sTemp, toc_table[ui]->nodename);
					node2stg(sTemp);
					voutlnf("@toc \"%s\"", sTemp);
				}
			}
		}
		stg_header(numbers, stgname, popup);
		break;

	case TOAMG:
		stg_out_endnode();
		set_inside_node(currdepth);

		node2stg(name);

		if (titleprogram[0] != EOS)
			voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
		else
			voutlnf("@node \"%s\" \"%s\"", name, name);
		if (toc->nodetitle != toc->nodename)
		{
			strcpy(stgname, toc->nodetitle);
			/* AmigaGuide has no @title command
			voutlnf("@title \"%s\"", stgname);
			*/
		}
		if (currdepth == TOC_NODE1)
		{
			if (called_tableofcontents)
				outln("@toc \"Main\"");
		} else
		{
			ui = toc->up_n_index[currdepth - 1];
			if (ui != 0)
			{
				strcpy(sTemp, toc_table[ui]->nodename);
				node2stg(sTemp);
				voutlnf("@toc \"%s\"", sTemp);
			}
		}
		stg_header(numbers, stgname, FALSE);
		break;

	case TOMAN:
		set_inside_node(currdepth);
		outln("");
		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		my_strupr(name);
		if (currdepth <= TOC_NODE2)
			sprintf(n, " %s%s%s", BOLD_ON, name, BOLD_OFF);
		else
			sprintf(n, " %s", name);
		c_internal_styles(n);
		outln(n);
		break;

	case TONRO:
		set_inside_node(currdepth);
		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		my_strupr(name);
		sprintf(n, "%s %s", currdepth == TOC_NODE1 ? ".SH" : currdepth == TOC_NODE2 ? ".SS" : ".TP\n.SS", name);
		c_internal_styles(n);
		outln(n);
		break;

	case TOASC:
		set_inside_node(currdepth);

		if (numbers[0] != EOS)
			strcat(numbers, " ");

		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		if (currdepth == TOC_NODE1)
		{
			outln("");
			outln("");

			if (use_style_book)
			{
				sprintf(n, "%s %s", bInsideAppendix ? get_lang()->appendix : get_lang()->chapter, numbers);
				del_right_spaces(n);
				output_ascii_line("=", zDocParwidth);
				outln(n);
				outln("");
				outln(name);
				output_ascii_line("=", zDocParwidth);
			} else
			{
				sprintf(n, "%s%s", numbers, name);
				outln(n);
				output_ascii_line("*", strlen(n));
			}
		} else
		{
			sprintf(n, "%s%s", numbers, name);
			outln("");
			outln(n);
			output_ascii_line(&asc_structure_chars[currdepth], strlen(n));
		}
		outln("");
		break;

	case TOIPF:
		set_inside_node(currdepth);

		node2NrIPF(n, toc->labindex);
		map[0] = EOS;

		if (toc->mapping != 0)
			sprintf(map, " res=%u", toc->mapping);

		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		if (bInsideAppendix)
		{
			voutlnf(":h%d id=%s%s.%s %s%s", currdepth - TOC_NODE1 + 1, n, map, get_lang()->appendix, numbers, name);
		} else
		{
			voutlnf(":h%d id=%s%s.%s%s", currdepth - TOC_NODE1 + 1, n, map, numbers, name);
		}
		break;

	case TOKPS:
		set_inside_node(currdepth);

		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		if (use_style_book)
		{
			sprintf(n, "%s %s", bInsideAppendix ? get_lang()->appendix : get_lang()->chapter, numbers);
			del_right_spaces(n);

			if (n[0] != EOS)
				strcat(n, " ");

			strcat(n, name);
			voutlnf("%d changeFontSize", laydat.nodesize[currdepth]);
		} else
		{
			if (numbers[0] != EOS)
				strcat(numbers, " ");
			sprintf(n, "%s%s", numbers, name);
			voutlnf("%d changeFontSize", laydat.nodesize[currdepth + 1]);
		}

		node2postscript(name, KPS_NAMEDEST);
		if (currdepth == TOC_NODE1)
		{
			strcpy(nodename, n);
			node2postscript(nodename, KPS_NODENAME);
			voutlnf("/NodeName (%s %s) def", get_lang()->chapter, nodename);
		}
		outln("newline");
		voutlnf("/%s NameDest", name);

		outln("Bon");
		node2postscript(n, KPS_CONTENT);
		voutlnf("(%s) udoshow", n);
		outln("Boff");

		outln("newline");
		voutlnf("%d changeFontSize", laydat.propfontsize);
		break;

	case TODRC:
		set_inside_node(currdepth);

		outln("%%*");

		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		if (currdepth == TOC_NODE1 && p2_toc_counter + 1 <= p1_toc_counter
			&& toc_table[p2_toc_counter + 1]->toctype == currdepth + 1)
		{
			voutlnf("%%%% 0, %ld, 0, 0, %d, %s", p2_toc_counter + drc_structure_numbers[currdepth + 1], iDrcFlags,
					name);
		} else if (p2_toc_counter + 1 <= p1_toc_counter && toc_table[p2_toc_counter + 1]->toctype == currdepth + 1)
		{
			voutlnf("%%%% %ld, %ld, 0, 0, %d, %s",
					last_n_index[currdepth - 1] + drc_structure_numbers[currdepth],
					p2_toc_counter + drc_structure_numbers[currdepth + 1], iDrcFlags, name);
		} else if (currdepth == TOC_NODE1)
		{
			voutlnf("%%%% 0, 0, 0, 0, %d, %s", iDrcFlags, name);
		} else
		{
			voutlnf("%%%% %ld, 0, 0, 0, %d, %s", last_n_index[currdepth - 1] + drc_structure_numbers[currdepth],
					iDrcFlags, name);
		}
		outln("%%*");
		outln("");
		break;

	case TOSRC:
	case TOSRP:
		set_inside_node(currdepth);
		outln("");
		if (currdepth == TOC_NODE1)		/* additional line */
			outln("");
		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		memset(n, src_structure_chars[currdepth], 62);
		n[62] = EOS;
		voutlnf("%s  %s", sSrcRemOn, n);
		voutlnf("    %c", src_structure_chars[currdepth]);
		if (currdepth == TOC_NODE1)
			voutlnf("    %c", src_structure_chars[currdepth]);
		voutlnf("    %c %s", src_structure_chars[currdepth], name);
		voutlnf("    %c", src_structure_chars[currdepth]);
		if (currdepth == TOC_NODE1)
			voutlnf("    %c", src_structure_chars[currdepth]);
		voutlnf("    %s  %s", n, sSrcRemOff);
		outln("");
		break;

	case TORTF:
		set_inside_node(currdepth);
		if (use_style_book && currdepth == TOC_NODE1)
		{
			/* new page for new main chapter */
			c_newpage();
		}

		outln(rtf_pardpar);

		strcpy(k, name);
		winspecials2ascii(k);
		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);

		if (do_index)
		{
			voutf("{\\xe\\v %s}", k);
		}
		node2winhelp(k);

		if (numbers[0] != EOS)
			strcat(numbers, " ");
		out("{");
		if (!invisible)
			voutf("\\tc\\tcl%d", currdepth - TOC_NODE1 + 1);
		if (currdepth == TOC_NODE1)
		{
			if (use_style_book)
			{
				voutlnf("%s\\fs%d %s %s\\par %s\\fs%d {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s",
						rtf_inv_chapt,
						laydat.nodesize[0],
						bInsideAppendix ? get_lang()->appendix : get_lang()->chapter,
						numbers,
						rtf_structure_names[currdepth][invisible], laydat.nodesize[0], k, name, k, rtf_parpard);
			} else
			{
				voutlnf("%s %s\\fs%d %s{\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s",
						rtf_plain,
						rtf_structure_names[currdepth + 1][invisible],
						laydat.nodesize[currdepth + 1], numbers, k, name, k, rtf_parpard);
			}
		} else
		{
			if (use_style_book)
			{
				sprintf(n, "%s\\fs%d", rtf_structure_names[currdepth][invisible], laydat.nodesize[currdepth]);
			} else
			{
				sprintf(n, "%s\\fs%d", rtf_structure_names[currdepth + 1][invisible], laydat.nodesize[currdepth + 1]);
			}
			voutlnf("%s %s %s{\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, numbers, k, name, k, rtf_parpard);
		}
		outln("}");
		output_aliasses();
		voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		set_inside_node(currdepth);
		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		output_win_header(name, invisible);
		output_aliasses();

		if (use_style_book && currdepth == TOC_NODE1)
		{
			sprintf(n, "%s %s\\par %s", bInsideAppendix ? get_lang()->appendix : get_lang()->chapter, numbers, name);
		} else
		{
			if (numbers[0] != EOS)
				strcat(numbers, "\\~\\~");
			sprintf(n, "%s%s", numbers, name);
		}
		win_headline(n, popup);
		break;

	case TOPCH:
		set_inside_node(currdepth);
		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		if (numbers[0] != EOS)
			strcat(numbers, " ");
		output_pch_header(numbers, name, popup);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		hx_start[0] = '\0';
		hx_end[0] = '\0';
		{
			int hsize;
			TOCTYPE d;
			
			if (!html_merge_node[currdepth])
			{
				if (!html_new_file())
					return;
				hsize = html_nodesize;
			} else
			{
				output_aliasses();
				if (currdepth == TOC_NODE1)
				{
					outln(xhtml_hr);
					outln("");
				}
				hsize = html_nodesize + currdepth - TOC_NODE1;
			}
			if (!toc->ignore_title)
			{
				sprintf(hx_start, "<h%d>", hsize);
				sprintf(hx_end, "</h%d>", hsize);
				d = toc->toctype;
				if (d != TOC_TOC)
				{
					for (; d >= TOC_NODE1; d--)
					{
						if (last_n_index[d] != 0 && toc_table[last_n_index[d]]->toptitle)
						{
							toptitle = toc_table[last_n_index[d]]->toptitle;
							break;
						}
					}
				}
			}
		}

		set_inside_node(currdepth);
		flag = FALSE;

		do_toptoc(currdepth, popup);

		if (use_chapter_images)
		{
			if (toc->image != NULL)
			{
				sGifSize[0] = EOS;

				if (toc->uiImageWidth != 0 && toc->uiImageHeight != 0)
				{
					sprintf(sGifSize, " width=\"%u\" height=\"%u\"", toc->uiImageWidth,
							toc->uiImageHeight);
				}
#if 0
				if (html_doctype == HTML5)
					voutlnf("%s<p class=\"UDO_p_align_center\">", hx_start);
#endif
				else
					voutlnf("%s<p align=\"center\">", hx_start);
				voutlnf("<img src=\"%s\" alt=\"%s%s\" title=\"%s%s\"%s%s%s>",
						toc->image, numbers, name, numbers, name, border, sGifSize, xhtml_closer);
				voutlnf("</p>");
				flag = TRUE;
			}
		}

		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		if (!flag && !toc->ignore_title)
		{
			strcpy(nameNoSty, name);
			del_html_styles(nameNoSty);
			label2html(nameNoSty);
			voutf("%s<a %s=\"%s\">%s%s</a>", hx_start, xhtml_id_attr, nameNoSty, numbers, name);
		}
		if (!toc->ignore_title)
		{
			if (toptitle != NULL)
				voutlnf("<span style=\"position: absolute; right:0;\">%s</span>%s", toptitle, hx_end);
			else
				voutlnf("%s", hx_end);
		}
		
		if (show_variable.source_filename)
		{
			voutlnf("<!-- %s: %li -->", file_lookup(toc->source_location.id),
					toc->source_location.line);
		}
		break;

	case TOLDS:
		set_inside_node(currdepth);
		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		if (use_style_book)
			voutlnf("<%s>%s<label id=\"%s\">", lds_structure_names[currdepth], name, stgname);
		else
			voutlnf("<%s>%s<label id=\"%s\">", lds_structure_names[currdepth + 1], name, stgname);
		output_aliasses();
		outln("<p>");
		break;

	case TOHPH:
		set_inside_node(currdepth);
		if (toc->nodetitle != toc->nodename)
			strcpy(name, toc->nodetitle);
		if (use_style_book)
			voutlnf("<%s>%s", hph_structure_names[currdepth], name);
		else
			voutlnf("<%s>%s", hph_structure_names[currdepth + 1], name);
		output_aliasses();
		break;
	}
}





/*******************************************************************************
*
*  c_node():
*  c_node_iv():
*  c_pnode():
*  c_pnode_iv():
*     wrappers for make_node()
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_node(void)
{
	make_node(TOC_NODE1, FALSE, FALSE);
}

GLOBAL void c_node_iv(void)
{
	make_node(TOC_NODE1, FALSE, TRUE);
}

GLOBAL void c_pnode(void)
{
	make_node(TOC_NODE1, TRUE, FALSE);
}

GLOBAL void c_pnode_iv(void)
{
	make_node(TOC_NODE1, TRUE, TRUE);
}


GLOBAL void c_subnode(void)
{
	make_node(TOC_NODE2, FALSE, FALSE);
}

GLOBAL void c_subnode_iv(void)
{
	make_node(TOC_NODE2, FALSE, TRUE);
}

GLOBAL void c_psubnode(void)
{
	make_node(TOC_NODE2, TRUE, FALSE);
}

GLOBAL void c_psubnode_iv(void)
{
	make_node(TOC_NODE2, TRUE, TRUE);
}


GLOBAL void c_subsubnode(void)
{
	make_node(TOC_NODE3, FALSE, FALSE);
}

GLOBAL void c_subsubnode_iv(void)
{
	make_node(TOC_NODE3, FALSE, TRUE);
}

GLOBAL void c_psubsubnode(void)
{
	make_node(TOC_NODE3, TRUE, FALSE);
}

GLOBAL void c_psubsubnode_iv(void)
{
	make_node(TOC_NODE3, TRUE, TRUE);
}


GLOBAL void c_subsubsubnode(void)
{
	make_node(TOC_NODE4, FALSE, FALSE);
}

GLOBAL void c_subsubsubnode_iv(void)
{
	make_node(TOC_NODE4, FALSE, TRUE);
}

GLOBAL void c_psubsubsubnode(void)
{
	make_node(TOC_NODE4, TRUE, FALSE);
}

GLOBAL void c_psubsubsubnode_iv(void)
{
	make_node(TOC_NODE4, TRUE, TRUE);
}


GLOBAL void c_subsubsubsubnode(void)
{
	make_node(TOC_NODE5, FALSE, FALSE);
}

GLOBAL void c_subsubsubsubnode_iv(void)
{
	make_node(TOC_NODE5, FALSE, TRUE);
}

GLOBAL void c_psubsubsubsubnode(void)
{
	make_node(TOC_NODE5, TRUE, FALSE);
}

GLOBAL void c_psubsubsubsubnode_iv(void)
{
	make_node(TOC_NODE5, TRUE, TRUE);
}


GLOBAL void c_subsubsubsubsubnode(void)
{
	make_node(TOC_NODE6, FALSE, FALSE);
}

GLOBAL void c_subsubsubsubsubnode_iv(void)
{
	make_node(TOC_NODE6, FALSE, TRUE);
}

GLOBAL void c_psubsubsubsubsubnode(void)
{
	make_node(TOC_NODE6, TRUE, FALSE);
}

GLOBAL void c_psubsubsubsubsubnode_iv(void)
{
	make_node(TOC_NODE6, TRUE, TRUE);
}

GLOBAL void c_subsubsubsubsubsubnode(void)
{
	make_node(TOC_NODE7, FALSE, FALSE);
}

GLOBAL void c_subsubsubsubsubsubnode_iv(void)
{
	make_node(TOC_NODE7, FALSE, TRUE);
}

GLOBAL void c_psubsubsubsubsubsubnode(void)
{
	make_node(TOC_NODE7, TRUE, FALSE);
}

GLOBAL void c_psubsubsubsubsubsubnode_iv(void)
{
	make_node(TOC_NODE7, TRUE, TRUE);
}


GLOBAL void c_subsubsubsubsubsubsubnode(void)
{
	make_node(TOC_NODE8, FALSE, FALSE);
}

GLOBAL void c_subsubsubsubsubsubsubnode_iv(void)
{
	make_node(TOC_NODE8, FALSE, TRUE);
}

GLOBAL void c_psubsubsubsubsubsubsubnode(void)
{
	make_node(TOC_NODE8, TRUE, FALSE);
}

GLOBAL void c_psubsubsubsubsubsubsubnode_iv(void)
{
	make_node(TOC_NODE8, TRUE, TRUE);
}


GLOBAL void c_subsubsubsubsubsubsubsubnode(void)
{
	make_node(TOC_NODE9, FALSE, FALSE);
}

GLOBAL void c_subsubsubsubsubsubsubsubnode_iv(void)
{
	make_node(TOC_NODE9, FALSE, TRUE);
}

GLOBAL void c_psubsubsubsubsubsubsubsubnode(void)
{
	make_node(TOC_NODE9, TRUE, FALSE);
}

GLOBAL void c_psubsubsubsubsubsubsubsubnode_iv(void)
{
	make_node(TOC_NODE9, TRUE, TRUE);
}







/*******************************************************************************
*
*  c_endnode():
*     wrapper for check_endnode()
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_endnode(void)
{
	check_endnode();
	check_styleflags();
	check_environments_node();
}





/*******************************************************************************
*
*  c_begin_node():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_node(void)
{
	check_endnode();

	if (p2_toctype == TOC_NONE)
	{
		make_node(TOC_NODE1, FALSE, FALSE);
	} else if (p2_toctype >= TOC_MAXDEPTH - 1)
	{
		make_node(TOC_MAXDEPTH - 1, FALSE, FALSE);
	} else
	{
		make_node(p2_toctype + 1, FALSE, FALSE);
	}
}





/*******************************************************************************
*
*  c_begin_node_iv():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_node_iv(void)
{
	check_endnode();

	if (p2_toctype == TOC_NONE)
	{
		make_node(TOC_NODE1, FALSE, TRUE);
	} else if (p2_toctype >= TOC_MAXDEPTH - 1)
	{
		make_node(TOC_MAXDEPTH - 1, FALSE, TRUE);
	} else
	{
		make_node(p2_toctype + 1, FALSE, TRUE);
	}
}





/*******************************************************************************
*
*  c_begin_pnode():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_pnode(void)
{
	check_endnode();

	if (p2_toctype == TOC_NONE)
	{
		make_node(TOC_NODE1, TRUE, FALSE);
	} else if (p2_toctype >= TOC_MAXDEPTH - 1)
	{
		make_node(TOC_MAXDEPTH - 1, TRUE, FALSE);
	} else
	{
		make_node(p2_toctype + 1, TRUE, FALSE);
	}
}





/*******************************************************************************
*
*  c_begin_pnode_iv():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_pnode_iv(void)
{
	check_endnode();

	if (p2_toctype == TOC_NONE)
	{
		make_node(TOC_NODE1, TRUE, TRUE);
	} else if (p2_toctype >= TOC_MAXDEPTH - 1)
	{
		make_node(TOC_MAXDEPTH - 1, TRUE, TRUE);
	} else
	{
		make_node(p2_toctype + 1, TRUE, TRUE);
	}
}





/*******************************************************************************
*
*  c_end_node():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_node(void)
{
	check_endnode();
	check_styleflags();
	check_environments_node();

	switch (p2_toctype)
	{
	case TOC_NODE1:
		p2_toctype = TOC_NONE;
		break;
	case TOC_NONE:
		/* error message already issued in pass1() */
		break;
	default:
		p2_toctype--;
		break;
	}
}





/*******************************************************************************
*
*  tocline_make_bold():
*     make TOC entry line bold
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void tocline_make_bold(char *s, const int depth)
{
	char *str;

	if (depth > 1)
	{
		switch (desttype)
		{
		case TOHAH:
		case TOHTM:
		case TOMHH:
			str = um_strdup_printf("%s<a ", BOLD_ON);
			replace_once(s, "<a ", str);
			free(str);
			str = um_strdup_printf("</a>%s", BOLD_OFF);
			replace_last(s, "</a>", str);
			free(str);
			c_internal_styles(s);
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			strinsert(s, BOLD_ON);
			strcat(s, BOLD_OFF);
			c_internal_styles(s);
			break;
/*    case TOKPS:
         strinsert(s, "14 changeFontSize Bon ");
         strcat(s, " Boff 11 changeFontSize changeBaseFont");
         break;
*/
		}
	}
}




/*******************************************************************************
*
*  tocline_handle_1st():
*     output start of TOC listing head if the first item is going to be output
*
*  Notes:
*     <first> flag will be reset!
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void tocline_handle_1st(_BOOL * first)
{
	if (*first)
	{
		switch (desttype)
		{
		case TOINF:
			outln("@menu");
			break;
		case TOHAH:
		case TOHTM:
		case TOMHH:
		case TOTEX:
		case TOPDL:
			outln(toc_list_top);
			break;
		}
		*first = FALSE;
	}
}





/*******************************************************************************
*
*  bookmarks_ps():
*     output bookmarks for PostScript / PDF
*
*  return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL bookmarks_ps(void)
{
	TOCIDX i;
	LABIDX li;
	TOCIDX apxstart;
	char s[MAX_NODE_LEN + 1];
	char n[MAX_NODE_LEN + 1];
	char numbers[10 * TOC_MAXDEPTH];
	TOCTYPE d;

	if (p1_toc_counter <= 0)
		return FALSE;

	apxstart = 1;

	for (i = 1; i <= p1_toc_counter; i++)
	{
		if (toc_table[i] != NULL && !toc_table[i]->invisible)
		{
			convert_toc_item(toc_table[i]);

			if (toc_table[i]->appendix)
			{
				apxstart = i;			/* fuer unten merken */
				break;					/* there can be only one appendix */
			} else
			{
				if (toc_table[i]->n[TOC_NODE1] != 0)
				{
					sprintf(numbers, "%d", toc_table[i]->nr[TOC_NODE1] + toc_offset[TOC_NODE1]);
					for (d = TOC_NODE2; d <= toc_table[i]->toctype; d++)
						sprintf(numbers + strlen(numbers), ".%d", toc_table[i]->nr[d] + toc_offset[d]);
					li = toc_table[i]->labindex;
					strcpy(s, label_table[li]->name);
					strcpy(n, label_table[li]->name);
					node2postscript(n, KPS_BOOKMARK);
					node2postscript(s, KPS_NAMEDEST);
					voutlnf("(%s %s) /%s %d Bookmarks", numbers, n, s, toc_table[i]->num_children);
				}
			}
		}
	}

	if (!apx_available)
		return TRUE;

	/* --- appendix --- */

	for (i = apxstart; i <= p1_toc_counter; i++)
	{
		if (toc_table[i] != NULL && !toc_table[i]->invisible)
		{
			convert_toc_item(toc_table[i]);

			if (toc_table[i]->appendix)
			{
				if (toc_table[i]->n[TOC_NODE1] != 0)
				{
					li = toc_table[i]->labindex;
					strcpy(s, label_table[li]->name);
					strcpy(n, label_table[li]->name);
					node2postscript(n, KPS_BOOKMARK);
					node2postscript(s, KPS_NAMEDEST);
					sprintf(numbers, "%c", 'A' - 1 + toc_table[i]->nr[TOC_NODE1] + toc_offset[TOC_NODE1]);
					for (d = TOC_NODE2; d <= toc_table[i]->toctype; d++)
						sprintf(numbers + strlen(numbers), ".%2d", toc_table[i]->nr[d] + toc_offset[d]);
					voutlnf("(%s %s) /%s %d Bookmarks", numbers, n, s, toc_table[i]->num_children);
				}
			}
		}
	}

	outln("");

	return TRUE;
}


LOCAL void print_tabs(int count)
{
	int i;

	switch (desttype)
	{
	case TOHAH:
	case TOHTM:
	case TOMHH:
		for (i = 0; i < count; i++)
			out("\t");
		break;
	}
}


/*******************************************************************************
*
*  toc_output():
*     create output for all !use_auto_...tocs commands
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void toc_output(TOCTYPE currdepth, const int depth, _BOOL for_apx, _BOOL no_numbers, _BOOL compressed)
{
	register TOCIDX i;
	LABIDX li;
	char n[512];
	char ref[512];
	char s[20];
	_BOOL leerzeile = FALSE;
	_BOOL last_n[TOC_MAXDEPTH];
	_BOOL first = TRUE;
	_BOOL output_done = FALSE;
	_BOOL done;
	_BOOL found;
	int d, d2, level;
	LABEL *l;
	
	/* LYX doesn't support !toc */
	if (desttype == TOLYX)
		return;

	if (p1_toc_counter == 0)
		return;

	for (d = TOC_NODE1; d < currdepth; d++)
		if (last_n_index[d] == 0)
			return;

	if (for_apx && !apx_available)
		return;

	last_n[TOC_NODE1] = TRUE;
	for (d = TOC_NODE2; d < TOC_MAXDEPTH; d++)
		last_n[d] = FALSE;

	for (i = currdepth == TOC_NODE1 ? 1 : last_n_index[currdepth - 1]; i <= p1_toc_counter; i++)
	{
		if (toc_table[i] != NULL && !toc_table[i]->invisible)
		{
			if (for_apx)
			{
				if (!toc_table[i]->appendix)
					continue;
			} else
			{
				if (toc_table[i]->appendix)
					break;				/* there can be only one appendix */
			}

			convert_toc_item(toc_table[i]);

			done = FALSE;
			found = TRUE;
			if (for_apx)
			{
				for (d = TOC_NODE1; d < currdepth; d++)
				{
					if (toc_table[i]->n[d] > p2_apx_n[d])
					{
						/* Das waren dann alle */
						done = TRUE;
						break;
					}
					found &= toc_table[i]->n[d] == p2_apx_n[d];
				}
			} else
			{
				for (d = TOC_NODE1; d < currdepth; d++)
				{
					if (toc_table[i]->n[d] > p2_toc_n[d])
					{
						/* Das waren dann alle */
						done = TRUE;
						break;
					}
					found &= toc_table[i]->n[d] == p2_toc_n[d];
				}
			}
			if (done)
				break;

			if (found)
			{
				for (level = currdepth; level < TOC_MAXDEPTH; level++)
				{
					if (depth > level - currdepth && toc_table[i]->toctype == level && !label_table[toc_table[i]->labindex]->is_popup)
					{
						/* Ein Kapitel */
						if (currdepth == TOC_NODE1 && level == TOC_NODE1 && leerzeile && depth > 1 && !compressed)
						{
							switch (desttype)
							{
							case TOWIN:
							case TOWH4:
							case TOAQV:
							case TORTF:
								outln(rtf_par);
								break;
							case TOHAH:
							case TOHTM:
							case TOMHH:
								outln("<br>&nbsp;");
								break;
							case TOTEX:
							case TOPDL:
								break;
							default:
								outln("");
								break;
							}
							/* leerzeile= FALSE; */
						}

						if (use_toc_list_commands == TOCL_HTM)
						{
							for (d = currdepth; d < level; d++)
							{
								if (last_n[d])
								{
									for (d2 = d; d2 < level; d2++)
									{
										print_tabs(d2 + 1);
										outln(toc_list_top);
									}
									last_n[d] = FALSE;
								}
							}
							for (d = level; d < TOC_MAXDEPTH; d++)
							{
								if (last_n[d])
								{
									if (d > level)
									{
										print_tabs(d + 1);
										outln("</li>");
									}
									for (d2 = level; d2 < d; d2++)
									{
										print_tabs(level - d2 + d);
										outln(toc_list_end);
										print_tabs(level - d2 + d);
										outln("</li>");
									}
									if (d > level)
										last_n[d] = FALSE;
								}
							}
							last_n[level] = TRUE;
						}

						if (use_toc_list_commands == TOCL_TEX)
						{
							for (d = currdepth; d < level; d++)
							{
								if (last_n[d])
								{
									for (d2 = d; d2 < level; d2++)
									{
										print_tabs(d2 + 1);
										outln(toc_list_top);
									}
									last_n[d] = FALSE;
								}
							}
							for (d = level + 1; d < TOC_MAXDEPTH; d++)
							{
								if (last_n[d])
								{
									for (d2 = level; d2 < d; d2++)
									{
										print_tabs(level - d2 + d);
										outln(toc_list_end);
									}
									last_n[d] = FALSE;
								}
							}
							last_n[level] = TRUE;
						}

						li = toc_table[i]->labindex;
						l = label_table[li];
						string2reference(ref, l->name, li, TRUE, "", 0, 0);
						
						if (no_numbers)
						{
							strcpy(n, form_t_nonumbers[currdepth][level]);
							replace_once(n, "%s", ref);
						} else
						{
							strcpy(n, form_t_numbers[currdepth][level]);
							if (for_apx)
								sprintf(s, "%2c", toc_table[i]->nr[TOC_NODE1] + 'A' - 1);
							else
								sprintf(s, "%2d", toc_table[i]->nr[TOC_NODE1] + toc_offset[TOC_NODE1]);
							replace_once(n, "%d", s);
							for (d = TOC_NODE2; d <= level; d++)
							{
								sprintf(s, "%d", toc_table[i]->nr[d] + toc_offset[d]);
								replace_once(n, "%d", s);
							}
							replace_once(n, "%s", ref);
						}

						if (level == TOC_NODE1)
							tocline_make_bold(n, depth);

						tocline_handle_1st(&first);

						print_tabs(level - currdepth + 1);
						outln(n);
						leerzeile = TRUE;
						output_done = TRUE;
					}
				}
			}
		}
	}

	if (output_done)
	{
		switch (desttype)
		{
		case TOHAH:
		case TOHTM:
		case TOMHH:
			for (d = currdepth; d < TOC_MAXDEPTH; d++)
			{
				if (last_n[d])
				{
					for (d2 = currdepth; d2 < d; d2++)
					{
						print_tabs(currdepth - d2 + d + 1);
						outln("</li>");
						print_tabs(currdepth - d2 + d);
						outln(toc_list_end);
					}
					if (d > currdepth)
						last_n[d] = FALSE;
					print_tabs(d - 1);
					outln("</li>");
				}
			}
			outln(toc_list_end);
			if (currdepth >= TOC_NODE2)
				outln(xhtml_br);
			break;
		case TOTEX:
		case TOPDL:
			for (d = currdepth + 1; d < TOC_MAXDEPTH; d++)
			{
				if (last_n[d])
				{
					for (d2 = currdepth; d2 < d; d2++)
					{
						print_tabs(currdepth - d2 + d);
						outln(toc_list_end);
					}
					last_n[d] = FALSE;
				}
			}
			outln(toc_list_end);
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
		case TORTF:
			outln(rtf_par);
			outln(rtf_pard);
			break;
		case TOINF:
			if (currdepth == TOC_NODE1 && (for_apx || !apx_available) && !no_index && bCalledIndex && use_udo_index)
			{
				outln("");
				voutlnf("* %s::", get_lang()->index);
			}
			outln("@end menu");
			break;
		case TOSTG:
		case TOAMG:
			outln("");
			break;
		}
	}
}





/*******************************************************************************
*
*  output_appendix_line():
*     output the Appendix title line
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_appendix_line(void)
{
	switch (desttype)
	{
	case TOINF:
		outln("@sp 2");
		outln(get_lang()->appendix);
		outln("@sp 1");
		break;
	case TOSTG:
		outln("");
		voutlnf("@{U}%s@{u}", get_lang()->appendix);
		outln("");
		break;
	case TOAMG:
		outln("");
		voutlnf("@{U}%s@{UU}", get_lang()->appendix);
		outln("");
		break;
	case TOTVH:
		outln("");
		out("  ");
		outln(get_lang()->appendix);
		out("  ");
		output_ascii_line("=", strlen(get_lang()->appendix));
		outln("");
		break;
	case TOASC:
	case TOPCH:
		outln("");
		outln(get_lang()->appendix);
		output_ascii_line("=", strlen(get_lang()->appendix));
		outln("");
		break;
	case TODRC:						/* nix */
		break;
	case TOWIN:
	case TOWH4:
	case TOAQV:
		voutlnf("{\\b %s}\\par\\pard\\par", get_lang()->appendix);
		break;
	case TORTF:						/* nix */
		break;
	case TOHAH:
	case TOHTM:
	case TOMHH:
		voutlnf("<h1>%s</h1>", get_lang()->appendix);
		break;
	case TOTEX:
	case TOPDL:
		break;
	}
}





/*******************************************************************************
*
*  do_toc/do_subtoc():
*     wrapper for toc_output()
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void do_toc(int depth, _BOOL no_numbers, _BOOL compressed)
{
	if (desttype == TORTF)				/* no TOC in RTF as we have no page numbers! */
		return;

	toc_output(TOC_NODE1, depth, FALSE, no_numbers, compressed);

	if (apx_available)
	{
		output_appendix_line();
		toc_output(TOC_NODE1, depth, TRUE, no_numbers, compressed);
	}
}


LOCAL void do_subtoc(TOCTYPE currdepth, int depth, _BOOL no_numbers, _BOOL compressed)
{
	if (desttype == TORTF)
		return;
	toc_output(currdepth, depth, bInsideAppendix, no_numbers, compressed);
}



/*******************************************************************************
*
*  do_toptoc():
*     outputs the breadcrumb navigation links for the current chapter
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void do_toptoc(const TOCTYPE currdepth, _BOOL popup)
{
	char s[512];
	char sIndent[512];
	char sTarget[64];
	char *sFile;
	const char *sSmartSep = "&gt;";		/* default separator string */
	int d, level, start;
	
	char border[20];

	if (currdepth == TOC_TOC || !use_auto_toptocs || toc_table[p2_toc_counter]->ignore_toptoc)
		return;

	switch (desttype)
	{
	case TOHAH:
	case TOHTM:
	case TOMHH:
		strcpy(border, " border=\"0\"");
#if 0
		if (html_doctype == HTML5)
			border[0] = EOS;
#endif

		for (d = currdepth; d < TOC_MAXDEPTH; d++)
			if (html_merge_node[d])
				return;

		if (html_navigation_separator[0] != 0)	/* check if valid userdef separator exists */
		{
			sSmartSep = html_navigation_separator;
		}

		if (no_images || no_auto_toptocs_icons)
		{
			strcpy(sIndent, "&nbsp;");
		} else
		{
			sprintf(sIndent, "<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>",
					GIF_FS_NAME, uiGifFsWidth, uiGifFsHeight, border, xhtml_closer);
		}

		if (html_frames_layout)
		{
			sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
			sFile = um_strdup_printf("%s%s%s", html_name_prefix, FRAME_FILE_CON, outfile.suff);
		} else
		{
			sTarget[0] = EOS;
			sFile = um_strdup_printf("%s%s", old_outfile.name, old_outfile.suff);
		}

		for (level = TOC_NODE1; level <= currdepth; level++)
		{
			if (level == TOC_NODE1)
			{
				if (titdat.htmltitle != NULL)
					strcpy(s, titdat.htmltitle);
				else
					strcpy(s, titleprogram);
				if (no_images)
				{
					voutlnf("<tt>+&nbsp;</tt>&nbsp;<a href=\"%s\"%s>%s</a>", sFile, sTarget, s);
				} else if (html_navigation_line)
				{
					/* open CSS class div */
					outln("<div class=\"UDO_nav_line\">");

					if (html_navigation_image)
					{
						/* if userdef image exists */
						if (html_navigation_image_fspec[0] != 0)
						{
							/* don't close the nav line already! */
							voutf("<img src=\"%s\" alt=\"\" title=\"\"%s%s>&nbsp;&nbsp;<a href=\"%s\"%s>%s</a>",
								  /* folder image file name */
								  html_navigation_image_fspec, border, xhtml_closer,	/* XHTML single tag closer (if any) */
								  sFile,	/* file name */
								  sTarget,	/* a href target */
								  s);	/* node name */
						} else
						{
							/* don't close the nav line already! */
							voutf("<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;&nbsp;<a href=\"%s\"%s>%s</a>", GIF_FO_NAME,	/* folder image file name */
								  uiGifFoWidth,	/* folder image width */
								  uiGifFoHeight,	/* folder image height */
								  border, xhtml_closer,	/* XHTML single tag closer (if any) */
								  sFile,	/* file name */
								  sTarget,	/* a href target */
								  s);	/* node name */
						}
					} else
					{
						voutf("<a href=\"%s\"%s>%s</a>", sFile,	/* file name */
							  sTarget,	/* a href target */
							  s);		/* node name */
					}
				} else
				{
					voutlnf
						("<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;<a href=\"%s\"%s>%s</a>",
						 GIF_FO_NAME, uiGifFoWidth, uiGifFoHeight, border, xhtml_closer, sFile, sTarget, s);
				}
			} else
			{
				if (last_n_index[level - 1] != 0 && !toc_table[last_n_index[level - 1]]->invisible)
				{
					strcpy(s, toc_table[last_n_index[level - 1]]->nodename);
					gen_references(s, TRUE, "", 0, 0);
					if (no_images)
					{
						voutf("<br%s><tt>", xhtml_closer);
						for (d = TOC_NODE2; d < level; d++)
							out("&nbsp;&nbsp;&nbsp;");
						voutlnf("|--+&nbsp;</tt>&nbsp;%s", s);
					} else if (html_navigation_line)
					{
						for (d = TOC_NODE1; d < level; d++)
							voutf(" %s %s", sSmartSep, s);	/* don't close the nav line already! */
					} else
					{
						voutf("<br%s>", xhtml_closer);
						for (d = TOC_NODE1; d < level; d++)
							out(sIndent);
						voutlnf("<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;%s",
								GIF_FO_NAME, uiGifFoWidth, uiGifFoHeight, border, xhtml_closer, s);
					}
				}
			}
		}
		free(sFile);

		if (html_navigation_line)
		{
			/* create link to Index page */
			if (!no_index && bCalledIndex && use_udo_index)
				voutlnf("\n <span class=\"UDO_nav_index\"><a href=\"%s%s\">%s</a></span>", sDocHtmlIndexudo,
						outfile.suff, get_lang()->index);
			/* close CSS class div */
			outln("</div> <!-- UDO_nav_line -->\n");
		}

		outln(xhtml_hr);
		outln("");
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		if (!popup)
		{
			for (level = TOC_NODE1; level <= currdepth; level++)
			{
				if (level == TOC_NODE1)
				{
					/* Hier muesste ein Verweis auf den ersten Node hin */
					/* Dies koennte das Inhaltsverzeichnis, die */
					/* Titelseite oder ein sonstiger erster Node sein!? */
				} else
				{
					if (last_n_index[level - 1] != 0 && !toc_table[last_n_index[level - 1]]->invisible)
					{
						strcpy(s, toc_table[last_n_index[level - 1]]->nodename);
						gen_references(s, TRUE, "", 0, 0);
						voutlnf("\\par\\li%d\\{bmc %s\\} %s", (level - TOC_NODE2) * 400, BMP_FO_NAME, s);
					}
				}
			}
			outln("\\par\\par");
		}
		break;

	case TOSTG:
	case TOAMG:
		start = TOC_NODE1;
		if (!called_tableofcontents)
			start = TOC_NODE2;
		for (level = start; level <= currdepth; level++)
		{
			if (level == TOC_NODE1)
			{
				if (!no_images && !no_auto_toptocs_icons)
				{
					voutlnf("@image %s 1", IMG_FO_NAME);
				}
				voutlnf("   %s", get_lang()->contents);
			} else
			{
				if (last_n_index[level - 1] != 0 && !toc_table[last_n_index[level - 1]]->invisible)
				{
					LABEL *l;
					LABIDX li;
					
					if (!no_images && !no_auto_toptocs_icons)
					{
						voutlnf("@image %s %d", IMG_FO_NAME, (level - start) * 3 + 1);
					}
					for (d = start; d <= level; d++)
						out("   ");
					li = toc_table[last_n_index[level - 1]]->labindex;
					l = label_table[li];
					string2reference(s, l->name, li, FALSE, "", 0, 0);
					voutlnf("%s", s);
				}
			}
		}
		outln("");
		break;

	case TOPCH:
		for (level = TOC_NODE1; level <= currdepth; level++)
		{
			if (level == TOC_NODE1)
			{
				if (uses_tableofcontents || uses_maketitle)
				{
					voutlnf("\001 \\#%s\\#", get_lang()->contents);
				}
			} else
			{
				if (last_n_index[level - 1] != 0 && !toc_table[last_n_index[level - 1]]->invisible)
				{
					for (d = TOC_NODE1; d < level; d++)
						out("    ");
					voutlnf("\001 \\#%s\\#", toc_table[last_n_index[level - 1]]->nodename);
				}
			}
		}
		output_ascii_line("-", zDocParwidth);
		break;
	}
}




/*******************************************************************************
*
*  get_toccmd_depth():
*     get the user-defined TOC depth, set by the !depth command
*
*  Return:
*     TOC depth #
*
******************************************|************************************/

LOCAL int get_toccmd_depth(void)
{
	register int i;
	int ret;

	for (i = 1; i < token_counter; i++)
	{
		if (strcmp(token[i], "!depth") == 0)
		{
			if (i + 1 < token_counter)
			{
				ret = atoi(token[i + 1]);
				if (ret <= 0)
					ret = TOC_MAXDEPTH;
				if (ret > TOC_MAXDEPTH)
					ret = TOC_MAXDEPTH;
				return ret;
			}
		}
	}

	return 0;							/* bei 0 werden die Defaultwerte (z.B. subtocs_depth) benutzt */
}


LOCAL _BOOL get_toccmd_nonumbers(void)
{
	register int i;

	for (i = 1; i < token_counter; i++)
	{
		if (strcmp(token[i], "!no_numbers") == 0)
			return TRUE;
	}
	return no_numbers;
}





/*******************************************************************************
*
*  c_toc():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_toc(void)
{
	_BOOL flag = FALSE;
	int d;
	_BOOL no_numbers;
	
	if (is_for_desttype(&flag, token[0], TRUE))
	{
		_BOOL compressed = has_flag_compressed();
		
		d = get_toccmd_depth();
		if (d == 0)
		{
			if (use_compressed_tocs)
				d = 1;
			else
				d = TOC_MAXDEPTH;
		}
		no_numbers = get_toccmd_nonumbers();
		
		if (desttype == TOINF)
			d = 1;
		do_toc(d, no_numbers, compressed);
	}
}





/*******************************************************************************
*
*  c_subtoc():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_subtoc(void)
{
	_BOOL flag = FALSE;
	int d;
	_BOOL no_numbers;

	/* token[0] enthaelt das !sub*toc-Kommando */
	if (is_for_desttype(&flag, token[0], TRUE))
	{
		_BOOL compressed = has_flag_compressed();
		
		if (active_nodetype >= TOC_NODE1 && active_nodetype < TOC_MAXDEPTH - 2)
		{
			d = get_toccmd_depth();
			if (d == 0)
				d = subtocs_depth[active_nodetype];
			no_numbers = get_toccmd_nonumbers();
			do_subtoc(active_nodetype + 1, d, no_numbers, compressed);
		}
	}
}





/*******************************************************************************
*
*  c_listoffigures():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_listoffigures(void)
{
	check_endnode();

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\listoffigures");
		break;

	case TOLDS:
		outln("<lof>");
		break;

	case TOLYX:
		outln("\\layout Standard");
		outln("\\begin_inset LatexCommand \\listoffigures");
		outln("\\end_inset");
		break;

	case TORTF:
		outln("\\page");
		voutlnf("%s\\fs36 %s\\par\\par", rtf_node1, get_lang()->listfigure);
		voutlnf("{\\field\\fldedit{\\*\\fldinst { TOC \\\\c \"%s\" }}{\\fldrslt %s not actual}}",
				get_lang()->listfigure, get_lang()->listfigure);
		break;
	}
}





/*******************************************************************************
*
*  c_listoftables():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_listoftables(void)
{
	check_endnode();

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\listoftables");
		break;

	case TOLDS:
		outln("<lot>");
		break;

	case TOLYX:
		outln("\\layout Standard");
		outln("\\begin_inset LatexCommand \\listoftables");
		outln("\\end_inset");
		break;

	case TORTF:
		outln("\\page");
		voutlnf("%s\\fs36 %s\\par\\par", rtf_node1, get_lang()->listtable);
		voutlnf("{\\field\\fldedit{\\*\\fldinst {TOC \\\\c \"Tabelle\" }}{\\fldrslt %s not actual}}",
				get_lang()->listtable);
		break;
	}
}





/*******************************************************************************
*
*  c_tableofcontents():
*     outputs an auto-generated Table Of Contents
*
*  Return:
*     -
*
******************************************|************************************/

void stg_out_endnode(void)
{
	if (stg_need_endnode)
	{
		outln("@endnode");
		outln("");
		outln("");
		stg_need_endnode = FALSE;
	}
}


GLOBAL void c_tableofcontents(void)
{
	char name[MAX_NODE_LEN * 2];
	char *n;
	int i;
	int depth;
	const char *title;
	_BOOL compressed = has_flag_compressed();
	
	if (called_tableofcontents)
		return;

	called_tableofcontents = TRUE;

	check_endnode();

	depth = get_toccmd_depth();
	if (depth == 0)						/* use default values */
	{
		if (use_compressed_tocs)		/* show only 1st TOC level */
			depth = 1;
		else							/* show all TOC levels */
			depth = TOC_MAXDEPTH;
	}

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		c_newpage();
		output_helpid(0);
		outln("\\tableofcontents");
		c_newpage();
		break;

	case TOLYX:
		outln("\\layout LaTeX");
		outln("\\pagebreak_top \\pagebreak_bottom");
		outln("\\begin_inset LatexCommand \\tableofcontents");
		outln("\\end_inset");
		break;

	case TOINF:
		outln("@ifinfo");
		n = NULL;
		if (p1_toc_counter >= 1 && toc_table[1] != NULL)
		{
			strcpy(name, toc_table[1]->nodename);
			node2texinfo(name);
			n = um_strdup_printf("@node Top, %s, (dir), (dir)", name);
		}
		output_helpid(0);
		outln(n);
		free(n);

		if (called_maketitle)
		{
			if (titdat.title != NULL)
				voutlnf("@center %s @*", titdat.title);
			if (titdat.program != NULL)
				voutlnf("@center %s @*", titdat.program);
			if (titdat.version != NULL)
				voutlnf("@center %s @*", titdat.version);
			if (titdat.date != NULL)
				voutlnf("@center %s @*", titdat.date);
			if (titdat.author != NULL)
			{
				outln("@sp 1");
				voutlnf("@center %s", get_lang()->by);
				outln("@sp 1");
				voutlnf("@center %s @*", titdat.author);
			}
			if (address_counter > 0)
			{
				for (i = 1; i <= address_counter; i++)
				{
					if (titdat.address[i] != NULL)
					{
						voutlnf("@center %s @*", titdat.address[i]);
					}
				}
			}
			outln("@center ");
			outln("@sp 1");
		}

		outln(get_lang()->contents);
		outln("");

		do_toc(1, no_numbers, compressed);						/* always 1 */
		outln("@end ifinfo");
		break;

	case TOSTG:
	case TOAMG:
		stg_out_endnode();
		toc_table[p2_toc_counter]->ignore_toptoc = TRUE;
		if (toc_table[0]->nodetitle != toc_table[0]->nodename)
			title = toc_table[0]->nodetitle;
		else
			title = get_lang()->contents;
		if (desttype == TOSTG)
		{
			voutlnf("@node \"Main\" \"%s\"", title);
			voutlnf("@symbol ari \"%s\"", get_lang()->contents);
		} else
		{
			if (titleprogram[0] != EOS && toc_table[0]->nodetitle == toc_table[0]->nodename)
			{
				voutlnf("@node \"Main\" \"%s - %s\"", titleprogram, title);
			} else
			{
				voutlnf("@node \"Main\" \"%s\"", title);
			}
			voutlnf("@keywords \"%s\"", get_lang()->contents);
		}
		outln("@noref");
		
		if (called_maketitle)
			voutlnf("@toc \"%s\"", get_lang()->title);

		output_helpid(0);
		stg_headline("", get_lang()->contents, FALSE);

		do_toc(depth, no_numbers, compressed);
#if 0
		/* no @endnode here, so the user can add raw cmds to TOC page */
		outln("@endnode");
		outln("");
		outln("");
#endif
		stg_need_endnode = TRUE;
		break;

	case TOTVH:
		outln("");
		if (toc_table[0]->nodetitle != toc_table[0]->nodename)
			title = toc_table[0]->nodetitle;
		else
			title = get_lang()->contents;
		voutlnf(".topic %s", title);
		output_helpid(0);
		out("  ");
		outln(title);
		out("  ");
		output_ascii_line("=", strlen(title));
		outln("");

		do_toc(depth, no_numbers, compressed);
		outln("");
		break;

	case TOASC:
		if (toc_table[0]->nodetitle != toc_table[0]->nodename)
			title = toc_table[0]->nodetitle;
		else
			title = get_lang()->contents;
		if (toc_available)
		{
			if (use_style_book)
			{
				output_ascii_line("=", zDocParwidth);
				outln(title);
				output_ascii_line("=", zDocParwidth);
			} else
			{
				outln(title);
				output_ascii_line("=", strlen(title));
			}
			outln("");
			toc_output(TOC_NODE1, depth, FALSE, no_numbers, compressed);
			outln("");
		}
		if (apx_available)
		{
			output_appendix_line();
			toc_output(TOC_NODE1, depth, TRUE, no_numbers, compressed);
			outln("");
		}
		break;

	case TODRC:						/* <???> */
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		check_endnode();

		outln("{");
		node2NrWinhelp(name, 0);
		voutlnf("#{\\footnote # %s}", name);
		output_helpid(0);
		voutlnf("${\\footnote $ %s}", get_lang()->contents);
		if (use_nodes_inside_index && !no_index)
			voutlnf("K{\\footnote K %s}", get_lang()->contents);
		else
			voutlnf("A{\\footnote A %s}", get_lang()->contents);

		if (!no_buttons)
		{
			outln(win_browse);
			enable_win_button("BTN_UP", called_maketitle, WIN_TITLE_NODE_NAME);
			{
				int i;

				for (i = 0; i < iNumWinButtons; i++)
					enable_win_button(sDocWinButtonName[i], FALSE, NULL);
			}
		}

		if (toc_available)
		{
			outln("\\keepn");
			n = um_strdup_printf("\\fs%d", iDocPropfontSize + rtf_structure_height[TOC_NODE1 + 1]);
			voutlnf("{%s\\b %s}\\par\\pard\\par", n, toc_table[0]->nodetitle != toc_table[0]->nodename ? toc_table[0]->nodetitle : get_lang()->contents);
			free(n);
			toc_output(TOC_NODE1, depth, FALSE, no_numbers, compressed);
		}

		if (apx_available)
		{
			output_appendix_line();
			toc_output(TOC_NODE1, depth, TRUE, no_numbers, compressed);
		}

		outln("}\\page");
		break;

	case TOPCH:
		if (toc_table[0]->nodetitle != toc_table[0]->nodename)
		{
			if (titdat.program != NULL)
				voutlnf("screen(capsensitive(\"%s\"), screen(capsensitive(\"%s\"), capsensitive(\"%s\"))", toc_table[0]->nodetitle,
						titdat.program, get_lang()->contents);
			else
				voutlnf("screen(capsensitive(\"%s\"), capsensitive(\"%s\"))", toc_table[0]->nodetitle, get_lang()->contents);
		} else if (titdat.program != NULL)
		{
			voutlnf("screen(capsensitive(\"%s\"), capsensitive(\"%s\"))", titdat.program, get_lang()->contents);
		} else
		{
			voutlnf("screen(capsensitive(\"%s\"))", get_lang()->contents);
		}
		output_helpid(0);
		pch_headline(get_lang()->contents);
		outln("");

		if (uses_maketitle)
			pch_titlepage();

		outln("");

		if (toc_available)
		{
			outln(get_lang()->contents);
			output_ascii_line("=", strlen(get_lang()->contents));
			outln("");
			toc_output(TOC_NODE1, depth, FALSE, no_numbers, compressed);
		}

		if (apx_available)
		{
			output_appendix_line();
			toc_output(TOC_NODE1, depth, TRUE, no_numbers, compressed);
		}

		outln("");
		outln("\\end");
		outln("");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		output_helpid(0);

		if (toc_available)
		{
			voutlnf("<h1><a %s=\"%s\">%s</a></h1>", xhtml_id_attr, HTML_LABEL_CONTENTS, get_lang()->contents);
			toc_output(TOC_NODE1, depth, FALSE, no_numbers, compressed);
			outln(xhtml_br);
		}

		if (apx_available)
		{
			output_appendix_line();
			toc_output(TOC_NODE1, depth, TRUE, no_numbers, compressed);
			outln(xhtml_br);
		}

		if (use_udo_index && !no_index && bCalledIndex && desttype != TOMHH)
		{
			voutlnf("<h1><a href=\"%s%s\">%s</a></h1>\n", sDocHtmlIndexudo, outfile.suff, get_lang()->index);
			outln(xhtml_br);
		}
		outln(xhtml_br);
		break;

	case TOKPS:
		check_endnode();

		output_helpid(0);
		if (toc_available)
		{
			outln("newline");

			voutlnf("/NodeName (%s) def", get_lang()->contents);
			voutlnf("20 changeFontSize (%s) udoshow newline %d changeFontSize", get_lang()->contents,
					laydat.propfontsize);
			toc_output(TOC_NODE1, depth, FALSE, no_numbers, compressed);
		}

		if (apx_available)
		{
			output_appendix_line();
			toc_output(TOC_NODE1, depth, TRUE, no_numbers, compressed);
		}
		if (toc_available)
			c_newpage();
		break;

	case TOLDS:
		output_helpid(0);
		outln("<toc>");
		break;

	case TORTF:
		voutlnf("\\plain\\s4\\ql\\b\\f0\\li567\\fi-567\\fs%d", laydat.nodesize[TOC_NODE1 + 1]);
		voutlnf("%s", get_lang()->contents);
		voutlnf("\\par\\pard\\par\\pard \\plain \\s1\\qj\\f0\\fs%d", iDocPropfontSize);
		outln("{\\field{\\*\\fldinst {TOC \\\\t \"Node1;1;Node2;2;Node3;3;Node4;4\" }}{\\fldrslt {Please refresh!}}}");
		outln("\\page");
		break;
	}
}





/*******************************************************************************
*
*  check_endnode():
*     Ende eines Kapitels testen und ggf. setzen
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void check_endnode(void)
{
	struct footnote *f, *next;

	if (active_nodetype != TOC_NONE)
	{
		if (active_nodetype >= TOC_NODE1 && active_nodetype < TOC_MAXDEPTH - 2)
			if (use_auto_subtocs[active_nodetype])
				if (!toc_table[p2_toc_counter]->ignore_subtoc)
					do_subtoc(active_nodetype + 1, subtocs_depth[active_nodetype], no_numbers, FALSE);

		switch (desttype)
		{
		case TOASC:
			if (footnote_cnt)
			{
				outln("-----");

				for (f = footnotes; f; f = f->next)
				{
					voutlnf("%d %s", f->number, f->str);
				}
			}
			break;

		case TOSTG:
		case TOAMG:
			outln("@endnode");
			outln("");
			outln("");
			if (footnote_cnt)
			{
				char sTemp[MAX_NODE_LEN * 2];
				
				strcpy(sTemp, toc_table[p2_toc_counter]->nodename);
				node2stg(sTemp);
				for (f = footnotes; f; f = f->next)
				{
					voutlnf("@pnode %%udofootnote_%d", f->global_number);
					voutlnf("@toc \"%s\"", sTemp);
					voutlnf("%s", f->str);
					outln("@endnode");
					outln("");
					outln("");
				}
			}
			break;

		case TOPCH:
			pch_bottomline();
			outln("\\end");
			break;

		case TOTVH:
			tvh_bottomline();
			break;

		case TOWIN:
		case TOWH4:
		case TOAQV:
			outln("}\\page");
			break;

		case TOHAH:
		case TOHTM:
		case TOMHH:
			break;
		}

		for (f = footnotes; f; f = next)
		{
			next = f->next;
			free(f);
		}

		footnote_cnt = 0;
		footnotes = NULL;

		active_nodetype = TOC_NONE;
	}
}





/*******************************************************************************
*
*  c_label/c_label_iv():
*     output a label in 2nd pass
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_intern_label(_BOOL ignore_index)
{
	char sLabel[512];
	char sTemp[512];
	int do_index = use_label_inside_index && !no_index && !ignore_index;

	/* Tokens umkopieren */
	tokcpy2(sLabel, 512);

	if (sLabel[0] == EOS)
	{
		error_missing_parameter(CMD_LABEL);
		return;
	}

	p2_lab_counter++;

	replace_udo_quotes(sLabel);
	convert_tilde(sLabel);

	switch (desttype)
	{
	case TOTEX:
		label2tex(sLabel);
		c_divis(sLabel);
		c_vars(sLabel);
		voutlnf("\\label{%s}", sLabel);
		break;

	case TOPDL:
		label2tex(sLabel);
		c_divis(sLabel);
		c_vars(sLabel);
		voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
		break;

	case TOLYX:
		label2lyx(sLabel);
		c_divis(sLabel);
		c_vars(sLabel);
		outln("");
		outln("\\layout Standard");
		voutlnf("\\begin_inset LatexCommand \\label{%s}", sLabel);
		outln("\\end_inset");
		outln("");
		break;

	case TOSTG:
		node2stg(sLabel);
		c_divis(sLabel);
		voutlnf("@symbol %cr%c \"%s\"", label_table[p2_lab_counter]->ignore_links ? ' ' : 'a', do_index ? 'i' : ' ', sLabel);
		break;

	case TOAMG:
		node2stg(sLabel);
		c_divis(sLabel);
		voutlnf("@keywords \"%s\"", sLabel);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		label2html(sLabel);
		/* check if we're in description environment */
		if (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_DESC && !bDescDDOpen)
			voutlnf("<dd><a %s=\"%s\"></a></dd>", xhtml_id_attr, sLabel);
		else
			voutlnf("<a %s=\"%s\"></a>", xhtml_id_attr, sLabel);
		break;

	case TOLDS:
		voutlnf("<label id=\"%s\">", sLabel);
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		if (do_index)
			voutf("K{\\footnote K %s}", sLabel);
		else
			voutf("A{\\footnote A %s}", sLabel);
		if (bDocWinOldKeywords)
		{
			strcpy(sTemp, sLabel);
			del_internal_styles(sTemp);
			node2winhelp(sTemp);
			voutlnf("#{\\footnote # %s}", sTemp);
		}
		label2NrWinhelp(sLabel, p2_lab_counter);
		voutf("#{\\footnote # %s}", sLabel);
		break;

	case TORTF:
		if (use_label_inside_index && !no_index)
		{
			voutf("{\\xe\\v %s}", sLabel);
		}
		break;

	case TOKPS:
		node2postscript(sLabel, KPS_NAMEDEST);
		voutlnf("/%s NameDest", sLabel);
		/* Must be changed if (!label ...) is possible */
		break;
	}
}


GLOBAL void c_label(void)
{
	c_intern_label(FALSE);
}


GLOBAL void c_label_iv(void)
{
	c_intern_label(TRUE);
}





/*******************************************************************************
*
*  c_alias():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_alias(void)
{
	p2_lab_counter++;
}


LOCAL void set_labelname(LABEL *label, const char *name)
{
	strcpy(label->name, name);
	replace_udo_quotes(label->name);
	label->len = strlen(label->name);
#if USE_NAME_HASH
	{
		_UWORD hash_index;

		hash_index = hash_val(label->name);
		label->next_hash = hash[hash_index];
		hash[hash_index] = label;
	}
#endif
#if USE_KWSET
	if (!config.bNoFastAutoref)
	{
		if (kwset != NULL)
			if (kwsincr(kwset, label->name, label->len, NULL) == FALSE)
			{
				kwsfree(kwset);
				kwset = NULL;
			}
	}
#endif
}


/*******************************************************************************
*
*  make_label():
*     add a label or alias to the internal list of labels
*
*  @label: label name string
*  @isn: TRUE: chapter (node), FALSE: label or alias
*  @isa: TRUE: alias, FALSE: label
*  @isp: TRUE: popup
*  @ignore_index: TRUE: does not appear in index
*
*  Notes:
*     Labels are now added in all formats, because else *toc_output() would output
*     wrong results because it directly references using the label index.
*
*  Return:
*     - 0: error
*     - p1_lab_counter
*
******************************************|************************************/

LOCAL LABIDX make_label(const char *label, const _BOOL isn, const _BOOL isa, const _BOOL isp, _BOOL ignore_index,
						_BOOL ignore_links, _BOOL referenced)
{
	LABEL *labptr;
	LABEL **new_label;

	if (label[0] == EOS)
		return 0;

	/* get space for table */
	if (p1_lab_counter >= p1_lab_alloc)	/* Noch Platz in der Liste? */
	{
		LABIDX new_alloc = p1_lab_alloc + 1024;

		/* allocate 1 more than the count, because label_table[0] is unused */
		new_label = (LABEL **) realloc(label_table, (new_alloc + 1) * sizeof(LABEL *));
		if (new_label == NULL)
		{
			return 0;
		}
		if (label_table == NULL)
			new_label[0] = NULL;
		label_table = new_label;
		p1_lab_alloc = new_alloc;
	}

	/* get space for new label */
	labptr = (LABEL *) malloc(sizeof(LABEL));

	if (labptr == NULL)					/* no more memory? */
	{
		return 0;
	}

	p1_lab_counter++;
	label_table[p1_lab_counter] = labptr;

	set_labelname(labptr, label);

	labptr->labindex = p1_lab_counter;
	labptr->is_node = isn;
	labptr->is_alias = isa;
	labptr->is_popup = isp;
	labptr->tocindex = p1_toc_counter;
	labptr->ignore_links = ignore_links;
	labptr->ignore_index = ignore_index;
	labptr->referenced = referenced;

	if (pflag[PASS1].inside_apx)
	{
		labptr->appendix = TRUE;
	} else
	{
		labptr->appendix = FALSE;
	}

	if (sCurrFileName[0] == EOS)
	{
		/* should only happen when called by add_toc_to_toc(),
		   because the input file has not yet been opened */
		labptr->source_location.id = 0;
		labptr->source_location.line = 0;
	} else
	{
		labptr->source_location.id = file_listadd(sCurrFileName);
		labptr->source_location.line = uiCurrFileLine;
	}

	/* set label in project file */
	if (isa)
		save_upr_entry_alias(sCurrFileName, current_node_name_sys, uiCurrFileLine);
	else if (!isn)						/* only labels which are not nodes */
		save_upr_entry_label(sCurrFileName, current_node_name_sys, uiCurrFileLine);

	return p1_lab_counter;
}



/*******************************************************************************
*
*  add_label():
*     add a label to the internal list of labels
*
*  Notes:
*     tocindex: position of label in toc_table[]
*
*     Labels are now added in all formats, because else *toc_output() would output
*     wrong results because it directly references using the label index.
*
*  Return:
*     - 0: error
*     - p1_lab_counter
*
******************************************|************************************/

GLOBAL LABIDX add_label(const char *label, const _BOOL isn, const _BOOL isp, _BOOL ignore_index, _BOOL ignore_links)
{
	return make_label(label, isn, FALSE, isp, ignore_index, ignore_links, FALSE);
}


/*******************************************************************************
*
*  add_alias():
*     adds an alias to the internal list
*
*  Note:
*     An alias is another name of a node.
*
*  Return:
*     FALSE: any error occurred
*      TRUE: success
*
******************************************|************************************/

GLOBAL LABIDX add_alias(const char *alias, const _BOOL isp, _BOOL referenced)
{
	return make_label(alias, FALSE, TRUE, isp, FALSE, FALSE, referenced);
}





/*******************************************************************************
*
*  set_ignore_headline():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

/* FIXME: (for all following set_*() functions):
   protect against constructs like
   !begin_node
   ...
   !end_node
   !ignore_headline
   !begin_node
   
   The set_* command is currently applied to the last node,
   but should be applied to active node (one level above,
   maybe no active node at all)
   */
GLOBAL void set_ignore_headline(void)
{
	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_headline = TRUE;
}





/*******************************************************************************
*
*  set_ignore_bottomline():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_bottomline(void)
{
	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_bottomline = TRUE;
}





/*******************************************************************************
*
*  set_raw_header_filename():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_raw_header_filename(void)
{
	char s[MYFILE_FULL_LEN + 1];

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	if (token[1][0] == EOS)
		return;

	um_strcpy(s, token[1], ArraySize(s), "set_raw_header_filename[1]");

	if (p1_toc_counter == 0)
	{
		sDocRawHeaderFilename = file_listadd(s);
	} else
	{
		toc_table[p1_toc_counter]->raw_header_filename = file_listadd(s);
	}
}





/*******************************************************************************
*
*  set_raw_footer_filename():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_raw_footer_filename(void)
{
	char s[MYFILE_FULL_LEN + 1];

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	if (token[1][0] == EOS)
		return;

	um_strcpy(s, token[1], sizeof(s), "set_raw_footer_filename[1]");

	if (p1_toc_counter == 0)
	{
		sDocRawFooterFilename = file_listadd(s);
	} else
	{
		toc_table[p1_toc_counter]->raw_footer_filename = file_listadd(s);
	}
}





/*******************************************************************************
*
*  set_ignore_raw_header():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_raw_header(void)
{
	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_raw_header = TRUE;
}





/*******************************************************************************
*
*  set_ignore_raw_footer():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_raw_footer(void)
{
	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_raw_footer = TRUE;
}





/*******************************************************************************
*
*  set_ignore_footer():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_footer(void)
{
	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_footer = TRUE;
}





GLOBAL void set_toptitle(void)
{
	char k[MAX_NODE_LEN];
	char *ptr;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	tokcpy2(k, ArraySize(k));
	c_vars(k);
	qdelete_all(k, "!-", 2);

	auto_quote_chars(k, TRUE);
	replace_udo_quotes(k);

	if (toc_table[p1_toc_counter]->toptitle != NULL)
	{
		error_called_twice(token[0]);
	} else
	{
		/* might warn here if used inside popup, because the title is never used then */
		ptr = strdup(k);

		if (ptr == NULL)
		{
			bFatalErrorDetected = TRUE;
		} else
		{
			toc_table[p1_toc_counter]->toptitle = ptr;
		}
	}
}



GLOBAL void set_nodetitle(TOCIDX idx)
{
	char k[MAX_NODE_LEN];
	char *ptr;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[idx] != NULL);

	tokcpy2(k, ArraySize(k));
	tokcpy2(k, ArraySize(k));
	c_vars(k);
	qdelete_all(k, "!-", 2);

	auto_quote_chars(k, TRUE);
	replace_udo_quotes(k);

	if (toc_table[idx]->nodetitle != toc_table[idx]->nodename)
	{
		error_called_twice(token[0]);
	} else
	{
		ptr = strdup(k);

		if (ptr == NULL)
		{
			bFatalErrorDetected = TRUE;
		} else
		{
			toc_table[idx]->nodetitle = ptr;
		}
	}
}




/*******************************************************************************
*
*  set_ignore_title():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_title(void)
{
	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_title = TRUE;
}





/*******************************************************************************
*
*  set_ignore_links():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_links(void)
{
	LABIDX li;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_links = TRUE;

	li = toc_table[p1_toc_counter]->labindex;

	if (li != 0)
		label_table[li]->ignore_links = TRUE;
}





/*******************************************************************************
*
*  set_ignore_index():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_index(void)
{
	LABIDX li;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_index = TRUE;

	li = toc_table[p1_toc_counter]->labindex;

	if (li != 0)
		label_table[li]->ignore_index = TRUE;
}





/*******************************************************************************
*
*  set_ignore_subtoc():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_subtoc(void)
{
	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_subtoc = TRUE;
}





/*******************************************************************************
*
*  set_ignore_toptoc():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_toptoc(void)
{
	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	toc_table[p1_toc_counter]->ignore_toptoc = TRUE;
}





/*******************************************************************************
*
*  set_helpid():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_helpid(void)
{
	char id[512];
	char *ptr;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	if (token[1][0] == EOS)
		return;

	um_strcpy(id, token[1], 512, "set_helpid");

	/* <???> Hier pruefen, ob nur A-Z, a-z, 0-9 und _ benutzt werden */

	ptr = (char *) malloc((1 + strlen(id)) * sizeof(char));
	if (ptr == NULL)
	{
		bFatalErrorDetected = TRUE;
	} else
	{
		strcpy(ptr, id);
		toc_table[p1_toc_counter]->helpid = ptr;
	}

	bUseIdMapFileC = TRUE;
}





/*******************************************************************************
*
*  set_win_button():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void win_set_button(void)
{
	char *ptr;
	int i;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);
	if (token[1][0] == EOS || token[2][0] == EOS)
	{
		error_wrong_nr_parameters(token[0]);
		return;
	}

	for (i = 0; i < iNumWinButtons; i++)
		if (strcmp(token[1], sDocWinButtonName[i]) == 0)
			break;
	if (i >= iNumWinButtons)
	{
		error_message(_("windows button %s not defined"), token[1]);
		return;
	}

	/* <???> Hier pruefen, ob nur A-Z, a-z, 0-9 und _ benutzt werden */

	ptr = strdup(token[2]);

	if (ptr == NULL)
	{
		bFatalErrorDetected = TRUE;
	} else
	{
		toc_table[p1_toc_counter]->win_button[i] = ptr;
	}
}


/*******************************************************************************
*
*  set_mapping():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_mapping(void)
{
	char map[512];
	unsigned int m;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	if (token[1][0] == EOS)
		return;

	um_strcpy(map, token[1], 512, "set_mapping[1]");

	/* <???> Hier pruefen, ob nur 0-9 benutzt wird */

	m = atoi(token[1]);

	if (m != 0)
	{
		toc_table[p1_toc_counter]->mapping = m;
		bUseIdMapFileC = TRUE;
	} else
	{
		error_message(_("mapping not numeric or not of type integer"));
	}
}





/*******************************************************************************
*
*  set_chapter_image():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_chapter_image(void)
{
	_UWORD bitcnt;
	char s[MYFILE_FULL_LEN];
	char *ptr;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	if (token[1][0] == EOS)
		return;

	fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
	sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);

	if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
		replace_char(s, '\\', '/');

	ptr = strdup(s);

	if (ptr == NULL)
	{
		bFatalErrorDetected = TRUE;
		return;
	}

	toc_table[p1_toc_counter]->image = ptr;

	if (desttype != TOHTM && desttype != TOMHH && desttype != TOHAH)
		return;

	/* Ausmasse des Icons ermitteln */
	get_picture_size(s, NULL, &toc_table[p1_toc_counter]->uiImageWidth, &toc_table[p1_toc_counter]->uiImageHeight, &bitcnt);
}





/*******************************************************************************
*
*  set_chapter_icon():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_chapter_icon(void)
{
	char s[MYFILE_FULL_LEN];
	char *ptr;

	_UWORD bitcnt;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	if (token[1][0] == EOS)
		return;

	fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
	sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);

	if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
		replace_char(s, '\\', '/');

	ptr = strdup(s);

	if (ptr == NULL)
	{
		bFatalErrorDetected = TRUE;
		return;
	}

	toc_table[p1_toc_counter]->icon = ptr;

	if (desttype != TOHTM && desttype != TOHAH && desttype != TOMHH)
		return;

	/* Ausmasse des Icons ermitteln */
	get_picture_size(s, NULL, &toc_table[p1_toc_counter]->uiIconWidth, &toc_table[p1_toc_counter]->uiIconHeight, &bitcnt);
}





/*******************************************************************************
*
*  set_chapter_icon_active():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_chapter_icon_active(void)
{
	char s[MYFILE_FULL_LEN];
	char *ptr;
	_UWORD bitcnt;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	if (token[1][0] == EOS)
		return;

	fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
	sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);

	if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
		replace_char(s, '\\', '/');

	ptr = strdup(s);

	if (ptr == NULL)
	{
		bFatalErrorDetected = TRUE;
		return;
	}

	toc_table[p1_toc_counter]->icon_active = ptr;

	if (desttype != TOHTM && desttype != TOHAH && desttype != TOMHH)
		return;

	/* Ausmasse des Icons ermitteln */
	get_picture_size(s, NULL, &toc_table[p1_toc_counter]->uiIconActiveWidth,
					 &toc_table[p1_toc_counter]->uiIconActiveHeight, &bitcnt);
}





/*******************************************************************************
*
*  set_chapter_icon_text():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_chapter_icon_text(void)
{
	char s[512];
	char *ptr;

	ASSERT(toc_table != NULL);
	ASSERT(toc_table[p1_toc_counter] != NULL);

	if (token[1][0] == EOS)
		return;

	tokcpy2(s, ArraySize(s));
	auto_quote_chars(s, TRUE);

	ptr = strdup(s);

	if (ptr == NULL)
	{
		bFatalErrorDetected = TRUE;
	} else
	{
		toc_table[p1_toc_counter]->icon_text = ptr;
	}
}



/*******************************************************************************
*
*  init_new_toc_entry():
*     initialize a new TOC entry
*
*  Return:
*     ^ TOCITEM
*
******************************************|************************************/

LOCAL TOCITEM *init_new_toc_entry(const TOCTYPE toctype, _BOOL invisible)
{
	TOCITEM *tocptr;
	int i;
	char name[MAX_NODE_LEN + 1];
	TOCITEM **new_toc;

	tokcpy2(name, MAX_NODE_LEN + 1);
	if (name[0] == EOS)
	{
		fatal_message(_("missing node name"));
		bFatalErrorDetected = TRUE;
		return NULL;
	}

	/* get memory for TOC array */
	if (p1_toc_counter >= p1_toc_alloc)
	{
		TOCIDX new_alloc = p1_toc_alloc + 1024;

		/*
		 * allocate 1 more than the count,
		 * because we use toc_table[0] for the table-of-contents
		 */
		new_toc = (TOCITEM **) realloc(toc_table, (new_alloc + 1) * sizeof(TOCITEM *));
		if (new_toc == NULL)
		{
			return NULL;
		}
		toc_table = new_toc;
		p1_toc_alloc = new_alloc;
	}

	/* get memory for new TOC structure */
	tocptr = (TOCITEM *) malloc(sizeof(TOCITEM));

	if (tocptr == NULL)
	{
		return NULL;
	}

	memset(tocptr, 0, sizeof(*tocptr));	/* clear whole (uninitialized) content first */

	strcpy(tocptr->nodename, name);
	tocptr->nodetitle = tocptr->nodename;
	
	c_styles(tocptr->nodename);

	switch (desttype)
	{
	case TOWIN:
	case TOWH4:
	case TOAQV:
		c_win_styles(tocptr->nodename);
		break;
	case TORTF:
		c_rtf_styles(tocptr->nodename);
		c_rtf_quotes(tocptr->nodename);
		break;
	default:
		c_internal_styles(tocptr->nodename);
		break;
	}

	if (desttype == TOPCH)
		replace_all_copyright(tocptr->nodename);

	tocptr->toctype = toctype;
	tocptr->converted = FALSE;
	tocptr->appendix = FALSE;
	tocptr->ignore_subtoc = FALSE;
	tocptr->ignore_toptoc = FALSE;
	tocptr->ignore_links = FALSE;
	tocptr->ignore_index = FALSE;
	tocptr->ignore_title = FALSE;
	tocptr->ignore_headline = FALSE;
	tocptr->ignore_bottomline = FALSE;
	tocptr->raw_header_filename = 0;
	tocptr->raw_footer_filename = 0;
	tocptr->ignore_raw_header = FALSE;
	tocptr->ignore_raw_footer = FALSE;
	tocptr->ignore_footer = FALSE;
	tocptr->filename[0] = EOS;
	tocptr->dirname = 0;
	tocptr->counter_command = 0;
	tocptr->keywords = NULL;
	tocptr->description = NULL;
	tocptr->bgsound = 0;
	tocptr->robots = NULL;
	tocptr->helpid = NULL;
	for (i = 0; i < MAX_WIN_BUTTONS; i++)
		tocptr->win_button[i] = NULL;
	tocptr->mapping = 0;
	tocptr->image = NULL;
	tocptr->uiImageWidth = 0;
	tocptr->uiImageHeight = 0;
	tocptr->icon = NULL;
	tocptr->uiIconWidth = 0;
	tocptr->uiIconHeight = 0;
	tocptr->icon_active = NULL;
	tocptr->uiIconActiveWidth = 0;
	tocptr->uiIconActiveHeight = 0;
	tocptr->icon_text = NULL;
	tocptr->has_children = FALSE;
	tocptr->has_visible_children = FALSE;
	tocptr->num_children = 0;
	for (i = TOC_NODE1; i < TOC_MAXDEPTH - 1; i++)
		tocptr->up_n_index[i] = 0;
	tocptr->next_index = 0;
	tocptr->prev_index = 0;
	for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
	{
		tocptr->n[i] = 0;
		tocptr->nr[i] = 0;
	}

	if (sCurrFileName[0] == EOS)
	{
		/* should only happen when called by add_toc_to_toc(),
		   because the input file has not yet been opened */
		tocptr->source_location.id = 0;
		tocptr->source_location.line = 0;
	} else
	{
		tocptr->source_location.id = file_listadd(sCurrFileName);
		tocptr->source_location.line = uiCurrFileLine;
	}

	tocptr->backimage = sDocBackImage;
	tocptr->backcolor = sDocBackColor.rgb;
	tocptr->textcolor = sDocTextColor.rgb;
	tocptr->linkcolor = sDocLinkColor.rgb;
	tocptr->alinkcolor = sDocAlinkColor.rgb;
	tocptr->vlinkcolor = sDocVlinkColor.rgb;

	tocptr->favicon_name = sDocFavIcon;

	/* Texinfo kennt keine versteckten Nodes, daher fuer */
	/* Texinfo das invisible-Flag immer auf FALSE setzen. */
	if (desttype == TOINF)
		invisible = FALSE;
	tocptr->invisible = invisible;
	tocptr->labindex = 0;

	p1_toctype = toctype;

	return tocptr;
}





/*******************************************************************************
*
*  add_toc_to_toc():
*     add TOC page (indexudo) to toc_table[0]
*
*  Notes:
*     Used for output formats which require toc_table[0].
*
*  Return:
*      TRUE: everything's fine
*     FALSE: error
*
******************************************|************************************/

LOCAL _BOOL add_toc_to_toc(void)
{
	TOCITEM *tocptr;

	/* should be get_lang()->contents, but is not initialized yet */
	strcpy(token[1], "Contents");
	token_counter = 2;
	tocptr = init_new_toc_entry(TOC_TOC, TRUE);

	if (tocptr == NULL)
		return FALSE;

	if (html_frames_layout)
		sprintf(tocptr->filename, "%s%s", html_name_prefix, FRAME_FILE_CON);
	else
		sprintf(tocptr->filename, "%s", outfile.name);

	tocptr->invisible = TRUE;
	tocptr->prev_index = 0;
	tocptr->next_index = 1;

	toc_table[0] = tocptr;

	return TRUE;
}





/*******************************************************************************
*
*  toc_init_lang():
*     add TOC title to toc_table[0]
*
*  Notes:
*     This function is only called by init_lang().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void toc_init_lang(void)
{
	if (toc_table != NULL && toc_table[0] != NULL)	/* kann passieren wenn schon waerend der Initialisierung was schief geht */
	{
		strcpy(toc_table[0]->nodename, get_lang()->contents);
		/* set_labelname(label_table[toc_table[0]->labindex], toc_table[0]->nodename); */
	}
}





/* Nicht LOCAL: wird von abo.c und udo.c benutzt! */

/*******************************************************************************
*
*  add_node_to_toc():
*     adds a node of a certain type to the TOC
*
*  Return:
*     FALSE: some error occurred
*      TRUE: success
*
******************************************|************************************/

GLOBAL _BOOL add_node_to_toc(TOCTYPE currdepth, _BOOL popup, _BOOL invisible)
{
	TOCITEM *tocptr;
	LABIDX li;
	int i;

	if (currdepth >= TOC_NODE2 && last_n_index[currdepth - 1] == 0)
	{
		error_node_not_allowed(currdepth - TOC_NODE1 - 1);
		return FALSE;
	}

	/* Texinfo kennt keine versteckten Kapitel */
	if (desttype == TOINF)
		invisible = FALSE;

	ASSERT(currdepth >= TOC_NODE1 && currdepth < TOC_MAXDEPTH);
	tocptr = init_new_toc_entry(currdepth, invisible);

	if (tocptr == NULL)
		return FALSE;

	all_nodes[currdepth]++;

	if (currdepth > toc_maxdepth)
		toc_maxdepth = currdepth;
	tocptr->ignore_subtoc = popup;
	
	/* ---------------------------------------------------- */
	/* Listenartige Verkettung erzeugen                     */
	/* ---------------------------------------------------- */
	/* noch ist p1_toc_counter nicht inkrementiert worden,  */
	/* zeigt daher auf den letzten (Sub(Sub))Node           */

	tocptr->prev_index = p1_toc_counter;

	/* Bei HTML muss das Mergen beachtet werden! Der        */
	/* Vorgaenger wird daher auf den letzten *Node gesetzt  */
	if (desttype == TOHTM || desttype == TOHAH)
	{
		for (i = TOC_MAXDEPTH; --i >= TOC_NODE2;)
		{
			if (html_merge_node[i] && last_n_index[i - 1] != 0)
				tocptr->prev_index = last_n_index[i - 1];
		}
		if (html_merge_node[TOC_NODE1])
			tocptr->prev_index = 0;
	}

	/* Den Nachfolger des Vorgaengers setzen: auf diesen */
	toc_table[p1_toc_counter]->next_index = p1_toc_counter + 1;

	if (desttype == TOHTM || desttype == TOHAH)
	{
		for (i = TOC_MAXDEPTH; --i >= TOC_NODE2;)
		{
			/* Wenn Subsubsubsubsubnode gemerged werden, dann muss  */
			/* beim letzten Subsubsubsubnode dieser Node als        */
			/* naechster Index eingetragen werden!              */
			if (html_merge_node[i] && last_n_index[i - 1] != 0)
			{
				toc_table[last_n_index[i - 1]]->next_index = p1_toc_counter + 1;
			}
		}
	}

	/* Der Zeiger auf den Nachfolger muss vom Nachfolger gesetzt werden. */
	tocptr->next_index = 0;

	/* Merken, dass der uebergeordnete Kinder hat */
	/* und die Anzahl der Subnodes erhoehen */
	if (currdepth >= TOC_NODE2 && last_n_index[currdepth - 1] != 0)
	{
		toc_table[last_n_index[currdepth - 1]]->has_children = TRUE;
		toc_table[last_n_index[currdepth - 1]]->num_children++;
	}
	if (currdepth >= TOC_NODE2 && last_n_index[currdepth - 1] != 0 && !invisible)
	{
		toc_table[last_n_index[currdepth - 1]]->has_visible_children = TRUE;
	}

	/* Hilfsvariablen setzen fuer die uebergeordneten Nodes */
	for (i = currdepth; i < TOC_MAXDEPTH - 1; i++)
		tocptr->up_n_index[i] = 0;
	if (currdepth >= TOC_NODE2)
		tocptr->up_n_index[currdepth - 1] = last_n_index[currdepth - 1];

	last_n_index[currdepth] = p1_toc_counter + 1;
	for (i = currdepth + 1; i < TOC_MAXDEPTH; i++)
		last_n_index[i] = 0;

	/* ---------------------------------------------------- */

	/* Zaehler hochsetzen und Zeiger in das Array kopieren  */
	p1_toc_counter++;
	toc_table[p1_toc_counter] = tocptr;

	if (pflag[PASS1].inside_apx)
	{
		apx_available = TRUE;
		p1_apx_n[currdepth]++;
		for (i = currdepth + 1; i < TOC_MAXDEPTH; i++)
			p1_apx_n[i] = 0;
		tocptr->appendix = TRUE;
		for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
			tocptr->n[i] = p1_apx_n[i];
		if (!invisible)
		{
			p1_apx_nr[currdepth]++;
			for (i = currdepth + 1; i < TOC_MAXDEPTH; i++)
				p1_apx_nr[i] = 0;
			for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
				tocptr->nr[i] = p1_apx_nr[i];
		}
	} else
	{
		toc_available = TRUE;
		p1_toc_n[currdepth]++;
		for (i = currdepth + 1; i < TOC_MAXDEPTH; i++)
			p1_toc_n[i] = 0;
		tocptr->appendix = FALSE;
		for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
			tocptr->n[i] = p1_toc_n[i];
		if (!invisible)
		{
			p1_toc_nr[currdepth]++;
			for (i = currdepth + 1; i < TOC_MAXDEPTH; i++)
				p1_toc_nr[i] = 0;
			for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
				tocptr->nr[i] = p1_toc_nr[i];
		}
	}

	if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
	{
		/* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
		get_html_filename(p1_toc_counter, tocptr->filename);
	}

	li = add_label(tocptr->nodename, TRUE, popup, FALSE, FALSE);

	tocptr->labindex = li;

	/* Set node in project file */
	if (currdepth >= TOC_NODE1 && currdepth < TOC_MAXDEPTH && !in_about_udo)
		save_upr_entry_node(currdepth - TOC_NODE1 + 1, sCurrFileName, current_node_name_sys, uiCurrFileLine);

	return TRUE;
}





/*******************************************************************************
*
*  toc_begin_node():
*     wrapper for add_<...>node_to_toc()
*
*  Notes:
*     This function is called in UDO.C:pass1() to handle the various levels of
*        !begin_node
*        !begin_node*
*        !begin_pnode
*        !begin_pnode*
*     which do NOT indicate the chapter hierarchy in themselves, like the older
*     commands do, like e.g.
*        !node
*        !subnode
*        !subsubnode
*        !subsubsubnode
*        !subsubsubsubnode
*
*  Return:
*      TRUE: everything's fine
*     FALSE: error
*
******************************************|************************************/

GLOBAL _BOOL toc_begin_node(const _BOOL popup, const _BOOL invisible)
{
	_BOOL ret;

	if (p1_toctype == TOC_NONE)
	{
		ret = add_node_to_toc(TOC_NODE1, popup, invisible);
	} else if (p1_toctype >= TOC_MAXDEPTH - 1)
	{
		warning_node_too_deep(popup, invisible);
		ret = add_node_to_toc(TOC_MAXDEPTH - 1, popup, invisible);
	} else
	{
		ret = add_node_to_toc(p1_toctype + 1, popup, invisible);
	}
	
	return ret;
}



/*******************************************************************************
*
*  toc_end_node():
*     decrease current node type during pass1()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void toc_end_node(void)
{
	switch (p1_toctype)
	{
	case TOC_NODE1:
		p1_toctype = TOC_NONE;
		break;

	case TOC_NONE:
		error_end_without_begin(CMD_END_NODE, CMD_BEGIN_NODE);
		break;

	default:
		p1_toctype--;
		break;
	}
}



GLOBAL _BOOL toc_inside_popup(void)
{
	TOCTYPE currdepth;

	currdepth = iUdopass == PASS1 ? p1_toctype : p2_toctype;
	if (currdepth >= TOC_NODE1 && currdepth < TOC_MAXDEPTH)
		return label_table[toc_table[last_n_index[currdepth]]->labindex]->is_popup;
	return FALSE;
}





/*******************************************************************************
*
*  is_current_node():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL is_current_node(TOCIDX tocindex)
{
	return tocindex == p2_toc_counter;
}





/*******************************************************************************
*
*  get_toc_counter():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL TOCIDX get_toc_counter(void)
{
	return p2_toc_counter;
}


/*
   ############################################################
   #
   #       Dateien mit den Jump-IDs ausgeben fuer C und Pascal
   #
   ############################################################
*/
/*******************************************************************************
*
*  save_the_alias():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL save_the_alias(const char *filename, const char *suffix, tWinMapData * data)
{
	register TOCIDX i;
	unsigned int map;
	char hid[256];
	char f[512];
	FILE *file;

	_BOOL saved_any = FALSE;

	strcpy(f, filename);
	strcat(f, suffix);

	file = fopen(f, "w");

	if (file == NULL)
		return FALSE;

	fprintf(file, "%s alias-file of %s, made with UDO%s %s\n\n", data->remOn, old_outfile.name, UDO_REL, data->remOff);

	for (i = 0; i <= p1_toc_counter; i++)
	{
		hid[0] = EOS;

		if (toc_table[i]->helpid != NULL)
		{
			strcpy(hid, toc_table[i]->helpid);
		} else
		{
			if (use_auto_helpids)
			{
				node2WinAutoID(hid, toc_table[i]->nodename);
			}
		}

		map = toc_table[i]->mapping;

		if (hid[0] != EOS || map != 0 || desttype == TOWH4)
		{
			if (hid[0] == EOS)
			{
				node2NrWinhelp(hid, toc_table[i]->labindex);
			}

			if (strcmp(hid, WIN_UDO_NODE_NAME) != 0)
			{
				strinsert(hid, sDocWinPrefixID);
				saved_any = TRUE;
			}

			fprintf(file, "%-*s =%s%s ; %s\n",
					MAX_HELPID_LEN + 1, hid, toc_table[i]->filename, outfile.suff, toc_table[i]->nodetitle);
		}
	}

	fclose(file);

	if (saved_any)
	{
		save_upr_entry_outfile(f);
	} else
	{
		remove(f);
	}

	return saved_any;
}





/*******************************************************************************
*
*  save_htmlhelp_alias():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_htmlhelp_alias(void)
{
	tWinMapData data;
	_BOOL flag;

	memset(&data, 0, sizeof(data));
	/* the alias file is not a C-File, and needs ";" as comment separator */
	strcpy(data.remOn, ";");
	strcpy(data.remOff, "");

	flag = save_the_alias(sMapNoSuff, ".hha", &data);

	return flag;
}





/*******************************************************************************
*
*  save_the_map():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL save_the_map(const char *filename, const char *suffix, tWinMapData *data)
{
	register TOCIDX i;
	unsigned int map;
	char hid[256];
	char f[512];
	FILE *file;
	_BOOL saved_any = FALSE;

	strcpy(f, filename);
	strcat(f, suffix);

	file = fopen(f, "w");
	if (file == NULL)
		return FALSE;

	fprintf(file, "%s mapping of %s for %s, made with UDO%s %s\n\n",
			data->remOn, outfile.name, data->compiler, UDO_REL, data->remOff);

	for (i = 0; i <= p1_toc_counter; i++)
	{
		hid[0] = EOS;

		if (toc_table[i]->helpid != NULL)
		{
			strcpy(hid, toc_table[i]->helpid);
		} else
		{
			if (use_auto_helpids)
			{
				node2WinAutoID(hid, toc_table[i]->nodename);
			}
		}

		map = toc_table[i]->mapping;

		if (hid[0] != EOS || map != 0 || desttype == TOWH4)
		{
			if (hid[0] == EOS)
			{
				node2NrWinhelp(hid, toc_table[i]->labindex);
			}

			if (strcmp(hid, WIN_UDO_NODE_NAME) != 0)
			{
				strinsert(hid, sDocWinPrefixID);
				saved_any = TRUE;
			}

			if (map == 0)
				map = 0x1000 + i;

			/* Fuer htmlhelp eine Datei mit C-Makros erzeugen, ueber welche 
			   dann eine Map vom Titel auf den Knoten (html-Dateinamen) 
			   gebildet werden kann.
			   Z.B. X("Formatierung","004006.html")
			 */

#if 0
			/*
			   Bullshit.
			   Die Routine erzeugt auch Header fuer WinHelp und WinHelp4,
			   und nicht nur HtmlHelp.
			   Und nicht nur fuer C, sondern auch Pascal und GFA.
			   Und wo bitte wird hier die map ID ausgegeben die man
			   muehselig ueberall mit win_helpid gesetzt hat???
			 */
			fprintf(file, "X(\"%s\",\"%s%s\")\n", toc_table[i]->nodename, toc_table[i]->filename, outfile.suff);
#endif
			fprintf(file, "%s %-*s%s\t%s%04X%s\t%s %s %s\n",
					data->cmd,
					MAX_HELPID_LEN + 1,
					hid, data->varOp, data->hexPre, map, data->hexSuf, data->remOn, toc_table[i]->nodename, data->remOff);
		}
	}

	fclose(file);

	if (saved_any)
	{
		save_upr_entry_outfile(f);
	} else
	{
		remove(f);
	}

	return saved_any;
}





/*******************************************************************************
*
*  save_htmlhelp_map():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_htmlhelp_map(void)
{
	tWinMapData data;
	_BOOL flag;

	memset(&data, 0, sizeof(data));
	strcpy(data.cmd, "#define");
	strcpy(data.hexPre, "0x");
	strcpy(data.remOn, "/*");
	strcpy(data.remOff, "*/");
	strcpy(data.compiler, "C");

	flag = save_the_map(sMapNoSuff, ".hhm", &data);

	return flag;
}





/*******************************************************************************
*
*  save_winhelp_map_c():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp_map_c(void)
{
	tWinMapData data;
	_BOOL flag;

	memset(&data, 0, sizeof(data));
	strcpy(data.cmd, "#define");
	strcpy(data.hexPre, "0x");
	strcpy(data.remOn, "/*");
	strcpy(data.remOff, "*/");
	strcpy(data.compiler, "C");

	flag = save_the_map(sMapNoSuff, ".hpc", &data);

	return flag;
}





/*******************************************************************************
*
*  save_winhelp_map_pas():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp_map_pas(void)
{
	tWinMapData data;
	_BOOL flag;

	memset(&data, 0, sizeof(data));
	strcpy(data.cmd, "const");
	strcpy(data.varOp, "=");
	strcpy(data.hexPre, "$");
	strcpy(data.hexSuf, ";");
	strcpy(data.remOn, "(*");
	strcpy(data.remOff, "*)");
	strcpy(data.compiler, "Pascal");

	flag = save_the_map(sMapNoSuff, ".hpp", &data);

	return flag;
}





/*******************************************************************************
*
*  save_winhelp_map_vb():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp_map_vb(void)
{
	tWinMapData data;
	_BOOL flag;

	memset(&data, 0, sizeof(data));
	strcpy(data.cmd, "Public Const");
	strcpy(data.varOp, "=");
	strcpy(data.hexPre, "&h");
	strcpy(data.hexSuf, "");
	strcpy(data.remOn, "'");
	strcpy(data.remOff, "");
	strcpy(data.compiler, "Visual Basic");

	flag = save_the_map(sMapNoSuff, ".hpb", &data);

	return flag;
}





/*******************************************************************************
*
*  save_winhelp_map_gfa():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp_map_gfa(void)
{
	tWinMapData data;
	_BOOL flag;

	memset(&data, 0, sizeof(data));
	strcpy(data.cmd, "Public Const");
	strcpy(data.varOp, "=");
	strcpy(data.hexPre, "&h");
	strcpy(data.hexSuf, "");
	strcpy(data.remOn, "'");
	strcpy(data.remOff, "");
	strcpy(data.compiler, "GFA-Basic");

	flag = save_the_map(sMapNoSuff, ".hpg", &data);

	return flag;
}



/*
 * workaround for Winhelp4 contents file:
 * the nodename is already translated to RTF,
 * but the contents file needs plain characters.
 * Undoes conversion from \'xx form to single
 * characters but may need some more
 * work for other sequences.
 * Will definitely not work for any fancy
 * characters that are taken from the symbol
 * font in the text, like greek alpha and beta.
 */
LOCAL void undo_rtf(char *s)
{
	char *str;

	replace_all(s, "{\\f1 \\'85}", "..");
	replace_all(s, "{\\f1 \\'97}", "---");
	replace_all(s, "{\\f1 \\'96}", "--");
	while ((str = strstr(s, "\\'")) != NULL)
	{
		str[0] = strtol(str + 2, NULL, 16);
		memmove(str + 1, str + 4, strlen(str + 4) + 1);
	}
	qreplace_all(s, "\\-", 2, "", 0);
	qreplace_all(s, "\\~", 2, " ", 1);
	qreplace_all(s, "\\\\{", 3, "{", 1);
	qreplace_all(s, "\\\\}", 3, "}", 1);
	qreplace_all(s, "\\\\", 2, "\\", 1);
}



/*******************************************************************************
*
*  save_winhelp4_cnt():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp4_cnt(void)
{
	FILE *cntfile;
	register TOCIDX i;
	LABIDX li;
	TOCIDX apxstart;
	char sName[512];
	char sMisc[512];
	char sID[128];
	_BOOL nHadChildren[TOC_MAXDEPTH];
	int d;

	cntfile = myFwopen(file_lookup(sCntfull), FTCNT);

	if (cntfile == NULL)
		return FALSE;

	save_upr_entry_outfile(file_lookup(sCntfull));

	for (d = TOC_NODE1; d < TOC_MAXDEPTH; d++)
		nHadChildren[d] = FALSE;

	fprintf(cntfile, ":Base %s.hlp>main\n", outfile.name);
	fprintf(cntfile, ":Index %s.hlp\n", outfile.name);

	strcpy(sMisc, titleprogram);
	undo_rtf(sMisc);
	if (sMisc[0] != EOS)
	{
		fprintf(cntfile, ":Title %s\n", sMisc);
	}

	/*
	 * if !tableofcontents was used,
	 * we have a TOC in the document and
	 * dont need the entries in the *.cnt file
	 */
	if (!uses_tableofcontents && p1_toc_counter > 0)
	{
		if (uses_tableofcontents)
		{
			node2NrWinhelp(sMisc, 0);
			fprintf(cntfile, "1 %s=%s\n", get_lang()->contents, sMisc);
		}

		apxstart = 1;

		for (i = 1; i <= p1_toc_counter; i++)
		{
			if (toc_table[i] != NULL && !toc_table[i]->invisible)
			{
				convert_toc_item(toc_table[i]);

				if (toc_table[i]->appendix)
				{
					apxstart = i;		/* fuer unten merken */
					break;
				} else
				{
					if (toc_table[i]->n[TOC_NODE1] != 0)
					{
						li = toc_table[i]->labindex;
						node2NrWinhelp(sID, li);
#if 0
						if (!no_numbers)
						{
							sprintf(sName, "[%d", toc_table[i]->nr[TOC_NODE1] + toc_offset[TOC_NODE1]);
							for (d = TOC_NODE2; d <= toc_table[i]->toctype; d++)
							{
								sprintf(sMisc, ".%d", toc_table[i]->nr[d] + toc_offset[d]);
								strcat(sName, sMisc);
							}
							strcat(sName, "] ");
							strcat(sName, toc_table[i]->nodetitle);
						} else
#endif
						{
							strcpy(sName, toc_table[i]->nodetitle);
						}
						undo_rtf(sName);
						if (nHadChildren[toc_table[i]->toctype] || toc_table[i]->has_visible_children)
						{
							fprintf(cntfile, "%d %s\n", toc_table[i]->toctype - TOC_NODE1 + 1, sName);
							fprintf(cntfile, "%d %s=%s\n", toc_table[i]->toctype - TOC_NODE1 + 2, sName, sID);
							nHadChildren[toc_table[i]->toctype] = TRUE;
						} else
						{
							fprintf(cntfile, "%d %s=%s\n", toc_table[i]->toctype - TOC_NODE1 + 1, sName, sID);
						}
						for (d = toc_table[i]->toctype + 1; d < TOC_MAXDEPTH; d++)
							nHadChildren[d] = FALSE;
					}
				}
			}
		}

		if (apx_available)
		{
			for (d = TOC_NODE1; d < TOC_MAXDEPTH; d++)
				nHadChildren[d] = FALSE;

			fprintf(cntfile, "1 %s\n", get_lang()->appendix);

			for (i = apxstart; i <= p1_toc_counter; i++)
			{
				if (toc_table[i] != NULL && !toc_table[i]->invisible)
				{
					convert_toc_item(toc_table[i]);

					if (toc_table[i]->appendix)
					{
						if (toc_table[i]->n[TOC_NODE1] != 0)
						{
							li = toc_table[i]->labindex;
							node2NrWinhelp(sID, li);
#if 0
							if (!no_numbers)
							{
								sprintf(sName, "[%c", 'A' - 1 + toc_table[i]->nr[TOC_NODE1]);
								for (d = TOC_NODE2; d <= toc_table[i]->toctype; d++)
								{
									sprintf(sMisc, ".%d", toc_table[i]->nr[d]);
									strcat(sName, sMisc);
								}
								strcat(sName, "] ");
								strcat(sName, toc_table[i]->nodetitle);
							} else
#endif
							{
								strcpy(sName, toc_table[i]->nodetitle);
							}
							undo_rtf(sName);
							if (nHadChildren[toc_table[i]->toctype] || toc_table[i]->has_visible_children)
							{
								fprintf(cntfile, "%d %s\n", toc_table[i]->toctype - TOC_NODE1 + 2, sName);
								fprintf(cntfile, "%d %s=%s\n", toc_table[i]->toctype - TOC_NODE1 + 3, sName, sID);
								nHadChildren[toc_table[i]->toctype] = TRUE;
							} else
							{
								fprintf(cntfile, "%d %s=%s\n", toc_table[i]->toctype - TOC_NODE1 + 2, sName, sID);
							}
							for (d = toc_table[i]->toctype + 1; d < TOC_MAXDEPTH; d++)
								nHadChildren[d] = FALSE;
						}
					}
				}
			}
		}
	}

	fclose(cntfile);
	return TRUE;
}





/*******************************************************************************
*
*  init_toc_forms_numbers():
*     initialize format strings for tables of content
*
*  Notes:
*     This is required when the state of !no_numbers is known, i.e.
*     between pass1() and pass2().
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_toc_forms_numbers(void)
{
	switch (desttype)
	{
	case TOAQV:
	case TOWIN:
	case TORTF:
		form_t_numbers[TOC_NODE1][TOC_NODE1] = "\\li320\\fi-320\\tx320 %d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE2] = "\\li880\\fi-560\\tx880 %d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE3] = "\\li1800\\fi-920\\tx1800 %d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE4] = "\\li2800\\fi-1000\\tx2800 %d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE5] = "\\li4000\\fi-1200\\tx4000 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE6] = "\\li5400\\fi-1400\\tx5400 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE7] = "\\li7000\\fi-1600\\tx7000 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE8] = "\\li8600\\fi-1800\\tx8600 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE9] = "\\li10200\\fi-2000\\tx10200 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE2] = "\\li480\\fi-480\\tx480 %d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE3] = "\\li1400\\fi-920\\tx1400 %d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE4] = "\\li2400\\fi-1000\\tx2400 %d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE5] = "\\li3600\\fi-1200\\tx3600 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE6] = "\\li5000\\fi-1400\\tx5000 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE7] = "\\li6600\\fi-1600\\tx6600 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE8] = "\\li8200\\fi-1800\\tx8200 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE9] = "\\li9800\\fi-2000\\tx9800 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE3] = "\\li880\\fi-880\\tx880 %d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE4] = "\\li1800\\fi-920\\tx1800 %d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE5] = "\\li3000\\fi-1200\\tx3000 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE6] = "\\li4400\\fi-1400\\tx4400 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE7] = "\\li6000\\fi-1600\\tx6000 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE8] = "\\li7600\\fi-1800\\tx7600 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE9] = "\\li9200\\fi-2000\\tx9200 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE4] = "\\li880\\fi-880\\tx880 %d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE5] = "\\li2080\\fi-1200\\tx2080 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE6] = "\\li3480\\fi-1400\\tx3480 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE7] = "\\li5080\\fi-1600\\tx5080 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE8] = "\\li6480\\fi-1800\\tx6480 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE9] = "\\li7880\\fi-2000\\tx7880 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE5] = "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE6] = "\\li2280\\fi-1400\\tx2280 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE7] = "\\li3880\\fi-1600\\tx3880 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE8] = "\\li5280\\fi-1800\\tx5280 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE9] = "\\li6680\\fi-2000\\tx6680 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE6][TOC_NODE6] = "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE6][TOC_NODE7] = "\\li2480\\fi-1600\\tx2480 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE6][TOC_NODE8] = "\\li3880\\fi-1800\\tx3880 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE6][TOC_NODE9] = "\\li5280\\fi-2000\\tx5280 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE7][TOC_NODE7] = "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE7][TOC_NODE8] = "\\li2680\\fi-1800\\tx2680 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE7][TOC_NODE9] = "\\li4080\\fi-2000\\tx4080 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE8][TOC_NODE8] = "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE8][TOC_NODE9] = "\\li2880\\fi-2000\\tx2880 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE9][TOC_NODE9] = "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		break;

	case TOWH4:
		form_t_numbers[TOC_NODE1][TOC_NODE1] = "\\li300\\fi-300\\tx300 %d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE2] = "\\li800\\fi-500\\tx800 %d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE3] = "\\li1600\\fi-800\\tx1600 %d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE4] = "\\li2600\\fi-1000\\tx2600 %d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE5] = "\\li3800\\fi-1200\\tx3800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE6] = "\\li5200\\fi-1400\\tx5200 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE7] = "\\li6800\\fi-1600\\tx6800 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE8] = "\\li8400\\fi-1800\\tx8400 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE1][TOC_NODE9] = "\\li10000\\fi-2000\\tx10000 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE2] = "\\li400\\fi-400\\tx400 %d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE3] = "\\li1300\\fi-920\\tx1300 %d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE4] = "\\li2200\\fi-1000\\tx2200 %d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE5] = "\\li3400\\fi-1200\\tx3400 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE6] = "\\li4800\\fi-1400\\tx4800 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE7] = "\\li6400\\fi-1600\\tx6400 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE8] = "\\li8000\\fi-1800\\tx8000 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE2][TOC_NODE9] = "\\li9600\\fi-2000\\tx10000 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE3] = "\\li800\\fi-800\\tx800 %d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE4] = "\\li1600\\fi-920\\tx1600 %d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE5] = "\\li2800\\fi-1200\\tx2800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE6] = "\\li4200\\fi-1400\\tx4200 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE7] = "\\li5800\\fi-1600\\tx5800 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE8] = "\\li7400\\fi-1800\\tx7400 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE3][TOC_NODE9] = "\\li9000\\fi-2000\\tx9000 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE4] = "\\li800\\fi-800\\tx800 %d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE5] = "\\li2000\\fi-1200\\tx2000 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE6] = "\\li3400\\fi-1400\\tx3400 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE7] = "\\li5000\\fi-1600\\tx5000 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE8] = "\\li6600\\fi-1800\\tx6600 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE4][TOC_NODE9] = "\\li8200\\fi-2000\\tx8200 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE5] = "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE6] = "\\li2200\\fi-1400\\tx2200 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE7] = "\\li3800\\fi-1600\\tx3800 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE8] = "\\li5400\\fi-1800\\tx5400 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE5][TOC_NODE9] = "\\li7000\\fi-2000\\tx7000 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE6][TOC_NODE6] = "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE6][TOC_NODE7] = "\\li2400\\fi-1600\\tx2400 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE6][TOC_NODE8] = "\\li4000\\fi-1800\\tx4000 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE6][TOC_NODE9] = "\\li5600\\fi-2000\\tx5600 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE7][TOC_NODE7] = "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE7][TOC_NODE8] = "\\li2600\\fi-1800\\tx2600 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE7][TOC_NODE9] = "\\li4200\\fi-2000\\tx4200 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE8][TOC_NODE8] = "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE8][TOC_NODE9] = "\\li2800\\fi-2000\\tx2800 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		form_t_numbers[TOC_NODE9][TOC_NODE9] = "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard";
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		form_t_numbers[TOC_NODE1][TOC_NODE1] = "<li>%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE2] = "<li>%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE3] = "<li>%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE4] = "<li>%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE5] = "<li>%d.%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE6] = "<li>%d.%d.%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE7] = "<li>%d.%d.%d.%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE8] = "<li>%d.%d.%d.%d.%d.%d.%d %d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE9] = "<li>%d.%d.%d.%d.%d.%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE2][TOC_NODE2] = form_t_numbers[TOC_NODE1][TOC_NODE2];
		form_t_numbers[TOC_NODE2][TOC_NODE3] = form_t_numbers[TOC_NODE1][TOC_NODE3];
		form_t_numbers[TOC_NODE2][TOC_NODE4] = form_t_numbers[TOC_NODE1][TOC_NODE4];
		form_t_numbers[TOC_NODE2][TOC_NODE5] = form_t_numbers[TOC_NODE1][TOC_NODE5];
		form_t_numbers[TOC_NODE2][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE2][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE2][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE2][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE3][TOC_NODE3] = form_t_numbers[TOC_NODE1][TOC_NODE3];
		form_t_numbers[TOC_NODE3][TOC_NODE4] = form_t_numbers[TOC_NODE1][TOC_NODE4];
		form_t_numbers[TOC_NODE3][TOC_NODE5] = form_t_numbers[TOC_NODE1][TOC_NODE5];
		form_t_numbers[TOC_NODE3][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE3][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE3][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE3][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE4][TOC_NODE4] = form_t_numbers[TOC_NODE1][TOC_NODE4];
		form_t_numbers[TOC_NODE4][TOC_NODE5] = form_t_numbers[TOC_NODE1][TOC_NODE5];
		form_t_numbers[TOC_NODE4][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE4][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE4][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE4][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE5][TOC_NODE5] = form_t_numbers[TOC_NODE1][TOC_NODE5];
		form_t_numbers[TOC_NODE5][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE5][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE5][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE5][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE6][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE6][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE6][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE6][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE7][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE7][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE7][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE8][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE8][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE9][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		break;

	case TOTEX:
	case TOPDL:
		form_t_numbers[TOC_NODE1][TOC_NODE1] = "\\item %d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE2] = "\\item %d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE3] = "\\item %d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE4] = "\\item %d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE5] = "\\item %d.%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE6] = "\\item %d.%d.%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE7] = "\\item %d.%d.%d.%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE8] = "\\item %d.%d.%d.%d.%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE1][TOC_NODE9] = "\\item %d.%d.%d.%d.%d.%d.%d.%d.%d %s";
		form_t_numbers[TOC_NODE2][TOC_NODE2] = form_t_numbers[TOC_NODE1][TOC_NODE2];
		form_t_numbers[TOC_NODE2][TOC_NODE3] = form_t_numbers[TOC_NODE1][TOC_NODE3];
		form_t_numbers[TOC_NODE2][TOC_NODE4] = form_t_numbers[TOC_NODE1][TOC_NODE4];
		form_t_numbers[TOC_NODE2][TOC_NODE5] = form_t_numbers[TOC_NODE1][TOC_NODE5];
		form_t_numbers[TOC_NODE2][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE2][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE2][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE2][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE3][TOC_NODE3] = form_t_numbers[TOC_NODE1][TOC_NODE3];
		form_t_numbers[TOC_NODE3][TOC_NODE4] = form_t_numbers[TOC_NODE1][TOC_NODE4];
		form_t_numbers[TOC_NODE3][TOC_NODE5] = form_t_numbers[TOC_NODE1][TOC_NODE5];
		form_t_numbers[TOC_NODE3][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE3][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE3][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE3][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE4][TOC_NODE4] = form_t_numbers[TOC_NODE1][TOC_NODE4];
		form_t_numbers[TOC_NODE4][TOC_NODE5] = form_t_numbers[TOC_NODE1][TOC_NODE5];
		form_t_numbers[TOC_NODE4][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE4][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE4][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE4][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE5][TOC_NODE5] = form_t_numbers[TOC_NODE1][TOC_NODE5];
		form_t_numbers[TOC_NODE5][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE5][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE5][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE5][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE6][TOC_NODE6] = form_t_numbers[TOC_NODE1][TOC_NODE6];
		form_t_numbers[TOC_NODE6][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE6][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE6][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE7][TOC_NODE7] = form_t_numbers[TOC_NODE1][TOC_NODE7];
		form_t_numbers[TOC_NODE7][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE7][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE8][TOC_NODE8] = form_t_numbers[TOC_NODE1][TOC_NODE8];
		form_t_numbers[TOC_NODE8][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		form_t_numbers[TOC_NODE9][TOC_NODE9] = form_t_numbers[TOC_NODE1][TOC_NODE9];
		break;

	case TOKPS:
		form_t_numbers[TOC_NODE1][TOC_NODE1] = "(%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE1][TOC_NODE2] = "(   %d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE1][TOC_NODE3] = "(        %d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE1][TOC_NODE4] = "(               %d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE1][TOC_NODE5] = "(                        %d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE1][TOC_NODE6] = "(                                   %d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE1][TOC_NODE7] = "(                                                %d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE1][TOC_NODE8] = "(                                                               %d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE1][TOC_NODE9] = "(                                                                                %d.%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE2][TOC_NODE2] = "(%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE2][TOC_NODE3] = "(     %d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE2][TOC_NODE4] = "(            %d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE2][TOC_NODE5] = "(                     %d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE2][TOC_NODE6] = "(                                %d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE2][TOC_NODE7] = "(                                             %d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE2][TOC_NODE8] = "(                                                            %d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE2][TOC_NODE9] = "(                                                                             %d.%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE3][TOC_NODE3] = "(%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE3][TOC_NODE4] = "(       %d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE3][TOC_NODE5] = "(                %d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE3][TOC_NODE6] = "(                           %d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE3][TOC_NODE7] = "(                                        %d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE3][TOC_NODE8] = "(                                                       %d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE3][TOC_NODE9] = "(                                                                        %d.%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE4][TOC_NODE4] = "(%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE4][TOC_NODE5] = "(         %d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE4][TOC_NODE6] = "(                    %d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE4][TOC_NODE7] = "(                                 %d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE4][TOC_NODE8] = "(                                                %d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE4][TOC_NODE9] = "(                                                                 %d.%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE5][TOC_NODE5] = "(%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE5][TOC_NODE6] = "(           %d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE5][TOC_NODE7] = "(                        %d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE5][TOC_NODE8] = "(                                       %d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE5][TOC_NODE9] = "(                                                        %d.%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE6][TOC_NODE6] = "(%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE6][TOC_NODE7] = "(             %d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE6][TOC_NODE8] = "(                            %d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE6][TOC_NODE9] = "(                                             %d.%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE7][TOC_NODE7] = "(%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE7][TOC_NODE8] = "(               %d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE7][TOC_NODE9] = "(                                %d.%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE8][TOC_NODE8] = "(%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE8][TOC_NODE9] = "(                 %d.%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		form_t_numbers[TOC_NODE9][TOC_NODE9] = "(%d.%d.%d.%d.%d.%d.%d.%d.%d ) %s udoshow newline";
		break;

	default:
		form_t_numbers[TOC_NODE1][TOC_NODE1] = "%d  %s";
		form_t_numbers[TOC_NODE1][TOC_NODE2] = "   %d.%d  %s";
		form_t_numbers[TOC_NODE1][TOC_NODE3] = "        %d.%d.%d  %s";
		form_t_numbers[TOC_NODE1][TOC_NODE4] = "               %d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE1][TOC_NODE5] = "                        %d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE1][TOC_NODE6] = "                                   %d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE1][TOC_NODE7] = "                                                %d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE1][TOC_NODE8] = "                                                               %d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE1][TOC_NODE9] = "                                                                                %d.%d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE2][TOC_NODE2] = "%d.%d  %s";
		form_t_numbers[TOC_NODE2][TOC_NODE3] = "     %d.%d.%d  %s";
		form_t_numbers[TOC_NODE2][TOC_NODE4] = "            %d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE2][TOC_NODE5] = "                     %d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE2][TOC_NODE6] = "                                %d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE2][TOC_NODE7] = "                                             %d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE2][TOC_NODE8] = "                                                            %d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE2][TOC_NODE9] = "                                                                             %d.%d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE3][TOC_NODE3] = "%d.%d.%d  %s";
		form_t_numbers[TOC_NODE3][TOC_NODE4] = "       %d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE3][TOC_NODE5] = "                %d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE3][TOC_NODE6] = "                           %d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE3][TOC_NODE7] = "                                        %d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE3][TOC_NODE8] = "                                                       %d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE3][TOC_NODE9] = "                                                                        %d.%d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE4][TOC_NODE4] = "%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE4][TOC_NODE5] = "         %d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE4][TOC_NODE6] = "                    %d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE4][TOC_NODE7] = "                                 %d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE4][TOC_NODE8] = "                                                %d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE4][TOC_NODE9] = "                                                                 %d.%d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE5][TOC_NODE5] = "%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE5][TOC_NODE6] = "           %d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE5][TOC_NODE7] = "                        %d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE5][TOC_NODE8] = "                                       %d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE5][TOC_NODE9] = "                                                        %d.%d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE6][TOC_NODE6] = "%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE6][TOC_NODE7] = "             %d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE6][TOC_NODE8] = "                            %d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE6][TOC_NODE9] = "                                             %d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE7][TOC_NODE7] = "%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE7][TOC_NODE8] = "               %d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE7][TOC_NODE9] = "                                %d.%d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE8][TOC_NODE8] = "%d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE8][TOC_NODE9] = "                 %d.%d.%d.%d.%d.%d.%d.%d.%d.%d  %s";
		form_t_numbers[TOC_NODE9][TOC_NODE9] = "%d.%d.%d.%d.%d.%d.%d.%d.%d  %s";
		break;
	}
}





/*******************************************************************************
*
*  init_toc_forms_no_numbers():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_toc_forms_no_numbers(void)
{
	int d,
	 d2;

	switch (desttype)
	{
	case TOAQV:
	case TOWIN:
	case TOWH4:
	case TORTF:
		form_t_nonumbers[TOC_NODE1][TOC_NODE1] = "{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE1][TOC_NODE2] = "\\li560{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE1][TOC_NODE3] = "\\li1120{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE1][TOC_NODE4] = "\\li1680{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE1][TOC_NODE5] = "\\li2240{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE1][TOC_NODE6] = "\\li2800{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE1][TOC_NODE7] = "\\li3360{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE1][TOC_NODE8] = "\\li3920{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE1][TOC_NODE9] = "\\li4480{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE2][TOC_NODE2] = "{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE2][TOC_NODE3] = "\\li560{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE2][TOC_NODE4] = "\\li1120{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE2][TOC_NODE5] = "\\li1680{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE2][TOC_NODE6] = "\\li2240{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE2][TOC_NODE7] = "\\li2800{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE2][TOC_NODE8] = "\\li3360{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE2][TOC_NODE9] = "\\li3920{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE3][TOC_NODE3] = "{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE3][TOC_NODE4] = "\\li560{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE3][TOC_NODE5] = "\\li1120{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE3][TOC_NODE6] = "\\li1680{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE3][TOC_NODE7] = "\\li2240{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE3][TOC_NODE8] = "\\li2800{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE3][TOC_NODE9] = "\\li3360{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE4][TOC_NODE4] = "{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE4][TOC_NODE5] = "\\li560{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE4][TOC_NODE6] = "\\li1120{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE4][TOC_NODE7] = "\\li1680{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE4][TOC_NODE8] = "\\li2240{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE4][TOC_NODE9] = "\\li2800{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE5][TOC_NODE5] = "{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE5][TOC_NODE6] = "\\li560{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE5][TOC_NODE7] = "\\li1120{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE5][TOC_NODE8] = "\\li1680{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE5][TOC_NODE9] = "\\li2240{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE6][TOC_NODE6] = "{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE6][TOC_NODE7] = "\\li560{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE6][TOC_NODE8] = "\\li1120{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE6][TOC_NODE9] = "\\li1680{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE7][TOC_NODE7] = "{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE7][TOC_NODE8] = "\\li560{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE7][TOC_NODE9] = "\\li1120{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE8][TOC_NODE8] = "{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE8][TOC_NODE9] = "\\li560{%s}\\par\\pard";
		form_t_nonumbers[TOC_NODE9][TOC_NODE9] = "{%s}\\par\\pard";
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		for (d = TOC_NODE1; d < TOC_MAXDEPTH; d++)
			for (d2 = d; d2 < TOC_MAXDEPTH; d2++)
			{
				form_t_nonumbers[d][d2] = "<li>%s";
			}
		break;

	case TOTEX:
	case TOPDL:
		for (d = TOC_NODE1; d < TOC_MAXDEPTH; d++)
			for (d2 = d; d2 < TOC_MAXDEPTH; d2++)
			{
				form_t_nonumbers[d][d2] = "\\item %s";
			}
		break;

	case TOINF:
		for (d = TOC_NODE1; d < TOC_MAXDEPTH; d++)
			for (d2 = d; d2 < TOC_MAXDEPTH; d2++)
			{
				form_t_nonumbers[d][d2] = "%s";
			}
		break;

	case TOKPS:
		form_t_nonumbers[TOC_NODE1][TOC_NODE1] = " %s newline";
		form_t_nonumbers[TOC_NODE1][TOC_NODE2] = "    %s newline";
		form_t_nonumbers[TOC_NODE1][TOC_NODE3] = "       %s newline";
		form_t_nonumbers[TOC_NODE1][TOC_NODE4] = "          %s newline";
		form_t_nonumbers[TOC_NODE1][TOC_NODE5] = "             %s newline";
		form_t_nonumbers[TOC_NODE1][TOC_NODE6] = "                %s newline";
		form_t_nonumbers[TOC_NODE1][TOC_NODE7] = "                   %s newline";
		form_t_nonumbers[TOC_NODE1][TOC_NODE8] = "                      %s newline";
		form_t_nonumbers[TOC_NODE1][TOC_NODE9] = "                         %s newline";
		form_t_nonumbers[TOC_NODE2][TOC_NODE2] = " %s newline";
		form_t_nonumbers[TOC_NODE2][TOC_NODE3] = "    %s newline";
		form_t_nonumbers[TOC_NODE2][TOC_NODE4] = "       %s newline";
		form_t_nonumbers[TOC_NODE2][TOC_NODE5] = "          %s newline";
		form_t_nonumbers[TOC_NODE2][TOC_NODE6] = "             %s newline";
		form_t_nonumbers[TOC_NODE2][TOC_NODE7] = "               %s newline";
		form_t_nonumbers[TOC_NODE2][TOC_NODE8] = "                  %s newline";
		form_t_nonumbers[TOC_NODE2][TOC_NODE9] = "                     %s newline";
		form_t_nonumbers[TOC_NODE3][TOC_NODE3] = " %s newline";
		form_t_nonumbers[TOC_NODE3][TOC_NODE4] = "    %s newline";
		form_t_nonumbers[TOC_NODE3][TOC_NODE5] = "       %s newline";
		form_t_nonumbers[TOC_NODE3][TOC_NODE6] = "          %s newline";
		form_t_nonumbers[TOC_NODE3][TOC_NODE7] = "             %s newline";
		form_t_nonumbers[TOC_NODE3][TOC_NODE8] = "                %s newline";
		form_t_nonumbers[TOC_NODE3][TOC_NODE9] = "                   %s newline";
		form_t_nonumbers[TOC_NODE4][TOC_NODE4] = " %s newline";
		form_t_nonumbers[TOC_NODE4][TOC_NODE5] = "    %s newline";
		form_t_nonumbers[TOC_NODE4][TOC_NODE6] = "      %s newline";
		form_t_nonumbers[TOC_NODE4][TOC_NODE7] = "         %s newline";
		form_t_nonumbers[TOC_NODE4][TOC_NODE8] = "           %s newline";
		form_t_nonumbers[TOC_NODE4][TOC_NODE9] = "             %s newline";
		form_t_nonumbers[TOC_NODE5][TOC_NODE5] = " %s newline";
		form_t_nonumbers[TOC_NODE5][TOC_NODE6] = "    %s newline";
		form_t_nonumbers[TOC_NODE5][TOC_NODE7] = "       %s newline";
		form_t_nonumbers[TOC_NODE5][TOC_NODE8] = "          %s newline";
		form_t_nonumbers[TOC_NODE5][TOC_NODE9] = "             %s newline";
		form_t_nonumbers[TOC_NODE6][TOC_NODE6] = " %s newline";
		form_t_nonumbers[TOC_NODE6][TOC_NODE7] = "    %s newline";
		form_t_nonumbers[TOC_NODE6][TOC_NODE8] = "       %s newline";
		form_t_nonumbers[TOC_NODE6][TOC_NODE9] = "          %s newline";
		form_t_nonumbers[TOC_NODE7][TOC_NODE7] = " %s newline";
		form_t_nonumbers[TOC_NODE7][TOC_NODE8] = "    %s newline";
		form_t_nonumbers[TOC_NODE7][TOC_NODE9] = "       %s newline";
		form_t_nonumbers[TOC_NODE8][TOC_NODE8] = " %s newline";
		form_t_nonumbers[TOC_NODE8][TOC_NODE9] = "    %s newline";
		form_t_nonumbers[TOC_NODE9][TOC_NODE9] = " %s newline";
		break;

	default:
		form_t_nonumbers[TOC_NODE1][TOC_NODE1] = " %s";
		form_t_nonumbers[TOC_NODE1][TOC_NODE2] = "    %s";
		form_t_nonumbers[TOC_NODE1][TOC_NODE3] = "       %s";
		form_t_nonumbers[TOC_NODE1][TOC_NODE4] = "          %s";
		form_t_nonumbers[TOC_NODE1][TOC_NODE5] = "             %s";
		form_t_nonumbers[TOC_NODE1][TOC_NODE6] = "                %s";
		form_t_nonumbers[TOC_NODE1][TOC_NODE7] = "                   %s";
		form_t_nonumbers[TOC_NODE1][TOC_NODE8] = "                      %s";
		form_t_nonumbers[TOC_NODE1][TOC_NODE9] = "                         %s";
		form_t_nonumbers[TOC_NODE2][TOC_NODE2] = " %s";
		form_t_nonumbers[TOC_NODE2][TOC_NODE3] = "    %s";
		form_t_nonumbers[TOC_NODE2][TOC_NODE4] = "       %s";
		form_t_nonumbers[TOC_NODE2][TOC_NODE5] = "          %s";
		form_t_nonumbers[TOC_NODE2][TOC_NODE6] = "             %s";
		form_t_nonumbers[TOC_NODE2][TOC_NODE7] = "               %s";
		form_t_nonumbers[TOC_NODE2][TOC_NODE8] = "                  %s";
		form_t_nonumbers[TOC_NODE2][TOC_NODE9] = "                     %s";
		form_t_nonumbers[TOC_NODE3][TOC_NODE3] = " %s";
		form_t_nonumbers[TOC_NODE3][TOC_NODE4] = "    %s";
		form_t_nonumbers[TOC_NODE3][TOC_NODE5] = "       %s";
		form_t_nonumbers[TOC_NODE3][TOC_NODE6] = "          %s";
		form_t_nonumbers[TOC_NODE3][TOC_NODE7] = "             %s";
		form_t_nonumbers[TOC_NODE3][TOC_NODE8] = "                %s";
		form_t_nonumbers[TOC_NODE3][TOC_NODE9] = "                   %s";
		form_t_nonumbers[TOC_NODE4][TOC_NODE4] = " %s";
		form_t_nonumbers[TOC_NODE4][TOC_NODE5] = "    %s";
		form_t_nonumbers[TOC_NODE4][TOC_NODE6] = "      %s";
		form_t_nonumbers[TOC_NODE4][TOC_NODE7] = "         %s";
		form_t_nonumbers[TOC_NODE4][TOC_NODE8] = "           %s";
		form_t_nonumbers[TOC_NODE4][TOC_NODE9] = "             %s";
		form_t_nonumbers[TOC_NODE5][TOC_NODE5] = " %s";
		form_t_nonumbers[TOC_NODE5][TOC_NODE6] = "    %s";
		form_t_nonumbers[TOC_NODE5][TOC_NODE7] = "       %s";
		form_t_nonumbers[TOC_NODE5][TOC_NODE8] = "          %s";
		form_t_nonumbers[TOC_NODE5][TOC_NODE9] = "             %s";
		form_t_nonumbers[TOC_NODE6][TOC_NODE6] = " %s";
		form_t_nonumbers[TOC_NODE6][TOC_NODE7] = "    %s";
		form_t_nonumbers[TOC_NODE6][TOC_NODE8] = "       %s";
		form_t_nonumbers[TOC_NODE6][TOC_NODE9] = "          %s";
		form_t_nonumbers[TOC_NODE7][TOC_NODE7] = " %s";
		form_t_nonumbers[TOC_NODE7][TOC_NODE8] = "    %s";
		form_t_nonumbers[TOC_NODE7][TOC_NODE9] = "       %s";
		form_t_nonumbers[TOC_NODE8][TOC_NODE8] = " %s";
		form_t_nonumbers[TOC_NODE8][TOC_NODE9] = "    %s";
		form_t_nonumbers[TOC_NODE9][TOC_NODE9] = " %s";
		break;
	}
}





/*******************************************************************************
*
*  init_module_toc_pass2():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_toc_pass2(void)
{
	char sF[128];
	char sS[128];
	TOCTYPE d;

	init_toc_forms_no_numbers();
	init_toc_forms_numbers();

	if (use_compressed_tocs)
	{
		for (d = TOC_NODE1; d < TOC_MAXDEPTH - 1; d++)
			subtocs_depth[d] = 1;
	}

	for (d = TOC_NODE1; d < TOC_MAXDEPTH - 1; d++)
		if (subtocs_depth[d] <= 0 || subtocs_depth[d] > TOC_MAXDEPTH)
			subtocs_depth[d] = TOC_MAXDEPTH;

	/* Die Formatkommando angeben, die fuer die Inhaltsausgabe */
	/* verwendet werden, um die Einrueckungen der Listen zu erzeugen */
	switch (desttype)
	{
	case TOHAH:
	case TOHTM:
	case TOMHH:
		toc_list_top = "<ul class=\"content\">";
		toc_list_end = "</ul>";
		use_toc_list_commands = TOCL_HTM;
		break;

	case TOTEX:
	case TOPDL:
		toc_list_top = "\\begin{itemize}\n\\itemsep 0pt\n\\parsep 0pt\n\\parskip 0pt";
		toc_list_end = "\\end{itemize}";
		use_toc_list_commands = TOCL_TEX;
		break;

	default:
		toc_list_top = "";
		toc_list_end = "";
		use_toc_list_commands = TOCL_NONE;
		break;
	}

	if (html_frames_layout)
		sprintf(html_target, " target=\"%s\"", FRAME_NAME_CON);
	else
		html_target[0] = EOS;

	/* Font-Tags vorbestimmen */
	sF[0] = 0;
	sS[0] = 0;
	sHtmlPropfontStart[0] = EOS;
	sHtmlPropfontEnd[0] = EOS;
	iDocHtmlPropfontSize = 0;

	if (sDocHtmlPropfontName[0] != EOS)
	{
		sprintf(sF, " face=\"%s\"", sDocHtmlPropfontName);
	}

	if (sDocHtmlPropfontSize[0] != EOS)
	{
		sprintf(sS, " size=\"%s\"", sDocHtmlPropfontSize);
		iDocHtmlPropfontSize = atoi(sDocHtmlPropfontSize);
	}

	if (sF[0] != EOS || sS[0] != EOS)
	{
		sprintf(sHtmlPropfontStart, "<font%s%s>", sF, sS);
		strcpy(sHtmlPropfontEnd, "</font>");
	}

	sF[0] = 0;
	sS[0] = 0;

	sHtmlMonofontStart[0] = EOS;
	sHtmlMonofontEnd[0] = EOS;
	iDocHtmlMonofontSize = 0;

	if (sDocHtmlMonofontName[0] != EOS)
	{
		sprintf(sF, " face=\"%s\"", sDocHtmlMonofontName);
	}

	if (sDocHtmlMonofontSize[0] != EOS)
	{
		sprintf(sS, " size=\"%s\"", sDocHtmlMonofontSize);
		iDocHtmlMonofontSize = atoi(sDocHtmlMonofontSize);
	}

	if (sF[0] != EOS || sS[0] != EOS)
	{
		sprintf(sHtmlMonofontStart, "<font%s%s>", sF, sS);
		strcpy(sHtmlMonofontEnd, "</font>");
	}
#if USE_KWSET
	if (kwset != NULL)
		if (kwsprep(kwset) == FALSE)
		{
			kwsfree(kwset);
			kwset = NULL;
		}
#endif
}





/*******************************************************************************
*
*  check_module_toc_pass1():
*     ??? (description missing)
*
*  Return:
*      TRUE: check was OK
*     FALSE: an issue has been found
*
******************************************|************************************/

GLOBAL _BOOL check_module_toc_pass1(void)
{
	LABIDX i, j;
	char sTyp[1024];
	char sNode[256];
	_BOOL ret = TRUE;
	_BOOL checkString;

	/* Schauen, ob bei Hypertextformaten Dinge eindeutig benutzt werden */
	switch (desttype)
	{
	case TOHAH:
	case TOHTM:
	case TOMHH:
	case TOWIN:
	case TOWH4:
	case TOPCH:
	case TOSTG:
	case TOAMG:
	case TOTEX:
	case TOPDL:
	case TOLYX:
		show_status_info(_("Checking nodes, labels and aliases..."));
		for (i = 1; i <= p1_lab_counter; i++)
		{
			for (j = i + 1; j <= p1_lab_counter; j++)
			{
				if (strcmp(label_table[i]->name, label_table[j]->name) == 0)
				{
					error_message(_("label \"%s\" used twice"), label_table[i]->name);

					sNode[0] = EOS;
					sprintf(sTyp, _("as a label in %s:%lu"), file_lookup(label_table[i]->source_location.id), label_table[i]->source_location.line);
					if (label_table[i]->is_node)
						sprintf(sTyp, _("as a node in %s:%lu"), file_lookup(label_table[i]->source_location.id), label_table[i]->source_location.line);
					if (label_table[i]->is_alias)
						sprintf(sTyp, _("as an alias in %s:%lu"), file_lookup(label_table[i]->source_location.id), label_table[i]->source_location.line);
					if (!label_table[i]->is_node)
						sprintf(sNode, _(" in node '%s'"), toc_table[label_table[i]->tocindex]->nodename);
					note_message("1. %s%s", sTyp, sNode);

					sNode[0] = EOS;
					sprintf(sTyp, _("as a label in %s:%lu"), file_lookup(label_table[j]->source_location.id), label_table[j]->source_location.line);
					if (label_table[j]->is_node)
						sprintf(sTyp, _("as a node in %s:%lu"), file_lookup(label_table[j]->source_location.id), label_table[j]->source_location.line);
					if (label_table[j]->is_alias)
						sprintf(sTyp, _("as an alias in %s:%lu"), file_lookup(label_table[j]->source_location.id), label_table[j]->source_location.line);
					if (!label_table[j]->is_node)
						sprintf(sNode, _(" in node '%s'"), toc_table[label_table[j]->tocindex]->nodename);
					note_message("2. %s%s", sTyp, sNode);

					ret = FALSE;
				}
			}
		}
		break;
	}

	/* Doppelt vergebene HTML-Dateinamen testen, dabei das Mergen von Nodes beachten */
	/* Werden Nodes in einer Datei vereint, dann besitzen die unteren Ebenen den */
	/* gleichen Dateinamen wie die obere Ebene! */

	switch (desttype)
	{
	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (!html_merge_node[TOC_NODE1])
		{
			TOCIDX i, j;
			int level, d;

			show_status_info(_("Checking HTML file names..."));
			for (i = 0; i <= p1_toc_counter; i++)
			{
				for (j = i + 1; j <= p1_toc_counter; j++)
				{
					checkString = TRUE;

					for (level = TOC_MAXDEPTH - 1; level >= TOC_NODE2; level--)
						if (html_merge_node[level])
						{
							checkString = FALSE;
							for (d = TOC_NODE1; d < level; d++)
								if (toc_table[i]->n[d] != toc_table[j]->n[d])
								{
									checkString = TRUE;
									break;
								}
						}

					if (checkString && strcmp(toc_table[i]->filename, toc_table[j]->filename) == 0)
					{
						error_message(_("file name \"%s\" used in \"%s\" and \"%s\""),
									  toc_table[i]->filename, toc_table[i]->nodename, toc_table[j]->nodename);

						ret = FALSE;
					}
				}
			}
		}
		break;
	}

	return ret;
}





/*******************************************************************************
*
*  check_module_toc_pass2():
*     pass 2 check: see if labels or aliases have been (auto-)referenced
*
*  Return:
*     TRUE
*
******************************************|************************************/

GLOBAL _BOOL check_module_toc_pass2(void)
{
	LABIDX i;

	show_status_info("");
	show_status_info(_("Checking usage of labels and aliases..."));
	for (i = 1; i <= p1_lab_counter; i++)
	{
		if (!label_table[i]->referenced)
		{
			if (!label_table[i]->is_node)
			{
				LABEL *lab = label_table[i];

				TOCITEM *toc = toc_table[lab->tocindex];

				note_message(_("%s %lu: label/alias '%s' in node '%s' wasn't referenced"),
							 file_lookup(lab->source_location.id), lab->source_location.line, lab->name, toc->nodename);
			}
		}
	}

	return TRUE;
}


/*
 * needed to detect structure gaps
 * in the appendix, e.g.
 * !begin_appendix
 * ...
 * !subnode
 */
GLOBAL void toc_pass1_begin_appendix(void)
{
	TOCTYPE i;

	for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
		last_n_index[i] = 0;
	p1_toctype = TOC_NONE;
}


GLOBAL void toc_pass2_begin_appendix(void)
{
/*
    TOCTYPE i;
    
    for (i = TOC_NODE2; i < TOC_MAXDEPTH; i++)
        last_n_index[i] = 0;
*/
	p2_toctype = TOC_NONE;
}



/*******************************************************************************
*
*  node2NrWinhelp():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2NrWinhelp(char *s, LABIDX li)
{
	sprintf(s, "UDON%05X", li + 1);
}





/*******************************************************************************
*
*  alias2NrWinhelp():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void alias2NrWinhelp(char *s, LABIDX li)
{
	sprintf(s, "UDOA%05X", li + 1);
}





/*******************************************************************************
*
*  label2NrWinhelp():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void label2NrWinhelp(char *s, LABIDX li)
{
	sprintf(s, "UDOL%05X", li + 1);
}





/*******************************************************************************
*
*  node2NrIPF():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2NrIPF(char *s, LABIDX li)
{
	sprintf(s, "UDON%05X", li + 1);
}





/*******************************************************************************
*
*  alias2NrIPF():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void alias2NrIPF(char *s, LABIDX li)
{
	sprintf(s, "UDOA%05X", li + 1);
}





/*******************************************************************************
*
*  label2NrIPF():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void label2NrIPF(char *s, LABIDX li)
{
	sprintf(s, "UDOL%05X", li + 1);
}





/*******************************************************************************
*
*  node2pchelp():
*     convert quotation marks to a Pure C Help convenient format
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2pchelp(char *s)
{
	qreplace_all(s, "\"", 1, "_0x20_", 6);
}





/*******************************************************************************
*
*  node2postscript():
*     adjust label or node for PostScript
*
*  Notes:
*     PostScript doesn't like spaces or other special characters in labels or nodes.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2postscript(char *s, int text)
{
	switch (text)
	{
	case KPS_PS2DOCINFO:
		qreplace_all(s, "\\[", 2, "[", 1);
		qreplace_all(s, "\\]", 2, "]", 1);
		break;

	case KPS_DOCINFO2PS:
		qreplace_all(s, "[", 1, "\\[", 2);
		qreplace_all(s, "]", 1, "\\]", 2);
		break;

	case KPS_NODENAME:
		{
			size_t tlen;

			if (titdat.author == NULL)
				tlen = 0;
			else
				tlen = strlen(titdat.author);
			if ((strlen(s) + tlen) > 80)
			{
				s[80] = EOS;
				if (s[79] == '\\')
					s[79] = EOS;
				strcat(s, "...\0");
			}
		}
		qreplace_all(s, "(", 1, "\\(", 2);
		qreplace_all(s, ")", 1, "\\)", 2);
		qreplace_all(s, "[", 1, "\\[", 2);
		qreplace_all(s, "]", 1, "\\]", 2);
		break;

	case KPS_CONTENT:
		qreplace_all(s, "/", 1, "\\/", 2);
		qreplace_all(s, "(", 1, "\\(", 2);
		qreplace_all(s, ")", 1, "\\)", 2);
		qreplace_all(s, "[", 1, "\\[", 2);
		qreplace_all(s, "]", 1, "\\]", 2);
		break;

	case KPS_BOOKMARK:
		if (strlen(s) > 32L)
		{
			s[32] = EOS;
			if (s[31] == '\\')
				s[31] = EOS;
		}
		qreplace_all(s, "/", 1, "\\/", 2);
		qreplace_all(s, "\\", 1, "\\\\", 2);
		qreplace_all(s, "(", 1, "\\(", 2);
		qreplace_all(s, ")", 1, "\\)", 2);
		qreplace_all(s, "[", 1, "\\[", 2);
		qreplace_all(s, "]", 1, "\\]", 2);
		break;

	case KPS_NAMEDEST:
		qreplace_all(s, " ", 1, "_", 1);
		qdelete_all(s, ";", 1);
		qdelete_all(s, ":", 1);
		qdelete_all(s, "/", 1);
		qdelete_all(s, "\\[", 2);
		qdelete_all(s, "[", 1);
		qdelete_all(s, "\\(", 2);
		qdelete_all(s, "(", 1);
		qdelete_all(s, "\\]", 2);
		qdelete_all(s, "]", 1);
		qdelete_all(s, "\\)", 2);
		qdelete_all(s, ")", 1);
		qdelete_all(s, "-", 1);
		qdelete_last(s, "_", 1);
		break;
	}
}





/*******************************************************************************
*
*  node2stg():
*     replace or remove all chars not allowed in an ST-Guide node
*
*  Notes:
*     @symbol ari "..."
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2stg(char *s)
{
	qreplace_all(s, "\\", 1, "\\\\", 2);
	qreplace_all(s, "\"", 1, "\\\"", 2);
}





/*******************************************************************************
*
*  index2stg():
*     replace or remove all chars not allowed in an ST-Guide label
*
*  Notes:
*     Function is identical to node2stg(), but this may change in the future.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void index2stg(char *s)
{
	qreplace_all(s, "\\", 1, "\\\\", 2);
	qreplace_all(s, "\"", 1, "\\\"", 2);
}





/*******************************************************************************
*
*  init_module_toc():
*     initialize TOC module
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL void init_module_toc(void)
{
	register int i;

	/* -------------------------------------------------------------- */
	/* In diesen Flags merkt sich UDO, welche Art von Node gerade     */
	/* aktiv ist (!node, !subnode, etc.)                              */
	/* -------------------------------------------------------------- */
	active_nodetype = TOC_NONE;


	/* -------------------------------------------------------------- */
	/* toc_offset enthaelt einen Offset fuer die Kapitelnumerierung   */
	/* Das erste Kapitel erhaelt dann die Nummer (1 + toc_offset)     */
	/* toc_offset kann auch negativ werden.                           */
	/* Die anderen Offsets entsprechend                               */
	/* -------------------------------------------------------------- */
	for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
		toc_offset[i] = 0;

	/* -------------------------------------------------------------- */
	/* Wenn auch nur ein Node existiert, dann kann ein !toc           */
	/* ausgegeben werden. toc_available wird dann TRUE                */
	/* -------------------------------------------------------------- */
	toc_available = FALSE;
	apx_available = FALSE;


	for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
	{
		/* -------------------------------------------------------------- */
		/* Hier werden die absoluten Kapitelnummern vermerkt. Diese       */
		/* Nummern weichen von den Nummern in den Inhaltsverzeichnissen   */
		/* ab, falls unsichtbare Nodes (!node*) benutzt werden.           */
		/* Beispiele:                                                     */
		/* 1  Node:        n1=1, n2=0, n3=0, n4=0                         */
		/* 1.2  Node:      n1=1, n2=2, n3=0, n4=0                         */
		/* 1.2.3  Node:    n1=1, n2=2, n3=3, n4=0                         */
		/* 1.2.3.4  Node:  n1=1, n2=2, n3=3, n4=4                         */
		/* -------------------------------------------------------------- */
		p1_toc_n[i] = 0;
		p1_apx_n[i] = 0;
		p2_toc_n[i] = 0;
		p2_apx_n[i] = 0;

		/* -------------------------------------------------------------- */
		/* Hier nun die Nummern, wie sie im Inhaltsverzeichis erscheinen  */
		/* -------------------------------------------------------------- */
		p1_toc_nr[i] = 0;
		p1_apx_nr[i] = 0;
	}

	/* -------------------------------------------------------------- */
	/* In diesen Variablen werden die Indizes der letzten Kapitel     */
	/* gesichert. Sie sind sehr wichtig, um die Links zu den          */
	/* uebergeordneten Kapiteln in Hypertexten ohne lange Sucherei    */
	/* erstellen zu koennen.                                          */
	/* -------------------------------------------------------------- */
	for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
		last_n_index[i] = 0;

	/* -------------------------------------------------------------- */
	/* Dieses Flag wird TRUE gesetzt, wenn das Inhaltsverzeichnis     */
	/* mit !tableofcontents aufgerufen wird. Nodes koenne dann auf    */
	/* dieses Inhaltsverzeichnis verweisen (z.B: ST-Guide per @toc)   */
	/* -------------------------------------------------------------- */
	called_tableofcontents = FALSE;

	/* -------------------------------------------------------------- */
	/* Diese Variable wird auf die tiefste benutzte Gliederungsebene  */
	/* gesetzt. In der LaTeX-Preambel muessen dann einige             */
	/* Befehle zusaetzlich ausgegeben werden.                         */
	/* -------------------------------------------------------------- */
	toc_maxdepth = TOC_NODE1 - 1;

	/* -------------------------------------------------------------- */
	/* p1_toc_counter enthaelt die Anzahl der in pass1() eingelesenen */
	/* Eintraege fuer das toc_table[]-Array. Nach pass1() enthaelt    */
	/* toc_table[p1_toc_counter] die Daten des letzten Kapitels.      */
	/* p2_toc_counter ist entsprechend ein Zaehler fuer den pass2().  */
	/* Waehrend pass2() zeigt p2_toc_counter auf den aktuellen Eintrag */
	/* des toc_table[]-Arrays.                                        */
	/* -------------------------------------------------------------- */
	p1_toc_counter = 0;
	p2_toc_counter = 0;

	/* -------------------------------------------------------------- */
	/* toc_table[]-Array ausnullen und Inhaltsverzeichnis "eintragen" */
	/* -------------------------------------------------------------- */
	p1_toc_alloc = 0;
	toc_table = NULL;
	add_toc_to_toc();


	/* -------------------------------------------------------------- */
	/* label_table[]-Array mit den Daten der referenzierbaren Stellen des     */
	/* Dokumentes ausnullen und Zaehler zuruecksetzen.                */
	/* -------------------------------------------------------------- */
	p1_lab_alloc = 0;
	label_table = NULL;
	p1_lab_counter = 0;
	p2_lab_counter = 0;

	/* -------------------------------------------------------------- */
	/* Kapitelzaehler zuruecksetzen                                   */
	/* -------------------------------------------------------------- */
	for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
		all_nodes[i] = 0;

	/* -------------------------------------------------------------- */
	/* Die Zeichen setzen, die beim Referenzieren vor und nach einem  */
	/* gefundenen Label erlaubt sind.                                 */
	/* -------------------------------------------------------------- */

	{
		const char *s;

		for (i = 0; i < 256; i++)
			allowed_next_chars[i] = 0;
		s = "\033 !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~\177";
		while (*s != EOS)
		{
			allowed_next_chars[(unsigned char) *s] = 1;
			s++;
		}
		allowed_next_chars[EOS] = 1;
		allowed_next_chars[TILDE_C] = 1;
		allowed_next_chars[NBSP_C] = 1;
		allowed_next_chars[INDENT_C] = 1;
		memcpy(allowed_prev_chars, allowed_next_chars, sizeof(allowed_prev_chars));
	}

	uses_tableofcontents = FALSE;

	current_chapter_name[0] = EOS;
	current_chapter_nr[0] = EOS;

	footer_buffer[0] = EOS;

	for (i = 0; i < TOC_MAXDEPTH - 1; i++)
		subtocs_depth[i] = TOC_MAXDEPTH;

	no_auto_toptocs_icons = FALSE;

	strcpy(html_modern_width, "128");
	html_modern_backcolor.set = FALSE;

	strcpy(html_frames_width, "128");
	strcpy(html_frames_height, "64");

	html_frames_backcolor.set = FALSE;
	html_frames_textcolor.set = FALSE;
	html_frames_linkcolor.set = FALSE;
	html_frames_alinkcolor.set = FALSE;
	html_frames_vlinkcolor.set = FALSE;
	html_frames_position = POS_LEFT;
	html_frames_backimage = 0;
	html_name_prefix[0] = EOS;
	html_header_links = 0;

	p1_toctype = TOC_NONE;
	p2_toctype = TOC_NONE;

	sHtmlPropfontStart[0] = EOS;
	sHtmlPropfontEnd[0] = EOS;

	sHtmlMonofontStart[0] = EOS;
	sHtmlMonofontEnd[0] = EOS;

	html_frames_toc_title = NULL;
	html_frames_con_title = NULL;

	refs_counter = 0;
	refs_alloc = 0;
	refs = NULL;

#if USE_NAME_HASH
	memset(hash, 0, sizeof(hash));
#endif
#if USE_KWSET
	if (!config.bNoFastAutoref)
		if ((kwset = kwsalloc(NULL)) == NULL)
		{
		}
#endif

	in_about_udo = FALSE;
	stg_need_endnode = FALSE;
}





void free_style_list(STYLELIST * list)
{
	int i;

	for (i = 0; i < list->count; i++)
	{
		free(list->style[i]->media);
		free(list->style[i]->title);
		free(list->style[i]);
	}
	free(list->style);
	list->alloc = 0;
	list->count = 0;
	list->style = NULL;
}


void free_script_list(SCRIPTLIST * list)
{
	int i;

	for (i = 0; i < list->count; i++)
	{
		free(list->script[i]);
	}
	free(list->script);
	list->alloc = 0;
	list->count = 0;
	list->script = NULL;
}


/*******************************************************************************
*
*  exit_module_toc():
*     exit TOC module
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void exit_module_toc(void)
{
	register TOCIDX i;
	int j;
	LABIDX l;

	if (toc_table != NULL)
	{
		for (i = 0; i <= p1_toc_counter; i++)
		{
			TOCITEM *item = toc_table[i];

			free(item->keywords);
			free(item->description);
			free(item->helpid);
			for (j = 0; j < MAX_WIN_BUTTONS; j++)
				free(item->win_button[j]);
			free(item->image);
			free(item->icon);
			free(item->icon_active);
			free(item->icon_text);
			free_style_list(&item->styles);
			free_script_list(&item->scripts);
			if (item->nodetitle != item->nodename)
				free(item->nodetitle);
			free(item);
		}
		free(toc_table);
	}
	toc_table = NULL;
	p1_toc_counter = 0;
	p1_toc_alloc = 0;

	if (label_table != NULL)
	{
		for (l = 1; l <= p1_lab_counter; l++)
		{
			free(label_table[l]);
		}
		free(label_table);
	}
	label_table = NULL;
	p1_lab_counter = 0;
	p1_lab_alloc = 0;

	reset_refs();
	if (refs != NULL)
	{
		free(refs);
		refs = NULL;
	}
	refs_alloc = 0;

#if USE_KWSET
	if (kwset != NULL)
	{
		kwsfree(kwset);
		kwset = NULL;
	}
#endif
}
