/**(TAB=0)**********************************************************************
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
*                 verwalten und fuer token_output() vorbereiten
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
*    fd  Jan 23: - converted all German umlauts in comments into plain ASCII
*                - file tidied up
*                - SHOW_VARIABLE -> SHOW_VAR
*    fd  Feb 19: LANG adjusted
*    fd  May 19: new: LANG.degree
*  2013:
*    fd  May 02: LANG string arrays enlarged to 64 chars each (tribute to UTF)
*    fd  Jun 03: lang.html_up removed (unused so far)
*    fd  Jun 04: lang.degree moved upwards in the _lang structure (recommended by ggs)
*  2017:
*    fd  Feb 08: lang.copyright added
*
******************************************|************************************/

#ifndef UDO_TYPE_H
#define UDO_TYPE_H





/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "udoport.h"





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define MYFILE_DRIV_LEN    16
#define MYFILE_PATH_LEN   256
#define MYFILE_NAME_LEN   256
#define MYFILE_SUFF_LEN    32
#define MYFILE_FULL_LEN   (MYFILE_DRIV_LEN + MYFILE_PATH_LEN + MYFILE_NAME_LEN + MYFILE_SUFF_LEN + 1)





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

struct rgb {
	unsigned char set;
	unsigned char r, g, b;
};

struct rgb_and_color {
	struct rgb rgb;
	int color;
};

typedef int FILE_ID;
typedef _ULONG FILE_LINENO;

typedef struct {
	FILE_ID id;
	FILE_LINENO line;
} FILE_LOCATION;

typedef struct _filelist FILELIST;
struct _filelist {
	FILELIST *next;
	FILE_ID id;
	char name[1];
};

typedef struct _udocolor
{
   int val;
   const char *name;
   struct rgb rgb;
   char drc[3];
   const char *wintext;
} UDOCOLOR;

typedef struct _passflags                 /* several flags for pass1() and pass2() */
{
   _BOOL   inside_apx;                  /* !begin_appendix aktiv? */
   int       ignore_line;                 /* Zeile nicht bearbeiten? */
   int       env;                         /* ENV_NONE, ENV_RAW etc. */
   _BOOL   env1st;
   _BOOL doinside;
   FILE_LOCATION loc;
}  PASSFLAGS;


typedef struct _lang                      /* language strings */
{
   char   preface[64];                    /* Vorwort */
   char   chapter[64];                    /* Kapitel */
   char   title[64];                      /* Titel */
   char   appendix[64];                   /* Anhang */
   char   contents[64];                   /* Inhaltsverzeichnis */
   char   listfigure[64];                 /* Abbildungsverzeichnis */
   char   listtable[64];                  /* Tabellenverzeichnis */
   char   figure[64];                     /* Abbildung */
   char   table[64];                      /* Tabelle */
   char   index[64];                      /* Index */
   char   page[64];                       /* Seite */
   char   see[64];                        /* siehe */
   char   also[64];                       /* siehe auch */
   char   by[64];                         /* von */
   char   fur[64];                        /* fuer  ("for" cannot be used -> C keyword) */
   char   up[64];                         /* Hoch (WinHelp) */
   char   exit[64];                       /* Beenden (WinHelp) */
   char   unknown[64];                    /* Unbekannt, Unknown etc. */
   char   update[64];                     /* Last updated on (HTML) */
   char   lcid[64];                       /* LCID fuer WinHelp4 & HtmlHelp */
   char   html_home[64];                  /* "Home" */
   char   html_up[64];                    /* "Hoch" */
   char   html_prev[64];                  /* "Zurueck" */
   char   html_next[64];                  /* "Weiter" */
   char   html_lang[64];                  /* Sprachenkuerzel */
   char   html_start[64];                 /* "Start" */
   char   translator[64];                 /* "Translator" */
   char   distributor[64];                /* "Distributor" */
   char   tex_stylename[64];
   char   lyx_langname[64];
   char   degree[64];                     /* "degree" */
   char   copyright[64];                  /* "Copyright" */

   /* --- these are filled in by UDO! --- */
   
   char   today[64];                      /* 28. Februar 1995 */
   char   short_today[64];                /* 28.02.1995 */
} LANG;


typedef struct _myfile                    /* file information */
{
   FILE  *file;                           /* Stream */
   char   full[MYFILE_FULL_LEN + 1];      /* Kompletter Zugriffspfad */
   char   driv[MYFILE_DRIV_LEN + 1];      /* Laufwerk */
   char   path[MYFILE_PATH_LEN + 1];      /* Pfad */
   char   name[MYFILE_NAME_LEN + 1];      /* Dateiname */
   char   suff[MYFILE_SUFF_LEN + 1];      /* Endung */
} MYFILE;

typedef struct _show_variable
{
   _BOOL source_filename;               /* Filename anzeigen */
} SHOW_VAR;


typedef struct _style                     /* style sheets */
{
   FILE_ID filename;                      /* filename only of stylesheet */
   char   *media;                         /* fuer welches Medium */
   char   *title;                         /* Titel eines Stylesheets */
   int    alternate;                      /* Alternate Stylesheet? */
} STYLE;

typedef struct _stylelist {
	int count;
	int alloc;
	STYLE **style;                        /* array of stylesheet names */
} STYLELIST;

typedef struct _script                    /* javascript files */
{
	FILE_ID filename;                     /* javascript file reference */
} SCRIPT;

typedef struct _scriptlist {
	int count;
	int alloc;
	SCRIPT **script;                      /* array of scripts */
} SCRIPTLIST;


#endif   /* UDO_TYPE_H */
