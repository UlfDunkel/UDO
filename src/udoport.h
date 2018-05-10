/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : udoport.h
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
*    fd  Feb 19: new: NIL
*    fd  Feb 22: new: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG
*  2011:
*    fd  Jan 31: new: XPOINT
*  2013:
*   tho  Dec 07: renamed from portab.h, sometimes concflicts
*                with system header of same name
*  2014:
*   tho  Aug 08: removed unused definitions
*                renamed remaining typedefs to _BOOL, _UBYTE, _UWORD and _ULONG because
*                of conflicts with windows headers
*                removed XPOINT typedef
*                removed NIL define
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

#define EOS        '\0'

#define LOCAL      static

#ifndef UNUSED
#define UNUSED(x)  if (x) {;}             /* tell compiler that variable seems to be used */
#endif

#ifdef __GNUC__
#define __build_bug(e) (__extension__ sizeof(struct { int:-!!(e); }))
/* &a[0] degrades to a pointer: a different type from an array */
#define __must_be_array(a) __build_bug(__builtin_types_compatible_p(typeof(a), typeof(&a[0])))
#else
#define __build_bug(e)
#define __must_be_array(a) 0
#endif

#define ArraySize(a) (sizeof(a) / sizeof((a)[0]) + __must_be_array(a))





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef int             _BOOL;            /* boolean type */
typedef unsigned char   _UBYTE;           /* unsigned 8 bit integer */
typedef unsigned int    _UWORD;           /* unsigned 16 bit integer */
typedef unsigned long   _ULONG;           /* unsigned 32 bit integer */





/*******************************************************************************
*
*     COMPILER MACRO DEFINITIONS
*
******************************************|************************************/

#ifndef __GNUC__
#  define __attribute__(x)
#endif

#ifndef NO_CONST
#  ifdef __GNUC__
#	 define NO_CONST(p) __extension__({ union { const void *cs; void *s; } x; x.cs = p; x.s; })
#  else
#	 define NO_CONST(p) ((void *)(p))
#  endif
#endif


#ifdef __GNUC__
#  define NOINLINE __attribute__((noinline))
#else
#  define NOINLINE /**/
#endif



#if (defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(__WIN64__))
#ifndef _WIN32
# define _WIN32 1
#endif
#ifndef __WIN32__
# define __WIN32__ 1
#endif
#if defined(_WIN64) && !defined(__WIN64__)
# define __WIN64__ 1
#endif
#endif


/* Define G_VA_COPY() to do the right thing for copying va_list variables.
 * config.h may have already defined G_VA_COPY as va_copy or __va_copy.
 */
#if !defined (G_VA_COPY)
#  if defined (__GNUC__)
#    define G_VA_COPY(ap1, ap2)	va_copy(ap1, ap2)
#  elif defined (G_VA_COPY_AS_ARRAY)
#    define G_VA_COPY(ap1, ap2)	  memmove ((ap1), (ap2), sizeof (va_list))
#  else /* va_list is a pointer */
#    define G_VA_COPY(ap1, ap2)	  ((ap1) = (ap2))
#  endif /* va_list is a pointer */
#endif /* !G_VA_COPY */

#ifndef __PUREC__
#  define HAVE_ANONYMOUS_STRUCTS
#endif

#ifndef ANONYMOUS_STRUCT_DUMMY
#  if defined(HAVE_ANONYMOUS_STRUCTS)
#    define ANONYMOUS_STRUCT_DUMMY(x)
#  else
#    define ANONYMOUS_STRUCT_DUMMY(x) struct x { int dummy; };
#  endif
#endif


#if defined(__cplusplus) || defined(c_plusplus)
#define EXTERN_C_BEG  extern "C" {
#define EXTERN_C_END  }
#else
#define EXTERN_C_BEG
#define EXTERN_C_END
#endif

/*******************************************************************************
*
*     OS MACRO DEFINITIONS
*
******************************************|************************************/

#endif   /* PORTAB_H */
