/*	############################################################
	# @(#) tos2iso.h
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
	# @(#) Uebersetzungstabellen von Atari-ST nach ISO-Latin-1
	# basierend auf chr_tos.h
	############################################################	*/

#ifndef	__TOS2ISO__
#define	__TOS2ISO__


#ifndef ID_TOS2ISO_H
#define	ID_TOS2ISO_H
const char *id_tos2iso_h= "@(#) tos2iso.h   11.07.1996";
#endif


typedef struct _tos2iso
{
	unsigned char	tos;
	unsigned char	iso;
}	TOS2ISO;


LOCAL const TOS2ISO tos2iso_item[128]=
{
	{ 128, 199 },		/* ,C		*/
	{ 129, 252 },		/* "u		*/
	{ 130, 233 },		/* 'e		*/
	{ 131, 226 },		/* ^a		*/
	{ 132, 228 },		/* "a		*/
	{ 133, 224 },		/* `a		*/
	{ 134, 229 },		/* .a		*/
	{ 135, 231 },		/* ,c		*/
	{ 136, 234 },		/* ^e		*/
	{ 137, 235 },		/* "e		*/
	{ 138, 232 },		/* `e		*/
	{ 139, 239 },		/* "i		*/
	{ 140, 238 },		/* ^i		*/
	{ 141, 236 },		/* `i		*/
	{ 142, 196 },		/* "A		*/
	{ 143, 197 },		/* .A		*/
	{ 144, 201 },		/* 'E		*/
	{ 145, 230 },		/* &ae		*/
	{ 146, 198 },		/* &AE		*/
	{ 147, 244 },		/* ^o		*/
	{ 148, 246 },		/* "o		*/
	{ 149, 242 },		/* `o		*/
	{ 150, 251 },		/* ^u		*/
	{ 151, 249 },		/* `u		*/
	{ 152, 255 },		/* "y		*/
	{ 153, 214 },		/* "O		*/
	{ 154, 220 },		/* "U		*/
	{ 155, 162 },		/* #cent	*/
	{ 156, 163 },		/* #pound	*/
	{ 157, 165 },		/* #yen		*/
	{ 158, 223 },		/* "s (sz)	*/
	{ 159, 131 },		/* #f		*/
	{ 160, 225 },		/* 'a		*/
	{ 161, 237 },		/* 'i		*/
	{ 162, 243 },		/* 'o		*/
	{ 163, 250 },		/* 'u		*/
	{ 164, 241 },		/* ~n		*/
	{ 165, 209 },		/* ~N		*/
	{ 166, 170 },		/* _a		*/
	{ 167, 186 },		/* _o		*/
	{ 168, 191 },		/* #?		*/
	{ 169, 0	},		/* #pos		*/
	{ 170, 172 },		/* #neg		*/
	{ 171, 189 },		/* #1/2		*/
	{ 172, 188 },		/* #1/4		*/
	{ 173, 161 },		/* #!		*/
	{ 174, 171 },		/* #<		*/
	{ 175, 187 },		/* #>		*/
	{ 176, 227 },		/* ~a		*/
	{ 177, 245 },		/* ~o		*/
	{ 178, 216 },		/* /O		*/
	{ 179, 248 },		/* /o		*/
	{ 180, 156 },		/* &oe		*/
	{ 181, 140 },		/* &OE		*/
	{ 182, 192 },		/* `A		*/
	{ 183, 195 },		/* ~A		*/
	{ 184, 213 },		/* ~O		*/
	{ 185, 168 },		/* #"		*/
	{ 186, 180 },		/* #'		*/
 	{ 187, 134 },		/* #dag		*/
	{ 188, 182 },		/* #p		*/
	{ 189, 169 },		/* #copy	*/
	{ 190, 174 },		/* #reg		*/
	{ 191, 153 },		/* #tm		*/
	{ 192, 0   },		/* ij-Lig	*/
	{ 193, 0   },		/* TOS: Arabisch */
	{ 194, 0   },		/* DOS: Grafik   */
	{ 195, 0   },		
	{ 196, 0   },		
	{ 197, 0   },		
	{ 198, 0   },		
	{ 199, 0   },		
	{ 200, 0   },		
	{ 201, 0   },		
	{ 202, 0   },		
	{ 203, 0   },		
	{ 204, 0   },		
	{ 205, 0   },		
	{ 206, 0   },		
	{ 207, 0   },		
	{ 208, 0   },		
	{ 209, 0   },		
	{ 210, 0   },		
	{ 211, 0   },		
	{ 212, 0   },		
	{ 213, 0   },		
	{ 214, 0   },		
	{ 215, 0   },		
	{ 216, 0   },		
	{ 217, 0   },		
	{ 218, 0   },		
	{ 219, 0   },		
	{ 220, 0   },		
	{ 221, 167 },		/* #sect	*/
	{ 222, '^' },		/* #circ	*/
	{ 223, 0   },		/* #infty	*/
	{ 224, 0   },		/* alpha	*/
	{ 225, 223 },		/* "s (sz)	*/
	{ 226, 0   },		/* Gamma	*/
	{ 227, 0   },		/* pi		*/
	{ 228, 0   },		/* Sigma	*/
	{ 229, 0   },		/* sigma	*/
	{ 230, 181 },		/* #mu		*/
	{ 231, 0   },		/* tau		*/
	{ 232, 0   },		/* Phi		*/
	{ 233, 0   },		/* teta		*/
	{ 234, 0   },		/* Omega	*/
	{ 235, 0   },		/* delta	*/
	{ 236, 0   },		/* ???		*/
	{ 237, 0   },		/* phi		*/
	{ 238, 0   },		/* Epsilon	*/
	{ 239, 0   },		/* eta		*/
	{ 240, 0   },		/* equiv	*/
	{ 241, 177 },		/* #pm		*/
	{ 242, 0   },		/* >=		*/
	{ 243, 0   },		/* <=		*/
	{ 244, 0   },		/* integ-up	*/
	{ 245, 0   },		/* integ-lo	*/
	{ 246, 247 },		/* div		*/
	{ 247, 0   },		/* approx	*/
	{ 248, 176 },		/* #degree	*/
	{ 249, 149 },		/* #bullet	*/
	{ 250, 183 },		/* #cdot	*/
	{ 251, 0   },		/* Wurzel	*/
	{ 252, 0   },		/* ^n		*/
	{ 253, 178 },		/* #^2		*/
	{ 254, 179 },		/* #^3		*/
	{ 255, 0   },		/* EOF		*/
};


#endif	/* __TOS2ISO__ */

