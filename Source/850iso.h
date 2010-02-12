/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : 850iso.h
*  Symbol prefix: chr
*
*  Description  : Uebersetzungstabellen von Codepage 850 nach ISO-Latin-1
*                 basierend auf chr_850.h
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

#ifndef __850ISO__
#define __850ISO__


#ifndef ID_850ISO_H
#define ID_850ISO_H
const char  *id_850iso_h = "@(#) 850iso.h    $date$";
#endif


typedef struct _cp850iso
{
   unsigned char   cp850;                 /* */
   unsigned char   iso;                   /* */
}  CP850ISO;


LOCAL const CP850ISO   cp850iso_item[128] =
{
   { 128,   199 },                        /* ,C */
   { 129,   252 },                        /* "u */
   { 130,   233 },                        /* 'e */
   { 131,   226 },                        /* ^a */
   { 132,   228 },                        /* "a */
   { 133,   224 },                        /* `a */
   { 134,   229 },                        /* .a */
   { 135,   231 },                        /* ,c */
   { 136,   234 },                        /* ^e */
   { 137,   235 },                        /* "e */
   { 138,   232 },                        /* `e */
   { 139,   239 },                        /* "i */
   { 140,   238 },                        /* ^i */
   { 141,   236 },                        /* `i */
   { 142,   196 },                        /* "A */
   { 143,   197 },                        /* .A */
   { 144,   201 },                        /* 'E */
   { 145,   230 },                        /* &ae */
   { 146,   198 },                        /* &AE */
   { 147,   244 },                        /* ^o */
   { 148,   246 },                        /* "o */
   { 149,   242 },                        /* `o */
   { 150,   251 },                        /* ^u */
   { 151,   249 },                        /* `u */
   { 152,   255 },                        /* "y */
   { 153,   214 },                        /* "O */
   { 154,   220 },                        /* "U */
   { 155,   248 },                        /* /o */
   { 156,   163 },                        /* #pound */
   { 157,   216 },                        /* /O */
   { 158,   215 },                        /* #times */
   { 159,   131 },                        /* #f */
   { 160,   225 },                        /* 'a */
   { 161,   237 },                        /* 'i */
   { 162,   243 },                        /* 'o */
   { 163,   250 },                        /* 'u */
   { 164,   241 },                        /* ~n */
   { 165,   209 },                        /* ~N */
   { 166,   170 },                        /* _a */
   { 167,   186 },                        /* _o */
   { 168,   191 },                        /* #? */
   { 169,   174 },                        /* #reg */
   { 160,   172 },                        /* #neg */
   { 171,   189 },                        /* #1/2 */
   { 172,   188 },                        /* #1/4 */
   { 173,   161 },                        /* #! */
   { 174,   171 },                        /* #< */
   { 175,   187 },                        /* #> */
   { 176,     0 },
   { 177,     0 },
   { 178,     0 },
   { 179,     0 },
   { 180,     0 },
   { 181,   193 },                        /* 'A */
   { 182,   194 },                        /* ^A */
   { 183,   192 },                        /* `A */
   { 184,   169 },                        /* #copy */
   { 185,     0 },
   { 186,     0 },
   { 187,     0 },
   { 188,     0 },
   { 189,   162 },                        /* #cent */
   { 190,   165 },                        /* #yen */
   { 191,     0 },
   { 192,     0 },
   { 193,     0 },
   { 194,     0 },
   { 195,     0 },
   { 196,     0 },
   { 197,     0 },
   { 198,   227 },                        /* ~a */
   { 199,   195 },                        /* ~A */
   { 200,     0 },
   { 201,     0 },
   { 202,     0 },
   { 203,     0 },
   { 204,     0 },
   { 205,     0 },
   { 206,     0 },
   { 207,   164 },                        /* general currency */
   { 208,   240 },                        /* o|'' */
   { 209,   208 },                        /* -D */
   { 210,   202 },                        /* ^E */
   { 211,   203 },                        /* "E */
   { 212,   200 },                        /* `E */
   { 213,     0 },
   { 214,   205 },                        /* 'I */
   { 215,   206 },                        /* ^I */
   { 216,   207 },                        /* "I */
   { 217,     0 },
   { 218,     0 },
   { 219,     0 },
   { 220,     0 },
   { 221,   166 },                        /* broken dash */   /* !!!! */
   { 222,   204 },                        /* `I */
   { 223,     0 },
   { 224,   211 },                        /* 'O */
   { 225,   223 },                        /* "s (beta) */
   { 226,   212 },                        /* ^O */
   { 227,   210 },                        /* `O */
   { 228,   245 },                        /* ~o */
   { 229,   213 },                        /* ~O */
   { 230,   181 },                        /* #mu */
   { 231,   222 },                        /* |b */
   { 232,   254 },                        /* |B */
   { 233,   218 },                        /* 'U */
   { 234,   219 },                        /* ^U */
   { 235,   217 },                        /* `U */
   { 236,   253 },                        /* 'y */
   { 237,   221 },                        /* 'Y */
   { 238,   175 },
   { 239,   180 },                        /* #' */
   { 240,   173 },                        /* strich */
   { 241,   177 },                        /* #pm */
   { 242,     0 },
   { 243,   190 },                        /* #3/4 */
   { 244,   182 },                        /* #p */
   { 245,   167 },                        /* #sect */
   { 246,   247 },                        /* #div */
   { 247,   184 },                        /* cedille */
   { 248,   176 },                        /* #degree */
   { 249,   168 },                        /* #" */
   { 250,   149 },                        /* #bullet */
   { 251,   185 },                        /* #^1 */
   { 252,   179 },                        /* #^3 */
   { 253,   178 },                        /* #^2 */
   { 254,     0 },
   { 255,     0 }
};


#endif   /* __850ISO__ */


/* +++ EOF +++ */

