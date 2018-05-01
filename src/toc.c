/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : toc.c
*  Symbol prefix: toc
*
*  Description  : This module contains routines which handle chapters, labels, aliases,
*                 table of contents and automatic referencing.
*
*                 Please find a detailed description of all variables in
*                 init_module_toc().
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
*  Co-Authors   : Ulf Dunkel (fd), Martin Elsaesser (ME), Gerhard Stoll (ggs)
*  Write access : fd, ME, ggs
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : -
*
*-------------------------------------------------------------------------------
*  History:
*
*  2008:
*    fd  Nov 14: indexudo.html now capitalizes the A-Z jump labels (issue #76 solved)
*  2009:
*    fd  May 26: closing bracket in <br%s> added
*    fd  Dec 15: do_toptoc() creates a link to the Index page now (should be formatted using CSS commands)
*  2010:
*    fd  Jan 20: - file partly reformatted
*                - save_html_index() now converts labels using label2html()
*    fd  Jan 23: converted all German umlauts in comments into plain ASCII
*    fd  Jan 24: html_footer() handles all 16 combinations of 
*                  webmasterurl, webmastername, webmastermailurl, webmasteremail
*    fd  Jan 25: save_html_index() does no longer list the indexudo page in itself
*    fd  Feb 03: c_label(): issue #84 fixed
*    fd  Feb 04: - c_label(): decision for <dd> now depends on bDescDDOpen
*                - more functions tidied up and reformatted
*    fd  Feb 05: - init_new_toc_entry(): toc[] structure cleared before usage
*                - set_html_keywords(): now uses MAX_TOKEN_LEN, to avoid issues in str2tok
*                - save_html_index(): Index jump line output fixed
*    fd  Feb 06: make_node(): usage of set_inside_node1() generalized
*    fd  Feb 08: - toc_output(): <br> not allowed outside of <li></li>
*                - make_node(): usage of set_inside_node1() restored
*    fd  Feb 09: - toc_output(): rewritten for HTML output (issue #85 fixed)
*                - save_html_index() debugged: (char)thisc
*                - init_toc_forms_numbers(): HTML format strings changed to avoid leading ' '
*                - toc_output() + its sub functions adjusted, using TOCL_HTM / TOCL_TEX
*                - save_html_index(): sorting fixed
*    fd  Feb 12: some octal chars resolved into constant macros
*    fd  Feb 16: CODE_CP1250_lig, sort_CODE_CP1250 added
*    fd  Feb 17: - CODE_437_lig[], sort_CODE_437[] + CODE_850_lig[], sort_CODE_850[] added
*                - CODE_HP_lig[] + sort_CODE_HP[] added
*                - CODE_NEXT_lig[] + sort_CODE_NEXT[] added
*                - win2sys() -> recode_chrtab()
*    fd  Feb 18: - str_UTF_sort_cmp()
*                - save_html_index() uses a new approach with flattened HTML_INDEX.sortname
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 23: - UDO_PL -> UDO_BUILD (no more patchlevels)
*                - unicode2char() adjusted, using ^string instead of local string
*    fd  Mar 01: html_footer(): changes from (ME) reverted - see discussion in UDO_DEV
*    fd  Mar 02: - html_footer(): notes added and mailto: handling enhanced
*                - webmastername    -> domain_name
*                - webmasterurl     -> domain_link
*                - webmasteremail   -> contact_name
*                - webmastermailurl -> contact_link
*    ME  Mar 03: - html_footer(): ..._link strings are complete URL
*                - if contact_link is empty, contact_name is not used to generate
*                  a "mailto:"-link. If the contact_name should be a link, the target
*                  has to be put into contact_link - there was one case in which
*                  contact_name without contact_link generated a link!
*                - use of contact_link for HTML the entries <link rev="made"> and
*                  <link rev="author"> if available
*    ME  Mar 04: - the chars uf lang.today are now quoted to the HTML-Chars
*                  ("M„rz" -> "M&auml;rz") in html_footer()
*    fd  Mar 12: bookmarks_ps(): ugly typo fixed (warned by Linux gcc)
*    ggs Apr 20: c_label: Labels will print out not only in description environment
*    ggs Apr 21: use_short_tocs -> use_compressed_tocs
*    fd  May 17: init_toc_forms_numbers() must no longer close </li> for HTML
*    fd  May 18: - output_html_doctype() no longer writes iso-8859-1 hard-coded
*                - output_html_meta() no longer writes iso-8859-1 hard-coded
*    fd  May 21: add_label(): supports "!label*" which must not be listed in index (#90)
*    ggs Aug 18: get_html_filename: New Parameter, which tells if a page is merged
*    fd  Sep 09: <a name>%s</a> changed to <a name></a>%s to avoid empty links
*  2011:
*    fd  Jan 29: HTML navigation bar output using GIF images no longer writes linefeeds
*                 in order to prevent gaps between images, so you can use images in
*                 segmented control style now.
*    fd  Feb 14: - add_...node_to_toc() merged into add_nodetype_to_toc()
*                - toc_begin_node() adjusted to handle calls from UDO.C
*                - add_nodetype_to_toc() enhanced
*                - all set_html_...() functions moved from TOC to TOC_HTML
*    fd  Feb 15: - more sources tidied up
*                - all *apx_output() functions merged into *toc_output() functions,
*                    which finally outputs the same proper HTML list formattings
*                - bookmarks_ps() simplified
*    fd  Feb 16: - make_*node() functions reformatted
*                - all make_*node() functions merged into new make_nodetype() function
*                - all set_inside_node*() functions merged into new set_inside_node() function
*    fd  Feb 17: - flag typos fixed
*                - all *toc_output() functions merged into toc_output() function
*                - all do_*toc() functions merged into do_toc() function
*                - save_htmlhelp_contents() adjusted for TOC_NODE5
*                - remaining functions reformatted
*                - more function descriptions added
*                - TOC output debugged
*    fd  Feb 19: c_tableofcontents(): tableofcontents command fixed for TeX ("\" -> "\\")
*    fd  Oct 07: toc_output(): avoid unwanted output of \end{itemize} in TeX
*  2013:
*    fd  Oct 23: HTML output now supports HTML5
*    fd  Nov 02: HTML5 output of <img> tags cleaned
*  2014:
*    ggs Apr 20: Add Node6
*    fd  Jun 20: HTML output of navigation bars now writes UDO_nav_xx IDs to anchors
*    fd  Sep 10: HTML TOC output for 6. level debugged (no longer doubles single 6th level entries in TOC)
*    fd  Oct 08: - HTML headlines|bottomlines output now creates unique UDO_nav_xx IDs
*                - HTML 5 no longer outputs <link rev='made'> and <meta name='Email'>
*                - string2reference() debugged: don't create IDs without name
*  2017:
*    fd  Feb 08: using lang.copyright
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
#include <time.h>
#include <ctype.h>
#include "udoport.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "udointl.h"
#include "commands.h"
#include "abo.h"
#include "chr.h"
#include "env.h"
#include "file.h"
#include "img.h"
#include "msg.h"
#include "par.h"
#include "str.h"
#include "sty.h"
#include "tp.h"
#include "udo.h"
#include "upr.h"
#include "gui.h"
#include "debug.h"
#include "cfg.h"
#include "udomem.h"

#include "export.h"
#include "toc.h"





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#if USE_NAME_HASH
#define HASH_SIZE 9973
LOCAL LABEL *hash[HASH_SIZE];
#endif

/*
 * max. references per paragraph,
 * only limited by encoding in add_placeholder()
 * (3 * 6 bits = 2 ^ 18)
 */
#define MAXREFERENCES       0x40000L




/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define TOCL_NONE  0
#define TOCL_HTM   1                      /* used for use_toc_list_commands */
#define TOCL_TEX   2                      /* dito */





/*******************************************************************************
*
*     LOCAL CONSTANTS
*
******************************************|************************************/

LOCAL const char *FRAME_NAME_TOC = "UDOtoc";
LOCAL const char *FRAME_NAME_CON = "UDOcon";

LOCAL const char *FRAME_FILE_TOC = "00toc";
LOCAL const char *FRAME_FILE_CON = "00con";

LOCAL const char *HTML_LABEL_CONTENTS = "UDOTOC";





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _reference                 /* auto-reference placeholders */
{
   char   magic[7];                       /* Eine Steuermarke <ESC><0x80+nr> */
   char   entry[MAX_TOKEN_LEN * 2];       /* ergibt max. 256 Zeichen */
} REFERENCE;


typedef struct   _hmtl_index              /* index output for HTML */
{
   int       toc_index;                   /* # of found label for TOC */
   _BOOL   is_node;                     /* the label is the caption (?) */
   char      tocname[512];                /* label or node name */
   char      sortname[512];               /* 'flattened' label or node name */
   _UWORD     codepoint;                   /* Unicode codepoint for sorting purposes */
} HTML_INDEX;

typedef struct _tWinMapData
{
   char   remOn[16],                      /* */
          remOff[16];                     /* */
   char   cmd[32];                        /* #define const */
   char   varOp[16];                      /*  = */
   char   hexPre[16],                     /* */
          hexSuf[16];                     /* 0x $ */
   char   compiler[32];                   /* C, Pascal, Visual-Basic, ... */
   }  tWinMapData;

typedef struct _hmtl_idx
{
   int    toc_index;
   char   tocname[512];
} HTML_IDX;





/*******************************************************************************
*
*     LOCAL VARIABLES
*
******************************************|************************************/

LOCAL _BOOL    toc_available;           /* Inhaltsverzeichnis existiert */
LOCAL _BOOL    apx_available;           /* Anhang existiert */
LOCAL _BOOL    head_foot;               /* TRUE: HEAD output, FALSE: FOOT */

LOCAL int        p1_toctype;              /* Typ des aktuellen Kapitels */
LOCAL int        p2_toctype;              /* Typ des aktuellen Kapitels */

LOCAL LABEL     *lab[MAXLABELS];          /* Array mit Zeigern auf Labels */
LOCAL int        p1_lab_counter;          /* Zaehler */
LOCAL int        p2_lab_counter;          /* Zaehler, 2. Durchgang */

LOCAL REFERENCE *refs;                    /* Referenzen */
LOCAL size_t     refs_counter;            /* # of used references */
LOCAL size_t     refs_alloc;              /* # of allocated references */

                                          /* absolut */
LOCAL int         p1_toc_n1, p1_toc_n2, p1_toc_n3, p1_toc_n4, p1_toc_n5, p1_toc_n6;
LOCAL int         p1_apx_n1, p1_apx_n2, p1_apx_n3, p1_apx_n4, p1_apx_n5, p1_apx_n6;

                                          /* Anzeige */
LOCAL int         p1_toc_nr1, p1_toc_nr2, p1_toc_nr3, p1_toc_nr4, p1_toc_nr5, p1_toc_nr6;
LOCAL int         p1_apx_nr1, p1_apx_nr2, p1_apx_nr3, p1_apx_nr4, p1_apx_nr5, p1_apx_nr6;

LOCAL int         p2_toc_n1, p2_toc_n2, p2_toc_n3, p2_toc_n4, p2_toc_n5, p2_toc_n6;
LOCAL int         p2_apx_n1, p2_apx_n2, p2_apx_n3, p2_apx_n4, p2_apx_n5, p2_apx_n6;

LOCAL int         curr_n1_index;
LOCAL int         curr_n2_index;
LOCAL int         curr_n3_index;
LOCAL int         curr_n4_index;
LOCAL int         curr_n5_index;
LOCAL int         curr_n6_index;

LOCAL int         last_n1_index;          /* toc[]-Indizes fuer Titelzeilen */
LOCAL int         last_n2_index;
LOCAL int         last_n3_index;
LOCAL int         last_n4_index;
LOCAL int         last_n5_index;
LOCAL int         last_n6_index;

LOCAL int         active_nodetype;        /* Flag fuer check_endnode() */

LOCAL char        form_t1_n1[80], form_t1_n2[80], form_t1_n3[80], form_t1_n4[80], form_t1_n5[80], form_t1_n6[80];
LOCAL char        form_t2_n2[80], form_t2_n3[80], form_t2_n4[80], form_t2_n5[80], form_t2_n6[80];
LOCAL char        form_t3_n3[80], form_t3_n4[80], form_t3_n5[80], form_t3_n6[80];
LOCAL char        form_t4_n4[80], form_t4_n5[80], form_t4_n6[80];
LOCAL char        form_t5_n5[80], form_t5_n6[80];
LOCAL char        form_t6_n6[80];

LOCAL char        form_a1_n1[80], form_a1_n2[80], form_a1_n3[80], form_a1_n4[80], form_a1_n5[80], form_a1_n6[80];
LOCAL char        form_a2_n2[80], form_a2_n3[80], form_a2_n4[80], form_a2_n5[80], form_a2_n6[80];
LOCAL char        form_a3_n3[80], form_a3_n4[80], form_a3_n5[80], form_a3_n6[80];
LOCAL char        form_a4_n4[80], form_a4_n5[80], form_a4_n6[80];
LOCAL char        form_a5_n5[80], form_a5_n6[80];
LOCAL char        form_a6_n6[80];

LOCAL char        toc_list_top[64],       /* */
                  toc_list_end[64];       /*r6pl2*/
LOCAL char        use_toc_list_commands;  /* TOCL_HTM | TOCL_TEX | 0 */

LOCAL char        allowed_next_chars[64]; /* r5pl10 */
LOCAL char        allowed_prev_chars[64];

LOCAL char        footer_buffer[512];     /* Puffer fuer den Footer */ /*r6pl2 */

LOCAL char        html_target[64];

LOCAL char encode_chars[64] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#=";





/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

   /* check if certain values are valid */
LOCAL _BOOL check_toc_counters(void);
   /* check if certain values are valid */
LOCAL _BOOL check_toc_and_token(void);

   /* output aliasses of a chapter */
LOCAL void output_aliasses(void);

   /*  */
LOCAL _BOOL add_ref(const char *r);
   /*  */
LOCAL void replace_refs(char *s);

   /* read raw file and output it unchanged */
LOCAL _BOOL output_raw_file(const char *filename);

   /* output header for ST-Guide */
LOCAL void stg_header(const char *numbers, const char *nodename, _BOOL is_popup);

   /* output topline for PC-HELP */
LOCAL void pch_headline(char *s);
   /* output bottomline for PC-HELP */
LOCAL void pch_bottomline(void);

   /* output bottomline for Turbo-Vision-Help */
LOCAL void tvh_bottomline(void);
   /* create header for Turbo-Vision-Help node */
LOCAL void output_vision_header(const char *numbers, const char *name);

   /* output nodeline for TeXinfo */
LOCAL void output_texinfo_node(const char *name);

   /* get filename for HTML according to current node */
LOCAL char *get_html_filename(const int tocindex, char *s, int *html_merge);
   /* output HTML meta data in the HTML head section */
LOCAL void output_html_meta(_BOOL keywords);
   /* output HTML doctype in HTML header */
LOCAL void output_html_doctype(void);
   /* create new HTML file and output header and meta information */
LOCAL _BOOL html_make_file(void);
   /*  */
LOCAL _BOOL html_new_file(void);
LOCAL void html_index_giflink(const int idxEnabled, const int idxDisabled, const char *sep, _BOOL head);
   /* create and output HOME link for HTML navigation bar */
LOCAL void html_home_giflink(const int idxEnabled, const int idxDisabled, const char *sep, _BOOL head);
   /* create and output link to 'back page' for HTML navigation bar */
LOCAL void html_back_giflink(const int idxEnabled, const int idxDisabled, const char *sep, _BOOL head);
   /* create and output HTML head and bottom bar lines */
LOCAL void html_node_bar_modern(void);
   /*  */
LOCAL void html_node_bar_frames(void);

   /* sets active_nodetype variable */
LOCAL void set_inside_node(int nodetype);

   /* create a new node of the requested depth */
LOCAL void make_nodetype(int nodetype, const _BOOL popup, const _BOOL invisible);

   /* make TOC entry line bold */
LOCAL void tocline_make_bold(char *s, const int depth);
   /* output start of TOC listing head if the first item is going to be output */
LOCAL void tocline_handle_1st(_BOOL *f);
   /* remove all formatting stuff from a node name */
LOCAL void convert_toc_item(TOCITEM *t);
   /* output the Appendix title line */
LOCAL void output_appendix_line(void);
   /*  */
LOCAL void toc_link_output(const int depth ); /* New in r6pl16 [NHz] */

   /* create output for all !use_auto_...tocs commands */
LOCAL void toc_output(int nodetype, const int depth, _BOOL apx);
   /* wrapper for toc_output() */
LOCAL void do_toc(int nodetype, const int depth);
   /* outputs the breadcrumb navigation links for the current chapter */
LOCAL void do_toptoc(const int current_node, _BOOL popup);
   /* get the user-defined TOC depth, set by the !depth command */
LOCAL int get_toccmd_depth(void);
   /* initialize a new TOC entry */
LOCAL TOCITEM *init_new_toc_entry(const int toctype, const _BOOL invisible);
   /* add TOC page (indexudo) to toc[0] */
LOCAL _BOOL add_toc_to_toc(void);
   /* exit TOC module */
/* LOCAL void free_toc_data(char **var ); */











/*******************************************************************************
*
*     LOCAL PROCEDURES
*
******************************************|************************************/

#if USE_NAME_HASH
LOCAL _UWORD hash_val(const char *name)
{
   _UWORD val;
    
   val = 0;
   while (*name != '\0')
   {
      val += (_UWORD)(unsigned char)(*name);
      name++;
   }
   return val % HASH_SIZE;
}
#endif /* USE_NAME_HASH */




/*******************************************************************************
*
*  check_toc_counters():
*     check if certain values are valid
*
*  Return:
*     FALSE: any checked value was invalid
*      TRUE: everything's fine
*
******************************************|************************************/

LOCAL _BOOL check_toc_counters(void)
{
   if (p1_toc_counter < 0)
      return FALSE;
      
   if (toc[p1_toc_counter] == NULL)
      return FALSE;
      
   return TRUE;
}





/*******************************************************************************
*
*  check_toc_and_token():
*     check if certain values are valid
*
*  Return:
*     FALSE: any checked value was invalid
*      TRUE: everything's fine
*
******************************************|************************************/

LOCAL _BOOL check_toc_and_token(void)
{
   if (p1_toc_counter < 0)
      return FALSE;
      
   if (toc[p1_toc_counter] == NULL)
      return FALSE;
      
   if (token[1][0] == EOS)
      return FALSE;
   
   return TRUE;
}





/*******************************************************************************
*
*  is_node_link():
*     Zu welchem Node gehoert ein Label (fuer ST-Guide, Texinfo, Pure-C-Help)
*
* @link: link text name
* @node: node name which uses this label
* @isnode: TRUE: is node, FALSE: is label or alias
* @ti: TOC index of node/label/alias
* @li: LAB index of node/label/alias
*
* @Return:
*      TRUE: label exists
*     FALSE: label doesn't exist
*
******************************************|************************************/

GLOBAL _BOOL is_node_link(const char *link, char *node, int *ti, _BOOL *isnode, _BOOL *isalias, _BOOL *ispopup, int *li)
{
   _BOOL ret = FALSE;
   
   node[0] = EOS;
   *isnode = FALSE;
   *isalias = FALSE;
   *ispopup = FALSE;
   
   if (link[0] == EOS)
   {
      return FALSE;
   }
   
#if USE_NAME_HASH
   {
      _UWORD hash_index;
      LABEL *l;
        
      hash_index = hash_val(link);
      l = hash[hash_index];
      while (l != NULL)
      {
         if (strcmp(l->name, link) == 0)
         {
            *isnode = l->is_node;
            *isalias = l->is_alias;
            *ispopup = l->is_popup;
            *li = l->labindex;
            *ti = l->tocindex;
            l->referenced = TRUE;
            strcpy(node, toc[*ti]->name);
            ret = TRUE;
            break;
         }
         l = l->next_hash;
      }
   }
#else
   {
      int i;
   
      for (i = 1; i <= p1_lab_counter; i++)
      {
         if (strcmp(lab[i]->name, link) == 0)
         {
            *isnode = lab[i]->is_node;
            *isalias = lab[i]->is_alias;
            *ispopup = lab[i]->is_popup;
            *li = i;
            *ti = lab[i]->tocindex;
            lab[i]->referenced = TRUE;
            strcpy(node, toc[*ti]->name);
            ret = TRUE;
            break;
         }
      }
   }
#endif

   return ret;
}





/*******************************************************************************
*
*  getLabelIndexFromTocIndex():
*     ??? (description missing)
*
*  return:
*     ???
*
******************************************|************************************/

GLOBAL int getLabelIndexFromTocIndex(

int        *li,  /* */
const int   ti)  /* */
{
   *li = toc[ti]->labindex;
    return *li;
}





/*******************************************************************************
*
*  output_helpid():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_helpid(

int      tocindex)  /* */
{
   char  s[256];    /* */

   s[0] = '\0';
   
   if (toc[tocindex]->helpid != NULL)
   {
      um_strcpy(s, toc[tocindex]->helpid, 256, "output_helpid[1]");
   }
   else if (use_auto_helpids)
   {
      node2WinAutoID(s, toc[tocindex]->name);
   }
   
   if (s[0] != '\0')
   {
      switch (desttype)
      {
      case TOSTG:
      case TOAMG:
         voutlnf("@alias \"%s\"", s);
         break;
         
      case TOWIN:
      case TOWH4:
      case TOAQV:
         voutlnf("#{\\footnote # %s}", s);
         break;
      
      case TOHAH:                         /* V6.5.17 */
      case TOHTM:
      case TOMHH:
         label2html(s);                   /*r6pl2*/
         
         if (html_doctype == HTML5)
         {
            voutlnf("<a id=\"%s\"></a>", s);
         }
         else
         {
            voutlnf("<a name=\"%s\"></a>", s);
         }

         break;  
      
      case TOLDS:
         voutlnf("<label id=\"%s\">", s);
         break;
         
      case TOTEX:                         /* r5pl9 */
      case TOPDL:
         voutlnf("\\label{%s}", s);
         break;
         
      case TOLYX:                         /* <???> */
         break;
      }
   }
}





/*******************************************************************************
*
*  output_aliasses():
*     output aliasses of a chapter
*
*  Note:
*     Diese muessen nach der Node-Angabe erfolgen.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_aliasses(void)
{
   register int   i;             /* */
   int            start;         /* */
   char           s[256],        /* */
                  keyword[256];  /* */
   
   /* Fuer Pure C Help und Turbo Vision Help werden die Aliasse zusammen */
   /* mit *nodes ausgegeben */
   
/* #if 1 */
   start = toc[p2_toc_counter]->labindex; /* r6pl2 */
/* #else
   start = 1;
#endif */
   
   if (start <= 0)
      return;
   
   for (i = start; i <= p1_lab_counter; i++)
   {
                                          /* r5pl6: aktuellen Zaehler mit Alias-Zugehoerigkeit vergleichen */
      if (lab[i]->is_alias && p2_toc_counter == lab[i]->tocindex)
      {
         switch (desttype)
         {
         case TOSTG:
            strcpy(s, lab[i]->name);
            node2stg(s);
            convert_tilde(s);
            voutlnf("@alias \"%s\"", s);
            break;
            
         case TOWIN:
         case TOWH4:
         case TOAQV:
            um_strcpy(s, lab[i]->name, 256, "output_aliasses[1]");
            del_internal_styles(s);
            convert_tilde(s);
            
            if (use_alias_inside_index && !no_index)
            {
               um_strcpy(keyword, s, 256, "output_aliasses[2]");
               winspecials2ascii(keyword);
               voutlnf("K{\\footnote K %s}", keyword);
            }
            
            alias2NrWinhelp(s, i);
            voutlnf("#{\\footnote # %s}", s);
            
            if (bDocWinOldKeywords)
            {
               um_strcpy(s, lab[i]->name, 256, "output_aliasses[3]");
               del_internal_styles(s);
               node2winhelp(s);
               voutlnf("#{\\footnote # %s}", s);
            }
            
            break;
            
         case TORTF:
            um_strcpy(s, lab[i]->name, 256, "output_aliasses[4]");
            del_internal_styles(s);
            convert_tilde(s);
            
            if (use_alias_inside_index && !no_index)
            {
               um_strcpy(keyword, s, 256, "output_aliasses[5]");
               winspecials2ascii(keyword);
               voutlnf("{\\xe\\v %s}", keyword);
            }
            
            break;
            
         case TOHAH:                      /* V6.5.17 */
         case TOHTM:
         case TOMHH:
            um_strcpy(s, lab[i]->name, 256, "output_aliasses [6]");
            convert_tilde(s);
            
            label2html(s);                /* r6pl2 */

            if (html_doctype == HTML5)
            {
               voutlnf("<a id=\"%s\"></a>", s);
            }
            else
            {
               voutlnf("<a name=\"%s\"></a>", s);
            }

            break;
            
         case TOLDS:
            um_strcpy(s, lab[i]->name, 256, "output_aliasses[7]");
            convert_tilde(s);
            voutlnf("<label id=\"%s\">", s);
            break;
            
         case TOTEX:                      /* r5pl9 */
         case TOPDL:
            um_strcpy(s, lab[i]->name, 256, "output_aliasses[8]");
            convert_tilde(s);
            label2tex(s);
            voutlnf("\\label{%s}", s);
            break;
            
         case TOLYX:                      /* <???> */
            break;
         }
      }
   }
   
   output_helpid(p2_toc_counter);         /* r6pl2: Jump-ID ausgeben */
}





/*******************************************************************************
*
*  reset_refs():
*     allgemeine Referenz-Routinen
*
*  Bei Formaten, bei denen Nodes und Labels selbstaendig referenziert werden muessen,
*  koennen folgende Routinen benutzt werden.
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void reset_refs(void)
{
   register size_t i;

   for (i = 0; i < refs_counter; i++)
   {
      refs[i].entry[0] = EOS;
      refs[i].magic[0] = EOS;
   }
   
   refs_counter = 0;
}





/*******************************************************************************
*
*  add_ref():
*     ??? (description missing)
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL add_ref(const char *r)
{
   size_t counter;
   unsigned char c1, c2, c3;
   REFERENCE *new_refs;
   
   counter = refs_counter;
   if (counter >= MAXREFERENCES)
      return FALSE;
   
   /*
    * when encoding, be sure not to generate
    * \033, '~' or \177 characters,
    * or any sequence of characters that
    * might me interpreted as an UDO command
    */
   c1 = encode_chars[((counter >> 12) & 0x3f)];
   c2 = encode_chars[((counter >>  6) & 0x3f)];
   c3 = encode_chars[((counter      ) & 0x3f)];
   if (counter >= refs_alloc)
   {
      size_t new_alloc = refs_alloc + 100;
      new_refs = (REFERENCE *)realloc(refs, new_alloc * sizeof(REFERENCE));
      if (new_refs == NULL)
      {
         return FALSE;
      }
      refs = new_refs;
      refs_alloc = new_alloc;
   }

   sprintf(refs[counter].magic, "\033%c%c%c%c\033", C_REF_MAGIC, c1, c2, c3);
   strcpy(refs[counter].entry, r);
   
   refs_counter++;
   
   return TRUE;
}




/*******************************************************************************
*
*  replace_refs():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void replace_refs(char *s)
{
   register size_t i;
   
   for (i = 0; i < refs_counter; i++)
   {
      replace_once(s, refs[i].magic, refs[i].entry);
   }
}





/*******************************************************************************
*
*  string2reference():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

void string2reference(

char           *ref,                 /* */
int li,
const _BOOL   for_toc,             /* */
const char     *pic,                 /* constant for GUI navigation image, e.g. GIF_UP_NAME */
const _UWORD     uiW,                 /* GUI navigation image width */
const _UWORD     uiH)                 /* GUI navigation image height */
{
   const LABEL   *l = lab[li];
   char         s[512],              /* */
                n[512],              /* */
                sNoSty[512],         /* */
                hfn[512],            /* */
                sGifSize[80];        /* */
   char         sIDName[32];         /* string buffer for anchor ID name, e.g. "id=\"UDO_nav_lf\" " */
   int          ti,                  /* */
                ui;                  /* */
   _BOOL      same_file = FALSE;   /* TRUE: reference is in same file */
   char        *htmlfilename,        /* */
                                     /* */
                suff[MYFILE_SUFF_LEN + 1];
   char         closer[8] = "\0";    /* single tag closer mark in XHTML */
   
   
   if (!strcmp(pic, GIF_UP_NAME))
      strcpy(sIDName, " id=\"UDO_nav_up");
   else if (!strcmp(pic, GIF_LF_NAME))
      strcpy(sIDName, " id=\"UDO_nav_lf");
   else if (!strcmp(pic, GIF_RG_NAME))
      strcpy(sIDName, " id=\"UDO_nav_rg");
   else
      sIDName[0] = 0;                     /* empty C string */

   /* mark ID as unique */
   if (sIDName[0] > 0)
   {
      if (head_foot)
         strcat(sIDName, "_HEAD\"");
      else
         strcat(sIDName, "_FOOT\"");
   }

   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   ref[0] = EOS;
   
   switch (desttype)
   {
   case TOWIN:
   case TOWH4:
   case TOAQV:
      um_strcpy(n, l->name, 512, "string2reference[1]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      
      if (l->is_node)
      {
         node2NrWinhelp(s, l->labindex);
      }
      else
      {
         if (l->is_alias)
         {
            alias2NrWinhelp(s, l->labindex);
         }
         else
         {
            label2NrWinhelp(s, l->labindex);
         }
      }
      
      if (l->is_popup)
      {
         sprintf(ref, "{\\ul %s}{\\v %s}", n, s);
      }
      else
      {
         sprintf(ref, "{\\uldb %s}{\\v %s}", n, s);
      }
      
      break;

      
   case TOIPF:                            /* r6pl7 */
      um_strcpy(n, l->name, 512, "string2reference[2]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      
      if (l->is_node)
      {
        node2NrIPF(s, l->labindex);
      }
      else
      {
        ui = l->tocindex;
         node2NrIPF(s, toc[ui]->labindex);
      }
                                          /*r6pl8*/
      sprintf(ref, ":link refid=%s reftype=hd.%s:elink.", s, n);
      break;
      
      
   case TOSTG:                            /* r5pl16 */
      if (l->ignore_links)
      {
         um_strcpy(n, l->name, 512, "string2reference[3]");
         replace_udo_tilde(n);
         replace_udo_nbsp(n);
         node2stg(n);
         sprintf(ref, "@{\"%s\" link \"%s\"}", n, n);
      }
      else
      {                                   /* wie bei default */
         strcpy(ref, l->name);
         replace_udo_tilde(ref);
         replace_udo_nbsp(ref);
      }
      
      break;
      
      
   case TOAMG:
      um_strcpy(s, l->name, 512, "string2reference[4]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      
      if (l->is_node)
      {
         strcpy(n, l->name);
      }
      else
      {
         ti = l->tocindex;
         um_strcpy(n, lab[toc[ti]->labindex]->name, 512, "string2reference[5]");
      }
      
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      node2stg(n);
      sprintf(ref, "@{\"%s\" link \"%s\"}", s, n);
      break;
      
      
   case TOTVH:
      um_strcpy(n, l->name, 512, "string2reference[6]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      um_strcpy(s, n, 512, "string2reference[7]");
      node2vision(s);
      sprintf(ref, "{%s:%s}", n, s);
      break;
      
      
   case TOPCH:
      um_strcpy(n, l->name, 512, "string2reference[8]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      
      if (strchr(n, '"') != NULL)
      {
         um_strcpy(s, n, 512, "string2reference[9]");
         node2pchelp(s);
         sprintf(ref, "\\link(\"%s\")%s\\#", s, n);
      }
      else
      {
         sprintf(ref, "\\#%s\\#", n);
      }
      
      if (!for_toc)
      {                                   /* r5pl10: Referenz als Platzhalter anlegen, damit der */
                                          /* Blocksatz korrekt wird. */
         insert_placeholder(ref, ref, ref, n);
      }
      
      break;
      
      
   case TOLDS:
      um_strcpy(n, l->name, 512, "string2reference[10]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      sprintf(ref, "<ref id=\"%s\" name=\"%s\">", n, n);
      break;
      
      
   case TOINF:
      um_strcpy(n, l->name, 512, "string2reference[11]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      node2texinfo(n);
      sprintf(ref, "* %s::", n);
      break;
      
      
   case TOHAH:                            /* V6.5.17 */
   case TOHTM:
   case TOMHH:
      um_strcpy(n, l->name, 512, "string2reference[12]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      
      um_strcpy(sNoSty, n, 512, "string2reference[13]");
      del_html_styles(sNoSty);
      
      label2html(sNoSty);
      
      ti = l->tocindex;
      
      /* Hier auch das Mergen beachten! */
      ui = ti;                            /* upper index = toc index */

      if (html_merge_node6 && toc[ti]->toctype == TOC_NODE6)
         ui = toc[ti]->up_n5_index;
      
      if (html_merge_node5 && toc[ti]->toctype == TOC_NODE5)
         ui = toc[ti]->up_n4_index;

      if (html_merge_node4 && toc[ti]->toctype == TOC_NODE4)
         ui = toc[ti]->up_n3_index;
      
      if (html_merge_node3 && toc[ti]->toctype == TOC_NODE3)
         ui = toc[ti]->up_n2_index;
      
      if (html_merge_node2 && toc[ti]->toctype == TOC_NODE2)
         ui = toc[ti]->up_n1_index;
      
      if (html_merge_node1)
         ui = 0;
      
      if (ui == 0)
      {
         um_strcpy(hfn, outfile.name, 512, "string2reference[14]");
         htmlfilename = hfn;
      }
      else
      {
/* #if 1 */
         sprintf(hfn, "%s%s", html_name_prefix, toc[ui]->filename);
         htmlfilename = hfn;
/*
#else
         htmlfilename = toc[ui]->filename;
#endif
*/
      }
      
                                          /* Feststellen, ob die Referenz im gleichen File liegt */
      if (strcmp(htmlfilename, outfile.name) == 0)
      {
         same_file = TRUE;
      }
      
                                          /* New in r6pl16 [NHz] */
      if (strchr(htmlfilename, '.') != NULL)
         strcpy(suff, "");
      else
         strcpy(suff, outfile.suff);
      
      if (pic[0] != EOS)                  /* GUI navigation */
      {
         if (no_images)                   /*r6pl2*/
         {
            if (l->is_node || l->is_alias)
            {
                                          /* Changed in r6pl16 [NHz] */
               sprintf(ref, "<a%s href=\"%s%s\"%s>%s</a>",
                  sIDName, htmlfilename, suff, html_target, n);
            }
            else
            {
                                          /* Changed in r6pl16 [NHz] */
               sprintf(ref, "<a%s href=\"%s%s#%s\"%s>%s</a>",
                  sIDName, htmlfilename, suff, sNoSty, html_target, n);
            }
         }
         else
         {      
            sGifSize[0] = EOS;
            
            if (uiW != 0 && uiH != 0)
            {
               sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
            }
            
            if (l->is_node || l->is_alias)
            {
               if (html_doctype == HTML5)
               {
                  sprintf(ref, "<a%s href=\"%s%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s></a>", 
                     sIDName, htmlfilename, suff, html_target, pic, n, n, sGifSize, closer);
               }
               else
               {
                  sprintf(ref, "<a%s href=\"%s%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s></a>", 
                     sIDName, htmlfilename, suff, html_target, pic, n, n, sGifSize, closer);
               }
            }
            else
            {
            	if (html_doctype == HTML5)
            	{
                  sprintf(ref, "<a%s href=\"%s%s#%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s></a>",
                     sIDName, htmlfilename, suff, sNoSty, html_target, pic, n, n, sGifSize, closer);
            	}
            	else
            	{
                  sprintf(ref, "<a%s href=\"%s%s#%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s></a>",
                     sIDName, htmlfilename, suff, sNoSty, html_target, pic, n, n, sGifSize, closer);
               }
            }
         }
      }
      else
      {
         if (l->is_node || l->is_alias)
         {
            if (same_file)
            {
               sprintf(ref, "<a%s href=\"#%s\"%s>%s</a>", 
                  sIDName, sNoSty, html_target, n);
            }
            else
            {                             /* Hier muss noch unterschieden werden, wenn */
                                          /* gemerged wird. Dann ein # einfuegen!!!! */
                                          /* ti oben bereits aus tocindex gesetzt */
               if (    (html_merge_node2 && toc[ti]->n2 > 0)
                    || (html_merge_node3 && toc[ti]->n3 > 0)
                    || (html_merge_node4 && toc[ti]->n4 > 0)
                    || (html_merge_node5 && toc[ti]->n5 > 0)
                    || (html_merge_node6 && toc[ti]->n6 > 0)
                 )
               {
                                          /* Changed in r6pl16 [NHz] */
                  sprintf(ref, "<a%s href=\"%s%s#%s\"%s>%s</a>",
                     sIDName, htmlfilename, suff, sNoSty, html_target, n);
               }
               else
               {
                                          /* Changed in r6pl16 [NHz] */
                  sprintf(ref, "<a%s href=\"%s%s\"%s>%s</a>",
                     sIDName, htmlfilename, suff, html_target, n);
               }
            }
         }
         else
         {
                                          /* Changed in r6pl16 [NHz] */
            sprintf(ref, "<a%s href=\"%s%s#%s\"%s>%s</a>",
               sIDName, htmlfilename, suff, sNoSty, html_target, n);
         }
      }
      
      break;
      
   case TOTEX:
      strcpy(ref, l->name);
      replace_udo_tilde(ref);
      replace_udo_nbsp(ref);
      break;
      
   case TOPDL:
      um_strcpy(n, l->name, 512, "string2reference[15]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      
                                          /* Changed in r6.2pl1 [NHz] */
                                          /* V6.5.20 [CS] Start */
      sprintf(ref, "%s \\hidelink{\\pdfstartlink goto num %d %s\\pdfendlink}", n, l->labindex, n);
      
/* old:
      sprintf(ref, "{\\pdfstartlink goto num %d\n%s\\pdfendlink}",
      l->labindex, n);
*/
      break;
      
                                          /* New in r6pl15 [NHz] */
   case TOKPS:
      um_strcpy(n, l->name, 512, "string2reference[16]");
      replace_udo_tilde(n);
      replace_udo_nbsp(n);
      
      if (strpbrk(n, " :;\\()/") != NULL)
      {
         um_strcpy(s, n, 512, "string2reference[17]");
         node2postscript(n, KPS_CONTENT); /* New in r6pl16 [NHz] */
         node2postscript(s, KPS_NAMEDEST);/* Changed in r6pl16 [NHz] */
         sprintf(ref, " (%s) /%s 0 0 0 Link", n, s);
      }
      else
      {
         sprintf(ref, " (%s) /%s 0 0 0 Link", n, n);
      }
      
      if (!for_toc)
      {
                                          /* r5pl10: Referenz als Platzhalter anlegen, damit der */
                                          /* Blocksatz korrekt wird. */
         insert_placeholder(ref, ref, ref, n);
      }
      
      break;
      
   default:
      strcpy(ref, l->name);
      replace_udo_tilde(ref);
      replace_udo_nbsp(ref);
   }
}





/*******************************************************************************
*
*  auto_references():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void auto_references(

char             *s,             /* ^ string to check */
const _BOOL     for_toc,       /* TRUE: use auto reference for TOC */
const char       *pic,           /* also images can be referenced (used in string2reference()) */
const _UWORD       uiWidth,       /* image width */
const _UWORD       uiHeight)      /* image height */
{
   register int   i;             /* counter */
   char           the_ref[512],  /* */
                 *pos,           /* */
                 *ptr,           /* */
                 *found_pos,     /* */
                 *searchpos;     /* */
   char           nextchar,      /* */
                  prevchar;      /* */
   int            found_lab;     /* */
   size_t         found_len,     /* */
                  ll;            /* */
   _BOOL        ref_it;        /* */
   _BOOL        ignore_it;     /* */
   _BOOL        next_ok,       /* */
                  prev_ok;       /* */
   _BOOL        found_one,     /* */
                  found_ok;      /* */
   LABEL         *labptr;        /* */
   
   
   if (bDocAutorefOff)                    /* it's so simple! */
      return;
   
   
   
   /* Automatische Referenzen werden nur fuer Inhaltsverzeichnisse */
   /* gesetzt. Andere Referenzen muessen wie bei TeX mit !link */
   /* manuell erzeugt werden! */

   if (desttype == TOINF && !for_toc)
      return;
   
   reset_refs();
   
   do
   {
      found_lab = -1;
      found_len =  0;
      found_pos =  s;
   
      for (i = 1; i < MAXLABELS; i++)
      {
         labptr = lab[i];
   
         if (labptr == NULL)
            break;
   
                                          /* r5pl15 */
         if (for_toc || (!for_toc && !labptr->ignore_links))
         {
            searchpos = s;
   
            found_one = TRUE;
            found_ok  = FALSE;
            
            while (found_one && !found_ok)
            {
               ptr = searchpos;
            
               while ( (pos = strstr(ptr, labptr->name)) != NULL)
               {
                  ignore_it = FALSE;
            
                  if ( pos - 2 >= s)
                  {
                                          /* r5pl9: vorher <' ' */
                     if (pos[-2] == ESC_C && pos[-1] < BS_C)
                     {
                        ptr = pos + 2;
                        ignore_it = TRUE;
                     }
                  }
            
                  if (!ignore_it)
                     break;
               }
   
               if (pos != NULL)
               {
                  found_one = TRUE;
   
                  ll = labptr->len;       /* r5pl10: Laenge wird in add_label() vorberechnet */
   
                  if (ll > found_len)
                  {
                     nextchar = pos[ll];

                     if (pos == s)
                        prevchar = EOS;
                     else
                        prevchar = pos[-1];
   
                     prev_ok = (prevchar == EOS || strchr(allowed_prev_chars, prevchar) != NULL);
                     next_ok = (nextchar == EOS || strchr(allowed_next_chars, nextchar) != NULL);
   
                     if (prev_ok && next_ok)
                     {
                        found_lab = i;
                        found_len = ll;
                        found_pos = pos;
                        found_ok  = TRUE;
                     }
                     else
                     {
                        searchpos = pos + 1;
                        found_ok  = FALSE;
                     }
                  }
                  else
                  {
                     searchpos = pos + 1;
                     found_ok  = FALSE;
                     
                  }  /* ll > found_len */
                  
               }
               else
               {
                  /* pos == NULL */
                  found_one = FALSE;
                  found_ok  = FALSE;
                  searchpos += labptr->len;
               }
   
            }  /* while (!found_and_ok) */
   
         }  /* !ignore_links */
   
      }  /* for */
   
      if (found_lab >= 0)
      {
         ref_it = TRUE;
                                          /* r6pl9 */
         lab[found_lab]->referenced = TRUE;
   
         /* Hier dafuer sorgen, dass nicht innerhalb eines Nodes */
         /* referenziert wird, wenn man nicht im Inhaltsverzeichnis ist */
   
         if (!for_toc)
         {
            if (p2_toc_counter == lab[found_lab]->tocindex)
            {
               ref_it = FALSE;
            }
         }
   
         if (ref_it)
         {
            string2reference(the_ref, found_lab, for_toc, pic, uiWidth, uiHeight);
            add_ref(the_ref);
         }
         else
         {
            add_ref(lab[found_lab]->name);
         }
   
         replace_once(found_pos, lab[found_lab]->name, refs[refs_counter - 1].magic);
   
      }  /* found_lab>=0 */
   
   }  while (found_lab>=0);
   
   replace_refs(s);
}





/*******************************************************************************
*
*  check_endnode():
*     Ende eines Kapitels testen und ggf. setzen
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void check_endnode(void)
{
   if (active_nodetype != TOC_NONE)
   {
      switch (active_nodetype)
      {
      case TOC_NODE1:
         if (use_auto_subtocs)
            do_toc(TOC_NODE2, subtocs1_depth);
            
         break;
         
      case TOC_NODE2:
         if (use_auto_subsubtocs)
            do_toc(TOC_NODE3, subtocs2_depth);
            
         break;
         
      case TOC_NODE3:
         if (use_auto_subsubsubtocs)
            do_toc(TOC_NODE4, subtocs3_depth);
            
         break;
         
      case TOC_NODE4:
         if (use_auto_subsubsubsubtocs)
            do_toc(TOC_NODE5, subtocs4_depth);
            
         break;

      case TOC_NODE5:
         if (use_auto_subsubsubsubsubtocs)
            do_toc(TOC_NODE6, subtocs5_depth);
            
         break;
      }
      
      switch (desttype)
      {
      case TOASC:
         if (footnote_cnt)
         {
            _ULONG        i;   /* counter */
            MYTEXTFILE  *tf;  /* */
            char         fnotefile[32] = "";
            char         buf[4];  /* */
            char         footnote[513];  /* */

            
            outln("-----");
            
            for (i = 0; i < footnote_cnt; i++)
            {
               sprintf(buf, "%03ld", i);
               strcpy(fnotefile, FNOTEFILE);
               strcat(fnotefile, buf);
               
               tf = myTextOpen(fnotefile);
               myTextGetline(footnote, 512, tf);
               voutlnf("%ld %s", i + 1, footnote);
               myTextClose(tf);
               remove(fnotefile);
            }
            
            footnote_cnt = 0;
         }
         
         break;
         
         
      case TOSTG:
      case TOAMG:
         outln("@endnode");
         outln("");
         break;
         
      case TOPCH:
         pch_bottomline();
         outln("\\end");
         break;
         
      case TOTVH:
         tvh_bottomline();
         break;
         
      case TOWIN:
      case TOWH4:
      case TOAQV:
         outln("}\\page");
         break;
         
      case TOHAH:                         /* V6.5.17 */
      case TOHTM:
      case TOMHH:
         break;
      }
      
      active_nodetype = TOC_NONE;
      bInsidePopup = FALSE;
   }
}





/*******************************************************************************
*
*  output_raw_file():
*     read raw file and output it unchanged
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL output_raw_file(

const char     *filename)           /* */
{
   MYTEXTFILE  *file;               /* */
   char         s[1024],            /* */
                old_filename[512],  /* */
                tmp_filename[512];  /* */
   size_t       len;                /* */
   
   
   um_strcpy(old_filename, filename, 512, "output_raw_file[1]");
   um_strcpy(tmp_filename, filename, 512, "output_raw_file[2]");
   
   build_include_filename(tmp_filename, "");
   
   file = myTextOpen(tmp_filename);
   
   if (!file)
   {
      um_strcpy(tmp_filename, old_filename, 512, "output_raw_file[3]");
      file = myTextOpen(tmp_filename);
   }
   
   if (!file)
      return FALSE;
   
   while (myTextGetline(s, 1024, file))
   {
      len = strlen(s);
      
      while ( (len>0) && (((_UBYTE)s[len-1]) <= 32) )
      {
         s[len-1]= EOS;
         len--;
      }
      
      replace_macros(s);                  /* New in V6.5.9 [NHz] */
   
      outln(s);
   }
   
   myTextClose(file);
   
   return TRUE;
}





/*******************************************************************************
*
*  check_output_raw_header():
*     ??? (description missing)
*
*  Note: changed in V6.5.9 [NHz]
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL _BOOL check_output_raw_header(void)
{
   if (!toc[p2_toc_counter]->ignore_raw_header)
   {
      if (toc[p2_toc_counter]->raw_header_filename != 0)
      {
         return output_raw_file(file_lookup(toc[p2_toc_counter]->raw_header_filename));
      }
      else
      {
         if (sDocRawHeaderFilename != 0)
         {
            return output_raw_file(file_lookup(sDocRawHeaderFilename));
         }
      }
   }
   
   return(FALSE);
}





/*******************************************************************************
*
*  check_output_raw_footer():
*     ??? (description missing)
*
*  Note: changed in V6.5.9 [NHz]
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL _BOOL check_output_raw_footer(

_BOOL   lastNode)    /* */
{
   int    offset = 1;  /* */
   
   
   if (lastNode)
      offset = 0;
   
   /* p2_toc_counter bereits hochgezaehlt, daher 1 abziehen, */
   /* aber nur dann, wenn es nicht der letzte Node ist (bei  */
   /* !end_document tritt das auf) !!! */
   
   if (!toc[p2_toc_counter-offset]->ignore_raw_footer)
   {
      if (toc[p2_toc_counter-offset]->raw_footer_filename != 0)
      {
         return output_raw_file(file_lookup(toc[p2_toc_counter-offset]->raw_footer_filename));
      }
      else
      {
         if (sDocRawFooterFilename != 0)
         {
            return output_raw_file(file_lookup(sDocRawFooterFilename));
         }
      }
   }
   
   return(FALSE);
}





/*******************************************************************************
*
*  man_headline():
*     Topline fuer die formatierte ASCII-Ausgabe
*
*  Note:
*     darf NICHT outln() aufrufen, da sonst Rekursion!
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void man_headline(void)
{
   char     n[256];   /* */
   char     s1[256];  /* */
   size_t   spaces,   /* */
            s1l;      /* */
   
   if (no_headlines)
      return;
   
   if (titdat.program == NULL)
      return;
   
   if (sDocManType[0]!=EOS)
      sprintf(s1, "%s%s(%s)%s", BOLD_ON, titdat.program, sDocManType, BOLD_OFF);
   else
      sprintf(s1, "%s%s%s", BOLD_ON, titdat.program, BOLD_OFF);
   
   s1l = strlen(s1) - strlen(BOLD_ON) - strlen(BOLD_OFF);
   
   spaces = zDocParwidth - 2 * s1l;
   
   sprintf(n, "%s%*s%-*s", s1, (int) spaces, "", (int) s1l, s1);
   
   c_internal_styles(n);
   
   fprintf(outfile.file, " %s\n\n", n);
   
   iManPageLines = 2;
}





/*******************************************************************************
*
*  man_bottomline():
*     Bottomline fuer die formatierte ASCII-Ausgabe
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void man_bottomline(void)
{
   char n[256];  /* */
   

   sprintf(n, "- %d -", iManPagePages+1);
   strcenter(n, zDocParwidth);     
   fprintf(outfile.file, "\n%s\n\n", n);
}





/*******************************************************************************
*
*  stg_headline():
*     Topline fuer den ST-Guide
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void stg_headline(const char *numbers, const char *nodename, _BOOL popup)
{
   char      n[512],
             s[512];
   size_t    i,
             sooft,
             platz_links,
             sl;
   
   do_toptoc(toc[p2_toc_counter]->toctype, popup);
   
   if (no_headlines)
      return;
   
   strcpy(s, numbers);
   
   if (s[0] != EOS)
      um_strcat(s, " ", 512, "stg_headline [1]");
   
   if (nodename[0] == EOS)
      tokcat(s, 512);
   else
      um_strcat(s, nodename, 512, "stg_headline [2]");
   
   replace_udo_quotes(s);
   delete_all_divis(s);
   
   replace_2at_by_1at(s);
   
   if (titdat.program != NULL)
      sl = strlen(titdat.program);
   else
      sl = 0;
   
   platz_links = zDocParwidth - sl - 1;
   
   if (toklen(s) > platz_links)
   {
      n[0] = EOS;
      strncat(n, s, platz_links - 4);     /*r6pl4: 2 Leerzeichen */
      strcat(n, "...  ");
   }
   else
   {
      strcpy(n, s);
      sooft = zDocParwidth - toklen(s) - sl;
   
      for (i = 0; i < sooft; i++)
         strcat(n, " ");                  /* <???>: Optimierbar! */
   }
   
   replace_1at_by_2at(s);
   
   if (titdat.program!=NULL)
      strcat(n, titdat.program);
   
   c_internal_styles(n);
   replace_udo_tilde(n);
   replace_udo_nbsp(n);
   
   if (desttype == TOSTG)
      voutlnf("@{U}%s@{u}", n);
   else
      voutlnf("@{U}%s@{UU}", n);
   
   outln("");
}





/*******************************************************************************
*
*  stg_header():
*     output header for ST-Guide
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void stg_header(const char *numbers, const char *nodename, _BOOL is_popup)
{
   int     ti;
   _BOOL   flag;
   
   output_aliasses();
   
   ti = p2_toc_counter;
   
   if (toc[ti]->ignore_links)
      outln("@noref");
   
   if (use_chapter_images && toc[ti]->image != NULL)
   {
      c_begin_center();
      flag = c_img_output(toc[ti]->image, "", FALSE, TRUE);
      c_end_center();
      if (flag)
         return;
   }
   
   if (!is_popup)
      stg_headline(numbers, nodename, is_popup);
}





/*******************************************************************************
*
*  pch_headline():
*     output topline for PC-HELP
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void pch_headline(

char       *s)            /* */
{
   char     n[512];       /* */
   size_t   i,            /* */
            sooft,        /* */
            platz_links,  /* */
            pl;           /* */
            
   
   if (no_headlines)
      return;
   
   pl = 0;
   
   if (titdat.program!=NULL)
      pl = strlen(titdat.program);
   
   platz_links = zDocParwidth - pl - 1;
   
   if (strlen(s) > platz_links)
   {
      n[0] = EOS;
      strncat(n, s, platz_links - 3);
      strcat(n, "...");
   }
   else
   {
      strcpy(n, s);
      sooft = zDocParwidth-strlen(s) - pl;
   
      for (i = 0; i < sooft; i++)
      {
         strcat(n, " ");                  /* <???> optimierbar */
      }
   }
   
   if (titdat.program != NULL)            /* r5pl6: Abfragen, ob Programmname vorhanden ist */
   {
      if (uses_tableofcontents)
      {
         strcat(n, PCH_LINK);    
         strcat(n, titdat.program);
         strcat(n, PCH_LINK);
      }
      else
      {
         strcat(n, titdat.program);
      }
   }
   
   replace_udo_quotes(n);
   delete_all_divis(n);
   c_internal_styles(n);
   replace_udo_tilde(n);
   replace_udo_nbsp(n);
   
   outln(n);
   
   output_ascii_line("-", zDocParwidth);
}





/*******************************************************************************
*
*  pch_bottomline():
*     output bottomline for PC-HELP
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void pch_bottomline(void)
{
   int    ci,      /* */
          pi,      /* */
          ni,      /* */
          ui;      /* */
   char   s[256];  /* */
   char  *up,      /* */                  /*r6pl2: ueber Zeiger, Umkopieren unnoetig */
         *pp,      /* */
         *np;      /* */
         
   
   if (no_bottomlines)
      return;
   
   up = pp = np = NULL;
   
   if (uses_tableofcontents)              /*r6pl2*/
   {
      up = lang.contents;
      pp = lang.contents;
   }
   
   ci = p2_toc_counter;
   pi = toc[ci]->prev_index;
   ni = toc[ci]->next_index;
   ui = 0;
   
   switch (toc[ci]->toctype)
   {
   case TOC_NODE2:
      ui = toc[ci]->up_n1_index;
      break;
   case TOC_NODE3:
      ui = toc[ci]->up_n2_index;
      break;
   case TOC_NODE4:
      ui = toc[ci]->up_n3_index;
      break;
   case TOC_NODE5:
      ui = toc[ci]->up_n4_index;
      break;
   case TOC_NODE6:
      ui = toc[ci]->up_n5_index;
      break;
   }
   
   if (ui > 0)
      up = toc[ui]->name;
   if (pi > 0)
      pp = toc[pi]->name;
   if (ni > 0)
      np = toc[ni]->name;
   
   output_ascii_line("-", zDocParwidth);
   
   if (up !=NULL)
   {
      if (strchr(up, '"') != NULL)
      {
         strcpy(s, up);
         node2pchelp(s);
         voutlnf("[^^^^] \\link(\"%s\")%s\\# ", s, up);
      }
      else
      {
         voutlnf("[^^^^] \\#%s\\#", up);
      }
   }
   
   if (pp != NULL)
   {
      if (strchr(pp, '"') != NULL)
      {
         strcpy(s, pp);
         node2pchelp(s);
         voutlnf("[<<<<] \\link(\"%s\")%s\\# ", s, pp);
      }
      else
      {
         voutlnf("[<<<<] \\#%s\\#", pp);
      }
   }
   
   if (np != NULL)           
   {
      if (np[0] != EOS)
      {
         if (strchr(np, '"') != NULL)
         {
            strcpy(s, np);
            node2pchelp(s);
            voutlnf("[>>>>] \\link(\"%s\")%s\\# ", s, np);
         }
         else
         {
            voutlnf("[>>>>] \\#%s\\#", np);
         }
      }
   }
   
   outln("");
}





/*******************************************************************************
*
*  output_pch_header():
*     output header for PC-HELP
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_pch_header(const char *numbers, const char *name, _BOOL popup)
{
   char    n[256], q[256];
   int            start;
   register int   i;

   
   outln("");
   outln("screen(");
   
/* #if 1 */
   start = toc[p2_toc_counter]->labindex;
/* #else
   start = 1;
   #endif
*/
   
   for (i = start; i < MAXLABELS; i++)
   {
      if (lab[i] != NULL)
      {
         if (lab[i]->tocindex == p2_toc_counter)
         {
            strcpy(q, lab[i]->name);
            node2pchelp(q);
            sprintf(n, "  capsensitive(\"%s\")", q);

            if (i + 1 < MAXLABELS && lab[i+1] != NULL)
            {
               if (lab[i+1]->tocindex == p2_toc_counter)
               {
                  strcat(n, ",");
               }
            }
            
            replace_all_copyright(n);
            replace_udo_tilde(n);
            replace_udo_nbsp(n);
            outln(n);
         }
         else
         {
                                          /* r5pl6 */
            if (lab[i]->tocindex>p2_toc_counter)
            {
               break;
            }
         }
      }
      else
      {
         break;
      }
   }
   
   outln(")");
   
   do_toptoc(toc[p2_toc_counter]->toctype, popup);
   
   sprintf(n, "%s%s", numbers, name);
   pch_headline(n);
   outln("");
}





/*******************************************************************************
*
*  tvh_headline():
*     Headline fuer Turbo-Vision-Help
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void tvh_headline(

const char  *s)       /* */
{
   char      n[256];  /* */
   size_t    nl;      /* */
   
   
   sprintf(n, " %s \334", s);
   outln(n);
   
   nl = strlen(n);
   
   strcpy(n, "  ");
   
   while (strlen(n) < nl)
   {
      strcat(n, "\337");
   }
   
   outln(n);
   outln("");
}





/*******************************************************************************
*
*  tvh_bottomline():
*     output bottomline for Turbo-Vision-Help
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void tvh_bottomline(void)
{
   int    ci,        /* */
          pi,        /* */
          ni,        /* */
          ui;        /* */
   char   up[256],   /* */
          pp[256],   /* */
          np[256];   /* */
   char   up2[256],  /* */
          pp2[256],  /* */
          np2[256];  /* */
   
   
   if (no_bottomlines)
      return;
   
   c_hline();
   
   strcpy(up, lang.contents);
   strcpy(pp, lang.contents);
   
   np[0] = EOS;
   
   ci = p2_toc_counter;
   pi = toc[ci]->prev_index;
   ni = toc[ci]->next_index;
   ui = 0;
   
   switch (toc[ci]->toctype)
   {
   case TOC_NODE2:
      ui = toc[ci]->up_n1_index;
      break;
   case TOC_NODE3:
      ui = toc[ci]->up_n2_index;
      break;
   case TOC_NODE4:
      ui = toc[ci]->up_n3_index;
      break;
   case TOC_NODE5:
      ui = toc[ci]->up_n4_index;
      break;
   case TOC_NODE6:
      ui = toc[ci]->up_n5_index;
      break;
   }
   
   if (ui > 0)
      strcpy(up, toc[ui]->name);
      
   if (pi > 0)
      strcpy(pp, toc[pi]->name);
      
   if (ni > 0)
      strcpy(np, toc[ni]->name);
   
   strcpy(up2, up);
   node2vision(up2);
   
   strcpy(pp2, pp);
   node2vision(pp2);
   
   strcpy(np2, np);
   node2vision(np2);
   
   voutlnf("  { \036 :%s}", up2);
   voutf(" {%s:%s}", "\021\304", pp2);
   
   if (np[0] != EOS)
      voutlnf("\301{%s:%s}", "\304\020", np2);
   else
      outln("\331");
   
   outln("");
}





/*******************************************************************************
*
*  output_vision_header():
*     create header for Turbo-Vision-Help node
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_vision_header(

const char       *numbers,  /* */
const char       *name)     /* */
{
   char           n[512],   /* */
                  l[512];   /* */
   register int   i;        /* */
   size_t         nl;       /* */
   
   
   strcpy(n, ".topic ");
   
   for (i = 1; i < MAXLABELS; i++)
   {
      if (lab[i] != NULL)
      {
         if (lab[i]->tocindex == p2_toc_counter)
         {
            strcpy(l, lab[i]->name);
            node2vision(l);
            strcat(n, l);
            strcat(n, ",");
         }
                                          /* r5pl6 */
         else if (lab[i]->tocindex > p2_toc_counter)
               break;
      }
      else
         break;
   }
   
   nl = strlen(n);
      
   if (n[nl-1] == ',')                    /* Letztes Komma im .topic entfernen */
   {
      n[nl-1] = EOS;
   }
   
   outln(n);
   
   sprintf(n, "%s%s", numbers, name);
   tvh_headline(n);
}





/*******************************************************************************
*
*  output_texinfo_node():
*     output nodeline for TeXinfo
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_texinfo_node(

const char  *name)     /* */
{
   int       ci,       /* */
             pi,       /* */
             ni,       /* */
             ui;       /* */
   char      n[512],   /* */
             pp[256],  /* */
             np[256],  /* */
             up[256];  /* */
   
   
   strcpy(n, name);
   strcpy(up, "Top");
   strcpy(np, "");                        /* r5pl8: vorher "Top" */
   strcpy(pp, "Top");
   
   ci = p2_toc_counter;
   pi = toc[ci]->prev_index;
   ni = toc[ci]->next_index;
   ui = 0;
   
   switch (toc[ci]->toctype)
   {
   case TOC_NODE2:
      ui = toc[ci]->up_n1_index;
      break;
   case TOC_NODE3:
      ui = toc[ci]->up_n2_index;
      break;
   case TOC_NODE4:
      ui = toc[ci]->up_n3_index;
      break;
   case TOC_NODE5:
      ui = toc[ci]->up_n4_index;
      break;
   case TOC_NODE6:
      ui = toc[ci]->up_n5_index;
      break;
   }
   
   if (ui > 0)
      strcpy(up, toc[ui]->name);
      
   if (pi > 0)
      strcpy(pp, toc[pi]->name);
      
   if (ni > 0)
      strcpy(np, toc[ni]->name);
   
   node2texinfo(n);
   node2texinfo(np);
   node2texinfo(pp);
   node2texinfo(up);
   
   outln("");
   
   voutlnf("@node %s, %s, %s, %s", n, np, pp, up);
}





/*******************************************************************************
*
*  win_headline():
*     output topline for WinHelp
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void win_headline(char *name, _BOOL popup)
{
   char   fs[32];
   int    ti;
   
   ti = p2_toc_counter;
   
   if (use_chapter_images)
   {
      if (toc[ti]->image != NULL)
      {
         c_begin_center();
         c_bmp_output(toc[ti]->image, "", FALSE);
         c_end_center();
         return;
      }
   }
   
   /* supress headlines if requested */
   if (no_headlines || toc[ti]->ignore_headline || (no_popup_headlines && popup))
      return;
   
   c_win_styles(name);
   
   if (!popup)
      outln("\\keepn");
   
   do_toptoc(toc[ti]->toctype, popup);
   
   sprintf(fs, "\\fs%d", iDocPropfontSize + 14);
   
   if (popup)
      /* voutlnf("{%s{\\b %s}}\\par\\pard\\par", fs, name) */;
   else
      voutlnf("{%s{\\b\\sa20\\sb20 %s}}\\par\\pard\\par", fs, name);
}



LOCAL void enable_win_button(const char *button, _BOOL enable, const char *nodename)
{
   char    hlp_name[256];

   if (enable)
   {
      if (desttype == TOAQV)
      {
         strcpy(hlp_name, "qchPath");
      }
      else
      {
         strcpy(hlp_name, "`'");
      }
      voutlnf("!{\\footnote ! EnableButton(\"%s\");", button);
      voutlnf("ChangeButtonBinding(\"%s\", \"JumpID(%s, `%s') \") }", button, hlp_name, nodename);
   } else
   {
      voutlnf("!{\\footnote ! DisableButton(\"%s\") }", button);
   }
}


LOCAL void check_win_buttons(int ci)
{
   int i;
    
   for (i = 0; i < iNumWinButtons; i++)
   {
      if (sDocWinButtonName[i][0] != '\0')
      {
         if (toc[ci]->win_button[i] != NULL)
         {
            char s[512];
            int ti;
            int li;
            _BOOL isnode;
            _BOOL isalias;
            _BOOL ispopup;
            
            if (is_node_link(toc[ci]->win_button[i], s, &ti, &isnode, &isalias, &ispopup, &li))
            {
               if (desttype == TOWIN || desttype == TOWH4 || desttype == TOAQV)
               {
                  if (isnode)
                  {
                     node2NrWinhelp(s, li);
                  } else if (isalias)
                  {
                     alias2NrWinhelp(s, li);
                  } else
                  {
                     label2NrWinhelp(s, li);
                  }
                  enable_win_button(sDocWinButtonName[i], TRUE, s);
               }
            } else
            {
               error_undefined_link(toc[ci]->win_button[i]);
            }
         } else
         {
            if (desttype == TOWIN || desttype == TOWH4 || desttype == TOAQV)
               enable_win_button(sDocWinButtonName[i], FALSE, NULL);
         }
      }
   }
}


/*******************************************************************************
*
*  output_win_header():
*     output header for WinHelp
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_win_header(const char *name, const _BOOL invisible)
{
   char  n[512], f[512];
   int ci, ui;
   
   strcpy(n, name);
   del_internal_styles(n);
   
   outln("{");
   
   if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
   {
      strcpy(f, n);
      winspecials2ascii(f);
      voutlnf("K{\\footnote K %s}", f);
   }
   
   if (bDocWinOldKeywords)
   {
      strcpy(f, n);
      node2winhelp(f);
      voutlnf("#{\\footnote # %s}", f);
   }
   
   node2NrWinhelp(f, toc[p2_toc_counter]->labindex);
   voutlnf("#{\\footnote # %s}", f);
   if (toc[p2_toc_counter]->mapping != 0)
      voutlnf("#{\\footnote # %u}", toc[p2_toc_counter]->mapping);
   voutlnf("${\\footnote $ %s}", n);
   
   if (!no_buttons)
   {
      if (!invisible)                     /* versteckte Kapitel nicht mit in die Browse-Sequence einbinden */
         outln(win_browse);
   
      ci = p2_toc_counter;
      ui = 0;
      
      switch (toc[ci]->toctype)
      {
      case TOC_NODE2:
         ui = toc[ci]->up_n1_index;
         break;
      case TOC_NODE3:
         ui = toc[ci]->up_n2_index;
         break;
      case TOC_NODE4:
         ui = toc[ci]->up_n3_index;
         break;
      case TOC_NODE5:
         ui = toc[ci]->up_n4_index;
         break;
      case TOC_NODE6:
         ui = toc[ci]->up_n5_index;
         break;
      }
      
      if (ui == 0)
      {
         if (called_tableofcontents)
         {
            node2NrWinhelp(n, 0);
            enable_win_button("BTN_UP", TRUE, n);
         }
         else
         {
            enable_win_button("BTN_UP", FALSE, NULL);
         }
      }
      else
      {
         node2NrWinhelp(n, toc[ui]->labindex);
         enable_win_button("BTN_UP", TRUE, n);
      }
      check_win_buttons(ci);
   }
}





/*******************************************************************************
*
*  get_html_filename():
*     get filename for HTML according to current node
*
*  Note:
*     UDO splittet die Files selbstaendig und benoetigt u.a. fuer die
*     Referenzen einen eindeutigen Dateinamen. Daher gelangen die Nummern
*     der Kapitel in den Dateinamen. Problem: Ab Kapitel 255 ist's mit der
*     Eindeutigkeit vorbei. Zurueckgeliefert wird nur der Name, kein Suffix
*
*  return:
*     -
*
******************************************|************************************/

LOCAL char *get_html_filename(

const int   tocindex,            /* */
char       *s,                   /* */
int        *html_merge)          /* TRUE = If the nodes are merge */
{
   /*
      The buffer in tmp_n? is with 17 chars a bit small.
      I inserted the following constant to easier use.
      The buffer increase was neccesary because it of
      bug #0000026 and perhaps #0000004.
      Perhaps its better to check if this buffer is big
      enough! Will try this later [vj]
   */
#define MAX_TMP_NX      100

char        tmp_n1[MAX_TMP_NX],  /* */
            tmp_n2[MAX_TMP_NX],  /* */
            tmp_n3[MAX_TMP_NX],  /* */
            tmp_n4[MAX_TMP_NX],  /* */
            tmp_n5[MAX_TMP_NX],  /* */
            tmp_n6[MAX_TMP_NX];  /* */
int         ti;                  /* */
int         hexwidth;            /* */    /* r6pl2 */


#if USE_LONG_FILENAMES
   if (!bForceShort)
      hexwidth = 3;                       /* -> 001002003004.html */
   else
      hexwidth = 2;                       /* -> 01020304.htm */
#else
   if (bForceLong)                        /*r6pl2*/
      hexwidth = 3;                       /* -> 001002003004.html */
   else
      hexwidth = 2;                       /* -> 01020304.htm */
#endif

   ti = tocindex;

   if ( html_merge_node1 || html_merge_node2 || html_merge_node3 ||
        html_merge_node4 || html_merge_node5 || html_merge_node6 )
      *html_merge = TRUE;
   else
      *html_merge = FALSE;

   if (outfile.file != stdout || (bTestmode && outfile.full[0] != EOS) )
   {
      s[0] = EOS;
   
      tmp_n1[0] = EOS;
      tmp_n2[0] = EOS;
      tmp_n3[0] = EOS;
      tmp_n4[0] = EOS;
      tmp_n5[0] = EOS;
      tmp_n6[0] = EOS;
      
      if (html_merge_node1)               /* Nodes nicht splitten */
      {
                                          /* Verweis auf Hauptfile */
         um_strcpy(tmp_n1, outfile.name, MAX_TMP_NX, "get_html_filename[1]");
         *html_merge = TRUE;
      }
      else
      {
         ti = tocindex;                   /* default */
/* Nur zum Debuggen */
/* #if 0
         if (ti < 0)
         {
            fprintf(stderr, "ti < 0\n");
         }

         if (ti > MAXTOCS)
         {
            fprintf(stderr, "ti > MAXTOCS\n");
         }
         
         if (toc[tocindex] == NULL)
         {
            fprintf(stderr, "toc[tocindex] == NULL\n");
         }
   #endif */
   
         switch (toc[tocindex]->toctype)
         {
         case TOC_NODE6:
            if (html_merge_node6)
               ti = toc[tocindex]->up_n5_index;

            if (html_merge_node5)
               ti = toc[tocindex]->up_n4_index;
               
            if (html_merge_node4)
               ti = toc[tocindex]->up_n3_index;
               
            if (html_merge_node3)
               ti = toc[tocindex]->up_n2_index;
               
            if (html_merge_node2)
               ti = toc[tocindex]->up_n1_index;
               
            break;
 
          case TOC_NODE5:
            if (html_merge_node5)
               ti = toc[tocindex]->up_n4_index;
               
            if (html_merge_node4)
               ti = toc[tocindex]->up_n3_index;
               
            if (html_merge_node3)
               ti = toc[tocindex]->up_n2_index;
               
            if (html_merge_node2)
               ti = toc[tocindex]->up_n1_index;
               
            break;
            
         case TOC_NODE4:
            if (html_merge_node4)
               ti = toc[tocindex]->up_n3_index;
               
            if (html_merge_node3)
               ti = toc[tocindex]->up_n2_index;
               
            if (html_merge_node2)
               ti = toc[tocindex]->up_n1_index;
               
            break;
            
         case TOC_NODE3:
            if (html_merge_node3)
               ti = toc[tocindex]->up_n2_index;
               
            if (html_merge_node2)
               ti = toc[tocindex]->up_n1_index;
               
            break;
            
         case TOC_NODE2:
            if (html_merge_node2)
               ti = toc[tocindex]->up_n1_index;
               
            break;
         }
   
         if (toc[ti]->filename[0] != EOS)
         {       
                                          /* New in r6pl16 [NHz] */
            {
                                          /* v6.3.12 [vj] See constant definition above */
               char   dummy[MAX_TMP_NX],  /* */
                      name[MAX_TMP_NX],   /* */
                      suff[MAX_TMP_NX];   /* */
                      
   
               fsplit(toc[ti]->filename, dummy, dummy, name, suff);
   
               if (strcmp(suff, ""))
                  sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, name, suff);
               else
                  sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);
            }
   
            um_strcpy(tmp_n1, toc[ti]->filename, MAX_TMP_NX, "get_html_filename[2]");
         }
         else
         {
            if (toc[ti]->appendix)
            {
               sprintf(tmp_n1, "_%c", 'a' + toc[ti]->n1 - 1);
            }
            else
            {
               if (toc[ti]->n1 == 0)
               {
                  um_strcpy(tmp_n1, old_outfile.name, MAX_TMP_NX, "get_html_filename[3]");
               }
               else
               {
                  sprintf(tmp_n1, "%0*x", hexwidth, toc[ti]->n1);
               }
            }

            if (toc[ti]->n2>0 && !html_merge_node2) 
            {
               sprintf(tmp_n2, "%0*x", hexwidth, toc[ti]->n2);
            }
   
            if (toc[ti]->n3>0 && !html_merge_node3)
            {
               sprintf(tmp_n3, "%0*x", hexwidth, toc[ti]->n3);
            }
   
            if (toc[ti]->n4>0 && !html_merge_node4)
            {
               sprintf(tmp_n4, "%0*x", hexwidth, toc[ti]->n4);
            }
            
   /* ToDo: [GS] Problem, wie man bei einen Dateinamen mit 8 Zeichen den Node 5 + 6 darstellt */

            if (toc[ti]->n5>0 && !html_merge_node5)
            {
               if (hexwidth == 3)         /* Long filename */
                  sprintf(tmp_n5, "%0*x", hexwidth, toc[ti]->n5);
               else
                  sprintf(tmp_n4, "%0*x", hexwidth, toc[ti]->n5+100);
            }

            if (toc[ti]->n6>0 && !html_merge_node6)
            {
               if (hexwidth == 3)         /* Long filename */
                  sprintf(tmp_n6, "%0*x", hexwidth, toc[ti]->n6);
               else
                  sprintf(tmp_n5, "%0*x", hexwidth, toc[ti]->n6+100);
            }

         }
      }
      
      if (hexwidth == 3)                  /* Long filename */
         sprintf(s, "%s%s%s%s%s%s", tmp_n1, tmp_n2, tmp_n3, tmp_n4, tmp_n5, tmp_n6);
      else
         sprintf(s, "%s%s%s%s", tmp_n1, tmp_n2, tmp_n3, tmp_n4);
   }
   else
   {
#if USE_LONG_FILENAMES
      if (!bForceShort)
         strcpy(s, "stdout.html");        /* r5pl11 */
      else
         strcpy(s, "stdout.htm");         /* r5pl11 */
#else
      if (bForceLong)
         strcpy(s, "stdout.html");        /* r5pl11 */
      else
         strcpy(s, "stdout.htm");         /* r5pl11 */
#endif
   }
   
   if (s[0] == EOS)
   {
      fprintf(stderr, "! empty filename: %d,%d,%d,%d,%d (%d)\n",
         toc[ti]->n1,
         toc[ti]->n2,
         toc[ti]->n3,
         toc[ti]->n4,
         toc[ti]->n5,
         toc[ti]->appendix);
         
      fprintf(stderr, "! using 'error' instead\n");
      fprintf(stderr, "! please inform the author (%s)!\n", UDO_URL);
      strcpy(s, "error");
   }
   
   return s;
}





/*******************************************************************************
*
*  html_make_file():
*     create new HTML file and output header and meta information
*
*  Note:
*     wird nur fuer das jeweils aktuelle Kapitel aufgerufen
*     (durch html_new_file())
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL html_make_file(void)
{
   if (outfile.name[0] == EOS)
      return FALSE;
   
   if (bOutOpened)
   {
      fclose(outfile.file);               /* close the already opened file */
      bOutOpened = FALSE;
   }
   
#if 0
   if (html_use_folders)
   {       
      if (toc[ti]->dirname != 0)
         sprintf(outfile.path, "%s%s", old_outfile.path, file_lookup(toc[ti]->dirname));
      else
         sprintf(outfile.path, "%s%04X", old_outfile.path, toc[ti]->n1);
   
      if (toc[ti]->toctype == TOC_NODE1)
      {                                   /* Verzeichnis anlegen, falls nicht vorhanden */
         if (toc[ti]->n2 == 0 && toc[ti]->n3 == 0 && toc[ti]->n4 == 0)
         {
            char   sDir[512];  /* */
            
            
            sprintf(sDir, "%s%s", outfile.driv, outfile.path);
            my_mkdir(sDir);
         }
      }
   
      strcat(outfile.path, "\\");
   }
#endif
   
   {                                      /* New in r6pl16 [NHz] */
      char   dummy[MAX_TMP_NX],  /* */    /* v6.3.12 [vj] See constant definition in get_html_filename */
             name[MAX_TMP_NX],   /* */
             suff[MAX_TMP_NX];   /* */
          
   
      um_strcpy(name, outfile.name, MAX_TMP_NX, "html_make_file[1]");
      fsplit(outfile.name, dummy, dummy, name, suff);
   
      if (strcmp(suff, ""))
      {
         sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, name, suff);
      }
      else
         sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);
   }

/*
   sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);
*/
   
   if (!bTestmode) 
   {
      outfile.file = myFwopen(outfile.full, TOHTM);
      
      if (!outfile.file)
      {
         error_open_outfile(outfile.full);
         warning_err_destination();
         bErrorDetected = TRUE;
         bFatalErrorDetected = TRUE;
         return FALSE;
      }
      
      bOutOpened = TRUE;
      save_upr_entry_outfile(outfile.full);
   }
   
   return TRUE;
}





/*******************************************************************************
*
*  output_html_meta():
*     output HTML meta data in the HTML head section
*
*  <???> <meta name="Subject" content="...">
*  <???> <meta name="Modification-Date" content="...">
*  <???> <meta name="Expiration-Date" content="...">
*  <???> <meta name="Language" content="...">
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_html_meta(_BOOL keywords)
{
   int      ti = 0,
            i,
            li,
            j,
            html_merge;
   STYLE  *styleptr;
   char    s[512];               /* buffer for charset and label name */
   char    htmlname[512],
           sTarget[512] = "\0";
   char    backpage[256],
           href[256],
           alt[256],
          *tok;

                                          /* get right charset name */
   strcpy(s, chr_codepage_charset_name(iEncodingTarget));
   
   if (html_doctype != HTML5)
   {
      voutlnf("<meta http-equiv=\"Content-Type\" content=\"text/html;charset=%s\"%s>", s, xhtml_closer);
      voutlnf("<meta http-equiv=\"Content-Language\" content=\"%s\"%s>", lang.html_lang, xhtml_closer);
      voutlnf("<meta http-equiv=\"Content-Style-Type\" content=\"text/css\"%s>", xhtml_closer);
      voutlnf("<meta http-equiv=\"Content-Script-Type\" content=\"text/javascript\"%s>", xhtml_closer);
   }
   else
      voutlnf("<meta charset='%s'%s>", s, xhtml_closer);

   /* New feature #0000054 in V6.5.2 [NHz] */
   if (html_header_date)
   {
      char     zone[20] = "+00:00";  /* */
      time_t   uhrzeit;              /* */
      int      hour_local,           /* */
               min_local,            /* */
               mday_local,           /* */
               min_utc,              /* */
               hour_utc,             /* */
               mday_utc;             /* */
      int      hours,                /* */
               minutes;              /* */


      if (strcmp(html_header_date_zone, "") > 0)
         um_strcpy(zone, html_header_date_zone, 9, "output_html_meta[1]1");
      else
      {
         time(&uhrzeit);
         mday_local = localtime(&uhrzeit)->tm_mday;
         mday_utc   = gmtime(&uhrzeit)->tm_mday;
         hour_local = localtime(&uhrzeit)->tm_hour;
         hour_utc   = gmtime(&uhrzeit)->tm_hour;
         min_local  = localtime(&uhrzeit)->tm_min;
         min_utc    = gmtime(&uhrzeit)->tm_min;

         if (min_local < min_utc)         /* special for countries with "broken times" (e.g. Iran +03:30) */
         {
            if (mday_local != mday_utc)   /* if different days over midnight */
               hours = hour_local - hour_utc - 1 + 24;
            else
               hours = hour_local - hour_utc - 1;

            minutes = min_utc - min_local;
         }
         else
         {
            if (mday_local != mday_utc)   /* if different days over midnight */
               hours = hour_local - hour_utc + 24;
            else
               hours = hour_local - hour_utc;
            
            minutes = min_local - min_utc;
         }

         sprintf(zone, "%+03d:%02d", hours, minutes);
      }
   
      voutlnf("<meta name=\"date\" content=\"%d-%02d-%02dT%02d:%02d:%02d%s\"%s>", 
         iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin, iDateSec, zone, xhtml_closer);
   }

   /* Changed in V6.5.5 [NHz] */
   voutlnf("<meta name=\"Generator\" content=\"UDO %s.%s %s for %s\"%s>",
      UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS, xhtml_closer);

   if (titdat.author != NULL)
   {
      voutlnf("<meta name=\"Author\" content=\"%s\"%s>", titdat.author, xhtml_closer);
   }

   if (keywords)
   {
      ti = p2_toc_counter;

      if (ti >= 0)
      {
         if (toc[ti]->keywords != NULL)
         {
            voutlnf("<meta name=\"Keywords\" content=\"%s\"%s>", toc[ti]->keywords, xhtml_closer);
         }

         /* New in V6.5.9 [NHz] */
         else
         {
            if (titdat.keywords != NULL)
            {
               voutlnf("<meta name=\"Keywords\" content=\"%s\"%s>", titdat.keywords, xhtml_closer);
            }
         }

         if (toc[ti]->description != NULL)
         {
            voutlnf("<meta name=\"Description\" content=\"%s\"%s>", toc[ti]->description, xhtml_closer);
         }
         else                             /* New in V6.5.9 [NHz] [docinfo] */
         {
            if (titdat.description != NULL)
            {
               voutlnf("<meta name=\"Description\" content=\"%s\"%s>", titdat.description, xhtml_closer);
            }
         }

         /* New in V6.5.17 */
         if (toc[ti]->robots != NULL)
         {
            voutlnf("<meta name=\"robots\" content=\"%s\"%s>", toc[ti]->robots, xhtml_closer);
         }
         else
         {
            if (titdat.robots != NULL)
            {
               voutlnf("<meta name=\"robots\" content=\"%s\"%s>", titdat.robots, xhtml_closer);
            }
         }
      }
   }

   /*r6pl5: <link>-Tag */
   if (titdat.contact_name != NULL)
   {
      if (html_doctype != HTML5)
         voutlnf("<meta name=\"Email\" content=\"%s\"%s>", titdat.contact_name, xhtml_closer);
      
	   if (titdat.contact_link == NULL)
      {
         if (html_doctype != HTML5)
            voutlnf("<link rev=\"made\" href=\"mailto:%s\" title=\"E-Mail\"%s>", titdat.contact_name, xhtml_closer);

         /* New in r6pl16 [NHz] */
         voutlnf("<link rel=\"author\" href=\"mailto:%s\" title=\"E-Mail\"%s>", titdat.contact_name, xhtml_closer);
      }
   }
   if (titdat.contact_link != NULL)
   {
      if (html_doctype != HTML5)
         voutlnf("<link rev=\"made\" href=\"%s\" title=\"E-Mail\"%s>", titdat.contact_link, xhtml_closer);

      /* New in r6pl16 [NHz] */
      voutlnf("<link rel=\"author\" href=\"%s\" title=\"E-Mail\"%s>", titdat.contact_link, xhtml_closer);
   }

   /* New in r6pl15 [NHz] */
   if (html_frames_layout)
   {
      sprintf(sTarget, " target=\"UDOcon\"");
   }

   /* New feature #0000053 in V6.5.2 [NHz] */
   if (html_header_links)
   {
      if (strstr(html_header_links_kind, "chapter") != NULL)
      {
         toc_link_output(1);
         toc_link_output(2);
         toc_link_output(3);
         toc_link_output(4);
         toc_link_output(5);
      }
   }

   /* New feature #0000053 in V6.5.2 [NHz] */
   if (html_header_links)
   {
      if (strstr(html_header_links_kind, "navigation"))
      {
         if (old_outfile.name[0] != EOS)
         {                                /* Changed in r6pl16 [NHz] */
                                          /* Feststellen, ob die Referenz im gleichen File liegt */
            if (strcmp(old_outfile.name, outfile.name) != 0)
            {
               voutlnf("<link rel=\"start\" href=\"%s%s\"%s title=\"%s\"%s>",
                  old_outfile.name, outfile.suff, sTarget, lang.html_start, xhtml_closer);

               /* Special for CAB */
               voutlnf("<link rel=\"home\" href=\"%s%s\"%s title=\"%s\"%s>", 
                  old_outfile.name, outfile.suff, sTarget, lang.html_start, xhtml_closer);
               
               if (uses_tableofcontents)
               {
                                          /* New in r6pl15 [NHz] */
                  voutlnf("<link rel=\"contents\" href=\"%s%s#UDOTOC\"%s title=\"%s\"%s>",
                     old_outfile.name, outfile.suff, sTarget, lang.contents, xhtml_closer);

                  /* Special for CAB */
                  voutlnf("<link rel=\"toc\" href=\"%s%s#UDOTOC\"%s title=\"%s\"%s>", 
                     old_outfile.name, outfile.suff, sTarget, lang.contents, xhtml_closer);
               }
            }
         }

         /* Andere moegliche Angaben laut SelfHTML 6.0:
          * <link rev="relation" href="http://www.autorshome.de/" title="Autoren-Homepage">
          * <link rel="index" href="stichwrt.htm" title="Stichwortverzeichnis">
          * <link rel="glossary" href="glossar.htm" title="Begriffs-Glossar">
          * <link rel="copyright" href="rechte.htm" title="Copyright">
          * <link rel="next" href="augsburg.htm" title="naechste Seite">
          * <link rel="previous" href="aachen.htm" title="vorherige Seite">
          * <link rel="help" href="hilfe.htm" title="Orientierungshilfe">
          * <link rel="bookmark" href="hinweis.htm" title="Neuorientierung">
          */

          
         /* New in r6pl16 [NHz] */
         /* Output of Link-Rel 'up' */
         /* is going to same place than !html_backpage */

         if (sDocHtmlBackpage[0] != EOS)
         {
            strcpy(backpage, sDocHtmlBackpage);
            tok = strtok(backpage, "\'");
            strcpy(href, tok);
            del_right_spaces(href);
            tok = strtok(NULL, "\'");
            
            if (tok != NULL)
            {
               strcpy(alt, tok);
               auto_quote_chars(alt, TRUE);
            }
            else
               strcpy(alt, href);

            /* Special for CAB */
            voutlnf("<link rel=\"up\" href=\"%s\" title=\"%s\"%s>", href, alt, xhtml_closer);
         }

         /* New in r6pl15 [NHz] */
         /* Output of Link-Rel 'first' */

         i = toc[ti]->prev_index;

         if (i > 0)
         {
            li = toc[1]->labindex;        /* First Node -> No Link */

            strcpy(s, lab[li]->name);
            get_html_filename(lab[li]->tocindex, htmlname, &html_merge);

            /* Special for CAB */
            /* Changed in r6.2pl1 [NHz] / Fixed Bug #0000039 */
            if (strchr(htmlname, '.') != NULL)
            {
               voutlnf("<link rel=\"first\" href=\"%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, sTarget, s, xhtml_closer);
            }
            else
            {
               voutlnf("<link rel=\"first\" href=\"%s%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, xhtml_closer);
            }
         }

         
         /* New in r6pl15 [NHz] */
         /* Output of Link-Rel 'prev' */

         if (i > 0)
         {
            li = toc[i]->labindex;
            strcpy(s, lab[li]->name);
            get_html_filename(lab[li]->tocindex, htmlname, &html_merge);

            /* Changed in r6.2pl1 [NHz] / Fixed Bug #0000039 */
            if (strchr(htmlname, '.') != NULL)
            {
               voutlnf("<link rel=\"prev\" href=\"%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, sTarget, s, xhtml_closer);
               
               /* Special for CAB */
               voutlnf("<link rel=\"previous\" href=\"%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, sTarget, s, xhtml_closer);
            }
            else
            {
               voutlnf("<link rel=\"prev\" href=\"%s%s%s\"%s title=\"%s\"%s>",
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, xhtml_closer);
               
               /* Special for CAB */
               voutlnf("<link rel=\"previous\" href=\"%s%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, xhtml_closer);
            }
         }

         /* Output of Link-Rel 'next' */

         i = toc[ti]->next_index;

         if (i > 1)
         {
            li = toc[i]->labindex;
            strcpy(s, lab[li]->name);
            get_html_filename(lab[li]->tocindex, htmlname, &html_merge);

            /* Changed in r6.2pl1 [NHz] / Fixed Bug #0000039*/
            if (strchr(htmlname, '.') != NULL)
            {
               voutlnf("<link rel=\"next\" href=\"%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, sTarget, s, xhtml_closer);
            }
            else
            {
               voutlnf("<link rel=\"next\" href=\"%s%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, xhtml_closer);
            }
         }
         

         /* New in r6pl15 [NHz] */
         /* Output of Link-Rel 'last' */

         if (i > 1)
         {
            if (use_about_udo)
            {
               li = toc[p1_toc_counter]->labindex;
               li--;
            }
            else
               li = toc[p1_toc_counter]->labindex;
            
            strcpy(s, lab[li]->name);
            get_html_filename(lab[li]->tocindex, htmlname, &html_merge);

            /* Special for CAB */
            /* Changed in r6.2pl1 [NHz] / Fixed Bug #0000039 */
            if (strchr(htmlname, '.') != NULL)
            {
               voutlnf("<link rel=\"last\" href=\"%s%s\"%s title=\"%s\"%s>",
                  html_name_prefix, htmlname, sTarget, s, xhtml_closer);
            }
            else
            {
               voutlnf("<link rel=\"last\" href=\"%s%s%s\"%s title=\"%s\"%s>",
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, xhtml_closer);
            }
         }
      }
   }

   /* New in r6pl15 [NHz] */
   /* Output of Link-Rel 'copyright' */
   /* Link shows to 'About UDO'; maybe changed in future times */

   if (use_about_udo)
   {
      li = toc[p1_toc_counter]->labindex;
      strcpy(s, lab[li]->name);
      get_html_filename(lab[li]->tocindex, htmlname, &html_merge);

                                          /* Changed in r6pl16 [NHz] */
      if (strcmp(htmlname, outfile.name) != 0)
      {
         voutlnf("<link rel=\"copyright\" href=\"%s%s\"%s title=\"%s\"%s>",
            htmlname, outfile.suff, sTarget, s, xhtml_closer);
      }
   }

   /* Link for overall and file-related stylesheet-file */
   for (j = 0; j < p1_style_counter; j++)
   {
      styleptr = style[j];
      
      if (styleptr->href != NULL && (styleptr->tocindex == 0 || styleptr->tocindex == p2_toc_counter))
      {
         char  this_style[512];
         
         strcpy(this_style, "<link rel=\"");

         if (styleptr->alternate == TRUE)
            strcat(this_style, "alternate ");
         
         strcat(this_style, "stylesheet\" type=\"text/css\" href=\"");
         strcat(this_style, styleptr->href);
         
         if (styleptr->media[0] != EOS)
         {
            strcat(this_style, "\" media=\"");
            strcat(this_style, styleptr->media);
         }
         
         if (styleptr->title[0] != EOS)
         {
            strcat(this_style, "\" title=\"");
            strcat(this_style, styleptr->title);
         }
         
         strcat(this_style, "\">");
         outln(this_style);
      }
   }

   /* Link for overall javascript-file */
   if (sDocScript != 0)
   {
      voutlnf("<script language=\"JavaScript\" src=\"%s\" type=\"text/javascript\">", file_lookup(sDocScript));
      outln("</script>");
   }

   /* Link for overall FavIcon */
   if (sDocFavIcon != 0)
      voutlnf("<link rel=\"shortcut icon\" href=\"%s\"%s>", file_lookup(sDocFavIcon), xhtml_closer);
   
   if (toc[p2_toc_counter]->bgsound != 0)
      voutlnf("<bgsound src=\"%s\">", file_lookup(toc[p2_toc_counter]->bgsound));
}





/*******************************************************************************
*
*  output_html_doctype():
*     output HTML doctype in HTML header
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_html_doctype(void)
{
   char   s[512];  /* buffer */
   
                                          /* get right charset name */
   strcpy(s, chr_codepage_charset_name(iEncodingTarget));
   
   switch (html_doctype)
   {
   case HTML_OLD:
      outln("<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">");
      break;
   case HTML_STRICT:
      outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"");
      outln("        \"http://www.w3.org/TR/html4/strict.dtd\">");
      break;
   case HTML_TRANS:
      outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"");
      outln("        \"http://www.w3.org/TR/html4/loose.dtd\">");
      break;
   case HTML5:
      outln("<!DOCTYPE HTML>");
      break;
   case XHTML_STRICT:
      voutlnf("<?xml version=\"1.0\" encoding=\"%s\"?>", s);
      outln("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"");
      outln("        \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
      break;
   case XHTML_TRANS:
      voutlnf("<?xml version=\"1.0\" encoding=\"%s\"?>", s);
      outln("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"");
      outln("        \"http://www.w3.org/TR/xhtml1/DTD/xhtm1-transitional.dtd\">");
      break;
   }
   
   if (html_header_date)
      voutlnf("<!-- last modified on %s -->", lang.short_today);
}





/*******************************************************************************
*
*  html_new_file():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL _BOOL html_new_file(void)
{
   char   t[512],        /* */
          xml_lang[80],
          xml_ns[40];    /* */
          
   
   if (outfile.file == stdout && !bTestmode)
      return TRUE;
   
   check_endnode();                       /* Bisherige Datei erst einmal schliessen */

   voutf("%s", sHtmlPropfontEnd);
   check_output_raw_footer(FALSE);        /*r6pl10*/
   outln("</body>");
   outln("</html>");
   
                                          /* Dateinamen der neuen Datei ermitteln */
#if 1
   sprintf(outfile.name, "%s%s", html_name_prefix, toc[p2_toc_counter]->filename);
#else
   strcpy(outfile.name, toc[p2_toc_counter]->filename);
#endif
   
   if (!html_make_file())                 /* r6pl4 */
      return FALSE;
   
   output_html_doctype();
   
                                          /* Header anlegen, Aktueller Node ist bekannt */
   if (html_doctype >= XHTML_STRICT)      /* Bisherige Datei erst einmal schliessen */
   {
      sprintf(xml_lang, " xml:lang=\"%s\"", lang.html_lang);
      sprintf(xml_ns, " xmlns=\"http://www.w3.org/1999/xhtml\"");
   }
   else
   {
      xml_lang[0] = EOS;
      xml_ns[0] = EOS;
   }
   
   voutlnf("<html%s lang=\"%s\"%s>", xml_ns, lang.html_lang, xml_lang);
   outln("<head>");
   outln("<title>");
   
   if (desttype == TOHTM || desttype == TOHAH)
   {
      if (titdat.htmltitle != NULL && titdat.htmltitle[0] != EOS)
      {
         strcpy(t, titdat.htmltitle);     /*r6pl5*/
      }
      else
      {
         strcpy(t, titleprogram);
      }
   }
   else
   {
      t[0] = EOS;
   }
   
   if (toc[p2_toc_counter] != NULL)
   {
      if (t[0] != EOS)
      {
         strcat(t, ": ");
      }
      
      strcat(t, toc[p2_toc_counter]->name);
   }
   
   outln(t);
   
   outln("</title>");
   output_html_meta(TRUE);
   outln("</head>");
   
   if (toc[p2_toc_counter] != NULL)
   {
      out("<body");
      
      if (toc[p2_toc_counter]->backimage != 0)
      {
         voutf(" background=\"%s\"", file_lookup(toc[p2_toc_counter]->backimage));
      }
      
      if (toc[p2_toc_counter]->backcolor.set)
      {
         voutf(" bgcolor=\"%s\"", html_color_string(&toc[p2_toc_counter]->backcolor));
      }
      
      if (toc[p2_toc_counter]->textcolor.set)
      {
         voutf(" text=\"%s\"", html_color_string(&toc[p2_toc_counter]->textcolor));
      }
      
      if (toc[p2_toc_counter]->linkcolor.set)
      {
         voutf(" link=\"%s\"", html_color_string(&toc[p2_toc_counter]->linkcolor));
      }
      
      if (toc[p2_toc_counter]->alinkcolor.set)
      {
         voutf(" alink=\"%s\"", html_color_string(&toc[p2_toc_counter]->alinkcolor));
      }
      
      if (toc[p2_toc_counter]->vlinkcolor.set)
      {
         voutf(" vlink=\"%s\"", html_color_string(&toc[p2_toc_counter]->vlinkcolor));
      }
      
      outln(">");
   }
   else
   {
      outln("<body>");
   }
   
   check_output_raw_header();             /*r6pl10*/
   
   outln(sHtmlPropfontStart);
   
   output_aliasses();                     /* r5pl9 */
   
   if (desttype == TOHTM || desttype == TOHAH)
      html_headline();
   else
      hh_headline();
   
   return TRUE;
}





/*******************************************************************************
*
*  output_html_header():
*     Wird nur fuer die Titelseite/Inhaltsverzeichnis benutzt
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void output_html_header(

const char  *t)                 /* */
{
   char      xml_lang[80],
             xml_ns[40];        /* */
   char      closer[8] = "\0";  /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   output_html_doctype();                 /* r6pl2 */
   
   if (html_doctype >= XHTML_STRICT)      /* Changed in V6.5.9 [NHz] */
   {
      sprintf(xml_lang, " xml:lang=\"%s\"", lang.html_lang);
      sprintf(xml_ns, " xmlns=\"http://www.w3.org/1999/xhtml\"");
   }
   else
   {
      xml_lang[0] = EOS;
      xml_ns[0] = EOS;
   }
   
   voutlnf("<html%s lang=\"%s\"%s>", xml_ns, lang.html_lang, xml_lang);
   outln("<head>");
   outln("<title>");
   outln(t);
   outln("</title>");
   
   /* New in r6pl16 [NHz]
   Fixed: added real title (from <title> Tag) [vj]
   */
   
   /* V6.5.17 */
   if (desttype == TOHAH)
   {
      if (titdat.appletitle != NULL)
         voutlnf("<meta name=\"AppleTitle\" content=\"%s\"%s>", titdat.appletitle, closer);
         
      if (titdat.appleicon != NULL)
         voutlnf("<meta name=\"AppleIcon\" content=\"%s\"%s>", titdat.appleicon, closer);
   }
   
   output_html_meta(TRUE);                /*r6pl5: auch Keywords auf der ersten Seite erlauben */
   outln("</head>");
   
   out("<body");
   
   if (sDocBackImage != 0)
   {
      if (!no_images)
      {
         voutf(" background=\"%s\"", file_lookup(sDocBackImage));
      }
   }
   
   if (sDocBackColor.rgb.set)
   {
      voutf(" bgcolor=\"%s\"", html_color_string(&sDocBackColor.rgb));
   }
   
   if (sDocTextColor.rgb.set)
   {
      voutf(" text=\"%s\"", html_color_string(&sDocTextColor.rgb));
   }
   
   if (sDocLinkColor.rgb.set)
   {
      voutf(" link=\"%s\"", html_color_string(&sDocLinkColor.rgb));
   }
   
   if (sDocAlinkColor.rgb.set)
   {
      voutf(" alink=\"%s\"", html_color_string(&sDocAlinkColor.rgb));
   }
   
   if (sDocVlinkColor.rgb.set)
   {
      voutf(" vlink=\"%s\"", html_color_string(&sDocVlinkColor.rgb));
   }
   
   voutlnf(">");
   check_output_raw_header();
   
   voutlnf("%s", sHtmlPropfontStart);
}





/*******************************************************************************
*
*  get_giflink_data():
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void get_giflink_data(const int index, const char **name, _UWORD *width, _UWORD *height)
{
   *width = *height = 0;
   
   switch (index)
   {
   case GIF_HM_INDEX:                     /* Home */
      *name = GIF_HM_NAME;
      *width = uiGifHmWidth;
      *height = uiGifHmHeight;
      break;
   case GIF_UP_INDEX:                     /* Up */
      *name = GIF_UP_NAME;
      *width = uiGifUpWidth;
      *height = uiGifUpHeight;
      break;
   case GIF_LF_INDEX:                     /* Left */
      *name = GIF_LF_NAME;
      *width = uiGifLfWidth;
      *height = uiGifLfHeight;
      break;
   case GIF_RG_INDEX:                     /* Right */
      *name = GIF_RG_NAME;
      *width = uiGifRgWidth;
      *height = uiGifRgHeight;
      break;
   case GIF_NOHM_INDEX:                   /* Home (disabled) */
      *name = GIF_NOHM_NAME;
      *width = uiGifNoHmWidth;
      *height = uiGifNoHmHeight;
      break;
   case GIF_NOUP_INDEX:                   /* Up (disabled) */
      *name = GIF_NOUP_NAME;
      *width = uiGifNoUpWidth;
      *height = uiGifNoUpHeight;
      break;
   case GIF_NOLF_INDEX:                   /* Left (disabled) */
      *name = GIF_NOLF_NAME;
      *width = uiGifNoLfWidth;
      *height = uiGifNoLfHeight;
      break;
   case GIF_NORG_INDEX:                   /* Right (disabled) */
      *name = GIF_NORG_NAME;
      *width = uiGifNoRgWidth;
      *height = uiGifNoRgHeight;
      break;
   case GIF_GER_INDEX:                    /* German */
      *name = GIF_GER_NAME;
      *width = uiGifGerWidth;
      *height = uiGifGerHeight;
      break;
   case GIF_ENG_INDEX:                    /* English */
      *name = GIF_ENG_NAME;
      *width = uiGifEngWidth;
      *height = uiGifEngHeight;
      break;
   }
}


/*******************************************************************************
*
*  html_index_giflink():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_index_giflink(const int idxEnabled, const int idxDisabled, const char *sep, _BOOL head)
{
   char      sTarget[64],
             *sFile,
             sGifSize[80];
   const char *sGifName;
   _UWORD    uiW, uiH;
   char      sIDName[32];       /* string buffer for anchor ID name */

   
   sTarget[0] = sGifSize[0] = EOS;
   
   if (html_frames_layout)
   {
      sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
      sFile = um_strdup_printf("%s%s%s", html_name_prefix, FRAME_FILE_CON, outfile.suff);
   }
   else
   {
      sTarget[0] = EOS;
      sFile = um_strdup_printf("%s%s", old_outfile.name, old_outfile.suff);
   }
   
   if (uses_tableofcontents)
   {
      /* mark ID as unique */
      if (head)
         strcpy(sIDName, "UDO_nav_up_HEAD");
      else
         strcpy(sIDName, "UDO_nav_up_FOOT");

      if (no_images)
      {
         voutlnf("%s<a id=\"%s\" href=\"%s%s#%s\"%s>%s</a>",
            sep, sIDName, sFile, outfile.suff, HTML_LABEL_CONTENTS, sTarget, " ^^^" /* lang.contents */);
      }
      else
      {
      	 char border[20];
      	 
      	 strcpy(border, " border=\"0\"");
#if 0
         if (html_doctype == HTML5)
            border[0] = EOS;
#endif
         get_giflink_data(idxEnabled, &sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
         voutlnf("<a id=\"%s\" href=\"%s#%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s></a>",
            sIDName, sFile, HTML_LABEL_CONTENTS, sTarget, sGifName, lang.contents, lang.contents, border, sGifSize, xhtml_closer);
      }
   }
   else
   {
      if (no_images)
      {
         voutlnf("%s ^^^", sep);
      }
      else
      {
      	 char border[20];
      	 
      	 strcpy(border, " border=\"0\"");
#if 0
         if (html_doctype == HTML5)
            border[0] = EOS;
#endif
         get_giflink_data(idxDisabled, &sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifName, border, sGifSize, xhtml_closer);
      }
   }
   free(sFile);
}





/*******************************************************************************
*
*  html_home_giflink():
*     create and output HOME link for HTML navigation bar
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_home_giflink(const int idxEnabled, const int idxDisabled, const char *sep, _BOOL head)
{
   char      sTarget[64],
             *sFile;
   char      sGifSize[128];
   const char *sGifName;
   char      sIDName[32];       /* string buffer for anchor ID name */
   _UWORD     uiW, uiH;

   switch (idxEnabled)
   {
   case GIF_HM_INDEX:
      strcpy(sIDName, "UDO_nav_hm");
      break;
   
   case GIF_LF_INDEX:
      strcpy(sIDName, "UDO_nav_lf");
      break;
   
   case GIF_RG_INDEX:
      strcpy(sIDName, "UDO_nav_rg");
      break;
   
   default:
      strcpy(sIDName, "UDO_nav_up");
      break;
   }
   
   /* mark ID as unique */
   if (head)
      strcat(sIDName, "_HEAD");
   else
      strcat(sIDName, "_FOOT");
   
   if (toc[p2_toc_counter]->toctype == TOC_TOC)
   {
      /* Im Inhaltsverzeichnis Link auf !html_backpage mit Home-Symbol */
      sTarget[0] = EOS;

      if (html_frames_layout)
         sprintf(sTarget, " target=\"_top\"");

      if (no_images)
      {
         voutlnf("%s%s", sep, lang.html_home);
      }
      else
      {
      	 char border[20];
      	 
      	 strcpy(border, " border=\"0\"");
#if 0
         if (html_doctype == HTML5)
            border[0] = EOS;
#endif
         /* Button disabled ausgeben */
         get_giflink_data(idxDisabled, &sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         voutlnf("<img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s>",
            sGifName, lang.html_home, lang.html_home, border, sGifSize, xhtml_closer);
      }
   }
   else
   {
      if (html_frames_layout)
      {
         sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
         sFile = um_strdup_printf("%s%s%s", html_name_prefix, FRAME_FILE_CON, outfile.suff);
      }
      else
      {
         sTarget[0] = EOS;
         sFile = um_strdup_printf("%s%s", old_outfile.name, old_outfile.suff);
      }

      if (no_images)
      {
         voutlnf("%s<a id=\"%s\" href=\"%s\"%s>%s</a>", sep, sIDName, sFile, sTarget, lang.html_home);
      }
      else
      {
      	 char border[20];
      	 
      	 strcpy(border, " border=\"0\"");
#if 0
         if (html_doctype == HTML5)
            border[0] = EOS;
#endif
         get_giflink_data(idxEnabled, &sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         voutlnf("<a id=\"%s\" href=\"%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s></a>",
            sIDName, sFile, sTarget, sGifName, lang.html_home, lang.html_home, border, sGifSize, xhtml_closer);
      }
      free(sFile);
   }
}





/*******************************************************************************
*
*  html_back_giflink():
*     create and output link to 'back page' for HTML navigation bar
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_back_giflink(const int idxEnabled, const int idxDisabled, const char *sep, _BOOL head)
{
   char      target[64],
             backpage[256],
             href[256],
             alt[256],
            *tok;
   char      sGifSize[128];
   const char *sGifName;
   char      sIDName[32];       /* string buffer for anchor ID name */
   _UWORD     uiW, uiH;
   
   switch (idxEnabled)
   {
   case GIF_HM_INDEX:
      strcpy(sIDName, "UDO_nav_hm");
      break;
   
   case GIF_LF_INDEX:
      strcpy(sIDName, "UDO_nav_lf");
      break;
   
   case GIF_RG_INDEX:
      strcpy(sIDName, "UDO_nav_rg");
      break;
   
   default:
      strcpy(sIDName, "UDO_nav_up");
      break;
   }
   
   /* mark ID as unique */
   if (head)
      strcat(sIDName, "_HEAD");
   else
      strcat(sIDName, "_FOOT");
   
   target[0] = EOS;
   
   if (sDocHtmlBackpage[0] != EOS)
   {
      strcpy(backpage, sDocHtmlBackpage);
      tok = strtok(backpage, "\'");
      strcpy(href, tok);
      del_right_spaces(href);
      tok = strtok(NULL, "\'");

      if (tok != NULL)
      {
         strcpy(alt, tok);
         auto_quote_chars(alt, TRUE);
      }
      else
         strcpy(alt, href);
      
      if (html_frames_layout)
      {
         sprintf(target, " target=\"_top\"");
      }

      if (no_images)
      {
         voutlnf("%s<a name=\"%s\" href=\"%s\"%s>%s</a>", sep, sIDName, href, target, alt);
      }
      else
      {
      	 char border[20];
      	 
      	 strcpy(border, " border=\"0\"");
#if 0
         if (html_doctype == HTML5)
            border[0] = EOS;
#endif
         get_giflink_data(idxEnabled, &sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         voutlnf("<a id=\"%s\" href=\"%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\"%s%s%s></a>",
            sIDName, href, target, sGifName, alt, alt, border, sGifSize, xhtml_closer);
      }
   }
   else
   {
      if (no_images)
      {
         voutlnf("%s^^^", sep);
      }
      else
      {
      	 char border[20];
      	 
      	 strcpy(border, " border=\"0\"");
#if 0
         if (html_doctype == HTML5)
            border[0] = EOS;
#endif
         /* Disabled Button ausgeben */
         get_giflink_data(idxDisabled, &sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifName, border, sGifSize, xhtml_closer);
      }
   }
}



/*******************************************************************************
*
*  html_hb_line():
*     create and output HTML head and bottom bar lines
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_hb_line(_BOOL head)
{
   int       i,
             ti,
             li;
   char      s[512],
             anchor[512],
             sGifSize[128],
             sTarget[64];
   const char *colptr;
   const char *sGifFile;
   _BOOL   old_autorefoff;
   _BOOL   for_main_file;
   _UWORD     uiW, uiH;
   char      buffer[32] = "";
   
   /* set global flag */
   head_foot = head;
   
   /* Herausfinden, fuer welchen Node die Kopf- und Fusszeile */
   /* ausgegeben werden soll. Beim Mergen ist der Index nicht */
   /* immer gleich dem Nodezaehler im 2. Durchlauf! */
   
   /* Um das Tildenproblem zu loesen, muss ueber lab[] */
   /* gegangen werden, da nur dort die Tilden noch nicht */
   /* bearbeitet wurden und nur so die Referenzen fuer die */
   /* Kopfzeilen gefunden werden! */
   
   ti = p2_toc_counter;
   
   if (ti > 0)
   {
      if (html_merge_node6)
      {
         ti = last_n5_index;
         
         if (ti <= 0)
            ti = last_n4_index; 

         if (ti <= 0)
            ti = last_n3_index; 

         if (ti <= 0)
            ti = last_n2_index; 
         
         if (ti <= 0)
            ti = last_n1_index; 
      }

      if (html_merge_node5)
      {
         ti = last_n4_index;
         
         if (ti <= 0)
            ti = last_n3_index; 

         if (ti <= 0)
            ti = last_n2_index; 
         
         if (ti <= 0)
            ti = last_n1_index; 
      }

      if (html_merge_node4)
      {
         ti = last_n3_index;
         
         if (ti <= 0)
            ti = last_n2_index; 
         
         if (ti <= 0)
            ti = last_n1_index; 
      }
      
      if (html_merge_node3)
      {
         ti = last_n2_index;
         
         if (ti <= 0)
            ti = last_n1_index; 
      }
      
      if (html_merge_node2)
         ti = last_n1_index;
      
      if (html_merge_node1)
         ti = 0;
   }
   
   for_main_file = (toc[ti]->toctype == TOC_TOC);

   /* ------------------------------------------- */
   /* ignore_headline/ignore_bottomline testen    */
   /* ------------------------------------------- */
   
   if (head && toc[ti]->ignore_headline)
      return;
   
   if (!head && toc[ti]->ignore_bottomline)
      return;
   
   old_autorefoff = bDocAutorefOff;
   bDocAutorefOff = FALSE;
   
   if (!head)
   {
      if (!html_modern_layout && !html_frames_layout)
      {
         if (!((no_footers || toc[ti]->ignore_footer) && (no_bottomlines || toc[ti]->ignore_bottomline)))
         {
         	outln(xhtml_hr);
         	outln("");
         }
      }
   }
   
#if 1
   colptr = NULL;
   if (html_modern_layout)
      colptr = html_color_string(&html_modern_backcolor);
   if (html_frames_layout)
      colptr = html_color_string(&html_frames_backcolor);
   if (colptr)
   {
      s[0] = EOS;
      if (colptr[0] != EOS)
      {
         sprintf(s, " bgcolor=\"%s\"", colptr);
      }
      voutlnf("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\"%s>", s);
      voutlnf("<tr>");
#if 0
      if (html_doctype == HTML5)
      {
         voutlnf("<td class=\"UDO_td_valign_top\">");
      }
      else
#endif
      {
         voutlnf("<td valign=\"top\">");
      }
   }
#endif
   
   /* ------------------------------------------------ */
   /* Verweis auf die Homepage erzeugen                */
   /* ------------------------------------------------ */
   html_home_giflink(GIF_HM_INDEX, GIF_NOHM_INDEX, "[ ", head);
   
   /* ------------------------------------------------ */
   /* Verweis auf das uebergeordnete Kapitel erzeugen  */
   /* ------------------------------------------------ */
   switch (toc[ti]->toctype)
   {
   case TOC_TOC:                          /* Verweis auf Backpage erzeugen */
      html_back_giflink(GIF_UP_INDEX, GIF_NOUP_INDEX, "| ", head);
      break;

   case TOC_NODE1:                        /* Weiter nach oben geht es nicht */
      /* Verweis auf index.htm erzeugen */
      html_index_giflink(GIF_UP_INDEX, GIF_NOUP_INDEX, "| ", head);
      break;
   
   case TOC_NODE2:                        /* Verweis auf aktuellen !node */
   case TOC_NODE3:                        /* Verweis auf aktuellen !subnode */
   case TOC_NODE4:                        /* Verweis auf aktuellen !subsubnode */
   case TOC_NODE5:                        /* Verweis auf aktuellen !subsubsubnode */
   case TOC_NODE6:                        /* Verweis auf aktuellen !subsubsubsubnode */
      switch (toc[ti]->toctype)
      {
      case TOC_NODE2:
         li = toc[last_n1_index]->labindex;
         strcpy(buffer, "html_hb_line[1]");
         break;
      case TOC_NODE3:
         li = toc[last_n2_index]->labindex;
         strcpy(buffer, "html_hb_line[2]");
         break;
      case TOC_NODE4:
         li = toc[last_n3_index]->labindex;
         strcpy(buffer, "html_hb_line[3]");
         break;
      case TOC_NODE5:
         li = toc[last_n4_index]->labindex;
         strcpy(buffer, "html_hb_line[4]");
         break;
      case TOC_NODE6:
         li = toc[last_n5_index]->labindex;
         strcpy(buffer, "html_hb_line[5]");
      }
            
      if (lab[li]->name != 0)
      {
         um_strcpy(s, lab[li]->name, 512, buffer);

         string2reference(anchor, li, TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
         replace_once(s, lab[li]->name, anchor);

         if (no_images)
         {
            replace_once(s, lab[li]->name, " ^^^");
            strinsert(s, "| ");
         }
   
         out(s);
      }
      break;
   }
   
   /* --------------------------------------------------- */
   /* Verweis auf die vorherige Seite erzeugen            */
   /* default:            das letzte Kapitel              */
   /* !html_merge_node1:  kein Aufruf dieser Routine      */
   /* !html_merge_node2:  der letzte !node                */
   /* !html_merge_node3:  der letzte !subnode             */
   /* !html_merge_node4:  der letzte !subsubnode          */
   /* !html_merge_node5:  der letzte !subsubsubnode       */
   /* !html_merge_node6:  der letzte !subsubsubsubnode    */
   /* --------------------------------------------------- */
   if (for_main_file)
   {
      /* Deaktivierten Link/Bild ausgeben */
      if (no_images)
      {
         outln("| &lt;&lt;&lt;");
      }
      else
      {
      	 char border[20];
      	 
      	 strcpy(border, " border=\"0\"");
#if 0
         if (html_doctype == HTML5)
            border[0] = EOS;
#endif
         get_giflink_data(GIF_NOLF_INDEX, &sGifFile, &uiW, &uiH);
         sGifSize[0] = EOS;
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifFile, border, sGifSize, xhtml_closer);
      }
   }
   else
   {
      i = toc[ti]->prev_index;

      if (i == 0)
      {
         /* Erster Node -> Zurueck zum Hauptfile */
         html_home_giflink(GIF_LF_INDEX, GIF_NOLF_INDEX, "| ", head);
      }
      else
      {
         if (i > 0)
         {
            li = toc[i]->labindex;
            um_strcpy(s, lab[li]->name, 512, "html_hb_line[5]");

            string2reference(anchor, li, TRUE, GIF_LF_NAME, uiGifLfWidth, uiGifLfHeight);
            replace_once(s, lab[li]->name, anchor);

            if (no_images)
            {
                                          /* [voja][R6PL17] deleted the + at "+replace_once" call */
               replace_once(s, lab[li]->name, " &lt;&lt;&lt;");
               strinsert(s, "| ");
            }
            
            out(s);
         }
         else
         {
            /* disabled nach links */
            if (no_images)
            {
               outln("| &lt;&lt;&lt;");
            }
            else
            {
      	       char border[20];
      	 
      	       strcpy(border, " border=\"0\"");
#if 0
               if (html_doctype == HTML5)
                   border[0] = EOS;
#endif
               get_giflink_data(GIF_NOLF_INDEX, &sGifFile, &uiW, &uiH);
               sGifSize[0] = EOS;
               if (uiW != 0 && uiH != 0)
               {
                  sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
               }
               voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifFile, border, sGifSize, xhtml_closer);
            }
         }
      }
   }
   
   /* ------------------------------------------- */
   /* Verweis auf die nachfolgende Seite erzeugen */
   /* ------------------------------------------- */
   i = 0;
   
   if (for_main_file)
   {
      if (p1_toc_counter > 0 && !html_merge_node1)
      {
         i = 1;
      }
   }
   else
   {
      i = toc[ti]->next_index;
      
      if (i > 0)
      {
         if (html_merge_node2)
         {
            if (toc[i]->toctype != TOC_NODE1)
            {
               i = 0;
            }
         }
         else if (html_merge_node3)
         {
            if (    toc[i]->toctype != TOC_NODE1 
                 && toc[i]->toctype != TOC_NODE2
               )
            {
               i = 0;
            }
         }
         else if (html_merge_node4)
         {
            if (    toc[i]->toctype != TOC_NODE1 
                 && toc[i]->toctype != TOC_NODE2 
                 && toc[i]->toctype != TOC_NODE3
               )
            {
               i = 0;
            }
         }
         else if (html_merge_node5)
         {
            if (    toc[i]->toctype != TOC_NODE1 
                 && toc[i]->toctype != TOC_NODE2 
                 && toc[i]->toctype != TOC_NODE3 
                 && toc[i]->toctype != TOC_NODE4
               )
            {
               i = 0;
            }
         }
         else if (html_merge_node6)
         {
            if (    toc[i]->toctype != TOC_NODE1 
                 && toc[i]->toctype != TOC_NODE2 
                 && toc[i]->toctype != TOC_NODE3 
                 && toc[i]->toctype != TOC_NODE4
                 && toc[i]->toctype != TOC_NODE5
               )
            {
               i = 0;
            }
         }
      }
   }
   
   if (i > 0)
   {
      li = toc[i]->labindex;
      um_strcpy(s, lab[li]->name, 512, "html_hb_line[5]");

      string2reference(anchor, li, TRUE, GIF_RG_NAME, uiGifRgWidth, uiGifRgHeight);
      replace_once(s, lab[li]->name, anchor);

      if (no_images)
      {
         replace_once(s, lab[li]->name, " &gt;&gt;&gt;");
         strinsert(s, "| ");
      }
   
      out(s);
   }
   else
   {
      /* disabled nach rechts */
      if (no_images)
      {
         outln("| &gt;&gt;&gt;");
      }
      else
      {
      	 char border[20];
      	 
      	 strcpy(border, " border=\"0\"");
#if 0
         if (html_doctype == HTML5)
            border[0] = EOS;
#endif
         get_giflink_data(GIF_NORG_INDEX, &sGifFile, &uiW, &uiH);
         sGifSize[0] = EOS;
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         voutlnf("<img src=\"%s\" alt=\"\" title=\"\"%s%s%s>", sGifFile, border, sGifSize, xhtml_closer);
      }
   }
   
   if (html_modern_layout || html_frames_layout)
   {
      if (iDocHtmlSwitchLanguage >= 0 && sDocHtmlSwitchLanguage[0] != EOS)
      {
#if 0
         if (html_doctype == HTML5)
         {
            outln("</td><td class=\"UDO_td_valign_top UDO_td_align_right\">");
         }
         else
#endif
         {
            outln("</td><td valign=\"top\" align=\"right\">");
         }
         if (no_images)
         {
            switch (iDocHtmlSwitchLanguage)
            {
            case TOGER:
               voutlnf("<a href=\"%s\">Deutsch</a>", sDocHtmlSwitchLanguage);
               break;
            case TOENG:
               voutlnf("<a href=\"%s\">English</a>", sDocHtmlSwitchLanguage);
               break;
            }
         }
         else
         {
      	 char border[20];
      	 
      	 strcpy(border, " border=\"0\"");
#if 0
         if (html_doctype == HTML5)
            border[0] = EOS;
#endif
            if (html_frames_layout)
            {
               strcpy(sTarget, " target=\"_top\"");
            }
            else
            {
               sTarget[0] = EOS;
            }
            
            sGifSize[0] = EOS;
            
            switch (iDocHtmlSwitchLanguage)
            {
            case TOGER:
               get_giflink_data(GIF_GER_INDEX, &sGifFile, &uiW, &uiH);
               if (uiW != 0 && uiH != 0)
               {
                  sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
               }
               voutlnf("<a href=\"%s\"%s><img src=\"%s\" alt=\"Deutsch\" title=\"Deutsche Version dieses Dokuments\"%s%s%s></a>",
                  sDocHtmlSwitchLanguage, sTarget, sGifFile, border, sGifSize, xhtml_closer);
               break;
               
            case TOENG:
               get_giflink_data(GIF_ENG_INDEX, &sGifFile, &uiW, &uiH);
               if (uiW != 0 && uiH != 0)
               {
                  sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
               }
               voutlnf("<a href=\"%s\"%s><img src=\"%s\" alt=\"English\" title=\"English version of this document\"%s%s%s></a>",
                  sDocHtmlSwitchLanguage, sTarget, sGifFile, border, sGifSize, xhtml_closer);
               break;
            }
         }
      }
   }
   
#if 1
   if (html_modern_layout || html_frames_layout)
   {
      outln("</td></tr></table>");
   }
#endif
   
   if (no_images)
   {
      outln("]");
   }
   
   if (head)
   {
      if (!html_modern_layout && !html_frames_layout)
      {
         outln("");
         outln(xhtml_hr);
         outln("");
      }
   }
   
   bDocAutorefOff = old_autorefoff;
}



/*******************************************************************************
*
*  html_node_bar_modern():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_node_bar_modern(void)
{
   register int   i;
   int            li;
   _UWORD          uiW, uiH;
   char           the_ref[1024],
                 *ptr;
   const char    *ptrImg;
   const char    *noImg = "";
   char           sGifSize[80],
                  sAlignOn[128],
                  sAlignOff[128];
   char border[20];

   sGifSize[0] = EOS;
   
   strcpy(border, " border=\"0\"");
#if 0
   if (html_doctype == HTML5)
      border[0] = EOS;
#endif

#if 1
   voutlnf("<table id=\"UDO_menu\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"%s\">", html_modern_width);
   
   switch (html_modern_alignment)
   {
   case ALIGN_LEFT:
      sprintf(sAlignOn, "<tr><td>%s", sHtmlPropfontStart);
      sprintf(sAlignOff, "%s</td></tr>", sHtmlPropfontEnd);
      break;
   case ALIGN_CENT:
#if 0
      if (html_doctype == HTML5)
      {
         sprintf(sAlignOn, "<tr><td class=\"UDO_td_align_center\">%s", sHtmlPropfontStart);
      }
      else
#endif
      {
         sprintf(sAlignOn, "<tr><td align=\"center\">%s", sHtmlPropfontStart);
      }
      sprintf(sAlignOff, "%s</td></tr>", sHtmlPropfontEnd);
      break;
   case ALIGN_RIGH:
#if 0
      if (html_doctype == HTML5)
      {
         sprintf(sAlignOn, "<tr><td class=\"UDO_td_align_right\">%s", sHtmlPropfontStart);
      }
      else
#endif
      {
         sprintf(sAlignOn, "<tr><td align=\"right\">%s", sHtmlPropfontStart);
      }
      sprintf(sAlignOff, "%s</td></tr>", sHtmlPropfontEnd);
      break;
   }
#else
   strcpy(sAlignOn, "<center>");
   strcpy(sAlignOff, "</center>");
#endif
   
   if (p2_toc_counter == 0 && titdat.authoricon_active != NULL)
   {
      if (titdat.authoriconActiveWidth != 0 && titdat.authoriconActiveHeight != 0)
         sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconActiveWidth, titdat.authoriconActiveHeight);
      voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" alt=\"\" title=\"\"%s%s%s></a>%s",
         sAlignOn, old_outfile.name, outfile.suff, titdat.authoricon_active, border, sGifSize, xhtml_closer, sAlignOff);
   }
   else
   {
      if (titdat.authoricon != NULL)
      {
         if (titdat.authoriconWidth != 0 && titdat.authoriconHeight != 0)
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconWidth, titdat.authoriconHeight);
         
         voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" alt=\"\" title=\"\"%s%s%s></a>%s",
            sAlignOn, old_outfile.name, outfile.suff, titdat.authoricon, border, sGifSize, xhtml_closer, sAlignOff);
      }
   }
   
   if (toc[0]->icon != NULL)
   {
      ptrImg = noImg;
      uiW = uiH = 0;
      
      if (toc[0]->icon != NULL)
      {
         ptrImg = toc[0]->icon;
         uiW = toc[0]->uiIconWidth;
         uiH = toc[0]->uiIconHeight;
      }
      
      if (toc[0]->icon_active != NULL)
      {
         if (p2_toc_counter == 0)
         {
            ptrImg = toc[0]->icon_active;
            uiW = toc[0]->uiIconActiveWidth;
            uiH = toc[0]->uiIconActiveHeight;
         }
      }
      
      if (ptrImg != noImg)
      {
         sGifSize[0] = EOS;
         
         if (uiW != 0 && uiH != 0)
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" alt=\"\" title=\"\"%s%s%s></a>%s",
            sAlignOn, old_outfile.name, outfile.suff, ptrImg, border, sGifSize, xhtml_closer, sAlignOff);
      }
   }
   
   for (i = 1; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL)
      {
         if (toc[i]->toctype == TOC_NODE1 && !toc[i]->invisible)
         {
            convert_toc_item(toc[i]);
            li = toc[i]->labindex;
   
            ptrImg = noImg;
            uiW = uiH = 0;
            
            if (toc[i]->icon != NULL)
            {
               ptrImg = toc[i]->icon;
               uiW = toc[i]->uiIconWidth;
               uiH = toc[i]->uiIconHeight;
            }

            if (toc[i]->icon_active != NULL)
            {
               if (toc[i]->n1 == p2_toc_n1)
               {
                  ptrImg = toc[i]->icon_active;
                  uiW = toc[i]->uiIconActiveWidth;
                  uiH = toc[i]->uiIconActiveHeight;
               }
            }
            
            string2reference(the_ref, li, FALSE, ptrImg, uiW, uiH);
            
            if (ptrImg != noImg && toc[i]->icon_text != NULL)
            {
               ptr = strstr(the_ref, "</a>");
               
               if (ptr != NULL)
               {
                  strinsert(ptr, toc[i]->icon_text);
                  strinsert(ptr, xhtml_br);
               }
            }
            voutlnf("%s%s%s", sAlignOn, the_ref, sAlignOff);
         }
      }
      else
      {
         break;
      }
   }
   outln("</table>");
}





/*******************************************************************************
*
*  html_save_frameset():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html_save_frameset(void)
{
   char   add[1024],
          add2[256],
          s[512],
          f1[512],
          f2[512];

   if (html_doctype >= XHTML_STRICT)
   {
      outln("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Frameset//EN\"");
      outln("        \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd\">");
      voutlnf("<html lang=\"%s\" xml:lang=\"%s\">", lang.html_lang, lang.html_lang);
   }
   else
   {
      outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Frameset//EN\"");
      outln("        \"http://www.w3.org/TR/html4/frameset.dtd\">");
      voutlnf("<html lang=\"%s\">", lang.html_lang);
   }
   
   outln("<head>");
   output_html_meta(TRUE);
   
   if (titdat.htmltitle != NULL && titdat.htmltitle[0] != EOS)
   {
      voutlnf("<title>%s</title>", titdat.htmltitle);
   }
   else
   {
      voutlnf("<title>%s</title>", titleprogram);
   }
   
   outln("</head>");
   
   add[0] = EOS;
   if (html_frames_noborder)
      strcat(add, " border=\"0\" frameborder=\"0\" framespacing=\"0\"");
   
   add2[0] = EOS;
   if (html_frames_noresize)
      strcat(add2, " noresize=\"noresize\"");
   if (html_frames_noscroll)
      strcat(add2, " scrolling=\"no\"");
   
   if (html_frames_toc_title == NULL)
   {
      sprintf(f1, "<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\"%s%s>",
         html_name_prefix, FRAME_FILE_TOC, outfile.suff, FRAME_NAME_TOC, add2, xhtml_closer);
   }
   else
   {
      sprintf(f1, "<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\" title=\"%s\"%s%s>",
         html_name_prefix, FRAME_FILE_TOC, outfile.suff, FRAME_NAME_TOC, html_frames_toc_title, add2, xhtml_closer);
   }
   
   if (html_frames_con_title == NULL)
   {
      sprintf(f2, "<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\"%s>",
         html_name_prefix, FRAME_FILE_CON, outfile.suff, FRAME_NAME_CON, xhtml_closer);
   }
   else
   {
      sprintf(f2, "<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\" title=\"%s\"%s>",
         html_name_prefix, FRAME_FILE_CON, outfile.suff, FRAME_NAME_CON, html_frames_con_title, xhtml_closer);
   }
   
   switch (html_frames_position)
   {
   case POS_LEFT:
      voutlnf("<frameset cols=\"%s,*\"%s>", html_frames_width, add);
      outln(f1);
      outln(f2);
      break;
   case POS_RIGHT:
      voutlnf("<frameset cols=\"*,%s\"%s>", html_frames_width, add);
      outln(f2);
      outln(f1);
      break;
   case POS_TOP:
      voutlnf("<frameset rows=\"%s,*\"%s>", html_frames_height, add);
      outln(f1);
      outln(f2);
      break;
   case POS_BOTTOM:
      voutlnf("<frameset rows=\"*,%s\"%s>", html_frames_height, add);
      outln(f2);
      outln(f1);
      break;
   }
   
   outln("</frameset>");
   
   /* Noframes for browsers who do not know frames */
   outln("<noframes>");
   c_maketitle();
   
   c_tableofcontents();
   
   /* Set both to FALSE in order that the title page and the
   table of contents will be written in the frame again */
   
   called_maketitle = FALSE;
   called_tableofcontents = FALSE;
   outln("</noframes>");
   outln("</html>");
   
   /* Das Inhaltverzeichnis fuer den linken Frame ausgeben */
   
#if 1
   sprintf(outfile.name, "%s%s", html_name_prefix, FRAME_FILE_TOC);
#else
   strcpy(outfile.name, FRAME_FILE_TOC);
#endif

   if (!html_make_file())
      return;
   
   output_html_doctype();
   outln("<html>");
   outln("<head>");
   voutlnf("<title>%s</title>", lang.contents);
   output_html_meta(FALSE);
   outln("</head>");
   add[0] = EOS;
   
   if (html_frames_backimage != 0)
   {
      sprintf(s, " background=\"%s\"", file_lookup(html_frames_backimage));
      strcat(add, s);
   }
   
   if (html_frames_backcolor.set)
   {
      sprintf(s, " bgcolor=\"%s\"", html_color_string(&html_frames_backcolor));
      strcat(add, s);
   }
   
   if (html_frames_linkcolor.set)
   {
      sprintf(s, " link=\"%s\"", html_color_string(&html_frames_linkcolor));
      strcat(add, s);
   }
   
   if (html_frames_alinkcolor.set)
   {
      sprintf(s, " alink=\"%s\"", html_color_string(&html_frames_alinkcolor));
      strcat(add, s);
   }
   
   if (html_frames_vlinkcolor.set)
   {
      sprintf(s, " vlink=\"%s\"", html_color_string(&html_frames_vlinkcolor));
      strcat(add, s);
   }

   voutlnf("<body%s class=\"frame_toc\">", add);
   
   outln(sHtmlPropfontStart);
   html_node_bar_frames();
   voutlnf("%s", sHtmlPropfontEnd);
   outln("</body>");
   outln("</html>");
   
   /* Neue Datei fuer das erste Kapitel anlegen */
   
   sprintf(outfile.name, "%s%s", html_name_prefix, FRAME_FILE_CON);
   html_make_file();
}





/*******************************************************************************
*
*  html_node_bar_frames():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void html_node_bar_frames(void)
{
   register int   i;
   int            li;
   _UWORD          uiW, uiH;
   char           the_ref[1024],
                 *ptr,
                  sGifSize[80];
   const char    *ptrImg;
   char           alignOn[128],
                  alignOff[128],
                  divOn[32],
                  divOff[32],
                  rowOn[16],
                  rowOff[16];
   const char    *noImg= "";
   char border[20];

   strcpy(border, " border=\"0\"");
#if 0
   if (html_doctype == HTML5)
      border[0] = EOS;
#endif

   switch (html_frames_position)
   {
   case POS_LEFT:
   case POS_RIGHT:
      divOn[0] = divOff[0] = rowOn[0] = rowOff[0] = EOS;
      
      switch (html_frames_alignment)
      {
      case ALIGN_LEFT:
         sprintf(alignOn, "<tr><td>%s", sHtmlPropfontStart);
         sprintf(alignOff, "%s</td></tr>", sHtmlPropfontEnd);
         break;
      case ALIGN_CENT:
#if 0
         if (html_doctype == HTML5)
         {
            sprintf(alignOn, "<tr><td class=\"UDO_td_align_center\">%s", sHtmlPropfontStart);
         }
         else
#endif
         {
            sprintf(alignOn, "<tr><td align=\"center\">%s", sHtmlPropfontStart);
         }
         sprintf(alignOff, "%s</td></tr>", sHtmlPropfontEnd);
         break;
      case ALIGN_RIGH:
#if 0
         if (html_doctype == HTML5)
         {
            sprintf(alignOn, "<tr><td class=\"UDO_td_align_right\">%s", sHtmlPropfontStart);
         }
         else
#endif
         {
            sprintf(alignOn, "<tr><td align=\"right\">%s", sHtmlPropfontStart);
         }
         sprintf(alignOff, "%s</td></tr>", sHtmlPropfontEnd);
         break;
      }
      outln(divOn);
      outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\">");
      outln(rowOn);
      break;
      
   default:
#if 0
      if (html_doctype == HTML5)
      {
         sprintf(alignOn, "<td class=\"td_nowrap\">%s", sHtmlPropfontStart);
      }
      else
#endif
      {
         sprintf(alignOn, "<td nowrap=\"nowrap\">%s", sHtmlPropfontStart);
      }
      sprintf(alignOff, "%s</td>", sHtmlPropfontEnd);
      strcpy(rowOn, "<tr>");
      strcpy(rowOff, "</tr>");
      switch (html_frames_alignment)
      {
      case ALIGN_LEFT:
         divOn[0] = EOS;
         divOff[0] = EOS;
         break;
      case ALIGN_CENT:
#if 0
         if (html_doctype == HTML5)
         {
            strcpy(divOn, "<div class=\"UDO_div_align_center\">");
         }
         else
#endif
         {
            strcpy(divOn, "<div align=\"center\">");
         }
         strcpy(divOff, "</div>");
         break;
      case ALIGN_RIGH:
#if 0
         if (html_doctype == HTML5)
         {
            strcpy(divOn, "<div class=\"UDO_div_align_right\">");
         }
         else
#endif
         {
            strcpy(divOn, "<div align=\"right\">");
         }
         strcpy(divOff, "</div>");
         break;
      }
      outln(divOn);
      outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">");
      outln(rowOn);
      break;
   }
   
   if (titdat.authoricon != NULL)
   {
      sGifSize[0] = EOS;
      if (titdat.authoriconWidth != 0 && titdat.authoriconHeight != 0)
         sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconWidth, titdat.authoriconHeight);
      voutlnf("%s<a href=\"%s%s%s\" target=\"%s\"><img src=\"%s%s\" alt=\"\" title=\"\"%s%s%s></a>%s",
         alignOn, html_name_prefix, FRAME_FILE_CON, outfile.suff,
         FRAME_NAME_CON, titdat.authoricon, "" /*sDocImgSuffix*/, border, sGifSize, xhtml_closer, alignOff);
   }
   
   for (i = 1; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL)
      {
         if (toc[i]->toctype == TOC_NODE1 && !toc[i]->invisible)
         {
            convert_toc_item(toc[i]);
            li = toc[i]->labindex;
            
            ptrImg = noImg;
            uiW = uiH = 0;
            
            if (toc[i]->icon != NULL)
            {
               ptrImg = toc[i]->icon;
               uiW = toc[i]->uiIconWidth;
               uiH = toc[i]->uiIconHeight;
            }
            
            if (toc[i]->icon_active != NULL)
            {
               if (toc[i]->n1 == p2_toc_n1)
               {
                  ptrImg = toc[i]->icon_active;
                  uiW = toc[i]->uiIconActiveWidth;
                  uiH = toc[i]->uiIconActiveHeight;
               }
            }
            
            string2reference(the_ref, li, FALSE, ptrImg, uiW, uiH);

            /* Im Inhaltsverzeichnis DARF nicht <a href="#..."> stehen! */
            /* kleiner Zwischenhack, da Frames mit gemergten Nodes wohl */
            /* niemand ernsthaft verwenden werden wird. */
            
            ptr = strstr(the_ref, "href=\"#");
            if (ptr != NULL)
            {
               ptr += 6;
               strinsert(ptr, outfile.suff);
               strinsert(ptr, FRAME_FILE_CON);
               strinsert(ptr, html_name_prefix);
            }
            
            if (ptrImg != noImg && toc[i]->icon_text != NULL)
            {
               ptr = strstr(the_ref, "</a>");
               if (ptr != NULL)
               {
                  strinsert(ptr, toc[i]->icon_text);
                  strinsert(ptr, xhtml_br);
               }
            }
            voutlnf("%s%s%s", alignOn, the_ref, alignOff);
         }
      }
      else
      {
         break;
      }
   }
   outln(rowOff);
   outln("</table>");
   outln(divOff);
}





/*******************************************************************************
*
*  html_headline():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html_headline(void)
{
   char bgCmd[512];
   
   if (html_modern_layout)
   {
      bgCmd[0] = EOS;
      
      if (html_modern_backimage != 0)
         sprintf(bgCmd, " background=\"%s\"", file_lookup(html_modern_backimage));

      outln("<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" width=\"100%\">");
      outln("<tr>");
      
      if (html_modern_backcolor.set)
      {
#if 0
         if (html_doctype == HTML5)
         {
            voutlnf("<td class=\"UDO_td_valign_top\" width=\"%s\" bgcolor=\"%s\"%s>%s",
               html_modern_width,
               html_color_string(&html_modern_backcolor),
               bgCmd,
               sHtmlPropfontStart);
         }
         else
#endif
         {
            voutlnf("<td valign=\"top\" width=\"%s\" bgcolor=\"%s\"%s>%s",
               html_modern_width,
               html_color_string(&html_modern_backcolor),
               bgCmd,
               sHtmlPropfontStart);
         }
      }
      else
      {
#if 0
         if (html_doctype == HTML5)
         {
            voutlnf("<td class=\"UDO_td_valign_top\" width=\"%s\"%s>%s", 
               html_modern_width,
               bgCmd,
               sHtmlPropfontStart);
         }
         else
#endif
         {
            voutlnf("<td valign=\"top\" width=\"%s\"%s>%s",
               html_modern_width,
               bgCmd,
               sHtmlPropfontStart);
         }
      }
      
      html_node_bar_modern();
      voutlnf("%s</td>", sHtmlPropfontEnd);
#if 0
      if (html_doctype == HTML5)
      {
         voutlnf("<td class=\"UDO_td_valign_top\" width=\"100%%\">%s", sHtmlPropfontStart);
      }
      else
#endif
      {
         voutlnf("<td valign=\"top\" width=\"100%%\">%s", sHtmlPropfontStart);
      }
   }
   
   if (!no_headlines)
      html_hb_line(TRUE);

   if (html_modern_layout || html_frames_layout)
   {
      outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\">");
      outln("<tr>");
#if 0
      if (html_doctype == HTML5)
      {
         voutlnf("<td class=\"UDO_td_valign_top\" width=\"8\">&nbsp;</td>");
         voutlnf("<td class=\"UDO_td_valign_top\" width=\"100%%\">%s", sHtmlPropfontStart);
      }
      else
#endif
      {
         voutlnf("<td valign=\"top\" width=\"8\">&nbsp;</td>");
         voutlnf("<td valign=\"top\" width=\"100%%\">%s", sHtmlPropfontStart);
      }
   }
}



/*******************************************************************************
*
*  html_bottomline():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html_bottomline(void)
{
   if (html_modern_layout)
   {
      voutlnf("%s", sHtmlPropfontEnd);
      html_footer();
#if 1
      outln("</td></tr></table>");
#endif
      if (!no_bottomlines)
         html_hb_line(FALSE);
      voutlnf("%s</td></tr>", sHtmlPropfontEnd);
      outln("</table>");
      return;
   }

   if (html_frames_layout)
   {
      voutlnf("%s", sHtmlPropfontEnd);
      html_footer();
#if 1
      outln("</td></tr></table>");
#endif
      if (!no_bottomlines)
         html_hb_line(FALSE);
      return;
   }

   html_footer();
   if (!no_bottomlines)
      html_hb_line(FALSE);
}



/*******************************************************************************
*
*  html_footer():
*     outputs address segment with copyright notes webmaster URL, and email
*
*  Notes:
*     This function reacts on the existance and content of the following !docinfo
*     parameters:
*
*     !docinfo [domain_link]    e.g. "http://www.mydomain.com"
*     !docinfo [domain_name]    e.g. "My Domain"
*     !docinfo [contact_link]   e.g. "mailto:webmaster@mydomain.com"
*     !docinfo [contact_name]   e.g. "Webmaster"
*
*
*     When [domain_link] and [domain_name] are available, the URL link is 
*     formatted like this: 
*     '<a href="[domain_link]">[domain_name]</a>'
*
*     When only [domain_link] is available, it is repeated in the visible link:
*     '<a href="[domain_link]">[domain_link]</a>'
*
*     When only [domain_name] is available, no link is created but the
*     [domain_name] is output as simple text in the HTML footer.
*
*
*     When [contact_link] and [contact_name] are available, the email URL 
*     link is formatted like this:
*     '<a href="mailto:[contact_link]">[contact_name]</a>
*
*     When only [contact_link] is available, it is repeated in the visible 
*     email link:
*     '<a href="mailto:[contact_link]">[contact_link]</a>
*
*     When only [contact_name] is available, no link is created but the
*     [contact_name] is output as simple text in the HTML footer.
*
*
*  Special feature:
*     Chances are that someone wants to use a web URL instead of an email address
*     [contact_link]. Today, many web users try to avoid having their email
*     address being placed visibly in web pages, to let email addresses harvester 
*     bots not find their email addresses for spam purposes. To avoid the complexity
*     to distinguish mail addresses from URLs and to give the user full control over
*     the output, the contact_link is used as it was set by
*     !docinfo [contact_link]. So mail addresses must be set as
*     "mailto:webmaster@example.com".
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html_footer(void)
{
   _BOOL   has_counter,
             has_main_counter;
   char      s[512];
   int       has_content = 0;
   
   has_counter = toc[p2_toc_counter]->counter_command != 0;
   has_main_counter = sCounterCommand != 0;
   
   if (!has_counter && !has_main_counter)
      if (no_footers || toc[p2_toc_counter]->ignore_footer)
         return;
   
   if (titdat.domain_link  != NULL)
      has_content  = 0x1000;

   if (titdat.domain_name  != NULL)
      has_content += 0x0100;

   if (titdat.contact_link != NULL)
      has_content += 0x0010;

   if (titdat.contact_name != NULL)
      has_content += 0x0001;
                                          /* draw a horizontal line */   
   if (has_counter || has_main_counter || has_content)
   {
      if (html_doctype < XHTML_STRICT)
         outln(HTML_HR);
      else
         outln(XHTML_HR);
   }
   
   if (has_counter)                       /* r6pl4: Counterkommando ausgeben */
   {
      outln(file_lookup(toc[p2_toc_counter]->counter_command));
   }
   else if (has_main_counter)
   {
      outln(file_lookup(sCounterCommand));
   }
   
   if (no_footers)
      return;
   
   if (footer_buffer[0] != EOS)
   {
      outln(footer_buffer);
      return;
   }
   
   
   if (!has_content)
   {
      no_footers = TRUE;
      return;
   }
   
                                          /* output address segment */
   /* sprintf(footer_buffer, "<address>%sCopyright &copy; ", sHtmlPropfontStart); */
   sprintf(footer_buffer, "<address>%s%s &copy; ", sHtmlPropfontStart, lang.copyright);

   s[0] = EOS;                            /* clear buffer */
   
   switch (has_content)
   {
   case 0x1111:                           /* domain_link + domain_name + contact_link + contact_name */
      sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"%s\">%s</a>)",
         titdat.domain_link, 
         titdat.domain_name,
         titdat.contact_link, 
         titdat.contact_name);
      break;
         
   case 0x1110:                           /* domain_link + domain_name + contact_link               */
      sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"%s\">%s</a>)",
         titdat.domain_link, 
         titdat.domain_name,
         titdat.contact_link, 
         titdat.contact_link);
      break;
      
   case 0x1101:                           /* domain_link + domain_name                + contact_name */
      sprintf(s, "<a href=\"%s\">%s</a> (%s)",
         titdat.domain_link, 
         titdat.domain_name,
         titdat.contact_name);
      break;
      
   case 0x1100:                           /* domain_link + domain_name                               */
      sprintf(s, "<a href=\"%s\">%s</a>",
         titdat.domain_link, 
         titdat.domain_name);
      break;
      
   case 0x1011:                           /* domain_link               + contact_link + contact_name */
      sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"%s\">%s</a>)",
         titdat.domain_link, 
         titdat.domain_link,
         titdat.contact_link, 
         titdat.contact_name);
      break;
   
   case 0x1010:                           /* domain_link               + contact_link                */
      sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"%s\">%s</a>)",
         titdat.domain_link, 
         titdat.domain_link,
         titdat.contact_link, 
         titdat.contact_link);
      break;
         
   case 0x1001:                           /* domain_link                              + contact_name */
      sprintf(s, "<a href=\"%s\">%s</a> (%s)",
         titdat.domain_link, 
         titdat.domain_link, 
         titdat.contact_name);
      break;
         
   case 0x1000:                           /* domain_link                                             */
      sprintf(s, "<a href=\"%s\">%s</a>",
         titdat.domain_link, 
         titdat.domain_link);
      break;

   case 0x0111:                           /*               domain_name + contact_link + contact_name */
      sprintf(s, "%s (<a href=\"%s\">%s</a>)",
         titdat.domain_name,
         titdat.contact_link, 
         titdat.contact_name);
      break;

   case 0x0110:                           /*               domain_name + contact_link                */
      sprintf(s, "%s (<a href=\"%s\">%s</a>)",
         titdat.domain_name,
         titdat.contact_link, 
         titdat.contact_link);
      break;

   case 0x0101:                           /*               domain_name                + contact_name */
      sprintf(s, "%s (%s)",
         titdat.domain_name,
         titdat.contact_name);
      break;

   case 0x0100:                           /*               domain_name                               */
      sprintf(s, "%s",
         titdat.domain_name);
      break;

   case 0x0011:                           /*                             contact_link + contact_name */
      sprintf(s, "<a href=\"%s\">%s</a>",
         titdat.contact_link, 
         titdat.contact_name);
      break;

   case 0x0010:                           /*                             contact_link                */
      sprintf(s, "<a href=\"%s\">%s</a>",
         titdat.contact_link, 
         titdat.contact_link);
      break;

   case 0x0001:                           /*                                            contact_name */
      sprintf(s, "%s",
         titdat.contact_name);
   }

   strcat(footer_buffer, s);
   
   if (html_doctype < XHTML_STRICT)
      strcat(footer_buffer, "<br>\n");
   else
      strcat(footer_buffer, "<br />\n");
   
   strcpy(s, lang.update);
   auto_quote_chars(s, TRUE);
   strcat(footer_buffer, s);
   strcat(footer_buffer, " ");
   
   strcpy(s, lang.today);
   auto_quote_chars(s, TRUE);
   strcat(footer_buffer, s);
   
   strcat(footer_buffer, sHtmlPropfontEnd);
   strcat(footer_buffer, "</address>\n");
   
   outln(footer_buffer);
}





/*******************************************************************************
*
*  comp_index_html():
*     Compares two index entries.
*
*  return:
*     -1: s1  < s2
*      0: s1 == s2
*      1: s1  > s2
*
******************************************|************************************/

LOCAL int comp_index_html(

const void  *_p1,              /* */
const void  *_p2)              /* */
{
   char      p1_tocname[512];  /* buffer for 1st entry name in TOC */
   char      p2_tocname[512];  /* buffer for 2nd entry name in TOC */

                                          /* cast the pointers to right structure */
   const HTML_INDEX *p1 = (const HTML_INDEX *)_p1;
   const HTML_INDEX *p2 = (const HTML_INDEX *)_p2;

   strcpy(p1_tocname, p1->sortname);      /* copy the entry names */
   strcpy(p2_tocname, p2->sortname);

   if (!html_ignore_8bit)                 /* V6.5.20 [gs] */
   {
      recode_chrtab(p1_tocname,CHRTAB_HTML);
      recode_chrtab(p2_tocname,CHRTAB_HTML);
   }

#if 0

   /* fd:2010-02-18: no longer required as we flatten HTML_INDEX.sortname first! */
   
   switch (iEncodingTarget)
   {
   case CODE_UTF8:                        /* n-byte encodings */
      return str_UTF_sort_cmp(p1_tocname, p2_tocname);
      
   default:                               /* 1-byte encodings */
      return str_sort_cmp(p1_tocname, p2_tocname);
   }
#endif

                                          /* Instead of strcmp v6.5.20 [gs] */
   return str_sort_cmp(p1_tocname, p2_tocname);
}





/*******************************************************************************
*
*  save_html_index():
*     This functions creates a temporary index file for HTML index generation.
*
*  return:
*     FALSE on errors
*     TRUE  if index could be saved
*
******************************************|************************************/

GLOBAL _BOOL save_html_index(void)
{
   FILE        *uif;              /* ^ to temporary index file */
   size_t       i;                /* counter */
   int          j;                /* counter */
   int          html_merge;       /* */
   size_t       num_index;        /* # of entries in index file */
   HTML_INDEX  *html_index;       /* ^ to HTML_INDEX array */
   _UWORD        thisc,            /* single char for comparison */
                lastc;            /* last char from comparison */
   char         htmlname[512];    /* */
   char         dummy[512];       /* */
   char         suff[100];        /* */
   char         cLabel[512];      /* */
   char        *tocname;          /* */
   char        *escapedtocname;   /* */
   char         jumplist[4096];   /* buffer string for A-Z navigation bar */
   char         thisc_char[42];   /* buffer string for converted thisc */
   char         thisc_label[42];  /* buffer string for HTML convenient converted thisc */

   
   num_index = 0;                         /* first we count how much entries we need */
   
   for (j = 1; j <= p1_lab_counter; j++)  /* check all collected labels */
   {
      if (lab[j] != NULL && lab[j]->ignore_index == FALSE)
         num_index++;
   }
   
   if (num_index == 0)                    /* index file will not be created */
      return FALSE;

   uif = udofile_tmpname("_udoind");      /* create temp. file name */

   if (!uif)                              /* no file pointer */
      return FALSE;
   
   fprintf(uif, "!newpage\n");            /* output index page stuff in UDO format */
   fprintf(uif, "!sloppy\n\n");
   fprintf(uif, "!node* %s\n", lang.index);
   fprintf(uif, "!html_name indexudo\n");
   
   if (!bDocAutorefOff)                   /* don't auto-reference the index page! */
      fprintf(uif, "!autoref [off]\n");

                                          /* we need memory */   
   html_index = (HTML_INDEX *)malloc(num_index * sizeof(HTML_INDEX));
   
   if (html_index == NULL)                /* fatal error! */
   {
      fclose(uif);
      return FALSE;
   }
   
   
   /* --- create index array --- */
   
   num_index = 0;
   
   for (j = 1; j <= p1_lab_counter; j++)
   {
      if (lab[j] != NULL  && lab[j]->ignore_index == FALSE)
      {
         html_index[num_index].toc_index = lab[j]->tocindex;
         html_index[num_index].is_node   = lab[j]->is_node;

                                          /* set ^ to name field in structure */
         tocname = html_index[num_index].tocname;
         strcpy(tocname, lab[j]->name);   /* copy name to structure */

         replace_macros(tocname);
         c_internal_styles(tocname);
         delete_all_divis(tocname);
         replace_udo_tilde(tocname);
         replace_udo_nbsp(tocname);
         del_html_styles(tocname);
         
                                          /* copy the name as we are going to flatten it */
         strcpy(html_index[num_index].sortname, tocname);
         
                                          /* get character for sorting purposes */
         html_index[num_index].codepoint = str_flatten(html_index[num_index].sortname);
         
         num_index++;
                                          /* ignore Table of Contents! */
         if (strcmp(tocname, HTML_LABEL_CONTENTS) == 0)
            num_index--;
                                          /* ignore indexudo page! */
         if (strcmp(tocname, lang.index) == 0)
            num_index--;
      }
   }
   
   
   /* --- sort the index (by HTML_INDEX.sortname!) --- */
   
   qsort(html_index, num_index, sizeof(HTML_INDEX), comp_index_html);


   /* --- create index A-Z jumplist --- */
   
   lastc = EOS;                           /* clear buffer for last character */
   
   strcpy(jumplist, "<div class=\"UDO_index_list\">\n");
   
   for (i = 0; i < num_index; i++)
   {
      thisc = html_index[i].codepoint;
      
      unicode2char(thisc,thisc_label);
      strcpy(thisc_char, thisc_label);    /* just convert it once, we need it often */

      label2html(thisc_label);            /* convert critical characters to HTML standards */
      
      if (thisc != lastc)
      {
                                          /* set anchor entry for index A-Z list */
         if (lastc == EOS)
            sprintf(dummy, "<a href=\"%s%s\">%s</a>\n", "#", thisc_label, thisc_char);
         else
            sprintf(dummy, " | <a href=\"%s%s\">%s</a>\n", "#", thisc_label, thisc_char);
         
         strcat(jumplist, dummy);
         
         lastc = thisc;
      }
   }
   
   strcat(jumplist, "</div>  <!-- UDO_index_list -->\n");
   
   
   /* --- output index --- */
   
   fprintf(uif, "!begin_raw\n");
   
   fprintf(uif, "%s", jumplist);          /* output A-Z jumplist */
   
   lastc = EOS;                           /* reset buffer for last character */
   
   for (i = 0; i < num_index; i++)
   {
      thisc = html_index[i].codepoint;
      
      unicode2char(thisc,thisc_label);
      strcpy(thisc_char, thisc_label);    /* just convert it once, we need it often */

      label2html(thisc_label);            /* convert critical characters to HTML standards */
      
      if (thisc != lastc)
      {
         if (lastc != EOS)                /* close previous character group of index entries */
            fprintf(uif, "</p>\n");
         
                                          /* start index group */
         fprintf(uif, "\n<p class=\"UDO_index_group\">\n");
         
         if (num_index > 100)             /* set jump entry for index A-Z list */
         {
            if (html_doctype == HTML5)
            {
               fprintf(uif, "<span class=\"UDO_index_name\"><a id=\"%s\"></a>%s</span>%s\n",
                  thisc_label, thisc_char, HTML_BR);
            }
            else
            {
               fprintf(uif, "<span class=\"UDO_index_name\"><a name=\"%s\"></a>%s</span>%s\n",
                  thisc_label, thisc_char, HTML_BR);
            }
         }
         else
         {
            if (html_doctype == HTML5)
            {
               fprintf(uif, "<a id=\"%s\"></a>\n", thisc_label);
            }
            else
            {
               fprintf(uif, "<a name=\"%s\"></a>\n", thisc_label);
            }
         }
         
         lastc = thisc;
      }
      
      strcpy(dummy, html_index[i].tocname);
      
      if (!html_ignore_8bit)
         recode_chrtab(dummy,CHRTAB_HTML);/* convert HTML characters to system characters  */

      get_html_filename(html_index[i].toc_index, htmlname, &html_merge);
   
      /* v6.5.15 [vj] need to make a copy of this, because we need to change it */
      /* fd:20071121: value increased (100 -> 512), as .tocname is 512 chars long */
      escapedtocname = um_physical_strcpy(html_index[i].tocname, 512, "save_html_index [1]");
      
      if (escapedtocname != NULL)
         replace_all(escapedtocname, "!", "&#33;");

      if (html_index[i].is_node)          /* this index entry points to another file */
      {
         fsplit(htmlname, dummy, dummy, dummy, suff);
         
         if (suff[0] == EOS)
         {
            if (html_merge)
            {
               fprintf(uif, "<a href=\"%s%s%s%s\">%s</a>",
                  htmlname, outfile.suff, "#", escapedtocname, escapedtocname);
            }
            else
            {
               fprintf(uif, "<a href=\"%s%s\">%s</a>",
                  htmlname, outfile.suff, escapedtocname);
            }
         }
         else
         {
            if (html_merge)
            {
               fprintf(uif, "<a href=\"%s%s%s\">%s</a>",
                  htmlname, "#", escapedtocname, escapedtocname);
            }
            else
            {
               fprintf(uif, "<a href=\"%s\">%s</a>",
                  htmlname, escapedtocname);
            }
         }
         fprintf(uif, "%s\n", HTML_BR);   /* end the entry line */
      }
      else                                /* this index entry is a label in another file */
      {
         strcpy (cLabel, html_index[i].tocname);
         
         if (!no_index && use_label_inside_index)
         {
            label2html (cLabel);
            
            /* v6.5.13 [vj] Compiler-Warnung beseitigt, # wurde in String ausgelagert,
            da der gcc sonst meckert: "toc.c:3940:17: warning: unknown escape sequence '\#'" */
            fprintf(uif, "<a href=\"%s%s%s%s\">%s</a>",
               htmlname, outfile.suff, "#", cLabel, escapedtocname);
            
            fprintf(uif, "%s\n", HTML_BR);   /* end the entry line */
         }
      }
      
      free(escapedtocname);            /* v6.5.15 [vj] var can be freed now */
   }
   
   fprintf(uif, "</p>\n\n");
   
   fprintf(uif, "%s", jumplist);          /* repeat A-Z jumplist */
   
   fprintf(uif, "!end_raw\n");
   
   fclose(uif);
   
   token_reset();
   
   strcpy(token[0], "!include");          /* sollte safe sein, da ein Token auf jeden Fall so lang werden kann :-) [vj] */
   
   um_strcpy(token[1], udofile.full, MAX_TOKEN_LEN+1, "save_html_index [2]");
   
   token_counter = 2;
   
   c_include();   
   
/* printf("%s\n", udofile.full); */
   remove(udofile.full);

   free((void *)html_index);
   
   return TRUE;
}





/*******************************************************************************
*
*  add_pass1_index_udo():
*     ???
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void add_pass1_index_udo(void)
{
   save_html_index();
   token_reset();
}





/*******************************************************************************
*
*  hh_headline():
*     ???
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void hh_headline(void)
{
#if 0
   if (!no_headlines)
      html_hb_line(TRUE);
#endif
}





/*******************************************************************************
*
*  hh_headline():
*     ???
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void hh_bottomline(void)
{
#if 0
   if (!no_bottomlines)
      html_hb_line(FALSE);
#endif
}





/*******************************************************************************
*
*  print_htmlhelp_contents():
*     ???
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void print_htmlhelp_contents(

FILE        *file,           /* */
const char  *indent,         /* */
const int    ti)             /* */
{
   char      filename[512],  /* */
             tocname[512];   /* */
   int       html_merge;     /* */
   
   
   if (ti > 0)
   {
      get_html_filename(ti, filename, &html_merge);
      um_strcpy(tocname, toc[ti]->name, 512, "print_htmlhelp_contents[1]");
   }
   else
   {
      strcpy(filename, old_outfile.name);
      
      tocname[0] = EOS;
   
      if (tocname[0] == EOS && titleprogram[0] != EOS)
         um_strcpy(tocname, titleprogram, 512, "print_htmlhelp_contents[2]");
      
      if (tocname[0] == EOS && called_tableofcontents)
         um_strcpy(tocname, lang.contents, 512, "print_htmlhelp_contents[3]");
      
      if (tocname[0] == EOS && called_maketitle)
         um_strcpy(tocname, lang.title, 512, "print_htmlhelp_contents[4]");
   }

   del_html_styles(tocname);

   fprintf(file, "%s<li><object type=\"text/sitemap\">\n", indent);
   fprintf(file, "%s<param name=\"Name\" value=\"%s\">\n", indent, tocname);
   fprintf(file, "%s<param name=\"Local\" value=\"%s%s\">\n", indent, filename, outfile.suff);
   fprintf(file, "%s</object>\n", indent);
}





/*******************************************************************************
*
*  save_htmlhelp_contents():
*     ???
*
*  return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

GLOBAL _BOOL save_htmlhelp_contents(

const char       *filename)            /* */
{
   FILE          *file;                /* */
   register int   i;                   /* */
   _BOOL        last_n = TRUE;       /* */
   _BOOL        last_sn = FALSE;     /* */
   _BOOL        last_ssn = FALSE;    /* */
   _BOOL        last_sssn = FALSE;   /* */
   _BOOL        last_ssssn = FALSE;  /* */
   _BOOL        last_sssssn = FALSE; /* */
   _BOOL        inApx = FALSE;       /* */
   
   
   file = myFwopen(filename, FTHHC);

   if (!file)
      return FALSE;

   save_upr_entry_outfile(filename);

   fprintf(file, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n");
   fprintf(file, "<html>\n");
   fprintf(file, "<head>\n");
   fprintf(file, "<meta name=\"GENERATOR\" content=\"UDO Version %s.%s %s for %s\">\n", UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS);
   fprintf(file, "<!-- Sitemap 1.0 -->\n");
   fprintf(file, "</head>\n");
   fprintf(file, "<body>\n");
   fprintf(file, "<ul>\n");

                                          /* r6pl10: Eintrag fuer erste Seite */
   print_htmlhelp_contents(file, "\t", 0);
   
   fprintf(file, "</ul>\n");
   fprintf(file, "<ul>\n");

   for (i = 1; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);

         if (!inApx && toc[i]->appendix)
         {
                                          /* r6pl13: Anhang mit ausgeben, hier den ersten Node im Anhang */
            inApx = TRUE;

            if (last_n)
               fprintf(file, "</ul>\n");
               
            if (last_sn)
               fprintf(file, "\t</ul>\n</ul>\n");
               
            if (last_ssn)
               fprintf(file, "\t\t</ul>\n\t</ul>\n</ul>\n");
               
            if (last_sssn)
               fprintf(file, "\t\t\t</ul>\n\t\t</ul>\n\t</ul>\n</ul>\n");
               
            if (last_ssssn)
               fprintf(file, "\t\t\t\t</ul>\n\t\t\t</ul>\n\t\t</ul>\n</ul>\n</ul>\n");
               
            if (last_sssssn)
               fprintf(file, "\t\t\t\t\t</ul>\n\t\t\t\t</ul>\n\t\t\t</ul>\n</ul>\n</ul>\n");

            last_n = last_sn = last_ssn = last_sssn = last_ssssn = last_sssssn = FALSE;
#if 0
            fprintf(file, "<ul>\t<li><object type=\"text/sitemap\">\n");
            fprintf(file, "\t\t<param name=\"Name\" value=\"%s\">\n", lang.appendix);
            fprintf(file, "\t\t</object>\n");
#endif
            fprintf(file, "<ul>\n");
         }

         if (toc[i]->n1 != 0)
         {
            switch (toc[i]->toctype)
            {
            case TOC_NODE1:               /* a chapter */
               if (last_sn)
               {
                  fprintf(file, "\t</ul>\n");
                  last_sn = FALSE;
               }

               if (last_ssn)
               {
                  fprintf(file, "\t\t</ul>\n\t</ul>\n");
                  last_ssn = FALSE;
               }
               
               if (last_sssn)
               {
                  fprintf(file, "\t\t\t</ul>\n\t\t</ul>\n\t</ul>\n");
                  last_sssn = FALSE;
               }
               
               if (last_ssssn)
               {
                  fprintf(file, "\t\t\t\t</ul>\n\t\t\t</ul>\n\t</ul>\n");
                  last_ssssn = FALSE;
               }
               
               if (last_sssssn)
               {
                  fprintf(file, "\t\t\t\t\t</ul>\n\t\t\t\t</ul>\n\t</ul>\n");
                  last_sssssn = FALSE;
               }
               
               last_n = TRUE;
               print_htmlhelp_contents(file, "\t", i);
               break;

            case TOC_NODE2:               /* Ein Abschnitt */
               if (last_n)
               {
                  fprintf(file, "\t<ul>\n");
                  last_n = FALSE;
               }
               
               if (last_ssn)
               {
                  fprintf(file, "\t\t</ul>\n");
                  last_ssn = FALSE;
               }
               
               if (last_sssn)
               {
                  fprintf(file, "\t\t\t</ul>\n\t\t</ul>\n");
                  last_sssn = FALSE;
               }
               
               if (last_ssssn)
               {
                  fprintf(file, "\t\t\t\t</ul>\n\t\t\t</ul>\n\t</ul>\n");
                  last_ssssn = FALSE;
               }
 
               if (last_sssssn)
               {
                  fprintf(file, "\t\t\t\t\t</ul>\n\t\t\t\t</ul>\n\t</ul>\n");
                  last_sssssn = FALSE;
               }
 
               last_sn = TRUE;
               print_htmlhelp_contents(file, "\t\t", i);
               break;

            case TOC_NODE3:               /* Ein Unterabschnitt */
               if (last_n)
               {
                  fprintf(file, "<ul>\n\t<ul>\n");
                  last_n = FALSE;
               }

               if (last_sn)
               {
                  fprintf(file, "\t\t<ul>\n");
                  last_sn = FALSE;
               }
               
               if (last_sssn)
               {
                  fprintf(file, "\t\t\t</ul>\n");
                  last_sssn = FALSE;
               }

               if (last_ssssn)
               {
                  fprintf(file, "\t\t\t\t</ul>\n\t\t\t</ul>\n\t</ul>\n");
                  last_ssssn = FALSE;
               }
 
               if (last_sssssn)
               {
                  fprintf(file, "\t\t\t\t\t</ul>\n\t\t\t\t</ul>\n\t</ul>\n");
                  last_sssssn = FALSE;
               }
 
               last_ssn = TRUE;
               print_htmlhelp_contents(file, "\t\t\t", i);
               break;

            case TOC_NODE4:               /* Ein Paragraph */
               if (last_n)
               {
                  fprintf(file, "\t<ul>\n\t\t<ul>\n\t\t\t<ul>\n");
                  last_n = FALSE;
               }
               
               if (last_sn) 
               {
                  fprintf(file, "\t<ul>\n\t\t<ul>\n");   
                  last_sn = FALSE;
               }
               
               if (last_ssn)
               {
                  fprintf(file, "\t\t\t<ul>\n");  
                  last_ssn = FALSE;
               }

               if (last_ssssn)
               {
                  fprintf(file, "\t\t\t\t</ul>\n\t\t\t</ul>\n\t</ul>\n");
                  last_ssssn = FALSE;
               }

               if (last_sssssn)
               {
                  fprintf(file, "\t\t\t\t\t</ul>\n\t\t\t\t</ul>\n\t</ul>\n");
                  last_sssssn = FALSE;
               }

               last_sssn = TRUE;
               print_htmlhelp_contents(file, "\t\t\t\t", i);
               break;

            case TOC_NODE5:               /* Ein Unterparagraph */
               if (last_n)
               {
                  fprintf(file, "\t<ul>\n\t\t<ul>\n\t\t\t<ul>\n\t\t\t\t<ul>\n");
                  last_n = FALSE;
               }
               
               if (last_sn)
               {
                  fprintf(file, "\t<ul>\n\t\t<ul>\n\t\t\t<ul>\n");
                  last_sn = FALSE;
               }
               
               if (last_ssn) 
               {
                  fprintf(file, "\t<ul>\n\t\t<ul>\n");   
                  last_ssn = FALSE;
               }
               
               if (last_sssn)
               {
                  fprintf(file, "\t\t\t<ul>\n");  
                  last_sssn = FALSE;
               }

               if (last_sssssn)
               {
                  fprintf(file, "\t\t\t\t\t</ul>\n\t\t\t\t</ul>\n\t</ul>\n");
                  last_ssssn = FALSE;
               }
 
               last_ssssn = TRUE;
               print_htmlhelp_contents(file, "\t\t\t\t\t", i);
               break;

            case TOC_NODE6:               /* Ein Unterparagraph */
               if (last_n)
               {
                  fprintf(file, "\t<ul>\n\t\t<ul>\n\t\t\t<ul>\n\t\t\t\t<ul>\n");
                  last_n = FALSE;
               }
               
               if (last_sn)
               {
                  fprintf(file, "\t<ul>\n\t\t<ul>\n\t\t\t<ul>\n");
                  last_sn = FALSE;
               }
               
               if (last_ssn) 
               {
                  fprintf(file, "\t<ul>\n\t\t<ul>\n");   
                  last_ssn = FALSE;
               }
               
               if (last_sssn)
               {
                  fprintf(file, "\t\t\t<ul>\n");  
                  last_sssn = FALSE;
               }

               if (last_ssssn)
               {
                  fprintf(file, "\t\t\t\t</ul>\n\t\t\t</ul>\n\t</ul>\n");
                  last_ssssn = FALSE;
               }
 
               last_sssssn = TRUE;
               print_htmlhelp_contents(file, "\t\t\t\t\t\t", i);
               
            }  /* switch (nodetype) */

         }  /* if (toc[i]->n1 != 0) */

      }  /* toc[i] != NULL && !toc[i]->invisible */

   }  /* for */

   if (last_sn)
      fprintf(file, "\t</ul>\n</ul>\n");
      
   if (last_ssn)
      fprintf(file, "\t\t</ul>\n\t</ul>\n");
      
   if (last_sssn)
      fprintf(file, "\t\t\t</ul>\n\t\t</ul>\n");
   
   if (last_ssssn)
      fprintf(file, "\t\t\t\t</ul>\n\t\t\t</ul>\n");
   
   if (last_sssssn)
      fprintf(file, "\t\t\t\t\t</ul>\n\t\t\t\t</ul>\n");


#if 0
   if (inApx)
      fprintf(file, "</ul>\n");
#endif

   fprintf(file, "</ul>\n");
   fprintf(file, "</body>\n</html>\n");

   fclose(file);

   return TRUE;
}





/*******************************************************************************
*
*  comp_index():
*     compares two index entries
*
*  return:
*     < 0, when s1 is smaller than s2
*     = 0, when s1 and s2 are identical
*     > 0, when s1 is greater than s2
*
******************************************|************************************/

LOCAL int comp_index(

const void  *_p1, 
const void  *_p2)
{
   const HTML_IDX *p1 = (const HTML_IDX *)_p1;
   const HTML_IDX *p2 = (const HTML_IDX *)_p2;

   return strcmp(p1->tocname, p2->tocname);
}





/*******************************************************************************
*
*  save_htmlhelp_index():
*     ???
*
*  return:
*     FALSE: error
*      TRUE: success
*
******************************************|************************************/

GLOBAL _BOOL save_htmlhelp_index(

const char   *filename)       /* */
{
   FILE      *file;           /* */
   size_t     i;              /* */
   int        j;              /* */
   int        html_merge;     /* */
   size_t     num_index;      /* */
   HTML_IDX  *html_index;     /* */
   char       htmlname[512];  /* */
   char      *tocname;        /* */
   
   
   num_index = 0;
   
#if 0
   for (i = 1; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      num_index++;
   }
#endif

   for (j = 1; j <= p1_lab_counter; j++)  /* erstmal zaehlen wieviel wir brauchen */
   {
      if (lab[j] != NULL)
         num_index++;
    }

   if (num_index == 0)
      return FALSE;                       /* Index-File wird nicht gebraucht */

   file = myFwopen(filename, FTHHK);

   if (file == NULL)
      return FALSE;

   html_index = (HTML_IDX *)malloc(num_index * sizeof(HTML_IDX));
   
   if (html_index == NULL)
   {
      fclose(file);
      return FALSE;
   }

   save_upr_entry_outfile(filename);

   fprintf(file, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n");
   fprintf(file, "<html>\n");
   fprintf(file, "<head>\n");
   fprintf(file, "<meta name=\"Generator\" content=\"UDO Version %s.%s %s for %s\">\n",UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS);

   if (titdat.author != NULL)
      fprintf(file, "<meta name=\"Author\" content=\"%s\">\n", titdat.author);
      
   fprintf(file, "<!-- Sitemap 1.0 -->\n");
   fprintf(file, "</head>\n");
   fprintf(file, "<body>\n");
   fprintf(file, "<ul>\n");

   num_index = 0;
   
#if 0
   for (j = 1; j <= p1_toc_counter; j++)
   {
      if (toc[j] != NULL && !toc[j]->invisible)
      {
         convert_toc_item(toc[j]);
         html_index[num_index].toc_index = j;
         strcpy(html_index[num_index].tocname, toc[j]->name);
         num_index++;
      }
   }
#endif

   for (j = 1; j <= p1_lab_counter; j++)  /* array aufbauen.. */
   {
      if (lab[j] != NULL)
      {
         html_index[num_index].toc_index = lab[j]->tocindex;
         tocname = html_index[num_index].tocname;
         strcpy(tocname, lab[j]->name);
         replace_macros(tocname);
         c_internal_styles(tocname);
/*       replace_udo_quotes(tocname); */
         delete_all_divis(tocname);
         replace_udo_tilde(tocname);
         replace_udo_nbsp(tocname);
         del_html_styles(tocname);
         num_index++;
      }
   }
   
   show_status_info(_("Sorting index..."));
   /* ..sortieren */
   qsort(html_index, num_index, sizeof(HTML_IDX), comp_index);
   
   /* ..und ausgeben */
   for (i = 0; i < num_index; i++)
   {
      get_html_filename(html_index[i].toc_index, htmlname, &html_merge);
      
      fprintf(file, "<li><object type=\"text/sitemap\"> <param name=\"Name\" value=\"%s\"> <param name=\"Local\" value=\"%s%s\"></object></li>\n",
            html_index[i].tocname,
            htmlname, 
            outfile.suff);
   }

   fprintf(file, "</ul>\n");
   fprintf(file, "</body>\n");
   fprintf(file, "</html>\n");
   fclose(file);

   free((void *)html_index);

   return TRUE;
}










/*******************************************************************************
*
*     CHAPTER COMMANDS
*
******************************************|************************************/

/*******************************************************************************
*
*  make_nodetype():
*     create a new node of the requested depth
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void make_nodetype(

int             nodetype,        /* TOC_NODE... */
const _BOOL   popup,           /* TRUE: this is a popup node */
const _BOOL   invisible)       /* TRUE: this is an invisible node */
{
   char         n[512],          /* */
                name[512],       /* */
                stgname[512],    /* */
                hx_start[16],    /* */
                hx_end[16],      /* */
                sTemp[512];      /* */
   char         numbers[512],    /* */
                nameNoSty[512],  /* */
                k[512];          /* */
   char         map[64],         /* */
                sGifSize[80],    /* */
                nodename[512];   /* */
   int          ti,              /* */
                ui,              /* */
                chapter,         /* */
                nr1 = 0,
                nr2 = 0,
                nr3 = 0,
                nr4,             /* */
                nr5,             /* */
                nr6;             /* */
   _BOOL      flag;            /* */
   _BOOL      do_index;        /* */
   
   _BOOL      html_mergenode;  /* */
   
   
   if (p2_toc_counter >= MAXTOCS)
   {
      bBreakInside = TRUE;
      return;
   }
   
   tokcpy2(name, 512);
   strcpy(stgname, name);

   
   if (name[0] == EOS)
   {
      switch (nodetype)
      {
      case TOC_NODE1:
         error_missing_parameter("!node");
         break;
         
      case TOC_NODE2:
         error_missing_parameter("!subnode");
         break;
         
      case TOC_NODE3:
         error_missing_parameter("!subsubnode");
         break;
         
      case TOC_NODE4:
         error_missing_parameter("!subsubsubnode");
         break;
         
      case TOC_NODE5:
         error_missing_parameter("!subsubsubsubnode");
         break;

      case TOC_NODE6:
         error_missing_parameter("!subsubsubsubsubnode");
      
      }
      
      return;
   }
   
   
   switch (nodetype)                      /* prepare some placeholders */
   {
   case TOC_NODE1:
      html_mergenode = html_merge_node1;
      break;
      
   case TOC_NODE2:
      html_mergenode = html_merge_node2;
      break;
      
   case TOC_NODE3:
      html_mergenode = html_merge_node3;
      break;
      
   case TOC_NODE4:
      html_mergenode = html_merge_node4;
      break;   
      
   case TOC_NODE5:
      html_mergenode = html_merge_node5;
      break;

   case TOC_NODE6:
      html_mergenode = html_merge_node6;
   }

   
   p2_lab_counter++;
   p2_toctype = nodetype;
   
   if ((desttype == TOHTM || desttype == TOHAH) && !html_mergenode)
   {
      check_endnode();
      html_bottomline();
   }
   
   if (desttype == TOMHH)
   {
      check_endnode();
      hh_bottomline();
   }
   
   check_styles(name);
   c_styles(name);
   
   
   switch (desttype)
   {
   case TOWIN:
   case TOWH4:
   case TOAQV:
      c_win_styles(name);
      break;
      
      
   case TORTF:
      c_rtf_styles(name);
      c_rtf_quotes(name);
      break;
      
      
   default:
      c_internal_styles(name);
   }
   
   
   replace_udo_quotes(name);
   delete_all_divis(name);
   replace_udo_tilde(name);
   replace_udo_nbsp(name);
   
   check_endnode();
   check_styleflags();
   check_environments_node();
   
   if (bInsideAppendix)
   {
      switch (nodetype)
      {
      case TOC_NODE1:
         p2_apx_n1++;
         p2_apx_n2 = 0;
         p2_apx_n3 = 0;
         p2_apx_n4 = 0;
         p2_apx_n5 = 0;
         p2_apx_n6 = 0;
         break;
         
      case TOC_NODE2:
         p2_apx_n2++;
         p2_apx_n3 = 0;
         p2_apx_n4 = 0;
         p2_apx_n5 = 0;
         p2_apx_n6 = 0;
         break;
         
      case TOC_NODE3:
         p2_apx_n3++;
         p2_apx_n4 = 0;
         p2_apx_n5 = 0;
         p2_apx_n6 = 0;
         break;
         
      case TOC_NODE4:
         p2_apx_n4++;
         p2_apx_n5 = 0;
         p2_apx_n6 = 0;
         break;
      
      case TOC_NODE5:
         p2_apx_n5++;
         p2_apx_n6 = 0;
         break;
         
      case TOC_NODE6:
         p2_apx_n6++;
      }
   }
   else
   {
      switch (nodetype)
      {
      case TOC_NODE1:
         p2_toc_n1++;
         p2_toc_n2 = 0;
         p2_toc_n3 = 0;
         p2_toc_n4 = 0;
         p2_toc_n5 = 0;
         p2_toc_n6 = 0;
         break;
         
      case TOC_NODE2:
         p2_toc_n2++;
         p2_toc_n3 = 0;
         p2_toc_n4 = 0;
         p2_toc_n5 = 0;
         p2_toc_n6 = 0;
         break;
         
      case TOC_NODE3:
         p2_toc_n3++;
         p2_toc_n4 = 0;
         p2_toc_n5 = 0;
         p2_toc_n6 = 0;
         break;
         
      case TOC_NODE4:
         p2_toc_n4++;
         p2_toc_n5 = 0;
         p2_toc_n6 = 0;
         break;
      
      case TOC_NODE5:
         p2_toc_n5++;
         p2_toc_n6 = 0;
         break;

      case TOC_NODE6:
         p2_toc_n6++;
      }
   }
   
   p2_toc_counter++;
   
   switch (nodetype)
   {
   case TOC_NODE1:
      curr_n1_index = p2_toc_counter;
      curr_n2_index = 0;
      curr_n3_index = 0;
      curr_n4_index = 0;
      curr_n5_index = 0;
      curr_n6_index = 0;
   
      last_n1_index = p2_toc_counter;
      last_n2_index = 0;
      last_n3_index = 0;
      last_n4_index = 0;
      last_n5_index = 0;
      last_n6_index = 0;
   
      nr1 = toc[p2_toc_counter]->nr1;
      break;
      
      
   case TOC_NODE2:
      curr_n2_index = p2_toc_counter;
      curr_n3_index = 0;
      curr_n4_index = 0;
      curr_n5_index = 0;
      curr_n6_index = 0;

      last_n2_index = p2_toc_counter;
      last_n3_index = 0;
      last_n4_index = 0;
      last_n5_index = 0;
      last_n6_index = 0;

      nr1 = toc[p2_toc_counter]->nr1;
      nr2 = toc[p2_toc_counter]->nr2;
      break;
      
      
   case TOC_NODE3:
      curr_n3_index = p2_toc_counter;
      curr_n4_index = 0;
      curr_n5_index = 0;
      curr_n6_index = 0;
   
      last_n3_index = p2_toc_counter;
      last_n4_index = 0;
      last_n5_index = 0;
      last_n6_index = 0;
   
      nr1 = toc[p2_toc_counter]->nr1;
      nr2 = toc[p2_toc_counter]->nr2;
      nr3 = toc[p2_toc_counter]->nr3;
      break;
      
      
   case TOC_NODE4:
      curr_n4_index = p2_toc_counter;
      curr_n5_index = 0;
      curr_n6_index = 0;
   
      last_n4_index = p2_toc_counter;
      last_n5_index = 0;
      last_n6_index = 0;
   
      nr1 = toc[p2_toc_counter]->nr1;
      nr2 = toc[p2_toc_counter]->nr2;
      nr3 = toc[p2_toc_counter]->nr3;
      nr4 = toc[p2_toc_counter]->nr4;
      break;
      
      
   case TOC_NODE5:
      curr_n5_index = p2_toc_counter;
      curr_n6_index = 0;

      last_n5_index = p2_toc_counter;
      last_n6_index = 0;

      nr1 = toc[p2_toc_counter]->nr1;
      nr2 = toc[p2_toc_counter]->nr2;
      nr3 = toc[p2_toc_counter]->nr3;
      nr4 = toc[p2_toc_counter]->nr4;
      nr5 = toc[p2_toc_counter]->nr5;
      break;

   case TOC_NODE6:
      curr_n6_index = p2_toc_counter;

      last_n6_index = p2_toc_counter;

      nr1 = toc[p2_toc_counter]->nr1;
      nr2 = toc[p2_toc_counter]->nr2;
      nr3 = toc[p2_toc_counter]->nr3;
      nr4 = toc[p2_toc_counter]->nr4;
      nr5 = toc[p2_toc_counter]->nr5;
      nr6 = toc[p2_toc_counter]->nr6;

   }
   
   
   (bInsideAppendix) ? (chapter = nr1) : (chapter = nr1 + toc_offset);
   
   n[0] = EOS;
   numbers[0] = EOS;
   
   if (!invisible)
   {
      if (bInsideAppendix)
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            sprintf(numbers, "%c", 
                        'A' + nr1 - 1);
            break;
            
         case TOC_NODE2:
            sprintf(numbers, "%c.%d", 
                        'A' + nr1 - 1, 
                        nr2 + subtoc_offset);
            break;
            
         case TOC_NODE3:
            sprintf(numbers, "%c.%d.%d", 
                        'A' + nr1 - 1, 
                        nr2 + subtoc_offset, 
                        nr3 + subsubtoc_offset);
            break;
            
         case TOC_NODE4:
            sprintf(numbers, "%c.%d.%d.%d",       
                        'A' + nr1 - 1, 
                        nr2 + subtoc_offset, 
                        nr3 + subsubtoc_offset, 
                        nr4 + subsubsubtoc_offset);
            break;
         
         case TOC_NODE5:
            sprintf(numbers, "%c.%d.%d.%d.%d",
                        'A' + nr1 - 1, 
                        nr2 + subtoc_offset, 
                        nr3 + subsubtoc_offset, 
                        nr4 + subsubsubtoc_offset, 
                        nr5 + subsubsubsubtoc_offset);
            break;

         case TOC_NODE6:
            sprintf(numbers, "%c.%d.%d.%d.%d.%d", 
                        'A' + nr1 - 1, 
                        nr2 + subtoc_offset, 
                        nr3 + subsubtoc_offset, 
                        nr4 + subsubsubtoc_offset, 
                        nr5 + subsubsubsubtoc_offset, 
                        nr6 + subsubsubsubsubtoc_offset);
         }
      }
      else
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            sprintf(numbers, "%d", 
                        chapter);
            break;
            
         case TOC_NODE2:
            sprintf(numbers, "%d.%d", 
                        chapter, 
                        nr2 + subtoc_offset);
            break;

         case TOC_NODE3:
            sprintf(numbers, "%d.%d.%d", 
                        chapter, 
                        nr2 + subtoc_offset, 
                        nr3 + subsubtoc_offset);
            break;
            
         case TOC_NODE4:
            sprintf(numbers, "%d.%d.%d.%d", 
                        chapter, 
                        nr2 + subtoc_offset, 
                        nr3 + subsubtoc_offset, 
                        nr4 + subsubsubtoc_offset);
            break;
         
         case TOC_NODE5:
            sprintf(numbers, "%d.%d.%d.%d.%d", 
                        chapter, 
                        nr2 + subtoc_offset, 
                        nr3 + subsubtoc_offset, 
                        nr4 + subsubsubtoc_offset, 
                        nr5 + subsubsubtoc_offset);
            break;

         case TOC_NODE6:
            sprintf(numbers, "%d.%d.%d.%d.%d.%d", 
                        chapter, 
                        nr2 + subtoc_offset, 
                        nr3 + subsubtoc_offset, 
                        nr4 + subsubsubtoc_offset, 
                        nr5 + subsubsubsubtoc_offset, 
                        nr6 + subsubsubsubsubtoc_offset);
         }
      }
   }
   
   if (bVerbose)
   {
	  char sInfMsg[256];
	  
      sprintf(sInfMsg, "[%s] ", numbers);
      show_status_node(sInfMsg, name);
   }
   
   if (no_numbers || invisible)
      numbers[0] = EOS;
   else
      strcat(numbers, " ");
   
   strcpy(current_chapter_name, name);
   strcpy(current_chapter_nr, numbers);
   
   do_index = (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index);
   
   if (desttype != TOWIN && desttype != TOWH4 && desttype != TOAQV && bCheckMisc)
      check_win_buttons(p2_toc_counter);
   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      set_inside_node(nodetype);
      
      if (invisible)
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            (use_style_book) ? voutlnf("\n\\chapter*{%s}", name) : voutlnf("\n\\section*{%s}", name);
            break;
         case TOC_NODE2:
            (use_style_book) ? voutlnf("\n\\section*{%s}", name) : voutlnf("\n\\subsection*{%s}", name);
            break;
         case TOC_NODE3:
            (use_style_book) ? voutlnf("\n\\subsection*{%s}", name) : voutlnf("\n\\subsubsection*{%s}", name);
            break;
         case TOC_NODE4:
            (use_style_book) ? voutlnf("\n\\subsubsection*{%s}", name) : voutlnf("\n\\paragraph*{%s}", name);
            break;
         case TOC_NODE5:
            (use_style_book) ? voutlnf("\n\\paragraph*{%s}", name) : voutlnf("\n\\subparagraph*{%s}", name);
            break;
         case TOC_NODE6:
            (use_style_book) ? voutlnf("\n\\paragraph*{%s}", name) : voutlnf("\n\\subparagraph*{%s}", name);
         }
      }
      else
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            (use_style_book) ? voutlnf("\n\\chapter{%s}", name) : voutlnf("\n\\section{%s}", name);
            break;
         case TOC_NODE2:
            (use_style_book) ? voutlnf("\n\\section{%s}", name)  : voutlnf("\n\\subsection{%s}", name);
            break;
         case TOC_NODE3:
            (use_style_book) ? voutlnf("\n\\subsection{%s}", name)  : voutlnf("\n\\subsubsection{%s}", name);
            break;
         case TOC_NODE4:
            (use_style_book) ? voutlnf("\n\\subsubsection{%s}", name)  : voutlnf("\n\\paragraph{%s}", name);
            break;
         case TOC_NODE5:
            (use_style_book) ? voutlnf("\n\\paragraph{%s}", name)  : voutlnf("\n\\subparagraph{%s}", name);
            break;
         case TOC_NODE6:
            (use_style_book) ? voutlnf("\n\\paragraph{%s}", name)  : voutlnf("\n\\subparagraph{%s}", name);
         }
      }
      
      label2tex(name);
      voutlnf("\\label{%s}", name);
      output_aliasses();
      
      if (desttype == TOPDL)
      {
         voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
         
         switch (nodetype)
         {
         case TOC_NODE1:
            voutlnf("\\pdfoutline goto num %d count %d {%s}", p2_lab_counter, toc[p2_toc_counter]->count_n2, name);
            break;
            
         case TOC_NODE2:
            voutlnf("\\pdfoutline goto num %d count %d {%s}", p2_lab_counter, toc[p2_toc_counter]->count_n3, name);
            break;
            
         case TOC_NODE3:
            voutlnf("\\pdfoutline goto num %d count %d {%s}", p2_lab_counter, toc[p2_toc_counter]->count_n4, name);
            break;
            
         case TOC_NODE4:
            voutlnf("\\pdfoutline goto num %d count 0 {%s}", p2_lab_counter, name);
            break;
            
         case TOC_NODE5:
            voutlnf("\\pdfoutline goto num %d count 0 {%s}", p2_lab_counter, name);
            break;

         case TOC_NODE6:
            voutlnf("\\pdfoutline goto num %d count 0 {%s}", p2_lab_counter, name);
         }
      }

      break;
   
   
   case TOLYX:
      set_inside_node(nodetype);

      out("\\layout ");
      
      if (invisible)
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            (use_style_book) ? outln("Chapter") : outln("Section*");
            break;
            
         case TOC_NODE2:
            (use_style_book) ? outln("Section*") : outln("Subsection*");
            break;
            
         case TOC_NODE3:
            (use_style_book) ? outln("Subsection*") : outln("Subsubsection*");
            break;
            
         case TOC_NODE4:
            (use_style_book) ? outln("Subsubsection*") : outln("Paragraph*");
            break;
            
         case TOC_NODE5:
            (use_style_book) ? outln("Subsubsection*") : outln("Paragraph*");
            break;

         case TOC_NODE6:
            (use_style_book) ? outln("Subsubsection*") : outln("Paragraph*");
         }
      }
      else
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            (use_style_book) ? outln("Chapter") : outln("Section");
            break;
            
         case TOC_NODE2:
            (use_style_book) ? outln("Section")  : outln("Subsection");
            break;
            
         case TOC_NODE3:
            (use_style_book) ? outln("Subsection")    : outln("Subsubsection");
            break;
            
         case TOC_NODE4:
            (use_style_book) ? outln("Subsubsection") : outln("Paragraph");
            break;
            
         case TOC_NODE5:
            (use_style_book) ? outln("Subsubsection") : outln("Paragraph");
            break;

         case TOC_NODE6:
            (use_style_book) ? outln("Subsubsection") : outln("Paragraph");
         }
      }
      
      indent2space(name);
      outln(name);
      break;
      
   
   case TOINF:
      set_inside_node(nodetype);

      output_texinfo_node(name);
      
      if (bInsideAppendix)
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            voutlnf("@appendix %s", name);
            break;
            
         case TOC_NODE2:
            voutlnf("@appendixsec %s", name);
            break;
            
         case TOC_NODE3:
            voutlnf("@appendixsubsec %s", name);
            break;
            
         case TOC_NODE4:
            voutlnf("@appendixsubsubsec %s", name);
            break;
            
         case TOC_NODE5:
            voutlnf("@appendixsubsubsec %s", name);
            break;

         case TOC_NODE6:
            voutlnf("@appendixsubsubsec %s", name);
         }
      }
      else
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            (invisible) ? (voutlnf("@chapheading %s", name)) : (voutlnf("@chapter %s", name));
            break;
            
         case TOC_NODE2:
            (invisible) ? (voutlnf("@heading %s", name)) : (voutlnf("@section %s", name));
            break;
            
         case TOC_NODE3:
            (invisible) ? (voutlnf("@subheading %s", name)) : (voutlnf("@subsection %s", name));
            break;
            
         case TOC_NODE4:
            (invisible) ? (voutlnf("@subsubheading %s", name)) : (voutlnf("@subsubsection %s", name));
            break;
            
         case TOC_NODE5:
            (invisible) ? (voutlnf("@subsubheading %s", name)) : (voutlnf("@subsubsection %s", name));
            break;

         case TOC_NODE6:
            (invisible) ? (voutlnf("@subsubheading %s", name)) : (voutlnf("@subsubsection %s", name));
         }
      }
      
      break;
      
   
   case TOTVH:
      set_inside_node(nodetype);
      
      if (numbers[0] != EOS)
         strcat(numbers, " ");
         
      output_vision_header(numbers, name);
      break;
      
   
   case TOSTG:
      stg_out_endnode();
      set_inside_node(nodetype);
      bInsidePopup = popup;
      node2stg(name);
      
      if (!do_index)
         outln("@indexoff");

      if (popup)
         voutlnf("@pnode \"%s\"", name);
      else
         voutlnf("@node \"%s\"", name);

      if (!do_index)
         outln("@indexon");
      
      if (!popup)
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            ui = 0;
            
            if (called_tableofcontents)
               outln("@toc \"Main\"");
               
            break;
            
            
         case TOC_NODE2:
            ui = toc[p2_toc_counter]->up_n1_index;
            break;
            
         case TOC_NODE3:
            ui = toc[p2_toc_counter]->up_n2_index;
            break;
            
         case TOC_NODE4:
            ui = toc[p2_toc_counter]->up_n3_index;
            break;
            
         case TOC_NODE5:
            ui = toc[p2_toc_counter]->up_n4_index;
            break;
            
         case TOC_NODE6:
            ui = toc[p2_toc_counter]->up_n5_index;
         }
         
         if (ui > 0)
         {
            strcpy(sTemp, toc[ui]->name);
            node2stg(sTemp);
            replace_2at_by_1at(sTemp);
            voutlnf("@toc \"%s\"", sTemp);
         }
      }
      
      stg_header(numbers, stgname, popup);
      break;
      
   
   case TOAMG:
      stg_out_endnode();
      set_inside_node(nodetype);
      
      node2stg(name);
      
      if (titleprogram[0] != EOS)
         voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
      else
         voutlnf("@node \"%s\" \"%s\"", name, name);
   
      switch (nodetype)
      {
      case TOC_NODE1:
         ui = 0;
         
         if (called_tableofcontents)
            outln("@toc \"Main\"");

         break;
         
         
      case TOC_NODE2:
         ui = toc[p2_toc_counter]->up_n1_index;
         break;
         
      case TOC_NODE3:
         ui = toc[p2_toc_counter]->up_n2_index;
         break;
         
      case TOC_NODE4:
         ui = toc[p2_toc_counter]->up_n3_index;
         break;
         
      case TOC_NODE5:
         ui = toc[p2_toc_counter]->up_n4_index;
         break;

      case TOC_NODE6:
         ui = toc[p2_toc_counter]->up_n5_index;
      }
      
      if (ui > 0)
      {
         strcpy(sTemp, toc[ui]->name);
         node2stg(sTemp);
         replace_2at_by_1at(sTemp);
         voutlnf("@toc \"%s\"", sTemp);
      }
   
      stg_header(numbers, stgname, FALSE);
      break;
      
   
   case TOMAN:
      set_inside_node(nodetype);
      
      outln("");
      
      switch (nodetype)
      {
      case TOC_NODE1:
      case TOC_NODE2:
         sprintf(n, " %s%s%s", BOLD_ON, name, BOLD_OFF);
         break;
      case TOC_NODE3:
      case TOC_NODE4:
      case TOC_NODE5:
      case TOC_NODE6:
         sprintf(n, " %s", name);
      }
      
      c_internal_styles(n);
      outln(n);
      break;
   
   
   case TONRO:
      set_inside_node(nodetype);
      
      if (nodetype == TOC_NODE1)
      {
         my_strupr(name);
         sprintf(n, ".SH %s", name);
      }
      if (nodetype == TOC_NODE2)
      {
         my_strupr(name);
         sprintf(n, ".SS %s", name);
      }
      if (nodetype == TOC_NODE3)
      {
         my_strupr(name);
         sprintf(n, ".TP\n.SS %s", name);
      }
      if (nodetype == TOC_NODE4)
      {
         my_strupr(name);
         sprintf(n, ".TP\n.SS %s", name);
      }
      if (nodetype == TOC_NODE5)
      {
         my_strupr(name);
         sprintf(n, ".TP\n.SS %s", name);
      }
      if (nodetype == TOC_NODE6)
      {
         my_strupr(name);
         sprintf(n, ".TP\n.SS %s", name);
      }

      c_internal_styles(n);
      outln(n);
      break;
   
   
   case TOASC:
      set_inside_node(nodetype);
      
      if (nodetype == TOC_NODE1)
      {
         outln("");
         outln("");
         
         if (use_style_book)
         {
            (bInsideAppendix) ? sprintf(n, "%s %s", lang.appendix, numbers) : sprintf(n, "%s %s", lang.chapter, numbers);

            del_right_spaces(n);
            output_ascii_line("=", zDocParwidth);
            outln(n);
            outln("");
            outln(name);
            output_ascii_line("=", zDocParwidth);
         }
         else
         {
            if (numbers[0] != EOS)
               strcat(numbers, " ");
         
            sprintf(n, "%s%s", numbers, name);
            outln(n);
            output_ascii_line("*", strlen(n));
         }
      }
      else
      {
         if (numbers[0] != EOS)
            strcat(numbers, " ");
         
         sprintf(n, "%s%s", numbers, name);
         outln("");
         outln(n);
      
         switch (nodetype)
         {
         case TOC_NODE2:
            output_ascii_line("=", strlen(n));
            break;
         case TOC_NODE3:
            output_ascii_line("-", strlen(n));
            break;
         case TOC_NODE4:
         case TOC_NODE5:
         case TOC_NODE6:
            ;
         }
      }
      
      outln("");
      break;
   
   
   case TOIPF:
      set_inside_node(nodetype);
      
      node2NrIPF(n, toc[p2_toc_counter]->labindex);
      map[0] = EOS;
      
      if (toc[p2_toc_counter]->mapping >= 0)
         sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
      
      if (bInsideAppendix)
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            voutlnf(":h1 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
            break;
            
         case TOC_NODE2:
            voutlnf(":h2 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
            break;
            
         case TOC_NODE3:
            voutlnf(":h3 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
            break;
            
         case TOC_NODE4:
            voutlnf(":h4 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
            break;
            
         case TOC_NODE5:
            voutlnf(":h5 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
            break;

         case TOC_NODE6:
            voutlnf(":h6 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
         }
      }
      else
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            voutlnf(":h1 id=%s%s.%s%s", n, map, numbers, name);
            break;
            
         case TOC_NODE2:
            voutlnf(":h2 id=%s%s.%s%s", n, map, numbers, name);
            break;
            
         case TOC_NODE3:
            voutlnf(":h3 id=%s%s.%s%s", n, map, numbers, name);
            break;
            
         case TOC_NODE4:
            voutlnf(":h4 id=%s%s.%s%s", n, map, numbers, name);
            break;
            
         case TOC_NODE5:
            voutlnf(":h5 id=%s%s.%s%s", n, map, numbers, name);
            break;

         case TOC_NODE6:
            voutlnf(":h6 id=%s%s.%s%s", n, map, numbers, name);
         }
      }
      
      break;
   
   
   case TOKPS:
      set_inside_node(nodetype);
   
      if (use_style_book)
      {
         (bInsideAppendix) ? sprintf(n, "%s %s", lang.appendix, numbers) : sprintf(n, "%s %s", lang.chapter, numbers);
         del_right_spaces(n);

         if (n[0] != EOS)
            strcat(n, " ");

         strcat(n, name);
         
         switch (nodetype)
         {
         case TOC_NODE1:
            outln("25 changeFontSize");
            break;
         case TOC_NODE2:
            outln("18 changeFontSize");
            break;
         case TOC_NODE3:
            outln("14 changeFontSize");
            break;
         case TOC_NODE4:
            outln("11 changeFontSize");
            break;
         case TOC_NODE5:
            outln("11 changeFontSize");
            break;
         case TOC_NODE6:
            outln("11 changeFontSize");
         }
      }
      else
      {
         if (numbers[0] != EOS)
            strcat(numbers, " ");
            
         sprintf(n, "%s%s", numbers, name);
         
         switch (nodetype)                /* Nodesize ist set on discrete value */
         {
         case TOC_NODE1:
            voutlnf("%d changeFontSize", laydat.node1size);
            break;
         case TOC_NODE2:
            voutlnf("%d changeFontSize", laydat.node2size);
            break;
         case TOC_NODE3:
            voutlnf("%d changeFontSize", laydat.node3size);
            break;
         case TOC_NODE4:
            voutlnf("%d changeFontSize", laydat.node4size);
            break;
         case TOC_NODE5:
            voutlnf("%d changeFontSize", laydat.node5size);
            break;
         case TOC_NODE6:
            voutlnf("%d changeFontSize", laydat.node6size);
         }
      }
      
      node2postscript(name, KPS_NAMEDEST);
                                          /* Changed: Fixed bug #0000040 in r6.3pl16 [NHz] */
      um_strcpy(nodename, n, 511, "make_nodetype TOKPS");
      node2postscript(nodename, KPS_NODENAME);
            
      voutlnf("/NodeName (%s %s) def", lang.chapter, nodename);

      outln("newline");
      voutlnf("/%s NameDest", name);
      
      outln("Bon");
      node2postscript(n, KPS_CONTENT);
      voutlnf("(%s) udoshow", n);
      outln("Boff");
      
      outln("newline");
      voutlnf("%d changeFontSize", laydat.propfontsize);
      break;
   
   
   case TODRC:
      set_inside_node(nodetype);
      
      outln("%%*");
      
      switch (nodetype)
      {
      case TOC_NODE1:
         if (p2_toc_counter + 1 <= p1_toc_counter && toc[p2_toc_counter + 1]->toctype == TOC_NODE2)
            voutlnf("%%%% 0, %d, 0, 0, %d, %s", p2_toc_counter+10, iDrcFlags, name);
         else
            voutlnf("%%%% 0, 0, 0, 0, %d, %s", iDrcFlags, name);
         
         break;
         
      
      case TOC_NODE2:
         if (p2_toc_counter + 1 <= p1_toc_counter && toc[p2_toc_counter + 1]->toctype == TOC_NODE3)
            voutlnf("%%%% %d, %d, 0, 0, %d, %s", last_n1_index + 10, p2_toc_counter + 100, iDrcFlags, name);
         else
            voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n1_index + 10, iDrcFlags, name);
         
         break;
         
         
      case TOC_NODE3:
         if (p2_toc_counter + 1 <= p1_toc_counter && toc[p2_toc_counter + 1]->toctype == TOC_NODE4)
            voutlnf("%%%% %d, %d, 0, 0, %d, %s", last_n2_index + 100, p2_toc_counter + 1000, iDrcFlags, name);
         else
            voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n2_index + 100, iDrcFlags, name);
         
         break;
         
         
      case TOC_NODE4:
         if (p2_toc_counter + 1 <= p1_toc_counter && toc[p2_toc_counter + 1]->toctype == TOC_NODE5)
            voutlnf("%%%% %d, %d, 0, 0, %d, %s", last_n3_index + 1000, p2_toc_counter + 100, iDrcFlags, name);
         else
            voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n3_index + 1000, iDrcFlags, name);
         
         break;
         
         
      case TOC_NODE5:
         if (p2_toc_counter + 1 <= p1_toc_counter && toc[p2_toc_counter + 1]->toctype == TOC_NODE6)
            voutlnf("%%%% %d, %d, 0, 0, %d, %s", last_n4_index + 1000, p2_toc_counter + 100, iDrcFlags, name);
         else
             voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n4_index + 10000, iDrcFlags, name);
         break;

      case TOC_NODE6:
         voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n5_index + 10000, iDrcFlags, name);

      }
      
      outln("%%*");
      outln("");
      break;
   
   
   case TOSRC:
   case TOSRP:
      set_inside_node(TOC_NODE1);         /* fd:2011-02-16: ??? why always node1 ??? */
      
      if (nodetype == TOC_NODE1)          /* additional line */
         outln("");
      
      outln("");
      
      switch (nodetype)
      {
      case TOC_NODE1:
         memset(n, '#', 62);
         n[62] = EOS;
         voutlnf("%s  %s", sSrcRemOn, n);
         outln("    #");
         outln("    #");
         voutlnf("    # %s", name);
         outln("    #");
         outln("    #");
         break;
         
      case TOC_NODE2:
         memset(n, '*', 62);
         n[62] = EOS;
         voutlnf("%s  %s", sSrcRemOn, n);
         outln("    *");
         voutlnf("    * %s", name);
         outln("    *");
         break;
         
      case TOC_NODE3:
         memset(n, '=', 62);
         n[62] = EOS;
         voutlnf("%s  %s", sSrcRemOn, n);
         voutlnf("    = %s", name);
         break;
         
      case TOC_NODE4:
      case TOC_NODE5:
      case TOC_NODE6:
         memset(n, '-', 62);
         n[62] = EOS;
         voutlnf("%s  %s", sSrcRemOn, n);
         voutlnf("    - %s", name);
      }
      
      voutlnf("    %s  %s", n, sSrcRemOff);
      outln("");
      break;
   
   
   case TORTF:
      set_inside_node(nodetype);
            
      if (nodetype == TOC_NODE1)          /* new page for new main chapter */
         if (use_style_book)
            c_newpage();
      
      outln(rtf_pardpar);
                                          /* r6pl6: Indizes fuer RTF */
      if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
      {
         strcpy(n, name);
         winspecials2ascii(n);
         voutf("{\\xe\\v %s}", n);
      }
      
      if (nodetype == TOC_NODE1)          /* fd:2011-02-16 why only in TOC_NODE1 ??? */
      {
         output_aliasses();
         
         um_strcpy(n, name, 512, "make_nodetype[RTF]");
         winspecials2ascii(n);
         node2winhelp(n);
      }
      else
      {
         um_strcpy(k, name, 512, "make_nodetype[RTF]");
         winspecials2ascii(k);
         node2winhelp(k);
      }
   
      if (use_style_book)
      {
         switch (nodetype)
         {
         case TOC_NODE1:
            if (bInsideAppendix)
            {
               if (invisible)
               {
                  voutlnf("%s\\fs%d %s %s\\par %s\\fs%d {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}\\par\\pard", 
                        rtf_inv_chapt, iDocPropfontSize + 28, lang.appendix, numbers, rtf_inv_chapt, 
                        iDocPropfontSize + 28, n, name, n);
               }
               else
               {
                  voutlnf("%s\\fs%d %s %s\\par %s\\fs%d {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}\\par\\pard", 
                        rtf_inv_chapt, iDocPropfontSize + 28, lang.appendix, numbers, rtf_chapt, 
                        iDocPropfontSize + 28, n, name, n);
               }
            }
            else
            {
               if (invisible)
               {
                  voutlnf("%s\\fs%d %s %s\\par %s\\fs%d {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}\\par\\pard", 
                        rtf_inv_chapt, iDocPropfontSize + 28, lang.chapter, numbers, rtf_inv_chapt, 
                        iDocPropfontSize + 28, n, name, n);
               }
               else
               {
                  voutlnf("%s\\fs%d %s %s\\par %s\\fs%d {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}\\par\\pard", 
                        rtf_inv_chapt, iDocPropfontSize + 28, lang.chapter, numbers, rtf_chapt, 
                        iDocPropfontSize + 28, n, name, n);
               }
            }
            
            break;
            
            
         case TOC_NODE2:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node1, iDocPropfontSize + 14);
            else
               sprintf(n, "%s\\fs%d", rtf_node1, iDocPropfontSize + 14);
               
            break;
            
         case TOC_NODE3:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node2, iDocPropfontSize + 6);
            else
               sprintf(n, "%s\\fs%d", rtf_node2, iDocPropfontSize + 6);
               
            break;
            
         case TOC_NODE4:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node3, iDocPropfontSize);
            else
               sprintf(n, "%s\\fs%d", rtf_node3, iDocPropfontSize);
               
            break;
            
         case TOC_NODE5:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node4, iDocPropfontSize);
            else
               sprintf(n, "%s\\fs%d", rtf_node4, iDocPropfontSize);

            break;

         case TOC_NODE6:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node5, iDocPropfontSize);
            else
               sprintf(n, "%s\\fs%d", rtf_node5, iDocPropfontSize);
         }
      }
      else
      {
         switch (nodetype)                /* Nodesize is set on discrete value */
         {
         case TOC_NODE1:
            if (numbers[0] == EOS)
            {
               if (invisible)
               {
                  voutlnf("%s %s\\fs%d {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", 
                        rtf_plain, rtf_inv_node1, laydat.node1size, n, name, n, rtf_parpard);
               }
               else
               {
                  voutlnf("%s %s\\fs%d {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", 
                        rtf_plain, rtf_node1, laydat.node1size, n, name, n, rtf_parpard);
               }
            }
            else
            {
               if (invisible)
               {
                  voutlnf("%s %s\\fs%d %s  {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", 
                        rtf_plain, rtf_inv_node1, laydat.node1size, numbers, n, name, n, rtf_parpard);
               }
               else
               {
                  voutlnf("%s %s\\fs%d %s  {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", 
                        rtf_plain, rtf_node1, laydat.node1size, numbers, n, name, n, rtf_parpard);
               }
            }
            
            break;
            
            
         case TOC_NODE2:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node2, laydat.node2size);
            else
               sprintf(n, "%s\\fs%d", rtf_node2, laydat.node2size);
         
            break;
            
         
         case TOC_NODE3:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node3, laydat.node3size);
            else
               sprintf(n, "%s\\fs%d", rtf_node3, laydat.node3size);
               
            break;
            
            
         case TOC_NODE4:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node4, laydat.node4size);
            else
               sprintf(n, "%s\\fs%d", rtf_node4, laydat.node4size);
               
            break;
         
         
         case TOC_NODE5:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node5, laydat.node5size);
            else
               sprintf(n, "%s\\fs%d", rtf_node5, laydat.node5size);

            break;

         case TOC_NODE6:
            if (invisible)
               sprintf(n, "%s\\fs%d", rtf_inv_node6, laydat.node6size);
            else
               sprintf(n, "%s\\fs%d", rtf_node6, laydat.node6size);
         }
      }

      if (nodetype != TOC_NODE1)
      {   
         if (numbers[0] == EOS)
            voutlnf("%s %s {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, k, name, k, rtf_parpard);
         else
            voutlnf("%s %s %s  {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, numbers, k, name, k, rtf_parpard);
      }
   
      voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);
      break;
      
   
   case TOWIN:
   case TOWH4:
   case TOAQV:
      set_inside_node(nodetype);
      
      output_win_header(name, invisible);
      output_aliasses();
      
      if (nodetype == TOC_NODE1)
      {
         if (use_style_book)
            (bInsideAppendix) ? sprintf(n, "%s %s\\par %s", lang.appendix, numbers, name) : sprintf(n, "%s %s\\par %s", lang.chapter, numbers, name);
         else
         {
            if (numbers[0] != EOS)
               strcat(numbers, "\\~\\~");
         
            sprintf(n, "%s%s", numbers, name);
         }
      }
      else
      {
         if (numbers[0] != EOS)
            strcat(numbers, "\\~\\~");
         
         sprintf(n, "%s%s", numbers, name);
      }
      
      win_headline(n, popup);
      break;
   
   
   case TOPCH:
      set_inside_node(nodetype);
      
      if (numbers[0] != EOS)
         strcat(numbers, " ");
         
      output_pch_header(numbers, name, popup);
      break;
   
   
   case TOHAH:
   case TOHTM:
   case TOMHH:
      ti = p2_toc_counter;
   
      if (!html_mergenode)
      {
         if (!html_new_file())
            return;
         
         if (!toc[ti]->ignore_title)
         {
            sprintf(hx_start, "<h%d>",  html_nodesize);
            sprintf(hx_end,   "</h%d>", html_nodesize);
         }
      }
      else
      {
         output_aliasses();
         
         if (nodetype == TOC_NODE1)
         {
            if (html_doctype < XHTML_STRICT)
               outln(HTML_HR);
            else
               outln(XHTML_HR);
         }

         if (!toc[ti]->ignore_title)
         {
            sprintf(hx_start, "<h%d>",  html_nodesize + nodetype - 1);
            sprintf(hx_end,   "</h%d>", html_nodesize + nodetype - 1);
         }
      }
   
      set_inside_node(nodetype);
      
      flag = FALSE;
   
      if (use_chapter_images)
      {
         char   closer[8] = "\0";  /* */
   
                                          /* no single tag closer in HTML! */
         if (html_doctype >= XHTML_STRICT)
            strcpy(closer, " /");
   
         ti = p2_toc_counter;
   
         if (ti >= 0 && toc[ti]->image != NULL)
         {
            sGifSize[0] = EOS;
   
            if (toc[ti]->uiImageWidth != 0 && toc[ti]->uiImageHeight != 0)
            {
               sprintf(sGifSize, " width=\"%u\" height=\"%u\"", 
                     toc[ti]->uiImageWidth, 
                     toc[ti]->uiImageHeight);
            }
   
            if (html_doctype == HTML5)
            {
               voutlnf("%s<p class=\"UDO_p_align_center\">", hx_start);
               
               voutlnf("<img src=\"%s%s\" alt=\"%s%s\" title=\"%s%s\" %s%s>",
                  toc[ti]->image, 
                  sDocImgSuffix, 
                  numbers, 
                  name, 
                  numbers, 
                  name, 
                  sGifSize, 
                  closer);
            }
            else
            {
               voutlnf("%s<p align=\"center\">", hx_start);

               voutlnf("<img src=\"%s%s\" alt=\"%s%s\" title=\"%s%s\" border=\"0\" %s%s>",
                  toc[ti]->image, 
                  sDocImgSuffix, 
                  numbers, 
                  name, 
                  numbers, 
                  name, 
                  sGifSize, 
                  closer);
            }
   
            voutlnf("</p>%s", hx_end);
            
            flag = TRUE;
         }
      }
   
      do_toptoc(nodetype, popup);
   
      if (!flag && !toc[ti]->ignore_title)
      {
         strcpy(nameNoSty, name);
         del_html_styles(nameNoSty);
   
         label2html(nameNoSty);
         
         if (html_doctype == HTML5)
         {
            voutlnf("%s<a id=\"%s\"></a>%s%s%s",
               hx_start, 
               nameNoSty, 
               numbers, 
               name, 
               hx_end);
         }
         else
         {
            voutlnf("%s<a name=\"%s\"></a>%s%s%s",
               hx_start, 
               nameNoSty, 
               numbers, 
               name, 
               hx_end);
         }
      }
      
      if (show_variable.source_filename)
      {
         voutlnf("<!-- %s: %li -->", 
               file_lookup(toc[p2_toc_counter]->source_location.id),
               toc[p2_toc_counter]->source_location.line);
      }
   
      break;
      
   
   case TOLDS:
      set_inside_node(nodetype);
      
      switch (nodetype)
      {
      case TOC_NODE1:
         (use_style_book) ? voutlnf("<chapter>%s<label id=\"%s\">", name, name) : voutlnf("<sect>%s<label id=\"%s\">", name, name);
         break;
         
      case TOC_NODE2:
         (use_style_book) ? voutlnf("<sect>%s<label id=\"%s\">", name, name) : voutlnf("<sect1>%s<label id=\"%s\">", name, name);
         break;
         
      case TOC_NODE3:
         (use_style_book) ? voutlnf("<sect1>%s<label id=\"%s\">", name, name) : voutlnf("<sect2>%s<label id=\"%s\">", name, name);
         break;
         
      case TOC_NODE4:
         (use_style_book) ? voutlnf("<sect2>%s<label id=\"%s\">", name, name) : voutlnf("<sect3>%s<label id=\"%s\">", name, name);
         break;
         
      case TOC_NODE5:
         (use_style_book) ? voutlnf("<sect3>%s<label id=\"%s\">", name, name) : voutlnf("<sect4>%s<label id=\"%s\">", name, name);
         break;

      case TOC_NODE6:
         (use_style_book) ? voutlnf("<sect4>%s<label id=\"%s\">", name, name) : voutlnf("<sect5>%s<label id=\"%s\">", name, name);

      }

      output_aliasses();
      outln("<p>");
      break;
   
   
   case TOHPH:
      set_inside_node(nodetype);
      
      switch (nodetype)
      {
      case TOC_NODE1:
         (use_style_book) ? voutlnf("<chapter>%s", name) : voutlnf("<s1>%s", name);
         break;
         
      case TOC_NODE2:
         (use_style_book) ? voutlnf("<s1>%s", name) : voutlnf("<s2>%s", name);
         break;
         
      case TOC_NODE3:
         (use_style_book) ? voutlnf("<s2>%s", name) : voutlnf("<s3>%s", name);
         break;
         
      case TOC_NODE4:
         (use_style_book) ? voutlnf("<s3>%s", name) : voutlnf("<s4>%s", name);
         break;
      
      case TOC_NODE5:
         (use_style_book) ? voutlnf("<s4>%s", name) : voutlnf("<s5>%s", name);
         break;

      case TOC_NODE6:
         (use_style_book) ? voutlnf("<s5>%s", name) : voutlnf("<s6>%s", name);
      }
      
      output_aliasses();

   }  /* switch (desttype) */

}
   




/*******************************************************************************
*
*  c_node():
*  c_node_iv():
*  c_pnode():
*  c_pnode_iv():
*     wrappers for make_nodetype()
*
*  Notes:
*     Texinfo kennt keine versteckten Kapitel, daher wird bei den 
*     node_iv-Funktionen als Invisible-Flag statt TRUE der Wert von 
*     (desttype != TOINF) benutzt. Kurz und elegant, nicht?
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_node(void)
{
   make_nodetype(TOC_NODE1, FALSE, FALSE);
}

GLOBAL void c_node_iv(void)
{
   make_nodetype(TOC_NODE1, FALSE, (desttype != TOINF));
}

GLOBAL void c_pnode(void)
{
   make_nodetype(TOC_NODE1, TRUE, FALSE);
}

GLOBAL void c_pnode_iv(void)
{
   make_nodetype(TOC_NODE1, TRUE, (desttype != TOINF));
}





/*******************************************************************************
*
*  c_subnode():
*  c_subnode_iv():
*  c_psubnode():
*  c_psubnode_iv():
*     wrappers for make_nodetype()
*
*  Notes:
*     Texinfo kennt keine versteckten Kapitel, daher wird bei den 
*     node_iv-Funktionen als Invisible-Flag statt TRUE der Wert von 
*     (desttype != TOINF) benutzt. Kurz und elegant, nicht?
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_subnode(void)
{
   make_nodetype(TOC_NODE2, FALSE, FALSE);
}

GLOBAL void c_subnode_iv(void)
{
   make_nodetype(TOC_NODE2, FALSE, (desttype != TOINF));
}

GLOBAL void c_psubnode(void)
{
   make_nodetype(TOC_NODE2, TRUE, FALSE);
}

GLOBAL void c_psubnode_iv(void)
{
   make_nodetype(TOC_NODE2, TRUE, (desttype != TOINF));
}





/*******************************************************************************
*
*  c_subsubnode():
*  c_subsubnode_iv():
*  c_psubsubnode():
*  c_psubsubnode_iv():
*     wrappers for make_nodetype()
*
*  Notes:
*     Texinfo kennt keine versteckten Kapitel, daher wird bei den 
*     node_iv-Funktionen als Invisible-Flag statt TRUE der Wert von 
*     (desttype != TOINF) benutzt. Kurz und elegant, nicht?
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_subsubnode(void)
{
   make_nodetype(TOC_NODE3, FALSE, FALSE);
}

GLOBAL void c_subsubnode_iv(void)
{
   make_nodetype(TOC_NODE3, FALSE, (desttype != TOINF));
}

GLOBAL void c_psubsubnode(void)
{
   make_nodetype(TOC_NODE3, TRUE, FALSE);
}

GLOBAL void c_psubsubnode_iv(void)
{
   make_nodetype(TOC_NODE3, TRUE, (desttype != TOINF));
}





/*******************************************************************************
*
*  c_subsubsubnode():
*  c_subsubsubnode_iv():
*  c_psubsubsubnode():
*  c_psubsubsubnode_iv():
*     wrappers for make_nodetype()
*
*  Notes:
*     Texinfo kennt keine versteckten Kapitel, daher wird bei den 
*     node_iv-Funktionen als Invisible-Flag statt TRUE der Wert von 
*     (desttype != TOINF) benutzt. Kurz und elegant, nicht?
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_subsubsubnode(void)
{
   make_nodetype(TOC_NODE4, FALSE, FALSE);
}

GLOBAL void c_subsubsubnode_iv(void)
{
   make_nodetype(TOC_NODE4, FALSE, (desttype != TOINF));
}

GLOBAL void c_psubsubsubnode(void)
{
   make_nodetype(TOC_NODE4, TRUE, FALSE);
}

GLOBAL void c_psubsubsubnode_iv(void)
{
   make_nodetype(TOC_NODE4, TRUE, (desttype != TOINF));
}





/*******************************************************************************
*
*  c_subsubsubsubnode():
*  c_subsubsubsubnode_iv():
*  c_psubsubsubsubnode():
*  c_psubsubsubsubnode_iv():
*     wrappers for make_nodetype()
*
*  Notes:
*     Texinfo kennt keine versteckten Kapitel, daher wird bei den 
*     node_iv-Funktionen als Invisible-Flag statt TRUE der Wert von 
*     (desttype != TOINF) benutzt. Kurz und elegant, nicht?
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_subsubsubsubnode(void)
{
   make_nodetype(TOC_NODE5, FALSE, FALSE);
}

GLOBAL void c_subsubsubsubnode_iv(void)
{
   make_nodetype(TOC_NODE5, FALSE, (desttype != TOINF));
}

GLOBAL void c_psubsubsubsubnode(void)
{
   make_nodetype(TOC_NODE5, TRUE, FALSE);
}

GLOBAL void c_psubsubsubsubnode_iv(void)
{
   make_nodetype(TOC_NODE5, TRUE, (desttype!=TOINF));
}





/*******************************************************************************
*
*  c_subsubsubsubsubnode():
*  c_subsubsubsubsubnode_iv():
*  c_psubsubsubsubsubnode():
*  c_psubsubsubsubsubnode_iv():
*     wrappers for make_nodetype()
*
*  Notes:
*     Texinfo kennt keine versteckten Kapitel, daher wird bei den 
*     node_iv-Funktionen als Invisible-Flag statt TRUE der Wert von 
*     (desttype != TOINF) benutzt. Kurz und elegant, nicht?
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_subsubsubsubsubnode(void)
{
   make_nodetype(TOC_NODE6, FALSE, FALSE);
}

GLOBAL void c_subsubsubsubsubnode_iv(void)
{
   make_nodetype(TOC_NODE6, FALSE, (desttype != TOINF));
}

GLOBAL void c_psubsubsubsubsubnode(void)
{
   make_nodetype(TOC_NODE6, TRUE, FALSE);
}

GLOBAL void c_psubsubsubsubsubnode_iv(void)
{
   make_nodetype(TOC_NODE6, TRUE, (desttype!=TOINF));
}





/*******************************************************************************
*
*  set_inside_node():
*     sets active_nodetype variable
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void set_inside_node(

int   nodetype)  /* TOC_NODE... */
{
   active_nodetype = nodetype;
}





/*******************************************************************************
*
*  c_endnode():
*     wrapper for check_endnode()
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_endnode(void)
{
   check_endnode();
}





/*******************************************************************************
*
*  c_begin_node():
*     ??? (description missing)
*
*  Notes:
*     r6pl5: new commands
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_node(void)
{
   check_endnode();
   
   switch (p2_toctype)
   {
   case TOC_NONE:
      c_node();
      break;
   case TOC_NODE1:
      c_subnode();
      break;
   case TOC_NODE2:
      c_subsubnode();
      break;
   case TOC_NODE3:
      c_subsubsubnode();
      break;
   case TOC_NODE4:
      c_subsubsubsubnode();
      break;
   case TOC_NODE5:
      c_subsubsubsubsubnode();
      break;
   default:
      warning_node_too_deep();
      c_subsubsubsubsubnode();
   }
}





/*******************************************************************************
*
*  c_begin_node_iv():
*     ??? (description missing)
*
*  Notes:
*     r6pl5: new commands
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_node_iv(void)
{
   check_endnode();
   
   switch (p2_toctype)
   {
   case TOC_NONE:
      c_node_iv();
      break;
   case TOC_NODE1:
      c_subnode_iv();
      break;
   case TOC_NODE2:
      c_subsubnode_iv();
      break;
   case TOC_NODE3:
      c_subsubsubnode_iv();
      break;
   case TOC_NODE4:
      c_subsubsubsubnode_iv();
      break;
   case TOC_NODE5:
      c_subsubsubsubsubnode_iv();
      break;
   default:
      warning_node_too_deep();
      c_subsubsubsubsubnode_iv();
   }
}





/*******************************************************************************
*
*  c_begin_pnode():
*     ??? (description missing)
*
*  Notes:
*     r6pl5: new commands
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_pnode(void)
{
   check_endnode();
   
   switch (p2_toctype)
   {
   case TOC_NONE:
      c_pnode();
      break;
   case TOC_NODE1:
      c_psubnode();
      break;
   case TOC_NODE2:
      c_psubsubnode();
      break;
   case TOC_NODE3:
      c_psubsubsubnode();
      break;
   case TOC_NODE4:
      c_psubsubsubsubnode();
      break;
   case TOC_NODE5:
      c_psubsubsubsubsubnode();
      break;
   default:
      warning_node_too_deep();
      c_psubsubsubsubsubnode();
   }
}





/*******************************************************************************
*
*  c_begin_pnode_iv():
*     ??? (description missing)
*
*  Notes:
*     r6pl5: new commands
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_begin_pnode_iv(void)
{
   check_endnode();
   
   switch (p2_toctype)
   {
   case TOC_NONE:
      c_pnode_iv();
      break;
   case TOC_NODE1:
      c_psubnode_iv();
      break;
   case TOC_NODE2:
      c_psubsubnode_iv();
      break;
   case TOC_NODE3:
      c_psubsubsubnode_iv();
      break;
   case TOC_NODE4:
      c_psubsubsubsubnode_iv();
      break;
   case TOC_NODE5:
      c_psubsubsubsubsubnode_iv();
      break;
   default:
      warning_node_too_deep();
      c_psubsubsubsubsubnode_iv();
   }
}





/*******************************************************************************
*
*  c_end_node():
*     ??? (description missing)
*
*  Notes:
*     r6pl5: new commands
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_end_node(void)
{
   check_endnode();

   switch (p2_toctype)
   {
   case TOC_NODE1:
      p2_toctype = TOC_NONE;
      break;
   case TOC_NODE2:
      p2_toctype = TOC_NODE1;
      break;
   case TOC_NODE3:
      p2_toctype = TOC_NODE2;
      break;
   case TOC_NODE4:
      p2_toctype = TOC_NODE3;
      break;
   case TOC_NODE5:
      p2_toctype = TOC_NODE4;
      break;
   case TOC_NODE6:
      p2_toctype = TOC_NODE5;
   }
}





/*******************************************************************************
*
*  tocline_make_bold():
*     make TOC entry line bold
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void tocline_make_bold(char *s, const int depth)
{
   char *str;
   
   if (depth > 1)
   {
      switch (desttype)
      {
      case TOHAH:
      case TOHTM:
      case TOMHH:
         str = um_strdup_printf("%s<a ", BOLD_ON);
         replace_once(s, "<a ", str);
         free(str);
         str = um_strdup_printf("</a>%s", BOLD_OFF);
         replace_last(s, "</a>", str);
         free(str);
         c_internal_styles(s);
         break;
      case TOWIN:
      case TOWH4:
      case TOAQV:
         strinsert(s, BOLD_ON);
         strcat(s, BOLD_OFF);
         c_win_styles(s);
         break;
/*    case TOKPS:
         strinsert(s, "14 changeFontSize Bon ");
         strcat(s, " Boff 11 changeFontSize changeBaseFont");
         break;
*/
      }
   }
}




/*******************************************************************************
*
*  tocline_handle_1st():
*     output start of TOC listing head if the first item is going to be output
*
*  Notes:
*     <first> flag will be reset!
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void tocline_handle_1st(_BOOL *first)
{
   if (*first)
   {
      switch (desttype)
      {
      case TOINF:
         outln("@menu");
         break;
      case TOHAH:
      case TOHTM:
      case TOMHH:
      case TOTEX:
      case TOPDL:
         outln(toc_list_top);
         break;
      }
      *first = FALSE;
   }
}





/*******************************************************************************
*
*  convert_toc_item():
*     remove all formatting stuff from a node name
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void convert_toc_item(

TOCITEM  *t)  /* */
{
   if (!t->converted)                     /* conversion should only be done once */
   {
      replace_macros(t->name);
      c_internal_styles(t->name);
      replace_udo_quotes(t->name);
      delete_all_divis(t->name);
      replace_udo_tilde(t->name);
      replace_udo_nbsp(t->name);
      
      t->converted = TRUE;                /* done! */
   }
}





/*******************************************************************************
*
*  bookmarks_ps():
*     output bookmarks for PostScript / PDF
*
*  return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL bookmarks_ps(void)
{
   /* 6.3.12 [vj] Added this define for buffer checks, increased value from 128 to 148 (for Ulrich :-)) */
   #define PS_BOOKM_LEN    148
   
   register int   i;                /* */
   int            li,               /* */
                  apxstart;         /* */
   char           s[PS_BOOKM_LEN],  /* */
                  n[PS_BOOKM_LEN];  /* */
   
   
   if (p1_toc_counter <= 0)
      return FALSE;

   apxstart = 1;

   for (i = 1; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);

         if (toc[i]->appendix)
         {
            apxstart = i;                 /* fuer unten merken */
            break;                        /* r5pl6: Es kann nur einen Anhang geben */
         }
         else
         {
            if (toc[i]->n1 != 0)
            {
               li = toc[i]->labindex;

               um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps");
               um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps");
               
               node2postscript(n, KPS_BOOKMARK);
               node2postscript(s, KPS_NAMEDEST);
                  

               switch (toc[i]->toctype)
               {
               case TOC_NODE1:            /* a node */
                  voutlnf("(%d %s) /%s %d Bookmarks",
                        toc[i]->nr1 + toc_offset,
                        n, s,
                        toc[i]->count_n2);
                  break;

               case TOC_NODE2:            /* a subnode */
                  voutlnf("(%d.%d %s) /%s %d Bookmarks",
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        n, s,
                        toc[i]->count_n3);
                  break;

               case TOC_NODE3:            /* a subsubnode */
                  voutlnf("(%d.%d.%d %s) /%s %d Bookmarks",
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        n, s,
                        toc[i]->count_n4);
                  break;

               case TOC_NODE4:            /* a subsubsubnode */
                  voutlnf("(%d.%d.%d.%d %s) /%s 0 Bookmarks",
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        n, s);
                  break;

               case TOC_NODE5:            /* a subsubsubsubnode */
                  voutlnf("(%d.%d.%d.%d.%d %s) /%s 0 Bookmarks",
                        toc[i]->nr1+toc_offset,
                        toc[i]->nr2+subtoc_offset,
                        toc[i]->nr3+subsubtoc_offset,
                        toc[i]->nr4+subsubsubtoc_offset,
                        toc[i]->nr5+subsubsubsubtoc_offset,
                        n, s);
                  break;

               case TOC_NODE6:            /* a subsubsubsubsubnode */
                  voutlnf("(%d.%d.%d.%d.%d.%d %s) /%s 0 Bookmarks",
                        toc[i]->nr1+toc_offset,
                        toc[i]->nr2+subtoc_offset,
                        toc[i]->nr3+subsubtoc_offset,
                        toc[i]->nr4+subsubsubtoc_offset,
                        toc[i]->nr5+subsubsubsubtoc_offset,
                        toc[i]->nr6+subsubsubsubsubtoc_offset,
                        n, s);

               }  /* switch (toc[i]->toctype) */

            }  /* toc[i]->n1 > 0 */

         }  /* !toc[i]->appendix */

      }  /* toc[i] != NULL && !toc[i]->invisible */

   }  /* for */


   if (!apx_available)                    /* we're done */
      return TRUE;


   /* --- appendix --- */

   for (i = apxstart; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);

         if (toc[i]->appendix)
         {
            if (toc[i]->n1 != 0)
            {
               li = toc[i]->labindex;

               um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps");
               um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps");

               node2postscript(n, KPS_BOOKMARK);
               node2postscript(s, KPS_NAMEDEST);

               switch (toc[i]->toctype)
               {
               case TOC_NODE1:            /* a node */
                  voutlnf("(%c %s) /%s %d Bookmarks",
                        'A' - 1 + toc[i]->nr1 + toc_offset,
                        n, s,
                        toc[i]->count_n2);
                  break;

               case TOC_NODE2:            /* a subnode */
                  voutlnf("(%c.%2d %s) /%s %d Bookmarks",
                        'A' - 1 + toc[i]->nr1 + toc_offset,
                                  toc[i]->nr2 + subtoc_offset,
                        n, s,
                        toc[i]->count_n3);
                  break;

               case TOC_NODE3:            /* a subsubnode */
                  voutlnf("(%c.%2d.%2d %s) /%s %d Bookmarks",
                        'A' - 1 + toc[i]->nr1 + toc_offset,
                                  toc[i]->nr2 + subtoc_offset,
                                  toc[i]->nr3 + subsubtoc_offset,
                        n, s,
                        toc[i]->count_n4);
                  break;

               case TOC_NODE4:            /* a subsubsubnode */
                  voutlnf("(%c.%2d.%2d.%2d %s) /%s 0 Bookmarks",
                        'A' - 1 + toc[i]->nr1 + toc_offset,
                                  toc[i]->nr2 + subtoc_offset,
                                  toc[i]->nr3 + subsubtoc_offset,
                                  toc[i]->nr4 + subsubsubtoc_offset,
                        n, s);
                  break;

               case TOC_NODE5:            /* a subsubsubsubnode */
                  voutlnf("(%c.%2d.%2d.%2d.%2d %s) /%s 0 Bookmarks",
                        'A' - 1 + toc[i]->nr1 + toc_offset,
                                  toc[i]->nr2 + subtoc_offset,
                                  toc[i]->nr3 + subsubtoc_offset,
                                  toc[i]->nr4 + subsubsubtoc_offset,
                                  toc[i]->nr5 + subsubsubsubtoc_offset,
                        n, s);
                  break;

               case TOC_NODE6:            /* a subsubsubsubsubnode */
                  voutlnf("(%c.%2d.%2d.%2d.%2d.%2d %s) /%s 0 Bookmarks",
                        'A' - 1 + toc[i]->nr1 + toc_offset,
                                  toc[i]->nr2 + subtoc_offset,
                                  toc[i]->nr3 + subsubtoc_offset,
                                  toc[i]->nr4 + subsubsubtoc_offset,
                                  toc[i]->nr5 + subsubsubsubtoc_offset,
                                  toc[i]->nr6 + subsubsubsubsubtoc_offset,
                        n, s);

               }  /* switch (toc[i]->toctype) */

            }  /* toc[i]->n1 > 0 */

         }  /* !toc[i]->appendix */

      }  /* toc[i] != NULL && !toc[i]->invisible */

   }  /* for */

   outln("");

   return TRUE;
}





/*******************************************************************************
*
*  toc_link_output():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void toc_link_output(

const int         depth)                /* */
{
   register int   i;                    /* */
   char          *htmlfilename,         /* */
                  hfn[512],             /* */
                  suff[12],             /* */
                  sTarget[512] = "\0";  /* */
   char           closer[8] = "\0";     /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   if (html_frames_layout)
      sprintf(sTarget, " target=\"UDOcon\"");
   
   if (p1_toc_counter <= 0)
      return;
   
   for (i = 1; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);
         
         if (toc[i]->n1 != 0)
         {
            switch (depth)
            {
            case 1:                       /* node */
               if ((toc[i]->toctype == TOC_NODE1) && !(toc[i]->appendix))
               {                          /* Ein Kapitel */     
                  sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
                  htmlfilename = hfn;
   
                  /* Feststellen, ob die Referenz im gleichen File liegt */
                  if ((html_merge_node1 == FALSE) && (strcmp(htmlfilename, outfile.name) != 0))
                  {
                     if (strchr(htmlfilename, '.') != NULL)
                        strcpy(suff, "");
                     else
                        strcpy(suff, outfile.suff);
   
                     if (no_numbers)      /* Fixed bug #0000044 [NHz] */
                     {
                        voutlnf("<link rel=\"chapter\" href=\"%s%s\"%s title=\"%s\"%s>", 
                           htmlfilename, suff, sTarget, toc[i]->name, closer);
                     }
                     else
                     {
                        voutlnf("<link rel=\"chapter\" href=\"%s%s\"%s title=\"%d %s\"%s>", 
                           htmlfilename, suff, sTarget, toc[i]->nr1+toc_offset, toc[i]->name, closer);
                     }
                  }
                  
               }  /* TOC_NODE1 */
               
               break;
   
            case 2:
               if (toc[i]->toctype == TOC_NODE2)
               {                          /* subnode */ 
               
               /* Changed in r6.2pl1 [NHz]; I'm not sure, if this makes sense, but it doesn't disturb */
                  if (   (toc[toc[i]->up_n1_index]->nr1 + toc_offset == toc[last_n1_index]->nr1 + toc_offset) 
                       &&     (toc[i]->up_n1_index == last_n1_index)
                    )
                  {
                     sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
                     htmlfilename = hfn;
                  
                     /* Feststellen, ob die Referenz im gleichen File liegt */
                     if ((html_merge_node2 == FALSE) && (strcmp(htmlfilename, outfile.name) != 0))
                     {
                        if (strchr(htmlfilename, '.') != NULL)
                           strcpy(suff, "");
                        else
                           strcpy(suff, outfile.suff);
                  
                        if (no_numbers)      /* Fixed bug #0000044 [NHz] */
                        {
                           voutlnf("<link rel=\"section\" href=\"%s%s\"%s title=\"%s\"%s>", 
                              htmlfilename, suff, sTarget, toc[i]->name, closer);
                        }
                        else
                        {
                           voutlnf("<link rel=\"section\" href=\"%s%s\"%s title=\"%d.%d %s\"%s>",
                              htmlfilename, suff, sTarget, toc[i]->nr1+toc_offset, toc[i]->nr2+subtoc_offset, 
                              toc[i]->name, closer); 
                        }
                     }
                  }
                  
               }  /* TOC_NODE2 */
               
               break;
               
            case 3:
               if (toc[i]->toctype == TOC_NODE3)
               {                          /* a subsubnode */    
               
                  /* Changed in r6.2pl1 [NHz] */
                  if (  (toc[toc[i]->up_n2_index]->nr2 + subtoc_offset == toc[last_n2_index]->nr2 + subtoc_offset)
                       &&    (toc[i]->up_n2_index == last_n2_index)
                    )
                  {
                     sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
                     htmlfilename = hfn;
                     
                     /* Feststellen, ob die Referenz im gleichen File liegt */
                     if ((html_merge_node3 == FALSE) && (strcmp(htmlfilename, outfile.name) != 0))
                     {
                        if (strchr(htmlfilename, '.') != NULL)
                           strcpy(suff, "");
                        else
                           strcpy(suff, outfile.suff);
                     
                        if (no_numbers)   /* Fixed bug #0000044 [NHz] */
                        {
                           voutlnf("<link rel=\"subsection\" href=\"%s%s\"%s title=\"%s\"%s>", 
                              htmlfilename, suff, sTarget, toc[i]->name, closer);
                        }
                        else
                        {
                        voutlnf("<link rel=\"subsection\" href=\"%s%s\"%s title=\"%d.%d.%d %s\"%s>", 
                           htmlfilename, suff, sTarget, toc[i]->nr1+toc_offset, toc[i]->nr2+subtoc_offset, 
                           toc[i]->nr3+subsubtoc_offset, toc[i]->name, closer);
                        }
                     }
                  }
                  
               }  /* TOC_NODE3 */
               
               break;
               
            case 4:
               if (toc[i]->toctype == TOC_NODE4)
               {                          /* a subsubsubnode */ 
               
                  if (  (toc[toc[i]->up_n3_index]->nr3 + subsubtoc_offset == toc[last_n3_index]->nr3 + subsubtoc_offset)
                       &&    (toc[i]->up_n3_index == last_n3_index)
                    )
                  {
                     sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
                     htmlfilename = hfn;
                     
                     /* Feststellen, ob die Referenz im gleichen File liegt */
                     if ((html_merge_node4 == FALSE) && (strcmp(htmlfilename, outfile.name) != 0))
                     {
                        if (strchr(htmlfilename, '.') != NULL)
                           strcpy(suff, "");
                        else
                           strcpy(suff, outfile.suff);
                     
                        if (no_numbers)   /* Fixed bug #0000044 [NHz] */
                        {
                           voutlnf("<link rel=\"subsection\" href=\"%s%s\"%s title=\"%s\"%s>",  /* ToDo: subsection? */
                              htmlfilename, suff, sTarget, toc[i]->name, closer);
                        }
                        else
                        {
                        voutlnf("<link rel=\"subsection\" href=\"%s%s\"%s title=\"%d.%d.%d.%d %s\"%s>", /* ToDo: subsection? */
                           htmlfilename, suff, sTarget, toc[i]->nr1+toc_offset, toc[i]->nr2+subtoc_offset, 
                           toc[i]->nr3+subsubtoc_offset, toc[i]->nr4+subsubsubtoc_offset, toc[i]->name, closer);
                        }
                     }
                  }
                  
               }  /* TOC_NODE4 */
               
               break;

               
            case 5:
               if (toc[i]->toctype == TOC_NODE5)
               {                          /* a subsubsubsubnode */ 
               
                  if (  (toc[toc[i]->up_n4_index]->nr3 + subsubtoc_offset == toc[last_n4_index]->nr4 + subsubtoc_offset)
                       &&    (toc[i]->up_n4_index == last_n4_index)
                    )
                  {
                     sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
                     htmlfilename = hfn;
                     
                     /* Feststellen, ob die Referenz im gleichen File liegt */
                     if ((html_merge_node5 == FALSE) && (strcmp(htmlfilename, outfile.name) != 0))
                     {
                        if (strchr(htmlfilename, '.') != NULL)
                           strcpy(suff, "");
                        else
                           strcpy(suff, outfile.suff);
                     
                        if (no_numbers)   /* Fixed bug #0000044 [NHz] */
                        {
                           voutlnf("<link rel=\"subsection\" href=\"%s%s\"%s title=\"%s\"%s>",  /* ToDo: subsection? */
                              htmlfilename, suff, sTarget, toc[i]->name, closer);
                        }
                        else
                        {
                        voutlnf("<link rel=\"subsection\" href=\"%s%s\"%s title=\"%d.%d.%d.%d.%d %s\"%s>", /* ToDo: subsection? */
                           htmlfilename, suff, sTarget, toc[i]->nr1+toc_offset, toc[i]->nr2+subtoc_offset, 
                           toc[i]->nr3+subsubtoc_offset, toc[i]->nr4+subsubsubtoc_offset,
                           toc[i]->nr5+subsubsubsubtoc_offset, toc[i]->name, closer);
                        }
                     }
                  }
                  
               }  /* TOC_NODE5 */
               
               break;

            case 6:
               if ((toc[i]->toctype == TOC_NODE1) && (toc[i]->appendix))
               {                          /* a subsubsubsubnode */ 
               
                  sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
                  htmlfilename = hfn;
               
                  /* Feststellen, ob die Referenz im gleichen File liegt */
                  if ((html_merge_node1 == FALSE) && (strcmp(htmlfilename, outfile.name) != 0))
                  {
                     if (strchr(htmlfilename, '.') != NULL)
                        strcpy(suff, "");
                     else
                        strcpy(suff, outfile.suff);
                  
                     if (no_numbers)      /* Fixed bug #0000044 [NHz] */
                     {
                        voutlnf("<link rel=\"appendix\" href=\"%s%s\"%s title=\"%s\"%s>", 
                           htmlfilename, suff, sTarget, toc[i]->name, closer);
                     }
                     else
                     {
                        voutlnf("<link rel=\"appendix\" href=\"%s%s\"%s title=\"%c %s\"%s>", 
                           htmlfilename, suff, sTarget, 'A'-1+toc[i]->nr1, toc[i]->name, closer);
                     }
                  }
                  
               }  /* TOC_NODE1 */

            } /* switch */
         
         } /* toc[i]->n1 > 0 */
      
      } /* toc[i]!=NULL && !toc[i]->invisible */
   
   }/* for */

}       /* toc_link_output */





/*******************************************************************************
*
*  toc_output():
*     create output for all !use_auto_...tocs commands
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void toc_output(

int               nodetype,             /* TOC_NODE... */
const int         depth,                /* TOC level depth */
_BOOL           apx)                  /* TRUE: appendix output */
{
   register int   i;                    /* */
   int            li;                   /* */
   char           n[512],               /* */
                  ref[512];             /* */
   _BOOL        leerzeile = FALSE;    /* TRUE: output an empty line */
   _BOOL        last_n = FALSE;       /* TRUE: this node is last node */
   _BOOL        last_sn = FALSE;      /* TRUE: this node is last subnode */
   _BOOL        last_ssn = FALSE;     /* TRUE: this node is last subsubnode */
   _BOOL        last_sssn = FALSE;    /* TRUE: this node is last subsubsubnode */
   _BOOL        last_ssssn = FALSE;   /* TRUE: this node is last subsubsubsubnode */
   _BOOL        last_sssssn = FALSE;  /* TRUE: this node is last subsubsubsubsubnode */
   _BOOL        first = TRUE;         /* */
   _BOOL        output_done = FALSE;  /* */
   _BOOL        old;                  /* */
   int            p2_n1 = 0,
                  p2_n2 = 0,
                  p2_n3 = 0,
                  p2_n4 = 0,
                  p2_n5 = 0;
   int            start;                /* for() loop start point */
   int            depth1 = TOC_NODE1;               /* buffers for TOC_NODE... */
   int            depth2 = TOC_NODE2;
   int            depth3 = TOC_NODE3;
   int            depth4 = TOC_NODE4;
   int            depth5 = TOC_NODE5;
   int            depth6 = TOC_NODE6;
   _BOOL        last1 = FALSE;        /* TRUE: this node is last node */
   _BOOL        last2 = FALSE;        /* TRUE: this node is last subnode */
   _BOOL        last3 = FALSE;        /* TRUE: this node is last subsubnode */
   _BOOL        last4 = FALSE;        /* TRUE: this node is last subsubsubnode */
   _BOOL        last5 = FALSE;        /* TRUE: this node is last subsubsubsubnode */
   _BOOL        last6 = FALSE;        /* TRUE: this node is last subsubsubsubsubnode */
   char          *form_x1 = form_t1_n1;
   char          *form_x2 = form_t1_n2;
   char          *form_x3 = form_t1_n3;
   char          *form_x4 = form_t1_n4;
   char          *form_x5 = form_t1_n5;
   char          *form_x6 = form_t1_n6;

   
   if (desttype == TOLYX)                 /* LYX doesn't support !toc */
      return;
   
   if (p1_toc_counter <= 0)               /* nothing to do */
      return;

   if (toc[p2_toc_counter]->ignore_subtoc)/* no subtocs */
      return;


   switch (nodetype)
   {
   case TOC_NODE1:   
      if (apx && !apx_available)
         return;

      start = 1;
      
      p2_n1 = 0;
      
      depth1 = TOC_NODE1;
      depth2 = TOC_NODE2;
      depth3 = TOC_NODE3;
      depth4 = TOC_NODE4;
      depth5 = TOC_NODE5;
      depth6 = TOC_NODE6;
      
      last1 = last_n;
      last2 = last_sn;
      last3 = last_ssn;
      last4 = last_sssn;
      last5 = last_ssssn;
      last6 = last_sssssn;
      
      if (apx)
      {
         form_x1 = form_a1_n1;
         form_x2 = form_a1_n2;
         form_x3 = form_a1_n3;
         form_x4 = form_a1_n4;
         form_x5 = form_a1_n5;
         form_x6 = form_a1_n6;
      }
      else
      {
         form_x1 = form_t1_n1;
         form_x2 = form_t1_n2;
         form_x3 = form_t1_n3;
         form_x4 = form_t1_n4;
         form_x5 = form_t1_n5;
         form_x6 = form_t1_n6;
      }
      
      break;

   
   case TOC_NODE2:
      if (apx)                            /* we're in appendix mode */
         p2_n1 = p2_apx_n1;
      else
         p2_n1 = p2_toc_n1;
      
      start = last_n1_index;

      depth1 = TOC_NODE2;
      depth2 = TOC_NODE3;
      depth3 = TOC_NODE4;
      depth4 = TOC_NODE5;
      depth5 = TOC_NODE6;
      
      last1 = last_sn;
      last2 = last_ssn;
      last3 = last_sssn;
      last4 = last_ssssn;
      last5 = last_sssssn;
      
      if (apx)
      {
         form_x1 = form_a2_n2;
         form_x2 = form_a2_n3;
         form_x3 = form_a2_n4;
         form_x4 = form_a2_n5;
         form_x5 = form_a2_n6;
      }
      else
      {
         form_x1 = form_t2_n2;
         form_x2 = form_t2_n3;
         form_x3 = form_t2_n4;
         form_x4 = form_t2_n5;
         form_x5 = form_t2_n6;
      }
      
      break;
      
   
   case TOC_NODE3:
      if (last_n2_index == 0)             /* Wer benutzt !subsubtoc in einem Node? */
         return;

      if (apx)                            /* we're in appendix mode */
      {
         p2_n1 = p2_apx_n1;
         p2_n2 = p2_apx_n2;
      }
      else
      {
         p2_n1 = p2_toc_n1;
         p2_n2 = p2_toc_n2;
      }
      
      start = last_n2_index;
      
      depth1 = TOC_NODE3;
      depth2 = TOC_NODE4;
      depth3 = TOC_NODE5;
      depth4 = TOC_NODE6;
      
      last1 = last_ssn;
      last2 = last_sssn;
      last3 = last_ssssn;
      last4 = last_sssssn;
      
      if (apx)
      {
         form_x1 = form_a3_n3;
         form_x2 = form_a3_n4;
         form_x3 = form_a3_n5;
         form_x4 = form_a3_n6;
      }
      else
      {
         form_x1 = form_t3_n3;
         form_x2 = form_t3_n4;
         form_x3 = form_t3_n5;
         form_x4 = form_t3_n6;
      }
      
      break;
      
      
   case TOC_NODE4:
      if (last_n2_index == 0)             /* Wer benutzt !subsubsubtoc in einem Node? */
         return;

      if (last_n3_index == 0)             /* Wer benutzt !subsubsubtoc in einem Subnode? */
         return;

      if (apx)                            /* we're in appendix mode */
      {
         p2_n1 = p2_apx_n1;
         p2_n2 = p2_apx_n2;
         p2_n3 = p2_apx_n3;
      }
      else
      {
         p2_n1 = p2_toc_n1;
         p2_n2 = p2_toc_n2;
         p2_n3 = p2_toc_n3;
      }
      
      start = last_n3_index;
      
      depth1 = TOC_NODE4;
      depth2 = TOC_NODE5;
      depth3 = TOC_NODE6;
      
      last1 = last_sssn;
      last2 = last_ssssn;
      last3 = last_sssssn;
      
      if (apx)
      {
         form_x1 = form_a4_n4;
         form_x2 = form_a4_n5;
         form_x3 = form_a4_n6;
      }
      else
      {
         form_x1 = form_t4_n4;
         form_x2 = form_t4_n5;
         form_x3 = form_t4_n6;
      }
      
      break;
      
      
   case TOC_NODE5:
      if (last_n2_index == 0)             /* Wer benutzt !subsubsubtoc in einem Node? */
         return;

      if (last_n3_index == 0)             /* Wer benutzt !subsubsubtoc in einem Subnode? */
         return;

      if (last_n4_index == 0)             /* Wer benutzt !subsubsubtoc in einem Subsubnode? */
         return;

      if (apx)                            /* we're in appendix mode */
      {
         p2_n1 = p2_apx_n1;
         p2_n2 = p2_apx_n2;
         p2_n3 = p2_apx_n3;
         p2_n4 = p2_apx_n4;
      }
      else
      {
         p2_n1 = p2_toc_n1;
         p2_n2 = p2_toc_n2;
         p2_n3 = p2_toc_n3;
         p2_n4 = p2_toc_n4;
      }
      
      start = last_n4_index;
      
      depth1 = TOC_NODE5;
      depth2 = TOC_NODE6;
      
      last1 = last_ssssn;
      last2 = last_sssssn;
      
      if (apx)
      {
         form_x1 = form_a5_n5;
         form_x2 = form_a5_n6;
      }
      else
      {
         form_x1 = form_t5_n5;
         form_x2 = form_t5_n6;
      }

      break;
      
   case TOC_NODE6:
      if (last_n2_index == 0)             /* Wer benutzt !subsubsubtoc in einem Node? */
         return;

      if (last_n3_index == 0)             /* Wer benutzt !subsubsubtoc in einem Subnode? */
         return;

      if (last_n4_index == 0)             /* Wer benutzt !subsubsubtoc in einem Subsubnode? */
         return;

      if (last_n5_index == 0)             /* Wer benutzt !subsubsubsubtoc in einem Subsubnode? */
         return;

      if (apx)                            /* we're in appendix mode */
      {
         p2_n1 = p2_apx_n1;
         p2_n2 = p2_apx_n2;
         p2_n3 = p2_apx_n3;
         p2_n4 = p2_apx_n4;
         p2_n5 = p2_apx_n5;
      }
      else
      {
         p2_n1 = p2_toc_n1;
         p2_n2 = p2_toc_n2;
         p2_n3 = p2_toc_n3;
         p2_n4 = p2_toc_n4;
         p2_n5 = p2_toc_n5;
      }
      
      start = last_n5_index;
      
      depth1 = TOC_NODE6;
      
      last1 = last_sssssn;
      
      if (apx)
         form_x1 = form_a6_n6;
      else
         form_x1 = form_t6_n6;
      
   }  /* switch (nodetype) */
   

   old = bDocAutorefOff;
   bDocAutorefOff = FALSE;
   
                                          /* walk through all collected nodes from pass1() */
   for (i = start; i <= p1_toc_counter; i++)
   {
                                          /* nothing to do here! */
      if (toc[i] == NULL || toc[i]->invisible)
         goto NEXT_TOC;                   /* try next TOC entry */

      convert_toc_item(toc[i]);

      if (!apx && toc[i]->appendix)       /* we're not (yet) in appendix mode */
         break;
                                      

      if (nodetype == TOC_NODE1)          /* don't use switch() here to be able and use break; */
      {
         if (apx && !toc[i]->appendix)    /* in appendix mode we skip all non-appendix TOC entries */
            goto NEXT_TOC;
      }
      else                                /* TOC_NODE2 ... TOC_NODE5: */
      {
         if (apx && toc[i]->appendix && toc[i]->n1 == 0)
            break;
                                
         if (toc[i]->n1 > p2_n1)          /* all nodes done */
            break;
      }

      if (toc[i]->n1 == 0)                /* not a valid node? */
         goto NEXT_TOC;

      if (    nodetype == TOC_NODE2       /* don't use switch() here to be able and use break; */
           || nodetype == TOC_NODE3
           || nodetype == TOC_NODE4
           || nodetype == TOC_NODE5
           || nodetype == TOC_NODE6
         )
      {
         if (toc[i]->n1 != p2_n1)
            goto NEXT_TOC;
      }


      if (    nodetype == TOC_NODE3       /* don't use switch() here to be able and use break; */
           || nodetype == TOC_NODE4
           || nodetype == TOC_NODE5
           || nodetype == TOC_NODE6
         )
      {
         if (toc[i]->n2 > p2_n2)
            break;
         
         if (toc[i]->n2 != p2_n2)
            goto NEXT_TOC;
      }
      
      if (    nodetype == TOC_NODE4       /* don't use switch() here to be able and use break; */
           || nodetype == TOC_NODE5
           || nodetype == TOC_NODE6
         )
      {
         if (toc[i]->n3 > p2_n3)
            break;
         
         if (toc[i]->n3 != p2_n3)
            goto NEXT_TOC;
      }
      
      if (    nodetype == TOC_NODE5        /* don't use switch() here to be able and use break; */
           || nodetype == TOC_NODE6
         )
      {
         if (toc[i]->n4 > p2_n4)
            break;
         
         if (toc[i]->n4 != p2_n4)
            goto NEXT_TOC;
      }

      if (nodetype == TOC_NODE6)          /* don't use switch() here to be able and use break; */
      {
         if (toc[i]->n5 > p2_n5)
            break;
         
         if (toc[i]->n5 != p2_n5)
            goto NEXT_TOC;
      }

                                          /* TOC_NODE1: current is a node */
                                          /* TOC_NODE2: current is a subnode */
                                          /* TOC_NODE3: current is a subsubnode */
                                          /* TOC_NODE4: current is a subsubsubnode */
                                          /* TOC_NODE5: current is a subsubsubsubnode */
                                          /* TOC_NODE6: current is a subsubsubsubsubnode */
      if (toc[i]->toctype == depth1)
      {
         /* --- check first if we have to close previous items --- */
         
         if (use_toc_list_commands)
         {
            if (last1)                    /* close last node item */
            {
               if (use_toc_list_commands == TOCL_HTM)
                  outln("\t</li>");
               else if (use_toc_list_commands != TOCL_TEX)
                  outln(toc_list_end);
               
               last1 = FALSE;
            }
            
            if (last2)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t</li>");
                  outln("\t\t</ul>");
                  outln("\t</li>");
               }
               else
                  outln(toc_list_end);
               
               last2 = FALSE;
            }
            
            if (last3)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t</li>");
                  outln("\t\t\t\t</ul>");
                  outln("\t\t\t</li>");
                  outln("\t\t</ul>");
                  outln("\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
               }
               
               last3 = FALSE;
            }

            if (last4)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t</li>");
                  outln("\t\t\t\t</ul>");
                  outln("\t\t\t</li>");
                  outln("\t\t</ul>");
                  outln("\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
                  outln(toc_list_end);
               }
               
               last4 = FALSE;
            }

            if (last5)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t</li>");
                  outln("\t\t\t\t</ul>");
                  outln("\t\t\t</li>");
                  outln("\t\t</ul>");
                  outln("\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
                  outln(toc_list_end);
               }
               
               last5 = FALSE;
            }

            if (last6)                    /* only for TOC_NODE1 */
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t</ul>");
                  outln("\t\t\t\t</li>");
                  outln("\t\t\t</ul>");
                  outln("\t\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
                  outln(toc_list_end);
                  outln(toc_list_end);
               }
               
               last6 = FALSE;
            }
         }
                                          /* TOC_NODE1: we're a node! */
                                          /* TOC_NODE2: we're a subnode! */
                                          /* TOC_NODE3: we're a subsubnode! */
                                          /* TOC_NODE4: we're a subsubsubnode! */
                                          /* TOC_NODE5: we're a subsubsubsubnode! */
                                          /* TOC_NODE6: we're a subsubsubsubsubnode! */
         last1 = TRUE;
         
         li = toc[i]->labindex;
         string2reference(ref, li, TRUE, "", 0, 0);
         
         if (no_numbers)
         {
            sprintf(n, form_x1, ref);
         }
         else
         {
            switch (nodetype)
            {
            case TOC_NODE1:
               if (apx)
               {
                  sprintf(n, form_x1, 
                        'A' - 1 + toc[i]->nr1, 
                        ref);
               }
               else
               {
                  sprintf(n, form_x1, 
                        toc[i]->nr1 + toc_offset, 
                        ref);
               }
               
               break;
               
               
            case TOC_NODE2:
               if (apx)
               {
                  sprintf(n, form_x1, 
                        'A' - 1 + toc[i]->nr1, 
                                  toc[i]->nr2, 
                        ref);
               }
               else
               {
                  sprintf(n, form_x1, 
                        toc[i]->nr1 + toc_offset, 
                        toc[i]->nr2 + subtoc_offset, 
                        ref);
               }
               
               break;
               
               
            case TOC_NODE3:
               if (apx)
               {
                  sprintf(n, form_x1, 
                        'A' - 1 + toc[i]->nr1, 
                                  toc[i]->nr2, 
                                  toc[i]->nr3, 
                        ref);
               }
               else
               {
                  sprintf(n, form_x1, 
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        ref);
               }
               
               break;
               
               
            case TOC_NODE4:
               if (apx)
               {
                  sprintf(n, form_x1,
                        'A' - 1 + toc[i]->nr1,
                                  toc[i]->nr2,
                                  toc[i]->nr3,
                                  toc[i]->nr4,
                        ref);
               }
               else
               {
                  sprintf(n, form_x1,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        ref);
               }
               
               break;
               
               
            case TOC_NODE5:
               if (apx)
               {
                  sprintf(n, form_x1,
                        'A' - 1 + toc[i]->nr1,
                                  toc[i]->nr2,
                                  toc[i]->nr3,
                                  toc[i]->nr4,
                                  toc[i]->nr5,
                        ref);
               }
               else
               {
                  sprintf(n, form_x1,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        ref);
               }
               
               break;

            case TOC_NODE6:
               if (apx)
               {
                  sprintf(n, form_x1,
                        'A' - 1 + toc[i]->nr1,
                                  toc[i]->nr2,
                                  toc[i]->nr3,
                                  toc[i]->nr4,
                                  toc[i]->nr5,
                                  toc[i]->nr6,
                        ref);
               }
               else
               {
                  sprintf(n, form_x1,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        toc[i]->nr6 + subsubsubsubsubtoc_offset,
                        ref);
               }
               
            }
         }
         
         switch (nodetype)
         {
         case TOC_NODE1:
            tocline_make_bold(n, depth);

                                          /* don't add blank lines when depth is 1 */
            if ( (leerzeile) && (depth > 1) )
            {
               switch (desttype)
               {
               case TOWIN:
               case TOWH4:
               case TOAQV:
                  outln(rtf_par);
                  break;
            
               case TOHAH:
               case TOHTM:
               case TOMHH:
                  outln("");
                  break;
               
               case TOTEX:
               case TOPDL:
                  break;
               
               default:
                  outln("");
               }
               
               leerzeile = FALSE;
            }
         }
         
         tocline_handle_1st(&first);

         if (use_toc_list_commands == TOCL_HTM)
            out("\t");
            
         outln(n);                        /* output the node item! */
         
         switch (nodetype)
         {
         case TOC_NODE1:
            leerzeile = TRUE;
            break;
         
         case TOC_NODE2:
         case TOC_NODE3:
         case TOC_NODE4:
         case TOC_NODE5:
         case TOC_NODE6:
            output_done = TRUE;
         }
         
      }  /* depth1 */


      if ( (toc[i]->toctype == depth2) && (depth > 1) )
      {
                                          /* TOC_NODE1: current is a subnode */
                                          /* TOC_NODE2: current is a subsubnode */
                                          /* TOC_NODE3: current is a subsubsubnode */
                                          /* TOC_NODE4: current is a subsubsubsubnode */
                                          /* TOC_NODE5: current is a subsubsubsubsubnode */
         /* --- check first if we have to close previous items --- */

         if (use_toc_list_commands)
         {
            if (last1)
            {
               if (use_toc_list_commands == TOCL_HTM)
                  out("\t\t");
               
               outln(toc_list_top);
               
               last1 = FALSE;
            }
            
            if (last2)                    /* close last subnode item */
            {
               if (use_toc_list_commands == TOCL_HTM)
                  outln("\t\t\t</li>");
               else
                  outln(toc_list_end);
               
               last2 = FALSE;
            }
            
            if (last3)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t</li>");
                  outln("\t\t\t\t</ul>");
                  outln("\t\t\t</li>");
               }
               else
                  outln(toc_list_end);
               
               last3 = FALSE;
            }
            
            if (last4)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t</li>");
                  outln("\t\t\t\t</ul>");
                  outln("\t\t\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
               }
               
               last4 = FALSE;
            }

            if (last5)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t</li>");
                  outln("\t\t\t\t</ul>");
                  outln("\t\t\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
                  outln(toc_list_end);
               }

               last5 = FALSE;
            }

            if (last6)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t</li>");
                  outln("\t\t\t\t</ul>");
                  outln("\t\t\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
                  outln(toc_list_end);
                  outln(toc_list_end);
               }

               last6 = FALSE;
            }
         }
                                          /* TOC_NODE1: we're a subnode! */
                                          /* TOC_NODE2: we're a subsubnode! */
                                          /* TOC_NODE3: we're a subsubsubnode! */
                                          /* TOC_NODE4: we're a subsubsubsubnode! */
                                          /* TOC_NODE5: we're a subsubsubsubsubnode! */
         last2 = TRUE;

         li = toc[i]->labindex;
         string2reference(ref, li, TRUE, "", 0, 0);
      
         if (no_numbers)
         {
            sprintf(n, form_x2, ref);
         }
         else
         {
            switch (nodetype)
            {
            case TOC_NODE1:
               if (apx)
               {
                  sprintf(n, form_x2, 
                        'A' - 1 + toc[i]->nr1, 
                                  toc[i]->nr2, 
                        ref);
               }
               else
               {
               sprintf(n, form_x2, 
                     toc[i]->nr1 + toc_offset,
                     toc[i]->nr2 + subtoc_offset, 
                     ref);
               }
               
               break;
               
               
            case TOC_NODE2:
               if (apx)
               {
                  sprintf(n, form_x2, 
                        'A' - 1 + toc[i]->nr1, 
                                  toc[i]->nr2, 
                                  toc[i]->nr3, 
                        ref);
               }
               else
               {
                  sprintf(n, form_x2, 
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        ref);
               }
               
               break;
               
               
            case TOC_NODE3:
               if (apx)
               {
                  sprintf(n, form_x2,
                        'A' - 1 + toc[i]->nr1,
                                  toc[i]->nr2,
                                  toc[i]->nr3,
                                  toc[i]->nr4,
                        ref);
               }
               else
               {
                  sprintf(n, form_x2,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        ref);
               }
               
               break;
               
               
            case TOC_NODE4:
               if (apx)
               {
                  sprintf(n, form_x2,
                        toc[i]->nr1,
                        toc[i]->nr2,
                        toc[i]->nr3,
                        toc[i]->nr4,
                        toc[i]->nr5,
                        ref);
               }
               else
               {
                  sprintf(n, form_x2,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        ref);
               }
               
               break;


            case TOC_NODE5:
               if (apx)
               {
                  sprintf(n, form_x2,
                        toc[i]->nr1,
                        toc[i]->nr2,
                        toc[i]->nr3,
                        toc[i]->nr4,
                        toc[i]->nr5,
                        toc[i]->nr6,
                        ref);
               }
               else
               {
                  sprintf(n, form_x2,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        toc[i]->nr6 + subsubsubsubsubtoc_offset,
                        ref);
               }
            }
         }
      
         tocline_handle_1st(&first);
      
         if (use_toc_list_commands == TOCL_HTM)
            out("\t\t\t");
            
                                          /* TOC_NODE1 : output subnode item! */
                                          /* TOC_NODE2 : output subsubnode item! */
                                          /* TOC_NODE3 : output subsubsubnode item! */
                                          /* TOC_NODE4 : output subsubsubsubnode item! */
                                          /* TOC_NODE6 : output subsubsubsubsubnode item! */
         outln(n);
         
         switch (nodetype)
         {
         case TOC_NODE2:
         case TOC_NODE3:
         case TOC_NODE4:
         case TOC_NODE5:
         case TOC_NODE6:
            output_done = TRUE;
         }
         
      }  /* depth2 */
      

      if ( (toc[i]->toctype == depth3) && (depth > 2) )
      {
                                          /* TOC_NODE1: current is a subsubnode */
                                          /* TOC_NODE2: current is a subsubsubnode */
                                          /* TOC_NODE3: current is a subsubsubsubnode */
                                          /* TOC_NODE4: current is a subsubsubsubsubnode */
         /* --- check first if we have to close previous items --- */

         if (use_toc_list_commands)
         {
            if (last1)
            {                             /* should not be reached! */
               switch (nodetype)
               {
               case TOC_NODE1:
                  voutlnf("%s%s", toc_list_top, toc_list_top);
                  break;
               
               case TOC_NODE2:
               case TOC_NODE3:
               case TOC_NODE4:
                  outln(toc_list_top);
               }
               
               last1 = FALSE;
            }
            
            if (last2)
            {
               if (use_toc_list_commands == TOCL_HTM)
                  out("\t\t\t\t");
                  
               outln(toc_list_top);
               
               last2 = FALSE;
            }
            
            if (last3)                    /* close last subsubnode item */
            {
               if (use_toc_list_commands == TOCL_HTM)
                  outln("\t\t\t\t\t</li>");
               else
                  outln(toc_list_end);
               
               last3 = FALSE;
            }
            
            if (last4)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t</li>");
               }
               else
                  outln(toc_list_end);
               
               last4 = FALSE;
            }
            
            if (last5)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
               }
               
               last5 = FALSE;
            }
            
            if (last6)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
                  outln(toc_list_end);
               }
               
               last6 = FALSE;
            }
         }
            
                                          /* TOC_NODE1: we're a subsubnode! */
                                          /* TOC_NODE2: we're a subsubsubnode! */
                                          /* TOC_NODE3: we're a subsubsubsubnode! */
                                          /* TOC_NODE4: we're a subsubsubsubsubnode! */
         last3 = TRUE;

         li = toc[i]->labindex;
         string2reference(ref, li, TRUE, "", 0, 0);
         
         if (no_numbers)
         {
            sprintf(n, form_x3, ref);
         }
         else
         {
            switch (nodetype)
            {
            case TOC_NODE1:
               if (apx)
               {
                  sprintf(n, form_x3, 
                        'A' - 1 + toc[i]->nr1, 
                                  toc[i]->nr2, 
                                  toc[i]->nr3, 
                        ref);
               }
               else
               {
                  sprintf(n, form_x3, 
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset, 
                        ref);
               }
               
               break;
               
               
            case TOC_NODE2:
               if (apx)
               {
                  sprintf(n, form_x3,
                        'A' - 1 + toc[i]->nr1,
                                  toc[i]->nr2,
                                  toc[i]->nr3,
                                  toc[i]->nr4,
                        ref);
               }
               else
               {
                  sprintf(n, form_x3,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        ref);
               }
               
               break;
               
               
            case TOC_NODE3:
               if (apx)
               {
                  sprintf(n, form_x3,
                          'A' - 1 + toc[i]->nr1,
                                    toc[i]->nr2,
                                    toc[i]->nr3,
                                    toc[i]->nr4,
                                    toc[i]->nr5,
                          ref);
               }
               else
               {
                  sprintf(n, form_x3,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        ref);
               }
               
               break;

            case TOC_NODE4:
               if (apx)
               {
                  sprintf(n, form_x3,
                          'A' - 1 + toc[i]->nr1,
                                    toc[i]->nr2,
                                    toc[i]->nr3,
                                    toc[i]->nr4,
                                    toc[i]->nr5,
                                    toc[i]->nr6,
                          ref);
               }
               else
               {
                  sprintf(n, form_x3,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        toc[i]->nr6 + subsubsubsubsubtoc_offset,
                        ref);
               }
            }
         }
         
         tocline_handle_1st(&first);
         
         if (use_toc_list_commands == TOCL_HTM)
            out("\t\t\t\t\t");
         
                                          /* TOC_NODE1: output subsubnode item! */
                                          /* TOC_NODE2: output subsubsubnode item! */
                                          /* TOC_NODE3: output subsubsubsubnode item! */
                                          /* TOC_NODE4: output subsubsubsubsubnode item! */
         outln(n);
         
         switch (nodetype)
         {
         case TOC_NODE2:
         case TOC_NODE3:
         case TOC_NODE4:
            output_done = TRUE;
         }
         
      }  /* depth3 */
      

      if ( (toc[i]->toctype == depth4) && (depth > 3) )
      {
                                          /* TOC_NODE1: current is a subsubsubnode */
                                          /* TOC_NODE2: current is a subsubsubsubnode */
                                          /* TOC_NODE3: current is a subsubsubsubsubnode */
         /* --- check first if we have to close previous items --- */
         
         if (use_toc_list_commands)
         {
            if (last1)
            {
                                          /* should not be reached! */
               switch (nodetype)
               {
               case TOC_NODE1:
                  voutlnf("%s%s%s", toc_list_top, toc_list_top, toc_list_top);
                  break;
               
               case TOC_NODE2:
               case TOC_NODE3:
               case TOC_NODE4:
               case TOC_NODE5:
               case TOC_NODE6:
                  outln(toc_list_top);
               }
                
               last1 = FALSE;
            }
            
            if (last2)
            {
                                          /* should not be reached! */
               switch (nodetype)
               {
               case TOC_NODE1:
                  voutlnf("%s%s", toc_list_top, toc_list_top);
                  break;
               
               case TOC_NODE2:
               case TOC_NODE3:
               case TOC_NODE4:
               case TOC_NODE5:
               case TOC_NODE6:
                  outln(toc_list_top);
               }
               
               last2 = FALSE;
            }
            
            if (last3)
            {
               if (use_toc_list_commands == TOCL_HTM)
                  out("\t\t\t\t\t\t");
               
               outln(toc_list_top);
               
               last3 = FALSE;
            }
            
            if (last4)                    /* close last subsubsubnode item */
            {
               if (use_toc_list_commands == TOCL_HTM)
                  outln("\t\t\t\t\t\t\t</li>");
               else
                  outln(toc_list_end);
               
               last4 = FALSE;
            }
            
            if (last5)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t\t\t</li>");
               }
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
               }
               
               last5 = FALSE;
            }

            if (last6)
            {
               if (use_toc_list_commands == TOCL_HTM)
               {
                  outln("\t\t\t\t\t\t\t\t\t\t</li>");
                  outln("\t\t\t\t\t\t\t\t</ul>");
                  outln("\t\t\t\t\t\t\t</li>");
               }
               else
                  outln(toc_list_end);
               
               last6 = FALSE;
            }
         }
         
                                          /* TOC_NODE1: we're a subsubsubnode! */
                                          /* TOC_NODE2: we're a subsubsubsubnode! */
                                          /* TOC_NODE3: we're a subsubsubsubsubnode! */
         last4 = TRUE;

         li = toc[i]->labindex;
         string2reference(ref, li, TRUE, "", 0, 0);
         
         if (no_numbers)
         {
            sprintf(n, form_x4, ref);
         }
         else
         {
            switch (nodetype)
            {
            case TOC_NODE1:
               if (apx)
               {
                  sprintf(n, form_x4,
                          'A' - 1 + toc[i]->nr1,
                                    toc[i]->nr2,
                                    toc[i]->nr3,
                                    toc[i]->nr4,
                          ref);
               }
               else
               {
                  sprintf(n, form_x4,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        ref);
               }
               
               break;
            
            
            case TOC_NODE2:
               if (apx)
               {
                  sprintf(n, form_x4,
                        'A' - 1 + toc[i]->nr1,
                                  toc[i]->nr2,
                                  toc[i]->nr3,
                                  toc[i]->nr4,
                                  toc[i]->nr5,
                        ref);
               }
               else
               {
                  sprintf(n, form_x4,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        ref);
               }
               
               break;

            case TOC_NODE3:
               if (apx)
               {
                  sprintf(n, form_x4,
                        'A' - 1 + toc[i]->nr1,
                                  toc[i]->nr2,
                                  toc[i]->nr3,
                                  toc[i]->nr4,
                                  toc[i]->nr5,
                                  toc[i]->nr6,
                        ref);
               }
               else
               {
                  sprintf(n, form_x4,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        toc[i]->nr6 + subsubsubsubsubtoc_offset,
                        ref);
               }
            }
         }
   
         tocline_handle_1st(&first);
      
         if (use_toc_list_commands == TOCL_HTM)
            out("\t\t\t\t\t\t\t");
         
         outln(n);
         
         switch (nodetype)
         {
         case TOC_NODE2:
         case TOC_NODE3:
            output_done = TRUE;
         }
   
      }  /* depth4 */


                                          /* TOC_NODE1: current is a subsubsubsubnode */
                                          /* TOC_NODE2: current is a subsubsubsubsubnode */
      if ( (toc[i]->toctype == depth5) && (depth > 4) )
      {
         /* --- check first if we have to close previous items --- */

         if (use_toc_list_commands)
         {
            if (last1)
            {
                                          /* should not be reached! */
               voutlnf("%s%s%s", toc_list_top, toc_list_top, toc_list_top);
               last1 = FALSE;
            }
               
            if (last2)
            {
                                          /* should not be reached! */
               voutlnf("%s%s", toc_list_top, toc_list_top);
               last2 = FALSE;
            }
               
            if (last3)
            {
               if (use_toc_list_commands == TOCL_HTM)
                  out("");
                  
               outln(toc_list_top);
               
               last3 = FALSE;
            }
            
            if (last4)
            {
               if (use_toc_list_commands == TOCL_HTM)
                  out("\t\t\t\t\t\t\t\t");
               
               outln(toc_list_top);
               
               last4 = FALSE;
            }

            if (last5)                    /* close last subsubsubsubnode item */
            {
               if (use_toc_list_commands == TOCL_HTM)
                  outln("\t\t\t\t\t\t\t\t\t</li>");
               else
                  outln(toc_list_end);
               
               last5 = FALSE;
            }

            if (last6)                    /* close last subsubsubsubsubnode item */
            {
               if (use_toc_list_commands == TOCL_HTM)
                  outln("\t\t\t\t\t\t\t\t\t\t</li>");
               else
                  outln(toc_list_end);
               
               last6 = FALSE;
            }
         }
      
         last5 = TRUE;                    /* we're a subsubsubsubnode! */

         li = toc[i]->labindex;
         string2reference(ref, li, TRUE, "", 0, 0);
         
         if (no_numbers)
         {
            sprintf(n, form_x5, ref);
         }
         else
         {
         
           switch (nodetype)
            {
            case TOC_NODE1:
               if (apx)
               {
                  sprintf(n, form_x5,
                          'A' - 1 + toc[i]->nr1,
                                    toc[i]->nr2,
                                    toc[i]->nr3,
                                    toc[i]->nr4,
                                    toc[i]->nr5,
                          ref);
               }
               else
               {
                  sprintf(n, form_x5,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        ref);
               }
               
               break;
            
            
            case TOC_NODE2:
               if (apx)
               {
                  sprintf(n, form_x5,
                        'A' - 1 + toc[i]->nr1,
                                  toc[i]->nr2,
                                  toc[i]->nr3,
                                  toc[i]->nr4,
                                  toc[i]->nr5,
                                  toc[i]->nr6,
                        ref);
               }
               else
               {
                  sprintf(n, form_x5,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        toc[i]->nr6 + subsubsubsubsubtoc_offset,
                        ref);
               }
            }
         
         }
   
         tocline_handle_1st(&first);
      
         if (use_toc_list_commands == TOCL_HTM)
            out("\t\t\t\t\t\t\t\t\t");
         
         outln(n);                        /* output subsubsubsubnode item! */
   
         switch (nodetype)
         {
         case TOC_NODE2:
            output_done = TRUE;
         }

      }  /* depth5 */


                                          /* TOC_NODE1: current is a subsubsubsubsubnode */
      if ( (toc[i]->toctype == depth6) && (depth > 5) )
      {
         /* --- check first if we have to close previous items --- */

         if (use_toc_list_commands)
         {
            if (last1)
            {
                                          /* should not be reached! */
               voutlnf("%s%s%s", toc_list_top, toc_list_top, toc_list_top);
               last1 = FALSE;
            }
               
            if (last2)
            {
                                          /* should not be reached! */
               voutlnf("%s%s", toc_list_top, toc_list_top);
               last2 = FALSE;
            }
               
            if (last3)
            {
               if (use_toc_list_commands == TOCL_HTM)
                  out("");
                  
               outln(toc_list_top);
               
               last3 = FALSE;
            }
            
            if (last4)
            {
               if (use_toc_list_commands == TOCL_HTM)
                  out("\t\t\t\t\t\t\t\t");
               
               outln(toc_list_top);
               
               last4 = FALSE;
            }

            if (last5)                    /* close last subsubsubsubnode item */
            {
               if (use_toc_list_commands == TOCL_HTM)
                  outln("\t\t\t\t\t\t\t\t\t</li>");
               else
               {
                  outln(toc_list_end);
                  outln(toc_list_end);
               }
               
               last5 = FALSE;
            }

            if (last6)                    /* close last subsubsubsubsubnode item */
            {
               if (use_toc_list_commands == TOCL_HTM)
                  outln("\t\t\t\t\t\t\t\t\t\t</li>");
               else
                  outln(toc_list_end);
               
               last6 = FALSE;
            }
         }
      
         last6 = TRUE;                    /* we're a subsubsubsubsubnode! */

         li = toc[i]->labindex;
         string2reference(ref, li, TRUE, "", 0, 0);
         
         if (no_numbers)
         {
            sprintf(n, form_x6, ref);
         }
         else
         {
            if (apx)
            {
               sprintf(n, form_x6,
                       'A' - 1 + toc[i]->nr1,
                                 toc[i]->nr2,
                                 toc[i]->nr3,
                                 toc[i]->nr4,
                                 toc[i]->nr5,
                                 toc[i]->nr6,
                       ref);
            }
            else
            {
               sprintf(n, form_x6,
                     toc[i]->nr1 + toc_offset,
                     toc[i]->nr2 + subtoc_offset,
                     toc[i]->nr3 + subsubtoc_offset,
                     toc[i]->nr4 + subsubsubtoc_offset,
                     toc[i]->nr5 + subsubsubsubtoc_offset,
                     toc[i]->nr6 + subsubsubsubsubtoc_offset,
                     ref);
            }
         }
   
         tocline_handle_1st(&first);
      
         if (use_toc_list_commands == TOCL_HTM)
            out("\t\t\t\t\t\t\t\t\t\t");
         
         outln(n);                        /* output subsubsubsubsubnode item! */
   
      }  /* depth6 */

NEXT_TOC:
      ;
   }  /* for */
   
   
   /* --- close TOC listing --- */
   
   switch (nodetype)
   {
   case TOC_NODE2:
   case TOC_NODE3:
   case TOC_NODE4:
   case TOC_NODE5:
   case TOC_NODE6:
      if (!output_done)
         goto DONE;
   }
   

   switch (desttype)
   {
   case TOHAH:
   case TOHTM:
   case TOMHH:
      if (last6)
      {
         outln("\t\t\t\t\t\t\t\t\t\t</li>");
         outln("\t\t\t\t\t\t\t\t\t</li>");
         outln("\t\t\t\t\t\t\t\t</ul>");
         outln("\t\t\t\t\t\t\t</li>");
         outln("\t\t\t\t\t\t</ul>");
         outln("\t\t\t\t\t</li>");
         outln("\t\t\t\t</ul>");
         outln("\t\t\t</li>");
         outln("\t\t</ul>");
      }
      if (last5)
      {
         outln("\t\t\t\t\t\t\t\t\t</li>");
         outln("\t\t\t\t\t\t\t\t</ul>");
         outln("\t\t\t\t\t\t\t</li>");
         outln("\t\t\t\t\t\t</ul>");
         outln("\t\t\t\t\t</li>");
         outln("\t\t\t\t</ul>");
         outln("\t\t\t</li>");
         outln("\t\t</ul>");
      }
         
      if (last4)
      {
         outln("\t\t\t\t\t\t\t</li>");
         outln("\t\t\t\t\t\t</ul>");
         outln("\t\t\t\t\t</li>");
         outln("\t\t\t\t</ul>");
         outln("\t\t\t</li>");
         outln("\t\t</ul>");
      }
         
      if (last3)
      {
         outln("\t\t\t\t\t</li>");
         outln("\t\t\t\t</ul>");
         outln("\t\t\t</li>");
         outln("\t\t</ul>");
      }
         
      if (last2)
      {
         outln("\t\t\t</li>");
         outln("\t\t</ul>");
      }

      outln("\t</li>");
      outln("</ul>\n");
      
      break;
      
      
   case TOTEX:
   case TOPDL:
      if (last6)
         voutlnf("%s%s%s%s%s", toc_list_end, toc_list_end, toc_list_end, toc_list_end, toc_list_end);

      if (last5)
         voutlnf("%s%s%s%s", toc_list_end, toc_list_end, toc_list_end, toc_list_end);
      
      if (last4)
         voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
      
      if (last3)
         voutlnf("%s%s", toc_list_end, toc_list_end);
      
      if (last2)
         outln(toc_list_end);
      
      outln(toc_list_end);
      
      break;
      
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
      switch (nodetype)
      {
      case TOC_NODE1:
         outln("\\par ");
         break;
      
      case TOC_NODE2:
      case TOC_NODE3:
      case TOC_NODE4:
      case TOC_NODE5:
      case TOC_NODE6:
         outln(rtf_par);
         outln(rtf_pard);
      }
      
      break;
      
      
   case TOINF:
      switch (nodetype)
      {
      case TOC_NODE1:
         if (!apx_available && !no_index && bCalledIndex && use_udo_index)
         {
            outln("");
            voutlnf("* %s::", lang.index);
         }
      }
      
      outln("@end menu");
      break;
      
      
   case TOSTG:
   case TOAMG:
      switch (nodetype)
      {
      case TOC_NODE1:
         if (!apx_available)
            outln("");
      }
      outln("");
      break;
      
   default:
      outln("");
      break;
   }

DONE:   
   bDocAutorefOff = old;

}  /* toc_output */





/*******************************************************************************
*
*  do_toc():
*     wrapper for toc_output()
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void do_toc(

int         nodetype,  /* TOC_NODE... */
const int   depth)     /* */
{
   if (desttype == TORTF)                 /* no TOC in RTF as we have no page numbers! */
      return;

   switch (nodetype)
   {
   case TOC_NODE1:
      toc_output(nodetype, depth, FALSE);

      if (apx_available)
      {
         output_appendix_line();
         toc_output(nodetype, depth, TRUE);
      }
      
      break;
      
      
   default:
      toc_output(nodetype, depth, bInsideAppendix);
   }
}





/*******************************************************************************
*
*  do_toptoc():
*     outputs the breadcrumb navigation links for the current chapter
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void do_toptoc(const int currdepth, _BOOL popup)
{
   char      s[512],
             sIndent[512],
             sTarget[64],
             *sFile;
   const char *sSmartSep = "&gt;";  /* default separator string */
   char border[20];
   
   if (html_navigation_separator[0] != 0) /* check if valid userdef separator exists */
   {
      sSmartSep = html_navigation_separator;
   }
   
   if (!use_auto_toptocs)
      return;
   
   if (html_merge_node1)
      return;
   
   if (html_merge_node2 && currdepth >= TOC_NODE2)
      return;
   
   if (html_merge_node3 && currdepth >= TOC_NODE3)
      return;
   
   if (html_merge_node4 && currdepth >= TOC_NODE4)
      return;

   if (html_merge_node5 && currdepth >= TOC_NODE5)
      return;
   
   if (html_merge_node6 && currdepth >= TOC_NODE6)
      return;
   
   switch (desttype)
   {
   case TOHAH:
   case TOHTM:
   case TOMHH:
  	 strcpy(border, " border=\"0\"");
#if 0
   if (html_doctype == HTML5)
      border[0] = EOS;
#endif

      if (no_images || no_auto_toptocs_icons)
      {
         strcpy(sIndent, "&nbsp;");
      }
      else
      {
         sprintf(sIndent, "<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>",
            GIF_FS_NAME, uiGifFsWidth, uiGifFsHeight, border, xhtml_closer);
      }

      if (html_frames_layout)
      {
         sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
         sFile = um_strdup_printf("%s%s%s", html_name_prefix, FRAME_FILE_CON, outfile.suff);
      }
      else
      {
         sTarget[0] = EOS;
         sFile = um_strdup_printf("%s%s", old_outfile.name, old_outfile.suff);
      }
   
      /* --- Level 1 --- */
      
      if (currdepth >= TOC_NODE1)
      {
         if (titdat.htmltitle != NULL)
         {
            strcpy(s, titdat.htmltitle);
         }
         else
         {
            strcpy(s, titleprogram);
         }
   
         if (no_images)
         {
            if (html_doctype == HTML5)
            {
               voutlnf("<span class=\"UDO_span_tt\">+&nbsp;</span>&nbsp;<a href=\"%s\"%s>%s</a>", 
                  sFile, sTarget, s);
            }
            else
            {
               voutlnf("<tt>+&nbsp;</tt>&nbsp;<a href=\"%s\"%s>%s</a>", 
                  sFile, sTarget, s);
            }
         }
         else if (html_navigation_line)
         {
                                          /* open CSS class div */
            outln("<div class=\"UDO_nav_line\">");
            
            if (html_navigation_image)
            {
                                          /* if userdef image exists */ 
               if (html_navigation_image_fspec[0] != 0)
               {
                     /* don't close the nav line already! */
                     voutf("<img src=\"%s\" alt=\"\" title=\"\"%s%s>&nbsp;&nbsp;<a href=\"%s\"%s>%s</a>",
                                         /* folder image file name */
                        html_navigation_image_fspec,
                        border,
                        xhtml_closer,    /* XHTML single tag closer (if any) */
                        sFile,           /* file name */
                        sTarget,         /* a href target */
                        s);              /* node name */
               }
               else
               {
                     /* don't close the nav line already! */
                     voutf("<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;&nbsp;<a href=\"%s\"%s>%s</a>",
                        GIF_FO_NAME,     /* folder image file name */
                        uiGifFoWidth,    /* folder image width */
                        uiGifFoHeight,   /* folder image height */
                        border,
                        xhtml_closer,    /* XHTML single tag closer (if any) */
                        sFile,           /* file name */
                        sTarget,         /* a href target */
                        s);              /* node name */
               }
            }
            else
            {
               voutf("<a href=\"%s\"%s>%s</a>",
                     sFile,               /* file name */
                     sTarget,             /* a href target */
                     s);                  /* node name */
            }
         }
         else
         {
               voutlnf("<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;<a href=\"%s\"%s>%s</a>",
                  GIF_FO_NAME, uiGifFoWidth, uiGifFoHeight, border, xhtml_closer, sFile, sTarget, s);
         }
      }
   
   
      /* --- Level 2 --- */
      
      if (currdepth >= TOC_NODE2 && last_n1_index > 0)
      {
         strcpy(s, toc[last_n1_index]->name);
         auto_references(s, TRUE, "", 0, 0);
   
         if (no_images)
         {
            if (html_doctype == HTML5)
            {
               voutlnf("<br%s><span class=\"UDO_span_tt\">|--+&nbsp;</span>&nbsp;%s", 
                  xhtml_closer, s);
            }
            else
            {
               voutlnf("<br%s><tt>|--+&nbsp;</tt>&nbsp;%s", 
                  xhtml_closer, s);
            }
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
            voutf("%s%s", sSmartSep, s);  /* don't close the nav line already! */
         }
         else
         {
               voutf("<br%s>", xhtml_closer);
               voutlnf("%s<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;%s", 
                  sIndent, 
                  GIF_FO_NAME, 
                  uiGifFoWidth, 
                  uiGifFoHeight,
                  border,
                  xhtml_closer, 
                  s);
         }
      }
   
   
      /* --- Level 3 --- */
      
      if (currdepth >= TOC_NODE3 && last_n2_index > 0)
      {
         strcpy(s, toc[last_n2_index]->name);
         auto_references(s, TRUE, "", 0, 0);
   
         if (no_images)
         {
            if (html_doctype == HTML5)
            {
               voutlnf("<br%s><span class=\"UDO_span_tt\">&nbsp;&nbsp;&nbsp;|--+&nbsp;</span>&nbsp;%s", 
                  xhtml_closer, s);
            }
            else
            {
               voutlnf("<br%s><tt>&nbsp;&nbsp;&nbsp;|--+&nbsp;</tt>&nbsp;%s", 
                  xhtml_closer, s);
            }
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
            voutf("%s%s", sSmartSep, s);  /* don't close the nav line already! */
         }
         else
         {
            voutf("<br%s>", xhtml_closer);
               voutlnf("%s%s<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;%s",
                  sIndent, 
                  sIndent, 
                  GIF_FO_NAME, 
                  uiGifFoWidth, 
                  uiGifFoHeight,
                  border,
                  xhtml_closer,
                  s);
         }
      }
   
   
      /* --- Level 4 --- */
      
      if (currdepth >= TOC_NODE4 && last_n3_index > 0)
      {
         strcpy(s, toc[last_n3_index]->name);
         auto_references(s, TRUE, "", 0, 0);
   
         if (no_images)
         {
            if (html_doctype == HTML5)
            {
               voutlnf("<br%s><span class=\"UDO_span_tt\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|--+&nbsp;</span>&nbsp;%s",
                  xhtml_closer, s);
            }
            else
            {
               voutlnf("<br%s><tt>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|--+&nbsp;</tt>&nbsp;%s",
                  xhtml_closer, s);
            }
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
            voutf("%s%s", sSmartSep, s);  /* don't close the nav line already! */
         }
         else
         {
                   voutf("<br%s>", xhtml_closer);
               voutlnf("%s%s%s<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;%s",
                  sIndent, 
                  sIndent, 
                  sIndent, 
                  GIF_FO_NAME, 
                  uiGifFoWidth, 
                  uiGifFoHeight,
                  border,
                  xhtml_closer,
                  s);
         }
      }
      

      /* --- Level 5 --- */
      
      if (currdepth >= TOC_NODE5 && last_n4_index > 0)
      {
         strcpy(s, toc[last_n4_index]->name);
         auto_references(s, TRUE, "", 0, 0);
   
         if (no_images)
         {
            if (html_doctype == HTML5)
            {
               voutlnf("<br%s><span class=\"UDO_span_tt\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|--+&nbsp;</span>&nbsp;%s",
                  xhtml_closer, s);
            }
            else
            {
               voutlnf("<br%s><tt>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|--+&nbsp;</tt>&nbsp;%s",
                  xhtml_closer, s);
            }
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
            voutf("%s%s", sSmartSep, s);  /* don't close the nav line already! */
         }
         else
         {
                   voutf("<br%s>", xhtml_closer);
               voutlnf("%s%s%s<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;%s",
                  sIndent, 
                  sIndent, 
                  sIndent, 
                  GIF_FO_NAME, 
                  uiGifFoWidth, 
                  uiGifFoHeight,
                  border,
                  xhtml_closer,
                  s);
         }
      }
      
      /* --- Level 6 --- */
      
      if (currdepth >= TOC_NODE6 && last_n5_index > 0)
      {
         strcpy(s, toc[last_n5_index]->name);
         auto_references(s, TRUE, "", 0, 0);
   
         if (no_images)
         {
            if (html_doctype == HTML5)
            {
               voutlnf("<br%s><span class=\"UDO_span_tt\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|--+&nbsp;</span>&nbsp;%s",
                  xhtml_closer, s);
            }
            else
            {
               voutlnf("<br%s><tt>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|--+&nbsp;</tt>&nbsp;%s",
                  xhtml_closer, s);
            }
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
            voutf("%s%s", sSmartSep, s);  /* don't close the nav line already! */
         }
         else
         {
                   voutf("<br%s>", xhtml_closer);
               voutlnf("%s%s%s<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\"%s%s>&nbsp;%s",
                  sIndent, 
                  sIndent, 
                  sIndent, 
                  GIF_FO_NAME, 
                  uiGifFoWidth, 
                  uiGifFoHeight,
                  border,
                  xhtml_closer,
                  s);
         }
      }
      free(sFile);

      if (html_navigation_line)
      {
                                          /* create link to Index page */
         voutlnf("\n <span class=\"UDO_nav_index\"><a href=\"indexudo.htm\">%s</a></span>", lang.index);
                                          /* close CSS class div */
         outln("</div> <!-- UDO_nav_line -->\n");
      }

      outln(xhtml_hr);
      outln("");
      break;
   
   case TOWIN:
   case TOWH4:
   case TOAQV:
     if (popup)
        return;
      if (currdepth == TOC_NODE1)
      {
         /* Hier muesste ein Verweis auf den ersten Node hin */
         /* Dies koennte das Inhaltsverzeichnis, die */
         /* Titelseite oder ein sonstiger erster Node sein!? */
         return;
      }
      
      if (currdepth >= TOC_NODE2 && last_n1_index > 0)
      {
         strcpy(s, toc[last_n1_index]->name);
         auto_references(s, TRUE, "", 0, 0);
         voutlnf("\\{bmc %s\\} %s", BMP_FO_NAME, s);
      }
      
      if (currdepth >= TOC_NODE3 && last_n2_index > 0)
      {
         strcpy(s, toc[last_n2_index]->name);
         auto_references(s, TRUE, "", 0, 0);
         voutlnf("\\par\\li400\\{bmc %s\\} %s", BMP_FO_NAME, s);
      }
      
      if (currdepth >= TOC_NODE4 && last_n3_index > 0)
      {
         strcpy(s, toc[last_n3_index]->name);
         auto_references(s, TRUE, "", 0, 0);
         voutlnf("\\par\\li800\\{bmc %s\\} %s", BMP_FO_NAME, s);
      }

      if (currdepth >= TOC_NODE5 && last_n4_index > 0)
      {
         strcpy(s, toc[last_n4_index]->name);
         auto_references(s, TRUE, "", 0, 0);
         voutlnf("\\par\\li1200\\{bmc %s\\} %s", BMP_FO_NAME, s);
      }
      
      if (currdepth >= TOC_NODE6 && last_n5_index > 0)
      {
         strcpy(s, toc[last_n5_index]->name);
         auto_references(s, TRUE, "", 0, 0);
         voutlnf("\\par\\li1600\\{bmc %s\\} %s", BMP_FO_NAME, s);
      }

      outln("\\par\\par");
      break;
   
   case TOSTG:
   case TOAMG:
     if (popup)
        return;
      if (currdepth >= TOC_NODE1 && uses_tableofcontents)
      {
         if (!no_images && !no_auto_toptocs_icons)
         {
            voutlnf("@image %s 1", IMG_FO_NAME);
         }
         
         voutlnf("   %s", lang.contents);
      }

      if (currdepth >= TOC_NODE2 && last_n1_index > 0)
      {
         if (!no_images && !no_auto_toptocs_icons)
         {
            voutlnf("@image %s 4", IMG_FO_NAME);
         }
         
         voutlnf("      %s", toc[last_n1_index]->name);
      }
      
      if (currdepth >= TOC_NODE3 && last_n2_index > 0)
      {
         if (!no_images && !no_auto_toptocs_icons)
         {
            voutlnf("@image %s 7", IMG_FO_NAME);
         }
         
         voutlnf("         %s", toc[last_n2_index]->name);
      }
      
      if (currdepth >= TOC_NODE4 && last_n3_index > 0)
      {
         if (!no_images && !no_auto_toptocs_icons)
         {
            voutlnf("@image %s 10", IMG_FO_NAME);
         }
         
         voutlnf("            %s", toc[last_n3_index]->name);
      }

      if (currdepth >= TOC_NODE5 && last_n4_index > 0)
      {
         if (!no_images && !no_auto_toptocs_icons)
         {
            voutlnf("@image %s 13", IMG_FO_NAME);
         }
         
         voutlnf("            %s", toc[last_n4_index]->name);
      }

      if (currdepth >= TOC_NODE6 && last_n5_index > 0)
      {
         if (!no_images && !no_auto_toptocs_icons)
         {
            voutlnf("@image %s 13", IMG_FO_NAME);
         }
         
         voutlnf("            %s", toc[last_n5_index]->name);
      }

      outln("");
      break;
   
   case TOPCH:
      if (currdepth >= TOC_NODE1 && (uses_tableofcontents || uses_maketitle))
      {
         voutlnf("\001 \\#%s\\#", lang.contents);
      }
      
      if (currdepth >= TOC_NODE2 && last_n1_index > 0)
      {
         voutlnf("    \001 \\#%s\\#", toc[last_n1_index]->name);
      }
      
      if (currdepth >= TOC_NODE3 && last_n2_index > 0)
      {
         voutlnf("        \001 \\#%s\\#", toc[last_n2_index]->name);
      }
      
      if (currdepth >= TOC_NODE4 && last_n3_index > 0)
      {
         voutlnf("            \001 \\#%s\\#", toc[last_n3_index]->name);
      }
      
      if (currdepth >= TOC_NODE5 && last_n4_index > 0)
      {
         voutlnf("                \001 \\#%s\\#", toc[last_n4_index]->name);
      }

      if (currdepth >= TOC_NODE6 && last_n5_index > 0)
      {
         voutlnf("                \001 \\#%s\\#", toc[last_n5_index]->name);
      }

      output_ascii_line("-", zDocParwidth);
      
   }  /* switch (desttype) */

}





/*******************************************************************************
*
*  get_toccmd_depth():
*     get the user-defined TOC depth, set by the !depth command
*
*  Return:
*     TOC depth #
*
******************************************|************************************/

LOCAL int get_toccmd_depth(void)
{
   register int   i;    /* */
   int            ret;  /* */
   

   for (i = 1; i < token_counter; i++)
   {
      if (strcmp(token[i], "!depth") == 0)
      {
         if (i + 1 < token_counter)
         { 
            ret = atoi(token[i + 1]);
            
            if (ret <= 0)
               ret = 9;

            if (ret > 9)
               ret = 9;

            return ret;
         }
      }
   }

   return 0;                              /* bei 0 werden die Defaultwerte (z.B. subtocs1_depth) benutzt */
}





/*******************************************************************************
*
*  c_toc():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_toc(void)
{
   _BOOL   flag = FALSE;  /* */
   int       d;             /* */
   
   
   if (is_for_desttype(&flag, "!toc"))
   {
      d = get_toccmd_depth();
      
      if (d == 0)
      {
         if (use_compressed_tocs)
            d = 1;
         else
            d = subtocs1_depth;
      }

      if (desttype == TOINF)
         d = 1;

      do_toc(TOC_NODE1, d);
   }
}





/*******************************************************************************
*
*  c_subtoc():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_subtoc(void)
{
   _BOOL   flag = FALSE;  /* */
   int       d;             /* */

                                          /* token[0] enthaelt das !sub*toc-Kommando */
   if (is_for_desttype(&flag, token[0]))
   {
      switch (active_nodetype)
      {
      case TOC_NODE1:
         d = get_toccmd_depth();

         if (d == 0)
            d = subtocs2_depth;

         do_toc(TOC_NODE2, d);
         break;
         
      case TOC_NODE2:
         d = get_toccmd_depth();
         
         if (d == 0)
            d = subtocs3_depth;

         do_toc(TOC_NODE3, d);
         break;
         
      case TOC_NODE3:
         d = get_toccmd_depth();

         if (d == 0)
            d = subtocs4_depth;

         do_toc(TOC_NODE4, d);
         break;

      case TOC_NODE4:
         d = get_toccmd_depth();

         if (d == 0)
            d = subtocs5_depth;

         do_toc(TOC_NODE5, d);
         break;

      case TOC_NODE5:
         do_toc(TOC_NODE6, 1);
      }
   }
}





/*******************************************************************************
*
*  c_listoffigures():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_listoffigures(void)
{
   check_endnode();

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\listoffigures");
      break;
      
   case TOLDS:
      outln("<lof>");
      break;
      
   case TOLYX:
      outln("\\layout Standard");
      outln("\\begin_inset LatexDel \\listoffigures");
      outln("\\end_inset");
      break;
      
   case TORTF:
      voutlnf("\\page\n%s\\fs36 %s\\par\\par", rtf_node1, lang.listfigure);
      voutlnf("{\\field\\fldedit{\\*\\fldinst { TOC \\\\c \"%s\" }}{\\fldrslt %s not actual}}", lang.listfigure, lang.listfigure);
   }
}





/*******************************************************************************
*
*  c_listoftables():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_listoftables(void)
{
   check_endnode();

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      outln("\\listoftables");
      break;
      
   case TOLDS:
      outln("<lot>");
      break;
      
   case TOLYX:
      outln("\\layout Standard");
      outln("\\begin_inset LatexDel \\listoftables");
      outln("\\end_inset");
      break;
      
   case TORTF:
      voutlnf("\\page\n%s\\fs36 %s\\par\\par", rtf_node1, lang.listtable);
      voutlnf("{\\field\\fldedit{\\*\\fldinst {TOC \\\\c \"Tabelle\" }}{\\fldrslt %s not actual}}", lang.listtable);
   }
}





/*******************************************************************************
*
*  output_appendix_line():
*     output the Appendix title line
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void output_appendix_line(void)
{
   switch (desttype)
   {
   case TOINF:
      outln("@sp 2");
      outln(lang.appendix);
      outln("@sp 1");
      break;
      
   case TOSTG:
      outln("");
      voutlnf("@{U}%s@{0}", lang.appendix);
      outln("");
      break;
      
   case TOAMG:
      outln("");
      voutlnf("@{U}%s@{UU}", lang.appendix);
      outln("");
      break;
      
   case TOTVH:
      outln("");
      out("  ");
      outln(lang.appendix);
      out("  ");
      output_ascii_line("=", strlen(lang.appendix));
      outln("");
      break;

   case TOASC:
   case TOPCH:
      outln("");
      outln(lang.appendix);
      output_ascii_line("=", strlen(lang.appendix));
      outln("");
      break;
      
   case TODRC:     /* <???> */
      break;
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
      voutlnf("{\\b %s}\\par\\pard\\par", lang.appendix);
      break;
      
   case TOHAH:
   case TOHTM:
   case TOMHH:
      voutlnf("<h1>%s</h1>", lang.appendix);
      break;
      
   case TOTEX:     /* <???> */
   case TOPDL:     /* <???> */
      break;
}

}





/*******************************************************************************
*
*  c_tableofcontents():
*     outputs an auto-generated Table Of Contents
*
*  Return:
*     -
*
******************************************|************************************/

void stg_out_endnode(void)
{
	if (stg_need_endnode)
	{
      outln("@endnode");
      outln("");
      outln("");
      stg_need_endnode = FALSE;
	}
}


GLOBAL void c_tableofcontents(void)
{
   char   name[256];
   char *n;
   int    i;
   int    depth;

   if (called_tableofcontents)
      return;

   called_tableofcontents = TRUE;

   check_endnode();

   depth = get_toccmd_depth();
   if (depth == 0)
   {
      if (use_compressed_tocs)
         depth = 1;
      else
         depth = 9;
   }

   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      c_newpage();
      output_helpid(0);
      outln("\\tableofcontents");
      c_newpage();
      break;
      
   case TOLYX:
      outln("\\layout LaTeX");
      outln("\\pagebreak_top \\pagebreak_bottom");
      outln("\\begin_inset LatexCommand \\tableofcontents");
      outln("\\end_inset");
      break;
      
   case TOINF:
      outln("@ifinfo");
      n = NULL;
      if (toc[1] != NULL)
      {
         strcpy(name, toc[1]->name);
         node2texinfo(name);
         n = um_strdup_printf("@node Top, %s, (dir), (dir)", name);
      }
      output_helpid(0);
      outln(n);
      free(n);

      if (called_maketitle)
      {
         if (titdat.title != NULL)
            voutlnf("@center %s @*", titdat.title);
         if (titdat.program != NULL)
            voutlnf("@center %s @*", titdat.program);
         if (titdat.version != NULL)
            voutlnf("@center %s @*", titdat.version);
         if (titdat.date != NULL)
            voutlnf("@center %s @*", titdat.date);
         if (titdat.author != NULL)
         {
            outln("@sp 1");
            voutlnf("@center %s", lang.by);
            outln("@sp 1");
            voutlnf("@center %s @*", titdat.author);
         }
         if (address_counter > 0)
         {
            for (i = 1; i <= address_counter; i++)
            {
               if (titdat.address[i] != NULL)
               {
                  voutlnf("@center %s @*", titdat.address[i]);
               }
            }
         }
         outln("@center ");
         outln("@sp 1");
      }

      outln(lang.contents);
      outln("");

      if (toc_available)
      {
         toc_output(TOC_NODE1, 1,FALSE);  /* depth always 1 */
      }

      if (apx_available)
      {
         output_appendix_line();
         toc_output(TOC_NODE1, 1,TRUE);   /* depth always 1 */
      }

      outln("@end ifinfo");
      break;

   case TOSTG:
   case TOAMG:
      stg_out_endnode();

      if (toc_title[0] != EOS)
      	n = toc_title;
      else
        n = lang.contents;
      if (desttype == TOSTG)
      {
         voutlnf("@node Main \"%s\"", n);
         voutlnf("@symbol \"%s\"", lang.contents);
      }
      else
      {
         if (titleprogram[0] != EOS && toc_title[0] == EOS)
         {
            voutlnf("@node Main \"%s - %s\"", titleprogram, n);
         }
         else
         {
            voutlnf("@node Main \"%s\"", n);
         }
      }

      if (called_maketitle)
         voutlnf("@toc \"%s\"", lang.title);

      output_helpid(0);
      stg_headline("", lang.contents, FALSE);

      if (toc_available)
         toc_output(TOC_NODE1, depth, FALSE);

      if (apx_available)
      {
         output_appendix_line();
         toc_output(TOC_NODE1, depth, TRUE);
      }
      
#if 0
		/* no @endnode here, so the user can add raw cmds to TOC page */
      outln("@endnode");
      outln("");
      outln("");
#endif
	  stg_need_endnode = TRUE;
      break;

   case TOTVH:
      outln("");
      if (toc_title[0] != EOS)
      	n = toc_title;
      else
        n = lang.contents;
      voutlnf(".topic %s", n);
      output_helpid(0);
      out("  ");
      outln(n);
      out("  ");
      output_ascii_line("=", strlen(n));
      outln("");

      if (toc_available)
         toc_output(TOC_NODE1, depth, FALSE);

      if (apx_available)
      {
         output_appendix_line();
         toc_output(TOC_NODE1, depth, TRUE);
      }
      
      outln("");
      break;

   case TOASC:
      if (toc_title[0] != EOS)
      	n = toc_title;
      else
        n = lang.contents;
      if (toc_available)
      {
         if (use_style_book)
         {
            output_ascii_line("=", zDocParwidth);
            outln(n);
            output_ascii_line("=", zDocParwidth);
         }
         else
         {
            outln(n);
            output_ascii_line("=", strlen(n));
         }

         outln("");
         toc_output(TOC_NODE1, depth, FALSE);
         outln("");
      }
      if (apx_available)
      {
         output_appendix_line();
         toc_output(TOC_NODE1, depth, TRUE);
         outln("");
      }
      break;

   case TODRC:     /* <???> */
      break;

   case TOWIN:
   case TOWH4:
   case TOAQV:
      check_endnode();

      outln("{");
      node2NrWinhelp(name, 0);
      voutlnf("#{\\footnote # %s}", name);
      output_helpid(0);
      voutlnf("${\\footnote $ %s}", lang.contents);
      voutlnf("K{\\footnote K %s}", lang.contents);
 
      if (!no_buttons)
      {
         outln(win_browse);
         enable_win_button("BTN_UP", called_maketitle, WIN_TITLE_NODE_NAME);
         {
            int i;
            
            for (i = 0; i < iNumWinButtons; i++)
               enable_win_button(sDocWinButtonName[i], FALSE, NULL);
         }
      }

      if (toc_available)
      {
         outln("\\keepn");
         n = um_strdup_printf("\\fs%d", iDocPropfontSize + 14);
         voutlnf("{%s\\b %s}\\par\\pard\\par", n, toc_title[0] != EOS ? toc_title : lang.contents);
         free(n);
         toc_output(TOC_NODE1, depth, FALSE);
      }

      if (apx_available)
      {
         output_appendix_line();
         toc_output(TOC_NODE1, depth, TRUE);
      }

      outln("}\\page");
      break;

   case TOPCH:
      if (toc_title[0] != EOS)
   	  {
   	     if (titdat.program != NULL)
         voutlnf("screen(capsensitive(\"%s\"), screen(capsensitive(\"%s\"), capsensitive(\"%s\"))", toc_title, titdat.program, lang.contents);
         else
         voutlnf("screen(capsensitive(\"%s\"), capsensitive(\"%s\"))", toc_title, lang.contents);
      } else if (titdat.program != NULL)
      {
         voutlnf("screen(capsensitive(\"%s\"), capsensitive(\"%s\"))", titdat.program, lang.contents);
      } else
      {
         voutlnf("screen(capsensitive(\"%s\"))", lang.contents);
      }
      output_helpid(0);
      pch_headline(lang.contents);
      outln("");
      
      if (uses_maketitle)
         pch_titlepage();

      outln("");
      
      if (toc_available)
      {
         outln(lang.contents);
         output_ascii_line("=", strlen(lang.contents));
         outln("");
         toc_output(TOC_NODE1, depth, FALSE);
      }
      
      if (apx_available)
      {
         output_appendix_line();
         toc_output(TOC_NODE1, depth, TRUE);
      }
      
      outln("");
      outln("\\end");
      outln("");
      break;

   case TOHAH:
   case TOHTM:
   case TOMHH:
      output_helpid(0);

      if (toc_available)
      {
         const char *a_name = "name";
         
#if 0
         if (html_doctype == HTML5)
            a_name = "id";
#endif
         voutlnf("<h1><a %s=\"%s\">%s</a></h1>", a_name, HTML_LABEL_CONTENTS, lang.contents);
         add_label(HTML_LABEL_CONTENTS, FALSE, FALSE, TRUE, TRUE);
         toc_output(TOC_NODE1, depth, FALSE);
      }
      
      if (apx_available)
      {
         output_appendix_line();
         toc_output(TOC_NODE1, depth, TRUE);
      }

      if (use_udo_index)
      {
         voutlnf("\n<h1><a href=\"indexudo%s\">%s</a></h1>\n", outfile.suff, lang.index);
      }

      break;

   case TOKPS:
      if (toc_available)
      {
         outln("newline");

         voutlnf("/NodeName (%s) def", lang.contents);
         voutlnf("20 changeFontSize (%s) udoshow newline %d changeFontSize", lang.contents, laydat.propfontsize);
         toc_output(TOC_NODE1, depth, FALSE);
      }

      if (apx_available)
      {
         output_appendix_line();
         toc_output(TOC_NODE1, depth, TRUE);
      }

      if (toc_available)
         c_newpage();

/*    check_endnode();
      output_helpid(0);

      if (toc_available)
      {
         outln("18 changeFontSize");
         voutlnf("(%s) show newline", lang.contents);
         outln("11 changeFontSize changeBaseFont");
         toc_output(TOC_NODE1, depth, FALSE);
      }
      
      if (apx_available)
      {
         output_appendix_line();
         toc_output(TOC_NODE1, depth, TRUE);
      }
      
      c_newpage();
*/
      break;

   case TOLDS:
      output_helpid(0);
      outln("<toc>");
      break;

   case TORTF:
      voutlnf("\\plain\\s4\\ql\\b\\f0\\li567\\fi-567\\fs%d", laydat.node1size);
      voutlnf("%s", lang.contents);
      voutlnf("\\par\\pard\\par\\pard \\plain \\s1\\qj\\f0\\fs%d", iDocPropfontSize);
      outln("{\\field{\\*\\fldinst {TOC \\\\t \"Node1;1;Node2;2;Node3;3;Node4;4\" }}{\\fldrslt {Please refresh!}}}");
      outln("\\page");
      
   }  /* switch (desttype) */
}





/*******************************************************************************
*
*  c_label():
*     output a label in 2nd pass
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_label(void)
{
   char   sLabel[512],  /* */
          sTemp[512];   /* */


   tokcpy2(sLabel, 512);                  /* Tokens umkopieren */

   if (sLabel[0] == EOS)
   {
      error_missing_parameter(CMD_LABEL);
      return;
   }

   p2_lab_counter++;

   replace_udo_quotes(sLabel);
   convert_tilde(sLabel);

   switch (desttype)
   {
   case TOTEX:
      label2tex(sLabel);
      c_divis(sLabel);
      c_vars(sLabel);
      voutlnf("\\label{%s}", sLabel);
      break;
      
      
   case TOPDL:
      label2tex(sLabel);
      c_divis(sLabel);
      c_vars(sLabel);
      voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
      break;
      
      
   case TOLYX:
      outln("");
      outln("\\layout Standard");
      voutlnf("\\begin_inset Label %s", sLabel);
      outln("");
      voutlnf("\\end_inset");
      outln("");
      break;
   
      
   case TOSTG:
      node2stg(sLabel);
      c_divis(sLabel);
      
      if (use_label_inside_index && !no_index)
         voutlnf("@symbol ari \"%s\"", sLabel);
      else
         voutlnf("@symbol ar \"%s\"", sLabel);
      
      break;
      

   case TOHAH:                            /* HTML Apple Help (since V6.5.17) */
   case TOHTM:                            /* HTML */
   case TOMHH:                            /* Microsoft HTML Help */
                                          /* v 6.5.19 [fd] */
      if (!no_index && use_label_inside_index)
      {
         label2html(sLabel);              /* r6pl2 */

                                          /* check if we're in description environment */
         if ( (iEnvLevel > 0) && (iEnvType[iEnvLevel] == ENV_DESC) )
         {
            if (!bDescDDOpen)             /* DD hasn't been opened yet */
            {
               if (html_doctype == HTML5)
               {
                  voutlnf("<dd><a id=\"%s\"></a></dd>", sLabel);
               }
               else
               {
                  voutlnf("<dd><a name=\"%s\"></a></dd>", sLabel);
               }
            }
            else
            {
               if (html_doctype == HTML5)
               {
                  voutlnf("<a id=\"%s\"></a>", sLabel);
               }
               else
               {
                  voutlnf("<a name=\"%s\"></a>", sLabel);
               }
            }
         }
         else
         {
            if (html_doctype == HTML5)
            {
               voutlnf("<a id=\"%s\"></a>", sLabel);
            }
            else
            {
               voutlnf("<a name=\"%s\"></a>", sLabel);
            }
         }
      }
   
      break;
   
   
   case TOLDS:
      voutlnf("<label id=\"%s\">", sLabel);
      break;
      
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
                                          /* r5pl10 */
      if (use_label_inside_index && !no_index)
      {
          voutf("K{\\footnote K %s}", sLabel);
      }
      
      if (bDocWinOldKeywords)
      {
         strcpy(sTemp, sLabel);
         del_internal_styles(sTemp);
         node2winhelp(sTemp);
         voutlnf("#{\\footnote # %s}", sTemp);
      }
      
      label2NrWinhelp(sLabel, p2_lab_counter);
      voutf("#{\\footnote # %s}", sLabel);
      break;
      
      
   case TORTF:
                                          /* r6pl6 */
      if (use_label_inside_index && !no_index)
      {
         voutf("{\\xe\\v %s}", sLabel);
      }
      
      break;


   case TOKPS:                            /* New in r6pl15 [NHz] */
                                          /* Fixed Bug #0000040 in r6.3pl16 [NHz] */
      node2postscript(sLabel, KPS_NAMEDEST);
      voutlnf("/%s NameDest", sLabel);
      /* Must be changed if (!label ...) is possible */
   }
}





/*******************************************************************************
*
*  c_alias():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void c_alias(void)
{
   p2_lab_counter++;
}


LOCAL void set_labelname(LABEL *label, const char *name)
{
   strcpy(label->name, name);
   replace_udo_quotes(label->name);
   label->len = strlen(label->name);
#if USE_NAME_HASH
   {
      _UWORD hash_index;
        
      hash_index = hash_val(label->name);
      label->next_hash = hash[hash_index];
      hash[hash_index] = label;
   }
#endif
}


/*******************************************************************************
*
*  make_label():
*     add a label or alias to the internal list of labels
*
*  @label: label name string
*  @isn: TRUE: chapter (node), FALSE: label or alias
*  @isa: TRUE: alias, FALSE: label
*  @isp: TRUE: popup
*  @ignore_index: TRUE: does not appear in index
*
*  Notes:
*     Labels are now added in all formats, because else *toc_output() would output
*     wrong results because it directly references using the label index.
*
*  Return:
*     - FALSE: error
*     - p1_lab_counter
*
******************************************|************************************/

LOCAL int make_label(const char *label, const _BOOL isn, const _BOOL isa, const _BOOL isp, _BOOL ignore_index, _BOOL ignore_links, _BOOL referenced)
{
   LABEL   *labptr;  /* ^ to label structure in memory */

   if (p1_lab_counter + 1 >= MAXLABELS)   /* list overflow? */
   {
      error_too_many_label();
      return FALSE;
   }

   if (label[0] == EOS || strlen(label) > MAX_LABEL_LEN)
      return FALSE;

                                          /* get space for new label */
   labptr = (LABEL *)malloc(sizeof(LABEL));

   if (labptr == NULL)                    /* no more memory? */
   {
       return FALSE;
   }

   p1_lab_counter++;
   lab[p1_lab_counter] = labptr;

   set_labelname(labptr, label);

   labptr->labindex = p1_lab_counter;
   labptr->is_node = isn;
   labptr->is_alias = isa;
   labptr->is_popup = isp;
   labptr->tocindex = p1_toc_counter;
   labptr->ignore_links = ignore_links;
   labptr->ignore_index = ignore_index;
   labptr->referenced = referenced;

   if (pflag[PASS1].inside_apx)
   {
      labptr->appendix = TRUE;
      
      labptr->n1       = p1_apx_n1;
      labptr->n2       = p1_apx_n2;
      labptr->n3       = p1_apx_n3;
      labptr->n4       = p1_apx_n4;
      labptr->n5       = p1_apx_n5;
      labptr->n6       = p1_apx_n6;
   }
   else
   {
      labptr->appendix = FALSE;
      
      labptr->n1       = p1_toc_n1;
      labptr->n2       = p1_toc_n2;
      labptr->n3       = p1_toc_n3;
      labptr->n4       = p1_toc_n4;
      labptr->n5       = p1_toc_n5;
      labptr->n6       = p1_toc_n6;
   }

   /* set label in project file */
   if (isa)
      save_upr_entry_alias(sCurrFileName, current_node_name_sys, uiCurrFileLine);
   else if (!isn) /* only labels which are not nodes */
      save_upr_entry_label(sCurrFileName, current_node_name_sys, uiCurrFileLine);

   return p1_lab_counter;
}





/*******************************************************************************
*
*  add_label():
*     add a label to the internal list of labels
*
*  Notes:
*     Labels are now added in all formats, because else *toc_output() would output
*     wrong results because it directly references using the label index.
*
*  Return:
*     - 0: error
*     - p1_lab_counter
*
******************************************|************************************/

GLOBAL int add_label(const char *label, const _BOOL isn, const _BOOL isp, _BOOL ignore_index, _BOOL ignore_links)
{
   return make_label(label, isn, FALSE, isp, ignore_index, ignore_links, FALSE);
}


/*******************************************************************************
*
*  add_alias():
*     adds an alias to the internal list
*
*  Note:
*     An alias is another name of a node.
*
*  Return:
*     FALSE: any error occurred
*      TRUE: success
*
******************************************|************************************/

GLOBAL int add_alias(const char *alias, const _BOOL isp, _BOOL referenced)
{
   return make_label(alias, FALSE, TRUE, isp, FALSE, FALSE, referenced);
}





/*******************************************************************************
*
*  set_ignore_headline():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_headline(void)
{
   if (!check_toc_counters())
      return;
   
   toc[p1_toc_counter]->ignore_headline = TRUE;
}





/*******************************************************************************
*
*  set_ignore_bottomline():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_bottomline(void)
{
   if (!check_toc_counters())
      return;
   
   toc[p1_toc_counter]->ignore_bottomline = TRUE;
}





/*******************************************************************************
*
*  set_raw_header_filename():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_raw_header_filename(void)
{
   char s[MYFILE_FULL_LEN + 1];
   
   if (!check_toc_and_token())
      return;

   um_strcpy(s, token[1], sizeof(s), "set_raw_header_filename[1]");

   if (p1_toc_counter == 0)
   {
      sDocRawHeaderFilename = file_listadd(s);
   }
   else
   {
      toc[p1_toc_counter]->raw_header_filename = file_listadd(s);
   }
}





/*******************************************************************************
*
*  set_raw_footer_filename():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_raw_footer_filename(void)
{
   char s[MYFILE_FULL_LEN + 1];
   
   if (!check_toc_and_token())
      return;

   um_strcpy(s, token[1], sizeof(s), "set_raw_footer_filename[1]");

   if (p1_toc_counter == 0)
   {
      sDocRawFooterFilename = file_listadd(s);
   }
   else
   {
      toc[p1_toc_counter]->raw_footer_filename = file_listadd(s);
   }
}





/*******************************************************************************
*
*  set_ignore_raw_header():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_raw_header(void)
{
   if (!check_toc_counters())
      return;

   toc[p1_toc_counter]->ignore_raw_header = TRUE;
}





/*******************************************************************************
*
*  set_ignore_raw_footer():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_raw_footer(void)
{
   if (!check_toc_counters())
      return;
   
   toc[p1_toc_counter]->ignore_raw_footer = TRUE;
}





/*******************************************************************************
*
*  set_ignore_footer():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_footer(void)
{
   if (!check_toc_counters())
      return;

   toc[p1_toc_counter]->ignore_footer = TRUE;
}





/*******************************************************************************
*
*  set_ignore_title():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_title(void)
{
   if (!check_toc_counters())
      return;

   toc[p1_toc_counter]->ignore_title = TRUE;
}





/*******************************************************************************
*
*  set_ignore_links():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_links(void)
{
   int   li;  /* */
   
   
   if (!check_toc_counters())
      return;

   toc[p1_toc_counter]->ignore_links = TRUE;

   li = toc[p1_toc_counter]->labindex;

   if (li > 0)
      lab[li]->ignore_links = TRUE;
}





/*******************************************************************************
*
*  set_ignore_index():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_index(void)
{
   int   li;  /* */
   
   
   if (!check_toc_counters())
      return;

   toc[p1_toc_counter]->ignore_index = TRUE;

   li = toc[p1_toc_counter]->labindex;

   if (li > 0)
      lab[li]->ignore_index = TRUE;
}





/*******************************************************************************
*
*  set_ignore_subtoc():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_ignore_subtoc(void)
{
   if (!check_toc_counters())
      return;

   toc[p1_toc_counter]->ignore_subtoc = TRUE;
}





/*******************************************************************************
*
*  set_helpid():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_helpid(void)
{
   char   id[512],  /* */
         *ptr;      /* */
   
   
   if (!check_toc_and_token())
      return;

   um_strcpy(id, token[1], 512, "set_helpid");

   /* <???> Hier pruefen, ob nur A-Z, a-z, 0-9 und _ benutzt werden */

   ptr = (char *)malloc(1 + strlen(id) * sizeof(char));

   if (!ptr)
   {
      bFatalErrorDetected = TRUE;
   }
   else
   {  
      strcpy(ptr, id);
      toc[p1_toc_counter]->helpid = ptr;
   }

   bUseIdMapFileC = TRUE;                 /* r6pl8: bei Verwendung auch die Datei erzeugen! */
}





/*******************************************************************************
*
*  set_win_button():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void win_set_button(void)
{
   char *ptr;
   int i;
    
   if (token[1][0] == EOS || token[2][0] == EOS)
   {
      error_wrong_nr_parameters(token[0]);
      return;
   }
    
   for (i = 0; i < iNumWinButtons; i++)
      if (strcmp(token[1], sDocWinButtonName[i]) == 0)
         break;
   if (i >= iNumWinButtons)
   {
       error_message(_("windows button %s not defined"), token[1]);
       return;
   }
    
   /* <???> Hier pruefen, ob nur A-Z, a-z, 0-9 und _ benutzt werden */

   ptr = strdup(token[2]);
    
   if (ptr == NULL)
   {
      bFatalErrorDetected = TRUE;
   }
   else
   {
      toc[p1_toc_counter]->win_button[i] = ptr;
   }
}


/*******************************************************************************
*
*  set_mapping():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_mapping(void)
{
   char   map[512];  /* */
   int    m;         /* */
   
   
   if (!check_toc_and_token())
      return;

   um_strcpy(map, token[1], 512, "set_mapping[1]");

   /* <???> Hier pruefen, ob nur 0-9 benutzt wird */

   m = atoi(token[1]);

   if (m >= 0)
   {
      toc[p1_toc_counter]->mapping = m;
      bUseIdMapFileC = TRUE;              /* r6pl8: bei Verwendung auch die Datei erzeugen! */
   }
   else
   {
      error_message(_("mapping not numeric or not of type integer"));
   }
}





/*******************************************************************************
*
*  set_chapter_image():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_chapter_image(void)
{
   _UWORD bitcnt;
   char s[MYFILE_FULL_LEN], *ptr;
   
   if (!check_toc_and_token())
      return;
   
   fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
   sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);

   if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
      replace_char(s, '\\', '/');
   
   ptr = strdup(s);
   
   if (ptr == NULL)
   {
      bFatalErrorDetected = TRUE;
      return;
   }

   toc[p1_toc_counter]->image = ptr;

   if (desttype != TOHTM && desttype != TOMHH && desttype != TOHAH)
      return;

   /* Ausmasse des Icons ermitteln */
   get_picture_size(s, NULL, &toc[p1_toc_counter]->uiImageWidth, &toc[p1_toc_counter]->uiImageHeight, &bitcnt);
}





/*******************************************************************************
*
*  set_chapter_icon():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_chapter_icon(void)
{
   char s[MYFILE_FULL_LEN], *ptr;
   _UWORD bitcnt;
   
   if (!check_toc_and_token())
      return;
   
   fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
   sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);
   
   if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
      replace_char(s, '\\', '/');

   ptr = strdup(s);
   
   if (ptr == NULL)
   {
      bFatalErrorDetected = TRUE;
      return;
   }

   toc[p1_toc_counter]->icon = ptr;

   if (desttype != TOHTM)
      return;

   /* Ausmasse des Icons ermitteln */
   get_picture_size(s, NULL, &toc[p1_toc_counter]->uiIconWidth, &toc[p1_toc_counter]->uiIconHeight, &bitcnt);
}





/*******************************************************************************
*
*  set_chapter_icon_active():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_chapter_icon_active(void)
{
   char s[MYFILE_FULL_LEN], *ptr;
   _UWORD bitcnt;
   
   if (!check_toc_and_token())
      return;
   
   fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
   sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);
   
   if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
      replace_char(s, '\\', '/');

   ptr = strdup(s);
   
   if (ptr == NULL)
   {
      bFatalErrorDetected = TRUE;
      return;
   }

   toc[p1_toc_counter]->icon_active = ptr;

   if (desttype != TOHTM)
      return;

   /* Ausmasse des Icons ermitteln */
   get_picture_size(s, NULL, &toc[p1_toc_counter]->uiIconActiveWidth, &toc[p1_toc_counter]->uiIconActiveHeight, &bitcnt);
}





/*******************************************************************************
*
*  set_chapter_icon_text():
*     ???
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_chapter_icon_text(void)
{
   char   s[512],  /* */
         *ptr;     /* */
   
   
   if (!check_toc_and_token())
      return;

   tokcpy2(s, 512);
   auto_quote_chars(s, TRUE);

   ptr = (char *)malloc(1 + strlen(s) * sizeof(char));

   if (!ptr)
   {
      bFatalErrorDetected = TRUE;
   }
   else
   {   
      strcpy(ptr, s);
      toc[p1_toc_counter]->icon_text = ptr;
   }
}





/*******************************************************************************
*
*  add_toc_to_toc():
*     add TOC page (indexudo) to toc[0]
*
*  Notes:
*     Used for output formats which require toc[0].
*
*  Return:
*      TRUE: everything's fine
*     FALSE: error
*
******************************************|************************************/

LOCAL _BOOL add_toc_to_toc(void)
{
   TOCITEM  *tocptr;  /* ^ to TOCITEM structure */


                                          /* get memory for new TOC structure */
   tocptr = (TOCITEM *)malloc(sizeof(TOCITEM));
 
   if (tocptr == NULL)                    /* memory error */
      return FALSE;

   memset(tocptr, 0, sizeof(TOCITEM));    /* clear whole (uninitialized) content first */

   strcpy(tocptr->name,     lang.contents);
   strcpy(tocptr->filename, FRAME_FILE_CON);

   tocptr->invisible  = TRUE;
   tocptr->toctype    = TOC_TOC;
   tocptr->prev_index = 0;
   tocptr->next_index = 1;
   tocptr->mapping    = -1;
   
   toc[0] = tocptr;

   return TRUE;
}





/*******************************************************************************
*
*  toc_init_lang():
*     add TOC title to toc[0]
*
*  Notes:
*     This function is only called by init_lang().
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void toc_init_lang(void)
{
   strcpy(toc[0]->name, lang.contents);
}





/*******************************************************************************
*
*  init_new_toc_entry():
*     initialize a new TOC entry
*
*  Return:
*     ^ TOCITEM
*
******************************************|************************************/

LOCAL TOCITEM *init_new_toc_entry(const int toctype, _BOOL invisible)
{
   TOCITEM *tocptr;

   if (p1_toc_counter >= MAXTOCS)
   {
      error_too_many_node();
      bBreakInside = TRUE;
      return NULL;
   }

                                          /* get memory for new TOC structure */
   tocptr = (TOCITEM *)malloc(sizeof(TOCITEM));
 
   if (tocptr == NULL)                    /* memory error */
      return FALSE;

   memset(tocptr, 0, sizeof(TOCITEM));    /* clear whole (uninitialized) content first */

   tokcpy2(tocptr->name, MAX_NODE_LEN + 1);

   if (tocptr->name[0] == EOS)            /* r5pl14 */
   {
      fatal_message("missing node name");
      bFatalErrorDetected = TRUE;
      free(tocptr);
      return NULL;
   }
                                          /* New in r6pl15 [NHz] */
                                          /* Set node in project file */
   save_upr_entry_node(toctype, sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine);
   
#if 1
   c_styles(tocptr->name);

   switch (desttype)                      /* r5pl3 */
   {
   case TOWIN:
   case TOWH4:
   case TOAQV:
      c_win_styles(tocptr->name);
      break;
      
   case TORTF:
      c_rtf_styles(tocptr->name);
      c_rtf_quotes(tocptr->name);
      break;
      
   default:
      c_internal_styles(tocptr->name);
   }
#endif

   if (desttype == TOPCH)                 /* Pure C Help */
      replace_all_copyright(tocptr->name);

#if 0
   /* fd:2010-02-05: only set non Null values explicitely! */
   
   tocptr->converted           = FALSE;
   tocptr->ignore_subtoc       = FALSE;
   tocptr->ignore_links        = FALSE;
   tocptr->ignore_index        = FALSE;
   tocptr->ignore_title        = FALSE;   /*r6pl13*/
   tocptr->ignore_headline     = FALSE;
   tocptr->ignore_bottomline   = FALSE;
   tocptr->raw_header_filename = 0;
   tocptr->raw_footer_filename = 0;
   tocptr->ignore_raw_header   = FALSE;   /*r6pl10*/
   tocptr->ignore_raw_footer   = FALSE;   /*r6pl10*/
   tocptr->ignore_footer       = FALSE;   /*r6pl2*/
   tocptr->filename[0]         = EOS;
   tocptr->dirname = 0;
   tocptr->counter_command = 0;
   tocptr->keywords            = NULL;
   tocptr->description         = NULL;    /*r6pl5*/
   tocptr->robots              = NULL;    /*V6.5.17*/
   tocptr->bgsound = 0;
   tocptr->helpid              = NULL;
   tocptr->image               = NULL;
   tocptr->uiImageWidth        = 0;
   tocptr->uiImageHeight       = 0;
   tocptr->icon                = NULL;
   tocptr->uiIconWidth         = 0;
   tocptr->uiIconHeight        = 0;
   tocptr->icon_active         = NULL;
   tocptr->uiIconActiveWidth   = 0;
   tocptr->uiIconActiveHeight  = 0;
   tocptr->icon_text           = NULL;
   tocptr->has_children        = FALSE;   /*r6pl5*/
   tocptr->count_n2            = 0;       /*r6pl8*/
   tocptr->count_n3            = 0;       /*r6pl8*/
   tocptr->count_n4            = 0;       /*r6pl8*/
   tocptr->count_n5            = 0;       /*r6pl8*/
   tocptr->count_n6            = 0;       /*r6pl8*/
#endif
   
   if (sCurrFileName[0] == EOS)
   {
   	  /* should only happen when called by add_toc_to_toc(),
   	     because the input file has not yet been opened */
   	  tocptr->source_location.id = 0;
   	  tocptr->source_location.line = 0;
   } else
   {
	   tocptr->source_location.id = file_listadd(sCurrFileName);
   	   tocptr->source_location.line = uiCurrFileLine;
   }
   
   tocptr->toctype             = toctype;
   tocptr->mapping             = -1;

   tocptr->backimage = sDocBackImage;
   tocptr->backcolor = sDocBackColor.rgb;
   tocptr->textcolor = sDocTextColor.rgb;
   tocptr->linkcolor = sDocLinkColor.rgb;
   tocptr->alinkcolor = sDocAlinkColor.rgb;
   tocptr->vlinkcolor = sDocVlinkColor.rgb;

   /* Texinfo kennt keine versteckten Nodes, daher fuer */
   /* Texinfo das invisible-Flag immer auf FALSE setzen. */
   if (desttype == TOINF)
      invisible = FALSE;
   tocptr->invisible = invisible;

   p1_toctype = toctype;

   return tocptr;
}





/* Nicht LOCAL: wird von abo.c und udo.c benutzt! */

/*******************************************************************************
*
*  add_nodetype_to_toc():
*     adds a node of a certain type to the TOC
*
*  Return:
*     FALSE: some error occurred
*      TRUE: success
*
******************************************|************************************/

GLOBAL _BOOL add_nodetype_to_toc(

int             nodetype,    /* TOC_... */
const _BOOL   popup,       /* */
const _BOOL   invisible)   /* */
{
   TOCITEM     *tocptr;      /* */
   int          li;          /* */
   int          html_merge;  /* */

   
   switch (nodetype)                      /* check if this node now is allowed */
   {
   case TOC_NODE6:
      if (last_n5_index == 0)
      {
         error_node6_not_allowed();
         return FALSE;
      }

      break;
   
   case TOC_NODE5:
      if (last_n4_index == 0)
      {
         error_node5_not_allowed();
         return FALSE;
      }

      break;
   
   case TOC_NODE4:
      if (last_n3_index == 0)
      {
         error_node4_not_allowed();
         return FALSE;
      }
      
      break;
      
   case TOC_NODE3:
      if (last_n2_index == 0)
      {
         error_node3_not_allowed();
         return FALSE;
      }
      
      break;
      
   case TOC_NODE2:
      if (last_n1_index == 0)
      {
         error_node2_not_allowed();
         return FALSE;
      }
   }
   
   tocptr = init_new_toc_entry(nodetype, invisible);

   if (tocptr == NULL)
      return FALSE;


   switch (nodetype)                      /* increase counter for node type */
   {
   case TOC_NODE6:
      all_subsubsubsubsubnodes++;
      called_subsubsubsubsubnode = TRUE;     /* r5pl6 */
      break;
   case TOC_NODE5:
      all_subsubsubsubnodes++;
      break;
   case TOC_NODE4:
      all_subsubsubnodes++;
      break;
   case TOC_NODE3:
      all_subsubnodes++;
      break;
   case TOC_NODE2:
      all_subnodes++;
      break;
   case TOC_NODE1:
      all_nodes++;
   }


   /* ---------------------------------------------------- */
   /* r5pl6: Listenartige Verkettung erzeugen              */
   /* ---------------------------------------------------- */
   /* noch ist p1_toc_counter nicht inkrementiert worden,  */
   /* zeigt daher auf den letzten (Sub(Sub))Node           */

   tocptr->prev_index = p1_toc_counter;

   /* Bei HTML muss das Mergen beachtet werden! Der        */
   /* Vorgaenger wird daher auf den letzten *Node gesetzt  */
   
                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOHAH)
   {
      if (html_merge_node6 && last_n5_index > 0)
         tocptr->prev_index = last_n5_index;

      if (html_merge_node5 && last_n4_index > 0)
         tocptr->prev_index = last_n4_index;

      if (html_merge_node4 && last_n3_index > 0)
         tocptr->prev_index = last_n3_index;

      if (html_merge_node3 && last_n2_index > 0)
         tocptr->prev_index = last_n2_index;

      if (html_merge_node2 && last_n1_index > 0)
         tocptr->prev_index = last_n1_index;

      if (html_merge_node1)
         tocptr->prev_index = 0;
   }

   /* Den Nachfolger des Vorgaengers setzen: auf diesen */

   toc[p1_toc_counter]->next_index = p1_toc_counter + 1;
   

   /* Merken, dass der uebergeordnete Kinder hat */
   /* und die Anzahl der Subsubnodes erhoehen */
   
   switch (nodetype)
   {
   case TOC_NODE6:
      if (last_n5_index > 0)
      {
         toc[last_n5_index]->has_children = TRUE;
         toc[last_n5_index]->count_n6++;
      }
      
      break;
   
   case TOC_NODE5:
      if (last_n4_index > 0)
      {
         toc[last_n4_index]->has_children = TRUE;
         toc[last_n4_index]->count_n5++;
      }
      
      break;
   
   case TOC_NODE4:
      if (last_n3_index > 0)
      {
         toc[last_n3_index]->has_children = TRUE;
         toc[last_n3_index]->count_n4++;
      }
   
      break;
      
   case TOC_NODE3:
      if (last_n2_index > 0)
      {
         toc[last_n2_index]->has_children = TRUE;
         toc[last_n2_index]->count_n3++;
      }
      
      break;
   
   case TOC_NODE2:
      if (last_n1_index > 0)
      {
         toc[last_n1_index]->has_children = TRUE;
         toc[last_n1_index]->count_n2++;
      }
   }

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOHAH)
   {
      switch (nodetype)
      {
      case TOC_NODE6:
         /* nothing to do until we introduce TOC_NODE7 ... */
         break;
         
      case TOC_NODE5:
      case TOC_NODE4:
      case TOC_NODE3:
      case TOC_NODE2:
      case TOC_NODE1:
         /* Wenn Subsubsubsubnodes gemerged werden, dann muss    */
         /* beim letzten Subsubnode dieser Subsubnode als        */
         /* naechster Index eingetragen werden!                  */

         if (html_merge_node6 && last_n5_index > 0)
            toc[last_n5_index]->next_index = p1_toc_counter + 1;
      }

      switch (nodetype)
      {
      case TOC_NODE4:
      case TOC_NODE3:
      case TOC_NODE2:
      case TOC_NODE1:
         /* Wenn Subsubsubsubnodes gemerged werden, dann muss    */
         /* beim letzten Subsubnode dieser Subsubnode als        */
         /* naechster Index eingetragen werden!                  */

         if (html_merge_node5 && last_n4_index > 0)
            toc[last_n4_index]->next_index = p1_toc_counter + 1;
      }
      
      switch (nodetype)
      {
      case TOC_NODE3:
      case TOC_NODE2:
      case TOC_NODE1:
         /* Wenn Subsubsubnodes gemerged werden, dann muss       */
         /* beim letzten Subsubnode dieser Subsubnode als        */
         /* naechster Index eingetragen werden!                  */

         if (html_merge_node4 && last_n3_index > 0)
            toc[last_n3_index]->next_index = p1_toc_counter + 1;
      }
      
      switch (nodetype)
      {
      case TOC_NODE2:
      case TOC_NODE1:
         /* Wenn Subsubnodes gemerged werden, dann muss beim     */
         /* letzten Subnode dieser Subnode als naechster         */
         /* Index eingetragen werden!                            */
      
         if (html_merge_node3 && last_n2_index > 0)
            toc[last_n2_index]->next_index = p1_toc_counter + 1;
      }
      
      switch (nodetype)
      {
      case TOC_NODE1:
         /* Werden Subnodes gemerged, so muss beim letzten Node  */
         /* dieser Node als naechster Index eingetragen werden!  */
      
         if (html_merge_node2 && last_n1_index > 0)
            toc[last_n1_index]->next_index = p1_toc_counter + 1;
      }
   }


   /* Der Zeiger auf den Nachfolger muss vom Nachfolger gesetzt werden. */

   tocptr->next_index = 0;
   

   /* Hilfsvariablen setzen fuer die uebergeordneten Nodes */

   switch (nodetype)
   {
   case TOC_NODE6:
      tocptr->up_n1_index = last_n1_index;
      tocptr->up_n2_index = last_n2_index;
      tocptr->up_n3_index = last_n3_index;
      tocptr->up_n4_index = last_n4_index;
      tocptr->up_n5_index = last_n5_index;

      last_n6_index = p1_toc_counter + 1;
      break;
      
   case TOC_NODE5:
      tocptr->up_n1_index = last_n1_index;
      tocptr->up_n2_index = last_n2_index;
      tocptr->up_n3_index = last_n3_index;
      tocptr->up_n4_index = last_n4_index;
      tocptr->up_n5_index = 0;

      last_n5_index = p1_toc_counter + 1;
      last_n6_index = 0;
      break;
      
   case TOC_NODE4:
      tocptr->up_n1_index = last_n1_index;
      tocptr->up_n2_index = last_n2_index;
      tocptr->up_n3_index = last_n3_index;
      tocptr->up_n4_index = 0;

      last_n4_index = p1_toc_counter + 1;
      last_n5_index = 0;
      last_n6_index = 0;
      break;
      
   case TOC_NODE3:
      tocptr->up_n1_index = last_n1_index;
      tocptr->up_n2_index = last_n2_index;
      tocptr->up_n3_index = 0;
      tocptr->up_n4_index = 0;
      tocptr->up_n5_index = 0;

      last_n3_index = p1_toc_counter + 1;
      last_n4_index = 0;
      last_n5_index = 0;
      last_n6_index = 0;
      break;
      
   case TOC_NODE2:
      tocptr->up_n1_index = last_n1_index;
      tocptr->up_n2_index = 0;
      tocptr->up_n3_index = 0;
      tocptr->up_n4_index = 0;
      tocptr->up_n5_index = 0;

      last_n2_index = p1_toc_counter + 1;
      last_n3_index = 0;
      last_n4_index = 0;
      last_n5_index = 0;
      last_n6_index = 0;
      break;
      
   case TOC_NODE1:
      tocptr->up_n1_index = 0;
      tocptr->up_n2_index = 0;
      tocptr->up_n3_index = 0;
      tocptr->up_n4_index = 0;
      tocptr->up_n5_index = 0;

      last_n1_index = p1_toc_counter + 1;
      last_n2_index = 0;
      last_n3_index = 0;
      last_n4_index = 0;
      last_n5_index = 0;
      last_n6_index = 0;
   }
   
   /* ---------------------------------------------------- */

   /* Zaehler hochsetzen und Zeiger in das Array kopieren  */
   
   p1_toc_counter++;
   toc[p1_toc_counter] = tocptr;

   if (pflag[PASS1].inside_apx)
   {
      apx_available = TRUE;

      switch (nodetype)
      {

      case TOC_NODE6:
         p1_apx_n6++;
         break;

      case TOC_NODE5:
         p1_apx_n5++;
         p1_apx_n6 = 0;
         break;
         
      case TOC_NODE4:
         p1_apx_n4++;
         p1_apx_n5 = 0;
         p1_apx_n6 = 0;
         break;
         
      case TOC_NODE3:
         p1_apx_n3++;
         p1_apx_n4 = 0;
         p1_apx_n5 = 0;
         p1_apx_n6 = 0;
         break;
         
      case TOC_NODE2:
         p1_apx_n2++;
         p1_apx_n3 = 0;
         p1_apx_n4 = 0;
         p1_apx_n5 = 0;
         p1_apx_n6 = 0;
         break;
      
      case TOC_NODE1:
         p1_apx_n1++;
         p1_apx_n2 = 0;
         p1_apx_n3 = 0;
         p1_apx_n4 = 0;
         p1_apx_n5 = 0;
         p1_apx_n6 = 0;
      }
      
      tocptr->appendix = TRUE;
      
      tocptr->n1 = p1_apx_n1;
      tocptr->n2 = p1_apx_n2;
      tocptr->n3 = p1_apx_n3;
      tocptr->n4 = p1_apx_n4;
      tocptr->n5 = p1_apx_n5;
      tocptr->n6 = p1_apx_n6;
      
      if (!invisible)
      {
         switch (nodetype)
         {
         case TOC_NODE6:
            p1_apx_nr6++;
            break;
            
         case TOC_NODE5:
            p1_apx_nr5++;
            p1_apx_nr6 = 0;
            break;
            
         case TOC_NODE4:
            p1_apx_nr4++;
            p1_apx_nr5 = 0;
            p1_apx_nr6 = 0;
            break;
         
         case TOC_NODE3:
            p1_apx_nr3++;
            p1_apx_nr4 = 0;
            p1_apx_nr5 = 0;
            p1_apx_nr6 = 0;
            break;
            
         case TOC_NODE2:
            p1_apx_nr2++;
            p1_apx_nr3 = 0;
            p1_apx_nr4 = 0;
            p1_apx_nr5 = 0;
            p1_apx_nr6 = 0;
            break;
         
         case TOC_NODE1:
            p1_apx_nr1++;
            p1_apx_nr2 = 0;
            p1_apx_nr3 = 0;
            p1_apx_nr4 = 0;
            p1_apx_nr5 = 0;
            p1_apx_nr6 = 0;
         }
         
         tocptr->nr1 = p1_apx_nr1;
         tocptr->nr2 = p1_apx_nr2;
         tocptr->nr3 = p1_apx_nr3;
         tocptr->nr4 = p1_apx_nr4;
         tocptr->nr5 = p1_apx_nr5;
         tocptr->nr6 = p1_apx_nr6;
      }
   }
   else
   {
      toc_available = TRUE;
      
      switch (nodetype)
      {
      case TOC_NODE6:
         p1_toc_n6++;
         break;
         
      case TOC_NODE5:
         p1_toc_n5++;
         p1_toc_n6 = 0;
         break;
         
      case TOC_NODE4:
         p1_toc_n4++;
         p1_toc_n5 = 0;
         p1_toc_n6 = 0;
         break;
         
      case TOC_NODE3:
         p1_toc_n3++;
         p1_toc_n4 = 0;
         p1_toc_n5 = 0;
         p1_toc_n6 = 0;
         break;
         
      case TOC_NODE2:
         p1_toc_n2++;
         p1_toc_n3 = 0;
         p1_toc_n4 = 0;
         p1_toc_n5 = 0;
         p1_toc_n6 = 0;
         break;
      
      case TOC_NODE1:
         p1_toc_n1++;
         p1_toc_n2 = 0;
         p1_toc_n3 = 0;
         p1_toc_n4 = 0;
         p1_toc_n5 = 0;
         p1_toc_n6 = 0;
      }
      
      tocptr->appendix = FALSE;
      
      tocptr->n1 = p1_toc_n1;
      tocptr->n2 = p1_toc_n2;
      tocptr->n3 = p1_toc_n3;
      tocptr->n4 = p1_toc_n4;
      tocptr->n5 = p1_toc_n5;
      tocptr->n6 = p1_toc_n6;
      
      if (!invisible)
      {
         switch (nodetype)
         {
         case TOC_NODE6:
            p1_toc_nr6++;
            break;
            
         case TOC_NODE5:
            p1_toc_nr5++;
            p1_toc_nr6 = 0;
            break;
            
         case TOC_NODE4:
            p1_toc_nr4++;
            p1_toc_nr5 = 0;
            p1_toc_nr6 = 0;
            break;
         
         case TOC_NODE3:
            p1_toc_nr3++;
            p1_toc_nr4 = 0;
            p1_toc_nr5 = 0;
            p1_toc_nr6 = 0;
            break;

         case TOC_NODE2:
            p1_toc_nr2++;
            p1_toc_nr3 = 0;
            p1_toc_nr4 = 0;
            p1_toc_nr5 = 0;
            p1_toc_nr6 = 0;
            break;
         
         case TOC_NODE1:
            p1_toc_nr1++;
            p1_toc_nr2 = 0;
            p1_toc_nr3 = 0;
            p1_toc_nr4 = 0;
            p1_toc_nr5 = 0;
            p1_toc_nr6 = 0;
         }
         
         tocptr->nr1 = p1_toc_nr1;
         tocptr->nr2 = p1_toc_nr2;
         tocptr->nr3 = p1_toc_nr3;
         tocptr->nr4 = p1_toc_nr4;
         tocptr->nr5 = p1_toc_nr5;
         tocptr->nr6 = p1_toc_nr6;
      }
   }

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
   {
      /* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
      /* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */

      get_html_filename(p1_toc_counter, tocptr->filename, &html_merge);
   }

   li = add_label(tocptr->name, TRUE, popup, FALSE, FALSE);

   if (li > 0)                            /* and not li>=0, V6.5.17 [GS] */
      tocptr->labindex = li;

   return TRUE;    
}





/*******************************************************************************
*
*  toc_begin_node():
*     wrapper for add_<...>node_to_toc()
*
*  Notes:
*     This function is called in UDO.C:pass1() to handle the various levels of
*        !begin_node
*        !begin_node*
*        !begin_pnode
*        !begin_pnode*
*     which do NOT indicate the chapter hierarchy in themselves, like the older
*     commands do, like e.g.
*        !node
*        !subnode
*        !subsubnode
*        !subsubsubnode
*        !subsubsubsubnode
*
*  Return:
*      TRUE: everything's fine
*     FALSE: error
*
******************************************|************************************/

GLOBAL _BOOL toc_begin_node(

const _BOOL   popup, 
const _BOOL   invisible)
{
   switch (p1_toctype)
   {
   case TOC_NONE:                         /* node type not known: */
      p1_toctype = TOC_NODE1;             /* start with node */
      break;
   
   default:                               /* known node type: */
      p1_toctype++;                       /* add sub chapter for this level */
   }

   return add_nodetype_to_toc(p1_toctype, popup, invisible);
}





/*******************************************************************************
*
*  toc_end_node():
*     decrease current node type 
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void toc_end_node(void)
{
   switch (p1_toctype)
   {
   case TOC_NODE1:
      p1_toctype = TOC_NONE;
      break;
   
   default:
      p1_toctype--;
   }
}





/*******************************************************************************
*
*  is_current_node():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL int is_current_node(

int   tocindex)  /* */
{
   return tocindex == p2_toc_counter;
}





/*******************************************************************************
*
*  get_toc_counter():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL int get_toc_counter(void)
{
   return p2_toc_counter;
}

/*
   ############################################################
   #
   #       Dateien mit den Jump-IDs ausgeben fuer C und Pascal
   #
   ############################################################
*/

/*******************************************************************************
*
*  save_the_alias():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL save_the_alias(

const char       *filename,  /* */
const char       *suffix,    /* */
tWinMapData      *data)      /* */
{
   register int   i;         /* */
   int            map;       /* */
   char           hid[256],  /* */
                  f[512];    /* */
   FILE          *file;      /* */
   
   
   strcpy(f, filename);
   strcat(f, suffix);

   file = fopen(f, "w");
   
   if (!file)
      return FALSE;

   if (file != NULL)
      setvbuf(file, NULL, _IOFBF, 8192);

   save_upr_entry_outfile(f);

   fprintf(file, "%s Alias-Datei for %s, made with UDO%s %s\n\n",
      data->remOn, 
      old_outfile.full, 
      UDO_REL, 
      data->remOff);

   for (i = 0; i <= p1_toc_counter; i++)
   {
      hid[0] = EOS;

      if (toc[i]->helpid!=NULL)
      {
         strcpy(hid, toc[i]->helpid);
      }
      else
      {
         if (use_auto_helpids)
         {
            node2WinAutoID(hid, toc[i]->name);
         }
      }

      map = -1;

      if (toc[i]->mapping >= 0)
         map = toc[i]->mapping;

      if (hid[0] != EOS || map >= 0 || desttype == TOWH4)
      {
         if (hid[0]==EOS)
         {
            node2NrWinhelp(hid, toc[i]->labindex);
         }

         strinsert(hid, sDocWinPrefixID);

         if (map < 0)
            map = 0x1000 + i;

         fprintf(file, "%-*s =%s%s ; %s\n",
            MAX_HELPID_LEN + 1,
            hid,
            toc[i]->filename,
            outfile.suff,
            toc[i]->name);
      }
   }

   fclose(file);

   return TRUE;    
}





/*******************************************************************************
*
*  save_htmlhelp_alias():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_htmlhelp_alias(void)
{
   tWinMapData   data;  /* */
   _BOOL       flag;  /* */
   
   
   memset(&data, 0, sizeof(data));
   strcpy(data.remOn,  "/*");
   strcpy(data.remOff, "*/");

   flag = save_the_alias(sMapNoSuff, ".hha", &data);

   return flag;
}





/*******************************************************************************
*
*  save_the_map():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL _BOOL save_the_map(

const char       *filename, 
const char       *suffix, 
tWinMapData      *data)
{
   register int   i;
   int            map;
   char           hid[256], 
                  f[512];
   FILE          *file;
   
   
   strcpy(f, filename);
   strcat(f, suffix);

   file = fopen(f, "w");
   
   if (!file)
   {
      return FALSE;
   }

   /* v6.9.10 [me] Einen Puffer zur Beschleunigung zuordnen */

   if (file != NULL)
      setvbuf(file, NULL, _IOFBF, 8192);

   save_upr_entry_outfile(f);

   fprintf(file, "%s mapping of %s for %s, made with UDO%s %s\n\n",
      data->remOn, 
      outfile.full, 
      data->compiler, 
      UDO_REL, 
      data->remOff);

   for (i = 0; i <= p1_toc_counter; i++)
   {
      hid[0] = EOS;

      if (toc[i]->helpid != NULL)
      {
         strcpy(hid, toc[i]->helpid);
      }
      else
      {
         if (use_auto_helpids)
         {
            node2WinAutoID(hid, toc[i]->name);
         }
      }

      map = -1;

      if (toc[i]->mapping >= 0)
      {
         map = toc[i]->mapping;
      }

      if (hid[0] != EOS || map >= 0 || desttype == TOWH4)
      {
         if (hid[0] == EOS)
         {
                                          /* V6.5.20 [CS] */
            node2WinAutoID(hid, toc[i]->name);
/* old:     node2NrWinhelp(hid, toc[i]->labindex);
*/
         }

         strinsert(hid, sDocWinPrefixID);

         if (map < 0)
            map = 0x1000 + i;

         /* V6.5.20 [CS]
            Fuer htmlhelp eine Datei mit C-Makros erzeugen, ueber welche 
            dann eine Map vom Titel auf den Knoten (html-Dateinamen) 
            gebildet werden kann.
            Z.B. X("Formatierung","004006.html")
         */

         fprintf(file, "X(\"%s\",\"%s%s\")\n",
            toc[i]->name,
            toc[i]->filename,
            outfile.suff);

/* old:
         fprintf(file, "%s %-*s%s\t%s%04X%s\t%s %s %s\n",
            data->cmd,
            MAX_HELPID_LEN + 1,
            hid,
            data->varOp,
            data->hexPre,
            map,
            data->hexSuf,
            data->remOn,
            toc[i]->name,
            data->remOff);
*/
      }  /* if (hid[0] != EOS || map >= 0 || desttype == TOWH4) */
      
   }  /* for (i = 0; i <= p1_toc_counter; i++) */

   fclose(file);

   return TRUE;    
}





/*******************************************************************************
*
*  save_htmlhelp_map():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_htmlhelp_map(void)
{
   tWinMapData   data;  /* */
   _BOOL       flag;  /* */
   
   
   memset(&data, 0, sizeof(data));
   strcpy(data.cmd, "#define");
   strcpy(data.hexPre, "0x");
   strcpy(data.remOn, "/*");
   strcpy(data.remOff, "*/");
   strcpy(data.compiler, "C");

   flag = save_the_map(sMapNoSuff, ".hhm", &data);

   return flag;
}





/*******************************************************************************
*
*  save_winhelp_map_c():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp_map_c(void)
{
   tWinMapData   data;  /* */
   _BOOL       flag;  /* */
   
   
   memset(&data, 0, sizeof(data));
   strcpy(data.cmd, "#define");
   strcpy(data.hexPre, "0x");
   strcpy(data.remOn, "/*");
   strcpy(data.remOff, "*/");
   strcpy(data.compiler, "C");

   flag = save_the_map(sMapNoSuff, ".hpc", &data);

   return flag;
}





/*******************************************************************************
*
*  save_winhelp_map_pas():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp_map_pas(void)
{
   tWinMapData   data;  /* */
   _BOOL       flag;  /* */
   
   
   memset(&data, 0, sizeof(data));
   strcpy(data.cmd, "const");
   strcpy(data.varOp, "=");
   strcpy(data.hexPre, "$");
   strcpy(data.hexSuf, ";");
   strcpy(data.remOn, "(*");
   strcpy(data.remOff, "*)");
   strcpy(data.compiler, "Pascal");

   flag = save_the_map(sMapNoSuff, ".hpp", &data);

   return flag;
}





/*******************************************************************************
*
*  save_winhelp_map_vb():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp_map_vb(void)
{
   tWinMapData   data;  /* */
   _BOOL       flag;  /* */
   
   
   memset(&data, 0, sizeof(data));
   strcpy(data.cmd, "Public Const");
   strcpy(data.varOp, "=");
   strcpy(data.hexPre, "&h");
   strcpy(data.hexSuf, "");
   strcpy(data.remOn, "'");
   strcpy(data.remOff, "");
   strcpy(data.compiler, "Visual Basic");

   flag = save_the_map(sMapNoSuff, ".hpb", &data);

   return flag;
}





/*******************************************************************************
*
*  save_winhelp_map_gfa():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp_map_gfa(void)
{
   tWinMapData   data;  /* */
   _BOOL       flag;  /* */
   
   
   memset(&data, 0, sizeof(data));
   strcpy(data.cmd, "Public Const");
   strcpy(data.varOp, "=");
   strcpy(data.hexPre, "&h");
   strcpy(data.hexSuf, "");
   strcpy(data.remOn, "'");
   strcpy(data.remOff, "");
   strcpy(data.compiler, "GFA-Basic");

   flag = save_the_map(sMapNoSuff, ".hpg", &data);

   return flag;
}







/*******************************************************************************
*
*  save_winhelp4_cnt():
*     ??? (description missing)
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL _BOOL save_winhelp4_cnt(void)
{
   FILE          *cntfile;                /* */
   register int   i;                      /* */
   int            li,                     /* */
                  apxstart;               /* */
   char           sName[512],             /* */
                  sMisc[512],             /* */
                  sID[128];               /* */
   _BOOL        n1HadChildren = FALSE;  /* */
   _BOOL        n2HadChildren = FALSE;  /* */
   _BOOL        n3HadChildren = FALSE;  /* */
   _BOOL        n4HadChildren = FALSE;  /* */
   _BOOL        n5HadChildren = FALSE;  /* */
   

   cntfile = myFwopen(file_lookup(sCntfull), FTCNT);

   if (cntfile == NULL)
      return FALSE;

   save_upr_entry_outfile(file_lookup(sCntfull));

   if (p1_toc_counter >= 0)
      goto DONE;

   
   fprintf(cntfile, ":Base %s.hlp>main\n", outfile.name);
   fprintf(cntfile, ":Index %s.hlp\n", outfile.name);

   strcpy(sMisc, titleprogram);
   recode_chrtab(sMisc,CHRTAB_ANSI);
   
   if (sMisc[0] != EOS)
   {
      fprintf(cntfile, ":Title %s\n", sMisc);
   }

   if (uses_tableofcontents)
   {
      node2NrWinhelp(sMisc, 0);
      fprintf(cntfile, "1 %s=%s\n", lang.contents, sMisc);
   }

   apxstart = 1;

   for (i = 1; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);

         if (toc[i]->appendix)
         {
            apxstart = i;              /* fuer unten merken */
            break;                     /* r5pl6: Es kann nur einen Anhang geben */
         }
         else if (toc[i]->n1 != 0)
         {
            li = toc[i]->labindex;
            node2NrWinhelp(sID, li);
               
            if (no_numbers)
               strcpy(sName, toc[i]->name);
            else
            {
               switch (toc[i]->toctype)
               {
               case TOC_NODE1:
                  sprintf(sName, "[%d] %s",
                        toc[i]->nr1 + toc_offset,
                        toc[i]->name);
                  break;
                  
               case TOC_NODE2:
                  sprintf(sName, "[%d.%d] %s",
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->name);
                  break;
                  
               case TOC_NODE3:
                  sprintf(sName, "[%d.%d.%d] %s",
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->name);
                  break;
                  
               case TOC_NODE4:
                  sprintf(sName, "[%d.%d.%d.%d] %s",
                     toc[i]->nr1 + toc_offset,
                     toc[i]->nr2 + subtoc_offset,
                     toc[i]->nr3 + subsubtoc_offset,
                     toc[i]->nr4 + subsubsubtoc_offset,
                     toc[i]->name);
                  break;
                  
               case TOC_NODE5:
                  sprintf(sName, "[%d.%d.%d.%d.%d] %s",
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        toc[i]->name);
                   break;
                   
               case TOC_NODE6:
                  sprintf(sName, "[%d.%d.%d.%d.%d,%d] %s",
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        toc[i]->nr6 + subsubsubsubsubtoc_offset,
                        toc[i]->name);
                   break;
                   
               }
            }
               
            recode_chrtab(sName,CHRTAB_ANSI);
            
            switch (toc[i]->toctype)
            {
            case TOC_NODE1:
               if (n1HadChildren || toc[i]->has_children)
               {
                  fprintf(cntfile, "1 %s\n", sName);
                  fprintf(cntfile, "2 %s=%s\n", sName, sID);
                  n1HadChildren = TRUE;
               }
               else
               {
                  fprintf(cntfile, "1 %s=%s\n", sName, sID);
               }

               n2HadChildren = FALSE;
               n3HadChildren = FALSE;
               n4HadChildren = FALSE;
               break;
            
            case TOC_NODE2:
               if (n2HadChildren || toc[i]->has_children)
               {
                  fprintf(cntfile, "2 %s\n", sName);
                  fprintf(cntfile, "3 %s=%s\n", sName, sID);
                  n2HadChildren = TRUE;
               }
               else
               {
                  fprintf(cntfile, "2 %s=%s\n", sName, sID);
               }

               n3HadChildren = FALSE;
               n4HadChildren = FALSE;
               break;
            
            case TOC_NODE3:
               if (n3HadChildren || toc[i]->has_children)
               {
                  fprintf(cntfile, "3 %s\n", sName);
                  fprintf(cntfile, "4 %s=%s\n", sName, sID);
                  n3HadChildren = TRUE;
               }
               else
               {
                  fprintf(cntfile, "3 %s=%s\n", sName, sID);
               }

               n4HadChildren = FALSE;
               break;
            
            case TOC_NODE4:
               if (n4HadChildren || toc[i]->has_children)
               {
                  fprintf(cntfile, "4 %s\n", sName);
                  fprintf(cntfile, "5 %s=%s\n", sName, sID);
                  n4HadChildren = TRUE;
               }
               else
               {
                  fprintf(cntfile, "4 %s=%s\n", sName, sID);
               }
               
               break;
            
            case TOC_NODE5:
               if (n5HadChildren || toc[i]->has_children)
               {
                  fprintf(cntfile, "5 %s\n", sName);
                  fprintf(cntfile, "6 %s=%s\n", sName, sID);
                  n4HadChildren = TRUE;
               }
               else
               {
                  fprintf(cntfile, "5 %s=%s\n", sName, sID);
               }
               
               break;
            
            case TOC_NODE6:
               fprintf(cntfile, "6 %s=%s\n", sName, sID);
               
            }  /* switch () */

         }  /* toc[i]->n1 > 0 */

      }  /* toc[i]!=NULL && !toc[i]->invisible */

   }  /* for */


   if (!apx_available)
      goto DONE;

   n1HadChildren = FALSE;
   n2HadChildren = FALSE;
   n3HadChildren = FALSE;
   n4HadChildren = FALSE;
   n5HadChildren = FALSE;

   fprintf(cntfile, "1 %s\n", lang.appendix);

   for (i = apxstart; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);

         if (toc[i]->appendix)
         {
            if (toc[i]->n1 != 0)
            {
               li = toc[i]->labindex;
               node2NrWinhelp(sID, li);
               
               if (no_numbers)
                  strcpy(sName, toc[i]->name);
               else
               {
                  switch (toc[i]->toctype)
                  {
                  case TOC_NODE1:
                     sprintf(sName, "[%c] %s",
                           'A' - 1 + toc[i]->nr1,
                           toc[i]->name);
                           break;
                           
                  case TOC_NODE2:
                     sprintf(sName, "[%c.%d] %s",
                           'A' - 1 + toc[i]->nr1,
                           toc[i]->nr2,
                           toc[i]->name);
                           break;
                           
                  case TOC_NODE3:
                     sprintf(sName, "[%c.%d.%d] %s",
                           'A' - 1 + toc[i]->nr1,
                           toc[i]->nr2,
                           toc[i]->nr3,
                           toc[i]->name);
                           break;
                           
                  case TOC_NODE4:
                     sprintf(sName, "[%c.%d.%d.%d] %s",
                           'A' - 1 + toc[i]->nr1,
                           toc[i]->nr2,
                           toc[i]->nr3,
                           toc[i]->nr4,
                           toc[i]->name);
                           break;
                           
                  case TOC_NODE5:
                     sprintf(sName, "[%c.%d.%d.%d.%d] %s",
                           'A' - 1 + toc[i]->nr1,
                           toc[i]->nr2,
                           toc[i]->nr3,
                           toc[i]->nr4,
                           toc[i]->nr5,
                           toc[i]->name);
                           break;

                  case TOC_NODE6:
                     sprintf(sName, "[%c.%d.%d.%d.%d.%d] %s",
                           'A' - 1 + toc[i]->nr1,
                           toc[i]->nr2,
                           toc[i]->nr3,
                           toc[i]->nr4,
                           toc[i]->nr5,
                           toc[i]->nr6,
                           toc[i]->name);
                  }
               }
               
               recode_chrtab(sName,CHRTAB_ANSI);
                  
               switch (toc[i]->toctype)
               {
               case TOC_NODE1:
                  if (n1HadChildren || toc[i]->has_children)
                  {
                     fprintf(cntfile, "2 %s\n", sName);
                     fprintf(cntfile, "3 %s=%s\n", sName, sID);
                     n1HadChildren = TRUE;
                  }
                  else
                  {
                     fprintf(cntfile, "2 %s=%s\n", sName, sID);
                  }

                  n2HadChildren = FALSE;
                  n3HadChildren = FALSE;
                  n4HadChildren = FALSE;
                  break;
               
               
               case TOC_NODE2:
                  if (n2HadChildren || toc[i]->has_children)
                  {
                     fprintf(cntfile, "3 %s\n", sName);
                     fprintf(cntfile, "4 %s=%s\n", sName, sID);
                     n2HadChildren = TRUE;
                  }
                  else
                  {
                     fprintf(cntfile, "3 %s=%s\n", sName, sID);
                  }

                  n3HadChildren = FALSE;
                  n4HadChildren = FALSE;
                  break;
               
               
               case TOC_NODE3:
                  if (n3HadChildren || toc[i]->has_children)
                  {
                     fprintf(cntfile, "4 %s\n", sName);
                     fprintf(cntfile, "5 %s=%s\n", sName, sID);
                     n3HadChildren = TRUE;
                  }
                  else
                  {
                     fprintf(cntfile, "4 %s=%s\n", sName, sID);
                  }
                  
                  n4HadChildren = FALSE;
                  break;
               
               
               case TOC_NODE4:
                  if (n4HadChildren || toc[i]->has_children)
                  {
                     fprintf(cntfile, "5 %s\n", sName);
                     fprintf(cntfile, "6 %s=%s\n", sName, sID);
                     n4HadChildren = TRUE;
                  }
                  else
                  {
                     fprintf(cntfile, "5 %s=%s\n", sName, sID);
                  }
                  
                  n5HadChildren = FALSE;
                  break;
               
               
               case TOC_NODE5:
                  if (n5HadChildren || toc[i]->has_children)
                  {
                     fprintf(cntfile, "6 %s\n", sName);
                     fprintf(cntfile, "7 %s=%s\n", sName, sID);
                     n5HadChildren = TRUE;
                  }
                  else
                  {
                     fprintf(cntfile, "6 %s=%s\n", sName, sID);
                  }
                  
                  break;


               case TOC_NODE6:
                  fprintf(cntfile, "7 %s=%s\n", sName, sID);

               }  /* switch () */

            }  /* toc[i]->n1 > 0 */

         }  /* !toc[i]->appendix */

      }  /* toc[i]!=NULL && !toc[i]->invisible */

   }  /* for */

DONE:
   fclose(cntfile);
   
   return TRUE;
}





/*******************************************************************************
*
*  init_toc_forms_numbers():
*     initialize format strings for tables of content
*
*  Notes:
*     This is required when the state of !no_numbers is known, i.e.
*     between pass1() and pass2().
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_toc_forms_numbers(void)
{
   switch (desttype)
   {
   case TOAQV:
   case TOWIN:
      strcpy(form_t1_n1, "\\li320\\fi-320\\tx320 %d\\tab{%s}\\par\\pard");
                                          /* 560 */
      strcpy(form_t1_n2, "\\li880\\fi-560\\tx880 %d.%d\\tab{%s}\\par\\pard");
                                          /* 920 */
      strcpy(form_t1_n3, "\\li1800\\fi-920\\tx1800 %d.%d.%d\\tab{%s}\\par\\pard");
                                          /*1000 */
      strcpy(form_t1_n4, "\\li2800\\fi-1000\\tx2800 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t1_n5, "\\li2800\\fi-1000\\tx2800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t1_n6, "\\li2800\\fi-1000\\tx2800 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t2_n2, "\\li480\\fi-480\\tx480 %d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n3, "\\li1400\\fi-920\\tx1400 %d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n4, "\\li2400\\fi-1000\\tx2400 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n5, "\\li2400\\fi-1000\\tx2400 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t2_n6, "\\li2400\\fi-1000\\tx2400 %.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t3_n3, "\\li880\\fi-880\\tx880 %d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t3_n4, "\\li1800\\fi-920\\tx1800 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t3_n5, "\\li1800\\fi-920\\tx1800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_t3_n6, "\\li1800\\fi-920\\tx1800 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_t4_n4, "\\li880\\fi-880\\tx880 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t4_n5, "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_t4_n6, "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_t5_n5, "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_t5_n6, "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_t6_n6, "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */

      strcpy(form_a1_n1, "\\li320\\fi-320\\tx320 %c\\tab{%s}\\par\\pard");
                                          /* 560 */
      strcpy(form_a1_n2, "\\li880\\fi-560\\tx880 %c.%d\\tab{%s}\\par\\pard");
                                          /* 920 */
      strcpy(form_a1_n3, "\\li1800\\fi-920\\tx1800 %c.%d.%d\\tab{%s}\\par\\pard");
                                          /*1000 */
      strcpy(form_a1_n4, "\\li2800\\fi-1000\\tx2800 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a1_n5, "\\li2800\\fi-1000\\tx2800 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a1_n6, "\\li2800\\fi-1000\\tx2800 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a2_n2, "\\li480\\fi-480\\tx480 %c.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n3, "\\li1400\\fi-920\\tx1400 %c.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n4, "\\li2400\\fi-1000\\tx2400 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n5, "\\li2400\\fi-1000\\tx2400 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a2_n6, "\\li2400\\fi-1000\\tx2400 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a3_n3, "\\li880\\fi-880\\tx880 %c.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a3_n4, "\\li1800\\fi-920\\tx1800 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a3_n5, "\\li1800\\fi-920\\tx1800 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a3_n6, "\\li1800\\fi-920\\tx1800 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a4_n4, "\\li880\\fi-880\\tx880 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a4_n5, "\\li880\\fi-880\\tx880 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a4_n6, "\\li880\\fi-880\\tx880 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a5_n5, "\\li880\\fi-880\\tx880 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a5_n6, "\\li880\\fi-880\\tx880 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a6_n6, "\\li880\\fi-880\\tx880 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      break;

   case TOWH4:
      strcpy(form_t1_n1, "\\li300\\fi-300\\tx300 %d\\tab{%s}\\par\\pard");
                                          /* 560 */
      strcpy(form_t1_n2, "\\li800\\fi-500\\tx800 %d.%d\\tab{%s}\\par\\pard");
                                          /* 920 */
      strcpy(form_t1_n3, "\\li1600\\fi-800\\tx1600 %d.%d.%d\\tab{%s}\\par\\pard");
                                          /*1000 */
      strcpy(form_t1_n4, "\\li2600\\fi-1000\\tx2600 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t1_n5, "\\li2600\\fi-1000\\tx2600 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t1_n6, "\\li2600\\fi-1000\\tx2600 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t2_n2, "\\li400\\fi-400\\tx400 %d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n3, "\\li1300\\fi-920\\tx1300 %d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n4, "\\li2200\\fi-1000\\tx2200 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n5, "\\li2200\\fi-1000\\tx2200 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t2_n6, "\\li2200\\fi-1000\\tx2200 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t3_n3, "\\li800\\fi-800\\tx800 %d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t3_n4, "\\li1600\\fi-920\\tx1600 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t3_n5, "\\li1600\\fi-920\\tx1600 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t3_n6, "\\li1600\\fi-920\\tx1600 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t4_n4, "\\li800\\fi-800\\tx800 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t4_n5, "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t4_n6, "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t5_n5, "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t5_n6, "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t6_n6, "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */

      strcpy(form_a1_n1, "\\li300\\fi-300\\tx300 %c\\tab{%s}\\par\\pard");
                                          /* 560 */
      strcpy(form_a1_n2, "\\li800\\fi-500\\tx800 %c.%d\\tab{%s}\\par\\pard");
                                          /* 920 */
      strcpy(form_a1_n3, "\\li1600\\fi-800\\tx1600 %c.%d.%d\\tab{%s}\\par\\pard");
                                          /*1000 */
      strcpy(form_a1_n4, "\\li2600\\fi-1000\\tx2600 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a1_n5, "\\li2600\\fi-1000\\tx2600 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a1_n6, "\\li2600\\fi-1000\\tx2600 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a2_n2, "\\li400\\fi-400\\tx400 %c.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n3, "\\li1300\\fi-920\\tx1300 %c.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n4, "\\li2200\\fi-1000\\tx2200 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n5, "\\li2200\\fi-1000\\tx2200 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a2_n6, "\\li2200\\fi-1000\\tx2200 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a3_n3, "\\li800\\fi-800\\tx800 %c.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a3_n4, "\\li1600\\fi-920\\tx1600 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a3_n5, "\\li1600\\fi-920\\tx1600 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a3_n6, "\\li1600\\fi-920\\tx1600 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a4_n4, "\\li800\\fi-800\\tx800 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a4_n5, "\\li800\\fi-800\\tx800 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a4_n6, "\\li800\\fi-800\\tx800 %c.%d%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a5_n5, "\\li800\\fi-800\\tx800 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a5_n6, "\\li800\\fi-800\\tx800 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a6_n6, "\\li800\\fi-800\\tx800 %c.%d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      break;
      

   case TOHAH:
   case TOHTM:
   case TOMHH:
      strcpy(form_t1_n1, "<li>%d %s");
      strcpy(form_t1_n2, "<li>%d.%d %s");
      strcpy(form_t1_n3, "<li>%d.%d.%d %s");
      strcpy(form_t1_n4, "<li>%d.%d.%d.%d %s");
      strcpy(form_t1_n5, "<li>%d.%d.%d.%d.%d %s");
      strcpy(form_t1_n6, "<li>%d.%d.%d.%d.%d.%d %s");
      strcpy(form_t2_n2, form_t1_n2);
      strcpy(form_t2_n3, form_t1_n3);
      strcpy(form_t2_n4, form_t1_n4);
      strcpy(form_t2_n5, form_t1_n5);
      strcpy(form_t2_n6, form_t1_n6);
      strcpy(form_t3_n3, form_t1_n3);
      strcpy(form_t3_n4, form_t1_n4);
      strcpy(form_t3_n5, form_t1_n5);
      strcpy(form_t3_n6, form_t1_n6);
      strcpy(form_t4_n4, form_t1_n4);
      strcpy(form_t4_n5, form_t1_n5);
      strcpy(form_t4_n6, form_t1_n6);
      strcpy(form_t5_n5, form_t1_n5);
      strcpy(form_t5_n6, form_t1_n6);
      strcpy(form_t6_n6, form_t1_n6);

      strcpy(form_a1_n1, "<li>%c %s");
      strcpy(form_a1_n2, "<li>%c.%d %s");
      strcpy(form_a1_n3, "<li>%c.%d.%d %s");
      strcpy(form_a1_n4, "<li>%c.%d.%d.%d %s");
      strcpy(form_a1_n5, "<li>%c.%d.%d.%d.%d %s");
      strcpy(form_a1_n6, "<li>%c.%d.%d.%d.%d.%d %s");
      strcpy(form_a2_n2, form_a1_n2);
      strcpy(form_a2_n3, form_a1_n3);
      strcpy(form_a2_n4, form_a1_n4);
      strcpy(form_a2_n5, form_a1_n5);
      strcpy(form_a2_n6, form_a1_n6);
      strcpy(form_a3_n3, form_a1_n3);
      strcpy(form_a3_n4, form_a1_n4);
      strcpy(form_a3_n5, form_a1_n5);
      strcpy(form_a3_n6, form_a1_n6);
      strcpy(form_a4_n4, form_a1_n4);
      strcpy(form_a4_n5, form_a1_n5);
      strcpy(form_a4_n6, form_a1_n6);
      strcpy(form_a5_n5, form_a1_n5);
      strcpy(form_a5_n6, form_a1_n6);
      strcpy(form_a6_n6, form_a1_n6);
      break;
      

   case TOTEX:
   case TOPDL:
      strcpy(form_t1_n1, "\\item %d %s");
      strcpy(form_t1_n2, "\\item %d.%d %s");
      strcpy(form_t1_n3, "\\item %d.%d.%d %s");
      strcpy(form_t1_n4, "\\item %d.%d.%d.%d %s");
      strcpy(form_t1_n5, "\\item %d.%d.%d.%d.%d %s");
      strcpy(form_t1_n6, "\\item %d.%d.%d.%d.%d.%d %s");
      strcpy(form_t2_n2, form_t1_n2);
      strcpy(form_t2_n3, form_t1_n3);
      strcpy(form_t2_n4, form_t1_n4);
      strcpy(form_t2_n5, form_t1_n5);
      strcpy(form_t2_n6, form_t1_n6);
      strcpy(form_t3_n3, form_t1_n3);
      strcpy(form_t3_n4, form_t1_n4);
      strcpy(form_t3_n5, form_t1_n5);
      strcpy(form_t3_n6, form_t1_n6);
      strcpy(form_t4_n4, form_t1_n4);
      strcpy(form_t4_n5, form_t1_n5);
      strcpy(form_t4_n6, form_t1_n6);
      strcpy(form_t5_n5, form_t1_n5);
      strcpy(form_t5_n6, form_t1_n6);
      strcpy(form_t6_n6, form_t1_n6);

      strcpy(form_a1_n1, "\\item %d %s");
      strcpy(form_a1_n2, "\\item %d.%d %s");
      strcpy(form_a1_n3, "\\item %d.%d.%d %s");
      strcpy(form_a1_n4, "\\item %d.%d.%d.%d %s");
      strcpy(form_a1_n5, "\\item %d.%d.%d.%d.%d %s");
      strcpy(form_a1_n6, "\\item %d.%d.%d.%d.%d.%d %s");
      strcpy(form_a2_n2, form_a1_n2);
      strcpy(form_a2_n3, form_a1_n3);
      strcpy(form_a2_n4, form_a1_n4);
      strcpy(form_a2_n5, form_a1_n5);
      strcpy(form_a2_n6, form_a1_n6);
      strcpy(form_a3_n3, form_a1_n3);
      strcpy(form_a3_n4, form_a1_n4);
      strcpy(form_a3_n5, form_a1_n5);
      strcpy(form_a3_n6, form_a1_n6);
      strcpy(form_a4_n4, form_a1_n4);
      strcpy(form_a4_n5, form_a1_n5);
      strcpy(form_a4_n6, form_a1_n6);
      strcpy(form_a5_n5, form_a1_n5);
      strcpy(form_a5_n6, form_a1_n6);
      strcpy(form_a6_n6, form_a1_n6);
      break;


                                          /* New in r6pl15 [NHz] */
   case TOKPS:
      strcpy(form_t1_n1, "(%2d ) udoshow %s newline");
      strcpy(form_t1_n2, "(   %2d.%d ) udoshow %s newline");
      strcpy(form_t1_n3, "(         %2d.%d.%d ) udoshow  %s newline");
      strcpy(form_t1_n4, "(               %2d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t1_n5, "(                     %2d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t1_n6, "(                           %2d.%d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t2_n2, "(%2d.%d ) udoshow %s newline");
      strcpy(form_t2_n3, "(      %2d.%d.%d ) udoshow %s newline");
      strcpy(form_t2_n4, "(            %2d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t2_n5, "(                  %2d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t2_n6, "(                        %2d.%d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t3_n3, "(%2d.%d.%d ) udoshow %s newline");
      strcpy(form_t3_n4, "(         %2d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t3_n5, "(              %2d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t3_n6, "(                   %2d.%d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t4_n4, "(%2d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t4_n5, "(     %2d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t4_n6, "(          %2d.%d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t5_n5, "(%2d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t5_n6, "(     %2d.%d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t6_n6, "(%2d.%d.%d.%d.%d.%d ) udoshow %s newline");

      strcpy(form_a1_n1, "( %c ) udoshow %s newline");
      strcpy(form_a1_n2, "(    %c.%d ) udoshow %s newline");
      strcpy(form_a1_n3, "(         %c.%d.%d ) udoshow  %s newline");
      strcpy(form_a1_n4, "(                 %c.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a1_n5, "(                     %c.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a1_n6, "(                         %c.%d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a2_n2, "( %c.%d ) udoshow %s newline");
      strcpy(form_a2_n3, "(      %c.%d.%d ) udoshow %s newline");
      strcpy(form_a2_n4, "(              %c.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a2_n5, "(                  %c.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a2_n6, "(                      %c.%d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a3_n3, "( %c.%d.%d ) udoshow %s newline");
      strcpy(form_a3_n4, "(         %c.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a3_n5, "(             %c.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a3_n6, "(                 %c.%d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a4_n4, "( %c.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a4_n5, "(     %c.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a4_n6, "(          %c.%d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a5_n5, "( %c.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a5_n6, "(     %c.%d.%d.%d.%d.%d ) udoshow %s newline");
      break;

/*
   case TOKPS:
      strcpy(form_t1_n1, "(%2d  %s) show newline");
      strcpy(form_t1_n2, "(   %2d.%d  %s) show newline");
      strcpy(form_t1_n3, "(        %2d.%d.%d  %s) show newline");
      strcpy(form_t1_n4, "(               %2d.%d.%d.%d  %s) show newline");
      strcpy(form_t2_n2, "(%2d.%d  %s) show newline");
      strcpy(form_t2_n3, "(     %2d.%d.%d  %s) show newline");
      strcpy(form_t2_n4, "(            %2d.%d.%d.%d  %s) show newline");
      strcpy(form_t3_n3, "(%2d.%d.%d  %s) show newline");
      strcpy(form_t3_n4, "(       %2d.%d.%d.%d  %s) show newline");
      strcpy(form_t4_n4, "(%2d.%d.%d.%d  %s) show newline");

      strcpy(form_a1_n1, "( %c  %s) show newline");
      strcpy(form_a1_n2, "(    %c.%d  %s) show newline");
      strcpy(form_a1_n3, "(         %c.%d.%d  %s) show newline");
      strcpy(form_a1_n4, "(                %c.%d.%d.%d  %s) show newline");
      strcpy(form_a2_n2, "( %c.%d  %s) show newline");
      strcpy(form_a2_n3, "(    %c.%d.%d  %s) show newline");
      strcpy(form_a2_n4, "(           %c.%d.%d.%d  %s) show newline");
      strcpy(form_a3_n3, "( %c.%d.%d  %s) show newline");
      strcpy(form_a3_n4, "(        %c.%d.%d.%d  %s) show newline");
      strcpy(form_a4_n4, "( %c.%d.%d.%d  %s) show newline");
      break;
*/

   default:
      strcpy(form_t1_n1, "%2d  %s");
      strcpy(form_t1_n2, "   %2d.%d  %s");
      strcpy(form_t1_n3, "        %2d.%d.%d  %s");
      strcpy(form_t1_n4, "               %2d.%d.%d.%d  %s");
      strcpy(form_t1_n5, "                      %2d.%d.%d.%d.%d  %s");
      strcpy(form_t1_n6, "                            %2d.%d.%d.%d.%d.%d  %s");
      strcpy(form_t2_n2, "%2d.%d  %s");
      strcpy(form_t2_n3, "     %2d.%d.%d  %s");
      strcpy(form_t2_n4, "            %2d.%d.%d.%d  %s");
      strcpy(form_t2_n5, "                   %2d.%d.%d.%d.%d  %s");
      strcpy(form_t2_n6, "                          %2d.%d.%d.%d.%d.%d  %s");
      strcpy(form_t3_n3, "%2d.%d.%d  %s");
      strcpy(form_t3_n4, "       %2d.%d.%d.%d  %s");
      strcpy(form_t3_n5, "              %2d.%d.%d.%d.%d  %s");
      strcpy(form_t3_n6, "                     %2d.%d.%d.%d.%d.%d  %s");
      strcpy(form_t4_n4, "%2d.%d.%d.%d  %s");
      strcpy(form_t4_n5, "       %2d.%d.%d.%d.%d  %s");
      strcpy(form_t4_n6, "              %2d.%d.%d.%d.%d.%d  %s");
      strcpy(form_t5_n5, "%2d.%d.%d.%d.%d  %s");
      strcpy(form_t5_n6, "       %2d.%d.%d.%d.%d.%d  %s");
      strcpy(form_t6_n6, "%2d.%d.%d.%d.%d.%d  %s");

      strcpy(form_a1_n1, " %c  %s");
      strcpy(form_a1_n2, "    %c.%d  %s");
      strcpy(form_a1_n3, "         %c.%d.%d  %s");
      strcpy(form_a1_n4, "                %c.%d.%d.%d  %s");
      strcpy(form_a1_n5, "                       %c.%d.%d.%d.%d  %s");
      strcpy(form_a1_n6, "                              %c.%d.%d.%d.%d.%d  %s");
      strcpy(form_a2_n2, " %c.%d  %s");
      strcpy(form_a2_n3, "    %c.%d.%d  %s");
      strcpy(form_a2_n4, "           %c.%d.%d.%d  %s");
      strcpy(form_a2_n5, "                  %c.%d.%d.%d.%d  %s");
      strcpy(form_a2_n6, "                         %c.%d.%d.%d.%d.%d  %s");
      strcpy(form_a3_n3, " %c.%d.%d  %s");
      strcpy(form_a3_n4, "        %c.%d.%d.%d  %s");
      strcpy(form_a3_n5, "               %c.%d.%d.%d.%d  %s");
      strcpy(form_a3_n6, "                      %c.%d.%d.%d.%d.%d  %s");
      strcpy(form_a4_n4, " %c.%d.%d.%d  %s");
      strcpy(form_a4_n5, "        %c.%d.%d.%d.%d  %s");
      strcpy(form_a4_n6, "                %c.%d.%d.%d.%d.%d  %s");
      strcpy(form_a5_n5, "%c.%d.%d.%d.%d  %s");
      strcpy(form_a5_n6, "       %c.%d.%d.%d.%d.%d  %s");
      strcpy(form_a6_n6, "%c.%d.%d.%d.%d.%d  %s");
   }
}




/*******************************************************************************
*
*  init_toc_forms_no_numbers():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_toc_forms_no_numbers(void)
{
   char   s[32];  /* */

   switch (desttype)
   {
   case TOAQV:
   case TOWIN:
   case TOWH4:
      strcpy(form_t1_n1, "{%s}\\par\\pard");
      strcpy(form_t1_n2, "\\li560{%s}\\par\\pard");
      strcpy(form_t1_n3, "\\li1120{%s}\\par\\pard");
      strcpy(form_t1_n4, "\\li1680{%s}\\par\\pard");
      strcpy(form_t1_n5, "\\li1680{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t1_n6, "\\li1680{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t2_n2, "{%s}\\par\\pard");
      strcpy(form_t2_n3, "\\li560{%s}\\par\\pard");
      strcpy(form_t2_n4, "\\li1120{%s}\\par\\pard");
      strcpy(form_t2_n5, "\\li1120{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t2_n6, "\\li1120{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t3_n3, "{%s}\\par\\pard");
      strcpy(form_t3_n4, "\\li560{%s}\\par\\pard");
      strcpy(form_t3_n5, "\\li560{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t3_n6, "\\li560{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t4_n4, "{%s}\\par\\pard");
      strcpy(form_t4_n5, "{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t4_n6, "{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t5_n5, "{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t5_n6, "{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t6_n6, "{%s}\\par\\pard"); /* ToDo: ??? */

      strcpy(form_a1_n1, form_t1_n1);
      strcpy(form_a1_n2, form_t1_n2);
      strcpy(form_a1_n3, form_t1_n3);
      strcpy(form_a1_n4, form_t1_n4);
      strcpy(form_a1_n5, form_t1_n5);
      strcpy(form_a1_n6, form_t1_n6);
      strcpy(form_a2_n2, form_t2_n2);
      strcpy(form_a2_n3, form_t2_n3);
      strcpy(form_a2_n4, form_t2_n4);
      strcpy(form_a2_n5, form_t2_n5);
      strcpy(form_a2_n6, form_t2_n6);
      strcpy(form_a3_n3, form_t3_n3);
      strcpy(form_a3_n4, form_t3_n4);
      strcpy(form_a3_n5, form_t3_n5);
      strcpy(form_a3_n6, form_t3_n6);
      strcpy(form_a4_n4, form_t4_n4);
      strcpy(form_a4_n5, form_t4_n5);
      strcpy(form_a4_n6, form_t4_n6);
      strcpy(form_a5_n5, form_t5_n5);
      strcpy(form_a5_n6, form_t5_n6);
      strcpy(form_a6_n6, form_t6_n6);
      break;
      

   case TOHAH:
   case TOHTM:
   case TOMHH:
      strcpy(s, "<li>%s");

      strcpy(form_t1_n1, s);
      strcpy(form_t1_n2, s);
      strcpy(form_t1_n3, s);
      strcpy(form_t1_n4, s);
      strcpy(form_t1_n5, s);
      strcpy(form_t1_n6, s);
      strcpy(form_t2_n2, s);
      strcpy(form_t2_n3, s);
      strcpy(form_t2_n4, s);
      strcpy(form_t2_n5, s);
      strcpy(form_t2_n6, s);
      strcpy(form_t3_n3, s);
      strcpy(form_t3_n4, s);
      strcpy(form_t3_n5, s);
      strcpy(form_t3_n6, s);
      strcpy(form_t4_n4, s);
      strcpy(form_t4_n5, s);
      strcpy(form_t4_n6, s);
      strcpy(form_t5_n5, s);
      strcpy(form_t5_n6, s);
      strcpy(form_t6_n6, s);

      strcpy(form_a1_n1, s);
      strcpy(form_a1_n2, s);
      strcpy(form_a1_n3, s);
      strcpy(form_a1_n4, s);
      strcpy(form_a1_n5, s);
      strcpy(form_a1_n6, s);
      strcpy(form_a2_n2, s);
      strcpy(form_a2_n3, s);
      strcpy(form_a2_n4, s);
      strcpy(form_a2_n5, s);
      strcpy(form_a2_n6, s);
      strcpy(form_a3_n3, s);
      strcpy(form_a3_n4, s);
      strcpy(form_a3_n5, s);
      strcpy(form_a3_n6, s);
      strcpy(form_a4_n4, s);
      strcpy(form_a4_n5, s);
      strcpy(form_a4_n6, s);
      strcpy(form_a5_n5, s);
      strcpy(form_a5_n6, s);
      strcpy(form_a6_n6, s);
      break;
      

   case TOTEX:
   case TOPDL:
      strcpy(s, "\\item %s");

      strcpy(form_t1_n1, s);
      strcpy(form_t1_n2, s);
      strcpy(form_t1_n3, s);
      strcpy(form_t1_n4, s);
      strcpy(form_t1_n5, s);
      strcpy(form_t1_n6, s);
      strcpy(form_t2_n2, s);
      strcpy(form_t2_n3, s);
      strcpy(form_t2_n4, s);
      strcpy(form_t2_n5, s);
      strcpy(form_t2_n6, s);
      strcpy(form_t3_n3, s);
      strcpy(form_t3_n4, s);
      strcpy(form_t3_n5, s);
      strcpy(form_t3_n6, s);
      strcpy(form_t4_n4, s);
      strcpy(form_t4_n5, s);
      strcpy(form_t4_n6, s);
      strcpy(form_t5_n5, s);
      strcpy(form_t5_n6, s);
      strcpy(form_t6_n6, s);

      strcpy(form_a1_n1, s);
      strcpy(form_a1_n2, s);
      strcpy(form_a1_n3, s);
      strcpy(form_a1_n4, s);
      strcpy(form_a1_n5, s);
      strcpy(form_a1_n6, s);
      strcpy(form_a2_n2, s);
      strcpy(form_a2_n3, s);
      strcpy(form_a2_n4, s);
      strcpy(form_a2_n5, s);
      strcpy(form_a2_n6, s);
      strcpy(form_a3_n3, s);
      strcpy(form_a3_n4, s);
      strcpy(form_a3_n5, s);
      strcpy(form_a3_n6, s);
      strcpy(form_a4_n4, s);
      strcpy(form_a4_n5, s);
      strcpy(form_a4_n6, s);
      strcpy(form_a5_n5, s);
      strcpy(form_a5_n6, s);
      strcpy(form_a6_n6, s);
      break;
      

   case TOINF:
      strcpy(s, "%s");

      strcpy(form_t1_n1, s);
      strcpy(form_t1_n2, s);
      strcpy(form_t1_n3, s);
      strcpy(form_t1_n4, s);
      strcpy(form_t1_n5, s);
      strcpy(form_t1_n6, s);
      strcpy(form_t2_n2, s);
      strcpy(form_t2_n3, s);
      strcpy(form_t2_n4, s);
      strcpy(form_t2_n5, s);
      strcpy(form_t2_n6, s);
      strcpy(form_t3_n3, s);
      strcpy(form_t3_n4, s);
      strcpy(form_t3_n5, s);
      strcpy(form_t3_n6, s);
      strcpy(form_t4_n4, s);
      strcpy(form_t4_n5, s);
      strcpy(form_t4_n6, s);
      strcpy(form_t5_n5, s);
      strcpy(form_t5_n6, s);
      strcpy(form_t6_n6, s);

      strcpy(form_a1_n1, s);
      strcpy(form_a1_n2, s);
      strcpy(form_a1_n3, s);
      strcpy(form_a1_n4, s);
      strcpy(form_a1_n5, s);
      strcpy(form_a1_n6, s);
      strcpy(form_a2_n2, s);
      strcpy(form_a2_n3, s);
      strcpy(form_a2_n4, s);
      strcpy(form_a2_n5, s);
      strcpy(form_a2_n6, s);
      strcpy(form_a3_n3, s);
      strcpy(form_a3_n4, s);
      strcpy(form_a3_n5, s);
      strcpy(form_a3_n6, s);
      strcpy(form_a4_n4, s);
      strcpy(form_a4_n5, s);
      strcpy(form_a4_n6, s);
      strcpy(form_a5_n5, s);
      strcpy(form_a5_n6, s);
      strcpy(form_a6_n6, s);
      break;
      

                                          /* New in r6pl15 [NHz] */
   case TOKPS:
      strcpy(form_t1_n1, " %s newline");
      strcpy(form_t1_n2, "    %s newline");
      strcpy(form_t1_n3, "       %s newline");
      strcpy(form_t1_n4, "          %s newline");
      strcpy(form_t1_n5, "             %s newline");
      strcpy(form_t1_n6, "                %s newline");
      strcpy(form_t2_n2, " %s newline");
      strcpy(form_t2_n3, "    %s newline");
      strcpy(form_t2_n4, "       %s newline");
      strcpy(form_t2_n5, "          %s newline");
      strcpy(form_t2_n6, "             %s newline");
      strcpy(form_t3_n3, " %s newline");
      strcpy(form_t3_n4, "    %s newline");
      strcpy(form_t3_n5, "      %s newline");
      strcpy(form_t3_n6, "         %s newline");
      strcpy(form_t4_n4, " %s newline");
      strcpy(form_t4_n5, "   %s newline");
      strcpy(form_t4_n6, "     %s newline");
      strcpy(form_t5_n5, " %s newline");
      strcpy(form_t5_n6, "   %s newline");
      strcpy(form_t6_n6, "%s newline");

      strcpy(form_a1_n1, " %s newline");
      strcpy(form_a1_n2, "    %s newline");
      strcpy(form_a1_n3, "       %s newline");
      strcpy(form_a1_n4, "          %s newline");
      strcpy(form_a1_n5, "             %s newline");
      strcpy(form_a1_n6, "                %s newline");
      strcpy(form_a2_n2, " %s newline");
      strcpy(form_a2_n3, "    %s newline");
      strcpy(form_a2_n4, "       %s newline");
      strcpy(form_a2_n5, "          %s newline");
      strcpy(form_a2_n6, "             %s newline");
      strcpy(form_a3_n3, " %s newline");
      strcpy(form_a3_n4, "    %s newline");
      strcpy(form_a3_n5, "       %s newline");
      strcpy(form_a3_n6, "          %s newline");
      strcpy(form_a4_n4, " %s newline");
      strcpy(form_a4_n5, "    %s newline");
      strcpy(form_a4_n6, "       %s newline");
      strcpy(form_a5_n5, " %s newline");
      strcpy(form_a5_n6, "    %s newline");
      strcpy(form_a6_n6, "%s newline");
      break;
      

   default:
      strcpy(form_t1_n1, " %s");
      strcpy(form_t1_n2, "    %s");
      strcpy(form_t1_n3, "       %s");
      strcpy(form_t1_n4, "          %s");
      strcpy(form_t1_n5, "             %s");
      strcpy(form_t1_n6, "                %s");
      strcpy(form_t2_n2, " %s");
      strcpy(form_t2_n3, "    %s");
      strcpy(form_t2_n4, "       %s");
      strcpy(form_t2_n5, "          %s");
      strcpy(form_t2_n6, "             %s");
      strcpy(form_t3_n3, " %s");
      strcpy(form_t3_n4, "    %s");
      strcpy(form_t3_n5, "       %s");
      strcpy(form_t3_n6, "          %s");
      strcpy(form_t4_n4, " %s");
      strcpy(form_t4_n5, "    %s");
      strcpy(form_t4_n6, "       %s");
      strcpy(form_t5_n5, " %s");
      strcpy(form_t5_n6, "    %s");
      strcpy(form_t6_n6, "%s");

      strcpy(form_a1_n1, " %s");
      strcpy(form_a1_n2, "    %s");
      strcpy(form_a1_n3, "       %s");
      strcpy(form_a1_n4, "          %s");
      strcpy(form_a1_n5, "             %s");
      strcpy(form_a1_n6, "                %s");
      strcpy(form_a2_n2, " %s");
      strcpy(form_a2_n3, "    %s");
      strcpy(form_a2_n4, "       %s");
      strcpy(form_a2_n5, "          %s");
      strcpy(form_a2_n6, "             %s");
      strcpy(form_a3_n3, " %s");
      strcpy(form_a3_n4, "    %s");
      strcpy(form_a3_n5, "       %s");
      strcpy(form_a3_n6, "          %s");
      strcpy(form_a4_n4, " %s");
      strcpy(form_a4_n5, "    %s");
      strcpy(form_a4_n6, "       %s");
      strcpy(form_a5_n5, " %s");
      strcpy(form_a5_n6, "    %s");
      strcpy(form_a6_n6, " %s");
   }
}





/*******************************************************************************
*
*  init_module_toc_pass2():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_toc_pass2(void)
{
   char   sF[128],  /* */
          sS[128];  /* */
   
   
   form_t1_n1[0] = EOS;
   form_t1_n2[0] = EOS;
   form_t1_n3[0] = EOS;
   
   form_t2_n2[0] = EOS;
   form_t2_n3[0] = EOS;
   
   form_t3_n3[0] = EOS;
   

   form_a1_n1[0] = EOS;
   form_a1_n2[0] = EOS;
   form_a1_n3[0] = EOS;

   form_a2_n2[0] = EOS;
   form_a2_n3[0] = EOS;

   form_a3_n3[0] = EOS;
   

   if (no_numbers)
      init_toc_forms_no_numbers();
   else
      init_toc_forms_numbers();


   /*r6pl5: die Reinkarnation von !use_compressed_tocs */
   
   if (use_compressed_tocs)
   {
      subtocs1_depth = 1;
      subtocs2_depth = 1;
      subtocs3_depth = 1;
      subtocs4_depth = 1;
      subtocs5_depth = 1;
   }

   if (subtocs1_depth <= 0 || subtocs1_depth > 9)
      subtocs1_depth = 4;

   if (subtocs2_depth <= 0 || subtocs2_depth > 9)
      subtocs2_depth = 3;

   if (subtocs3_depth <= 0 || subtocs3_depth > 9)
      subtocs3_depth = 2;

   if (subtocs4_depth <= 0 || subtocs4_depth > 9)
       subtocs4_depth = 1;

   if (subtocs5_depth <= 0 || subtocs5_depth > 9)
       subtocs5_depth = 1;

   /* Die Formatkommando angeben, die fuer die Inhaltsausgabe */
   /* verwendet werden, um die Einrueckungen der Listen zu erzeugen */

   switch (desttype)                      /* r6pl2 */
   {
   case TOHAH:
   case TOHTM:
   case TOMHH:
                                          /* Changed in r6pl16 [NHz] */
      strcpy(toc_list_top, "<ul class=\"content\">");
      strcpy(toc_list_end, "</ul>");
      
      use_toc_list_commands = TOCL_HTM;
      break;
      
      
   case TOTEX:
   case TOPDL:
      strcpy(toc_list_top, "\\begin{itemize}\n\\itemsep 0pt\n\\parsep 0pt\n\\parskip 0pt");
      strcpy(toc_list_end, "\\end{itemize}");
      
      use_toc_list_commands = TOCL_TEX;
      break;
      
      
   default:
      toc_list_top[0] = EOS;
      toc_list_end[0] = EOS;
      
      use_toc_list_commands = 0;
   }

   if (html_frames_layout)
      sprintf(html_target, " target=\"%s\"", FRAME_NAME_CON);
   else
      html_target[0] = EOS;


   /* Font-Tags vorbestimmen */

   sF[0] = 0;
   sS[0] = 0;
   
   sHtmlPropfontStart[0] = EOS;
   sHtmlPropfontEnd[0]   = EOS;
   iDocHtmlPropfontSize  = 0;

   if (sDocHtmlPropfontName[0] != EOS)
   {
      sprintf(sF, " face=\"%s\"", sDocHtmlPropfontName);
   }
   
   if (sDocHtmlPropfontSize[0] != EOS)
   {
      sprintf(sS, " size=\"%s\"", sDocHtmlPropfontSize);
      iDocHtmlPropfontSize= atoi(sDocHtmlPropfontSize);
   }

   if (sF[0] != EOS || sS[0] != EOS)
   {
      sprintf(sHtmlPropfontStart, "<font%s%s>", sF, sS);
      strcpy(sHtmlPropfontEnd, "</font>");
   }

   sF[0] = 0;
   sS[0] = 0;
   
   sHtmlMonofontStart[0] = EOS;
   sHtmlMonofontEnd[0]   = EOS;
   iDocHtmlMonofontSize  = 0;

   if (sDocHtmlMonofontName[0] != EOS)
   {
      sprintf(sF, " face=\"%s\"", sDocHtmlMonofontName);
   }
   
   if (sDocHtmlMonofontSize[0] != EOS)
   {
      sprintf(sS, " size=\"%s\"", sDocHtmlMonofontSize);
      iDocHtmlMonofontSize= atoi(sDocHtmlMonofontSize);
   }

   if (sF[0] != EOS || sS[0] != EOS)
   {
      sprintf(sHtmlMonofontStart, "<font%s%s>", sF, sS);
      strcpy(sHtmlMonofontEnd, "</font>");
   }
}





/*******************************************************************************
*
*  check_module_toc_pass1():
*     ??? (description missing)
*
*  Return:
*      TRUE: check was OK
*     FALSE: an issue has been found
*
******************************************|************************************/

GLOBAL _BOOL check_module_toc_pass1(void)
{
   int       i,            /* counter */
             j;            /* cunter */
   char      s[512],       /* */
             sTyp[32],     /* */
             sNode[256];   /* */
   _BOOL   ret = TRUE;   /* */
   _BOOL   checkString;  /* */


   /* --- Schauen, ob bei Hypertextformaten Dinge eindeutig benutzt werden --- */

   switch (desttype)
   {
   case TOHAH:
   case TOHTM:
   case TOMHH:
   case TOWIN:
   case TOWH4:
   case TOPCH:
   case TOSTG:
   case TOAMG:
   case TOTEX:
   case TOPDL:
      show_status_info(_("Checking nodes, labels and aliases..."));
      
      for (i = 1; i <= p1_lab_counter; i++)
      {
         for (j = i + 1; j <= p1_lab_counter; j++)
         {
            if (strcmp(lab[i]->name, lab[j]->name) == 0)
            {
               error_message(_("label \"%s\" used twice"), lab[i]->name);

               sNode[0] = EOS;
               strcpy(sTyp, _("as a label"));
               
               if (lab[i]->is_node)
                  strcpy(sTyp, _("as a node"));
               
               if (lab[i]->is_alias)
                  strcpy(sTyp, _("as an alias"));

               if (!lab[i]->is_node)
                  sprintf(sNode, _(" in node '%s'"), toc[lab[i]->tocindex]->name);
               
               sprintf(s, "1. %s%s", sTyp, sNode);
               note_message(s);

               sNode[0] = EOS;
               strcpy(sTyp, _("as a label"));

               if (lab[j]->is_node)
                  strcpy(sTyp, _("as a node"));

               if (lab[j]->is_alias)
                  strcpy(sTyp, _("as an alias"));

               if (!lab[j]->is_node)
                  sprintf(sNode, _(" in node '%s'"), toc[lab[j]->tocindex]->name);

               sprintf(s, "2. %s%s", sTyp, sNode);
               note_message(s);

               ret = FALSE;
            }
         }
      }
   }

   /* --- Doppelt vergebene HTML-Dateinamen testen, dabei das Mergen non Nodes beachten --- */
   /* Werden Nodes in einer Datei vereint, dann besitzen die unteren Ebenen den */
   /* gleichen Dateinamen wie die obere Ebene! r6pl13 */

   switch (desttype)
   {
   case TOHAH:
   case TOHTM:
   case TOMHH:
      if (!html_merge_node1)
      {
         show_status_info(_("Checking HTML file names..."));

         for (i = 0; i < p1_toc_counter; i++)
         {
            for (j = i + 1; j < p1_toc_counter; j++)
            {
               checkString = FALSE;

               if (html_merge_node6)
               {
                  checkString = (    (toc[i]->n1 != toc[j]->n1)
                                  || (toc[i]->n2 != toc[j]->n2)
                                  || (toc[i]->n3 != toc[j]->n3)
                                  || (toc[i]->n4 != toc[j]->n4)
                                  || (toc[i]->n5 != toc[j]->n5) );
               }

               if (html_merge_node5)
               {
                  checkString = (    (toc[i]->n1 != toc[j]->n1)
                                  || (toc[i]->n2 != toc[j]->n2)
                                  || (toc[i]->n3 != toc[j]->n3)
                                  || (toc[i]->n4 != toc[j]->n4) );
               }

               if (html_merge_node4)
               {
                  checkString = (    (toc[i]->n1 != toc[j]->n1)
                                  || (toc[i]->n2 != toc[j]->n2)
                                  || (toc[i]->n3 != toc[j]->n3) );
               }

               if (html_merge_node3)
               {
                  checkString = (    (toc[i]->n1 != toc[j]->n1)
                                  || (toc[i]->n2 != toc[j]->n2) );
               }

               if (html_merge_node2)
               {
                  checkString = (toc[i]->n1 != toc[j]->n1);
               }


               if (checkString && strcmp(toc[i]->filename, toc[j]->filename) == 0)
               {
                  error_message(_("file name \"%s\" used in \"%s\" and \"%s\""),
                     toc[i]->filename,
                     toc[i]->name,
                     toc[j]->name);

                  ret = FALSE;
               }
            }
         }
      }
   }

   return ret;
}





/*******************************************************************************
*
*  check_module_toc_pass2():
*     pass 2 check: see if labels or aliases have been (auto-)referenced
*
*  Return:
*     TRUE
*
******************************************|************************************/

GLOBAL _BOOL check_module_toc_pass2(void)
{
   int    i;       /* counter */
   
   show_status_info("");
   show_status_info(_("Checking usage of labels and aliases..."));
   
   for (i = 1; i < p1_lab_counter; i++)
   {
      if (!lab[i]->referenced)
      {
         if (!lab[i]->is_node)
         {
            note_message(_("label/alias '%s' in node '%s' wasn't referenced"),
               lab[i]->name,
               toc[lab[i]->tocindex]->name);
         }
      }
   }
   
   return TRUE;
}





/*******************************************************************************
*
*  init_module_toc():
*     initialize TOC module
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL void init_module_toc(void)
{
   register int   i;  /* */


   /* -------------------------------------------------------------- */
   /* In diesen Flags merkt sich UDO, welche Art von Node gerade     */
   /* aktiv ist (!node, !subnode, etc.)                              */
   /* -------------------------------------------------------------- */
   
   active_nodetype = TOC_NONE;


   /* -------------------------------------------------------------- */
   /* toc_offset enthaelt einen Offset fuer die Kapitelnumerierung   */
   /* Das erste Kapitel erhaelt dann die Nummer (1 + toc_offset)     */
   /* toc_offset kann auch negativ werden.                           */
   /* Die anderen Offsets entsprechend                               */
   /* -------------------------------------------------------------- */
   
   toc_offset             = 0;
   subtoc_offset          = 0;
   subsubtoc_offset       = 0;
   subsubsubtoc_offset    = 0;
   subsubsubsubtoc_offset = 0;            /* [GS] */
   subsubsubsubsubtoc_offset = 0;


   /* -------------------------------------------------------------- */
   /* Zeiger auf den aktuellen Node, Subnode und Subsubnode          */
   /* Mit diesen Variablen kann man toc[] direkt adressieren         */
   /* -------------------------------------------------------------- */
   
   curr_n1_index = 0;
   curr_n2_index = 0;
   curr_n3_index = 0;
   curr_n4_index = 0;                     /* [GS] */
   curr_n5_index = 0;
   curr_n6_index = 0;


   /* -------------------------------------------------------------- */
   /* Wenn auch nur ein Node existiert, dann kann ein !toc           */
   /* ausgegeben werden. toc_available wird dann TRUE                */
   /* -------------------------------------------------------------- */
   
   toc_available = FALSE;
   apx_available = FALSE;


   /* -------------------------------------------------------------- */
   /* Hier werden die absoluten Kapitelnummern vermerkt. Diese       */
   /* Nummern weichen von den Nummern in den Inhaltsverzeichnissen   */
   /* ab, falls unsichtbare Nodes (!node*) benutzt werden.           */
   /* Beispiele:                                                     */
   /* 1  Node:        n1=1, n2=0, n3=0, n4=0                         */
   /* 1.2  Node:      n1=1, n2=2, n3=0, n4=0                         */
   /* 1.2.3  Node:    n1=1, n2=2, n3=3, n4=0                         */
   /* 1.2.3.4  Node:  n1=1, n2=2, n3=3, n4=4                         */
   /* -------------------------------------------------------------- */
   
   p1_toc_n1 = 0;
   p1_toc_n2 = 0;
   p1_toc_n3 = 0;
   p1_toc_n4 = 0;
   p1_toc_n5 = 0;
   p1_toc_n6 = 0;
   
   p2_toc_n1 = 0;
   p2_toc_n2 = 0;
   p2_toc_n3 = 0;
   p2_toc_n4 = 0;
   p2_toc_n5 = 0;
   p2_toc_n6 = 0;
   
   p1_apx_n1 = 0;
   p1_apx_n2 = 0;
   p1_apx_n3 = 0;
   p1_apx_n4 = 0;
   p1_apx_n5 = 0;
   p1_apx_n6 = 0;

   p2_apx_n1 = 0;
   p2_apx_n2 = 0;
   p2_apx_n3 = 0;
   p2_apx_n4 = 0;
   p2_apx_n5 = 0;
   p2_apx_n6 = 0;


   /* -------------------------------------------------------------- */
   /* Hier nun die Nummern, wie sie im Inhaltsverzeichis erscheinen  */
   /* -------------------------------------------------------------- */
   
   p1_toc_nr1 = 0;
   p1_toc_nr2 = 0;
   p1_toc_nr3 = 0;
   p1_toc_nr4 = 0;
   p1_toc_nr5 = 0;
   p1_toc_nr6 = 0;
   
   p1_apx_nr1 = 0;
   p1_apx_nr2 = 0;
   p1_apx_nr3 = 0;
   p1_apx_nr4 = 0;
   p1_apx_nr5 = 0;
   p1_apx_nr6 = 0;


   /* -------------------------------------------------------------- */
   /* In diesen Variablen werden die Indizes der letzten Kapitel     */
   /* gesichert. Sie sind sehr wichtig, um die Links zu den          */
   /* uebergeordneten Kapiteln in Hypertexten ohne lange Sucherei    */
   /* erstellen zu koennen.                                          */
   /* -------------------------------------------------------------- */
   
   last_n1_index = 0;
   last_n2_index = 0;
   last_n3_index = 0;
   last_n4_index = 0;
   last_n5_index = 0;                     /* [GS] */
   last_n6_index = 0;


   /* -------------------------------------------------------------- */
   /* Dieses Flag wird TRUE gesetzt, wenn das Inhaltsverzeichnis     */
   /* mit !tableofcontents aufgerufen wird. Nodes koenne dann auf    */
   /* dieses Inhaltsverzeichnis verweisen (z.B: ST-Guide per @toc)   */
   /* -------------------------------------------------------------- */
   
   called_tableofcontents = FALSE;


   /* -------------------------------------------------------------- */
   /* Dieses Flag wird TRUE gesetzt, wenn die vierte Gliederungs-    */
   /* Ebene benutzt wird. In der LaTeX-Preambel mussen dann einige   */
   /* Befehle zusaetzlich ausgegeben werden.                         */
   /* -------------------------------------------------------------- */
   
   called_subsubsubsubsubnode = FALSE;       /* [GS] */


   /* -------------------------------------------------------------- */
   /* Eintraege fuer das toc[]-Array. Nach pass1() enthaelt          */
   /* toc[p1_toc_counter] die Daten des letzten Kapitels.            */
   /* p2_toc_counter ist entsprechend ein Zaehler fuer den pass2().  */
   /* Waehren pass2() zeigt p2_toc_counter auf den aktuellen Eintrag */
   /* des toc[]-Arrays.                                              */
   /* -------------------------------------------------------------- */
   
   p1_toc_counter = 0;
   p2_toc_counter = 0;      


   /* -------------------------------------------------------------- */
   /* toc[]-Array ausnullen und Inhaltsverzeichnis "eintragen"       */
   /* -------------------------------------------------------------- */

   for (i = 0; i < MAXTOCS; i++)
      toc[i] = NULL;

   add_toc_to_toc();                      /* r5pl6 */


   /* -------------------------------------------------------------- */
   /* lab[]-Array mit den Daten der referenzierbaren Stellen des     */
   /* Dokumentes ausnullen und Zaehler zuruecksetzen.                */
   /* -------------------------------------------------------------- */

   for (i = 0; i < MAXLABELS; i++)
      lab[i] = NULL;
      
   p1_lab_counter = 0;
   p2_lab_counter = 0;


   /* -------------------------------------------------------------- */
   /* Kapitelzaehler zuruecksetzen                                   */
   /* -------------------------------------------------------------- */

   all_nodes             = 0;             /* r5pl7 */
   all_subnodes          = 0;
   all_subsubnodes       = 0;
   all_subsubsubnodes    = 0;
   all_subsubsubsubnodes = 0;             /* [GS] */
   all_subsubsubsubsubnodes = 0;


   /* -------------------------------------------------------------- */
   /* Die Zeichen setzen, die beim Referenzieren vor und nach einem  */
   /* gefundenen Label erlaubt sind.                                 */
   /* -------------------------------------------------------------- */

   sprintf(allowed_next_chars, "\033 !\"#$%%&'()*+,-./:;<=>?@[\\]^_`{|}~%c%c%c", TILDE_C, NBSP_C, INDENT_C);
   
   strcpy(allowed_prev_chars, allowed_next_chars);


   uses_tableofcontents = FALSE;
   toc_title[0] = EOS;

   current_chapter_name[0] = EOS;         /* r5pl16 */
   current_chapter_nr[0]   = EOS;         /* r5pl16 */

   footer_buffer[0] = EOS;                /* r6pl2 */

   subtocs1_depth = 5;                    /*r6pl2*/
   subtocs2_depth = 4;                    /*r6pl2*/
   subtocs3_depth = 3;                    /*r6pl2*/
   subtocs4_depth = 2;                    /*r6pl2*/
   subtocs5_depth = 1;                    /*r6pl2*/

   no_auto_toptocs_icons = FALSE;         /*r6pl13*/

   strcpy(html_modern_width, "128");
   html_modern_backcolor.set = FALSE;

   strcpy(html_frames_width, "128");
   strcpy(html_frames_height, "64");
   
   html_frames_backcolor.set = FALSE;
   html_frames_textcolor.set = FALSE;
   html_frames_linkcolor.set = FALSE;
   html_frames_alinkcolor.set = FALSE;
   html_frames_vlinkcolor.set = FALSE;
   html_frames_position = POS_LEFT;
   html_frames_backimage = 0;
   html_name_prefix[0] = EOS;
   
   p1_toctype = TOC_NONE;
   p2_toctype = TOC_NONE;

   sHtmlPropfontStart[0] = EOS;
   sHtmlPropfontEnd[0] = EOS;

   sHtmlMonofontStart[0] = EOS;
   sHtmlMonofontEnd[0] = EOS;

   html_frames_toc_title = NULL;
   html_frames_con_title = NULL;

   refs_counter = 0;
   refs_alloc = 0;
   refs = NULL;

#if USE_NAME_HASH
   memset(hash, 0, sizeof(hash));
#endif
   
   stg_need_endnode = FALSE;
}





/*******************************************************************************
*
*  free_toc_data():
*     exit TOC module
*
*  Return:
*     ???
*
******************************************|************************************/

/*
v6.5.0 [vj] auskommentiert, um eine Compilerwarnung zu entfernen.
Diese Methode wird im Moment nicht mehr benoetigt (siehe exit_module_toc).

LOCAL void free_toc_data(

char **var)
{
   if (*var != NULL)
   {
      free(*var);
      *var = NULL;
   }
}
*/





/*******************************************************************************
*
*  exit_module_toc():
*     exit TOC module
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void exit_module_toc(void)
{
   reset_refs();
   if (refs != NULL)
   {
      free(refs);
      refs = NULL;
   }
   refs_alloc = 0;
}
