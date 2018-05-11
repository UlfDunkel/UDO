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
   _BOOL   bold;                        /* (!B)...(!b) */
   _BOOL   footnote;                    /* (!N)...(!n) */
   _BOOL   italic;                      /* (!I)...(!i) */
   _BOOL   underlined;                  /* (!U)...(!u) */
   _BOOL   verbatim;                    /* (!V)...(!v) */
   _BOOL   twriter;                     /* (!T)...(!t) */
   _BOOL   ghost;                       /* (!G)...(!g) */
   _BOOL   shadow;                      /* (!S)...(!s) */
   _BOOL   outline;                     /* (!O)...(!o) */
   _BOOL   insert;                      /* (!INS)...(!ins) */
   _BOOL   deleted;                     /* (!DEL)...(!del) */
   _BOOL   color;                       /* (!<colorname>)...(!coloff) */
   _BOOL   sup;                         /* (!SUP)...(!sup) */
   _BOOL   sub;                         /* (!SUB)...(!sub) */
}  STYLEFLAG;





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

/*
 * length of internal placeholder string
 * may not exceed CMD_STYLELEN or you get buffer overflows at least in c_styles()
 */
#define STYLELEN         4

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
#define C_INSERT_ON     16
#define C_INSERT_OFF    17
#define C_DELETED_ON    18
#define C_DELETED_OFF   19
/* don't use            21                -> Vertical space */
#define C_GHOST_ON      22
#define C_GHOST_OFF     23
#define C_SHADOW_ON     24
#define C_SHADOW_OFF    25
/* don't use            26                -> Ctrl-Z */
/* don't use            27                -> ESC */
#define C_OUTLINE_ON    28
#define C_OUTLINE_OFF   29
/* don't use 32-64 */
#define C_COLOR_BLACK   65
#define C_COLOR_SILVER  66
#define C_COLOR_GRAY    67
#define C_COLOR_WHITE   68
#define C_COLOR_MAROON  69
#define C_COLOR_RED     70
#define C_COLOR_PURPLE  71
#define C_COLOR_FUCHSIA 72
#define C_COLOR_GREEN   73
#define C_COLOR_LIME    74
#define C_COLOR_OLIVE   75
#define C_COLOR_YELLOW  76
#define C_COLOR_NAVY    77
#define C_COLOR_BLUE    78
#define C_COLOR_TEAL    79
#define C_COLOR_AQUA    80
#define C_COLOR_OFF     81
#define C_SUP_ON        82
#define C_SUP_OFF       83
#define C_SUB_ON        84
#define C_SUB_OFF       85





/*******************************************************************************
*
*     GLOBAL VARIABLES
*
d******************************************|************************************/

GLOBAL STYLEFLAG   styleflag;             /* flags of currently active styles */

GLOBAL char        BOLD_ON[8],
                   BOLD_OFF[8];
GLOBAL char        ITALIC_ON[8],
                   ITALIC_OFF[8];
GLOBAL char        TWRITER_ON[8], TWRITER_OFF[8];
GLOBAL char        UNDER_ON[8], UNDER_OFF[8];
GLOBAL char        GHOST_ON[8], GHOST_OFF[8];
GLOBAL char        SHADOW_ON[8], SHADOW_OFF[8];
GLOBAL char        OUTLINE_ON[8], OUTLINE_OFF[8];
GLOBAL char        INSERT_ON[8], INSERT_OFF[8];
GLOBAL char        DELETED_ON[8], DELETED_OFF[8];
GLOBAL char        COLOR_BLACK[8],
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
GLOBAL char        SUP_ON[8], SUP_OFF[8];
GLOBAL char        SUB_ON[8], SUB_OFF[8];





/*******************************************************************************
*
*     GLOBAL FUNCTION PROTOTYPES
*
******************************************|************************************/

void del_html_styles(char *s);
void del_internal_styles(char *s);

void c_pch_styles(char *s);
void c_rtf_styles(char *s);
void c_win_styles(char *s);
void c_internal_styles(char *s);
void c_styles(char *s);
_BOOL c_footnotes(char *s);

GLOBAL void check_styles(char *s);
GLOBAL void check_styleflags(void);
GLOBAL void check_verb_style(void);

GLOBAL void check_styles_drc_next_line(void);
GLOBAL void check_styles_asc_last_line(char *s);
GLOBAL void check_styles_asc_next_line(void);

GLOBAL void init_module_sty(void);


#endif /* UDO_STY_H */
