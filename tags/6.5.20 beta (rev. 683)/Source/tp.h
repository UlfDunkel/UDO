/* ############################################################
   # @(#) tp.h
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
   ############################################################ */

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
   char          *title;                  /* Titelzeile */
   char          *program;                /* Programmname */
   char          *date;                   /* Datum */
   char          *version;                /* Version */
   char          *author;                 /* Name des Autors */
   char          *address[MAXADDRESS+1];  /* Adresse */
   char          *webmastername;          /* Fuer HTML */
   char          *webmasteremail;         /* Fuer HTML */
   char          *webmastermailurl;       /* Fuer HTML */
   char          *webmasterurl;           /* Fuer HTML */
   char          *programimage;           /* program image */
   char          *authorimage;            /* author's funny face image */
   char          *authoricon;             /* -> Modern/Frames */
   char          *authoricon_active;      /* -> Modern/Frames */
   char          *appletitle;             /* for HTML Apple Help V6.5.17 */
   char          *appleicon;              /* for HTML Apple Help V6.5.17 */
   unsigned int   authoriconWidth;        /* */
   unsigned int   authoriconHeight;       /* */
   unsigned int   authoriconActiveWidth;  /* */
   unsigned int   authoriconActiveHeight; /* */
   char          *keywords;               /* New in r6pl15 [NHz] */
   char          *description;            /* New in r6pl15 [NHz] */
   char          *robots;                 /* New in V6.5.17 */
   char          *company;                /* New in V6.5.2 [NHz] */
   char          *category;               /* New in V6.5.2 [NHz] */
   char          *drc_statusline;
   char          *stg_database;
   char          *htmltitle;              /* <title>         */
   char          *distributor;            /* distributor name */

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
   char          *paper;                  /* paper format */
   unsigned int   width_mm10;             /* width  in 10th of a mm */
   unsigned int   height_mm10;            /* height in 10th of a mm */
   unsigned int   width_pt;               /* */
   unsigned int   height_pt;              /* */
   unsigned int   margintop_pt;           /* */
   unsigned int   marginleft_pt;          /* */
   unsigned int   marginright_pt;         /* */
   unsigned int   marginbottom_pt;        /* */
   unsigned int   width_twips;            /* */
   unsigned int   height_twips;           /* */
   BOOLEAN        landscape;              /* TRUE: landscape, FALSE: portrait */
} PAPERFORMAT;





/*******************************************************************************
*
*  Layout Data
*
******************************************|************************************/

typedef struct                            /* ---- Layoutinfos ---- */
{
   char          *paper;                  /* Papierformat */
   char          *pagemode;               /* HowToOpen */
   char          *viewerpreferences;      /* */
   char          *pagelayout;             /* */
   char          *fitwindow;              /* */
   char          *openpage;               /* */
   char          *hidetoolbar;            /* */
   char          *hidemenubar;            /* */
   char          *propfontname;           /* */
   unsigned int   propfontsize;           /* */
   char          *monofontname;           /* */
   unsigned int   monofontsize;           /* */
   unsigned int   node1size;              /* New in r6pl16 [NHz] */
   unsigned int   node2size;              /* New in r6pl16 [NHz] */
   unsigned int   node3size;              /* New in r6pl16 [NHz] */
   unsigned int   node4size;              /* New in r6pl16 [NHz] */
   unsigned int   node5size;
}  LAYOUTDATA;


#endif /* UDO_TP_H */





/*******************************************************************************
*
*     GLOBAL UNINITIALIZED VARIABLES
*
******************************************|************************************/

GLOBAL int          address_counter;      /* */
GLOBAL BOOLEAN      called_maketitle;     /* */
GLOBAL BOOLEAN      uses_maketitle;       /* */

GLOBAL TITLEDATA    titdat;               /* */
GLOBAL LAYOUTDATA   laydat;               /* New in r6pl15 [NHz] */

GLOBAL char         titleprogram[512];    /* */





/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/
   
GLOBAL BOOLEAN set_show_variable(void);   /* New V6.5.19 */
GLOBAL BOOLEAN set_mainlayout(void);      /* New in r6pl16 [NHz] */
GLOBAL BOOLEAN set_doclayout(void);       /* New in r6pl15 [NHz] */
GLOBAL BOOLEAN set_docinfo(void);
GLOBAL void    c_maketitle(void);
GLOBAL void    pch_titlepage(void);

GLOBAL void    init_module_tp(void);      /* */
GLOBAL void    init_module_tp_pass2(void);/* */
GLOBAL void    exit_module_tp(void);      /* */

/* +++ EOF (tp.h) +++ */