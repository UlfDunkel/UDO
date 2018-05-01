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
*    fd  Feb 14: - all set_html_...() functions moved from TOC to TOC_HTML
*                - function descriptions added
*
******************************************|************************************/

/*******************************************************************************
*
*     GLOBAL PROTOTYPES
*
******************************************|************************************/

   /* creates the navigation bar for HTML output */
GLOBAL _BOOL set_html_navigation(void);

   /* sets the variable html_doctype */
GLOBAL void set_html_doctype(int type);
GLOBAL void c_set_html_doctype(void);

   /* sets HTML header date */
GLOBAL void set_html_header_date(void);

   /* sets html_header_links variable */
GLOBAL void set_html_header_links(void);

   /* sets various html_frames_... flags */
GLOBAL void set_html_frames_layout(void);

   /* sets HTML filename */
GLOBAL void set_html_filename(void);

   /* sets HTML name prefix */
GLOBAL void set_html_filename_prefix(void);

   /* sets HTML dirname variable */
GLOBAL void set_html_dirname(void);

   /* sets ...SwitchLanguage variables */
GLOBAL void set_html_switch_language(void);

   /* sets HTML keywords */
GLOBAL void set_html_keywords(void);

   /* sets HTML description */
GLOBAL void set_html_description(void);

   /* sets HTML robots */
GLOBAL void set_html_robots(void);

   /* sets the sound for a node */
GLOBAL void set_html_bgsound(void);

   /* sets HTML backimage */
GLOBAL void set_html_backimage(void);

   /* sets HTML color */
GLOBAL void set_html_color(const int which);

   /* sets HTML style */
GLOBAL void set_html_style(void);

   /* sets HTML script name */
GLOBAL void set_html_script(void);

   /* sets HTML favicon */
GLOBAL void set_html_favicon(void);

   /* sets special color for HTML */
GLOBAL void set_html_special_color(struct rgb *rgb);

   /* sets counter_command */
GLOBAL void set_html_counter_command(void);

   /* sets html_frames_toc_title variable */
GLOBAL void set_html_frames_toc_title(void);

   /* sets html_frames_con_title variable */
GLOBAL void set_html_frames_con_title(void);

   /* sets html_modern_width variable */
GLOBAL void set_html_modern_width(void);

   /* sets html_modern_alignment variable */
GLOBAL void set_html_modern_alignment(void);

   /* sets html_modern_backimage variable */
GLOBAL void set_html_modern_backimage(void);

   /* sets html_frames_width variable */
GLOBAL void set_html_frames_width(void);

   /* sets html_frames_height variable */
GLOBAL void set_html_frames_height(void);

   /* sets html_frames_position variable */
GLOBAL void set_html_frames_position(void);

   /* sets html_frames_alignment variable */
GLOBAL void set_html_frames_alignment(void);

   /* sets html_frames_backimage variable */
GLOBAL void set_html_frames_backimage(void);

   /* sets html_button_alignment variable */
GLOBAL void set_html_button_alignment(void);

   /* sets html_quotes variable */
GLOBAL void set_html_quotes(void);


GLOBAL void init_module_toc_html(void);
GLOBAL void exit_module_toc_html(void);
