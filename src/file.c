/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : file.c
*  Symbol prefix: file
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
*  Description  : ???
*
*-------------------------------------------------------------------------------
*
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Martin Osieka (MO)
*                 Volker Jansen (vj)
*                 Ulf Dunkel (fd)
*                 Gerhard Stoll (ggs)
*  Write access : fd, ggs
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
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*    fd  Feb 22: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 25: myTextGetline() no longer concatenates '!\' lines in ENV_VERBATIM
*    ggs Mar 13: Delete # in line 49
*  2011:
*    fd  Feb 21: more reformatting done
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "udoport.h"
#include "version.h"
#include "str.h"
#include "udo_type.h"
#include "msg.h"
#include "udomem.h"
#if USE_HTML_FOLDERS
#ifdef __WIN32__
#include <direct.h>
#endif
#endif

#include "export.h"
#include "file.h"


static FILELIST *filelist;

static FILE_ID last_fileid;


/*******************************************************************************
*
*     FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  myTextOpen():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL MYTEXTFILE *myTextOpen(const char *filename)
{
	MYTEXTFILE *tf;

	tf = (MYTEXTFILE *) malloc(sizeof(*tf));

	if (tf == NULL)
		return NULL;

	memset(tf, 0, sizeof(*tf));

	/* Auf normale Routine zurueckgreifen */
	tf->file = fopen(filename, "rb");

	if (tf->file == NULL)
	{
		free(tf);
		tf = NULL;
	}

	return tf;
}





/*******************************************************************************
*
*	myTextGetline():
*		??? (description missing)
*
*	Return:
*		???
*
******************************************|************************************/

GLOBAL _BOOL myTextGetline(char *string, size_t n, MYTEXTFILE * tf)
{
	size_t sl;
	_BOOL cont;
	int c;

	/* This indicates how many lines have been added with \! to the current line */
	/* 0 = Es wurden keine Zeilen zusammengefuegt, */
	/* 1 = Es wurde eine Zeile angehaengt */
	/* 2 = Es wurden zwei Zeilen angehaengt, ... */
	uiMultiLines = -1;

	/*
	 * this used to call fgets(), but that doesnt work if
	 * we try i.e. to read a file with CR endings only on Unix,
	 * the fgets would read to the limit because there is no '\n'
	 */
	n--;
	do
	{
		cont = FALSE;
		sl = 0;
		for (;;)
		{
			if (sl == n)
				break;
			c = getc(tf->file);

			if (c == EOF)
			{
				if (sl == 0 && uiMultiLines == -1)
					return FALSE;
				break;
			}
			if (c == 0x0d)
			{
				c = getc(tf->file);
				if (c != 0x0a)
					ungetc(c, tf->file);
				break;
			}
			if (c == 0x0a)
				break;
			string[sl++] = c;
		}
		string[sl] = '\0';
		uiMultiLines++;
		/* Is there a continue line mark before linebreak? */
		if (sl >= 2 && string[sl - 2] == '!' && string[sl - 1] == '\\')
		{
			sl = sl - 2;				/* String got shorter */
			string[sl] = '\0';			/* Cut continue line! */
			/* Above n is used to indicate how much space is left and string is the buffer start */
			/* The new buffer is n minus the string we currently have */
			n = n - sl;
			/* So this is the new buffer start */
			string = string + sl;
			cont = TRUE;
		}
	} while (cont);

	return TRUE;
}





/*******************************************************************************
*
*	myTextClose():
*		??? (description missing)
*
*	Return:
*		???
*
******************************************|************************************/

GLOBAL _BOOL myTextClose(MYTEXTFILE * tf)
{
	if (tf == NULL)
		return FALSE;

	if (tf->buffer != NULL)
		free(tf->buffer);

	fclose(tf->file);
	free(tf);

	return TRUE;
}




#ifndef __MACOS__
/*******************************************************************************
*
*	strmir():
*		Spiegelt einen String
*
*	Return:
*		???
*
******************************************|************************************/

LOCAL char *strmir(char *s)
{
	size_t sl, i;
	char swap;

	if ((sl = strlen(s)) > 0)
	{
		for (i = 0; i < sl / 2; i++)
		{
			swap = s[i];
			s[i] = s[sl - i - 1];
			s[sl - i - 1] = swap;
		}
	}

	return s;
}




/*******************************************************************************
*
*	fsplit():
*		Zerpflueckt einen Zugriffspfad in seine Bestandteile
*
*	Notes:
*		Uebergabe:	 s:			Zugriffspfad (z.B. "C:\GEMINI2\HOME\MUPFEL.RC");
*		Rueckgabe:	 drive:		"C:"
*						 path:		"\GEMINI2\HOME\"
*						 filename:	"MUPFEL"
*						 suffix: 	".RC"
*
*	Return:
*		-
*
******************************************|************************************/

GLOBAL void fsplit(char *s, char *drive, char *path, char *filename, char *suffix)
{
	char wrk[MYFILE_FULL_LEN + 1];
	char *found;
	size_t wl, fl, l;

	strcpy(drive, "");
	strcpy(path, "");
	strcpy(filename, "");
	strcpy(suffix, "");

	strcpy(wrk, s);
	wl = strlen(wrk);

	if (wl == 0)
		return;

	strcpy(wrk, s);
	strmir(wrk);

	/* Drive ermitteln und abschneiden */
	if (wrk[wl - 2] == ':')
	{
		strcpy(drive, "a:");
		drive[0] = wrk[wl - 1];
		wrk[wl - 2] = EOS;
		wl = strlen(wrk);
	}

	/* Filenamen ermitteln und abschneiden */
	strcpy(filename, wrk);
	l = 0;
	while (filename[l] != EOS && filename[l] != '\\' && filename[l] != '/')
		l++;
	filename[l] = EOS;
	strmir(filename);
	fl = strlen(filename);
	strmir(wrk);
	wrk[wl - fl] = EOS;

	/* Jetzt noch aus dem Filenamen den Suffix extrahieren */
	if ((found = strrchr(filename, '.')) != NULL)
	{
		strcpy(suffix, found);
		filename[fl - strlen(suffix)] = EOS;
	}

	/* Das, was von <wrk> uebriggeblieben ist, ist der Pfad */
	strcpy(path, wrk);
}
#endif /* #ifndef __MACOS__ */





#ifdef __MACOS__
/*******************************************************************************
*
*	fsplit():
*		splits a file specification into its components (Mac version)
*
*	Note:
*		Mac version by Martin Osieka @ OF2, 1996-04-18:
*		----------------------------------------------------------------------
*		Zerlegt den Dateipfad <sour> in seine Bestandteile und liefert sie
*		im Macintosh-Format in den <dest...> Parametern zurueck.
*		Ein Macintosh-Dateipfad kann folgendermassen aufgebaut sein:
*	
*		Absoluter Pfad:							volume:folder1:...:folderN:name
*		Pfad relativ zum aktuellen Ordner:	:folderM:...:folderN:name
*		Datei im aktuellen Ordner: 			name
*	
*		D.h. sobald der Dateipfad mindestens einen ':'-Seperator enthaelt und 
*		dieser nicht am Pfadanfang steht, ist der erste Bestandteil des
*		Dateipfades ein volume-Name.
*		----------------------------------------------------------------------
*
*	Return:
*		-
*
******************************************|************************************/

GLOBAL void fsplit(const char *sour, char *destDrive, char *destFolders, char *destName, char *destSuffix)
{
	char *s;

	*destDrive = 0;
	*destFolders = 0;

	s = strrchr(sour, ':');
	if (s && (s != sour + 1))
	{
		/* Macintosh-Dateipfad (volume-Name wird nicht abgetrennt) */
		s += 1;
		strncpy(destFolders, sour, s - sour);
		destFolders[s - sour] = 0;
		sour = s;
	} else
	{
		/* DOS- oder Unix-Dateipfad */
		if (s)
		{
			strncpy(destDrive, sour, 2);
			destDrive[2] = 0;
			sour += 2;
		}

		s = strrchr(sour, '/');
		if (s)
		{
			if (sour[0] != '/')
			{
				*destFolders++ = ':';
			}
			s += 1;
			strncpy(destFolders, sour, s - sour);
			destFolders[s - sour] = 0;
			sour = s;
			s = destFolders;
			while ((s = strchr(s, '/')) != NULL)
			{
				*s++ = ':';
			}
		} else
		{
			s = strrchr(sour, '\\');
			if (s)
			{
				if (sour[0] != '\\')
				{
					*destFolders++ = ':';
				}
				s += 1;
				strncpy(destFolders, sour, s - sour);
				destFolders[s - sour] = 0;
				sour = s;
				s = destFolders;
				while ((s = strchr(s, '\\')) != NULL)
				{
					*s++ = ':';
				}
			}
		}
	}

	/* Dateinamen und -suffix aufspalten */
	s = strrchr(sour, '.');
	if (s)
	{
		strncpy(destName, sour, s - sour);
		destName[s - sour] = 0;
		strcpy(destSuffix, s);
	} else
	{
		strcpy(destName, sour);
		*destSuffix = 0;
	}
}
#endif /* #ifdef __MACOS__ */





/*******************************************************************************
*
*	myFwopen():
*		open a file in text write mode
*
*	Note:
*		Here we also set the file type for all systems which need a Creator type
*		(idea: Rainer Riedl). This avoids more queries in other modules and 
*		forgotten Creator types.
*
*		<filetype> is set in these formats:
*		- TOASC
*		- TOHTM
*		- TOGIF
*
*	Return:
*		???
*
******************************************|************************************/

GLOBAL FILE *myFwopen(const char *filename, const int filetype)
{
	FILE *file;

	file = fopen(filename, "w");

#if USE_SETFILETYPE
	if (file)
	{
		SetFileType(filename, filetype);
	}
#else
	UNUSED(filetype);
#endif

	return file;
}





/*******************************************************************************
*
*	myFwbopen():
*		open a file in binary write mode
*
*	Note:
*		see myFwopen()
*	Return:
*		???
*
******************************************|************************************/

GLOBAL FILE *myFwbopen(const char *filename, const int filetype)
{
	FILE *file;

	file = fopen(filename, "wb");

#if USE_SETFILETYPE
	if (file)
	{
		SetFileType(filename, filetype);
	}
#else
	UNUSED(filetype);
#endif

	return file;
}





/*******************************************************************************
*
*	path_adjust_separator():
*		adjust path separator character(s)
*
*	Return:
*		-
*
******************************************|************************************/

GLOBAL void path_adjust_separator(char *s)
{
#if USE_SLASH
	replace_char(s, '\\', '/');
#else
	replace_char(s, '/', '\\');
#endif
}





#if USE_HTML_FOLDERS
/*******************************************************************************
*
*	my_getcwd():
*		get current directory
*
*	Return:
*		FALSE: doesn't exist
*		 TRUE: success
*
******************************************|************************************/

LOCAL _BOOL my_getcwd(char *s, size_t maxlen)
{
	_BOOL ret = TRUE;

	if (getcwd(s, maxlen) == NULL)
		ret = FALSE;

	return ret;
}





/*******************************************************************************
*
*	myDirExists():
*		check whether a directory exists on file
*
*	Return:
*		FALSE: doesn't exist
*		 TRUE: success
*
******************************************|************************************/

LOCAL _BOOL myDirExists(const char *s)
{
	char old[MYFILE_FULL_LEN + 1];
	_BOOL ret = TRUE;

	my_getcwd(old, sizeof(old));

	if (chdir(s) != 0)
		ret = FALSE;

	chdir(old);

	return ret;
}





/*******************************************************************************
*
*	my_mkdir():
*		create a directory on file 
*
*	Return:
*		FALSE: error
*		 TRUE: success
*
******************************************|************************************/

GLOBAL _BOOL my_mkdir(const char *s)
{
	_BOOL ret = TRUE;

	if (!myDirExists(s))
	{
		if (mkdir(s, 0755) != 0)
		{
			ret = FALSE;
			error_mkdir(s);
		}
	}

	return ret;
}
#endif /* USE_HTML_FOLDERS */


FILE_ID file_listadd(const char *name)
{
	FILELIST *f;

	size_t len;

	if (name == NULL || *name == '\0')
	{
		return 0;
	}

	for (f = filelist; f != NULL; f = f->next)
		if (strcmp(f->name, name) == 0)
		{
			return f->id;
		}
	len = strlen(name);
	f = (FILELIST *) malloc(sizeof(*f) + len);
	if (f == NULL)
		return 0;
	++last_fileid;
	f->id = last_fileid;
	strcpy(f->name, name);
	f->next = filelist;
	filelist = f;
	return f->id;
}


const char *file_lookup(FILE_ID id)
{
	FILELIST *f;

	if (id != 0)
	{
		for (f = filelist; f != NULL; f = f->next)
			if (f->id == id)
			{
				return f->name;
			}
	}
	return "<no filename>";
}


void init_module_files(void)
{
	filelist = NULL;
	last_fileid = 0;
}


void exit_module_files(void)
{
	FILELIST *f, *next;

	for (f = filelist; f != NULL; f = next)
	{
		next = f->next;
		free(f);
	}
	filelist = NULL;
	last_fileid = 0;
}
