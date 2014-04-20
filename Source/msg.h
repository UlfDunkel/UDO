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
*                - VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
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

   /* --- message wrapper functions --- */

GLOBAL void fatal_msg_solo(const char *s);
GLOBAL void fatal_msg_para(const char *f, const char *s);

GLOBAL void error_msg_solo(const char *s);
GLOBAL void error_msg_para(const char *f, const char *s);

GLOBAL void warning_msg_solo(const char *em);
GLOBAL void warning_msg_para(const char *f, const char *s);

GLOBAL void note_msg_solo(const char *em);
GLOBAL void note_msg_para(const char *f, const char *s);



   /* --- string output to log file --- */

GLOBAL void logln(const char *s);
GLOBAL void vloglnf ( const char *fmt, ... ) __attribute__((format(printf, 1, 2)));


   /* --- write information into log file --- */

GLOBAL void logln_warnings_errors(void);
GLOBAL void logln_information(void);
GLOBAL void logln_interrupted(void);
GLOBAL void logln_file_generated(const char *kind, const char *filename, const char *suff );

GLOBAL void error_message(const char *msg );
GLOBAL void warning_message(const char *msg );
GLOBAL void note_message(const char *msg );
GLOBAL void fatal_message(const char *msg );


   /* --- program error messages --- */

GLOBAL void error_open_logfile(const char *s);
GLOBAL void error_open_hypfile(const char *s);
GLOBAL void error_open_idxfile(const char *s);
GLOBAL void error_open_treefile(const char *s);
GLOBAL void error_open_uprfile(const char *s);
GLOBAL void error_open_outfile(const char *s);
GLOBAL void error_open_infile(const char *s);
GLOBAL void error_infile_outfile(const char *s);
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
GLOBAL void error_malloc_failed(void);
GLOBAL void error_buffer_overflow(void);
GLOBAL void error_empty_docinfo(void);
GLOBAL void error_missing_title_data(void);
GLOBAL void error_unknown_docinfo(const char *s);
GLOBAL void error_unknown_html_navigation(const char *s);  /* New V 6.5.20 */
GLOBAL void error_unknown_color(const char *s);
GLOBAL void error_wrong_header_date(const char *s); /* New in V6.5.5 [NHz] */
GLOBAL void error_empty_header_links(void);   /* New feature #0000053 in V6.5.2 [NHz] */
GLOBAL void error_argument_header_links(const char *s); /* New feature #0000053 in V6.5.2 [NHz] */
GLOBAL void error_error(const char *s);


   /* --- severe syntax errors --- */

GLOBAL void error_syntax_error(void);
GLOBAL void error_end_without_begin(const char *se, const char *sb);
GLOBAL void error_wrong_end(const char *sb, const char *se);
GLOBAL void error_item_outside_env(void);
GLOBAL void error_item_many_enum(void);
GLOBAL void error_missing_end(const char *s);
GLOBAL void error_called_twice(const char *s);
GLOBAL void error_too_many_env(void);
GLOBAL void error_not_active(const char *s);
GLOBAL void error_still_active(const char *s);
GLOBAL void error_missing_parameter(const char *s);
GLOBAL void error_too_many_parameters(void);
GLOBAL void error_outside_preamble(const char *s);
GLOBAL void error_inside_preamble(const char *s);
GLOBAL void error_unknown_command(const char *s);
GLOBAL void error_unexpected_eol(void);
GLOBAL void error_wrong_nr_parameters(const char *s);
GLOBAL void error_too_many_macros(void);
GLOBAL void error_long_macro_name(int len);
GLOBAL void error_long_macro_cont(int len);
GLOBAL void error_too_many_defines(void);
GLOBAL void error_long_define_name(int len);
GLOBAL void error_long_define_cont(int len);
GLOBAL void error_too_many_placeholder(void);
GLOBAL void error_too_many_symbols(void);
GLOBAL void error_unset_symbol(const char *s);
GLOBAL void error_too_many_hyphens(void);
GLOBAL void error_too_many_tokens(void);
GLOBAL void error_too_many_node(void);
GLOBAL void error_too_many_label(void);
GLOBAL void error_too_many_alias(void);
GLOBAL void error_too_many_files(void);
GLOBAL void error_replace_param(const char *s);
GLOBAL void error_undefined_link(const char *l);
GLOBAL void error_too_many_if(const char *s, const UWORD l);
GLOBAL void error_else_without_if(void);
GLOBAL void error_endif_without_if(void);
GLOBAL void error_missing_endif(const char *s, const UWORD l);
GLOBAL void error_table_width(void);
GLOBAL void error_table_height(void);
GLOBAL void error_table_cell_width(void);
GLOBAL void error_table_label(void);
GLOBAL void error_odd_dblquotes(void);
GLOBAL void error_odd_quotes(void);
GLOBAL void error_no_language(const char *s);
GLOBAL void error_no_charset(const char *s);
GLOBAL void error_xlink_win_syntax(void);
GLOBAL void error_xlink_win_topic(void);
GLOBAL void error_xlink_win_file(void);
GLOBAL void error_no_udoinputpath(void);
GLOBAL void error_fatal_error(const char *s);
GLOBAL void error_table_inside_table(void);
GLOBAL void error_wrong_mapping(void);
GLOBAL void error_node2_not_allowed(void);
GLOBAL void error_node3_not_allowed(void);
GLOBAL void error_node4_not_allowed(void);
GLOBAL void error_node5_not_allowed(void);
GLOBAL void error_node6_not_allowed(void);


   /* --- warnings (tiny syntax errors) --- */

GLOBAL void note_long_sourceline(void);
GLOBAL void warning_long_destline(const char *s, const UWORD lnr, const int ll);

GLOBAL void note_short_sourceline(const char *s);
GLOBAL void warning_short_destline(const char *s, const UWORD lnr, const int ll, const char *w);

GLOBAL void warning_no_unichar(const char *s);
GLOBAL void warning_cannot_recode(const char c, const char *scs, const char *dcs);
GLOBAL void warning_cannot_recode_utf8(const char *utf, const char *dcs);
GLOBAL void warning_no_isochar(const char c);
GLOBAL void warning_no_texchar(const char c);

GLOBAL void warning_split_verb(void);

GLOBAL void warning_node_too_deep(void);


   /* --- inquiry functions --- */

GLOBAL int get_warning_counter(void);
GLOBAL int get_note_counter(void);
GLOBAL int get_error_counter(void);


   /* --- module initialization --- */

GLOBAL void init_module_msg(void);



   /* --- debug functions --- */
   
/* define this, to let loglnposprintf do printf, instead passing string to GUI */
#define USE_LOGLNPOSPRINTF

GLOBAL void loglnposprintf(const char *we, const char *msg);


/* +++ EOF +++ */
