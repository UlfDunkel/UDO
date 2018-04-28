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
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
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
#include "constant.h"                     /* ENV_... */





/*******************************************************************************
*
*     EXTERNAL REFERENCES
*
******************************************|************************************/

extern _UWORD       uiMultiLines;          /* */
extern PASSFLAGS   pflag[3];              /* UDO.H */
extern int         iUdopass;              /* UDO.H */






/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

LOCAL char *strmir(char *s);










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

GLOBAL MYTEXTFILE *myTextOpen(

const char     *filename)  /* */
{
   MYTEXTFILE  *tf;        /* */
   

   tf = (MYTEXTFILE *)malloc(sizeof(*tf));

   if (tf == NULL)
      return NULL;

   memset(tf, 0, sizeof(*tf));

#if USE_MYTEXTFILE
   tf->file = fopen(filename, "rb");

   if (tf->file == NULL)
   {
      free(tf);
      return NULL;
   }

                                          /* get file size */
   fseek(tf->file, 0, SEEK_END);
   fgetpos(tf->file, &(tf->filelen));
   fseek(tf->file, 0, SEEK_SET);

   if (tf->filelen > 0)
   {
      tf->buffer = (char *)malloc((size_t)tf->filelen);

      if (tf->buffer != NULL)
      {
         fread(tf->buffer, sizeof(char), (size_t) tf->filelen, tf->file);
      }
   }
   else
   {
      tf->buffer = NULL;
   }
   tf->bufptr = tf->buffer;
   tf->bufend = tf->buffer + tf->filelen;
#else
   /* Auf normale Routine zurueckgreifen */
   /* v6.5.9 [me] fgets kommt mit Zeilenenden nicht so gut klar,   */
   /*             wenn diese gem. den Konventionen einer anderen   */
   /*             Plattform codiert sind. Daher Ausweichen auf     */
   /*             fread und selbst '\n' und '\r' erkennen. Dazu    */
   /*             muss hier die Datei binaer geoeffnet werden!         */

#ifndef __fast_file
   tf->file = fopen(filename, "rb");
#else
   tf->file = fopen(filename, "r");
#endif


   if (tf->file == NULL)
   {
      free(tf);
      tf = NULL;
   }
   else
   {
      /* v6.5.13 [vj] Dieser Befehl darf natuerlich nur ausgefuehrt werden,
                        wenn tf-file != NULL ist, sonst crashed UDO an
                        dieser Stelle */
      setvbuf(tf->file, NULL, _IOFBF, 8192);
   }

#endif

   return tf;
}





/*******************************************************************************
*
*  myTextGetline():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL char *myTextGetline(

char        *string,  /* */
size_t       n,       /* */
MYTEXTFILE  *tf)      /* */
{
#if USE_MYTEXTFILE
   size_t    sl;      /* */
   char     *cr,      /* ^ to Carriage Return (CR) */
            *lf;      /* ^ to Line Feed       (LF) */


   *string = EOS;                         /* clear string */

   if (!tf || !tf->buffer || !tf->bufptr || tf->bufptr >= tf->bufend)
      return NULL;

   cr = strchr(tf->bufptr, '\r');         /* find CR */
   lf = strchr(tf->bufptr, '\n');         /* find LF */

   if (cr == NULL && lf == NULL)          /* Kein Zeilenende mehr gefunden -> Rest zurueckgeben */
   {
      sl = tf->bufend - tf->bufptr;
      
      memcpy(string, tf->bufptr, sl);
      
      string[sl] = EOS;
      tf->bufptr = tf->bufend;
      
      return string;
   }

   if (cr != NULL && lf != NULL)          /* DOS-Zeile */
   {
      *cr = EOS;
      *lf = EOS;
      
      strcpy(string, tf->bufptr);

      if (cr < lf)
         tf->bufptr = lf + 1;
      else
         tf->bufptr = cr + 1;

      return string;
   }

   if (cr != NULL)                        /* Mac-Zeile */
   {
      *cr = EOS;
      
      strcpy(string, tf->bufptr);
      
      tf->bufptr = cr + 1;
      
      return string;
   }

   if (lf != NULL)                        /* Unix-Zeile */
   {
      *lf = EOS;
      
      strcpy(string, tf->bufptr);
      
      tf->bufptr = lf + 1;
      
      return string;
   }
   
#else

   register char  *s_ptr;  /* */
   size_t          sl;     /* */
   _BOOL         cont;   /* */

   /* This indicates how many lines have been added with \! to the current line */

   uiMultiLines = -1;                     /* 0 = Es wurden keine Zeilen zusammengefuegt, */
                                          /* 1 = Es wurde eine Zeile angehaengt, */
                                          /* 2 = Es wurden zwei Zeilen angehaengt, ... */

   do
   {
      cont = FALSE;

      /* Auf normale Routine zurueckgreifen und Endekennung entfernen */
      /* v6.5.9 [me] fgets kommt mit Zeilenenden nicht so gut klar,   */
      /*             wenn diese gem. den Konventionen einer anderen   */
      /*             Plattform codiert sind. Daher Ausweichen auf     */
      /*             fread und selbst '\n' und '\r' erkennen.         */
      
#ifndef __fast_file
      sl = fread(string, sizeof(*string), n - 1, tf->file);
      
      if (sl < 1)
         return NULL;

      string[sl] = EOS;

      /* v6.5.9 [me] den String am Ende der Zeile kuerzen und */
      /*             die passende Anzahl von Zeichen wieder   */
      /*             in den Input-Stream stellen.             */
      
      for (s_ptr = string; *s_ptr != '\n' && *s_ptr != '\r' && *s_ptr != '\0'; s_ptr++)
      {
         /* Reine Zaehlschleife, daher gibt es hier nichts zu tun */
      }


      /* v6.5.10 [me]   Die neue Stringlaenge wird bestimmt, um eine */
      /*                erneute Zaehlung der Zeichen zu vermeiden!   */
      
      sl = (s_ptr - string);

                                          /* Bei den Zeichen fuer neue Zeile innehalten */
      if (*s_ptr == '\n' || *s_ptr == '\r')
      {
         char ch = *s_ptr;                /* Den zu verarbeitenden String abteilen */
         *(s_ptr++) = EOS;

                                          /* Das naechste zu lesende Zeichen der neuen Zeile suchen */
         if ( (*s_ptr == '\n' || *s_ptr == '\r') && *s_ptr != ch)
            s_ptr++;

                                          /* Nun genau so viele Zeichen zurueckgeben, */
                                          /* wie nun in s_ptr zu viel gelesen wurden */
         fseek(tf->file, -(long)strlen(s_ptr), SEEK_CUR);
      }
#else
      if (fgets(string, n, tf->file) == NULL)
         return NULL;

      sl = strlen(string);
#endif

      uiMultiLines++;
      
      while (sl > 0 && (string[sl - 1] == '\n' || string[sl - 1] == '\r') )
      {
         string[sl - 1] = EOS;
         sl--;
      }


      switch (pflag[iUdopass].env)        /* don't glue these soft-broken lines in ALL environments! */
      {
      case ENV_VERBATIM:
         break;
         
      default:

      /*   v6.5.4 [vj]   This is a new check for a continued line. This is handled low level, */
      /*               so UDO doesn't need to care about later, except that some buffers      */
      /*               could use more space!                                                  */
      
                                          /* Is there a continue line mark before linebreak? */
         if (sl > 1 && (string[sl - 2] == '!') && (string[sl - 1] == '\\'))
         {
            sl = sl - 2;                  /* shorte string */

            string[sl] = EOS;             /* cut continue line! */
         
         /* Above n is used to indicate how much space is left and string is the buffer start */
         
            n = n - sl;                   /* The new buffer is n minus the string we currently have */

            string = string + sl;         /* So this is the new buffer start */
         
            cont = TRUE;
         }
         
      }  /* switch () */
   }
   while (cont == TRUE);
#endif

   return string;
}





/*******************************************************************************
*
*  myTextClose():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL int myTextClose(

MYTEXTFILE  *tf)  /* */
{
   if (tf == NULL)
      return EOF;

   if (tf->buffer != NULL)
      free(tf->buffer);

   fclose(tf->file);
   free(tf);

   return 0;
}





#ifndef __MACOS__
/*******************************************************************************
*
*  strmir():
*     Spiegelt einen String
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL char *strmir(

char       *s)     /* */
{
   size_t   sl,    /* */
            i;     /* */
   char     swap;  /* */
   

   if ( (sl = strlen(s)) > 0)
   {
      for (i = 0; i < sl / 2; i++)
      {
         swap = s[i];
         s[i] = s[sl - i - 1];
         s[sl - i - 1] = swap;
      }
   }

   return (s);      
}
#endif /* #ifndef __MACOS__ */





#ifndef __MACOS__
/*******************************************************************************
*
*  fsplit():
*     Zerpflueckt einen Zugriffspfad in seine Bestandteile
*
*  Notes:
*     Uebergabe:   s:         Zugriffspfad (z.B. "C:\GEMINI2\HOME\MUPFEL.RC");
*     Rueckgabe:   drive:     "C:"
*                  path:      "\GEMINI2\HOME\"
*                  filename:  "MUPFEL"
*                  suffix:    ".RC"
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void fsplit(

char       *s,         /* */
char       *drive,     /* */
char       *path,      /* */
char       *filename,  /* */
char       *suffix)    /* */
{
   char     wrk[512];  /* */
   char    *found;     /* */
   size_t   wl,        /* */
            fl,        /* */
            l;         /* */


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

   if (wrk[wl - 2] == ':')                /* Drive ermitteln und abschneiden */   
   {
      strcpy(drive, "a:");
      drive[0] = wrk[wl - 1];
      wrk[wl - 2] = EOS;
      wl = strlen(wrk);
   }

   strcpy(filename, wrk);                 /* Filenamen ermitteln und abschneiden */   
   l = 0;
   
   while ( (filename[l] != EOS) && (filename[l] != '\\') && (filename[l] != '/') )
      l++;
      
   filename[l] = EOS;

   strmir(filename);
   fl = strlen(filename);
   
   strmir(wrk);
   
   wrk[wl - fl] = EOS;   

                                          /* Jetzt noch aus dem Filenamen den Suffix extrahieren */
   if ( (found = strrchr(filename, '.')) != NULL)
   {
      strcpy(suffix, found);
      filename[fl - strlen(suffix)] = EOS;
   }

   strcpy(path, wrk);                     /* Das, was von <wrk> uebriggeblieben ist, ist der Pfad */
}
#endif /* #ifndef __MACOS__ */





#ifdef __MACOS__
/*******************************************************************************
*
*  fsplit():
*     splits a file specification into its components (Mac version)
*
*  Note:
*     Mac version by Martin Osieka @ OF2, 1996-04-18:
*     ----------------------------------------------------------------------
*     Zerlegt den Dateipfad <sour> in seine Bestandteile und liefert sie
*     im Macintosh-Format in den <dest...> Parametern zurueck.
*     Ein Macintosh-Dateipfad kann folgendermassen aufgebaut sein:
*  
*     Absoluter Pfad:                     volume:folder1:...:folderN:name
*     Pfad relativ zum aktuellen Ordner:  :folderM:...:folderN:name
*     Datei im aktuellen Ordner:          name
*  
*     D.h. sobald der Dateipfad mindestens einen ':'-Seperator enthaelt und 
*     dieser nicht am Pfadanfang steht, ist der erste Bestandteil des
*     Dateipfades ein volume-Name.
*     ----------------------------------------------------------------------
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void fsplit(

const char  *sour,         /* */
char        *destDrive,    /* */
char        *destFolders,  /* */
char        *destName,     /* */
char        *destSuffix)   /* */
{
   char     *s;            /* */
   

   *destDrive   = 0;
   *destFolders = 0;

   s = strrchr( sour, ':');
   
   if (s && (s != sour + 1))
   {
      /* Macintosh-Dateipfad (volume-Name wird nicht abgetrennt) */
      s += 1;
      strncpy(destFolders, sour, s - sour);
      destFolders[s - sour] = 0;
      sour = s;
   }
   else
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
         if (sour[ 0] != '/')
         {
            *destFolders++ = ':';
         }
         
         s += 1;
         strncpy( destFolders, sour, s - sour);
         destFolders[ s - sour] = 0;
         sour = s;
         s = destFolders;
         
         while ((s = strchr( s, '/')) != NULL)
         {
            *s++ = ':';
         }
      }
      else
      {
         s = strrchr( sour, '\\');
         
         if (s)
         {
            if (sour[ 0] != '\\')
            {
               *destFolders++ = ':';
            }
            
            s += 1;
            strncpy( destFolders, sour, s - sour);
            destFolders[ s - sour] = 0;
            sour = s;
            s = destFolders;
            
            while ((s = strchr( s, '\\')) != NULL)
            {
               *s++ = ':';
            }
         }
      }
   }

   /* Dateinamen und -suffix aufspalten */
   
   s = strrchr( sour, '.');
   
   if (s)
   {
      strncpy( destName, sour, s - sour);
      destName[ s - sour] = 0;
      strcpy( destSuffix, s);
   }
   else
   {
      strcpy( destName, sour);
      *destSuffix = 0;
   }
}
#endif /* #ifdef __MACOS__ */





/*******************************************************************************
*
*  myFwopen():
*     open a file in text write mode
*
*  Note:
*     Here we also set the file type for all systems which need a Creator type
*     (idea: Rainer Riedl). This avoids more queries in other modules and 
*     forgotten Creator types.
*
*     <filetype> is set in these formats:
*     - TOASC
*     - TOHTM
*     - TOGIF
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL FILE *myFwopen(

const char  *filename,  /* */
const int    filetype)  /* */
{
   FILE     *file;      /* */
   

   file = fopen(filename, "w");

#if USE_SETFILETYPE   
   if (file)
   {
      SetFileType(filename, filetype);
   }
#else
   UNUSED(filetype);
#endif

   /* v6.9.10 [me] Einen Puffer zur Beschleunigung zuordnen */
   if (file != NULL)
      setvbuf(file, NULL, _IOFBF, 8192);

   return file;
}





/*******************************************************************************
*
*  myFwbopen():
*     open a file in binary write mode
*
*  Note:
*     see myFwopen()
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL FILE *myFwbopen(

const char  *filename,  /* */
const int    filetype)  /* */
{
   FILE     *file;      /* */
   

   file = fopen(filename, "wb");

#if USE_SETFILETYPE   
   if (file)
   {
      SetFileType(filename, filetype);
   }
#else
   UNUSED(filetype);
#endif

   /* v6.9.10 [me] Einen Puffer zur Beschleunigung zuordnen */
   if (file != NULL)
      setvbuf(file, NULL, _IOFBF, 8192);

   return file;
}





/*******************************************************************************
*
*  my_new_myfile():
*     allocates space for a new file
*
*  Return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

LOCAL MYFILE *my_new_myfile(void)
{
   MYFILE  *myfile;

   myfile = (MYFILE *)malloc(sizeof(MYFILE));

   if (myfile != NULL)
   {
      memset(myfile, 0, sizeof(MYFILE));
   }

   return myfile;
}





/*******************************************************************************
*
*  my_free_myfile():
*     frees memory buffer for a file
*
*  Return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

LOCAL _BOOL my_free_myfile(

MYFILE  *myfile)  /* */
{
   if (myfile != NULL)
   {
      free(myfile);
      return TRUE;
   }

   return FALSE;
}





/*******************************************************************************
*
*  my_fopen():
*     open a file
*
*  Return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

GLOBAL MYFILE *my_fopen(

const char  *filename,  /* */
const char  *mode)      /* */
{
   MYFILE   *myfile;    /* */
   

   myfile = my_new_myfile();

   if (myfile != NULL)
   {
      myfile->file = fopen(filename, mode);

      if (myfile->file)
      {
         myfile->opened = TRUE;
      }
   }

   return myfile;
}





/*******************************************************************************
*
*  my_fclose():
*     close a file
*
*  Return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

GLOBAL _BOOL my_fclose(

MYFILE  *myfile)  /* */
{
   if (myfile != NULL)
   {
      if (myfile->file)
      {
         fclose(myfile->file);
      }

      return my_free_myfile(myfile);
   }

   return FALSE;
}





/*******************************************************************************
*
*  path_adjust_separator():
*     adjust path separator character(s)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void path_adjust_separator(

char  *s)  /* */
{
#if USE_SLASH
   replace_char(s, "\\", "/");
#else
   replace_char(s, "/", "\\");
#endif
}





#if USE_HTML_FOLDERS
/*******************************************************************************
*
*  myDirExists():
*     get current directory
*
*  Return:
*     FALSE: doesn't exist
*      TRUE: success
*
******************************************|************************************/

LOCAL _BOOL my_getcwd(

char        *s,            /* */
int          maxlen)       /* */
{
   _BOOL   ret = TRUE;   /* */
   

   if (getcwd(s, maxlen) == NULL)
      ret = FALSE;

   return ret;
}
#endif /* USE_HTML_FOLDERS */





#if USE_HTML_FOLDERS
/*******************************************************************************
*
*  myDirExists():
*     check whether a directory exists on file
*
*  Return:
*     FALSE: doesn't exist
*      TRUE: success
*
******************************************|************************************/

LOCAL _BOOL myDirExists(

char        *s)           /* */
{
   char      old[512];    /* */
   _BOOL   ret = TRUE;  /* */
   

   my_getcwd(old, 512);

   if (chdir(s) != 0)
      ret = FALSE;

   chdir(old);

   return ret;
}
#endif /* USE_HTML_FOLDERS */





#if USE_HTML_FOLDERS
/*******************************************************************************
*
*  my_mkdir():
*     create a directory on file 
*
*  Return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

GLOBAL _BOOL my_mkdir(

char        *s)           /* */
{
   _BOOL   ret = TRUE;  /* */
   

   if (!myDirExists(s))
   {
      if (mkdir(s) != 0)
      {
         ret = FALSE;
         error_mkdir(s);
      }
   }

   return ret;
}
#endif /* USE_HTML_FOLDERS */


/* +++ EOF +++ */
