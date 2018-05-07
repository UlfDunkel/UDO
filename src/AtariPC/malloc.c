/*
 * malloc, free, realloc: dynamic memory allocation
 *
 * Substitute for Pure-C implementation,
 * which keeps getting out of memory
 * with lots of malloc()/free calls.
 *
 * Taken from MiNTlib 0.60.0
 */

#include <compiler.h>

#if defined(__PUREC__) && defined(_PUREC_SOURCE) /* rest of file */

#include <stddef.h>	/* for size_t */
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <osbind.h>
#include <errno.h>
#include "udomem.h" /* for DEBUG_ALLOC only */


#undef malloc
#undef calloc
#undef strdup
#undef realloc
#undef free


#define MINFREE      (8L * 1024L)            /* free at least this much mem on top */
#define MINKEEP (64L * 1024L)                /* keep at least this much mem on stack */

static void *_heapbase;
static short _split_mem;
extern long _stksize;
extern void *_StkLim;
extern char **environ;


#if DEBUG_ALLOC >= 3
static unsigned long cur_mallocs;
static unsigned long max_mallocs;
static unsigned long total_mallocs;
static unsigned long total_frees;
#endif


/* definitions needed in malloc.c and realloc.c */

struct mem_chunk 
{
	long valid;
#define VAL_FREE  (long)0xf4ee0abcL
#define VAL_ALLOC (long)0xa11c0abcL
#define VAL_BORDER (long)0xb04d0abcL

	struct mem_chunk *next;
	unsigned long size;
	/* unsigned long alloc_size; */
};
#define ALLOC_SIZE(ch) (*(unsigned long *)((char *)(ch) + sizeof(*(ch))))
#define BORDER_EXTRA ((sizeof(struct mem_chunk) + sizeof(long) + 7) & ~7)

/* CAUTION: use _mallocChunkSize() to tailor to your environment,
 *          do not make the default too large, as the compiler
 *          gets screwed on a 1M machine otherwise (stack/heap clash)
 */
/* minimum chunk to ask OS for */
static size_t MINHUNK =	8192L;	/* default */
static size_t MAXHUNK = 32 * 1024L; /* max. default */

/* tune chunk size */
void _mallocChunkSize(size_t siz)
{
	MAXHUNK = MINHUNK = siz;
}

/* flag to control zero'ing of malloc'ed chunks */
static int ZeroMallocs = 0;

/* linked list of free blocks struct defined in lib.h */
static struct mem_chunk _mchunk_free_list = { VAL_FREE, NULL, 0L };


#define DEF_PAGESIZE 8192				/* default page size for TOS */

int getpagesize(void)
{
	return DEF_PAGESIZE;
}


void *malloc(size_t n)
{
	struct mem_chunk *p, *q;
	unsigned long sz;

	/* add a mem_chunk to required size and round up */
	n = (n + sizeof(struct mem_chunk) + 7) & ~7;

	/* look for first block big enough in free list */
	p = &_mchunk_free_list;
	q = _mchunk_free_list.next;
	while (q && (q->size < n || q->valid == VAL_BORDER))
	{
		p = q;
		q = q->next;
	}

	/* if not enough memory, get more from the system */
	if (q == NULL) 
	{
		if (((!_split_mem) && (_heapbase != NULL))
		    || n + BORDER_EXTRA > MINHUNK)
		{
			sz = n;
			if (_heapbase == NULL)
				sz += BORDER_EXTRA;
		}
		else
		{
			sz = MINHUNK;
			if (MINHUNK < MAXHUNK)
				MINHUNK *= 2;
		}
		if (_split_mem || _heapbase == NULL)
		{
			int page_size;
			
			page_size = getpagesize ();
			
			sz = (sz + page_size - 1) & -page_size;
		}

		q = (struct mem_chunk * ) sbrk(sz);
		if (q == (void *)-1) /* can't alloc any more? */
			return NULL;

		/* Note: q may be below the highest allocated chunk */
		p = &_mchunk_free_list;
		while (p->next && q > p->next)
			p = p->next;

		if (_heapbase == NULL)
		{
			q->size = BORDER_EXTRA;
			sz -= BORDER_EXTRA;
			q->valid = VAL_BORDER;
			ALLOC_SIZE (q) = sz;
			q->next = (struct mem_chunk *) ((char *) q + BORDER_EXTRA);
			q->next->next = p->next;
			p = p->next = q;
			q = q->next;
		}
		else
		{
			q->next = p->next;
			p->next = q;
		}

		q->size = sz;
		q->valid = VAL_FREE;
	}

	if (q->size > n + sizeof(struct mem_chunk))
	{
		/* split, leave part of free list */
		q->size -= n;
		q = (struct mem_chunk * )(((char *) q) + q->size);
		q->size = n;
		q->valid = VAL_ALLOC;
	}
	else
	{
		/* just unlink it */
		p->next = q->next;
		q->valid = VAL_ALLOC;
	}

	q->next = NULL;	
	q++; /* hand back ptr to after chunk desc */

	if (ZeroMallocs)
		memset(q, 0, (size_t)(n - sizeof(struct mem_chunk)));

	return (void *) q;
}


void *calloc(size_t nitems, size_t size)
{
	void *ptr;
	
	nitems *= size;
	ptr = malloc(nitems);
	if (ptr != NULL)
		memset(ptr, 0, nitems);
	return ptr;
}


void free(void *param)
{
	struct mem_chunk *o, *p, *q, *s;
	struct mem_chunk *r = (struct mem_chunk *) param;

	/* free(NULL) should do nothing */
	if (r == NULL)
		return;

	/* move back to uncover the mem_chunk */
	r--; /* there it is! */

	if (r->valid != VAL_ALLOC)
		return;

	r->valid = VAL_FREE;

	/* stick it into free list, preserving ascending address order */
	o = NULL;
	p = &_mchunk_free_list;
	q = _mchunk_free_list.next;
	while (q && q < r) 
	{
		o = p;
		p = q;
		q = q->next;
	}

	/* merge after if possible */
	s = (struct mem_chunk *)(((long) r) + r->size);
	if (q && s >= q && q->valid != VAL_BORDER)
	{
		assert(s == q);
		r->size += q->size;
		q = q->next;
		s->size = 0;
		s->next = NULL;
	}
	r->next = q;

	/* merge before if possible, otherwise link it in */
	s = (struct mem_chunk * )(((long) p) + p->size);
	if (q && s >= r && p != &_mchunk_free_list)
	{
		/* remember: r may be below &_mchunk_free_list in memory */
		assert(s == r);

		if (p->valid == VAL_BORDER)
		{
			if (ALLOC_SIZE(p) == r->size)
			{
				o->next = r->next;
				Mfree (p);
#if DEBUG_ALLOC >= 3
				++total_frees;
				--cur_mallocs;
#endif
			}
			else
				p->next = r;

			return;
		}

		p->size += r->size;
		p->next = r->next;
		r->size = 0;
		r->next = NULL;

		s = (struct mem_chunk *)(((long) p) + p->size);
		if ((!_split_mem) && _heapbase != NULL &&
		    s >= (struct mem_chunk *) _heapbase &&
		    s < (struct mem_chunk *) ((char *)_heapbase + _stksize))
		{
			assert(s == (struct mem_chunk *) _heapbase);

			_heapbase = (void *) p;
			_stksize += p->size;
			o->next = p->next; /* o is always != NULL here */
		}
		else if (o->valid == VAL_BORDER && ALLOC_SIZE(o) == p->size)
		{
			q = &_mchunk_free_list;
			s = q->next;
			while (s && s < o)
			{
				q = s;
				s = q->next;
			}
			if (s)
			{
				assert (s == o);
				q->next = p->next;
				Mfree (o);
#if DEBUG_ALLOC >= 3
				++total_frees;
				--cur_mallocs;
#endif
			}
		}
	}
	else
        {
		s = (struct mem_chunk * )(((long) r) + r->size);
		if ((!_split_mem) && _heapbase != NULL &&
		    s >= (struct mem_chunk *) _heapbase &&
		    s < (struct mem_chunk *) ((char *)_heapbase + _stksize))
		{
			assert(s == (struct mem_chunk *) _heapbase);

			_heapbase = (void *) r;
			_stksize += r->size;

			p->next = r->next;
		}
		else
			p->next = r;
	}
}



static void *HeapAlloc(unsigned long sz)
{
	char slush[64];
	register void *sp;

	sp = (void *) slush;
	sz = (sz + 7) & ~((unsigned long) 7L);	/* round up request size next octet */

	if (sp < (void *) ((char *) _heapbase + sz))
		return NULL;

	sp = _heapbase;
	_heapbase = (void *) ((char *) _heapbase + sz);
	_stksize -= (long) sz;

	return sp;
}


/* provided for compilers with sizeof(int) == 2 */
void *sbrk(intptr_t n)
{
	void *rval;

	if ((!_split_mem) && (_heapbase != NULL))
	{
		if (n)
			rval = HeapAlloc(n);
		else
			rval = _heapbase;
	} else
	{
		rval = (void *) Malloc(n);
#if DEBUG_ALLOC >= 3
		if (rval != NULL)
		{
			++total_mallocs;
			++cur_mallocs;
			if (cur_mallocs > max_mallocs)
				max_mallocs = cur_mallocs;
		}
#endif
	}

	if (rval == NULL)
	{
		if (_split_mem)
		{
			/* now switch over to own heap for further requests,
			 * including this one
			 */
			_split_mem = 0;
			return sbrk(n);
		}

		__set_errno(ENOMEM);
		rval = (void *) (-1L);
	}
	return rval;
}


void *realloc(void *r, size_t n)
{
	struct mem_chunk *p;
	long sz;

	/* obscure features:
	 * 
	 * realloc(NULL,n) is the same as malloc(n)
	 * realloc(p, 0) is the same as free(p)
	 */
	if (!r)
		return malloc(n);

	if (n == 0) {
		free(r);
		return NULL;
	}

	p = ((struct mem_chunk *) r) - 1;
	sz = (n + sizeof(struct mem_chunk) + 7) & ~7;

	if (p->size > (sz + ((2 * sizeof(struct mem_chunk) + 7) & ~7)))
	{
		/* resize down */
		void *newr;

		newr = malloc(n);
		if (newr)
		{
			memcpy(newr, r, n);
		    free(r);

			r = newr;
		}
		/* else
		 * malloc failed; can be safely ignored as the new block
		 * is smaller
		 */
	}
	else if (p->size < sz)
	{
		/* block too small, get new one */
		struct mem_chunk *q, *s, *t;

		q = &_mchunk_free_list;
		t = _mchunk_free_list.next;
		while (t && t < p)
		{
			q = t;
			t = t->next;
		}

		/* merge after if possible */
		s = (struct mem_chunk * )(((char *) p) + p->size);
		if (t && s >= t && (long)(p->size + t->size) >= sz
		    && t->valid != VAL_BORDER)
		{
			assert(s == t);

			p->size += t->size;
			q->next = t->next;
			t->size = 0;
			t->next = NULL;
		}
		else
		{
			void *newr;

			newr = malloc(n);
			if (newr)
			{
				memcpy(newr, r, p->size - sizeof(struct mem_chunk));
			    free(r);
			}
			r = newr;
		}
	}

	return (void *) r;
}


void __assert_fail(const char *assertion, const char *file, unsigned int line, const char *function)
{
	(void)function;
	fprintf(stderr, "\nAssertion failed: %s, file %s, line %u\n",
		assertion, file, line);
	abort();
}


void _crtinit(void)
{
	register BASEPAGE *bp;
	register long m;
	register long freemem;

	bp = _base;

	/* m = # bytes used by environment + args */
	m = (char *)_StkLim - (char *)environ;

	/* make m the total number of bytes required by program sans stack/heap */
	m += (bp->p_tlen + bp->p_dlen + bp->p_blen + sizeof(BASEPAGE));
	m = (m + 3L) & (~3L);

	/* freemem the amount of free mem accounting for MINFREE at top */
	if ((freemem = (long)bp->p_hitpa - (long)bp - MINFREE - m) <= 0L)
	{
		(void) Cconws("Fatal error: insufficient memory\r\n");
		(void) Cconws("Hint: either decrease stack size using 'stack' command (not recomended)\r\n" \
			   "      or increase TPA_INITIALMEM value in mint.cnf.\r\n");
		Pterm(-1);
	}
	
	if (_stksize >= -1L)
		/* malloc from Malloc first, then from own heap */
		_split_mem = 1;

	if (_stksize == -1L) {
		_stksize = freemem;
		_heapbase = (void *)((long)bp + m);
	} else if (_stksize == 0L) {	/* free all but MINKEEP */
		_stksize = MINKEEP;
	} else if (_stksize == 1L) { 	/* keep 1/4, free 3/4 */
		_stksize = freemem >> 2;
	} else if (_stksize ==  2L) {	/* keep 1/2, free 1/2 */
		_stksize = freemem >> 1;
	} else if (_stksize == 3L) {	/* keep 3/4, free 1/4 */
		_stksize = freemem - (freemem >> 2); 
	} else {
		if(_stksize < -1L) {	/* keep |_stksize|, use heap for mallocs */
			_stksize = -_stksize;
			_heapbase = (void *)((long)bp + m);
		}
	}
#if 0
	printf("_base: %p\n", _base);
	printf("_stksize: %lx\n", _stksize);
	printf("_heapbase: %p\n", _heapbase);
	printf("bss start & length: %p %lx\n", bp->p_bbase, bp->p_blen);
	printf("hitpa: %p\n", bp->p_hitpa);
#endif
}


void _crtexit(void)
{
#if DEBUG_ALLOC >= 3
	fprintf(stderr, "Mallocs: %lu (max %lu), Mfrees %lu, cur %ld\n",
		total_mallocs,
		max_mallocs,
		total_frees,
		cur_mallocs);
#if 0
	{
		struct mem_chunk *p;
		p = &_mchunk_free_list;
		while (p->next)
		{
			p = p->next;
			fprintf(stderr, "%s: %p %lx",
				p->valid == VAL_FREE ? "free" :
				p->valid == VAL_ALLOC ? "alloc" :
				p->valid == VAL_BORDER ? "border" :
				"???",
				p,
				p->size);
			if (p->valid == VAL_BORDER)
				fprintf(stderr, " allocsize %lx", ALLOC_SIZE(p));
			fprintf(stderr, "\n");
		}
	}
#endif
#endif
}

#endif
