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
*    fd  Mar 12: c_code() removed
*  2014
*    ggs Apr 20: Add Node6
*
******************************************|************************************/

/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _udoswitch                 /* ---- table of functions ---- */
{
   const char *magic;                     /* UDO command */
   _BOOL  *flag;                          /* relevant switch */
   char      partype;                     /* parameter type */
   const char *parcmd;                    /* parameter command */
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
LOCAL _BOOL str_for_destlang(const char *s);
LOCAL _BOOL str_for_os(const char *s);

   /* color handling */
LOCAL int get_color(void);
LOCAL void c_drc_bcolor(void);
LOCAL void c_drc_icolor(void);
LOCAL void c_drc_ucolor(void);
LOCAL void c_drc_flags(void);

   /* check if a command uses [on] or [off] */
LOCAL _BOOL check_on(void);
LOCAL _BOOL check_off(void);

   /* manage symbols */
LOCAL void c_set(void);
LOCAL void c_unset(void);

   /* error messages */
LOCAL void cmd_outside_preamble(void);
LOCAL void cmd_inside_preamble(void);

   /* miscellaneous */
LOCAL int idxlist_compare(IDXLIST *p, IDXLIST *q);
LOCAL void sort_idxlist(void);
LOCAL void print_ascii_index(void);
LOCAL void print_info_index(void);
LOCAL void c_index(void);
LOCAL void c_toplink(void);
LOCAL void c_udolink(void);

   /* headings */
LOCAL void c_heading(void);
LOCAL void c_subheading(void);
LOCAL void c_subsubheading(void);
LOCAL void c_subsubsubheading(void);
LOCAL void c_subsubsubsubheading(void);
LOCAL void c_subsubsubsubsubheading(void);
LOCAL void c_subsubsubsubsubsubheading(void);
LOCAL void c_subsubsubsubsubsubsubheading(void);
LOCAL void c_subsubsubsubsubsubsubsubheading(void);

LOCAL void c_listheading(void);
LOCAL void c_listsubheading(void);
LOCAL void c_listsubsubheading(void);
LOCAL void c_listsubsubsubheading(void);
LOCAL void c_listsubsubsubsubheading(void);
LOCAL void c_listsubsubsubsubsubheading(void);
LOCAL void c_listsubsubsubsubsubsubheading(void);
LOCAL void c_listsubsubsubsubsubsubsubheading(void);
LOCAL void c_listsubsubsubsubsubsubsubsubheading(void);

   /* encoding handling */
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
LOCAL void c_limage(void);
LOCAL void c_define(void);
LOCAL void c_undef(void);

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
LOCAL void c_rtf_add_color(void);
LOCAL void c_html_img_suffix(void);
LOCAL void c_html_nodesize(void);

LOCAL void c_htag_img_suffix(void);
LOCAL void c_tabwidth(void);
LOCAL void c_verbatimsize(void);
LOCAL void c_linedrawsize(void);

   /* handle special commands like !raw [tex] */
LOCAL void c_check_raw(char *s);

   /* general image handling */
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

   /* parse lines and create TOCs (pass 1) */
LOCAL _BOOL pass1(const char *datei);

   /* parse lines and convert them (pass 2) */
LOCAL void c_comment(void);

LOCAL _BOOL pass2(const char *datei);

   /* more misc. */
LOCAL _BOOL passU(const char *datei);

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

LOCAL _BOOL check_modules_pass1(void);
LOCAL _BOOL check_modules_pass2(void);

   /* adjust file names and extensions */
LOCAL void logfile_adjust(void);
