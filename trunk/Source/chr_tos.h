/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_tos.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer Atari TOS
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
*                 - try to assign the three unnamed chars in uCODE_TOS[] -> U_NIL
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 10: header updated, file reformatted and tidied up (TAB-free)
*    fd  Feb 12: - all octal chars converted into decimal values
*                - u_CODE_TOS[] introduced
*
******************************************|************************************/

#ifndef ID_CHARSET_H
#define ID_CHARSET_H
const char  *id_charset_h = "@(#) chr_tos.h   $date$";
#endif

#ifndef THIS_CHARSET
#define THIS_CHARSET  "TOS"
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


LOCAL const ISO2SYS iso2sys_item[128] =
{
   {128,   0},                            /* null *//* !!!! */
   {129,   0},                            /* null *//* !!!! */
   {130,   0},                            /* '' (9u) *//* !!!! */
   {131, 159},                            /* #f */
   {132,   0},                            /* "" (99u) *//* !!!! */
   {133,   0},                            /* !.. *//* !!!! */
   {134, 187},                            /* #dag */
   {135,   0},                            /* 2x#dag *//* !!!! */
   {136, 222},                            /* #circ */
   {137,   0},                            /* #promill */
   {138, 'S'},                            /* vS *//* !!!! */
   {139, '<'},                            /* < *//* !!!! */
   {140, 181},                            /* &OE */
   {141,   0},                            /* null */
   {142,   0},                            /* null */
   {143,   0},                            /* null */
   {144,   0},                            /* null */
   {145,   0},                            /* '' (6o) *//* !!!! */
   {146,   0},                            /* '' (9o) *//* !!!! */
   {147,   0},                            /* "" (66o) *//* !!!! */
   {148,   0},                            /* "" (99u) *//* !!!! */
   {149, 249},                            /* #bullet */
   {150, '-'},                            /* -- *//* !!!! */
   {151, '-'},                            /* --- *//* !!!! */
   {152, '~'},                            /* !~ *//* !!!! */
   {153, 191},                            /* #tm */
   {154, 's'},                            /* vs */
   {155, '>'},                            /* > */
   {156, 180},                            /* &oe */
   {157,   0},                            /* null */
   {158,   0},                            /* null */
   {159, 'Y'},                            /* "Y *//* !!!! */
   {150,   0},                            /* null */
   {161, 173},                            /* #! */
   {162, 155},                            /* #cent */
   {163, 156},                            /* #pound */
   {164,   0},                            /* general currency */
   {165, 157},                            /* #yen */
   {166, '|'},                            /* broken dash *//* !!!! */
   {167, 221},                            /* #sect */
   {168, 185},                            /* #" */
   {169, 189},                            /* #copy */
   {170, 166},                            /* _a */
   {171, 174},                            /* #< */
   {172, 170},                            /* #neg */
   {173,   0},                            /* strich *//* !!!! */
   {174, 190},                            /* #reg */
   {175,   0},                            /* #macron *//* !!!! */
   {176, 248},                            /* #degree */
   {177, 241},                            /* #pm */
   {178, 253},                            /* #^2 */
   {179, 254},                            /* #^3 */
   {180, 186},                            /* #' */
   {181, 230},                            /* #mu */
   {182, 188},                            /* #p */
   {183, 250},                            /* #cdot */
   {184,   0},                            /* cedille *//* !!!! */
   {185,   0},                            /* #^1 *//* !!!! */
   {186, 167},                            /* _o */
   {187, 175},                            /* #> */
   {188, 172},                            /* #1/4 */
   {189, 171},                            /* #1/2 */
   {190,   0},                            /* #3/4 *//* !!!! */
   {191, 168},                            /* #? */
   {192, 182},                            /* `A */
   {193, 'A'},                            /* 'A *//* !!!! */
   {194, 'A'},                            /* ^A *//* !!!! */
   {195, 183},                            /* ~A */
   {196, 142},                            /* "A */
   {197, 143},                            /* .A */
   {198, 146},                            /* &AE */
   {199, 128},                            /* ,C */
   {200, 'E'},                            /* `E *//* !!!! */
   {201, 'E'},                            /* 'E *//* !!!! */
   {202, 'E'},                            /* ^E *//* !!!! */
   {203, 'E'},                            /* "E *//* !!!! */
   {204, 'I'},                            /* `I *//* !!!! */
   {205, 'I'},                            /* 'I *//* !!!! */
   {206, 'I'},                            /* ^I *//* !!!! */
   {207, 'I'},                            /* "I *//* !!!! */
   {208,   0},                            /* -D */
   {209, 165},                            /* ~N */
   {210, 'O'},                            /* `O *//* !!!! */
   {211, 'O'},                            /* 'O *//* !!!! */
   {212, 'O'},                            /* ^O *//* !!!! */
   {213, 184},                            /* ~O */
   {214, 153},                            /* "O */
   {215, 'x'},                            /* #times *//* !!!! */
   {216, 178},                            /* /O */
   {217, 'U'},                            /* `U *//* !!!! */
   {218, 'U'},                            /* 'U *//* !!!! */
   {219, 'U'},                            /* ^U *//* !!!! */
   {220, 154},                            /* "U */
   {221, 'Y'},                            /* 'Y *//* !!!! */
   {222,   0},                            /* |b */
   {223, 158},                            /* "s (sz) *//* r6pl12: vorher \341 (beta) */
   {224, 133},                            /* `a */
   {225, 160},                            /* 'a */
   {226, 131},                            /* ^a */
   {227, 176},                            /* ~a */
   {228, 132},                            /* "a */
   {229, 134},                            /* .a */
   {230, 145},                            /* &ae */
   {231, 135},                            /* ,c */
   {232, 138},                            /* `e */
   {233, 130},                            /* 'e */
   {234, 136},                            /* ^e */
   {235, 137},                            /* "e */
   {236, 141},                            /* `i */
   {237, 161},                            /* 'i */
   {238, 140},                            /* ^i */
   {239, 139},                            /* "i */
   {240,   0},                            /* o|'' *//* !!!! */
   {241, 164},                            /* ~n */
   {242, 149},                            /* `o */
   {243, 162},                            /* 'o */
   {244, 147},                            /* ^o */
   {245, 177},                            /* ~o */
   {246, 148},                            /* "o */
   {247, 222},                            /* #div */
   {248, 179},                            /* /o */
   {249, 151},                            /* `u */
   {250, 163},                            /* 'u */
   {251, 150},                            /* ^u */
   {252, 129},                            /* "u */
   {253, 'y'},                            /* 'y *//* !!!! */
   {254,   0},                            /* |B *//* !!!! */
   {255, 152}                             /* "y */
};





/*******************************************************************************
*
*     Recode System codepage into various codepages
*
******************************************|************************************/

typedef struct _chartable
{
   unsigned   charsystem;                 /* */
   char      *ascii;                      /* */
   char      *ansi;                       /* */
   char      *tex;                        /* */
   char      *html;                       /* */
   char      *ps;                         /* */
}  CHARTABLE;





LOCAL /* const */ CHARTABLE   chrtab[128] =
{
/*          ASCII Ansi              TeX            HTML        PS      */
/* ------------------------------------------------------------------- */
   {128, "C",    "\\'C7",          "\\c{C}",      "&Ccedil;", "\\307"},
#ifdef __TOS__                            /* Changed in r6pl15 [NHz] */
   {129, "ue",   "\\'FC",          "{\\\"u}",     "&uuml;",   "\\374"},
#else
   {129, "ue",   "\\'FC",          "{\\\"u}",     "&uuml;",   "\\371"},
#endif
   {130, "e",    "\\'E9",          "\\'{e}",      "&eacute;", "\\351"},
   {131, "a",    "\\'E2",          "\\^{a}",      "&acirc;",  "\\342"},
   {132, "ae",   "\\'E4",          "{\\\"a}",     "&auml;",   "\\344"},
   {133, "a",    "\\'E0",          "\\`{a}",      "&agrave;", "\\340"},
   {134, "a",    "\\'E5",          "{\\aa}",      "&aring;",  "\\345"},
   {135, "c",    "\\'E7",          "\\c{c}",      "&ccedil;", "\\347"},
   
   {136, "e",    "\\'EA",          "\\^{e}",      "&ecirc;",  "\\352"},
   {137, "e",    "\\'EB",          "\\\"{e}",     "&euml;",   "\\353"},
   {138, "e",    "\\'E8",          "\\`{e}",      "&egrave;", "\\350"},
   {139, "i",    "\\'EF",          "\\\"{i}",     "&iuml;",   "\\357"},
   {140, "i",    "\\'EE",          "\\^{i}",      "&icirc;",  "\\356"},
   {141, "i",    "\\'EC",          "\\`{i}",      "&igrave;", "\\354"},
   {142, "Ae",   "\\'C4",          "{\\\"A}",     "&Auml;",   "\\304"},
   {143, "A",    "\\'C5",          "{\\AA}",      "&Aring;",  "\\305"},
   
   {144, "E",    "\\'C9",          "\\'{E}",      "&Eacute;", "\\311"},
   {145, "ae",   "\\'E6",          "{\\ae}",      "&aelig;",  "\\346"},
   {146, "AE",   "\\'C6",          "{\\AE}",      "&AElig;",  "\\306"},
   {147, "o",    "\\'F4",          "\\^{o}",      "&ocirc;",  "\\364"},
   {148, "oe",   "\\'F6",          "{\\\"o}",     "&ouml;",   "\\366"},
   {149, "o",    "\\'F2",          "\\`{o}",      "&ograve;", "\\362"},
   {150, "u",    "\\'FB",          "\\^{u}",      "&ucirc;",  "\\373"},
   {151, "u",    "\\'F9",          "\\`{u}",      "&ugrave;", "\\371"},
   
   {152, "y",    "\\'FF",          "\\\"{y}",     "&yuml;",   "\\377"},
   {153, "Oe",   "\\'D6",          "{\\\"O}",     "&Ouml;",   "\\326"},
   {154, "Ue",   "\\'DC",          "{\\\"U}",     "&Uuml;",   "\\334"},
   {155, "",     "\\'A2",          "cent",        "&#162;",   "\\242"},
   {156, "",     "\\'A3",          "\\pounds{}",  "&#163;",   "\\243"},
   {157, "",     "\\'A5",          "yen",         "&#165;",   "\\245"},
   {158, "ss",   "\\'DF",          "{\\ss}",      "&szlig;",  "\\337"},
   {159, "",     "\\'83",          "$f$",         "&#166;",   "\\203"},
   
   {160, "a",    "\\'E1",          "\\'{a}",      "&aacute;", "\\341"},
   {161, "i",    "\\'ED",          "\\'{i}",      "&iacute;", "\\355"},
   {162, "o",    "\\'F3",          "\\'{o}",      "&oacute;", "\\363"},
   {163, "u",    "\\'FA",          "\\'{u}",      "&uacute;", "\\372"},
   {164, "n",    "\\'F1",          "\\~{n}",      "&ntilde;", "\\361"},
   {165, "N",    "\\'D1",          "\\~{N}",      "&Ntilde;", "\\321"},
   {166, "",     "\\'AA",          "\\b{a}",      "&#170;",   "\\252"},
   {167, "",     "\\'BA",          "\\b{o}",      "&#186;",   "\\272"},
   
   {168, "",     "\\'BF",          "?`",          "&#191;",   "\\277"},
   {169, "",     "",               "",            "",         ""},
   {170, "",     "\\'AC",          "$\\neg$",     "&#172;",   "\\254"},
   {171, "",     "\\'BD",          "$\\frac{1}{2}$","&#189;", "\\275"},
   {172, "",     "\\'BC",          "$\\frac{1}{4}$","&#188;", "\\274"},
   {173, "!",    "\\'A1",          "!`",          "&#161;",   "\\241"},
   {174, "",     "\\'AB",          "\"<",         "&#171;",   "\\253"},
   {175, "",     "\\'BB",          "\">",         "&#187;",   "\\273"},
   
   {176, "a",    "\\'E3",          "\\~{a}",      "&atilde;", "\\343"},
   {177, "o",    "\\'F5",          "\\~{o}",      "&otilde;", "\\365"},
   {178, "O",    "\\'D8",          "{\\O}",       "&Oslash;", "\\330"},
   {179, "o",    "\\'F8",          "{\\o}",       "&oslash;", "\\370"},
   {180, "oe",   "\\'9C",          "{\\oe}",      "&#156;",   "\\234"},
   {181, "OE",   "\\'8C",          "{\\OE}",      "&#140;",   "\\214"},
   {182, "A",    "\\'C0",          "\\`{A}",      "&Agrave;", "\\300"},
   {183, "A",    "\\'C3",          "\\~{A}",      "&Atilde;", "\\303"},
   
   {184, "O",    "\\'D5",          "\\~{O}",      "&Otilde;", "\\325"},
   {185, "",     "\\'A8",          "\\!{}",       "&#168;",   "\\250"},
   {186, "`",    "\\'B4",          "\\`{}",       "&#180;",   "\\264"},
   {187, "",     "\\'86",          "\\dag{}",     "&#134;",   "\\206"},
   {188, "",     "\\'B6",          "\\P{}",       "&#182;",   "\\266"},
   {189, "(c)",  "\\'A9",          "\\copyright{}","&#169;",  "\\251"},
   {190, "(R)",  "\\'AE",          "(R)",         "&#174;",   "\\256"},
   {191, "(TM)", "\\'99",         "(TM)",        "&#153;",   "\\231"},
   
   {192, "ij",   "ij",             "ij",          "ij",       "ij"},
   {193, "IJ",   "IJ",             "IJ",          "IJ",       "ij"},
   {194, "",     "",               "",            "",         ""},
   {195, "",     "",               "",            "",         ""},
   {196, "",     "-",              "",            "",         ""},
   {197, "",     "",               "",            "",         ""},
   {198, "",     "",               "",            "",         ""},
   {199, "",     "",               "",            "",         ""},
   
   {200, "",     "",               "",            "",         ""},
   {201, "",     "",               "",            "",         ""},
   {202, "",     "",               "",            "",         ""},
   {203, "",     "",               "",            "",         ""},
   {204, "",     "",               "",            "",         ""},
   {205, "",     "",               "",            "",         ""},
   {206, "",     "",               "",            "",         ""},
   {207, "",     "",               "",            "",         ""},
   
   {208, "",     "",               "",            "",         ""},
   {209, "",     "",               "",            "",         ""},
   {210, "",     "",               "",            "",         ""},
   {211, "",     "",               "",            "",         ""},
   {212, "",     "",               "",            "",         ""},
   {213, "",     "",               "",            "",         ""},
   {214, "",     "",               "",            "",         ""},
   {215, "",     "",               "",            "",         ""},
   
   {216, "",     "",               "",            "",         ""},
   {217, "",     "",               "",            "",         ""},
   {218, "",     "+",              "",            "",         ""},
   {219, "",     "",               "",            "",         ""},
   {220, "",     "",               "",            "",         ""},
   {221, "",     "\\'A7",          "\\S{}",       "&sect;",   "\\167"},
   {222, "",     "\\'F7",          "$\\wedge$",   "&#136;",   "\\367"},
   {223, "",     "{\\f2 \\'A5}",   "$\\infty$",   "",         ""},
   
   {224, "",     "{\\f2 a}",       "$\\alpha$",   "",         ""},
   {225, "ss",   "\\'DF",          "{\\ss}",      "&szlig;",  "\\337"},
   {226, "",     "{\\f2 G}",       "$\\Gamma$",   "",         ""},
   {227, "",     "{\\f2 p}",       "$\\pi$",      "",         ""},
   {228, "",     "{\\f2 S}",       "$\\Sigma$",   "",         ""},
   {229, "",     "{\\f2 s}",       "$\\sigma$",   "",         ""},
   {230, "",     "\\'B5",          "$\\mu$",      "&#181;",   "\\265"},
   {231, "",     "{\\f2 t}",       "$\\tau$",     "",         ""},
   
   {232, "",     "{\\f2 F}",       "$\\Phi$",     "",         ""},
   {233, "",     "{\\f2 f}",       "$\\phi$",     "",         ""},
   {234, "",     "{\\f2 W}",       "$\\Omega$",   "",         ""},
   {235, "",     "{\\f2 d}",       "$\\delta$",   "",         ""},
   {236, "",     "{\\f2 \\'A5}",   "$\\infty$",   "",         ""},
   {237, "",     "",               "",            "",         ""},
   {238, "",     "{\\f2 e}",       "$\\epsilon$", "",         ""},
   {239, "",     "{\\f2 h}",       "$\\eta$",     "",         ""},
   
   {240, "",     "{\\f2 \\'BA}",   "$\\equiv$",   "",         ""},
   {241, "",     "\\'B1",          "$\\pm$",      "&#177;",   "\\261"},
   {242, "",     "{\\f2 \\'B3}",   "$\\geq$",     "",         ""},
   {243, "",     "{\\f2 \\'A3}",   "$\\leq$",     "",         ""},
   {244, "",     "",               "",            "",         ""},
   {245, "",     "",               "",            "",         ""},
   {246, "",     "{\\f2 \\'B8}",   "$\\div$",     "&#247;",   ""},
   {247, "",     "{\\f2 \\'BB}",   "$\\approx$",  "",         ""},
   
   {248, "",     "\\'B0",          "$\\circ$",    "&#176;",   "\\260"},
   {249, "",     "\\'95",          "$\\bullet$",  "&#149;",   "\\225"},
   {250, "",     "\\'B7",          "$\\bullet$",  "&#183;",   "\\267"},
   {251, "",     "{\\f2 \\'D6}",   "$\\surd$",    "",         ""},
   {252, "",     "",               "$^n$",        "",         ""},
   {253, "",     "\\'B2",          "$^2$",        "&#178;",   "\\262"},
   {254, "",     "\\'B3",          "$^3$",        "&#179;",   "\\263"},
   {255, "",     "\\'AF",          "",            "&#175;",   "\\257"}/* #macron*/
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


#define UNI2SYSTABSIZE  64

LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   {"(!\"a)",  "\204"},
   {"(!\"e)",  "\211"},
   {"(!\"i)",  "\213"},
   {"(!\"o)",  "\224"},
   {"(!\"u)",  "\201"},
   {"(!\"y)",  "\230"},
   {"(!\"s)",  "\236"},
   {"(!\"A)",  "\216"},
   {"(!\"E)",  "E"   },
   {"(!\"I)",  "I"   },
   {"(!\"O)",  "\231"},
   {"(!\"U)",  "\232"},
   {"(!\"Y)",  "Y"   },                   /* 13 */
   
   {"(!'a)",   "\240"},
   {"(!'e)",   "\202"},
   {"(!'i)",   "\241"},
   {"(!'o)",   "\242"},
   {"(!'u)",   "\243"},
   {"(!'y)",   "y"   },
   {"(!'A)",   "A"   },
   {"(!'E)",   "\220"},
   {"(!'I)",   "I"   },
   {"(!'O)",   "O"   },
   {"(!'U)",   "U"   },
   {"(!'Y)",   "Y"   },                   /* 12 */
   
   {"(!`a)",   "\205"},
   {"(!`e)",   "\212"},
   {"(!`i)",   "\215"},
   {"(!`o)",   "\225"},
   {"(!`u)",   "\227"},
   {"(!`A)",   "A"   },
   {"(!`E)",   "E"   },
   {"(!`I)",   "I"   },
   {"(!`O)",   "O"   },
   {"(!`U)",   "U"   },                   /* 10 */
   
   {"(!^a)",   "\203"},
   {"(!^e)",   "\210"},
   {"(!^i)",   "\214"},
   {"(!^o)",   "\223"},
   {"(!^u)",   "\226"},
   {"(!^A)",   "A"   },
   {"(!^E)",   "E"   },
   {"(!^I)",   "I"   },
   {"(!^O)",   "O"   },
   {"(!^U)",   "U"   },                   /* 10 */
   
   {"(!~a)",   "a"   },
   {"(!~n)",   "\244"},
   {"(!~o)",   "o"   },
   {"(!~A)",   "A"   },
   {"(!~N)",   "\245"},
   {"(!~O)",   "O"   },                   /*  6 */
   
   {"(!.a)",   "\206"},
   {"(!.A)",   "\217"},                   /*  2 */
   
   {"(!&ae)",  "\221"},
   {"(!&AE)",  "\222"},
   {"(!&oe)",  "oe"  },
   {"(!&OE)",  "OE"  },                   /*  4 */
   
   {"(!,c)",   "\207"},
   {"(!,C)",   "\200"},                   /*  2 */
   
   {"(!_a)",   "\246"},
   {"(!_o)",   "\247"},                   /*  2 */
   
   {"(!\\o)",  "o"   },
   {"(!\\O)",  "O"   },                   /*  2 */
   
   {"(!#S)",   "\335"},
};





/******************************************************************************
*
*  u_CODE_TOS[]:
*     Unicode named codepage for TOS encoding
*
******************************************|************************************/

static unsigned   u_CODE_TOS[] =          /* CODE_TOS */
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

   U_LatinCapitalLetterCWithCedilla,      /* 0x80  U_LatinCapitalLetterCWithCedilla */
   U_LatinSmallLetterUWithDiaeresis,      /* 0x81  U_LatinSmallLetterUWithDiaeresis */
   U_LatinSmallLetterEWithAcute,          /* 0x82  U_LatinSmallLetterEWithAcute */
   U_LatinSmallLetterAWithCircumflex,     /* 0x83  U_LatinSmallLetterAWithCircumflex */
   U_LatinSmallLetterAWithDiaeresis,      /* 0x84  U_LatinSmallLetterAWithDiaeresis */
   U_LatinSmallLetterAWithGrave,          /* 0x85  U_LatinSmallLetterAWithGrave */
   U_LatinSmallLetterAWithRingAbove,      /* 0x86  U_LatinSmallLetterAWithRingAbove */
   U_LatinSmallLetterCWithCedilla,        /* 0x87  U_LatinSmallLetterCWithCedilla */
   U_LatinSmallLetterEWithCircumflex,     /* 0x88  U_LatinSmallLetterEWithCircumflex */
   U_LatinSmallLetterEWithDiaeresis,      /* 0x89  U_LatinSmallLetterEWithDiaeresis */
   U_LatinSmallLetterEWithGrave,          /* 0x8a  U_LatinSmallLetterEWithGrave */
   U_LatinSmallLetterIWithDiaeresis,      /* 0x8b  U_LatinSmallLetterIWithDiaeresis */
   U_LatinSmallLetterIWithCircumflex,     /* 0x8c  U_LatinSmallLetterIWithCircumflex */
   U_LatinSmallLetterIWithGrave,          /* 0x8d  U_LatinSmallLetterIWithGrave */
   U_LatinCapitalLetterAWithDiaeresis,    /* 0x8e  U_LatinCapitalLetterAWithDiaeresis */
   U_LatinCapitalLetterAWithRingAbove,    /* 0x8f  U_LatinCapitalLetterAWithRingAbove */
                                          
   U_LatinCapitalLetterEWithAcute,        /* 0x90  U_LatinCapitalLetterEWithAcute */
   U_LatinSmallLigatureAE,                /* 0x91  U_LatinSmallLigatureAE */
   U_LatinCapitalLigatureAE,              /* 0x92  U_LatinCapitalLigatureAE */
   U_LatinSmallLetterOWithCircumflex,     /* 0x93  U_LatinSmallLetterOWithCircumflex */
   U_LatinSmallLetterOWithDiaeresis,      /* 0x94  U_LatinSmallLetterOWithDiaeresis */
   U_LatinSmallLetterOWithGrave,          /* 0x95  U_LatinSmallLetterOWithGrave */
   U_LatinSmallLetterUWithCircumflex,     /* 0x96  U_LatinSmallLetterUWithCircumflex */
   U_LatinSmallLetterUWithGrave,          /* 0x97  U_LatinSmallLetterUWithGrave */
   U_LatinSmallLetterYWithDiaeresis,      /* 0x98  U_LatinSmallLetterYWithDiaeresis */
   U_LatinCapitalLetterOWithDiaeresis,    /* 0x99  U_LatinCapitalLetterOWithDiaeresis */
   U_LatinCapitalLetterUWithDiaeresis,    /* 0x9a  U_LatinCapitalLetterUWithDiaeresis */
   U_CentSign,                            /* 0x9b  U_CentSign */
   U_PoundSign,                           /* 0x9c  U_PoundSign */
   U_YenSign,                             /* 0x9d  U_YenSign */
   U_LatinSmallLetterSharpS,              /* 0x9e  U_LatinSmallLetterSharpS */
   U_LatinSmallLetterScriptF,             /* 0x9f  U_LatinSmallLetterScriptF */
                                          
   U_LatinSmallLetterAWithAcute,          /* 0xa0  U_LatinSmallLetterAWithAcute */
   U_LatinSmallLetterIWithAcute,          /* 0xa1  U_LatinSmallLetterIWithAcute */
   U_LatinSmallLetterOWithAcute,          /* 0xa2  U_LatinSmallLetterOWithAcute */
   U_LatinSmallLetterUWithAcute,          /* 0xa3  U_LatinSmallLetterUWithAcute */
   U_LatinSmallLetterNWithTilde,          /* 0xa4  U_LatinSmallLetterNWithTilde */
   U_LatinCapitalLetterNWithTilde,        /* 0xa5  U_LatinCapitalLetterNWithTilde */
   U_FeminineOrdinalIndicator,            /* 0xa6  U_FeminineOrdinalIndicator */
   U_MasculineOrdinalIndicator,           /* 0xa7  U_MasculineOrdinalIndicator */
   U_InvertedQuestionMark,                /* 0xa8  U_InvertedQuestionMark */
   U_ReversedNotSign,                     /* 0xa9  U_ReversedNotSign */
   U_NotSign,                             /* 0xaa  U_NotSign */
   U_VulgarFractionOneHalf,               /* 0xab  U_VulgarFractionOneHalf */
   U_VulgarFractionOneQuarter,            /* 0xac  U_VulgarFractionOneQuarter */
   U_InvertedExclamationMark,             /* 0xad  U_InvertedExclamationMark */
   U_LeftPointingGuillemet,               /* 0xae  U_LeftPointingGuillemet */
   U_RightPointingGuillemet,              /* 0xaf  U_RightPointingGuillemet */
                                          
   U_LatinSmallLetterAWithTilde,          /* 0xb0  U_LatinSmallLetterAWithTilde */
   U_LatinSmallLetterOWithTilde,          /* 0xb1  U_LatinSmallLetterOWithTilde */
   U_LatinCapitalLetterOSlash,            /* 0xb2  U_LatinCapitalLetterOSlash */
   U_LatinSmallLetterOSlash,              /* 0xb3  U_LatinSmallLetterOSlash */
   U_LatinSmallLigatureOE,                /* 0xb4  U_LatinSmallLigatureOE */
   U_LatinCapitalLigatureOE,              /* 0xb5  U_LatinCapitalLigatureOE */
   U_LatinCapitalLetterAWithGrave,        /* 0xb6  U_LatinCapitalLetterAWithGrave */
   U_LatinCapitalLetterAWithTilde,        /* 0xb7  U_LatinCapitalLetterAWithTilde */
   U_LatinCapitalLetterOWithTilde,        /* 0xb8  U_LatinCapitalLetterOWithTilde */
   U_Diaeresis,                           /* 0xb9  U_Diaeresis */
   U_AcuteAccent,                         /* 0xba  U_AcuteAccent */
   U_Dagger,                              /* 0xbb  U_Dagger */
   U_ParagraphSign,                       /* 0xbc  U_ParagraphSign */
   U_CopyrightSign,                       /* 0xbd  U_CopyrightSign */
   U_RegisteredSign,                      /* 0xbe  U_RegisteredSign */
   U_TradeMarkSign,                       /* 0xbf  U_TradeMarkSign */
                                          
   U_LatinSmallLigatureIJ,                /* 0xc0  U_LatinSmallLigatureIJ */
   U_LatinCapitalLigatureIJ,              /* 0xc1  U_LatinCapitalLigatureIJ */
   U_HebrewLetterAlef,                    /* 0xc2  U_HebrewLetterAlef */
   U_HebrewLetterBet,                     /* 0xc3  U_HebrewLetterBet */
   U_HebrewLetterGimel,                   /* 0xc4  U_HebrewLetterGimel */
   U_HebrewLetterDalet,                   /* 0xc5  U_HebrewLetterDalet */
   U_HebrewLetterHe,                      /* 0xc6  U_HebrewLetterHe */
   U_HebrewLetterVav,                     /* 0xc7  U_HebrewLetterVav */
   U_HebrewLetterZayin,                   /* 0xc8  U_HebrewLetterZayin */
   U_HebrewLetterHet,                     /* 0xc9  U_HebrewLetterHet */
   U_HebrewLetterTet,                     /* 0xca  U_HebrewLetterTet */
   U_HebrewLetterYod,                     /* 0xcb  U_HebrewLetterYod */
   U_HebrewLetterKaf,                     /* 0xcc  U_HebrewLetterKaf */
   U_HebrewLetterLamed,                   /* 0xcd  U_HebrewLetterLamed */
   U_HebrewLetterMem,                     /* 0xce  U_HebrewLetterMem */
   U_HebrewLetterNun,                     /* 0xcf  U_HebrewLetterNun */
                                          
   U_HebrewLetterSamekh,                  /* 0xd0  U_HebrewLetterSamekh */
   U_HebrewLetterAyin,                    /* 0xd1  U_HebrewLetterAyin */
   U_HebrewLetterPe,                      /* 0xd2  U_HebrewLetterPe */
   U_HebrewLetterTsadi,                   /* 0xd3  U_HebrewLetterTsadi */
   U_HebrewLetterQof,                     /* 0xd4  U_HebrewLetterQof */
   U_HebrewLetterResh,                    /* 0xd5  U_HebrewLetterResh */
   U_HebrewLetterShin,                    /* 0xd6  U_HebrewLetterShin */
   U_HebrewLetterTav,                     /* 0xd7  U_HebrewLetterTav */
   U_HebrewLetterNun,                     /* 0xd8  U_HebrewLetterNun */
   U_HebrewLetterFinalKaf,                /* 0xd9  U_HebrewLetterFinalKaf */
   U_HebrewLetterFinalMem,                /* 0xda  U_HebrewLetterFinalMem */
   U_HebrewLetterFinalPe,                 /* 0xdb  U_HebrewLetterFinalPe */
   U_HebrewLetterFinalTsadi,              /* 0xdc  U_HebrewLetterFinalTsadi */
   U_SectionSign,                         /* 0xdd  U_SectionSign */
   U_ModifierLetterCircumflexAccent,      /* 0xde  U_ModifierLetterCircumflexAccent */
   U_Infinity,                            /* 0xdf  U_Infinity */
                                          
   U_GreekSmallLetterAlpha,               /* 0xe0  U_GreekSmallLetterAlpha */
   U_GreekSmallLetterBeta,                /* 0xe1  U_GreekSmallLetterBeta */
   U_GreekCapitalLetterGamma,             /* 0xe2  U_GreekCapitalLetterGamma */
   U_GreekSmallLetterPi,                  /* 0xe3  U_GreekSmallLetterPi */
   U_GreekCapitalLetterSigma,             /* 0xe4  U_GreekCapitalLetterSigma */
   U_GreekSmallLetterSigma,               /* 0xe5  U_GreekSmallLetterSigma */
   U_GreekSmallLetterMu,                  /* 0xe6  U_GreekSmallLetterMu */
   U_GreekSmallLetterTau,                 /* 0xe7  U_GreekSmallLetterTau */
   U_NIL,                                 /* 0xe8  ??? */
   U_NIL,                                 /* 0xe9  ??? */
   U_GreekCapitalLetterOmega,             /* 0xea  U_GreekCapitalLetterOmega */
   U_GreekSmallLetterDelta,               /* 0xeb  U_GreekSmallLetterDelta */
   U_ContourIntegral,                     /* 0xec  U_ContourIntegral */
   U_NIL,                                 /* 0xed  ??? */
   U_ElementOf,                           /* 0xee  U_ElementOf */
   U_Intersection,                        /* 0xef  U_Intersection */
                                          
   U_IdenticalTo,                         /* 0xf0  U_IdenticalTo */
   U_PlusMinusSign,                       /* 0xf1  U_PlusMinusSign */
   U_GreaterThanOrEqualTo,                /* 0xf2  U_GreaterThanOrEqualTo */
   U_LessThanOrEqualTo,                   /* 0xf3  U_LessThanOrEqualTo */
   U_Integral,                            /* 0xf4  U_Integral (upper half) */
   U_Integral,                            /* 0xf5  U_Integral (lower half) */
   U_DivisionSign,                        /* 0xf6  U_DivisionSign */
   U_AlmostEqualTo,                       /* 0xf7  U_AlmostEqualTo */
   U_DegreeSign,                          /* 0xf8  U_DegreeSign */
   U_Bullet,                              /* 0xf9  U_Bullet */
   U_MiddleDot,                           /* 0xfa  U_MiddleDot */
   U_SquareRoot,                          /* 0xfb  U_SquareRoot */
   U_SuperscriptLatinSmallLetterN,        /* 0xfc  U_SuperscriptLatinSmallLetterN */
   U_SuperscriptTwo,                      /* 0xfd  U_SuperscriptTwo */
   U_SuperscriptThree,                    /* 0xfe  U_SuperscriptThree */
   U_Macron                               /* 0xff  U_Macron */
};


/* +++ EOF +++ */
