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

/*
 * Defines the check codes..
 */
#define UM_CHECK_HEAD_START     "UDo\0"
#define UM_CHECK_HEAD_START_LEN 4
#define UM_CHECK_FOOTER_STR     "You've a buffer overflow"
#define UM_CHECK_FOOTER_STR_LEN 26
/*
 * Declarations for vars that keep memory management information
 */
extern int um_malloc_count;
extern int um_free_count;
/*
 * This is the UDO memory interface. Use it instead of malloc or mfree!
 */
GLOBAL void init_um();
GLOBAL void exit_um();
GLOBAL void *um_malloc(size_t size);
GLOBAL void *um_realloc(void *block, size_t size);
GLOBAL void um_free(void *memblock);

