/*	##################################################
	# @(#) version.h
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
	# Compiler- und systemabhaengige Defines setzen
	##################################################	*/

#ifndef VERSION_H
#define	VERSION_H

/*	------------------------------------------------------------
	Einige Flags um Neuentwicklungen zu (de)aktivieren
	------------------------------------------------------------	*/
#define	USE_HTML_FOLDERS		0	/* Ordnerstruktur erzeugen?				*/
#define	USE_OLD_BUILD_FILE		1	/* build_search_file() benutzen?		*/
#define	USE_MYTEXTFILE			0	/* Eigene Dateiroutinen benutzen?		*/


/*	------------------------------------------------------------
	Debugging-Flags
	------------------------------------------------------------	*/
#define	CHECK_REPLACE_LEN		0	/* qreplace*() checken? */


/*	------------------------------------------------------------
	Release-Nummer und Patchlevel setzen
	------------------------------------------------------------	*/
#define	UDO_REL		"6"
#define UDO_SUBVER	"5"
#define	UDO_PL		"0"
#define	UDO_URL		"http://www.udo-open-source.org"
#define	UDO_MADE	"Made with UDO"

/*	------------------------------------------------------------
	Copyright Meldung
	------------------------------------------------------------	*/
#define	COPYRIGHT	"Copyright (c) 1995-2001 by Dirk Hagedorn\nCopyright (c) 2001-2004 by The UDO community"
#define UDO_COPYRIGHT_TEXT "Copyright (!copyright) 1995-2001 by Dirk Hagedorn\t(!nl)\nCopyright (!copyright) 2001-2004 by The UDO community\t(!nl)\n"

/*	------------------------------------------------------------
	Zeichensaetze
	------------------------------------------------------------	*/
#define	CODE_LAT1		0		/* ISO Latin 1						*/
#define	CODE_DOS			1		/* IBM PC							*/
#define	CODE_437			1		/* DOS Codepage 437 (wie IBM PC)	*/
#define	CODE_TOS			2		/* Atari ST							*/
#define CODE_HP8			3		/* HP-Roman-8						*/
#define	CODE_MAC			4		/* Apple Macintosh					*/
#define	CODE_NEXT		5		/* NextSTep							*/
#define	CODE_850			6		/* DOS Codepage 850					*/
#define	CODE_UTF8		7		/* UTF-8 (BeOS)						*/

/*	------------------------------------------------------------
	Compiler- und system abhaengige Dinge setzen
	------------------------------------------------------------	*/
#ifdef __TOS__
#define	UDO_OS					"TOS"
#define	USE_SLASH				0
#define	USE_LONG_FILENAMES	0
#define	USE_LATIN1_CHARSET	0
#define	SYSTEM_CHARSET			CODE_TOS
#define	HAVE_STRUPR				1
#define	HAVE_STRLWR				1
#define	HAVE_STRICMP			1
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		0
#define	HAVE_SYS_ERRLIST		1
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				0
#endif

#ifdef __MSDOS__
#define	UDO_OS					"DOS"
#define	USE_SLASH				0
#define	USE_LONG_FILENAMES	0
#define	USE_LATIN1_CHARSET	0
#define	SYSTEM_CHARSET			CODE_437
#define	HAVE_STRUPR				1
#define	HAVE_STRLWR				1
#define	HAVE_STRICMP			1
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		0
#define	HAVE_SYS_ERRLIST		1
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __MSDOS850__
#define	UDO_OS					"DOS"
#define	USE_SLASH				0
#define	USE_LONG_FILENAMES	0
#define	USE_LATIN1_CHARSET	0
#define	SYSTEM_CHARSET			CODE_850
#define	HAVE_STRUPR				1
#define	HAVE_STRLWR				1
#define	HAVE_STRICMP			1
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		0
#define	HAVE_SYS_ERRLIST		1
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __WIN32__
#define	UDO_OS					"Win32"
#define	USE_SLASH				0
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	1
#define	SYSTEM_CHARSET			CODE_LAT1
#define	HAVE_STRUPR				1
#define	HAVE_STRLWR				1
#define	HAVE_STRICMP			1
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		0
#define	HAVE_SYS_ERRLIST		1
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __LINUX__
#define	UDO_OS					"Linux"
#define	USE_SLASH				1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	1
#define	SYSTEM_CHARSET			CODE_LAT1
#define	HAVE_STRUPR				0
#define	HAVE_STRLWR				0
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			0
#define	HAVE_STRCASECMP		1
#define	HAVE_SYS_ERRLIST		1
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __AMIGA__
#define	UDO_OS					"Amiga"
#define	USE_SLASH				1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	1
#define	SYSTEM_CHARSET			CODE_LAT1
#define	HAVE_STRUPR				0
#define	HAVE_STRLWR				0
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		1
#define	HAVE_SYS_ERRLIST		1
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __SINIX__
#define	UDO_OS					"Sinix"
#define	USE_SLASH				1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	1
#define	SYSTEM_CHARSET			CODE_LAT1
#define	HAVE_STRUPR				1
#define	HAVE_STRLWR				1
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		0
#define	HAVE_SYS_ERRLIST		0
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __SUNOS__
#define	UDO_OS					"SunOS"
#define	USE_SLASH				1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	1
#define	SYSTEM_CHARSET			CODE_LAT1
#define	HAVE_STRUPR				0
#define	HAVE_STRLWR				0
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		0
#define	HAVE_SYS_ERRLIST		1
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __IRIX__
#define	UDO_OS					"IRIX"
#define	USE_SLASH				1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	1
#define	SYSTEM_CHARSET			CODE_LAT1
#define	HAVE_STRUPR				0
#define	HAVE_STRLWR				0
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		1
#define	HAVE_SYS_ERRLIST		1
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __HPUX_ISO__
#define	UDO_OS					"HP-UX"
#define	USE_SLASH				1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	1
#define	SYSTEM_CHARSET			CODE_LAT1
#define	HAVE_STRUPR				1
#define	HAVE_STRLWR				0
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		1
#define	HAVE_SYS_ERRLIST		0
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __HPUX_ROMAN8__
#define	UDO_OS					"HP-UX"
#define	USE_SLASH				1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	0
#define	SYSTEM_CHARSET			CODE_HP8
#define	HAVE_STRUPR				1
#define	HAVE_STRLWR				1
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		1
#define	HAVE_SYS_ERRLIST		0
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __MACOS__
#define	UDO_OS					"MacOS"
#define	USE_SLASH				0
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	0
#define	SYSTEM_CHARSET			CODE_MAC
#define	HAVE_STRUPR				0
#define	HAVE_STRLWR				0
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		0
#define	HAVE_SYS_ERRLIST		0
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		1
#define	HAVE_TMPNAM				1
#endif

#ifdef __MACOSX__
#define	UDO_OS			"MacOSX"
#define	USE_SLASH			1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	0
#define	SYSTEM_CHARSET		CODE_MAC
#define	HAVE_STRUPR			0
#define	HAVE_STRLWR			0
#define	HAVE_STRICMP		0
#define	HAVE_STRNICMP			0
#define	HAVE_STRCASECMP		1
#define	HAVE_SYS_ERRLIST	1
#define	HAVE_STRERROR		1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __NEXTSTEP__
#define	UDO_OS					"NeXTStep"
#define	USE_SLASH				1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	0
#define	SYSTEM_CHARSET			CODE_NEXT
#define	HAVE_STRUPR				1
#define	HAVE_STRLWR				1
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		0
#define	HAVE_SYS_ERRLIST		1
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		0
#define	HAVE_TMPNAM				1
#endif

#ifdef __BEOS__
#define	UDO_OS					"BeOS"
#define	USE_SLASH				1
#define	USE_LONG_FILENAMES	1
#define	USE_LATIN1_CHARSET	0
#define	SYSTEM_CHARSET			CODE_UTF8
#define	HAVE_STRUPR				0
#define	HAVE_STRLWR				0
#define	HAVE_STRICMP			0
#define	HAVE_STRNICMP			1
#define	HAVE_STRCASECMP		0
#define	HAVE_SYS_ERRLIST		0
#define	HAVE_STRERROR			1
#define	USE_SETFILETYPE		1
#define	HAVE_TMPNAM				1
#endif

#endif	/* VERSION_H */


/*	------------------------------------------------------------
	Definitionen testen und ggf. abbrechen, falls etwas nicht
	angelegt wurde.
	------------------------------------------------------------	*/
#ifndef	UDO_OS
#error	"UDO_OS not defined!"
#endif

#ifndef	USE_SLASH
#error	"USE_SLASH not defined!"
#endif

#ifndef	USE_LONG_FILENAMES
#error	"USE_LONG_FILENAMES not defined!"
#endif

#ifndef	USE_LATIN1_CHARSET
#error	"USE_LATIN1_CHARSET not defined!"
#endif

#ifndef	SYSTEM_CHARSET
#error	"SYSTEM_CHARSET not defined!"
#endif

#ifndef	HAVE_STRUPR
#error	"HAVE_STRUPR not defined!"
#endif

#ifndef	HAVE_STRLWR
#error	"HAVE_STRLWR not defined!"
#endif

#ifndef	HAVE_STRICMP
#error	"HAVE_STRICMP not defined!"
#endif

#ifndef	HAVE_STRNICMP
#error	"HAVE_STRNICMP not defined!"
#endif

#ifndef	HAVE_STRCASECMP
#error	"HAVE_STRCASECMP not defined!"
#endif

#ifndef	HAVE_SYS_ERRLIST
#error	"HAVE_SYS_ERRLIST not defined!"
#endif

#ifndef	HAVE_STRERROR
#error	"HAVE_STRERROR not defined!"
#endif

#ifndef	USE_SETFILETYPE
#error	"USE_SETFILETYPE not defined!"
#endif

#ifndef	HAVE_TMPNAM
#error	"HAVE_TMPNAM not defined!"
#endif
