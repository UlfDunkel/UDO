#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __TOS__
#include <mint/arch/nf_ops.h>
#endif

#ifdef _DEBUG

int __my_assert(const char *expr, const char *file, int line);

#define ASSERT(expr) ((void)((expr) ? 0 : __my_assert(#expr, __FILE__, __LINE__)))

#else

#define ASSERT(expr)

#endif

#endif /* __DEBUG_H__ */
