/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_hp8.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer HP-UX
*                 Charset: HP-Roman-8
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
const char *id_charset_h= "@(#) chr_hp8.h   18.04.1996";
#endif

#ifndef THIS_CHARSET
#define THIS_CHARSET   "HP Roman 8"
#endif





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
   { "(!\"a)", "\314" },
   { "(!\"e)", "\315" },
   { "(!\"i)", "\335" },
   { "(!\"o)", "\316" },
   { "(!\"u)", "\317" },
   { "(!\"y)", "\357" },
   { "(!\"s)", "\336" },
   { "(!\"A)", "\330" },
   { "(!\"E)", "\245" },
   { "(!\"I)", "\247" },
   { "(!\"O)", "\332" },
   { "(!\"U)", "\333" },
   { "(!\"Y)", "\356" },                  /* 13 */

   { "(!'a)",  "\304" },
   { "(!'e)",  "\305" },
   { "(!'i)",  "\325" },
   { "(!'o)",  "\306" },
   { "(!'u)",  "\307" },
   { "(!'y)",  "\262" },
   { "(!'A)",  "\340" },
   { "(!'E)",  "\334" },
   { "(!'I)",  "\346" },
   { "(!'O)",  "\347" },
   { "(!'U)",  "\355" },
   { "(!'Y)",  "\261" },                  /* 12 */

   { "(!`a)",  "\310" },
   { "(!`e)",  "\311" },
   { "(!`i)",  "\331" },
   { "(!`o)",  "\312" },
   { "(!`u)",  "\313" },
   { "(!`A)",  "\241" },
   { "(!`E)",  "\243" },
   { "(!`I)",  "\345" },
   { "(!`O)",  "\350" },
   { "(!`U)",  "\255" },                  /* 10 */

   { "(!^a)",  "\300" },
   { "(!^e)",  "\301" },
   { "(!^i)",  "\321" },
   { "(!^o)",  "\302" },
   { "(!^u)",  "\303" },
   { "(!^A)",  "\242" },
   { "(!^E)",  "\244" },
   { "(!^I)",  "\245" },
   { "(!^O)",  "\337" },
   { "(!^U)",  "\256" },                  /* 10 */

   { "(!~a)",  "\342" },
   { "(!~n)",  "\267" },
   { "(!~o)",  "\352" },
   { "(!~A)",  "\341" },
   { "(!~N)",  "\266" },
   { "(!~O)",  "\351" },                  /*  6 */

   { "(!.a)",  "\324" },
   { "(!.A)",  "\320" },                  /*  2 */

   { "(!&ae)", "\327" },
   { "(!&AE)", "\323" },
   { "(!&oe)", ""     },
   { "(!&OE)", ""     },                  /*  4 */

   { "(!,c)",  "\265" },
   { "(!,C)",  "\264" },                  /*  2 */

   { "(!_a)",  "\371" },
   { "(!_o)",  "\372" },                  /*  2 */

   { "(!\\o)", "\326" },
   { "(!\\O)", "\322" },                  /*  2 */

   { "(!#S)",  "\275" },
};


/* +++ EOF +++ */
