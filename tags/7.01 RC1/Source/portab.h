/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : portab.h
*  Symbol prefix: -
*
*  Description  : Global portability definitions for several supported platforms.
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
*  Co-Authors   : Ulf Dunkel (fd), Gerhard Stoll (ggs)
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
*    fd  Feb 11: file reformatted and tidied up, TAB-free
*    fd  Feb 19: NIL introduced
*    fd  Feb 22: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*
******************************************|************************************/

#ifndef PORTAB_H
#define PORTAB_H





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#ifndef TRUE
#define TRUE   1
#define FALSE  0
#endif

#define NIL        (-1)                   /* 'invalid' indicator */
#define EOS        '\0'

#define LOCAL      static

#ifndef UNUSED
#define UNUSED(x)  if (x) {;}             /* tell compiler that variable seems to be used */
#endif





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef int             BOOLEAN;          /* boolean type */
typedef void            VOID;             /* void type */
typedef signed char     SBYTE;            /* signed 8 bit integer */
typedef unsigned char   UBYTE;            /* unsigned 8 bit integer */
typedef signed int      SWORD;            /* signed 16 bit integer */
typedef unsigned int    UWORD;            /* unsigned 16 bit integer */
typedef signed long     SLONG;            /* signed 32 bit integer */
typedef unsigned long   ULONG;            /* unsigned 32 bit integer */





/*******************************************************************************
*
*     COMPILER MACRO DEFINITIONS
*
******************************************|************************************/

#ifndef __GNUC__
#  define __attribute__(x)
#endif





/*******************************************************************************
*
*     OS MACRO DEFINITIONS
*
******************************************|************************************/

#ifdef __MSDOS__
#endif

#ifdef __WIN32__
#endif

#ifdef __TOS__
#endif

#ifdef __LINUX__
#endif

#ifdef __SUNOS__
#endif

#ifdef __NEXTSTEP__
#endif

#ifdef __HPUX_ISO__
#endif

#ifdef __HPUX_ROMAN8__
#endif

#ifdef __AMIGA__
#endif

#ifdef __SINIX__
#endif

#ifdef __BEOS__
#endif

#ifdef __MACOS__
#define __AddLFToNL__ 0                   /* solange es keinen HCP auf dem Mac gibt notwendig */
#endif

#ifdef __MACOSX__
#endif

#endif   /* PORTAB_H */


/* +++ EOF +++ */

