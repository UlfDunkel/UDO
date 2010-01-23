/*******************************************************************************
*
*  Project name : UDO
*  Module name  : udo_type.h
*  Symbol prefix: udo_type
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
*  Description  : This module contains routines which handle the environment
*                 Routinen, die die Ausgabe der zahlreichen Umgebungen
*	               verwalten und fuer token_output() vorbereiten
*
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
*  2009:
*    fd  Jun 04: !docinfo [translator] introduced
*  2010:
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*
******************************************|************************************/


#ifndef UDO_TYPE_H
#define	UDO_TYPE_H

#include	"portab.h"

/*	--------------------------------------------------
	diverse Flags fuer pass1() und pass2()
	--------------------------------------------------	*/
typedef struct _passflags
{
	BOOLEAN	inside_apx;			/* !begin_appendix aktiv?	*/

	int		ignore_line;		/* Zeile nicht bearbeiten?	*/

	int		env;				/* ENV_NONE, ENV_RAW etc.	*/	/*r6pl2*/
	BOOLEAN	env1st;

}	PASSFLAGS;


/*	--------------------------------------------------
	Sprachstrings
	--------------------------------------------------	*/
typedef struct _lang
{
	char	preface[32];			/* Vorwort					*/
	char	chapter[32];			/* Kapitel					*/
	char	appendix[32];			/* Anhang					*/
	char	contents[32];			/* Inhaltsverzeichnis		*/
	char	title[32];				/* Titel					*/
	char	figure[32];				/* Abbildung				*/
	char	table[32];				/* Tabelle					*/
	char	index[32];				/* Index					*/
	char	listfigure[32];			/* Abbildungsverzeichnis	*/
	char	listtable[32];			/* Tabellenverzeichnis		*/
	char	page[32];				/* Seite					*/
	char	see[32];				/* siehe					*/
	char	also[32];				/* siehe auch				*/
	char	by[16];					/* von						*/
	/* New in V6.5.2 [NHz] */
	char	fur[16];					/* fuer						*/
	char	up[8];					/* Hoch (WinHelp)			*/
	char	exit[10];				/* Beenden (WinHelp)		*/
	char	today[32];				/* 28. Februar 1995			*/
	char	short_today[32];		/* 28.02.1995				*/
	char	update[64];				/* Last updated on (HTML)	*/
	char	unknown[32];			/* Unbekannt, Unknown etc.	*/
	char	html_home[32];			/* "Home"					*/
	char	html_up[32];			/* "Hoch"					*/
	char	html_prev[32];			/* "Zurueck"				*/
	char	html_next[32];			/* "Weiter"					*/
	char	lcid[64];				/* LCID fuer WinHelp4		*/
	/* New in r6pl16 [NHz] */
	char	html_lang[15];                   /* Sprachenkuerzel */
	char	html_start[32];                  /* "Start" */
   
   char  translator[32];                  /* "Translator" */
   char  distributor[32];                 /* "Distributor" */
}	LANG;


/*	--------------------------------------------------	*/


#define	MYFILE_FULL_LEN	512
#define	MYFILE_DRIV_LEN	16
#define	MYFILE_PATH_LEN	256
#define	MYFILE_NAME_LEN	256
#define	MYFILE_SUFF_LEN	32

typedef struct _myfile
{
	FILE	*file;						/* Stream					*/
	char	full[MYFILE_FULL_LEN+1];	/* Kompletter Zugriffspfad	*/
	char	driv[MYFILE_DRIV_LEN+1];	/* Laufwerk					*/
	char	path[MYFILE_PATH_LEN+1];	/* Pfad						*/
	char	name[MYFILE_NAME_LEN+1];	/* Dateiname				*/
	char	suff[MYFILE_SUFF_LEN+1];	/* Endung					*/
	int		opened;						/* Datei geoeffnet?			*/
}	MYFILE;


/*	--------------------------------------------------	*/
/* New in V6.5.19 */

typedef struct _show_variable
{
	BOOLEAN source_filename;			/* Filename anzeigen		*/
}	SHOW_VARAIABLE;


/*	############################################################
	# udo_type.h
	############################################################	*/

#endif	/* UDO_TYPE_H */
