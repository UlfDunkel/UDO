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
*     CONSTANTS
*
******************************************|************************************/

#ifndef ID_MSG_C
#define ID_MSG_C
const char *id_msg_c= "@(#) msg.c       $Date$";
#endif





/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include "udoport.h"
#include "constant.h"
#include "version.h"
#include "udo_type.h"
#include "udo.h"
#include "toc.h"
#include "gui.h"

#include "export.h"
#include "msg.h"





/*******************************************************************************
*
*     LOCAL VARIABLES
*
******************************************|************************************/

LOCAL int   error_counter;                /* */
LOCAL int   warning_counter;              /* */
LOCAL int   note_counter;                 /* */





/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

LOCAL void loglnpos(const char *we, const char *msg);
LOCAL void warnlnpos(const char *msg);
LOCAL void errlnpos(const char *msg);
LOCAL void fatallnpos(const char *msg);

LOCAL void error_msg_para2(const char *f, const char *s1, const char *s2);

LOCAL char *my_strerror(char *s);
LOCAL void errno_logln(const char *s);











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

LOCAL void loglnpos(

const char  *we,             /* */
const char  *msg)            /* */
{
   char      z[512];         /* */
   char      lineinfo[100];  /* */
   _UWORD     realstart;      /* */
   
   if (uiMultiLines > 0)                  /* New in v6.5.5 to get a proper message with multilines */
   {
                                          /* Special: we are on a multiline */
      realstart = uiCurrFileLine - uiMultiLines;
      sprintf(lineinfo, "%u-%u", realstart, uiCurrFileLine);
   }
   else
   {
      sprintf(lineinfo, "%u", uiCurrFileLine);
   }
   
   sprintf(z, "%s: %s %s: %s", we, sCurrFileName, lineinfo, msg);
   logln(z);

   show_logln_message(z);                 /* Ausgabe ans GUI weiterreichen */
}





/*******************************************************************************
*
*  warnlnpos():
*     output a warning message with file name and line position
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void warnlnpos(

const char  *msg)  /* */
{
   if (!bNoWarnings)
      loglnpos("Warning", msg);
}





/*******************************************************************************
*
*  errlnpos():
*     output an error message with file name and line position
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void errlnpos(

const char  *msg)  /* */
{
   loglnpos("Error", msg);
}





/*******************************************************************************
*
*  fatallnpos():
*     output a fatal error message with file name and line position
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void fatallnpos(

const char  *msg)  /* */
{
   loglnpos("Fatal Error", msg);
}





/*******************************************************************************
*
*  notelnpos():
*     output a note message with file name and line position
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void notelnpos(

const char  *msg)  /* */
{
   if (!bNoWarnings)
      loglnpos("Note", msg);
}





/*******************************************************************************
*
*  error_msg_para2():
*     ?? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void error_msg_para2(

const char  *f,       /* */
const char  *s1,      /* */
const char  *s2)      /* */
{
   char      m[512];  /* */
   

   sprintf(m, f, s1, s2);
   errlnpos(m);
   error_counter++;
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

LOCAL char *my_strerror(

char  *s)  /* */
{
#if HAVE_STRERROR
   strcpy(s, strerror(errno));
#elif HAVE_SYS_ERRLIST
   strcpy(s, sys_errlist[errno]);
#else
   sprintf(s, "Error #%d", errno);
#endif

   return s;
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

LOCAL void errno_logln(

const char  *s)       /* */
{
   char      p[512];  /* */


   my_strerror(p);
   
   if (s[0] != EOS)
      vloglnf("%s: %s", s, p);
   else
      vloglnf("%s", p);
}










/*******************************************************************************
*
*     GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  fatal_msg_solo():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void fatal_msg_solo(

const char  *s)  /* */
{
   fatallnpos(s);
   error_counter++;
   bFatalErrorDetected = TRUE;
}





/*******************************************************************************
*
*  fatal_msg_para():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void fatal_msg_para(

const char  *f,       /* */
const char  *s)       /* */
{
   char      m[512];  /* */


   sprintf(m, f, s);
   fatallnpos(m);
   error_counter++;
   bFatalErrorDetected = TRUE;
}





/*******************************************************************************
*
*  error_msg_solo():
*     ?? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_msg_solo(

const char  *em)  /* */
{
   errlnpos(em);
   error_counter++;
}





/*******************************************************************************
*
*  error_msg_para():
*     ?? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_msg_para(

const char  *f,       /* */
const char  *s)       /* */
{
   char      m[512];  /* */


   sprintf(m, f, s);
   errlnpos(m);
   error_counter++;
}





/*******************************************************************************
*
*  warning_msg_solo():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_msg_solo(

const char  *em)  /* */
{
   warnlnpos(em);
   warning_counter++;
}





/*******************************************************************************
*
*  warning_msg_para():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_msg_para(

const char  *f,       /* */
const char  *s)       /* */
{
   char      m[512];  /* */
   

   sprintf(m, f, s);
   warnlnpos(m);
   warning_counter++;
}





/*******************************************************************************
*
*  note_msg_solo():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void note_msg_solo(

const char  *em)  /* */
{
   notelnpos(em);
   note_counter++;
}





/*******************************************************************************
*
*  note_msg_para():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void note_msg_para(

const char  *f,       /* */
const char  *s)       /* */
{
   char      m[512];  /* */


   sprintf(m, f, s);
   notelnpos(m);
   note_counter++;
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

GLOBAL void logln(

const char  *s)  /* log file entry line */
{
   if (bBeQuiet && bNoLogfile)
      return;
   
   if (bNoLogfile && no_stderr_output)
      return;
   
   fprintf(fLogfile, "%s\n", s);
}





/*******************************************************************************
*
*  loglnposprintf():
*     Ausgabe ins Logfile und via printf inklusive Datei und Zeilennummer
*
*  Notes:
*     [vj] v6.3.7 hinzugefuegt zu debuggingzwecken
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void loglnposprintf(

const char  *we,             /* */
const char  *msg)            /* */
{
   char      z[512];         /* */
   char      lineinfo[100];  /* */
   _UWORD     realstart;      /* */
   
   
   if (uiMultiLines > 0)                  /* New in v6.5.5 to get a proper message with multilines */
   {
                                          /* Special: we are on a multiline */
      realstart = uiCurrFileLine - uiMultiLines;
      
      sprintf(lineinfo, "%u-%u", realstart, uiCurrFileLine);
   }
   else
   {
      sprintf(lineinfo, "%u", uiCurrFileLine);
   }
   
   sprintf(z, "%s: %s %s: %s", we, sCurrFileName, lineinfo, msg);
   logln(z);

#ifdef USE_LOGLNPOSPRINTF
   printf("%s\n", z);
#else
   show_logln_message(z);                 /* r6pl12: Ausgabe ans GUI weiterreichen */
#endif
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

GLOBAL void vloglnf(

const char  *fmt,      /* format string */
             ...)      /* more parameters */
{
   va_list   ap;       /* */
   char      s[1024];  /* line output buffer */


   s[0] = EOS;                            /* clear buffer */
   
   va_start(ap, fmt);
   vsprintf(s, fmt, ap);
   va_end(ap);
   
   logln(s);
}





/*******************************************************************************
*
*  error_message():
*     ?? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_message(

const char  *msg)     /* */
{
   char      s[512];  /* */


   sprintf(s, "Error: %s", msg);
   logln(s);
   error_counter++;
}





/*******************************************************************************
*
*  warning_message():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_message(

const char  *msg)     /* */
{
   char      s[512];  /* */
   

   sprintf(s, "Warning: %s", msg);
   logln(s);
   warning_counter++;
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

GLOBAL void note_message(

const char  *msg)     /* */
{
   char      s[512];  /* */
   

   sprintf(s, "Note: %s", msg);
   logln(s);
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

GLOBAL void fatal_message(

const char  *msg)     /* */
{
   char      s[512];  /* */
   

   sprintf(s, "Fatal Error: %s", msg);
   logln(s);
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
   logln("######## errors, warnings and notes:");
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
   logln("######## information:");
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
   logln("interruption");
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

GLOBAL void logln_file_generated(

const char  *kind,      /* */
const char  *filename,  /* */
const char  *suff)      /* */
{
   char      m[512];    /* */
   

   sprintf(m, "%s written to %s%s", kind, filename, suff);
   logln(m);
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

GLOBAL void error_open_logfile(

const char  *s)  /* */
{
   error_msg_para("couldn't open logfile <%s>", s);
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

GLOBAL void error_open_hypfile(

const char  *s)  /* */
{
   error_msg_para("couldn't open hypfile <%s>", s);
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

GLOBAL void error_open_idxfile(

const char  *s)  /* */
{
   error_msg_para("couldn't open index file <%s>", s);
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

GLOBAL void error_open_treefile(

const char  *s)  /* */
{
   error_msg_para("couldn't open treefile <%s>", s);
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

GLOBAL void error_open_uprfile(

const char  *s)  /* */
{
   error_msg_para("couldn't open project file <%s>", s);
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

GLOBAL void error_open_outfile(

const char  *s)  /* */
{
   error_msg_para("couldn't open destination file <%s>", s);
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

GLOBAL void error_open_infile(

const char  *s)  /* */
{
   error_msg_para("couldn't open source file <%s>", s);
   errno_logln(s);
}





/*******************************************************************************
*
*  error_infile_outfile():
*     program error message: source and destination file are equal
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_infile_outfile(

const char  *s)  /* */
{
   error_msg_para("source and destination file are equal: <%s>", s);
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

GLOBAL void error_write_img(

const char  *s)  /* */
{
   error_msg_para("couldn't write IMG header of <%s>", s);
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

GLOBAL void error_read_img(

const char  *s)  /* */
{
   error_msg_para("couldn't read IMG header of <%s>", s);
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

GLOBAL void error_read_bmp(

const char  *s)  /* */
{
   if (strcmp(s, BMP_MW_NAME) == 0)       /* Fixed bug #0000017 in V6.5.2 [NHz] */
      note_msg_solo("Image for UDO link generated (see below), please translate again to complete");
   else
   {
      error_msg_para("couldn't read BMP header of <%s>", s);
      errno_logln(s);
   }
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

GLOBAL void error_read_pcx(

const char  *s)  /* */
{
   error_msg_para("couldn't read PCX header of <%s>", s);
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

GLOBAL void error_read_msp(

const char  *s)  /* */
{
   error_msg_para("couldn't read MSP header of <%s>", s);
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

GLOBAL void error_read_gif(

const char  *s)  /* */
{
   error_msg_para("couldn't read GIF header of <%s>", s);
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

GLOBAL void error_read_png(

const char  *s)  /* */
{
   error_msg_para("couldn't read PNG header of <%s>", s);
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

GLOBAL void error_read_jpeg(

const char  *s)  /* */
{
   error_msg_para("couldn't read JPEG header of <%s>", s);
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

GLOBAL void error_open_pass1(

const char  *s)       /* */
{
   char      e[512];  /* */
   
   
   my_strerror(e);
   error_msg_para2("couldn't open <%s>: %s", s, e);
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

GLOBAL void error_open_pass2(

const char  *s)       /* */
{
   char      e[512];  /* */
   
   
   my_strerror(e);
   error_msg_para2("couldn't open <%s>: %s", s, e);
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

GLOBAL void error_mkdir(

const char  *s)       /* */
{
   char      e[512];  /* */
   
   
   my_strerror(e);
   error_msg_para2("couldn't make directory <%s>: %s", s, e);
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

GLOBAL void error_malloc_failed(void)
{
   error_msg_solo("memory allocation failed");
}





/*******************************************************************************
*
*  error_buffer_overflow():
*     program error message: string buffer overflow
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_buffer_overflow(void)
{
   error_msg_solo("string buffer overflow");
}





/*******************************************************************************
*
*  error_missing_title_data():
*     program error message: no title data available
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_missing_title_data(void)
{
   error_msg_solo("no title data available");
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
   error_msg_solo("empty !docinfo");
}





/*******************************************************************************
*
*  error_unknown_docinfo():
*     program error message: unknown docinfo
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_unknown_docinfo(const char *s)
{
   error_msg_para("unknown !docinfo: %s", s);
}





/*******************************************************************************
*
*  error_unknown_html_navigation():
*     program error message: unknown html_navigation
*
*  Notes:
*     New V 6.5.20
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_unknown_html_navigation(

const char  *s)  /* */
{
   error_msg_para("unknown html_navigation: %s", s);
}





/*******************************************************************************
*
*  error_unknown_color():
*     program error message: unknown color
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_unknown_color(

const char  *s)  /* */
{
   error_msg_para("unknown color: %s", s);
}





/*******************************************************************************
*
*  error_wrong_header_date():
*     program error message: wrong argument for html_header_date
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_wrong_header_date(

const char  *s)  /* */
{
   error_msg_para("wrong argument for !html_header_date: %s, e.g. +01:00", s);
}





/*******************************************************************************
*
*  error_empty_header_links():
*     program error message: empty html_header_links
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_empty_header_links(void)
{
   error_msg_solo("empty !html_header_links");
}





/*******************************************************************************
*
*  error_argument_header_links():
*     program error message: unknown linktype (!html_header_links)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_argument_header_links(

const char  *s)  /* */
{
   error_msg_para("unknown linktype (!html_header_links): %s", s);
}





/*******************************************************************************
*
*  error_error():
*     ??? (desription missing)
*
*  Notes:
*     r6pl4
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void error_error(

const char  *s)  /* */
{
   error_msg_solo(s);
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
   error_msg_solo("syntax error");
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

GLOBAL void error_end_without_begin(

const char  *se,      /* */
const char  *sb)      /* */
{
   char      m[512];  /* */
   
   
   sprintf(m, "'%s' without '%s'", se, sb);
   errlnpos(m);
   error_counter++;
}





/*******************************************************************************
*
*  error_wrong_end():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_wrong_end(

const char  *sb,      /* */
const char  *se)      /* */
{
   char      m[512];  /* */
   
   
   sprintf(m, "'%s' followed by '%s'", sb, se);
   errlnpos(m);
   error_counter++;
}





/*******************************************************************************
*
*  error_item_outside_env():
*     error message: '!item' outside environment
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_item_outside_env(void)
{
   error_msg_solo("'!item' outside environment");
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
   error_msg_solo("too many items inside enumeration");
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

GLOBAL void error_missing_end(

const char  *s)  /* */
{
   error_msg_para("'%s' expected", s);
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

GLOBAL void error_called_twice(

const char  *s)  /* */
{
   error_msg_para("'%s' called twice", s);
}





/*******************************************************************************
*
*  error_too_many_env():
*     error message: too many environments used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_env(void)
{
   error_msg_solo("too many environments used");
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

GLOBAL void error_not_active(

const char  *s)  /* */
{
   error_msg_para("%s not active", s);
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

GLOBAL void error_still_active(

const char  *s)  /* */
{
   error_msg_para("%s still active", s);
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

GLOBAL void error_missing_parameter(

const char  *s)  /* */
{
   error_msg_para("missing parameter(s) at %s", s);
}




/*******************************************************************************
*
*  error_too_many_parameters():
*     error message: too many parameters used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_parameters(void)
{
   error_msg_solo("too many parameters used");
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

GLOBAL void error_wrong_nr_parameters(

const char  *s)  /* */
{
   error_msg_para("wrong number of parameters: %s", s);
}





/*******************************************************************************
*
*  error_outside_preamble():
*     error message: %s ignored outside preamble
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_outside_preamble(

const char  *s)  /* */
{
   error_msg_para("%s ignored outside preamble", s);
}





/*******************************************************************************
*
*  error_inside_preamble():
*     error message: %s ignored inside preamble
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_inside_preamble(

const char  *s)  /* */
{
   error_msg_para("%s ignored inside preamble", s);
}





/*******************************************************************************
*
*  error_unknown_command():
*     error message: unknown command: %s
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_unknown_command(

const char  *s)  /* */
{
   error_msg_para("unknown command: %s", s);
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
   error_msg_solo("unexpected end of line in command");
}





/*******************************************************************************
*
*  error_too_many_macros():
*     error message: too many macros used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_macros(void)
{
   error_msg_solo("too many macros used");
}





/*******************************************************************************
*
*  error_long_macro_name():
*     error message: macro name longer than %s characters
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_long_macro_name(

int       len)    /* */
{
   char   s[32];  /* */
   
   
   sprintf(s, "%d", len);
   error_msg_para("macro name longer than %s characters", s);
}





/*******************************************************************************
*
*  error_long_macro_cont():
*     error message: macro contents longer than %s characters
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_long_macro_cont(

int       len)    /* */
{
   char   s[32];  /* */
   
   
   sprintf(s, "%d", len);
   error_msg_para("macro contents longer than %s characters", s);
}





/*******************************************************************************
*
*  error_too_many_defines():
*     error message: too many definitions used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_defines(void)
{
   error_msg_solo("too many definitions used");
}





/*******************************************************************************
*
*  error_long_define_name():
*     error message: definition name longer than %s characters
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_long_define_name(

int       len)    /* */
{
   char   s[32];  /* */
   
   
   sprintf(s, "%d", len);
   error_msg_para("definition name longer than %s characters", s);
}





/*******************************************************************************
*
*  error_long_define_cont():
*     error message: definition contents longer than %s characters
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_long_define_cont(

int       len)    /* */
{
   char   s[32];  /* */
   
   
   sprintf(s, "%d", len);
   error_msg_para("definition contents longer than %s characters", s);
}





/*******************************************************************************
*
*  error_too_many_placeholder():
*     error message: too many placeholder used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_placeholder(void)
{
   error_msg_solo("too many placeholder used");
}





/*******************************************************************************
*
*  error_too_many_symbols():
*     error message: too many symbols used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_symbols(void)
{
   error_msg_solo("too many symbols used");
}





/*******************************************************************************
*
*  error_unset_symbol():
*     error message: symbol %s not set
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_unset_symbol(

const char  *s)  /* */
{
   error_msg_para("symbol %s not set", s);
}





/*******************************************************************************
*
*  error_too_many_hyphens():
*     error message: too many hyphens used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_hyphens(void)
{
   error_msg_solo("too many hyphens used");
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
   error_msg_solo("too many words used inside paragraph");
}





/*******************************************************************************
*
*  error_too_many_node():
*     error message: too many nodes used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_node(void)
{
   error_msg_solo("too many nodes used");
}





/*******************************************************************************
*
*  error_too_many_label():
*     error message: too many labels used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_label(void)
{
   error_msg_solo("too many labels used");
}





/*******************************************************************************
*
*  error_too_many_alias():
*     error message: too many aliases used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_alias(void)
{
   error_msg_solo("too many aliases used");
}





/*******************************************************************************
*
*  error_too_many_files():
*     error message: too many files opened
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_files(void)
{
   error_msg_solo("too many files opened");
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

GLOBAL void error_replace_param(

const char  *s)  /* */
{
   error_msg_para("couldn't replace (%s ...)", s);
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

GLOBAL void error_undefined_link(

const char  *l)  /* */
{   
   if (bInsideDocument)
   {
      error_msg_para("link destination undefined: %s", l);
   }
}





/*******************************************************************************
*
*  error_too_many_if():
*     error message: too many !if in: <%s> line %d
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_too_many_if(

const char   *s,       /* */
const _UWORD   l)       /* */
{
   char       m[512];  /* */
   
   
   sprintf(m, "too many !if in: <%s> line %d", s, l);
   error_msg_solo(m);
}





/*******************************************************************************
*
*  error_else_without_if():
*     error message: !else without !if...
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_else_without_if(void)
{
   error_msg_solo("!else without !if...");
}





/*******************************************************************************
*
*  error_endif_without_if():
*     error message: !endif without !if...
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_endif_without_if(void)
{
   error_msg_solo("!endif without !if...");
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

GLOBAL void error_missing_endif(

const char   *s,       /* */
const _UWORD   l)       /* */
{
   char       m[512];  /* */
   
   
   error_msg_solo("'!endif' expected");
   sprintf(m, "last '!if': <%s> line %d", s, l);
   error_msg_solo(m);
}





/*******************************************************************************
*
*  error_table_width():
*     error message: too many columns used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_table_width(void)
{
   error_msg_solo("too many columns used");
}





/*******************************************************************************
*
*  error_table_height():
*     error message: too many rows used
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_table_height(void)
{
   error_msg_solo("too many rows used");
}





/*******************************************************************************
*
*  error_table_cell_width():
*     error message: table cell contains too many characters
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_table_cell_width(void)
{
   error_msg_solo("table cell contains too many characters");
}





/*******************************************************************************
*
*  error_table_label():
*     error message: too many labels used in table
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_table_label(void)
{
   error_msg_solo("too many labels used in table");
}





/*******************************************************************************
*
*  error_odd_dblquotes():
*     error message: odd number of ""
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_odd_dblquotes(void)
{
   error_msg_solo("odd number of \"\"");
}





/*******************************************************************************
*
*  error_odd_quotes():
*     error message: odd number of ''
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_odd_quotes(void)
{
   error_msg_solo("odd number of ''");
}





/*******************************************************************************
*
*  error_no_language():
*     error message: language %s not supported
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_no_language(

const char  *s)  /* */
{
   error_msg_para("language %s not supported", s);
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

GLOBAL void error_no_charset(

const char  *s)  /* */
{
   error_msg_para("charset/encoding %s not supported", s);
}





/*******************************************************************************
*
*  error_xlink_win_syntax():
*     error message: use (!xlink [text] [topic@foo.hlp])
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_xlink_win_syntax(void)
{
   error_msg_solo("use (!xlink [text] [topic@foo.hlp])");
}





/*******************************************************************************
*
*  error_xlink_win_topic():
*     error message: xlink needs WinHelp destination topic
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_xlink_win_topic(void)
{
   error_msg_solo("xlink needs WinHelp destination topic");
}





/*******************************************************************************
*
*  error_xlink_win_file():
*     error message: xlinks needs WinHelp destination file
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_xlink_win_file(void)
{
   error_msg_solo("xlinks needs WinHelp destination file");
}





/*******************************************************************************
*
*  error_no_udoinputpath():
*     error message: $UDOINPUTPATH not set!
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_no_udoinputpath(void)
{
   error_msg_solo("$UDOINPUTPATH not set!");
}





/*******************************************************************************
*
*  error_fatal_error():
*     error message: fatal error
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_fatal_error(

const char  *s)  /* */
{
   fatal_msg_para("%s", s);
}





/*******************************************************************************
*
*  error_fatal_error():
*     error message: UDO cannot handle nested tables
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_table_inside_table(void)
{
   error_msg_solo("UDO cannot handle nested tables");
}





/*******************************************************************************
*
*  error_wrong_mapping():
*     error message: mapping not numeric or not of type integer
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_wrong_mapping(void)
{
   error_msg_solo("mapping not numeric or not of type integer");
}





/*******************************************************************************
*
*  error_node2_not_allowed():
*     error message: use !node first (structure gap) or use !begin_node & !end_node
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_node2_not_allowed(void)
{
   fatal_msg_solo("use !node first (structure gap) or use !begin_node & !end_node");
}





/*******************************************************************************
*
*  error_node3_not_allowed():
*     error message: use !subnode first (structure gap) or use !begin_node & !end_node
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_node3_not_allowed(void)
{
   fatal_msg_solo("use !subnode first (structure gap) or use !begin_node & !end_node");
}





/*******************************************************************************
*
*  error_node4_not_allowed():
*     error message: use !subsubnode first (structure gap) or use !begin_node & !end_node
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_node4_not_allowed(void)
{
   fatal_msg_solo("use !subsubnode first (structure gap) or use !begin_node & !end_node");
}





/*******************************************************************************
*
*  error_node5_not_allowed():
*     error message: use !subsubsubnode first (structure gap) or use !begin_node & !end_node
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_node5_not_allowed(void)
{
   fatal_msg_solo("use !subsubsubnode first (structure gap) or use !begin_node & !end_node");
}





/*******************************************************************************
*
*  error_node6_not_allowed():
*     error message: use !subsubsubsubnode first (structure gap) or use !begin_node & !end_node
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void error_node6_not_allowed(void)
{
   fatal_msg_solo("use !subsubsubsubnode first (structure gap) or use !begin_node & !end_node");
}





/*******************************************************************************
*
*  note_long_sourceline():
*     note message: check this paragraph (line too long)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void note_long_sourceline(void)
{
   if (!bNoWarnings && !bNoWarningsLines)
      note_msg_solo("check this paragraph");
   else
      note_counter++;
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

GLOBAL void warning_long_destline(

const char   *s,       /* */
const _UWORD   lnr,     /* */
const int     ll)      /* */
{
   char       m[512];  /* */

   if (!bNoWarnings && !bNoWarningsLines)
   {
      sprintf(m, "Warning: %s %u: overfull line: %d", s, lnr, ll);
      logln(m);
   }
   
   warning_counter++;
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

GLOBAL void note_short_sourceline(

const char  *s)  /* */
{
   if (!bNoWarnings && !bNoWarningsLines)
      note_msg_para("check this paragraph", s);
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

GLOBAL void warning_short_destline(

const char   *s,       /* */
const _UWORD   lnr,     /* */
const int     ll,      /* */
const char   *w)       /* */
{
   char       m[512];  /* */

   if (!bNoWarnings && !bNoWarningsLines)
   {
      sprintf(m, "Warning: %s %u: too short line: %d: %s", s, lnr, ll, w);
      logln(m);
   }
   
   warning_counter++;
}





/*******************************************************************************
*
*  warning_no_unichar():
*     warning message: %s not available in this charset
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void warning_no_unichar(

const char  *s)  /* */
{
   warning_msg_para("%s not available in this charset", s);
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

GLOBAL void warning_cannot_recode(

const char   c,       /* char */
const char  *se,      /* source encoding */
const char  *te)      /* target encoding */
{
   char      s[512];  /* */


   if (iUdopass == PASS2)
   {
      sprintf(s, "cannot recode %c (%s #%u) to %s", c, se, ((_UBYTE)c), te);
      warning_msg_solo(s);
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

GLOBAL void warning_cannot_recode_utf8(

const char  *utf,     /* UTF-8 byte stream (e.g. 0xC0 0x85) */
const char  *te)      /* target encoding */
{
   char      s[512];  /* */

   if (iUdopass == PASS2)
   {
      sprintf(s, "can't recode UTF-8 (%s) to %s", utf, te);
      warning_msg_solo(s);
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

GLOBAL void warning_no_isochar(

const char   c)     /* */
{
   char      s[2];  /* */
   

   sprintf(s, "%c", c);
   warning_msg_para("%s not available in ISO Latin 1", s);
}





/*******************************************************************************
*
*  warning_no_texchar():
*     warning message: %s not available in LaTeX
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void warning_no_texchar(

const char   c)     /* */
{
   char      s[2];  /* */


   sprintf(s, "%c", c);
   warning_msg_para("%s maybe not available in LaTeX", s);
}





/*******************************************************************************
*
*  warning_split_verb():
*     warning message: please use (!V) and (!v) in one paragraph
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void warning_split_verb(void)
{
   warning_msg_solo("please use (!V) and (!v) in one paragraph");
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

GLOBAL void warning_node_too_deep(void)
{
   warning_msg_solo("structure depth exceeded, using subsubsubsubnode"); /* [GS] */
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
   return (warning_counter);
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
   return (note_counter);
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
   return (error_counter);
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
   error_counter   = 0;
   warning_counter = 0;
   note_counter    = 0;
}


/* +++ EOF +++ */
