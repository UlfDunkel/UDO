AC_DEFUN([AC_C_VA_COPY], [
dnl **********************
dnl *** va_copy checks ***
dnl **********************
dnl we currently check for all three va_copy possibilities, so we get
dnl all results in config.log for bug reports.
AC_CACHE_CHECK([for an implementation of va_copy()],glib_cv_va_copy,[
	AC_LINK_IFELSE([AC_LANG_SOURCE([[#include <stdarg.h>
#include <stdlib.h>
	void f (int i, ...) {
	va_list args1, args2;
	va_start (args1, i);
	va_copy (args2, args1);
	if (va_arg (args2, int) != 42 || va_arg (args1, int) != 42)
	  exit (1);
	va_end (args1); va_end (args2);
	}
	int main() {
	  f (0, 42);
	  return 0;
	}]])],
	[glib_cv_va_copy=yes],
	[glib_cv_va_copy=no])
])
AC_CACHE_CHECK([for an implementation of __va_copy()],glib_cv___va_copy,[
	AC_LINK_IFELSE([AC_LANG_SOURCE([[#include <stdarg.h>
#include <stdlib.h>
	void f (int i, ...) {
	va_list args1, args2;
	va_start (args1, i);
	__va_copy (args2, args1);
	if (va_arg (args2, int) != 42 || va_arg (args1, int) != 42)
	  exit (1);
	va_end (args1); va_end (args2);
	}
	int main() {
	  f (0, 42);
	  return 0;
	}]])],
	[glib_cv___va_copy=yes],
	[glib_cv___va_copy=no])
])

if test "x$glib_cv_va_copy" = "xyes"; then
  g_va_copy_func=va_copy
else if test "x$glib_cv___va_copy" = "xyes"; then
  g_va_copy_func=__va_copy
fi
fi

if test -n "$g_va_copy_func"; then
  AC_DEFINE_UNQUOTED(G_VA_COPY,$g_va_copy_func,[A 'va_copy' style function])
fi

AC_CACHE_CHECK([whether va_lists can be copied by value],glib_cv_va_val_copy,[
	AC_TRY_RUN([#include <stdarg.h>
#include <stdlib.h> 
	void f (int i, ...) {
	va_list args1, args2;
	va_start (args1, i);
	args2 = args1;
	if (va_arg (args2, int) != 42 || va_arg (args1, int) != 42)
	  exit (1);
	va_end (args1); va_end (args2);
	}
	int main() {
	  f (0, 42);
	  return 0;
	}],
	[glib_cv_va_val_copy=yes],
	[glib_cv_va_val_copy=no],
	[glib_cv_va_val_copy=yes])
])

if test "x$glib_cv_va_val_copy" = "xno"; then
  AC_DEFINE(G_VA_COPY_AS_ARRAY,1, ['va_lists' cannot be copies as values])
fi

])
