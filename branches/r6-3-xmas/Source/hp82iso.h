/*	############################################################
	# @(#) hp82iso.h
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
	# @(#) Uebersetzungstabellen von HP-Roman-8 nach ISO-Latin-1
	############################################################	*/

#ifndef __HP82ISO__
#define __HP82ISO__

#ifndef ID_HP82ISO_H
#define	ID_HP82ISO_H
const char *id_hp82iso_h= "@(#) hp82iso.h   26.06.1996";
#endif


typedef struct _hp82iso
{	unsigned char	hp8;
	unsigned char	iso;
}	HP82ISO;


LOCAL const HP82ISO hp82iso_item[128]=
{
	{ 128, 0   },
	{ 129, 0   },

	{ 130, 0   },
	{ 131, 0   },
	{ 132, 0   },
	{ 133, 0   },
	{ 134, 0   },
	{ 135, 0   },
	{ 136, 0   },
	{ 137, 0   },
	{ 138, 0   },
	{ 139, 0   },

	{ 140, 0   },
	{ 141, 0   },
	{ 142, 0   },
	{ 143, 0   },
	{ 144, 0   },
	{ 145, 0   },
	{ 146, 0   },
	{ 147, 0   },
	{ 148, 0   },
	{ 149, 0   },

	{ 150, 0   },
	{ 151, 0   },
	{ 152, 0   },
	{ 153, 0   },
	{ 154, 0   },
	{ 155, 0   },
	{ 156, 0   },
	{ 157, 0   },
	{ 158, 0   },
	{ 159, 0   },

	{ 160, 0   },		/* null		*/
	{ 161, 192 },		/* `A		*/
	{ 162, 194 },		/* ^A		*/
	{ 163, 200 },		/* `E		*/
	{ 164, 202 },		/* ^E		*/
	{ 165, 203 },		/* "E		*/
	{ 166, 206 },		/* ^I		*/
	{ 167, 207 },		/* "I		*/
	{ 168, 180 },		/* #'		*/
	{ 169, 0   },		/* #`		*/

	{ 170, 0   },		/* #circ	*/
	{ 171, 168 },		/* #"		*/
	{ 172, 152 },		/* !~		*/
	{ 173, 217 },		/* `U		*/
	{ 174, 219 },		/* ^U		*/
	{ 175, 0   },		/* ???		*/
	{ 176, 175 },		/* upline	*/
	{ 177, 221 },		/* 'Y		*/
	{ 178, 253 },		/* 'y		*/
	{ 179, 176 },		/* #degree	*/

	{ 180, 199 },		/* ,C		*/
	{ 181, 231 },		/* ,c		*/
	{ 182, 209 },		/* ~N		*/
	{ 183, 241 },		/* ~n		*/
	{ 184, 161 },		/* #!		*/
	{ 185, 191 },		/* #?		*/
	{ 186, 164 },		/* general currency	*/
	{ 187, 163 },		/* #pound	*/
	{ 188, 165 },		/* #yen		*/
	{ 189, 167 },		/* #sect	*/

	{ 190, 131 },		/* #f		*/
	{ 191, 162 },		/* #cent	*/
	{ 192, 226 },		/* ^a		*/
	{ 193, 234 },		/* ^e		*/
	{ 194, 244 },		/* ^o		*/
	{ 195, 251 },		/* ^u		*/
	{ 196, 225 },		/* 'a		*/
	{ 197, 233 },		/* 'e		*/
	{ 198, 243 },		/* 'o		*/
	{ 199, 250 },		/* 'u		*/

	{ 200, 224 },		/* `a		*/
	{ 201, 232 },		/* `e		*/
	{ 202, 242 },		/* `o		*/
	{ 203, 249 },		/* `u		*/
	{ 204, 228 },		/* "a		*/
	{ 205, 235 },		/* "e		*/
	{ 206, 246 },		/* "o		*/
	{ 207, 252 },		/* "u		*/
	{ 208, 197 },		/* .A		*/
	{ 209, 238 },		/* ^i		*/

	{ 210, 216 },		/* /O		*/
	{ 211, 198 },		/* &AE		*/
	{ 212, 229 },		/* .a		*/
	{ 213, 237 },		/* 'i		*/
	{ 214, 248 },		/* /o		*/
	{ 215, 230 },		/* &ae		*/
	{ 216, 196 },		/* "A		*/
	{ 217, 236 },		/* `i		*/
	{ 218, 214 },		/* "O		*/
	{ 219, 220 },		/* "U		*/

	{ 220, 201 },		/* 'E		*/
	{ 221, 239 },		/* "i		*/
	{ 222, 223 },		/* "s		*/
	{ 223, 212 },		/* ^O		*/
	{ 224, 193 },		/* 'A		*/
	{ 225, 195 },		/* ~A		*/
	{ 226, 227 },		/* ~a		*/
	{ 227, 208 },		/* -D		*/
	{ 228, 240 },		/* o|''		*/
	{ 229, 205 },		/* 'I		*/

	{ 230, 204 },		/* `I		*/
	{ 231, 211 },		/* 'O		*/
	{ 232, 210 },		/* `O		*/
	{ 233, 213 },		/* ~O		*/
	{ 234, 245 },		/* ~o		*/
	{ 235, 138 },		/* vS		*/
	{ 236, 154 },		/* vs		*/
	{ 237, 218 },		/* 'U		*/
	{ 238, 159 },		/* "Y		*/
	{ 239, 255 },		/* "y		*/

	{ 240, 222 },		/* |b		*/
	{ 241, 254 },		/* |B		*/
	{ 242, 149 },		/* #bullet	*/
	{ 243, 181 },		/* #mu		*/
	{ 244, 182 },		/* #p		*/
	{ 245, 190 },		/* #3/4		*/
	{ 246, 0   },		/* ????		*/
	{ 247, 188 },		/* #1/4		*/
	{ 248, 189 },		/* #1/2		*/
	{ 249, 170 },		/* _a		*/

	{ 250, 186 },		/* _o		*/
	{ 251, 171 },		/* #<		*/
	{ 252, 149 },		/* bullet	*/
	{ 253, 187 },		/* #>		*/
	{ 254, 177 },		/* #pm		*/
	{ 255, 0   },		/* null		*/
};

#endif /* __HP82ISO__ */

