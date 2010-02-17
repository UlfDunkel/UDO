/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr_tos.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen fuer Atari TOS
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
*    fd  Feb 12: - all octal chars converted into decimal values
*                - u_CODE_TOS[] introduced
*    fd  Feb 17: - iso2sys_item[] removed (deprecated)
*                - chrtab[] merged in CHR.H
*
******************************************|************************************/

#ifndef ID_CHARSET_H
#define ID_CHARSET_H
const char  *id_charset_h = "@(#) chr_tos.h   $date$";
#endif

#ifndef THIS_CHARSET
#define THIS_CHARSET  "TOS"
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


#define UNI2SYSTABSIZE  64

LOCAL const UNI2SYSTAB   uni2sys[UNI2SYSTABSIZE] =
{
   {"(!\"a)",  "\204"},
   {"(!\"e)",  "\211"},
   {"(!\"i)",  "\213"},
   {"(!\"o)",  "\224"},
   {"(!\"u)",  "\201"},
   {"(!\"y)",  "\230"},
   {"(!\"s)",  "\236"},
   {"(!\"A)",  "\216"},
   {"(!\"E)",  "E"   },
   {"(!\"I)",  "I"   },
   {"(!\"O)",  "\231"},
   {"(!\"U)",  "\232"},
   {"(!\"Y)",  "Y"   },                   /* 13 */
   
   {"(!'a)",   "\240"},
   {"(!'e)",   "\202"},
   {"(!'i)",   "\241"},
   {"(!'o)",   "\242"},
   {"(!'u)",   "\243"},
   {"(!'y)",   "y"   },
   {"(!'A)",   "A"   },
   {"(!'E)",   "\220"},
   {"(!'I)",   "I"   },
   {"(!'O)",   "O"   },
   {"(!'U)",   "U"   },
   {"(!'Y)",   "Y"   },                   /* 12 */
   
   {"(!`a)",   "\205"},
   {"(!`e)",   "\212"},
   {"(!`i)",   "\215"},
   {"(!`o)",   "\225"},
   {"(!`u)",   "\227"},
   {"(!`A)",   "A"   },
   {"(!`E)",   "E"   },
   {"(!`I)",   "I"   },
   {"(!`O)",   "O"   },
   {"(!`U)",   "U"   },                   /* 10 */
   
   {"(!^a)",   "\203"},
   {"(!^e)",   "\210"},
   {"(!^i)",   "\214"},
   {"(!^o)",   "\223"},
   {"(!^u)",   "\226"},
   {"(!^A)",   "A"   },
   {"(!^E)",   "E"   },
   {"(!^I)",   "I"   },
   {"(!^O)",   "O"   },
   {"(!^U)",   "U"   },                   /* 10 */
   
   {"(!~a)",   "a"   },
   {"(!~n)",   "\244"},
   {"(!~o)",   "o"   },
   {"(!~A)",   "A"   },
   {"(!~N)",   "\245"},
   {"(!~O)",   "O"   },                   /*  6 */
   
   {"(!.a)",   "\206"},
   {"(!.A)",   "\217"},                   /*  2 */
   
   {"(!&ae)",  "\221"},
   {"(!&AE)",  "\222"},
   {"(!&oe)",  "oe"  },
   {"(!&OE)",  "OE"  },                   /*  4 */
   
   {"(!,c)",   "\207"},
   {"(!,C)",   "\200"},                   /*  2 */
   
   {"(!_a)",   "\246"},
   {"(!_o)",   "\247"},                   /*  2 */
   
   {"(!\\o)",  "o"   },
   {"(!\\O)",  "O"   },                   /*  2 */
   
   {"(!#S)",   "\335"},
};


/* +++ EOF +++ */
