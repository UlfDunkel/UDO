/*	#################################################################
	# @(#) file.c
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
	#################################################################	*/
#include	"import.h"
#include	<stdio.h>	
#include	<string.h>	
#include	<stdlib.h>	
#if USE_HTML_FOLDERS
#ifdef __WIN32__
#include	<direct.h>
#endif
#endif
#include	"portab.h"
#include	"version.h"
#include	"str.h"
#include	"msg.h"

#include	"export.h"
#include	"file.h"
#include	"udo_type.h"
#include        "udomem.h"

#ifndef ID_FSPLIT_C
#define	ID_FSPLIT_C
const char *id_fsplit_c= "@(#) file.c      02.09.1998";
#endif


LOCAL char *strmir ( char *s );

/*	#################################################################
	#
	# Funktionen zum Lesen von Textdateien
	#
	#################################################################	*/
GLOBAL MYTEXTFILE *myTextOpen ( const char *filename )
{
	MYTEXTFILE *tf;

	tf= (MYTEXTFILE *) um_malloc (sizeof(*tf));

	if (tf == NULL)
	{
		return NULL;
	}

	memset(tf, 0, sizeof(*tf));

#if USE_MYTEXTFILE
	tf->file= fopen(filename, "rb");

	if (tf->file == NULL)
	{
		um_free(tf);
		return NULL;
	}

	/* get file size */
	fseek(tf->file, 0, SEEK_END);
	fgetpos(tf->file, &(tf->filelen));
	fseek(tf->file, 0, SEEK_SET);

	if (tf->filelen>0)
	{
		tf->buffer= (char *) um_malloc ((size_t) tf->filelen);

		if (tf->buffer != NULL)
		{
			fread(tf->buffer, sizeof(char), (size_t) tf->filelen, tf->file);
		}
	} else
	{
		tf->buffer = NULL;
	}
	tf->bufptr= tf->buffer;
	tf->bufend= tf->buffer + tf->filelen;
#else
	/* Auf normale Routine zurueckgreifen */
	tf->file= fopen(filename, "r");

	if (tf->file == NULL)
	{
		um_free(tf);
		tf= NULL;
	}

#endif

	return tf;

}	/* myTextOpen */


GLOBAL char *myTextGetline ( char *string, int n, MYTEXTFILE *tf )
{
#if USE_MYTEXTFILE
	size_t sl;
	char *cr, *lf;

	*string= '\0';

	if (!tf || !tf->buffer || !tf->bufptr || tf->bufptr >= tf->bufend)
	{
		return NULL;
	}

	cr= strchr(tf->bufptr, '\r');
	lf= strchr(tf->bufptr, '\n');

	if (cr == NULL && lf == NULL)
	{	/* Kein Zeilenende mehr gefunden -> Rest zurueckgeben */
		sl= tf->bufend - tf->bufptr;
		memcpy(string, tf->bufptr, sl);
		string[sl]= '\0';
		tf->bufptr= tf->bufend;
		return string;
	}

	if (cr != NULL && lf != NULL)
	{	/* DOS-Zeile */
		*cr= '\0';
		*lf= '\0';
		strcpy(string, tf->bufptr);

		if (cr<lf)
		{	tf->bufptr= lf+1;
		}
		else
		{	tf->bufptr= cr+1;
		}

		return string;
	}

	if (cr != NULL)
	{	/* MAC-Zeile */
		*cr= '\0';
		strcpy(string, tf->bufptr);
		tf->bufptr= cr+1;
		return string;
	}

	if (lf != NULL)
	{	/* Unix-Zeile */
		*lf= '\0';
		strcpy(string, tf->bufptr);
		tf->bufptr= lf+1;
		return string;
	}
#else
	size_t sl;
	BOOLEAN cont;

	do {
		cont=FALSE;
		/* Auf normale Routine zurueckgreifen und Endekennung entfernen */
		if (fgets(string, n, tf->file) == NULL)
		{
			return NULL;
		}

		sl= strlen(string);
		while (sl>0 && (string[sl-1]=='\n' || string[sl-1]=='\r'))
		{
			string[sl-1]= '\0';
			sl--;
		}
		/*	v6.5.4 [vj] This is a new check for a continued line. This is handled low level,
			so UDO doesn't need to care about later, except that some buffers could use more space! */
		if ((string[sl-2]=='!')&&(string[sl-1]=='\\')) /* Is there a continue line mark before linebreak? */
		{
			sl=sl-2; /* String got shorter */
			string[sl]='\0'; /* Cut continue line! */
			/* Above n is used to indicate how much space is left and string is the buffer start */
			n=n-sl; /* The new buffer is n minus the string we currently have */
			string=string+sl; /* So this is the new buffer start */
			cont=TRUE;
		}
	}
	while (cont==TRUE);
#endif

	return string;

}	/* myTextGetline */


GLOBAL int myTextClose ( MYTEXTFILE *tf )
{
	if (tf == NULL)
	{
		return EOF;
	}

	if (tf->buffer != NULL)
	{
		um_free(tf->buffer);
	}

	fclose(tf->file);
	um_free(tf);

	return 0;

}	/* myTextClose */



/*	#################################################################
	#################################################################	*/

#ifndef __MACOS__

/*	----------------------------------------------------------------------
	Funktion:	strmir()
	Zweck:		Spiegelt einen String
	----------------------------------------------------------------------	*/
LOCAL char *strmir ( char *s )
{
	size_t	sl, i;
	char	swap;
	
	if (  ( sl=strlen(s) ) > 0  )
	{	for (i=0; i<sl/2; i++)
		{	swap= s[i];
			s[i]= s[sl-i-1];
			s[sl-i-1]= swap;
		}
	}

	return(s);		
}	/* strmir */

/*	----------------------------------------------------------------------
	Funktion:	fsplit()
	Zweck:		Zerpflueckt einen Zugriffspfad in seine Bestandteile
	Uebergabe:	s:			Zugriffspfad (z.B. "C:\GEMINI2\HOME\MUPFEL.RC");
	Rueckgabe:	drive:		"C:"
				path:		"\GEMINI2\HOME\"
				filename:	"MUPFEL"
				suffix:		".RC"
	----------------------------------------------------------------------	*/
GLOBAL void fsplit (char *s, char *drive, char *path, char *filename, char*suffix)
{
	char	wrk[512];
	char	*found;
	size_t	wl, fl, l;
	
	strcpy(drive, "");
	strcpy(path, "");
	strcpy(filename, "");
	strcpy(suffix, "");
	
	strcpy(wrk, s);
	wl= strlen(wrk);

	if ( wl==0 )	return;

	strcpy(wrk, s);
	strmir(wrk);
	
	/* Drive ermitteln und abschneiden */	
	if ( wrk[wl-2]==':' )
	{	strcpy(drive, "a:");
		drive[0]=wrk[wl-1];
		wrk[wl-2]='\0';
		wl= strlen(wrk);
	}

	/* Filenamen ermitteln und abschneiden */	
	strcpy(filename, wrk);
	l= 0;
	while ( (filename[l]!='\0') && (filename[l]!='\\') && (filename[l]!='/') )
		l++;
	filename[l]='\0';
	strmir(filename);
	fl= strlen(filename);
	strmir(wrk);
	wrk[wl-fl]= '\0';	

	/* Jetzt noch aus dem Filenamen den Suffix extrahieren */
	if ( (found=strrchr(filename, '.'))!=NULL )
	{	strcpy(suffix, found);
		filename[fl-strlen(suffix)]= '\0';
	}

	/* Das, was von <wrk> uebriggeblieben ist, ist der Pfad */
	strcpy(path, wrk);

}	/*fsplit*/

#endif /* #ifndef __MACOS__ */



#ifdef __MACOS__
/*	----------------------------------------------------------------------
	Version fuer Apple Macintosh: Martin Osieka @ OF2, 18.04.1996
	Zerlegt den Dateipfad <sour> in seine Bestandteile und liefert sie
	im Macintosh-Format in den <dest...> Parametern zurueck.
	Ein Macintosh-Dateipfad kann folgendermassen aufgebaut sein:

	Absoluter Pfad:                     volume:folder1:...:folderN:name
	Pfad relativ zum aktuellen Ordner:  :folderM:...:folderN:name
	Datei im aktuellen Ordner:          name

	D.h. sobald der Dateipfad mindestens einen ':'-Seperator enthaelt und 
	dieser nicht am Pfadanfang steht, ist der erste Bestandteil des
	Dateipfades ein volume-Name.
	----------------------------------------------------------------------	*/

GLOBAL void 
fsplit( const char *sour, char *destDrive, char *destFolders, char *destName, char *destSuffix)
{
	char *s;
	
	*destDrive = 0;
	*destFolders = 0;
	
	s = strrchr( sour, ':');
	if (s && (s != sour + 1)) {	
		/* Macintosh-Dateipfad (volume-Name wird nicht abgetrennt) */
		s += 1;
		strncpy( destFolders, sour, s - sour);
		destFolders[ s - sour] = 0;
		sour = s;
	}
	else {
		/* DOS- oder Unix-Dateipfad */
		if (s) {
			strncpy( destDrive, sour, 2);
			destDrive[ 2] = 0;
			sour += 2;
		}
		s = strrchr( sour, '/');
		if (s) {
			if (sour[ 0] != '/') {
				*destFolders++ = ':';
			}
			s += 1;
			strncpy( destFolders, sour, s - sour);
			destFolders[ s - sour] = 0;
			sour = s;
			s = destFolders;
			while ((s = strchr( s, '/')) != NULL) {
				*s++ = ':';
			}
		}
		else {
			s = strrchr( sour, '\\');
			if (s) {
				if (sour[ 0] != '\\') {
					*destFolders++ = ':';
				}
				s += 1;
				strncpy( destFolders, sour, s - sour);
				destFolders[ s - sour] = 0;
				sour = s;
				s = destFolders;
				while ((s = strchr( s, '\\')) != NULL) {
					*s++ = ':';
				}
			}
		}
	}
	
	/* Dateinamen und -suffix aufspalten */
	s = strrchr( sour, '.');
	if (s) {
		strncpy( destName, sour, s - sour);
		destName[ s - sour] = 0;
		strcpy( destSuffix, s);
	}
	else {
		strcpy( destName, sour);
		*destSuffix = 0;
	}
} /* fsplit */


#endif /* #ifdef __MACOS__ */



/*	--------------------------------------------------------------
	myFwopen() / myFwbopen()
	Oeffnen einer Datei mit Modus "w" bzw. "wb" und gleichzeitigem
	Aufruf von SetFileType fuer die Systeme, die einen Creator
	setzen muessen (Idee: Rainer Riedl)
	Dadurch spart man sich die ganzen Abfragen in den anderen
	Modulen und vermeidet, dass man ein SetFileType vergisst.
	->	filename: siehe fopen()
		filetype: TOASC, TOHTM, TOGIF (neu)
	<-	Stream wie bei fopen()
	--------------------------------------------------------------	*/
GLOBAL FILE * myFwopen ( const char *filename, const int filetype )
{
	FILE *file;

	file= fopen(filename, "w");

#if USE_SETFILETYPE	
	if (file)
	{	SetFileType(filename, filetype);
	}
#else
	UNUSED(filetype);
#endif

	return file;
}	/* myFwopen */


GLOBAL FILE * myFwbopen ( const char *filename, const int filetype )
{
	FILE *file;

	file= fopen(filename, "wb");

#if USE_SETFILETYPE	
	if (file)
	{	SetFileType(filename, filetype);
	}
#else
	UNUSED(filetype);
#endif

	return file;
}	/* myFwbopen */


/*	----------------------------------------------------------------------
	Oeffnen/Schliessen von Dateien und Rueck-/Uebergabe von MYFILE struct
	----------------------------------------------------------------------	*/

LOCAL MYFILE *my_new_myfile ( void )
{
	MYFILE *myfile;

	myfile = (MYFILE *)um_malloc(sizeof(MYFILE));

	if (myfile!=NULL)
	{
		memset(myfile, 0, sizeof(MYFILE));
	}

	return myfile;
}

LOCAL BOOLEAN my_free_myfile ( MYFILE *myfile )
{
	if (myfile!=NULL)
	{
		um_free(myfile);
		return TRUE;
	}

	return FALSE;
}

GLOBAL MYFILE *my_fopen ( const char *filename, const char *mode )
{
	MYFILE *myfile;

	myfile= my_new_myfile();

	if (myfile!=NULL)
	{
		myfile->file= fopen(filename, mode);

		if (myfile->file)
		{
			myfile->opened= TRUE;
		}
	}

	return myfile;
}

GLOBAL BOOLEAN my_fclose ( MYFILE *myfile )
{
	if (myfile!=NULL)
	{
		if (myfile->file)
		{
			fclose(myfile->file);
		}

		return my_free_myfile(myfile);
	}

	return FALSE;
}



/*	----------------------------------------------------------------------
	Anpassen des Pfad-Separators abhaengig von USE_SLASH
	----------------------------------------------------------------------	*/
GLOBAL void path_adjust_separator ( char *s )
{
#if USE_SLASH
	replace_char(s, "\\", "/");
#else
	replace_char(s, "/", "\\");
#endif
}	/* path_adjust_separator */



#if USE_HTML_FOLDERS

/*	----------------------------------------------------------------------
	Ermitteln des aktuellen Verzeichnisses
	----------------------------------------------------------------------	*/
LOCAL BOOLEAN my_getcwd ( char *s, int maxlen )
{
	BOOLEAN ret= TRUE;

	if (getcwd(s, maxlen)==NULL)
	{	ret= FALSE;
	}

	return ret;

}	/* my_getcwd */


/*	----------------------------------------------------------------------
	Testen, ob ein Verzeichnis vorhanden ist
	----------------------------------------------------------------------	*/
LOCAL BOOLEAN myDirExists ( char *s )
{
	char old[512];
	BOOLEAN ret= TRUE;

	my_getcwd(old, 512);

	if (chdir(s)!=0)
	{	ret= FALSE;
	}

	chdir(old);

	return ret;

}	/* myDirExists */

/*	----------------------------------------------------------------------
	Anlegen eines Verzeichniss
	----------------------------------------------------------------------	*/
GLOBAL BOOLEAN my_mkdir ( char *s )
{
	BOOLEAN ret= TRUE;

	if (!myDirExists(s))
	{	if (mkdir(s)!=0)
		{	ret= FALSE;
			error_mkdir(s);
		}
	}

	return ret;

}	/* my_mkdir */


#endif /* USE_HTML_FOLDERS */


/*	##############################################################
	# file.c
	##############################################################	*/
