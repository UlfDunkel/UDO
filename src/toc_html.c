/**(TAB=0)**********************************************************************
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
*  2011:
*    fd  Feb 14: - all set_html_...() functions moved from TOC to TOC_HTML
*                - functions tidied up
*  2013:
*    fd  Oct 23: set_html_doctype() now knows HTML5
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "udoport.h"
#include "constant.h"
#include "udo_type.h"
#include "chr.h"
#include "file.h"
#include "msg.h"
#include "par.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"

#include "export.h"
#include "udomem.h"








/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

   /* check if certain values are valid */
LOCAL _BOOL check_toc_and_counters(void);










/*******************************************************************************
*
*     LOCAL PROCEDURES
*
******************************************|************************************/

/*******************************************************************************
*
*  check_toc_and_counters():
*     check if certain values are valid
*
*  Return:
*     FALSE: any checked value was invalid
*      TRUE: everything's fine
*
******************************************|************************************/

LOCAL _BOOL check_toc_and_counters(void)
{
   if (p1_toc_counter < 0)
      return FALSE;
      
   if (toc[p1_toc_counter] == NULL)
      return FALSE;
      
   if (token[1][0] == EOS)
      return FALSE;
   
   return TRUE;
}










/*******************************************************************************
*
*     GLOBAL PROCEDURES
*
******************************************|************************************/

/*******************************************************************************
*
*  set_html_navigation():
*     creates the navigation bar for HTML output
*
*  Note:
*     All data are found in token[].
*
*  Return:
*     TRUE  = OK
*     else  = error
*
******************************************|************************************/

GLOBAL _BOOL set_html_navigation(void)
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





/*******************************************************************************
*
*  set_html_doctype():
*     sets the variable html_doctype
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_doctype(void)
{
   char   s[512];  /* string buffer */


   tokcpy2(s, 512);

   if (strcmp(s, "5") == 0)
      html_doctype = HTML5;

   if (strcmp(s, "Old") == 0)
      html_doctype = HTML_OLD;

   if (strcmp(s, "Strict") == 0)
      html_doctype = HTML_STRICT;

   if (strcmp(s, "Transitional") == 0)
      html_doctype = HTML_TRANS;

   if (strcmp(s, "XHTML Strict") == 0)
      html_doctype = XHTML_STRICT;

   if (strcmp(s, "XHTML Transitional") == 0)
      html_doctype = XHTML_TRANS;

}





/*******************************************************************************
*
*  set_html_header_date():
*     sets HTML header date
*
*  Note:
*     New feature #0000054 in V6.5.2 [NHz]
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_header_date(void)
{
   tokcpy2(html_header_date_zone, 9);

   if (    (    (html_header_date_zone[0] != '+') 
             && (html_header_date_zone[0] != '-')
           )
        || isdigit(html_header_date_zone[1] == 0) 
        || isdigit(html_header_date_zone[2] == 0)
        || html_header_date_zone[3] != ':'
        || isdigit(html_header_date_zone[4] == 0) 
        || isdigit(html_header_date_zone[5] == 0)
      )
   {
      error_wrong_header_date(html_header_date_zone);
      return;
   }

   html_header_date = TRUE;
}





/*******************************************************************************
*
*  set_html_header_links():
*     sets html_header_links variable
*
*  Note:
*     New feature #0000053 in V6.5.2 [NHz]
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_header_links(void)
{
   char  *kind;  /* */
                 /* */
   char   possible[] = "navigation chapter";


   tokcpy2(html_header_links_kind, 40);

   if (html_header_links_kind[0] == EOS)
   {
      error_empty_header_links();
      return;
   }

   kind = strtok(html_header_links_kind, " ");
   
   while (kind != NULL)
   {
      if (strstr(possible, kind) == NULL)
         error_argument_header_links(kind);
         
      kind = strtok(NULL, " ");
   }

   tokcpy2(html_header_links_kind, 40);
   html_header_links = TRUE;
}





/*******************************************************************************
*
*  set_html_frames_layout():
*     sets various html_frames_... flags
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_frames_layout(void)
{
   char   s[512];  /* string buffer */


   html_frames_layout = TRUE;

   tokcpy2(s, 512);

   if (strstr(s, "noresize=\"noresize\"") != NULL)
      html_frames_noresize = TRUE;

   if (strstr(s, "noborder") != NULL)
      html_frames_noborder = TRUE;

   if (strstr(s, "noscrolling") != NULL)
      html_frames_noscroll = TRUE;
}





/*******************************************************************************
*
*  set_html_filename():
*     sets HTML filename
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_filename(void)
{
   char  *ptr;  /* */


   switch (desttype)                      /* !html_name is used in HTML and HTML-Help output */
   {
   case TOHTM:
   case TOMHH:
   case TOHAH:                            /* new: Apple Help; v6.5.17 */
      break;
   
   default:
      return;
   }
   
   if (!check_toc_and_counters())
      return;

   fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);

   ptr = toc[p1_toc_counter]->filename;
   ptr[0] = EOS;
                                          /* Nur den Dateinamen benutzen, nicht den Pfad! */
   strncat(ptr, tmp_name, MAX_FILENAME_LEN);

   if (strcmp(tmp_suff, ""))
      strncat(ptr, tmp_suff, 6);
}





/*******************************************************************************
*
*  set_html_filename_prefix():
*     sets HTML name prefix
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_filename_prefix(void)
{
   switch (desttype)
   {
   case TOHTM:
   case TOHAH:
      break;
   
   default:
      return;
   }

   if (!check_toc_and_counters())
      return;

   um_strcpy(html_name_prefix, token[1], 512, "set_html_filename_prefix[1]");
}




/*******************************************************************************
*
*  set_html_dirname():
*     sets HTML dirname variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_dirname(void)
{
   char  *ptr;  /* */
   

   switch (desttype)
   {
   case TOHTM:
   case TOHAH:
      break;
   
   default:
      return;
   }

   if (!check_toc_and_counters())
      return;

   fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);

   if (tmp_path[0] == EOS && tmp_name[0] != EOS)
      strcpy(tmp_path, tmp_name);

   if (tmp_path[0] != EOS)
   {
      ptr = toc[p1_toc_counter]->dirname;
      ptr[0] = EOS;
      strncat(ptr, tmp_name, MAX_FILENAME_LEN);
   }
}




/*******************************************************************************
*
*  set_html_switch_language():
*     sets ...SwitchLanguage variables
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_switch_language(void)
{
   switch (desttype)                      /* check destination format */
   {
   case TOHTM:
   case TOMHH:
   case TOHAH:
      break;
      
   default:
      return;
   }
   
   if (!check_toc_and_counters())
      return;

   iDocHtmlSwitchLanguage = -1;
   sDocHtmlSwitchLanguage[0] = EOS;

   if (strstr(token[1], "german"))
   {
      iDocHtmlSwitchLanguage = TOGER;
   }
   else if (strstr(token[1], "english"))
   {
      iDocHtmlSwitchLanguage = TOENG;
   }

   if (iDocHtmlSwitchLanguage >= 0)
   {
      token[1][0] = EOS;
      tokcpy2(sDocHtmlSwitchLanguage, 256);
   }
}





/*******************************************************************************
*
*  set_html_keywords():
*     sets HTML keywords
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_keywords(void)
{
   char      k[MAX_TOKEN_LEN],     /* */
            *ptr,                  /* */
             oldk[MAX_TOKEN_LEN],  /* */
            *oldptr;               /* */
   size_t    newsize;              /* */


   if (!check_toc_and_counters())
      return;

   tokcpy2(k, MAX_TOKEN_LEN);
   c_vars(k);
   qdelete_all(k, "!-", 2);

   auto_quote_chars(k, TRUE);
   replace_udo_quotes(k);

   if (toc[p1_toc_counter]->keywords != NULL)
   {                                      /* r6pl5: Keywords bereits vorhanden, neue anhaengen */
      oldptr = toc[p1_toc_counter]->keywords;
      
      um_strcpy(oldk, oldptr, MAX_TOKEN_LEN + 1, "\n!html_keywords too long in this line\nset_html_keywords [1]");
      
      newsize = strlen(oldk) + strlen(k) + 3;

      ptr = (char *)um_realloc(oldptr, newsize);
      
      if (!ptr)
      {
         error_malloc_failed();
         bFatalErrorDetected = TRUE;
      }
      else
      {       
         sprintf(ptr, "%s, %s", oldk, k);
         toc[p1_toc_counter]->keywords = ptr;
      }
   }
   else
   {
      ptr = (char *)um_malloc(1 + strlen(k) * sizeof(char));

      if (!ptr)
      {
         error_malloc_failed();
         bFatalErrorDetected = TRUE;
      }
      else
      {
         strcpy(ptr, k);
         toc[p1_toc_counter]->keywords = ptr;
      }
   }
}





/*******************************************************************************
*
*  set_html_description():
*     sets HTML description
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_description(void)
{
   char     d[1024],     /* */
           *ptr,         /* */
            oldd[1024],  /* */
           *oldptr;      /* */
   size_t   newsize;     /* */
   
   
   if (!check_toc_and_counters())
      return;

   tokcpy2(d, 1024);
   c_vars(d);
   qdelete_all(d, "!-", 2);

   auto_quote_chars(d, TRUE);
   replace_udo_quotes(d);

   if (toc[p1_toc_counter]->description != NULL)
   { 
                                          /* r6pl5: description bereits vorhanden, neue anhaengen */
      oldptr = toc[p1_toc_counter]->description;
      strcpy(oldd, oldptr);
      newsize = strlen(oldd) + strlen(d) + 2;

      ptr = (char *)um_realloc(oldptr, newsize);

      if (!ptr)
      {
         error_malloc_failed();
         bFatalErrorDetected = TRUE;
      }
      else
      {       
         sprintf(ptr, "%s %s", oldd, d);
         toc[p1_toc_counter]->description = ptr;
      }
   }
   else
   { 
      ptr = (char *)um_malloc(1 + strlen(d) * sizeof(char));

      if (!ptr)
      {
         error_malloc_failed();
         bFatalErrorDetected = TRUE;
      }
      else
      { 
         strcpy(ptr, d);
         toc[p1_toc_counter]->description = ptr;
      }
   }
}





/*******************************************************************************
*
*  set_html_robots():
*     sets HTML robots
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_robots(void)
{
   char   d[1024],  /* */
         *ptr;      /* */
   
   
   if (!check_toc_and_counters())
      return;

   tokcpy2(d, 1024);
   c_vars(d);
   qdelete_all(d, "!-", 2);

   auto_quote_chars(d, TRUE);
   replace_udo_quotes(d);

   if (strcmp(d, "none") != 0)
   {    
      if (strcmp(d, "noindex") != 0)
      {  
         if (strcmp(d, "index") != 0)
         {  
            if (strcmp(d, "nofollow") != 0)
            {  
               if (strcmp(d, "follow") != 0)
               {                          /* For HTML Apple Help */
                  if (strcmp(d, "keywords") != 0)
                  {                       /* For HTML Apple Help */
                     if (strcmp(d, "segments") != 0)
                     {                    /* For HTML Apple Help */
                        if (strcmp(d, "anchors") != 0)
                        {
                           error_syntax_error();
                           return;
                        }
                     }
                  }
               }
            }
         }
      }
   }

   ptr = (char *)um_malloc(1 + strlen(d) * sizeof(char));

   if (!ptr)
   {
      error_malloc_failed();
      bFatalErrorDetected = TRUE;
   }
   else
   {
      strcpy(ptr, d);
      toc[p1_toc_counter]->robots = ptr;
   }
}





/*******************************************************************************
*
*  set_html_bgsound():
*     sets the sound for a node
*
*     Only HTML
*
******************************************|************************************/

GLOBAL void set_html_bgsound(void)
{
   char  *ptr,            /* */
         *dest;           /* */
   char   filename[512];  /* */
   char   loop [40],      /* */
          sTemp[1024];    /* */
   
   
   if (desttype != TOHTM)
      return;

   if (!check_toc_and_counters())
      return;

   dest = toc[p1_toc_counter]->bgsound;

   if (token[1][0] == '\"')
   {
      tokcpy2(sTemp, 1024);
      ptr = strchr(sTemp + 1, '\"');      /* find second quote character (") */

      if (ptr)
      { 
         ptr[0] = EOS;
         strcpy(filename, sTemp + 1);
         um_strcpy(loop, ptr + 1, 40, "set_html_bgsound[1]");
         del_whitespaces(loop);
      }
      else
      {
         strcpy(filename, sTemp);
         loop[0] = EOS;
      }
   }
   else
   {
      um_strcpy(filename, token[1], 512, "set_html_bgsound[2]");
      token[1][0] = EOS;
      tokcpy2(loop, 40);
      del_whitespaces(loop);
   }

   replace_char(filename, "\\", "/");

   if (loop[0] == EOS)
      sprintf(dest, "\"%s\" loop=\"infinitive\"", filename);
   else
      sprintf(dest, "\"%s\" loop=\"%s\"", filename, loop);
}





/*******************************************************************************
*
*  set_html_backimage():
*     sets HTML backimage
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_backimage(void)
{
   char  *ptr,         /* */
         *dest;        /* */
   char   sTemp[512];  /* */
   
   
   if (!check_toc_and_counters())
      return;

   if (p1_toc_counter == 0)
      dest = sDocBackImage;
   else
      dest = toc[p1_toc_counter]->backimage;

   if (token[1][0] == '\"')
   {
      tokcpy2(sTemp, 512);
      ptr = strchr(sTemp + 1, '\"');      /* find second quote character (") */

      if (ptr)
      {
         ptr[0] = EOS;
         strcpy(dest, sTemp + 1);
      }
      else
      { 
         strcpy(dest, sTemp);
      }
   }
   else
   {
      strcpy(dest, token[1]);
   }

/* dest[0] = EOS; */
/* strncat(dest, sTemp, MAX_IMAGE_LEN); */

                                          /* Hier muessen immer / benutzt werden! */
   replace_char(dest, "\\", "/");
}





/*******************************************************************************
*
*  set_html_color():
*     sets HTML color
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_color(

const int    which)       /* */
{
   char      color[256],  /* */
            *ptr;         /* */
   _BOOL   ret;         /* */
   
   
   if (!check_toc_and_counters())
      return;

   color[0] = EOS;

   qdelete_once(token[1], "[", 1);
   qdelete_last(token[1], "]", 1);

   if (token[1][0] == '#')
   {
      um_strcpy(color, token[1], 256, "set_html_color[1]");
      ret = TRUE;
   }
   else
   { 
      ret = get_html_color(token[1], color);
   }

   if (ret)
   {
      if (p1_toc_counter == 0)
      {
         ptr = sDocBackColor;             /* default */
         
         switch (which)
         {
         case HTML_COLOR_BACK:
            ptr = sDocBackColor;   
            break;
            
         case HTML_COLOR_TEXT:
            ptr = sDocTextColor;  
            break;
            
         case HTML_COLOR_LINK:
            ptr = sDocLinkColor;   
            break;
            
         case HTML_COLOR_ALINK:
            ptr = sDocAlinkColor;  
            break;
            
         case HTML_COLOR_VLINK:
            ptr = sDocVlinkColor;  
         }
      }
      else
      {
         ptr = toc[p1_toc_counter]->backcolor;
         
         switch (which)
         {
         case HTML_COLOR_BACK:
            ptr = toc[p1_toc_counter]->backcolor; 
            break;
            
         case HTML_COLOR_TEXT:
            ptr = toc[p1_toc_counter]->textcolor;  
            break;
            
         case HTML_COLOR_LINK:
            ptr = toc[p1_toc_counter]->linkcolor;   
            break;
            
         case HTML_COLOR_ALINK:
            ptr = toc[p1_toc_counter]->alinkcolor;  
            break;
            
         case HTML_COLOR_VLINK:
            ptr = toc[p1_toc_counter]->vlinkcolor; 
         }
      }
      
      ptr[0] = EOS;

      if (color[0] != EOS)
      { 
         strncat(ptr, color, MAX_COLOR_LEN);
      }
   }
   else
   {  
      error_unknown_color(token[1]);
   }
}





/*******************************************************************************
*
*  set_html_style():
*     sets HTML style
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_style(void)
{
   STYLE  *styleptr;    /* */
   char    sTemp[512],  /* */
          *ptr;         /* */
   int     i;           /* */
   long    lang;        /* */
   
   
   if (!check_toc_and_counters())
      return;

   if (p1_style_counter + 1 >= MAXSTYLES) /* list overflow? */
   {
      error_too_many_label();
      return;
   }

   styleptr = (STYLE *)um_malloc(sizeof(STYLE) + 1);

   if (styleptr == NULL)                  /* no memory? */
   {
      error_malloc_failed();
      return;
   }

                                          /* Set style in project file (not yet) */
/* if (!isn) */                           /* Only labels which aren't nodes */
/*    save_upr_entry_label (sCurrFileName, strchr(current_node_name_sys, ' ') + 1, uiCurrFileLine); */

   p1_style_counter++;
   
   style[p1_style_counter] = styleptr;
   
   styleptr->href[0]   = EOS;
   styleptr->media[0]  = EOS;
   styleptr->title[0]  = EOS;
   styleptr->alternate = FALSE;

   tokcpy2(sTemp, 512);

   if (sTemp[0] == '\'')
   {
      lang = strcspn(sTemp + 1, "'");
      strncpy(styleptr->href, sTemp + 1, lang);
      styleptr->href[lang] = EOS;

                                          /* always use / characters here! */
      replace_char(styleptr->href, "\\", "/");
   }
   else
      strcpy(styleptr->href, token[1]);

   for (i = 1; i < p1_style_counter; i++) /* check if this CSS file has already been included */
   {
      if (!strcmp(styleptr->href, style[i]->href))
      {
         p1_style_counter--;
         return;
      }
   }

   ptr = strstr(sTemp, "media=");
   
   if (ptr != NULL)
   {
      lang = strcspn(ptr + 6, " \0");
      strncpy(styleptr->media, ptr + 6, lang);
      styleptr->media[lang] = EOS;
   }
   
   ptr = strstr(sTemp, "title=");
   
   if (ptr != NULL)
   {
      if (strchr(ptr + 6, '\''))
      {
         lang = strcspn(ptr + 7, "'");
         strncpy(styleptr->title, ptr + 7, lang);
      }
      else
      {
         lang = strcspn(ptr + 6, " \0");
         strncpy(styleptr->title, ptr + 6, lang);
      }

      styleptr->title[lang] = EOS;
   }

   ptr = strstr(sTemp, "alternate");

   if (ptr != NULL)
      styleptr->alternate = TRUE;
   else
      styleptr->alternate = FALSE;

   styleptr->styleindex = p1_style_counter;
   styleptr->tocindex   = p1_toc_counter;
}





/*******************************************************************************
*
*  set_html_script():
*     sets HTML script (usually a JavaScript file)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_script(void)
{
   SCRIPT  *scriptptr;   /* */
   char     sTemp[512];  /* */
   int      i;           /* */
   long     lang;        /* */
   
   
   if (!check_toc_and_counters())
      return;

                                          /* list overflow? */
   if (p1_script_counter + 1 >= MAXSCRIPTS)
   {
      error_too_many_label();
      return;
   }

   scriptptr = (SCRIPT *)um_malloc(sizeof(SCRIPT) + 1);

   if (scriptptr == NULL)                 /* no memory? */
   {
      error_malloc_failed();
      return;
   }

   p1_script_counter++;
   
   script[p1_script_counter] = scriptptr;
   
   scriptptr->href[0] = EOS;

   tokcpy2(sTemp, 512);

   if (sTemp[0] == '\'')
   {
      lang = strcspn(sTemp + 1, "'");
      strncpy(scriptptr->href, sTemp + 1, lang);
      scriptptr->href[lang] = EOS;

                                          /* always use / characters here! */
      replace_char(scriptptr->href, "\\", "/");
   }
   else
      strcpy(scriptptr->href, token[1]);

   for (i = 1; i < p1_script_counter; i++) /* check if this CSS file has already been included */
   {
      if (!strcmp(scriptptr->href, script[i]->href))
      {
         p1_script_counter--;
         return;
      }
   }

   scriptptr->scriptindex = p1_script_counter;
   scriptptr->tocindex    = p1_toc_counter;
}





/*******************************************************************************
*
*  set_html_favicon():
*     sets HTML favicon
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_favicon(void)
{
   char  *ptr,         /* */
         *dest;        /* */
   char   sTemp[512];  /* */
   
   
   if (!check_toc_and_counters())
      return;

   if (p1_toc_counter == 0)
      dest = sDocFavIcon;
   else
      dest = toc[p1_toc_counter]->favicon_name;


   if (token[1][0] == '\"')
   {
      tokcpy2(sTemp, 512);
      ptr = strchr(sTemp + 1, '\"');      /* find second quote character (") */

      if (ptr)
      {  
         ptr[0] = EOS;
         strcpy(dest, sTemp + 1);
      }
      else
      {
         strcpy(dest, sTemp);
      }
   }
   else
   {
      strcpy(dest, token[1]);
   }

/* dest[0] = EOS; */
/* strncat(dest, sTemp, MAX_IMAGE_LEN); */

                                          /* Hier muessen immer / benutzt werden! */
   replace_char(dest, "\\", "/");
}





/*******************************************************************************
*
*  set_html_special_color():
*     sets special color for HTML
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_special_color(

char        *hc)          /* */
{
   char      color[256];  /* */
   _BOOL   ret;         /* */
   
   
   if (!check_toc_and_counters())
      return;

   color[0] = EOS;

   qdelete_once(token[1], "[", 1);
   qdelete_last(token[1], "]", 1);

   if (token[1][0] == '#')
   { 
      um_strcpy(color, token[1], 256, "set_html_special_color [1]");
      ret = TRUE;
   }
   else
   {  
      ret = get_html_color(token[1], color);
   }

   if (ret)
   { 
      hc[0] = EOS;
      
      if (color[0] != EOS)
      { 
         strncat(hc, color, MAX_COLOR_LEN);
      }
   }
   else
   { 
      error_unknown_color(token[1]);
   }
}





/*******************************************************************************
*
*  set_html_counter_command():
*     sets counter_command
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_counter_command(void)
{
   char   k[512],  /* */
         *ptr;     /* */
   
   
   if (!check_toc_and_counters())
      return;

   tokcpy2(k, 512);

   if (p1_toc_counter == 0)
   {
      strcpy(sCounterCommand, k);
      return;
   }

   ptr = (char *)um_malloc(1 + strlen(k) * sizeof(char));

   if (!ptr)
   {
      error_malloc_failed();
      bFatalErrorDetected = TRUE;
   }
   else
   { 
      strcpy(ptr, k);
      toc[p1_toc_counter]->counter_command = ptr;
   }
}





/*******************************************************************************
*
*  set_html_frames_toc_title():
*     sets html_frames_toc_title variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_frames_toc_title(void)
{
   char   d[1024],  /* */
         *ptr;      /* */
   
   
   tokcpy2(d, 1024);
   c_vars(d);
   qdelete_all(d, "!-", 2);

   auto_quote_chars(d, TRUE);
   replace_udo_quotes(d);

   if (html_frames_toc_title != NULL)
      um_free(html_frames_toc_title);

   ptr = (char *)um_malloc(1 + strlen(d) * sizeof(char));

   if (!ptr)
   { 
      error_malloc_failed();
      bFatalErrorDetected = TRUE;
   }
   else
   {  
      strcpy(ptr, d);
      html_frames_toc_title = ptr;
   }
}





/*******************************************************************************
*
*  set_html_frames_con_title():
*     sets html_frames_con_title variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_frames_con_title(void)
{
   char   d[1024],  /* */
         *ptr;      /* */
   
   
   tokcpy2(d, 1024);
   c_vars(d);
   qdelete_all(d, "!-", 2);

   auto_quote_chars(d, TRUE);
   replace_udo_quotes(d);

   if (html_frames_con_title != NULL)
      um_free(html_frames_con_title);

   ptr = (char *)um_malloc(1 + strlen(d) * sizeof(char));

   if (!ptr)
   { 
      error_malloc_failed();
      bFatalErrorDetected = TRUE;
   }
   else
   {  
      strcpy(ptr, d);
      html_frames_con_title = ptr;
   }
}





/*******************************************************************************
*
*  set_html_modern_width():
*     sets html_modern_width variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_modern_width(void)
{
   int   width;  /* */
   
   
   if (!check_toc_and_counters())
      return;

                                          /*r6pl8: Falls z.B. 30%, dann komplett umkopieren */
   if (strstr(token[1], "%") != NULL)
   {
      um_strcpy(html_modern_width, token[1], 16, "set_html_modern_width[1]");
   }
   else
   {
      width = atoi(token[1]);
      
      if (width < 0)
         width = 128;
         
      sprintf(html_modern_width, "%d", width);
   }
}





/*******************************************************************************
*
*  set_html_modern_alignment():
*     sets html_modern_alignment variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_modern_alignment(void)
{
   char   s[256];  /* buffer for parameter string */
   
   
   tokcpy2(s, 256);

   if (strstr(s, "center") != NULL)
   {
      html_modern_alignment = ALIGN_CENT;
      return;
   }

   if (strstr(s, "left") != NULL)
   {
      html_modern_alignment = ALIGN_LEFT;
      return;
   }

   if (strstr(s, "right") != NULL)
   { 
      html_modern_alignment = ALIGN_RIGH;
      return;
   }
}





/*******************************************************************************
*
*  set_html_modern_backimage():
*     sets html_modern_backimage variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_modern_backimage(void)
{
   char  *ptr;         /* */
   char   sTemp[512];  /* */
   
   
   if (!check_toc_and_counters())
      return;

   if (token[1][0] == '\"')
   {
      tokcpy2(sTemp, 512);
      ptr = strchr(sTemp+1, '\"');        /* find second quote character (") */

      if (ptr)
      {
         ptr[0] = EOS;
         um_strcpy(html_modern_backimage, sTemp + 1, 512, "set_html_modern_backimage[1]");
      }
      else
      { 
         um_strcpy(html_modern_backimage, sTemp, 512, "set_html_modern_backimage[2]");
      }
   }
   else
   {
      um_strcpy(html_modern_backimage, token[1], 512, "set_html_modern_backimage[3]");
   }

                                          /* Hier muessen immer / benutzt werden! */
   replace_char(html_modern_backimage, "\\", "/");
}





/*******************************************************************************
*
*  set_html_frames_width():
*     sets html_frames_width variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_frames_width(void)
{
   int   width;  /* */


   if (!check_toc_and_counters())
      return;
                                          /*r6pl8: Falls z.B. 30%, dann komplett umkopieren */
   if (strstr(token[1], "%") != NULL)
   {
      um_strcpy(html_frames_width, token[1], 16, "set_html_frames_width");
   }
   else
   {
      width = atoi(token[1]);
      
      if (width < 0)
      width = 128;
      
      sprintf(html_frames_width, "%d", width);
   }
}





/*******************************************************************************
*
*  set_html_frames_height():
*     sets html_frames_height variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_frames_height(void)
{
   int   height;  /* */
   
   
   if (!check_toc_and_counters())
      return;
                                          /*r6pl8: Falls z.B. 30%, dann komplett umkopieren */
   if (strstr(token[1], "%") != NULL)
   {
      um_strcpy(html_frames_height, token[1], 16, "set_html_frames_height[1]");
   }
   else
   {
      height = atoi(token[1]);
      
      if (height < 0)
         height = 64;
         
      sprintf(html_frames_height, "%d", height);
   }
}





/*******************************************************************************
*
*  set_html_frames_position():
*     sets html_frames_position variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_frames_position(void)
{
   if (!check_toc_and_counters())
      return;

   if (strstr(token[1], "left") != NULL)
   {
      html_frames_position = POS_LEFT;
      return;
   }

   if (strstr(token[1], "right") != NULL)
   {
      html_frames_position = POS_RIGHT;
      return;
   }

   if (strstr(token[1], "top") != NULL)
   { 
      html_frames_position = POS_TOP;
      return;
   }

   if (strstr(token[1], "bottom") != NULL)
   {
      html_frames_position = POS_BOTTOM;
      return;
   }
}





/*******************************************************************************
*
*  set_html_frames_alignment():
*     sets html_frames_alignment variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_frames_alignment(void)
{
   char   s[256];  /* buffer for parameter string */
   
   
   tokcpy2(s, 256);

   if (strstr(s, "center") != NULL)
   {
      html_frames_alignment = ALIGN_CENT;
      return;
   }

   if (strstr(s, "left") != NULL)
   { 
      html_frames_alignment = ALIGN_LEFT;
      return;
   }

   if (strstr(s, "right") != NULL)
   { 
      html_frames_alignment = ALIGN_RIGH;
      return;
   }
}





/*******************************************************************************
*
*  set_html_frames_backimage():
*     sets html_frames_backimage variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_frames_backimage(void)
{
   char  *ptr;         /* */
   char   sTemp[512];  /* */
   
   
   if (!check_toc_and_counters())
      return;

   if (token[1][0] == '\"')
   {
      tokcpy2(sTemp, 512);
      ptr = strchr(sTemp + 1, '\"');      /* find second quote character (") */

      if (ptr)
      {
         ptr[0] = EOS;
         um_strcpy(html_frames_backimage, sTemp+1, 512, "set_html_frames_backimage[1]");
      }
      else
      {
         um_strcpy(html_frames_backimage, sTemp, 512, "set_html_frames_backimage[2]");
      }
   }
   else
   {
      um_strcpy(html_frames_backimage, token[1], 512, "set_html_frames_backimage[3]");
   }

                                          /* Hier muessen immer / benutzt werden! */
   replace_char(html_frames_backimage, "\\", "/");
}





/*******************************************************************************
*
*  set_html_button_alignment():
*     sets html_button_alignment variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_button_alignment(void)
{
   char   s[256];  /* buffer for parameter string */
   
   
   tokcpy2(s, 256);

   if (strstr(s, "center") != NULL)
   {
      html_button_alignment = ALIGN_CENT;
      return;
   }

   if (strstr(s, "left") != NULL)
   {
      html_button_alignment = ALIGN_LEFT;
      return;
   }

   if (strstr(s, "right") != NULL)
   {
      html_button_alignment = ALIGN_RIGH;
      return;
   }
}





/*******************************************************************************
*
*  set_html_quotes():
*     sets html_quotes variable
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_quotes(void)
{
   char   s[256];  /* buffer for parameter string */

   
   tokcpy2(s, 256);                       /* get command parameters */
   
   if (strstr(s, "classic") != NULL)
   {
      html_quotes = QUOTES_CLASSIC;       /* ALIGN_CENT; */
      return;
   }
   
   if (strstr(s, "tags") != NULL)
   {
      html_quotes = QUOTES_TAGS;
      return;
   }
}


/* +++ EOF +++ */
