/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : tp.h
*  Symbol prefix: tp
*
*  Description  : This module contains routines which handle the environment
*                 Routinen, die die Ausgabe der zahlreichen Umgebungen
*                 verwalten und fuer token_output() vorbereiten
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
*  2009:
*    fd  Jun 04: !docinfo [translator] introduced
*  2010:
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Mar 02: - webmastername    -> domain_name
*                - webmasterurl     -> domain_link
*                - webmasteremail   -> contact_name
*                - webmastermailurl -> contact_link
*  2014
*    ggs Apr 20: Add Node6
*
******************************************|************************************/

/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/


#define MAXADDRESS   20
#define MAXPAPERSIZE  6                   /* New in r6pl15 [NHz] */





#ifndef UDO_TP_H
#define UDO_TP_H

/*******************************************************************************
*
*  Title Data
*
******************************************|************************************/

typedef struct _titledata                 /* ---- Titelseiteninfos ---- */
{
   char   *title;                         /* Titelzeile */
   char   *program;                       /* Programmname */
   char   *date;                          /* Datum */
   char   *version;                       /* Version */
   char   *author;                        /* Name des Autors */
   char   *address[MAXADDRESS + 1];       /* Adresse */
   char   *domain_name;                   /* for HTML */
   char   *domain_link;                   /* for HTML */
   char   *contact_name;                  /* for HTML */
   char   *contact_link;                  /* for HTML */
   char   *programimage;                  /* program image */
   char   *authorimage;                   /* author's funny face image */
   char   *authoricon;                    /* -> Modern/Frames */
   char   *authoricon_active;             /* -> Modern/Frames */
   char   *appletitle;                    /* for HTML Apple Help V6.5.17 */
   char   *appleicon;                     /* for HTML Apple Help V6.5.17 */
   _UWORD   authoriconWidth;               /* */
   _UWORD   authoriconHeight;              /* */
   _UWORD   authoriconActiveWidth;         /* */
   _UWORD   authoriconActiveHeight;        /* */
   char   *keywords;                      /* New in r6pl15 [NHz] */
   char   *description;                   /* New in r6pl15 [NHz] */
   char   *robots;                        /* New in V6.5.17 */
   char   *company;                       /* New in V6.5.2 [NHz] */
   char   *category;                      /* New in V6.5.2 [NHz] */
   char   *drc_statusline;
   char   *stg_database;
   char   *htmltitle;                     /* <title>         */
   char   *translator;                    /* translator name */
   char   *distributor;                   /* distributor name */
   char   *degree;                        /* unused??? */
   char   *copyright;                     /* copyright */
}   TITLEDATA;





/*******************************************************************************
*
*  Paper Format
*
*  Note: New in r6pl15 [NHz]
*
******************************************|************************************/

typedef struct                            /* Paper Format */
{
   char     *paper;                       /* paper format */
   _UWORD     width_mm10;                  /* width  in 10th of a mm */
   _UWORD     height_mm10;                 /* height in 10th of a mm */
   _UWORD     width_pt;                    /* */
   _UWORD     height_pt;                   /* */
   _UWORD     margintop_pt;                /* */
   _UWORD     marginleft_pt;               /* */
   _UWORD     marginright_pt;              /* */
   _UWORD     marginbottom_pt;             /* */
   _UWORD     width_twips;                 /* */
   _UWORD     height_twips;                /* */
   _BOOL   landscape;                   /* TRUE: landscape, FALSE: portrait */
} PAPERFORMAT;





/*******************************************************************************
*
*  Layout Data
*
******************************************|************************************/

typedef struct                            /* ---- Layoutinfos ---- */
{
   char   *paper;                         /* Papierformat */
   char   *pagemode;                      /* HowToOpen */
   char   *viewerpreferences;             /* */
   char   *pagelayout;                    /* */
   char   *fitwindow;                     /* */
   char   *openpage;                      /* */
   char   *hidetoolbar;                   /* */
   char   *hidemenubar;                   /* */
   char   *propfontname;                  /* */
   _UWORD   propfontsize;                  /* */
   char   *monofontname;                  /* */
   _UWORD   monofontsize;                  /* */
   _UWORD   node1size;                     /* New in r6pl16 [NHz] */
   _UWORD   node2size;                     /* New in r6pl16 [NHz] */
   _UWORD   node3size;                     /* New in r6pl16 [NHz] */
   _UWORD   node4size;                     /* New in r6pl16 [NHz] */
   _UWORD   node5size;
   _UWORD   node6size;
}  LAYOUTDATA;


#endif /* UDO_TP_H */





/*******************************************************************************
*
*     GLOBAL UNINITIALIZED VARIABLES
*
******************************************|************************************/

GLOBAL int          address_counter;      /* */
GLOBAL _BOOL      called_maketitle;     /* */
GLOBAL _BOOL      uses_maketitle;       /* */

GLOBAL TITLEDATA    titdat;               /* */
GLOBAL LAYOUTDATA   laydat;               /* New in r6pl15 [NHz] */

GLOBAL char         titleprogram[512];    /* */





/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/
   
GLOBAL _BOOL set_show_variable(void);   /* New V6.5.19 */
GLOBAL _BOOL set_mainlayout(void);      /* New in r6pl16 [NHz] */
GLOBAL _BOOL set_doclayout(void);       /* New in r6pl15 [NHz] */
GLOBAL _BOOL set_docinfo(void);
GLOBAL void    c_maketitle(void);
GLOBAL void    pch_titlepage(void);

GLOBAL void    init_module_tp(void);      /* */
GLOBAL void    init_module_tp_pass2(void);/* */
GLOBAL void    exit_module_tp(void);      /* */

/* +++ EOF (tp.h) +++ */