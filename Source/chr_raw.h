/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_raw.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer ...
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
const char  *id_charset_h = "@(#) chr_  .h    $date$";
#endif





/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#include "portab.h"





/*******************************************************************************
*
*     Recode ISO codepage into System codepage
*
******************************************|************************************/

typedef struct _ansi2ascii
{
   unsigned char   iso;                   /* */
   unsigned char   charsys;               /* */
}  ANSI2ASCII;





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


#define UNI2SYSTABSIZE   64               /* fd:2010-02-11: was 63 ?!? */


LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   { "(!\"a)", ""  },
   { "(!\"e)", ""  },
   { "(!\"i)", ""  },
   { "(!\"o)", ""  },
   { "(!\"u)", ""  },
   { "(!\"y)", ""  },
   { "(!\"s)", ""  },
   { "(!\"A)", ""  },
   { "(!\"E)", ""  },
   { "(!\"I)", ""  },
   { "(!\"O)", ""  },
   { "(!\"U)", ""  },
   { "(!\"Y)", ""  },                     /* 13 */

   { "(!'a)",  ""  },
   { "(!'e)",  ""  },
   { "(!'i)",  ""  },
   { "(!'o)",  ""  },
   { "(!'u)",  ""  },
   { "(!'y)",  ""  },
   { "(!'A)",  ""  },
   { "(!'E)",  ""  },
   { "(!'I)",  ""  },
   { "(!'O)",  ""  },
   { "(!'U)",  ""  },
   { "(!'Y)",  ""  },                     /* 12 */

   { "(!`a)",  ""  },
   { "(!`e)",  ""  },
   { "(!`i)",  ""  },
   { "(!`o)",  ""  },
   { "(!`u)",  ""  },
   { "(!`A)",  ""  },
   { "(!`E)",  ""  },
   { "(!`I)",  ""  },
   { "(!`O)",  ""  },
   { "(!`U)",  ""  },                     /* 10 */

   { "(!^a)",  ""  },
   { "(!^e)",  ""  },
   { "(!^i)",  ""  },
   { "(!^o)",  ""  },
   { "(!^u)",  ""  },
   { "(!^A)",  ""  },
   { "(!^E)",  ""  },
   { "(!^I)",  ""  },
   { "(!^O)",  ""  },
   { "(!^U)",  ""  },                     /* 10 */

   { "(!~a)",  ""  },
   { "(!~n)",  ""  },
   { "(!~o)",  ""  },
   { "(!~A)",  ""  },
   { "(!~N)",  ""  },
   { "(!~O)",  ""  },                     /*  6 */

   { "(!.a)",  ""  },
   { "(!.A)",  ""  },                     /*  2 */

   { "(!&ae)", ""  },
   { "(!&AE)", ""  },
   { "(!&oe)", ""  },
   { "(!&OE)", ""  },                     /*  4 */

   { "(!,c)",  ""  },
   { "(!,C)",  ""  },                     /*  2 */

   { "(!_a)",  ""  },
   { "(!_o)",  ""  },                     /*  2 */

   { "(!\\o)", ""  },
   { "(!\\O)", ""  },                     /*  2 */

   { "(!#S)",  "." },
};


/* +++ EOF +++ */
