/*	############################################################
	# @(#) udomem.h
	# @(#)
	# @(#) Copyright (c) 2003 by Volker Janzen
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
	############################################################	*/
#ifndef UDO_MEMORY
#define UDO_MEMORY
/*
 * Defines the check codes..
 */
#define UM_LONG_CHECK 0x55446f00L
#define UM_END_STRING "You've got a buffer overflow!"
/* define or undef this symbol, to get or don't get call-messages */
#undef UM_DEBUG_SHOW_CALLS
/* define or undefine this symbol, to get or don't get a stat of malloc/free calls */
#define UM_DEBUG_SHOW_STATS
/* define or undef to get more debug messages */
#define UM_DEBUG_SHOW_MSGS
/* define or undef to say um_free to print the block start and end on an
 * "memory block end check broken" error
 */
#define UM_DEBUG_SHOW_BUFFER_ON_FREE_ERROR
/*
 * For gcc the um_free and um_realloc methods use %ld instead of %d in some printf
 * statements, to get rid of some compiler warnings. This tests if Linux is used,
 * so the Symbol UM_PRINTF_USE_LD is set to switch this behavior on, otherwise the
 * symbol is deleted
 * Note: at the moment I don't know for which compiler this will be need, so its
 * always undef
 */
#undef	UM_PRINTF_USE_LD
#ifdef	__TOS__
#define	UM_PRINTF_USE_LD
#endif
#ifdef	__LINUX__
#define	UM_PRINTF_USE_LD
#endif
/*
 * Declarations for vars that keep memory management information
 */
extern long um_malloc_count;	/* This counts the number of um_malloc calls */
extern long um_free_count;	/* Counts the um_free calls */
extern int memory_error;	/* This indicates a broken memory management */
extern char endstring[];	/* This is the const string, that holds the ending string of memory blocks */
extern size_t endstring_len; /* For better performance this var saves the string length of endstring */
/*
 * Structure definitions
 */
typedef struct _memory_list
{
	long check;
	void *block;
	char *endmark;
	struct _memory_list *next;
} MEMLIST;
/*
 * This is the UDO memory interface. Use it instead of malloc or mfree!
 */
GLOBAL void init_um(void);
GLOBAL void exit_um(void);
GLOBAL void *um_malloc(size_t size);
GLOBAL void *um_realloc(void *block, size_t size);
GLOBAL void um_free(void *memblock);
#endif
