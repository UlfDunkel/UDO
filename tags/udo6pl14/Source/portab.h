/*	##############################################################
	# @(#) portab.h
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
	##############################################################	*/

#ifndef PORTAB_H
#define	PORTAB_H

/*	--------------------------------------------------------------	*/

#ifndef TRUE
#define	TRUE	1
#define	FALSE	0
#endif

#define	BOOLEAN	int
#define	UCHAR	unsigned char
#define	UINT	unsigned int

#define	EOS		'\0'

#define	LOCAL	static


/*	--------------------------------------------------------------	*/

#ifdef	__BORLANDC__
#define	FAR		far
#define	NEAR	near
#define	HUGE	huge
#else
#define	FAR
#define	NEAR
#define	HUGE
#endif

/*	--------------------------------------------------------------	*/

#ifdef __MSDOS__
	#ifndef WORD
	#define	WORD	short
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned short
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef WIN32
	#ifndef WORD
	#define	WORD	short
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned short
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __TOS__
	#ifndef WORD
	#define WORD	int
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned short
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __LINUX__
	#ifndef WORD
	#define WORD	int
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned int
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __SUNOS__
	#ifndef WORD
	#define WORD	int
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned int
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __NEXTSTEP__
	#ifndef WORD
	#define WORD	int
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned int
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __HPUX_ISO__
	#ifndef WORD
	#define WORD	int
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned int
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __HPUX_ROMAN8__
	#ifndef WORD
	#define WORD	int
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned int
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __AMIGA__
	#ifndef WORD
	#define WORD	int
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned int
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __SINIX__
	#ifndef WORD
	#define WORD	int
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned int
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __BEOS__
	#ifndef WORD
	#define WORD	int
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned int
	#endif
#endif

/*	--------------------------------------------------------------	*/

#ifdef __MACOS__
	#ifndef WORD
	#define WORD	short
	#endif
	#ifndef UWORD
	#define	UWORD	unsigned short
	#endif

	#define __SHAREWARE__ 0
	#define __AddLFToNL__ 0	/* solange es keinen HCP auf dem Mac gibt notwendig */
#endif

/*	--------------------------------------------------------------	*/

#ifndef	WORD
#error	"WORD not defined in portab.h!"
#endif

#ifndef	UWORD
#error	"UWORD not defined in portab.h!"
#endif

/*	--------------------------------------------------------------	*/

#endif	/* PORTAB_H */

