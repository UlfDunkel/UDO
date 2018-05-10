/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : abo.c
*  Symbol prefix: abo
*
*  Description  : Output information about UDO (at !end_document)
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
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - output_about_udo(): check if TOKPS does still not support this
*
*-------------------------------------------------------------------------------
*  History:
*
*  1995:
*    DH  mmm dd: introduced
*  2001:
*    DH  Oct 02: last DH version
*  2010:
*    fd  Jan 30: file reformatted and tidied up
*    fd  Feb 16: udofile is global now (udo.h)
*    fd  Feb 23: UDO_PL -> UDO_BUILD (no more patchlevels)
*    fd  Mar 01: !code -> !code_source
*    fd  May 19: output_about_udo_ger() + output_about_udo_eng() updated
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
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "cfg.h"
#include "file.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"
#include "udointl.h"
#include "lang.h"

#include "export.h"
#include "abo.h"
#include "str.h"





/*******************************************************************************
*
*     UNINITIALIZED LOCAL VARIABLES
*
******************************************|************************************/

LOCAL char      strUdoNodeName[32];
LOCAL char      strUdoHtmlName[32];





/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  udofile_tmpname():
*     compose temp file specs
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL FILE *udofile_tmpname(const char *templatename)
{
#if defined(HAVE_MKSTEMP) && defined(HAVE_FDOPEN)
	{
	    char t[512];
	    int fd;
	    
	    sprintf(t, "%s%s%s%s", outfile.driv, outfile.path, "udoXXXXXX", "");
	    path_adjust_separator(t);
	    if ((fd = mkstemp(t)) >= 0 )
	    {   
	        strcpy(udofile.full, t);
	        return fdopen(fd, "w");
	    }
    }
#elif defined(HAVE_TMPNAM)
   {
      char   t[512];  /* temp dir fspec */
      FILE *uif;
   
      if (tmpnam(t) != NULL)
         strcpy(udofile.full, t);
      else
         strcat(strcpy(udofile.full, templatename), ".tmp");
      uif = myFwopen(udofile.full, TOASC);
      if (uif != NULL)
         return uif;
   }
#endif
   {
   char  *tp;      /* temp dir path */

   tp = NULL;

   if ( (tp = getenv("TEMP")) == NULL)    /* try to find any temp dir */
   {
      if ( (tp = getenv("TMP")) == NULL)
         tp = getenv("TMPDIR");
   }

   if (tp != NULL)                        /* got one! */
   {
      fsplit(tp, tmp_driv, tmp_path, tmp_name, tmp_suff);
      
      strcpy(udofile.driv, tmp_driv);
      strcpy(udofile.path, tmp_path);
   }
   else                                   /* use my own paths */
   {
      strcpy(udofile.driv, outfile.driv);
      strcpy(udofile.path, outfile.path);
   }

   strcpy(udofile.name, templatename);
   strcpy(udofile.suff, ".tmp");
   sprintf(udofile.full, "%s%s%s%s", udofile.driv, udofile.path, udofile.name, udofile.suff);
   }
   path_adjust_separator(udofile.full);
   return myFwopen(udofile.full, TOASC);
}





/*******************************************************************************
*
*  output_about_udo_ger():
*     German text for "About UDO"
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_about_udo_ger(FILE *f)
{
   fprintf(f, "%s\n", CMD_BEGIN_CENTER);
   fprintf(f, "!universal_charset [on]\n");
   fprintf(f, "Dieser Text wurde erzeugt mit\n");
   fprintf(f, "\n");
   fprintf(f, "(!B)UDO(!b) (!nl)\n");
   fprintf(f, "%s (!nl)\n", UDO_VERSION_STRING);
   fprintf(f, "%s\n", UDO_OS);
   fprintf(f, "\n");
   fprintf(f, UDO_COPYRIGHT_TEXT);
   fprintf(f, "UDO ist Open Source (!nl)\n");
   fprintf(f, "\n");
   fprintf(f, "!udolink\n");
   fprintf(f, "\n");
   fprintf(f, "UDO ist ein Programm, mit dem Sie Textdateien, die im\n");
   fprintf(f, "Universal-Document-Format erstellt wurden, in (!\"u)ber\n");
   fprintf(f, "25 Zielformate umwandeln k(!\"o)nnen.\n");
   fprintf(f, "\n");
   fprintf(f, "Weitere Informationen sowie die aktuellen Versionen finden Sie im Internet unter (!nl)\n");
   fprintf(f, "(!url [%s][])\n", UDO_URL);
   fprintf(f, "%s\n\n", CMD_END_CENTER);
}





/*******************************************************************************
*
*  output_about_udo_eng():
*     English text for "About UDO"
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_about_udo_eng(FILE *f)
{
   fprintf(f, "%s\n", CMD_BEGIN_CENTER);
   fprintf(f, _("This text was made with\n"));
   fprintf(f, "\n");
   fprintf(f, "(!B)UDO(!b) (!nl)\n");
   fprintf(f, "%s (!nl)\n", UDO_VERSION_STRING);
   fprintf(f, "%s\n", UDO_OS);
   fprintf(f, "\n");
   fprintf(f, UDO_COPYRIGHT_TEXT);
   fprintf(f, _("UDO is Open Source (!nl)\n"));
   fprintf(f, "\n");
   fprintf(f, "!udolink\n");
   fprintf(f, "\n");
   fprintf(f, _("UDO is an application that converts text files which you\n"));
   fprintf(f, _("have written in Universal Document Format, into more than\n"));
   fprintf(f, _("25 different target formats.\n"));
   fprintf(f, "\n");
   fprintf(f, _("Get further information and the current versions on the Internet at (!nl)\n"));
   fprintf(f, "\n");
   fprintf(f, "(!url [%s] [])\n", UDO_URL);
   fprintf(f, "%s\n\n", CMD_END_CENTER);
}










/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  output_about_udo():
*     output "About UDO" information
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void output_about_udo(void)
{
   FILE *uif;
   
   switch (desttype)
   {
   case TOSRC:
   case TOSRP:
      /* nur eine kurze Info in c_end_document ausgeben */
      return;
#if 0 /* now uses default from abo.c */
   case TOKPS:
      return;
#endif
   }

   uif = udofile_tmpname("_udoinfo");

   if (!uif)
      return;
   

   fprintf(uif, "!newpage\n");
   fprintf(uif, "!code_source [sys]\n");
   fprintf(uif, "!sloppy\n\n");
   fprintf(uif, "!node* %s\n", strUdoNodeName);
   fprintf(uif, "!html_name %s\n", strUdoHtmlName);
   fprintf(uif, "!win_helpid %s\n\n", WIN_UDO_NODE_NAME);
   
   if (!bDocAutorefOff)                   /* don't auto-reference the 'About UDO' page */
      fprintf(uif, "!autoref [off]\n");
   
   
   switch (destlang)
   {
   case TOGER:
      output_about_udo_ger(uif);
      break;
      
   default:
      output_about_udo_eng(uif);
      break;
   }

   fclose(uif);

   token_reset();
   strcpy(token[0], "!include");          /* sollte safe sein, da ein Token auf jeden Fall so lang werden kann :-) [vj] */
   
   um_strcpy(token[1], udofile.full, MAX_TOKEN_LEN + 1, "output_about_udo");
   
   token_counter = 2;
   
   c_include();

   remove(udofile.full);
}





/*******************************************************************************
*
*  add_pass1_about_udo():
*     output "About UDO" in pass 1 (???)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void add_pass1_about_udo(void)
{
   output_about_udo();
   token_reset();
}





/*******************************************************************************
*
*  init_module_about():
*     init module
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_about(void)
{
   use_about_udo = FALSE;

   sprintf(strUdoNodeName, "UDO%s", UDO_REL);
   strcpy(strUdoHtmlName, "aboutudo");
}
