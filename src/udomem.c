/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : udomem.c
*  Symbol prefix: udo
*
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
*  Description  : Memory Debug Layer
*                 Written by tho
*
*-------------------------------------------------------------------------------
*
*  Author       : Thorsten Otto (tho)
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : vj, fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2013:
*   tho  Oct 28: complete rewrite
*  2010:
*    fd  Jan 23: - converted all German umlauts in comments into plain ASCII
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDES
*
******************************************|************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "import.h"
#include "udoport.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "udo_type.h"
#include "msg.h"
#include "udointl.h"

#include "export.h"
#include "udomem.h"

#ifndef printnull
#  define printnull(p) ((p) ? (p) : "(null)")
#endif

/*******************************************************************************
*
*     UNINITIALIZED GLOBALS
*
******************************************|************************************/

void (*mem_print_alloc_errors)(size_t size);

/*
 * only for debug,
 * since it will slow down UDO dramatically
 */
static int got_errors;
#if DEBUG_ALLOC
static long memUse;
static size_t memUseSize;
static size_t startMemCount;
static size_t startMemSize;
static int mem_test_ignored;
#if DEBUG_ALLOC >= 3
static size_t memMaxUse;
static size_t memMaxUseSize;
static size_t memMaxUseBlock;
static size_t memReallocs;
#endif
#if DEBUG_ALLOC >= 4
static FILE *trc_file;
#define TRC_FILENAME "dbgalloc.trc"
#endif
#endif

#define MEM_MAGIC_SIZE 4

typedef struct _mem_control
{
	size_t size;
#if DEBUG_ALLOC >= 2
	const char *who;
	long line;
	struct _mem_control *next;
#endif
	long magic;
	unsigned char checker[MEM_MAGIC_SIZE];
} MEM_CONTROL;

#define MEM_MAGIC_START_INTERN 8154711L

/*
 * bytevalue put in memory just before and beyond the
 * allocated block
 */
#define MEM_MAGIC_END			0xaa
/*
 * bytevalue put in newly allocate blocks
 */
#define MEM_MAGIC_NEW_ALLOCATED 0xbb
/*
 * bytevalue put in blocks that are going to be freed
 */
#define MEM_MAGIC_FREED         0x99

#ifndef ALLOC_ALIGN_SIZE
#  define ALLOC_ALIGN_SIZE (sizeof(double) > 8 ? 16 : 8)
#endif

#define SIZEOF_MEM_CONTROL (((sizeof(MEM_CONTROL) + ALLOC_ALIGN_SIZE - 1) / ALLOC_ALIGN_SIZE) * ALLOC_ALIGN_SIZE)

#define EXTRA_MEM (SIZEOF_MEM_CONTROL + sizeof(unsigned char) * MEM_MAGIC_SIZE)


static void oom(size_t size)
{
	if (mem_print_alloc_errors)
	{
		mem_print_alloc_errors(size);
	}
}


/* ---------------------------------------------------------------------- */

char *um_strdup_vprintf(const char *format, va_list args)
{
	char *res;
	size_t len;
	size_t initsize;
	
/* Pure-C lacks vsnprintf() */
#if defined(__PUREC__) && defined(_PUREC_SOURCE)
	void (*save_print_alloc_errors)(size_t size) = mem_print_alloc_errors;
	mem_print_alloc_errors = 0;
	initsize = 16384;
	res = malloc(initsize * sizeof(char));
	while (res == NULL && initsize > 128)
	{
		initsize >>= 1;
		res = malloc(initsize * sizeof(char));
	}
	mem_print_alloc_errors = save_print_alloc_errors;
	if (res == NULL)
	{
		oom(initsize);
		return NULL;
	}

	len = vsprintf(res, format, args);
	if (len >= initsize)
	{
		abort();
	}
	res = realloc(res, (len + 1) * sizeof(char));
#else
	va_list args2;

	initsize = 1024;
	res = (char *)malloc(initsize * sizeof(char));
	if (res == NULL)
	{
		return NULL;
	}
	G_VA_COPY(args2, args);

	len = vsnprintf(res, initsize, format, args);
	if (len >= initsize)
	{
		initsize = len + 1;
		res = (char *)realloc(res, initsize * sizeof(char));
		if (res != NULL)
		{
			len = vsnprintf(res, initsize, format, args2);
			if (len >= initsize)
			{
				abort();
			}
		}
	}
	va_end(args2);
#endif
	
	return res;
}

/* ---------------------------------------------------------------------- */

char *um_strdup_printf(const char *format, ...)
{
   va_list args;
   char *res;
   
   va_start(args, format);
   res = um_strdup_vprintf(format, args);
   va_end(args);
   return res;
}

/* ********************************************************************** */
/* ---------------------------------------------------------------------- */
/* ********************************************************************** */

#undef malloc
#undef calloc
#undef strdup
#undef realloc
#undef free

#if DEBUG_ALLOC >= 2
static MEM_CONTROL *alloc_list;

static int delete_alloc_list(MEM_CONTROL *block, const char *who, long line)
{
	MEM_CONTROL *search = alloc_list;

	if (block == search)
	{
		alloc_list = search->next;
	} else
	{
		while (search && search->next != block)
			search = search->next;
		if (search && search->next == block)
		{
			search->next = search->next->next;
		} else
		{
			fprintf(stderr, "%s:%ld: Memory Block not found: %p %-5.5s\n", printnull(who), line, (char *)block + SIZEOF_MEM_CONTROL, (const char *)block + SIZEOF_MEM_CONTROL);
#if DEBUG_ALLOC >= 4
			if (trc_file != NULL)
			{
				int i, maxl = 30;
				const unsigned char *p = (const unsigned char *)block + SIZEOF_MEM_CONTROL;
				fprintf(trc_file, "%s:%ld: Memory Block not found: %p ", printnull(who), line, (const char *)block + SIZEOF_MEM_CONTROL);
				for (i = 0; i < maxl && *p; i++)
				{
					if (*p >= 0x20 && *p < 0x7f)
						putc(*p, trc_file);
					else
						fprintf(trc_file, "\\x%02x", *p);
					p++;
				}
				fprintf(trc_file, "\n");
				fflush(trc_file);
			}
#endif
			got_errors = TRUE;
			return FALSE;
		}
	}
	return TRUE;
}

/* ---------------------------------------------------------------------- */

static int in_alloc_list(MEM_CONTROL *block)
{
	MEM_CONTROL *search = alloc_list;

	while (search)
	{
		if (search == block)
			return TRUE;
		search = search->next;
	}
	got_errors = TRUE;
	return FALSE;
}

#endif							/* DEBUG_ALLOC >= 2 */

/* ---------------------------------------------------------------------- */

#if DEBUG_ALLOC

static void *mem_debug_getit(size_t size, int zero, const char *who, long line)
{
	MEM_CONTROL *cntl;
	
	if (size == 0)
	{
		fprintf(stderr, "malloc(0) ? (%s:%ld)\n", printnull(who), line);
		return NULL;
	}

	cntl = mem_get(size + EXTRA_MEM);

	if (cntl == NULL)
	{
		return NULL;
	}
	
	cntl->magic = MEM_MAGIC_START_INTERN;
	
	cntl->size = size;
	{
		size_t i;
		
		for (i = 0; i < SIZEOF_MEM_CONTROL - offsetof(MEM_CONTROL, checker); i++)
			cntl->checker[i] = MEM_MAGIC_END;
	}
#if DEBUG_ALLOC >= 2
	cntl->next = alloc_list;
	alloc_list = cntl;
	cntl->who = who;
	cntl->line = line;
#endif
	cntl = (MEM_CONTROL *)((char *)cntl + SIZEOF_MEM_CONTROL);

	if (zero)
		memset(cntl, 0, size);
	else
		memset(cntl, MEM_MAGIC_NEW_ALLOCATED, size);

	{
		unsigned char *test;
		size_t i;
		
		test = (unsigned char *) cntl + size;
		for (i = 0; i < MEM_MAGIC_SIZE; i++)
			test[i] = MEM_MAGIC_END;
	}
	memUseSize += size;
	memUse++;
#if DEBUG_ALLOC >= 3
	if (memUse > memMaxUse)
		memMaxUse = memUse;
	if (memUseSize > memMaxUseSize)
		memMaxUseSize = memUseSize;
	if (size > memMaxUseBlock)
		memMaxUseBlock = size;
#endif


#if DEBUG_ALLOC >= 4
	if (trc_file != NULL)
	{
		fprintf(trc_file, "Trace: allocated %lu bytes memory at %p in %s:%ld\n", (unsigned long)size, cntl, printnull(who), line);
		fflush(trc_file);
	}
#endif
	return (void *) cntl;
}

/* ********************************************************************** */
/* ---------------------------------------------------------------------- */
/* ********************************************************************** */

void *mem_debug_realloc(void *ptr, size_t size, const char *who, long line)
{
	MEM_CONTROL *cntl;
	MEM_CONTROL *newcntl;
	int defect;
	size_t oldsize;
	
	if (size == 0)
	{
#if DEBUG_ALLOC >= 4
		if (trc_file != NULL)
		{
			fprintf(trc_file, "Trace: realloc: free %p\n", ptr);
			fflush(trc_file);
		}
#endif
		mem_debug_free(ptr, who, line);
		return NULL;
	}
	if (ptr == NULL)
	{
#if DEBUG_ALLOC >= 4
		if (trc_file != NULL)
		{
			fprintf(trc_file, "Trace: realloc: ptr is NULL\n");
			fflush(trc_file);
		}
#endif
		return mem_debug_getit(size, FALSE, who, line);
	}
	
	cntl = (MEM_CONTROL *) ((char *) (ptr) - SIZEOF_MEM_CONTROL);

#if DEBUG_ALLOC >= 2
	if (!in_alloc_list(cntl))
	{
		fprintf(stderr, "%s:%ld: Memory Block not found: %p\n", printnull(who), line, ptr);
#if DEBUG_ALLOC >= 4
		if (trc_file != NULL)
		{
			fprintf(trc_file, "%s:%ld: Memory Block not found: %p\n", printnull(who), line, ptr);
			fflush(trc_file);
		}
#endif
		return NULL;
	}
#endif
	
	defect = FALSE;
	if (cntl->magic != MEM_MAGIC_START_INTERN)
		defect = TRUE;

	{
		size_t i;
		unsigned char *test;
	
		test = cntl->checker;
		for (i = 0; i < SIZEOF_MEM_CONTROL - offsetof(MEM_CONTROL, checker); i++)
			if (test[i] != MEM_MAGIC_END)
				defect = TRUE;
	}

	if (defect)
	{
		got_errors = TRUE;
#if DEBUG_ALLOC >= 2
		fprintf(stderr, "%s:%ld: MemStart defekt: %p(%lu)\n", printnull(who), line, ptr, (unsigned long)cntl->size);
#else
		fprintf(stderr, "MemStart defekt: %p\n", ptr);
#endif
		return NULL;
	}

	{
		size_t i;
		unsigned char *test;
	
		defect = FALSE;
		test = ((unsigned char *) (cntl)) + cntl->size + SIZEOF_MEM_CONTROL;
		for (i = 0; i < MEM_MAGIC_SIZE; i++)
			if (test[i] != MEM_MAGIC_END)
				defect = TRUE;
		if (defect)
		{
			got_errors = TRUE;
#if DEBUG_ALLOC >= 2
			fprintf(stderr, "%s:%ld: MemEnd defekt: %p(%lu)\n", printnull(who), line, ptr, (unsigned long)cntl->size);
#else
			fprintf(stderr, "MemEnd defekt: %p\n", ptr);
#endif
			return NULL;
		}
	}

#if DEBUG_ALLOC >= 3
	memReallocs++;
#endif

	oldsize = cntl->size;
	
#if DEBUG_ALLOC >= 2
	if (!delete_alloc_list(cntl, who, line))
		return NULL;
#endif
	newcntl = mem_realloc(cntl, size + EXTRA_MEM);
	if (newcntl == NULL)
	{
		return NULL;
	}
	newcntl->magic = MEM_MAGIC_START_INTERN;
	
	newcntl->size = size;
	{
		size_t i;
		
		for (i = 0; i < SIZEOF_MEM_CONTROL - offsetof(MEM_CONTROL, checker); i++)
			newcntl->checker[i] = MEM_MAGIC_END;
	}
#if DEBUG_ALLOC >= 2
	newcntl->next = alloc_list;
	alloc_list = newcntl;
	newcntl->who = who;
	newcntl->line = line;
#endif
	
	newcntl = (MEM_CONTROL *)((char *)newcntl + SIZEOF_MEM_CONTROL);

	if (size > oldsize)
		memset((char *)newcntl + oldsize, MEM_MAGIC_NEW_ALLOCATED, size - oldsize);

	{
		unsigned char *test;
		size_t i;
		
		test = (unsigned char *) newcntl + size;
		for (i = 0; i < MEM_MAGIC_SIZE; i++)
			test[i] = MEM_MAGIC_END;
	}
	
	if (size > oldsize)
		memUseSize += size - oldsize;
	else
		memUseSize -= oldsize - size;
#if DEBUG_ALLOC >= 3
	if (memUseSize > memMaxUseSize)
		memMaxUseSize = memUseSize;
	if (size > memMaxUseBlock)
		memMaxUseBlock = size;
#endif
#if DEBUG_ALLOC >= 4
	if (trc_file != NULL)
	{
		fprintf(trc_file, "Trace: realloc (%p,%lu) to (%p,%lu) in %s:%ld\n", ((const char *)cntl + SIZEOF_MEM_CONTROL), oldsize, newcntl, size, printnull(who), line);
		fflush(trc_file);
	}
#endif
	
	return (void *) newcntl;
}

/* ---------------------------------------------------------------------- */

void mem_debug_free(void *ptr, const char *who, long line)
{
	MEM_CONTROL *memCntl;
	int defect;
	
	if (ptr == NULL)
	{
		return;
	}

	memCntl = (MEM_CONTROL *)((char *)ptr - SIZEOF_MEM_CONTROL);

#if DEBUG_ALLOC >= 2
	if (!delete_alloc_list(memCntl, who, line))
		return;
#endif
	defect = FALSE;
	if (memCntl->magic != MEM_MAGIC_START_INTERN)
		defect = TRUE;

	{
		size_t i;
		
		for (i = 0; i < SIZEOF_MEM_CONTROL - offsetof(MEM_CONTROL, checker); i++)
			if (memCntl->checker[i] != MEM_MAGIC_END)
				defect = TRUE;
	}

	if (defect)
	{
		got_errors = TRUE;
#if DEBUG_ALLOC >= 2
		fprintf(stderr, "%s:%ld: MemStart defekt: %p(%lu)\n", printnull(memCntl->who), memCntl->line, ptr, (unsigned long)memCntl->size);
#else
		fprintf(stderr, "%s:%ld: MemStart defekt: %p\n", ptr, printnull(who), line);
#endif
		return;
	}

#if DEBUG_ALLOC >= 2
	{
		unsigned char *test = ((unsigned char *)memCntl) + memCntl->size + SIZEOF_MEM_CONTROL;
		size_t i;
		
		defect = FALSE;
		for (i = 0; i < MEM_MAGIC_SIZE; i++)
			if (test[i] != MEM_MAGIC_END)
				defect = TRUE;
		if (defect)
		{
			got_errors = TRUE;
			/* assumes MAGIC_SIZE >= 4 */
			fprintf(stderr, "%s:%ld: MemEnd defekt %p(%lu): %02x %02x %02x %02x\n", printnull(memCntl->who), memCntl->line, ptr,
				(unsigned long)memCntl->size,
				test[0], test[1], test[2], test[3]);
		}
	}
#endif

#if DEBUG_ALLOC >= 4
	if (trc_file != NULL)
	{
		fprintf(trc_file, "Trace: free %p(%ld) %s:%ld\n", ptr, memCntl->size, printnull(who), line);
		fflush(trc_file);
	}
#endif

	memUse--;
	memUseSize -= memCntl->size;
	memset(memCntl, MEM_MAGIC_FREED, memCntl->size + EXTRA_MEM);

	free(memCntl);
}

/* ---------------------------------------------------------------------- */

void *mem_debug_get(size_t size, const char *who, long line)
{
	return mem_debug_getit(size, FALSE, who, line);
}

/* ---------------------------------------------------------------------- */

void *mem_debug_0get(size_t size, const char *who, long line)
{
	return mem_debug_getit(size, TRUE, who, line);
}

/* ---------------------------------------------------------------------- */

char *mem_debug_str_dup(const char *str, const char *from, long line)
{
	char *new;

	if (str == NULL)
		return NULL;
	new = mem_debug_getit(strlen(str) + 1, FALSE, from, line);
	if (new != NULL)
		strcpy(new, str);
	return new;
}

#endif /* DEBUG_ALLOC */

/* ********************************************************************** */
/* ---------------------------------------------------------------------- */
/* ********************************************************************** */

void *mem_get(size_t size)
{
	void *ptr;
	
	ptr = malloc(size);
	if (ptr == NULL)
		oom(size);
	return ptr;
}

/* ---------------------------------------------------------------------- */

void *mem_0get(size_t size)
{
	void *ptr;
	
	ptr = calloc(1, size);
	if (ptr == NULL)
		oom(size);
	return ptr;
}

/* ---------------------------------------------------------------------- */

char *mem_str_dup(const char *str)
{
	char *p;
	size_t size;
	
	if (str == NULL)
		return NULL;
	size = strlen(str) + 1;
	if ((p = (char *)mem_get(size)) != NULL)
		return strcpy(p, str);
	return NULL;
}

/* ---------------------------------------------------------------------- */

void *mem_realloc(void *ptr, size_t newsize)
{
	if (newsize == 0)
	{
		mem_free(ptr);
		return NULL;
	}
	if (ptr == NULL)
		return mem_get(newsize);
	ptr = realloc(ptr, newsize);
	if (ptr == NULL)
	{
		oom(newsize);
	}
	return ptr;
}

/* ---------------------------------------------------------------------- */

void mem_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

/*******************************************************************************
*
*  mem_test_start():
*     sets up the memory layer
*
*  Notes:
*     Initialize Counters, anchor for memory-usage list, memory error indicator
*     and length of the ending string
*
*  Return:
*     -
*
******************************************|************************************/

#if defined(__PUREC__) && defined(_PUREC_SOURCE)
extern void _crtinit(void);
extern void _crtexit(void);
#endif

GLOBAL void mem_test_start(void)
{
#ifdef __TOS__
#if defined(__PUREC__) && defined(_PUREC_SOURCE)
	_crtinit();
#endif
	_mallocChunkSize(0x10000UL);
#endif
	got_errors = FALSE;
#if DEBUG_ALLOC
	startMemCount = memUse;
	startMemSize = memUseSize;
#endif
#if DEBUG_ALLOC >= 3
	memMaxUse = 0;
	memMaxUseSize = 0;
	memMaxUseBlock = 0;
	memReallocs = 0;
#endif
#if DEBUG_ALLOC >= 4
	trc_file = fopen(TRC_FILENAME, "w");
#endif
}




/*******************************************************************************
*
*  mem_test_end():
*     frees all memory allocated by mallocs and makes consistency
*     checks on the memory blocks.
*
*  Return:
*     -
*
******************************************|************************************/
 
int mem_test_end(void)
{
#if DEBUG_ALLOC
	if ((memUse != startMemCount || memUseSize != startMemSize) && !mem_test_ignored)
	{
		fprintf(stderr, "MemTest A:%ld S:%ld\n", (long)(memUse - startMemCount), (long)(memUseSize - startMemSize));
		got_errors = TRUE;
#if DEBUG_ALLOC >= 4
		if (trc_file != NULL)
		{
			MEM_CONTROL *list;
			
			fprintf(trc_file, "MemTest A:%ld S:%ld\n", (long)(memUse - startMemCount), (long)(memUseSize - startMemSize));
			for (list = alloc_list; list != NULL; list = list->next)
			{
				fprintf(trc_file, "-> %s:%ld: %p(%lu)\n", printnull(list->who), list->line, (const char *)list + SIZEOF_MEM_CONTROL, (unsigned long)list->size);
			}
		}
#endif
#if DEBUG_ALLOC >= 2
		while (alloc_list != NULL)
		{
			fprintf(stderr, "-> %s:%ld: %p(%lu)\n", printnull(alloc_list->who), alloc_list->line, (const char *)alloc_list + SIZEOF_MEM_CONTROL, (unsigned long)alloc_list->size);
			alloc_list = alloc_list->next;
		}
#endif
	}
#endif
#if DEBUG_ALLOC >= 3
	fprintf(stderr, "Memory usage: %lu blocks, %lu bytes, largest %lu, reallocs %lu\n",
		(unsigned long)memMaxUse,
		(unsigned long)memMaxUseSize,
		(unsigned long)memMaxUseBlock,
		(unsigned long)memReallocs);
#endif
#if defined(__PUREC__) && defined(_PUREC_SOURCE)
	_crtexit();
#endif
#if DEBUG_ALLOC >= 4
	if (trc_file != NULL)
	{
		fprintf(trc_file, "Memory usage: %lu blocks, %lu bytes, largest %lu, reallocs %lu\n",
			(unsigned long)memMaxUse,
			(unsigned long)memMaxUseSize,
			(unsigned long)memMaxUseBlock,
			(unsigned long)memReallocs);
		fclose(trc_file);
		trc_file = NULL;
	}
#endif
	return !got_errors;
}
