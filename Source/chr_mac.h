/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_mac.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer Apple Macintosh
*                 gemaess Scan von Martin Osieka @ OF2
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
*  Things to do : re-write UDO string and encoding engine for full Unicode support 
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 10: header updated, file reformatted and tidied up (TAB-free)
*    fd  Feb 12: - all octal chars converted into decimal values
*                - u_CODE_MAC[] introduced (Mac OS Roman)
*    fd  Feb 17: - iso2sys_item[] removed (deprecated)
*                - chrtab[] merged in CHR.H
*
******************************************|************************************/

#ifndef ID_CHARSET_H
#define ID_CHARSET_H
const char  *id_charset_h = "@(#) chr_mac.h   $date$";
#endif

#ifndef THIS_CHARSET
#define THIS_CHARSET   "MacOS"
#endif





/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#include "portab.h"





/*******************************************************************************
*
*     Recode 'Universal codepage' into ASCII codepage
*
******************************************|************************************/

typedef struct _uni2systab
{
   char  *uni;                            /* */
   char  *system;                         /* */
}  UNI2SYSTAB;


#define UNI2SYSTABSIZE   64


LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   { "(!\"a)", "\212" },
   { "(!\"e)", "\221" },
   { "(!\"i)", "\225" },
   { "(!\"o)", "\232" },
   { "(!\"u)", "\237" },
   { "(!\"y)", "\330" },
   { "(!\"s)", "\247" },
   { "(!\"A)", "\200" },
   { "(!\"E)", "\350" },
   { "(!\"I)", "\354" },
   { "(!\"O)", "\205" },
   { "(!\"U)", "\206" },
   { "(!\"Y)", "Y"    },                  /* 13 */

   { "(!'a)",  "\207" },
   { "(!'e)",  "\216" },
   { "(!'i)",  "\222" },
   { "(!'o)",  "\227" },
   { "(!'u)",  "\234" },
   { "(!'y)",  ""     },
   { "(!'A)",  "\347" },
   { "(!'E)",  "\203" },
   { "(!'I)",  "\352" },
   { "(!'O)",  "\356" },
   { "(!'U)",  "\362" },
   { "(!'Y)",  ""     },                  /* 12 */

   { "(!`a)",  "\210" },
   { "(!`e)",  "\217" },
   { "(!`i)",  "\223" },
   { "(!`o)",  "\230" },
   { "(!`u)",  "\235" },
   { "(!`A)",  "\313" },
   { "(!`E)",  "\351" },
   { "(!`I)",  "\355" },
   { "(!`O)",  "\361" },
   { "(!`U)",  "\364" },                  /* 10 */

   { "(!^a)",  "\211" },
   { "(!^e)",  "\220" },
   { "(!^i)",  "\224" },
   { "(!^o)",  "\231" },
   { "(!^u)",  "\236" },
   { "(!^A)",  "\345" },
   { "(!^E)",  "\346" },
   { "(!^I)",  "\353" },
   { "(!^O)",  "\357" },
   { "(!^U)",  "\363" },                  /* 10 */

   { "(!~a)",  "\213" },
   { "(!~n)",  "\226" },
   { "(!~o)",  "\233" },
   { "(!~A)",  "\314" },
   { "(!~N)",  "\204" },
   { "(!~O)",  "\315" },                  /*  6 */

   { "(!.a)",  "\214" },
   { "(!.A)",  "\201" },                  /*  2 */

   { "(!&ae)", "\276" },
   { "(!&AE)", "\256" },
   { "(!&oe)", "\317" },
   { "(!&OE)", "\316" },                  /*  4 */

   { "(!,c)",  "\215" },
   { "(!,C)",  "\202" },                  /*  2 */

   { "(!_a)",  "\273" },
   { "(!_o)",  "\274" },                  /*  2 */

   { "(!\\o)", "\277" },
   { "(!\\O)", "\257" },                  /*  2 */

   { "(!#S)",  "\244" },
};


/* +++ EOF +++ */
