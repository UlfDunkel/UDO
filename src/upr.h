/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : upr.h
*  Symbol prefix: upr
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
*  Co-Authors   : Ulf Dunkel (fd), Thorsen Otto
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
*  2004:
*    tho Nov 14: created
******************************************|************************************/

#ifndef __UPR_H__
#define __UPR_H__

   /* ? */
GLOBAL void save_upr_entry_infile(const char *filename, int level);
   /* ? */
GLOBAL void save_upr_entry_outfile(const char *filename);
   /* ? */
GLOBAL void save_upr_entry_image(const char *filename);

/* Extra parameter line */
   /* ? */
GLOBAL void save_upr_entry_node(const int level, const char *filename, const char *title, FILE_LINENO line);
   /* ? */
GLOBAL void save_upr_entry_heading(const int level, const char *filename, const char *title, FILE_LINENO line);
   /* ? */
GLOBAL void save_upr_entry_alias(const char *filename, const char *title, FILE_LINENO line);
   /* ? */
GLOBAL void save_upr_entry_label(const char *filename, const char *title, FILE_LINENO line);
   /* ? */
GLOBAL void save_upr_entry_index(const int level, const char *filename, const char *title, FILE_LINENO line);

#endif /* __UPR_H__ */
