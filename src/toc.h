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
#define MAX_NODE_LEN       199            /* v6.3.9 (old: 128) */
#define MAX_FILENAME_LEN    64
#define MAX_IMAGE_LEN      128
#define MAX_HELPID_LEN      16

#define TOC_TOC    0                      /* table of content */
#define TOC_NODE1  1                      /* !node */
#define TOC_NODE2  2                      /* !subnode */
#define TOC_NODE3  3                      /* !subsubnode */
#define TOC_NODE4  4                      /* !subsubsubnode */
#define TOC_NODE5  5                      /* !subsubsubsubnode */
#define TOC_NODE6  6                      /* !subsubsubsubsubnode */
#define TOC_NONE   7                      /* neither nor ... :-) */



#define USE_NAME_HASH 1




/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _style                     /* style sheets */
{
   char  *href;                           /* Quelle eines Stylesheets */
   char  *filename;                       /* filename only of stylsheet */
   char   media[MAX_LABEL_LEN + 1];       /* fuer welches Medium */
   char   title[MAX_LABEL_LEN + 1];       /* Titel eines Stylesheets */
   int    alternate;                      /* Alternate Stylesheet? */
   int    tocindex;                       /* Gehoert zum Node "toc[tocindex]" */
} STYLE;


typedef struct _label                     /* jump labels to be referenced */
{
   char      name[MAX_LABEL_LEN + 1];     /* label name */
   int       labindex;                    /* lab[1]==1, lab[2]==2, etc. */
   size_t    len;                         /* label name len */
   int       n1;                          /* defined in this node */
   int       n2;                          /* ... subnode */
   int       n3;                          /* ... subsubnode */
   int       n4;                          /* ... subsubsubnode */
   int       n5;                          /* ... subsubsubsubnode */
   int       n6;                          /* ... subsubsubsubsubnode */
   _BOOL   appendix;                    /* label is in appendix */
   _BOOL   is_node;                     /* label is node title */
   _BOOL   is_popup;                    /* node is a popup node */
   _BOOL   is_alias;                    /* alias name of a node */
   int       tocindex;                    /* belongs to node "toc[tocindex]" */
   _BOOL   ignore_links;                /* don't link to this label */
   _BOOL   ignore_index;                /* don't index this label (node only!) */
   _BOOL   referenced;                  /* TRUE: label has been referenced */
#if USE_NAME_HASH
    struct _label *next_hash;
#endif
} LABEL;



typedef struct _tocitem                   /* entries for the Table Of Contents (TOC) */
{
   char      name[MAX_NODE_LEN + 1];      /* Der Eintrag selber */
   int       n1;                          /* Kapitelnummer (absolut) */
   int       n2;                          /* Abschnittnummer (absolut) */
   int       n3;                          /* Unterabschnittnummer   (absolut) */
   int       n4;                          /* Unterabschnittnummer   (absolut) */
   int       n5;                          /* Unterabschnittnummer   (absolut) */
   int       n6;                          /* Unterabschnittnummer   (absolut) */
   int       nr1,nr2,nr3,nr4,nr5,nr6;     /* Inhaltsverzeichnis-Nummern */
   _BOOL   appendix;                    /* TRUE = Steht im Anhang */
   int       toctype;                     /* !node, !subnode, !subsubnode, !subsubsubnode, !subsubsubsubnode */
                                          /* Filename der Sourcecodedatei */   /* V6.5.18 */
   FILE_LOCATION source_location;
   char      filename[MAX_FILENAME_LEN+1];    /* HTML-Filename */
   FILE_ID   dirname;                         /* HTML-Verzeichnisname */
   char     *keywords;                    /* HTML-Keywords */   /* r5pl3 */
   char     *description;                 /* HTML-Description */   /* r6pl5 */
   char     *robots;                      /* HTML-Robots */   /* V6.5.17 */
   FILE_ID   counter_command;                 /* HTML-Kommandos fuer Counter */
   struct rgb backcolor;                      /* HTML <BODY BGCOLOR=...> */
   struct rgb textcolor;                      /* HTML <BODY TEXT=...> */
   struct rgb linkcolor;                      /* HTML <BODY LINK=...> */
   struct rgb alinkcolor;                     /* HTML <BODY ALINK=...> */
   struct rgb vlinkcolor;                     /* HTML <BODY VLINK=...> */
   FILE_ID   backimage;                       /* HTML <BODY BACKGROUND=...> */
   FILE_ID   script_name;                     /* HTML <SCRIPT> */
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
   _BOOL   invisible;                         /* TRUE = Nicht ins Inhaltsverzeichnis */
   _BOOL   converted;                         /* Bereits Makros etc. angepasst? */
   int       labindex;                    /* lab[]-Position */
   int       prev_index;                  /* toc[]-Position des HTML-Vorgaengers */
   int       next_index;                  /* toc[]-Position des HTML-Nachfolgers */
   int       up_n1_index;                 /* toc[]-Position oberhalb */
   int       up_n2_index;
   int       up_n3_index;
   int       up_n4_index;
   int       up_n5_index;
   int       count_n2;                    /* # of contained subnodes */
   int       count_n3;                    /* # of contained subsubnodes */
   int       count_n4;                    /* # of contained subsubsubnodes */
   int       count_n5;                    /* # of contained subsubsubsubnodes */
   int       count_n6;                    /* # of contained subsubsubsubsubnodes */
   _BOOL   ignore_subtoc;               /* ignore !use_auto_subtoc */
   _BOOL   ignore_links;                /* don't link to this page */
   _BOOL   ignore_index;                /* don't add this to the index page */
   _BOOL   ignore_title;                /* don't create title for this node */
   _BOOL   ignore_headline;             /* don't create a header line */
   _BOOL   ignore_bottomline;           /* don't create a bottom line */
   _BOOL   ignore_footer;               /* don't create a footer line */
   FILE_ID   raw_header_filename;             /* file to include in header */
   FILE_ID   raw_footer_filename;             /* file to include in footer */
   _BOOL   ignore_raw_header;           /* don't read user-defined header */
   _BOOL   ignore_raw_footer;           /* don't read user-defined footer */
   _BOOL   has_children;                /* TRUE: this node has subnode(s) */

}  TOCITEM, *pTOCITEM;



/*******************************************************************************
*
*     GLOBAL VARIABLES
*
******************************************|************************************/

GLOBAL int       toc_offset;              /* Offsets fuer Kapitelnumerierung, Default=0 */
GLOBAL int       subtoc_offset;
GLOBAL int       subsubtoc_offset;
GLOBAL int       subsubsubtoc_offset;
GLOBAL int       subsubsubsubtoc_offset;  /* [GS] */
GLOBAL int       subsubsubsubsubtoc_offset;  /* [GS] */

GLOBAL int       all_nodes, 
                 all_subnodes, 
                 all_subsubnodes, 
                 all_subsubsubnodes, 
                 all_subsubsubsubnodes,
                 all_subsubsubsubsubnodes;

GLOBAL _BOOL   bInsideAppendix,         /* Ist UDO im Anhang? */
                 bInsideDocument,         /* Ist UDO im Dokument selber? */
                 bInsidePopup;            /* In einem Popup-Node? */

GLOBAL _BOOL   called_tableofcontents;  /* Wurde toc ausgegeben? (@toc) */
GLOBAL _BOOL   called_subsubsubsubsubnode;

GLOBAL _BOOL   uses_tableofcontents;    /* !tableofcontents wird benutzt */
GLOBAL char      toc_title[MAX_NODE_LEN + 1];

                                          /* 6.3.11 [vj]: This is needed, because current_node_name_sys needs to buffer a lot of stuff! */
GLOBAL char      current_node_name_sys[CNNS_LEN];
                                          /* New in r6pl15 [NHz] */
/* GLOBAL char   current_node_name_sys[MAX_NODE_LEN + 1];
*/
GLOBAL char      current_chapter_name[MAX_NODE_LEN + 1];
GLOBAL char      current_chapter_nr[32];

GLOBAL int       subtocs1_depth;          /*r6pl2*/
GLOBAL int       subtocs2_depth;          /*r6pl2*/
GLOBAL int       subtocs3_depth;          /*r6pl2*/
GLOBAL int       subtocs4_depth;
GLOBAL int       subtocs5_depth;

GLOBAL char      sHtmlPropfontStart[256]; /*r6pl7*/
GLOBAL char      sHtmlPropfontEnd[16];    /*r6pl7*/

GLOBAL char      sHtmlMonofontStart[256]; /*r6pl7*/
GLOBAL char      sHtmlMonofontEnd[16];    /*r6pl7*/

GLOBAL TOCITEM  *toc[MAXTOCS];            /* Zeiger auf Inhaltsverzeichnis */
GLOBAL int       p1_toc_counter;          /* Zaehler fuer das toc[]-Array */
GLOBAL int       p2_toc_counter;

GLOBAL STYLE   **style;                   /* Array mit Zeigern auf Stylesheets */
GLOBAL int       p1_style_counter;        /* Zaehler */

GLOBAL char     *html_frames_toc_title;
GLOBAL char     *html_frames_con_title;

GLOBAL _BOOL	stg_need_endnode;





/*******************************************************************************
*
*     GLOBAL PROTOTYPES
*
******************************************|************************************/

GLOBAL _BOOL is_node_link(const char *link, char *node, int *ti, _BOOL *isnode, int *li);
GLOBAL int getLabelIndexFromTocIndex(int *li, const int ti);

GLOBAL void reset_refs(void);
GLOBAL void auto_references(char *s, const _BOOL for_toc, const char *pic, const _UWORD uiWidth, const _UWORD uiHeight);

GLOBAL void check_endnode(void);
void stg_out_endnode(void);

GLOBAL _BOOL check_output_raw_header(void);
GLOBAL _BOOL check_output_raw_footer(_BOOL lastNode);

GLOBAL void man_headline(void);
GLOBAL void man_bottomline(void);
GLOBAL void stg_headline(const char *numbers, const char *nodename);
GLOBAL void tvh_headline(const char *s);
GLOBAL void output_html_header(const char *t);
GLOBAL void html_save_frameset(void);
GLOBAL void html_headline(void);
GLOBAL void html_bottomline(void);
GLOBAL void html_footer(void);
GLOBAL _BOOL save_html_index(void);
GLOBAL void add_pass1_index_udo(void);

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
GLOBAL void c_alias(void);


   /* --- misc. --- */

GLOBAL int add_label(const char *label, const _BOOL isn, const _BOOL isp, _BOOL ignore_index, _BOOL ignore_links);
GLOBAL int add_alias(const char *alias, const _BOOL isp, _BOOL referenced);

GLOBAL void string2reference(char *ref, int li, const _BOOL for_toc, const char *pic, const _UWORD uiW, const _UWORD uiH);

 
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
GLOBAL void set_helpid(void);
GLOBAL void set_mapping(void);

GLOBAL void set_chapter_image(void);
GLOBAL void set_chapter_icon(void);
GLOBAL void set_chapter_icon_active(void);
GLOBAL void set_chapter_icon_text(void);

GLOBAL _BOOL add_nodetype_to_toc(int nodetype, const _BOOL popup, const _BOOL invisible);

GLOBAL _BOOL toc_begin_node (const _BOOL popup, const _BOOL invisible);
GLOBAL void toc_end_node(void);
GLOBAL int is_current_node(int tocindex);
GLOBAL int get_toc_counter(void);
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


   /* --- module functions --- */

GLOBAL void init_module_toc_pass2(void);
GLOBAL void init_module_toc(void);
GLOBAL void exit_module_toc(void);

#endif /* __UDOTOC__ */
