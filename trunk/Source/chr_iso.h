/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_iso.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer Commodore Amiga und Linux
*                 Werte laut Screenshot von Michael Gehrke @ MK2
*                 und Tabelle von Frank Baumgart @ PB3
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
*  Things to do : re-write UDO string and encoding engine for full Unicode support 
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 10: header updated, file reformatted and tidied up (TAB-free)
*    fd  Feb 12: u_CODE_ISO[] introduced
*
******************************************|************************************/

#ifndef ID_CHARSET_H
#define ID_CHARSET_H
const char *id_charset_h= "@(#) chr_iso.h   16.07.1998";
#endif

#ifndef THIS_CHARSET
#define THIS_CHARSET   "ISO Latin1"
#endif





/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#include "portab.h"





/*******************************************************************************
*
*     Recode ISO codepage into System codepage
*
*     Bei ANSI und ISO stimmen die Zeichen von \240 bis \377
*     ueberein, dennoch wird diese Tabelle mitgeschleppt, damit
*     in chars.c nicht unnoetige Abfragen erfolgen muessen.
*
******************************************|************************************/

typedef struct _iso2sys
{
   unsigned char   iso;                   /* */
   unsigned char   charsys;               /* */
}  ISO2SYS;


LOCAL const ISO2SYS   iso2sys_item[128] =
{
   { 128, 0   },
   { 129, 0   },
   { 130, 0   },
   { 131, 0   },
   { 132, 0   },
   { 133, 0   },
   { 134, 0   },
   { 135, 0   },
   { 136, 0   },
   { 137, 0   },
   { 138, 0   },
   { 139, 0   },
   { 140, 0   },
   { 141, 0   },
   { 142, 0   },
   { 143, 0   },
   { 144, 0   },
   { 145, 0   },
   { 146, 0   },
   { 147, 0   },
   { 148, 0   },
   { 149, 0   },
   { 150, 0   },
   { 151, 0   },
   { 152, 0   },
   { 153, 0   },
   { 154, 0   },
   { 155, 0   },
   { 156, 0   },
   { 157, 0   },
   { 158, 0   },
   { 159, 0   },
   { 160, 160 },
   { 161, 161 },
   { 162, 162 },
   { 163, 163 },
   { 164, 164 },
   { 165, 165 },
   { 166, 166 },
   { 167, 167 },
   { 168, 168 },
   { 169, 169 },
   { 170, 170 },
   { 171, 171 },
   { 172, 172 },
   { 173, 173 },
   { 174, 174 },
   { 175, 175 },
   { 176, 176 },
   { 177, 177 },
   { 178, 178 },
   { 179, 179 },
   { 180, 180 },
   { 181, 181 },
   { 182, 182 },
   { 183, 183 },
   { 184, 184 },
   { 185, 185 },
   { 186, 186 },
   { 187, 187 },
   { 188, 188 },
   { 189, 189 },
   { 190, 190 },
   { 191, 191 },
   { 192, 192 },
   { 193, 193 },
   { 194, 194 },
   { 195, 195 },
   { 196, 196 },
   { 197, 197 },
   { 198, 198 },
   { 199, 199 },
   { 200, 200 },
   { 201, 201 },
   { 202, 202 },
   { 203, 203 },
   { 204, 204 },
   { 205, 205 },
   { 206, 206 },
   { 207, 207 },
   { 208, 208 },
   { 209, 209 },
   { 210, 210 },
   { 211, 211 },
   { 212, 212 },
   { 213, 213 },
   { 214, 214 },
   { 215, 215 },
   { 216, 216 },
   { 217, 217 },
   { 218, 218 },
   { 219, 219 },
   { 220, 220 },
   { 221, 221 },
   { 222, 222 },
   { 223, 223 },
   { 224, 224 },
   { 225, 225 },
   { 226, 226 },
   { 227, 227 },
   { 228, 228 },
   { 229, 229 },
   { 230, 230 },
   { 231, 231 },
   { 232, 232 },
   { 233, 233 },
   { 234, 234 },
   { 235, 235 },
   { 236, 236 },
   { 237, 237 },
   { 238, 238 },
   { 239, 239 },
   { 240, 240 },
   { 241, 241 },
   { 242, 242 },
   { 243, 243 },
   { 244, 244 },
   { 245, 245 },
   { 246, 246 },
   { 247, 247 },
   { 248, 248 },
   { 249, 249 },
   { 250, 250 },
   { 251, 251 },
   { 252, 252 },
   { 253, 253 },
   { 254, 254 },
   { 255, 255 },
};





/*******************************************************************************
*
*     Recode System codepage into various codepages
*
******************************************|************************************/

typedef struct _chartable
{
   unsigned char   charsystem;            /* */
   char           *ascii;                 /* */
   char           *ansi;                  /* */
   char           *tex;                   /* */
   char           *html;                  /* */
   char           *ps;                    /* */
}  CHARTABLE;


LOCAL /*const*/ CHARTABLE   chrtab[128] =
{
   { 128, "",    "",      "",               "&#128;",   "\\200" },
   { 129, "",    "",      "",               "&#129;",   "\\201" },
   { 130, "",    "",      "",               "&#130;",   "\\202" },
   { 131, "",    "",      "",               "&#131;",   "\\203" },
   { 132, "",    "",      "",               "&#132;",   "\\204" },
   { 133, "",    "",      "",               "&#133;",   "\\205" },
   { 134, "",    "",      "",               "&#134;",   "\\206" },
   { 135, "",    "",      "",               "&#135;",   "\\207" },
   { 136, "",    "",      "",               "&#136;",   "\\210" },
   { 137, "",    "",      "",               "&#137;",   "\\211" },
   { 138, "",    "",      "",               "&#138;",   "\\212" },
   { 139, "",    "",      "",               "&#139;",   "\\213" },
   { 140, "",    "",      "",               "&#140;",   "\\214" },
   { 141, "",    "",      "",               "&#141;",   "\\215" },
   { 142, "",    "",      "",               "&#142;",   "\\216" },
   { 143, "",    "",      "",               "&#143;",   "\\217" },
   { 144, "",    "",      "",               "&#144;",   "\\220" },
   { 145, "",    "",      "",               "&#145;",   "\\221" },
   { 146, "",    "",      "",               "&#146;",   "\\222" },
   { 147, "",    "",      "",               "&#147;",   "\\223" },
   { 148, "",    "",      "",               "&#148;",   "\\224" },
   { 149, "",    "",      "",               "&#149;",   "\\225" },
   { 150, "",    "",      "",               "&#150;",   "\\226" },
   { 151, "",    "",      "",               "&#151;",   "\\227" },
   { 152, "",    "",      "",               "&#152;",   "\\230" },
   { 153, "",    "",      "",               "&#153;",   "\\231" },
   { 154, "",    "",      "",               "&#154;",   "\\232" },
   { 155, "",    "",      "",               "&#155;",   "\\233" },
   { 156, "",    "",      "",               "&#156;",   "\\234" },
   { 157, "",    "",      "",               "&#157;",   "\\235" },
   { 158, "",    "",      "",               "&#158;",   "\\236" },
   { 159, "",    "",      "",               "&#159;",   "\\237" },
   { 160, "",    "\\'A0", "",               "&#160;",   "\\240" },
   { 161, "!",   "\\'A1", "!`",             "&#161;",   "\\241" },
   { 162, "",    "\\'A2", "cent",           "&#162;",   "\\242" },
   { 163, "",    "\\'A3", "\\pounds{}",     "&#163;",   "\\243" },
   { 164, "",    "\\'A4", "",               "&#164;",   "\\244" },   /* general-currency sign */
   { 165, "",    "\\'A5", "yen",            "&#165;",   "\\245" },
   { 166, "",    "\\'A6", "$\\mid$",        "&#166;",   "\\246" },   /* broken-vertical-line */
   { 167, "",    "\\'A7", "\\S{}",          "&sect;",   "\\247" },
   { 168, "",    "\\'A8", "\\\"{ }",        "&#168;",   "\\250" },
   { 169, "(C)", "\\'A9", "\\copyright{}",  "&copy;",   "\\251" },
   { 170, "",    "\\'AA", "\\b{a}",         "&#170;",   "\\252" },
   { 171, "<",   "\\'AB", "\"<",            "&#171;",   "\\253" },
   { 172, "",    "\\'AC", "$\\neq$",        "&#172;",   "\\254" },
   { 173, "",    "\\'AD", "\\-",            "&#173;",   "\\255" },
   { 174, "(R)", "\\'AE", "(R)",            "&#174;",   "\\256" },
   { 175, "",    "\\'AF", "",               "&#175;",   "\\257" },   /* macron */
   { 176, "",    "\\'B0", "$\\circ$",       "&#176;",   "\\260" },
   { 177, "",    "\\'B1", "$\\pm$",         "&#177;",   "\\261" },
   { 178, "",    "\\'B2", "$^2$",           "&#178;",   "\\262" },
   { 179, "",    "\\'B3", "$^3$",           "&#179;",   "\\263" },
   { 180, "",    "\\'B4", "\\'{ }",         "&#180;",   "\\264" },
   { 181, "",    "\\'B5", "$\\mu$",         "&#181;",   "\\265" },
   { 182, "",    "\\'B6", "\\P{}",          "&#182;",   "\\266" },
   { 183, "",    "\\'B7", "\\cdot{}",       "&#183;",   "\\267" },
   { 184, "",    "\\'B8", "\\c{ }",         "&#184;",   "\\270" },
   { 185, "",    "\\'B9", "$^1$",           "&#185;",   "\\271" },
   { 186, "",    "\\'BA", "\\b{o}",         "&#186;",   "\\272" },
   { 187, ">",   "\\'BB", "\">",            "&#187;",   "\\273" },
   { 188, "1/4", "\\'BC", "$\\frac{1}{4}$", "&#188;",   "\\274" },
   { 189, "1/2", "\\'BD", "$\\frac{1}{2}$", "&#189;",   "\\275" },
   { 190, "3/4", "\\'BE", "$\\frac{3}{4}$", "&#180;",   "\\276" },
   { 191, "?",   "\\'BF", "?`",             "&#191;",   "\\277" },
   { 192, "A",   "\\'C0", "\\`{A}",         "&Agrave;", "\\300" },
   { 193, "A",   "\\'C1", "\\'{A}",         "&Aacute;", "\\301" },
   { 194, "A",   "\\'C2", "\\^{A}",         "&Acirc;",  "\\302" },
   { 195, "A",   "\\'C3", "\\~{A}",         "&Atilde;", "\\303" },
   { 196, "Ae",  "\\'C4", "{\\\"A}",        "&Auml;",   "\\304" },
   { 197, "A",   "\\'C5", "{\\AA}",         "&Aring;",  "\\305" },
   { 198, "AE",  "\\'C6", "{\\AE}",         "&AElig;",  "\\306" },
   { 199, "C",   "\\'C7", "\\c{C}",         "&Ccedil;", "\\307" },
   { 200, "E",   "\\'C8", "\\`{E}",         "&Egrave;", "\\310" },
   { 201, "E",   "\\'C9", "\\'{E}",         "&Eacute;", "\\311" },
   { 202, "E",   "\\'CA", "\\^{E}",         "&Ecirc;",  "\\312" },
   { 203, "E",   "\\'CB", "\\\"E",          "&Euml;",   "\\313" },
   { 204, "I",   "\\'CC", "\\`{I}",         "&Igrave;", "\\314" },
   { 205, "I",   "\\'CD", "\\'{I}",         "&Iacute;", "\\315" },
   { 206, "I",   "\\'CE", "\\^{I}",         "&Icirc;",  "\\316" },
   { 207, "I",   "\\'CF", "\\\"I",          "&Iuml;",   "\\317" },
   { 208, "N",   "\\'D0", "",               "&#208;",   "\\320" },   /* -D */
   { 209, "O",   "\\'D1", "\\~{N}",         "&Ntilde;", "\\321" },
   { 210, "O",   "\\'D2", "\\`{O}",         "&Ograve;", "\\322" },
   { 211, "O",   "\\'D3", "\\'{O}",         "&Oacute;", "\\323" },
   { 212, "O",   "\\'D4", "\\^{O}",         "&Ocirc;",  "\\324" },
   { 213, "O",   "\\'D5", "\\~{O}",         "&Otilde;", "\\325" },
   { 214, "Oe",  "\\'D6", "{\\\"O}",        "&Ouml;",   "\\326" },
   { 215, "x",   "\\'D7", "$\\times$",      "&#215;",   "\\327" },
   { 216, "O",   "\\'D8", "{\\O}",          "&Oslash;", "\\330" },
   { 217, "U",   "\\'D9", "\\`{U}",         "&Ugrave;", "\\331" },
   { 218, "U",   "\\'DA", "\\'{U}",         "&Uacute;", "\\332" },
   { 219, "U",   "\\'DB", "\\^{U}",         "&Ucirc;",  "\\333" },
   { 220, "Ue",  "\\'DC", "{\\\"U}",        "&Uuml;",   "\\334" },
   { 221, "Y",   "\\'DD", "\\'{Y}",         "&Yacute;", "\\335" },
   { 222, "",    "\\'DE", "",               "&#222;",   "\\336" },   /* |o */
   { 223, "ss",  "\\'DF", "{\\ss}",         "&szlig;",  "\\337" },
   { 224, "a",   "\\'E0", "\\`{a}",         "&agrave;", "\\340" },
   { 225, "a",   "\\'E1", "\\'{a}",         "&aacute;", "\\341" },
   { 226, "a",   "\\'E2", "\\^{a}",         "&acirc;",  "\\342" },
   { 227, "a",   "\\'E3", "\\~{a}",         "&atilde;", "\\343" },
   { 228, "ae",  "\\'E4", "{\\\"a}",        "&auml;",   "\\344" },
   { 229, "a",   "\\'E5", "{\\aa}",         "&aring;",  "\\345" },
   { 230, "ae",  "\\'E6", "{\\ae}",         "&aelig;",  "\\346" },
   { 231, "c",   "\\'E7", "\\c{c}",         "&ccedil;", "\\347" },
   { 232, "e",   "\\'E8", "\\`{e}",         "&egrave;", "\\350" },
   { 233, "e",   "\\'E9", "\\'{e}",         "&eacute;", "\\351" },
   { 234, "e",   "\\'EA", "\\^{e}",         "&ecirc;",  "\\352" },
   { 235, "e",   "\\'EB", "\\\"e",          "&euml;",   "\\353" },
   { 236, "i",   "\\'EC", "\\`{i}",         "&igrave;", "\\354" },
   { 237, "i",   "\\'ED", "\\'{i}",         "&iacute;", "\\355" },
   { 238, "i",   "\\'EE", "\\^{i}",         "&icirc;",  "\\356" },
   { 239, "i",   "\\'EF", "\\\"{i}",        "&iuml;",   "\\357" },
   { 240, "",    "\\'F0", "",               "&#240;",   "\\360" },   /* THORN */
   { 241, "n",   "\\'F1", "\\~{n}",         "&ntilde;", "\\361" },
   { 242, "o",   "\\'F2", "\\`{o}",         "&ograve;", "\\362" },
   { 243, "o",   "\\'F3", "\\'{o}",         "&oacute;", "\\363" },
   { 244, "o",   "\\'F4", "\\^{o}",         "&ocirc;",  "\\364" },
   { 245, "o",   "\\'F5", "\\~{o}",         "&otilde;", "\\365" },
   { 246, "oe",  "\\'F6", "{\\\"o}",        "&ouml;",   "\\366" },
   { 247, "",    "\\'F7", "$\\div$",        "&#247;",   "\\367" },
   { 248, "o",   "\\'F8", "{\\o}",          "&oslash;", "\\370" },
   { 249, "u",   "\\'F9", "\\`{u}",         "&ugrave;", "\\371" },
   { 250, "u",   "\\'FA", "\\'{u}",         "&uacute;", "\\372" },
   { 251, "u",   "\\'FB", "\\^{u}",         "&ucirc;",  "\\373" },
   { 252, "ue",  "\\'FC", "{\\\"u}",        "&uuml;",   "\\374" },
   { 253, "y",   "\\'FD", "\\'{y}",         "&yacute;", "\\375" },
   { 254, "",    "\\'FE", "",               "&#254;",   "\\376" },   /* |B */
   { 255, "y",   "\\'FF", "\\\"{y}",        "&yuml;",   "\\377" }
};





/*******************************************************************************
*
*     Recode 'Universal codepage' into ASCII codepage
*
******************************************|************************************/

typedef struct _uni2systab
{
   char           *uni;                   /* */
   unsigned char  *system;                /* */
}  UNI2SYSTAB;


#define UNI2SYSTABSIZE   64


LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   { "(!\"a)", "\344" },
   { "(!\"e)", "\353" },
   { "(!\"i)", "\357" },
   { "(!\"o)", "\366" },
   { "(!\"u)", "\374" },
   { "(!\"y)", "\377" },
   { "(!\"s)", "\337" },
   { "(!\"A)", "\304" },
   { "(!\"E)", "\313" },
   { "(!\"I)", "\317" },
   { "(!\"O)", "\326" },
   { "(!\"U)", "\334" },
   { "(!\"Y)", "\237" },                  /* 13 */

   { "(!'a)",  "\341" },
   { "(!'e)",  "\351" },
   { "(!'i)",  "\355" },
   { "(!'o)",  "\363" },
   { "(!'u)",  "\372" },
   { "(!'y)",  "\375" },
   { "(!'A)",  "\301" },
   { "(!'E)",  "\311" },
   { "(!'I)",  "\315" },
   { "(!'O)",  "\323" },
   { "(!'U)",  "\332" },
   { "(!'Y)",  "\335" },                  /* 12 */

   { "(!`a)",  "\340" },
   { "(!`e)",  "\350" },
   { "(!`i)",  "\354" },
   { "(!`o)",  "\362" },
   { "(!`u)",  "\371" },
   { "(!`A)",  "\300" },
   { "(!`E)",  "\310" },
   { "(!`I)",  "\314" },
   { "(!`O)",  "\322" },
   { "(!`U)",  "\331" },                  /* 10 */

   { "(!^a)",  "\342" },
   { "(!^e)",  "\352" },
   { "(!^i)",  "\356" },
   { "(!^o)",  "\364" },
   { "(!^u)",  "\373" },
   { "(!^A)",  "\302" },
   { "(!^E)",  "\312" },
   { "(!^I)",  "\316" },
   { "(!^O)",  "\324" },
   { "(!^U)",  "\333" },                  /* 10 */

   { "(!~a)",  "\343" },
   { "(!~n)",  "\361" },
   { "(!~o)",  "\365" },
   { "(!~A)",  "\303" },
   { "(!~N)",  "\321" },
   { "(!~O)",  "\325" },                  /*  6 */

   { "(!.a)",  "\345" },
   { "(!.A)",  "\305" },                  /*  2 */

   { "(!&ae)", "\346" },
   { "(!&AE)", "\306" },
   { "(!&oe)", "\234" },
   { "(!&OE)", "\214" },                  /*  4 */

   { "(!,c)",  "\347" },
   { "(!,C)",  "\307" },                  /*  2 */

   { "(!_a)",  "\252" },
   { "(!_o)",  "\272" },                  /*  2 */

   { "(!\\o)", "\370" },
   { "(!\\O)", "\330" },                  /*  2 */

   { "(!#S)",  "\247" },
};





/******************************************************************************
*
*  u_CODE_ISO[]:
*     Unicode named codepage for ISO encoding (cp1252)
*
******************************************|************************************/

static unsigned   u_CODE_ISO[] =          /* CODE_ISO */
{
   U_NUL,                                 /* 0x00  NULl */
   U_SOH,                                 /* 0x01  Start Of Heading */
   U_STX,                                 /* 0x02  Start of TeXt */
   U_ETX,                                 /* 0x03  End of TeXt */
   U_EOT,                                 /* 0x04  End Of Transmission */
   U_ENQ,                                 /* 0x05  ENQuiry */
   U_ACK,                                 /* 0x06  ACKnowledge */
   U_BEL,                                 /* 0x07  BELl */
   U_BS,                                  /* 0x08  BackSpace */
   U_HT,                                  /* 0x09  Horizontal Tabulation */
   U_LF,                                  /* 0x0a  Line Feed */
   U_VT,                                  /* 0x0b  Vertical Tabulation */
   U_FF,                                  /* 0x0c  Form Feed */
   U_CR,                                  /* 0x0d  Carriage Return */
   U_SO,                                  /* 0x0e  Shift Out */
   U_SI,                                  /* 0x0f  Shift In */
   U_DLE,                                 /* 0x10  Data Link Escape */
   U_DC1,                                 /* 0x11  Device Control 1 */
   U_DC2,                                 /* 0x12  Device Control 2 */
   U_DC3,                                 /* 0x13  Device Control 3 */
   U_DC4,                                 /* 0x14  Device Control 4 */
   U_NAK,                                 /* 0x15  Negative AcKnowledge */
   U_SYN,                                 /* 0x16  SYNchronous idle */
   U_ETB,                                 /* 0x17  End of Transmission Block */
   U_CAN,                                 /* 0x18  CANcel */
   U_EM,                                  /* 0x19  End of Medium */
   U_SUB,                                 /* 0x1a  SUBstitute */
   U_ESC,                                 /* 0x1b  ESCape */
   U_FS,                                  /* 0x1c  File Separator */
   U_GS,                                  /* 0x1d  Group Separator */
   U_RS,                                  /* 0x1e  Record Separator */
   U_US,                                  /* 0x1f  Unit Separator */

   U_SP,                                  /* 0x20  SPace */
   U_ExclamationMark,                     /* 0x21  ! */
   U_QuotationMark,                       /* 0x22  " */
   U_NumberSign,                          /* 0x23  # */
   U_DollarSign,                          /* 0x24  $ */
   U_PercentSign,                         /* 0x25  % */
   U_Ampersand,                           /* 0x26  & */
   U_Apostrophe,                          /* 0x27  ' */
   U_OpeningParenthesis,                  /* 0x28  ( */
   U_ClosingParenthesis,                  /* 0x29  ) */
   U_Asterisk,                            /* 0x2A  * */
   U_PlusSign,                            /* 0x2B  + */
   U_Comma,                               /* 0x2C  , */
   U_HyphenMinus,                         /* 0x2D  - */
   U_Period,                              /* 0x2E  . */
   U_Slash,                               /* 0x2F  / */
   U_Digit0,                              /* 0x30  0 */
   U_Digit1,                              /* 0x31  1 */
   U_Digit2,                              /* 0x32  2 */
   U_Digit3,                              /* 0x33  3 */
   U_Digit4,                              /* 0x34  4 */
   U_Digit5,                              /* 0x35  5 */
   U_Digit6,                              /* 0x36  6 */
   U_Digit7,                              /* 0x37  7 */
   U_Digit8,                              /* 0x38  8 */
   U_Digit9,                              /* 0x39  9 */
   U_Colon,                               /* 0x3A  : */
   U_Semicolon,                           /* 0x3B  ; */
   U_LessThanSign,                        /* 0x3C  < */
   U_EqualsSign,                          /* 0x3D  = */
   U_GreaterThanSign,                     /* 0x3E  > */
   U_QuestionMark,                        /* 0x3F  ? */
   U_CommercialAt,                        /* 0x40  @ */
   U_LatinCapitalLetterA,                 /* 0x41  A */
   U_LatinCapitalLetterB,                 /* 0x42  B */
   U_LatinCapitalLetterC,                 /* 0x43  C */
   U_LatinCapitalLetterD,                 /* 0x44  D */
   U_LatinCapitalLetterE,                 /* 0x45  E */
   U_LatinCapitalLetterF,                 /* 0x46  F */
   U_LatinCapitalLetterG,                 /* 0x47  G */
   U_LatinCapitalLetterH,                 /* 0x48  H */
   U_LatinCapitalLetterI,                 /* 0x49  I */
   U_LatinCapitalLetterJ,                 /* 0x4A  J */
   U_LatinCapitalLetterK,                 /* 0x4B  K */
   U_LatinCapitalLetterL,                 /* 0x4C  L */
   U_LatinCapitalLetterM,                 /* 0x4D  M */
   U_LatinCapitalLetterN,                 /* 0x4E  N */
   U_LatinCapitalLetterO,                 /* 0x4F  O */
   U_LatinCapitalLetterP,                 /* 0x50  P */
   U_LatinCapitalLetterQ,                 /* 0x51  Q */
   U_LatinCapitalLetterR,                 /* 0x52  R */
   U_LatinCapitalLetterS,                 /* 0x53  S */
   U_LatinCapitalLetterT,                 /* 0x54  T */
   U_LatinCapitalLetterU,                 /* 0x55  U */
   U_LatinCapitalLetterV,                 /* 0x56  V */
   U_LatinCapitalLetterW,                 /* 0x57  W */
   U_LatinCapitalLetterX,                 /* 0x58  X */
   U_LatinCapitalLetterY,                 /* 0x59  Y */
   U_LatinCapitalLetterZ,                 /* 0x5A  Z */
   U_OpeningSquareBracket,                /* 0x5B  [ */
   U_Backslash,                           /* 0x5C  \ */
   U_ClosingSquareBracket,                /* 0x5D  ] */
   U_CircumflexAccent,                    /* 0x5E  ^ */
   U_SpacingUnderscore,                   /* 0x5F  _ */
   U_GraveAccent,                         /* 0x60  ` */
   U_LatinCapitalLetterA,                 /* 0x61  a */
   U_LatinCapitalLetterB,                 /* 0x62  b */
   U_LatinCapitalLetterC,                 /* 0x63  c */
   U_LatinCapitalLetterD,                 /* 0x64  d */
   U_LatinCapitalLetterE,                 /* 0x65  e */
   U_LatinCapitalLetterF,                 /* 0x66  f */
   U_LatinCapitalLetterG,                 /* 0x67  g */
   U_LatinCapitalLetterH,                 /* 0x68  h */
   U_LatinCapitalLetterI,                 /* 0x69  i */
   U_LatinCapitalLetterJ,                 /* 0x6A  j */
   U_LatinCapitalLetterK,                 /* 0x6B  k */
   U_LatinCapitalLetterL,                 /* 0x6C  l */
   U_LatinCapitalLetterM,                 /* 0x6D  m */
   U_LatinCapitalLetterN,                 /* 0x6E  n */
   U_LatinCapitalLetterO,                 /* 0x6F  o */
   U_LatinCapitalLetterP,                 /* 0x70  p */
   U_LatinCapitalLetterQ,                 /* 0x71  q */
   U_LatinCapitalLetterR,                 /* 0x72  r */
   U_LatinCapitalLetterS,                 /* 0x73  s */
   U_LatinCapitalLetterT,                 /* 0x74  t */
   U_LatinCapitalLetterU,                 /* 0x75  u */
   U_LatinCapitalLetterV,                 /* 0x76  v */
   U_LatinCapitalLetterW,                 /* 0x77  w */
   U_LatinCapitalLetterX,                 /* 0x78  x */
   U_LatinCapitalLetterY,                 /* 0x79  y */
   U_LatinCapitalLetterZ,                 /* 0x7A  z */
   U_OpeningCurlyBracket,                 /* 0x7B  { */
   U_VerticalLine,                        /* 0x7C  | */
   U_ClosingCurlyBracket,                 /* 0x7D  } */
   U_Tilde,                               /* 0x7E  ~ */
   U_DEL,                                 /* 0x7F  Delete */

   U_EuroSign,                            /* 0x80  U_EuroSign */
   U_NIL,                                 /* 0x81  --- UNDEFINED --- */
   U_SingleLow9QuotationMark,             /* 0x82  U_SingleLow9QuotationMark */
   U_LatinSmallLetterScriptF,             /* 0x83  U_LatinSmallLetterScriptF */
   U_DoubleLow9QuotationMark,             /* 0x84  U_DoubleLow9QuotationMark */
   U_HorizontalEllipsis,                  /* 0x85  U_HorizontalEllipsis */
   U_Dagger,                              /* 0x86  U_Dagger */
   U_DoubleDagger,                        /* 0x87  U_DoubleDagger */
   U_ModifierLetterCircumflexAccent,      /* 0x88  U_ModifierLetterCircumflexAccent */
   U_PerMilleSign,                        /* 0x89  U_PerMilleSign */
   U_LatinCapitalLetterSWithCaron,        /* 0x8a  U_LatinCapitalLetterSWithCaron */
   U_LeftPointingSingleGuillemet,         /* 0x8b  U_LeftPointingSingleGuillemet */
   U_LatinCapitalLigatureOE,              /* 0x8c  U_LatinCapitalLigatureOE */
   U_NIL,                                 /* 0x8d  --- UNDEFINED --- */
   U_LatinCapitalLetterZWithCaron,        /* 0x8e  U_LatinCapitalLetterZWithCaron */
   U_NIL,                                 /* 0x8f  --- UNDEFINED --- */
                                          
   U_NIL,                                 /* 0x90  --- UNDEFINED --- */
   U_LeftSingleQuotationMark,             /* 0x91  U_LeftSingleQuotationMark */
   U_RightSingleQuotationMark,            /* 0x92  U_RightSingleQuotationMark */
   U_LeftDoubleQuotationMark,             /* 0x93  U_LeftDoubleQuotationMark */
   U_RightDoubleQuotationMark,            /* 0x94  U_RightDoubleQuotationMark */
   U_Bullet,                              /* 0x95  U_Bullet */
   U_EnDash,                              /* 0x96  U_EnDash */
   U_EmDash,                              /* 0x97  U_EmDash */
   U_SmallTilde,                          /* 0x98  U_SmallTilde */
   U_TradeMarkSign,                       /* 0x99  U_TradeMarkSign */
   U_LatinSmallLetterSWithCaron,          /* 0x9a  U_LatinSmallLetterSWithCaron */
   U_RightPointingSingleGuillemet,        /* 0x9b  U_RightPointingSingleGuillemet */
   U_LatinSmallLigatureOE,                /* 0x9c  U_LatinSmallLigatureOE */
   U_NIL,                                 /* 0x9d  --- UNDEFINED --- */
   U_LatinSmallLetterZWithCaron,          /* 0x9e  U_LatinSmallLetterZWithCaron */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0x9f  U_LatinCapitalLetterYWithDiaeresis */
                                          
   U_NB_SP,                               /* 0xa0  U_NB_SP */
   U_InvertedExclamationMark,             /* 0xa1  U_InvertedExclamationMark */
   U_CentSign,                            /* 0xa2  U_CentSign */
   U_PoundSign,                           /* 0xa3  U_PoundSign */
   U_CurrencySign,                        /* 0xa4  U_CurrencySign */
   U_YenSign,                             /* 0xa5  U_YenSign */
   U_BrokenVerticalBar,                   /* 0xa6  U_BrokenVerticalBar */
   U_SectionSign,                         /* 0xa7  U_SectionSign */
   U_Diaeresis,                           /* 0xa8  U_Diaeresis */
   U_CopyrightSign,                       /* 0xa9  U_CopyrightSign */
   U_FeminineOrdinalIndicator,            /* 0xaa  U_FeminineOrdinalIndicator */
   U_LeftPointingGuillemet,               /* 0xab  U_LeftPointingGuillemet */
   U_NotSign,                             /* 0xac  U_NotSign */
   U_SoftHyphen,                          /* 0xad  U_SoftHyphen */
   U_RegisteredSign,                      /* 0xae  U_RegisteredSign */
   U_Macron,                              /* 0xaf  U_Macron */
   
   U_DegreeSign,                          /* 0xb0  U_DegreeSign */
   U_PlusMinusSign,                       /* 0xb1  U_PlusMinusSign */
   U_SuperscriptTwo,                      /* 0xb2  U_SuperscriptTwo */
   U_SuperscriptThree,                    /* 0xb3  U_SuperscriptThree */
   U_AcuteAccent,                         /* 0xb4  U_AcuteAccent */
   U_MicroSign,                           /* 0xb5  U_MicroSign */
   U_ParagraphSign,                       /* 0xb6  U_ParagraphSign */
   U_MiddleDot,                           /* 0xb7  U_MiddleDot */
   U_Cedilla,                             /* 0xb8  U_Cedilla */
   U_SuperscriptOne,                      /* 0xb9  U_SuperscriptOne */
   U_MasculineOrdinalIndicator,           /* 0xba  U_MasculineOrdinalIndicator */
   U_RightPointingGuillemet,              /* 0xbb  U_RightPointingGuillemet */
   U_VulgarFractionOneQuarter,            /* 0xbc  U_VulgarFractionOneQuarter */
   U_VulgarFractionOneHalf,               /* 0xbd  U_VulgarFractionOneHalf */
   U_VulgarFractionThreeQuarters,         /* 0xbe  U_VulgarFractionThreeQuarters */
   U_InvertedQuestionMark,                /* 0xbf  U_InvertedQuestionMark */
                                          
   U_LatinCapitalLetterAWithGrave,        /* 0xc0  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterAWithAcute,        /* 0xc1  U_LatinCapitalLetterAWithAcute */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xc2  U_LatinCapitalLetterAWithCircumflex */
   U_LatinCapitalLetterAWithTilde,        /* 0xc3  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0xc4  U_LatinCapitalLetterAWithDiaeresis */
   U_LatinCapitalLetterAWithRingAbove,    /* 0xc5  U_LatinCapitalLetterAWithRingAbove */
   U_LatinCapitalLigatureAE,              /* 0xc6  U_LatinCapitalLigatureAE */
   U_LatinCapitalLetterCWithCedilla,      /* 0xc7  U_LatinCapitalLetterCWithCedilla */
   U_LatinCapitalLetterEWithGrave,        /* 0xc8  U_LatinCapitalLetterEWithGrave */
   U_LatinCapitalLetterEWithAcute,        /* 0xc9  U_LatinCapitalLetterEWithAcute */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xca  U_LatinCapitalLetterEWithCircumflex */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xcb  U_LatinCapitalLetterEWithDiaeresis */
   U_LatinCapitalLetterIWithGrave,        /* 0xcc  U_LatinCapitalLetterIWithGrave */
   U_LatinCapitalLetterIWithAcute,        /* 0xcd  U_LatinCapitalLetterIWithAcute */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xce  U_LatinCapitalLetterIWithCircumflex */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xcf  U_LatinCapitalLetterIWithDiaeresis */
                                          
   U_LatinCapitalLetterEth,               /* 0xd0  U_LatinCapitalLetterEth */
   U_LatinCapitalLetterNWithTilde,        /* 0xd1  U_LatinCapitalLetterNWithTilde */
   U_LatinCapitalLetterOWithGrave,        /* 0xd2  U_LatinCapitalLetterOWithGrave */
   U_LatinCapitalLetterOWithAcute,        /* 0xd3  U_LatinCapitalLetterOWithAcute */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xd4  U_LatinCapitalLetterOWithCircumflex */
   U_LatinCapitalLetterOWithTilde,        /* 0xd5  U_LatinCapitalLetterOWithTilde */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0xd6  U_LatinCapitalLetterOWithDiaeresis */
   U_MultiplicationSign,                  /* 0xd7  U_MultiplicationSign */
   U_LatinCapitalLetterOSlash,            /* 0xd8  U_LatinCapitalLetterOSlash */
   U_LatinCapitalLetterUWithGrave,        /* 0xd9  U_LatinCapitalLetterUWithGrave */
   U_LatinCapitalLetterUWithAcute,        /* 0xda  U_LatinCapitalLetterUWithAcute */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xdb  U_LatinCapitalLetterUWithCircumflex */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0xdc  U_LatinCapitalLetterUWithDiaeresis */
   U_LatinCapitalLetterYWithAcute,        /* 0xdd  U_LatinCapitalLetterYWithAcute */
   U_LatinCapitalLetterThorn,             /* 0xde  U_LatinCapitalLetterThorn */
   U_LatinSmallLetterSharpS,              /* 0xdf  U_LatinSmallLetterSharpS */
                                          
   U_LatinSmallLetterAWithGrave,          /* 0xe0  U_LatinSmallLetterAWithGrave */
   U_LatinSmallLetterAWithAcute,          /* 0xe1  U_LatinSmallLetterAWithAcute */
   U_LatinSmallLetterAWithCircumflex,     /* 0xe2  U_LatinSmallLetterAWithCircumflex */
   U_LatinSmallLetterAWithTilde,          /* 0xe3  U_LatinSmallLetterAWithTilde */
   U_LatinSmallLetterAWithDiaeresis,      /* 0xe4  U_LatinSmallLetterAWithDiaeresis */
   U_LatinSmallLetterAWithRingAbove,      /* 0xe5  U_LatinSmallLetterAWithRingAbove */
   U_LatinSmallLigatureAE,                /* 0xe6  U_LatinSmallLigatureAE */
   U_LatinSmallLetterCWithCedilla,        /* 0xe7  U_LatinSmallLetterCWithCedilla */
   U_LatinSmallLetterEWithGrave,          /* 0xe8  U_LatinSmallLetterEWithGrave */
   U_LatinSmallLetterEWithAcute,          /* 0xe9  U_LatinSmallLetterEWithAcute */
   U_LatinSmallLetterEWithCircumflex,     /* 0xea  U_LatinSmallLetterEWithCircumflex */
   U_LatinSmallLetterEWithDiaeresis,      /* 0xeb  U_LatinSmallLetterEWithDiaeresis */
   U_LatinSmallLetterIWithGrave,          /* 0xec  U_LatinSmallLetterIWithGrave */
   U_LatinSmallLetterIWithAcute,          /* 0xed  U_LatinSmallLetterIWithAcute */
   U_LatinSmallLetterIWithCircumflex,     /* 0xee  U_LatinSmallLetterIWithCircumflex */
   U_LatinSmallLetterIWithDiaeresis,      /* 0xef  U_LatinSmallLetterIWithDiaeresis */
                                          
   U_LatinSmallLetterEth,                 /* 0xf0  U_LatinSmallLetterEth */
   U_LatinSmallLetterNWithTilde,          /* 0xf1  U_LatinSmallLetterNWithTilde */
   U_LatinSmallLetterOWithGrave,          /* 0xf2  U_LatinSmallLetterOWithGrave */
   U_LatinSmallLetterOWithAcute,          /* 0xf3  U_LatinSmallLetterOWithAcute */
   U_LatinSmallLetterOWithCircumflex,     /* 0xf4  U_LatinSmallLetterOWithCircumflex */
   U_LatinSmallLetterOWithTilde,          /* 0xf5  U_LatinSmallLetterOWithTilde */
   U_LatinSmallLetterOWithDiaeresis,      /* 0xf6  U_LatinSmallLetterOWithDiaeresis */
   U_DivisionSign,                        /* 0xf7  U_DivisionSign */
   U_LatinSmallLetterOSlash,              /* 0xf8  U_LatinSmallLetterOSlash */
   U_LatinSmallLetterUWithGrave,          /* 0xf9  U_LatinSmallLetterUWithGrave */
   U_LatinSmallLetterUWithAcute,          /* 0xfa  U_LatinSmallLetterUWithAcute */
   U_LatinSmallLetterUWithCircumflex,     /* 0xfb  U_LatinSmallLetterUWithCircumflex */
   U_LatinSmallLetterUWithDiaeresis,      /* 0xfc  U_LatinSmallLetterUWithDiaeresis */
   U_LatinSmallLetterYWithAcute,          /* 0xfd  U_LatinSmallLetterYWithAcute */
   U_LatinSmallLetterThorn,               /* 0xfe  U_LatinSmallLetterThorn */
   U_LatinSmallLetterYWithDiaeresis       /* 0xff  U_LatinSmallLetterYWithDiaeresis */
};


