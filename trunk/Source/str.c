/*******************************************************************************
*
*  Project name : UDO
*  Module name  : str.c
*  Symbol prefix: str
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
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : fd
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
*
******************************************|************************************/

#ifndef ID_STR_C
#define  ID_STR_C
const char *id_str_c= "@(#) str.c       10.03.1997";
#endif

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "portab.h"

#include "export.h"
#include "str.h"
#include "version.h"

#include "msg.h"

#include "udomem.h"
/*
   #################################################################
   #
   # strcat und strcpy Wrapper, die Puffergrenzen checken koennen
   #
   #################################################################
*/

GLOBAL char *um_strcpy(char *dest, const char *src, size_t max, const char *place)
{
   char errbuf[120];
   size_t slen; /* Temporaere Variable, fuer die Laenge von src */
   
   if ( dest == NULL )
   {
      sprintf(errbuf, "um_strcpy: dest is NULL: %s", place);
      loglnposprintf ("Warning", errbuf);
      return dest;
   }
   if ( src == NULL )
   {
      sprintf(errbuf, "um_strcpy: src is NULL: %s", place);
      loglnposprintf ("Warning", errbuf);
      dest[0]=EOS;
      return dest;
   }

   slen=(size_t)strlen(src); /* Stringlaenge bestimmen */
   if (((size_t)slen+1)<max) /* Testen obs  */
   {
      return strcpy(dest, src);
   }
   else
   {
      dest[0]=EOS;
      sprintf(errbuf, "um_strcpy: buffer overrun prevented: %s: %d>%d", place, slen+1, max);
      loglnposprintf ("Warning", errbuf);
      return dest;
   }
}

GLOBAL char *um_strncpy(char *dest, const char *src, size_t n, size_t max, const char *place)
{
   char errbuf[120];

   if ( dest == NULL )
   {
      sprintf(errbuf, "um_strncpy: dest is NULL: %s", place);
      loglnposprintf ("Warning", errbuf);
      return dest;
   }
   if ( src == NULL )
   {
      sprintf(errbuf, "um_strncpy: src is NULL: %s", place);
      loglnposprintf ("Warning", errbuf);
      dest[0]=EOS;
      return dest;
   }

   if ((n+1)<max)
   {
      return strncpy(dest, src, n);
   }
   else
   {
      dest[0]=EOS;
      sprintf(errbuf, "um_strncpy: buffer overrun prevented: %s: %d>%d", place, n+1, max);
      loglnposprintf ("Warning", errbuf);
      return dest;
   }
}

GLOBAL char *um_strcat(char *dest, const char *src, size_t max, const char *place)
{
   char errbuf[120];
   size_t dlen, slen;

   if ( dest == NULL )
   {
      sprintf(errbuf, "um_strcat: dest is NULL: %s", place);
      loglnposprintf ("Warning", errbuf);
      return dest;
   }
   if ( src == NULL )
   {
      sprintf(errbuf, "um_strcat: src is NULL: %s", place);
      loglnposprintf ("Warning", errbuf);
      return dest;
   }

   dlen=(size_t)strlen(dest);
   slen=(size_t)strlen(src);
   
   if ((dlen+slen+1)<max)
   {
      return strcat(dest, src);
   }
   else
   {
      dest[0]=EOS;
      sprintf(errbuf, "um_strcat: buffer overrun prevented: %s: %d>%d", place, dlen+slen+1, max);
      loglnposprintf ("Warning", errbuf);
      return dest;
   }
}

GLOBAL char *um_strncat(char *dest, const char *src, size_t n, size_t max, const char *place)
{
   char errbuf[120];
   size_t dlen;

   if ( dest == NULL )
   {
      sprintf(errbuf, "um_strncat: dest is NULL: %s", place);
      loglnposprintf ("Warning", errbuf);
      return dest;
   }
   if ( src == NULL )
   {
      sprintf(errbuf, "um_strncat: src is NULL: %s", place);
      loglnposprintf ("Warning", errbuf);
      return dest;
   }

   dlen=strlen(dest);
   if ((dlen+n+1)<max)
   {
      return strncat(dest, src, n);
   }
   else
   {
      dest[0]=EOS;
      sprintf(errbuf, "um_strncat: buffer overrun prevented: %s: %d>%d", place, dlen+n+1, max);
      loglnposprintf("Warning", errbuf);
      return dest;
   }
}

/*
 * v6.5.15 [vj] New function makes physical copies of a string
 *
 * morealloc is the number of bytes that should be alloced more
 * for the new string (e.g. if you need to extend the copied string
 * but leave the original alone)
 */
GLOBAL char *um_physical_strcpy(const char *src, size_t morealloc, const char *place)
{
   size_t slen; /* length of source string */
   char *dest;  /* pointer to the new string */
   char placebuf[120]; /* internal buffer for place handling */

   sprintf(placebuf, "%s: um_physical_strcpy", place);

   slen=strlen(src);
   dest=um_malloc(slen+morealloc+1);

   if (dest != NULL)
   {
      dest=um_strcpy(dest, src, slen+morealloc+1, placebuf);
   }

   return dest;
}

/* ############################################################
   #
   # Anhaengen von Strings und Zeichen
   #
   ############################################################   */
/* ----------------------------------------------------------------------
   chrcat()
   Aufgabe: Anhaengen eines Zeichens an einen String
   ----------------------------------------------------------------------  */
GLOBAL char *chrcat (char *dest, const char c)
{
   char one[2]={0,0};

   one[0]= c;
   return(strcat(dest, one));
}  /* chrcat */



/* ############################################################
   #
   # Einfuegen von Strings
   #
   ############################################################   */
/* ------------------------------------------------------------
   strinsert() fuegt am Anfang von <s> den String <ins> ein
   -> string: String, in dem eingefuegt werden soll
      insert:  einzufuegender String
   <- Zeiger auf <string>
   ------------------------------------------------------------   */
GLOBAL char *strinsert ( char *string, const char *insert)
{
   char  *start;
   size_t   sl, il;
   
   if ( insert[0]=='\0' )
   {  return string;
   }
   
   sl= strlen(string);
   il= strlen(insert);

   /* Platz schaffen fuer neues und dorthin kopieren */
   start= string;
   memmove(string+il, string, sl+1);
   memcpy(start, insert, il);
   
   return string;
}  /*strinsert*/




/* ############################################################
   #
   # Ersetzen von einzelnen Zeichen
   #
   ############################################################   */

/*******************************************************************************
*
*  replace_char():
*     replaces all occurrences of <search> by <replace> in <string>
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_char(

char        *string,   /* ^string to be edited */
const char  *search,   /* ^search string */
const char  *replace)  /* ^replace string */
{
   char     *ptr;      /* ^edit string */

   
   ptr = string;                          /* set ^ to begin of edit string */

   while (*ptr != EOS)                    /* check whole edit string */
   {
      if (*ptr == *search)                /* character found! */
        *ptr = *replace;                  /* replace it */
      
      ptr++;
   }
}



/* ############################################################
   #
   # Ersetzen von Strings
   #
   ############################################################   */

/* ------------------------------------------------------------
   replace_once() ersetzt in <s> einmal <rep> durch <by>
   -> source: String, in dem ersetzt werden soll
      rep:  zu ersetzender String
      by:      neuer String
   <- 1: String wurde ersetzt
      0: String nicht gefunden
   ------------------------------------------------------------   */
GLOBAL int replace_once ( char *source, const char *replace, const char *by)
{
   char  *found;
   size_t   rlen, blen, flen;
   
   if ( source[0]=='\0' )     return 0;
   if ( replace[0]=='\0' )    return 0;
   
   if ( (found= strstr(source, replace))==NULL )   return 0;

   rlen=strlen(replace);
   flen= strlen(found);

   /* Zu Ersetzendes entfernen */
   memmove(found, found+rlen, flen-rlen+1);

   /* Platz schaffen fuer neues und dorthin kopieren */
   if ( by[0]!=EOS )
   {  blen= strlen(by);
      flen= strlen(found);
      memmove(found+blen, found, flen+1);
      memcpy(found, by, blen);
   }
   
   return 1;
}  /*replace_once*/


/* ------------------------------------------------------------
   replace_last() ersetzt in <s> das letzte <rep> durch <by>
   ------------------------------------------------------------   */
GLOBAL int replace_last ( char *source, const char *replace, const char *by)
{
   char *found, *look, *last;

   if ( source[0]=='\0' )     return 0;
   if ( replace[0]=='\0' )    return 0;
   
   look= source;
   last= NULL;

   while ( (found= strstr(look, replace))!=NULL )
   {  look= found+1;
      last= found;
   }

   if (last!=NULL)
   {  return ( replace_once(last, replace, by) );
   }
   
   return 0;
}  /* replace_last */





/*******************************************************************************
*
*  replace_all():
*     replaces all occurrences of <search> by <replace> in string <source>
*
*  Return:
*     1 = success
*     2 = error
*
******************************************|************************************/

GLOBAL int replace_all(

   char        *source,   /* ^string to be edited */
   const char  *search,   /* ^search string to be replaced */
   const char  *replace)  /* ^replacement string */
{
   char       *found;     /* ^ found character */
   size_t      slen,      /* length of search string */
               rlen,      /* length of replacement string */
               flen,      /* length of found string */
               i;         /* counter */
   
   
   if (source[0]  == '\0')                /* empty edit string? */
      return 0;                           /* not allowed! */
      
   if (replace[0] == '\0')                /* empty search string? */
      return 0;                           /* not allowed! */

                                          /* search string not in edit string? */
   if ( (found = strstr(source, search)) == NULL )
      return 0;

   slen = strlen(search);
   rlen = strlen(replace);

   /* --- simple method: --- */
   
   if (slen == rlen)                      /* search + replace string lengths are equal */
   {
      while (found != NULL)               /* still something found! */
      {
         for (i = 0; i < rlen; i++)       /* replace characters in edit string */
            found[i] = replace[i];             

                                          /* find next position of replacement string */
         found = strstr(found + rlen, search);
      }
      
      return 1;                           /* done! */
   }

   /* --- complex method: --- */
   /* search + replace string lengths are different */

   while (found != NULL)                  /* still something found: */
   {
      flen = strlen(found);               /* get length of remaining edit string */

                                          /* Zu Ersetzendes entfernen */
      memmove(found, found + slen, flen - slen + 1);
   

      if (replace[0] != EOS)              /* replacement string must not be empty! */
      {
         flen = strlen(found);            /* get new length of remaining edit string */
                                          /* Platz schaffen fuer neues und dorthin kopieren */
         memmove(found + rlen, found, flen + 1);
         memcpy(found, replace, rlen);    /* insert replacement string */

                                          /* find next position of replacement string */
         found = strstr(found + rlen, search);
      }
      else
      {
         found = strstr(found, search);
      }
   }
   
   return 1;                              /* done! */
}





/* ############################################################
   #
   # Ersetzen von Strings (schnelle Variante) r6pl2
   #
   ############################################################   */

/* ------------------------------------------------------------
   qreplace_once() ersetzt in <s> einmal <rep> durch <by>
   Im Gegensatz zu replace_one() sind die Laengen der Strings
   bekannt (kein strlen() noetig). Dadurch   ist diese Routine
   schneller als replace_one(): "q" steht fuer "quick"
   -> source:     String, in dem ersetzt werden soll
      replace: zu ersetzender String
      rlen:    strlen(replace)
      by:         neuer String
      blen:    strlen(by)
   <- 1: String wurde ersetzt
      0: String nicht gefunden
   ------------------------------------------------------------   */
GLOBAL int qreplace_once ( char *source,
                     const char *replace,
                     const size_t rlen,
                     const char *by,
                     const size_t blen
                  )
{
   char  *found;
   size_t   flen;

#if CHECK_REPLACE_LEN
   if (rlen!=strlen(replace))
   {  fprintf(stdout, "Fehler in qreplace_once:\n");
      fprintf(stdout, "rlen= %d\n", rlen);
      fprintf(stdout, "strlen(%s)= %d\n", replace, strlen(replace));
   }
   if (blen!=strlen(by))
   {  fprintf(stdout, "Fehler in qreplace_once:\n");
      fprintf(stdout, "blen= %d\n", blen);
      fprintf(stdout, "strlen(%s)= %d\n", by, strlen(by));
   }
#endif
   
   if ( source[0]=='\0' )     return 0;
   if ( replace[0]=='\0' )    return 0;

   if ( (found= strstr(source, replace))==NULL )   return 0;

   flen= strlen(found);

   /* Zu Ersetzendes entfernen */
   memmove(found, found+rlen, flen-rlen+1);

   /* Platz schaffen fuer neues und dorthin kopieren */
   if ( by[0]!=EOS )
   {  flen= strlen(found);
      memmove(found+blen, found, flen+1);
      memcpy(found, by, blen);
   }
   
   return 1;
}  /* qreplace_once */


/* ------------------------------------------------------------
   qreplace_last() ersetzt in <s> das letzte <rep> durch <by>
   ------------------------------------------------------------   */
GLOBAL int qreplace_last ( char *source,
                     const char *replace,
                     const size_t rlen,
                     const char *by,
                     const size_t blen
                  )
{
   char *found, *look, *last;

#if CHECK_REPLACE_LEN
   if (rlen!=strlen(replace))
   {  fprintf(stdout, "Fehler in qreplace_last:\n");
      fprintf(stdout, "rlen= %d\n", rlen);
      fprintf(stdout, "strlen(%s)= %d\n", replace, strlen(replace));
   }
   if (blen!=strlen(by))
   {  fprintf(stdout, "Fehler in qreplace_last:\n");
      fprintf(stdout, "blen= %d\n", blen);
      fprintf(stdout, "strlen(%s)= %d\n", by, strlen(by));
   }
#endif

   if ( source[0]=='\0' )     return 0;
   if ( replace[0]=='\0' )    return 0;
   
   look= source;
   last= NULL;

   while ( (found= strstr(look, replace))!=NULL )
   {  look= found+1;
      last= found;
   }

   if (last!=NULL)
   {  return ( qreplace_once(last, replace, rlen, by, blen) );
   }
   
   return 0;
}  /* qreplace_last */





/*******************************************************************************
*
*  qreplace_all():
*     replace all <rep> by <by> in <s>
*
*  return:
*     1 = replacement was successful
*     0 = error
*
******************************************|************************************/

GLOBAL int qreplace_all(

char          *source,   /* */
const char    *replace,  /* */
const size_t   rlen,     /* */
const char    *by,       /* */
const size_t   blen)     /* */
{
   char       *found;    /* */
   size_t      flen,     /* */
               i;        /* */

#if CHECK_REPLACE_LEN
   if (rlen != strlen(replace))
   {
      fprintf(stdout, "Fehler in qreplace_all:\n");
      fprintf(stdout, "rlen= %d\n", rlen);
      fprintf(stdout, "strlen(%s)= %d\n", replace, strlen(replace));
   }
   
   if (blen != strlen(by))
   {
      fprintf(stdout, "Fehler in qreplace_all:\n");
      fprintf(stdout, "blen= %d\n", blen);
      fprintf(stdout, "strlen(%s)= %d\n", by, strlen(by));
   }
#endif
   
   if (source[0]  == '\0')
      return 0;
      
   if (replace[0] == '\0')
      return 0;

   if ( (found = strstr(source, replace)) == NULL)
      return 0;

   if (rlen == blen)
   {
      while (found != NULL)
      {
         for (i = 0; i < blen; i++)
         {
            found[i] = by[i];
         }
         
         found = strstr(found + blen, replace);
      }
      
      return 1;
   }

   while (found != NULL)
   {
      flen = strlen(found);

                                          /* Zu Ersetzendes entfernen */
      memmove(found, found + rlen, flen - rlen + 1);
   
      if (by[0] != EOS)                   /* Platz schaffen fuer neues und dorthin kopieren */
      {
         flen = strlen(found);
         memmove(found + blen, found, flen + 1);
         memcpy(found, by, blen);
         found = strstr(found + blen, replace);
      }
      else
      {
         found = strstr(found, replace);
      }
      
   }

   return 1;
}





/* ############################################################
   #
   # Loeschen von Strings
   #
   ############################################################   */
GLOBAL int delete_once ( char *source, const char *to_delete )
{
   return(replace_once (source, to_delete, ""));
}

GLOBAL int delete_last ( char *source, const char *to_delete )
{
   return(replace_last (source, to_delete, ""));
}

GLOBAL int delete_all ( char *source, const char *to_delete )
{
   return(replace_all (source, to_delete, ""));
}


GLOBAL int qdelete_once ( char *source, const char *to_delete, const size_t dlen )
{
   return ( qreplace_once (source, to_delete, dlen, "", 0) );
}

GLOBAL int qdelete_last ( char *source, const char *to_delete, const size_t dlen )
{
   return ( qreplace_last (source, to_delete, dlen, "", 0) );
}

GLOBAL int qdelete_all ( char *source, const char *to_delete, const size_t dlen )
{
   return ( qreplace_all (source, to_delete, dlen, "", 0) );
}



/* ------------------------------------------------------------
   del_right_spaces() entfernt Leerzeichen am Ende
   ------------------------------------------------------------   */
GLOBAL void del_right_spaces ( char *s )
{
   size_t   sl;
   
   sl= strlen(s);

   while (  (sl>0) && (s[sl-1]==' ') )
   {  s[sl-1]= EOS;
      sl--;
   }

}  /* del_right_spaces */



/* ------------------------------------------------------------
   del_whitespaces() entfernt Leerzeichen und Tabs am Anfang
   und Ende des uebergebenen Strings.
   ------------------------------------------------------------   */
GLOBAL void del_whitespaces ( char *s)
{
   size_t   sl;
   
   /* Neue Methode: schneller */
   
   char *p1st = s;
   
   while (*p1st != EOS && (*p1st == ' ' || *p1st == '\t') )
   {  ++p1st;
   }

   sl = strlen(p1st);
   
   if (*p1st != EOS && s != p1st)
   {  
      memmove(s, p1st, sl+1);
   }
   
   /* Rechts TAB's und Leerzeichen entfernen */
   if (sl > 0)
   {
      p1st = s + sl - 1;
      while (*p1st == ' ' || *p1st == '\t')
         --p1st;
      p1st[1] = EOS;
   }
}  /*del_whitespaces*/





/*******************************************************************************
*
*  get_brackets_ptr():
*     Ermittelt aus einem String wie "!raw [ stg, tex ] foo bar"
*     oder "!docinfo [author] Dirk Hagedorn" den Zeiger auf das
*     erste Zeichen hinter der ersten [ und die Anzahl der Zeichen,
*     die bis zur ersten ] folgen.
*  
*  Returns:
*     0   : wrong syntax (no brackets [ + ] found)
*     else: length of content
*
******************************************|*************************************/

GLOBAL size_t get_brackets_ptr(

char       *s,     /* ^ string to be checked */
char      **cont,  /* ^ first char of content */
char      **data)  /* ^ first char of data */
{
   char    *ptr;   /* a pointer */
   size_t   len;   /* computed length */
   

   ptr = s;                               /* copy pointer as we will change it local */
   
   *cont = NULL;                          /* nothing found yet */
   *data = NULL;

   len = 0;                               /* nothing to report yet */
   
   while (*ptr != EOS)
   {
      if (*ptr == '[')                    /* first opening bracket [ found */
      {
         *cont = ptr + 1;                 /* remind start of content */
      }
      
      if (*ptr == ']')                    /* first closing bracket ] found */ 
      {
         if (*cont != NULL)               /* we have found content already */
         {
            *data = ptr + 1;              /* set ^ data behind this bracket */
            len = ptr - *cont;            /* compute length of content string */
         }
         
         return len;                      /* we're done */
      }
      
      ptr++;                              /* next char */
   }

   return 0;                              /* error */
   
}  /* get_brackets_ptr() */





/*******************************************************************************
*
*  get_two_brackets_ptr():
*     Ermittelt aus einem String wie "!doclayout [ ps, rtf ] [paper] foo bar"
*     die Zeiger auf die ersten Zeichen hinter den ersten [ und die
*     Anzahl der Zeichen, die bis zur ersten ] folgen.
*  
*  Returns:
*     0   : wrong syntax (no brackets [ + ] found)
*     else: length of format and content
*
*  Note: New since r6pl15 [NHz]
*
******************************************|*************************************/

GLOBAL struct size_brackets get_two_brackets_ptr(

char                     *s,             /* ^ string to be checked */
char                    **cont_format,   /* ^ first char of formats */
char                    **cont_content,  /* ^ first char of content */
char                    **data)          /* ^ first char of data */
{
   char                  *ptr;           /* a pointer */
   struct size_brackets   len;           /* computed length */
   BOOLEAN                firstend;      /* flag: TRUE = first ] found in string */
   
   
   ptr = s;                               /* copy pointer as we will change it local */

   *cont_format  = NULL;                  /* nothing found yet */
   *cont_content = NULL;
   *data         = NULL;

   len.format  = 0;                       /* nothing to report yet */
   len.content = 0;
   
   firstend = FALSE;                      /* no closing bracket ] found yet */

   while (*ptr != EOS)
   {
      if ((*ptr=='[') && (!firstend))     /* 1st opening bracket [ found */
      {
         *cont_format = ptr + 1;          /* remind start of format string */
      }
                                          /* 1st closing bracket ] found */
      else if ((*ptr == ']') && (!firstend))
      {
         firstend = TRUE;                 /* format descriptor string is complete */
         len.format = ptr - *cont_format; /* remind length of format */
      }
                                         /* 2nd opening bracket [ found */
      else if ((*ptr == '[') && (firstend))
      {
         *cont_content = ptr + 1;        /* remind start of content string */
      }
                                         /* 2nd closing bracket ] found */ 
      else if ((*ptr == ']') && (firstend))
      {
         if (*cont_content != NULL)      /* we have found content already */
         {
            *data = ptr + 1;             /* set ^ data behind this bracket */
                                         /* compute length of content string */ 
            len.content = ptr - *cont_content;
         }
         
         return len;                     /* we're done */
      }
      
      ptr++;                             /* next char */
   }

   return len;                           /* in case of errors still return len */
   
}  /* get_two_brackets_ptr() */





/* --------------------------------------------------------------
   get_8bit_ptr() ermittelt die Position des ersten 8-Bit-Chars
   eines Strings.
   -> s: Zeiger auf den String
   <- Zeiger auf das erste 8-Bit-Zeichen bzw. NULL, wenn kein
      8-Bit-Zeichen enthalten ist.
   -------------------------------------------------------------- */
GLOBAL char *get_8bit_ptr ( char *s )
{
   char *ptr;
   
   ptr= s;
   
   while ( *ptr!=EOS )
   {  if ( (UCHAR) *ptr > 127 )
      {  return ptr;
      }
      ptr++;
   }
   
   return NULL;
}


/* --------------------------------------------------------------
   get_section_ptr() ermittelt die Position des ersten
   Paragraphen-Zeichens eines Strings, dass bei DOS und OS/2
   unter \025 zu finden ist
   -> s: Zeiger auf den String
   <- Zeiger auf das Zeichen bzw. NULL, wenn nicht enthalten
   -------------------------------------------------------------- */
GLOBAL char *get_section_ptr ( char *s )
{
   char *ptr;
   
   ptr= s;
   
   while ( *ptr!=EOS )
   {  if ( (UCHAR) *ptr == '\025' )
      {  return ptr;
      }
      ptr++;
   }
   
   return NULL;
}  /* get_section_ptr */


/* --------------------------------------------------------------
   get_1stchar_ptr() ermittelt die Position des ersten Zeichens,
   das sich von ' ' und '\t' unterscheidet.
   -> s: Zeiger auf den String
   <- Zeiger auf das erste Zeichen oder NULL, wenn der String
      leer oder nur Blanks und/der TABs enthaelt
   -------------------------------------------------------------- */
GLOBAL char *get_1stchar_ptr ( char *s )
{
   char *ptr;
   
   ptr= s;
   
   while ( *ptr!=EOS )
   {  if ( *ptr!=' ' && *ptr!='\t' )
      {  return ptr;
      }
      ptr++;
   }
   
   return NULL;
}



/* ############################################################
   #
   # Umwandlungsroutinen
   #
   ############################################################   */

/* ----------------------------------------------
   TABs in Leerzeichen umwandeln und dabei die
   Tabposition beachten
   ----------------------------------------------  */
GLOBAL void tabs2spaces (char *s, const int tw)
{
   char n[1024], one[2]={0, 0};
   size_t i, nl;

   /* r6pl2: Wenn !bDocTabwidth==0 dann nicht ersetzen! */
   if (tw==0)
   {  return;
   }

   n[0]= EOS;
   nl= 0;
   
   for (i=0; i<strlen(s); i++)
   {  if (s[i]=='\t')
      {  do
         {  strcat(n, " ");
            nl++;
         }  while ( (nl % tw)!=0 );
      }
      else
      {  one[0]= s[i];
         strcat(n, one);
         nl++;
      }
   }

   strcpy(s, n);  

}  /* tabs2spaces */



/* ----------------------------------------------
   Dezimalzahlen in roemische Zahlen umwandeln
   I =    1     IV      =    4
   V =    5     IX      =    9
   X =   10     XL      =   40
   L =   50     XC      =   90
   C =  100     CD      =  400
   D =  500     CM      =  900
   M = 1000     MCMXCVI = 1996
   ----------------------------------------------  */

GLOBAL char *itoroman ( int value, char *string )
{
   int   t, c, d, o, i;
   
   static const char *cent[]= {  "", "c", "cc", "ccc", "cd", "d", "dc", "dcc", "dccc", "cm"  };
   static const char *deci[]= {  "", "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc"  };
   static const char *ones[]= {  "", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix"  };

   string[0]= '\0';

   if (value<=0)
   {  return(string);
   }
   
   t= value/1000;
   c= (value-t*1000)/100;
   d= (value-t*1000-c*100)/10;
   o= (value-t*1000-c*100-d*10);
   
   
   for (i=0; i<t; i++)  strcat(string, "m") ;

   strcat(string, cent[c]);   
   strcat(string, deci[d]);   
   strcat(string, ones[o]);   
   
   return(string);
}  /* itoroman */


/* ----------------------------------------------
   String in Grossbuchstaben umwandeln
   ----------------------------------------------  */
GLOBAL void my_strupr ( char *string )
{
#if HAVE_STRUPR
   strupr(string);
#else
   size_t i;
   if (string[0]==EOS)
   {  return;
   }
   
   for (i=0; i<strlen(string); i++)
   {  if ( string[i]>='a' && string[i]<='z' )
      {
         string[i] = (char)toupper(string[i]);
      }
   }
#endif
}  /* my_strupr */

/* ----------------------------------------------
   String in Kleinbuchstaben umwandeln
   ----------------------------------------------  */
GLOBAL void my_strlwr ( char *string )
{
#if HAVE_STRLWR
   strlwr(string);
#else
   size_t i;
   if (string[0]==EOS)
   {  return;
   }
   
   for (i=0; i<strlen(string); i++)
   {  if ( string[i]>='A' && string[i]<='Z' )
      {
         string[i] = (char)tolower(string[i]);
      }
   }
#endif
}  /* my_strlwr */





/* New V6.5.20 [gs] */
/*******************************************************************************
*
*  str_din_5007_1():
*     converts a string in DIN 5007-1 style
*
*  Note:
*     use it for glossaries, index pages, etc.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void str_din_5007_1(

char  *string)  /* ^string to be edited */
{
   if (string[0] == EOS)                  /* string is empty? */
      return;                             /* done! */
   
   replace_all(string, "„", "ae");        /* what about ENCODING here? */
   replace_all(string, "”", "oe");
   replace_all(string, "", "ue");
   replace_all(string, "ž", "ss");
   replace_all(string, "Ž", "Ae");
   replace_all(string, "™", "Oe");
   replace_all(string, "š", "Ue");
}





/* New V6.5.20 [gs] */
/*  ----------------------------------------------
    Die nationalen Sonderzeichen werden auf die entsprechenden Vokale umgemappt
    und somit direkt hinter sie sortiert.
    Die Tabelle wandelt auch gleichzeitig nach Grossbuchstaben
    ----------------------------------------------  */

static unsigned char sort_tab[] = 
{
/* 0x00 - 0x0F */   0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,
/* 0x10 - 0x1F */   0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,
/* 0x20 - 0x2F */   0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
/* 0x30 - 0x3F */   0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
/* 0x40 - 0x4F */   0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
/* 0x50 - 0x5F */   0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,
/* 0x60 - 0x6F */   0x60,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
/* 0x70 - 0x7F */   0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x7B,0x7C,0x7D,0x7E,0x7F,
/* 0x80 - 0x8F */   'C' ,'U' ,'E' ,'A' ,'A' ,'A' ,'A' ,'C' ,'E' ,'E' ,'E' ,'I' ,'I' ,'I' ,'A' ,'A' ,
/* 0x90 - 0x9F */   'E' ,'A' ,'A' ,'O' ,'O' ,'O' ,'U' ,'U' ,'Y' ,'O' ,'U' ,0x9B,0x9C,0x9D,0x9E,'E' ,
/* 0xA0 - 0xAF */   'A' ,'I' ,'O' ,'U' ,'N' ,'N' ,'A' ,'O' ,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,
/* 0xB0 - 0xBF */   'A' ,'O' ,'O' ,'O' ,'O' ,'O' ,'A' ,'A' ,'O' ,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF,
/* 0xC0 - 0xCF */   'I' ,'I' ,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD,0xCE,0xCF,
/* 0xD0 - 0xDF */   0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,0xDB,0xDC,0xDD,0xDE,0xDF,
/* 0xE0 - 0xEF */   0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEA,0xEB,0xEC,0xED,0xEE,0xEF,
/* 0xF0 - 0xFF */   0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFA,0xFB,0xFC,0xFD,0xFE,0xFF
};





/*******************************************************************************
*
*  str_sort_cmp():
*     Compares two index entries.
*
*  return:
*     -1: s1  < s2
*      0: s1 == s2
*      1: s1  > s2
*
******************************************|************************************/

GLOBAL int str_sort_cmp(

char              *s1,  /* */
char              *s2)  /* */
{
   unsigned char   c1,  /* */
                   c2;  /* */

   if (!s1)                               /* s1 doesn't exist? */
      return (s2) ? -1 : 0;               /* return s2 > s1 or both don't exist */
   
   if (!s2)                               /* s2 doesn't exist? */
      return 1;                           /* so s1 is greater */

   /* --- replace with more than one character --- */
   replace_all(s1, "ž", "ss");            /* ATARI (?) sslig */
   replace_all(s2, "ž", "ss");            /* ATARI (?) sslig */
   
   do 
   {
      c1 = sort_tab[(unsigned char)*s1];
      c2 = sort_tab[(unsigned char)*s2];

      s1++;
      s2++;
   } 
   while (c1 != '\0' && c1 == c2);


   if (c1 == c2)
      return 0;
   
   if (c1 == '\0')
      return -1;
   
   if (c2 == '\0')
      return 1;
   
   return (c1 - c2);
}





/* ----------------------------------------------
   Strings caseinsensitiv vergleichen
   ----------------------------------------------  */
GLOBAL int my_stricmp ( const char *s1, const char *s2 )
{

#if HAVE_STRICMP
     return stricmp(s1, s2);
#elif HAVE_STRCASECMP
     return strcasecmp(s1, s2);
#else
     return strcmp(s1, s2);
#endif

}  /* my_stricmp */

/* ----------------------------------------------
   Strings caseinsensitiv vergleichen
   max. n Zeichen
   ----------------------------------------------  */
GLOBAL int my_strnicmp ( const char *s1, const char *s2, size_t len )
{

#if HAVE_STRNICMP
   return strnicmp(s1, s2, len);
#else
   return strncmp(s1, s2, len);
#endif

}  /* my_stricmp */

/* ############################################################
   # str.c
   ############################################################   */

