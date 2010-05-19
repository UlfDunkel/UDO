/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : par.c
*  Symbol prefix: par
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
*  Description  : ???
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
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*    fd  Feb 05: - file partly reformatted, TAB-free now
*                - replace_placeholders(): issue #12 fixed
*    fd  Feb 22: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 24: replace_placeholders() debugged
*    fd  Feb 25: replace_placeholders() debugged
*    fd  Feb 26: replace_placeholders() debugged
*    fd  May 17: add_macro(): auto_quote_chars() faded
*    fd  May 19: file tidied up
*
******************************************|************************************/

#ifndef ID_PAR_C
#define ID_PAR_C
const char *id_par_c= "@(#) par.c       $DATE$";
#endif





/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <time.h>                         /* v6.5.19 */
#include <stdlib.h>
#include "portab.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "chr.h"
#include "file.h"
#include "msg.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"
#include "img.h"

#include "export.h"
#include "par.h"
#include "udomem.h"





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define MAX_PARAMETERS  9                 /* */





/*******************************************************************************
*
*     LOCAL VARIABLES
*
******************************************|************************************/

LOCAL char      Param[MAX_PARAMETERS + 1][1024];
LOCAL char      Space[MAX_PARAMETERS + 1][64];

LOCAL HYPHEN   *hyphen[MAXHYPHEN];        /* Array mit Zeigern auf Trennregeln */

LOCAL MACROS   *macros[MAXMACROS];        /* Array auf Zeiger mit Makros */

LOCAL DEFS     *defs[MAXDEFS];            /* Array auf Zeiger mit defines */

   /* --- Platzhalter --- */
LOCAL SPECCMD   speccmd[MAXSPECCMDS + 1];
LOCAL int       speccmd_counter;





/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

   /* delete quotes in parameter strings */
LOCAL void del_param_quotes (char *s);

   /* get # of parameter blocks of command blocks in round brackets */
LOCAL int get_nr_of_parameters(const char *cmd, char *s);

   /*  */
LOCAL void reset_parameters(void);

   /* extract parameters from a string */
LOCAL int extract_parameters(char *s, const char *cmd, const int count);

   /* get parameters from a string */
LOCAL int get_parameters(char *s, const char *search, const int count);

   /*  */
LOCAL void adjust_params_inside(char * s);

   /* convert a link command into LDS format */
LOCAL BOOLEAN convert_link_lds(char *s, const char *p0, char *p1, char *p2, const char *link);

   /* convert a link command into STG format */
LOCAL BOOLEAN convert_link_stg(char *s, const char *p0, char *p1, char *p2, const char *link);

   /* convert a link command into PureC format */
LOCAL BOOLEAN convert_link_pch(char *s, const char *p0, char *p1, char *p2, const char *link);

   /* convert a link command into TeX format */
LOCAL BOOLEAN convert_link_tex(char *s, const char *p0, char *p1, char *p2);

   /* convert a link command into PDF format */
LOCAL BOOLEAN convert_link_pdf(char *s, const char *p0, char *p1, char *p2, const char *link);

   /* convert a link command into LaTeX format */
LOCAL BOOLEAN convert_link_lyx(char *s, const char *p0, char *p1, char *p2);

   /* convert a link command into TurboVisionHelp format */
LOCAL BOOLEAN convert_link_tvh(char *s, const char *p0, char *p1, char *p2);

   /* convert a link command into TeXinfo format */
LOCAL BOOLEAN convert_link_info(char *s, const char *p0, char *p1, char *p2, const char *link);

   /* convert a link command into IPF format */
LOCAL BOOLEAN convert_link_ipf(char *s, const char *p0, char *p1, char *p2, const char *link);

   /* convert a link command into RTF? format */
LOCAL BOOLEAN convert_link_etc(char *s, const char *p0, char *p1, char *p2, const char *link);

   /* convert a link command into its target format */
LOCAL void c_link(char *s, BOOLEAN inside_b4_macro);

   /* convert a url command into its target format */
LOCAL void c_url(char *s, BOOLEAN inside_b4_macro);

   /* convert an xlink command into its target format */
LOCAL void c_xlink(char *s, BOOLEAN inside_b4_macro);

   /* convert an ilink command into its target format */
LOCAL void c_ilink(char *s, const BOOLEAN inside_b4_macro);

   /* convert a plink command into its target format */
LOCAL void c_plink(char *s, const BOOLEAN inside_b4_macro);

   /* convert a label command into its target format */
LOCAL void c_plabel(char *s, const BOOLEAN inside_b4_macro); /* New in V6.5.9 [NHz] */

   /* convert a nolink command into its target format */
LOCAL void c_nolink(char *s, const BOOLEAN inside_b4_macro);

   /* convert a comment command into its target format */
LOCAL void c_comment(char *s, const BOOLEAN inside_b4_macro);

   /* convert an index command into its target format */
LOCAL BOOLEAN c_index(char *s, const BOOLEAN inside_b4_macro);

   /*  */
LOCAL BOOLEAN c_single_index(char *s, const BOOLEAN inside_b4_macro);

   /*  */
LOCAL BOOLEAN c_double_index(char *s, const BOOLEAN inside_b4_macro);

   /*  */
LOCAL BOOLEAN c_tripple_index(char *s, const BOOLEAN inside_b4_macro);

   /*  */
LOCAL BOOLEAN c_quadruple_index(char *s, const BOOLEAN inside_b4_macro);

   /* convert a time command into its target format */
LOCAL void c_internal_time(char *s, const BOOLEAN inside_b4_macro); /* V 6.5.19 */

   /* convert an img command into its target format */
LOCAL void c_internal_image(char *s, const BOOLEAN inside_b4_macro);

   /* convert a raw command into its target format */
LOCAL BOOLEAN c_single_raw(char *s, const BOOLEAN inside_b4_macro);

   /* convert a raw command into its target format */
LOCAL BOOLEAN c_double_raw(char *s, const BOOLEAN inside_b4_macro);

   /* handle conversion of raw commands */
LOCAL void c_internal_raw(char *s, const BOOLEAN inside_b4_macro);

   /* check if macro or definition uses parameters */
LOCAL BOOLEAN md_uses_parameters(const char *s);










/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  del_param_quotes():
*     delete quotes in parameter strings
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void del_param_quotes(

char  *s)  /* ^ to a complete line */
{
   qreplace_all(s, "!)", 2, ")", 1);
   qreplace_all(s, "!]", 2, "]", 1);
}





/*******************************************************************************
*
*  get_nr_of_parameters():
*     get # of parameter blocks of command blocks in round brackets
*
*     which are formatted like this: (!command [p1] [p2] [...])
*     or even like this: (!command[p1][p2][..])
*
*  Out:
*     # of parameter blocks
*
******************************************|************************************/

LOCAL int get_nr_of_parameters(

const char  *cmd,             /* command string, e.g. "raw" */
char        *s)               /* string to check */
{
   int       count = 0;       /* # of found parameters */
   char     *pos;             /* ^ to string s */
   char      search[128];     /* buffer for search string */


   sprintf(search, "(!%s", cmd);          /* create search string, e.g. "(!raw" */

                                          /* command not found */
   if ((pos = strstr(s, search)) == NULL )
      return 0;                           /* exit */

   pos += strlen(search);                 /* skip command */

                                          /* find first uncasted closing bracket */
   while (pos[0] != ')' || (pos[0] == ')' && pos[-1] == '!') )
   {
      switch (pos[0])
      {
      case EOS:                           /* not allowed: command block has a line break! */
         error_unexpected_eol();
         return 0;
         
      case ']':                           /* parameter found? */
         if (pos[-1] != '!')              /* if ] wasn't casted by ! ... */
         {
            count++;                      /* yes, parameter found */
         }
         
         break;
      }
      
      pos++;                              /* next char */
   }

   return count;
}





/*******************************************************************************
*
*  reset_parameters():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void reset_parameters(void)
{
   int   i;  /* */
   
   
   for (i = 0; i < MAX_PARAMETERS; i++)
   {
      Param[i][0] = EOS;
      Space[i][0] = EOS;
   };
}





/*******************************************************************************
*
*  extract_parameters():
*     extract parameters from a string
*
*  Notes:
*     The string has to have the syntax "(!command [text] [text] [text])".
*
*  Return:
*     # of parameters
*
******************************************|************************************/

LOCAL int extract_parameters(

char       *s,            /* ^ complete line */
const char *cmd,          /* ^ command without "(!": link, plink, xlink */
const int   count)        /* */
{
   int      i;            /* */
   char    *pos,          /* */
            search[128];  /* */
            

   sprintf(search, "(!%s", cmd);          /* PL3 */

   if ( (pos = strstr(s, search)) == NULL)
      return 0;
      

   reset_parameters();

   pos += strlen(search);

   i = 0;

   while (i < count)      
   {
      /* Anfang "[" des Parameters bestimmen */
      /* und die Zeichen ermitteln, die bis dahin */
      /* im Quelltext auftauchen */
      
      while ( (pos[0] != '[') && (pos[0] != EOS) )
      {
         chrcat(Space[i], pos[0]);
         pos++;
      }
      
      if (pos[0] == EOS)
      {
         error_unexpected_eol();
         return 0;
      }

      /* Pointer auf erstes Zeichen des Parameters setzen */
      /* und bis zur naechsten Klammer lesen, die nicht */
      /* duch ein Ausrufungszeichen gequotet ist. */
      
      pos++;

      while ( (pos[0] != ']' || (pos[0] == ']' && pos[-1] == '!')) && (pos[0] != EOS) )
      {
         chrcat(Param[i + 1], pos[0]);
         pos++;
      }

      if (pos[0] == EOS)
      {
         error_unexpected_eol();
         return 0;
      }

      pos++;
      i++;
   }

   /* Zeichen lesen, die bis zum Ende des Kommandos auftauchen */

#if 1
   while ( (pos[0] != ')') && (pos[0] != EOS) )
   {
      chrcat(Space[count], pos[0]);
      pos++;
   }
#else
   while ( (pos[0] != ')') && (pos[0] != EOS) )
   {
      chrcat(Space[count + 1], pos[0]);
      pos++;
   }
#endif

   if (pos[0] == EOS)
   {
      error_unexpected_eol();
      return 0;
   }

   return i;                              /* PL14: Anzahl der Parameter statt BOOLEAN */
}





/*******************************************************************************
*
*  get_parameters():
*     get parameters from a string
*
*  Return:
*     # of parameters
*
******************************************|************************************/

LOCAL int get_parameters(

char        *s,       /* */
const char  *search,  /* */
const int    count)   /* */
{
   int       i,       /* */
             params;  /* */
             

   params = extract_parameters(s, search, count);

   if (params == 0)
      return 0;
   

#if 0
   if (params != count)
      error "was nun?"
#endif

   sprintf(Param[0], "(!%s%s", search, Space[0]);

   if (params > 0)
   {
      for (i = 1; i <= params; i++)
      {
         strcat(Param[0], "[");
         strcat(Param[0], Param[i]);
         strcat(Param[0], "]");
         strcat(Param[0], Space[i]);
         
         del_param_quotes(Param[i]);   
      }
   }

   strcat(Param[0], ")");

   return params;                         /* PL14: Anzahl der Parameter statt BOOLEAN */
}





/*******************************************************************************
*
*  adjust_params_inside():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void adjust_params_inside(

char  *s)  /* */
{
   replace_macros(s);
   c_divis(s);
   c_vars(s);
   c_styles(s);
}





/*******************************************************************************
*
*  convert_link_lds():
*     convert a link command into LDS format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_lds(

char        *s,                /* */
const char  *p0,               /* */
char        *p1,               /* */
char        *p2,               /* */
const char  *link)             /* */
{
   char      s_entry[1024],    /* */
             old_entry[1024];  /* */
   char     *ptr;              /* */
   BOOLEAN   flag;             /* */
   

   strcpy(s_entry, p2);
   c_tilde(s_entry);
   replace_udo_quotes(s_entry);

   convert_tilde(p1);
   convert_tilde(p2);
   
   replace_udo_quotes(p1);
   replace_udo_quotes(p2);
   
   strcpy(old_entry, p2);

                                          /* auch Links innerhalb der Seite ermoeglichen */
   auto_references(s_entry, TRUE, "", 0, 0);
   
   /* Trick: Schauen, ob nun "> im Eintrag steht und dann */
   /* ab dort den Link einsetzen. */
   
   flag = FALSE;
   
   if ( (ptr = strstr(s_entry, "name=\"")) != NULL)
      flag = replace_once(ptr, old_entry, p1);

   if (!flag)
   {
      error_undefined_link(link);
      strcpy(s_entry, p1);   /* PL9 */
   }

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_stg():
*     convert a link command into STG format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_stg(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2,             /* */
const char  *link)           /* */
{
   char      nodename[256],  /* */
             s_entry[256];   /* */
   int       ti,             /* */
             li;             /* */
   BOOLEAN   isnode;         /* */
   BOOLEAN   flag;           /* */
   

   c_tilde(p2);
   replace_udo_quotes(p2);

   flag = is_node_link(p2, nodename, &ti, &isnode, &li);

   replace_udo_tilde(p2);
   replace_udo_nbsp(p2);

   convert_tilde(p1);
   replace_udo_quotes(p1);

   if (flag)
   {
      node2stg(p1);
      node2stg(p2);

      replace_2at_by_1at(p1);
      replace_2at_by_1at(p2);
      
      replace_2at_by_1at(nodename);

      if (isnode && is_current_node(ti))  /* r6pl15: links auf gleiche node mag ST-Guide nicht */
      {
         strcpy(s_entry, p1);
      }
      else
      {
         if (!isnode)                     /* PL9: Links auf Labels sind etwas besonderes */
            sprintf(s_entry, "@{\"%s\" link \"%s\" \"%s\"}", p1, nodename, p2);
         else
            sprintf(s_entry, "@{\"%s\" link \"%s\"}", p1, p2);
      }
   }

   if (!flag)                             /* Node, Alias oder Label nicht definiert */
   {
      error_undefined_link(link);
      strcpy(s_entry, p1);
   }

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_pch():
*     convert a link command into PureC format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_pch(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2,             /* */
const char  *link)           /* */
{
   char      nodename[256],  /* */
             s_entry[256];   /* */
   int       ti,             /* */
             li;             /* */
   BOOLEAN   isnode;         /* */
   BOOLEAN   flag;           /* */
   

   c_tilde(p2);
   replace_udo_quotes(p2);

   flag = is_node_link(p2, nodename, &ti, &isnode, &li);

   replace_udo_tilde(p2);
   replace_udo_nbsp(p2);

   convert_tilde(p1);
   replace_udo_quotes(p1);

   if (flag)
   {
      node2pchelp(p2);
      sprintf(s_entry, "\\link(\"%s\")%s\\#", p2, p1);
   }
   else                                   /* Node, Alias oder Label nicht definiert */
   {
      error_undefined_link(link);
      strcpy(s_entry, p1);
   }

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_tex():
*     convert a link command into TeX format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_tex(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2)             /* */
{
   char      s_entry[1024];  /* */
   int       li,             /* */
             ti;             /* */
   BOOLEAN   isnode;         /* */
   char      nodename[256];  /* */
   

   convert_tilde(p1);
   convert_tilde(p2);
   
   replace_udo_quotes(p1);
   replace_udo_quotes(p2);
   
   label2tex(p2);

   is_node_link(p2, nodename, &ti, &isnode, &li);

   sprintf(s_entry, "%s (%s \\ref{%s})", p1, lang.see, p2);

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_pdf():
*     convert a link command into PDF format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_pdf(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2,             /* */
const char  *link)           /* */
{
   char      nodename[256],  /* */
             s_entry[256];   /* */
   int       ti,             /* */
             li,             /* */
             dest;           /* */
   BOOLEAN   isnode;         /* */
   BOOLEAN   flag;           /* */
   

   c_tilde(p2);
   replace_udo_quotes(p2);

   flag = is_node_link(p2, nodename, &ti, &isnode, &li);

   convert_tilde(p1);
   replace_udo_quotes(p1);

   if (flag)
   {
      if (isnode)
         dest = ti;
      else
         dest= li;
      
      /* Changed in r6.2pl1 [NHz] */
/* V6.5.20 [CS] Start */
      sprintf(s_entry, "\\hidelink{\\pdfstartlink goto num %d %s\\pdfendlink}", dest, p1);
/* old:
      sprintf(s_entry, "{\\pdfstartlink goto num %d\n%s\\pdfendlink}", dest, p1);
*/
   }
   else                                   /* Node, Alias oder Label nicht definiert */
   {
      error_undefined_link(link);
      strcpy(s_entry, p1);
   }

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_lyx():
*     convert a link command into LaTeX format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_lyx(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2)             /* */
{
   char      s_entry[1024];  /* */
   int       li,             /* */
             ti;             /* */
   BOOLEAN   isnode;         /* */
   char      nodename[256];  /* */

   is_node_link(p2, nodename, &ti, &isnode, &li);

   sprintf(s_entry,
           "%s (%s \n\\begin_inset LatexDel \\ref{%s}\n\n\\end_inset\n\n)",
           p1, lang.see, p2);

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_tvh():
*     convert a link command into TurboVisionHelp format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_tvh(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2)             /* */
{
   char      s_entry[1024];  /* */
   int       li,             /* */
             ti;             /* */
   BOOLEAN   isnode;         /* */
   char      nodename[256];  /* */
   

   is_node_link(p2, nodename, &ti, &isnode, &li);

   node2vision(p2);
   sprintf(s_entry, "{%s:%s}", p1, p2);

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_info():
*     convert a link command into TeXinfo format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_info(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2,             /* */
const char  *link)           /* */
{
   char      nodename[256],  /* */
             s_entry[256];   /* */
   int       ti,             /* */
             li;             /* */
   BOOLEAN   isnode;         /* */
   BOOLEAN   flag;           /* */
   

   c_tilde(p2);
   replace_udo_quotes(p2);

   flag = is_node_link(p2, nodename, &ti, &isnode, &li);

   convert_tilde(p1);
   replace_udo_quotes(p1);

   replace_udo_tilde(p2);
   replace_udo_nbsp(p2);
   node2texinfo(p2);

   if (flag)
   {
      if (isnode)
         strcpy(nodename, p2);
      else
         node2texinfo(nodename);

      sprintf(s_entry, "%s (@xref{%s})", p1, nodename);
   }
   else                                   /* Node, Alias oder Label nicht definiert */
   {
      error_undefined_link(link);
      strcpy(s_entry, p1);
   }

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_ipf():
*     convert a link command into IPF format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_ipf(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2,             /* */
const char  *link)           /* */
{
   char      nodename[256],  /* */
             s_entry[256],   /* */
             s_id[256];      /* */
   int       ti,             /* */
             li;             /* */
   BOOLEAN   isnode;         /* */
   BOOLEAN   flag;           /* */
   

   c_tilde(p2);
   replace_udo_quotes(p2);

   flag = is_node_link(p2, nodename, &ti, &isnode, &li);

   convert_tilde(p1);
   replace_udo_quotes(p1);

   if (flag)
   {
      getLabelIndexFromTocIndex(&li, ti);
      node2NrIPF(s_id, li);
      sprintf(s_entry, ":link reftype=hd refid=%s.%s:elink.", s_id, p1);
   }
   else                                   /* Node, Alias oder Label nicht definiert */
   {
      error_undefined_link(link);
      strcpy(s_entry, p1);
   }

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_ps():
*     ??? (description)
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_ps(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2,             /* */
const char  *link)           /* */
{
   char      nodename[256],  /* */
             s_entry[256];   /* */
   int       ti,             /* */
             li;             /* */
   BOOLEAN   isnode;         /* */
   BOOLEAN   flag;           /* */
   

                                          /* Internal Link for Postscript */
   flag = is_node_link(p2, nodename, &ti, &isnode, &li);

   convert_tilde(p1);
   
   if (flag)
   {
      if (p2[0] == EOS)
         strcpy(p2, Param[1]);
      
      replace_udo_quotes(p2);
      replace_udo_quotes(p1);

      /* Changed in V6.5.3 [NHz] */
      replace_all(p1, "(", "\\(");
      replace_all(p1, ")", "\\)");
      
      c_vars(p1);
      
      qreplace_all(p1, KPSPC_S, KPSPC_S_LEN, ")", 1);
      qreplace_all(p1, KPSPO_S, KPSPO_S_LEN, "(", 1);
      
      sprintf(s_entry, ") udoshow (%s) /%s 0 255 0 Link (", p1, p2);
   }
   else                                   /* Node, Alias oder Label nicht definiert */
   {
      error_undefined_link(link);
      strcpy(s_entry, p1);
   }

   if (insert_placeholder(s, p0, s_entry, p1))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  convert_link_etc():
*     convert a link command into RTF? format
*
*  return:
*     FALSE: failure
*     TRUE : success
*
******************************************|************************************/

LOCAL BOOLEAN convert_link_etc(

char        *s,              /* */
const char  *p0,             /* */
char        *p1,             /* */
char        *p2,             /* */
const char  *link)           /* */
{
   char      nodename[256],  /* */
             s_entry[256];   /* */
   char      lq[16],         /* */
             rq[16];         /* */
   int       ti,             /* */
             li;             /* */
   BOOLEAN   isnode;         /* */
   BOOLEAN   flag;           /* */
   

   c_tilde(p2);
   replace_udo_quotes(p2);

   flag = is_node_link(p2, nodename, &ti, &isnode, &li);

   replace_udo_tilde(p2);
   replace_udo_nbsp(p2);

   /* Deleted in r6.2pl1 [NHz] / Bug #00000030 */
/* convert_tilde(p1); */

   replace_udo_quotes(p1);

   if (flag)
   {
      if (no_links)
      {
         /* r6pl6: Links unterdruecken */
         strcpy(s_entry, p1);
      }
      else
      {
         if (desttype == TORTF)   /*r6pl6: die richtigen benutzen */
         {
            strcpy(lq, "\\ldblquote");
            strcpy(rq, "\\rdblquote");
         }
         else
         {
            strcpy(lq, "\"");
            strcpy(rq, "\"");
         }

         if (!isnode)
         {
            /* PL9: Links auf Labels sind etwas besonderes */
            sprintf(s_entry, "%s (%s %s%s%s)", p1, lang.see, lq, nodename, rq);
         }
         else
         {
            sprintf(s_entry, "%s (%s %s%s%s)", p1, lang.see, lq, p2, rq);
         }
      }
   }


   if (!flag)
   {
      /* Node, Alias oder Label nicht definiert */
      error_undefined_link(link);
      strcpy(s_entry, p1);
   }

   if (replace_once(s, p0, s_entry))
      return TRUE;

   return FALSE;
}





/*******************************************************************************
*
*  c_link():
*     convert a link command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_link(

char        *s,                /* */
BOOLEAN      inside_b4_macro)  /* */
{
   int       pnr = 0;          /* */
   char      s_entry[1024],    /* */
             old_entry[1024],  /* */
             link[1024];       /* */
   char     *ptr;              /* */
   BOOLEAN   linkerror;        /* */
   BOOLEAN   flag;             /* */
   BOOLEAN   old_autorefoff;   /* */
   

   old_autorefoff = bDocAutorefOff;
   bDocAutorefOff = FALSE;

   linkerror = FALSE;
   
   while (!linkerror && ((pnr = get_parameters(s, "link", 2)) == 2) )
   {
      strcpy(link, Param[2]);
      
      del_whitespaces(Param[1]);
      del_whitespaces(Param[2]);


      if (inside_b4_macro)
      {
         if (desttype != TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(Param[2], TRUE);
         }

         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
      }

      switch (desttype)
      {
      case TOHAH:
      case TOHTM:
      case TOMHH:
         strcpy(s_entry, Param[2]);
         c_tilde(s_entry);
         replace_udo_quotes(s_entry);

         convert_tilde(Param[1]);
         convert_tilde(Param[2]);
         
         replace_udo_quotes(Param[1]);
         replace_udo_quotes(Param[2]);
         
         strcpy(old_entry, Param[2]);

         auto_references(s_entry, TRUE, "", 0, 0);      /* auch Links innerhalb der Seite ermoeglichen */

         /* Trick: Schauen, ob nun "> im Eintrag steht und dann */
         /* ab dort den Link einsetzen. */
         
         flag = FALSE;
         
         if ( (ptr = strstr(s_entry, "\">")) != NULL)
            flag = replace_once(ptr, old_entry, Param[1]);

         if (!flag)
         {
            error_undefined_link(link);
            strcpy(s_entry, Param[1]);
         }

         linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
         break;


      case TOWIN:
      case TOWH4:
      case TOAQV:
         strcpy(s_entry, Param[2]);
         c_tilde(s_entry);
         replace_udo_quotes(s_entry);

         convert_tilde(Param[1]);
         convert_tilde(Param[2]);
         
         replace_udo_quotes(Param[1]);
         replace_udo_quotes(Param[2]);
         
         strcpy(old_entry, Param[2]);

         auto_references(s_entry, TRUE, "", 0, 0);      /* auch Links innerhalb der Seite ermoeglichen */

         /* Trick: Schauen, ob nun {\uldb im Eintrag steht und dann */
         /* ab dort den Link einsetzen. */
         
         flag = FALSE;

         ptr =strstr(s_entry, "{\\uldb");

         if (ptr == NULL)   /* PL8: Links auf Popups erlauben */
            ptr = strstr(s_entry, "{\\ul");
 
         if (ptr != NULL)
            flag = replace_once(ptr, old_entry, Param[1]);

         if (!flag)
         {
            error_undefined_link(link);
            strcpy(s_entry, Param[1]);
         }

         linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
         break;
         
         
      case TOLDS:
         linkerror = !convert_link_lds(s, Param[0], Param[1], Param[2], link);
         break;
         
         
      case TOSTG:
      case TOAMG:
         linkerror = !convert_link_stg(s, Param[0], Param[1], Param[2], link);
         break;
         
         
      case TOTEX:
         linkerror = !convert_link_tex(s, Param[0], Param[1], Param[2]);
         break;
         
         
      case TOPDL:
         linkerror = !convert_link_pdf(s, Param[0], Param[1], Param[2], link);
         break;
         
         
      case TOLYX:
         linkerror = !convert_link_lyx(s, Param[0], Param[1], Param[2]);
         break;
         
         
      case TOTVH:
         linkerror = !convert_link_tvh(s, Param[0], Param[1], Param[2]);
         break;
         
         
      case TOPCH:
         linkerror = !convert_link_pch(s, Param[0], Param[1], Param[2], link);
         break;
         
         
      case TOINF:
         linkerror = !convert_link_info(s, Param[0], Param[1], Param[2], link);
         break;
         
         
      case TOIPF:
         linkerror = !convert_link_ipf(s, Param[0], Param[1], Param[2], link);
         break;

         /* Internal Link for Postscript */
      case TOKPS:
         linkerror = !convert_link_ps(s, Param[0], Param[1], Param[2], link);
         break;


      default:
         linkerror = !convert_link_etc(s, Param[0], Param[1], Param[2], link);
      }
   }

   if (linkerror)
   {
      replace_once(s, Param[0], Param[1]);
      error_replace_param("!link");
   }

   if (pnr != 0 && pnr != 2)
      error_wrong_nr_parameters("!link");
   
   bDocAutorefOff = old_autorefoff;
}





/*******************************************************************************
*
*  c_url():
*     convert a url command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_url(

char        *s,                  /* */
BOOLEAN      inside_b4_macro)    /* */
{
   int       pnr = 0,            /* */
             url_len,            /* */
             i;                  /* counter */
   char      s_entry[4096],      /* */
             url_rtf[2048],      /* */
             rtf0[4];            /* */
   BOOLEAN   linkerror = FALSE;  /* */
   
   char      rtf1[] = "00d0c9ea79f9bace118c8200aa004ba90b0200000003000000";
   char      rtf2[] = "e0c9ea79f9bace118c8200aa004ba90b";
   char      rtf3[] = "000000";
   char      rtf4[] = "0000";


   while (!linkerror && ((pnr = get_parameters(s, "url", 2)) == 2))
   {
      del_whitespaces(Param[1]);

      /* Wird ein leerer Parameter benutzt, dann den ersten auch als zweiten verwenden. */

      if (Param[2][0] == EOS)
         um_strcpy(Param[2], Param[1], 1024, "c_url[1]");
      
      if (inside_b4_macro)
      {
         if (desttype != TOSTG)
            auto_quote_chars(Param[1], TRUE);

         adjust_params_inside(Param[1]);
      }

      if (no_urls)
      {
         replace_all(s, Param[0], Param[1]);
      }
      else
      {
         switch (desttype)
         {
         case TOHAH:
         case TOHTM:
         case TOMHH:
            convert_tilde(Param[1]);
            
            if (Param[2][0] == EOS)
               um_strcpy(Param[2], Param[1], 1024, "c_url[TOHTM|1]");
            
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[1]);
            
            if (html_frames_layout)
               sprintf(s_entry, "<a href=\"%s\" target=\"_top\">%s</a>", Param[2], Param[1]);
            else
               sprintf(s_entry, "<a href=\"%s\">%s</a>", Param[2], Param[1]);
            
            if (strlen(s_entry)>=4096) /* vj: For debugging reasons */
               printf("c_url: s_entry buffer overrus after sprintf\n");

            linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
            break;


            /* New in r6pl15 [NHz] */
            /* Weblink for Postscript/PDF */
         case TOKPS:
            convert_tilde(Param[1]);
            
            if (Param[2][0] == EOS)
               strcpy(Param[2], Param[1]);
            
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[1]);
            
            /* Changed in V6.5.5 [NHz] */
            c_divis(Param[1]);
            c_vars(Param[1]);
            
            /* Changed: Fixed bug #0000062 in V 6.5.8 [NHz] */
            node2postscript(Param[1], KPS_CONTENT);
            
            replace_all(Param[1], KPSPO_S, "(");
            replace_all(Param[1], KPSPC_S, ")");
            
            sprintf(s_entry, ") udoshow (%s) (%s) 0 0 255 WebLink (", Param[1], Param[2]);
            linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
            break;


            /* Deleted bug in V6.5.8 [NHz] */
            /* Weblink for WinHelp4 */
         case TOWH4:
            convert_tilde(Param[1]);
            
            if (Param[2][0] == EOS)
               strcpy(Param[2], Param[1]);
            
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[1]);
            
            sprintf(s_entry, "{\\ul %s}{\\v !ExecFile(%s)}", Param[1], Param[2]);
            linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
            break;

            /* New in r6pl15 [NHz] */
            /* Weblink for Richtext Format */
         case TORTF:
            convert_tilde(Param[1]);

            /* New in r6.2pl1 [NHz] / Bug #00000029 */
            c_rtf_quotes(Param[1]);

            if (Param[2][0] == EOS)
               strcpy(Param[2], Param[1]);
            
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[1]);

            /* Changed in r6.2pl1 [NHz] */
            auto_quote_chars(Param[2], TRUE);
            url_len = (int)strlen(Param[2]);

            rtf0[0]    = EOS;
            url_rtf[0] = EOS;

            for (i = 0; i < url_len;i++)
            {
               if (Param[2][i] == '\\')
               {
                  i += 2;
                  rtf0[0]=EOS;
                  strncpy(rtf0, Param[2]+i, 2);
                  i++;
               }
               else
                  sprintf(rtf0, "%x", (int)Param[2][i]); 
                  
               strcat(url_rtf, rtf0);
               strcat(url_rtf, "00");
            }

            sprintf(s_entry, 
                    "{\\field{\\*\\fldinst {HYPERLINK \"%s\"}{{\\*\\datafield %s%s%x%s%s%s}}}\n{\\fldrslt {\\cs15\\ul\\cf2 %s}}}", 
                    Param[2], rtf1, rtf2, (url_len+1)*2, rtf3, url_rtf, rtf4, Param[1]);

            linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
            break;


         default:
            convert_tilde(Param[1]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            
            linkerror = !insert_placeholder(s, Param[0], Param[1], Param[1]);

         }   /*switch*/
         
      }   /* if (no_urls) */

   }   /* while */

   if (linkerror)
   {
      replace_once(s, Param[0], Param[1]);
      error_replace_param("!url");
   }

   if (pnr != 0 && pnr != 2)
      error_wrong_nr_parameters("!url");
}





/*******************************************************************************
*
*  c_xlink():
*     convert an xlink command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_xlink(

char        *s,                  /* */
BOOLEAN      inside_b4_macro)    /* */
{
   int       pnr = 0;            /* */
   char      s_entry[1024];      /* */
   char      wnode[1024],        /* */
             wfile[1024],        /* */
            *ptr;                /* */
   BOOLEAN   linkerror = FALSE;  /* */
   

   while (!linkerror && ((pnr = get_parameters(s, "xlink", 2)) == 2))
   {
      del_whitespaces(Param[1]);

      /* PL6: Wird ein leerer Parameter benutzt, dann den ersten auch als zweiten verwenden. */
      
      if (Param[2][0] == EOS && desttype != TOHTM && desttype != TOMHH && desttype != TOHAH)
      {
         strcpy(Param[2], Param[1]);
      }


      if (inside_b4_macro)
      {
         if (desttype != TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);
         }

         adjust_params_inside(Param[1]);
      }

      if (no_xlinks)
      {
         replace_all(s, Param[0], Param[1]);
      }
      else
      {
         switch (desttype)
         {
         case TOSTG:
         case TOAMG:
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            
            replace_2at_by_1at(Param[2]);
            replace_2at_by_1at(Param[1]);
            
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[1]);
            
            node2stg(Param[2]);
            node2stg(Param[1]);
            
            sprintf(s_entry, "@{\"%s\" link \"%s\"}", Param[1], Param[2]);

            linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
            break;
            
            
         case TOHAH:
         case TOHTM:
         case TOMHH:
            convert_tilde(Param[1]);
            
            if (Param[2][0] == EOS)
               strcpy(Param[2], Param[1]);
            
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[1]);
            
            if (html_frames_layout)
               sprintf(s_entry, "<a href=\"%s\" target=\"_top\">%s</a>", Param[2], Param[1]);
            else
               sprintf(s_entry, "<a href=\"%s\">%s</a>", Param[2], Param[1]);
            
            linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
            break;
            
            
         case TOLDS:
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);

            sprintf(s_entry, "<htmlurl url=\"%s\" name=\"%s\">", Param[2], Param[1]);
            linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
            break;
            
            case TOPCH:
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);

            sprintf(s_entry, "\\#%s\\#", Param[1]);
            linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
            break;
         
         case TOWIN:
         case TOWH4:
         case TOAQV:
            /* PL8: Der erste Teil muss auch angepasst werden */
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
         
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);

            ptr = strchr(Param[2], '@');
            
            if (ptr != NULL)
            {
               ptr[0] = EOS;
               
               strcpy(wnode, Param[2]);
               strcpy(wfile, ptr+1);
               
               if (wnode[0] != EOS && wfile[0] != EOS)
               {
                  node2winhelp(wnode);
                  sprintf(s_entry, "{\\uldb %s}{\\v %s@%s}", Param[1], wnode, wfile);
                  linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
               }
               else
               {
                  if (wnode[0] != EOS)
                  {
                     error_xlink_win_topic();
                     linkerror = !replace_once(s, Param[0], Param[1]);
                  }
                  
                  if (wfile[0] != EOS)
                  {
                     error_xlink_win_file();
                     linkerror = !replace_once(s, Param[0], Param[1]);
                  }
               }
            }
            else
            {
               error_xlink_win_syntax();
               linkerror = !replace_once(s, Param[0], Param[1]);
            }
            
            break;


            /* New in r6pl15 [NHz] */
            /* Filelink for Postscript */
         case TOKPS:
            convert_tilde(Param[1]);
            
            if (Param[2][0] == EOS)
               strcpy(Param[2], Param[1]);
            
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[1]);

            /* Changed in V6.5.6 [NHz] */
            c_divis(Param[1]);
            c_vars(Param[1]);
            auto_quote_chars(Param[1], TRUE);
            
            sprintf(s_entry, ") udoshow (%s) (%s) %s 255 0 0 FileLink (", Param[1], Param[2], "/Null");
            linkerror = !insert_placeholder(s, Param[0], s_entry, Param[1]);
            break;


         default:
            convert_tilde(Param[1]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            
            linkerror = !insert_placeholder(s, Param[0], Param[1], Param[1]);
            
         }   /*switch*/
            
      }   /* if (no_xlinks) */

   }   /* while */

   if (linkerror)
   {
      replace_once(s, Param[0], Param[1]);
      error_replace_param("!xlink");
   }

   if (pnr != 0 && pnr != 2)
      error_wrong_nr_parameters("!xlink");
}





/*******************************************************************************
*
*  c_ilink():
*     convert an ilink command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_ilink(

char           *s,                 /* komplette Zeile */
const BOOLEAN   inside_b4_macro)   /* Sind bereits Makros in dieser Zeile umgewandelt worden? */
{
   int          pnr = 0;           /* */
   char         s_entry[1024],     /* */
                img_entry[1024],   /* */
                old_entry[1024],   /* */
                link[1024];        /* */
   char        *ptr;               /* */
   BOOLEAN      flag;              /* */
   BOOLEAN      linkerror;         /* */
   BOOLEAN      old_autorefoff;    /* */
   char         closer[8] = "\0";  /* tag closer */
   
   
   old_autorefoff = bDocAutorefOff;
   bDocAutorefOff = FALSE;
   
   linkerror = FALSE;
   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   while (!linkerror && ((pnr = get_parameters(s, "ilink", 3)) == 3) )
   {
      strcpy(link, Param[3]);
      del_whitespaces(Param[1]);
      del_whitespaces(Param[2]);
      del_whitespaces(Param[3]);
   
      if (inside_b4_macro)
      {
         /* Fixed bug #0000055 in V6.5.2 [NHz] */
/*       if (desttype!=TOSTG)
         {
            auto_quote_chars(Param[2], TRUE);
            auto_quote_chars(Param[3], TRUE);
         }
*/
   
         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
         adjust_params_inside(Param[3]);
      }
      
      fsplit(Param[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
      
      replace_udo_quotes(Param[2]);
      replace_udo_quotes(Param[3]);
      
      switch (desttype)
      {
      case TOHAH:                         /* V6.5.17 */
      case TOHTM:
      case TOMHH:
         strcpy(tmp_suff, sDocImgSuffix);
         sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
         replace_char(Param[1], "\\", "/");
         
         strcpy(s_entry, Param[3]);
         c_tilde(s_entry);
         replace_udo_quotes(s_entry);
         
         convert_tilde(Param[2]);
         convert_tilde(Param[3]);
         replace_udo_quotes(Param[2]);
         replace_udo_quotes(Param[3]);
         strcpy(old_entry, Param[3]);
         
                                          /* auch innerhalb des Nodes linken (TRUE)! */
         auto_references(s_entry, TRUE, "", 0, 0);
         
         /* Trick/Hack: Schauen, ob nun "> im Eintrag steht und dann */
         /* ab dort den Image-Eintrag setzen. */
         
         flag = FALSE;
         
         if ((ptr = strstr(s_entry, "\">")) != NULL )
         {
            if (no_images)                /* r6pl2 */
            {
               strcpy(img_entry, Param[2]);
            }
            else
            {
               sprintf(img_entry, "<img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s>",
                  Param[1], Param[2], Param[2], closer);
            }

            flag = replace_once(ptr, old_entry, img_entry);
         }
         
         if (!flag)
         {
            error_undefined_link(link);
            strcpy(s_entry, Param[2]);    /* PL9 */
         }
         
         linkerror = !insert_placeholder(s, Param[0], s_entry, Param[2]);
         break;
         
      case TOWIN:
      case TOWH4:
      case TOAQV:
         strcpy(tmp_suff, ".bmp");
         sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
         replace_char(Param[1], "\\", "/");
         
         strcpy(s_entry, Param[3]);
         c_tilde(s_entry);
         replace_udo_quotes(s_entry);
         
         convert_tilde(Param[2]);
         convert_tilde(Param[3]);
         replace_udo_quotes(Param[2]);
         replace_udo_quotes(Param[3]);
         strcpy(old_entry, Param[3]);
         
                                          /* auch innerhalb des Nodes linken (TRUE)! */
         auto_references(s_entry, TRUE, "", 0, 0);
         
         /* Trick: Schauen, ob nun {\uldb im Eintrag steht und dann */
         /* ab dort den Image-Text einsetzen. */
         
         flag = FALSE;
         
         if ((ptr = strstr(s_entry, "{\\uldb")) != NULL )
         {
            if (no_images)                /*r6pl2*/
            {
               strcpy(img_entry, Param[2]);
            }
            else
            {
               sprintf(img_entry, "\\{bmc %s\\}", Param[1]);
            }

            flag = replace_once(ptr, old_entry, img_entry);
         }
         
         if (!flag)
         {
            error_undefined_link(link);
            strcpy(s_entry, Param[2]);    /* PL9 */
         }
         
         linkerror = !insert_placeholder(s, Param[0], s_entry, Param[2]);
         break;
         
      case TOLDS:
         linkerror = !convert_link_lds(s, Param[0], Param[2], Param[3], link);
         break;
         
      case TOSTG:
      case TOAMG:
         linkerror = !convert_link_stg(s, Param[0], Param[2], Param[3], link);
         break;
         
      case TOTEX:
      case TOPDL:
         linkerror = !convert_link_tex(s, Param[0], Param[2], Param[3]);
         break;
         
      case TOLYX:
         linkerror = !convert_link_lyx(s, Param[0], Param[2], Param[3]);
         break;
         
      case TOTVH:
         linkerror = !convert_link_tvh(s, Param[0], Param[2], Param[3]);
         break;
         
      /* New in V6.5.5 [NHz] */
      case TOKPS:
         linkerror = !convert_link_ps(s, Param[0], Param[2], Param[3], link);
         break;
         
      default:
         linkerror = !convert_link_etc(s, Param[0], Param[2], Param[3], link);
      }
   }
   
   if (linkerror)
   {
      replace_once(s, Param[0], Param[2]);
      error_replace_param("!ilink");
   }
   
   if (pnr != 0 && pnr != 3)
   {
      error_wrong_nr_parameters("!ilink");
   }
   
   bDocAutorefOff = old_autorefoff;
}





/*******************************************************************************
*
*  c_plink():
*     convert a plink command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_plink(

char           *s,                  /* */
const BOOLEAN   inside_b4_macro)    /* */
{
   int          pnr = 0;            /* */
   char         s_entry[1024];      /* */
   char         n[512];             /* */
   BOOLEAN      linkerror = FALSE;  /* */

   while (!linkerror && (pnr = get_parameters(s, "plink", 2)) == 2)
   {

      if (inside_b4_macro)
      {
         if (desttype != TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(Param[2], TRUE);   
         }
         
         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
      }

      switch (desttype)
      {
      case TOTEX:
      case TOPDL:
         label2tex(Param[2]);
         sprintf(s_entry, "%s (%s %s \\pageref{%s})", Param[1], lang.see, lang.page, Param[2]);
         linkerror = !replace_once(s, Param[0], s_entry);
         break;
         
         
      case TOLYX:
         sprintf(s_entry,
                 "%s (%s %s \n\\begin_inset LatexDel \\pageref{%s}\n\n\\end_inset\n\n)",
                 Param[1], lang.see, lang.page, Param[2]);
                 
         if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
         {
            linkerror = TRUE;
            replace_once(s, Param[0], s_entry);
         }
         
         break;
         
         
      case TORTF:
         um_strcpy(n, Param[2], 512, "c_plink[1]");
         node2winhelp(n);
         
         sprintf(s_entry, 
                 "%s (%s %s {\\field{\\*\\fldinst {PAGEREF %s }}{\\fldrslt {\\lang1024 x}}})",
                 Param[1], lang.see, lang.page, n);
                 
         linkerror = !replace_once(s, Param[0], s_entry);
         break;    
         
                             
      default:
         linkerror = !replace_once(s, Param[0], Param[1]);
      }
   }

   if (pnr != 0 && pnr != 2)
      error_wrong_nr_parameters("!plink");
   

   if (linkerror)
      error_replace_param("!plink");
}





/*******************************************************************************
*
*  c_plabel():
*     convert a label command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_plabel(

char           *s,                  /* */
const BOOLEAN   inside_b4_macro)    /* */
{
   int          pnr = 0;            /* */
   char         s_entry[1024],      /* */
                n[512];             /* */
   BOOLEAN      linkerror = FALSE;  /* */


   while (!linkerror && (pnr = get_parameters(s, "label", 2)) == 2)
   {
      if (inside_b4_macro)
      {
         if (desttype != TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(Param[2], TRUE);   
         }
         
         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
      }

      switch (desttype)
      {
      case TORTF:
         um_strcpy(n, Param[2], 512, "c_plabel[1]");
         node2winhelp(n);
         sprintf(s_entry, "{\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}", n, Param[1], n);
         linkerror = !replace_once(s, Param[0], s_entry);
         break;                    
         
         
      default:
         linkerror = !replace_once(s, Param[0], Param[1]);
      }
   }

   if (pnr != 0 && pnr != 2)
      error_wrong_nr_parameters("!label");
   

   if (linkerror)
      error_replace_param("!label");
}





/*******************************************************************************
*
*  c_nolink():
*     convert a nolink command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_nolink(

char           *s,                  /* */
const BOOLEAN   inside_b4_macro)    /* */
{
   int          pnr = 0;            /* */
   char         s_entry[1024];      /* */
   BOOLEAN      linkerror = FALSE;  /* */


   while (!linkerror && (pnr=get_parameters(s, "nolink", 1)) == 1)
   {
      if (inside_b4_macro)
      {
         if (desttype != TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(Param[2], TRUE);   
         }
         
         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
      }

      switch (desttype)
      {
      case TOSTG:
      case TOAMG:
         replace_2at_by_1at(Param[1]);
         sprintf(s_entry, "@{\"%s\" ignore}", Param[1]);
         
         if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
         {
            linkerror = TRUE;
            replace_once(s, Param[0], Param[1]);
         }
         
         break;


      default:
         if (!insert_placeholder(s, Param[0], Param[1], Param[1]))
         {
            linkerror = TRUE;
            replace_once(s, Param[0], Param[1]);
         }
      }
   }

   if (pnr != 0 && pnr != 1)
      error_wrong_nr_parameters("!nolink");
   

   if (linkerror)
      error_replace_param("!nolink");
}





/*******************************************************************************
*
*  c_comment():
*     convert a comment command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_comment(

char           *s,                  /* */
const BOOLEAN   inside_b4_macro)    /* */
{
   int          pnr = 0;            /* */
   char         s_entry[1024];      /* */
   BOOLEAN      linkerror = FALSE;  /* */
   

   while (!linkerror && (pnr = get_parameters(s, "comment", 1)) == 1)
   {
      if (inside_b4_macro)
      {
         if (desttype!=TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(Param[2], TRUE);   
         }
         
         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
      }

      switch (desttype)
      {
      case TOHAH:
      case TOHTM:
      case TOMHH:
         sprintf(s_entry, "<!-- %s -->", Param[1]);
         
         if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
         {
            linkerror = TRUE;
            replace_once(s, Param[0], Param[1]);
         }
         
         break;


      case TOSRC:
      case TOSRP:
         sprintf(s_entry, "%s %s %s", sSrcRemOn, Param[1], sSrcRemOff);
         
         if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
         {
            linkerror = TRUE;
            replace_once(s, Param[0], Param[1]);
         }
         
         break;


      case TOWIN:
      case TOWH4:
      case TORTF:
      case TOAQV:
         sprintf(s_entry, "{\\*\\%s}", Param[1]);
         
         if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
         {
            linkerror = TRUE;
            replace_once(s, Param[0], Param[1]);
         }
         
         break;


      default:
         if (use_comments)
         {
            sprintf(s_entry, "(%s)", Param[1]);
            
            if (!replace_once(s, Param[0], s_entry))
            {
               linkerror = TRUE;
               replace_once(s, Param[0], Param[1]);
            }
         }
         else
         {
            if (!delete_once(s, Param[0]))
            {
               linkerror = TRUE;
            }
         }
      }
   }

   if (pnr != 0 && pnr != 1)
      error_wrong_nr_parameters("comment");

   if (linkerror)
      error_replace_param("comment");
}





/*******************************************************************************
*
*  c_index():
*     convert an index command into its target format
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL BOOLEAN c_index(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   char         s_tidx[256],      /* */
                s_entry[256],     /* */
                upr_entry[512];   /* */
   char         keyword[256];     /* */
   BOOLEAN      ret = TRUE;       /* */
   

   if (get_parameters(s, "index", 1) )
   {
      strcpy(s_tidx, Param[1]);

      if (inside_b4_macro)
      {
         if (desttype!=TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(s_tidx, TRUE);   
         }

         adjust_params_inside(Param[1]);
      }

      /* New in r6pl15 [NHz] */

      /* Set index in project file */

      sprintf(upr_entry, "%s", Param[1]); 

      save_upr_entry_index(1, sCurrFileName, upr_entry, uiCurrFileLine);

      if (no_index)
      {
         ret = replace_once(s, Param[0], Param[1]);
      }
      else
      {
         bCalledIndex = TRUE;

         switch (desttype)
         {
         case TOTEX:
         case TOPDL:
            auto_quote_texindex(s_tidx);
            sprintf(s_entry, "\\index{%s}", s_tidx);
            ret = delete_once(s, Param[0]);
            break;
            
            
         case TORTF:
            sprintf(s_entry, "{\\xe\\v %s}", Param[1]);

            if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
            {
               ret = FALSE;
               replace_once(s, Param[0], s_entry);
            }
            
/*          ret = delete_once(s, Param[0]); */
            break;
            
            
         case TOWIN:
         case TOWH4:
         case TOAQV:
            convert_tilde(Param[1]);
            
            del_internal_styles(Param[1]);
            
            replace_udo_quotes(Param[1]);
            
            strcpy(keyword, Param[1]);
            
            winspecials2ascii(keyword);
            
            sprintf(s_entry, "{K{\\footnote K %s}}", keyword);
            
            if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
            {
               ret = FALSE;
               replace_once(s, Param[0], s_entry);
            }
            
            break;
            
            
         case TOSTG:
         case TOAMG:
            delete_all_divis(Param[1]);
            
            convert_tilde(Param[1]);
            
            del_internal_styles(Param[1]);
            
            replace_udo_quotes(Param[1]);
            
            if (iUdopass == PASS2 && bInsideDocument)
            {
               index2stg(Param[1]);
               voutlnf("@index \"%s\"", Param[1]);
            }
            
            ret = delete_once(s, Param[0]);   /*r6pl9: Soll nicht angezeigt werden*/
            break;
            
            
         case TOINF:
            if (iUdopass == PASS2 && bInsideDocument)
            {
               voutlnf("@cindex %s", Param[1]);
               add_idxlist_item(Param[1], "", "");
            }
            
            ret = delete_once(s, Param[0]);
            break;
            
            
         case TOHPH:
            sprintf(s_entry, "<idx>%s<\\idx>", Param[1]);
            
            if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
            {
               ret = FALSE;
               replace_once(s, Param[0], s_entry);
            }
            
            break;
            
            
         case TOASC:
            delete_all_divis(Param[1]);
            
            convert_tilde(Param[1]);
            
            replace_udo_quotes(Param[1]);
            
            if (iUdopass == PASS2)
               add_idxlist_item(Param[1], "", "");
            
            ret = delete_once(s, Param[0]);
            break;
            
            
         case TOMHH:
            if (iUdopass == PASS2)
               output_htmlhelp_index(1, Param[1], "", "");
            
            ret = delete_once(s, Param[0]);
            break;


         default:
            ret = delete_once(s, Param[0]);
         }

      }
   }

   if (!ret)
   {
      error_replace_param("!index");
      return FALSE;
   }

   return TRUE;
}





/*******************************************************************************
*
*  c_single_index():
*     ??? (description)
*
*  Notes:
*     PL15: Die Nummer des Pass wird geprueft, damit bei Formaten, die die
*     Indexbefehle direkt ausgeben, nicht am Anfang der Zieldatei die
*     gesamten Indizes landen.
*
*     r6pl2: Stilbefehle und Umlaute werden umgewandelt.
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL BOOLEAN c_single_index(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   char         s_tidx[256],      /* */
                s_entry[256],     /* */
                upr_entry[512];   /* */
   char         keyword[256];     /* */
   BOOLEAN      ret = TRUE;       /* */
   

   if (get_parameters(s, "idx", 1) )
   {
      strcpy(s_tidx, Param[1]);

      if (inside_b4_macro)
      {
         if (desttype != TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(s_tidx, TRUE);   
         }

         adjust_params_inside(Param[1]);
      }

      /* New in r6pl15 [NHz] */

      /* Set index in project file */

      sprintf(upr_entry, "%s", Param[1]); 

      save_upr_entry_index(1, sCurrFileName, upr_entry, uiCurrFileLine);

      if (no_index)
      {
         ret = replace_once(s, Param[0], Param[1]);
      }
      else
      {
         bCalledIndex = TRUE;

         switch (desttype)
         {
            case TOTEX:
            case TOPDL:
               auto_quote_texindex(s_tidx);
               sprintf(s_entry, "%s\\index{%s}", Param[1], s_tidx);
               ret = replace_once(s, Param[0], s_entry);
               break;
               
               
            case TORTF:
               sprintf(s_entry, "{\\xe\\v %s}%s", Param[1], Param[1]);
               ret = replace_once(s, Param[0], s_entry);
               break;
               
               
            case TOWIN:
            case TOWH4:
            case TOAQV:
               convert_tilde(Param[1]);
               
               del_internal_styles(Param[1]);
               
               replace_udo_quotes(Param[1]);
               
               strcpy(keyword, Param[1]);
               
               winspecials2ascii(keyword);
               
               sprintf(s_entry, "{K{\\footnote K %s}}%s", keyword, Param[1]);
               
               if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
               {
                  ret = FALSE;
                  replace_once(s, Param[0], s_entry);
               }
               
               break;
               
               
            case TOSTG:
            case TOAMG:
               delete_all_divis(Param[1]);
               
               convert_tilde(Param[1]);
               
               del_internal_styles(Param[1]);
               
               replace_udo_quotes(Param[1]);
               
               if (iUdopass == PASS2 && bInsideDocument)
               {
                  index2stg(Param[1]);
                  voutlnf("@index \"%s\"", Param[1]);
               }
               
               ret = replace_once(s, Param[0], Param[1]);
               break;
               
               
            case TOINF:
               if (iUdopass == PASS2 && bInsideDocument)
               {
                  voutlnf("@cindex %s", Param[1]);
                  add_idxlist_item(Param[1], "", "");
               }
               
               ret = replace_once(s, Param[0], Param[1]);
               break;
               
               
            case TOHPH:
               sprintf(s_entry, "<idx>%s<\\idx>%s", Param[1], Param[1]);
               
               if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
               {
                  ret = FALSE;
                  replace_once(s, Param[0], s_entry);
               }
               
               break;
               
               
            case TOASC:
               delete_all_divis(Param[1]);
               
               convert_tilde(Param[1]);
               
               replace_udo_quotes(Param[1]);
               
               if (iUdopass == PASS2)
                  add_idxlist_item(Param[1], "", "");

               ret = replace_once(s, Param[0], Param[1]);
               break;
               
               
            case TOMHH:
               if (iUdopass == PASS2)
                  output_htmlhelp_index(1, Param[1], "", "");

               ret = replace_once(s, Param[0], Param[1]);
               break;
               
               
            default:
               ret = replace_once(s, Param[0], Param[1]);
         }

      }
   }

   if (!ret)
   {
      error_replace_param("!idx");
      return FALSE;
   }

   return TRUE;
}





/*******************************************************************************
*
*  c_double_index():
*     ??? (description)
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL BOOLEAN c_double_index(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   char         s_entry[1024],    /* */
                upr_entry[512];   /* */
   BOOLEAN      ret = TRUE;       /* */
   

   if (get_parameters(s, "idx", 2) )
   {

      if (inside_b4_macro)
      {
         if (desttype!=TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(Param[2], TRUE);   
         }   

         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
      }

      /* New in r6pl15 [NHz] */

      /* Set index in project file */

      sprintf(upr_entry, "%s:%s", Param[1], Param[2]); 

      save_upr_entry_index(2, sCurrFileName, upr_entry, uiCurrFileLine);

      if (no_index)
      {
         ret = replace_once(s, Param[0], Param[1]);
      }
      else
      {
         bCalledIndex = TRUE;

         switch (desttype)
         {
         case TOTEX:
         case TOPDL:
            auto_quote_texindex(Param[2]);
            sprintf(s_entry, "%s\\index{%s}", Param[1], Param[2]);
            ret = replace_once(s, Param[0], s_entry);
            break;
            
            
         case TORTF:
            sprintf(s_entry, "{\\xe\\v %s}%s", Param[2], Param[1]);
            ret = replace_once(s, Param[0], s_entry);
            break;
            
            
         case TOWIN:
         case TOWH4:
         case TOAQV:
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            
            del_internal_styles(Param[1]);
            del_internal_styles(Param[2]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            
            winspecials2ascii(Param[2]);
            
            sprintf(s_entry, "{K{\\footnote K %s}}%s", Param[2], Param[1]);
            
            if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
            {
               ret = FALSE;
               replace_once(s, Param[0], s_entry);
            }
            
            break;
            
            
         case TOSTG:
         case TOAMG:
            delete_all_divis(Param[1]);
            delete_all_divis(Param[2]);
            
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            
            del_internal_styles(Param[1]);
            del_internal_styles(Param[2]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            
            if (iUdopass == PASS2 && bInsideDocument)
            {
               index2stg(Param[2]);
               voutlnf("@index \"%s\"", Param[2]);
            }
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         case TOINF:
            if (iUdopass == PASS2 && bInsideDocument)
            {
               voutlnf("@cindex %s", Param[2]);
               add_idxlist_item(Param[2], "", "");
            }
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         case TOHPH:
            sprintf(s_entry, "<idx>%s<\\idx>%s", Param[2], Param[1]);
            
            if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
            {
               ret = FALSE;
               replace_once(s, Param[0], s_entry);
            }
            
            break;
            
         case TOASC:
            delete_all_divis(Param[1]);
            delete_all_divis(Param[2]);
            
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            
            if (iUdopass == PASS2)
               add_idxlist_item(Param[2], "", "");
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         case TOMHH:
            if (iUdopass == PASS2)
               output_htmlhelp_index(1, Param[2], "", "");
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         default:
            ret = replace_once(s, Param[0], Param[1]);
         }
      }
   }

   if (!ret)
   {
      error_replace_param("!idx");
      return FALSE;
   }

   return TRUE;
}





/*******************************************************************************
*
*  c_tripple_index():
*     ??? (description)
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL BOOLEAN c_tripple_index(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   char         s_entry[1024],    /* */
                upr_entry[512];   /* */
   BOOLEAN      ret = TRUE;       /* */
   

   if (get_parameters(s, "idx", 3) )
   {
      if (inside_b4_macro)
      {
         if (desttype!=TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(Param[2], TRUE);   
            auto_quote_chars(Param[3], TRUE);   
         }

         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
         adjust_params_inside(Param[3]);
      }

      /* New in r6pl15 [NHz] */

      /* Set index in project file */

      sprintf(upr_entry, "%s:%s:%s", Param[1], Param[2], Param[3]); 

      save_upr_entry_index(3, sCurrFileName, upr_entry, uiCurrFileLine);

      if (no_index)
      {
         ret = replace_once(s, Param[0], Param[1]);
      }
      else
      {
         bCalledIndex = TRUE;

         switch (desttype)
         {
         case TOTEX:
         case TOPDL:
            auto_quote_texindex(Param[2]);
            auto_quote_texindex(Param[3]);
            
            if (use_mirrored_indices)
            {
               sprintf(s_entry, "%s\\index{%s!%s}\\index{%s!%s}",
                  Param[1], Param[2], Param[3], Param[3], Param[2]);
            }
            else
            {
               sprintf(s_entry, "%s\\index{%s!%s}", Param[1], Param[2], Param[3]);
            }
            
            ret = replace_once(s, Param[0], s_entry);
            break;
            
            
         case TORTF:
            if (use_mirrored_indices)
            {
               sprintf(s_entry, "{\\xe\\v %s\\:%s}{\\xe\\v %s\\:%s}%s",
                  Param[2], Param[3], Param[3], Param[2], Param[1]);
            }
            else
            {
               sprintf(s_entry, "{\\xe\\v %s\\:%s}%s", Param[2], Param[3], Param[1]);
            }
            
            ret = replace_once(s, Param[0], s_entry);
            break;
            
            
         case TOWIN:
         case TOWH4:
         case TOAQV:
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            convert_tilde(Param[3]);
            
            del_internal_styles(Param[1]);
            del_internal_styles(Param[2]);
            del_internal_styles(Param[3]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[3]);
            
            winspecials2ascii(Param[2]);
            winspecials2ascii(Param[3]);
            
            if (use_mirrored_indices)
            {
               sprintf(s_entry, "{K{\\footnote K %s, %s}}{K{\\footnote K %s, %s}}%s",
                  Param[2], Param[3], Param[3], Param[2], Param[1]);
            }
            else
            {
               sprintf(s_entry, "{K{\\footnote K %s, %s}}%s", Param[2], Param[3], Param[1]);
            }
            
            if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
            {
               ret = FALSE;
               replace_once(s, Param[0], s_entry);
            }
            
            break;
            
            
         case TOSTG:
         case TOAMG:
            delete_all_divis(Param[1]);
            delete_all_divis(Param[2]);
            delete_all_divis(Param[3]);
            
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            convert_tilde(Param[3]);
            
            del_internal_styles(Param[1]);
            del_internal_styles(Param[2]);
            del_internal_styles(Param[3]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[3]);
            
            if (iUdopass == PASS2 && bInsideDocument)
            {
               index2stg(Param[2]);
               index2stg(Param[3]);
               voutlnf("@index \"%s, %s\"", Param[2], Param[3]);
               
               if (use_mirrored_indices)
               {
                  voutlnf("@index \"%s, %s\"", Param[3], Param[2]);
               }
            }
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         case TOINF:
            if (iUdopass==PASS2 && bInsideDocument)
            {
               voutlnf("@cindex %s, %s", Param[2], Param[3]);
               add_idxlist_item(Param[2], Param[3], "");
               
               if (use_mirrored_indices)
               {
                  voutlnf("@cindex %s, %s", Param[3], Param[2]);
                  add_idxlist_item(Param[3], Param[2], "");
               }
            }
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         case TOHPH:
            sprintf(s_entry, "<idx>%s, %s<\\idx>%s", Param[2], Param[3], Param[1]);
            
            if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
            {
               ret = FALSE;
               replace_once(s, Param[0], s_entry);
            }
            
            break;
            
            
         case TOASC:
            delete_all_divis(Param[1]);
            delete_all_divis(Param[2]);
            delete_all_divis(Param[3]);
            
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            convert_tilde(Param[3]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[3]);
            
            if (iUdopass == PASS2)
            {
               add_idxlist_item(Param[2], Param[3], "");
               
               if (use_mirrored_indices)
                  add_idxlist_item(Param[3], Param[2], "");
            }
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         case TOMHH:
            if (iUdopass == PASS2)
               output_htmlhelp_index(2, Param[2], Param[3], "");
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         default:
            ret = replace_once(s, Param[0], Param[1]);
         }
      }
   }

   if (!ret)
   {   error_replace_param("!idx");
      return FALSE;
   }

   return TRUE;

}





/*******************************************************************************
*
*  c_quadruple_index():
*     ??? (description)
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL BOOLEAN c_quadruple_index(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   char         s_entry[1024],    /* */
                upr_entry[512];   /* */
   BOOLEAN      ret = TRUE;       /* */
   

   if (get_parameters(s, "idx", 4) )
   {
      if (inside_b4_macro)
      {
         if (desttype!=TOSTG)
         {
            auto_quote_chars(Param[1], TRUE);   
            auto_quote_chars(Param[2], TRUE);
            auto_quote_chars(Param[3], TRUE);
            auto_quote_chars(Param[4], TRUE);
         }

         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
         adjust_params_inside(Param[3]);
         adjust_params_inside(Param[4]);
      }

      /* Set index in project file */

      sprintf(upr_entry, "%s:%s:%s:%s", Param[1], Param[2], Param[3], Param[4]); 

      save_upr_entry_index(4, sCurrFileName, upr_entry, uiCurrFileLine);

      if (no_index)
      {
         ret = replace_once(s, Param[0], Param[1]);
      }
      else
      {
         bCalledIndex = TRUE;

         switch (desttype)
         {
         case TOTEX:
         case TOPDL:
            auto_quote_texindex(Param[2]);
            auto_quote_texindex(Param[3]);
            auto_quote_texindex(Param[4]);
            
            sprintf(s_entry, "%s\\index{%s!%s!%s}", Param[1], Param[2], Param[3], Param[4]);
            ret = replace_once(s, Param[0], s_entry);
            break;
            
            
         case TORTF:
            sprintf(s_entry, "{\\xe\\v %s\\:%s\\:%s}%s", Param[2], Param[3], Param[4], Param[1]);
            ret = replace_once(s, Param[0], s_entry);
            break;
            
            
         case TOWIN:
         case TOWH4:
         case TOAQV:
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            convert_tilde(Param[3]);
            convert_tilde(Param[4]);
            
            del_internal_styles(Param[1]);
            del_internal_styles(Param[2]);
            del_internal_styles(Param[3]);
            del_internal_styles(Param[4]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[3]);
            replace_udo_quotes(Param[4]);
            
            winspecials2ascii(Param[2]);
            winspecials2ascii(Param[3]);
            winspecials2ascii(Param[4]);
            
            sprintf(s_entry, "{K{\\footnote K %s, %s, %s}}%s", Param[2], Param[3], Param[4], Param[1]);
            
            if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
            {
               ret = FALSE;
               replace_once(s, Param[0], s_entry);
            }
            
            break;
            
            
         case TOSTG:
         case TOAMG:
            delete_all_divis(Param[1]);
            delete_all_divis(Param[2]);
            delete_all_divis(Param[3]);
            delete_all_divis(Param[4]);
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            convert_tilde(Param[3]);
            convert_tilde(Param[4]);
            
            del_internal_styles(Param[1]);
            del_internal_styles(Param[2]);
            del_internal_styles(Param[3]);
            del_internal_styles(Param[4]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[3]);
            replace_udo_quotes(Param[4]);
            
            if (iUdopass == PASS2 && bInsideDocument)
            {
               index2stg(Param[2]);
               index2stg(Param[3]);
               index2stg(Param[4]);
               voutlnf("@index \"%s, %s, %s\"", Param[2], Param[3], Param[4]);
            }
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         case TOINF:
            if (iUdopass == PASS2 && bInsideDocument)
            {
               voutlnf("@cindex %s, %s, %s", Param[2], Param[3], Param[4]);
               add_idxlist_item(Param[2], Param[3], Param[4]);
            }
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         case TOHPH:
            sprintf(s_entry, "<idx>%s, %s, %s<\\idx>%s", Param[2], Param[3], Param[4], Param[1]);
            
            if (!insert_placeholder(s, Param[0], s_entry, s_entry) )
            {
               ret = FALSE;
               replace_once(s, Param[0], s_entry);
            }
            
            break;
            
            
         case TOASC:
            delete_all_divis(Param[1]);
            delete_all_divis(Param[2]);
            delete_all_divis(Param[3]);
            delete_all_divis(Param[4]);
            
            convert_tilde(Param[1]);
            convert_tilde(Param[2]);
            convert_tilde(Param[3]);
            convert_tilde(Param[4]);
            
            replace_udo_quotes(Param[1]);
            replace_udo_quotes(Param[2]);
            replace_udo_quotes(Param[3]);
            replace_udo_quotes(Param[4]);
            
            if (iUdopass == PASS2)
               add_idxlist_item(Param[2], Param[3], Param[4]);
               
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         case TOMHH:
            if (iUdopass == PASS2)
               output_htmlhelp_index(3, Param[2], Param[3], Param[4]);
            
            ret = replace_once(s, Param[0], Param[1]);
            break;
            
            
         default:
            ret = replace_once(s, Param[0], Param[1]);
         }
      }
   }

   if (!ret)
   {   error_replace_param("!idx");
      return FALSE;
   }

   return TRUE;
}





/*******************************************************************************
*
*  c_internal_time():
*     convert a time command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_internal_time(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   char         str[1024];        /* */
   BOOLEAN      flag;             /* */
   time_t       uhrzeit;          /* */
   struct tm   *timeptr;          /* */


   flag = FALSE;

   while (!flag && (get_parameters(s, "time", 1) == 1) )
   {
      if (inside_b4_macro)
         adjust_params_inside(Param[1]);

      time( &uhrzeit);
      timeptr = localtime (&uhrzeit);
      
      if (strlen(&Param[1][0]) > 1000)
         strcpy (str, "time parameter too long");
      else
         strftime(str, 1024, Param[1], timeptr);

      flag = !insert_placeholder(s, Param[0], str, Param[1]);

   }

   if (flag)
   {
      replace_once(s, Param[0], Param[1]);
      error_replace_param("!time");
   }
}





/*******************************************************************************
*
*  c_internal_image():
*     convert an img command into its target format
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_internal_image(

char           *s,                 /* */
const BOOLEAN   inside_b4_macro)   /* */
{
   int          pnr = 0,           /* */
                count;             /* */
   char         s_entry[1024],     /* */
                sGifSize[80],      /* */
                sGifName[512];     /* */
   BOOLEAN      flag;              /* */
   UWORD        uiW,               /* */
                uiH;               /* */
   char         closer[8] = "\0";  /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   flag = FALSE;
   
   count = get_nr_of_parameters("img",s); /* V 6.5.18 */
   
                                          /* V 6.5.18 */
   while (!flag && ((pnr = get_parameters(s, "img", count)) == 2 || pnr == 3) )
   {
      if (inside_b4_macro)
      {
         /* Fixed bug #0000055 in V6.5.2 [NHz] */
/*       if (desttype != TOSTG)
         {
            auto_quote_chars(Param[2], TRUE);   
         }
*/
   
         adjust_params_inside(Param[1]);
         adjust_params_inside(Param[2]);
         adjust_params_inside(Param[3]);  /* V 6.5.18 */
      }
   
      fsplit(Param[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
   
      replace_udo_quotes(Param[2]);
      replace_udo_quotes(Param[3]);       /* V 6.5.18 */
   
      switch (desttype)
      {
      case TOHAH:                         /* V6.5.17 */
      case TOHTM:
      case TOMHH:
         strcpy(tmp_suff, sDocImgSuffix);
         sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
         path_adjust_separator(Param[1]);
         
         uiW = uiH = 0;
         sGifSize[0] = EOS;
         
         if (!no_img_size)
         {
            if (my_stricmp(tmp_suff, ".gif") == 0)
            {
               strcpy(sGifName, Param[1]);
               strinsert(sGifName, old_outfile.path);
               strinsert(sGifName, old_outfile.driv);
               path_adjust_separator(sGifName);
         
               if (!get_gif_size(sGifName, &uiW, &uiH))
               {
                  error_read_gif (sGifName);
               }
            }
         }
         
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
         replace_char(Param[1], "\\", "/");
         
         if (no_images)                   /*r6pl2*/
         {
            strcpy(s_entry, Param[2]);
         }
         else                             /* Feature-Wunsch 0000070 V6.5.18 */
         {
            if (Param[3][0] != EOS)
            {
               sprintf(s_entry, "<img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s>",
                  Param[1], Param[2], Param[3], sGifSize, closer);
            }
            else
            {
               sprintf(s_entry, "<img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s>",
                  Param[1], Param[2], Param[2], sGifSize, closer);
            }
         }
         
         flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
         break;
         
      case TOHPH:
         strcpy(tmp_suff, sDocImgSuffix);
         sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
         replace_char(Param[1], "\\", "/");
         
         if (no_images)                   /*r6pl2*/
         {
            strcpy(s_entry, Param[2]);
         }
         else
         {
            sprintf(s_entry, "<graphic>%s<\\graphic>", Param[1]);
         }
         
         flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
         break;
         
      case TOWIN:
      case TOWH4:
      case TOAQV:
         strcpy(tmp_suff, ".bmp");
         sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
         replace_char(Param[1], "\\", "/");
         
         if (no_images)                   /*r6pl2*/
         {
            strcpy(s_entry, Param[2]);
         }
         else
         {
            sprintf(s_entry, " \\{bmc %s\\}", Param[1]);
         }
         
         flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
         break;
         
      case TOIPF:                         /*r6pl8*/
         strcpy(tmp_suff, ".bmp");
         sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
         
         if (no_images)                   /*r6pl2*/
         {
            strcpy(s_entry, Param[2]);
         }
         else
         {
            sprintf(s_entry, "\n:artwork runin name='%s'.\n", Param[1]);
         }
         
         flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
         break;
         
      /* New in r6.3pl3 [NHz] */
      case TORTF:
         strcpy(s_entry, "");
         
         flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
         break;
      
      /* New in V6.5.5 [NHz] */
      case TOKPS:
         strcpy(s_entry, Param[2]);
         c_vars(s_entry);
         replace_all(s_entry, KPSPC_S, ")");
         replace_all(s_entry, KPSPO_S, "(");
         
         flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
         break;

      default:
         strcpy(s_entry, Param[2]);
         flag = !insert_placeholder(s, Param[0], s_entry, Param[2]);
      }
   }
   
   if (flag)
   {
      replace_once(s, Param[0], Param[2]);
      error_replace_param("!img");
   }
   
   if (pnr != 0 && pnr == 1)
   {
      error_wrong_nr_parameters("!img");
   }
}





/*******************************************************************************
*
*  c_single_raw():
*     convert a raw command into its target format
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL BOOLEAN c_single_raw(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   BOOLEAN      flag;             /* */


   UNUSED(inside_b4_macro);
   
   if (get_parameters(s, "raw", 1))
   {
      flag = insert_placeholder(s, Param[0], Param[1], Param[1]);

      if (!flag)
      {
         replace_once(s, Param[0], Param[1]);
         error_replace_param("!raw");
         return FALSE;
      }

   }

   return TRUE;
}





/*******************************************************************************
*
*  c_double_raw():
*     convert a raw command into its target format
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL BOOLEAN c_double_raw(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   BOOLEAN      flag;             /* */


   UNUSED(inside_b4_macro);
   
   if (get_parameters(s, "raw", 2))
   {
      if (str_for_desttype(Param[1]))
      {
         flag = insert_placeholder(s, Param[0], Param[2], Param[2]);

         if (!flag)
         {
            delete_once(s, Param[0]);
            error_replace_param("!raw");
            return FALSE;
         }
      }
      else
      {
         delete_once(s, Param[0]);
      }
   }

   return TRUE;
}





/*******************************************************************************
*
*  c_internal_raw():
*     handle conversion of raw commands
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_internal_raw(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   int          nr;               /* */
   BOOLEAN      flag;             /* */
   

   if (strstr(s, "(!raw") == NULL)
      return;

   do
   {   
      nr = get_nr_of_parameters("raw", s);

      switch (nr)
      {
      case 0:
         flag = FALSE;
         break;
         
      case 1:
         flag = c_single_raw(s, inside_b4_macro);
         break;
         
      case 2:
         flag = c_double_raw(s, inside_b4_macro);
         break;
         
      default:
         error_wrong_nr_parameters("!raw");
         flag = FALSE;
      }

   } while (flag);
}





/*******************************************************************************
*
*  md_uses_parameters():
*     check if macro or definition uses parameters
*
*  Return:
*     FALSE: doesn't use parameters
*     TRUE : uses parametes
*
******************************************|************************************/

LOCAL BOOLEAN md_uses_parameters(

const char  *s)  /* ^ to macro/definition string */
{
   if (strstr(s, "(!0)") != NULL)
      return TRUE;
      
   if (strstr(s, "(!1)") != NULL)
      return TRUE;
      
   if (strstr(s, "(!2)") != NULL)
      return TRUE;
      
   if (strstr(s, "(!3)") != NULL)
      return TRUE;
      
   if (strstr(s, "(!4)") != NULL)
      return TRUE;
      
   if (strstr(s, "(!5)") != NULL)
      return TRUE;
      
   if (strstr(s, "(!6)") != NULL)
      return TRUE;
      
   if (strstr(s, "(!7)") != NULL)
      return TRUE;
      
   if (strstr(s, "(!8)") != NULL)
      return TRUE;
      
   if (strstr(s, "(!9)") != NULL)
      return TRUE;

   return FALSE;
}










/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  replace_variables():
*     adjust macros and definitions which contain variables
*
*  Example:
*     !macro Maus (!1) (!2) @ (!3), (!1)_(!2)@(!3).maus.de
*     MausNet:   (!Maus [Dirk] [Hagedorn] [MK2])
*
*     cmd   = Maus
*     entry = (!1) (!2) @ (!3), (!1)_(!2)@(!3).maus.de
*     s     = string with macro
*
*     -->
*     MausNet: Dirk Hagedorn @ MK2, Dirk_Hagedorn@MK2.maus.de
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_variables(

char        *s,             /* */
const char  *cmd,           /* */
const char  *entry)         /* */
{
   int       parms,         /* */
             i;             /* */
   char      p[16],         /* */
             without[128],  /* */
            *ptr;           /* ^ into string <s> */
   BOOLEAN   flag;          /* */

                                          /* PL10: (!macro) vorher loeschen */
   sprintf(without, "(!%s)", cmd);
   delete_all(s, without);

   flag = TRUE;
   
   while (flag && (parms = get_nr_of_parameters(cmd, s)) > 0)
   {
      if (parms > MAX_PARAMETERS)
      {
         error_too_many_parameters();
         return;
      }   

      get_parameters(s, cmd, parms);

      /* r6pl2: ptr statt s benutzen, damit die Parameter nur ab */
      /* der Stelle des/r Makros/Definition ersetzt werden und */
      /* nicht bereits davor. */
      
      /* Trotzdem werden auch (!1) etc. ersetzt, die nach den */
      /* Parameter-Befehle stehen. Dies wuerde aber einen */
      /* unheimlichen Umstand bedeuten (Ausschneiden, Ersetzen, */
      /* wieder Einfuegen: fuer jedes etwaige vorhandene Makro) */
      /* Da aber (!0) ... (!9) eh verboten sind, wird hier keine */
      /* Ruecksicht auf die Pappenheimer genommen, die UDO-Befehle */
      /* nicht quoten wollen, wie z.B. mit (!/0), (!/1) etc. */

      ptr = strstr(s, Param[0]);

                                          /* r6pl2: ptr statt s */
      if (replace_all(ptr, Param[0], entry) )
      {
         qdelete_all(ptr, "(!0)", 4);     /* r6pl2 */
         
         for (i = 0; i < MAX_PARAMETERS; i++)
         {
            sprintf(p, "(!%d)", i + 1);
            
            if (parms > i)
            {
                                          /* <???> */
               auto_quote_chars(Param[i + 1], TRUE);
               replace_all(ptr, p, Param[i+1]);
            }
            else
            {
               qdelete_all(ptr, p, 4);
            }
         }
      }
      else
      {
         flag = FALSE;
      }
   }

   if (!flag)
   {
      sprintf(without, "!%s", cmd);
      error_replace_param(without);
   }
}





/*******************************************************************************
*
*  reset_speccmds():
*     remove special format command placeholders from the text
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void reset_speccmds(void)
{
   int   i;  /* counter */
   

   if (speccmd_counter >= 0)
   {
      for (i = 0; i < speccmd_counter; i++)
      {
         if (speccmd[i].entry != NULL)
         {
            um_free(speccmd[i].entry);
            speccmd[i].entry = NULL;
         }

         speccmd[i].magic[0] = EOS;
      }
   }

   speccmd_counter = -1;
}





/*******************************************************************************
*
*  add_speccmd():
*     insert special format commands into the text as placeholders
*
*  Notes:
*     These format commands don't contain visible text!
*
*  Return:
*      TRUE: ???
*     FALSE: failure
*
******************************************|************************************/

GLOBAL BOOLEAN add_speccmd(

char       *entry)  /* */
{
   size_t   sl;     /* */
   char    *ptr;    /* */
   

   if (speccmd_counter < MAXSPECCMDS)
   {
      speccmd_counter++;

      sl = strlen(entry);
      
      ptr = (char *)(um_malloc(sl * sizeof(char) + 1));
      
      if (ptr == NULL)
      {
         error_malloc_failed();
         speccmd_counter--;
         return FALSE;
      }

      if (speccmd_counter + OFFSET_SPECCMD == (int)'~')
      {
         speccmd_counter++;
      }
      
      if (speccmd_counter + OFFSET_SPECCMD == (int)127)
      {
         speccmd_counter++;
      }

      sprintf(speccmd[speccmd_counter].magic, "\033%c%c\033", C_SPECCMD_MAGIC, speccmd_counter + OFFSET_SPECCMD);

      speccmd[speccmd_counter].entry = ptr;

      strcpy(speccmd[speccmd_counter].entry, entry);

      return TRUE;
   }

   return FALSE;
}





/*******************************************************************************
*
*  insert_speccmd():
*     insert special format command placeholders into the text
*
*  Notes:
*     These format commands don't contain visible text!
*
*  Return:
*      TRUE: ???
*     FALSE: failure
*
******************************************|************************************/

GLOBAL BOOLEAN insert_speccmd(

char        *s,      /* */
const char  *rep,    /* */
char        *entry)  /* */
{
   if (add_speccmd(entry))
   {
      if (replace_once(s, rep, speccmd[speccmd_counter].magic))
      {
         return TRUE;
      }
   }

   return FALSE;
}





/*******************************************************************************
*
*  replace_speccmds():
*     replace special format command placeholders in the text
*
*  Notes:
*     These format commands don't contain visible text!
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_speccmds(

char             *s)              /* */
{
   register int   i;              /* */
   int            replaced = -1;  /* */

   if (speccmd_counter >= 0)
   {
      if (strstr(s, ESC_SPECCMD_MAGIC) == NULL)
         return;


      /* PL10: Rueckwaerts ersetzen, da ein Platzhalter auch in */
      /* einem Platzhalter stecken kann! */
      
      for (i = speccmd_counter; i >= 0; i--)
      {
         if (replace_once(s, speccmd[i].magic, speccmd[i].entry))
         {
            speccmd[i].magic[0] = EOS;
            replaced++;
         }
      }
      
      if (replaced == speccmd_counter)
      {
         reset_speccmds();
      }
   }
}





/*******************************************************************************
*
*  reset_placeholders():
*     handle links and other internal commands
*
*  Notes:
*     This has to be done BEFORE the tokenization takes place!
*
*  Format:
*     (!link [text] [destination])
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void reset_placeholders(void)
{
   int   i;  /* counter */


   if (phold_counter >= 0)
   {
      for (i = 0; i < phold_counter; i++)
      {
         if (phold[i].entry != NULL)
         {
            um_free(phold[i].entry);
            phold[i].entry = NULL;
         }

         if (phold[i].text != NULL)
         {
            um_free(phold[i].text);
            phold[i].text= NULL;
         }

         phold[i].magic[0] = EOS;
      }
   }

   phold_counter = -1;
}





/*******************************************************************************
*
*  add_placeholder():
*     ??? (description missing)
*
*  Return:
*      TRUE: everything's fine
*     FALSE: error
*
******************************************|************************************/

GLOBAL BOOLEAN add_placeholder(

char       *entry,    /* */
char       *rawtext)  /* */
{
   size_t   el,       /* entry length */
            tl;       /* text length */
   char    *eptr,     /* */
           *tptr;     /* */
           

   if (phold_counter < MAXPHOLDS)
   {
      phold_counter++;

      el = strlen(entry);
      
      eptr = (char *)(um_malloc(el * sizeof(char) + 1));
      
      if (eptr == NULL)
      {
         error_malloc_failed();
         phold_counter--;
         return FALSE;
      }

      tl = strlen(rawtext);
      
      tptr = (char *)(um_malloc(tl * sizeof(char) + 1));
      
      if (tptr == NULL)
      {
         error_malloc_failed();
         um_free(eptr);
         phold_counter--;
         return FALSE;
      }

      sprintf(phold[phold_counter].magic, "\033%c%04i\033", C_PHOLD_MAGIC, phold_counter + OFFSET_PHOLD);

      phold[phold_counter].entry = eptr;
      phold[phold_counter].text  = tptr;

      strcpy(phold[phold_counter].entry, entry);
      strcpy(phold[phold_counter].text, rawtext);

      return TRUE;
   }
   else
      error_too_many_placeholder();   

   return FALSE;
}





/*******************************************************************************
*
*  insert_placeholder():
*     ??? (description missing)
*
*  Return:
*      TRUE: everything's fine
*     FALSE: error
*
******************************************|************************************/

GLOBAL BOOLEAN insert_placeholder(

char        *s,        /* */
const char  *rep,      /* */
char        *entry,    /* */
char        *rawtext)  /* */
{
   if (add_placeholder(entry, rawtext))
   {
      if (replace_once(s, rep, phold[phold_counter].magic))
         return TRUE;
   }

   return FALSE;
}





/*******************************************************************************
*
*  replace_placeholders():
*     replace the internal placeholder commands by human-readable content
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_placeholders(

char             *s)              /* ^ line */
{
   register int   i;              /* counter */
   int            replaced = -1;  /* */

   
   if (phold_counter >= 0)
   {
      if (strstr(s, ESC_PHOLD_MAGIC) == NULL)
         return;

      /* PL10: Rueckwaerts ersetzen, da ein Platzhalter auch in */
      /* einem Platzhalter stecken kann! */
      
      for (i = phold_counter; i >= 0; i--)
      {
         if (phold[i].magic[0] != EOS)
         {
            if (replace_once(s, phold[i].magic, phold[i].entry))
            {
               phold[i].magic[0] = EOS;   /* clear magic */
               replaced++;
            }
         }
      }
      
      if (replaced == phold_counter)
         reset_placeholders();
   }
}





/*******************************************************************************
*
*  replace_placeholders_text():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_placeholders_text(

char             *s)  /* */
{
   register int   i;  /* counter */
   

   if (phold_counter >= 0)
   {
      if (strstr(s, ESC_PHOLD_MAGIC) == NULL)
         return;

      for (i = 0; i <= phold_counter; i++)
         replace_once(s, phold[i].magic, phold[i].text);
   }
}





/*******************************************************************************
*
*  pholdlen():
*     return length of placeholder text
*
*  return:
*     length of placeholder text
*     0
*
******************************************|************************************/

GLOBAL size_t pholdlen(

int   i)  /* # of desired placeholder */
{
   if (i >= 0 && i <= MAXPHOLDS)
   {
      if (phold[i].text != NULL)
      {
         return(strlen(phold[i].text));
      }
   }

   return 0;
}





/*******************************************************************************
*
*  c_internal_index():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_internal_index(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   int          nr;               /* */
   BOOLEAN      flag;             /* */
   BOOLEAN      has_idx,          /* */
                has_index;        /* */


   has_idx   = (strstr(s, "(!idx")   != NULL);
   has_index = (strstr(s, "(!index") != NULL);

   if (has_idx)
   {
      do
      {   
         nr = get_nr_of_parameters(CMD_IDX, s);

         switch (nr)
         {
         case 0:
            flag = FALSE;
            break;
            
         case 1:
            flag = c_single_index(s, inside_b4_macro);
            break;
            
         case 2:
            flag = c_double_index(s, inside_b4_macro);
            break;
            
         case 3:
            flag = c_tripple_index(s, inside_b4_macro);
            break;
            
         case 4:
            flag = c_quadruple_index(s, inside_b4_macro);
            break;
            
         default:
            error_wrong_nr_parameters("!idx");
            flag = FALSE;
         }

      } while (flag == TRUE);
   }


   if (has_index)                         /* r6pl6: Unterstuetzung fuer (!index [...]) */
   {
      do
      {   
         nr = get_nr_of_parameters("index", s);

         switch (nr)
         {
         case 0:
            flag = FALSE;
            break;
            
         case 1:
            flag = c_index(s, inside_b4_macro);
            break;
            
         default:
            error_wrong_nr_parameters("!index");
            flag = FALSE;
         }

      }  while (flag == TRUE);
   }
}





/*******************************************************************************
*
*  c_commands_inside():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_commands_inside(

char           *s,                /* */
const BOOLEAN   inside_b4_macro)  /* */
{
   if (strstr(s, "(!") == NULL)           /* wrong format */
      return;

   c_link(s, inside_b4_macro);
   c_url(s, inside_b4_macro);
   c_xlink(s, inside_b4_macro);
   c_ilink(s, inside_b4_macro);
   c_plink(s, inside_b4_macro);
   c_plabel(s, inside_b4_macro);          /* New in V6.5.9 [NHz] */
   c_nolink(s, inside_b4_macro);
   c_comment(s, inside_b4_macro);
   c_internal_index(s, inside_b4_macro);
   c_internal_time(s, inside_b4_macro);   /* V 6.5.19 */
   c_internal_image(s, inside_b4_macro);
   c_internal_raw(s, inside_b4_macro);

}





/*******************************************************************************
*
*  replace_hyphens():
*     replace word with hyphenated word in document
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_hyphens(

char      *s)  /* ^ character */
{
   UWORD   h;  /* hyphen index */

        
   if (hyphen_counter == 0)
      return;

   for (h = 0; h < hyphen_counter; h++)   /* check whole list of hyphenated words */
   {
      if (hyphen[h] != NULL)              /* add hyphens to word */
      {
         replace_all(s, hyphen[h]->solo, hyphen[h]->hyphen);
      }
   }
}





/*******************************************************************************
*
*  add_hyphen():
*     add hyphen to list of hyphens
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void add_hyphen(void)
{
   HYPHEN  *p;  /* ^ hyphen structure */


   switch (desttype)
   {
   case TOWIN:
   case TOWH4:
   case TOAQV:
   case TORTF:
   case TOHAH:                            /* V6.5.17 */
   case TOHTM:
   case TOMHH:
      return;                             /* these formats don't support hyphenation rules (yet) */
   }


   if (hyphen_counter >= MAXHYPHEN)       /* check # of hyphens overflow */
   {
      error_too_many_hyphens();
      return;
   }

   if (token_counter <= 1)                /* only "!hyphen" in the line? */
   {
      error_missing_parameter("!hyphen");
      return;
   }

                                          /* create space for hyphen structure */
   p = (HYPHEN *)um_malloc(sizeof(HYPHEN));

   if (p == NULL)                         /* no free memory? */
   {
      error_malloc_failed();
      return;
   }

   tokcpy2(p->hyphen, HYPHEN_LEN + 1);    /* copy   hyphenated word */
   tokcpy2(p->solo,   HYPHEN_LEN + 1);    /* buffer hyphenated word */

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      /* Die Tokens sind leider vorher schon durch c_vars gelaufen */
      /* Dabei wurden auch (!ck) usw. bereits in "ck umgewandelt */
      /* Problem: replace_hyphens() findet Dru"cker dann nicht */

      qdelete_all(p->solo, "\\-", 2);
      break;

   default:
      delete_all_divis(p->solo);
   }

   hyphen[hyphen_counter] = p;
   hyphen_counter++;
}





/*******************************************************************************
*
*  replace_macros():
*     replace macro (!%s) with macro content in document
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_macros(

char      *s)  /* ^ found macro string "(!%s)" in document */
{
   UWORD   i;  /* counter */
   

   if (strstr(s, "(!") == NULL)           /* wrong format */
      return;

   for (i = 0; i < macro_counter; i++)    /* check all macros */
   {
      if (macros[i] != NULL)              /* valid macro */
      {
         if (macros[i]->vars)             /* replace by macro content with parameters */
            replace_variables(s, macros[i]->name, macros[i]->entry);
         else                             /* replace by macro content */
            replace_all(s, macros[i]->name, macros[i]->entry);
      }
   }
}





/*******************************************************************************
*
*  add_macro():
*     add macro to list of macros
*  Notes:
*     The "!macro ..." data which are handled here can be found in token[].
*
*  Return:
*     FALSE: error
*     TRUE : macro has been added successfully
*
******************************************|************************************/

GLOBAL BOOLEAN add_macro(void)
{
   int      i;           /* counter */
   MACROS  *p;           /* ^ to macro */
   char     entry[512];  /* string buffer */

   if (macro_counter >= MAXMACROS)        /* check # of macros overflow */
   {
      error_too_many_macros();
      return FALSE;
   }

   if (token_counter <= 1)                /* only "!macro" in the line? */
   {
      error_missing_parameter(CMD_MACRO);
      return FALSE;
   }

   if (strlen(token[1]) > MACRO_NAME_LEN) /* macro name too long? */
   {
      error_long_macro_name(MACRO_NAME_LEN);
      return FALSE;
   }

                                          /* create space for a macro */
   p = (MACROS *)um_malloc(sizeof(MACROS));

   if (p == NULL)                         /* no free memory! */
   {
      error_malloc_failed();
      return FALSE;
   }

   entry[0] = EOS;                         /* erase string buffer */

   if (token_counter >= 2)                 /* "!macro" and at least on other token */
   {
      for (i = 2; i < token_counter; i++)  /* skip "!macro" */
      {
                                           /* get macro name */
         um_strcat(entry, token[i], 512, "add_macro[1]");
         
         if (i < token_counter - 1)        /* get macro content */
            um_strcat(entry, " ", 512, "add_macro[2]");
      }
   }


/* fd:2010-05-08: faded for macros!
   auto_quote_chars(entry, FALSE);
*/

   replace_macros(entry);
   replace_defines(entry);
   
   c_divis(entry);
   c_vars(entry);


   if (strlen(entry) > MACRO_CONT_LEN)     /* macro content too long? */
   {
      error_long_macro_cont(MACRO_CONT_LEN);
      um_free(p);
      return FALSE;
   }

                                           /* copy collected content to structure */
   um_strcpy(p->entry, entry, MACRO_CONT_LEN + 1, "add_macro[3]");

   if (md_uses_parameters(p->entry) )      /* macro uses parameters */
   {
      um_strcpy(p->name, token[1], MACRO_NAME_LEN + 1, "add_macro[4]");
      p->vars = TRUE;
   }
   else                                    /* normal macro */
   {
      sprintf(p->name, "(!%s)", token[1]);
      token[1][0]= EOS;
      p->vars = FALSE;
   }

   macros[macro_counter] = p;
   macro_counter++;

   return TRUE;   
}





/*******************************************************************************
*
*  replace_defines():
*     replace definition (!%s) with definition content in document
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_defines(

char      *s)  /* ^ found definition string "(!%s)" in document */
{
   UWORD   i;  /* counter */


   if (strstr(s, "(!") == NULL)           /* wrong format */
      return;

   for (i = 0; i < define_counter; i++)   /* check all definitions */
   {
      if (defs[i] != NULL)                /* valid definition */
      {
         if (defs[i]->vars)               /* replace by content with parameters */
            replace_variables(s, defs[i]->name, defs[i]->entry);
         else                             /* replace by content */
            replace_all(s, defs[i]->name, defs[i]->entry);
      }
   }
}





/*******************************************************************************
*
*  add_define():
*     add definition to list of definitions
*
*  Notes:
*     The "!define ..." data which are handled here can be found in token[].
*
*  Return:
*     FALSE: error
*     TRUE : definition has been added successfully
*
******************************************|************************************/

GLOBAL BOOLEAN add_define(void)
{
   int    i;           /* counter */
   DEFS  *p;           /* ^ to definition */
   char   entry[512];  /* string buffer */


   if (define_counter >= MAXDEFS)         /* check # of definitions overflow */
   {
      error_too_many_defines();
      return FALSE;
   }

   if (token_counter <= 1)                /* only "!define" in the line? */   
   {
      error_missing_parameter(CMD_DEFINE);
      return FALSE;
   }

   if (strlen(token[1]) > DEFINE_NAME_LEN)/* definition name too long? */   
   {
      error_long_define_name(DEFINE_NAME_LEN);
      return FALSE;
   }

   p = (DEFS *)um_malloc(sizeof(DEFS));    /* create space for a definition */

   if (p == NULL)                          /* no free memory! */
   {
      error_malloc_failed();
      return FALSE;
   }

   entry[0] = EOS;                         /* erase string buffer */

   if (token_counter >= 2)                 /* "!define" + at least one other token */
   {
      for (i = 2; i < token_counter; i++)  /* skip "!define" */
      {
                                           /* get definition name */
         um_strcat(entry, token[i], 512, "add_define[1]");
         
         if (i < token_counter - 1)        /* get definition content */ 
            um_strcat(entry, " ", 512, "add_define[2]");
      }
   }

   if (strlen(entry) > DEFINE_CONT_LEN)    /* definition content too long? */
   {
      error_long_define_cont(DEFINE_CONT_LEN);
      um_free(p);
      return FALSE;
   }

                                           /* copy collected content to structure */
   um_strcpy(p->entry, entry, MACRO_CONT_LEN + 1, "add_define[3]");


   /* --- check if !define uses parameters --- */

   if (md_uses_parameters(p->entry) )      /* definition uses parameters */
   {
      um_strcpy(p->name, token[1], MACRO_NAME_LEN+1, "add_define[4]");
      p->vars = TRUE;
   }
   else                                    /* normal definition */
   {
      sprintf(p->name, "(!%s)", token[1]);
      token[1][0] = EOS;
      p->vars = FALSE;
   }

   defs[define_counter] = p;
   define_counter++;

   return TRUE;   
}





/*******************************************************************************
*
*  init_module_par():
*     initialize all arrays used in this module
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_par(void)
{
   int   i;  /* counter */

   phold_counter= -1;                     /* first of all, everything should be empty */

   for (i = 0; i < MAXPHOLDS; i++)
   {
      phold[i].magic[0] = EOS;
      phold[i].entry    = NULL;
      phold[i].text     = NULL;
   }

   hyphen_counter = 0;
   
   for (i = 0; i < MAXHYPHEN; i++)
      hyphen[i] = NULL;

   macro_counter = 0;
   
   for (i = 0; i < MAXMACROS; i++)
      macros[i] = NULL;

   define_counter = 0;
   
   for (i = 0; i < MAXDEFS; i++)
      defs[i] = NULL;
}





/*******************************************************************************
*
*  exit_module_par():
*     release all arrays used in this module
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void exit_module_par(void)
{
/*
   r6.3.19[vj]: Der folgende Code wurde auskommentiert, um zu ueberpruefen,
   ob sich hieraus ein Geschwindigkeitsvorteil erlangen laesst. Wird der
   Speicher hier nicht freigegeben, wird das spaeter um_exit tun,
   das die Speicherbereiche viel effizienter freigeben kann.
   Bitte nicht loeschen, da er spaeter vielleicht wieder rein kommt!

   int   i;

   for (i = MAXMACROS - 1; i >= 0; i--)
   {
      if (macros[i] != NULL)
         um_free(macros[i]);
   }

   for (i = MAXDEFS - 1; i >= 0; i--)
   {
      if (defs[i] != NULL)
         um_free(defs[i]);
   }

   for (i = MAXHYPHEN - 1; i >= 0; i--)
   {
      if (hyphen[i] != NULL)
         um_free(hyphen[i]);
   }
*/

   reset_placeholders();
}


/* +++ EOF +++ */
