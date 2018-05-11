/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : toc.h
*  Symbol prefix: toc
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
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : fd
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
*    fd  Jan 20: new: html_quotes()
*    fd  Feb 05: file reformatted and tidied up; TAB-free
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  May 21: more comments translated
*  2011:
*    fd  Feb 14: - functions add_...node_to_toc() merged into add_nodetype_to_toc()
*                - all set_html_...() functions moved from TOC to TOC_HTML
*  2014:
*    ggs Apr 20: Add Node6
*
******************************************|************************************/

#ifndef __UDOTOC__
#define __UDOTOC__

/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define MAX_LABEL_LEN      199
#define MAX_NODE_LEN       199
#define MAX_FILENAME_LEN    64
#define MAX_IMAGE_LEN      128
#define MAX_HELPID_LEN      16

typedef _UWORD LABIDX;
typedef int TOCIDX;
typedef int TOCTYPE;

#define TOC_NODE1    0                    /* !node */
#define TOC_NODE2    1                    /* !subnode */
#define TOC_NODE3    2                    /* !subsubnode */
#define TOC_NODE4    3                    /* !subsubsubnode */
#define TOC_NODE5    4                    /* !subsubsubsubnode */
#define TOC_NODE6    5                    /* !subsubsubsubsubnode */
#define TOC_NODE7    6                    /* !subsubsubsubsubsubnode */
#define TOC_NODE8    7                    /* !subsubsubsubsubsubsubnode */
#define TOC_NODE9    8                    /* !subsubsubsubsubsubsubsubnode */
#define TOC_MAXDEPTH 9
#define TOC_TOC     (TOC_MAXDEPTH)        /* table of contents */
#define TOC_NONE    (TOC_MAXDEPTH+1)      /* neither nor ... :-) */

#define KPS_CONTENT       0
#define KPS_BOOKMARK      1
#define KPS_NAMEDEST      2
#define KPS_PS2DOCINFO    3
#define KPS_DOCINFO2PS    4
#define KPS_NODENAME      5



#define USE_NAME_HASH 1




/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _label                     /* jump labels to be referenced */
{
   char      name[MAX_LABEL_LEN + 1];     /* label name */
   LABIDX    labindex;                    /* lab[1]==1, lab[2]==2, etc. */
   size_t    len;                         /* label name len */
   _BOOL   appendix;                    /* label is in appendix */
   _BOOL   is_node;                     /* label is node title */
   _BOOL   is_popup;                    /* node is a popup node */
   _BOOL   is_alias;                    /* alias name of a node */
   TOCIDX    tocindex;                    /* belongs to node "toc_table[tocindex]" */
   _BOOL   ignore_links;                /* don't link to this label */
   _BOOL   ignore_index;                /* don't index this label (node only!) */
   _BOOL   referenced;                  /* TRUE: label has been referenced */
   FILE_LOCATION source_location;       /* where the label was defined */
#if USE_NAME_HASH
    struct _label *next_hash;
#endif
} LABEL;



typedef struct _tocitem                       /* entries for the Table Of Contents (TOC) */
{
   char      nodename[MAX_NODE_LEN + 1];      /* The name of the node */
   char      *nodetitle;					  /* The text that is displayed as title and in links */
   TOCIDX    n[TOC_MAXDEPTH];                 /* Kapitelnummern (absolut) */
   TOCIDX    nr[TOC_MAXDEPTH];                /* Inhaltsverzeichnis-Nummern */
   _BOOL   appendix;                          /* TRUE = Steht im Anhang */
   TOCTYPE   toctype;                         /* !node, !subnode etc. */
   FILE_LOCATION source_location;             /* Filename der Sourcecodedatei */
   char      filename[MAX_FILENAME_LEN+1];    /* HTML-Filename (basename only, without suffix and html_name_prefix) */
   FILE_ID   dirname;                         /* HTML-Verzeichnisname */
   char     *keywords;                        /* HTML-Keywords */
   char     *description;                     /* HTML-Description */
   char     *robots;                          /* HTML-Robots */
   FILE_ID   counter_command;                 /* HTML-Kommandos fuer Counter */
   struct rgb backcolor;                      /* HTML <BODY BGCOLOR=...> */
   struct rgb textcolor;                      /* HTML <BODY TEXT=...> */
   struct rgb linkcolor;                      /* HTML <BODY LINK=...> */
   struct rgb alinkcolor;                     /* HTML <BODY ALINK=...> */
   struct rgb vlinkcolor;                     /* HTML <BODY VLINK=...> */
   FILE_ID   backimage;                       /* HTML <BODY BACKGROUND=...> */
   STYLELIST styles;                          /* HTML <style> */
   SCRIPTLIST scripts;                        /* HTML <SCRIPT> */
   FILE_ID   favicon_name;                    /* HTML <FAVICON> */
   FILE_ID   bgsound;                         /* HTML <bgsound> */
   char     *image;                           /* Grafik anstelle Kapitelnamen */
   _UWORD     uiImageWidth;                   /* Breite und Hoehe des Bildes */ 
   _UWORD     uiImageHeight;
   char     *icon;                            /* Icon fuer modernes Layout */
   _UWORD     uiIconWidth;                    /* Breite und Hoehe des Icons */ 
   _UWORD     uiIconHeight;
   char     *icon_active;                     /* Icon fuer    -""- (aktive Seite) */
   _UWORD     uiIconActiveWidth;              /* Breite und Hoehe des Icons */ 
   _UWORD     uiIconActiveHeight;
   char     *icon_text;                       /* Icontext fuer modernes Layout */
   char     *helpid;                          /* Eine Jump-ID, wie ein Alias */
   int       mapping;                         /* Eine Jump-ID fuer WinHelp/IPF */
   char     *win_button[MAX_WIN_BUTTONS];
   _BOOL   invisible;                         /* TRUE = Nicht ins Inhaltsverzeichnis */
   _BOOL   converted;                         /* Bereits Makros etc. angepasst? */
   LABIDX    labindex;                        /* label_table[]-Position */
   TOCIDX    prev_index;                      /* toc_table[]-Position des Vorgaengers */
   TOCIDX    next_index;                      /* toc_table[]-Position des Nachfolgers */
   TOCIDX    up_n_index[TOC_MAXDEPTH - 1];    /* toc_table[]-Positionen oberhalb */
   TOCIDX    num_children;                    /* Anzahl enthaltener Subnodes */
   _BOOL   ignore_subtoc;                     /* ignore !use_auto_subtoc */
   _BOOL   ignore_toptoc;                     /* ignore !use_auto_toptoc */
   _BOOL   ignore_links;                      /* don't link to this page */
   _BOOL   ignore_index;                      /* don't add this to the index page */
   _BOOL   ignore_title;                      /* don't create title for this node */
   _BOOL   ignore_headline;                   /* don't create a header line */
   _BOOL   ignore_bottomline;                 /* don't create a bottom line */
   _BOOL   ignore_footer;                     /* don't create a footer line */
   FILE_ID   raw_header_filename;             /* file to include in header */
   FILE_ID   raw_footer_filename;             /* file to include in footer */
   _BOOL   ignore_raw_header;                 /* don't read user-defined header */
   _BOOL   ignore_raw_footer;                 /* don't read user-defined footer */
   _BOOL   has_children;                      /* TRUE: this node has subnode(s) */
   _BOOL   has_visible_children;              /* TRUE: this node has visible subnode(s) */
   char *toptitle;                            /* title used in header line */
} TOCITEM;





/*******************************************************************************
*
*     GLOBAL VARIABLES
*
******************************************|************************************/

GLOBAL TOCITEM **toc_table;                  /* Zeiger auf Inhaltsverzeichnis */
GLOBAL TOCIDX    toc_offset[TOC_MAXDEPTH];   /* Offsets fuer Kapitelnumerierung, Default=0 */

GLOBAL TOCIDX    all_nodes[TOC_MAXDEPTH];

GLOBAL _BOOL   bInsideAppendix,              /* Ist UDO im Anhang? */
                 bInsideDocument;            /* Ist UDO im Dokument selber? */

GLOBAL _BOOL   called_tableofcontents;       /* Wurde toc ausgegeben? (@toc) */
GLOBAL TOCTYPE   toc_maxdepth;

GLOBAL _BOOL   uses_tableofcontents;         /* !tableofcontents wird benutzt */

GLOBAL _BOOL   in_about_udo;				 /* if TRUE dont make entry in log files (for files generated by UDO itself) */
GLOBAL char      current_node_name_sys[LINELEN];

GLOBAL char      current_chapter_name[MAX_NODE_LEN + 1];
GLOBAL char      current_chapter_nr[32];

GLOBAL _BOOL   use_auto_subtocs[TOC_MAXDEPTH - 1];   /* autom. Unter-Toc's anlegen? */
GLOBAL int       subtocs_depth[TOC_MAXDEPTH - 1];

GLOBAL char      sHtmlPropfontStart[256];
GLOBAL char      sHtmlPropfontEnd[16];

GLOBAL char      sHtmlMonofontStart[256];
GLOBAL char      sHtmlMonofontEnd[16];

GLOBAL _BOOL   html_merge_node[TOC_MAXDEPTH];         /* Nodes nicht splitten? */

GLOBAL TOCIDX    p1_toc_counter;             /* counter for toc_table[]-array, pass1; contains last used lot # (1 less than number of entries) */
GLOBAL TOCIDX    p2_toc_counter;             /* counter for toc_table[]-array, pass2; contains last used slot # (1 less than number of entries) */

GLOBAL char     *html_frames_toc_title;
GLOBAL char     *html_frames_con_title;

GLOBAL _BOOL	stg_need_endnode;

extern int rtf_structure_height[TOC_MAXDEPTH + 1]; /* +1 fuer use_style_book */

extern int kps_structure_height[TOC_MAXDEPTH + 1]; /* +1 fuer use_style_book */

extern char asc_structure_chars[TOC_MAXDEPTH];





/*******************************************************************************
*
*     GLOBAL PROTOTYPES
*
******************************************|************************************/

GLOBAL _BOOL is_node_link(const char *link, char *node, TOCIDX *ti, _BOOL *isnode, _BOOL *isalias, _BOOL *ispopup, LABIDX *li);
GLOBAL LABIDX getLabelIndexFromTocIndex(LABIDX *li, const TOCIDX ti);

GLOBAL void reset_refs(void);
GLOBAL void auto_references(char *s, const _BOOL for_toc, const char *pic, const _UWORD uiWidth, const _UWORD uiHeight);
GLOBAL void gen_references(char *s, const _BOOL for_toc, const char *pic, const _UWORD uiWidth, const _UWORD uiHeight);

GLOBAL void check_endnode(void);
void stg_out_endnode(void);

GLOBAL _BOOL check_output_raw_header(void);
GLOBAL _BOOL check_output_raw_footer(_BOOL lastNode);

GLOBAL void man_headline(void);
GLOBAL void man_bottomline(void);
GLOBAL void stg_headline(const char *numbers, const char *nodename, _BOOL popup);
GLOBAL void tvh_headline(const char *s);
GLOBAL void output_html_header(const char *t);
GLOBAL void html_save_frameset(void);
GLOBAL void html_headline(void);
GLOBAL void html_bottomline(void);
GLOBAL void html_footer(void);
GLOBAL _BOOL save_html_index(void);
GLOBAL void add_pass1_index_udo(void);
void toc_mark_index_referenced(void);

GLOBAL void hh_headline(void);
GLOBAL void hh_bottomline(void);
GLOBAL _BOOL save_htmlhelp_contents(const char* filename);
GLOBAL _BOOL save_htmlhelp_index(const char* filename);


   /* --- chapter commands --- */

GLOBAL void c_node(void);
GLOBAL void c_node_iv(void);
GLOBAL void c_pnode(void);
GLOBAL void c_pnode_iv(void);

GLOBAL void c_subnode(void);
GLOBAL void c_subnode_iv(void);
GLOBAL void c_psubnode(void);
GLOBAL void c_psubnode_iv(void);

GLOBAL void c_subsubnode(void);
GLOBAL void c_subsubnode_iv(void);
GLOBAL void c_psubsubnode(void);
GLOBAL void c_psubsubnode_iv(void);

GLOBAL void c_subsubsubnode(void);
GLOBAL void c_subsubsubnode_iv(void);
GLOBAL void c_psubsubsubnode(void);
GLOBAL void c_psubsubsubnode_iv(void);

GLOBAL void c_subsubsubsubnode(void);
GLOBAL void c_subsubsubsubnode_iv(void);
GLOBAL void c_psubsubsubsubnode(void);
GLOBAL void c_psubsubsubsubnode_iv(void);

GLOBAL void c_subsubsubsubsubnode(void);
GLOBAL void c_subsubsubsubsubnode_iv(void);
GLOBAL void c_psubsubsubsubsubnode(void);
GLOBAL void c_psubsubsubsubsubnode_iv(void);

GLOBAL void c_subsubsubsubsubsubnode(void);
GLOBAL void c_subsubsubsubsubsubnode_iv(void);
GLOBAL void c_psubsubsubsubsubsubnode(void);
GLOBAL void c_psubsubsubsubsubsubnode_iv(void);

GLOBAL void c_subsubsubsubsubsubsubnode(void);
GLOBAL void c_subsubsubsubsubsubsubnode_iv(void);
GLOBAL void c_psubsubsubsubsubsubsubnode(void);
GLOBAL void c_psubsubsubsubsubsubsubnode_iv(void);

GLOBAL void c_subsubsubsubsubsubsubsubnode(void);
GLOBAL void c_subsubsubsubsubsubsubsubnode_iv(void);
GLOBAL void c_psubsubsubsubsubsubsubsubnode(void);
GLOBAL void c_psubsubsubsubsubsubsubsubnode_iv(void);

GLOBAL void c_endnode(void);

GLOBAL void c_begin_node(void);
GLOBAL void c_begin_node_iv(void);
GLOBAL void c_begin_pnode(void);
GLOBAL void c_begin_pnode_iv(void);

GLOBAL void c_end_node(void);


   /* --- TOC output --- */

GLOBAL void c_toc(void);
GLOBAL void c_subtoc(void);

GLOBAL void c_listoffigures(void);
GLOBAL void c_listoftables(void);
GLOBAL void c_tableofcontents(void);

GLOBAL _BOOL bookmarks_ps(void);


   /* --- output a label in pass 2 --- */

GLOBAL void c_label(void);
GLOBAL void c_label_iv(void);
GLOBAL void c_alias(void);


   /* --- misc. --- */

GLOBAL LABIDX add_label(const char *label, const _BOOL isn, const _BOOL isp, _BOOL ignore_index, _BOOL ignore_links);
GLOBAL LABIDX add_alias(const char *alias, const _BOOL isp, _BOOL referenced);

GLOBAL void string2reference(char *ref, const char *display, const LABIDX li, const _BOOL for_toc,
                      const char *pic, const unsigned int uiW, const unsigned int uiH );
void free_style_list(STYLELIST *list);
void free_script_list(SCRIPTLIST *list);


   /* --- enhance TOC --- */

GLOBAL void set_ignore_headline(void);
GLOBAL void set_ignore_bottomline(void);
GLOBAL void set_raw_header_filename(void);
GLOBAL void set_ignore_raw_header(void);
GLOBAL void set_raw_footer_filename(void);
GLOBAL void set_ignore_raw_footer(void);
GLOBAL void set_ignore_footer(void);
GLOBAL void set_ignore_title(void);
GLOBAL void set_ignore_links(void);
GLOBAL void set_ignore_index(void);
GLOBAL void set_ignore_subtoc(void);
GLOBAL void set_ignore_popup_title(void);
GLOBAL void set_ignore_toptoc(void);
GLOBAL void set_helpid(void);
GLOBAL void win_set_button(void);
GLOBAL void set_mapping(void);
GLOBAL void set_toptitle(void);
GLOBAL void set_nodetitle(TOCIDX idx);


GLOBAL void set_chapter_image(void);
GLOBAL void set_chapter_icon(void);
GLOBAL void set_chapter_icon_active(void);
GLOBAL void set_chapter_icon_text(void);

GLOBAL _BOOL add_node_to_toc(TOCTYPE nodetype, _BOOL popup, _BOOL invisible);

GLOBAL _BOOL toc_begin_node (const _BOOL popup, const _BOOL invisible);
GLOBAL void toc_end_node(void);
GLOBAL _BOOL is_current_node(TOCIDX tocindex);
GLOBAL _BOOL toc_inside_popup(void);
GLOBAL TOCIDX get_toc_counter(void);
GLOBAL void toc_init_lang(void);


   /* --- output files with Jump IDs for several compilers --- */

GLOBAL _BOOL save_htmlhelp_alias(void);
GLOBAL _BOOL save_htmlhelp_map(void);
GLOBAL _BOOL save_winhelp_map_c(void);
GLOBAL _BOOL save_winhelp_map_pas(void);
GLOBAL _BOOL save_winhelp_map_vb(void);
GLOBAL _BOOL save_winhelp_map_gfa(void);

GLOBAL _BOOL save_winhelp4_cnt(void);


   /* --- module check --- */

GLOBAL _BOOL check_module_toc_pass1(void);
GLOBAL _BOOL check_module_toc_pass2(void);


   /* --- create nodenames --- */

GLOBAL void node2NrWinhelp(char *s, LABIDX i);
GLOBAL void alias2NrWinhelp(char *s, LABIDX i);
GLOBAL void label2NrWinhelp(char *s, LABIDX i);

GLOBAL void node2NrIPF(char *s, LABIDX i);
GLOBAL void alias2NrIPF(char *s, LABIDX i);
GLOBAL void label2NrIPF(char *s, LABIDX i);

GLOBAL void node2pchelp(char *n);
GLOBAL void node2postscript(char *s, int text);

GLOBAL void node2stg(char *s);
GLOBAL void index2stg(char *s);


   /* --- module functions --- */

GLOBAL void toc_pass1_begin_appendix(void);
GLOBAL void toc_pass2_begin_appendix(void);
GLOBAL void init_module_toc_pass2(void);
GLOBAL void init_module_toc(void);
GLOBAL void exit_module_toc(void);

#endif /* __UDOTOC__ */
