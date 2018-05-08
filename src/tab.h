/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : tab.h
*  Symbol prefix: tab
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
*    fd  Feb 22: header adjusted
*
******************************************|************************************/

/* ############################################################
   # globale Variablen
   ############################################################   */

/* ############################################################
   # globale Funktionen
   ############################################################   */
GLOBAL void c_table_caption(void);
GLOBAL void c_table_caption_nonr(void);
GLOBAL void table_get_header(char *s);

GLOBAL _BOOL table_add_line(char *s);
GLOBAL void table_output(void);

GLOBAL void set_table_counter(const int i);

GLOBAL void set_table_alignment(void);

GLOBAL void init_module_tab(void);
