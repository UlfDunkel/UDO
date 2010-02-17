/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_raw.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer ...
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
*    fd  Feb 12: all octal chars converted into decimal values
*    fd  Feb 17: iso2sys_item[] removed (deprecated)
*
******************************************|************************************/

#ifndef ID_CHARSET_H
#define ID_CHARSET_H
const char  *id_charset_h = "@(#) chr_  .h    $date$";
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

typedef struct _ansi2ascii
{
   unsigned char   iso;                   /* */
   unsigned char   charsys;               /* */
}  ANSI2ASCII;





/*******************************************************************************
*
*     Recode System codepage into various codepages
*
******************************************|************************************/

typedef struct _chartable
{
   unsigned char   charsystem;            /* */
   char           *ansi;                  /* */
   char           *tex;                   /* */
   char           *html;                  /* */
}  CHARTABLE;


LOCAL const CHARTABLE   chrtab[128] =
{
   {   0, "\\'C7", "\\c{C}",         "&Ccedil;" },
   {   0, "\\'FC", "\"u",            "&uuml;"   },
   {   0, "\\'E9", "\\'{e}",         "&eacute;" },
   {   0, "\\'E2", "\\^{a}",         "&acirc;"  },
   {   0, "\\'E4", "\"a",            "&auml;"   },
   {   0, "\\'E0", "\\`{a}",         "&agrave;" },
   {   0, "\\'E5", "{\\aa}",         "&aring;"  },
   {   0, "\\'E7", "\\c{c}",         "&ccedil;" },
   {   0, "\\'EA", "\\^{e}",         "&ecirc;"  },
   {   0, "\\'EB", "\\\"{e}",        "&euml;"   },
   {   0, "\\'E8", "\\`{e}",         "&egrave;" },
   {   0, "\\'EF", "\\\"{i}",        "&iuml;"   },
   {   0, "\\'EE", "\\^{i}",         "&icirc;"  },
   {   0, "\\'EC", "\\`{i}",         "&igrave;" },
   {   0, "\\'C4", "\"A",            "&Auml;"   },
   {   0, "\\'C5", "{\\AA}",         "&Aring;"  },
   {   0, "\\'C9", "\\'{E}",         "&Eacute;" },
   {   0, "\\'E6", "{\\ae}",         "&aelig;"  },
   {   0, "\\'C6", "{\\AE}",         "&AElig;"  },
   {   0, "\\'F4", "\\^{o}",         "&ocirc;"  },
   {   0, "\\'F6", "\"o",            "&ouml;"   },
   {   0, "\\'F2", "\\`{o}",         "&ograve;" },
   {   0, "\\'FB", "\\^{u}",         "&ucirc;"  },
   {   0, "\\'F9", "\\`{u}",         "&ugrave;" },
   {   0, "\\'FF", "\\\"{y}",        "&yuml;"   },
   {   0, "\\'D6", "\"O",            "&Ouml;"   },
   {   0, "\\'DC", "\"U",            "&Uuml;"   },
   {   0, "\\'A2", "cent",           "&#162;"   },
   {   0, "\\'A3", "\\pounds{}",     "&#163;"   },
   {   0, "\\'A5", "yen",            "&#165;"   },
   {   0, "\\'DF", "{\\ss}",         "&szlig;"  },
   {   0, "\\'83", "$f$",            "&#166;"   },
   {   0, "\\'E1", "\\'{a}",         "&aacute;" },
   {   0, "\\'ED", "\\'{i}",         "&iacute;" },
   {   0, "\\'F3", "\\'{o}",         "&oacute;" },
   {   0, "\\'FA", "\\'{u}",         "&uacute;" },
   {   0, "\\'F1", "\\~{n}",         "&ntilde;" },
   {   0, "\\'D1", "\\~{N}",         "&Ntilde;" },
   {   0, "\\'AA", "\\b{a}",         "&#170;"   },
   {   0, "\\'BA", "\\b{o}",         "&#186;"   },
   {   0, "\\'BF", "?`",             "&#191;"   },
   {   0, "",      "",               ""         },
   {   0, "\\'AC", "$\\neg$",        "&#172;"   },
   {   0, "\\'BD", "$\\frac{1}{2}$", "&#189;"   },
   {   0, "\\'BC", "$\\frac{1}{4}$", "&#188;"   },
   {   0, "\\'A1", "!`",             "&#161;"   },
   {   0, "\\'AB", "\"<",            "&#171;"   },
   {   0, "\\'BB", "\">",            "&#187;"   },
   {   0, "\\'E3", "\\~{a}",         "&atilde;" },
   {   0, "\\'F5", "\\~{o}",         "&otilde;" },
   {   0, "\\'D8", "{\\O}",          "&Oslash;" },
   {   0, "\\'F8", "{\\o}",          "&oslash;" },
   {   0, "\\'9C", "{\\oe}",         "&#156;"   },
   {   0, "\\'8C", "{\\OE}",         "&#140;"   },
   {   0, "\\'C0", "\\`{A}",         "&Agrave;" },
   {   0, "\\'C3", "\\~{A}",         "&Atilde;" },
   {   0, "\\'D5", "\\~{O}",         "&Otilde;" },
   {   0, "\\'A8", "\\!{ }",         "&#168;"   },
   {   0, "\\'B4", "\\`{ }",         "&#180;"   },
   {   0, "\\'86", "\\dag{}",        "&#134;"   },
   {   0, "\\'B6", "\\P{}",          "&#182;"   },
   {   0, "\\'A9", "\\copyright{}",  "&#169;"   },
   {   0, "\\'AE", "(R)",            "&#174;"   },
   {   0, "\\'99", "(TM)",           "&#153;"   },
   {   0, "ij",    "ij",             "ij"       },
   {   0, "IJ",    "IJ",             "IJ"       },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "\\'A7", "\\S{}",          "&sect;"   },
   {   0, "\\'F7", "$\\wedge$",      "&#136;"   },
   {   0, "",      "$\\infty$",      ""         },
   {   0, "",      "$\\alpha$",      ""         },
   {   0, "\\'DF", "{\\ss}",         "&szlig;"  },
   {   0, "",      "$\\Gamma$",      ""         },
   {   0, "",      "$\\pi$",         ""         },
   {   0, "",      "$\\Sigma$",      ""         },
   {   0, "",      "$\\sigma$",      ""         },
   {   0, "\\'B5", "$\\mu$",         "&#181;"   },
   {   0, "",      "$\\tau$",        ""         },
   {   0, "",      "$\\Phi$",        ""         },
   {   0, "",      "$\\phi$",        ""         },
   {   0, "",      "$\\Omega$",      ""         },
   {   0, "",      "$\\delta$",      ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "$\\epsilon$",    ""         },
   {   0, "",      "$\\eta$",        ""         },
   {   0, "",      "$\\equiv$",      ""         },
   {   0, "\\'B1", "$\\pm$",         "&#177;"   },
   {   0, "",      "$\\geq$",        ""         },
   {   0, "",      "$\\leq$",        ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "",               ""         },
   {   0, "",      "$\\div$",        "&#247;"   },
   {   0, "",      "$\\approx$",     ""         },
   {   0, "\\'B0", "$\\circ$",       "&#176;"   },
   {   0, "\\'95", "$\\bullet$",     "&#149;"   },
   {   0, "\\'B7", "$\\bullet$",     "&#183;"   },
   {   0, "",      "$\\surd$",       ""         },
   {   0, "",      "$^n$",           ""         },
   {   0, "\\'B2", "$^2$",           "&#178;"   },
   {   0, "\\'B3", "$^3$",           "&#179;"   },
   {   0, "\\'AF", "",               "&#175;"   }      /* #macron */
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


#define UNI2SYSTABSIZE   64               /* fd:2010-02-11: was 63 ?!? */


LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   { "(!\"a)", ""  },
   { "(!\"e)", ""  },
   { "(!\"i)", ""  },
   { "(!\"o)", ""  },
   { "(!\"u)", ""  },
   { "(!\"y)", ""  },
   { "(!\"s)", ""  },
   { "(!\"A)", ""  },
   { "(!\"E)", ""  },
   { "(!\"I)", ""  },
   { "(!\"O)", ""  },
   { "(!\"U)", ""  },
   { "(!\"Y)", ""  },                     /* 13 */

   { "(!'a)",  ""  },
   { "(!'e)",  ""  },
   { "(!'i)",  ""  },
   { "(!'o)",  ""  },
   { "(!'u)",  ""  },
   { "(!'y)",  ""  },
   { "(!'A)",  ""  },
   { "(!'E)",  ""  },
   { "(!'I)",  ""  },
   { "(!'O)",  ""  },
   { "(!'U)",  ""  },
   { "(!'Y)",  ""  },                     /* 12 */

   { "(!`a)",  ""  },
   { "(!`e)",  ""  },
   { "(!`i)",  ""  },
   { "(!`o)",  ""  },
   { "(!`u)",  ""  },
   { "(!`A)",  ""  },
   { "(!`E)",  ""  },
   { "(!`I)",  ""  },
   { "(!`O)",  ""  },
   { "(!`U)",  ""  },                     /* 10 */

   { "(!^a)",  ""  },
   { "(!^e)",  ""  },
   { "(!^i)",  ""  },
   { "(!^o)",  ""  },
   { "(!^u)",  ""  },
   { "(!^A)",  ""  },
   { "(!^E)",  ""  },
   { "(!^I)",  ""  },
   { "(!^O)",  ""  },
   { "(!^U)",  ""  },                     /* 10 */

   { "(!~a)",  ""  },
   { "(!~n)",  ""  },
   { "(!~o)",  ""  },
   { "(!~A)",  ""  },
   { "(!~N)",  ""  },
   { "(!~O)",  ""  },                     /*  6 */

   { "(!.a)",  ""  },
   { "(!.A)",  ""  },                     /*  2 */

   { "(!&ae)", ""  },
   { "(!&AE)", ""  },
   { "(!&oe)", ""  },
   { "(!&OE)", ""  },                     /*  4 */

   { "(!,c)",  ""  },
   { "(!,C)",  ""  },                     /*  2 */

   { "(!_a)",  ""  },
   { "(!_o)",  ""  },                     /*  2 */

   { "(!\\o)", ""  },
   { "(!\\O)", ""  },                     /*  2 */

   { "(!#S)",  "." },
};


/* +++ EOF +++ */
