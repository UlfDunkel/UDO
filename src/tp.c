/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : tp.c
*  Symbol prefix: tp
*
*  Description  : This module contains routines which handle the environment
*                 Routinen, die die Ausgabe der zahlreichen Umgebungen
*                 verwalten und fuer token_output() vorbereiten
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
*  Co-Authors   : Norbert Hanz (NHz), Ulf Dunkel (fd), Gerhard Stoll (ggs)
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
*  2009:
*    fd  Jun 04: !docinfo [translator] introduced
*  2010:
*    fd  Mar 02: - html_footer(): notes added and mailto: handling enhanced
*                - webmastername    -> domain_name
*                - webmasterurl     -> domain_link
*                - webmasteremail   -> contact_name
*                - webmastermailurl -> contact_link
*    fd  Mar 05: file tidied up
*  2013:
*    fd  Oct 23: - <h1> on HTML5 now uses class UDO_h1_align_center| UDO_h1_align_right
*                - <h2> on HTML5 now uses class UDO_h2_align_center| UDO_h2_align_right
*    fd  Oct 31: c_gif_output() renamed: c_html_image_output()
*  2014
*    ggs Apr 20: Add Node6
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "udoport.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "chr.h"
#include "env.h"
#include "file.h"
#include "img.h"
#include "msg.h"
#include "par.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"

#include "export.h"
#include "tp.h"
#include "udomem.h"





/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

LOCAL _BOOL init_docinfo_data(char *data, char **var, int allow_empty);
LOCAL void init_titdat(void);
LOCAL void free_titdat(char **var);










/*******************************************************************************
*
*     LOCAL / GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  set_show_variable():
*     Setzen von Informationen fuer Variablen
*
*  Notes:
*     New in V6.5.19 [NHz]
*     Die Daten stehen in token[]. Ich habe die Funktion hier herein
*     gepackt, da ich keine neue C-Datei eroeffnen wollte.
*     
*     !show_variable [format] [foo]
*
*  Out:
*     - TRUE: OK
*
******************************************|************************************/

GLOBAL _BOOL set_show_variable(void)
{
   char     s[512],       /* */
           *cont,         /* */
           *data,         /* */
            inhalt[512];  /* */
   size_t   contlen;      /* */
   
   
   tokcpy2(s, 512);

   contlen = strlen(token[1]);            /* New in V6.5.9 [NHz] */

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

   if (strcmp(inhalt, "source_filename") == 0)
   {
      show_variable.source_filename = TRUE;
      return TRUE;
   }
   
   return FALSE;
}





/*******************************************************************************
*
*  set_mainlayout():
*     Setzen von Informationen fuer das Layout (neue Version)
*
*  Notes:
*     New in r6pl16 [NHz]
*     Die Daten stehen in token[]. Ich habe die Funktion hier herein
*     gepackt, da ich keine neue C-Datei eroeffnen wollte.
*     Hier werden Vorgaben gemacht, wenn der Nutzer keine Angaben zum
*     Layout macht.
*
*  Out:
*     - TRUE: OK
*
******************************************|************************************/

GLOBAL _BOOL set_mainlayout(void)
{
                                          /* Fixed Bug #40 in r6.3pl16 [NHz] */
   init_docinfo_data("A4PORTRAIT", &(laydat.paper), FALSE);

   init_docinfo_data("Times New Roman", &(laydat.propfontname), FALSE);
   laydat.propfontsize = 11;
   
   init_docinfo_data("Courier New", &(laydat.monofontname), FALSE);
   laydat.monofontsize = 11;
   
   init_docinfo_data("/UseNone", &(laydat.pagemode), FALSE);
   init_docinfo_data("/SinglePage", &(laydat.viewerpreferences), FALSE);
   init_docinfo_data("false", &(laydat.fitwindow), FALSE);
   init_docinfo_data("1", &(laydat.openpage), FALSE);
   init_docinfo_data("false", &(laydat.hidetoolbar), FALSE);
   init_docinfo_data("false", &(laydat.hidemenubar), FALSE);
   
                                          /* New in r6pl16 [NHz] */
   laydat.node1size = 0;
   laydat.node2size = 0;
   laydat.node3size = 0;
   laydat.node4size = 0;
   laydat.node5size = 0;
   laydat.node6size = 0;

   return TRUE;
}





/*******************************************************************************
*
*  set_doclayout():
*     Setzen von Informationen fuer das Layout (neue Version)
*
*  Notes:
*     New in r6pl15 [NHz]:
*     Die Daten stehen in token[]. Ich habe die Funktion hier herein
*     gepackt, da ich keine neue C-Datei eroeffnen wollte.
*
*     !doclayout [format] [foo]
*
*  Out:
*     - TRUE: OK
*     - error
*
******************************************|************************************/

GLOBAL _BOOL set_doclayout(void)
{
   char   s[512],        /* */
         *cont_format,   /* */
         *cont_content,  /* */
         *data,          /* */
          format[512],   /* */
          content[512];  /* */
   char  *page,          /* */
          page2[2];      /* */
                         /* */
   struct size_brackets   contlen;


   tokcpy2(s, 512);

   contlen = get_two_brackets_ptr(s, &cont_format, &cont_content, &data);

   if (contlen.format == 0 || contlen.content == 0 || cont_content == NULL || cont_format == NULL || data == NULL)
   { 
      error_syntax_error();
      return FALSE;
   }

   format[0] = EOS; 
   strncpy(format, cont_format, contlen.format);
   format[contlen.format] = EOS;
   del_whitespaces(format);

   content[0] = EOS;        
   strncpy(content, cont_content, contlen.content);
   content[contlen.content] = EOS;
   del_whitespaces(content);

   if (strcmp(content, "paper") == 0)
   { 
      if (str_for_desttype(format))       /* Layout festlegen */
         init_docinfo_data(data, &(laydat.paper), FALSE);

      return TRUE;
   }

   if (strcmp(content, "propfontname") == 0)
   { 
      if (str_for_desttype(format))       /* Set proportional font */
         init_docinfo_data(data, &(laydat.propfontname), FALSE);

      return TRUE;
   }

   if (strcmp(content, "propfontsize") == 0)
   {  
      if (str_for_desttype(format))       /* Set size of proportional font */
         laydat.propfontsize = atoi(data);

      return TRUE;
   }

   if (strcmp(content, "monofontname") == 0)
   { 
      if (str_for_desttype(format))       /* Set aquidistant font */
         init_docinfo_data(data, &(laydat.monofontname), FALSE);

      return TRUE;
   }

   if (strcmp(content, "monofontsize") == 0)
   {    
      if (str_for_desttype(format))       /* Set size of the aquidistant font */
         laydat.monofontsize = atoi(data);

      return TRUE;
   }

                                          /* New in r6pl16 [NHz] */
   if (strcmp(content, "node1size") == 0)
   {  
      if (str_for_desttype(format))       /* Set size of node */
         laydat.node1size = atoi(data);

      return TRUE;
   }

   if (strcmp(content, "node2size") == 0)
   {  
      if (str_for_desttype(format))       /* Set size of subnode */
         laydat.node2size = atoi(data);

      return TRUE;
   }

   if (strcmp(content, "node3size") == 0)
   {  
      if (str_for_desttype(format))       /* Set size of subsubnode */
         laydat.node3size = atoi(data);

      return TRUE;
   }

   if (strcmp(content, "node4size") == 0)
   { 
      if (str_for_desttype(format))       /* Set size of subsubsubnode */
         laydat.node4size = atoi(data);

      return TRUE;
   }

   if (strcmp(content, "node5size") == 0)
   {
      if (str_for_desttype(format))       /* Set size of subsubsubsubnode */
         laydat.node5size = atoi(data);

      return TRUE;
   }

   if (strcmp(content, "node6size") == 0)
   {
      if (str_for_desttype(format))       /* Set size of subsubsubsubnode */
         laydat.node6size = atoi(data);

      return TRUE;
   }
                                          /* Specialties for Postscript */
   if (strcmp(content, "openMode") == 0)
   {
      if (strstr(data, "Outlines"))
         init_docinfo_data("/UseOutlines", &(laydat.pagemode), FALSE);
      else if (strstr(data, "Thumbs"))
         init_docinfo_data("/UseThumbs", &(laydat.pagemode), FALSE);
      else if (strstr(data, "Fullscreen"))
         init_docinfo_data("/FullScreen", &(laydat.pagemode), FALSE);
      else
         init_docinfo_data("/UseNone", &(laydat.pagemode), FALSE);

      page = strstr(data, "Page=");

      if (page != NULL)
      {
         page2[0] = *(page + 5);
         page2[1] = EOS;

         init_docinfo_data(page2, &(laydat.openpage), FALSE);
      }
      else
         init_docinfo_data("1", &(laydat.openpage), FALSE);

      if (strstr(data, "HideToolbar"))
         init_docinfo_data("true", &(laydat.hidetoolbar), FALSE);
      else
         init_docinfo_data("false", &(laydat.hidetoolbar), FALSE);

      if (strstr(data, "HideMenubar"))
         init_docinfo_data("true", &(laydat.hidemenubar), FALSE);
      else
         init_docinfo_data("false", &(laydat.hidemenubar), FALSE);

      if (strstr(data, "OneColumn"))
         init_docinfo_data("/OneColumn", &(laydat.viewerpreferences), FALSE);
      else if (strstr(data, "ColumnLeft"))
         init_docinfo_data("/TwoColumnLeft", &(laydat.viewerpreferences), FALSE);
      else if (strstr(data, "ColumnRight"))
         init_docinfo_data("/TwoColumnRight", &(laydat.viewerpreferences), FALSE);
      else
         init_docinfo_data("/SinglePage", &(laydat.viewerpreferences), FALSE);

      if (strstr(data, "Title"))
         init_docinfo_data("true", &(laydat.fitwindow), FALSE);
      else
         init_docinfo_data("false", &(laydat.fitwindow), FALSE);

      return TRUE;
   }

   return FALSE;
}





/*******************************************************************************
*
*  init_docinfo_data():
*     Anpassung der Daten fuer die Titelseite samt Anforderung des benoetigten Speichers
*
*  Notes:
*     [voja][R6PL17] I needed to do the buffer creation first in this function,
*     else you can't use memmove() with compilers like GCC 3.x and
*     MS VS .net. An segmentation fault will occur (Bug #0000016).
*     I guess this is because of better memory protection techniques:
*     The *data coming in can be an constant(!) value. I think these compilers
*     write constant variable allocations to a protected memory region.
*     Writing to this region will crash...
*
*  Out:
*     - TRUE: OK
*     - error
*
******************************************|************************************/

LOCAL _BOOL init_docinfo_data(

char       *data,         /* ^ to content */
char      **var,          /* ^^ to variable */
int         allow_empty)  /* TRUE: empty data are okay, FALSE: throw error message */
{
   char    *buffer;       /* */
   size_t   len;          /* */

   len = strlen(data)*sizeof(char);
   len *=2;                               /* We need space if some text will be replace */
   len++;                                 /* End of string */

   buffer = (char *)um_malloc(len);

   if (buffer)                            /* Check if the buffer could be allocated */
   {
      /* First we copy the data to the buffer, this prevents bug #16 with modern compilers */
      strcpy(buffer, data);
      
      del_whitespaces(buffer);            /* Parameter was data */
      c_divis(buffer);                    /* Parameter was data */
      c_vars(buffer);                     /* Parameter was data */
      c_tilde(buffer);                    /* Parameter was data */
      c_styles(buffer);                   /* Parameter was data */
      del_internal_styles(buffer);        /* Parameter was data */
      replace_udo_tilde(buffer);          /* Parameter was data */
      replace_udo_nbsp(buffer);           /* Parameter was data */
      replace_udo_quotes(buffer);         /* Parameter was data */
      delete_all_divis(buffer);           /* Parameter was data */

      if (data[0] == EOS && !allow_empty)
      {
         error_empty_docinfo();
         return FALSE;
      }

      *var = buffer;

      return TRUE;
   }

   /* An error occured when allocating the buffer */
   error_malloc_failed();
   bFatalErrorDetected = TRUE;
   return FALSE;
}





/*******************************************************************************
*
*  set_docinfo():
*     set document information for title page (new approach) 
*
*  Notes:
*     The data can be found in token[]. In former versions of UDO, e.g. the 
*     app name was defined using "!program UDO", now with "!docinfo [program] UDO".
*
*  Out:
*     - TRUE: OK
*     - error
*
******************************************|************************************/

GLOBAL _BOOL set_docinfo(void)
{
   char     s[512],              /* */
           *cont,                /* */
           *data,                /* */
            inhalt[512],         /* */
           *buffer;              /* */
   char     sDriv[512],          /* */
            sPath[512],          /* */
            sFile[512],          /* */
            sSuff[512];          /* */
   size_t   contlen;             /* */
   char     udo_macro[]="UDO_",  /* */
            macro_tmp[512];      /* V6.5.9 */
   
   
   tokcpy2(s, 512);                       /* */
   
   contlen = strlen(token[1]);            /* New in V6.5.9 [NHz] */
   
   um_strncpy(macro_tmp, token[1] + 1, contlen - 2, 500, "set_docinfo[1]");
   um_strncpy(token[1], udo_macro, 5, 10, "set_docinfo[2]");
   um_strncat(token[1], macro_tmp, (long)(contlen-2L), 500, "set_docinfo[3]");
   add_define();
   
   if (desttype == TOKPS)                 /* New: Fixed bug #0000040 in r6.3pl16 [NHz] */
      node2postscript(s, KPS_PS2DOCINFO);
   
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
   
   if (desttype == TOKPS)                 /* New: Fixed Bug #0000040 in r6.3pl16 [NHz] */
      node2postscript(data, KPS_DOCINFO2PS);
   
   
   /* --- authorimage --- */
   
   if (strcmp(inhalt,"authorimage") == 0)
   {
      del_whitespaces(data);
      
      if (data[0] == EOS)
      {
         error_empty_docinfo();
      }
      else
      {
         path_adjust_separator(data);
         buffer = (char *) um_malloc(strlen(data) * sizeof(char) + 1);
         
         if (buffer)
         {
            strcpy(buffer, data);
            titdat.authorimage = buffer;
            
            if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
            {
               replace_char(titdat.authorimage, "\\", "/");    /*r6pl4*/
                                          /* r6pl9: Ausmasse nicht ermitteln -> da */
                                          /* ueber c_html_image_output() ausgegeben wird  */
            }
         }
         else
         {
            error_malloc_failed();
            bFatalErrorDetected = TRUE;
         }
      }
      
      return TRUE;
   }
   

   /* --- authoricon --- */
   
   if (strcmp(inhalt,"authoricon") == 0)  /*r6pl6*/
   {
      del_whitespaces(data);
      
      if (data[0] == EOS)
      {
         error_empty_docinfo();
      }
      else
      {                                   /* r6pl12: Endung abschneiden und mit !html_img_suffix ersetzen */
         fsplit(data, sDriv, sPath, sFile, sSuff);
         sprintf(data, "%s%s%s", sPath, sFile, sDocImgSuffix);
         path_adjust_separator(data);
         
         buffer = (char*)um_malloc(strlen(data) * sizeof(char) + 1);
         
         if (buffer)
         {
            strcpy(buffer, data);
            titdat.authoricon = buffer;
            
            if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
            {
               replace_char(titdat.authoricon, "\\", "/");
               
               if (my_stricmp(sDocImgSuffix, ".gif") == 0)
               {                          /* r6pl9: Ausmasse ermitteln */
                  strinsert(data, old_outfile.path);
                  strinsert(data, old_outfile.driv);
                  /* strcat(data, ".gif"); */
                  path_adjust_separator(data);
                  
                  if (!get_gif_size(data, &titdat.authoriconWidth, &titdat.authoriconHeight))
                  {
                     error_read_gif(data);
                  }
               }
            }
         }
         else
         {
            error_malloc_failed();
            bFatalErrorDetected = TRUE;
         }
      }
      
      return TRUE;
   }
   
   
   /* --- authoricon_active --- */
   
   if (strcmp(inhalt, "authoricon_active") == 0)     /*r6pl13*/
   {
      del_whitespaces(data);
      
      if (data[0] == EOS)
      {
         error_empty_docinfo();
      }
      else
      {                                   /* r6pl12: Endung abschneiden und mit !html_img_suffix ersetzen */
         fsplit(data, sDriv, sPath, sFile, sSuff);
         sprintf(data, "%s%s%s", sPath, sFile, sDocImgSuffix);
         path_adjust_separator(data);
         
         buffer = (char*)um_malloc(strlen(data) * sizeof(char) + 1);
         
         if (buffer)
         {
            strcpy(buffer, data);
            titdat.authoricon_active = buffer;
            
            if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
            {
               replace_char(titdat.authoricon_active, "\\", "/");
               
               if (my_stricmp(sDocImgSuffix, ".gif") == 0)
               {                          /* r6pl9: Ausmasse ermitteln */
                  strinsert(data, old_outfile.path);
                  strinsert(data, old_outfile.driv);
                  /* strcat(data, ".gif"); */
                  path_adjust_separator(data);
                  
                  if (!get_gif_size(data, &titdat.authoriconActiveWidth, &titdat.authoriconActiveHeight))
                  {
                     error_read_gif(data);
                  }
               }
            }
         }
         else
         {
            error_malloc_failed();
            bFatalErrorDetected = TRUE;
         }
      }
     
      return TRUE;
   }
   
   
   /* --- programimage --- */
   
   if (strcmp(inhalt, "programimage") == 0)
   {
      del_whitespaces(data);
      
      if (data[0] == EOS)
      {
         error_empty_docinfo();
      }
      else
      {
         path_adjust_separator(data);
         buffer = (char*)um_malloc(strlen(data) * sizeof(char) + 1);
         
         if (buffer)
         {
            strcpy(buffer, data);
            titdat.programimage = buffer;
            
            if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
            {
               replace_char(titdat.programimage, "\\", "/");   /*r6pl4*/
                                          /* r6pl9: Ausmasse nicht ermitteln -> da */
                                          /* ueber c_html_image_output() ausgegeben wird  */
            }
         }
         else
         {
            error_malloc_failed();
            bFatalErrorDetected = TRUE;
         }
      }
      
      return TRUE;
   }
   
   
   /* --- title --- */
   
   if (strcmp(inhalt,"title") == 0)
   {
      init_docinfo_data(data, &(titdat.title), FALSE);
      return TRUE;
   }
   
   
   /* --- program --- */
   
   if (strcmp(inhalt,"program") == 0)
   {
      init_docinfo_data(data, &(titdat.program), FALSE);
      return TRUE;
   }
   
   
   /* --- version --- */
   
   if (strcmp(inhalt,"version") == 0)
   {
      init_docinfo_data(data, &(titdat.version), FALSE);
      return TRUE;
   }

   
   /* --- date --- */
   
   if (strcmp(inhalt,"date") == 0)
   {
      init_docinfo_data(data, &(titdat.date), FALSE);
      return TRUE;
   }

   
   /* --- author --- */
   
   if (strcmp(inhalt,"author") == 0)
   {
      init_docinfo_data(data, &(titdat.author), FALSE);
      return TRUE;
   }

   
   /* --- address --- */
   
   if (strcmp(inhalt, "address") == 0)
   {
      if (address_counter < MAXADDRESS)
      {
         address_counter++;
         init_docinfo_data(data, &(titdat.address[address_counter]), FALSE);
      }
      
      return TRUE;
   }

   
   /* --- keywords --- */
   
   /* New in r6pl15 [NHz] */
   if (strcmp(inhalt,"keywords") == 0)
   {
      init_docinfo_data(data, &(titdat.keywords), FALSE);
      return TRUE;
   }

   
   /* --- description --- */
   
   /* New in r6pl15 [NHz] */
   if (strcmp(inhalt,"description") == 0)
   {
      init_docinfo_data(data, &(titdat.description), FALSE);
      return TRUE;
   }

   
   /* --- robots --- */
   
   /* New in V6.5.17 */
   if (strcmp(inhalt,"robots") == 0)
   {
      init_docinfo_data(data, &(titdat.robots), FALSE);
      
      if (strcmp(titdat.robots,"none") != 0)
      {
         if (strcmp(titdat.robots,"noindex") != 0)
         {
            if (strcmp(titdat.robots,"index") != 0)
            {
               if (strcmp(titdat.robots,"nofollow") != 0)
               {
                  if (strcmp(titdat.robots,"follow") != 0)
                  {
                                          /* For HTML Apple Help */
                     if (strcmp(titdat.robots,"keywords") != 0)
                     {
                                          /* For HTML Apple Help */
                        if (strcmp(titdat.robots,"segments") != 0)
                        {
                                          /* For HTML Apple Help */
                           if (strcmp(titdat.robots,"anchors") != 0)
                           {
                              error_syntax_error();
                              titdat.robots = NULL;
                              return TRUE;
                           }
                        }
                     }
                  }
               }
            }
         }
      }
      
      return TRUE;
   }
   

   /* --- company --- */

   if (strcmp(inhalt,"company") == 0)     /* New in V6.5.2 [NHz] */
   {
      init_docinfo_data(data, &(titdat.company), FALSE);
      return TRUE;
   }
   

   /* --- category --- */
   
   if (strcmp(inhalt, "category") == 0)   /* New in V6.5.2 [NHz] */
   {
      init_docinfo_data(data, &(titdat.category), FALSE);
      return TRUE;
   }
   

   /* --- stgdatabase --- */
   
                                          /* Spezialitaeten fuer ST-Guide *//*r6pl4*/
   if (strcmp(inhalt, "stgdatabase") == 0)
   {
      init_docinfo_data(data, &(titdat.stg_database), TRUE);
      return TRUE;
   }
   

   /* --- drcstatusline --- */
   
                                          /* Spezialitaeten fuer DRC *//*r6pl4*/
   if (strcmp(inhalt, "drcstatusline") == 0) 
   {
      init_docinfo_data(data, &(titdat.drc_statusline), FALSE);
      return TRUE;
   }
   

   /* --- htmltitle --- */
   
   if (strcmp(inhalt, "htmltitle") == 0)  /* Spezialitaeten fuer HTML */
   {
      init_docinfo_data(data, &(titdat.htmltitle), FALSE);
      return TRUE;
   }
   

   /* --- domain_name --- */
   
   if (strcmp(inhalt, "domain_name") == 0)
   {
      init_docinfo_data(data, &(titdat.domain_name), FALSE);
      return TRUE;
   }
   

   /* --- domain_link --- */
   
   if (strcmp(inhalt, "domain_link") == 0)
   {
      del_whitespaces(data);              /* nicht init_...!!! */
      convert_tilde(data);
      
      if (data[0] == EOS)
      {
         error_empty_docinfo();
      }
      else
      {
         buffer = (char*)um_malloc(strlen(data) * sizeof(char) + 1);
         
         if (buffer)
         {
            strcpy(buffer, data);
            titdat.domain_link = buffer;
         }
         else
         {
            error_malloc_failed();
            bFatalErrorDetected = TRUE;
         }
      }

      return TRUE;
   }
   

   /* --- contact_name --- */
   
   if (strcmp(inhalt, "contact_name") == 0)
   {
      init_docinfo_data(data, &(titdat.contact_name), FALSE);
      return TRUE;
   }
   

   /* --- contact_link --- */
   
   if (strcmp(inhalt, "contact_link") == 0)
   {
      init_docinfo_data(data, &(titdat.contact_link), FALSE);
      return TRUE;
   }
   

   /* --- appletitle --- */

   if (strcmp(inhalt,"appletitle") == 0)  /* Spezialitaeten fuer HTML Apple Help V6.5.17 */
   {
      init_docinfo_data(data, &(titdat.appletitle), TRUE);
      return TRUE;
   }
   

   /* --- appleicon --- */
   
   if (strcmp(inhalt,"appleicon") == 0)   /* Spezialitaeten fuer HTML Apple Help V6.5.17 */
   {
      init_docinfo_data(data, &(titdat.appleicon), TRUE);
      return TRUE;
   }
   
   
   /* --- translator --- */
   
   if (strcmp(inhalt,"translator") == 0)
   {
      init_docinfo_data(data, &(titdat.translator), TRUE);
      return TRUE;
   }
   
   /* --- distributor --- */
   
   if (strcmp(inhalt,"distributor") == 0)
   {
      init_docinfo_data(data, &(titdat.distributor), TRUE);
      return TRUE;
   }
   
   error_unknown_docinfo(inhalt);
   
   return FALSE;
}





/*******************************************************************************
*
*  c_maketitle():
*     creates and outputs title page of the document
*
*  Out:
*     -
*
******************************************|************************************/

GLOBAL void c_maketitle(void)
{
   int       i;                 /* counter var. */
   char      n[512],            /* */
             s1[128],           /* */
             s2[128];           /* */
   _BOOL   has_author,        /* flag */
             has_program,       /* flag */
             has_title,         /* flag */
             has_version,       /* flag */
             has_date,          /* flag */
             has_authorimage,   /* flag */
             has_programimage,  /* flag */
             has_address,       /* flag */
             has_company,       /* flag; New in V6.5.2 [NHz] */
             has_translator,    /* flag */
             has_distributor;   /* flag */
   char      closer[8] = "\0";  /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   if (called_maketitle)                  /* this function has been used already? */
   {
      error_called_twice("!maketitle");   /*r6pl2*/
      return;
   }

   called_maketitle = TRUE;               /* set flag when this function is used */

   has_author       = (titdat.author       != NULL);
   has_authorimage  = (titdat.authorimage  != NULL);
   has_address      = (address_counter     >  0);
   has_program      = (titdat.program      != NULL);
   has_programimage = (titdat.programimage != NULL);
   has_title        = (titdat.title        != NULL);
   has_version      = (titdat.version      != NULL);
   has_date         = (titdat.date         != NULL);
                                          /* New in V6.5.2 [NHz] */
   has_company      = (titdat.company      != NULL);
   has_translator   = (titdat.translator   != NULL);
   has_distributor  = (titdat.distributor  != NULL);

   if ( !(    has_author
           || has_authorimage
           || has_program
           || has_programimage
           || has_title
           || has_version
           || has_date
           || has_address
           || has_company                 /* New in V6.5.2 [NHz] */
           || has_translator
           || has_distributor
          )
      )
   {
      error_missing_title_data();         /* r6pl2 */
      return;
   }


   switch (desttype)                      /* which output format? */
   {
   case TOTEX:                            /* TeX */
   case TOPDL:                            /* */
      outln("\\begin{titlepage}");
      outln("\\begin{center}");
      
      if (has_title)
      {
         voutlnf("{\\Large %s} \\\\", titdat.title);
         outln("\\bigskip");
      }

      if (has_programimage)
      {
         switch (iTexVersion)
         {
         case TEX_LINDNER:
         case TEX_STRUNK:
            c_begin_center();
            c_img_output(titdat.programimage, "", FALSE);
            c_end_center();
            break;
            
         case TEX_EMTEX:
         case TEX_MIKTEX:                 /* V6.5.20 [CS] */
            c_begin_center();
            c_msp_output(titdat.programimage, "", FALSE);
            c_end_center();
            break;
            
         case TEX_TETEX:
            c_begin_center();
            c_eps_output(titdat.programimage, "", ".eps", FALSE);
            c_end_center();
         }
      }
      
      if (has_program)
      {
         voutlnf("{\\Huge %s} \\\\", titdat.program);
         outln("\\bigskip");
      }

      if (has_version)
      {
         voutlnf("{\\large %s} \\\\", titdat.version);
         outln("\\bigskip");
      }
      
      if (has_date)
      {
         voutlnf("{\\large %s} \\\\", titdat.date);
      }

      if (has_author || has_authorimage)
      {
         voutlnf("\\vfill\n%s\\\\\n\\medskip", lang.by);
      }

      if (has_authorimage)
      {
         switch (iTexVersion)
         {
         case TEX_LINDNER:
         case TEX_STRUNK:
            c_begin_center();
            c_img_output(titdat.authorimage, "", FALSE);
            c_end_center();
            break;
            
         case TEX_EMTEX:
            c_begin_center();
            c_msp_output(titdat.authorimage, "", FALSE);
            c_end_center();
            break;
            
         case TEX_TETEX:
            c_begin_center();
            c_eps_output(titdat.authorimage, "", ".eps", FALSE);
            c_end_center();
         }
      }

      if (has_author)
      {
         voutlnf("%s \\\\", titdat.author);
      }

      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         auto_quote_chars(lang.fur, FALSE);
         voutlnf("\\vfill\n%s\\\\\n\\medskip", lang.fur);
         voutlnf("%s \\\\", titdat.company);
      }

      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               voutlnf("%s \\\\", titdat.address[i]);
            }
         }
      }

      if (has_translator)
      {
         auto_quote_chars(lang.translator, FALSE);
         voutlnf("\\vfill\n%s\\\\\n\\medskip", lang.translator);
         voutlnf("%s \\\\", titdat.translator);
      }

      if (has_distributor)
      {
         auto_quote_chars(lang.distributor, FALSE);
         voutlnf("\\vfill\n%s\\\\\n\\medskip", lang.distributor);
         voutlnf("%s \\\\", titdat.distributor);
      }

      outln("\\end{center}");
      outln("\\end{titlepage}");
      break;

   case TOLYX:                            /* */
      outln("\\layout Title");
      outln("\\fill_top");
      outln("");
      
      if (has_title)
      {
         voutlnf("\\layout Section*\n\\align center\n%s\n\\newline\n", titdat.title);
      }
      
      if (has_program)
      {
         voutlnf("\\size giant %s\n", titdat.program);
      }
      
      if (has_version)
      {
         voutlnf("\\layout Subsection*\n\\align center\n%s\n", titdat.version);
      }
      
      if (has_date)
      {
         voutlnf("\\layout Subsection*\n\\align center\n%s\n", titdat.date);
      }
      
      if (has_author)
      {
         voutlnf("\\fill_bottom\n\\layout Subsubsection*\n\\align center\n\n%s\n", lang.by);
         voutlnf("\\layout Subsection*\n\\align center\n\n%s\n", titdat.author);
      }
      
      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         voutlnf("\\fill_bottom\n\\layout Subsubsection*\n\\align center\n\n%s\n", lang.fur);
         voutlnf("\\layout Subsection*\n\\align center\n\n%s\n", titdat.company);
      }
      
      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               voutlnf("\\layout Subsection*\n\\align center\n%s\n", titdat.address[i]);
            }
         }
      }
      
      if (has_translator)
      {
         voutlnf("\\fill_bottom\n\\layout Subsubsection*\n\\align center\n\n%s\n", lang.translator);
         voutlnf("\\layout Subsection*\n\\align center\n\n%s\n", titdat.translator);
      }
      
      if (has_distributor)
      {
         voutlnf("\\fill_bottom\n\\layout Subsubsection*\n\\align center\n\n%s\n", lang.distributor);
         voutlnf("\\layout Subsection*\n\\align center\n\n%s\n", titdat.distributor);
      }
      
      break;

   case TOINF:                            /* */
      outln("@titlepage");
      outln("@sp 1");
      
      if (has_title)
      {
         voutlnf("@center @titlefont{%s}", titdat.title);
         outln("@sp 1");
      }
      
      if (has_program)
      {
         voutlnf("@center @titlefont{%s}", titdat.program);
         outln("@sp 1");
      }
      
      if (has_version)
      {
         voutlnf("@center %s", titdat.version);
         outln("@sp 1");
      }
      
      if (has_date)
      {
         voutlnf("@center %s", titdat.date);
         outln("@sp 1");
      }
      
      if (has_author)
      {
         outln("@sp 10");
         voutlnf("@center %s", lang.by);
         outln("@sp 1");
         voutlnf("@center %s", titdat.author);
      }
      
      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         outln("@sp 10");
         voutlnf("@center %s", lang.fur);
         outln("@sp 1");
         voutlnf("@center %s", titdat.company);
      }
      
      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               voutlnf("@center %s", titdat.address[i]);
            }
         }
      }
      
      if (has_translator)
      {
         outln("@sp 10");
         voutlnf("@center %s", lang.translator);
         outln("@sp 1");
         voutlnf("@center %s", titdat.translator);
      }
      
      if (has_distributor)
      {
         outln("@sp 10");
         voutlnf("@center %s", lang.distributor);
         outln("@sp 1");
         voutlnf("@center %s", titdat.distributor);
      }
      
      outln("@end titlepage");
      break;

   case TOSTG:                            /* ST-Guide */
      outln("");
      voutlnf("@node \"%s\"", lang.title);
      stg_headline("", lang.title);
      outln("");
      outln("@autorefoff");
      
      if (has_title)
      {
         outlncenter(titdat.title);
         outln("");
      }

      if (has_programimage)
      {
         strcpy(n, titdat.programimage);
         change_sep_suffix(n, ".img");    /* PL6 */
         c_begin_center();
         c_img_output(n, "", FALSE);
         c_end_center();
      }
      
      if (has_program)
      {
         outlncenter(titdat.program);
         outln("");
      }

      if (has_version)
         outlncenter(titdat.version);
      
      if (has_date)
         outlncenter(titdat.date);
      
      if (has_author || has_authorimage)
      {
         outln("");
         outlncenter(lang.by);
      }

      if (has_authorimage)
      {
         strcpy(n, titdat.authorimage);
         change_sep_suffix(n, ".img");    /* PL6 */
         c_begin_center();
         c_img_output(n, "", FALSE);
         c_end_center();
      }

      if (has_author)
      {
         outln("");
         outlncenter(titdat.author);
      }

      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         outln("");
         outlncenter(lang.fur);
         outln("");
         outlncenter(titdat.company);
      }

      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               outlncenter(titdat.address[i]);
            }
         }
      }
      
      if (has_translator)
      {
         outln("");
         outlncenter(lang.translator);
         outln("");
         outlncenter(titdat.translator);
      }

      if (has_distributor)
      {
         outln("");
         outlncenter(lang.distributor);
         outln("");
         outlncenter(titdat.distributor);
      }

      outln("@autorefon");
      outln("");

      if (uses_tableofcontents)
      {
         outln("");
         outlncenter(lang.contents);
      }
      
      outln("@endnode");
      outln("");
      break;

   case TOAMG:                            /* */
      outln("");
      voutlnf("@node \"%s\" \"%s\"", lang.title, titleprogram);
      stg_headline("", lang.title);
      outln("");

      if (has_title)
      {
         outlncenter(titdat.title);
         outln("");
      }

      if (has_program)
      {
         outlncenter(titdat.program);
         outln("");
      }

      if (has_version)
         outlncenter(titdat.version);
      
      if (has_date)
         outlncenter(titdat.date);
      
      if (has_author)
      {
         outln("");
         outlncenter(lang.by);
         outln("");
         outlncenter(titdat.author);
      }

      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         outln("");
         outlncenter(lang.fur);
         outln("");
         outlncenter(titdat.company);
      }

      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               outlncenter(titdat.address[i]);
            }
         }
      }
      
      if (has_translator)
      {
         outln("");
         outlncenter(lang.translator);
         outln("");
         outlncenter(titdat.translator);
      }

      if (has_distributor)
      {
         outln("");
         outlncenter(lang.distributor);
         outln("");
         outlncenter(titdat.distributor);
      }

      outln("");
      
      if (uses_tableofcontents)
      {
         outln("");
         outlncenter(lang.contents);
      }
      
      outln("@endnode");
      outln("");
      break;

   case TOPCH:                            /* PC-Help */
      /* Titelseite erfolgt bei PC-HELP bei tableofcontents... */
      break;

   case TODRC:                            /* */
      n[0] = EOS;
      
      if (has_title)
      {
         strcat(n, titdat.title);
         strcat(n, " ");
      }
      
      if (has_program)
      {
         strcat(n, titdat.program);
      }
      
      del_whitespaces(n);
      
      if (n[0] == EOS)
      {
         strcpy(n, lang.unknown);
      }
      
      voutlnf("%%%% 1, %s", n);

      /*r6pl5: Eigene Titelseitenroutine, damit die Zentrierung klappt */
      if (has_title)
      {
         outlncenterfill(titdat.title);
         outln("");
      }
      
      if (has_program)
      {
         outlncenterfill(titdat.program);
         outln("");
      }
      
      if (has_version)
         outlncenterfill(titdat.version);
      
      if (has_date)
         outlncenterfill(titdat.date);

      if (has_author)
      {
         outln("");
         outlncenterfill(lang.by);
         outln("");
         outlncenterfill(titdat.author);
      }

      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         outln("");
         outlncenterfill(lang.fur);
         outln("");
         outlncenterfill(titdat.company);
      }

      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               outlncenterfill(titdat.address[i]);
            }
         }
         
         outln("");
      }
      
      if (has_translator)
      {
         outln("");
         outlncenterfill(lang.translator);
         outln("");
         outlncenterfill(titdat.translator);
      }

      if (has_distributor)
      {
         outln("");
         outlncenterfill(lang.distributor);
         outln("");
         outlncenterfill(titdat.distributor);
      }

      outln("");
      break;

   case TOASC:                            /* ASCII */
   case TOMAN:                            /* */
      if (has_title)
      {
         outlncenter(titdat.title);
         outln("");
      }
      
      if (has_program)
      {
         outlncenter(titdat.program);
         outln("");
      }
      
      if (has_version)
         outlncenter(titdat.version);
      
      if (has_date)
         outlncenter(titdat.date);
      
      if (has_author)
      {
         outln("");
         outlncenter(lang.by);
         outln("");
         outlncenter(titdat.author);
      }

      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         outln("");
         outlncenter(lang.fur);
         outln("");
         outlncenter(titdat.company);
      }
      
      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               outlncenter(titdat.address[i]);
            }
         }
         
         outln("");
      }
      
      if (has_translator)
      {
         outln("");
         outlncenter(lang.translator);
         outln("");
         outlncenter(titdat.translator);
      }
      
      if (has_distributor)
      {
         outln("");
         outlncenter(lang.distributor);
         outln("");
         outlncenter(titdat.distributor);
      }
      
      outln("");
      outln("");
      
      if (desttype == TOMAN)
      {
         c_newpage();
      }
      
      break;

   case TOSRC:                            /* */
   case TOSRP:                            /* */
      memset(n, '#', 62);
      n[62] = EOS;
      voutlnf("%s  %s", sSrcRemOn, n);
      
      if (has_title)
      {
         strcpy(s1, titdat.title);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
         outln("    #");
      }
      
      if (has_program)
      {
         strcpy(s1, titdat.program);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
         outln("    #");
      }
      
      if (has_version)
      {
         strcpy(s1, titdat.version);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
      }
      
      if (has_date)
      {
         strcpy(s1, titdat.date);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
      }
      
      if (has_author)
      {
         outln("    #");
         
/* YYY fd:20071108: the next output should be localized! */
         strcpy(s1, "Copyright (C) by");
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
         outln("    #");
         strcpy(s1, titdat.author);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
      }
      
      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         outln("    #");
         strcpy(s1, lang.fur);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
         outln("    #");
         strcpy(s1, titdat.company);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
      }

      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               strcpy(s1, titdat.address[i]);
               stringcenter(s1, 60);
               voutlnf("    # %s", s1);
            }
         }
         
         outln("    #");
      }
      
      if (has_translator)
      {
         outln("    #");
         strcpy(s1, lang.translator);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
         outln("    #");
         strcpy(s1, titdat.translator);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
      }

      if (has_distributor)
      {
         outln("    #");
         strcpy(s1, lang.distributor);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
         outln("    #");
         strcpy(s1, titdat.distributor);
         stringcenter(s1, 60);
         voutlnf("    # %s", s1);
      }

      voutlnf("    %s %s", n, sSrcRemOff);
      break;

   case TORTF:                            /* RTF */
      outln(rtf_par);
      outln("\\qc ");
      
      if (has_title)
      {
         voutlnf("{\\fs%d %s}%s%s", iDocPropfontSize + 14, titdat.title, rtf_par, rtf_par);
      }
      
      if (has_program)
      {
         voutlnf("{\\fs%d %s}%s%s", iDocPropfontSize + 38, titdat.program, rtf_par, rtf_par);
      }
      
      if (has_version)
      {
         voutlnf("{\\fs%d %s}%s", iDocPropfontSize + 6, titdat.version, rtf_par);
      }
      
      if (has_date)
      {
         voutlnf("{\\fs%d %s}%s", iDocPropfontSize + 6, titdat.date, rtf_par);
      }
      
      if (has_author || has_address)
      {
         /* New in V6.5.2 [NHz] */
         if (has_company)
            for (i = 0; i < (22 - address_counter); i++)
               out(rtf_par);
         else
            for (i = 0; i < (25 - address_counter); i++)
               out(rtf_par);
               
         outln(rtf_par);
      }
      
      if (has_author)
      {
         voutlnf("%s%s%s", lang.by, rtf_par, rtf_par);
         voutlnf("%s%s", titdat.author, rtf_par);
      }
      
      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         auto_quote_chars(lang.fur, FALSE);
         voutlnf("%s %s%s%s", rtf_par, lang.fur, rtf_par, rtf_par);
         voutlnf("%s%s", titdat.company, rtf_par);
      }
      
      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               voutlnf("%s%s", titdat.address[i], rtf_par);
            }
         }
      }
      
      if (has_translator)
      {
         auto_quote_chars(lang.translator, FALSE);
         voutlnf("%s %s%s%s", rtf_par, lang.translator, rtf_par, rtf_par);
         voutlnf("%s%s", titdat.translator, rtf_par);
      }
      
      if (has_distributor)
      {
         auto_quote_chars(lang.distributor, FALSE);
         voutlnf("%s %s%s%s", rtf_par, lang.distributor, rtf_par, rtf_par);
         voutlnf("%s%s", titdat.distributor, rtf_par);
      }
      
      outln("\\ql");
      outln("\\page");
      break;

   case TOWIN:                            /* */
   case TOWH4:                            /* */
      check_endnode();

      outln("");              
      outln("{");     
      voutlnf("#{\\footnote # %s}", WIN_TITLE_NODE_NAME);
      voutlnf("${\\footnote $ %s}", lang.title);
      voutlnf("K{\\footnote K %s}", lang.title);
      
      if (!no_buttons)        /* r6pl8 */
      {
         outln(win_browse);
         outln("!{\\footnote ! DisableButton(\"BTN_UP\") }");
      }

      if (has_title)
      {
         voutlnf("\\qc{\\fs%d %s}\\par\\pard", iDocPropfontSize + 6, titdat.title);
      }

      if (has_programimage)
      {
         outln("\\par");
         c_begin_center();
         c_bmp_output(titdat.programimage, "", FALSE);
         c_end_center();
      }
      
      if (has_program)
      {
         voutlnf("\\qc{\\fs%d %s}\\par\\pard", iDocPropfontSize + 26, titdat.program);
      }
      
      if (has_version)
         voutlnf("\\qc{%s}\\par\\pard", titdat.version);
      
      if (has_date)
         voutlnf("\\qc{%s}\\par\\pard", titdat.date);
      
      if (has_author || has_authorimage)
      {
         voutlnf("\\par\\qc{%s}\\par\\pard", lang.by);
      }

      if (has_authorimage)
      {
         outln("\\par");
         c_begin_center();
         c_bmp_output(titdat.authorimage, "", FALSE);
         c_end_center();
      }

      if (has_author)
      {
         voutlnf("\\qc{%s}\\par\\pard", titdat.author);
      }

      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         auto_quote_chars(lang.fur, FALSE);
         voutlnf("\\par\\qc{%s}\\par\\pard", lang.fur);
         voutlnf("\\qc{%s}\\par\\pard", titdat.company);
      }

      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               voutlnf("\\qc{%s}\\par\\pard", titdat.address[i]);
            }
         }
      }

      if (has_translator)
      {
         auto_quote_chars(lang.translator, FALSE);
         voutlnf("\\par\\qc{%s}\\par\\pard", lang.translator);
         voutlnf("\\qc{%s}\\par\\pard", titdat.translator);
      }

      if (has_distributor)
      {
         auto_quote_chars(lang.distributor, FALSE);
         voutlnf("\\par\\qc{%s}\\par\\pard", lang.distributor);
         voutlnf("\\qc{%s}\\par\\pard", titdat.distributor);
      }

      outln("\\par\\par");
      
      if (uses_tableofcontents)
      {
         node2NrWinhelp(n, 0);
         voutlnf("\\qc{{\\uldb %s}{\\v %s}}\\par\\pard", lang.contents, n);
      }
      
      outln("}\\page");
      break;
      
   case TOAQV:                            /* */
      check_endnode();

      outln("");              
      outln("{");     
      voutlnf("#{\\footnote # %s}", WIN_TITLE_NODE_NAME);
      voutlnf("${\\footnote $ %s}", lang.title);
      voutlnf("K{\\footnote K %s}", lang.title);

      if (!no_buttons)        /* r6pl8 */
      {
         outln(win_browse);
         outln("!{\\footnote ! DisableButton(\"BTN_UP\") }");
      }

      if (has_title)
      {
         voutlnf("\\qc %s\\par\\pard\\par", titdat.title);
      }

      if (has_programimage)
      {
         outln("\\par");
         c_begin_center();
         c_bmp_output(titdat.programimage, "", FALSE);
         c_end_center();
      }
      
      if (has_program)
      {
         voutlnf("\\qc\\fs%d %s\\par\\pard\\plain", iDocPropfontSize + 26, titdat.program);
      }

      if (has_version)
         voutlnf("\\qc %s\\par\\pard", titdat.version);
         
      if (has_date)
         voutlnf("\\qc %s\\par\\pard", titdat.date);
         
      if (has_author || has_authorimage)
      {
         voutlnf("\\par\\qc %s\\par\\pard", lang.by);
      }

      if (has_authorimage)
      {
         outln("\\par");
         c_begin_center();
         c_bmp_output(titdat.authorimage, "", FALSE);
         c_end_center();
      }

      if (has_author)
      {
         voutlnf("\\qc %s\\par\\pard", titdat.author);
      }
      
      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         auto_quote_chars(lang.fur, FALSE);
         voutlnf("\\par\\qc %s\\par\\pard", lang.fur);
         voutlnf("\\qc %s\\par\\pard", titdat.company);
      }
      
      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               voutlnf("\\qc %s\\par\\pard", titdat.address[i]);
            }
         }
      }

      if (has_translator)
      {
         auto_quote_chars(lang.translator, FALSE);
         voutlnf("\\par\\qc %s\\par\\pard", lang.translator);
         voutlnf("\\qc %s\\par\\pard", titdat.translator);
      }
      
      if (has_distributor)
      {
         auto_quote_chars(lang.distributor, FALSE);
         voutlnf("\\par\\qc %s\\par\\pard", lang.distributor);
         voutlnf("\\qc %s\\par\\pard", titdat.distributor);
      }
      
      outln("\\par\\par");
         
      if (uses_tableofcontents)
      {
         voutlnf("\\qc {\\uldb %s}{\\v %s}\\par\\pard", lang.contents, lang.contents);
      }
         
      outln("}\\page");
      break;
         
   case TOHAH:                            /* Apple-Help (HTML); New in V6.5.17 */
   case TOHTM:                            /* HTML */
   case TOMHH:                            /*        ; New in V6.5.9 [NHz] */
      outln("<div id=\"udo_titlepage\">");

      if (has_title)
      {
         if (html_doctype == HTML5)
         {
            voutlnf("<h2 class=\"UDO_h2_align_center\">%s</h2>", titdat.title);
         }
         else
         {
            voutlnf("<h2 align=\"center\">%s</h2>", titdat.title);
         }
      }

      if (has_programimage)
      {
         c_begin_center();
         c_html_image_output(titdat.programimage, "", sDocImgSuffix, 0);
         c_end_center();
      }
      
      if (has_program)
      {
         if (html_doctype == HTML5)
         {
            voutlnf("<h1 class=\"UDO_h1_align_center\">%s</h1>", titdat.program);
         }
         else
         {
            voutlnf("<h1 align=\"center\">%s</h1>", titdat.program);
         }
      }
      
      if (has_version || has_date || has_author || has_address)
      {
         if (html_doctype == HTML5)
         {
            outln("<p class=\"UDO_p_align_center\">");
         }
         else
         {
            outln("<p align=\"center\">");
         }
      }
      
      if (has_version)
      {
         voutlnf("%s<br%s>", titdat.version, closer);
      }
      
      if (has_date)
      {
         voutlnf("%s<br%s>", titdat.date, closer);
      }
      
      if (has_author || has_authorimage)
      {
         voutlnf("<br%s>%s<br%s>", closer, lang.by, closer);
      }
      
      if (has_authorimage)
      {
         c_begin_center();
         c_html_image_output(titdat.authorimage, "", sDocImgSuffix, 0);
         c_end_center();
         
         if (has_author || has_address)
         {
            if (html_doctype == HTML5)
            {
               outln("<p class=\"UDO_p_align_center\">");
            }
            else
            {
               outln("<p align=\"center\">");
            }
         }
      }
      
      if (has_author)
      {
         voutlnf("%s<br%s>", titdat.author, closer);
      }

      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         auto_quote_chars(lang.fur, FALSE);
         voutlnf("<br%s>%s<br%s>", closer, lang.fur, closer);
         voutlnf("%s<br%s>", titdat.company, closer);
      }

      if (has_address)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               voutlnf("%s<br%s>", titdat.address[i], closer);
            }
         }
      }

      if (has_translator)
      {
         auto_quote_chars(lang.translator, FALSE);
         voutlnf("<br%s>%s<br%s>", closer, lang.translator, closer);
         voutlnf("%s<br%s>", titdat.translator, closer);
      }

      if (has_distributor)
      {
         auto_quote_chars(lang.distributor, FALSE);
         voutlnf("<br%s>%s<br%s>", closer, lang.distributor, closer);
         voutlnf("%s<br%s>", titdat.distributor, closer);
      }

      if (has_version || has_date || has_author || has_address || has_translator || has_distributor)
      {
         outln("<p>");
      }

      if (uses_tableofcontents)
      {
         if (html_doctype < XHTML_STRICT)
            outln(HTML_HR);
         else
            outln(XHTML_HR);
      }

      /* New in V6.5.9 [NHz] */
      outln("</div>");

      break;

   case TOTVH:                            /* */
      outln("");
      voutlnf(".topic %s=0", lang.title);
      outln("");

      if (has_title)
      {
         outlncenter(titdat.title);
         outln("");
      }

      if (has_program)
      {
         outlncenter(titdat.program);
         outln("");
      }

      if (has_version)
         outlncenter(titdat.version);
      
      if (has_date)
         outlncenter(titdat.date);
      
      if (has_author)
      {
         outln("");
         outlncenter(lang.by);
         outln("");
         outlncenter(titdat.author);
      }

      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         outln("");
         outlncenter(lang.fur);
         outln("");
         outlncenter(titdat.company);
      }

      if (address_counter>0)
      {
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               outlncenter(titdat.address[i]);
            }
         }
      }

      if (has_translator)
      {
         outln("");
         outlncenter(lang.translator);
         outln("");
         outlncenter(titdat.translator);
      }

      if (has_distributor)
      {
         outln("");
         outlncenter(lang.distributor);
         outln("");
         outlncenter(titdat.distributor);
      }

      outln("");
      outln("");

      if (uses_tableofcontents)
      {
         sprintf(s1, "%s", lang.contents);       /* PL10: Leerzeichen davor */
         sprintf(s2, "{%s:%s}", lang.contents, lang.contents);
         strcpy(n, lang.contents);
         strcenter(n, zDocParwidth);
         replace_once(n, s1, s2);
         outln(n);
      }

      outln("");
      break;

   /* New in r6pl15 [NHz] */
   /* Title-Page for Postscript */
   case TOKPS:                            /* */
      outln("/acty acty 50 sub def");
      outln("newline");
      
      if (has_title)
      {
         outln("14 changeFontSize");
         voutlnf("(%s) Center setAlign", titdat.title);
      }
      
      if (has_program)
      {
         outln("22 changeFontSize");
         outln("newline");
         voutlnf("(%s) Center setAlign", titdat.program);
      }
      
      if (has_version)
      {
         outln("14 changeFontSize");
         outln("newline");
         voutlnf("(%s) Center setAlign", titdat.version);
      }
      
      if (has_date)
      {
         outln("newline");
         voutlnf("(%s) Center setAlign", titdat.date);
         outln("11 changeFontSize");
      }
      
      if (has_author)
      {
         outln("currentpoint exch pop lowermargin 125 add lt");
         outln("{");
         outln("  /acty lowermargin 125 add def");
         outln("}");
         outln("{");
         outln("  /acty lowermargin 200 add def");
         outln("} ifelse");
         outln("newline");
         voutlnf("(%s) Center setAlign newline", lang.by);
         voutlnf("(%s) Center setAlign", titdat.author);
      }
      
      /* New in V6.5.2 [NHz] */
      if (has_company)
      {
         outln("newline");
         auto_quote_chars(lang.fur, FALSE);
         voutlnf("(%s) Center setAlign newline", lang.fur);
         voutlnf("(%s) Center setAlign", titdat.company);
      }
      
      if (has_address)
      {
         outln("newline");
         for (i = 1; i <= address_counter; i++)
         {
            if (titdat.address[i] != NULL)
            {
               voutlnf("(%s) Center setAlign newline", titdat.address[i]);
            }
         }
         
         outln("newline");
      }
      
      if (has_translator)
      {
         outln("newline");
         auto_quote_chars(lang.translator, FALSE);
         voutlnf("(%s) Center setAlign newline", lang.translator);
         voutlnf("(%s) Center setAlign", titdat.translator);
      }
      
      if (has_distributor)
      {
         outln("newline");
         auto_quote_chars(lang.distributor, FALSE);
         voutlnf("(%s) Center setAlign newline", lang.distributor);
         voutlnf("(%s) Center setAlign", titdat.distributor);
      }
      
      c_newpage();
      
      /* New: Fixed bug #0000040 in r6.3pl16 [NHz] */
      outln("newline");
      break;

   }  /* switch (desttype) */
}





/*******************************************************************************
*
*  pch_titlepage():
*     output title page for Pure C Help
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void pch_titlepage(void)
{
   int   i;  /* counter */
   

   if (titdat.title != NULL)
   {
      outlncenter(titdat.title);
      outln("");
   }

   if (titdat.program != NULL)
   {
      outlncenter(titdat.program);
      outln("");
   }

   if (titdat.version != NULL)
   {
      outlncenter(titdat.version);
   }

   if (titdat.date != NULL)
   {
      outlncenter(titdat.date);
   }

   if (titdat.author != NULL)
   {
      outln("");
      outlncenter(lang.by);
      outln("");
      outlncenter(titdat.author);
   }

   if (titdat.company != NULL)            /* New in V6.5.2 [NHz] */
   {
      outln("");
      outlncenter(lang.fur);
      outln("");
      outlncenter(titdat.company);
   }

   if (address_counter > 0)
   {
      for (i = 1; i <= address_counter; i++)
      {
         if (titdat.address[i] != NULL)
         {
            outlncenter(titdat.address[i]);
         }
      }
   }

   if (titdat.translator != NULL)
   {
      outln("");
      outlncenter(lang.translator);
      outln("");
      outlncenter(titdat.translator);
   }

   if (titdat.distributor != NULL)
   {
      outln("");
      outlncenter(lang.distributor);
      outln("");
      outlncenter(titdat.distributor);
   }

   outln("");
}





/*******************************************************************************
*
*  init_titdat():
*     initialize this module (tp)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_titdat(void)
{
   int   i;  /* counter */


   titdat.title   = NULL;
   titdat.program = NULL;
   titdat.date    = NULL;
   titdat.version = NULL;
   titdat.author  = NULL;

   for (i = 0; i < MAXADDRESS; i++)
   {
      titdat.address[i] = NULL;
   }

   titdat.keywords               = NULL;  /* New in r6pl15 [NHz] */
   titdat.description            = NULL;  /* New in r6pl15 [NHz] */
   titdat.robots                 = NULL;  /* New in V6.5.17 */
   titdat.company                = NULL;  /* New in V6.5.2 [NHz] */
   titdat.category               = NULL;  /* New in V6.5.2 [NHz] */
   titdat.htmltitle              = NULL;
   titdat.domain_name            = NULL;
   titdat.domain_link            = NULL;
   titdat.contact_name           = NULL;
   titdat.contact_link           = NULL;
   titdat.programimage           = NULL;
   titdat.appletitle             = NULL;  /* V6.5.17 */
   titdat.appleicon              = NULL;  /* V6.5.17 */
   titdat.authorimage            = NULL;
   titdat.authoricon             = NULL;
   titdat.authoricon_active      = NULL;
   titdat.authoriconWidth        = 0;
   titdat.authoriconHeight       = 0;
   titdat.authoriconActiveWidth  = 0;
   titdat.authoriconActiveHeight = 0;

   titdat.drc_statusline         = NULL;
   titdat.stg_database           = NULL;
   titdat.translator             = NULL;
   titdat.distributor            = NULL;
}





/*******************************************************************************
*
*  init_module_tp():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_tp(void)
{
   uses_maketitle   = FALSE;
   called_maketitle = FALSE;
   address_counter  = 0;

   titleprogram[0]  = EOS;

   init_titdat();
}





/*******************************************************************************
*
*  init_module_tp_pass2():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_tp_pass2(void)
{
   titleprogram[0] = EOS;

   if (titdat.title != NULL)
   {
      strcat(titleprogram, titdat.title);
      strcat(titleprogram, " ");
   }

   if (titdat.program != NULL)
   {
      strcat(titleprogram, titdat.program);
   }

   del_whitespaces(titleprogram);
}





/*******************************************************************************
*
*  free_titdat():
*     reset all content of titdat[]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void free_titdat(

char **var)  /* ^^ to string in titdat.[] */
{
   if (*var != NULL)
   {
      um_free(*var);
      *var = NULL;
   }
}





/*******************************************************************************
*
*  exit_module_tp():
*     reset all content of titdat.[]
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void exit_module_tp(void)
{
   int   i;  /* */


   free_titdat(&(titdat.title));
   free_titdat(&(titdat.program));
   free_titdat(&(titdat.date));
   free_titdat(&(titdat.version));
   free_titdat(&(titdat.author));  

   for (i = address_counter; i >= 1; i--)
   {
      free_titdat(&(titdat.address[i]));
   }

   free_titdat(&(titdat.keywords));       /* New in r6pl15 [NHz] */
   free_titdat(&(titdat.description));    /* New in r6pl15 [NHz] */
   free_titdat(&(titdat.company));        /* New in V6.5.2 [NHz] */
   free_titdat(&(titdat.category));       /* New in V6.5.2 [NHz] */
   free_titdat(&(titdat.htmltitle));
   free_titdat(&(titdat.domain_name));
   free_titdat(&(titdat.domain_link));
   free_titdat(&(titdat.contact_name));
   free_titdat(&(titdat.contact_link));
   free_titdat(&(titdat.programimage));
   free_titdat(&(titdat.authorimage));
   free_titdat(&(titdat.authoricon));
   free_titdat(&(titdat.authoricon_active));

   free_titdat(&(titdat.drc_statusline));  
   free_titdat(&(titdat.stg_database));    
   free_titdat(&(titdat.translator));    
   free_titdat(&(titdat.distributor));    
}


/* +++ EOF +++ */
