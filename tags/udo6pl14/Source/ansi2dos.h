/*	############################################################
	# @(#) ansi2dos.h
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
	# @(#) Uebersetzungstabellen von Windows-ANSI nach DOS
	# basierend auf tos2iso.h
	############################################################	*/

#ifndef	__ANSI2DOS__
#define	__ANSI2DOS__


#ifndef ID_ANSI2DOS_H
#define	ID_ANSI2DOS_H
const char *id_ansi2dos_h= "@(#) ansi2dos.h  14.10.1996";
#endif


typedef struct
{
	unsigned char	ansi;
	unsigned char	dos;
}	ANSI2DOS;


LOCAL const ANSI2DOS ansi2dos_item[128]=
{
	{ 128, 000 },
	{ 129, 000 },
	{ 130, 000 },
	{ 131, 159 },		/* #f		*/
	{ 132, 000 },
	{ 133, 000 },
 	{ 134, 187 },		/* #dag		*/
	{ 135, 000 },
	{ 136, 222 },		/* #circ	*/
	{ 137, 000 },
	{ 138, 000 },
	{ 139, 000 },
	{ 140, 181 },		/* &OE		*/
	{ 141, 000 },
	{ 142, 000 },
	{ 143, 000 },
	{ 144, 000 },
	{ 145, 000 },
	{ 146, 000 },
	{ 147, 000 },
	{ 148, 000 },
	{ 149, 249 },		/* #bullet	*/
	{ 150, 000 },
	{ 151, 000 },
	{ 152, 000 },
	{ 153, 191 },		/* #tm		*/
	{ 154, 000 },
	{ 155, 000 },
	{ 156, 180 },		/* &oe		*/
	{ 157, 000 },
	{ 158, 000 },
	{ 159, 000 },
	{ 160, 000 },
	{ 161, 173 },		/* #!		*/
	{ 162, 155 },		/* #cent	*/
	{ 163, 156 },		/* #pound	*/
	{ 164, 000 },
	{ 165, 157 },		/* #yen		*/
	{ 166, 000 },
	{ 167, 221 },		/* #sect	*/
	{ 168, 185 },		/* #"		*/
	{ 169, 189 },		/* #copy	*/
	{ 170, 166 },		/* _a		*/
	{ 171, 174 },		/* #<		*/
	{ 172, 170 },		/* #neg		*/
	{ 173, 000 },
	{ 174, 190 },		/* #reg		*/
	{ 175, 000 },
	{ 176, 248 },		/* #degree	*/
	{ 177, 241 },		/* #pm		*/
	{ 178, 253 },		/* #^2		*/
	{ 179, 254 },		/* #^3		*/
	{ 180, 186 },		/* #'		*/
	{ 181, 230 },		/* #mu		*/
	{ 182, 188 },		/* #p		*/
	{ 183, 250 },		/* #cdot	*/
	{ 184, 000 },
	{ 185, 000 },
	{ 186, 167 },		/* _o		*/
	{ 187, 175 },		/* #>		*/
	{ 188, 172 },		/* #1/4		*/
	{ 189, 171 },		/* #1/2		*/
	{ 190, 000 },
	{ 191, 168 },		/* #?		*/
	{ 192, 182 },		/* `A		*/
	{ 193, 000 },
	{ 194, 000 },
	{ 195, 183 },		/* ~A		*/
	{ 196, 142 },		/* "A		*/
	{ 197, 143 },		/* .A		*/
	{ 198, 146 },		/* &AE		*/
	{ 199, 128 },		/* ,C		*/
	{ 200, 000 },
	{ 201, 144 },		/* 'E		*/
	{ 202, 000 },
	{ 203, 000 },
	{ 204, 000 },
	{ 205, 000 },
	{ 206, 000 },
	{ 207, 000 },
	{ 208, 000 },
	{ 209, 165 },		/* ~N		*/
	{ 210, 000 },
	{ 211, 000 },
	{ 212, 000 },
	{ 213, 184 },		/* ~O		*/
	{ 214, 153 },		/* "O		*/
	{ 215, 000 },
	{ 216, 178 },		/* /O		*/
	{ 217, 000 },
	{ 218, 000 },
	{ 219, 000 },
	{ 220, 154 },		/* "U		*/
	{ 221, 000 },
	{ 222, 000 },
	{ 223, 225 },		/* "s (sz)	*/
	{ 224, 133 },		/* `a		*/
	{ 225, 160 },		/* 'a		*/
	{ 226, 131 },		/* ^a		*/
	{ 227, 176 },		/* ~a		*/
	{ 228, 132 },		/* "a		*/
	{ 229, 134 },		/* .a		*/
	{ 230, 145 },		/* &ae		*/
	{ 231, 135 },		/* ,c		*/
	{ 232, 138 },		/* `e		*/
	{ 233, 130 },		/* 'e		*/
	{ 234, 136 },		/* ^e		*/
	{ 235, 137 },		/* "e		*/
	{ 236, 141 },		/* `i		*/
	{ 237, 161 },		/* 'i		*/
	{ 238, 140 },		/* ^i		*/
	{ 239, 139 },		/* "i		*/
	{ 240, 000 },
	{ 241, 164 },		/* ~n		*/
	{ 242, 149 },		/* `o		*/
	{ 243, 162 },		/* 'o		*/
	{ 244, 147 },		/* ^o		*/
	{ 245, 177 },		/* ~o		*/
	{ 246, 148 },		/* "o		*/
	{ 247, 246 },		/* div		*/
	{ 248, 179 },		/* /o		*/
	{ 249, 151 },		/* `u		*/
	{ 250, 163 },		/* 'u		*/
	{ 251, 150 },		/* ^u		*/
	{ 252, 129 },		/* "u		*/
	{ 253, 000 },
	{ 254, 000 },
	{ 255, 152 },		/* "y		*/
};


#endif	/* __ANSI2DOS__ */

