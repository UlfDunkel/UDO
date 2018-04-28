#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

#ifdef _DEBUG

int __my_assert(const char *expr, const char *file, int line)
{
	fflush(stdout);
	fprintf(stderr, "assertion failed: file %s, line %d:\n%s\n", file, line, expr);
	fflush(stderr);
	abort();
	return 1;
}

#endif
