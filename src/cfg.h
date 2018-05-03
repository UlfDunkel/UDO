/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : cfg.h
*  Symbol prefix: cfg
*
*  Description  : ???
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
*  Co-Authors   : Gerhard Stoll (ggs), Ulf Dunkel
*  Write access : ggs, fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 22: header adjusted
*
******************************************|************************************/

/*   ############################################################
   # Typen
   ############################################################   */

#ifndef __UDOCFG__
#define __UDOCFG__

#include "version.h"

#define   CFG_READ_OK          0
#define   CFG_READ_NOT_FOUND   1
#define   CFG_READ_ERROR       2

#define   CFG_WRITE_OK         0
#define   CFG_WRITE_NOT_SAVED  1
#define   CFG_WRITE_ERROR      2


#define   CFG_MAX_FILE_LEN   128
#define   CFG_MAX_OPT_LEN     64
#define   CFG_MAX_USER_LEN    32

#define   CFG_MAX_SYMBOL       8
#define   CFG_MAX_SYMBOL_LEN  32

typedef struct _appcfg
{
   char      strApp[CFG_MAX_FILE_LEN+1];
   char      strOpt[CFG_MAX_OPT_LEN+1];
   _BOOL   bVa;
   _BOOL   bTos;
}  APPCFG;

typedef struct _config
{
   _BOOL   bRegistered;
   char   strUserName[CFG_MAX_USER_LEN+1];
   char   strUserStreet[CFG_MAX_USER_LEN+1];
   char   strUserTown[CFG_MAX_USER_LEN+1];
   char   strUserKey[CFG_MAX_USER_LEN+1];

   _BOOL   bDestAdjust;
   _BOOL   bDestAdjustAll;
   _BOOL   bDestAdjustName;
   _BOOL   bDestAdjustSuff;
   _BOOL   bDestLowerFile;
   _BOOL   bDestLowerPath;

   _BOOL   bUseLogfile;
   _BOOL   bUseHypfile;
   _BOOL   bUseTreefile;
   _BOOL   bUseUPRfile;
   _BOOL   bShowStatus;
   _BOOL bForceLong;
   _BOOL bForceShort;

#if USE_KWSET
    _BOOL bNoFastAutoref;
#endif
    
#ifdef __TOS__
   APPCFG   dedit, dview;
   APPCFG   sedit, sview;

   APPCFG   asc;
   APPCFG   aqv;
   APPCFG   htm;
   APPCFG   inf;
   APPCFG   lds;
   APPCFG   man;
   APPCFG   pch;
   APPCFG   rtf;
   APPCFG   stg;
   APPCFG   tex;
   APPCFG   tvh;
   APPCFG   win;
   APPCFG   hph;
   APPCFG   nro;
   APPCFG   src;
   APPCFG   srp;
   APPCFG   lyx;
   APPCFG   ipf;
   APPCFG   drc;
   APPCFG   mhh;
   APPCFG   pdl;
   APPCFG   wh4;
   APPCFG   u2u;
   APPCFG   ps;

   int      desttype;
   char     strSourcefile[CFG_MAX_FILE_LEN+1];
   char     strDestfile[CFG_MAX_FILE_LEN+1];

   _BOOL  bDestView;
   _BOOL  bNoWarnings;
   _BOOL  bCheckMisc;
   _BOOL  bAskQuit;
   _BOOL  bWarnOver;

   char   strSymbol[CFG_MAX_SYMBOL][CFG_MAX_SYMBOL_LEN];
   _BOOL  bUseSymbol[CFG_MAX_SYMBOL];
   
#endif /* __TOS__ */

}   CONFIG;

/*   ############################################################
   # Variablen
   ############################################################   */
GLOBAL CONFIG config;


/*   ############################################################
   # Funktionen
   ############################################################   */
GLOBAL _BOOL key_check (const char *nam, const char *str, const char *tow, const char *key );
GLOBAL void key_calc (const char *nam, const char *str, const char *tow, const char *app, const char *os, char *key );


GLOBAL int read_profile(void);
GLOBAL int write_profile(void);

GLOBAL void init_module_config ( const char *pfname, const char *prgname, const char *prgos );

#endif   /* __UDOCFG__ */
