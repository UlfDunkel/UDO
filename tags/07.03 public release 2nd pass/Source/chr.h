/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr.h
*  Symbol prefix: chr
*
*  Description  : headers and definitions for CHR.C
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
*  2010:
*    fd  Feb 10: header updated, file reformatted and tidied up (TAB-free)
*    fd  Feb 17: - ansi2dos() removed
*                - win2sys() & html2sys() & umlaute2ascii() -> recode_chrtab()
*                - CHRTAB_... introduced
*    fd  Feb 19: uni2ascii() renamed -> recode_udo()
*    fd  Feb 20: utf8_to_uchar()
*    fd  Feb 22: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 23: some prototypes adjusted
*    fd  Feb 24: - new: chr_codepage()
*                - new: chr_codepage_name()
*                - new: chr_sort_codepage()
*                - new: chr_usort_codepage()
*                - new: chr_ligatures()
*    fd  May 18: new: chr_codepage_charset_name()
*  2011:
*    fd  Feb 18: utf8_to_uchar() enhanced
*
******************************************|************************************/

#ifndef __UDOCHR__
#define __UDOCHR__





/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "unicode.h"





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define TTF_REGULAR       0
#define TTF_BOLD          1
#define TTF_ITALIC        2

#define TTF_ARIAL         0
#define TTF_TIMES         1
#define TTF_COURIER       2

#define TTF_10PT          0
#define TTF_11PT          1

   /* New in r6pl16 [NHz] */
#define KPS_CONTENT       0
#define KPS_BOOKMARK      1
#define KPS_NAMEDEST      2

   /* New: Fixed bug #0000040 in r6.2pl2 [NHz] */
#define KPS_PS2DOCINFO    3
#define KPS_DOCINFO2PS    4
#define KPS_NODENAME      5


   /* new in v6.5.19 [fd] */
   /* this is a list of UDO supported special HTML characters */
#define HTML_SPEC_HELLIP  0
#define HTML_SPEC_MDASH   1
#define HTML_SPEC_NDASH   2
#define HTML_SPEC_SHY     3
#define HTML_SPEC_MAX     4


   /* --- indicators for usage of recode_chrtab() --- */
#define CHRTAB_ASCII      0
#define CHRTAB_ANSI       1
#define CHRTAB_TEX        2
#define CHRTAB_HTML       3
#define CHRTAB_PS         4






/*******************************************************************************
*
*     GLOBAL FUNCTION PROTOTYPES
*
******************************************|************************************/

   /* convert UTF-8 bytes into Unicode codepoint value (known length of byte stream!) */
GLOBAL UWORD utf8_to_bstr(const char *sz, int len);

   /* convert UTF-8 bytes into Unicode char (unknown length of byte stream) */
GLOBAL UWORD utf8_to_uchar(const char *sz, int *length);

   /* convert Unicode value into UTF-8 bytes */
GLOBAL char *bstr_to_utf8(UWORD ucode, char *s);

   /* get char(s!) from Unicode value */
GLOBAL char *unicode2char(UWORD unicode, char *s);


GLOBAL void convert_sz(char * s);

   /* recode a line into another encoding */
GLOBAL void recode(char *zeile, int char_set);

   /* convert (UDO's) universal characters into target encoding */
GLOBAL void recode_udo(char * s);

   /* recode a string from chrtab[] via Unicode name to another encoding */
GLOBAL void recode_chrtab(char * s, int type);

GLOBAL int calc_ttf_twip(const char *s, const int font, const int style);

GLOBAL void replace_udo_quotes(char * s);
GLOBAL void replace_all_copyright(char *s);

GLOBAL void delete_all_divis(char *s);

GLOBAL void indent2space(char * s);
GLOBAL void space2indent(char * s);
GLOBAL void nbsp2space(char * s);
GLOBAL void space2nbsp(char * s);

GLOBAL void label2tex(char * s);
GLOBAL void label2html(char * s);

GLOBAL void node2winhelp(char *n);
GLOBAL void node2WinAutoID(char *id, const char *n);
GLOBAL void node2NrWinhelp(char *s, int i);
GLOBAL void alias2NrWinhelp(char *s, int i);
GLOBAL void label2NrWinhelp(char *s, int i);

GLOBAL void node2NrIPF(char *s, int i);
GLOBAL void alias2NrIPF(char *s, int i);
GLOBAL void label2NrIPF(char *s, int i);

GLOBAL void node2pchelp (char *n);
GLOBAL void node2postscript(char *s, BOOLEAN text);

GLOBAL void node2stg(char *s);
GLOBAL void index2stg(char *s);
GLOBAL void replace_2at_by_1at(char * s);
GLOBAL void replace_1at_by_2at(char * s);

GLOBAL void node2vision(char *n);
GLOBAL void node2texinfo(char *s);

GLOBAL void c_umlaute(char *s);

GLOBAL void c_tilde(char *s);
GLOBAL void replace_udo_tilde(char * s);
GLOBAL void replace_udo_nbsp(char * s);
GLOBAL void convert_tilde(char * s);

GLOBAL void c_divis(char *s);

GLOBAL void winspecials2ascii(char * s);
GLOBAL void c_rtf_quotes(char * s);
GLOBAL void c_vars(char *s);

GLOBAL void c_man_styles(char * s);

   /* convert special characters for relevant target encodings */
GLOBAL void auto_quote_chars(char *s, BOOLEAN all);
GLOBAL void auto_quote_texindex(char * s);
GLOBAL void auto_quote_linedraw(char * s);

GLOBAL void init_module_chars(void);

   /* get ^ to desired codepage */
GLOBAL UWORD *chr_codepage(int encoding);

   /* get ^ to desired codepage for sorting purposes */
GLOBAL UWORD *chr_sort_codepage(int encoding);

   /* get ^ to desired Unicode sorting table */
GLOBAL VOID *chr_usort_codepage(int encoding);

   /* get ^ to desired table of ligatures */
GLOBAL VOID *chr_ligatures(int encoding);

   /* get human-readable name of desired codepage */
GLOBAL char *chr_codepage_name(int encoding);

   /* get Content-Type charset name of desired codepage for HTML */
GLOBAL char *chr_codepage_charset_name(int encoding);

#endif   /* __UDOCHR__ */


/* +++ EOF +++ */
