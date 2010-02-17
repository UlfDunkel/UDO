/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_next.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer NeXTStep
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
*    fd  Feb 12: all octal chars converted into decimal values
*    fd  Feb 17: - iso2sys_item[] removed (deprecated)
*                - chrtab[] merged in CHR.H
*
******************************************|************************************/

#ifndef ID_CHARSET_H
#define ID_CHARSET_H
const char  *id_charset_h = "@(#) chr_next.h  $date$";
#endif

#ifndef THIS_CHARSET
#define THIS_CHARSET   "NeXTStep"
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
   char           *uni;                   /* */
   unsigned char  *system;                /* */
}  UNI2SYSTAB;


#define UNI2SYSTABSIZE  64


LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   { "(!\"a)", "\331" },
   { "(!\"e)", "\337" },
   { "(!\"i)", "\345" },
   { "(!\"o)", "\360" },
   { "(!\"u)", "\366" },
   { "(!\"y)", "\375" },
   { "(!\"s)", "\373" },
   { "(!\"A)", "\205" },
   { "(!\"E)", "\213" },
   { "(!\"I)", "\217" },
   { "(!\"O)", "\226" },
   { "(!\"U)", "\232" },
   { "(!\"Y)", "Y"    },                  /* 13 */

   { "(!'a)",  "\326" },
   { "(!'e)",  "\335" },
   { "(!'i)",  "\342" },
   { "(!'o)",  "\355" },
   { "(!'u)",  "\363" },
   { "(!'y)",  "\367" },
   { "(!'A)",  "\202" },
   { "(!'E)",  "\211" },
   { "(!'I)",  "\215" },
   { "(!'O)",  "\223" },
   { "(!'U)",  "\230" },
   { "(!'Y)",  "\233" },                  /* 12 */

   { "(!`a)",  "\325" },
   { "(!`e)",  "\334" },
   { "(!`i)",  "\340" },
   { "(!`o)",  "\354" },
   { "(!`u)",  "\362" },
   { "(!`A)",  "\201" },
   { "(!`E)",  "\210" },
   { "(!`I)",  "\214" },
   { "(!`O)",  "\222" },
   { "(!`U)",  "\227" },                  /* 10 */

   { "(!^a)",  "\327" },
   { "(!^e)",  "\336" },
   { "(!^i)",  "\344" },
   { "(!^o)",  "\356" },
   { "(!^u)",  "\364" },
   { "(!^A)",  "\203" },
   { "(!^E)",  "\212" },
   { "(!^I)",  "\216" },
   { "(!^O)",  "\224" },
   { "(!^U)",  "\231" },                  /* 10 */

   { "(!~a)",  "\330" },
   { "(!~n)",  "\347" },
   { "(!~o)",  "\357" },
   { "(!~A)",  "\204" },
   { "(!~N)",  "\221" },
   { "(!~O)",  "\225" },                  /*  6 */

   { "(!.a)",  "\332" },
   { "(!.A)",  "\206" },                  /*  2 */

   { "(!&ae)", "\361" },
   { "(!&AE)", "\341" },
   { "(!&oe)", "\372" },
   { "(!&OE)", "\352" },                  /*  4 */

   { "(!,c)",  "\333" },
   { "(!,C)",  "\207" },                  /*  2 */

   { "(!_a)",  "\343" },
   { "(!_o)",  "\353" },                  /*  2 */

   { "(!\\o)", "\371" },
   { "(!\\O)", "\351" },                  /*  2 */

   { "(!#S)",  "\235" },
};


/* +++ EOF +++ */
