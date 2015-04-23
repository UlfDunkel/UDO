/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : par.h
*  Symbol prefix: par
*
*  Description  : ???
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
*  Co-Authors   : Gerhard Stoll (ggs), Ulf Dunkel
*  Write access : ggs, fd
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
*    fd  Feb 22: - header adjusted
*                - void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  May 19: file tidied up
*
******************************************|************************************/

#ifndef UDO_PAR_H
#define UDO_PAR_H





/*******************************************************************************
*
*     GLOBAL VARIABLES
*
******************************************|************************************/

GLOBAL size_t         hyphen_counter;      /* # of loaded hyphenation rules */
GLOBAL _UWORD         macro_counter;       /* # of loaded macros */
GLOBAL _UWORD         define_counter;      /* # of loaded definitions */





/*******************************************************************************
*
*     GLOBAL PROTOTYPES
*
******************************************|************************************/

   /* remove special format command placeholders from the text */
GLOBAL void reset_speccmds(void);

   /* insert special format commands into the text as placeholders */
GLOBAL _BOOL add_speccmd(const char *entry);

   /* insert special format command placeholders into the text */
GLOBAL _BOOL insert_speccmd(char *s, const char *rep, const char *entry);

   /* replace special format command placeholders in the text */
GLOBAL void replace_speccmds(char *s);

   /*  */
GLOBAL _BOOL add_placeholder(const char *entry, const char *rawtext);

   /*  */
GLOBAL _BOOL insert_placeholder(char *s, const char *rep, const char *entry, const char *rawtext);

   /* replace the internal placeholder commands by human-readable content */
GLOBAL void replace_placeholders(char *s);

   /*  */
GLOBAL void replace_placeholders_text(char *s);

   /* handle links and other internal commands */
GLOBAL void reset_placeholders(void);

   /* return length of placeholder text */
GLOBAL size_t pholdlen(const char *p);

   /*  */
GLOBAL void c_internal_index(char *s, const _BOOL inside_b4_macro);

   /*  */
GLOBAL void c_commands_inside(char *s, const _BOOL inside_b4_macro);

   /* replace word with hyphenated word in document */
GLOBAL void replace_hyphens(char *s);

   /* add hyphen to list of hyphens */
GLOBAL void add_hyphen(void);

   /* replace macro (!%s) with macro content in document */
GLOBAL void replace_macros(char *s);

GLOBAL _BOOL is_internal_name(const char *name);

   /* add macro to list of macros */
GLOBAL _BOOL add_macro(void);

   /* replace definition (!%s) with definition content in document */
GLOBAL void replace_defines(char *s);

   /* add definition to list of definitions */
GLOBAL _BOOL add_define(void);
GLOBAL _BOOL del_define(void);

   /* initialize all arrays used in this module */
GLOBAL void init_module_par(void);

   /* release all arrays used in this module */
GLOBAL void exit_module_par(void);

void sort_hyphens(void);

#endif /* UDO_PAR_H */
