#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#if defined(__WIN32__) || defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define STRICT
#define WINVER 0x0500
#define __SIMPLE_LOCALES__
#include <windows.h>
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <errno.h>
#include "udoport.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "udointl.h"
#include "udomem.h"
#include "str.h"


#ifdef ENABLE_NLS

static char *localedir = NULL;

/*** ---------------------------------------------------------------------- ***/

const char *xs_dgettext(const char *domain, const char *msgid)
{
	const char *ret = dgettext(domain, msgid);
	const char *ctxt;
	
	if (ret == msgid)
	{
		ctxt = strchr(msgid, GETTEXT_CONTEXT_GLUE[0]);
		if (ctxt != NULL)
			ret = dgettext(domain, ctxt + 1);
	}
	return ret;
}

/*** ---------------------------------------------------------------------- ***/

const char *xs_dngettext(const char *domain, const char *msgid, const char *msgid_plural, unsigned long n)
{
	const char *ret = dngettext(domain, msgid, msgid_plural, n);
	const char *ctxt;
	
	if (ret == msgid || ret == msgid_plural)
	{
		ctxt = strchr(msgid, GETTEXT_CONTEXT_GLUE[0]);
		if (ctxt != NULL)
			ret = dngettext(domain, ctxt + 1, msgid_plural, n);
	}
	return ret;
}

#endif /* ENABLE_NLS */

/*** ---------------------------------------------------------------------- ***/

char *g_get_package_installation_directory(void)
{
	char *retval;
	char *p;

#if defined(__WIN32__) || defined(_WIN32)
	wchar_t wc_fn[MAX_PATH];
	int len;
	
	if (!GetModuleFileNameW(NULL, wc_fn, MAX_PATH))
		return NULL;
	len = WideCharToMultiByte(CP_UTF8, 0, wc_fn, -1, NULL, 0, NULL, NULL);
	retval = malloc(len);
	WideCharToMultiByte(CP_UTF8, 0, wc_fn, -1, retval, len, NULL, NULL);
	if ((p = strrchr(retval, '\\')) != NULL)
		*p = '\0';
#else
	retval = NULL;
	{
		char path[PATH_MAX];
		ssize_t len;
		
		if ((len = readlink("/proc/self/exe", path, sizeof(path) - 1)) > 0)
		{
			path[len] = '\0';
			retval = strdup(path);
			if ((p = strrchr(retval, '/')) != NULL)
				*p = '\0';
		}
	}
	if (retval == NULL)
		retval = strdup(BINDIR);
#endif

#if USE_SLASH
	while ((p = strrchr(retval, '\\')) != NULL)
	   *p = '/';
	p = strrchr(retval, '/');
#else
	while ((p = strrchr(retval, '/')) != NULL)
	   *p = '\\';
	p = strrchr(retval, '\\');
#endif

	if (p && (my_stricmp(p + 1, "bin") == 0 ||
        my_stricmp(p + 1, "bin64") == 0 ||
        my_stricmp(p + 1, "lib64") == 0 ||
	    my_stricmp(p + 1, "lib") == 0))
	    *p = '\0';

#ifdef G_WITH_CYGWIN
	/* In Cygwin we need to have POSIX paths */
	{
		char tmp[MAX_PATH];

		cygwin_conv_to_posix_path(retval, tmp);
		free(retval);
	    retval = strdup(tmp);
	}
#endif

	return retval;
}

/*** ---------------------------------------------------------------------- ***/

#ifdef ENABLE_NLS
const char *xs_get_locale_dir(void)
{
	if (localedir == NULL)
	{
		char *root, *temp;
		
		root = g_get_package_installation_directory();
		temp = (char *)malloc(strlen(root) + sizeof("/share/locale"));
#if USE_SLASH
		strcat(strcpy(temp, root), "/share/locale");
#else
		strcat(strcpy(temp, root), "\\share\\locale");
#endif
		free(root);

#if defined(__WIN32__) || defined(_WIN32)
		/* localedir is passed to bindtextdomain() which isn't
		 * UTF-8-aware.
		 */
		{
			int len;
			wchar_t *wc_fn;
			
			len = MultiByteToWideChar(CP_UTF8, 0, temp, -1, NULL, 0);
			wc_fn = malloc(len * sizeof(wchar_t));
			MultiByteToWideChar(CP_UTF8, 0, temp, -1, wc_fn, len);
			len = WideCharToMultiByte(CP_ACP, 0, wc_fn, -1, NULL, 0, NULL, NULL);
			localedir = malloc(len);
			WideCharToMultiByte(CP_ACP, 0, wc_fn, -1, localedir, len, NULL, NULL);
			free(wc_fn);
			free(temp);
		}
#else
		localedir = temp;
#endif
	}
	
	return localedir;
}


void xs_locale_exit(void)
{
	if (localedir)
	{
		free(localedir);
		localedir = NULL;
	}
}
#endif
