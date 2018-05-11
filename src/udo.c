/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : udo.c
*  Symbol prefix: udo
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
*  Co-Authors   : Volker Jansen (vj), Martin Osaka (MO), Christof Schardt (CS),
*                 Ulf Dunkel (fd), Gerhard Stoll (ggs)
*  Write access : fd, ggs
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - Check if UDOCOMMAND.reset should really be in structure;
*                   there is only one command ("!item") which should not be reset!
*
*                 - str_for_os(): check if preprocessor commands are really required!
*
*                 - check if c_heading(), c_subheading(), etc. can be merged
*
*-------------------------------------------------------------------------------
*  History:
*
*  1995:
*    DH  Jan xx: introduced
*  2001:
*    DH  Oct 02: last DH version
*  2008:
*    fd  Nov 14: TOPOL introduced
*  2009:
*    ggs Jan 11: Change year
*    fd  Jun 08: TAB -> '   ', reformattings
*  2010:
*    fd  Jan 20: set_html_quotes()
*    fd  Jan 23: - partly reformatted
*                - converted all German umlauts in comments into plain ASCII
*    fd  Jan 28: c_subsubsubsubheading() adjusted
*    fd  Jan 29: file reformatted and tidied up
*    fd  Feb 05: pass1(): bugfix for issue #77
*    fd  Feb 08: description environment items are no longer closed here, but in ENV.C
*    fd  Feb 12: some octal chars resolved into constant macros
*    fd  Feb 15: - new: !code_source [] + c_code_source() -> iEncodingSource
*                - new: !code_target [] + c_code_target() -> iEncodingTarget
*    fd  Feb 16: udocharset: "cp1250" added
*    fd  Feb 17: - ansi2dos() removed
*                - win2sys() -> recode_chrtab()
*                - umlaute2sys() merged into recode_chrtab()
*    fd  Feb 18: CODE_LAT2
*    fd  Feb 19: - CODE_CP1257; MAXCHARSET removed; udocharset[] resorted for relevance
*                - c_universal_charset() debugged
*    fd  Feb 20: CODE_CP1251
*    fd  Feb 22: - VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*                - CODE_CP1253 (Greek)
*    fd  Feb 23: - CODE_MAC_CE
*                - CODE_LAT1 -> CODE_CP1252
*                - CODE_LAT2 -> CODE_LATIN2
*                - CODE_LATIN1
*                - UDO_PL -> UDO_BUILD (no more patchlevels)
*                - adjustments from Xcode's complaints for stricmp()
*    fd  Feb 24: - CODE_CP1254 (Turkish)
*                - CODE_CP1255 (Hebrew)
*                - CODE_CP1256 (Arabic)
*                - CODE_CP1258 (Vietnamese)
*                - udocharset[]: more mnemonics as used in Unix command iconv
*    fd  Feb 26: token_output() no longer adds ' ' behind placeholder token (issue #12)
*    fd  Feb 27: HTML output for ENV_DESC, ENV_LIST + other environments adjusted
*    fd  Mar 01: new: use_short_itemizes
*                     use_short_enumerates
*                     use_short_descriptions
*                     use_short_lists
*                !code command and c_code() function removed -> code_source
*    fd  Mar 03: pass_check_if() debugged - #86 fixed
*    fd  Mar 04: token_output(): inside_short -> inside_compressed
*    fd  Mar 05: - CODE_LATIN3
*                - CODE_LATIN4
*                - CODE_CYRILLIC
*                - CODE_ARABIC
*                - CODE_HEBREW
*    fd  Mar 08: - CODE_TURKISH
*                - CODE_NORDIC
*                - CODE_THAI
*                - CODE_BALTIC
*                - CODE_CELTIC
*                - CODE_LATIN9
*                - CODE_LATIN10
*                - c_code_source() + c_code_target() adjusted
*    fd  Mar 12: adjustments for Linux gcc
*    ggs Mar 28: token_output: Compressed works for ASCII, ST-Guide and AmigaGuide again
*    ggs Mar 29: token_output: I hope compressed work in all formats again
*    ggs Apr 21: - use_short_tocs -> use_compressed_tocs
*                - Labels inside tables work now in HTML
*    fd  May 18: pass1_check_preamble_commands(): html_ignore_8bit_use_charset no longer required
*    fd  May 19: !use_short_... commands are no longer supported
*    fd  May 20: - typo in udocharset[windows-1252] fixed
*                - token_output(): some adjustments for description item output in KPS
*    fd  May 21: new: label* | l*  (#90)
*  2011:
*    fd  Feb 14: - pass1() handles "!subsubsubsubnode" and its derivates (finally)
*                - copyright year updated
*    fd  Feb 19: output_preamble(): TeX supports utf8 package [#96 fixed]
*  2013:
*    fd  Feb 15: Japanese added (TOJAP, etc.)
*    ggs Mar 03: copyright year updated
*    fd  Oct 23: - image output supports HTML5
*                - tags who used align or valign attrs now use class names, like
*                - <div> on HTML5 now uses class UDO_div_align_center| UDO_div_align_right
*                - <p>   on HTML5 now uses class UDO_p_align_center  | UDO_p_align_right
*                - <td>  on HTML5 now uses class UDO_td_align_center | UDO_td_align_right
*    fd  Oct 31: c_gif_output() renamed: c_html_image_output()
*  2014
*    ggs Apr 16: copyright year updated
*    ggs Apr 20: Add Node6
*  2015:
*    fd  Feb 25: malloc_token_output_buffer(): tomaxlen increased from 200 to 256
*  2017:
*    fd  Feb 07: "russian" added
*    fd  Feb 08: save_htmlhelp_project() adjusted
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
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include "udoport.h"

#include "version.h"					/* WICHTIGE Makros! */
#include "constant.h"					/* WICHTIGE Makros! */
#include "commands.h"					/* UDO-Kommandos */
#include "udo_type.h"					/* diverse Typen */
#include "udointl.h"

#include "abo.h"						/* Ausgabe einer Infoseite */
#include "cfg.h"						/* Konfiguration lesen/schreiben */
#include "chr.h"						/* Zeichensatzumwandlungen */
#include "env.h"						/* Umgebungen verwalten */
#include "file.h"						/* Aufsplitten von Dateinamen */
#include "img.h"						/* Ausgabe/Einbindung von Grafiken */
#include "lang.h"						/* ausgewaehlte Sprache */
#include "msg.h"						/* Fehlermeldungen erzeugen */
#include "par.h"						/* (!...) Parameter bearbeiten */
#include "str.h"						/* Manipulation von Strings */
#include "sty.h"						/* Textstilumwandlungen */
#include "tab.h"						/* Tabellensatz */
#include "toc.h"						/* !node, !alias, !label, !toc */
#include "toc_html.h"					/* HTML parts for !node, !alias, !label, !toc */
#include "tp.h"							/* Titelseite (!maketitle) */

#include "gui.h"						/* Funktionen GUI-/CLI-Version */
#include "udosym.h"						/* Symbole */
#include "debug.h"						/* Debugging */
#include "udomem.h"						/* Memory-Management */
#include "upr.h"

#include "export.h"
#include "udo.h"						/* globale Prototypen */





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#ifdef __MACOS__
# define NL "\n\r"						/* solange es keinen HCP auf dem Mac gibt notwendig */
#else
# define NL "\n"
#endif

/* IF-Stack fuer !if-Umgebungen sowie Flags fuer pass1() und pass2() */
#define IF_NONE        0
#define IF_GENERAL     1
#define IF_DEST        2
#define IF_LANG        3
#define IF_SET         4
#define IF_OS          5

#define MAX_IF_STACK  32

#define CMD_ALWAYS          0			/* used in UDO function table */
#define CMD_ONLY_PREAMBLE   1
#define CMD_ONLY_MAINPART   2





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _if_stack_item
{
	int kind;
	_BOOL ignore;
	FILE_LOCATION loc;
} IF_STACK_ITEM;

typedef struct _hyplist
{
	char data[128];
	struct _hyplist *next;
} HYPLIST;

typedef struct _idxlist
{
	char letter;						/* Hier soll der Eintrag einsortiert werden */
	int depth;							/* Indextiefe: 1, 2 oder 3 */
	char chapter[MAX_NODE_LEN + 1];		/* In diesem Kapitel gesetzt */
	char idx[3][128];					/* Die Index-Daten */
	struct _idxlist *next;
} IDXLIST;

typedef void (*CMDPROC) (void);

typedef struct _udocommand				/* ---- Funktionentabelle ---- */
{
	const char *magic;					/* command name, including leading "!" */
	const char *macut;					/* abbreviation, including leading "!" (optional) */
	CMDPROC proc;						/* function to be called in pass2() */
	_BOOL reset;						/* clear tokens after command? */
	int pos;							/* possible positions (CMD_* above) */
} UDOCOMMAND;

#define MAX_UDOCOLOR 17


typedef struct _udocharset				/* list of encoding mnemonics */
{
	const char *magic;					/* encoding mnemonic */
	int codepage;						/* relevant encoding # */
} UDOCHARSET;


LOCAL UDOCHARSET const udocharset[] =	/* list of encoding mnemonics */
{
	{ "sys", SYSTEM_CHARSET },

	{ "utf-8", CODE_UTF8 },
	{ "utf8", CODE_UTF8 },

	{ "cp1250", CODE_CP1250 },
	{ "ms-ee", CODE_CP1250 },
	{ "windows-1250", CODE_CP1250 },

	{ "cp1251", CODE_CP1251 },
	{ "ms-cyrl", CODE_CP1251 },
	{ "windows-1251", CODE_CP1251 },
	{ "russian", CODE_CP1251 },

	{ "cp1252", CODE_CP1252 },
	{ "ms-ansi", CODE_CP1252 },
	{ "windows-1252", CODE_CP1252 },
	{ "WIN", CODE_CP1252 },
	{ "iso", CODE_CP1252},				/* Version 6.xx compatibility, deprecated */

	{ "cp1253", CODE_CP1253 },
	{ "greek", CODE_CP1253 },
	{ "ms-greek", CODE_CP1253 },
	{ "windows-1253", CODE_CP1253 },

	{ "CP1254", CODE_CP1254 },
	{ "ms-turk", CODE_CP1254 },
	{ "turkish", CODE_CP1254 },
	{ "windows-1254", CODE_CP1254 },

	{ "cp1255", CODE_CP1255 },
	{ "hebrew", CODE_CP1255 },
	{ "ms-hebr", CODE_CP1255 },
	{ "windows-1255", CODE_CP1255 },

	{ "cp1256", CODE_CP1256 },
	{ "arabic", CODE_CP1256 },
	{ "ms-arab", CODE_CP1256 },
	{ "windows-1256", CODE_CP1256 },

	{ "cp1257", CODE_CP1257 },
	{ "baltic", CODE_CP1257 },
	{ "winbaltrim", CODE_CP1257 },
	{ "windows-1257", CODE_CP1257 },

	{ "cp1258", CODE_CP1258 },
	{ "windows-1258", CODE_CP1258 },

	{ "iso-8859-1", CODE_LATIN1},		/* beware: UDO6 used CP1252 here */
	{ "iso-ir-100", CODE_LATIN1 },
	{ "iso8859-1", CODE_LATIN1 },
	{ "iso_8859-1", CODE_LATIN1 },
	{ "latin1", CODE_LATIN1 },			/* beware: UDO6 used CP1252 here */
	{ "l1", CODE_LATIN1 },
	{ "csisolatin1", CODE_LATIN1 },

	{ "iso-8859-2", CODE_LATIN2 },
	{ "iso-ir-101", CODE_LATIN2 },
	{ "iso8859-2", CODE_LATIN2 },
	{ "iso_8859-2", CODE_LATIN2 },
	{ "latin2", CODE_LATIN2 },
	{ "l2", CODE_LATIN2 },
	{ "csisolatin2", CODE_LATIN2 },

	{ "iso-8859-3", CODE_LATIN3 },
	{ "iso-ir-109", CODE_LATIN3 },
	{ "iso8859-3", CODE_LATIN3 },
	{ "iso_8859-3", CODE_LATIN3 },
	{ "latin3", CODE_LATIN3 },
	{ "l3", CODE_LATIN3 },
	{ "csisolatin3", CODE_LATIN3 },

	{ "iso-8859-4", CODE_LATIN4 },
	{ "iso-ir-110", CODE_LATIN4 },
	{ "iso8859-4", CODE_LATIN4 },
	{ "iso_8859-4", CODE_LATIN4 },
	{ "latin4", CODE_LATIN4 },
	{ "l4", CODE_LATIN4 },
	{ "csisolatin4", CODE_LATIN4 },

	{ "iso-8859-5", CODE_CYRILLIC },
	{ "iso-ir-144", CODE_CYRILLIC },
	{ "iso8859-5", CODE_CYRILLIC },
	{ "iso_8859-5", CODE_CYRILLIC },
	{ "cyrillic", CODE_CYRILLIC },
	{ "csisolatincyrillic", CODE_CYRILLIC },

	{ "iso-8859-6", CODE_ARABIC },
	{ "iso-ir-127", CODE_ARABIC },
	{ "iso8859-6", CODE_ARABIC },
	{ "iso_8859-6", CODE_ARABIC },
	{ "arabic", CODE_ARABIC },
	{ "csisolatinarabic", CODE_ARABIC },
	{ "asmo-708", CODE_ARABIC },
	{ "ecma-114", CODE_ARABIC },

	{ "iso-8859-7", CODE_GREEK },
	{ "iso-ir-126", CODE_GREEK },
	{ "iso8859-7", CODE_GREEK },
	{ "iso_8859-7", CODE_GREEK },
	{ "greek", CODE_GREEK },
	{ "greek8", CODE_GREEK },
	{ "csisolatingreek", CODE_GREEK },
	{ "ecma-118", CODE_GREEK },
	{ "elot_928", CODE_GREEK },

	{ "iso-8859-8", CODE_HEBREW },
	{ "iso-ir-138", CODE_HEBREW },
	{ "iso8859-8", CODE_HEBREW },
	{ "iso_8859-8", CODE_HEBREW },
	{ "hebrew", CODE_HEBREW },
	{ "csisolatinhebrew", CODE_HEBREW },

	{ "iso-8859-9", CODE_TURKISH },
	{ "iso-ir-148", CODE_TURKISH },
	{ "iso8859-9", CODE_TURKISH },
	{ "iso_8859-9", CODE_TURKISH },
	{ "latin5", CODE_TURKISH },
	{ "l5", CODE_TURKISH },
	{ "csisolatin5", CODE_TURKISH },
	{ "turkish", CODE_TURKISH },

	{ "iso-8859-10", CODE_NORDIC },
	{ "iso-ir-157", CODE_NORDIC },
	{ "iso8859-10", CODE_NORDIC },
	{ "iso_8859-10", CODE_NORDIC },
	{ "latin6", CODE_NORDIC },
	{ "l6", CODE_NORDIC },
	{ "csisolatin6", CODE_NORDIC },
	{ "nordic", CODE_NORDIC },

	{ "iso-8859-11", CODE_THAI },
	{ "iso8859-11", CODE_THAI },
	{ "iso_8859-11", CODE_THAI },
	{ "thai", CODE_THAI },

	{ "iso-8859-13", CODE_BALTIC },
	{ "iso-ir-179", CODE_BALTIC },
	{ "iso8859-13", CODE_BALTIC },
	{ "iso_8859-13", CODE_BALTIC },
	{ "latin7", CODE_BALTIC },
	{ "l7", CODE_BALTIC },
	{ "csisolatin7", CODE_BALTIC },
	{ "baltic", CODE_BALTIC },

	{ "iso-8859-14", CODE_CELTIC },
	{ "iso-ir-199", CODE_CELTIC },
	{ "iso8859-14", CODE_CELTIC },
	{ "iso_8859-14", CODE_CELTIC },
	{ "latin8", CODE_CELTIC },
	{ "l8", CODE_CELTIC },
	{ "csisolatin8", CODE_BALTIC },
	{ "iso-celtic", CODE_CELTIC },
	{ "celtic", CODE_CELTIC },

	{ "iso-8859-15", CODE_LATIN9 },
	{ "iso-ir-203", CODE_LATIN9 },
	{ "iso8859-15", CODE_LATIN9 },
	{ "iso_8859-15", CODE_LATIN9 },
	{ "latin9", CODE_LATIN9 },
	{ "l9", CODE_LATIN9 },
	{ "csisolatin9", CODE_LATIN9 },

	{ "iso-8859-16", CODE_LATIN10 },
	{ "iso-ir-226", CODE_LATIN10 },
	{ "iso8859-16", CODE_LATIN10 },
	{ "iso_8859-16", CODE_LATIN10 },
	{ "latin10", CODE_LATIN10 },
	{ "l10", CODE_LATIN10 },
	{ "csisolatin10", CODE_LATIN10 },

	{ "mac", CODE_MAC },					/* Version 6.xx compatibility, deprecated */
	{ "macintosh", CODE_MAC },
	{ "macroman", CODE_MAC },
	{ "csmacintosh", CODE_MAC },

	{ "mac_ce", CODE_MAC_CE },
	{ "maccentraleurope", CODE_MAC_CE },

	{ "tos", CODE_TOS },					/* non-standard iconv name(s); iconv does not know about Atari codepage */
	{ "atari", CODE_TOS },
	{ "atarist", CODE_TOS },

	{ "437", CODE_437 },
	{ "cp437", CODE_437 },
	{ "ibm437", CODE_437 },
	{ "cspc8codepage437", CODE_437 },
	{ "dos", CODE_437 },					/* Version 6.xx compatibility, deprecated */

	{ "850", CODE_850 },
	{ "cp850", CODE_850 },
	{ "ibm850", CODE_850 },
	{ "cspc850multilingual", CODE_850 },
	{ "os2", CODE_850 },					/* Version 6.xx compatibility, deprecated */

	{ "hp8", CODE_HP8 },					/* Version 6.xx compatibility, deprecated */
	{ "hp-roman8", CODE_HP8 },
	{ "r8", CODE_HP8 },
	{ "roman8", CODE_HP8 },
	{ "cshproman8", CODE_HP8 },

	{ "next", CODE_NEXT },
	{ "nextstep", CODE_NEXT }
};





/*******************************************************************************
*
*     INITIALIZED LOCAL VARIABLES
*
******************************************|************************************/

/*
 * Builtin color table for default text/background/linkcolor.
 * The mnemonic are according to W3C HTML3.2 DTD,
 * and should match the style commands, (!green) etc.
 * For RTF output, the color numbers MUST match those written
 * out to the \colortbl in env.c.
 */
UDOCOLOR const udocolor[MAX_UDOCOLOR] = {
	{ BC_BLACK,   "black",   { 0,   0,   0,   0 }, "\003@", "\\cf1" },
	{ BC_SILVER,  "silver",  { 0, 192, 192, 192 }, "\003G", "\\cf2" },
	{ BC_GRAY,    "gray",    { 0, 128, 128, 128 }, "\003H", "\\cf3" },
	{ BC_WHITE,   "white",   { 0, 255, 255, 255 }, "\003O", "\\cf4" },
	{ BC_MAROON,  "maroon",  { 0, 128,   0,   0 }, "\003D", "\\cf5" },
	{ BC_RED,     "red",     { 0, 255,   0,   0 }, "\003L", "\\cf6" },
	{ BC_PURPLE,  "purple",  { 0, 128,   0, 128 }, "\003E", "\\cf7" },
	{ BC_FUCHSIA, "fuchsia", { 0, 255,   0, 255 }, "\003M", "\\cf8" },
	{ BC_GREEN,   "green",   { 0,   0, 128,   0 }, "\003B", "\\cf9" },
	{ BC_LIME,    "lime",    { 0,   0, 255,   0 }, "\003J", "\\cf10" },
	{ BC_OLIVE,   "olive",   { 0, 128, 128,   0 }, "\003J", "\\cf11" },
	{ BC_YELLOW,  "yellow",  { 0, 255, 255,   0 }, "\003N", "\\cf12" },
	{ BC_NAVY,    "navy",    { 0,   0,   0, 128 }, "\003A", "\\cf13" },
	{ BC_BLUE,    "blue",    { 0,   0,   0, 255 }, "\003I", "\\cf14" },
	{ BC_TEAL,    "teal",    { 0,   0, 128, 128 }, "\003B", "\\cf15" },
	{ BC_AQUA,    "aqua",    { 0,   0, 255, 255 }, "\003C", "\\cf16" },
	{ BC_NONE,    "none",    { 0,   0,   0,   0 }, "", "" }
};





/*******************************************************************************
*
*     UNINITIALIZED LOCAL VARIABLES
*
******************************************|************************************/

#include "udolocal.h"					/* local prototypes */

LOCAL _BOOL format_needs_exact_toklen;
LOCAL _BOOL format_uses_output_buffer;
LOCAL _BOOL format_protect_commands;

LOCAL _BOOL out_lf_needed;				/* Fehlt noch ein Linefeed? */
FILE_LINENO outlines;					/* Anzahl gesicherter Zeilen */

LOCAL char *tobuffer;					/* Puffer fuer token_output() */

LOCAL _BOOL bDocSloppy;					/* Kurze Zeilen bemaengeln? */
LOCAL _BOOL no_verbatim_umlaute;		/* In verbatim Umlaute entfernen? */
LOCAL _BOOL use_output_buffer;			/* Erst puffern, dann ausgeben? */

LOCAL char timer_start[16];				/* Uhrzeiten fuer Start und Stopp */
LOCAL char timer_stop[16];

LOCAL char silbe[MAXSILBEN][MAX_TOKEN_LEN + 1];	/* Ein Array mit Silben */
LOCAL int silben_counter;				/* Der passende Zaehler */

LOCAL _BOOL bHypSaved;
LOCAL _BOOL bIdxSaved;
LOCAL _BOOL bTreeSaved;
LOCAL _BOOL bCmdSaved;
LOCAL _BOOL bHpjSaved;
LOCAL _BOOL bCntSaved;
LOCAL _BOOL bUPRSaved;
LOCAL _BOOL bMapSavedC;
LOCAL _BOOL bMapSavedPas;
LOCAL _BOOL bMapSavedVB;
LOCAL _BOOL bMapSavedGFA;
LOCAL _BOOL bHhpSaved;
LOCAL _BOOL bHhcSaved;
LOCAL _BOOL bHhkSaved;

LOCAL int iFilesOpened;					/* depth of !include stack */
LOCAL struct
{
	FILE_LOCATION loc;					/* Zeilen geoeffneter Files */
	MYTEXTFILE *file;
} uiFiles[MAXFILECOUNTER + 1];

LOCAL IF_STACK_ITEM if_stack[MAX_IF_STACK + 1];

LOCAL int counter_if_stack;

LOCAL FILE_LINENO lPass1Lines, lPass2Lines;		/* fuer die Prozentangabe */

LOCAL HYPLIST *hyplist;
LOCAL IDXLIST *idxlist;


/*******************************************************************************
*
*     UDO FUNCTION TABLE
*     ==================
*
*     Note:
*     Die Tabellen sollten nach der Wahrscheinlichkeit sortiert
*     werden, mit dem ein Kommando aufgerufen wird, um Suchzeiten
*     zu verringern. Die Kapitel-Kommandos sollten dabei ganz
*     oben stehen, weniger gebraeuchliche Kommandos ganz zum Schluss.
*
******************************************|************************************/

LOCAL const UDOCOMMAND udoCmdSeq[] = {
	{ "!node",                           "!n",            c_node,                          TRUE,  CMD_ONLY_MAINPART },
	{ "!subnode",                        "!sn",           c_subnode,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubnode",                     "!ssn",          c_subsubnode,                    TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubnode",                  "!sssn",         c_subsubsubnode,                 TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubnode",               "!ssssn",        c_subsubsubsubnode,              TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubnode",            "!sssssn",       c_subsubsubsubsubnode,           TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubnode",         "!ssssssn",      c_subsubsubsubsubsubnode,        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubsubnode",      "!sssssssn",     c_subsubsubsubsubsubsubnode,     TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubsubsubnode",   "!ssssssssn",    c_subsubsubsubsubsubsubsubnode,  TRUE,  CMD_ONLY_MAINPART },
	{ "!node*",                          "!n*",           c_node_iv,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!subnode*",                       "!sn*",          c_subnode_iv,                    TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubnode*",                    "!ssn*",         c_subsubnode_iv,                 TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubnode*",                 "!sssn*",        c_subsubsubnode_iv,              TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubnode*",              "!ssssn*",       c_subsubsubsubnode_iv,           TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubnode*",           "!sssssn*",      c_subsubsubsubsubnode_iv,        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubnode*",        "!ssssssn*",     c_subsubsubsubsubsubnode_iv,     TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubsubnode*",     "!sssssssn*",    c_subsubsubsubsubsubsubnode_iv,  TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubsubsubnode*",  "!ssssssssn*",   c_subsubsubsubsubsubsubsubnode_iv, TRUE, CMD_ONLY_MAINPART },
	{ "!pnode",                          "!p",            c_pnode,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!psubnode",                       "!ps",           c_psubnode,                      TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubnode",                    "!pss",          c_psubsubnode,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubnode",                 "!psss",         c_psubsubsubnode,                TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubnode",              "!pssss",        c_psubsubsubsubnode,             TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubsubnode",           "!psssss",       c_psubsubsubsubsubnode,          TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubsubsubnode",        "!pssssss",      c_psubsubsubsubsubsubnode,       TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubsubsubsubnode",     "!psssssss",     c_psubsubsubsubsubsubsubnode,    TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubsubsubsubsubnode",  "!pssssssss",    c_psubsubsubsubsubsubsubsubnode, TRUE,  CMD_ONLY_MAINPART },
	{ "!pnode*",                         "!p*",           c_pnode_iv,                      TRUE,  CMD_ONLY_MAINPART },
	{ "!psubnode*",                      "!ps*",          c_psubnode_iv,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubnode*",                   "!pss*",         c_psubsubnode_iv,                TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubnode*",                "!psss*",        c_psubsubsubnode_iv,             TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubnode*",             "!pssss*",       c_psubsubsubsubnode_iv,          TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubsubnode*",          "!psssss*",      c_psubsubsubsubsubnode_iv,       TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubsubsubnode*",       "!pssssss*",     c_psubsubsubsubsubsubnode_iv,    TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubsubsubsubnode*",    "!psssssss*",    c_psubsubsubsubsubsubsubnode_iv, TRUE,  CMD_ONLY_MAINPART },
	{ "!psubsubsubsubsubsubsubsubnode*", "!pssssssss*",   c_psubsubsubsubsubsubsubsubnode_iv, TRUE, CMD_ONLY_MAINPART },
	{ "!begin_node",                     "!bn",           c_begin_node,                    TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_node*",                    "!bn*",          c_begin_node_iv,                 TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_pnode",                    "!bp",           c_begin_pnode,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_pnode*",                   "!bp*",          c_begin_pnode_iv,                TRUE,  CMD_ONLY_MAINPART },
	{ "!end_node",                       "!en",           c_end_node,                      TRUE,  CMD_ONLY_MAINPART },
	{ "!item",                           "!i",            c_item,                          FALSE, CMD_ONLY_MAINPART },
	{ "!begin_itemize",                  "!bi",           c_begin_itemize,                 TRUE,  CMD_ONLY_MAINPART },
	{ "!end_itemize",                    "!ei",           c_end_itemize,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_enumerate",                "!be",           c_begin_enumerate,               TRUE,  CMD_ONLY_MAINPART },
	{ "!end_enumerate",                  "!ee",           c_end_enumerate,                 TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_description",              "!bd",           c_begin_description,             TRUE,  CMD_ONLY_MAINPART },
	{ "!end_description",                "!ed",           c_end_description,               TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_xlist",                    "!bxl",          c_begin_xlist,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!end_xlist",                      "!exl",          c_end_xlist,                     TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_blist",                    "!bbl",          c_begin_blist,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!end_blist",                      "!ebl",          c_end_blist,                     TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_ilist",                    "!bil",          c_begin_ilist,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!end_ilist",                      "!eil",          c_end_ilist,                     TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_tlist",                    "!btl",          c_begin_tlist,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!end_tlist",                      "!etl",          c_end_tlist,                     TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_quote",                    "!bq",           c_begin_quote,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!end_quote",                      "!eq",           c_end_quote,                     TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_center",                   "!bc",           c_begin_center,                  TRUE,  CMD_ONLY_MAINPART },
	{ "!end_center",                     "!ec",           c_end_center,                    TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_flushright",               "!bfr",          c_begin_flushright,              TRUE,  CMD_ONLY_MAINPART },
	{ "!end_flushright",                 "!efr",          c_end_flushright,                TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_flushleft",                "!bfl",          c_begin_flushleft,               TRUE,  CMD_ONLY_MAINPART },
	{ "!end_flushleft",                  "!efl",          c_end_flushleft,                 TRUE,  CMD_ONLY_MAINPART },
	{ "!label",                          "!l",            c_label,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!label*",                         "!l*",           c_label_iv,                      TRUE,  CMD_ONLY_MAINPART },
	{ "!label-",                         "",              c_label,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!alias",                          "!a",            c_alias,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!alias-",                         "!a-",           c_alias,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!index",                          "!x",            c_index,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!heading",                        "!h",            c_heading,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!subheading",                     "!sh",           c_subheading,                    TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubheading",                  "!ssh",          c_subsubheading,                 TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubheading",               "!sssh",         c_subsubsubheading,              TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubheading",            "!ssssh",        c_subsubsubsubheading,           TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubheading",         "!sssssh",       c_subsubsubsubsubheading,        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubheading",      "!ssssssh",      c_subsubsubsubsubsubheading,     TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubsubheading",   "!sssssssh",     c_subsubsubsubsubsubsubheading,  TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubsubsubheading","!ssssssssh",    c_subsubsubsubsubsubsubsubheading, TRUE, CMD_ONLY_MAINPART },
	{ "!listheading",                    "!lh",           c_listheading,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!listsubheading",                 "!lsh",          c_listsubheading,                TRUE,  CMD_ONLY_MAINPART },
	{ "!listsubsubheading",              "!lssh",         c_listsubsubheading,             TRUE,  CMD_ONLY_MAINPART },
	{ "!listsubsubsubheading",           "!lsssh",        c_listsubsubsubheading,          TRUE,  CMD_ONLY_MAINPART },
	{ "!listsubsubsubsubheading",        "!lssssh",       c_listsubsubsubsubheading,       TRUE,  CMD_ONLY_MAINPART },
	{ "!listsubsubsubsubsubheading",     "!lsssssh",      c_listsubsubsubsubsubheading,    TRUE,  CMD_ONLY_MAINPART },
	{ "!listsubsubsubsubsubsubheading",  "!lssssssh",     c_listsubsubsubsubsubsubheading, TRUE,  CMD_ONLY_MAINPART },
	{ "!listsubsubsubsubsubsubsubheading", "!lsssssssh",  c_listsubsubsubsubsubsubsubheading, TRUE, CMD_ONLY_MAINPART },
	{ "!listsubsubsubsubsubsubsubsubheading", "!lssssssssh", c_listsubsubsubsubsubsubsubsubheading, TRUE, CMD_ONLY_MAINPART },
	{ "!jumpid",                         "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!win_helpid",                     "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!win_make_button",                "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_set_button",                 "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!wh4_helpid",                     "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!mapping",                        "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!html_name",                      "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!html_dirname",                   "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!html_keywords",                  "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!html_description",               "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!html_robots",                    "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!html_bgsound",                   "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!html_backimage",                 "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!html_backcolor",                 "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!html_textcolor",                 "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!html_linkcolor",                 "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!html_alinkcolor",                "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!html_vlinkcolor",                "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!html_verbatim_backcolor",        "",              c_verbatim_backcolor,            TRUE,  CMD_ALWAYS },
	{ "!html_counter_command",           "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!hh_backimage",                   "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!hh_backcolor",                   "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!hh_textcolor",                   "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!hh_linkcolor",                   "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!hh_alinkcolor",                  "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!hh_vlinkcolor",                  "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!hh_verbatim_backcolor",          "",              c_verbatim_backcolor,            TRUE,  CMD_ALWAYS },
	{ "!chapterimage",                   "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!chaptericon",                    "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!chaptericon_active",             "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!chaptericon_text",               "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!newpage",                        "",              c_newpage,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!comment",                        "",              c_comment,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!include",                        "",              c_include,                       TRUE,  CMD_ALWAYS },
	{ "!vinclude",                       "",              c_include_verbatim,              TRUE,  CMD_ONLY_MAINPART },
	{ "!rinclude",                       "",              c_include_raw,                   TRUE,  CMD_ALWAYS },
	{ "!sinclude",                       "",              c_include_src,                   TRUE,  CMD_ONLY_MAINPART },
	{ "!cinclude",                       "",              c_include_comment,               TRUE,  CMD_ONLY_MAINPART },
	{ "!ldinclude",                      "",              c_include_linedraw,              TRUE,  CMD_ONLY_MAINPART },
	{ "!pinclude",                       "",              c_include_preformatted,          TRUE,  CMD_ONLY_MAINPART },
	{ "!input",                          "",              c_input,                         TRUE,  CMD_ALWAYS },
	{ "!image",                          "",              c_image,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!image*",                         "",              c_image_nonr,                    TRUE,  CMD_ONLY_MAINPART },
	{ "!bigskip",                        "",              c_bigskip,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!medskip",                        "",              c_medskip,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!smallskip",                      "",              c_smallskip,                     TRUE,  CMD_ONLY_MAINPART },
	{ "!tex_dpi",                        "",              c_tex_dpi,                       TRUE,  CMD_ALWAYS },
	{ "!tex_verb",                       "",              c_tex_verb,                      TRUE,  CMD_ALWAYS },
	{ "!maketitle",                      "",              c_maketitle,                     TRUE,  CMD_ONLY_MAINPART },
	{ "!tableofcontents",                "",              c_tableofcontents,               TRUE,  CMD_ONLY_MAINPART },
	{ "!toc_title",                      "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!node_title",                     "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!top_title",                      "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!listoffigures",                  "",              c_listoffigures,                 TRUE,  CMD_ONLY_MAINPART },
	{ "!listoftables",                   "",              c_listoftables,                  TRUE,  CMD_ONLY_MAINPART },
	{ "!toc",                            "",              c_toc,                           TRUE,  CMD_ONLY_MAINPART },
	{ "!subtoc",                         "",              c_subtoc,                        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubtoc",                      "",              c_subtoc,                        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubtoc",                   "",              c_subtoc,                        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubtoc",                "",              c_subtoc,                        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubtoc",             "",              c_subtoc,                        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubtoc",          "",              c_subtoc,                        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubsubtoc",       "",              c_subtoc,                        TRUE,  CMD_ONLY_MAINPART },
	{ "!subsubsubsubsubsubsubsubtoc",    "",              c_subtoc,                        TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_appendix",                 "",              c_begin_appendix,                TRUE,  CMD_ONLY_MAINPART },
	{ "!end_appendix",                   "",              c_end_appendix,                  TRUE,  CMD_ONLY_MAINPART },
	{ "!begin_document",                 "",              c_begin_document,                TRUE,  CMD_ONLY_PREAMBLE },
	{ "!end_document",                   "",              c_end_document,                  TRUE,  CMD_ONLY_MAINPART },
	{ "!sloppy",                         "",              c_sloppy,                        TRUE,  CMD_ALWAYS },
	{ "!fussy",                          "",              c_fussy,                         TRUE,  CMD_ALWAYS },
	{ "!code",                           "",              c_code_source,                   TRUE,  CMD_ALWAYS },
	{ "!code_source",                    "",              c_code_source,                   TRUE,  CMD_ALWAYS },
	{ "!code_target",                    "",              c_code_target,                   TRUE,  CMD_ALWAYS },
	{ "!autoref",                        "",              c_autoref,                       TRUE,  CMD_ALWAYS },
	{ "!autoref_items",                  "",              c_autoref_items,                 TRUE,  CMD_ALWAYS },
	{ "!stg_limage",                     "",              c_limage,                        TRUE,  CMD_ALWAYS },
	{ "!hline",                          "",              c_hline,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!table_caption",                  "",              c_table_caption,                 TRUE,  CMD_ONLY_MAINPART },
	{ "!table_caption*",                 "",              c_table_caption_nonr,            TRUE,  CMD_ONLY_MAINPART },
	{ "!universal_charset",              "",              c_universal_charset,             TRUE,  CMD_ALWAYS },
	{ "!win_charwidth",                  "",              c_win_charwidth,                 TRUE,  CMD_ALWAYS },
	{ "!wh4_charwidth",                  "",              c_wh4_charwidth,                 TRUE,  CMD_ALWAYS },
	{ "!rtf_charwidth",                  "",              c_rtf_charwidth,                 TRUE,  CMD_ALWAYS },
	{ "!rtf_add_colour",                 "",              c_rtf_add_color,                 TRUE,  CMD_ONLY_PREAMBLE },
	{ "!rtf_add_color",                  "",              c_rtf_add_color,                 TRUE,  CMD_ONLY_PREAMBLE },
	{ "!rtf_keep_tables",                "",              c_rtf_keep_tables,               TRUE,  CMD_ALWAYS },
	{ "!html_img_suffix",                "",              c_html_img_suffix,               TRUE,  CMD_ALWAYS },
	{ "!html_nodesize",                  "",              c_html_nodesize,                 TRUE,  CMD_ALWAYS },
	{ "!htag_img_suffix",                "",              c_htag_img_suffix,               TRUE,  CMD_ALWAYS },
	{ "!hh_img_suffix",                  "",              c_html_img_suffix,               TRUE,  CMD_ALWAYS },
	{ "!tabwidth",                       "",              c_tabwidth,                      TRUE,  CMD_ALWAYS },
	{ "!verbatimsize",                   "",              c_verbatimsize,                  TRUE,  CMD_ALWAYS },
	{ "!linedrawsize",                   "",              c_linedrawsize,                  TRUE,  CMD_ALWAYS },
	{ "!set",                            "",              c_set,                           TRUE,  CMD_ALWAYS },
	{ "!unset",                          "",              c_unset,                         TRUE,  CMD_ALWAYS },
	{ "!drc_bcolor",                     "",              c_drc_bcolor,                    TRUE,  CMD_ALWAYS },
	{ "!drc_icolor",                     "",              c_drc_icolor,                    TRUE,  CMD_ALWAYS },
	{ "!drc_ucolor",                     "",              c_drc_ucolor,                    TRUE,  CMD_ALWAYS },
	{ "!use_raw_header",                 "",              c_tunix,                         TRUE,  CMD_ONLY_PREAMBLE },
	{ "!use_raw_footer",                 "",              c_tunix,                         TRUE,  CMD_ONLY_PREAMBLE },
	{ "!udolink",                        "",              c_udolink,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!toplink",                        "",              c_toplink,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!endnode",                        "",              c_endnode,                       TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_subtoc",                  "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_subsubtoc",               "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_subsubsubtoc",            "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_subsubsubsubtoc",         "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_subsubsubsubsubtoc",      "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_subsubsubsubsubsubtoc",   "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_subsubsubsubsubsubsubtoc", "",             c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_subsubsubsubsubsubsubsubtoc", "",          c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_links",                   "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_index",                   "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_title",                   "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_headline",                "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_bottomline",              "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_raw_header",              "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_raw_footer",              "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!ignore_toptoc",                  "",              c_tunix,                         TRUE,  CMD_ONLY_MAINPART },
	{ "!macro",                          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!define",                         "",              c_define,                        TRUE,  CMD_ALWAYS },
	{ "!undef",                          "",              c_undef,                         TRUE,  CMD_ALWAYS },
	{ "!hyphen",                         "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!docinfo",                        "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!doclayout",                      "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!toc_offset",                     "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!subtoc_offset",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!subsubtoc_offset",               "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!subsubsubtoc_offset",            "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!subsubsubsubtoc_offset",         "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!subsubsubsubsubtoc_offset",      "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!subsubsubsubsubsubtoc_offset",   "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!subsubsubsubsubsubsubtoc_offset", "",             cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!subsubsubsubsubsubsubsubtoc_offset", "",          cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!table_counter",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!table_alignment",                "",              set_table_alignment,             TRUE,  CMD_ALWAYS },
	{ "!image_counter",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!image_alignment",                "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!tex_lindner",                    "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!tex_strunk",                     "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!tex_emtex",                      "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!tex_miktex",                     "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!tex_tetex",                      "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!tex_2e",                         "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_name_prefix",               "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_no_xlist",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_backpage",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_indexname",                 "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_propfont_name",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_propfont_size",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_monofont_name",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_monofont_size",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_merge_nodes",               "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_merge_subnodes",            "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_merge_subsubnodes",         "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_merge_subsubsubnodes",      "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_merge_subsubsubsubnodes",   "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_merge_subsubsubsubsubnodes", "",             cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_merge_subsubsubsubsubsubnodes", "",          cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_merge_subsubsubsubsubsubsubnodes", "",       cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_ignore_8bit",               "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_navigation",                "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_modern_layout",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_modern_width",              "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_modern_alignment",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_modern_backcolor",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_modern_backimage",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_layout",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_width",              "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_alignment",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_height",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_position",           "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_backcolor",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_textcolor",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_linkcolor",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_alinkcolor",         "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_vlinkcolor",         "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_backimage",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_doctype",                   "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_style_name",                "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!html_script_name",               "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!html_favicon_name",              "",              c_tunix,                         TRUE,  CMD_ALWAYS },
	{ "!html_button_alignment",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_quotes",                    "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_switch_language",           "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_use_hyphenation",           "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_transparent_buttons",       "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_use_folders",               "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_header_date",               "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_header_links",              "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_toc_title",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!html_frames_con_title",          "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!rtf_propfont",                   "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!rtf_monofont",                   "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!rtf_propfont_size",              "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!rtf_monofont_size",              "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!rtf_no_tables",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_propfont",                   "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_monofont",                   "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_propfont_size",              "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_monofont_size",              "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_backcolor",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_textcolor",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_linkcolor",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_background",                 "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_inline_bitmaps",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_high_compression",           "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_medium_compression",         "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_old_keywords",               "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_propfont",                   "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_monofont",                   "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_propfont_size",              "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_monofont_size",              "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_backcolor",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_textcolor",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_background",                 "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_inline_bitmaps",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_high_compression",           "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_medium_compression",         "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_old_keywords",               "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!win_prefix_helpids",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!wh4_prefix_helpids",             "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!pdf_high_compression",           "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!pdf_medium_compression",         "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!parwidth",                       "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!sort_hyphen_file",               "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!man_lpp",                        "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!man_type",                       "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!drc_flags",                      "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!nroff_type",                     "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!language",                       "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE },
	{ "!break",                          "",              c_break,                         TRUE,  CMD_ALWAYS },
	{ "!error",                          "",              c_error,                         TRUE,  CMD_ALWAYS },
	{ "!nop",                            "",              c_nop,                           TRUE,  CMD_ALWAYS },
	{ "!show_variable",                  "",              cmd_outside_preamble,            TRUE,  CMD_ONLY_PREAMBLE }
};


LOCAL const UDOSWITCH udoswitch[] = {
	{ "!use_auto_subtocs",                      &use_auto_subtocs[TOC_NODE1], 'i',  "!depth", &subtocs_depth[TOC_NODE1] },
	{ "!use_auto_subsubtocs",                   &use_auto_subtocs[TOC_NODE2], 'i',  "!depth", &subtocs_depth[TOC_NODE2] },
	{ "!use_auto_subsubsubtocs",                &use_auto_subtocs[TOC_NODE3], 'i',  "!depth", &subtocs_depth[TOC_NODE3] },
	{ "!use_auto_subsubsubsubtocs",             &use_auto_subtocs[TOC_NODE4], 'i',  "!depth", &subtocs_depth[TOC_NODE4] },
	{ "!use_auto_subsubsubsubsubtocs",          &use_auto_subtocs[TOC_NODE5], 'i',  "!depth", &subtocs_depth[TOC_NODE5] },
	{ "!use_auto_subsubsubsubsubsubtocs",       &use_auto_subtocs[TOC_NODE6], 'i',  "!depth", &subtocs_depth[TOC_NODE6] },
	{ "!use_auto_subsubsubsubsubsubsubtocs",    &use_auto_subtocs[TOC_NODE7], 'i',  "!depth", &subtocs_depth[TOC_NODE7] },
	{ "!use_auto_subsubsubsubsubsubsubsubtocs", &use_auto_subtocs[TOC_NODE8], 'i',  "!depth", &subtocs_depth[TOC_NODE8] },
	{ "!use_auto_toptocs",                      &use_auto_toptocs,            'b',  "!no_icons", &no_auto_toptocs_icons },
	{ "!use_compressed_tocs",                   &use_compressed_tocs,         '\0', "", NULL },
	{ "!use_compressed_envs",                   &use_compressed_envs,         '\0', "", NULL },
	{ "!use_compressed_descriptions",           &use_compressed_descriptions, '\0', "", NULL },
	{ "!use_compressed_enumerates",             &use_compressed_enumerates,   '\0', "", NULL },
	{ "!use_compressed_itemizes",               &use_compressed_itemizes,     '\0', "", NULL },
	{ "!use_compressed_lists",                  &use_compressed_lists,        '\0', "", NULL },
	{ "!use_formfeed",                          &use_formfeed,                '\0', "", NULL },
	{ "!use_chapter_images",                    &use_chapter_images,          '\0', "", NULL },
	{ "!use_about_udo",                         &use_about_udo,               '\0', "", NULL },
	{ "!use_ansi_tables",                       &use_ansi_tables,             '\0', "", NULL },
	{ "!use_style_book",                        &use_style_book,              '\0', "", NULL },
	{ "!use_justification",                     &use_justification,           '\0', "", NULL },
	{ "!use_output_buffer",                     &use_output_buffer,           '\0', "", NULL },
	{ "!use_nodes_inside_index",                &use_nodes_inside_index,      '\0', "", NULL },
	{ "!use_alias_inside_index",                &use_alias_inside_index,      '\0', "", NULL },
	{ "!use_label_inside_index",                &use_label_inside_index,      '\0', "", NULL },
	{ "!use_udo_index",                         &use_udo_index,               '\0', "", NULL },
	{ "!use_mirrored_indices",                  &use_mirrored_indices,        '\0', "", NULL },
	{ "!use_comments",                          &use_comments,                '\0', "", NULL },
	{ "!use_auto_helpids",                      &use_auto_helpids,            '\0', "", NULL },
	{ "!no_index",                              &no_index,                    '\0', "", NULL },
	{ "!no_images",                             &no_images,                   '\0', "", NULL },
	{ "!no_img_size",                           &no_img_size,                 '\0', "", NULL },
	{ "!no_numbers",                            &no_numbers,                  '\0', "", NULL },
	{ "!no_umlaute",                            &no_umlaute,                  '\0', "", NULL },
	{ "!no_8bit",                               &no_umlaute,                  '\0', "", NULL },
	{ "!no_xlinks",                             &no_xlinks,                   '\0', "", NULL },
	{ "!no_urls",                               &no_urls,                     '\0', "", NULL },
	{ "!no_links",                              &no_links,                    '\0', "", NULL },
	{ "!no_verbatim_umlaute",                   &no_verbatim_umlaute,         '\0', "", NULL },
	{ "!no_effects",                            &no_effects,                  '\0', "", NULL },
	{ "!no_quotes",                             &no_quotes,                   '\0', "", NULL },
	{ "!no_preamble",                           &no_preamble,                 '\0', "", NULL },
	{ "!no_headlines",                          &no_headlines,                '\0', "", NULL },
	{ "!no_bottomlines",                        &no_bottomlines,              '\0', "", NULL },
	{ "!no_popup_headlines",                    &no_popup_headlines,          '\0', "", NULL },
	{ "!no_footers",                            &no_footers,                  '\0', "", NULL },
	{ "!no_buttons",                            &no_buttons,                  '\0', "", NULL },
	{ "!no_sourcecode",                         &no_sourcecode,               '\0', "", NULL },
	{ "!no_table_lines",                        &no_table_lines,              '\0', "", NULL }
};

#define MAXSWITCH ArraySize(udoswitch)


typedef struct _udolanguage				/* ---- Sprachentabelle ---- */
{
	const char *magic;					/* UDO-Kommando */
	int langval;						/* zugehoerige Sprache */
} UDOLANGUAGE;


LOCAL UDOLANGUAGE const udolanguage[] = {
	{ "czech",      TOCZE }, { "cz", TOCZE },
	{ "danish",     TODAN }, { "da", TODAN },
	{ "dutch",      TODUT }, { "nl", TODUT },
	{ "english",    TOENG }, { "en", TOENG },
	{ "finnish",    TOFIN }, { "fi", TOFIN },
	{ "french",     TOFRA }, { "fr", TOFRA },
	{ "german",     TOGER }, { "de", TOGER },
	{ "italian",    TOITA }, { "it", TOITA },
	{ "japanese",   TOJAP }, { "ja", TOJAP },
	{ "latvian",    TOLVA }, { "lv", TOLVA },
	{ "norwegian",  TONOR }, { "nn", TONOR }, { "no-nyn", TONOR },
	{ "polish",     TOPOL }, { "pl", TOPOL },
	{ "portuguese", TOPOR }, { "pt", TOPOR },
	{ "spanish",    TOSPA }, { "es", TOSPA },
	{ "swedish",    TOSWE }, { "sv", TOSWE },
	{ "russian",    TORUS }, { "ru", TORUS }
};

#define  MAXLANGUAGE ArraySize(udolanguage)



GLOBAL char compile_date[11] = "\0";
GLOBAL char compile_time[9] = "\0";










/*******************************************************************************
*
*     CENTRAL OUTPUT ROUTINES
*     =======================
*
*     Note:
*     Hier werden Strings in eine Datei geschrieben. 
*     Nirgends im Sourcecode wird direkt ins Outfile geschrieben, 
*     es laeuft alles ueber outln(), out() und voutlnf()
*
******************************************|************************************/

#define MAN_HEADLINES    2
#define MAN_BOTTOMLINES  3

/*******************************************************************************
*
*  count_manpage_lines():
*     count number of lines written to current page
*     and output bottom/headlines if needed
*
*  Notes:
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void count_manpage_lines(void)
{
	if (iManPageLines >= iManPageLength - MAN_BOTTOMLINES)
	{
		man_bottomline();
		iManPagePages++;
		iManPageLines = 0;
		if (out_lf_needed)
		{
			if (!bTestmode)
			{
				fputs(NL, outfile.file);
			}
			outlines++;
		}
		man_headline();
	}
	iManPageLines++;
}

/*******************************************************************************
*
*  outln():
*     outputs a line with the content <s>
*
*  Notes:
*     Aenderungen muessen auch in voutf() beruecksichtigt werden!!!
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void outln(const char *s)
{
	const char *start;
	_BOOL need_nl;

	if (s == NULL)
		return;
	need_nl = TRUE;
	while (*s != '\0')
	{
		start = s;
		while (*s != '\0' && *s != '\n')
			s++;

		if (desttype == TOMAN && iManPageLength > 0)
			count_manpage_lines();

		if (!bTestmode)
		{
			fwrite(start, 1, (size_t) (s - start), outfile.file);
			/* fprintf(outfile.file, " %lu", outlines); */
			fputs(NL, outfile.file);
		}

		outlines++;
		out_lf_needed = FALSE;
		need_nl = FALSE;
		if (*s != '\0')
		{
			need_nl = TRUE;
			s++;
		}
	}
	if (need_nl)
	{
		if (desttype == TOMAN && iManPageLength > 0)
			count_manpage_lines();
		if (!bTestmode)
		{
			/* fprintf(outfile.file, " %lu", outlines); */
			fputs(NL, outfile.file);
		}

		outlines++;
		out_lf_needed = FALSE;
	}
}





/*******************************************************************************
*
*  voutlnf():
*     outputs a line with variable content PLUS a line feed
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void voutlnf(const char *fmt, ...)
{
	va_list ap;

	if (!bTestmode)
	{
		va_start(ap, fmt);
		vfprintf(outfile.file, fmt, ap);
		va_end(ap);
	}
	outln("");
}





/*******************************************************************************
*
*  out():
*     outputs a line with the content <s>
*
*  Notes:
*     Aenderungen muessen auch in voutf() beruecksichtigt werden!!!
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void out(const char *s)
{
	if (!bTestmode)
	{
		fprintf(outfile.file, "%s", s);
	}
	out_lf_needed = TRUE;
}





/*******************************************************************************
*
*  voutf():
*     outputs a line with variable content WITHOUT a line feed
*
*  Notes:
*     -
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void voutf(const char *fmt, ...)
{
	va_list ap;

	if (!bTestmode)
	{
		va_start(ap, fmt);
		vfprintf(outfile.file, fmt, ap);
		va_end(ap);
	}
	out_lf_needed = TRUE;
}










/*******************************************************************************
*
*     STRING MANIPULATIONS
*     ====================
*
******************************************|************************************/

/*******************************************************************************
*
*  stringcenter():
*     Zentriert einen String innerhalb <length> Zeichen
*
*  Notes:
*     Ist der String laenger, wird er nicht gekuerzt.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void stringcenter(char *string, size_t length)
{
	char s[256];
	size_t sl;							/* string length */
	size_t add;							/* number of spaces to add */

	if (length >= ArraySize(s))			/* avoid buffer overflow */
	{
		warning_message(_("stringcenter(): length must not exceed %d!"), (int) ArraySize(s) - 1);
		return;
	}

	sl = toklen(string);				/* get real length of string */
	if (sl >= length)					/* too long? */
		return;

	add = (length - sl) / 2;			/* compute additional space */
	memset(s, ' ', add);				/* fill left part of buffer with spaces */
	strcpy(s + add, string);			/* add string to buffer (so it's centered) */
	strcpy(string, s);					/* return centered string */
}





/*******************************************************************************
*
*  strcenter():
*     zentriert einen String innerhalb <length> Zeichen oder kuerzt ihn, wenn er zu lang ist
*
*  Notes:
*     Ist der String laenger, wird er nicht gekuerzt.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void strcenter(char *string, size_t length)
{
	char s[256];
	size_t sl;							/* string length */
	size_t add;							/* number of spaces to add */

	if (length >= ArraySize(s))			/* avoid buffer overflow */
	{
		warning_message(_("strcenter(): length must not exceed %d!"), (int) ArraySize(s) - 1);
		return;
	}

	sl = toklen(string);				/* get real length of string */

	if (sl == length)					/* nothing to do? */
		return;

	if (sl > length)					/* string is longer then requested! */
	{
		string[length] = EOS;			/* cut off string! */
		return;
	}

	add = (length - sl) / 2;			/* compute additional space */
	memset(s, ' ', add);				/* fill left part of buffer with spaces */
	strcpy(s + add, string);			/* add string to buffer (so it's centered) */

	strcpy(string, s);					/* return centered string */
}





/*******************************************************************************
*
*  outlncenter():
*     Ausgabe eines zentrierten Strings
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void outlncenter(const char *s)
{
	char tmp[512];

	strcpy(tmp, s);
	strcenter(tmp, zDocParwidth);
	outln(tmp);
}





/*******************************************************************************
*
*  outlncenterfill():
*     Ausgabe eines zentrierten Strings mit Auffuellen durch Leerzeichen (fuer DRC)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void outlncenterfill(const char *s)
{
	char tmp[513];						/* string buffer */
	size_t sl;							/* string length */

	sl = strlen(s);						/* get length of string */

	if (sl >= ArraySize(tmp))
	{
		warning_message(_("outlncenterfill(): string must not be longer than %d characters"), (int) ArraySize(tmp) - 1);
		return;
	}

	strcpy(tmp, s);						/* copy string for conversion */

	strcenter(tmp, zDocParwidth);		/* center string */

	sl = strlen(tmp);					/* get length of converted string */

	while (sl < zDocParwidth)			/* fill right part of centered string */
	{
		strcat(tmp, " ");
		sl++;
	}
	outln(tmp);							/* output converted string */
}





/*******************************************************************************
*
*  strright():
*     Formatiert einen String rechtsbuendig auf <length> Zeichen
*
*  Note:
*     Falls er zu lang ist, wird er gekuerzt.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void strright(char *string, size_t length)
{
	char s[256];						/* string buffer */
	size_t sl;							/* string length */
	size_t add;							/* number of spaces to add */

	sl = toklen(string);				/* get length of string */
	if (sl == length)					/* nothing to do */
		return;

	if (sl > length)					/* string too long! */
	{
		string[length] = EOS;			/* cut off! */
		return;
	}

	add = length - sl;
	memset(s, ' ', add);
	strcpy(s + add, string);

	strcpy(string, s);
}





/*******************************************************************************
*
*  strjustify():
*     Blocksatz fuer Strings, die nicht mit einem Space beginnen
*
*  Return:
*     -
*
******************************************|************************************/

#define MAXBLANKPOS  256

LOCAL size_t blankpos[MAXBLANKPOS + 1];	/* Positionen der Blanks */

LOCAL _BOOL justify_from_right;			/* Blanks rechts einfuegen? */

LOCAL void strjustify(char *s, size_t len)
{
	size_t sl;							/* string length */
	size_t tl;
	size_t i;
	int count, pos, j;
	_BOOL is_verbed;

	/* string starts with space or is empty? */
	if (s[0] == ' ' || s[0] == EOS)
		return;

	if (len > MAXBLANKPOS)
	{
		warning_message(_("strjustify(): string must not be longer than %d characters"), MAXBLANKPOS - 1);
		return;
	}

	tl = toklen(s);						/* get real length of string */

	if (tl > len)						/* string longer than required */
		return;

	sl = strlen(s);

	count = -1;

	is_verbed = styleflag.verbatim;

	for (i = 0; i < sl; i++)
	{
		if (!is_verbed)					/* Nur die, die nicht in (!V)...(!v) stehen */
		{
			if (s[i] == ' ')
			{
				count++;
				blankpos[count] = i;
			}
		}

		if (s[i] == ESC_STYLE_MAGIC[0] && s[i + 1] == ESC_STYLE_MAGIC[1])
		{
			switch (s[i + 2])
			{
			case C_VERB_ON:
				is_verbed = TRUE;
				break;
			case C_VERB_OFF:
				is_verbed = FALSE;
				break;
			}
			i += 4;
		}
	}

	if (count < 0)
		return;

	if (justify_from_right)
	{
		pos = count;
		while (tl < len)
		{
			strinsert(s + blankpos[pos], " ");
			tl++;
			for (j = pos; j <= count; j++)
				blankpos[j]++;

			pos--;
			if (pos < 0)
				pos = count;
		}
	} else
	{
		pos = 0;
		while (tl < len)
		{
			strinsert(s + blankpos[pos], " ");
			tl++;
			for (j = pos; j <= count; j++)
				blankpos[j]++;

			pos++;
			if (pos > count)
				pos = 0;
		}
	}

	justify_from_right = !justify_from_right;
}





/*******************************************************************************
*
*  output_ascii_line():
*     output a line with a repeated character
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_ascii_line(const char *c, const size_t len)
{
	char s[512];

	memset(s, c[0], len);
	s[len] = EOS;
	outln(s);
}





/*******************************************************************************
*
*  cmd_outside_preamble():
*     output error message for commands which are allowed in the preamble only
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void cmd_outside_preamble(void)
{
	if (bInsideDocument)
	{
		error_message(_("%s ignored outside preamble"), token[0]);
	}
}





/*******************************************************************************
*
*  cmd_inside_preamble():
*     output error message for commands which are allowed in the document only
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void cmd_inside_preamble(void)
{
	if (!bInsideDocument)
	{
		error_message(_("%s ignored inside preamble"), token[0]);
	}
}





static int langid_from_name(const char *s)
{
	int i;
	
	for (i = 0; i < (int) MAXLANGUAGE; i++)
	{
		if (my_stricmp(s, udolanguage[i].magic) == 0)
			return udolanguage[i].langval;
		if (strlen(udolanguage[i].magic) == 2 && my_strnicmp(s, udolanguage[i].magic, 2) == 0)
			return udolanguage[i].langval;
		if (strlen(udolanguage[i].magic) == 3 && my_strnicmp(s, udolanguage[i].magic, 3) == 0)
			return udolanguage[i].langval;
	}
	return -1;
}

/*******************************************************************************
*
*  str_for_destlang():
*     check if a command is allowed for a language, format or operating system
*
*  Return:
*      TRUE: command is allowed
*     FALSE: command is not allowed
*
******************************************|************************************/

LOCAL _BOOL str_for_destlang(const char *s, _BOOL warn)
{
	_BOOL flag = FALSE;					/* return value */
	int i;
	char *test;
	char *p;
	const char *sep = " \t,[]";
	
	test = strdup(s);
	if (test == NULL)
		return FALSE;
	p = strtok(test, sep);
	while (p != NULL)
	{
		if (*p != '\0')
		{
			if (strcmp(p, "all") == 0)
			{
				flag = TRUE;
			} else if (strcmp(p, "none") == 0)
			{
				flag = FALSE;
			} else
			{
				i = langid_from_name(p);
				if (i < 0 && warn && iUdopass == PASS1)
					warning_message(_("unknown !language: %s"), p);
				if (destlang == i)
				{
					flag = TRUE;
				}
			}
		}
		p = strtok(NULL, sep);
	}
	free(test);
		
	return flag;
}





/*******************************************************************************
*
*  str_for_desttype():
*     check if a command is allowed for a specified language
*
*  Return:
*      TRUE: command is allowed
*     FALSE: command is not allowed
*
******************************************|************************************/

static int desttype_from_name(const char *s)
{
	if (strcmp(s, "amg") == 0)
		return TOAMG;
	if (strcmp(s, "aqv") == 0 || strcmp(s, "quickview") == 0)
		return TOAQV;
	if (strcmp(s, "asc") == 0)
		return TOASC;
	if (strcmp(s, "drc") == 0)
		return TODRC;
	if (strcmp(s, "hah") == 0)
		return TODRC;
	if (strcmp(s, "hh") == 0 || strcmp(s, "htmlhelp") == 0)
		return TOMHH;
	if (strcmp(s, "htag") == 0 || strcmp(s, "helptag") == 0)
		return TOHPH;
	if (strcmp(s, "html") == 0)
		return TOHTM;
	if (strcmp(s, "info") == 0)
		return TOINF;
	if (strcmp(s, "ipf") == 0)
		return TOIPF;
	if (strcmp(s, "ldoc") == 0)
		return TOLDS;
	if (strcmp(s, "lyx") == 0)
		return TOLYX;
	if (strcmp(s, "man") == 0)
		return TOMAN;
	if (strcmp(s, "nroff") == 0)
		return TONRO;
	if (strcmp(s, "pascal") == 0)
		return TOSRP;
	if (strcmp(s, "pch") == 0 || strcmp(s, "pchelp") == 0)
		return TOPCH;
	if (strcmp(s, "pdf") == 0 || strcmp(s, "pdflatex") == 0)
		return TOPDL;
	if (strcmp(s, "ps") == 0)
		return TOKPS;
	if (strcmp(s, "rtf") == 0)
		return TORTF;
	if (strcmp(s, "src") == 0 || strcmp(s, "c") == 0)
		return TOSRC;
	if (strcmp(s, "stg") == 0)
		return TOSTG;
	if (strcmp(s, "tex") == 0)
		return TOTEX;
	if (strcmp(s, "tvh") == 0 || strcmp(s, "vision") == 0)
		return TOTVH;
	if (strcmp(s, "udo") == 0)
		return TOUDO;
	if (strcmp(s, "wh4") == 0 || strcmp(s, "win4") == 0)
		return TOWH4;
	if (strcmp(s, "win") == 0)
		return TOWIN;
	return -1;
}



GLOBAL int str_for_desttype(const char *s, _BOOL warn)
{
	int flag = FALSE;					/* return value */
	int i;
	char *test;
	char *p;
	const char *sep = " \t,[]";
	
	test = strdup(s);
	if (test == NULL)
		return FALSE;
	p = strtok(test, sep);
	while (p != NULL)
	{
		if (*p != '\0')
		{
			if (strcmp(p, "all") == 0)
			{
				flag = TRUE;
			} else if (strcmp(p, "none") == 0)
			{
				flag = -1;
			} else
			{
				i = desttype_from_name(p);
				if (i < 0 && warn)
					warning_message(_("unknown output format: %s"), p);
				if (desttype == i)
				{
					flag = TRUE;
				}
			}
		}
		p = strtok(NULL, sep);
	}
	free(test);
	
	return flag;
}





/*******************************************************************************
*
*  is_for_desttype():
*     ??? (description missing)
*
*  Return:
*      TRUE: command is allowed
*     FALSE: command is not allowed
*
******************************************|************************************/

GLOBAL _BOOL is_for_desttype(_BOOL *schalter, const char *cmd, _BOOL warn)
{
	register int i;
	_BOOL flag = FALSE;					/* return value */
	int val;
	
	if (token_counter <= 1)
	{
		error_missing_parameter(cmd);
	} else
	{
		for (i = 1; i < token_counter; i++)
		{
			/* stop checking for commands like !subtoc [all] !depth 1 */
			if (token[i][0] == META_C)
				break;
			val = str_for_desttype(token[i], warn);
			flag |= val > 0;
			if (val < 0)
				*schalter = FALSE;
		}
	}

	/* Problem: Default-Werte z.B. fuer Texinfo werden bei */
	/* !no_umlaute [asc] uberschrieben. Daher Schalter nur */
	/* noch im positiven Falle setzen. */

	if (flag)
		*schalter = TRUE;
	return flag;
}





/*******************************************************************************
*
*  str_for_os():
*     check if command is allowed for specific operating system
*
*  Return:
*      TRUE: command is allowed
*     FALSE: command is not allowed
*
******************************************|************************************/

LOCAL _BOOL str_for_os(const char *s, _BOOL warn)
{
	_BOOL flag;							/* return value */
	_BOOL warn_unix;
	char *test;
	char *p;
	const char *sep = " \t,[]";

	flag = FALSE;
	warn_unix = FALSE;

	test = strdup(s);
	if (test == NULL)
		return FALSE;
	p = strtok(test, sep);
	while (p != NULL)
	{
		if (*p != '\0')
		{
			if (strcmp(p, "all") == 0)
			{
				flag = TRUE;
			} else if (strcmp(p, "none") == 0)
			{
				flag = FALSE;
			} else
			{
				if (strcmp(p, "hpux") == 0 || 
					strcmp(p, "irix") == 0 ||
					strcmp(p, "linux") == 0 ||
					strcmp(p, "sinix") == 0 ||
					strcmp(p, "sunos") == 0)
				{
					warn_unix = TRUE;
#ifdef __UNIX__
					flag = TRUE;
#endif
				} else if (strcmp(p, "beos") == 0)
				{
#ifdef __BEOS__
					flag = TRUE;
#endif
				} else if (strcmp(p, "macos") == 0)
				{
#ifdef __MACOS__
					flag = TRUE;
#endif
				} else if (strcmp(p, "macosx") == 0)
				{
#ifdef __MACOSX__
					flag = TRUE;
#endif
				} else if (strcmp(p, "dos") == 0)
				{
#ifdef __MSDOS__
					flag = TRUE;
#endif
				} else if (strcmp(p, "os2") == 0)
				{
#ifdef __OS2__
					flag = TRUE;
#endif
				} else if (strncmp(p, "win", 3) == 0)
				{
#ifdef __WIN32__
					flag = TRUE;
#endif
				} else if (strcmp(p, "nextstep") == 0)
				{
#ifdef __NEXTSTEP__
					flag = TRUE;
#endif
				} else if (strcmp(p, "tos") == 0)
				{
#ifdef __TOS__
					flag = TRUE;
#endif
				} else if (strcmp(p, "unix") == 0)
				{
#ifdef __UNIX__
					flag = TRUE;
#endif
				} else
				{
					if (warn && iUdopass == PASS1)
						warning_message(_("unknown os: %s"), p);
				}
			}
		}
		p = strtok(NULL, sep);
	}
	free(test);
		
	if (warn_unix && iUdopass == PASS1)
		warning_message(_("use \"unix\" to test for unix systems"));

	return flag;
}





/*******************************************************************************
*
*  get_color():
*     get (a?) color
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL int find_color(const char *name)
{
	register int i;

	for (i = 0; i < MAX_UDOCOLOR; i++)
	{
		if (my_stricmp(name, udocolor[i].name) == 0)
			return i;
	}

	error_message(_("unknown color: %s"), name);
	return -1;
}


LOCAL int get_color(void)
{
	char n[1024];

	tokcpy2(n, ArraySize(n));
	qdelete_once(n, "[", 1);
	qdelete_last(n, "]", 1);

	return find_color(n);
}




const char *html_color_string(const struct rgb *color)
{
	static char s[10];

	if (color->set)
		sprintf(s, "#%02x%02x%02x", color->r, color->g, color->b);
	else
		s[0] = '\0';
	return s;
}


/*******************************************************************************
*
*  get_html_color():
*     get (a?) HTML color
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL get_html_color(const char *s, struct rgb_and_color *rgb)
{
	int color;

	if ((color = find_color(s)) >= 0)
	{
		if (color != BC_NONE)
		{
			rgb->rgb = udocolor[color].rgb;
			rgb->rgb.set = TRUE;
		} else
		{
			rgb->rgb.set = FALSE;
		}
		rgb->color = color;
		return TRUE;
	}

	return FALSE;
}


GLOBAL _BOOL get_html_color_or_rgb(const char *s, struct rgb_and_color *rgb)
{
	int r, g, b;
	_BOOL ret;

	struct rgb_and_color color;

	memset(&color, 0, sizeof(color));
	if (s[0] == '#')
	{
		ret = sscanf(s, "#%02x%02x%02x", &r, &g, &b) == 3;
		color.rgb.r = r;
		color.rgb.g = g;
		color.rgb.b = b;
		color.rgb.set = ret;
		color.color = 0;
	} else
	{
		ret = get_html_color(s, &color);
	}
	*rgb = color;
	return ret;
}



/*******************************************************************************
*
*  get_drc_color():
*     get (a?) DRC color
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void get_drc_color(char *h)
{
	int color;

	h[0] = EOS;
	if ((color = get_color()) >= 0)
		if (color != BC_NONE)
			strcpy(h, udocolor[color].drc);
}





/*******************************************************************************
*
*  c_drc_bcolor():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_drc_bcolor(void)
{
	get_drc_color(sDrcBcolor);
}





/*******************************************************************************
*
*  c_drc_icolor():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_drc_icolor(void)
{
	get_drc_color(sDrcIcolor);
}





/*******************************************************************************
*
*  c_drc_ucolor():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_drc_ucolor(void)
{
	get_drc_color(sDrcUcolor);
}





/*******************************************************************************
*
*  c_drc_flags():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_drc_flags(void)
{
	char s[256];

	tokcpy2(s, ArraySize(s));
	iDrcFlags = atoi(s);

	if (iDrcFlags < 0 || iDrcFlags > 64)
	{
		iDrcFlags = 0;
	}
}





/*******************************************************************************
*
*  set_win_backcolor():
*     Copy to <s> the color definition used to define the background color
*     in a Windows Help-Project file.
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void set_win_backcolor(struct rgb_and_color *color, int c)
{
	color->color = c;
	color->rgb = udocolor[color->color].rgb;
	color->rgb.set = c != BC_NONE;
}

static const char *win_color_string(struct rgb_and_color *color)
{
	static char s[20];

	s[0] = EOS;
	if (color->rgb.set && color->color != BC_NONE)
	{
		if (desttype == TOWH4)
			sprintf(s, "(r%lu)",
					(((unsigned long) udocolor[color->color].rgb.g * 256LU) + udocolor[color->color].rgb.b) * 256LU +
					udocolor[color->color].rgb.r);
		else
			sprintf(s, "(%u,%u,%u)", udocolor[color->color].rgb.r, udocolor[color->color].rgb.g,
					udocolor[color->color].rgb.b);
	}
	return s;
}




/*******************************************************************************
*
*  set_win_textcolor():
*     Copy to <s> the rtf command needed to switch to color <c>
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void set_win_textcolor(struct rgb_and_color *color, const int c)
{
	color->color = c;
	color->rgb = udocolor[color->color].rgb;
	color->rgb.set = c != BC_NONE;
}





/*******************************************************************************
*
*  check_on():
*     check if a command uses [on]
*
*  Return:
*     NULL: doesn't use [on]
*    >NULL: uses [on]
*
******************************************|************************************/

LOCAL _BOOL check_on(void)
{
	char n[512];

	tokcpy2(n, ArraySize(n));
	return strstr(n, "on") != NULL;
}





/*******************************************************************************
*
*  check_off():
*     check if a command uses [off]
*
*  Return:
*     NULL: doesn't use [off]
*    >NULL: uses [off]
*
******************************************|************************************/

LOCAL _BOOL check_off(void)
{
	char n[512];

	tokcpy2(n, ArraySize(n));
	return strstr(n, "off") != NULL;
}






/*******************************************************************************
*
*  c_set():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_set(void)
{
	char s[LINELEN];

	tokcpy2(s, ArraySize(s));
	add_udosymbol(s);
}





LOCAL void c_define(void)
{
	add_define();
}


LOCAL void c_undef(void)
{
	del_define();
}





/*******************************************************************************
*
*  c_unset():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_unset(void)
{
	char s[LINELEN];

	tokcpy2(s, ArraySize(s));
	del_udosymbol(s);
}





/*******************************************************************************
*
*  c_hline():
*     output horizontal line
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_hline(void)
{
	int indent;
	char n[128];

	switch (desttype)
	{
	case TOHAH:
	case TOHTM:
	case TOMHH:
		outln(xhtml_hr);
		outln("");
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
	case TORTF:
		strcpy_indent(n);
		voutlnf("%s\\sl30\\brdrt\\brdrs \\par\\pard\\par", n);
		break;

	case TOTEX:
	case TOPDL:
		break;

	case TOLYX:
		break;

	case TOSTG:
	case TOAMG:
		if (token[1][0] == '-')
			indent = strlen_prev_indent();
		else
			indent = strlen_indent();
		voutlnf("@line %d %d 0 0 1", indent + 1, ((int) zDocParwidth) - indent);
		outln("");
		break;

	case TOASC:
	case TOPCH:
	case TODRC:
		strcpy_indent(n);
		indent2space(n);
		out(n);
		output_ascii_line("-", zDocParwidth - strlen(n));
		outln("");
		break;

	case TOTVH:
		strcpy_indent(n);
		indent2space(n);
		if (n[0] == EOS)
			strcpy(n, " ");
		out(n);
		output_ascii_line("\304", zDocParwidth - strlen(n));
		outln("");
		break;

	case TOSRC:
	case TOSRP:
		out("    ");
		output_ascii_line("-", zDocParwidth - strlen(n));
		break;

	case TOIPF:
		break;

	case TOKPS:
		outln("hline");
		break;
	}
}





/*******************************************************************************
*
*  idxlist_compare():
*     ???
*
*  Return:
*     -1: p < q
*      1: p > q
*      0: p == q
*
******************************************|************************************/

LOCAL int idxlist_compare(IDXLIST *p, IDXLIST *q)
{
	char ps[3 * (128 + 2) + MAX_NODE_LEN + 1];
	char qs[3 * (128 + 2) + MAX_NODE_LEN + 1];

	ps[0] = EOS;
	qs[0] = EOS;

	strcat(ps, p->idx[0]);
	strcat(ps, ", ");
	if (p->depth > 0)
		strcat(ps, p->idx[1]);
	strcat(ps, ", ");
	if (p->depth > 1)
		strcat(ps, p->idx[2]);
	strcat(ps, ", ");
	strcat(ps, p->chapter);

	strcat(qs, q->idx[0]);
	strcat(qs, ", ");
	if (q->depth > 0)
		strcat(qs, q->idx[1]);
	strcat(qs, ", ");
	if (q->depth > 1)
		strcat(qs, q->idx[2]);
	strcat(qs, ", ");
	strcat(qs, q->chapter);

	return my_stricmp(ps, qs);
}





/*******************************************************************************
*
*  idxlist_merge():
*     ???
*
*  Return:
*     head.next
*
******************************************|************************************/

LOCAL IDXLIST *idxlist_merge(IDXLIST *p, IDXLIST *q)
{
	IDXLIST *r, head;

	for (r = &head; p && q;)
	{
		if (idxlist_compare(p, q) < 0)
		{
			r = r->next = p;
			p = p->next;
		} else
		{
			r = r->next = q;
			q = q->next;
		}
	}

	r->next = (p ? p : q);
	return head.next;
}





/*******************************************************************************
*
*  idxlist_sort():
*     ???
*
*  Return:
*     sorted IDXLIST p
*
******************************************|************************************/

LOCAL IDXLIST *idxlist_sort(IDXLIST *p)
{
	IDXLIST *q, *r;

	if (p)
	{
		q = p;
		for (r = q->next; r && (r = r->next) != NULL; r = r->next)
			q = q->next;
		r = q->next;
		q->next = NULL;
		if (r)
			p = idxlist_merge(idxlist_sort(r), idxlist_sort(p));
	}

	return p;
}





/*******************************************************************************
*
*  new_idxlist_item():
*     ???
*
*  Return:
*     new IDXLIST l
*
******************************************|************************************/

LOCAL IDXLIST *new_idxlist_item(void)
{
	IDXLIST *l;

	l = (IDXLIST *) malloc(sizeof(IDXLIST));

	if (l != NULL)
	{
		memset(l, 0, sizeof(IDXLIST));
	}

	return l;
}





/*******************************************************************************
*
*  add_idxlist_item():
*     ???
*
*  Return:
*      TRUE: done (or nothing to do)
*     FALSE: error!
*
******************************************|************************************/

GLOBAL _BOOL add_idxlist_item(const char *x1, const char *x2, const char *x3)
{
	IDXLIST *n;
	char c;

	if (no_index)
		return TRUE;

	if (!use_udo_index)
		return TRUE;

	if (x1[0] == EOS)
		return TRUE;

	n = new_idxlist_item();

	if (n == NULL)
	{
		return FALSE;
	}

	strcpy(n->idx[0], x1);
	strcpy(n->idx[1], x2);
	strcpy(n->idx[2], x3);
	n->chapter[0] = EOS;

	del_internal_styles(n->idx[0]);
	del_internal_styles(n->idx[1]);
	del_internal_styles(n->idx[2]);


	/* Buchstaben bestimmen, unter dem der Eintrag einsortiert werden soll */
	/* <???> Achtung: Umlaute werden noch nicht beachtet! */

	c = (char) toupper(n->idx[0][0]);
	if (c >= 'A' && c <= 'Z')
	{
		n->letter = c;
	} else
	{
		n->letter = '*';
	}

	n->depth = 0;

	if (n->idx[1][0] != EOS)
	{
		n->depth++;
		if (n->idx[2][0] != EOS)
			n->depth++;
	}

	switch (desttype)
	{
	case TOASC:
		if (no_numbers)
			strcpy(n->chapter, current_chapter_name);
		else
			strcpy(n->chapter, current_chapter_nr);
		break;

	case TOINF:
		strcpy(n->chapter, current_chapter_name);
		node2texinfo(n->chapter);
		break;
	}

	del_whitespaces(n->chapter);

	n->next = idxlist;
	idxlist = n;

	return TRUE;
}





/*******************************************************************************
*
*  sort_idxlist():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void sort_idxlist(void)
{
	if (!use_udo_index)
		return;

	if (idxlist == NULL)
		return;

	show_status_info("");
	show_status_info("");
	show_status_info(_("Sorting index..."));

	idxlist = idxlist_sort(idxlist);
}





/*******************************************************************************
*
*  print_ascii_index():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void print_ascii_index(void)
{
	IDXLIST *ptr, *prev;
	char thisc,  lastc;
	_BOOL misslf = FALSE;
	_BOOL same1, same2, same3;

	if (!use_udo_index)
		return;

	toc_mark_index_referenced();

	ptr = idxlist;
	prev = NULL;
	if (ptr == NULL)
		return;

	outln("");

	if (use_style_book)
	{
		output_ascii_line("=", zDocParwidth);
		outln(get_lang()->index);
		output_ascii_line("=", zDocParwidth);
	} else
	{
		outln(get_lang()->index);
		output_ascii_line("*", strlen(get_lang()->index));
	}

	lastc = EOS;

	do
	{
		thisc = ptr->letter;

		if (toupper(thisc) != toupper(lastc))
		{
			if (misslf)
			{
				outln("");
				misslf = FALSE;
			}

			outln("");
			lastc = thisc;
			prev = NULL;
		}

		same1 = same2 = same3 = FALSE;
		if (prev != NULL)
		{
			if (strcmp(ptr->idx[0], prev->idx[0]) == 0)
			{
				same1 = TRUE;
			}

			if (ptr->depth >= 1 && prev->depth >= 1)
			{
				same2 = (strcmp(ptr->idx[1], prev->idx[1]) == 0);
			}

			if (ptr->depth >= 2 && prev->depth >= 2)
			{
				same3 = (strcmp(ptr->idx[2], prev->idx[2]) == 0);
			}
		}

		switch (ptr->depth)
		{
		case 0:						/* Ein Index-Eintrag */
			if (same1)
			{
				voutf(", %s", ptr->chapter);
				misslf = TRUE;
			} else
			{
				if (misslf)
					outln("");
				voutf("%s, %s", ptr->idx[0], ptr->chapter);
				misslf = TRUE;
			}
			break;

		case 1:						/* Zwei Index-Eintraege */
			if (same1)
			{
				if (same2)
				{
					voutf(", %s", ptr->chapter);
					misslf = TRUE;
				} else
				{
					if (misslf)
						outln("");
					voutf("     %s, %s", ptr->idx[1], ptr->chapter);
					misslf = TRUE;
				}
			} else
			{
				if (misslf)
					outln("");
				outln(ptr->idx[0]);
				voutf("     %s, %s", ptr->idx[1], ptr->chapter);
				misslf = TRUE;
			}
			break;

		case 2:						/* Drei Index-Eintraege */
			if (same1)
			{
				if (same2)
				{
					if (same3)
					{
						voutf(", %s", ptr->chapter);
						misslf = TRUE;
					} else
					{
						if (misslf)
							outln("");
						voutf("        %s, %s", ptr->idx[2], ptr->chapter);
						misslf = TRUE;
					}
				} else
				{
					if (misslf)
						outln("");
					voutf("     %s, %s", ptr->idx[1], ptr->chapter);
					misslf = TRUE;
				}
			} else
			{
				if (misslf)
					outln("");
				outln(ptr->idx[0]);
				voutlnf("     %s", ptr->idx[1]);
				voutf("        %s, %s", ptr->idx[2], ptr->chapter);
				misslf = TRUE;
			}
			break;
		}

		prev = ptr;
		ptr = ptr->next;

	} while (ptr != NULL);

	if (misslf)
		outln("");
}





/*******************************************************************************
*
*  print_info_index():
*     ???
*
*  ------------------------------------------------------------
*     Aufbau:
*
*     @menu
*     * Indexeintrag:  Nodename.
*     @end menu
*
*     Achtung: Es duerfen keine zwei gleiche Indexeintraege benutzt
*     werden, da Info sonst den falschen Node anspringt. Daher
*     werden hier zur Not Zahlen in Klammern angefuegt.
*     ------------------------------------------------------------
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void print_info_index(void)
{
	int counter;
	IDXLIST *ptr;
	char left[3 * (128 + 2) + 20];
	char old_left[3 * (128 + 2) + 20];
	char val[32];

	outln("");
	outln("@iftex");
	outln("@unnumbered Index");
	outln("@printindex cp");
	outln("@end iftex");
	outln("");

	if (!use_udo_index)
		return;

	toc_mark_index_referenced();

	ptr = idxlist;
	left[0] = EOS;
	old_left[0] = EOS;
	counter = 0;

	if (ptr == NULL)
		return;

	outln("@ifinfo");
	voutlnf("@node %s, , , Top", get_lang()->index);
	voutlnf("@chapter %s", get_lang()->index);
	outln("");
	outln("@menu");

	do
	{
		switch (ptr->depth)
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

		qdelete_all(left, ":", 1);		/* ":" (colons) mag Info dort nicht */

		if (strlen(left) > 34)
			left[34] = EOS;

		if (strcmp(left, old_left) == 0)
		{
			counter++;
			sprintf(val, " (%d)", counter + 1);
			strcat(left, val);
		} else
		{
			strcpy(old_left, left);
			counter = 0;
		}

		voutlnf("* %-38s:%s.", left, ptr->chapter);

		ptr = ptr->next;

	} while (ptr != NULL);

	outln("@end menu");
	outln("@end ifinfo");
	outln("");
}





#define USE_RAW_INDEX 0

#if USE_RAW_INDEX
/*******************************************************************************
*
*  print_raw_index():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void print_raw_index(void)
{
	IDXLIST *ptr;

	if (!use_udo_index)
		return;

	toc_mark_index_referenced();

	ptr = idxlist;

	if (ptr == NULL)
		return;

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

		ptr = ptr->next;

	} while (ptr != NULL);
}
#endif





/*******************************************************************************
*
*  print_index():
*     print an index register
*
*  Notes:
*     This function is called by c_end_document().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void print_index(void)
{
	if (no_index || !bCalledIndex)
		return;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\printindex");
		toc_mark_index_referenced();
		break;

	case TOLYX:
		outln("\\begin_inset LatexCommand \\printindex{}");
		outln("");
		outln("\\end_inset");
		outln("");
		toc_mark_index_referenced();
		break;

	case TOINF:
		sort_idxlist();
		print_info_index();
		break;

	case TOASC:
		sort_idxlist();
		print_ascii_index();
		break;

	case TOSTG:
		/* HCP will generate the Index */
		toc_mark_index_referenced();
		break;

	case TOMHH:
		/* index already generated by save_htmlhelp_index() */
		break;

	case TOHTM:
	case TOHAH:
		/* index already generated by save_html_index() */
		break;

	case TOAQV:
	case TOWIN:
	case TOWH4:
		/* index will be generated by help compiler */
		toc_mark_index_referenced();
		break;
	}

#if USE_RAW_INDEX
	print_raw_index();
#endif
}





/*******************************************************************************
*
*  output_htmlhelp_index():
*     output an index line for HTML-Help.
*
*  Format:
*     <OBJECT type="application/x-oleobject" classid="clsid:1e2a7bd0-dab9-11d0-b93a-00c04fc99f9e">
*     <param name="Keyword" value="MyKLink">
*     </OBJECT>
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_htmlhelp_index(const int count, const char *x0, const char *x1, const char *x2)
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
}





/*******************************************************************************
*
*  c_index():
*     handle the command !index idx1 [!! idx2 [!! idx3]]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_index(void)
{
	char idx[3 * (128 + 2) + 20];
	char n[3][128];
	char entry[3 * (128 + 2) + 20];
	int count, j;
	size_t i;

	if (no_index)
		return;

	/* Tokens umkopieren */
	tokcpy2(idx, ArraySize(idx));

	if (idx[0] == EOS)
	{
		error_missing_parameter(CMD_INDEX);
		return;
	}

	n[0][0] = EOS;
	n[1][0] = EOS;
	n[2][0] = EOS;

	count = 0;
	i = 0;

	while (idx[i] != EOS)
	{
		if (idx[i] == '!' && idx[i + 1] == '!')
		{
			if (count == 2)
				break;
			count++;
			i++;
		} else
		{
			chrcat(n[count], idx[i]);
		}
		i++;
	}

	for (j = 0; j < 3; j++)
	{
		del_whitespaces(n[j]);
	}

	count = 0;
	if (n[0][0] != EOS)
		count++;
	if (n[1][0] != EOS)
		count++;
	if (n[2][0] != EOS)
		count++;
	if (count == 0)
		return;

	/* Set index in project file */
	sprintf(entry, "%s:%s:%s", n[0], n[1], n[2]);
	save_upr_entry_index(count, sCurrFileName, entry, uiCurrFileLine);

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
	case TOINF:
		for (j = 0; j < 3; j++)
		{
			delete_all(n[j], "!-");
			auto_quote_texindex(n[j]);
			c_internal_styles(n[j]);
			replace_udo_quotes(n[j]);
			convert_tilde(n[j]);
		}
		if (desttype == TOTEX || desttype == TOPDL)
		{
			switch (count)
			{
			case 1:
				voutlnf("\\index{%s}", n[0]);
				break;
			case 2:
				voutlnf("\\index{%s!%s}", n[0], n[1]);
				if (use_mirrored_indices)
					voutlnf("\\index{%s!%s}", n[1], n[0]);
				break;
			case 3:
				voutlnf("\\index{%s!%s!%s}", n[0], n[1], n[2]);
				break;
			}
		} else
		{
			switch (count)
			{
			case 1:
				voutlnf("@cindex %s", n[0]);
				break;
			case 2:
				voutlnf("@cindex %s, %s", n[0], n[1]);
				if (use_mirrored_indices)
					voutlnf("@cindex %s, %s", n[1], n[0]);
				break;
			case 3:
				voutlnf("@cindex %s, %s, %s", n[0], n[1], n[2]);
				break;
			}

			add_idxlist_item(n[0], n[1], n[2]);
			if (use_mirrored_indices && count == 2)
				add_idxlist_item(n[1], n[0], n[2]);
		}
		break;

	case TOLYX:
		for (j = 0; j < 3; j++)
		{
			delete_all(n[j], "!-");
			replace_all(n[j], "\\backslash" INDENT_S, "\\");
			auto_quote_texindex(n[j]);
			c_internal_styles(n[j]);
			replace_udo_quotes(n[j]);
			c_tilde(n[j]);
			replace_udo_tilde(n[j]);
			replace_char(n[j], NBSP_C, '~');
		}
		switch (count)
		{
		case 1:
			outln("");
			out("\\begin_inset LatexCommand \\index{");
			out(n[0]);
			outln("}");
			outln("");
			outln("\\end_inset");
			outln("");
			break;
		case 2:
			outln("");
			out("\\begin_inset LatexCommand \\index{");
			out(n[0]);
			out("!");
			out(n[1]);
			outln("}");
			outln("");
			outln("\\end_inset");
			outln("");
			if (use_mirrored_indices)
			{
				out("\\begin_inset LatexCommand \\index{");
				out(n[1]);
				out("!");
				out(n[0]);
				outln("}");
				outln("");
				outln("\\end_inset");
				outln("");
			}
			break;
		case 3:
			outln("");
			out("\\begin_inset LatexCommand \\index{");
			out(n[0]);
			out("!");
			out(n[1]);
			out("!");
			out(n[2]);
			outln("}");
			outln("");
			outln("\\end_inset");
			outln("");
			break;
		}
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		for (j = 0; j < 3; j++)
		{
			del_internal_styles(n[j]);
			replace_udo_quotes(n[j]);
			convert_tilde(n[j]);
			winspecials2ascii(n[j]);
		}

		switch (count)
		{
		case 1:
			voutf("K{\\footnote K %s}", n[0]);
			break;
		case 2:
			voutf("K{\\footnote K %s, %s}", n[0], n[1]);
			if (use_mirrored_indices)
				voutf("K{\\footnote K %s, %s}", n[1], n[2]);
			break;
		case 3:
			voutf("K{\\footnote K %s, %s, %s}", n[0], n[1], n[2]);
			break;
		}
		break;

	case TORTF:
		for (j = 0; j < 3; j++)
		{
			del_internal_styles(n[j]);
			replace_udo_quotes(n[j]);
			convert_tilde(n[j]);
		}

		switch (count)
		{
		case 1:
			voutf("{\\xe\\v %s}", n[0]);
			break;
		case 2:
			voutf("{\\xe\\v %s\\:%s}", n[0], n[1]);
			if (use_mirrored_indices)
				voutf("{\\xe\\v %s\\:%s}", n[1], n[0]);
			break;
		case 3:
			voutf("{\\xe\\v %s\\:%s\\:%s}", n[0], n[1], n[2]);
			break;
		}
		break;

	case TOSTG:
	case TOAMG:
		for (j = 0; j < 3; j++)
		{
			del_internal_styles(n[j]);
			replace_udo_quotes(n[j]);
			convert_tilde(n[j]);
			index2stg(n[j]);
		}

		switch (count)
		{
		case 1:
			voutlnf("@index \"%s\"", n[0]);
			break;
		case 2:
			voutlnf("@index \"%s, %s\"", n[0], n[1]);
			if (use_mirrored_indices)
				voutlnf("@index \"%s, %s\"", n[1], n[0]);
			break;
		case 3:
			voutlnf("@index \"%s, %s, %s\"", n[0], n[1], n[2]);
			break;
		}
		break;

	case TOIPF:
		for (j = 0; j < 3; j++)
		{
			del_internal_styles(n[j]);
			replace_udo_quotes(n[j]);
			convert_tilde(n[j]);
		}

		switch (count)
		{
		case 1:
			voutlnf(":i1.%s", n[0]);
			break;
		case 2:
			voutlnf(":i1.%s, %s", n[0], n[1]);
			if (use_mirrored_indices)
				voutlnf(":i1.%s, %s", n[1], n[0]);
			break;
		case 3:
			voutlnf(":i1.%s, %s, %s", n[0], n[1], n[2]);
			break;
		}
		break;

	case TOASC:
		for (j = 0; j < count; j++)
		{
			del_internal_styles(n[j]);
			replace_udo_quotes(n[j]);
			convert_tilde(n[j]);
		}

		add_idxlist_item(n[0], n[1], n[2]);
		if (use_mirrored_indices && count == 2)
			add_idxlist_item(n[1], n[0], n[2]);
		break;

	case TOMHH:
		for (j = 0; j < 3; j++)
		{
			delete_all(n[j], "!-");
			c_internal_styles(n[j]);
			replace_udo_quotes(n[j]);
			convert_tilde(n[j]);
		}
		output_htmlhelp_index(count, n[0], n[1], n[2]);
		break;
	}

	bCalledIndex = TRUE;
}





/*******************************************************************************
*
*  c_heading():
*     make heading
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_internal_heading(TOCTYPE level)
{
	char name[LINELEN], n[512], align[64];
	_BOOL inside_center, inside_right;
	char cmd[3 * TOC_MAXDEPTH + 20];
	TOCTYPE i;

	tokcpy2(name, ArraySize(name));

	if (name[0] == EOS)
	{
		strcpy(cmd, META_S);
		for (i = TOC_NODE1; i < level; i++)
			strcat(cmd, "sub");
		strcat(cmd, "heading");
		error_missing_parameter(cmd);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	save_upr_entry_heading(level - TOC_NODE1 + 1, sCurrFileName, current_node_name_sys, uiCurrFileLine);
	check_styles(name);

	inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
	inside_right = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		c_internal_styles(name);
		switch (level)
		{
		case TOC_NODE1:
			voutlnf("{\\Large{\\bf %s}}", name);
			break;
		case TOC_NODE2:
			voutlnf("{\\large{\\bf %s}}", name);
			break;
		case TOC_NODE3:
		default:
			voutlnf("{\\normalsize{\\bf %s}}", name);
			break;
		}
		outln("");
		break;

	case TOINF:
		c_internal_styles(name);
		outln("");
		switch (level)
		{
		case TOC_NODE1:
			voutlnf("@chapheading %s", name);
			break;
		case TOC_NODE2:
			voutlnf("@heading %s", name);
			break;
		case TOC_NODE3:
		default:
			voutlnf("@subheading %s", name);
			break;
		}
		outln("");
		break;

	case TORTF:
		c_rtf_styles(name);
		c_rtf_quotes(name);
		align[0] = EOS;
		if (inside_center)
			strcpy(align, "\\qc");
		if (inside_right)
			strcpy(align, "\\qr");
		voutlnf("%s{\\fs%d\\b %s}\\par\\pard\\par", align, laydat.nodesize[level + 1], name);
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		c_win_styles(name);
		align[0] = EOS;
		if (inside_center)
			strcpy(align, "\\qc");
		if (inside_right)
			strcpy(align, "\\qr");
		voutlnf("{%s\\fs%d\\b %s}\\par\\pard\\par", align, iDocPropfontSize + rtf_structure_height[level + 1], name);
		break;

	case TOKPS:
		outln("newline");
		voutlnf("%d changeFontSize", laydat.nodesize[level + 1]);
		node2postscript(name, KPS_CONTENT);
		outln("Bon");
		voutlnf("(%s) udoshow", name);
		outln("Boff");
		voutlnf("%d changeFontSize", laydat.propfontsize);
		outln("newline");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		c_internal_styles(name);
		n[0] = EOS;
#if 0
		if (html_doctype == HTML5)
		{
			if (inside_center)
				strcpy(n, " class=\"UDO_td_align_center\"");

			if (inside_right)
				strcpy(n, " class=\"UDO_td_align_right\"");
		} else
#endif
		{
			if (inside_center)
				strcpy(n, " align=\"center\"");
			if (inside_right)
				strcpy(n, " align=\"right\"");
		}
		voutlnf("<h%d%s>%s</h%d>", html_nodesize + level, n, name, html_nodesize + level);
		break;

	case TOASC:
	case TOPCH:
		c_internal_styles(name);
		outln("");
		outln(name);
		output_ascii_line(&asc_structure_chars[level], strlen(name));
		outln("");
		break;

	case TOMAN:
		if (level == TOC_NODE1)
			my_strupr(name);
		sprintf(n, " %s%s%s", BOLD_ON, name, BOLD_OFF);
		c_internal_styles(n);
		outln(n);
		break;

	case TONRO:
		if (level == TOC_NODE1)
			my_strupr(name);
		voutlnf(".SH %s", name);
		break;

	case TOSTG:
	case TOAMG:
		sprintf(n, "%s%s%s", UNDER_ON, name, UNDER_OFF);
		if (inside_center)
			strcenter(n, zDocParwidth);
		if (inside_right)
			strright(n, zDocParwidth);
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

	case TODRC:
	case TOHPH:
	case TOIPF:
	case TOLYX:
		break;
	}
}


LOCAL void c_heading(void)
{
	c_internal_heading(TOC_NODE1);
}


LOCAL void c_subheading(void)
{
	c_internal_heading(TOC_NODE2);
}


LOCAL void c_subsubheading(void)
{
	c_internal_heading(TOC_NODE3);
}


LOCAL void c_subsubsubheading(void)
{
	c_internal_heading(TOC_NODE4);
}


LOCAL void c_subsubsubsubheading(void)
{
	c_internal_heading(TOC_NODE5);
}


LOCAL void c_subsubsubsubsubheading(void)
{
	c_internal_heading(TOC_NODE6);
}


LOCAL void c_subsubsubsubsubsubheading(void)
{
	c_internal_heading(TOC_NODE7);
}


LOCAL void c_subsubsubsubsubsubsubheading(void)
{
	c_internal_heading(TOC_NODE8);
}


LOCAL void c_subsubsubsubsubsubsubsubheading(void)
{
	c_internal_heading(TOC_NODE9);
}





/*******************************************************************************
*
*  c_listheading():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_internal_listheading(int offset)
{
	char name[LINELEN];
	char sFontBeg[512];
	char sFontEnd[32];
	char align[64];
	_BOOL inside_center, inside_right;
	int iSize;
	char cmd[3 * TOC_MAXDEPTH + 20];
	int i;

	tokcpy2(name, ArraySize(name));

	if (name[0] == EOS)
	{
		strcpy(cmd, "!list");
		for (i = 3; i > offset; i--)
			strcat(cmd, "sub");
		strcat(cmd, "heading");
		error_missing_parameter(cmd);
		return;
	}

	convert_tilde(name);
	replace_udo_quotes(name);
	delete_all_divis(name);

	check_styles(name);

	inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
	inside_right = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);

	switch (desttype)
	{
	case TOHAH:
	case TOHTM:
	case TOMHH:
		c_internal_styles(name);
		align[0] = EOS;
#if 0
		if (html_doctype == HTML5)
		{
			if (inside_center)
				strcpy(align, " class=\"UDO_td_align_center\"");

			if (inside_right)
				strcpy(align, " class=\"UDO_td_align_right\"");
		} else
#endif
		{
			if (inside_center)
				strcpy(align, " align=\"center\"");
			if (inside_right)
				strcpy(align, " align=\"right\"");
		}

		sFontBeg[0] = EOS;
		sFontEnd[0] = EOS;
		if (sDocHtmlPropfontName[0] != EOS)
		{
			iSize = iDocHtmlPropfontSize + offset;
			sprintf(sFontBeg, "<font face=\"%s\" size=\"%s%d\">", sDocHtmlPropfontName, iSize >= 0 ? "+" : "", iSize);
			strcpy(sFontEnd, "</font>");
		}
#if 0
		if (html_doctype == HTML5)
		{
			voutlnf("<tr><td class=\"UDO_td_valign_top %s\" colspan=\"2\">&nbsp;<br%s>%s<b>%s</b>",
					align, closer, sFontBeg, name);
		} else
#endif
		{
			voutlnf("<tr><td valign=\"top\"%s colspan=\"2\">&nbsp;%s%s<b>%s</b>", align, xhtml_br, sFontBeg, name);
		}

		if (bEnv1stItem[iEnvLevel])
		{
			voutlnf("%s</td></tr>", sFontEnd);
		}
		break;
	}
}


LOCAL void c_listheading(void)
{
	c_internal_listheading(3);
}

LOCAL void c_listsubheading(void)
{
	c_internal_listheading(2);
}

LOCAL void c_listsubsubheading(void)
{
	c_internal_listheading(1);
}

LOCAL void c_listsubsubsubheading(void)
{
	c_internal_listheading(0);
}

LOCAL void c_listsubsubsubsubheading(void)
{
	c_internal_listheading(-1);
}

LOCAL void c_listsubsubsubsubsubheading(void)
{
	c_internal_listheading(-2);
}

LOCAL void c_listsubsubsubsubsubsubheading(void)
{
	c_internal_listheading(-3);
}

LOCAL void c_listsubsubsubsubsubsubsubheading(void)
{
	c_internal_listheading(-4);
}

LOCAL void c_listsubsubsubsubsubsubsubsubheading(void)
{
	c_internal_listheading(-5);
}



/*******************************************************************************
*
*  c_newpage():
*     make newpage
*
*  Notes:
*     UDO command: (!newpage)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_newpage(void)
{
	switch (desttype)
	{
	case TOTEX:
		outln("");
		outln("\\newpage");
		break;

	case TOPDL:
		outln("");
		outln("\\newpage");
		break;

	case TOINF:
		outln("@page");
		break;

	case TOLYX:
		outln("");
		outln("\\pagebreak_bottom");
		break;

	case TORTF:
		out("\\page ");
		break;

	case TOMAN:
		if (iManPageLength > 0)
		{
			while (iManPageLines < iManPageLength - MAN_BOTTOMLINES)
			{
				if (!bTestmode)
					fprintf(outfile.file, "\n");
				iManPageLines++;
				outlines++;
			}
			man_bottomline();
			iManPagePages++;
			iManPageLines = 0;
			man_headline();
		}
		break;

	case TOASC:
		if (use_formfeed)
		{
			out("\014");
		}
		break;

	case TOKPS:
		outln("newpage");
		break;

	case TOHTM:
		outln("<span class=\"page-break\"></span>");
		break;

	case TOHAH:
	case TOMHH:
		outln("<span style=\"page-break-after:always\"></span>");
		break;

	case TODRC:
	case TOHPH:
	case TOIPF:
		break;
	}
}





/*******************************************************************************
*
*  c_tunix():
*     do nothing
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_tunix(void)
{
}





/*******************************************************************************
*
*  c_nop():
*     do nothing but toggle the _BOOL nop_detected
*
*  Notes:
*     Use c_nop() for debugging, just by inserting !nop in the UDO document
*     in front of a critical position.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_nop(void)
{
	bNopDetected = !bNopDetected;
}





/*******************************************************************************
*
*  c_break():
*     break UDO document translation
*
*  Notes:
*     When the UDO command !break is found in the document environment of a 
*     UDO manual source, the translation is stopped immediately.
*
*     !break is a "real" command now and thus can be placed between inquiry
*     commands.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_break(void)
{
	bBreakInside = TRUE;
	if (bInsideDocument)
		c_end_document();
}





/*******************************************************************************
*
*  c_error():
*     output an error (even into the log) and quit the application
*
*  Notes:
*     !error
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_error(void)
{
	char e[LINELEN];

	tokcpy2(e, ArraySize(e));
	error_message("%s", e);

	bBreakInside = TRUE;
	if (bInsideDocument)
		c_end_document();

	bFatalErrorDetected = TRUE;
}





/*******************************************************************************
*
*  c_sloppy():
*     set the internal sloppy flag
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_sloppy(void)
{
	bDocSloppy = TRUE;
}





/*******************************************************************************
*
*  c_fussy():
*     unset the internal sloppy flag
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_fussy(void)
{
	bDocSloppy = FALSE;
}





/*******************************************************************************
*
*  c_code_source():
*     change internal encoding for source documents
*
*  Notes:
*     Reacts on the UDO command "!code_source [xxx]" and sets iEncodingSource.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_code_source(void)
{
	char s[256];
	size_t i;

	if (token[1][0] == EOS)
	{
		error_missing_parameter("!code_source");
		return;
	}

	tokcpy2(s, ArraySize(s));

	delete_once(s, "[");
	delete_last(s, "]");

	for (i = 0; i < ArraySize(udocharset); i++)
	{									/* compare whole string to avoid conflicts */
		/*  with e.g. "l1" and "l10" */
		if (my_stricmp(s, udocharset[i].magic) == 0)
		{
			iEncodingSource = udocharset[i].codepage;
			return;
		}
	}

	error_no_charset(s);
}





/*******************************************************************************
*
*  c_code_target():
*     change internal encoding for target documents
*
*  Notes:
*     Reacts on the UDO command "!code_target [xxx]" and sets iEncodingTarget.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_code_target(void)
{
	char s[256];
	size_t i;

	if (token[1][0] == EOS)				/* this command needs a parameter */
	{
		error_missing_parameter("!code_target");
		return;
	}

	tokcpy2(s, ArraySize(s));

	delete_once(s, "[");
	delete_last(s, "]");

	for (i = 0; i < ArraySize(udocharset); i++)
	{									/* compare whole string to avoid conflicts */
		/*  with e.g. "l1" and "l10" */
		if (my_stricmp(s, udocharset[i].magic) == 0)
		{
			set_encoding_target(udocharset[i].codepage);

			lang_changed = TRUE;
			return;
		}
	}

	error_no_charset(s);
}





/*******************************************************************************
*
*  c_autoref():
*     handle the autoref commands
*
*  Notes:
*     !autoref [off] = TOC.C doesn't create automatic crosslinks
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_autoref(void)
{
	_BOOL newoff;

	if (token_counter <= 1)
	{
		error_missing_parameter(CMD_AUTOREF);
		return;
	}

	newoff = check_off();

	if (newoff && bDocAutorefOff)
	{
		error_not_active(CMD_AUTOREF);
		return;
	}

	if (!newoff && !bDocAutorefOff)
	{
		error_still_active(CMD_AUTOREF);
		return;
	}

	bDocAutorefOff = newoff;

	switch (desttype)
	{
	case TOSTG:
	case TOAMG:
		if (bDocAutorefOff)
			outln("@autorefoff");
		else
			outln("@autorefon");
		break;
	}
}


LOCAL void c_limage(void)
{
	if (token_counter <= 1)
	{
		error_missing_parameter("!stg_limage");
		return;
	}

	bStgLimage = !check_off();
}





/*******************************************************************************
*
*  c_autoref_items():
*     handle the autoref_items commands
*
*  Notes:
*     !autoref_items [off] = ENV.C doesn't create automatic references
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_autoref_items(void)
{
	_BOOL newoff;

	if (token_counter <= 1)
	{
		error_missing_parameter(CMD_AUTOREF_ITEMS);
		return;
	}

	newoff = check_off();

	if (newoff && bDocAutorefItemsOff)
	{
		error_not_active(CMD_AUTOREF_ITEMS);
		return;
	}

	if (!newoff && !bDocAutorefItemsOff)
	{
		error_still_active(CMD_AUTOREF_ITEMS);
		return;
	}

	bDocAutorefItemsOff = newoff;
}





/*******************************************************************************
*
*  c_universal_charset():
*     handle the !universal_charset command
*
*  Notes:
*     !universal_charset [on] = 
*     UDO universal char strings like (!"a) or (!"U) are converted into 
*     their recoded equivalents ("ae" or "Ue").
*
*     All UDO source documents seem to be parsed twice (2nd run from a TMP file),
*     so we should avoid to throw error messages when a switch is set again
*     just by re-parsing the same content.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_universal_charset(void)
{
	_BOOL newon;

	if (token_counter <= 1)
	{
		error_missing_parameter(CMD_UNIVERSAL_CHARSET);
		return;
	}

	newon = check_on();

#if 0
	/* disabled because unnecessary,
	   and makes it almost impossible to explicitly
	   change setting when needed
	 */
	if (newon && bDocUniversalCharsetOn)
	{
		error_already_active(CMD_UNIVERSAL_CHARSET);
		return;
	}

	if (!newon && !bDocUniversalCharsetOn)
	{
		error_not_active(CMD_UNIVERSAL_CHARSET);
		return;
	}
#endif

	bDocUniversalCharsetOn = newon;
}





/*******************************************************************************
*
*  c_rtf_keep_tables():
*     handle the rtf_keep_tables commands
*
*  Notes:
*     !rtf_keep_tables [on] = RTF tables are output as a block which will not
*     be wrapped by Microsoft Word. Else long tables will also be wrapped.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_rtf_keep_tables(void)
{
	if (token_counter <= 1)
	{
		error_missing_parameter(CMD_RTF_KEEP_TABLES);
		return;
	}

	bDocRtfKeepTablesOn = check_on();
}





/*******************************************************************************
*
*  c_verbatim_backcolor():
*     set background color for HTML verbatim environments
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_verbatim_backcolor(void)
{
	_BOOL ret;

	struct rgb_and_color color;

	if (token[1][0] == EOS)
		return;

	ret = get_html_color_or_rgb(token[1], &color);

	if (ret)
	{
		sDocVerbatimBackColor = color;
	}
}





/*******************************************************************************
*
*  output_empty_lines():
*     Ausgabe von <count> zusaetzlichen Leerzeilen.
*     Wird von c_*skip verwendet.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_empty_lines(const int count)
{
	register int i;

	if (count <= 0)
		return;

	if (desttype == TOINF)
	{
		voutlnf("@sp %d", count);
		return;							/* done */
	}

	for (i = 0; i < count; i++)
	{
		switch (desttype)
		{
		case TORTF:
		case TOAQV:
		case TOWIN:
		case TOWH4:
			outln(rtf_par);
			break;
		case TOHAH:
		case TOHTM:
		case TOMHH:
			outln(xhtml_br);
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





/*******************************************************************************
*
*  c_bigskip():
*     output a "big newline"
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_bigskip(void)
{
	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\bigskip");
		break;

	case TOINF:
		outln("@sp 3");
		break;

	case TOKPS:
		outln("newline newline newline");
		outln("");
		break;

	case TOLYX:
		outln("\\added_space_bottom bigskip");
		break;

	case TOIPF:
	case TOHPH:
		break;

	default:
		output_empty_lines(3);
		break;
	}
}





/*******************************************************************************
*
*  c_medskip():
*     output a "medium newline"
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_medskip(void)
{
	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\medskip");
		break;

	case TOINF:
		outln("@sp 2");
		break;

	case TOLYX:
		outln("\\added_space_bottom medskip");
		break;

	case TOKPS:
		outln("newline newline");
		outln("");
		break;

	case TOIPF:
	case TOHPH:
		break;

	default:
		output_empty_lines(2);
		break;
	}
}





/*******************************************************************************
*
*  c_smallskip():
*     output a "small newline"
*
*  return:
*     -
*
******************************************|************************************/


LOCAL void c_smallskip(void)
{
	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		outln("\\smallskip");
		break;

	case TOINF:
		outln("@sp 1");
		break;

	case TOLYX:
		outln("\\added_space_bottom smallskip");
		break;

	case TOKPS:
		outln("newline");
		outln("");
		break;

	case TOIPF:
	case TOHPH:
		break;

	default:
		output_empty_lines(1);
		break;
	}
}





/*******************************************************************************
*
*  c_udolink():
*     fuegt einen Link samt Bild auf der UDO-Seite ein
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_udolink(void)
{
	char sTemp[64];
	char nodename[512];
	char sGifSize[80];
	_BOOL inside_center, inside_right;
	char border[20];

	uses_udolink = TRUE;

	switch (iUdopass)
	{
	case PASS1:
		break;

	case PASS2:
		inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
		inside_right = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);

		tokcpy2(nodename, ArraySize(nodename));

		switch (desttype)
		{
		case TOHAH:
		case TOHTM:
		case TOMHH:
			sGifSize[0] = EOS;
			if (uiGifMwWidth != 0 && uiGifMwHeight != 0)
			{
				sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiGifMwWidth, uiGifMwHeight);
			}

			strcpy(sTemp, "<p>");
			strcpy(border, " border=\"0\"");
#if 0
			if (html_doctype == HTML5)
			{
				if (inside_center)
					strcpy(sTemp, "<p class=\"UDO_p_align_center\">");
				if (inside_right)
					strcpy(sTemp, "<p class=\"UDO_p_align_right\">");
				border[0] = EOS;
			} else
#endif
			{
				if (inside_center)
					strcpy(sTemp, "<p align=\"center\">");
				if (inside_right)
					strcpy(sTemp, "<p align=\"right\">");
			}

			if (nodename[0] == EOS)
			{
				voutlnf("%s<a href=\"%s\"><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s></a>",
						sTemp, UDO_URL, GIF_MW_NAME, UDO_MADE, UDO_MADE, border, sGifSize, xhtml_closer);
			} else
			{
				gen_references(nodename, TRUE, GIF_MW_NAME, uiGifMwWidth, uiGifMwHeight);
				voutlnf("%s%s", sTemp, nodename);
			}
			outln("</p>");
			bParagraphOpen = FALSE;
			break;

		case TOWIN:
		case TOWH4:
			strcpy(sTemp, "ql");
			if (inside_center)
				strcpy(sTemp, "qc");
			if (inside_right)
				strcpy(sTemp, "qr");
			voutlnf("\\%s{\\{%s %s\\}}\\par\\par\\pard", sTemp, bDocInlineBitmaps ? "bmc" : "bmcwd", BMP_MW_NAME);
			break;

		case TOSTG:
		case TOAMG:
			if (!no_images)
				voutlnf("@limage \"%s\" 0", IMG_MW_NAME);
			break;

		case TORTF:
			if (!no_images)
				c_bmp_output(BMP_MW_NAME, "", TRUE);
			break;

		case TOLYX:
			if (!no_images)
				c_eps_output(EPS_MW_NAME, "", TRUE);
			break;

		case TOPDL:
			if (!no_images)
				c_png_output(PNG_MW_NAME, "", TRUE);
			break;

		case TOTEX:
			if (!no_images)
			{
				switch (iTexVersion)
				{
				case TEX_LINDNER:
				case TEX_STRUNK:
					c_img_output(IMG_MW_NAME, "", TRUE, TRUE);
					break;
				case TEX_EMTEX:
					/*
					   if (!c_msp_output(filename, "", TRUE))
					   c_pcx_output(filename, "", TRUE);
					 */
					break;
				case TEX_MIKTEX:
					c_eps_output(EPS_MW_NAME, "", TRUE);
					break;
				case TEX_TETEX:
					c_eps_output(EPS_MW_NAME, "", TRUE);
					break;
				}
			}
			break;

		case TOIPF:
			if (!no_images)
				c_bmp_output(BMP_MW_NAME, "", TRUE);
			break;
		}
		break;

	case PASSU:
		/* outln("!udolink"); */
		break;
	}
}





/*******************************************************************************
*
*  c_toplink():
*     Fuegt einen Link samt Bild an den Anfang der Seite ein.
*     (Unterstuetzung nur fuer Hypertext-Formate.)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_toplink(void)
{
	char sGifSize[64];
	_UWORD w, h, bitcnt;

	uses_toplink = TRUE;

	switch (iUdopass)
	{
	case PASS1:
		break;
	case PASS2:
		sGifSize[0] = EOS;
		switch (desttype)
		{
		case TOHAH:
		case TOHTM:
		case TOMHH:
			if (!no_images)
			{
				char border[20];

				strcpy(border, " border=\"0\"");
#if 0
				if (html_doctype == HTML5)
					border[0] = EOS;
#endif
				get_picture_size(GIF_TP_NAME, NULL, &w, &h, &bitcnt);
				if (w != 0 && h != 0)
					sprintf(sGifSize, " width=\"%u\" height=\"%u\"", w, h);
				voutlnf("<p><a href=\"#\"><img src=\"%s\" alt=\"\" title=\"\"%s%s%s></a></p>", GIF_TP_NAME, border,
						sGifSize, xhtml_closer);
			}
			break;
		}
		break;
	case PASSU:
		/* outln("!toplink"); */
		break;
	}
}





/*******************************************************************************
*
*  c_tex_dpi():
*     set dpi value for image output with LaTeX
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_tex_dpi(void)
{
	iTexDPI = atoi(token[1]);
	if (iTexDPI <= 0)
		iTexDPI = 100;
}





/*******************************************************************************
*
*  c_tex_verb():
*     set the char which is used for \verb... in LaTeX
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_tex_verb(void)
{
	cTexVerb = token[1][0];
	if (cTexVerb == EOS)
		cTexVerb = VERB_C;
}





/*******************************************************************************
*
*  c_win_charwidth():
*     set the char width for WinHelp
*
*  Notes:
*     The char width is used for indentation in lists an tables and cannot be 
*     inquired from the system by UDO.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_win_charwidth(void)
{
	iDocCharwidth = atoi(token[1]);
	if (iDocCharwidth <= 0)
		iDocCharwidth = 150;
}





/*******************************************************************************
*
*  c_wh4_charwidth():
*     set the char width for WinHelp 4
*
*  Notes:
*     The char width is used for indentation in lists an tables and cannot be 
*     inquired from the system by UDO.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_wh4_charwidth(void)
{
	iDocCharwidth = atoi(token[1]);
	if (iDocCharwidth <= 0)
		iDocCharwidth = 150;
}





/*******************************************************************************
*
*  c_rtf_charwidth():
*     set the char width for RTF
*
*  Notes:
*     The char width is used for indentation in lists an tables and cannot be 
*     inquired from the system by UDO.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_rtf_charwidth(void)
{
	iDocCharwidth = atoi(token[1]);
	if (iDocCharwidth <= 0)
		iDocCharwidth = 150;
}





/*******************************************************************************
*
*  c_rtf_add_color():
*     add colors to RTF file header
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_rtf_add_color(void)
{
	um_strncpy(sDocColour, token[1], 50, ArraySize(sDocColour), "c_rtf_add_color[1]");

	qreplace_all(sDocColour, ";", 1, ";\n", 2);
	qreplace_last(sDocColour, ";\n", 2, ";", 1);
}





/*******************************************************************************
*
*  c_html_img_suffix():
*     set file suffix for use in !image and (!img) commands in HTML
*
*  Notes:
*     Default: .gif
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_html_img_suffix(void)
{
	sDocImgSuffix[0] = EOS;
	um_strcpy(sDocImgSuffix, token[1], ArraySize(sDocImgSuffix) - 1, "!html_img_suffix");

	if (sDocImgSuffix[0] != EOS)
	{
		if (sDocImgSuffix[0] != '.')
		{
			strinsert(sDocImgSuffix, ".");
		}
	}
}





/*******************************************************************************
*
*  c_html_nodesize():
*     set node size for headlines in HTML
*
*  Notes:
*     Default: 1 -> <h1>...</h1>.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_html_nodesize(void)
{
	html_nodesize = atoi(token[1]);
	if (html_nodesize < 1)
		html_nodesize = 1;
	if (html_nodesize > 3)
		html_nodesize = 3;
}





/*******************************************************************************
*
*  c_htag_img_suffix():
*     set file suffix for use in !image and (!img) commands in HP-Helptag-SGML
*
*  Notes:
*     Default: .tiff
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_htag_img_suffix(void)
{
	sDocImgSuffix[0] = EOS;
	um_strcpy(sDocImgSuffix, token[1], ArraySize(sDocImgSuffix) - 1, "!htag_img_suffix");

	if (sDocImgSuffix[0] != EOS)
	{
		if (sDocImgSuffix[0] != '.')
		{
			strinsert(sDocImgSuffix, ".");
		}
	}
}


/*******************************************************************************
*
*  c_tabwidth():
*     set tabulator positions for verbatim environments
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_tabwidth(void)
{
	bDocTabwidth = atoi(token[1]);

	/* tabwidth von 0 zulassen, dann spaeter keine Ersetzung */
	if (bDocTabwidth < 0)
		bDocTabwidth = 0;
	if (bDocTabwidth > 8)
		bDocTabwidth = 8;
}





/*******************************************************************************
*
*  c_verbatimsize():
*     set font size for verbatim environments
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_verbatimsize(void)
{
	if (strstr(token[1], "normal"))
	{
		iDocVerbatimSize = VERB_NORMAL;
		return;
	}

	if (strstr(token[1], "small"))
	{
		iDocVerbatimSize = VERB_SMALL;
		return;
	}

	if (strstr(token[1], "tiny"))
	{
		iDocVerbatimSize = VERB_TINY;
		return;
	}

	if (strstr(token[1], "large"))
	{
		iDocVerbatimSize = VERB_LARGE;
		return;
	}

	if (strstr(token[1], "huge"))
	{
		iDocVerbatimSize = VERB_HUGE;
		return;
	}

	error_missing_parameter(CMD_VERBATIMSIZE);
}





/*******************************************************************************
*
*  c_linedrawsize():
*     set font size for linedraw environments
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_linedrawsize(void)
{
	if (strstr(token[1], "normal"))
	{
		iDocLinedrawSize = VERB_NORMAL;
		return;
	}

	if (strstr(token[1], "small"))
	{
		iDocLinedrawSize = VERB_SMALL;
		return;
	}

	if (strstr(token[1], "tiny"))
	{
		iDocLinedrawSize = VERB_TINY;
		return;
	}

	if (strstr(token[1], "large"))
	{
		iDocLinedrawSize = VERB_LARGE;
		return;
	}

	if (strstr(token[1], "huge"))
	{
		iDocLinedrawSize = VERB_HUGE;
		return;
	}

	error_missing_parameter(CMD_LINEDRAWSIZE);
}





/*******************************************************************************
*
*  c_check_raw():
*     check if a line contains a format specific command
*
*  Notes:
*     Ausgewertet wird die oben angelegte Tabelle <udospec>. Enthaelt die Zeile 
*     ein solches Kommando, wird der Rest unveraendert ausgegeben. Die Funktion 
*     erhaelt eine unbearbeitete Zeile, also koennen die Befehle noch eingerueckt 
*     sein!
*
*  Beispiel: !raw [tex] \documentstyle[german]{article}
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_check_raw(char *s)
{
	size_t contlen;
	char *ptr, inhalt[512], *cont, *data;

	ptr = s;

	/* find first non-blank */
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;

	if (*ptr == EOS)
		return;

	if (strncmp(ptr, "!raw", 4) != 0)
		return;

	if (ptr[4] != ' ' && ptr[4] != '\t')
		return;

	ptr += 5;

	/* find next non-blank */
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;

	/* Klammerinhalt ermitteln, wenn bl==0 dann kein Inhalt oder fehlende Klammern */
	contlen = get_brackets_ptr(ptr, &cont, &data);
	if (contlen == 0 || cont == NULL || data == NULL)
	{
		error_syntax_error();
		s[0] = EOS;
		return;
	}

	/* Klammerinhalt kopieren und Zeiger auf den Rest der Zeile setzen */
	inhalt[0] = EOS;
	strncpy(inhalt, cont, contlen);
	inhalt[contlen] = EOS;

	/* Letzten Absatz ausgeben */
	if (token_counter > 0)
	{
		token_output(TRUE, FALSE);
	}

	/* Schauen, ob diese Zeile fuer das aktuelle Format bestimmt ist */
	if (str_for_desttype(inhalt, TRUE) > 0)
	{
		/* Rest der Zeile ausgeben */
		outln(data + 1);
	}

	s[0] = EOS;
}





/*******************************************************************************
*
*  convert_image():
*     handle the !image command and prepare all info for the IMG.C functions
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void convert_image(const _BOOL visible)
{
	char filename[512];
	char caption[512];
	char sTemp[1024];
	char *ptr;

	if (no_images)
		return;

	switch (desttype)					/* these formats don't support images */
	{
	case TOASC:
	case TODRC:
	case TOINF:
	case TOKPS:
	case TOMAN:
	case TONRO:
	case TOPCH:
	case TOSRC:
	case TOSRP:
	case TOTVH:
		return;
	}


	/* Lange Dateinamen mit Leerzeichen abfangen */
	/*Bsp.:  !image "Ein Testbild" Hier ist die Unterschrift */

	if (token[1][0] == '\"')
	{
		tokcpy2(sTemp, ArraySize(sTemp));
		ptr = strchr(sTemp + 1, '\"');	/* zweites " suchen */

		if (ptr)
		{
			ptr[0] = EOS;
			strcpy(filename, sTemp + 1);
			strcpy(caption, ptr + 1);
			del_whitespaces(caption);
		} else
		{
			strcpy(filename, sTemp);
			caption[0] = EOS;
		}
	} else
	{
		um_strcpy(filename, token[1], ArraySize(filename), "convert_image[1]");
		token[1][0] = EOS;
		tokcpy2(caption, ArraySize(caption));
		del_whitespaces(caption);
	}

#if 0
	auto_quote_chars(caption, TRUE);
	c_divis(caption);
	delete_all_divis(caption);
	c_vars(caption);
	replace_udo_quotes(caption);
#endif

	check_styles(caption);

	switch (desttype)
	{
	case TOSTG:
	case TOAMG:
		c_internal_styles(caption);
		change_sep_suffix(filename, ".img");
		c_img_output(filename, caption, visible, bStgLimage);
		break;

	case TOTEX:
		qreplace_all(filename, "$\\backslash$", 12, "\\", 1);
		c_internal_styles(caption);
		qreplace_all(filename, "\\_", 2, "_", 1);
		build_image_filename(filename, ".img");

		switch (iTexVersion)
		{
		case TEX_LINDNER:
		case TEX_STRUNK:
			c_img_output(filename, caption, visible, bStgLimage);
			break;
		case TEX_EMTEX:
		case TEX_MIKTEX:
			if (!c_msp_output(filename, caption, visible))
				c_pcx_output(filename, caption, visible);
			break;
		case TEX_TETEX:
			c_eps_output(filename, caption, visible);
			break;
		}
		break;

	case TOPDL:
		c_internal_styles(caption);
		qreplace_all(filename, "\\_", 2, "_", 1);
		c_png_output(filename, caption, visible);
		break;

	case TOLYX:
		replace_all(filename, "\\backslash" INDENT_S, "\\");
		c_internal_styles(caption);
		indent2space(caption);
		c_eps_output(filename, caption, visible);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		del_internal_styles(caption);
		change_sep_suffix(filename, sDocImgSuffix);
		c_html_image_output(filename, caption);
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
		c_bmp_output(filename, caption, visible);
		break;

	case TORTF:
		qreplace_all(filename, "\\\\", 2, "\\", 1);
		c_rtf_quotes(caption);
		c_rtf_styles(caption);
		c_bmp_output(filename, caption, visible);
		break;

	case TOHPH:
		break;
	}
}





/*******************************************************************************
*
*  c_image():
*     wrapper for convert_image(TRUE)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_image(void)
{
	convert_image(TRUE);
}





/*******************************************************************************
*
*  c_image_nonr():
*     wrapper for convert_image(FALSE)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_image_nonr(void)
{
	convert_image(FALSE);
}


/*******************************************************************************
*
*  check_quotes():
*     check wether any quotes are left open
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void check_quotes(void)
{
	if (b1stQuote)
	{
		error_message(_("odd number of \"\""));
		b1stQuote = FALSE;
	}
	if (b1stApost)
	{
		error_message(_("odd number of ''"));
		b1stApost = FALSE;
	}
}





/*******************************************************************************
*
*  c_include():
*     handle the !include command
*
*  Notes:
*     used in ABO.C
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_include(void)
{
	char name[MYFILE_FULL_LEN];

	if (token[1][0] != EOS)
	{
		if (token[1][0] == '\"')
		{
			tokcpy2(name, ArraySize(name));
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		} else
		{
			um_strcpy(name, token[1], ArraySize(name), "!include");
		}

		check_quotes();
		token_reset();
		replace_macros(name);

		switch (iUdopass)
		{
		case PASS1:
			pass1(name);
			break;
		case PASS2:
			pass2(name);
			break;
		case PASSU:
			passU(name);
			break;
		}
		multitasking_interrupt();
	}
}





/*******************************************************************************
*
*  c_include_verbatim():
*     handle the !vinclude command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_include_verbatim(void)
{
	char name[MYFILE_FULL_LEN];

	if (token[1][0] != EOS)
	{
		if (token[1][0] == '\"')
		{
			tokcpy2(name, ArraySize(name));
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		} else
		{
			um_strcpy(name, token[1], ArraySize(name), "!vinclude");
		}

		token_reset();
		replace_macros(name);

		pflag[iUdopass].env = ENV_VERBATIM;

		switch (iUdopass)
		{
		case PASS1:
			pass1(name);
			break;
		case PASS2:
			output_begin_verbatim("UDO_env_verbatim");
			pass2(name);
			output_end_verbatim();
			break;
		case PASSU:
			output_begin_verbatim("UDO_env_verbatim");
			/*
			 * FIXME: doesnt work when the include file contains a '!end_verbatim' command,
			 * because that will already end the '!begin_verbatim' from above
			 */
			passU(name);
			output_end_verbatim();
			break;
		}

		pflag[iUdopass].env = ENV_NONE;
		multitasking_interrupt();
	}
}





/*******************************************************************************
*
*  c_include_preformatted():
*     handle the !pinclude command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_include_preformatted(void)
{
	char name[MYFILE_FULL_LEN];

	if (token[1][0] != EOS)
	{
		if (token[1][0] == '\"')
		{
			tokcpy2(name, ArraySize(name));
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		} else
		{
			um_strcpy(name, token[1], ArraySize(name), "!pinclude");
		}

		token_reset();
		replace_macros(name);

		pflag[iUdopass].env = ENV_PREFORMATTED;

		switch (iUdopass)
		{
		case PASS1:
			pass1(name);
			break;
		case PASS2:
			output_begin_preformatted();
			pass2(name);
			output_end_preformatted();
			break;
		case PASSU:
			output_begin_preformatted();
			passU(name);
			output_end_preformatted();
			break;
		}

		pflag[iUdopass].env = ENV_NONE;
		multitasking_interrupt();
	}
}





/*******************************************************************************
*
*  c_include_linedraw():
*     handle the !ldinclude command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_include_linedraw(void)
{
	char name[MYFILE_FULL_LEN];

	if (token[1][0] != EOS)
	{
		if (token[1][0] == '\"')
		{
			tokcpy2(name, ArraySize(name));
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		} else
		{
			um_strcpy(name, token[1], ArraySize(name), "!linclude");
		}

		token_reset();
		replace_macros(name);

		pflag[iUdopass].env = ENV_LINEDRAW;

		switch (iUdopass)
		{
		case PASS1:
			pass1(name);
			break;
		case PASS2:
			output_begin_linedraw();
			pass2(name);
			output_end_linedraw();
			break;
		case PASSU:
			output_begin_linedraw();
			passU(name);
			output_end_linedraw();
			break;
		}

		pflag[iUdopass].env = ENV_NONE;
		multitasking_interrupt();
	}
}





/*******************************************************************************
*
*  c_include_raw():
*     handle the !rinclude command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_include_raw(void)
{
	char name[MYFILE_FULL_LEN];

	if (token[1][0] != EOS)
	{
		if (token[1][0] == '\"')
		{
			tokcpy2(name, ArraySize(name));
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		} else
		{
			um_strcpy(name, token[1], ArraySize(name), "!rinclude");
		}

		token_reset();
		replace_macros(name);

		pflag[iUdopass].env = ENV_RAW;

		switch (iUdopass)
		{
		case PASS1:
			pass1(name);
			break;
		case PASS2:
			pass2(name);
			break;
		case PASSU:
			outln(CMD_BEGIN_RAW);
			passU(name);
			outln(CMD_END_RAW);
			break;
		}

		pflag[iUdopass].env = ENV_NONE;
		multitasking_interrupt();
	}
}





/*******************************************************************************
*
*  c_include_src():
*     handle the !sinclude command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_include_src(void)
{
	char name[MYFILE_FULL_LEN];

	if (token[1][0] != EOS)
	{
		if (token[1][0] == '\"')
		{
			tokcpy2(name, ArraySize(name));
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		} else
		{
			um_strcpy(name, token[1], ArraySize(name), "!sinclude");
		}

		token_reset();
		replace_macros(name);

		pflag[iUdopass].env = ENV_SOURCECODE;

		switch (iUdopass)
		{
		case PASS1:
			pass1(name);
			break;
		case PASS2:
			output_begin_sourcecode();
			pass2(name);
			output_end_sourcecode();
			break;
		case PASSU:
			output_begin_sourcecode();
			passU(name);
			output_end_sourcecode();
			break;
		}

		pflag[iUdopass].env = ENV_NONE;
		multitasking_interrupt();
	}
}





/*******************************************************************************
*
*  c_include_src():
*     handle the !cinclude command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_include_comment(void)
{
	char name[MYFILE_FULL_LEN];

	if (token[1][0] != EOS)
	{
		if (token[1][0] == '\"')
		{
			tokcpy2(name, ArraySize(name));
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		} else
		{
			um_strcpy(name, token[1], ArraySize(name), "!cinclude");
		}

		token_reset();
		replace_macros(name);

		pflag[iUdopass].env = ENV_COMMENT;
		switch (iUdopass)
		{
		case PASS1:
			pass1(name);
			break;
		case PASS2:
			output_begin_comment();
			pass2(name);
			output_end_comment();
			break;
		case PASSU:
			output_begin_comment();
			passU(name);
			output_end_comment();
			break;
		}

		pflag[iUdopass].env = ENV_NONE;
		multitasking_interrupt();
	}
}





/*******************************************************************************
*
*  c_input():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_input(void)
{
	char *tmp;
	char path[MYFILE_FULL_LEN];
	char name[MYFILE_FULL_LEN];
	size_t sl;

	tmp = getenv("UDOINPUTPATH");
	if (tmp != NULL)
	{
		um_strcpy(path, tmp, ArraySize(path) - 1, "!input");
		sl = strlen(path);
		if (sl > 0 && path[sl - 1] != '\\' && path[sl - 1] != '/')
		{
			um_strcat(path, "/", ArraySize(path), "!input");
		}
	} else
	{
		if (iUdopass != PASS1)
		{
			error_message(_("$UDOINPUTPATH not set!"));
		}
		return;
	}

	if (token[1][0] != EOS)
	{
		if (token[1][0] == '\"')
		{
			tokcpy2(name, ArraySize(name));
			qdelete_once(name, "\"", 1);
			qdelete_last(name, "\"", 1);
		} else
		{
			um_strcpy(name, token[1], ArraySize(name), "!input");
		}

		token_reset();
		replace_macros(name);
		um_strcat(path, name, 512, "!input");
		path_adjust_separator(path);

		switch (iUdopass)
		{
		case PASS1:
			pass1(path);
			break;
		case PASS2:
			pass2(path);
			break;
		case PASSU:
			passU(path);
			break;
		}
		multitasking_interrupt();
	}
}





/*******************************************************************************
*
*  str2silben():
*     hyphenation
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void str2silben(const char *s)
{
	size_t i, sl, yl;
	char syl[MAX_TOKEN_LEN + 1];

	silben_counter = -1;

	/* Kein Trennzeichen enthalten? */
	if ((strchr(s, '-') == NULL) && (strchr(s, DIVIS_C) == NULL))
		return;

	/* Token besteht nur aus einem Bindestrich? */
	if ((s[0] == '-') && (s[1] == EOS))
		return;

	/* <???> Ist das Leeren nicht ueberfluessig, wenn silbe[] */
	/* ueber strcpy() gesetzt und silben_counter benutzt wird? */
	for (i = 0; i < MAXSILBEN; i++)
		silbe[i][0] = EOS;

	syl[0] = EOS;
	yl = 0;

	sl = strlen(s);

	for (i = 0; i < sl; i++)
	{
		syl[yl + 1] = EOS;
		syl[yl] = s[i];
		yl++;

		switch (s[i])
		{
		case '-':
		case '/':
			if (i > 0)
			{
				/* Nur dann trennen, wenn das naechste Zeichen */
				/* keine Zahl, kein Komma und kein ')',']','}' ist */
				if (((s[i + 1] < '0') || (s[i + 1] > '9'))
					&& (s[i + 1] != ',') && (s[i + 1] != ')') && (s[i + 1] != ']') && (s[i + 1] != '}'))
				{
					silben_counter++;
					strcpy(silbe[silben_counter], syl);
					syl[0] = EOS;
					yl = 0;
				}
			}
			break;

		case DIVIS_C:
			silben_counter++;
			strcpy(silbe[silben_counter], syl);
			syl[0] = EOS;
			yl = 0;
			break;
		}
	}

	if (syl[0] != EOS)
	{
		silben_counter++;
		strcpy(silbe[silben_counter], syl);
	}
}





/*******************************************************************************
*
*  check_parwidth():
*     check if !parwidth has a valid parameter
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void check_parwidth(size_t tomaxlen)
{
	if (zDocParwidth <= 0)
		zDocParwidth = tomaxlen;

	if (zDocParwidth < 20)
		zDocParwidth = MAXZEILE;

	if (zDocParwidth > tomaxlen)
		zDocParwidth = tomaxlen;
}





/*******************************************************************************
*
*  malloc_token_output_buffer():
*     allocate memory for token output buffer
*
*  Notes:
*     Da bei WinHelp, HTML und Linuxdoc-SGML erst viel spaeter
*     als nach 70 Zeichen umbrochen wird, wird extra ein Puffer angelegt,
*     damit in token_output nicht z[16384] etc. deklariert werden
*     muss. Da moeglichst dort erst dann umbrochen werden soll,
*     wenn der ganze Absatz in einer Zeile steht und alle Links
*     gesetzt werden koennen, sollte der Buffer so gross wie
*     moeglich sein. Da in der Zeile noch Ersetzungen stattfinden
*     koennen, sollte der Buffer zehnmal so gross sein wie die
*     maximale Zeilenlaenge.
*
*  return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

LOCAL _BOOL malloc_token_output_buffer(void)
{
	static size_t const bs[5] = { 32768U, 16384U, 8192U, 4096U, 2048U };
	static int const ml[5] = { 3200, 1600, 800, 400, 200 };
	int i;

	if (format_uses_output_buffer && use_output_buffer)
	{
		for (i = 0; i < 5; i++)
		{
			tobuffer = (char *) malloc(bs[i]);
			if (tobuffer != NULL)
			{
				check_parwidth(ml[i]);
				return TRUE;
			}
		}
	}

	tobuffer = (char *) malloc(2048);

	if (tobuffer == NULL)
	{
		return FALSE;
	}

	check_parwidth(256);

	return TRUE;
}





/*******************************************************************************
*
*  free_token_output_buffer():
*     release allocated token output buffer
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void free_token_output_buffer(void)
{
	if (tobuffer != NULL)
	{
		free(tobuffer);
		tobuffer = NULL;
	}
}





/*******************************************************************************
*
*  insert_nl_token_buffer():
*     insert line feeds into token output buffer
*
*  Notes:
*     Falls der Puffer verwendet wird, entstehen furchtbar lange
*     Zeilen, die man schlecht nachbearbeiten koennte. Daher
*     werden hier ein paar LFs an geeigneter Stelle eingefuegt.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void insert_nl_token_buffer(void)
{
	char *ptr, *start;
	size_t pl;

	if (tobuffer[0] == EOS)
		return;

	ptr = tobuffer;
	start = tobuffer;
	pl = strlen(ptr);

	while (pl > zDocParwidth && ptr > start)
	{
		ptr += zDocParwidth;
		while (ptr[0] != ' ' && ptr > start)
			ptr--;
		ptr++;
		strinsert(ptr, "\n");
		pl = strlen(ptr);
	}
}





/*******************************************************************************
*
*  toklen():
*     get length of string with all required UDO commands converted
*
*  return:
*     length of string
*
******************************************|************************************/

GLOBAL size_t toklen(const char *s)
{
	size_t len;
	const char *ptr;

	if (s[0] == EOS)
		return 0;

	if (!format_needs_exact_toklen)
		return strlen(s);

	ptr = s;
	len = 0;

	while (*ptr != EOS)
	{
		switch (*ptr)
		{
		case DIVIS_C:
			/* Laenge 0 */
			ptr++;
			break;

		case ESC_C:
			ptr++;
			switch (*ptr)
			{
			case C_PHOLD_MAGIC:
				ptr++;
				/* Laenge des Linktexts addieren */
				len += pholdlen(ptr);
				/* skip phold_counter & terminating ESC_C */
				ptr += 4;
				break;

			case C_STYLE_MAGIC:
				ptr += STYLELEN - 1;
				break;

			default:
				/* skip ESC sequences */
				while (*ptr != EOS && *ptr != ESC_C)
					ptr++;
				if (*ptr != EOS)
					ptr++;
				break;
			}
			break;

		case '!':
			ptr++;
			/* Naechstes Zeichen betrachten */
			switch (*ptr)
			{
			case '/':
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

		case '@':
			ptr++;
			if (desttype == TOSTG && *ptr == '@')
				ptr++;
			len++;
			break;
		case NBSP_C:
		case TILDE_C:
		case INDENT_C:
		default:
			ptr++;
			len++;
			break;
		}
	}

	return len;
}





/*******************************************************************************
*
*  tokcat():
*     concatenate all tokens as of token[1] space-separated to a string
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void tokcat(char *s, size_t maxlen)
{
	int i;
	size_t m = 0;						/* Laenge des bisherigen Strings mitzaehlen */

	for (i = 1; i < token_counter; i++)
	{
		/* add length of new token, eventually included space + Nullbyte */
		m += strlen(token[i]) + 2;

		/* new size is within buffer limit? */
		if (m < maxlen)
		{
			strcat(s, token[i]);
			/* add separating space character */
			if (i < token_counter - 1)
				strcat(s, " ");
		}
	}

	/* buffer limit reached or exceeded? */
	if (m >= maxlen)
	{
		warning_buffer_overrun("tokcat", "", m + 1, maxlen);
	}
}





/*******************************************************************************
*
*  tokcpy2():
*     clear token string and call tokcat()
*
*  Notes:
*     In <s> befinden sich alle danach mit Ausnahme des Kommandos aus
*     token[0] alle Tokens, die durch Leerzeichen getrennt wurden.
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void tokcpy2(char *s, size_t maxlen)
{
	s[0] = EOS;
	tokcat(s, maxlen);
}





/*******************************************************************************
*
*  output_hyphen_line():
*     warn about too long word and save word in hyphen file
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_hyphen_line(const char *s)
{
	/* Erst oeffnen, wenn die Datei gebraucht wird */
	if (!bNoHypfile && !bHypopened && !bHypfailed)
	{
		if (outfile.full[0] != EOS)
		{
			if (sHypfull != 0)
			{
				fHypfile = myFwopen(file_lookup(sHypfull), TOASC);
				if (fHypfile == NULL)
				{
					fHypfile = stderr;
					bHypfailed = TRUE;
					warning_err_hypfile();
					bErrorDetected = TRUE;
				}

				bHypopened = TRUE;
				bHypSaved = TRUE;
				save_upr_entry_outfile(file_lookup(sHypfull));
			}
		}
	}

	if (bHypopened)
	{
		fprintf(fHypfile, "!hyphen %s\n", s);
	}
}





/*******************************************************************************
*
*  warning_short_line():
*     warn about too short line and prepare too long word for hyphenation
*
*  Notes:
*     using output_hyphen_line()
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void warning_short_line(const size_t len, const char *t)
{
	char next[MAX_TOKEN_LEN + 1], *ptr;
	size_t i, sl;
	int nr;

	/* Wenn im naechsten Token bereits ein Trennvorschlag steckt, */
	/* dann die Zeile nicht bemaengeln, da offensichtlich nicht */
	/* besser getrennt werden kann. */
	if (strchr(t, DIVIS_C) != NULL)
		return;

	strcpy(next, t);
	replace_udo_quotes(next);
	del_internal_styles(next);
	replace_placeholders_text(next);

	replace_all(next, NBSP_S, "~");
	replace_all(next, TILDE_S, "!~");

	if (outfile.full[0] != EOS)
		warning_short_destline(outfile.full, outlines + 1, (int) (len), next);

	note_short_sourceline(next);

	if (!bNoHypfile)
	{
		/* Nur den Teil des Wortes bis zum ersten Minus oder Leerzeichen ausgeben. */

		ptr = strchr(next, '-');
		if (ptr != NULL)
			ptr[0] = EOS;

		ptr = strchr(next, ' ');
		if (ptr != NULL)
			ptr[0] = EOS;

		/* Falls ein Wort nur einen Vokal enthaelt, dann hat es */
		/* keinen Sinn, dieses Wort in die Hyphendatei zu schreiben. */
		nr = 0;
		sl = strlen(next);
		for (i = 0; i < sl; i++)
		{
			if (next[i] == 'a' ||
				next[i] == 'e' ||
				next[i] == 'i' ||
				next[i] == 'o' ||
				next[i] == 'u' ||
				next[i] == 'A' ||
				next[i] == 'E' ||
				next[i] == 'I' ||
				next[i] == 'O' ||
				next[i] == 'U' ||
				(iEncodingTarget == CODE_TOS && (next[i] == '\204' ||
												 next[i] == '\224' ||
												 next[i] == '\201' ||
												 next[i] == '\216' ||
												 next[i] == '\231' ||
												 next[i] == '\232' ||
												 next[i] == '\236')))
			{
				nr++;
				if (nr > 1)
					break;
			}
		}

		if (nr > 1)
		{
			/* Interpunktionszeichen entfernen */
			while (sl > 0 && strchr(" !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", next[0]) != NULL)
			{
				memmove(&next[0], &next[1], sl);
				sl--;
			}
			while (sl > 0 && strchr(" !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~", next[sl - 1]) != NULL)
			{
				--sl;
				next[sl] = '\0';
			}
			if (next[0] != EOS)
			{
				output_hyphen_line(next);
			}
		}
	}
}





/*******************************************************************************
*
*  str2tok():
*     decompose a string and copy the contained words to token[]
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void str2tok(const char *s)
{
	char *tok;
	char tmp[LINELEN + 1];
	const char *sep = " \t";			/* space and tab */

	if (token_counter >= MAX_TOKENS)
	{
		error_too_many_tokens();
		return;
	}

	um_strcpy(tmp, s, LINELEN + 1, "str2tok[1]");

	tok = strtok(tmp, sep);
	while ((tok != NULL) && (token_counter < MAX_TOKENS))
	{
		um_strcpy(token[token_counter], tok, MAX_TOKEN_LEN + 1, "str2tok[2]");
		token_counter++;
		tok = strtok(NULL, sep);
	}

	if (token_counter > MAX_TOKENS)
	{
		error_too_many_tokens();
	}
}





/*******************************************************************************
*
*  token_reset():
*     clear the token[] array
*
*  Notes:
*     This has to be done because token_counter isn't checked in many places.
*
*     (used in ABO.C)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void token_reset(void)
{
	register int i;

	for (i = 0; i < token_counter; i++)
		token[i][0] = EOS;
	token_counter = 0;
	tokens_contain_item = FALSE;
}





/*******************************************************************************
*
*  to_check_rtf_quote_indent():
*     right indent quote environments
*
*  Notes:
*     This is a subfunction of token_output().
*
*     In RTF, \ri will be attached.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void to_check_rtf_quote_indent(char *s)
{
	char t[80];
	int i, val;

	if (iEnvLevel > 0)
	{
		val = 0;
		for (i = 0; i <= iEnvLevel; i++)
		{
			if (iEnvType[i] == ENV_QUOT)
			{
				val += iEnvIndent[i];
			}
		}

		if (val > 0)
		{
			switch (desttype)
			{
			case TORTF:
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
}





/*******************************************************************************
*
*  to_check_quote_indent():
*     right indent quote environments
*
*  Notes:
*     This is a subfunction of token_output().
*
*     In ASCII, the paragraph width will be reduced.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void to_check_quote_indent(size_t *u)
{
	int i, val;

	if (iEnvLevel > 0)
	{
		val = 0;
		for (i = 0; i <= iEnvLevel; i++)
		{
			if (iEnvType[i] == ENV_QUOT)
			{
				val += iEnvIndent[i];
			}
		}

		if (val > 0)
		{
			switch (desttype)
			{
			case TOASC:
			case TODRC:
			case TOMAN:
			case TOPCH:
			case TOSTG:
			case TOAMG:
			case TOTVH:
			case TOSRC:
			case TOSRP:
				*u -= val;
				break;
			}
		}
	}
}






/*******************************************************************************
*
*  token_output():
*     format and output paragraphs
*
*  Notes:
*     token_output() is one of the central functions within UDO. It is called 
*     when all tokens of a paragraph have been collected. A 'token' is anything 
*     like a single word which has been detected by checking the word separators, 
*     e.g. ' ' and '\t'. (The end of a paragraph is detected by two line feeds 
*     in a row or by a new UDO command.)
*
*     Within token_output() a full paragraph (or name it a 'section') is output.
*     Some formats even control the width of lines within a paragraph here.
*     We can specially treat the start and the end of a paragraph.
*
*  Example:
*     In ENV_ITEM environment, this function will be called three times for this 
*     source:
*
*     # ---snip---
*     !begin_itemize
*     !item This is an item.
*
*     It has three paragraphs.
*
*     This is the last paragraph.
*     !end_itemize
*     # ---snap---
*
*     In this example, somewhere else the start of the ENV_ITEM is output:
*     # ---snip---
*     "<ul>\n"
*     # ---snap---
*
*     The 1st call of token_output() has these tokens:
*
*     token[0] = "<pseudocode for '<li>'"
*     token[1] = "This"
*     token[2] = "is"
*     token[3] = "an"
*     token[4] = "item."
*     token[5] = ""             <-- Indicates the end of this paragraph content.
*
*     It will be output as paragraph like this (after the pseudocode has been converted):
*
*     # ---snip---
*     "<li>This is an item.\n"
*     # ---snap---
*
*     Depending on the environment type, we have to decide whether to close the 
*     already output paragraph or to just remember that a first paragraph has been
*     output, in order to be able and handle some kind of space between paragraphs
*     just before we output the next paragraph(s).
*
*     The 2nd call of token_output() has these tokens:
*
*     token[0] = "It"
*     token[1] = "has"
*     token[2] = "three"
*     token[3] = "paragraphs"
*     token[4] = ""             <-- Indicates the end of this paragraph content.
*
*     It will be output as paragraph like this:
*
*     # ---snip---
*     "It has three paragraphs.\n"
*     # ---snap---
*
*     The 3rd call of token_output() has these tokens:
*
*     token[0] = "This"
*     token[1] = "is"
*     token[2] = "the"
*     token[3] = "last"
*     token[4] = "paragraph."
*     token[5] = ""             <-- Indicates the end of this paragraph content.
*
*     It will be output as paragraph like this:
*
*     # ---snip---
*     "This is the last paragraph.\n"
*     # ---snap---
*
*     Somewhere else, the end of the ENV_ITEM is output:
*
*     # ---snip---
*     "</li>\n</ul>\n"
*     # ---snap---
*
*
*  ENV_ITEM + ENV_ENUM implementation:
*     In e.g. HTML output, we treat various ENV_... differently:
*
*     ENV_ITEM + ENV_ENUM:
*     !compressed format example:
*
*     # ---snip---
*     <ul> | <ol>
*     <li>[content of 1st paragraph]<br>
*
*     [content of next paragraph(s)]</li>
*     </ul> | </ol>
*     # ---snap---
*
*     non-!compressed format example:
*
*     <ul> | <ol>
*     <li><p>[content of 1st paragraph]<br><br>
*
*     [content of next paragraph(s)]</p></li>
*     </ul> | </ol>
*
*     Note that multiple paragraphs within one <li>...</li> are not separated by
*     inserting additional </p><p> but with <br><br>, which is much easier because 
*     we avoid too splendid listings and can handle the additional space between 
*     paragraphs IN FRONT of any paragraph following the 1st paragraph.
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void token_output(_BOOL reset_internals, _BOOL with_para)
{
	register int i, j;
	int silb;
	char *z = tobuffer;					/* buffer for paragraph content output */
	char sIndent[512];
	size_t umbruch;						/* computes the line width for several formats */
	_BOOL newline = FALSE;				/* TRUE: (!nl) detected, we have to output some linefeed */

	/*   or a line has become too long and must be wrapped */
	_BOOL just_linefeed = FALSE;
	_BOOL use_token;
	_BOOL inside_center,				/* TRUE: we're inside an ENV_CENT */
	 inside_right,						/* TRUE: we're inside an ENV_RIGH */
	 inside_left,						/* TRUE: we're inside an ENV_LEFT */
	 inside_quote;						/* TRUE: we're inside an ENV_QUOT */

	_BOOL inside_compressed,			/* TRUE: this environment should be output 'compressed' */
	 inside_env,						/* TRUE: we're inside ENV_ITEM | ENV_ENUM | ENV_DESC | ENV_LIST */
	 inside_fussy;

	size_t sl, len_zeile, len_silbe, len_token;

	if (token_counter <= 0)				/* nothing to do here */
		return;

	if (!bInsideDocument)				/* we're not allowed to output tokens here */
		return;

	umbruch = zDocParwidth;

	switch (desttype)
	{
	case TOSTG:
	case TOAMG:
		umbruch = zDocParwidth;

		if (toc_inside_popup() && zDocParwidth > 60)
			umbruch = 60;

		break;

	case TOMAN:
		umbruch = zDocParwidth - 5;
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		umbruch = zDocParwidth;

		if (iListLevel > 0 && umbruch > 70)
			umbruch = 70;

		break;

	case TOSRC:
	case TOSRP:
		outln(sSrcRemOn);
		break;
	}

	inside_center = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT);
	inside_right = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_RIGH);
	inside_left = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_LEFT);
	inside_quote = (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_QUOT);
	inside_env = (iItemLevel > 0 || iEnumLevel > 0 || iDescLevel > 0 || iListLevel > 0);

	inside_fussy = ((!inside_center) && (!inside_right) && (!inside_left) && (!bDocSloppy));

	inside_compressed = (iEnvLevel > 0 && bEnvCompressed[iEnvLevel]);

	i = 0;
	z[0] = EOS;
	sIndent[0] = EOS;
	len_zeile = 0;


	if ((token[0][0] != ' ') && (token[0][0] != INDENT_C))
		strcat_indent(z);


	/* --- treat START of paragraph --- */

	switch (desttype)
	{
	case TORTF:
	case TOWIN:
	case TOWH4:
	case TOAQV:
		to_check_rtf_quote_indent(z);

		if (inside_center)
			strcat(z, "\\qc ");

		if (inside_right)
			strcat(z, "\\qr ");

		if (inside_left)
			strcat(z, "\\ql ");

		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:

		if (!inside_compressed)
		{
			if (inside_center)			/* centered text */
			{
#if 0
				if (html_doctype == HTML5)
				{
					strcat(z, "<div class=\"UDO_div_align_center\">\n");
				} else
#endif
				{
					strcat(z, "<div align=\"center\">\n");
				}
			} else if (inside_right)	/* right-justified text */
			{
#if 0
				if (html_doctype == HTML5)
				{
					strcat(z, "<div class=\"UDO_div_align_right\">\n");
				} else
#endif
				{
					strcat(z, "<div align=\"right\">\n");
				}
			} else if (!inside_env)		/* ordinary text in a <p>...</p> */
			{
				strcat(z, "<p>");
				bParagraphOpen = TRUE;
			} else if (bEnv1stPara[iEnvLevel])
			{
				bEnv1stPara[iEnvLevel] = FALSE;
			} else
			{
				strcat(z, xhtml_br);
			}
		} else
		{
			if (inside_env)
			{
				if (bEnv1stPara[iEnvLevel])
				{
					bEnv1stPara[iEnvLevel] = FALSE;
				} else
				{
					strcat(z, xhtml_br);
				}
			}
		}
		break;

	case TOIPF:
		if (!inside_env)
			strcat(z, ":p.");
		break;

	case TOLDS:
		if (inside_quote)
			outln("<quote>");
		break;

	case TOLYX:
		if (iEnvLevel == 0)
		{
			outln("\\layout Standard");
			outln("");
		} else
		{
			if (inside_center)
			{
				outln("\\layout Standard");
				outln("\\align center");
			}
			if (inside_right)
				outln("\\align right");
			if (!tokens_contain_item && !inside_center)
				outln("\\newline");
		}
		break;

	case TOKPS:
		if (inside_env)
		{
			if (bEnv1stPara[iEnvLevel])
				bEnv1stPara[iEnvLevel] = FALSE;
			else
				outln(" newline");
		}
		out("(");
		break;

	default:
		to_check_quote_indent(&umbruch);
		break;
	}


	if (format_protect_commands)
	{
		strcpy(sIndent, z);
		if (insert_speccmd(sIndent, sIndent, sIndent))
			strcpy(z, sIndent);
	}

	if (desttype == TORTF)
	{
		if (iEnvLevel == 0)
		{
			out(rtf_plain);
			voutf("%s\\fs%d ", rtf_norm, iDocPropfontSize);
		}
	}


	/* --- now COMPOSE the paragraph content --- */

	while (i < token_counter)
	{
		use_token = TRUE;

		switch (desttype)
		{
		case TOPCH:
			c_pch_styles(token[i]);
			break;
		}

		if (token[i][1] == META_C && token[i][2] != QUOTE_C)
		{
			/* vorzeitiger Zeilenumbruch? */
			if (strcmp(token[i], "(!nl)") == 0)
			{
				newline = TRUE;
				just_linefeed = TRUE;
				use_token = FALSE;

				switch (desttype)
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
					replace_all(token[i], ")", KPSPC_S);
					replace_all(token[i], "(", KPSPO_S);
					break;

				case TONRO:
					strcpy(token[i], ".br\n");
					break;

				case TOIPF:
					strcpy(token[i], ".br\n");
					break;

				case TOINF:
					token[i][0] = EOS;
					if (!inside_center && !inside_right && !inside_left)
						strcat(z, "@*");
					break;

				case TORTF:
					if (iEnvLevel > 0)
					{
						switch (iEnvType[iEnvLevel])
						{
						case ENV_ITEM:
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
					} else
					{
						strcpy(token[i], "\\par ");
					}
					break;

				case TOWIN:
				case TOWH4:
				case TOAQV:
					strcpy(token[i], "\\line ");
					insert_speccmd(token[i], token[i], token[i]);
					break;

				case TOHAH:
				case TOHTM:
				case TOMHH:
					strcpy(token[i], xhtml_br);
					break;

				case TOLDS:
				case TOHPH:
					strcpy(token[i], "<newline>");
					break;

				default:
					token[i][0] = EOS;
					break;
				}
			}
		}


		switch (desttype)
		{
		case TOKPS:
			replace_all(token[i], "[", "\\[");
			replace_all(token[i], "]", "\\]");
			replace_all(token[i], "(", "\\(");
			replace_all(token[i], ")", "\\)");
			qreplace_all(token[i], KPSPC_S, KPSPC_S_LEN, ")", 1);
			qreplace_all(token[i], KPSPO_S, KPSPO_S_LEN, "(", 1);
			break;
		}

		if (use_token)
		{
			len_zeile = toklen(z);
			len_token = toklen(token[i]);

			if ((len_zeile + len_token) <= umbruch)
			{
				/* Das naechste Token hat noch Platz in der Zeile */
				if (token[i][0] != EOS)
				{
					strcat(z, token[i]);
					if (i == 0 && use_justification)
						strcat(z, INDENT_S);
					else
						strcat(z, " ");

					/* Capture first blank in string for a better appearance */
					if (inside_env && desttype == TOKPS)
					{
						_BOOL replaced_blank;

						do
						{
							replaced_blank = qreplace_once(z, "( ", 2, "(", 1);
						} while (replaced_blank);
					}
					len_zeile += len_token + 1;
				}
				newline = FALSE;
			} else
			{
				/* Die Zeile wird zu lang, also zur Ausgabe vorbereiten */
				newline = TRUE;

				switch (desttype)
				{
				case TOASC:
				case TODRC:
				case TOMAN:
				case TOSTG:
				case TOAMG:
				case TOPCH:
					/* Schauen, ob das "ueberhaengende" Wort in den Trennvorschlaegen steckt */
					replace_hyphens(token[i]);
					str2silben(token[i]);
					if (silben_counter >= 0)
					{
						silb = 0;		/* Zaehler der naechsten Silbe */

						/* len_zeile= toklen(z);: unveraendert */
						len_silbe = toklen(silbe[silb]);

						while (silb <= silben_counter && (len_zeile + len_silbe + 1) <= umbruch)
						{
							strcat(z, silbe[silb]);
							len_zeile += len_silbe;
							silb++;
							len_silbe = toklen(silbe[silb]);
						}

						if (silb > 0)
						{
							/* An die Zeile wurden Silben angehaengt */
							/* In ihr befinden sich u.U. noch DIVIS_C */
							/* Daher das letzte DIVIS_C in "-" umwandeln, */
							/* anderen entfernen */
							sl = strlen(z);

							if (z[sl - 1] == DIVIS_C)
							{
								z[sl - 1] = '-';
								/* Deutsches c!-k in k-k wandeln */
								if (z[sl - 2] == 'c' && silbe[silb][0] == 'k' && destlang == TOGER)
									z[sl - 2] = 'k';
							}
							delete_all_divis(z);

							/* Nun noch die restlichen Silben in das */
							/* naechste Token uebertragen */
							token[i][0] = EOS;
							for (j = silb; j <= silben_counter; j++)
								um_strcat(token[i], silbe[j], MAX_TOKEN_LEN + 1, "token_output[14]");
							delete_all_divis(token[i]);
						}
					}
					break;
				}
			}
		}


		if (newline)
		{
			/* we have to wrap this line */
			check_styles(z);
			replace_udo_quotes(z);
			delete_all_divis(z);

			/* Zeilen zentrieren? */
			if (inside_center)
			{
				switch (desttype)
				{
				case TOASC:
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
			{
				switch (desttype)
				{
				case TOASC:
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

			switch (desttype)
			{
			case TOTEX:
				replace_hyphens(z);
				indent2space(z);
				if (strncmp(z, "\\\\[", 3) == 0)
					qreplace_once(z, "[", 1, "{\\symbol{91}}", 13);
				auto_references(z, FALSE, "", 0, 0);
				break;

			case TOPDL:
				indent2space(z);
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
				/* Einen kleinen Mangel der Umgebungen TAB+SPACE beseitigen */
				qreplace_all(z, "\\tab  ", 6, "\\tab ", 5);
				auto_references(z, FALSE, "", 0, 0);
				break;

			case TOPCH:
				auto_references(z, FALSE, "", 0, 0);
				break;

			case TOHAH:
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

			case TOSTG:
				/*
				 * for ST-GUIDE, we usually let the help compiler
				 * generate the automatic references. However, when
				 * checking, we have to do that ourselfes so we notice
				 * the referenced labels.
				 */
				if (bCheckMisc)
					auto_references(z, FALSE, "", 0, 0);
				replace_1at_by_2at(z);
				break;

			default:
				break;
			}

			/* Kurze Zeilen bemaengeln, wenn sloppy nicht gesetzt ist */
			if ((inside_fussy) && (z[0] != EOS) && (i + 1 < token_counter) && (!just_linefeed))
			{
				switch (desttype)
				{
				case TOASC:
				case TODRC:
				case TOMAN:
				case TOSTG:
				case TOAMG:
				case TOPCH:
#if 0
					/* z wurde, ausser bei der Zentrierung */
					/* nicht veraendert. len_zeile hat also */
					/* noch den richtigen Wert. */
					len_zeile = toklen(z);
#endif
					if (use_justification && !inside_left)
					{
						if (len_zeile < umbruch - 9)
							warning_short_line(len_zeile, token[i]);
					} else
					{
						if (len_zeile < umbruch - 6)
							warning_short_line(len_zeile, token[i]);
					}
					break;
				}
			}

			if (use_justification)
			{
				if (i < token_counter && !just_linefeed && !inside_center && !inside_right && !inside_left)
				{
					switch (desttype)
					{
					case TOASC:
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

			/* remove last space, added by concatenating the tokens */
			switch (desttype)
			{
			case TORTF:
			case TOWIN:
			case TOWH4:
			case TOAQV:
			case TOLYX:
				break;
			default:
				del_right_spaces(z);
				break;
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
				if (strlen(z) > 0)
					strcat(z, " ");
				break;
			case TOLYX:
				indent2space(z);
				break;
			}


			if (format_uses_output_buffer && use_output_buffer)
				insert_nl_token_buffer();

			/* Fuer STG wieder ein Leerzeichen anhaengen, damit HypC */
			/* daran erkennen kann, dass der Absatz noch nicht zuende ist */
			/* Das Leerzeichen muss oben entfernt werden, da sonst der */
			/* Blocksatz weiter oben nicht richtig erzeugt wird! */
			if (desttype == TOSTG && !just_linefeed)
				strcat(z, " ");

			if (!no_effects && desttype == TOASC)
			{
				/* Offene Effekte am Zeilenende beenden */
				/* und unten in der naechsten Zeile oeffnen */
				check_styles_asc_last_line(z);
			}


			/* Endlich kann die Zeile ausgegeben werden */
			outln(z);

#if 0									/* WTF */
			/* strange hack to recognize begin of description item content */
			if (desttype == TOKPS)
				if (strstr(z, "offDesc writeBeforeLeft Boff newline "))
					out("(");
#endif

			/* Schonmal die naechste Zeile vorbereiten. */
			z[0] = EOS;
			len_zeile = 0;

			switch (desttype)
			{
			case TORTF:
			case TOWIN:
			case TOWH4:
			case TOAQV:
				to_check_rtf_quote_indent(z);
				break;
			default:
				strcat_indent(z);
				break;
			}

			if (format_protect_commands)
			{
				strcpy(sIndent, z);
				if (insert_speccmd(sIndent, sIndent, sIndent))
					strcpy(z, sIndent);
			}

			if (!no_effects)
			{
				switch (desttype)
				{
				case TODRC:
					check_styles_drc_next_line();
					break;
				case TOASC:
					check_styles_asc_next_line();
					break;
				}
			}

			strcat(z, token[i]);

			if (!just_linefeed)
				strcat(z, " ");
			else
				just_linefeed = FALSE;
		}

		i++;
	}


	/* --- output the (maybe last of multiple) line output --- */

	if (z[0] != EOS)
	{
		check_styles(z);
		replace_udo_quotes(z);
		delete_all_divis(z);

		if (inside_center)
		{
			switch (desttype)
			{
			case TOASC:
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
		{
			switch (desttype)
			{
			case TOASC:
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

		switch (desttype)
		{
		case TOTEX:
			replace_hyphens(z);
			indent2space(z);
			if (strncmp(z, "\\\\[", 3) == 0)
				qreplace_once(z, "[", 1, "{\\symbol{91}}", 13);
			auto_references(z, FALSE, "", 0, 0);
			break;
		case TOPDL:
			indent2space(z);
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
			/* Einen kleinen Mangel der Umgebungen TAB+SPACE beseitigen */
			qreplace_all(z, "\\tab  ", 6, "\\tab ", 5);
			auto_references(z, FALSE, "", 0, 0);
			break;
		case TOPCH:
			auto_references(z, FALSE, "", 0, 0);
			break;
		case TOHAH:
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
		case TOSTG:
			/*
			 * for ST-GUIDE, we usually let the help compiler
			 * generate the automatic references. However, when
			 * checking, we have to do that ourselfes so we notice
			 * the referenced labels.
			 */
			if (bCheckMisc)
				auto_references(z, FALSE, "", 0, 0);
			replace_1at_by_2at(z);
			break;
		default:
			break;
		}

		if (use_justification)
			indent2space(z);

		replace_placeholders(z);
		replace_speccmds(z);
		c_internal_styles(z);

		replace_udo_tilde(z);
		replace_udo_nbsp(z);

		switch (desttype)				/* remove last space, added by concatenating the tokens */
		{
		case TORTF:
		case TOWIN:
		case TOWH4:
		case TOAQV:
		case TOLYX:
			break;
		default:
			del_right_spaces(z);
			break;
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
		case TOLYX:
			indent2space(z);
			break;
		}

		if (format_uses_output_buffer && use_output_buffer)
			insert_nl_token_buffer();

		outln(z);
	}

	check_verb_style();


	/* --- treat END of paragraph --- */

	switch (desttype)
	{
	case TOWIN:
	case TOWH4:
	case TOAQV:
		if (inside_compressed)
			outln(rtf_parpard);
		else if (with_para)
			outln("\\par\\pard\\par");
		break;

	case TORTF:
		if (inside_compressed)
			outln(rtf_parpard);
		else
			outln("\\par\\pard\\par");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (!inside_compressed)
		{
			if (inside_center || inside_right)
			{
				outln("</div>");
			} else if (inside_env)
			{
				out(xhtml_br);
				outln("&nbsp;");
			} else
			{
				if (bParagraphOpen)
					outln("</p>");
				bParagraphOpen = FALSE;
			}
		}
		break;

	case TONRO:
		if (!inside_env && !inside_compressed)
			outln("");
		break;

	case TOLDS:
		if (!inside_compressed)
		{
			if (inside_quote)
				outln("</quote>");
			else
				outln("");
		}
		break;

	case TOINF:
		if (!inside_compressed)
		{
			if (inside_center)
				outln("@center");
			outln("");
		}
		break;

	case TOSRC:
	case TOSRP:
		outln(sSrcRemOff);
		break;

	case TOIPF:
		if (!inside_compressed)
			outln("");
		break;

	case TOHPH:
		if (!inside_compressed)
			outln("");
		break;

	case TOKPS:
		if (!inside_compressed)
			outln("newline");
		break;

	case TOTEX:
	case TOPDL:
		outln("");
		break;

	case TOSTG:
		if (!inside_compressed && with_para)
			outln("");
		break;

	default:
		if (!inside_compressed)
			outln("");
		break;
	}

	token_reset();

	if (reset_internals)
	{
		reset_placeholders();
		reset_refs();
	}
#if 1
	reset_speccmds();
#endif
}






/*******************************************************************************
*
*  tokenize():
*     convert lines to tokens (using str2tok()) and do commands
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void tokenize(char *s)
{
	_BOOL newtoken = FALSE;
	_BOOL reset_token = FALSE;
	_BOOL found = FALSE;
	register int i, j;

	if (s[0] == EOS)
		return;

	/* Bei einem neuen Kommando erst den Token-Buffer ausgeben, */
	/* bevor das neue Kommando bearbeitet wird. */
	if (s[0] == META_C && s[1] >= 'a' && s[1] <= 'z')
	{
		token_output(FALSE, strcmp(s, "!end_node") != 0);
		newtoken = TRUE;
	}

	str2tok(s);

	if (!newtoken)
		return;

	i = 0;
	while (i < token_counter && !found)
	{
		if (token[i][0] == META_C && token[i][1] != QUOTE_C)
		{
			/* Sequentielle Suche */
			for (j = 0; j < (int) ArraySize(udoCmdSeq); j++)
			{
				if (strcmp(token[i], udoCmdSeq[j].magic) == 0 ||
					(udoCmdSeq[j].macut[0] != EOS && strcmp(token[i], udoCmdSeq[j].macut) == 0))
				{
					switch (udoCmdSeq[j].pos)
					{
					case CMD_ALWAYS:
						udoCmdSeq[j].proc();
						break;
					case CMD_ONLY_PREAMBLE:
						if (!bInsideDocument)
							udoCmdSeq[j].proc();
						else
							cmd_outside_preamble();
						break;
					case CMD_ONLY_MAINPART:
						if (bInsideDocument)
							udoCmdSeq[j].proc();
						else
							cmd_inside_preamble();
						break;
					}
					reset_token = udoCmdSeq[j].reset;
					found = TRUE;
					break;
				}
			}
		}

		i++;
	}

	i = 0;
	while (!found && i < token_counter)
	{
		for (j = 0; j < (int) MAXSWITCH; j++)
		{
			if (token[i][0] == META_C && token[i][1] != QUOTE_C)
			{
				if (strcmp(token[i], udoswitch[j].magic) == 0)
				{
					cmd_outside_preamble();
					found = TRUE;
					reset_token = TRUE;
					break;
				}
			}
		}

		i++;
	}

	i = 0;
	while (!found && i < token_counter)
	{
		if (token[i][0] == META_C && token[i][1] != QUOTE_C)
		{
			error_message(_("unknown command: %s"), token[i]);
			reset_token = TRUE;
			break;
		}

		i++;
	}

	if (reset_token)
	{
		for (i = 0; i < token_counter; i++)
			token[i][0] = EOS;
		token_counter = 0;
		reset_placeholders();
		reset_refs();
	}
}





/*******************************************************************************
*
*  change_sep_suffix():
*     change file separator and suffix
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void change_sep_suffix(char *full, const char *suff)
{
	fsplit(full, tmp_driv, tmp_path, tmp_name, tmp_suff);

	path_adjust_separator(tmp_path);

#ifdef __TOS__
	/* Laufwerksbuchstabe sollte wegen Freedom gross sein */
	/* Siehe E-Mail von Christian Huch @ BM */
	if (tmp_driv[0] != EOS)
	{
		tmp_driv[0] = toupper(tmp_driv[0]);
	}
#endif

	sprintf(full, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, suff);
}





/*******************************************************************************
*
*  hyplist_compare():
*     compare entries of hyphenation list
*
*  return:
*     comparison result
*
******************************************|************************************/

LOCAL int hyplist_compare(const HYPLIST *p, const HYPLIST *q)
{
	size_t l1, l2;

	l1 = strlen(p->data);
	l2 = strlen(q->data);
	if (l1 < l2 && my_strnicmp(p->data, q->data, l1) == 0)
		return 1;
	if (l1 > l2 && my_strnicmp(p->data, q->data, l2) == 0)
		return -1;
	return my_stricmp(p->data, q->data);
}





/*******************************************************************************
*
*  hyplist_merge():
*     merge hyphenation lists
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL HYPLIST *hyplist_merge(HYPLIST *p, HYPLIST *q)
{
	HYPLIST *r, head;

	for (r = &head; p && q;)
	{
		if (hyplist_compare(p, q) < 0)
		{
			r = r->next = p;
			p = p->next;
		} else
		{
			r = r->next = q;
			q = q->next;
		}
	}
	r->next = (p ? p : q);
	return head.next;
}





/*******************************************************************************
*
*  hyplist_sort():
*     sort hyphenation list
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL HYPLIST *hyplist_sort(HYPLIST *p)
{
	HYPLIST *q, *r;

	if (p)
	{
		q = p;
		for (r = q->next; r && (r = r->next) != NULL; r = r->next)
			q = q->next;
		r = q->next;
		q->next = NULL;
		if (r)
			p = hyplist_merge(hyplist_sort(r), hyplist_sort(p));
	}
	return p;
}





/*******************************************************************************
*
*  add_hyplist_item():
*     add entry to hyphenation list
*
*  return:
*      TRUE: success
*     FALSE: error
*
******************************************|************************************/

LOCAL _BOOL add_hyplist_item(const char *s)
{
	HYPLIST *n;

	n = (HYPLIST *) malloc(sizeof(HYPLIST));
	if (n != NULL)
	{
		strcpy(n->data, s);
		n->next = hyplist;
		hyplist = n;
		return TRUE;
	}

	return FALSE;
}





/*******************************************************************************
*
*  sort_hypfile():
*     sort hyphenation list
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void sort_hypfile(const char *name)
{
	FILE *file;
	char z[256];
	HYPLIST *ptr, *ptr_next;

	hyplist = NULL;

	if (name == NULL || *name == EOS)
		return;

	if (!bHypopened && !bHypfailed)
	{
		remove(name);
		return;
	}

	file = fopen(name, "r");

	if (file == NULL)
		return;

	show_status_info(_("Reading hyphen file..."));

	while (fgets(z, (int) ArraySize(z), file))
		add_hyplist_item(z);

	fclose(file);

	if (hyplist == NULL)
		return;

	show_status_info(_("Sorting hyphen file..."));

	hyplist = hyplist_sort(hyplist);

	show_status_info(_("Writing hyphen file..."));

	file = myFwopen(name, TOASC);

	if (file == NULL)
		return;

	ptr = hyplist;
	while (ptr != NULL)
	{
		if (ptr->next != NULL)
		{
			if (strcmp(ptr->data, ptr->next->data) != 0)
			{
				fprintf(file, "%s", ptr->data);
			}
		} else
		{
			fprintf(file, "%s", ptr->data);
		}
		ptr = ptr->next;
	}

	fclose(file);

	for (ptr = hyplist; ptr != NULL; ptr = ptr_next)
	{
		ptr_next = ptr->next;
		free(ptr);
	}
	hyplist = NULL;
}





/*******************************************************************************
*
*  build_search_file():
*     Dateinamen setzen, falls nicht vollstaendig
*
*  Notes:
*     Falls ein relativer Pfad angegeben wird, werden Laufwerk
*     und Pfad des Infiles verwendet.
*
*  Bug:
*     UDO kommt nicht mit "udo -o ! ../udo.u" klar.
*
*  return:
*     -
*
******************************************|************************************/

static void build_search_file(char *d, const char *relto, const char *suff)
{
	char tmp_path2[MYFILE_PATH_LEN + 1];
	MYFILE rel;

	fsplit(d, tmp_driv, tmp_path, tmp_name, tmp_suff);
	strcpy(rel.full, relto);
	fsplit(rel.full, rel.driv, rel.path, rel.name, rel.suff);

#ifndef __MACOS__
	if (((tmp_driv[0] == EOS) || (tmp_driv[1] != ':')) && ((tmp_path[0] != '\\') && (tmp_path[0] != '/')))
	{
		strcpy(tmp_driv, rel.driv);
		strcpy(tmp_path2, rel.path);
		strcat(tmp_path2, tmp_path);
		strcpy(tmp_path, tmp_path2);
	}
#else /* __MACOS__ */
	/* MO: nochmal leicht ueberarbeitet */
	/* Martin Osieka, 18.04.1996 */
	/* Kein Laufwerk? Dann Laufwerk von <infile> */
	if (tmp_driv[0] == EOS)
	{
		strcpy(tmp_driv, rel.driv);
	}
	/* Relativer Pfad? Dann Pfad von <infile> davor */
	if (rel.path[0])
	{
		if ((tmp_path[0] == ':') && strcmp(tmp_path, rel.path))
		{
			strcpy(tmp_path2, rel.path);
			strcat(tmp_path2, &tmp_path[1]);
			strcpy(tmp_path, tmp_path2);
		} else if (tmp_path[0] == EOS)
		{
			strcpy(tmp_path, rel.path);
		}
	}
#endif /* __MACOS__ */

#ifdef __TOS__
	/* Laufwerksbuchstabe sollte wegen Freedom gross sein */
	/* Siehe E-Mail von Christian Huch @ BM */
	if (tmp_driv[0] != EOS)
		tmp_driv[0] = toupper(tmp_driv[0]);
#endif

	if (tmp_suff[0] == EOS)
		strcpy(tmp_suff, suff);

	path_adjust_separator(tmp_path);

	sprintf(d, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
}





/*******************************************************************************
*
*  build_include_filename():
*     Dateinamen komplettieren, ausgehend vom aktuellen Verzeichnis
*
*  Notes:
*     Strategie bei Uebersetzung von C:\Foo\bar.u:
*
*     !include foo      ->   C:\Foo\foo.(suff)
*       (1)             nur Dateiname gegeben:
*                       Laufwerk und Pfad des Infiles
* 
*     !include \foo     ->   C:\foo.(suff)
*       (2)             absolutes Verzeichnis und Dateiname:
*                       Laufwerk des Infiles
*
*     !include D:\foo   ->   D:\foo.(suff)
*       (3)             absolutes Laufwerk und Verzeichnis:
*                       komplett uebernehmen
*
*     !include Bar\foo  ->   C:\Foo\Bar\foo.(suff)
*       (4)             relatives Verzeichnis:
*                       Laufwerk und Pfad des Infiles
*  
*  return:
*     -
*
******************************************|************************************/

GLOBAL void build_include_filename(char *d, const char *relto, const char *suff)
{
	build_search_file(d, relto, suff);
}





/*******************************************************************************
*
*  build_image_filename():
*     Dateinamen komplettieren, ausgehend vom aktuellen Verzeichnis
*
*  Notes:
*     Strategie bei Uebersetzung von C:\Foo\bar.u nach C:\Foo\html\bar.html:
*
*     !image foo      ->   C:\Foo\foo.gif
*       (1)           nur Dateiname gegeben:
*                     Laufwerk und Pfad des Outfiles
* 
*     !image \foo     ->   C:\foo.gif
*       (2)           absolutes Verzeichnis und Dateiname:
*                     Laufwerk des Infiles
*
*     !image D:\foo   ->   D:\foo.gif
*       (3)           absolutes Laufwerk und Verzeichnis:
*                     komplett uebernehmen
*
*     !image Bar\foo  ->   C:\Foo\Bar\foo.gif
*       (4)           relatives Verzeichnis:
*                     Laufwerk und Pfad des Outfiles
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void build_image_filename(char *d, const char *suff)
{
	build_search_file(d, infile.full, suff);
}





/*******************************************************************************
*
*  output_preamble():
*     output preamble for some formats
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_preamble(void)
{
	char s[512];

	if (no_preamble)
		return;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		if (bTex2e)
		{
			strcpy(s, "\\documentclass[10pt]");
			if (use_style_book)
			{
				strcat(s, "{scrbook}");
			} else
			{
				strcat(s, "{scrartcl}");
			}
			outln(s);
			s[0] = EOS;
			strcat(s, get_lang()->tex_stylename);
			if (!no_index && bCalledIndex)
				strcat(s, ",makeidx");
			if (!no_images && (iTexVersion == TEX_TETEX || iTexVersion == TEX_MIKTEX))
			{
				strcat(s, ",graphicx");
			}
			if (s[0] != EOS)
				voutlnf("\\usepackage{%s}", s);

			outln("\\usepackage{eurosym}");
			outln("\\usepackage{times}");

			/* UTF-8 output? */
			if (iEncodingTarget == CODE_UTF8)
				outln("\\usepackage[utf8]{inputenc}");

			if (desttype == TOPDL)
			{
				outln("\\pdfoutput=1\\relax");
				if (bDocMediumCompression)
					outln("\\pdfcompresslevel=1");
				if (bDocHighCompression)
					outln("\\pdfcompresslevel=9");

				outln("\\pdfpagewidth=\\paperwidth");
				outln("\\pdfpageheight=\\paperheight");
			}
		} else
		{
			strcpy(s, "\\documentstyle[11pt,");
			strcat(s, get_lang()->tex_stylename);
			if (!no_index && bCalledIndex)
				strcat(s, ",makeidx");
			strcat(s, "]");
			if (use_style_book)
				strcat(s, "{book}");
			else
				strcat(s, "{article}");
			outln(s);
		}

		if (!no_index && bCalledIndex)
		{
			outln("\\makeindex");
		}

		if (use_style_book)
		{
			voutlnf("\\setcounter{tocdepth}{%d}", toc_maxdepth - TOC_NODE1 + 1);
			voutlnf("\\setcounter{secnumdepth}{%d}", toc_maxdepth - TOC_NODE1 + 1);
		} else
		{
			voutlnf("\\setcounter{tocdepth}{%d}", toc_maxdepth - TOC_NODE1 + 2);
			voutlnf("\\setcounter{secnumdepth}{%d}", toc_maxdepth - TOC_NODE1 + 2);
		}

		outln("\\newcounter{subsubparagraph}[subparagraph]");
		outln("\\newcounter{subsubsubparagraph}[subsubparagraph]");
		outln("\\newcounter{subsubsubsubparagraph}[subsubsubparagraph]");
		outln("\\newcounter{subsubsubsubsubparagraph}[subsubsubsubparagraph]");
		outln("\\makeatletter");
		outln("\\renewcommand\\thesubsubparagraph{\\thesubparagraph.\\@arabic\\c@subsubparagraph}");
		outln("\\renewcommand\\thesubsubsubparagraph{\\thesubsubparagraph.\\@arabic\\c@subsubsubparagraph}");
		outln("\\renewcommand\\thesubsubsubsubparagraph{\\thesubsubsubparagraph.\\@arabic\\c@subsubsubsubparagraph}");
		outln
			("\\renewcommand\\thesubsubsubsubsubparagraph{\\thesubsubsubsubparagraph.\\@arabic\\c@subsubsubsubsubparagraph}");
		outln("\\newcommand\\subsubparagraph{\\@startsection{subsubparagraph}{6}{\\parindent}%");
		outln("   {3.25ex \\@plus1ex \\@minus .2ex}%");
		outln("   {-1em}%");
		outln("   {\\normalfont\\normalsize\\bfseries}}");
		outln("\\newcommand\\subsubsubparagraph{\\@startsection{subsubsubparagraph}{7}{\\parindent}%");
		outln("   {3.25ex \\@plus1ex \\@minus .2ex}%");
		outln("   {-1em}%");
		outln("   {\\normalfont\\normalsize\\bfseries}}");
		outln("\\newcommand\\subsubsubsubparagraph{\\@startsection{subsubsubsubparagraph}{8}{\\parindent}%");
		outln("   {3.25ex \\@plus1ex \\@minus .2ex}%");
		outln("   {-1em}%");
		outln("   {\\normalfont\\normalsize\\bfseries}}");
		outln("\\newcommand\\subsubsubsubsubparagraph{\\@startsection{subsubsubsubsubparagraph}{9}{\\parindent}%");
		outln("   {3.25ex \\@plus1ex \\@minus .2ex}%");
		outln("   {-1em}%");
		outln("   {\\normalfont\\normalsize\\bfseries}}");
		outln("\\newcommand*\\l@subsubparagraph{\\@dottedtocline{6}{14em}{7em}}");
		outln("\\newcommand*\\l@subsubsubparagraph{\\@dottedtocline{7}{16em}{8em}}");
		outln("\\newcommand*\\l@subsubsubsubparagraph{\\@dottedtocline{8}{18em}{9em}}");
		outln("\\newcommand*\\l@subsubsubsubsubparagraph{\\@dottedtocline{9}{20em}{10em}}");
		outln("\\makeatother");
		break;

	case TOLYX:
		outln("#LyX 1.3 did not create this file");
		voutlnf("# This file was created by UDO %s", UDO_VERSION_STRING);
		outln("# UDO (C) 1995-2001 by Dirk Hagedorn (info@dirk-hagedorn.de)");
		outln("# UDO (C) 2001-2014 by The UDO Community (www.udo-open-source.org)");
		outln("\\lyxformat 221");
		outln("\\begin_preamble");
		voutlnf("\\textclass %s", (use_style_book) ? "book" : "article");
		outln("\\usepackage{eurosym}");
		if (!no_index && bCalledIndex)
		{
			outln("\\usepackage{makeidx}");
			outln("\\makeindex");
		}
		outln("\\end_preamble");
		outln("\\inputencoding auto");
		outln("\\fontscheme default");
		outln("\\graphics dvips");
		outln("\\papersize default");
		outln("\\paperfontsize 11");
		outln("\\spacing single");
		voutlnf("\\secnumdepth %d", toc_maxdepth - TOC_NODE1 + 1);
		voutlnf("\\tocdepth %d", toc_maxdepth - TOC_NODE1 + 1);
		outln("\\paragraph_separation indent");
		voutlnf("\\language %s", get_lang()->lyx_langname);

		switch (destlang)
		{
		case TOENG:
			outln("\\quotes_language english");
			break;
		case TOFRA:
			outln("\\quotes_language french");
			break;
		default:
			outln("\\quotes_language german");
			break;
		}
		outln("\\quotes_times 2");
		outln("\\paperorientation portrait");
		outln("\\papercolumns 0");
		outln("\\papersides 1");
		outln("\\paperpagestyle headings");
		outln("\\use_geometry 0");
		outln("\\use_amsmath 1");
		/*
		   outln("\\use_natbib 0");
		   outln("\\use_numerical_citations 0");
		 */
		break;

	case TODRC:
		if (titleprogram[0] != EOS)
		{
			voutlnf("%%%%Title 0, %s", titleprogram);
		} else
		{
			voutlnf("%%%%Title 0, %s", get_lang()->unknown);
		}

		outln("%%Status_line 3");
		outln("%%*");
		outln("%% 3, 0, 7, Status line");

		if (titdat.drc_statusline != NULL)
		{
			outln(titdat.drc_statusline);
		} else if (titdat.author != NULL)
		{
			voutlnf("Copyright (c) by %s", titdat.author);
		} else
		{
			voutlnf("Made with UDO %s", UDO_VERSION_STRING_OS);
		}

		if (uses_maketitle)
		{
			voutlnf("%%%%Opening_screen 1");
		}
		outln("%%Default_flags 7");
		break;

	case TOSTG:
		outln("@if VERSION >= 6");
		voutlnf("@os \"%s\"", UDO_OS);
		voutlnf("@charset \"%s\"", chr_codepage_charset_name(CODE_TOS));
		voutlnf("@inputenc \"%s\"", chr_codepage_charset_name(iEncodingTarget));
		voutlnf("@lang \"%s\"", get_lang()->html_lang);
		outln("@endif");
		break;
	}
}






/*******************************************************************************
*
*  clear_file_stack():
*     clear stack of !include files
*
******************************************|************************************/

LOCAL void clear_file_stack(void)
{
	int i;

	iFilesOpened = 0;
	for (i = 0; i < MAXFILECOUNTER; i++)
	{
		uiFiles[i].loc.line = 0;
		uiFiles[i].loc.id = 0;
		uiFiles[i].file = NULL;
	}
}


/*******************************************************************************
*
*  push_file_stack():
*     push current file onto stack of includes
*
******************************************|************************************/

LOCAL _BOOL push_file_stack(const char *filename, MYTEXTFILE *file)
{
	if (iFilesOpened >= MAXFILECOUNTER)
	{
		error_message(_("too many files opened"));
		return FALSE;
	}
	uiFiles[iFilesOpened].loc.line = 0;
	uiFiles[iFilesOpened].loc.id = file_listadd(filename);
	uiFiles[iFilesOpened].file = file;
	iFilesOpened++;

	strcpy(sCurrFileName, filename);
	uiCurrFileLine = 0;
	return TRUE;
}


/*******************************************************************************
*
*  pop_file_stack():
*     pop file from stack of includes and make it current
*
******************************************|************************************/

LOCAL _BOOL pop_file_stack(void)
{
	if (iFilesOpened > 0)
	{
		iFilesOpened--;
		myTextClose(uiFiles[iFilesOpened].file);
		if (iFilesOpened == 0)
		{
			sCurrFileName[0] = EOS;
			uiCurrFileLine = 0;
		} else
		{
			if (iFilesOpened > 0)
				strcpy(sCurrFileName, file_lookup(uiFiles[iFilesOpened - 1].loc.id));
			uiCurrFileLine = uiFiles[iFilesOpened].loc.line;
		}
		return TRUE;
	}
	return FALSE;
}


/*******************************************************************************
*
*  clear_if_stack():
*     clear stack of !if environments
*
*  Notes:
*     Has to be called before pass1() and pass2(), best done in udo().
*
*     Abfragen auf Befehle fuer format- und/oder sprachabhaengige Umgebungen. 
*     Trifft die Funktion auf einen dieser Befehle, so werden Flags, die in 
*     pass1() und pass2() beachtet werden, gesetzt, und die Zeile geleert, 
*     so dass sie nicht weiter bearbeitet wird.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void clear_if_stack(void)
{
	register int i;

	for (i = 0; i < MAX_IF_STACK; i++)
	{
		if_stack[i].kind = IF_NONE;
		if_stack[i].ignore = FALSE;
		if_stack[i].loc.line = 0;
		if_stack[i].loc.id = 0;
	}
	counter_if_stack = 0;
}





/*******************************************************************************
*
*  push_if_stack():
*     push environment on !if stack
*
*  Notes:
*     Used for "!ifdest", "!ifndest", "!iflang", and "!ifnlang".
*     
*     If <ignore> == TRUE, all lines until "!else" or "!endif" will not be 
*     evaluated in pass1() and pass2().
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void push_if_stack(int kind, _BOOL ignore)
{
	if (counter_if_stack < MAX_IF_STACK)
	{
		counter_if_stack++;

		if_stack[counter_if_stack].kind = kind;
		if_stack[counter_if_stack].ignore = ignore;
		if_stack[counter_if_stack].loc = uiFiles[iFilesOpened - 1].loc;
	} else
	{
		error_message(_("too many !if"));
	}
}





/*******************************************************************************
*
*  pop_if_stack():
*     pops last !if environment from stack when !endif has been found
*
*  return:
*     -
*
******************************************|************************************/

LOCAL _BOOL pop_if_stack(void)
{
	if (counter_if_stack > 0)
	{
		if_stack[counter_if_stack].kind = IF_NONE;
		if_stack[counter_if_stack].ignore = FALSE;
		counter_if_stack--;
		return TRUE;
	}
	return FALSE;
}





/*******************************************************************************
*
*  toggle_if_stack():
*     toggles !if environment on stack when !else has been found
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void toggle_if_stack(void)
{
	if (counter_if_stack > 0)
	{
		if_stack[counter_if_stack].ignore = !(if_stack[counter_if_stack].ignore);
	} else
	{
		error_end_without_begin("!else", "!if...");
	}
}





/*******************************************************************************
*
*  is_if_stack_ignore():
*     checks if ignore flag has been set in *one* of the !if environments
*
*  return:
*     FALSE: no ignore flag has been found
*      TRUE: ignore flag has been found
*
******************************************|************************************/

LOCAL _BOOL is_if_stack_ignore(void)
{
	register int i;

	if (counter_if_stack > 0)
	{
		for (i = 1; i <= counter_if_stack; i++)
		{
			if (if_stack[i].ignore)
				return TRUE;
		}
		/* all environments are valid */
		return FALSE;
	}

	/* no active environment at all */
	return FALSE;
}





/*******************************************************************************
*
*  pass_check_free_line():
*     clears string to prevent it from further evaluation
*
*  Notes:
*     In 2nd pass, the last paragraph will be output.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void pass_check_free_line(char *zeile, int pnr)
{
	if (pnr == PASS2 && token_counter > 0)
	{
		token_output(TRUE, TRUE);
	}

	zeile[0] = EOS;
}



/*******************************************************************************
*
*  pass_check_if():
*     checks line on !if... commands and proceeds line
*
*  Notes:
*     Here the ignore flag will be set.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL _BOOL pass_check_if(char *zeile, int pnr)
{
	char cmd[128];
	char *p;
	const char *pcmd;
	_BOOL ignore = FALSE;

	strncpy(cmd, zeile, ArraySize(cmd));
	cmd[ArraySize(cmd) - 1] = EOS;
	pcmd = cmd;
	while (*pcmd == ' ' || *pcmd == '\t')
		pcmd++;
	if (pcmd[0] != META_C)
		return FALSE;
	p = strchr(pcmd, ' ');
	if (p == NULL)
		p = strchr(pcmd, '\t');
	if (p != NULL)
		*p++ = EOS;
	
	if (strcmp(pcmd, "!ifdest") == 0)
	{
		if (p == NULL)
			error_missing_parameter(pcmd);
		else
			ignore = str_for_desttype(p, TRUE) <= 0;
		push_if_stack(IF_DEST, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, "!ifndest") == 0)
	{
		if (p == NULL)
			error_missing_parameter(pcmd);
		else
			ignore = str_for_desttype(p, TRUE) > 0;
		push_if_stack(IF_DEST, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, "!iflang") == 0)
	{
		if (p == NULL)
			error_missing_parameter(pcmd);
		else
			ignore = !str_for_destlang(p, TRUE);
		push_if_stack(IF_LANG, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, "!ifnlang") == 0)
	{
		if (p == NULL)
			error_missing_parameter(pcmd);
		else
			ignore = str_for_destlang(p, TRUE);
		push_if_stack(IF_LANG, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, "!ifos") == 0)
	{
		if (p == NULL)
			error_missing_parameter(pcmd);
		else
			ignore = !str_for_os(p, TRUE);
		push_if_stack(IF_OS, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, "!ifnos") == 0)
	{
		if (p == NULL)
			error_missing_parameter(pcmd);
		else
			ignore = str_for_os(p, TRUE);
		push_if_stack(IF_OS, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, "!ifset") == 0)
	{
		if (p == NULL)
			error_missing_parameter(pcmd);
		else
			ignore = !udosymbol_set(p);
		push_if_stack(IF_SET, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, "!ifnset") == 0)
	{
		if (p == NULL)
			error_missing_parameter(pcmd);
		else
			ignore = udosymbol_set(p);
		push_if_stack(IF_SET, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, "!if") == 0)
	{
		if (p == NULL)
		{
			error_missing_parameter(pcmd);
		} else
		{
			_BOOL matches_dest = str_for_desttype(p, FALSE) > 0;
			_BOOL matches_lang = str_for_destlang(p, FALSE);
			_BOOL matches_os = str_for_os(p, FALSE);
			_BOOL matches_symb = udosymbol_set(p);
			ignore = !(matches_dest | matches_lang | matches_symb | matches_os);
		}
		push_if_stack(IF_GENERAL, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, CMD_BEGIN_IGNORE) == 0)
	{
		push_if_stack(IF_GENERAL, TRUE);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}
#if 0
	if (strcmp(pcmd, "!elif") == 0)
	{
		pop_if_stack();
		pflag[pnr].ignore_line = is_if_stack_ignore();
		if (p == NULL)
		{
			error_missing_parameter(pcmd);
		} else
		{
			matches_dest = str_for_desttype(p, FALSE) > 0;
			matches_lang = str_for_destlang(p, FALSE);
			matches_os = str_for_os(p, FALSE);
			matches_symb = udosymbol_set(p);
			ignore = !(matches_dest | matches_lang | matches_symb | matches_os);
		}
		push_if_stack(IF_GENERAL, ignore);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}
#endif

	if (strcmp(pcmd, "!else") == 0)
	{
		toggle_if_stack();
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, "!endif") == 0)
	{
		if (!pop_if_stack())
			error_end_without_begin("!endif", "!if...");
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	if (strcmp(pcmd, CMD_END_IGNORE) == 0)
	{
		if (!pop_if_stack())
			error_end_without_begin(CMD_END_IGNORE, CMD_BEGIN_IGNORE);
		pflag[pnr].ignore_line = is_if_stack_ignore();
		pass_check_free_line(zeile, pnr);
		return TRUE;
	}

	return FALSE;
}





/*******************************************************************************
*
*  get_switch_par():
*     get switches
*
*  Notes:
*     Moegliche Syntax:
*    !no_* [<formate>]
*    !use_* [<formate>] !<parameter> <wert>
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void get_switch_par(const UDOSWITCH *us)
{
	register int i;
	int val;

	if (us->parcmd[0] == EOS)
		return;

	for (i = 1; i < token_counter; i++)
	{
		if (strcmp(token[i], us->parcmd) == 0)
		{
			switch (us->partype)
			{
			case 'b':					/* boolean */
				*(_BOOL *) (us->parval) = TRUE;
				return;

			case 'i':					/* int */
				if (i + 1 < token_counter)
				{
					val = atoi(token[i + 1]);
					if (us->parval != NULL)
					{
						*(int *) (us->parval) = val;
					}
				}
				return;
			}
		}
	}
}





/*******************************************************************************
*
*  pass1_check_preamble_commands():
*     ??? (description missing)
*
*  return:
*      TRUE: ???
*     FALSE: ???
*
******************************************|************************************/

LOCAL _BOOL pass1_check_preamble_commands(void)
{
	register int i;
	int c;
	int d, d2;

	/* Allgemeine globale Schalter (im Vorspann erlaubt) */

	for (i = 0; i < (int) MAXSWITCH; i++)
	{
		if (strcmp(token[0], udoswitch[i].magic) == 0)
		{
			if (is_for_desttype(udoswitch[i].flag, udoswitch[i].magic, TRUE))
			{
				get_switch_par(&(udoswitch[i]));
			}
			return TRUE;
		}
	}

	/* Allgemeine lokale Schalter */
	for (d = TOC_NODE1; d < TOC_MAXDEPTH; d++)
	{
		char subs[3 * TOC_MAXDEPTH + 1 + 80];
		
		strcpy(subs, "!");
		for (d2 = TOC_NODE1; d2 < d; d2++)
			strcat(subs, "sub");
		strcat(subs, "toc_offset");
		if (strcmp(token[0], subs) == 0)
		{
			if (token[1][0] == EOS)
			{
				toc_offset[d] = 0;
			} else
			{
				toc_offset[d] = atoi(token[1]);
			}
			return TRUE;
		}
	}

	if (strcmp(token[0], "!table_counter") == 0)
	{
		if (token[1][0] == EOS)
		{
			set_table_counter(0);
		} else
		{
			set_table_counter(atoi(token[1]));
		}
		return TRUE;
	}

	if (strcmp(token[0], "!image_counter") == 0)
	{
		if (token[1][0] == EOS)
		{
			set_image_counter(0);
		} else
		{
			set_image_counter(atoi(token[1]));
		}
		return TRUE;
	}

	if (strcmp(token[0], "!language") == 0)
	{
		i = langid_from_name(token[1]);
		if (i >= 0)
		{
			set_destlang(i);
			lang_changed = TRUE;
			return TRUE;
		}
		error_message(_("language %s not supported"), token[1]);
		return TRUE;
	}

	if (strcmp(token[0], "!parwidth") == 0)
	{
		zDocParwidth = strtol(token[1], NULL, 0);
		/* FIXME: should check for insane values here */
		return TRUE;
	}

	if (strcmp(token[0], "!sort_hyphen_file") == 0)
	{
		bDocSortHyphenFile = TRUE;
		return TRUE;
	}

	if (strcmp(token[0], "!image_alignment") == 0)
	{
		set_image_alignment();
		return TRUE;
	}

	if (strcmp(token[0], "!table_alignment") == 0)
	{
		set_table_alignment();
		return TRUE;
	}

	if (strcmp(token[0], "!win_make_button") == 0)
	{
		if (iNumWinButtons < MAX_WIN_BUTTONS)
		{
			strcpy(sDocWinButtonName[iNumWinButtons], token[1]);
			strcpy(sDocWinButtonText[iNumWinButtons], token[2]);
			iNumWinButtons++;
		} else
		{
			error_message(_("more than %d buttons defined"), MAX_WIN_BUTTONS);
		}
		return TRUE;
	}

	/* spezielle Schalter */

	switch (desttype)
	{
	case TOTEX:
		if (strcmp(token[0], "!tex_lindner") == 0)
		{
			iTexVersion = TEX_LINDNER;
			bTex2e = FALSE;
			return TRUE;
		}

		if (strcmp(token[0], "!tex_strunk") == 0)
		{
			iTexVersion = TEX_STRUNK;
			bTex2e = FALSE;
			return TRUE;
		}

		if (strcmp(token[0], "!tex_emtex") == 0)
		{
			iTexVersion = TEX_EMTEX;
			bTex2e = FALSE;
			return TRUE;
		}

		if (strcmp(token[0], "!tex_miktex") == 0)
		{
			iTexVersion = TEX_MIKTEX;
			bTex2e = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!tex_tetex") == 0)
		{
			iTexVersion = TEX_TETEX;
			bTex2e = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!tex_2e") == 0)
		{
			bTex2e = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!tex_209") == 0)
		{
			bTex2e = FALSE;
			return TRUE;
		}
		break;

	case TOPDL:
		if (strcmp(token[0], "!pdf_high_compression") == 0)
		{
			bDocHighCompression = TRUE;
			bDocMediumCompression = FALSE;
			return TRUE;
		}

		if (strcmp(token[0], "!pdf_medium_compression") == 0)
		{
			bDocMediumCompression = TRUE;
			bDocHighCompression = FALSE;
			return TRUE;
		}
		break;

	case TOMAN:
		if (strcmp(token[0], "!man_lpp") == 0)
		{
			iManPageLength = atoi(token[1]);
			if (iManPageLength < 0)
				iManPageLength = 0;
			return TRUE;
		}

		if (strcmp(token[0], "!man_type") == 0)
		{
			tokcpy2(sDocManType, ArraySize(sDocManType));
			return TRUE;
		}
		break;

	case TONRO:
		if (strcmp(token[0], "!nroff_type") == 0)
		{
			tokcpy2(sDocNroffType, ArraySize(sDocNroffType));
			return TRUE;
		}
		break;

	case TODRC:
		if (strcmp(token[0], "!drc_flags") == 0)
			c_drc_flags();
		break;

	case TOWIN:
	case TOAQV:
		if (strcmp(token[0], "!win_backcolor") == 0 || strcmp(token[0], "!win_background") == 0)
		{
			if ((c = get_color()) < 0)
				c = BC_WHITE;
			set_win_backcolor(&sDocBackColor, c);
			return TRUE;
		}

		if (strcmp(token[0], "!win_textcolor") == 0)
		{
			if ((c = get_color()) < 0)
				c = BC_BLACK;
			set_win_textcolor(&sDocTextColor, c);
			return TRUE;
		}

		if (strcmp(token[0], "!win_linkcolor") == 0)
		{
			if ((c = get_color()) >= 0)
				set_win_textcolor(&sDocLinkColor, c);
			return TRUE;
		}

		if (strcmp(token[0], "!win_inline_bitmaps") == 0)
		{
			bDocInlineBitmaps = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!win_high_compression") == 0)
		{
			bDocHighCompression = TRUE;
			bDocMediumCompression = FALSE;
			return TRUE;
		}

		if (strcmp(token[0], "!win_medium_compression") == 0)
		{
			bDocMediumCompression = TRUE;
			bDocHighCompression = FALSE;
			return TRUE;
		}

		if (strcmp(token[0], "!win_propfont") == 0)
		{
			tokcpy2(sDocPropfont, ArraySize(sDocPropfont));
			return TRUE;
		}

		if (strcmp(token[0], "!win_monofont") == 0)
		{
			tokcpy2(sDocMonofont, ArraySize(sDocMonofont));
			return TRUE;
		}

		if (strcmp(token[0], "!win_propfont_size") == 0)
		{
			tokcpy2(sDocPropfontSize, ArraySize(sDocPropfontSize));
			return TRUE;
		}

		if (strcmp(token[0], "!win_monofont_size") == 0)
		{
			tokcpy2(sDocMonofontSize, ArraySize(sDocMonofontSize));
			return TRUE;
		}

		if (strcmp(token[0], "!win_old_keywords") == 0)
		{
			bDocWinOldKeywords = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!win_prefix_helpids") == 0)
		{
			tokcpy2(sDocWinPrefixID, ArraySize(sDocWinPrefixID));
			return TRUE;
		}
		break;

	case TOWH4:
		if (strcmp(token[0], "!wh4_backcolor") == 0 || strcmp(token[0], "!wh4_background") == 0)
		{
			if ((c = get_color()) < 0)
				c = BC_WHITE;
			set_win_backcolor(&sDocBackColor, c);
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_textcolor") == 0)
		{
			if ((c = get_color()) < 0)
				c = BC_BLACK;
			set_win_textcolor(&sDocTextColor, c);
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_linkcolor") == 0)
		{
			if ((c = get_color()) >= 0)
				set_win_textcolor(&sDocLinkColor, c);
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_inline_bitmaps") == 0)
		{
			bDocInlineBitmaps = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_high_compression") == 0)
		{
			bDocHighCompression = TRUE;
			bDocMediumCompression = FALSE;
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_medium_compression") == 0)
		{
			bDocHighCompression = FALSE;
			bDocMediumCompression = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_propfont") == 0)
		{
			tokcpy2(sDocPropfont, ArraySize(sDocPropfont));
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_monofont") == 0)
		{
			tokcpy2(sDocMonofont, ArraySize(sDocMonofont));
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_propfont_size") == 0)
		{
			tokcpy2(sDocPropfontSize, ArraySize(sDocPropfontSize));
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_monofont_size") == 0)
		{
			tokcpy2(sDocMonofontSize, ArraySize(sDocMonofontSize));
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_old_keywords") == 0)
		{
			bDocWinOldKeywords = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!wh4_prefix_helpids") == 0)
		{
			tokcpy2(sDocWinPrefixID, ArraySize(sDocWinPrefixID));
			return TRUE;
		}
		break;

	case TORTF:
		if (strcmp(token[0], "!rtf_no_tables") == 0)
		{
			bDocNoTables = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!rtf_monofont") == 0)
		{
			tokcpy2(sDocMonofont, ArraySize(sDocMonofont));
			return TRUE;
		}

		if (strcmp(token[0], "!rtf_propfont") == 0)
		{
			tokcpy2(sDocPropfont, ArraySize(sDocPropfont));
			return TRUE;
		}

		if (strcmp(token[0], "!rtf_monofont_size") == 0)
		{
			tokcpy2(sDocMonofontSize, ArraySize(sDocMonofontSize));
			return TRUE;
		}

		if (strcmp(token[0], "!rtf_propfont_size") == 0)
		{
			tokcpy2(sDocPropfontSize, ArraySize(sDocPropfontSize));
			return TRUE;
		}
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (strncmp(token[0], "!html", 5) != 0)
			return FALSE;

		/* check !html_merge_nodes, html_merge_subnodes etc. */
		for (d = TOC_NODE1; d < TOC_MAXDEPTH; d++)
		{
			char s[256];
			
			strcpy(s, "!html_merge_");
			for (d2 = TOC_NODE1; d2 < d; d2++)
				strcat(s, "sub");
			strcat(s, "nodes");
			if (strcmp(token[0], s) == 0)
			{
				for (d2 = d; d2 < TOC_MAXDEPTH; d2++)
					html_merge_node[d2] = TRUE;
				return TRUE;
			}
		}

		if (strcmp(token[0], "!html_no_xlist") == 0)
		{
			html_no_xlist = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!html_ignore_8bit") == 0)
		{
			html_ignore_8bit = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!html_navigation") == 0)
		{
			if (set_html_navigation())
				return TRUE;
		}

		if (strcmp(token[0], "!html_modern_layout") == 0)
		{
			html_modern_layout = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_layout") == 0)
		{
			set_html_frames_layout();
			return TRUE;
		}

		if (strcmp(token[0], "!html_backpage") == 0)
		{
			tokcpy2(sDocHtmlBackpage, ArraySize(sDocHtmlBackpage));
			return TRUE;
		}

		if (strcmp(token[0], "!html_indexname") == 0)
		{
			tokcpy2(sDocHtmlIndexudo, ArraySize(sDocHtmlIndexudo));
			return TRUE;
		}

		if (strcmp(token[0], "!html_backcolor") == 0)
		{
			set_html_color(HTML_COLOR_BACK);
			return TRUE;
		}

		if (strcmp(token[0], "!html_textcolor") == 0)
		{
			set_html_color(HTML_COLOR_TEXT);
			return TRUE;
		}

		if (strcmp(token[0], "!html_linkcolor") == 0)
		{
			set_html_color(HTML_COLOR_LINK);
			return TRUE;
		}

		if (strcmp(token[0], "!html_alinkcolor") == 0)
		{
			set_html_color(HTML_COLOR_ALINK);
			return TRUE;
		}

		if (strcmp(token[0], "!html_vlinkcolor") == 0)
		{
			set_html_color(HTML_COLOR_VLINK);
			return TRUE;
		}

		if (strcmp(token[0], "!html_backimage") == 0)
		{
			set_html_backimage();
			return TRUE;
		}

		if (strcmp(token[0], "!html_style_name") == 0)
		{
			set_html_style();
			return TRUE;
		}

		if (strcmp(token[0], "!html_script_name") == 0)
		{
			set_html_script();
			return TRUE;
		}

		if (strcmp(token[0], "!html_favicon_name") == 0)
		{
			set_html_favicon();
			return TRUE;
		}

		if (strcmp(token[0], "!html_modern_width") == 0)
		{
			set_html_modern_width();
			return TRUE;
		}

		if (strcmp(token[0], "!html_modern_alignment") == 0)
		{
			set_html_modern_alignment();
			return TRUE;
		}

		if (strcmp(token[0], "!html_modern_backcolor") == 0)
		{
			set_html_special_color(&html_modern_backcolor);
			return TRUE;
		}

		if (strcmp(token[0], "!html_modern_backimage") == 0)
		{
			set_html_modern_backimage();
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_width") == 0)
		{
			set_html_frames_width();
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_alignment") == 0)
		{
			set_html_frames_alignment();
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_position") == 0)
		{
			set_html_frames_position();
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_backcolor") == 0)
		{
			set_html_special_color(&html_frames_backcolor);
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_textcolor") == 0)
		{
			set_html_special_color(&html_frames_textcolor);
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_linkcolor") == 0)
		{
			set_html_special_color(&html_frames_linkcolor);
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_alinkcolor") == 0)
		{
			set_html_special_color(&html_frames_alinkcolor);
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_vlinkcolor") == 0)
		{
			set_html_special_color(&html_frames_vlinkcolor);
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_backimage") == 0)
		{
			set_html_frames_backimage();
			return TRUE;
		}

		if (strcmp(token[0], "!html_button_alignment") == 0)
		{
			set_html_button_alignment();
			return TRUE;
		}

		if (strcmp(token[0], "!html_quotes") == 0)
		{
			set_html_quotes();
			return TRUE;
		}

		if (strcmp(token[0], "!html_transparent_buttons") == 0)
		{
			html_transparent_buttons = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!html_use_folders") == 0)
		{
			html_use_folders = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!html_propfont_name") == 0)
		{
			tokcpy2(sDocHtmlPropfontName, ArraySize(sDocHtmlPropfontName));
			return TRUE;
		}

		if (strcmp(token[0], "!html_propfont_size") == 0)
		{
			tokcpy2(sDocHtmlPropfontSize, ArraySize(sDocHtmlPropfontSize));
			return TRUE;
		}

		if (strcmp(token[0], "!html_monofont_name") == 0)
		{
			tokcpy2(sDocHtmlMonofontName, ArraySize(sDocHtmlMonofontName));
			return TRUE;
		}

		if (strcmp(token[0], "!html_monofont_size") == 0)
		{
			tokcpy2(sDocHtmlMonofontSize, ArraySize(sDocHtmlMonofontSize));
			return TRUE;
		}

		if (strcmp(token[0], "!html_name_prefix") == 0)
		{
			set_html_filename_prefix();
			return TRUE;
		}

		if (strcmp(token[0], "!html_switch_language") == 0)
		{
			set_html_switch_language();
			return TRUE;
		}

		if (strcmp(token[0], "!html_use_hyphenation") == 0)
		{
			html_use_hyphenation = TRUE;
			return TRUE;
		}

		if (strcmp(token[0], "!html_doctype") == 0)
		{
			c_set_html_doctype();
			return TRUE;
		}

		if (strcmp(token[0], "!html_header_date") == 0)
		{
			set_html_header_date();
			return TRUE;
		}

		if (strcmp(token[0], "!html_header_links") == 0)
		{
			set_html_header_links();
			return TRUE;
		}

		if (strcmp(token[0], "!html_counter_command") == 0)
		{
			set_html_counter_command();
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_toc_title") == 0)
		{
			set_html_frames_toc_title();
			return TRUE;
		}

		if (strcmp(token[0], "!html_frames_con_title") == 0)
		{
			set_html_frames_con_title();
			return TRUE;
		}
		break;
	}

	return FALSE;
}





/*******************************************************************************
*
*  pass1_check_main_commands():
*     ??? (description missing)
*
*  return:
*      TRUE: ???
*     FALSE: ???
*
******************************************|************************************/

LOCAL _BOOL pass1_check_main_commands(void)
{
	/* spezielle Schalter (nur im Hauptteil erlaubt) */

	switch (desttype)
	{
	case TOMHH:
		if (strcmp(token[0], "!html_name") == 0)
		{
			set_html_filename();
			return TRUE;
		}
		break;

	case TOHAH:
	case TOHTM:
		if (strncmp(token[0], "!html", 5) != 0)
			return FALSE;

		if (strcmp(token[0], "!html_name") == 0)
		{
			set_html_filename();
			return TRUE;
		}
		if (strcmp(token[0], "!html_dirname") == 0)
		{
			set_html_dirname();
			return TRUE;
		}
		if (strcmp(token[0], "!html_keywords") == 0)
		{
			set_html_keywords();
			return TRUE;
		}
		if (strcmp(token[0], "!html_description") == 0)
		{
			set_html_description();
			return TRUE;
		}
		if (strcmp(token[0], "!html_robots") == 0)
		{
			set_html_robots();
			return TRUE;
		}
		if (strcmp(token[0], "!html_bgsound") == 0)
		{
			set_html_bgsound();
			return TRUE;
		}
		if (strcmp(token[0], "!html_counter_command") == 0)
		{
			set_html_counter_command();
			return TRUE;
		}
		break;
	}

	return FALSE;
}





/*******************************************************************************
*
*  pass1_check_everywhere_commands():
*     ??? (description missing)
*
*  return:
*      TRUE: ???
*     FALSE: ???
*
******************************************|************************************/

LOCAL _BOOL pass1_check_everywhere_commands(void)
{
	/* spezielle Schalter (ueberall erlaubt) */

	switch (desttype)
	{
	case TOHAH:
	case TOHTM:
		if (strcmp(token[0], "!html_img_suffix") == 0)
		{
			c_html_img_suffix();
			return TRUE;
		}
		if (strcmp(token[0], "!html_backcolor") == 0)
		{
			set_html_color(HTML_COLOR_BACK);
			return TRUE;
		}
		if (strcmp(token[0], "!html_textcolor") == 0)
		{
			set_html_color(HTML_COLOR_TEXT);
			return TRUE;
		}
		if (strcmp(token[0], "!html_linkcolor") == 0)
		{
			set_html_color(HTML_COLOR_LINK);
			return TRUE;
		}
		if (strcmp(token[0], "!html_alinkcolor") == 0)
		{
			set_html_color(HTML_COLOR_ALINK);
			return TRUE;
		}
		if (strcmp(token[0], "!html_vlinkcolor") == 0)
		{
			set_html_color(HTML_COLOR_VLINK);
			return TRUE;
		}
		if (strcmp(token[0], "!html_backimage") == 0)
		{
			set_html_backimage();
			return TRUE;
		}
		if (strcmp(token[0], "!html_style_name") == 0)
		{
			set_html_style();
			return TRUE;
		}
		if (strcmp(token[0], "!html_script_name") == 0)
		{
			set_html_script();
			return TRUE;
		}
		break;

	case TOMHH:
		if (strcmp(token[0], "!hh_img_suffix") == 0)
		{
			c_html_img_suffix();
			return TRUE;
		}
		if (strcmp(token[0], "!hh_backcolor") == 0)
		{
			set_html_color(HTML_COLOR_BACK);
			return TRUE;
		}
		if (strcmp(token[0], "!hh_textcolor") == 0)
		{
			set_html_color(HTML_COLOR_TEXT);
			return TRUE;
		}
		if (strcmp(token[0], "!hh_linkcolor") == 0)
		{
			set_html_color(HTML_COLOR_LINK);
			return TRUE;
		}
		if (strcmp(token[0], "!hh_alinkcolor") == 0)
		{
			set_html_color(HTML_COLOR_ALINK);
			return TRUE;
		}
		if (strcmp(token[0], "!hh_vlinkcolor") == 0)
		{
			set_html_color(HTML_COLOR_VLINK);
			return TRUE;
		}
		if (strcmp(token[0], "!hh_backimage") == 0)
		{
			set_html_backimage();
			return TRUE;
		}
		if (strcmp(token[0], "!html_style_name") == 0)
		{
			set_html_style();
			return TRUE;
		}
		if (strcmp(token[0], "!html_script_name") == 0)
		{
			set_html_script();
			return TRUE;
		}
		break;

	case TODRC:
		if (strcmp(token[0], "!drc_bcolor") == 0)
		{
			c_drc_bcolor();
			return TRUE;
		}
		if (strcmp(token[0], "!drc_icolor") == 0)
		{
			c_drc_icolor();
			return TRUE;
		}
		if (strcmp(token[0], "!drc_ucolor") == 0)
		{
			c_drc_ucolor();
			return TRUE;
		}
		break;
	}

	return FALSE;
}





/*******************************************************************************
*
*  pass1_check_environments():
*     check special environments in pass 1
*
*  return:
*     -
*
******************************************|************************************/

LOCAL _BOOL pass1_check_environments(char *zeile)
{
	char cmd[128];
	char *p;
	const char *pcmd;

	strncpy(cmd, zeile, ArraySize(cmd));
	cmd[ArraySize(cmd) - 1] = EOS;
	pcmd = cmd;
	while (*pcmd == ' ' || *pcmd == '\t')
		pcmd++;
	if (pcmd[0] != META_C)
		return FALSE;
	p = strchr(pcmd, ' ');
	if (p == NULL)
		p = strchr(pcmd, '\t');
	if (p != NULL)
		*p = EOS;

	/* Verbatim-Umgebung */
	if (pflag[PASS1].env == ENV_NONE || pflag[PASS1].env == ENV_VERBATIM)
	{
		if (strcmp(pcmd, CMD_BEGIN_VERBATIM) == 0)
		{
			pflag[PASS1].env = ENV_VERBATIM;
			pflag[PASS1].loc = uiFiles[iFilesOpened - 1].loc;
			zeile[0] = EOS;
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_VERBATIM) == 0)
		{
			pflag[PASS1].env = ENV_NONE;
			zeile[0] = EOS;
			return TRUE;
		}
	}

	/* Sourcecode-Umgebung */
	if (pflag[PASS1].env == ENV_NONE || pflag[PASS1].env == ENV_SOURCECODE)
	{
		if (strcmp(pcmd, CMD_BEGIN_SOURCECODE) == 0)
		{
			pflag[PASS1].env = ENV_SOURCECODE;
			pflag[PASS1].loc = uiFiles[iFilesOpened - 1].loc;
			zeile[0] = EOS;
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_SOURCECODE) == 0)
		{
			pflag[PASS1].env = ENV_NONE;
			zeile[0] = EOS;
			return TRUE;
		}
	}

	/* Raw-Umgebung */
	if (pflag[PASS1].env == ENV_NONE || pflag[PASS1].env == ENV_RAW)
	{
		if (strcmp(pcmd, CMD_BEGIN_RAW) == 0)
		{
			pflag[PASS1].env = ENV_RAW;
			pflag[PASS1].loc = uiFiles[iFilesOpened - 1].loc;
			zeile[0] = EOS;
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_RAW) == 0)
		{
			pflag[PASS1].env = ENV_NONE;
			zeile[0] = EOS;
			return TRUE;
		}
	}

	/* Table-Umgebung */
	if (pflag[PASS1].env == ENV_NONE || pflag[PASS1].env == ENV_TABLE)
	{
		if (strcmp(pcmd, CMD_BEGIN_TABLE) == 0)
		{
			if (pflag[PASS1].env == ENV_TABLE)
			{
				/* unnecessary check here, error message will be issued during pass2() */
			}
			pflag[PASS1].env = ENV_TABLE;
			pflag[PASS1].loc = uiFiles[iFilesOpened - 1].loc;
			zeile[0] = EOS;
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_TABLE) == 0)
		{
			pflag[PASS1].env = ENV_NONE;
			zeile[0] = EOS;
			return TRUE;
		}
	}

	/* Comment-Umgebung */
	if (pflag[PASS1].env == ENV_NONE || pflag[PASS1].env == ENV_COMMENT)
	{
		if (strcmp(pcmd, CMD_BEGIN_COMMENT) == 0)
		{
			pflag[PASS1].env = ENV_COMMENT;
			pflag[PASS1].loc = uiFiles[iFilesOpened - 1].loc;
			zeile[0] = EOS;
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_COMMENT) == 0)
		{
			pflag[PASS1].env = ENV_NONE;
			zeile[0] = EOS;
			return TRUE;
		}
	}

	/* Linedraw-Umgebung */
	if (pflag[PASS1].env == ENV_NONE || pflag[PASS1].env == ENV_LINEDRAW)
	{
		if (strcmp(pcmd, CMD_BEGIN_LINEDRAW) == 0)
		{
			pflag[PASS1].env = ENV_LINEDRAW;
			pflag[PASS1].loc = uiFiles[iFilesOpened - 1].loc;
			zeile[0] = EOS;
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_LINEDRAW) == 0)
		{
			pflag[PASS1].env = ENV_NONE;
			zeile[0] = EOS;
			return TRUE;
		}
	}

	/* Preformatted-Umgebung */
	if (pflag[PASS1].env == ENV_NONE || pflag[PASS1].env == ENV_PREFORMATTED)
	{
		if (strcmp(pcmd, CMD_BEGIN_PREFORMATTED) == 0)
		{
			pflag[PASS1].env = ENV_PREFORMATTED;
			pflag[PASS1].loc = uiFiles[iFilesOpened - 1].loc;
			pflag[PASS1].doinside = strstr(zeile, "!inside") != NULL;
			zeile[0] = EOS;
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_PREFORMATTED) == 0)
		{
			pflag[PASS1].env = ENV_NONE;
			pflag[PASS1].doinside = FALSE;
			zeile[0] = EOS;
			return TRUE;
		}
	}

	return FALSE;
}





/*******************************************************************************
*
*  pass1():
*     Zeilen einlesen und Inhaltsverzeichnis ermitteln (1st Pass)
*
*  Return:
*     ???
*
******************************************|************************************/

#define USE_PASS1_OUTPUT   0

LOCAL _BOOL pass1(const char *datei)
{
	MYTEXTFILE *file;
	char zeile[LINELEN];
	char tmp_datei[MYFILE_FULL_LEN];
	char tmp[512];
	size_t len;
	int i;
	int start_if_stack;
	FILE_ID id;

	strcpy(tmp_datei, datei);

	file = myTextOpen(tmp_datei);

	if (file == NULL && iFilesOpened > 0)
	{
		build_include_filename(tmp_datei, file_lookup(uiFiles[iFilesOpened - 1].loc.id), ".ui");
		file = myTextOpen(tmp_datei);
	}

	if (file == NULL)
	{
		strcpy(tmp_datei, datei);
		build_include_filename(tmp_datei, infile.full, ".ui");
		file = myTextOpen(tmp_datei);
	}

	if (file == NULL)
	{
		bErrorDetected = TRUE;
		return FALSE;
	}

	/* Rekursive Includes testen */
	id = file_listadd(tmp_datei);
	for (i = 0; i < iFilesOpened; i++)
	{
		if (uiFiles[i].loc.id == id)
		{
			fatal_message(_("Recursive !include detected"));
			bFatalErrorDetected = TRUE;
			myTextClose(file);
			return FALSE;
		}
	}

	start_if_stack = counter_if_stack;

	if (push_file_stack(tmp_datei, file) == FALSE)
	{
		myTextClose(file);
		return FALSE;
	}

	if (bVerbose)
	{
		show_status_file_1(lPass1Lines, tmp_datei);
	}

	if (!in_about_udo)
	{
		if (bUseTreefile)
		{
			if (bTreeopened)
			{
				for (i = 0; i < (iFilesOpened - 1); i++)
					fprintf(fTreefile, "|----");
				fprintf(fTreefile, "%s\n", tmp_datei);
			}
		}

		save_upr_entry_infile(tmp_datei, iFilesOpened);
	}

	while (!bBreakHappened && !bBreakInside && !bFatalErrorDetected && myTextGetline(zeile, LINELEN, file))
	{
		_BOOL ignore_comment_or_empty;

		/* Here we need to add possible splitted line numbers */
		uiFiles[iFilesOpened - 1].loc.line += 1 + uiMultiLines;
		uiCurrFileLine = uiFiles[iFilesOpened - 1].loc.line;
		lPass1Lines++;

		if (break_action())
		{
			pop_file_stack();
			return FALSE;
		}

		len = strlen(zeile);
		while ((len > 0) && (((_UBYTE) zeile[len - 1]) <= 32))
		{
			zeile[len - 1] = EOS;
			len--;
		}

		/* dont recode commments */
		ignore_comment_or_empty = zeile[0] == '#' || zeile[0] == EOS;
		if (!ignore_comment_or_empty && pflag[PASS1].ignore_line == 0 && pflag[PASS1].env != ENV_RAW)
		{
			recode(zeile, iEncodingSource, iEncodingTarget);
		}

		if (!ignore_comment_or_empty && pflag[PASS1].env == ENV_NONE)
		{
			pass_check_if(zeile, PASS1);
		}

		if (!ignore_comment_or_empty && pflag[PASS1].ignore_line == 0)
		{
			ignore_comment_or_empty |= pass1_check_environments(zeile);
		}

		if (zeile[0] != EOS)
		{
			if (pflag[PASS1].ignore_line == 0 && (pflag[PASS1].env == ENV_NONE || pflag[PASS1].env == ENV_TABLE))
			{
				del_whitespaces(zeile);

				/* fix for bug #77: */
				/* replace macros right here because they might contain */
				/*  PASS1 commands, like !node, etc. */
#if 0
				/*
				   commented out for several reasons:
				   - using macros to define section commands just is not supported.
				     when replacing macros here, someone will surely
				     try to do something like !macro MYMACRO !macro ...
				   - auto_quote_chars has not been called yet, so the macro
				     would get unconverted parameters, which would lead
				     to different node names in pass1() and pass2()
				   - replace_macros() is called below again, which would make it
				     impossible to quote macro names
				   - this would be similar trying to do a "#define x #include y"
				     in C, which is not allowed either (guess why)
				   - conclusion: the bug is not that is does not work in pass1(),
				     but that is DOES work in pass2()
				   [tho]
				 */
				if (bInsideDocument && zeile[0] != META_C)
					replace_macros(zeile);
#endif

				if (zeile[0] == META_C && zeile[1] != QUOTE_C)
				{
					/* Erster Parameter von !macro und !define darf nicht gequotet werden! */
					if (strncmp(zeile, CMD_DEFINE, 7) == 0)
					{
						token_reset();
						str2tok(zeile);
						add_define();
						zeile[0] = EOS;
					}
					if (strncmp(zeile, CMD_UNDEF, 6) == 0)
					{
						token_reset();
						str2tok(zeile);
						del_define();
						zeile[0] = EOS;
					}

					if (!bInsideDocument)
					{
						if (strncmp(zeile, CMD_MACRO, 6) == 0)
						{
							token_reset();
							str2tok(zeile);
							add_macro();
							zeile[0] = EOS;
						}
					}

					if (strncmp(zeile, CMD_SET, 4) == 0)
					{
						token_reset();
						str2tok(zeile);
						zeile[0] = EOS;
						tokcpy2(zeile, LINELEN);
						add_udosymbol(zeile);
						zeile[0] = EOS;
					}

					if (strncmp(zeile, CMD_UNSET, 6) == 0)
					{
						token_reset();
						str2tok(zeile);
						zeile[0] = EOS;
						tokcpy2(zeile, LINELEN);
						del_udosymbol(zeile);
						zeile[0] = EOS;
					}

					/* <???> Problem/Bug: Falls man Makros wie !macro INC !include ... */
					/* verwendet, dann wird das nicht erkannt, da oben auf */
					/* zeile[0][0]==META_C getestet wird. */
					/* Ergebnis: !include wird dann nicht erkannt, die Prozentzahlen */
					/* stimmen im 2. Durchlauf nicht mehr. */

					if (zeile[0] != EOS)
					{
						/* Set node name for project file */
						strcpy(current_node_name_sys, zeile);

						auto_quote_chars(zeile, FALSE);
						replace_macros(zeile);
						replace_defines(zeile);

						c_divis(zeile);
						c_vars(zeile);
						c_tilde(zeile);
						c_styles(zeile);
						c_internal_index(zeile, FALSE);
					}

					token_reset();
					str2tok(zeile);

					if (bInsideDocument && token[0][0] != EOS)
					{
						/* Kommandos, die nur im Hauptteil erlaubt sind */
						if (strcmp(token[0], "!node") == 0 ||
							strcmp(token[0], "!n") == 0)
						{
							add_node_to_toc(TOC_NODE1, FALSE, FALSE);
						} else if (strcmp(token[0], "!node*") == 0 ||
							      strcmp(token[0], "!n*") == 0)
						{
							add_node_to_toc(TOC_NODE1, FALSE, TRUE);
						} else if (strcmp(token[0], "!subnode") == 0 ||
						           strcmp(token[0], "!sn") == 0)
						{
							add_node_to_toc(TOC_NODE2, FALSE, FALSE);
						} else if (strcmp(token[0], "!subnode*") == 0 ||
							       strcmp(token[0], "!sn*") == 0)
						{
							add_node_to_toc(TOC_NODE2, FALSE, TRUE);
						} else if (strcmp(token[0], "!subsubnode") == 0 ||
							       strcmp(token[0], "!ssn") == 0)
						{
							add_node_to_toc(TOC_NODE3, FALSE, FALSE);
						} else if (strcmp(token[0], "!subsubnode*") == 0 ||
							       strcmp(token[0], "!ssn*") == 0)
						{
							add_node_to_toc(TOC_NODE3, FALSE, TRUE);
						} else if (strcmp(token[0], "!subsubsubnode") == 0 ||
						           strcmp(token[0], "!sssn") == 0)
						{
							add_node_to_toc(TOC_NODE4, FALSE, FALSE);
						} else if (strcmp(token[0], "!subsubsubnode*") == 0 ||
							       strcmp(token[0], "!sssn*") == 0)
						{
							add_node_to_toc(TOC_NODE4, FALSE, TRUE);
						} else if (strcmp(token[0], "!subsubsubsubnode") == 0 ||
							       strcmp(token[0], "!ssssn") == 0)
						{
							add_node_to_toc(TOC_NODE5, FALSE, FALSE);
						} else if (strcmp(token[0], "!subsubsubsubnode*") == 0 ||
							       strcmp(token[0], "!ssssn*") == 0)
						{
							add_node_to_toc(TOC_NODE5, FALSE, TRUE);
						} else if (strcmp(token[0], "!subsubsubsubsubnode") == 0 ||
							       strcmp(token[0], "!sssssn") == 0)
						{
							add_node_to_toc(TOC_NODE6, FALSE, FALSE);
						} else if (strcmp(token[0], "!subsubsubsubsubnode*") == 0 ||
							       strcmp(token[0], "!sssssn*") == 0)
						{
							add_node_to_toc(TOC_NODE6, FALSE, TRUE);
						} else if (strcmp(token[0], "!subsubsubsubsubsubnode") == 0 ||
								   strcmp(token[0], "!ssssssn") == 0)
						{
							add_node_to_toc(TOC_NODE7, FALSE, FALSE);
						} else if (strcmp(token[0], "!subsubsubsubsubsubsubnode*") == 0 ||
								   strcmp(token[0], "!ssssssn*") == 0)
						{
							add_node_to_toc(TOC_NODE7, FALSE, TRUE);
						} else if (strcmp(token[0], "!subsubsubsubsubsubsubnode") == 0 ||
								   strcmp(token[0], "!sssssssn") == 0)
						{
							add_node_to_toc(TOC_NODE8, FALSE, FALSE);
						} else if (strcmp(token[0], "!subsubsubsubsubsubsubnode*") == 0 ||
								   strcmp(token[0], "!sssssssn*") == 0)
						{
							add_node_to_toc(TOC_NODE8, FALSE, TRUE);
						} else if (strcmp(token[0], "!subsubsubsubsubsubsubsubnode") == 0 ||
								   strcmp(token[0], "!ssssssssn") == 0)
						{
							add_node_to_toc(TOC_NODE9, FALSE, FALSE);
						} else if (strcmp(token[0], "!subsubsubsubsubsubsubsubnode*") == 0 ||
								   strcmp(token[0], "!ssssssssn*") == 0)
						{
							add_node_to_toc(TOC_NODE9, FALSE, TRUE);
						} else if (strcmp(token[0], "!pnode") == 0 ||
							       strcmp(token[0], "!p") == 0)
						{
							add_node_to_toc(TOC_NODE1, TRUE, FALSE);
						} else if (strcmp(token[0], "!pnode*") == 0 ||
							       strcmp(token[0], "!p*") == 0)
						{
							add_node_to_toc(TOC_NODE1, TRUE, TRUE);
						} else if (strcmp(token[0], "!psubnode") == 0 ||
							       strcmp(token[0], "!ps") == 0)
						{
							add_node_to_toc(TOC_NODE2, TRUE, FALSE);
						} else if (strcmp(token[0], "!psubnode*") == 0 ||
							       strcmp(token[0], "!ps*") == 0)
						{
							add_node_to_toc(TOC_NODE2, TRUE, TRUE);
						} else if (strcmp(token[0], "!psubsubnode") == 0 ||
							       strcmp(token[0], "!pss") == 0)
						{
							add_node_to_toc(TOC_NODE3, TRUE, FALSE);
						} else if (strcmp(token[0], "!psubsubnode*") == 0 ||
							       strcmp(token[0], "!pss*") == 0)
						{
							add_node_to_toc(TOC_NODE3, TRUE, TRUE);
						} else if (strcmp(token[0], "!psubsubsubnode") == 0 ||
							       strcmp(token[0], "!psss") == 0)
						{
							add_node_to_toc(TOC_NODE4, TRUE, FALSE);
						} else if (strcmp(token[0], "!psubsubsubnode*") == 0 ||
							       strcmp(token[0], "!psss*") == 0)
						{
							add_node_to_toc(TOC_NODE4, TRUE, TRUE);
						} else if (strcmp(token[0], "!psubsubsubsubnode") == 0 ||
							       strcmp(token[0], "!pssss") == 0)
						{
							add_node_to_toc(TOC_NODE5, TRUE, FALSE);
						} else if (strcmp(token[0], "!psubsubsubsubnode*") == 0 ||
							       strcmp(token[0], "!pssss*") == 0)
						{
							add_node_to_toc(TOC_NODE5, TRUE, TRUE);
						} else if (strcmp(token[0], "!psubsubsubsubsubnode") == 0 ||
							       strcmp(token[0], "!psssss") == 0)
						{
							add_node_to_toc(TOC_NODE6, TRUE, FALSE);
						} else if (strcmp(token[0], "!psubsubsubsubsubnode*") == 0 ||
							       strcmp(token[0], "!psssss*") == 0)
						{
							add_node_to_toc(TOC_NODE6, TRUE, TRUE);
						} else if (strcmp(token[0], "!psubsubsubsubsubsubnode") == 0 ||
								   strcmp(token[0], "!pssssss") == 0)
						{
							add_node_to_toc(TOC_NODE7, TRUE, FALSE);
						} else if (strcmp(token[0], "!psubsubsubsubsubsubnode*") == 0 ||
								   strcmp(token[0], "!pssssss*") == 0)
						{
							add_node_to_toc(TOC_NODE7, TRUE, TRUE);
						} else if (strcmp(token[0], "!psubsubsubsubsubsubsubnode") == 0 ||
								   strcmp(token[0], "!psssssss") == 0)
						{
							add_node_to_toc(TOC_NODE8, TRUE, FALSE);
						} else if (strcmp(token[0], "!psubsubsubsubsubsubsubnode*") == 0 ||
								   strcmp(token[0], "!psssssss*") == 0)
						{
							add_node_to_toc(TOC_NODE8, TRUE, TRUE);
						} else if (strcmp(token[0], "!psubsubsubsubsubsubsubsubnode") == 0 ||
								   strcmp(token[0], "!pssssssss") == 0)
						{
							add_node_to_toc(TOC_NODE9, TRUE, FALSE);
						} else if (strcmp(token[0], "!psubsubsubsubsubsubsubsubnode*") == 0 ||
								   strcmp(token[0], "!pssssssss*") == 0)
						{
							add_node_to_toc(TOC_NODE9, TRUE, TRUE);
						} else if (strcmp(token[0], "!begin_node") == 0 ||
							       strcmp(token[0], "!bn") == 0)
						{
							toc_begin_node(FALSE, FALSE);
						} else if (strcmp(token[0], "!begin_node*") == 0 ||
							       strcmp(token[0], "!bn*") == 0)
						{
							toc_begin_node(FALSE, TRUE);
						} else if (strcmp(token[0], "!begin_pnode") == 0 ||
							       strcmp(token[0], "!bp") == 0)
						{
							toc_begin_node(TRUE, FALSE);
						} else if (strcmp(token[0], "!begin_pnode*") == 0 ||
							       strcmp(token[0], "!bp*") == 0)
						{
							toc_begin_node(TRUE, TRUE);
						} else if (strcmp(token[0], "!end_node") == 0 ||
							       strcmp(token[0], "!en") == 0)
						{
							toc_end_node();
						} else if (strcmp(token[0], "!alias") == 0 ||
						           strcmp(token[0], "!a") == 0)
						{
							tokcpy2(tmp, ArraySize(tmp));
							add_alias(tmp, toc_inside_popup(), FALSE);
						} else if (strcmp(token[0], "!alias-") == 0 ||
							       strcmp(token[0], "!a-") == 0)
						{
							tokcpy2(tmp, ArraySize(tmp));
							add_alias(tmp, toc_inside_popup(), TRUE);
						} else if (strcmp(token[0], "!index") == 0 ||
							       strcmp(token[0], "!x") == 0)
						{
							bCalledIndex = TRUE;
						} else if (strcmp(token[0], "!mapping") == 0)
						{
							set_mapping();
						} else if (strcmp(token[0], "!win_helpid") == 0)
						{
							set_helpid();
						} else if (strcmp(token[0], "!wh4_helpid") == 0)
						{
							set_helpid();
						} else if (strcmp(token[0], "!jumpid") == 0)	/* Alter Kommandoname */
						{
							set_helpid();
						} else if (strcmp(token[0], "!udolink") == 0)
						{
							c_udolink();
						} else if (strcmp(token[0], "!toplink") == 0)
						{
							c_toplink();
						} else if (strcmp(token[0], "!win_set_button") == 0)
						{
							win_set_button();
						} else if (strcmp(token[0], "!html_img_suffix") == 0)
						{
							c_html_img_suffix();
						} else if (strcmp(token[0], "!chapterimage") == 0)
						{
							set_chapter_image();
						} else if (strcmp(token[0], "!chaptericon") == 0)
						{
							set_chapter_icon();
						} else if (strcmp(token[0], "!chaptericon_active") == 0)
						{
							set_chapter_icon_active();
						} else if (strcmp(token[0], "!chaptericon_text") == 0)
						{
							set_chapter_icon_text();
						} else if (strcmp(token[0], "!ignore_subtoc") == 0)
						{
							set_ignore_subtoc();
						} else if (strcmp(token[0], "!ignore_subsubtoc") == 0)
						{
							set_ignore_subtoc();
						} else if (strcmp(token[0], "!ignore_subsubsubtoc") == 0)
						{
							set_ignore_subtoc();
						} else if (strcmp(token[0], "!ignore_subsubsubsubtoc") == 0)
						{
							set_ignore_subtoc();
						} else if (strcmp(token[0], "!ignore_subsubsubsubsubtoc") == 0)
						{
							set_ignore_subtoc();
						} else if (strcmp(token[0], "!ignore_subsubsubsubsubsubtoc") == 0)
						{
							set_ignore_subtoc();
						} else if (strcmp(token[0], "!ignore_subsubsubsubsubsubsubtoc") == 0)
						{
							set_ignore_subtoc();
						} else if (strcmp(token[0], "!ignore_subsubsubsubsubsubsubsubtoc") == 0)
						{
							set_ignore_subtoc();
						} else if (strcmp(token[0], "!ignore_links") == 0)
						{
							set_ignore_links();
						} else if (strcmp(token[0], "!ignore_index") == 0)
						{
							set_ignore_index();
						} else if (strcmp(token[0], "!ignore_title") == 0)
						{
							set_ignore_title();
						} else if (strcmp(token[0], "!ignore_headline") == 0)
						{
							set_ignore_headline();
						} else if (strcmp(token[0], "!ignore_bottomline") == 0)
						{
							set_ignore_bottomline();
						} else if (strcmp(token[0], "!ignore_raw_header") == 0)
						{
							set_ignore_raw_header();
						} else if (strcmp(token[0], "!ignore_raw_footer") == 0)
						{
							set_ignore_raw_footer();
						} else if (strcmp(token[0], "!ignore_toptoc") == 0)
						{
							set_ignore_toptoc();
						} else if (strcmp(token[0], "!maketitle") == 0)
						{
							uses_maketitle = TRUE;
						} else if (strcmp(token[0], "!tableofcontents") == 0)
						{
							uses_tableofcontents = TRUE;
						} else if (strcmp(token[0], "!toc_title") == 0)
						{
							set_nodetitle(0);
						} else if (strcmp(token[0], "!node_title") == 0)
						{
							set_nodetitle(p1_toc_counter);
						} else if (strcmp(token[0], "!top_title") == 0)
						{
							set_toptitle();
						} else if (strcmp(token[0], "!begin_appendix") == 0)
						{
							pflag[PASS1].inside_apx = TRUE;
							toc_pass1_begin_appendix();
						} else if (strcmp(token[0], "!end_appendix") == 0)
						{
							/* pflag[PASS1].inside_apx = FALSE; */
						} else if (pass1_check_main_commands())
						{
							token[0][0] = EOS;
						} else if (pass1_check_everywhere_commands())
						{
							token[0][0] = EOS;
						}
					}


					/* Kommandos, die nur im Vorspann erlaubt sind */
					if (!bInsideDocument && token[0][0] != EOS)
					{
						if (strcmp(token[0], CMD_BEGIN_DOCUMENT) == 0)
						{
							bInsideDocument = TRUE;
						} else if (strcmp(token[0], "!hyphen") == 0)
						{
							add_hyphen();
						} else if (strcmp(token[0], "!docinfo") == 0)
						{
							if (set_docinfo())
								token[0][0] = EOS;
						} else if (strcmp(token[0], "!doclayout") == 0)
						{
							if (set_doclayout())
								token[0][0] = EOS;
						} else if (strcmp(token[0], "!show_variable") == 0)
						{
							if (set_show_variable())
								token[0][0] = EOS;
						} else if (pass1_check_preamble_commands())
						{
							token[0][0] = EOS;
						} else if (pass1_check_everywhere_commands())
						{
							token[0][0] = EOS;
						}
					}

					/* Kommandos, die ueberall erlaubt sind... */
					if (token[0][0] != EOS)
					{
						if (strcmp(token[0], "!nop") == 0)
						{
							bNopDetected = !bNopDetected;
						} else if (strcmp(token[0], "!label") == 0 ||
							       strcmp(token[0], "!l") == 0)
						{
							tokcpy2(tmp, ArraySize(tmp));
							replace_udo_quotes(tmp);
							add_label(tmp, FALSE, toc_inside_popup(), FALSE, FALSE);
						} else if (strcmp(token[0], "!label*") == 0 ||
							       strcmp(token[0], "!l*") == 0)
						{
							tokcpy2(tmp, ArraySize(tmp));
							replace_udo_quotes(tmp);
							add_label(tmp, FALSE, toc_inside_popup(), TRUE, FALSE);
						} else if (strcmp(token[0], "!label-") == 0)
						{
							tokcpy2(tmp, ArraySize(tmp));
							replace_udo_quotes(tmp);
							add_label(tmp, FALSE, toc_inside_popup(), FALSE, TRUE);
						} else if (strcmp(token[0], "!include") == 0)
						{
							c_include();
						} else if (strcmp(token[0], "!input") == 0)
						{
							c_input();
						} else if (strcmp(token[0], "!rinclude") == 0)
						{
							c_include_raw();
						} else if (strcmp(token[0], "!vinclude") == 0)
						{
							c_include_verbatim();
						} else if (strcmp(token[0], "!pinclude") == 0)
						{
							c_include_preformatted();
						} else if (strcmp(token[0], "!sinclude") == 0)
						{
							c_include_src();
						} else if (strcmp(token[0], "!cinclude") == 0)
						{
							c_include_comment();
						} else if (strcmp(token[0], "!ldinclude") == 0)
						{
							c_include_linedraw();
						} else if (strcmp(token[0], "!code_source") == 0)
						{
							c_code_source();
						} else if (strcmp(token[0], "!code") == 0)
						{
							warning_message(_("!code is deprecated, use !code_source instead"));
							c_code_source();
						} else if (strcmp(token[0], "!code_target") == 0)
						{
							c_code_target();
						} else if (strcmp(token[0], "!universal_charset") == 0)
						{
							c_universal_charset();
						} else if (strcmp(token[0], "!break") == 0)
						{
							bBreakInside = TRUE;
						} else if (strcmp(token[0], "!error") == 0)
						{
							c_error();
						} else if (strcmp(token[0], "!use_raw_header") == 0)
						{
							set_raw_header_filename();
						} else if (strcmp(token[0], "!use_raw_footer") == 0)
						{
							set_raw_footer_filename();
						} else if (pass1_check_everywhere_commands())
						{
							zeile[0] = EOS;
						}
					}
				}
			}
		}
	}

	/* richtigen Einsatz von !if testen */
	if (!bBreakHappened && !bBreakInside)
	{
		if (counter_if_stack > start_if_stack)
		{
			error_missing_endif(file_lookup(if_stack[counter_if_stack].loc.id), if_stack[counter_if_stack].loc.line);
		}
	}

	pop_file_stack();

	token_reset();

	multitasking_interrupt();

	return !bFatalErrorDetected;
}



static void dump_node_structure(void)
{
	TOCTYPE d;
	TOCIDX ti;
	TOCITEM *tocptr;
	_BOOL in_appendix = FALSE;

	fprintf(fTreefile, "\n");
	for (ti = 1; ti <= p1_toc_counter; ti++)
	{
		tocptr = toc_table[ti];
		if (tocptr->appendix)
			in_appendix = TRUE;
		for (d = TOC_NODE1; d <= tocptr->toctype; d++)
		{
			if (d == TOC_NODE1 && tocptr->appendix)
				fprintf(fTreefile, "  %c ", 'A' + tocptr->nr[d] - 1);
			else
				fprintf(fTreefile, "%3d ", tocptr->nr[d]);
		}
		for (; d <= toc_maxdepth; d++)
			fprintf(fTreefile, "    ");
		fprintf(fTreefile, "  %s; %s", tocptr->nodename, file_lookup(tocptr->source_location.id));
		if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
			fprintf(fTreefile, "; %s", tocptr->filename);
		fprintf(fTreefile, "\n");
		UNUSED(in_appendix);
	}
}





/*******************************************************************************
*
*  output_verbatim_line():
*     output one line in verbatim environment
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_verbatim_line(char *zeile)
{
	char indent[128];

	if (zeile[0] == '#')
	{
		recode(zeile, iEncodingSource, iEncodingTarget);
	}

	strcpy_indent(indent);
	if (use_justification)
		indent2space(indent);

	if (no_verbatim_umlaute)
		recode_chrtab(zeile, CHRTAB_ASCII);

	/* TABs in Leerzeichen umwandeln */
	if (strchr(zeile, '\t') != NULL)
		tabs2spaces(zeile, bDocTabwidth);

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
	switch (desttype)
	{
	case TOASC:
	case TODRC:
	case TOMAN:
	case TOPCH:
	case TOSTG:
	case TOAMG:
	case TOTVH:
		if (!(pflag[PASS2].env == ENV_PREFORMATTED && pflag[PASS2].doinside))
		{
			size_t len = strlen(indent) + strlen(zeile);
			if (len > zDocParwidth)
			{
				if (warning_long_destline(outfile.full, outlines + 1, (int) len))
					note_message(_("check this paragraph"));
			}
		}
		break;
	}

	switch (desttype)
	{
	case TORTF:
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
		if (indent[0] == EOS)
			strcpy(indent, " ");
		auto_quote_chars(zeile, TRUE);
		auto_references(zeile, FALSE, "", 0, 0);
		break;

	case TOSTG:
	case TOAMG:
		replace_1at_by_2at(zeile);
		if (pflag[PASS2].env == ENV_PREFORMATTED && pflag[PASS2].doinside)
		{
			c_commands_inside(zeile, TRUE);

			replace_macros(zeile);
			c_divis(zeile);
			c_vars(zeile);
			c_tilde(zeile);
			c_styles(zeile);
			c_commands_inside(zeile, FALSE);

			replace_defines(zeile);
			if (bCheckMisc)
				auto_references(zeile, FALSE, "", 0, 0);
			replace_placeholders(zeile);
			replace_speccmds(zeile);
			c_internal_styles(zeile);

			replace_udo_tilde(zeile);
			replace_udo_nbsp(zeile);
			reset_placeholders();
			reset_refs();
		} else
		{
			if (bCheckMisc)
				auto_references(zeile, FALSE, "", 0, 0);
		}
		break;

	case TOTEX:
	case TOPDL:
		indent[0] = EOS;
		break;

	case TOLYX:
		indent[0] = EOS;
		outln("\\layout LyX-Code");
		outln("");
		replace_all(zeile, "\\", "\\backslash" INDENT_S);
		if (zeile[0] == EOS)
			strcpy(zeile, "\n \n");
		else
			replace_all(zeile, " ", "\n\\begin_inset space ~\n\\end_inset\n");
		indent2space(zeile);
		break;

	case TOINF:
		indent[0] = EOS;
		auto_quote_chars(zeile, TRUE);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		indent[0] = EOS;
		auto_quote_chars(zeile, TRUE);
		if (pflag[PASS2].env == ENV_PREFORMATTED && pflag[PASS2].doinside)
		{
			c_commands_inside(zeile, TRUE);

			replace_macros(zeile);
			c_divis(zeile);
			c_vars(zeile);
			c_tilde(zeile);
			c_styles(zeile);
			c_commands_inside(zeile, FALSE);

			replace_defines(zeile);
			auto_references(zeile, FALSE, "", 0, 0);
			replace_placeholders(zeile);
			replace_speccmds(zeile);
			c_internal_styles(zeile);

			replace_udo_tilde(zeile);
			replace_udo_nbsp(zeile);
		} else
		{
			auto_references(zeile, FALSE, "", 0, 0);
		}
		break;

	case TOLDS:
		indent[0] = EOS;
		qreplace_all(zeile, "&", 1, "&ero;", 5);
		qreplace_all(zeile, "</", 2, "&etago;", 7);
		break;

	case TODRC:
		break;

	case TOIPF:
		indent[0] = EOS;
		auto_quote_chars(zeile, TRUE);
		auto_references(zeile, FALSE, "", 0, 0);
		break;

	case TOKPS:
		auto_quote_chars(zeile, TRUE);
		strinsert(indent, "(");
		strcat(zeile, ") show newline");
		break;
	}

	if (indent[0] != '\0')
		out(indent);
	outln(zeile);
}





/*******************************************************************************
*
*  output_linedraw_line():
*     output one line in linedraw environment (RTF only)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_linedraw_line(char *zeile)
{
	char indent[128];

	if (desttype != TORTF)
	{
		output_verbatim_line(zeile);
		return;
	}

	strcpy_indent(indent);

	/* TABs in Leerzeichen umwandeln */
	if (strchr(zeile, '\t') != NULL)
		tabs2spaces(zeile, bDocTabwidth);

	qreplace_all(indent, "\\qj", 3, "\\ql", 3);
	auto_quote_linedraw(zeile);
	voutlnf("%s%s%s", indent, zeile, rtf_par);
}





/*******************************************************************************
*
*  output_comment_line():
*     output one line in comment environment
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_comment_line(char *zeile)
{
	switch (desttype)
	{
	case TOHAH:
	case TOHTM:
	case TOMHH:
		voutlnf("<!-- %s -->", zeile);
		break;

	case TOLDS:
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

	case TOWIN:
	case TOWH4:
	case TOAQV:
	case TORTF:
	case TOPCH:
	case TONRO:
		break;

	case TOASC:
		/* <???> Hier noch use_comment abfragen */
		break;

	case TOKPS:
		voutlnf("%% %s", zeile);
		break;
	}
}





/*******************************************************************************
*
*  c_comment():
*     wrapper for line output in comment environment
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_comment(void)
{
	char s[512];

	tokcpy2(s, ArraySize(s));
	output_comment_line(s);
}





/*******************************************************************************
*
*  pass2_check_environments():
*     check special environments in pass 2
*
*  Return:
*      TRUE: force (!nl) after the end of this environment
*     FALSE: don't force (!nl)
*
******************************************|************************************/

LOCAL _BOOL pass2_check_environments(char *zeile)
{
	char cmd[128];
	char *p;
	const char *pcmd;

	strncpy(cmd, zeile, ArraySize(cmd));
	cmd[ArraySize(cmd) - 1] = EOS;
	pcmd = cmd;
	while (*pcmd == ' ' || *pcmd == '\t')
		pcmd++;
	if (pcmd[0] != META_C)
		return FALSE;
	p = strchr(pcmd, ' ');
	if (p == NULL)
		p = strchr(pcmd, '\t');
	if (p != NULL)
		*p = EOS;

	/* ---Verbatim-Umgebung--- */
	if (pflag[iUdopass].env == ENV_NONE || pflag[iUdopass].env == ENV_VERBATIM)
	{
		if (strcmp(pcmd, CMD_BEGIN_VERBATIM) == 0)
		{
			pflag[iUdopass].env = ENV_VERBATIM;
			pflag[iUdopass].loc = uiFiles[iFilesOpened - 1].loc;
			pflag[iUdopass].env1st = TRUE;
			if (token_counter > 0)
				token_output(TRUE, TRUE);
			zeile[0] = EOS;
			output_begin_verbatim("UDO_env_verbatim");
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_VERBATIM) == 0)
		{
			if (pflag[iUdopass].env == ENV_VERBATIM)
			{
				pflag[iUdopass].env = ENV_NONE;
				zeile[0] = EOS;
				output_end_verbatim();
			} else
			{
				error_end_without_begin(CMD_END_VERBATIM, CMD_BEGIN_VERBATIM);
				zeile[0] = EOS;
			}
			return TRUE;
		}
	}


	/* ---Sourcecode-Umgebung--- */
	if (pflag[iUdopass].env == ENV_NONE || pflag[iUdopass].env == ENV_SOURCECODE)
	{
		if (strcmp(pcmd, CMD_BEGIN_SOURCECODE) == 0)
		{
			pflag[iUdopass].env = ENV_SOURCECODE;
			pflag[iUdopass].loc = uiFiles[iFilesOpened - 1].loc;
			pflag[iUdopass].env1st = TRUE;
			if (token_counter > 0)
				token_output(TRUE, TRUE);
			zeile[0] = EOS;
			output_begin_sourcecode();
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_SOURCECODE) == 0)
		{
			if (pflag[iUdopass].env == ENV_SOURCECODE)
			{
				pflag[iUdopass].env = ENV_NONE;
				zeile[0] = EOS;
				output_end_sourcecode();
			} else
			{
				error_end_without_begin(CMD_END_SOURCECODE, CMD_BEGIN_SOURCECODE);
				zeile[0] = EOS;
			}
			return TRUE;
		}
	}

	/* ---Raw-Umgebung--- */
	if (pflag[iUdopass].env == ENV_NONE || pflag[iUdopass].env == ENV_RAW)
	{
		if (strcmp(pcmd, CMD_BEGIN_RAW) == 0)
		{
			pflag[iUdopass].env = ENV_RAW;
			pflag[iUdopass].loc = uiFiles[iFilesOpened - 1].loc;
			pflag[iUdopass].env1st = TRUE;
			if (token_counter > 0)
				token_output(TRUE, FALSE);
			zeile[0] = EOS;
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_RAW) == 0)
		{
			if (pflag[iUdopass].env == ENV_RAW)
			{
				pflag[iUdopass].env = ENV_NONE;
				zeile[0] = EOS;
				outln("");
			} else
			{
				error_end_without_begin(CMD_END_RAW, CMD_BEGIN_RAW);
				zeile[0] = EOS;
			}
			return TRUE;
		}
	}

	/* ---Table-Umgebung--- */
	if (pflag[iUdopass].env == ENV_NONE || pflag[iUdopass].env == ENV_TABLE)
	{
		if (strcmp(pcmd, CMD_BEGIN_TABLE) == 0)
		{
			if (pflag[iUdopass].env == ENV_TABLE)
			{
				/* Es kann nur eine geben */
				error_message(_("UDO cannot handle nested tables"));
				zeile[0] = EOS;
			} else
			{
				pflag[iUdopass].env = ENV_TABLE;
				if (token_counter > 0)
					token_output(TRUE, TRUE);
				pflag[iUdopass].loc = uiFiles[iFilesOpened - 1].loc;
				table_get_header(zeile);
				zeile[0] = EOS;
			}
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_TABLE) == 0)
		{
			if (pflag[iUdopass].env == ENV_TABLE)
			{
				pflag[iUdopass].env = ENV_NONE;
				zeile[0] = EOS;
				table_output();
				outln("");
			} else
			{
				error_end_without_begin(CMD_END_TABLE, CMD_BEGIN_TABLE);
				zeile[0] = EOS;
			}
			return TRUE;
		} else if (pflag[iUdopass].env == ENV_TABLE &&
			(strcmp(pcmd, CMD_BEGIN_NODE) == 0 ||
			 strcmp(pcmd, CMD_END_NODE) == 0 ||
			 strcmp(pcmd, "!begin_node*") == 0 ||
			 strcmp(pcmd, "!begin_pnode") == 0 ||
			 strcmp(pcmd, "!begin_pnode*") == 0))
		{
			error_missing_end(CMD_END_TABLE);
			pflag[iUdopass].env = ENV_NONE;
		}
	}

	/* ---Comment-Umgebung--- */
	if (pflag[iUdopass].env == ENV_NONE || pflag[iUdopass].env == ENV_COMMENT)
	{
		if (strcmp(pcmd, CMD_BEGIN_COMMENT) == 0)
		{
			pflag[iUdopass].env = ENV_COMMENT;
			pflag[iUdopass].env1st = TRUE;
			if (token_counter > 0)
				token_output(TRUE, TRUE);
			pflag[iUdopass].loc = uiFiles[iFilesOpened - 1].loc;
			zeile[0] = EOS;
			output_begin_comment();
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_COMMENT) == 0)
		{
			if (pflag[iUdopass].env == ENV_COMMENT)
			{
				pflag[iUdopass].env = ENV_NONE;
				zeile[0] = EOS;
				output_end_comment();
			} else
			{
				error_end_without_begin(CMD_END_COMMENT, CMD_BEGIN_COMMENT);
				zeile[0] = EOS;
			}
			return TRUE;
		}
	}

	/* ---Linedraw-Umgebung--- */
	if (pflag[iUdopass].env == ENV_NONE || pflag[iUdopass].env == ENV_LINEDRAW)
	{
		if (strcmp(pcmd, CMD_BEGIN_LINEDRAW) == 0)
		{
			pflag[iUdopass].env = ENV_LINEDRAW;
			pflag[iUdopass].env1st = TRUE;
			if (token_counter > 0)
				token_output(TRUE, TRUE);
			pflag[iUdopass].loc = uiFiles[iFilesOpened - 1].loc;
			zeile[0] = EOS;
			output_begin_linedraw();
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_LINEDRAW) == 0)
		{
			if (pflag[iUdopass].env == ENV_LINEDRAW)
			{
				pflag[iUdopass].env = ENV_NONE;
				zeile[0] = EOS;
				output_end_linedraw();
			} else
			{
				error_end_without_begin(CMD_END_LINEDRAW, CMD_BEGIN_LINEDRAW);
				zeile[0] = EOS;
			}
			return TRUE;
		}
	}

	/* ---Preformatted-Umgebung--- */
	if (pflag[iUdopass].env == ENV_NONE || pflag[iUdopass].env == ENV_PREFORMATTED)
	{
		if (strcmp(pcmd, CMD_BEGIN_PREFORMATTED) == 0)
		{
			pflag[iUdopass].env = ENV_PREFORMATTED;
			pflag[iUdopass].env1st = TRUE;
			pflag[iUdopass].doinside = strstr(zeile, "!inside") != NULL;
			if (token_counter > 0)
				token_output(TRUE, TRUE);
			pflag[iUdopass].loc = uiFiles[iFilesOpened - 1].loc;
			zeile[0] = EOS;
			output_begin_preformatted();
			return TRUE;
		} else if (strcmp(pcmd, CMD_END_PREFORMATTED) == 0)
		{
			if (pflag[iUdopass].env == ENV_PREFORMATTED)
			{
				pflag[iUdopass].env = ENV_NONE;
				pflag[iUdopass].doinside = FALSE;
				zeile[0] = EOS;
				output_end_preformatted();
			} else
			{
				error_end_without_begin(CMD_END_PREFORMATTED, CMD_BEGIN_PREFORMATTED);
				zeile[0] = EOS;
			}
			return TRUE;
		}
	}
	return FALSE;
}





/*******************************************************************************
*
*  pass2_check_env_output():
*     output or proceed lines if a special environment is active in pass 2
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void pass2_check_env_output(char *zeile)
{
	switch (pflag[PASS2].env)
	{
	case ENV_VERBATIM:					/* ---- Verbatim-Ausgabe ---- */
		if (!pflag[PASS2].env1st)
			output_verbatim_line(zeile);
		break;

	case ENV_PREFORMATTED:				/* ---- Preformatted-Ausgabe ---- */
		if (!pflag[PASS2].env1st)
			output_verbatim_line(zeile);
		break;

	case ENV_LINEDRAW:					/* ---- Linedraw-Ausgabe ---- */
		if (!pflag[PASS2].env1st)
			output_linedraw_line(zeile);
		break;

	case ENV_RAW:						/* ---- Raw-Ausgabe ---- */
		if (!pflag[PASS2].env1st)
			outln(zeile);
		break;

	case ENV_SOURCECODE:				/* ---- Sourcecode-Ausgabe ---- */
		if (!pflag[PASS2].env1st)
		{
			if (desttype == TOSRC || desttype == TOSRP)
			{
				/* TABs in Leerzeichen umwandeln */
				if (strchr(zeile, '\t') != NULL)
					tabs2spaces(zeile, bDocTabwidth);
				outln(zeile);
			} else if (!no_sourcecode)
			{
				output_verbatim_line(zeile);
			}
		}
		break;

	case ENV_COMMENT:					/* ---- Comment-Ausgabe ---- */
		if (!pflag[PASS2].env1st)
		{
			/* Nicht alle Formate ermoeglichen Kommentare */
			output_comment_line(zeile);
		}
		break;

	case ENV_TABLE:					/* ---- Tabelle erweitern ---- */
		table_add_line(zeile);
		break;
	}

	pflag[PASS2].env1st = FALSE;
}





/*******************************************************************************
*
*  pass2():
*     read and convert lines (pass 2)
*
*  Return:
*      TRUE: everything's fine
*     FALSE: error
*
******************************************|************************************/

LOCAL _BOOL pass2(const char *datei)
{
	MYTEXTFILE *file;
	char zeile[LINELEN];
	char tmp_datei[MYFILE_FULL_LEN];
	size_t len;

	strcpy(tmp_datei, datei);

	file = myTextOpen(tmp_datei);

	if (file == NULL && iFilesOpened > 0)
	{
		build_include_filename(tmp_datei, file_lookup(uiFiles[iFilesOpened - 1].loc.id), ".ui");
		file = myTextOpen(tmp_datei);
	}

	if (file == NULL)
	{
		strcpy(tmp_datei, datei);
		build_include_filename(tmp_datei, infile.full, ".ui");
		file = myTextOpen(tmp_datei);
	}

	if (file == NULL)
	{
		error_open_pass2(datei);
		bErrorDetected = TRUE;
		return FALSE;
	}

	if (push_file_stack(tmp_datei, file) == FALSE)
	{
		myTextClose(file);
		return FALSE;
	}

	show_status_percent(lPass1Lines, lPass2Lines);
	if (bVerbose)
	{
		show_status_file_2(lPass2Lines, tmp_datei);
	}

	while (!bBreakHappened && !bBreakInside && !bFatalErrorDetected && myTextGetline(zeile, LINELEN, file))
	{
		_BOOL ignore_comment_or_empty;

		uiFiles[iFilesOpened - 1].loc.line += 1 + uiMultiLines;
		uiCurrFileLine = uiFiles[iFilesOpened - 1].loc.line;
		lPass2Lines++;
		show_status_percent(lPass1Lines, lPass2Lines);

		if (break_action())
		{
			pop_file_stack();
			return FALSE;
		}

		/* --- remove all line feed and whitespace characters at the end of line --- */
		len = strlen(zeile);
		while (len > 0 && (((_UBYTE) zeile[len - 1]) <= 32))
		{
			zeile[len - 1] = EOS;
			len--;
		}

		/* dont recode commments */
		ignore_comment_or_empty = zeile[0] == '#' || zeile[0] == EOS;
		if (!ignore_comment_or_empty && pflag[PASS2].ignore_line == 0 && pflag[PASS2].env != ENV_RAW)
		{
			recode(zeile, iEncodingSource, iEncodingTarget);
		}

		if (pflag[PASS2].env == ENV_NONE)
		{
			/* Befehle wie !raw [tex] bearbeiten */
			if (pflag[PASS2].ignore_line == 0)
			{
				c_check_raw(zeile);
			}
		}

		if (!ignore_comment_or_empty && pflag[PASS2].env == ENV_NONE)
		{
			pass_check_if(zeile, PASS2);
		}

		/* Spezielle Umgebungen (verbatim, raw, table, sourcecode) testen. */
		/* Gesucht wird nur nach !begin... bzw !end... */
		if (!ignore_comment_or_empty && pflag[PASS2].ignore_line == 0)
		{
			ignore_comment_or_empty |= pass2_check_environments(zeile);
		}

		/* Ausgabe/Bearbeitung der aktuellen Zeile, falls eine */
		/* spezielle Umgebung aktiv ist */
		if (pflag[PASS2].ignore_line == 0)
		{
			pass2_check_env_output(zeile);
		}

		/* Keine spezielle Umgebung aktiv, also Zeile auswerten und */
		/* beim Auftreten einer Leerzeile den Absatz ausgeben */
		if (pflag[PASS2].ignore_line == 0 && pflag[PASS2].env == ENV_NONE)
		{
			if (zeile[0] != EOS)
			{
				if (zeile[0] != '#')
				{
					del_whitespaces(zeile);

					if (zeile[0] == META_C && zeile[1] != QUOTE_C)
						strcpy(current_node_name_sys, zeile);

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
			} else if (token_counter > 0)
			{
				/* Leerzeile */
				token_output(TRUE, TRUE);
			}
		}
	}

	if (token_counter > 0)
	{
		token_output(TRUE, TRUE);
	}

	check_quotes();

	pop_file_stack();

	multitasking_interrupt();

	return !bFatalErrorDetected;
}





/*******************************************************************************
*
*  save_pchelp_commandfile():
*     save command file for Pure C Help Compiler
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_pchelp_commandfile(void)
{
	FILE *cmdfile;

	if (bTestmode)
		return;

	cmdfile = myFwopen(file_lookup(sCmdfull), TOASC);

	if (cmdfile == NULL)
		return;

	save_upr_entry_outfile(file_lookup(sCmdfull));

	fprintf(cmdfile, "-V\n\n");
	fprintf(cmdfile, "%s.HLP\n\n", outfile.name);
	fprintf(cmdfile, "%s.SCR\n", outfile.name);

	fclose(cmdfile);
	bCmdSaved = TRUE;
}





/*******************************************************************************
*
*  save_winhelp_project():
*     save project file for WinHelp Compiler
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_winhelp_project(void)
{
	FILE *hpjfile;
	char n[512];
	char hlp_name[MYFILE_NAME_LEN];
	char bc[128];
	int i;

	if (bTestmode)
		return;

	hpjfile = myFwopen(file_lookup(sHpjfull), FTHPJ);
	if (hpjfile == NULL)
		return;

	save_upr_entry_outfile(file_lookup(sHpjfull));

	/*
	 * "qchPath" is a global variable in WinHelp() that contains the
	 * full path to the current helpfile. We could use that also for
	 * the Windows version, but specifying an empty string will
	 * work there, too.
	 */
	if (desttype == TOAQV)
		strcpy(hlp_name, "qchPath");
	else
		strcpy(hlp_name, "`'");

	fprintf(hpjfile, "[OPTIONS]\n");
	strcpy(n, titleprogram);
	del_right_spaces(n);
	if (desttype != TOWIN)
		recode_chrtab(n, CHRTAB_ANSI);
	qdelete_all(n, "\\~", 2);
	qdelete_all(n, "~", 1);

	/* Title-Option darf maximal 50 Zeichen lang sein */
	if (strlen(n) > 50)
	{
		n[50] = EOS;
	}

	if (n[0] != EOS)
	{
		fprintf(hpjfile, "Title=%s\n", n);
	}

	if (titdat.author != NULL)
	{
		strcpy(n, titdat.author);
		if (desttype != TOWIN)
			recode_chrtab(n, CHRTAB_ANSI);
		qdelete_all(n, "\\~", 2);
		qdelete_all(n, "~", 1);
		fprintf(hpjfile, "Copyright=Copyright (\251) by %s\n", n);
	}

	fprintf(hpjfile, "ErrorLog= %s.err\n", outfile.name);

	/* Weitere Optionen einbauen. Versteht QuickView die? */
	fprintf(hpjfile, "Warning=3\n");
	fprintf(hpjfile, "Report=TRUE\n");

	if (bDocHighCompression)
	{
		fprintf(hpjfile, "Compress=HIGH\n");
	}
	if (bDocMediumCompression)
	{
		fprintf(hpjfile, "Compress=MEDIUM\n");
	}

	fprintf(hpjfile, "\n[WINDOWS]\n");
	fprintf(hpjfile, "main=\"\",(20,20,708,960),0,%s,%s\n", win_color_string(&sDocBackColor), "(192,192,192)");
	fprintf(hpjfile, "win1=\"UDO%s\",(573,71,437,500),0,(255,255,231),(192,192,192),1\n", UDO_REL);

	fprintf(hpjfile, "\n[CONFIG]\n");

	if (!no_buttons)
	{
		if (get_toc_counter() > 1 || (get_toc_counter() > 0 && called_tableofcontents))
		{
			if (desttype == TOAQV)
			{
				/* show default menu */
				fprintf(hpjfile, "Std20Menus()\n");
				/* show default buttons */
				fprintf(hpjfile, "Std20Buttons()\n");
				/* QuickView always needs "&Up" regardless of language */
				fprintf(hpjfile, "CreateButton(\"BTN_UP\", \"%s\", \"JumpID(%s, `%s')\")\n", "&Up", hlp_name,
						WIN_TITLE_NODE_NAME);
			} else
			{
				/* enable browse buttons "<<" and ">>" */
				fprintf(hpjfile, "BrowseButtons()\n");
				fprintf(hpjfile, "CreateButton(\"BTN_UP\", \"%s\", \"JumpID(%s, `%s')\")\n", get_lang()->up, hlp_name,
						WIN_TITLE_NODE_NAME);
				/* create user defined buttons */
				for (i = 0; i < iNumWinButtons; i++)
				{
					if (sDocWinButtonName[i][0] != '\0')
					{
						fprintf(hpjfile, "CreateButton(\"%s\", \"%s\", \"JumpID(%s, `%s')\")\n",
								sDocWinButtonName[i], sDocWinButtonText[i], hlp_name, WIN_TITLE_NODE_NAME);
					}
				}
#if 0
				/* WinHelp: Knopf zum Beenden einbauen */
				fprintf(hpjfile, "CreateButton(\"BTN_EXIT\", \"%s\", \"Exit()\")\n", get_lang()->exit);
#endif
			}

			if (called_tableofcontents)
			{
				node2NrWinhelp(bc, 0);
				fprintf(hpjfile, "ChangeButtonBinding(\"BTN_CONTENTS\", \"JumpID(%s, `%s')\")\n", hlp_name, bc);
			}
		}

		if (use_about_udo)
		{
			/* append "UDO" button */
			fprintf(hpjfile, "CreateButton(\"BTN_UDO\", \"UDO%s\", \"JumpID(%s, `%s')\")\n", UDO_REL, hlp_name,
					WIN_UDO_NODE_NAME);

			/* and also add it to the menu of Winhelp */
			if (desttype == TOAQV)
			{
				/* AQV kann kein zweites Fenster */
				fprintf(hpjfile, "AppendItem(\"mnu_help\", \"item_udoinfo\", \"&UDO%s...\", \"JumpID(%s, `%s')\")\n",
						UDO_REL, hlp_name, WIN_UDO_NODE_NAME);
			} else
			{
				fprintf(hpjfile,
						"AppendItem(\"mnu_help\", \"item_udoinfo\", \"&UDO%s...\", \"JumpID(`>win1', `%s')\")\n",
						UDO_REL, WIN_UDO_NODE_NAME);
			}
		}
	}

	/* Macro used for !url */
	fprintf(hpjfile, "RegisterRoutine(\"shell32.dll\", \"ShellExecuteA\", \"USSSSU\")\n");

	fprintf(hpjfile, "\n[FILES]\n");
	fprintf(hpjfile, "%s.rtf\n", outfile.name);

	if (bUseIdMapFileC)
	{
		fprintf(hpjfile, "\n[MAP]\n");
		fprintf(hpjfile, "#include <%s.hpc>\n", outfile.name);
	}

	fclose(hpjfile);

	bHpjSaved = TRUE;
}





/*******************************************************************************
*
*  save_winhelp4_project():
*     save project file for WinHelp4 Compiler
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_winhelp4_project(void)
{
	FILE *hpjfile;
	char n[512];
	int i;

	if (bTestmode)
		return;

	hpjfile = myFwopen(file_lookup(sHpjfull), FTHPJ);
	if (hpjfile == NULL)
		return;

	save_upr_entry_outfile(file_lookup(sHpjfull));

	fprintf(hpjfile, "; This file is maintained by UDO. Do not modify this file directly.\n\n");
	fprintf(hpjfile, "[OPTIONS]\n");
	fprintf(hpjfile, "HCW=0\n");
	fprintf(hpjfile, "HLP=%s.hlp\n", outfile.name);
	fprintf(hpjfile, "CNT=%s.cnt\n", outfile.name);
	fprintf(hpjfile, "LCID=%s 0x0 0x0\n", get_lang()->lcid);
	strcpy(n, titleprogram);
	del_right_spaces(n);
	recode_chrtab(n, CHRTAB_ANSI);
	qdelete_all(n, "\\~", 2);
	qdelete_all(n, "~", 1);

	if (n[0] != EOS)
	{
		fprintf(hpjfile, "TITLE=%s\n", n);
	}

	if (titdat.author != NULL)
	{
		strcpy(n, titdat.author);
		recode_chrtab(n, CHRTAB_ANSI);
		qdelete_all(n, "\\~", 2);
		qdelete_all(n, "~", 1);
		fprintf(hpjfile, "COPYRIGHT=Copyright (\251) by %s\n", n);
	}

	fprintf(hpjfile, "ERRORLOG=%s.err\n", outfile.name);
	fprintf(hpjfile, "REPORT=TRUE\n");

	if (bDocHighCompression)
	{
		fprintf(hpjfile, "COMPRESS=12 Hall Zeck\n");
	}

	if (bDocMediumCompression)
	{
		fprintf(hpjfile, "COMPRESS=8 Zeck\n");
	}

	fprintf(hpjfile, "\n[WINDOWS]\n");
	fprintf(hpjfile, "main=\"\",(20,20,540,880),0,%s,%s\n", win_color_string(&sDocBackColor), "(r12632256)");
	fprintf(hpjfile, "win1=\"UDO%s\",(573,71,437,500),4,(r15204351),(r12632256),1\n", UDO_REL);

	fprintf(hpjfile, "\n[CONFIG]\n");
	if (!no_buttons)
	{
		if (get_toc_counter() > 1 || (get_toc_counter() > 0 && called_tableofcontents))
		{
			/* << und >> anzeigen */
			fprintf(hpjfile, "BrowseButtons()\n");
			fprintf(hpjfile, "CreateButton(\"BTN_UP\", \"%s\", \"JumpID(`', `%s')\")\n", get_lang()->up,
					WIN_TITLE_NODE_NAME);

			/* create user defined buttons */
			for (i = 0; i < iNumWinButtons; i++)
			{
				if (sDocWinButtonName[i][0] != '\0')
				{
					fprintf(hpjfile, "CreateButton(\"%s\", \"%s\", \"JumpID(`', `%s')\")\n",
							sDocWinButtonName[i], sDocWinButtonText[i], WIN_TITLE_NODE_NAME);
				}
			}
		}

		if (use_about_udo)
		{
			/* append "UDO" button */
			fprintf(hpjfile, "CreateButton(\"BTN_UDO\", \"UDO%s\", \"JumpID(`>win1', `%s')\")\n", UDO_REL,
					WIN_UDO_NODE_NAME);

			/* and also add it to the menu of Winhelp */
			fprintf(hpjfile, "AppendItem(\"mnu_help\", \"item_udoinfo\", \"&UDO%s...\", \"JumpID(`>win1', `%s')\")\n",
					UDO_REL, WIN_UDO_NODE_NAME);
		}

		/* if we created our own table-of-contents, redirect the button there */
		if (called_tableofcontents)
		{
			node2NrWinhelp(n, 0);
			fprintf(hpjfile, "ChangeButtonBinding(\"BTN_CONTENTS\", \"JumpID(`', `%s')\")\n", n);
		}
	}

	/* Macro used for !url */
	fprintf(hpjfile, "RegisterRoutine(\"shell32.dll\", \"ShellExecuteA\", \"USSSSU\")\n");

	fprintf(hpjfile, "\n[FILES]\n");
	fprintf(hpjfile, "%s.rtf\n", outfile.name);

	if (bMapSavedC)
	{
		fprintf(hpjfile, "\n[MAP]\n");
		fprintf(hpjfile, "#include \"%s.hpc\"\n", outfile.name);
	}

	fclose(hpjfile);

	bHpjSaved = TRUE;
}





/*******************************************************************************
*
*  save_htmlhelp_project():
*     save project file for HTML Help
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void save_htmlhelp_project(void)
{
	FILE *hhpfile;
	char sTitle[1024];
	char hhcname[MYFILE_NAME_LEN + MYFILE_SUFF_LEN + 1];
	char hhkname[MYFILE_NAME_LEN + MYFILE_SUFF_LEN + 1];
	char aboname[MYFILE_NAME_LEN + MYFILE_SUFF_LEN + 1];
	const char *jump1text;
	unsigned long properties = 0x63520UL;
	unsigned long buttons = 0x304eUL;

	if (bTestmode)
		return;

	hhpfile = myFwopen(file_lookup(sHhpfull), FTHHP);
	if (hhpfile == NULL)
		return;

	save_upr_entry_outfile(file_lookup(sHhpfull));

	fprintf(hhpfile, "[OPTIONS]\n");

	strcpy(sTitle, titleprogram);		/* Windows-Umlaute benutzen, also nicht "titleprogram"! */
	html2sys(sTitle);

	fprintf(hhpfile, "Title=%s\n", sTitle);
	fprintf(hhpfile, "Compatibility=1.1 or later\n");
	fprintf(hhpfile, "Compiled file=%s.chm\n", old_outfile.name);
	fprintf(hhpfile, "Error log file=%s.log\n", old_outfile.name);

	*hhcname = '\0';
	if (bHhcSaved)
	{
		strcat(strcpy(hhcname, old_outfile.name), ".hhc");
		fprintf(hhpfile, "Contents file=%s\n", hhcname);
	}

	*hhkname = '\0';
	if (bHhkSaved)
	{
		strcat(strcpy(hhkname, old_outfile.name), ".hhk");
		fprintf(hhpfile, "Index file=%s\n", hhkname);
	}

	if (use_about_udo)
	{
		strcat(strcpy(aboname, "aboutudo"), outfile.suff);
		jump1text = "UDO" UDO_REL;
		buttons |= 1l << 18;			/* HHWIN_BUTTON_JUMP1 */
	} else
	{
		*aboname = '\0';
		jump1text = "";
	}
	fprintf(hhpfile, "Default topic=%s%s\n", old_outfile.name, outfile.suff);
	fprintf(hhpfile, "Display compile progress=No\n");
	fprintf(hhpfile, "Flat=Yes\n");
	fprintf(hhpfile, "Full-text search=Yes\n");
	fprintf(hhpfile, "Auto Index=Yes\n");
	fprintf(hhpfile, "Language=%s\n", get_lang()->lcid);
	fprintf(hhpfile, "Default Window=main\n");
	fprintf(hhpfile, "\n");
	fprintf(hhpfile, "[FILES]\n");
	fprintf(hhpfile, "%s%s\n", old_outfile.name, outfile.suff);
	/* FIXME: have to output all style sheet filenames here */
	fprintf(hhpfile, "\n");
	fprintf(hhpfile, "[WINDOWS]\n");
	fprintf(hhpfile, "main=,\"%s\",\"%s\",\"%s%s\",\"%s%s\",\"%s\",\"%s\",,,0x%lx,,0x%lx,,,,,,,,0\n", hhcname, hhkname, old_outfile.name, outfile.suff,	/* default file */
			old_outfile.name, outfile.suff,	/* home button file */
			aboname, jump1text, properties, buttons);

	if (bMapSavedC)
	{
		fprintf(hhpfile, "\n[ALIAS]\n");
		fprintf(hhpfile, "#include <%s.hha>\n", old_outfile.name);

		fprintf(hhpfile, "\n[MAP]\n");
		fprintf(hhpfile, "#include <%s.hhm>\n", old_outfile.name);
	}

	fclose(hhpfile);

	bHhpSaved = TRUE;
}





/*******************************************************************************
*
*  set_format_flags():
*     set important format-dependant conversion flags
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void set_format_flags(void)
{
	/* Bei manchen Formaten ist es fuer die Laengenberechnung */
	/* einer Zeile enorm wichtig, die Laenge ohne UDO- */
	/* Spezialitaeten zu kennen (STG, PCH, ASC...) */
	/* Bei manchen ist es hingegen wurscht, wie lang eine */
	/* Zeile wird (RTF, HTML, WinHelp, ...) */
	format_needs_exact_toklen = FALSE;

	/* Bei den Formaten, bei denen referenziert wird und bei */
	/* denen die Laenge einer Ausgabezeile egal ist, sollte */
	/* erst dann referenziert werden, wenn der ganze Absatz */
	/* moeglichst in einer Zeile enthalten ist, damit nicht */
	/* durch einen vorzeitigen Umbruch Links verloren gehen. */
	format_uses_output_buffer = FALSE;


	/* Die Kommandos einiger Formate muessen vor der Veraen- */
	/* derung durch die Referenzierung geschuetzt werden. */
	/* z.B. WinHelp und HTML. Dort waere es fatal, wuerde UDO */
	/* \li, \footnote oder dergleichen referenzieren! */
	format_protect_commands = FALSE;

	switch (desttype)
	{
	case TOASC:
	case TODRC:
	case TOSRC:
	case TOSRP:
	case TOKPS:
		format_needs_exact_toklen = TRUE;
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		format_uses_output_buffer = TRUE;
		format_protect_commands = TRUE;
		break;

	case TOHPH:
		format_uses_output_buffer = TRUE;
		format_protect_commands = TRUE;
		break;

	case TOIPF:
		format_protect_commands = TRUE;
		break;

	case TOINF:
		break;

	case TOLDS:
		format_uses_output_buffer = TRUE;
		format_protect_commands = TRUE;
		break;

	case TOMAN:
	case TONRO:
		format_needs_exact_toklen = TRUE;
		break;

	case TOPCH:
		format_needs_exact_toklen = TRUE;
		break;

	case TORTF:
		break;

	case TOSTG:
	case TOAMG:
		format_needs_exact_toklen = TRUE;
		break;

	case TOTEX:
	case TOPDL:
	case TOLYX:
		break;

	case TOTVH:
		format_needs_exact_toklen = TRUE;
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
		format_needs_exact_toklen = TRUE;
		format_uses_output_buffer = TRUE;
		format_protect_commands = TRUE;
		break;
	}
}





/*******************************************************************************
*
*  udo_cleanup():
*     release used resources
*
*  Return:
*     -
*
******************************************|************************************/

static _BOOL udo_cleanup(void)
{
	if (bLogopened)
		fclose(fLogfile);
	if (bHypopened)
		fclose(fHypfile);
	if (bIdxopened)
		fclose(fIdxfile);
	if (bTreeopened)
		fclose(fTreefile);
	if (bUPRopened)
		fclose(fUPRfile);
	if (bOutOpened && outfile.file != NULL)
	{
		fclose(outfile.file);
		outfile.file = NULL;
		bOutOpened = FALSE;
	}
	while (pop_file_stack())
		;
	exit_modules();
	free_token_output_buffer();
	exit_udo_vars();
	return FALSE;
}





/*******************************************************************************
*
*  get_timestr():
*     Ermittelt die aktuelle Uhrzeit
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void get_timestr(char *t)
{
	time_t timer;
	struct tm *zeit;

	time(&timer);
	zeit = localtime(&timer);

	sprintf(t, "%02d:%02d:%02d", zeit->tm_hour, zeit->tm_min, zeit->tm_sec);
}



static NOINLINE void print_results(void)
{
	char sInfMsg[MYFILE_FULL_LEN + 100];
	int val;

	if (!bTestmode && !bFatalErrorDetected)
	{
		sprintf(sInfMsg, _("Output (%lu lines) written to %s"), outlines, outfile.full);
		show_status_info(sInfMsg);
	} else if (bTestmode)
	{
		sprintf(sInfMsg, _("Output: %lu lines"), outlines);
		show_status_info(sInfMsg);
	}

	if ((val = get_warning_counter()) > 0)
	{
		sprintf(sInfMsg, _("Warnings: %d"), val);
		show_status_errors(sInfMsg);
	}

	if ((val = get_note_counter()) > 0)
	{
		sprintf(sInfMsg, _("Notes:    %d"), val);
		show_status_errors(sInfMsg);
	}

	if ((val = get_error_counter()) > 0)
	{
		sprintf(sInfMsg, _("Errors:   %d"), val);
		show_status_errors(sInfMsg);
	}
}





/*******************************************************************************
*
*  udo():
*     main routine
*
*  Return:
*      TRUE: everything worked fine
*     FALSE: some error occured
*
******************************************|************************************/

GLOBAL _BOOL udo(const char *datei)
{
	_BOOL ret = FALSE;
	int i;
	FILE *file;
	char tmp_filename[MYFILE_FULL_LEN];

	get_timestr(timer_start);

	bFatalErrorDetected = FALSE;
	bErrorDetected = FALSE;
	bBreakHappened = FALSE;
	bBreakInside = FALSE;

	fLogfile = stderr;
	bLogopened = FALSE;

	set_destlang(TOENG);
	iCharset = iEncodingSource = SYSTEM_CHARSET;
	set_encoding_target(CODE_DEFAULT);

	init_modules();
	init_udosymbol_pass1();
	set_format_flags();

	bOutOpened = FALSE;
	outlines = 0;

	fHypfile = stderr;
	bHypopened = FALSE;
	bHypSaved = FALSE;
	bHypfailed = FALSE;
	hyplist = NULL;
	fIdxfile = stderr;
	bIdxopened = FALSE;
	bIdxSaved = FALSE;
	bIdxfailed = FALSE;
	idxlist = NULL;
	fTreefile = stderr;
	bTreeopened = FALSE;
	bTreeSaved = FALSE;
	fUPRfile = stderr;
	bUPRopened = FALSE;
	bUPRSaved = FALSE;

	/* Erstmal testen, ob die Datei vorhanden ist, damit nicht unnoetig Dateien angelegt werden. */

	strcpy(tmp_filename, datei);

	file = fopen(tmp_filename, "r");
	if (file == NULL)
	{
		build_include_filename(tmp_filename, infile.full, ".u");
		file = fopen(tmp_filename, "r");
		if (file == NULL)
		{
			error_open_infile(datei);
			return udo_cleanup();
		}
		datei = tmp_filename;
	}
	fclose(file);

	if (!bNoLogfile)
	{
		if (outfile.full[0] != EOS)
		{
			if (sLogfull == 0)
				logfile_adjust();

			fLogfile = myFwopen(file_lookup(sLogfull), TOASC);
			if (fLogfile == NULL)
			{
				fLogfile = stderr;
				warning_err_logfile();
				bErrorDetected = TRUE;
				return udo_cleanup();
			}
			bLogopened = TRUE;
			save_upr_entry_outfile(file_lookup(sLogfull));
		}
	}

	if (bUseTreefile)
	{
		if (outfile.full[0] != EOS)
		{
			if (sTreefull != 0)
			{
				fTreefile = myFwopen(file_lookup(sTreefull), TOASC);
				if (fTreefile == NULL)
				{
					fTreefile = stderr;
					warning_err_treefile();
					bErrorDetected = TRUE;
					return udo_cleanup();
				}
				bTreeopened = TRUE;
				bTreeSaved = TRUE;
				save_upr_entry_outfile(file_lookup(sTreefull));
			}
		}
	}

	if (bUseUPRfile)
	{
		if (outfile.full[0] != EOS)
		{
			if (sUPRfull != 0)
			{
				fUPRfile = myFwopen(file_lookup(sUPRfull), TOASC);
				if (fUPRfile == NULL)
				{
					fUPRfile = stderr;
					warning_err_uprfile();
					bErrorDetected = TRUE;
					return udo_cleanup();
				}
				bUPRopened = TRUE;
				bUPRSaved = TRUE;
				save_upr_entry_outfile(file_lookup(sUPRfull));
			}
		}
	}

	if (outfile.full[0] != EOS)
	{
		if (strcmp(outfile.full, "~") == 0 || strcmp(outfile.full, "!") == 0)
		{
			dest_adjust();
		}

		if (!bTestmode)
		{
			if (strcmp(outfile.full, infile.full) == 0)
			{
				error_message(_("source and destination file are equal: <%s>"), outfile.full);
				bErrorDetected = TRUE;
				return udo_cleanup();
			}

			outfile.file = myFwopen(outfile.full, desttype);
			if (outfile.file == NULL)
			{
				error_open_outfile(outfile.full);
				warning_err_destination();
				bErrorDetected = TRUE;
				return udo_cleanup();
			}
			bOutOpened = TRUE;
			save_upr_entry_outfile(outfile.full);
		}
	}


	for (i = 0; i < MAXENVLEVEL; i++)
		iEnvIndent[i] = 0;

	strcpy(old_outfile.full, outfile.full);
	strcpy(old_outfile.driv, outfile.driv);
	strcpy(old_outfile.path, outfile.path);
	strcpy(old_outfile.name, outfile.name);
	strcpy(old_outfile.suff, outfile.suff);

	init_vars_spec();
	init_lang();

	bBreakInside = FALSE;
	bInsideDocument = FALSE;
	b1stQuote = FALSE;
	b1stApost = FALSE;
	bDocUniversalCharsetOn = FALSE;

	logln_warnings_errors();

	show_status_pass(_("Pass 1..."));

	clear_if_stack();

	iUdopass = PASS1;

	if (pass1(datei) &&					/* Erster Durchlauf aufgrund eines Fehlers gescheitert? */
		( /* !bCheckMisc || */ check_modules_pass1()))	/* Diverse Ueberpruefungen auf Wunsch durchfuehren */
	{
		/* Unregistrierte Versionen erzeugen immer die Werbeseite */
		if (!config.bRegistered)
		{
			/* use_about_udo = TRUE; *//* UDO is now Open Source */
		}

		switch (desttype)
		{
		case TOHTM:
		case TOHAH:
			/* not for HtmlHelp because index is saved directly as html and no node is generated */
			if (!no_index && bCalledIndex && use_udo_index)
				add_pass1_index_udo();
			break;
		}

		if (bUseTreefile && bTreeopened)
			dump_node_structure();

		if (use_about_udo && desttype != TOUDO)
		{
			in_about_udo = TRUE;
			add_pass1_about_udo();
			in_about_udo = FALSE;
		}

		/* Speicher anfordern */
		if (no_pass2)
		{
			ret = TRUE;
		} else if (malloc_token_output_buffer())
		{
			/* itemchar wird erst nach pass1() gesetzt */
			/* bei !no_umlaute wird kein 8bit-Zeichen mehr verwendet */
			init_env_itemchar();

			bBreakInside = FALSE;
			bInsideDocument = FALSE;
			b1stQuote = FALSE;
			b1stApost = FALSE;
			iCharset = SYSTEM_CHARSET;
			bDocUniversalCharsetOn = FALSE;

			/* init_vars_spec(); */
			init_module_toc_pass2();
			init_module_tp_pass2();
			init_module_img_pass2();
			init_udosymbol_pass2();
			define_counter = 0;

			sort_hyphens();

			if (!bBreakHappened && !bBreakInside)
			{
				if (desttype == TOUDO)
					show_status_pass("udo2udo...");
				else
					show_status_pass(_("Pass 2..."));

				/* Die folgende if-Abfrage ist nur ein Workaround,
				 * damit -vor allem bei der HTML-Ausgabe- die
				 * Kapitelnummern stimmen und die Unterinhalts-
				 * verzeichnisse erzeugt werden
				 *
				 * Die if-Abfrage bleibt drin, fuer den Fall,
				 * dass ein aehnlicher Fehler nochmal
				 * auftritt, er wird dann vielleicht frueher erkannt
				 */
#ifdef _DEBUG
				if (bInsideAppendix)
				{
					bInsideAppendix = FALSE;
					fprintf(stderr, "Warning: bInsideAppendix=TRUE - fixed it\n");
				}
#endif

				clear_if_stack();
				output_preamble();

				if (desttype == TOUDO)
				{
					iUdopass = PASSU;
					if (passU(datei))
					{
						ret = TRUE;
					}
				} else
				{
					iUdopass = PASS2;

					if ((desttype == TOHTM || desttype == TOHAH) && html_frames_layout)
					{
						html_save_frameset();
					}

					if (pass2(datei))
					{
						if (bCalledBeginDocument && !bCalledEndDocument)
						{
							error_missing_end(CMD_END_DOCUMENT);
							if (pflag[iUdopass].env != ENV_NONE)
							{
								note_message(_("last environment: %s line %lu"), file_lookup(pflag[iUdopass].loc.id), pflag[iUdopass].loc.line);
							}
							c_end_document();
						}

						outln("");
						outln("");

						ret = TRUE;

						if (bOutOpened)
						{
							switch (desttype)
							{
							case TOPCH:
								save_pchelp_commandfile();
								break;

							case TOAQV:
							case TOWIN:
							case TOWH4:
								if (desttype == TOWH4)
								{
									bCntSaved = save_winhelp4_cnt();
								}
								if (bUseIdMapFileC)
								{
									bMapSavedC = save_winhelp_map_c();
								}
								if (bUseIdMapFilePas)
								{
									bMapSavedPas = save_winhelp_map_pas();
								}
								if (bUseIdMapFileVB)
								{
									bMapSavedVB = save_winhelp_map_vb();
								}
								if (bUseIdMapFileGFA)
								{
									bMapSavedGFA = save_winhelp_map_gfa();
								}
								if (desttype == TOWH4)
								{
									save_winhelp4_project();
								} else
								{
									save_winhelp_project();
								}
								break;

							case TORTF:
								break;

							case TOHAH:
							case TOHTM:
								break;

							case TOMHH:
								bHhcSaved = save_htmlhelp_contents(file_lookup(sHhcfull));
								bHhkSaved = save_htmlhelp_index(file_lookup(sHhkfull));
								if (bUseIdMapFileC)
								{
									strcpy(outfile.full, old_outfile.full);
									bMapSavedC = save_htmlhelp_map();
									bMapSavedC &= save_htmlhelp_alias();
								}
								save_htmlhelp_project();
								break;

							case TOSTG:
							case TOAMG:
								break;

							case TOIPF:
								break;

							case TOLYX:
								break;

							case TOPDL:
								break;
							}
						}

						if (bCheckMisc)
						{
							/* Diverse Ueberpruefungen auf Wunsch durchfuehren */
							check_modules_pass2();
						}
					}
				}

				get_timestr(timer_stop);
			}
		}
	}



	/* Hier geht's weiter, wenn schon pass1() versagte */

	/* Alten Filenamen zurueckholen */
	strcpy(outfile.full, old_outfile.full);
	strcpy(outfile.driv, old_outfile.driv);
	strcpy(outfile.path, old_outfile.path);
	strcpy(outfile.name, old_outfile.name);
	strcpy(outfile.suff, old_outfile.suff);
	sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);

	/* Hier Informationen ueber das erzeugte File ausgeben. */

	if (!bNoLogfile)
	{
		logln_information();
		vloglnf("source file: %s", infile.full);
		logln("");
		vloglnf("Warnings:                      %d", get_warning_counter());
		vloglnf("Notes:                         %d", get_note_counter());
		vloglnf("Errors:                        %d", get_error_counter());
		logln("");
		vloglnf("Nodes:                         %u", all_nodes[TOC_NODE1]);
		vloglnf("Subnodes:                      %u", all_nodes[TOC_NODE2]);
		vloglnf("Subsubnodes:                   %u", all_nodes[TOC_NODE3]);
		vloglnf("Subsubsubnodes:                %u", all_nodes[TOC_NODE4]);
		vloglnf("Subsubsubsubnodes:             %u", all_nodes[TOC_NODE5]);
		vloglnf("Subsubsubsubsubnodes:          %u", all_nodes[TOC_NODE6]);
		vloglnf("Subsubsubsubsubsubnodes:       %u", all_nodes[TOC_NODE7]);
		vloglnf("Subsubsubsubsubsubsubnodes:    %u", all_nodes[TOC_NODE8]);
		vloglnf("Subsubsubsubsubsubsubsubnodes: %u", all_nodes[TOC_NODE9]);
		vloglnf("Total nodes:                   %lu", (unsigned long) p1_toc_counter + 1);
		vloglnf("Macros:                        %u", macro_counter);
		vloglnf("Defines:                       %u", define_counter);
		vloglnf("Hyphens:                       %lu", (unsigned long) hyphen_counter);
		logln("");
		vloglnf("started:  %s", timer_start);
		vloglnf("finished: %s", timer_stop);
		logln("");

		if (bGifHmSaved)
			logln_file_generated("GIF", file_lookup(sGifHmFull), "");
		if (bGifUpSaved)
			logln_file_generated("GIF", file_lookup(sGifUpFull), "");
		if (bGifLfSaved)
			logln_file_generated("GIF", file_lookup(sGifLfFull), "");
		if (bGifRgSaved)
			logln_file_generated("GIF", file_lookup(sGifRgFull), "");
		if (bGifNoHmSaved)
			logln_file_generated("GIF", file_lookup(sGifNoHmFull), "");
		if (bGifNoUpSaved)
			logln_file_generated("GIF", file_lookup(sGifNoUpFull), "");
		if (bGifNoLfSaved)
			logln_file_generated("GIF", file_lookup(sGifNoLfFull), "");
		if (bGifNoRgSaved)
			logln_file_generated("GIF", file_lookup(sGifNoRgFull), "");
		if (bGifTpSaved)
			logln_file_generated("GIF", file_lookup(sGifTpFull), "");
		if (bGifFoSaved)
			logln_file_generated("GIF", file_lookup(sGifFoFull), "");
		if (bGifFcSaved)
			logln_file_generated("GIF", file_lookup(sGifFcFull), "");
		if (bGifFsSaved)
			logln_file_generated("GIF", file_lookup(sGifFsFull), "");
		if (bGifMwSaved)
			logln_file_generated("GIF", file_lookup(sGifMwFull), "");
		if (bGifGerSaved)
			logln_file_generated("GIF", file_lookup(sGifGerFull), "");
		if (bGifEngSaved)
			logln_file_generated("GIF", file_lookup(sGifEngFull), "");
		if (bBmpFoSaved)
			logln_file_generated("BMP", file_lookup(sBmpFoFull), "");
		if (bBmpFcSaved)
			logln_file_generated("BMP", file_lookup(sBmpFcFull), "");
		if (bBmpMwSaved)
			logln_file_generated("BMP", file_lookup(sBmpMwFull), "");
		if (bImgFoSaved)
			logln_file_generated("IMG", file_lookup(sImgFoFull), "");
		if (bImgFcSaved)
			logln_file_generated("IMG", file_lookup(sImgFcFull), "");
		if (bImgMwSaved)
			logln_file_generated("IMG", file_lookup(sImgMwFull), "");
		if (bEpsMwSaved)
			logln_file_generated("EPS", file_lookup(sEpsMwFull), "");
		if (bPngMwSaved)
			logln_file_generated("PNG", file_lookup(sPngMwFull), "");
		if (bCmdSaved)
			logln_file_generated("Pure C command file", file_lookup(sCmdfull), "");
		if (bHpjSaved)
			logln_file_generated("WinHelp project", file_lookup(sHpjfull), "");
		if (bCntSaved)
			logln_file_generated("WinHelp4 contents", file_lookup(sCntfull), "");
		if (bMapSavedC)
			logln_file_generated("WinHelp map for C", sMapNoSuff, ".hpc");
		if (bMapSavedPas)
			logln_file_generated("WinHelp map for Pascal", sMapNoSuff, ".hpp");
		if (bMapSavedVB)
			logln_file_generated("WinHelp map for Visual Basic", sMapNoSuff, ".hpb");
		if (bMapSavedGFA)
			logln_file_generated("WinHelp map for GFA Basic", sMapNoSuff, ".hpg");
		if (bHhpSaved)
			logln_file_generated("HTML Help project", file_lookup(sHhpfull), "");
		if (bHhcSaved)
			logln_file_generated("HTML Help contents", file_lookup(sHhcfull), "");
		if (bHhkSaved)
			logln_file_generated("HTML Help index", file_lookup(sHhkfull), "");
		if (bHypSaved)
			logln_file_generated("Hyphen file", file_lookup(sHypfull), "");
		if (bIdxSaved)
			logln_file_generated("Index file", file_lookup(sIdxfull), "");
		if (bTreeSaved)
			logln_file_generated("Tree file", file_lookup(sTreefull), "");
		if (bUPRSaved)
			logln_file_generated("Project file", file_lookup(sUPRfull), "");

		if (outfile.full[0] != EOS)
		{
			if (bBreakHappened)
			{
				logln_interrupted();
			} else if (!bTestmode)
			{
				logln_file_generated("Output", outfile.full, "");
			}
		}

		if (bFatalErrorDetected)
		{
			logln("UDO stopped because of fatal error(s)");
		}

	}

	print_results();

	/* Hyphenfile sortieren und Dupes entfernen */
	if (!bNoHypfile && bDocSortHyphenFile)
	{
		sort_hypfile(file_lookup(sHypfull));
	}

	udo_cleanup();

	return ret;
}





/*******************************************************************************
*
*  passU():
*     make UDO source text from UDO source text
*
*  Notes:
*     Dabei Include-Dateien in die neue Datei einbinden.
*
*     Die normalen Routinen koennen dafuer nicht benutzt werden, da ueberall 
*     spezielle Ausgaben erfolgen und If-Strukturen auch beruecksichtigt wuerden.
*
*     Es werden keine Indexfiles, Hyphenfiles erzeugt, jedoch Logfile und Treefile.
*
*  Return:
*      TRUE: everything worked fine
*     FALSE: some error occured
*
******************************************|************************************/

LOCAL _BOOL passU(const char *datei)
{
	MYTEXTFILE *file;
	char zeile[LINELEN];
	char zeileBak[LINELEN];
	char tmp_datei[MYFILE_FULL_LEN];
	size_t len;
	_BOOL inc_done;
	static char const orgBeg[] = "##### start of ";
	static char const orgEnd[] = "##### end of ";

	strcpy(tmp_datei, datei);

	file = myTextOpen(tmp_datei);

	if (file == NULL && iFilesOpened > 0)
	{
		build_include_filename(tmp_datei, file_lookup(uiFiles[iFilesOpened - 1].loc.id), ".ui");
		file = myTextOpen(tmp_datei);
	}

	if (file == NULL)
	{
		build_include_filename(tmp_datei, infile.full, ".ui");
		file = myTextOpen(tmp_datei);
	}

	if (file == NULL)
	{
		error_open_pass2(datei);
		bErrorDetected = TRUE;
		return FALSE;
	}

	if (push_file_stack(tmp_datei, file) == FALSE)
	{
		myTextClose(file);
		return FALSE;
	}

	if (bVerbose)
	{
		show_status_udo2udo(lPass2Lines, tmp_datei);
	}

	while (!bBreakHappened && !bBreakInside && !bFatalErrorDetected && myTextGetline(zeile, LINELEN, file))
	{
		uiFiles[iFilesOpened - 1].loc.line += 1 + uiMultiLines;
		uiCurrFileLine = uiFiles[iFilesOpened - 1].loc.line;
		lPass2Lines++;

		if (break_action())
		{
			pop_file_stack();
			return FALSE;
		}

		/* remove all line feed and whitespace characters at the end of line */
		len = strlen(zeile);
		while (len > 0 && (((_UBYTE) zeile[len - 1]) <= 32))
		{
			zeile[len - 1] = EOS;
			len--;
		}

		/* copy the line to be output later */
		strcpy(zeileBak, zeile);

		token_reset();

		/* Spezielle (verbatim, raw, table sourcecode) Umgebungen testen. */
		/* Gesucht wird nur nach !begin... bzw !end... */
		if (zeile[0] != '#')
		{
			pass2_check_environments(zeile);
		}

		replace_defines(zeile);
		str2tok(zeile);

		inc_done = FALSE;
		if (pflag[PASSU].env == ENV_NONE)
		{
			replace_defines(zeile);
			if (!inc_done && strcmp(token[0], "!include") == 0)
			{
				inc_done = TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include();
				voutlnf("%s%s", orgEnd, zeile);
			}

			if (!inc_done && strcmp(token[0], "!vinclude") == 0)
			{
				inc_done = TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_verbatim();
				voutlnf("%s%s", orgEnd, zeile);
			}

			if (!inc_done && strcmp(token[0], "!pinclude") == 0)
			{
				inc_done = TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_preformatted();
				voutlnf("%s%s", orgEnd, zeile);
			}

			if (!inc_done && strcmp(token[0], "!rinclude") == 0)
			{
				inc_done = TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_raw();
				voutlnf("%s%s", orgEnd, zeile);
			}

			if (!inc_done && strcmp(token[0], "!sinclude") == 0)
			{
				inc_done = TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_src();
				voutlnf("%s%s", orgEnd, zeile);
			}

			if (!inc_done && strcmp(token[0], "!cinclude") == 0)
			{
				inc_done = TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_comment();
				voutlnf("%s%s", orgEnd, zeile);
			}

			if (!inc_done && strcmp(token[0], "!ldinclude") == 0)
			{
				inc_done = TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_include_linedraw();
				voutlnf("%s%s", orgEnd, zeile);
			}

			if (!inc_done && strcmp(token[0], "!input") == 0)
			{
				inc_done = TRUE;
				voutlnf("%s%s", orgBeg, zeile);
				c_input();
				voutlnf("%s%s", orgEnd, zeile);
			}
		}

		if (!inc_done)
		{
			outln(zeileBak);
		}
	}

	pop_file_stack();

	multitasking_interrupt();

	return !bFatalErrorDetected;
}





/*******************************************************************************
*
*  init_vars_texinfo():
*     init TeX info variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_texinfo(void)
{
	int i;

	if (desttype == TOINF)
	{
		no_umlaute = TRUE;
		no_numbers = TRUE;
		for (i = TOC_NODE1; i < TOC_MAXDEPTH - 1; i++)
		{
			use_auto_subtocs[i] = TRUE;
			subtocs_depth[i] = 1;
		}
	}
}





/*******************************************************************************
*
*  init_vars_nroff():
*     init Nroff variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_nroff(void)
{
	if (desttype == TONRO)
	{
		no_umlaute = TRUE;
		no_numbers = TRUE;
	}
}





/*******************************************************************************
*
*  init_vars_sourcecode():
*     init Sourcecode variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_sourcecode(void)
{
	sSrcRemOn[0] = EOS;
	sSrcRemOff[0] = EOS;

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
}





/*******************************************************************************
*
*  init_vars_stg():
*     init ST-Guide variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_stg(void)
{
	if (desttype == TOSTG)
	{
#if 0
		/* dont change here; !parwidth sets zDocParwidth
		   only during pass1(), and this function gets
		   called in pass2() too */
		zDocParwidth = 75;
#endif
		strcpy(sDocImgSuffix, ".img");
	}
}


/*******************************************************************************
*
*  init_vars_tex():
*     init TeX variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_tex(void)
{
	if (desttype == TOTEX)
	{
		switch (iTexVersion)
		{
		case TEX_LINDNER:
		case TEX_STRUNK:
			strcpy(sDocImgSuffix, ".img");
			break;
		case TEX_EMTEX:
			strcpy(sDocImgSuffix, ".msp");
			break;
		case TEX_MIKTEX:
			strcpy(sDocImgSuffix, ".eps");
			break;
		case TEX_TETEX:
			strcpy(sDocImgSuffix, ".eps");
			break;
		}
	}
}





/*******************************************************************************
*
*  init_vars_htmlhelp():
*     init HTML-Help variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_htmlhelp(void)
{
	if (desttype == TOMHH)
	{
		no_headlines = TRUE;
		no_bottomlines = TRUE;
		no_footers = TRUE;
		strcpy(sDocImgSuffix, ".gif");
	}
}





/*******************************************************************************
*
*  init_vars_lyx():
*     init LyX variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_lyx(void)
{
	if (desttype == TOLYX)
	{
		strcpy(sDocImgSuffix, ".eps");
	}
}





/*******************************************************************************
*
*  init_vars_ipf():
*     init IPF variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_ipf(void)
{
	if (desttype == TOIPF)
	{
		strcpy(sDocImgSuffix, ".bmp");
	}
}


/*******************************************************************************
*
*  init_vars_pdf():
*     init PDF (?) variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_pdf(void)
{
	if (desttype == TOPDL)
	{
		bTex2e = TRUE;
		strcpy(sDocImgSuffix, ".png");
	}
}





/*******************************************************************************
*
*  init_vars_win():
*     init Winhelp variables
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_win(void)
{
	if (desttype == TOWIN || desttype == TOWH4 || desttype == TORTF)
	{
		strcpy(sDocImgSuffix, ".bmp");
	}
}


LOCAL void init_module_udo(void)
{
	/* --- force format requirements --- */

	switch (desttype)
	{
	case TOSTG:
	case TOPCH:
		if (iEncodingTarget == CODE_DEFAULT)
			set_encoding_target(CODE_TOS);
		break;

	case TOAMG:
	case TOWIN:
	default:
		if (iEncodingTarget == CODE_DEFAULT)
			set_encoding_target(CODE_CP1252);
		break;
	}
}


LOCAL void exit_module_udo(void)
{
	IDXLIST *idx,
	*idx_next;

	for (idx = idxlist; idx != NULL; idx = idx_next)
	{
		idx_next = idx->next;
		free(idx);
	}
}




/*******************************************************************************
*
*  init_vars_spec():
*     init specific variables
*
*  Notes:
*     <desttype> has to be valid when this function is called!
*
*     The functions may not set values or variables which might be changed by
*     pass1() or the read data become invalid!
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_vars_spec(void)
{
	init_vars_nroff();
	init_vars_texinfo();
	init_vars_tex();
	init_vars_sourcecode();
	init_vars_htmlhelp();
	init_vars_stg();
	init_vars_pdf();
	init_vars_win();
	init_vars_lyx();
	init_vars_ipf();
}





/*******************************************************************************
*
*  init_modules():
*     initialize other modules
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_modules(void)
{
	init_module_udo();
	init_module_about();				/* Werbeseite */
	init_module_chars();				/* Zeichenumwandlungen */
	init_module_env();					/* Umgebungen */
	init_module_img();					/* Bilder */
	init_module_msg();					/* Fehlermeldungen */
	init_module_par();					/* Parameter */
	init_module_sty();					/* Stile etc. */
	init_module_tab();					/* Tabellensatz */
	init_module_toc();					/* Inhaltsverzeichnis(se) */
	init_module_toc_html();
	init_module_tp();					/* Titelseite */

	init_vars_spec();
}





/*******************************************************************************
*
*  exit_modules():
*     exit various modules
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void exit_modules(void)
{
	exit_module_toc();
	exit_module_toc_html();
	exit_module_par();
	exit_module_tp();
	exit_udosymbol();
	exit_module_udo();
}


void exit_udo_vars(void)
{
	exit_module_files();
}




/*******************************************************************************
*
*  check_modules_pass1():
*     starts check functions of modules for pass 1
*
*  Return:
*      TRUE: success
*     FALSE: error
*
******************************************|************************************/

LOCAL _BOOL check_modules_pass1(void)
{
	if (!check_module_toc_pass1())
		return FALSE;

	return TRUE;
}





/*******************************************************************************
*
*  check_modules_pass1():
*     starts check functions of modules for pass 1
*
*  Return:
*      TRUE: success
*     FALSE: error
*
******************************************|************************************/

LOCAL _BOOL check_modules_pass2(void)
{
	if (!check_module_toc_pass2())
		return FALSE;

	return TRUE;
}





/*******************************************************************************
*
*  getMonth():
*     extract month int value from date string in __DATE__ format
*
*  Return:
*     month int value
*
******************************************|************************************/

LOCAL int getMonth(const char *date_string)
{
	if (my_strnicmp(date_string, "Jan", 3) == 0)
		return 1;
	if (my_strnicmp(date_string, "Feb", 3) == 0)
		return 2;
	if (my_strnicmp(date_string, "Mar", 3) == 0)
		return 3;
	if (my_strnicmp(date_string, "Apr", 3) == 0)
		return 4;
	if (my_strnicmp(date_string, "May", 3) == 0)
		return 5;
	if (my_strnicmp(date_string, "Jun", 3) == 0)
		return 6;
	if (my_strnicmp(date_string, "Jul", 3) == 0)
		return 7;
	if (my_strnicmp(date_string, "Aug", 3) == 0)
		return 8;
	if (my_strnicmp(date_string, "Sep", 3) == 0)
		return 9;
	if (my_strnicmp(date_string, "Oct", 3) == 0)
		return 10;
	if (my_strnicmp(date_string, "Nov", 3) == 0)
		return 11;
	if (my_strnicmp(date_string, "Dec", 3) == 0)
		return 12;
	return 0;
}





/*******************************************************************************
*
*  init_udo_vars():
*     initialize (many!) variables
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_udo_vars(void)
{
	register int i;

	init_module_files();

	/* -------------------------------------------------- */
	/* UDOs Kontrollvariablen initialisieren              */
	/* -------------------------------------------------- */

	bNopDetected = FALSE;

	lPass1Lines = 0;
	lPass2Lines = 0;

	footnote_cnt = 0;
	global_footnote_cnt = 0;
	footnotes = NULL;

	bInsideAppendix = FALSE;
	bInsideDocument = FALSE;

	bDescDDOpen = FALSE;
	bParagraphOpen = FALSE;

	out_lf_needed = FALSE;

	bCmdSaved = FALSE;
	bHpjSaved = FALSE;
	bCntSaved = FALSE;
	bHhpSaved = FALSE;
	bHhcSaved = FALSE;
	bHhkSaved = FALSE;
	bHypSaved = FALSE;
	bUPRSaved = FALSE;
	bMapSavedC = FALSE;
	bMapSavedPas = FALSE;
	bMapSavedVB = FALSE;
	bMapSavedGFA = FALSE;

	clear_file_stack();

	silben_counter = 0;
	for (i = 0; i < MAXSILBEN; i++)
		silbe[i][0] = EOS;

	memset(&styleflag, FALSE, sizeof(STYLEFLAG));

	memset(&pflag[PASS1], 0, sizeof(PASSFLAGS));
	memset(&pflag[PASS2], 0, sizeof(PASSFLAGS));

	/* clear all token buffers */
	token_counter = MAX_TOKENS - 1;
	token_reset();

	/* clear all symbols */
	init_udosymbol();


	/*   -------------------------------------------------- */
	/*   Dokumentvariablen und -flags initialisieren        */
	/*   -------------------------------------------------- */

	for (i = 0; i < (int) MAXSWITCH; i++)
		*(udoswitch[i].flag) = FALSE;
	no_auto_toptocs_icons = FALSE;

	bDocSortHyphenFile = FALSE;
	zDocParwidth = 70;
	bDocTabwidth = 8;
	iDocVerbatimSize = VERB_NORMAL;
	iDocLinedrawSize = VERB_NORMAL;

	for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
		html_merge_node[i] = FALSE;
	for (i = TOC_NODE1; i < TOC_MAXDEPTH - 1; i++)
		use_auto_subtocs[i] = FALSE;
	html_no_xlist = FALSE;
	html_ignore_8bit = FALSE;
	html_navigation_line = FALSE;
	html_navigation_image = FALSE;
	html_modern_layout = FALSE;
	html_modern_alignment = ALIGN_CENT;
	html_frames_layout = FALSE;
	html_frames_noresize = FALSE;
	html_frames_noborder = FALSE;
	html_frames_noscroll = FALSE;
	html_frames_alignment = ALIGN_CENT;
	html_nodesize = 1;
	html_quotes = QUOTES_TAGS;
	html_button_alignment = ALIGN_CENT;
	html_use_folders = FALSE;
	html_transparent_buttons = FALSE;
	html_use_hyphenation = FALSE;
	set_html_doctype(HTML_TRANS);
	html_header_date = FALSE;
	html_header_date_zone[0] = EOS;
	html_header_links = FALSE;

	sDocHtmlBackpage[0] = EOS;
	sDocHtmlPropfontName[0] = EOS;
	sDocHtmlPropfontSize[0] = EOS;
	sDocHtmlSwitchLanguage[0] = EOS;
	iDocHtmlSwitchLanguage = -1;
	strcpy(sDocHtmlIndexudo, "indexudo");

	image_alignment = ALIGN_LEFT;
	table_alignment = ALIGN_CENT;
	strcpy(sDocImgSuffix, ".gif");

	sDocBackImage = 0;
	sDocScript.count = 0;
	sDocStyle.count = 0;
	sDocFavIcon = 0;
	sDocBackColor.rgb.set = FALSE;
	sDocTextColor.rgb.set = FALSE;
	sDocLinkColor.rgb.set = FALSE;
	sDocAlinkColor.rgb.set = FALSE;
	sDocVlinkColor.rgb.set = FALSE;
	sDocVerbatimBackColor.rgb.set = FALSE;
	sDocRawHeaderFilename = 0;
	sDocRawFooterFilename = 0;
	sDocWinPrefixID[0] = EOS;
	sDocWinButtonName[0][0] = EOS;
	sDocWinButtonText[0][0] = EOS;
	iNumWinButtons = 0;
	sCounterCommand = 0;

	iTexVersion = TEX_NONE;
	iTexDPI = 100;
	cTexVerb = VERB_C;
	bTex2e = TRUE;
	bCalledIndex = TRUE;
	iDrcFlags = 0;

	iManPageLines = 0;
	iManPageLength = 0;
	iManPagePages = 0;
	sDocManType[0] = EOS;

	bDocSloppy = FALSE;
	bDocAutorefOff = FALSE;
	bDocAutorefItemsOff = FALSE;
	bStgLimage = TRUE;

	bDocInlineBitmaps = FALSE;
	iDocCharwidth = 150;
	bDocHighCompression = FALSE;
	bDocMediumCompression = FALSE;
	bDocNoTables = FALSE;
	bDocRtfKeepTablesOn = FALSE;
	bDocWinOldKeywords = FALSE;

	sDocPropfont[0] = EOS;
	sDocMonofont[0] = EOS;
	sDocPropfontSize[0] = EOS;
	sDocMonofontSize[0] = EOS;

	/* set_mainlayout(); gehoert nach init_module_tp() und wird jetzt auch dort erledigt */

	justify_from_right = FALSE;

	uses_udolink = FALSE;
	uses_toplink = FALSE;

	/* ---------------------------------------------------- */
	/* Variablen fuer Compile-Zeit und Datum initialisieren */
	/* ---------------------------------------------------- */

	if (compile_date[0] == '\0')
	{
		char date[] = __DATE__;

		if (date[4] == ' ')
			date[4] = '0';

		sprintf(compile_date, "%c%c%c%c-%02d-%c%c", date[7], date[8], date[9], date[10], getMonth(date), date[4],
				date[5]);
	}
	if (compile_time[0] == '\0')
	{
		strcpy(compile_time, __TIME__);
	}
}





/*******************************************************************************
*
*  logfile_adjust():
*     adjust file names and suffixes
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void logfile_adjust(void)
{
	char suff[MYFILE_SUFF_LEN + 1];
	char filename[MYFILE_FULL_LEN + 1];

	switch (desttype)
	{
	case TONRO:
		strcpy(suff, ".ul1");
		break;
	case TOWH4:
		strcpy(suff, ".ul4");
		break;
	case TOASC:
		strcpy(suff, ".ula");
		break;
	case TOSRC:
		strcpy(suff, ".ulc");
		break;
	case TODRC:
		strcpy(suff, ".uld");
		break;
	case TOPDL:
		strcpy(suff, ".ulf");
		break;
	case TOHPH:
		strcpy(suff, ".ulg");
		break;
	case TOAMG:						/* Dupe! */
		strcpy(suff, ".ulg");
		break;
	case TOHTM:
		strcpy(suff, ".ulh");
		break;
	case TOHAH:						/* Dupe! */
		strcpy(suff, ".ulh");
		break;
	case TOMHH:						/* Dupe! */
		strcpy(suff, ".ulh");
		break;
	case TOINF:
		strcpy(suff, ".uli");
		break;
	case TOIPF:						/* Dupe! */
		strcpy(suff, ".uli");
		break;
	case TOLYX:
		strcpy(suff, ".ull");
		break;
	case TOMAN:
		strcpy(suff, ".ulm");
		break;
	case TOPCH:
		strcpy(suff, ".ulp");
		break;
	case TOSRP:						/* Dupe! */
		strcpy(suff, ".ulp");
		break;
	case TOKPS:						/* Dupe! */
		strcpy(suff, ".ulp");
		break;
	case TOAQV:
		strcpy(suff, ".ulq");
		break;
	case TORTF:
		strcpy(suff, ".ulr");
		break;
	case TOSTG:
		strcpy(suff, ".uls");
		break;
	case TOTEX:
		strcpy(suff, ".ult");
		break;
	case TOUDO:
		strcpy(suff, ".ulu");
		break;
	case TOTVH:
		strcpy(suff, ".ulv");
		break;
	case TOWIN:
		strcpy(suff, ".ulw");
		break;
	case TOLDS:
		strcpy(suff, ".ulx");
		break;
	default:
		strcpy(suff, ".log");
		break;
	}

	sprintf(filename, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, suff);
	sLogfull = file_listadd(filename);
}





/*******************************************************************************
*
*  dest_special_adjust():
*     adjust special stuff
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void dest_special_adjust(void)
{
	char filename[MYFILE_FULL_LEN + 1];

	/* -------------------------------------------------- */
	/* Endung und Dateinamen des Logfiles setzen          */
	/* -------------------------------------------------- */
	logfile_adjust();

	/* -------------------------------------------------- */
	/* Endung des Treefiles setzen (wie logfile, nur 't') */
	/* -------------------------------------------------- */
	strcpy(filename, file_lookup(sLogfull));
	filename[strlen(filename) - 2] = 't';
	sTreefull = file_listadd(filename);

	/* -------------------------------------------------- */
	/* Endung des Indexfiles setzen (wie oben, nur 'x')   */
	/* -------------------------------------------------- */
	strcpy(filename, file_lookup(sLogfull));
	filename[strlen(filename) - 2] = 'x';
	sIdxfull = file_listadd(filename);

	/* ------------------------------------------------- */
	/* Endung des Hypfiles setzen (wie logfile, nur 'h') */
	/* ------------------------------------------------- */
	sHypfull = 0;
	switch (desttype)
	{
	case TOASC:
	case TODRC:
	case TOMAN:
	case TOSTG:
	case TOAMG:
	case TOPCH:
		strcpy(filename, file_lookup(sLogfull));
		filename[strlen(filename) - 2] = 'h';
		sHypfull = file_listadd(filename);
		break;
	}

	/* -------------------------------------------------- */
	/* Restliche Dateinamen setzen                        */
	/* -------------------------------------------------- */
	sprintf(filename, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".cmd");
	sCmdfull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, outfile.name);
	sMapNoSuff = file_lookup(file_listadd(filename));
	sprintf(filename, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".hpj");
	sHpjfull = file_listadd(filename);
	sprintf(filename, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".cnt");
	sCntfull = file_listadd(filename);
	sprintf(filename, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".hhp");
	sHhpfull = file_listadd(filename);
	sprintf(filename, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".hhc");
	sHhcfull = file_listadd(filename);
	sprintf(filename, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".hhk");
	sHhkfull = file_listadd(filename);
	sprintf(filename, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, ".upr");
	sUPRfull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_HM_NAME);
	sGifHmFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_UP_NAME);
	sGifUpFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_LF_NAME);
	sGifLfFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_RG_NAME);
	sGifRgFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_NOHM_NAME);
	sGifNoHmFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_NOUP_NAME);
	sGifNoUpFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_NOLF_NAME);
	sGifNoLfFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_NORG_NAME);
	sGifNoRgFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_TP_NAME);
	sGifTpFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_FO_NAME);
	sGifFoFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_FC_NAME);
	sGifFcFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_FS_NAME);
	sGifFsFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_MW_NAME);
	sGifMwFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_GER_NAME);
	sGifGerFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, GIF_ENG_NAME);
	sGifEngFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, BMP_FO_NAME);
	sBmpFoFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, BMP_FC_NAME);
	sBmpFcFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, BMP_MW_NAME);
	sBmpMwFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, IMG_FO_NAME);
	sImgFoFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, IMG_FC_NAME);
	sImgFcFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, IMG_MW_NAME);
	sImgMwFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, EPS_MW_NAME);
	sEpsMwFull = file_listadd(filename);
	sprintf(filename, "%s%s%s", outfile.driv, outfile.path, PNG_MW_NAME);
	sPngMwFull = file_listadd(filename);
}





/*******************************************************************************
*
*  dest_special_adjust():
*     adjust special stuff
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void dest_adjust(void)
{
	char html_suff[MYFILE_SUFF_LEN + 1];
	char texi_suff[MYFILE_SUFF_LEN + 1];
	char sgml_suff[MYFILE_SUFF_LEN + 1];
	char guide_suff[MYFILE_SUFF_LEN + 1];

#if USE_LONG_FILENAMES
	if (!bForceShort)
	{
		strcpy(html_suff, ".html");
		strcpy(texi_suff, ".texi");
		strcpy(sgml_suff, ".sgml");
		strcpy(guide_suff, ".guide");
	} else
	{
		strcpy(html_suff, ".htm");
		strcpy(texi_suff, ".tex");
		strcpy(sgml_suff, ".sgm");
		strcpy(guide_suff, ".gui");
	}
#else
	if (bForceLong)
	{
		strcpy(html_suff, ".html");
		strcpy(texi_suff, ".texi");
		strcpy(sgml_suff, ".sgml");
		strcpy(guide_suff, ".guide");
	} else
	{
		strcpy(html_suff, ".htm");
		strcpy(texi_suff, ".tex");
		strcpy(sgml_suff, ".sgm");
		strcpy(guide_suff, ".gui");
	}
#endif

	if (config.bDestAdjustAll)
	{
		strcpy(outfile.driv, infile.driv);
		strcpy(outfile.path, infile.path);
	}

	if (!config.bDestAdjustSuff)
	{
		strcpy(outfile.name, infile.name);
	}

	switch (desttype)
	{
	case TOASC:
		strcpy(outfile.suff, ".txt");
		break;
	case TODRC:
		strcpy(outfile.suff, ".drc");
		break;
	case TOMAN:
		strcpy(outfile.suff, ".man");
		break;
	case TONRO:
		strcpy(outfile.suff, ".1");
		break;
	case TOSTG:
		strcpy(outfile.suff, ".stg");
		break;
	case TOAMG:
		strcpy(outfile.suff, guide_suff);
		break;
	case TOTEX:
		strcpy(outfile.suff, ".tex");
		break;
	case TOPDL:
		strcpy(outfile.suff, ".tex");
		break;
	case TOINF:
		strcpy(outfile.suff, texi_suff);
		break;
	case TOIPF:
		strcpy(outfile.suff, ".ipf");
		break;
	case TORTF:
		strcpy(outfile.suff, ".rtf");
		break;
	case TOAQV:
		strcpy(outfile.suff, ".rtf");
		break;
	case TOWIN:
		strcpy(outfile.suff, ".rtf");
		break;
	case TOWH4:
		strcpy(outfile.suff, ".rtf");
		break;
	case TOPCH:
		strcpy(outfile.suff, ".scr");
		break;
	case TOTVH:
		strcpy(outfile.suff, ".txt");
		break;
	case TOHAH:
		strcpy(outfile.suff, html_suff);
		break;
	case TOHTM:
		strcpy(outfile.suff, html_suff);
		break;
	case TOMHH:
		strcpy(outfile.suff, html_suff);
		break;
	case TOLDS:
		strcpy(outfile.suff, sgml_suff);
		break;
	case TOHPH:
		strcpy(outfile.suff, sgml_suff);
		break;
	case TOLYX:
		strcpy(outfile.suff, ".lyx");
		break;
	case TOSRC:
		strcpy(outfile.suff, ".c");
		break;
	case TOSRP:
		strcpy(outfile.suff, ".pas");
		break;
	case TOUDO:
		strcpy(outfile.suff, ".udo");
		break;
	case TOKPS:
		strcpy(outfile.suff, ".ps");
		break;
	default:
		outfile.suff[0] = EOS;
		break;
	}

	if (config.bDestLowerFile)
	{
		my_strlwr(outfile.name);
	}
	if (config.bDestLowerPath)
	{
		my_strlwr(outfile.path);
	}

	sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);

	dest_special_adjust();
}
