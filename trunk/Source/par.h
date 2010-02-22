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
                 - VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*
******************************************|************************************/

/*   ############################################################
   # Typen
   ############################################################   */
#ifndef UDO_PAR_H
#define UDO_PAR_H

/*   --------------------------------------------------
   Trennvorschlaege
   --------------------------------------------------   */
#define   HYPHEN_LEN   128

typedef struct _hyphen
{
   char   hyphen[HYPHEN_LEN+1];   /* Wort mit Trennstrichen drin   */
   char   solo[HYPHEN_LEN+1];      /* gleiches Wort, aber ohne !-   */
}   HYPHEN, *pHYPHEN;


/*   --------------------------------------------------
   Makros
   --------------------------------------------------   */
#define   MACRO_NAME_LEN   32
#define   MACRO_CONT_LEN   256

typedef struct _macros
{
   char   name[MACRO_NAME_LEN+1];      /* Der Name des Makros      */
   char   entry[MACRO_CONT_LEN+1];   /* Der Inhalt des Makros   */
   BOOLEAN   vars;                  /* mit Parametern? PL3      */
}   MACROS, *pMACROS;


/*   --------------------------------------------------
   Definitionen
   --------------------------------------------------   */
#define   DEFINE_NAME_LEN   32
#define   DEFINE_CONT_LEN   256

typedef struct _defs
{
   char name[DEFINE_NAME_LEN+1];      /* Der Name der Definition   */
   char entry[DEFINE_CONT_LEN+1];      /* Der Inhalt            */
   BOOLEAN   vars;                  /* mit Parametern? PL3      */
}   DEFS, *pDEFS;


/*   --------------------------------------------------
   Allgemeiner Platzhalter
   --------------------------------------------------   */
typedef struct _placeholder            
{
   char   magic[10];   /* Eine Steuermarke <ESC><0xB0+nr>   */
   char   *entry;      /* Das komplette Kommando         */
   char   *text;      /* Nur Text (wichtig fuer toklen())   */
   BOOLEAN   replaced;   /* TRUE: PH ist bereits ersetzt worden */
}   PLACEHOLDER;


/*   --------------------------------------------------
   Spezielle Platzhalter fuer Formatbefehle
   --------------------------------------------------   */
typedef struct _speccmd
{
   char   magic[6];   /* Eine Steuermarke <ESC><0xB0+nr>   */
   char   *entry;      /* Das komplette Kommando         */
   BOOLEAN   replaced;   /* TRUE: PH ist bereits ersetzt worden */
}   SPECCMD;

#endif   /* UDO_PAR_H */



/*   ############################################################
   # globale Variablen
   ############################################################   */
GLOBAL UWORD   hyphen_counter;      /* Anzahl von geladenen Trennregeln      */
GLOBAL UWORD   macro_counter;      /* Anzahl geladener Makros            */
GLOBAL UWORD   define_counter;      /* Anzahl geladener defines            */


/*   ############################################################
   # globale Funktionen
   ############################################################   */
GLOBAL void replace_variables ( char *s, const char *cmd, const char *entry);

GLOBAL void reset_speccmds(void);
GLOBAL BOOLEAN add_speccmd ( char *entry );
GLOBAL BOOLEAN insert_speccmd ( char *s, const char *rep, char *entry );
GLOBAL void replace_speccmds(char *s);

GLOBAL BOOLEAN add_placeholder ( char *entry, char *rawtext );
GLOBAL BOOLEAN insert_placeholder ( char *s, const char *rep, char *entry, char *rawtext );
GLOBAL void replace_placeholders(char *s);
GLOBAL void replace_placeholders_text(char *s);
GLOBAL void reset_placeholders(void);
GLOBAL size_t pholdlen ( int i );

GLOBAL void c_internal_index ( char *s, const BOOLEAN inside_b4_macro);

GLOBAL void c_commands_inside ( char *s, const BOOLEAN inside_b4_macro );


GLOBAL void replace_hyphens(char *s);
GLOBAL void add_hyphen(void);

GLOBAL void replace_macros(char *s);
GLOBAL BOOLEAN add_macro(void);

GLOBAL void replace_defines(char *s);
GLOBAL BOOLEAN add_define(void);


GLOBAL void init_module_par(void);
GLOBAL void exit_module_par(void);


/* +++ EOF +++ */
