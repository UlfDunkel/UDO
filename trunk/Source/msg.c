/*	######################################################################
	# @(#) msg.c
	# @(#)
	# @(#) Copyright (c) 1995-2001 by Dirk Hagedorn
	# @(#) Dirk Hagedorn (udo@dirk-hagedorn.de)
	#
	# This program is free software; you can redistribute it and/or
	# modify it under the terms of the GNU General Public License
	# as published by the Free Software Foundation; either version 2
	# of the License, or (at your option) any later version.
	# 
	# This program is distributed in the hope that it will be useful,
	# but WITHOUT ANY WARRANTY; without even the implied warranty of
	# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	# GNU General Public License for more details.
	# 
	# You should have received a copy of the GNU General Public License
	# along with this program; if not, write to the Free Software
	# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
	######################################################################	*/

#ifndef ID_MSG_C
#define ID_MSG_C
const char *id_msg_c= "@(#) msg.c       01.01.1999";
#endif

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include "portab.h"
#include "constant.h"
#include "version.h"
#include "udo_type.h"
#include "udo.h"
#include "toc.h"
#include "gui.h"

#include "export.h"
#include "msg.h"


/*	######################################################################
	# lokale Variablen
	######################################################################	*/
LOCAL int error_counter;
LOCAL int warning_counter;
LOCAL int note_counter;


/*	######################################################################
	# lokale Prototypen
	######################################################################	*/
LOCAL void loglnpos ( const char *we, const char *msg );
LOCAL void warnlnpos ( const char *msg );
LOCAL void errlnpos ( const char *msg );
LOCAL void fatallnpos ( const char *msg );

LOCAL void error_msg_solo ( const char *em );
LOCAL void error_msg_para ( const char *f, const char *s );
LOCAL void error_msg_para2 ( const char *f, const char *s1, const char *s2 );

LOCAL char * my_strerror ( char *s );
LOCAL void errno_logln ( const char *s );

LOCAL void warning_msg_solo ( const char *em );
LOCAL void warning_msg_para ( const char *f, const char *s );

LOCAL void note_msg_solo ( const char *em );
LOCAL void note_msg_para ( const char *f, const char *s );

LOCAL void fatal_msg_solo ( const char *s );
LOCAL void fatal_msg_para ( const char *f, const char *s );


/*	######################################################################
	# Ausgabe von Strings in die passenden Dateien
	######################################################################	*/
/*	----------------------------------------------------------------------
	Ausgabe einer Zeile ins Logfile inkl. Zeilenvorschub
	----------------------------------------------------------------------	*/
GLOBAL void logln ( const char *s )
{
	if (bBeQuiet && bNoLogfile)
	{	return;
	}
	if (bNoLogfile && no_stderr_output)
	{	return;
	}
	fprintf(fLogfile, "%s\n", s);
}	/* logln */


/*	----------------------------------------------------------------------
	Ausgabe ins Logfile inklusive Datei und Zeilennummer
	----------------------------------------------------------------------	*/
LOCAL void loglnpos ( const char *we, const char *msg )
{
	char z[512];
	
	sprintf(z, "%s: %s %u: %s",
		we,
		sCurrFileName,
		uiCurrFileLine,
		msg
	);
	logln(z);

	show_logln_message(z);	/* r6pl12: Ausgabe ans GUI weiterreichen */
	
}	/* loglnpos */


LOCAL void warnlnpos ( const char *msg )
{
	if (!bNoWarnings)
	{	loglnpos("Warning", msg);
	}
}	/* warnlnpos */

LOCAL void errlnpos ( const char *msg )
{
	loglnpos("Error", msg);
}	/* errlnpos */


LOCAL void fatallnpos ( const char *msg )
{
	loglnpos("Fatal Error", msg);
}	/* fatallnpos */

LOCAL void notelnpos ( const char *msg )
{
	if (!bNoWarnings)
	{	loglnpos("Note", msg);
	}
}	/* notelnpos */


/*	----------------------------------------------------------------------
	Ausgabe einer Zeile ins Logfile inkl. Zeilenvorschub mit Variablen
	----------------------------------------------------------------------	*/
GLOBAL void vloglnf ( const char *fmt, ... )
{
	va_list ap;
	char s[1024];

	s[0]= EOS;
	va_start(ap, fmt);
	vsprintf(s, fmt, ap);
	va_end(ap);
	logln(s);
		
}	/* vloglnf */



/*	######################################################################
	# lokale Funktionen
	######################################################################	*/
LOCAL void error_msg_solo ( const char *em )
{
	errlnpos(em);
	error_counter++;
}

LOCAL void error_msg_para ( const char *f, const char *s )
{
	char m[512];

	sprintf(m, f, s);
	errlnpos(m);
	error_counter++;
}

LOCAL void error_msg_para2 ( const char *f, const char *s1, const char *s2 )
{
	char m[512];

	sprintf(m, f, s1, s2);
	errlnpos(m);
	error_counter++;
}

GLOBAL void error_message ( const char *msg )
{
	char s[512];

	sprintf(s, "Error: %s", msg);
	logln(s);
	error_counter++;
}

/* Fehlermeldung abhaengig von errno ausgeben, zumeist nach */
/* fehlgeschlagenem Oeffnen von Dateien. 					*/

/* Falls der Compiler strerror nicht anbietet, dann		*/
/* in version.h #define HAVE_STRERROR 0 setzen!			*/

/* Falls der Compiler sys_errlist nicht anbietet, dann		*/
/* in version.h #define HAVE_SYS_ERRLIST 0 setzen!			*/

LOCAL char * my_strerror ( char *s )
{
#if HAVE_STRERROR
	strcpy(s, strerror(errno));
#elif HAVE_SYS_ERRLIST
	strcpy(s, sys_errlist[errno]);
#else
	sprintf(s, "Error #%d", errno);
#endif

	return s;
}	/* my_strerror */


LOCAL void errno_logln ( const char *s )
{
	char p[512];

	my_strerror(p);
	
	if (s[0]!=EOS)
	{	vloglnf("%s: %s", s, p);
	}
	else
	{	vloglnf("%s", p);
	}

}	/* errno_logln */


LOCAL void warning_msg_solo ( const char *em )
{
	warnlnpos(em);
	warning_counter++;
}

LOCAL void warning_msg_para ( const char *f, const char *s )
{
	char m[512];

	sprintf(m, f, s);
	warnlnpos(m);
	warning_counter++;
}


GLOBAL void warning_message ( const char *msg )
{
	char s[512];

	sprintf(s, "Warning: %s", msg);
	logln(s);
	warning_counter++;
}

LOCAL void note_msg_solo ( const char *em )
{
	notelnpos(em);
	note_counter++;
}

LOCAL void note_msg_para ( const char *f, const char *s )
{
	char m[512];

	sprintf(m, f, s);
	notelnpos(m);
	note_counter++;
}

GLOBAL void note_message ( const char *msg )
{
	char s[512];

	sprintf(s, "Note: %s", msg);
	logln(s);
	note_counter++;
}

LOCAL void fatal_msg_solo ( const char *s )
{
	fatallnpos(s);
	error_counter++;
	bFatalErrorDetected= TRUE;
}

LOCAL void fatal_msg_para ( const char *f, const char *s )
{
	char m[512];

	sprintf(m, f, s);
	fatallnpos(m);
	error_counter++;
	bFatalErrorDetected= TRUE;
}

GLOBAL void fatal_message ( const char *msg )
{
	char s[512];

	sprintf(s, "Fatal Error: %s", msg);
	logln(s);
	error_counter++;
	bFatalErrorDetected= TRUE;
}	/* fatal_message */


/*	######################################################################
	# Informationen, die ins Logfile geschrieben werden
	######################################################################	*/
GLOBAL void logln_warnings_errors ( void )
{	logln("######## errors, warnings and notes:");
	logln("");
}

GLOBAL void logln_information ( void )
{
	logln("");
	logln("######## information:");
	logln("");
}

GLOBAL void logln_interrupted ( void )
{
	logln("interruption");
}

GLOBAL void logln_file_generated ( const char *kind, const char *filename )
{
	char m[512];

	sprintf(m, "%s written to %s", kind, filename);
	logln(m);
}


/*	######################################################################
	# Programm-Fehlermeldungen
	######################################################################	*/
GLOBAL void error_open_logfile ( const char *s )
{	error_msg_para("couldn't open logfile <%s>", s);
	errno_logln(s);
}

GLOBAL void error_open_hypfile ( const char *s )
{	error_msg_para("couldn't open hypfile <%s>", s);
	errno_logln(s);
}

GLOBAL void error_open_idxfile ( const char *s )
{	error_msg_para("couldn't open index file <%s>", s);
	errno_logln(s);
}

GLOBAL void error_open_treefile ( const char *s )
{	error_msg_para("couldn't open treefile <%s>", s);
	errno_logln(s);
}

GLOBAL void error_open_uprfile ( const char *s )
{	error_msg_para("couldn't open project file <%s>", s);
	errno_logln(s);
}

GLOBAL void error_open_outfile ( const char *s )
{	error_msg_para("couldn't open destination file <%s>", s);
	errno_logln(s);
}

GLOBAL void error_open_infile ( const char *s )
{	error_msg_para("couldn't open source file <%s>", s);
	errno_logln(s);
}

GLOBAL void error_infile_outfile ( const char *s )
{	error_msg_para("source and destination file are equal: <%s>", s);
}

GLOBAL void error_write_img ( const char *s )
{	error_msg_para("couldn't write IMG header of <%s>", s);
	errno_logln(s);
}

GLOBAL void error_read_img ( const char *s )
{	error_msg_para("couldn't read IMG header of <%s>", s);
	errno_logln(s);
}

GLOBAL void error_read_bmp ( const char *s )
{	error_msg_para("couldn't read BMP header of <%s>", s);
	errno_logln(s);
}

GLOBAL void error_read_pcx ( const char *s )
{	error_msg_para("couldn't read PCX header of <%s>", s);
	errno_logln(s);
}

GLOBAL void error_read_msp ( const char *s )
{	error_msg_para("couldn't read MSP header of <%s>", s);
	errno_logln(s);
}

GLOBAL void error_read_gif ( const char *s )
{	error_msg_para("couldn't read GIF header of <%s>", s);
	errno_logln(s);
}

GLOBAL void error_read_png ( const char *s )
{	error_msg_para("couldn't read PNG header of <%s>", s);
	errno_logln(s);
}

GLOBAL void error_read_jpeg ( const char *s )
{	error_msg_para("couldn't read JPEG header of <%s>", s);
	errno_logln(s);
}

GLOBAL void error_open_pass1 ( const char *s )
{
	char e[512];
	
	my_strerror(e);
	error_msg_para2("couldn't open <%s>: %s", s, e);
}

GLOBAL void error_open_pass2 ( const char *s )
{
	char e[512];
	
	my_strerror(e);
	error_msg_para2("couldn't open <%s>: %s", s, e);
}

GLOBAL void error_mkdir ( const char *s )
{
	char e[512];
	
	my_strerror(e);
	error_msg_para2("couldn't make directory <%s>: %s", s, e);
}


GLOBAL void error_malloc_failed ( void )
{	error_msg_solo("memory allocation failed");
}

GLOBAL void error_buffer_overflow ( void )
{	error_msg_solo("string buffer overflow");
}

GLOBAL void error_missing_title_data ( void )
{	error_msg_solo("no title data available");
}

GLOBAL void error_empty_docinfo ( void )
{	error_msg_solo("empty !docinfo");
}

GLOBAL void error_unknown_docinfo ( const char *s )
{	error_msg_para("unknown docinfo: %s", s);
}

GLOBAL void error_unknown_color ( const char *s )
{	error_msg_para("unknown color: %s", s);
}

GLOBAL void error_error ( const char *s )	/*r6pl4*/
{	error_msg_solo(s);
}


/*	######################################################################
	# grobe Syntaxfehler
	######################################################################	*/
GLOBAL void error_syntax_error ( void )
{	error_msg_solo("syntax error");
}

GLOBAL void error_end_without_begin ( const char *se, const char *sb )
{
	char m[512];
	sprintf(m, "'%s' without '%s'", se, sb);
	errlnpos(m);
	error_counter++;
}

GLOBAL void error_wrong_end ( const char *sb, const char *se )
{
	char m[512];
	sprintf(m, "'%s' followed by '%s'", sb, se);
	errlnpos(m);
	error_counter++;
}

GLOBAL void error_item_outside_env ( void )
{	error_msg_solo("'!item' outside environment");
}

GLOBAL void error_item_many_enum ( void )
{	error_msg_solo("too many items inside enumeration");
}

GLOBAL void error_missing_end ( const char *s )
{	error_msg_para("'%s' expected", s);
}

GLOBAL void error_called_twice ( const char *s )
{	error_msg_para("'%s' called twice", s);
}

GLOBAL void error_too_many_env ( void )
{	error_msg_solo("too many environments used");
}

GLOBAL void error_not_active ( const char *s )
{	error_msg_para("%s not active", s);
}

GLOBAL void error_still_active ( const char *s )
{	error_msg_para("%s still active", s);
}

GLOBAL void error_missing_parameter ( const char *s )
{	error_msg_para("missing parameter(s) at %s", s);
}

GLOBAL void error_too_many_parameters ( void )
{	error_msg_solo("too many parameters used");
}

GLOBAL void error_wrong_nr_parameters ( const char *s )
{	error_msg_para("wrong number of parameters: %s", s);
}

GLOBAL void error_outside_preamble ( const char *s )
{	error_msg_para("%s ignored outside preamble", s);
}

GLOBAL void error_inside_preamble ( const char *s )
{	error_msg_para("%s ignored inside preamble", s);
}

GLOBAL void error_unknown_command ( const char *s )
{	error_msg_para("unknown command: %s", s);
}

GLOBAL void error_unexpected_eol ( void )
{	error_msg_solo("unexpected end of line in command");
}

GLOBAL void error_too_many_macros ( void )
{	error_msg_solo("too many macros used");
}

GLOBAL void error_long_macro_name ( int len )
{
	char s[32];
	sprintf(s, "%d", len);
	error_msg_para("macro name longer than %s characters", s);
}

GLOBAL void error_long_macro_cont ( int len )
{
	char s[32];
	sprintf(s, "%d", len);
	error_msg_para("macro contents longer than %s characters", s);
}

GLOBAL void error_too_many_defines ( void )
{	error_msg_solo("too many definitions used");
}

GLOBAL void error_long_define_name ( int len )
{
	char s[32];
	sprintf(s, "%d", len);
	error_msg_para("definition name longer than %s characters", s);
}

GLOBAL void error_long_define_cont ( int len )
{
	char s[32];
	sprintf(s, "%d", len);
	error_msg_para("definition contents longer than %s characters", s);
}

GLOBAL void error_too_many_symbols ( void )
{	error_msg_solo("too many symbols used");
}

GLOBAL void error_unset_symbol ( const char *s )
{	error_msg_para("symbol %s not set", s);
}

GLOBAL void error_too_many_hyphens ( void )
{	error_msg_solo("too many hyphens used");
}

GLOBAL void error_too_many_tokens ( void )
{	error_msg_solo("too many words used inside paragraph");
}

GLOBAL void error_too_many_node ( void )
{	error_msg_solo("too many nodes used");
}

GLOBAL void error_too_many_label ( void )
{	error_msg_solo("too many labels used");
}

GLOBAL void error_too_many_alias ( void )
{	error_msg_solo("too many aliases used");
}

GLOBAL void error_too_many_files ( void )
{	error_msg_solo("too many files opened");
}

GLOBAL void error_replace_param ( const char *s )
{	error_msg_para("couldn't replace (%s ...)", s);
}

GLOBAL void error_undefined_link ( const char *l )
{	
	if (bInsideDocument)
	{	error_msg_para("link destination undefined: %s", l);
	}
}

GLOBAL void error_else_without_if ( void )
{	error_msg_solo("!else without !if...");
}

GLOBAL void error_endif_without_if ( void )
{	error_msg_solo("!endif without !if...");
}

GLOBAL void error_missing_endif ( const char *s, const UINT l )
{	char m[512];
	error_msg_solo("'!endif' expected");
	sprintf(m, "last '!if': <%s> line %d", s, l);
	error_msg_solo(m);
}


GLOBAL void error_table_width ( void )
{	error_msg_solo("too many columns used");
}

GLOBAL void error_table_height ( void )
{	error_msg_solo("too many rows used");
}

GLOBAL void error_table_cell_width ( void )
{	error_msg_solo("table cell contains too many characters");
}

GLOBAL void error_odd_dblquotes ( void )
{	error_msg_solo("odd number of \"\"");
}

GLOBAL void error_odd_quotes ( void )
{	error_msg_solo("odd number of ''");
}

GLOBAL void error_no_language ( const char *s )
{	error_msg_para ("language %s not supported", s);
}

GLOBAL void error_no_charset ( const char *s )
{	error_msg_para ("charset %s not supported", s);
}

GLOBAL void error_xlink_win_syntax ( void )
{	error_msg_solo("use (!xlink [text] [topic@foo.hlp])");
}

GLOBAL void error_xlink_win_topic ( void )
{	error_msg_solo("xlink needs WinHelp destination topic");
}

GLOBAL void error_xlink_win_file ( void )
{	error_msg_solo("xlinks needs WinHelp destination file");
}

GLOBAL void error_no_udoinputpath ( void )
{	error_msg_solo("$UDOINPUTPATH not set!");
}

GLOBAL void error_fatal_error ( const char *s )
{	fatal_msg_para("%s", s);
}

GLOBAL void error_table_inside_table ( void )
{	error_msg_solo("UDO cannot handle nested tables");
}

GLOBAL void error_wrong_mapping ( void )
{	error_msg_solo("mapping not numeric or not of type integer");
}

GLOBAL void error_node2_not_allowed ( void )
{	fatal_msg_solo("use !node first (structure gap)");
}

GLOBAL void error_node3_not_allowed ( void )
{	fatal_msg_solo("use !subnode first(structure gap)");
}

GLOBAL void error_node4_not_allowed ( void )
{	fatal_msg_solo("use !subsubnode first (structure gap)");
}

/*	######################################################################
	# Warnmeldungen (leichte Syntaxfehler)
	######################################################################	*/

GLOBAL void note_long_sourceline ( void )
{	note_msg_solo("check this paragraph");
}

GLOBAL void warning_long_destline ( const char *s,
	const unsigned int lnr,
	const int ll)
{
	char m[512];

	if (!bNoWarnings)
	{	sprintf(m, "Warning: %s %u: overfull line: %d", s, lnr, ll);
		logln(m);
	}
	warning_counter++;
}


GLOBAL void note_short_sourceline ( const char *s )
{	note_msg_para("check this paragraph", s);
}

GLOBAL void warning_short_destline ( const char *s,
	const unsigned int lnr,
	const int ll,
	const char *w)
{
	char m[512];

	if (!bNoWarnings)
	{	sprintf(m, "Warning: %s %u: underfull line: %d: %s", s, lnr, ll, w);
		logln(m);
	}
	warning_counter++;
}

GLOBAL void warning_no_unichar ( const char *s )
{
	warning_msg_para("%s not available in this charset", s);
}

GLOBAL void warning_cannot_recode ( const char c, const char *scs, const char *dcs )
{	/* scs = source char set */
	/* dcs = dest char set */
	char s[512];

	if (iUdopass==PASS2)	
	{	sprintf(s, "cannot convert %c (%s #%u) to %s", c, scs, ((unsigned char) c), dcs);
		warning_msg_solo(s);
	}
}

GLOBAL void warning_cannot_recode_utf8 ( const char *utf, const char *dcs )
{	/* utf = UTF-8 Characters (e.g. 0xC0 0x85) */
	/* dcs = dest char set */
	char s[512];

	if (iUdopass==PASS2)	
	{	sprintf(s, "can't convert UTF-8 (%s) to %s", utf, dcs);
		warning_msg_solo(s);
	}
}

GLOBAL void warning_no_isochar ( const char c )
{
	char s[2];

	sprintf(s, "%c", c);
	warning_msg_para("%s not available in ISO Latin 1", s);
}

GLOBAL void warning_no_texchar ( const char c )
{
	char s[2];

	sprintf(s, "%c", c);
	warning_msg_para("%s maybe not available in LaTeX", s);
}

GLOBAL void warning_split_verb ( void )
{
	warning_msg_solo("please use (!V) and (!v) in one paragraph");
}

GLOBAL void warning_node_too_deep ( void )
{
	warning_msg_solo("structure depth exceeded, using subsubsubnode");
}


/*	######################################################################
	# Abfrageroutinen fuer andere Routinen
	######################################################################	*/
GLOBAL int get_warning_counter ( void )
{	return(warning_counter);
}

GLOBAL int get_note_counter ( void )
{	return(note_counter);
}

GLOBAL int get_error_counter ( void )
{	return(error_counter);
}


/*	######################################################################
	# Modulinit
	######################################################################	*/
GLOBAL void init_module_msg ( void )
{
	error_counter= 0;
	warning_counter= 0;
	note_counter= 0;
}	/* init_module_msg */

/*	######################################################################
	# msg.c
	######################################################################	*/

