/*	############################################################
	# @(#) abo.c
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
	# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	# GNU General Public License for more details.
	# 
	# You should have received a copy of the GNU General Public License
	# along with this program; if not, write to the Free Software
	# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
	# 
	#
	# Informationen ueber UDO ausgeben (bei !end_document)
	#
	############################################################	*/

#ifndef ID_ABOUT_C
#define ID_ABOUT_C
const char *id_abo_c= "@(#) abo.c       02.10.2001";
#endif

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


/*	############################################################
	# lokale Variablen
	############################################################	*/
LOCAL char		strUdoNodeName[32];
LOCAL char		strUdoHtmlName[32];

LOCAL MYFILE	udofile;


/*	############################################################
	# lokale Prototypen
	############################################################	*/
LOCAL void udofile_adjust ( void );

LOCAL void output_about_udo_ger ( FILE *f );
LOCAL void output_about_udo_eng ( FILE *f );


/*	############################################################
	# extern Variablen und Prototypen
	############################################################	*/


/*	############################################################
	# Dateinamen zusammenbasteln
	############################################################	*/
LOCAL void udofile_adjust ( void )
{

#if HAVE_TMPNAM

	char t[512];
	
	if ( tmpnam(t)!=NULL )
	{	
		strcpy(udofile.full, t);
	}
	else
	{	strcpy(udofile.full, "_udoinfo.tmp");
	}

#else

	char	*tp;

	tp= NULL;

	if ( (tp=getenv("TEMP"))==NULL )
	{	if ( (tp=getenv("TMP"))==NULL )
		{	tp=getenv("TMPDIR");
		}
	}

	if ( tp!=NULL )
	{	fsplit(tp, tmp_driv, tmp_path, tmp_name, tmp_suff);
		strcpy(udofile.driv, tmp_driv);
		strcpy(udofile.path, tmp_path);
	}
	else
	{	strcpy(udofile.driv, outfile.driv);
		strcpy(udofile.path, outfile.path);
	}

	strcpy(udofile.name, "_udoinfo");
	strcpy(udofile.suff, ".tmp");

	sprintf(udofile.full, "%s%s%s%s", udofile.driv, udofile.path, udofile.name, udofile.suff);
#endif

}	/* udofile_adjust */



/*	############################################################
	# Deutscher Text fuer !german
	############################################################	*/
LOCAL void output_about_udo_ger ( FILE *f )
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
	fprintf(f, "HTML-, WinHelp-, Texinfo-, Linuxdoc-SGML-, LyX-, Apple-QuickView-\n");
	fprintf(f, "und Turbo-Vision-Help-Format umwandeln kann.\n");
	fprintf(f, "\n");
	fprintf(f, "Weitere Informationen sowie die aktuellen Versionen findet man im World Wide Web unter\t(!nl)\n");
	fprintf(f, "(!url [%s][])\n", UDO_URL);
	fprintf(f, "%s\n\n", CMD_END_CENTER);

}	/* output_about_udo_ger */


/*	############################################################
	# Englischer Text fuer !english, !french
	############################################################	*/
LOCAL void output_about_udo_eng ( FILE *f )
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
	fprintf(f, "Texinfo, Linuxdoc-SGML, LyX, Apple QuickView and Turbo-Vision-Help.\n");
	fprintf(f, "Further information and the current versions can be found at\t(!nl)\n");
	fprintf(f, "\n");
	fprintf(f, "(!url [%s] [])\n", UDO_URL);
	fprintf(f, "%s\n\n", CMD_END_CENTER);

}	/* output_about_udo_eng */



GLOBAL void output_about_udo ( void )
{
	FILE *uif;
	
	/* supplied TOKPS in r6pl15 [NHz] */
	if (desttype==TOSRC || desttype==TOSRP || desttype==TOKPS)
	{	/* nur eine kurze Info in c_end_document ausgeben */
		return;
	}

	udofile_adjust();

	uif= myFwopen(udofile.full, TOASC);
	
	if (!uif)
	{	return;
	}

	fprintf(uif, "!newpage\n");
	fprintf(uif, "!code [sys]\n");
	fprintf(uif, "!sloppy\n\n");
	fprintf(uif, "!node* %s\n", strUdoNodeName);
	fprintf(uif, "!html_name %s\n", strUdoHtmlName);
	fprintf(uif, "!win_helpid %s\n\n", WIN_UDO_NODE_NAME);	/* r6pl2 */
	if (!bDocAutorefOff)
	{	fprintf(uif, "!autoref [off]\n");
	}
	
	switch (destlang)
	{	case TOGER:	output_about_udo_ger(uif);	break;
		default:	output_about_udo_eng(uif);	break;
	}

	fclose(uif);

	token_reset();
	strcpy(token[0], "!include"); /* sollte safe sein, da ein Token auf jeden Fall so lang werden kann :-) [vj] */
	um_strcpy(token[1], udofile.full, MAX_TOKEN_LEN+1, "output_about_udo");
	token_counter= 2;
	
	c_include();	

	remove(udofile.full);
}	/* output_about_udo */



GLOBAL void add_pass1_about_udo ( void )
{
	output_about_udo();
	token_reset();

}	/* add_pass1_about_udo */



/*	############################################################
	# Registrierungshinweise
	############################################################	*/
GLOBAL void about_unregistered ( void )
{
	/* UDO is now Open Source */
	/* this method is not needed anymore */
}	/* about_unregistered */


/*	############################################################
	# Modulinit
	############################################################	*/
GLOBAL void init_module_about ( void )
{
	use_about_udo= FALSE;

	sprintf(strUdoNodeName, "UDO%s", UDO_REL);
	strcpy(strUdoHtmlName, "aboutudo");
}


/*	############################################################
	# about.c
	############################################################	*/

