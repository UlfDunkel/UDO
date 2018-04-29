/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_all.h
*  Symbol prefix: chr
*
*  Description  : Allgemeine Uebersetzungstabellen
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
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#include "udoport.h"





typedef struct _quoteinfo
{
   char c;
   const char *quoted;
}  QUOTEINFO;





/*******************************************************************************
*
*     Recode ???
*
******************************************|************************************/

LOCAL QUOTEINFO const tex7bit[] =
{
   { '\025', "\\S{}"          },          /* Paragraph unter DOS und OS/2 */
   { '\"',   "{\\symbol{34}}" },
   { '#',    "\\#"            },
   { '$',    "\\$"            },
   { '%',    "\\%"            },
   { '&',    "\\&"            },
   { '<',    "$<$"            },
   { '>',    "$>$"            },
   { '\\',   "$\\backslash$"  },
   { '_',    "\\_"            },
   { '{',    "\\{"            },
   { '|',    "$\\mid$"        },
   { '}',    "\\}"            },
   { '^',    "{\\symbol{94}}" },
   { '`',    "{\\symbol{96}}" },
#if 0
   { '[',    "{\\symbol{91}}" },
   { ']',    "{\\symbol{93}}" }
#endif
};
#define MAXTEX7BIT   ((int)ArraySize(tex7bit))

/* ------------------------------------------------------------ */

LOCAL QUOTEINFO const rtf7bit[] =
{
   { '\025', "\\'A7" },                   /* Paragraph unter DOS und OS/2 */
   { '{',    "\\{"   },
   { '}',    "\\}"   },
   { '\\',   "\\\\"  }
};
#define MAXRTF7BIT   ((int)ArraySize(rtf7bit))

/* ------------------------------------------------------------ */

LOCAL QUOTEINFO const win7bit[] =
{
   { '\025', "\\'A7" },                   /* Paragraph unter DOS und OS/2 */
   { '{',    "\\{"   },
   { '}',    "\\}"   },
   { '\\',   "\\\\"  }
};
#define MAXWIN7BIT   ((int)ArraySize(win7bit))

/* ------------------------------------------------------------ */

LOCAL QUOTEINFO const html7bit[] =
{
   { '\025', "&sect;" },                  /* Paragraph unter DOS und OS/2 */
   { '&',    "&amp;"  },
   { '<',    "&lt;"   },
   { '>',    "&gt;"   },
   { '\"',   "&quot;" }
};
#define MAXHTML7BIT  ((int)ArraySize(html7bit))

/* ------------------------------------------------------------ */

LOCAL QUOTEINFO const htag7bit[] =
{
   { '&',  "&&"  },
   { '<',  "&<"  },
   { '\\', "&\\" }
};
#define MAXHTAG7BIT  ((int)ArraySize(htag7bit))

/* ------------------------------------------------------------ */

LOCAL QUOTEINFO const lds7bit[] =
{
   { '\025', "&sect;"   },                /* Paragraph unter DOS und OS/2 */
   { '&',    "&amp;"    },
   { '<',    "&lt;"     },
   { '>',    "&gt;"     },
   { '$',    "&dollar;" },
   { '#',    "&num;"    },
   { '%',    "&percnt;" },
   { '\"',   "&dquot;"  },
   { '~',    "&tilde;"  }
};
#define MAXLDS7BIT  ((int)ArraySize(lds7bit))

/* ------------------------------------------------------------ */

LOCAL QUOTEINFO const lyx7bit[] =
{
   { '\\', "\\backslash"INDENT_S }
};
#define MAXLYX7BIT  ((int)ArraySize(lyx7bit))

/* ------------------------------------------------------------ */

LOCAL QUOTEINFO const ipf7bit[] =
{
   { ':', "&colon." },
   { '&', "&amp."   },
   { '.', "&per."   }
};
#define MAXIPF7BIT  ((int)ArraySize(ipf7bit))





/*******************************************************************************
*
*     Recode ???
*
******************************************|************************************/

typedef struct _unitable
{
   const char *uni;
   const char *win;
   const char *tex;
   const char *html;
   const char *lyx;
} UNITABLE;

LOCAL const UNITABLE unitab[] =
{
   { "(!\"a)", "\\'E4", "\\\"a",   "&auml;",   "\xE4" },
   { "(!\"e)", "\\'EB", "\\\"{e}", "&euml;",   "\xEB" },
   { "(!\"i)", "\\'EF", "\\\"{i}", "&iuml;",   "\xEF" },
   { "(!\"o)", "\\'F6", "\\\"o",   "&ouml;",   "\xF6" },
   { "(!\"u)", "\\'FC", "\\\"u",   "&uuml;",   "\xFC" },
   { "(!\"y)", "\\'FF", "\\\"{y}", "&yuml;",   "\xFF" },
   { "(!\"s)", "\\'DF", "{\\ss}",  "&szlig;",  "\xDF" },
   { "(!\"A)", "\\'C4", "\\\"A",   "&Auml;",   "\xC4" },
   { "(!\"E)", "\\'CB", "\\\"{E}", "&Euml;",   "\xCB" },
   { "(!\"I)", "\\'CF", "\\\"{I}", "&Iuml;",   "\xCF" },
   { "(!\"O)", "\\'D6", "\\\"O",   "&Ouml;",   "\xD6" },
   { "(!\"U)", "\\'DC", "\\\"U",   "&Uuml;",   "\xDC" },

   { "(!'a)",  "\\'E1", "\\'{a}",  "&aacute;", "\xE1" },
   { "(!'e)",  "\\'E9", "\\'{e}",  "&eacute;", "\xE9" },
   { "(!'i)",  "\\'ED", "\\'{i}",  "&iacute;", "\xED" },
   { "(!'o)",  "\\'F3", "\\'{o}",  "&oacute;", "\xF3" },
   { "(!'u)",  "\\'FA", "\\'{u}",  "&uacute;", "\xFA" },
   { "(!'y)",  "\\'FD", "\\'{y}",  "&yacute;", "\xFD" },
   { "(!'A)",  "\\'C1", "\\'{A}",  "&Aacute;", "\xC1" },
   { "(!'E)",  "\\'C9", "\\'{E}",  "&Eacute;", "\xC9" },
   { "(!'I)",  "\\'CD", "\\'{I}",  "&Iacute;", "\xCD" },
   { "(!'O)",  "\\'D3", "\\'{O}",  "&Oacute;", "\xD3" },
   { "(!'U)",  "\\'DA", "\\'{U}",  "&Uacute;", "\xDA" },
   { "(!'Y)",  "\\'DD", "\\'{Y}",  "&Yacute;", "\xDD" },

   { "(!`a)",  "\\'E0", "\\`{a}",  "&agrave;", "\xE0" },
   { "(!`e)",  "\\'E8", "\\`{e}",  "&egrave;", "\xE8" },
   { "(!`i)",  "\\'EC", "\\`{i}",  "&igrave;", "\xEC" },
   { "(!`o)",  "\\'F2", "\\`{o}",  "&ograve;", "\xF2" },
   { "(!`u)",  "\\'F9", "\\`{u}",  "&ugrave;", "\xF9" },
   { "(!`A)",  "\\'C0", "\\`{A}",  "&Agrave;", "\xC0" },
   { "(!`E)",  "\\'C8", "\\`{E}",  "&Egrave;", "\xC8" },
   { "(!`I)",  "\\'CC", "\\`{I}",  "&Igrave;", "\xCC" },
   { "(!`O)",  "\\'D2", "\\`{O}",  "&Ograve;", "\xD2" },
   { "(!`U)",  "\\'D9", "\\`{U}",  "&Ugrave;", "\xD9" },

   { "(!^a)",  "\\'E2", "\\^{a}",  "&acirc;",  "\xE2" },
   { "(!^e)",  "\\'EA", "\\^{e}",  "&ecirc;",  "\xEA" },
   { "(!^i)",  "\\'EE", "\\^{i}",  "&icirc;",  "\xEE" },
   { "(!^o)",  "\\'F4", "\\^{o}",  "&ocirc;",  "\xF4" },
   { "(!^u)",  "\\'FB", "\\^{u}",  "&ucirc;",  "\xFB" },
   { "(!^A)",  "\\'C2", "\\^{A}",  "&Acirc;",  "\xC2" },
   { "(!^E)",  "\\'CA", "\\^{E}",  "&Ecirc;",  "\xCA" },
   { "(!^I)",  "\\'CE", "\\^{I}",  "&Icirc;",  "\xCE" },
   { "(!^O)",  "\\'D4", "\\^{O}",  "&Ocirc;",  "\xD4" },
   { "(!^U)",  "\\'DB", "\\^{U}",  "&Ucirc;",  "\xDB" },

   { "(!~a)",  "\\'E3", "\\~{a}",  "&atilde;", "\xE3" },
   { "(!~n)",  "\\'F1", "\\~{n}",  "&ntilde;", "\xF1" },
   { "(!~o)",  "\\'F5", "\\~{o}",  "&otilde;", "\xF5" },
   { "(!~A)",  "\\'C3", "\\~{A}",  "&Atilde;", "\xC3" },
   { "(!~N)",  "\\'D1", "\\~{N}",  "&Ntilde;", "\xD1" },
   { "(!~O)",  "\\'D5", "\\~{O}",  "&Otilde;", "\xD5" },

   { "(!.a)",  "\\'E5", "{\\aa}",  "&aring;",  "\xE5" },
   { "(!.A)",  "\\'C5", "{\\AA}",  "&Aring;",  "\xC5" },

   { "(!&ae)", "\\'E6", "{\\ae}",  "&aelig;",  "\xE6" },
   { "(!&AE)", "\\'C6", "{\\AE}",  "&AElig;",  "\xC6" },
   { "(!&oe)", "\\'9C", "{\\oe}",  "&#156;",   "\x9C" },
   { "(!&OE)", "\\'8C", "{\\OE}",  "&#140;",   "\x8C" },

   { "(!,c)",  "\\'E7", "\\c{c}",  "&ccedil;", "\xE7" },
   { "(!,C)",  "\\'C7", "\\c{C}",  "&Ccedil;", "\xC7" },

   { "(!_a)",  "\\'AA", "\\b{a}",  "&#170;",   "\xAA" },
   { "(!_o)",  "\\'BA", "\\b{o}",  "&#186;",   "\xBA" },

   { "(!\\o)", "\\'F8", "{\\o}",   "&oslash;", "\xF8" },
   { "(!\\O)", "\\'D8", "{\\O}",   "&Oslash;", "\xD8" },

   { "(!#S)",  "\\'A7", "\\S{}",   "&sect;",   "\xA7" }
};
#define  UNITABLESIZE   ArraySize(unitab)
