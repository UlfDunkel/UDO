/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_mac.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer Apple Macintosh
*                 gemaess Scan von Martin Osieka @ OF2
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
*    fd  Feb 12: - all octal chars converted into decimal values
*                - u_CODE_MAC[] introduced (Mac OS Roman)
*
******************************************|************************************/

#ifndef ID_CHARSET_H
#define ID_CHARSET_H
const char  *id_charset_h = "@(#) chr_mac.h   $date$";
#endif

#ifndef THIS_CHARSET
#define THIS_CHARSET   "MacOS"
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
******************************************|************************************/

typedef struct _iso2sys
{
   unsigned char   iso;                   /* */
   unsigned char   charsys;               /* */
}  ISO2SYS;


LOCAL const ISO2SYS   iso2sys_item[128] =
{
   { 128,   0 },                          /* null */
   { 129,   0 },                          /* null */
   { 130, 226 },                          /* '' (9u) */
   { 131, 196 },                          /* #f */
   { 132, 227 },                          /* "" (99u) */
   { 133, 201 },                          /* !.. */
   { 134, 160 },                          /* #dag */
   { 135, 224 },                          /* 2x#dag */
   { 136, 246 },                          /* #circ */
   { 137, 228 },                          /* #promill */
   { 138, 'S' },                          /* vS */   /* !!!! */
   { 139, 220 },                          /* < */
   { 140, 206 },                          /* &OE */
   { 141,   0 },                          /* null */
   { 142,   0 },                          /* null */
   { 143,   0 },                          /* null */
   { 144,   0 },                          /* null */
   { 145, 212 },                          /* ` (6o) */
   { 146, 213 },                          /* '' (9o) */
   { 147, 210 },                          /* "" (66o) */
   { 148, 211 },                          /* "" (99o) */
   { 149, 165 },                          /* #bullet */
   { 150, 208 },                          /* -- */
   { 151, 209 },                          /* --- */
   { 152, '~' },                          /* !~ */   /* !!!! */
   { 153, 170 },                          /* #tm */
   { 154, 's' },                          /* vs */   /* !!!! */
   { 155, 221 },                          /* > */
   { 156, 207 },                          /* &oe */
   { 157,   0 },                          /* null */
   { 158,   0 },                          /* null */
   { 159, 217 },                          /* "Y */
   { 160,   0 },                          /* null */
   { 161, 193 },                          /* #! */
   { 162, 162 },                          /* #cent */
   { 163, 163 },                          /* #pound */
   { 164, 219 },                          /* general currency */
   { 165, 180 },                          /* #yen */
   { 166, '|' },                          /* broken dash */   /* !!!! */
   { 167, 164 },                          /* #sect */
   { 168, 172 },                          /* #" */
   { 169, 169 },                          /* #copy */
   { 170, 187 },                          /* _a */
   { 171, 199 },                          /* #< */
   { 172, 194 },                          /* #neg */
   { 173,   0 },                          /* strich */
   { 174, 168 },                          /* #reg */
   { 175,   0 },                          /* #macron */
   { 176, 161 },                          /* #degree */
   { 177, 177 },                          /* #pm */
   { 178,   0 },                          /* #^2 */
   { 179,   0 },                          /* #^3 */
   { 180, 171 },                          /* #' */
   { 181, 181 },                          /* #mu */
   { 182, 166 },                          /* #p */
   { 183, 250 },                          /* #cdot */
   { 184, 252 },                          /* cedille */
   { 185, 245 },                          /* #^1 */
   { 186, 188 },                          /* _o */
   { 187, 200 },                          /* #> */
   { 188,   0 },                          /* #1/4 */
   { 189,   0 },                          /* #1/2 */
   { 190,   0 },                          /* #3/4 */
   { 191, 192 },                          /* #? */
   { 192, 203 },                          /* `A */
   { 193, 231 },                          /* 'A */
   { 194, 229 },                          /* ^A */
   { 195, 204 },                          /* ~A */
   { 196, 128 },                          /* "A */
   { 197, 129 },                          /* .A */
   { 198, 174 },                          /* &AE */
   { 199, 130 },                          /* ,C */
   { 200, 233 },                          /* `E */
   { 201, 131 },                          /* 'E */
   { 202, 230 },                          /* ^E */
   { 203, 232 },                          /* "E */
   { 204, 237 },                          /* `I */
   { 205, 234 },                          /* 'I */
   { 206, 235 },                          /* ^I */
   { 207, 236 },                          /* "I */
   { 208,   0 },                          /* -D */
   { 209, 132 },                          /* ~N */
   { 210, 241 },                          /* `O */
   { 211, 238 },                          /* 'O */
   { 212, 239 },                          /* ^O */
   { 213, 205 },                          /* ~O */
   { 214, 133 },                          /* "O */
   { 215, 'x' },                          /* #times */   /* !!!! */
   { 216, 175 },                          /* /O */
   { 217, 244 },                          /* `U */
   { 218, 242 },                          /* 'U */
   { 219, 243 },                          /* ^U */
   { 220, 134 },                          /* "U */
   { 221, 'Y' },                          /* 'Y */   /* !!!! */
   { 222,   0 },                          /* |b */
   { 223, 167 },                          /* "s (sz) */
   { 224, 136 },                          /* `a */
   { 225, 135 },                          /* 'a */
   { 226, 137 },                          /* ^a */
   { 227, 139 },                          /* ~a */
   { 228, 138 },                          /* "a */
   { 229, 140 },                          /* .a */
   { 230, 190 },                          /* &ae */
   { 231, 141 },                          /* ,c */
   { 232, 143 },                          /* `e */
   { 233, 142 },                          /* 'e */
   { 234, 144 },                          /* ^e */
   { 235, 145 },                          /* "e */
   { 236, 147 },                          /* `i */
   { 237, 146 },                          /* 'i */
   { 238, 148 },                          /* ^i */
   { 239, 149 },                          /* "i */
   { 240,   0 },                          /* o|'' */   /* !!!! */
   { 241, 150 },                          /* ~n */
   { 242, 152 },                          /* `o */
   { 243, 151 },                          /* 'o */
   { 244, 153 },                          /* ^o */
   { 245, 155 },                          /* ~o */
   { 246, 154 },                          /* "o */
   { 247, 214 },                          /* #div */
   { 248, 191 },                          /* /o */
   { 249, 157 },                          /* `u */
   { 250, 156 },                          /* 'u */
   { 251, 158 },                          /* ^u */
   { 252, 159 },                          /* "u */
   { 253, 'y' },                          /* 'y */   /* !!!! */
   { 254,   0 },                          /* |B */
   { 255, 216 }                           /* "y */
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


LOCAL /* const */ CHARTABLE   chrtab[128] =
{
   { 128, "Ae",   "\\'C4",        "{\\\"A}",       "&Auml;",   "\\304" },
   { 129, "A",    "\\'C5",        "{\\AA}",        "&Aring;",  "\\305" },
   { 130, "C",    "\\'C7",        "\\c{C}",        "&Ccedil;", "\\307" },
   { 131, "E",    "\\'C9",        "\\'{E}",        "&Eacute;", "\\311" },
   { 132, "N",    "\\'D1",        "\\~{N}",        "&Ntilde;", "\\321" },
   { 133, "Oe",   "\\'D6",        "{\\\"O}",       "&Ouml;",   "\\326" },
   { 134, "Ue",   "\\'DC",        "{\\\"U}",       "&Uuml;",   "\\334" },
   { 135, "a",    "\\'E1",        "\\'{a}",        "&aacute;", "\\341" },

   { 136, "a",    "\\'E0",        "\\`{a}",        "&agrave;", "\\340" },
   { 137, "a",    "\\'E2",        "\\^{a}",        "&acirc;",  "\\342" },
   { 138, "ae",   "\\'E4",        "{\\\"a}",       "&auml;",   "\\344" },
   { 139, "a",    "\\'E3",        "\\~{a}",        "&atilde;", "\\343" },
   { 140, "a",    "\\'E5",        "{\\aa}",        "&aring;",  "\\345" },
   { 141, "c",    "\\'E7",        "\\c{c}",        "&ccedil;", "\\347" },
   { 142, "e",    "\\'E9",        "\\'{e}",        "&eacute;", "\\351" },
   { 143, "e",    "\\'E8",        "\\`{e}",        "&egrave;", "\\350" },

   { 144, "e",    "\\'EA",        "\\^{e}",        "&ecirc;",  "\\352" },
   { 145, "e",    "\\'EB",        "\\\"{e}",       "&euml;",   "\\353" },
   { 146, "i",    "\\'ED",        "\\'{i}",        "&iacute;", "\\355" },
   { 147, "i",    "\\'EC",        "\\`{i}",        "&igrave;", "\\354" },
   { 148, "i",    "\\'EE",        "\\^{i}",        "&icirc;",  "\\356" },
   { 149, "i",    "\\'EF",        "\\\"{i}",       "&iuml;",   "\\357" },
   { 150, "n",    "\\'F1",        "\\~{n}",        "&ntilde;", "\\361" },
   { 151, "o",    "\\'F3",        "\\'{o}",        "&oacute;", "\\363" },

   { 152, "o",    "\\'F2",        "\\`{o}",        "&ograve;", "\\362" },
   { 153, "o",    "\\'F4",        "\\^{o}",        "&ocirc;",  "\\364" },
   { 154, "oe",   "\\'F6",        "{\\\"o}",       "&ouml;",   "\\366" },
   { 155, "o",    "\\'F5",        "\\~{o}",        "&otilde;", "\\365" },
   { 156, "u",    "\\'FA",        "\\'{u}",        "&uacute;", "\\372" },
   { 157, "u",    "\\'F9",        "\\`{u}",        "&ugrave;", "\\371" },
   { 158, "u",    "\\'FB",        "\\^{u}",        "&ucirc;",  "\\373" },
   { 159, "ue",   "\\'FC",        "{\\\"u}",       "&uuml;",   "\\371" },

   { 160, "",     "\\'86",        "\\dag{}",       "&#134;",   "\\206" },
   { 161, "",     "\\'B0",        "$\\circ$",      "&#176;",   "\\260" },
   { 162, "",     "\\'A2",        "cent",          "&#162;",   "\\242" },
   { 163, "",     "\\'A3",        "\\pounds{}",    "&#163;",   "\\243" },
   { 164, "",     "\\'A7",        "\\S{}",         "&sect;",   "\\167" },
   { 165, "",     "\\'95",        "$\\bullet$",    "&#149;",   "\\225" },
   { 166, "",     "\\'B6",        "\\P{}",         "&#182;",   "\\266" },
   { 167, "ss",   "\\'DF",        "{\\ss}",        "&szlig;",  "\\337" },

   { 168, "(R)",  "\\'AE",        "(R)",           "&#174;",   "\\256" },
   { 169, "(C)",  "\\'A9",        "\\copyright{}", "&#169;",   "\\251" },
   { 170, "(TM)", "\\'99",        "(TM)",          "&#153;",   "\\231" },
   { 171, "",     "\\'B4",        "\\'{ }",        "&#180;",   "\\264" },
   { 172, "",     "\\'A8",        "\\!{ }",        "&#168;",   "\\250" },
   { 173, "",     "{\\f2 \\'B9}", "$\\neq$",       "&#172;",   "\\254" },
   { 174, "AE",   "\\'C6",        "{\\AE}",        "&AElig;",  "\\306" },
   { 175, "O",    "\\'D8",        "{\\O}",         "&Oslash;", "\\330" },

   { 176, "",     "{\\f2 \\'A5}", "$\\infty$",     "&nbsp;",   ""      },
   { 177, "",     "\\'B1",        "$\\pm$",        "&#177;",   "\\261" },
   { 178, "",     "{\\f2 \\'A3}", "$\\leq$",       "",         ""      },
   { 179, "",     "{\\f2 \\'B3}", "$\\geq$",       "",         ""      },
   { 180, "",     "\\'A5",        "yen",           "&#165;",   "\\245" },
   { 181, "",     "\\'B5",        "$\\mu$",        "&#181;",   "\\365" },
   { 182, "",     "{\\f2 \\'B6}", "$\\partial$",   "",         ""      },
   { 183, "",     "{\\f2 S}",     "$\\Sigma$",     "",         ""      },

   { 184, "",     "{\\f2 P}",     "$\\Pi$",        "",         ""      },
   { 185, "",     "{\\f2 p}",     "$\\pi$",        "",         ""      },
   { 186, "",     "",             "",              "",         ""      },
   { 187, "",     "\\'AA",        "\\b{a}",        "&#170;",   "\\252" },
   { 188, "",     "\\'BA",        "\\b{o}",        "&#186;",   "\\272" },
   { 189, "",     "{\\f2 W}",     "$\\Omega$",     "",         ""      },
   { 190, "ae",   "\\'E6",        "{\\ae}",        "&aelig;",  "\\346" },
   { 191, "o",    "\\'F8",        "{\\o}",         "&oslash;", "\\370" },

   { 192, "?",    "\\'BF",        "?`",            "&#191;",   "\\277" },
   { 193, "!",    "\\'A1",        "!`",            "&#161;",   "\\241" },
   { 194, "",     "\\'AC",        "$\\neg$",       "&#172;",   "\\254" },
   { 195, "",     "{\\f2 \\'D6}", "$\\surd$",      "",         "?"     },
   { 196, "",     "\\'83",        "$f$",           "&#131;",   "\\203" },
   { 197, "",     "{\\f2 \\'BB}", "$\\approx$",    "",         "?"     },
   { 198, "",     "{\\f2 D}",     "$\\Delta$",     "",         "?"     },
   { 199, "<<",   "\\'AB",        "\"<",           "&#171;",   "\\253" },

   { 200, ">>",   "\\'BB",        "\">",           "&#187;",   "\\273" },
   { 201, "...",  "\\'85",        "\\ldots{}",     "&#133;",   "\\205" },
   { 202, "",     "\\~",          "~",             "&nbsp;",   ""      },
   { 203, "A",    "\\'C0",        "\\`{A}",        "&Agrave;", "\\300" },
   { 204, "A",    "\\'C3",        "\\~{A}",        "&Atilde;", "\\303" },
   { 205, "O",    "\\'D5",        "\\~{O}",        "&Otilde;", "\\325" },
   { 206, "OE",   "\\'8C",        "{\\OE}",        "&#140;",   "\\214" },
   { 207, "oe",   "\\'9C",        "{\\oe}",        "&#156;",   "\\234" },

   { 208, "--",   "\\'96",        "--",            "&#150;",   "\\226" },
   { 209, "---",  "\\'97",        "---",           "&#151;",   "\\227" },
   { 210, "",     "\\'93",        "``",            "&#147;",   "\\223" },
   { 211, "",     "\\'94",        "''",            "&#148;",   "\\224" },
   { 212, "",     "\\'91",        "`",             "&#145;",   "\\221" },
   { 213, "",     "\\'92",        "'",             "&#146;",   "\\222" },
   { 214, "",     "{\\f2 \\'B8}", "$\\div$",       "&#247;",   "\\367" },
   { 215, "",     "{\\f2 \\'E0}", "$\\Diamond$",   "",         "?" },

   { 216, "y",    "\\'FF",        "\\\"{y}",       "&yuml;",   "\\377" },
   { 217, "Y",    "\\'9F",        "\\\"{Y}",       "&Yuml;",   "?"     },
   { 218, "/",    "{\\f2 \\'A4}", "/",             "/",        "/"     },
   { 219, "",     "\\'A4",        "",              "&#164;",   "?"     },   /* gcs */
   { 220, "<",    "<",            "$<$",           "&lt;",     "<"     },
   { 221, ">",    ">",            "$>$",           "&gt;",     ">"     },
   { 222, "fi",   "fi",           "fi",            "fi",       "?"     },
   { 223, "fl",   "fl",           "fl",            "fl",       "?"     },

   { 224, "",     "\\'87",        "$\\ddagger$",   "&#135;",   "\\207" },
   { 225, "",     "\\'82",        "`",             "&#130;",   "\\202" },
   { 226, "",     "\\'84",        "``",            "&#132;",   "\\204" },
   { 227, "",     "\\'89",        "",              "&#137;",   "\\211" },
   { 228, "A",    "\\'C2",        "\\^{A}",        "&Acirc;",  "\\302" },
   { 229, "E",    "\\'CA",        "\\^{E}",        "&Ecirc;",  "\\312" },
   { 230, "A",    "\\'C1",        "\\'{A}",        "&Aacute;", "\\301" },
   { 231, "ss",   "\\'DF",        "{\\ss}",        "&szlig;",  "\\337" },

   { 232, "E",    "\\'CB",        "\\\"{E}",       "&Euml;",   "\\313" },
   { 233, "E",    "\\'C8",        "\\`{E}",        "&Egrave;", "\\310" },
   { 234, "I",    "\\'CD",        "\\'{I}",        "&Iacute;", "\\315" },
   { 235, "I",    "\\'CE",        "\\^{I}",        "&Icirc;",  "\\316" },
   { 236, "I",    "\\'CF",        "\\\"{I}",       "&Iuml;",   "\\317" },
   { 237, "I",    "\\'CC",        "\\`{I}",        "&Igrave;", "\\314" },
   { 238, "O",    "\\'D3",        "\\'{O}",        "&Oacute;", "\\323" },
   { 239, "O",    "\\'D4",        "\\^{O}",        "&Ocirc;",  "\\324" },

   { 240, "",     "",             "",              "",         ""      },   /* Apple-Logo */
   { 241, "O",    "\\'D2",        "\\`{O}",        "&Ograve;", "\\322" },
   { 242, "U",    "\\'DA",        "\\'{U}",        "&Uacute;", "\\332" },
   { 243, "U",    "\\'DB",        "\\^{U}",        "&Ucirc;",  "\\333" },
   { 244, "U",    "\\'D9",        "\\`{U}",        "&Ugrave;", "\\331" },
   { 245, "",     "\\'B9",        "$^1$",          "&#185;",   "\\271" },
   { 246, "",     "\\'F7",        "\\^{ }",        "^",        "^"     },
   { 247, "",     "~",            "\\~{ }",        "~",        "~"     },

   { 248, "",     "",             "\\={ }",        "",         "?"     },
   { 249, "",     "",             "\\u{ }",        "",         "?"     },
   { 250, "",     "\\'B7",        "\\.{ }",        "&#183;",   "\\267" },
   { 251, "",     "\\'B0",        "$\\circ$",      "&#176;",   "\\260" },
   { 252, "",     "\\'B8",        "\\c{ }",        "&#184;",   "\\270" },
   { 253, "",     "{\\f2 \\'B2}", "\\H{ }",        "",         ""      },
   { 254, "",     "",             "",              "",         ""      },
   { 255, "",     "",             "\\v{ }",        "",         ""      }
};





/*******************************************************************************
*
*     Recode 'Universal codepage' into ASCII codepage
*
******************************************|************************************/

typedef struct _uni2systab
{
   char  *uni;                            /* */
   char  *system;                         /* */
}  UNI2SYSTAB;


#define UNI2SYSTABSIZE   64


LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   { "(!\"a)", "\212" },
   { "(!\"e)", "\221" },
   { "(!\"i)", "\225" },
   { "(!\"o)", "\232" },
   { "(!\"u)", "\237" },
   { "(!\"y)", "\330" },
   { "(!\"s)", "\247" },
   { "(!\"A)", "\200" },
   { "(!\"E)", "\350" },
   { "(!\"I)", "\354" },
   { "(!\"O)", "\205" },
   { "(!\"U)", "\206" },
   { "(!\"Y)", "Y"    },                  /* 13 */

   { "(!'a)",  "\207" },
   { "(!'e)",  "\216" },
   { "(!'i)",  "\222" },
   { "(!'o)",  "\227" },
   { "(!'u)",  "\234" },
   { "(!'y)",  ""     },
   { "(!'A)",  "\347" },
   { "(!'E)",  "\203" },
   { "(!'I)",  "\352" },
   { "(!'O)",  "\356" },
   { "(!'U)",  "\362" },
   { "(!'Y)",  ""     },                  /* 12 */

   { "(!`a)",  "\210" },
   { "(!`e)",  "\217" },
   { "(!`i)",  "\223" },
   { "(!`o)",  "\230" },
   { "(!`u)",  "\235" },
   { "(!`A)",  "\313" },
   { "(!`E)",  "\351" },
   { "(!`I)",  "\355" },
   { "(!`O)",  "\361" },
   { "(!`U)",  "\364" },                  /* 10 */

   { "(!^a)",  "\211" },
   { "(!^e)",  "\220" },
   { "(!^i)",  "\224" },
   { "(!^o)",  "\231" },
   { "(!^u)",  "\236" },
   { "(!^A)",  "\345" },
   { "(!^E)",  "\346" },
   { "(!^I)",  "\353" },
   { "(!^O)",  "\357" },
   { "(!^U)",  "\363" },                  /* 10 */

   { "(!~a)",  "\213" },
   { "(!~n)",  "\226" },
   { "(!~o)",  "\233" },
   { "(!~A)",  "\314" },
   { "(!~N)",  "\204" },
   { "(!~O)",  "\315" },                  /*  6 */

   { "(!.a)",  "\214" },
   { "(!.A)",  "\201" },                  /*  2 */

   { "(!&ae)", "\276" },
   { "(!&AE)", "\256" },
   { "(!&oe)", "\317" },
   { "(!&OE)", "\316" },                  /*  4 */

   { "(!,c)",  "\215" },
   { "(!,C)",  "\202" },                  /*  2 */

   { "(!_a)",  "\273" },
   { "(!_o)",  "\274" },                  /*  2 */

   { "(!\\o)", "\277" },
   { "(!\\O)", "\257" },                  /*  2 */

   { "(!#S)",  "\244" },
};





/******************************************************************************
*
*  u_CODE_MAC[]:
*     Unicode named codepage for Apple Mac encoding (Mac OS Roman)
*
*  This character set is used for at least the following Mac OS localizations: 
*  U.S., British, Canadian French, French, Swiss French, German, Swiss German, 
*  Italian, Swiss Italian, Dutch, Swedish, Norwegian, Danish, Finnish, Spanish, 
*  Catalan, Portuguese, Brazilian, and the default International system.
*
*  Notes:
*     The following corporate zone Unicode character is used in this mapping:
*
*        0xF8FF   Apple logo
*
*     The graphic image associated with the Apple logo characteris not
*     authorized for use without permission of Apple, and unauthorized use might 
*     constitute trademark infringement. (Thus we map this characterto U_NIL here!)
*
******************************************|************************************/

static unsigned   u_CODE_MAC[] =          /* CODE_MAC */
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
   U_NIL,                                 /* 0x7F  --- UNDEFINED --- */

   U_LatinCapitalLetterAWithDiaeresis,    /* 0x80  U_LatinCapitalLetterAWithDiaeresis */
   U_LatinCapitalLetterAWithRingAbove,    /* 0x81  U_LatinCapitalLetterAWithRingAbove */
   U_LatinCapitalLetterCWithCedilla,      /* 0x82  U_LatinCapitalLetterCWithCedilla */
   U_LatinCapitalLetterEWithAcute,        /* 0x83  U_LatinCapitalLetterEWithAcute */
   U_LatinCapitalLetterNWithTilde,        /* 0x84  U_LatinCapitalLetterNWithTilde */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0x85  U_LatinCapitalLetterOWithDiaeresis */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0x86  U_LatinCapitalLetterUWithDiaeresis */
   U_LatinSmallLetterAWithAcute,          /* 0x87  U_LatinSmallLetterAWithAcute */
   U_LatinSmallLetterAWithGrave,          /* 0x88  U_LatinSmallLetterAWithGrave */
   U_LatinSmallLetterAWithCircumflex,     /* 0x89  U_LatinSmallLetterAWithCircumflex */
   U_LatinSmallLetterAWithDiaeresis,      /* 0x8a  U_LatinSmallLetterAWithDiaeresis */
   U_LatinSmallLetterAWithTilde,          /* 0x8b  U_LatinSmallLetterAWithTilde */
   U_LatinSmallLetterAWithRingAbove,      /* 0x8c  U_LatinSmallLetterAWithRingAbove */
   U_LatinSmallLetterCWithCedilla,        /* 0x8d  U_LatinSmallLetterCWithCedilla */
   U_LatinSmallLetterEWithAcute,          /* 0x8e  U_LatinSmallLetterEWithAcute */
   U_LatinSmallLetterEWithGrave,          /* 0x8f  U_LatinSmallLetterEWithGrave */
                                          
   U_LatinSmallLetterEWithCircumflex,     /* 0x90  U_LatinSmallLetterEWithCircumflex */
   U_LatinSmallLetterEWithDiaeresis,      /* 0x91  U_LatinSmallLetterEWithDiaeresis */
   U_LatinSmallLetterIWithAcute,          /* 0x92  U_LatinSmallLetterIWithAcute */
   U_LatinSmallLetterIWithGrave,          /* 0x93  U_LatinSmallLetterIWithGrave */
   U_LatinSmallLetterIWithCircumflex,     /* 0x94  U_LatinSmallLetterIWithCircumflex */
   U_LatinSmallLetterIWithDiaeresis,      /* 0x95  U_LatinSmallLetterIWithDiaeresis */
   U_LatinSmallLetterNWithTilde,          /* 0x96  U_LatinSmallLetterNWithTilde */
   U_LatinSmallLetterOWithAcute,          /* 0x97  U_LatinSmallLetterOWithAcute */
   U_LatinSmallLetterOWithGrave,          /* 0x98  U_LatinSmallLetterOWithGrave */
   U_LatinSmallLetterOWithCircumflex,     /* 0x99  U_LatinSmallLetterOWithCircumflex */
   U_LatinSmallLetterOWithDiaeresis,      /* 0x9a  U_LatinSmallLetterOWithDiaeresis */
   U_LatinSmallLetterOWithTilde,          /* 0x9b  U_LatinSmallLetterOWithTilde */
   U_LatinSmallLetterUWithAcute,          /* 0x9c  U_LatinSmallLetterUWithAcute */
   U_LatinSmallLetterUWithGrave,          /* 0x9d  U_LatinSmallLetterUWithGrave */
   U_LatinSmallLetterUWithCircumflex,     /* 0x9e  U_LatinSmallLetterUWithCircumflex */
   U_LatinSmallLetterUWithDiaeresis,      /* 0x9f  U_LatinSmallLetterUWithDiaeresis */
                                          
   U_Dagger,                              /* 0xa0  U_Dagger */
   U_DegreeSign,                          /* 0xa1  U_DegreeSign */
   U_CentSign,                            /* 0xa2  U_CentSign */
   U_PoundSign,                           /* 0xa3  U_PoundSign */
   U_SectionSign,                         /* 0xa4  U_SectionSign */
   U_Bullet,                              /* 0xa5  U_Bullet */
   U_ParagraphSign,                       /* 0xa6  U_ParagraphSign (aka: pilcrow sign) */
   U_LatinSmallLetterSharpS,              /* 0xa7  U_LatinSmallLetterSharpS */
   U_RegisteredSign,                      /* 0xa8  U_RegisteredSign */
   U_CopyrightSign,                       /* 0xa9  U_CopyrightSign */
   U_TradeMarkSign,                       /* 0xaa  U_TradeMarkSign */
   U_AcuteAccent,                         /* 0xab  U_AcuteAccent */
   U_Diaeresis,                           /* 0xac  U_Diaeresis */
   U_NotEqualTo,                          /* 0xad  U_NotEqualTo */
   U_LatinCapitalLigatureAE,              /* 0xae  U_LatinCapitalLigatureAE */
   U_LatinCapitalLetterOSlash,            /* 0xaf  U_LatinCapitalLetterOSlash */
   
   U_Infinity,                            /* 0xb0  U_Infinity */
   U_PlusMinusSign,                       /* 0xb1  U_PlusMinusSign */
   U_LessThanOrEqualTo,                   /* 0xb2  U_LessThanOrEqualTo */
   U_GreaterThanOrEqualTo,                /* 0xb3  U_GreaterThanOrEqualTo */
   U_YenSign,                             /* 0xb4  U_YenSign */
   U_MicroSign,                           /* 0xb5  U_MicroSign */
   U_PartialDifferential,                 /* 0xb6  U_PartialDifferential */
   U_NArySummation,                       /* 0xb7  U_NArySummation */
   U_NAryProduct,                         /* 0xb8  U_NAryProduct */
   U_GreekSmallLetterPi,                  /* 0xb9  U_GreekSmallLetterPi */
   U_Integral,                            /* 0xba  U_Integral */
   U_FeminineOrdinalIndicator,            /* 0xbb  U_FeminineOrdinalIndicator */
   U_MasculineOrdinalIndicator,           /* 0xbc  U_MasculineOrdinalIndicator */
   U_GreekCapitalLetterOmega,             /* 0xbd  U_GreekCapitalLetterOmega */
   U_LatinSmallLigatureAE,                /* 0xbe  U_LatinSmallLigatureAE */
   U_LatinSmallLetterOSlash,              /* 0xbf  U_LatinSmallLetterOSlash */
                                          
   U_InvertedQuestionMark,                /* 0xc0  U_InvertedQuestionMark */
   U_InvertedExclamationMark,             /* 0xc1  U_InvertedExclamationMark */
   U_NotSign,                             /* 0xc2  U_NotSign */
   U_SquareRoot,                          /* 0xc3  U_SquareRoot */
   U_LatinSmallLetterScriptF,             /* 0xc4  U_LatinSmallLetterScriptF */
   U_AlmostEqualTo,                       /* 0xc5  U_AlmostEqualTo */
   U_Increment,                           /* 0xc6  U_Increment */
   U_LeftPointingGuillemet,               /* 0xc7  U_LeftPointingGuillemet */
   U_RightPointingGuillemet,              /* 0xc8  U_RightPointingGuillemet */
   U_HorizontalEllipsis,                  /* 0xc9  U_HorizontalEllipsis */
   U_NB_SP,                               /* 0xca  U_NB_SP */
   U_LatinCapitalLetterAWithGrave,        /* 0xcb  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterAWithTilde,        /* 0xcc  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterOWithTilde,        /* 0xcd  U_LatinCapitalLetterOWithTilde */
   U_LatinCapitalLigatureOE,              /* 0xce  U_LatinCapitalLigatureOE */
   U_LatinSmallLigatureOE,                /* 0xcf  U_LatinSmallLigatureOE */
                                          
   U_EnDash,                              /* 0xd0  U_EnDash */
   U_EmDash,                              /* 0xd1  U_EmDash */
   U_LeftDoubleQuotationMark,             /* 0xd2  U_LeftDoubleQuotationMark */
   U_RightDoubleQuotationMark,            /* 0xd3  U_RightDoubleQuotationMark */
   U_LeftSingleQuotationMark,             /* 0xd4  U_LeftSingleQuotationMark */
   U_RightSingleQuotationMark,            /* 0xd5  U_RightSingleQuotationMark */
   U_DivisionSign,                        /* 0xd6  U_DivisionSign */
   U_Lozenge,                             /* 0xd7  U_Lozenge */
   U_LatinSmallLetterYWithDiaeresis,      /* 0xd8  U_LatinSmallLetterYWithDiaeresis */
   U_LatinCapitalLetterYWithDiaeresis,    /* 0xd9  U_LatinCapitalLetterYWithDiaeresis */
   U_FractionSlash,                       /* 0xda  U_FractionSlash */
   U_EuroSign,                            /* 0xdb  U_EuroSign */
   U_LeftPointingSingleGuillemet,         /* 0xdc  U_LeftPointingSingleGuillemet */
   U_RightPointingSingleGuillemet,        /* 0xdd  U_RightPointingSingleGuillemet */
   U_LatinSmallLigatureFI,                /* 0xde  U_LatinSmallLigatureFI */
   U_LatinSmallLigatureFL,                /* 0xdf  U_LatinSmallLigatureFL */
                                          
   U_DoubleDagger,                        /* 0xe0  U_DoubleDagger */
   U_MiddleDot,                           /* 0xe1  U_MiddleDot */
   U_SingleLow9QuotationMark,             /* 0xe2  U_SingleLow9QuotationMark */
   U_DoubleLow9QuotationMark,             /* 0xe3  U_DoubleLow9QuotationMark */
   U_PerMilleSign,                        /* 0xe4  U_PerMilleSign */
   U_LatinCapitalLetterAWithCircumflex,   /* 0xe5  U_LatinCapitalLetterAWithCircumflex */
   U_LatinCapitalLetterEWithCircumflex,   /* 0xe6  U_LatinCapitalLetterEWithCircumflex */
   U_LatinCapitalLetterAWithAcute,        /* 0xe7  U_LatinCapitalLetterAWithAcute */
   U_LatinCapitalLetterEWithDiaeresis,    /* 0xe8  U_LatinCapitalLetterEWithDiaeresis */
   U_LatinCapitalLetterEWithGrave,        /* 0xe9  U_LatinCapitalLetterEWithGrave */
   U_LatinCapitalLetterIWithAcute,        /* 0xea  U_LatinCapitalLetterIWithAcute */
   U_LatinCapitalLetterIWithCircumflex,   /* 0xeb  U_LatinCapitalLetterIWithCircumflex */
   U_LatinCapitalLetterIWithDiaeresis,    /* 0xec  U_LatinCapitalLetterIWithDiaeresis */
   U_LatinCapitalLetterIWithGrave,        /* 0xed  U_LatinCapitalLetterIWithGrave */
   U_LatinCapitalLetterOWithAcute,        /* 0xee  U_LatinCapitalLetterOWithAcute */
   U_LatinCapitalLetterOWithCircumflex,   /* 0xef  U_LatinCapitalLetterOWithCircumflex */
                                          
   U_NIL,                                 /* 0xf0  -- (Apple logo: 0xF8FF) -- */
   U_LatinCapitalLetterOWithGrave,        /* 0xf1  U_LatinCapitalLetterOWithGrave */
   U_LatinCapitalLetterUWithAcute,        /* 0xf2  U_LatinCapitalLetterUWithAcute */
   U_LatinCapitalLetterUWithCircumflex,   /* 0xf3  U_LatinCapitalLetterUWithCircumflex */
   U_LatinCapitalLetterUWithGrave,        /* 0xf4  U_LatinCapitalLetterUWithGrave */
   U_LatinSmallLetterDotlessI,            /* 0xf5  U_LatinSmallLetterDotlessI */
   U_ModifierLetterCircumflexAccent,      /* 0xf6  U_ModifierLetterCircumflexAccent */
   U_SmallTilde,                          /* 0xf7  U_SmallTilde */
   U_Macron,                              /* 0xf8  U_Macron */
   U_Breve,                               /* 0xf9  U_Breve */
   U_DotAbove,                            /* 0xfa  U_DotAbove */
   U_RingAbove,                           /* 0xfb  U_RingAbove */
   U_Cedilla,                             /* 0xfc  U_Cedilla */
   U_DoubleAcuteAccent,                   /* 0xfd  U_DoubleAcuteAccent */
   U_Ogonek,                              /* 0xfe  U_Ogonek */
   U_Caron                                /* 0xff  U_Caron */
};


/* +++ EOF +++ */
