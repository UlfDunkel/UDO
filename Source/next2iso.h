/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : next2iso.h
*  Symbol prefix: chr
*
*  Description  : basierend auf iso2sys_item aus chr_next.h
*                 (0 geloescht, Werte umgedreht, sortiert, 0 eingefuegt)
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

#ifndef __NEXT2ISO__
#define __NEXT2ISO__


#ifndef ID_NEXT2ISO_H
#define ID_NEXT2ISO_H
const char  *id_next2iso_h = "@(#) next2iso.h  $date$";
#endif


typedef struct _next2iso
{
   unsigned char   next;                  /* */
   unsigned char   iso;                   /* */
}  NEXT2ISO;


LOCAL const NEXT2ISO   next2iso_item[128] =
{
   { 128,   0 },
   { 129, 192 },                          /* `A */

   { 130, 193 },                          /* 'A */
   { 131, 194 },                          /* ^A */
   { 132, 195 },                          /* ~A */
   { 133, 196 },                          /* "A */
   { 134, 197 },                          /* .A */
   { 135, 199 },                          /* ,C */
   { 136, 200 },                          /* `E */
   { 137, 201 },                          /* 'E */
   { 138, 202 },                          /* ^E */
   { 139, 203 },                          /* "E */

   { 140, 204 },                          /* `I */
   { 141, 205 },                          /* 'I */
   { 142, 206 },                          /* ^I */
   { 143, 207 },                          /* "I */
   { 144, 208 },                          /* -D */
   { 145, 209 },                          /* ~N */
   { 146, 210 },                          /* `O */
   { 147, 211 },                          /* 'O */
   { 148, 212 },                          /* ^O */
   { 149, 213 },                          /* ~O */

   { 150, 214 },                          /* "O */
   { 151, 217 },                          /* `U */
   { 152, 218 },                          /* 'U */
   { 153, 219 },                          /* ^U */
   { 154, 220 },                          /* "U */
   { 155, 221 },                          /* 'Y */
   { 156, 222 },                          /* |b */
   { 157, 181 },                          /* #mu */
   { 158, 215 },                          /* #times */
   { 159, 247 },                          /* #div */

   { 160, 169 },                          /* #copy */
   { 161, 161 },                          /* #! */
   { 162, 162 },                          /* #cent */
   { 163, 163 },                          /* #pound */
   { 164,   0 },
   { 165, 165 },                          /* #yen */
   { 166, 131 },                          /* #f */
   { 167,   0 },
   { 168, 164 },                          /* general currency */
   { 169, 146 },                          /* '' (9o) */

   { 170, 147 },                          /* "" (66o) */
   { 171, 171 },                          /* #< */
   { 172, 139 },                          /* < */
   { 173, 155 },                          /* > */
   { 174,   0 },
   { 175,   0 },
   { 176, 174 },                          /* #reg */
   { 177, 150 },                          /* -- */
   { 178, 134 },                          /* #dag */
   { 179, 135 },                          /* 2x#dag */

   { 180, 183 },                          /* #cdot */
   { 181, 166 },                          /* broken dash */
   { 182, 182 },                          /* #p */
   { 183, 149 },                          /* #bullet */
   { 184, 130 },                          /* '' (9u) */
   { 185, 132 },                          /* "" (99u) */
   { 186,   0 },
   { 187, 187 },                          /* #> */
   { 188, 133 },                          /* !.. */
   { 189, 137 },                          /* #promill */

   { 190, 172 },                          /* #neg */
   { 191, 191 },                          /* #? */
   { 192, 185 },                          /* #^1 */
   { 193,   0 },
   { 194, 180 },                          /* #' */
   { 195, 136 },                          /* #circ */
   { 196, 152 },                          /* !~ */
   { 197,   0 },
   { 198,   0 },
   { 199,   0 },

   { 200, 168 },                          /* #" */
   { 201, 178 },                          /* #^2 */
   { 202, 176 },                          /* #degree */
   { 203, 184 },                          /* cedille */
   { 204, 179 },                          /* #^3 */
   { 205,   0 },
   { 206,   0 },
   { 207,   0 },
   { 208, 151 },                          /* --- */
   { 209, 177 },                          /* #pm */

   { 210, 188 },                          /* #1/4 */
   { 211, 189 },                          /* #1/2 */
   { 212, 190 },                          /* #3/4 */
   { 213, 224 },                          /* `a */
   { 214, 225 },                          /* 'a */
   { 215, 226 },                          /* ^a */
   { 216, 227 },                          /* ~a */
   { 217, 228 },                          /* "a */
   { 218, 229 },                          /* .a */
   { 219, 231 },                          /* ,c */

   { 220, 232 },                          /* `e */
   { 221, 233 },                          /* 'e */
   { 222, 234 },                          /* ^e */
   { 223, 235 },                          /* "e */
   { 224, 236 },                          /* `i */
   { 225, 198 },                          /* &AE */
   { 226, 237 },                          /* 'i */
   { 227, 170 },                          /* _a */
   { 228, 238 },                          /* ^i */
   { 229, 239 },                          /* "i */

   { 230, 240 },                          /* o|'' */
   { 231, 241 },                          /* ~n */
   { 232,   0 },
   { 233, 216 },                          /* /O */
   { 234, 140 },                          /* &OE */
   { 235, 186 },                          /* _o */
   { 236, 242 },                          /* `o */
   { 237, 243 },                          /* 'o */
   { 238, 244 },                          /* ^o */
   { 239, 245 },                          /* ~o */

   { 240, 246 },                          /* "o */
   { 241, 230 },                          /* &ae */
   { 242, 249 },                          /* `u */
   { 243, 250 },                          /* 'u */
   { 244, 251 },                          /* ^u */
   { 245,   0 },
   { 246, 252 },                          /* "u */
   { 247, 253 },                          /* 'y */
   { 248,   0 },
   { 249, 248 },                          /* /o */

   { 250, 156 },                          /* &oe */
   { 251, 223 },                          /* "s (sz) */
   { 252, 254 },                          /* |B */
   { 253, 255 },                          /* "y */
   { 254,   0 },
   { 255,   0 },

};

#endif /* __NEXT2ISO__ */


/* +++ EOF +++ */

