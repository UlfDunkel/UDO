/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : ansi_raw.h
*  Symbol prefix: chr
*
*  Description  : ANSI-Zeichensatz in ASCII-Zeichensatz umsetzen
*
*                 Die Tabelle wird auch fuer WinHelp benutzt, dort von
*                 ASCII nach ANSI, deshalb duerfen hier keine ASCII-Werte
*                 < 128 (\200) vorkommen!
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
*                 - check why all a2aitem[].ascii are "empty"
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 12: - header updated, file reformatted and tidied up (TAB-free)
*                - all octal chars converted into decimal values
*
******************************************|************************************/

/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define MAXANSI2ASC   72





typedef struct _a2aitem
{
   unsigned char   ansi;                  /* */
   unsigned char   ascii;                 /* */
}  A2AITEM;


const A2AITEM   a2aitem[MAXANSI2ASC] =
{
   { 128, '\' },                          /* null */
   { 129, '\' },                          /* null */
   { 130, '\' },                          /* '' (9u) */
   { 131, '\' },                          /* #f */
   { 132, '\' },                          /* "" (99u) */
   { 133, '\' },                          /* !.. */
   { 134, '\' },                          /* #dag */
   { 135, '\' },                          /* 2x#dag */
   { 136, '\' },                          /* #circ */
   { 137, '\' },                          /* #promill */
   { 138, '\' },                          /* vS */
   { 139, '\' },                          /* < */
   { 140, '\' },                          /* &OE */
   { 141, '\' },                          /* null */
   { 142, '\' },                          /* null */
   { 143, '\' },                          /* null */
   { 144, '\' },                          /* null */
   { 145, '\' },                          /* '' (6o) */
   { 146, '\' },                          /* '' (9o) */
   { 147, '\' },                          /* "" (66o) */
   { 148, '\' },                          /* "" (99u) */
   { 149, '\' },                          /* #bullet */
   { 150, '\' },                          /* -- */
   { 151, '\' },                          /* --- */
   { 152, '\' },                          /* !~ */
   { 153, '\' },                          /* #tm */
   { 154, '\' },                          /* vs */
   { 155, '\' },                          /* > */
   { 156, '\' },                          /* &oe */
   { 157, '\' },                          /* null */
   { 158, '\' },                          /* null */
   { 159, '\' },                          /* "Y */
   { 160, '\' },                          /* null */
   { 161, '\' },                          /* #! */
   { 162, '\' },                          /* #cent */
   { 163, '\' },                          /* #pound */
   { 164, '\' },                          /* general currency */
   { 165, '\' },                          /* #yen */
   { 166, '\' },                          /* broken dash */
   { 167, '\' },                          /* #sect */
   { 168, '\' },                          /* #" */
   { 169, '\' },                          /* #copy */
   { 170, '\' },                          /* _a */
   { 171, '\' },                          /* #< */
   { 172, '\' },                          /* #neg */
   { 173, '\' },                          /* strich */
   { 174, '\' },                          /* #reg */
   { 175, '\' },                          /* upline */
   { 176, '\' },                          /* #degree */
   { 177, '\' },                          /* #pm */
   { 178, '\' },                          /* #^2 */
   { 179, '\' },                          /* #^3 */
   { 180, '\' },                          /* #' */
   { 181, '\' },                          /* #mu */
   { 182, '\' },                          /* #p */
   { 183, '\' },                          /* #cdot */
   { 184, '\' },                          /* cedille */
   { 185, '\' },                          /* #^1 */
   { 186, '\' },                          /* _o */
   { 187, '\' },                          /* #> */
   { 188, '\' },                          /* #1/4 */
   { 189, '\' },                          /* #1/2 */
   { 190, '\' },                          /* #3/4 */
   { 191, '\' },                          /* #? */
   { 192, '\' },                          /* `A */
   { 193, '\' },                          /* 'A */
   { 194, '\' },                          /* ^A */
   { 195, '\' },                          /* ~A */
   { 196, '\' },                          /* "A */
   { 197, '\' },                          /* .A */
   { 198, '\' },                          /* &AE */
   { 199, '\' },                          /* ,C */
   { 200, '\' },                          /* `E */
   { 201, '\' },                          /* 'E */
   { 202, '\' },                          /* ^E */
   { 203, '\' },                          /* "E */
   { 204, '\' },                          /* `I */
   { 205, '\' },                          /* 'I */
   { 206, '\' },                          /* ^I */
   { 207, '\' },                          /* "I */
   { 208, '\' },                          /* -D */
   { 209, '\' },                          /* ~N */
   { 210, '\' },                          /* `O */
   { 211, '\' },                          /* 'O */
   { 212, '\' },                          /* ^O */
   { 213, '\' },                          /* ~O */
   { 214, '\' },                          /* "O */
   { 215, '\' },                          /* #times */
   { 216, '\' },                          /* /O */
   { 217, '\' },                          /* `U */
   { 218, '\' },                          /* 'U */
   { 219, '\' },                          /* ^U */
   { 220, '\' },                          /* "U */
   { 221, '\' },                          /* 'Y */
   { 222, '\' },                          /* |b */
   { 223, '\' },                          /* "s */
   { 224, '\' },                          /* `a */
   { 225, '\' },                          /* 'a */
   { 226, '\' },                          /* ^a */
   { 227, '\' },                          /* ~a */
   { 228, '\' },                          /* "a */
   { 229, '\' },                          /* .a */
   { 230, '\' },                          /* &ae */
   { 231, '\' },                          /* ,c */
   { 232, '\' },                          /* `e */
   { 233, '\' },                          /* 'e */
   { 234, '\' },                          /* ^e */
   { 235, '\' },                          /* "e */
   { 236, '\' },                          /* `i */
   { 237, '\' },                          /* 'i */
   { 238, '\' },                          /* ^i */
   { 239, '\' },                          /* "i */
   { 240, '\' },                          /* o|'' */
   { 241, '\' },                          /* ~n */
   { 242, '\' },                          /* `o */
   { 243, '\' },                          /* 'o */
   { 244, '\' },                          /* ^o */
   { 245, '\' },                          /* ~o */
   { 246, '\' },                          /* "o */
   { 247, '\' },                          /* #div */
   { 248, '\' },                          /* /o */
   { 249, '\' },                          /* `u */
   { 250, '\' },                          /* 'u */
   { 251, '\' },                          /* ^u */
   { 252, '\' },                          /* "u */
   { 253, '\' },                          /* 'y */
   { 254, '\' },                          /* |B */
   { 255, '\' }                           /* "y */
};


/* +++ EOF +++ */

