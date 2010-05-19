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
*                - SHOW_VARAIABLE -> SHOW_VAR
*    fd  Feb 19: LANG adjusted
*    fd  May 19: new: LANG.degree
*
******************************************|************************************/

#ifndef UDO_TYPE_H
#define UDO_TYPE_H





/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "portab.h"                       /* */





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define MYFILE_FULL_LEN   512             /* */
#define MYFILE_DRIV_LEN    16             /* */
#define MYFILE_PATH_LEN   256             /* */
#define MYFILE_NAME_LEN   256             /* */
#define MYFILE_SUFF_LEN    32             /* */





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _passflags                 /* several flags for pass1() and pass2() */
{
   BOOLEAN   inside_apx;                  /* !begin_appendix aktiv? */
   int       ignore_line;                 /* Zeile nicht bearbeiten? */
   int       env;                         /* ENV_NONE, ENV_RAW etc. */   /*r6pl2*/
   BOOLEAN   env1st;
}  PASSFLAGS;


typedef struct _lang                      /* language strings */
{
   char   preface[32];                    /* Vorwort */
   char   chapter[32];                    /* Kapitel */
   char   title[32];                      /* Titel */
   char   appendix[32];                   /* Anhang */
   char   contents[32];                   /* Inhaltsverzeichnis */
   char   listfigure[32];                 /* Abbildungsverzeichnis */
   char   listtable[32];                  /* Tabellenverzeichnis */
   char   figure[32];                     /* Abbildung */
   char   table[32];                      /* Tabelle */
   char   index[32];                      /* Index */
   char   page[32];                       /* Seite */
   char   see[32];                        /* siehe */
   char   also[32];                       /* siehe auch */
   char   by[32];                         /* von */
   char   fur[32];                        /* fuer  ("for" cannot be used -> C keyword) */
   char   up[32];                         /* Hoch (WinHelp) */
   char   exit[32];                       /* Beenden (WinHelp) */
   char   unknown[32];                    /* Unbekannt, Unknown etc. */
   char   update[64];                     /* Last updated on (HTML) */
   char   lcid[64];                       /* LCID fuer WinHelp4 */
   char   html_home[32];                  /* "Home" */
   char   html_up[32];                    /* "Hoch" */
   char   html_prev[32];                  /* "Zurueck" */
   char   html_next[32];                  /* "Weiter" */
   char   html_lang[16];                  /* Sprachenkuerzel */
   char   html_start[32];                 /* "Start" */
   char   translator[32];                 /* "Translator" */
   char   distributor[32];                /* "Distributor" */
   
   /* --- these are filled in by UDO! --- */
   
   char   today[32];                      /* 28. Februar 1995 */
   char   short_today[32];                /* 28.02.1995 */

   /* --- the following are not used in TITLEDATA so far! --- */
   char   degree[32];                     /* "degree" */
   
}  LANG;


typedef struct _myfile                    /* file information */
{
   FILE  *file;                           /* Stream */
   char   full[MYFILE_FULL_LEN + 1];      /* Kompletter Zugriffspfad */
   char   driv[MYFILE_DRIV_LEN + 1];      /* Laufwerk */
   char   path[MYFILE_PATH_LEN + 1];      /* Pfad */
   char   name[MYFILE_NAME_LEN + 1];      /* Dateiname */
   char   suff[MYFILE_SUFF_LEN + 1];      /* Endung */
   int    opened;                         /* Datei geoeffnet? */
}  MYFILE;

                                          /* New in V6.5.19 */
typedef struct _show_variable             /* */
{
   BOOLEAN source_filename;               /* Filename anzeigen */
}  SHOW_VAR;


#endif   /* UDO_TYPE_H */

/* +++ EOF +++ */

