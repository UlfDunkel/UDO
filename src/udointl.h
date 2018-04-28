#ifndef __UDO_INTL_H__
#define __UDO_INTL_H__

#ifdef ENABLE_NLS
# include <libintl.h>
# include <locale.h>

/* The separator between msgctxt and msgid in a .mo file.  */
#ifndef GETTEXT_CONTEXT_GLUE
#  define GETTEXT_CONTEXT_GLUE "\004"
#endif

# define _(String) xs_dgettext(GETTEXT_PACKAGE, String)
# define P_(String, Stringp, n) xs_dngettext(GETTEXT_PACKAGE, String, Stringp, n)
# define C_(Context, String) xs_dgettext(GETTEXT_PACKAGE, Context GETTEXT_CONTEXT_GLUE String)
# define N_(String) String
# define NC_(Context, String) Context GETTEXT_CONTEXT_GLUE String

#undef printf
#undef fprintf
#undef sprintf
#undef vfprintf
#undef vprintf
#undef vsprintf
#undef snprintf
#undef vsnprintf
#undef asprintf
#undef vasprintf
#undef fwprintf
#undef vfwprintf
#undef wprintf
#undef vwprintf
#undef swprintf
#undef vswprintf

#else  /* !ENABLE_NLS */

# define _(String) (String)
# define C_(Context, String) (String)
# define P_(String, Stringp, n) ((n) == 1 ? (String) : (Stringp))
# define N_(String) (String)
# define NC_(Context, String) String
# define textdomain(String) (String)
# define gettext(String) (String)
# define dgettext(Domain, String) (String)
# define dcgettext(Domain, String, Type) (String)
# define bindtextdomain(Domain, Directory) (Domain) 

#endif /* !ENABLE_NLS */

EXTERN_C_BEG

const char *xs_dgettext(const char *domain, const char *msgid);
const char *xs_dngettext(const char *domain, const char *msgid, const char *msgid_plural, unsigned long n);

const char *xs_get_locale_dir(void);
char *g_get_package_installation_directory(void);
void xs_locale_exit(void);

EXTERN_C_END

#endif /* __UDO_INTL_H__ */
