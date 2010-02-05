/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : chr.c
*  Symbol prefix: chr
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
*  Description  : This module contains routines which convert strings between ISO and
*                 the system font. There are also function which replace character.
*                 
*
*-------------------------------------------------------------------------------
*
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Ulf Dunkel (fd), Gerhard Stoll (ggs)
*  Write access : fd, ggs
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : re-write UDO string and encoding engine for full Unicode support 
*
*-------------------------------------------------------------------------------
*  History:
*
*  2008:
*    fd  Nov 14: indexudo.html now capitalizes the A-Z jump labels (issue #76 solved)
*    ggs Dec 12: output for ST-Guide and PureC Help always uses CODE_TOS
*  2010:
*    fd  Jan 26: file reformatted and tidied up
*
******************************************|************************************/

/*******************************************************************************
*
*     CONSTANTS
*
******************************************|************************************/

#ifndef ID_CHARS_C
#define ID_CHARS_C
const char *id_chr_c= "@(#) chr.c       $DATE$";
#endif





/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "portab.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "msg.h"
#include "str.h"
#include "sty.h"
#include "tp.h"
#include "udo.h"
#include "chr_all.h"
#include "chr_ttf.h"
#include "ansi2dos.h"

#ifdef __TOS__
#include "chr_tos.h"
#else
#include "tos2iso.h"
#include "iso2tos.h"
#endif

#ifdef __MSDOS__
#include "chr_437.h"
#else
#include "437iso.h"
#endif

#ifdef __MSDOS850__
#include "chr_850.h"
#else
#include "850iso.h"
#endif

#ifdef __HPUX_ROMAN8__
#include "chr_hp8.h"
#else
#include "hp82iso.h"
#endif

#if __NEXTSTEP__
#include "chr_next.h"
#else
#include "next2iso.h"
#endif

/* #if __BEOS__           */
/* #include "chr_utf8.h"  */
/* #else                  */
/* #include "utf82iso.h"  */
/* #endif                 */

#include "utf82iso.h"

#if __MACOS__
#include "chr_mac.h"
#else
#include "mac2iso.h"
#endif

#if __MACOSX__
#include "chr_mac.h"
#else
#include "mac2iso.h"
#endif

#if USE_LATIN1_CHARSET
#include "chr_iso.h"
#endif

#include "export.h"
#include "chr.h"





/*******************************************************************************
*
*     INCLUDE ERRORS
*
******************************************|************************************/

#ifndef MAXTEX7BIT
#error  "MAXTEX7BIT not defined!"
#endif

#ifndef MAXRTF7BIT
#error  "MAXRTF7BIT not defined!"
#endif

#ifndef MAXWIN7BIT
#error  "MAXWIN7BIT not defined!"
#endif

#ifndef MAXHTML7BIT
#error  "MAXHTML7BIT not defined!"
#endif

#ifndef MAXLDS7BIT
#error  "MAXLDS7BIT not defined!"
#endif

#ifndef MAXHTAG7BIT
#error  "MAXHTAG7BIT not defined!"
#endif










/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _quotecommand
{
  char    *cmd;                           /* String PL6: vorher UCHAR */
  size_t   cmdlen;                        /* Laenge des Kommandos (need speed ;-))*/
  char    *abb;                           /* Kommandoabkuerzung */
  size_t   abblen;                        /* Laenge der Abkuerzung */
} QUOTECOMMAND;





/*******************************************************************************
*
*     UNINITIALIZED VARIABLES
*
******************************************|************************************/

LOCAL BOOLEAN   last_aqc_verb;            /* */
LOCAL int       texinfo_np_counter;       /* Non-Printable-Texinfo-Node-Counter ;-) */


LOCAL char *html_specs[HTML_SPEC_MAX] =   /* list of supported HTML specials */
{
   {"&hellip;"},
   {"&mdash;"},
   {"&ndash;"},
   {"&shy;"}
};


/*      ############################################################
        #
        # Automatisches Quoten von kritischen Zeichen dort, wo kein
        # (!V)/(!v) benutzt wird und kein !tex, !=tex etc. am
        # Zeilenanfang steht.
        #
        ############################################################    */



/* Es wird zwar unten mit strncmp() getestet, ob das Kommando */
/* gequotet werden muss, allerdings muss nach dem Kommando */
/* Ein Leerzeichen oder ein Tab auftreten, damit die Abfrage */
/* TRUE liefert. Daher muessen hier sowohl !node als auch */
/* !node* angegeben werden! */

# define        MAXQUOTECMD     39

LOCAL const QUOTECOMMAND quotecommand[MAXQUOTECMD] =
{
   {"!node",              5, "!n",     2       },
   {"!subnode",           8, "!sn",    3       },
   {"!subsubnode",       11, "!ssn",   4       },
   {"!subsubsubnode",    14, "!sssn",  5       },
   {"!pnode",             6, "!p",     2       },
   {"!psubnode",          9, "!ps",    3       },
   {"!psubsubnode",      12, "!pss",   4       },
   {"!psubsubsubnode",   15, "!psss",  5       },
   {"!node*",             6, "!n*",    3       },
   {"!subnode*",          9, "!sn*",   4       },
   {"!subsubnode*",      12, "!ssn*",  5       },
   {"!subsubsubnode*",   15, "!sssn*", 6       },
   {"!pnode*",            7, "!p*",    3       },
   {"!psubnode*",        10, "!ps*",   4       },
   {"!psubsubnode*",     13, "!pss*",  5       },
   {"!psubsubsubnode*",  16, "!psss*", 6       },
   {"!begin_node",       11, "!bn",    3       },
   {"!begin_pnode",      12, "!bp",    3       },
   {"!begin_node*",      12, "!bn*",   4       },
   {"!begin_pnode*",     13, "!bp*",   4       },
   {"!item",              5, "!i",     2       },
   {"!index",             6, "!x",     2       },
   {"!image",             6, "",       0       },
   {"!image*",            7, "",       0       },
   {"!table_caption",    14, "",       0       },
   {"!table_caption*",   15, "",       0       },      /* r6pl1 */
   {"!begin_xlist",      12, "!bxl",   4       },      /* wegen des Inhalts der eckigen Klammern!  */
   {"!begin_blist",      12, "!bbl",   4       },      /* Fehlen die hier, so bekommt c_begin_list */
   {"!begin_ilist",      12, "!bil",   4       },      /* einen String, der c_vars(), aber nicht   */
   {"!begin_tlist",      12, "!btl",   4       },      /* auto_quote_chars() durchlaufen hat!!!    */
   {"!heading",           8, "!h",     2       },
   {"!subheading",       11, "!sh",    3       },
   {"!subsubheading",    14, "!ssh",   4       },
   {"!subsubsubheading", 17, "!sssh",  5       },
   {"!macro",             6, "",       0       },
   {"!hyphen",            7, "",       0       },
   {"!label",             6, "",       0       },
   {"!alias",             6, "",       0       },
   {"!docinfo",           8, "",       0       },
};





/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

   /* convert (UDO's) universal characters into miscellaneous encodings */
LOCAL void uni2misc(char *s);

   /* convert ISO encoding into desired system encoding */
LOCAL void iso2system(char *s);

   /* convert ISO encoding into desired system encoding */
LOCAL void iso2sys(char *s);

   /* convert ISO encoding into TOS encoding */

#if !defined(__MACOS__) && !defined(__MACOSX__)
   /* convert Mac encoding into ISO encoding */
LOCAL void mac2iso(char *s);
#endif

   /* convert UTF-8 encoding into ISO encoding */
LOCAL void utf82iso(char *s);

#ifndef __NEXTSTEP__
   /* convert NextStep encoding into ISO encoding */
LOCAL void next2iso(char *s);
#endif

   /* convert Atari TOS encoding into ISO encoding */
LOCAL void tos2iso(char *s);

   /* convert Codepage 437 encoding into ISO encoding */
LOCAL void cp437iso(char *s);

   /* convert Codepage 850 encoding into ISO encoding */
LOCAL void cp850iso(char *s);

   /* convert DOS encoded section sign into ISO encoded section sign */
LOCAL void section2iso(char *s);

#ifndef __HPUX_ROMAN8__
   /* convert HP Roman 8 encoding into ISO encoding */
LOCAL void hp82iso(char *s);
#endif

LOCAL void specials2ascii(char *s);
LOCAL void specials2ipf(char *s);
LOCAL void specials2info(char *s);
LOCAL void specials2win(char *s);
LOCAL void specials2rtf(char *s);
LOCAL void texvar2ascii(char *s);

   /* replace single or double quotation marks from UDO format to system characters */
LOCAL void c_quotes_apostrophes(char *s, const char *aon, const char *aoff, const char *qon, const char *qoff );

LOCAL void str2manbold(char *d, const char *s);
LOCAL void str2manunder(char *d, const char *s);










/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  uni2misc():
*     convert (UDO's) universal characters into miscellaneous encodings
*
*  Notes:
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void uni2misc(

char             *s)  /* ^ string */
{
   register int   i;  /* counter */


   if (s[0] == EOS)                       /* empty string */
      return;

   if (strstr(s, "(!") == NULL)           /* No UDO command header found */
      return;

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      for (i = 0; i < UNITABLESIZE; i++)
         replace_all(s, unitab[i].uni, unitab[i].tex);

      break;

   case TOHAH:
   case TOHTM:
   case TOMHH:
   case TOLDS:
   case TOHPH:
      for (i = 0; i < UNITABLESIZE; i++)
         replace_all(s, unitab[i].uni, unitab[i].html);

      break;

   case TOWIN:
   case TOWH4:
   case TOAQV:
   case TORTF:
      for (i = 0; i < UNITABLESIZE; i++)
         replace_all(s, unitab[i].uni, unitab[i].win);

      break;

   case TOPCH:
      for (i = 0; i < UNI2SYSTABSIZE; i++)
         replace_all(s, uni2sys[i].uni, (const char *) uni2sys[i].system);

      if (no_umlaute)                     /* target encoding must not use umlauts */
         umlaute2ascii(s);                /* convert all umlauts to pure ASCII */

      break;

   case TOLYX:
      for (i = 0; i < UNITABLESIZE; i++)
         replace_all(s, unitab[i].uni, unitab[i].lyx);
   }
}





/*******************************************************************************
*
*  iso2system():
*     convert ISO encoding into desired system encoding
*
*  Notes:
*     The ISO source encoding is determined by the UDO preamble command:
*     !code [iso]
*
*     The function iso2system() ALWAYS converts, while iso2sys() only converts 
*     when it should not convert into an encoding which doesn't use ANSI
*     (like RTF, WinHelp)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void iso2system(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ position in string */
   int    idx;  /* index in conversion table */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) > 127)           /* only convert high-ASCII characters */
      {
         idx = ((UCHAR)*ptr) - 128;       /* conversion table starts with ASCII 128! */

                                          /* check if conversion is possible */
         if (iso2sys_item[idx].charsys != EOS)
         {
            *ptr = iso2sys_item[idx].charsys;
         }
         else                             /* conversion is not possible */
         {
            warning_cannot_recode(*ptr, "Latin1", "system charset");
            *ptr= '?';
         }
      }
#ifdef __MSDOS__
      else
      {
         if (*ptr == '\247')              /* U_SectionSign (paragraph) */
         {
            *ptr = '\025';
         }
      }
#endif
#ifdef __MSDOS850__
      else
      {
         if (*ptr == '\247')              /* U_SectionSign (paragraph) */
         {
            *ptr = '\025';
         }
      }
#endif

      ptr++;                              /* next character */
   }
}





/*******************************************************************************
*
*  iso2sys():
*     convert ISO encoding into desired system encoding
*
*  Notes:
*     The ISO source encoding is determined by the UDO preamble command:
*     !code [iso]
*
*     The function iso2system() ALWAYS converts, while iso2sys() only converts 
*     when it should not convert into an encoding which doesn't use ANSI
*     (like RTF, WinHelp)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void iso2sys(

char *s)
{
                                          /* Changed: Fixed Bug #0000040 in r6.3pl16 [NHz] */
                                          /* Supplement of desttype==TOKPS */
   if (iCharset == CODE_LAT1)             /* PL14: TOLYX */
   {
      switch (desttype)
      {
      case TOWIN:
      case TOWH4:
      case TORTF:
      case TOAQV:
      case TOLYX:
      case TOKPS:
         return;
      }
   }
            
#if USE_LATIN1_CHARSET

   switch (desttype)
   {
   case TOSTG:
   case TOPCH:
      iso2tos(s);
      return;
   }
   
# else
# ifndef __TOS__

   if ((desttype == TOSTG) || (desttype == TOPCH) )
      iso2tos(s)
   else
# endif
      iso2system(s);
#endif
}





#ifndef __TOS__
/*******************************************************************************
*
*  iso2tos():
*     convert ISO encoding into TOS encoding
*
*  Notes:
*     The ISO source encoding is determined by the UDO preamble command:
*     !code [iso]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void iso2tos(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ position in string */
   int    idx;  /* index in conversion table */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) > 127)           /* only convert high-ASCII characters */
      {
         idx = ((UCHAR)*ptr) - 128;       /* conversion table starts with ASCII 128! */

                                          /* check if conversion is possible */
         if (iso2tos_item[idx].charsys != EOS)
         {
            *ptr = iso2tos_item[idx].charsys;
         }
         else                             /* conversion is not possible */
         {
            warning_cannot_recode(*ptr, "Latin1", "system charset");
            *ptr= '?';
         }
      }
#ifdef __MSDOS__
      else
      {
         if (*ptr == '\247')              /* U_SectionSign (paragraph) */
         {
            *ptr = '\025';
         }
      }
#endif
#ifdef __MSDOS850__
      else
      {
         if (*ptr == '\247')              /* U_SectionSign (paragraph) */
         {
            *ptr = '\025';
         }
      }
#endif

      ptr++;                              /* next character */
   }
}
#endif  /* #ifndef __TOS__ */





#if !defined(__MACOS__) && !defined(__MACOSX__)
/*******************************************************************************
*
*  mac2iso():
*     convert Mac encoding into ISO encoding
*
*  Notes:
*     The Mac source encoding is determined by the UDO preamble command:
*     !code [mac]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void mac2iso(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ position in string */
   int    idx;  /* index in conversion table */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) > 127)           /* only convert high-ASCII characters */
      {
         idx = ((UCHAR)*ptr) - 128;       /* conversion table starts with ASCII 128! */

                                          /* check if conversion is possible */
         if (mac2iso_item[idx].iso != EOS)
         {
            *ptr = mac2iso_item[idx].iso;
         }
         else                             /* conversion is not possible */
         {
            warning_cannot_recode(*ptr, "MacOS", "Latin1");
            *ptr= '?';
         }
      }

      ptr++;                              /* next character */
   }
}
#endif  /* __MACOS__ */





/* #ifndef __BEOS__ */
/*******************************************************************************
*
*  utf82iso():
*     convert UTF-8 encoding into ISO encoding
*
*  Notes:
*     The Mac source encoding is determined by the UDO preamble command:
*     !code [utf8]    (or)
*     !code [utf-8]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void utf82iso(

char     *s)           /* ^ string */
{
   char  *ptr,         /* ^ position in string */
          sUTF[16],    /* */
          onechar[1];  /* */
   int    i,           /* counter */
          bytes;       /* */
BOOLEAN   found;       /* flag */


   ptr = s;                               /* set ^ to begin of string */

   if (*ptr == EOS)                       /* empty string */
      return;

   strcpy(onechar, " ");

   while (*ptr != EOS)                    /* check whole string */
   {
                                          /* UTF-8-Zeichen gefunden */
      if ( ((UCHAR)*ptr > 127) && (((UCHAR)*ptr & 0xC0) != 0x80) )
      {                                   /* nun herausfinden, wieviele Bytes insgesamt vorliegen */
         bytes = ((UCHAR) *ptr >> 5) & 0x03;

         switch (bytes)
         {
         case 2:                          /* 0xC.. , also zwei Bytes */
            if (ptr[1] != EOS)
            {
               found = FALSE;

               for (i = 0; i < 128; i++)
               {
                  if (    ((UCHAR)ptr[0] == utf82iso_item[i].utf8[0])
                       && ((UCHAR)ptr[1] == utf82iso_item[i].utf8[1]) )
                  {
                     onechar[0] = utf82iso_item[i].latin1;
                     qreplace_once(ptr, (char *)utf82iso_item[i].utf8, 2, onechar, 1);
                     found = TRUE;
                     break;
                  }
               }
               
               if (!found)
               {
                  sprintf(sUTF, "%X %X", ptr[0], ptr[1]);
                  warning_cannot_recode_utf8(sUTF, "Latin1");
                  ptr++;
               }
            }
            
            break;

         case 3:                          /* 0xE.. , also drei Bytes */
            if (ptr[1]!=EOS && ptr[2]!=EOS)
            {
               sprintf(sUTF, "%X %X %X", ptr[0], ptr[1], ptr[2]);
               warning_cannot_recode_utf8(sUTF, "Latin1");
               ptr+= 2;
            }

            break;

         default:
            warning_cannot_recode(*ptr, "UTF-8", "Latin1");
         }
      }

      ptr++;                              /* next character */
      
   }  /* while (*ptr != EOS) */
}
/* #endif */    /* #ifndef __BEOS__ */





#ifndef __NEXTSTEP__
/*******************************************************************************
*
*  next2iso():
*     convert NextStep encoding into ISO encoding
*
*  Notes:
*     The NextStep source encoding is determined by the UDO preamble command:
*     !code [next]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void next2iso(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ position in string */
   int    idx;  /* index in conversion table */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) > 127)           /* only convert high-ASCII characters */
      {
         idx = ((UCHAR)*ptr) - 128;       /* conversion table starts with ASCII 128! */

                                          /* check if conversion is possible */
         if (next2iso_item[idx].iso != EOS)
         {
            *ptr = next2iso_item[idx].iso;
         }
         else                             /* conversion is not possible */
         {
            warning_cannot_recode(*ptr, "NeXTSTep", "Latin1");
            *ptr= '?';
         }
      }

      ptr++;                              /* next character */
   }
}
#endif  /* __NEXTSTEP__ */





#ifndef __TOS__
/*******************************************************************************
*
*  tos2iso():
*     convert Atari TOS encoding into ISO encoding
*
*  Notes:
*     The Atari TOS source encoding is determined by the UDO preamble command:
*     !code [tos]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void tos2iso(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ position in string */
   int    idx;  /* index in conversion table */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) > 127)           /* only convert high-ASCII characters */
      {
         idx = ((UCHAR)*ptr) - 128;       /* conversion table starts with ASCII 128! */

                                          /* check if conversion is possible */
         if (tos2iso_item[idx].iso != EOS)
         {
            *ptr = tos2iso_item[idx].iso;
         }
         else                             /* conversion is not possible */
         {
            warning_cannot_recode(*ptr, "TOS", "Latin1");
            *ptr= '?';
         }
      }

      ptr++;                              /* next character */
   }
}
#endif  /* __TOS__ */





#ifndef __MSDOS__
/*******************************************************************************
*
*  cp437iso():
*     convert Codepage 437 encoding into ISO encoding
*
*  Notes:
*     The Codepage 437 source encoding is determined by the UDO preamble command:
*     !code [cp437]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void cp437iso(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ position in string */
   int    idx;  /* index in conversion table */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) > 127)           /* only convert high-ASCII characters */
      {
         idx = ((UCHAR)*ptr) - 128;       /* conversion table starts with ASCII 128! */

                                          /* check if conversion is possible */
         if (cp437iso_item[idx].iso != EOS)
         {
            *ptr = cp437iso_item[idx].iso;
         }
         else                             /* conversion is not possible */
         {
            warning_cannot_recode(*ptr, "cp437", "Latin1");
            *ptr= '?';
         }
      }

      ptr++;                              /* next character */
   }
}
#endif  /* __MSDOS__ */





#ifndef __MSDOS850__
/*******************************************************************************
*
*  cp850iso():
*     convert Codepage 850 encoding into ISO encoding
*
*  Notes:
*     The Codepage 850 source encoding is determined by the UDO preamble command:
*     !code [cp850]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void cp850iso(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ position in string */
   int    idx;  /* index in conversion table */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) > 127)           /* only convert high-ASCII characters */
      {
         idx = ((UCHAR)*ptr) - 128;       /* conversion table starts with ASCII 128! */

                                          /* check if conversion is possible */
         if (cp850iso_item[idx].iso != EOS)
         {
            *ptr = cp850iso_item[idx].iso;
         }
         else                             /* conversion is not possible */
         {
            warning_cannot_recode(*ptr, "cp850", "Latin1");
            *ptr= '?';
         }
      }

      ptr++;                              /* next character */
   }
}
#endif  /* __MSDOS850__ */





#if !defined(__MSDOS__) && !defined(__MSDOS850__)
/*******************************************************************************
*
*  section2iso():
*     convert DOS encoded section sign into ISO encoded section sign
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void section2iso(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ position in string */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) == '\025')       /* DOS section sign found? */
         *ptr= '\247';                    /* convert it */

      ptr++;                              /* next character */
   }
}
#endif





#ifndef __HPUX_ROMAN8__
/*******************************************************************************
*
*  hp82iso():
*     convert HP Roman 8 encoding into ISO encoding
*
*  Notes:
*     The HP Roman 8 source encoding is determined by the UDO preamble command:
*     !code [hp8]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void hp82iso(

char     *s)    /* ^ string */
{
   char  *ptr;  /* ^ position in string */
   int    idx;  /* index in conversion table */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) > 127)           /* only convert high-ASCII characters */
      {
         idx = ((UCHAR)*ptr) - 128;       /* conversion table starts with ASCII 128! */

                                          /* check if conversion is possible */
         if (hp82iso_item[idx].iso != EOS)
         {
            *ptr = hp82iso_item[idx].iso;
         }
         else                             /* conversion is not possible */
         {
            warning_cannot_recode(*ptr, "HP Roman 8", "Latin1");
            *ptr= '?';
         }
      }

      ptr++;                              /* next character */
   }
}
#endif  /* __HPUX_ROMAN8__ */





/*******************************************************************************
*
*  recode_always():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void recode_always(

char  *zeile,     /* ^ text line */
int    char_set)  /* isn't this identical to iCharset??? */
{
   switch (char_set)
   {
#if !USE_LATIN1_CHARSET
   case CODE_LAT1:
      iso2system(zeile);
      break;
#endif

#if !defined(__MACOS__) && !defined(__MACOSX__)
   case CODE_MAC:
      mac2iso(zeile);
      iso2system(zeile);
      break;
#endif

#ifndef __TOS__
   case CODE_TOS:
      tos2iso(zeile);
      iso2system(zeile);
      break;
#endif

#ifndef __MSDOS__
   case CODE_437:
      cp437iso(zeile);
      iso2system(zeile);
      break;
#endif

#ifndef __MSDOS850__
   case CODE_850:
      cp850iso(zeile);
      iso2system(zeile);
      break;
#endif

#ifndef __HPUX_ROMAN8__
   case CODE_HP8:
      hp82iso(zeile);
      iso2system(zeile);
      break;
#endif

#ifndef __NEXTSTEP__
   case CODE_NEXT:
      next2iso(zeile);
      iso2system(zeile);
      break;
#endif
   }
}










/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  convert_sz():
*     convert encoding of German ss ligature
*
*  Notes:
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void convert_sz(

char  *s)  /* ^ string */
{
   if (html_ignore_8bit)                  /* ignore any conversion */
      return;

#ifdef __TOS__
   replace_char(s, "\341", "\236");       /* from DOS(?):0xE1 to TOS:0x9E */
#else
# if !defined(__MSDOS__) && !defined(__MSDOS850__)

   if (desttype != TOSTG || desttype == TOPCH)
      replace_char(s, "\236", "\341");    /* from TOS:0x9E to DOS(?):0xE1 */
# else
   UNUSED(s);
# endif
#endif
}





/*******************************************************************************
*
*  uni2ascii():
*     convert (UDO's) universal characters into system encoding or target encoding
*
*  Notes:
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void uni2ascii(

char             *s)  /* ^ string */
{
   register int   i;  /* counter */
   

   if (s[0] == EOS)                       /* empty string */
      return;

   if (strstr(s, "(!") == NULL)           /* No UDO command header found */
      return;

   for (i = 0; i < UNI2SYSTABSIZE; i++)   /* uni2sys[] depends on encoding! */
   {
      replace_all(s, uni2sys[i].uni, (const char *)uni2sys[i].system);
   }

   if (no_umlaute)                        /* target encoding must not use umlauts */
      umlaute2ascii(s);                   /* convert all umlauts to pure ASCII */
}





/*******************************************************************************
*
*  recode():
*     recode a line into another encoding
*
*  Notes:
*     Es wird zunaechst das erste 8-Bit-Zeichen gesucht, da[mit?] in *2iso() 
*     und iso2sys() nicht die 7-Bit-Zeichen zweimal uebersprungen werden muessen.
*     Ist kein 8-Bit-Zeichen enthalten, so spart man sich zwei Aufrufe mit 
*     nutzlosen 128-Schritt-Schleifen.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void recode(

char     *zeile,     /* ^ line */
int       char_set)  /* iCharset */
{
   char  *ptr;       /*  */

   switch (char_set)
   {
#if !USE_LATIN1_CHARSET
   case CODE_LAT1:
      iso2sys(zeile);
      break;
#endif

#if !defined (__MACOS__) && !defined(__MACOSX__)
   case CODE_MAC:
      ptr = get_8bit_ptr(zeile);

      if (ptr)
      {
         mac2iso(ptr);
         iso2sys(ptr);
      }
      
      break;
#endif

#ifndef __TOS__
   case CODE_TOS:
      ptr = get_8bit_ptr(zeile);
      
      if (ptr)
      {
         tos2iso(ptr);
         iso2sys(ptr);
      }
      
      break;
#endif

#ifndef __MSDOS__
   case CODE_437:
      ptr = get_8bit_ptr(zeile);
      
      if (ptr)
      {
         cp437iso(ptr);
         iso2sys(ptr);
      }

      ptr = get_section_ptr(zeile);

      if (ptr)
      {
         section2iso(ptr);
      }
      
      break;
#endif

#ifndef __MSDOS850__
   case CODE_850:
      ptr = get_8bit_ptr(zeile);
      
      if (ptr)
      {
         cp850iso(ptr);
         iso2sys(ptr);
      }
      
/*    ptr = get_section_ptr(zeile);

      if (ptr)
      {
         section2iso(ptr);
      }
*/

      break;
#endif

#ifndef __HPUX_ROMAN8__
   case CODE_HP8:
      ptr = get_8bit_ptr(zeile);
      
      if (ptr)
      {
         hp82iso(ptr);
         iso2sys(ptr);
      }
      
      break;
#endif

#ifndef __NEXTSTEP__
   case CODE_NEXT:
      ptr = get_8bit_ptr(zeile);

      if (ptr)
      {
         next2iso(ptr);
         iso2sys(ptr);
      }
      
      break;
#endif

/* #ifndef      __BEOS__ */
   case CODE_UTF8:
      ptr = get_8bit_ptr(zeile);
      
      if (ptr)
      {
         utf82iso(ptr);
         iso2sys(ptr);
      }
      
      break;
/* #endif */
    }
}





/*******************************************************************************
*
*  win2sys():
*     recode a string with Windows characters (used for TITLE option)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void win2sys(

char             *s)        /* ^ string */
{
   register int   i;        /* counter */
   char           one[2];   /* one char buffer */
   char           four[5];  /* four chars buffer */
   char          *ptr;      /* ^ into string */


   if (s[0] == EOS)                       /* empty string */
      return;

   strcpy(one, " ");                      /* clear buffer */

   for (i = 0; i < 128; i++)
   {
      if (chrtab[i].ansi[0] == '\\')
      {
         one[0] = chrtab[i].charsystem;
         replace_all(s, chrtab[i].ansi, one);
      }
   }

   replace_char(s, "\236", "\341");       /* Noch das sz anpassen */

   strcpy(four, "    ");                  /* clear other buffer */
   
                                          /* Nicht umwandelbare Zeichen entfernen */
   while((ptr = strstr(s, "\\'")) != NULL)
   {
      four[0]= ptr[0];
      four[1]= ptr[1];
      four[2]= ptr[2];
      four[3]= ptr[3];

      delete_all(s, four);
   }
}





/*******************************************************************************
*
*  html2sys():
*     String mit HTML-Zeichen in Systemzeichen wandeln
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html2sys(

char             *s)            /* ^ to string */
{
   register int   i;            /* counter */
   char           one[2] = "";  /* cleared string buffer */
   
   
   if (s[0] == EOS)                       /* empty string */
      return;
   
   for (i = 0; i < 128; i++)              /* convert lower ASCII part */
   {
      one[0] = chrtab[i].charsystem;
      replace_all(s, chrtab[i].html, one);
   }
   
   for (i = 0; i < MAXHTML7BIT; i++)      /* convert special HTML characters */
   {
      one[0] = html7bit[i].c;             /* get HTML character (e.g. '&') */
                                          /* replace it (e.g. by '&amp;') */
      replace_all(s, html7bit[i].quoted, one);
   }
}





/*******************************************************************************
*
*  ansi2dos():
*     recode Windows characters into DOS characters
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void ansi2dos(

char             *s)    /* ^ string */
{
   char          *ptr;  /* ^ position in string */
   register int   idx;  /* index in conversion table */


   ptr = s;                               /* set ^ to begin of string */

   while (*ptr != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)*ptr) > 127)           /* only convert high-ASCII characters */
      {
         idx = ((UCHAR)*ptr) - 128;       /* conversion table starts with ASCII 128! */

                                          /* check if conversion is possible */
         if (ansi2dos_item[idx].dos != EOS)
         {
            *ptr = ansi2dos_item[idx].dos;
         }
         else                             /* conversion is not possible */
         {
            warning_cannot_recode(*ptr, "Latin1", "system charset");
            *ptr= '?';
         }
      }

      ptr++;                              /* next character */
   }
}





/*******************************************************************************
*
*  calc_ttf_twip():
*     Breiten von Strings in twip (1/1440" bzw. 1/20 pt) fuer WinHelp berechnen
*
*  Return:
*     twip
*
******************************************|************************************/

GLOBAL int calc_ttf_twip(

const char *s,       /* ^ string */
const int   font,    /* */
const int   style)   /* */
{
   int      pixel,   /* */
            twip;    /* */
   size_t   i;       /* counter */
   char     d[512];  /* */
   
   
   if (s[0] == EOS)                       /* empty string */
      return (0);

   strcpy(d, s);                          /* copy string */
   recode_always(d, iCharset);
   strcat(d, "W");                        /* Breitenausgleiche */

   pixel = 0;

   switch (font)
   {       
   case TTF_TIMES:
      switch (style)
      {
      case TTF_BOLD:
         for (i = 0; i < strlen(d); i++)
         {
            pixel += width_times_11_bold[(UCHAR)d[i]];
            pixel++;
         }
         
         break;
         
      case TTF_ITALIC:
         for (i = 0; i < strlen(d); i++)
         {
            pixel += width_times_11_italic[(UCHAR)d[i]];
            pixel++;
         }
         
         break;

      default:
         for (i = 0; i < strlen(d); i++)
         {
            pixel += width_times_11_regular[(UCHAR)d[i]];
            pixel++;
         }
      }
      
      break;

   case TTF_COURIER:
      switch (style)
      {
      case TTF_BOLD:
         for (i = 0; i < strlen(d); i++)
         {
            pixel += width_courier_10_bold[(UCHAR)d[i]];
            pixel++;
         }
         
         break;

      case TTF_ITALIC:
         for (i = 0; i < strlen(d); i++)
         {
            pixel += width_courier_10_italic[(UCHAR)d[i]];
            pixel++;
         }
         
         break;

      default:
         for (i = 0; i < strlen(d); i++)
         {
            pixel += width_courier_10_regular[(UCHAR)d[i]];
            pixel++;
         }
      }
      
      break;

   default:
      switch (style)
      {
      case TTF_BOLD:
         for (i = 0; i < strlen(d); i++)
         {
            pixel += width_arial_10_bold[(UCHAR)d[i]];
            pixel++;
         }
         
         break;
         
      case TTF_ITALIC:
         for (i = 0; i < strlen(d); i++)
         {
            pixel += width_arial_10_italic[(UCHAR)d[i]];
            pixel++;
         }

         break;
         
      default:
         for (i = 0; i <strlen(d); i++)
         {
            pixel += width_arial_10_regular[(UCHAR)d[i]];
            pixel++;
         }
      }
   }

   /* pt   = pixel * 72 / 100                     */
   /* twip = pixel * 72 / 100 * 20 = pixel * 14.4 */
   /* passt aber nicht, daher etwas mehr!         */

   twip = (int)(pixel * 14.4);

   return(twip);
}





/*******************************************************************************
*
*     BASIC REPLACEMENT ROUTINES
*
*     - which remove not allowed characters from nodes
*     - handle special UDO cases
*
******************************************|************************************/

/*******************************************************************************
*
*  replace_udo_quotes():
*     quote UDO commands in text environment
*
*  Example:
*     !node -> !/node
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_udo_quotes(

char  *s)  /* ^ string */
{
   qreplace_all(s, "!/", 2, "!", 1);      /* */
}





/*******************************************************************************
*
*  replace_all_copyright():
*     adjust copyright links
*
*  Notes:
*     Bei Pure C Help wird bei Copyright auf die Borland-Seite
*     verwiesen, und nicht auf einen eigenen Node. Daher die
*     Zeichenkette anpassen. Nicht schoen, aber zweckmaessig.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_all_copyright(

char  *s)  /* ^ string */
{
   if (desttype == TOPCH)                 /* Pure C Help */
   {
      qreplace_all(s, "Copyright", 9, "Copy-Right", 10);
   }
}





/*******************************************************************************
*
*  delete_all_divis():
*     delete all internal UDO hyphen markers
*
*  Notes:
*     DIVIS_S + DIVIS_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void delete_all_divis(

char  *s)  /* ^ string */
{
   qdelete_all(s, DIVIS_S, DIVIS_S_LEN);  /* */
}





/*******************************************************************************
*
*  indent2space():
*     convert indents into spaces
*
*  Notes:
*     INDENT_S + INDENT_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void indent2space(

char  *s)  /* ^ string */
{
#if (INDENT_S_LEN==1)
   replace_char(s, INDENT_S, " ");
#else
   qreplace_all(s, INDENT_S, INDENT_S_LEN, " ", 1);
#endif
}





/*******************************************************************************
*
*  space2indent():
*     convert spaces into indents
*
*  Notes:
*     INDENT_S + INDENT_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void space2indent(

char  *s)  /* ^ string */
{
#if (INDENT_S_LEN==1)
   replace_char(s, " ", INDENT_S);
#else
   qreplace_all(s, " ", 1, INDENT_S, INDENT_S_LEN);
#endif
}





/*******************************************************************************
*
*  nbsp2space():
*     convert non-breakable spaces into spaces
*
*  Notes:
*     NBSP_S + NBSP_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void nbsp2space(

char  *s)  /* ^ string */
{
#if (NBSP_S_LEN==1)
   replace_char(s, NBSP_S, " ");
#else
   qreplace_all(s, NBSP_S, NBSP_S_LEN, " ", 1);
#endif
}





/*******************************************************************************
*
*  space2nbsp():
*     convert spaces into non-breakable spaces
*
*  Notes:
*     NBSP_S + NBSP_S_LEN are defined in constant.h
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void space2nbsp(

char  *s)  /* ^ string */
{
#if (NBSP_S_LEN==1)
   replace_char(s, " ", NBSP_S);
#else
   qreplace_all(s, " ", 1, NBSP_S, NBSP_S_LEN);
#endif
}





/*******************************************************************************
*
*  umlaute2ascii():
*     convert German umlauts into their 7bit versions
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void umlaute2ascii(

char  *s)  /* ^ string */
{
   int      id;           /* */
   size_t   i = 0;        /* counter */
   char     one[2] = "";  /* char buffer */
   

   if (s[0] == EOS)                       /* empty string */
      return;

   while (s[i] != EOS)                    /* check whole string */
   {
      if ( ((UCHAR)s[i]) > 127)           /* only convert high-ASCII characters */
      {
         id = ((UCHAR)s[i]) - 128;        /* conversion table starts with ASCII 128! */

         if (chrtab[id].ascii[0] != EOS)  /* check if conversion is possible */
         {
            one[0] = s[i];
            replace_all(s + i, one, chrtab[id].ascii);
         }
      }
      
      i++;                                /* next character */
   }
}





/*******************************************************************************
*
*  label2tex():
*     replace or remove all chars which are not allowed in a TeX label "\label{...}"
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void label2tex(

char  *s)  /* ^ string which has already adjusted special chars for LaTeX */
{
   qreplace_all(s, "{\\\"a}", 4, "ae",   2);
   qreplace_all(s, "{\\\"o}", 4, "oe",   2);
   qreplace_all(s, "{\\\"u}", 4, "ue",   2);
   qreplace_all(s, "{\\\"s}", 4, "ss",   2);
   qreplace_all(s, "{\\\"A}", 4, "Ae",   2);
   qreplace_all(s, "{\\\"O}", 4, "Oe",   2);
   qreplace_all(s, "{\\\"U}", 4, "Ue",   2);
   qreplace_all(s, "\\_",     2, "-",    1);
   qreplace_all(s, "_",       1, "-",    1);
   qreplace_all(s, "#",       1, "035-", 4);
   qreplace_all(s, "$",       1, "036-", 4);
   qreplace_all(s, "%",       1, "037-", 4);
   qreplace_all(s, "&",       1, "038-", 4);
   qreplace_all(s, "~",       1, "126-", 4);
   qreplace_all(s, "^",       1, "094-", 4);
   qreplace_all(s, "{",       1, "123-", 4);
   qreplace_all(s, "}",       1, "125-", 4);

   qdelete_all(s, "\\", 1);

   qreplace_all(s, "\"'",     2, "'",    1);
   qreplace_all(s, "\"`",     2, "`",    1);
}





/*******************************************************************************
*
*  label2html():
*     replace or remove all chars which are not allowed in an HTML anchor
*
*  Notes:
*     Gemaess SGML companion sind erlaubt: "a-z", "A-Z", "0-9", "$+.-_". 
*     Alle anderen Codes werden durch _xx dargestellt (_ und Hexcode).
*
*     HTML-4.0-Spec: "ID and NAME tokens must begin with a letter ([A-Za-z]) 
*     and may be followed by any number of letters, digits ([0-9]), hyphens ("-"),
*     underscores ("_"), colons (":"), and periods (".")."
*
*  Example:
*     "Ein Label" -> "Ein_20Label"
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void label2html(

char     *s)               /* ^ to label name */
{
   char  *ptr,             /* ^ to current char in string */
          val[16];         /* char value */
   char   one[2]= {0, 0};  /* hex value buffer */


   ptr = s;

   while (*ptr != EOS)
   {
      if (*ptr >= 'a' && *ptr <= 'z')
         goto LABEL2HTML_NEXT;

      if (*ptr >= 'A' && *ptr <= 'Z')
         goto LABEL2HTML_NEXT;

      if (*ptr >= '0' && *ptr <= '9')
         goto LABEL2HTML_NEXT;

      if (*ptr == '-')
         goto LABEL2HTML_NEXT;

      if (*ptr == '_')
         goto LABEL2HTML_NEXT;

      if (*ptr == ':')
         goto LABEL2HTML_NEXT;

      if (*ptr == '.')
         goto LABEL2HTML_NEXT;

      sprintf(val, "_%X", (UCHAR)*ptr);
      one[0] = *ptr;
      replace_once(ptr, one, val);

LABEL2HTML_NEXT:
      ptr++;
   }

   /* Labelname muss mit einem Buchstaben beginnen (siehe Spec) */
   if (*s >= 'a' && *s <= 'z')
      return;

   if (*s >= 'A' && *s <= 'Z')
      return;
}





/*******************************************************************************
*
*  node2winhelp():
*     adjust index names for WinHelp
*
*  Notes:
*     WinHelp mag keine Umlaute und Sonderzeichen in einer Referenz.
*     Leerzeichen werden durch Underscores ersetzt, alles andere durch Hexwerte.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2winhelp(

char       *n)            /* ^ node name */
{
   char     t[512] = "";  /* buffer for converted node name */
   char     v[32]  = "";  /* buffer for hex values */
   size_t   i;            /* ^ into string */


   if (n[0] == EOS)                       /* empty string */
      return;

   umlaute2ascii(n);
   replace_udo_quotes(n);
   delete_all_divis(n);

   for (i = 0; i < strlen(n); i++)
   {       
      if ( (n[i] >= '0' && n[i] <= '9') || (n[i] >= 'a' && n[i] <= 'z') || (n[i] >= 'A' && n[i] <= 'Z') )
      {
         chrcat(t, n[i]);
      }
      else if (n[i] == ' ' || n[i] == '_' )
      {
         chrcat(t, '_');
      }
      else
      {
         sprintf(v, "_%X", (UCHAR)n[i]);
         strcat(t, v);
      }
   }

   if (strlen(t) > 80)                    /* Windows Help Compiler doesn't like */
      t[81] = EOS;                        /* longer names in the index */

   strcpy(n, t);
}





/*******************************************************************************
*
*  node2WinAutoID():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2WinAutoID(

char        *id,      /* ID */
const char  *n)       /* name */
{
   char      s[512];  /* buffer for name */
   size_t    i;       /* pointer into name buffer */


   id[0] = EOS;                           /* clear ID */

   if (n[0] == EOS)                       /* empty name */
      return;

   strcpy(s, n);                          /* copy name */
   win2sys(s);
   umlaute2ascii(s);
   replace_udo_quotes(s);
   delete_all_divis(s);

   id[0] = EOS;                           /* clear ID  (again???) */

   for (i = 0; i < strlen(s); i++)        /* search for allowed characters */
   {
      if ( (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_' )
      {
         chrcat(id, s[i]);
      }
   }
}





/*******************************************************************************
*
*  node2NrWinhelp():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2NrWinhelp(

char  *s,   /* ^ node context string */
int    li)  /* internal label # (lab[]->, not toc[]->!!) */
{
   sprintf(s, "UDON%05X", li + 1);
}





/*******************************************************************************
*
*  alias2NrWinhelp():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void alias2NrWinhelp(

char  *s,   /* ^ node context string */
int    li)  /* internal label # (lab[]->, not toc[]->!!) */
{
   sprintf(s, "UDOA%05X", li + 1);
}





/*******************************************************************************
*
*  label2NrWinhelp():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void label2NrWinhelp(

char  *s,   /* ^ node context string */
int    li)  /* internal label # (lab[]->, not toc[]->!!) */
{
   sprintf(s, "UDOL%05X", li + 1);
}





/*******************************************************************************
*
*  node2NrIPF():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2NrIPF(

char  *s,   /* ^ node context string */
int    li)  /* internal label # (lab[]->, not toc[]->!!) */
{
   sprintf(s, "UDON%05X", li + 1);
}





/*******************************************************************************
*
*  alias2NrIPF():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void alias2NrIPF(

char  *s,   /* ^ node context string */
int    li)  /* internal label # (lab[]->, not toc[]->!!) */
{
   sprintf(s, "UDOA%05X", li + 1);
}





/*******************************************************************************
*
*  label2NrIPF():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void label2NrIPF(

char  *s,   /* ^ node context string */
int    li)  /* internal label # (lab[]->, not toc[]->!!) */
{
   sprintf(s, "UDOL%05X", li + 1);
}





/*******************************************************************************
*
*  node2pchelp():
*     convert quotation marks to a Pure C Help convenient format
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2pchelp(

char  *s)  /* ^ string to be used as label or node */
{
   qreplace_all(s, "\"", 1, "_0x20_", 6);
}





/*******************************************************************************
*
*  node2postscript():
*     adjust label or node for PostScript
*
*  Notes:
*     PostScript doesn't like spaces or other special characters in labels or nodes.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2postscript(

char     *s,      /* ^ string to be used as label or node */
int       text)   /* */
{
   long   talen;  /* */


   switch(text)
   {
                                          /* New: Fixed bug #0000040 in r6.3pl16 [NHz] */
   case KPS_PS2DOCINFO:
      qreplace_all(s, "\\[", 2, "[", 1);
      qreplace_all(s, "\\]", 2, "]", 1);
      break;

   case KPS_DOCINFO2PS:
      qreplace_all(s, "[", 1, "\\[", 2);
      qreplace_all(s, "]", 1, "\\]", 2);
      break;

   case KPS_NODENAME:
                                          /* v6.5.14 [vj]: titdat.author kann ein Null-Pointer sein
                                           * => ich berechnet strlen(titdat.author) vor und nehme 0
                                           *    an, wenn es leer ist.
                                           */
      if (titdat.author)
         talen = strlen(titdat.author);
      else
         talen = 0;

      if ((long)strlen(s) > 80L - talen)
      {
         s[80L - talen] = EOS;
         
         if (s[79L - talen] == '\\')
            s[79L - talen] = EOS;

         strcat(s, "...\0");
      }
      
                                          /* Changed in V6.5.5 [NHz] */
      qreplace_all(s, "(", 1, "\\(", 2);
      qreplace_all(s, ")", 1, "\\)", 2);
                                          /* Changed: Fixed bug #0000062 in V6.5.8 [NHz] */
      qreplace_all(s, "[", 1, "\\[", 2);
      qreplace_all(s, "]", 1, "\\]", 2);
      break;

   case KPS_CONTENT:
      qreplace_all(s, "/", 1, "\\/", 2);
                                          /* Changed in V6.5.5 [NHz] */
      qreplace_all(s, "(", 1, "\\(", 2);
      qreplace_all(s, ")", 1, "\\)", 2);
      qreplace_all(s, "[", 1, "\\[", 2);
      qreplace_all(s, "]", 1, "\\]", 2);
      break;

   case KPS_BOOKMARK:
      if (strlen(s) > 32L)
      {
         s[32] = EOS;
         
         if (s[31] == '\\')
            s[31] = EOS;
      }
      
      qreplace_all(s, "/", 1, "\\/", 2);
                                          /* Changed in V6.5.5 [NHz] */
      qreplace_all(s, "(", 1, "\\(", 2);
      qreplace_all(s, ")", 1, "\\)", 2);
      qreplace_all(s, "[", 1, "\\[", 2);
      qreplace_all(s, "]", 1, "\\]", 2);
      break;

   case KPS_NAMEDEST:
      qreplace_all(s, " ", 1, "_", 1);
      qdelete_all(s, ";", 1);
      qdelete_all(s, ":", 1);
      qdelete_all(s, "/", 1);
                                          /* New: Fixed Bug #0000040 in r6.3pl16 [NHz] */
      qdelete_all(s, "\\[", 2);
      qdelete_all(s, "[", 1);
      qdelete_all(s, "\\(", 2);
      qdelete_all(s, "(", 1);
                                          /* New: Fixed Bug #0000040 in r6.3pl16 [NHz] */
      qdelete_all(s, "\\]", 2);
      qdelete_all(s, "]", 1);
      qdelete_all(s, "\\)", 2);
      qdelete_all(s, ")", 1);
      qdelete_all(s, "-", 1);
      qdelete_last(s, "_", 1);
   }
}





/*******************************************************************************
*
*  node2stg():
*     replace or remove all chars not allowed in an ST-Guide node
*
*  Notes:
*     @symbol ari "..."
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2stg(

char  *s)  /* ^ string to be used as label or node */
{
   qreplace_all(s, "\"", 1, "\\\"", 2);
}





/*******************************************************************************
*
*  index2stg():
*     replace or remove all chars not allowed in an ST-Guide label
*
*  Notes:
*     Function is identical to node2stg(), but this may change in the future.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void index2stg(

char  *s)  /* ^ string to be used as label or node */
{
   qreplace_all(s, "\"", 1, "\\\"", 2);
}





/*******************************************************************************
*
*  replace_2at_by_1at():
*     replace "@@" by "@"
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_2at_by_1at(

char  *s)  /* ^ string to be used as label or node */
{
   qreplace_all(s, "@@", 2, "@", 1);
}





/*******************************************************************************
*
*  replace_1at_by_2at():
*     replace "@" by "@@"
*
*  Return:
*     -
*
******************************************|************************************/


GLOBAL void replace_1at_by_2at(

char  *s)  /* ^ string to be used as label or node */
{
   qreplace_all(s, "@", 1, "@@", 2);
}





/*******************************************************************************
*
*  node2vision():
*     adjust characters for a Turbo Vision Help topic
*
*  Notes:
*     In einem Topic fuer Turbo Vision Help duerfen nur Zeichen vorkommen, 
*     die auch in C oder Pascal als Funktionsnamen erlaubt sind.
*
*
*     - genau wie bei node2winhelp
*     - Strings werden noch nicht gekuerzt
*     - <???> Testen, ob TVH mit langen Namen klarkommt
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2vision(

char       *n)            /* ^ string */
{
   char     t[512] = "",  /* buffer for topic string */
            v[32]  = "";  /* buffer for hex values */
   size_t   i;            /* pointer into string */
   

   if (n[0] == EOS)                       /* empty string */
      return;

   umlaute2ascii(n);
   replace_udo_quotes(n);
   delete_all_divis(n);
   replace_udo_tilde(n);
   replace_udo_nbsp(n);

   for (i = 0; i < strlen(n); i++)
   {
      if ( (n[i] >= '0' && n[i] <= '9') || (n[i] >= 'a' && n[i] <= 'z') || (n[i] >= 'A' && n[i] <= 'Z') )
      {
         chrcat(t, n[i]);
      }
      else if (n[i] == ' ' || n[i] == '_')
      {
         chrcat(t, '_');
      }
      else
      {
         sprintf(v, "_%X", (UCHAR) n[i]);
         strcat(t, v);
      }
   }

   strcpy(n, t);
}





/*******************************************************************************
*
*  node2texinfo():
*     adjust node name for Texinfo
*
*  Notes:
*     In einem @node duerfen bei Texinfo einige Zeichen nicht auftauchen. 
*     Diese werden entfernt.
*
*     PL15: Wenn der Titel hingegen keine alphanumerischen Zeichen enthaelt, 
*     so werden alle Zeichen im Titel durch Ascii/Hexcodes ersetzt.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void node2texinfo(

char        *s)       /* ^ string (chapter title) */
{
   size_t    sl,      /* */
             i;       /* */
   char      d[512],  /* */
             a[32],   /* */
             c;       /* */
   BOOLEAN   has_an;  /* has_alphanumeric */

   if (s[0] == EOS)                       /* empty string */
      return;

   replace_udo_quotes(s);
   delete_all_divis(s);

   qreplace_all(s, "@dots{}",  7, "...", 3);
   qreplace_all(s, "@minus{}", 8, "-",   1);

   sl = strlen(s);
   has_an = FALSE;

   for (i = 0; i < sl; i++)
   {
      c = s[i];

      if ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') )
      {
         has_an = TRUE;
         break;
      }
   }

   if (has_an)
   {                                      /* Die folgenden Zeichen mag Info nicht in einem String */      
      qdelete_all(s, ",",  1);
      qdelete_all(s, ";",  1);
      qdelete_all(s, ":",  1);
      qdelete_all(s, "'",  1);
      qdelete_all(s, "`",  1);
      qdelete_all(s, "\"", 1);
      qdelete_all(s, ")",  1);
      qdelete_all(s, "(",  1);

                                          /* Einen Punkt am Ende des Titels mag Info gar nicht */
      sl = strlen(s);
      
      while (sl > 0 && s[sl - 1] == '.')
      {
         s[sl - 1] = EOS;
         sl--;
      }

      qreplace_all(s, ". ", 2, ".", 1);

                                          /* Nun noch die doppelten Leerzeichen herausschmeissen */       
      while ( qreplace_all(s, "  ", 2, " ", 1) )
         ;
   }
   else                                   /* PL15: ASCII-Codes einsetzen */
   {
      sl = strlen(s);
      strcpy(d, s);
      s[0] = EOS;

      for (i = 0; i < sl; i++)
      {
         sprintf(a, "%d-", d[i]);
         strcat(s, a);
      }

      s[strlen(s) - 1] = EOS;             /* Noch das letzte "-" entfernen */
   }
}





/*******************************************************************************
*
*  c_tilde():
*     convert tilde and quoted tilde into internal sequences
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_tilde(

char  *s)  /* ^ string */
{
                                          /* Tilde ~ */
   qreplace_all(s, "!~", 2, TILDE_S, TILDE_S_LEN);
#if (NBSP_S_LEN==1)
   replace_char(s, "~", NBSP_S);          /* non breaking space */
#else
                                          /* non breaking space */
   qreplace_all(s, "~", 1, NBSP_S, NBSP_S_LEN);
#endif
}





/*******************************************************************************
*
*  replace_udo_tilde():
*     replace UDO internal sequence by tilde command for target format 
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_udo_tilde(

char  *s)  /* ^ string */
{
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      qreplace_all(s, TILDE_S, TILDE_S_LEN, "\\symbol{126}", 12);
      break;
      
   case TOLYX:
      qreplace_all(s, TILDE_S, TILDE_S_LEN, "~", 1);
      break;
      
   case TOLDS:
      qreplace_all(s, TILDE_S, TILDE_S_LEN, "&tilde;", 7);
      break;
      
   default:
#if (TILDE_S_LEN==1)
      replace_char(s, TILDE_S, "~");
#else
      qreplace_all(s, TILDE_S, TILDE_S_LEN, "~", 1);
#endif
   }
}





/*******************************************************************************
*
*  replace_udo_nbsp():
*     replace internal sequence by a non-breakable space for target format
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void replace_udo_nbsp(

char  *s)  /* ^ string */
{
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
#if (NBSP_S_LEN==1)
      replace_char(s, NBSP_S, "~");
#else
      qreplace_all(s, NBSP_S, NBSP_S_LEN, "~", 1);
#endif
      break;
      
   case TOLYX:
      qreplace_all(s, NBSP_S, NBSP_S_LEN, "\\protected_separator ", 21);
      break;
      
   case TOWIN:
   case TOWH4:
   case TORTF:
   case TOAQV:
      qreplace_all(s, NBSP_S, NBSP_S_LEN, "\\~", 2);
      break;
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      qreplace_all(s, NBSP_S, NBSP_S_LEN, "&nbsp;", 6);
      break;
      
   case TOIPF:
      qreplace_all(s, NBSP_S, NBSP_S_LEN, "&rbl.", 5);
      break;
      
   default:
#if (NBSP_S_LEN==1)
      replace_all(s, NBSP_S, " ");
#else
      qreplace_all(s, NBSP_S, NBSP_S_LEN, " ", 1);
#endif
   }
}





/*******************************************************************************
*
*  convert_tilde():
*     do the whole tilde conversion stuff
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void convert_tilde(

char  *s)  /* ^ string */
{
   c_tilde(s);
   replace_udo_tilde(s);
   replace_udo_nbsp(s);
}





/*******************************************************************************
*
*  c_divis():
*     convert UDO hyphen (!-) into an internal code
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_divis(

char  *s)  /* ^ string */
{
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      qreplace_all(s, "!-", 2, "\\-", 2);
      break;
      
   case TORTF:
      qreplace_all(s, "!-", 2, "\\-", 2);
      break;
      
   case TOSTG:
   case TOAMG:
   case TOASC:
   case TODRC:
   case TOMAN:
   case TONRO:
   case TOPCH:
   case TOSRC:
   case TOSRP:
      qreplace_all(s, "!-", 2, DIVIS_S, DIVIS_S_LEN);
      break;

   case TOHAH:
   case TOHTM:
      if (html_use_hyphenation == TRUE)
         qreplace_all(s, "!-", 2, "&shy;", 5);
      else
         qdelete_all(s, "!-", 2);

      break;

   default:
      qdelete_all(s, "!-", 2);
   }
}





/*******************************************************************************
*
*  specials2ascii():
*     replace UDO special commands by their ASCII equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2ascii(

char  *s)  /* ^ string */
{
   qreplace_all(s, "!..",    3,            "...",     3);

   qreplace_all(s, "(---)",  5,            TEMPO_S,   TEMPO_S_LEN);
   qreplace_all(s, "(--)",   4,            TEMPO_S2,  TEMPO_S2_LEN);
   
   qreplace_all(s, "---",    3,            "-",       1);
   qreplace_all(s, "--",     2,            "-",       1);
   
   qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "---",     3);
   qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--",      2);
}





/*******************************************************************************
*
*  specials2html():
*     replace UDO special commands by their HTML equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2html(

char  *s)  /* ^ string */
{
                                          /* Doesn't work in CAB :-( */
/* qreplace_all(s, "!..",    3,            "&hellip;", 8); */
   qreplace_all(s, "!..",    3,            "...",      3);
   
   qreplace_all(s, "(---)",  5,            TEMPO_S,    TEMPO_S_LEN);
   qreplace_all(s, "(--)",   4,            TEMPO_S2,   TEMPO_S2_LEN);
   qreplace_all(s, "---",    3,            "&mdash;",  7);
   qreplace_all(s, "--",     2,            "&ndash;",  7);
   
   qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "---",      3);
   qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--",       2);
}





/*******************************************************************************
*
*  specials2ps():
*     replace UDO special commands by their PostScript equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2ps(

char  *s)  /* ^ string */
{
   qreplace_all(s, "(---)",  5,            TEMPO_S,  TEMPO_S_LEN);
   qreplace_all(s, "(--)",   4,            TEMPO_S2, TEMPO_S2_LEN);
   qreplace_all(s, "---",    3,            "\\230",  4);
   qreplace_all(s, "--",     2,            "\\227",  4);
   
   qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "---",    3);
   qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--",     2);
                                          /* according to table in ud2ps.h */
   qreplace_all(s, "!..",    3,            "\\214",  4);
   qreplace_all(s, COPY_S,   COPY_S_LEN,   "\\251",  4);
}





/*******************************************************************************
*
*  specials2ipf():
*     replace UDO special commands by their IPF equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2ipf(

char  *s)  /* ^ string */
{
   qreplace_all(s, "!&per.&per.", 11, "&per.&per.&per.", 15);

   qreplace_all(s, "(---)",       5,            TEMPO_S,  TEMPO_S_LEN);
   qreplace_all(s, "(--)",        4,            TEMPO_S2, TEMPO_S2_LEN);
   qreplace_all(s, "---",         3,            "-",      1);
   qreplace_all(s, "--",          2,            "-",      1);

   qreplace_all(s, TEMPO_S,       TEMPO_S_LEN,  "---",    3);
   qreplace_all(s, TEMPO_S2,      TEMPO_S2_LEN, "--",     2);
}





/*******************************************************************************
*
*  specials2info():
*     replace UDO special commands by their Texinfo equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2info(

char  *s)  /* ^ string */
{
   qreplace_all(s, "!..",    3, "@dots{}", 7);

   qreplace_all(s, "(---)",  5,            TEMPO_S,    TEMPO_S_LEN);
   qreplace_all(s, "(--)",   4,            TEMPO_S2,   TEMPO_S2_LEN);
   qreplace_all(s, "---",    3,            "@minus{}", 8);
   qreplace_all(s, "--",     2,            "@minus{}", 8);
   
   qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "---",      3);
   qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--",       2);
}





/*******************************************************************************
*
*  specials2win():
*     replace UDO special commands by their WinHelp equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2win(

char  *s)  /* ^ string */
{
   qreplace_all(s, "!..",    3,            "\\'85",  4);

   qreplace_all(s, "(---)",  5,            TEMPO_S,  TEMPO_S_LEN);
   qreplace_all(s, "(--)",   4,            TEMPO_S2, TEMPO_S2_LEN);
   qreplace_all(s, "---",    3,            "\\'97",  4);
   qreplace_all(s, "--",     2,            "\\'96",  4);
   
   qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "---",    3);
   qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--",     2);
}





/*******************************************************************************
*
*  specials2rtf():
*     replace UDO special commands by their RTF equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void specials2rtf(

char  *s)  /* ^ string */
{
   qreplace_all(s, "!..",    3,            "\\'85",    4);

   qreplace_all(s, "(---)",  5,            TEMPO_S,    TEMPO_S_LEN);
   qreplace_all(s, "(--)",   4,            TEMPO_S2,   TEMPO_S2_LEN);
   qreplace_all(s, "---",    3,            "\\emdash", 7);
   qreplace_all(s, "--",     2,            "\\endash", 7);

   qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "---",      3);
   qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--",       2);
}





/*******************************************************************************
*
*  winspecials2ascii():
*     convert WinHelp special characters to ASCII notation
*
*  Notes:
*     The Search dialog of WinHelp doesn't show these special characters and 
*     typographical quotation marks properly.
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void winspecials2ascii(

char  *s)  /* ^ string */
{
   qreplace_all(s, "\\'85", 4, "...", 3);
   qreplace_all(s, "\\'97", 4, "-",   1);
   qreplace_all(s, "\\'96", 4, "-",   1);

   qreplace_all(s, "\\'84", 4, "\"",  1);
   qreplace_all(s, "\\'93", 4, "\"",  1);
   qreplace_all(s, "\\'94", 4, "\"",  1);
}





/*******************************************************************************
*
*  texvar2ascii():
*     replace LaTeX output placeholders by their ASCII equivalents
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void texvar2ascii(

char  *s)  /* ^ string */
{
   if (strstr(s, "(!") == NULL)           /* no command start block found */
      return;

   qreplace_all(s, "(!TeX)",        6, "TeX",     3);
   qreplace_all(s, "(!LaTeX)",      8, "LaTeX",   5);
   qreplace_all(s, "(!LaTeXe)",     9, "LaTeX2e", 7);
   qreplace_all(s, "(!copyright)", 12, "(c)",     3);

   qreplace_all(s, "(!alpha)",      8, "alpha",   5);
   qreplace_all(s, "(!beta)",       7, "beta",    4);
}





/*******************************************************************************
*
*  c_rtf_quotes():
*     adjust RTF quotes
*
*  Notes:
*     This function replaces "\rquote " by "\rquote  " (regard the double space),
*     when no space follows in the text stream. A space is strictly required to
*     exist directly before a line is output in RTF.
*
*     The reason for this is c_vars() which is called before str2tok(), which 
*     causes the loss of the last space when the line is composed in token_output().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_rtf_quotes(

char  *s)  /* ^ string */
{
   qreplace_all(s, "\\lquote",     7, "\\lquote ",     8);
   qreplace_all(s, "\\ldblquote", 10, "\\ldblquote ", 11);

   qreplace_all(s, "\\rquote",     7, "\\rquote ",     8);
   qreplace_all(s, "\\rdblquote", 10, "\\rdblquote ", 11);

   qreplace_all(s, "\\emdash",     7, "\\emdash ",     8);
   qreplace_all(s, "\\endash",     7, "\\endash ",     8);
}





/*******************************************************************************
*
*  c_quotes_apostrophes():
*     replace single or double quotation marks from UDO format to system quotation marks
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void c_quotes_apostrophes(

char        *s,     /* ^ string */
const char  *aon,   /* ^ opening single quote */
const char  *aoff,  /* ^ closing single quote */
const char  *qon,   /* ^ opening double quote */
const char  *qoff)  /* ^ closing single quote */
{
   while (strstr(s, "''") != NULL)
   {
      (b1stApost) ? replace_once(s, "''", aon) : replace_once(s, "''", aoff);
      
      b1stApost = !b1stApost;
   }
   
   while (strstr(s, "\"\"") != NULL)
   {
      (b1stQuote) ? replace_once(s, "\"\"", qon) : replace_once(s, "\"\"", qoff);
      
      b1stQuote = !b1stQuote;
   }
}





/*******************************************************************************
*
*  c_vars():
*     replace pre-defined placeholders and special strings, like:
*     "", '', !.., or (--)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_vars(

char *s)  /* ^ string */
{
   replace_all(s, "(!today)", lang.today);
   replace_all(s, "(!short_today)", lang.short_today);

   
   /* === quotation marks === */
   
   qreplace_all(s, "(\"\")", 4, TEMPO_S,  TEMPO_S_LEN);
   qreplace_all(s, "('')",   4, TEMPO_S2, TEMPO_S2_LEN);
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      switch (destlang)
      {
      case TOGER:
         c_quotes_apostrophes(s, "`", "'", "\"`", "\"'");
         break;
      default:
         c_quotes_apostrophes(s, "`", "'", "``", "''");
         break;
      }
      
      qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "\\symbol{34}\\symbol{34}", 22);
      qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "\\symbol{39}\\symbol{39}", 22);
      break;
      
   case TOLYX:
      switch (destlang)
      {
      case TOGER:
         c_quotes_apostrophes(s,
            "'", "'",
            "\\begin_inset"INDENT_S"Quotes"INDENT_S"gld\\end_inset"INDENT_S,
            "\\begin_inset"INDENT_S"Quotes"INDENT_S"grd\\end_inset"INDENT_S);
         break;                          
      case TOFRA:
         c_quotes_apostrophes(s,
            "'", "'",
            "\\begin_inset"INDENT_S"Quotes"INDENT_S"fld\\end_inset"INDENT_S,
            "\\begin_inset"INDENT_S"Quotes"INDENT_S"frd\\end_inset"INDENT_S);
         break;                          
      default:
         c_quotes_apostrophes(s,
            "'", "'",
            "\\begin_inset"INDENT_S"Quotes"INDENT_S"eld\\end_inset"INDENT_S,
            "\\begin_inset"INDENT_S"Quotes"INDENT_S"erd\\end_inset"INDENT_S);
         break;
      }
      
      break;
      
   case TORTF:
      if (no_quotes)
      {
         qreplace_all(s, "\"\"", 2, "\"", 1);
         qreplace_all(s, "''",   2, "'",  1);
      }
      else
      {                                   /* PL6 */
         /* Ohne schliessende Leerzeichen, damit nicht Tokens daraus werden! */
         /* Die Leerzeichen werden in c_rtf_quotes() hinzugefuegt! */
         
         c_quotes_apostrophes(s, "\\lquote", "\\rquote", "\\ldblquote", "\\rdblquote");
      }
      
      qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "\"\"", 2);
      qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''",   2);
      break;
      
   case TOWIN:
   case TOAQV:
      if (no_quotes)
      {
         qreplace_all(s, "\"\"", 2, "\"", 1);
         qreplace_all(s, "''", 2, "'", 1);
      }
      else
      {
         switch (destlang)
         {
         case TOGER:
            c_quotes_apostrophes(s, "{\\'91}", "{\\'92}", "{\\'84}", "{\\'93}");
            break;
         default:
            c_quotes_apostrophes(s, "\\'91", "\\'92", "\\'93", "\\'94");
            break;
         }
      }
      
      qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "\"\"", 2);
      qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''",   2);
      break;
      
   case TOLDS:     
      c_quotes_apostrophes(s, "`", "'", "``", "''");
      qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "\"\"", 2);
      qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''",   2);
      break;
      
   case TOHPH:     
      c_quotes_apostrophes(s, "`", "'", "<quote>", "<\\quote>");
      qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "\"\"", 2);
      qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''",   2);
      break;
      
   case TOHAH:                            /* V6.5.17 */
   case TOHTM:                            /*r6pl5*/
   case TOMHH:
      switch (html_quotes)
      {
      case QUOTES_CLASSIC:
         c_quotes_apostrophes(s, "`", "'", "&quot;", "&quot;");
         break;
      case QUOTES_TAGS:
      default:
         c_quotes_apostrophes(s, "<q>", "</q>", "<q>", "</q>");
      }
      
      qreplace_all(s, TEMPO_S,  TEMPO_S_LEN,  "&quot;&quot;", 12);
      qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''",            2);
      break;
      
   case TOKPS:                            /* Changed in V6.5.6 [NHz] */
      {       
         switch (destlang)
         {
         case TOGER:                      /* according to table in ud2ps.h */
            c_quotes_apostrophes(s, "\\220", "\\221", "\\226", "\\225");
            break;
         case TOFRA:                      /* according to table in ud2ps.h */
            c_quotes_apostrophes(s, "\\222", "\\223", "\\253", "\\273");
            break;
         case TONOR:
            c_quotes_apostrophes(s, "\\<", "\\>", "\\\\\\(", "\\\\\\)");
            break;
         default:
            c_quotes_apostrophes(s, "'", "'", "\"", "\"");
            break;
         }
      }
      
      qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
      qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
      break;
   
   default:
      c_quotes_apostrophes(s, "`", "'", "\"", "\"");
      qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
      qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
      break;
   }
   
   
   /* === Miscellaneous === */

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      qreplace_all(s, "!..",           3, "\\ldots ",        7);
      qreplace_all(s, "(---)",         5, "-{}-{}-",         7);
      qreplace_all(s, "(--)",          4, "-{}-",            4);
      qreplace_all(s, "(!grin)",       7, "\\verb/;-)/",    10);
      qreplace_all(s, "(!laugh)",      8, "\\verb/:-)/",    10);
      qreplace_all(s, "(!TeX)",        6, "\\TeX{}",         6);
      qreplace_all(s, "(!LaTeX)",      8, "\\LaTeX{}",       8);
      qreplace_all(s, "(!LaTeXe)",     9, "\\LaTeXe{}",      9);
      qreplace_all(s, "(!copyright)", 12, "\\copyright{}",  12);
      qreplace_all(s, "(!alpha)",      8, "$\\alpha$",       8);
      qreplace_all(s, "(!beta)",       7, "$\\beta$",        7);
      
                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",       7, "\\euro",          5);
      qreplace_all(s, "(!pound)",      8, "GBP",             3);
      qreplace_all(s, "(!reg)",        6, "\\registered{}", 13);
      qreplace_all(s, "(!tm)",         5, "\\trademark{}",  12);
      qreplace_all(s, "(!deg)",        6, "$^{o}$",          6);
      break;
      
   case TOLYX:
      replace_all(s, "(!grin)", "\\family"INDENT_S"typewriter"INDENT_S";-)\\family"INDENT_S"default"INDENT_S);
      replace_all(s, "(!laugh)", "\\family"INDENT_S"typewriter"INDENT_S":-)\\family"INDENT_S"default"INDENT_S);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",  7, "EUR",   3);
      qreplace_all(s, "(!pound)", 8, "GBP",   3);
      qreplace_all(s, "(!reg)",   6, "(r)",   3);
      qreplace_all(s, "(!tm)",    5, "(tm)",  4);
      qreplace_all(s, "(!deg)",   6, " Grad", 5);
      specials2ascii(s);
      texvar2ascii(s);
      break;
      
   case TOINF:
      qreplace_all(s, "(!grin)",       7, "@code{;-)}",   10);
      qreplace_all(s, "(!laugh)",      8, "@code{:-)}",   10);
      qreplace_all(s, "(!TeX)",        6, "@TeX{}",        6);
      qreplace_all(s, "(!copyright)", 12, "@copyright{}", 12);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",       7, "EUR",   3);
      qreplace_all(s, "(!pound)",      8, "GBP",   3);
      qreplace_all(s, "(!reg)",        6, "(r)",   3);
      qreplace_all(s, "(!tm)",         5, "(tm)",  4);
      qreplace_all(s, "(!deg)",        6, " Grad", 5);
      specials2info(s);
      texvar2ascii(s);
      break;
      
   case TOSTG:
   case TOAMG:
   case TOPCH:
      qreplace_all(s, "(!copyright)", 12, COPY_S,  COPY_S_LEN);
      qreplace_all(s, "(!grin)",       7, ";-)",   3);
      qreplace_all(s, "(!laugh)",      8, ":-)",   3);
      qreplace_all(s, "(!alpha)",      8, ALPHA_S, ALPHA_S_LEN);
      qreplace_all(s, "(!beta)",       7, BETA_S,  BETA_S_LEN);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",       7, "EUR",   3);
      qreplace_all(s, "(!pound)",      8, "GBP",   3);
      qreplace_all(s, "(!reg)",        6, "(r)",   3);
      qreplace_all(s, "(!tm)",         5, "(tm)",  4);
      qreplace_all(s, "(!deg)",        6, " Grad", 5);
      specials2ascii(s);
      texvar2ascii(s);
      break;
      
   case TOKPS:
      qreplace_all(s, "(!copyright)", 12, COPY_S,  COPY_S_LEN);
      qreplace_all(s, "(!grin)",       7, ";-\\)", 4); /* New in r6pl15 [NHz] */
      qreplace_all(s, "(!laugh)",      8, ":-\\)", 4);
      qreplace_all(s, "(!alpha)",      8, ALPHA_S, ALPHA_S_LEN);
      qreplace_all(s, "(!beta)",       7, BETA_S,  BETA_S_LEN);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",       7, "\\200", 4);
      qreplace_all(s, "(!pound)",      8, "\\243", 4);
      qreplace_all(s, "(!reg)",        6, "\\256", 3);
      qreplace_all(s, "(!tm)",         5, "\\215", 4);
      qreplace_all(s, "(!deg)",        6, "\\201", 4);

/*    For future use, but commented because of some problems */
/*    qreplace_all(s, "\\(--\\)", 6, "--", 2);
*/
                                          /* Changed in V6.5.5 [NHz] */
      specials2ps(s);
/*    specials2ascii(s);
*/
      texvar2ascii(s);
      break;
      
   case TOASC:
   case TODRC:
   case TOMAN:
   case TONRO:
   case TOTVH:                            /* PL10 */
   case TOSRC:                            /* PL16 */
   case TOSRP:
      qreplace_all(s, "(!grin)",  7, ";-)",   3);
      qreplace_all(s, "(!laugh)", 8, ":-)",   3);
      qreplace_all(s, "(!alpha)", 8, ALPHA_S, ALPHA_S_LEN);
      qreplace_all(s, "(!beta)",  7, BETA_S,  BETA_S_LEN);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",  7, "EUR",   3);
      qreplace_all(s, "(!pound)", 8, "GBP",   3);
      qreplace_all(s, "(!reg)",   6, "(r)",   3);
      qreplace_all(s, "(!tm)",    5, "(tm)",  4);
      qreplace_all(s, "(!deg)",   6, " Grad", 5);
      specials2ascii(s);
      texvar2ascii(s);
      break;
      
   case TOIPF:
      qreplace_all(s, "(!grin)",  7, ";-)",       3);
      qreplace_all(s, "(!laugh)", 8, "&colon.-)", 9);
      qreplace_all(s, "(!alpha)", 8, ALPHA_S,     ALPHA_S_LEN);
      qreplace_all(s, "(!beta)",  7, BETA_S,      BETA_S_LEN);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",  7, "EUR",       3);
      qreplace_all(s, "(!pound)", 8, "GBP",       3);
      qreplace_all(s, "(!reg)",   6, "(r)",       3);
      qreplace_all(s, "(!tm)",    5, "(tm)",      4);
      qreplace_all(s, "(!deg)",   6, " Grad",     5);
      specials2ipf(s);
      texvar2ascii(s);
      break;
      
   case TORTF:
      qreplace_all(s, "(!grin)",       7, "{\\f1 ;-)}", 9);
      qreplace_all(s, "(!laugh)",      8, "{\\f1 :-)}", 9);
      qreplace_all(s, "(!alpha)",      8, "alpha",      5);
      qreplace_all(s, "(!beta)",       7, "beta",       4);
      qreplace_all(s, "(!copyright)", 12, "\\'A9",      4);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",       7, "\\'80",      4);
      qreplace_all(s, "(!pound)",      8, "\\'A3",      4);
      qreplace_all(s, "(!reg)",        6, "\\'AE",      4);
      qreplace_all(s, "(!tm)",         5, "\\'99",      4);
      qreplace_all(s, "(!deg)",        6, "\\'B0",      4);
      specials2rtf(s);
      texvar2ascii(s);
      break;
      
   case TOWIN:
   case TOAQV:
      qreplace_all(s, "(!grin)",       7, "{\\f1 ;-)}", 9);
      qreplace_all(s, "(!laugh)",      8, "{\\f1 :-)}", 9);
      qreplace_all(s, "(!alpha)",      8, "{\\f2 a}",   7);
      qreplace_all(s, "(!beta)",       7, "{\\f2 b}",   7);
      qreplace_all(s, "(!copyright)", 12, "\\'A9",      4);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",       7, "EUR",        3);
      qreplace_all(s, "(!pound)",      8, "GBP",        3);
      qreplace_all(s, "(!reg)",        6, "\\'AE",      4);
      qreplace_all(s, "(!tm)",         5, "(tm)",       4);
      qreplace_all(s, "(!deg)",        6, "\\'B0",      4);
      specials2win(s);
      texvar2ascii(s);
      break;
      
   case TOWH4:
      qreplace_all(s, "(!grin)",       7, "{\\f1 ;-)}", 9);
      qreplace_all(s, "(!laugh)",      8, "{\\f1 :-)}", 9);
      qreplace_all(s, "(!alpha)",      8, "{\\f2 a}",   7);
      qreplace_all(s, "(!beta)",       7, "{\\f2 b}",   7);
      qreplace_all(s, "(!copyright)", 12, "\\'A9",      4);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",       7, "\\'80",      4);
      qreplace_all(s, "(!pound)",      8, "\\'A3",      4);
      qreplace_all(s, "(!reg)",        6, "\\'AE",      4);
      qreplace_all(s, "(!tm)",         5, "(tm)",       4);
      qreplace_all(s, "(!deg)",        6, "\\'B0",      4);
      specials2ascii(s);
      texvar2ascii(s);
      break;
      
   case TOHAH:                            /* V6.5.17 */
   case TOHTM:
   case TOMHH:
      qreplace_all(s, "(!grin)",       7, "<TT>;-)</TT>", 12);
      qreplace_all(s, "(!laugh)",      8, "<TT>:-)</TT>", 12);
      qreplace_all(s, "(!copyright)", 12, "&copy;",        6);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",       7, "&euro;",        6);
      qreplace_all(s, "(!pound)",      8, "&pound;",       7);
      qreplace_all(s, "(!reg)",        6, "&reg;",         5);
      qreplace_all(s, "(!tm)",         5, "&trade;",       7);
      qreplace_all(s, "(!deg)",        6, "&deg;",         5);
      
                                          /* Changed in r6pl15 [NHz] */
      specials2html(s);
      
/*    specials2ascii(s);
*/
      texvar2ascii(s);
      break;
      
   case TOLDS:
      qreplace_all(s, "(!grin)",  7, "<tt/;-)/", 8);
      qreplace_all(s, "(!laugh)", 8, "<tt/:-)/", 8);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",  7, "EUR",      3);
      qreplace_all(s, "(!pound)", 8, "GBP",      3);
      qreplace_all(s, "(!reg)",   6, "(r)",      3);
      qreplace_all(s, "(!tm)",    5, "(tm)",     4);
      qreplace_all(s, "(!deg)",   6, " Grad",    5);
      specials2ascii(s);
      texvar2ascii(s);
      break;
      
   case TOHPH:
      qreplace_all(s, "(!grin)",  7, "<ex>;-)<\\ex>", 12);
      qreplace_all(s, "(!laugh)", 8, "<ex>:-)<\\ex>", 12);

                                          /* New in V6.5.8 [NHz] */
      qreplace_all(s, "(!euro)",  7, "EUR",            3);
      qreplace_all(s, "(!pound)", 8, "GBP",            3);
      qreplace_all(s, "(!reg)",   6, "(r)",            3);
      qreplace_all(s, "(!tm)",    5, "(tm)",           4);
      qreplace_all(s, "(!deg)",   6, " Grad",          5);
      specials2ascii(s);
      texvar2ascii(s);
      break;
   }
}





/*******************************************************************************
*
*  str2manbold():
*     adjust internal text style effect 'bold' for Manualpages
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void str2manbold(

char        *d,          /* ^ reformatted string */
const char  *s)          /* ^ string */
{
   size_t    i;          /* counter */
   char      c[2] = "";  /* char buffer */


   d[0] = EOS;                            /* clear result string */

   if (s[0] == EOS)                       /* empty string */
      return;

   for (i = 0; i < strlen(s); i++)
   {
      c[0] = s[i];
      
      strcat(d, c);
      strcat(d, "\010");
      strcat(d, c);
   }
}





/*******************************************************************************
*
*  str2manunder():
*     adjust internal text style effect 'underlined' for Manualpages
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void str2manunder(

char        *d,          /* ^ reformatted string */
const char  *s)          /* ^ string */
{
   size_t    i;          /* counter */
   char      c[2] = "";  /* char buffer */


   d[0] = EOS;                            /* clear result string */

   if (s[0] == EOS)                       /* empty string */
      return;

   for (i = 0; i < strlen(s); i++)
   {
      strcat(d, "_\010");
      c[0] = s[i];
      strcat(d, c);
   }
}





/*******************************************************************************
*
*  check_html_specs():
*     check if a quoted string is a HTML special character supported by UDO
*  
*  return:
*     TRUE:  is special char, don't cast '&' to '&amp;'
*     FALSE: no special char ...
*
******************************************|************************************/

LOCAL BOOLEAN check_html_specs(

char       *s)  /* ^ string */
{
   size_t   i;  /* counter */


   for (i = 0; i < HTML_SPEC_MAX; i++)
   {
      if (strncmp(html_specs[i], s, strlen(html_specs[i])) == 0)
         return TRUE;
   }

   return FALSE;
}





/*******************************************************************************
*
*  c_man_styles():
*     convert Manualpages styles (bold + underlined)
*
*  Notes:
*     ptr does always point to the first char of the STYLEMAGIC (\033\001).
*     UDO replaces commands like (!B) by its own Escape commands first,
*     formatted as ESC-001-xxx-ESC, where xxx is the relevant style.
*  
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_man_styles(

char        *s)               /* ^ string */
{
   char     *ptr;             /* ^ to STYLEMAGIC in string */
   char      alt[512],        /* */
             neu[512];        /* */
   char     *start;           /* buffer for start of style in string */
   char      s_char[2] = "";  /* */
   BOOLEAN   bold_active;     /* TRUE: bold style on, FALSE: bold style off */
   BOOLEAN   under_active;    /* TRUE: underlined on, FALSE: underlined off */
   BOOLEAN   replace_it;      /* */
   

   if (s[0] == EOS)                       /* empty string */
      return;

   bold_active  = styleflag.bold;
   under_active = styleflag.underlined;
   replace_it   = FALSE;

   ptr = strstr(s, STYLEMAGIC);           /* see Notes above! */

   if (ptr == NULL)                       /* no style found */
      return;

   start = ptr;

   alt[0] = EOS;                          /* clear buffer */

   do
   {
      if (ptr[0] != STYLEMAGIC[0] && ptr[0] != STYLEMAGIC[1])
      {
         if (bold_active || under_active)
         {
            s_char[0] = ptr[0];
            strcat(alt, s_char);
         }
      }
      else if (ptr[0] == STYLEMAGIC[0] && ptr[1] == STYLEMAGIC[1])
      {
         switch (ptr[2])         
         {
         case C_BOLD_ON:
            bold_active = TRUE;
            alt[0] = EOS;
            ptr += 3;
            start = ptr + 1;
            break;
         
         case C_BOLD_OFF:
            bold_active = FALSE;
            ptr += 3;
            str2manbold(neu, alt);
            replace_it = TRUE;
            break;

         case C_UNDER_ON:
            under_active = TRUE;
            alt[0] = EOS;
            ptr += 3;
            start = ptr + 1;
            break;
            
         case C_UNDER_OFF:
            under_active = FALSE;
            ptr += 3;
            str2manunder(neu, alt);
            replace_it = TRUE;
            break;
         }
      }

      if (replace_it)
      {
         replace_once(start, alt, neu);
         ptr += (strlen(neu) - strlen(alt));
         alt[0] = EOS;
         replace_it = FALSE;
      }

      ptr++;          
      
   } while (ptr[0] != EOS);
}





/*******************************************************************************
*
*  XXXXXXXXXXXXXXXXXXXXX():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/






/*******************************************************************************
*
*  auto_quote_chars():
*     ??? (description missing)
*  
*  return:
*     -
*
******************************************|************************************/

GLOBAL void auto_quote_chars(

char             *s,              /* ^ string */
BOOLEAN           all)            /* */
{
   register int   i,              /* */
                  tabidx;         /* */
   char          *ptr,            /* */
                 *oldptr;         /* */
   const char    *ptr_quoted;     /* */
   char           s_temp[32];     /* */
   char           s_char[2];      /* */
   BOOLEAN        aqc_verb;       /* */
   BOOLEAN        found = FALSE;  /* */
   size_t         cmplen,         /* */
                  sl_verb_on,     /* */
                  sl_verb_off;    /* */


   if (s[0] == EOS)                       /* empty string */
      return;

   if (no_umlaute)
      umlaute2ascii(s);

   switch(desttype)
   {
   case TOASC:                            /* Hier muss nicht gequotet werden! */
   case TODRC:
   case TOMAN:
   case TONRO:
   case TOSTG:
   case TOAMG:
   case TOTVH:
   case TOINF:
   case TOSRC:
   case TOSRP:
#ifdef __TOS__
      replace_all(s, BETA_S, "\236");
#endif
#ifdef __MSDOS__
      replace_all(s, "\236", "\341");
#endif
#ifdef __MSDOS850__
      replace_all(s, "\236", "\341");
#endif
      if (bDocUniversalCharsetOn)
         uni2ascii(s);

      /* r6pl2: Neue Version: immer quoten */
      /* nicht auf !raw !stg testen, da dies im wichtigen pass2() */
      /* nicht auftreten kann, da vorher die Zeilen mit */
      /* c_special_commands() bearbeitet werden. */

      switch (desttype)
      {
      case TOSTG:                         /* ST-Guide */
         replace_1at_by_2at(s);
         return;

      case TOINF:
         qreplace_all(s, "@", 1, "@@", 2);
         qreplace_all(s, "}", 1, "@}", 2);
         qreplace_all(s, "{", 1, "@{", 2);
         return;

      case TOTVH:                         /* r5pl10 */
         qreplace_all(s, "{", 1, "{{", 2);
         return;
      }

      return;
   }       


   ptr = s;

   if (!all)
   {
      /* Wenn in der Zeile ein Kommando steht, dann nur den Rest */
      /* quoten, wenn das Kommando einen Parameter enthaelt, */
      /* der gequotet werden muss! */

      if (s[0] == META_C && s[1] >= 'a' && s[1] <= 'z')
      {
         for (i = 0; i < MAXQUOTECMD; i++)
         {
            cmplen = quotecommand[i].cmdlen;

            if (strncmp(s, quotecommand[i].cmd, cmplen) == 0)
            {
               /* Das naechste Zeichen muss aber Space oder Tab sein! */
               if (s[cmplen] == ' ' || s[cmplen] == '\t')
               {
                  found = TRUE;
                  ptr += cmplen;
                  break;
               }
            }

            if ((cmplen = quotecommand[i].abblen) > 0)
            {
               /*r6pl12: Abkuerzungen auch beachten */
               if (strncmp(s, quotecommand[i].abb, cmplen) == 0)
               {
                  /* Das naechste Zeichen muss aber Space oder Tab sein! */
                  if (s[cmplen] == ' ' || s[cmplen] == '\t')
                  {
                     found = TRUE;
                     ptr += cmplen;
                     break;
                  }
               }
            }
         }

         if (!found)
            return;
      }
   }


   ptr_quoted = NULL;
   s_temp[0] = EOS;
   s_char[1] = EOS;
   aqc_verb = last_aqc_verb;              /* Pl13: vorher = TRUE */

   sl_verb_on = CMD_STYLELEN;
   sl_verb_off = CMD_STYLELEN;

   while (ptr[0] != EOS)
   {
      /* PL13: Innerhalb (!V)...(!v) Leerzeichen durch interne  */
      /* feste Leerzeichen ersetzen, damit token_output() nicht */
      /* \verb+...+ umbricht. */

      if (desttype == TOTEX || desttype == TOPDL)
      {
         if (aqc_verb || styleflag.verbatim)
         {
            if (ptr[0] == ' ')
            {
               ptr[0] = INDENT_C;
               goto NO_QUOTE_NEEDED;
            }
         }
      }

      /* Das Alphabet und die Ziffern muessen nie gequotet werden! */
      /* Also einfach den ganzen Rotz ueberspringen */

      if (ptr[0] == ' ')                  /* space */
         goto NO_QUOTE_NEEDED;

      if (ptr[0] >= 'a' && ptr[0] <= 'z') /* [a..z] */
         goto NO_QUOTE_NEEDED;

      if (ptr[0] >= 'A' && ptr[0] <= 'Z') /* [A..Z] */
         goto NO_QUOTE_NEEDED;

      if (ptr[0] >= '0' && ptr[0] <= '9') /* [0..9] */
         goto NO_QUOTE_NEEDED;


      if ((desttype == TOTEX || desttype == TOPDL) && !all)
      {
         if (strncmp(ptr, CMD_VERB_ON, sl_verb_on) == 0)
         {
            /* Optimierung durch Hochzaehlen von ptr */
            aqc_verb = TRUE;
            ptr += (sl_verb_on - 1);
            goto NO_QUOTE_NEEDED;
         }

         if (strncmp(ptr, CMD_VERB_OFF, sl_verb_off) == 0)
         {
            /* Optimierung durch Hochzaehlen von ptr */
            aqc_verb = FALSE;
            ptr += (sl_verb_off - 1);
            goto NO_QUOTE_NEEDED;
         }
      }

      /* Sonderbehandlung fuer doppelte Anfuehrungszeichen und Apostrophe */
      if (ptr[0] == '\"' && ptr[1] == '\"')
      {
         /* Doppelquotes: "" */
         ptr++;
         goto NO_QUOTE_NEEDED;
      }

      /* Gequotete Quotes: ("") */
      if (ptr[0] == '(' && ptr[1] == '\"' && ptr[2] == '\"' && ptr[3] == ')')
      {
         ptr += 3;
         goto NO_QUOTE_NEEDED;
      }

      /* Gequotete Apostrophe: ('') */
      if (ptr[0] == '(' && ptr[1] == '\'' && ptr[2] == '\'' && ptr[3] == ')')
      {
         ptr += 3;
         goto NO_QUOTE_NEEDED;
      }


      /* Sonderbehandlung fuer Platzhalter, welche spaeter */
      /* gequotet werden (macro, define, link, index) */
      /* PL6: aber nicht in verbatim-Umgebungen! */

      /* Dabei beruecksichtigen, dass Klammern innerhalb */
      /* durch ein Ausrufungszeichen gequotet werden. */              

      if (pflag[PASS2].env != ENV_VERBATIM)
      {
         if (ptr[0] == '(' && ptr[1] == META_C && ptr[2] != QUOTE_C)
         {
            oldptr = ptr;                 /* Pointer sichern */
            ptr++;

            while (ptr[0] != EOS && ptr[0] != ')' )
            {
               if (ptr[0] == '!' && ptr[1] == ')' )
               {
                  ptr++;                  /* gequotete Klammer ueberspringen */
               }

               ptr++;
            }       

            if (ptr[0] == EOS)
            {
               /* PL16: Falls der Pointer auf das Ende zeigt, dann */
               /* ist etwas schiefgelaufen oder aber es handelte */
               /* sich gar nicht um einen Parameter (z.B. "(!)") */
               /* In dem Falle den alten Pointer restaurieren */

               ptr = oldptr;
               ptr++;
            }
            else
            {
               /* Optimierung: Rest ueberspringen */
               goto NO_QUOTE_NEEDED;
            }
         }
      }


      switch (desttype)
      {
      case TOTEX:
      case TOPDL:
         if ((all) || (!styleflag.verbatim && !aqc_verb) )
         {
            found = FALSE;

            if (((UCHAR) ptr[0]) > 127 )
            {
               tabidx = ((UCHAR) ptr[0]) - 128;

               if (chrtab[tabidx].tex[0] != EOS)
               {
                  ptr_quoted = chrtab[tabidx].tex;
                  found = TRUE;
               }
            }
            else
            {
               for (i = 0; i < MAXTEX7BIT; i++)
               {
                  if (( /*(UCHAR)*/ ptr[0]) == tex7bit[i].c)
                  {
                     ptr_quoted = tex7bit[i].quoted;
                     found = TRUE;
                     break;
                  }
               }
            }

            if (!found)
            {
               if ((UCHAR) ptr[0] >= 127)
               {
                  warning_no_texchar(ptr[0]);     /* PL12 */
                  sprintf(s_temp, "$\\symbol{%d}$", (UCHAR) ptr[0]);
                  ptr_quoted = s_temp;
               }
            }
         }
         break;

      case TOLYX:
         found = FALSE;

         for (i = 0; i < MAXLYX7BIT; i++)
         {
            if (( /*(UCHAR)*/ ptr[0]) == lyx7bit[i].c)
            {
               ptr_quoted = lyx7bit[i].quoted;
               found = TRUE;
               break;
            }
         }
         break;

      case TOIPF:
         found = FALSE;

         for (i = 0; i < MAXIPF7BIT; i++)
         {
            if (( /*(UCHAR)*/ ptr[0]) == ipf7bit[i].c)
            {
               ptr_quoted = ipf7bit[i].quoted;
               found = TRUE;
               break;
            }
         }
         break;

      case TORTF:
         found = FALSE;

         if (((UCHAR) ptr[0]) > 127 )
         {
            /* Wie bei WinHelp */
            if (iCharset != CODE_LAT1)
            {
               tabidx = ((UCHAR) ptr[0]) - 128;

               if (chrtab[tabidx].ansi[0] != EOS)
               {
                  ptr_quoted = chrtab[tabidx].ansi;
                  found = TRUE;
               }
               else
               {
                  warning_cannot_recode(ptr[0], "system charset", "Windows ANSI");
                  ptr[0] = '?';
               }
            }

            if (!found)
            {
               sprintf(s_temp, "\\'%X", (UCHAR) ptr[0]);
               ptr_quoted = s_temp;
            }
         }
         else
         {
            for (i = 0; i < MAXRTF7BIT; i++)
            {
               if (( ptr[0]) == rtf7bit[i].c)
               {
                  ptr_quoted = rtf7bit[i].quoted;
                  found = TRUE;
                  break;
               }
            }
         }
         break;

      case TOKPS:
         found = FALSE;

         if (((UCHAR) ptr[0]) > 127)
         {       
            if (iCharset != CODE_LAT1)
            {
               tabidx = ((UCHAR) ptr[0]) - 128;

               if (chrtab[tabidx].ps[0] != EOS)
               {
                  ptr_quoted = chrtab[tabidx].ps;
                  found = TRUE;
               }
               else
               {
                  warning_cannot_recode(ptr[0], "system charset", "Windows ANSI");
                  ptr[0] = '?';
               }
            }

            if (!found)
            {
               sprintf(s_temp, "\\%03o", (UCHAR) ptr[0]);
               ptr_quoted = s_temp;
            }
         }

         /* Changed in V6.5.5 [NHz] */
#if 0
         else
         {
            LOCAL QUOTEINFO const   ps7bit[] =
            {
               { '[',  "\\["  },
               { ']',  "\\]"  },

               { '(',  "\\("  },
               { ')',  "\\)"  },
               { '\\', "\\\\" }
            };


            for (i = 0; i < sizeof(ps7bit) / sizeof(ps7bit[0]); i++)
            {
               if ((ptr[0]) == ps7bit[i].c)
               {
                  ptr_quoted = ps7bit[i].quoted;
                  found = TRUE;
                  break;
               }
            }
         }
#endif
         break;

      case TOWIN:
      case TOWH4:
      case TOAQV:
         found = FALSE;

         if (((UCHAR) ptr[0]) > 127)
         {
            if (iCharset != CODE_LAT1)
            {
               tabidx = ((UCHAR) ptr[0]) - 128;

               if (chrtab[tabidx].ansi[0] != EOS)
               {
                  ptr_quoted = chrtab[tabidx].ansi;
                  found = TRUE;
               }
               else
               {
                  warning_cannot_recode(ptr[0], "system charset", "Windows ANSI");
                  ptr[0] = '?';
               }
            }

            if (!found)
            {
               sprintf(s_temp, "\\'%X", ((UCHAR) ptr[0]) );
               ptr_quoted = s_temp;
            }
         }
         else
         {
            for (i = 0; i < MAXWIN7BIT; i++)
            {
               if ((/*(UCHAR)*/ ptr[0]) == win7bit[i].c)
               {
                  ptr_quoted = win7bit[i].quoted;
                  found = TRUE;
                  break;
               }
            }
         }
         break;

      case TOPCH:
         if (ptr[0] == '\\')
         {
            strcpy(s_temp, "\\\\");
            ptr_quoted = s_temp;
         }
         break;

      case TOHAH:                         /* HTML Apple Help (since V6.5.17) */
      case TOHTM:                         /* HTML */
      case TOMHH:                         /* Microsoft HTML Help */
         found = FALSE;

         if (((UCHAR) ptr[0]) > 127)
         {
            if (!html_ignore_8bit)
            {
               tabidx = ((UCHAR) ptr[0]) - 128;

               if (chrtab[tabidx].html[0] != EOS)
               {
                  ptr_quoted = chrtab[tabidx].html;
                  found= TRUE;
               }
               else
               {
                  warning_no_isochar(ptr[0]);
               }
            }
         }
         else
         {
            for (i = 0; i < MAXHTML7BIT; i++)
            {
               if (ptr[0] == html7bit[i].c)
               {
                  if (ptr[0] == '&')      /* insert check for HTML entities */
                  {
                     if (check_html_specs(ptr) == FALSE)
                     {
                        ptr_quoted = html7bit[i].quoted;
                        found = TRUE;
                        break;
                     }
                  }
                  else
                  {                  
                     ptr_quoted = html7bit[i].quoted;
                     found = TRUE;
                     break;
                  }
               }
            }
         }
         break;

      case TOLDS:
         found = FALSE;

         if (((UCHAR) ptr[0]) > 127)
         {
            tabidx = ((UCHAR) ptr[0]) - 128;

            if (chrtab[tabidx].html[0] != EOS)
            {
               ptr_quoted = chrtab[tabidx].html;
               found = TRUE;
            }
            else
            {
               warning_no_isochar(ptr[0]);
            }
         }
         else
         {
            for (i = 0; i < MAXLDS7BIT; i++)
            {
               if ((ptr[0]) == lds7bit[i].c)
               {
                  ptr_quoted = lds7bit[i].quoted;
                  found = TRUE;
                  break;
               }
            }
         }
         break;

      case TOHPH:
         found = FALSE;

         if (((UCHAR) ptr[0]) > 127)
         {
            tabidx = ((UCHAR) ptr[0]) - 128;

            if (chrtab[tabidx].html[0] != EOS)
            {
               ptr_quoted = chrtab[tabidx].html;
               found= TRUE;
            }
            else
            {
               warning_no_isochar(ptr[0]);
            }
         }
         else
         {
            for (i = 0; i < MAXHTAG7BIT; i++)
            {
               if (ptr[0] == htag7bit[i].c)
               {
                  ptr_quoted = htag7bit[i].quoted;
                  found = TRUE;
                  break;
               }
            }
         }
         break;

      }  /* switch (desttype) */


      if (ptr_quoted != NULL && ptr_quoted[0] != EOS)
      {
         s_char[0] = ptr[0];
         cmplen = strlen(ptr_quoted);
         qreplace_once(ptr, s_char, 1, ptr_quoted, cmplen);

         ptr = ptr + cmplen - 1;
         s_temp[0] = EOS;
         ptr_quoted = NULL;
      }

NO_QUOTE_NEEDED:
      ptr++;
   }

   if (bDocUniversalCharsetOn)
   {
      uni2misc(s);
   }

   if (iUdopass == PASS2)
   {
      last_aqc_verb = aqc_verb;           /* PL13: Status sichern */
   }
   else
   {
      /* r6pl9: In pass1() werden nur Kommandozeilen beachtet. */
      /* Wird last_aqc_verb nicht zurueckgesetzt, dann kracht es! */
      last_aqc_verb = FALSE;
   }

} /* auto_quote_chars */





/*******************************************************************************
*
*  auto_quote_texindex():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void auto_quote_texindex(

char  *s)  /* ^ string */
{
   if (desttype == TOTEX || desttype == TOPDL)
   {
#if 0
      qreplace_all(s, "{\\\"a}", 5, "\\\"a", 3);     /* {\"a} -> \"a */
      qreplace_all(s, "{\\\"o}", 5, "\\\"o", 3);     /* {\"o} -> \"o */
      qreplace_all(s, "{\\\"u}", 5, "\\\"u", 3);     /* {\"u} -> \"u */
      qreplace_all(s, "{\\\"A}", 5, "\\\"A", 3);     /* {\"A} -> \"A */
      qreplace_all(s, "{\\\"O}", 5, "\\\"O", 3);     /* {\"O} -> \"O */
      qreplace_all(s, "{\\\"U}", 5, "\\\"U", 3);     /* {\"U} -> \"U */
#endif
      qreplace_all(s, "\"`",     2, "\"\"`", 3);     /* "` -> \"` */
      qreplace_all(s, "\"'",     2, "\"\"'", 3);     /* "' -> \"' */
      qreplace_all(s, "!",       1, "\"!",   2);     /* !  -> "! */
      qreplace_all(s, "@",       1, "\"@",   2);     /* @  -> "@ */
      qreplace_all(s, "|",       1, "\"|",   2);     /* |  -> "| */
   }
}





/*******************************************************************************
*
*  auto_quote_linedraw():
*     adjust characgters for Linedraw environment (RTF only)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void auto_quote_linedraw(

char             *s)              /* ^ string */
{
   register int   i;              /* */
   char          *ptr,            /* */
                 *quoted;         /* */
   char           sTemp[32];      /* */
   char           sChar[2] = "";  /* */


   ptr = s;

   while (ptr[0] != EOS)
   {
      if ( ((UCHAR)ptr[0]) > 127)
      {
         sprintf(sTemp, "\\'%X", (UCHAR)ptr[0]);
         sChar[0] = ptr[0];
         qreplace_once(ptr, sChar, 1, sTemp, 4);
         ptr += 3;
      }
      else
      {       
         for (i = 0; i < MAXRTF7BIT; i++)
         {
            if ( (ptr[0]) == rtf7bit[i].c)
            {
               quoted = rtf7bit[i].quoted;
               sChar[0] = ptr[0];
               replace_once(ptr, sChar, quoted);
               ptr= ptr + strlen(quoted) - 1;
               break;
            }
         }
      }

      ptr++;

   }  /* while */
}





/*******************************************************************************
*
*  init_module_chars():
*     init module variables
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_chars(void)
{
   last_aqc_verb      = FALSE;            /* */
   texinfo_np_counter = 0;                /* */
}


/* +++ EOF +++ */
