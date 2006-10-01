/* ############################################################
   # @(#) toc_html.c
   # @(#)
   # @(#) Copyright (c) 1995-2001 by Dirk Hagedorn
   # @(#) Dirk Hagedorn (udo@dirk-hagedorn.de)
   #
   # This program is free software; you can redistribute it and/or
   # modify it under the terms of the GNU General Public License
   # as published by the Free Software Foundation; either version 2
   # of the License, or (at your option) any later version.
   # 
   # This program is distributed in the hope that it will be useful,
   # but WITHOUT ANY WARRANTY; without even the implied warranty of
   # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
   # GNU General Public License for more details.
   # 
   # You should have received a copy of the GNU General Public License
   # along with this program; if not, write to the Free Software
   # Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
   #
   #  Routinen im Bezug auf HTML, die sich um Kapitel, Labels, Aliase,
   #  dem Inhaltsverzeichnis und der automatischen
   #  Referenzierung kuemmern.
   #  
   #  
   #
   ############################################################   */

#ifndef ID_TOC_HTML_C
#define ID_TOC_HTML_C
const char *id_toc_html_c= "@(#) toc_html.c    $Date$";
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include "portab.h"
#include "constant.h"
#include "udo_type.h"
#include "msg.h"
#include "str.h"
#include "udo.h"

#include "export.h"

/* ############################################################
   # lokale Variablen
   ############################################################ */

/* ############################################################
   # lokale Prototypen
   ############################################################ */

/* --------------------------------------------------------------
   set_html_navigation()
   Setzen der Navigationsleiste fÅr HTML.
   Die Daten stehen in token[].
   <-    TRUE:   OK
         sonst:  Fehler
   --------------------------------------------------------------  */

GLOBAL BOOLEAN set_html_navigation ( void )
{
   char s[512], *cont, *data, inhalt[512];
   size_t contlen;

   tokcpy2(s, 512);

   contlen= get_brackets_ptr(s, &cont, &data);

   if (contlen==0 || cont==NULL || data==NULL)
   {
      error_syntax_error();
      return FALSE;
   }

   inhalt[0]= EOS; 
   strncpy(inhalt, cont, contlen);
   inhalt[contlen]= EOS;
   del_whitespaces(inhalt);

   if (strcmp(inhalt, "line")==0)
   {
      del_whitespaces(data);
      
      html_navigation_line = TRUE;

      if (data[0]==EOS)
         um_strcpy(html_navigation_separator, "", 20, "set_html_navigation[html_navigation_line]");
      else
         um_strcpy(html_navigation_separator, &data[0], 20, "set_html_navigation[html_navigation_line]");
      
      return TRUE;
   }

   if (strcmp(inhalt, "image")==0)
   {
      del_whitespaces(data);
      
      html_navigation_image = TRUE;

      if (data[0]==EOS)
         um_strcpy(html_navigation_image_fspec, "", 128, "set_html_navigation[html_navigation_image_fspec]");
      else
         um_strcpy(html_navigation_image_fspec, &data[0], 128, "set_html_navigation[html_navigation_image_fspec]");
      
      return TRUE;
   }

   error_unknown_html_navigation(inhalt);

   return FALSE;

}  /* set_docinfo */
