/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : env.c
*  Symbol prefix: env
*
*  Description  : This module handles the environment routines which manage the 
*                 output of various environments and prepare them for 
*                 token_output().
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
*  2008:
*    fd  Nov 14: indexudo.html now capitalizes the A-Z jump labels (issue #76 solved)
*  2009:
*    ggs Jan 11: Bullet for the !begin_itemize, will always use in ST-Guide
*    fd  Jun 04: !docinfo [translator] introduced
*    fd  Jun 08: TAB -> '   '
*  2010:
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*    fd  Feb 03: file reformatted and tidied up
*    fd  Feb 05: c_end_enumerate() outputs an empty HTML code line (for readability)
*    fd  Feb 08: issue #79 fixed (weird empty lines on "!autoref []" in description environments
*    fd  Feb 17: win2sys() -> recode_chrtab()
*    fd  Feb 23: UDO_PL -> UDO_BUILD (no more patchlevels)
*    fd  Feb 27: HTML output for ENV_DESC, ENV_LIST + other environments adjusted
*
******************************************|************************************/

/*******************************************************************************
*
*     CONSTANTS
*
******************************************|************************************/

#ifndef ID_ENV_C
#define ID_ENV_C
const char *id_env_c= "@(#) env.c       $DATE$";
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
#include "portab.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "abo.h"
#include "cfg.h"
#include "chr.h"
#include "file.h"
#include "img.h"
#include "msg.h"
#include "par.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "tp.h"
#include "udo.h"
#include "gui.h"

#include "export.h"
#include "env.h"
#include "udo2ps.h"
#include "udo2pdf.h"





/*******************************************************************************
*
*     UNINITIALIZED VARIABLES
*
******************************************|************************************/

LOCAL int   env_kind[MAXENVLEVEL + 1];    /* Art der Umgebung (LIST_BOLD, ... */
LOCAL int   enum_count[MAXENVLEVEL + 1];  /* Item-Zaehler fuer enumerate */

LOCAL int   cent_level;                   /* Zaehler fuer center-Umgebungen */
LOCAL int   flushright_level;             /* Zaehler fuer flushright-Umgebungen */
LOCAL int   flushleft_level;              /* Zaehler fuer flushleft-Umgebungen */
LOCAL int   quot_level;                   /* Zaehler fuer quote-Umgebungen */

LOCAL char   itemchar[MAXENVLEVEL+1][64]; /* Zeichen fuer Itemize-Umgebung */


LOCAL BOOLEAN   bCalledBeginAppendix;     /* */
LOCAL BOOLEAN   bCalledEndAppendix;       /* */

LOCAL int   pre_linedraw_charset;

LOCAL const PAPERFORMAT paperSize[MAXPAPERSIZE]=
{
   { "A3PORTRAIT",   2970, 4200,  842, 1191, 1136, 85,  780, 72, 0, 0, FALSE},
   { "A3LANDSCAPE",  4200, 2970, 1191,  842,  780, 72, 1119, 72, 0, 0, TRUE },
   { "A4PORTRAIT",   2100, 2970,  595,  842,  780, 85,  540, 72, 0, 0, FALSE},
   { "A4LANDSCAPE",  2970, 2100,  842,  595,  530, 72,  770, 72, 0, 0, TRUE },
   { "A5PORTRAIT",   1485, 2100,  421,  595,  530, 85,  366, 72, 0, 0, FALSE},
   { "A5LANDSCAPE",  2100, 1485,  595,  421,  356, 72,  523, 72, 0, 0, TRUE },
};





/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

LOCAL int strlen_prev_indent(void);
LOCAL void strcat_prev_indent(char *s);
LOCAL void strcpy_prev_indent(char *s);

LOCAL void set_env_short(const int el, const char *s);
LOCAL BOOLEAN check_iEnvLevel(void);
LOCAL BOOLEAN check_env_end(const int etype, const int ekind, const char *ecomm);

LOCAL void end_env_output_line(const int el);

LOCAL char *itoenum(int level, int *count, char *string);
LOCAL char *strcat_blanks(char *string, int count);
LOCAL void add_description(void);

LOCAL void c_begin_list(int listkind);
LOCAL void c_end_list(int listkind);










/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*     CONTROL ROUTINES
*
******************************************|************************************/

/*******************************************************************************
*
*  set_env_short():
*     Setzt das short-Flag. Falls kein !short angegeben wurde, so wird
*     ein eventuell gesetztes Flag der aeusseren Umgebung vererbt.
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void set_env_short(

const int    el,  /* */
const char  *s)   /* */
{
   if (use_short_envs)
   {
      bEnvShort[el] = TRUE;
      return;
   }
   
   bEnvShort[el] = (strstr(s, "!short") != NULL);

   if (!bEnvShort[el])
   {
      if (el > 1 && bEnvShort[el - 1])
      {
         bEnvShort[el] = TRUE;
      }
   }
}





/*******************************************************************************
*
*  check_iEnvLevel():
*     check if maximum evironment level depth has been exceeded
*
*  Return:
*     TRUE: all OK
*    FALSE: max. depth exceeded
*
******************************************|************************************/

LOCAL BOOLEAN check_iEnvLevel(void)
{
   if (iEnvLevel >= MAXENVLEVEL - 1)
   {
      error_too_many_env();
      return FALSE;
   }
   
   return TRUE;
}





/*******************************************************************************
*
*  check_env_end():
*     check if !end_* fits to last !begin_*
*
*  Notes:
*     Environments have to be closed properly, e.g. 
*     !end_itemize has to follow !begin_itemize, not another !begin_*.
*     When e.g. !end_enumerate follows !begin_itemize, an error message
*     has to be thrown.
*
*  Return:
*     TRUE: all OK
*    FALSE: wrong !end_*
*
******************************************|************************************/

LOCAL BOOLEAN check_env_end(

const int    etype,  /* ENV_ITEM, ENV_ENUM, etc. */
const int    ekind,  /* LIST_NORMAL, LIST_BOLD, etc. */
const char  *ecomm)  /* used command (for error message) */
{
   if (iEnvLevel <= 0)
      return TRUE;
   

   if (    (iEnvType[iEnvLevel] != etype)
        || (iEnvType[iEnvLevel] == etype && env_kind[iEnvLevel] != ekind)
      )
   {
      switch (iEnvType[iEnvLevel])
      {
      case ENV_ITEM:
         error_wrong_end(CMD_BEGIN_ITEMIZE, ecomm);
         break;
         
      case ENV_ENUM:
         error_wrong_end(CMD_BEGIN_ENUMERATE, ecomm);
         break;
         
      case ENV_DESC:
         error_wrong_end(CMD_BEGIN_DESCRIPTION, ecomm);
         break;
         
      case ENV_LIST:
         switch (env_kind[iEnvLevel])
         {
         case LIST_BOLD:
            error_wrong_end(CMD_BEGIN_BLIST, ecomm);
            break;
            
         case LIST_ITALIC:
            error_wrong_end(CMD_BEGIN_ILIST, ecomm);
            break;
            
         case LIST_TYPEWRITER:
            error_wrong_end(CMD_BEGIN_TLIST, ecomm);
            break;
            
         default:
            error_wrong_end(CMD_BEGIN_XLIST, ecomm);
         }
      }
      
      return FALSE;
   }

   return TRUE;
}





/*******************************************************************************
*
*  check_environments_node():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void check_environments_node(void)
{
   int   i;  /* counter */

   
   if (iEnvLevel <= 0)
      return;
   

   for (i = iEnvLevel; i >= 1; i--)
   {
      switch (iEnvType[i])
      {
      case ENV_ITEM:
         error_missing_end(CMD_END_ITEMIZE);
         break;
         
      case ENV_DESC:
         error_missing_end(CMD_END_DESCRIPTION);
         break;
         
      case ENV_ENUM:
         error_missing_end(CMD_END_ENUMERATE);
         break;
         
      case ENV_LIST:
         switch (env_kind[iEnvLevel])
         {
         case LIST_BOLD:
            error_missing_end(CMD_END_BLIST);
            break;
            
         case LIST_ITALIC:
            error_missing_end(CMD_END_ILIST);
            break;
            
         case LIST_TYPEWRITER:
            error_missing_end(CMD_END_TLIST);
            break;
            
         default:
            error_missing_end(CMD_END_XLIST);
         }
         
         break;
         
      case ENV_QUOT:
         error_missing_end(CMD_END_QUOTE);
         break;
         
      case ENV_CENT:
         error_missing_end(CMD_END_CENTER);
         break;
         
      case ENV_RIGH:
         error_missing_end(CMD_END_RIGHT);
         break;
         
      case ENV_LEFT:
         error_missing_end(CMD_END_LEFT);
      }
   }


   /* --- Noch begonnene Umgebungen automatisch beenden --- */

   for (i = iEnvLevel; i >= 1; i--)
   {
      switch (iEnvType[i])
      {
      case ENV_ITEM:
         c_end_itemize();
         break;
         
      case ENV_DESC:
         c_end_description();
         break;
         
      case ENV_ENUM:
         c_end_enumerate();
         break;
         
      case ENV_QUOT:
         c_end_quote();
         break;
         
      case ENV_CENT:
         c_end_center();
         break;
         
      case ENV_RIGH:
         c_end_flushright();
         break;
         
      case ENV_LEFT:
         c_end_flushleft();
         break;
         
      case ENV_LIST:
         switch (env_kind[iEnvLevel])
         {
         case LIST_BOLD:
            c_end_blist();
            break;
            
         case LIST_ITALIC:
            c_end_ilist();
            break;
            
         case LIST_TYPEWRITER:
            c_end_tlist();
            break;
            
         default:
            c_end_xlist();
         }
      }
   }
}





/*******************************************************************************
*
*  end_env_output_line():
*     output empty line after end of compressed environment
*
*  Notes:
*     Falls eine Umgebung beendet wird, die komprimiert dargestellt werden soll, 
*     so muss eine Leerzeile ausgegeben werden, da dies nicht in token_output() 
*     geschieht, da ja dort die Umgebung noch aktiv ist, wenn die letzte Zeile 
*     des Absatzes ausgegeben wird. Verstanden? ;-)
* 
*     Aber die Leerzeile darf nur dann ausgegeben werden, wenn nicht noch eine 
*     uebergeordnete komprimierte Umgebung vorhanden ist.
*
*     iEnvLevel cannot be used here, because it has already been decreased in the
*     relevant !end_* routines.
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void end_env_output_line(

const int    el)            /* environment level to check */
{
   BOOLEAN   flag = FALSE;  /* */
   
   switch (el)
   {
   case 0:                                /* only possible on output_end_verbatim() */
      if (iEnvLevel == 0 || (iEnvLevel > 0 && !bEnvShort[iEnvLevel]) )
         flag = TRUE;
         
      break;
      
   case 1:                               /* Letzte Umgebung, also Leerzeile, falls komprimiert */
      flag = bEnvShort[el];
      break;
      
   default:                              /* Leerzeile nur dann ausgeben, falls die aeussere   */
                                         /* Umgebung nicht komprimiert ist UND die aktuelle   */
                                         /* nicht komprimiert ist.                     */
      if (bEnvShort[el] && !bEnvShort[el - 1])
         flag = TRUE;
   }
   
   if (flag)
   {
      switch (desttype)
      {
      case TOWIN:
      case TOWH4:
      case TOAQV:
      case TORTF:
         outln("\\par");
         break;
         
      case TOHAH:
      case TOHTM:
      case TOMHH:
#if 0   /* r6pl6*/
         outln("</p>");   
#endif
         break;

      case TOIPF:
         /* Hier keine Leerzeile */
         break;

      case TOKPS:
         outln("newline");
         break;

      default:
         outln("");
      }
   }
}





/*******************************************************************************
*
*     HELP ROUTINES
*
******************************************|************************************/

/*******************************************************************************
*
*  itoenum():
*     get number for enumerate environment
*
*  Notes:
*     The number depends on the environment level and item counter.
*
*     TeX-like:
*        2.
*       (b)
*       ii.
*        B.
*        3.
*       (c)
*
*  Return:
*     formatted number string
*
******************************************|************************************/

LOCAL char *itoenum(

int    level,   /* enumeration level */
int   *count,   /* item counter */
char  *string)  /* ^ string buffer */
{
   switch (level)
   {
   case 1:
   case 5:
      sprintf(string, "%d.", *count);
      break;
      
   case 2:
   case 6:
      if (*count > 26)                    /* Buchstabenbereich checken */
      {
         error_item_many_enum();
         *count = 1;
      }
      
      sprintf(string, "(%c)", 'a' - 1 + *count);
      break;
      
   case 3:
      itoroman(*count, string);
      strcat(string, ".");
      break;
      
   case 4:
      if (*count > 26)                    /* Buchstabenbereich checken */
      {
         error_item_many_enum();
         *count = 1;
      }
      
      sprintf(string, "%c.", 'A' - 1 + *count);
   }

   return string;
}





/*******************************************************************************
*
*  output_begin_verbatim():
*     begin verbatim environment
*
*  Notes:
*     The routine is called by pass2() and c_include_verbatim().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_begin_verbatim(void)
{
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      switch (iDocVerbatimSize)
      {
      case VERB_TINY:
         outln("\\begin{tiny}");
         break;
         
      case VERB_SMALL:
         outln("\\begin{scriptsize}");
         break;
         
      case VERB_LARGE:
         outln("\\begin{large}");
         break;
         
      case VERB_HUGE:
         outln("\\begin{huge}");
      }
      
      outln("\\begin{verbatim}");
      break;

      
   case TOINF:
      outln("@example");
      break;
      

   case TOIPF:
      outln(":xmp.");
      break;

      
   case TOAQV:
   case TOWIN:
   case TOWH4:
      out(win_verb_on);
      
      switch (iDocVerbatimSize)
      {
      case VERB_TINY:
         voutf("\\fs%d", iDocMonofontSize - 10);
         break;
         
      case VERB_SMALL:
         voutf("\\fs%d", iDocMonofontSize - 6);
         break;
         
      case VERB_NORMAL:
         voutf("\\fs%d", iDocMonofontSize - 2);
         break;
         
      case VERB_LARGE:
         voutf("\\fs%d", iDocMonofontSize + 2);
         break;
         
      case VERB_HUGE:
         voutf("\\fs%d", iDocMonofontSize + 6);
      }
      
      out(" ");
      break;
      
      
   case TORTF:
      out(rtf_pardplain);
      out(rtf_verb);
      
      switch (iDocVerbatimSize)
      {
      case VERB_TINY:
         voutf("\\fs%d ", iDocMonofontSize - 8);
         break;
         
      case VERB_SMALL:
         voutf("\\fs%d ", iDocMonofontSize - 4);
         break;
         
      case VERB_NORMAL:
         voutf("\\fs%d ", iDocMonofontSize);
         break;
         
      case VERB_LARGE:
         voutf("\\fs%d ", iDocMonofontSize + 4);
         break;
         
      case VERB_HUGE:
         voutf("\\fs%d ", iDocMonofontSize + 8);
      }
      
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      if (sDocVerbatimBackColor[0] != EOS)
      {
         voutlnf("<table width=\"100%%\" bgcolor=\"%s\"><tr><td>%s", sDocVerbatimBackColor, sHtmlMonofontStart);
      }
      
      switch (iDocVerbatimSize)
      {
      case VERB_TINY:
         outln("<font size=-2>");
         break;
         
      case VERB_SMALL:
         outln("<font size=-1>");
         break;
         
      case VERB_LARGE:
         outln("<font size=+1>");
         break;
         
      case VERB_HUGE:
         outln("<font size=+2>");
      }
      
      out("<pre>");                       /*r6pl5: vorher outln(), was zu einer Leerzeile zuviel fuehrte */
      break;
      
      
   case TOLDS:
      outln("<verb>");
      break;
      
      
   case TOHPH:
      outln("<ex>");
      break;
      
      
   case TOKPS:
      outln("Von");
   }
}





/*******************************************************************************
*
*  output_end_verbatim():
*     end verbatim environment
*
*  Notes:
*     The routine is called by pass2() and c_include_verbatim().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_end_verbatim(void)
{
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\end{verbatim}");
      
      switch (iDocVerbatimSize)
      {
      case VERB_TINY:
         outln("\\end{tiny}");
         break;
         
      case VERB_SMALL:
         outln("\\end{scriptsize}");
         break;
         
      case VERB_LARGE:
         outln("\\end{large}");
         break;
         
      case VERB_HUGE:
         outln("\\end{huge}");
      }
      
      break;
      
      
   case TOINF:
      outln("@end example");
      break;
      
      
   case TOIPF:
      outln(":exmp.");
      break;
      
      
   case TOAQV:
   case TOWIN:
   case TOWH4:
      outln(win_verb_off);
      break;
      
      
   case TORTF:
      outln(rtf_pardplain);
      voutlnf("%s\\fs%d", rtf_norm, iDocPropfontSize);
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      outln("</pre>");
      
      switch (iDocVerbatimSize)
      {
      case VERB_TINY:
         outln("</font>");
         break;
         
      case VERB_SMALL:
         outln("</font>");
         break;
         
      case VERB_LARGE:
         outln("</font>");
         break;
         
      case VERB_HUGE:
         outln("</font>");
      }
      
      if (sDocVerbatimBackColor[0] != EOS)
      {
         voutlnf("%s</td></tr></table>", sHtmlMonofontEnd);
      }
      
      break;
      
      
   case TOLDS:
      outln("</verb>");
      break;
      
      
   case TOHPH:
      outln("<\\ex>");
      break;
      
      
   case TOKPS:
      outln("Voff");
      break;
      
      
   default:
      break;
   }
   
   end_env_output_line(0);
}





/*******************************************************************************
*
*  output_begin_linedraw():
*     begin linedraw environment
*
*  Notes:
*     The routine is called by pass2() and c_include_linedraw().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_begin_linedraw(void)
{
   if (desttype != TORTF)
   {
      pre_linedraw_charset = iCharset;
      iCharset = CODE_437;
      output_begin_verbatim();
      return;
   }

   out(rtf_pardplain);
   out(rtf_linedraw);

   switch (iDocLinedrawSize)
   {
   case VERB_TINY:
      voutf("\\fs%d ", iDocMonofontSize - 8);
      break;
      
   case VERB_SMALL:
      voutf("\\fs%d ", iDocMonofontSize - 4);
      break;
      
   case VERB_NORMAL:
      voutf("\\fs%d ", iDocMonofontSize);
      break;
      
   case VERB_LARGE:
      voutf("\\fs%d ", iDocMonofontSize + 4);
      break;
      
   case VERB_HUGE:
      voutf("\\fs%d ", iDocMonofontSize + 8);
   }
}





/*******************************************************************************
*
*  output_end_linedraw():
*     end linedraw environment
*
*  Notes:
*     The routine is called by pass2() and c_include_linedraw().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_end_linedraw(void)
{
   output_end_verbatim();
   iCharset = pre_linedraw_charset;
}





/*******************************************************************************
*
*  output_begin_sourcecode():
*     begin sourcecode environment
*
*  Notes:
*     The routine is called by pass2() and c_include_src().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_begin_sourcecode(void)
{
   if (desttype != TOSRC && desttype != TOSRP)
   {
      if (!no_sourcecode)
      {
         c_begin_quote();
         output_begin_verbatim();
      }
   }
}





/*******************************************************************************
*
*  output_end_sourcecode():
*     end sourcecode environment
*
*  Notes:
*     The routine is called by pass2() and c_include_src().
*
*  Return:
*     -
*
******************************************|************************************/



GLOBAL void output_end_sourcecode(void)
{
   if (desttype != TOSRC && desttype != TOSRP)
   {
      if (!no_sourcecode)
      {
         output_end_verbatim();
         c_end_quote();
      }
   }

   outln("");
}





/*******************************************************************************
*
*  output_begin_comment():
*     begin comment environment
*
*  Notes:
*     The routine is called by pass2() and c_include_comment().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_begin_comment(void)
{
   return;
}





/*******************************************************************************
*
*  output_end_comment():
*     end comment environment
*
*  Notes:
*     The routine is called by pass2() and c_include_comment().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_end_comment(void)
{
   return;
}





/*******************************************************************************
*
*  strcat_blanks():
*     concatenate <count> spaces to <string>
*
*  Return:
*     enhanced string
*
******************************************|************************************/

LOCAL char *strcat_blanks(

char     *string,   /* */
int       count)    /* */
{
   char   li[128];  /* */

   switch (desttype)
   {
   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      sprintf(li, "\\li%d", count);       /* count entspricht tics! */
      strcat(string, li);
      break;
   
   default:
                                          /* count entspricht Anzahl an Leerzeichen */
      if (use_justification)
         memset(li, INDENT_C, (size_t) count);
      else
         memset(li, ' ', (size_t) count);

      li[count] = EOS;
      strcat(string, li);
   }
   
   return string;
}





/*******************************************************************************
*
*  strlen_prev_indent():
*     find length of string to be indented
*
*  Notes:
*     For RTF, it is the value used for \li...
*
*  Return:
*     # of spaces to indent
*
******************************************|************************************/

LOCAL int strlen_prev_indent(void)
{
   int   i,   /* counter */
         il;  /* */
         

   il = 0;

   for (i = 0; i < iEnvLevel; i++)
   {
      il += iEnvIndent[i];
   }

   return il;
}





/*******************************************************************************
*
*  strlen_indent():
*     find length of string to be indented
*
*  Notes:
*     For RTF, it is the value used for \li...
*
*  Return:
*     # of spaces to indent
*
******************************************|************************************/

GLOBAL int strlen_indent(void)
{
   int   i,   /* counter */
         il;  /* */
         

   il = 0;

   for (i = 0; i <= iEnvLevel; i++)
   {
      il += iEnvIndent[i];
   }

   return il;
}





/*******************************************************************************
*
*  strcat_prev_indent():
*     concatenate spaces to <s> for the previous environment
*
*  Notes:
*     For RTF, a numeric value is used instead of spaces!
*     See the difference to strcat_indent(): < instead of <=
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void strcat_prev_indent(

char     *s)        /* */
{
   int    il;       /* */
   char   sil[64];  /* */


   il = strlen_prev_indent();

   if (il == 0)
      return;
   
   
   switch (desttype)
   {
   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      sprintf(sil, "\\li%d", il);
      strcat(s, sil);
      break;
      
   case TOASC:
   case TODRC:
   case TOMAN:
   case TOSTG:
   case TOAMG:
   case TOPCH:
   case TOTVH:
      strcat_blanks(s, il);
      break;
      
   case TOIPF:                            /* <???> */
      break;
   }
}





/*******************************************************************************
*
*  strcat_prev_indent():
*     concatenate spaces to <s> for the previous environment
*
*  Notes:
*     For RTF, a numeric value is used instead of spaces!
*     See the difference to strcat_prev_indent(): <= instead of <
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void strcat_indent(

char     *s)        /* */
{
   int    il;       /* */
   char   sil[64];  /* */


   il = strlen_indent();

   if (il == 0)
      return;
   

   switch (desttype)
   {
   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      sprintf(sil, "\\li%d", il);
      strcat(s, sil);
      
      if (iEnvLevel > 0 && iEnvType[iEnvLevel] == ENV_CENT)
         strcat(s, "\\qc");
      else
         strcat(s, "\\qj");
      
      strcat(s, " ");
      break;
      
   case TOASC:
   case TODRC:
   case TOMAN:
   case TOSTG:
   case TOAMG:
   case TOPCH:
   case TOTVH:
      strcat_blanks(s, il);
      break;
      
   case TOIPF:                            /* <???> */
      break;
   }
}





/*******************************************************************************
*
*  strcpy_prev_indent():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void strcpy_prev_indent(

char  *s)  /* */
{
   s[0] = EOS;
   strcat_prev_indent(s);
}





/*******************************************************************************
*
*  strcpy_indent():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void strcpy_indent(

char  *s)  /* */
{
   s[0] = EOS;
   strcat_indent(s);
}





/*******************************************************************************
*
*     QUOTES
*
******************************************|************************************/

/*******************************************************************************
*
*  c_begin_quote():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_quote(void)
{
   char   quote[1024],  /* */
         *ptr,          /* */
          title[512];   /* */
   int    j,            /* */
          k;            /* */
   long   lang;         /* */


   if (!check_iEnvLevel())
      return;
   
   iEnvLevel++;
   
   iEnvType[iEnvLevel]    = ENV_QUOT;
   env_kind[iEnvLevel]    = 0;
   iEnvIndent[iEnvLevel]  = 0;
   bEnv1stItem[iEnvLevel] = TRUE;
   bEnv1stPara[iEnvLevel] = TRUE;
   
   set_env_short(iEnvLevel, token[1]);

   quot_level++;

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\begin{quote}");
      break;
      
      
   case TOLYX:                            /* <???> */
      break;
      
      
   case TOINF:
      outln("@quotation");
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
                                          /* Changed in V6.5.9 [NHz] [blockquote] */
      um_strcpy(quote, "<blockquote", 1020, "c_begin_quote[1]");
      
      if (token[1][0] == '[')
      {
         token[token_counter - 1][strlen(token[token_counter - 1]) - 1] = EOS;
         
         for (j = 1;j < token_counter; j++)
         {
            ptr = strstr(token[j], "id=");
            
            if (ptr != NULL)
            {
               lang = strcspn(ptr, " ");
               
               um_strcat(quote, " id=\"", 1020, "c_begin_quote[2]");
               um_strncat(quote, ptr + 3, lang, 1020, "c_begin_quote[3]");
               um_strcat(quote, "\"", 1020, "c_begin_quote[4]");
            }
            
            ptr = strstr(token[j], "class=");
            
            if (ptr != NULL)
            {
               lang = strcspn(ptr, " ");
               
               um_strcat(quote, " class=\"", 1020, "c_begin_quote[5]");
               um_strncat(quote, ptr + 6, lang, 1020, "c_begin_quote[6]");
               um_strcat(quote, "\"", 1020, "c_begin_quote[7]");
            }
            
            ptr = strstr(token[j], "cite=");
            
            if (ptr != NULL)
            {
               lang = strcspn(ptr, " ");
               
               um_strcat(quote, " cite=\"", 1020, "c_begin_quote[8]");
               um_strncat(quote, ptr + 5, lang, 1020, "c_begin_quote[9]");
               um_strcat(quote, "\"", 1020, "c_begin_quote[10]");
            }
            
            ptr = strstr(token[j], "lang=");
            
            if (ptr != NULL)
            {
               lang = strcspn(ptr, " ");
               
               um_strcat(quote, " lang=\"", 1020, "c_begin_quote[11]");
               um_strncat(quote, ptr + 5, lang, 1020, "c_begin_quote[12]");
               um_strcat(quote, "\"", 1020, "c_begin_quote[13]");
            }
            
            ptr = strstr(token[j], "title=");
            
            if (ptr != NULL)
            {
               um_strcat(quote, " title=\"", 1020, "c_begin_quote[14]");
               
               if (ptr[6] == '\'')
               {
                  um_strcpy(title, ptr + 7, 512, "c_begin_quote[15]");
                  
                  lang = strlen(title);
                  
                  if (title[lang-1L] == '\'')
                     goto no_blanks;
                     
                  k = j;
                  
                  do
                  {
                     k++;
                     um_strcat(title, " ", 512, "c_begin_quote[16]");
                     um_strcat(title, token[k], 512, "c_begin_quote[17]");
                  } while(strrchr(token[k], '\'') == NULL);
                  
                  lang = strlen(title);

                  no_blanks:
                  title[lang - 1L] = EOS;
                  
                  um_strncat(quote, title, lang, 1020, "c_begin_quote[18]");
               }
               else
               {
                  lang = strcspn(ptr + 6, " ");
                  um_strncat(quote, ptr + 6, lang, 1020, "c_begin_quote[19]");
               }
               
               um_strcat(quote, "\"", 1020, "c_begin_quote[20]");
            }
         }
      }
      
      um_strcat(quote, ">", 1020, "c_begin_quote[21]");
      outln(quote);
/*    outln("<blockquote>");
*/
      break;
      
      
   case TOLDS:                            /* siehe token_output() */
      break;
      
      
   case TOIPF:
      voutlnf(":lm margin=%d.", quot_level * ENV_IND_ASC_QUOT + 1);
   }

   switch (desttype)
   {
   case TORTF:
      iEnvIndent[iEnvLevel] = ENV_IND_RTF_QUOT;
      break;
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
      iEnvIndent[iEnvLevel] = ENV_IND_WIN_QUOT;
      break;
      
   default:
      iEnvIndent[iEnvLevel] = ENV_IND_ASC_QUOT;
   }
}





/*******************************************************************************
*
*  c_end_quote():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_quote(void)
{
   if (quot_level == 0)
   {
      error_end_without_begin(CMD_END_QUOTE, CMD_BEGIN_QUOTE);
   }

   if (iEnvLevel > 0)
   {
      iEnvIndent[iEnvLevel] = 0;
      iEnvLevel--;
   }

   if (quot_level > 0)
   {
      quot_level--;
   }

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\end{quote}");
      outln("");
      break;
      
   case TOLYX:                            /* <???> */
      break;
      
   case TOINF:
      outln("@end quotation");
      break;
      
   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      if (quot_level == 0)
      {
         outln("\\li0\\ri0\\fi0 ");
      }
      
      break;
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      outln("</blockquote>");
      break;
      
   case TOLDS:                            /* siehe token_output() */
      break;
      
   case TOIPF:
      voutlnf(":lm margin=%d.", quot_level*ENV_IND_ASC_QUOT+1);
   }
}





/*******************************************************************************
*
*     CENTER ENVIRONMENT
*    (centered text)
*
******************************************|************************************/

/*******************************************************************************
*
*  c_begin_center():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_center(void)
{
   if (!check_iEnvLevel())
      return;

   iEnvLevel++;

   iEnvType[iEnvLevel]    = ENV_CENT;
   env_kind[iEnvLevel]    = 0;
   iEnvIndent[iEnvLevel]  = 0;
   bEnv1stItem[iEnvLevel] = TRUE;
   bEnv1stPara[iEnvLevel] = TRUE;
   
   /*r6pl6:   !short verbieten, da UDO dann nur Schrott erzeugt */
   /*         und eine Anpassung unheimlich problematisch ist   */
   
   switch (desttype)
   {
   case TOHTM:
   case TOMHH:
   case TOHAH:
      bEnvShort[iEnvLevel] = FALSE;
      break;
   
   default:
      set_env_short(iEnvLevel, token[1]);
   }

   cent_level++;
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\begin{center}");
      break;
      
   case TOIPF:
      outln(":lines align=center.");      /* r6pl7*/
      break;
      
   case TOLYX:                            /* <???> */
      break;
   }
}

/*******************************************************************************
*
*  c_end_center():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_center(void)
{
   if (cent_level == 0)
   {
      error_end_without_begin(CMD_END_CENTER, CMD_BEGIN_CENTER);
   }
   
   if (iEnvLevel > 0)
   {
      iEnvIndent[iEnvLevel] = 0;
      iEnvLevel--;
   }

   if (cent_level > 0)
   {
      cent_level--;
   }

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\end{center}");
      outln("");
      break;
      
   case TOIPF:
      outln(":elines.");                  /* r6pl7*/
      break;
      
   case TOLYX:                            /* <???> */
      break;
   }
}





/*******************************************************************************
*
*     RIGHT ENVIRONMENT
*    (right-justified text)
*
******************************************|************************************/

/*******************************************************************************
*
*  c_begin_flushright():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_flushright(void)
{
   if (!check_iEnvLevel())
      return;
   
   iEnvLevel++;

   iEnvType[iEnvLevel]    = ENV_RIGH;
   env_kind[iEnvLevel]    = 0;
   iEnvIndent[iEnvLevel]  = 0;
   bEnv1stItem[iEnvLevel] = TRUE;
   bEnv1stPara[iEnvLevel] = TRUE;
   
   /*r6pl6:   !short verbieten, da UDO dann nur Schrott erzeugt */
   /*         und eine Anpassung unheimlich problematisch ist   */
   
   switch (desttype)
   {
   case TOHTM:
   case TOMHH:
   case TOHAH:
      bEnvShort[iEnvLevel] = FALSE;
      break;
   
   default:
      set_env_short(iEnvLevel, token[1]);
   }

   flushright_level++;
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\begin{flushright}");
      break;
      
   case TOLYX:                            /* <???> */
      break;
      
   case TOINF:
      outln("@flushright");
      outln("");
      break;
      
   case TOIPF:
      outln(":lines align=right.");       /* r6pl7*/
   }
}





/*******************************************************************************
*
*  c_end_flushright():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_flushright(void)
{
   if (flushright_level == 0)
   {
      error_end_without_begin(CMD_END_RIGHT, CMD_BEGIN_RIGHT);
   }
   
   if (iEnvLevel > 0)
   {
      iEnvIndent[iEnvLevel] = 0;
      iEnvLevel--;
   }

   if (flushright_level > 0)
   {
      flushright_level--;
   }

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\end{flushright}");
      outln("");
      break;
      
   case TOLYX:                            /* <???> */
      break;
      
   case TOINF:
      outln("@end flushright");
      outln("");
      break;
      
   case TOIPF:
      outln(":elines.");                  /* r6pl7*/
   }
}





/*******************************************************************************
*
*     LEFT ENVIRONMENT
*    (left-justified text)
*
******************************************|************************************/

/*******************************************************************************
*
*  c_begin_flushleft():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_flushleft(void)
{
   if (!check_iEnvLevel())
      return;

   iEnvLevel++;

   iEnvType[iEnvLevel]    = ENV_LEFT;
   env_kind[iEnvLevel]    = 0;
   iEnvIndent[iEnvLevel]  = 0;
   bEnv1stItem[iEnvLevel] = TRUE;
   bEnv1stPara[iEnvLevel] = TRUE;

   /*r6pl6:   !short verbieten, da UDO dann nur Schrott erzeugt */
   /*         und eine Anpassung unheimlich problematisch ist   */
   
   switch (desttype)
   {
   case TOHTM:
   case TOMHH:
   case TOHAH:
      bEnvShort[iEnvLevel] = FALSE;
      break;
   
   default:
      set_env_short(iEnvLevel, token[1]);
   }

   flushleft_level++;
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\begin{flushleft}");
      break;
      
   case TOLYX:                            /* <???> */
      break;
      
   case TOINF:
      outln("@flushleft");
      outln("");
      break;
      
   case TOIPF:
      outln(":lines align=left.");        /* r6pl7*/
   }
}





/*******************************************************************************
*
*  c_end_flushleft():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_flushleft(void)
{
   if (flushleft_level == 0)
   {
      error_end_without_begin(CMD_END_LEFT, CMD_BEGIN_LEFT);
   }
   
   if (iEnvLevel > 0)
   {
      iEnvIndent[iEnvLevel] = 0;
      iEnvLevel--;
   }

   if (flushleft_level > 0)
   {
      flushleft_level--;
   }

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\end{flushleft}");
      outln("");
      break;
   case TOLYX:                            /* <???> */
      break;
   case TOINF:
      outln("@end flushleft");
      outln("");
      break;
   case TOIPF:
      outln(":elines.");                  /* r6pl7*/
   }
}





/*******************************************************************************
*
*  c_begin_itemize():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_itemize(void)
{
   if (!check_iEnvLevel())
      return;
   
   iEnvLevel++;
   
   iEnvType[iEnvLevel]    = ENV_ITEM;
   env_kind[iEnvLevel]    = 0;
   iEnvIndent[iEnvLevel]  = 0;
   bEnv1stItem[iEnvLevel] = TRUE;
   bEnv1stPara[iEnvLevel] = TRUE;
   
   set_env_short(iEnvLevel, token[1]);
   
   iItemLevel++;
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\begin{itemize}");
      
      if (bEnvShort[iEnvLevel])
      {
         outln("\\itemsep 0pt");
         outln("\\parsep 0pt");
         outln("\\parskip 0pt");
      }
      
      break;
      
      
   case TOLYX:
      if (iEnvLevel > 1)
      {
         outln("\\begin_deeper");
      }
      
      break;
      
      
   case TOINF:
      out("@itemize ");
      
      switch (iItemLevel)
      {
      case 1:
      case 3:
         outln("@bullet");
         break;
         
      case 2:
      case 4:
         outln("@minus");
      }
      
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      if (bParagraphOpen)                 /* paragraph still open?!? */
      {
         if (!bEnvShort[iEnvLevel])       /* no short environment */
         {
            switch (iEnvType[iEnvLevel])
            {
            case ENV_DESC:
               outln("</p>\n");           /* close previous paragraph first */
               break;
               
            case ENV_LIST:
               outln("</p>");             /* close previous paragraph first */
               break;
            
            default:
               out("</p>");               /* close previous paragraph first */
            }
         }
      }
      
      bParagraphOpen = FALSE;
         
      outln("\n<ul>");
      break;
      
      
   case TOHPH:
      outln("<list>");
      break;
      
      
   case TOLDS:
      outln("<itemize>");
      break;
      
      
   case TOIPF:
      if (bEnvShort[iEnvLevel])
         outln(":ul compact.");
      else
         outln(":ul.");
      
      break;
      
      
   case TOKPS:
      voutlnf("/off%d (000) addStrSpaceLeft", iEnvLevel);
   }
   
   switch (desttype)
   {
   case TORTF:
      iEnvIndent[iEnvLevel] = ENV_IND_RTF_ITEM;
      break;
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
      iEnvIndent[iEnvLevel] = ENV_IND_WIN_ITEM;
      break;
      
   default:
      iEnvIndent[iEnvLevel] = ENV_IND_ASC_ITEM;
   }
}





/*******************************************************************************
*
*  c_begin_enumerate():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_enumerate(void)
{
   if (!check_iEnvLevel())
      return;

   iEnvLevel++;

   iEnvType[iEnvLevel]    = ENV_ENUM;
   env_kind[iEnvLevel]    = 0;
   enum_count[iEnvLevel]  = 0;
   iEnvIndent[iEnvLevel]  = 0;
   bEnv1stItem[iEnvLevel] = TRUE;
   bEnv1stPara[iEnvLevel] = TRUE;
   
   set_env_short(iEnvLevel, token[1]);

   iEnumLevel++;
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\begin{enumerate}");
      
      if (bEnvShort[iEnvLevel])
      {
         outln("\\itemsep 0pt");
         outln("\\parsep 0pt");
         outln("\\parskip 0pt");
      }
      
      break;
      
      
   case TOLYX:
      if (iEnvLevel > 1)
      {
         outln("\\begin_deeper");
      }
      
      break;
      
      
   case TOINF:
      out("@enumerate ");
      
      switch (iEnumLevel)
      {
      case 1:
         outln("1");
         break;
         
      case 2:
         outln("a");
         break;
         
      case 3:
         outln("1");
         break;
         
      case 4:
         outln("A");
      }
      
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      if (bParagraphOpen)                 /* paragraph still open?!? */
      {
         if (!bEnvShort[iEnvLevel])       /* no short environment */
         {
            switch (iEnvType[iEnvLevel])
            {
            case ENV_DESC:
               outln("</p>\n");           /* close previous paragraph first */
               break;
               
            case ENV_LIST:
               outln("</p>");             /* close previous paragraph first */
               break;
               
            default:
               out("</p>");               /* close previous paragraph first */
            }
         }
      }
      
      bParagraphOpen = FALSE;
         
      out("\n<ol");
      
      switch (iEnumLevel)                 /*r6pl5: HTML 3.2 Moeglichkeiten nutzen */
      {
      case 1:
      case 5:
         break;
         
      case 2:
      case 6:
         outln(" type=a");
         break;
         
      case 3:
         outln(" type=i");
         break;
         
      case 4:
         outln(" type=A");
      }
      
      outln(">");
      break;
      
      
   case TOHPH:
      outln("<list>");
      break;
      
      
   case TOLDS:
      outln("<enum>");
      break;
      
      
   case TOIPF:
      if (bEnvShort[iEnvLevel])
         outln(":ol compact.");
      else
         outln(":ol.");
      
      break;
      
      
   case TOKPS:
      voutlnf("/off%d (000) addStrSpaceLeft", iEnvLevel);
   }

   switch (desttype)
   {
   case TORTF:
      iEnvIndent[iEnvLevel] = ENV_IND_RTF_ENUM;
      break;
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
      iEnvIndent[iEnvLevel] = ENV_IND_WIN_ENUM;
      break;
      
   default:
      if (iEnumLevel == 3)
         iEnvIndent[iEnvLevel] = 4 + ENV_IND_ASC_ENUM;
      else
         iEnvIndent[iEnvLevel] = ENV_IND_ASC_ENUM;
   }
}





/*******************************************************************************
*
*  c_begin_description():
*     output begin of description environment
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_description(void)
{
   if (!check_iEnvLevel())
      return;

   iEnvLevel++;

   iEnvType[iEnvLevel]    = ENV_DESC;
   env_kind[iEnvLevel]    = 0;
   iEnvIndent[iEnvLevel]  = 0;
   bEnv1stItem[iEnvLevel] = TRUE;
   bEnv1stPara[iEnvLevel] = TRUE;
   
   set_env_short(iEnvLevel, token[1]);

   iDescLevel++;
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\begin{description}");
      
      if (bEnvShort[iEnvLevel])
      {
         outln("\\itemsep 0pt");
         outln("\\parsep 0pt");
         outln("\\parskip 0pt");
      }
      
      break;
      
      
   case TOLYX:
      if (iEnvLevel > 1)
      {
         outln("\\begin_deeper");
      }
      
      break;
      
      
   case TOINF:
      outln("@table @strong");
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      outln("<dl>");
      bDescDDOpen = FALSE;                /* <dd> not opened yet! */
      bParagraphOpen = FALSE;             /* <p> not opened yet! */
      break;
      
      
   case TOHPH:
      outln("<list>");
      break;
      
      
   case TOLDS:
      outln("<descrip>");
      break;
      
      
   case TOIPF:
      if (bEnvShort[iEnvLevel])
         outln(":dl compact break=none tsize=4.");
      else
         outln(":dl break=none tsize=4.");
      
      break;
      
      
   case TOKPS:                            /* New in r6pl15 [NHz] */
      outln("Bon");
      outln("/offDesc (000000) addStrSpaceLeft");
      outln("Boff");
      outln("description");
   }

   switch (desttype)
   {
   case TORTF:
      iEnvIndent[iEnvLevel] = ENV_IND_RTF_DESC;
      break;
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
      iEnvIndent[iEnvLevel] = ENV_IND_WIN_DESC;
      break;
      
   default:
      iEnvIndent[iEnvLevel] = ENV_IND_ASC_DESC;
   }
}





/*******************************************************************************
*
*  c_begin_list():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_begin_list(

int       listkind)     /* */
{
   char   sWidth[256],  /* */
          sShort[256],  /* */
         *ptr;          /* */
   int    ll;           /* */
   

   if (!check_iEnvLevel())
      return;

   switch (desttype)
   {
   case TOLDS:
   case TOHPH:
   case TONRO:
      c_begin_description();
      return;
   
   case TOHTM:
   case TOHAH:
      if (html_no_xlist)
      {
         c_begin_description();
         return;
      }
   }

   iEnvLevel++;

   iEnvType[iEnvLevel]    = ENV_LIST;
   env_kind[iEnvLevel]    = listkind;
   iEnvIndent[iEnvLevel]  = 0;
   bEnv1stItem[iEnvLevel] = TRUE;
   bEnv1stPara[iEnvLevel] = TRUE;
   
   iListLevel++;
   
   
   /* String fuer die Breite ermitteln und schauen, ob !short vorkommt */

   sShort[0] = EOS;
   token[0][0] = EOS;
   tokcpy2(sWidth, 256);
   
   delete_once(sWidth, "[");
   delete_last(sWidth, "]");

   ptr = strstr(sWidth, "!short");
   
   if (ptr != NULL)
   {
      /* Aha, !short wird benutzt. Da manche Dumpfnasen das aber nicht */
      /* immer ans Ende setzen, hier gleich die passenden Abfragen.    */

      strcpy(sShort, "!short");           /* Fuer set_env_short() */
            
      if (ptr == sWidth)
      {
         /* Siehste, hat's mal wieder an den Anfang gesetzt      */
         /* Das mitzuentfernende Leerzeichen kommt von tokcpy2() */
         
         delete_once(sWidth, "!short ");
      }
      else
      {
         /* So gehoert es sich, schoen ans Ende der Zeile */
         delete_last(sWidth, " !short");
      }
   }
   
   del_internal_styles(sWidth);
   qdelete_all(sWidth, "!-", 2);
   replace_udo_quotes(sWidth);

   set_env_short(iEnvLevel, sShort);      /* Jetzt noch das short-Flag setzen */

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      switch (listkind)
      {
      case LIST_BOLD:
         out("\\begin{blist}");
         break;
         
      case LIST_ITALIC:
         out("\\begin{ilist}");
         break;
         
      case LIST_TYPEWRITER:
         out("\\begin{tlist}");
         break;
         
      default:
         out("\\begin{xlist}");
      }
      
      voutlnf("{%s}", sWidth);
      
      if (bEnvShort[iEnvLevel])
      {
         outln("\\itemsep 0pt");
         outln("\\parsep 0pt");
         outln("\\parskip 0pt");
      }
      
      break;
      
      
   case TOLYX:
      if (iEnvLevel > 1)
      {
         outln("\\begin_deeper");
      }
      
      break;
      
      
   case TOINF:
      outln("@table @asis");
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      outln("<table>");
      break;
      
      
   case TOSTG:
   case TOAMG:
   case TOASC:
   case TODRC:
   case TOMAN:
   case TOPCH:
   case TOTVH:
   case TOKPS:
   {
                                          /* Changed in r6pl15 [NHz] */
      char   space[50];  /* */
      int    i;          /* */
   
                                          /* Changed in r6pl16 [NHz] */
      space[0] = EOS;
      ll= (int) strlen(sWidth);
      
      iEnvIndent[iEnvLevel] = (int) strlen(sWidth) + 3;
      
      for (i = 0; i < iEnvIndent[iEnvLevel]; i++)
         strcat(space, "0");

      if (desttype == TOKPS)
      {
         switch (listkind)
         {
         case LIST_BOLD:
            outln("Bon");
            break;
            
         case LIST_ITALIC:
            outln("Ion");
            break;
            
         case LIST_TYPEWRITER:
            outln("Von");
         }
         
/*       voutlnf("/offList (%s00) addStrSpaceLeft", space);
*/
         outln("/offCount offCount 1 add def");
         outln("/offCountS offCount 4 add def");
         voutlnf("offList offCount get (%s00) addStrSpaceLeft", space);

         switch (listkind)
         {
         case LIST_BOLD:
            outln("Boff");
            break;
            
         case LIST_ITALIC:
            outln("Ioff");
            break;
            
         case LIST_TYPEWRITER:
            outln("Voff");
         }
      }
      
      break;
   }
   
   
   case TOIPF:
      if (bEnvShort[iEnvLevel])
      {
         voutlnf(":dl compact break=none tsize=%d.", (int)strlen(sWidth)+4);
      }
      else
      {
         voutlnf(":dl break=none tsize=%d.", (int)strlen(sWidth)+4);
      }
      
      break;
      
      
   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      recode_chrtab(sWidth,CHRTAB_ANSI);
      
      ll = (int)toklen(sWidth);

      if (desttype == TORTF)
         iEnvIndent[iEnvLevel] = ll * iDocCharwidth;
      
      else
      {   
#if 1
         iEnvIndent[iEnvLevel] = ll * iDocCharwidth;
#else
         switch (listkind)
         {
         case LIST_BOLD:
            ll= calc_ttf_twip(sWidth, TTF_TIMES, TTF_BOLD);
            break;
            
         case LIST_ITALIC:
            ll= calc_ttf_twip(sWidth, TTF_TIMES, TTF_ITALIC);
            break;
            
         case LIST_TYPEWRITER:
            ll= calc_ttf_twip(sWidth, TTF_COURIER, TTF_REGULAR);
            break;
            
         default:
            ll= calc_ttf_twip(sWidth, TTF_TIMES, TTF_REGULAR);
         }
      
         iEnvIndent[iEnvLevel] = ll;
#endif
      }
   }
}





/*******************************************************************************
*
*  c_begin_xlist():
*     wrapper for c_begin_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_xlist(void)
{
   c_begin_list(LIST_NORMAL);
}





/*******************************************************************************
*
*  c_begin_blist():
*     wrapper for c_begin_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_blist(void)
{
   c_begin_list(LIST_BOLD);
}





/*******************************************************************************
*
*  c_begin_ilist():
*     wrapper for c_begin_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_ilist(void)
{
   c_begin_list(LIST_ITALIC);
}





/*******************************************************************************
*
*  c_begin_tlist():
*     wrapper for c_begin_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_tlist(void)
{
   c_begin_list(LIST_TYPEWRITER);
}





/*******************************************************************************
*
*  add_description():
*     get the content of !item [...] and copy it into 1st token, ] included
*
*  Notes:
*     Gesucht wird die erste eckige Klammer, die nicht durch ein ! gequotet wird.
*
*     PL10: fast komplett neu, wegen Quotefunktion
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void add_description(void)
{
   int       i;                 /* */
   size_t    sl;                /* */
   BOOLEAN   finished = FALSE;  /* */
   BOOLEAN   no_bracket;        /* */
   char     *found,             /* */
            *ptr;               /* */
            

   sl= strlen(token[1]);

                                          /* Alles im ersten Token? */
   if (sl > 1 && token[1][sl - 1] == ']' && token[1][sl - 2] != '!')
   {
      replace_all(token[1], "!]", "]");
      um_strcat(token[0], token[1], MAX_TOKEN_LEN + 1, "add_description [1]");
      token[1][0] = EOS;
      return;
   }


   /* Die Sache sieht komplizierter aus, da der Item-Inhalt */
   /* ueber mehrere Tokens verteilt ist */

   no_bracket = TRUE;
   i = 1;

   while ( (!finished) && (i < token_counter) )
   {
      if (token[i][0] != EOS)
      {
         if ( (found = strchr(token[i], ']')) == NULL)
         {
            um_strcat(token[0], token[i], MAX_TOKEN_LEN+1, "add_description [2]");
            um_strcat(token[0], " ", MAX_TOKEN_LEN+1, "add_description [3]");
            token[i][0] = EOS;
            i++;
         }
         else
         {
            while (found != NULL && found[-1] == '!')
            {
               found--;
               delete_once(found, "!");
               ptr = found + 1;
               found = strchr(ptr, ']');
            }
               
            if (found == NULL)
            {                             /* wie oben */
               um_strcat(token[0], token[i], MAX_TOKEN_LEN+1, "add_description [4]");
               um_strcat(token[0], " " , MAX_TOKEN_LEN+1, "add_description [5]");
               token[i][0] = EOS;
               i++;
            }
            else
            {
               um_strcat(token[0], token[i], MAX_TOKEN_LEN+1, "add_description [6]");
               token[i][0] = EOS;
               finished= TRUE;
               no_bracket= FALSE;
            }
         }
      }
      else
      {
         finished = TRUE;
      }
   }

   /* PL17: Warnung ausgeben, falls keine (nicht-quotierte) "]" gefunden wurde */      

   if (no_bracket)
   {
      error_unexpected_eol();
   }
}





/*******************************************************************************
*
*  c_item():
*     format an item
*
*  Notes:
*     The first char of token[0] HAS TO BE a space, or token_output() has
*     difficulties to properly output the stuff.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_item(void)
{
   char     s[512],       /* */
            li[128],      /* */
            ri[128];      /* */
   char     sBig[1024],   /* */
            sTemp[1024],  /* */
            sAdd[128];    /* */
   size_t   tl,           /* */
            sl,           /* */
            i;            /* */
   int      ll,           /* */
            lp;           /* */
   
   
   if ( (iItemLevel == 0) && (iEnumLevel == 0) && (iDescLevel == 0) && (iListLevel == 0) )
   {
      error_item_outside_env();
   }

   bEnv1stPara[iEnvLevel] = TRUE;

   tokens_contain_item = TRUE;

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      um_strcpy(token[0], "\\item", MAX_TOKEN_LEN+1, "c_item [1]");
      
      switch (iEnvType[iEnvLevel])
      {
      case ENV_DESC:
      case ENV_LIST:
         if (token[1][0] == '[')
            add_description();
      }
      
      break;
      
      
   case TOLYX:
      token[0][0] = EOS;
      
      switch (iEnvType[iEnvLevel])
      {
      case ENV_ITEM:
         outln("\\layout Itemize");
         outln("");
         break;
         
      case ENV_ENUM:
         outln("\\layout Enumerate");
         outln("");
         break;
         
      case ENV_DESC:
         outln("\\layout Description");
         outln("");
         break;
         
      case ENV_LIST:
         outln("\\layout List");
         outln("");
      }
      
      switch (iEnvType[iEnvLevel])
      {
      case ENV_DESC:
         if (token[1][0] == '[')
         {
            add_description();
            delete_once(token[0], "[");
            delete_last(token[0], "]");
         }
         
         space2nbsp(token[0]);
         break;
         
      case ENV_LIST:
         if (token[1][0] == '[')
         {
            add_description();
            delete_once(token[0], "[");
            delete_last(token[0], "]");
         }
         
         space2nbsp(token[0]);
         
         switch (env_kind[iEnvLevel])
         {
         case LIST_BOLD:
            strinsert(token[0], "\\series bold ");
            um_strcat(token[0], "\\series default ", MAX_TOKEN_LEN+1, "c_item[2]");
            break;
            
         case LIST_ITALIC:
            strinsert(token[0], "\\shape italic ");
            um_strcat(token[0], "\\shape default ", MAX_TOKEN_LEN+1, "c_item[3]");
         }
      }
      
      break;

      
   case TOINF:
      um_strcpy(token[0], "@item ", MAX_TOKEN_LEN+1, "c_item[4]");
      
      switch (iEnvType[iEnvLevel])
      {
      case ENV_DESC:
      case ENV_LIST:
         if (token[1][0] == '[')
         {
            add_description();
            delete_once(token[0], "[");
            delete_last(token[0], "]");
         }
         
         um_strcat(token[0], "\n", MAX_TOKEN_LEN+1, "c_item[5]");
      }
      
      break;


   case TOSTG:
   case TOAMG:
   case TOASC:
   case TODRC:
   case TOMAN:
   case TOPCH:
   case TOTVH:
      switch (iEnvType[iEnvLevel])
      {
      case ENV_ITEM:
         token[0][0] = EOS;
         tl = strlen_indent();
         
         if (tl > 1)
         {
            memset(sAdd, ' ', (size_t) (tl-1));
            sAdd[tl-1] = EOS;
            um_strcat(token[0], sAdd, MAX_TOKEN_LEN+1, "c_item[6]");
            token[0][tl-2] = itemchar[iItemLevel][0];
         }
         
         break;
         
      case ENV_ENUM:
         enum_count[iEnvLevel]++;
         itoenum(iEnumLevel, &(enum_count[iEnvLevel]), s);
         
         sl = strlen(s);
         token[0][0] = EOS;
         tl = strlen_indent();
         
         if (tl > 1)
         {
            memset(sAdd, ' ', (size_t) (tl-1));
            sAdd[tl-1] = EOS;
            um_strcat(token[0], sAdd, MAX_TOKEN_LEN+1, "c_item[7]");
            
            for (i = 0; i < sl; i++)
            {
               token[0][tl-sl-1+i] = s[i];
            }
         }
         
         break;
         

      case ENV_DESC:
#if 1    /* Neue Version mit !autoref_items-Unterstuetzung */
         token[0][0] = EOS;
         
         strcpy_prev_indent(li);
         
         if (token[1][0] == '[')
         {
            add_description();

            if (desttype == TOSTG && bDocAutorefItemsOff)
            {
               delete_once(token[0], "[");
               delete_last(token[0], "]");
               del_internal_styles(token[0]);
               um_strcpy(sTemp, token[0], 1024, "c_item[8]");
               replace_all(sTemp, "\"", "\\\"");
               replace_2at_by_1at(sTemp);   /* r6pl1 */
               sprintf(sBig, "@{B}@{\"%s\" ignore}@{b}", sTemp);
               
               if (insert_placeholder(sBig, sBig, sBig, token[0]))
               {
                  sprintf(token[0], " %s%s", li, sBig);
               }
               else
               {
                  token[0][0] = EOS;
               }
            }
            else
            {
               replace_once(token[0], "[", BOLD_ON);
               replace_last(token[0], "]", BOLD_OFF);
               strinsert(token[0], li);
               strinsert(token[0], " ");
            }
         }
#else    /* Alte Version, ohne !autoref_items-Unterstuetzung */
         um_strcpy(token[0], " ", MAX_TOKEN_LEN+1, "c_item[9]");
         strcat_prev_indent(token[0]);
         
         if (token[1][0] == '[')
         {
            add_description();
            replace_once(token[0], "[", BOLD_ON);
            replace_last(token[0], "]", BOLD_OFF);
         }
#endif
         break;

      case ENV_LIST:
         token[0][0] = EOS;
         
         if (token[1][0] == '[')
         {
            add_description();
            delete_once(token[0], "[");
            delete_last(token[0], "]");
         }

         ri[0] = EOS;
         ll = iEnvIndent[iEnvLevel] - 2;

                                          /* PL16: Das leidige @@-Problem beim ST-Guide */
         if (desttype == TOSTG)
         {
            um_strcpy(sBig, token[0], 1024, "c_item[10]");
            replace_2at_by_1at(sBig);
            
            tl = toklen(sBig);
         }
         else
         {
            tl = toklen(token[0]);
         }

         sAdd[0] = EOS;
         
         if (((int) tl) < ll)
         {
            memset(sAdd, ' ', (size_t) (ll-tl));
            sAdd[ll-tl] = EOS;
            /* sAdd wird weiter unten hinzugefuegt */
         }

         strcpy_prev_indent(li);

                                          /* Hier fuer den ST-Guide noch !autoref_items supporten */
         if (desttype == TOSTG && bDocAutorefItemsOff)
         {
            del_internal_styles(token[0]);
            um_strcpy(sTemp, token[0], 1024, "c_item[11]");
            replace_all(sTemp, "\"", "\\\"");
            sprintf(sBig, "@{\"%s\" ignore}", sTemp);
            
            switch (env_kind[iEnvLevel])
            {
            case LIST_BOLD:
               strinsert(sBig, "@{B}");
               strcat(sBig, "@{b}");
               break;
               
            case LIST_ITALIC:
               strinsert(sBig, "@{I}");
               strcat(sBig, "@{i}");
            }

            if (insert_placeholder(sBig, sBig, sBig, token[0]))
            {
               strcat(sBig, ri);
               strinsert(sBig, li);
               strinsert(sBig, " ");
               strcat(sBig, sAdd);
            }
            else
            {
               token[0][0] = EOS;
            }
            
            um_strcpy(token[0], sBig, 1024, "c_item[12]");
         }
         else
         {
            switch (env_kind[iEnvLevel])
             {
             case LIST_BOLD:
                sprintf(s, " %s%s%s%s%s", li, BOLD_ON, token[0], BOLD_OFF, ri);
                break;
                
             case LIST_ITALIC:
                sprintf(s, " %s%s%s%s%s", li, ITALIC_ON, token[0], ITALIC_OFF, ri);
                break;
                
             default:
                sprintf(s, " %s%s%s", li, token[0], ri);
             }

            um_strcpy(token[0], s, MAX_TOKEN_LEN+1, "c_item[13]");
            um_strcat(token[0], sAdd, MAX_TOKEN_LEN+1, "c_item[14]");
         }

      }   /* switch (iEnvType[iEnvLevel]) */
      
      if (use_justification)
      {
         space2indent(token[0]);
      }
      
      break;
      
      
   case TONRO:
      switch (iEnvType[iEnvLevel])
      {
      case ENV_ITEM:
         um_strcpy(token[0], ".TP\n.B o\n", MAX_TOKEN_LEN+1, "c_item[15]");
         break;
         
      case ENV_ENUM:
         enum_count[iEnvLevel]++;
         itoenum(iEnumLevel, &(enum_count[iEnvLevel]), s);
         sprintf(token[0], ".TP\n.B %s\n", s);
         break;
         
      case ENV_DESC:
         um_strcpy(token[0], ".TP\n", MAX_TOKEN_LEN+1, "c_item[16]");
         
         if (token[1][0] == '[')
         {
            add_description();
            replace_once(token[0], "[", ".B ");
            replace_last(token[0], "]", "\n");
         }
      }
      
      break;


   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      switch (iEnvType[iEnvLevel])
      {
      case ENV_ITEM:
         ll = strlen_indent();
         sprintf(sBig, "\\pard\\ \\tqr\\tx%d\\tx%d\\li%d\\fi-%d\\qj\\tab %s\\tab", ll-167, ll, ll, ll, itemchar[iItemLevel]);
         break;
         
      case ENV_ENUM:
         enum_count[iEnvLevel]++;
         ll= strlen_indent();
         itoenum(iEnumLevel, &(enum_count[iEnvLevel]), s);
         sprintf(sBig, "\\pard\\tqr\\tx%d\\tx%d\\li%d\\fi-%d\\qj\\tab %s\\tab", ll-167, ll, ll, ll, s);
         break;
         
      case ENV_DESC:
         token[0][0] = EOS;
         sBig[0] = EOS;
         
         if (token[1][0] == '[')
         {
            add_description();
            replace_once(token[0], "[", BOLD_ON);
            replace_last(token[0], "]", BOLD_OFF);
            um_strcpy(sBig, token[0], 1024, "c_item[17]");
            
            if (desttype == TORTF)
            {
               c_rtf_styles(sBig);
               c_rtf_quotes(sBig);
               replace_udo_quotes(sBig);
            }
            else
            {
               c_win_styles(sBig);
               replace_udo_quotes(sBig);
               
               if (!bDocAutorefItemsOff)
               {
                  auto_references(sBig, FALSE, "", 0, 0);
               }
            }
         }
         
         ll= strlen_indent();
         strcpy(sTemp, sBig);
         sprintf(sBig, "\\pard\\li%d\\fi-%d\\qj %s", ll, 567, sTemp);
         break;
         
      case ENV_LIST:
         token[0][0] = EOS;
         sBig[0] = EOS;
         
         if (token[1][0] == '[')
         {
            add_description();
            delete_once(token[0], "[");
            delete_last(token[0], "]");
            um_strcpy(sBig, token[0], 1024, "c_item[18]");
            
            if (desttype == TORTF)
            {
               c_rtf_styles(sBig);
               c_rtf_quotes(sBig);
               replace_udo_quotes(sBig);
            }
            else
            {
               c_win_styles(sBig);
               replace_udo_quotes(sBig);
               
               if (!bDocAutorefItemsOff)
               {
                  auto_references(sBig, FALSE, "", 0, 0);
               }
            }
         }
         
         ll = strlen_indent();
         
         if (iEnvLevel > 1)
         {
#if 1
            lp = ll - strlen_prev_indent();
#else
            if (iEnvType[iEnvLevel - 1] == ENV_LIST)
            {
               lp = ll - strlen_prev_indent();
            }
            else
            {
               lp = ll - iEnvIndent[iEnvLevel - 1];
            }
#endif
         }
         else
         {
            lp = ll;
         }
         
         strcpy(sTemp, sBig);
         
         switch (env_kind[iEnvLevel])
         {
         case LIST_NORMAL:
            sprintf(sBig, "\\pard\\li%d\\fi-%d\\tx%d\\qj %s\\tab", ll, lp, ll, sTemp);
            break;
            
         case LIST_BOLD:
            sprintf(sBig, "\\pard\\li%d\\fi-%d\\tx%d\\qj {\\b %s}\\tab", ll, lp, ll, sTemp);
            break;
            
         case LIST_ITALIC:
            sprintf(sBig, "\\pard\\li%d\\fi-%d\\tx%d\\qj {\\i %s}\\tab", ll, lp, ll, sTemp);
            break;
            
         case LIST_TYPEWRITER:
            sprintf(sBig, "\\pard\\li%d\\fi-%d\\tx%d\\qj {\\f1 %s}\\tab", ll, lp, ll, sTemp);
         }
         
      }  /* switch (iEnvType[iEnvLevel]) */
      
      if (insert_placeholder(sBig, sBig, sBig, sBig))
      {
         um_strcpy(token[0], sBig, MAX_TOKEN_LEN+1, "c_item[19]");
      }
      else
      {
         token[0][0] = EOS;
      }
      
      break;


   case TOHAH:
   case TOHTM:
   case TOMHH:
      switch (iEnvType[iEnvLevel])        /* which kind of environment item? */
      {
      case ENV_ITEM:                      /* <ul> list item */
      case ENV_ENUM:                      /* <ol> list item */
         if (!bEnv1stItem[iEnvLevel])     /* not the first <li>? */
            outln("</li>");               /* r6pl6: </li> ausgeben */
         
         bEnv1stItem[iEnvLevel] = FALSE;  /* switch off 1st Item state anyway */
         
         strcpy(sBig, "<li>");            /* output <li> */
         bParagraphOpen = FALSE;
         
/* fd:2010-02-26: always !short in <ul> + <ol> environments

         if (!bEnvShort[iEnvLevel])
         {
            strcat(sBig, "<p>");
            bParagraphOpen = TRUE;
         }
 */       
         
         break;
         
      case ENV_DESC:                      /* New in V6.5.11 [NHz] */
         if (bDescDDOpen)                 /* handle still open <dd> tag first: */
         {
            if (bParagraphOpen)           /* paragraph still open? */
            {
               if (bEnvShort[iEnvLevel])  /* additional linefeed? */
               {
                  if (html_doctype < XHTML_STRICT)
                    outln("<br>");
                   else
                     outln("<br />");
               }
               else                       /* close paragraph */
                  outln("</p>\n");
            }

            bParagraphOpen = FALSE;
            
            outln("</dd>");               /* close previous <dd> tag */
         }

         bDescDDOpen = FALSE;             /* close DD flag anyway */
         
         token[0][0] = EOS;
         sBig[0] = EOS;
         
         if (token[1][0] == '[')
         {
            add_description();
            replace_once(token[0], "[", BOLD_ON);
            replace_last(token[0], "]", BOLD_OFF);
            um_strcpy(sBig, token[0], 1024, "c_item[20]");
            replace_udo_quotes(sBig);
            
            if (!bDocAutorefItemsOff)
               auto_references(sBig, FALSE, "", 0, 0);
            
            c_internal_styles(sBig);
            strinsert(sBig, "<dt>");
            um_strcat(sBig, "</dt>\n<dd>\n", 1024, "c_item[21]");
         }
         else
         {
            um_strcpy(sBig, "<dt>&nbsp;</dt>\n<dd>\n", 1024, "c_item[22]");
         }

         bDescDDOpen = TRUE;              /* open DD flag */
         
         if (!bEnvShort[iEnvLevel])
            um_strcat(sBig, "<p>", 1024, "c_item[22]");

         bParagraphOpen = TRUE;
         
         bEnv1stPara[iEnvLevel] = TRUE;
         bEnv1stItem[iEnvLevel] = TRUE;
         break;

      case ENV_LIST:
         token[0][0] = EOS;
         sBig[0] = EOS;
         
         if (!bEnv1stItem[iEnvLevel])
         {
            if (bParagraphOpen)
               if (bEnvShort[iEnvLevel])
               {
                  if (html_doctype < XHTML_STRICT)
                    outln("<br>");
                   else
                     outln("<br />");
               }
               else
                  out("</p>");
                  
            voutlnf("%s</td></tr>\n", sHtmlPropfontEnd);
            bEnv1stItem[iEnvLevel] = FALSE;
            bParagraphOpen = FALSE;
         }
         
         if (token[1][0] == '[')
         {
            add_description();
            
            switch (env_kind[iEnvLevel])
            {   
            case LIST_NORMAL:
               delete_once(token[0], "[");
               delete_last(token[0], "]");
               break;
               
            case LIST_BOLD:
               replace_once(token[0], "[", BOLD_ON);
               replace_last(token[0], "]", BOLD_OFF);
               break;
               
            case LIST_ITALIC:
               replace_once(token[0], "[", ITALIC_ON);
               replace_last(token[0], "]", ITALIC_OFF);
               break;
               
            case LIST_TYPEWRITER:
               replace_once(token[0], "[", TWRITER_ON);
               replace_last(token[0], "]", TWRITER_OFF);
            }
            
            um_strcpy(sBig, token[0], 1024, "c_item[23]");
            replace_udo_quotes(sBig);
            
            if (!bDocAutorefItemsOff)
               auto_references(sBig, FALSE, "", 0, 0);
            
            c_internal_styles(sBig);
            strinsert(sBig, sHtmlPropfontStart);
            strinsert(sBig, "<tr><td nowrap=\"nowrap\" valign=\"top\">");
            strcat(sBig, sHtmlPropfontEnd);
            strcat(sBig, "</td>\n<td valign=\"top\">");
            strcat(sBig, sHtmlPropfontStart);
            
            if (!bEnvShort[iEnvLevel])
               strcat(sBig, "\n<p>");
            
         }
         else
         {
            sprintf(sBig, "<tr><td>&nbsp;</td>\n<td>%s", sHtmlPropfontStart);
         }
         
         bParagraphOpen = TRUE;
         bEnv1stItem[iEnvLevel] = FALSE;
         
         /* Dafuer sorgen, dass in token_output() nicht noch */
         /* ein <P> vor <TR> gesetzt wird! */

         html_ignore_p = TRUE;
         
      }  /* switch (iEnvType[iEnvLevel]) */

      
      if (insert_placeholder(sBig, sBig, sBig, sBig))
      {
         um_strcpy(token[0], sBig, MAX_TOKEN_LEN+1, "c_item[24]");
      }
      else
      {
         token[0][0] = EOS;
      }

      break;


   case TOLDS:
      switch (iEnvType[iEnvLevel])
      {
      case ENV_ITEM:
      case ENV_ENUM:
         um_strcpy(token[0], "<item>", MAX_TOKEN_LEN+1, "c_item[25]");
         break;
       
      case ENV_DESC:
         token[0][0] = EOS;
         
         if (token[1][0] == '[')
         {
            add_description();
            delete_once(token[0], "[");
            delete_last(token[0], "]");
            strinsert(token[0], "<tag>");
            um_strcat(token[0], "</tag>", MAX_TOKEN_LEN+1, "c_item[26]");
         }
         else
         {
            um_strcpy(token[0], "<tag> </tag>", MAX_TOKEN_LEN+1, "c_item[27]");
         }
         
         break;
       
      case ENV_LIST:   /* Hier genau wie bei ASCII */
         um_strcpy(token[0], " ", MAX_TOKEN_LEN+1, "c_item[28]");
         
         if (token[1][0] == '[')
         {
            add_description();
            delete_once(token[0], "[");
            delete_last(token[0], "]");
         }

         ll = iEnvIndent[iEnvLevel]-2;    /* Die 2 Leerzeichen Ausgleich oben hier beruecksichtigen! */
         tl = toklen(token[0]);
         
         while ((int) tl <= ll)
         {
            um_strcat(token[0], " ", MAX_TOKEN_LEN+1, "c_item[29]");
            tl++;
         }

         strcpy_prev_indent(li);
         sprintf(s, "%s%s", li, token[0]);
         um_strcpy(token[0], s, MAX_TOKEN_LEN+1, "c_item[30]");
         
      }  /* switch (iEnvType[iEnvLevel]) */
      
      break;
      

   case TOHPH:
      switch (iEnvType[iEnvLevel])
      {
      case ENV_ITEM:
      case ENV_ENUM:
         um_strcpy(token[0], "<item>", MAX_TOKEN_LEN+1, "c_item[31]");
         break;
       
      case ENV_DESC:
         um_strcpy(token[0], "<item>", MAX_TOKEN_LEN+1, "c_item[32]");
         
         if (token[1][0] == '[')
         {
            add_description();
            replace_once(token[0], "[", "<emph>");
            replace_last(token[0], "]", "<\\emph>");
         }
         else
         {
            um_strcpy(token[0], "<item>", MAX_TOKEN_LEN+1, "c_item[33]");
         }
         
         break;
       
      case ENV_LIST:   /* Hier genau wie bei ASCII */
         um_strcpy(token[0], " ", MAX_TOKEN_LEN+1, "c_item[34]");
         
         if (token[1][0] == '[')
         {
            add_description();
            delete_once(token[0], "[");
            delete_last(token[0], "]");
         }

         ll = iEnvIndent[iEnvLevel]-2;    /* Die 2 Leerzeichen Ausgleich oben hier beruecksichtigen! */
         tl = toklen(token[0]);
         
         while ((int) tl <= ll)
         {
            um_strcat(token[0], " ", MAX_TOKEN_LEN+1, "c_item[35]");
            tl++;
         }

         strcpy_prev_indent(li);
         sprintf(s, "%s%s", li, token[0]);
         um_strcpy(token[0], s, MAX_TOKEN_LEN+1, "c_item[36]");
      }
      
      break;


   case TOIPF:
      switch (iEnvType[iEnvLevel])
      {
      case ENV_ITEM:
      case ENV_ENUM:
         strcpy(token[0], ":li.");
         break;
          
      case ENV_DESC:
         um_strcpy(token[0], ":dt.", MAX_TOKEN_LEN+1, "c_item[37]");
         
         if (token[1][0] == '[')
         {
            add_description();
            replace_once(token[0], "[", BOLD_ON);
            replace_last(token[0], "]", BOLD_OFF);
         }
         
         um_strcat(token[0], "\n:dd.", MAX_TOKEN_LEN+1, "c_item[38]");
         break;

      case ENV_LIST:
         um_strcpy(token[0], ":dt.", MAX_TOKEN_LEN+1, "c_item[39]");
         
         if (token[1][0]=='[')
         {
            add_description();
            
            switch (env_kind[iEnvLevel])
            {   
            case LIST_NORMAL:
               delete_once(token[0], "[");
               delete_last(token[0], "]");
               break;
               
            case LIST_BOLD:
               replace_once(token[0], "[", BOLD_ON);
               replace_last(token[0], "]", BOLD_OFF);
               break;
               
            case LIST_ITALIC:
               replace_once(token[0], "[", ITALIC_ON);
               replace_last(token[0], "]", ITALIC_OFF);
               break;
               
            case LIST_TYPEWRITER:
               replace_once(token[0], "[", TWRITER_ON);
               replace_last(token[0], "]", TWRITER_OFF);
            }
         }
         
         um_strcat(token[0], "\n:dd.", MAX_TOKEN_LEN+1, "c_item[40]");
      }
      
      break;
      
   
   case TOKPS:
      switch (iEnvType[iEnvLevel])
      {
      case ENV_ITEM:
         um_strcpy(token[0], itemchar[iItemLevel], MAX_TOKEN_LEN+1, "c_item[41]");
         break;
         
      case ENV_ENUM:
         enum_count[iEnvLevel]++;
         itoenum(iEnumLevel, &(enum_count[iEnvLevel]), s);
                                          /* Changed in V6.5.5 [NHz] */
         sprintf(token[0], "%s\n%s%d.%s off%d writeBeforeLeft\n%s", KPSPC_S, KPSPO_S, enum_count[iEnvLevel], KPSPC_S, iEnvLevel, KPSPO_S);
         break;

                                          /* New in r6pl15 [NHz] */
      case ENV_DESC:
         token[0][0] = EOS;
         strcpy_prev_indent(li);
         
         if (token[1][0] == '[')
         {
            add_description();

            ri[0] = EOS;
            ll = iEnvIndent[iEnvLevel]-2;
            tl = toklen(token[0]);

            sAdd[0] = EOS;
            
            if (((int) tl) < ll)
            {
               memset(sAdd, ' ', (size_t) (ll-tl));
               sAdd[ll-tl] = EOS;
               /* sAdd wird weiter unten hinzugefuegt */
            }

            delete_once(token[0], "[");
            delete_last(token[0], "]");
                                          /* Changed in V6.5.5 [NHz] */
            sprintf(s, "%s udoshow Bon %s%s%s offDesc writeBeforeLeft Boff %s", KPSPC_S, KPSPO_S, token[0], KPSPC_S, KPSPO_S);

            um_strcpy(token[0], s, MAX_TOKEN_LEN+1, "c_item[42]");
            um_strcat(token[0], sAdd, MAX_TOKEN_LEN+1, "c_item[43]");
         }
         
         break;
         
/* substituted by code above
      case ENV_DESC:
         token[0][0] = EOS;
         strcpy_prev_indent(li);
         
         if (token[1][0] == '[')
         {
            add_description();
            replace_once(token[0], "[", BOLD_ON);
            replace_last(token[0], "]", BOLD_OFF);
            strinsert(token[0], li);
            strinsert(token[0], " ");
         }
         
         break;
*/
      case ENV_LIST:
         token[0][0] = EOS;
            
         if (token[1][0] == '[')
         {
            add_description();
            delete_once(token[0], "[");
            delete_last(token[0], "]");
         }

         ri[0] = EOS;
         
         ll = iEnvIndent[iEnvLevel]-2;
         tl = toklen(token[0]);

         sAdd[0] = EOS;
         
         if (((int) tl) < ll)
         {
            memset(sAdd, ' ', (size_t) (ll-tl));
            sAdd[ll-tl] = EOS;
            /* sAdd wird weiter unten hinzugefuegt */
         }

         strcpy_prev_indent(li);

         switch (env_kind[iEnvLevel])
         {
         case LIST_BOLD:
                                          /* Changed in V6.5.5 [NHz] */
            sprintf(s, "%s udoshow Bon %s%s%s offList offCountS get writeBeforeLeft Boff %s", KPSPC_S, KPSPO_S, token[0], KPSPC_S, KPSPO_S);
            break;
         case LIST_ITALIC:
                                          /* Changed in V6.5.5 [NHz] */
            sprintf(s, "%s udoshow Ion %s%s%s offList offCountS get writeBeforeLeft Ioff %s", KPSPC_S, KPSPO_S, token[0], KPSPC_S, KPSPO_S);
            break;
         case LIST_TYPEWRITER:
                                          /* Changed in V6.5.5 [NHz] */
            sprintf(s, "%s udoshow Von %s%s%s offList offCountS get writeBeforeLeft Voff  %s", KPSPC_S, KPSPO_S, token[0], KPSPC_S, KPSPO_S);
            break;
         default:
                                          /* Changed in V6.5.5 [NHz] */
            sprintf(s, "%s udoshow %s%s%s offList offCountS get writeBeforeLeft %s", KPSPC_S, KPSPO_S, token[0], KPSPC_S, KPSPO_S);
         }

         um_strcpy(token[0], s, MAX_TOKEN_LEN+1, "c_item[44]");
         um_strcat(token[0], sAdd, MAX_TOKEN_LEN+1, "c_item[45]");
      }
      
      if (use_justification)
      {
         space2indent(token[0]);
      }
      
   }  /* switch (desttype) */
   
/*   bEnv1stItem[iEnvLevel] = FALSE;
*/

}  /* c_item() */





/*******************************************************************************
*
*  c_end_list():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void c_end_list(

int   listkind)  /* */
{
   switch (desttype)
   {
   case TOLDS:
   case TOHPH:
   case TONRO:
      c_end_description();
      return;
   
   case TOHTM:
   case TOHAH:
      if (html_no_xlist)
      {
         c_end_description();
         return;
      }
   }

   switch (listkind)
   {
   case LIST_BOLD:
      check_env_end (ENV_LIST, listkind, CMD_END_BLIST);
      break;
      
   case LIST_ITALIC:
      check_env_end (ENV_LIST, listkind, CMD_END_ILIST);
      break;
      
   case LIST_TYPEWRITER:
      check_env_end (ENV_LIST, listkind, CMD_END_TLIST);
      break;
      
   default:
      check_env_end (ENV_LIST, listkind, CMD_END_XLIST);
   }

   if (iListLevel == 0)
   {
      switch (listkind)
      {
      case LIST_BOLD:
         error_end_without_begin(CMD_END_BLIST, CMD_BEGIN_BLIST);
         break;
         
      case LIST_ITALIC:
         error_end_without_begin(CMD_END_ILIST, CMD_BEGIN_ILIST);
         break;
         
      case LIST_TYPEWRITER:
         error_end_without_begin(CMD_END_TLIST, CMD_BEGIN_TLIST);
         break;
         
      default:
         error_end_without_begin(CMD_END_XLIST, CMD_BEGIN_XLIST);
      }
   }
   
   if (iEnvLevel > 0)
   {
      iEnvIndent[iEnvLevel] = 0;
      iEnvLevel--;
   }

   if (iListLevel > 0)
   {
      iListLevel--;
   }
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      switch (listkind)
      {
      case LIST_BOLD:
         outln("\\end{blist}");
         break;
         
      case LIST_ITALIC:
         outln("\\end{ilist}");
         break;
         
      case LIST_TYPEWRITER:
         outln("\\end{tlist}");
         break;
         
      default:
         outln("\\end{xlist}");
      }
      
      outln("");
      break;
      
      
   case TOLYX:
      if (iEnvLevel>0)
      {
         outln("\\end_deeper");
      }
      
      break;
      
      
   case TOINF:
      outln("@end table");
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      voutlnf("%s", sHtmlPropfontEnd);
      
      if (bParagraphOpen)
         if (!bEnvShort[iEnvLevel])
            out("</p>");

      outln("</td></tr>\n</table>\n");

      html_ignore_p = FALSE;              /*r6pl6*/
      bParagraphOpen = FALSE;
      break;
      
      
   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      if (iEnvLevel == 0)
      {
         outln("\\pard\\");
      }
      
      break;
      
      
   case TOIPF:                            /*r6pl3*/
      outln(":edl.");
      break;
      
      
                                          /* New in r6pl15 [NHz] */
   case TOKPS:
/*    outln("offList subOffFromLeft");
*/
      outln("offList offCountS get subOffFromLeft");
      outln("/offCount offCount 1 sub def");
      outln("/offCountS offCount 4 add def");
   }
   
   end_env_output_line(iEnvLevel + 1);
}





/*******************************************************************************
*
*  c_end_xlist():
*     wrapper for c_end_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_xlist(void)
{
   c_end_list(LIST_NORMAL);
}





/*******************************************************************************
*
*  c_end_blist():
*     wrapper for c_end_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_blist(void)
{
   c_end_list(LIST_BOLD);
}





/*******************************************************************************
*
*  c_end_ilist():
*     wrapper for c_end_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_ilist(void)
{
   c_end_list(LIST_ITALIC);
}





/*******************************************************************************
*
*  c_end_tlist():
*     wrapper for c_end_list()
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_tlist(void)
{
   c_end_list(LIST_TYPEWRITER);
}





/*******************************************************************************
*
*  c_end_description():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_description(void)
{
   if (iDescLevel == 0)
   {
      error_end_without_begin(CMD_END_DESCRIPTION, CMD_BEGIN_DESCRIPTION);
   }

   check_env_end (ENV_DESC, 0, CMD_END_DESCRIPTION);

   if (iEnvLevel > 0)
   {
      iEnvIndent[iEnvLevel] = 0;
      iEnvLevel--;
   }
   
   if (iDescLevel > 0)
   {
      iDescLevel--;
   }
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\end{description}");
      outln("");
      break;
      
   case TOLYX:
      if (iEnvLevel > 0)
      {
         outln("\\end_deeper");
      }
      
      break;
      
   case TOINF:
      outln("@end table");
      break;
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      if (bParagraphOpen)
      {
         if (bEnvShort[iEnvLevel + 1])    /* iEnvLevel has already been decreased */
         {
            if (html_doctype < XHTML_STRICT)
               outln("<br>\n");
            else
               outln("<br />\n");
         }
         else
            outln("</p>\n");
      }
      
      bParagraphOpen = FALSE;
      
      outln("</dd>\n</dl>\n");            /* Changed in V6.5.11 [NHz] */
      bDescDDOpen = FALSE;                /* close DD flag anyway */
      break;
      
   case TOHPH:
      outln("<\\list>");
      break;
      
   case TOLDS:
      outln("</descrip>");
      break;
      
   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      if (iEnvLevel == 0)
      {
         outln("\\pard\\");
      }
      
      break;
      
   case TOIPF:                            /*r6pl3*/
      outln(":edl.");
      break;
      
   case TOKPS:                            /* New in r6pl15 [NHz] */
      outln("description");
      outln("offDesc subOffFromLeft");
   }

   end_env_output_line(iEnvLevel + 1);
}





/*******************************************************************************
*
*  c_end_enumerate():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_enumerate(void)
{
   if (iEnumLevel == 0)
   {
      error_end_without_begin(CMD_END_ENUMERATE, CMD_BEGIN_ENUMERATE);
   }

   check_env_end (ENV_ENUM, 0, CMD_END_ENUMERATE);

   if (iEnvLevel > 0)
   {
      iEnvIndent[iEnvLevel] = 0;
      iEnvLevel--;
   }
   
   if (iEnumLevel > 0)
   {
      iEnumLevel--;
   }

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\end{enumerate}");
      outln("");
      break;
      
   case TOLYX:
      if (iEnvLevel>0)
      {
         outln("\\end_deeper");
      }
      
      break;
      
   case TOINF:
      outln("@end enumerate");
      outln("");
      break;
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      outln("</li>");                     /* r6pl6: Mit </li> */
      outln("</ol>\n");
      break;
      
   case TOHPH:
      outln("<\\list>");
      break;
      
   case TOLDS:
      outln("</enum>");
      break;
      
   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      if (iEnvLevel == 0)
      {
         outln("\\pard\\");
      }
      
      break;
      
   case TOIPF:                            /*r6pl3*/
      outln(":eol.");
      break;
      
   case TOKPS:
      voutlnf("off%d subOffFromLeft", iEnvLevel + 1);
      outln("newline");
   }

   end_env_output_line(iEnvLevel + 1);
}





/*******************************************************************************
*
*  c_end_itemize():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_itemize(void)
{
   if (iItemLevel == 0)
   {
      error_end_without_begin(CMD_END_ITEMIZE, CMD_BEGIN_ITEMIZE);
   }

   check_env_end (ENV_ITEM, 0, CMD_END_ITEMIZE);
   
   if (iEnvLevel > 0)
   {
      iEnvIndent[iEnvLevel] = 0;
      iEnvLevel--;
   }

   if (iItemLevel > 0)
   {
      iItemLevel--;
   }

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\end{itemize}");
      outln("");
      break;
      
      
   case TOLYX:
      if (iEnvLevel > 0)
      {
         outln("\\end_deeper");
      }
      
      break;
      
      
   case TOINF:
      outln("@end itemize");
      outln("");
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      outln("</li>");                     /* r6pl6: mit </li> */
      outln("</ul>\n");
      break;
      
      
   case TOHPH:
      outln("<\\list>");
      break;
      
      
   case TOLDS:
      outln("</itemize>");
      break;
      
      
   case TORTF:
   case TOAQV:
   case TOWIN:
   case TOWH4:
      if (iEnvLevel == 0)
      {
         outln("\\pard\\");
      }
      
      break;
      
      
   case TOIPF:                            /*r6pl3*/
      outln(":eul.");
      break;
      
      
   case TOKPS:
      voutlnf("off%d subOffFromLeft", iEnvLevel+1);
      outln("newline");
   }

   end_env_output_line(iEnvLevel + 1);
}





/*******************************************************************************
*
*  output_tex_environments():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_tex_environments(void)
{
   outln("\\def\\hidelink#1{}");          /* V6.5.20 [CS] */
   outln("");
   
   outln("\\begin{document}");
   outln("");
   
   outln("\\newenvironment{xlist}[1]{\\begin{list}{}{\\settowidth{\\labelwidth}{#1}");
   outln("  \\setlength{\\leftmargin}{\\labelwidth} \\addtolength{\\leftmargin}{\\labelsep}");
   outln("  \\setlength{\\parsep}{0.5ex plus0.2ex minus0.2ex}");
   outln("  \\setlength{\\itemsep}{0.3ex}");
   outln("  \\renewcommand{\\makelabel}[1]{##1\\hfill}}}{\\end{list}}");
   outln("");
   
   outln("\\newenvironment{blist}[1]{\\begin{list}{}{\\settowidth{\\labelwidth}{{\\bf #1}}");
   outln("  \\setlength{\\leftmargin}{\\labelwidth} \\addtolength{\\leftmargin}{\\labelsep}");
   outln("  \\setlength{\\parsep}{0.5ex plus0.2ex minus0.2ex}");
   outln("  \\setlength{\\itemsep}{0.3ex}");
   outln("  \\renewcommand{\\makelabel}[1]{{\\bf ##1}\\hfill}}}{\\end{list}}");
   outln("");
   
   outln("\\newenvironment{ilist}[1]{\\begin{list}{}{\\settowidth{\\labelwidth}{{\\it #1}}");
   outln("  \\setlength{\\leftmargin}{\\labelwidth} \\addtolength{\\leftmargin}{\\labelsep}");
   outln("  \\setlength{\\parsep}{0.5ex plus0.2ex minus0.2ex}");
   outln("  \\setlength{\\itemsep}{0.3ex}");
   outln("  \\renewcommand{\\makelabel}[1]{{\\it ##1}\\hfill}}}{\\end{list}}");
   outln("");
   
   outln("\\newenvironment{tlist}[1]{\\begin{list}{}{\\settowidth{\\labelwidth}{{\\tt #1}}");
   outln("  \\setlength{\\leftmargin}{\\labelwidth} \\addtolength{\\leftmargin}{\\labelsep}");
   outln("  \\setlength{\\parsep}{0.5ex plus0.2ex minus0.2ex}");
   outln("  \\setlength{\\itemsep}{0.3ex}");
   outln("  \\renewcommand{\\makelabel}[1]{{\\tt ##1}\\hfill}}}{\\end{list}}");
   outln("");
   
   outln("");
   
   outln("\\makeatletter");
   outln("\\@ifundefined{LaTeXe}%");
   outln("  {\\def\\LaTeXe{{\\protect\\LaTeX{}2${}_{\\textstyle\\varepsilon}$}}");
   outln("   \\def\\textbf#1{{\\bf #1}}");
   outln("   \\def\\textit#1{{\\it #1}}");
   outln("   \\def\\texttt#1{{\\tt #1}}");
   outln("  }");
   outln("  {\\def\\underlined#1{\\relax}");
   outln("  }");
   outln("\\makeatother");
   outln("");
   
   outln("");
}





/*******************************************************************************
*
*  output_rtf_colortbl():
*     output the RTF color table
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_rtf_colortbl(void)
{
   outln("{\\colortbl;");
   outln("\\red0\\green0\\blue0;");       /* \cf1:  black */   /*r6pl5: siehe HTML 3.2 DTD */
   outln("\\red192\\green192\\blue192;"); /* \cf2:  silver */
   outln("\\red128\\green128\\blue128;"); /* \cf3:  gray */
   outln("\\red255\\green255\\blue255;"); /* \cf4:  white */
   outln("\\red128\\green0\\blue0;");     /* \cf5:  maroon */
   outln("\\red255\\green0\\blue0;");     /* \cf6:  red */
   outln("\\red128\\green0\\blue128;");   /* \cf7:  purple */
   outln("\\red255\\green0\\blue255;");   /* \cf8:  fuchsia */
   outln("\\red0\\green128\\blue0;");     /* \cf9:  green */
   outln("\\red0\\green255\\blue0;");     /* \cf10: lime */
   outln("\\red128\\green128\\blue0;");   /* \cf11: olive */
   outln("\\red255\\green255\\blue0;");   /* \cf12: yellow */
   outln("\\red0\\green0\\blue128;");     /* \cf13: navy */
   outln("\\red0\\green0\\blue255;");     /* \cf14: blue */
   outln("\\red0\\green128\\blue128;");   /* \cf15: teal */
   outln("\\red0\\green255\\blue255;");   /* \cf16: aqua */
   
                                          /* New in V6.5.9 [NHz] */
   if (sDocColour[0] != EOS)
      outln(sDocColour);
   
   outln("}");
}





/*******************************************************************************
*
*  c_begin_document():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_document(void)
{
   char   s[512];  /* */
   int    i;       /* counter */
   

   if (bCalledBeginDocument)
   {
      error_called_twice(CMD_BEGIN_DOCUMENT);
      return;
   }

   bInsideDocument = TRUE;

   switch (desttype)
   {
   case TOPDL:
                                          /* Changed in r6.2pl1 [NHz] */
      if (titdat.author != NULL || titdat.title != NULL || titdat.program != NULL)
      {
         outln("\\pdfinfo {");
         
         if (titdat.title != NULL)
            voutlnf("  /Title (%s)", titdat.title);
            
         if (titdat.author != NULL)
            voutlnf("  /Author (%s)", titdat.author);
         
         voutlnf("  /Creator (UDO Version %s.%s %s for %s)", UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS);
         voutlnf("  /CreationDate (D:%d%02d%02d%02d%02d%02d)", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin, iDateSec);
         voutlnf("  /ModDate (D:%d%02d%02d%02d%02d%02d)", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin, iDateSec);
         
         if (titdat.description != NULL)
            voutlnf("  /Subject (%s)", titdat.description);
            
         if (titdat.keywords != NULL)
         {                                /* Set by !docinfo [keywords] foo */
            voutlnf("  /Keywords (%s)", titdat.keywords);
         }
            
         outln("}");
      }
      
      output_tex_environments();
      break;
      

   case TOTEX:
      output_tex_environments();
      break;
      
      
   case TOLYX:                            /* <???> */
      break;
      
      
   case TOINF:
      outln("\\input texinfo @c-*-texinfo-*-");
      outln("@c %**start of header");
      voutlnf("@setfilename %s.info", outfile.name);
      strcpy(s, titleprogram);
      auto_quote_chars(s, TRUE);
      
      if (s[0] == EOS)
      {
         strcpy(s, lang.unknown);
      }
      
      voutlnf("@settitle %s", s);
      outln("@c %**end of header");
      break;
      
      
   case TOMAN:
      man_headline();
      break;
      
      
   case TONRO:
      sprintf(s, ".TH ");
      if (titdat.program != NULL)
      {
         strcat(s, titdat.program);
      }
      else
      {
         strcat(s, lang.unknown);
      }
      
      if (sDocNroffType[0] != EOS)
      {
         strcat(s, " ");
         strcat(s, sDocNroffType);
      }
      else
      {
         strcat(s, " 1");
      }
      
      strcat(s, " \"");
      
      if (titdat.date != NULL)
      {
         strcat(s, titdat.date);
      }
      else
      {
         strcat(s, lang.today);
      }
      
      strcat(s, "\"");
      
      if (titdat.author != NULL)
      {
         strcat(s, " \"");
         strcat(s, titdat.author);
         strcat(s, "\"");
      }
      
      outln(s);
      break;
      
      
   case TOSTG:
   case TOAMG:
      if (titdat.stg_database != NULL)
      {
         if (*titdat.stg_database != EOS)
            voutlnf("@database \"%s\"", titdat.stg_database);
      }
      else if (titleprogram[0] != EOS)
      {
         voutlnf("@database \"%s\"", titleprogram);
      }
      else
      {
         voutlnf("@database \"%s\"", lang.unknown);
      }
      

      if (titdat.author != NULL)
      {
         voutlnf("@author \"%s\"", titdat.author);
      }

      if (titdat.version != NULL)
      {
         if (titdat.date != NULL)
         {
            voutlnf("@$VER: %s (%s)", titdat.version, titdat.date);
         }
         else
         {
            voutlnf("@$VER: %s", titdat.version);
         }
      }
      else
      {
         if (titdat.date != NULL)
         {
            voutlnf("@$VER: %s", titdat.date);
         }
      }

                                          /* 6/1: immer ausgeben */
      voutlnf("@width %d", (int) zDocParwidth);
      
      if (uses_maketitle)
      {
         voutlnf("@default %s", lang.title);
      }
      else
      {
         if (uses_tableofcontents)
         {
            outln("@default Main");       /*r6pl5: Main statt lang.contents */
         }
      }
      
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      if (titdat.htmltitle != NULL && titdat.htmltitle[0] != EOS)
      {
         output_html_header(titdat.htmltitle);
      }
      else
      {
         if (titleprogram[0] != EOS)
         {
            output_html_header(titleprogram);
         }
         else
         {
            output_html_header(lang.unknown);
         }
      }

      html_headline();

      break;
      
      
   case TORTF:
                                          /* RTF-HEADER */
      if (sDocPropfont[0] == EOS)
      {
         strcpy(sDocPropfont, "Times New Roman");
      }
      
      if (sDocMonofont[0] == EOS)
      {
         strcpy(sDocMonofont, "Courier New");
      }
      
      voutlnf("{\\rtf1\\ansi{\\fonttbl{\\f0\\froman %s;}{\\f1\\fswiss %s;}{\\f2\\fmodern MS LineDraw;}}", sDocPropfont, sDocMonofont);
      out("{\\stylesheet");

      if (sDocPropfontSize[0] != EOS)
         iDocPropfontSize = atoi(sDocPropfontSize) * 2;
      else
         iDocPropfontSize = 11 * 2;       /* Times New Roman 11pt */

      if (sDocMonofontSize[0] != EOS)
         iDocMonofontSize = atoi(sDocMonofontSize) * 2;
      else
         iDocMonofontSize = 10 * 2;       /* Courier New 10pt */

                                          /* New in r6pl16 [NHz] */
                                          /* Size of nodes */
      if (laydat.node1size != 0)
         laydat.node1size *= 2;
      else
         laydat.node1size = iDocPropfontSize + 14;

      if (laydat.node2size != 0)
         laydat.node2size *= 2;
      else
         laydat.node2size = iDocPropfontSize + 6;

      if (laydat.node3size != 0)
         laydat.node3size *= 2;
      else
         laydat.node3size = iDocPropfontSize;

      if (laydat.node4size != 0)
         laydat.node4size *= 2;
      else
         laydat.node4size = iDocPropfontSize;

      voutlnf("{%s\\fs%d\\snext0 Normal;}",   rtf_norm,  iDocPropfontSize);
      voutlnf("{%s\\fs%d\\snext1 Verbatim;}", rtf_verb,  iDocMonofontSize);
      voutlnf("{%s\\fs%d\\snext2 Chapter;}",  rtf_chapt, iDocPropfontSize + 28);

                                          /* Changed in r6pl16 [NHz] */
      voutlnf("{%s\\fs%d\\snext3 Node1;}",    rtf_node1,     laydat.node1size);
      voutlnf("{%s\\fs%d\\snext4 Node2;}",    rtf_node2,     laydat.node2size);
      voutlnf("{%s\\fs%d\\snext5 Node3;}",    rtf_node3,     laydat.node3size);
      voutlnf("{%s\\fs%d\\snext6 Node4;}",    rtf_node4,     laydat.node4size);
      voutlnf("{%s\\fs%d\\snext7 Chapter*;}", rtf_inv_chapt, iDocPropfontSize + 28);

                                          /* Changed in r6pl16 [NHz] */
      voutlnf("{%s\\fs%d\\snext8 Node1*;}",    rtf_inv_node1, laydat.node1size);
      voutlnf("{%s\\fs%d\\snext9 Node2*;}",    rtf_inv_node2, laydat.node2size);
      voutlnf("{%s\\fs%d\\snext10 Node3*;}",   rtf_inv_node3, laydat.node3size);
      voutlnf("{%s\\fs%d\\snext11 Node4*;}",   rtf_inv_node4, laydat.node4size);
      voutlnf("{%s\\fs%d\\snext13 LineDraw;}", rtf_linedraw,  iDocMonofontSize);

      output_rtf_colortbl();

      outln("}");
      outln("\\paperw11904\\paperh16836");
      outln("\\margl1134\\margr1134\\margt1984\\margb1984");

                                          /* New '\widowctrl' in r6pl15 [NHz] */
      outln("\\pgnstart1\\ftnbj\\ftnrestart\\facingp\\margmirror\\makeback\\widowctrl");
      outln("\\sectd\\pgndec\\headery1134\\footery1134\\cols1\\colsx567\\pgndec");

                                          /* New in V6.5.9 [NHz] */
      voutlnf("{\\*\\revtbl {Unknown;}{UDO Version %s.%s %s;}}", UDO_REL, UDO_SUBVER, UDO_BUILD);

      voutlnf("\\f0\\fs%d", iDocPropfontSize);   

      if (!check_output_raw_header())     /* New in V6.5.9 [NHz];
                                             hier muss auch der Fussteil uebergeben werden, sonst
                                             funktioniert es in RTF nicht? */
      {
         if (titleprogram[0] != EOS)
         {
            if (!no_headlines)            /* r6pl6*/
            {
               voutlnf("{\\headerl\\pard\\plain\\pard\\tqr\\tx9636\\f0\\fs%d {\\i %s \\chpgn\\tab %s}\\par}", iDocPropfontSize, lang.page, titleprogram);
               voutlnf("{\\headerr\\pard\\plain\\pard\\tqr\\tx9636\\f0\\fs%d {\\i %s\\tab %s \\chpgn}\\par}", iDocPropfontSize, titleprogram, lang.page);
            }
         }
      }
      
      outln("{\\info");                   /* PL9: Infoblock ausgeben */


      /* ---- \author ---- */
      
      s[0] = EOS;
      
      if (titdat.author != NULL)
      {
         strcpy(s, titdat.author);
      }
      else
      {
         if (config.bRegistered)
         {
            strcpy(s, config.strUserName);
            auto_quote_chars(s, TRUE);
         }
      }
      
      if (s[0] != EOS)
      {
         voutlnf("  {\\author %s}", s);
      }


      /* ---- \title ---- */
      
      if (titleprogram[0] != EOS)
      {
         voutlnf("  {\\title %s}", titleprogram);
      }

                                          /* New in V6.5.2 [NHz] */
      /* ---- \description ---- */
      
      if (titdat.description != NULL)     /* v6.5.6 [vj] added test for NULL, otherwise UDO might crash */
      {
         if (titdat.description[0] != EOS)
         {
            voutlnf("  {\\subject %s}", titdat.description);
         }
      }

                                          /* New in V6.5.2 [NHz] */
      /* ---- \keywords ---- */
      
      if (titdat.keywords != NULL)        /* v6.5.6 [vj] added test for NULL, otherwise UDO might crash */
      {
         if (titdat.keywords[0] != EOS)
         {
            voutlnf("  {\\keywords %s}", titdat.keywords);
         }
      }

                                          /* New in V6.5.2 [NHz] */
      /* ---- \company ---- */
      
      if (titdat.company != NULL)         /* v6.5.6 [vj] added test for NULL, otherwise UDO might crash */
      {
         if (titdat.company[0] != EOS)
         {
            voutlnf("  {\\*\\company %s}", titdat.company);
         }
      }

                                          /* New in V6.5.2 [NHz] */
      /* ---- \category ---- */
      
      if (titdat.category != NULL)        /* v6.5.6 [vj] added test for NULL, otherwise UDO might crash */
      {
         if (titdat.category[0] != EOS)
         {
            voutlnf("  {\\*\\category %s}", titdat.category);
         }
      }

      /* ---- \translator ---- */

      if (titdat.translator != NULL)
      {
         if (titdat.translator[0] != EOS)
         {
            voutlnf("  {\\*\\translator %s}", titdat.translator);
         }
      }

      /* ---- \distributor ---- */
      
      if (titdat.distributor != NULL)
      {
         if (titdat.distributor[0] != EOS)
         {
            voutlnf("  {\\*\\distributor %s}", titdat.distributor);
         }
      }

      /* ---- About UDO ---- */
      
      voutlnf("  {\\doccomm UDO Version %s.%s %s}", UDO_REL, UDO_SUBVER, UDO_BUILD);

      /* ---- Erstellungsdatum & Sonstiges ---- */
      
      voutlnf("  {\\creatim\\yr%d\\mo%d\\dy%d\\hr%d\\min%d}", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin);
      
      outln("  {\\version1}{\\nofpages0}{\\nofwords0}{\\nofchars0}{\\edmins0}");
      outln("}");

      outln(rtf_pardplain);
      voutlnf("%s\\fs%d", rtf_norm, iDocPropfontSize);
      break;
      
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
      if (sDocPropfont[0] == EOS)
      {
         strcpy(sDocPropfont, (desttype == TOWH4) ? "MS Sans Serif" : "Times New Roman");
      }
      
      if (sDocMonofont[0] == EOS)
      {
         strcpy(sDocMonofont, "Courier New");
      }
      
      outln("{\\rtf1\\ansi \\deff0");
      outln("{\\fonttbl");
      voutlnf(" {\\f0\\fswiss %s;}", sDocPropfont);
      voutlnf(" {\\f1\\fswiss %s;}", sDocMonofont);
      outln(" {\\f2\\ftech Symbol;}");
      outln("}");
      
      output_rtf_colortbl();
      
      if (sDocPropfontSize[0] != EOS)
         iDocPropfontSize = atoi(sDocPropfontSize) * 2;
      else if (desttype == TOWH4)
         iDocPropfontSize = 8 * 2;        /* MS Sans Serif 8pt */
      else
         iDocPropfontSize = 11 * 2;       /* Times New Roman 11pt */
      voutlnf("\\f0\\fs%d", iDocPropfontSize);   

      if (sDocMonofontSize[0] != EOS)
         iDocMonofontSize = atoi(sDocMonofontSize) * 2;
      else
         iDocMonofontSize = 10 * 2;       /* Courier New 10pt */

      outln(sDocTextColor);
      break;
      

   case TOLDS:
      outln("<!doctype linuxdoc system>");
      outln("");
      
      if (use_style_book)
      {
         outln("<book>");
         outln("");
      }
      else
      {
         outln("<article>");
         outln("");
      }

      if (titleprogram[0] != EOS)
      {
         voutlnf("<title>%s", titleprogram);
      }

      if (titdat.author != NULL || address_counter > 0)
      {
         out("<author>");
         
         if (titdat.author != NULL)
         {
            out(titdat.author);
         }
         
         if (address_counter > 0)
         {
            for (i = 1; i <= address_counter; i++)
            {
               if (titdat.address[i] != NULL)
               {
                  out(", ");
                  out(titdat.address[i]);
               }
            }
         }
         
         outln("");
      }
      
      if (titdat.date != NULL)
      {
         voutlnf("<date>%s", titdat.date);
      }
      
      break;


   case TOHPH:
      outln("<helpvolume>");
      outln("<metainfo>");

      if (titleprogram[0] != EOS)
      {
         voutlnf("<title>%s", titleprogram);
      }

      outln("<\\metainfo>");
      break;
      

   case TOIPF:
      outln(":userdoc.");
      outln(":docprof toc=1234.");        /*r6pl2*/
      
      if (titleprogram[0] != EOS)
      {
         voutlnf(":title.%s", titleprogram);
      }
      else
      {
         voutlnf(":title.%s", lang.unknown);
      }
      break;
      
      
   case TOKPS:
                                          /* New in r6pl16 [NHz] */
                                          /* Size of nodes */
      if (laydat.node1size == 0)
         laydat.node1size = laydat.propfontsize + 7;

      if (laydat.node2size == 0)
         laydat.node2size = laydat.propfontsize + 3;

      if (laydat.node3size == 0)
         laydat.node3size = laydat.propfontsize;

      if (laydat.node4size == 0)
         laydat.node4size = laydat.propfontsize;

      outln(UDO2PS);                      /* in udo2ps.h definiert (c) by Christian Krueger und Norbert Hanz */
      outln(UDO2PDF);                     /* in udo2pdf.h definiert (c) by Norbert Hanz */

      if (laydat.paper != NULL)
      {
         int   i;  /* counter */
         

         for (i = 0; i < MAXPAPERSIZE; i++)
         {
            if (strcmp(laydat.paper, paperSize[i].paper) == 0)
            {
               voutlnf("<< /PageSize [ %d %d ] >> setpagedevice", paperSize[i].width_pt, paperSize[i].height_pt);
               voutlnf("/cctopmargin   %d def", paperSize[i].margintop_pt);
               voutlnf("/ccleftmargin  %d def", paperSize[i].marginleft_pt);
               voutlnf("/ccrightmargin %d def", paperSize[i].marginright_pt);
               voutlnf("/cclowermargin %d def", paperSize[i].marginbottom_pt);
               outln("/topmargin      cctopmargin 20 sub def");
               outln("/lowermargin    cclowermargin def");
               outln("/rightmargin    ccrightmargin def");
               outln("/leftmargin     ccleftmargin def");
            }
         }
      }

/*    outln("/topmargin    792 def");
      outln("/lowermargin   72 def");
      outln("/rightmargin  540 def");
      outln("/leftmargin    90 def");
*/
      outln("/linespacing  1.5 def");
      outln("0 0 0 setBaseColor");        /* New in r6pl15 [NHz] */
      outln("setup");

                                          /* New in r6pl15 [NHz] */
      if (    (strstr(laydat.propfontname, "Helvetica"))
           || (strstr(laydat.propfontname, "Arial"))
           || (strstr(laydat.propfontname, "sans-serif"))
         )
         voutlnf("/basefont %d def", 1);
         
      voutlnf("/fontsize %d def", laydat.propfontsize);
      outln("basefont setBaseFont");
      
      voutlnf("/Titeltext (%s %s) def", titdat.title, titdat.program);
      
                                          /* Changed: Fixed bug #0000040 in r6.3pl16 [NHz] */
      if (titdat.author)
         voutlnf("/FootAuthor (\\251 %s) def", titdat.author);
      else
         outln("/FootAuthor () def");
      
                                          /* Document info */
      voutlnf("[ /Title (%s %s)", titdat.title, titdat.program);
      voutlnf("  /Author (%s)", titdat.author);
      
                                          /* Changed: Fixed bug #0000062 in V6.5.8 [NHz] */
      if (titdat.description)
         voutlnf("  /Subject (%s)", titdat.description);
      if (titdat.keywords)
      {                                   /* Set by !docinfo [keywords] foo */
         voutlnf("  /Keywords (%s)", titdat.keywords);
      }
      
      voutlnf("  /Creator (UDO Version %s.%s %s for %s)", UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS);
      voutlnf("  /CreationDate (D:%d%02d%02d%02d%02d%02d)", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin, iDateSec);
      voutlnf("  /ModDate (D:%d%02d%02d%02d%02d%02d)", iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin, iDateSec);
      outln("/DOCINFO pdfmark\n");

                                          /* How to open a PDF-document */
      voutlnf("%s %s %s %s %s %s HowToOpen\n",
                   laydat.pagemode,
                   laydat.openpage,
                   laydat.hidetoolbar,
                   laydat.hidemenubar,
                   laydat.viewerpreferences,
                   laydat.fitwindow);

      bookmarks_ps();
      
   }  /* switch (desttype) */
   
   bCalledBeginDocument = TRUE;

}  /* c_begin_document() */





/*******************************************************************************
*
*  c_end_document():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_document(void)
{
   char   n[128];  /* */
   
   
   if (bCalledEndDocument)
   {
      error_called_twice(CMD_END_DOCUMENT);
      return;
   }

   if (bCalledBeginDocument && !bInsideDocument)
   {
      error_end_without_begin(CMD_END_DOCUMENT, CMD_BEGIN_DOCUMENT);
   }

   check_styleflags();                    /* PL16 */
   check_endnode();

   if (use_about_udo)
   {
      output_about_udo();
      check_endnode();
   }

   switch (desttype)
   {
   case TOHTM:
   case TOHAH:
      if (!no_index)
      {
         save_html_index();
         check_endnode();
      }
      
      html_bottomline();
   }

   if (bInsideAppendix)
   {
      bInsideAppendix = FALSE;

      switch (desttype)
      {   
      case TOTEX:
      case TOPDL:
         outln("\\end{appendix}");
         outln("");
         break;
         
      case TOLYX:                         /* <???> */
         break;
         
      default:
         outln("");
      }
   }

   print_index();

   unregistered_copyright();
   bInsideDocument= FALSE;

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\end{document}");
      outln("");
      break;
      
      
   case TOLYX:                            /* <???> */
      break;
      
      
   case TOINF:
      if (called_tableofcontents)
      {
         outln("@iftex");
         outln("@shortcontents");
         outln("@contents");
         outln("@end iftex");
      }
      
      outln("@bye");
      break;
      
      
   case TOMAN:
      if (iManPageLength > 0)
      {
         if (iManPageLines < iManPageLength)
         {
            man_bottomline();
         }
      }
      
      break;
      
      
   case TORTF:
   case TOWIN:
   case TOWH4:
   case TOAQV:
      outln("}");
      outln("");
      break;
      
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      voutlnf("%s", sHtmlPropfontEnd);
      check_output_raw_footer(TRUE);
      outln("</body>");
      outln("</html>");
      break;
      
      
   case TOLDS:
      if (use_style_book)
      {
         outln("</book>");
         outln("");
      }
      else
      {
         outln("</article>");
         outln("");
      }
      
      break;
      
      
   case TOHPH:
      outln("<\\helpvolume>");
      break;
      
   
   case TOSRC:
   case TOSRP:
      if (use_about_udo)
      {
         memset(n, '#', 62);   n[62] = EOS;
         outln("");
         voutlnf("%s  %s", sSrcRemOn, n);
         voutlnf("    # @(#) %s%s - made with UDO Version %s.%s %s for %s", outfile.name, outfile.suff, UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS);
         voutlnf("    %s %s", n, sSrcRemOff);
      }
      
      break;
      
      
   case TODRC:
      outln("%%");                        /*r6pl5*/
      break;
      
      
   case TOIPF:
      outln(":euserdoc.");
      break;         
      
      
   case TOKPS:
      outln("newpage");

      if (use_about_udo)                  /* New in r6pl15 [NHz] */
      {
         outln("/NodeName (About UDO) def");
         outln("/acty acty 50 sub def");
         outln("actx acty moveto");
         
         if (destlang == TOGER)
            voutlnf("(Version %s.%s %s) (%s) (%s) aboutUDO_ger", UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS, UDO_URL);
         else
            voutlnf("(Version %s.%s %s) (%s) (%s) aboutUDO_eng", UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS, UDO_URL);
            
         outln("newpage");
      }
   }

   bCalledEndDocument = TRUE;
}





/*******************************************************************************
*
*  c_begin_appendix():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_appendix(void)
{
   if (bCalledBeginAppendix)              /* PL6 */
   {
      error_called_twice(CMD_BEGIN_APPENDIX);
      return;
   }

   bInsideAppendix = TRUE;

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\begin{appendix}");
      break;
      
   case TOLYX:                            /* <???> */
      break;
      
   default:
      outln("");
   }

   bCalledBeginAppendix = TRUE;           /* PL6 */
}





/*******************************************************************************
*
*  c_end_appendix():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_appendix(void)
{
   if (bCalledEndAppendix)                /* PL6 */
   {
      error_called_twice(CMD_END_APPENDIX);
      return;
   }

   if (!bInsideAppendix)
   {
      error_end_without_begin(CMD_END_APPENDIX, CMD_BEGIN_APPENDIX);
   }
   
   /* Sonst nichts ausgeben, der Rest wird in c_end_document erledigt! */

   bCalledEndAppendix = TRUE;             /* PL6 */
}





/*******************************************************************************
*
*  init_module_env():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_env(void)
{
   int   i;  /* counter */

   for (i = 0; i < MAXENVLEVEL; i++)
   {
      bEnvShort[i]   = FALSE;
      bEnv1stItem[i] = TRUE;
      bEnv1stPara[i] = TRUE;
   }

   iEnvLevel  = 0;
   iItemLevel = 0;
   iEnumLevel = 0;
   iDescLevel = 0;
   quot_level = 0;
   iListLevel = 0;
   cent_level = 0;
   
   flushright_level = 0;
   flushleft_level  = 0;

   bCalledBeginDocument = FALSE;
   bCalledEndDocument   = FALSE;
   bCalledBeginAppendix = FALSE;
   bCalledEndAppendix   = FALSE;
}





/*******************************************************************************
*
*  init_env_itemchar():
*     initialize 'bullet' characters for itemize environment
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_env_itemchar(void)
{
   switch (desttype)
   {
   case TOSTG:
   case TOAMG:
   case TOASC:
   case TODRC:
   case TOMAN:
   case TONRO:
   case TOPCH:
   case TOTVH:
      strcpy(itemchar[1], ".");
      
      if (!no_umlaute)                    /* PL6 */
      {
         if (desttype == TOSTG)
            strcpy(itemchar[1], "\371");
         else
         {
#ifdef __TOS__
            strcpy(itemchar[1], "\371");
#endif
#ifdef __NEXTSTEP__
            strcpy(itemchar[1], "\367");
#endif
#ifdef __HPUX_ROMAN8__
            strcpy(itemchar[1], "\374");
#endif
#if defined(__MACOS__) || defined(__MACOSX__) || defined(__BEOS__)
            strcpy(itemchar[1], "\245");
#endif
         } /* if (desttype == TOSTG) */

      }   /* if (!no_umlaute) PL6 */

      strcpy(itemchar[2], "-");
      strcpy(itemchar[3], "*");
      strcpy(itemchar[4], ".");
      strcpy(itemchar[5], itemchar[1]);
      strcpy(itemchar[6], itemchar[2]);
      break;
   

   case TORTF:
      strcpy(itemchar[1], "\\bullet");
      strcpy(itemchar[2], "-");
      strcpy(itemchar[3], "*");
      strcpy(itemchar[4], ".");
      strcpy(itemchar[5], itemchar[1]);
      strcpy(itemchar[6], itemchar[2]);
      break;


   case TOWIN:
   case TOAQV:
      strcpy(itemchar[1], "{\\f2 \\'B7}");
      strcpy(itemchar[2], "\\'96");
      strcpy(itemchar[3], "\\'95");
      strcpy(itemchar[4], ".");
      strcpy(itemchar[5], itemchar[1]);
      strcpy(itemchar[6], itemchar[2]);
      break;


   case TOWH4:
      strcpy(itemchar[1], "{\\f2 \\'B7}");
      strcpy(itemchar[2], "-");
      strcpy(itemchar[3], "\\'95");
      strcpy(itemchar[4], ".");
      strcpy(itemchar[5], itemchar[1]);
      strcpy(itemchar[6], itemchar[2]);
      break;


   case TOKPS:
                                          /* Changed in V6.5.6 [NHz] */
      sprintf(itemchar[1], "%s\n/bullet off1 writeBulletLeft\n%s", KPSPC_S, KPSPO_S);
      sprintf(itemchar[2], "%s\n/endash off1 writeBulletLeft\n%s", KPSPC_S, KPSPO_S);
      sprintf(itemchar[3], "%s\n/asterix off1 writeBulletLeft\n%s", KPSPC_S, KPSPO_S);
      sprintf(itemchar[4], "%s\n/periodcentered off1 writeBulletLeft\n%s", KPSPC_S, KPSPO_S);
      strcpy(itemchar[5], itemchar[1]);
      strcpy(itemchar[6], itemchar[2]);
   }
}


/* +++ EOF +++ */
