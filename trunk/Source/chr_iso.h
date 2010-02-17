/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_iso.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer Commodore Amiga und Linux
*                 Werte laut Screenshot von Michael Gehrke @ MK2
*                 und Tabelle von Frank Baumgart @ PB3
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
*    fd  Feb 12: u_CODE_ISO[] introduced
*    fd  Feb 17: - iso2sys_item[] removed (deprecated)
*                - chrtab[] merged in CHR.H
*
******************************************|************************************/

#ifndef ID_CHARSET_H
#define ID_CHARSET_H
const char *id_charset_h= "@(#) chr_iso.h   16.07.1998";
#endif

#ifndef THIS_CHARSET
#define THIS_CHARSET   "ISO Latin1"
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


#define UNI2SYSTABSIZE   64


LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   { "(!\"a)", "\344" },
   { "(!\"e)", "\353" },
   { "(!\"i)", "\357" },
   { "(!\"o)", "\366" },
   { "(!\"u)", "\374" },
   { "(!\"y)", "\377" },
   { "(!\"s)", "\337" },
   { "(!\"A)", "\304" },
   { "(!\"E)", "\313" },
   { "(!\"I)", "\317" },
   { "(!\"O)", "\326" },
   { "(!\"U)", "\334" },
   { "(!\"Y)", "\237" },                  /* 13 */

   { "(!'a)",  "\341" },
   { "(!'e)",  "\351" },
   { "(!'i)",  "\355" },
   { "(!'o)",  "\363" },
   { "(!'u)",  "\372" },
   { "(!'y)",  "\375" },
   { "(!'A)",  "\301" },
   { "(!'E)",  "\311" },
   { "(!'I)",  "\315" },
   { "(!'O)",  "\323" },
   { "(!'U)",  "\332" },
   { "(!'Y)",  "\335" },                  /* 12 */

   { "(!`a)",  "\340" },
   { "(!`e)",  "\350" },
   { "(!`i)",  "\354" },
   { "(!`o)",  "\362" },
   { "(!`u)",  "\371" },
   { "(!`A)",  "\300" },
   { "(!`E)",  "\310" },
   { "(!`I)",  "\314" },
   { "(!`O)",  "\322" },
   { "(!`U)",  "\331" },                  /* 10 */

   { "(!^a)",  "\342" },
   { "(!^e)",  "\352" },
   { "(!^i)",  "\356" },
   { "(!^o)",  "\364" },
   { "(!^u)",  "\373" },
   { "(!^A)",  "\302" },
   { "(!^E)",  "\312" },
   { "(!^I)",  "\316" },
   { "(!^O)",  "\324" },
   { "(!^U)",  "\333" },                  /* 10 */

   { "(!~a)",  "\343" },
   { "(!~n)",  "\361" },
   { "(!~o)",  "\365" },
   { "(!~A)",  "\303" },
   { "(!~N)",  "\321" },
   { "(!~O)",  "\325" },                  /*  6 */

   { "(!.a)",  "\345" },
   { "(!.A)",  "\305" },                  /*  2 */

   { "(!&ae)", "\346" },
   { "(!&AE)", "\306" },
   { "(!&oe)", "\234" },
   { "(!&OE)", "\214" },                  /*  4 */

   { "(!,c)",  "\347" },
   { "(!,C)",  "\307" },                  /*  2 */

   { "(!_a)",  "\252" },
   { "(!_o)",  "\272" },                  /*  2 */

   { "(!\\o)", "\370" },
   { "(!\\O)", "\330" },                  /*  2 */

   { "(!#S)",  "\247" },
};


/* +++ EOF +++ */
