/*	############################################################
	# @(#) utf82iso.h
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
	# @(#) Uebersetzungstabellen von UTF-8 nach ISO-Latin-1
	############################################################	*/

#ifndef	UTF82ISO_H
#define	UTF82ISO_H


#ifndef ID_UTF82ISO_H
#define	ID_UTF82ISO_H
const char *id_utf82iso_h= "@(#) utf82iso.h   01.01.1999";
#endif


typedef struct _utf82iso
{
	unsigned char	utf8[3];
	unsigned char	latin1;
}	UTF82ISO;


LOCAL const UTF82ISO utf82iso_item[128]=
{
	{ "\xC2\xA0", 160 },		/* &nbsp;	*/
	{ "\xC2\xA1", 161 },		/*	*/
	{ "\xC2\xA2", 162 },		/*	*/
	{ "\xC2\xA3", 163 },		/*	*/
	{ "\xC2\xA4", 164 },		/*	*/
	{ "\xC2\xA5", 165 },		/*	*/
	{ "\xC2\xA6", 166 },		/*	*/
	{ "\xC2\xA7", 167 },		/*	*/
	{ "\xC2\xA8", 168 },		/*	*/
	{ "\xC2\xA9", 169 },		/*	*/
	{ "\xC2\xAA", 170 },		/*	*/
	{ "\xC2\xAB", 171 },		/*	*/
	{ "\xC2\xAC", 172 },		/*	*/
	{ "\xC2\xAD", 173 },		/*	*/
	{ "\xC2\xAE", 174 },		/*	*/
	{ "\xC2\xAF", 175 },		/*	*/

	{ "\xC2\xB0", 176 },		/* 	*/
	{ "\xC2\xB1", 177 },		/* 	*/
	{ "\xC2\xB2", 178 },		/* 	*/
	{ "\xC2\xB3", 179 },		/* 	*/
	{ "\xC2\xB4", 180 },		/* 	*/
	{ "\xC2\xB5", 181 },		/* 	*/
	{ "\xC2\xB6", 182 },		/* 	*/
	{ "\xC2\xB7", 183 },		/* 	*/
	{ "\xC2\xB8", 184 },		/* 	*/
	{ "\xC2\xB9", 185 },		/* 	*/
	{ "\xC2\xBA", 186 },		/* 	*/
	{ "\xC2\xBB", 187 },		/* 	*/
	{ "\xC2\xBC", 188 },		/* 	*/
	{ "\xC2\xBD", 189 },		/* 	*/
	{ "\xC2\xBE", 190 },		/* 	*/
	{ "\xC2\xBF", 191 },		/* 	*/

	{ "\xC3\x80", 192 },		/* 	*/
	{ "\xC3\x81", 193 },		/* 	*/
	{ "\xC3\x82", 194 },		/* 	*/
	{ "\xC3\x83", 195 },		/* 	*/
	{ "\xC3\x84", 196 },		/* 	*/
	{ "\xC3\x85", 197 },		/* 	*/
	{ "\xC3\x86", 198 },		/* 	*/
	{ "\xC3\x87", 199 },		/* 	*/
	{ "\xC3\x88", 200 },		/* 	*/
	{ "\xC3\x89", 201 },		/* 	*/
	{ "\xC3\x8A", 202 },		/* 	*/
	{ "\xC3\x8B", 203 },		/* 	*/
	{ "\xC3\x8C", 204 },		/* 	*/
	{ "\xC3\x8D", 205 },		/* 	*/
	{ "\xC3\x8E", 206 },		/* 	*/
	{ "\xC3\x8F", 207 },		/* 	*/

	{ "\xC3\x90", 208 },		/* 	*/
	{ "\xC3\x91", 209 },		/* 	*/
	{ "\xC3\x92", 210 },		/* 	*/
	{ "\xC3\x93", 211 },		/* 	*/
	{ "\xC3\x94", 212 },		/* 	*/
	{ "\xC3\x95", 213 },		/* 	*/
	{ "\xC3\x96", 214 },		/* 	*/
	{ "\xC3\x97", 215 },		/* 	*/
	{ "\xC3\x98", 216 },		/* 	*/
	{ "\xC3\x99", 217 },		/* 	*/
	{ "\xC3\x9A", 218 },		/* 	*/
	{ "\xC3\x9B", 219 },		/* 	*/
	{ "\xC3\x9C", 220 },		/* 	*/
	{ "\xC3\x9D", 221 },		/* 	*/
	{ "\xC3\x9E", 222 },		/* 	*/
	{ "\xC3\x9F", 223 },		/* 	*/

	{ "\xC3\xA0", 224 },		/* 	*/
	{ "\xC3\xA1", 225 },		/* 	*/
	{ "\xC3\xA2", 226 },		/* 	*/
	{ "\xC3\xA3", 227 },		/* 	*/
	{ "\xC3\xA4", 228 },		/* 	*/
	{ "\xC3\xA5", 229 },		/* 	*/
	{ "\xC3\xA6", 230 },		/* 	*/
	{ "\xC3\xA7", 231 },		/* 	*/
	{ "\xC3\xA8", 232 },		/* 	*/
	{ "\xC3\xA9", 233 },		/* 	*/
	{ "\xC3\xAA", 234 },		/* 	*/
	{ "\xC3\xAB", 235 },		/* 	*/
	{ "\xC3\xAC", 236 },		/* 	*/
	{ "\xC3\xAD", 237 },		/* 	*/
	{ "\xC3\xAE", 238 },		/* 	*/
	{ "\xC3\xAF", 239 },		/* 	*/

	{ "\xC3\xB0", 240 },		/* 	*/
	{ "\xC3\xB1", 241 },		/* 	*/
	{ "\xC3\xB2", 242 },		/* 	*/
	{ "\xC3\xB3", 243 },		/* 	*/
	{ "\xC3\xB4", 244 },		/* 	*/
	{ "\xC3\xB5", 245 },		/* 	*/
	{ "\xC3\xB6", 246 },		/* 	*/
	{ "\xC3\xB7", 247 },		/* 	*/
	{ "\xC3\xB8", 248 },		/* 	*/
	{ "\xC3\xB9", 249 },		/* 	*/
	{ "\xC3\xBA", 250 },		/* 	*/
	{ "\xC3\xBB", 251 },		/* 	*/
	{ "\xC3\xBC", 252 },		/* 	*/
	{ "\xC3\xBD", 253 },		/* 	*/
	{ "\xC3\xBE", 254 },		/* 	*/
	{ "\xC3\xBF", 255 },		/* 	*/
};


#endif	/* UTF82ISO_H */

