/*	############################################################
	# @(#) mac2iso.h
	# @(#) Uebersetzungstabellen von Mac nach ISO-Latin-1
	# @(#)
	# @(#) Copyright (c) 1995-2001 by Dirk Hagedorn
	# @(#) Dirk Hagedorn (udo@dirk-hagedorn.de)
	#
	# This program is free software; you can redistribute it and/or
	# modify it under the terms of the GNU General Public License
	# as published by the Free Software Foundation; either version 2
	# of the License, or (at your option) any later version.
	# 
	# This program is distributed in the hope that it will be useful,
	# but WITHOUT ANY WARRANTY; without even the implied warranty of
	# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	# GNU General Public License for more details.
	# 
	# You should have received a copy of the GNU General Public License
	# along with this program; if not, write to the Free Software
	# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
	# 
	#
	# basierend auf iso2sys_item aus chr_mac.h
	# (0 geloescht, Werte umgedreht, sortiert, 0 eingefuegt)
	############################################################	*/

#ifndef __MAC2ISO__
#define __MAC2ISO__


#ifndef ID_MAC2ISO_H
#define	ID_MAC2ISO_H
const char *id_mac2iso_h= "@(#) mac2iso.h   26.06.1996";
#endif


typedef struct _mac2iso
{	unsigned char	mac;
	unsigned char	iso;
}	MAC2ISO;


LOCAL const MAC2ISO mac2iso_item[128]=
{
	{ 128, 196 },			/* "A 		*/
	{ 129, 197 },		/* .A		*/

	{ 130, 199 },		/* ,C		*/
	{ 131, 201 },		/* 'E		*/
	{ 132, 209 },		/* ~N		*/
	{ 133, 214 },		/* "O		*/
	{ 134, 220 },		/* "U		*/
	{ 135, 225 },		/* 'a		*/
	{ 136, 224 },		/* `a		*/
	{ 137, 226 },		/* ^a		*/
	{ 138, 228 },		/* "a		*/
	{ 139, 227 },		/* ~a		*/

	{ 140, 229 },		/* .a		*/
	{ 141, 231 },		/* ,c		*/
	{ 142, 233 },		/* 'e		*/
	{ 143, 232 },		/* `e		*/
	{ 144, 234 },		/* ^e		*/
	{ 145, 235 },		/* "e		*/
	{ 146, 237 },		/* 'i		*/
	{ 147, 236 },		/* `i		*/
	{ 148, 238 },		/* ^i		*/
	{ 149, 239 },		/* "i		*/

	{ 150, 241 },		/* ~n		*/
	{ 151, 243 },		/* 'o		*/
	{ 152, 242 },		/* `o		*/
	{ 153, 244 },		/* ^o		*/
	{ 154, 246 },		/* "o		*/
	{ 155, 245 },		/* ~o		*/
	{ 156, 250 },		/* 'u		*/
	{ 157, 249 },		/* `u		*/
	{ 158, 251 },		/* ^u		*/
	{ 159, 252 },		/* "u		*/

	{ 160, 134 },		/* #dag		*/
	{ 161, 176 },		/* #degree	*/
	{ 162, 162 },		/* #cent	*/
	{ 163, 163 },		/* #pound	*/
	{ 164, 167 },		/* #sect	*/
	{ 165, 149 },		/* #bullet	*/
	{ 166, 182 },		/* #p		*/
	{ 167, 223 },		/* "s (sz)	*/
	{ 168, 174 },		/* #reg		*/
	{ 169, 169 },		/* #copy	*/

	{ 170, 153 },		/* #tm		*/
	{ 171, 180 },		/* #'		*/
	{ 172, 168 },		/* #"		*/
	{ 173, 0   },		/* /= (neq) */
	{ 174, 198 },		/* &AE		*/
	{ 175, 216 },		/* /O		*/
	{ 176, 0   },		/* (leer)	*/
	{ 177, 177 },		/* #pm		*/
	{ 178, 0   },		/* <=		*/
	{ 179, 0   },		/* >=		*/

	{ 180, 165 },		/* #yen		*/
	{ 181, 181 },		/* #mu		*/
	{ 182, 0   },		/* delta	*/
	{ 183, 0   },		/* Sigma	*/
	{ 184, 0   },		/* Pi		*/
	{ 185, 0   },		/* pi		*/
	{ 186, 0   },		/* Integral	*/
	{ 187, 170 },		/* _a		*/
	{ 188, 186 },		/* _o		*/
	{ 189, 0   },		/* Omega	*/

	{ 190, 230 },		/* &ae		*/
	{ 191, 248 },		/* /o		*/
	{ 192, 191 },		/* #?		*/
	{ 193, 161 },		/* #!		*/
	{ 194, 172 },		/* #neg		*/
	{ 195, 0   },		/* wurzel	*/
	{ 196, 131 },		/* #f		*/
	{ 197, 0   },		/* circa	*/
	{ 198, 0   },		/* Delta	*/
	{ 199, 171 },		/* #<		*/

	{ 200, 187 },		/* #>		*/
	{ 201, 133 },		/* !..		*/
	{ 202, 0   },		/* nbsp		*/
	{ 203, 192 },		/* `A		*/
	{ 204, 195 },		/* ~A		*/
	{ 205, 213 },		/* ~O		*/
	{ 206, 140 },		/* &OE		*/
	{ 207, 156 },		/* &oe		*/
	{ 208, 150 },		/* --		*/
	{ 209, 151 },		/* ---		*/

	{ 210, 147 },		/* "" (66o)	*/
	{ 211, 148 },		/* "" (99o)	*/
	{ 212, 145 },		/* ` (6o)	*/
	{ 213, 146 },		/* '' (9o)	*/
	{ 214, 247 },		/* #div		*/
	{ 215, 0   },		/* Raute	*/
	{ 216, 255 },		/* "y		*/
	{ 217, 159 },		/* "Y		*/
	{ 218, '/' },		/* /		*/
	{ 219, 164 },		/* general currency	*/

	{ 220, 139 },		/* <		*/
	{ 221, 155 },		/* >		*/
	{ 222, 0   },		/* fi-Lig	*/
	{ 223, 0   },		/* fl-Lig	*/
	{ 224, 135 },		/* 2x#dag	*/
	{ 225, 0   },		/* dot		*/
	{ 226, 130 },		/* '' (9u)	*/
	{ 227, 132 },		/* "" (99u)	*/
	{ 228, 137 },		/* #promill	*/
	{ 229, 194 },		/* ^A		*/

	{ 230, 202 },		/* ^E		*/
	{ 231, 193 },		/* 'A		*/
	{ 232, 203 },		/* "E		*/
	{ 233, 200 },		/* `E		*/
	{ 234, 205 },		/* 'I		*/
	{ 235, 206 },		/* ^I		*/
	{ 236, 207 },		/* "I		*/
	{ 237, 204 },		/* `I		*/
	{ 238, 211 },		/* 'O		*/
	{ 239, 212 },		/* ^O		*/

	{ 240, 0   },		/* Apfel	*/
	{ 241, 210 },		/* `O		*/
	{ 242, 218 },		/* 'U		*/
	{ 243, 219 },		/* ^U		*/
	{ 244, 217 },		/* `U		*/
	{ 245, 185 },		/* #^1		*/
	{ 246, 136 },		/* #circ	*/
	{ 247, 0   },		/* ~-Akzent	*/
	{ 248, 0   },		/* - Akzent */
	{ 249, 0   },		/* u Akzent */

	{ 250, 183 },		/* #cdot	*/
	{ 251, 0   },		/* o Akzent */
	{ 252, 184 },		/* cedille	*/
	{ 253, 0   },		/* Diaresis */
	{ 254, 0   },		/* ???		*/
	{ 255, 0   },		/* v Akzent */
};

#endif /* __MAC2ISO__ */

