/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : u_udo.h
*  Symbol prefix: u_
*
*  Description  : Unicode named codepage for UDO universal characters
*
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
*  Author       : Ulf Dunkel (fd)
*  Co-Authors   : -
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
*    fd  Feb 19: file introduced (content merged from CHR_xxx.h files)
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 25: u_CODE_UDO[] enhanced:
*                - (!#P) -> U_SectionSign (aka 'Paragraph')
*                - (!/O) -> U_LatinCapitalLetterOSlash (more intuitive)
*                - (!_?) -> U_InvertedQuestionMark
*                - (!_!) -> U_InvertedExclamationMark
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#include "udoport.h"
#include "unicode.h"





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _udo2utf
{
   const char *udo;                       /* UDO universal character string */
   _UWORD unicode;                        /* Unicode */
   _UWORD uni2ascii;                      /* 7-bit ASCII Unicode */
   const char *win;
   const char *tex;
   const char *html;
   const char *lyx;
} UDO2UTF;





/******************************************************************************
*
*  u_CODE_UDO[]:
*     Unicode named codepage for UDO universal characters
*
******************************************|************************************/

static UDO2UTF const u_CODE_UDO[] =            /* CODE_UDO */
{
   /* UDO       Unicode                               7-bit Unicode           Windows  TeX        HTML        LyX    */
   /* -------------------------------------------------------------------------------------------------------------- */
   { "(!#P)",   U_SectionSign,                        U_Asterisk,             "\\'A7", "\\S{}",   "&sect;",   "\0xA7" },
   { "(!#S)",   U_SectionSign,                        U_Asterisk,             "\\'A7", "\\S{}",   "&sect;",   "\0xA7" },
   
   { "(!&AE)",  U_LatinCapitalLigatureAE,             U_LatinCapitalLetterA,  "\\'C6", "{\\AE}",  "&AElig;",  "\0xC6" },
   { "(!&ae)",  U_LatinSmallLigatureAE,               U_LatinSmallLetterA,    "\\'E6", "{\\ae}",  "&aelig;",  "\0xE6" },
   { "(!&OE)",  U_LatinCapitalLigatureOE,             U_LatinCapitalLetterO,  "\\'8C", "{\\OE}",  "&OElig;",  "\0x8C" },
   { "(!&oe)",  U_LatinSmallLigatureOE,               U_LatinSmallLetterO,    "\\'9C", "{\\oe}",  "&oelig;",  "\0x9C" },
   
   { "(!,C)",   U_LatinCapitalLetterCWithCedilla,     U_LatinCapitalLetterC,  "\\'C7", "\\c{C}",  "&Ccedil;", "\0xC7" },
   { "(!,c)",   U_LatinSmallLetterCWithCedilla,       U_LatinSmallLetterC,    "\\'E7", "\\c{c}",  "&ccedil;", "\0xE7" },
   
   { "(!.A)",   U_LatinCapitalLetterAWithRingAbove,   U_LatinCapitalLetterA,  "\\'C5", "{\\AA}",  "&Aring;",  "\0xC5" },
   { "(!.a)",   U_LatinSmallLetterAWithRingAbove,     U_LatinSmallLetterA,    "\\'E5", "{\\aa}",  "&aring;",  "\0xE5" },
   
   { "(!\"A)",  U_LatinCapitalLetterAWithDiaeresis,   U_LatinCapitalLetterA,  "\\'C4", "\\\"A",   "&Auml;",   "\0xC4" },
   { "(!\"a)",  U_LatinSmallLetterAWithDiaeresis,     U_LatinSmallLetterA,    "\\'E4", "\\\"a",   "&auml;",   "\0xE4" },
   { "(!\"E)",  U_LatinCapitalLetterEWithDiaeresis,   U_LatinCapitalLetterE,  "\\'CB", "\\\"{E}", "&Euml;",   "\0xCB" },
   { "(!\"e)",  U_LatinSmallLetterEWithDiaeresis,     U_LatinSmallLetterE,    "\\'EB", "\\\"{e}", "&euml;",   "\0xEB" },
   { "(!\"I)",  U_LatinCapitalLetterIWithDiaeresis,   U_LatinCapitalLetterI,  "\\'CF", "\\\"{I}", "&Iuml;",   "\0xCF" },
   { "(!\"i)",  U_LatinSmallLetterIWithDiaeresis,     U_LatinSmallLetterI,    "\\'EF", "\\\"{i}", "&iuml;",   "\0xEF" },
   { "(!\"O)",  U_LatinCapitalLetterOWithDiaeresis,   U_LatinCapitalLetterO,  "\\'D6", "\\\"O",   "&Ouml;",   "\0xD6" },
   { "(!\"o)",  U_LatinSmallLetterOWithDiaeresis,     U_LatinSmallLetterO,    "\\'F6", "\\\"o",   "&ouml;",   "\0xF6" },
   { "(!\"s)",  U_LatinSmallLetterSharpS,             U_LatinSmallLetterS,    "\\'DF", "{\\ss}",  "&szlig;",  "\0xDF" },
   { "(!\"U)",  U_LatinCapitalLetterUWithDiaeresis,   U_LatinCapitalLetterU,  "\\'DC", "\\\"U",   "&Uuml;",   "\0xDC" },
   { "(!\"u)",  U_LatinSmallLetterUWithDiaeresis,     U_LatinSmallLetterU,    "\\'FC", "\\\"u",   "&uuml;",   "\0xFC" },
   { "(!\"Y)",  U_LatinCapitalLetterYWithDiaeresis,   U_LatinCapitalLetterY,  "\\'FF", "\\\"{Y}", "&Yuml;",   "\0xFF" },
   { "(!\"y)",  U_LatinSmallLetterYWithDiaeresis,     U_LatinSmallLetterY,    "\\'FF", "\\\"{y}", "&yuml;",   "\0xFF" },
   
   { "(!/O)",   U_LatinCapitalLetterOSlash,           U_LatinCapitalLetterO,  "\\'D8", "{\\O}",   "&Oslash;", "\0xD8" },
   { "(!/o)",   U_LatinSmallLetterOSlash,             U_LatinSmallLetterO,    "\\'F8", "{\\o}",   "&oslash;", "\0xF8" },
   { "(!\\O)",  U_LatinCapitalLetterOSlash,           U_LatinCapitalLetterO,  "\\'D8", "{\\O}",   "&Oslash;", "\0xD8" },
   { "(!\\o)",  U_LatinSmallLetterOSlash,             U_LatinSmallLetterO,    "\\'F8", "{\\o}",   "&oslash;", "\0xF8" },
   
   { "(!^A)",   U_LatinCapitalLetterAWithCircumflex,  U_LatinCapitalLetterA,  "\\'C2", "\\^{A}",  "&Acirc;",  "\0xC2" },
   { "(!^a)",   U_LatinSmallLetterAWithCircumflex,    U_LatinSmallLetterA,    "\\'E2", "\\^{a}",  "&acirc;",  "\0xE2" },
   { "(!^E)",   U_LatinCapitalLetterEWithCircumflex,  U_LatinCapitalLetterE,  "\\'CA", "\\^{E}",  "&Ecirc;",  "\0xCA" },
   { "(!^e)",   U_LatinSmallLetterEWithCircumflex,    U_LatinSmallLetterE,    "\\'EA", "\\^{e}",  "&ecirc;",  "\0xEA" },
   { "(!^I)",   U_LatinCapitalLetterIWithCircumflex,  U_LatinCapitalLetterI,  "\\'CE", "\\^{I}",  "&Icirc;",  "\0xCE" },
   { "(!^i)",   U_LatinSmallLetterIWithCircumflex,    U_LatinSmallLetterI,    "\\'EE", "\\^{i}",  "&icirc;",  "\0xEE" },
   { "(!^O)",   U_LatinCapitalLetterOWithCircumflex,  U_LatinCapitalLetterO,  "\\'D4", "\\^{O}",  "&Ocirc;",  "\0xD4" },
   { "(!^o)",   U_LatinSmallLetterOWithCircumflex,    U_LatinSmallLetterO,    "\\'F4", "\\^{o}",  "&ocirc;",  "\0xF4" },
   { "(!^U)",   U_LatinCapitalLetterUWithCircumflex,  U_LatinCapitalLetterU,  "\\'DB", "\\^{U}",  "&Ucirc;",  "\0xDB" },
   { "(!^u)",   U_LatinSmallLetterUWithCircumflex,    U_LatinSmallLetterU,    "\\'FB", "\\^{u}",  "&ucirc;",  "\0xFB" },
   
   { "(!_a)",   U_FeminineOrdinalIndicator,           U_LatinSmallLetterO,    "\\'AA", "\\b{a}",  "&#170;",   "\0xAA" },
   { "(!_o)",   U_MasculineOrdinalIndicator,          U_LatinSmallLetterA,    "\\'BA", "\\b{o}",  "&#186;",   "\0xBA" },
   { "(!_?)",   U_InvertedQuestionMark,               U_QuestionMark,         "\\'BF", "?",       "&iquest;", "\0xBF" },
   { "(!_!)",   U_InvertedExclamationMark,            U_ExclamationMark,      "\\'A1", "!",       "&iexcl;",  "\0xA1" },
   
   { "(!`A)",   U_LatinCapitalLetterAWithGrave,       U_LatinCapitalLetterA,  "\\'C0", "\\`{A}",  "&Agrave;", "\0xC0" },
   { "(!`a)",   U_LatinSmallLetterAWithGrave,         U_LatinSmallLetterA,    "\\'E0", "\\`{a}",  "&agrave;", "\0xE0" },
   { "(!`E)",   U_LatinCapitalLetterEWithGrave,       U_LatinCapitalLetterE,  "\\'C8", "\\`{E}",  "&Egrave;", "\0xC8" },
   { "(!`e)",   U_LatinSmallLetterEWithGrave,         U_LatinSmallLetterE,    "\\'E8", "\\`{e}",  "&egrave;", "\0xE8" },
   { "(!`I)",   U_LatinCapitalLetterIWithGrave,       U_LatinCapitalLetterI,  "\\'CC", "\\`{I}",  "&Igrave;", "\0xCC" },
   { "(!`i)",   U_LatinSmallLetterIWithGrave,         U_LatinSmallLetterI,    "\\'EC", "\\`{i}",  "&igrave;", "\0xEC" },
   { "(!`O)",   U_LatinCapitalLetterOWithGrave,       U_LatinCapitalLetterO,  "\\'D2", "\\`{O}",  "&Ograve;", "\0xD2" },
   { "(!`o)",   U_LatinSmallLetterOWithGrave,         U_LatinSmallLetterO,    "\\'F2", "\\`{o}",  "&ograve;", "\0xF2" },
   { "(!`U)",   U_LatinCapitalLetterUWithGrave,       U_LatinCapitalLetterU,  "\\'D9", "\\`{U}",  "&Ugrave;", "\0xD9" },
   { "(!`u)",   U_LatinSmallLetterUWithGrave,         U_LatinSmallLetterU,    "\\'F9", "\\`{u}",  "&ugrave;", "\0xF9" },
   
   { "(!~A)",   U_LatinCapitalLetterAWithTilde,       U_LatinCapitalLetterA,  "\\'C3", "\\~{A}",  "&Atilde;", "\0xC3" },
   { "(!~a)",   U_LatinSmallLetterAWithTilde,         U_LatinSmallLetterA,    "\\'E3", "\\~{a}",  "&atilde;", "\0xE3" },
   { "(!~N)",   U_LatinCapitalLetterNWithTilde,       U_LatinCapitalLetterN,  "\\'D1", "\\~{N}",  "&Ntilde;", "\0xD1" },
   { "(!~n)",   U_LatinSmallLetterNWithTilde,         U_LatinSmallLetterN,    "\\'F1", "\\~{n}",  "&ntilde;", "\0xF1" },
   { "(!~O)",   U_LatinCapitalLetterOWithTilde,       U_LatinCapitalLetterO,  "\\'D5", "\\~{O}",  "&Otilde;", "\0xD5" },
   { "(!~o)",   U_LatinSmallLetterOWithTilde,         U_LatinSmallLetterO,    "\\'F5", "\\~{o}",  "&otilde;", "\0xF5" },
   
   { "(!'A)",   U_LatinCapitalLetterAWithAcute,       U_LatinCapitalLetterA,  "\\'C1", "\\'{A}",  "&Aacute;", "\0xC1" },
   { "(!'a)",   U_LatinSmallLetterAWithAcute,         U_LatinSmallLetterA,    "\\'E1", "\\'{a}",  "&aacute;", "\0xE1" },
   { "(!'E)",   U_LatinCapitalLetterEWithAcute,       U_LatinCapitalLetterE,  "\\'C9", "\\'{E}",  "&Eacute;", "\0xC9" },
   { "(!'e)",   U_LatinSmallLetterEWithAcute,         U_LatinSmallLetterE,    "\\'E9", "\\'{e}",  "&eacute;", "\0xE9" },
   { "(!'I)",   U_LatinCapitalLetterIWithAcute,       U_LatinCapitalLetterI,  "\\'CD", "\\'{I}",  "&Iacute;", "\0xCD" },
   { "(!'i)",   U_LatinSmallLetterIWithAcute,         U_LatinSmallLetterI,    "\\'ED", "\\'{i}",  "&iacute;", "\0xED" },
   { "(!'O)",   U_LatinCapitalLetterOWithAcute,       U_LatinCapitalLetterO,  "\\'D3", "\\'{O}",  "&Oacute;", "\0xD3" },
   { "(!'o)",   U_LatinSmallLetterOWithAcute,         U_LatinSmallLetterO,    "\\'F3", "\\'{o}",  "&oacute;", "\0xF3" },
   { "(!'U)",   U_LatinCapitalLetterUWithAcute,       U_LatinCapitalLetterU,  "\\'DA", "\\'{U}",  "&Uacute;", "\0xDA" },
   { "(!'u)",   U_LatinSmallLetterUWithAcute,         U_LatinSmallLetterU,    "\\'FA", "\\'{u}",  "&uacute;", "\0xFA" },
   { "(!'Y)",   U_LatinCapitalLetterYWithAcute,       U_LatinCapitalLetterY,  "\\'DD", "\\'{Y}",  "&Yacute;", "\0xDD" },
   { "(!'y)",   U_LatinSmallLetterYWithAcute,         U_LatinSmallLetterY,    "\\'FD", "\\'{y}",  "&yacute;", "\0xFD" },
   
   { NULL,      U_NIL,                                U_NIL,                  "",      "",        "",         ""      }  /* list terminator */
};
