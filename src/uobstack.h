/* obstack.h - object stack macros
   Copyright (C) 1988,89,90,91,92,93,94,96,97,98,99 Free Software Foundation, Inc.

   This file is part of the GNU C Library.  Its master source is NOT part of
   the C library, however.  The master source lives in /gd/gnu/lib.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Summary:

All the apparent functions defined here are macros. The idea
is that you would use these pre-tested macros to solve a
very specific set of problems, and they would run fast.
Caution: no side-effects in arguments please!! They may be
evaluated MANY times!!

These macros operate a stack of objects.  Each object starts life
small, and may grow to maturity.  (Consider building a word syllable
by syllable.)  An object can move while it is growing.  Once it has
been "finished" it never changes address again.  So the "top of the
stack" is typically an immature growing object, while the rest of the
stack is of mature, fixed size and fixed address objects.

These routines grab large chunks of memory, using a function you
supply, called `obstack_chunk_alloc'.  On occasion, they free chunks,
by calling `obstack_chunk_free'.  You must define them and declare
them before using any obstack macros.

Each independent stack is represented by a `struct obstack'.
Each of the obstack macros expects a pointer to such a structure
as the first argument.

One motivation for this package is the problem of growing char strings
in symbol tables.  Unless you are "fascist pig with a read-only mind"
--Gosper's immortal quote from HAKMEM item 154, out of context--you
would not like to put any arbitrary upper limit on the length of your
symbols.

In practice this often means you will build many short symbols and a
few long symbols.  At the time you are reading a symbol you don't know
how long it is.  One traditional method is to read a symbol into a
buffer, realloc()ating the buffer every time you try to read a symbol
that is longer than the buffer.  This is beaut, but you still will
want to copy the symbol from the buffer to a more permanent
symbol-table entry say about half the time.

With obstacks, you can work differently.  Use one obstack for all symbol
names.  As you read a symbol, grow the name in the obstack gradually.
When the name is complete, finalize it.  Then, if the symbol exists already,
free the newly read name.

The way we do this is to take a large chunk, allocating memory from
low addresses.  When you want to build a symbol in the chunk you just
add chars above the current "high water mark" in the chunk.  When you
have finished adding chars, because you got to the end of the symbol,
you know how long the chars are, and you can create a new object.
Mostly the chars will not burst over the highest address of the chunk,
because you would typically expect a chunk to be (say) 100 times as
long as an average object.

In case that isn't clear, when we have enough chars to make up
the object, THEY ARE ALREADY CONTIGUOUS IN THE CHUNK (guaranteed)
so we just point to it where it lies.  No moving of chars is
needed and this is the second win: potentially long strings need
never be explicitly shuffled. Once an object is formed, it does not
change its address during its lifetime.

When the chars burst over a chunk boundary, we allocate a larger
chunk, and then copy the partly formed object from the end of the old
chunk to the beginning of the new larger chunk.  We then carry on
accreting characters to the end of the object as we normally would.

A special macro is provided to add a single char at a time to a
growing object.  This allows the use of register variables, which
break the ordinary 'growth' macro.

Summary:
	We allocate large chunks.
	We carve out one object at a time from the current chunk.
	Once carved, an object never moves.
	We are free to append data of any size to the currently
	  growing object.
	Exactly one object is growing in an obstack at any one time.
	You can run one obstack per control block.
	You may have as many control blocks as you dare.
	Because of the way we do it, you can `unwind' an obstack
	  back to a previous state. (You may remove objects much
	  as you would with a stack.)
*/


/* Don't do the contents of this file more than once.  */

#ifndef _UDO_OBSTACK_H
#define _UDO_OBSTACK_H 1

#include "udoport.h"

#ifdef __cplusplus
extern "C" {
#endif

/* We use subtraction of (char *) 0 instead of casting to int
   because on word-addressable machines a simple cast to int
   may ignore the byte-within-word field of the pointer.  */

#ifndef __PTR_TO_INT
# define __PTR_TO_INT(P) ((P) - (char *) 0)
#endif

#ifndef __INT_TO_PTR
# define __INT_TO_PTR(P) ((P) + (char *) 0)
#endif

#ifdef __PUREC__
/* Pure-C miscompiles the macros above and truncates the offset
   (and thus the whole result) to 16 bit */
#undef __INT_TO_PTR
#undef __PTR_TO_INT
#define __PTR_TO_INT(P) ((size_t)(P))
#define __INT_TO_PTR(P) ((char *)(P))
#endif


/* We need the type of the resulting object.  If __PTRDIFF_TYPE__ is
   defined, as with GNU C, use that; that way we don't pollute the
   namespace with <stddef.h>'s symbols.  Otherwise, if <stddef.h> is
   available, include it and use ptrdiff_t.  In traditional C, long is
   the best that we can do.  */

#ifdef __PTRDIFF_TYPE__
# define PTR_INT_TYPE __PTRDIFF_TYPE__
#else
# ifdef HAVE_STDDEF_H
#  include <stddef.h>
#  define PTR_INT_TYPE ptrdiff_t
# else
#  define PTR_INT_TYPE long
# endif
#endif

#include <string.h>
#define _obstack_memcpy(To, From, N) memcpy ((To), (From), (N))

struct _obstack_chunk		/* Lives at front of each chunk. */
{
  char  *limit;			/* 1 past end of this chunk */
  struct _obstack_chunk *prev;	/* address of prior chunk or NULL */
  char	contents[4];		/* objects begin here */
};

struct obstack		/* control current object in current chunk */
{
  long	chunk_size;		/* preferred size to allocate chunks in */
  struct _obstack_chunk *chunk;	/* address of current struct obstack_chunk */
  char	*object_base;		/* address of object we are building */
  char	*next_free;		/* where to add next char to current object */
  char	*chunk_limit;		/* address of char after current chunk */
  PTR_INT_TYPE alignment_mask;		/* Mask of alignment for each object. */
  void *(*chunkfun) (size_t);
  void (*freefun) (void *);
  unsigned maybe_empty_object:1;/* There is a possibility that the current
				   chunk contains a zero-length object.  This
				   prevents freeing the chunk if we allocate
				   a bigger chunk to replace it. */
  unsigned alloc_failed:1;	/* No longer used, as we now call the failed
				   handler on error, but retained for binary
				   compatibility.  */
};

/* Declare the external functions we use; they are in obstack.c.  */

extern _BOOL _udo_obstack_newchunk (struct obstack *, PTR_INT_TYPE);
extern _BOOL _udo_obstack_begin (struct obstack *h, PTR_INT_TYPE size, PTR_INT_TYPE alignment,
			    void * (*chunkfun) (size_t), void (*freefun) (void *));
extern PTR_INT_TYPE udo_obstack_memory_used (struct obstack *);

/* Do the function-declarations after the structs
   but before defining the macros.  */

void udo_obstack_init (struct obstack *obstack);

void * udo_obstack_alloc (struct obstack *obstack, PTR_INT_TYPE size);

void * udo_obstack_copy (struct obstack *obstack, void *address, PTR_INT_TYPE size);
void * udo_obstack_copy0 (struct obstack *obstack, void *address, PTR_INT_TYPE size);

_BOOL udo_obstack_free (struct obstack *obstack, void *block);

_BOOL udo_obstack_blank (struct obstack *obstack, PTR_INT_TYPE size);

_BOOL udo_obstack_grow(struct obstack *obstack, void * data, PTR_INT_TYPE length);
_BOOL udo_obstack_grow0(struct obstack *obstack, void * data, PTR_INT_TYPE length);

_BOOL udo_obstack_1grow (struct obstack *obstack, int data_char);
_BOOL udo_obstack_ptr_grow (struct obstack *obstack, void *data);
_BOOL udo_obstack_int_grow (struct obstack *obstack, int data);
_BOOL udo_obstack_long_grow(struct obstack *obstack, long data);

void * udo_obstack_finish (struct obstack *obstack);

PTR_INT_TYPE udo_obstack_object_size (struct obstack *obstack);
_BOOL udo_obstack_empty_p (struct obstack *obstack);

PTR_INT_TYPE udo_obstack_room (struct obstack *obstack);
_BOOL udo_obstack_make_room (struct obstack *obstack, PTR_INT_TYPE size);
void udo_obstack_1grow_fast (struct obstack *obstack, int data_char);
void udo_obstack_ptr_grow_fast (struct obstack *obstack, void *data);
void udo_obstack_int_grow_fast (struct obstack *obstack, int data);
void udo_obstack_blank_fast (struct obstack *obstack, PTR_INT_TYPE size);

void * udo_obstack_base (struct obstack *obstack);
void * udo_obstack_next_free (struct obstack *obstack);
PTR_INT_TYPE udo_obstack_alignment_mask (struct obstack *obstack);
long udo_obstack_chunk_size (struct obstack *obstack);




/* To prevent prototype warnings provide complete argument list in
   standard C version.  */
# define udo_obstack_init(h) _udo_obstack_begin ((h), 0, 0, udo_obstack_chunk_alloc, udo_obstack_chunk_free)

# define udo_obstack_begin(h, size) _udo_obstack_begin ((h), (size), 0, udo_obstack_chunk_alloc, udo_obstack_chunk_free)

# define udo_obstack_ptr_grow_fast(h,aptr) (*((char **) (h)->next_free)++ = (char *) aptr)
# define udo_obstack_int_grow_fast(h,aint) (*((int *) (h)->next_free)++ = (int) aint)

#ifdef __cplusplus
}	/* C++ */
#endif

#endif /* _UDO_OBSTACK_H */
