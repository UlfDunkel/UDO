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

#ifdef __MSDOS__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __WIN32__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __TOS__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __LINUX__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __SUNOS__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __NEXTSTEP__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __HPUX_ISO__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __HPUX_ROMAN8__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __AMIGA__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __SINIX__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __BEOS__
#endif

/*	--------------------------------------------------------------	*/

#ifdef __MACOS__
#define __AddLFToNL__ 0	/* solange es keinen HCP auf dem Mac gibt notwendig */
#endif

/*	--------------------------------------------------------------	*/

#ifdef __MACOSX__
#endif

/*	--------------------------------------------------------------	*/

#ifndef UNUSED
#define UNUSED(x) if (x) {}
#endif

#ifndef __GNUC__
#  define __attribute__(x)
#endif

#endif	/* PORTAB_H */
