/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : msg.h
*  Symbol prefix: msg
*
*  Description  : ???
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
*  Co-Authors   : Gerhard Stoll (ggs), Ulf Dunkel
*  Write access : ggs, fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 22: - header adjusted
*                - void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Mar 04: - file tidied up
*                - message wrapper functions now global
*  2014:
*    ggs Apr 20: Add Node6
*
******************************************|************************************/

/*******************************************************************************
*
*     GLOBAL PROTOTYPES
*
******************************************|************************************/

   /* --- string output to log file --- */

GLOBAL void logln(const char *s);
GLOBAL void vloglnf(const char *fmt, ...) __attribute__((format(printf, 1, 2)));


   /* --- write information into log file --- */

GLOBAL void logln_warnings_errors(void);
GLOBAL void logln_information(void);
GLOBAL void logln_interrupted(void);
GLOBAL void logln_file_generated(const char *kind, const char *filename, const char *suff );

GLOBAL void error_message(const char *msg, ...) __attribute__((format(printf, 1, 2)));
GLOBAL void warning_message(const char *msg, ...) __attribute__((format(printf, 1, 2)));
GLOBAL void note_message(const char *msg, ...) __attribute__((format(printf, 1, 2)));
GLOBAL void fatal_message(const char *msg, ...) __attribute__((format(printf, 1, 2)));


   /* --- program error messages --- */

GLOBAL void error_open_logfile(const char *s);
GLOBAL void error_open_hypfile(const char *s);
GLOBAL void error_open_idxfile(const char *s);
GLOBAL void error_open_treefile(const char *s);
GLOBAL void error_open_uprfile(const char *s);
GLOBAL void error_open_outfile(const char *s);
GLOBAL void error_open_infile(const char *s);
GLOBAL void error_write_img(const char *s);
GLOBAL void error_read_img(const char *s);
GLOBAL void error_read_bmp(const char *s);
GLOBAL void error_read_pcx(const char *s);
GLOBAL void error_read_msp(const char *s);
GLOBAL void error_read_gif(const char *s);
GLOBAL void error_read_png(const char *s);
GLOBAL void error_read_jpeg(const char *s);
GLOBAL void error_open_pass1(const char *s);
GLOBAL void error_open_pass2(const char *s);
GLOBAL void error_mkdir(const char *s);
GLOBAL void error_malloc_failed(size_t size);
GLOBAL void error_empty_docinfo(void);


   /* --- severe syntax errors --- */

GLOBAL void error_syntax_error(void);
GLOBAL void error_end_without_begin(const char *se, const char *sb);
GLOBAL void error_item_many_enum(void);
GLOBAL void error_missing_end(const char *s);
GLOBAL void error_called_twice(const char *s);
GLOBAL void error_not_active(const char *s);
GLOBAL void error_already_active(const char *s);
GLOBAL void error_still_active(const char *s);
GLOBAL void error_missing_parameter(const char *s);
GLOBAL void error_unexpected_eol(void);
GLOBAL void error_wrong_nr_parameters(const char *s);
GLOBAL void error_too_many_tokens(void);
GLOBAL void error_replace_param(const char *s);
GLOBAL void error_undefined_link(const char *l);
GLOBAL void error_missing_endif(const char *s, FILE_LINENO line);
GLOBAL void error_no_charset(const char *s);
GLOBAL void error_node_not_allowed(int level);


   /* --- warnings (tiny syntax errors) --- */

GLOBAL void note_long_sourceline(void);
GLOBAL _BOOL warning_long_destline(const char *s, FILE_LINENO lnr, const int ll);

GLOBAL void note_short_sourceline(const char *s);
GLOBAL _BOOL warning_short_destline(const char *s, FILE_LINENO lnr, const int ll, const char *w);

GLOBAL void warning_cannot_recode(unsigned int c, const char *scs, const char *dcs);
GLOBAL void warning_cannot_recode_utf8(const char *utf, const char *dcs);
GLOBAL void warning_no_isochar(const char c);
GLOBAL void warning_buffer_overrun(const char *func, const char *place, size_t n, size_t max);

GLOBAL void warning_node_too_deep(_BOOL popup, _BOOL invisible);


   /* --- inquiry functions --- */

GLOBAL int get_warning_counter(void);
GLOBAL int get_note_counter(void);
GLOBAL int get_error_counter(void);


   /* --- module initialization --- */

GLOBAL void init_module_msg(void);
