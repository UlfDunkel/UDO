/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : udolocal.h
*  Symbol prefix: udo
*
*  Description  : Typen, die nur in udo.c verwendet werden
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
*  Co-Authors   : Volker Jansen (vj), Martin Osaka (MO), Christof Schardt (CS),
*                 Ulf Dunkel (fd), Gerhard Stoll (ggs)
*  Write access : fd, ggs
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  1995:
*    DH  Jan xx: introduced
*  2010:
*    fd  Feb 15: - file tidied up and reformatted, TAB-free
*                - new: c_code_source(), c_code_target()
*
******************************************|************************************/

/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _udoswitch                 /* ---- table of functions ---- */
{
   char     *magic;                       /* UDO command */
   BOOLEAN  *flag;                        /* relevant switch */
   char      partype;                     /* parameter type */
   char     *parcmd;                      /* parameter command */
   void     *parval;                      /* parameter variable */
}  UDOSWITCH;





/*******************************************************************************
*
*     LOCAL (!) PROTOTYPES FROM UDO.C
*
******************************************|************************************/

   /* justified */
LOCAL void strjustify(char *s, size_t len);

   /* check if command is valid for desired language or format */
LOCAL BOOLEAN str_for_destlang(const char *s);
LOCAL BOOLEAN str_for_os(const char *s);

   /* color handling */
LOCAL int get_color(void);
LOCAL void get_drc_color(const char *s, char *h);
LOCAL void c_drc_bcolor(void);
LOCAL void c_drc_icolor(void);
LOCAL void c_drc_ucolor(void);
LOCAL void c_drc_flags(void);

LOCAL void set_win_backcolor (char *s, const int c);
LOCAL void set_win_textcolor (char *s, const int c);
LOCAL void set_win_linkcolor (char *s, const int c);

LOCAL void set_wh4_backcolor (char *s, const int c);
LOCAL void set_wh4_textcolor (char *s, const int c);
LOCAL void set_wh4_linkcolor (char *s, const int c);

   /* check if a command uses [on] or [off] */
LOCAL BOOLEAN check_on(void);
LOCAL BOOLEAN check_off(void);

   /* manage symbols */
LOCAL void c_set(void);
LOCAL void c_unset(void);

   /* error messages */
LOCAL void cmd_outside_preamble(void);
LOCAL void cmd_inside_preamble(void);

   /* miscellaneous */
LOCAL int idxlist_compare (IDXLIST *p, IDXLIST *q);
LOCAL void sort_idxlist(void);
LOCAL void print_ascii_index(void);
LOCAL void print_info_index(void);
LOCAL void c_index(void);

   /* headings */
LOCAL void c_heading(void);
LOCAL void c_subheading(void);
LOCAL void c_subsubheading(void);
LOCAL void c_subsubsubheading(void);
LOCAL void c_subsubsubsubheading(void);

LOCAL void c_listheading(void);
LOCAL void c_listsubheading(void);
LOCAL void c_listsubsubheading(void);
LOCAL void c_listsubsubsubheading(void);
LOCAL void c_listsubsubsubsubheading(void);

   /* encoding handling */
LOCAL void c_code(void);
LOCAL void c_code_source(void);
LOCAL void c_code_target(void);

   /* more misc. */
LOCAL void c_tunix(void);
LOCAL void c_nop(void);
LOCAL void c_break(void);
LOCAL void c_error(void);

LOCAL void c_sloppy(void);
LOCAL void c_fussy(void);

LOCAL void c_autoref(void);
LOCAL void c_autoref_items(void);

LOCAL void c_universal_charset(void);
LOCAL void c_rtf_keep_tables(void);

LOCAL void c_verbatim_backcolor(void);
LOCAL void output_empty_lines(const int count);
LOCAL void c_bigskip(void);
LOCAL void c_medskip(void);
LOCAL void c_smallskip(void);

LOCAL void c_tex_dpi(void);
LOCAL void c_tex_verb(void);
LOCAL void c_win_charwidth(void);
LOCAL void c_wh4_charwidth(void);
LOCAL void c_rtf_charwidth(void);
/* New in V6.5.9 [NHz] */
LOCAL void c_rtf_add_colour(void);
LOCAL void c_html_img_suffix(void);
LOCAL void c_html_nodesize(void);

LOCAL void c_htag_img_suffix(void);
LOCAL void c_tabwidth(void);
LOCAL void c_verbatimsize(void);
LOCAL void c_linedrawsize(void);

   /* handle special commands like !raw [tex] */
LOCAL void c_check_raw(char *s);

   /* general image handling */
LOCAL void convert_image(const BOOLEAN visible);
LOCAL void c_image(void);
LOCAL void c_image_nonr(void);

   /* include + input */
LOCAL void c_include_verbatim(void);
LOCAL void c_include_preformatted(void);
LOCAL void c_include_linedraw(void);
LOCAL void c_include_raw(void);
LOCAL void c_include_src(void);
LOCAL void c_include_comment(void);

LOCAL void c_input(void);

   /* hyphenation */
LOCAL void str2silben(char *s);

   /* token management */
LOCAL void check_parwidth(void);
LOCAL BOOLEAN malloc_token_output_buffer(void);
LOCAL void free_token_output_buffer(void);
LOCAL void insert_nl_token_buffer(void);

LOCAL void output_hyphen_line(const char *s);
LOCAL void warning_short_line(const size_t len, const char *t);

LOCAL void to_check_rtf_quote_indent(char *s);
LOCAL void to_check_quote_indent(size_t *u);

   /* sort hyphen file and remove dupes */
LOCAL int hyplist_compare (HYPLIST *p, HYPLIST *q);
LOCAL HYPLIST *hyplist_merge (HYPLIST *p, HYPLIST *q);
LOCAL HYPLIST *hyplist_sort (HYPLIST *p);
LOCAL HYPLIST * new_hyplist_item(void);
LOCAL BOOLEAN add_hyplist_item(const char *s);
LOCAL void sort_hypfile(const char *name);

   /* check commands for formats or languages */
LOCAL void clear_if_stack(void);
LOCAL void push_if_stack(int kind, BOOLEAN ignore);
LOCAL void pop_if_stack(void);
LOCAL void toggle_if_stack(void);
LOCAL BOOLEAN is_if_stack_ignore(void);
LOCAL void pass_check_free_line(char *zeile, int pnr);
LOCAL void pass_check_if (char *zeile, int pnr);

   /* get + set switches */
LOCAL void get_switch_par(const UDOSWITCH *us);
LOCAL BOOLEAN pass1_check_preamble_commands(void);
LOCAL BOOLEAN pass1_check_main_commands(void);
LOCAL BOOLEAN pass1_check_everywhere_commands(void);

   /* check special environments */
LOCAL void pass1_check_environments(char *zeile);

   /* parse lines and create TOCs (pass 1) */
LOCAL BOOLEAN pass1(char *datei);

   /* parse lines and convert them (pass 2) */
LOCAL void output_verbatim_line(char *zeile);
LOCAL void output_linedraw_line(char *zeile);
LOCAL void output_comment_line(char *zeile);
LOCAL void c_comment(void);

LOCAL BOOLEAN pass2 (char *datei);

   /* create files for several target formats */
LOCAL void save_pchelp_commandfile(void);
LOCAL void save_winhelp_project(void);
LOCAL void save_winhelp4_project(void);
LOCAL void save_htmlhelp_project(void);

   /* set important format-dependent conversion flags */
LOCAL void set_format_flags(void);

   /* more misc. */
LOCAL void show_udo_intro(void);
LOCAL BOOLEAN passU(char *datei);

   /* set strings for target language */
LOCAL void get_timestr(char *t);

   /* init variables */
LOCAL void init_vars_nroff(void);
LOCAL void init_vars_stg(void);
LOCAL void init_vars_texinfo(void);
LOCAL void init_vars_sourcecode(void);
LOCAL void init_vars_htmlhelp(void);
LOCAL void init_vars_pdf(void);
LOCAL void init_vars_win(void);
LOCAL void init_vars_spec(void);

LOCAL void init_modules(void);
LOCAL void exit_modules(void);

LOCAL BOOLEAN check_modules_pass1(void);
LOCAL BOOLEAN check_modules_pass2(void);

   /* adjust file names and extensions */
LOCAL void logfile_adjust(void);


/* +++ EOF +++ */

