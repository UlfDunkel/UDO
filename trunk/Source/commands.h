/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : commands.h
*  Symbol prefix: commands
*
*  Description  : Kommando- und Platzhalterbezeichner
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
*  Co-Authors   : Gerhard Stoll (ggs), Ulf Dunkel
*  Write access : ggs, fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - demnaechst ein Modul cmd.c anlegen, das die Strings global 
*                   zur Verfuegung stellt, um das Binary kleiner zu halten 
*                   und den Praeprozessor zu entlasten
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 22: header adjusted
*
******************************************|************************************/

/* --------------------------------------------------   */
/* Schriftumschaltungen                                 */
/* --------------------------------------------------   */

#define CMD_BOLD_ON      "(!B)"
#define CMD_BOLD_OFF     "(!b)"
#define CMD_ITALIC_ON    "(!I)"
#define CMD_ITALIC_OFF   "(!i)"
#define CMD_FOOT_ON      "(!N)"
#define CMD_FOOT_OFF     "(!n)"
#define CMD_TWRITER_ON   "(!T)"
#define CMD_TWRITER_OFF  "(!t)"
#define CMD_UNDER_ON     "(!U)"
#define CMD_UNDER_OFF    "(!u)"
#define CMD_VERB_ON      "(!V)"
#define CMD_VERB_OFF     "(!v)"
#define CMD_STYLELEN     4

/* New in V6.5.9 [NHz] */
#define CMD_INSERT_ON    "(!INS)"
#define CMD_INSERT_OFF   "(!ins)"
#define CMD_DELETED_ON   "(!DEL)"
#define CMD_DELETED_OFF  "(!del)"
/* New in V6.5.20 [GS] */
#define CMD_SUP_ON    "(!SUP)"
#define CMD_SUP_OFF   "(!sup)"
#define CMD_SUB_ON    "(!SUB)"
#define CMD_SUB_OFF   "(!sub)"





/* --------------------------------------------------   */
/* Farben                                               */
/* --------------------------------------------------   */
/* New in V6.5.9 [NHz] */

#define CMD_COLOR_BLACK    "(!black)"
#define CMD_COLOR_SILVER   "(!silver)"
#define CMD_COLOR_GRAY     "(!gray)"
#define CMD_COLOR_WHITE    "(!white)"
#define CMD_COLOR_MAROON   "(!maroon)"
#define CMD_COLOR_RED      "(!red)"
#define CMD_COLOR_PURPLE   "(!purple)"
#define CMD_COLOR_FUCHSIA  "(!fuchsia)"
#define CMD_COLOR_GREEN    "(!green)"
#define CMD_COLOR_LIME     "(!lime)"
#define CMD_COLOR_OLIVE    "(!olive)"
#define CMD_COLOR_YELLOW   "(!yellow)"
#define CMD_COLOR_NAVY     "(!navy)"
#define CMD_COLOR_BLUE     "(!blue)"
#define CMD_COLOR_TEAL     "(!teal)"
#define CMD_COLOR_AQUA     "(!aqua)"
#define CMD_COLOR_OFF      "(!coloff)"





/* --------------------------------------------------   */
/* Umgebungen                                           */
/* --------------------------------------------------   */

#define CMD_BEGIN_APPENDIX      "!begin_appendix"
#define CMD_END_APPENDIX        "!end_appendix"

#define CMD_BEGIN_CENTER        "!begin_center"
#define CMD_END_CENTER          "!end_center"

#define CMD_BEGIN_RIGHT         "!begin_flushright"
#define CMD_END_RIGHT           "!end_flushright"

#define CMD_BEGIN_LEFT          "!begin_flushleft"
#define CMD_END_LEFT            "!end_flushleft"

#define CMD_BEGIN_DESCRIPTION   "!begin_description"
#define CMD_END_DESCRIPTION     "!end_description"

#define CMD_BEGIN_DOCUMENT      "!begin_document"
#define CMD_END_DOCUMENT        "!end_document"

#define CMD_BEGIN_ENUMERATE     "!begin_enumerate"
#define CMD_END_ENUMERATE       "!end_enumerate"

#define CMD_BEGIN_ITEMIZE       "!begin_itemize"
#define CMD_END_ITEMIZE         "!end_itemize"

#define CMD_BEGIN_QUOTE         "!begin_quote"
#define CMD_END_QUOTE           "!end_quote"

#define CMD_BEGIN_RAW           "!begin_raw"
#define CMD_END_RAW             "!end_raw"
#define CUT_BEGIN_RAW           "!br"
#define CUT_END_RAW             "!er"

#define CMD_BEGIN_TABLE         "!begin_table"
#define CMD_END_TABLE           "!end_table"
#define CUT_BEGIN_TABLE         "!bt"
#define CUT_END_TABLE           "!et"

#define CMD_BEGIN_VERBATIM      "!begin_verbatim"
#define CMD_END_VERBATIM        "!end_verbatim"
#define CUT_BEGIN_VERBATIM      "!bv"
#define CUT_END_VERBATIM        "!ev"

#define CMD_BEGIN_SOURCECODE    "!begin_sourcecode"
#define CMD_END_SOURCECODE      "!end_sourcecode"

#define CMD_BEGIN_COMMENT       "!begin_comment"
#define CMD_END_COMMENT         "!end_comment"

#define CMD_BEGIN_LINEDRAW      "!begin_linedraw"
#define CMD_END_LINEDRAW        "!end_linedraw"

#define CMD_BEGIN_PREFORMATTED  "!begin_preformatted"
#define CMD_END_PREFORMATTED    "!end_preformatted"

#define CMD_BEGIN_XLIST         "!begin_xlist"
#define CMD_END_XLIST           "!end_xlist"

#define CMD_BEGIN_BLIST         "!begin_blist"
#define CMD_END_BLIST           "!end_blist"

#define CMD_BEGIN_ILIST         "!begin_ilist"
#define CMD_END_ILIST           "!end_ilist"

#define CMD_BEGIN_TLIST         "!begin_tlist"
#define CMD_END_TLIST           "!end_tlist"





/* --------------------------------------------------   */
/* Platzhalter (ohne !)                                 */
/* --------------------------------------------------   */
#define CMD_IDX  "idx"





/* --------------------------------------------------   */
/* Kapitel und Ueberschriften                           */
/* --------------------------------------------------   */

#define CMD_HEADING           "!heading"
#define CMD_SUBHEADING        "!subheading"
#define CMD_SUBSUBHEADING     "!subsubheading"
#define CMD_SUBSUBSUBHEADING  "!subsubsubheading"
#define CMD_SUBSUBSUBSUBHEADING  "!subsubsubsubheading"





/* --------------------------------------------------   */
/* Sonstiges, alphabetisch sortiert                     */
/* --------------------------------------------------   */

#define CMD_ALIAS              "!alias"
#define CMD_AUTOREF            "!autoref"
#define CMD_AUTOREF_ITEMS      "!autoref_items"
#define CMD_BREAK              "!break"
#define CMD_DEFINE             "!define"
#define CMD_HYPHEN             "!hyphen"
#define CMD_INDEX              "!index"
#define CMD_KEYWORD            "!keyword"
#define CMD_LABEL              "!label"
#define CMD_MACRO              "!macro"
#define CMD_SET                "!set"
#define CMD_UNSET              "!unset"
#define CMD_UNIVERSAL_CHARSET  "!universal_charset"
#define CMD_VERBATIMSIZE       "!verbatimsize"
#define CMD_LINEDRAWSIZE       "!linedrawsize"
#define CMD_RTF_KEEP_TABLES    "!rtf_keep_tables"





/* --------------------------------------------------   */
/* HTML-Kommandos                                       */
/* --------------------------------------------------   */

#define HTML_BR          "<br>"
#define HTML_HR          "<hr>\n"

#define XHTML_BR         "<br />"
#define XHTML_HR         "<hr />\n"

/* the next two seem to be unused so far */
#define HTML_CENTER_ON   "<p align=\"center\">"
#define HTML_CENTER_OFF  "</p>"

#if 0

#define html_bq_on       "<blockquote>"
#define html_bq_off      "</blockquote>"
#define html_ul_on       "<ul>"
#define html_ul_off      "</ul>"
#define html_html_on     "<html>"
#define html_html_off    "</html>"
#define html_title_on    "<title>"
#define html_title_off   "</title>"
#define html_head_on     "<head>"
#define html_head_off    "</head>"
#define html_body_on     "<body>"
#define html_body_off    "</body>"

#define html_italic_on   "<i>"
#define html_italic_off  "</i>"

#define html_bold_on     "<b>"
#define html_bold_off    "</b>"

#define html_pre_on      "<pre>"
#define html_pre_off     "</pre>"

#endif





/* --------------------------------------------------   */
/* RTF-Kommandos                                        */
/* --------------------------------------------------   */

#define rtf_par        "\\par"
#define rtf_pard       "\\pard"
#define rtf_plain      "\\plain"

#define rtf_parpard    "\\par\\pard"
#define rtf_pardpar    "\\pard\\par"

#define rtf_pardplain  "\\pard\\plain"
#define rtf_parplain   "\\par\\plain"

#define rtf_norm       "\\s1\\qj\\f0"
#define rtf_verb       "\\s2\\ql\\f1"

#define rtf_chapt      "\\s3\\ql\\b\\f0"
#define rtf_node1      "\\s4\\ql\\b\\f0\n\\li567\\fi-567"
#define rtf_node2      "\\s5\\ql\\b\\f0\\li907\\fi-907"
#define rtf_node3      "\\s6\\ql\\b\\f0\\li1134\\fi-1134"
#define rtf_node4      "\\s7\\ql\\b\\f0\\li1248\\fi-1248"
#define rtf_node5      "\\s7\\ql\\b\\f0\\li1248\\fi-1248" /* ToDo: ??? */

#define rtf_inv_chapt  "\\s8\\ql\\b\\f0"
#define rtf_inv_node1  "\\s9\\ql\\b\\f0"
#define rtf_inv_node2  "\\s10\\ql\\b\\f0"
#define rtf_inv_node3  "\\s11\\ql\\b\\f0"
#define rtf_inv_node4  "\\s12\\ql\\b\\f0"
#define rtf_inv_node5  "\\s12\\ql\\b\\f0"                  /* ToDo: ??? */

#define rtf_linedraw   "\\s13\\ql\\f2"





/* --------------------------------------------------   */
/* WinHelp-Kommandos                                    */
/* --------------------------------------------------   */

#define win_text      "\\f0 "
#define win_verb      "\\f1 "
#define win_symb      "\\f2 "

#define win_verb_on   "{\\f1\\keep"
#define win_verb_off  "}\\pard"

#define win_browse    "+{\\footnote 00001:002}"





/* --------------------------------------------------   */
/* Fuer Pure-C-Help                                     */
/* --------------------------------------------------   */
#define PCH_LINK  "\\#"


/* +++ EOF +++ */
