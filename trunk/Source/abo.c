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
*  Things to do : - re-write UDO string and encoding engine for full Unicode support
*                 - output_about_udo(): check if TOKPS does still not support this
*                 - remove about_unregistered()
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
*
******************************************|************************************/

/*******************************************************************************
*
*     CONSTANTS
*
******************************************|************************************/

#ifndef ID_ABOUT_C
#define ID_ABOUT_C
const char *id_abo_c= "@(#) abo.c       $DATE$";
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
#include "cfg.h"
#include "file.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"
#include "export.h"
#include "abo.h"
#include "str.h"





/*******************************************************************************
*
*     UNINITIALIZED LOCAL VARIABLES
*
******************************************|************************************/

LOCAL char     strUdoNodeName[32];        /* */
LOCAL char     strUdoHtmlName[32];        /* */

LOCAL MYFILE   udofile;                   /* */





/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

   /* compose temp file specs */
LOCAL void udofile_adjust(void);

   /* German text for "About UDO" */
LOCAL void output_about_udo_ger(FILE *f);
   /* English text for "About UDO" */
LOCAL void output_about_udo_eng(FILE *f);










/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  udofile_adjust():
*     compose temp file specs
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void udofile_adjust(void)
{
#if HAVE_TMPNAM
   char   t[512];  /* temp dir fspec */
   
   
   if (tmpnam(t) != NULL)
      strcpy(udofile.full, t);
   else
      strcpy(udofile.full, "_udoinfo.tmp");
#else
   char  *tp;      /* ^ temp dir path */


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

   strcpy(udofile.name, "_udoinfo");
   strcpy(udofile.suff, ".tmp");

   sprintf(udofile.full, "%s%s%s%s", udofile.driv, udofile.path, udofile.name, udofile.suff);
#endif
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

LOCAL void output_about_udo_ger(

FILE  *f)  /* ^ aboutudo file */
{
   fprintf(f, "%s\n", CMD_BEGIN_CENTER);
   fprintf(f, "Dieser Text wurde erzeugt mit\n");
   fprintf(f, "\n");
   fprintf(f, "(!B)UDO(!b)\t(!nl)\n");
   fprintf(f, "Version %s.%s.%s\t(!nl)\n", UDO_REL, UDO_SUBVER, UDO_PL);
   fprintf(f, "%s\n", UDO_OS);
   fprintf(f, "\n");
   fprintf(f, UDO_COPYRIGHT_TEXT);
   fprintf(f, "UDO ist Open Source\t(!nl)\n");
   fprintf(f, "\n");
   fprintf(f, "!udolink\n");
   fprintf(f, "\n");
   fprintf(f, "UDO ist ein Programm, welches Textdateien, die im\n");
   fprintf(f, "Universal Document Format erstellt wurden, in das ASCII-,\n");
   fprintf(f, "ST-Guide-, LaTeX-, Rich Text-, Pure-C-Help-, Manualpage-,\n");
   fprintf(f, "HTML-, WinHelp-, Texinfo-, Linuxdoc-SGML-, LyX-, Apple-QuickView-, \n");
   fprintf(f, "HTML Apple Help- und Turbo-Vision-Help-Format umwandeln kann.\n");
   fprintf(f, "\n");
   fprintf(f, "Weitere Informationen sowie die aktuellen Versionen findet man im World Wide Web unter\t(!nl)\n");
   fprintf(f, "(!url [%s][])\n", UDO_URL);
   fprintf(f, "%s\n\n", CMD_END_CENTER);
}





/*******************************************************************************
*
*  output_about_udo_ger():
*     English text for "About UDO"
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_about_udo_eng(

FILE  *f)  /* ^ aboutudo file */
{
   fprintf(f, "%s\n", CMD_BEGIN_CENTER);
   fprintf(f, "This text was made with\n");
   fprintf(f, "\n");
   fprintf(f, "(!B)UDO(!b)\t(!nl)\n");
   fprintf(f, "Version %s.%s.%s\t(!nl)\n", UDO_REL, UDO_SUBVER, UDO_PL);
   fprintf(f, "%s\n", UDO_OS);
   fprintf(f, "\n");
   fprintf(f, UDO_COPYRIGHT_TEXT);
   fprintf(f, "UDO is Open Source\t(!nl)\n");
   fprintf(f, "\n");
   fprintf(f, "!udolink\n");
   fprintf(f, "\n");
   fprintf(f, "UDO is a program that converts files that are written\n");
   fprintf(f, "in the Universal Document Format into ASCII, ST-Guide, LaTeX,\n");
   fprintf(f, "Rich Text Format, Pure C Help, Manualpage, HTML, WinHelp\n,");
   fprintf(f, "Texinfo, Linuxdoc-SGML, LyX, Apple QuickView HTML Apple Help and Turbo-Vision-Help.\n");
   fprintf(f, "Further information and the current versions can be found at\t(!nl)\n");
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
   FILE  *uif;  /* */
   
                                          /* supplied TOKPS in r6pl15 [NHz] */
   switch (desttype)
   {
   case TOSRC:
   case TOSRP:
   case TOKPS:
      /* nur eine kurze Info in c_end_document ausgeben */
      return;
   }

   udofile_adjust();

   uif = myFwopen(udofile.full, TOASC);
   
   if (!uif)
      return;
   

   fprintf(uif, "!newpage\n");
   fprintf(uif, "!code [sys]\n");
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
*  about_unregistered():
*     output "About UDO" in unregistered UDO versions
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void about_unregistered(void)
{
   /* UDO is now Open Source */
   /* this method is not needed anymore */
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


/* +++ EOF +++ */
