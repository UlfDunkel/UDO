/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : env.h
*  Symbol prefix: env
*
*  Description  : This module handles the environment routines which manage the 
*                 output of various environments and prepare them for 
*                 token_output().
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
*  Co-Authors   : Ulf Dunkel (fd)
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
*    fd  Feb 04: header updated; bDescDDOpen introduced
*    fd  Feb 26: new: bParagraphOpen
*    fd  Mar 04: bEnvShort[] -> bEnvCompressed[]
*
******************************************|************************************/

/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define ENV_IND_ASC_QUOT   5              /* Einrueckungstiefen der Umgebungen */
#define ENV_IND_RTF_QUOT   567
#define ENV_IND_WIN_QUOT   454

#define ENV_IND_ASC_ITEM   5
#define ENV_IND_RTF_ITEM   567
#define ENV_IND_WIN_ITEM   567

#define ENV_IND_ASC_ENUM   5
#define ENV_IND_RTF_ENUM   567
#define ENV_IND_WIN_ENUM   567

#define ENV_IND_ASC_DESC   5
#define ENV_IND_RTF_DESC   567
#define ENV_IND_WIN_DESC   567





/*******************************************************************************
*
*     GLOBAL VARIABLES
*
******************************************|************************************/

GLOBAL int       iEnvLevel;               /* Zaehler fuer Umgebungen */
                                          /* Typ der Umgebung (ENV_ITEM, ... */
GLOBAL int       iEnvType[MAXENVLEVEL + 1];
                                          /* Einrueckungstiefe einer Umgebung */
GLOBAL int       iEnvIndent[MAXENVLEVEL + 1];
                                          /* TRUE: compressed, FALSE: splendid (default) */
GLOBAL _BOOL   bEnvCompressed[MAXENVLEVEL + 1];
                                          /* Ist das naechste !item das erste? */
GLOBAL _BOOL   bEnv1stItem[MAXENVLEVEL + 1];
                                          /* Erster Absatz des !item? */
GLOBAL _BOOL   bEnv1stPara[MAXENVLEVEL + 1];

GLOBAL int       iItemLevel;              /* Zaehler fuer itemize-Umgebungen */
GLOBAL int       iEnumLevel;              /* Zaehler fuer enumerate-Umgeb. */
GLOBAL int       iDescLevel;              /* Zaehler fuer description-Umgeb. */
GLOBAL int       iListLevel;              /* Zaehler fuer xlist-Umgebungen */

GLOBAL _BOOL   bCalledEndDocument;      /* */
GLOBAL _BOOL   bCalledBeginDocument;    /* */

GLOBAL _BOOL   bDescDDOpen;             /* TRUE: description env.: <dd> open */
GLOBAL _BOOL   bParagraphOpen;          /* TRUE: <p> has been output */





/*******************************************************************************
*
*     GLOBAL PROTOTYPES
*
******************************************|************************************/

GLOBAL void check_environments_node(void);

GLOBAL void output_begin_verbatim(void);
GLOBAL void output_end_verbatim(void);

GLOBAL void output_begin_preformatted(void);
GLOBAL void output_end_preformatted(void);

GLOBAL void output_begin_linedraw(void);
GLOBAL void output_end_linedraw(void);

GLOBAL void output_begin_sourcecode(void);
GLOBAL void output_end_sourcecode(void);

GLOBAL void output_begin_comment(void);
GLOBAL void output_end_comment(void);

GLOBAL int strlen_indent(void);
GLOBAL void strcat_indent(char *s);
GLOBAL void strcpy_indent(char *s);

GLOBAL void c_begin_quote(void);
GLOBAL void c_end_quote(void);

GLOBAL void c_begin_center(void);
GLOBAL void c_end_center(void);

GLOBAL void c_begin_flushright(void);
GLOBAL void c_end_flushright(void);

GLOBAL void c_begin_flushleft(void);
GLOBAL void c_end_flushleft(void);

GLOBAL void c_begin_itemize(void);
GLOBAL void c_begin_enumerate(void);
GLOBAL void c_begin_description(void);
GLOBAL void c_begin_xlist(void);
GLOBAL void c_begin_blist(void);
GLOBAL void c_begin_ilist(void);
GLOBAL void c_begin_tlist(void);

GLOBAL void c_item(void);

GLOBAL void c_end_xlist(void);
GLOBAL void c_end_blist(void);
GLOBAL void c_end_ilist(void);
GLOBAL void c_end_tlist(void);
GLOBAL void c_end_description(void);
GLOBAL void c_end_enumerate(void);
GLOBAL void c_end_itemize(void);

GLOBAL void c_begin_document(void);
GLOBAL void c_end_document(void);

GLOBAL void c_begin_appendix(void);
GLOBAL void c_end_appendix(void);

GLOBAL void init_module_env(void);
GLOBAL void init_env_itemchar(void);
