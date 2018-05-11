/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : msg.c
*  Symbol prefix: msg
*
*  Copyright    : 1995-2001 Dirk Hagedorn
*  Open Source  : since 2001
*
*                 This program is free software; you can redistribute it and/or
*                 modify it under the terms of the GNU General Public License
*                 as published by the Free Software Foundation; either version 2
*                 of the License, or (at your option) any later version.
*
*                 This program is distributed in the hope that it will be useful,
*                 but WITHOUT ANY WARRANTY; without even the implied warranty of
*                 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*                 GNU General Public License for more details.
*
*                 You should have received a copy of the GNU General Public License
*                 along with this program; if not, write to the Free Software
*                 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*
*-------------------------------------------------------------------------------
*
*  Author       : Dirk Hagedorn (udo@dirk-hagedorn.de)
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - check if warning_no_isochar() is still needed
*                 - check if warning_no_texchar() is still needed
*                 - try and combine more error message functions, e.g. for images
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Jan 23: - converted all German umlauts in comments into plain ASCII
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Mar 04: - file tidied up (some message texts updated or adjusted)
*                - message wrapper functions now global
*  2014:
*    ggs Apr 20: Add Node6
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include "udoport.h"
#include "constant.h"
#include "version.h"
#include "udointl.h"
#include "udo_type.h"
#include "udo.h"
#include "toc.h"
#include "gui.h"
#include "udomem.h"
#include "file.h"

#include "export.h"
#include "msg.h"





/*******************************************************************************
*
*     LOCAL VARIABLES
*
******************************************|************************************/

LOCAL int error_counter;
LOCAL int warning_counter;
LOCAL int note_counter;





/*******************************************************************************
*
*     LOCAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  loglnpos():
*     Ausgabe ins Logfile inklusive Datei und Zeilennummer
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void loglnpos(const char *we, const char *format, va_list args)
{
	char *txt,*msg;
	char lineinfo[100];
	FILE_LINENO realstart;

	if (uiCurrFileLine > 0)
	{
		if (uiMultiLines > 0)
		{
			realstart = uiCurrFileLine - uiMultiLines;
			sprintf(lineinfo, "%lu-%lu: ", realstart, uiCurrFileLine);
		} else
		{
			sprintf(lineinfo, "%lu: ", uiCurrFileLine);
		}
	} else
	{
		lineinfo[0] = EOS;
	}

	msg = um_strdup_vprintf(format, args);
	txt = um_strdup_printf("%s: %s %s%s", we, sCurrFileName, lineinfo, msg);
	logln(txt);

	show_logln_message(txt);			/* Ausgabe ans GUI weiterreichen */
	free(txt);
	free(msg);
}





/*******************************************************************************
*
*  my_strerror():
*     Fehlermeldung abhaengig von errno ausgeben, zumeist nach fehlgeschlagenem Oeffnen von Dateien
*
*  Notes:
*     Falls der Compiler strerror nicht anbietet, dann in version.h #define HAVE_STRERROR 0 setzen!
*     Falls der Compiler sys_errlist nicht anbietet, dann in version.h #define HAVE_SYS_ERRLIST 0 setzen!
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL const char *my_strerror(int err_no)
{
#if defined(HAVE_STRERROR)
	return strerror(err_no);
#elif defined(HAVE_SYS_ERRLIST)
	return sys_errlist[err_no];
#else
	static char s[20];

	sprintf(s, "Error #%d", err_no);

	return s;
#endif
}





/*******************************************************************************
*
*  errno_logln():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void errno_logln(const char *s)
{
	const char *p;
	char *buf;

	p = my_strerror(errno);

	if (s[0] != EOS)
	{
		buf = um_strdup_printf("%s: %s", s, p);
	} else
	{
		buf = strdup(p);
	}
	logln(buf);
	show_logln_message(buf);
	free(buf);
}








/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  warning_message():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_message(const char *msg, ...)
{
	va_list args;

	if (!bNoWarnings)
	{
		va_start(args, msg);
		loglnpos(_("Warning"), msg, args);
		va_end(args);
	}
	warning_counter++;
}





/*******************************************************************************
*
*  error_message():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_message(const char *msg, ...)
{
	va_list args;

	va_start(args, msg);
	loglnpos(_("Error"), msg, args);
	va_end(args);
	error_counter++;
}





/*******************************************************************************
*
*  logln():
*     output a line and line feed into the log file
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void logln(const char *s)
{
	/*
	 * if no logfile, output wil go to screen;
	 * suppress if requested by quiet option
	 */
	if (bBeQuiet && bNoLogfile)
		return;

	/*
	 * if no logfile, fLogfile will be stderr;
	 * suppress if using GUI and output should not go there
	 */
	if (bNoLogfile && no_stderr_output)
		return;

	if (fLogfile == NULL)
		return;
	if (*s == '\0' && fLogfile == stderr)
		return;

	fprintf(fLogfile, "%s\n", s);
	fflush(fLogfile);
}





/*******************************************************************************
*
*  vloglnf():
*     Ausgabe einer Zeile ins Logfile inkl. Zeilenvorschub mit Variablen
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void vloglnf(const char *fmt, ...)
{
	va_list ap;
	char *s;

	va_start(ap, fmt);
	s = um_strdup_vprintf(fmt, ap);
	va_end(ap);
	logln(s);
	free(s);
}





/*******************************************************************************
*
*  note_message():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void note_message(const char *msg, ...)
{
	va_list args;

	if (!bNoWarnings && msg != NULL)
	{
		va_start(args, msg);
		loglnpos(_("Note"), msg, args);
		va_end(args);
	}
	note_counter++;
}





/*******************************************************************************
*
*  fatal_message():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void fatal_message(const char *msg, ...)
{
	va_list args;

	va_start(args, msg);
	loglnpos(_("Fatal Error"), msg, args);
	va_end(args);
	error_counter++;
	bFatalErrorDetected = TRUE;
}





/*******************************************************************************
*
*  logln_warnings_errors():
*     output header line for errors, warnings and notes into log
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void logln_warnings_errors(void)
{
	if (fLogfile == stderr)
		return;
	logln(_("######## errors, warnings and notes:"));
	logln("");
}





/*******************************************************************************
*
*  logln_information():
*     output header line for information into log
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void logln_information(void)
{
	logln("");
	logln(_("######## information:"));
	logln("");
}





/*******************************************************************************
*
*  logln_interrupted():
*     output header line for interruption into log
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void logln_interrupted(void)
{
	logln(_("interruption"));
}





/*******************************************************************************
*
*  logln_file_generated():
*     output info about generated file into log
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void logln_file_generated(const char *kind, const char *filename, const char *suff)
{
	char *m;

	m = um_strdup_printf(_("%s written to %s%s"), kind, filename, suff);
	logln(m);
	free(m);
}





/*******************************************************************************
*
*  error_open_logfile():
*     program error message: couldn't open log file
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_open_logfile(const char *s)
{
	error_message(_("couldn't open logfile <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_open_hypfile():
*     program error message: couldn't open hyphenation file
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_open_hypfile(const char *s)
{
	error_message(_("couldn't open hyphen file <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_open_idxfile():
*     program error message: couldn't open index file
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_open_idxfile(const char *s)
{
	error_message(_("couldn't open index file <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_open_treefile():
*     program error message: couldn't open tree file
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_open_treefile(const char *s)
{
	error_message(_("couldn't open treefile <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_open_uprfile():
*     program error message: couldn't open project file
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_open_uprfile(const char *s)
{
	error_message(_("couldn't open project file <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_open_outfile():
*     program error message: couldn't open destination file
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_open_outfile(const char *s)
{
	error_message(_("couldn't open destination file <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_open_infile():
*     program error message: couldn't open source file
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_open_infile(const char *s)
{
	error_message(_("couldn't open source file <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_write_img():
*     program error message: couldn't write IMG header
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_write_img(const char *s)
{
	error_message(_("couldn't write IMG header of <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_read_img():
*     program error message: couldn't read IMG header
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_read_img(const char *s)
{
	error_message(_("couldn't read IMG header of <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_read_bmp():
*     program error message: couldn't read BMP header
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_read_bmp(const char *s)
{
	error_message(_("couldn't read BMP header of <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_read_pcx():
*     program error message: couldn't read PCX header
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_read_pcx(const char *s)
{
	error_message(_("couldn't read PCX header of <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_read_msp():
*     program error message: couldn't read MSP header
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_read_msp(const char *s)
{
	error_message(_("couldn't read MSP header of <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_read_gif():
*     program error message: couldn't read GIF header
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_read_gif(const char *s)
{
	error_message(_("couldn't read GIF header of <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_read_png():
*     program error message: couldn't read PNG header
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_read_png(const char *s)
{
	error_message(_("couldn't read PNG header of <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_read_jpeg():
*     program error message: couldn't read JPEG header
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_read_jpeg(const char *s)
{
	error_message(_("couldn't read JPEG header of <%s>"), s);
	errno_logln(s);
}





/*******************************************************************************
*
*  error_open_pass1():
*     program error message: couldn't open <file> in pass 1
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_open_pass1(const char *s)
{
	const char *e;

	e = my_strerror(errno);
	error_message(_("couldn't open <%s>: %s"), s, e);
}





/*******************************************************************************
*
*  error_open_pass2():
*     program error message: couldn't open <file> in pass 2
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_open_pass2(const char *s)
{
	const char *e;

	e = my_strerror(errno);
	error_message(_("couldn't open <%s>: %s"), s, e);
}





/*******************************************************************************
*
*  error_mkdir():
*     program error message: couldn't make directory
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_mkdir(const char *s)
{
	const char *e;

	e = my_strerror(errno);
	error_message(_("couldn't make directory <%s>: %s"), s, e);
}





/*******************************************************************************
*
*  error_malloc_failed():
*     program error message: memory allocation failed
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_malloc_failed(size_t size)
{
	fatal_message(_("failed to allocate %lu bytes"), (unsigned long) size);
}





/*******************************************************************************
*
*  error_empty_docinfo():
*     program error message: empty docinfo
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_empty_docinfo(void)
{
	error_message(_("empty !docinfo"));
}





/*******************************************************************************
*
*  error_syntax_error():
*     grobe Syntaxfehler
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_syntax_error(void)
{
	error_message(_("syntax error"));
}





/*******************************************************************************
*
*  error_end_without_begin():
*     throw error message about !end_xxx without !begin_xxx
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_end_without_begin(const char *se, const char *sb)
{
	error_message(_("'%s' without '%s'"), se, sb);
}





/*******************************************************************************
*
*  error_item_many_enum():
*     error message: too many items inside enumeration
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_item_many_enum(void)
{
	error_message(_("too many items inside enumeration"));
}





/*******************************************************************************
*
*  error_missing_end():
*     error message: '%s' expected
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_missing_end(const char *s)
{
	error_message(_("'%s' expected"), s);
}





/*******************************************************************************
*
*  error_called_twice():
*     error message: '%s' called twice
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_called_twice(const char *s)
{
	error_message(_("'%s' called twice"), s);
}





/*******************************************************************************
*
*  error_not_active():
*     error message: %s not active
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_not_active(const char *s)
{
	error_message(_("%s not active"), s);
}





/*******************************************************************************
*
*  error_already_active():
*     error message: %s already active
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_already_active(const char *s)
{
	error_message(_("%s already active"), s);
}





/*******************************************************************************
*
*  error_still_active():
*     error message: %s still active
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_still_active(const char *s)
{
	error_message(_("%s still active"), s);
}





/*******************************************************************************
*
*  error_missing_parameter():
*     error message: missing parameter(s) at %s
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_missing_parameter(const char *s)
{
	error_message(_("missing parameter(s) at %s"), s);
}




/*******************************************************************************
*
*  error_wrong_nr_parameters():
*     error message: wrong number of parameters
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_wrong_nr_parameters(const char *s)
{
	error_message(_("wrong number of parameters: %s"), s);
}





/*******************************************************************************
*
*  error_unexpected_eol():
*     error message: unexpected end of line in command
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_unexpected_eol(void)
{
	error_message(_("unexpected end of line in command"));
}





/*******************************************************************************
*
*  error_too_many_tokens():
*     error message: too many words used inside paragraph
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_tokens(void)
{
	error_message(_("too many words used inside paragraph"));
}





/*******************************************************************************
*
*  error_replace_param():
*     error message: couldn't replace (%s ...)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_replace_param(const char *s)
{
	error_message(_("couldn't replace (%s ...)"), s);
}





/*******************************************************************************
*
*  error_undefined_link():
*     error message: link destination undefined: %s
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_undefined_link(const char *l)
{
	if (bInsideDocument)
	{
		error_message(_("link destination undefined: '%s'"), l);
	}
}





/*******************************************************************************
*
*  error_missing_endif():
*     error message: '!endif' expected
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_missing_endif(const char *s, FILE_LINENO l)
{
	error_missing_end("!endif");
	note_message(_("last '!if': <%s> line %lu"), s, l);
}





/*******************************************************************************
*
*  error_no_charset():
*     error message: charset/encoding %s not supported
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_no_charset(const char *s)
{
	error_message(_("charset/encoding %s not supported"), s);
}





/*******************************************************************************
*
*  error_node_not_allowed():
*     error message: use !node first (structure gap) or use !begin_node & !end_node
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_node_not_allowed(int level)
{
	char sub[TOC_MAXDEPTH * 3 + 1];
	int i;

	*sub = '\0';
	for (i = 0; i < level; i++)
		strcat(sub, "sub");
	fatal_message(_("use !%snode first (structure gap)"), sub);
}





/*******************************************************************************
*
*  warning_long_destline():
*     warning message: overfull line
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL _BOOL warning_long_destline(const char *s, FILE_LINENO lnr, const int ll)
{
	char *m;

	if (!bNoWarningsLines)
	{
		warning_counter++;
		if (!bNoWarnings)
		{
			m = um_strdup_printf(_("Warning: %s %lu: overfull line: %d"), s, lnr, ll);
			logln(m);
			show_logln_message(m);
			free(m);
			return TRUE;
		}
	}
	return FALSE;
}





/*******************************************************************************
*
*  note_short_sourceline():
*     note message: check this paragraph (line too short)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void note_short_sourceline(const char *s)
{
	if (!bNoWarnings && !bNoWarningsLines)
		note_message(_("check this paragraph: %s"), s);
	else
		note_counter++;
}





/*******************************************************************************
*
*  warning_short_destline():
*     warning message: too short line
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL _BOOL warning_short_destline(const char *s, FILE_LINENO lnr, const int ll, const char *w)
{
	char *m;

	if (!bNoWarningsLines)
	{
		warning_counter++;
		if (!bNoWarnings)
		{
			m = um_strdup_printf(_("Warning: %s %lu: too short line: %d: %s"), s, lnr, ll, w);
			logln(m);
			show_logln_message(m);
			free(m);
			return TRUE;
		}
	}
	return FALSE;
}





/*******************************************************************************
*
*  warning_cannot_recode():
*     warning message: too short line
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void warning_cannot_recode(unsigned int c, const char *se, const char *te)
{
	if (iUdopass == PASS2)
	{
		warning_message(_("cannot convert %s #0x%x to %s"), se, c, te);
	}
}





/*******************************************************************************
*
*  warning_cannot_recode_utf8():
*     warning message: can't recode UTF-8 (%s) to %s
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void warning_cannot_recode_utf8(const char *utf, const char *te)
{
	if (iUdopass == PASS2)
	{
		warning_message(_("can't convert UTF-8 (%s) to %s"), utf, te);
	}
}





/*******************************************************************************
*
*  warning_no_isochar():
*     warning message: %s not available in ISO Latin 1
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void warning_no_isochar(const char c)
{
	warning_message(_("%x not available in ISO Latin 1"), (_UBYTE) c);
}





/*******************************************************************************
*
*  warning_node_too_deep():
*     warning message: structure depth exceeded, using subsubsubsubnode
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void warning_node_too_deep(_BOOL popup, _BOOL invisible)
{
	char n[100 + TOC_MAXDEPTH * 3];
	int i;

	strcpy(n, "!");
	if (popup)
		strcat(n, "p");
	for (i = 0; i < TOC_MAXDEPTH - 1; i++)
		strcat(n, "sub");
	strcat(n, "node");
	if (invisible)
		strcat(n, "*");
	warning_message(_("structure depth exceeded, using %s"), n);
}





GLOBAL void warning_buffer_overrun(const char *func, const char *place, size_t n, size_t maxlen)
{
	warning_message(_("%s: buffer overrun prevented: %s: %u>%u"), func, place, (unsigned int) (n + 1),
					(unsigned int) (maxlen));
}

/*******************************************************************************
*
*  get_warning_counter():
*     get # of warnings
*
*  return:
*     # of warnings
*
******************************************|************************************/

GLOBAL int get_warning_counter(void)
{
	return warning_counter;
}





/*******************************************************************************
*
*  get_note_counter():
*     get # of notes
*
*  return:
*     # of notes
*
******************************************|************************************/

GLOBAL int get_note_counter(void)
{
	return note_counter;
}





/*******************************************************************************
*
*  get_error_counter():
*     get # of errors
*
*  return:
*     # of errors
*
******************************************|************************************/

GLOBAL int get_error_counter(void)
{
	return error_counter;
}





/*******************************************************************************
*
*  init_module_msg():
*     initialize variables in MSG.C module
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_msg(void)
{
	error_counter = 0;
	warning_counter = 0;
	note_counter = 0;
}
