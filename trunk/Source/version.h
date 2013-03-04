/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : version.h
*  Symbol prefix: version
*
*  Description  : Compiler- und systemabhaengige Defines setzen
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
*  2009:
*    ggs Jan 11: Change year
*  2010:
*    fd  Jan 23: - year updated
*                - converted all German umlauts in comments into plain ASCII
*    fd  Feb 12: comments reformatted
*    fd  Feb 18: CODE_LAT2
*    fd  Feb 19: CODE_CP1257
*    fd  Feb 20: CODE_CP1251
*    fd  Feb 22: CODE_CP1253
*    fd  Feb 23: - CODE_MAC_CE
*                - CODE_LAT1 -> CODE_CP1252
*                - CODE_LAT2 -> CODE_LATIN2
*                - CODE_LATIN1
*                - UDO_PL -> UDO_BUILD (no more patchlevels)
*                - v7.00 RC1
*    fd  Feb 24: - CODE_CP1254 (Turkish)
*                - CODE_CP1255 (Hebrew)
*                - CODE_CP1256 (Arabic)
*                - CODE_CP1258 (Vietnamese)
*    fd  Feb 25: v7.00 RC2
*    fd  Mar 01: v7.00 public release
*    fd  Mar 02: "Mac OS" and "Mac OS X" love spaces ;-)
*    fd  Mar 04: version strings prepared for v7.01 beta
*    fd  Mar 05: - CODE_LATIN3
*                - CODE_LATIN4
*                - CODE_CYRILLIC
*                - CODE_ARABIC
*                - CODE_GREEK
*                - CODE_HEBREW
*    fd  Mar 08: - COOE_TURKISH
*                - CODE_NORDIC
*                - CODE_THAI
*                - CODE_BALTIC
*                - CODE_CELTIC
*                - CODE_LATIN9
*                - CODE_LATIN10
*    fd  Mar 12: Linux gcc doesn't like tmpnam
*    fd  May 19: v7.01 RC1 (1126)
*    fd  May 25: v7.01 (1151)
*  2011:
*    fd  Feb 14: copyright year updated
*  2013:
*    ggs Mar 03: copyright year updated
*
******************************************|************************************/

#ifndef VERSION_H
#define VERSION_H





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

   /* --- Einige Flags um Neuentwicklungen zu (de)aktivieren --- */

#define USE_HTML_FOLDERS     0            /* Ordnerstruktur erzeugen?       */
#define USE_OLD_BUILD_FILE   1            /* build_search_file() benutzen?  */
#define USE_MYTEXTFILE       0            /* Eigene Dateiroutinen benutzen? */


   /* --- Debugging-Flags --- */
   
#define CHECK_REPLACE_LEN    0            /* qreplace*() checken? */


   /* --- Release-Nummer und Patchlevel setzen --- */

#define UDO_REL     "7"
#define UDO_SUBVER  "01"
#define UDO_BUILD   "(1151)"
#define UDO_URL     "http://www.udo-open-source.org/"
#define UDO_MADE    "Made with UDO"

   /* --- Copyright Meldung --- */

#define COPYRIGHT           "Copyright (C) 1995-2001 by Dirk Hagedorn\nCopyright (C) 2001-2013 by The UDO Community"
#define UDO_COPYRIGHT_TEXT  "Copyright (!copyright) 1995-2001 by Dirk Hagedorn\t(!nl)\nCopyright (!copyright) 2001-2013 by The UDO Community\t(!nl)\n"

   /* --- Zeichensaetze --- */

#define CODE_CP1252    0                  /* Microsoft Windows codepage 1252 */
#define CODE_DOS       1                  /* IBM PC */
#define CODE_437       1                  /* DOS Codepage 437 (wie IBM PC) */
#define CODE_TOS       2                  /* Atari TOS */
#define CODE_HP8       3                  /* Hewlett Packard Roman-8 */
#define CODE_MAC       4                  /* Apple Macintosh */
#define CODE_NEXT      5                  /* NextSTep */
#define CODE_850       6                  /* DOS Codepage 850 */
#define CODE_UTF8      7                  /* UTF-8 (e.g. for BeOS) */
#define CODE_CP1250    8                  /* Microsoft Windows codepage 1250 "CE" */
#define CODE_LATIN2    9                  /* ISO Latin 2 (iso-8859-2) "Middle European" */
#define CODE_CP1257   10                  /* Microsoft Windows codepage 1257 "Baltic" */
#define CODE_CP1251   11                  /* Microsoft Windows codepage 1251 "Russian" */
#define CODE_CP1253   12                  /* Microsoft Windows codepage 1253 "Greek" */
#define CODE_MAC_CE   13                  /* Apple Central Europe */
#define CODE_LATIN1   14                  /* ISO Latin 1 (iso-8859-1) "West European" */
#define CODE_CP1254   15                  /* Microsoft Windows codepage 1254 "Turkish" */
#define CODE_CP1255   16                  /* Microsoft Windows codepage 1255 "Hebrew" */
#define CODE_CP1256   17                  /* Microsoft Windows codepage 1256 "Arabic" */
#define CODE_CP1258   18                  /* Microsoft Windows codepage 1258 "Vietnamese" */
#define CODE_LATIN3   19                  /* ISO Latin 3 (iso-8859-3) "South European" */
#define CODE_LATIN4   20                  /* ISO Latin 4 (iso-8859-4) "North European" */
#define CODE_CYRILLIC 21                  /* ISO Cyrillic (iso-8859-5) */
#define CODE_ARABIC   22                  /* ISO Arabic (iso-8859-6) */
#define CODE_GREEK    23                  /* ISO Greek (iso-8859-7) */
#define CODE_HEBREW   24                  /* ISO Hebrew (iso-8859-8) */
#define CODE_TURKISH  25                  /* ISO Latin 5 (iso-8859-9) "Turkish" */
#define CODE_NORDIC   26                  /* ISO Latin 6 (iso-8859-10) "Nordic" */
#define CODE_THAI     27                  /* ISO Thai (iso-8859-11) */
#define CODE_BALTIC   28                  /* ISO Latin 7 (iso-8859-13) "Baltic" */
#define CODE_CELTIC   29                  /* ISO Latin 8 (iso-8859-14) "Celtic" */
#define CODE_LATIN9   30                  /* ISO Latin 9 (iso-8859-15) "West European" */
#define CODE_LATIN10  31                  /* ISO Latin 10 (iso-8859-16) "South East European" */

#define CODE_TOTAL    32                  /* # of supported encodings */

   /* --- Compiler- und systemabhaengige Dinge setzen --- */

#ifdef __TOS__
#define UDO_OS               "TOS"
#define USE_SLASH            0
#define USE_LONG_FILENAMES   0
#define USE_LATIN1_CHARSET   0
#define SYSTEM_CHARSET       CODE_TOS
#define HAVE_STRUPR          1
#define HAVE_STRLWR          1
#define HAVE_STRICMP         1
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      0
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          0
#endif

                                          /* OS/2 Support: OS/2 verhaelt sich wie DOS */
#ifdef __OS2__
#define __MSDOS__
#endif

#ifdef __MSDOS__
#define UDO_OS               "DOS"
#define USE_SLASH            0
#define USE_LONG_FILENAMES   0
#define USE_LATIN1_CHARSET   0
#define SYSTEM_CHARSET       CODE_437
#define HAVE_STRUPR          1
#define HAVE_STRLWR          1
#define HAVE_STRICMP         1
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      0
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __OS2__
#undef UDO_OS
#define UDO_OS          "OS/2"
#endif

#ifdef __MSDOS850__
#define UDO_OS               "DOS"
#define USE_SLASH            0
#define USE_LONG_FILENAMES   0
#define USE_LATIN1_CHARSET   0
#define SYSTEM_CHARSET       CODE_850
#define HAVE_STRUPR          1
#define HAVE_STRLWR          1
#define HAVE_STRICMP         1
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      0
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __WIN32__
#define UDO_OS               "Win32"
#define USE_SLASH            0
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   1
#define SYSTEM_CHARSET       CODE_CP1252
#define HAVE_STRUPR          1
#define HAVE_STRLWR          1
#define HAVE_STRICMP         1
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      0
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __LINUX__
#define UDO_OS               "Linux"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   1
#define SYSTEM_CHARSET       CODE_CP1252
#define HAVE_STRUPR          0
#define HAVE_STRLWR          0
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        0
#define HAVE_STRCASECMP      1
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          0
#endif

#ifdef __AMIGA__
#define UDO_OS               "Amiga"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   1
#define SYSTEM_CHARSET       CODE_CP1252
#define HAVE_STRUPR          0
#define HAVE_STRLWR          0
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      1
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __SINIX__
#define UDO_OS               "Sinix"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   1
#define SYSTEM_CHARSET       CODE_CP1252
#define HAVE_STRUPR          1
#define HAVE_STRLWR          1
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      0
#define HAVE_SYS_ERRLIST     0
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __SUNOS__
#define UDO_OS               "SunOS"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   1
#define SYSTEM_CHARSET       CODE_CP1252
#define HAVE_STRUPR          0
#define HAVE_STRLWR          0
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      0
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __IRIX__
#define UDO_OS               "IRIX"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   1
#define SYSTEM_CHARSET       CODE_CP1252
#define HAVE_STRUPR          0
#define HAVE_STRLWR          0
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      1
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __HPUX_ISO__
#define DO_OS               "HP-UX"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   1
#define SYSTEM_CHARSET       CODE_CP1252
#define HAVE_STRUPR          1
#define HAVE_STRLWR          0
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      1
#define HAVE_SYS_ERRLIST     0
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __HPUX_ROMAN8__
#define UDO_OS               "HP-UX"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   0
#define SYSTEM_CHARSET       CODE_HP8
#define HAVE_STRUPR          1
#define HAVE_STRLWR          1
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      1
#define HAVE_SYS_ERRLIST     0
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __MACOS__
#define UDO_OS               "Mac OS"
#define USE_SLASH            0
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   0
#define SYSTEM_CHARSET       CODE_MAC
#define HAVE_STRUPR          0
#define HAVE_STRLWR          0
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      0
#define HAVE_SYS_ERRLIST     0
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      1
#define HAVE_TMPNAM          1
#endif

#ifdef __MACOSX__
#define UDO_OS               "Mac OS X"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   0
#define SYSTEM_CHARSET       CODE_MAC
#define HAVE_STRUPR          0
#define HAVE_STRLWR          0
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        0
#define HAVE_STRCASECMP      1
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __NEXTSTEP__
#define UDO_OS               "NeXTStep"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   0
#define SYSTEM_CHARSET       CODE_NEXT
#define HAVE_STRUPR          1
#define HAVE_STRLWR          1
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      0
#define HAVE_SYS_ERRLIST     1
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      0
#define HAVE_TMPNAM          1
#endif

#ifdef __BEOS__
#define UDO_OS               "BeOS"
#define USE_SLASH            1
#define USE_LONG_FILENAMES   1
#define USE_LATIN1_CHARSET   0
#define SYSTEM_CHARSET       CODE_UTF8
#define HAVE_STRUPR          0
#define HAVE_STRLWR          0
#define HAVE_STRICMP         0
#define HAVE_STRNICMP        1
#define HAVE_STRCASECMP      0
#define HAVE_SYS_ERRLIST     0
#define HAVE_STRERROR        1
#define USE_SETFILETYPE      1
#define HAVE_TMPNAM          1
#endif

#endif   /* VERSION_H */





/*******************************************************************************
*
*     ERROR OUTPUT
*
******************************************|************************************/

#ifndef UDO_OS
#error  "UDO_OS not defined!"
#endif

#ifndef USE_SLASH
#error  "USE_SLASH not defined!"
#endif

#ifndef USE_LONG_FILENAMES
#error  "USE_LONG_FILENAMES not defined!"
#endif

#ifndef USE_LATIN1_CHARSET
#error  "USE_LATIN1_CHARSET not defined!"
#endif

#ifndef SYSTEM_CHARSET
#error  "SYSTEM_CHARSET not defined!"
#endif

#ifndef HAVE_STRUPR
#error  "HAVE_STRUPR not defined!"
#endif

#ifndef HAVE_STRLWR
#error  "HAVE_STRLWR not defined!"
#endif

#ifndef HAVE_STRICMP
#error  "HAVE_STRICMP not defined!"
#endif

#ifndef HAVE_STRNICMP
#error  "HAVE_STRNICMP not defined!"
#endif

#ifndef HAVE_STRCASECMP
#error  "HAVE_STRCASECMP not defined!"
#endif

#ifndef HAVE_SYS_ERRLIST
#error  "HAVE_SYS_ERRLIST not defined!"
#endif

#ifndef HAVE_STRERROR
#error  "HAVE_STRERROR not defined!"
#endif

#ifndef USE_SETFILETYPE
#error  "USE_SETFILETYPE not defined!"
#endif

#ifndef HAVE_TMPNAM
#error  "HAVE_TMPNAM not defined!"
#endif

/* +++ EOF +++ */
