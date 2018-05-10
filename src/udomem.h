/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : udomem.h
*  Symbol prefix: um_
*
*  Description  : ???
*
*  Copyright    : Copyright (c) 2003 by Volker Janzen
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
*  Author       : Volker Janzen
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
*    fd  Feb 22: header adjusted
*
******************************************|************************************/

#ifndef UDO_MEMORY
#define UDO_MEMORY

#include <stdarg.h>
#include "udoport.h"
#include "debug.h"

/*
 * values for DEBUG_ALLOC:
 * 0 - disable
 * 1 - track number of blocks and total allocated size
 * 2 - track every block and where it is allocated
 * 3 - same as 2 and track maximum allocated size & number
 * 4 - same as 3 and write log file to "dbgalloc.trc"
 */
#ifndef DEBUG_ALLOC
#  define DEBUG_ALLOC 0
#endif

void *mem_get(size_t size);
void *mem_realloc(void *block, size_t newsize);
void mem_free(void *p);
void *mem_0get(size_t size);
char *mem_str_dup(const char *str);
char *mem_str_ndup(const char *str, size_t len);

#undef strdup
#undef strndup

#if DEBUG_ALLOC

void *mem_debug_get(size_t size, const char *from, long line);
void mem_debug_free(void *block, const char *from, long line);
void *mem_debug_0get(size_t size, const char *from, long line);
char *mem_debug_str_dup(const char *str, const char *from, long line);
char *mem_debug_str_ndup(const char *str, size_t len, const char *from, long line);
void *mem_debug_realloc(void *block, size_t newsize, const char *from, long line);

#define malloc(size) mem_debug_get(size, __FILE__, __LINE__)
#define calloc(nitems, size) mem_debug_0get((size_t)(nitems) * (size_t)(size), __FILE__, __LINE__)
#define strdup(str) mem_debug_str_dup(str, __FILE__, __LINE__)
#define strndup(str, len) mem_debug_str_ndup(str, len, __FILE__, __LINE__)
#define free(block) mem_debug_free(block, __FILE__, __LINE__)
#define realloc(block, newsize) mem_debug_realloc(block, newsize, __FILE__, __LINE__)

#else

#define malloc(size) mem_get(size)
#define calloc(nitems, size) mem_0get((size_t)(nitems) * (size_t)(size))
#define strdup(str) mem_str_dup(str)
#define strndup(str, len) mem_str_ndup(str, len)
#define realloc(block, newsize) mem_realloc(block, newsize)
#define free(block) mem_free(block)

#endif /* DEBUG_ALLOC */

extern void (*mem_print_alloc_errors)(size_t size);

void mem_test_start(void);
int mem_test_end(void);

char *um_strdup_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));
char *um_strdup_vprintf(const char *format, va_list args);

#endif /* UDO_MEMORY */
