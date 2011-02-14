/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : toc_html.h
*  Symbol prefix: -
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
*  Description  : -
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
*    fd  Jan 23: file reformatted
*  2011:
*    fd  Feb 14: all set_html_...() functions moved from TOC to TOC_HTML
*
******************************************|************************************/

/*******************************************************************************
*
*     GLOBAL PROTOTYPES
*
******************************************|************************************/

   /* creates the navigation bar for HTML output */
GLOBAL BOOLEAN set_html_navigation(void);

   /* sets the variable html_doctype */
GLOBAL void set_html_doctype(void);

   /* sets HTML header date */
GLOBAL void set_html_header_date(void);

   /*  */
GLOBAL void set_html_header_links(void);

   /* sets various html_frames_... flags */
GLOBAL void set_html_frames_layout(void);

GLOBAL void set_html_filename(void);
GLOBAL void set_html_filename_prefix(void);
GLOBAL void set_html_dirname(void);
GLOBAL void set_html_switch_language(void);

GLOBAL void set_html_keywords(void);
GLOBAL void set_html_description(void);
GLOBAL void set_html_robots(void);        /* new V6.5.17 */
GLOBAL void set_html_bgsound(void);       /* New in 6.5.20 [GS] */
GLOBAL void set_html_backimage(void);
GLOBAL void set_html_color(const int which);

GLOBAL void set_html_style(void);
GLOBAL void set_html_script(void);
GLOBAL void set_html_favicon(void);
GLOBAL void set_html_special_color(char *hc);
GLOBAL void set_html_counter_command(void);

GLOBAL void set_html_frames_toc_title(void); /* New in 6.5.16 [GS] */
GLOBAL void set_html_frames_con_title(void); /* New in 6.5.16 [GS] */

GLOBAL void set_html_modern_width(void);
GLOBAL void set_html_modern_alignment(void);
GLOBAL void set_html_modern_backimage(void);
GLOBAL void set_html_frames_width(void);
GLOBAL void set_html_frames_height(void);
GLOBAL void set_html_frames_alignment(void);
GLOBAL void set_html_frames_position(void);
GLOBAL void set_html_frames_backimage(void);
GLOBAL void set_html_button_alignment(void);
GLOBAL void set_html_quotes(void);

/* +++ EOF +++ */
