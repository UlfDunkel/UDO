/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : sty.h
*  Symbol prefix: sty
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
*  Description  : style definitions
*
*
*-------------------------------------------------------------------------------
*
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Norbert Hanz (NHz)
*                 Gerhard Stoll (GS)
*                 Ulf Dunkel (fd)
*  Write access : NHz, GS, fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2009:
*    fd  Jun 08: header updated; definitions for C_COLOR_... updated (octal!)
*  2010:
*    fd  Feb 26: file tidied up, style macros revalued to fix the color bug
*    fd  Mar 08: try to avoid style macro chars which may be converted or casted 
*                 somewhere on the run (this whole MAGIC crap isn't rather safe)
*
******************************************|************************************/

#ifndef UDO_STY_H
#define UDO_STY_H





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _styleflag                 /* various style control flags */
{
   BOOLEAN   bold;
   BOOLEAN   footnote;
   BOOLEAN   italic;
   BOOLEAN   underlined;
   BOOLEAN   verbatim;
   BOOLEAN   twriter;
   BOOLEAN   insert;                      /* (!INS)...(!ins) New in V6.5.9 [NHz] */
   BOOLEAN   deleted;                     /* (!DEL)...(!del) */
   BOOLEAN   colour;                      /* New in V6.5.9 [NHz] */
   BOOLEAN   sup;                         /* (!SUP)...(!sup) New in V6.5.20 [GS] */
   BOOLEAN   sub;                         /* (!SUB)...(!sub) */
}  STYLEFLAG;

#endif /* UDO_STY_H */





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define STYLELEN         4                 /* length of placeholder string */

   /*
    *   The placeholders are formed as a 4 byte string like this:
    *   ---------------------------------------------------------
    *   "(!purple)" 
    *   -> ESC_STYLE_MAGIC + C_COLOR_PURPLE + C_STYLE_MAGIC 
    *   -> "\033\001" + "\034" + "\001"    (octal)
    *   -> "\x1B\x01\x1C\x01"              (hex)
    */

/* don't use             0                 -> C string closure EOS ! */
#define C_BOLD_ON        1
#define C_BOLD_OFF       2
#define C_ITALIC_ON      3
#define C_ITALIC_OFF     4
#define C_FOOT_ON        5
#define C_FOOT_OFF       6
#define C_UNDER_ON       7
#define C_UNDER_OFF      8
/* don't use             9                 -> TAB */
/* don't use            10                 -> LF (LineFeed) */
#define C_VERB_ON       11
#define C_VERB_OFF      12
/* don't use            13                 -> CR (Carriage Return) */
#define C_TWRITER_ON    14
#define C_TWRITER_OFF   15
                                          /* New in V6.5.9 [NHz] */
#define C_INSERT_ON     16
#define C_INSERT_OFF    17
#define C_DELETED_ON    18
#define C_DELETED_OFF   19
                                          /* New in V6.5.9 [NHz] */
#define C_COLOR_BLACK   20
/* don't use            21                -> ??? */
#define C_COLOR_SILVER  22
#define C_COLOR_GRAY    23
#define C_COLOR_WHITE   24
#define C_COLOR_MAROON  25
/* don't use            26                -> ESC */
#define C_COLOR_RED     27
#define C_COLOR_PURPLE  28
#define C_COLOR_FUCHSIA 29
#define C_COLOR_GREEN   30
#define C_COLOR_LIME    31
#define C_COLOR_OLIVE   32
#define C_COLOR_YELLOW  33
/* don't use            34                -> " */
#define C_COLOR_NAVY    35
#define C_COLOR_BLUE    36
#define C_COLOR_TEAL    37
/* don't use            38                -> & */
/* don't use            39                -> ' */
/* don't use            40                -> ( */
/* don't use            41                -> ) */
#define C_COLOR_AQUA    42
#define C_COLOR_OFF     43
                                          /* New in V6.5.20 [GS] */
#define C_SUP_ON        44
#define C_SUP_OFF       45
#define C_SUB_ON        46
/* don't use            47                -> / */
#define C_SUB_OFF       48





/*******************************************************************************
*
*     GLOBAL VARIABLES
*
d******************************************|************************************/

GLOBAL STYLEFLAG   styleflag;             /* Flags fuer die Stilpaare */

GLOBAL char        STYLEMAGIC[8];
GLOBAL char        BOLD_ON[8],
                   BOLD_OFF[8];
GLOBAL char        FOOT_ON[8],
                   FOOT_OFF[8];
GLOBAL char        ITALIC_ON[8],
                   ITALIC_OFF[8];
GLOBAL char        TWRITER_ON[8],
                   TWRITER_OFF[8];
GLOBAL char        UNDER_ON[8],
                   UNDER_OFF[8];
GLOBAL char        INSERT_ON[8],          /* New in V6.5.9 [NHz] */
                   INSERT_OFF[8];
GLOBAL char        DELETED_ON[8],
                   DELETED_OFF[8];
GLOBAL char        COLOR_BLACK[8],        /* New in V6.5.9 [NHz] */
                   COLOR_SILVER[8],
                   COLOR_GRAY[8],
                   COLOR_WHITE[8],
                   COLOR_MAROON[8],
                   COLOR_RED[8],
                   COLOR_PURPLE[8],
                   COLOR_FUCHSIA[8],
                   COLOR_GREEN[8],
                   COLOR_LIME[8],
                   COLOR_OLIVE[8],
                   COLOR_YELLOW[8],
                   COLOR_NAVY[8],
                   COLOR_BLUE[8],
                   COLOR_TEAL[8],
                   COLOR_AQUA[8],
                   COLOR_OFF[8];
GLOBAL char        SUP_ON[8],             /* New in V6.5.20 [GS] */
                   SUP_OFF[8];
GLOBAL char        SUB_ON[8],
                   SUB_OFF[8];





/*******************************************************************************
*
*     GLOBAL FUNCTION PROTOTYPES
*
******************************************|************************************/

GLOBAL void del_footnotes(char *s);
GLOBAL void del_internal_footnotes(char *s);
GLOBAL void del_html_styles(char *s);
GLOBAL void del_internal_styles(char *s);

GLOBAL void c_pch_styles(char *s);
GLOBAL void c_rtf_styles(char *s);
GLOBAL void c_win_styles(char *s);
GLOBAL void c_internal_styles(char *s);
GLOBAL void c_styles(char *s);

GLOBAL void check_styles(char *s);
GLOBAL void check_styleflags(void);
GLOBAL void check_verb_style(void);

GLOBAL void check_styles_drc_next_line(void);
GLOBAL void check_styles_asc_last_line(char *s);
GLOBAL void check_styles_asc_next_line(void);

GLOBAL void init_module_sty(void);


/* +++ EOF +++ */
