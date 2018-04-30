/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : file.h
*  Symbol prefix: file
*
*  Description  : ???
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
*  Co-Authors   : Gerhard Stoll (ggs), Ulf Dunkel
*  Write access : ggs, fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 22: header adjusted
*
******************************************|************************************/

#ifndef __UDOFILE__
#define __UDOFILE__

#include "version.h"
#include "udo_type.h"

/* ############################################################
   # Typen
   ############################################################   */
typedef struct _mytextfile
{
   FILE   *file;
   char   *buffer;
}  MYTEXTFILE;

/* ############################################################
   # Globale Routinen
   ############################################################   */

GLOBAL int uiMultiLines;          /* Anzahl zusammengefuegter Zeilen (0=nicht zusammengefuegt, 1=eine Zeile angehaengt) */

void init_module_files(void);
void exit_module_files(void);


GLOBAL MYTEXTFILE *myTextOpen ( const char *filename );
GLOBAL _BOOL myTextGetline ( char *string, size_t n, MYTEXTFILE *tf );
GLOBAL _BOOL myTextClose ( MYTEXTFILE *tf );


#ifndef __MACOS__
GLOBAL void fsplit (char *s, char *drive, char *path, char *filename, char*suffix);
#else
GLOBAL void fsplit( const char *sour, char *destDrive, char *destFolders, char *destName, char *destSuffix);
#endif /* __MACOS__ */

GLOBAL FILE * myFwopen ( const char *filename, const int filetype );
GLOBAL FILE * myFwbopen ( const char *filename, const int filetype );

GLOBAL void path_adjust_separator(char *s);

FILE_ID file_listadd(const char *name);
const char *file_lookup(FILE_ID id);


#if USE_HTML_FOLDERS

GLOBAL _BOOL my_mkdir(const char *s);

#endif /* USE_HTML_FOLDERS */

/* ##############################################################
   # MO: Funktion zum Setzen von Dateityp und -creator.
   # Uebergeben werden die von UDO definierten Kennungen fuer die
   # verschiedenen Dateiformate.
   ##############################################################   */

#if USE_SETFILETYPE
extern void SetFileType( const char *fileName, int fileKind);
#else
#define SetFileType( fileName, fileKind)
#endif


#endif /* __UDOFILE__ */
