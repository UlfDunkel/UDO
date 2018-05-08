#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "windows_.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_IO_H
#include <io.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_SETLOCALE
#include <locale.h>
#endif
#include <sys/stat.h>

/* avoid warnings from G_TYPE_* macros */
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wstrict-prototypes"
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wc++-compat"
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib/gstdio.h>
#ifdef G_OS_UNIX
#include <gio/gdesktopappinfo.h>
#endif
#pragma GCC diagnostic warning "-Wcast-qual"
#pragma GCC diagnostic warning "-Wstrict-prototypes"
#pragma GCC diagnostic warning "-Wc++-compat"

#include "udoport.h"
#undef GETTEXT_PACKAGE
#define GETTEXT_PACKAGE "udosh"
#include "udointl.h"
#include "gtkcompat.h"
#include "udomem.h"

#define UDOSH_VERSION "1.06"


#define fixnull(p) ((p) == NULL ? "" : (p))
#define empty(p) ((p) == NULL || *(p) == '\0')

#ifdef G_PLATFORM_WIN32
#define filename_cmp stricmp
#else
#define filename_cmp strcmp
#endif


#define IDS_TYPE_SOURCE      _("source")
#define IDS_TYPE_DESTINATION _("destination")
#define IDS_TYPE_RESULT      _("result") 
#define IDS_TYPE_PARAMETER   _("parameter")

/*
 * filters for file chooser.
 * Filters are separated by newlines.
 * In each filter, the display string is separated from the extension list by '|'.
 * If a display string is not defined, the extension list is used.
 * An extension list may specify several wildcard specifications separated by spaces.
 */
#define IDS_SELECT_PROGRAM _("*.exe *.bat *.cmd|Program files (*.exe;*.bat;*.cmd)\n*.*|All files (*.*)\n")
#define IDS_SELECT_SOURCE _("*.u*|UDO files (*.u*)\n*.*|All files (*.*)\n")
#define IDS_SELECT_DEST _("*.*|All files (*.*)\n")
#define IDS_SELECT_HELP _("*.hlp *.chm|Help files (*.hlp;*.chm)\n*.*|All files (*.*)\n")

extern char const gl_program_name[];
extern char const gl_program_version[];

GdkPixbuf *app_icon(void);
void check_desktop_file(char **filename);
void check_toplevels(GtkWidget *toplevel);

