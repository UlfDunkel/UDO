/*	##############################################################
	# @(#) udo.c
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
	##############################################################
	# Start:	Januar 1995
	# Version:	2. Oktober 2001
	##############################################################	*/

#ifndef ID_UDO_C
#define ID_UDO_C
const char *id_udo_c= "@(#) udo.c       09.10.2001";
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>
#include "portab.h"

#include "version.h"	/* WICHTIGE Makros!					*/
#include "constant.h"	/* WICHTIGE Makros!					*/
#include "commands.h"	/* UDO-Kommandos					*/
#include "udo_type.h"	/* diverse Typen					*/

#include "abo.h"		/* Ausgabe einer Infoseite			*/
#include "cfg.h"		/* Konfiguration lesen/schreiben	*/
#include "chr.h"		/* Zeichensatzumwandlungen			*/
#include "env.h"		/* Umgebungen verwalten				*/
#include "file.h"		/* Aufsplitten von Dateinamen		*/
#include "img.h"		/* Ausgabe/Einbindung von Grafiken	*/
#include "msg.h"		/* Fehlermeldungen erzeugen			*/
#include "par.h"		/* (!...) Parameter bearbeiten		*/
#include "str.h"		/* Manipulation von Strings			*/
#include "sty.h"		/* Textstilumwandlungen				*/
#include "tab.h"		/* Tabellensatz						*/
#include "toc.h"		/* !node, !alias, !label, !toc		*/
#include "tp.h"			/* Titelseite (!maketitle)			*/

#include "gui.h"		/* Funktionen GUI-/CLI-Version		*/

#include "export.h"
#include "udo.h"		/* globale Prototypen				*/



/*	############################################################
	# Makros
	############################################################	*/

#if !__AddLFToNL__
#define NL "\n"
#else
#define NL "\n\r"	/* MO */
#endif

/*	############################################################
	# Konstanten
	############################################################	*/
/*	------------------------------------------------------
	Datum-Konstanten (Umlaut in Maerz besonders beachten!)
	Innerhalb init_lang() und init_lang_date() werden
	die Zeichen des "Universal Charset" angepasst.
	------------------------------------------------------	*/

/* Deutsch */
LOCAL const char *MONTH_GER[]=
{	"Januar", "Februar", "M(!\"a)rz", "April", "Mai", "Juni",
	"Juli", "August", "September", "Oktober", "November", "Dezember"
};

/* Niederlaendisch */
LOCAL const char *MONTH_DUT[]=
{	"januari", "februari", "maart", "april", "mei", "juni",
	"juli", "augustus", "september", "oktober", "november", "december"
};

/* Englisch */
LOCAL const char *MONTH_ENG[]=
{	"January", "February", "March", "April", "May", "June",
	"July", "August", "September", "October", "November", "December"
};

/* Franzoesisch */
LOCAL const char *MONTH_FRA[]=
{	"janvier", "f(!'e)vrier", "mars", "avril", "mai", "juin",
	"juillet", "ao(!^u)t", "septembre", "octobre", "novembre", "d(!'e)cembre"
};

/* Italienisch */
LOCAL const char *MONTH_ITA[]=
{	"Gennaio", "Febbraio", "Marzo", "Aprile", "Maggio", "Giugno",
	"Luglio", "Agosto", "Settembre", "Ottobre", "Novembre", "Dicembre"
};

/* Schwedisch */
LOCAL const char *MONTH_SWE[]=
{	"Januari", "Februari", "Mars", "April", "Maj", "Juni",
	"Juli", "Augusti", "September", "Oktober", "November", "December"
};

/* Spanisch */
LOCAL const char *MONTH_SPA[]=
{	"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
	"Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
};




/*	############################################################
	#
	# lokale Variablen
	#
	############################################################	*/


LOCAL BOOLEAN		format_needs_exact_toklen;
LOCAL BOOLEAN		format_uses_output_buffer;
LOCAL BOOLEAN		format_protect_commands;

LOCAL BOOLEAN		out_lf_needed;			/* Fehlt noch ein Linefeed? */
LOCAL unsigned int	outlines;				/* Anzahl gesicherter Zeilen */

LOCAL char		*tobuffer;					/* Puffer fuer token_output()			*/
LOCAL size_t	tomaxlen;					/* spaeteste Umbruchstelle in t_o()		*/

LOCAL BOOLEAN	bDocSloppy;					/* Kurze Zeilen bemaengeln?				*/
LOCAL BOOLEAN	no_verbatim_umlaute;		/* In verbatim Umlaute entfernen?		*/
LOCAL BOOLEAN	use_output_buffer;			/* Erst puffern, dann ausgeben?			*/

LOCAL char		timer_start[16];			/* Uhrzeiten fuer Start und Stopp		*/
LOCAL char		timer_stop[16];

LOCAL char		silbe[MAXSILBEN][MAX_TOKEN_LEN+1]; /* Ein Array mit Silben				*/
LOCAL int		silben_counter;				/* Der passende Zaehler					*/

LOCAL BOOLEAN	bHypSaved;
LOCAL BOOLEAN	bIdxSaved;
LOCAL BOOLEAN	bTreeSaved;
LOCAL BOOLEAN	bCmdSaved;
LOCAL BOOLEAN	bHpjSaved;
LOCAL BOOLEAN	bCntSaved;
LOCAL BOOLEAN	bUPRSaved;
LOCAL BOOLEAN	bMapSavedC, bMapSavedPas, bMapSavedVB, bMapSavedGFA;
LOCAL BOOLEAN	bHhpSaved, bHhcSaved, bHhkSaved;

LOCAL int	iFilesOpened;						/* Anzahl geoeffneter Files		*/
LOCAL UINT	uiFileLines[MAXFILECOUNTER];			/* Zeilen geoeffneter Files		*/
LOCAL char	sFileNames[MAXFILECOUNTER][512+1];	/* Namen geoeffneter Files		*/

/*	------------------------------------------------------------------------	*/

/* IF-Stack fuer !if-Umgebungen sowie Flags fuer pass1() und pass2() */
#define	IF_NONE		0
#define	IF_GENERAL	1
#define	IF_DEST		2
#define	IF_LANG		3
#define	IF_SET		4
#define	IF_OS		5

typedef struct _if_stack_item
{	int		kind;
	BOOLEAN	ignore;
	char	filename[512];
	UINT	fileline;
}	IF_STACK_ITEM;

#define	MAX_IF_STACK	32	/*r6pl2: 32 statt 10, auf Nummer sicher */

LOCAL IF_STACK_ITEM		if_stack[MAX_IF_STACK+1];
LOCAL int				counter_if_stack;

/*	------------------------------------------------------------------------	*/

LOCAL unsigned long		lPass1Lines, lPass2Lines;			/* fuer die Prozentangabe */

/*	------------------------------------------------------------------------	*/

typedef struct _hyplist
{
	char	data[128];
	struct _hyplist	*next;
}	HYPLIST;

LOCAL HYPLIST *hyplist;

/*	------------------------------------------------------------------------	*/

typedef struct _idxlist
{
	char	letter;						/* Hier soll der Eintrag einsortiert werden */
	int		depth;						/* Indextiefe: 1, 2 oder 3 */
	char	chapter[MAX_NODE_LEN+1];	/* In diesem Kapitel gesetzt */
	char	idx[3][128];				/* Die Index-Daten */
	struct _idxlist	*next;
}	IDXLIST;

LOCAL IDXLIST *idxlist;


/*	############################################################
	#
	# lokale Prototypen
	#
	############################################################	*/
#include "udolocal.h"


/*	############################################################
	#
	# Funktionen
	#
	# die Tabellen sollten nach der Wahrscheinlichkeit sortiert
	# werden, mit dem ein Kommando aufgerufen wird, um Suchzeiten
	# zu verringern. Die Kapitel-Kommandos sollten dabei ganz
	# oben stehen, weniger gebraeuchliche Kommandos ganz zum
	# Schluss.
	#
	############################################################	*/
#define	CMD_ALWAYS			0
#define	CMD_ONLY_PREAMBLE	1
#define	CMD_ONLY_MAINPART	2

typedef	void (*CMDPROC)(void);

typedef struct _udocommand		/* ---- Funktionentabelle ----		*/
{	char		magic[30];	/* UDO-Kommando						*/
	char		macut[8];	/* Shortcut des Kommandos			*/
	CMDPROC	proc;			/* zugehoerige Routine				*/
	BOOLEAN	reset;			/* Tokens danach loeschen?			*/
	int		pos;			/* Erlaubnis Vorspann/Hauptteil		*/
}	UDOCOMMAND;

LOCAL const UDOCOMMAND udoCmdSeq[]=
{
	{ "!node",						"!n",		c_node,					TRUE,	CMD_ONLY_MAINPART	},
	{ "!subnode",					"!sn",		c_subnode,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!subsubnode",				"!ssn",		c_subsubnode,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!subsubsubnode",				"!sssn",	c_subsubsubnode,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!node*",						"!n*",		c_node_iv,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!subnode*",					"!sn*",		c_subnode_iv,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!subsubnode*",				"!ssn*",	c_subsubnode_iv,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!subsubsubnode*",			"!sssn*",	c_subsubsubnode_iv,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!pnode",						"!p",		c_pnode,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!psubnode",					"!ps",		c_psubnode,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!psubsubnode",				"!pss",		c_psubsubnode,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!psubsubsubnode",			"!psss",	c_psubsubsubnode,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!pnode*",					"!p*",		c_pnode_iv,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!psubnode*",					"!ps*",		c_psubnode_iv,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!psubsubnode*",				"!pss*",	c_psubsubnode_iv,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!psubsubsubnode*",			"!psss*",	c_psubsubsubnode_iv,	TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_node",				"!bn",		c_begin_node,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_node*",				"!bn*",		c_begin_node_iv,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_pnode",				"!bp",		c_begin_pnode,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_pnode*",				"!bp*",		c_begin_pnode_iv,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_node",					"!en",		c_end_node,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!item",						"!i",		c_item,					FALSE,	CMD_ONLY_MAINPART	},
	{ "!begin_itemize",				"!bi",		c_begin_itemize,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_itemize",				"!ei",		c_end_itemize,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_enumerate",			"!be",		c_begin_enumerate,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_enumerate",				"!ee",		c_end_enumerate,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_description",			"!bd",		c_begin_description,	TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_description",			"!ed",		c_end_description,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_xlist",				"!bxl",		c_begin_xlist,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_xlist",					"!exl",		c_end_xlist,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_blist",				"!bbl",		c_begin_blist,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_blist",					"!ebl",		c_end_blist,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_ilist",				"!bil",		c_begin_ilist,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_ilist",					"!eil",		c_end_ilist,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_tlist",				"!btl",		c_begin_tlist,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_tlist",					"!etl",		c_end_tlist,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_quote",				"!bq",		c_begin_quote,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_quote",					"!eq",		c_end_quote,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_center",				"!bc",		c_begin_center,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_center",				"!ec",		c_end_center,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_flushright",			"!bfr",		c_begin_flushright,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_flushright",			"!efr",		c_end_flushright,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_flushleft",			"!bfl",		c_begin_flushleft,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_flushleft",				"!efl",		c_end_flushleft,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!label",						"!l",		c_label,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!alias",						"!a",		c_alias,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!index",						"!x",		c_index,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!heading",					"!h",		c_heading,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!subheading",				"!sh",		c_subheading,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!subsubheading",				"!ssh",		c_subsubheading,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!subsubsubheading",			"!sssh",	c_subsubsubheading,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!listheading",				"!lh",		c_listheading,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!listsubheading",			"!lsh",		c_listsubheading,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!listsubsubheading",			"!lssh",	c_listsubsubheading,	TRUE,	CMD_ONLY_MAINPART	},
	{ "!listsubsubsubheading",		"!lsssh",	c_listsubsubsubheading,	TRUE,	CMD_ONLY_MAINPART	},
	{ "!jumpid",					"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!win_helpid",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!wh4_helpid",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!mapping",					"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!html_name",					"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!html_dirname",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!html_keywords",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!html_description",			"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!html_backimage",			"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!html_backcolor",			"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!html_textcolor",			"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!html_linkcolor",			"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!html_alinkcolor",			"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!html_vlinkcolor",			"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!html_verbatim_backcolor",	"",			c_verbatim_backcolor,	TRUE,	CMD_ALWAYS			},
	{ "!html_counter_command",		"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!html_javascript",			"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!hh_backimage",				"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!hh_backcolor",				"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!hh_textcolor",				"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!hh_linkcolor",				"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!hh_alinkcolor",				"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!hh_vlinkcolor",				"",			c_tunix,				TRUE,	CMD_ALWAYS			},
	{ "!hh_verbatim_backcolor",		"",			c_verbatim_backcolor,	TRUE,	CMD_ALWAYS			},
	{ "!chapterimage",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!chaptericon",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!chaptericon_active",		"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!chaptericon_text",			"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!newpage",					"",			c_newpage,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!comment",					"",			c_comment,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!include",					"",			c_include,				TRUE,	CMD_ALWAYS			},
	{ "!vinclude",					"",			c_include_verbatim,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!rinclude",					"",			c_include_raw,			TRUE,	CMD_ALWAYS			},
	{ "!sinclude",					"",			c_include_src,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!cinclude",					"",			c_include_comment,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!ldinclude",					"",			c_include_linedraw,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!pinclude",					"",			c_include_preformatted,	TRUE,	CMD_ONLY_MAINPART	},
	{ "!input",						"",			c_input,				TRUE,	CMD_ALWAYS			},
	{ "!image",						"",			c_image,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!image*",					"",			c_image_nonr,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!bigskip",					"",			c_bigskip,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!medskip",					"",			c_medskip,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!smallskip",					"",			c_smallskip,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!tex_dpi",					"",			c_tex_dpi,				TRUE,	CMD_ALWAYS			},
	{ "!tex_verb",					"",			c_tex_verb,				TRUE,	CMD_ALWAYS			},
	{ "!maketitle",					"",			c_maketitle,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!tableofcontents",			"",			c_tableofcontents,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!listoffigures",				"",			c_listoffigures,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!listoftables",				"",			c_listoftables,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!toc",						"",			c_toc,					TRUE,	CMD_ONLY_MAINPART	},
	{ "!subtoc",					"",			c_subtoc,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!subsubtoc",					"",			c_subtoc,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!subsubsubtoc",				"",			c_subtoc,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_appendix",			"",			c_begin_appendix,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!end_appendix",				"",			c_end_appendix,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!begin_document",			"",			c_begin_document,		TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!end_document",				"",			c_end_document,			TRUE,	CMD_ONLY_MAINPART	},
	{ "!sloppy",					"",			c_sloppy,				TRUE,	CMD_ALWAYS			},
	{ "!fussy",						"",			c_fussy,				TRUE,	CMD_ALWAYS			},
	{ "!code",						"",			c_code,					TRUE,	CMD_ALWAYS			},
	{ "!autoref",					"",			c_autoref,				TRUE,	CMD_ALWAYS			},
	{ "!autoref_items",				"",			c_autoref_items,		TRUE,	CMD_ALWAYS			},
	{ "!hline",						"",			c_hline,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!table_caption",				"",			c_table_caption,		TRUE,	CMD_ONLY_MAINPART	},
	{ "!table_caption*",			"",			c_table_caption_nonr,	TRUE,	CMD_ONLY_MAINPART	},
	{ "!universal_charset",			"",			c_universal_charset,	TRUE,	CMD_ALWAYS			},
	{ "!win_charwidth",				"",			c_win_charwidth,		TRUE,	CMD_ALWAYS			},
	{ "!wh4_charwidth",				"",			c_wh4_charwidth,		TRUE,	CMD_ALWAYS			},
	{ "!rtf_charwidth",				"",			c_rtf_charwidth,		TRUE,	CMD_ALWAYS			},
	{ "!rtf_keep_tables",			"",			c_rtf_keep_tables,		TRUE,	CMD_ALWAYS			},
	{ "!html_img_suffix",			"",			c_html_img_suffix,		TRUE,	CMD_ALWAYS			},
	{ "!html_nodesize",				"",			c_html_nodesize,		TRUE,	CMD_ALWAYS			},
	{ "!htag_img_suffix",			"",			c_htag_img_suffix,		TRUE,	CMD_ALWAYS			},
	{ "!tabwidth",					"",			c_tabwidth,				TRUE,	CMD_ALWAYS			},
	{ "!verbatimsize",				"",			c_verbatimsize,			TRUE,	CMD_ALWAYS			},
	{ "!linedrawsize",				"",			c_linedrawsize,			TRUE,	CMD_ALWAYS			},
	{ "!set",						"",			c_set,					TRUE,	CMD_ALWAYS			},
	{ "!unset",						"",			c_unset,				TRUE,	CMD_ALWAYS			},
	{ "!drc_bcolor",				"",			c_drc_bcolor,			TRUE,	CMD_ALWAYS			},
	{ "!drc_icolor",				"",			c_drc_icolor,			TRUE,	CMD_ALWAYS			},
	{ "!drc_ucolor",				"",			c_drc_ucolor,			TRUE,	CMD_ALWAYS			},
	{ "!use_raw_header",			"",			c_tunix,				TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!use_raw_footer",			"",			c_tunix,				TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!udolink",					"",			c_udolink,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!toplink",					"",			c_toplink,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!endnode",					"",			c_endnode,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_subtoc",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_subsubtoc",			"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_subsubsubtoc",		"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_links",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_index",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_title",				"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_headline",			"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_bottomline",			"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_raw_header",			"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!ignore_raw_footer",			"",			c_tunix,				TRUE,	CMD_ONLY_MAINPART	},
	{ "!macro",						"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!define",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!hyphen",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!docinfo",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!doclayout",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	}, /* New in r6pl15 [NHz] */
	{ "!toc_offset",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!subtoc_offset",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!subsubtoc_offset",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!subsubsubtoc_offset",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!table_counter",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!table_alignment",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!image_counter",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!image_alignment",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!tex_lindner",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!tex_strunk",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!tex_emtex",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!tex_miktex",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!tex_tetex",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!tex_2e",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_name_prefix",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_no_xlist",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_backpage",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_propfont_name",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_propfont_size",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_monofont_name",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_monofont_size",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_merge_nodes",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_merge_subnodes",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_merge_subsubnodes",	"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_merge_subsubsubnodes",	"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_ignore_8bit",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_modern_layout",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_modern_width",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_modern_alignment",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_modern_backcolor",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_modern_backimage",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_layout",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_width",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_alignment",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_height",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_position",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_backcolor",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_textcolor",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_linkcolor",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_alinkcolor",	"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_vlinkcolor",	"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_frames_backimage",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_doctype",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},	/* New in r6pl16 [NHz] */
	{ "!html_style_name",		"",			c_tunix,	TRUE,	CMD_ALWAYS	}, /* New in r6pl15 [NHz] */
	{ "!html_script_name",		"",			c_tunix,	TRUE,	CMD_ALWAYS	}, /* New in r6pl15 [NHz] */
	{ "!html_favicon_name",		"",			c_tunix,	TRUE,	CMD_ALWAYS	}, /* New in r6pl15 [NHz] */
	{ "!html_button_alignment",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_switch_language",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_transparent_buttons",	"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!html_use_folders",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!rtf_propfont",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!rtf_monofont",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!rtf_propfont_size",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!rtf_monofont_size",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!rtf_no_tables",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_propfont",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_monofont",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_propfont_size",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_monofont_size",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_backcolor",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_textcolor",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_linkcolor",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_background",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_inline_bitmaps",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_high_compression",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_medium_compression",	"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_old_keywords",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_propfont",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_monofont",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_propfont_size",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_monofont_size",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_backcolor",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_textcolor",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_background",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_inline_bitmaps",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_high_compression",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_medium_compression",	"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_old_keywords",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!win_prefix_helpids",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!wh4_prefix_helpids",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!pdf_high_compression",		"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!pdf_medium_compression",	"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!parwidth",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!sort_hyphen_file",			"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!man_lpp",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!man_type",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!drc_flags",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!nroff_type",				"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!language",					"",			cmd_outside_preamble,	TRUE,	CMD_ONLY_PREAMBLE	},
	{ "!break",						"",			c_break,				TRUE,	CMD_ALWAYS			},
	{ "!error",						"",			c_error,				TRUE,	CMD_ALWAYS			},
	{ "!nop",						"",			c_nop,					TRUE,	CMD_ALWAYS			},
};


#define	MAXSWITCH	40

LOCAL const UDOSWITCH udoswitch[MAXSWITCH+1]=
{
	{ "!use_auto_subtocs",			&use_auto_subtocs		,	'i',	"!depth",		&subtocs1_depth	},
	{ "!use_auto_subsubtocs",		&use_auto_subsubtocs	,	'i',	"!depth",		&subtocs2_depth	},
	{ "!use_auto_subsubsubtocs",	&use_auto_subsubsubtocs	,	'i',	"!depth",		&subtocs3_depth	},
	{ "!use_auto_toptocs",			&use_auto_toptocs		,	'b',	"!no_icons",	&no_auto_toptocs_icons	},
	{ "!use_short_envs",			&use_short_envs			,	'\0',	"",				NULL			},
	{ "!use_short_tocs",			&use_short_tocs			,	'\0',	"",				NULL			},
	{ "!use_formfeed",				&use_formfeed			,	'\0',	"",				NULL			},
	{ "!use_chapter_images",		&use_chapter_images		,	'\0',	"",				NULL			},
	{ "!use_about_udo",				&use_about_udo			,	'\0',	"",				NULL			},
	{ "!use_ansi_tables",			&use_ansi_tables		,	'\0',	"",				NULL			},
	{ "!use_style_book",			&use_style_book			,	'\0',	"",				NULL			},
	{ "!use_justification",			&use_justification		,	'\0',	"",				NULL			},
	{ "!use_output_buffer",			&use_output_buffer		,	'\0',	"",				NULL			},
	{ "!use_nodes_inside_index",	&use_nodes_inside_index	,	'\0',	"",				NULL			},
	{ "!use_alias_inside_index",	&use_alias_inside_index	,	'\0',	"",				NULL			},
	{ "!use_label_inside_index",	&use_label_inside_index	,	'\0',	"",				NULL			},
	{ "!use_udo_index",				&use_udo_index			,	'\0',	"",				NULL			},
	{ "!use_mirrored_indices",		&use_mirrored_indices	,	'\0',	"",				NULL			},
	{ "!use_comments",				&use_comments			,	'\0',	"",				NULL			},
	{ "!use_auto_helpids",			&use_auto_helpids		,	'\0',	"",				NULL			},
	{ "!no_index",					&no_index				,	'\0',	"",				NULL			},
	{ "!no_images",					&no_images				,	'\0',	"",				NULL			},
	{ "!no_img_size",				&no_img_size			,	'\0',	"",				NULL			},
	{ "!no_numbers",				&no_numbers				,	'\0',	"",				NULL			},
	{ "!no_umlaute",				&no_umlaute				,	'\0',	"",				NULL			},
	{ "!no_8bit",					&no_umlaute				,	'\0',	"",				NULL			},
	{ "!no_xlinks",					&no_xlinks				,	'\0',	"",				NULL			},
	{ "!no_urls",					&no_urls				,	'\0',	"",				NULL			},
	{ "!no_links",					&no_links				,	'\0',	"",				NULL			},
	{ "!no_verbatim_umlaute",		&no_verbatim_umlaute	,	'\0',	"",				NULL			},
	{ "!no_effects",				&no_effects				,	'\0',	"",				NULL			},
	{ "!no_quotes",					&no_quotes				,	'\0',	"",				NULL			},
	{ "!no_preamble",				&no_preamble			,	'\0',	"",				NULL			},
	{ "!no_titles",					&no_titles				,	'\0',	"",				NULL			},
	{ "!no_headlines",				&no_headlines			,	'\0',	"",				NULL			},
	{ "!no_bottomlines",			&no_bottomlines			,	'\0',	"",				NULL			},
	{ "!no_popup_headlines",		&no_popup_headlines		,	'\0',	"",				NULL			},
	{ "!no_footers",				&no_footers				,	'\0',	"",				NULL			},
	{ "!no_buttons",				&no_buttons				,	'\0',	"",				NULL			},
	{ "!no_sourcecode",				&no_sourcecode			,	'\0',	"",				NULL			},
	{ "!no_table_lines",			&no_table_lines			,	'\0',	"",				NULL			},
};


typedef struct _udolanguage		/* ---- Sprachentabelle ----	*/
{	char	magic[25];		/* UDO-Kommando					*/
	int	langval;			/* zugehoerige Sprache			*/
}	UDOLANGUAGE;

/* Changed in r6pl16 [NHz] */
#define	MAXLANGUAGE	11

LOCAL const UDOLANGUAGE udolanguage[MAXLANGUAGE]=
{
	{ "danish",			TODAN	},
	{ "dutch",		TODUT	},
	{ "english",	TOENG	},
	{ "finnish",		TOFIN	},
	{ "french",		TOFRA	},
	{ "german",		TOGER	},
	{ "italian",	TOITA	},
	{ "norwegian",	TONOR	},
	{ "portuguese",	TOPOR	},
	{ "spanish",	TOSPA	},
	{ "swedish",	TOSWE	},
};



typedef struct _udocharset		/* ---- Zeichensatztabelle ----	*/
{	char	magic[16];			/* code-Parameter				*/
	int	codepage;				/* zugehoeriger Zeichensatz		*/
}	UDOCHARSET;

#define	MAXCHARSET	15

LOCAL const UDOCHARSET udocharset[MAXCHARSET]=
{
	{ "dos",		CODE_437		},
	{ "os2",		CODE_850		},
	{ "cp437",		CODE_437		},
	{ "cp850",		CODE_850		},
	{ "hp8",		CODE_HP8		},
	{ "iso-8859-1",	CODE_LAT1		},
	{ "iso",		CODE_LAT1		},
	{ "latin1",		CODE_LAT1		},
	{ "mac",		CODE_MAC		},
	{ "next",		CODE_NEXT		},
	{ "tos",		CODE_TOS		},
	{ "utf-8",		CODE_UTF8		},
	{ "utf8",		CODE_UTF8		},
	{ "sys",		SYSTEM_CHARSET	},
	{ "win",		CODE_LAT1		},
};

GLOBAL char compile_date[11] = "\0";
GLOBAL char compile_time[9]  = "\0";


/*	######################################################################
	#
	# Zentrale Ausgabe-Routinen. Hier werden Strings in eine Datei
	# geschrieben. Nirgends im Sourcecode wird direkt ins Outfile
	# geschrieben, es laeuft alles ueber outln(), out() unf voutlnf()
	#
	######################################################################	*/

#define	MAN_HEADLINES		2
#define	MAN_BOTTOMLINES		3

GLOBAL void outln (const char *s)
{	/* Aenderungen muessen auch in voutf() beruecksichtigt werden!!! */
	if (desttype==TOMAN && iManPageLength>0)
	{	if (iManPageLines>=iManPageLength-MAN_BOTTOMLINES)
		{	man_bottomline();
			iManPagePages++;
			iManPageLines= 0;
			if (out_lf_needed)
			{	if (!bTestmode)
				{	fprintf(outfile.file, NL);
				}
				outlines++;
			}
			man_headline();
		}
		iManPageLines++;
	}
	
	if (!bTestmode)
	{	fprintf(outfile.file, "%s" NL, s);
	}
	
	outlines++;
	out_lf_needed= FALSE;
}	/* outln */


GLOBAL void voutlnf ( const char *fmt, ... )
{
	va_list ap;

	if (!bTestmode)
	{	va_start(ap, fmt);
		vfprintf(outfile.file, fmt, ap);
		va_end(ap);
	}
	outln("");
}	/* voutlnf */



GLOBAL void out (const char *s)
{	/* Aenderungen muessen auch in voutf() beruecksichtigt werden!!! */
	if (!bTestmode)
	{	fprintf(outfile.file, "%s", s);
	}
	out_lf_needed= TRUE;
}	/* out */



GLOBAL void voutf ( const char *fmt, ... )
{
	va_list ap;

	if (!bTestmode)
	{	va_start(ap, fmt);
		vfprintf(outfile.file, fmt, ap);
		va_end(ap);
	}
	out_lf_needed= TRUE;
}	/* voutf */



/*	######################################################################
	#
	#     String-Manipulation
	#
	######################################################################	*/
/*	----------------------------------------------------------------------
	stringcenter()
	Aufgabe:	Zentriert einen String innerhalb <length> Zeichen
				Ist der String laenger, wird er nicht gekuerzt
	->	length: Laenge des zentrierten Strings
	<->	string:	Zeiger auf den String
	----------------------------------------------------------------------	*/
GLOBAL void stringcenter (char *string, size_t length)
{
	char	s[256];
	size_t	sl, add;

	sl = toklen(string);
	
	if (sl>=length)
	{	return;
	}

	add= (length-sl)/2;	
	memset(s, ' ', add+1);
	s[add+1]= EOS;
	strcpy(s+add, string);
	strcpy(string, s);
	
}	/* stringcenter */



/*	----------------------------------------------------------------------
	strcenter()
	Aufgabe:	Zentriert einen String innerhalb <length> Zeichen
				oder kuerzt ihn, wenn er zu lang ist
	->	length: Laenge des zentrierten Strings
	<->	string:	Zeiger auf den String
	----------------------------------------------------------------------	*/
GLOBAL void strcenter(char *string, size_t length)
{
	char	s[256];
	size_t	sl, add;
	
	sl = toklen(string);
	
	if (sl==length)
	{	return;
	}
	
	if ( sl > length)
	{	/* Der String ist laenger als die uebergebene Laenge, also */
		/* nicht zentrieren, sondern String kuerzen. */
		string[length] = EOS;
		return;
	}
	
	add= (length-sl)/2;
	memset(s, ' ', add+1);
	s[add+1]= EOS;
	strcpy(s+add, string);
	strcpy(string, s);
	
}	/* strcenter */



/*	------------------------------------------------------------
	outlncenter()
	Aufgabe:	Ausgabe eines zentrierten Strings
	->			s:	der String
	------------------------------------------------------------	*/
GLOBAL void outlncenter ( char *s )
{
	char tmp[512];
	
	strcpy(tmp, s);

	strcenter(tmp, zDocParwidth);
	
	outln(tmp);
}	/*outlncenter*/



/*	------------------------------------------------------------
	outlncenter()
	Aufgabe:	Ausgabe eines zentrierten Strings mit Auffuellen
				durch Leerzeichen (fuer DRC)
	->			s:	der String
	------------------------------------------------------------	*/
GLOBAL void outlncenterfill ( char *s )
{
	char tmp[512];
	size_t sl;
	
	strcpy(tmp, s);

	strcenter(tmp, zDocParwidth);

	sl=strlen(tmp);
	while (sl<zDocParwidth)
	{	strcat(tmp, " ");
		sl++;
	}
	
	outln(tmp);
}	/*outlncenterfill*/



/*	----------------------------------------------------------------------
	strright()
	Aufgabe:	Formatiert einen String rechtsbuendig auf <length> Zeichen
				Falls er zu lang ist, wird er gekuerzt.
	->	length: Laenge des rechtsbuendigen Strings
	<->	string:	Zeiger auf den String
	----------------------------------------------------------------------	*/
GLOBAL void strright(char *string, size_t length)
{
	char	s[256];
	size_t	sl, add;
	
	sl = toklen(string);
	
	if (sl==length)
	{	return;
	}
	
	if ( sl > length)
	{	/* Der String ist laenger als die uebergebene Laenge, also */
		/* nicht ausrichten, sondern String kuerzen. */
		string[length] = EOS;
		return;
	}
	
#if 1
	/* Diese Methode ist um Faktor 5 schneller als sprintf() */

	add= length - sl;
	memset(s, ' ', add+1);
	s[add+1]= EOS;
	strcpy(s+add, string);
#else
	sprintf(s, "%*s", length, string);
#endif

	strcpy(string, s);
	
}	/* strright */



/*	----------------------------------------------------------
	Blocksatz fuer Strings, die nicht mit einem	Space beginnen
	->	s:		Auszurichtender String
		len:	Breite
	----------------------------------------------------------	*/
#define	MAXBLANKPOS		256

LOCAL size_t 	blankpos[MAXBLANKPOS+1];	/* Positionen der Blanks	*/
LOCAL BOOLEAN	justify_from_right;			/* Blanks rechts einfuegen?	*/

LOCAL void strjustify ( char *s, size_t len )
{
	size_t	sl, tl, i;
	int count, pos, j;
	BOOLEAN	is_verbed;

	if (s[0]==' ' || s[0]==EOS)
	{	return;
	}
	
	if ( len>MAXBLANKPOS )
	{	return;
	}

	tl= toklen(s);

	if (tl>len)
	{	return;
	}

	sl= strlen(s);

	count= -1;
	
	is_verbed= styleflag.verbatim;
	
	for (i=0; i<sl; i++)
	{
		if (!is_verbed)		/* Nur die, die nicht in (!V)...(!v) stehen */
		{	if (s[i]==' ')
			{	count++;
				blankpos[count]= i;
			}
		}
		
		if ( s[i]==STYLEMAGIC[0] && s[i+1]==STYLEMAGIC[1] )
		{	switch (s[i+2])
			{	case C_VERB_ON:		is_verbed= TRUE;	break;
				case C_VERB_OFF:	is_verbed= FALSE;	break;
			}
			i+= 4;
		}
	}
	
	if (count<0)
	{	return;
	}

	if (justify_from_right)
	{	pos= count;
		while (tl<len)
		{	strinsert(s+blankpos[pos], " ");
			tl++;
			for (j=pos; j<=count; j++)
			{	blankpos[j]++;
			}
			pos--;
			if (pos<0)
			{	pos= count;
			}
		}
	}
	else
	{	pos= 0;
		while (tl<len)
		{	strinsert(s+blankpos[pos], " ");
			tl++;
			for (j=pos; j<=count; j++)
			{	blankpos[j]++;
			}
			pos++;
			if (pos>count)
			{	pos= 0;
			}
		}
	}

	justify_from_right= !justify_from_right;

}	/* strjustify */


/*	------------------------------------------------------------
	output_ascii_line()
	Aufgabe:	Ausgabe einer Linie
	->	c:		das Zeichen, aus dem die Linie bestehen soll
		len:	die Laenge der Linie
	------------------------------------------------------------	*/
GLOBAL void output_ascii_line ( const char *c, const size_t len )
{
	char s[512];
	
	memset(s, c[0], len);
	s[len]= EOS;
	outln(s);	

}	/*output_ascii_line*/



/*	############################################################
	#
	# Fehlermeldungen fuer Kommandos ausgeben, die nur im
	# Vorspann oder nur ausserhalb des Vorspanns benutzt
	# werden duerfen.
	#
	############################################################	*/
LOCAL void cmd_outside_preamble ( void )
{
	if (bInsideDocument)	
	{	error_outside_preamble(token[0]);
	}
}	/* cmd_outside_preamble */

LOCAL void cmd_inside_preamble ( void )
{
	if (!bInsideDocument)	
	{	error_inside_preamble(token[0]);
	}
}	/* cmd_inside_preamble */


/*	############################################################
	#
	# Testen, ob ein Kommando fuer die Ausgabesprache bzw.
	# das Ausgabeformat oder das aktuelle OS bestimmt ist
	#
	############################################################	*/
LOCAL BOOLEAN str_for_destlang ( const char *s )
{
	BOOLEAN flag= FALSE;
	register int i;

	for (i=0; i<MAXLANGUAGE; i++)
	{
		if ( destlang==udolanguage[i].langval )
		{
			if ( strstr(s, udolanguage[i].magic) )
			{	flag= TRUE;
				break;
			}
		}
	}

	if (strstr(s, "all")!=NULL)		flag= TRUE;
	if (strstr(s, "none")!=NULL)	flag= FALSE;
		
	return flag;
}	/* str_for_destlang */


GLOBAL BOOLEAN str_for_desttype ( const char *s )
{
	BOOLEAN flag= FALSE;

	switch (desttype)	/* vor r5pl6: Einzelabfragen */
	{
		case TOAMG:	flag= (strstr(s, "amg")!=NULL);		break;
		case TOAQV:	flag= (strstr(s, "aqv")!=NULL);		break;
		case TOASC:	flag= (strstr(s, "asc")!=NULL);		break;
		case TODRC:	flag= (strstr(s, "drc")!=NULL);		break;
		case TOHPH:	flag= (strstr(s, "htag")!=NULL);	break;
		case TOHTM:	flag= (strstr(s, "html")!=NULL);	break;
		case TOMHH:	flag= (strstr(s, "hh")!=NULL);		break;
		case TOIPF:	flag= (strstr(s, "ipf")!=NULL);		break;
		case TOLYX:	flag= (strstr(s, "lyx")!=NULL);		break;
		case TOMAN:	flag= (strstr(s, "man")!=NULL);		break;
		case TONRO:	flag= (strstr(s, "nroff")!=NULL);	break;
		case TOPCH:	flag= (strstr(s, "pch")!=NULL);		break;
		case TORTF:	flag= (strstr(s, "rtf")!=NULL);		break;
		case TOSRC:	flag= (strstr(s, "src")!=NULL);		break;
		case TOSRP:	flag= (strstr(s, "pas")!=NULL);		break;
		case TOSTG:	flag= (strstr(s, "stg")!=NULL);		break;
		case TOTEX:	flag= (strstr(s, "tex")!=NULL);		break;
		case TOPDL:	flag= (strstr(s, "pdf")!=NULL);		break;
		case TOWIN:	flag= (strstr(s, "win")!=NULL);		break;
		case TOWH4:	flag= (strstr(s, "wh4")!=NULL);		break;
		case TOINF:	flag= (strstr(s, "info")!=NULL);	break;
		case TOTVH:	flag= (strstr(s, "tvh")!=NULL);		break;
		case TOUDO:	flag= (strstr(s, "udo")!=NULL);		break;
		case TOKPS:	flag= (strstr(s, "ps")!=NULL);		break;
		case TOLDS:	flag= (strstr(s, "ldoc")!=NULL);	break;
	}
		
	if (strstr(s, "all")!=NULL)		flag= TRUE;
	if (strstr(s, "none")!=NULL)	flag= FALSE;
		
	return flag;
}	/* str_for_desttype */


GLOBAL BOOLEAN is_for_desttype (BOOLEAN *schalter, const char *cmd)
{
	register int i;
	BOOLEAN flag= FALSE;
	
	if (token_counter<=1)
	{	error_missing_parameter(cmd);
	}
	else
	{	for (i=0; i<token_counter; i++)
		{	if ( (flag=str_for_desttype(token[i]))==TRUE )
			{	break;
			}
		}
	}

	/* Problem: Default-Werte z.B. fuer Texinfo werden bei */
	/* !no_umlaute [asc] uberschrieben. Daher Schalter nur */
	/* noch im positiven Falle setzen. (r5pl16) */

	if (flag)
	{	*schalter= TRUE;
	}
	
	return flag;

}	/* is_for_desttype */


LOCAL BOOLEAN str_for_os ( const char *s )
{
	BOOLEAN flag;

	flag = FALSE;
	
#ifdef __BEOS__
	flag |= (strstr(s, "beos")!=NULL);
#endif

#ifdef __HPUX_ISO__
	flag |= (strstr(s, "hpux")!=NULL);
#endif

#ifdef __HPUX_ROMAN8__
	flag |= (strstr(s, "hpux")!=NULL);
#endif

#ifdef __LINUX__
	flag |= (strstr(s, "linux")!=NULL);
#endif

#ifdef __MACOS__
	flag |= (strstr(s, "macos")!=NULL);
#endif

#ifdef __MACOSX__
	flag |= (strstr(s, "macosx")!=NULL);
#endif

#ifdef __MSDOS__
	flag |= (strstr(s, "dos")!=NULL);
#endif

#ifdef __WIN32__
	flag |= (strstr(s, "dos")!=NULL);
	flag |= (strstr(s, "win")!=NULL);
#endif

#ifdef __NEXTSTEP__
	flag |= (strstr(s, "nextstep")!=NULL);
#endif

#ifdef __SINIX__
	flag |= (strstr(s, "sinix")!=NULL);
#endif

#ifdef __SUNOS__
	flag |= (strstr(s, "sunos")!=NULL);
#endif

#ifdef __TOS__
	flag |= (strstr(s, "tos")!=NULL);
#endif

	if (strstr(s, "all")!=NULL)		flag= TRUE;
	if (strstr(s, "none")!=NULL)	flag= FALSE;
		
	return flag;

}	/* str_for_os */



/*	############################################################
	#
	# Farben (gemaess W3C-HTML3.2-DTD)
	#
	############################################################	*/

typedef struct _udocolor
{	int val;
	char name[20];
	char html[8];
	char drc[3];
	char wintext[32];
	char winback[32];
	char wh4back[32];
}	UDOCOLOR;

#define	MAX_UDOCOLOR	17
LOCAL UDOCOLOR udocolor[MAX_UDOCOLOR+1]=	/* WinHelp4 BGR -> dezimal */
{
	{	BC_BLACK,	"black",	"#000000",	"\003@",	"",			",0,(0,0,0),(0,0,0)",				",(r0),(r0)"				},
	{	BC_SILVER,	"silver",	"#C0C0C0",	"\003G",	"\\cf2",	",0,(192,192,192),(192,192,192)",	",(r12632256),(r12632256)"	},
	{	BC_GRAY,	"gray",		"#808080",	"\003H",	"\\cf3",	",0,(128,128,128),(128,128,128)",	",(r8421504),(r8421504)"	},
	{	BC_WHITE,	"white",	"#FFFFFF",	"\003O",	"\\cf4",	"",									""							},
	{	BC_MAROON,	"maroon",	"#800000",	"\003D",	"\\cf5",	",0,(128,0,0),(128,0,0)",			",(r128),(r128)"			},
	{	BC_RED,		"red",		"#FF0000",	"\003L",	"\\cf6",	",0,(255,0,0),(255,0,0)",			",(r255),(r255)"			},
	{	BC_PURPLE,	"purple",	"#800080",	"\003E",	"\\cf7",	",0,(128,0,128),(128,0,128)",		",(r8388736),(r8388736)"	},
	{	BC_FUCHSIA,	"fuchsia",	"#FF00FF",	"\003M",	"\\cf8",	",0,(255,0,255),(255,0,255)",		",(r16711935),(r16711935)"	},
	{	BC_GREEN,	"green",	"#008000",	"\003B",	"\\cf9",	",0,(0,128,0),(0,128,0)",			",(r32768),(r32768)"		},
	{	BC_LIME,	"lime",		"#00FF00",	"\003J",	"\\cf10",	",0,(0,255,0),(0,255,0)",			",(r65280),(r65280)"		},
	{	BC_OLIVE,	"olive",	"#808000",	"\003J",	"\\cf11",	",0,(128,128,0),(128,128,0)",		",(r32896),(r32896)"		},
	{	BC_YELLOW,	"yellow",	"#FFFF00",	"\003N",	"\\cf12",	",0,(255,255,0),(255,255,0)",		",(r65535),(r65535)"		},
	{	BC_NAVY,	"navy",		"#000080",	"\003A",	"\\cf13",	",0,(0,0,128),(0,0,128)",			",(r8388608),(r8388608)"	},
	{	BC_BLUE,	"blue",		"#0000FF",	"\003I",	"\\cf14",	",0,(0,0,255),(0,0,255)",			",(r16711680),(r16711680)"	},
	{	BC_TEAL,	"teal",		"#008080",	"\003B",	"\\cf15",	",0,(0,128,128),(0,128,128)",		",(r8421376),(r8421376)"	},
	{	BC_AQUA,	"aqua",		"#00FFFF",	"\003C",	"\\cf16",	",0,(0,255,255),(0,255,255)",		",(r16776960),(r16776960)"	},
	{	BC_NONE,	"none",		"",			"",			"",			"",									""							},
};

LOCAL int get_color ( void )
{
	char n[1024];
	register int i;

	tokcpy2(n, 1024);

	for (i=0; i<MAX_UDOCOLOR; i++)
	{	if ( strstr(n, udocolor[i].name)!=NULL )
		{	return i;
		}
	}

	return BC_WHITE;
}	/* get_color */


GLOBAL BOOLEAN get_html_color ( const char *s, char *h )
{
	register int i;

	h[0]= EOS;

	for (i=0; i<MAX_UDOCOLOR; i++)
	{
		if ( strstr(s, udocolor[i].name)!=NULL )
		{
			strcpy(h, udocolor[i].html);
			return TRUE;
		}
	}

	return FALSE;

}	/* get_html_color */



LOCAL void get_drc_color ( const char *s, char *h )
{
	register int i;

	h[0]= EOS;

	for (i=0; i<MAX_UDOCOLOR; i++)
	{
		if ( strstr(s, udocolor[i].name)!=NULL )
		{
			strcpy(h, udocolor[i].drc);
			return;
		}
	}

}	/* get_drc_color */


LOCAL void c_drc_bcolor ( void )
{
	char color[256];
	
	tokcpy2(color, 256);
	get_drc_color(color, sDrcBcolor);

}	/* c_drc_bcolor */


LOCAL void c_drc_icolor ( void )
{
	char color[256];
	
	tokcpy2(color, 256);
	get_drc_color(color, sDrcIcolor);

}	/* c_drc_icolor */


LOCAL void c_drc_ucolor ( void )
{
	char color[256];
	
	tokcpy2(color, 256);
	get_drc_color(color, sDrcUcolor);

}	/* c_drc_ucolor */

LOCAL void c_drc_flags ( void )
{
	char s[256];
	
	tokcpy2(s, 256);
	iDrcFlags= atoi(s);

	if (iDrcFlags<0 || iDrcFlags>64)
	{	iDrcFlags= 0;
	}

}	/* c_drc_flags */


LOCAL void set_win_backcolor (char *s, const int c)
{
	s[0]= EOS;

	if (c>=0 || c<MAX_UDOCOLOR)
	{	strcpy(s, udocolor[c].winback);
	}
}	/*set_win_backcolor*/


LOCAL void set_win_textcolor (char *s, const int c)
{
	s[0]= EOS;

	if (c>=0 || c<MAX_UDOCOLOR)
	{	strcpy(s, udocolor[c].wintext);
	}
}	/*set_win_textcolor*/


LOCAL void set_win_linkcolor (char *s, const int c)
{
	s[0]= EOS;

	if (c>=0 || c<MAX_UDOCOLOR)
	{	strcpy(s, udocolor[c].wintext);
	}
}	/*set_win_linkcolor*/


LOCAL void set_wh4_backcolor (char *s, const int c)
{
	s[0]= EOS;

	if (c>=0 || c<MAX_UDOCOLOR)
	{	strcpy(s, udocolor[c].wh4back);
	}
}	/*set_wh4_backcolor*/


LOCAL void set_wh4_textcolor (char *s, const int c)
{
	s[0]= EOS;

	if (c>=0 || c<MAX_UDOCOLOR)
	{	strcpy(s, udocolor[c].wintext);
	}
}	/*set_wh4_textcolor*/


LOCAL void set_wh4_linkcolor (char *s, const int c)
{
	s[0]= EOS;

	if (c>=0 || c<MAX_UDOCOLOR)
	{	strcpy(s, udocolor[c].wintext);
	}
}	/*set_wh4_linkcolor*/


/*	############################################################
	#
	# Testen, ob bei einem Kommando [on] oder [off] benutzt wird
	#
	############################################################	*/
LOCAL BOOLEAN check_on ( void )
{
	char n[512];
	tokcpy2(n, 512);
	return ( strstr(n, "on")!=NULL );
}	/* check_on */


LOCAL BOOLEAN check_off ( void )
{
	char n[512];
	tokcpy2(n, 512);
	return ( strstr(n, "off")!=NULL );
}	/* check_off */



/*	############################################################
	#
	# Symbole (Commandline-Definitionen) verwalten
	#
	############################################################	*/
GLOBAL void del_udosymbol ( const char *s )
{
	BOOLEAN found= FALSE;
	register int i, j;
	
	if (udosymbol_counter>=0 && s[0]!=EOS)
	{
		for (i=0; i<=udosymbol_counter; i++)
		{	if ( strstr(s, udosymbol[i])!=NULL )
			{	for (j=i; j<udosymbol_counter; j++)
				{	strcpy(udosymbol[j], udosymbol[j+1]);
				}
				udosymbol[udosymbol_counter][0]= EOS;
				udosymbol_counter--;
				found= TRUE;
			}
		}
	}
	
	if (!found)
	{	error_unset_symbol(s);
	}
	
}	/* del_udosymbol */


GLOBAL void add_udosymbol ( const char *s )
{
	if (udosymbol_counter<MAX_UDOSYMBOLS)
	{	if (s[0]!=EOS)
		{	udosymbol_counter++;
			strcpy(udosymbol[udosymbol_counter], s);
		}
		else
		{	error_missing_parameter(CMD_SET);
		}
	}
	else
	{	error_too_many_symbols();
	}
	
}	/* add_udosymbol */


GLOBAL BOOLEAN udosymbol_set ( const char *s )
{
	register int i;
	
	if (udosymbol_counter>=0)
	{
		for (i=0; i<=udosymbol_counter; i++)
		{	if ( strstr(s, udosymbol[i])!=NULL )
			{	return TRUE;
			}
		}
	}

	return FALSE;
}	/* udosymbol_set */


LOCAL void c_set ( void )
{
	char s[512];
	
	tokcpy2(s, 512);
	add_udosymbol(s);
}

LOCAL void c_unset ( void )
{
	char s[512];
	
	tokcpy2(s, 512);
	del_udosymbol(s);
}



/*	############################################################
	#
	# Horizontale Trennlinien ausgeben
	#
	############################################################	*/
GLOBAL void c_hline ( void )
{
	int indent;
	char	n[128];
	
	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
			outln(HTML_HR);
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			strcpy_indent(n);
			voutlnf("%s\\sl30\\brdrt\\brdrs \\par\\pard\\par", n);
			break;
		case TOSTG:
		case TOAMG:
			indent=strlen_indent();
			voutlnf("@line %d %d 0 0 7", indent+1, ((int) zDocParwidth)-indent);	/*r6pl5*/
			outln("");
			break;
		case TOASC:
		case TOPCH:
		case TODRC:
			strcpy_indent(n);
			indent2space(n);
			out(n);
			output_ascii_line("-", zDocParwidth-strlen(n));
			outln("");
			break;
		case TOTVH:
			strcpy_indent(n);
			indent2space(n);
			if (n[0]==EOS)
			{	strcpy(n, " ");
			}
			out(n);
			output_ascii_line("\304", zDocParwidth-strlen(n));
			outln("");
			break;
		case TOSRC:
		case TOSRP:
			out("    ");
			output_ascii_line("-", zDocParwidth-strlen(n));
			break;
		case TOIPF:	/* <???> */
			break;
		case TOKPS:
			outln("hline");
			break;
	}

}	/* c_hline */




/*	############################################################
	#
	#
	# Indizes bearbeiten, verwalten und Indexregister ausgeben
	# -1: p < q
	#  1: p > q
	#  0: p == q
	#
	############################################################	*/

LOCAL int idxlist_compare (IDXLIST *p, IDXLIST *q)
{
	char ps[1024], qs[1024];
	
	ps[0]= EOS;
	qs[0]= EOS;

	strcat(ps, p->idx[0]);	strcat(ps, ", ");	
	if (p->depth>0)	strcat(ps, p->idx[1]);	strcat(ps, ", ");	
	if (p->depth>1)	strcat(ps, p->idx[2]);	strcat(ps, ", ");	
	strcat(ps, p->chapter);

	strcat(qs, q->idx[0]);	strcat(qs, ", ");	
	if (q->depth>0)	strcat(qs, q->idx[1]);	strcat(qs, ", ");	
	if (q->depth>1)	strcat(qs, q->idx[2]);	strcat(qs, ", ");	
	strcat(qs, q->chapter);
	
	return my_stricmp(ps, qs);

}	/* idxlist_compare */


LOCAL IDXLIST *idxlist_merge (IDXLIST *p, IDXLIST *q)
{
      IDXLIST *r, head;

      for ( r = &head; p && q; )
      {
            if ( idxlist_compare(p, q) < 0 )
            {
                  r = r->next = p;
                  p = p->next;
            }
            else
            {
                  r = r->next = q;
                  q = q->next;
            }
      }
      r->next = (p ? p : q);
      return head.next;
}

LOCAL IDXLIST *idxlist_sort (IDXLIST *p)
{
	  IDXLIST *q, *r;

      if ( p )
      {
            q = p;
            for ( r = q->next; r && (r = r->next) != NULL; r = r->next )
                  q = q->next;
            r = q->next;
            q->next = NULL;
            if ( r )
                  p = idxlist_merge(idxlist_sort(r), idxlist_sort(p));
      }
      return p;
}

/*	------------------------------------------------------------	*/

LOCAL IDXLIST * new_idxlist_item ( void )
{
	IDXLIST *l;

	l= (IDXLIST *) malloc (sizeof(IDXLIST));

	if (l!=NULL)
	{	memset(l, 0, sizeof(IDXLIST));
	}
	return l;
}


GLOBAL BOOLEAN add_idxlist_item ( const char *x1, const char *x2, const char *x3)
{
	IDXLIST *n;
	char c;

	if (no_index)
	{	return TRUE;
	}
	
	if (!use_udo_index)
	{	return TRUE;
	}

	if (x1[0]==EOS)
	{	return TRUE;
	}

	n= new_idxlist_item();

	if (n==NULL)
	{	error_malloc_failed();
		return FALSE;
	}

	strcpy(n->idx[0], x1);
	strcpy(n->idx[1], x2);
	strcpy(n->idx[2], x3);
	n->chapter[0]= EOS;
	
	del_internal_styles(n->idx[0]);
	del_internal_styles(n->idx[1]);
	del_internal_styles(n->idx[2]);


	/* Buchstaben bestimmen, unter dem der Eintrag einsortiert werden soll */
	/* <???> Achtung: Umlaute werden noch nicht beachtet! */

	c= (char) toupper(n->idx[0][0]);
	if ( c>='A' && c<='Z' )
	{	n->letter= c;
	}	
	else
	{	n->letter= '*';
	}

	n->depth= 0;

	if (n->idx[1][0]!=EOS)
	{	n->depth++;
		if (n->idx[2][0]!=EOS)
		{	n->depth++;
		}
	}

	switch (desttype)
	{
		case TOASC:
			if (no_numbers)
			{	strcpy(n->chapter, current_chapter_name);
			}
			else
			{	strcpy(n->chapter, current_chapter_nr);
			}
			break;
		case TOINF:
			strcpy(n->chapter, current_chapter_name);
			node2texinfo(n->chapter);
			break;

	}
	
	del_whitespaces(n->chapter);

	n->next= idxlist;
	idxlist= n;

	return TRUE;

}


LOCAL void sort_idxlist ( void )
{

	if (!use_udo_index)
	{	return;
	}
	
	if (idxlist==NULL)
	{	return;
	}

	show_status_info("");
	show_status_info("");
	show_status_info("Sorting index...");

	idxlist= idxlist_sort(idxlist);

}	/* sort_idxlist */


LOCAL void print_ascii_index ( void )
{
	IDXLIST *ptr, *prev;
	char thisc, lastc;
	BOOLEAN misslf= FALSE;
	BOOLEAN same1, same2, same3;

	if (!use_udo_index)
	{	return;
	}
	
	ptr= idxlist;
	prev= NULL;
	
	if (ptr==NULL)
	{	return;
	}

	outln("");
	if (use_style_book)
	{	output_ascii_line("=", zDocParwidth);
		outln(lang.index);
		output_ascii_line("=", zDocParwidth);
	}
	else	
	{	outln(lang.index);
		output_ascii_line("*", strlen(lang.index));
	}

	lastc= EOS;

	do
	{
		thisc= ptr->letter;

		if (toupper(thisc)!=toupper(lastc))
		{	if (misslf)
			{	outln("");
				misslf= FALSE;
			}
			outln("");
			lastc= thisc;
			prev= NULL;
		}

		same1= same2= same3= FALSE;
		
		if (prev!=NULL)
		{	if (strcmp(ptr->idx[0], prev->idx[0])==0)
			{	same1= TRUE;
			}
			if (ptr->depth>=1 && prev->depth>=1)
			{	same2= (strcmp(ptr->idx[1], prev->idx[1])==0);
			}
			if (ptr->depth>=2 && prev->depth>=2)
			{	same3= (strcmp(ptr->idx[2], prev->idx[2])==0);
			}
		}

		switch ( ptr->depth )
		{
			case 0:	/* Ein Index-Eintrag */
				if (same1)
				{	voutf(", %s", ptr->chapter);
					misslf= TRUE;
				}
				else
				{	if (misslf)	outln("");
					voutf("%s, %s", ptr->idx[0], ptr->chapter);
					misslf= TRUE;
				}
				break;

			case 1:	/* Zwei Index-Eintraege */
				if (same1)
				{
					if (same2)
					{	voutf(", %s", ptr->chapter);
						misslf= TRUE;
					}
					else
					{	if (misslf)
						{	outln("");
						}
						voutf("     %s, %s", ptr->idx[1], ptr->chapter);
						misslf= TRUE;
					}
				}
				else
				{	if (misslf)
					{	outln("");
					}
					outln(ptr->idx[0]);
					voutf("     %s, %s", ptr->idx[1], ptr->chapter);
					misslf= TRUE;
				}
				break;

			case 2:	/* Drei Index-Eintraege */
				if (same1)
				{	if (same2)
					{	if (same3)
						{	voutf(", %s", ptr->chapter);
							misslf= TRUE;
						}
						else
						{	if (misslf)
							{	outln("");
							}
							voutf("        %s, %s", ptr->idx[2], ptr->chapter);
							misslf= TRUE;
						}
					}
					else
					{	if (misslf)
						{	outln("");
						}
						voutf("     %s, %s", ptr->idx[1], ptr->chapter);
						misslf= TRUE;
					}
				}
				else
				{	if (misslf)
					{	outln("");
					}
					outln(ptr->idx[0]);
					voutlnf("     %s", ptr->idx[1]);
					voutf("        %s, %s", ptr->idx[2], ptr->chapter);
					misslf= TRUE;
				}
				break;
		}

		prev= ptr;		
		ptr= ptr->next;		

	}	while(ptr!=NULL);

	if (misslf)
	{	outln("");
	}

}	/* pint_ascii_index */


LOCAL void print_info_index ( void )
{
	int counter;
	IDXLIST *ptr;
	char left[512], old_left[512], val[32];
	
	outln("");
	outln("@iftex");
	outln("@unnumbered Index");
	outln("@printindex cp");
	outln("@end iftex");
	outln("");

	if (!use_udo_index)
	{	return;
	}

	ptr= idxlist;
	left[0]= EOS;
	old_left[0]= EOS;
	counter= 0;
	
	if (ptr==NULL)
	{	return;
	}

	outln("@ifinfo");
	voutlnf("@node %s, , , Top", lang.index);
	voutlnf("@chapter %s", lang.index);
	outln("");
	outln("@menu");

	/*	------------------------------------------------------------
		Aufbau:
		
		@menu
		* Indexeintrag:  Nodename.
		@end menu
		
		Achtung: Es duerfen keine zwei gleiche Indexeintraege benutzt
		werden, da Info sonst den falschen Node anspringt. Daher
		werden hier zur Not Zahlen in Klammern angefuegt.
		------------------------------------------------------------	*/

	do
	{
		switch ( ptr->depth )
		{
			case 0:
				strcpy(left, ptr->idx[0]);
				break;
			case 1:
				sprintf(left, "%s, %s", ptr->idx[0], ptr->idx[1]);
				break;
			case 2:
				sprintf(left, "%s, %s, %s", ptr->idx[0], ptr->idx[1], ptr->idx[2]);
				break;
		}

		qdelete_all(left, ":", 1);	/* ":" (colons) mag Info dort nicht */		

		if (strlen(left)>34)
		{	left[34]= EOS;
		}

		if (strcmp(left, old_left)==0)
		{	counter++;
			sprintf(val, " (%d)", counter+1);
			strcat(left, val);
		}
		else
		{	strcpy(old_left, left);
			counter= 0;
		}

		voutlnf("* %-38s:%s.", left, ptr->chapter);

		ptr= ptr->next;		

	}	while(ptr!=NULL);

	outln("@end menu");
	outln("@end ifinfo");
	outln("");

}	/* print_info_index */


#define	USE_RAW_INDEX 0

#if USE_RAW_INDEX
LOCAL void print_raw_index ( void )
{
	IDXLIST *ptr;

	if (!use_udo_index)
	{	return;
	}
	
	ptr= idxlist;
	
	if (ptr==NULL)
	{	return;
	}

	outln("");
	
	do
	{
		switch (ptr->depth)
		{
			case 0:
				voutlnf("%s, %s", ptr->idx[0], ptr->chapter);
				break;
			case 1:
				voutlnf("%s, %s, %s", ptr->idx[0], ptr->idx[1], ptr->chapter);
				break;
			case 2:
				voutlnf("%s, %s, %s, %s", ptr->idx[0], ptr->idx[1], ptr->idx[2], ptr->chapter);
				break;
		}

		ptr= ptr->next;		

	}	while(ptr!=NULL);

}	/* pint_raw_index */
#endif


/*	--------------------------------------------------
	print_index() sorgt fuer die Ausgabe eines
	Indexregisters und wird von c_end_document()
	aufgerufen.	r5pl6
	--------------------------------------------------	*/
GLOBAL void print_index ( void )
{
	if (no_index || !bCalledIndex)
	{	return;
	}
	
	switch (desttype)
	{
		case TOTEX:
		case TOPDL:
			outln("\\printindex");
			break;
		
		case TOINF:
			sort_idxlist();
			print_info_index();
			break;

		case TOASC:
			sort_idxlist();
			print_ascii_index();
			break;
	}

#if USE_RAW_INDEX
	print_raw_index();
#endif
	
}	/* print_index */

/*	--------------------------------------------------------------
	output_htmlhelp_index()
	Gibt eine Index-Zeile fuer HTML-Help aus. Aufbau:
	<Object type="application/x-oleobject" classid="clsid:1e2a7bd0-dab9-11d0-b93a-00c04fc99f9e">
		<param name="Keyword" value="MyKLink">
	</OBJECT>
	--------------------------------------------------------------	*/
GLOBAL void output_htmlhelp_index ( const int count, const char *x0, const char *x1, const char *x2 )
{
	outln("<OBJECT type=\"application/x-oleobject\" classid=\"clsid:1e2a7bd0-dab9-11d0-b93a-00c04fc99f9e\">");

	switch (count)
	{
		case 1:
			voutlnf("\t<param name=\"Keyword\" value=\"%s\">", x0);
			break;
		case 2:
			voutlnf("\t<param name=\"Keyword\" value=\"%s, %s\">", x0, x1);
			break;
		case 3:
			voutlnf("\t<param name=\"Keyword\" value=\"%s, %s, %s\">", x0, x1, x2);
			break;
	}

	outln("</OBJECT>");
}	/* output_htmlhelp_index */



/*	--------------------------------------------------------------
	c_index()
	Bearbeiten des Kommandos !index idx1 [!! idx2 [!! idx3]]
	--------------------------------------------------------------	*/
LOCAL void c_index ( void )
{
	char 	idx[512];
	char	n[3][128];

	char	entry[512];
	int 	count, j;
	size_t	i;

	if (no_index)
	{	return;
	}

	/* Tokens umkopieren */
	tokcpy2(idx, 512);

	if (idx[0]==EOS)
	{	error_missing_parameter(CMD_INDEX);
		return;
	}
	
	n[0][0]= EOS;
	n[1][0]= EOS;
	n[2][0]= EOS;
	
	count= 0;
	i= 0;
	
	while ( idx[i]!=EOS )
	{	if (idx[i]=='!' && idx[i+1]=='!')
		{	if (count==2)
			{	break;
			}
			count++;
			i++;
		}
		else
		{	chrcat(n[count], idx[i]);
		}
		i++;
	}

	for (j=0; j<3; j++)
	{	del_whitespaces(n[j]);
	}
	
	count= 0;
	if (n[0][0]!=EOS)	count++;
	if (n[1][0]!=EOS)	count++;
	if (n[2][0]!=EOS)	count++;

	if (count==0)
	{	return;
	}


	/* New in r6pl15 [NHz] */

	/* Set index in project file */

	sprintf(entry, "%s:%s:%s", n[0], n[1], n[2]); 

	save_upr_entry_index ( count, sCurrFileName, entry, uiCurrFileLine );

	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
		case TOINF:
			for (j=0; j<3; j++)
			{	delete_all(n[j], "!-");
				auto_quote_texindex(n[j]);
				c_internal_styles(n[j]);
				replace_udo_quotes(n[j]);
				convert_tilde(n[j]);
			}
			if (desttype==TOTEX || desttype==TOPDL)
			{	switch (count)
				{	case 1:
						voutlnf("\\index{%s}", n[0]);
						break;
					case 2:
						voutlnf("\\index{%s!%s}", n[0], n[1]);
						if (use_mirrored_indices)
						{	voutlnf("\\index{%s!%s}", n[1], n[0]);
						}
						break;
					case 3:
						voutlnf("\\index{%s!%s!%s}", n[0], n[1], n[2]);
						break;
				}
			}
			else
			{	switch (count)
				{	case 1:
						voutlnf("@cindex %s", n[0]);
						break;
					case 2:
						voutlnf("@cindex %s, %s", n[0], n[1]);
						if (use_mirrored_indices)
						{	voutlnf("@cindex %s, %s", n[1], n[0]);
						}
						break;
					case 3:
						voutlnf("@cindex %s, %s, %s", n[0], n[1], n[2]);
						break;
				}
				add_idxlist_item(n[0], n[1], n[2]);
				if (use_mirrored_indices && count==2)
				{	add_idxlist_item(n[1], n[0], n[2]);
				}
			}
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			for (j=0; j<3; j++)
			{	del_internal_styles(n[j]);
				replace_udo_quotes(n[j]);
				convert_tilde(n[j]);
				winspecials2ascii(n[j]);
			}
			switch (count)
			{	case 1:
					voutf("K{\\footnote K %s}", n[0]);
					break;
				case 2:
					voutf("K{\\footnote K %s, %s}", n[0], n[1]);
					if (use_mirrored_indices)
					{	voutf("K{\\footnote K %s, %s}", n[1], n[2]);
					}
					break;
				case 3:
					voutf("K{\\footnote K %s, %s, %s}", n[0], n[1], n[2]);
					break;
			}
			break;
		case TORTF:
			for (j=0; j<3; j++)
			{	del_internal_styles(n[j]);
				replace_udo_quotes(n[j]);
				convert_tilde(n[j]);
			}
			switch (count)
			{	case 1:
					voutf("{\\xe\\v %s}", n[0]);
					break;
				case 2:
					voutf("{\\xe\\v %s\\:%s}", n[0], n[1]);
					if (use_mirrored_indices)
					{	voutf("{\\xe\\v %s\\:%s}", n[1], n[0]);
					}
					break;
				case 3:
					voutf("{\\xe\\v %s\\:%s\\:%s}", n[0], n[1], n[2]);
					break;
			}
			break;
		case TOSTG:
		case TOAMG:
			for (j=0; j<3; j++)
			{	del_internal_styles(n[j]);
				replace_udo_quotes(n[j]);
				convert_tilde(n[j]);
				index2stg(n[j]);
			}
			switch (count)
			{	case 1:
					voutlnf("@index \"%s\"", n[0]);
					break;
				case 2:
					voutlnf("@index \"%s, %s\"", n[0], n[1]);
					if (use_mirrored_indices)
					{	voutlnf("@index \"%s, %s\"", n[1], n[0]);
					}
					break;
				case 3:
					voutlnf("@index \"%s, %s, %s\"", n[0], n[1], n[2]);
					break;
			}
			break;

		case TOIPF:	/*r6pl8*/
			for (j=0; j<3; j++)
			{	del_internal_styles(n[j]);
				replace_udo_quotes(n[j]);
				convert_tilde(n[j]);
			}
			switch (count)
			{	case 1:
			voutlnf(":i1.%s", n[0]);
					break;
				case 2:
					voutlnf(":i1.%s, %s", n[0], n[1]);
					if (use_mirrored_indices)
					{	voutlnf(":i1.%s, %s", n[1], n[0]);
					}
					break;
				case 3:
					voutlnf(":i1.%s, %s, %s", n[0], n[1], n[2]);
					break;
			}
			break;

		case TOASC:
			for (j=0; j<count; j++)
			{	del_internal_styles(n[j]);
				replace_udo_quotes(n[j]);
				convert_tilde(n[j]);
			}
			add_idxlist_item(n[0], n[1], n[2]);
			if (use_mirrored_indices && count==2)
			{	add_idxlist_item(n[1], n[0], n[2]);
			}
			break;

		case TOMHH:	/*r6pl9*/
			for (j=0; j<3; j++)
			{	delete_all(n[j], "!-");
				auto_quote_texindex(n[j]);
				c_internal_styles(n[j]);
				replace_udo_quotes(n[j]);
				convert_tilde(n[j]);
			}
			output_htmlhelp_index(count, n[0], n[1], n[2]);
			break;

	}

	bCalledIndex= TRUE;
	
}	/* c_index */



/*	############################################################
	#
	# Ueberschriften erzeugen
	#
	############################################################	*/
LOCAL void c_heading ( void )
{
	char name[512], n[512], align[64];
	BOOLEAN inside_center, inside_right;

	tokcpy2(name, 512);
	
	if (name[0]==EOS)
	{	error_missing_parameter(CMD_HEADING);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	check_styles(name);	/*r6pl3*/

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);	/*r6pl5*/
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);	/*r6pl5*/

	switch (desttype)
	{
		case TOTEX:
		case TOPDL:
			c_internal_styles(name);
			voutlnf("{\\Large{\\bf %s}}", name);
			outln("");
			break;
		case TOINF:
			c_internal_styles(name);
			outln("");
			voutlnf("@chapheading %s", name);
			outln("");
			break;
		case TORTF:
			c_rtf_styles(name);
			c_rtf_quotes(name);
			align[0]= EOS;
			if (inside_center)	strcpy(align, "\\qc");
			if (inside_right)	strcpy(align, "\\qr");
			/* Bug -> Corrected in r6pl15 [NHz] */
/*			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize + 14, name);*/
			/* Changed in r6pl16 [NHz] */
			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, laydat.node1size, name);
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			c_win_styles(name);
			align[0]= EOS;
			if (inside_center)	strcpy(align, "\\qc");
			if (inside_right)	strcpy(align, "\\qr");
			voutlnf("{%s\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize + 14, name);
/*			voutlnf("{%s\\fs%d\\b %s}\\par\\pard\\par", iDocPropfontSize + 14, align, name);*/
			break;
		case TOKPS:
			outln("newline");
			/* Changed in r6pl16 [NHz] */
			voutlnf("%d changeFontSize", laydat.node1size);
			outln("Bon");
			voutlnf("(%s) udoshow", name);
			outln("Boff");
			/* Changed in r6pl15 [NHz] */
			voutlnf("%d changeFontSize", laydat.propfontsize);
			/*outln("11 changeFontSize");*/
			/* Deleted in r6pl15 [NHz] */
			/* outln("changeBaseFont"); */
			outln("newline");
			break;
		case TOHTM:
		case TOMHH:
			c_internal_styles(name);
			n[0]= EOS;
			if (inside_center)	strcpy(n, " align=\"center\"");
			if (inside_right)	strcpy(n, " align=\"right\"");
			voutlnf("<h%d%s>%s</h%d>", html_nodesize, n, name, html_nodesize);
			break;
		case TOASC:
		case TOPCH:
			c_internal_styles(name);
			outln("");
			outln(name);
			output_ascii_line("*", strlen(name));
			outln("");
			break;
		case TOMAN:
			my_strupr(name);
			sprintf(n, " %s%s%s", BOLD_ON, name, BOLD_OFF);
			c_internal_styles(n);
			outln(n);
			break;
		case TONRO:
			my_strupr(name);
			voutlnf(".SH %s", name);
			break;
		case TOSTG:
		case TOAMG:
			sprintf(n, "%s%s%s", UNDER_ON, name, UNDER_OFF);
			if (inside_center)	strcenter(n, zDocParwidth);
			if (inside_right)	strright(n, zDocParwidth);
			c_internal_styles(n);
			outln("");
			outln(n);
			outln("");
			break;
		case TOTVH:
			c_internal_styles(name);
			tvh_headline(name);
			outln("");
			break;
		case TOHPH:	/* <???> */
		case TOLYX:	/* <???> */
		case TODRC:	/* <???> */
		case TOIPF:	/* <???> */
			break;
	}

	
}	/* c_heading */


LOCAL void c_subheading ( void )
{
	char name[512], n[512], align[64];
	BOOLEAN inside_center, inside_right;

	tokcpy2(name, 512);
	
	if (name[0]==EOS)
	{	error_missing_parameter(CMD_SUBHEADING);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	check_styles(name);	/*r6pl3*/

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);	/*r6pl5*/
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);	/*r6pl5*/

	switch (desttype)
	{
		case TOTEX:
		case TOPDL:
			c_internal_styles(name);
			voutlnf("{\\large{\\bf %s}}", name);
			outln("");
			break;
		case TOINF:
			c_internal_styles(name);
			outln("");
			voutlnf("@heading %s", name);
			outln("");
			break;
		case TORTF:
			c_rtf_styles(name);
			c_rtf_quotes(name);
			/* New in r6pl15 [NHz] */

			align[0]= EOS;
			if (inside_center)	strcpy(align, "\\qc");
			if (inside_right)	strcpy(align, "\\qr");
			/* Changed in r6pl16 [NHz] */
			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, laydat.node2size, name);
/*			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize + 6, name);*/
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			c_win_styles(name);
			/* New in r6pl15 [NHz] */

			align[0]= EOS;
			if (inside_center)	strcpy(align, "\\qc");
			if (inside_right)	strcpy(align, "\\qr");
			voutlnf("{%s\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize + 6, name);
			break;
		case TOKPS:
			outln("newline");
			/* Changed in r6pl16 [NHz] */
			voutlnf("%d changeFontSize", laydat.node2size);
			outln("Bon");
			voutlnf("(%s) udoshow", name);
			outln("Boff");
			/* Changed in r6pl15 [NHz] */
			voutlnf("%d changeFontSize", laydat.propfontsize);
			/*outln("11 changeFontSize");*/
			/* Deleted in r6pl15 [NHz] */
			/* outln("changeBaseFont"); */
			outln("newline");
			break;
		case TOHTM:
		case TOMHH:
			c_internal_styles(name);
			n[0]= EOS;
			if (inside_center)	strcpy(n, " align=\"center\"");
			if (inside_right)	strcpy(n, " align=\"right\"");
			voutlnf("<h%d%s>%s</h%d>", html_nodesize+1, n, name, html_nodesize+1);
			break;
		case TOASC:
		case TOPCH:
			c_internal_styles(name);
			outln("");
			outln(name);
			output_ascii_line("=", strlen(name));
			outln("");
			break;
		case TOMAN:
			sprintf(n, " %s%s%s", BOLD_ON, name, BOLD_OFF);
			c_internal_styles(n);
			outln(n);
			break;
		case TONRO:
			my_strupr(name);
			voutlnf(".SH %s", name);
			break;
		case TOSTG:
		case TOAMG:
			sprintf(n, "%s%s%s", UNDER_ON, name, UNDER_OFF);
			if (inside_center)	strcenter(n, zDocParwidth);
			if (inside_right)	strright(n, zDocParwidth);
			c_internal_styles(n);
			outln("");
			outln(n);
			outln("");
			break;
		case TOTVH:
			c_internal_styles(name);
			tvh_headline(name);
			outln("");
			break;
		case TODRC:	/* <???> */
		case TOHPH:	/* <???> */
		case TOIPF:	/* <???> */
		case TOLYX:	/* <???> */
			break;
	}

}	/* c_subheading */


LOCAL void c_subsubheading ( void )
{
	char name[512], n[512], align[64];
	BOOLEAN inside_center, inside_right;

	tokcpy2(name, 512);
	
	if (name[0]==EOS)
	{	error_missing_parameter(CMD_SUBSUBHEADING);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	check_styles(name);	/*r6pl3*/

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);	/*r6pl5*/
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);	/*r6pl5*/

	switch (desttype)
	{
		case TOTEX:
		case TOPDL:
			c_internal_styles(name);
			voutlnf("{\\normalsize{\\bf %s}}", name);
			outln("");
			break;
		case TOINF:
			c_internal_styles(name);
			outln("");
			voutlnf("@subheading %s", name);
			outln("");
			break;
		case TORTF:
			c_rtf_styles(name);
			c_rtf_quotes(name);
			/* New in r6pl15 [NHz] */

			align[0]= EOS;
			if (inside_center)	strcpy(align, "\\qc");
			if (inside_right)	strcpy(align, "\\qr");
			/* Changed in r6pl16 [NHz] */
			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, laydat.node3size, name);
/*			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize, name);*/
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			c_win_styles(name);
			/* New in r6pl15 [NHz] */

			align[0]= EOS;
			if (inside_center)	strcpy(align, "\\qc");
			if (inside_right)	strcpy(align, "\\qr");
			voutlnf("{%s\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize, name);
			break;
		case TOKPS:
			outln("newline");
			/* Changed in r6pl16 [NHz] */
			voutlnf("%d changeFontSize", laydat.node3size);
			outln("Bon");
			voutlnf("(%s) udoshow", name);
			outln("Boff");
			/* Changed in r6pl15 [NHz] */
			voutlnf("%d changeFontSize", laydat.propfontsize);
			outln("newline");
			break;
		case TOHTM:
		case TOMHH:
			c_internal_styles(name);
			n[0]= EOS;
			if (inside_center)	strcpy(n, " align=\"center\"");
			if (inside_right)	strcpy(n, " align=\"right\"");
			voutlnf("<h%d%s>%s</h%d>", html_nodesize+2, n, name, html_nodesize+2);
			break;
		case TOASC:
		case TOPCH:
			c_internal_styles(name);
			outln("");
			outln(name);
			output_ascii_line("-", strlen(name));
			outln("");
			break;
		case TOMAN:
			sprintf(n, " %s%s%s", BOLD_ON, name, BOLD_OFF);
			c_internal_styles(n);
			outln(n);
			break;
		case TONRO:
			my_strupr(name);
			voutlnf(".SH %s", name);
			break;
		case TOSTG:
		case TOAMG:
			sprintf(n, "%s%s%s", UNDER_ON, name, UNDER_OFF);
			if (inside_center)	strcenter(n, zDocParwidth);
			if (inside_right)	strright(n, zDocParwidth);
			c_internal_styles(n);
			outln("");
			outln(n);
			outln("");
			break;
		case TOTVH:
			c_internal_styles(name);
			tvh_headline(name);
			outln("");
			break;
		case TODRC:	/* <???> */
		case TOHPH:	/* <???> */
		case TOIPF:	/* <???> */
		case TOLYX:	/* <???> */
			break;
	}

}	/* c_subsubheading */


LOCAL void c_subsubsubheading ( void )
{
	char name[512], n[512], align[64];
	BOOLEAN inside_center, inside_right;

	tokcpy2(name, 512);
	
	if (name[0]==EOS)
	{	error_missing_parameter(CMD_SUBSUBSUBHEADING);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	check_styles(name);	/*r6pl3*/

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);	/*r6pl5*/
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);	/*r6pl5*/

	switch (desttype)
	{
		case TOTEX:
		case TOPDL:
			c_internal_styles(name);
			voutlnf("{\\normalsize{\\bf %s}}", name);
			outln("");
			break;
		case TOINF:
			c_internal_styles(name);
			outln("");
			voutlnf("@subheading %s", name);
			outln("");
			break;
		case TORTF:
			c_rtf_styles(name);
			c_rtf_quotes(name);
			/* New in r6pl15 [NHz] */

			align[0]= EOS;
			if (inside_center)	strcpy(align, "\\qc");
			if (inside_right)	strcpy(align, "\\qr");
			/* Changed in r6pl16 [NHz] */
			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, laydat.node4size, name);
/*			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize, name);*/
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			c_win_styles(name);
			/* New in r6pl15 [NHz] */

			align[0]= EOS;
			if (inside_center)	strcpy(align, "\\qc");
			if (inside_right)	strcpy(align, "\\qr");
			voutlnf("{%s\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize, name);
			break;
		case TOKPS:
			outln("newline");
			/* Changed in r6pl16 [NHz] */
			/* Changed in r6pl16 [NHz] */
			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, laydat.node4size, name);
/*			voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize, name);*/
			outln("Bon");
			voutlnf("(%s) udoshow", name);
			outln("Boff");
			/* Changed in r6pl15 [NHz] */
			voutlnf("%d changeFontSize", laydat.propfontsize);
			outln("newline");
			break;
		case TOHTM:
		case TOMHH:
			c_internal_styles(name);
			n[0]= EOS;
			if (inside_center)	strcpy(n, " align=\"center\"");
			if (inside_right)	strcpy(n, " align=\"right\"");
			voutlnf("<h%d%s>%s</h%d>", html_nodesize+3, n, name, html_nodesize+3);
			break;
		case TOASC:
		case TOPCH:
			c_internal_styles(name);
			outln("");
			outln(name);
			outln("");
			break;
		case TOMAN:
			sprintf(n, " %s%s%s", BOLD_ON, name, BOLD_OFF);
			c_internal_styles(n);
			outln(n);
			break;
		case TONRO:
			my_strupr(name);
			voutlnf(".SH %s", name);
			break;
		case TOSTG:
		case TOAMG:
			sprintf(n, "%s%s%s", UNDER_ON, name, UNDER_OFF);
			if (inside_center)	strcenter(n, zDocParwidth);
			if (inside_right)	strright(n, zDocParwidth);
			c_internal_styles(n);
			outln("");
			outln(n);
			outln("");
			break;
		case TOTVH:
			c_internal_styles(name);
			tvh_headline(name);
			outln("");
			break;
		case TODRC:	/* <???> */
		case TOHPH:	/* <???> */
		case TOIPF:	/* <???> */
		case TOLYX:	/* <???> */
			break;
	}

}	/* c_subsubsubheading */


LOCAL void c_listheading ( void )
{
	char name[512], sFontBeg[512], sFontEnd[32], align[64];
	BOOLEAN inside_center, inside_right;
	int iSize;

	tokcpy2(name, 512);
	
	if (name[0]==EOS)
	{	error_missing_parameter(CMD_HEADING);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	check_styles(name);	/*r6pl3*/

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);	/*r6pl5*/
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);	/*r6pl5*/

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
			c_internal_styles(name);
			align[0]= EOS;
			if (inside_center)	strcpy(align, " align=\"center\"");
			if (inside_right)	strcpy(align, " align=\"right\"");
			sFontBeg[0]= EOS;
			sFontEnd[0]= EOS;
			if (sDocHtmlPropfontName[0]!=EOS)
			{	iSize= iDocHtmlPropfontSize + 3;
				sprintf(sFontBeg, "<font face=\"%s\" size=\"%s%d\">", sDocHtmlPropfontName, (iSize>=0) ? "+" : "", iSize);
				strcpy(sFontEnd, "</font>");
			}
			voutlnf("<tr><td valign=\"top\"%s colspan=\"2\">&nbsp;<br>%s<b>%s</b>", align, sFontBeg, name);
			if (bEnv1stItem[iEnvLevel])
			{	voutlnf("%s</td></tr>", sFontEnd);
			}
			break;
	}

	
}	/* c_listheading */


LOCAL void c_listsubheading ( void )
{
	char name[512], sFontBeg[512], sFontEnd[32], align[64];
	BOOLEAN inside_center, inside_right;
	int iSize;

	tokcpy2(name, 512);
	
	if (name[0]==EOS)
	{	error_missing_parameter(CMD_HEADING);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	check_styles(name);	/*r6pl3*/

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);	/*r6pl5*/
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);	/*r6pl5*/

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
			c_internal_styles(name);
			align[0]= EOS;
			if (inside_center)	strcpy(align, " align=\"center\"");
			if (inside_right)	strcpy(align, " align=\"right\"");
			sFontBeg[0]= EOS;
			sFontEnd[0]= EOS;
			if (sDocHtmlPropfontName[0]!=EOS)
			{	iSize= iDocHtmlPropfontSize + 2;
				sprintf(sFontBeg, "<font face=\"%s\" size=\"%s%d\">", sDocHtmlPropfontName, (iSize>=0) ? "+" : "", iSize);
				strcpy(sFontEnd, "</font>");
			}
			voutlnf("<tr><td valign=\"top\"%s colspan=\"2\">&nbsp;<br>%s<b>%s</b>", align, sFontBeg, name);
			if (bEnv1stItem[iEnvLevel])
			{	voutlnf("%s</td></tr>", sFontEnd);
			}
			break;
	}

	
}	/* c_listsubheading */

LOCAL void c_listsubsubheading ( void )
{
	char name[512], sFontBeg[512], sFontEnd[32], align[64];
	BOOLEAN inside_center, inside_right;
	int iSize;

	tokcpy2(name, 512);
	
	if (name[0]==EOS)
	{	error_missing_parameter(CMD_HEADING);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	check_styles(name);	/*r6pl3*/

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);	/*r6pl5*/
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);	/*r6pl5*/

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
			c_internal_styles(name);
			align[0]= EOS;
			if (inside_center)	strcpy(align, " align=\"center\"");
			if (inside_right)	strcpy(align, " align=\"right\"");
			sFontBeg[0]= EOS;
			sFontEnd[0]= EOS;
			if (sDocHtmlPropfontName[0]!=EOS)
			{	iSize= iDocHtmlPropfontSize + 1;
				sprintf(sFontBeg, "<font face=\"%s\" size=\"%s%d\">", sDocHtmlPropfontName, (iSize>=0) ? "+" : "", iSize);
				strcpy(sFontEnd, "</font>");
			}
			voutlnf("<tr><td valign=\"top\"%s colspan=\"2\">&nbsp;<br>%s<b>%s</b>", align, sFontBeg, name);
			if (bEnv1stItem[iEnvLevel])
			{	voutlnf("%s</td></tr>", sFontEnd);
			}
			break;
	}

	
}	/* c_listsubsubheading */

LOCAL void c_listsubsubsubheading ( void )
{
	char name[512], sFontBeg[512], sFontEnd[32], align[64];
	BOOLEAN inside_center, inside_right;
	int iSize;

	tokcpy2(name, 512);
	
	if (name[0]==EOS)
	{	error_missing_parameter(CMD_HEADING);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	check_styles(name);	/*r6pl3*/

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);	/*r6pl5*/
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);	/*r6pl5*/

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
			c_internal_styles(name);
			align[0]= EOS;
			if (inside_center)	strcpy(align, " align=\"center\"");
			if (inside_right)	strcpy(align, " align=\"right\"");
			sFontBeg[0]= EOS;
			sFontEnd[0]= EOS;
			if (sDocHtmlPropfontName[0]!=EOS)
			{	iSize= iDocHtmlPropfontSize;
				sprintf(sFontBeg, "<font face=\"%s\" size=\"%s%d\">", sDocHtmlPropfontName, (iSize>=0) ? "+" : "", iSize);
				strcpy(sFontEnd, "</font>");
			}
			voutlnf("<tr><td valign=\"top\"%s colspan=\"2\">&nbsp;<br>%s<b>%s</b>", align, sFontBeg, name);
			if (bEnv1stItem[iEnvLevel])
			{	voutlnf("%s</td></tr>", sFontEnd);
			}
			break;
	}

	
}	/* c_listsubsubsubheading */

/*	############################################################
	#
	# Seitenumbruch erzeugen (!newpage)
	#
	############################################################	*/
GLOBAL void c_newpage( void )
{

	switch(desttype)
	{
		case TOTEX:	outln(""); outln("\\newpage");	break;
		case TOPDL:	outln(""); outln("\\newpage");	break;
		case TODRC:	/* <???> */				break;
		case TOHPH:	/* <???> */				break;
		case TOIPF:	/* <???> */				break;
		case TOLYX:	/* <???> */				break;
		case TOINF:	outln("@page");			break;
		case TORTF:	out("\\page ");			break;
		case TOMAN:
			if (iManPageLength>0)
			{	while ( iManPageLines<iManPageLength-MAN_BOTTOMLINES )
				{	if (!bTestmode)
						fprintf(outfile.file, "\n");
					iManPageLines++;
					outlines++;
				}
				man_bottomline();
				iManPagePages++;
				iManPageLines= 0;
				man_headline();
			}
			break;
		case TOASC:
			if (use_formfeed)
			{	out("\014");
			}
			break;
		case TOKPS:
			outln("newpage");
			break;
		/* New in r6pl16 [NHz] */
		case TOHTM:
			outln("<span class=\"page-break\"></span>");
			break;
	}
	
}	/*c_newpage*/


/*	############################################################
	# Diverses
	############################################################	*/
/*	--------------------------------------------------------------
	c_tunix()
	Macht gar nichts (wer haette das gedacht)
	--------------------------------------------------------------	*/
LOCAL void c_tunix ( void )
{
	return;
}	/*c_tunix*/


/*	--------------------------------------------------------------
	c_debug(): Macht auch nichts -> fuer's Testen
	--------------------------------------------------------------	*/
GLOBAL void c_debug ( void )
{
}	/* c_debug */



/*	--------------------------------------------------------------
	c_nop()
	Dieses Kommando macht auch gar nichts, ausser die Boolsche
	Variable nop_detected zu togglen. Daher eignet sich !nop
	erstklassig zum Debuggen, in dem man in problematischen
	Quelltext vor die jeweilige Stelle !nop einfuegt.
	--------------------------------------------------------------	*/
LOCAL void c_nop ( void )
{
	bNopDetected= !bNopDetected;
}

/*	--------------------------------------------------------------
	c_break()
	Sobald !break im Quelltext auftritt, wird die Uebersetzung
	abgebrochen. Seit Rel.5 PL17 ist !break ein "richtige"
	Kommando, kann daher auch zwischen Abfragebefehlen stehen.
	--------------------------------------------------------------	*/
LOCAL void c_break ( void )
{
	bBreakInside= TRUE;
	if (bInsideDocument)
	{	c_end_document();
	}
}


/*	--------------------------------------------------------------
	c_error()
	Bei !error werden die folgenden Zeichen ausgegeben (auch
	im Logfile) und das Programm beendet.
	--------------------------------------------------------------	*/
LOCAL void c_error ( void )
{
	char e[512];
	tokcpy2(e, 512);
	error_error(e);

	bBreakInside= TRUE;
	if (bInsideDocument)
	{	c_end_document();
	}
	bFatalErrorDetected= TRUE;
}


/*	--------------------------------------------------------------
	c_sloppy() / c_fussy()
	Togglen des internen Flags, ob kurze Zeilen bemaengelt werden
	sollen.
	--------------------------------------------------------------	*/
LOCAL void c_sloppy ( void )
{
	bDocSloppy= TRUE;
}	/* c_sloppy */

LOCAL void c_fussy ( void )
{
	bDocSloppy= FALSE;
}	/* c_fussy */



/*	--------------------------------------------------------------
	c_code()
	Zeichensatz intern umstellen. iCharset wird an einigen Stellen
	in chr.c abgefragt, besonders in recode()
	--------------------------------------------------------------	*/
LOCAL void c_code ( void )
{
	char s[256];
	int i;
	
	/* r6pl2: Neue Version "!code iso"	*/
	/* vorher: "!code_iso" etc.			*/
	
	if (token[1][0]==EOS)
	{	error_missing_parameter("!code");
		return;
	}
	
	tokcpy2(s, 256);

#if 1
	for (i=0; i<MAXCHARSET; i++)
	{
		if ( strstr(s, udocharset[i].magic)!=NULL )
		{	iCharset= udocharset[i].codepage;
			return;
		}
	}
#else
	if (strstr(s, "iso")!=NULL)
	{	iCharset= CODE_LAT1;
		return;
	}

	if (strstr(s, "latin1")!=NULL)	/*r6pl2*/
	{	iCharset= CODE_LAT1;
		return;
	}

	if (strstr(s, "tos")!=NULL)
	{	iCharset= CODE_TOS;
		return;
	}

	if (strstr(s, "dos")!=NULL)
	{	iCharset= CODE_437;
		return;
	}

	if (strstr(s, "cp437")!=NULL)
	{	iCharset= CODE_437;
		return;
	}

	if (strstr(s, "cp850")!=NULL)
	{	iCharset= CODE_850;
		return;
	}

	if (strstr(s, "hp8")!=NULL)
	{	iCharset= CODE_HP8;
		return;
	}

	if (strstr(s, "mac")!=NULL)
	{	iCharset= CODE_MAC;
		return;
	}

	if (strstr(s, "next")!=NULL)
	{	iCharset= CODE_NEXT;
		return;
	}

	if (strstr(s, "sys")!=NULL)
	{	iCharset= SYSTEM_CHARSET;	/* r6pl2: vorher CODE_SYS */
		return;
	}
#endif

	error_no_charset(s);

}	/* c_code */



/*	--------------------------------------------------------------
	c_autoref()
	Bearbeiten der Kommandos !autoref [off] und !autoref [on]
	Wenn autoref_off==TRUE so erzeugt UDO in toc.c keine
	automatischen Querverweise im Outfile
	--------------------------------------------------------------	*/
LOCAL void c_autoref ( void )
{
	BOOLEAN newoff;
	
	if ( token_counter<=1 )
	{	error_missing_parameter(CMD_AUTOREF);
		return;
	}
		
	newoff= check_off();
	
	if (newoff && bDocAutorefOff)
	{	error_not_active(CMD_AUTOREF);
		return;
	}
	
	if (!newoff && !bDocAutorefOff)
	{	error_still_active(CMD_AUTOREF);
		return;
	}

	bDocAutorefOff= newoff;

	if (desttype==TOSTG || desttype==TOAMG)
	{	if (bDocAutorefOff)
		{	outln("@autorefoff");
		}
		else
		{	outln("@autorefon");
		}
	}

}	/* c_autoref */


/*	--------------------------------------------------------------
	c_autoref_items()
	Bearbeiten der Kommandos !autoref_items [off] und
	!autoref_items [on]
	Wenn autoref_items_off==TRUE so ruft UDO in env.c bei c_item()
	keine automatische Referenzierung 
	--------------------------------------------------------------	*/
LOCAL void c_autoref_items ( void )
{
	BOOLEAN newoff;
	
	if ( token_counter<=1 )
	{	error_missing_parameter(CMD_AUTOREF_ITEMS);
		return;
	}
		
	newoff= check_off();
	
	if (newoff && bDocAutorefItemsOff)
	{	error_not_active(CMD_AUTOREF_ITEMS);
		return;
	}
	
	if (!newoff && !bDocAutorefItemsOff)
	{	error_still_active(CMD_AUTOREF_ITEMS);
		return;
	}

	bDocAutorefItemsOff= newoff;

}	/* c_autoref_items */


/*	--------------------------------------------------------------
	c_universal_charset()
	Bearbeiten des Kommandos universal_charset [off] / [on]
	Wenn universal_charset_on==TRUE, so werden Strings wie
	("a) oder ("U) in ae oder Ue umgewandelt.
	--------------------------------------------------------------	*/
LOCAL void c_universal_charset ( void )
{
	BOOLEAN newon;
	
	if ( token_counter<=1 )
	{	error_missing_parameter(CMD_UNIVERSAL_CHARSET);
		return;
	}
		
	newon= check_on();
	
	if (newon && bDocUniversalCharsetOn)
	{	error_not_active(CMD_UNIVERSAL_CHARSET);
		return;
	}
	
	if (!newon && !bDocUniversalCharsetOn)
	{	error_still_active(CMD_UNIVERSAL_CHARSET);
		return;
	}

	bDocUniversalCharsetOn= newon;

}	/* c_universal_charset */


/*	--------------------------------------------------------------
	c_rtf_keep_tables()
	Bearbeiten des Kommandos rtf_keep_tables [off] / [on]
	Wenn rtf_keep_tables==TRUE, dann werden RTF-Tabellen so
	ausgegeben, da˜ WinWord sie auf einer Seite zusammenhaengend
	darstellt. Ansonsten bricht WinWord auch innerhalb einer
	Tabelle um.
	--------------------------------------------------------------	*/
LOCAL void c_rtf_keep_tables ( void )
{
	if ( token_counter<=1 )
	{	error_missing_parameter(CMD_RTF_KEEP_TABLES);
		return;
	}
		
	bDocRtfKeepTablesOn= check_on();
	
}	/* c_rtf_keep_tables */



/*	--------------------------------------------------------------
	c_verbatim_backcolor()
	Hintergrundfarbe fuer HTML-verbatim-Umgebungen setzen
	--------------------------------------------------------------	*/
LOCAL void c_verbatim_backcolor ( void )
{
	char color[256];
	BOOLEAN ret;
	
	if (token[1][0]==EOS)	return;

	color[0]= EOS;

	if (token[1][0]=='#')
	{	strcpy(color, token[1]);
		ret= TRUE;
	}
	else
	{	ret= get_html_color(token[1], color);
	}

	if (ret)
	{	strcpy(sDocVerbatimBackColor, color);
	}
	else
	{	error_unknown_color(token[1]);
	}

}	/* c_verbatim_backcolor */


/*	--------------------------------------------------------------
	output_empty_lines()
	Ausgabe von <count> zusaetzlichen Leerzeilen
	Wird von c_*skip verwendet.
	--------------------------------------------------------------	*/
LOCAL void output_empty_lines ( const int count )
{
	register int i;
	
	if (count<=0)	return;

	if (desttype==TOINF)
	{
		voutlnf("@sp %d", count);
	}
	else
	{
		for (i=0; i<count; i++)
		{
			switch(desttype)
			{
				case TORTF:
				case TOAQV:
				case TOWIN:
				case TOWH4:
					outln(rtf_par);
					break;
				case TOHTM:
				case TOMHH:
					outln("<br>");
					/* outln("<br>&nbsp;"); */
					break;
				case TOKPS:
					outln("newline");
					break;
				default:
					outln("");
					break;
			}
		}
	}
	
}	/* output_empty_lines */


LOCAL void c_bigskip ( void )
{
	switch(desttype)
	{	case TOTEX:
		case TOPDL:	outln("\\bigskip");		break;
		case TOLYX:	/* <???> */				break;
		case TOIPF:	/* <???> */				break;
		case TOHPH:	/* <???> */				break;
		case TOINF:	outln("@sp 3");			break;
		case TOKPS:	outln("newline newline newline\n");		break; /* New in r6pl15 [NHz] */
		default:	output_empty_lines(3);	break;
	}
}	/* c_bigskip */

LOCAL void c_medskip ( void )
{
	switch(desttype)
	{	case TOTEX:
		case TOPDL:	outln("\\medskip");		break;
		case TOLYX:	/* <???> */				break;
		case TOIPF:	/* <???> */				break;
		case TOHPH:	/* <???> */				break;
		case TOINF:	outln("@sp 2");			break;
		case TOKPS:	outln("newline newline\n");		break; /* New in r6pl15 [NHz] */
		default:	output_empty_lines(2);	break;
	}
}	/* c_medskip */

LOCAL void c_smallskip ( void )
{
	switch(desttype)
	{	case TOTEX:
		case TOPDL:	outln("\\smallskip");	break;
		case TOLYX:	/* <???> */				break;
		case TOIPF:	/* <???> */				break;
		case TOHPH:	/* <???> */				break;
		case TOINF:	outln("@sp 1");			break;
		case TOKPS:	outln("newline\n");		break; /* New in r6pl15 [NHz] */
		default:	output_empty_lines(1);	break;
	}
}	/* c_smallskip */



/*	--------------------------------------------------------------
	c_udolink() fuegt einen Link samt Bild auf die UDO-Seite ein
	--------------------------------------------------------------	*/
GLOBAL void c_udolink ( void )
{
	char sTemp[64], nodename[512], sGifSize[80];
	BOOLEAN inside_center, inside_right;

	uses_udolink= TRUE;

	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);	/*r6pl5*/
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);	/*r6pl5*/

	tokcpy2(nodename, 512);

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
			sGifSize[0]= EOS;
			if (uiGifMwWidth!=0 && uiGifMwHeight!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiGifMwWidth, uiGifMwHeight);
			}
			strcpy(sTemp, "<p>");
			if (inside_center)	strcpy(sTemp, "<p align=\"center\">");
			if (inside_right)	strcpy(sTemp, "<p align=\"right\">");
			if (nodename[0]==EOS)
			{	voutlnf("%s<a href=\"%s\"><img src=\"%s\" alt=\"%s\" border=\"0\"%s></a>",
					sTemp, UDO_URL, GIF_MW_NAME, UDO_MADE, sGifSize);
			}
			else
			{	auto_references(nodename, TRUE, GIF_MW_NAME, uiGifMwWidth, uiGifMwHeight);
				voutlnf("%s%s", sTemp, nodename);
			}
			outln("</p>");
			break;

		case TOWIN:
		case TOWH4:
			strcpy(sTemp, "ql");
			if (inside_center)	strcpy(sTemp, "qc");
			if (inside_right)	strcpy(sTemp, "qr");
			voutlnf("\\%s{\\{bmc %s\\}}\\par\\par\\pard", sTemp, BMP_MW_NAME);
			break;

		case TOSTG:
		case TOAMG:
			if (!no_images)
			{	voutlnf("@limage %s 0", IMG_MW_NAME);
			}
			break;

		case TORTF:
			if (!no_images)
			{	c_bmp_output(BMP_MW_NAME, "", TRUE);
			}
			break;

	}

}	/* c_udolink */



/*	--------------------------------------------------------------
	c_toplink() fuegt einen Link samt Bild an den Anfang der Seite
	ein (Unterstuetzung nur fuer Hypertext-Formate).
	--------------------------------------------------------------	*/
GLOBAL void c_toplink ( void )
{
	uses_toplink= TRUE;

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
                        /* set width and height =24 to fix bug #0000005 [voja] */
			voutlnf("<p><a href=\"#\"><img src=\"%s\" border=\"0\" width=\"24\" height=\"24\"></a></p>", GIF_TP_NAME);
			break;
	}

}	/* c_toplink */


/*	############################################################
	#
	#
	# Formatabhaengige Kommandos
	#
	#
	############################################################	*/

/*	--------------------------------------------------------------
	c_tex_dpi()
	Setzen des DPI-Wertes zur Ausgabe von Bildern mit LaTeX
	--------------------------------------------------------------	*/
LOCAL void c_tex_dpi ( void )
{
	iTexDPI= atoi(token[1]);
	
	if (iTexDPI<=0)
	{	iTexDPI= 100;
	}
}	/* c_tex_dpi */


/*	--------------------------------------------------------------
	c_tex_verb()
	Setzen des Zeichens, welches fuer \verb... verwendet wird
	--------------------------------------------------------------	*/
LOCAL void c_tex_verb ( void )
{
	cTexVerb= token[1][0];
	
	if (cTexVerb==EOS)
	{	cTexVerb= VERB_C;
	}
}


/*	--------------------------------------------------------------
	c_win_charwidth() / c_rtf_charwidth
	Setzen der Zeichenbreite eines Zeichens fuer WinHelp und RTF
	Die Zeichenbreiten werden zur Berechnung von Einrueckungen
	in Listen und Tabellen verwendet und koennen von UDO nicht
	ueber das System abgefragt werden.
	--------------------------------------------------------------	*/
LOCAL void c_win_charwidth ( void )
{
	iDocCharwidth= atoi(token[1]);
	
	if (iDocCharwidth<=0)
	{	iDocCharwidth= 150;
	}
}	/* c_win_charwidth */

LOCAL void c_wh4_charwidth ( void )
{
	iDocCharwidth= atoi(token[1]);
	
	if (iDocCharwidth<=0)
	{	iDocCharwidth= 150;
	}
}	/* c_wh4_charwidth */

LOCAL void c_rtf_charwidth ( void )
{
	iDocCharwidth= atoi(token[1]);
	
	if (iDocCharwidth<=0)
	{	iDocCharwidth= 150;
	}
}	/* c_rtf_charwidth */


/*	--------------------------------------------------------------
	c_html_img_suffix()
	Setzen der Endung, die UDO beim !image- und (!img)-Befehl
	fuer HTML verwenden soll. Default: .gif
	--------------------------------------------------------------	*/
LOCAL void c_html_img_suffix ( void )
{
	sDocImgSuffix[0]= EOS;
	strncat(sDocImgSuffix, token[1], 16);

	if (sDocImgSuffix[0]!=EOS)
	{	if (sDocImgSuffix[0]!='.')
		{	strinsert(sDocImgSuffix, ".");
		}
	}

}	/* c_html_img_suffix */



/*	--------------------------------------------------------------
	c_html_nodesize()
	Setzen, welche Groesse fuer die Erzeugung von Ueberschriften
	verwendet werden soll. Default: 1 -> <H1>...</H1>
	--------------------------------------------------------------	*/
LOCAL void c_html_nodesize ( void )
{
	html_nodesize= atoi(token[1]);
	
	if (html_nodesize<1)
	{	html_nodesize= 1;
	}

	if (html_nodesize>3)
	{	html_nodesize= 3;
	}

}	/* html_nodesize */



/*	--------------------------------------------------------------
	htag_img_suffix()
	Setzen der Bildendung fuer HP-Helptag-SGML. Default: .tiff
	--------------------------------------------------------------	*/
LOCAL void c_htag_img_suffix ( void )
{
	sDocImgSuffix[0]= EOS;
	strncat(sDocImgSuffix, token[1], 16);

	if (sDocImgSuffix[0]!=EOS)
	{	if (sDocImgSuffix[0]!='.')
		{	strinsert(sDocImgSuffix, ".");
		}
	}

}	/* htag_img_suffix */


/*	--------------------------------------------------------------
	c_tabwidth()
	Setzen der Tabulator-Positionen fuer Verbatim-Umgebungen
	--------------------------------------------------------------	*/
LOCAL void c_tabwidth ( void )
{
	bDocTabwidth= atoi(token[1]);
	
	/* r6pl2: tabwidth von 0 zulassen, dann spaeter keine Ersetzung */
	if (bDocTabwidth<0)
	{	bDocTabwidth= 0;
	}

	if (bDocTabwidth>8)
	{	bDocTabwidth= 8;
	}
}

/*	--------------------------------------------------------------
	c_verbatimsize()
	Setzen der Fontgroesse von verbatim-Umgebungen
	--------------------------------------------------------------	*/
LOCAL void c_verbatimsize ( void )
{
	if (strstr(token[1], "normal"))
	{	iDocVerbatimSize= VERB_NORMAL;
		return;
	}

	if (strstr(token[1], "small"))
	{	iDocVerbatimSize= VERB_SMALL;
		return;
	}

	if (strstr(token[1], "tiny"))
	{	iDocVerbatimSize= VERB_TINY;
		return;
	}

	if (strstr(token[1], "large"))
	{	iDocVerbatimSize= VERB_LARGE;
		return;
	}

	if (strstr(token[1], "huge"))
	{	iDocVerbatimSize= VERB_HUGE;
		return;
	}

	error_missing_parameter(CMD_VERBATIMSIZE);
	
}	/* c_verbatimsize */


/*	--------------------------------------------------------------
	c_linedrawsize()
	Setzen der Fontgroesse von linedraw-Umgebungen
	--------------------------------------------------------------	*/
LOCAL void c_linedrawsize ( void )
{
	if (strstr(token[1], "normal"))
	{	iDocLinedrawSize= VERB_NORMAL;
		return;
	}

	if (strstr(token[1], "small"))
	{	iDocLinedrawSize= VERB_SMALL;
		return;
	}

	if (strstr(token[1], "tiny"))
	{	iDocLinedrawSize= VERB_TINY;
		return;
	}

	if (strstr(token[1], "large"))
	{	iDocLinedrawSize= VERB_LARGE;
		return;
	}

	if (strstr(token[1], "huge"))
	{	iDocLinedrawSize= VERB_HUGE;
		return;
	}

	error_missing_parameter(CMD_LINEDRAWSIZE);
	
}	/* c_linedrawsize */

/*	--------------------------------------------------------------
	c_check_raw()
	Untersucht eine Zeile daraufhin, ob sie ein formatspezifisches
	Kommando einthaelt. Ausgewertet wird die oben angelegte
	Tabelle <udospec>. Enthaelt die Zeile ein solches Kommando,
	wird der Rest unveraenert ausgegeben.
	Die Funktion erhaelt eine unbearbeitete Zeile, also koennen
	die Befehle noch eingerueckt sein!
	Beispiel: !raw [tex] \documentstyle[german]{article}
	--------------------------------------------------------------	*/
LOCAL void c_check_raw ( char *s )
{
	size_t contlen;
	char *ptr, inhalt[512], *cont, *data;
	
	/* Neue Version: !raw [tex] \documentstyle[german]{article} */
	
	ptr= s;

	/* Erstes Non-Blank suchen */
	while (*ptr!=EOS && (*ptr==' ' || *ptr=='\t') )
	{	ptr++;
	}
	
	if (*ptr==EOS)
	{	return;
	}
	
	if (strncmp(ptr, "!raw", 4)!=0)
	{	return;
	}

	if (ptr[4]!=' ' && ptr[4]!='\t')
	{	return;
	}

	ptr+= 5;

	/* Naechstes Non-Blank suchen */
	while (*ptr!=EOS && (*ptr==' ' || *ptr=='\t') )
	{	ptr++;
	}

	/* Klammerinhalt ermitteln, wenn bl==0 dann kein Inhalt oder fehlende Klammern */
	contlen= get_brackets_ptr(ptr, &cont, &data);
	
	if (contlen==0 || cont==NULL || data==NULL)
	{	error_syntax_error();
		s[0]= EOS;
		return;
	}

	/* Klammerinhalt kopieren und Zeiger auf den Rest der Zeile setzen */
	inhalt[0]= EOS;
	strncpy(inhalt, cont, contlen);
	inhalt[contlen]= EOS;

	/* Letzten Absatz ausgeben */
	if (token_counter>0)
	{	token_output(TRUE);	/* r5pl11: TRUE statt FALSE */
	}

	/* Schauen, ob diese Zeile fuer das aktuelle Format bestimmt ist */
	
	if ( str_for_desttype(inhalt) )
	{	/* Rest der Zeile ausgeben */
		outln(data+1);
	}

	s[0]= EOS;
	
}	/* c_check_raw */



/*	--------------------------------------------------------------
	convert_image()
	Bearbeiten des !image-Kommandos samt Weitergabe der Infos an
	die Funktionen in img.c	
	--------------------------------------------------------------	*/
LOCAL void convert_image ( const BOOLEAN visible )
{
	char	filename[512], caption[512], sTemp[1024];
	char	*ptr;

	if (no_images)
	{	return;
	}

	switch(desttype)	/* Hier kein Image-Support */
	{	case TOASC:
		case TODRC:
		case TOMAN:
		case TONRO:
		case TOPCH:
		case TOINF:
		case TOTVH:
		case TOSRC:
		case TOSRP:
		case TOKPS:
			return;
	}


	/*r6pl5: Lange Dateinamen mit Leerzeichen abfangen*/
	/*Bsp.:  !image "Ein Testbild" Hier ist die Unterschrift */

	if (token[1][0]=='\"')
	{
		tokcpy2(sTemp, 1024);
		ptr= strchr(sTemp+1, '\"');		/* zweites " suchen */

		if (ptr)
		{	ptr[0]= EOS;
			strcpy(filename, sTemp+1);
			strcpy(caption, ptr+1);
			del_whitespaces(caption);
		}
		else
		{	strcpy(filename, sTemp);
			caption[0]= EOS;
		}
	}
	else
	{
		strcpy(filename, token[1]);
		token[1][0]= EOS;
		tokcpy2(caption, 512);
		del_whitespaces(caption);
	}

#if 0
	auto_quote_chars(caption, TRUE);
	c_divis(caption);
	delete_all_divis(caption);
	c_vars(caption);
	replace_udo_quotes(caption);
#endif

	check_styles(caption);	/*r6pl3*/


	switch(desttype)	
	{
		case TOSTG:
		case TOAMG:
			c_internal_styles(caption);
			change_sep_suffix(filename, ".img");
			c_img_output(filename, caption, visible);
			break;
		case TOTEX:
			qreplace_all(filename, "$\\backslash$", 12, "\\", 1);
			c_internal_styles(caption);
			qreplace_all(filename, "\\_", 2, "_", 1);
			build_image_filename(filename, ".img");
			switch (iTexVersion)
			{	case TEX_LINDNER:
				case TEX_STRUNK:
					c_img_output(filename, caption, visible);
					break;
				case TEX_EMTEX:
					if ( !c_msp_output(filename, caption, visible) )
					{	c_pcx_output(filename, caption, visible);
					}
					break;
				case TEX_MIKTEX:
					/* <???> */
					break;
				case TEX_TETEX:
					c_eps_output(filename, caption, ".eps", visible);
					break;
			}
			break;
		case TOPDL:
			c_internal_styles(caption);
			/* build_image_filename(filename, ".png");	*/
			qreplace_all(filename, "\\_", 2, "_", 1);
			c_png_output(filename, caption, ".png", visible);
			break;
		case TOLYX:
			replace_all(filename, "\\backslash"INDENT_S, "\\");
			c_internal_styles(caption);
			indent2space(caption);
			c_eps_output(filename, caption, ".eps", visible);
			break;
		case TOHTM:
		case TOMHH:
			del_internal_styles(caption);	/*r6pl3*/
			c_gif_output(filename, caption, sDocImgSuffix, 0);
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			qreplace_all(filename, "\\\\", 2, "\\", 1);
			c_win_styles(caption);
			c_bmp_output(filename, caption, visible);
			break;
		case TOIPF:
			qreplace_all(filename, "&per.", 5, ".", 1);
			c_bmp_output(filename, caption, visible);	/*r6pl6*/
			break;
		case TORTF:
			qreplace_all(filename, "\\\\", 2, "\\", 1);
			c_rtf_quotes(caption);
			c_win_styles(caption);
			c_bmp_output(filename, caption, visible);	/*r6pl6*/
			break;
		case TOHPH:	/* <???> */
			break;
	}
	
}	/* convert_image */


LOCAL void c_image ( void )
{
	convert_image(TRUE);
}

LOCAL void c_image_nonr ( void )
{
	convert_image(FALSE);
}


/*	############################################################
	#
	# Include, Einbinden von weiteren Dateien mittels
	# !include, !vinclude, !rinclude, !sinclude und !cinclude
	#
	############################################################	*/
/* nicht LOCAL, da in abo.c benutzt */
GLOBAL void c_include ( void )
{
	char	name[512];
	
	if ( token[1][0]!=EOS )
	{
		if (token[1][0]=='\"')	/*r6pl2*/
		{	tokcpy2(name, 512);
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		}
		else
		{	strcpy(name, token[1]);
		}

		b1stQuote= TRUE;
		b1stApost= TRUE;

		token_reset();
		replace_macros(name);
		switch (iUdopass)
		{	case PASS1:	pass1(name);	break;
			case PASS2:	pass2(name);	break;
			case PASSU:	passU(name);	break;
		}
		multitasking_interrupt();
	}

}	/*c_include*/


LOCAL void c_include_verbatim ( void )
{
	char	name[512];

	if ( token[1][0]!=EOS )
	{
		if (token[1][0]=='\"')	/*r6pl2*/
		{	tokcpy2(name, 512);
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		}
		else
		{	strcpy(name, token[1]);
		}
		token_reset();
		replace_macros(name);
		switch (iUdopass)
		{
			case PASS1:
				pflag[PASS1].env= ENV_VERBATIM;
				pass1(name);
				pflag[PASS1].env= ENV_NONE;
				break;
			case PASS2:
				pflag[PASS2].env= ENV_VERBATIM;
				output_begin_verbatim();
				pass2(name);
				output_end_verbatim();
				pflag[PASS2].env= ENV_NONE;
				break;
			case PASSU:
				pflag[PASSU].env= ENV_VERBATIM;
				outln("!begin_verbatim");
				passU(name);
				outln("!end_verbatim");
				pflag[PASSU].env= ENV_NONE;
				break;
		}
		multitasking_interrupt();
	}
	
}	/* c_include_verbatim */


LOCAL void c_include_preformatted ( void )
{
	char	name[512];

	if ( token[1][0]!=EOS )
	{
		if (token[1][0]=='\"')	/*r6pl2*/
		{	tokcpy2(name, 512);
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		}
		else
		{	strcpy(name, token[1]);
		}
		token_reset();
		replace_macros(name);
		switch (iUdopass)
		{
			case PASS1:
				pflag[PASS1].env= ENV_PREFORMATTED;
				pass1(name);
				pflag[PASS1].env= ENV_NONE;
				break;
			case PASS2:
				pflag[PASS2].env= ENV_PREFORMATTED;
				output_begin_verbatim();
				pass2(name);
				output_end_verbatim();
				pflag[PASS2].env= ENV_NONE;
				break;
			case PASSU:
				pflag[PASSU].env= ENV_PREFORMATTED;
				outln("!begin_preformatted");
				passU(name);
				outln("!end_preformatted");
				pflag[PASSU].env= ENV_NONE;
				break;
		}
		multitasking_interrupt();
	}
	
}	/* c_include_preformatted */


LOCAL void c_include_linedraw ( void )
{
	char	name[512];

	if ( token[1][0]!=EOS )
	{
		if (token[1][0]=='\"')
		{	tokcpy2(name, 512);
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		}
		else
		{	strcpy(name, token[1]);
		}
		token_reset();
		replace_macros(name);
		switch (iUdopass)
		{
			case PASS1:
				pflag[PASS1].env= ENV_LINEDRAW;
				pass1(name);
				pflag[PASS1].env= ENV_NONE;
				break;
			case PASS2:
				pflag[PASS2].env= ENV_LINEDRAW;
				output_begin_linedraw();
				pass2(name);
				output_end_linedraw();
				pflag[PASS2].env= ENV_NONE;
				break;
			case PASSU:
				pflag[PASSU].env= ENV_LINEDRAW;
				outln("!begin_linedraw");
				passU(name);
				outln("!end_linedraw");
				pflag[PASSU].env= ENV_NONE;
				break;
		}
		multitasking_interrupt();
	}
	
}	/* c_include_linedraw */


LOCAL void c_include_raw ( void )
{
	char	name[512];

	if ( token[1][0]!=EOS )
	{
		if (token[1][0]=='\"')	/*r6pl2*/
		{	tokcpy2(name, 512);
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		}
		else
		{	strcpy(name, token[1]);
		}

		token_reset();
		replace_macros(name);
		pflag[iUdopass].env= ENV_RAW;
		switch (iUdopass)
		{	case PASS1:
				pass1(name);
				break;
			case PASS2:
				pass2(name);
				break;
			case PASSU:
				outln("!begin_raw");
				passU(name);
				outln("!end_raw");
				break;
		}
		pflag[iUdopass].env= ENV_NONE;
		multitasking_interrupt();
	}
	
}	/* c_include_raw */


LOCAL void c_include_src ( void )
{
	char	name[512];

	if ( token[1][0]!=EOS )
	{
		if (token[1][0]=='\"')	/*r6pl2*/
		{	tokcpy2(name, 512);
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		}
		else
		{	strcpy(name, token[1]);
		}

		token_reset();
		replace_macros(name);
		switch (iUdopass)
		{
			case PASS1:
				pflag[PASS1].env= ENV_SOURCECODE;
				pass1(name);
				pflag[PASS1].env= ENV_NONE;
				break;
			case PASS2:
				pflag[PASS2].env= ENV_SOURCECODE;
				output_begin_sourcecode();
				pass2(name);
				output_end_sourcecode();
				pflag[PASS2].env= ENV_NONE;
				break;
			case PASSU:
				pflag[PASSU].env= ENV_SOURCECODE;
				outln("!begin_sourcecode");
				passU(name);
				outln("!end_sourcecode");
				pflag[PASSU].env= ENV_NONE;
				break;
		}
		multitasking_interrupt();
	}
	
}	/* c_include_src */


LOCAL void c_include_comment ( void )
{
	char name[512];

	if ( token[1][0]!=EOS )
	{
		if (token[1][0]=='\"')	/*r6pl2*/
		{	tokcpy2(name, 512);
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		}
		else
		{	strcpy(name, token[1]);
		}

		token_reset();
		replace_macros(name);
		switch (iUdopass)
		{
			case PASS1:
				pflag[PASS1].env= ENV_COMMENT;
				pass1(name);
				pflag[PASS1].env= ENV_NONE;
				break;
			case PASS2:
				pflag[PASS2].env= ENV_COMMENT;
				output_begin_comment();
				pass2(name);
				output_end_comment();
				pflag[PASS2].env= ENV_NONE;
				break;
			case PASSU:
				pflag[PASSU].env= ENV_COMMENT;
				outln("!begin_comment");
				passU(name);
				outln("!end_comment");
				pflag[PASSU].env= ENV_NONE;
				break;
		}
		multitasking_interrupt();
	}
	
}	/* c_include_comment */


LOCAL void c_input ( void )
{
	char *tmp, path[512], name[512];
	size_t sl;

	tmp= getenv("UDOINPUTPATH");
	if (tmp!=NULL)
	{	strcpy(path, tmp);
		sl= strlen(path);
		if (path[sl-1]!='\\' && path[sl-1]!='/')
		{	strcat(path, "/");
		}
	}
	else
	{	if (iUdopass!=PASS1)
		{	error_no_udoinputpath();
		}
		return;
	}

	
	if ( token[1][0]!=EOS )
	{
		if (token[1][0]=='\"')	/*r6pl2*/
		{	tokcpy2(name, 512);
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		}
		else
		{	strcpy(name, token[1]);
		}

		token_reset();
		replace_macros(name);
		strcat(path, name);
		path_adjust_separator(path);
		switch (iUdopass)
		{	case PASS1:	pass1(path);	break;
			case PASS2:	pass2(path);	break;
			case PASSU:	passU(path);	break;
		}
		multitasking_interrupt();
	}

}	/*c_input*/



/*	############################################################
	#
	#
	# Silbentrennung
	#
	#
	############################################################	*/
LOCAL void str2silben ( char *s )
{
	size_t	i, sl, yl;
	char	syl[MAX_TOKEN_LEN+1];
	
	silben_counter= -1;
	
	/* Kein Trennzeichen enthalten? */
	if ( (strchr(s, '-')==NULL) && (strchr(s, DIVIS_C)==NULL) )
	{	return;
	}

	/* Token besteht nur aus einem Bindestrich? */
	if ( (s[0]=='-') && (s[1]==EOS) )
	{	return;
	}

	/* <???> Ist das Leeren nicht ueberfluessig, wenn silbe[] */
	/* ueber strcpy() gesetzt und silben_counter benutzt wird? */
	for (i=0; i<MAXSILBEN; silbe[i++][0]= EOS) ;
	
	syl[0]= EOS;
	yl= 0;

	/* <???> Schleife optimierbar ueber while (*ptr!=EOS) */
	
	sl= strlen(s);
	
	for (i=0; i<sl; i++)
	{
		syl[yl+1]= EOS;	/* vorher: chrcat() */
		syl[yl]= s[i];
		yl++;
		
		switch (s[i])
		{	case '-':
			case '/':
				if (i>0)
				{	/* Nur dann trennen, wenn das naechste Zeichen */
					/* keine Zahl, kein Komma und )]} ist */
					if	(	((s[i+1]<'0') || (s[i+1]>'9'))
						&&	(s[i+1]!=',')
						&&	(s[i+1]!=')')
						&&	(s[i+1]!=']')
						&&	(s[i+1]!='}')
						)
					{	silben_counter++;
						strcpy(silbe[silben_counter], syl);
						syl[0]= EOS;
						yl= 0;
					}
				}
				break;
			case DIVIS_C:
				silben_counter++;
				strcpy(silbe[silben_counter], syl);
				syl[0]= EOS;
				yl= 0;
				break;
		}
	}

	if ( syl[0]!=EOS )
	{	silben_counter++;
		strcpy(silbe[silben_counter], syl);
	}
	
}	/* str2silben */



/*	############################################################
	#
	#
	# Tokenverwaltung
	#
	#
	############################################################	*/
/*	--------------------------------------------------------------
	check_parwidth()
	Testen, ob der Benutzer bei !parwith etwas brauchbares
	angegeben hat.
	--------------------------------------------------------------	*/
LOCAL void check_parwidth ( void )
{

	if (zDocParwidth<=0)
	{	zDocParwidth= tomaxlen;
	}

	if (zDocParwidth<20)
	{	zDocParwidth= MAXZEILE;
	}
	
	switch (desttype)
	{	case TOTVH:	zDocParwidth= MAXZEILE;	break;
		case TOMAN:	zDocParwidth= MAXZEILE;	break;
	}

	if (zDocParwidth>tomaxlen)
	{	zDocParwidth= tomaxlen;
	}

}	/* check_parwidth */


/*	------------------------------------------------------------
	Speicher fuer token_output anfordern und freigeben
	Da bei WinHelp, HTML und Linuxdoc-SGML erst viel spaeter
	umbrochen als 70 Zeichen wird extra ein Puffer angelegt,
	damit in token_output nicht z[16384] etc. deklariert werden
	muss. Da moeglichst dort erst dann umbrochen werden soll,
	wenn der ganze Absatz in einer Zeile steht und alle Links
	gesetzt werden koennen, sollte der Buffer so gross wie
	moeglich sein. Da in der Zeile noch Ersetzungen stattfinden
	koennen, sollte der Buffer zehnmal so gross sein wie die
	maximale Zeilenlaenge.
	------------------------------------------------------------	*/
LOCAL BOOLEAN malloc_token_output_buffer ( void )
{
	const size_t bs[6]=	{ 32768L, 16384L, 8192L, 4096L, 2048L };
	const int ml[6]=	{  3200,   1600,   800,   400,   200  };
	int i;
	
	if (format_uses_output_buffer && use_output_buffer)
	{
		for (i=0; i<6; i++)
		{	tobuffer= (char *) malloc ( bs[i] );
			if (tobuffer!=NULL)
			{	tomaxlen= ml[i];
				check_parwidth();
				return TRUE;
			}
		}
	}
	
	tobuffer= (char *) malloc ( 2048L );

	if (tobuffer==NULL)
	{	error_malloc_failed();
		return FALSE;
	}

	tomaxlen= 200;
	check_parwidth();

	return TRUE;

}	/* malloc_token_output_buffer */


/*	--------------------------------------------------------------
	free_token_output_buffer() gibt den oben angeforderten
	Speicher wieder frei.
	--------------------------------------------------------------	*/
LOCAL void free_token_output_buffer ( void )
{

	if (tobuffer!=NULL)
	{	free(tobuffer);
		tobuffer= NULL;
	}
	
}	/* free_token_output_buffer */



/*	------------------------------------------------------------
	insert_nl_token_buffer()
	Falls der Puffer verwendet wird, entstehen furchtbar lange
	Zeilen, die man schlecht nachbearbeiten koennte. Daher
	werden hier ein paar LFs an geeigneter Stelle eingefuegt.
	------------------------------------------------------------	*/
LOCAL void insert_nl_token_buffer ( void )
{
	char	*ptr, *start;
	size_t	pl;

	if (tobuffer[0]==EOS)
	{	return;
	}

	ptr= tobuffer;
	start= tobuffer;
	
	pl= strlen(ptr);
	
	while ( pl>zDocParwidth && ptr>start)
	{	
		ptr+= zDocParwidth;
		while (ptr[0]!=' ' && ptr>start)
		{	ptr--;
		}
		ptr++;
		strinsert(ptr, "\n");
		pl= strlen(ptr);
	}
		
}	/* insert_nl_token_buffer */


/*	------------------------------------------------------------
	toklen()
	toklen ermittelt die Laenge eines Strings, die er haette,
	wenn alle UDO-Spezialitaeten umgewandelt worden waeren.
	------------------------------------------------------------	*/
GLOBAL size_t toklen ( char *s )
{
	size_t len;
	char *ptr;
	
	if ( s[0]==EOS)
	{	return 0;
	}
	
	if (!format_needs_exact_toklen)
	{	return strlen(s);
	}

	ptr= s;
	len= 0;

	while (*ptr!=EOS)
	{
		switch (*ptr)
		{

			case DIVIS_C:
				/* Laenge 0 */
				break;

			case '\033':
				ptr++;
				switch (*ptr)
				{
					case C_PHOLD_MAGIC:
						/* Laenge des Linktexts addieren */
						ptr++;
						len+= pholdlen(*ptr-OFFSET_PHOLD);
						/* Und noch das ESC ueberspringen */
						ptr++;
						break;
					case C_STYLE_MAGIC:
						ptr++;
						switch (desttype)
						{
							case TOTEX:
							case TOPDL:
							case TOLYX:
							case TORTF:
							case TOWIN:
							case TOWH4:
							case TOAQV:
							case TOHPH:	/* <???> */
							case TOIPF:
								break;
							default:
								switch (*ptr)
								{	case C_FOOT_ON:
										len+= 2;	/* " (" */
										ptr++;
										break;
									case C_FOOT_OFF:
										len+= 1;	/* ")" */
										ptr++;
										break;
								}
								break;
						}
						/* ESC-Sequenz ueberspringen */
						while ( *ptr!=EOS && *ptr!='\033')
						{	ptr++;
						}
						break;
					default:
						/* ESC-Sequenz ueberspringen */
						while ( *ptr!=EOS && *ptr!='\033')
						{	ptr++;
						}
						break;
				}
				break;

			case '!':
#if 1
				/* Neue Version, die auch !/ richtig berechnet */
				/* Naechstes Zeichen betrachten */
				switch (*(ptr+1))
				{	case '/':
						/* !/ = UDO-Quote, Laenge 1 */
						len++;
						ptr++;
						break;
					case '-':
						/* !- = UDO-Trennmarke, Laenge 0 */
						ptr++;
						break;
					default:
						/* nur ! zaehlen */
						len++;
						break;
				}
				break;
#else
				switch (*ptr)
				{	case '/':
						/* !/ = UDO-Quote, Laenge 1 */
						len++;
						ptr++;
						break;
					case '-':
						/* !- = UDO-Trennmarke, Laenge 0 */
						ptr++;
						break;
					default:
						/* ! und aktuelles Zeichen zaehlen */
						len++;
						break;
				}
				break;
#endif

			default:
				len++;
				break;
		}

		ptr++;
	}

	return len;
}	/*toklen*/


/*	------------------------------------------------------------
	tokcat()
	tokcat haengt alle ab dem zweiten Token (token[1]) an einen
	String an, getrennt durch ein Leerzeichen.
	------------------------------------------------------------	*/
GLOBAL void tokcat ( char *s, int maxlen )
{	/* VJD - diverse Änderungen */
	register int i;
	int m=0; /* Länge des bisherigen Strings */
	char tmp[50];

	for (i=1; i<token_counter; i++)
	{	/* VJD */
		m+=strlen(token[i]);
		if (m<maxlen) /* Nur kopieren, wenn Puffer nicht überläuft */
		{
			strcat(s, token[i]);
			if (i<token_counter-1)
			{	strcat(s, " ");
			}
		}
	}
	if (m>=maxlen)
	{
		printf("Pufferueberlauf erkannt (tokcat): %d>=%d\n", m, maxlen);
		printf("Press [Enter]\n");
		gets(tmp);
	}
}	/*tokcat*/

/*	------------------------------------------------------------
	tokcpy2() leert den String und ruft tokcat auf. In <s>
	befinden sich alle danach mit Ausnahme des Kommandos aus
	token[0] alle Tokens, die durch Leerzeichen getrennt wurden.
	------------------------------------------------------------	*/
GLOBAL void tokcpy2 ( char *s, int maxlen )
{
	s[0]= EOS;
	tokcat(s, maxlen);
}	/*tokcpy2*/


/*	------------------------------------------------------------
	output_hyphen_line()
	Kurze Zeilen bemaengeln und Wort in die Hyphendatei sichern
	->	s:	Das ueberlange Wort
	------------------------------------------------------------	*/
LOCAL void output_hyphen_line ( const char *s )
{
	/* Erst oeffnen, wenn die Datei gebraucht wird */
	if (!bNoHypfile && !bHypopened && !bHypfailed)
	{	
		if ( outfile.full[0]!=EOS )
		{
			if (sHypfull[0]!=EOS)			
			{	fHypfile= myFwopen(sHypfull, TOASC);
				if (fHypfile == NULL)
				{	fHypfile= stderr;
					bHypfailed= TRUE;
					warning_err_hypfile();
					bErrorDetected= TRUE;
				}
				bHypopened= TRUE;
				save_upr_entry_outfile(sHypfull);
			}
		}
	}

	if (bHypopened)
	{	fprintf(fHypfile, "!hyphen %s\n", s);
	}

}	/* output_hyphen_line */


/*	--------------------------------------------------------------
	warning_short_line()
	Erzeugt eine Warnmeldung, dass eine Zeile "zu kurz" ist
	und bereitet das nicht mehr hineinpassende ueberlange Wort
	zur Ausgabe mittels output_hyphen_line() vor.
	->	len:	Laenge der kurzen Zeile
		t:		Das nicht trennbare Wort
	--------------------------------------------------------------	*/
LOCAL void warning_short_line ( const size_t len, const char *t )
{
	char	next[128], *ptr;
	size_t	i, sl;
	int		nr;
	BOOLEAN	flag;
	
	/* Wenn im naechsten Token bereits ein Trennvorschlag steckt,	*/
	/* dann die Zeile nicht bemaengeln, da offensichtlich nicht		*/
	/* besser getrennt werden kann.									*/
	if (strstr(t, DIVIS_S)!=NULL)
	{	return;
	}
	
	strcpy(next, t);
	replace_udo_quotes(next);
	c_internal_styles(next);
	replace_placeholders_text(next);
	
	replace_all(next, NBSP_S, "~");
	replace_all(next, TILDE_S, "!~");

	if ( outfile.full[0]!=EOS )
	{	warning_short_destline(outfile.full, outlines+1, (int) (len), next);
	}
	note_short_sourceline(next);

	if (!bNoHypfile)
	{
		/* Nur den Teil des Wortes bis zum ersten Minus oder	*/
		/* Leerzeichen ausgeben.								*/

		ptr=strchr(next, '-');
		if (ptr!=NULL)
		{	ptr[0]= EOS;
		}

		ptr=strchr(next, ' ');
		if (ptr!=NULL)
		{	ptr[0]= EOS;
		}

		/* Falls ein Wort nur einen Vokal enthaelt, dann macht es	*/
		/* keinen Sinn, dieses Wort in die Hyphendatei zu schreiben	*/

		nr= 0;
		for (i=0; i<strlen(next); i++)
		{	if	(	next[i]=='a' ||
					next[i]=='e' ||
					next[i]=='i' ||
					next[i]=='o' ||
					next[i]=='u'
				)
			{	nr++;
				if (nr>1)
				{	break;
				}
			}
		}
		
		if (nr>0)
		{	/* Interpunktionszeichen entfernen */
			do
			{	sl= strlen(next);
#if 1
				flag= ( strchr(" !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", next[sl-1])!=NULL );
#else
				flag=	(next[sl-1]>=' ' && next[sl-1]<='/') ||
						(next[sl-1]>=':' && next[sl-1]<='?') ||
						(next[sl-1]>='[' && next[sl-1]<='`') ||
						(next[sl-1]>='{' && next[sl-1]<='~');
#endif
				if (flag)
				{	next[sl-1]= EOS;
				}
			}	while (flag);
		
			if (next[0]!=EOS)
			{	output_hyphen_line(next);
			}
		}
	}

}	/* warning_short_line */




/*	------------------------------------------------------------
	str2tok()
	Nimmt sich einen String, pflueckt in auseinander und kopiert
	die enthaltenen Worte nach token[]
	------------------------------------------------------------	*/
GLOBAL void str2tok ( char *s )
{
	char		*tok;
	char		tmp[LINELEN+1];
	const char	*sep= " \t";	/* Leerzeichen und Tabs */

	if (token_counter>=MAX_TOKENS)
	{	error_too_many_tokens();
		return;
	}

	strcpy(tmp, s);

	tok= strtok(tmp, sep);
	
	while ( (tok!=NULL) && (token_counter<MAX_TOKENS) )
	{	strcpy(token[token_counter], tok);
		token_counter++;
		tok= strtok(NULL, sep);
	}

}	/*str2tok*/



/*	------------------------------------------------------------
	token_reset() loescht das token[]-Feld.
	Die Strings muessen alle geleert werden, da fast nirgends
	der token_counter getestet wird.
	nicht LOCAL, wird von abo.c benutzt
	------------------------------------------------------------	*/
GLOBAL void token_reset ( void )
{
	register int i;

	for (i=0; i<=token_counter; token[i++][0]= EOS) ;
	token_counter= 0;
	tokens_contain_item= FALSE;
}	/*token_reset*/



/*	------------------------------------------------------------
	to_check_rtf_quote_indent() Subfunktion von token_output()
	Quote-Umgebungen rechts einruecken. Bei RTFs wird \ri
	angehaengt, bei ASCII-Formaten der umbruch verringert.
	------------------------------------------------------------	*/
LOCAL void to_check_rtf_quote_indent ( char *s )
{
	char	t[80];
	int		i, val;
	
	if (iEnvLevel>0)
	{	val= 0;
		for (i=0; i<=iEnvLevel; i++)
		{	if (iEnvType[i]==ENV_QUOT)
			{	val+= iEnvIndent[i];
			}
		}
		if (val>0)
		{	switch(desttype)
			{	case TORTF:
					sprintf(t, "\\ri%d ", val);
					strcat(s, t);
					break;
				case TOWIN:
				case TOWH4:
				case TOAQV:
					sprintf(t, "\\ri%d ", val);
					strcat(s, t);
					break;
			}
		}
	}

}	/* to_check_rtf_quote_indent */


/*	--------------------------------------------------------------
	to_check_quote_indent() Subfunktion von token_output()
	Einrueckung fuer Quote-Umgebungen erzeugen. Fuer RTF gibt's
	eine spezielle Funktion
	->	u:	Anzahl der Leerzeichen, um die eine Zeile eingerueckt
			werden muss.
	--------------------------------------------------------------	*/
LOCAL void to_check_quote_indent ( size_t *u )
{
	int	i, val;
	
	if (iEnvLevel>0)
	{	val= 0;
		for (i=0; i<=iEnvLevel; i++)
		{	if (iEnvType[i]==ENV_QUOT)
			{	val+= iEnvIndent[i];
			}
		}
		if (val>0)
		{	switch(desttype)
			{	case TOASC:
				case TODRC:
				case TOMAN:
				case TOPCH:
				case TOSTG:
				case TOAMG:
				case TOTVH:
				case TOSRC:
				case TOSRP:
					*u-= val;
					break;
			}
		}
	}

}	/* to_check_quote_indent */


/*	##############################################################
	##############################################################

	token_output() ist eines der Herzstuecke von UDO. Hier
	werden Absaetze formatiert und ausgegeben. Hier durchzusteigen
	faellt mir langsam selber schwer. ;-)

	##############################################################
	##############################################################	*/
GLOBAL void token_output ( BOOLEAN reset_internals )
{
	register int i, j;
	int silb;
	char	*z= tobuffer;
	char	sIndent[512];
	size_t	umbruch;
	BOOLEAN	newline= FALSE;
	BOOLEAN	just_linefeed= FALSE;
	BOOLEAN	use_token;
	BOOLEAN inside_center, inside_right, inside_left, inside_quote;
	BOOLEAN inside_short, inside_env, inside_fussy;
	size_t	sl, len_zeile, len_silbe, len_token;

	if (token_counter<=0)
	{	return;
	}
	
	if (!bInsideDocument)
	{	return;
	}

	umbruch= zDocParwidth;
	
	switch (desttype)
	{	case TOSTG:	
		case TOAMG:
			umbruch= zDocParwidth;
			if (bInsidePopup && zDocParwidth>60)
			{	umbruch= 60;
			}
			break;
		case TOMAN:
			umbruch= zDocParwidth - 5;
			break;
		case TOHTM:
		case TOMHH:
			umbruch= zDocParwidth;
			if (iListLevel>0 && umbruch>70)
			{	umbruch= 70;
			}
			break;
		case TOSRC:
		case TOSRP:
			outln(sSrcRemOn);
			break;
	}
	
	inside_center= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_CENT);
	inside_right= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_RIGH);
	inside_left= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_LEFT);
	inside_quote= (iEnvLevel>0 && iEnvType[iEnvLevel]==ENV_QUOT);
	inside_env= (iItemLevel>0 || iEnumLevel>0 || iDescLevel>0 || iListLevel>0);
	inside_short= (iEnvLevel>0 && bEnvShort[iEnvLevel]);
	inside_fussy= ( (!inside_center) && (!inside_right) && (!inside_left) && (!bDocSloppy) );

	i=0;
	z[0]= EOS;
	sIndent[0]= EOS;
	len_zeile= 0;


	if ( token[0][0]!=' ' && token[0][0]!=INDENT_C)
	{	strcat_indent(z);
	}
	
	switch(desttype)
	{	case TORTF:
		case TOWIN:
		case TOWH4:
		case TOAQV:
			to_check_rtf_quote_indent(z);
			if ( inside_center )
			{	strcat(z, "\\qc ");
			}
			if ( inside_right )
			{	strcat(z, "\\qr ");
			}
			if ( inside_left )
			{	strcat(z, "\\ql ");
			}
			break;
		case TOHTM:
		case TOMHH:
			if ( !inside_short )
			{	if ( inside_center )
				{	strcat(z, "<div align=\"center\">");
				}
				else
				{	if ( inside_right )
					{	strcat(z, "<div align=\"right\">");
					}
					else
					{
						if (!inside_env)
						{	strcat(z, "<p>");
						}
						else
						{
							if (bEnv1stPara[iEnvLevel])
							{	bEnv1stPara[iEnvLevel]= FALSE;
							}
							else
							{	strcat(z, "<br>"/*"<p>"*/);
							}
						}
					}
				}
			}
			else
			{
				if (inside_env)
				{
					if (bEnv1stPara[iEnvLevel])
					{	bEnv1stPara[iEnvLevel]= FALSE;
					}
					else
					{	strcat(z, "<br>");
					}
				}
			}

			break;

		case TOIPF:
			if (!inside_env)
			{	strcat(z, ":p.");
			}
			break;

		case TOLDS:
			if (inside_quote)
			{	outln("<quote>");
			}
			break;

		case TOLYX:
			if (iEnvLevel==0)
			{	outln("\\layout Standard");
			    outln("");
			}
			else
			{	if (inside_center)
				{	outln("\\layout Standard");
				    outln("\\align center");
				}
				if (inside_right)
				{	outln("\\align right");
				}
				if (!tokens_contain_item && !inside_center)
				{	outln("\\newline");
				}
			}
			break;
		case TOKPS:
			if (inside_env)
			{
				if (bEnv1stPara[iEnvLevel])
				{	bEnv1stPara[iEnvLevel]= FALSE;
				}
				else
				{	outln(" newline");
				}
			}
			out("(");

			break;
		default:
			to_check_quote_indent(&umbruch);
			break;
	}

	if (format_protect_commands)
	{	strcpy(sIndent, z);
		if ( insert_speccmd(sIndent, sIndent, sIndent) )
		{	strcpy(z, sIndent);
		}
	}

	if (desttype==TORTF)
	{	if (iEnvLevel==0)
		{	out(rtf_plain);
			voutf("%s\\fs%d ", rtf_norm, iDocPropfontSize);
		}
	}
	
	while ( i<token_counter )
	{	use_token= TRUE;

		switch (desttype)
		{	case TOPCH:	c_pch_styles(token[i]);	break;
		}	/*switch*/
		
		if ( token[i][1]==META_C && token[i][2]!=QUOTE_C )
		{	/* vorzeitiger Zeilenumbruch? */
			if (strcmp(token[i], "(!nl)")==0)
			{	newline= TRUE;
				just_linefeed= TRUE;
				use_token= FALSE;
				switch(desttype)
				{	
					case TOTEX:
					case TOPDL:
						strcpy(token[i], "\\\\");
						break;
					case TOLYX:
						strcpy(token[i], "\n\\newline\n");
						break;
					case TOKPS:
						strcpy(token[i], ") udoshow newline\n(");

						break;
					case TONRO:
						strcpy(token[i], ".br\n");
						break;
					case TOIPF:
						strcpy(token[i], ".br\n");	/*r6pl3*/
						break;
					case TOINF:
						token[i][0]= EOS;
						if (!inside_center && !inside_right && !inside_left)
						{	strcat(z, "@*");
						}
						break;
					case TORTF:
						if ( iEnvLevel>0 )
						{
							switch(iEnvType[iEnvLevel])
							{	case ENV_ITEM:
								case ENV_ENUM:
									strcpy(token[i], "\\par\\tab\\tab ");
									break;
								case ENV_DESC:
								case ENV_LIST:
									strcpy(token[i], "\\par\\tab ");
									break;
								default:
									strcpy(token[i], "\\par ");
									break;
							}
						}
						else
						{	strcpy(token[i], "\\par ");
						}
						break;
					case TOWIN:
					case TOWH4:
					case TOAQV:
						strcpy(token[i], "\\line ");
						insert_speccmd(token[i], token[i], token[i]);
						break;
					case TOHTM:
					case TOMHH:
						strcpy(token[i], HTML_BR);
						break;
					case TOLDS:
					case TOHPH:
						strcpy(token[i], "<newline>");
						break;
					default:
						token[i][0]= EOS;
						break;
				}/*switch*/
			}/*if*/
		}/*if*/
		
		if (use_token)
		{
			len_zeile= toklen(z);
			len_token= toklen(token[i]);

			if ( (len_zeile+len_token) <= umbruch )
			{	/* Das naechste Token hat noch Platz in der Zeile */
				if ( token[i][0]!=EOS )
				{	strcat(z, token[i]);
					if (i==0 && use_justification)
					{	strcat(z, INDENT_S);
					}
					else
					{	strcat(z, " ");
					}
					/* New in r6pl15 [NHz] */
					/* Capture first blank in string for a better appearance */
					if((inside_env) && (desttype == TOKPS))
					{
						BOOLEAN replaced_blank= TRUE;
						do
						{
							replaced_blank = qreplace_once (z, "( ", 2L, "(", 1L );
						} while (replaced_blank);
					}
					len_zeile+= (len_token+1);
				}/*if*/
				newline= FALSE;
			}/*if..then*/
			else
			{	/* Die Zeile wird zu lang, also zur Ausgabe vorbereiten */
				newline= TRUE;

				switch(desttype)
				{	case TOASC:
					case TODRC:
					case TOMAN:
					case TOSTG:
					case TOAMG:
					case TOPCH:
						/* Schauen, ob das "ueberhaengende" Wort in den Trennvorschlaegen steckt */
						replace_hyphens(token[i]);
						str2silben(token[i]);
					
						if (silben_counter>=0)
						{
							silb= 0;	/* Zaehler der naechsten Silbe */

							/* len_zeile= toklen(z);: unveraendert */
							len_silbe= toklen(silbe[silb]);
							while	(	(silb<=silben_counter) &&
										( (len_zeile+len_silbe+1) <= umbruch)
									)
							{	strcat(z, silbe[silb]);
								len_zeile+= len_silbe;
								silb++;
								len_silbe= toklen(silbe[silb]);
							}/*while*/

							if ( silb>0 )
							{	/* An die Zeile wurden Silben angehaengt */
								/* In ihr befinden sich u.U. noch DIVIS_C */
								/* Daher das letzte DIVIS_C in "-" umwandeln, */
								/* anderen entfernen */
								sl= strlen(z);
								if ( z[sl-1]==DIVIS_C )
								{	z[sl-1]= '-';
									/* Deutsches c!-k in k-k wandeln */
									if ( z[sl-2]=='c' && silbe[silb][0]=='k' && destlang==TOGER)
									{	z[sl-2]='k';
									}
								}
								delete_all_divis(z);

								/* Nun noch die restlichen Silben in das */
								/* naechste Token uebertragen */
								token[i][0]= EOS;
								for (j=silb; j<=silben_counter; j++)
								{	strcat(token[i], silbe[j]);
								}
								delete_all_divis(token[i]);
							
							}/*if (silb>0)*/
						}/* if (silben_counter>=0) */
						break;
				}/*switch*/
			}/*if..else*/
		}/*if (use_token)*/
		
		if (newline)
		{
			check_styles(z);
			replace_udo_quotes(z);
			delete_all_divis(z);
			
			/* Zeilen zentrieren? */
			if (inside_center)
			{	switch(desttype)
				{	case TOASC:
					case TODRC:
					case TOMAN:
					case TOSTG:
					case TOAMG:
					case TOPCH:
					case TOTVH:
					case TOSRC:
					case TOSRP:
						del_right_spaces(z);
						strcenter(z, umbruch);
						break;
					case TOINF:
						strinsert(z, "@center ");
						break;
				}
			}

			if (inside_right)
			{	switch(desttype)
				{	case TOASC:
					case TODRC:
					case TOMAN:
					case TOSTG:
					case TOAMG:
					case TOPCH:
					case TOTVH:
					case TOSRC:
					case TOSRP:
						del_right_spaces(z);
						strright(z, umbruch);
						break;
				}
			}

			switch(desttype)
			{
				case TOTEX:
					replace_hyphens(z);
					indent2space(z);
					if ( strncmp(z, "\\\\[", 3)==0 )
					{	qreplace_once(z, "[", 1, "{\\symbol{91}}", 13);
					}
					auto_references(z, FALSE, "", 0, 0);
					break;
				case TOPDL:
					auto_references(z, FALSE, "", 0, 0);
					break;
				case TOLYX:
					c_internal_styles(z);
					indent2space(z);
					break;
				case TORTF:
					c_rtf_styles(z);
					c_rtf_quotes(z);
					break;
				case TOWIN:
				case TOWH4:
				case TOAQV:
					c_win_styles(z);
					/* Einen kleinen Maengel der Umgebungen TAB+SPACE beseitigen */
					qreplace_all(z, "\\tab  ", 6, "\\tab ", 5);
					auto_references(z, FALSE, "", 0, 0);
					break;
				case TOPCH:
					auto_references(z, FALSE, "", 0, 0);
					break;
				case TOHTM:
				case TOMHH:
					c_internal_styles(z);
					auto_references(z, FALSE, "", 0, 0);
					break;
				case TOHPH:
					break;
				case TOTVH:
					auto_references(z, FALSE, "", 0, 0);
					break;
				case TOIPF:
					auto_references(z, FALSE, "", 0, 0);
					break;
				case TOAMG:
					auto_references(z, FALSE, "", 0, 0);
					break;
				default:
					break;
			}

			/* Kurze Zeilen bemaengeln, wenn sloppy nicht gesetzt ist	*/
			/* <???> "i+1<token_counter", nicht "i<token_counter"?		*/

			if ( (inside_fussy) && (z[0]!=EOS) && (i+1<token_counter) && (!just_linefeed) )
			{	switch(desttype)
				{	case TOASC:
					case TODRC:
					case TOMAN:
					case TOSTG:
					case TOAMG:
					case TOPCH:
#if 0
						/* z wurde, ausser bei der Zentrierung	*/
						/* nicht veraendert. len_zeile hat also */
						/* noch den richtigen Wert.				*/
						len_zeile= toklen(z);
#endif
						if (use_justification && !inside_left)
						{	if (len_zeile<umbruch-9)
							{	warning_short_line(len_zeile, token[i]);
							}
						}
						else
						{	if (len_zeile<umbruch-6)
							{	warning_short_line(len_zeile, token[i]);
							}
						}
						break;
				}	/* switch */
			}	/* if */

			if ( use_justification )
			{	if ( i<token_counter && !just_linefeed && !inside_center && !inside_right && !inside_left )
				{	switch (desttype)
					{	case TOASC:
						case TODRC:
						case TOMAN:
						case TOSTG:
						case TOAMG:
						case TOPCH:
						case TOSRC:
						case TOSRP:
							del_right_spaces(z);
							strjustify(z, (size_t) umbruch);
							break;
					}
				}
				indent2space(z);
			}
			
			replace_placeholders(z);
			replace_speccmds(z);
			c_internal_styles(z);

			replace_udo_tilde(z);
			replace_udo_nbsp(z);

			/* Letztes Leerzeichen entfernen */
			if ( (desttype!=TORTF) && (desttype!=TOWIN) && (desttype!=TOWH4)
					&& (desttype!=TOAQV) && (desttype!=TOLYX) )
			{	del_right_spaces(z);
			}
			
			switch (desttype)			
			{
				case TOMAN:
					strinsert(z, "     ");
					break;
				case TOSRC:
				case TOSRP:
					strinsert(z, "    ");
					break;
				case TONRO:
					qreplace_all(z, "\n ", 2, "\n", 1);
					qreplace_all(z, "\n\n", 2, "\n", 1);
					break;
				case TOKPS:
					/* Deleted in r6pl16 [NHz] */
					/* No special line end within a paragraph  for PS anymore */
					break;
			}
			

			if (format_uses_output_buffer && use_output_buffer)
			{	insert_nl_token_buffer();
			}
			
			/* r5pl14: Fuer STG wieder ein Leerzeichen anhaengen, damit HypC */
			/* daran erkennen kann, dass der Absatz noch nicht zuende ist */
			/* Das Leerzeichen muss oben entfernt werden, da sonst der */
			/* Blocksatz weiter oben nicht richtig erzeugt wird! */
			
			if (desttype==TOSTG && !just_linefeed)
			{	strcat(z, " ");
			}

			if (!no_effects && desttype==TOASC)
			{	/* Offene Effekte am Zeilenende beenden */
				/* und unten in der naechsten Zeile oeffnen */
				check_styles_asc_last_line(z);
			}
			
			/* Endlich kann die Zeile ausgegeben werden */
			outln(z);

			/* Schonmal die naechste Zeile vorbereiten. */
			z[0]= EOS;
			len_zeile= 0;
			
			if (desttype!=TORTF && desttype!=TOWIN && desttype!=TOWH4 && desttype!=TOAQV)
			{	strcat_indent(z);
			}
			else
			{	to_check_rtf_quote_indent(z);
			}

			if (format_protect_commands)
			{	strcpy(sIndent, z);
				if ( insert_speccmd(sIndent, sIndent, sIndent) )
				{	strcpy(z, sIndent);
				}
			}

			if (!no_effects)
			{	switch (desttype)
				{	case TODRC:	check_styles_drc_next_line();	break;
					case TOASC:	check_styles_asc_next_line();	break;
				}
			}

			strcat(z, token[i]);
			
			if (!just_linefeed)
			{	strcat(z, " ");
			}
			else
			{	just_linefeed= FALSE;
			}
			
		}/*if*/
		
		i++;
	}	/* while (i<token_counter) */
	
	
	if ( z[0]!=EOS )
	{
		check_styles(z);
		replace_udo_quotes(z);
		delete_all_divis(z);
		
		if (inside_center)
		{	switch(desttype)
			{	case TOASC:
				case TODRC:
				case TOMAN:
				case TOSTG:
				case TOAMG:
				case TOPCH:
				case TOTVH:
				case TOSRC:
				case TOSRP:
					del_right_spaces(z);
					strcenter(z, umbruch);
					break;
				case TOINF:
					strinsert(z, "@center ");
					break;
			}
		}

		if (inside_right)
		{	switch(desttype)
			{	case TOASC:
				case TODRC:
				case TOMAN:
				case TOSTG:
				case TOAMG:
				case TOPCH:
				case TOTVH:
				case TOSRC:
				case TOSRP:
					del_right_spaces(z);
					strright(z, umbruch);
					break;
			}
		}

		switch(desttype)
		{
			case TOTEX:
				replace_hyphens(z);
				indent2space(z);
				if ( strncmp(z, "\\\\[", 3)==0 )
				{	qreplace_once(z, "[", 1, "{\\symbol{91}}", 13);
				}
				auto_references(z, FALSE, "", 0, 0);
				break;
			case TOPDL:
				auto_references(z, FALSE, "", 0, 0);
				break;
			case TOLYX:
				c_internal_styles(z);
				indent2space(z);
				break;
			case TORTF:
				c_rtf_styles(z);
				c_rtf_quotes(z);	/* r5pl6 */
				break;
			case TOWIN:
			case TOWH4:
			case TOAQV:
				c_win_styles(z);
				/* Einen kleinen Maengel der Umgebungen TAB+SPACE beseitigen */
				qreplace_all(z, "\\tab  ", 6, "\\tab ", 5);
				auto_references(z, FALSE, "", 0, 0);
				break;
			case TOPCH:
				auto_references(z, FALSE, "", 0, 0);
				break;
			case TOHTM:
			case TOMHH:
				c_internal_styles(z);
				auto_references(z, FALSE, "", 0, 0);
				break;
			case TOHPH:
				break;
			case TOTVH:
				auto_references(z, FALSE, "", 0, 0);
				break;
			case TOIPF:
				auto_references(z, FALSE, "", 0, 0);
				break;
			case TOAMG:
				auto_references(z, FALSE, "", 0, 0);
				break;
			default:
				break;
		}

		if (use_justification)
		{	indent2space(z);
		}

		replace_placeholders(z);
		replace_speccmds(z);
		c_internal_styles(z);

		replace_udo_tilde(z);
		replace_udo_nbsp(z);

		/* Letztes Leerzeichen entfernen */
		if ( (desttype!=TORTF) && (desttype!=TOWIN) && (desttype!=TOWH4)
				&& (desttype!=TOAQV) && (desttype!=TOLYX) )
		{	del_right_spaces(z);
		}

		switch (desttype)
		{
			case TOMAN:
				strinsert(z, "     ");
				break;
			case TOSRC:
			case TOSRP:
				strinsert(z, "    ");
				break;
			case TONRO:
				qreplace_all(z, "\n ", 2, "\n", 1);
				qreplace_all(z, "\n\n", 2, "\n", 1);
				break;
			case TOKPS:
				strcat(z, ") udoshow");
				break;
		}

		if (format_uses_output_buffer && use_output_buffer)
		{	insert_nl_token_buffer();
		}

		outln(z);
		
	}	/* if (z[0]!=EOS) */

	check_verb_style();	/* r5pl16 */

	/* Leerzeilen dann ausgeben, wenn der Absatz sich nicht in einer	*/
	/* komprimierten Umgebung befindet.									*/

	if ( inside_short )
	{	switch (desttype)
		{	case TOWIN:
			case TOWH4:
			case TOAQV:
			case TORTF:
				outln(rtf_parpard);
				break;
			case TOSRC:
			case TOSRP:
				outln(sSrcRemOff);
				break;
			case TOHTM:
			case TOMHH:
				html_ignore_p= FALSE;
				break;
			case TOTEX:
			case TOPDL:
				outln("");
				break;
			case TOKPS:
				/* Deleted in r6pl15 [NHz] */

/*				outln("newline");*/
				break;
		}
	}
	else
	{	switch (desttype)
		{	case TOWIN:
			case TOWH4:
			case TOAQV:
			case TORTF:
				outln("\\par\\pard\\par");
				break;
			case TOHTM:
			case TOMHH:
				if (!inside_short)
				{	if (inside_center || inside_right)
					{	outln("</div>");
					}
					else
					{	if (inside_env)
						{	outln("<br>&nbsp;");
						}
						else
						{	outln("</p>");
						}
					}
				}
				else
				{	if (inside_env)
					{	outln("<br>&nbsp;");
					}
					else
					{	outln("</p>\n");
					}
				}
				break;
			case TOHPH:
				outln("");
				break;
			case TONRO:
				if (!inside_env)
				{	outln("");
				}
				break;
			case TOLDS:
				if (inside_quote)
				{	outln("</quote>");
				}
				else
				{	outln("");
				}
				break;
			case TOINF:
				if (inside_center)
				{	outln("@center");
				}
				outln("");
				break;
			case TOSRC:
			case TOSRP:
				outln(sSrcRemOff);
				break;
			case TOIPF:
				break;
			case TOKPS:

			/* Changed in r6pl15 [NHz] */
				outln("newline");
/*				outln("newline newline");*/
				break;
			default:
				outln("");
				break;
		}
	}
	
	token_reset();

	if (reset_internals)
	{	reset_placeholders();
		reset_refs();
	}
	
#if 1
	reset_speccmds();
#endif

}	/*token_output*/




/*	------------------------------------------------------------
	tokenize()
	Zeilen mittels str2tok() in Tokens wandeln und eventuell
	enthaltene Kommandos ausfuehren.
	------------------------------------------------------------	*/
GLOBAL void tokenize ( char *s)
{
	BOOLEAN	newtoken= FALSE;
	BOOLEAN	reset_token= FALSE;
	BOOLEAN found= FALSE;
	register int i, j;

	if ( s[0]==EOS )
	{	return;		
	}
	
	/* Bei einem neuen Kommando erst den Token-Buffer ausgeben, */
	/* bevor das neue Kommando bearbeitet wird. */
	if ( s[0]==META_C && s[1]>='a' && s[1]<='z' )
	{	token_output(FALSE);
		newtoken= TRUE;
	}

	str2tok(s);	

	if (!newtoken)
	{	return;
	}
	
	i= 0;
	while ( (i<token_counter) && (!found) )
	{
		if (token[i][0]==META_C && token[i][1]!=QUOTE_C)
		{

			/* Sequentielle Suche */
			for (j=0; j<sizeof(udoCmdSeq) / sizeof(udoCmdSeq[0]); j++)
			{
				if	(
						(strcmp(token[i], udoCmdSeq[j].magic)==0) ||
						(udoCmdSeq[j].macut[0]!=EOS && strcmp(token[i], udoCmdSeq[j].macut)==0)
					)
				{
					switch (udoCmdSeq[j].pos)
					{	case CMD_ALWAYS:
							udoCmdSeq[j].proc();
							break;
						case CMD_ONLY_PREAMBLE:
							if (!bInsideDocument)
							{	udoCmdSeq[j].proc();
							}
							else
							{	cmd_outside_preamble();
							}
							break;
						case CMD_ONLY_MAINPART:
							if (bInsideDocument)
							{	udoCmdSeq[j].proc();
							}
							else
							{	cmd_inside_preamble();
							}
							break;
					}
					reset_token= udoCmdSeq[j].reset;
					found= TRUE;
					break;
				}	/* if */

			}	/* for */
		}	/* if */
		i++;
	}	/* while */
	
	i=0;
	while (!found && i<token_counter)
	{	for (j=0; j<MAXSWITCH; j++)
		{	if (token[i][0]==META_C && token[i][1]!=QUOTE_C)
			{	if (strcmp(token[i], udoswitch[j].magic)==0)
				{	cmd_outside_preamble();
					found= TRUE;
					reset_token= TRUE;
					break;
				}
			}
		}
		i++;
	}

	i=0;
	while (!found && i<token_counter)
	{	if (token[i][0]==META_C && token[i][1]!=QUOTE_C)
		{	error_unknown_command(token[i]);
			reset_token= TRUE;
			break;
		}
		i++;
	}
	
	if (reset_token)
	{	for (i=0; i<token_counter; token[i++][0]= EOS) ;
		token_counter= 0;
		reset_placeholders();
		reset_refs();
	}
	
}	/*tokenize*/



/*	############################################################
	#
	# Pfadseparator und Fileendung anpassen
	#
	############################################################	*/
GLOBAL void change_sep_suffix ( char *full, const char *suff )
{
	fsplit(full, tmp_driv, tmp_path, tmp_name, tmp_suff);

	path_adjust_separator(tmp_path);

#ifdef __TOS__
	/* Laufwerksbuchstabe sollte wegen Freedom gro˜ sein */
	/* Siehe E-Mail von Christian Huch @ BM */
	if (tmp_driv[0]!=EOS)	/*r6pl4*/
	{	tmp_driv[0]= toupper(tmp_driv[0]);
	}
#endif

	sprintf(full, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, suff);
	
}	/* change_sep_suffix */




/*	############################################################
	#
	# Hyphendatei sortieren und Dupes entfernen
	# Die Sortierroutine entstammt den C-Snippets
	#
	############################################################	*/
LOCAL int hyplist_compare (HYPLIST *p, HYPLIST *q)
{
	return my_stricmp(p->data, q->data);
}

LOCAL HYPLIST *hyplist_merge (HYPLIST *p, HYPLIST *q)
{
      HYPLIST *r, head;

      for ( r = &head; p && q; )
      {
            if ( hyplist_compare(p, q) < 0 )
            {
                  r = r->next = p;
                  p = p->next;
            }
            else
            {
                  r = r->next = q;
                  q = q->next;
            }
      }
      r->next = (p ? p : q);
      return head.next;
}

LOCAL HYPLIST *hyplist_sort (HYPLIST *p)
{
	  HYPLIST *q, *r;

      if ( p )
      {
            q = p;
            for ( r = q->next; r && (r = r->next) != NULL; r = r->next )
                  q = q->next;
            r = q->next;
            q->next = NULL;
            if ( r )
                  p = hyplist_merge(hyplist_sort(r), hyplist_sort(p));
      }
      return p;
}

/*	------------------------------------------------------------	*/

LOCAL HYPLIST *new_hyplist_item ( void )
{
	HYPLIST *l;

	l= (HYPLIST *) malloc (sizeof(HYPLIST));

	if (l!=NULL)
	{	memset(l, 0, sizeof(HYPLIST));
	}
	return l;
}

LOCAL BOOLEAN add_hyplist_item ( const char *s )
{
	HYPLIST *n;

	n= new_hyplist_item();
	if (n!=NULL)
	{	strcpy(n->data, s);
		n->next= hyplist;
		hyplist= n;
		return TRUE;
	}

	return FALSE;
}


LOCAL void sort_hypfile ( const char *name )
{
	FILE	*file;
	char	z[256];
	HYPLIST	*ptr;
	
	hyplist= NULL;

	if (name==NULL || *name==EOS)
	{	return;
	}
	
	file= fopen(name, "r");

	if (!file)
	{	return;
	}

	show_status_info("Reading hyphen file...");

	while (fgets(z, 256,file))
	{	add_hyplist_item(z);
	}

	fclose(file);
	
	if (hyplist==NULL)
	{	return;
	}

	show_status_info("Sorting hyphen file...");

	hyplist= hyplist_sort(hyplist);

	show_status_info("Writing hyphen file...");

	file= myFwopen(name, TOASC);
	
	if (!file)
	{	return;
	}

	ptr= hyplist;

	while (ptr!=NULL)
	{	if (ptr->next!=NULL)
		{	if (strcmp(ptr->data, ptr->next->data)!=0)
			{	fprintf(file, "%s", ptr->data);
			}
		}
		else
		{	fprintf(file, "%s", ptr->data);
		}
		ptr=ptr->next;
	}

	fclose(file);
	
}	/* sort_hypfile */



/*	############################################################
	#
	# Dateinamen setzen, falls nicht vollstaendig
	# falls ein relativer Pfad angegeben wird, werden Laufwerk
	# und Pfad des Infiles verwendet.
	# Bug: UDO kommt nicht mit "udo -o ! ../udo.u" klar.
	#
	############################################################	*/
GLOBAL void build_search_file ( char *d, const char *suff )
{
	char	tmp_path2[MYFILE_PATH_LEN+1];

	fsplit(d, tmp_driv, tmp_path, tmp_name, tmp_suff);

#ifndef __MACOS__
	if ( ((tmp_driv[0]==EOS) || (tmp_driv[1]!=':')) &&
		 ((tmp_path[0]!='\\') && (tmp_path[0]!='/'))
		)
	{	strcpy(tmp_driv, infile.driv);
		strcpy(tmp_path2, infile.path);
		strcat(tmp_path2, tmp_path);
		strcpy(tmp_path, tmp_path2);
	}
#else	/* __MACOS__ */	/* MO: nochmal leicht ueberarbeitet */
	/* Martin Osieka, 18.04.1996 */
	/* Kein Laufwerk? Dann Laufwerk von <infile> */
	if (tmp_driv[ 0] == EOS) {
		strcpy( tmp_driv, infile.driv);
	}
	/* Relativer Pfad? Dann Pfad von <infile> davor */
	if (infile.path[ 0]) {
		if ((tmp_path[ 0] == ':') && strcmp( tmp_path, infile.path)) {	/* DOS: != '\\' */
			strcpy( tmp_path2, infile.path);
			strcat( tmp_path2, &tmp_path[ 1]);
			strcpy( tmp_path, tmp_path2);
		}
		else if (tmp_path[ 0] == EOS) {
			strcpy( tmp_path, infile.path);
		}
	}
#endif	/* __MACOS__ */

#ifdef __TOS__
	/* Laufwerksbuchstabe sollte wegen Freedom gro˜ sein */
	/* Siehe E-Mail von Christian Huch @ BM */
	if (tmp_driv[0]!=EOS)	/*r6pl4*/
	{	tmp_driv[0]= toupper(tmp_driv[0]);
	}
#endif

    if (tmp_suff[0]==EOS)
    {   strcpy( tmp_suff, suff);
    }

	path_adjust_separator(tmp_path);

	sprintf( d, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
}	/* build_search_file */



/*	############################################################
	#
	# Dateinamen komplettieren, ausgehend vom Pfad der
	# Ausgabedatei
	#
	############################################################	*/
GLOBAL void build_search_file_output ( char *d, const char *suff )
{
	char	tmp_path2[MYFILE_PATH_LEN+1];

	fsplit(d, tmp_driv, tmp_path, tmp_name, tmp_suff);

#ifndef __MACOS__
	if ( ((tmp_driv[0]==EOS) || (tmp_driv[1]!=':')) &&
		 ((tmp_path[0]!='\\') && (tmp_path[0]!='/'))
		)
	{	strcpy(tmp_driv, outfile.driv);
		strcpy(tmp_path2, outfile.path);
		strcat(tmp_path2, tmp_path);
		strcpy(tmp_path, tmp_path2);
	}
#else	/* __MACOS__ */	/* MO: nochmal leicht ueberarbeitet */
	/* Martin Osieka, 18.04.1996 */
	/* Kein Laufwerk? Dann Laufwerk von <infile> */
	if (tmp_driv[ 0] == EOS) {
		strcpy( tmp_driv, outfile.driv);
	}
	/* Relativer Pfad? Dann Pfad von <infile> davor */
	if (infile.path[ 0]) {
		if ((tmp_path[ 0] == ':') && strcmp( tmp_path, outfile.path)) {	/* DOS: != '\\' */
			strcpy( tmp_path2, outfile.path);
			strcat( tmp_path2, &tmp_path[ 1]);
			strcpy( tmp_path, tmp_path2);
		}
		else if (tmp_path[ 0] == EOS) {
			strcpy( tmp_path, outfile.path);
		}
	}
#endif	/* __MACOS__ */

#ifdef __TOS__
	/* Laufwerksbuchstabe sollte wegen Freedom gro˜ sein */
	/* Siehe E-Mail von Christian Huch @ BM */
	if (tmp_driv[0]!=EOS)	/*r6pl4*/
	{	tmp_driv[0]= toupper(tmp_driv[0]);
	}
#endif

    if (tmp_suff[0]==EOS)
    {   strcpy( tmp_suff, suff);
    }

	path_adjust_separator(tmp_path);

	sprintf( d, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
}	/* build_search_file_output */



/*	############################################################
	# Falls ein Dateiname nicht vollstaendig ist, dann
	# den Pfad ausgehend vom aktuellen Verzeichnis komplettieren
	#
	# Strategie bei Uebersetzung von C:\Foo\bar.u:
	# !include foo		->	C:\Foo\foo.(suff)
	#	(1)					nur Dateiname gegeben:
	#						Laufwerk und Pfad des Infiles
	# !include \foo		->	C:\foo.(suff)
	#	(2)					absolutes Verzeichnis und Dateiname:
	#						Laufwerk des Infiles
	# !include D:\foo	->	D:\foo.(suff)
	#	(3)					absolutes Laufwerk und Verzeichnis:
	#						komplett uebernehmen
	# !include Bar\foo	->	C:\Foo\Bar\foo.(suff)
	#	(4)					relatives Verzeichnis:
	#						Laufwerk und Pfad des Infiles
	############################################################	*/
GLOBAL void build_include_filename ( char *d, const char *suff )
{

#if USE_OLD_BUILD_FILE
	build_search_file(d, suff);
	return;
#else
	char tmp_path2[MYFILE_PATH_LEN+1];

	fsplit(d, tmp_driv, tmp_path, tmp_name, tmp_suff);

# ifndef __MACOS__
	if (tmp_driv[0]==EOS)
	{	/* In Fall 1, 2 und 4 wird jeweils das Laufwerk des Infiles benutzt */
		strcpy(tmp_driv, infile.driv);

		if (tmp_path[0]==EOS)
		{	/* Fall (1) */
			strcpy(tmp_path, infile.path);
		}
		else
		{
			if (tmp_path[0]!='\\' && tmp_path[0]!='/')
			{	/* Fall (4) */
				strinsert(tmp_path, infile.path);
			}
		}
	}

	/* Die Endung wird in jedem Fall angepasst */
	if (tmp_suff[0]==EOS)
	{	strcpy(tmp_suff, suff);
	}

# else	/* __MACOS__ */	/* MO: nochmal leicht ueberarbeitet */
	/* -dh-: Martin, ggf. noch anpassen!!! */
	/* Martin Osieka, 18.04.1996 */
	/* Kein Laufwerk? Dann Laufwerk von <infile> */
	if (tmp_driv[ 0] == EOS) {
		strcpy( tmp_driv, infile.driv);
	}
	/* Relativer Pfad? Dann Pfad von <infile> davor */
	if (infile.path[ 0]) {
		if ((tmp_path[ 0] == ':') && strcmp( tmp_path, infile.path)) {	/* DOS: != '\\' */
			strcpy( tmp_path2, infile.path);
			strcat( tmp_path2, &tmp_path[ 1]);
			strcpy( tmp_path, tmp_path2);
		}
		else if (tmp_path[ 0] == EOS) {
			strcpy( tmp_path, infile.path);
		}
	}

    if (tmp_suff[0]==EOS)
    {   strcpy( tmp_suff, suff);
    }
# endif	/* __MACOS__ */


# ifdef __TOS__
	/* Laufwerksbuchstabe sollte wegen Freedom gro˜ sein */
	/* Siehe E-Mail von Christian Huch @ BM */
	if (tmp_driv[0]!=EOS)	/*r6pl4*/
	{	tmp_driv[0]= toupper(tmp_driv[0]);
	}
# endif

	path_adjust_separator(tmp_path);

	sprintf( d, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
#endif

}	/* build_include_filename */



/*	############################################################
	# Falls ein Dateiname nicht vollstaendig ist, dann
	# den Pfad ausgehend vom aktuellen Verzeichnis komplettieren
	#
	# Strategie bei Uebersetzung von C:\Foo\bar.u nach
	# C:\Foo\html\bar.html:
	# !image foo		->	C:\Foo\foo.gif
	#	(1)					nur Dateiname gegeben:
	#						Laufwerk und Pfad des Outfiles
	# !image \foo		->	C:\foo.gif
	#	(2)					absolutes Verzeichnis und Dateiname:
	#						Laufwerk des Outfiles
	# !image D:\foo		->	D:\foo.gif
	#	(3)					absolutes Laufwerk und Verzeichnis:
	#						komplett uebernehmen
	# !image Bar\foo	->	C:\Foo\Bar\foo.gif
	#	(4)					relatives Verzeichnis:
	#						Laufwerk und Pfad des Outfiles
	############################################################	*/
GLOBAL void build_image_filename ( char *d, const char *suff )
{

#if USE_OLD_BUILD_FILE
	build_search_file(d, suff);
	return;
#else
	char tmp_path2[MYFILE_PATH_LEN+1];

	fsplit(d, tmp_driv, tmp_path, tmp_name, tmp_suff);

# ifndef __MACOS__
	if (tmp_driv[0]==EOS)
	{	/* In Fall 1, 2 und 4 wird jeweils das Laufwerk des Infiles benutzt */
		strcpy(tmp_driv, outfile.driv);

		if (tmp_path[0]==EOS)
		{	/* Fall (1) */
			strcpy(tmp_path, outfile.path);
		}
		else
		{
			if (tmp_path[0]!='\\' && tmp_path[0]!='/')
			{	/* Fall (4) */
				strinsert(tmp_path, outfile.path);
			}
		}
	}

	/* Die Endung wird in jedem Fall angepasst */
	if (tmp_suff[0]==EOS)
	{	strcpy(tmp_suff, suff);
	}

# else	/* __MACOS__ */	/* MO: nochmal leicht ueberarbeitet */
	/* -dh-: Martin, ggf. noch anpassen!!! */
	/* Martin Osieka, 18.04.1996 */
	/* Kein Laufwerk? Dann Laufwerk von <infile> */
	if (tmp_driv[ 0] == EOS) {
		strcpy( tmp_driv, outfile.driv);
	}
	/* Relativer Pfad? Dann Pfad von <infile> davor */
	if (infile.path[ 0]) {
		if ((tmp_path[ 0] == ':') && strcmp( tmp_path, outfile.path)) {	/* DOS: != '\\' */
			strcpy( tmp_path2, outfile.path);
			strcat( tmp_path2, &tmp_path[ 1]);
			strcpy( tmp_path, tmp_path2);
		}
		else if (tmp_path[ 0] == EOS) {
			strcpy( tmp_path, outfile.path);
		}
	}

    if (tmp_suff[0]==EOS)
    {   strcpy( tmp_suff, suff);
    }
# endif	/* __MACOS__ */


# ifdef __TOS__
	/* Laufwerksbuchstabe sollte wegen Freedom gro˜ sein */
	/* Siehe E-Mail von Christian Huch @ BM */
	if (tmp_driv[0]!=EOS)	/*r6pl4*/
	{	tmp_driv[0]= toupper(tmp_driv[0]);
	}
# endif

	path_adjust_separator(tmp_path);

	sprintf( d, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
#endif

}	/* build_image_filename */






/*	############################################################
	#
	# Preambel fuer einige Formate ausgeben
	#
	############################################################	*/
LOCAL void output_preamble ( void )
{
	char s[512];
	
	if (no_preamble)
	{	return;
	}
	
	switch (desttype)
	{
		case TOTEX:
		case TOPDL:
			if (bTex2e)
			{	strcpy(s, "\\documentclass[11pt]");
				if (use_style_book)
				{	strcat(s, "{book}");
				}
				else
				{	strcat(s, "{article}");
				}
				outln(s);
				s[0]= EOS;
				if (destlang==TOGER)
				{	if (iTexVersion==TEX_MIKTEX)
					{	strcat(s, "germanb");
					}
					else
					{	strcat(s, "german,a4");
					}
				}
				if (!no_index && bCalledIndex)
				{	if (s[0]!= EOS)
					{	strcat(s, ",");
					}
					strcat(s, "makeidx");
				}
				if (!no_images && iTexVersion == TEX_TETEX)
				{	if (s[0]!= EOS)
					{	strcat(s, ",");
					}
					strcat(s, "graphicx");
				}
				if (s[0]!= EOS)
				{	voutlnf("\\usepackage{%s}", s);
				}
				if (desttype==TOPDL)	/* r6pl8*/
				{	outln("\\pdfoutput=1\\relax");
					if (bDocMediumCompression)
					{	outln("\\pdfcompresslevel=1");
					}
					if (bDocHighCompression)
					{	outln("\\pdfcompresslevel=9");
					}
					outln("\\pdfpagewidth=\\paperwidth");
					outln("\\pdfpageheight=\\paperheight");
				}
			}
			else
			{	strcpy(s, "\\documentstyle[11pt");
				if (destlang==TOGER)
				{	strcat(s, ",german");
				}
				if (!no_index && bCalledIndex)
				{	strcat(s, ",makeidx");
				}
				strcat(s, "]");
				if (use_style_book)
				{	strcat(s, "{book}");
				}
				else
				{	strcat(s, "{article}");
				}
				outln(s);
			}
			if (!no_index && bCalledIndex)
			{	outln("\\makeindex");
			}

			if (called_subsubsubnode)
			{	if (use_style_book)
				{	outln("\\setcounter{tocdepth}{4}");
					outln("\\setcounter{secnumdepth}{4}");
				}
				else
				{	outln("\\setcounter{tocdepth}{5}");
					outln("\\setcounter{secnumdepth}{5}");
				}
			}
			break;
			
		case TOLYX:
			voutlnf("# This file was created by UDO Release %s.%s Patchlevel %s", UDO_REL, UDO_SUBVER, UDO_PL);
			outln("# UDO (C) 1995-1999 by Dirk Hagedorn (info@dirk-hagedorn.de)");
			outln("\\lyxformat 2.10");
			voutlnf("\\textclass %s", (use_style_book) ? "book" : "article");
			outln("\\inputencoding latin1");
			outln("\\fontscheme default");
			outln("\\epsfig dvips");
			outln("\\papersize default");
			outln("\\paperfontsize 11");
			outln("\\baselinestretch 1.0");
			if (called_subsubsubnode)
			{	outln("\\secnumdepth 4");
				outln("\\tocdepth 4");
			}
			else
			{	outln("\\secnumdepth 3");
				outln("\\tocdepth 3");
			}
			outln("\\paragraph_separation indent");
			switch (destlang)
			{
				case TOENG: outln("\\language english");
							outln("\\quotes_language english");
							break;
				case TOFRA: outln("\\language french");
							outln("\\quotes_language french");
							break;
				default:	outln("\\language german");
							outln("\\quotes_language german");
							break;
			}
			outln("\\quotes_times 2");
			outln("\\paperorientation portrait");
			outln("\\papercolumns 0");
			outln("\\papersides 1");
			outln("\\paperpagestyle headings");
			outln("");
			break;

		case TODRC:
			if (titleprogram[0]!=EOS)
			{	voutlnf("%%%%Title 0, %s", titleprogram);
			}
			else
			{	voutlnf("%%%%Title 0, %s", lang.unknown);
			}
			
			outln("%%Status_line 3");
			outln("%%*");
			outln("%% 3, 0, 7, Status line");

			if (titdat.drc_statusline!=NULL)
			{	outln(titdat.drc_statusline);
			}
			else
			{	if (titdat.author!=NULL)
				{	voutlnf("Copyright (c) by %s", titdat.author);
				}
				else
				{	voutlnf("Made with UDO Release %s.%s Patchlevel %s", UDO_REL, UDO_SUBVER, UDO_PL);
				}
			}
			
			if (uses_maketitle)
			{	voutlnf("%%%%Opening_screen 1");
			}
			
			outln("%%Default_flags 7");
			break;
			
	}
	
}	/* output_preamble */




/*	############################################################
	#
	# Abfragen auf Befehle fuer format- und/oder sprachabhaengige
	# Umgebungen. Trifft die Funktion auf einen dieser Befehle,
	# so werden Flags, die in pass1() und pass2() beachtet
	# werden, gesetzt, und die Zeile geleert, so dass sie nicht
	# weiter bearbeitet wird. (r5pl6)
	#
	############################################################	*/
/*	--------------------------------------------------------------
	clear_if_stack()
	leert den Stack der !if-Umgebungen. Muss vor pass1() und
	pass2() aufgerufen werden, am besten in udo()
	--------------------------------------------------------------	*/
LOCAL void clear_if_stack ( void )
{
	register int i;

	for (i=0; i<MAX_IF_STACK; i++)
	{	if_stack[i].kind= IF_NONE;
		if_stack[i].fileline= 0;
		if_stack[i].filename[0]= EOS;
	}
	counter_if_stack= 0;
}


/*	--------------------------------------------------------------
	push_if_stack()
	packt bei "!ifdest", "!ifndest", "!iflang" und "!ifnlang" die
	Umgebung auf den Stack. Falls ignore==TRUE, werden alle Zeilen
	bis "!else" oder "!endif" von pass1() und pass2() nicht
	bearbeitet
	--------------------------------------------------------------	*/
LOCAL void push_if_stack ( int kind, BOOLEAN ignore )
{
	if (counter_if_stack<MAX_IF_STACK)
	{	counter_if_stack++;
		if_stack[counter_if_stack].kind= kind;
		if_stack[counter_if_stack].ignore= ignore;
		if_stack[counter_if_stack].fileline= uiFileLines[iFilesOpened];
		strcpy(if_stack[counter_if_stack].filename, sFileNames[iFilesOpened]);
	}
	else
	{	/* <???> Fehlermeldung fehlt */
	}

}	/* push_if_stack */


/*	--------------------------------------------------------------
	holt bei "!endif" die letzte !if-Umgebung vom Stack
	--------------------------------------------------------------	*/
LOCAL void pop_if_stack ( void )
{
	if (counter_if_stack>0)
	{	if_stack[counter_if_stack].kind= IF_NONE;
		if_stack[counter_if_stack].ignore= FALSE;
		counter_if_stack--;
	}
	else
	{	error_endif_without_if();
	}	
}	/* pop_if_stack */


/*	--------------------------------------------------------------
	wird beim Eintreffen von "!else" aufgerufen
	--------------------------------------------------------------	*/
LOCAL void toggle_if_stack ( void )
{
	if (counter_if_stack>0)
	{	if_stack[counter_if_stack].ignore=
			!(if_stack[counter_if_stack].ignore);
	}
	else
	{	error_else_without_if();
	}
}	/* toggle_if_stack */


/*	--------------------------------------------------------------
	testet, ob das ignore-Flag bei *einer* der !if-Umgebungen
	gesetzt ist
	--------------------------------------------------------------	*/
LOCAL BOOLEAN is_if_stack_ignore ( void )
{
	register int i;
	
	if (counter_if_stack>0)
	{	for (i=1; i<=counter_if_stack; i++)
		{	if (if_stack[i].ignore)
			{	return TRUE;
			}
		}
		/* Alle Umgebungen nun "durchlaessig" */
		return FALSE;
	}

	/* ueberhaupt keine Umgebung aktiv */
	return FALSE;
}	/* is_if_stack_ignore */


/*	--------------------------------------------------------------
	leert den String, damit er nicht weiterbearbeitet wird
	im 2. Durchgang wird der letzte Absatz ausgegeben
	--------------------------------------------------------------	*/
LOCAL void pass_check_free_line ( char *zeile, int pnr )
{
	if (pnr==PASS2 && token_counter>0)
	{	token_output(TRUE);
	}
	zeile[0]= EOS;
}


/*	--------------------------------------------------------------
	pass_check_if()
	Ueberprueft Zeilen auf die Abfragebefehle und leitete dann
	die notfalls noetigen Schritte ein (Setzen der Ignore-Flags)
	--------------------------------------------------------------	*/
LOCAL void pass_check_if (char *zeile, int pnr)
{
	BOOLEAN ignore, match;
	BOOLEAN	matches_lang, matches_dest, matches_symb, matches_os;
	
	if ( strstr(zeile, "!ifdest")!=NULL )
	{	ignore= !str_for_desttype(zeile);
		push_if_stack(IF_DEST, ignore);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!ifndest")!=NULL )
	{	ignore= str_for_desttype(zeile);
		push_if_stack(IF_DEST, ignore);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!iflang")!=NULL )
	{	ignore= !str_for_destlang(zeile);
		push_if_stack(IF_LANG, ignore);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!ifnlang")!=NULL )
	{	ignore= str_for_destlang(zeile);
		push_if_stack(IF_LANG, ignore);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!ifos")!=NULL )
	{	ignore= !str_for_os(zeile);
		push_if_stack(IF_OS, ignore);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!ifnos")!=NULL )
	{	ignore= str_for_os(zeile);
		push_if_stack(IF_OS, ignore);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!ifset")!=NULL )
	{	ignore= !udosymbol_set(zeile);
		push_if_stack(IF_SET, ignore);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!ifnset")!=NULL )
	{	ignore= udosymbol_set(zeile);
		push_if_stack(IF_SET, ignore);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!if")!=NULL )
	{	matches_dest= str_for_desttype(zeile);
		matches_lang= str_for_destlang(zeile);
		matches_os= str_for_os(zeile);
		matches_symb= udosymbol_set(zeile);
		match= (matches_dest | matches_lang | matches_symb | matches_os);
		push_if_stack(IF_GENERAL, !match);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!begin_ignore")!=NULL )
	{	push_if_stack(IF_GENERAL, TRUE);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}


#if 0
	if ( strstr(zeile, "!elif")!=NULL )	
	{	pop_if_stack();
		pflag[pnr].ignore_line= is_if_stack_ignore();
		matches_dest= str_for_desttype(zeile);
		matches_lang= str_for_destlang(zeile);
		matches_os= str_for_os(zeile);
		matches_symb= udosymbol_set(zeile);
		match= (matches_dest | matches_lang | matches_symb);
		push_if_stack(IF_GENERAL, !match);
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}
#endif

	if ( strstr(zeile, "!else")!=NULL )
	{	toggle_if_stack();
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!endif")!=NULL )
	{	pop_if_stack();
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

	if ( strstr(zeile, "!end_ignore")!=NULL )
	{	pop_if_stack();
		pflag[pnr].ignore_line= is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return;
	}

}	/*pass_check_if*/


/*	############################################################
	#
	# Schalter suchen, setzen und auswerten
	# Moegliche Syntax:
	# !no_* [<formate>]
	# !use_* [<formate>] !<parameter> <wert>
	############################################################	*/
LOCAL void get_switch_par ( const UDOSWITCH *us )
{
	register int i;
	int val;
	
	if (us->parcmd[0]==EOS)
	{	return;
	}
	
	for (i=1; i<token_counter; i++)
	{
		if (strcmp(token[i], us->parcmd)==0)
		{
			switch (us->partype)
			{
				case 'b':	/* boolean */
					*(BOOLEAN *)(us->parval)= TRUE;
					return;

				case 'i':	/* int */
					if (i+1<token_counter)
					{
						val= atoi(token[i+1]);
						if (us->parval!=NULL)
						{
							*(int *)(us->parval)= val;
						}
					}
					return;
			}
		}
	}
	
}	/* get_switch_par */



LOCAL BOOLEAN pass1_check_preamble_commands ( void )
{
	register int i;
	int c;
	char s[256];
	
	/* Allgemeine globale Schalter (im Vorspann erlaubt) */

	for (i=0; i<MAXSWITCH; i++)
	{	if ( strcmp(token[0], udoswitch[i].magic)==0 )
		{	if (is_for_desttype(udoswitch[i].flag, udoswitch[i].magic))
			{	get_switch_par(&(udoswitch[i]));
			}
			return TRUE;
		}
	}


	/* Allgemeine lokale Schalter */

	if ( strcmp(token[0], "!toc_offset")==0 )
	{	if (token[1][0]==EOS)
		{	toc_offset= 0;
		}
		else
		{	toc_offset= atoi(token[1]);
		}
		return TRUE;
	}

	if ( strcmp(token[0], "!subtoc_offset")==0 )
	{	if (token[1][0]==EOS)
		{	subtoc_offset= 0;
		}
		else
		{	subtoc_offset= atoi(token[1]);
		}
		return TRUE;
	}

	if ( strcmp(token[0], "!subsubtoc_offset")==0 )
	{	if (token[1][0]==EOS)
		{	subsubtoc_offset= 0;
		}
		else
		{	subsubtoc_offset= atoi(token[1]);
		}
		return TRUE;
	}

	if ( strcmp(token[0], "!subsubsubtoc_offset")==0 )
	{	if (token[1][0]==EOS)
		{	subsubsubtoc_offset= 0;
		}
		else
		{	subsubsubtoc_offset= atoi(token[1]);
		}
		return TRUE;
	}

	if ( strcmp(token[0], "!table_counter")==0 )
	{	if (token[1][0]==EOS)
		{	set_table_counter(0);
		}
		else
		{	set_table_counter(atoi(token[1]));
		}
		return TRUE;
	}

	if ( strcmp(token[0], "!image_counter")==0 )
	{	if (token[1][0]==EOS)
		{	set_image_counter(0);
		}
		else
		{	set_image_counter(atoi(token[1]));
		}
		return TRUE;
	}


	if ( strcmp(token[0], "!language")==0 )
	{	tokcpy2(s, 256);	/* r6pl2: str... auf s statt token[1] */
		for (i=0; i<MAXLANGUAGE; i++)
		{	if (strstr(s, udolanguage[i].magic)!=NULL)	/* r6pl2: strstr statt strcmp */
			{	destlang= udolanguage[i].langval;
				init_lang();
				init_lang_date();
				return TRUE;
			}
		}
		error_no_language(s);
		return TRUE;
	}

	if (strcmp(token[0], "!parwidth")==0)
	{	zDocParwidth= atoi(token[1]);
		return TRUE;
	}

	if (strcmp(token[0], "!sort_hyphen_file")==0)
	{	bDocSortHyphenFile= TRUE;
		return TRUE;
	}

	if (strcmp(token[0], "!image_alignment")==0)
	{	set_image_alignment();
		return TRUE;
	}

	if (strcmp(token[0], "!table_alignment")==0)
	{	set_table_alignment();
		return TRUE;
	}

	/* spezielle Schalter */

	switch (desttype)
	{
		case TOTEX:
			if (strncmp(token[0], "!tex", 4)!=0)
			{	return FALSE;
			}
			if (strcmp(token[0], "!tex_lindner")==0)
			{	iTexVersion= TEX_LINDNER;
				bTex2e = FALSE;
				return TRUE;
			}
			if (strcmp(token[0], "!tex_strunk")==0)
			{	iTexVersion= TEX_STRUNK;
				bTex2e = FALSE;
				return TRUE;
			}
			if (strcmp(token[0], "!tex_emtex")==0)
			{	iTexVersion= TEX_EMTEX;
				bTex2e = FALSE;
				return TRUE;
			}
			if (strcmp(token[0], "!tex_miktex")==0)
			{	iTexVersion= TEX_MIKTEX;
				bTex2e= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!tex_tetex")==0)
			{	iTexVersion= TEX_TETEX;
				bTex2e= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!tex_2e")==0)
			{	bTex2e= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!tex_209")==0) 
			{	bTex2e= FALSE; 
				return TRUE; 
			} 
			break;

		case TOPDL:
			if (strncmp(token[0], "!pdf", 4)!=0)
			{	return FALSE;
			}
			if (strcmp(token[0], "!pdf_high_compression")==0)
			{	bDocHighCompression= TRUE;
				bDocMediumCompression= FALSE;
				return TRUE;
			}
			if (strcmp(token[0], "!pdf_medium_compression")==0)
			{	bDocMediumCompression= TRUE;
				bDocHighCompression= FALSE;
				return TRUE;
			}
			break;

		case TOMAN:
			if (strcmp(token[0], "!man_lpp")==0)
			{	iManPageLength= atoi(token[1]);
				if (iManPageLength<0)
				{	iManPageLength= 0;
				}
				return TRUE;
			}
			if (strcmp(token[0], "!man_type")==0)
			{	tokcpy2(sDocManType, 32);
				return TRUE;
			}
			break;

		case TONRO:
			if (strcmp(token[0], "!nroff_type")==0)
			{	tokcpy2(sDocNroffType, 32);
				return TRUE;
			}
			break;

		case TODRC:
			if (strcmp(token[0], "!drc_flags")==0)
			{	c_drc_flags();
			}
			break;

		case TOWIN:
		case TOAQV:
			if (strcmp(token[0], "!win_backcolor")==0)
			{	c= get_color();
				set_win_backcolor(sDocBackColor, c);
				return TRUE;
			}
			if (strcmp(token[0], "!win_textcolor")==0)
			{	c= get_color();
				set_win_textcolor(sDocTextColor, c);
				return TRUE;
			}
			if (strcmp(token[0], "!win_linkcolor")==0)
			{	c= get_color();
				set_win_linkcolor(sDocLinkColor, c);
				return TRUE;
			}
			if (strcmp(token[0], "!win_inline_bitmaps")==0)
			{	bDocInlineBitmaps= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!win_high_compression")==0)
			{	bDocHighCompression= TRUE;
				bDocMediumCompression= FALSE;
				return TRUE;
			}
			if (strcmp(token[0], "!win_medium_compression")==0)
			{	bDocMediumCompression= TRUE;
				bDocHighCompression= FALSE;
				return TRUE;
			}
			if (strcmp(token[0], "!win_propfont")==0)
			{	tokcpy2(sDocPropfont, MAXZEILE+1);
				return TRUE;
			}
			if (strcmp(token[0], "!win_monofont")==0)
			{	tokcpy2(sDocMonofont, MAXZEILE+1);
				return TRUE;
			}
			if (strcmp(token[0], "!win_propfont_size")==0)
			{	tokcpy2(sDocPropfontSize, 16);
				return TRUE;
			}
			if (strcmp(token[0], "!win_monofont_size")==0)
			{	tokcpy2(sDocMonofontSize, 16);
				return TRUE;
			}
			if (strcmp(token[0], "!win_background")==0)
			{	c= get_color();
				set_win_backcolor(sDocBackColor, c);
				return TRUE;
			}
			if (strcmp(token[0], "!win_old_keywords")==0)
			{	bDocWinOldKeywords= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!win_prefix_helpids")==0)
			{	tokcpy2(sDocWinPrefixID, 64);
				return TRUE;
			}
			break;

		case TOWH4:
			if (strcmp(token[0], "!wh4_backcolor")==0)
			{	c= get_color();
				set_wh4_backcolor(sDocBackColor, c);
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_textcolor")==0)
			{	c= get_color();
				set_wh4_textcolor(sDocTextColor, c);
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_linkcolor")==0)
			{	c= get_color();
				set_wh4_linkcolor(sDocLinkColor, c);
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_inline_bitmaps")==0)
			{	bDocInlineBitmaps= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_high_compression")==0)
			{	bDocHighCompression= TRUE;
				bDocMediumCompression= FALSE;
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_medium_compression")==0)
			{	bDocHighCompression= FALSE;
				bDocMediumCompression= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_propfont")==0)
			{	tokcpy2(sDocPropfont, MAXZEILE+1);
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_monofont")==0)
			{	tokcpy2(sDocMonofont, MAXZEILE+1);
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_propfont_size")==0)
			{	tokcpy2(sDocPropfontSize, 16);
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_monofont_size")==0)
			{	tokcpy2(sDocMonofontSize, 16);
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_background")==0)
			{	c= get_color();
				set_win_backcolor(sDocBackColor, c);
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_old_keywords")==0)
			{	bDocWinOldKeywords= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!wh4_prefix_helpids")==0)
			{	tokcpy2(sDocWinPrefixID, 64);
				return TRUE;
			}
			break;

		case TORTF:
			if (strcmp(token[0], "!rtf_no_tables")==0)
			{	bDocNoTables= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!rtf_monofont")==0)
			{	tokcpy2(sDocMonofont, MAXZEILE+1);
				return TRUE;
			}
			if (strcmp(token[0], "!rtf_propfont")==0)
			{	tokcpy2(sDocPropfont, MAXZEILE+1);
				return TRUE;
			}
			if (strcmp(token[0], "!rtf_monofont_size")==0)
			{	tokcpy2(sDocMonofontSize, 16);
				return TRUE;
			}
			if (strcmp(token[0], "!rtf_propfont_size")==0)
			{	tokcpy2(sDocPropfontSize, 16);
				return TRUE;
			}
			break;

		case TOHTM:
			if (strncmp(token[0], "!html", 5)!=0)
			{	return FALSE;
			}
			if (strcmp(token[0], "!html_merge_nodes")==0)
			{	html_merge_node1= TRUE;
				html_merge_node2= TRUE;
				html_merge_node3= TRUE;
				html_merge_node4= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!html_merge_subnodes")==0)
			{	html_merge_node2= TRUE;
				html_merge_node3= TRUE;
				html_merge_node4= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!html_merge_subsubnodes")==0)
			{	html_merge_node3= TRUE;
				html_merge_node4= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!html_merge_subsubsubnodes")==0)
			{	html_merge_node4= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!html_no_xlist")==0)
			{	html_no_xlist= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!html_ignore_8bit")==0)
			{	html_ignore_8bit= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!html_modern_layout")==0)
			{	html_modern_layout= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!html_frames_layout")==0)
			{	set_html_frames_layout();
				return TRUE;
			}
			if (strcmp(token[0], "!html_backpage")==0)
			{	tokcpy2(sDocHtmlBackpage, 512);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_backcolor")==0 )
			{	set_html_color(HTML_COLOR_BACK);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_textcolor")==0 )
			{	set_html_color(HTML_COLOR_TEXT);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_linkcolor")==0 )
			{	set_html_color(HTML_COLOR_LINK);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_alinkcolor")==0 )
			{	set_html_color(HTML_COLOR_ALINK);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_vlinkcolor")==0 )
			{	set_html_color(HTML_COLOR_VLINK);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_backimage")==0 )
			{	set_html_backimage();
				return TRUE;
			}
			/* New in r6pl15 [NHz] */
			if ( strcmp(token[0], "!html_style_name")==0 )
			{	set_html_style();
				return TRUE;
			}
			/* New in r6pl15 [NHz] */
			if ( strcmp(token[0], "!html_script_name")==0 )
			{	set_html_script();
				return TRUE;
			}
			/* New in r6pl15 [NHz] */
			if ( strcmp(token[0], "!html_favicon_name")==0 )
			{	set_html_favicon();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_modern_width")==0 )
			{	set_html_modern_width();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_modern_alignment")==0 )
			{	set_html_modern_alignment();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_modern_backcolor")==0 )
			{	set_html_special_color(html_modern_backcolor);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_modern_backimage")==0 )
			{	set_html_modern_backimage();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_frames_width")==0 )
			{	set_html_frames_width();
				return TRUE;
			}
			if (strcmp(token[0], "!html_frames_alignment")==0)
			{	set_html_frames_alignment();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_frames_position")==0 )
			{	set_html_frames_position();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_frames_backcolor")==0 )
			{	set_html_special_color(html_frames_backcolor);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_frames_textcolor")==0 )
			{	set_html_special_color(html_frames_textcolor);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_frames_linkcolor")==0 )
			{	set_html_special_color(html_frames_linkcolor);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_frames_alinkcolor")==0 )
			{	set_html_special_color(html_frames_alinkcolor);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_frames_vlinkcolor")==0 )
			{	set_html_special_color(html_frames_vlinkcolor);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_frames_backimage")==0 )
			{	set_html_frames_backimage();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_button_alignment")==0 )
			{	set_html_button_alignment();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_transparent_buttons")==0 )
			{	html_transparent_buttons= TRUE;
				return TRUE;
			}
			if ( strcmp(token[0], "!html_use_folders")==0 )
			{	html_use_folders= TRUE;
				return TRUE;
			}
			if (strcmp(token[0], "!html_propfont_name")==0)
			{	tokcpy2(sDocHtmlPropfontName, 64);
				return TRUE;
			}
			if (strcmp(token[0], "!html_propfont_size")==0)
			{	tokcpy2(sDocHtmlPropfontSize, 16);
				return TRUE;
			}
			if (strcmp(token[0], "!html_monofont_name")==0)
			{	tokcpy2(sDocHtmlMonofontName, 64);
				return TRUE;
			}
			if (strcmp(token[0], "!html_monofont_size")==0)
			{	tokcpy2(sDocHtmlMonofontSize, 16);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_name_prefix")==0 )
			{	set_html_filename_prefix();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_switch_language")==0 )
			{	set_html_switch_language();
				return TRUE;
			}
			/* New in r6pl16 [NHz] */
			if ( strcmp(token[0], "!html_use_hyphenation")==0 )
			{	html_use_hyphenation = TRUE;
				return TRUE;
			}
			/* New in r6pl16 [NHz] */
			if ( strcmp(token[0], "!html_doctype")==0 )
			{	set_html_doctype();
				return TRUE;
			}
			break;
	}	/* switch */


	return FALSE;
}	/*pass1_check_preamble_commands*/



LOCAL BOOLEAN pass1_check_main_commands ( void )
{
	/* spezielle Schalter (nur im Hauptteil erlaubt) */

	switch (desttype)
	{
		case TOHTM:
			if (strncmp(token[0], "!html", 5)!=0)
			{	return FALSE;
			}
			if ( strcmp(token[0], "!html_name")==0 )
			{	set_html_filename();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_dirname")==0 )
			{	set_html_dirname();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_keywords")==0 )
			{	set_html_keywords();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_description")==0 )
			{	set_html_description();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_counter_command")==0 )
			{	set_html_counter_command();
				return TRUE;
			}
			break;
	}

	return FALSE;
}	/*pass1_check_main_commands*/



LOCAL BOOLEAN pass1_check_everywhere_commands ( void )
{
	/* spezielle Schalter (ueberall erlaubt) */

	switch (desttype)
	{
		case TOHTM:
			if (strncmp(token[0], "!html", 5)!=0)
			{	return FALSE;
			}
			if ( strcmp(token[0], "!html_img_suffix")==0 )
			{	c_html_img_suffix();
				return TRUE;
			}
			if ( strcmp(token[0], "!html_backcolor")==0 )
			{	set_html_color(HTML_COLOR_BACK);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_textcolor")==0 )
			{	set_html_color(HTML_COLOR_TEXT);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_linkcolor")==0 )
			{	set_html_color(HTML_COLOR_LINK);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_alinkcolor")==0 )
			{	set_html_color(HTML_COLOR_ALINK);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_vlinkcolor")==0 )
			{	set_html_color(HTML_COLOR_VLINK);
				return TRUE;
			}
			if ( strcmp(token[0], "!html_backimage")==0 )
			{	set_html_backimage();
				return TRUE;
			}
			break;

		case TOMHH:
			if (strncmp(token[0], "!hh", 3)!=0)
			{	return FALSE;
			}

			if ( strcmp(token[0], "!hh_backcolor")==0 )
			{	set_html_color(HTML_COLOR_BACK);
				return TRUE;
			}
			if ( strcmp(token[0], "!hh_textcolor")==0 )
			{	set_html_color(HTML_COLOR_TEXT);
				return TRUE;
			}
			if ( strcmp(token[0], "!hh_linkcolor")==0 )
			{	set_html_color(HTML_COLOR_LINK);
				return TRUE;
			}
			if ( strcmp(token[0], "!hh_alinkcolor")==0 )
			{	set_html_color(HTML_COLOR_ALINK);
				return TRUE;
			}
			if ( strcmp(token[0], "!hh_vlinkcolor")==0 )
			{	set_html_color(HTML_COLOR_VLINK);
				return TRUE;
			}
			if ( strcmp(token[0], "!hh_backimage")==0 )
			{	set_html_backimage();
				return TRUE;
			}

		case TODRC:
			if (strncmp(token[0], "!drc", 4)!=0)
			{	return FALSE;
			}
			if ( strcmp(token[0], "!drc_bcolor")==0 )
			{	c_drc_bcolor();
				return TRUE;
			}
			if ( strcmp(token[0], "!drc_icolor")==0 )
			{	c_drc_icolor();
				return TRUE;
			}
			if ( strcmp(token[0], "!drc_ucolor")==0 )
			{	c_drc_ucolor();
				return TRUE;
			}
			break;
	}	/* switch */


	return FALSE;
}	/*pass1_check_everywhere_commands*/



/*	############################################################
	#
	# Spezielle Umgebungen fuer Pass 1 testen
	#
	############################################################	*/
LOCAL void pass1_check_environments ( char *zeile )
{
	/* Verbatim-Umgebung */
	if ( pflag[PASS1].env==ENV_NONE || pflag[PASS1].env==ENV_VERBATIM )
	{	if ( strstr(zeile, CMD_BEGIN_VERBATIM)!=NULL )
		{	pflag[PASS1].env= ENV_VERBATIM;
			zeile[0]= EOS;
			return;
		}	else
		if ( strstr(zeile, CMD_END_VERBATIM)!=NULL )
		{	pflag[PASS1].env= ENV_NONE;
			zeile[0]= EOS;
			return;
		}
	}

	/* Sourcecode-Umgebung */
	if ( pflag[PASS1].env==ENV_NONE || pflag[PASS1].env==ENV_SOURCECODE )
	{	if ( strstr(zeile, CMD_BEGIN_SOURCECODE)!=NULL )
		{	pflag[PASS1].env= ENV_SOURCECODE;
			zeile[0]= EOS;
			return;
		}	else
		if ( strstr(zeile, CMD_END_SOURCECODE)!=NULL )
		{	pflag[PASS1].env= ENV_NONE;
			zeile[0]= EOS;
			return;
		}
	}

	/* Raw-Umgebung */
	if ( pflag[PASS1].env==ENV_NONE || pflag[PASS1].env==ENV_RAW )
	{	if ( strstr(zeile, CMD_BEGIN_RAW)!=NULL )
		{	pflag[PASS1].env= ENV_RAW;
			zeile[0]= EOS;
			return;
		}	else
		if ( strstr(zeile, CMD_END_RAW)!=NULL )
		{	pflag[PASS1].env= ENV_NONE;
			zeile[0]= EOS;
			return;
		}
	}

	/* Table-Umgebung */
	if ( pflag[PASS1].env==ENV_NONE || pflag[PASS1].env==ENV_TABLE )
	{	if ( strstr(zeile, CMD_BEGIN_TABLE)!=NULL )
		{	if (pflag[PASS1].env==ENV_TABLE)
			{	/* <???> Fehlermeldung!! */
			}
			pflag[PASS1].env= ENV_TABLE;
			zeile[0]= EOS;
			return;
		}	else
		if ( strstr(zeile, CMD_END_TABLE)!=NULL )
		{	pflag[PASS1].env= ENV_NONE;
			zeile[0]= EOS;
			return;
		}
	}

	/* Comment-Umgebung r6pl2 */
	if ( pflag[PASS1].env==ENV_NONE || pflag[PASS1].env==ENV_COMMENT )
	{	if ( strstr(zeile, CMD_BEGIN_COMMENT)!=NULL )
		{	pflag[PASS1].env= ENV_COMMENT;
			zeile[0]= EOS;
			return;
		}	else
		if ( strstr(zeile, CMD_END_COMMENT)!=NULL )
		{	pflag[PASS1].env= ENV_NONE;
			zeile[0]= EOS;
			return;
		}
	}

	/* Linedraw-Umgebung r6pl5 */
	if ( pflag[PASS1].env==ENV_NONE || pflag[PASS1].env==ENV_LINEDRAW )
	{	if ( strstr(zeile, CMD_BEGIN_LINEDRAW)!=NULL )
		{	pflag[PASS1].env= ENV_LINEDRAW;
			zeile[0]= EOS;
			return;
		}	else
		if ( strstr(zeile, CMD_END_LINEDRAW)!=NULL )
		{	pflag[PASS1].env= ENV_NONE;
			zeile[0]= EOS;
			return;
		}
	}

	/* Preformatted-Umgebung r6pl5*/
	if ( pflag[PASS1].env==ENV_NONE || pflag[PASS1].env==ENV_PREFORMATTED )
	{	if ( strstr(zeile, CMD_BEGIN_PREFORMATTED)!=NULL )
		{	pflag[PASS1].env= ENV_PREFORMATTED;
			zeile[0]= EOS;
			return;
		}	else
		if ( strstr(zeile, CMD_END_PREFORMATTED)!=NULL )
		{	pflag[PASS1].env= ENV_NONE;
			zeile[0]= EOS;
			return;
		}
	}

}	/* pass1_check_environments */



/*	############################################################
	#
	# Zeilen einlesen und Inhaltsverzeichnis ermitteln (Pass One)
	#
	############################################################	*/

#define	USE_PASS1_OUTPUT	0	

LOCAL BOOLEAN pass1 (char *datei)
{
	MYTEXTFILE 	*file;
	char	zeile[LINELEN], tmp_datei[256], old_datei[256];
	char	tmp[512];
	size_t	len;
	int		i;


	if (iFilesOpened>=MAXFILECOUNTER)
	{	error_too_many_files();
		return FALSE;
	}

	strcpy(old_datei, datei);
	strcpy(tmp_datei, datei);

	build_include_filename(tmp_datei, ".ui");
	file = myTextOpen(tmp_datei);
	
	if (file == NULL)
	{	strcpy(tmp_datei, old_datei);
		file = myTextOpen(tmp_datei);
	}
	
	if (file == NULL)
	{
		bErrorDetected= TRUE;

		return FALSE;
	}
	
	/* r5pl14: Rekursive Includes testen */
	for (i=0; i<iFilesOpened; i++)
	{	if ( strcmp(sFileNames[i], tmp_datei)==0 )
		{	error_fatal_error("Recursive include detected");
			bFatalErrorDetected= TRUE;
			myTextClose(file);
			return FALSE;
		}
	}

	if (bVerbose)
	{	show_status_file_1(tmp_datei);
	}

	iFilesOpened++;
	uiFileLines[iFilesOpened]= 0;
	strcpy(sFileNames[iFilesOpened], tmp_datei);

	strcpy(sCurrFileName, tmp_datei);
	uiCurrFileLine= 0;

	while ( (!bBreakHappened) && (!bBreakInside) && (!bFatalErrorDetected) && (myTextGetline(zeile, LINELEN, file)) )
	{
		uiFileLines[iFilesOpened]++;
		uiCurrFileLine= uiFileLines[iFilesOpened];

		lPass1Lines++;
		
		if ( break_action() )
		{	iFilesOpened--;
			myTextClose(file);
			strcpy(sCurrFileName, sFileNames[iFilesOpened]);
			return FALSE;
		}

#if 0
		/* Was passiert bei den rekursiven Aufrufen mit goto? */
		if ( zeile[0]=='#')
		{	goto PASS1_READ_NEXT_LINE;
		}
#endif


		len= strlen(zeile);
		while (  (len>0) && (((UCHAR) zeile[len-1])<=32) )
		{	zeile[len-1]= EOS;
			len--;
		}

		if (zeile[0]!='#')			/* Kommentare nicht recoden */
		{	recode(zeile, iCharset);
			convert_sz(zeile);
		}

		if	(	(zeile[0]!='#' && (zeile[0]!=EOS) )
			&& (pflag[PASS1].env==ENV_NONE)
			)
		{
			pass_check_if(zeile, PASS1);
			
		}	/*if ( zeile[0]!='#' )*/



		if	(	(zeile[0]!='#')
			&&	(zeile[0]!=EOS)
			&&	(pflag[PASS1].ignore_line==0)
			)
		{
			pass1_check_environments(zeile);
		}


		if ( zeile[0]!=EOS )
		{
			if	(
				(pflag[PASS1].ignore_line==0)
				&& (pflag[PASS1].env==ENV_NONE)
				)
			{
				del_whitespaces(zeile);
				
				if ( (zeile[0]==META_C) && (zeile[1]!=QUOTE_C) )
				{	/* Erster Parameter von !macro und !define	*/
					/* darf nicht gequotet werden!				*/
					if (!bInsideDocument)
					{	if ( strncmp(zeile, "!define", 7)==0 )
						{	token_reset();

							if( strstr(zeile, "!\\") != NULL )

							{	char tmp_zeile[512];

								long lang;

								do

								{	myTextGetline(tmp_zeile, LINELEN, file);

									lang = strlen(zeile);

									zeile[lang-2] = EOS;

									strcat(zeile, tmp_zeile);



									uiFileLines[iFilesOpened]++;
									uiCurrFileLine= uiFileLines[iFilesOpened];

									lPass1Lines++;
								} while( strstr(tmp_zeile, "!\\") != NULL );

							}

							str2tok(zeile);
							add_define();
							zeile[0]= EOS;
						}

						if ( strncmp(zeile, "!macro", 6)==0 )
						{	token_reset();
							if( strstr(zeile, "!\\") != NULL )

							{	char tmp_zeile[512];

								long lang;

								do

								{	myTextGetline(tmp_zeile, LINELEN, file);

									lang = strlen(zeile);

									zeile[lang-2] = EOS;

									strcat(zeile, tmp_zeile);



									uiFileLines[iFilesOpened]++;
									uiCurrFileLine= uiFileLines[iFilesOpened];

									lPass1Lines++;
								} while( strstr(tmp_zeile, "!\\") != NULL );

							}

							str2tok(zeile);
							add_macro();
							zeile[0]= EOS;
						}

						if ( strncmp(zeile, CMD_SET, 4)==0 )
						{	token_reset();
							str2tok(zeile);
							zeile[0]= EOS;
							tokcpy2(zeile, LINELEN);
							add_udosymbol(zeile);
							zeile[0]= EOS;
						}

						if ( strncmp(zeile, CMD_UNSET, 6)==0 )
						{	token_reset();
							str2tok(zeile);
							zeile[0]= EOS;
							tokcpy2(zeile, LINELEN);
							del_udosymbol(zeile);
							zeile[0]= EOS;
						}
					}

					/* <???> Problem/Bug: Falls man Makros wie !macro INC !include ... */
					/* verwendet, dann wird das nicht erkannt, da oben auf */
					/* zeile[0][0]==META_C getestet wird. */
					/* Ergebnis: !include wird dann nicht erkannt, die Prozentzahlen */
					/* stimmen im 2. Durchlauf nicht mehr. */
					
					if (zeile[0]!=EOS)
					{	/* New in r6pl15 [NHz] */

						/* Set node name for project file */

						/*if((strstr(zeile, "node")!=NULL) || (strstr(zeile, "heading")!=NULL))*/

							strcpy(current_node_name_sys, zeile);



						if (no_umlaute)
						{	umlaute2ascii(zeile);
						}
						auto_quote_chars(zeile, FALSE);
						replace_macros(zeile);
						replace_defines(zeile);

						c_divis(zeile);
						c_vars(zeile);
						c_tilde(zeile);		/* r5pl9 */
						c_styles(zeile);	/* r6pl2 */
						c_internal_index(zeile, FALSE);
					}
					
					/* Dies darf nicht mit in die obige Klammer! */
					token_reset();
					str2tok(zeile);

					if ( (bInsideDocument) && (token[0][0]!=EOS) )
					{	/* Kommandos, die nur im Hauptteil erlaubt sind */
						if (strcmp(token[0], "!node")==0 || strcmp(token[0], "!n")==0)
						{	add_node_to_toc(NODE_NORMAL, NODE_VISIBLE);
							bInsidePopup= FALSE;
						}	else
						if (strcmp(token[0], "!node*")==0 || strcmp(token[0], "!n*")==0)
						{	add_node_to_toc(NODE_NORMAL, NODE_INVISIBLE);
							bInsidePopup= FALSE;
						}	else
						if ( strcmp(token[0], "!subnode")==0 || strcmp(token[0], "!sn")==0)
						{	add_subnode_to_toc(NODE_NORMAL, NODE_VISIBLE);
							bInsidePopup= FALSE;
						}	else
						if ( strcmp(token[0], "!subnode*")==0 || strcmp(token[0], "!sn*")==0)
						{	add_subnode_to_toc(NODE_NORMAL, NODE_INVISIBLE);
							bInsidePopup= FALSE;
						}	else
						if ( strcmp(token[0], "!subsubnode")==0 || strcmp(token[0], "!ssn")==0)
						{	add_subsubnode_to_toc(NODE_NORMAL, NODE_VISIBLE);
							bInsidePopup= FALSE;
						}	else
						if ( strcmp(token[0], "!subsubnode*")==0 || strcmp(token[0], "!ssn*")==0)
						{	add_subsubnode_to_toc(NODE_NORMAL, NODE_INVISIBLE);
							bInsidePopup= FALSE;
						}	else
						if ( strcmp(token[0], "!subsubsubnode")==0 || strcmp(token[0], "!sssn")==0)
						{	add_subsubsubnode_to_toc(NODE_NORMAL, NODE_VISIBLE);
							bInsidePopup= FALSE;
						}	else
						if ( strcmp(token[0], "!subsubsubnode*")==0 || strcmp(token[0], "!sssn*")==0)
						{	add_subsubsubnode_to_toc(NODE_NORMAL, NODE_INVISIBLE);
							bInsidePopup= FALSE;
						}	else
						if (strcmp(token[0], "!pnode")==0 || strcmp(token[0], "!p")==0)
						{	add_node_to_toc(NODE_POPUP, NODE_VISIBLE);
							bInsidePopup= TRUE;
						}	else
						if (strcmp(token[0], "!pnode*")==0 || strcmp(token[0], "!p*")==0)
						{	add_node_to_toc(NODE_POPUP, NODE_INVISIBLE);
							bInsidePopup= TRUE;
						}	else
						if ( strcmp(token[0], "!psubnode")==0 || strcmp(token[0], "!ps")==0)
						{	add_subnode_to_toc(NODE_POPUP, NODE_VISIBLE);
							bInsidePopup= TRUE;
						}	else
						if ( strcmp(token[0], "!psubnode*")==0 || strcmp(token[0], "!ps*")==0)
						{	add_subnode_to_toc(NODE_POPUP, NODE_INVISIBLE);
							bInsidePopup= TRUE;
						}	else
						if ( strcmp(token[0], "!psubsubnode")==0 || strcmp(token[0], "!pss")==0)
						{	add_subsubnode_to_toc(NODE_POPUP, NODE_VISIBLE);
							bInsidePopup= TRUE;
						}	else
						if ( strcmp(token[0], "!psubsubnode*")==0 || strcmp(token[0], "!pss*")==0)
						{	add_subsubnode_to_toc(NODE_POPUP, NODE_INVISIBLE);
							bInsidePopup= TRUE;
						}	else
						if ( strcmp(token[0], "!psubsubsubnode")==0 || strcmp(token[0], "!psss")==0)
						{	add_subsubsubnode_to_toc(NODE_POPUP, NODE_VISIBLE);
							bInsidePopup= TRUE;
						}	else
						if ( strcmp(token[0], "!psubsubsubnode*")==0 || strcmp(token[0], "!psss*")==0)
						{	add_subsubsubnode_to_toc(NODE_POPUP, NODE_INVISIBLE);
							bInsidePopup= TRUE;
						}	else
						if ( strcmp(token[0], "!begin_node")==0 || strcmp(token[0], "!bn")==0)
						{	toc_begin_node(NODE_NORMAL, NODE_VISIBLE);
							bInsidePopup= FALSE;
						}	else
						if ( strcmp(token[0], "!begin_node*")==0 || strcmp(token[0], "!bn*")==0)
						{	toc_begin_node(NODE_NORMAL, NODE_INVISIBLE);
							bInsidePopup= FALSE;
						}	else
						if ( strcmp(token[0], "!begin_pnode")==0 || strcmp(token[0], "!bp")==0)
						{	toc_begin_node(NODE_POPUP, NODE_VISIBLE);
							bInsidePopup= TRUE;
						}	else
						if ( strcmp(token[0], "!begin_pnode*")==0 || strcmp(token[0], "!bp*")==0)
						{	toc_begin_node(NODE_POPUP, NODE_INVISIBLE);
							bInsidePopup= TRUE;
						}	else
						if ( strcmp(token[0], "!end_node")==0 || strcmp(token[0], "!en")==0)
						{	toc_end_node();
							bInsidePopup= FALSE;
						}	else

						/* New in r6pl15 [NHz] */
						if ( strcmp(token[0], "!heading")==0 || strcmp(token[0], "!h")==0)
						{	save_upr_entry_heading (1, sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine );
						}	else
						/* New in r6pl15 [NHz] */
						if ( strcmp(token[0], "!subheading")==0 || strcmp(token[0], "!sh")==0)
						{	save_upr_entry_heading (2, sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine );
						}	else
						/* New in r6pl15 [NHz] */
						if ( strcmp(token[0], "!subsubheading")==0 || strcmp(token[0], "!ssh")==0)
						{	save_upr_entry_heading (3, sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine );
						}	else
						/* New in r6pl15 [NHz] */
						if ( strcmp(token[0], "!subsubsubheading")==0 || strcmp(token[0], "!sssh")==0)
						{	save_upr_entry_heading (4, sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine );
						}	else
						if ( strcmp(token[0], "!alias")==0 || strcmp(token[0], "!a")==0)
						{	tokcpy2(tmp, 512);
							add_alias(tmp, bInsidePopup);
						}	else
						if ( strcmp(token[0], "!index")==0 || strcmp(token[0], "!x")==0)
						{	bCalledIndex= TRUE;
						}	else
						if ( strcmp(token[0], "!mapping")==0 )
						{	set_mapping();
						}	else
						if ( strcmp(token[0], "!win_helpid")==0 )
						{	set_helpid();
						}	else
						if ( strcmp(token[0], "!jumpid")==0 )	/* Alter Kommandoname */
						{	set_helpid();
						}	else
						if ( strcmp(token[0], "!html_img_suffix")==0 )
						{	c_html_img_suffix();
						}	else
						if ( strcmp(token[0], "!chapterimage")==0 )
						{	set_chapter_image();
						}	else
						if ( strcmp(token[0], "!chaptericon")==0 )
						{	set_chapter_icon();
						}	else
						if ( strcmp(token[0], "!chaptericon_active")==0 )
						{	set_chapter_icon_active();
						}	else
						if ( strcmp(token[0], "!chaptericon_text")==0 )
						{	set_chapter_icon_text();
						}	else
						if ( strcmp(token[0], "!ignore_subtoc")==0 )
						{	set_ignore_subtoc();
						}	else
						if ( strcmp(token[0], "!ignore_subsubtoc")==0 )
						{	set_ignore_subtoc();
						}	else
						if ( strcmp(token[0], "!ignore_subsubsubtoc")==0 )
						{	set_ignore_subtoc();
						}	else
						if ( strcmp(token[0], "!ignore_links")==0 )
						{	set_ignore_links();
						}	else
						if ( strcmp(token[0], "!ignore_index")==0 )
						{	set_ignore_index();
						}	else
						if ( strcmp(token[0], "!ignore_title")==0 )
						{	set_ignore_title();
						}	else
						if ( strcmp(token[0], "!ignore_headline")==0 )
						{	set_ignore_headline();
						}	else
						if ( strcmp(token[0], "!ignore_bottomline")==0 )
						{	set_ignore_bottomline();
						}	else
						if ( strcmp(token[0], "!ignore_raw_header")==0 )
						{	set_ignore_raw_header();
						}	else
						if ( strcmp(token[0], "!ignore_raw_footer")==0 )
						{	set_ignore_raw_footer();
						}	else
						if (strcmp(token[0], "!maketitle")==0)
						{	uses_maketitle= TRUE;
						}	else
						if (strcmp(token[0], "!tableofcontents")==0)
						{	uses_tableofcontents= TRUE;
						}	else
						if (strcmp(token[0], "!begin_appendix")==0)
						{	pflag[PASS1].inside_apx= TRUE;
						}	else
						if (strcmp(token[0], "!end_appendix")==0)
						{	/* pflag[PASS1].inside_apx= FALSE; */ /* 0.44 */
						}	else
						if (pass1_check_main_commands())
						{	zeile[0]= EOS;
						}	else
						if (pass1_check_everywhere_commands())
						{	zeile[0]= EOS;
						}
					}

					if ( (!bInsideDocument) && (token[0][0]!=EOS) )
					{	/* Kommandos, die nur im Vorspann erlaubt sind */
						if (strcmp(token[0], CMD_BEGIN_DOCUMENT)==0)
						{	bInsideDocument= TRUE;
						}	else
						if ( strcmp(token[0], "!hyphen")==0 )
						{	add_hyphen();
						}	else
						if (strcmp(token[0], "!docinfo")==0)	/* r6pl2 */
						{	if (set_docinfo())
							{	token[0][0]= EOS;
							}
						}	else
						/* New in r6pl15 [NHz] */
						if (strcmp(token[0], "!doclayout")==0)	/* r6pl15 [NHz] */
						{	if (set_doclayout())
							{	token[0][0]= EOS;
							}
						}	else
						if (pass1_check_preamble_commands())
						{	zeile[0]= EOS;
						}	else
						if (pass1_check_everywhere_commands())
						{	zeile[0]= EOS;
						}

					} /* !bInsideDocument */
	
					
					/* Kommandos, die ueberall erlaubt sind... */
					if ( token[0][0]!=EOS )
					{
#if 1
						if (strcmp(token[0], "!nop")==0)
						{	bNopDetected= !bNopDetected;
						}	else
#endif
						if ( strcmp(token[0], "!label")==0 || strcmp(token[0], "!l")==0)
						{	tokcpy2(tmp, 512);
							replace_udo_quotes(tmp);
							add_label(tmp, FALSE, bInsidePopup);
						}	else
						if ( strcmp(token[0], "!include")==0 )
						{	c_include();
						}	else
						if (strcmp(token[0], "!input")==0)
						{	c_input();
						}	else
						if ( strcmp(token[0], "!rinclude")==0 )
						{	c_include_raw();
						}	else
						if ( strcmp(token[0], "!vinclude")==0 )
						{	c_include_verbatim();
						}	else
						if ( strcmp(token[0], "!pinclude")==0 )
						{	c_include_preformatted();
						}	else
						if ( strcmp(token[0], "!sinclude")==0 )
						{	c_include_src();
						}	else
						if ( strcmp(token[0], "!cinclude")==0 )
						{	c_include_comment();
						}	else
						if ( strcmp(token[0], "!ldinclude")==0 )
						{	c_include_linedraw();
						}	else
						if ( strcmp(token[0], "!code")==0 )
						{	c_code();
						}	else
						if ( strcmp(token[0], "!universal_charset")==0 )
						{	c_universal_charset();
						}	else
						if ( strcmp(token[0], "!break")==0 )
						{	bBreakInside= TRUE;
						}	else
						if ( strcmp(token[0], "!error")==0 )
						{	c_error();
						}	else
						if ( strcmp(token[0], "!use_raw_header")==0 )
						{	set_raw_header_filename();
						}	else
						if ( strcmp(token[0], "!use_raw_footer")==0 )
						{	set_raw_footer_filename();
						}	else
						if (pass1_check_everywhere_commands())
						{	zeile[0]= EOS;
						}
						
					}
					
				}	/* if (zeile[0]==META_C) */

			}	/* if (!pflag[PASS1].ignore_line...) */

		}	/* if (zeile[0]!=EOS) */

#if 0
		PASS1_READ_NEXT_LINE:
#endif
		
		/* Das obige Label kann direkt angesprungen werden	*/
		/* und ueberspringt somit ueberfluessige Abfragen	*/

	}	/* while (fgets) */

	iFilesOpened--;
	myTextClose(file);
	strcpy(sCurrFileName, sFileNames[iFilesOpened]);

	token_reset();

	multitasking_interrupt();

	return (!bFatalErrorDetected);
}	/* pass1 */



/*	############################################################
	#
	# Eine Zeile einer verbatim-Umgebung ausgeben
	#
	############################################################	*/
LOCAL void output_verbatim_line ( char *zeile )
{
	char indent[128];
	size_t len;

	if (zeile[0]=='#')
	{	recode(zeile, iCharset);	/* r6pl2: sonst werden UDO-Kommentare in verbatim-Umgebungen */
		convert_sz(zeile);		/* r6pl2: ... nicht angepasst und falsch ausgegeben! */
	}

	strcpy_indent(indent);
	if (use_justification)
	{	indent2space(indent);
	}

	if (no_verbatim_umlaute)
	{	umlaute2ascii(zeile);
	}
				
	/* TABs in Leerzeichen umwandeln */
	if (strchr(zeile, '\t')!=NULL)
	{	tabs2spaces(zeile, bDocTabwidth);
	}
				
	/* Zeilen ggf. weiter einruecken */
	switch (desttype)
	{
		case TOMAN:
			strinsert(zeile, "     ");
			break;
		case TOSRC:
		case TOSRP:
			strinsert(zeile, "    ");
			break;
	}

	/* Zu lange Zeilen bemaengeln */
	switch(desttype)
	{	case TOASC:
		case TODRC:
		case TOMAN:
		case TOPCH:
		case TOSTG:
		case TOAMG:
		case TOTVH:
			len= strlen(indent)+ strlen(zeile);
			if ( len>zDocParwidth )
			{	warning_long_destline(outfile.full, outlines+1, (int) len);
				note_long_sourceline();
			}
			break;
	}

	switch(desttype)
	{	case TORTF:
			qreplace_all(indent, "\\qj", 3, "\\ql", 3);
			auto_quote_chars(zeile, TRUE);
			strcat(zeile, rtf_par);
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			qreplace_all(indent, "\\qj", 3, "\\ql", 3);
			auto_quote_chars(zeile, TRUE);
			qreplace_all(zeile, "\\{bmc ", 6, "\\{ bmc ", 7);
			qreplace_all(zeile, "\\{bmcwd ", 8, "\\{ bmcwd ", 9);
			auto_references(zeile, FALSE, "", 0, 0);
			strcat(zeile, rtf_par);
			break;
		case TOPCH:
			auto_quote_chars(zeile, TRUE);
			auto_references(zeile, FALSE, "", 0, 0);
			replace_placeholders(zeile);
			reset_placeholders();
			break;
		case TOTVH:
			if (indent[0]==EOS)
			{	strcpy(indent, " ");
			}
			auto_quote_chars(zeile, TRUE);
			auto_references(zeile, FALSE, "", 0, 0);
			break;
		case TOSTG:
		case TOAMG:
			qreplace_all(zeile, "@", 1, "@@", 2);
			break;
		case TOTEX:
		case TOPDL:
			indent[0]= EOS;
			break;
		case TOLYX:
			indent[0]= EOS;
			outln("\\layout LyX-Code");
			outln("");
			replace_all(zeile, "\\", "\\backslash"INDENT_S);
			if (zeile[0]==EOS)
			{	strcpy(zeile, "\n\\protected_separator\n");
			}
			else
			{	replace_all(zeile, " ", "\\protected_separator\n");
			}
			indent2space(zeile);
			break;
		case TOINF:
			indent[0]= EOS;
			auto_quote_chars(zeile, TRUE);
			break;
		case TOHTM:
		case TOMHH:
			indent[0]= EOS;
			auto_quote_chars(zeile, TRUE);
			auto_references(zeile, FALSE, "", 0, 0);
			break;
		case TOLDS:
			indent[0]= EOS;
			qreplace_all(zeile, "&", 1, "&ero;", 5);
			qreplace_all(zeile, "</", 2, "&etago;", 7);
			break;
		case TODRC:	/* <???> */
			break;
		case TOIPF:
			indent[0]= EOS;	/* <???> */
			auto_quote_chars(zeile, TRUE);
			auto_references(zeile, FALSE, "", 0, 0);
			break;
		case TOKPS:
			auto_quote_chars(zeile, TRUE);
			strinsert(indent, "(");
			strcat(zeile, ") show newline");
			break;
	}

	voutlnf("%s%s", indent, zeile);

}	/* output_verbatim_line */



/*	############################################################
	#
	# Eine Zeile einer linedraw-Umgebung ausgeben (nur RTF)
	#
	############################################################	*/
LOCAL void output_linedraw_line ( char *zeile )
{
	char indent[128];

	if (desttype!=TORTF)
	{	output_verbatim_line(zeile);
		return;
	}

	strcpy_indent(indent);

	/* TABs in Leerzeichen umwandeln */
	if (strchr(zeile, '\t')!=NULL)
	{	tabs2spaces(zeile, bDocTabwidth);
	}

	qreplace_all(indent, "\\qj", 3, "\\ql", 3);
	auto_quote_linedraw(zeile);
	voutlnf("%s%s%s", indent, zeile, rtf_par);

}	/* output_linedraw_line */


/*	############################################################
	#
	# Eine Zeile einer verbatim-Umgebung ausgeben
	#
	############################################################	*/
LOCAL void output_comment_line ( char *zeile )
{
	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
			voutlnf("<!-- %s -->", zeile);
			break;
		case TOLDS:	/* <???> */
			voutlnf("<!-- %s -->", zeile);
			break;
		case TOINF:
			voutlnf("@comment %s", zeile);
			break;
		case TOSTG:
			voutlnf("## %s", zeile);
			break;
		case TOAMG:
			voutlnf("@REM %s", zeile);
			break;
		case TOTEX:
		case TOPDL:
			voutlnf("%% %s", zeile);
			break;
		case TOSRC:
		case TOSRP:
			voutlnf("%s %s %s", sSrcRemOn, zeile, sSrcRemOff);
			break;
		case TODRC:
			voutlnf("%%%%* %s", zeile);
			break;
		case TOIPF:
			voutlnf(".* %s", zeile);
			break;
		case TOLYX:
			voutlnf("# %s", zeile);
			break;
		case TOWIN:	/* <???> */
		case TOWH4: /* <???> */
		case TOAQV:	/* <???> */
		case TORTF:	/* <???> */
		case TOPCH:	/* <???> */
		case TONRO:	/* <???> */
			break;
		case TOASC:
			/* <???> Hier noch use_comment abfragen */
			break;
		case TOKPS:
			voutlnf("%% %s", zeile);
			break;
	}

}	/* output_comment_line */


LOCAL void c_comment ( void )
{
	char s[512];

	tokcpy2(s, 512);
	output_comment_line(s);

}	/* c_comment */



/*	############################################################
	#
	# Spezielle Umgebungen fuer Pass 2 testen
	#
	############################################################	*/
LOCAL void pass2_check_environments ( char *zeile )
{
	char *found;
	
	/* ---Verbatim-Umgebung--- */
	if	( pflag[PASS2].env==ENV_NONE || pflag[PASS2].env==ENV_VERBATIM )
	{	if ((found=strstr(zeile, CMD_BEGIN_VERBATIM))!=NULL)
		{	if ( found[1]!=QUOTE_C )
			{	pflag[PASS2].env= ENV_VERBATIM;
				pflag[PASS2].env1st= TRUE;
				if (token_counter>0) token_output(TRUE);
				zeile[0]= EOS;
				output_begin_verbatim();
				return;
			}
		}	else
		if ( (found=strstr(zeile, CMD_END_VERBATIM))!=NULL )
		{	if ( found[1]!=QUOTE_C )
			{	if (pflag[PASS2].env==ENV_VERBATIM)
				{	pflag[PASS2].env= ENV_NONE;
					zeile[0]= EOS;
					output_end_verbatim();
					return;
				}
				else
				{	error_end_without_begin(CMD_END_VERBATIM, CMD_BEGIN_VERBATIM);
					zeile[0]= EOS;
					return;
				}
			}
		}
	}


	/* ---Sourcecode-Umgebung--- */
	if	( pflag[PASS2].env==ENV_NONE || pflag[PASS2].env==ENV_SOURCECODE )
	{	if ((found=strstr(zeile, CMD_BEGIN_SOURCECODE))!=NULL)
		{	if ( found[1]!=QUOTE_C )
			{	pflag[PASS2].env= ENV_SOURCECODE;
				pflag[PASS2].env1st= TRUE;
				if (token_counter>0) token_output(TRUE);
				zeile[0]= EOS;
				output_begin_sourcecode();
				return;
			}
		}	else
		if ( (found=strstr(zeile, CMD_END_SOURCECODE))!=NULL )
		{	if ( found[1]!=QUOTE_C )
			{	if (pflag[PASS2].env==ENV_SOURCECODE)
				{	pflag[PASS2].env= ENV_NONE;
					zeile[0]= EOS;
					output_end_sourcecode();
					return;
				}
				else
				{	error_end_without_begin(CMD_END_SOURCECODE, CMD_BEGIN_SOURCECODE);
					zeile[0]= EOS;
					return;
				}
			}
		}
	}
	
	/* ---Raw-Umgebung--- */
	if	( pflag[PASS2].env==ENV_NONE || pflag[PASS2].env==ENV_RAW )
	{	if ( (found=strstr(zeile, CMD_BEGIN_RAW))!=NULL )
		{	if ( found[1]!=QUOTE_C )
			{	pflag[PASS2].env= ENV_RAW;
				pflag[PASS2].env1st= TRUE;
				if (token_counter>0) token_output(TRUE);
				zeile[0]= EOS;
				return;
			}
		}	else
		if ( (found=strstr(zeile, CMD_END_RAW))!=NULL )
		{	if ( found[1]!=QUOTE_C )
			{	if (pflag[PASS2].env==ENV_RAW)
				{	pflag[PASS2].env= ENV_NONE;
					zeile[0]= EOS;
					outln("");
					return;
				}
				else
				{	error_end_without_begin(CMD_END_RAW, CMD_BEGIN_RAW);
					zeile[0]= EOS;
					return;
				}
			}
		}
	}

	/* ---Table-Umgebung--- */
	if	( pflag[PASS2].env==ENV_NONE || pflag[PASS2].env==ENV_TABLE )
	{
		if ( (found=strstr(zeile, CMD_BEGIN_TABLE))!=NULL )
		{	if ( found[1]!=QUOTE_C )
			{
				if (pflag[PASS2].env==ENV_TABLE)
				{	/* Es kann nur eine geben */
					error_table_inside_table();
					zeile[0]= EOS;
				}
				else
				{
					pflag[PASS2].env= ENV_TABLE;
					if (token_counter>0) token_output(TRUE);
					table_reset();
					table_get_header(zeile);
					zeile[0]= EOS;
				}
				return;
			}
		}	else
		if ( (found=strstr(zeile, CMD_END_TABLE))!=NULL )
		{	if ( found[1]!=QUOTE_C )
			{	if (pflag[PASS2].env==ENV_TABLE)
				{	pflag[PASS2].env= ENV_NONE;
					zeile[0]= EOS;
					table_output();
					outln("");
					return;
				}
				else
				{	error_end_without_begin(CMD_END_TABLE, CMD_BEGIN_TABLE);
					zeile[0]= EOS;
					return;
				}
			}
		}
	}

	/* ---Comment-Umgebung--- r6pl2 */
	if	( pflag[PASS2].env==ENV_NONE || pflag[PASS2].env==ENV_COMMENT )
	{	if ((found=strstr(zeile, CMD_BEGIN_COMMENT))!=NULL)
		{	if ( found[1]!=QUOTE_C )
			{	pflag[PASS2].env= ENV_COMMENT;
				pflag[PASS2].env1st= TRUE;
				if (token_counter>0) token_output(TRUE);
				zeile[0]= EOS;
				output_begin_comment();
				return;
			}
		}	else
		if ( (found=strstr(zeile, CMD_END_COMMENT))!=NULL )
		{	if ( found[1]!=QUOTE_C )
			{	if (pflag[PASS2].env==ENV_COMMENT)
				{	pflag[PASS2].env= ENV_NONE;
					zeile[0]= EOS;
					output_end_comment();
					return;
				}
				else
				{	error_end_without_begin(CMD_END_COMMENT, CMD_BEGIN_COMMENT);
					zeile[0]= EOS;
					return;
				}
			}
		}
	}

	/* ---Linedraw-Umgebung--- */
	if	( pflag[PASS2].env==ENV_NONE || pflag[PASS2].env==ENV_LINEDRAW )
	{	if ((found=strstr(zeile, CMD_BEGIN_LINEDRAW))!=NULL)
		{	if ( found[1]!=QUOTE_C )
			{	pflag[PASS2].env= ENV_LINEDRAW;
				pflag[PASS2].env1st= TRUE;
				if (token_counter>0) token_output(TRUE);
				zeile[0]= EOS;
				output_begin_linedraw();
				return;
			}
		}	else
		if ( (found=strstr(zeile, CMD_END_LINEDRAW))!=NULL )
		{	if ( found[1]!=QUOTE_C )
			{	if (pflag[PASS2].env==ENV_LINEDRAW)
				{	pflag[PASS2].env= ENV_NONE;
					zeile[0]= EOS;
					output_end_linedraw();
					return;
				}
				else
				{	error_end_without_begin(CMD_END_LINEDRAW, CMD_BEGIN_LINEDRAW);
					zeile[0]= EOS;
					return;
				}
			}
		}
	}


	/* ---Preformatted-Umgebung--- */
	if	( pflag[PASS2].env==ENV_NONE || pflag[PASS2].env==ENV_PREFORMATTED )
	{	if ((found=strstr(zeile, CMD_BEGIN_PREFORMATTED))!=NULL)
		{	if ( found[1]!=QUOTE_C )
			{	pflag[PASS2].env= ENV_PREFORMATTED;
				pflag[PASS2].env1st= TRUE;
				if (token_counter>0) token_output(TRUE);
				zeile[0]= EOS;
				output_begin_verbatim();
				return;
			}
		}	else
		if ( (found=strstr(zeile, CMD_END_PREFORMATTED))!=NULL )
		{	if ( found[1]!=QUOTE_C )
			{	if (pflag[PASS2].env==ENV_PREFORMATTED)
				{	pflag[PASS2].env= ENV_NONE;
					zeile[0]= EOS;
					output_end_verbatim();
					return;
				}
				else
				{	error_end_without_begin(CMD_END_PREFORMATTED, CMD_BEGIN_PREFORMATTED);
					zeile[0]= EOS;
					return;
				}
			}
		}
	}


}	/* pass2_check_environments */



/*	############################################################
	#
	# Zeilen ausgeben/bearbeiten, falls eine spezielle Umgebung
	# in Pass 2 aktiv ist
	#
	############################################################	*/
LOCAL void pass2_check_env_output ( char *zeile )
{
	switch (pflag[PASS2].env)
	{
		case ENV_VERBATIM:		/* ---- Verbatim-Ausgabe ---- */
		case ENV_PREFORMATTED:	/* ---- Preformatted-Ausgabe ---- */
			if (!pflag[PASS2].env1st)
			{	output_verbatim_line(zeile);
			}
			break;
		
		case ENV_LINEDRAW:		/* ---- Linedraw-Ausgabe ---- */
			if (!pflag[PASS2].env1st)
			{	output_linedraw_line(zeile);
			}
			break;

		case ENV_RAW:			/* ---- Raw-Ausgabe ---- */
			if (!pflag[PASS2].env1st)
			{	outln(zeile);
			}
			break;

		case ENV_SOURCECODE:	/* ---- Sourcecode-Ausgabe ---- */
			if (!pflag[PASS2].env1st)
			{
				if (desttype==TOSRC || desttype==TOSRP)
				{	/* TABs in Leerzeichen umwandeln */
					if (strchr(zeile, '\t')!=NULL)
					{	tabs2spaces(zeile, bDocTabwidth);
					}
					outln(zeile);
				}
				else
				{	if (!no_sourcecode)
					{	output_verbatim_line(zeile);
					}
				}
			}
			break;

		case ENV_COMMENT:		/* ---- Comment-Ausgabe ---- */
			if (!pflag[PASS2].env1st)
			{	/* Nicht alle Formate ermoeglichen Kommentare */
				output_comment_line(zeile);
			}
			break;

		case ENV_TABLE:			/* ---- Tabelle erweitern ---- */
			table_add_line(zeile);
			break;

	}	/* switch */

	pflag[PASS2].env1st= FALSE;
	
}	/* pass2_check_env_output */



/*	############################################################
	#
	#
	# Zeilen einlesen und umwandeln (Pass 2)
	#
	#
	############################################################	*/
LOCAL BOOLEAN pass2 (char *datei)
{
	MYTEXTFILE 	*file;
	char	zeile[LINELEN];
	char	tmp_datei[256], old_datei[256];
	int		i;
	size_t	len;

	if (iFilesOpened>=MAXFILECOUNTER)
	{	error_too_many_files();
		return FALSE;
	}

	strcpy(old_datei, datei);
	strcpy(tmp_datei, datei);

	build_include_filename(tmp_datei, ".ui");

	file = myTextOpen(tmp_datei);
	
	if (file == NULL)
	{	strcpy(tmp_datei, old_datei);
		file = myTextOpen(tmp_datei);

		if (file == NULL)
		{	error_open_pass2(tmp_datei);
			bErrorDetected= TRUE;
			return FALSE;
		}
	}

	show_status_percent(lPass1Lines, lPass2Lines);
	if (bVerbose)
	{	show_status_file_2(tmp_datei);
	}
	
	iFilesOpened++;
	uiFileLines[iFilesOpened]= 0;
	strcpy(sFileNames[iFilesOpened], tmp_datei);

	strcpy(sCurrFileName, tmp_datei);
	uiCurrFileLine= 0;

	if (bUseTreefile)
	{	if (bTreeopened)
		{	for (i=0; i<iFilesOpened; i++)
			{	fprintf(fTreefile, "|----");
			}
			fprintf(fTreefile, "%s\n", tmp_datei);
		}
	}

	save_upr_entry_infile(tmp_datei);

	while ( (!bBreakHappened) && (!bBreakInside) && (!bFatalErrorDetected) && (myTextGetline(zeile, LINELEN, file)) )
	{
		uiFileLines[iFilesOpened]++;
		uiCurrFileLine= uiFileLines[iFilesOpened];
		lPass2Lines++;
		show_status_percent(lPass1Lines, lPass2Lines);

		if ( break_action() )
		{	iFilesOpened--;
			myTextClose(file);
			strcpy(sCurrFileName, sFileNames[iFilesOpened]);
			return FALSE;
		}
		
		/* LF, CR und LEERZEICHEN (<=!!!!) etc. am Ende entfernen */
		len= strlen(zeile);
		while (  (len>0) && (((UCHAR) zeile[len-1])<=32) )
		{	zeile[len-1]= EOS;
			len--;
		}

		if ( (zeile[0]!=EOS) && (zeile[0]!='#') )
		{	recode(zeile, iCharset);
			convert_sz(zeile);
		}

		if	( pflag[PASS2].env==ENV_NONE )
		{	/* Befehle wie !raw [tex] bearbeiten */
			if (pflag[PASS2].ignore_line==0)	/* r5pl17 */
			{	c_check_raw(zeile);
			}
		}
		
		if	( (zeile[0]!='#') && (zeile[0]!=EOS) && (pflag[PASS2].env==ENV_NONE) )
		{	pass_check_if(zeile, PASS2);
		}
		
#if 0
		if (pflag[PASS2].ignore_line>0)
		{	goto AFTER_IGNORED;
		}
#endif

		/* Spezielle (verbatim, raw, table sourcecode) Umgebungen testen. */
		/* Gesucht wird nur nach !begin... bzw !end... */
		if ( zeile[0]!='#' && pflag[PASS2].ignore_line==0)
		{	pass2_check_environments(zeile);
		}

		/* Ausgabe/Bearbeitung der aktuellen Zeile, falls eine */
		/* spezielle Umgebung aktiv ist */
		if (pflag[PASS2].ignore_line==0)
		{	pass2_check_env_output(zeile);
		}
		
		/* Keine spezielle Umgebung aktiv, also Zeile auswerten und */
		/* beim Auftreten einer Leerzeile den Absatz ausgeben */
		if	(	(pflag[PASS2].ignore_line==0)
			&&	(pflag[PASS2].env==ENV_NONE)
			)
		{	if ( zeile[0]!=EOS )
			{	if (zeile[0]!='#')
				{	del_whitespaces(zeile);
					if (no_umlaute) umlaute2ascii(zeile);
					auto_quote_chars(zeile, FALSE);

					c_commands_inside(zeile, TRUE);

					replace_macros(zeile);
					c_divis(zeile);
					c_vars(zeile);
					c_tilde(zeile);
					c_styles(zeile);

					c_commands_inside(zeile, FALSE);

					replace_defines(zeile);

					tokenize(zeile);
				}
			}
			else
			{	/* Leerzeile */
				if (token_counter>0)
				{	token_output(TRUE);
				}
			}
		}
		
	}	/* while (fgets) */

	if (token_counter>0)
	{	token_output(TRUE);
	}

	if (!bNoLogfile)
	{	if (!b1stQuote)
		{	error_odd_dblquotes();
		}
		if (!b1stApost)
		{	error_odd_quotes();
		}
	}
		
	iFilesOpened--;
	strcpy(sCurrFileName, sFileNames[iFilesOpened]);
	myTextClose(file);

	multitasking_interrupt();

	return (!bFatalErrorDetected);
}	/*pass2*/


/*	############################################################
	# Eintraege fuer das Projectfile anlegen
	############################################################	*/
GLOBAL void save_upr_entry_infile ( const char *filename )
{
	if (bUseUPRfile && bUPRopened)	/*r6pl12*/
	{	fprintf(fUPRfile, "infile\t%d\t%s\n", iFilesOpened, filename);
	}
}

GLOBAL void save_upr_entry_outfile ( const char *filename )
{
	if (bUseUPRfile && bUPRopened)	/*r6pl12*/
	{	fprintf(fUPRfile, "outfile\t%s\n", filename);
	}
}

GLOBAL void save_upr_entry_image ( const char *filename )
{
	if (bUseUPRfile && bUPRopened)	/*r6pl12*/
	{	fprintf(fUPRfile, "image\t%s\n", filename);
	}
}

/* Changed in r6pl15 [NHz] */

/* Extra parameter 'line' */

GLOBAL void save_upr_entry_node ( const int level, const char *filename, const char *title, const long line )
{
	if (bUseUPRfile && bUPRopened)	/*r6pl12*/
	{	fprintf(fUPRfile, "node\t%d\t%s\t%ld\t%s\n", level, filename, line, title);
	}
}

/* New in r6pl15 [NHz] */

GLOBAL void save_upr_entry_heading ( const int level, const char *filename, const char *title, const long line )
{
	if (bUseUPRfile && bUPRopened)	/*r6pl12*/
	{	fprintf(fUPRfile, "heading\t%d\t%s\t%ld\t%s\n", level, filename, line, title);
	}
}

/* New in r6pl15 [NHz] */

GLOBAL void save_upr_entry_alias ( const char *filename, const char *title, const long line )
{
	if (bUseUPRfile && bUPRopened)	/*r6pl12*/
	{	fprintf(fUPRfile, "alias\t%s\t%ld\t%s\n", filename, line, title);
	}
}

/* New in r6pl15 [NHz] */

GLOBAL void save_upr_entry_label ( const char *filename, const char *title, const long line )
{
	if (bUseUPRfile && bUPRopened)	/*r6pl12*/
	{	fprintf(fUPRfile, "label\t%s\t%ld\t%s\n", filename, line, title);
	}
}

/* New in r6pl15 [NHz] */

GLOBAL void save_upr_entry_index ( const int level, const char *filename, const char *title, const long line )
{
	if (bUseUPRfile && bUPRopened)	/*r6pl12*/
	{	fprintf(fUPRfile, "index\t%d\t%s\t%ld\t%s\n", level, filename, line, title);
	}
}

/*	############################################################
	# Commandofile fuer Pure-C-Helpcompiler anlegen
	############################################################	*/
LOCAL void save_pchelp_commandfile ( void )
{
	FILE	*cmdfile;

	if (bTestmode)
	{	return;
	}

	cmdfile= myFwopen(sCmdfull, TOASC);
	
	if (!cmdfile)
	{	return;
	}

	save_upr_entry_outfile(sCmdfull);

	fprintf(cmdfile, "-V\n\n");
	fprintf(cmdfile, "%s.HLP\n\n", outfile.name);
	fprintf(cmdfile, "%s.SCR\n", outfile.name);
	
	fclose(cmdfile);
	bCmdSaved= TRUE;

}	/* save_pchelp_commandfile */


/*	############################################################
	# Projektdatei fuer WinHelpcompiler anlegen
	############################################################	*/
LOCAL void save_winhelp_project ( void )
{
	FILE	*hpjfile;
	char	n[512], hlp_name[256], bc[128];

	if (bTestmode)
	{	return;
	}

	hpjfile= myFwopen(sHpjfull, FTHPJ);
	
	if (!hpjfile)
	{	return;
	}

	save_upr_entry_outfile(sHpjfull);

	if (desttype==TOAQV)
	{	strcpy(hlp_name, "qchPath");
	}
	else
	{	sprintf(hlp_name, "`%s.hlp'", outfile.name);
	}

	fprintf(hpjfile, "[OPTIONS]\n");
	strcpy(n, titleprogram);
	del_right_spaces(n);
	win2sys(n);
	if (desttype==TOWIN && iCharset!=CODE_437) 
	{	ansi2dos(n);
	}
	qdelete_all(n, "\\~", 2);
	qdelete_all(n, "~", 1);
	
	/* Title-Option darf maximal 50 Zeichen lang sein */
	if (strlen(n)>50)
	{	n[50]= EOS;
	}

	if (n[0]!=EOS)
	{	fprintf(hpjfile, "Title=%s\n", n);
	}
	
	if (titdat.author!=NULL)	/* Pl12 */
	{	strcpy(n, titdat.author);
		win2sys(n);
		if (desttype==TOWIN && iCharset!=CODE_437)
		{	ansi2dos(n);
		}
		qdelete_all(n, "\\~", 2);
		qdelete_all(n, "~", 1);
		fprintf(hpjfile, "Copyright=(c) by %s\n", n);
	}
	
	fprintf(hpjfile, "ErrorLog= %s.err\n", outfile.name);
	
	/* Weitere Optionen einbauen. Versteht QuickView die?	*/
	fprintf(hpjfile, "Warning=3\n");	
	fprintf(hpjfile, "Report=TRUE\n");

	if (bDocHighCompression)
	{	fprintf(hpjfile, "Compress=HIGH\n");
	}
	if (bDocMediumCompression)
	{	fprintf(hpjfile, "Compress=MEDIUM\n");
	}


	fprintf(hpjfile, "\n[CONFIG]\n");

	if (!no_buttons)	/* r6pl7 */
	{
		if (get_toc_counter() > 1 ||
			(get_toc_counter() > 0 && called_tableofcontents))
		{
			if (desttype==TOAQV)
			{	fprintf(hpjfile, "Std20Menus()\n");		/* Defaultmenuezeile anzeigen */
				fprintf(hpjfile, "Std20Buttons()\n");	/* Defaultbuttons anzeigen */
			}
			else
			{	fprintf(hpjfile, "BrowseButtons()\n");	/* << und >> anzeigen */
			}
	
			if (desttype==TOAQV)
			{	sprintf(n, "CreateButton(\"BTN_UP\", \"%s\", \"JumpID(%s, `%s')\")",
					"&Up", hlp_name, WIN_TITLE_NODE_NAME);	/* immer "Up" bei QuickView */
				fprintf(hpjfile, "%s\n", n);
			}
			else
			{	sprintf(n, "CreateButton(\"BTN_UP\", \"%s\", \"JumpID(%s, `%s')\")",
					lang.up, hlp_name, WIN_TITLE_NODE_NAME);
				fprintf(hpjfile, "%s\n", n);
#if 0
				/* WinHelp: Knopf zum Beenden einbauen */
				sprintf(n, "CreateButton(\"BTN_EXIT\", \"%s\", \"Exit()\")",
					lang.exit);
				fprintf(hpjfile, "%s\n", n);
#endif
			}

			if ( called_tableofcontents )
			{	node2NrWinhelp(bc, 0);
				sprintf(n, "ChangeButtonBinding(\"BTN_CONTENTS\", \"JumpID(%s, `%s')\")",
					hlp_name, bc);
				fprintf(hpjfile, "%s\n", n);
			}
		}
				
		if (use_about_udo)
		{	/*r6pl5: Button fr UDO einbauen */
			sprintf(n, "CreateButton(\"BTN_UDO\", \"UDO%s\", \"JumpID(%s, `%s')\")",
				UDO_REL, hlp_name, WIN_UDO_NODE_NAME);
			fprintf(hpjfile, "%s\n", n);

			if (desttype==TOAQV)	/* AQV kann kein zweites Fenster */
			{	sprintf(n, "AppendItem(\"mnu_help\", \"item_udoinfo\", \"&UDO%s...\", \"JumpID(%s, `%s')\")",
					UDO_REL, hlp_name, WIN_UDO_NODE_NAME);
				fprintf(hpjfile, "%s\n", n);
			}
			else
			{	sprintf(n, "AppendItem(\"mnu_help\", \"item_udoinfo\", \"&UDO%s...\", \"JumpID(`%s.hlp>win1', `%s')\")",
					UDO_REL, outfile.name, WIN_UDO_NODE_NAME);
				fprintf(hpjfile, "%s\n", n);
			}
		}
	}
	
	fprintf(hpjfile, "\n[WINDOWS]\n");
	fprintf(hpjfile, "main=,(20,20,708,960)%s\n", sDocBackColor);
	fprintf(hpjfile, "win1=\"UDO%s\",(200,200,800,800)%s\n", UDO_REL, sDocBackColor);
	
	fprintf(hpjfile, "\n[FILES]\n");
	fprintf(hpjfile, "%s.rtf\n", outfile.name);

	if (bUseIdMapFileC)
	{
		fprintf(hpjfile, "\n[MAP]\n");
		fprintf(hpjfile, "#include <%s.hpc>\n", outfile.name);
	}
	
	fclose(hpjfile);
	
	bHpjSaved= TRUE;

}	/* save_winhelp_project */


LOCAL void save_winhelp4_project ( void )
{
	FILE	*hpjfile;
	char	n[512], hlp_name[256];

	if (bTestmode)
	{	return;
	}

	hpjfile= myFwopen(sHpjfull, FTHPJ);
	
	if (!hpjfile)
	{	return;
	}

	save_upr_entry_outfile(sHpjfull);

	sprintf(hlp_name, "`%s.hlp'", outfile.name);


	fprintf(hpjfile, "; This file is maintained by UDO. Do not modify this file directly.\n\n");
	fprintf(hpjfile, "[OPTIONS]\n");
	fprintf(hpjfile, "HCW=0\n");
	fprintf(hpjfile, "HLP=.\\%s.hlp\n", outfile.name);
	fprintf(hpjfile, "CNT=.\\%s.cnt\n", outfile.name);
	fprintf(hpjfile, "%s\n", lang.lcid);
	strcpy(n, titleprogram);
	del_right_spaces(n);
	win2sys(n);
	qdelete_all(n, "\\~", 2);
	qdelete_all(n, "~", 1);
	
	if (n[0]!=EOS)
	{	fprintf(hpjfile, "TITLE=%s\n", n);
	}
	
	if (titdat.author!=NULL)	/* Pl12 */
	{	strcpy(n, titdat.author);
		win2sys(n);
		qdelete_all(n, "\\~", 2);
		qdelete_all(n, "~", 1);
		fprintf(hpjfile, "COPYRIGHT=(c) by %s\n", n);
	}
	
	fprintf(hpjfile, "ERRORLOG= %s.err\n", outfile.name);
	fprintf(hpjfile, "REPORT=TRUE\n");

	if (bDocHighCompression)
	{	fprintf(hpjfile, "COMPRESS=12 Hall Zeck\n");
	}
	if (bDocMediumCompression)
	{	fprintf(hpjfile, "COMPRESS=8 Zeck\n");
	}


	fprintf(hpjfile, "\n[CONFIG]\n");

	if (!no_buttons)	/* r6pl7 */
	{
		if (get_toc_counter() > 1 ||
			(get_toc_counter() > 0 && called_tableofcontents))
		{
			fprintf(hpjfile, "BrowseButtons()\n");	/* << und >> anzeigen */

			sprintf(n, "CreateButton(\"BTN_UP\", \"%s\", \"JumpID(%s, `%s')\")",
				lang.up, hlp_name, WIN_TITLE_NODE_NAME);
			fprintf(hpjfile, "%s\n", n);
		}
			
		if (use_about_udo)
		{	/*r6pl5: Button fr UDO einbauen */
			sprintf(n, "CreateButton(\"BTN_UDO\", \"UDO%s\", \"JumpID(`%s.hlp>win1', `%s')\")",
				UDO_REL, outfile.name, WIN_UDO_NODE_NAME);
			fprintf(hpjfile, "%s\n", n);

			sprintf(n, "AppendItem(\"mnu_help\", \"item_udoinfo\", \"&UDO%s...\", \"JumpID(`%s.hlp>win1', `%s')\")",
				UDO_REL, outfile.name, WIN_UDO_NODE_NAME);
			fprintf(hpjfile, "%s\n", n);
		}
#if 0	/* Damit beim Klick auf Inhalt die Auswahlbox kommt */
		if ( called_tableofcontents )
		{	node2NrWinhelp(bc, 0);
			sprintf(n, "ChangeButtonBinding(\"BTN_CONTENTS\", \"JumpID(%s, `%s')\")",
				hlp_name, bc);
			fprintf(hpjfile, "%s\n", n);
		}
#endif
	}
	
	fprintf(hpjfile, "\n[WINDOWS]\n");
	fprintf(hpjfile, "main=\"\",(20,20,540,880),0%s\n", sDocBackColor);
	fprintf(hpjfile, "win1=\"UDO%s\",(573,71,437,462),4,(r15204351),(r15204351),1\n", UDO_REL);
	
	fprintf(hpjfile, "\n[FILES]\n");
	fprintf(hpjfile, "%s.rtf\n", outfile.name);

	if (bUseIdMapFileC)
	{
		fprintf(hpjfile, "\n[MAP]\n");
		fprintf(hpjfile, "#include <%s.hpc>\n", outfile.name);
	}
	
	fclose(hpjfile);
	
	bHpjSaved= TRUE;

}	/* save_winhelp4_project */



/*	############################################################
	# Projektdatei fuer HTML-Help anlegen
	############################################################	*/
LOCAL void save_htmlhelp_project ( void )
{
	FILE	*hhpfile;
	char	sTitle[1024];

	if (bTestmode)
	{	return;
	}

	hhpfile= myFwopen(sHhpfull, FTHHP);
	
	if (!hhpfile)
	{	return;
	}

	save_upr_entry_outfile(sHhpfull);

	fprintf(hhpfile, "[OPTIONS]\n");
	/* Windows-Umlaute benutzen, also nicht "titleprogram"! */
	strcpy(sTitle, titleprogram);
	html2sys(sTitle);
	fprintf(hhpfile, "Title=%s\n", sTitle);
	fprintf(hhpfile, "Compatibility=1.0\n");
	fprintf(hhpfile, "Compiled file=%s.chm\n", old_outfile.name);
	fprintf(hhpfile, "Error log file=%s.log\n", old_outfile.name);
	if (bHhcSaved)
		fprintf(hhpfile, "Contents file=%s.hhc\n", old_outfile.name);
	if (bHhkSaved)
	{	fprintf(hhpfile, "Index file=%s.hhk\n", old_outfile.name);
	}
	fprintf(hhpfile, "Default topic=%s%s\n", old_outfile.name, outfile.suff);
	fprintf(hhpfile, "Display compile progress=Yes\n");
	fprintf(hhpfile, "Flat=Yes\n");
	fprintf(hhpfile, "Full-text search=Yes\n");
	fprintf(hhpfile, "Auto Index=Yes\n");
	fprintf(hhpfile, "Language=");
	switch(destlang)
	{
		case TOGER:	fprintf(hhpfile, "0x407\n");	break;
		case TOENG:	fprintf(hhpfile, "0x409\n");	break;
		case TOFRA:	fprintf(hhpfile, "0x40c\n");	break;
		case TOITA:	fprintf(hhpfile, "0x410\n");	break;
		case TOSPA:	fprintf(hhpfile, "0xc0a\n");	break;
		case TOSWE:	fprintf(hhpfile, "0x41d\n");	break;
		case TOPOR:	fprintf(hhpfile, "0x816\n");	break;
		/* case TODUT:	fprintf(hhpfile, "0x41d\n");	break; */
		case TODAN:	fprintf(hhpfile, "0x406\n");	break;
		case TONOR:	fprintf(hhpfile, "0x414\n");	break;
		case TOFIN:	fprintf(hhpfile, "0x40b\n");	break;
	}
	fprintf(hhpfile, "\n");
	fprintf(hhpfile, "[FILES]\n");
	fprintf(hhpfile, "%s%s\n", old_outfile.name, outfile.suff);
	
	fclose(hhpfile);
	
	bHhpSaved= TRUE;

}	/* save_htmlhelp_project */



/*	############################################################
	#
	# wichtige formatabhaengige Konvertierung-Flags setzen
	#
	############################################################	*/
LOCAL void set_format_flags ( void )
{
	/*	Bei manchen Formaten ist es fuer die Laengenberechnung	*/
	/*	einer Zeile enorm wichtig, die Laenge ohne UDO-			*/
	/*	Spezialitaeten zu kennen (STG, PCH, ASC...)				*/
	/*	Bei manchen ist es hingegen wurscht, wie lang eine		*/
	/*	Zeile wird (RTF, HTML, WinHelp, ...)					*/
	format_needs_exact_toklen= FALSE;

	/*	Bei den Formaten, bei denen referenziert wird und bei	*/
	/*	denen die Laenge einer Ausgabezeile egal ist, sollte	*/
	/*	erst dann referenziert werden, wenn der ganze Absatz	*/
	/*	moeglichst in einer Zeile enthalten ist, damit nicht	*/
	/*	durch einen vorzeitigen Umbruch Links verloren gehen.	*/
	format_uses_output_buffer= FALSE;


	/*	Die Kommandos einiger Formate muessen vor der Veraen-	*/
	/*	derung durch die Referenzierung geschuetzt werden.		*/
	/*	z.B. WinHelp und HTML. Dort waere es fatal, wuerde UDO	*/
	/*	\li, \footnote oder dergleichen referenzieren!			*/
	format_protect_commands= FALSE;
	
	switch (desttype)
	{
		case TOASC:
		case TODRC:
		case TOSRC:
		case TOSRP:
		case TOKPS:
			format_needs_exact_toklen= TRUE;
			break;
		case TOHTM:
		case TOMHH:
			format_uses_output_buffer= TRUE;
			format_protect_commands= TRUE;
			break;
		case TOHPH:
			format_uses_output_buffer= TRUE;
			format_protect_commands= TRUE;
			break;
		case TOIPF:
			format_protect_commands= TRUE;
			break;
		case TOINF:	/* <???> */
			break;
		case TOLDS:
			format_uses_output_buffer= TRUE;
			format_protect_commands= TRUE;
			break;
		case TOMAN:
		case TONRO:
			format_needs_exact_toklen= TRUE;
			break;
		case TOPCH:
			format_needs_exact_toklen= TRUE;
			break;
		case TORTF:
			break;
		case TOSTG:
		case TOAMG:
			format_needs_exact_toklen= TRUE;
			break;
		case TOTEX:
		case TOPDL:
		case TOLYX:
			break;
		case TOTVH:
			format_needs_exact_toklen= TRUE;
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			format_uses_output_buffer= TRUE;
			format_protect_commands= TRUE;
			break;
	}

	/*	Wenn ein Format den Puffer benoetigt, muss das	*/
	/*	toklen-Flag unbedingt FALSE sein, da toklen()	*/
	/*	sonst Speicherbereiche ueberschreibt!!!			*/
	
	if (format_uses_output_buffer)
	{	format_needs_exact_toklen= FALSE;
	}

}	/* set_format_flags */



/*	############################################################
	#
	#
	# Hauptroutine
	#
	#
	############################################################	*/
LOCAL void show_udo_intro ( void )
{
	show_status_info("");
	sprintf(sInfMsg, "This is UDO Release %s.%s Patchlevel %s for %s", UDO_REL, UDO_SUBVER, UDO_PL, UDO_OS);
	show_status_loginfo(sInfMsg);
	show_status_loginfo("Copyright (c) 1995-2001 by Dirk Hagedorn.");
	sprintf(sInfMsg, "UDO is Open Source (see %s for further information).", UDO_URL);
	show_status_loginfo(sInfMsg);
	show_status_loginfo("");

}	/* show_udo_intro */

LOCAL int call_dummy ( void )
{
	int i=42;

	return i;
}

GLOBAL BOOLEAN udo (char *datei)
{
	BOOLEAN ret= FALSE;
	int		i, val;
	FILE	*file;
	char	tmp[512];

	get_timestr(timer_start);

	init_modules();
	set_format_flags();

	bFatalErrorDetected= FALSE;
	bErrorDetected= FALSE;
	bBreakHappened= FALSE;
	bBreakInside= FALSE;
	
	bOutOpened= FALSE;
	outlines= 0;

	fLogfile= stderr;	bLogopened= FALSE;
	fHypfile= stderr;	bHypopened= FALSE;	bHypSaved= FALSE;	bHypfailed= FALSE;	hyplist= NULL;
	fIdxfile= stderr;	bIdxopened= FALSE;	bIdxSaved= FALSE;	bIdxfailed= FALSE;	idxlist= NULL;
	fTreefile= stderr;	bTreeopened= FALSE;	bTreeSaved= FALSE;
	fUPRfile= stderr;	bUPRopened= FALSE;	bUPRSaved= FALSE;

	/* Erstmal testen, ob die Datei vorhanden ist, damit nicht unnoetig	*/
	/* Dateien angelegt werden.	 0.47									*/

	strcpy(tmp, datei);

	build_include_filename(tmp, ".ui");

	file = fopen(tmp, "r");
	if (!file)
	{	error_open_infile(tmp);
		return FALSE;
	}
	fclose(file);
	

	if (!bNoLogfile)
	{	
		if ( outfile.full[0]!=EOS )
		{	if ( sLogfull[0]==EOS )
			{	logfile_adjust();
			}
			
			fLogfile= myFwopen(sLogfull, TOASC);
			if (fLogfile == NULL)
			{	fLogfile= stderr;
				warning_err_logfile();
				bErrorDetected= TRUE;
				return FALSE;
			}
			bLogopened= TRUE;
			save_upr_entry_outfile(sLogfull);
		}
	}



	if (bUseTreefile)
	{	if ( outfile.full[0]!=EOS )
		{	if (sTreefull[0]!=EOS)			
			{	fTreefile= myFwopen(sTreefull, TOASC);
				if (fTreefile == NULL)
				{	fTreefile= stderr;
					warning_err_treefile();
					bErrorDetected= TRUE;
					return FALSE;
				}
				bTreeopened= TRUE;
				save_upr_entry_outfile(sTreefull);
			}
		}
	}

	if (bUseUPRfile)
	{	if ( outfile.full[0]!=EOS )
		{	if (sUPRfull[0]!=EOS)			
			{	fUPRfile= myFwopen(sUPRfull, TOASC);
				if (fUPRfile == NULL)
				{	fUPRfile= stderr;
					warning_err_uprfile();
					bErrorDetected= TRUE;
					return FALSE;
				}
				bUPRopened= TRUE;
				save_upr_entry_outfile(sUPRfull);
			}
		}
	}

	if ( outfile.full[0]!=EOS )
	{
		if ( (strcmp(outfile.full, "~")==0) || (strcmp(outfile.full, "!")==0) )
		{	dest_adjust();
		}
		
		if (!bTestmode)
		{
			if (strcmp(outfile.full, infile.full)==0)	/* 0.48 */
			{	error_infile_outfile(outfile.full);
				bErrorDetected= TRUE;
				if (bLogopened)		fclose(fLogfile);
				if (bHypopened)		fclose(fHypfile);
				if (bIdxopened)		fclose(fIdxfile);
				if (bTreeopened)	fclose(fTreefile);
				if (bUPRopened)		fclose(fUPRfile);
				return FALSE;
			}

			outfile.file= myFwopen(outfile.full, desttype);
			if (outfile.file == NULL)
			{	error_open_outfile(outfile.full);
				warning_err_destination();
				bErrorDetected= TRUE;
				if (bLogopened)		fclose(fLogfile);
				if (bHypopened)		fclose(fHypfile);
				if (bIdxopened)		fclose(fIdxfile);
				if (bTreeopened)	fclose(fTreefile);
				if (bUPRopened)		fclose(fUPRfile);
				return FALSE;
			}
			bOutOpened= TRUE;
			save_upr_entry_outfile(outfile.full);
		}
	}


	for (i=0; i<MAXENVLEVEL; iEnvIndent[i++]= 0) ;

	if (desttype==TOHTM || desttype==TOMHH)
	{
		strcpy(old_outfile.full, outfile.full);
		strcpy(old_outfile.driv, outfile.driv);
		strcpy(old_outfile.path, outfile.path);
		strcpy(old_outfile.name, outfile.name);
		strcpy(old_outfile.suff, outfile.suff);
	}
	
	init_vars_spec();

	udo_running= TRUE;
	
	destlang= TOGER;

	init_lang();
	init_lang_date();
	
	bBreakInside= FALSE;
	bInsideDocument= FALSE;
	bInsidePopup= FALSE;
	b1stQuote= TRUE;
	b1stApost= TRUE;
	iCharset= SYSTEM_CHARSET;
	bDocUniversalCharsetOn= FALSE;

	show_udo_intro();


	logln_warnings_errors();

	show_status_pass("Pass 1:");

	clear_if_stack();

	iUdopass= PASS1;


	if (pass1(datei) &&							/* Erster Durchlauf aufgrund eines Fehlers gescheitert? */
		(!bCheckMisc || check_modules_pass1()))	/* Diverse Ueberpruefungen auf Wunsch durchfuehren */
	{
	
		/* Unregistrierte Versionen erzeugen immer die Werbeseite */
		if (!config.bRegistered)
		{	/* use_about_udo= TRUE; */ /* UDO is now Open Source */
		}
	
		if ( use_about_udo )
		{	add_pass1_about_udo();
		}
			
		/* Speicher anfordern */
		if ( malloc_token_output_buffer() )
		{
			init_lang_date();		/* Kann IMHO weg */
			check_parwidth();
	
			/* itemchar wird erst nach pass1() gesetzt */
			/* bei !no_umlaute wird kein 8bit-Zeichen mehr verwendet */
			init_env_itemchar();
	
			bBreakInside= FALSE;
			bInsideDocument= FALSE;
			bInsidePopup= FALSE;
			b1stQuote= TRUE;
			b1stApost= TRUE;
			iCharset= SYSTEM_CHARSET;
	
			init_vars_spec();
			init_module_toc_pass2();
			init_module_tp_pass2();
			init_module_img_pass2();
	
			/* richtigen Einsatz von !if testen */
			if ( !bBreakHappened && !bBreakInside )	/*r6pl4: && !bBreakInside */
			{
				if (counter_if_stack > 0)
				{	error_missing_endif(if_stack[counter_if_stack].filename, if_stack[counter_if_stack].fileline);
					bBreakHappened= TRUE;
					ret= FALSE;
				}
			}
					
			if ( !bBreakHappened && !bBreakInside)	/*r6pl4: && !bBreakInside */
			{
				show_status_pass("Pass 2...");
/* VJD */
if (bInsideAppendix)
{
	bInsideAppendix=FALSE;
	printf("[Debug] Warning bInsideAppendix=TRUE - fixed it\n");
}
				clear_if_stack();
				output_preamble();
				iUdopass= PASS2;
	
				if (desttype==TOHTM && html_frames_layout )
				{	html_save_frameset();
				}
					
				if ( pass2(datei) )
				{
					if (bCalledBeginDocument && !bCalledEndDocument)
					{	error_missing_end(CMD_END_DOCUMENT);
						c_end_document();
					}
					if (bCheckMisc)
					{	/* Diverse Ueberpruefungen auf Wunsch durchfuehren */
						check_modules_pass2();
					}
					outln("");
					outln("");
					ret= TRUE;
				
					if (bOutOpened)
					{	switch (desttype)
						{	case TOPCH:
								save_pchelp_commandfile();
								break;
							case TOAQV:
							case TOWIN:
							case TOWH4:
								if (desttype==TOWH4)
								{	save_winhelp4_project();
									bCntSaved = save_winhelp4_cnt();
								}
								else
								{	save_winhelp_project();
								}
								save_win_bmps();	/*r6pl5*/
								if (bUseIdMapFileC)
								{	bMapSavedC= save_winhelp_map_c();
								}
								if (bUseIdMapFilePas)
								{	bMapSavedPas= save_winhelp_map_pas();
								}
								if (bUseIdMapFileVB)
								{	bMapSavedVB= save_winhelp_map_vb();
								}
								if (bUseIdMapFileGFA)
								{	bMapSavedGFA= save_winhelp_map_gfa();
								}
								break;
							case TORTF:
								save_rtf_bmps();	/*r6pl6*/
								break;
							case TOHTM:
								save_html_gifs();
								break;
							case TOMHH:
								bHhcSaved= save_htmlhelp_contents(sHhcfull);
								bHhkSaved= save_htmlhelp_index(sHhkfull);
								save_htmlhelp_project();
								save_html_gifs();
								break;
							case TOSTG:
							case TOAMG:
								save_stg_imgs();
								break;
						}
					}
					
					get_timestr(timer_stop);
	
				}	/* if ( pass2() ) */
	
			}	/* if (!bBreakHappened) */
	
		}	/* if ( malloc...() ) */
	}	

	/* Hier geht's weiter, wenn schon pass1() versagte */
	udo_running= FALSE;


	if (desttype==TOHTM || desttype==TOMHH)	/* Alten Filenamen zurueckholen */
	{
		strcpy(outfile.full, old_outfile.full);
		strcpy(outfile.driv, old_outfile.driv);
		strcpy(outfile.path, old_outfile.path);
		strcpy(outfile.name, old_outfile.name);
		strcpy(outfile.suff, old_outfile.suff);
		sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);
	}	

	/* Hier Informationen ueber das erzeugte File ausgeben. */

	if (!bNoLogfile)
	{	logln_information();
		vloglnf("source file: %s", infile.full);
		logln("");
		vloglnf("Warnings:       %d", get_warning_counter());
		vloglnf("Notes:          %d", get_note_counter());
		vloglnf("Errors:         %d", get_error_counter());
		logln("");
		vloglnf("Nodes:          %d", all_nodes);
		vloglnf("Subnodes:       %d", all_subnodes);
		vloglnf("Subsubnodes:    %d", all_subsubnodes);
		vloglnf("Subsubsubnodes: %d", all_subsubsubnodes);
		vloglnf("Macros:         %d", macro_counter);
		vloglnf("Defines:        %d", define_counter);
		vloglnf("Hyphens:        %d", hyphen_counter);
		logln("");
		vloglnf("started:  %s", timer_start);
		vloglnf("finished: %s", timer_stop);
		logln("");

		if (bGifHmSaved)	logln_file_generated("GIF", sGifHmFull, "");
		if (bGifUpSaved)	logln_file_generated("GIF", sGifUpFull, "");
		if (bGifLfSaved)	logln_file_generated("GIF", sGifLfFull, "");
		if (bGifRgSaved)	logln_file_generated("GIF", sGifRgFull, "");
		if (bGifNoHmSaved)	logln_file_generated("GIF", sGifNoHmFull, "");
		if (bGifNoUpSaved)	logln_file_generated("GIF", sGifNoUpFull, "");
		if (bGifNoLfSaved)	logln_file_generated("GIF", sGifNoLfFull, "");
		if (bGifNoRgSaved)	logln_file_generated("GIF", sGifNoRgFull, "");
		if (bGifTpSaved)	logln_file_generated("GIF", sGifTpFull, "");
		if (bGifFoSaved)	logln_file_generated("GIF", sGifFoFull, "");
		if (bGifFcSaved)	logln_file_generated("GIF", sGifFcFull, "");
		if (bGifFsSaved)	logln_file_generated("GIF", sGifFsFull, "");
		if (bGifMwSaved)	logln_file_generated("GIF", sGifMwFull, "");
		if (bGifGerSaved)	logln_file_generated("GIF", sGifGerFull, "");
		if (bGifEngSaved)	logln_file_generated("GIF", sGifEngFull, "");
		if (bBmpFoSaved)	logln_file_generated("BMP", sBmpFoFull, "");
		if (bBmpFcSaved)	logln_file_generated("BMP", sBmpFcFull, "");
		if (bBmpMwSaved)	logln_file_generated("BMP", sBmpMwFull, "");
		if (bImgFoSaved)	logln_file_generated("IMG", sImgFoFull, "");
		if (bImgFcSaved)	logln_file_generated("IMG", sImgFcFull, "");
		if (bImgMwSaved)	logln_file_generated("IMG", sImgMwFull, "");
		if (bCmdSaved)		logln_file_generated("Pure C command file", sCmdfull, "");
		if (bHpjSaved)		logln_file_generated("WinHelp project", sHpjfull, "");
		if (bCntSaved)		logln_file_generated("WinHelp4 contents", sCntfull, "");
		if (bMapSavedC)		logln_file_generated("WinHelp map for C", sMapNoSuff, ".hpc");
		if (bMapSavedPas)	logln_file_generated("WinHelp map for Pascal", sMapNoSuff, ".hpp");
		if (bMapSavedVB)	logln_file_generated("WinHelp map for Visual Basic", sMapNoSuff, ".hpb");
		if (bMapSavedGFA)	logln_file_generated("WinHelp map for GFA Basic", sMapNoSuff, ".hpg");
		if (bHhpSaved)		logln_file_generated("HTML Help project", sHhpfull, "");
		if (bHhcSaved)		logln_file_generated("HTML Help contents", sHhcfull, "");
		if (bHhkSaved)		logln_file_generated("HTML Help index", sHhkfull, "");
		if (bHypSaved)		logln_file_generated("Hyphen file", sHypfull, "");
		if (bIdxSaved)		logln_file_generated("Index file", sIdxfull, "");
		if (bTreeSaved)		logln_file_generated("Tree file", sTreefull, "");
		if (bUPRSaved)		logln_file_generated("Project file", sUPRfull, "");

		if ( outfile.full[0]!=EOS )
		{	if (bBreakHappened)
			{	logln_interrupted();
			}
			else
			{	if (!bTestmode)
				{	logln_file_generated("Output", outfile.full, "");
				}
			}
		}

		if (bFatalErrorDetected)
		{	logln("UDO stopped because of fatal error(s)");
		}

	}	/* if (!nologfile) */


	if (!bTestmode && !bFatalErrorDetected)
	{	show_status_info("");
		show_status_info("");
		sprintf(sInfMsg, "Output written to %s", outfile.full);
		show_status_info(sInfMsg);
	}
	show_status_info("");	
	show_status_info("");	

	if ( (val=get_warning_counter())>0)
	{	sprintf(sInfMsg, "Warnings: %d", val);
		show_status_errors(sInfMsg);
	}
	if ( (val=get_note_counter())>0)
	{	sprintf(sInfMsg, "Notes:    %d", val);
		show_status_errors(sInfMsg);
	}
	if ( (val=get_error_counter())>0)
	{	sprintf(sInfMsg, "Errors:   %d", val);
		show_status_errors(sInfMsg);
	}

	call_dummy();
	
	if (bLogopened && fLogfile!=NULL)		fclose(fLogfile);
	if (bHypopened && fHypfile!=NULL)		fclose(fHypfile);
	if (bIdxopened && fIdxfile!=NULL)		fclose(fIdxfile);
	if (bTreeopened && fTreefile!=NULL)		fclose(fTreefile);
	if (bUPRopened && fUPRfile!=NULL)		fclose(fUPRfile);
	if (bOutOpened && outfile.file!=NULL)
	{
		fclose(outfile.file);
		outfile.file= NULL;
		bOutOpened= FALSE;
	}

	exit_modules();
	free_token_output_buffer();

	/* Hyphenfile sortieren und Dupes entfernen */
	if (!bNoHypfile && bDocSortHyphenFile)
	{	sort_hypfile(sHypfull);
	}

	init_vars();
	
	return ret;
}	/* udo */


/*	############################################################
	#
	# Aus einem UDO Quelltext wieder einen Quelltext machen.
	# Dabei Include-Dateien in die neue Datei einbinden.
	# Die normalen Routinen koennen dafuer nicht benutzt
	# werden, da ueberall spezielle Ausgaben erfolgen und
	# If-Strukturen auch beruecksichtigt wuerden.
	#
	# Es werden keine Indexfiles, Hyphenfiles erzeugt,
	# jedoch Logfile und Treefile.
	#
	############################################################	*/
LOCAL BOOLEAN passU (char *datei)
{
	MYTEXTFILE 	*file;
	char	zeile[LINELEN], zeileBak[LINELEN];
	char	tmp_datei[256], old_datei[256];
	int		i;
	size_t	len;
	BOOLEAN	inc_done;
	const char *orgBeg= "##### start of ";
	const char *orgEnd= "##### end of ";

	if (iFilesOpened>=MAXFILECOUNTER)
	{	error_too_many_files();
		return FALSE;
	}

	strcpy(old_datei, datei);
	strcpy(tmp_datei, datei);

	build_include_filename(tmp_datei, ".ui");

	file = myTextOpen(tmp_datei);
	
	if (!file)
	{	strcpy(tmp_datei, old_datei);
		file = myTextOpen(tmp_datei);

		if (!file)
		{	error_open_pass2(tmp_datei);
			bErrorDetected= TRUE;
			return FALSE;
		}
	}

	if (bVerbose)
	{	show_status_udo2udo(tmp_datei);
	}
	
	iFilesOpened++;
	uiFileLines[iFilesOpened]= 0;
	strcpy(sFileNames[iFilesOpened], tmp_datei);

	strcpy(sCurrFileName, tmp_datei);
	uiCurrFileLine= 0;

	if (bUseTreefile)
	{	if (bTreeopened)
		{	for (i=0; i<iFilesOpened; i++)
			{	fprintf(fTreefile, "|----");
			}
			fprintf(fTreefile, "%s\n", tmp_datei);
		}
	}

	while ( (!bBreakHappened) && (!bBreakInside) && (!bFatalErrorDetected) && (myTextGetline(zeile, LINELEN, file)) )
	{
		uiFileLines[iFilesOpened]++;
		uiCurrFileLine= uiFileLines[iFilesOpened];

		if ( break_action() )
		{	iFilesOpened--;
			myTextClose(file);
			strcpy(sCurrFileName, sFileNames[iFilesOpened]);
			return FALSE;
		}
		
		/* LF, CR und LEERZEICHEN (<=!!!!) etc. am Ende entfernen */
		len= strlen(zeile);
		while (  (len>0) && (((UCHAR) zeile[len-1])<=32) )
		{	zeile[len-1]= EOS;
			len--;
		}

		/* Kopie der spaeter auszugebenden Zeile anlegen */
		strcpy(zeileBak, zeile);

		token_reset();
		replace_defines(zeile);
		str2tok(zeile);

		inc_done= FALSE;
		if (pflag[PASSU].env==ENV_NONE)
		{
			replace_defines(zeile);
			if (!inc_done && strcmp(token[0], "!include")==0)
			{	inc_done= TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include();
				voutlnf("%s%s", orgEnd, zeile);
			}
			if (!inc_done && strcmp(token[0], "!vinclude")==0)
			{	inc_done= TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_verbatim();
				voutlnf("%s%s", orgEnd, zeile);
			}
			if (!inc_done && strcmp(token[0], "!pinclude")==0)
			{	inc_done= TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_preformatted();
				voutlnf("%s%s", orgEnd, zeile);
			}
			if (!inc_done && strcmp(token[0], "!rinclude")==0)
			{	inc_done= TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_raw();
				voutlnf("%s%s", orgEnd, zeile);
			}
			if (!inc_done && strcmp(token[0], "!sinclude")==0)
			{	inc_done= TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_src();
				voutlnf("%s%s", orgEnd, zeile);
			}
			if (!inc_done && strcmp(token[0], "!cinclude")==0)
			{	inc_done= TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_comment();
				voutlnf("%s%s", orgEnd, zeile);
			}
			if (!inc_done && strcmp(token[0], "!ldinclude")==0)
			{	inc_done= TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_linedraw();
				voutlnf("%s%s", orgEnd, zeile);
			}
			if (!inc_done && strcmp(token[0], "!input")==0)
			{	inc_done= TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_input();
				voutlnf("%s%s", orgEnd, zeile);
			}
		}

		if (!inc_done)
		{
			outln(zeileBak);
		}
		
	}	/* while (fgets) */

	iFilesOpened--;
	strcpy(sCurrFileName, sFileNames[iFilesOpened]);
	myTextClose(file);

	multitasking_interrupt();

	return (!bFatalErrorDetected);

}	/*passU*/


GLOBAL BOOLEAN udo2udo (char *datei)
{
	BOOLEAN ret= FALSE;
	int		i, val;
	FILE	*file;
	char	tmp[512];

	get_timestr(timer_start);

	init_modules();
	set_format_flags();

	bFatalErrorDetected= FALSE;
	bErrorDetected= FALSE;
	bBreakHappened= FALSE;
	bBreakInside= FALSE;
	
	bOutOpened= FALSE;
	outlines= 0;

	fLogfile= stderr;	bLogopened= FALSE;
	fTreefile= stderr;	bTreeopened= FALSE;	bTreeSaved= FALSE;

	/* Erstmal testen, ob die Datei vorhanden ist, damit nicht unnoetig	*/
	/* Dateien angelegt werden.	 0.47									*/

	strcpy(tmp, datei);

	build_include_filename(tmp, ".ui");

	file = fopen(tmp, "r");
	if (!file)
	{	error_open_infile(tmp);
		return FALSE;
	}
	fclose(file);
	

	if (!bNoLogfile)
	{	
		if ( outfile.full[0]!=EOS )
		{	if ( sLogfull[0]==EOS )
			{	logfile_adjust();
			}
			
			fLogfile= myFwopen(sLogfull, TOASC);
			if (!fLogfile)
			{	fLogfile= stderr;
				warning_err_logfile();
				bErrorDetected= TRUE;
				return FALSE;
			}
			bLogopened= TRUE;
			save_upr_entry_outfile(sLogfull);
		}
	}



	if (bUseTreefile)
	{	if ( outfile.full[0]!=EOS )
		{	if (sTreefull[0]!=EOS)			
			{	fTreefile= myFwopen(sTreefull, TOASC);
				if (!fTreefile)
				{	fTreefile= stderr;
					warning_err_treefile();
					bErrorDetected= TRUE;
					return FALSE;
				}
				bTreeopened= TRUE;
				save_upr_entry_outfile(sTreefull);
			}
		}
	}


	if ( outfile.full[0]!=EOS )
	{
		if ( (strcmp(outfile.full, "~")==0) || (strcmp(outfile.full, "!")==0) )
		{	dest_adjust();
		}
		
		if (!bTestmode)
		{
			if (strcmp(outfile.full, infile.full)==0)	/* 0.48 */
			{	error_infile_outfile(outfile.full);
				bErrorDetected= TRUE;
				if (bLogopened)		fclose(fLogfile);
				if (bTreeopened)	fclose(fTreefile);
				return FALSE;
			}

			outfile.file= myFwopen(outfile.full, desttype);
			if (outfile.file == NULL)
			{	error_open_outfile(outfile.full);
				warning_err_destination();
				bErrorDetected= TRUE;
				if (bLogopened)		fclose(fLogfile);
				if (bTreeopened)	fclose(fTreefile);
				return FALSE;
			}
			bOutOpened= TRUE;
			save_upr_entry_outfile(outfile.full);
		}
	}


	for (i=0; i<MAXENVLEVEL; iEnvIndent[i++]= 0) ;

	if (desttype==TOHTM || desttype==TOMHH)
	{
		strcpy(outfile.full, old_outfile.full);
		strcpy(outfile.driv, old_outfile.driv);
		strcpy(outfile.path, old_outfile.path);
		strcpy(outfile.name, old_outfile.name);
		strcpy(outfile.suff, old_outfile.suff);
		sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);
	}
	
	init_vars_spec();

	udo_running= TRUE;
	
	destlang= TOGER;

	init_lang();
	init_lang_date();
	
	bBreakInside= FALSE;
	bInsideDocument= FALSE;
	bInsidePopup= FALSE;
	b1stQuote= TRUE;
	b1stApost= TRUE;
	iCharset= SYSTEM_CHARSET;
	bDocUniversalCharsetOn= FALSE;

	show_udo_intro();

	logln_warnings_errors();

	show_status_pass("Pass 1...");

	clear_if_stack();

	iUdopass= PASS1;

	if ( pass1(datei) )
	{
		/* Speicher anfordern */
		if ( malloc_token_output_buffer() )
		{
			init_lang_date();		/* Kann IMHO weg */
			check_parwidth();

			/* itemchar wird erst nach pass1() gesetzt */
			/* bei !no_umlaute wird kein 8bit-Zeichen mehr verwendet */
			init_env_itemchar();

			bBreakInside= FALSE;
			bInsideDocument= FALSE;
			bInsidePopup= FALSE;
			b1stQuote= TRUE;
			b1stApost= TRUE;
			iCharset= SYSTEM_CHARSET;

			init_vars_spec();
			init_module_toc_pass2();
			init_module_tp_pass2();
			init_module_img_pass2();

			/* richtigen Einsatz von !if testen */
			if ( !bBreakHappened && !bBreakInside )	/*r6pl4: && !bBreakInside */
			{
				if (counter_if_stack > 0)
				{	error_missing_endif(if_stack[counter_if_stack].filename, if_stack[counter_if_stack].fileline);
					bBreakHappened= TRUE;
					ret= FALSE;
				}
			}
				
			if ( !bBreakHappened && !bBreakInside)	/*r6pl4: && !bBreakInside */
			{
				show_status_pass("udo2udo...");
				clear_if_stack();
				iUdopass= PASSU;

				if ( passU(datei) )
				{
					ret= TRUE;
					get_timestr(timer_stop);

				}	/* if ( pass2() ) */

			}	/* if (!bBreakHappened) */

		}	/* if ( malloc...() ) */

	}	/* if ( pass1() ) */


	udo_running= FALSE;

	/* Hier Informationen ueber das erzeugte File ausgeben. */

	if (!bNoLogfile)
	{	logln_information();
		vloglnf("source file: %s", infile.full);
		logln("");
		vloglnf("Warnings:       %d", get_warning_counter());
		vloglnf("Notes:          %d", get_note_counter());
		vloglnf("Errors:         %d", get_error_counter());
		logln("");
		vloglnf("Nodes:          %d", all_nodes);
		vloglnf("Subnodes:       %d", all_subnodes);
		vloglnf("Subsubnodes:    %d", all_subsubnodes);
		vloglnf("Subsubsubnodes: %d", all_subsubsubnodes);
		vloglnf("Macros:         %d", macro_counter);
		vloglnf("Defines:        %d", define_counter);
		vloglnf("Hyphens:        %d", hyphen_counter);
		logln("");
		vloglnf("started:  %s", timer_start);
		vloglnf("finished: %s", timer_stop);
		logln("");

		if (bTreeSaved)		logln_file_generated("Tree file", sTreefull, "");

		if ( outfile.full[0]!=EOS )
		{	if (bBreakHappened)
			{	logln_interrupted();
			}
			else
			{	if (!bTestmode)
				{	logln_file_generated("Output", outfile.full, "");
				}
			}
		}

		if (bFatalErrorDetected)
		{	logln("UDO stopped because of fatal error(s)");
		}

	}	/* if (!nologfile) */


	if (!bTestmode)
	{	show_status_info("");
		show_status_info("");
		sprintf(sInfMsg, "Output written to %s", outfile.full);
		show_status_info(sInfMsg);
	}

	show_status_info("");	
	show_status_info("");	

	if ( (val=get_warning_counter())>0)
	{	sprintf(sInfMsg, "Warnings: %d", val);
		show_status_errors(sInfMsg);
	}
	if ( (val=get_note_counter())>0)
	{	sprintf(sInfMsg, "Notes:    %d", val);
		show_status_errors(sInfMsg);
	}
	if ( (val=get_error_counter())>0)
	{	sprintf(sInfMsg, "Errors:   %d", val);
		show_status_errors(sInfMsg);
	}
	
	if (bLogopened && fLogfile!=NULL)
	{
		fclose(fLogfile);
	}
	if (bTreeopened && fTreefile!=NULL)
	{
		fclose(fTreefile);
	}
	if (bOutOpened && outfile.file!=NULL)
	{
		fclose(outfile.file);
		outfile.file= NULL;
		bOutOpened = FALSE;
	}

	exit_modules();
	free_token_output_buffer();

	init_vars();

	return ret;

}	/* udo2udo */


/*	############################################################
	# init_lang
	# Strings fuer die ausgewaehlte Sprache setzen (destlang)
	############################################################	*/

/*	--------------------------------------------------------------
	get_timestr()
	Ermittelt die aktuelle Uhrzeit
	->	t:	String, der danach die Zeit in Form HH:MM:SS enthaelt
	--------------------------------------------------------------	*/
LOCAL void get_timestr ( char *t )
{
	time_t		timer;
	struct tm	*zeit;

	time(&timer);
	zeit= localtime(&timer);

	sprintf(t, "%02d:%02d:%02d", zeit->tm_hour, zeit->tm_min, zeit->tm_sec);

}	/* get_timestr */


/*	--------------------------------------------------------------
	init_lang_date()
	Setzt Uhrzeit und Datum abhaengig von der jeweiligen Sprache
	--------------------------------------------------------------	*/
LOCAL void init_lang_date ( void )
{
	time_t		timer;
	struct tm	*zeit;
	int			old_charset;

	time(&timer);
	zeit= localtime(&timer);
	
	iDateDay=	zeit->tm_mday;	/* Global sichern z.B. fuer RTF */
	iDateMonth=	zeit->tm_mon+1;
	iDateYear=	zeit->tm_year+1900;
	iDateHour=	zeit->tm_hour;
	iDateMin=	zeit->tm_min;
	iDateSec=	zeit->tm_sec;

	switch (destlang)
	{
		case TOENG:	/* Englisch */
			sprintf(lang.today, "%s %d, %d", MONTH_ENG[zeit->tm_mon], zeit->tm_mday, 1900+zeit->tm_year);
			sprintf(lang.short_today, "%0d/%02d/%02d", 1900+zeit->tm_year, zeit->tm_mon+1, zeit->tm_mday);
			break;

		case TOFRA:	/* Franzoesisch */
			sprintf(lang.today, "%d %s %d", zeit->tm_mday, MONTH_FRA[zeit->tm_mon], 1900+zeit->tm_year);
			sprintf(lang.short_today, "%02d.%02d.%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
			break;

		case TOITA:	/* Italienisch */
			sprintf(lang.today, "%d. %s %d", zeit->tm_mday, MONTH_ITA[zeit->tm_mon], 1900+zeit->tm_year);
			sprintf(lang.short_today, "%02d.%02d.%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
			break;

		case TOSWE:	/* Schwedisch */
			sprintf(lang.today, "%s %d, %d", MONTH_SWE[zeit->tm_mon], zeit->tm_mday, 1900+zeit->tm_year);
			sprintf(lang.short_today, "%0d-%02d-%02d", 1900+zeit->tm_year, zeit->tm_mon+1, zeit->tm_mday);
			break;

		case TOSPA:	/* Spanisch */
			sprintf(lang.today, "%d. %s %d", zeit->tm_mday, MONTH_SPA[zeit->tm_mon], 1900+zeit->tm_year);
			sprintf(lang.short_today, "%02d.%02d.%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
			break;

		case TODUT:	/* Hollaendisch */
			sprintf(lang.today, "%d %s %d", zeit->tm_mday, MONTH_DUT[zeit->tm_mon], 1900+zeit->tm_year);
			sprintf(lang.short_today, "%02d-%02d-%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
			break;

		default:	/* Deutsch ist default */
			sprintf(lang.today, "%d. %s %d", zeit->tm_mday, MONTH_GER[zeit->tm_mon], 1900+zeit->tm_year);
			sprintf(lang.short_today, "%02d.%02d.%d", zeit->tm_mday, zeit->tm_mon+1, 1900+zeit->tm_year);
			break;
	}

	uni2ascii(lang.today);
	old_charset= iCharset;		/* r6pl2: sonst wird M"arz falsch ausgegeben,	*/
	iCharset= SYSTEM_CHARSET;	/* falls man Latin1 fuer WinHelp benutzt.		*/
	auto_quote_chars(lang.today, TRUE);
	iCharset= old_charset;

}	/* init_lang_date */


/*	--------------------------------------------------------------
	init_lang() initialsisiert die von UDO benutzen Ausdrucke in
	der jeweiligen Sprache. Sonderzeichen muessen im Universal
	Charset angegeben werden.
	--------------------------------------------------------------	*/
LOCAL void init_lang ( void )
{
	memset(&lang, 0, sizeof(LANG));

	switch (destlang)	
	{
		case TODUT:	/* Rogier_Cobben@nextjk.stuyts.nl */
		    strcpy(lang.preface,    "Voorwoord");
		    strcpy(lang.chapter,    "Hoofdstuk");
		    strcpy(lang.title,      "Titel");
		    strcpy(lang.appendix,   "Bijlage");
		    strcpy(lang.contents,   "Inhoud");
		    strcpy(lang.listfigure, "Afbeeldingenlijst");
		    strcpy(lang.listtable,  "Tabellenlijst");
		    strcpy(lang.figure,     "Afbeelding");
		    strcpy(lang.table,      "Tabel");
		    strcpy(lang.index,      "Index");
		    strcpy(lang.page,       "bladzijde");
		    strcpy(lang.see,        "zie");
		    strcpy(lang.also,       "zie ook");
		    strcpy(lang.by,         "door");
		    strcpy(lang.up,         "&Omhoog");
		    strcpy(lang.exit,       "Be	i&ndigen");
		    strcpy(lang.unknown,    "Onbekend");
		    strcpy(lang.update,		"Last updated on");
		    strcpy(lang.lcid,		"LCID=0x407 0x0 0x0 ;German (Germany)");
				strcpy(lang.html_home,	"Home");
				strcpy(lang.html_up,	"Up");
				strcpy(lang.html_prev,	"Prev");
				strcpy(lang.html_next,	"Next");
				/* New in r6pl16 [NHz] */
				strcpy(lang.html_lang,	"nl");
				strcpy(lang.html_start,	"Begin of the document");
		    break;

		case TOENG:
		  	strcpy(lang.preface,	"Preface");
		  	strcpy(lang.chapter,	"Chapter");
		  	strcpy(lang.title,		"Title");
		  	strcpy(lang.appendix,	"Appendix");
		  	strcpy(lang.contents,	"Contents");
		  	strcpy(lang.listfigure,	"List of Figures");
		  	strcpy(lang.listtable,	"List of Tables");
		  	strcpy(lang.figure,		"Figure");
		  	strcpy(lang.table,		"Table");
		  	strcpy(lang.index,		"Index");
		  	strcpy(lang.page,		"page");
		  	strcpy(lang.see,		"see");
		  	strcpy(lang.also,		"see also");
		  	strcpy(lang.by,			"by");
		  	strcpy(lang.up,			"&Up");
		  	strcpy(lang.exit,		"E&xit");
		  	strcpy(lang.unknown,	"Unknown");
		  	strcpy(lang.update,		"Last updated on");
		    strcpy(lang.lcid,		"LCID=0x409 0x0 0x0 ;English (USA)");
				strcpy(lang.html_home,	"Home");
				strcpy(lang.html_up,	"Up");
				strcpy(lang.html_prev,	"Prev");
				strcpy(lang.html_next,	"Next");
				/* New in r6pl16 [NHz] */
				strcpy(lang.html_lang,	"en");
				strcpy(lang.html_start,	"Begin of the document");
			break;

		case TOFRA:		/* vergleiche german.sty von LaTeX */
		  	strcpy(lang.preface,	"Pr(!'e)face");
		  	strcpy(lang.chapter,	"Chapitre");
		  	strcpy(lang.title,		"Titre");
		  	strcpy(lang.appendix,	"Annexe");
				strcpy(lang.contents,	"Sommaire");	/* r6pl13: laut Didier Briel (ddc@imaginet.fr) */
		  	strcpy(lang.listfigure,	"Table des figures");
		  	strcpy(lang.listtable,	"Liste des tableaux");
		  	strcpy(lang.figure,		"Figure");
		  	strcpy(lang.table,		"Tableau");
		  	strcpy(lang.index,		"Index");
		  	strcpy(lang.page,		"page");
		  	strcpy(lang.see,		"voir");
		  	strcpy(lang.also,		"voir aussi");
		  	strcpy(lang.by,			"de");
		  	strcpy(lang.up,			"&Haut");
		  	strcpy(lang.exit,		"&Fin");
		  	strcpy(lang.unknown,	"Inconnu");
		  	strcpy(lang.update,		"Derni(!`e)re mise (!`a) jour le");		/* r6pl13: laut Didier Briel (ddc@imaginet.fr) */
		    strcpy(lang.lcid,		"LCID=0x40c 0x0 0x0 ;Frensh (France)");
				strcpy(lang.html_home,	"Home");
				strcpy(lang.html_up,	"Up");
				strcpy(lang.html_prev,	"Prev");
				strcpy(lang.html_next,	"Next");
				/* New in r6pl16 [NHz] */
				strcpy(lang.html_lang,	"fr");
				strcpy(lang.html_start,	"Begin of the document");
		  	
		  	/* Strings mit Sonderzeichen anpassen */
		  	uni2ascii(lang.preface);
				/* Changed in r6pl17 [NHz] */
		  	/* uni2ascii(lang.contents);*/
		  	uni2ascii(lang.update);
		  	break;

		case TOITA:		/* laut "g.morando@agora.stm.it" */
		  	strcpy(lang.preface,	"Prefazione");
		  	strcpy(lang.chapter,	"Capitolo");
		  	strcpy(lang.title,		"Titolo");
		  	strcpy(lang.appendix,	"Appendice");
		  	strcpy(lang.contents,	"Contenuto");
		  	strcpy(lang.listfigure,	"Lista di Figure");
		  	strcpy(lang.listtable,	"Lista di Tabelle");
		  	strcpy(lang.figure,		"Figura");
		  	strcpy(lang.table,		"Tabella");
		  	strcpy(lang.index,		"Index");
		  	strcpy(lang.page,		"pagina");
		  	strcpy(lang.see,		"vedere");
		  	strcpy(lang.also,		"vedere anche");
		  	strcpy(lang.by,			"da");
		  	strcpy(lang.up,			"S&u");
		  	strcpy(lang.exit,		"Uscita");
		  	strcpy(lang.unknown,	"Ignoto");
		  	strcpy(lang.update,		"Last updated on");
		    strcpy(lang.lcid,		"LCID=0x410 0x0 0x0 ;Italian (Italy)");
				strcpy(lang.html_home,	"Home");
				strcpy(lang.html_up,	"Up");
				strcpy(lang.html_prev,	"Prev");
				strcpy(lang.html_next,	"Next");
				/* New in r6pl16 [NHz] */
				strcpy(lang.html_lang,	"it");
				strcpy(lang.html_start,	"Begin of the document");
		  	break;

		case TOSPA:	/* Euro-Dictionary */
		  	strcpy(lang.preface,	"Prefacio");
		  	strcpy(lang.chapter,	"Cap(!`i)tulo");
		  	strcpy(lang.title,		"T(!`i)tulo");
		  	strcpy(lang.appendix,	"Ap(!`e)ndice");
		  	strcpy(lang.contents,	"Contenido");
		  	strcpy(lang.listfigure,	"Lista de grabados");
		  	strcpy(lang.listtable,	"Lista de tablas");
		  	strcpy(lang.figure,		"Grabado");
		  	strcpy(lang.table,		"Tabla");
		  	strcpy(lang.index,		"(!`I)ndice");
		  	strcpy(lang.page,		"p(!`a)gina");
		  	strcpy(lang.see,		"ver");
		  	strcpy(lang.also,		"ver tambi(!`e)n");
		  	strcpy(lang.by,			"de");
		  	strcpy(lang.up,			"Elevado");
		  	strcpy(lang.exit,		"Terminar");
		  	strcpy(lang.unknown,	"Desconocido");
		  	strcpy(lang.update,		"Last updated on");
		    strcpy(lang.lcid,		"LCID=0x40a 0x0 0x0 ;Spanish (Traditional)");
				strcpy(lang.html_home,	"Home");
				strcpy(lang.html_up,	"Up");
				strcpy(lang.html_prev,	"Prev");
				strcpy(lang.html_next,	"Next");
				/* New in r6pl16 [NHz] */
				strcpy(lang.html_lang,	"es");
				strcpy(lang.html_start,	"Begin of the document");

		  	/* Strings mit Sonderzeichen anpassen */
		  	uni2ascii(lang.chapter);
		  	uni2ascii(lang.title);
		  	uni2ascii(lang.appendix);
		  	uni2ascii(lang.index);
		  	uni2ascii(lang.page);
		  	uni2ascii(lang.also);
		  	break;

		case TOSWE:
		  	strcpy(lang.preface,	"F(!\"o)rord");
		  	strcpy(lang.chapter,	"Kapitel");
		  	strcpy(lang.title,		"Titel");
		  	strcpy(lang.appendix,	"Appendix");
		  	strcpy(lang.contents,	"Inneh(!.a)ll");
		  	strcpy(lang.listfigure,	"Lista av Figurer");
		  	strcpy(lang.listtable,	"Lista av Tabeller");
		  	strcpy(lang.figure,		"Figurer");
		  	strcpy(lang.table,		"Tabeller");
		  	strcpy(lang.index,		"Index");
		  	strcpy(lang.page,		"Sida");
		  	strcpy(lang.see,		"se");
		  	strcpy(lang.also,		"se (!\"a)ven");
		  	strcpy(lang.by,			"av");
		  	strcpy(lang.up,			"&Upp");
		  	strcpy(lang.exit,		"Avsluta");
		  	strcpy(lang.unknown,	"Unknown");
		  	strcpy(lang.update,		"Last updated on");
		    strcpy(lang.lcid,		"LCID=0x41d 0x0 0x0 ;Swedish (Sweden)");
				strcpy(lang.html_home,	"Home");
				strcpy(lang.html_up,	"Up");
				strcpy(lang.html_prev,	"Prev");
				strcpy(lang.html_next,	"Next");
				/* New in r6pl16 [NHz] */
				strcpy(lang.html_lang,	"sv");
				strcpy(lang.html_start,	"Begin of the document");
		  	
		  	/* Strings mit Sonderzeichen anpassen */
		  	uni2ascii(lang.preface);
		  	uni2ascii(lang.contents);
		  	uni2ascii(lang.also);
		  	break;

		default:	/* Deutsch ist default */
				strcpy(lang.preface,	"Vorwort");
		  	strcpy(lang.chapter,	"Kapitel");
		  	strcpy(lang.title,		"Titel");
		  	strcpy(lang.appendix,	"Anhang");
		  	strcpy(lang.contents,	"Inhaltsverzeichnis");
		  	strcpy(lang.listfigure,	"Abbildungsverzeichnis");
		  	strcpy(lang.listtable,	"Tabellenverzeichnis");
		  	strcpy(lang.figure,		"Abbildung");
		  	strcpy(lang.table,		"Tabelle");
		  	strcpy(lang.index,		"Index");
		  	strcpy(lang.page,		"Seite");
		  	strcpy(lang.see,		"siehe");
		  	strcpy(lang.also,		"siehe auch");
		  	strcpy(lang.by,			"von");
		  	strcpy(lang.up,			"&Hoch");
		  	strcpy(lang.exit,		"Bee&nden");
		  	strcpy(lang.unknown,	"Unbekannt");
				strcpy(lang.update,		"Letzte Aktualisierung am");	/*r6pl5: (!\"A)nderung */
		    strcpy(lang.lcid,		"LCID=0x407 0x0 0x0 ;German (Germany)");
				strcpy(lang.html_home,	"Home");
				strcpy(lang.html_up,	"Up");
				strcpy(lang.html_prev,	"Prev");
				strcpy(lang.html_next,	"Next");
				/* New in r6pl16 [NHz] */
				strcpy(lang.html_lang,	"de");
				strcpy(lang.html_start,	"Beginn des Dokumentes");
		  	
		  	uni2ascii(lang.update);
		  	break;
	}
	
	toc_init_lang();
	
}	/*init_lang*/



/*	############################################################
	#
	# Globale und lokale Variablen initialisieren
	#
	############################################################	*/
LOCAL void init_vars_texinfo ( void )
{
	if (desttype==TOINF)
	{
		no_umlaute= TRUE;
		use_auto_subtocs= TRUE;			subtocs1_depth= 1;
		use_auto_subsubtocs= TRUE;		subtocs2_depth= 1;
		use_auto_subsubsubtocs= TRUE;	subtocs3_depth= 1;
		no_numbers= TRUE;
	}
}

LOCAL void init_vars_nroff ( void )
{
	if (desttype==TONRO)
	{
		no_umlaute= TRUE;
		no_numbers= TRUE;
	}
}


LOCAL void init_vars_sourcecode ( void )
{
	sSrcRemOn[0]= EOS;
	sSrcRemOff[0]= EOS;
	
	switch (desttype)
	{
		case TOSRC:
			strcpy(sSrcRemOn, "/*");
			strcpy(sSrcRemOff, "*/");
			break;
		case TOSRP:
			strcpy(sSrcRemOn, "(*");
			strcpy(sSrcRemOff, "*)");
			break;
	}

}	/* init_vars_sourcecode */


LOCAL void init_vars_stg ( void )
{
#if 0
	if (desttype==TOSTG)
	{
		zDocParwidth= 75;
	}
#endif
}


LOCAL void init_vars_htmlhelp ( void )
{
	if (desttype==TOMHH)
	{
		no_headlines= TRUE;
		no_bottomlines= TRUE;
		no_footers= TRUE;
	}
}

LOCAL void init_vars_pdf ( void )
{
	if (desttype==TOPDL)
	{
		bTex2e= TRUE;
		/* Deleted in r6.2pl1 [NHz] */ 		/* iTexVersion= TEX_MIKTEX; */
	}
}


LOCAL void init_vars_win ( void )
{
}

/*	--------------------------------------------------------------
	init_vars_spec() setzt sinnvolle Default-Werte fuer die
	jeweiligen Formate. desttype muss bereits feststehen!
	In den Funktionen duerfen keine Werte gesetzt werden, die
	von pass1() veraendert werden koennen, da ansonsten die
	ausgelesenen Daten hinfaellig werden
	--------------------------------------------------------------	*/
LOCAL void init_vars_spec ( void )
{
	init_vars_nroff();
	init_vars_texinfo();
	init_vars_sourcecode();
	init_vars_htmlhelp();
	init_vars_stg();
	init_vars_pdf();
	init_vars_win();
}


/*	--------------------------------------------------------------
	init_modules() initialisiert die anderen Module
	--------------------------------------------------------------	*/
LOCAL void init_modules ( void )
{
	init_module_about();	/* Werbeseite				*/
	init_module_chars();	/* Zeichenumwandlungen		*/
	init_module_env();		/* Umgebungen				*/
	init_module_img();		/* Bilder					*/
	init_module_msg();		/* Fehlermeldungen			*/
	init_module_par();		/* Parameter				*/
	init_module_sty();		/* Stile etc. 				*/
	init_module_tab();		/* tabellensatz				*/
	init_module_toc();		/* Inhaltsverzeichnis(se)	*/
	init_module_tp();		/* Titelseite				*/

	init_vars_spec();

}	/* init_modules */


LOCAL void exit_modules ( void )
{
	cursor_working();

	exit_module_toc();
	exit_module_par();
	exit_module_tp();

	cursor_active();

}	/* exit_modules */


/*	--------------------------------------------------------------
	check_modules_pass*() startet die Check-Funktionen der Module
	--------------------------------------------------------------	*/
LOCAL BOOLEAN check_modules_pass1 ( void )
{
	if (!check_module_toc_pass1())	return FALSE;

	return TRUE;
}	/* check_modules_pass1 */

LOCAL BOOLEAN check_modules_pass2 ( void )
{
	if (!check_module_toc_pass2())	return FALSE;

	return TRUE;
}	/* check_modules_pass2 */


/*	----------------------------------------------------------------------
	getMonth() extrahiert aus Datums-String im __DATE__-Format
	den Monat als int
	----------------------------------------------------------------------	*/
LOCAL int getMonth( const char *date_string )
{
	if( my_strnicmp(date_string, "Jan", 3)==0 )
		return 1;
	if( my_strnicmp(date_string, "Feb", 3)==0 )
		return 2;
	if( my_strnicmp(date_string, "Mar", 3)==0 )
		return 3;
	if( my_strnicmp(date_string, "Apr", 3)==0 )
		return 4;
	if( my_strnicmp(date_string, "May", 3)==0 )
		return 5;
	if( my_strnicmp(date_string, "Jun", 3)==0 )
		return 6;
	if( my_strnicmp(date_string, "Jul", 3)==0 )
		return 7;
	if( my_strnicmp(date_string, "Aug", 3)==0 )
		return 8;
	if( my_strnicmp(date_string, "Sep", 3)==0 )
		return 9;
	if( my_strnicmp(date_string, "Oct", 3)==0 )
		return 10;
	if( my_strnicmp(date_string, "Nov", 3)==0 )
		return 11;
	if( my_strnicmp(date_string, "Dec", 3)==0 )
		return 12;
	return 0;
}

/*	--------------------------------------------------------------
	Default-Werte setzen
	--------------------------------------------------------------	*/
GLOBAL void init_vars ( void )
{
	register int i;
	
	cursor_working();

	/*	--------------------------------------------------	*/
	/*	UDOs Kontrollvariablen initialisieren				*/
	/*	--------------------------------------------------	*/
	
	bNopDetected= FALSE;

	lPass1Lines=		0;
	lPass2Lines=		0;

	destlang=			TOGER;

	bInsidePopup=		FALSE;
	bInsideAppendix=	FALSE;
	bInsideDocument=	FALSE;
	
	out_lf_needed=		FALSE;

	bCmdSaved=			FALSE;
	bHpjSaved=			FALSE;
	bCntSaved=			FALSE;
	bHhpSaved=			FALSE;
	bHhcSaved=			FALSE;
	bHhkSaved=			FALSE;
	bHypSaved=			FALSE;
	bUPRSaved=			FALSE;

	iFilesOpened= 0;
	for (i=0; i<MAXFILECOUNTER; i++)
	{	uiFileLines[i]=0;
		sFileNames[i][0]= EOS;
	}

	silben_counter= 0;
	for (i=0; i<MAXSILBEN; silbe[i++][0]= EOS) ;

	memset(&styleflag, FALSE, sizeof(STYLEFLAG));

	memset(&pflag[PASS1], 0, sizeof(PASSFLAGS));
	memset(&pflag[PASS2], 0, sizeof(PASSFLAGS));

	/* Dafuer sorgen, dass alle geleert werden */
	token_counter= MAX_TOKENS-1;
	token_reset();

	/* Symbole leeren */
	udosymbol_counter= -1;
	for (i=0; i<MAX_UDOSYMBOLS; udosymbol[i++][0]= EOS) ;
	

	/*	--------------------------------------------------	*/
	/*	Dokumentvariablen und -flags initialisieren			*/
	/*	--------------------------------------------------	*/
	
	for (i=0; i<MAXSWITCH; *(udoswitch[i++].flag)= FALSE) ;

	bDocSortHyphenFile=		FALSE;
	zDocParwidth=			70;	/* Fuer ST-Guide 75 nehmen? */
	bDocTabwidth=			8;
	iDocVerbatimSize=		VERB_NORMAL;
	iDocLinedrawSize=		VERB_NORMAL;

	html_merge_node1=			FALSE;
	html_merge_node2=			FALSE;
	html_merge_node3= 			FALSE;
	html_merge_node4=			FALSE;
	html_no_xlist=				FALSE;
	html_ignore_8bit=			FALSE;	/*r6pl2*/
	html_modern_layout=			FALSE;	/*r6pl2*/
	html_modern_alignment=		ALIGN_CENT;	/*r6pl13*/
	html_frames_layout=			FALSE;	/*r6pl2*/
	html_frames_noresize=		FALSE;	/*r6pl6*/
	html_frames_noborder=		FALSE;	/*r6pl6*/
	html_frames_noscroll=		FALSE;	/*r6pl6*/
	html_frames_alignment=		ALIGN_CENT;	/*r6pl13*/
	html_nodesize=				1;
	sDocHtmlBackpage[0]=		EOS;
	sDocHtmlPropfontName[0]=	EOS;
	sDocHtmlPropfontSize[0]=	EOS;
	html_button_alignment=		ALIGN_CENT;	/*r6pl6*/
	html_use_folders=			FALSE;		/*r6pl6*/
	sDocHtmlSwitchLanguage[0]=	EOS;		/*r6pl12*/
	iDocHtmlSwitchLanguage=		-1;			/*r6pl12*/
	html_transparent_buttons=	FALSE;		/*r6pl12*/
	html_use_hyphenation=	FALSE;		/* New in r6pl16 [NHz] */
	html_doctype= HTML_TRANS;	/* New in r6pl16 [NHz] */
	
	html_ignore_p= 				FALSE;

	image_alignment=			ALIGN_LEFT;	/*r6pl9*/
	table_alignment=			ALIGN_CENT;	/*r6pl9*/

	strcpy(sDocImgSuffix, 		".gif");
	sDocBackImage[0]=			EOS;
	sDocStyle[0]=			EOS; /* New in r6pl15 [NHz] */
	sDocScript[0]=			EOS; /* New in r6pl15 [NHz] */
	sDocFavIcon[0]=			EOS; /* New in r6pl15 [NHz] */
	sDocBackColor[0]=			EOS;
	sDocTextColor[0]=			EOS;
	sDocLinkColor[0]=			EOS;
	sDocAlinkColor[0]=			EOS;
	sDocVlinkColor[0]=			EOS;
	sDocVerbatimBackColor[0]=	EOS;
	sDocRawHeaderFilename[0]=	EOS;		/*r6pl10*/
	sDocRawFooterFilename[0]=	EOS;		/*r6pl10*/

	sDocWinPrefixID[0]=			EOS;		/*r6pl13*/

	iTexVersion=			TEX_NONE;
	iTexDPI=				100;
	cTexVerb=				VERB_C;
	bTex2e=					TRUE;
	/* New in r6.2pl1 [NHz] */ 	bCalledIndex=		TRUE; 
	iDrcFlags=				0;
	
	iManPageLines=			0;
	iManPageLength=			0;
	iManPagePages=			0;
	sDocManType[0]=			EOS;
	
	bDocSloppy=				FALSE;
	bDocAutorefOff=			FALSE;
	bDocAutorefItemsOff=	FALSE;

	bDocInlineBitmaps=		FALSE;
	iDocCharwidth=			150;
	bDocHighCompression=	FALSE;
	bDocMediumCompression=	FALSE;
	bDocNoTables=			FALSE;
	bDocRtfKeepTablesOn=	FALSE;
	bDocWinOldKeywords=		FALSE;

	sDocPropfont[0]=		EOS;
	sDocMonofont[0]=		EOS;
	sDocPropfontSize[0]=	EOS;
	sDocMonofontSize[0]=	EOS;

	/* New in r6pl16 [NHz] */
	set_mainlayout();

	justify_from_right= FALSE;

	uses_udolink= FALSE;
	uses_toplink= FALSE;

	cursor_active();

	/*	--------------------------------------------------- */
	/*	Variablen für Compile-Zeit und Datum initialisieren */
	/*	--------------------------------------------------- */
	
	if( compile_date[0]=='\0' )
	{
		char date[11] = __DATE__;
		
		if( date[4]==' ' )
			date[4] = '0';

		sprintf(compile_date, "%c%c%c%c-%02i-%c%c", date[7], date[8], date[9], date[10],
			getMonth(date), date[4], date[5]);
	}
	if( compile_time[0]=='\0' )
	{
		strcpy(compile_time, __TIME__);
	}

}	/*init_vars*/




/*	######################################################################
	#
	# Dateinamen und -endungen anpassen
	#
	######################################################################	*/
LOCAL void logfile_adjust ( void )
{
	char	suff[MYFILE_SUFF_LEN+1];

	switch(desttype)
	{
		case TONRO:	strcpy(suff, ".ul1");	break;
		case TOWH4:	strcpy(suff, ".ul4");	break;
		case TOASC:	strcpy(suff, ".ula");	break;
		case TOSRC:	strcpy(suff, ".ulc");	break;
		case TODRC:	strcpy(suff, ".uld");	break;	/* r6pl2 */
		case TOPDL:	strcpy(suff, ".ulf");	break;
		case TOHPH:	strcpy(suff, ".ulg");	break;	/* Dupe! */
		case TOAMG:	strcpy(suff, ".ulg");	break;
		case TOHTM:	strcpy(suff, ".ulh");	break;
		case TOMHH:	strcpy(suff, ".ulh");	break;	/* Dupe! */
		case TOINF:	strcpy(suff, ".uli");	break;	/* Dupe! */
		case TOIPF:	strcpy(suff, ".uli");	break;	/* Dupe! */
		case TOLYX:	strcpy(suff, ".ull");	break;
		case TOMAN:	strcpy(suff, ".ulm");	break;
		case TOPCH:	strcpy(suff, ".ulp");	break;	/* Dupe! */
		case TOSRP:	strcpy(suff, ".ulp");	break;	/* Dupe! */
		case TOKPS:	strcpy(suff, ".ulp");	break;	/* Dupe! */
		case TOAQV:	strcpy(suff, ".ulq");	break;
		case TORTF:	strcpy(suff, ".ulr");	break;
		case TOSTG:	strcpy(suff, ".uls");	break;
		case TOTEX:	strcpy(suff, ".ult");	break;
		case TOUDO:	strcpy(suff, ".ulu");	break;
		case TOTVH:	strcpy(suff, ".ulv");	break;
		case TOWIN:	strcpy(suff, ".ulw");	break;
		case TOLDS:	strcpy(suff, ".ulx");	break;
		default:	strcpy(suff, ".log");	break;
	}

	sprintf(sLogfull, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, suff);

}	/* logfile_adjust */




GLOBAL void dest_special_adjust ( void )
{

	/* -------------------------------------------------- */
	/* Endung und Dateinamen des Logfiles setzen          */
	/* -------------------------------------------------- */
	sLogfull[0]= EOS;
	logfile_adjust();

	/* -------------------------------------------------- */
	/* Endung des Treefiles setzen (wie logfile, nur 't') */
	/* -------------------------------------------------- */
	strcpy(sTreefull, sLogfull);
	sTreefull[strlen(sTreefull)-2]= 't';

	/* -------------------------------------------------- */
	/* Endung des Indexfiles setzen (wie oben, nur 'x')   */
	/* -------------------------------------------------- */
	strcpy(sIdxfull, sLogfull);
	sIdxfull[strlen(sIdxfull)-2]= 'x';

	/* ------------------------------------------------- */
	/* Endung des Hypfiles setzen (wie logfile, nur 'h') */
	/* ------------------------------------------------- */
	sHypfull[0]= EOS;
	switch(desttype)
	{	case TOASC:
		case TODRC:
		case TOMAN:
		case TOSTG:
		case TOAMG:
		case TOPCH:
			strcpy(sHypfull, sLogfull);
			sHypfull[strlen(sHypfull)-2]= 'h';
			break;
	}

	/* -------------------------------------------------- */
	/* Restliche Dateinamen setzen						  */
	/* -------------------------------------------------- */
	sprintf(sCmdfull, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".cmd");
	sprintf(sMapNoSuff, "%s%s%s", outfile.driv, outfile.path, outfile.name);
	sprintf(sHpjfull, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".hpj");
	sprintf(sCntfull, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".cnt");
	sprintf(sHhpfull, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".hhp");
	sprintf(sHhcfull, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".hhc");
	sprintf(sHhkfull, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".hhk");
	sprintf(sUPRfull, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".upr");
	sprintf(sGifHmFull, "%s%s%s", outfile.driv, outfile.path, GIF_HM_NAME);
	sprintf(sGifUpFull, "%s%s%s", outfile.driv, outfile.path, GIF_UP_NAME);
	sprintf(sGifLfFull, "%s%s%s", outfile.driv, outfile.path, GIF_LF_NAME);
	sprintf(sGifRgFull, "%s%s%s", outfile.driv, outfile.path, GIF_RG_NAME);
	sprintf(sGifNoHmFull, "%s%s%s", outfile.driv, outfile.path, GIF_NOHM_NAME);
	sprintf(sGifNoUpFull, "%s%s%s", outfile.driv, outfile.path, GIF_NOUP_NAME);
	sprintf(sGifNoLfFull, "%s%s%s", outfile.driv, outfile.path, GIF_NOLF_NAME);
	sprintf(sGifNoRgFull, "%s%s%s", outfile.driv, outfile.path, GIF_NORG_NAME);
	sprintf(sGifTpFull, "%s%s%s", outfile.driv, outfile.path, GIF_TP_NAME);
	sprintf(sGifFoFull, "%s%s%s", outfile.driv, outfile.path, GIF_FO_NAME);
	sprintf(sGifFcFull, "%s%s%s", outfile.driv, outfile.path, GIF_FC_NAME);
	sprintf(sGifFsFull, "%s%s%s", outfile.driv, outfile.path, GIF_FS_NAME);
	sprintf(sGifMwFull, "%s%s%s", outfile.driv, outfile.path, GIF_MW_NAME);
	sprintf(sGifGerFull, "%s%s%s", outfile.driv, outfile.path, GIF_GER_NAME);
	sprintf(sGifEngFull, "%s%s%s", outfile.driv, outfile.path, GIF_ENG_NAME);
	sprintf(sBmpFoFull, "%s%s%s", outfile.driv, outfile.path, BMP_FO_NAME);
	sprintf(sBmpFcFull, "%s%s%s", outfile.driv, outfile.path, BMP_FC_NAME);
	sprintf(sBmpMwFull, "%s%s%s", outfile.driv, outfile.path, BMP_MW_NAME);
	sprintf(sImgFoFull, "%s%s%s", outfile.driv, outfile.path, IMG_FO_NAME);
	sprintf(sImgFcFull, "%s%s%s", outfile.driv, outfile.path, IMG_FC_NAME);
	sprintf(sImgMwFull, "%s%s%s", outfile.driv, outfile.path, IMG_MW_NAME);

}	/* dest_special_adjust */


GLOBAL void dest_adjust ( void )
{
	char html_suff[12], texi_suff[12], sgml_suff[12], guide_suff[12];

#if	USE_LONG_FILENAMES
	if (!bForceShort)	/*r6pl13*/
	{	strcpy(html_suff, ".html");
		strcpy(texi_suff, ".texi");
		strcpy(sgml_suff, ".sgml");
		strcpy(guide_suff, ".guide");
	}
	else
	{	strcpy(html_suff, ".htm");
		strcpy(texi_suff, ".tex");
		strcpy(sgml_suff, ".sgm");
		strcpy(guide_suff, ".gui");
	}
#else
	if (bForceLong)	/*r6pl2*/
	{	strcpy(html_suff, ".html");
		strcpy(texi_suff, ".texi");
		strcpy(sgml_suff, ".sgml");
		strcpy(guide_suff, ".guide");
	}
	else
	{	strcpy(html_suff, ".htm");
		strcpy(texi_suff, ".tex");
		strcpy(sgml_suff, ".sgm");
		strcpy(guide_suff, ".gui");
	}
#endif

	if (config.bDestAdjustAll)
	{	strcpy(outfile.driv, infile.driv);
		strcpy(outfile.path, infile.path);
	}
	
	if (!config.bDestAdjustSuff)
	{	strcpy(outfile.name, infile.name);
	}

	switch(desttype)
	{	case TOASC:	strcpy(outfile.suff, ".txt");		break;
		case TODRC:	strcpy(outfile.suff, ".drc");		break;
		case TOMAN:	strcpy(outfile.suff, ".man");		break;
		case TONRO:	strcpy(outfile.suff, ".1");			break;
		case TOSTG:	strcpy(outfile.suff, ".stg");		break;
		case TOAMG:	strcpy(outfile.suff, guide_suff);	break;
		case TOTEX:	strcpy(outfile.suff, ".tex");		break;
		case TOPDL:	strcpy(outfile.suff, ".tex");		break;
		case TOINF:	strcpy(outfile.suff, texi_suff);	break;
		case TOIPF:	strcpy(outfile.suff, ".ipf");		break;
		case TORTF:	strcpy(outfile.suff, ".rtf");		break;
		case TOAQV: strcpy(outfile.suff, ".rtf");		break;
		case TOWIN:	strcpy(outfile.suff, ".rtf");		break;
		case TOWH4:	strcpy(outfile.suff, ".rtf");		break;
		case TOPCH:	strcpy(outfile.suff, ".scr");		break;
		case TOTVH:	strcpy(outfile.suff, ".txt");		break;
		case TOHTM:	strcpy(outfile.suff, html_suff);	break;
		case TOMHH:	strcpy(outfile.suff, html_suff);	break;
		case TOLDS:	strcpy(outfile.suff, sgml_suff);	break;
		case TOHPH:	strcpy(outfile.suff, sgml_suff);	break;
		case TOLYX:	strcpy(outfile.suff, ".lyx");		break;
		case TOSRC:	strcpy(outfile.suff, ".c");			break;
		case TOSRP:	strcpy(outfile.suff, ".pas");		break;
		case TOUDO:	strcpy(outfile.suff, ".udo");		break;
		case TOKPS:	strcpy(outfile.suff, ".ps");		break;
		default:	outfile.suff[0]= EOS;
	}

	if (config.bDestLowerFile)
	{	my_strlwr(outfile.name);
	}
	if (config.bDestLowerPath)
	{	my_strlwr(outfile.path);
	}

	sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);

	dest_special_adjust();	
}	/* dest_adjust */


/*	######################################################################
	# udo.c
	######################################################################	*/
