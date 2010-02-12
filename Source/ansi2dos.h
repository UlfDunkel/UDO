/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : ansi2dos.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen von Windows-ANSI nach DOS
*                 basierend auf tos2iso.h
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
*    fd  Feb 12: header updated, file reformatted and tidied up (TAB-free)
*
******************************************|************************************/

#ifndef __ANSI2DOS__
#define __ANSI2DOS__


#ifndef ID_ANSI2DOS_H
#define ID_ANSI2DOS_H
const char  *id_ansi2dos_h = "@(#) ansi2dos.h  $date$";
#endif


typedef struct _ansi2dos
{
   unsigned char   ansi;                  /* */
   unsigned char   dos;                   /* */
}  ANSI2DOS;


LOCAL const ANSI2DOS   ansi2dos_item[128] =
{
   { 128,   0 },
   { 129,   0 },
   { 130,   0 },
   { 131, 159 },                          /* #f */
   { 132,   0 },
   { 133,   0 },
   { 134, 187 },                          /* #dag */
   { 135,   0 },
   { 136, 222 },                          /* #circ */
   { 137,   0 },
   { 138,   0 },
   { 139,   0 },
   { 140, 181 },                          /* &OE */
   { 141,   0 },
   { 142,   0 },
   { 143,   0 },
   { 144,   0 },
   { 145,   0 },
   { 146,   0 },
   { 147,   0 },
   { 148,   0 },
   { 149, 249 },                          /* #bullet */
   { 150,   0 },
   { 151,   0 },
   { 152,   0 },
   { 153, 191 },                          /* #tm */
   { 154,   0 },
   { 155,   0 },
   { 156, 180 },                          /* &oe */
   { 157,   0 },
   { 158,   0 },
   { 159,   0 },
   { 160,   0 },
   { 161, 173 },                          /* #! */
   { 162, 155 },                          /* #cent */
   { 163, 156 },                          /* #pound */
   { 164,   0 },
   { 165, 157 },                          /* #yen */
   { 166,   0 },
   { 167, 221 },                          /* #sect */
   { 168, 185 },                          /* #" */
   { 169, 189 },                          /* #copy */
   { 170, 166 },                          /* _a */
   { 171, 174 },                          /* #< */
   { 172, 170 },                          /* #neg */
   { 173,   0 },
   { 174, 190 },                          /* #reg */
   { 175,   0 },
   { 176, 248 },                          /* #degree */
   { 177, 241 },                          /* #pm */
   { 178, 253 },                          /* #^2 */
   { 179, 254 },                          /* #^3 */
   { 180, 186 },                          /* #' */
   { 181, 230 },                          /* #mu */
   { 182, 188 },                          /* #p */
   { 183, 250 },                          /* #cdot */
   { 184,   0 },
   { 185,   0 },
   { 186, 167 },                          /* _o */
   { 187, 175 },                          /* #> */
   { 188, 172 },                          /* #1/4 */
   { 189, 171 },                          /* #1/2 */
   { 190,   0 },
   { 191, 168 },                          /* #? */
   { 192, 182 },                          /* `A */
   { 193,   0 },
   { 194,   0 },
   { 195, 183 },                          /* ~A */
   { 196, 142 },                          /* "A */
   { 197, 143 },                          /* .A */
   { 198, 146 },                          /* &AE */
   { 199, 128 },                          /* ,C */
   { 200,   0 },
   { 201, 144 },                          /* 'E */
   { 202,   0 },
   { 203,   0 },
   { 204,   0 },
   { 205,   0 },
   { 206,   0 },
   { 207,   0 },
   { 208,   0 },
   { 209, 165 },                          /* ~N */
   { 210,   0 },
   { 211,   0 },
   { 212,   0 },
   { 213, 184 },                          /* ~O */
   { 214, 153 },                          /* "O */
   { 215,   0 },
   { 216, 178 },                          /* /O */
   { 217,   0 },
   { 218,   0 },
   { 219,   0 },
   { 220, 154 },                          /* "U */
   { 221,   0 },
   { 222,   0 },
   { 223, 225 },                          /* "s (sz) */
   { 224, 133 },                          /* `a */
   { 225, 160 },                          /* 'a */
   { 226, 131 },                          /* ^a */
   { 227, 176 },                          /* ~a */
   { 228, 132 },                          /* "a */
   { 229, 134 },                          /* .a */
   { 230, 145 },                          /* &ae */
   { 231, 135 },                          /* ,c */
   { 232, 138 },                          /* `e */
   { 233, 130 },                          /* 'e */
   { 234, 136 },                          /* ^e */
   { 235, 137 },                          /* "e */
   { 236, 141 },                          /* `i */
   { 237, 161 },                          /* 'i */
   { 238, 140 },                          /* ^i */
   { 239, 139 },                          /* "i */
   { 240,   0 },
   { 241, 164 },                          /* ~n */
   { 242, 149 },                          /* `o */
   { 243, 162 },                          /* 'o */
   { 244, 147 },                          /* ^o */
   { 245, 177 },                          /* ~o */
   { 246, 148 },                          /* "o */
   { 247, 246 },                          /* div */
   { 248, 179 },                          /* /o */
   { 249, 151 },                          /* `u */
   { 250, 163 },                          /* 'u */
   { 251, 150 },                          /* ^u */
   { 252, 129 },                          /* "u */
   { 253,   0 },
   { 254,   0 },
   { 255, 152 }                           /* "y */
};


#endif   /* __ANSI2DOS__ */


/* +++ EOF +++ */

