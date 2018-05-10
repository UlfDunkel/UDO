#define CC_FOR_BUILD 1

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif
#undef HAVE_GLIB
#undef HAVE_GTK
#include "windows_.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>
#include <gettext-po.h>
#include "rcintl.h"

#include <getopt.h>
#define LANG_STRINGS 1
#include "../rcintl/localenm.c"

#ifndef CATOBJEXT
#define CATOBJEXT ".gmo"
#endif

#ifndef FALSE
#  define FALSE 0
#  define TRUE  1
#endif
#ifndef UNUSED
#  define UNUSED(x) ((void)(x))
#endif

#define G_IS_DIR_SEPARATOR(c) ((c) == '/' || (c) == '\\')
#define G_DIR_SEPARATOR '/'

#define g_new(t, n) (t *)malloc(sizeof(t) * (n))


char const gl_program_name[] = "polinguas";

static int num_errors;
static int num_warnings;
static int bShowVersion;
static int bShowHelp;

struct fileentry {
	char *filename;
	char *lang;
	struct fileentry *next;
};
static struct fileentry *filelist;
static const char *podir = "../po";


/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void handle_error(int severity)
{
	switch (severity)
	{
	case PO_SEVERITY_WARNING:
		num_warnings++;
		break;
	case PO_SEVERITY_ERROR:
		num_errors++;
		break;
	case PO_SEVERITY_FATAL_ERROR:
	default:
		abort();
		break;
	}
}

/*** ---------------------------------------------------------------------- ***/

static void my_xerror(
	int severity,
	po_message_t message,
	const char *filename,
	size_t lineno,
	size_t column,
	int multiline_p,
	const char *message_text)
{
	UNUSED(message);
	UNUSED(column);
	UNUSED(multiline_p);
	fprintf(stderr, "%s: %s:%ld: %s\n", gl_program_name, filename, (long)lineno, message_text);
	handle_error(severity);
}

/*** ---------------------------------------------------------------------- ***/

/* Signal a problem that refers to two messages.
   Similar to two calls to xerror.
     If possible, a "..." can be appended to MESSAGE_TEXT1 and prepended to
     MESSAGE_TEXT2.  */
static void my_xerror2(
	int severity,
	po_message_t message1,
	const char *filename1, size_t lineno1, size_t column1,
	int multiline_p1, const char *message_text1,
	po_message_t message2,
	const char *filename2, size_t lineno2, size_t column2,
	int multiline_p2, const char *message_text2)
{
	UNUSED(message1);
	UNUSED(column1);
	UNUSED(multiline_p1);
	UNUSED(message2);
	UNUSED(column2);
	UNUSED(multiline_p2);
	fprintf(stderr, "%s: %s:%ld: %s\n", gl_program_name, filename1, (long)lineno1, message_text1);
	fprintf(stderr, "%s: %s:%ld: %s\n", gl_program_name, filename2, (long)lineno2, message_text2);
	handle_error(severity);
}

static const struct po_xerror_handler my_xerror_handler = {
	my_xerror,
	my_xerror2
};

#define SUBLANG_SHIFT 10
#undef MAKELANGID
#define MAKELANGID(primary, sub) (((sub) << SUBLANG_SHIFT) | (primary))
#undef PRIMARYLANGID
#define PRIMARYLANGID(id) ((id) & ~(1 << SUBLANG_SHIFT))
#undef SUBLANGID
#define SUBLANGID(id) ((id) >> SUBLANG_SHIFT)
#undef MAKELCID
#define MAKELCID(l,s) ((LCID)((((LCID)((uint16_t)(s)))<<16)|((LCID)((uint16_)(l)))))
#undef LANGIDFROMLCID
#define LANGIDFROMLCID(l) ((uint16_t)((l) & 0xffff))

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

/*
 * like basename() or g_basename(),
 * but using this function throughout the package
 * because we sometimes have to deal with pathnames
 * from different OS than current one
 */
static const char *hyp_basename(const char *path)
{
	const char *p;
	const char *base = NULL;
	
	if (path == NULL)
		return path;
	p = path;
	while (*p != '\0')
	{
		if (G_IS_DIR_SEPARATOR(*p))
			base = p + 1;
		++p;
	}
	if (base != NULL)
		return base;
	
	if (isalpha(path[0]) && path[1] == ':')
	{
    	/* can only be X:name, without slash */
    	path += 2;
	}
	
	return path;
}

/*** ---------------------------------------------------------------------- ***/

static char *g_build_filename(const char *first, ...)
{
	va_list args;
	size_t len;
	const char *str;
	char *ret, *ptr;
	
	if (first == NULL)
		return NULL;
	len = strlen(first) + 1;
	va_start(args, first);
	for (;;)
	{
		str = va_arg(args, const char *);
		if (str == NULL)
			break;
		while (G_IS_DIR_SEPARATOR(*str))
			str++;
		len += strlen(str) + 1;
	}
	va_end(args);
	ret = (char *)malloc(len);
	if (ret == NULL)
		return NULL;
	strcpy(ret, first);
	ptr = ret + strlen(ret);
	while (ptr > ret && G_IS_DIR_SEPARATOR(ptr[-1]))
		*--ptr = '\0';
	va_start(args, first);
	for (;;)
	{
		str = va_arg(args, const char *);
		if (str == NULL)
			break;
		while (G_IS_DIR_SEPARATOR(*str))
			str++;
		if (*str == '\0')
			continue;
		ptr = ret + strlen(ret);
		*ptr++ = G_DIR_SEPARATOR;
		strcpy(ptr, str);
		ptr += strlen(ptr);
		while (ptr > ret && G_IS_DIR_SEPARATOR(ptr[-1]))
			*--ptr = '\0';
	}
	va_end(args);
	return ret;
}

/*** ---------------------------------------------------------------------- ***/

static char *g_strconcat(const char *first, ...)
{
	va_list args;
	size_t len;
	const char *str;
	char *ret, *ptr;
	
	if (first == NULL)
		return NULL;
	len = strlen(first) + 1;
	va_start(args, first);
	for (;;)
	{
		str = va_arg(args, const char *);
		if (str == NULL)
			break;
		len += strlen(str);
	}
	va_end(args);
	ret = g_new(char, len);
	if (ret == NULL)
		return NULL;
	strcpy(ret, first);
	ptr = ret + strlen(ret);
	va_start(args, first);
	for (;;)
	{
		str = va_arg(args, const char *);
		if (str == NULL)
			break;
		strcpy(ptr, str);
		ptr += strlen(ptr);
	}
	va_end(args);
	return ret;
}

/*** ---------------------------------------------------------------------- ***/

/*
 * Removes trailing whitespace from a string.
 */
static char *g_strchomp(char *str)
{
	char *end;
	
	if (str == NULL)
		return NULL;
	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n'))
		--end;
	*++end = '\0';
	return str;
}

/*** ---------------------------------------------------------------------- ***/

/*
 * Removes leading whitespace from a string, by moving the rest of the characters forward.
 */
static char *g_strchug(char *str)
{
	char *src;
	
	if (str == NULL)
		return NULL;
	src = str;
	while (*src == ' ' || *src == '\t')
		src++;
	if (str != src)
		memmove(str, src, strlen(src) + 1);
	return str;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static char *translations;

static int dofile(FILE *out, struct fileentry *entry)
{
	po_file_t file = po_file_read(entry->filename, &my_xerror_handler);
	const char *const *domains;
	const char *header;
	char *lang;
	int i, n;
	char *moname;
	char *p;
	char *tmp2;
	char tmp[100];
	
	if (file == NULL)
	{
		fprintf(stderr, "%s: %s: %s\n", gl_program_name, entry->filename, strerror(errno));
		return FALSE;
	}
	domains = po_file_domains(file);
	if (domains == NULL || domains[0] == NULL || strcmp(domains[0], "messages") != 0)
	{
		fprintf(stderr, "%s: %s: %s\n", gl_program_name, entry->filename, "not a messages file");
		po_file_free(file);
		return FALSE;
	}
	header = po_file_domain_header(file, domains[0]);
	lang = po_header_field(header, "Language");
	if (lang)
	{
		free(entry->lang);
		entry->lang = strdup(lang);
		free(lang);
	}
	po_file_free(file);
	
	n = (int)(sizeof(sublang_table) / sizeof(sublang_table[0])) - 1;
	for (i = 0; i < n; i++)
	{
		if (strncmp(entry->lang, sublang_table[i].po_name, sublang_table[i].namelen) == 0)
			break;
	}
	if (i >= n)
	{
		for (i = 0; i < n; i++)
		{
			if (strncmp(entry->lang, sublang_table[i].po_name, 2) == 0 &&
				(SUBLANGID(sublang_table[i].id) == SUBLANG_DEFAULT ||
				 SUBLANGID(sublang_table[i].id) == SUBLANG_NEUTRAL))
				break;
		}
	}
	if (i >= n)
	{
		fprintf(stderr, "%s: %s: unsupported language %s\n", gl_program_name, entry->filename, entry->lang);
	}
	fprintf(out, "LANGUAGE %s, %s\n", sublang_table[i].langname, sublang_table[i].subname);
	moname = strdup(hyp_basename(entry->filename));
	p = strrchr(moname, '.');
	if (p)
		*p = '\0';
	fprintf(out, "1 RT_MOFILE LOADONCALL MOVEABLE DISCARDABLE IMPURE \"%s/%s" CATOBJEXT "\"\n", podir, moname);
	free(moname);
	if (translations == NULL)
	{
		translations = strdup("0x0409, 1200"); /* LANG_ENGLISH, SUBLANG_ENGLISH_US */
	}
	sprintf(tmp, ", 0x%04x, 1200", sublang_table[i].id);
	tmp2 = g_strconcat(translations, tmp, NULL);
	free(translations);
	translations = tmp2;
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void addfile(const char *path)
{
	char *filename = NULL;
	struct stat s;
	struct fileentry *entry;
	char *lang;
	char *p;
	struct fileentry **root;
	
	if (stat(path, &s) == 0)
		filename = strdup(path);
	if (filename == NULL)
		filename = g_build_filename(podir, path, NULL);
	entry = (struct fileentry *)malloc(sizeof(*entry));
	entry->filename = filename;
	lang = strdup(hyp_basename(path));
	p = strchr(lang, '.');
	if (p)
		*p = '\0';
	entry->lang = lang;
	root = &filelist;
	while (*root)
		root = &(*root)->next;
	*root = entry;
}

/*** ---------------------------------------------------------------------- ***/

static int read_linguas(const char *filename)
{
	FILE *fp;
	char buf[1024];
	
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		fprintf(stderr, "%s: %s: %s:\n", gl_program_name, filename, strerror(errno));
		return FALSE;
	}
	while (fgets(buf, (int)sizeof(buf), fp) != NULL)
	{
		g_strchomp(buf);
		g_strchug(buf);
		if (*buf == '\0' || *buf == '#')
			continue;
		strncat(buf, ".po", sizeof(buf));
		addfile(buf);
	}
	
	fclose(fp);
	return TRUE;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

enum {
	OPT_HELP = 'h',
	OPT_VERSION = 'V',
	OPT_LINGUAS = 256,
	OPT_PODIR,
};

static struct option const long_options[] = {
	{ "linguas", required_argument, NULL, OPT_LINGUAS },
	{ "podir", required_argument, NULL, OPT_PODIR },
	{ "help", no_argument, NULL, OPT_HELP },
	{ "version", no_argument, NULL, OPT_VERSION },
	
	{ NULL, no_argument, NULL, 0 }
};

/*** ---------------------------------------------------------------------- ***/

static void show_version(void)
{
}

/*** ---------------------------------------------------------------------- ***/

static void show_help(void)
{
}

/*** ---------------------------------------------------------------------- ***/

int main(int argc, char **argv)
{
	int i;
	int c;
	int retval = TRUE;
	
	while ((c = getopt_long_only(argc, argv, "hV?", long_options, NULL)) != EOF)
	{
		switch (c)
		{
		case OPT_LINGUAS:
			retval &= read_linguas(optarg);
			break;
		
		case OPT_PODIR:
			podir = optarg;
			break;
		
		case OPT_HELP:
			bShowHelp = TRUE;
			break;
		case OPT_VERSION:
			bShowVersion = TRUE;
			break;
		case '?':
			if (optopt == '?')
			{
				bShowHelp = TRUE;
			} else
			{
				retval = FALSE;
			}
			break;
		
		case 0:
			/* option which just sets a var */
			break;
		
		case 1:
			addfile(optarg);
			break;
		
		default:
			/* error message already issued */
			retval = FALSE;
			break;
		}
	}

	if (bShowHelp)
	{
		show_help();
	} else if (bShowVersion)
	{
		show_version();
	} else if (retval)
	{
		struct fileentry *l;
		FILE *out = stdout;

		for (i = optind; i < argc; i++)
		{
			addfile(argv[i]);
		}
		if (filelist == NULL)
		{
			fprintf(stderr, "%s: no files\n", gl_program_name);
			retval = FALSE;
		}
		fprintf(out, "#define RT_MOFILE %d\n", RT_MOFILE);
		fprintf(out, "\n");
		for (l = filelist; l; l = l->next)
		{
			retval &= dofile(out, l);
		}
		if (translations)
		{
			fprintf(out, "\n");
			fprintf(out, "#define PO_TRANSLATIONS %s\n", translations);
			free(translations);
			translations = NULL;
		}
		fprintf(out, "\n");
		fprintf(out, "LANGUAGE LANG_ENGLISH, SUBLANG_ENGLISH_US\n");
		fprintf(out, "#pragma code_page(1252)\n");
		fprintf(out, "\n");
	}
	
	return retval == FALSE || num_errors > 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
