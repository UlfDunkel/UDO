/*	############################################################
	# @(#) file.h
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
	############################################################	*/

#ifndef __UDOFILE__
#define	__UDOFILE__

#include "version.h"
#include "udo_type.h"

/*	############################################################
	# Typen
	############################################################	*/
typedef struct _mytextfile
{
	FILE	*file;
	fpos_t	filelen;
	char	*buffer;
	char	*bufptr;
	char	*bufend;
}	MYTEXTFILE;


/*	############################################################
	# Globale Routinen
	############################################################	*/

GLOBAL MYTEXTFILE *myTextOpen ( const char *filename );
GLOBAL char *myTextGetline ( char *string, int n, MYTEXTFILE *tf );
GLOBAL int myTextClose ( MYTEXTFILE *tf );


#ifndef __MACOS__
GLOBAL void fsplit (char *s, char *drive, char *path, char *filename, char*suffix);
#else
GLOBAL void fsplit( const char *sour, char *destDrive, char *destFolders, char *destName, char *destSuffix);
#endif /* __MACOS__ */

GLOBAL FILE * myFwopen ( const char *filename, const int filetype );
GLOBAL FILE * myFwbopen ( const char *filename, const int filetype );

GLOBAL MYFILE *my_fopen ( const char *filename, const char *mode );
GLOBAL BOOLEAN my_fclose ( MYFILE *myfile );

GLOBAL void path_adjust_separator ( char *s );


#if USE_HTML_FOLDERS

GLOBAL BOOLEAN my_mkdir ( char *s );

#endif /* USE_HTML_FOLDERS */

/*	##############################################################
	# MO: Funktion zum Setzen von Dateityp und -creator.
	# Uebergeben werden die von UDO definierten Kennungen fuer die
	# verschiedenen Dateiformate.
	##############################################################	*/

#if USE_SETFILETYPE
extern void SetFileType( const char *fileName, int fileKind);
#else
#define SetFileType( fileName, fileKind)
#endif


#endif /* __UDOFILE__ */