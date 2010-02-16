/*******************************************************************************
*
*  Project name : UDO
*  Module name  : toc_html.c
*  Symbol prefix: -
*
*  Description  : Routinen im Bezug auf HTML, die sich um Kapitel, Labels, Aliase,
*                 dem Inhaltsverzeichnis und der automatischen Referenzierung kuemmern.
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
*  Co-Authors   : Ulf Dunkel (fd), Gerhard Stoll (ggs)
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
*  2010:
*    fd  Jan 23: file reformatted
*
******************************************|************************************/

#ifndef ID_TOC_HTML_C
#define ID_TOC_HTML_C
const char *id_toc_html_c= "@(#) toc_html.c    $Date$";
#endif





/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "portab.h"
#include "constant.h"
#include "udo_type.h"
#include "chr.h"
#include "file.h"
#include "msg.h"
#include "par.h"
#include "str.h"
#include "sty.h"
#include "udo.h"

#include "export.h"
#include "udomem.h"





/*******************************************************************************
*
*     GLOBAL PROCEDURES
*
******************************************|************************************/

/*******************************************************************************
*
*  set_html_navigation():
*     Creates the navigation bar for HTML output.
*
*  Note:
*     All data are found in token[].
*
*  Return:
*     TRUE  = OK
*     else  = error
*
******************************************|************************************/

GLOBAL BOOLEAN set_html_navigation(void)
{
   char     s[512],       /* */
           *cont,         /* */
           *data,         /* */
            inhalt[512];  /* */
   size_t   contlen;      /* */
   

   tokcpy2(s, 512);

   contlen = get_brackets_ptr(s, &cont, &data);

   if (contlen == 0 || cont == NULL || data == NULL)
   {
      error_syntax_error();
      return FALSE;
   }

   inhalt[0] = EOS; 
   strncpy(inhalt, cont, contlen);
   inhalt[contlen] = EOS;
   del_whitespaces(inhalt);

   if (strcmp(inhalt, "line") == 0)
   {
      del_whitespaces(data);
      
      html_navigation_line = TRUE;

      if (data[0] == EOS)
         um_strcpy(html_navigation_separator, "", 20, "set_html_navigation[html_navigation_line]");
      else
         um_strcpy(html_navigation_separator, &data[0], 20, "set_html_navigation[html_navigation_line]");
      
      return TRUE;
   }

   if (strcmp(inhalt, "image") == 0)
   {
      del_whitespaces(data);
      
      html_navigation_image = TRUE;

      if (data[0] == EOS)
         um_strcpy(html_navigation_image_fspec, "", 128, "set_html_navigation[html_navigation_image_fspec]");
      else
         um_strcpy(html_navigation_image_fspec, &data[0], 128, "set_html_navigation[html_navigation_image_fspec]");
      
      return TRUE;
   }

   error_unknown_html_navigation(inhalt);

   return FALSE;
}

/* +++ EOF +++ */
