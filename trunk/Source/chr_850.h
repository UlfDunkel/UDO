/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_850.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer MS-DOS (Codepage 850)
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
*  2010:
*    fd  Feb 10: header updated, file reformatted and tidied up (TAB-free)
*    fd  Feb 12: all octal chars converted into decimal values
*    fd  Feb 17: - iso2sys_item[] removed (deprecated)
*                - chrtab[] merged in CHR.H
*
******************************************|************************************/

#ifndef ID_CHARSET_H
#define ID_CHARSET_H
const char  *id_charset_h = "@(#) chr_850.h   $date$";
#endif

#ifndef THIS_CHARSET
#define THIS_CHARSET   "cp850"
#endif





/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#include "portab.h"





/*******************************************************************************
*
*     Recode 'Universal Codepage' into ASCII codepages
*
******************************************|************************************/

typedef struct _uni2systab
{
   char           *uni;                   /* */
   unsigned char  *system;                /* */
}  UNI2SYSTAB;


#define UNI2SYSTABSIZE   64

LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   { "(!\"a)", "\204" },
   { "(!\"e)", "\211" },
   { "(!\"i)", "\213" },
   { "(!\"o)", "\224" },
   { "(!\"u)", "\201" },
   { "(!\"y)", "\230" },
   { "(!\"s)", "\341" },
   { "(!\"A)", "\216" },
   { "(!\"E)", "\323" },
   { "(!\"I)", "\330" },
   { "(!\"O)", "\231" },
   { "(!\"U)", "\232" },
   { "(!\"Y)", "Y"    },                  /* 13 */

   { "(!'a)",  "\240" },
   { "(!'e)",  "\202" },
   { "(!'i)",  "\241" },
   { "(!'o)",  "\242" },
   { "(!'u)",  "\243" },
   { "(!'y)",  "\354" },
   { "(!'A)",  "\265" },
   { "(!'E)",  "\220" },
   { "(!'I)",  "\326" },
   { "(!'O)",  "\340" },
   { "(!'U)",  "\351" },
   { "(!'Y)",  "\355" },                  /* 12 */

   { "(!`a)",  "\205" },
   { "(!`e)",  "\212" },
   { "(!`i)",  "\215" },
   { "(!`o)",  "\225" },
   { "(!`u)",  "\227" },
   { "(!`A)",  "\267" },
   { "(!`E)",  "\324" },
   { "(!`I)",  "\336" },
   { "(!`O)",  "\343" },
   { "(!`U)",  "\353" },                  /* 10 */

   { "(!^a)",  "\203" },
   { "(!^e)",  "\210" },
   { "(!^i)",  "\214" },
   { "(!^o)",  "\223" },
   { "(!^u)",  "\226" },
   { "(!^A)",  "\266" },
   { "(!^E)",  "\322" },
   { "(!^I)",  "\327" },
   { "(!^O)",  "\342" },
   { "(!^U)",  "\352" },                  /* 10 */

   { "(!~a)",  "\306" },
   { "(!~n)",  "\244" },
   { "(!~o)",  "\344" },
   { "(!~A)",  "\307" },
   { "(!~N)",  "\245" },
   { "(!~O)",  "\345" },                  /*  6 */

   { "(!.a)",  "\206" },
   { "(!.A)",  "\217" },                  /*  2 */

   { "(!&ae)", "\221" },
   { "(!&AE)", "\222" },
   { "(!&oe)", "oe"   },
   { "(!&OE)", "OE"   },                  /*  4 */

   { "(!,c)",  "\207" },
   { "(!,C)",  "\200" },                  /*  2 */

   { "(!_a)",  "\246" },
   { "(!_o)",  "\247" },                  /*  2 */

   { "(!\\o)", "\233" },
   { "(!\\O)", "\235" },                  /*  2 */

   { "(!#S)",  "\365" },
};


/* +++ EOF +++ */
