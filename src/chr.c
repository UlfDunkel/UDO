/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr.c
*  Symbol prefix: chr
*
*  Description  : This module contains routines which convert strings between all
*                 supported encodings. There are also functions which replace characters.
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
*  Co-Authors   : Ulf Dunkel (fd), Gerhard Stoll (ggs)
*  Write access : fd, ggs
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
*    ggs Dec 12: output for ST-Guide and PureC Help always uses CODE_TOS
*  2010:
*    fd  Jan 26: file reformatted and tidied up
*    fd  Feb 16: recode(): forces target encoding for several output formats
*    fd  Feb 17: - CODE_437_lig[], sort_CODE_437[] + CODE_850_lig[], sort_CODE_850[] added
*                - CODE_HP_lig[] + sort_CODE_HP[] added
*                - CODE_NEXT_lig[] + sort_CODE_NEXT[] added
*                - various chartab[] merged here
*                - cp850iso() and stuff removed
*                - cp437iso() and stuff removed
*                - hp82iso() and stuff removed
*                - iso2tos() and stuff removed
*                - mac2iso() and stuff removed
*                - next2iso() and stuff removed
*                - tos2iso() and stuff removed
*                - utf82iso() and stuff removed
*                - iso2sys(), iso2system() and stuff removed
*                - section2iso() removed (unused)
*                - ansi2dos() removed
*                - win2sys() rewritten and generalized as recode_chrtab()
*                - html2sys() merged into recode_chrtab()
*                - umlaute2sys() merged into recode_chrtab()
*                - auto_quote_chars() adjusted
*                - recode(): UTF-8 output enabled
*                - recode(): UTF-8 input enabled
*                - bstr_to_utf8() debugged
*    fd  Feb 18: - CODE_LAT2
*    fd  Feb 19: - CODE_CP1257
*                - unicode2chars()
*                - uni2ascii() rewritten, using the generalized table u_CODE_UDO
*                - uni2misc() supports !html_ignore_8bit
*                - recode() supports !html_ignore_8bit
*                - uni2ascii() renamed -> recode_udo()
*                - recode() debugged for UTF-8 -> 1-byte encoding
*                - recode(): U_ReplacementCharacter or '*' for unsupported chars
*    fd  Feb 20: - CODE_CP1251
*                - utf8_to_uchar()
*    fd  Feb 22: - VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*                - CODE_CP1253
*    fd  Feb 23: - CODE_MAC_CE
*                - CODE_LAT1 -> CODE_CP1252
*                - CODE_LAT2 -> CODE_LATIN2
*                - CODE_LATIN1
*                - bstr_to_utf8() adjusted, using ^string instead of local string
*                - adjustments from Xcode's complaints for strupr()
*    fd  Feb 24: - CODE_CP1254 (Turkish)
*                - CODE_CP1255 (Hebrew)
*                - CODE_CP1256 (Arabic)
*                - CODE_CP1258 (Vietnamese)
*                - new: chr_codepage()
*                - new: chr_codepage_name()
*                - new: chr_sort_codepage()
*                - new: chr_usort_codepage()
*                - new: chr_ligatures()
*                - unicode2char() debugged
*    fd  Mar 05: - CODE_LATIN3
*                - CODE_LATIN4
*                - CODE_CYRILLIC
*                - CODE_ARABIC
*                - CODE_GREEK
*                - CODE_HEBREW
*    fd  Mar 08: - CODE_TURKISH
*                - CODE_NORDIC
*                - CODE_THAI
*                - CODE_BALTIC
*                - CODE_CELTIC
*                - CODE_LATIN9
*                - CODE_LATIN10
*    fd  Mar 12: adjustments for the Linux ggc
*    fd  May 18: - auto_quote_chars() cancels on UTF-8
*                - recode() simplified
*                - new: chr_codepage_charset_name()
*    fd  May 19: - auto_quote_chars() debugged
*                - (!deg) is replaced by localized string lang.degree, if not supported
*    fd  May 21: new: label* | l*  (#90)
*  2011:
*    fd  Jan 31: - auto_quote_chars(): speed optimized for HTML output formats
*                - recode_chrtab(): no longer recodes  on Unicode targets [#94 fixed]
*                - convert_sz():    no longer converts on Unicode targets
*    fd  Feb 18: - auto_quote_chars() supports Unicode for RTF [#95 fixed]
*                - new: QUOTECOMMAND.skip_brackets [#97 fixed]
*    fd  Feb 19: - auto_quote_chars(): gcc (at least under Linux) doesn't support itoa()
*                - auto_quote_chars(): TeX writes unquoted UTF-8 chars, if required [#96 fixed]
*                - auto_quote_chars(): RTF now supports UTF-8 chars > 32768 (up to 65535)
*  2012:
*    fd  Apr 24: !begin_enumerate added to quotecommand[] 
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

#include "udoport.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "udointl.h"
#include "msg.h"
#include "str.h"
#include "sty.h"
#include "udo.h"
#include "chr_all.h"
#include "chr_ttf.h"
#include "udomem.h"
#include "lang.h"

#include "export.h"
#include "chr.h"

#include "u_dos.h"
#include "u_hp.h"
#include "u_iso.h"
#include "u_mac.h"
#include "u_mswin.h"
#include "u_next.h"
#include "u_tos.h"
#include "u_utf.h"

#include "u_udo.h"						/* u_CODE_UDO[] */


/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _quotecommand
{
	const char *cmd;					/* name of command */
	size_t cmdlen;						/* Laenge des Kommandos (need speed ;-)) */
	const char *abb;					/* Kommandoabkuerzung */
	size_t abblen;						/* Laenge der Abkuerzung */
	_BOOL skip_brackets;				/* don't quote command content in [] */
} QUOTECOMMAND;


typedef struct _chartable
{
	_UWORD uname;						/* Unicode name for character */
	const char *ascii;					/* ASCII (7bit!) representation, if any */
	const char *rtf;					/* Used for WinHelp, RTF, etc. */
	const char *tex;					/* TeX */
	const char *html;					/* HTML */
	const char *ps;						/* PostScript */
} CHARTABLE;






/*******************************************************************************
*
*     UNINITIALIZED VARIABLES
*
******************************************|************************************/

LOCAL _BOOL last_aqc_verb;





/* ############################################################
   #
   # Automatisches Quoten von kritischen Zeichen dort, wo kein
   # (!V)/(!v) benutzt wird und kein !tex, !=tex etc. am
   # Zeilenanfang steht.
   #
   ############################################################   */

/* Es wird zwar unten mit strncmp() getestet, ob das Kommando */
/* gequotet werden muss, allerdings muss nach dem Kommando */
/* Ein Leerzeichen oder ein Tab auftreten, damit die Abfrage */
/* TRUE liefert. Daher muessen hier sowohl !node als auch */
/* !node* angegeben werden! */

LOCAL const QUOTECOMMAND quotecommand[] = {
	{ "!node",                               5, "!n",            2, FALSE },
	{ "!subnode",                            8, "!sn",           3, FALSE },
	{ "!subsubnode",                        11, "!ssn",          4, FALSE },
	{ "!subsubsubnode",                     14, "!sssn",         5, FALSE },
	{ "!subsubsubsubnode",                  17, "!ssssn",        6, FALSE },
	{ "!subsubsubsubsubnode",               20, "!sssssn",       7, FALSE },
	{ "!subsubsubsubsubsubnode",            23, "!ssssssn",      8, FALSE },
	{ "!subsubsubsubsubsubsubnode",         26, "!sssssssn",     9, FALSE },
	{ "!subsubsubsubsubsubsubsubnode",      29, "!ssssssssn",   10, FALSE },
	{ "!pnode",                              6, "!p",            2, FALSE },
	{ "!psubnode",                           9, "!ps",           3, FALSE },
	{ "!psubsubnode",                       12, "!pss",          4, FALSE },
	{ "!psubsubsubnode",                    15, "!psss",         5, FALSE },
	{ "!psubsubsubsubnode",                 18, "!pssss",        6, FALSE },
	{ "!psubsubsubsubsubnode",              21, "!psssss",       7, FALSE },
	{ "!psubsubsubsubsubsubnode",           24, "!pssssss",      8, FALSE },
	{ "!psubsubsubsubsubsubsubnode",        27, "!psssssss",     9, FALSE },
	{ "!psubsubsubsubsubsubsubsubnode",     30, "!pssssssss",   10, FALSE },
	{ "!node*",                              6, "!n*",           3, FALSE },
	{ "!subnode*",                           9, "!sn*",          4, FALSE },
	{ "!subsubnode*",                       12, "!ssn*",         5, FALSE },
	{ "!subsubsubnode*",                    15, "!sssn*",        6, FALSE },
	{ "!subsubsubsubnode*",                 18, "!ssssn*",       7, FALSE },
	{ "!subsubsubsubsubnode*",              21, "!sssssn*",      9, FALSE },
	{ "!subsubsubsubsubsubnode*",           24, "!ssssssn*",     9, FALSE },
	{ "!subsubsubsubsubsubsubnode*",        27, "!sssssssn*",   10, FALSE },
	{ "!subsubsubsubsubsubsubsubnode*",     30, "!ssssssssn*",  11, FALSE },
	{ "!pnode*",                             7, "!p*",           3, FALSE },
	{ "!psubnode*",                         10, "!ps*",          4, FALSE },
	{ "!psubsubnode*",                      13, "!pss*",         5, FALSE },
	{ "!psubsubsubnode*",                   16, "!psss*",        6, FALSE },
	{ "!psubsubsubsubnode*",                19, "!pssss*",       7, FALSE },
	{ "!psubsubsubsubsubnode*",             22, "!psssss*",      8, FALSE },
	{ "!psubsubsubsubsubsubnode*",          25, "!pssssss*",     9, FALSE },
	{ "!psubsubsubsubsubsubsubnode*",       28, "!psssssss*",   10, FALSE },
	{ "!psubsubsubsubsubsubsubsubnode*",    31, "!pssssssss*",  11, FALSE },
	{ "!begin_node",                        11, "!bn",           3, FALSE },
	{ "!begin_pnode",                       12, "!bp",           3, FALSE },
	{ "!begin_node*",                       12, "!bn*",          4, FALSE },
	{ "!begin_pnode*",                      13, "!bp*",          4, FALSE },
	{ "!item",                               5, "!i",            2, FALSE },
	{ "!index",                              6, "!x",            2, FALSE },
	{ "!image",                              6, "",              0, FALSE },
	{ "!image*",                             7, "",              0, FALSE },
	{ "!table_caption",                     14, "",              0, FALSE },
	{ "!table_caption*",                    15, "",              0, FALSE },
	{ "!begin_xlist",                       12, "!bxl",          4, FALSE },	/* wegen des Inhalts der eckigen Klammern! */
	{ "!begin_blist",                       12, "!bbl",          4, FALSE },	/* Fehlen die hier, so bekommt c_begin_list */
	{ "!begin_ilist",                       12, "!bil",          4, FALSE },	/* einen String, der c_vars(), aber nicht */
	{ "!begin_tlist",                       12, "!btl",          4, FALSE },	/* auto_quote_chars() durchlaufen hat!!! */
	{ "!begin_enumerate",                   16, "!be",           3, FALSE },
	{ "!heading",                            8, "!h",            2, FALSE },
	{ "!subheading",                        11, "!sh",           3, FALSE },
	{ "!subsubheading",                     14, "!ssh",          4, FALSE },
	{ "!subsubsubheading",                  17, "!sssh",         5, FALSE },
	{ "!subsubsubsubheading",               20, "!ssssh",        6, FALSE },
	{ "!subsubsubsubsubheading",            23, "!sssssh",       7, FALSE },
	{ "!subsubsubsubsubsubheading",         26, "!ssssssh",      8, FALSE },
	{ "!subsubsubsubsubsubsubheading",      29, "!sssssssh",     9, FALSE },
	{ "!subsubsubsubsubsubsubsubheading",   32, "!ssssssssh",   10, FALSE },
	{ "!macro",                              6, "",              0, FALSE },
	{ "!hyphen",                             7, "",              0, FALSE },
	{ "!label",                              6, "!l",            2, FALSE },
	{ "!label*",                             7, "!l*",           3, FALSE },
	{ "!alias",                              6, "!a",            2, FALSE },
	{ "!docinfo",                            8, "",              0, TRUE }
};

#define MAXQUOTECMD ArraySize(quotecommand)




LOCAL CHARTABLE const chrtab[] =		/* in no particular order */
{
/*  Unicode name                          ASCII    Rtf                    TeX               HTML        PS         */
/* ------------------------------------------------------------------------------------------------------------- */
	{ U_GraveAccent,                      "`",     "`",                   "`",              "`", "" },	/* ` */

	{ U_EuroSign,                         "EUR",   "\\'80",               "\\euro{}",       "&#x20AC;", "\\244" },
	{ U_SingleLow9QuotationMark,          ",",     "\\'82",               "\\symbol{44}",   "&#x201A;", "\\202" },
	{ U_LatinSmallLetterScriptF,          "f",     "\\'83",               "$f$",            "&#x192;",  "\\203" },
	{ U_DoubleLow9QuotationMark,          "",      "\\'84",               "``",             "&#x201E;", "\\204" },
	{ U_HorizontalEllipsis,               "...",   "\\'85",               "\\ldots{}",      "&#x2026;", "\\205" },
	{ U_Dagger,                           "",      "\\'86",               "\\dag{}",        "&#x2020;", "\\206" },
	{ U_DoubleDagger,                     "",      "\\'87",               "$\\ddagger$",    "&#x2021;", "\\207" },
	{ U_ModifierLetterCircumflexAccent,   "^",     "\\'88",               "\\^{ }",         "&#x2c6;",  "^" },
	{ U_PerMilleSign,                     "0/00",  "\\'89",               "",               "&#x2030;", "\\211" },
	{ U_LatinCapitalLetterSWithCaron,     "S",     "\\'8A",               "\\v{S}",         "&#x160;",  "\\212" },
	{ U_LeftPointingSingleGuillemet,      "<",     "\\'8B",               "$<$",            "&#x2039;", "<" },
	{ U_LatinCapitalLigatureOE,           "OE",    "\\'8C",               "{\\OE}",         "&#x152;",  "\\214" },
	{ U_LatinCapitalLetterZWithCaron,     "Z",     "\\'8E",               "\\v{Z}",         "&#x17D;",  "\\231" },
	{ U_CombiningGraveAccent,             "`",     "\\'91",               "`",              "&#x300;",  "" },
	{ U_RightSingleQuotationMark,         "'",     "\\'92",               "'",              "&#x2019;", "\\222" },
	{ U_LeftDoubleQuotationMark,          "\"",    "\\'93",               "``",             "&#x201C;", "\\223" },
	{ U_RightDoubleQuotationMark,         "\"",    "\\'94",               "''",             "&#x201D;", "\\224" },
	{ U_Bullet,                           "*",     "\\'95",               "$\\bullet$",     "&#x2022;", "\\225" },
	{ U_BulletOperator,                   "*",     "\\'95",               "$\\bullet$",     "&#x2219;", "\\225" },
	{ U_FullBlock,                        "*",     "\\'95",               "$\\bullet$",     "&#x2588;", "" },
	{ U_EnDash,                           "--",    "\\'96",               "--",             "&#x2013;", "\\226" },
	{ U_EmDash,                           "---",   "\\'97",               "---",            "&#x2014;", "\\227" },
	{ U_SmallTilde,                       "~",     "\\'98",               "\\~{ }",         "~",        "" },	/* !~ */
	{ U_TradeMarkSign,                    "(TM)",  "\\'99",            "\\texttrademark{}", "&#x2122;", "\\231" },
	{ U_LatinSmallLetterSWithCaron,       "s",     "\\'9A",               "\\v{s}",         "&#x161;",  "" },
	{ U_LatinSmallLigatureOE,             "oe",    "\\'9C",               "{\\oe}",         "&#x153;",  "\\234" },
	{ U_LatinSmallLetterZWithCaron,       "z",     "\\'9E",               "\\v{z}",         "&#x17E;",  "\\236" },
	{ U_LatinCapitalLetterYWithDiaeresis, "Y",     "\\'9F",               "\\\"{Y}",        "&Yuml;",   "\\237" },
	{ U_NB_SP,                            " ",     "\\~",                 "~",              "&nbsp;",   "\\240" },
	{ U_InvertedExclamationMark,          "!",     "\\'A1",               "!`",             "&#161;",   "\\241" },
	{ U_CentSign,                         "ct",    "\\'A2",               "cent",           "&#162;",   "\\242" },
	{ U_PoundSign,                        "GBP",   "\\'A3",               "\\pounds{}",     "&#163;",   "\\243" },
	{ U_CurrencySign,                     "EUR",   "\\'A4",               "\\euro{}",       "&#164;",   "\\244" },	/* general-currency sign */
	{ U_YenSign,                          "JPY",   "\\'A5",               "yen",            "&#165;",   "\\245" },
	{ U_BrokenVerticalBar,                "|",     "\\'A6",               "$\\mid$",        "&#166;",   "\\246" },	/* broken-vertical-line */
	{ U_SectionSign,                      "",      "\\'A7",               "\\S{}",          "&sect;",   "\\247" },
	{ U_Diaeresis,                        "\"",    "\\'A8",               "\\\"{ }",        "&#168;",   "\\250" },
	{ U_CopyrightSign,                    "(C)",   "\\'A9",               "\\copyright{}",  "&copy;",   "\\251" },
	{ U_FeminineOrdinalIndicator,         "",      "\\'AA",               "\\b{a}",         "&#170;",   "\\252" },
	{ U_LeftPointingGuillemet,            "<<",    "\\'AB",               "\"<",            "&#171;",   "\\253" },
	{ U_NotSign,                          "",      "\\'AC",               "$\\neq$",        "&#172;",   "\\254" },
	{ U_SoftHyphen,                       "",      "\\-",                 "\\-",            "&#173;",   "\\255" },
	{ U_RegisteredSign,                   "(R)",   "\\'AE",           "\\textregistered{}", "&#174;",   "\\256" },
	{ U_Macron,                           "_",     "\\'AF",               "",               "&#175;",   "\\257" },
	{ U_DegreeSign,                       "",      "\\'B0",               "$^{o}$",         "&#176;",   "\\260" },
	{ U_PlusMinusSign,                    "+/-",   "\\'B1",               "$\\pm$",         "&#177;",   "\\261" },
	{ U_SuperscriptTwo,                   "2",     "\\'B2",               "$^2$",           "&#178;",   "\\262" },
	{ U_SuperscriptThree,                 "3",     "\\'B3",               "$^3$",           "&#179;",   "\\263" },
	{ U_AcuteAccent,                      "'",     "\\'B4",               "\\`{}",          "&#180;",   "\\264" },
	{ U_MicroSign,                        "",      "\\'B5",               "$\\mu$",         "&#181;",   "\\265" },
	{ U_ParagraphSign,                    "Par.",  "\\'B6",               "\\P{}",          "&#182;",   "\\266" },
	{ U_MiddleDot,                        ".",     "\\'B7",               "\\cdot{}",       "&#183;",   "\\267" },
	{ U_Cedilla,                          ",",     "\\'B8",               "\\c{ }",         "&#184;",   "\\270" },
	{ U_SuperscriptOne,                   "1",     "\\'B9",               "$^1$",           "&#185;",   "\\271" },
	{ U_MasculineOrdinalIndicator,        "",      "\\'BA",               "\\b{o}",         "&#186;",   "\\272" },
	{ U_RightPointingGuillemet,           ">>",    "\\'BB",               "\">",            "&#187;",   "\\273" },
	{ U_VulgarFractionOneQuarter,         "1/4",   "\\'BC",               "$\\frac{1}{4}$", "&#188;",   "\\274" },
	{ U_VulgarFractionOneHalf,            "1/2",   "\\'BD",               "$\\frac{1}{2}$", "&#189;",   "\\275" },
	{ U_VulgarFractionThreeQuarters,      "3/4",   "\\'BE",               "$\\frac{3}{4}$", "&#180;",   "\\276" },
	{ U_InvertedQuestionMark,             "?",     "\\'BF",               "?`",             "&#191;",   "\\277" },
	{ U_LatinCapitalLetterAWithGrave,     "A",     "\\'C0",               "\\`{A}",         "&Agrave;", "\\300" },
	{ U_LatinCapitalLetterAWithAcute,     "A",     "\\'C1",               "\\'{A}",         "&Aacute;", "\\301" },
	{ U_LatinCapitalLetterAWithCircumflex,"A",     "\\'C2",               "\\^{A}",         "&Acirc;",  "\\302" },
	{ U_LatinCapitalLetterAWithTilde,     "A",     "\\'C3",               "\\~{A}",         "&Atilde;", "\\303" },
	{ U_LatinCapitalLetterAWithDiaeresis, "Ae",    "\\'C4",               "{\\\"A}",        "&Auml;",   "\\304" },
	{ U_LatinCapitalLetterAWithRingAbove, "A",     "\\'C5",               "{\\AA}",         "&Aring;",  "\\305" },
	{ U_LatinCapitalLigatureAE,           "AE",    "\\'C6",               "{\\AE}",         "&AElig;",  "\\306" },
	{ U_LatinCapitalLetterCWithCedilla,   "C",     "\\'C7",               "\\c{C}",         "&Ccedil;", "\\307" },
	{ U_LatinCapitalLetterEWithGrave,     "E",     "\\'C8",               "\\`{E}",         "&Egrave;", "\\310" },
	{ U_LatinCapitalLetterEWithAcute,     "E",     "\\'C9",               "\\'{E}",         "&Eacute;", "\\311" },
	{ U_LatinCapitalLetterEWithCircumflex,"E",     "\\'CA",               "\\^{E}",         "&Ecirc;",  "\\312" },
	{ U_LatinCapitalLetterEWithDiaeresis, "E",     "\\'CB",               "{\\\"E}",        "&Euml;",   "\\313" },
	{ U_LatinCapitalLetterIWithGrave,     "I",     "\\'CC",               "\\`{I}",         "&Igrave;", "\\314" },
	{ U_LatinCapitalLetterIWithAcute,     "I",     "\\'CD",               "\\'{I}",         "&Iacute;", "\\315" },
	{ U_LatinCapitalLetterIWithCircumflex,"I",     "\\'CE",               "\\^{I}",         "&Icirc;",  "\\316" },
	{ U_LatinCapitalLetterIWithDiaeresis, "I",     "\\'CF",               "{\\\"I}",        "&Iuml;",   "\\317" },
	{ U_LatinCapitalLetterEth,            "TH",    "\\'D0",               "",               "&#208;",   "\\320" },	/* ETH */
	{ U_LatinCapitalLetterNWithTilde,     "N",     "\\'D1",               "\\~{N}",         "&Ntilde;", "\\321" },
	{ U_LatinCapitalLetterOWithGrave,     "O",     "\\'D2",               "\\`{O}",         "&Ograve;", "\\322" },
	{ U_LatinCapitalLetterOWithAcute,     "O",     "\\'D3",               "\\'{O}",         "&Oacute;", "\\323" },
	{ U_LatinCapitalLetterOWithCircumflex,"O",     "\\'D4",               "\\^{O}",         "&Ocirc;",  "\\324" },
	{ U_LatinCapitalLetterOWithTilde,     "O",     "\\'D5",               "\\~{O}",         "&Otilde;", "\\325" },
	{ U_LatinCapitalLetterOWithDiaeresis, "Oe",    "\\'D6",               "{\\\"O}",        "&Ouml;",   "\\326" },
	{ U_MultiplicationSign,               "x",     "\\'D7",               "$\\times$",      "&#215;",   "\\327" },
	{ U_LatinCapitalLetterOSlash,         "O",     "\\'D8",               "{\\O}",          "&Oslash;", "\\330" },
	{ U_LatinCapitalLetterUWithGrave,     "U",     "\\'D9",               "\\`{U}",         "&Ugrave;", "\\331" },
	{ U_LatinCapitalLetterUWithAcute,     "U",     "\\'DA",               "\\'{U}",         "&Uacute;", "\\332" },
	{ U_LatinCapitalLetterUWithCircumflex,"U",     "\\'DB",               "\\^{U}",         "&Ucirc;",  "\\333" },
	{ U_LatinCapitalLetterUWithDiaeresis, "Ue",    "\\'DC",               "{\\\"U}",        "&Uuml;",   "\\334" },
	{ U_LatinCapitalLetterYWithAcute,     "Y",     "\\'DD",               "\\'{Y}",         "&Yacute;", "\\335" },
	{ U_LatinCapitalLetterThorn,          "TH",    "\\'DE",               "",               "&#222;",   "\\336" },	/* THORN */
	{ U_LatinSmallLetterSharpS,           "ss",    "\\'DF",               "{\\ss}",         "&szlig;",  "\\337" },
	{ U_LatinSmallLetterAWithGrave,       "a",     "\\'E0",               "\\`{a}",         "&agrave;", "\\340" },
	{ U_LatinSmallLetterAWithAcute,       "a",     "\\'E1",               "\\'{a}",         "&aacute;", "\\341" },
	{ U_LatinSmallLetterAWithCircumflex,  "a",     "\\'E2",               "\\^{a}",         "&acirc;",  "\\342" },
	{ U_LatinSmallLetterAWithTilde,       "a",     "\\'E3",               "\\~{a}",         "&atilde;", "\\343" },
	{ U_LatinSmallLetterAWithDiaeresis,   "ae",    "\\'E4",               "{\\\"a}",        "&auml;",   "\\344" },
	{ U_LatinSmallLetterAWithRingAbove,   "a",     "\\'E5",               "{\\aa}",         "&aring;",  "\\345" },
	{ U_LatinSmallLigatureAE,             "ae",    "\\'E6",               "{\\ae}",         "&aelig;",  "\\346" },
	{ U_LatinSmallLetterCWithCedilla,     "c",     "\\'E7",               "\\c{c}",         "&ccedil;", "\\347" },
	{ U_LatinSmallLetterEWithGrave,       "e",     "\\'E8",               "\\`{e}",         "&egrave;", "\\350" },
	{ U_LatinSmallLetterEWithAcute,       "e",     "\\'E9",               "\\'{e}",         "&eacute;", "\\351" },
	{ U_LatinSmallLetterEWithCircumflex,  "e",     "\\'EA",               "\\^{e}",         "&ecirc;",  "\\352" },
	{ U_LatinSmallLetterEWithDiaeresis,   "e",     "\\'EB",               "{\\\"e}",        "&euml;",   "\\353" },
	{ U_LatinSmallLetterIWithGrave,       "i",     "\\'EC",               "\\`{i}",         "&igrave;", "\\354" },
	{ U_LatinSmallLetterIWithAcute,       "i",     "\\'ED",               "\\'{i}",         "&iacute;", "\\355" },
	{ U_LatinSmallLetterIWithCircumflex,  "i",     "\\'EE",               "\\^{i}",         "&icirc;",  "\\356" },
	{ U_LatinSmallLetterIWithDiaeresis,   "i",     "\\'EF",               "{\\\"i}",        "&iuml;",   "\\357" },
	{ U_LatinSmallLetterEth,              "th",    "\\'F0",               "",               "&#240;",   "\\360" },	/* eth */
	{ U_LatinSmallLetterNWithTilde,       "n",     "\\'F1",               "\\~{n}",         "&ntilde;", "\\361" },
	{ U_LatinSmallLetterOWithGrave,       "o",     "\\'F2",               "\\`{o}",         "&ograve;", "\\362" },
	{ U_LatinSmallLetterOWithAcute,       "o",     "\\'F3",               "\\'{o}",         "&oacute;", "\\363" },
	{ U_LatinSmallLetterOWithCircumflex,  "o",     "\\'F4",               "\\^{o}",         "&ocirc;",  "\\364" },
	{ U_LatinSmallLetterOWithTilde,       "o",     "\\'F5",               "\\~{o}",         "&otilde;", "\\365" },
	{ U_LatinSmallLetterOWithDiaeresis,   "oe",    "\\'F6",               "{\\\"o}",        "&ouml;",   "\\366" },
	{ U_DivisionSign,                     ":",     "{\\f3 \\'B8}",        "$\\div$",        "&#247;",   "\\367" },
	{ U_LatinSmallLetterOSlash,           "o",     "\\'F8",               "{\\o}",          "&oslash;", "\\370" },
	{ U_LatinSmallLetterUWithGrave,       "u",     "\\'F9",               "\\`{u}",         "&ugrave;", "\\371" },
	{ U_LatinSmallLetterUWithAcute,       "u",     "\\'FA",               "\\'{u}",         "&uacute;", "\\372" },
	{ U_LatinSmallLetterUWithCircumflex,  "u",     "\\'FB",               "\\^{u}",         "&ucirc;",  "\\373" },
	{ U_LatinSmallLetterUWithDiaeresis,   "ue",    "\\'FC",               "{\\\"u}",        "&uuml;",   "\\374" },
	{ U_LatinSmallLetterYWithAcute,       "y",     "\\'FD",               "\\'{y}",         "&yacute;", "\\375" },
	{ U_LatinSmallLetterThorn,            "th",    "\\'FE",               "",               "&#254;",   "\\376" },	/* thorn */
	{ U_LatinSmallLetterYWithDiaeresis,   "y",     "\\'FF",               "\\\"{y}",        "&yuml;",   "\\377" },

	{ U_DotAbove,                         ".",     "\\'B7",               "\\.{ }",         "&#xb7;",   "\\267" },
	{ U_LatinSmallLetterDotlessI,         "i",     "\\'B9",               "$^1$",           "&#xb9;",   "\\271" },
	{ U_CombiningCircumflexAccent,        "^",     "\\'F7",               "\\^{ }",         "&#x302;",   "" },

	{ U_Breve,                            "",      "",                    "\\u{ }",         "&#x2D8;",  "" },
	{ U_Caron,                            "",      "",                    "\\v{ }",         "&#x2C7;",  "" },
	{ U_RingAbove,                        "",      "\\'B0",               "$\\circ$",       "&#x2DA;",  "\\260" },
	{ U_Ogonek,                           ",",     "",                    "",               "&#x2DB;",  "" },	/* <???> */
	{ U_DoubleAcuteAccent,                "",      "{\\f3 \\'B2}",        "\\H{ }",         "&#x2DD;",  "" },

	{ U_CombiningTilde,                   "~",     "~",                   "\\~{ }",         "&#x303;",  "" },	/* ~ */

	{ U_GreekCapitalLetterAlpha,          "Alpha", "{\\f3 A}",            "$\\Alpha$",      "&#x391;",  "Alpha" },
	{ U_GreekCapitalLetterBeta,           "Beta",  "{\\f3 B}",            "$\\Beta$",       "&#x392;",  "Beta" },
	{ U_GreekCapitalLetterGamma,          "Gamma", "{\\f3 G}",            "$\\Gamma$",      "&#x393;",  "Gamma" },
	{ U_GreekCapitalLetterDelta,          "Delta", "{\\f3 D}",            "$\\Delta$",      "&#x394;",  "Delta" },
	{ U_GreekCapitalLetterEpsilon,        "",      "{\\f3 E}",            "$\\Epsilon$",    "&#x395;",  "" },
	{ U_GreekCapitalLetterZeta,           "",      "{\\f3 Z}",            "$\\Zeta$",       "&#x396;",  "" },
	{ U_GreekCapitalLetterEta,            "",      "{\\f3 E}",            "$\\Eta$",        "&#x397;",  "" },
	{ U_GreekCapitalLetterTheta,          "",      "{\\f3 Q}",            "$\\Theta$",      "&#x398;",  "" },
	{ U_GreekCapitalLetterIota,           "",      "{\\f3 I}",            "$\\Iota$",       "&#x399;",  "" },
	{ U_GreekCapitalLetterKappa,          "",      "{\\f3 K}",            "$\\Kappa$",      "&#x39A;",  "" },
	{ U_GreekCapitalLetterLambda,         "",      "{\\f3 L}",            "$\\Lambda$",     "&#x39B;",  "" },
	{ U_GreekCapitalLetterMu,             "",      "{\\f3 M}",            "$\\Mu$",         "&#x39C;",  "" },
	{ U_GreekCapitalLetterNu,             "",      "{\\f3 N}",            "$\\Nu$",         "&#x39D;",  "" },
	{ U_GreekCapitalLetterXi,             "",      "{\\f3 X}",            "$\\Xi$",         "&#x39E;",  "" },
	{ U_GreekCapitalLetterOmicron,        "",      "{\\f3 O}",            "$\\Omicron$",    "&#x39F;",  "" },
	{ U_GreekCapitalLetterPi,             "",      "{\\f3 P}",            "$\\Pi$",         "&#x3A0;",  "" },
	{ U_GreekCapitalLetterRho,            "",      "{\\f3 R}",            "$\\Rho$",        "&#x3A1;",  "" },
	{ U_GreekCapitalLetterSigma,          "",      "{\\f3 S}",            "$\\Sigma$",      "&#x3A3;",  "" },
	{ U_GreekCapitalLetterTau,            "",      "{\\f3 T}",            "$\\Tau$",        "&#x3A4;",  "" },
	{ U_GreekCapitalLetterUpsilon,        "",      "{\\f3 U}",            "$\\Upsilon$",    "&#x3A5;",  "" },
	{ U_GreekCapitalLetterPhi,            "",      "{\\f3 J}",            "$\\Phi$",        "&#x3A6;",  "" },
	{ U_GreekCapitalLetterChi,            "",      "{\\f3 C}",            "$\\Chi$",        "&#x3A7;",  "" },
	{ U_GreekCapitalLetterPsi,            "",      "{\\f3 Y}",            "$\\Psi$",        "&#x3A8;",  "" },
	{ U_GreekCapitalLetterOmega,          "",      "{\\f3 W}",            "$\\Omega$",      "&#x3A9;",  "" },
	{ U_GreekCapitalLetterIotaWithDialytika, "",   "",                    "",               "&#x3AA;",  "" },
	{ U_GreekCapitalLetterUpsilonWithDialytika,"", "",                    "",               "&#x3AB;",  "" },
	{ U_GreekSmallLetterAlphaWithTonos,   "",      "",                    "",               "&#x3AC;",  "" },
	{ U_GreekSmallLetterEpsilonWithTonos, "",      "",                    "",               "&#x3AD;",  "" },
	{ U_GreekSmallLetterEtaWithTonos,     "",      "",                    "",               "&#x3AE;",  "" },
	{ U_GreekSmallLetterIotaWithTonos,    "",      "",                    "",               "&#x3AF;",  "" },
	{ U_GreekSmallLetterUpsilonWithDialytikaAndTonos, "", "",             "",               "&#x3B0;",  "" },
	{ U_GreekSmallLetterAlpha,            "alpha", "{\\f3 a}",            "$\\alpha$",      "&#x3B1;",  "alpha" },
	{ U_GreekSmallLetterBeta,             "beta",  "{\\f3 b}",            "$\\beta$",       "&#x3B2;",  "beta" },
	{ U_GreekSmallLetterGamma,            "gamma", "{\\f3 g}",            "$\\gamma$",      "&#x3B3;",  "gamma" },
	{ U_GreekSmallLetterDelta,            "delta", "{\\f3 d}",            "$\\delta$",      "&#x3B4;",  "delta" },
	{ U_GreekSmallLetterEpsilon,          "",      "{\\f3 e}",            "$\\varepsilon$", "&#x3B5;",  "" },
	{ U_GreekSmallLetterZeta,             "",      "{\\f3 z}",            "$\\zeta$",       "&#x3B6;",  "" },
	{ U_GreekSmallLetterEta,              "",      "{\\f3 e}",            "$\\eta$",        "&#x3B7;",  "" },
	{ U_GreekSmallLetterTheta,            "",      "{\\f3 q}",            "$\\theta$",      "&#x3B8;",  "" },
	{ U_GreekSmallLetterIota,             "",      "{\\f3 i}",            "$\\iota$",       "&#x3B9;",  "" },
	{ U_GreekSmallLetterKappa,            "",      "{\\f3 k}",            "$\\kappa$",      "&#x3BA;",  "" },
	{ U_GreekSmallLetterLambda,           "",      "{\\f3 l}",            "$\\lambda$",     "&#x3BB;",  "" },
	{ U_GreekSmallLetterMu,               "",      "{\\f3 m}",            "$\\mu$",         "&#x3BC;",  "\\265" },
	{ U_GreekSmallLetterNu,               "",      "{\\f3 n}",            "$\\nu$",         "&#x3BD;",  "" },
	{ U_GreekSmallLetterXi,               "",      "{\\f3 x}",            "$\\xi$",         "&#x3BE;",  "" },
	{ U_GreekSmallLetterOmicron,          "",      "{\\f3 o}",            "$\\omicron$",    "&#x3BF;",  "" },
	{ U_GreekSmallLetterPi,               "",      "{\\f3 p}",            "$\\pi$",         "&#x3C0;",  "" },
	{ U_GreekSmallLetterRho,              "",      "{\\f3 r}",            "$\\rho$",        "&#x3C1;",  "" },
	{ U_GreekSmallLetterFinalSigma,       "",      "{\\f3 V}",            "$\\varsigma$",   "&#x3C2;",  "" },
	{ U_GreekSmallLetterSigma,            "",      "{\\f3 s}",            "$\\sigma$",      "&#x3C3;",  "" },
	{ U_GreekSmallLetterTau,              "",      "{\\f3 t}",            "$\\tau$",        "&#x3C4;",  "" },
	{ U_GreekSmallLetterUpsilon,          "",      "{\\f3 u}",            "$\\upsilon$",    "&#x3C5;",  "" },
	{ U_GreekSmallLetterPhi,              "",      "{\\f3 j}",            "$\\varphi$",     "&#x3C6;",  "\\370" },
	{ U_GreekSmallLetterChi,              "",      "{\\f3 c}",            "$\\chi$",        "&#x3C7;",  "" },
	{ U_GreekSmallLetterPsi,              "",      "{\\f3 y}",            "$\\psi$",        "&#x3C8;",  "" },
	{ U_GreekSmallLetterOmega,            "",      "{\\f3 w}",            "$\\omega$",      "&#x3C9;",  "" },
	{ U_GreekSmallLetterIotaWithDialytika,"",      "",                    "",               "&#x3CA;",  "" },
	{ U_GreekSmallLetterUpsilonWithDialytika, "",  "",                    "",               "&#x3CB;",  "" },
	{ U_GreekSmallLetterOmicronWithTonos, "",      "",                    "",               "&#x3CC;",  "" },
	{ U_GreekSmallLetterUpsilonWithTonos, "",      "",                    "",               "&#x3CD;",  "" },
	{ U_GreekSmallLetterOmegaWithTonos,   "",      "",                    "",               "&#x3CE;",  "" },
	{ U_GreekCapitalKaiSymbol,            "",      "",                    "",               "&#x3CF;",  "" },
	{ U_GreekBetaSymbol,                  "",      "",                    "",               "&#x3D0;",  "", },
	{ U_GreekThetaSymbol,                 "",      "",                    "$\\vartheta$",   "&#x3D1;",  "", },
	{ U_GreekUpsilonWithHookSymbol,       "",      "",                    "",               "&#x3D2;",  "", },
	{ U_GreekUpsilonWithAcuteAndHookSymbol, "",    "",                    "",               "&#x3D3;",  "", },
	{ U_GreekUpsilonWithDiaeresisAndHookSymbol,"", "",                    "",               "&#x3D4;",  "", },
	{ U_GreekPhiSymbol,                   "",      "",                    "$\\phi$",        "&#x3D5;",  "", },
	{ U_GreekPiSymbol,                    "",      "",                    "$\\varpi$",      "&#x3D6;",  "", },
	{ U_GreekLunateEpsilonSymbol,         "",      "",                    "$\\epsilon$",    "&#x3F5;",  "", },
	{ U_GreekReversedLunateEpsilonSymbol, "",      "",                   "$\\backepsilon$", "&#x3F6;",  "", },

	{ U_LeftSingleQuotationMark,          "'",     "\\'91",               "`",              "&#x2018;", "\\221" },
	{ U_RightPointingSingleGuillemet,     ">",     ">",                   "$>$",            "&#x203A;", ">" },
	{ U_FractionSlash,                    "/",     "{\\f3 \\'A4}",        "/",              "&#x2044;", "/" },
	{ U_SuperscriptLatinSmallLetterN,     "n",     "",                    "$^n$",           "&#x207F;", "" },
	{ U_LiraSign,                         "ITL",   "",                    "",               "&#x20A4;", "" },	/* dp */
	{ U_PesetaSign,                       "",      "",                    "",               "&#x20A7;", "" },

	{ U_ForAll,                           "",      "",                    "$\\forall$",     "&#x2200;", "", },
	{ U_PartialDifferential,              "",      "{\\f3 \\'B6}",        "$\\partial$",    "&#x2202;", "" },
	{ U_Increment,                        "",      "{\\f3 D}",            "$\\triangle$",   "&#x2206;", "" },
	{ U_Nabla,                            "",      "{\\f3 \\'D1}",        "$\\nabla$",      "&#x2207;", "" },
	{ U_ElementOf,                        "",      "{\\f3 \\'CE}",        "$\\in$",         "&#x2208;", "" },
	{ U_NAryProduct,                      "",      "{\\f3 \\'D5}",        "$\\prod$",       "&#x220F;", "" },
	{ U_NArySummation,                    "",      "{\\f3 \\'E5}",        "$\\sum$",        "&#x2211;", "" },
	{ U_SquareRoot,                       "",      "{\\f3 \\'D6}",        "$\\surd$",       "&#x221a;", "" },
	{ U_Infinity,                         "",      "{\\f3 \\'A5}",        "$\\infty$",      "&#x221e;", "" },
	{ U_LogicalAnd,                       "&&",    "{\\f3 \\'D9}",        "$\\land$",       "&#x2227;", "\\367" },
	{ U_LogicalOr,                        "||",    "{\\f3 \\'DA}",        "$\\lor$",        "&#x2228;", "" },
	{ U_Intersection,                     "",      "{\\f3 \\'C7}",        "$\\cap$",        "&#x2229;", "" },
	{ U_Union,                            "",      "{\\f3 \\'C8}",        "$\\cup$",        "&#x222A;", "" },
	{ U_Integral,                         "",      "",                    "$\\intop$",      "&#x222B;", "" },
	{ U_ContourIntegral,                  "",      "{\\f3 \\'A5}",        "$\\ointop$",     "&#x222E;", "" },
	{ U_AlmostEqualTo,                    "",      "{\\f3 \\'BB}",        "$\\approx$",     "&#x2248;", "" },
	{ U_NotEqualTo,                       "",      "{\\f3 \\'B9}",        "$\\neq$",        "&#x2260;", "\\254" },
	{ U_IdenticalTo,                      "==",    "{\\f3 \\'BA}",        "$\\equiv$",      "&#x2261;", "" },
	{ U_LessThanOrEqualTo,                "<=",    "{\\f3 \\'A3}",        "$\\leq$",        "&#x2264;", "" },
	{ U_GreaterThanOrEqualTo,             ">=",    "{\\f3 \\'B3}",        "$\\geq$",        "&#x2265;", "" },

	{ U_ReversedNotSign,                  "",      "",                    "",               "&#x2310;", "" },
	{ U_TopHalfIntegral,                  "",      "",                    "",               "&#x2320;", "" },
	{ U_BottomHalfIntegral,               "",      "",                    "",               "&#x2321;", "" },
	{ U_Frown,                            ":-(",   "",                    "$\\frown$",      "&#x2322;", "", },
	{ U_Smile,                            ":-)",   "",                    "$\\smile$",      "&#x2323;", "", },

	{ U_Lozenge,                          "",      "{\\f3 \\'E0}",        "$\\lozenge$",    "&#x25CA;", "" },

	{ U_LatinCapitalLigatureIJ,           "IJ",    "IJ",                  "IJ",             "&#x132;",  "ij" },
	{ U_LatinSmallLigatureIJ,             "ij",    "ij",                  "ij",             "&#x133;",  "ij" },
	{ U_LatinCapitalLetterLWithStroke,    "L",     "",                    "",               "&#x141;",  "" },	/* L/ <???> */
	{ U_LatinSmallLetterLWithStroke,      "l",     "",                    "",               "&#x142;",  "" },	/* l/ <???> */
	{ U_LatinSmallLigatureFI,             "fi",    "fi",                  "fi",             "&#xFB01;", "fi" },
	{ U_LatinSmallLigatureFL,             "fl",    "fl",                  "fl",             "&#xFB02;", "fl" },

	/* list terminator */
	{ U_NIL, "", "", "", "", "" }
};





/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  uni2misc():
*     convert (UDO's) universal characters into miscellaneous encodings
*
*  Notes:
*     This function is only called when bDocUniversalCharsetOn is TRUE,
*     set by the UDO command !universal_charset.
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void uni2misc(char *s)
{
	register int i;

	if (s[0] == EOS)					/* empty string */
		return;

	if (strstr(s, "(!") == NULL)		/* No UDO command header found */
		return;

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		for (i = 0; i < (int) UNITABLESIZE; i++)
			replace_all(s, unitab[i].uni, unitab[i].tex);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (html_ignore_8bit)
		{
			recode_udo(s);
		} else
		{
			for (i = 0; i < (int) UNITABLESIZE; i++)
				replace_all(s, unitab[i].uni, unitab[i].html);
		}
		break;

	case TOLDS:
	case TOHPH:
		for (i = 0; i < (int) UNITABLESIZE; i++)
			replace_all(s, unitab[i].uni, unitab[i].html);
		break;

	case TOWIN:
	case TOWH4:
	case TOAQV:
	case TORTF:
		for (i = 0; i < (int) UNITABLESIZE; i++)
			replace_all(s, unitab[i].uni, unitab[i].win);
		break;

	case TOPCH:
		recode_udo(s);
		if (no_umlaute)					/* target encoding must not use umlauts */
			recode_chrtab(s, CHRTAB_ASCII);	/* convert all umlauts to pure ASCII */
		break;

	case TOLYX:
		for (i = 0; i < (int) UNITABLESIZE; i++)
			replace_all(s, unitab[i].uni, unitab[i].lyx);
		break;
	}
}





#if 0
/*******************************************************************************
*
*  recode_always():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void recode_always(char *zeile, int char_set)
{
	switch (char_set)
	{
#if SYSTEM_CHARSET != CODE_CP1252
	case CODE_CP1252:
		iso2system(zeile);
		break;
#endif

#if !defined(__MACOS__) && !defined(__MACOSX__)
	case CODE_MAC:
		mac2iso(zeile);
		iso2system(zeile);
		break;
#endif

#ifndef __TOS__
	case CODE_TOS:
		tos2iso(zeile);
		iso2system(zeile);
		break;
#endif

#ifndef __MSDOS__
	case CODE_437:
		cp437iso(zeile);
		iso2system(zeile);
		break;
#endif

#ifndef __MSDOS850__
	case CODE_850:
		cp850iso(zeile);
		iso2system(zeile);
		break;
#endif

#ifndef __HPUX_ROMAN8__
	case CODE_HP8:
		hp82iso(zeile);
		iso2system(zeile);
		break;
#endif

#ifndef __NEXTSTEP__
	case CODE_NEXT:
		next2iso(zeile);
		iso2system(zeile);
		break;
#endif
	}
}
#endif










/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  unicode2chars():
*     get char(s!) from Unicode value
*
*  return:
*     ^ string with char(s)
*
******************************************|************************************/

GLOBAL const char *unicode2char(_UWORD unicode, char *cbuf)
{
	int i = 0;
	const _UWORD *pumap;				/* u_CODE_xxx[] arrays */


	if (unicode == U_NIL)				/* nothing to do */
		return "";

	if (iEncodingTarget == CODE_UTF8)	/* Unicode first! */
	{
		bstr_to_utf8(unicode, cbuf);
		return cbuf;
	}

	pumap = chr_codepage(iEncodingTarget);	/* get ^ to codepage */

	if (pumap == NULL)					/* no codepage for Unicode!!! */
		return "";

	for (i = 0; i < 256; i++)			/* get ALL chars */
	{
		if (pumap[i] == unicode)		/* found! */
		{
			cbuf[0] = i;				/* compose string */
			cbuf[1] = EOS;
			return cbuf;
		}
	}

	return "";
}





/*******************************************************************************
*
*  utf8_to_bstr():
*     convert UTF-8 bytes into Unicode codepoint value (known length of byte stream!)
*
*  Notes:
*     see bstr_to_utf8()
*
*  Return:
*     Unicode codepoint
*
******************************************|************************************/

GLOBAL _UWORD utf8_to_bstr(const char *sz, int len)
{
	int i = 0;
	_UWORD temp = 0;

	while (i < len)
	{
		if ((sz[i] & 0x80) == 0)		/* 0000 0000-0000 007F 0xxxxxxx */
		{
			temp = sz[i];
			++i;
		} else if ((sz[i] & 0xE0) == 0xC0)	/* 0000 0080-0000 07FF 110xxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x1F);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			i += 2;
		} else if ((sz[i] & 0xF0) == 0xE0)	/* 0000 0800-0000 FFFF 1110xxxx 10xxxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x0F);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 2] & 0x3F);
			i += 3;
		} else if ((sz[i] & 0xF8) == 0xF0)	/* 0001 0000-001F FFFF 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x07);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 2] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 3] & 0x3F);
			i += 4;
		}
#if 0
		/* fd:2010-02-17: faded for now */

		else if ((sz[i] & 0xFC) == 0xF8)	/* 0020 0000-03FF FFFF 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x03);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 2] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 3] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 4] & 0x3F);
			i += 5;
		} else if ((sz[i] & 0xFE) == 0xFC)	/* 0400 0000-7FFF FFFF 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x01);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 2] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 3] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 4] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 5] & 0x3F);
			i += 6;
		}
#endif /* #if 0 */

		else
		{
			temp = '?';
		}
	}

	return temp;
}





/*******************************************************************************
*
*  utf8_to_uchar():
*     convert UTF-8 bytes into Unicode char (unknown length of byte stream)
*
*  Notes:
*     see bstr_to_utf8()
*
*  Return:
*     Unicode codepoint
*
******************************************|************************************/

GLOBAL _UWORD utf8_to_uchar(const char *sz, int *length)
{
	int i = 0;
	_UWORD temp = 0;					/* buffer for Unicode codepoint value */
	_BOOL done = FALSE;					/* TRUE: 1st Unicode char found */

	while (sz[i] != '\0')				/* whole string */
	{
		if ((sz[i] & 0x80) == 0)		/* 0000 0000-0000 007F 0xxxxxxx */
		{
			temp = sz[i];
			*length = 1;
			done = TRUE;
		} else if ((sz[i] & 0xE0) == 0xC0)	/* 0000 0080-0000 07FF 110xxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x1F);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			*length = 2;
			done = TRUE;
		} else if ((sz[i] & 0xF0) == 0xE0)	/* 0000 0800-0000 FFFF 1110xxxx 10xxxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x0F);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 2] & 0x3F);
			*length = 3;
			done = TRUE;
		} else if ((sz[i] & 0xF8) == 0xF0)	/* 0001 0000-001F FFFF 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x07);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 2] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 3] & 0x3F);
			*length = 4;
			done = TRUE;
		}
#if 0
		/* fd:2010-02-17: faded, because UTF-8 cannot have more than 4 bytes! */

		else if ((sz[i] & 0xFC) == 0xF8)	/* 0020 0000-03FF FFFF 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x03);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 2] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 3] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 4] & 0x3F);
			i += 5;
		} else if ((sz[i] & 0xFE) == 0xFC)	/* 0400 0000-7FFF FFFF 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
		{
			temp = (sz[i] & 0x01);
			temp <<= 6;
			temp += (sz[i + 1] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 2] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 3] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 4] & 0x3F);
			temp <<= 6;
			temp += (sz[i + 5] & 0x3F);
			i += 6;
		}
#endif /* #if 0 */

		else
		{
			temp = '?';
			done = TRUE;
		}

		if (done)
			break;
	}

	return temp;
}





/*******************************************************************************
*
*  bstr_to_utf8():
*     convert Unicode value into UTF-8 bytes
*
*  Notes:
*
*     Table 3-6. UTF-8 Bit Distribution (source: www.unicode.org)
*     ------------------------------------------------------------------
*     Scalar Value                1st Byte  2nd Byte  3rd Byte  4th Byte
*     00000000 0xxxxxxx           0xxxxxxx
*     00000yyy yyxxxxxx           110yyyyy  10xxxxxx
*     zzzzyyyy yyxxxxxx           1110zzzz  10yyyyyy  10xxxxxx
*     000uuuuu zzzzyyyy yyxxxxxx  11110uuu  10uuzzzz  10yyyyyy  10xxxxxx
*     ------------------------------------------------------------------
*
*  Mnemonic of bit map:
*     0nnnnnnn = single-byte char                (00 .. 7F)
*     10nnnnnn = following byte in a n-byte char (80 .. BF)
*     110nnnnn = first byte of a 2-byte char     (C0 .. DF)
*     1110nnnn = first byte of a 3-byte char     (E0 .. EF)
*     11110nnn = first byte of a 4-byte char     (F0 .. F7)
*
*  General source found at:
*     http://www.codeguru.com/forum/archive/index.php/t-288665.html
*
*  Return:
*     UTF-8 encoded, null-terminated string
*
******************************************|************************************/

GLOBAL char *bstr_to_utf8(_UWORD ucode, char *utf)
{
	_ULONG temp;

	memset(utf, 0, 7);					/* clear buffer */
	temp = (_ULONG) ucode;

	if (temp < 0x0080)					/* 0000 0000-0000 007F -> 0xxxxxxx */
	{
		utf[0] = temp;
	} else if (temp < 0x0800)			/* 0000 0080-0000 07FF -> 110xxxxx 10xxxxxx */
	{
		utf[0] = (0xC0 | (temp >> 6));
		utf[1] = (0x80 | (temp & 0x3F));
	} else if (temp <= 0xFFFF)			/* 0000 0800-0000 FFFF -> 1110xxxx 10xxxxxx 10xxxxxx */
	{
		utf[0] = (0xE0 | (temp >> 12));
		utf[1] = (0x80 | ((temp >> 6) & 0x3F));
		utf[2] = (0x80 | (temp & 0x3F));
	}
#if 0
	/* fd:2010-02-17: faded, because UNICODE.H does not define Unicode constants > 0xFFFF yet! */

	else if (temp < 0x00200000)			/* 0001 0000-001F FFFF -> 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
	{
		utf[0] = (0xF0 | (temp >> 18));
		utf[1] = (0x80 | ((temp >> 12) & 0x3F));
		utf[2] = (0x80 | ((temp >> 6) & 0x3F));
		utf[3] = (0x80 | (temp & 0x3F));
	}
#endif /* #if 0 */

#if 0
	/* fd:2010-02-17: faded, because UTF-8 cannot have more than 4 bytes! */

	else if (temp < 0x04000000)			/* 0020 0000-03FF FFFF 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
	{
		utf[0] = (0xF8 | (temp >> 24));
		utf[1] = (0x80 | ((temp >> 18) & 0x3F));
		utf[2] = (0x80 | ((temp >> 12) & 0x3F));
		utf[3] = (0x80 | ((temp >> 6) & 0x3F));
		utf[4] = (0x80 | (temp & 0x3F));
	} else if (temp < 0x80000000)		/* 0400 0000-7FFF FFFF 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx */
	{
		utf[0] = (0xFC | (temp >> 30));
		utf[1] = (0x80 | ((temp >> 24) & 0x3F));
		utf[2] = (0x80 | ((temp >> 18) & 0x3F));
		utf[3] = (0x80 | ((temp >> 12) & 0x3F));
		utf[4] = (0x80 | ((temp >> 6) & 0x3F));
		utf[5] = (0x80 | (temp & 0x3F));
	}
#endif /* #if 0 */

	return utf;							/* return a null-terminated string */
}





/*******************************************************************************
*
*  convert_sz():
*     convert encoding of German ss ligature
*
*  Notes:
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void convert_sz(char *s)
{
#ifdef __TOS__
	replace_char(s, '\341', '\236');	/* from DOS(?):0xE1 to TOS:0x9E */
#else
# if !defined(__MSDOS__) && !defined(__MSDOS850__)
	replace_char(s, '\236', '\341');	/* from TOS:0x9E to DOS(?):0xE1 */
#else
	UNUSED(s);
#endif
#endif
}





/*******************************************************************************
*
*  recode_udo():
*     convert (UDO's) universal characters into target encoding
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void recode_udo(char *s)
{
	register int i = 0;
	char cbuf[8];
	const char *repl;

	if (s[0] == EOS)					/* empty string */
		return;

	if (strstr(s, "(!") == NULL)		/* no UDO command header found */
		return;

	while (u_CODE_UDO[i].udo != NULL)	/* check whole table */
	{
		/* get recoded replacement char(s) */
		repl = unicode2char(u_CODE_UDO[i].unicode, cbuf);
		/* replace all existances */
		replace_all(s, u_CODE_UDO[i].udo, repl);

		if (strstr(s, "(!") == NULL)	/* no further UDO command header found */
			break;

		i++;
	}

	if (no_umlaute)						/* target encoding must not use umlauts */
		recode_chrtab(s, CHRTAB_ASCII);	/* convert all umlauts to pure ASCII */
}




/*******************************************************************************
*
*  recode():
*     recode a line into another encoding
*
*  Notes:
*     When code_source or code_target are UTF-8, there are no relevant codepages.
*     As this function handles three different methods of recoding, the NULL pointer 
*     of the non-existing UTF codepages should not be any problem here.
*
*     The recoding methods are:
*     -  UTF-8 to 1-byte recoding
*     -  1-byte to UTF-8 recoding
*     -  1-byte to 1-byte recoding
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void recode(char *zeile, int from_char_set, int to_char_set)
{
	char *ptr;
	_UWORD idx;
	const _UWORD *pUsrc;				/* encoding table for source encoding */
	const _UWORD *pUtrg;				/* encoding table for target encoding */
	char sSource[42];					/* source encoding name, human-readable */
	char sTarget[42];					/* target encoding name, human-readable */
	_UWORD i;
	_BOOL found = FALSE;				/* TRUE: char found */

	if (from_char_set == to_char_set)
		return;

	pUsrc = chr_codepage(from_char_set);
	pUtrg = chr_codepage(to_char_set);

	strcpy(sSource, chr_codepage_name(from_char_set));
	strcpy(sTarget, chr_codepage_name(to_char_set));


	ptr = get_8bit_ptr(zeile);			/* set ^ to first high-ASCII char */

	if (!ptr)
	{
		if (bDocUniversalCharsetOn)		/* clear UDO universal chars */
			recode_udo(zeile);

		return;
	}

	/* --- UTF-8 to 1-byte recoding --- */

	if (from_char_set == CODE_UTF8)		/* convert UTF-8 to 1-byte format first */
	{
		char sbuf[LINELEN];				/* line buffer */
		char cbuf[9];					/* chars buffer */
		int j;
		int len = 0;					/* >1 = convert n-byte UTF value */

		memset(sbuf, 0, LINELEN);
		memset(cbuf, 0, 9);

		for (j = 0; zeile[j] != EOS; j++)
		{
			idx = (_UBYTE) zeile[j];

			if (idx < 128)				/* 0000 0000-0000 007F 0xxxxxxx */
			{
				cbuf[0] = idx;
				cbuf[1] = EOS;
				strcat(sbuf, cbuf);
				len = 0;
			} else if ((idx & 0xE0) == 0xC0)	/* 0000 0080-0000 07FF 110xxxxx 10xxxxxx */
			{
				cbuf[0] = idx;
				j++;
				cbuf[1] = (_UBYTE) zeile[j];
				cbuf[2] = EOS;
				len = 2;
			} else if ((idx & 0xF0) == 0xE0)	/* 0000 0800-0000 FFFF 1110xxxx 10xxxxxx 10xxxxxx */
			{
				cbuf[0] = idx;
				j++;
				cbuf[1] = (_UBYTE) zeile[j];
				j++;
				cbuf[2] = (_UBYTE) zeile[j];
				cbuf[3] = EOS;
				len = 3;
			} else if ((idx & 0xF8) == 0xF0)	/* 0001 0000-001F FFFF 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
			{
				cbuf[0] = idx;
				j++;
				cbuf[1] = (_UBYTE) zeile[j];
				j++;
				cbuf[2] = (_UBYTE) zeile[j];
				j++;
				cbuf[3] = (_UBYTE) zeile[j];
				cbuf[4] = EOS;
				len = 4;
			}

			if (len > 0)
			{
				idx = utf8_to_bstr(cbuf, len);	/* get Unicode */

				found = FALSE;

				for (i = 128; i < 256; i++)	/* check if target encoding supports this char */
				{
					if (pUtrg[i] == idx)
					{
						cbuf[0] = i;	/* use char from THIS codepage slot! */
						cbuf[1] = EOS;
						strcat(sbuf, cbuf);
						found = TRUE;
						break;
					}
				}

				if (!found)				/* no valid character found */
				{
					cbuf[0] = '*';		/* no ANSI character */
					cbuf[1] = EOS;
					warning_cannot_recode(idx, sSource, sTarget);
					strcat(sbuf, cbuf);
				}
			}
		}

		strcpy(zeile, sbuf);			/* restore line */

		if (bDocUniversalCharsetOn)		/* clear UDO universal chars */
			recode_udo(zeile);

		return;							/* we're done already! */
	}


	/* --- 1-byte to UTF-8 recoding --- */

	if (to_char_set == CODE_UTF8)		/* convert 1-byte format to UTF-8 first */
	{
		char sbuf[LINELEN];				/* line buffer */
		char cbuf[9];					/* chars buffer */
		int j;

		memset(sbuf, 0, sizeof(sbuf));
		memset(cbuf, 0, sizeof(cbuf));

		for (j = 0; zeile[j] != EOS; j++)
		{
			idx = (_UBYTE) zeile[j];

			if (idx < 128)				/* low-ASCII char */
			{
				cbuf[0] = idx;
				cbuf[1] = EOS;
				strcat(sbuf, cbuf);
			} else if (pUsrc[idx] != U_NIL)	/* valid Unicode */
			{
				bstr_to_utf8(pUsrc[idx], cbuf);
				strcat(sbuf, cbuf);
			} else						/* wrong source encoding or invalid char */
			{
				bstr_to_utf8(U_ReplacementCharacter, cbuf);
				strcat(sbuf, cbuf);
			}
		}

		strcpy(zeile, sbuf);			/* restore line */

		if (bDocUniversalCharsetOn)		/* clear UDO universal chars */
			recode_udo(zeile);

		return;							/* we're done already */
	}


	/* --- 1-byte to 1-byte recoding --- */

	while (*ptr)						/* check whole string */
	{
		idx = (_UBYTE) * ptr;			/* get char value */

		if (idx > 127)					/* handle BYTE encodings */
		{
			if (pUsrc[idx] != U_NIL)	/* check if conversion is possible */
			{
				for (i = 128; i < 256; i++)
				{
					if (pUtrg[i] == pUsrc[idx])
					{
						*ptr = i;
						break;
					}
				}
				if (i >= 256)
				{
					warning_cannot_recode(idx, sSource, sTarget);
				}
			} else						/* conversion is not possible */
			{
				warning_cannot_recode(idx, sSource, sTarget);

				/* pass un-mappable char through */
/*          *ptr = '?';
*/
			}
		}

		ptr++;							/* next character */

		if (bDocUniversalCharsetOn)		/* clear UDO universal chars */
			recode_udo(zeile);
	}
}





GLOBAL void html2sys(char *s)
{
	register int i;
	char one[2];

	if (s[0] == EOS)
		return;

	strcpy(one, " ");

	for (i = 0; chrtab[i].uname != U_NIL; i++)
	{
		if (chrtab[i].uname < 0x100)
		{
			one[0] = chrtab[i].uname;
			replace_all(s, chrtab[i].html, one);
		}
	}

	for (i = 0; i < MAXHTML7BIT; i++)
	{
		one[0] = html7bit[i].c;
		replace_all(s, html7bit[i].quoted, one);
	}
}


/*******************************************************************************
*
*  recode_chrtab():
*     recode a string from chrtab[] via Unicode name to another encoding
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void recode_chrtab(char *s, int type)
{
	register int i = 0;					/* counter for string */
	register int j = 0;					/* counter for chrtab[] */
	const _UWORD *pUtrg;				/* encoding table for target encoding */
	_UWORD idx;							/* Unicode index of char */
	char sbuf[LINELEN];					/* buffer the whole string */
	char cbuf[2];						/* buffer for one char */

	if (s[0] == EOS)					/* empty string */
		return;

	pUtrg = chr_codepage(iEncodingTarget);	/* get the right encoding table! */

	if (!pUtrg)							/* Unicode? */
		return;							/* no recoding! */

	memset(sbuf, 0, LINELEN);
	memset(cbuf, 0, 2);

	for (i = 0; s[i] != EOS; i++)
	{
		idx = (_UBYTE) s[i];			/* get Unicode index of char */

		if (idx > 127)					/* convertable char */
		{
			j = 0;

			while (chrtab[j].uname != U_NIL)	/* check for end of table! */
			{
				/* identical Unicode name found! */
				if (chrtab[j].uname == pUtrg[idx])
				{

					switch (type)
					{
					case CHRTAB_ASCII:
						/* we have do replace something */
						if (chrtab[j].ascii[0] != EOS)
						{				/* add replacement string to buffer */
							strcat(sbuf, chrtab[j].ascii);
							break;
						}

						break;

					case CHRTAB_ANSI:
						/* we have do replace something */
						if (chrtab[j].rtf[0] != EOS)
						{				/* add replacement string to buffer */
							strcat(sbuf, chrtab[j].rtf);
							break;
						}

						break;

					case CHRTAB_HTML:
						/* we have do replace something */
						if (chrtab[j].html[0] != EOS)
						{				/* add replacement string to buffer */
							strcat(sbuf, chrtab[j].html);
							break;
						}

						break;

					}
				}

				j++;					/* next chrtab[] entry */
			}
		} else
		{
			cbuf[0] = s[i];				/* convert char to string */
			strcat(sbuf, cbuf);			/* add to buffer */
		}
	}

	strcpy(s, sbuf);					/* return converted string */

	switch (type)
	{
	case CHRTAB_HTML:
		for (i = 0; i < MAXHTML7BIT; i++)	/* convert special HTML characters */
		{
			cbuf[0] = html7bit[i].c;	/* get HTML character (e.g. '&') */
			/* replace it (e.g. by '&amp;') */
			replace_all(s, html7bit[i].quoted, cbuf);
		}
		break;
	}


#if 0
	/* fd:2010-02-17: old stuff from win2sys() */

	strcpy(four, "    ");				/* clear other buffer */

	/* Nicht umwandelbare Zeichen entfernen */
	while ((ptr = strstr(s, "\\'")) != NULL)
	{
		four[0] = ptr[0];
		four[1] = ptr[1];
		four[2] = ptr[2];
		four[3] = ptr[3];

		delete_all(s, four);
	}
#endif
}





/*******************************************************************************
*
*  calc_ttf_twip():
*     Breiten von Strings in twip (1/1440" bzw. 1/20 pt) fuer WinHelp berechnen
*
*  Return:
*     twip
*
******************************************|************************************/

GLOBAL int calc_ttf_twip(const char *s, const int font, const int style)
{
	int pixel, twip;
	size_t i;
	char d[512];

	if (s[0] == EOS)
		return 0;

	strcpy(d, s);
	strcat(d, "W");						/* Breitenausgleiche */

	pixel = 0;
	switch (font)
	{
	case TTF_TIMES:
		switch (style)
		{
		case TTF_BOLD:
			for (i = 0; i < strlen(d); i++)
			{
				pixel += width_times_11_bold[(_UBYTE) d[i]];
				pixel++;
			}
			break;

		case TTF_ITALIC:
			for (i = 0; i < strlen(d); i++)
			{
				pixel += width_times_11_italic[(_UBYTE) d[i]];
				pixel++;
			}
			break;

		default:
			for (i = 0; i < strlen(d); i++)
			{
				pixel += width_times_11_regular[(_UBYTE) d[i]];
				pixel++;
			}
			break;
		}
		break;

	case TTF_COURIER:
		switch (style)
		{
		case TTF_BOLD:
			for (i = 0; i < strlen(d); i++)
			{
				pixel += width_courier_10_bold[(_UBYTE) d[i]];
				pixel++;
			}
			break;

		case TTF_ITALIC:
			for (i = 0; i < strlen(d); i++)
			{
				pixel += width_courier_10_italic[(_UBYTE) d[i]];
				pixel++;
			}
			break;

		default:
			for (i = 0; i < strlen(d); i++)
			{
				pixel += width_courier_10_regular[(_UBYTE) d[i]];
				pixel++;
			}
			break;
		}
		break;

	default:
		switch (style)
		{
		case TTF_BOLD:
			for (i = 0; i < strlen(d); i++)
			{
				pixel += width_arial_10_bold[(_UBYTE) d[i]];
				pixel++;
			}
			break;

		case TTF_ITALIC:
			for (i = 0; i < strlen(d); i++)
			{
				pixel += width_arial_10_italic[(_UBYTE) d[i]];
				pixel++;
			}
			break;

		default:
			for (i = 0; i < strlen(d); i++)
			{
				pixel += width_arial_10_regular[(_UBYTE) d[i]];
				pixel++;
			}
			break;
		}
		break;
	}

	/* pt = pixel * 72 / 100                       */
	/* twip = pixel * 72 / 100 * 20 = pixel * 14.4 */
	/* passt aber nicht, daher etwas mehr!         */

	twip = (int) (pixel * 14.4);

	return twip;
}





/*******************************************************************************
*
*     BASIC REPLACEMENT ROUTINES
*
*     - which remove not allowed characters from nodes
*     - handle special UDO cases
*
******************************************|************************************/

/*******************************************************************************
*
*  replace_all_copyright():
*     adjust copyright links
*
*  Notes:
*     Bei Pure C Help wird bei Copyright auf die Borland-Seite
*     verwiesen, und nicht auf einen eigenen Node. Daher die
*     Zeichenkette anpassen. Nicht schoen, aber zweckmaessig.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_all_copyright(char *s)
{
	if (desttype == TOPCH)				/* Pure C Help */
	{
		qreplace_all(s, "Copyright", 9, "Copy-Right", 10);
	}
}





/*******************************************************************************
*
*  delete_all_divis():
*     delete all internal UDO hyphen markers
*
*  Notes:
*     DIVIS_S + DIVIS_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void delete_all_divis(char *s)
{
	qdelete_all(s, DIVIS_S, DIVIS_S_LEN);
}





/*******************************************************************************
*
*  indent2space():
*     convert indents into spaces
*
*  Notes:
*     INDENT_S + INDENT_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void indent2space(char *s)
{
#if (INDENT_S_LEN==1)
	replace_char(s, INDENT_C, ' ');
#else
	qreplace_all(s, INDENT_S, INDENT_S_LEN, " ", 1);
#endif
}





/*******************************************************************************
*
*  space2indent():
*     convert spaces into indents
*
*  Notes:
*     INDENT_S + INDENT_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void space2indent(char *s)
{
#if (INDENT_S_LEN==1)
	replace_char(s, ' ', INDENT_C);
#else
	qreplace_all(s, " ", 1, INDENT_S, INDENT_S_LEN);
#endif
}





/*******************************************************************************
*
*  nbsp2space():
*     convert non-breakable spaces into spaces
*
*  Notes:
*     NBSP_S + NBSP_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void nbsp2space(char *s)
{
#if (NBSP_S_LEN==1)
	replace_char(s, NBSP_C, ' ');
#else
	qreplace_all(s, NBSP_S, NBSP_S_LEN, " ", 1);
#endif
}





/*******************************************************************************
*
*  space2nbsp():
*     convert spaces into non-breakable spaces
*
*  Notes:
*     NBSP_S + NBSP_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void space2nbsp(char *s)
{
#if (NBSP_S_LEN==1)
	replace_char(s, ' ', NBSP_C);
#else
	qreplace_all(s, " ", 1, NBSP_S, NBSP_S_LEN);
#endif
}





/*******************************************************************************
*
*  label2tex():
*     replace or remove all chars which are not allowed in a TeX label "\label{...}"
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void label2tex(char *s)
{
	qreplace_all(s, "{\\\"a}", 5, "ae", 2);
	qreplace_all(s, "{\\\"o}", 5, "oe", 2);
	qreplace_all(s, "{\\\"u}", 5, "ue", 2);
	qreplace_all(s, "{\\\"s}", 5, "ss", 2);
	qreplace_all(s, "{\\ss}", 5, "ss", 2);
	qreplace_all(s, "{\\\"A}", 5, "Ae", 2);
	qreplace_all(s, "{\\\"O}", 5, "Oe", 2);
	qreplace_all(s, "{\\\"U}", 5, "Ue", 2);
	qreplace_all(s, "\\_", 2, "-", 1);
	qreplace_all(s, "_", 1, "-", 1);
	qreplace_all(s, "#", 1, "035-", 4);
	qreplace_all(s, "$", 1, "036-", 4);
	qreplace_all(s, "%", 1, "037-", 4);
	qreplace_all(s, "&", 1, "038-", 4);
	qreplace_all(s, "~", 1, "126-", 4);
	qreplace_all(s, "^", 1, "094-", 4);
	qreplace_all(s, "{", 1, "123-", 4);
	qreplace_all(s, "}", 1, "125-", 4);

	qdelete_all(s, "\\", 1);
	qreplace_all(s, "\"'", 2, "'", 1);
	qreplace_all(s, "\"`", 2, "`", 1);
}



/*******************************************************************************
*
*  label2lyx():
*     replace or remove all chars which are not allowed in a Lyx label "\label{...}"
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void label2lyx(char *s)
{
	qreplace_all(s, "{\\\"a}", 5, "ae", 2);
	qreplace_all(s, "{\\\"o}", 5, "oe", 2);
	qreplace_all(s, "{\\\"u}", 5, "ue", 2);
	qreplace_all(s, "{\\\"s}", 5, "ss", 2);
	qreplace_all(s, "{\\ss}", 5, "ss", 2);
	qreplace_all(s, "{\\\"A}", 5, "Ae", 2);
	qreplace_all(s, "{\\\"O}", 5, "Oe", 2);
	qreplace_all(s, "{\\\"U}", 5, "Ue", 2);
	qreplace_all(s, "\\_", 2, "-", 1);
	qreplace_all(s, "_", 1, "-", 1);
	qreplace_all(s, "#", 1, "035-", 4);
	qreplace_all(s, "$", 1, "036-", 4);
	qreplace_all(s, "%", 1, "037-", 4);
	qreplace_all(s, "&", 1, "038-", 4);
	qreplace_all(s, "\\SpecialChar ~\n", 15, "~", 1);
	qreplace_all(s, "~", 1, "126-", 4);
	qreplace_all(s, "^", 1, "094-", 4);
	qreplace_all(s, "{", 1, "123-", 4);
	qreplace_all(s, "}", 1, "125-", 4);

	qdelete_all(s, "\\", 1);
	qreplace_all(s, "\"'", 2, "'", 1);
	qreplace_all(s, "\"`", 2, "`", 1);
	indent2space(s);
}





/*******************************************************************************
*
*  label2html():
*     replace or remove all chars which are not allowed in an HTML anchor
*
*  Notes:
*     Gemaess SGML companion sind erlaubt: "a-z", "A-Z", "0-9", "$+.-_". 
*     Alle anderen Codes werden durch _xx dargestellt (_ und Hexcode).
*
*     HTML-4.0-Spec: "ID and NAME tokens must begin with a letter ([A-Za-z]) 
*     and may be followed by any number of letters, digits ([0-9]), hyphens ("-"),
*     underscores ("_"), colons (":"), and periods (".")."
*
*  Example:
*     "Ein Label" -> "Ein_20Label"
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void label2html(char *s)
{
	char *ptr, val[16];
	char one[2] = { 0, 0 };				/* hex value buffer */

	ptr = s;

	while (*ptr != EOS)
	{
		if (*ptr >= 'a' && *ptr <= 'z')
			goto LABEL2HTML_NEXT;
		if (*ptr >= 'A' && *ptr <= 'Z')
			goto LABEL2HTML_NEXT;
		if (*ptr >= '0' && *ptr <= '9')
			goto LABEL2HTML_NEXT;
		if (*ptr == '-')
			goto LABEL2HTML_NEXT;
		if (*ptr == '_')
			goto LABEL2HTML_NEXT;
		if (*ptr == ':')
			goto LABEL2HTML_NEXT;
		if (*ptr == '.')
			goto LABEL2HTML_NEXT;

		sprintf(val, "_%X", (_UBYTE) * ptr);
		one[0] = *ptr;
		replace_once(ptr, one, val);

	  LABEL2HTML_NEXT:
		ptr++;
	}

	/* Labelname muss mit einem Buchstaben beginnen (siehe Spec) */
	if (*s >= 'a' && *s <= 'z')
		return;
	if (*s >= 'A' && *s <= 'Z')
		return;
	strinsert(s, "UDO_");
}





/*******************************************************************************
*
*  node2winhelp():
*     adjust index names for WinHelp
*
*  Notes:
*     WinHelp mag keine Umlaute und Sonderzeichen in einer Referenz.
*     Leerzeichen werden durch Underscores ersetzt, alles andere durch Hexwerte.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2winhelp(char *n)
{
	char t[512];						/* buffer for converted node name */
	char v[32];							/* buffer for hex values */
	size_t i;

	if (n[0] == EOS)
		return;

	recode_chrtab(n, CHRTAB_ASCII);
	replace_udo_quotes(n);
	delete_all_divis(n);

	t[0] = EOS;
	for (i = 0; n[i] != '\0'; i++)
	{
		if ((n[i] >= '0' && n[i] <= '9') || (n[i] >= 'a' && n[i] <= 'z') || (n[i] >= 'A' && n[i] <= 'Z'))
		{
			chrcat(t, n[i]);
		} else if (n[i] == ' ' || n[i] == '_')
		{
			chrcat(t, '_');
		} else
		{
			sprintf(v, "_%X", (_UBYTE) n[i]);
			strcat(t, v);
		}
	}

	/*
	 * Workaround.
	 * Windows Help Compiler doesn't like
	 * longer names in the index
	 */
	if (strlen(t) > 80)
		t[81] = EOS;

	strcpy(n, t);
}





/*******************************************************************************
*
*  node2WinAutoID():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2WinAutoID(char *id, const char *n)
{
	char s[512];						/* buffer for name */
	size_t i;							/* pointer into name buffer */
	id[0] = EOS;						/* clear ID */

	if (n[0] == EOS)
		return;

	strcpy(s, n);
	recode_chrtab(s, CHRTAB_ANSI);
	recode_chrtab(s, CHRTAB_ASCII);
	replace_udo_quotes(s);
	delete_all_divis(s);

	id[0] = EOS;						/* clear ID  (again???) */
	for (i = 0; s[i] != '\0'; i++)		/* search for allowed characters */
	{
		if ((s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
		{
			chrcat(id, s[i]);
		}
	}
}





/*******************************************************************************
*
*  replace_2at_by_1at():
*     replace "@@" by "@"
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_2at_by_1at(char *s)
{
	qreplace_all(s, "@@", 2, "@", 1);
}





/*******************************************************************************
*
*  replace_1at_by_2at():
*     replace "@" by "@@"
*
*  Return:
*     -
*
******************************************|************************************/


GLOBAL void replace_1at_by_2at(char *s)
{
	qreplace_all(s, "@", 1, "@@", 2);
}





/*******************************************************************************
*
*  node2vision():
*     adjust characters for a Turbo Vision Help topic
*
*  Notes:
*     In einem Topic fuer Turbo Vision Help duerfen nur Zeichen vorkommen, 
*     die auch in C oder Pascal als Funktionsnamen erlaubt sind.
*
*
*     - genau wie bei node2winhelp
*     - Strings werden noch nicht gekuerzt
*     - <???> Testen, ob TVH mit langen Namen klarkommt
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2vision(char *n)
{
	char t[512];						/* buffer for topic string */
	char v[32];							/* buffer for hex values */
	size_t i;							/* pointer into string */

	if (n[0] == EOS)
		return;

	recode_chrtab(n, CHRTAB_ASCII);
	replace_udo_quotes(n);
	delete_all_divis(n);
	replace_udo_tilde(n);
	replace_udo_nbsp(n);

	t[0] = EOS;
	for (i = 0; i < strlen(n); i++)
	{
		if ((n[i] >= '0' && n[i] <= '9') || (n[i] >= 'a' && n[i] <= 'z') || (n[i] >= 'A' && n[i] <= 'Z'))
		{
			chrcat(t, n[i]);
		} else if (n[i] == ' ' || n[i] == '_')
		{
			chrcat(t, '_');
		} else
		{
			sprintf(v, "_%X", (_UBYTE) n[i]);
			strcat(t, v);
		}
	}

	strcpy(n, t);
}





/*******************************************************************************
*
*  node2texinfo():
*     adjust node name for Texinfo
*
*  Notes:
*     In einem @node duerfen bei Texinfo einige Zeichen nicht auftauchen. 
*     Diese werden entfernt.
*
*     Wenn der Titel hingegen keine alphanumerischen Zeichen enthaelt, 
*     so werden alle Zeichen im Titel durch Ascii/Hexcodes ersetzt.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2texinfo(char *s)
{
	size_t sl, i;
	char d[512], a[32], c;
	_BOOL has_an;						/* has_alphanumeric */

	if (s[0] == EOS)
		return;

	/* replace_udo_quotes(s); */
	delete_all_divis(s);

	qreplace_all(s, "@dots{}", 7, "...", 3);
	qreplace_all(s, "@minus{}", 8, "-", 1);

	sl = strlen(s);
	has_an = FALSE;

	for (i = 0; i < sl; i++)
	{
		c = s[i];

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
		{
			has_an = TRUE;
			break;
		}
	}

	if (has_an)
	{									/* Die folgenden Zeichen mag Info nicht in einem String */
		qdelete_all(s, ",", 1);
		qdelete_all(s, ";", 1);
		qdelete_all(s, ":", 1);
		qdelete_all(s, "'", 1);
		qdelete_all(s, "`", 1);
		qdelete_all(s, "\"", 1);
		qreplace_all(s, ")", 1, "29", 2);
		qreplace_all(s, "(", 1, "28", 2);

		/* Einen Punkt am Ende des Titels mag Info gar nicht */
		sl = strlen(s);
		while (sl > 0 && s[sl - 1] == '.')
		{
			s[sl - 1] = EOS;
			sl--;
		}

		qreplace_all(s, ". ", 2, ".", 1);

		/* Nun noch die doppelten Leerzeichen herausschmeissen */
		while (qreplace_all(s, "  ", 2, " ", 1))
			;
	} else
	{
		sl = strlen(s);
		strcpy(d, s);
		s[0] = EOS;

		for (i = 0; i < sl; i++)
		{
			sprintf(a, "%d-", d[i]);
			strcat(s, a);
		}
		/* Noch das letzte "-" entfernen */
		s[strlen(s) - 1] = EOS;
	}
}





/*******************************************************************************
*
*  c_tilde():
*     convert tilde and quoted tilde into internal sequences
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_tilde(char *s)
{
	qreplace_all(s, "!~", 2, TILDE_S, TILDE_S_LEN);
#if (NBSP_S_LEN==1)
	replace_char(s, '~', NBSP_C);
#else
	qreplace_all(s, "~", 1, NBSP_S, NBSP_S_LEN);
#endif
}





/*******************************************************************************
*
*  replace_udo_tilde():
*     replace UDO internal sequence by tilde command for target format 
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_udo_tilde(char *s)
{
	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		qreplace_all(s, TILDE_S, TILDE_S_LEN, "\\symbol{126}", 12);
		break;

	case TOLYX:
		qreplace_all(s, TILDE_S, TILDE_S_LEN, "~", 1);
		break;

	case TOLDS:
		qreplace_all(s, TILDE_S, TILDE_S_LEN, "&tilde;", 7);
		break;

	default:
#if (TILDE_S_LEN==1)
		replace_char(s, TILDE_C, '~');
#else
		qreplace_all(s, TILDE_S, TILDE_S_LEN, "~", 1);
#endif
		break;
	}
}





/*******************************************************************************
*
*  replace_udo_nbsp():
*     replace internal sequence by a non-breakable space for target format
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_udo_nbsp(char *s)
{
	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
#if (NBSP_S_LEN==1)
		replace_char(s, NBSP_C, '~');
#else
		qreplace_all(s, NBSP_S, NBSP_S_LEN, "~", 1);
#endif
		break;

	case TOLYX:
		qreplace_all(s, NBSP_S, NBSP_S_LEN, "\\protected_separator ", 21);
		break;

	case TOWIN:
	case TOWH4:
	case TORTF:
	case TOAQV:
		qreplace_all(s, NBSP_S, NBSP_S_LEN, "\\~", 2);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		qreplace_all(s, NBSP_S, NBSP_S_LEN, "&nbsp;", 6);
		break;

	case TOIPF:
		qreplace_all(s, NBSP_S, NBSP_S_LEN, "&rbl.", 5);
		break;

	default:
#if (NBSP_S_LEN==1)
		replace_char(s, NBSP_C, ' ');
#else
		qreplace_all(s, NBSP_S, NBSP_S_LEN, " ", 1);
#endif
		break;
	}
}





/*******************************************************************************
*
*  convert_tilde():
*     do the whole tilde conversion stuff
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void convert_tilde(char *s)
{
	c_tilde(s);
	replace_udo_tilde(s);
	replace_udo_nbsp(s);
}





/*******************************************************************************
*
*  c_divis():
*     convert UDO hyphen (!-) into an internal code
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_divis(char *s)
{
	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		qreplace_all(s, "!-", 2, "\\-", 2);
		break;

	case TOLYX:
		replace_all(s, "!-", "\\SpecialChar \\-\n");
		break;

	case TORTF:
		qreplace_all(s, "!-", 2, "\\-", 2);
		break;

	case TOSTG:
	case TOAMG:
	case TOASC:
	case TODRC:
	case TOMAN:
	case TONRO:
	case TOPCH:
	case TOSRC:
	case TOSRP:
		qreplace_all(s, "!-", 2, DIVIS_S, DIVIS_S_LEN);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		if (html_use_hyphenation)
			qreplace_all(s, "!-", 2, "&shy;", 5);
		else
			qdelete_all(s, "!-", 2);
		break;

	default:
		qdelete_all(s, "!-", 2);
		break;
	}
}



/*******************************************************************************
*
*  specials2ascii():
*     replace UDO special commands by their ASCII equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2ascii(char *s)
{
	qreplace_all(s, "!..", 3, "...", 3);

	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);

	qreplace_all(s, "---", 3, "-", 1);
	qreplace_all(s, "--", 2, "-", 1);

	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}





/*******************************************************************************
*
*  specials2html():
*     replace UDO special commands by their HTML equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2html(char *s)
{
	/* Doesn't work in CAB :-( */
	if (iEncodingTarget == CODE_TOS)
		qreplace_all(s, "!..", 3, "...", 3);
	else
		qreplace_all(s, "!..", 3, "&#x2026;", 8);
	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "&mdash;", 7);
	qreplace_all(s, "--", 2, "&ndash;", 7);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}





/*******************************************************************************
*
*  specials2ps():
*     replace UDO special commands by their PostScript equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2ps(char *s)
{
	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "\\230", 4);
	qreplace_all(s, "--", 2, "\\227", 4);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
	qreplace_all(s, "!..", 3, "\\214", 4);
}





/*******************************************************************************
*
*  specials2ipf():
*     replace UDO special commands by their IPF equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2ipf(char *s)
{
	qreplace_all(s, "!&per.&per.", 11, "&per.&per.&per.", 15);
	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "-", 1);
	qreplace_all(s, "--", 2, "-", 1);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}





/*******************************************************************************
*
*  specials2info():
*     replace UDO special commands by their Texinfo equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2info(char *s)
{
	qreplace_all(s, "!..", 3, "@dots{}", 7);
	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "@minus{}", 8);
	qreplace_all(s, "--", 2, "@minus{}", 8);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}





/*******************************************************************************
*
*  specials2win():
*     replace UDO special commands by their WinHelp equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2win(char *s)
{
	qreplace_all(s, "!..", 3, "\\'85", 4);

	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "\\'97", 4);
	qreplace_all(s, "--", 2, "\\'96", 4);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}

LOCAL void specials2win4(char *s)
{
	qreplace_all(s, "!..", 3, "{\\f1 \\'85}", 10);

	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "{\\f1 \\'97}", 10);
	qreplace_all(s, "--", 2, "{\\f1 \\'96}", 10);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}





/*******************************************************************************
*
*  specials2rtf():
*     replace UDO special commands by their RTF equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2rtf(char *s)
{
	qreplace_all(s, "!..", 3, "\\'85", 4);

	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "\\emdash", 7);
	qreplace_all(s, "--", 2, "\\endash", 7);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}





/*******************************************************************************
*
*  winspecials2ascii():
*     convert WinHelp special characters to ASCII notation
*
*  Notes:
*     The Search dialog of WinHelp doesn't show these special characters and 
*     typographical quotation marks properly.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void winspecials2ascii(char *s)
{
	qreplace_all(s, "\\'85", 4, "...", 3);
	qreplace_all(s, "\\'97", 4, "-", 1);
	qreplace_all(s, "\\'96", 4, "-", 1);

	qreplace_all(s, "\\'84", 4, "\"", 1);
	qreplace_all(s, "\\'93", 4, "\"", 1);
	qreplace_all(s, "\\'94", 4, "\"", 1);
}





/*******************************************************************************
*
*  texvar2ascii():
*     replace LaTeX output placeholders by their ASCII equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void texvar2ascii(char *s)
{
	if (strstr(s, "(!") == NULL)
		return;

	qreplace_all(s, "(!TeX)", 6, "TeX", 3);
	qreplace_all(s, "(!LaTeX)", 8, "LaTeX", 5);
	qreplace_all(s, "(!LaTeXe)", 9, "LaTeX2e", 7);
	qreplace_all(s, "(!copyright)", 12, "(c)", 3);
	qreplace_all(s, "(!registered)", 13, "(r)", 3);
	qreplace_all(s, "(!alpha)", 8, "alpha", 5);
	qreplace_all(s, "(!beta)", 7, "beta", 4);
	qreplace_all(s, "(!euro)", 7, "EUR", 3);
	qreplace_all(s, "(!pound)", 8, "GBP", 3);
	qreplace_all(s, "(!reg)", 6, "(r)", 3);
	qreplace_all(s, "(!tm)", 5, "(tm)", 4);
	replace_all(s, "(!deg)", get_lang()->degree);
}





/*******************************************************************************
*
*  c_rtf_quotes():
*     adjust RTF quotes
*
*  Notes:
*     This function replaces "\rquote " by "\rquote  " (regard the double space),
*     when no space follows in the text stream. A space is strictly required to
*     exist directly before a line is output in RTF.
*
*     The reason for this is c_vars() which is called before str2tok(), which 
*     causes the loss of the last space when the line is composed in token_output().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_rtf_quotes(char *s)
{
	qreplace_all(s, "\\lquote", 7, "\\lquote ", 8);
	qreplace_all(s, "\\ldblquote", 10, "\\ldblquote ", 11);

	qreplace_all(s, "\\rquote", 7, "\\rquote ", 8);
	qreplace_all(s, "\\rdblquote", 10, "\\rdblquote ", 11);

	qreplace_all(s, "\\emdash", 7, "\\emdash ", 8);
	qreplace_all(s, "\\endash", 7, "\\endash ", 8);
}





/*******************************************************************************
*
*  c_quotes_apostrophes():
*     replace single or double quotation marks from UDO format to system quotation marks
*
*  Parameters:
*    aon : opening single quote
*    aoff: closing single quote
*    qon : opening double quote
*    qoff: closing single quote
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_quotes_apostrophes(char *s, const char *aon, const char *aoff, const char *qon, const char *qoff)
{
	if (no_quotes)
	{
		qreplace_all(s, "\"\"", 2, "\"", 1);
		qreplace_all(s, "''", 2, "'", 1);
	} else
	{
		while (strstr(s, "''") != NULL)
		{
			b1stApost = !b1stApost;
			replace_once(s, "''", b1stApost ? aon : aoff);
		}

		while (strstr(s, "\"\"") != NULL)
		{
			b1stQuote = !b1stQuote;
			replace_once(s, "\"\"", b1stQuote ? qon : qoff);
		}
	}
}





/*******************************************************************************
*
*  c_vars():
*     replace pre-defined placeholders and special strings, like:
*     "", '', !.., or (--)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_vars(char *s)
{
	char *str;
	char cbuf[8];
	const char *repl;

	if ((repl = strstr(s, "(!")) != NULL)
	{
		replace_all(s, "(!today)", get_lang()->today);
		replace_all(s, "(!short_today)", get_lang()->short_today);
	}

	/* === quotation marks === */

	qreplace_all(s, "(\"\")", 4, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "('')", 4, TEMPO_S2, TEMPO_S2_LEN);

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		switch (destlang)
		{
		case TOGER:
			c_quotes_apostrophes(s, "`", "'", "\"`", "\"'");
			break;
		default:
			c_quotes_apostrophes(s, "`", "'", "``", "''");
			break;
		}
		qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\\symbol{34}\\symbol{34}", 22);
		qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "\\symbol{39}\\symbol{39}", 22);
		break;

	case TOLYX:
		switch (destlang)
		{
		case TOGER:
			c_quotes_apostrophes(s,
								 "'", "'",
								 "\\begin_inset" INDENT_S "Quotes" INDENT_S "gld\\end_inset" INDENT_S,
								 "\\begin_inset" INDENT_S "Quotes" INDENT_S "grd\\end_inset" INDENT_S);
			break;
		case TOFRA:
			c_quotes_apostrophes(s,
								 "'", "'",
								 "\\begin_inset" INDENT_S "Quotes" INDENT_S "fld\\end_inset" INDENT_S,
								 "\\begin_inset" INDENT_S "Quotes" INDENT_S "frd\\end_inset" INDENT_S);
			break;
		default:
			c_quotes_apostrophes(s,
								 "'", "'",
								 "\\begin_inset" INDENT_S "Quotes" INDENT_S "eld\\end_inset" INDENT_S,
								 "\\begin_inset" INDENT_S "Quotes" INDENT_S "erd\\end_inset" INDENT_S);
			break;
		}
		replace_all(s, TEMPO_S,
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"symbol{34}" INDENT_S "\\backslash" INDENT_S "symbol{34}\\end_inset" INDENT_S);
		replace_all(s, TEMPO_S2,
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"symbol{39}" INDENT_S "\\backslash" INDENT_S "symbol{39}\\end_inset" INDENT_S);
		break;

	case TORTF:
		/* Ohne schliessende Leerzeichen, damit nicht Tokens daraus werden! */
		/* Die Leerzeichen werden in c_rtf_quotes() hinzugefuegt! */
		c_quotes_apostrophes(s, "\\lquote", "\\rquote", "\\ldblquote", "\\rdblquote");
		qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
		qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
		break;

	case TOWIN:
	case TOAQV:
		switch (destlang)
		{
		case TOGER:
			c_quotes_apostrophes(s, "{\\'91}", "{\\'92}", "{\\'84}", "{\\'93}");
			break;
		default:
			c_quotes_apostrophes(s, "\\'91", "\\'92", "\\'93", "\\'94");
			break;
		}
		qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
		qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
		break;

	case TOLDS:
		c_quotes_apostrophes(s, "`", "'", "``", "''");
		qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
		qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
		break;

	case TOHPH:
		c_quotes_apostrophes(s, "`", "'", "<quote>", "<\\quote>");
		qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
		qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		switch (html_quotes)
		{
		case QUOTES_CLASSIC:
			c_quotes_apostrophes(s, "`", "'", "&quot;", "&quot;");
			break;
		case QUOTES_TAGS:
		default:
			c_quotes_apostrophes(s, "`", "'", "<q>", "</q>");
			break;
		}
		qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "&quot;&quot;", 12);
		qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
		break;

	case TOKPS:
		switch (destlang)
		{
		case TOGER:					/* according to table in ud2ps.h */
			c_quotes_apostrophes(s, "\\220", "\\221", "\\226", "\\225");
			break;
		case TOFRA:					/* according to table in ud2ps.h */
			c_quotes_apostrophes(s, "\\222", "\\223", "\\253", "\\273");
			break;
		case TONOR:
			c_quotes_apostrophes(s, "\\<", "\\>", "\\\\\\(", "\\\\\\)");
			break;
		default:
			c_quotes_apostrophes(s, "'", "'", "\"", "\"");
			break;
		}
		qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
		qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
		break;

	default:
		c_quotes_apostrophes(s, "`", "'", "\"", "\"");
		qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
		qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
		break;
	}


	/* === Miscellaneous === */

	switch (desttype)
	{
	case TOTEX:
	case TOPDL:
		qreplace_all(s, "!..", 3, "\\ldots{}", 8);
		qreplace_all(s, "(---)", 5, "-{}-{}-", 7);
		qreplace_all(s, "(--)", 4, "-{}-", 4);
		/*
		 * this used to replace "(!grin)" with "\\verb+;-)+",
		 * but that doesnt work if it is used together
		 * with text attributes like (!B)
		 */
		/* str = um_strdup_printf("\\verb%c;-)%c", cTexVerb, cTexVerb); */
		str = strdup(";-)");
		replace_all(s, "(!grin)", str);
		free(str);
		/* str = um_strdup_printf("\\verb%c:-)%c", cTexVerb, cTexVerb); */
		str = strdup(":-)");
		replace_all(s, "(!laugh)", str);
		free(str);
		qreplace_all(s, "(!TeX)", 6, "\\TeX{}", 6);
		qreplace_all(s, "(!LaTeX)", 8, "\\LaTeX{}", 8);
		qreplace_all(s, "(!LaTeXe)", 9, "\\LaTeXe{}", 9);
		qreplace_all(s, "(!copyright)", 12, "\\copyright{}", 12);
		qreplace_all(s, "(!registered)", 13, "\\textregistered{}", 17);
		qreplace_all(s, "(!alpha)", 8, "$\\alpha$", 8);
		qreplace_all(s, "(!beta)", 7, "$\\beta$", 7);
		qreplace_all(s, "(!euro)", 7, "\\euro{}", 7);
		qreplace_all(s, "(!pound)", 8, "\\pounds{}", 9);
		qreplace_all(s, "(!reg)", 6, "\\textregistered{}", 17);
		qreplace_all(s, "(!tm)", 5, "\\texttrademark{}", 16);
		qreplace_all(s, "(!deg)", 6, "$^{o}$", 6);
		break;

	case TOLYX:
		replace_all(s, "!..", "\\SpecialChar" INDENT_S "\\ldots{}" INDENT_S);
		replace_all(s, "(---)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "-{}-{}-\\end_inset"
					INDENT_S);
		replace_all(s, "(--)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "-{}-\\end_inset"
					INDENT_S);
		replace_all(s, "(!grin)", "\\family" INDENT_S "typewriter" INDENT_S ";-)\\family" INDENT_S "default" INDENT_S);
		replace_all(s, "(!laugh)", "\\family" INDENT_S "typewriter" INDENT_S ":-)\\family" INDENT_S "default" INDENT_S);
		replace_all(s, "(!TeX)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"TeX\\end_inset" INDENT_S);
		replace_all(s, "(!LaTeX)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"LaTeX\\end_inset" INDENT_S);
		replace_all(s, "(!LaTeXe)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"LaTeXe\\end_inset" INDENT_S);
		replace_all(s, "(!copyright)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"copyright\\end_inset" INDENT_S);
		replace_all(s, "(!registered)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"textregistered\\end_inset" INDENT_S);
		replace_all(s, "(!alpha)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "$" INDENT_S
					"\\backslash" INDENT_S "alpha$\\end_inset" INDENT_S);
		replace_all(s, "(!beta)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "$" INDENT_S
					"\\backslash" INDENT_S "beta$\\end_inset" INDENT_S);
		replace_all(s, "(!euro)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"euro\\end_inset" INDENT_S);
		replace_all(s, "(!pound)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"pounds\\end_inset" INDENT_S);
		replace_all(s, "(!reg)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"textregistered\\end_inset" INDENT_S);
		replace_all(s, "(!tm)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "\\backslash" INDENT_S
					"texttrademark\\end_inset" INDENT_S);
		replace_all(s, "(!deg)",
					"\\begin_inset" INDENT_S "ERT" INDENT_S "status" INDENT_S "Inlined" INDENT_S "$^{o}$\\end_inset"
					INDENT_S);
		break;

	case TOINF:
		qreplace_all(s, "(!grin)", 7, "@code{;-)}", 10);
		qreplace_all(s, "(!laugh)", 8, "@code{:-)}", 10);
		qreplace_all(s, "(!TeX)", 6, "@TeX{}", 6);
		qreplace_all(s, "(!copyright)", 12, "@copyright{}", 12);
		specials2info(s);
		texvar2ascii(s);
		break;

	case TOSTG:
	case TOAMG:
	case TOPCH:
		repl = unicode2char(U_CopyrightSign, cbuf);
		replace_all(s, "(!copyright)", repl);
		repl = unicode2char(U_RegisteredSign, cbuf);
		replace_all(s, "(!registered)", repl);
		replace_all(s, "(!reg)", repl);
		qreplace_all(s, "(!grin)", 7, ";-)", 3);
		qreplace_all(s, "(!laugh)", 8, ":-)", 3);
		repl = unicode2char(U_GreekSmallLetterAlpha, cbuf);
		if (*repl == '\0')
			repl = "alpha";
		replace_all(s, "(!alpha)", repl);
		repl = unicode2char(U_GreekSmallLetterBeta, cbuf);
		if (*repl == '\0')
			repl = unicode2char(U_LatinSmallLetterSharpS, cbuf);
		if (*repl == '\0')
			repl = "beta";
		replace_all(s, "(!beta)", repl);
		specials2ascii(s);
		texvar2ascii(s);
		break;

	case TOKPS:
		repl = unicode2char(U_CopyrightSign, cbuf);
		replace_all(s, "(!copyright)", repl);
		repl = unicode2char(U_RegisteredSign, cbuf);
		replace_all(s, "(!registered)", repl);
		replace_all(s, "(!reg)", repl);
		qreplace_all(s, "(!grin)", 7, ";-\\)", 4);
		qreplace_all(s, "(!laugh)", 8, ":-\\)", 4);
		repl = unicode2char(U_GreekSmallLetterAlpha, cbuf);
		if (*repl == '\0')
			repl = "alpha";
		replace_all(s, "(!alpha)", repl);
		repl = unicode2char(U_GreekSmallLetterBeta, cbuf);
		if (*repl == '\0')
			repl = unicode2char(U_LatinSmallLetterSharpS, cbuf);
		if (*repl == '\0')
			repl = "beta";
		replace_all(s, "(!beta)", repl);
		qreplace_all(s, "(!euro)", 7, "\\200", 4);
		qreplace_all(s, "(!pound)", 8, "\\243", 4);
		qreplace_all(s, "(!tm)", 5, "\\215", 4);
		qreplace_all(s, "(!deg)", 6, "\\201", 4);
		specials2ps(s);
		texvar2ascii(s);
		break;

	case TOASC:
	case TODRC:
	case TOMAN:
	case TONRO:
	case TOTVH:
	case TOSRC:
	case TOSRP:
		qreplace_all(s, "(!grin)", 7, ";-)", 3);
		qreplace_all(s, "(!laugh)", 8, ":-)", 3);
		repl = unicode2char(U_GreekSmallLetterAlpha, cbuf);
		if (*repl == '\0')
			repl = "alpha";
		replace_all(s, "(!alpha)", repl);
		repl = unicode2char(U_GreekSmallLetterBeta, cbuf);
		if (*repl == '\0')
			repl = unicode2char(U_LatinSmallLetterSharpS, cbuf);
		if (*repl == '\0')
			repl = "beta";
		replace_all(s, "(!beta)", repl);
		specials2ascii(s);
		texvar2ascii(s);
		break;

	case TOIPF:
		qreplace_all(s, "(!grin)", 7, ";-)", 3);
		qreplace_all(s, "(!laugh)", 8, "&colon.-)", 9);
		repl = unicode2char(U_GreekSmallLetterAlpha, cbuf);
		if (*repl == '\0')
			repl = "alpha";
		replace_all(s, "(!alpha)", repl);
		repl = unicode2char(U_GreekSmallLetterBeta, cbuf);
		if (*repl == '\0')
			repl = unicode2char(U_LatinSmallLetterSharpS, cbuf);
		if (*repl == '\0')
			repl = "beta";
		replace_all(s, "(!beta)", repl);
		specials2ipf(s);
		texvar2ascii(s);
		break;

	case TORTF:
		qreplace_all(s, "(!grin)", 7, "{\\f1 ;-)}", 9);
		qreplace_all(s, "(!laugh)", 8, "{\\f1 :-)}", 9);
		qreplace_all(s, "(!alpha)", 8, "{\\f3 a}", 7);
		qreplace_all(s, "(!beta)", 7, "{\\f3 b}", 7);
		qreplace_all(s, "(!copyright)", 12, "\\'A9", 4);
		qreplace_all(s, "(!registered)", 13, "\\'AE", 4);
		qreplace_all(s, "(!euro)", 7, "\\'80", 4);
		qreplace_all(s, "(!pound)", 8, "\\'A3", 4);
		qreplace_all(s, "(!reg)", 6, "\\'AE", 4);
		qreplace_all(s, "(!tm)", 5, "\\'99", 4);
		qreplace_all(s, "(!deg)", 6, "\\'B0", 4);
		specials2rtf(s);
		texvar2ascii(s);
		break;

	case TOWIN:
	case TOAQV:
		qreplace_all(s, "(!grin)", 7, "{\\f1 ;-)}", 9);
		qreplace_all(s, "(!laugh)", 8, "{\\f1 :-)}", 9);
		qreplace_all(s, "(!alpha)", 8, "{\\f3 a}", 7);
		qreplace_all(s, "(!beta)", 7, "{\\f3 b}", 7);
		qreplace_all(s, "(!copyright)", 12, "\\'A9", 4);
		qreplace_all(s, "(!registered)", 13, "\\'AE", 4);
		qreplace_all(s, "(!euro)", 7, "\\'80", 4);
		qreplace_all(s, "(!pound)", 8, "\\'A3", 4);
		qreplace_all(s, "(!reg)", 6, "\\'AE", 4);
		qreplace_all(s, "(!tm)", 5, "\\'99", 4);
		qreplace_all(s, "(!deg)", 6, "\\'B0", 4);
		specials2win(s);
		texvar2ascii(s);
		break;

	case TOWH4:
		qreplace_all(s, "(!grin)", 7, "{\\f1 ;-)}", 9);
		qreplace_all(s, "(!laugh)", 8, "{\\f1 :-)}", 9);
		qreplace_all(s, "(!alpha)", 8, "{\\f3 a}", 7);
		qreplace_all(s, "(!beta)", 7, "{\\f3 b}", 7);
		qreplace_all(s, "(!copyright)", 12, "\\'A9", 4);
		qreplace_all(s, "(!registered)", 13, "\\'AE", 4);
		qreplace_all(s, "(!euro)", 7, "\\'80", 4);
		qreplace_all(s, "(!pound)", 8, "\\'A3", 4);
		qreplace_all(s, "(!reg)", 6, "\\'AE", 4);
		qreplace_all(s, "(!tm)", 5, "\\'99", 4);
		qreplace_all(s, "(!deg)", 6, "\\'B0", 4);
		specials2win4(s);
		texvar2ascii(s);
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		qreplace_all(s, "(!grin)", 7, "<TT>;-)</TT>", 12);
		qreplace_all(s, "(!laugh)", 8, "<TT>:-)</TT>", 12);
		qreplace_all(s, "(!copyright)", 12, "&copy;", 6);
		qreplace_all(s, "(!registered)", 13, "&#174;", 6);
		qreplace_all(s, "(!euro)", 7, "&euro;", 6);
		qreplace_all(s, "(!pound)", 8, "&pound;", 7);
		qreplace_all(s, "(!reg)", 6, "&#174;", 6);
		qreplace_all(s, "(!tm)", 5, "&#8482;", 7);
		qreplace_all(s, "(!deg)", 6, "&#176;", 6);
		qreplace_all(s, "(!alpha)", 8, "&#x3B1;", 7);
		qreplace_all(s, "(!beta)", 7, "&#x3B2;", 7);
		specials2html(s);
		texvar2ascii(s);
		break;

	case TOLDS:
		qreplace_all(s, "(!grin)", 7, "<tt/;-)/", 8);
		qreplace_all(s, "(!laugh)", 8, "<tt/:-)/", 8);
		specials2ascii(s);
		texvar2ascii(s);
		break;

	case TOHPH:
		qreplace_all(s, "(!grin)", 7, "<ex>;-)<\\ex>", 12);
		qreplace_all(s, "(!laugh)", 8, "<ex>:-)<\\ex>", 12);
		specials2ascii(s);
		texvar2ascii(s);
		break;
	}
}



/*******************************************************************************
*
*  str2manbold():
*     adjust internal text style effect 'bold' for Manualpages
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void str2manbold(char *d, const char *s)
{
	size_t i;
	char c[2] = { 0, 0 };				/* char buffer */

	d[0] = EOS;							/* clear result string */

	if (s[0] == EOS)
		return;

	for (i = 0; i < strlen(s); i++)
	{
		c[0] = s[i];
		strcat(d, c);
		strcat(d, "\010");
		strcat(d, c);
	}
}





/*******************************************************************************
*
*  str2manunder():
*     adjust internal text style effect 'underlined' for Manualpages
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void str2manunder(char *d, const char *s)
{
	size_t i;
	char c[2] = { 0, 0 };				/* char buffer */

	d[0] = EOS;							/* clear result string */

	if (s[0] == EOS)
		return;

	for (i = 0; i < strlen(s); i++)
	{
		strcat(d, "_\010");
		c[0] = s[i];
		strcat(d, c);
	}
}





/*******************************************************************************
*
*  c_man_styles():
*     convert Manualpages styles (bold + underlined)
*
*  Notes:
*     ptr does always point to the first char of the ESC_STYLE_MAGIC (\033\001).
*     UDO replaces commands like (!B) by its own Escape commands first,
*     formatted as ESC-001-xxx-ESC, where xxx is the relevant style.
*  
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_man_styles(char *s)
{
	char *ptr;							/* ESC_STYLE_MAGIC in string */
	char alt[512];
	char neu[512];

	char *start;						/* buffer for start of style in string */
	char s_char[2] = { 0, 0 };
	_BOOL bold_active;					/* TRUE: bold style on, FALSE: bold style off */

	_BOOL under_active;					/* TRUE: underlined on, FALSE: underlined off */
	_BOOL replace_it;

	if (s[0] == EOS)
		return;

	bold_active = styleflag.bold;
	under_active = styleflag.underlined;
	replace_it = FALSE;

	ptr = strstr(s, ESC_STYLE_MAGIC);
	if (ptr == NULL)					/* no style found */
		return;

	start = ptr;

	alt[0] = EOS;

	do
	{
		if (ptr[0] != ESC_STYLE_MAGIC[0] && ptr[0] != ESC_STYLE_MAGIC[1])
		{
			if (bold_active || under_active)
			{
				s_char[0] = ptr[0];
				strcat(alt, s_char);
			}
		} else if (ptr[0] == ESC_STYLE_MAGIC[0] && ptr[1] == ESC_STYLE_MAGIC[1])
		{
			switch (ptr[2])
			{
			case C_BOLD_ON:
				bold_active = TRUE;
				alt[0] = EOS;
				ptr += 3;
				start = ptr + 1;
				break;

			case C_BOLD_OFF:
				bold_active = FALSE;
				ptr += 3;
				str2manbold(neu, alt);
				replace_it = TRUE;
				break;

			case C_UNDER_ON:
				under_active = TRUE;
				alt[0] = EOS;
				ptr += 3;
				start = ptr + 1;
				break;

			case C_UNDER_OFF:
				under_active = FALSE;
				ptr += 3;
				str2manunder(neu, alt);
				replace_it = TRUE;
				break;
			}
		}

		if (replace_it)
		{
			replace_once(start, alt, neu);
			ptr += (strlen(neu) - strlen(alt));
			alt[0] = EOS;
			replace_it = FALSE;
		}

		ptr++;
	} while (ptr[0] != EOS);
}





/*******************************************************************************
*
*  auto_quote_chars():
*     convert special characters for relevant target encodings
*  
*  return:
*     -
*
******************************************|************************************/

GLOBAL void auto_quote_chars(char *s, _BOOL all)
{
	register int i, j;
	int len;							/* indicates length of found Unicode char */
	_UWORD idx;
	const _UWORD *pUtrg;				/* encoding table for target encoding */
	char *ptr;							/* position in string s */
	char *oldptr;						/* buffer for ptr */
	const char *ptr_quoted;
	char s_temp[32];
	char s_buf[32];
	char s_char[2];
	_BOOL aqc_verb;
	_BOOL found = FALSE;

	size_t cmplen, sl_verb_on, sl_verb_off;

	if (s[0] == EOS)
		return;

	pUtrg = chr_codepage(iEncodingTarget);	/* get the right encoding table! */

	if (no_umlaute)
		recode_chrtab(s, CHRTAB_ASCII);

	switch (desttype)
	{
	case TOASC:						/* Hier muss nicht gequotet werden! */
	case TODRC:
	case TOMAN:
	case TONRO:
	case TOSTG:
	case TOAMG:
	case TOTVH:
	case TOINF:
	case TOSRC:
	case TOSRP:
		if (bDocUniversalCharsetOn)
			recode_udo(s);

		switch (desttype)
		{
		case TOSTG:					/* ST-Guide */
			/*
			 * wrong place. doing that here
			 * - requires us to undo this replacement in each and every stg command
			 * - causes wrong calculations in table output
			 * - prevents autoreferences from working
			 * - prevents !index command from working
			 * ...
			 */
#if 0
			replace_1at_by_2at(s);
#endif
			break;

		case TOINF:
			qreplace_all(s, "@", 1, "@@", 2);
			qreplace_all(s, "}", 1, "@}", 2);
			qreplace_all(s, "{", 1, "@{", 2);
			break;

		case TOTVH:
			qreplace_all(s, "{", 1, "{{", 2);
			break;
		}
		return;
	}

	ptr = s;

	if (!all)
	{
		/* Wenn in der Zeile ein Kommando steht, dann nur den Rest */
		/* quoten, wenn das Kommando einen Parameter enthaelt, */
		/* der gequotet werden muss! */
		if (s[0] == META_C && s[1] >= 'a' && s[1] <= 'z')
		{
			for (i = 0; i < (int) MAXQUOTECMD; i++)
			{
				cmplen = quotecommand[i].cmdlen;
				if (strncmp(s, quotecommand[i].cmd, cmplen) == 0)
				{
					/* Das naechste Zeichen muss aber Space oder Tab sein! */
					if (s[cmplen] == ' ' || s[cmplen] == '\t')
					{
						found = TRUE;
						ptr += cmplen;
						break;
					}
				}

				if ((cmplen = quotecommand[i].abblen) > 0)
				{
					/* Abkuerzungen auch beachten */
					if (strncmp(s, quotecommand[i].abb, cmplen) == 0)
					{
						/* Das naechste Zeichen muss aber Space oder Tab sein! */
						if (s[cmplen] == ' ' || s[cmplen] == '\t')
						{
							found = TRUE;
							ptr += cmplen;
							break;
						}
					}
				}
			}

			if (!found)
				return;

			if (found)
			{							/* don't quote content inside [] */
				if (quotecommand[i].skip_brackets)
				{
					while (*ptr && *ptr != ']')
						ptr++;
				}
			}
		}
	}

	ptr_quoted = NULL;
	s_temp[0] = EOS;
	s_char[1] = EOS;
	aqc_verb = last_aqc_verb;

	sl_verb_on = CMD_STYLELEN;
	sl_verb_off = CMD_STYLELEN;
	while (ptr[0] != EOS)
	{
		/* Innerhalb (!V)...(!v) Leerzeichen durch interne  */
		/* feste Leerzeichen ersetzen, damit token_output() nicht */
		/* \verb+...+ umbricht. */
		if (desttype == TOTEX || desttype == TOPDL)
		{
			if (aqc_verb || styleflag.verbatim)
			{
				if (ptr[0] == ' ')
				{
					ptr[0] = INDENT_C;
					goto NO_QUOTE_NEEDED;
				}
			}
		}

		/* Das Alphabet und die Ziffern muessen nie gequotet werden! */
		/* Also einfach den ganzen Rotz ueberspringen */
		if (ptr[0] == ' ')				/* space */
			goto NO_QUOTE_NEEDED;
		if (ptr[0] >= 'a' && ptr[0] <= 'z')	/* [a..z] */
			goto NO_QUOTE_NEEDED;
		if (ptr[0] >= 'A' && ptr[0] <= 'Z')	/* [A..Z] */
			goto NO_QUOTE_NEEDED;
		if (ptr[0] >= '0' && ptr[0] <= '9')	/* [0..9] */
			goto NO_QUOTE_NEEDED;

		if ((desttype == TOTEX || desttype == TOPDL) && !all)
		{
			if (strncmp(ptr, CMD_VERB_ON, sl_verb_on) == 0)
			{
				/* Optimierung durch Hochzaehlen von ptr */
				aqc_verb = TRUE;
				ptr += (sl_verb_on - 1);
				goto NO_QUOTE_NEEDED;
			}

			if (strncmp(ptr, CMD_VERB_OFF, sl_verb_off) == 0)
			{
				/* Optimierung durch Hochzaehlen von ptr */
				aqc_verb = FALSE;
				ptr += (sl_verb_off - 1);
				goto NO_QUOTE_NEEDED;
			}
		}

		/* Sonderbehandlung fuer doppelte Anfuehrungszeichen und Apostrophe */
		if (ptr[0] == '\"' && ptr[1] == '\"')
		{
			/* Doppelquotes: "" */
			ptr++;
			goto NO_QUOTE_NEEDED;
		}

		/* Gequotete Quotes: ("") */
		if (ptr[0] == '(' && ptr[1] == '\"' && ptr[2] == '\"' && ptr[3] == ')')
		{
			ptr += 3;
			goto NO_QUOTE_NEEDED;
		}

		/* Gequotete Apostrophe: ('') */
		if (ptr[0] == '(' && ptr[1] == '\'' && ptr[2] == '\'' && ptr[3] == ')')
		{
			ptr += 3;
			goto NO_QUOTE_NEEDED;
		}

		/* Sonderbehandlung fuer Platzhalter, welche spaeter */
		/* gequotet werden (macro, define, link, index) */
		/* aber nicht in verbatim-Umgebungen! */

		/* Dabei beruecksichtigen, dass Klammern innerhalb */
		/* durch ein Ausrufungszeichen gequotet werden. */

		if (pflag[PASS2].env != ENV_VERBATIM)
		{
			if (ptr[0] == '(' && ptr[1] == META_C && ptr[2] != QUOTE_C)
			{
				oldptr = ptr;			/* Pointer sichern */
				ptr++;

				while (ptr[0] != EOS && ptr[0] != ')')
				{
					if (ptr[0] == '!' && ptr[1] == ')')
					{
						ptr++;			/* gequotete Klammer ueberspringen */
					}
					ptr++;
				}

				if (ptr[0] == EOS)
				{
					/* Falls der Pointer auf das Ende zeigt, dann */
					/* ist etwas schiefgelaufen oder aber es handelte */
					/* sich gar nicht um einen Parameter (z.B. "(!)") */
					/* In dem Falle den alten Pointer restaurieren */
					ptr = oldptr;
					ptr++;
				} else
				{
					/* Optimierung: Rest ueberspringen */
					goto NO_QUOTE_NEEDED;
				}
			}
		}

		switch (desttype)
		{
		case TOTEX:
		case TOPDL:
			if (all || (!styleflag.verbatim && !aqc_verb))
			{
				found = FALSE;

				idx = (_UBYTE) * ptr;

				if (idx > 127)
				{
					if (!pUtrg)			/* target is Unicode */
					{
						idx = utf8_to_uchar(ptr, &len);
						ptr += len - 1;
						goto NO_QUOTE_NEEDED;	/* we're already done */
					}

					j = 0;

					/* check for end of table! */
					while (chrtab[j].uname != U_NIL)
					{
						/* identical Unicode name found! */
						if (chrtab[j].uname == pUtrg[idx])
						{
							if (chrtab[j].tex[0] != EOS)
							{
								ptr_quoted = chrtab[j].tex;
								found = TRUE;
								break;
							}
						}

						j++;
					}
				} else
				{
					for (i = 0; i < MAXTEX7BIT; i++)
					{
						if (ptr[0] == tex7bit[i].c)
						{
							ptr_quoted = tex7bit[i].quoted;
							found = TRUE;
							break;
						}
					}
				}

				if (!found)
				{
					if (idx >= 127)
					{
						warning_message(_("%x maybe not available in LaTeX"), idx);
						sprintf(s_temp, "$\\symbol{%d}$", idx);
						ptr_quoted = s_temp;
					}
				}
			}
			break;

		case TOLYX:
			found = FALSE;
			for (i = 0; i < MAXLYX7BIT; i++)
			{
				if (ptr[0] == lyx7bit[i].c)
				{
					ptr_quoted = lyx7bit[i].quoted;
					found = TRUE;
					break;
				}
			}
			break;

		case TOIPF:
			found = FALSE;
			for (i = 0; i < MAXIPF7BIT; i++)
			{
				if (ptr[0] == ipf7bit[i].c)
				{
					ptr_quoted = ipf7bit[i].quoted;
					found = TRUE;
					break;
				}
			}
			break;

		case TORTF:
			found = FALSE;
			idx = (_UBYTE) * ptr;		/* get value of current char */
			if (idx > 127)
			{
				if (!pUtrg)				/* target is Unicode */
				{
					/* find Unicode codepoint */
					idx = utf8_to_uchar(ptr, &len);

					/* format it for RTF (format "\uN" where N is decimal) */
					sprintf(s_temp, "\\u%u", idx);

					ptr_quoted = s_temp;	/* set ^ to temp string */

					strncpy(s_buf, ptr, len);	/* copy all used Unicode bytes from line to another buffer */
					s_buf[len] = 0;		/* close C string */

					cmplen = strlen(ptr_quoted);
					/* exchange character by RTF Unicode command */
					qreplace_once(ptr, s_buf, len, ptr_quoted, cmplen);

					ptr_quoted = NULL;	/* reset ^ */
					ptr += cmplen - 1;	/* adjust string ^ */

					goto NO_QUOTE_NEEDED;	/* we're already done */
				}

				j = 0;
				/* check for end of table! */
				while (chrtab[j].uname != U_NIL)
				{
					/* identical Unicode name found! */
					if (chrtab[j].uname == pUtrg[idx])
					{
						if (chrtab[j].rtf[0] != EOS)
						{
							ptr_quoted = chrtab[j].rtf;
							found = TRUE;
							break;
						}
					}

					j++;
				}

				if (!found)
				{
					warning_cannot_recode(idx, chr_codepage_name(iEncodingSource), chr_codepage_name(iEncodingTarget));
					sprintf(s_temp, "\\'%X", idx);
					ptr_quoted = s_temp;
				}
			} else
			{
				for (i = 0; i < MAXRTF7BIT; i++)
				{
					if (ptr[0] == rtf7bit[i].c)
					{
						ptr_quoted = rtf7bit[i].quoted;
						found = TRUE;
						break;
					}
				}
				if (!found && idx < 0x20)
				{
					warning_cannot_recode(idx, chr_codepage_name(iEncodingSource), chr_codepage_name(iEncodingTarget));
					sprintf(s_temp, "\\'%X", idx);
					ptr_quoted = s_temp;
				}
			}
			break;

		case TOKPS:
			found = FALSE;
			idx = (_UBYTE) * ptr;

			if (idx > 127)
			{
				j = 0;

				/* check for end of table! */
				while (chrtab[j].uname != U_NIL)
				{
					/* identical Unicode name found! */
					if (pUtrg && chrtab[j].uname == pUtrg[idx])
					{
						if (chrtab[j].ps[0] != EOS)
						{
							ptr_quoted = chrtab[j].ps;
							found = TRUE;
							break;
						}
					}

					j++;
				}

				if (!found)
				{
					warning_cannot_recode(idx, chr_codepage_name(iEncodingSource), chr_codepage_name(iEncodingTarget));
					sprintf(s_temp, "\\%03o", idx);
					ptr_quoted = s_temp;
				}
			}
			break;

		case TOWIN:
		case TOWH4:
		case TOAQV:
			found = FALSE;

			idx = (_UBYTE) * ptr;

			if (idx > 127)
			{
				j = 0;

				/* check for end of table! */
				while (chrtab[j].uname != U_NIL)
				{
					/* identical Unicode name found! */
					if (pUtrg && chrtab[j].uname == pUtrg[idx])
					{
						if (chrtab[j].rtf[0] != EOS)
						{
							ptr_quoted = chrtab[j].rtf;
							found = TRUE;
							break;
						}
					}

					j++;
				}

				if (!found)
				{
					warning_cannot_recode(idx, chr_codepage_name(iEncodingSource), chr_codepage_name(iEncodingTarget));
					sprintf(s_temp, "\\'%X", idx);
					ptr_quoted = s_temp;
				}
			} else
			{
				for (i = 0; i < MAXWIN7BIT; i++)
				{
					if (ptr[0] == win7bit[i].c)
					{
						ptr_quoted = win7bit[i].quoted;
						found = TRUE;
						break;
					}
				}
				if (!found && idx < 0x20)
				{
					warning_cannot_recode(idx, chr_codepage_name(iEncodingSource), chr_codepage_name(iEncodingTarget));
					sprintf(s_temp, "\\'%X", idx);
					ptr_quoted = s_temp;
				}
			}
			break;

		case TOPCH:
			if (ptr[0] == '\\')
			{
				strcpy(s_temp, "\\\\");
				ptr_quoted = s_temp;
			}
			break;

		case TOHAH:					/* HTML Apple Help */
		case TOHTM:					/* HTML */
		case TOMHH:					/* Microsoft HTML Help */

			found = FALSE;

			idx = (_UBYTE) * ptr;

			if (idx > 127 && pUtrg != NULL && !html_ignore_8bit)
			{
				j = 0;					/* search chrtab[] from first entry */

				/* check for end of table! */
				while (chrtab[j].uname != U_NIL)
				{
					/* identical Unicode name found! */
					if (chrtab[j].uname == pUtrg[idx])
					{
						/* valid HTML entity found? */
						if (chrtab[j].html[0] != EOS)
						{
							ptr_quoted = chrtab[j].html;
							found = TRUE;
							break;
						} else			/* no valid HTML entity found */
							warning_no_isochar(ptr[0]);
					}

					j++;
				}

				if (!found)
				{
					warning_cannot_recode(idx, chr_codepage_name(iEncodingSource), chr_codepage_name(iEncodingTarget));
				}
			} else
			{
				for (i = 0; i < MAXHTML7BIT; i++)
				{
					if (ptr[0] == html7bit[i].c)
					{
						ptr_quoted = html7bit[i].quoted;
						found = TRUE;
						break;
					}
				}
			}
			break;

		case TOLDS:
			found = FALSE;

			idx = (_UBYTE) * ptr;

			if (idx > 127)
			{
				j = 0;

				/* check for end of table! */
				while (chrtab[j].uname != U_NIL)
				{
					/* identical Unicode name found! */
					if (pUtrg && (chrtab[j].uname == pUtrg[idx]))
					{
						if (chrtab[j].html[0] != EOS)
						{
							ptr_quoted = chrtab[j].html;
							found = TRUE;
							break;
						} else
							warning_no_isochar(idx);
					}

					j++;
				}
			} else
			{
				for (i = 0; i < MAXLDS7BIT; i++)
				{
					if (ptr[0] == lds7bit[i].c)
					{
						ptr_quoted = lds7bit[i].quoted;
						found = TRUE;
						break;
					}
				}
			}
			break;

		case TOHPH:
			found = FALSE;

			idx = (_UBYTE) * ptr;

			if (idx > 127)
			{
				j = 0;
				while (chrtab[j].uname != U_NIL)
				{
					/* identical Unicode name found! */
					if (pUtrg && (chrtab[j].uname == pUtrg[idx]))
					{
						if (chrtab[j].html[0] != EOS)
						{
							ptr_quoted = chrtab[j].html;
							found = TRUE;
							break;
						} else
							warning_no_isochar(idx);
					}

					j++;
				}
			} else
			{
				for (i = 0; i < MAXHTAG7BIT; i++)
				{
					if (ptr[0] == htag7bit[i].c)
					{
						ptr_quoted = htag7bit[i].quoted;
						found = TRUE;
						break;
					}
				}
			}
			break;
		}

		if (ptr_quoted != NULL && ptr_quoted[0] != EOS)
		{
			s_char[0] = ptr[0];
			cmplen = strlen(ptr_quoted);
			qreplace_once(ptr, s_char, 1, ptr_quoted, cmplen);
			ptr = ptr + cmplen - 1;
			s_temp[0] = EOS;
			ptr_quoted = NULL;
		}

	  NO_QUOTE_NEEDED:
		ptr++;
	}

	if (bDocUniversalCharsetOn)
		uni2misc(s);

	if (iUdopass == PASS2)
	{
		last_aqc_verb = aqc_verb;
	} else
	{
		/* Wird last_aqc_verb nicht zurueckgesetzt, dann kracht es! */
		last_aqc_verb = FALSE;
	}
}





/*******************************************************************************
*
*  auto_quote_texindex():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void auto_quote_texindex(char *s)
{
	if (desttype == TOTEX || desttype == TOPDL || desttype == TOLYX)
	{
		qreplace_all(s, "\"", 1, "\"\"", 2);	/* " ->  "" */
		qreplace_all(s, "!", 1, "\"!", 2);	/* !  -> "! */
		qreplace_all(s, "@", 1, "\"@", 2);	/* @  -> "@ */
		qreplace_all(s, "|", 1, "\"|", 2);	/* |  -> "| */
		qreplace_all(s, "{", 1, "\"{", 2);	/* {  -> "{ */
		qreplace_all(s, "}", 1, "\"}", 2);	/* }  -> "} */
	}
}





/*******************************************************************************
*
*  auto_quote_linedraw():
*     adjust characgters for Linedraw environment (RTF only)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void auto_quote_linedraw(char *s)
{
	register int i;
	char *ptr;
	const char *quoted;
	char sTemp[32];
	char sChar[2] = { 0, 0 };

	ptr = s;

	while (ptr[0] != EOS)
	{
		if (((_UBYTE) ptr[0]) > 127)
		{
			sprintf(sTemp, "\\'%X", (_UBYTE) ptr[0]);
			sChar[0] = ptr[0];
			qreplace_once(ptr, sChar, 1, sTemp, 4);
			ptr += 3;
		} else
		{
			for (i = 0; i < MAXRTF7BIT; i++)
			{
				if (ptr[0] == rtf7bit[i].c)
				{
					quoted = rtf7bit[i].quoted;
					sChar[0] = ptr[0];
					replace_once(ptr, sChar, quoted);
					ptr = ptr + strlen(quoted) - 1;
					break;
				}
			}
		}

		ptr++;
	}
}





/*******************************************************************************
*
*  init_module_chars():
*     init module variables
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_chars(void)
{
	last_aqc_verb = FALSE;
}





/*******************************************************************************
*
*  chr_codepage():
*     get ^ to desired codepage
*
*  Notes:
*     UTF-8 has no codepage and will return NULL
*
*  Return:
*     ^ codepage
*
******************************************|************************************/

GLOBAL const _UWORD *chr_codepage(int encoding)
{
	switch (encoding)
	{
	case CODE_437:
		return u_CODE_437;

	case CODE_850:
		return u_CODE_850;

	case CODE_CP1250:
		return u_CODE_CP1250;

	case CODE_CP1251:
		return u_CODE_CP1251;

	case CODE_CP1253:
		return u_CODE_CP1253;

	case CODE_CP1254:
		return u_CODE_CP1254;

	case CODE_CP1255:
		return u_CODE_CP1255;

	case CODE_CP1256:
		return u_CODE_CP1256;

	case CODE_CP1257:
		return u_CODE_CP1257;

	case CODE_CP1258:
		return u_CODE_CP1258;

	case CODE_HP8:
		return u_CODE_HP8;

	case CODE_LATIN1:
		return u_CODE_LATIN1;

	case CODE_LATIN2:
		return u_CODE_LATIN2;

	case CODE_LATIN3:
		return u_CODE_LATIN3;

	case CODE_LATIN4:
		return u_CODE_LATIN4;

	case CODE_CYRILLIC:
		return u_CODE_CYRILLIC;

	case CODE_ARABIC:
		return u_CODE_ARABIC;

	case CODE_GREEK:
		return u_CODE_GREEK;

	case CODE_HEBREW:
		return u_CODE_HEBREW;

	case CODE_TURKISH:
		return u_CODE_TURKISH;

	case CODE_NORDIC:
		return u_CODE_NORDIC;

	case CODE_THAI:
		return u_CODE_THAI;

	case CODE_BALTIC:
		return u_CODE_BALTIC;

	case CODE_CELTIC:
		return u_CODE_CELTIC;

	case CODE_LATIN9:
		return u_CODE_LATIN9;

	case CODE_LATIN10:
		return u_CODE_LATIN10;

	case CODE_MAC:
		return u_CODE_MAC;

	case CODE_MAC_CE:
		return u_CODE_MAC_CE;

	case CODE_NEXT:
		return u_CODE_NEXT;

	case CODE_TOS:
		return u_CODE_TOS;

	case CODE_UTF8:
		return NULL;					/* no codepage! */

	case CODE_CP1252:
	default:
		break;
	}
	return u_CODE_CP1252;
}





/*******************************************************************************
*
*  chr_ligatures():
*     get ^ to desired table of ligatures
*
*  Return:
*     ^ table of ligatures
*
******************************************|************************************/

GLOBAL lig_array *chr_ligatures(int encoding)
{
	switch (encoding)
	{
	case CODE_437:
		return CODE_437_lig;

	case CODE_850:
		return CODE_850_lig;

	case CODE_CP1250:
		return CODE_CP1250_lig;

	case CODE_CP1251:
		return CODE_CP1251_lig;

	case CODE_CP1253:
		return CODE_CP1253_lig;

	case CODE_CP1254:
		return CODE_CP1254_lig;

	case CODE_CP1255:
		return CODE_CP1255_lig;

	case CODE_CP1256:
		return CODE_CP1256_lig;

	case CODE_CP1257:
		return CODE_CP1257_lig;

	case CODE_CP1258:
		return CODE_CP1258_lig;

	case CODE_HP8:
		return CODE_HP8_lig;

	case CODE_LATIN1:
		return CODE_LATIN1_lig;

	case CODE_LATIN2:
		return CODE_LATIN2_lig;

	case CODE_LATIN3:
		return CODE_LATIN3_lig;

	case CODE_LATIN4:
		return CODE_LATIN4_lig;

	case CODE_CYRILLIC:
		return CODE_CYRILLIC_lig;

	case CODE_ARABIC:
		return CODE_ARABIC_lig;

	case CODE_GREEK:
		return CODE_GREEK_lig;

	case CODE_HEBREW:
		return CODE_HEBREW_lig;

	case CODE_TURKISH:
		return CODE_TURKISH_lig;

	case CODE_NORDIC:
		return CODE_NORDIC_lig;

	case CODE_THAI:
		return CODE_THAI_lig;

	case CODE_BALTIC:
		return CODE_BALTIC_lig;

	case CODE_CELTIC:
		return CODE_CELTIC_lig;

	case CODE_LATIN9:
		return CODE_LATIN9_lig;

	case CODE_LATIN10:
		return CODE_LATIN10_lig;

	case CODE_MAC:
		return CODE_MAC_lig;

	case CODE_MAC_CE:
		return CODE_MAC_CE_lig;

	case CODE_NEXT:
		return CODE_NEXT_lig;

	case CODE_TOS:
		return CODE_TOS_lig;

	case CODE_UTF8:
		return CODE_UTF_lig;

	case CODE_CP1252:
	default:
		break;
	}
	return CODE_CP1252_lig;
}





/*******************************************************************************
*
*  chr_sort_codepage():
*     get ^ to desired codepage for sorting purposes
*
*  Notes:
*     UTF-8 has a two-dimensional sort array, which will be handled directly
*     in chr_usort_codepage().
*
*  Return:
*     ^ codepage
*
******************************************|************************************/

GLOBAL const _UWORD *chr_sort_codepage(int encoding)
{
	switch (encoding)
	{
	case CODE_437:
		return sort_CODE_437;

	case CODE_850:
		return sort_CODE_850;

	case CODE_CP1250:
		return sort_CODE_CP1250;

	case CODE_CP1251:
		return sort_CODE_CP1251;

	case CODE_CP1253:
		return sort_CODE_CP1253;

	case CODE_CP1254:
		return sort_CODE_CP1254;

	case CODE_CP1255:
		return sort_CODE_CP1255;

	case CODE_CP1256:
		return sort_CODE_CP1256;

	case CODE_CP1257:
		return sort_CODE_CP1257;

	case CODE_CP1258:
		return sort_CODE_CP1258;

	case CODE_HP8:
		return sort_CODE_HP8;

	case CODE_LATIN1:
		return sort_CODE_LATIN1;

	case CODE_LATIN2:
		return sort_CODE_LATIN2;

	case CODE_LATIN3:
		return sort_CODE_LATIN3;

	case CODE_LATIN4:
		return sort_CODE_LATIN4;

	case CODE_CYRILLIC:
		return sort_CODE_CYRILLIC;

	case CODE_ARABIC:
		return sort_CODE_ARABIC;

	case CODE_GREEK:
		return sort_CODE_GREEK;

	case CODE_HEBREW:
		return sort_CODE_HEBREW;

	case CODE_TURKISH:
		return sort_CODE_TURKISH;

	case CODE_NORDIC:
		return sort_CODE_NORDIC;

	case CODE_THAI:
		return sort_CODE_THAI;

	case CODE_BALTIC:
		return sort_CODE_BALTIC;

	case CODE_CELTIC:
		return sort_CODE_CELTIC;

	case CODE_LATIN9:
		return sort_CODE_LATIN9;

	case CODE_LATIN10:
		return sort_CODE_LATIN10;

	case CODE_MAC:
		return sort_CODE_MAC;

	case CODE_MAC_CE:
		return sort_CODE_MAC_CE;

	case CODE_NEXT:
		return sort_CODE_NEXT;

	case CODE_TOS:
		return sort_CODE_TOS;

	case CODE_UTF8:
		return NULL;

	case CODE_CP1252:
	default:
		break;
	}
	return sort_CODE_CP1252;
}





/*******************************************************************************
*
*  chr_usort_codepage():
*     get ^ to desired Unicode sorting table
*
*  Return:
*     ^ codepage
*
******************************************|************************************/

GLOBAL usort_array *chr_usort_codepage(int encoding)
{
	switch (encoding)
	{
	case CODE_UTF8:
		return sort_CODE_UTF;

	default:
		break;
	}
	return NULL;
}





/*******************************************************************************
*
*  chr_codepage_name():
*     get human-readable name of desired codepage
*
*  Notes:
*     String length must not exceed 40 chars!
*
*  Return:
*     codepage name 
*
******************************************|************************************/

GLOBAL const char *chr_codepage_name(int encoding)
{
	/* Length: 1234567890123456789012345678901234567890 */

	switch (encoding)
	{
	case CODE_437:
		return "DOS (cp437)";

	case CODE_850:
		return "DOS (cp850)";

	case CODE_CP1250:
		return "Windows codepage 1250 (Central Europe)";

	case CODE_CP1251:
		return "Windows codepage 1251 (Russian)";

	case CODE_CP1253:
		return "Windows codepage 1253 (Greek)";

	case CODE_CP1254:
		return "Windows codepage 1254 (Turkish)";

	case CODE_CP1255:
		return "Windows codepage 1255 (Hebrew)";

	case CODE_CP1256:
		return "Windows codepage 1256 (Arabic)";

	case CODE_CP1257:
		return "Windows codepage 1257 (Baltic)";

	case CODE_CP1258:
		return "Windows codepage 1258 (Vietnamese)";

	case CODE_HP8:
		return "HP-Roman8";

	case CODE_LATIN1:
		return "ISO 8859-1 (Latin 1)";

	case CODE_LATIN2:
		return "ISO 8859-2 (Latin 2)";

	case CODE_LATIN3:
		return "ISO 8859-3 (Latin 3)";

	case CODE_LATIN4:
		return "ISO 8859-4 (Latin 4)";

	case CODE_CYRILLIC:
		return "ISO 8859-5 (Cyrillic)";

	case CODE_ARABIC:
		return "ISO 8859-6 (Arabic)";

	case CODE_GREEK:
		return "ISO 8859-7 (Greek)";

	case CODE_HEBREW:
		return "ISO 8859-8 (Hebrew)";

	case CODE_TURKISH:
		return "ISO 8859-9 (Latin 5)";

	case CODE_NORDIC:
		return "ISO 8859-10 (Latin 6)";

	case CODE_THAI:
		return "ISO 8859-11 (Thai)";

	case CODE_BALTIC:
		return "ISO 8859-13 (Latin 7)";

	case CODE_CELTIC:
		return "ISO 8859-14 (Latin 8)";

	case CODE_LATIN9:
		return "ISO 8859-15 (Latin 9)";

	case CODE_LATIN10:
		return "ISO 8859-16 (Latin 10)";

	case CODE_MAC:
		return "Mac";

	case CODE_MAC_CE:
		return "Mac CE";

	case CODE_NEXT:
		return "NeXTSTEP";

	case CODE_TOS:
		return "Atari TOS";

	case CODE_UTF8:
		return "UTF-8";

	case CODE_CP1252:
		return "Windows codepage 1252 (Western)";
	}

	return "unknown codepage!!!";
}





/*******************************************************************************
*
*  chr_codepage_charset_name():
*     get Content-Type charset name of desired codepage for HTML
*
*  Return:
*     charset name 
*
******************************************|************************************/

GLOBAL const char *chr_codepage_charset_name(int encoding)
{
	switch (encoding)
	{
	case CODE_437:
		return "cp437";

	case CODE_850:
		return "cp850";

	case CODE_CP1250:
		return "Windows-1250";

	case CODE_CP1251:
		return "Windows-1251";

	case CODE_CP1252:
		return "Windows-1252";

	case CODE_CP1253:
		return "Windows-1253";

	case CODE_CP1254:
		return "Windows-1254";

	case CODE_CP1255:
		return "Windows-1255";

	case CODE_CP1256:
		return "Windows-1256";

	case CODE_CP1257:
		return "Windows-1257";

	case CODE_CP1258:
		return "Windows-1258";

	case CODE_HP8:
		return "hp-roman8";

	case CODE_LATIN1:
		return "ISO-8859-1";

	case CODE_LATIN2:
		return "ISO-8859-2";

	case CODE_LATIN3:
		return "ISO-8859-3";

	case CODE_LATIN4:
		return "ISO-8859-4";

	case CODE_CYRILLIC:
		return "ISO-8859-5";

	case CODE_ARABIC:
		return "ISO-8859-6";

	case CODE_GREEK:
		return "ISO-8859-7";

	case CODE_HEBREW:
		return "ISO-8859-8";

	case CODE_TURKISH:
		return "ISO-8859-9";

	case CODE_NORDIC:
		return "ISO-8859-10";

	case CODE_THAI:
		return "ISO-8859-11";

	case CODE_BALTIC:
		return "ISO-8859-13";

	case CODE_CELTIC:
		return "ISO-8859-14";

	case CODE_LATIN9:
		return "ISO-8859-15";

	case CODE_LATIN10:
		return "ISO-8859-16";

	case CODE_MAC:
		return "MacRoman";

	case CODE_MAC_CE:
		return "MacCE";

	case CODE_NEXT:
		return "next";

	case CODE_TOS:
		return "atari";

	case CODE_UTF8:
		return "UTF-8";

	default:
		break;
	}
	return "ISO-8859-1";
}


#undef iEncodingTarget
void (set_encoding_target) (int code, const char *file, int line)
{
	iEncodingTarget = code;
#if 0									/* for debugging */
	fprintf(stderr, "set enc: %s %d %s\n", file, line, chr_codepage_charset_name(iEncodingTarget));
#else
	UNUSED(file);
	UNUSED(line);
#endif
}


#if 0									/* for debugging */
#undef iEncodingTarget
int get_encoding_target(const char *file, int line)
{
	static int been_here;

	if (!been_here)
	{
		fprintf(stderr, "get enc: %s %d %s\n", file, line, chr_codepage_charset_name(iEncodingTarget));
		been_here = 1;
	}
	return iEncodingTarget;
}
#endif
