/*******************************************************************************
*
*  Project name : UDO
*  Module name  : str.c
*  Symbol prefix: str
*
*  Description  : This module contains various string manipulation functions.
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
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - tabs2spaces(): check size of n[] (might be 4096 chars now!)
*                 - tabs2spaces(): check new faster method of strcat()
*                 - str_sort_tmp(): add more tables when available
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*    fd  Jan 28: file reformatted and tidied up
*    fd  Feb 09: str_sort_cmp(): done (so far ;-))
*    fd  Feb 16: - str_sort_cmp(): adjusted to new encoding tables
*                - CODE_CP1250_lig, sort_CODE_CP1250 added
*    fd  Feb 17: - CODE_437_lig[], sort_CODE_437[] + CODE_850_lig[], sort_CODE_850[] added
*                - CODE_HP_lig[] + sort_CODE_HP[] added
*                - CODE_NEXT_lig[] + sort_CODE_NEXT[] added
*    fd  Feb 18: - str_UTF_sort_cmp(), str_flatten(), str_sort_flatten_cmp()
*                  CODE_LAT2
*    fd  Feb 19: - CODE_CP1257
*                - str_flatten() debugged for 1-byte encodings
*
******************************************|************************************/

#ifndef ID_STR_C
#define  ID_STR_C
const char *id_str_c= "@(#) str.c       $DATE$";
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
#include "constant.h"                     /* LINELEN */
#include "chr.h"                          /* utf8_to_bstr() */

#include "u_dos.h"
#include "u_hp.h"
#include "u_iso.h"
#include "u_mac.h"
#include "u_mswin.h"
#include "u_next.h"
#include "u_tos.h"
#include "u_utf.h"





/*******************************************************************************
*
*     EXTERNAL REFERENCES
*
******************************************|************************************/

extern int   iEncodingTarget;             /* udo.h: target encoding */









/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  um_strcpy():
*     wrapper for strcpy() which checks buffer borders
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL char *um_strcpy(

char        *dest,         /* */
const char  *src,          /* */
size_t       max,          /* */
const char  *place)        /* */
{
   char      errbuf[120];  /* */
   size_t    slen;         /* temp buffer for the length of src */
   
   
   if (dest == NULL)
   {
      sprintf(errbuf, "um_strcpy: dest is NULL: %s", place);
      loglnposprintf("Warning", errbuf);
      return dest;
   }
   
   if (src == NULL)
   {
      sprintf(errbuf, "um_strcpy: src is NULL: %s", place);
      loglnposprintf("Warning", errbuf);
      dest[0] = EOS;
      return dest;
   }

   slen = (size_t)strlen(src);            /* Stringlaenge bestimmen */
   
   if ( ((size_t)slen + 1) < max)         /* Testen obs  */
   {
      return strcpy(dest, src);
   }
   else
   {
      dest[0] = EOS;
      sprintf(errbuf, "um_strcpy: buffer overrun prevented: %s: %ld>%ld", place, slen + 1, max);
      loglnposprintf("Warning", errbuf);
      return dest;
   }
}





/*******************************************************************************
*
*  um_strncpy():
*     wrapper for strncpy() which checks buffer borders
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL char *um_strncpy(

char        *dest,         /* */
const char  *src,          /* */
size_t       n,            /* */
size_t       max,          /* */
const char  *place)        /* */
{
   char      errbuf[120];  /* */


   if (dest == NULL)
   {
      sprintf(errbuf, "um_strncpy: dest is NULL: %s", place);
      loglnposprintf("Warning", errbuf);
      return dest;
   }
   if (src == NULL)
   {
      sprintf(errbuf, "um_strncpy: src is NULL: %s", place);
      loglnposprintf("Warning", errbuf);
      dest[0] = EOS;
      return dest;
   }

   if ( (n + 1) < max)
   {
      return strncpy(dest, src, n);
   }
   else
   {
      dest[0] = EOS;
      sprintf(errbuf, "um_strncpy: buffer overrun prevented: %s: %ld>%ld", place, n + 1, max);
      loglnposprintf("Warning", errbuf);
      return dest;
   }
}





/*******************************************************************************
*
*  um_strcat():
*     wrapper for strcat() which checks buffer borders
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL char *um_strcat(

char        *dest,         /* */
const char  *src,          /* */
size_t       max,          /* */
const char  *place)        /* */
{
   char      errbuf[120];  /* */
   size_t    dlen,         /* */
             slen;         /* */
            

   if (dest == NULL)
   {
      sprintf(errbuf, "um_strcat: dest is NULL: %s", place);
      loglnposprintf("Warning", errbuf);
      return dest;
   }
   if (src == NULL)
   {
      sprintf(errbuf, "um_strcat: src is NULL: %s", place);
      loglnposprintf("Warning", errbuf);
      return dest;
   }

   dlen = (size_t)strlen(dest);
   slen = (size_t)strlen(src);
   
   if ( (dlen + slen + 1) < max)
   {
      return strcat(dest, src);
   }
   else
   {
      dest[0] = EOS;
      sprintf(errbuf, "um_strcat: buffer overrun prevented: %s: %ld>%ld", place, dlen + slen + 1, max);
      loglnposprintf("Warning", errbuf);
      return dest;
   }
}





/*******************************************************************************
*
*  um_strncat():
*     wrapper for strncat() which checks buffer borders
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL char *um_strncat(

char        *dest,         /* */
const char  *src,          /* */
size_t       n,            /* */
size_t       max,          /* */
const char  *place)        /* */
{
   char      errbuf[120];  /* */
   size_t    dlen;         /* */


   if (dest == NULL)
   {
      sprintf(errbuf, "um_strncat: dest is NULL: %s", place);
      loglnposprintf("Warning", errbuf);
      return dest;
   }
   if (src == NULL)
   {
      sprintf(errbuf, "um_strncat: src is NULL: %s", place);
      loglnposprintf("Warning", errbuf);
      return dest;
   }

   dlen = strlen(dest);
   
   if ( (dlen + n + 1) < max)
   {
      return strncat(dest, src, n);
   }
   else
   {
      dest[0] = EOS;
      sprintf(errbuf, "um_strncat: buffer overrun prevented: %s: %ld>%ld", place, dlen + n + 1, max);
      loglnposprintf("Warning", errbuf);
      return dest;
   }
}





/*******************************************************************************
*
*  um_physical_strcpy():
*     make physical copy of a string
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL char *um_physical_strcpy(

const char  *src,            /* */
size_t       morealloc,      /* # of bytes to allocate for new string, */
                             /*  e.g. when it will become longer than the original */
const char  *place)          /* */
{
   size_t    slen;           /* length of source string */
   char     *dest;           /* pointer to the new string */
   char      placebuf[120];  /* internal buffer for place handling */


   sprintf(placebuf, "%s: um_physical_strcpy", place);

   slen = strlen(src);
   dest = um_malloc(slen + morealloc + 1);

   if (dest != NULL)
   {
      dest = um_strcpy(dest, src, slen + morealloc + 1, placebuf);
   }

   return dest;
}





/*******************************************************************************
*
*  chrcat():
*     concatenate a char to the end of a string
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL char *chrcat(

char        *dest,         /* */
const char   c)            /* */
{
   char      one[2] = "";  /* char buffer string */


   one[0] = c;
   
   return(strcat(dest, one));
}





/*******************************************************************************
*
*  strinsert():
*     insert a string <insert> at the start of string <string>
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL char *strinsert(

char        *string,  /* */
const char  *insert)  /* */
{
   char     *start;   /* ^ to start of string */
   size_t    sl,      /* length of string */
             il;      /* length of insert string */
             
   
   if (insert[0] == '\0')                 /* nothing to do */
      return string;
   
   sl = strlen(string);
   il = strlen(insert);

   start = string;                        /* set ^ to start of string */
   memmove(string + il, string, sl + 1);  /* make space for insert string */
   memcpy(start, insert, il);
   
   return string;
}





/*******************************************************************************
*
*  replace_char():
*     replace all occurrences of <search> by <replace> in <string>
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





/*******************************************************************************
*
*  replace_once():
*     replace first occurrence of <search> by <replace> in <string>
*
*  Return:
*     1: <search> has been replaced
*     0: <search> has not been found
*
******************************************|************************************/

GLOBAL int replace_once(

char        *string,   /* */
const char  *search,   /* */
const char  *replace)  /* */
{
   char     *found;    /* */
   size_t    slen,     /* */
             rlen,     /* */
             flen;     /* */
             
   
   if (string[0] == '\0')                 /* empty string */
      return 0;
      
   if (search[0] == '\0')                 /* nothing to search for */
      return 0;
                                          /* <search> not found */
   if ( (found = strstr(string, search) ) == NULL)
      return 0;

   slen = strlen(search);
   flen = strlen(found);

                                          /* remove <search> */
   memmove(found, found + slen, flen - slen + 1);

   if (replace[0] != EOS)                 /* <replace> may even be empty! */
   {
      rlen = strlen(replace);
      flen = strlen(found);
      
      memmove(found + rlen, found, flen + 1);
      memcpy(found, replace, rlen);
   }
   
   return 1;
}





/*******************************************************************************
*
*  replace_last():
*     replace first occurrence of <search> by <replace> in <string>
*
*  Return:
*     1: <search> has been replaced
*     0: <search> has not been found
*
******************************************|************************************/

GLOBAL int replace_last(

char        *string,   /* */
const char  *search,   /* */
const char  *replace)  /* */
{
   char     *found,    /* */
            *look,     /* */
            *last;     /* */

   if (string[0] == '\0')                 /* empty string */
      return 0;
      
   if (search[0] == '\0')                 /* nothing to search for */
      return 0;
   
   look = string;
   last = NULL;

   while ( (found = strstr(look, search)) != NULL)
   {
      look = found + 1;
      last = found;
   }

   if (last != NULL)                      /* last position of <search> found */
   {
     return (replace_once(last, search, replace));
   }
   
   return 0;
}





/*******************************************************************************
*
*  replace_all():
*     replaces all occurrences of <search> by <replace> in string <source>
*
*  Return:
*     1: <search> has been replaced
*     0: <search> has not been found
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
   if ((found = strstr(source, search)) == NULL )
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





/*******************************************************************************
*
*  qreplace_once():
*     quickly replace first occurrence of <search> by <replace> in <string>
*
*  Notes:
*     In contrary to replace_once(), the lengths of strings are known here 
*     (no strlen() required). This makes this routine much faster.
*
*  Return:
*     1: <search> has been replaced
*     0: <search> has not been found
*
******************************************|************************************/

GLOBAL int qreplace_once(

char          *string,   /* */
const char    *search,   /* */
const size_t   slen,     /* */
const char    *replace,  /* */
const size_t   rlen)     /* */
{
   char       *found;    /* */
   size_t      flen;     /* */

#if CHECK_REPLACE_LEN
   if (rlen != strlen(replace))
   {
      fprintf(stdout, "Fehler in qreplace_once:\n");
      fprintf(stdout, "slen= %d\n", slen);
      fprintf(stdout, "strlen(%s)= %d\n", search, strlen(search));
   }
   
   if (rlen != strlen(by))
   {
      fprintf(stdout, "Fehler in qreplace_once:\n");
      fprintf(stdout, "rlen= %d\n", rlen);
      fprintf(stdout, "strlen(%s)= %d\n", replace, strlen(replace));
   }
#endif
   
   if (string[0] == '\0')                 /* empty string */
      return 0;
      
   if (search[0] == '\0')                 /* nothing to search for */
      return 0;
                                          /* <search> not found */

   if ( (found = strstr(string, search)) == NULL)
      return 0;

   flen = strlen(found);                  /* get length of remaining edit string */

                                          /* Zu Ersetzendes entfernen */
   memmove(found, found + slen, flen - slen + 1);

   if (replace[0] != EOS)                 /* replacement string must not be empty! */
   {
      flen = strlen(found);               /* get new length of remaining edit string */
                                          /* Platz schaffen fuer neues und dorthin kopieren */
      memmove(found + rlen, found, flen + 1);
      memcpy(found, replace, rlen);       /* insert replacement string */
   }
   
   return 1;                              /* done! */
}





/*******************************************************************************
*
*  qreplace_last():
*     quickly replace last occurrence of <search> by <replace> in <string>
*
*  Notes:
*     In contrary to replace_last(), the lengths of strings are known here 
*     (no strlen() required). This makes this routine much faster.
*
*  Return:
*     1: <search> has been replaced
*     0: <search> has not been found
*
******************************************|************************************/

GLOBAL int qreplace_last(

char          *string,
const char    *search,
const size_t   slen,
const char    *replace,
const size_t   rlen)
{
   char       *found, 
              *look, 
              *last;

#if CHECK_REPLACE_LEN
   if (slen != strlen(search))
   {
      fprintf(stdout, "Fehler in qreplace_last:\n");
      fprintf(stdout, "slen = %d\n", slen);
      fprintf(stdout, "strlen(%s)= %d\n", search, strlen(search));
   }
   
   if (rlen != strlen(replace))
   {
      fprintf(stdout, "Fehler in qreplace_last:\n");
      fprintf(stdout, "rlen = %d\n", rlen);
      fprintf(stdout, "strlen(%s)= %d\n", replace, strlen(replace));
   }
#endif

   if (string[0] == '\0')                 /* empty string */
      return 0;
      
   if (search[0] == '\0')                 /* nothing to search for */
      return 0;
   
   look = string;
   last = NULL;

   while ( (found = strstr(look, search)) != NULL)
   {
      look = found + 1;
      last = found;
   }

   if (last != NULL)                      /* last position of <search> found */
   {
      return (qreplace_once(last, search, slen, replace, rlen) );
   }
   
   return 0;
}





/*******************************************************************************
*
*  qreplace_all():
*     replace all <rep> by <by> in <s>
*
*  return:
*     1 = replacement was successful
*     0 = nothing replaced
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

   if ((found = strstr(source, replace)) == NULL)
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





/*******************************************************************************
*
*  delete_once():
*     delete first occurrence of a char in a string
*
*  Return:
*     1 = replacement was successful
*     0 = nothing replaced
*
******************************************|************************************/

GLOBAL int delete_once(

char        *source,     /* */
const char  *to_delete)  /* */
{
   return (replace_once(source, to_delete, ""));
}





/*******************************************************************************
*
*  delete_last():
*     delete last occurrence of a char in a string
*
*  Return:
*     1 = replacement was successful
*     0 = nothing replaced
*
******************************************|************************************/


GLOBAL int delete_last(

char        *source,     /* */
const char  *to_delete)  /* */
{
   return (replace_last(source, to_delete, ""));
}





/*******************************************************************************
*
*  delete_all():
*     delete all occurrences of a char in a string
*
*  Return:
*     1 = replacement was successful
*     0 = nothing replaced
*
******************************************|************************************/


GLOBAL int delete_all(

char        *source,     /* */
const char  *to_delete)  /* */
{
   return (replace_all(source, to_delete, ""));
}





/*******************************************************************************
*
*  qdelete_once():
*     quickly delete first occurrence of a char in a string
*
*  Return:
*     1 = replacement was successful
*     0 = nothing replaced
*
******************************************|************************************/

GLOBAL int qdelete_once(

char          *source,     /* */
const char    *to_delete,  /* */
const size_t   dlen)       /* */
{
   return (qreplace_once (source, to_delete, dlen, "", 0));
}





/*******************************************************************************
*
*  qdelete_last():
*     quickly delete last occurrence of a char in a string
*
*  Return:
*     1 = replacement was successful
*     0 = nothing replaced
*
******************************************|************************************/


GLOBAL int qdelete_last(

char          *source,     /* */
const char    *to_delete,  /* */
const size_t   dlen)       /* */
{
   return (qreplace_last (source, to_delete, dlen, "", 0));
}





/*******************************************************************************
*
*  qdelete_all():
*     quickly delete all occurrences of a char in a string
*
*  Return:
*     1 = replacement was successful
*     0 = nothing replaced
*
******************************************|************************************/


GLOBAL int qdelete_all(

char          *source,     /* */
const char    *to_delete,  /* */
const size_t   dlen)       /* */
{
   return (qreplace_all (source, to_delete, dlen, "", 0));
}





/*******************************************************************************
*
*  del_right_spaces():
*     delete spaces at the end of a string (aka "right_trim")
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void del_right_spaces(

char       *s)   /* ^ string */
{
   size_t   sl;  /* length of string */
   
   
   sl = strlen(s);                        /* get length of string */

   while ( (sl > 0) && (s[sl - 1] == ' ') )
   {
      s[sl - 1] = EOS;
      sl--;
   }
}





/*******************************************************************************
*
*  del_whitespaces():
*     delete spaces and tabs at the beginning and end of string
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void del_whitespaces(

char       *s)         /* ^ string */
{
   size_t   sl;        /* length of string */
   char    *p1st = s;  /* ^ start of string */
   
   
                                          /* find first space or tab */
   while (*p1st != EOS && (*p1st == ' ' || *p1st == '\t') )
   {
      ++p1st;
   }

   sl = strlen(p1st);                     /* get length of remaining string */
   
   if ( (*p1st != EOS) && (s != p1st) )
   {  
      memmove(s, p1st, sl + 1);
   }
   
   if (sl > 0)                            /* remove right spaces and tabs */
   {
      p1st = s + sl - 1;                  /* set ^ to end of string */
      
      while (*p1st == ' ' || *p1st == '\t')
         --p1st;
         
      p1st[1] = EOS;
   }
}





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
}





/*******************************************************************************
*
*  get_8bit_ptr():
*     get first position of a 8bit (> ASCII 127) char in a string
*
*  Return:
*     position of char in string
*     NULL, if no 8bit char has been found
*
******************************************|************************************/

GLOBAL char *get_8bit_ptr(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ to string */
   
   
   ptr = s;                               /* start */
   
   while (*ptr != EOS)                    /* check whole string */
   {
      if ((UCHAR)*ptr > 127)              /* gotcha! */
         return ptr;
      
      ptr++;                              /* next char */
   }
   
   return NULL;                           /* nothing found */
}





/*******************************************************************************
*
*  get_section_ptr():
*     get first position of DOS or OS/2 section character in a string
*
*  Notes:
*     DOS an OS/2 use \025 for the section character (paragraph sign)
*
*  Return:
*     position of char in string
*     NULL, if char has not been found
*
******************************************|************************************/

GLOBAL char *get_section_ptr(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ to string */
   
   
   ptr = s;                               /* start */
   
   while (*ptr != EOS)                    /* check whole string */
   {
      if ((UCHAR)*ptr == '\025')          /* gotcha! */
         return ptr;
      
      ptr++;                              /* next char */
   }
   
   return NULL;                           /* nothing found */
}





/*******************************************************************************
*
*  get_1stchar_ptr():
*     get first position of a character other than space and tab in a string
*
*  Return:
*     position of char in string
*     NULL, if char has not been found
*
******************************************|************************************/

GLOBAL char *get_1stchar_ptr(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ to string */
   
   
   ptr = s;                               /* start */
   
   while (*ptr != EOS)                    /* check whole string */
   {
                                          /* gotcha! */
      if ( (*ptr != ' ') && (*ptr != '\t') )
         return ptr;
      
      ptr++;                              /* next char */
   }
   
   return NULL;                           /* nothing found */
}





/*******************************************************************************
*
*  tabs2spaces():
*     convert tabs into spaces, respecting the tab position
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void tabs2spaces(

char       *s,            /* ^ string */
const int   tw)           /* tab width */
{
   char     n[1024];      /* buffer for converted string */
#if 0
   char     one[2] = "";  /* char buffer string */
#endif
   size_t   i,            /* counter */
            nl;           /* length of buffer string */
            

   if (tw == 0)                           /* don't replace Null sized tabs! */
      return;

   n[0] = EOS;                            /* clear buffer */
   
   nl = 0;
   
   for (i = 0; i < strlen(s); i++)        /* check whole string */
   {
      if (s[i] == '\t')                   /* tab found! */
      {
         do
         {
            strcat(n, " ");               /* add as many spaces as required */
            nl++;
         } while ( (nl % tw) != 0);       /* by tab width */
      }
#if 0
      /* fd:2010-01-28: old method, seems to be unneccessary */
      
      else                                /* other char found */
      {
         one[0] = s[i];                   /* buffer this char */
         strcat(n, one);                  /* attach this char to n[] */
         nl++;                            /* increase length of n */
      }
#endif
      else
      {
         n[nl] = s[i];
         nl++;
      }
   }

   strcpy(s, n);                          /* return converted string */
}





/*******************************************************************************
*
*  itoroman():
*     convert decimal number into Roman (lowercase!) numbers string
*
*  Notes:
*     I =    1     IV      =    4
*     V =    5     IX      =    9
*     X =   10     XL      =   40
*     L =   50     XC      =   90
*     C =  100     CD      =  400
*     D =  500     CM      =  900
*     M = 1000     MCMXCVI = 1996
*
*  Return:
*     converted string
*
******************************************|************************************/

GLOBAL char *itoroman(

int      value,   /* decimal value to be converted */
char    *string)  /* ^ result string */
{
   int   m,       /* thousands */
         c,       /* hundreds */
         d,       /* tenths */
         o,       /* ones */
         i;       /* counter */
   
   static const char *ones[] = {"", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix"};
   static const char *cent[] = {"", "c", "cc", "ccc", "cd", "d", "dc", "dcc", "dccc", "cm"};
   static const char *deci[] = {"", "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc"};

   string[0] = '\0';                      /* clear result string */

   if (value <= 0)                        /* no negative or zero values! */
      return (string);
   
   
   m = value / 1000;                      /* decompose value */
   c = (value - m * 1000) / 100;
   d = (value - m * 1000  - c * 100) / 10;
   o = (value - m * 1000  - c * 100 - d * 10);
   
   for (i = 0; i < m; i++)                /* add thousands first */
      strcat(string, "m") ;

   strcat(string, cent[c]);               /* add hundreds */
   strcat(string, deci[d]);               /* add tenths */
   strcat(string, ones[o]);               /* add ones */
   
   return (string);
}





/*******************************************************************************
*
*  my_strupr():
*     convert string to uppercase
*
*  Notes:
*     This is a wrapper for strupr() in case it isn't available in a system.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void my_strupr(

char  *string)  /* ^ string */
{
#if HAVE_STRUPR
   strupr(string);
#else

   size_t   i;  /* counter */
   
   
   if (string[0] == EOS)                  /* empty string */
      return;
   
   for (i = 0; i < strlen(string); i++)   /* whole string */
   {
      if (string[i] >= 'a' && string[i] <= 'z')
      {
         string[i] = (char)toupper(string[i]);
      }
   }
#endif
}





/*******************************************************************************
*
*  my_strlwr():
*     convert string to lowercase
*
*  Notes:
*     This is a wrapper for strlwr() in case it isn't available in a system.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void my_strlwr(

char  *string)  /* ^ string */
{
#if HAVE_STRLWR
   strlwr(string);
#else

   size_t   i;  /* counter */
   
   
   if (string[0] == EOS)                  /* empty string */
      return;
   
   for (i = 0; i < strlen(string); i++)   /* whole string */
   {
      if (string[i] >= 'A' && string[i] <= 'Z')
      {
         string[i] = (char)tolower(string[i]);
      }
   }
#endif
}





/*******************************************************************************
*
*  my_stricmp():
*     compare two strings case-insensitive
*
*  Notes:
*     This is a wrapper for stricmp() in case it isn't available in a system.
*
*     HAVE_STRICMP and HAVE_STRCASECMP are defined in version.h
*
*  Return:
*     result of relevant comparison function
*
******************************************|************************************/

GLOBAL int my_stricmp(

const char  *s1,  /* ^ 1st string */
const char  *s2)  /* ^ 2nd string */
{

#if HAVE_STRICMP
     return stricmp(s1, s2);
#elif HAVE_STRCASECMP
     return strcasecmp(s1, s2);
#else
     return strcmp(s1, s2);
#endif
}





/*******************************************************************************
*
*  my_strnicmp():
*     compare a maximum of <n> characters in two strings case-insensitive
*
*  Notes:
*     This is a wrapper for strnicmp() in case it isn't available in a system.
*
*     HAVE_STRNICMP is defined in version.h
*
*  Return:
*     result of relevant comparison function
*
******************************************|************************************/

GLOBAL int my_strnicmp(

const char  *s1,   /* ^ 1st string */
const char  *s2,   /* ^ 2nd string */
size_t       len)  /* # of chars to compare */
{
#if HAVE_STRNICMP
   return strnicmp(s1, s2, len);
#else
   return strncmp(s1, s2, len);
#endif
}





/*******************************************************************************
*
*  str_flatten():
*     flatten a given string to 7bit-ASCII
*
*  Notes:
*     Because qsort() is implemented in a way that the structures which have to
*     be compared cannot be changed, we cannot get this sort char directly in 
*     the routines which are used for comparison (e.g. str_sort_cmp()).
*
*  return:
*     <zeile> -> flattened
*     1st char
*
******************************************|************************************/

GLOBAL char str_flatten(

char  *zeile)  /* ^ string */
{
   int        i = 0;          /* counter for table entries */
   int        j = 0;          /* counter for chars of <zeile> */
   int        len;            /* indicator for byte length of UTF char */
   unsigned (*plig)[3];       /* ^ to CODE_xxx_lig[][] arrays */
   unsigned (*psort);         /* ^ to sort_CODE_xxx[] arrays */
   unsigned (*pusort)[2];     /* ^ to sort_CODE_UTF[] array */
   char       sbuf[LINELEN];  /* line buffer */
   char       cbuf[9];        /* chars buffer */
   char       lgc[2] = "";    /* ligature char buffer */
   char       lig[3] = "";    /* ligature string buffer */
   char      *psbuf;          /* ^ string begin */
   unsigned   idx;            /* Unicode */
   size_t     c1;             /* char value (up to 4 bytes!) */
   int        found;          /* TRUE: Unicode found in relevant table */


   if (!zeile)                            /* empty string? */
      return EOS;
   
   if (iEncodingTarget == CODE_UTF8)      /* Unicode first */
   {
      plig   = CODE_UTF_lig;
      pusort = sort_CODE_UTF;

      memset(sbuf,0,LINELEN);
      memset(cbuf,0,9);
      
      for (j = 0; j < strlen(zeile); j++)
      {
         idx = (UCHAR)zeile[j];
         
         if (idx < 128)                   /* 0000 0000-0000 007F 0xxxxxxx */
         {
            cbuf[0] = idx;
            cbuf[1] = EOS;
            strcat(sbuf,cbuf);
            len = 0;
         }
         else if ((idx & 0xE0) == 0xC0)   /* 0000 0080-0000 07FF 110xxxxx 10xxxxxx */
         {
            cbuf[0] = idx;
            j++;
            cbuf[1] = (UCHAR)zeile[j];
            cbuf[2] = EOS;
            len = 2;
         }
         else if ((idx & 0xF0) == 0xE0)   /* 0000 0800-0000 FFFF 1110xxxx 10xxxxxx 10xxxxxx */
         {
            cbuf[0] = idx;
            j++;
            cbuf[1] = (UCHAR)zeile[j];
            j++;
            cbuf[2] = (UCHAR)zeile[j];
            cbuf[3] = EOS;
            len = 3;
         }
         else if ((idx & 0xF8) == 0xF0)   /* 0001 0000-001F FFFF 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
         {
            cbuf[0] = idx;
            j++;
            cbuf[1] = (UCHAR)zeile[j];
            j++;
            cbuf[2] = (UCHAR)zeile[j];
            j++;
            cbuf[3] = (UCHAR)zeile[j];
            cbuf[4] = EOS;
            len = 4;
         }
       
         if (len > 0)
         {
            idx = utf8_to_bstr(cbuf,len);
            found = FALSE;
            i = 0;
         
            while (plig[i][0] != 0x00)    /* is it a ligature? */
            {
               if (idx == plig[i][0])     /* ligature character found */
               {
                  cbuf[0] = plig[i][1];   /* compose ligature replacement string */
                  cbuf[1] = plig[i][2];   /* lig[2] must always be 0 (C string!) */
                  cbuf[2] = EOS;
                  strcat(sbuf,cbuf);
                  found = TRUE;           /* this character is done! */
               }

               if (found)                 /* was a ligature */
                  break;
            
               i++;                       /* check next ligature */
            }
             
            if (!found)                   /* was a ligature */
            {
               i = 0;
         
                                          /* is it a Unicode which we should replace? */
               while (pusort[i][0] != 0x00)
               {
                                          /* Unicode found */
                  if (idx == pusort[i][0])
                  {
                     cbuf[0] = pusort[i][1];
                     cbuf[1] = EOS;
                     strcat(sbuf,cbuf);
                     found = TRUE;
                  }
            
                  if (found)
                     break;
             
                  i++;
               }
            }
         }
         
      }  /* for (j ...) */
         
      strcpy(zeile,sbuf);                 /* restore line */
         
      zeile = strupr(zeile);              /* we want to compare UPPERCASE */
      
      return zeile[0];                    /* used for Index page */
   }
   

   switch (iEncodingTarget)               /* 1-byte encodings */
   {
   case CODE_437:
      plig = CODE_437_lig;
      psort = sort_CODE_437;
      break;
   
   case CODE_850:
      plig = CODE_850_lig;
      psort = sort_CODE_850;
      break;
   
   case CODE_CP1250:
      plig = CODE_CP1250_lig;
      psort = sort_CODE_CP1250;
      break;
   
   case CODE_CP1257:
      plig = CODE_CP1257_lig;
      psort = sort_CODE_CP1257;
      break;
   
   case CODE_HP8:
      plig  = CODE_HP8_lig;
      psort = sort_CODE_HP8;
      break;
   
   case CODE_LAT2:
      plig  = CODE_LAT2_lig;
      psort = sort_CODE_LAT2;
      break;
   
   case CODE_MAC:
      plig  = CODE_MAC_lig;
      psort = sort_CODE_MAC;
      break;
   
   case CODE_NEXT:
      plig  = CODE_NEXT_lig;
      psort = sort_CODE_NEXT;
      break;
   
   case CODE_TOS:
      plig  = CODE_TOS_lig;
      psort = sort_CODE_TOS;
      break;
   
   case CODE_LAT1:
   default:
      plig  = CODE_LAT1_lig;
      psort = sort_CODE_LAT1;
   }


   /* --- resolve ligature characters with more than one character --- */
   
   while (plig[i][0] != 0x00)             /* EOL not reached */
   {
      lgc[0] = plig[i][0];                /* get ligature character */
                                          /* lgc[1] must always be 0 (C string!) */
      
      lig[0] = plig[i][1];                /* compose ligature replacement string */
      lig[1] = plig[i][2];                /* lig[2] must always be 0 (C string!) */

      replace_all(zeile, lgc, lig);

      i++;                                /* next ligature */
   }

   psbuf = zeile;                         /* remember begin of string */
   
   do                                     /* flatten extended characters */
   {
      c1 = psort[*zeile & 0x00FF];
      *zeile++ = c1;
   }
   while (c1 != EOS);

   zeile = strupr(psbuf);                 /* restore ^ to begin of string */

   return zeile[0];                       /* used for Index page */
}





/*******************************************************************************
*
*  str_sort_flatten_cmp():
*     flatten two strings and compare them
*
*  return:
*     -1: s1  < s2
*      0: s1 == s2
*      1: s1  > s2
*
******************************************|************************************/

GLOBAL int str_sort_flatten_cmp(

char         *s1,           /* ^ 1st string for comparison */
char         *s2)           /* ^ 2nd string for comparison */
{
   int        i = 0;        /* counter */
   size_t     c1,           /* Unicode char value (up to 4 bytes!) */
              c2;           /* Unicode char value (up to 4 bytes!) */
   char       lgc[2] = "";  /* ligature char buffer */
   char       lig[3] = "";  /* ligature string buffer */
   unsigned (*psort);       /* ^ to sort_CODE_xxx[] arrays */
   unsigned (*pumap);       /* ^ to u_CODE_xxx[] arrays */
   unsigned (*plig)[3];     /* ^ to CODE_xxx_lig[][] arrays */
   char      *psbuf;        /* ^ char begin */
   size_t     len1,         /* length of original 1st string */
              len2;         /* length of original 2nd string */
   
            
   if (!s1)                               /* s1 doesn't exist? */
      return (s2) ? -1 : 0;               /* return s2 > s1 or both don't exist */
   
   if (!s2)                               /* s2 doesn't exist? */
      return 1;                           /* so s1 is greater */


   switch (iEncodingTarget)               /* use the right tables! ;-) */
   {
   case CODE_437:
      plig = CODE_437_lig;
      psort = sort_CODE_437;
      pumap = u_CODE_437;
      break;
   
   case CODE_850:
      plig = CODE_850_lig;
      psort = sort_CODE_850;
      pumap = u_CODE_850;
      break;
   
   case CODE_CP1250:
      plig = CODE_CP1250_lig;
      psort = sort_CODE_CP1250;
      pumap = u_CODE_CP1250;
      break;
   
   case CODE_CP1257:
      plig = CODE_CP1257_lig;
      psort = sort_CODE_CP1257;
      pumap = u_CODE_CP1257;
      break;
   
   case CODE_HP8:
      plig  = CODE_HP8_lig;
      psort = sort_CODE_HP8;
      pumap = u_CODE_HP8;
      break;
   
   case CODE_LAT2:
      plig  = CODE_LAT2_lig;
      psort = sort_CODE_LAT2;
      pumap = u_CODE_LAT2;
      break;
   
   case CODE_MAC:
      plig  = CODE_MAC_lig;
      psort = sort_CODE_MAC;
      pumap = u_CODE_MAC;
      break;
   
   case CODE_NEXT:
      plig  = CODE_NEXT_lig;
      psort = sort_CODE_NEXT;
      pumap = u_CODE_NEXT;
      break;
   
   case CODE_TOS:
      plig  = CODE_TOS_lig;
      psort = sort_CODE_TOS;
      pumap = u_CODE_TOS;
      break;
   
   case CODE_LAT1:
   default:
      plig  = CODE_LAT1_lig;
      psort = sort_CODE_LAT1;
      pumap = u_CODE_LAT1;
   }
   
   UNUSED(pumap);
   
   len1 = strlen(s1);
   len2 = strlen(s2);
   
   
   /* --- resolve ligature characters with more than one character --- */
   
   while (plig[i][0] != 0x00)             /* EOL not reached */
   {
      lgc[0] = plig[i][0];                /* get ligature character */
                                          /* lgc[1] must always be 0 (C string!) */
      
      lig[0] = plig[i][1];                /* compose ligature replacement string */
      lig[1] = plig[i][2];                /* lig[2] must always be 0 (C string!) */

      replace_all(s1, lgc, lig);
      replace_all(s2, lgc, lig);

      i++;                                /* next ligature */
   }


   /* --- 'flatten' extended characters --- */
   
   psbuf = s1;                            /* remember begin of 1st string */
   
   do
   {
      c1 = psort[*s1 & 0x00FF];
      *s1++ = c1;
   }
   while (c1 != EOS);
   
   s1 = psbuf;                            /* restore ^ 1st string */
   
   psbuf = s2;                            /* remember begin of 2nd string */
   
   do
   {
      c2 = psort[*s2 & 0x00FF];
      *s2++ = c2;
   }
   while (c2 != EOS);
   
   s2 = psbuf;                            /* restore ^ 2nd string */
   
   
   s1 = strupr(s1);                       /* we compare UPPERCASE */
   s2 = strupr(s2);

   
   do                                     /* --- compare characters --- */
   {
      c1 = *s1;
      c2 = *s2;
      
      s1++;
      s2++;
   }
   while (c1 != '\0' && c1 == c2);
   
   
   /* --- result --- */
   
   if (c1 == c2)                          /* strings seem to be identical */
   {
      if (len1 == len2)                   /* even string lengths are identical */
         return 0;                        /* THEY ARE IDENTICAL! */
      
      return (len1 < len2) ? 1 : -1;      /* compare string lengths of originals */
                                          /* e.g. 'ae' is lower than '"a' */
   }

   return (c1 < c2) ? -1 : 1;
}





/*******************************************************************************
*
*  str_UTF_sort_cmp():
*     compares two Unicode encoded strings
*
*  return:
*     -1: s1  < s2
*      0: s1 == s2
*      1: s1  > s2
*
******************************************|************************************/

GLOBAL int str_UTF_sort_cmp(

char         *s1,             /* ^ 1st string for comparison */
char         *s2)             /* ^ 2nd string for comparison */
{
   int        i = 0;          /* counter for table entries */
   int        j = 0;          /* counter for chars of <zeile> */
   int        k = 0;          /* counter for s1 + s2 */
   int        len;            /* indicator for byte length of UTF char */
   size_t     c1,             /* Unicode char value (up to 4 bytes!) */
              c2;             /* Unicode char value (up to 4 bytes!) */
   unsigned (*psort)[2];      /* ^ to sort_CODE_xxx[] arrays */
   unsigned (*plig)[3];       /* ^ to CODE_xxx_lig[][] arrays */
   size_t     len1,           /* length of original 1st string */
              len2;           /* length of original 2nd string */
   char       sbuf[LINELEN];  /* line buffer */
   char       cbuf[9];        /* chars buffer */
   unsigned   idx;            /* Unicode */
   int        found;          /* TRUE: Unicode found in relevant table */
   char      *zeile;          /* ^ to s1 or s2 */
   
            
   if (!s1)                               /* s1 doesn't exist? */
      return (s2) ? -1 : 0;               /* return s2 > s1 or both don't exist */
   
   if (!s2)                               /* s2 doesn't exist? */
      return 1;                           /* so s1 is greater */


   switch (iEncodingTarget)               /* use the right tables! ;-) */
   {
   case CODE_UTF8:
      plig  = CODE_UTF_lig;
      psort = sort_CODE_UTF;
   }
   
   
   if (iEncodingTarget == CODE_UTF8)      /* convert UTF-8 to 1-byte format first */
   {
      for (k = 0; k < 2; k++)
      {
         if (k == 0)
            zeile = s1;
         else
            zeile = s2;         
      
         memset(sbuf,0,LINELEN);
         memset(cbuf,0,9);
      
         for (j = 0; j < strlen(zeile); j++)
         {
            idx = (UCHAR)zeile[j];
         
            if (idx < 128)                /* 0000 0000-0000 007F 0xxxxxxx */
            {
               cbuf[0] = idx;
               cbuf[1] = EOS;
               strcat(sbuf,cbuf);
               len = 0;
            }
            else if ((idx & 0xE0) == 0xC0)/* 0000 0080-0000 07FF 110xxxxx 10xxxxxx */
            {
               cbuf[0] = idx;
               j++;
               cbuf[1] = (UCHAR)zeile[j];
               cbuf[2] = EOS;
               len = 2;
            }
            else if ((idx & 0xF0) == 0xE0)/* 0000 0800-0000 FFFF 1110xxxx 10xxxxxx 10xxxxxx */
            {
               cbuf[0] = idx;
               j++;
               cbuf[1] = (UCHAR)zeile[j];
               j++;
               cbuf[2] = (UCHAR)zeile[j];
               cbuf[3] = EOS;
               len = 3;
            }
            else if ((idx & 0xF8) == 0xF0)/* 0001 0000-001F FFFF 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
            {
               cbuf[0] = idx;
               j++;
               cbuf[1] = (UCHAR)zeile[j];
               j++;
               cbuf[2] = (UCHAR)zeile[j];
               j++;
               cbuf[3] = (UCHAR)zeile[j];
               cbuf[4] = EOS;
               len = 4;
            }
         
            if (len > 0)
            {
               idx = utf8_to_bstr(cbuf,len);
               found = FALSE;
               i = 0;
            
               while (plig[i][0] != 0x00) /* is it a ligature? */
               {
                  if (idx == plig[i][0])  /* ligature character found */
                  {
                     cbuf[0] = plig[i][1];/* compose ligature replacement string */
                     cbuf[1] = plig[i][2];/* lig[2] must always be 0 (C string!) */
                     cbuf[2] = EOS;
                     strcat(sbuf,cbuf);
                     found = TRUE;        /* this character is done! */
                  }

                  if (found)              /* was a ligature */
                     break;
               
                  i++;                    /* check next ligature */
               }
             
               if (!found)                /* was a ligature */
               {
                  i = 0;
            
                                          /* is it a Unicode which we should replace? */
                  while (psort[i][0] != 0x00)
                  {
                                          /* Unicode found */
                     if (idx == psort[i][0])
                     {
                        cbuf[0] = psort[i][1];
                        cbuf[1] = EOS;
                        strcat(sbuf,cbuf);
                        found = TRUE;
                     }
               
                     if (found)
                        break;
               
                     i++;
                  }
               }
            }
            
         }  /* for (j ...) */
         
         strcpy(zeile,sbuf);              /* restore line */
         
      }  /* for (k ...) */
      
   }

   s1 = strupr(s1);                       /* we compare UPPERCASE */
   s2 = strupr(s2);
   
   len1 = strlen(s1);
   len2 = strlen(s2);

   
   do                                     /* --- compare characters --- */
   {
      c1 = *s1;
      c2 = *s2;
      
      s1++;
      s2++;
   }
   while (c1 != '\0' && c1 == c2);
   
   
   /* --- result --- */
   
   if (c1 == c2)                          /* strings seem to be identical */
   {
      if (len1 == len2)                   /* even string lengths are identical */
         return 0;                        /* THEY ARE IDENTICAL! */
      
      return (len1 < len2) ? 1 : -1;      /* compare string lengths of originals */
                                          /* e.g. 'ae' is lower than '"a' */
   }

   return (c1 < c2) ? -1 : 1;
}





/*******************************************************************************
*
*  str_sort_cmp():
*     Compares two ASCII (!) index entries.
*
*  return:
*     -1: s1  < s2
*      0: s1 == s2
*      1: s1  > s2
*
******************************************|************************************/

GLOBAL int str_sort_cmp(

char         *s1,           /* ^ 1st string for comparison */
char         *s2)           /* ^ 2nd string for comparison */
{
   size_t     c1,           /* char value (up to 4 bytes!) */
              c2;           /* char value (up to 4 bytes!) */
   
            
   if (!s1)                               /* s1 doesn't exist? */
      return (s2) ? -1 : 0;               /* return s2 > s1 or both don't exist */
   
   if (!s2)                               /* s2 doesn't exist? */
      return 1;                           /* so s1 is greater */


   s1 = strupr(s1);                       /* we compare UPPERCASE */
   s2 = strupr(s2);

   
   do                                     /* --- compare characters --- */
   {
      c1 = *s1;
      c2 = *s2;
      
      s1++;
      s2++;
   }
   while (c1 != '\0' && c1 == c2);
   
   
   /* --- result --- */
   
   if (c1 == c2)                          /* strings seem to be identical */
      return 0;

   return (c1 < c2) ? -1 : 1;
}


/* +++ EOF +++ */
