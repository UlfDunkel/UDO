/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : upr.c
*  Symbol prefix: upr
*
*  Description  : This module write various entries to the project (*upr) file
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
*  Co-Authors   : Ulf Dunkel (fd), Thorsten Otto (tho)
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
*  2004:
*    tho Nov 14: created
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
#include <string.h>
#include <stdlib.h>
#include "udoport.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "udo.h"
#include "par.h"
#include "str.h"
#include "chr.h"
#include "udomem.h"
#include "lang.h"

#include "export.h"
#include "upr.h"

/*******************************************************************************
*
*  save_upr_entry_infile():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void save_upr_entry_infile(const char *filename, int level)
{
   if (bUseUPRfile && bUPRopened)
   {
      fprintf(fUPRfile, "infile\t%d\t%s\n", level, filename);
   }
}





/*******************************************************************************
*
*  save_upr_entry_outfile():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void save_upr_entry_outfile(const char *filename)
{
   if (bUseUPRfile && bUPRopened)
   {
      fprintf(fUPRfile, "outfile\t%s\n", filename);
   }
}





/*******************************************************************************
*
*  save_upr_entry_image():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void save_upr_entry_image(const char *filename)
{
   if (bUseUPRfile && bUPRopened)
   {
      fprintf(fUPRfile, "image\t%s\n", filename);
   }
}





/*******************************************************************************
*
*  convert_title():
*     Convert the line with the node name. We get the complete line here,
*     including the command.
*
*  Notes:
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL int convert_title(char *buf, const char *title)
{
   const char *s;
   int flag;
   char cbuf[8];
   const char *repl;
   
   s = strchr(title, ' ');
   if (s != NULL)
   {
      while (*s == ' ' || *s == '\t')
         s++;
      strcpy(buf, s);
      replace_macros(buf);
      replace_defines(buf);
      
      qdelete_all(buf, "!-", 2);
      
      replace_all(buf, "(!today)", get_lang()->today);
      replace_all(buf, "(!short_today)", get_lang()->short_today);
      
      qreplace_all(buf, "(\"\")", 4, TEMPO_S, TEMPO_S_LEN);
      qreplace_all(buf, "('')", 4, TEMPO_S2, TEMPO_S2_LEN);
      if (no_quotes)
      {
         qreplace_all(buf, "\"\"", 2, "\"", 1);
         qreplace_all(buf, "''", 2, "'", 1);
      } else
      {
         flag = FALSE;
         while (strstr(buf, "''") != NULL)
         {
            flag = !flag;
            replace_once(buf, "''", flag ? "`" : "'");
         }
         
         flag = FALSE;
         while (strstr(buf, "\"\"") != NULL)
         {
            flag = !flag;
            replace_once(buf, "\"\"", flag ? "\"" : "\"");
         }
      }
      qreplace_all(buf, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
      qreplace_all(buf, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
      
      qreplace_all(buf, "!..", 3, "...", 3);
      repl = unicode2char(U_CopyrightSign, cbuf);
      replace_all(buf, "(!copyright)",  repl);
      repl = unicode2char(U_RegisteredSign, cbuf);
      replace_all(buf, "(!registered)", repl);
      replace_all(buf, "(!reg)", repl);
      qreplace_all(buf, "(!grin)", 7, ";-)", 3);
      qreplace_all(buf, "(!laugh)", 8, ":-)", 3);
      repl = unicode2char(U_GreekSmallLetterAlpha, cbuf);
      if (*repl == '\0')
         repl = "alpha";
      replace_all(buf, "(!alpha)", repl);
      repl = unicode2char(U_GreekSmallLetterBeta, cbuf);
      if (*repl == '\0')
         repl = unicode2char(U_LatinSmallLetterSharpS, cbuf);
      if (*repl == '\0')
         repl = "beta";
      replace_all(buf, "(!beta)", repl);
      qreplace_all(buf, "(!tm)", 5, "(tm)", 4);
      qreplace_all(buf, "(!TeX)", 6, "TeX", 3);
      qreplace_all(buf, "(!LaTeX)", 8, "LaTeX", 5);
      qreplace_all(buf, "(!LaTeXe)", 9, "LaTeX2e", 7);
      qreplace_all(buf, "(!euro)", 7, "EUR", 3);
      qreplace_all(buf, "(!pound)", 8, "GBP", 3);
      qreplace_all(buf, "(!deg)", 6, " Grad", 5);
      
      qreplace_all(buf, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
      qreplace_all(buf, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
      qreplace_all(buf, "---", 3, "-", 1);
      qreplace_all(buf, "--", 2, "-", 1);
      qreplace_all(buf, TEMPO_S, TEMPO_S_LEN, "---", 3);
      qreplace_all(buf, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
      
      qreplace_all(buf, "!~", 2, TEMPO_S, TEMPO_S_LEN);
      qreplace_all(buf, "~", 1, " ", 1);
      qreplace_all(buf, TEMPO_S, TEMPO_S_LEN, "~", 1);
      
      replace_udo_quotes(buf);
      
      return TRUE;
   }
   return FALSE;
}


/*******************************************************************************
*
*  save_upr_entry_node():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void save_upr_entry_node(const int level, const char *filename, const char *title, FILE_LINENO line)
{
   char buf[LINELEN];
   
   if (bUseUPRfile && bUPRopened)
   {
      if (convert_title(buf, title))
         fprintf(fUPRfile, "node\t%d\t%s\t%lu\t%s\n", level, filename, line, buf);
   }
}





/*******************************************************************************
*
*  save_upr_entry_heading():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void save_upr_entry_heading(const int level, const char *filename, const char *title, FILE_LINENO line)
{
   char buf[LINELEN];
   
   if (bUseUPRfile && bUPRopened)
   {
      if (convert_title(buf, title))
         fprintf(fUPRfile, "heading\t%d\t%s\t%lu\t%s\n", level, filename, line, buf);
   }
}





/*******************************************************************************
*
*  save_upr_entry_alias():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void save_upr_entry_alias(const char *filename, const char *title, FILE_LINENO line)
{
   char buf[LINELEN];
   
   if (bUseUPRfile && bUPRopened)
   {
      if (convert_title(buf, title))
         fprintf(fUPRfile, "alias\t%s\t%lu\t%s\n", filename, line, buf);
   }
}





/*******************************************************************************
*
*  save_upr_entry_label():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void save_upr_entry_label(const char *filename, const char *title, FILE_LINENO line)
{
   char buf[LINELEN];
   
   if (bUseUPRfile && bUPRopened)
   {
      if (convert_title(buf, title))
         fprintf(fUPRfile, "label\t%s\t%lu\t%s\n", filename, line, buf);
   }
}





/*******************************************************************************
*
*  save_upr_entry_index():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void save_upr_entry_index(const int level, const char *filename, const char *title, FILE_LINENO line)
{
   char *buf;
   
   if (bUseUPRfile && bUPRopened)
   {
      buf = strdup(title);
      replace_char(buf, TILDE_C, '~');
      replace_char(buf, NBSP_C, '~');
      replace_char(buf, INDENT_C, ' ');
      replace_char(buf, DIVIS_C, '-');
      fprintf(fUPRfile, "index\t%d\t%s\t%lu\t%s\n", level, filename, line, buf);
      free(buf);
   }
}
