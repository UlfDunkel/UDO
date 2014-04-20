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
*    fd  Feb 22: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  May 21: more comments translated
*  2011:
*    fd  Feb 14: - functions add_...node_to_toc() merged into add_nodetype_to_toc()
*                - all set_html_...() functions moved from TOC to TOC_HTML
*  2014:
*    ggs Apr 20: Add Node6
*
******************************************|************************************/

/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#ifndef __CONSTANT_H
#include "constant.h"
#endif





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define MAX_LABEL_LEN      199
#define MAX_NODE_LEN       199            /* v6.3.9 (old: 128) */
#define MAX_FILENAME_LEN    64
#define MAX_IMAGE_LEN      128
#define MAX_COLOR_LEN       16
#define MAX_HELPID_LEN      16

#define TOC_TOC    0                      /* table of content */
#define TOC_NODE1  1                      /* !node */
#define TOC_NODE2  2                      /* !subnode */
#define TOC_NODE3  3                      /* !subsubnode */
#define TOC_NODE4  4                      /* !subsubsubnode */
#define TOC_NODE5  5                      /* !subsubsubsubnode */
#define TOC_NODE6  6                      /* !subsubsubsubsubnode */
#define TOC_NONE   7                      /* neither nor ... :-) */






/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

#ifndef __UDOTOC__
#define __UDOTOC__

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
   BOOLEAN   appendix;                    /* label is in appendix */
   BOOLEAN   is_node;                     /* label is node title */
   BOOLEAN   is_popup;                    /* node is a popup node */
   BOOLEAN   is_alias;                    /* alias name of a node */
   int       tocindex;                    /* belongs to node "toc[tocindex]" */
   BOOLEAN   ignore_links;                /* don't link to this label */
   BOOLEAN   ignore_index;                /* don't index this label (node only!) */
   BOOLEAN   referenced;                  /* TRUE: label has been referenced */
   
}  LABEL,  *pLABEL;



                                          /* New in V6.5.9 [NHz] */
typedef struct _style                     /* style sheets */
{
   char   href[MAX_LABEL_LEN  + 1];       /* Quelle eines Stylesheets */
   char   media[MAX_LABEL_LEN + 1];       /* fuer welches Medium */
   char   title[MAX_LABEL_LEN + 1];       /* Titel eines Stylesheets */
   int    alternate;                      /* Alternate Stylesheet? */
   int    styleindex;                     /* style[1]==1, style[2]==2 etc. */
   int    tocindex;                       /* Gehoert zum Node "toc[tocindex]" */
   
}  STYLE, *pSTYLE;



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
   BOOLEAN   appendix;                    /* TRUE = Steht im Anhang */
   int       toctype;                     /* !node, !subnode, !subsubnode, !subsubsubnode, !subsubsubsubnode */
                                          /* Filename der Sourcecodedatei */   /* V6.5.18 */
   char      source_filename[MYFILE_FULL_LEN];
   long      source_line;                 /* Zeile im Sourcecode ab der der Node beginnt */   /* V6.5.18 */
   char      filename[MAX_FILENAME_LEN+1];/* HTML-Filename */   /* r5pl3 */
   char      dirname[MAX_FILENAME_LEN+1]; /* HTML-Verzeichnisname */   /* r6pl6 */
   char     *keywords;                    /* HTML-Keywords */   /* r5pl3 */
   char     *description;                 /* HTML-Description */   /* r6pl5 */
   char     *robots;                      /* HTML-Robots */   /* V6.5.17 */
   char     *counter_command;             /* HTML-Kommandos fuer Counter */   /* r5pl4 */
   char      backcolor[MAX_COLOR_LEN+1];  /* HTML <BODY BGCOLOR=...> */   /* r6pl1 */
   char      textcolor[MAX_COLOR_LEN+1];  /* HTML <BODY TEXT=...> */   /* r6pl1 */
   char      linkcolor[MAX_COLOR_LEN+1];  /* HTML <BODY LINK=...> */   /* r6pl1 */
   char      alinkcolor[MAX_COLOR_LEN+1]; /* HTML <BODY ALINK=...> */   /* r6pl1 */
   char      vlinkcolor[MAX_COLOR_LEN+1]; /* HTML <BODY VLINK=...> */   /* r6pl1 */
                                          /* HTML <BODY BGCOLOR=...> */   /* r6pl12 */
   char      modern_backcolor[MAX_COLOR_LEN + 1];
                                          /* HTML <BODY TEXT=...> */   /* r6pl12 */
   char      modern_textcolor[MAX_COLOR_LEN + 1];
                                          /* HTML <BODY LINK=...> */   /* r6pl12 */
   char      modern_linkcolor[MAX_COLOR_LEN + 1];
                                          /* HTML <BODY ALINK=...> */   /* r6pl12 */
   char      modern_alinkcolor[MAX_COLOR_LEN + 1];
                                          /* HTML <BODY VLINK=...> */   /* r6pl12 */
   char      modern_vlinkcolor[MAX_COLOR_LEN + 1];
                                          /* HTML <BODY BACKGROUND=...> */   /* r6pl1 */
   char      backimage[MAX_IMAGE_LEN + 1];
                                          /* HTML <style> r6pl15 [NHz] */
   char      style_name[MAX_IMAGE_LEN + 1];
                                          /* HTML < SCRIPT> r6pl15 [NHz] */
   char      script_name[MAX_IMAGE_LEN + 1];
                                          /* HTML < FAVICON> r6pl15 [NHz] */
   char      favicon_name[MAX_IMAGE_LEN + 1];
                                          /* HTML < bgsound> V6.5.20 [GS] */
   char      bgsound[MYFILE_FULL_LEN + 1];

   char     *image;                       /* Grafik anstelle Kapitelnamen */
   UWORD     uiImageWidth;                /* Breite und Hoehe des Bildes */ 
   UWORD     uiImageHeight;
   char     *icon;                        /* Icon fuer modernes Layout */
   UWORD     uiIconWidth;                 /* Breite und Hoehe des Icons */ 
   UWORD     uiIconHeight;
   char     *icon_active;                 /* Icon fuer    -""- (aktive Seite) */
   UWORD     uiIconActiveWidth;           /* Breite und Hoehe des Icons */ 
   UWORD     uiIconActiveHeight;
   char     *icon_text;                   /* Icontext fuer modernes Layout */
   char     *helpid;                      /* Eine Jump-ID, wie ein Alias */
   int       mapping;                     /* Eine Jump-ID fuer WinHelp/IPF */
   BOOLEAN   invisible;                   /* TRUE = Nicht ins Inhaltsverzeichnis */
   BOOLEAN   converted;                   /* Bereits Makros etc. angepasst? */
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
   BOOLEAN   ignore_subtoc;               /* ignore !use_auto_subtoc */
   BOOLEAN   ignore_links;                /* don't link to this page */
   BOOLEAN   ignore_index;                /* don't add this to the index page */
   BOOLEAN   ignore_title;                /* don't create title for this node */
   BOOLEAN   ignore_headline;             /* don't create a header line */
   BOOLEAN   ignore_bottomline;           /* don't create a bottom line */
   BOOLEAN   ignore_footer;               /* don't create a footer line */
   char     *raw_header_filename;         /* */
   char     *raw_footer_filename;         /* */
   BOOLEAN   ignore_raw_header;           /* don't read user-defined header */
   BOOLEAN   ignore_raw_footer;           /* don't read user-defined footer */
   BOOLEAN   has_children;                /* TRUE: this node has subnode(s) */

}  TOCITEM, *pTOCITEM;



typedef struct _reference                 /* auto-reference placeholders */
{
   char   magic[6];                       /* Eine Steuermarke <ESC><0x80+nr> */
   char   entry[MAX_TOKEN_LEN * 2];       /* ergibt max. 256 Zeichen */
   
}  REFERENCE;

#endif /* __UDOTOC__ */






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

GLOBAL BOOLEAN   bInsideAppendix,         /* Ist UDO im Anhang? */
                 bInsideDocument,         /* Ist UDO im Dokument selber? */
                 bInsidePopup;            /* In einem Popup-Node? */

GLOBAL BOOLEAN   called_tableofcontents;  /* Wurde toc ausgegeben? (@toc) */
GLOBAL BOOLEAN   called_subsubsubsubsubnode;

GLOBAL BOOLEAN   uses_tableofcontents;    /* !tableofcontents wird benutzt */

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

                                          /* New in V6.5.9 [NHz] */
GLOBAL STYLE    *style[MAXSTYLES];        /* Array mit Zeigern auf Stylesheets */
GLOBAL int       p1_style_counter;        /* Zaehler */

GLOBAL char     *html_frames_toc_title;   /* V6.5.16 [GS] */
GLOBAL char     *html_frames_con_title;   /* V6.5.16 [GS] */





/*******************************************************************************
*
*     GLOBAL PROTOTYPES
*
******************************************|************************************/

GLOBAL BOOLEAN is_node_link(const char *link, char *node, int *ti, BOOLEAN *isnode, int *li);
GLOBAL int getLabelIndexFromTocIndex(int *li, const int ti);

GLOBAL void reset_refs(void);
GLOBAL void auto_references(char *s, const BOOLEAN for_toc, const char *pic, const UWORD uiWidth, const UWORD uiHeight);

GLOBAL void check_endnode(void);

GLOBAL BOOLEAN check_output_raw_header(void);
GLOBAL BOOLEAN check_output_raw_footer(BOOLEAN lastNode);

GLOBAL void man_headline(void);
GLOBAL void man_bottomline(void);
GLOBAL void stg_headline(const char *numbers, const char *nodename);
GLOBAL void tvh_headline(const char *s);
GLOBAL void output_html_header(const char *t);
GLOBAL void html_save_frameset(void);
GLOBAL void html_headline(void);
GLOBAL void html_bottomline(void);
GLOBAL void html_footer(void);
GLOBAL BOOLEAN save_html_index(void);
GLOBAL void add_pass1_index_udo(void);
GLOBAL void hh_headline(void);
GLOBAL void hh_bottomline(void);
GLOBAL BOOLEAN save_htmlhelp_contents(const char* filename);
GLOBAL BOOLEAN save_htmlhelp_index(const char* filename);


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
/*   GLOBAL void c_subsubtoc(void); */
/*   GLOBAL void c_subsubsubtoc(void); */

GLOBAL void c_listoffigures(void);
GLOBAL void c_listoftables(void);
   /* outputs an auto-generated Table Of Contents */
GLOBAL void c_tableofcontents(void);

GLOBAL BOOLEAN bookmarks_ps(void);


   /* --- output a label in pass 2 --- */

GLOBAL void c_label(void);
GLOBAL void c_alias(void);


   /* --- misc. --- */

GLOBAL BOOLEAN add_label(const char *label, const BOOLEAN isn, const BOOLEAN isp);
GLOBAL BOOLEAN add_alias(const char *alias, const BOOLEAN isp);


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

GLOBAL BOOLEAN add_nodetype_to_toc(int nodetype, const BOOLEAN popup, const BOOLEAN invisible);

GLOBAL BOOLEAN toc_begin_node (const BOOLEAN popup, const BOOLEAN invisible);
GLOBAL void toc_end_node(void);
GLOBAL int is_current_node(int tocindex);
GLOBAL int get_toc_counter(void);
GLOBAL void toc_init_lang(void);


   /* --- output files with Jump IDs for several compilers --- */

GLOBAL BOOLEAN save_htmlhelp_alias(void);
GLOBAL BOOLEAN save_htmlhelp_map(void);
GLOBAL BOOLEAN save_winhelp_map_c(void);
GLOBAL BOOLEAN save_winhelp_map_pas(void);
GLOBAL BOOLEAN save_winhelp_map_vb(void);
GLOBAL BOOLEAN save_winhelp_map_gfa(void);

GLOBAL BOOLEAN save_winhelp4_cnt(void);


   /* --- module check --- */

GLOBAL BOOLEAN check_module_toc_pass1(void);
GLOBAL BOOLEAN check_module_toc_pass2(void);


   /* --- module functions --- */

GLOBAL void init_module_toc_pass2(void);
GLOBAL void init_module_toc(void);
GLOBAL void exit_module_toc(void);


/* +++ EOF +++ */
