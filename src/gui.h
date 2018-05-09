/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : gui.h
*  Symbol prefix: gui
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
*                - VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*
******************************************|************************************/

/* ######################################################################
   # Variablen
   ######################################################################   */
GLOBAL _BOOL no_stderr_output;
GLOBAL _BOOL no_pass2;


/* ######################################################################
   # Funktionen
   ######################################################################   */

GLOBAL void show_status_info(const char *s);
GLOBAL void show_status_loginfo(const char *s);
GLOBAL void show_status_node(const char *numbers, const char *name);
GLOBAL void show_status_file_1(FILE_LINENO Pass1Lines, const char *s);
GLOBAL void show_status_file_2(FILE_LINENO Pass2Lines, const char *s);
GLOBAL void show_status_percent(FILE_LINENO Pass1Lines, FILE_LINENO Pass2Lines);
GLOBAL void show_status_pass(const char *s);
GLOBAL void show_status_udo2udo(FILE_LINENO Pass2Lines, const char *s);
GLOBAL void show_status_errors(const char *s);

GLOBAL void show_logln_message(const char *s);

GLOBAL void warning_err_logfile(void);
GLOBAL void warning_err_treefile(void);
GLOBAL void warning_err_uprfile(void);
GLOBAL void warning_err_hypfile(void);
GLOBAL void warning_err_idxfile(void);
GLOBAL void warning_err_destination(void);
GLOBAL void multitasking_interrupt(void);
GLOBAL _BOOL break_action(void);
