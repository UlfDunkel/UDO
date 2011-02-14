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
*    fd  Feb 22: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
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
*
******************************************|************************************/

/*******************************************************************************
*
*     CONSTANTS
*
******************************************|************************************/

#ifndef ID_TOC_C
#define ID_TOC_C
const char *id_toc_c= "@(#) toc.c       $date$";
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
#include <time.h>
#include <ctype.h>
#include "portab.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
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
#include "gui.h"

#include "export.h"
#include "toc.h"
#include "udomem.h"





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define TOC_TOC    0                      /* table of content */
#define TOC_NODE1  1                      /* !node */
#define TOC_NODE2  2                      /* !subnode */
#define TOC_NODE3  3                      /* !subsubnode */
#define TOC_NODE4  4                      /* !subsubsubnode */
#define TOC_NODE5  5                      /* !subsubsubsubnode */
#define TOC_NONE   6                      /* neither nor ... :-) */

#define TOCL_HTM   1                      /* used for use_toc_list_commands */
#define TOCL_TEX   2                      /* dito */





/*******************************************************************************
*
*     LOCAL CONSTANTS
*
******************************************|************************************/

LOCAL const char  *FRAME_NAME_TOC = "UDOtoc";
LOCAL const char  *FRAME_NAME_CON = "UDOcon";

LOCAL const char  *FRAME_FILE_TOC = "00toc";
LOCAL const char  *FRAME_FILE_CON = "00con";

LOCAL const char  *HTML_LABEL_CONTENTS = "UDOTOC";





/*******************************************************************************
*
*     LOCAL VARIABLES
*
******************************************|************************************/

LOCAL BOOLEAN    toc_available;           /* Inhaltsverzeichnis existiert */
LOCAL BOOLEAN    apx_available;           /* Anhang existiert */

LOCAL TOCITEM   *toc[MAXTOCS];            /* Zeiger auf Inhaltsverzeichnis */
LOCAL int        p1_toc_counter;          /* Zaehler fuer das toc[]-Array */
LOCAL int        p2_toc_counter;

LOCAL int        p1_toctype;              /* Typ des aktuellen Kapitels */
LOCAL int        p2_toctype;              /* Typ des aktuellen Kapitels */

LOCAL LABEL     *lab[MAXLABELS];          /* Array mit Zeigern auf Labels */
LOCAL int        p1_lab_counter;          /* Zaehler */
LOCAL int        p2_lab_counter;          /* Zaehler, 2. Durchgang */

                                          /* New in V6.5.9 [NHz] */
LOCAL STYLE      *style[MAXSTYLES];       /* Array mit Zeigern auf Stylesheets */
LOCAL int         p1_style_counter;       /* Zaehler */

LOCAL REFERENCE   refs[MAXREFERENCES+1];  /* Referenzen   */
LOCAL int         refs_counter;           /* Zaehler */

                                          /* absolut */
LOCAL int         p1_toc_n1, p1_toc_n2, p1_toc_n3, p1_toc_n4, p1_toc_n5;
LOCAL int         p1_apx_n1, p1_apx_n2, p1_apx_n3, p1_apx_n4, p1_apx_n5;

                                          /* Anzeige */
LOCAL int         p1_toc_nr1, p1_toc_nr2, p1_toc_nr3, p1_toc_nr4, p1_toc_nr5;
LOCAL int         p1_apx_nr1, p1_apx_nr2, p1_apx_nr3, p1_apx_nr4, p1_apx_nr5;

LOCAL int         p2_toc_n1, p2_toc_n2, p2_toc_n3, p2_toc_n4, p2_toc_n5;
LOCAL int         p2_apx_n1, p2_apx_n2, p2_apx_n3, p2_apx_n4, p2_apx_n5;

LOCAL int         curr_n1_index;
LOCAL int         curr_n2_index;
LOCAL int         curr_n3_index;
LOCAL int         curr_n4_index;          /* [GS] */

LOCAL int         last_n1_index;          /* toc[]-Indizes fuer Titelzeilen */
LOCAL int         last_n2_index;
LOCAL int         last_n3_index;
LOCAL int         last_n4_index;
LOCAL int         last_n5_index;          /* [GS] */

LOCAL int         active_nodetype;        /* Flag fuer check_endnode() */

LOCAL char        form_t1_n1[80], form_t1_n2[80], form_t1_n3[80], form_t1_n4[80], form_t1_n5[80];
LOCAL char        form_t2_n2[80], form_t2_n3[80], form_t2_n4[80], form_t2_n5[80];
LOCAL char        form_t3_n3[80], form_t3_n4[80], form_t3_n5[80];
LOCAL char        form_t4_n4[80], form_t4_n5[80];
LOCAL char        form_t5_n5[80];

LOCAL char        form_a1_n1[80], form_a1_n2[80], form_a1_n3[80], form_a1_n4[80], form_a1_n5[80];
LOCAL char        form_a2_n2[80], form_a2_n3[80], form_a2_n4[80], form_a2_n5[80];
LOCAL char        form_a3_n3[80], form_a3_n4[80], form_a3_n5[80];
LOCAL char        form_a4_n4[80], form_a4_n5[80];
LOCAL char        form_a5_n5[80];

LOCAL char        toc_list_top[64],
                  toc_list_end[64];       /*r6pl2*/
LOCAL char        use_toc_list_commands;  /* TOCL_HTM | TOCL_TEX | 0 */

LOCAL char        allowed_next_chars[64]; /* r5pl10 */
LOCAL char        allowed_prev_chars[64];

LOCAL char        footer_buffer[512];     /* Puffer fuer den Footer */ /*r6pl2 */

LOCAL char        html_target[64];

LOCAL char       *html_frames_toc_title;  /* V6.5.16 [GS] */
LOCAL char       *html_frames_con_title;  /* V6.5.16 [GS] */





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct   _hmtl_index              /* index output for HTML */
   {
   int       toc_index;                   /* # of found label for TOC */
   BOOLEAN   is_node;                     /* the label is the caption (?) */
   char      tocname[512];                /* label or node name */
   char      sortname[512];               /* 'flattened' label or node name */
   UWORD     codepoint;                   /* Unicode codepoint for sorting purposes */
   }  HTML_INDEX;

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





/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

LOCAL void output_aliasses(void);

LOCAL BOOLEAN add_ref(const char *r);
LOCAL void replace_refs(char *s);
LOCAL void string2reference(char *ref, const LABEL *l, const BOOLEAN for_toc, const char *pic, const UWORD uiW, const UWORD uiH);

LOCAL BOOLEAN output_raw_file(const char *filename);

LOCAL void stg_header(const char *numbers, const char *nodename, BOOLEAN is_popup);

LOCAL void pch_headline(char *s);
LOCAL void pch_bottomline(void);
LOCAL void output_pch_header(const char *numbers, const char *name);

LOCAL void tvh_bottomline(void);
LOCAL void output_vision_header(const char *numbers, const char *name);

LOCAL void output_texinfo_node(const char *name);

LOCAL void win_headline(char *name, BOOLEAN popup);
LOCAL void output_win_header(const char *name, const BOOLEAN insivisble);

LOCAL char *get_html_filename(const int tocindex, char *s, int *html_merge);

LOCAL void output_html_meta(BOOLEAN keywords);
LOCAL void output_html_doctype(void);
LOCAL BOOLEAN html_new_file(void);
LOCAL void get_giflink_data(const int index, char *name, UWORD *width, UWORD *height);
LOCAL void html_index_giflink(const int idxEnabled, const int idxDisabled, const char *sep);
LOCAL void html_home_giflink(const int idxEnabled, const int idxDisabled, const char *sep);
LOCAL void html_back_giflink(const int idxEnabled, const int idxDisabled, const char *sep);
LOCAL void html_hb_line(BOOLEAN head);
LOCAL void html_node_bar_modern(void);
LOCAL void html_node_bar_frames(void);

LOCAL void set_inside_node1(void);
LOCAL void set_inside_node2(void);
LOCAL void set_inside_node3(void);
LOCAL void set_inside_node4(void);
LOCAL void set_inside_node5(void);

LOCAL void make_node(const BOOLEAN popup, const BOOLEAN invisible);
LOCAL void make_subnode(const BOOLEAN popup, const BOOLEAN invisible);
LOCAL void make_subsubnode(const BOOLEAN popup, const BOOLEAN invisible);
LOCAL void make_subsubsubnode(const BOOLEAN popup, const BOOLEAN invisible);
LOCAL void make_subsubsubsubnode(const BOOLEAN popup, const BOOLEAN invisible);

LOCAL void tocline_make_bold(char *s, const int depth);
LOCAL void tocline_handle_1st(BOOLEAN *f);
LOCAL void convert_toc_item(TOCITEM *t);
LOCAL void output_appendix_line(void);
LOCAL void toc_link_output(const int depth ); /* New in r6pl16 [NHz] */

LOCAL void toc_output(const int depth);
LOCAL void subtoc_output(const int depth);
LOCAL void subsubtoc_output(const int depth);
LOCAL void subsubsubtoc_output(const int depth);
LOCAL void subsubsubsubtoc_output(void);

LOCAL void apx_output(const int depth);
LOCAL void subapx_output(const int depth);
LOCAL void subsubapx_output(const int depth);
LOCAL void subsubsubapx_output(const int depth);
LOCAL void subsubsubsubapx_output(void);

LOCAL void do_toc(const int depth);
LOCAL void do_subtoc(const int depth);
LOCAL void do_subsubtoc(const int depth);
LOCAL void do_subsubsubtoc(const int depth);
LOCAL void do_subsubsubsubtoc(void);

LOCAL void do_toptoc(const int current_node);

LOCAL int get_toccmd_depth(void);

LOCAL TOCITEM *init_new_toc_entry(const int toctype, const BOOLEAN invisible);
LOCAL BOOLEAN add_toc_to_toc(void);

/*LOCAL void free_toc_data(char **var );*/











/*******************************************************************************
*
*     LOCAL PROCEDURES
*
******************************************|************************************/

/*******************************************************************************
*
*  is_node_link():
*     Zu welchem Node gehoert ein Label (fuer ST-Guide, Texinfo, Pure-C-Help)
*
*  Return:
*      TRUE: label exists
*     FALSE: label doesn't exist
*
******************************************|************************************/

GLOBAL BOOLEAN is_node_link(

const char       *link,          /* ^ link text name */
char             *node,          /* ^ node name which uses this label */
int              *ti,            /* TOC index of node/label/alias */
BOOLEAN          *isnode,        /* TRUE: is label, FALSE: is node or alias */
int              *li)            /* LAB index of node/label/alias */
{
   register int   i;             /* counter*/
   BOOLEAN        ret = FALSE;   /* TRUE: label exists, FALSE: label does not exist*/


   node[0] = EOS;
   *isnode = FALSE;

   if (link[0] == EOS)
   {
      return FALSE;
   }
   
   for (i = 1; i <= p1_lab_counter; i++)
   {
      if (strcmp(lab[i]->name, link) == 0)
      {
         if (lab[i]->is_node)
         {
            *isnode = TRUE;
         }
         
         *li = i;
         *ti = lab[i]->tocindex;
         lab[i]->referenced = TRUE;
         strcpy(node, toc[*ti]->name);
         ret = TRUE;
         break;
      }
   }
   
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
         voutlnf("<a name=\"%s\"></a>", s);
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
*     Aliase eines Kapitels ausgeben. Diese muessen nach der Node-Angabe erfolgen.
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
            voutlnf("<a name=\"%s\"></a>", s);
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
   register int   i;  /* counter */
   
   if (refs_counter >= 0)
   {
      for (i = 0; i <= refs_counter; i++)
      {
         refs[i].entry[0]= EOS;
         refs[i].magic[0]= EOS;
      }
   }
   
   refs_counter = -1;
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

LOCAL BOOLEAN add_ref(

const char  *r)  /* */
{
   if (refs_counter < MAXREFERENCES)
   {
      refs_counter++;
      
                                          /* r5pl8 */
      if (refs_counter + OFFSET_REF == (int)'~')
      {
         refs_counter++;
      }
      
                                          /* r5pl8 */
      if (refs_counter + OFFSET_REF == (int)127)
      {
         refs_counter++;
      }
      
      sprintf(refs[refs_counter].magic, "\033%c%c\033", C_REF_MAGIC, refs_counter+OFFSET_REF);
      strcpy(refs[refs_counter].entry, r);
      
      return TRUE;
   }
   
   return FALSE;
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

LOCAL void replace_refs(

char             *s)  /* */
{
   register int   i;  /* */
   
   
   if (refs_counter >= 0)
   {
      for (i = 0; i <= refs_counter; i++)
      {
         replace_once(s, refs[i].magic, refs[i].entry);
      }
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

LOCAL void string2reference(

char           *ref,                 /* */
const LABEL    *l,                   /* */
const BOOLEAN   for_toc,             /* */
const char     *pic,                 /* constant for GUI navigation image, e.g. GIF_UP_NAME */
const UWORD     uiW,                 /* GUI navigation image width */
const UWORD     uiH)                 /* GUI navigation image height */
{
   char         s[512],              /* */
                n[512],              /* */
                sNoSty[512],         /* */
                hfn[512],            /* */
                sGifSize[80];        /* */
   int          ti,                  /* */
                ui;                  /* */
   BOOLEAN      same_file = FALSE;   /* TRUE: reference is in same file */
   char        *htmlfilename,        /* */
                                     /* */
                suff[MYFILE_SUFF_LEN + 1];
   char         closer[8] = "\0";    /* single tag closer mark in XHTML */
   
   
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
               sprintf(ref, "<a href=\"%s%s\"%s>%s</a>",htmlfilename, suff, html_target, n);
            }
            else
            {
                                          /* Changed in r6pl16 [NHz] */
               sprintf(ref, "<a href=\"%s%s#%s\"%s>%s</a>",htmlfilename, suff, sNoSty, html_target, n);
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
               sprintf(ref, "<a href=\"%s%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s></a>", 
                  htmlfilename, suff, html_target, pic, n, n, sGifSize, closer);
            }
            else
            {
               sprintf(ref, "<a href=\"%s%s#%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s></a>",
                  htmlfilename, suff, sNoSty, html_target, pic, n, n, sGifSize, closer);
            }
         }
      }
      else
      {
         if (l->is_node || l->is_alias)
         {
            if (same_file)
            {
               sprintf(ref, "<a href=\"#%s\"%s>%s</a>", sNoSty, html_target, n);
            }
            else
            {                             /* Hier muss noch unterschieden werden, wenn */
                                          /* gemerged wird. Dann ein # einfuegen!!!! */
                                          /* ti oben bereits aus tocindex gesetzt */
               if (    (html_merge_node2 && toc[ti]->n2 > 0)
                    || (html_merge_node3 && toc[ti]->n3 > 0)
                    || (html_merge_node4 && toc[ti]->n4 > 0)
                    || (html_merge_node5 && toc[ti]->n5 > 0)
                 )
               {
                                          /* Changed in r6pl16 [NHz] */
                  sprintf(ref, "<a href=\"%s%s#%s\"%s>%s</a>",
                     htmlfilename, suff, sNoSty, html_target, n);
               }
               else
               {
                                          /* Changed in r6pl16 [NHz] */
                  sprintf(ref, "<a href=\"%s%s\"%s>%s</a>",
                     htmlfilename, suff, html_target, n);
               }
            }
         }
         else
         {
                                          /* Changed in r6pl16 [NHz] */
            sprintf(ref, "<a href=\"%s%s#%s\"%s>%s</a>",
               htmlfilename, suff, sNoSty, html_target, n);
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
const BOOLEAN     for_toc,       /* TRUE: use auto reference for TOC */
const char       *pic,           /* also images can be referenced (used in string2reference()) */
const UWORD       uiWidth,       /* image width */
const UWORD       uiHeight)      /* image height */
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
   BOOLEAN        ref_it;        /* */
   BOOLEAN        ignore_it;     /* */
   BOOLEAN        next_ok,       /* */
                  prev_ok;       /* */
   BOOLEAN        found_one,     /* */
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
            string2reference(the_ref, lab[found_lab], for_toc, pic, uiWidth, uiHeight);
            add_ref(the_ref);
         }
         else
         {
            add_ref(lab[found_lab]->name);
         }
   
         replace_once(found_pos, lab[found_lab]->name, refs[refs_counter].magic);
   
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
            do_subtoc(subtocs1_depth);
            
         break;
         
      case TOC_NODE2:
         if (use_auto_subsubtocs)
            do_subsubtoc(subtocs2_depth);
            
         break;
         
      case TOC_NODE3:
         if (use_auto_subsubsubtocs)
            do_subsubsubtoc(subtocs3_depth);
            
         break;
         
      case TOC_NODE4:
         if (use_auto_subsubsubsubtocs)
            do_subsubsubsubtoc();
            
         break;
      }
      
      switch (desttype)
      {
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
*     Raw-Header einlesen und unveraendert ausgeben (r6pl10)
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL BOOLEAN output_raw_file(

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
      
      while ( (len>0) && (((UBYTE)s[len-1]) <= 32) )
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

GLOBAL BOOLEAN check_output_raw_header(void)
{
   if (!toc[p2_toc_counter]->ignore_raw_header)
   {
      if (toc[p2_toc_counter]->raw_header_filename!=NULL)
      {
         return(output_raw_file(toc[p2_toc_counter]->raw_header_filename));
      }
      else
      {
         if (sDocRawHeaderFilename[0] != EOS)
         {
            return(output_raw_file(sDocRawHeaderFilename));
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

GLOBAL BOOLEAN check_output_raw_footer(

BOOLEAN   lastNode)    /* */
{
   int    offset = 1;  /* */
   
   
   if (lastNode)
      offset = 0;
   
   /* p2_toc_counter bereits hochgezaehlt, daher 1 abziehen, */
   /* aber nur dann, wenn es nicht der letzte Node ist (bei  */
   /* !end_document tritt das auf) !!! */
   
   if (!toc[p2_toc_counter-offset]->ignore_raw_footer)
   {
      if (toc[p2_toc_counter-offset]->raw_footer_filename != NULL)
      {
         return(output_raw_file(toc[p2_toc_counter-offset]->raw_footer_filename));
      }
      else
      {
         if (sDocRawFooterFilename[0] != EOS)
         {
            return(output_raw_file(sDocRawFooterFilename));
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

GLOBAL void stg_headline(

const char  *numbers,      /* */
const char  *nodename)     /* */
{
   char      n[512],       /* */
             s[512];       /* */
   size_t    i,            /* counter */
             sooft,        /* */
             platz_links,  /* */
             sl;           /* */
   
   
   do_toptoc(toc[p2_toc_counter]->toctype);
   
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
*     Header fuer den ST-Guide
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void stg_header(

const char  *numbers,   /* */
const char  *nodename,  /* */
BOOLEAN      is_popup)  /* */
{
   char      n[512];    /* */
   int       ti;        /* */
   BOOLEAN   flag;      /* */
   
   
   output_aliasses();
   
   ti = p2_toc_counter;
   
   if (ti >= 0)
   {
      if (toc[ti]->ignore_links)
         outln("@noref");
   
      if (use_chapter_images && toc[ti]->image != NULL)
      {       
         strcpy(n, toc[ti]->image);
         change_sep_suffix(n, ".img");
         c_begin_center();                /* R6r5pl1 */
         flag = c_img_output(n, "", FALSE);
         c_end_center();

         if (flag)
            return;
      }
   }
   
   if (!is_popup)  
      stg_headline(numbers, nodename);
}





/*******************************************************************************
*
*  pch_headline():
*     Topline fuer PC-HELP
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
*     Bottomline fuer PC-HELP
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
*     ??? (description missing)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_pch_header(

const char       *numbers,  /* */
const char       *name)     /* */
{
   char           n[256],   /* */
                  q[256];   /* */
   int            start;    /* */
   register int   i;        /* */

   
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
   
   do_toptoc(toc[p2_toc_counter]->toctype);
   
   sprintf(n, "%s%s", numbers, name);
   pch_headline(n);
   outln("");
}





/*******************************************************************************
*
*  output_pch_header():
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
*  output_pch_header():
*     Bottomline fuer Turbo-Vision-Help
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
*     Turbo-Vision-Help-Node-Header erzeugen
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
*     Nodeline fuer Texinfo
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
*     Topline fuer WinHelp
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void win_headline(

char     *name,    /* */
BOOLEAN   popup)   /* */
{
   char   n[512],  /* */
          fs[32];  /* */
   int    ti;      /* */
   
   
   ti = p2_toc_counter;
   
   if (use_chapter_images)
   {       
      if (ti >= 0 && toc[ti]->image != NULL)
      {
         um_strcpy(n, toc[ti]->image, 512, "win_headline[1]");
         c_begin_center();                /* r6pl1 */
         c_bmp_output(n, "", FALSE);
         c_end_center();                  /* r6pl1 */
         return;
      }
   }
   
                                          /* r5pl16: Headlines wirklich unterdruecken */
   if (no_headlines || toc[ti]->ignore_headline || (no_popup_headlines && popup))
      return;
   
   c_win_styles(name);
   
   if (!popup)
      outln("\\keepn");
   
   do_toptoc(toc[ti]->toctype);    /*r6pl5*/
   
   sprintf(fs, "\\fs%d", iDocPropfontSize + 14);
   
   if (popup)
      voutlnf("{%s{\\b %s}}\\par\\pard\\par", fs, name);
   else
      voutlnf("{%s{\\b\\sa20\\sb20 %s}}\\par\\pard\\par", fs, name);
}





/*******************************************************************************
*
*  output_win_header():
*     Header fuer WinHelp
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void output_win_header(

const char     *name,           /* */
const BOOLEAN   invisible)      /* */
{
   char         n[512],         /* */
                f[512],         /* */
                cbb[512];       /* */
   int          ci,             /* */
                ui;             /* */
   char         hlp_name[256];  /* */
   
   const char *btn_disable = "!{\\footnote ! DisableButton(\"BTN_UP\") }";
   const char *btn_enable  = "!{\\footnote ! EnableButton(\"BTN_UP\");";
   const char *btn_change  = "ChangeButtonBinding(\"BTN_UP\", \"JumpID(%s, `%s') \") }";

   
   if (desttype == TOAQV)                 /* r5pl6 */
      strcpy(hlp_name, "qchPath");
   else
      sprintf(hlp_name, "`%s.hlp'", outfile.name);
   
   um_strcpy(n, name, 512, "output_win_header[1]");

   del_internal_styles(n);                /* r5pl3 */
   
   outln("{");
   
                                          /* r5pl10 */
   if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
   {
      um_strcpy(f, n, 512, "output_win_header[2]");
      winspecials2ascii(f);
      voutlnf("K{\\footnote K %s}", f);
   }
   
   if (bDocWinOldKeywords)
   {
      um_strcpy(f, n, 512, "output_win_header[3]");
      node2winhelp(f);
      voutlnf("#{\\footnote # %s}", f);
   }
   
                                          /* r6pl2 */
   node2NrWinhelp(f, toc[p2_toc_counter]->labindex);

   voutlnf("#{\\footnote # %s}", f);

   if (toc[p2_toc_counter]->mapping>=0)
   {
      voutlnf("#{\\footnote # %d}", toc[p2_toc_counter]->mapping);
   }
   
   voutlnf("${\\footnote $ %s}", n);      /* r5pl3 */
   
   if (!no_buttons)                       /* r6pl8 */
   {
      if (!invisible)                     /* r5pl12: versteckte Kapitel nicht mit in die Browse-Sequence einbinden */
      {
         outln(win_browse);
      }
   
      cbb[0] = EOS;
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
      }
      
      if (ui == 0)
      {
         if (called_tableofcontents)
         {
            node2NrWinhelp(n, 0);
                                          /* r5pl6 */
            sprintf(cbb, btn_change, hlp_name, n);
            outln(btn_enable);
            outln(cbb);
         }
         else
         {
            outln(btn_disable);
         }
      }
      else
      {
         node2NrWinhelp(n, toc[ui]->labindex);
                                          /* r5pl6 */
         sprintf(cbb, btn_change, hlp_name, n);
         outln(btn_enable);
         outln(cbb);
      }
   }
}





/*******************************************************************************
*
*  get_html_filename():
*     Dateinamen fuer HTML abhaengig vom aktuellen Node ermitteln.
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
            tmp_n5[MAX_TMP_NX];  /* */
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
        html_merge_node4 || html_merge_node5 )
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
            
   /* ToDo: [GS] Problem, wie man bei einen Dateinamen mit 8 Zeichen den Node 5 darstellt */

            if (toc[ti]->n5>0 && !html_merge_node5)
            {
               if (hexwidth == 3)         /* Long filename */
                  sprintf(tmp_n5, "%0*x", hexwidth, toc[ti]->n5);
               else
                  sprintf(tmp_n4, "%0*x", hexwidth, toc[ti]->n5+100);
            }
         }
      }
      
      if (hexwidth == 3)                  /* Long filename */
         sprintf(s, "%s%s%s%s%s", tmp_n1, tmp_n2, tmp_n3, tmp_n4, tmp_n5);
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
      fprintf(stderr, "! empty filename: %d,%d,%d,%d (%d)\n",
         toc[ti]->n1,
         toc[ti]->n2,
         toc[ti]->n3,
         toc[ti]->n4,
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
*     Neue Datei fuer HTML anlegen, Header und Metainfos ausgeben
*
*  Note:
*     wird nur fuer das jeweils aktuelle Kapitel aufgerufen
*     (durch html_new_file())
*
*  return:
*     ???
*
******************************************|************************************/

LOCAL BOOLEAN html_make_file(void)
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
      if (toc[ti]->dirname[0] != EOS)
         sprintf(outfile.path, "%s%s", old_outfile.path, toc[ti]->dirname);
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

LOCAL void output_html_meta(

BOOLEAN    keywords)             /* */
{
   int     ti = 0,               /* */
           i,                    /* */
           li,                   /* */
           j,                    /* */
           html_merge;           /* */
   STYLE  *styleptr;             /* */
   char    s[512],               /* buffer for charset and label name */
           htmlname[512],        /* */
           sTarget[512] = "\0";  /* */
   char    backpage[256],        /* */
           href[256],            /* */
           alt[256],             /* */
          *tok;                  /* */
   char    closer[8] = "\0";     /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
                                          /* get right charset name */
   strcpy(s, chr_codepage_charset_name(iEncodingTarget));
     
   voutlnf("<meta http-equiv=\"Content-Type\" content=\"text/html;charset=%s\"%s>", s, closer);
   voutlnf("<meta http-equiv=\"Content-Language\" content=\"%s\"%s>", lang.html_lang, closer);
   voutlnf("<meta http-equiv=\"Content-Style-Type\" content=\"text/css\"%s>", closer);
   voutlnf("<meta http-equiv=\"Content-Script-Type\" content=\"text/javascript\"%s>", closer);

   /* New feature #0000054 in V6.5.2 [NHz] */
   if (html_header_date)
   {
      char     zone[10] = "+00:00";  /* */
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
         iDateYear, iDateMonth, iDateDay, iDateHour, iDateMin, iDateSec, zone, closer);
   }

   /* Changed in V6.5.5 [NHz] */
   voutlnf("<meta name=\"Generator\" content=\"UDO %s.%s %s for %s\"%s>",
      UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS, closer);

   if (titdat.author != NULL)
   {
      voutlnf("<meta name=\"Author\" content=\"%s\"%s>", titdat.author, closer);
   }

   if (keywords)
   {
      ti = p2_toc_counter;

      if (ti >= 0)
      {
         if (toc[ti]->keywords != NULL)
         {
            voutlnf("<meta name=\"Keywords\" content=\"%s\"%s>", toc[ti]->keywords, closer);
         }

         /* New in V6.5.9 [NHz] */
         else
         {
            if (titdat.keywords != NULL)
            {
               voutlnf("<meta name=\"Keywords\" content=\"%s\"%s>", titdat.keywords, closer);
            }
         }

         if (toc[ti]->description != NULL)
         {
            voutlnf("<meta name=\"Description\" content=\"%s\"%s>", toc[ti]->description, closer);
         }
         else                             /* New in V6.5.9 [NHz] [docinfo] */
         {
            if (titdat.description != NULL)
            {
               voutlnf("<meta name=\"Description\" content=\"%s\"%s>", titdat.description, closer);
            }
         }

         /* New in V6.5.17 */
         if (toc[ti]->robots != NULL)
         {
            voutlnf("<meta name=\"robots\" content=\"%s\"%s>", toc[ti]->robots, closer);
         }
         else
         {
            if (titdat.robots != NULL)
            {
               voutlnf("<meta name=\"robots\" content=\"%s\"%s>", titdat.robots, closer);
            }
         }
      }
   }

   /*r6pl5: <link>-Tag */
   if (titdat.contact_name != NULL)
   {
      voutlnf("<meta name=\"Email\" content=\"%s\"%s>", titdat.contact_name, closer);
	   if (titdat.contact_link == NULL)
      {
         voutlnf("<link rev=\"made\" href=\"mailto:%s\" title=\"E-Mail\"%s>", titdat.contact_name, closer);

         /* New in r6pl16 [NHz] */
         voutlnf("<link rel=\"author\" href=\"mailto:%s\" title=\"E-Mail\"%s>", titdat.contact_name, closer);
      }
   }
   if (titdat.contact_link != NULL)
   {
      voutlnf("<link rev=\"made\" href=\"%s\" title=\"E-Mail\"%s>", titdat.contact_link, closer);

      /* New in r6pl16 [NHz] */
      voutlnf("<link rel=\"author\" href=\"%s\" title=\"E-Mail\"%s>", titdat.contact_link, closer);
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
                  old_outfile.name, outfile.suff, sTarget, lang.html_start, closer);

               /* Special for CAB */
               voutlnf("<link rel=\"home\" href=\"%s%s\"%s title=\"%s\"%s>", 
                  old_outfile.name, outfile.suff, sTarget, lang.html_start, closer);
               
               if (uses_tableofcontents)
               {
                                          /* New in r6pl15 [NHz] */
                  voutlnf("<link rel=\"contents\" href=\"%s%s#UDOTOC\"%s title=\"%s\"%s>",
                     old_outfile.name, outfile.suff, sTarget, lang.contents, closer);

                  /* Special for CAB */
                  voutlnf("<link rel=\"toc\" href=\"%s%s#UDOTOC\"%s title=\"%s\"%s>", 
                     old_outfile.name, outfile.suff, sTarget, lang.contents, closer);
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
            voutlnf("<link rel=\"up\" href=\"%s\" title=\"%s\"%s>", href, alt, closer);
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
                  html_name_prefix, htmlname, sTarget, s, closer);
            }
            else
            {
               voutlnf("<link rel=\"first\" href=\"%s%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, closer);
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
                  html_name_prefix, htmlname, sTarget, s, closer);
               
               /* Special for CAB */
               voutlnf("<link rel=\"previous\" href=\"%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, sTarget, s, closer);
            }
            else
            {
               voutlnf("<link rel=\"prev\" href=\"%s%s%s\"%s title=\"%s\"%s>",
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, closer);
               
               /* Special for CAB */
               voutlnf("<link rel=\"previous\" href=\"%s%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, closer);
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
                  html_name_prefix, htmlname, sTarget, s, closer);
            }
            else
            {
               voutlnf("<link rel=\"next\" href=\"%s%s%s\"%s title=\"%s\"%s>", 
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, closer);
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
                  html_name_prefix, htmlname, sTarget, s, closer);
            }
            else
            {
               voutlnf("<link rel=\"last\" href=\"%s%s%s\"%s title=\"%s\"%s>",
                  html_name_prefix, htmlname, outfile.suff, sTarget, s, closer);
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
            htmlname, outfile.suff, sTarget, s, closer);
      }
   }

   /* New in r6pl15 [NHz] */
   /* Link for overall and file-related stylesheet-file */
   /* Changed in V6.5.9 [NHz] */

   for (j = 1; j <= p1_style_counter; j++)
   {
      styleptr = style[j];
      
      if (styleptr->href != NULL && (styleptr->tocindex == 0 || styleptr->tocindex == p2_toc_counter))
      {
         char  this_style[512];  /* */

         
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
         
         strcat(this_style, "\">");       /* fd:20071114: tag closed */
         outln(this_style);
      }
   }

/* if (sDocStyle[0] != EOS)     
      voutlnf("<link rel=\"stylesheet\" type=\"text/css\" href=\"%s\"%s>", sDocStyle, closer);
*/

   /* Link for overall javascript-file */
   if (sDocScript[0] != EOS)
   {
      voutlnf("<script language=\"JavaScript\" src=\"%s\" type=\"text/javascript\">", sDocScript);
      outln("</script>");
   }

   /* New in r6pl15 [NHz] */
   /* Link for overall FavIcon */
   if (sDocFavIcon[0] != EOS)
      voutlnf("<link rel=\"shortcut icon\" href=\"%s\"%s>", sDocFavIcon, closer);
   
        /* New in V6.5.20 [GS] */
        if (toc[p2_toc_counter]->bgsound[0] != '\0')
                voutlnf("<bgsound src=%s>", toc[p2_toc_counter]->bgsound);

}  /* output_html_meta */





/*******************************************************************************
*
*  output_html_doctype():
*     ??? (description missing)
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
   
   switch (html_doctype)                  /* Changed in r6pl16 [NHz] */
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
   
   if (html_header_date)                  /* fixed in v6.5.19 */
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

LOCAL BOOLEAN html_new_file(void)
{
   char   t[512],        /* */
          xml_lang[15],  /* */
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
      
      if (toc[p2_toc_counter]->backimage[0]!=EOS)
      {
         voutf(" background=\"%s\"", toc[p2_toc_counter]->backimage);
      }
      
      if (toc[p2_toc_counter]->backcolor[0] != EOS)
      {
         voutf(" bgcolor=\"%s\"", toc[p2_toc_counter]->backcolor);
      }
      
      if (toc[p2_toc_counter]->textcolor[0] != EOS)
      {
         voutf(" text=\"%s\"", toc[p2_toc_counter]->textcolor);
      }
      
      if (toc[p2_toc_counter]->linkcolor[0] != EOS)
      {
         voutf(" link=\"%s\"", toc[p2_toc_counter]->linkcolor);
      }
      
      if (toc[p2_toc_counter]->alinkcolor[0] != EOS)
      {
         voutf(" alink=\"%s\"", toc[p2_toc_counter]->alinkcolor);
      }
      
      if (toc[p2_toc_counter]->vlinkcolor[0] != EOS)
      {
         voutf(" vlink=\"%s\"", toc[p2_toc_counter]->vlinkcolor);
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
   char      xml_lang[15],      /* */
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
   
   if (sDocBackImage[0] != EOS)
   {
      if (!no_images)                     /*r6pl2*/
      {
         voutf(" background=\"%s\"", sDocBackImage);
      }
   }
   
   if (sDocBackColor[0] != EOS)
   {
      voutf(" bgcolor=\"%s\"", sDocBackColor);
   }
   
   if (sDocTextColor[0] != EOS)
   {
      voutf(" text=\"%s\"", sDocTextColor);
   }
   
   if (sDocLinkColor[0] != EOS)
   {
      voutf(" link=\"%s\"", sDocLinkColor);
   }
   
   if (sDocAlinkColor[0] != EOS)
   {
      voutf(" alink=\"%s\"", sDocAlinkColor);
   }
   
   if (sDocVlinkColor[0] != EOS)
   {
      voutf(" vlink=\"%s\"", sDocVlinkColor);
   }
   
   voutlnf(">");
   
   check_output_raw_header();             /*r6pl10*/
   
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

LOCAL void get_giflink_data(

const int   index,   /* */
char       *name,    /* */
UWORD      *width,   /* */
UWORD      *height)  /* */
{
   name[0] = EOS;                         /* clear name */
   
   *width  = *height = 0;
   
   switch (index)
   {
   case GIF_HM_INDEX:                     /* Home */
      strcpy(name, GIF_HM_NAME);
      *width  = uiGifHmWidth;
      *height = uiGifHmHeight;
      break;
   case GIF_UP_INDEX:                     /* Up */
      strcpy(name, GIF_UP_NAME);
      *width  = uiGifUpWidth;
      *height = uiGifUpHeight;
      break;
   case GIF_LF_INDEX:                     /* Left */
      strcpy(name, GIF_LF_NAME);
      *width  = uiGifLfWidth;
      *height = uiGifLfHeight;
      break;
   case GIF_RG_INDEX:                     /* Right */
      strcpy(name, GIF_RG_NAME);
      *width  = uiGifRgWidth;
      *height = uiGifRgHeight;
      break;
   case GIF_NOHM_INDEX:                   /* Home (disabled) */
      strcpy(name, GIF_NOHM_NAME);
      *width  = uiGifNoHmWidth;
      *height = uiGifNoHmHeight;
      break;
   case GIF_NOUP_INDEX:                   /* Up (disabled) */
      strcpy(name, GIF_NOUP_NAME);
      *width  = uiGifNoUpWidth;
      *height = uiGifNoUpHeight;
      break;
   case GIF_NOLF_INDEX:                   /* LEft (disabled) */
      strcpy(name, GIF_NOLF_NAME);
      *width  = uiGifNoLfWidth;
      *height = uiGifNoLfHeight;
      break;
   case GIF_NORG_INDEX:                   /* Right (disabled) */
      strcpy(name, GIF_NORG_NAME);
      *width  = uiGifNoRgWidth;
      *height = uiGifNoRgHeight;
      break;
   case GIF_GER_INDEX:                    /* German */
      strcpy(name, GIF_GER_NAME);
      *width  = uiGifGerWidth;
      *height = uiGifGerHeight;
      break;
   case GIF_ENG_INDEX:                    /* English */
      strcpy(name, GIF_ENG_NAME);
      *width  = uiGifEngWidth;
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

LOCAL void html_index_giflink(

const int    idxEnabled,        /* */
const int    idxDisabled,       /* */
const char  *sep)               /* */
{
   char      sTarget[64],       /* */
             sFile[64],         /* */
             sGifSize[80],      /* */
             sGifName[256];     /* */
   UWORD     uiW,               /* */
             uiH;               /* */
   char      closer[8] = "\0";  /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   sTarget[0] = sGifSize[0] = EOS;
   
   if (html_frames_layout)
   {
      sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
      sprintf(sFile, "%s%s", html_name_prefix, FRAME_FILE_CON);
   }
   else
   {
      sTarget[0] = EOS;
      strcpy(sFile, old_outfile.name);
   }
   
   
   if (uses_tableofcontents)
   {
      if (no_images)                      /*r6pl2*/
      {
         voutlnf("%s<a href=\"%s%s#%s\"%s>%s</a>",
            sep, sFile, outfile.suff, HTML_LABEL_CONTENTS, sTarget, " ^^^" /* lang.contents */);
      }
      else
      {
         get_giflink_data(idxEnabled, sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;

         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
         voutf("<a href=\"%s%s#%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s></a>",
            sFile, outfile.suff, HTML_LABEL_CONTENTS, sTarget, sGifName, lang.contents, lang.contents, sGifSize, closer);
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
         get_giflink_data(idxDisabled, sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
         
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
         voutf("<img src=\"%s\" alt=\"\" title=\"\" border=\"0\"%s%s>", sGifName, sGifSize, closer);
      }
   }
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

LOCAL void html_home_giflink(

const int    idxEnabled,        /* */
const int    idxDisabled,       /* */
const char  *sep)               /* */
{
   char      sTarget[64],       /* */
             sFile[64];         /* */
   char      sGifSize[128],     /* */
             sGifName[256];     /* */
   UWORD     uiW,               /* */
             uiH;               /* */
   char      closer[8] = "\0";  /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   if (toc[p2_toc_counter]->toctype == TOC_TOC)
   {
   /* r6pl7: Im Inhaltsverzeichnis Link auf !html_backpage mit Home-Symbol */
      sTarget[0] = EOS;
   
      if (html_frames_layout)
      {
         sprintf(sTarget, " target=\"_top\"");
      }
   
      if (no_images)
      {
         voutlnf("%s%s", sep, lang.html_home);
      }
      else
      {                                   /* Button disabled ausgeben */
         get_giflink_data(idxDisabled, sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;

         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
         voutf("<img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s>",
            sGifName, lang.html_home, lang.html_home, sGifSize, closer);
      }
   }
   else
   {
      if (html_frames_layout)
      {
         sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
         sprintf(sFile, "%s%s", html_name_prefix, FRAME_FILE_CON);
      }
      else
      {
         sTarget[0] = EOS;
         strcpy(sFile, old_outfile.name);
      }
   
      if (no_images)                      /*r6pl2*/
      {
         voutlnf("%s<a href=\"%s%s\"%s>%s</a>", sep, sFile, outfile.suff, sTarget, lang.html_home);
      }
      else
      {
         get_giflink_data(idxEnabled, sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
         
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
         voutf("<a href=\"%s%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s></a>",
                        sFile, outfile.suff, sTarget, sGifName, lang.html_home, lang.html_home, sGifSize, closer);
      }
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

LOCAL void html_back_giflink(

const int    idxEnabled,        /* */
const int    idxDisabled,       /* */
const char  *sep)               /* */
{
   char      target[64],        /* */
             backpage[256],     /* */
             href[256],         /* */
             alt[256],          /* */
            *tok;               /* */
   char      sGifSize[128],     /* */
             sGifName[256];     /* */
   UWORD     uiW,               /* */
             uiH;               /* */
   char      closer[8] = "\0";  /* single tag closer mark in XHTML */
   
   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   target[0] = sGifName[0] = EOS;
   
   if (sDocHtmlBackpage[0] != EOS)
   {
                                          /* New in r6pl16 [NHz] */
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
   
                                          /* Changed in r6pl16 [NHz] */
      if (no_images)
      {
         voutlnf("%s<a href=\"%s\"%s>%s</a>", sep, href, target, alt);
      }                                   /* changed */
      else
      {
         get_giflink_data(idxEnabled, sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
   
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
                                          /* Changed in r6pl16 [NHz] */
         voutf("<a href=\"%s\"%s><img src=\"%s\" alt=\"%s\" title=\"%s\" border=\"0\"%s%s></a>",
            href, target, sGifName, alt, alt, sGifSize, closer);
      }
   }
   else
   {
      if (no_images)
      {
         voutlnf("%s^^^", sep);
      }
      else
      {                                   /* Diabled Button ausgeben */
         get_giflink_data(idxDisabled, sGifName, &uiW, &uiH);
         sGifSize[0] = EOS;
         
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
         voutf("<img src=\"%s\" alt=\"\" title=\"\" border=\"0\"%s%s>", sGifName, sGifSize, closer);
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

LOCAL void html_hb_line(

BOOLEAN      head)              /*  TRUE: output GUI navigation bar in page header; */
                                /* FALSE: output GUI navigation bar in page footer */
{
   int       i,                 /* */
             ti,                /* */
             li;                /* */
   char      s[512],            /* */
             anchor[512],       /* */
             sGifSize[128],     /* */
             sGifFile[128],     /* */
             sTarget[64],       /* */
            *colptr;            /* */
   BOOLEAN   old_autorefoff;    /* */
   BOOLEAN   for_main_file;     /* */
   UWORD     uiW,               /* */
             uiH;               /* */
   char      closer[8] = "\0";  /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
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
   
   if (head && toc[ti]->ignore_headline)  /* r5pl12 */
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
            if (html_doctype < XHTML_STRICT)
               outln(HTML_HR);
            else
               outln(XHTML_HR);
         }
      }
   }
   
   
#if 1
   colptr = NULL;
   
   if (html_modern_layout)
      colptr = html_modern_backcolor;
      
   if (html_frames_layout)
      colptr = html_frames_backcolor;
   
   if (colptr)
   {
      s[0] = EOS;
      
      if (colptr[0] != EOS)
      {
         sprintf(s, " bgcolor=\"%s\"", colptr);
      }
      
      voutlnf("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\"%s><tr><td valign=\"top\">", s);
   }
#endif
   
   /* ------------------------------------------------ */
   /* Verweis auf die Homepage erzeugen                */
   /* ------------------------------------------------ */
   
   html_home_giflink(GIF_HM_INDEX, GIF_NOHM_INDEX, "[ ");
   
   
   /* ------------------------------------------------ */
   /* Verweis auf das uebergeordnete Kapitel erzeugen  */
   /* ------------------------------------------------ */
   
   switch (toc[ti]->toctype)
   {
   case TOC_TOC:                          /* Verweis auf Backpage erzeugen */
      html_back_giflink(GIF_UP_INDEX, GIF_NOUP_INDEX, "| ");
      break;

   case TOC_NODE1:                        /* Weiter nach oben geht es nicht */
      html_index_giflink(GIF_UP_INDEX, GIF_NOUP_INDEX, "| ");
      break;
   
   case TOC_NODE2:                        /* Verweis auf aktuellen !node */
      li = toc[last_n1_index]->labindex;
      
      if (lab[li]->name != EOS)
      {
         um_strcpy(s, lab[li]->name, 512, "html_hb_line[1]");

         string2reference(anchor, lab[li], TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
         replace_once(s, lab[li]->name, anchor);

         if (no_images)
         {
            replace_once(s, lab[li]->name, " ^^^");
            strinsert(s, "| ");
         }
   
         out(s);
      }
      
      break;
   
   case TOC_NODE3:                        /* Verweis auf aktuellen !subnode */
      li = toc[last_n2_index]->labindex;
      
      if (lab[li]->name != EOS)
      {
         um_strcpy(s, lab[li]->name, 512, "html_hb_line[2]");
      
         string2reference(anchor, lab[li], TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
         replace_once(s, lab[li]->name, anchor);

         if (no_images)
         {
            replace_once(s, lab[li]->name, " ^^^");
            strinsert(s, "| ");
         }
      
         out(s);
      }
      
      break;
      
   case TOC_NODE4:                        /* Verweis auf aktuellen !subsubnode */
      li = toc[last_n3_index]->labindex;
      
      if (lab[li]->name != EOS)
      {
         um_strcpy(s, lab[li]->name, 512, "html_hb_line[3]");

         string2reference(anchor, lab[li], TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
         replace_once(s, lab[li]->name, anchor);

         if (no_images)
         {
            replace_once(s, lab[li]->name, " ^^^");
            strinsert(s, "| ");
         }
      
         out(s);
      }
      
      break;

   case TOC_NODE5:                        /* Verweis auf aktuellen !subsubsubnode */
      li = toc[last_n4_index]->labindex;

      if (lab[li]->name != EOS)
      {
         um_strcpy(s, lab[li]->name, 512, "html_hb_line[4]");

         string2reference(anchor, lab[li], TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
         replace_once(s, lab[li]->name, anchor);

         if (no_images)
         {
            replace_once(s, lab[li]->name, " ^^^");
            strinsert(s, "| ");
         }
      
         out(s);
      }
      
   }
   
   
   /* --------------------------------------------------- */
   /* Verweis auf die vorherige Seite erzeugen            */
   /* default:            das letzte Kapitel              */
   /* !html_merge_node1:  kein Aufruf dieser Routine      */
   /* !html_merge_node2:  der letzte !node                */
   /* !html_merge_node3:  der letzte !subnode             */
   /* !html_merge_node4:  der letzte !subsubnode          */
   /* --------------------------------------------------- */
   
   if (for_main_file)
   {
#if 1
      if (no_images)                      /* Deaktivierten Link/Bild ausgeben */
      {
         outln("| &lt;&lt;&lt;");
      }
      else
      {
         get_giflink_data(GIF_NOLF_INDEX, s, &uiW, &uiH);
         sGifSize[0] = EOS;
         
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
         voutf("<img src=\"%s\" alt=\"\" title=\"\" border=\"0\"%s%s>", s, sGifSize, closer);
      }
#else
      html_back_giflink(GIF_LF_INDEX, GIF_NOLF_INDEX, "| ");
#endif
   }
   else
   {
      i = toc[ti]->prev_index;
   
      if (i == 0)
      {                                   /* Erster Node -> Zurueck zum Hauptfile */
         html_home_giflink(GIF_LF_INDEX, GIF_NOLF_INDEX, "| ");
      }
      else
      {
         if (i > 0)
         {
            li = toc[i]->labindex;
            um_strcpy(s, lab[li]->name, 512, "html_hb_line[5]");

            string2reference(anchor, lab[li], TRUE, GIF_LF_NAME, uiGifLfWidth, uiGifLfHeight);
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
#if 1
            if (no_images)                /* disabled nach links */
            {
               outln("| &lt;&lt;&lt;");
            }
            else
            {
               get_giflink_data(GIF_NOLF_INDEX, s, &uiW, &uiH);
               sGifSize[0] = EOS;
               
               if (uiW != 0 && uiH != 0)
               {
                  sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
               }
               
               voutf("<img src=\"%s\" alt=\"\" title=\"\" border=\"0\"%s%s>", s, sGifSize, closer);
            }
#else
                                          /* Frueher Link auf die Startseite */
            html_home_giflink(GIF_LF_INDEX, GIF_NOLF_INDEX, "| ");
#endif
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
            if (toc[i]->toctype != TOC_NODE1 && toc[i]->toctype != TOC_NODE2)
            {
               i = 0;
            }
         }
         else if (html_merge_node4)
         {
            if (toc[i]->toctype != TOC_NODE1 && toc[i]->toctype != TOC_NODE2 && toc[i]->toctype != TOC_NODE3)
            {
               i = 0;
            }
         }
         else if (html_merge_node5)
         {
            if (toc[i]->toctype != TOC_NODE1 && toc[i]->toctype != TOC_NODE2 && toc[i]->toctype != TOC_NODE3 && toc[i]->toctype != TOC_NODE4)
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

      string2reference(anchor, lab[li], TRUE, GIF_RG_NAME, uiGifRgWidth, uiGifRgHeight);
      replace_once(s, lab[li]->name, anchor);

      if (no_images)
      {
         replace_once(s, lab[li]->name, " &gt;&gt;&gt;");
         strinsert(s, "| ");
      }
   
      out(s);
   }
   else
   {                                      /* disabled nach rechts */
      if (no_images)
      {
         outln("| &gt;&gt;&gt;");
      }
      else
      {
         get_giflink_data(GIF_NORG_INDEX, s, &uiW, &uiH);
         sGifSize[0] = EOS;
         
         if (uiW != 0 && uiH != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
         voutf("<img src=\"%s\" alt=\"\" title=\"\" border=\"0\"%s%s>", s, sGifSize, closer);
      }
   }
   
   if (html_modern_layout || html_frames_layout)
   {
      if (iDocHtmlSwitchLanguage >= 0 && sDocHtmlSwitchLanguage[0] != EOS)
      {
#if 1
         outln("</td><td valign=\"top\" align=\"right\">");
#endif
         if (no_images)
         {
            switch (iDocHtmlSwitchLanguage)
            {
            case TOGER:
               voutlnf("<a href=\"%s\">Deutsch</a>", sDocHtmlSwitchLanguage);
                  break;
            case TOENG:
               voutlnf("<a href=\"%s\">English</a>", sDocHtmlSwitchLanguage);
            }
         }
         else
         {
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
               get_giflink_data(GIF_GER_INDEX, sGifFile, &uiW, &uiH);
               
               if (uiW != 0 && uiH != 0)
               {
                  sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
               }
                                          /* Changed in r6pl16 [NHz] */
               voutlnf("<a href=\"%s\"%s><img src=\"%s\" alt=\"Deutsch\" title=\"Deutsche Version dieses Dokuments\" border=\"0\"%s%s></a>",
                  sDocHtmlSwitchLanguage, sTarget, sGifFile, sGifSize, closer);
               break;
               
            case TOENG:
               get_giflink_data(GIF_ENG_INDEX, sGifFile, &uiW, &uiH);
               
               if (uiW != 0 && uiH != 0)
               {
                  sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
               }
                                          /* Changed in r6pl16 [NHz] */
               voutlnf("<a href=\"%s\"%s><img src=\"%s\" alt=\"English\" title=\"English version of this document\" border=\"0\"%s%s></a>",
                  sDocHtmlSwitchLanguage, sTarget, sGifFile, sGifSize, closer);
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
         
         if (html_doctype < XHTML_STRICT)
            outln(HTML_HR);
         else
            outln(XHTML_HR);
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
   register int   i;                 /* */
   int            li;                /* */
   UWORD          uiW,               /* */
                  uiH;               /* */
   char           the_ref[1024],     /* */
                 *ptrImg,            /* */
                 *ptr;               /* */
   char          *noImg = "";        /* */
   char           sGifSize[80],      /* */
                  sAlignOn[128],     /* */
                  sAlignOff[128];    /* */
   char           closer[8] = "\0";  /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   sGifSize[0] = EOS;
   
#if 1
   /* Changed in V6.5.9 [NHz] */
   voutlnf("<table id=\"UDO_menu\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"%s\">", html_modern_width);
   
   switch (html_modern_alignment)
   {
   case ALIGN_LEFT:
      sprintf(sAlignOn, "<tr><td>%s", sHtmlPropfontStart);
      sprintf(sAlignOff, "%s</td></tr>", sHtmlPropfontEnd);
      break;
   case ALIGN_CENT:
      sprintf(sAlignOn, "<tr><td align=\"center\">%s", sHtmlPropfontStart);
      sprintf(sAlignOff, "%s</td></tr>", sHtmlPropfontEnd);
      break;
   case ALIGN_RIGH:
      sprintf(sAlignOn, "<tr><td align=\"right\">%s", sHtmlPropfontStart);
      sprintf(sAlignOff, "%s</td></tr>", sHtmlPropfontEnd);
   }
#else
   strcpy(sAlignOn, "<center>");
   strcpy(sAlignOff, "</center>");
#endif
   
   
   
   if (p2_toc_counter == 0 && titdat.authoricon_active != NULL)
   {
      if (titdat.authoriconActiveWidth != 0 && titdat.authoriconActiveHeight != 0)
      {
         sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconActiveWidth, titdat.authoriconActiveHeight);
      }
      
      voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" alt=\"\" title=\"\" border=\"0\"%s%s></a>%s",
         sAlignOn, old_outfile.name, outfile.suff, titdat.authoricon_active, sGifSize, closer, sAlignOff);
   }
   else
   {
      if (titdat.authoricon != NULL)
      {
         if (titdat.authoriconWidth != 0 && titdat.authoriconHeight != 0)
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconWidth, titdat.authoriconHeight);
         }
         
         voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" alt=\"\" title=\"\" border=\"0\"%s%s></a>%s",
            sAlignOn, old_outfile.name, outfile.suff, titdat.authoricon, sGifSize, closer, sAlignOff);
      }
   }
   
   if (toc[0]->icon != NULL)              /*r6pl13*/
   {
      ptrImg = noImg;
      uiW = uiH = 0;
      
      if (toc[0]->icon != NULL)           /* fd:20071114: ??? */
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
         {
            sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
         }
         
                                          /*r6pl13*/
         voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" alt=\"\" title=\"\" border=\"0\"%s%s></a>%s",
            sAlignOn, old_outfile.name, outfile.suff, ptrImg, sGifSize, closer, sAlignOff);
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
            
            string2reference(the_ref, lab[li], FALSE, ptrImg, uiW, uiH);
            
            if (ptrImg != noImg && toc[i]->icon_text != NULL)
            {
               ptr = strstr(the_ref, "</a>");
               
               if (ptr != NULL)
               {
                  strinsert(ptr, toc[i]->icon_text);
                  
                  if (html_doctype < XHTML_STRICT)
                     strinsert(ptr, "<br>");
                  else
                     strinsert(ptr, "<br />");
               }
            }
                                          /*r6pl3*/
            voutlnf("%s%s%s", sAlignOn, the_ref, sAlignOff);
         }
      }
      else
      {
         break;
      }
   }
   
#if 1
   outln("</table>");
#endif
   
}       /* html_node_bar_modern */





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
   char   add[1024],         /* */
          add2[256],         /* */
          s[512],            /* */
          f1[512],           /* */
          f2[512];           /* */
   char   closer[8] = "\0";  /* single tag closer mark in XHTML */
   
   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   
   /* New in r6pl16 [NHz] */
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
                                          /*r6pl5*/
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
   
   if (html_frames_toc_title == NULL)     /* Change in 6.5.16 [GS] */
   {
      sprintf(f1, "<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\"%s%s>",
      html_name_prefix, FRAME_FILE_TOC, outfile.suff, FRAME_NAME_TOC, add2, closer);
   }
   else
   {
      sprintf(f1, "<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\" title=\"%s\"%s%s>",
      html_name_prefix, FRAME_FILE_TOC, outfile.suff, FRAME_NAME_TOC, html_frames_toc_title, add2, closer);
   }
   
   if (html_frames_con_title == NULL)     /* Change in 6.5.16 [GS] */
   {
      sprintf(f2, "<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\"%s>",
      html_name_prefix, FRAME_FILE_CON, outfile.suff, FRAME_NAME_CON, closer);
   }
   else
   {
      sprintf(f2, "<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\" title=\"%s\"%s>",
      html_name_prefix, FRAME_FILE_CON, outfile.suff, FRAME_NAME_CON, html_frames_con_title, closer);
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
   }
   
   outln("</frameset>");
   
   /* New in r6pl15 [NHz] */
   
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
   
   if (html_frames_backimage[0] != EOS)
   {
      sprintf(s, " background=\"%s\"", html_frames_backimage);
      strcat(add, s);
   }
   
   if (html_frames_backcolor[0] != EOS)
   {
      sprintf(s, " bgcolor=\"%s\"", html_frames_backcolor);
      strcat(add, s);
   }
   
   if (html_frames_linkcolor[0] != EOS)
   {
      sprintf(s, " link=\"%s\"", html_frames_linkcolor);
      strcat(add, s);
   }
   
   if (html_frames_alinkcolor[0] != EOS)
   {
      sprintf(s, " alink=\"%s\"", html_frames_alinkcolor);
      strcat(add, s);
   }
   
   if (html_frames_vlinkcolor[0] != EOS)
   {
      sprintf(s, " vlink=\"%s\"", html_frames_vlinkcolor);
      strcat(add, s);
   }
                                          /* Changed in r6pl16 [NHz] */
   voutlnf("<body%s class=\"frame_toc\">", add);
   
   outln(sHtmlPropfontStart);
   html_node_bar_frames();
   voutlnf("%s", sHtmlPropfontEnd);
   outln("</body>");
   outln("</html>");
   
   /* Neue Datei fuer das erste Kapitel anlegen */
   
   sprintf(outfile.name, "%s%s", html_name_prefix, FRAME_FILE_CON);
   html_make_file();
   
}       /* html_save_frameset */ 





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
   register int   i;                 /* */
   int            li;                /* */
   UWORD          uiW,               /* */
                  uiH;               /* */
   char           the_ref[1024],     /* */
                 *ptr,               /* */
                 *ptrImg,            /* */
                  sGifSize[80];      /* */
   char           alignOn[128],      /* */
                  alignOff[128],     /* */
                  divOn[32],         /* */
                  divOff[32],        /* */
                  rowOn[16],         /* */
                  rowOff[16];        /* */
   char          *noImg= "";         /* */
   char           closer[8] = "\0";  /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   
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
         sprintf(alignOn, "<tr><td align=\"center\">%s", sHtmlPropfontStart);
         sprintf(alignOff, "%s</td></tr>", sHtmlPropfontEnd);
         break;
      case ALIGN_RIGH:
         sprintf(alignOn, "<tr><td align=\"right\">%s", sHtmlPropfontStart);
         sprintf(alignOff, "%s</td></tr>", sHtmlPropfontEnd);
      }
      
      outln(divOn);
      outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\">");
      outln(rowOn);
      break;
      
   default:
      sprintf(alignOn, "<td nowrap=\"nowrap\">%s", sHtmlPropfontStart);
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
         strcpy(divOn, "<div align=\"center\">");
         strcpy(divOff, "</div>");
         break;
      case ALIGN_RIGH:
         strcpy(divOn, "<div align=\"right\">");
         strcpy(divOff, "</div>");
      }
      
      outln(divOn);
      outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">");
      outln(rowOn);
   }
   
   
   if (titdat.authoricon != NULL)
   {
      sGifSize[0] = EOS;
      
      if (titdat.authoriconWidth != 0 && titdat.authoriconHeight != 0)
      {
         sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconWidth, titdat.authoriconHeight);
      }
      
      voutlnf("%s<a href=\"%s%s%s\" target=\"%s\"><img src=\"%s%s\" alt=\"\" title=\"\" border=\"0\"%s%s></a>%s",
         alignOn, html_name_prefix, FRAME_FILE_CON, outfile.suff,
         FRAME_NAME_CON, titdat.authoricon, "" /*sDocImgSuffix*/, sGifSize, closer, alignOff);
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
            
            string2reference(the_ref, lab[li], FALSE, ptrImg, uiW, uiH);
   
            /* Im Inhaltsverzeichnis DARF nicht <a href="#..."> stehen! */
            /* kleiner Zwischenhack, da Frames mit gemergten Nodes wohl */
            /* niemand ernsthaft verwenden werden wird. */
            
            ptr= strstr(the_ref, "href=\"#");
            
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
                  
                  if (html_doctype < XHTML_STRICT)
                     strinsert(ptr, "<br>");
                  else
                     strinsert(ptr, "<br />");
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
   char   bgCmd[512];  /* */
   
   
   if (html_modern_layout)
   {
      bgCmd[0] = EOS;
      
      if (html_modern_backimage[0] != EOS)
         sprintf(bgCmd, " background=\"%s\"", html_modern_backimage);

      outln("<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" width=\"100%\">");
      outln("<tr>");
      
      if (html_modern_backcolor[0] != EOS)
      {
         voutlnf("<td valign=\"top\" width=\"%s\" bgcolor=\"%s\"%s>%s",
            html_modern_width,            /* */
            html_modern_backcolor,        /* */
            bgCmd,                        /* */
            sHtmlPropfontStart);          /* */
      }
      else
      {
         voutlnf("<td valign=\"top\" width=\"%s\"%s>%s", 
            html_modern_width,            /* */
            bgCmd,                        /* */
            sHtmlPropfontStart);          /* */
      }
      
      html_node_bar_modern();
      voutlnf("%s</td>", sHtmlPropfontEnd);

#if 0
                                          /*r6pl3*/
      outln("<td valign=\"top\" width=\"8\">&nbsp;</td>");
#endif

      voutlnf("<td valign=\"top\" width=\"100%%\">%s", sHtmlPropfontStart);
   }
   
   if (!no_headlines)
      html_hb_line(TRUE);

#if 1
   if (html_modern_layout || html_frames_layout)
   {
      outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\">\n<tr>");
      voutlnf("<td valign=\"top\" width=\"8\">&nbsp;</td><td valign=\"top\" width=\"100%%\">%s", sHtmlPropfontStart);
   }
#endif
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
*     the output, the contact_link is used as it was setted by
*     !docinfo [webmaster_contact_link]. So mail addresses must be set as
*     "mailto:webmaster@example.com".
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void html_footer(void)
{
   BOOLEAN   has_counter,       /* */
             has_main_counter;  /* */
   char      s[512];            /* */
   int       has_content = 0;   /* flags */
   
   
                                          /* Changed in V6.5.9 [NHz] */
   has_counter = (toc[p2_toc_counter]->counter_command != NULL);

   has_main_counter = (sCounterCommand[0] != EOS);
   
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
      outln(toc[p2_toc_counter]->counter_command);
   }
   else if (has_main_counter)             /* New in V6.5.9 [NHz] */
   {
      outln(sCounterCommand);
   }
   
   if (no_footers)                        /* New in V6.5.9 [NHz] */
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
   sprintf(footer_buffer, "<address>%sCopyright &copy; ", sHtmlPropfontStart);
   
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





/* GLOBAL MYFILE   udofile; */

/* --------------------------------------------------------------
   * Dateinamen zusammenbasteln
   --------------------------------------------------------------  */
LOCAL void udofile_adjust_index(void)
{

#if HAVE_TMPNAM

   char t[512];

   if (tmpnam(t)!=NULL)
   {  
      strcpy(udofile.full, t);
   }
   else
   {  strcpy(udofile.full, "_udoind.tmp");
   }

#else

   char  *tp;

   tp= NULL;

   if ((tp=getenv("TEMP"))==NULL)
   {  if ((tp=getenv("TMP"))==NULL)
      {  tp=getenv("TMPDIR");
      }
   }

   if (tp!=NULL)
   {  fsplit(tp, tmp_driv, tmp_path, tmp_name, tmp_suff);
      strcpy(udofile.driv, tmp_driv);
      strcpy(udofile.path, tmp_path);
   }
   else
   {  strcpy(udofile.driv, outfile.driv);
      strcpy(udofile.path, outfile.path);
   }

   strcpy(udofile.name, "_udoind");
   strcpy(udofile.suff, ".tmp");

   sprintf(udofile.full, "%s%s%s%s", udofile.driv, udofile.path, udofile.name, udofile.suff);
#endif

}  /* udofile_adjust_index */





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
   HTML_INDEX *p1 = (HTML_INDEX *)_p1;
   HTML_INDEX *p2 = (HTML_INDEX *)_p2;

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

GLOBAL BOOLEAN save_html_index(void)
{
   FILE        *uif;              /* ^ to temporary index file */
   size_t       i;                /* counter */
   int          j;                /* counter */
   int          html_merge;       /* */
   size_t       num_index;        /* # of entries in index file */
   HTML_INDEX  *html_index;       /* ^ to HTML_INDEX array */
   UWORD        thisc,            /* single char for comparison */
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

   udofile_adjust_index();                /* create temp. file name */

   uif = myFwopen(udofile.full, TOASC);   /* create temporary index file */

   if (!uif)                              /* no file pointer */
      return FALSE;
   
   fprintf(uif, "!newpage\n");            /* output index page stuff in UDO format */
   fprintf(uif, "!sloppy\n\n");
   fprintf(uif, "!node* %s\n", lang.index);
   fprintf(uif, "!html_name indexudo\n");
   
   if (!bDocAutorefOff)                   /* don't auto-reference the index page! */
      fprintf(uif, "!autoref [off]\n");

                                          /* we need memory */   
   html_index = (HTML_INDEX *)um_malloc(num_index * sizeof(HTML_INDEX));
   
   if (html_index == NULL)                /* fatal error! */
   {
      fclose(uif);
      error_malloc_failed();
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
   
   fprintf(uif, jumplist);                /* output A-Z jumplist */
   
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
            fprintf(uif, "<span class=\"UDO_index_name\"><a name=\"%s\"></a>%s</span>%s\n",
               thisc_label, thisc_char, HTML_BR);
         }
         else
            fprintf(uif, "<a name=\"%s\"></a>\n", thisc_label);
         
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
      
      um_free(escapedtocname);            /* v6.5.15 [vj] var can be freed now */
   }
   
   fprintf(uif, "</p>\n\n");
   
   fprintf(uif, jumplist);                /* repeat A-Z jumplist */
   
   fprintf(uif, "!end_raw\n");
   
   fclose(uif);
   
   token_reset();
   
   strcpy(token[0], "!include");          /* sollte safe sein, da ein Token auf jeden Fall so lang werden kann :-) [vj] */
   
   um_strcpy(token[1], udofile.full, MAX_TOKEN_LEN+1, "save_html_index [2]");
   
   token_counter = 2;
   
   c_include();   
   
   remove(udofile.full);

   um_free((void *)html_index);
   
   return TRUE;
}





/* --------------------------------------------------------------
   --------------------------------------------------------------  */

GLOBAL void add_pass1_index_udo(void)
{
   save_html_index();
   token_reset();

}  /* add_pass1_index_udo */

/*      ############################################################
        #
        # Spezielles fuer HTML Help
        #
        ############################################################    */

GLOBAL void hh_headline(void)
{
#if 0
        if (!no_headlines)
        {       html_hb_line(TRUE);
        }
#endif
}       /* hh_headline */


GLOBAL void hh_bottomline(void)
{
#if 0
        if (!no_bottomlines)
        {       html_hb_line(FALSE);
        }
#endif
}       /* hh_bottomline */



LOCAL void print_htmlhelp_contents(FILE *file, const char *indent, const int ti)
{
        char filename[512], tocname[512];
        int  html_merge;

        if (ti>0)
        {
                get_html_filename(ti, filename, &html_merge);
                um_strcpy(tocname, toc[ti]->name, 512, "print_htmlhelp_contents[1]");
        }
        else
        {
                strcpy(filename, old_outfile.name);
                tocname[0]= EOS;
                if (tocname[0]==EOS && titleprogram[0]!=EOS)    um_strcpy(tocname, titleprogram, 512, "print_htmlhelp_contents[2]");
                if (tocname[0]==EOS && called_tableofcontents)  um_strcpy(tocname, lang.contents, 512, "print_htmlhelp_contents[3]");
                if (tocname[0]==EOS && called_maketitle)                um_strcpy(tocname, lang.title, 512, "print_htmlhelp_contents[4]");
        }
        del_html_styles(tocname);

    fprintf(file, "%s<li><object type=\"text/sitemap\">\n", indent);
        fprintf(file, "%s<param name=\"Name\" value=\"%s\">\n", indent, tocname);
        fprintf(file, "%s<param name=\"Local\" value=\"%s%s\">\n", indent, filename, outfile.suff);
    fprintf(file, "%s</object>\n", indent);

}       /* print_htmlhelp_contents */


GLOBAL BOOLEAN save_htmlhelp_contents(const char* filename)
{
        FILE *file;

        register int i;
        BOOLEAN last_n= TRUE;
        BOOLEAN last_sn= FALSE;
        BOOLEAN last_ssn= FALSE;
        BOOLEAN last_sssn= FALSE;
        BOOLEAN last_ssssn= FALSE;
        BOOLEAN inApx= FALSE;

        file= myFwopen(filename, FTHHC);

        if (!file)
        {       return FALSE;
        }

        save_upr_entry_outfile(filename);

        fprintf(file, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n");
   fprintf(file, "<html>\n");
   fprintf(file, "<head>\n");
        fprintf(file, "<meta name=\"GENERATOR\" content=\"UDO Version %s.%s %s for %s\">\n",
                                                UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS);
        fprintf(file, "<!-- Sitemap 1.0 -->\n");
        fprintf(file, "</head>\n");
        fprintf(file, "<body>\n");
        fprintf(file, "<ul>\n");

        print_htmlhelp_contents(file, "\t", 0); /* r6pl10: Eintrag fuer erste Seite */
        fprintf(file, "</ul>\n");
   fprintf(file, "<ul>\n");

        for (i=1; i<=p1_toc_counter; i++)
        {
                if (toc[i]!=NULL && !toc[i]->invisible)
                {
                        convert_toc_item(toc[i]);

                        if (!inApx && toc[i]->appendix)
                        {       /* r6pl13: Anhang mit ausgeben, hier den ersten Node im Anhang */
                                inApx= TRUE;
                                if (last_n)             fprintf(file, "</ul>\n");
                                if (last_sn)    fprintf(file, "\t</ul>\n</ul>\n");
                                if (last_ssn)   fprintf(file, "\t\t</ul>\n\t</ul>\n</ul>\n");
                                if (last_sssn)  fprintf(file, "\t\t\t</ul>\n\t\t</ul>\n\t</ul>\n</ul>\n");
                                if (last_ssssn)  fprintf(file, "\t\t\t\t</ul>\n\t\t\t</ul>\n\t\t</ul>\n</ul>\n</ul>\n");
                                last_n= last_sn= last_ssn= last_sssn= last_ssssn= FALSE;
#if 0
                                fprintf(file, "<ul>\t<li><object type=\"text/sitemap\">\n");
                                fprintf(file, "\t\t<param name=\"Name\" value=\"%s\">\n", lang.appendix);
                                fprintf(file, "\t\t</object>\n");
#endif
                                fprintf(file, "<ul>\n");
                        }
/* ToDo: last_ssssn */

                        if (toc[i]->n1 != 0)
                        {
                                if (toc[i]->toctype==TOC_NODE1)
                                {       /* Ein Kapitel */       

                                        if (last_sn)    {       fprintf(file, "\t</ul>\n");                                                     last_sn= FALSE;         }
                                        if (last_ssn)   {       fprintf(file, "\t\t</ul>\n\t</ul>\n");                          last_ssn= FALSE;        }
                                        if (last_sssn)  {       fprintf(file, "\t\t\t</ul>\n\t\t</ul>\n\t</ul>\n");     last_sssn= FALSE;       }
                                        last_n= TRUE;
                                        print_htmlhelp_contents(file, "\t", i);

                                }/* TOC_NODE1 */
                                        
                                        
                                if (toc[i]->toctype==TOC_NODE2)
                                {       /* Ein Abschnitt */
                                        if (last_n)             {       fprintf(file, "\t<ul>\n");                                      last_n= FALSE;          }
                                        if (last_ssn)   {       fprintf(file, "\t\t</ul>\n");                           last_ssn= FALSE;        }
                                        if (last_sssn)  {       fprintf(file, "\t\t\t</ul>\n\t\t</ul>\n");      last_sssn= FALSE;       }
                                        last_sn= TRUE;
                                        print_htmlhelp_contents(file, "\t\t", i);

                                }/* TOC_NODE2 */
                                        
                                if (toc[i]->toctype==TOC_NODE3)
                                {       /* Ein Unterabschnitt */
                                        if (last_n)             {       fprintf(file, "<ul>\n\t<ul>\n");        last_n= FALSE;          }
                                        if (last_sn)    {       fprintf(file, "\t\t<ul>\n");            last_sn= FALSE;         }
                                        if (last_sssn)  {       fprintf(file, "\t\t\t</ul>\n");         last_sssn= FALSE;       }
                                        last_ssn= TRUE;
                                        print_htmlhelp_contents(file, "\t\t\t", i);

                                }/* TOC_NODE3 */
                                        
                                        
                                if (toc[i]->toctype==TOC_NODE4)
                                {       /* Ein Paragraph */
                                        if (last_n)             {       fprintf(file, "\t<ul>\n\t\t<ul>\n\t\t\t<ul>\n");        last_n= FALSE;          }
                                        if (last_sn)    {       fprintf(file, "\t<ul>\n\t\t<ul>\n");                            last_sn= FALSE;         }
                                        if (last_ssn)   {       fprintf(file, "\t\t\t<ul>\n");                                          last_ssn= FALSE;        }
                                        last_sssn= TRUE;
                                        print_htmlhelp_contents(file, "\t\t\t\t", i);

                                }/* TOC_NODE4 */

                        }/* toc[i]->n1 > 0 */

                }/* toc[i]!=NULL && !toc[i]->invisible */

        }/* for */


        if (last_sn)    fprintf(file, "\t</ul>\n</ul>\n");
        if (last_ssn)   fprintf(file, "\t\t</ul>\n\t</ul>\n");
        if (last_sssn)  fprintf(file, "\t\t\t</ul>\n\t\t</ul>\nswitch (</ul>\n");

#if 0
        if (inApx)              fprintf(file, "</ul>\n");
#endif

        fprintf(file, "</ul>\n");
        fprintf(file, "</body>\n</html>\n");

        fclose(file);

        return TRUE;

}       /* save_htmlhelp_contents */


typedef struct _hmtl_idx {
        int toc_index;
        char tocname[512];
} HTML_IDX;

LOCAL int comp_index(const void *_p1, const void *_p2)
{
        const HTML_IDX *p1 = (const HTML_IDX *)_p1;
        const HTML_IDX *p2 = (const HTML_IDX *)_p2;

        return strcmp(p1->tocname, p2->tocname);
}


GLOBAL BOOLEAN save_htmlhelp_index(const char* filename)
{
        FILE *file;
        size_t i;
        int j;
        int  html_merge;
        size_t num_index;
        HTML_IDX *html_index;
        char htmlname[512];
        char *tocname;

        /* erstmal zaehlen wieviel wir brauchen */
        num_index = 0;
#if 0
        for (i = 1; i <= p1_toc_counter; i++)
        {
                if (toc[i] != NULL && !toc[i]->invisible)
                        num_index++;
        }
#endif
        for (j = 1; j <= p1_lab_counter; j++)
                if (lab[j] != NULL)
                        num_index++;

        if (num_index == 0)
                return FALSE;   /* Index-File wird nicht gebraucht */

        file = myFwopen(filename, FTHHK);

        if (file == NULL)
        {
                return FALSE;
        }
        html_index = (HTML_IDX *)um_malloc(num_index * sizeof(HTML_IDX));
        if (html_index == NULL)
        {
                fclose(file);
                error_malloc_failed();
                return FALSE;
        }

        save_upr_entry_outfile(filename);

        fprintf(file, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n");
        fprintf(file, "<html>\n");
        fprintf(file, "<head>\n");
        fprintf(file, "<meta name=\"Generator\" content=\"UDO Version %s.%s %s for %s\">\n",
                                                UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS);
        if (titdat.author != NULL)
                fprintf(file, "<meta name=\"Author\" content=\"%s\">\n", titdat.author);
        fprintf(file, "<!-- Sitemap 1.0 -->\n");
        fprintf(file, "</head>\n");
        fprintf(file, "<body>\n");
        fprintf(file, "<ul>\n");

        /* array aufbauen.. */
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
        for (j = 1; j <= p1_lab_counter; j++)
        {
                if (lab[j] != NULL)
                {
                        html_index[num_index].toc_index = lab[j]->tocindex;
                        tocname = html_index[num_index].tocname;
                        strcpy(tocname, lab[j]->name);
                        replace_macros(tocname);
                        c_internal_styles(tocname);
                        /* replace_udo_quotes(tocname); */
                        delete_all_divis(tocname);
                        replace_udo_tilde(tocname);
                        replace_udo_nbsp(tocname);
                        del_html_styles(tocname);
                        num_index++;
                }
        }
        /* ..sortieren */
        qsort(html_index, num_index, sizeof(HTML_IDX), comp_index);

        /* ..und ausgeben */
        for (i = 0; i < num_index; i++)
        {
                get_html_filename(html_index[i].toc_index, htmlname, &html_merge);
                fprintf(file, "<li><object type=\"text/sitemap\"> <param name=\"Name\" value=\"%s\"> <param name=\"Local\" value=\"%s%s\"></object></li>\n",
                        html_index[i].tocname,
                        htmlname, outfile.suff);
        }

        fprintf(file, "</ul>\n");
        fprintf(file, "</body>\n");
        fprintf(file, "</html>\n");
        fclose(file);

        um_free((void *) html_index);

        return TRUE;
}       /* save_htmlhelp_index */










/*******************************************************************************
*
*     CHAPTER COMMANDS
*
******************************************|************************************/

/*******************************************************************************
*
*  make_node():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void make_node(

const BOOLEAN   popup,             /* TRUE: this is a popup node */
const BOOLEAN   invisible)         /* TRUE: this is an invisible node */
{
   char         n[512],            /* */
                name[512],         /* */
                stgname[512],      /* */
                numbers[512],      /* */
                nameNoSty[512];    /* */
   char         map[64],           /* */
                sGifSize[80],      /* */
                nodename[512];     /* */
   int          ti,                /* */
                chapter,           /* */
                nr1;               /* */
   BOOLEAN       flag;              /* */
   BOOLEAN      do_index;          /* */
   char         closer[8] = "\0";  /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   
   if (p2_toc_counter >= MAXTOCS)         /* r5pl2 */
   {
      bBreakInside = TRUE;
      return;
   }
   
   tokcpy2(name, 512);
   strcpy(stgname, name);                 /* r5pl14 */


   if (name[0] == EOS)
   {
      error_missing_parameter("!node");
      return;
   }
   
   p2_lab_counter++;                      /*r6pl2*/
   p2_toctype= TOC_NODE1;                 /*r6pl5*/
   
   if ((desttype == TOHTM || desttype == TOHAH) && !html_merge_node1)
   {
      check_endnode();
      html_bottomline();
   }
   
   if (desttype == TOMHH)
   {
      check_endnode();
      hh_bottomline();
   }
   
   check_styles(name);                    /*r6pl3*/
   c_styles(name);
   
   switch (desttype)                      /*r5pl3*/
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
      p2_apx_n1++;
      p2_apx_n2 = 0;
      p2_apx_n3 = 0;
      p2_apx_n4 = 0;
      p2_apx_n5 = 0;
   }
   else
   {
      p2_toc_n1++;
      p2_toc_n2 = 0;
      p2_toc_n3 = 0;
      p2_toc_n4 = 0;
      p2_toc_n5 = 0;
   }
   
   p2_toc_counter++;
   curr_n1_index = p2_toc_counter;
   curr_n2_index = 0;
   curr_n3_index = 0;
   curr_n4_index = 0;
   
   last_n1_index = p2_toc_counter;
   last_n2_index = 0;
   last_n3_index = 0;
   last_n4_index = 0;
   last_n5_index = 0;
   
   nr1 = toc[p2_toc_counter]->nr1;
   
   (bInsideAppendix) ? (chapter = nr1) : (chapter = nr1 + toc_offset);
   
   n[0] = EOS;
   numbers[0] = EOS;
   
   if (!invisible)
   {
      if (bInsideAppendix)
      {
         sprintf(numbers, "%c", 'A'+ nr1 - 1);
      }
      else
      {
         sprintf(numbers, "%d", chapter); /* r5pl7: chapter statt nr1 */
      }
   }
   
   if (bVerbose)
   {
      sprintf(sInfMsg, "[%s] ", numbers);
      show_status_node(sInfMsg);
   }
   
   if (no_numbers || invisible)
   {
      numbers[0] = EOS;
   }
   else
   {
      strcat(numbers, " ");
   }
   
   strcpy(current_chapter_name, name);
   strcpy(current_chapter_nr, numbers);
   
                                          /* r5pl10 */
   do_index = (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index);

   
   switch (desttype)
   {
   case TOTEX:
   case TOPDL:
      set_inside_node1();
      
      if (invisible)
      {
         (use_style_book) ? voutlnf("\n\\chapter*{%s}", name) : voutlnf("\n\\section*{%s}", name);
      }
      else
      {
         (use_style_book) ? voutlnf("\n\\chapter{%s}", name) : voutlnf("\n\\section{%s}", name);
      }
      
      label2tex(name);                    /*r6pl2*/
      voutlnf("\\label{%s}", name);       /*r6pl2*/
      output_aliasses();
   
      if (desttype == TOPDL)              /*r6pl8*/
      {
         voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
         voutlnf("\\pdfoutline goto num %d count %d {%s}",
         p2_lab_counter, toc[p2_toc_counter]->count_n2, name);
      }
      
      break;
   
   case TOLYX:
      set_inside_node1();
      out("\\layout ");
      
      if (invisible)
      {
         (use_style_book) ? outln("Chapter") : outln("Section*");
      }
      else
      {
         (use_style_book) ? outln("Chapter") : outln("Section");
      }
      
      indent2space(name);
      outln(name);
      break;
   
   case TOINF:
      set_inside_node1();
      output_texinfo_node(name);
      
      if (bInsideAppendix)
      {
         voutlnf("@appendix %s", name);
      }
      else
      {
         (invisible) ? (voutlnf("@chapheading %s", name)) : (voutlnf("@chapter %s", name));
      }
      break;
   
   case TOTVH:
      set_inside_node1();
      if (numbers[0] != EOS)
         strcat(numbers, " ");
         
      output_vision_header(numbers, name);
      break;
   
   case TOSTG:
      set_inside_node1();
      bInsidePopup = popup;
   
      replace_2at_by_1at(name);
   
      node2stg(name);
   
      outln("");
      
      if (!do_index)
      {
         outln("@indexoff");
      }
      
      if (popup)
      {
         voutlnf("@pnode \"%s\"", name);
      }
      else
      {
         voutlnf("@node \"%s\"", name);
      }
      
      if (!do_index)
      {
         outln("@indexon");
      }
   
      if (!popup)
      {
         if (called_tableofcontents)
         {
            outln("@toc \"Main\"");
         }
      }
      
      stg_header(numbers, stgname, popup);
      break;
   
   case TOAMG:
      set_inside_node1();
      replace_2at_by_1at(name);
      
      node2stg(name);
      
      outln("");
      
      if (titleprogram[0] != EOS)
      {
         voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
      }
      else
      {
         voutlnf("@node \"%s\" \"%s\"", name, name);
      }
      
      if (called_tableofcontents)
      {
         outln("@toc \"Main\"");
      }
      
      stg_header(numbers, stgname, FALSE);
      break;
   
   case TOMAN:
      set_inside_node1();
      outln("");
      my_strupr(name);
      sprintf(n, " %s%s%s", BOLD_ON, name, BOLD_OFF);
      c_internal_styles(n);
      outln(n);
      break;
      
   case TONRO:
      set_inside_node1();
      my_strupr(name);
      sprintf(n, ".SH %s", name);
      c_internal_styles(n);
      outln(n);
      break;
      
   case TOASC:
      set_inside_node1();
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
      
      outln("");
      break;
      
   case TOKPS:
      set_inside_node1();

      if (use_style_book)
      {
         (bInsideAppendix) ? sprintf(n, "%s %s", lang.appendix, numbers) : sprintf(n, "%s %s", lang.chapter, numbers);
         del_right_spaces(n);
         
         if (n[0] != EOS)
            strcat(n, " ");

         strcat(n, name);
         outln("25 changeFontSize");
      }
      else
      {
         if (numbers[0] != EOS)
            strcat(numbers, " ");
         
         sprintf(n, "%s%s", numbers, name);
         
         /* Changed in r6pl16 [NHz] */
         /* Nodesize ist set on discrete value */
         voutlnf("%d changeFontSize", laydat.node1size);
      }
      
                                          /* Changed in r6pl16 [NHz] */
      node2postscript(name, KPS_NAMEDEST);
                                          /* Changed: Fixed bug #0000040 in r6.3pl16 [NHz] */
      um_strcpy(nodename, n, 511, "make_node TOKPS");
      node2postscript(nodename, KPS_NODENAME);
      voutlnf("/NodeName (%s %s) def", lang.chapter, nodename);
      outln("newline");
      voutlnf("/%s NameDest", name);      /* New in r6pl15 [NHz] */
      outln("Bon");
      
      node2postscript(n, KPS_CONTENT);    /* Changed in V6.5.5 [NHz] */
      voutlnf("(%s) udoshow", n);
      outln("Boff");
      outln("newline");
                                          /* Changed in r6pl15 [NHz] */
      voutlnf("%d changeFontSize", laydat.propfontsize);
   break;
   
   case TODRC:
      set_inside_node1();
      outln("%%*");
      
      if (p2_toc_counter + 1 <= p1_toc_counter && toc[p2_toc_counter + 1]->toctype == TOC_NODE2)
      {
         voutlnf("%%%% 0, %d, 0, 0, %d, %s", p2_toc_counter+10, iDrcFlags, name);
      }
      else
      {
         voutlnf("%%%% 0, 0, 0, 0, %d, %s", iDrcFlags, name);
      }
      
      outln("%%*");
      outln("");
      break;
      
   case TOIPF:
      set_inside_node1();
                                          /* r6pl2 */
      node2NrIPF(n, toc[p2_toc_counter]->labindex);
      map[0] = EOS;
      
      if (toc[p2_toc_counter]->mapping >= 0)
      {
         sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
      }
      
      if (bInsideAppendix)
      {
         voutlnf(":h1 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
      }
      else
      {
         voutlnf(":h1 id=%s%s.%s%s", n, map, numbers, name);
      }
      
      break;
      
   case TOSRC:
   case TOSRP:
      set_inside_node1();
      outln("");
      outln("");
      
      memset(n, '#', 62);
      n[62] = EOS;
      voutlnf("%s  %s", sSrcRemOn, n);
      outln("    #");
      outln("    #");
      
      voutlnf("    # %s", name);
      outln("    #");
      outln("    #");
      
      voutlnf("    %s  %s", n, sSrcRemOff);
      outln("");
      break;
      
   case TORTF:
      set_inside_node1();

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
      
      output_aliasses();
      
      /* New in V6.5.9 [NHz] [bookmark] */
      um_strcpy(n, name, 512, "make_node[RTF]");
      winspecials2ascii(n);
      node2winhelp(n);
      
      if (use_style_book)
      {
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
      }
      else
      {
         if (numbers[0] == EOS)
         {
            if (invisible)
            {                             /* Changed in V6.5.9 [NHz] */
                                          /* Nodesize ist set on discrete value */
               voutlnf("%s %s\\fs%d {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", 
                  rtf_plain, rtf_inv_node1, laydat.node1size, n, name, n, rtf_parpard);
            }
            else
            {                             /* Changed in V6.5.9 [NHz] */
                                          /* Nodesize ist set on discrete value */
               voutlnf("%s %s\\fs%d {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", 
                  rtf_plain, rtf_node1, laydat.node1size, n, name, n, rtf_parpard);
            }
         }
         else
         {
            if (invisible)
            {                             /* Changed in V6.5.9 [NHz] */
                                          /* Nodesize ist set on discrete value */
               voutlnf("%s %s\\fs%d %s  {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", 
                  rtf_plain, rtf_inv_node1, laydat.node1size, numbers, n, name, n, rtf_parpard);
            }
            else
            {                             /* Changed in V6.5.9 [NHz] */
                                          /* Nodesize ist set on discrete value */
               voutlnf("%s %s\\fs%d %s  {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", 
                  rtf_plain, rtf_node1, laydat.node1size, numbers, n, name, n, rtf_parpard);
            }
         }
      }
      
      voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);
      break;
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
      set_inside_node1();
      output_win_header(name, invisible);
      output_aliasses();
      
      if (use_style_book)
      {
         (bInsideAppendix) ? sprintf(n, "%s %s\\par %s", lang.appendix, numbers, name) : sprintf(n, "%s %s\\par %s", lang.chapter, numbers, name);
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
      set_inside_node1();
      if (numbers[0] != EOS)
         strcat(numbers, " ");

      output_pch_header(numbers, name);
      break;
      
   case TOHAH:                            /* V6.5.17 */
   case TOHTM:
   case TOMHH:
      ti= p2_toc_counter;
      
      if (!html_merge_node1)
      {
         if (!html_new_file())
            return;
      }
      else
      {
         output_aliasses();
         
         if (html_doctype < XHTML_STRICT)
            outln(HTML_HR);
         else
            outln(XHTML_HR);
      }
      
      set_inside_node1();
      flag = FALSE;
      
      do_toptoc(TOC_NODE1);               /*r6pl5*/
      
      if (use_chapter_images)
      { 
         if (ti >= 0 && toc[ti]->image != NULL)
         {
            sGifSize[0] = EOS;
            
            if (toc[ti]->uiImageWidth != 0 && toc[ti]->uiImageHeight != 0)
            {
               sprintf(sGifSize, " width=\"%u\" height=\"%u\"",
                  toc[ti]->uiImageWidth, toc[ti]->uiImageHeight);
            }
                                          /* r5pl4 */
            voutlnf("<h%d><p align=\"center\">", html_nodesize);
               
            voutlnf("<img src=\"%s%s\" alt=\"%s%s\" title=\"%s%s\" border=\"0\"%s%s>",
               toc[ti]->image, sDocImgSuffix, numbers, name, numbers, name, sGifSize, closer);
                  
                                          /* r5pl4 */
            voutlnf("</p></h%d>", html_nodesize);
            
            flag = TRUE;
         }
      }
      
      if (!flag && !toc[ti]->ignore_title)
      { 
         strcpy(nameNoSty, name);
         del_html_styles(nameNoSty);
      
         label2html(nameNoSty);           /*r6pl2*/
         
                                          /* r5pl4 */
         voutlnf("\n<h%d><a name=\"%s\"></a>%s%s</h%d>\n",
            html_nodesize, nameNoSty, numbers, name, html_nodesize);
      }
      
      if (show_variable.source_filename)  /* V6.5.19 */
                                          /* V6.5.18 */
         voutlnf("<!-- %s: %li -->", toc[p2_toc_counter]->source_filename, 
            toc[p2_toc_counter]->source_line);
      
      break;
      
   case TOLDS:
      set_inside_node1();
      (use_style_book) ? voutlnf("<chapter>%s<label id=\"%s\">", name, name) : voutlnf("<sect>%s<label id=\"%s\">", name, name);
      output_aliasses();                  /* r5pl8 */
      outln("<p>");
      break;
   
   case TOHPH:
      set_inside_node1();
      (use_style_book) ? voutlnf("<chapter>%s", name) : voutlnf("<s1>%s", name);
      output_aliasses();
   }
   
}  /* make_node() */





/*******************************************************************************
*
*  make_subnode():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void make_subnode(

const BOOLEAN   popup,             /* TRUE: this is a popup node */
const BOOLEAN   invisible)         /* TRUE: this is an invisible node */
{
        char    n[512], name[512], stgname[512], hx_start[16], hx_end[16], sTemp[512];
        char    numbers[512], nameNoSty[512], k[512]; /* Changed in V6.5.9 [NHz] */
        char    map[64], sGifSize[80];
        int             ti, ui, chapter, nr1, nr2;
        BOOLEAN flag;
        BOOLEAN do_index;

        if (p2_toc_counter>=MAXTOCS)    /* r5pl2 */
        {       bBreakInside= TRUE;
                return;
        }

        tokcpy2(name, 512);
        strcpy(stgname, name);

        if (name[0]==EOS)
        {       error_missing_parameter("!subnode");
                return;
        }

        p2_lab_counter++;               /*r6pl2*/
        p2_toctype= TOC_NODE2;  /*r6pl5*/

        if ((desttype==TOHTM || desttype==TOHAH) && !html_merge_node2)
        {       check_endnode();
                html_bottomline();
        }

        if (desttype==TOMHH)
        {       check_endnode();
                hh_bottomline();
        }

        check_styles(name);                     /*r6pl3*/
        c_styles(name);
        switch (desttype)                       /* r5pl3 */
        {       case TOWIN:
                case TOWH4:
                case TOAQV:     c_win_styles(name);     break;
                case TORTF:     c_rtf_styles(name);     c_rtf_quotes(name);     break;
                default:        c_internal_styles(name); break;
        }
        replace_udo_quotes(name);
        delete_all_divis(name);
        replace_udo_tilde(name);
        replace_udo_nbsp(name);

        check_endnode();        
        check_styleflags();
        check_environments_node();

        if (bInsideAppendix)
        {       p2_apx_n2++;
                p2_apx_n3= 0;
                p2_apx_n4= 0;
                p2_apx_n5= 0;
        }
        else
        {       p2_toc_n2++;
                p2_toc_n3= 0;
                p2_toc_n4= 0;
                p2_toc_n5= 0;
        }

        p2_toc_counter++;
        curr_n2_index= p2_toc_counter;
        curr_n3_index= 0;
        curr_n4_index= 0;

        last_n2_index= p2_toc_counter;
        last_n3_index= 0;
        last_n4_index= 0;
        last_n5_index= 0;

        nr1= toc[p2_toc_counter]->nr1;
        nr2= toc[p2_toc_counter]->nr2;
        (bInsideAppendix) ? (chapter= nr1) : (chapter= nr1+toc_offset);

        n[0]= EOS;
        numbers[0]= EOS;

        if (!invisible)
        {       if (bInsideAppendix)
                {       sprintf(numbers, "%c.%d", 'A'+nr1-1, nr2+subtoc_offset);
                }
                else
                {       sprintf(numbers, "%d.%d", chapter, nr2+subtoc_offset);
                }
        }

        if (bVerbose)
        {       sprintf(sInfMsg, "[%s] ", numbers);
                show_status_node(sInfMsg);
        }

        if (no_numbers || invisible)
        {       numbers[0]= EOS;
        }
        else
        {       strcat(numbers, " ");
        }

        strcpy(current_chapter_name, name);
        strcpy(current_chapter_nr, numbers);

        do_index= (use_nodes_inside_index && !no_index &&
                                        !toc[p2_toc_counter]->ignore_index);    /* r5pl10 */

        switch (desttype)
        {
                case TOTEX:
                case TOPDL:
                        set_inside_node2();
                        if (invisible)
                        {       (use_style_book)        ? voutlnf("\n\\section*{%s}", name)
                                                                        : voutlnf("\n\\subsection*{%s}", name);
                        }
                        else
                        {       (use_style_book)        ? voutlnf("\n\\section{%s}", name)
                                                                        : voutlnf("\n\\subsection{%s}", name);
                        }
                        label2tex(name);                                /*r6pl2*/
                        voutlnf("\\label{%s}", name);   /*r6pl2*/
                        output_aliasses();
                        if (desttype==TOPDL)    /*r6pl8*/
                        {
                                voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
                                voutlnf("\\pdfoutline goto num %d count %d {%s}",
                                        p2_lab_counter, toc[p2_toc_counter]->count_n3, name);
                        }
                        break;
                case TOLYX:
                        set_inside_node2();
                        out("\\layout ");
                        if (invisible)
                        {       (use_style_book)        ? outln("Section*")
                                                                        : outln("Subsection*");
                        }
                        else
                        {       (use_style_book)        ? outln("Section")
                                                                        : outln("Subsection");
                        }
                        indent2space(name);
                        outln(name);
                        break;
                case TOINF:
                        set_inside_node2();
                        output_texinfo_node(name);
                        if (bInsideAppendix)
                        {       voutlnf("@appendixsec %s", name);
                        }
                        else
                        {       (invisible) ?   (voutlnf("@heading %s", name))
                                                        :       (voutlnf("@section %s", name));
                        }
                        break;
                case TOTVH:
                        set_inside_node2();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        output_vision_header(numbers, name);
                        break;
                case TOSTG:
                        set_inside_node2();
                        bInsidePopup= popup;
                        replace_2at_by_1at(name);
                        node2stg(name);

                        outln("");
                        if (!do_index)
                        {       outln("@indexoff");
                        }
                        if (popup)
                        {       voutlnf("@pnode \"%s\"", name);
                        }
                        else
                        {       voutlnf("@node \"%s\"", name);
                        }
                        if (!do_index)
                        {       outln("@indexon");
                        }

                        /* r5pl6: up_n1_index wird statt der alten Abfrage benutzt */
                        if (!popup)
                        {       ui= toc[p2_toc_counter]->up_n1_index;
                                if (ui>0)
                                {       strcpy(sTemp, toc[ui]->name);
                                        node2stg(sTemp);
                                        replace_2at_by_1at(sTemp);
                                        voutlnf("@toc \"%s\"", sTemp);
                                }
                        }
                        stg_header(numbers, stgname, popup);
                        break;
                case TOAMG:
                        set_inside_node2();
                        replace_2at_by_1at(name);
                        node2stg(name);

                        outln("");
                        if (titleprogram[0]!=EOS)
                        {       voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
                        }
                        else
                        {       voutlnf("@node \"%s\" \"%s\"", name, name);
                        }

                        /* r5pl6: up_n1_index wird statt der alten Abfrage benutzt */
                        ui= toc[p2_toc_counter]->up_n1_index;
                        if (ui>0)
                        {       strcpy(sTemp, toc[ui]->name);
                                node2stg(sTemp);
                                replace_2at_by_1at(sTemp);
                                voutlnf("@toc \"%s\"", sTemp);
                        }
                        stg_header(numbers, stgname, FALSE);
                        break;
                case TOMAN:
                        set_inside_node2();
                        outln("");
                        sprintf(n, " %s%s%s", BOLD_ON, name, BOLD_OFF);
                        c_internal_styles(n);
                        outln(n);
                        break;
                case TONRO:
                        set_inside_node2();
                        sprintf(n, ".SH %s", name);
                        c_internal_styles(n);
                        outln(n);
                        break;

                case TOASC:
                        set_inside_node2();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        sprintf(n, "%s%s", numbers, name);
                        outln("");
                        outln(n);
                        output_ascii_line("=", strlen(n));
                        outln("");
                        break;

                case TOIPF:
                        set_inside_node2();
                        node2NrIPF(n, toc[p2_toc_counter]->labindex);   /* r6pl2 */
                        map[0]= EOS;
                        if (toc[p2_toc_counter]->mapping>=0)
                        {       sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
                        }
                        if (bInsideAppendix)
                        {       voutlnf(":h2 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
                        }
                        else
                        {       voutlnf(":h2 id=%s%s.%s%s", n, map, numbers, name);
                        }
                        break;


                case TOKPS:
                        set_inside_node2();

                        if (use_style_book)
                        {       (bInsideAppendix)       ?       sprintf(n, "%s %s", lang.appendix, numbers)
                                                                        :       sprintf(n, "%s %s", lang.chapter, numbers);
                                del_right_spaces(n);
                                if (n[0]!=EOS) strcat(n, " ");
                                strcat(n, name);
                                outln("18 changeFontSize");
                        }
                        else
                        {       if (numbers[0]!=EOS) strcat(numbers, " ");
                                sprintf(n, "%s%s", numbers, name);
                                /* Changed in r6pl16 [NHz] */
                                voutlnf("%d changeFontSize", laydat.node2size);
                        }
                        outln("newline");
                        node2postscript(name, KPS_NAMEDEST); /* Changed in r6pl16 [NHz] */
                        voutlnf("/%s NameDest", name); /* New in r6pl15 [NHz] */
                        outln("Bon");
                        /* New in V6.5.5 [NHz] */
                        node2postscript(n, KPS_CONTENT);
                        voutlnf("(%s) udoshow", n);
                        outln("Boff");
                        outln("newline");
                        voutlnf("%d changeFontSize", laydat.propfontsize); /* Changed in r6pl15 [NHz] */
                        break;

                case TODRC:
                        set_inside_node2();
                        outln("%%*");
                        if (p2_toc_counter+1<=p1_toc_counter && toc[p2_toc_counter+1]->toctype==TOC_NODE3)
                        {       voutlnf("%%%% %d, %d, 0, 0, %d, %s", last_n1_index+10, p2_toc_counter+100, iDrcFlags, name);
                        }
                        else
                        {       voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n1_index+10, iDrcFlags, name);
                        }
                        outln("%%*");
                        outln("");
                        break;

                case TOSRC:
                case TOSRP:
                        set_inside_node1();
                        outln("");
                        memset(n, '*', 62); n[62]= EOS;
                        voutlnf("%s  %s", sSrcRemOn, n);
                        outln("    *");
                        voutlnf("    * %s", name);
                        outln("    *");
                        voutlnf("    %s  %s", n, sSrcRemOff);
                        outln("");
                        break;

                case TORTF:
                        set_inside_node2();
                        outln(rtf_pardpar);

                        /* r6pl6: Indizes fuer RTF */
                        if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
                        {       strcpy(n, name);
                                winspecials2ascii(n);
                                voutf("{\\xe\\v %s}", n);
                        }

                        /* New in V6.5.9 [NHz] */
                        um_strcpy(k, name, 512, "make_subnode[RTF]");
                        winspecials2ascii(k);
                        node2winhelp(k);

                        if (use_style_book)
                        {
                                if (invisible)
                                        sprintf(n, "%s\\fs%d", rtf_inv_node1, iDocPropfontSize + 14);
                                else
                                        sprintf(n, "%s\\fs%d", rtf_node1, iDocPropfontSize + 14);
                        }
                        else
                        {
                                if (invisible)
                                {       /* Changed in r6pl16 [NHz] */
                                        /* Nodesize ist set on discrete value */
                                        sprintf(n, "%s\\fs%d", rtf_inv_node2, laydat.node2size);
                                }
                                else
                                {       /* Changed in r6pl16 [NHz] */
                                        /* Nodesize ist set on discrete value */
                                        sprintf(n, "%s\\fs%d", rtf_node2, laydat.node2size);
                                }
                        }

                        if (numbers[0]==EOS)    /* Changed in V6.5.9 [NHz] [bookmark] */
                        {       voutlnf("%s %s {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, k, name, k, rtf_parpard);
                        }
                        else
                        {       voutlnf("%s %s %s  {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, numbers, k, name, k, rtf_parpard);
                        }
                        voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);      /* r5pl6 */
                        break;

                case TOWIN:
                case TOWH4:
                case TOAQV:
                        set_inside_node2();
                        output_win_header(name, invisible);
                        output_aliasses();
                        if (numbers[0]!=EOS) strcat(numbers, "\\~\\~");
                        sprintf(n, "%s%s", numbers, name);
                        win_headline(n, popup);
                        break;

                case TOPCH:
                        set_inside_node2();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        output_pch_header(numbers, name);
                        break;

                case TOHAH:             /* V6.5.17 */
                case TOHTM:
                case TOMHH:
                        ti= p2_toc_counter;

                        if (!html_merge_node2)
                        {       if (!html_new_file()) return;
                                if (!toc[ti]->ignore_title)
                                {       sprintf(hx_start, "<h%d>", html_nodesize);
                                        sprintf(hx_end, "</h%d>", html_nodesize);
                                }
                        }
                        else
                        {       if (!toc[ti]->ignore_title)
                                {       sprintf(hx_start, "<h%d>", html_nodesize+1);
                                        sprintf(hx_end, "</h%d>", html_nodesize+1);
                                }
                                output_aliasses();
                        }
                        set_inside_node2();
                        flag= FALSE;


                        do_toptoc(TOC_NODE2);   /*r6pl5*/

                        if (use_chapter_images)
                        {
            char closer[8] = "\0";
               
                                          /* no single tag closer in HTML! */
            if (html_doctype >= XHTML_STRICT)
               strcpy(closer, " /");
               
            ti = p2_toc_counter;
            
                                if (ti>=0 && toc[ti]->image!=NULL)
                                {
               sGifSize[0]= EOS;
               
                                        if (toc[ti]->uiImageWidth!=0 && toc[ti]->uiImageHeight!=0)
                                        {
                  sprintf(sGifSize, " width=\"%u\" height=\"%u\"",
                                                        toc[ti]->uiImageWidth, toc[ti]->uiImageHeight);
                                        }
               
                                        voutlnf("%s<p align=\"center\">", hx_start);
               
                                        voutlnf("<img src=\"%s%s\" alt=\"%s%s\" title=\"%s%s\" border=\"0\"%s%s>",
                                                toc[ti]->image, sDocImgSuffix, numbers, name, numbers, name, sGifSize, closer);
               
                                        voutlnf("</p>%s", hx_end);
                                        flag= TRUE;
                                }
                        }

                        if (!flag)
                        {       strcpy(nameNoSty, name);
                                del_html_styles(nameNoSty);
            
            label2html(nameNoSty);      /*r6pl2*/
            voutlnf("%s<a name=\"%s\"></a>%s%s%s",hx_start, nameNoSty, numbers, name, hx_end);
                        }
                        if (show_variable.source_filename) /* V6.5.19 */
                                voutlnf("<!-- %s: %li -->", toc[p2_toc_counter]->source_filename, toc[p2_toc_counter]->source_line);

                        break;

                case TOLDS:
                        (use_style_book)        ?       voutlnf("<sect>%s<label id=\"%s\">", name, name)
                                                                :       voutlnf("<sect1>%s<label id=\"%s\">", name, name);
                        output_aliasses();      /* r5pl8 */
                        outln("<p>");
                        break;

                case TOHPH:
                        set_inside_node2();
                        (use_style_book)        ?       voutlnf("<s1>%s", name)
                                                                :       voutlnf("<s2>%s", name);
                        output_aliasses();
                        break;
        }

}  /* make_subnode() */





/*******************************************************************************
*
*  make_subsubnode():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void make_subsubnode(

const BOOLEAN   popup,             /* TRUE: this is a popup node */
const BOOLEAN   invisible)         /* TRUE: this is an invisible node */
{
        char    n[512], name[512], stgname[512], hx_start[16], hx_end[16], sTemp[512];
        char    numbers[512], nameNoSty[512], k[512];   /* New in V6.5.9 [NHz] */
        char    map[64], sGifSize[80];
        int             ti, ui, chapter, nr1, nr2, nr3;
        BOOLEAN flag;
        BOOLEAN do_index;

        if (p2_toc_counter>=MAXTOCS)    /* r5pl2 */
        {       bBreakInside= TRUE;
                return;
        }

        tokcpy2(name, 512);
        strcpy(stgname, name);  /* r5pl14 */

        if (name[0]==EOS)
        {       error_missing_parameter("!subsubnode");
                return;
        }

        p2_lab_counter++;               /*r6pl2*/
        p2_toctype= TOC_NODE3;  /*r6pl5*/

        if ((desttype==TOHTM || desttype==TOHAH) && !html_merge_node3)
        {       check_endnode();
                html_bottomline();
        }

        if (desttype==TOMHH)
        {       check_endnode();
                hh_bottomline();
        }

        check_styles(name);                     /*r6pl3*/
        c_styles(name);
        switch (desttype)                       /* r5pl3 */
        {       case TOWIN:
                case TOWH4:
                case TOAQV:     c_win_styles(name);     break;
                case TORTF:     c_rtf_styles(name);     c_rtf_quotes(name);     break;
                default:        c_internal_styles(name); break;
        }
        replace_udo_quotes(name);
        delete_all_divis(name);
        replace_udo_tilde(name);
        replace_udo_nbsp(name);

        check_endnode();
        check_styleflags();
        check_environments_node();

        if (bInsideAppendix)
        {       p2_apx_n3++;
                p2_apx_n4= 0;
                p2_apx_n5= 0;
        }
        else
        {       p2_toc_n3++;
                p2_toc_n4= 0;
                p2_toc_n5= 0;
        }

        p2_toc_counter++;
        curr_n3_index= p2_toc_counter;
        curr_n4_index= 0;

        last_n3_index= p2_toc_counter;
        last_n4_index= 0;
        last_n5_index= 0;

        nr1= toc[p2_toc_counter]->nr1;
        nr2= toc[p2_toc_counter]->nr2;
        nr3= toc[p2_toc_counter]->nr3;
        (bInsideAppendix) ? (chapter= nr1) : (chapter= nr1+toc_offset);

        n[0]= EOS;
        numbers[0]= EOS;

        if (!invisible)
        {       if (bInsideAppendix)
        {       sprintf(numbers, "%c.%d.%d", 'A'+nr1-1, nr2+subtoc_offset, nr3+subsubtoc_offset);
                }
                else
                {       sprintf(numbers, "%d.%d.%d", chapter, nr2+subtoc_offset, nr3+subsubtoc_offset);
                }
        }

        if (bVerbose)
        {       sprintf(sInfMsg, "[%s] ", numbers);
                show_status_node(sInfMsg);
        }

        if (no_numbers || invisible)
        {       numbers[0]= EOS;
        }
        else
        {       strcat(numbers, " ");
        }

        strcpy(current_chapter_name, name);
        strcpy(current_chapter_nr, numbers);

        do_index= (use_nodes_inside_index && !no_index &&
                                        !toc[p2_toc_counter]->ignore_index);    /* r5pl10 */

        switch (desttype)
        {
                case TOTEX:
                case TOPDL:
                        set_inside_node3();
                        if (invisible)
                        {       (use_style_book)        ? voutlnf("\n\\subsection*{%s}", name)
                                                                        : voutlnf("\n\\subsubsection*{%s}", name);
                        }
                        else
                        {       (use_style_book)        ? voutlnf("\n\\subsection{%s}", name)
                                                                        : voutlnf("\n\\subsubsection{%s}", name);
                        }
                        label2tex(name);                                /*r6pl2*/
                        voutlnf("\\label{%s}", name);   /*r6pl2*/
                        if (desttype==TOPDL)    /*r6pl8*/
                        {
                                voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
                                voutlnf("\\pdfoutline goto num %d count %d {%s}",
                                        p2_lab_counter, toc[p2_toc_counter]->count_n4, name);
                        }
                        output_aliasses();
                        break;
                case TOLYX:
                        set_inside_node3();
                        out("\\layout ");
                        if (invisible)
                        {       (use_style_book)        ? outln("Subsection*")
                                                                        : outln("Subsubsection*");
                        }
                        else
                        {       (use_style_book)        ? outln("Subsection")
                                                                        : outln("Subsubsection");
                        }
                        indent2space(name);
                        outln(name);
                        break;
                case TOINF:
                        set_inside_node3();
                        output_texinfo_node(name);
                        if (bInsideAppendix)
                        {       voutlnf("@appendixsubsec %s", name);
                        }
                        else
                        {       (invisible) ?   (voutlnf("@subheading %s", name))
                                                        :       (voutlnf("@subsection %s", name));
                        }
                        break;
                case TOTVH:
                        set_inside_node3();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        output_vision_header(numbers, name);
                        break;
                case TOSTG:
                        set_inside_node3();
                        bInsidePopup= popup;
                        replace_2at_by_1at(name);
                        node2stg(name);

                        outln("");
                        if (!do_index)
                        {       outln("@indexoff");
                        }
                        if (popup)
                        {       voutlnf("@pnode \"%s\"", name);
                        }
                        else
                        {       voutlnf("@node \"%s\"", name);
                        }
                        if (!do_index)
                        {       outln("@indexon");
                        }

                        /* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
                        if (!popup)
                        {       ui= toc[p2_toc_counter]->up_n2_index;
                                if (ui>0)
                                {       strcpy(sTemp, toc[ui]->name);
                                        node2stg(sTemp);
                                        replace_2at_by_1at(sTemp);
                                        voutlnf("@toc \"%s\"", sTemp);
                                }
                        }
                        stg_header(numbers, stgname, popup);    /* r5pl14: stgname statt "" */
                        break;

                case TOAMG:
                        set_inside_node3();
                        replace_2at_by_1at(name);
                        node2stg(name);

                        outln("");
                        if (titleprogram[0]!=EOS)
                        {       voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
                        }
                        else
                        {       voutlnf("@node \"%s\" \"%s\"", name, name);
                        }

                        /* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
                        ui= toc[p2_toc_counter]->up_n2_index;
                        if (ui>0)
                        {       strcpy(sTemp, toc[ui]->name);
                                node2stg(sTemp);
                                replace_2at_by_1at(sTemp);
                                voutlnf("@toc \"%s\"", sTemp);
                        }
                        stg_header(numbers, stgname, FALSE);    /* r5pl14: stgname statt "" */
                        break;

                case TOMAN:
                        set_inside_node3();
                        outln("");
                        sprintf(n, " %s", name);
                        c_internal_styles(n);
                        outln(n);
                        break;

                case TONRO:
                        set_inside_node3();
                        sprintf(n, ".SH %s", name);
                        c_internal_styles(n);
                        outln(n);
                        break;

                case TOASC:
                        set_inside_node3();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        sprintf(n, "%s%s", numbers, name);
                        outln("");
                        outln(n);
                        output_ascii_line("-", strlen(n));
                        outln("");
                        break;

                case TOIPF:
                        set_inside_node3();
                        node2NrIPF(n, toc[p2_toc_counter]->labindex);   /* r6pl2 */
                        map[0]= EOS;
                        if (toc[p2_toc_counter]->mapping>=0)
                        {       sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
                        }
                        if (bInsideAppendix)
                        {       voutlnf(":h3 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
                        }
                        else
                        {       voutlnf(":h3 id=%s%s.%s%s", n, map, numbers, name);
                        }
                        break;


                case TOKPS:
                        set_inside_node3();

                        if (use_style_book)
                        {       (bInsideAppendix)       ?       sprintf(n, "%s %s", lang.appendix, numbers)
                                                                        :       sprintf(n, "%s %s", lang.chapter, numbers);
                                del_right_spaces(n);
                                if (n[0]!=EOS) strcat(n, " ");
                                strcat(n, name);
                                outln("14 changeFontSize");
                        }
                        else
                        {       if (numbers[0]!=EOS) strcat(numbers, " ");
                                sprintf(n, "%s%s", numbers, name);
                                /* Changed in r6pl16 [NHz] */
                                voutlnf("%d changeFontSize", laydat.node3size);
                        }
                        outln("newline");
                        node2postscript(name, KPS_NAMEDEST); /* Changed in r6pl16 [NHz] */
                        voutlnf("/%s NameDest", name); /* New in r6pl15 [NHz] */
                        outln("Bon");
                        /* New in V6.5.5 [NHz] */
                        node2postscript(n, KPS_CONTENT);
                        voutlnf("(%s) udoshow", n);
                        outln("Boff");
                        outln("newline");
                        voutlnf("%d changeFontSize", laydat.propfontsize); /* Changed in r6pl15 [NHz] */
                        break;

                case TODRC:
                        set_inside_node3();
                        outln("%%*");
                        if (p2_toc_counter+1<=p1_toc_counter && toc[p2_toc_counter+1]->toctype==TOC_NODE4)
                        {       voutlnf("%%%% %d, %d, 0, 0, %d, %s", last_n2_index+100, p2_toc_counter+1000, iDrcFlags, name);
                        }
                        else
                        {       voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n2_index+100, iDrcFlags, name);
                        }
                        outln("%%*");
                        outln("");
                        break;

                case TOSRC:
                case TOSRP:
                        set_inside_node1();
                        outln("");
                        memset(n, '=', 62); n[62]= EOS;
                        voutlnf("%s  %s", sSrcRemOn, n);
                        voutlnf("    = %s", name);
                        voutlnf("    %s  %s", n, sSrcRemOff);
                        outln("");
                        break;

                case TORTF:
                        set_inside_node3();
                        outln(rtf_pardpar);

                        /* r6pl6: Indizes fuer RTF */
                        if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
                        {       strcpy(n, name);
                                winspecials2ascii(n);
                                voutf("{\\xe\\v %s}", n);
                        }

                        /* New in V6.5.9 [NHz] */
                        um_strcpy(k, name, 512, "make_subsubnode[RTF]");
                        winspecials2ascii(k);
                        node2winhelp(k);

                        if (use_style_book)
                        {
                                if (invisible)
                                        sprintf(n, "%s\\fs%d", rtf_inv_node2, iDocPropfontSize + 6);
                                else
                                        sprintf(n, "%s\\fs%d", rtf_node2, iDocPropfontSize + 6);
                        }
                        else
                        {
                                if (invisible)
                                {       /* Changed in r6pl16 [NHz] */
                                        /* Nodesize ist set on discrete value */
                                        sprintf(n, "%s\\fs%d", rtf_inv_node3, laydat.node3size);
                                }
                                else
                                {       /* Changed in r6pl16 [NHz] */
                                        /* Nodesize ist set on discrete value */
                                        sprintf(n, "%s\\fs%d", rtf_node3, laydat.node3size);
                                }
                        }
                        if (numbers[0]==EOS)    /* Changed in V6.5.9 [NHz] */
                        {       voutlnf("%s %s {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, k, name, k, rtf_parpard);
                        }
                        else
                        {       voutlnf("%s %s %s  {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, numbers, k, name, k, rtf_parpard);
                        }

                        voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);      /* r5pl6 */
                        break;

                case TOWIN:
                case TOWH4:
                case TOAQV:
                        set_inside_node3();

                        output_win_header(name, invisible);
                        output_aliasses();

                        if (numbers[0]!=EOS) strcat(numbers, "\\~\\~");
                        sprintf(n, "%s%s", numbers, name);
                        win_headline(n, popup);
                        break;

                case TOPCH:
                        set_inside_node3();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        output_pch_header(numbers, name);
                        break;

                case TOHAH:             /* V6.5.17 */
                case TOHTM:
                case TOMHH:
                        ti= p2_toc_counter;

                        if (!html_merge_node3)
                        {       if (!html_new_file()) return;
                                if (!toc[ti]->ignore_title)
                                {       sprintf(hx_start, "<h%d>", html_nodesize);
                                        sprintf(hx_end, "</h%d>", html_nodesize);
                                }
                        }
                        else
                        {       if (!toc[ti]->ignore_title)
                                {       sprintf(hx_start, "<h%d>", html_nodesize+2);
                                        sprintf(hx_end, "</h%d>", html_nodesize+2);
                                }
                                output_aliasses();
                        }

                        set_inside_node3();
                        flag= FALSE;

                        if (use_chapter_images)
                        {
            char closer[8] = "\0";
               
                                          /* no single tag closer in HTML! */
            if (html_doctype >= XHTML_STRICT)
               strcpy(closer, " /");
               
                                ti= p2_toc_counter;
                                if (ti>=0 && toc[ti]->image!=NULL)
                                {
                sGifSize[0]= EOS;
               
                                        if (toc[ti]->uiImageWidth!=0 && toc[ti]->uiImageHeight!=0)
                                        {
                sprintf(sGifSize, " width=\"%u\" height=\"%u\"",
                                                        toc[ti]->uiImageWidth, toc[ti]->uiImageHeight);
                                        }
               
                                        voutlnf("%s<p align=\"center\">", hx_start);
               
                                        voutlnf("<img src=\"%s%s\" alt=\"%s%s\" title=\"%s%s\" border=\"0\"%s%s>",
                                                toc[ti]->image, sDocImgSuffix, numbers, name, numbers, name, sGifSize, closer);
               
                                        voutlnf("</p>%s", hx_end);
                                        flag= TRUE;
                                }
                        }

                        do_toptoc(TOC_NODE3);   /*r6pl5*/

                        if (!flag)
                        {
                                strcpy(nameNoSty, name);
                                del_html_styles(nameNoSty);
            
            label2html(nameNoSty);      /*r6pl2*/
            voutlnf("%s<a name=\"%s\"></a>%s%s%s",hx_start, nameNoSty, numbers, name, hx_end);
                        }
                        if (show_variable.source_filename) /* V6.5.19 */
                                voutlnf("<!-- %s: %li -->", toc[p2_toc_counter]->source_filename, toc[p2_toc_counter]->source_line);

                        break;

                case TOLDS:
                        set_inside_node3();
                        (use_style_book)        ?       voutlnf("<sect1>%s<label id=\"%s\">", name, name)
                                                                :       voutlnf("<sect2>%s<label id=\"%s\">", name, name);
                        output_aliasses();      /* r5pl8 */
                        outln("<p>");
                        break;

                case TOHPH:
                        set_inside_node3();
                        (use_style_book)        ?       voutlnf("<s2>%s", name)
                                                                :       voutlnf("<s3>%s", name);
                        output_aliasses();
                        break;
        }

}  /* make_subsubnode() */





/*******************************************************************************
*
*  make_subsubsubnode():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void make_subsubsubnode(

const BOOLEAN   popup,             /* TRUE: this is a popup node */
const BOOLEAN   invisible)         /* TRUE: this is an invisible node */
{
        char    n[512], name[512], stgname[512], hx_start[16], hx_end[16], sTemp[512];
        char    numbers[512], nameNoSty[512], k[512];   /* New in V6.5.9 [NHz] */
        char    map[64], sGifSize[80];
        int             ti, ui, chapter, nr1, nr2, nr3, nr4;
        BOOLEAN flag;
        BOOLEAN do_index;

        if (p2_toc_counter>=MAXTOCS)    /* r5pl2 */
        {       bBreakInside= TRUE;
                return;
        }

        tokcpy2(name, 512);
        strcpy(stgname, name);  /* r5pl14 */

        if (name[0]==EOS)
        {       error_missing_parameter("!subsubsubnode");
                return;
        }

        p2_lab_counter++;               /*r6pl2*/
        p2_toctype= TOC_NODE4;  /*r6pl5*/

        if ((desttype==TOHTM || desttype==TOHAH) && !html_merge_node4)
        {       check_endnode();
                html_bottomline();
        }

        if (desttype==TOMHH)
        {       check_endnode();
                hh_bottomline();
        }

        check_styles(name);                     /*r6pl3*/
        c_styles(name);
        switch (desttype)                       /* r5pl3 */
        {       case TOWIN:
                case TOWH4:
                case TOAQV:     c_win_styles(name);     break;
                case TORTF:     c_rtf_styles(name);     c_rtf_quotes(name);     break;
                default:        c_internal_styles(name); break;
        }
        replace_udo_quotes(name);
        delete_all_divis(name);
        replace_udo_tilde(name);
        replace_udo_nbsp(name);

        check_endnode();
        check_styleflags();
        check_environments_node();

        if (bInsideAppendix)
        {       p2_apx_n4++;
                p2_apx_n5= 0;
        }
        else
        {       p2_toc_n4++;
                p2_toc_n5= 0;
        }

        p2_toc_counter++;
        curr_n4_index= p2_toc_counter;

        last_n4_index= p2_toc_counter;
        last_n5_index= 0;

        nr1= toc[p2_toc_counter]->nr1;
        nr2= toc[p2_toc_counter]->nr2;
        nr3= toc[p2_toc_counter]->nr3;
        nr4= toc[p2_toc_counter]->nr4;
        (bInsideAppendix) ? (chapter= nr1) : (chapter= nr1+toc_offset);

        n[0]= EOS;
        numbers[0]= EOS;

        if (!invisible)
        {       if (bInsideAppendix)
                {       sprintf(numbers, "%c.%d.%d.%d", 'A'+nr1-1, nr2+subtoc_offset, nr3+subsubtoc_offset, nr4+subsubsubtoc_offset);
                }
                else
                {       sprintf(numbers, "%d.%d.%d.%d", chapter, nr2+subtoc_offset, nr3+subsubtoc_offset, nr4+subsubsubtoc_offset);
                }
        }

        if (bVerbose)
        {       sprintf(sInfMsg, "[%s] ", numbers);
                show_status_node(sInfMsg);
        }

        if (no_numbers || invisible)
        {       numbers[0]= EOS;
        }
        else
        {       strcat(numbers, " ");
        }

        strcpy(current_chapter_name, name);
        strcpy(current_chapter_nr, numbers);

        do_index= (use_nodes_inside_index && !no_index &&
                                        !toc[p2_toc_counter]->ignore_index);    /* r5pl10 */

        switch (desttype)
        {
                case TOTEX:
                case TOPDL:
                        set_inside_node4();
                        if (invisible)
                        {       (use_style_book)        ? voutlnf("\n\\subsubsection*{%s}", name)
                                                                        : voutlnf("\n\\paragraph*{%s}", name);
                        }
                        else
                        {       (use_style_book)        ? voutlnf("\n\\subsubsection{%s}", name)
                                                                        : voutlnf("\n\\paragraph{%s}", name);
                        }
                        label2tex(name);                                /*r6pl2*/
                        voutlnf("\\label{%s}", name);   /*r6pl2*/
                        output_aliasses();
                        if (desttype==TOPDL)    /*r6pl8*/
                        {
                                voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
                                voutlnf("\\pdfoutline goto num %d count 0 {%s}", p2_lab_counter, name);
                        }
                        break;

                case TOLYX:
                        set_inside_node4();
                        out("\\layout ");
                        if (invisible)
                        {       (use_style_book)        ? outln("Subsubsection*")
                                                                        : outln("Paragraph*");
                        }
                        else
                        {       (use_style_book)        ? outln("Subsubsection")
                                                                        : outln("Paragraph");
                        }
                        indent2space(name);
                        outln(name);
                        break;

                case TOINF:
                        set_inside_node4();
                        output_texinfo_node(name);
                        if (bInsideAppendix)
                        {       voutlnf("@appendixsubsubsec %s", name);
                        }
                        else
                        {       (invisible) ?   (voutlnf("@subsubheading %s", name))
                                                        :       (voutlnf("@subsubsection %s", name));
                        }
                        break;

                case TOTVH:
                        set_inside_node4();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        output_vision_header(numbers, name);
                        break;

                case TOSTG:
                        set_inside_node4();
                        bInsidePopup= popup;
                        replace_2at_by_1at(name);
                        node2stg(name);

                        outln("");
                        if (!do_index)
                        {       outln("@indexoff");
                        }
                        if (popup)
                        {       voutlnf("@pnode \"%s\"", name);
                        }
                        else
                        {       voutlnf("@node \"%s\"", name);
                        }
                        if (!do_index)
                        {       outln("@indexon");
                        }

                        /* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
                        if (!popup)
                        {       ui= toc[p2_toc_counter]->up_n3_index;
                                if (ui>0)
                                {       strcpy(sTemp, toc[ui]->name);
                                        node2stg(sTemp);
                                        replace_2at_by_1at(sTemp);
                                        voutlnf("@toc \"%s\"", sTemp);
                                }
                        }
                        stg_header(numbers, stgname, popup);    /* r5pl14: stgname statt "" */
                        break;

                case TOAMG:
                        set_inside_node4();
                        replace_2at_by_1at(name);
                        node2stg(name);

                        outln("");
                        if (titleprogram[0]!=EOS)
                        {       voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
                        }
                        else
                        {       voutlnf("@node \"%s\" \"%s\"", name, name);
                        }

                        /* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
                        ui= toc[p2_toc_counter]->up_n3_index;
                        if (ui>0)
                        {       strcpy(sTemp, toc[ui]->name);
                                node2stg(sTemp);
                                replace_2at_by_1at(sTemp);
                                voutlnf("@toc \"%s\"", sTemp);
                        }
                        stg_header(numbers, stgname, FALSE);    /* r5pl14: stgname statt "" */
                        break;

                case TOMAN:
                        set_inside_node4();
                        outln("");
                        sprintf(n, " %s", name);
                        c_internal_styles(n);
                        outln(n);
                        break;

                case TONRO:
                        set_inside_node4();
                        sprintf(n, ".SH %s", name);
                        c_internal_styles(n);
                        outln(n);
                        break;

                case TOASC:
                        set_inside_node4();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        sprintf(n, "%s%s", numbers, name);
                        outln("");
                        outln(n);
                        outln("");
                        break;

                case TOIPF:
                        set_inside_node4();
                        node2NrIPF(n, toc[p2_toc_counter]->labindex);   /* r6pl2 */
                        map[0]= EOS;
                        if (toc[p2_toc_counter]->mapping>=0)
                        {       sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
                        }
                        if (bInsideAppendix)
                        {       voutlnf(":h4 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
                        }
                        else
                        {       voutlnf(":h4 id=%s%s.%s%s", n, map, numbers, name);
                        }
                        break;


                case TOKPS:
                        set_inside_node4();

                        if (use_style_book)
                        {       (bInsideAppendix)       ?       sprintf(n, "%s %s", lang.appendix, numbers)
                                                                        :       sprintf(n, "%s %s", lang.chapter, numbers);
                                del_right_spaces(n);
                                if (n[0]!=EOS) strcat(n, " ");
                                strcat(n, name);
                                outln("11 changeFontSize");
                        }
                        else
                        {       if (numbers[0]!=EOS) strcat(numbers, " ");
                                sprintf(n, "%s%s", numbers, name);
                                /* Changed in r6pl16 [NHz] */
                                voutlnf("%d changeFontSize", laydat.node4size);
                        }
                        node2postscript(name, KPS_NAMEDEST); /* Changed in r6pl16 [NHz] */
                        voutlnf("/%s NameDest", name); /* New in r6pl15 [NHz] */
                        outln("newline");
                        outln("Bon");
                        /* New in V6.5.5 [NHz] */
                        node2postscript(n, KPS_CONTENT);
                        voutlnf("(%s) udoshow", n);
                        outln("Boff");
                        outln("newline");
                        voutlnf("%d changeFontSize", laydat.propfontsize); /* Changed in r6pl15 [NHz] */
                        break;

                case TODRC:
                        set_inside_node4();
                        outln("%%*");
                        if (p2_toc_counter+1<=p1_toc_counter && toc[p2_toc_counter+1]->toctype==TOC_NODE4)
                        {       voutlnf("%%%% %d, %d, 0, 0, %d, %s", last_n3_index+1000, p2_toc_counter+100, iDrcFlags, name);
                        }
                        else
                        {       voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n3_index+1000, iDrcFlags, name);
                        }
                        outln("%%*");
                        outln("");
                        break;

                case TOSRC:
                case TOSRP:
                        set_inside_node1();
                        outln("");
                        memset(n, '-', 62); n[62]= EOS;
                        voutlnf("%s  %s", sSrcRemOn, n);
                        voutlnf("    - %s", name);
                        voutlnf("    %s  %s", n, sSrcRemOff);
                        outln("");
                        break;

                case TORTF:
                        set_inside_node4();
                        outln(rtf_pardpar);

                        /* r6pl6: Indizes fuer RTF */
                        if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
                        {       strcpy(n, name);
                                winspecials2ascii(n);
                                voutf("{\\xe\\v %s}", n);
                        }

                        /* New in V6.5.9 [NHz] */
                        um_strcpy(k, name, 512, "make_subsubsubnode[RTF]");
                        winspecials2ascii(k);
                        node2winhelp(k);

                        if (use_style_book)
                        {
                                if (invisible)
                                        sprintf(n, "%s\\fs%d", rtf_inv_node3, iDocPropfontSize);
                                else
                                        sprintf(n, "%s\\fs%d", rtf_node3, iDocPropfontSize);
                        }
                        else
                        {
                                if (invisible)
                                {       /* Changed in r6pl16 [NHz] */
                                        /* Nodesize ist set on discrete value */
                                        sprintf(n, "%s\\fs%d", rtf_inv_node4, laydat.node4size);
                                }
                                else
                                {       /* Changed in r6pl16 [NHz] */
                                        /* Nodesize ist set on discrete value */
                                        sprintf(n, "%s\\fs%d", rtf_node4, laydat.node4size);
                                }
                        }

                        if (numbers[0]==EOS)    /* Changed in V6.5.9 [NHz] */
                        {       voutlnf("%s %s {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, k, name, k, rtf_parpard);
                        }
                        else
                        {       voutlnf("%s %s %s  {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, numbers, k, name, k, rtf_parpard);
                        }
                        voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);      /* r5pl6 */
                        break;

                case TOWIN:
                case TOWH4:
                case TOAQV:
                        set_inside_node4();

                        output_win_header(name, invisible);
                        output_aliasses();

                        if (numbers[0]!=EOS) strcat(numbers, "\\~\\~");
                        sprintf(n, "%s%s", numbers, name);
                        win_headline(n, popup);
                        break;

                case TOPCH:
                        set_inside_node4();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        output_pch_header(numbers, name);
                        break;

                case TOHAH: /* V6.5.17 */
                case TOHTM:
                case TOMHH:
                        ti= p2_toc_counter;

                        if (!html_merge_node4)
                        {       if (!html_new_file()) return;
                                if (!toc[ti]->ignore_title)
                                {       sprintf(hx_start, "<h%d>", html_nodesize);
                                        sprintf(hx_end, "</h%d>", html_nodesize);
                                }
                        }
                        else
                        {       if (!toc[ti]->ignore_title)
                                {       sprintf(hx_start, "<h%d>", html_nodesize+3);
                                        sprintf(hx_end, "</h%d>", html_nodesize+3);
                                }
                                output_aliasses();
                        }

                        set_inside_node4();
                        flag= FALSE;

                        if (use_chapter_images)
                        {
            char closer[8] = "\0";
               
                                          /* no single tag closer in HTML! */
            if (html_doctype >= XHTML_STRICT)
               strcpy(closer, " /");
               
                                ti = p2_toc_counter;
            
                                if (ti >= 0 && toc[ti]->image != NULL)
                                {
                sGifSize[0] = EOS;
               
                                        if (toc[ti]->uiImageWidth!=0 && toc[ti]->uiImageHeight!=0)
                                        {
                sprintf(sGifSize, " width=\"%u\" height=\"%u\"",
                                                        toc[ti]->uiImageWidth, toc[ti]->uiImageHeight);
                                        }
               
                                        voutlnf("%s<p align=\"center\">", hx_start);
               
                                        voutlnf("<img src=\"%s%s\" alt=\"%s%s\" title=\"%s%s\" border=\"0\" %s%s>",
                                                toc[ti]->image, sDocImgSuffix, numbers, name, numbers, name, sGifSize, closer);
               
                                        voutlnf("</p>%s", hx_end);
                                        flag = TRUE;
                                }
                        }

                        do_toptoc(TOC_NODE4);   /*r6pl5*/

                        if (!flag)
                        {
                                strcpy(nameNoSty, name);
                                del_html_styles(nameNoSty);
            
            label2html(nameNoSty);      /*r6pl2*/
            voutlnf("%s<a name=\"%s\"></a>%s%s%s",      hx_start, nameNoSty, numbers, name, hx_end);
                        }
                        if (show_variable.source_filename) /* V6.5.19 */
                                voutlnf("<!-- %s: %li -->", toc[p2_toc_counter]->source_filename, toc[p2_toc_counter]->source_line);

                        break;

                case TOLDS:
                        set_inside_node4();
                        (use_style_book)        ?       voutlnf("<sect2>%s<label id=\"%s\">", name, name)
                                                                :       voutlnf("<sect3>%s<label id=\"%s\">", name, name);
                        output_aliasses();      /* r5pl8 */
                        outln("<p>");
                        break;

                case TOHPH:
                        set_inside_node4();
                        (use_style_book)        ?       voutlnf("<s3>%s", name)
                                                                :       voutlnf("<s4>%s", name);
                        output_aliasses();
                        break;
        }

}  /* make_subsubsubnode() */





/*******************************************************************************
*
*  make_subsubsubsubnode():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void make_subsubsubsubnode(

const BOOLEAN   popup,             /* TRUE: this is a popup node */
const BOOLEAN   invisible)         /* TRUE: this is an invisible node */
{
        char    n[512], name[512], stgname[512], hx_start[16], hx_end[16], sTemp[512];
        char    numbers[512], nameNoSty[512], k[512];
        char    map[64], sGifSize[80];
        int             ti, ui, chapter, nr1, nr2, nr3, nr4, nr5;
        BOOLEAN flag;
        BOOLEAN do_index;

        if (p2_toc_counter>=MAXTOCS)
        {       bBreakInside= TRUE;
                return;
        }

        tokcpy2(name, 512);
        strcpy(stgname, name);

        if (name[0]==EOS)
        {       error_missing_parameter("!subsubsubsubnode");
                return;
        }

        p2_lab_counter++;               /*r6pl2*/
        p2_toctype= TOC_NODE5;  /*r6pl5*/

        if ((desttype==TOHTM || desttype==TOHAH) && !html_merge_node5)
        {       check_endnode();
                html_bottomline();
        }

        if (desttype==TOMHH)
        {       check_endnode();
                hh_bottomline();
        }

        check_styles(name);                     /*r6pl3*/
        c_styles(name);
        switch (desttype)                       /* r5pl3 */
        {       case TOWIN:
                case TOWH4:
                case TOAQV:     c_win_styles(name);     break;
                case TORTF:     c_rtf_styles(name);     c_rtf_quotes(name);     break;
                default:        c_internal_styles(name); break;
        }
        replace_udo_quotes(name);
        delete_all_divis(name);
        replace_udo_tilde(name);
        replace_udo_nbsp(name);

        check_endnode();
        check_styleflags();
        check_environments_node();

        if (bInsideAppendix)
        {       p2_apx_n5++;
        }
        else
        {       p2_toc_n5++;
        }

        p2_toc_counter++;

        last_n5_index= p2_toc_counter;

        nr1= toc[p2_toc_counter]->nr1;
        nr2= toc[p2_toc_counter]->nr2;
        nr3= toc[p2_toc_counter]->nr3;
        nr4= toc[p2_toc_counter]->nr4;
        nr5= toc[p2_toc_counter]->nr5;
        (bInsideAppendix) ? (chapter= nr1) : (chapter= nr1+toc_offset);

        n[0]= EOS;
        numbers[0]= EOS;

        if (!invisible)
        {       if (bInsideAppendix)
                {       sprintf(numbers, "%c.%d.%d.%d.%d", 'A'+nr1-1, nr2+subtoc_offset, nr3+subsubtoc_offset, nr4+subsubsubtoc_offset, nr5+subsubsubsubtoc_offset);
                }
                else
                {       sprintf(numbers, "%d.%d.%d.%d.%d", chapter, nr2+subtoc_offset, nr3+subsubtoc_offset, nr4+subsubsubtoc_offset, nr5+subsubsubtoc_offset);
                }
        }

        if (bVerbose)
        {       sprintf(sInfMsg, "[%s] ", numbers);
                show_status_node(sInfMsg);
        }

        if (no_numbers || invisible)
        {       numbers[0]= EOS;
        }
        else
        {       strcat(numbers, " ");
        }

        strcpy(current_chapter_name, name);
        strcpy(current_chapter_nr, numbers);

        do_index= (use_nodes_inside_index && !no_index &&
                                        !toc[p2_toc_counter]->ignore_index);    /* r5pl10 */

        switch (desttype)
        {
                case TOTEX:
                case TOPDL:
                        set_inside_node5();
                        if (invisible)
                        {       (use_style_book)        ? voutlnf("\n\\paragraph*{%s}", name)  /* ToDo: Was muss hier hin? */
                                                                        : voutlnf("\n\\subparagraph*{%s}", name);   /* ToDo: Was muss hier hin? */
                        }
                        else
                        {       (use_style_book)        ? voutlnf("\n\\paragraph{%s}", name)  /* ToDo: Was muss hier hin? */
                                                                        : voutlnf("\n\\subparagraph{%s}", name);   /* ToDo: Was muss hier hin? */
                        }
                        label2tex(name);                                /*r6pl2*/
                        voutlnf("\\label{%s}", name);   /*r6pl2*/
                        output_aliasses();
                        if (desttype==TOPDL)    /*r6pl8*/
                        {
                                voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
                                voutlnf("\\pdfoutline goto num %d count 0 {%s}", p2_lab_counter, name);
                        }
                        break;

                case TOLYX:
                        set_inside_node5();
                        out("\\layout ");
                        if (invisible)
                        {       (use_style_book)        ? outln("Subsubsection*")         /* ToDo: Was muss hier hin? */
                                                                        : outln("Paragraph*");  /* ToDo: Was muss hier hin? */
                        }
                        else
                        {       (use_style_book)        ? outln("Subsubsection")  /* ToDo: Was muss hier hin? */
                                                                        : outln("Paragraph");  /* ToDo: Was muss hier hin? */
                        }
                        indent2space(name);
                        outln(name);
                        break;

                case TOINF:
                        set_inside_node5();
                        output_texinfo_node(name);
                        if (bInsideAppendix)
                        {       voutlnf("@appendixsubsubsec %s", name);  /* ToDo: Was muss hier hin? */
                        }
                        else
                        {       (invisible) ?   (voutlnf("@subsubheading %s", name))  /* ToDo: Was muss hier hin? */
                                                        :       (voutlnf("@subsubsection %s", name));  /* ToDo: Was muss hier hin? */
                        }
                        break;

                case TOTVH:
                        set_inside_node5();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        output_vision_header(numbers, name);
                        break;

                case TOSTG:
                        set_inside_node5();
                        bInsidePopup= popup;
                        replace_2at_by_1at(name);
                        node2stg(name);

                        outln("");
                        if (!do_index)
                        {       outln("@indexoff");
                        }
                        if (popup)
                        {       voutlnf("@pnode \"%s\"", name);
                        }
                        else
                        {       voutlnf("@node \"%s\"", name);
                        }
                        if (!do_index)
                        {       outln("@indexon");
                        }

                        /* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
                        if (!popup)
                        {       ui= toc[p2_toc_counter]->up_n4_index;
                                if (ui>0)
                                {       strcpy(sTemp, toc[ui]->name);
                                        node2stg(sTemp);
                                        replace_2at_by_1at(sTemp);
                                        voutlnf("@toc \"%s\"", sTemp);
                                }
                        }
                        stg_header(numbers, stgname, popup);    /* r5pl14: stgname statt "" */
                        break;

                case TOAMG:
                        set_inside_node5();
                        replace_2at_by_1at(name);
                        node2stg(name);

                        outln("");
                        if (titleprogram[0]!=EOS)
                        {       voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
                        }
                        else
                        {       voutlnf("@node \"%s\" \"%s\"", name, name);
                        }

                        /* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
                        ui= toc[p2_toc_counter]->up_n4_index;
                        if (ui>0)
                        {       strcpy(sTemp, toc[ui]->name);
                                node2stg(sTemp);
                                replace_2at_by_1at(sTemp);
                                voutlnf("@toc \"%s\"", sTemp);
                        }
                        stg_header(numbers, stgname, FALSE);    /* r5pl14: stgname statt "" */
                        break;

                case TOMAN:
                        set_inside_node5();
                        outln("");
                        sprintf(n, " %s", name);
                        c_internal_styles(n);
                        outln(n);
                        break;

                case TONRO:
                        set_inside_node5();
                        sprintf(n, ".SH %s", name);
                        c_internal_styles(n);
                        outln(n);
                        break;

                case TOASC:
                        set_inside_node5();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        sprintf(n, "%s%s", numbers, name);
                        outln("");
                        outln(n);
                        outln("");
                        break;

                case TOIPF:
                        set_inside_node5();
                        node2NrIPF(n, toc[p2_toc_counter]->labindex);   /* r6pl2 */
                        map[0]= EOS;
                        if (toc[p2_toc_counter]->mapping>=0)
                        {       sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
                        }
                        if (bInsideAppendix)
                        {       voutlnf(":h5 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name); /* ToDo: Ist h5 richtig? */
                        }
                        else
                        {       voutlnf(":h5 id=%s%s.%s%s", n, map, numbers, name);  /* ToDo: Ist h5 richtig? */
                        }
                        break;


                case TOKPS:
                        set_inside_node5();

                        if (use_style_book)
                        {       (bInsideAppendix)       ?       sprintf(n, "%s %s", lang.appendix, numbers)
                                                                        :       sprintf(n, "%s %s", lang.chapter, numbers);
                                del_right_spaces(n);
                                if (n[0]!=EOS) strcat(n, " ");
                                strcat(n, name);
                                outln("11 changeFontSize");
                        }
                        else
                        {       if (numbers[0]!=EOS) strcat(numbers, " ");
                                sprintf(n, "%s%s", numbers, name);
                                /* Changed in r6pl16 [NHz] */
                                voutlnf("%d changeFontSize", laydat.node4size);
                        }
                        node2postscript(name, KPS_NAMEDEST); /* Changed in r6pl16 [NHz] */
                        voutlnf("/%s NameDest", name); /* New in r6pl15 [NHz] */
                        outln("newline");
                        outln("Bon");
                        /* New in V6.5.5 [NHz] */
                        node2postscript(n, KPS_CONTENT);
                        voutlnf("(%s) udoshow", n);
                        outln("Boff");
                        outln("newline");
                        voutlnf("%d changeFontSize", laydat.propfontsize); /* Changed in r6pl15 [NHz] */
                        break;

                case TODRC:
                        set_inside_node5();
                        outln("%%*");
                        voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n4_index+10000, iDrcFlags, name);
                        outln("%%*");
                        outln("");
                        break;

                case TOSRC:
                case TOSRP:
                        set_inside_node1();
                        outln("");
                        memset(n, '-', 62); n[62]= EOS;
                        voutlnf("%s  %s", sSrcRemOn, n);
                        voutlnf("    - %s", name);
                        voutlnf("    %s  %s", n, sSrcRemOff);
                        outln("");
                        break;

                case TORTF:
                        set_inside_node5();
                        outln(rtf_pardpar);

                        /* r6pl6: Indizes fuer RTF */
                        if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
                        {       strcpy(n, name);
                                winspecials2ascii(n);
                                voutf("{\\xe\\v %s}", n);
                        }

                        /* New in V6.5.9 [NHz] */
                        um_strcpy(k, name, 512, "make_subsubsubsubnode[RTF]");
                        winspecials2ascii(k);
                        node2winhelp(k);

                        if (use_style_book)
                        {
                                if (invisible)
                                        sprintf(n, "%s\\fs%d", rtf_inv_node4, iDocPropfontSize);
                                else
                                        sprintf(n, "%s\\fs%d", rtf_node4, iDocPropfontSize);
                        }
                        else
                        {
                                if (invisible)
                                {       /* Changed in r6pl16 [NHz] */
                                        /* Nodesize ist set on discrete value */
                                        sprintf(n, "%s\\fs%d", rtf_inv_node5, laydat.node5size);
                                }
                                else
                                {       /* Changed in r6pl16 [NHz] */
                                        /* Nodesize ist set on discrete value */
                                        sprintf(n, "%s\\fs%d", rtf_node5, laydat.node5size);
                                }
                        }

                        if (numbers[0]==EOS)    /* Changed in V6.5.9 [NHz] */
                        {       voutlnf("%s %s {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, k, name, k, rtf_parpard);
                        }
                        else
                        {       voutlnf("%s %s %s  {\\*\\bkmkstart %s}%s{\\*\\bkmkend %s}%s", rtf_plain, n, numbers, k, name, k, rtf_parpard);
                        }
                        voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);      /* r5pl6 */
                        break;

                case TOWIN:
                case TOWH4:
                case TOAQV:
                        set_inside_node5();

                        output_win_header(name, invisible);
                        output_aliasses();

                        if (numbers[0]!=EOS) strcat(numbers, "\\~\\~");
                        sprintf(n, "%s%s", numbers, name);
                        win_headline(n, popup);
                        break;

                case TOPCH:
                        set_inside_node5();
                        if (numbers[0]!=EOS) strcat(numbers, " ");
                        output_pch_header(numbers, name);
                        break;

                case TOHAH: /* V6.5.17 */
                case TOHTM:
                case TOMHH:
                        ti= p2_toc_counter;

                        if (!html_merge_node5)
                        {       if (!html_new_file()) return;
                                if (!toc[ti]->ignore_title)
                                {       sprintf(hx_start, "<h%d>", html_nodesize);
                                        sprintf(hx_end, "</h%d>", html_nodesize);
                                }
                        }
                        else
                        {       if (!toc[ti]->ignore_title)
                                {       sprintf(hx_start, "<h%d>", html_nodesize + 4);
                                        sprintf(hx_end, "</h%d>", html_nodesize + 4);
                                }
                                output_aliasses();
                        }

                        set_inside_node5();
                        flag= FALSE;

                        if (use_chapter_images)
                        {
            char closer[8] = "\0";
               
                                          /* no single tag closer in HTML! */
            if (html_doctype >= XHTML_STRICT)
               strcpy(closer, " /");
               
                                ti = p2_toc_counter;
            
                                if (ti >= 0 && toc[ti]->image != NULL)
                                {
                sGifSize[0] = EOS;
               
                                        if (toc[ti]->uiImageWidth!=0 && toc[ti]->uiImageHeight!=0)
                                        {
                sprintf(sGifSize, " width=\"%u\" height=\"%u\"",
                                                        toc[ti]->uiImageWidth, toc[ti]->uiImageHeight);
                                        }
               
                                        voutlnf("%s<p align=\"center\">", hx_start);
               
                                        voutlnf("<img src=\"%s%s\" alt=\"%s%s\" title=\"%s%s\" border=\"0\" %s%s>",
                                                toc[ti]->image, sDocImgSuffix, numbers, name, numbers, name, sGifSize, closer);
               
                                        voutlnf("</p>%s", hx_end);
                                        flag = TRUE;
                                }
                        }

                        do_toptoc(TOC_NODE5);   /*r6pl5*/

                        if (!flag)
                        {
                                strcpy(nameNoSty, name);
                                del_html_styles(nameNoSty);
            
            label2html(nameNoSty);      /*r6pl2*/
            voutlnf("%s<a name=\"%s\"></a>%s%s%s",      hx_start, nameNoSty, numbers, name, hx_end);
                        }
                        if (show_variable.source_filename) /* V6.5.19 */
                                voutlnf("<!-- %s: %li -->", toc[p2_toc_counter]->source_filename, toc[p2_toc_counter]->source_line);

                        break;

                case TOLDS:
                        set_inside_node5();
                        (use_style_book)        ?       voutlnf("<sect2>%s<label id=\"%s\">", name, name)
                                                                :       voutlnf("<sect3>%s<label id=\"%s\">", name, name);
                        output_aliasses();      /* r5pl8 */
                        outln("<p>");
                        break;

                case TOHPH:
                        set_inside_node5();
                        (use_style_book)        ?       voutlnf("<s4>%s", name)
                                                                :       voutlnf("<s5>%s", name);
                        output_aliasses();
                        break;
        }

}  /* make_subsubsubsubnode() */





/*******************************************************************************
*
*  c_node():
*     wrapper for make_node()
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_node(void)
{
   make_node(FALSE, FALSE);
}





/*******************************************************************************
*
*  c_node_iv():
*     wrapper for make_node()
*
*  Notes:
*     r5pl15:
*     Texinfo kennt keine versteckten Kapitel, daher wird bei den 
*     node_iv-Funktionen als Invisible-Flag statt TRUE der Wert von 
*     (desttype != TOINF) benutzt. Kurz und elegant, nicht?
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_node_iv(void)
{
   make_node(FALSE, (desttype != TOINF)); /* r5pl15 */
}





/*******************************************************************************
*
*  c_pnode():
*     wrapper for make_node()
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_pnode(void)
{
   make_node(TRUE, FALSE);
}





/*******************************************************************************
*
*  c_pnode_iv():
*     wrapper for make_node()
*
*  Notes:
*     r5pl15:
*     Texinfo kennt keine versteckten Kapitel, daher wird bei den 
*     node_iv-Funktionen als Invisible-Flag statt TRUE der Wert von 
*     (desttype != TOINF) benutzt. Kurz und elegant, nicht?
*
*  return:
*     -
*
******************************************|************************************/

GLOBAL void c_pnode_iv(void)
{
   make_node(TRUE, (desttype != TOINF));  /* r5pl15 */
}





/*******************************************************************************
*
*  set_inside_node1():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void set_inside_node1(void)
{
   active_nodetype = TOC_NODE1;
}





/*******************************************************************************
*
*  set_inside_node2():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void set_inside_node2(void)
{
   active_nodetype = TOC_NODE2;
}





/*******************************************************************************
*
*  set_inside_node3():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void set_inside_node3(void)
{
   active_nodetype = TOC_NODE3;
}





/*******************************************************************************
*
*  set_inside_node4():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void set_inside_node4(void)
{
   active_nodetype = TOC_NODE4;
}





/*******************************************************************************
*
*  set_inside_node5():
*     ??? (description)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void set_inside_node5(void)
{
   active_nodetype = TOC_NODE5;
}







GLOBAL void c_subnode(void)
{       make_subnode (FALSE, FALSE);
}       /* c_subnode */

GLOBAL void c_subnode_iv(void)
{       make_subnode (FALSE, (desttype!=TOINF));        /* r5pl15 */
}       /* c_subnode */

GLOBAL void c_psubnode(void)
{       make_subnode (TRUE, FALSE);
}       /* c_psubnode */

GLOBAL void c_psubnode_iv(void)
{       make_subnode (TRUE, (desttype!=TOINF)); /* r5pl15 */
}       /* c_psubnode */


GLOBAL void c_subsubnode(void)
{       make_subsubnode (FALSE, FALSE);
}       /* c_subsubnode */

GLOBAL void c_subsubnode_iv(void)
{       make_subsubnode (FALSE, (desttype!=TOINF));     /* r5pl15 */
}       /* c_subsubnode */

GLOBAL void c_psubsubnode(void)
{       make_subsubnode (TRUE, FALSE);
}       /* c_psubsubnode */

GLOBAL void c_psubsubnode_iv(void)
{       make_subsubnode (TRUE, (desttype!=TOINF));      /* r5pl15 */
}       /* c_psubsubnode */


GLOBAL void c_subsubsubnode(void)
{       make_subsubsubnode (FALSE, FALSE);
}       /* c_subsubsubnode */

GLOBAL void c_subsubsubnode_iv(void)
{       make_subsubsubnode (FALSE, (desttype!=TOINF));  /* r5pl15 */
}       /* c_subsubsubnode */

GLOBAL void c_psubsubsubnode(void)
{       make_subsubsubnode (TRUE, FALSE);
}       /* c_psubsubsubnode */

GLOBAL void c_psubsubsubnode_iv(void)
{       make_subsubsubnode (TRUE, (desttype!=TOINF));   /* r5pl15 */
}       /* c_psubsubsubnode */



GLOBAL void c_subsubsubsubnode(void)
{       make_subsubsubsubnode (FALSE, FALSE);
}       /* c_subsubsubsubnode */

GLOBAL void c_subsubsubsubnode_iv(void)
{       make_subsubsubsubnode (FALSE, (desttype!=TOINF));       /* r5pl15 */
}       /* c_subsubsubsubnode */

GLOBAL void c_psubsubsubsubnode(void)
{       make_subsubsubsubnode (TRUE, FALSE);
}       /* c_psubsubsubnode */

GLOBAL void c_psubsubsubsubnode_iv(void)
{       make_subsubsubsubnode (TRUE, (desttype!=TOINF));        /* r5pl15 */
}       /* c_psubsubsubsubnode */



GLOBAL void c_endnode(void)
{
        check_endnode();
}       /* c_endnode */





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
   default:
      warning_node_too_deep();
      c_subsubsubsubnode();
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
   default:
      warning_node_too_deep();
      c_subsubsubsubnode_iv();
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
   default:
      warning_node_too_deep();
      c_psubsubsubsubnode();
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
   default:
      warning_node_too_deep();
      c_psubsubsubsubnode_iv();
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
   }
}





/*******************************************************************************
*
*  tocline_make_bold():
*     make TOC entry line bold
*
*  Notes:
*     r6pl6: Kapitel werden direkt referenziert. Der zeitraubende Weg 
*     ueber auto_references() entfaellt.
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void tocline_make_bold(

char *s, 
const int depth)
{
   if (depth > 1)                         /* r6pl5: >1 statt ==1 */
   {
      switch (desttype)
      {
      case TOHAH:
      case TOHTM:
      case TOMHH:
         qreplace_once(s, "<li>", 4, "<li><b>", 7);
         qreplace_last(s, "</a>", 4, "</a></b>", 8);
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

LOCAL void tocline_handle_1st(

BOOLEAN  *f)  /* */
{
   if (*f)                                /* first */
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
      }
      
      *f = FALSE;                         /* done */
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





/* New in r6pl15 [NHz] */
/* Output of bookmarks for postscript/PDF */
GLOBAL BOOLEAN bookmarks_ps(void)
{
        register int i;
        int li, apxstart;
/* 6.3.12 [vj] Added this define for buffer checks, increased value from 128 to 148 (for Ulrich :-)) */
#define PS_BOOKM_LEN    148
        char s[PS_BOOKM_LEN], n[PS_BOOKM_LEN];

        if (p1_toc_counter<=0)
        {       return FALSE;
        }

        apxstart= 1;

        for (i=1; i<=p1_toc_counter; i++)
        {
                if (toc[i]!=NULL && !toc[i]->invisible)
                {
                        convert_toc_item(toc[i]);

                        if (toc[i]->appendix)
                        {
                                apxstart= i;    /* fuer unten merken */
                                break;                  /* r5pl6: Es kann nur einen Anhang geben */
                        }
                        else
                        {       if (toc[i]->n1 != 0)
                                {
                                        if (toc[i]->toctype==TOC_NODE1)
                                        {       /* Ein Kapitel */       

                                                li= toc[i]->labindex;

                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[1]");
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[2]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%d %s) /%s %d Bookmarks",
                                                                                        toc[i]->nr1+toc_offset,
                                                                                        n, s,
                                                                                        toc[i]->count_n2);
                                        }/* TOC_NODE1 */


                                        if (toc[i]->toctype==TOC_NODE2)
                                        {       /* Ein Abschnitt */

                                                li= toc[i]->labindex;

                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[3]");
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[4]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%d.%d %s) /%s %d Bookmarks",
                                                                                        toc[i]->nr1+toc_offset,
                                                                                        toc[i]->nr2+subtoc_offset,
                                                                                        n, s,
                                                                                        toc[i]->count_n3);
                                        }/* TOC_NODE2 */

                                        if (toc[i]->toctype==TOC_NODE3)
                                        {       /* Ein Unterabschnitt */

                                                li= toc[i]->labindex;

                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[5]");
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[6]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%d.%d.%d %s) /%s %d Bookmarks",
                                                                                        toc[i]->nr1+toc_offset,
                                                                                        toc[i]->nr2+subtoc_offset,
                                                                                        toc[i]->nr3+subsubtoc_offset,
                                                                                        n, s,
                                                                                        toc[i]->count_n4);
                                        }/* TOC_NODE3 */

                                        if (toc[i]->toctype==TOC_NODE4)
                                        {       /* Ein Paragraph */

                                                li= toc[i]->labindex;

                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[7]");
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[8]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%d.%d.%d.%d %s) /%s 0 Bookmarks",
                                                                                        toc[i]->nr1+toc_offset,
                                                                                        toc[i]->nr2+subtoc_offset,
                                                                                        toc[i]->nr3+subsubtoc_offset,
                                                                                        toc[i]->nr4+subsubsubtoc_offset,
                                                                                        n, s);
                                        }/* TOC_NODE4 */

                                        if (toc[i]->toctype==TOC_NODE5)
                                        {       /* Ein Paragraph */ /* ToDo: ??? */

                                                li= toc[i]->labindex;

                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[7.1]");
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[8.1]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%d.%d.%d.%d.%d %s) /%s 0 Bookmarks",
                                                                                        toc[i]->nr1+toc_offset,
                                                                                        toc[i]->nr2+subtoc_offset,
                                                                                        toc[i]->nr3+subsubtoc_offset,
                                                                                        toc[i]->nr4+subsubsubtoc_offset,
                                                                                        toc[i]->nr5+subsubsubsubtoc_offset,
                                                                                        n, s);
                                        }/* TOC_NODE5 */

                                }/* toc[i]->n1 > 0 */

                        }/* !toc[i]->appendix */

                }/* toc[i]!=NULL && !toc[i]->invisible */

        }/* for */

        if (!apx_available)
        {
                return TRUE;
        }

        for (i=apxstart; i<=p1_toc_counter; i++)
        {
                if (toc[i]!=NULL && !toc[i]->invisible)
                {
                        convert_toc_item(toc[i]);

                        if (toc[i]->appendix)
                        {
                                if (toc[i]->n1 != 0)
                                {
                                        if (toc[i]->toctype==TOC_NODE1)
                                        {       /* Ein Kapitel */       

                                                li= toc[i]->labindex;

                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[9]");
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[10]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%c %s) /%s %d Bookmarks",
                                                                                        'A'-1+toc[i]->nr1+toc_offset,
                                                                                        n, s,
                                                                                        toc[i]->count_n2);
                                        }/* TOC_NODE1 */


                                        if (toc[i]->toctype==TOC_NODE2)
                                        {       /* Ein Abschnitt */

                                                li= toc[i]->labindex;

                                                /*um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[11]"); v6.3.12 [vj] entfernt, da die naechste zeile gleich ist */
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[12]");
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[13]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%c.%2d %s) /%s %d Bookmarks",
                                                                                        'A'-1+toc[i]->nr1+toc_offset,
                                                                                        toc[i]->nr2+subtoc_offset,
                                                                                        n, s,
                                                                                        toc[i]->count_n3);
                                        }/* TOC_NODE2 */

                                        if (toc[i]->toctype==TOC_NODE3)
                                        {       /* Ein Unterabschnitt */

                                                li= toc[i]->labindex;

                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[14]");
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[15]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%c.%2d.%2d %s) /%s %d Bookmarks",
                                                                                        'A'-1+toc[i]->nr1+toc_offset,
                                                                                        toc[i]->nr2+subtoc_offset,
                                                                                        toc[i]->nr3+subsubtoc_offset,
                                                                                        n, s,
                                                                                        toc[i]->count_n4);
                                        }/* TOC_NODE3 */

                                        if (toc[i]->toctype==TOC_NODE4)
                                        {       /* Ein Paragraph */

                                                li= toc[i]->labindex;

                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[16]");
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[17]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%c.%2d.%2d.%2d %s) /%s 0 Bookmarks",
                                                                                        'A'-1+toc[i]->nr1+toc_offset,
                                                                                        toc[i]->nr2+subtoc_offset,
                                                                                        toc[i]->nr3+subsubtoc_offset,
                                                                                        toc[i]->nr4+subsubsubtoc_offset,
                                                                                        n, s);
                                        }/* TOC_NODE4 */

                                        if (toc[i]->toctype==TOC_NODE5)
                                        {       /* Ein Paragraph */     /* ToDo: ??? */

                                                li= toc[i]->labindex;

                                                um_strcpy(s, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[16]");
                                                /* Changed in r6pl16 [NHz] */
                                                um_strcpy(n, lab[li]->name, PS_BOOKM_LEN, "bookmarks_ps[17]");
                                                node2postscript(n, KPS_BOOKMARK);
                                                node2postscript(s, KPS_NAMEDEST);
                                                voutlnf("(%c.%2d.%2d.%2d.%2d %s) /%s 0 Bookmarks",
                                                                                        'A'-1+toc[i]->nr1+toc_offset,
                                                                                        toc[i]->nr2+subtoc_offset,
                                                                                        toc[i]->nr3+subsubtoc_offset,
                                                                                        toc[i]->nr4+subsubsubtoc_offset,
                                                                                        toc[i]->nr5+subsubsubsubtoc_offset,
                                                                                        n, s);
                                        }/* TOC_NODE5 */

                                }/* toc[i]->n1 > 0 */

                        }/* !toc[i]->appendix */

                }/* toc[i]!=NULL && !toc[i]->invisible */

        }/* for */

        outln("");

        return TRUE;
}       /* bookmarks_ps */


/* New in r6pl16 [NHz] */
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
               if ((toc[i]->toctype == TOC_NODE1) && (toc[i]->appendix))
               {                          /* a subsubsubnode */ 
               
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
*     create output for !use_auto_toptocs command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void toc_output(

const int         depth)              /* */
{
   register int   i;                  /* */
   int            li;                 /* */
   char           n[512],             /* */
                  ref[512];           /* */
   BOOLEAN        leerzeile = FALSE;  /* TRUE: output an empty line */
   BOOLEAN        last_n = FALSE;     /* TRUE: this node is last node */
   BOOLEAN        last_sn = FALSE;    /* TRUE: this node is last subnode */
   BOOLEAN        last_ssn = FALSE;   /* TRUE: this node is last subsubnode */
   BOOLEAN        last_sssn = FALSE;  /* TRUE: this node is last subsubsubnode */
   BOOLEAN        last_ssssn = FALSE; /* TRUE: this node is last subsubsubsubnode */
   BOOLEAN        first = TRUE;       /* */
   BOOLEAN        old;                /* */

   
   if (desttype == TOLYX)                 /* LYX doesn't support !toc */
      return;
   
   if (p1_toc_counter <= 0)               /* nothing to do */
      return;
   
   
   old = bDocAutorefOff;
   bDocAutorefOff = FALSE;
   
   for (i = 1; i <= p1_toc_counter; i++)  /* walk through all collected nodes from pass1() */
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);
   
         if (toc[i]->appendix)            /* r5pl6: Es kann nur einen Anhang geben */
            break;

         if (toc[i]->n1 != 0)             /* valid node */
         {
                                          /* current is a node */     
            if (toc[i]->toctype == TOC_NODE1)
            {
               /* --- check first if we have to close previous items --- */
               
               if (use_toc_list_commands)
               {
                  if (last_n)             /* close last node item */
                  {
                     if (use_toc_list_commands == TOCL_HTM)
                        outln("\t</li>");
                     else
                        outln(toc_list_end);
                     
                     last_n = FALSE;
                  }
                  
                  if (last_sn)
                  {
                     if (use_toc_list_commands == TOCL_HTM)
                     {
                        outln("\t\t\t</li>");
                        outln("\t\t</ul>");
                        outln("\t</li>");
                     }
                     else
                        outln(toc_list_end);
                     
                     last_sn = FALSE;
                  }
                  
                  if (last_ssn)
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
                     
                     last_ssn = FALSE;
                  }

                  if (last_sssn)
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
                     
                     last_sssn = FALSE;
                  }

                  if (last_ssssn)
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
                     
                     last_ssssn = FALSE;
                  }
               }
               
               last_n = TRUE;             /* we're a node! */

               li = toc[i]->labindex;
               string2reference(ref, lab[li], TRUE, "", 0, 0);
               
               if (no_numbers)
                  sprintf(n, form_t1_n1, ref);
               else
                  sprintf(n, form_t1_n1, toc[i]->nr1 + toc_offset, ref);
               
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
               
               tocline_handle_1st(&first);

               if (use_toc_list_commands == TOCL_HTM)
                  out("\t");
                  
               outln(n);                  /* output the node item! */
               
               leerzeile = TRUE;
               
            }  /* TOC_NODE1 */

   
            if (depth > 1)
            {                             /* current is a subnode */
               if (toc[i]->toctype == TOC_NODE2)
               {
                  /* --- check first if we have to close previous items --- */

                  if (use_toc_list_commands)
                  {
                     if (last_n)
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           out("\t\t");
                        
                        outln(toc_list_top);
                        
                        last_n = FALSE;
                     }
                     
                     if (last_sn)         /* close last subnode item */
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           outln("\t\t\t</li>");
                        else
                           outln(toc_list_end);
                        
                        last_sn = FALSE;
                     }
                     
                     if (last_ssn)
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                        {
                           outln("\t\t\t\t\t</li>");
                           outln("\t\t\t\t</ul>");
                           outln("\t\t\t</li>");
                        }
                        else
                           outln(toc_list_end);
                        
                        last_ssn = FALSE;
                     }
                     
                     if (last_sssn)
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
                        
                        last_sssn = FALSE;
                     }

                     if (last_ssssn)
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

                        last_ssssn = FALSE;
                     }
                  }
               
                  last_sn = TRUE;         /* we're a subnode! */
                  
                  li = toc[i]->labindex;
                  string2reference(ref, lab[li], TRUE, "", 0, 0);
               
                  if (no_numbers)
                     sprintf(n, form_t1_n2, ref);
                  else
                  {
                     sprintf(n, form_t1_n2, 
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset, ref);
                  }
               
                  tocline_handle_1st(&first);
               
                  if (use_toc_list_commands == TOCL_HTM)
                     out("\t\t\t");
                     
                  outln(n);               /* output subnode item! */
                  
               }  /* TOC_NODE2 */
               
            }  /* depth > 1 */
   
   
            if (depth > 2)
            {                             /* current is a a subsubnode */
               if (toc[i]->toctype == TOC_NODE3)
               {
                  /* --- check first if we have to close previous items --- */

                  if (use_toc_list_commands)
                  {
                     if (last_n)
                     {                    /* should not be reached! */
                        voutlnf("%s%s", toc_list_top, toc_list_top);
                        
                        last_n = FALSE;
                     }
                     
                     if (last_sn)
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           out("\t\t\t\t");
                           
                        outln(toc_list_top);
                        
                        last_sn = FALSE;
                     }
                     
                     if (last_ssn)        /* close last subsubnode item */
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           outln("\t\t\t\t\t</li>");
                        else
                           outln(toc_list_end);
                        
                        last_ssn = FALSE;
                     }
                     
                     if (last_sssn)
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                        {
                           outln("\t\t\t\t\t\t\t</li>");
                           outln("\t\t\t\t\t\t</ul>");
                           outln("\t\t\t\t\t</li>");
                        }
                        else
                           outln(toc_list_end);
                        
                        last_sssn = FALSE;
                     }
                     
                     if (last_ssssn)
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
                        
                        last_ssssn = FALSE;
                     }
                  }
                     
                  last_ssn = TRUE;        /* we're a subsubnode! */
                  
                  li = toc[i]->labindex;
                  string2reference(ref, lab[li], TRUE, "", 0, 0);
                  
                  if (no_numbers)
                     sprintf(n, form_t1_n3, ref);
                  else
                  {
                     sprintf(n, form_t1_n3, toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset, ref);
                  }
                  
                  tocline_handle_1st(&first);
                  
                  if (use_toc_list_commands == TOCL_HTM)
                     out("\t\t\t\t\t");
                  
                  outln(n);               /* output subsubnode item! */
                  
               }  /* TOC_NODE3 */
               
            }  /* depth > 2 */
   
   
            if (depth > 3)
            {                             /* current is a subsubsubnode */
               if (toc[i]->toctype == TOC_NODE4)
               {
                  /* --- check first if we have to close previous items --- */
                  
                  if (use_toc_list_commands)
                  {
                     if (last_n)
                     {
                                          /* should not be reached! */
                        voutlnf("%s%s%s", toc_list_top, toc_list_top, toc_list_top);
                        last_n = FALSE;
                     }
                     
                     if (last_sn)
                     {
                                          /* should not be reached! */
                        voutlnf("%s%s", toc_list_top, toc_list_top);
                        last_sn = FALSE;
                     }
                     
                     if (last_ssn)
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           out("\t\t\t\t\t\t");
                        
                        outln(toc_list_top);
                        
                        last_ssn = FALSE;
                     }
                     
                     if (last_sssn)       /* close last subsubsubnode item */
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           outln("\t\t\t\t\t\t\t</li>");
                        else
                           outln(toc_list_end);
                        
                        last_sssn = FALSE;
                     }
                     
                     if (last_ssssn)
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                        {
                           outln("\t\t\t\t\t\t\t\t\t</li>");
                           outln("\t\t\t\t\t\t\t\t</ul>");
                           outln("\t\t\t\t\t\t\t</li>");
                        }
                        else
                           outln(toc_list_end);
                        
                        last_ssssn = FALSE;
                     }
                  }
               
                  last_sssn = TRUE;       /* we're a subsubsubnode! */
                  
                  li = toc[i]->labindex;
                  string2reference(ref, lab[li], TRUE, "", 0, 0);
                  
                  if (no_numbers)
                     sprintf(n, form_t1_n4, ref);
                  else
                  {
                     sprintf(n, form_t1_n4,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        ref);
                  }
            
                  tocline_handle_1st(&first);
               
                  if (use_toc_list_commands == TOCL_HTM)
                     out("\t\t\t\t\t\t\t");
                  
                  outln(n);
            
               }  /* TOC_NODE4 */
         
            }  /* if (depth > 3) */
      
            if (depth > 4)
            {
                                          /* current is a subsubsubsubnode */
               if (toc[i]->toctype == TOC_NODE5)
               {
                  /* --- check first if we have to close previous items --- */

                  if (use_toc_list_commands)
                  {
                     if (last_n)
                     {
                                          /* should not be reached! */
                        voutlnf("%s%s%s", toc_list_top, toc_list_top, toc_list_top);
                        last_n = FALSE;
                     }
                     
                     if (last_sn)
                     {
                                          /* should not be reached! */
                        voutlnf("%s%s", toc_list_top, toc_list_top);
                        last_sn = FALSE;
                     }
                     
                     if (last_ssn)
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           out("");
                           
                        outln(toc_list_top);
                        
                        last_ssn = FALSE;
                     }
                     
                     if (last_sssn)
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           out("\t\t\t\t\t\t\t\t");
                        
                        outln(toc_list_top);
                        
                        last_sssn = FALSE;
                     }

                     if (last_ssssn)      /* close last subsubsubnode item */
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           outln("\t\t\t\t\t\t\t\t\t</li>");
                        else
                           outln(toc_list_end);
                        
                        last_ssssn = FALSE;
                     }
                  }
               
                  last_ssssn = TRUE;      /* we're a subsubsubsubnode! */
                  
                  li = toc[i]->labindex;
                  string2reference(ref, lab[li], TRUE, "", 0, 0);
                  
                  if (no_numbers)
                     sprintf(n, form_t1_n5, ref);
                  else
                  {
                     sprintf(n, form_t1_n5,
                        toc[i]->nr1 + toc_offset,
                        toc[i]->nr2 + subtoc_offset,
                        toc[i]->nr3 + subsubtoc_offset,
                        toc[i]->nr4 + subsubsubtoc_offset,
                        toc[i]->nr5 + subsubsubsubtoc_offset,
                        ref);
                  }
            
                  tocline_handle_1st(&first);
               
                  if (use_toc_list_commands == TOCL_HTM)
                     out("\t\t\t\t\t\t\t\t\t");
                  
                  outln(n);               /* output subsubsubsubnode item! */
            
               }  /* TOC_NODE5 */
         
            }  /* if (depth > 4) */

         }  /* toc[i]->n1 > 0 */

      }  /* toc[i] != NULL && !toc[i]->invisible */
   
   }  /* for */
   
   
   /* --- close TOC listing --- */
   
   switch (desttype)
   {
   case TOHAH:
   case TOHTM:
   case TOMHH:
      if (last_ssssn)
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
         
      if (last_sssn)
      {
         outln("\t\t\t\t\t\t\t</li>");
         outln("\t\t\t\t\t\t</ul>");
         outln("\t\t\t\t\t</li>");
         outln("\t\t\t\t</ul>");
         outln("\t\t\t</li>");
         outln("\t\t</ul>");
      }
         
      if (last_ssn)
      {
         outln("\t\t\t\t\t</li>");
         outln("\t\t\t\t</ul>");
         outln("\t\t\t</li>");
         outln("\t\t</ul>");
      }
         
      if (last_sn)
      {
         outln("\t\t\t</li>");
         outln("\t\t</ul>");
      }


      outln("\t</li>");
      outln("</ul>\n");
      break;
      
      
   case TOTEX:
   case TOPDL:
      if (last_ssssn)
         voutlnf("%s%s%s%s", toc_list_end, toc_list_end, toc_list_end, toc_list_end);
      
      if (last_sssn)
         voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
      
      if (last_ssn)
         voutlnf("%s%s", toc_list_end, toc_list_end);
      
      if (last_sn)
         outln(toc_list_end);
      
      outln(toc_list_end);
      
      break;
      
      
   case TOWIN:
   case TOWH4:
   case TOAQV:
      outln("\\par ");
      break;
      
      
   case TOINF:
      if (!apx_available && !no_index && bCalledIndex && use_udo_index)
      {
         outln("");
         voutlnf("* %s::", lang.index);
      }
      
      outln("@end menu");
      break;
      
      
   case TOSTG:
   case TOAMG:
      if (!apx_available)
      {
         outln("");
      }
   }
   
   bDocAutorefOff = old;

}  /* toc_output */





/*******************************************************************************
*
*  subtoc_output():
*     create output for !use_auto_subtocs command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void subtoc_output(

const int         depth)                /* */
{
   register int   i;                    /* */
   int            li;                   /* */
   char           n[512],               /* */
                  ref[512];             /* */
   BOOLEAN        last_sn = FALSE;    /* TRUE: this node is last subnode */
   BOOLEAN        last_ssn = FALSE;   /* TRUE: this node is last subsubnode */
   BOOLEAN        last_sssn = FALSE;  /* TRUE: this node is last subsubsubnode */
   BOOLEAN        last_ssssn = FALSE; /* TRUE: this node is last subsubsubsubnode */
   BOOLEAN        output_done = FALSE;  /* */
   BOOLEAN        first       = TRUE;   /* */
   BOOLEAN        old;                  /* */


   if (desttype == TOLYX)                 /* LYX doesn't support !toc */
      return;
   
   if (p1_toc_counter <= 0)               /* nothing to do */
      return;
   
   if (toc[p2_toc_counter]->ignore_subtoc)
      return;

   old = bDocAutorefOff;
   bDocAutorefOff = FALSE;

                                          /* walk through all nodes after last n1 */
   for (i = last_n1_index; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);

         if (toc[i]->appendix)            /* r5pl6: Nach dem ersten Anhang-Node kommt nichts mehr */
            break;

         if (toc[i]->n1 > p2_toc_n1)      /* r5pl6: Das waren alle nodes */
            break;

         if (toc[i]->n1 != 0)             /* valid node */
         {
            if (toc[i]->n1 == p2_toc_n1)
            {
                                          /* current is a subnode */
               if (toc[i]->toctype == TOC_NODE2)
               {
                  /* --- check first if we have to close previous items --- */
                  
                  if (use_toc_list_commands)
                  {
                     if (last_sn)         /* close last subnode item */
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                           outln("\t</li>");
                        else
                           outln(toc_list_end);
                        
                        last_sn = FALSE;
                     }
                     
                     if (last_ssn)
                     {
                        if (use_toc_list_commands == TOCL_HTM)
                        {
                           outln("\t\t\t</li>");
                           outln("\t\t</ul>");
                           outln("\t</li>");
                        }
                        else
                           outln(toc_list_end);
                           
                        last_ssn = FALSE;
                     }
                     
                     if (last_sssn)
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
                        
                        last_sssn = FALSE;
                     }

                     if (last_ssssn)
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
                        
                        last_ssssn = FALSE;
                     }
                  }

                  last_sn = TRUE;         /* we're a subnode */

                  li = toc[i]->labindex;
                  string2reference(ref, lab[li], TRUE, "", 0, 0);

                  if (no_numbers)
                     sprintf(n, form_t2_n2, ref);
                  else
                  {
                     sprintf(n, form_t2_n2, 
                           toc[i]->nr1 + toc_offset, 
                           toc[i]->nr2 + subtoc_offset, 
                           ref);
                  }

                  tocline_handle_1st(&first);
                  
                  if (use_toc_list_commands == TOCL_HTM)
                     out("\t");
                     
                  outln(n);               /* output the subnode item! */
                  
                  output_done = TRUE;
                  
               }  /* TOC_NODE2 */


               if (depth > 1)
               {                          /* current is a subsubnode */
                  if (toc[i]->toctype == TOC_NODE3)
                  {
                     /* --- check first if we have to close previous items --- */
                     
                     if (use_toc_list_commands)
                     {
                        if (last_sn)
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                              out("\t\t");
                              
                           outln(toc_list_top);
                           
                           last_sn = FALSE;
                        }
                     
                        if (last_ssn)     /* close last subsubnode item */
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                              outln("\t\t\t</li>");
                           else
                              outln(toc_list_end);
                           
                           last_ssn = FALSE;
                        }
                     
                        if (last_sssn)
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                           {
                              outln("\t\t\t\t\t</li>");
                              outln("\t\t\t\t</ul>");
                              outln("\t\t\t</li>");
                           }
                           else
                              outln(toc_list_end);
                           
                           last_sssn = FALSE;
                        }

                        if (last_ssssn)
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
                           
                           last_ssssn = FALSE;
                        }
                     }
                     
                     last_ssn = TRUE;     /* we're a subsubnode */

                     li = toc[i]->labindex;
                     string2reference(ref, lab[li], TRUE, "", 0, 0);

                     if (no_numbers)
                        sprintf(n, form_t2_n3, ref);
                     else
                     {
                        sprintf(n, form_t2_n3, 
                              toc[i]->nr1 + toc_offset,
                              toc[i]->nr2 + subtoc_offset,
                              toc[i]->nr3 + subsubtoc_offset,
                              ref);
                     }

                     tocline_handle_1st(&first);
                     
                     if (use_toc_list_commands == TOCL_HTM)
                        out("\t\t\t");
                        
                     outln(n);            /* output the subsubnode item! */
                     
                     output_done = TRUE;

                  } /* TOC_NODE3 */

               }  /* depth > 1 */


               if (depth > 2)
               {                          /* current is a subsubsubnode */
                  if (toc[i]->toctype == TOC_NODE4)
                  {
                     /* --- check first if we have to close previous items --- */
                     
                     if (use_toc_list_commands)
                     {
                        if (last_sn)
                        {
                           outln(toc_list_top);
                           
                           last_sn = FALSE;
                        }
                        
                        if (last_ssn)
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                              out("\t\t\t\t");
                              
                           outln(toc_list_top);

                           last_ssn = FALSE;
                        }
                        
                        if (last_sssn)    /* close last subsubsubnode item */
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                              outln("\t\t\t\t\t</li>");
                           else
                              outln(toc_list_end);
                           
                           last_sssn = FALSE;
                        }
                      
                        if (last_ssssn)
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                           {
                              outln("\t\t\t\t\t\t\t</li>");
                              outln("\t\t\t\t\t\t</ul>");
                              outln("\t\t\t\t\t</li>");
                           }
                           else
                              outln(toc_list_end);
                              
                           last_sssn = FALSE;
                        }
                     }

                     last_sssn = TRUE;    /* we're a subsubsubnode */

                     li = toc[i]->labindex;
                     string2reference(ref, lab[li], TRUE, "", 0, 0);

                     if (no_numbers)
                     {
                        sprintf(n, form_t2_n4, ref);
                     }
                     else
                     {
                        sprintf(n, form_t2_n4,
                              toc[i]->nr1 + toc_offset,
                              toc[i]->nr2 + subtoc_offset,
                              toc[i]->nr3 + subsubtoc_offset,
                              toc[i]->nr4 + subsubsubtoc_offset,
                              ref);
                     }
   
                     tocline_handle_1st(&first);

                     if (use_toc_list_commands == TOCL_HTM)
                        out("\t\t\t\t\t");
                        
                     outln(n);            /* output the subsubsubnode item! */
                     
                     output_done = TRUE;

                  } /* TOC_NODE4 */

               }  /* depth > 2 */


               if (depth > 3)
               {                          /* current is a subsubsubsubnode */
                  if (toc[i]->toctype == TOC_NODE5)
                  {
                     /* --- check first if we have to close previous items --- */
                     
                     if (use_toc_list_commands)
                     {
                        if (last_sn)
                        {
                                          /* should not be reached! */
                           outln(toc_list_top);
                           
                           last_sn = FALSE;
                        }
                     
                        if (last_ssn)
                        {
                                          /* should not be reached! */
                           outln(toc_list_top);
                           
                           last_ssn = FALSE;
                        }
                     
                        if (last_sssn)
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                              out("\t\t\t\t\t\t");
                              
                           outln(toc_list_top);
                           
                           last_ssn = FALSE;
                        }
                     }

                     last_ssssn = TRUE;   /* we're a subsubsubsubnode */
                     
                     li = toc[i]->labindex;
                     string2reference(ref, lab[li], TRUE, "", 0, 0);

                     if (no_numbers)
                        sprintf(n, form_t2_n5, ref);
                     else
                     {
                        sprintf(n, form_t2_n5,
                              toc[i]->nr1 + toc_offset,
                              toc[i]->nr2 + subtoc_offset,
                              toc[i]->nr3 + subsubtoc_offset,
                              toc[i]->nr4 + subsubsubtoc_offset,
                              toc[i]->nr5 + subsubsubsubtoc_offset,
                              ref);
                     }

                     tocline_handle_1st(&first);
                     
                     if (use_toc_list_commands == TOCL_HTM)
                        out("\t\t\t\t\t\t\t");
                        
                     outln(n);
                     
                     output_done = TRUE;
   
                  }  /* TOC_NODE5 */
   
               }  /* depth > 3 */

            }
         }
      }
   }

   if (output_done)
   {
      switch (desttype)
      {
      case TOHAH: /* V6.5.17 */
      case TOHTM:
      case TOMHH:
         if (last_ssssn)
         {
            outln("\t\t\t\t\t\t\t</li>");
            outln("\t\t\t\t\t\t</ul>");
            outln("\t\t\t\t\t</li>");
            outln("\t\t\t\t</ul>");
            outln("\t\t\t</li>");
            outln("\t\t</ul>");
         }
         
         if (last_sssn)
         {
            outln("\t\t\t\t\t</li>");
            outln("\t\t\t\t</ul>");
            outln("\t\t\t</li>");
            outln("\t\t</ul>");
         }
         
         if (last_ssn)
         {
            outln("\t\t\t</li>");
            outln("\t\t</ul>");
         }
         
         outln("\t</li>");
         outln("</ul>\n");

         break;


      case TOTEX:
      case TOPDL:
         if (last_ssssn)
            voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
      
         if (last_sssn)
            voutlnf("%s%s", toc_list_end, toc_list_end);
      
         if (last_ssn)
            outln(toc_list_end);
      
         outln(toc_list_end);
         break;


      case TOAQV:
      case TOWIN:
      case TOWH4:
         outln(rtf_par);
         outln(rtf_pard);
         break;
         
         
      case TOINF:
         outln("@end menu");
         break;
         
         
      default:
         outln("");
      }
   }

   bDocAutorefOff = old;

}  /* subtoc_output() */





/*******************************************************************************
*
*  subsubtoc_output():
*     create output for !use_auto_subsubtocs command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void subsubtoc_output(

const int         depth)                /* */
{
   register int   i;                    /* */
   int            li;                   /* */
   char           n[512],               /* */
                  ref[512];             /* */
   BOOLEAN        last_ssn    = FALSE;  /* */
   BOOLEAN        last_sssn   = FALSE;  /* */
   BOOLEAN        last_ssssn  = FALSE;  /* */
   BOOLEAN        output_done = FALSE;  /* */
   BOOLEAN        first       = TRUE;   /* */
   BOOLEAN        old;                  /* */


   if (desttype == TOLYX)                 /* LYX doesn't support !toc */
      return;
   
   if (p1_toc_counter <= 0)               /* nothing to do */
      return;
   
   if (toc[p2_toc_counter]->ignore_subtoc)
      return;

   if (last_n2_index == 0)                /* Wer benutzt !subsubtoc in einem Node? */
      return;

   old = bDocAutorefOff;
   bDocAutorefOff = FALSE;

                                          /* walk through all nodes after last n2 */
   for (i = last_n2_index; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);

         if (toc[i]->appendix)            /* r5pl6: Nach dem ersten Anhang-Node kommt nichts mehr */
            break;

         if (toc[i]->n1 > p2_toc_n1)      /* r5pl6: Das waren dann alle */
            break;

         if (toc[i]->n1 != 0)             /* valid node */
         {
            if (toc[i]->n1 == p2_toc_n1)
            {
               if (toc[i]->n2 > p2_toc_n2)/* r5pl6: Das waren dann alle */
                  break;

               if (toc[i]->n2 == p2_toc_n2)
               {
                                          /* current is a subsubnode */     
                  if (toc[i]->toctype == TOC_NODE3)
                  {
                     /* --- check first if we have to close previous items --- */
                     
                     if (use_toc_list_commands)
                     {
                        if (last_ssn)     /* close last subsubnode item */
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                              outln("\t</li>");
                           else
                              outln(toc_list_end);
                           
                           last_ssn = FALSE;
                        }
                        
                        if (last_sssn)
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                           {
                              outln("\t\t\t</li>");
                              outln("\t\t</ul>");
                              outln("\t</li>");
                           }
                           else
                              outln(toc_list_end);
                        
                           last_sssn = FALSE;
                        }
                        
                        if (last_ssssn)
                        {
                           if (use_toc_list_commands == TOCL_HTM)
                           {
                              outln("t\t\t\t\t</li>");
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
                        
                           last_ssssn = FALSE;
                        }
                     }

                     last_ssn = TRUE;     /* we're a subsubnode */

                     li = toc[i]->labindex;
                     string2reference(ref, lab[li], TRUE, "", 0, 0);

                     if (no_numbers)
                        sprintf(n, form_t3_n3, ref);
                     else
                     {
                        sprintf(n, form_t3_n3, 
                              toc[i]->nr1 + toc_offset,
                              toc[i]->nr2 + subtoc_offset,
                              toc[i]->nr3 + subsubtoc_offset,
                              ref);
                     }

                     tocline_handle_1st(&first);
                     
                     if (use_toc_list_commands == TOCL_HTM)
                        out("\t");
                        
                     outln(n);            /* output the subsubnode item! */
                     
                     output_done = TRUE;

                  }  /* TOC_NODE3 */
                  

                  if (depth > 1)
                  {                       /* current is a subsubsubnode */
                     if (toc[i]->toctype == TOC_NODE4)
                     {
                        /* --- check first if we have to close previous items --- */
                        
                        if (use_toc_list_commands)
                        {
                           if (last_ssn)
                           {
                              if (use_toc_list_commands == TOCL_HTM)
                                 out("\t\t");
                                 
                              outln(toc_list_top);
                              
                              last_ssn = FALSE;
                           }
                           
                           if (last_sssn) /* close last subsubsubnode item */
                           {
                              if (use_toc_list_commands == TOCL_HTM)
                                 outln("\t\t\t</li>");
                              else
                                 outln(toc_list_end);
                              
                              last_sssn = FALSE;
                           }
                           
                           if (last_ssssn)
                           {
                              if (use_toc_list_commands == TOCL_HTM)
                              {
                                 outln("\t\t\t\t\t</li>");
                                 outln("\t\t\t\t</ul>");
                                 outln("\t\t\t</li>");
                              }
                              else
                                 outln(toc_list_end);
                           
                              last_ssssn = FALSE;
                           }
                                          /* we're a subsubsubnode */
                           last_sssn = TRUE;
                        }

                        li = toc[i]->labindex;
                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                        if (no_numbers)
                           sprintf(n, form_t3_n4, ref);
                        else
                        {
                           sprintf(n, form_t3_n4,
                                 toc[i]->nr1 + toc_offset,
                                 toc[i]->nr2 + subtoc_offset,
                                 toc[i]->nr3 + subsubtoc_offset,
                                 toc[i]->nr4 + subsubsubtoc_offset,
                                 ref);
                        }

                        tocline_handle_1st(&first);
                        
                        if (use_toc_list_commands == TOCL_HTM)
                           out("\t\t\t");
                           
                        outln(n);         /* output the subsubsubnode item! */
                        
                        output_done = TRUE;

                     }  /* TOC_NODE4 */
                  }


                  if (depth > 2)
                  {                       /* current is a subsubsubsubnode */
                     if (toc[i]->toctype == TOC_NODE5)
                     {
                        /* --- check first if we have to close previous items --- */
                        
                        if (use_toc_list_commands)
                        {
                           if (last_ssn)
                           {
                                          /* should not be reached! */
                              outln(toc_list_top);
                              
                              last_ssn = FALSE;
                           }
                           
                           if (last_sssn)
                           {
                              if (use_toc_list_commands == TOCL_HTM)
                                 out("\t\t");
                                 
                              outln(toc_list_top);
                              
                              last_sssn = FALSE;
                           }
                        }

                        last_ssssn = TRUE;/* we're a subsubsubsubnode */ 

                        li = toc[i]->labindex;
                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                        if (no_numbers)
                           sprintf(n, form_t3_n5, ref);
                        else
                        {
                           sprintf(n, form_t3_n5,
                                 toc[i]->nr1 + toc_offset,
                                 toc[i]->nr2 + subtoc_offset,
                                 toc[i]->nr3 + subsubtoc_offset,
                                 toc[i]->nr4 + subsubsubtoc_offset,
                                 toc[i]->nr5 + subsubsubsubtoc_offset,
                                 ref);
                        }

                        tocline_handle_1st(&first);
                        
                        if (use_toc_list_commands == TOCL_HTM)
                           out("\t\t\t\t\t");
                           
                        outln(n);         /* output the subsubsubsubnode item! */
                        
                        output_done = TRUE;

                     }  /* TOC_NODE5 */
                  }
               }
            }
         }
      }
   }

   if (output_done)
   {
      switch (desttype)
      {
      case TOHAH: /* V6.5.17 */
      case TOHTM:
      case TOMHH:
         if (last_ssssn)
         {
            outln("\t\t\t\t\t</li>");
            outln("\t\t\t\t</ul>");
            outln("\t\t\t</li>");
            outln("\t\t</ul>");
         }
         
         if (last_sssn) 
         {
            outln("\t\t\t</li>");
            outln("\t\t</ul>");
         }

         outln("\t</li>");
         outln("</ul>\n");
         break;
         

      case TOTEX:
      case TOPDL:
         if (last_ssssn)
            voutlnf("%s%s", toc_list_end, toc_list_end);

         if (last_sssn)
            outln(toc_list_end);
            
         outln(toc_list_end);
         break;
         
         
      case TOAQV:
      case TOWIN:
      case TOWH4:
         outln(rtf_par);
         outln(rtf_pard);
         break;
         
         
      case TOINF:
         outln("@end menu");
         break;
         
         
      default:
         outln("");
      }
   }

   bDocAutorefOff = old;

}  /* subsubtoc_output() */





/*******************************************************************************
*
*  subsubsubtoc_output():
*     create output for !use_auto_subsubsubtocs command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void subsubsubtoc_output(

const int         depth)                /* */
{
   register int   i;                    /* */
   int            li;                   /* */
   char           n[512],               /* */
                  ref[512];             /* */
   BOOLEAN        last_sssn   = FALSE;  /* */
   BOOLEAN        last_ssssn  = FALSE;  /* */
   BOOLEAN        output_done = FALSE;  /* */
   BOOLEAN        first       = TRUE;   /* */
   BOOLEAN        old;                  /* */


   if (desttype == TOLYX)                 /* LYX doesn't support !toc */
      return;
   
   if (p1_toc_counter <= 0)               /* nothing to do */
      return;
   
   if (toc[p2_toc_counter]->ignore_subtoc)
      return;

   if (last_n2_index == 0)                /* Wer benutzt !subsubsubtoc in einem Node? */
      return;

   if (last_n3_index == 0)                /* Wer benutzt !subsubsubtoc in einem Subnode? */
      return;


   old = bDocAutorefOff;
   bDocAutorefOff = FALSE;

                                          /* walk through all nodes after last n3 */
   for (i = last_n3_index; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);

         if (toc[i]->appendix)           /* r5pl6: Nach dem ersten Anhang-Node kommt nichts mehr */
            break;

         if (toc[i]->n1 > p2_toc_n1)     /* r5pl6: Das waren dann alle */
            break;

         if (toc[i]->n1 != 0)
         {
            if (toc[i]->n1 == p2_toc_n1)
            {
                                         /* r5pl6: Das waren dann alle */
               if (toc[i]->n2 > p2_toc_n2)
                  break;

               if (toc[i]->n2 == p2_toc_n2)
               {
                                         /* r5pl6: Das waren dann alle */
                  if (toc[i]->n3 > p2_toc_n3)
                     break;

                  if (toc[i]->n3 == p2_toc_n3)
                  {                      /* current is a subsubsubnode */
                     if (toc[i]->toctype == TOC_NODE4)
                     {
                        /* --- check first if we have to close previous items --- */
                        
                        if (use_toc_list_commands)
                        {
                           if (last_sssn)/* close last subsubsubnode item */
                           {
                              if (use_toc_list_commands == TOCL_HTM)
                                 outln("\t</li>");
                              else
                                 outln(toc_list_end);
                           
                              last_sssn = FALSE;
                           }
                           
                           if (last_ssssn)
                           {
                              if (use_toc_list_commands == TOCL_HTM)
                              {
                                 outln("\t\t\t</li>");
                                 outln("\t\t</ul>");
                                 outln("\t</li>");
                              }
                              else
                                 outln(toc_list_end);
                              
                              last_ssssn = FALSE;
                           }
                        }

                        last_sssn = TRUE;

                        li = toc[i]->labindex;
                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                        if (no_numbers)
                           sprintf(n, form_t4_n4, ref);
                        else
                        {
                           sprintf(n, form_t4_n4,
                              toc[i]->nr1 + toc_offset,
                              toc[i]->nr2 + subtoc_offset,
                              toc[i]->nr3 + subsubtoc_offset,
                              toc[i]->nr4 + subsubsubtoc_offset,
                              ref);
                        }

                        tocline_handle_1st(&first);
                        
                        if (use_toc_list_commands == TOCL_HTM)
                           out("\t");
                           
                        outln(n);
                        
                        output_done = TRUE;

                     }  /* TOC_NODE4 */


                     if (depth > 1)
                     {                   /* current is a subsubsubsubnode */
                        if (toc[i]->toctype == TOC_NODE5)
                        {
                           /* --- check first if we have to close previous items --- */
                           
                           if (use_toc_list_commands)
                           {
                              if (last_sssn)
                              {
                                 if (use_toc_list_commands == TOCL_HTM)
                                    out("\t\t");
                                 
                                 outln(toc_list_top);
                                 
                                 last_sssn = FALSE;
                              }
                                         /* close last subsubsubsubnode item */                             
                              if (last_ssssn)
                              {
                                 if (use_toc_list_commands == TOCL_HTM)
                                    outln("\t\t\t</li>");
                                 else
                                    outln(toc_list_end);
                                 
                                 last_sssn = FALSE;
                              }
                           }

                           last_ssssn = TRUE;
                           
                           li = toc[i]->labindex;
                           string2reference(ref, lab[li], TRUE, "", 0, 0);

                           if (no_numbers)
                              sprintf(n, form_t4_n5, ref);
                           else
                           {
                              sprintf(n, form_t4_n5,
                                    toc[i]->nr1 + toc_offset,
                                    toc[i]->nr2 + subtoc_offset,
                                    toc[i]->nr3 + subsubtoc_offset,
                                    toc[i]->nr4 + subsubsubtoc_offset,
                                    toc[i]->nr5 + subsubsubsubtoc_offset,
                                    ref);
                           }

                           tocline_handle_1st(&first);

                           if (use_toc_list_commands == TOCL_HTM)
                              out("\t\t\t");
                              
                           outln(n);     /* output subsubsubsubnode item! */
                           
                           output_done = TRUE;

                        }  /* TOC_NODE5 */

                     }  /* depth>1 */

                  }
               }
            }
         }
      }
   }

   if (output_done)
   {
      switch (desttype)
      {
      case TOHAH: /* V6.5.17 */
      case TOHTM:
      case TOMHH:
         if (last_ssssn)
         {
            outln("\t\t\t</li>");
            outln("\t\t</ul>");
         }

         outln("\t</li>");
         outln("</ul>\n");
         break;
         
         
      case TOTEX:
      case TOPDL:
         if (last_ssssn)
            voutlnf("%s%s", toc_list_end, toc_list_end);
 
         outln(toc_list_end);
         break;
         
         
      case TOAQV:
      case TOWIN:
      case TOWH4:
         outln(rtf_par);
         outln(rtf_pard);
         break;
         
         
      case TOINF:
         outln("@end menu");
         break;
         
         
      default:
         outln("");
      }
   }

   bDocAutorefOff = old;

}  /*subsubsubtoc_output() */





/*******************************************************************************
*
*  subsubsubsubtoc_output():
*     create output for !use_auto_subsubsubsubtocs command
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void subsubsubsubtoc_output(void)
{
   register int   i;                    /* */
   int            li;                   /* */
   char           n[512],               /* */
                  ref[512];             /* */
   BOOLEAN        output_done = FALSE;  /* */
   BOOLEAN        first       = TRUE;   /* */
   BOOLEAN        old;                  /* */


   if (desttype == TOLYX)                 /* LYX doesn't support !toc */
      return;
   
   if (p1_toc_counter <= 0)               /* nothing to do */
      return;
   
   if (toc[p2_toc_counter]->ignore_subtoc)
      return;

   if (last_n2_index == 0)                /* Wer benutzt !subsubsubtoc in einem Node? */
      return;             

   if (last_n3_index == 0)                /* Wer benutzt !subsubsubtoc in einem Subnode? */
      return;

   if (last_n4_index == 0)                /* Wer benutzt !subsubsubtoc in einem Subnode? */
      return;

   old = bDocAutorefOff;
   bDocAutorefOff = FALSE;

                                          /* walk through all nodes after last n4 */
   for (i = last_n4_index; i <= p1_toc_counter; i++)
   {
      if (toc[i] != NULL && !toc[i]->invisible)
      {
         convert_toc_item(toc[i]);

         if (toc[i]->appendix)            /* r5pl6: Nach dem ersten Anhang-Node kommt nichts mehr */
            break;

         if (toc[i]->n1 > p2_toc_n1)      /* r5pl6: Das waren dann alle */
            break;

         if (toc[i]->n1 != 0)
         {
            if (toc[i]->n1 == p2_toc_n1)
            {
                                          /* r5pl6: Das waren dann alle */
               if (toc[i]->n2 > p2_toc_n2)
                  break;

               if (toc[i]->n2 == p2_toc_n2)
               {
                                          /* r5pl6: Das waren dann alle */
                  if (toc[i]->n3 > p2_toc_n3)
                     break;

                  if (toc[i]->n3 == p2_toc_n3)
                  {
                                          /* r5pl6: Das waren dann alle */
                     if (toc[i]->n4 > p2_toc_n4)
                        break;

                     if (toc[i]->n4 == p2_toc_n4)
                     {                    /* current is a subsubsubsubnode */
                        if (toc[i]->toctype == TOC_NODE5)
                        {
                           li = toc[i]->labindex;
                           string2reference(ref, lab[li], TRUE, "", 0, 0);

                           if (no_numbers)
                              sprintf(n, form_t5_n5, ref);
                           else
                           {
                              sprintf(n, form_t5_n5,
                                 toc[i]->nr1 + toc_offset,
                                 toc[i]->nr2 + subtoc_offset,
                                 toc[i]->nr3 + subsubtoc_offset,
                                 toc[i]->nr4 + subsubsubtoc_offset,
                                 toc[i]->nr5 + subsubsubsubtoc_offset,
                                 ref);
                           }

                           tocline_handle_1st(&first);
                           
                           if (use_toc_list_commands == TOCL_HTM)
                              out("\t");
                              
                           outln(n);      /* output the subsubsubsubnode item! */
                           
                           output_done = TRUE;

                        }  /* TOC_NODE5 */
                     }
                  }
               }
            }
         }
      }
   }

   if (output_done)
   {
      switch (desttype)
      {
      case TOHAH: /* V6.5.17 */
      case TOHTM:
      case TOMHH:
         outln("\t</li>");
         outln("</ul>\n");
         break;
         
         
      case TOTEX:
      case TOPDL:
         outln(toc_list_end);
         break;
         
         
      case TOAQV:
      case TOWIN:
      case TOWH4:
         outln(rtf_par);
         outln(rtf_pard);
         break;
         
         
      case TOINF:
         outln("@end menu");
         break;
         
         
      default:
         outln("");
      }
   }

   bDocAutorefOff = old;

}  /*subsubsubsubtoc_output() */










LOCAL void apx_output(const int depth)
{
        register int i;
        int li;
        char    n[512], ref[512];
        BOOLEAN leerzeile= FALSE;
        BOOLEAN last_n= TRUE;
        BOOLEAN last_sn= FALSE;
        BOOLEAN last_ssn= FALSE;
        BOOLEAN last_sssn= FALSE;
        BOOLEAN last_ssssn= FALSE;
        BOOLEAN first= TRUE;

        BOOLEAN old;

        if (desttype==TOLYX)
        {       return;
        }

        if (p1_toc_counter<=0)
        {       return;
        }

        if (!apx_available)             /* r5pl16 */
        {       return;
        }

        old= bDocAutorefOff;
        bDocAutorefOff= FALSE;

        for (i=1; i<=p1_toc_counter; i++)
        {
                /* r5pl10: langwierige Indizierung vermeiden */
                toc[i]= toc[i];

                if (toc[i]!=NULL && !toc[i]->invisible)
                {
                        convert_toc_item(toc[i]);

                        if (toc[i]->appendix)
                        {       if (toc[i]->n1 != 0)
                                {
                                        if (toc[i]->toctype==TOC_NODE1)
                                        {       /* Ein Kapitel */

                                                if ((leerzeile) && (depth>1))
                                                {       
                     switch (desttype)
                                                        {
                     case TOHAH: /* V6.5.17 */
                     case TOHTM:
                     case TOMHH:
                        if (html_doctype < XHTML_STRICT)
                           outln("<br>");
                        else
                           outln("<br />&nbsp;");
                        break;
                     
                     case TOWIN:
                     case TOWH4:
                     case TOAQV:
                        outln(rtf_par);
                        break;
                     
                     case TOTEX:
                     case TOPDL:
                        break;
                     
                     default:
                        outln("");
                                                        }
                                                        /* leerzeile= FALSE; */
                                                }

                                                if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                {       if (last_sn)
                                                        {       outln(toc_list_end);
                                                                last_sn= FALSE;
                                                        }
                                                        if (last_ssn)
                                                        {       voutlnf("%s%s", toc_list_end, toc_list_end);
                                                                last_ssn= FALSE;
                                                        }
                                                        if (last_sssn)
                                                        {       voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
                                                                last_sssn= FALSE;
                                                        }
                                                        if (last_ssssn)
                                                        {       voutlnf("%s%s%s%s", toc_list_end, toc_list_end, toc_list_end, toc_list_end);
                                                                last_ssssn= FALSE;
                                                        }
                                                        last_n= TRUE;
                                                }

                                                li= toc[i]->labindex;
                                                string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                if (no_numbers)
                                                {       sprintf(n, form_a1_n1, ref);
                                                }
                                                else
                                                {       sprintf(n, form_a1_n1, 'A'-1+toc[i]->nr1, ref);
                                                }

                                                tocline_make_bold(n, depth);
                                                tocline_handle_1st(&first);

                                                outln(n);
                                                leerzeile= TRUE;
                                        }

                                        if (depth>1)
                                        {
                                                if (toc[i]->toctype==TOC_NODE2)
                                                {       /* Ein Abschnitt */
                                                        if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                        {       if (last_n)
                                                                {       outln(toc_list_top);
                                                                        last_n= FALSE;
                                                                }
                                                                if (last_ssn)
                                                                {       outln(toc_list_end);
                                                                        last_ssn= FALSE;
                                                                }
                                                                if (last_sssn)
                                                                {       voutlnf("%s%s", toc_list_end, toc_list_end);
                                                                        last_sssn= FALSE;
                                                                }
                                                                if (last_ssssn)
                                                                {       voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
                                                                        last_ssssn= FALSE;
                                                                }
                                                                last_sn= TRUE;
                                                        }

                                                        li= toc[i]->labindex;
                                                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                        if (no_numbers)
                                                        {       sprintf(n, form_a1_n2, ref);
                                                        }
                                                        else
                                                        {       sprintf(n, form_a1_n2, 'A'-1+toc[i]->nr1, toc[i]->nr2, ref);
                                                        }

                                                        tocline_handle_1st(&first);
                                                        outln(n);
                                                }
                                        }       /* depth>1 */

                                        if (depth>2)
                                        {
                                                if (toc[i]->toctype==TOC_NODE3)
                                                {       /* Ein Unterabschnitt */
                                                        if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                        {       if (last_n)
                                                                {       voutlnf("%s%s", toc_list_top, toc_list_top);
                                                                        last_n= FALSE;
                                                                }
                                                                if (last_sn)
                                                                {       outln(toc_list_top);
                                                                        last_sn= FALSE;
                                                                }
                                                                if (last_sssn)
                                                                {       outln(toc_list_end);
                                                                        last_sssn= FALSE;
                                                                }
                                                                if (last_ssssn)
                                                                {       voutlnf("%s%s", toc_list_top, toc_list_top);
                                                                        last_ssssn= FALSE;
                                                                }
                                                                last_ssn= TRUE;
                                                        }

                                                        li= toc[i]->labindex;
                                                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                        if (no_numbers)
                                                        {       sprintf(n, form_a1_n3, ref);
                                                        }
                                                        else
                                                        {       sprintf(n, form_a1_n3, 'A'-1+toc[i]->nr1, toc[i]->nr2, toc[i]->nr3, ref);
                                                        }

                                                        tocline_handle_1st(&first);
                                                        outln(n);
                                                }/* TOC_NODE3 */
                                        }       /* depth>2 */

                                        if (depth>3)
                                        {
                                                if (toc[i]->toctype==TOC_NODE4)
                                                {       /* Ein Paragraph */
                                                        if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                        {       if (last_n)
                                                                {       voutlnf("%s%s%s", toc_list_top, toc_list_top, toc_list_top);
                                                                        last_n= FALSE;
                                                                }
                                                                if (last_sn)
                                                                {       voutlnf("%s%s", toc_list_top, toc_list_top);
                                                                        last_sn= FALSE;
                                                                }
                                                                if (last_ssn)
                                                                {       outln(toc_list_top);
                                                                        last_ssn= FALSE;
                                                                }
                                                                if (last_ssssn)
                                                                {       outln(toc_list_end);
                                                                        last_ssssn= FALSE;
                                                                }
                                                                last_sssn= TRUE;
                                                        }

                                                        li= toc[i]->labindex;
                                                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                        if (no_numbers)
                                                        {       sprintf(n, form_a1_n4, ref);
                                                        }
                                                        else
                                                        {       sprintf(n, form_a1_n4,
                                                                        'A'-1+toc[i]->nr1,
                                                                        toc[i]->nr2,
                                                                        toc[i]->nr3,
                                                                        toc[i]->nr4,
                                                                        ref);
                                                        }

                                                        tocline_handle_1st(&first);
                                                        outln(n);
                                                }/* TOC_NODE4 */

                                        }/* depth>3 */

                                        if (depth>4)
                                        {
                                                if (toc[i]->toctype==TOC_NODE5)
                                                {       /* Ein Paragraph */
                                                        if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                        {       if (last_n)
                                                                {       voutlnf("%s%s%s", toc_list_top, toc_list_top, toc_list_top); /* ToDo: noch ein %s? */
                                                                        last_n= FALSE;
                                                                }
                                                                if (last_sn)
                                                                {       voutlnf("%s%s", toc_list_top, toc_list_top);
                                                                        last_sn= FALSE;
                                                                }
                                                                if (last_ssn)
                                                                {       outln(toc_list_top);
                                                                        last_ssn= FALSE;
                                                                }

                                                                if (last_sssn)
                                                                {       outln(toc_list_top);
                                                                        last_sssn= FALSE;
                                                                }

                                                                last_ssssn= TRUE;
                                                        }

                                                        li= toc[i]->labindex;
                                                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                        if (no_numbers)
                                                        {       sprintf(n, form_a1_n5, ref);
                                                        }
                                                        else
                                                        {       sprintf(n, form_a1_n5,
                                                                        'A'-1+toc[i]->nr1,
                                                                        toc[i]->nr2,
                                                                        toc[i]->nr3,
                                                                        toc[i]->nr4,
                                                                        toc[i]->nr5,
                                                                        ref);
                                                        }

                                                        tocline_handle_1st(&first);
                                                        outln(n);
                                                }/* TOC_NODE5 */

                                        }/* depth>4 */
                                }/* toc[i]->n1!=0 */
                        }/* toc[i]->appendix */
                }
        }

        switch (desttype)
        {
                case TOHAH: /* V6.5.17 */
                case TOHTM:
                case TOMHH:
                case TOTEX:
                case TOPDL:
                        if (last_sn)            outln(toc_list_end);
                        if (last_ssn)           voutlnf("%s%s", toc_list_end, toc_list_end);
                        if (last_sssn)          voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
                        if (last_ssssn) voutlnf("%s%s%s%s", toc_list_end, toc_list_end, toc_list_end, toc_list_end);
                        outln(toc_list_end);
                        break;
                case TOINF:
                        if (!no_index && bCalledIndex && use_udo_index)
                        {       outln("");
                                voutlnf("* %s::", lang.index);
                        }
                        outln("@end menu");
                        break;
                case TOSTG:
                case TOAMG:
                        outln("");
                        break;
        }

        bDocAutorefOff= old;
}       /* apx_output */


LOCAL void subapx_output(const int depth)
{
        register int i;
        int li;
        char    n[512], ref[512];
        BOOLEAN last_sn= FALSE;
        BOOLEAN last_ssn= FALSE;
        BOOLEAN last_sssn= FALSE;
        BOOLEAN last_ssssn= FALSE;
        BOOLEAN output_done= FALSE;
        BOOLEAN first= TRUE;

        BOOLEAN old;

        if (desttype==TOLYX)
        {       return;
        }

        if (p1_toc_counter<=0)
        {       return;
        }

        if (toc[p2_toc_counter]->ignore_subtoc )       /* r5pl6 */
        {       return;
        }

        old= bDocAutorefOff;
        bDocAutorefOff= FALSE;

        for (i=last_n1_index; i<=p1_toc_counter; i++)
        {
                if (toc[i]!=NULL && !toc[i]->invisible)
                {
                        convert_toc_item(toc[i]);

                        if (toc[i]->appendix && toc[i]->n1!=0)
                        {
                                if (toc[i]->n1>p2_apx_n1)
                                {       break;  /* r5pl6: das waren dann alle */
                                }

                                if (toc[i]->n1 == p2_apx_n1)
                                {
                                        if (toc[i]->toctype==TOC_NODE2)
                                        {       /* Ein Abschnitt */
                                                if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                {       if (last_ssn)
                                                        {       outln(toc_list_end);
                                                                last_ssn= FALSE;
                                                        }
                                                        if (last_sssn)
                                                        {       voutlnf("%s%s", toc_list_end, toc_list_end);
                                                                last_sssn= FALSE;
                                                        }
                                                        if (last_ssssn)
                                                        {       voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
                                                                last_ssssn= FALSE;
                                                        }
                                                        last_sn= TRUE;
                                                }

                                                li= toc[i]->labindex;
                                                string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                if (no_numbers)
                                                {       sprintf(n, form_a2_n2, ref);
                                                }
                                                else
                                                {       sprintf(n, form_a2_n2, 'A'-1+toc[i]->nr1, toc[i]->nr2, ref);
                                                }

                                                tocline_handle_1st(&first);
                                                outln(n);
                                                output_done= TRUE;
                                        }

                                        if (depth>1)
                                        {
                                                if (toc[i]->toctype==TOC_NODE3)
                                                {       /* Ein Unterabschnitt */
                                                        if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                        {       if (last_sn)
                                                                {       outln(toc_list_top);
                                                                        last_sn= FALSE;
                                                                }
                                                                if (last_sssn)
                                                                {       outln(toc_list_end);
                                                                        last_sssn= FALSE;
                                                                }
                                                                if (last_ssssn)
                                                                {       voutlnf("%s%s", toc_list_end, toc_list_end);
                                                                        last_ssssn= FALSE;
                                                                }
                                                                last_ssn= TRUE;
                                                        }

                                                        li= toc[i]->labindex;
                                                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                        if (no_numbers)
                                                        {       sprintf(n, form_a2_n3, ref);
                                                        }
                                                        else
                                                        {       sprintf(n, form_a2_n3, 'A'-1+toc[i]->nr1, toc[i]->nr2, toc[i]->nr3, ref);
                                                        }

                                                        tocline_handle_1st(&first);
                                                        outln(n);
                                                        output_done= TRUE;
                                                }/* TOC_NODE3 */
                                        }       /* depth>1 */

                                        if (depth>2)
                                        {
                                                if (toc[i]->toctype==TOC_NODE4)
                                                {       /* Ein Paragraph */
                                                        if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                        {       if (last_sn)
                                                                {       outln(toc_list_top);
                                                                        last_sn= FALSE;
                                                                }
                                                                if (last_ssn)
                                                                {       outln(toc_list_top);
                                                                        last_ssn= FALSE;
                                                                }
                                                                if (last_ssssn)
                                                                {       outln(toc_list_end);
                                                                        last_ssssn= FALSE;
                                                                }
                                                                last_sssn= TRUE;
                                                        }

                                                        li= toc[i]->labindex;
                                                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                        if (no_numbers)
                                                        {       sprintf(n, form_a2_n4, ref);
                                                        }
                                                        else
                                                        {       sprintf(n, form_a2_n4,
                                                                        'A'-1+toc[i]->nr1,
                                                                        toc[i]->nr2,
                                                                        toc[i]->nr3,
                                                                        toc[i]->nr4,
                                                                        ref);
                                                        }

                                                        tocline_handle_1st(&first);
                                                        outln(n);
                                                        output_done= TRUE;
                                                }/* TOC_NODE4 */
                                        }       /* depth>2 */

                                        if (depth>3)
                                        {
                                                if (toc[i]->toctype==TOC_NODE5)
                                                {       /* Ein Paragraph */                                     /* ToDo: ??? */
                                                        if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                        {       if (last_sn)
                                                                {       outln(toc_list_top);
                                                                        last_sn= FALSE;
                                                                }
                                                                if (last_ssn)
                                                                {       outln(toc_list_top);
                                                                        last_ssn= FALSE;
                                                                }
                                                                if (last_sssn)
                                                                {       outln(toc_list_top);
                                                                        last_sssn= FALSE;
                                                                }
                                                                last_ssssn= TRUE;
                                                        }

                                                        li= toc[i]->labindex;
                                                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                        if (no_numbers)
                                                        {       sprintf(n, form_a2_n5, ref);
                                                        }
                                                        else
                                                        {       sprintf(n, form_a2_n5,
                                                                        'A'-1+toc[i]->nr1,
                                                                        toc[i]->nr2,
                                                                        toc[i]->nr3,
                                                                        toc[i]->nr4,
                                                                        toc[i]->nr5,
                                                                        ref);
                                                        }

                                                        tocline_handle_1st(&first);
                                                        outln(n);
                                                        output_done= TRUE;
                                                }/* TOC_NODE4 */
                                        }       /* depth>2 */

                                }
                        }
                }
        }

        if (output_done)
        {       switch (desttype)
                {
                        case TOHAH: /* V6.5.17 */
                        case TOHTM:
                        case TOMHH:
                                if (last_ssn)
                                {       outln(toc_list_end);
                                }
                                if (last_sssn)
                                {       voutlnf("%s%s", toc_list_end, toc_list_end);
                                }
                                if (last_ssssn)
                                {       voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
                                }
                                outln(toc_list_end);
            
            if (html_doctype < XHTML_STRICT)
                                outln(HTML_BR);
            else
                                outln(XHTML_BR);
            
                                break;
            
                        case TOTEX:
                        case TOPDL:
                                if (last_ssn)
                                {       outln(toc_list_end);
                                }
                                if (last_sssn)
                                {       voutlnf("%s%s", toc_list_end, toc_list_end);
                                }
                                if (last_ssssn)
                                {       voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
                                }
                                outln(toc_list_end);
                                break;
                        case TOAQV:
                        case TOWIN:
                        case TOWH4:
                                outln(rtf_par);
                                outln(rtf_pard);
                                break;
                        case TOINF:
                                outln("@end menu");
                                break;
                        default:
                                outln("");
                                break;
                }
        }

        bDocAutorefOff= old;
}       /*subapx_output*/


LOCAL void subsubapx_output(const int depth)
{
        register int i;
        int li;
        char    n[512], ref[512];
        BOOLEAN last_ssn= FALSE;
        BOOLEAN last_sssn= FALSE;
        BOOLEAN last_ssssn= FALSE;
        BOOLEAN output_done= FALSE;
        BOOLEAN first= TRUE;
        BOOLEAN old;

        if (desttype==TOLYX)
        {       return;
        }

        if (p1_toc_counter<=0)
        {       return;
        }

        if (toc[p2_toc_counter]->ignore_subtoc )       /* r5pl6 */
        {       return;
        }

        if (last_n2_index==0 ) /* r5pl6 */
        {       return;                         /* Wer benutzt !subsubtoc in einem Node? */
        }

        old= bDocAutorefOff;
        bDocAutorefOff= FALSE;

        for (i=last_n2_index; i<=p1_toc_counter; i++)
        {
                /* r5pl10: langwierige Indizierung vermeiden */
                toc[i]= toc[i];

                if (toc[i]!=NULL && !toc[i]->invisible)
                {
                        convert_toc_item(toc[i]);

                        if (toc[i]->appendix && toc[i]->n1!=0)
                        {
                                if ( toc[i]->n1>p2_apx_n1)
                                {       break;  /* r5pl6: Das waren dann alle */
                                }

                                if (toc[i]->n1 == p2_apx_n1)
                                {
                                        if (toc[i]->n2>p2_apx_n2)
                                        {       break;  /* r5pl6: Das waren dann alle */
                                        }

                                        if (toc[i]->n2==p2_apx_n2)
                                        {
                                                if (toc[i]->toctype==TOC_NODE3)
                                                {       /* Ein Unterabschnitt */

                                                        if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                        {       if (last_sssn)
                                                                {       outln(toc_list_end);
                                                                        last_sssn= FALSE;
                                                                }
                                                                if (last_ssssn)
                                                                {       voutlnf("%s%s", toc_list_end, toc_list_end);
                                                                        last_ssssn= FALSE;
                                                                }
                                                                last_ssn= TRUE;
                                                        }

                                                        li= toc[i]->labindex;
                                                        string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                        if (no_numbers)
                                                        {       sprintf(n, form_a3_n3, ref);
                                                        }
                                                        else
                                                        {       sprintf(n, form_a3_n3, 'A'-1+toc[i]->nr1, toc[i]->nr2, toc[i]->nr3, ref);
                                                        }

                                                        tocline_handle_1st(&first);
                                                        outln(n);
                                                        output_done= TRUE;
                                                }/* TOC_NODE3 */

                                                if (depth>1)
                                                {       if (toc[i]->toctype==TOC_NODE4)
                                                        {       /* Ein Paragraph */

                                                                if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                                {       if (last_ssn)
                                                                        {       outln(toc_list_top);
                                                                                last_ssn= FALSE;
                                                                        }
                                                                        if (last_ssssn)
                                                                        {       outln(toc_list_end);
                                                                                last_ssssn= FALSE;
                                                                        }
                                                                        last_sssn= TRUE;
                                                                }

                                                                li= toc[i]->labindex;
                                                                string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                                if (no_numbers)
                                                                {       sprintf(n, form_a3_n4, ref);
                                                                }
                                                                else
                                                                {       sprintf(n, form_a3_n4,
                                                                                'A'-1+toc[i]->nr1,
                                                                                toc[i]->nr2,
                                                                                toc[i]->nr3,
                                                                                toc[i]->nr4,
                                                                                ref);
                                                                }

                                                                tocline_handle_1st(&first);
                                                                outln(n);
                                                                output_done= TRUE;
                                                        }/* TOC_NODE3 */
                                                }

                                                if (depth>2)
                                                {       if (toc[i]->toctype==TOC_NODE5)
                                                        {       /* Ein Paragraph */

                                                                if (use_toc_list_commands)      /* r6pl2: vorher: desttype==TOHTM */
                                                                {       if (last_ssn)
                                                                        {       outln(toc_list_top);
                                                                                last_ssn= FALSE;
                                                                        }
                                                                        if (last_sssn)
                                                                        {       outln(toc_list_top);
                                                                                last_sssn= FALSE;
                                                                        }
                                                                        last_ssssn= TRUE;
                                                                }

                                                                li= toc[i]->labindex;
                                                                string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                                if (no_numbers)
                                                                {       sprintf(n, form_a3_n5, ref);
                                                                }
                                                                else
                                                                {       sprintf(n, form_a3_n5,
                                                                                'A'-1+toc[i]->nr1,
                                                                                toc[i]->nr2,
                                                                                toc[i]->nr3,
                                                                                toc[i]->nr4,
                                                                                toc[i]->nr5,
                                                                                ref);
                                                                }

                                                                tocline_handle_1st(&first);
                                                                outln(n);
                                                                output_done= TRUE;
                                                        }/* TOC_NODE5 */
                                                }

                                        }
                                }
                        }
                }
        }

        if (output_done)
        {       switch (desttype)
                {
                        case TOHAH: /* V6.5.17 */
                        case TOHTM:
                        case TOMHH:
                                if (last_sssn)  outln(toc_list_end);
                                if (last_ssssn) voutlnf("%s%s", toc_list_end, toc_list_end);
                                outln(toc_list_end);
            
            if (html_doctype < XHTML_STRICT)
                                outln(HTML_BR);
            else
                                outln(XHTML_BR);
                                break;
         
                        case TOTEX:
                        case TOPDL:
                                if (last_sssn)  outln(toc_list_end);
                                if (last_ssssn) voutlnf("%s%s", toc_list_end, toc_list_end);
                                outln(toc_list_end);
                                break;
                        case TOAQV:
                        case TOWIN:
                        case TOWH4:
                                outln(rtf_par);
                                outln(rtf_pard);
                                break;
                        case TOINF:
                                outln("@end menu");
                                break;
                        default:
                                outln("");
                                break;
                }
        }

        bDocAutorefOff= old;
}       /*subsubapx_output*/

LOCAL void subsubsubapx_output(const int depth)
{
        register int i;
        int li;
        char    n[512], ref[512];
        BOOLEAN last_sssn= FALSE;
        BOOLEAN last_ssssn= FALSE;
        BOOLEAN output_done= FALSE;
        BOOLEAN first= TRUE;
        BOOLEAN old;

        if (desttype==TOLYX)
        {       return;
        }

        if (p1_toc_counter<=0)
        {       return;
        }

        if (toc[p2_toc_counter]->ignore_subtoc )       /* r5pl6 */
        {       return;
        }

        if (last_n2_index==0 ) /* r5pl6 */
        {       return;                         /* Wer benutzt !subsubsubtoc in einem Node? */
        }

        if (last_n3_index==0 ) /* r5pl6 */
        {       return;                         /* Wer benutzt !subsubsubtoc in einem Subnode? */
        }

        old= bDocAutorefOff;
        bDocAutorefOff= FALSE;

        for (i=last_n3_index; i<=p1_toc_counter; i++)
        {
                /* r5pl10: langwierige Indizierung vermeiden */
                toc[i]= toc[i];

                if (toc[i]!=NULL && !toc[i]->invisible)
                {
                        convert_toc_item(toc[i]);

                        if (toc[i]->appendix && toc[i]->n1!=0)
                        {
                                if ( toc[i]->n1>p2_apx_n1)
                                {       break;  /* r5pl6: Das waren dann alle */
                                }

                                if (toc[i]->n1 == p2_apx_n1)
                                {
                                        if (toc[i]->n2>p2_apx_n2)
                                        {       break;  /* r5pl6: Das waren dann alle */
                                        }

                                        if (toc[i]->n2==p2_apx_n2)
                                        {
                                                if (toc[i]->n3>p2_apx_n3)
                                                {       break;  /* r5pl6: Das waren alle */
                                                }

                                                if (toc[i]->n3==p2_apx_n3)
                                                {
                                                        if (toc[i]->toctype==TOC_NODE4)
                                                        {       /* Ein Paragraph */

                                                                if (use_toc_list_commands)
                                                                {       if (last_ssssn)
                                                                        {       outln(toc_list_end);
                                                                                last_ssssn= FALSE;
                                                                        }
                                                                        last_sssn= TRUE;
                                                                }

                                                                li= toc[i]->labindex;
                                                                string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                                if (no_numbers)
                                                                {       sprintf(n, form_a4_n4, ref);
                                                                }
                                                                else
                                                                {       sprintf(n, form_a4_n4,
                                                                                'A'-1+toc[i]->nr1,
                                                                                toc[i]->nr2,
                                                                                toc[i]->nr3,
                                                                                toc[i]->nr4,
                                                                                ref);
                                                                }

                                                                tocline_handle_1st(&first);
                                                                outln(n);
                                                                output_done= TRUE;
                                                        }/* TOC_NODE4 */

                                                        if (depth>1)
                                                        {       if (toc[i]->toctype==TOC_NODE5)
                                                                {       /* Ein Paragraph */
        
                                                                        if (use_toc_list_commands)
                                                                        {       if (last_sssn)
                                                                                {       outln(toc_list_top);
                                                                                        last_sssn= FALSE;
                                                                                }
                                                                                last_ssssn= TRUE;
                                                                        }
        
                                                                        li= toc[i]->labindex;
                                                                        string2reference(ref, lab[li], TRUE, "", 0, 0);
        
                                                                        if (no_numbers)
                                                                        {       sprintf(n, form_a4_n5, ref);
                                                                        }
                                                                        else
                                                                        {       sprintf(n, form_a4_n5,
                                                                                        toc[i]->nr1,
                                                                                        toc[i]->nr2,
                                                                                        toc[i]->nr3,
                                                                                        toc[i]->nr4,
                                                                                        toc[i]->nr5,
                                                                                        ref);
                                                                        }
        
                                                                        tocline_handle_1st(&first);
                                                                        outln(n);
                                                                        output_done= TRUE;
                                                                }/* TOC_NODE5 */
                                                        } /* depth>1 */

                                                }
                                        }
                                }
                        }
                }
        }

        if (output_done)
        {       switch (desttype)
                {
                        case TOHAH: /* V6.5.17 */
                        case TOHTM:
                        case TOMHH:
                      if (last_sssn)
                         outln(toc_list_end);
                         
                      if (last_ssssn)
                         voutlnf("%s%s", toc_list_end, toc_list_end);

                                outln(toc_list_end);
            
            if (html_doctype < XHTML_STRICT)
                                outln(HTML_BR);
            else
                                outln(XHTML_BR);
            
                                break;
            
                        case TOTEX:
                        case TOPDL:
                      if (last_sssn)
                         outln(toc_list_end);
                         
                      if (last_ssssn)
                         voutlnf("%s%s", toc_list_end, toc_list_end);

                                outln(toc_list_end);
                                break;
                        case TOAQV:
                        case TOWIN:
                        case TOWH4:
                                outln(rtf_par);
                                outln(rtf_pard);
                                break;
                        case TOINF:
                                outln("@end menu");
                                break;
                        default:
                                outln("");
                                break;
                }
        }

        bDocAutorefOff= old;
}       /*subsubsubapx_output*/

LOCAL void subsubsubsubapx_output(void)
{
        register int i;
        int li;
        char    n[512], ref[512];
        BOOLEAN output_done= FALSE;
        BOOLEAN first= TRUE;
        BOOLEAN old;

        if (desttype==TOLYX)
        {       return;
        }

        if (p1_toc_counter<=0)
        {       return;
        }

        if (toc[p2_toc_counter]->ignore_subtoc )       /* r5pl6 */
        {       return;
        }

        if (last_n2_index==0 ) /* r5pl6 */
        {       return;                         /* Wer benutzt !subsubsubtoc in einem Node? */
        }

        if (last_n3_index==0 ) /* r5pl6 */
        {       return;                         /* Wer benutzt !subsubsubtoc in einem Subnode? */
        }

        if (last_n4_index==0 ) /* r5pl6 */
        {       return;                         /* Wer benutzt !subsubsubtoc in einem Subnode? */
        }

        old= bDocAutorefOff;
        bDocAutorefOff= FALSE;

        for (i=last_n4_index; i<=p1_toc_counter; i++)
        {
                /* r5pl10: langwierige Indizierung vermeiden */
                toc[i]= toc[i];

                if (toc[i]!=NULL && !toc[i]->invisible)
                {
                        convert_toc_item(toc[i]);

                        if (toc[i]->appendix && toc[i]->n1!=0)
                        {
                                if ( toc[i]->n1>p2_apx_n1)
                                {       break;  /* r5pl6: Das waren dann alle */
                                }

                                if (toc[i]->n1 == p2_apx_n1)
                                {
                                        if (toc[i]->n2>p2_apx_n2)
                                        {       break;  /* r5pl6: Das waren dann alle */
                                        }

                                        if (toc[i]->n2==p2_apx_n2)
                                        {
                                                if (toc[i]->n3>p2_apx_n3)
                                                {       break;  /* r5pl6: Das waren alle */
                                                }

                                                if (toc[i]->n3==p2_apx_n3)
                                                {
                                                        if (toc[i]->n4>p2_apx_n4)
                                                        {       break;  /* r5pl6: Das waren alle */
                                                        }

                                                        if (toc[i]->toctype==TOC_NODE5)
                                                        {       /* Ein Paragraph */

                                                                li= toc[i]->labindex;
                                                                string2reference(ref, lab[li], TRUE, "", 0, 0);

                                                                if (no_numbers)
                                                                {       sprintf(n, form_a5_n5, ref);
                                                                }
                                                                else
                                                                {       sprintf(n, form_a5_n5,
                                                                                'A'-1+toc[i]->nr1,
                                                                                toc[i]->nr2,
                                                                                toc[i]->nr3,
                                                                                toc[i]->nr4,
                                                                                toc[i]->nr5,
                                                                                ref);
                                                                }

                                                                tocline_handle_1st(&first);
                                                                outln(n);
                                                                output_done= TRUE;
                                                        }/* TOC_NODE5 */
                                                }
                                        }
                                }
                        }
                }
        }

        if (output_done)
        {       switch (desttype)
                {
                        case TOHAH: /* V6.5.17 */
                        case TOHTM:
                        case TOMHH:
                                outln(toc_list_end);
            
            if (html_doctype < XHTML_STRICT)
                                outln(HTML_BR);
            else
                                outln(XHTML_BR);
            
                                break;
            
                        case TOTEX:
                        case TOPDL:
                                outln(toc_list_end);
                                break;
                        case TOAQV:
                        case TOWIN:
                        case TOWH4:
                                outln(rtf_par);
                                outln(rtf_pard);
                                break;
                        case TOINF:
                                outln("@end menu");
                                break;
                        default:
                                outln("");
                                break;
                }
        }

        bDocAutorefOff= old;
}       /*subsubsubapx_output*/





/*******************************************************************************
*
*  do_toc():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void do_toc(

const int   depth)  /* */
{
   if (desttype == TORTF)                 /* no TOC in RTF as we have no page numbers! */
      return;

   toc_output(depth);

   if (apx_available)
   {
      output_appendix_line();             /*r6pl2*/
      apx_output(depth);
   }
}





/*******************************************************************************
*
*  do_subtoc():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void do_subtoc(

const int   depth)  /* */
{
   if (desttype == TORTF)                 /* no TOC in RTF as we have no page numbers! */
      return;

   (bInsideAppendix) ? subapx_output(depth) : subtoc_output(depth);
}





/*******************************************************************************
*
*  do_subsubtoc():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void do_subsubtoc(

const int   depth)  /* */
{
   if (desttype == TORTF)                 /* no TOC in RTF as we have no page numbers! */
      return;

   (bInsideAppendix) ? subsubapx_output(depth) : subsubtoc_output(depth);
}





/*******************************************************************************
*
*  do_subsubsubtoc():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void do_subsubsubtoc(

const int   depth)  /* */
{
   if (desttype == TORTF)                 /* no TOC in RTF as we have no page numbers! */
      return;

   (bInsideAppendix) ? subsubsubapx_output(depth) : subsubsubtoc_output(depth);
}





/*******************************************************************************
*
*  do_subsubsubsubtoc():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void do_subsubsubsubtoc(void)
{
   if (desttype == TORTF)                 /* no TOC in RTF as we have no page numbers! */
      return;

   (bInsideAppendix) ? subsubsubsubapx_output() : subsubsubsubtoc_output();
}





/*******************************************************************************
*
*  do_toptoc():
*     outputs the navigation section (basically on top of the current page)
*
*  return:
*     -
*
******************************************|************************************/

LOCAL void do_toptoc(

const int    currdepth)                 /* current node depth */
{
   char      s[512],                    /* */
             sIndent[512],              /* */
             sTarget[64],               /* */
             sFile[64];                 /* */
   char      sSmartSep[64] = " &gt; ";  /* default separator string */
   char      closer[8] = "\0";          /* single tag closer mark in XHTML */

   
   if (html_doctype >= XHTML_STRICT)      /* no single tag closer in HTML! */
      strcpy(closer, " /");
   
   if (html_navigation_separator[0] != 0) /* check if valid userdef separator exists */
   {
      strcpy(sSmartSep, " ");             /* overwrite local default */
      strcat(sSmartSep, html_navigation_separator);
      strcat(sSmartSep, " ");
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
   
   
   switch (desttype)
   {
   case TOHAH:                            /* V6.5.17 */
   case TOHTM:
   case TOMHH:
      if (no_images || no_auto_toptocs_icons)
      {
         strcpy(sIndent, "&nbsp;");
      }
      else
      {
         sprintf(sIndent, "<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\" border=\"0\"%s>", 
            GIF_FS_NAME, uiGifFsWidth, uiGifFsHeight, closer);
      }
   
      if (html_frames_layout)
      {
         sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
         sprintf(sFile, "%s%s", html_name_prefix, FRAME_FILE_CON);
      }
      else
      {
         sTarget[0] = EOS;
         strcpy(sFile, old_outfile.name);
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
            voutlnf("<tt>+&nbsp;</tt>&nbsp;<a href=\"%s%s\"%s>%s</a>", sFile, outfile.suff, sTarget, s);
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
                                          /* open CSS class div */
            outln("<div class=\"UDO_nav_line\">");
            
            if (html_navigation_image)
            {
                                          /* if userdef image exists */ 
               if (html_navigation_image_fspec[0] != 0)
               {
                                          /* don't close the nav line already! */
                  voutf("<img src=\"%s\" alt=\"\" title=\"\" border=\"0\"%s>&nbsp;&nbsp;<a href=\"%s%s\"%s>%s</a>",
                                          /* folder image file name */
                     html_navigation_image_fspec,
                     closer,              /* XHTML single tag closer (if any) */
                     sFile,               /* file name */
                     outfile.suff,        /* file suffix */
                     sTarget,             /* a href target */
                     s);                  /* node name */
               }
               else
               {
                                          /* don't close the nav line already! */
                  voutf("<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\" border=\"0\"%s>&nbsp;&nbsp;<a href=\"%s%s\"%s>%s</a>",
                     GIF_FO_NAME,         /* folder image file name */
                     uiGifFoWidth,        /* folder image width */
                     uiGifFoHeight,       /* folder image height */
                     closer,              /* XHTML single tag closer (if any) */
                     sFile,               /* file name */
                     outfile.suff,        /* file suffix */
                     sTarget,             /* a href target */
                     s);                  /* node name */
               }
            }
            else
            {
               voutf("<a href=\"%s%s\"%s>%s</a>",
                     sFile,               /* file name */
                     outfile.suff,        /* file suffix */
                     sTarget,             /* a href target */
                     s);                  /* node name */
            }
         }
         else
         {
            voutlnf("<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\" border=\"0\"%s>&nbsp;<a href=\"%s%s\"%s>%s</a>",
               GIF_FO_NAME,               /* folder image file name */
               uiGifFoWidth,              /* folder image width */
               uiGifFoHeight,             /* folder image height */
               closer,                    /* XHTML single tag closer (if any) */
               sFile,                     /* file name */
               outfile.suff,              /* file suffix */
               sTarget,                   /* a href target */
               s);                        /* node name */
         }
      }
   
   
      /* --- Level 2 --- */
      
      if (currdepth >= TOC_NODE2 && last_n1_index > 0)
      {
         strcpy(s, toc[last_n1_index]->name);
         auto_references(s, TRUE, "", 0, 0);
   
         if (no_images)
         {
            voutlnf("<br%s><tt>|--+&nbsp;</tt>&nbsp;%s", 
               closer, s);
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
            voutf("%s%s", sSmartSep, s);  /* don't close the nav line already! */
         }
         else
         {
            voutlnf("<br%s>%s<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\" border=\"0\"%s>&nbsp;%s", 
               closer, sIndent, GIF_FO_NAME, uiGifFoWidth, uiGifFoHeight, closer, s);
         }
      }
   
   
      /* --- Level 3 --- */
      
      if (currdepth >= TOC_NODE3 && last_n2_index > 0)
      {
         strcpy(s, toc[last_n2_index]->name);
         auto_references(s, TRUE, "", 0, 0);
   
         if (no_images)
         {
            voutlnf("<br%s><tt>&nbsp;&nbsp;&nbsp;|--+&nbsp;</tt>&nbsp;%s", 
               closer, s);
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
            voutf("%s%s", sSmartSep, s);  /* don't close the nav line already! */
         }
         else
         {
            voutlnf("<br%s>%s%s<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\" border=\"0\"%s>&nbsp;%s",
               closer,
               sIndent, 
               sIndent, 
               GIF_FO_NAME, 
               uiGifFoWidth, 
               uiGifFoHeight, 
               closer,
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
            voutlnf("<br%s><tt>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|--+&nbsp;</tt>&nbsp;%s",
               closer, s);
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
            voutf("%s%s", sSmartSep, s);  /* don't close the nav line already! */
         }
         else
         {
            voutlnf("<br%s>%s%s%s<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\" border=\"0\"%s>&nbsp;%s",
               closer,
               sIndent, 
               sIndent, 
               sIndent, 
               GIF_FO_NAME, 
               uiGifFoWidth, 
               uiGifFoHeight, 
               closer,
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
            voutlnf("<br%s><tt>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|--+&nbsp;</tt>&nbsp;%s",
               closer, s);
         }
         else if (html_navigation_line)   /* new v6.5.19[fd] */
         {
            voutf("%s%s", sSmartSep, s);  /* don't close the nav line already! */
         }
         else
         {
            voutlnf("<br%s>%s%s%s<img src=\"%s\" width=\"%u\" height=\"%u\" alt=\"\" title=\"\" border=\"0\"%s>&nbsp;%s",
               closer,
               sIndent, 
               sIndent, 
               sIndent, 
               GIF_FO_NAME, 
               uiGifFoWidth, 
               uiGifFoHeight, 
               closer,
               s);
         }
      }
      
      if (html_navigation_line)
      {
                                          /* create link to Index page */
         voutlnf("\n <span class=\"UDO_nav_index\"><a href=\"indexudo.htm\">%s</a></span>", lang.index);
                                          /* close CSS class div */
         outln("</div> <!-- UDO_nav_line -->\n");
      }

      if (html_doctype < XHTML_STRICT)
         outln(HTML_HR);
      else
         outln(XHTML_HR);
      
      break;
   
   case TOWIN:
   case TOWH4:
   case TOAQV:
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
      
      outln("\\par\\par");
      break;
   
   case TOSTG:
   case TOAMG:
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

      output_ascii_line("-", zDocParwidth);
      
   }  /* switch (desttype) */

}       /* do_toptoc */


LOCAL int get_toccmd_depth(void)
{
        register int i;
        int ret;

        for (i=1; i<token_counter; i++)
        {
                if (strcmp(token[i], "!depth")==0)
                {
                        if (i+1<token_counter)
                        {       ret= atoi(token[i+1]);
                                if (ret<=0)     ret= 9;
                                if (ret>9)      ret= 9;
                                return ret;
                        }
                }
        }

        return 0;       /* bei 0 werden die Defaultwerte (z.B. subtocs1_depth) benutzt */

}       /* get_toccmd_depth */


GLOBAL void c_toc(void)
{
        BOOLEAN flag= FALSE;
        int d;

        if (is_for_desttype(&flag, "!toc"))
        {
                d= get_toccmd_depth();
                if (d==0)
                {       if (use_compressed_tocs)
                        {       d=1;
                        }
                        else
                        {       d=9;
                        }
                }

                if (desttype==TOINF)
                {       d= 1;
                }
                do_toc(d);
        }

}       /* c_toc */





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
   BOOLEAN   flag = FALSE;  /* */
   int       d;             /* */

                                          /* token[0] enthaelt das !sub*toc-Kommando */
   if (is_for_desttype(&flag, token[0]))
   {
      switch (active_nodetype)
      {
      case TOC_NODE1:
         d = get_toccmd_depth();

         if (d == 0)
            d = subtocs1_depth;

         do_subtoc(d);
         break;
         
      case TOC_NODE2:
         d = get_toccmd_depth();
         
         if (d == 0)
            d = subtocs2_depth;

         do_subsubtoc(d);
         break;
         
      case TOC_NODE3:
         d = get_toccmd_depth();

         if (d == 0)
            d = subtocs3_depth;

         do_subsubsubtoc(d);
         break;

      case TOC_NODE4:
         do_subsubsubsubtoc();
      }
   }
}


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
                /* New in r6pl16 [NHz] */
                case TORTF:
                        voutlnf("\\page\n%s\\fs36 %s\\par\\par", rtf_node1, lang.listfigure);
                        voutlnf("{\\field\\fldedit{\\*\\fldinst { TOC \\\\c \"%s\" }}{\\fldrslt %s not actual}}", lang.listfigure, lang.listfigure);
                        break;
        }
}       /* c_listoffigures */


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
                /* New in r6.3pl3 [NHz] */
                case TORTF:
                        voutlnf("\\page\n%s\\fs36 %s\\par\\par", rtf_node1, lang.listtable);
                        voutlnf("{\\field\\fldedit{\\*\\fldinst {TOC \\\\c \"Tabelle\" }}{\\fldrslt %s not actual}}", lang.listtable);
                        break;
        }
}       /* c_listoftables */



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
                        out("  ");      outln(lang.appendix);
                        out("  ");      output_ascii_line("=", strlen(lang.appendix));
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
                case TOHAH: /* V6.5.17 */
                case TOHTM:
                case TOMHH:
                        voutlnf("<h1>%s</h1>", lang.appendix);
                        break;
                case TOTEX:     /* <???> */
                case TOPDL:     /* <???> */
                        break;
        }

}       /* output_appendix_line */


GLOBAL void c_tableofcontents(void)
{
        char    n[256], 
         name[256], 
         hlp_name[256];
        int     i;
        int     depth;

        if (called_tableofcontents)
        {       return;
        }

        called_tableofcontents= TRUE;

        check_endnode();

        depth= get_toccmd_depth();      /*r6pl2*/
        if (depth==0)
        {       if (use_compressed_tocs)              /*r6pl5*/
                {       depth= 1;
                }
                else
                {       depth= 9;
                }
        }


        switch (desttype)
        {
                case TOTEX:
                case TOPDL:
                        c_newpage();
                        output_helpid(0);
                        outln("\tableofcontents");
                        c_newpage();
                        break;
                case TOLYX:
                        outln("\\layout LaTeX");
                        outln("\\pagebreak_top \\pagebreak_bottom");
                        outln("\\begin_inset LatexDel \\tableofcontents");
                        outln("\\end_inset");
                        break;
                case TOINF:
                        outln("@ifinfo");
                        n[0]= EOS;
                        if (toc[1]!=NULL)
                        {       strcpy(name, toc[1]->name);
                                node2texinfo(name);
                                sprintf(n, "@node Top, %s, (dir), (dir)", name);
                        }
                        output_helpid(0);
                        outln(n);

                        if (called_maketitle)
                        {       if (titdat.title!=NULL)        voutlnf("@center %s @*", titdat.title);
                                if (titdat.program!=NULL)      voutlnf("@center %s @*", titdat.program);
                                if (titdat.version!=NULL)      voutlnf("@center %s @*", titdat.version);
                                if (titdat.date!=NULL)         voutlnf("@center %s @*", titdat.date);
                                if (titdat.author!=NULL)
                                {       outln("@sp 1");
                                        voutlnf("@center %s", lang.by);
                                        outln("@sp 1");
                                        voutlnf("@center %s @*", titdat.author);
                                }
                                if (address_counter>0)
                                {       for (i=1; i<=address_counter; i++)
                                        {       if (titdat.address[i]!=NULL)
                                                {       voutlnf("@center %s @*", titdat.address[i]);
                                                }
                                        }
                                }
                                outln("@center ");
                                outln("@sp 1");
                        }

                        outln(lang.contents);
                        outln("");                      

                        if (toc_available)
                        {       toc_output(1);  /* immer 1 */
                        }
                        if (apx_available)
                        {       output_appendix_line();
                                apx_output(1);  /* immer 1 */
                        }
                        outln("@end ifinfo");
                        break;
                case TOSTG:
                case TOAMG:
                        outln("");
                        if (desttype==TOSTG)
                        {
                                voutlnf("@node Main \"%s\"", lang.contents);
                                voutlnf("@symbol \"%s\"", lang.contents);
                        }
                        else
                        {
                                if (titleprogram[0]!=EOS)
                                {       voutlnf("@node Main \"%s - %s\"", titleprogram, lang.contents);
                                }
                                else
                                {       voutlnf("@node Main \"%s\"", lang.contents);
                                }
                        }

                        if (called_maketitle)
                        {       voutlnf("@toc \"%s\"", lang.title);
                        }
                        output_helpid(0);
                        stg_headline("", lang.contents);

                        if (toc_available)
                        {       toc_output(depth);
                        }
                        if (apx_available)
                        {       output_appendix_line();
                                apx_output(depth);
                        }
                        outln("@endnode");
                        outln("");
                        break;

                case TOTVH:
                        outln("");
                        voutlnf(".topic %s", lang.contents);
                        output_helpid(0);
                        strcpy(n, lang.contents);
                        out("  ");      outln(n);
                        out("  ");      output_ascii_line("=", strlen(n));
                        outln("");

                        if (toc_available)
                        {       toc_output(depth);
                        }
                        if (apx_available)
                        {       output_appendix_line();
                                apx_output(depth);
                        }
                        outln("");
                        break;

                case TOASC:
                        if (toc_available)
                        {
                                if (use_style_book)
                                {       output_ascii_line("=", zDocParwidth);
                                        outln(lang.contents);
                                        output_ascii_line("=", zDocParwidth);
                                }
                                else
                                {       outln(lang.contents);
                                        output_ascii_line("=", strlen(lang.contents));
                                }

                                outln("");
                                toc_output(depth);
                                outln("");
                        }
                        if (apx_available)
                        {       output_appendix_line();
                                apx_output(depth);
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
                        node2NrWinhelp(n, 0);
                        voutlnf("#{\\footnote # %s}", n);
                        output_helpid(0);
                        voutlnf("${\\footnote $ %s}", lang.contents);
                        voutlnf("K{\\footnote K %s}", lang.contents);

                        if (!no_buttons)        /* r6pl8 */
                        {       outln(win_browse);

                                if (desttype==TOAQV)    /* r5pl6 */
                                {       strcpy(hlp_name, "qchPath");
                                }
                                else
                                {       sprintf(hlp_name, "`%s.hlp'", outfile.name);
                                }

                                if (called_maketitle)
                                {       outln("!{\\footnote ! EnableButton(\"BTN_UP\");");
                                        voutlnf("ChangeButtonBinding(\"BTN_UP\", \"JumpID(%s, `%s')\") }",
                                                hlp_name, WIN_TITLE_NODE_NAME);
                                }
                                else
                                {       outln("!{\\footnote ! DisableButton(\"BTN_UP\") }");
                                }
                        }

                        if (toc_available)
                        {       outln("\\keepn");       /* r6pl11*/
                                sprintf(n, "\\fs%d", iDocPropfontSize + 14);
                                voutlnf("{%s\\b %s}\\par\\pard\\par", n, lang.contents);
                                toc_output(depth);
                        }

                        if (apx_available)
                        {       output_appendix_line();
                                apx_output(depth);
                        }

                        outln("}\\page");
                        break;

                case TOPCH:
                        if (titdat.program!=NULL)
                        {       voutlnf("screen(capsensitive(\"%s\"), capsensitive(\"%s\"))",
                                                        titdat.program, lang.contents);
                        }
                        else
                        {       voutlnf("screen(capsensitive(\"%s\"), capsensitive(\"%s\"))",
                                                        lang.unknown, lang.contents);
                        }
                        output_helpid(0);
                        pch_headline(lang.contents);
                        outln("");
                        if (uses_maketitle)
                        {       pch_titlepage();
                        }
                        outln("");
                        if (toc_available)
                        {       outln(lang.contents);
                                output_ascii_line("=", strlen(lang.contents));
                                outln("");
                                toc_output(depth);
                        }
                        if (apx_available)
                        {       output_appendix_line();
                                apx_output(depth);
                        }
                        outln("");
                        outln("\\end");
                        outln("");
                        break;

                case TOHAH: /* V6.5.17 */
                case TOHTM:
                case TOMHH:
                        output_helpid(0);
         
                        if (toc_available)
                        {
                voutlnf("\n<h1><a name=\"%s\"></a>%s</h1>\n", HTML_LABEL_CONTENTS, lang.contents);
                                /* New in V6.5.9 [NHz] */
                                add_label(HTML_LABEL_CONTENTS, FALSE, FALSE);
                                toc_output(depth);
                        }
                        if (apx_available)
                        {
                output_appendix_line();
                                apx_output(depth);
                        }
         
         /* new since v6.5.19 */
         if (use_udo_index)
         {
            voutlnf("\n<h1><a href=\"indexudo%s\">%s</a></h1>\n", outfile.suff, lang.index);
         }
         
                        break;  /* r5pl4 */

                case TOKPS:
                        /* New in r6pl15 [NHz] */
                        if (toc_available)
                        {       outln("newline");

                                voutlnf("/NodeName (%s) def", lang.contents);
                                voutlnf("20 changeFontSize (%s) udoshow newline %d changeFontSize", lang.contents, laydat.propfontsize); /* Changed in r6pl15 [NHz] */
                                toc_output(depth);
                        }

                        if (apx_available)
                        {       output_appendix_line();
                                apx_output(depth);
                        }

                        if (toc_available)
                                c_newpage();

/*                      check_endnode();

                        output_helpid(0);
                        if (toc_available)
                        {
                                outln("18 changeFontSize");
                                voutlnf("(%s) show newline", lang.contents);
                                outln("11 changeFontSize changeBaseFont");
                                toc_output(depth);
                        }
                        if (apx_available)
                        {
                                output_appendix_line();
                                apx_output(depth);
                        }
                        c_newpage();*/
                        break;

                case TOLDS:
                        output_helpid(0);
                        outln("<toc>");
                        break;

                /* New in r6pl16 [NHz] */
                case TORTF:
                        voutlnf("\\plain\\s4\\ql\\b\\f0\\li567\\fi-567\\fs%d", laydat.node1size);
                        voutlnf("%s", lang.contents);
                        voutlnf("\\par\\pard\\par\\pard \\plain \\s1\\qj\\f0\\fs%d", iDocPropfontSize);
                        outln("{\\field{\\*\\fldinst {TOC \\\\t \"Node1;1;Node2;2;Node3;3;Node4;4\" }}{\\fldrslt {Please refresh!}}}");
                        outln("\\page");
                        break;
        }

}       /*c_tableofcontents*/





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
               voutlnf("<dd><a name=\"%s\"></a></dd>", sLabel);
            else
               voutlnf("<a name=\"%s\"></a>", sLabel);
         }
         else
            voutlnf("<a name=\"%s\"></a>", sLabel);
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
   
}  /* c_label() */





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





/*******************************************************************************
*
*  add_label():
*     add a label to the internal list of labels
*
*  Notes:
*     tocindex: position of label in toc[]
*
*     Labels are now added in all formats, because else *toc_output() would output
*     wrong results because it directly references using the label index.
*
*  Return:
*     - FALSE: error
*     - p1_lab_counter
*
******************************************|************************************/

GLOBAL int add_label(

const char     *label,   /* ^ label name string */
const BOOLEAN   isn,     /* TRUE: chapter (node), FALSE: label only */
const BOOLEAN   isp)     /* TRUE: popup */
{
   LABEL       *labptr;  /* ^ to label structure in memory */


   if (p1_lab_counter + 1 >= MAXLABELS)   /* list overflow? */
   {
      error_too_many_label();
      return FALSE;
   }

                                          /* label empty or too long? */
   if (label[0] == EOS || strlen(label) > MAX_LABEL_LEN)
      return FALSE;

                                          /* get space for new label */
   labptr = (LABEL *)um_malloc(sizeof(LABEL) + 1);

   if (labptr == NULL)                    /* no more memory? */
   {
      error_malloc_failed();
   return FALSE;
   }


   /* --- set label in project file --- */

   if (!isn)                              /* only labels which are not nodes */
      save_upr_entry_label(sCurrFileName, strchr(current_node_name_sys, ' ') + 1, uiCurrFileLine);

   p1_lab_counter++;
   lab[p1_lab_counter] = labptr;

   strcpy(labptr->name, label);
   replace_udo_quotes(labptr->name);

   labptr->len          = strlen(labptr->name);
   labptr->labindex     = p1_lab_counter;
   labptr->is_node      = isn;
   labptr->is_alias     = FALSE;
   labptr->is_popup     = isp;
   labptr->tocindex     = p1_toc_counter;
   labptr->ignore_links = FALSE;
   labptr->referenced   = FALSE;

                                          /* check for labels which should not be listed in index */
   if (    (strcmp(token[0],"!label*") == 0)
        || (strcmp(token[0],"!l*")     == 0)
      )
      labptr->ignore_index = TRUE;
   else
      labptr->ignore_index = FALSE;

   if (pflag[PASS1].inside_apx)
   {
      labptr->appendix = TRUE;
      labptr->n1       = p1_apx_n1;
      labptr->n2       = p1_apx_n2;
      labptr->n3       = p1_apx_n3;
      labptr->n4       = p1_apx_n4;
      labptr->n5       = p1_apx_n5;
   }
   else
   {
      labptr->appendix = FALSE;
      labptr->n1       = p1_toc_n1;
      labptr->n2       = p1_toc_n2;
      labptr->n3       = p1_toc_n3;
      labptr->n4       = p1_toc_n4;
      labptr->n5       = p1_toc_n5;
   }

   return p1_lab_counter;
}





/*      ############################################################
        #
        # Einen Alias der internen Liste hinzufuegen
        # Ein Alias ist ein Zweitname (Drittname, ...) eines Nodes
        #
        ############################################################    */
GLOBAL BOOLEAN add_alias(const char *alias, const BOOLEAN isp)
{
        LABEL   *labptr;

        /* r5pl9: Aliase fuer alle Formate sichern */

        if (p1_lab_counter+1>=MAXLABELS)        /* Noch Platz in der Liste? */
        {       error_too_many_alias();
                return FALSE;
        }

        /* rel6pl2: Leeren Alias abweisen */
#if 1
        if (alias[0]==EOS)
        {       return FALSE;
        }
#endif

        labptr= (LABEL *) um_malloc(sizeof(LABEL)+1);

        if (labptr==NULL)                                       /* Kein Speicher mehr frei? */
        {       error_malloc_failed();
                return FALSE;
        }

        /* New in r6pl15 [NHz] */

        /* Set alias in project file */

        save_upr_entry_alias (sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine);

        p1_lab_counter++;
        lab[p1_lab_counter]= labptr;

        strcpy( labptr->name, alias);
        replace_udo_quotes(labptr->name);
        labptr->len= strlen(labptr->name);      /* r5pl10 */

        labptr->labindex= p1_lab_counter;       /* r6pl2 */
        labptr->is_node= FALSE;
        labptr->is_alias= TRUE;
        labptr->is_popup= isp;

        labptr->tocindex= p1_toc_counter;
        labptr->ignore_links= FALSE;
        labptr->ignore_index= FALSE;
        labptr->referenced= FALSE;                      /* r6pl9 */

        if (pflag[PASS1].inside_apx)
        {       labptr->appendix= TRUE;
                labptr->n1= p1_apx_n1;
                labptr->n2= p1_apx_n2;
                labptr->n3= p1_apx_n3;
                labptr->n4= p1_apx_n4;
                labptr->n5= p1_apx_n5;
        }
        else
        {       labptr->appendix= FALSE;
                labptr->n1= p1_toc_n1;
                labptr->n2= p1_toc_n2;
                labptr->n3= p1_toc_n3;
                labptr->n4= p1_toc_n4;
                labptr->n5= p1_toc_n5;
        }

        return TRUE;

}       /* add_alias */


/*      ############################################################
        #
        # Inhaltsverzeichnis erweitern
        #
        ############################################################    */
GLOBAL void set_ignore_headline(void )        /* r5pl12 */
{
        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;

        toc[p1_toc_counter]->ignore_headline= TRUE;

}       /* set_ignore_headline */


GLOBAL void set_ignore_bottomline(void )      /* r6pl10 */
{
        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;

        toc[p1_toc_counter]->ignore_bottomline= TRUE;

}       /* set_ignore_bottomline */


GLOBAL void set_raw_header_filename(void)
{
        char *ptr, s[512];

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        um_strcpy(s, token[1], 512, "set_raw_header_filename[1]");

        if (p1_toc_counter==0)
        {
                um_strcpy(sDocRawHeaderFilename, s, 512, "set_raw_header_filename[2]");
        }
        else
        {
                ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));
                if (!ptr)
                {       error_malloc_failed();
                        bFatalErrorDetected= TRUE;
                }
                else
                {
                        strcpy(ptr, s);
                        toc[p1_toc_counter]->raw_header_filename= ptr;
                }
        }

}       /* set_raw_header_filename */


GLOBAL void set_raw_footer_filename(void)
{
        char *ptr, s[512];

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        um_strcpy(s, token[1], 512, "set_raw_footer_filename[1]");

        if (p1_toc_counter==0)
        {
                um_strcpy(sDocRawFooterFilename, s, 512, "set_raw_footer_filename[2]");
        }
        else
        {
                ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));
                if (!ptr)
                {       error_malloc_failed();
                        bFatalErrorDetected= TRUE;
                }
                else
                {
                        strcpy(ptr, s);
                        toc[p1_toc_counter]->raw_footer_filename= ptr;
                }
        }

}       /* set_raw_footer_filename */


GLOBAL void set_ignore_raw_header(void )      /* r6pl10 */
{
        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;

        toc[p1_toc_counter]->ignore_raw_header= TRUE;

}       /* set_ignore_raw_header */


GLOBAL void set_ignore_raw_footer(void )      /* r6pl10 */
{
        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;

        toc[p1_toc_counter]->ignore_raw_footer= TRUE;

}       /* set_ignore_raw_footer */


GLOBAL void set_ignore_footer(void )  /* r6pl2 */
{
        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;

        toc[p1_toc_counter]->ignore_footer= TRUE;

}       /* set_ignore_footer */


GLOBAL void set_ignore_title(void )   /* r6pl13 */
{
        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;

        toc[p1_toc_counter]->ignore_title= TRUE;

}       /* set_ignore_title */

GLOBAL void set_ignore_links(void )   /* r5pl8 */
{
        int li;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;

        toc[p1_toc_counter]->ignore_links= TRUE;

        li= toc[p1_toc_counter]->labindex;

        if (li>0)
        {       lab[li]->ignore_links= TRUE;
        }

}       /* set_ignore_links */


GLOBAL void set_ignore_index(void )   /* r5pl10 */
{
        int li;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;

        toc[p1_toc_counter]->ignore_index= TRUE;

        li= toc[p1_toc_counter]->labindex;

        if (li>0)
        {       lab[li]->ignore_index= TRUE;
        }

}       /* set_ignore_index */


GLOBAL void set_ignore_subtoc(void )  /* r5pl6 */
{

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;

        toc[p1_toc_counter]->ignore_subtoc= TRUE;

}       /* set_ignore_subtoc */


GLOBAL void set_helpid(void)
{
        char id[512], *ptr;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        um_strcpy(id, token[1], 512, "set_helpid");

        /* <???> Hier pruefen, ob nur A-Z, a-z, 0-9 und _ benutzt werden */

        ptr= (char *) um_malloc(1+strlen(id)*sizeof(char));

        if (!ptr)
        {       error_malloc_failed();
                bFatalErrorDetected= TRUE;
        }
        else
        {       strcpy(ptr, id);
                toc[p1_toc_counter]->helpid= ptr;
        }

        bUseIdMapFileC= TRUE;   /* r6pl8: bei Verwendung auch die Datei erzeugen! */

}       /* set_helpid */


GLOBAL void set_mapping(void)
{
        char map[512];
        int m;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        um_strcpy(map, token[1], 512, "set_mapping[1]");

        /* <???> Hier pruefen, ob nur 0-9 benutzt wird */

        m= atoi(token[1]);

        if (m>=0)
        {
                toc[p1_toc_counter]->mapping= m;
                bUseIdMapFileC= TRUE;   /* r6pl8: bei Verwendung auch die Datei erzeugen! */
        }
        else
        {
                error_wrong_mapping();
        }

}       /* set_mapping */


/* New in r6pl16 [NHz] */
GLOBAL void set_html_doctype(void)
{
        char s[512];

        tokcpy2(s, 512);

        if (strcmp(s, "Old")==0)
        {       html_doctype= HTML_OLD;
        }

        if (strcmp(s, "Strict")==0)
        {       html_doctype= HTML_STRICT;
        }

        if (strcmp(s, "Transitional")==0)
        {       html_doctype= HTML_TRANS;
        }

        if (strcmp(s, "XHTML Strict")==0)
        {       html_doctype= XHTML_STRICT;
        }

        if (strcmp(s, "XHTML Transitional")==0)
        {       html_doctype= XHTML_TRANS;
        }

}       /* set_html_doctype */


/* New feature #0000054 in V6.5.2 [NHz] */
GLOBAL void set_html_header_date(void)
{
        tokcpy2(html_header_date_zone, 9);

        if (((html_header_date_zone[0] != '+') &&
                (html_header_date_zone[0] != '-')) ||
                isdigit(html_header_date_zone[1] == 0) ||
                isdigit(html_header_date_zone[2] == 0) ||
                (html_header_date_zone[3] != ':') ||
                isdigit(html_header_date_zone[4] == 0) ||
                isdigit(html_header_date_zone[5] == 0))
        {
                error_wrong_header_date(html_header_date_zone);
                return;
        }

        html_header_date = TRUE;

}       /* set_html_header_date */


/* New feature #0000053 in V6.5.2 [NHz] */
GLOBAL void set_html_header_links(void)
{
        char *kind;
        char possible[]="navigation chapter";

        tokcpy2(html_header_links_kind, 40);

        if (html_header_links_kind[0]==EOS)
        {       error_empty_header_links();
                return;
        }

        kind = strtok(html_header_links_kind, " ");
        while (kind != NULL)
        {
                if (strstr(possible, kind)==NULL)
                        error_argument_header_links(kind);

                kind = strtok(NULL, " ");
        }

        tokcpy2(html_header_links_kind, 40);
        html_header_links = TRUE;

}       /* set_html_header_links */


GLOBAL void set_html_frames_layout(void)
{
        char s[512];

        html_frames_layout= TRUE;

        tokcpy2(s, 512);

        if (strstr(s, "noresize=\"noresize\"")!=NULL)
        {       html_frames_noresize= TRUE;
        }

        if (strstr(s, "noborder")!=NULL)
        {       html_frames_noborder= TRUE;
        }

        if (strstr(s, "noscrolling")!=NULL)
        {       html_frames_noscroll= TRUE;
        }

}       /* set_html_frames_layout */


GLOBAL void set_html_counter_command(void)
{
        char k[512], *ptr;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        tokcpy2(k, 512);

        /* New in V6.5.9 [NHz] */
        if (p1_toc_counter==0)
        {       strcpy(sCounterCommand, k);
                return;
        }

        ptr= (char *) um_malloc(1+strlen(k)*sizeof(char));

        if (!ptr)
        {       error_malloc_failed();
                bFatalErrorDetected= TRUE;
        }
        else
        {       strcpy(ptr, k);
                toc[p1_toc_counter]->counter_command= ptr;
        }

}       /* set_html_counter_command */


GLOBAL void set_html_filename(void)
{
        char *ptr;

        /* New in v6.5.10 [vj]: !html_name is read in HTML and (new) HTML-Help output */
        if ((desttype!=TOHTM)&&(desttype!=TOMHH) && desttype!=TOHAH ) /* New TOHAH; V6.5.17 */
                return;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);

        ptr= toc[p1_toc_counter]->filename;
        ptr[0]= EOS;
        /* Nur den Dateinamen benutzen, nicht den Pfad! */
        strncat(ptr, tmp_name, MAX_FILENAME_LEN);

        /* New in r6pl16 [NHz] */
        if (strcmp(tmp_suff, ""))
                strncat(ptr, tmp_suff, 6);

}       /* set_html_filename */


GLOBAL void set_html_filename_prefix(void)
{
        if (desttype!=TOHTM && desttype!=TOHAH ) /* New TOHAH; V6.5.17 */
                return;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        um_strcpy(html_name_prefix, token[1], 512, "set_html_filename_prefix[1]");

}       /* set_html_filename_prefix */


GLOBAL void set_html_dirname(void)
{
        char *ptr;

        if (desttype!=TOHTM && desttype!=TOHAH ) /* New TOHAH; V6.5.17 */
                return;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);

        if (tmp_path[0]==EOS && tmp_name[0]!=EOS)
        {       strcpy(tmp_path, tmp_name);
        }

        if (tmp_path[0]!=EOS)
        {       ptr= toc[p1_toc_counter]->dirname;
                ptr[0]= EOS;
                strncat(ptr, tmp_name, MAX_FILENAME_LEN);
        }

}       /* set_html_dirname */


GLOBAL void set_html_switch_language(void)
{
        if (desttype!=TOHTM && desttype!=TOMHH && desttype!=TOHAH ) /* New TOHAH; V6.5.17 */
        {       return;
        }

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        iDocHtmlSwitchLanguage= -1;
        sDocHtmlSwitchLanguage[0]= EOS;

        if (strstr(token[1], "german"))
        {       iDocHtmlSwitchLanguage= TOGER;
        }       else
        if (strstr(token[1], "english"))
        {       iDocHtmlSwitchLanguage= TOENG;
        }

        if (iDocHtmlSwitchLanguage>=0)
        {
                token[1][0]= EOS;
                tokcpy2(sDocHtmlSwitchLanguage, 256);
        }

}       /* set_html_switch_language */


GLOBAL void set_html_color(const int which)
{
        char color[256], *ptr;
        BOOLEAN ret;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        color[0]= EOS;

        qdelete_once(token[1], "[", 1);
        qdelete_last(token[1], "]", 1);

        if (token[1][0]=='#')
        {       um_strcpy(color, token[1], 256, "set_html_color[1]");
                ret= TRUE;
        }
        else
        {       ret= get_html_color(token[1], color);
        }

        if (ret)
        {
                if (p1_toc_counter==0)
                {
                        ptr= sDocBackColor;     /* default */
                        switch (which)
                        {
                                case HTML_COLOR_BACK:   ptr= sDocBackColor;             break;
                                case HTML_COLOR_TEXT:   ptr= sDocTextColor;             break;
                                case HTML_COLOR_LINK:   ptr= sDocLinkColor;             break;
                                case HTML_COLOR_ALINK:  ptr= sDocAlinkColor;    break;
                                case HTML_COLOR_VLINK:  ptr= sDocVlinkColor;    break;
                        }
                }
                else
                {
                        ptr= toc[p1_toc_counter]->backcolor;
                        switch (which)
                        {
                                case HTML_COLOR_BACK:   ptr= toc[p1_toc_counter]->backcolor;    break;
                                case HTML_COLOR_TEXT:   ptr= toc[p1_toc_counter]->textcolor;    break;
                                case HTML_COLOR_LINK:   ptr= toc[p1_toc_counter]->linkcolor;    break;
                                case HTML_COLOR_ALINK:  ptr= toc[p1_toc_counter]->alinkcolor;   break;
                                case HTML_COLOR_VLINK:  ptr= toc[p1_toc_counter]->vlinkcolor;   break;
                        }
                }
                ptr[0]= EOS;
                if (color[0]!=EOS)
                {       strncat(ptr, color, MAX_COLOR_LEN);
                }
        }
        else
        {       error_unknown_color(token[1]);
        }

}       /* set_html_color */





/*******************************************************************************
*
*  set_html_bgsound():
*     Set the sound for a node
*
*     Only HTML
*
******************************************|************************************/

/* New in v6.5.20 [GS] */
GLOBAL void set_html_bgsound(void)
{
        char *ptr, *dest;
        char    filename[512];
        char loop [40], sTemp[1024];

        if (desttype!=TOHTM)
                return;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        dest = toc[p1_toc_counter]->bgsound;

        if (token[1][0]=='\"')
        {
                tokcpy2(sTemp, 1024);
                ptr= strchr(sTemp+1, '\"');             /* zweites " suchen */

                if (ptr)
                {       ptr[0]= EOS;
                        strcpy(filename, sTemp+1);
                        um_strcpy(loop, ptr+1, 40, "set_html_bgsound[1]");
                        del_whitespaces(loop);
                }
                else
                {       strcpy(filename, sTemp);
                        loop[0]= EOS;
                }
        }
        else
        {
                um_strcpy(filename, token[1], 512, "set_html_bgsound[2]");
                token[1][0]= EOS;
                tokcpy2(loop, 40);
                del_whitespaces(loop);
        }

        replace_char(filename, "\\", "/");

        if (loop[0] == EOS)
                sprintf(dest, "\"%s\" loop=\"infinitie\"", filename);
        else
                sprintf(dest, "\"%s\" loop=\"%s\"", filename, loop);
}       /* set_html_bgsound */


GLOBAL void set_html_backimage(void)
{
        char *ptr, *dest;
        char sTemp[512];

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        if (p1_toc_counter==0)
        {       dest= sDocBackImage;
        }
        else
        {       dest= toc[p1_toc_counter]->backimage;
        }

        if (token[1][0]=='\"')
        {
                tokcpy2(sTemp, 512);
                ptr= strchr(sTemp+1, '\"');             /* zweites " suchen */

                if (ptr)
                {       ptr[0]= EOS;
                        strcpy(dest, sTemp+1);
                }
                else
                {       strcpy(dest, sTemp);
                }
        }
        else
        {
                strcpy(dest, token[1]);
        }

        /* dest[0]= EOS;        */
        /* strncat(dest, sTemp, MAX_IMAGE_LEN); */

        /* Hier muessen immer / benutzt werden! */
        replace_char(dest, "\\", "/");

}       /* set_html_backimage */



/* New in r6pl15 [NHz] */
GLOBAL void set_html_style(void)
{
        STYLE *styleptr;
        char sTemp[512], *ptr;
        int i;
        long lang;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        /* Changed in V6.5.9 [NHz] */
        if (p1_style_counter+1>=MAXSTYLES)      /* Noch Platz in der Liste? */
        {       error_too_many_label();
                return;
        }

        styleptr= (STYLE *) um_malloc(sizeof(STYLE)+1);

        if (styleptr==NULL)                                     /* Kein Speicher mehr frei? */
        {       error_malloc_failed();
                return;
        }

        /* Set style in project file (not yet) */

/*      if (!isn)*/ /* Only labels which aren't nodes */
/*              save_upr_entry_label (sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine);
*/

        p1_style_counter++;
        style[p1_style_counter]= styleptr;
        styleptr->href[0]=EOS;
        styleptr->media[0]=EOS;
        styleptr->title[0]=EOS;
        styleptr->alternate=FALSE;

        tokcpy2(sTemp, 512);

        if (sTemp[0]=='\'')
        {
                lang = strcspn(sTemp+1, "'");
                strncpy(styleptr->href, sTemp+1, lang);
                styleptr->href[lang] = EOS;

                /* Hier muessen immer / benutzt werden! */
                replace_char(styleptr->href, "\\", "/");
        }
        else
                strcpy(styleptr->href, token[1]);

        for(i=1;i<p1_style_counter;i++)
        {
                if (!strcmp(styleptr->href, style[i]->href))
                {
                        p1_style_counter--;
                        return;
                }
        }

        ptr = strstr(sTemp, "media=");
        if (ptr != NULL)
        {
                lang = strcspn(ptr+6, " \0");
                strncpy(styleptr->media, ptr+6, lang);
                styleptr->media[lang] = EOS;
        }
        ptr = strstr(sTemp, "title=");
        if (ptr != NULL)
        {
                if (strchr(ptr+6, '\''))
                {
                        lang = strcspn(ptr+7, "'");
                        strncpy(styleptr->title, ptr+7, lang);
                }
                else
                {
                        lang = strcspn(ptr+6, " \0");
                        strncpy(styleptr->title, ptr+6, lang);
                }
                styleptr->title[lang] = EOS;
        }
        ptr = strstr(sTemp, "alternate");
        if (ptr != NULL)
                styleptr->alternate = TRUE;
        else
                styleptr->alternate = FALSE;

        styleptr->styleindex= p1_style_counter;
        styleptr->tocindex= p1_toc_counter;

}       /* set_html_style */


/* New in r6pl15 [NHz] */
GLOBAL void set_html_script(void)
{
        char *ptr, *dest;
        char sTemp[512];

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        if (p1_toc_counter==0)
        {       dest= sDocScript;
        }
        else
        {       dest= toc[p1_toc_counter]->script_name;
        }


        if (token[1][0]=='\"')
        {
                tokcpy2(sTemp, 512);
                ptr= strchr(sTemp+1, '\"');             /* zweites " suchen */

                if (ptr)
                {       ptr[0]= EOS;
                        strcpy(dest, sTemp+1);
                }
                else
                {       strcpy(dest, sTemp);
                }
        }
        else
        {
                strcpy(dest, token[1]);
        }

        /* dest[0]= EOS;        */
        /* strncat(dest, sTemp, MAX_IMAGE_LEN); */

        /* Hier muessen immer / benutzt werden! */
        replace_char(dest, "\\", "/");

}       /* set_html_script */



/* New in r6pl15 [NHz] */
GLOBAL void set_html_favicon(void)
{
        char *ptr, *dest;
        char sTemp[512];

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        if (p1_toc_counter==0)
        {       dest= sDocFavIcon;
        }
        else
        {       dest= toc[p1_toc_counter]->favicon_name;
        }


        if (token[1][0]=='\"')
        {
                tokcpy2(sTemp, 512);
                ptr= strchr(sTemp+1, '\"');             /* zweites " suchen */

                if (ptr)
                {       ptr[0]= EOS;
                        strcpy(dest, sTemp+1);
                }
                else
                {       strcpy(dest, sTemp);
                }
        }
        else
        {
                strcpy(dest, token[1]);
        }

        /* dest[0]= EOS;        */
        /* strncat(dest, sTemp, MAX_IMAGE_LEN); */

        /* Hier muessen immer / benutzt werden! */
        replace_char(dest, "\\", "/");

}       /* set_html_favicon */





/*******************************************************************************
*
*  set_html_keywords():
*     Set the HTML keywords
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void set_html_keywords(void)
{
   char      k[MAX_TOKEN_LEN],     /* */
            *ptr,                  /* */
             oldk[MAX_TOKEN_LEN],  /* */
            *oldptr;               /* */
   size_t    newsize;              /* */


   if (p1_toc_counter < 0)
      return;
      
   if (toc[p1_toc_counter] == NULL)
      return;
      
   if (token[1][0] == EOS)
      return;


   tokcpy2(k, MAX_TOKEN_LEN);
   c_vars(k);
   qdelete_all(k, "!-", 2);

   auto_quote_chars(k, TRUE);
   replace_udo_quotes(k);

   if (toc[p1_toc_counter]->keywords != NULL)
   {                                      /* r6pl5: Keywords bereits vorhanden, neue anhaengen */
      oldptr = toc[p1_toc_counter]->keywords;
      
      um_strcpy(oldk, oldptr, MAX_TOKEN_LEN + 1, "\n!html_keywords too long in this line\nset_html_keywords [1]");
      
      newsize = strlen(oldk) + strlen(k) + 3;

      ptr = (char *)um_realloc(oldptr, newsize);
      
      if (!ptr)
      {
         error_malloc_failed();
         bFatalErrorDetected = TRUE;
      }
      else
      {       
         sprintf(ptr, "%s, %s", oldk, k);
         toc[p1_toc_counter]->keywords = ptr;
      }
   }
   else
   {
      ptr = (char *)um_malloc(1 + strlen(k) * sizeof(char));

      if (!ptr)
      {
         error_malloc_failed();
         bFatalErrorDetected = TRUE;
      }
      else
      {
         strcpy(ptr, k);
         toc[p1_toc_counter]->keywords = ptr;
      }
   }
}





GLOBAL void set_html_description(void)
{
        char d[1024], *ptr, oldd[1024], *oldptr;
        size_t newsize;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        tokcpy2(d, 1024);
        c_vars(d);
        qdelete_all(d, "!-", 2);

        auto_quote_chars(d, TRUE);
        replace_udo_quotes(d);

        if (toc[p1_toc_counter]->description!=NULL)
        {       /* r6pl5: description bereits vorhanden, neue anhaengen */
                oldptr= toc[p1_toc_counter]->description;
                strcpy(oldd, oldptr);
                newsize= strlen(oldd) + strlen(d) + 2;

                ptr= (char *) um_realloc(oldptr, newsize);
                if (!ptr)
                {       error_malloc_failed();
                        bFatalErrorDetected= TRUE;
                }
                else
                {       
                        sprintf(ptr, "%s %s", oldd, d);
                        toc[p1_toc_counter]->description= ptr;
                }
        }
        else
        {       ptr= (char *) um_malloc(1+strlen(d)*sizeof(char));

                if (!ptr)
                {       error_malloc_failed();
                        bFatalErrorDetected= TRUE;
                }
                else
                {       strcpy(ptr, d);
                        toc[p1_toc_counter]->description= ptr;
                }
        }

}       /* set_html_description */

/* new since V6.5.17 */
GLOBAL void set_html_robots(void)
{
        char d[1024], *ptr;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        tokcpy2(d, 1024);
        c_vars(d);
        qdelete_all(d, "!-", 2);

        auto_quote_chars(d, TRUE);
        replace_udo_quotes(d);

        if (strcmp(d, "none") != 0)
        {       if (strcmp(d, "noindex") != 0)
                {       if (strcmp(d, "index") != 0)
                        {       if (strcmp(d, "nofollow") != 0)
                                {       if (strcmp(d, "follow") != 0)
                                        {       if (strcmp(d, "keywords") != 0 )     /* For HTML Apple Help */
                                                {       if (strcmp(d, "segements") != 0 )    /* For HTML Apple Help */
                                                        {       if (strcmp(d, "anchors") != 0 )      /* For HTML Apple Help */
                                                                {       error_syntax_error();
                                                                        return;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }

        ptr= (char *) um_malloc(1+strlen(d)*sizeof(char));

        if (!ptr)
        {       error_malloc_failed();
                bFatalErrorDetected= TRUE;
        }
        else
        {       strcpy(ptr, d);
                toc[p1_toc_counter]->robots= ptr;
        }

}       /* set_html_robots */

GLOBAL void set_html_special_color(char *hc)
{
        char color[256];
        BOOLEAN ret;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        color[0]= EOS;

        qdelete_once(token[1], "[", 1);
        qdelete_last(token[1], "]", 1);

        if (token[1][0]=='#')
        {       um_strcpy(color, token[1], 256, "set_html_special_color [1]");
                ret= TRUE;
        }
        else
        {       ret= get_html_color(token[1], color);
        }

        if (ret)
        {       hc[0]= EOS;
                if (color[0]!=EOS)
                {       strncat(hc, color, MAX_COLOR_LEN);
                }
        }
        else
        {       error_unknown_color(token[1]);
        }

}       /* set_html_special_color */


GLOBAL void set_html_modern_width(void)
{
        int width;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        /*r6pl8: Falls z.B. 30%, dann komplett umkopieren */
        if (strstr(token[1], "%")!=NULL)
        {
                um_strcpy(html_modern_width, token[1], 16, "set_html_modern_width[1]");
        }
        else
        {
                width= atoi(token[1]);
                if (width<0)    width= 128;
                sprintf(html_modern_width, "%d", width);
        }

}       /* set_html_modern_width */


GLOBAL void set_html_modern_alignment(void)
{
        char s[256];

        tokcpy2(s, 256);

        if (strstr(s, "center")!=NULL)
        {       html_modern_alignment= ALIGN_CENT;
                return;
        }

        if (strstr(s, "left")!=NULL)
        {       html_modern_alignment= ALIGN_LEFT;
                return;
        }

        if (strstr(s, "right")!=NULL)
        {       html_modern_alignment= ALIGN_RIGH;
                return;
        }

}       /* set_html_modern_alignment */



GLOBAL void set_html_modern_backimage(void)
{
        char *ptr;
        char sTemp[512];

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        if (token[1][0]=='\"')
        {
                tokcpy2(sTemp, 512);
                ptr= strchr(sTemp+1, '\"');             /* zweites " suchen */

                if (ptr)
                {       ptr[0]= EOS;
                        um_strcpy(html_modern_backimage, sTemp+1, 512, "set_html_modern_backimage[1]");
                }
                else
                {       um_strcpy(html_modern_backimage, sTemp, 512, "set_html_modern_backimage[2]");
                }
        }
        else
        {
                um_strcpy(html_modern_backimage, token[1], 512, "set_html_modern_backimage[3]");
        }

        /* Hier muessen immer / benutzt werden! */
        replace_char(html_modern_backimage, "\\", "/");

}       /* set_html_modern_backimage */


/* New in v6.5.16 [GS] */
GLOBAL void set_html_frames_toc_title(void)
{
        char d[1024], *ptr;

        tokcpy2(d, 1024);
        c_vars(d);
        qdelete_all(d, "!-", 2);

        auto_quote_chars(d, TRUE);
        replace_udo_quotes(d);

        if (html_frames_toc_title !=NULL)
                um_free(html_frames_toc_title);

        {       ptr= (char *) um_malloc(1+strlen(d)*sizeof(char));

                if (!ptr)
                {       error_malloc_failed();
                        bFatalErrorDetected= TRUE;
                }
                else
                {       strcpy(ptr, d);
                        html_frames_toc_title = ptr;
                }
        }

}       /* set_html_frames_toc_title */

/* New in 6.5.16 [GS] */
GLOBAL void set_html_frames_con_title(void)
{
        char d[1024], *ptr;

        tokcpy2(d, 1024);
        c_vars(d);
        qdelete_all(d, "!-", 2);

        auto_quote_chars(d, TRUE);
        replace_udo_quotes(d);

        if (html_frames_con_title !=NULL)
                um_free(html_frames_con_title);

        {       ptr= (char *) um_malloc(1+strlen(d)*sizeof(char));

                if (!ptr)
                {       error_malloc_failed();
                        bFatalErrorDetected= TRUE;
                }
                else
                {       strcpy(ptr, d);
                        html_frames_con_title = ptr;
                }
        }

}       /* set_html_frames_con_title */

GLOBAL void set_html_frames_width(void)
{
        int width;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        /*r6pl8: Falls z.B. 30%, dann komplett umkopieren */
        if (strstr(token[1], "%")!=NULL)
        {
                um_strcpy(html_frames_width, token[1], 16, "set_html_frames_width");
        }
        else
        {
                width= atoi(token[1]);
                if (width<0)    width= 128;
                sprintf(html_frames_width, "%d", width);
        }

}       /* set_html_frames_width */

GLOBAL void set_html_frames_height(void)
{
        int height;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        /*r6pl8: Falls z.B. 30%, dann komplett umkopieren */
        if (strstr(token[1], "%")!=NULL)
        {
                um_strcpy(html_frames_height, token[1], 16, "set_html_frames_height[1]");
        }
        else
        {
                height= atoi(token[1]);
                if (height<0)   height= 64;
                sprintf(html_frames_height, "%d", height);
        }

}       /* set_html_frames_height */


GLOBAL void set_html_frames_position(void)
{
        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        if (strstr(token[1], "left")!=NULL)
        {       html_frames_position= POS_LEFT;
                return;
        }

        if (strstr(token[1], "right")!=NULL)
        {       html_frames_position= POS_RIGHT;
                return;
        }

        if (strstr(token[1], "top")!=NULL)
        {       html_frames_position= POS_TOP;
                return;
        }

        if (strstr(token[1], "bottom")!=NULL)
        {       html_frames_position= POS_BOTTOM;
                return;
        }

}       /* set_html_frames_position */


GLOBAL void set_html_frames_alignment(void)
{
        char s[256];

        tokcpy2(s, 256);

        if (strstr(s, "center")!=NULL)
        {       html_frames_alignment= ALIGN_CENT;
                return;
        }

        if (strstr(s, "left")!=NULL)
        {       html_frames_alignment= ALIGN_LEFT;
                return;
        }

        if (strstr(s, "right")!=NULL)
        {       html_frames_alignment= ALIGN_RIGH;
                return;
        }

}       /* set_html_frames_alignment */


GLOBAL void set_html_frames_backimage(void)
{
        char *ptr;
        char sTemp[512];

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        if (token[1][0]=='\"')
        {
                tokcpy2(sTemp, 512);
                ptr= strchr(sTemp+1, '\"');             /* zweites " suchen */

                if (ptr)
                {       ptr[0]= EOS;
                        um_strcpy(html_frames_backimage, sTemp+1, 512, "set_html_frames_backimage[1]");
                }
                else
                {       um_strcpy(html_frames_backimage, sTemp, 512, "set_html_frames_backimage[2]");
                }
        }
        else
        {
                um_strcpy(html_frames_backimage, token[1], 512, "set_html_frames_backimage[3]");
        }

        /* Hier muessen immer / benutzt werden! */
        replace_char(html_frames_backimage, "\\", "/");

}       /* set_html_frames_backimage */


GLOBAL void set_html_button_alignment(void)
{
        char s[256];

        tokcpy2(s, 256);

        if (strstr(s, "center")!=NULL)
        {       html_button_alignment= ALIGN_CENT;
                return;
        }

        if (strstr(s, "left")!=NULL)
        {       html_button_alignment= ALIGN_LEFT;
                return;
        }

        if (strstr(s, "right")!=NULL)
        {       html_button_alignment= ALIGN_RIGH;
                return;
        }

}       /* set_html_button_alignment */


GLOBAL void set_html_quotes(void)
{
   char   s[256];  /* buffer for parameter string */

   
   tokcpy2(s, 256);                       /* get command parameters */
   
   if (strstr(s, "classic") != NULL)
   {
      html_quotes = QUOTES_CLASSIC; /* ALIGN_CENT; */
      return;
   }
   
   if (strstr(s, "tags") != NULL)
   {
      html_quotes = QUOTES_TAGS;
      return;
   }
}


GLOBAL void set_chapter_image(void)
{
        char s[512], *ptr;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
        sprintf(s, "%s%s%s", tmp_driv, tmp_path, tmp_name);

        if (desttype==TOHTM || desttype==TOMHH || desttype==TOHAH ) /* New TOHAH; V6.5.17 */
        {       replace_char(s, "\\", "/");     /*r6pl4*/
        }

        ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));

        if (!ptr)
        {       error_malloc_failed();
                bFatalErrorDetected= TRUE;
                return;
        }

        strcpy(ptr, s);
        toc[p1_toc_counter]->image= ptr;

        if (desttype!=TOHTM && desttype!=TOMHH && desttype!=TOHAH ) /* New TOHAH; V6.5.17 */
        {       return;
        }

        /* Ausmasse des Icons ermitteln, falls es ein GIF ist */
        /* In s[] steht noch der Dateiname ohne Endung */
        if (strcmp(sDocImgSuffix, ".gif")!=0)
        {       return;
        }

        strinsert(s, old_outfile.path);
        strinsert(s, old_outfile.driv);
        strcat(s, ".gif");
        path_adjust_separator(s);
        get_gif_size(s, &toc[p1_toc_counter]->uiImageWidth, &toc[p1_toc_counter]->uiImageHeight);

}       /* set_chapter_image */



GLOBAL void set_chapter_icon(void)
{
        char s[512], *ptr;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
        sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);

        if (desttype==TOHTM || desttype==TOMHH || desttype==TOHAH ) /* New TOHAH; V6.5.17 */
        {       replace_char(s, "\\", "/");     /*r6pl4*/
        }

        ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));

        if (!ptr)
        {       error_malloc_failed();
                bFatalErrorDetected= TRUE;
                return;
        }

        strcpy(ptr, s);
        toc[p1_toc_counter]->icon= ptr;

        if (desttype!=TOHTM && desttype!=TOHAH ) /* New TOHAH; V6.5.17 */
        {       return;
        }

        /* Ausmasse des Icons ermitteln, falls es ein GIF ist */
        /* In s[] steht noch der Dateiname ohne Endung */
        if (strcmp(sDocImgSuffix, ".gif")==0)
        {
                strinsert(s, old_outfile.path);
                strinsert(s, old_outfile.driv);
                path_adjust_separator(s);
                if (!get_gif_size(s, &toc[p1_toc_counter]->uiIconWidth, &toc[p1_toc_counter]->uiIconHeight))
                {
                        error_read_gif (s);
                }
        }

        /* Ausmasse des Icons ermitteln, falls es ein GIF ist */
        /* In s[] steht noch der Dateiname ohne Endung */
        if ((strcmp(sDocImgSuffix, ".jpg")==0) || (strcmp(sDocImgSuffix, ".jpeg")==0))
        {
                strinsert(s, old_outfile.path);
                strinsert(s, old_outfile.driv);
                path_adjust_separator(s);
                if (!get_jpg_size(s, &toc[p1_toc_counter]->uiIconWidth, &toc[p1_toc_counter]->uiIconHeight))
                {
                        error_read_jpeg(s);
                }
        }

}       /* set_chapter_icon */


GLOBAL void set_chapter_icon_active(void)
{
        char s[512], *ptr;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
        sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);

        if (desttype==TOHTM || desttype==TOMHH || desttype==TOHAH ) /* New TOHAH; V6.5.17 */
        {       replace_char(s, "\\", "/");     /*r6pl4*/
        }

        ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));

        if (!ptr)
        {       error_malloc_failed();
                bFatalErrorDetected= TRUE;
                return;
        }

        strcpy(ptr, s);
        toc[p1_toc_counter]->icon_active= ptr;

        if (desttype!=TOHTM && desttype!=TOHAH ) /* New TOHAH; V6.5.17 */
        {       return;
        }

        /* Ausmasse des Icons ermitteln, falls es ein GIF ist */
        /* In s[] steht noch der Dateiname ohne Endung */
        if (strcmp(sDocImgSuffix, ".gif")!=0)
        {       return;
        }

        strinsert(s, old_outfile.path);
        strinsert(s, old_outfile.driv);
        path_adjust_separator(s);
        get_gif_size(s, &toc[p1_toc_counter]->uiIconActiveWidth, &toc[p1_toc_counter]->uiIconActiveHeight);

}       /* set_chapter_icon_active */


GLOBAL void set_chapter_icon_text(void)
{
        char s[512], *ptr;

        if (p1_toc_counter<0)   return;
        if (toc[p1_toc_counter]==NULL)  return;
        if (token[1][0]==EOS)   return;

        tokcpy2(s, 512);
        auto_quote_chars(s, TRUE);

        ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));

        if (!ptr)
        {       error_malloc_failed();
                bFatalErrorDetected= TRUE;
        }
        else
        {       strcpy(ptr, s);
                toc[p1_toc_counter]->icon_text= ptr;
        }

}       /* set_chapter_icon_text */





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

LOCAL BOOLEAN add_toc_to_toc(void)
{
   TOCITEM  *tocptr;  /* ^ to TOCITEM structure */


                                          /* get memory for new TOC structure */
   tocptr = (TOCITEM *)um_malloc(sizeof(TOCITEM));
 
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
*     ???
*
*  Return:
*     ???
*
******************************************|************************************/

LOCAL TOCITEM *init_new_toc_entry(

const int       toctype,    /* */
const BOOLEAN   invisible)  /* TRUE: node is invisible */
{
   TOCITEM     *tocptr;     /* ^ into toc[] structure */


   if (p1_toc_counter >= MAXTOCS)         /* r5pl2 */
   {
      error_too_many_node();
      bBreakInside = TRUE;
      return NULL;
   }

                                          /* get memory for new TOC structure */
   tocptr = (TOCITEM *)um_malloc(sizeof(TOCITEM));
 
   if (tocptr == NULL)                    /* memory error */
      return FALSE;

   memset(tocptr, 0, sizeof(TOCITEM));    /* clear whole (uninitialized) content first */

   tokcpy2(tocptr->name, MAX_NODE_LEN + 1);

   if (tocptr->name[0] == EOS)            /* r5pl14 */
   {
      error_fatal_error("missing node name");
      bFatalErrorDetected = TRUE;
      um_free(tocptr);
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
   tocptr->raw_header_filename = NULL;    /*r6pl10*/
   tocptr->raw_footer_filename = NULL;    /*r6pl10*/
   tocptr->ignore_raw_header   = FALSE;   /*r6pl10*/
   tocptr->ignore_raw_footer   = FALSE;   /*r6pl10*/
   tocptr->ignore_footer       = FALSE;   /*r6pl2*/
   tocptr->filename[0]         = EOS;
   tocptr->dirname[0]          = EOS;
   tocptr->counter_command     = NULL;
   tocptr->keywords            = NULL;
   tocptr->description         = NULL;    /*r6pl5*/
   tocptr->robots              = NULL;    /*V6.5.17*/
   tocptr->bgsound[0]          = '\0';    /* V6.5.20 [GS] */
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
#endif
   
                                          /* V6.5.18 */
   strcpy(tocptr->source_filename, sCurrFileName);
   
   tocptr->toctype             = toctype;
   tocptr->source_line         = uiCurrFileLine;
   tocptr->mapping             = -1;

   strcpy(tocptr->backimage,  sDocBackImage);
   strcpy(tocptr->backcolor,  sDocBackColor);
   strcpy(tocptr->textcolor,  sDocTextColor);
   strcpy(tocptr->linkcolor,  sDocLinkColor);
   strcpy(tocptr->alinkcolor, sDocAlinkColor);
   strcpy(tocptr->vlinkcolor, sDocVlinkColor);

   /* r5pl15: Texinfo kennt keine versteckten Nodes, daher fuer */
   /* Texinfo das invisible-Flag immer aus FALSE setzen. */
   
   if (desttype == TOINF)
      tocptr->invisible = FALSE;
   else
      tocptr->invisible = invisible;

   p1_toctype = toctype;

   return tocptr;
}





/* Nicht LOCAL: wird von abo.c und udo.c benutzt! */

/*******************************************************************************
*
*  add_node_to_toc():
*     ???
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL BOOLEAN add_node_to_toc(

const BOOLEAN   popup,       /* */
const BOOLEAN   invisible)   /* */
{
   TOCITEM     *tocptr;      /* */
   int          li;          /* */
   int          html_merge;  /* */
   
   
   tocptr = init_new_toc_entry(TOC_NODE1, invisible);

   if (tocptr == NULL)
      return FALSE;

   all_nodes++;

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

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOHAH)
   {
      /* Wenn Subsubsubsubnode gemerged werden, dann muss     */
      /* beim letzten Subsubnode dieser Node als              */
      /* naechster Index eingetragen werden!                  */
      
      if (html_merge_node5 && last_n4_index > 0)
         toc[last_n4_index]->next_index = p1_toc_counter + 1;

      /* Wenn Subsubsubnode gemerged werden, dann muss        */
      /* beim letzten Subsubnode dieser Node als              */
      /* naechster Index eingetragen werden!                  */
      
      if (html_merge_node4 && last_n3_index > 0)
         toc[last_n3_index]->next_index = p1_toc_counter + 1;

      /* Wenn Subsubnodes gemerged werden, dann muss beim     */
      /* letzten Subnode dieser Node als naechster            */
      /* Index eingetragen werden!                            */
      
      if (html_merge_node3 && last_n2_index > 0)
         toc[last_n2_index]->next_index = p1_toc_counter + 1;

      /* Werden Subnodes gemerged, so muss beim letzten Node  */
      /* dieser Node als naechster Index eingetragen werden!  */
      
      if (html_merge_node2 && last_n1_index > 0)
         toc[last_n1_index]->next_index = p1_toc_counter + 1;
   }

   /* Der Zeiger auf den Nachfolger muss vom Nachfolger gesetzt werden. */

   tocptr->next_index = 0;

   /* Hilfsvariablen setzen fuer die uebergeordneten Nodes */

   tocptr->up_n1_index = 0;
   tocptr->up_n2_index = 0;
   tocptr->up_n3_index = 0;
   tocptr->up_n4_index = 0;

   last_n1_index = p1_toc_counter + 1;
   last_n2_index = 0;
   last_n3_index = 0;
   last_n4_index = 0;
   last_n5_index = 0;
   
   /* ---------------------------------------------------- */

   p1_toc_counter++;
   toc[p1_toc_counter] = tocptr;

   if (pflag[PASS1].inside_apx)
   {
      apx_available = TRUE;
      
      p1_apx_n1++;
      p1_apx_n2 = 0;
      p1_apx_n3 = 0;
      p1_apx_n4 = 0;
      p1_apx_n5 = 0;
      
      tocptr->appendix = TRUE;
      
      tocptr->n1 = p1_apx_n1;
      tocptr->n2 = p1_apx_n2;
      tocptr->n3 = p1_apx_n3;
      tocptr->n4 = p1_apx_n4;
      tocptr->n5 = p1_apx_n5;
      
      if (!invisible)
      {
         p1_apx_nr1++;
         
         p1_apx_nr2 = 0;
         p1_apx_nr3 = 0;
         p1_apx_nr4 = 0;
         p1_apx_nr5 = 0;
         
         tocptr->nr1 = p1_apx_nr1;
         tocptr->nr2 = p1_apx_nr2;
         tocptr->nr3 = p1_apx_nr3;
         tocptr->nr4 = p1_apx_nr4;
         tocptr->nr5 = p1_apx_nr5;
      }
   }
   else
   {
      toc_available = TRUE;
      p1_toc_n1++;
      p1_toc_n2 = 0;
      p1_toc_n3 = 0;
      p1_toc_n4 = 0;
      p1_toc_n5 = 0;
      
      tocptr->appendix = FALSE;
      
      tocptr->n1 = p1_toc_n1;
      tocptr->n2 = p1_toc_n2;
      tocptr->n3 = p1_toc_n3;
      tocptr->n4 = p1_toc_n4;
      tocptr->n5 = p1_toc_n5;
      
      if (!invisible)
      {
         p1_toc_nr1++;
         p1_toc_nr2 = 0;
         p1_toc_nr3 = 0;
         p1_toc_nr4 = 0;
         p1_toc_nr5 = 0;
         
         tocptr->nr1 = p1_toc_nr1;
         tocptr->nr2 = p1_toc_nr2;
         tocptr->nr3 = p1_toc_nr3;
         tocptr->nr4 = p1_toc_nr4;
         tocptr->nr5 = p1_toc_nr5;
      }
   }

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
   {
      /* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
      /* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */

      get_html_filename(p1_toc_counter, tocptr->filename, &html_merge);
   }

   li = add_label(tocptr->name, TRUE, popup);

   if (li > 0)                            /* and not li>=0, V6.5.17 [GS] */
      tocptr->labindex= li;

   return TRUE;    
}





/*******************************************************************************
*
*  add_subnode_to_toc():
*     ???
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL BOOLEAN add_subnode_to_toc(

const BOOLEAN   popup,       /* */
const BOOLEAN   invisible)   /* */
{
   TOCITEM     *tocptr;      /* */
   int          li;          /* */
   int          html_merge;  /* */
   

   if (last_n1_index == 0)
   {
      error_node2_not_allowed();
      return FALSE;
   }

   tocptr = init_new_toc_entry(TOC_NODE2, invisible);

   if (tocptr == NULL)
      return FALSE;

   all_subnodes++;

   /* ---------------------------------------------------- */
   /* r5pl6: Listenartige Verkettung erzeugen              */
   /* ---------------------------------------------------- */
   /* noch ist p1_toc_counter nich inkrementiert worden,   */
   /* zeigt daher auf den letzten (Sub(Sub))Node           */
   /* Bei HTML muss das Mergen beachtet werden!            */
   
   tocptr->prev_index = p1_toc_counter;

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOHAH)
   {
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

   /* Den Nachfolger des Vorgaengers setzen, also auf  */
   /* bzw. bei !html_merge... auf die letzten          */

   toc[p1_toc_counter]->next_index = p1_toc_counter + 1;

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOHAH)
   {
      /* Wenn Subsubsubsubnode gemerged werden, dann muss     */
      /* beim letzten Subsubnode dieser Subnode als           */
      /* naechster Index eingetragen werden!                  */

      if (html_merge_node5 && last_n4_index > 0)
         toc[last_n4_index]->next_index = p1_toc_counter + 1;

      /* Wenn Subsubsubnode gemerged werden, dann muss        */
      /* beim letzten Subsubnode dieser Subnode als           */
      /* naechster Index eingetragen werden!                  */
      
      if (html_merge_node4 && last_n3_index > 0)
         toc[last_n3_index]->next_index = p1_toc_counter + 1;


      /* Wenn Subsubnodes gemerged werden, dann muss beim     */
      /* letzten Subnode dieser Subnode als naechster         */
      /* Index eingetragen werden!                            */
      
      if (html_merge_node3 && last_n2_index > 0)
         toc[last_n2_index]->next_index = p1_toc_counter + 1;
   }

   /* Der Zeiger auf den Nachfolger muss vom Nachfolger gesetzt werden. */
   tocptr->next_index = 0;

   /* Merken, dass der uebergeordnete Kinder hat */
   /* und die Anzahl der Subnodes erhoehen */
   
   if (last_n1_index>0)
   {
      toc[last_n1_index]->has_children = TRUE;
      toc[last_n1_index]->count_n2++;
   }

   /* Hilfsvariablen setzen fuer die uebergeordneten Nodes */

   tocptr->up_n1_index = last_n1_index;
   tocptr->up_n2_index = 0;
   tocptr->up_n3_index = 0;
   tocptr->up_n4_index = 0;

   last_n2_index = p1_toc_counter + 1;
   last_n3_index = 0;
   last_n4_index = 0;
   last_n5_index = 0;

   /* ---------------------------------------------------- */

   /* Zaehler hochsetzen und Zeiger in das Array kopieren  */
   
   p1_toc_counter++;
   toc[p1_toc_counter] = tocptr;

   if (pflag[PASS1].inside_apx)
   {
      apx_available = TRUE;
      
      p1_apx_n2++;
      p1_apx_n3 = 0;
      p1_apx_n4 = 0;
      p1_apx_n5 = 0;
      
      tocptr->appendix = TRUE;
      
      tocptr->n1 = p1_apx_n1;
      tocptr->n2 = p1_apx_n2;
      tocptr->n3 = p1_apx_n3;
      tocptr->n4 = p1_apx_n4;
      tocptr->n5 = p1_apx_n5;
      
      if (!invisible)
      {
         p1_apx_nr2++;
         p1_apx_nr3 = 0;
         p1_apx_nr4 = 0;
         p1_apx_nr5 = 0;
         
         tocptr->nr1 = p1_apx_nr1;
         tocptr->nr2 = p1_apx_nr2;
         tocptr->nr3 = p1_apx_nr3;
         tocptr->nr4 = p1_apx_nr4;
         tocptr->nr5 = p1_apx_nr5;
      }
   }
   else
   {
      toc_available = TRUE;
      
      p1_toc_n2++;
      p1_toc_n3 = 0;
      p1_toc_n4 = 0;
      p1_toc_n5 = 0;
      
      tocptr->appendix = FALSE;
      
      tocptr->n1 = p1_toc_n1;
      tocptr->n2 = p1_toc_n2;
      tocptr->n3 = p1_toc_n3;
      tocptr->n4 = p1_toc_n4;
      tocptr->n5 = p1_toc_n5;

      if (!invisible)
      {
         p1_toc_nr2++;
         p1_toc_nr3 = 0;
         p1_toc_nr4 = 0;
         p1_toc_nr5 = 0;
         
         tocptr->nr1 = p1_toc_nr1;
         tocptr->nr2 = p1_toc_nr2;
         tocptr->nr3 = p1_toc_nr3;
         tocptr->nr4 = p1_toc_nr4;
         tocptr->nr5 = p1_toc_nr5;
      }
   }

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
   {
      /* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
      /* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */

      get_html_filename(p1_toc_counter, tocptr->filename, &html_merge);
   }

   li = add_label(tocptr->name, TRUE, popup);

   if (li > 0)                            /* and not li>=0, V6.5.17 [GS] */
      tocptr->labindex= li;

   return TRUE;    
}





/*******************************************************************************
*
*  add_subsubnode_to_toc():
*     ???
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL BOOLEAN add_subsubnode_to_toc(

const BOOLEAN   popup,       /* */
const BOOLEAN   invisible)   /* */
{
   TOCITEM     *tocptr;      /* */
   int          li;          /* */
   int          html_merge;  /* */
   

   if (last_n2_index == 0)
   {
      error_node3_not_allowed();
      return FALSE;
   }

   tocptr = init_new_toc_entry(TOC_NODE3, invisible);

   if (tocptr == NULL)
      return FALSE;

   all_subsubnodes++;

   /* ---------------------------------------------------- */
   /* r5pl6: Listenartige Verkettung erzeugen              */
   /* ---------------------------------------------------- */
   /* noch ist p1_toc_counter nich inkrementiert worden    */
   /* und zeigt daher auf den letzten (Sub(Sub))Node        */
   
   tocptr->prev_index = p1_toc_counter;

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOHAH)
   {
      if (html_merge_node5 && last_n4_index > 0)
         tocptr->prev_index = last_n4_index;

      if (html_merge_node4 && last_n3_index > 0)
         tocptr->prev_index = last_n3_index;

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
   
   if (last_n2_index > 0)
   {
      toc[last_n2_index]->has_children = TRUE;
      toc[last_n2_index]->count_n3++;
   }

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOHAH)
   {
      /* Wenn Subsubsubsubnodes gemerged werden, dann muss    */
      /* beim letzten Subsubnode dieser Subsubnode als        */
      /* naechster Index eingetragen werden!                  */

      if (html_merge_node5 && last_n4_index > 0)
         toc[last_n4_index]->next_index = p1_toc_counter + 1;

      /* Wenn Subsubsubnodes gemerged werden, dann muss       */
      /* beim letzten Subsubnode dieser Subsubnode als        */
      /* naechster Index eingetragen werden!                  */

      if (html_merge_node4 && last_n3_index > 0)
         toc[last_n3_index]->next_index = p1_toc_counter + 1;
   }

   /* Der Zeiger auf den Nachfolger muss vom Nachfolger gesetzt werden. */
   
   tocptr->next_index = 0;

   /* Hilfsvariablen setzen fuer die uebergeordneten Nodes */
   
   tocptr->up_n1_index = last_n1_index;
   tocptr->up_n2_index = last_n2_index;
   tocptr->up_n3_index = 0;
   tocptr->up_n4_index = 0;

   last_n3_index = p1_toc_counter + 1;
   last_n4_index = 0;
   last_n5_index = 0;
   
   /* ---------------------------------------------------- */

   p1_toc_counter++;
   toc[p1_toc_counter] = tocptr;

   if (pflag[PASS1].inside_apx)
   {
      apx_available = TRUE;
      p1_apx_n3++;
      p1_apx_n4 = 0;
      p1_apx_n5 = 0;
      
      tocptr->appendix = TRUE;
      
      tocptr->n1 = p1_apx_n1;
      tocptr->n2 = p1_apx_n2;
      tocptr->n3 = p1_apx_n3;
      tocptr->n4 = p1_apx_n4;
      tocptr->n5 = p1_apx_n5;

      if (!invisible)
      {
         p1_apx_nr3++;
         p1_apx_nr4 = 0;
         p1_apx_nr5 = 0;
         
         tocptr->nr1 = p1_apx_nr1;
         tocptr->nr2 = p1_apx_nr2;
         tocptr->nr3 = p1_apx_nr3;
         tocptr->nr4 = p1_apx_nr4;
         tocptr->nr5 = p1_apx_nr5;
      }
   }
   else
   {
      toc_available = TRUE;
      
      p1_toc_n3++;
      p1_toc_n4 = 0;
      p1_toc_n5 = 0;
      
      tocptr->appendix = FALSE;
      
      tocptr->n1 = p1_toc_n1;
      tocptr->n2 = p1_toc_n2;
      tocptr->n3 = p1_toc_n3;
      tocptr->n4 = p1_toc_n4;
      tocptr->n5 = p1_toc_n5;

      {
         p1_toc_nr3++;
         p1_toc_nr4 = 0;
         p1_toc_nr5 = 0;
         
         tocptr->nr1 = p1_toc_nr1;
         tocptr->nr2 = p1_toc_nr2;
         tocptr->nr3 = p1_toc_nr3;
         tocptr->nr4 = p1_toc_nr4;
         tocptr->nr5 = p1_toc_nr5;
      }
   }

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
   {
      /* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
      /* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */
      
      get_html_filename(p1_toc_counter, tocptr->filename, &html_merge);
   }

   li = add_label(tocptr->name, TRUE, popup);

   if (li > 0)
      tocptr->labindex = li;
      
   return TRUE;
}





/*******************************************************************************
*
*  add_subsubsubnode_to_toc():
*     ???
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL BOOLEAN  add_subsubsubnode_to_toc(

const BOOLEAN   popup,       /* */
const BOOLEAN   invisible)   /* */
{
   TOCITEM     *tocptr;      /* */
   int          li;          /* */
   int          html_merge;  /* */
   
   
   if (last_n3_index == 0)
   {
      error_node4_not_allowed();
      return FALSE;
   }

   tocptr = init_new_toc_entry(TOC_NODE4, invisible);

   if (tocptr == NULL)
      return FALSE;

   all_subsubsubnodes++;

   /* ---------------------------------------------------- */
   /* r5pl6: Listenartige Verkettung erzeugen              */
   /* ---------------------------------------------------- */
   /* noch ist p1_toc_counter nicht inkrementiert worden   */
   /* und zeigt daher auf den letzten (Sub(Sub))Node       */
   
   tocptr->prev_index = p1_toc_counter;

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOHAH)
   {
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

   /* Den Nachfolger des Vorgaengers setzen: auf diesen    */
   toc[p1_toc_counter]->next_index= p1_toc_counter+1;

   /* Merken, dass der uebergeordnete Kinder hat */
   /* und die Anzahl der Subsubsubnodes erhoehen */
   
   if (last_n3_index>0)
   {
      toc[last_n3_index]->has_children = TRUE;
      toc[last_n3_index]->count_n4++;
   }

   /* Der Zeiger auf den Nachfolger muss vom Nachfolger gesetzt werden. */

   tocptr->next_index = 0;

   /* Hilfsvariablen setzen fuer die uebergeordneten Nodes */
   
   tocptr->up_n1_index = last_n1_index;
   tocptr->up_n2_index = last_n2_index;
   tocptr->up_n3_index = last_n3_index;
   tocptr->up_n4_index = 0;

   last_n4_index = p1_toc_counter + 1;
   last_n5_index = 0;
   
   /* ---------------------------------------------------- */

   p1_toc_counter++;
   toc[p1_toc_counter] = tocptr;

   if (pflag[PASS1].inside_apx)
   {
      apx_available = TRUE;
      p1_apx_n4++;
      p1_apx_n5 = 0;
      tocptr->appendix = TRUE;
      
      tocptr->n1 = p1_apx_n1;
      tocptr->n2 = p1_apx_n2;
      tocptr->n3 = p1_apx_n3;
      tocptr->n4 = p1_apx_n4;
      tocptr->n5 = p1_apx_n5;
      
      if (!invisible)
      {
         p1_apx_nr4++;
         p1_apx_nr5 = 0;
         
         tocptr->nr1 = p1_apx_nr1;
         tocptr->nr2 = p1_apx_nr2;
         tocptr->nr3 = p1_apx_nr3;
         tocptr->nr4 = p1_apx_nr4;
         tocptr->nr5 = p1_apx_nr5;
      }
   }
   else
   {
      toc_available = TRUE;
      p1_toc_n4++;
      p1_toc_n5 = 0;
      tocptr->appendix = FALSE;
      
      tocptr->n1 = p1_toc_n1;
      tocptr->n2 = p1_toc_n2;
      tocptr->n3 = p1_toc_n3;
      tocptr->n4 = p1_toc_n4;
      tocptr->n5 = p1_toc_n5;
      
      {
         p1_toc_nr4++;
         p1_toc_nr5 = 0;
         
         tocptr->nr1 = p1_toc_nr1;
         tocptr->nr2 = p1_toc_nr2;
         tocptr->nr3 = p1_toc_nr3;
         tocptr->nr4 = p1_toc_nr4;
         tocptr->nr5 = p1_toc_nr5;
      }
   }

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
   {
      /* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
      /* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */
      
      get_html_filename(p1_toc_counter, tocptr->filename, &html_merge);
   }

   li = add_label(tocptr->name, TRUE, popup);

   if (li >= 0)
      tocptr->labindex = li;

   return TRUE;
}





/*******************************************************************************
*
*  add_subsubsubsubnode_to_toc():
*     ???
*
*  Return:
*     ???
*
******************************************|************************************/

GLOBAL BOOLEAN add_subsubsubsubnode_to_toc(

const BOOLEAN   popup,       /* */
const BOOLEAN   invisible)   /* */
{
   TOCITEM     *tocptr;      /* */
   int          li;          /* */
   int          html_merge;  /* */
   
   
   if (last_n4_index == 0)
   {
      error_node5_not_allowed();
      return FALSE;
   }

   tocptr = init_new_toc_entry(TOC_NODE5, invisible);

   if (tocptr == NULL)
      return FALSE;

   all_subsubsubsubnodes++;

   called_subsubsubsubnode = TRUE;        /* r5pl6 */

   /* ---------------------------------------------------- */
   /* r5pl6: Listenartige Verkettung erzeugen              */
   /* ---------------------------------------------------- */
   /* noch ist p1_toc_counter nicht inkrementiert worden   */
   /* und zeigt daher auf den letzten (Sub(Sub))Node       */

   tocptr->prev_index = p1_toc_counter;

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOHAH)
   {
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

   /* Den Nachfolger des Vorgaengers setzen: auf diesen    */
   
   toc[p1_toc_counter]->next_index = p1_toc_counter + 1;

   /* Merken, dass der uebergeordnete Kinder hat */
   /* und die Anzahl der Subsubsubnodes erhoehen */
   
   if (last_n4_index > 0)
   {
      toc[last_n4_index]->has_children = TRUE;
      toc[last_n4_index]->count_n5++;
   }

   /* Der Zeiger auf den Nachfolger muss vom Nachfolger gesetzt werden. */
   
   tocptr->next_index = 0;

   /* Hilfsvariablen setzen fuer die uebergeordneten Nodes */
   
   tocptr->up_n1_index = last_n1_index;
   tocptr->up_n2_index = last_n2_index;
   tocptr->up_n3_index = last_n3_index;
   tocptr->up_n4_index = last_n4_index;

   last_n5_index = p1_toc_counter + 1;
   
   /* ---------------------------------------------------- */

   p1_toc_counter++;
   toc[p1_toc_counter] = tocptr;

   if (pflag[PASS1].inside_apx)
   {
      apx_available = TRUE;
      p1_apx_n5++;

      tocptr->appendix = TRUE;
      
      tocptr->n1 = p1_apx_n1;
      tocptr->n2 = p1_apx_n2;
      tocptr->n3 = p1_apx_n3;
      tocptr->n4 = p1_apx_n4;
      tocptr->n5 = p1_apx_n5;

      if (!invisible)
      {
         p1_apx_nr5++;
         
         tocptr->nr1 = p1_apx_nr1;
         tocptr->nr2 = p1_apx_nr2;
         tocptr->nr3 = p1_apx_nr3;
         tocptr->nr4 = p1_apx_nr4;
         tocptr->nr5 = p1_apx_nr5;
      }
   }
   else
   {
      toc_available = TRUE;
      p1_toc_n5++;
      
      tocptr->appendix = FALSE;
      
      tocptr->n1 = p1_toc_n1;
      tocptr->n2 = p1_toc_n2;
      tocptr->n3 = p1_toc_n3;
      tocptr->n4 = p1_toc_n4;
      tocptr->n5 = p1_toc_n5;

      {
         p1_toc_nr5++;
         
         tocptr->nr1 = p1_toc_nr1;
         tocptr->nr2 = p1_toc_nr2;
         tocptr->nr3 = p1_toc_nr3;
         tocptr->nr4 = p1_toc_nr4;
         tocptr->nr5 = p1_toc_nr5;
      }
   }

                                          /* New TOHAH; V6.5.17 */
   if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
   {
      /* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
      /* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */
      
      get_html_filename(p1_toc_counter, tocptr->filename, &html_merge);
   }

   li = add_label(tocptr->name, TRUE, popup);

   if (li >= 0)
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

GLOBAL BOOLEAN toc_begin_node(

const BOOLEAN   popup, 
const BOOLEAN   invisible)
{
   switch (p1_toctype)
   {
   case TOC_NONE:
      return add_node_to_toc(popup, invisible);

   case TOC_NODE1:
      return add_subnode_to_toc(popup, invisible);

   case TOC_NODE2:
      return add_subsubnode_to_toc(popup, invisible);

   case TOC_NODE3:
      return add_subsubsubnode_to_toc(popup, invisible);

   case TOC_NODE4:
      return add_subsubsubsubnode_to_toc(popup, invisible);

   default:
      return add_subsubsubsubnode_to_toc(popup, invisible);
   }
}





/*******************************************************************************
*
*  toc_end_node():
*     ???
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
   case TOC_NODE2:
      p1_toctype = TOC_NODE1;
      break;
   case TOC_NODE3:
      p1_toctype = TOC_NODE2;
      break;
   case TOC_NODE4:
      p1_toctype = TOC_NODE3;
      break;
   case TOC_NODE5:
      p1_toctype = TOC_NODE4;
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

LOCAL BOOLEAN save_the_alias(

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

GLOBAL BOOLEAN save_htmlhelp_alias(void)
{
   tWinMapData   data;  /* */
   BOOLEAN       flag;  /* */
   
   
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

LOCAL BOOLEAN save_the_map(

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

GLOBAL BOOLEAN save_htmlhelp_map(void)
{
   tWinMapData   data;  /* */
   BOOLEAN       flag;  /* */
   
   
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

GLOBAL BOOLEAN save_winhelp_map_c(void)
{
   tWinMapData   data;  /* */
   BOOLEAN       flag;  /* */
   
   
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

GLOBAL BOOLEAN save_winhelp_map_pas(void)
{
   tWinMapData   data;  /* */
   BOOLEAN       flag;  /* */
   
   
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

GLOBAL BOOLEAN save_winhelp_map_vb(void)
{
   tWinMapData   data;  /* */
   BOOLEAN       flag;  /* */
   
   
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

GLOBAL BOOLEAN save_winhelp_map_gfa(void)
{
   tWinMapData   data;  /* */
   BOOLEAN       flag;  /* */
   
   
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

GLOBAL BOOLEAN save_winhelp4_cnt(void)
{
   FILE          *cntfile;                /* */
   register int   i;                      /* */
   int            li,                     /* */
                  apxstart;               /* */
   char           sName[512],             /* */
                  sMisc[512],             /* */
                  sID[128];               /* */
   BOOLEAN        n1HadChildren = FALSE;  /* */
   BOOLEAN        n2HadChildren = FALSE;  /* */
   BOOLEAN        n3HadChildren = FALSE;  /* */
   BOOLEAN        n4HadChildren = FALSE;  /* */
   

   cntfile = myFwopen(sCntfull, FTCNT);

   if (cntfile == NULL)
      return FALSE;

   save_upr_entry_outfile(sCntfull);

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
               fprintf(cntfile, "5 %s=%s\n", sName, sID);
               
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
                  
                  break;
               
               
               case TOC_NODE5:
                  fprintf(cntfile, "6 %s=%s\n", sName, sID);

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
      strcpy(form_t2_n2, "\\li480\\fi-480\\tx480 %d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n3, "\\li1400\\fi-920\\tx1400 %d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n4, "\\li2400\\fi-1000\\tx2400 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n5, "\\li2400\\fi-1000\\tx2400 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t3_n3, "\\li880\\fi-880\\tx880 %d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t3_n4, "\\li1800\\fi-920\\tx1800 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t3_n5, "\\li1800\\fi-920\\tx1800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_t4_n4, "\\li880\\fi-880\\tx880 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t4_n5, "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_t5_n5, "\\li880\\fi-880\\tx880 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */

      strcpy(form_a1_n1, "\\li320\\fi-320\\tx320 %c\\tab{%s}\\par\\pard");
                                          /* 560 */
      strcpy(form_a1_n2, "\\li880\\fi-560\\tx880 %c.%d\\tab{%s}\\par\\pard");
                                          /* 920 */
      strcpy(form_a1_n3, "\\li1800\\fi-920\\tx1800 %c.%d.%d\\tab{%s}\\par\\pard");
                                          /*1000 */
      strcpy(form_a1_n4, "\\li2800\\fi-1000\\tx2800 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a1_n5, "\\li2800\\fi-1000\\tx2800 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a2_n2, "\\li480\\fi-480\\tx480 %c.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n3, "\\li1400\\fi-920\\tx1400 %c.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n4, "\\li2400\\fi-1000\\tx2400 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n5, "\\li2400\\fi-1000\\tx2400 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a3_n3, "\\li880\\fi-880\\tx880 %c.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a3_n4, "\\li1800\\fi-920\\tx1800 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a3_n5, "\\li1800\\fi-920\\tx1800 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a4_n4, "\\li880\\fi-880\\tx880 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a4_n5, "\\li880\\fi-880\\tx880 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
      strcpy(form_a5_n5, "\\li880\\fi-880\\tx880 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard");/* ToDo: ??? */
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
      strcpy(form_t2_n2, "\\li400\\fi-400\\tx400 %d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n3, "\\li1300\\fi-920\\tx1300 %d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n4, "\\li2200\\fi-1000\\tx2200 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t2_n5, "\\li2200\\fi-1000\\tx2200 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t3_n3, "\\li800\\fi-800\\tx800 %d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t3_n4, "\\li1600\\fi-920\\tx1600 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t3_n5, "\\li1600\\fi-920\\tx1600 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t4_n4, "\\li800\\fi-800\\tx800 %d.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_t4_n5, "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t5_n5, "\\li800\\fi-800\\tx800 %d.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */

      strcpy(form_a1_n1, "\\li300\\fi-300\\tx300 %c\\tab{%s}\\par\\pard");
                                          /* 560 */
      strcpy(form_a1_n2, "\\li800\\fi-500\\tx800 %c.%d\\tab{%s}\\par\\pard");
                                          /* 920 */
      strcpy(form_a1_n3, "\\li1600\\fi-800\\tx1600 %c.%d.%d\\tab{%s}\\par\\pard");
                                          /*1000 */
      strcpy(form_a1_n4, "\\li2600\\fi-1000\\tx2600 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a1_n5, "\\li2600\\fi-1000\\tx2600 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a2_n2, "\\li400\\fi-400\\tx400 %c.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n3, "\\li1300\\fi-920\\tx1300 %c.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n4, "\\li2200\\fi-1000\\tx2200 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a2_n5, "\\li2200\\fi-1000\\tx2200 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a3_n3, "\\li800\\fi-800\\tx800 %c.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a3_n4, "\\li1600\\fi-920\\tx1600 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a3_n5, "\\li1600\\fi-920\\tx1600 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a4_n4, "\\li800\\fi-800\\tx800 %c.%d.%d.%d\\tab{%s}\\par\\pard");
      strcpy(form_a4_n5, "\\li800\\fi-800\\tx800 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_a5_n5, "\\li800\\fi-800\\tx800 %c.%d.%d.%d.%d\\tab{%s}\\par\\pard"); /* ToDo: ??? */
      break;
      

   case TOHAH:
   case TOHTM:
   case TOMHH:
      strcpy(form_t1_n1, "<li>%d %s");
      strcpy(form_t1_n2, "<li>%d.%d %s");
      strcpy(form_t1_n3, "<li>%d.%d.%d %s");
      strcpy(form_t1_n4, "<li>%d.%d.%d.%d %s");
      strcpy(form_t1_n5, "<li>%d.%d.%d.%d.%d %s");
      strcpy(form_t2_n2, form_t1_n2);
      strcpy(form_t2_n3, form_t1_n3);
      strcpy(form_t2_n4, form_t1_n4);
      strcpy(form_t2_n5, form_t1_n5);
      strcpy(form_t3_n3, form_t1_n3);
      strcpy(form_t3_n4, form_t1_n4);
      strcpy(form_t3_n5, form_t1_n5);
      strcpy(form_t4_n4, form_t1_n4);
      strcpy(form_t4_n5, form_t1_n5);
      strcpy(form_t5_n5, form_t1_n5);

      strcpy(form_a1_n1, "<li>%c %s");
      strcpy(form_a1_n2, "<li>%c.%d %s");
      strcpy(form_a1_n3, "<li>%c.%d.%d %s");
      strcpy(form_a1_n4, "<li>%c.%d.%d.%d %s");
      strcpy(form_a1_n5, "<li>%c.%d.%d.%d.%d %s");
      strcpy(form_a2_n2, form_a1_n2);
      strcpy(form_a2_n3, form_a1_n3);
      strcpy(form_a2_n4, form_a1_n4);
      strcpy(form_a2_n5, form_a1_n5);
      strcpy(form_a3_n3, form_a1_n3);
      strcpy(form_a3_n4, form_a1_n4);
      strcpy(form_a3_n5, form_a1_n5);
      strcpy(form_a4_n4, form_a1_n4);
      strcpy(form_a4_n5, form_a1_n5);
      strcpy(form_a5_n5, form_a1_n5);
      break;
      

   case TOTEX:
   case TOPDL:
      strcpy(form_t1_n1, "\\item %d %s");
      strcpy(form_t1_n2, "\\item %d.%d %s");
      strcpy(form_t1_n3, "\\item %d.%d.%d %s");
      strcpy(form_t1_n4, "\\item %d.%d.%d.%d %s");
      strcpy(form_t1_n5, "\\item %d.%d.%d.%d.%d %s");
      strcpy(form_t2_n2, form_t1_n2);
      strcpy(form_t2_n3, form_t1_n3);
      strcpy(form_t2_n4, form_t1_n4);
      strcpy(form_t2_n5, form_t1_n5);
      strcpy(form_t3_n3, form_t1_n3);
      strcpy(form_t3_n4, form_t1_n4);
      strcpy(form_t3_n5, form_t1_n5);
      strcpy(form_t4_n4, form_t1_n4);
      strcpy(form_t4_n5, form_t1_n5);
      strcpy(form_t5_n5, form_t1_n5);

      strcpy(form_a1_n1, "\\item %d %s");
      strcpy(form_a1_n2, "\\item %d.%d %s");
      strcpy(form_a1_n3, "\\item %d.%d.%d %s");
      strcpy(form_a1_n4, "\\item %d.%d.%d.%d %s");
      strcpy(form_a1_n5, "\\item %d.%d.%d.%d.%d %s");
      strcpy(form_a2_n2, form_t1_n2);
      strcpy(form_a2_n3, form_t1_n3);
      strcpy(form_a2_n4, form_t1_n4);
      strcpy(form_a2_n5, form_t1_n5);
      strcpy(form_a3_n3, form_t1_n3);
      strcpy(form_a3_n4, form_t1_n4);
      strcpy(form_a3_n5, form_t1_n5);
      strcpy(form_a4_n4, form_t1_n4);
      strcpy(form_a4_n5, form_t1_n5);
      strcpy(form_a5_n5, form_t1_n5);
      break;


                                          /* New in r6pl15 [NHz] */
   case TOKPS:
      strcpy(form_t1_n1, "(%2d ) udoshow %s newline");
      strcpy(form_t1_n2, "(   %2d.%d ) udoshow %s newline");
      strcpy(form_t1_n3, "(         %2d.%d.%d ) udoshow  %s newline");
      strcpy(form_t1_n4, "(               %2d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t1_n5, "(                     %2d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t2_n2, "(%2d.%d ) udoshow %s newline");
      strcpy(form_t2_n3, "(      %2d.%d.%d ) udoshow %s newline");
      strcpy(form_t2_n4, "(            %2d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t2_n5, "(                  %2d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t3_n3, "(%2d.%d.%d ) udoshow %s newline");
      strcpy(form_t3_n4, "(         %2d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t3_n5, "(              %2d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t4_n4, "(%2d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t4_n5, "(     %2d.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_t5_n5, "(%2d.%d.%d.%d.%d ) udoshow %s newline");

      strcpy(form_a1_n1, "( %c ) udoshow %s newline");
      strcpy(form_a1_n2, "(    %c.%d ) udoshow %s newline");
      strcpy(form_a1_n3, "(         %c.%d.%d ) udoshow  %s newline");
      strcpy(form_a1_n4, "(                 %c.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a1_n5, "(                     %c.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a2_n2, "( %c.%d ) udoshow %s newline");
      strcpy(form_a2_n3, "(      %c.%d.%d ) udoshow %s newline");
      strcpy(form_a2_n4, "(              %c.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a2_n5, "(                  %c.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a3_n3, "( %c.%d.%d ) udoshow %s newline");
      strcpy(form_a3_n4, "(         %c.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a3_n5, "(             %c.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a4_n4, "( %c.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a4_n5, "(     %c.%d.%d.%d.%d ) udoshow %s newline");
      strcpy(form_a5_n5, "( %c.%d.%d.%d.%d ) udoshow %s newline");
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
      strcpy(form_t2_n2, "%2d.%d  %s");
      strcpy(form_t2_n3, "     %2d.%d.%d  %s");
      strcpy(form_t2_n4, "            %2d.%d.%d.%d  %s");
      strcpy(form_t2_n5, "                   %2d.%d.%d.%d.%d  %s");
      strcpy(form_t3_n3, "%2d.%d.%d  %s");
      strcpy(form_t3_n4, "       %2d.%d.%d.%d  %s");
      strcpy(form_t3_n5, "              %2d.%d.%d.%d.%d  %s");
      strcpy(form_t4_n4, "%2d.%d.%d.%d  %s");
      strcpy(form_t4_n5, "       %2d.%d.%d.%d.%d  %s");
      strcpy(form_t5_n5, "%2d.%d.%d.%d.%d  %s");

      strcpy(form_a1_n1, " %c  %s");
      strcpy(form_a1_n2, "    %c.%d  %s");
      strcpy(form_a1_n3, "         %c.%d.%d  %s");
      strcpy(form_a1_n4, "                %c.%d.%d.%d  %s");
      strcpy(form_a1_n5, "                       %c.%d.%d.%d.%d  %s");
      strcpy(form_a2_n2, " %c.%d  %s");
      strcpy(form_a2_n3, "    %c.%d.%d  %s");
      strcpy(form_a2_n4, "           %c.%d.%d.%d  %s");
      strcpy(form_a2_n5, "                  %c.%d.%d.%d.%d  %s");
      strcpy(form_a3_n3, " %c.%d.%d  %s");
      strcpy(form_a3_n4, "        %c.%d.%d.%d  %s");
      strcpy(form_a3_n5, "               %c.%d.%d.%d.%d  %s");
      strcpy(form_a4_n4, " %c.%d.%d.%d  %s");
      strcpy(form_a4_n5, "        %c.%d.%d.%d.%d  %s");
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
      strcpy(form_t2_n2, "{%s}\\par\\pard");
      strcpy(form_t2_n3, "\\li560{%s}\\par\\pard");
      strcpy(form_t2_n4, "\\li1120{%s}\\par\\pard");
      strcpy(form_t2_n5, "\\li1120{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t3_n3, "{%s}\\par\\pard");
      strcpy(form_t3_n4, "\\li560{%s}\\par\\pard");
      strcpy(form_t3_n5, "\\li560{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t4_n4, "{%s}\\par\\pard");
      strcpy(form_t4_n5, "{%s}\\par\\pard"); /* ToDo: ??? */
      strcpy(form_t5_n5, "{%s}\\par\\pard"); /* ToDo: ??? */

      strcpy(form_a1_n1, form_t1_n1);
      strcpy(form_a1_n2, form_t1_n2);
      strcpy(form_a1_n3, form_t1_n3);
      strcpy(form_a1_n4, form_t1_n4);
      strcpy(form_a1_n5, form_t1_n5);
      strcpy(form_a2_n2, form_t2_n2);
      strcpy(form_a2_n3, form_t2_n3);
      strcpy(form_a2_n4, form_t2_n4);
      strcpy(form_a2_n5, form_t2_n5);
      strcpy(form_a3_n3, form_t3_n3);
      strcpy(form_a3_n4, form_t3_n4);
      strcpy(form_a3_n5, form_t3_n5);
      strcpy(form_a4_n4, form_t4_n4);
      strcpy(form_a4_n5, form_t4_n5);
      strcpy(form_a5_n5, form_t5_n5);
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
      strcpy(form_t2_n2, s);
      strcpy(form_t2_n3, s);
      strcpy(form_t2_n4, s);
      strcpy(form_t2_n4, s);
      strcpy(form_t3_n3, s);
      strcpy(form_t3_n4, s);
      strcpy(form_t3_n5, s);
      strcpy(form_t4_n4, s);
      strcpy(form_t4_n5, s);
      strcpy(form_t5_n5, s);

      strcpy(form_a1_n1, s);
      strcpy(form_a1_n2, s);
      strcpy(form_a1_n3, s);
      strcpy(form_a1_n4, s);
      strcpy(form_a1_n5, s);
      strcpy(form_a2_n2, s);
      strcpy(form_a2_n3, s);
      strcpy(form_a2_n4, s);
      strcpy(form_a2_n5, s);
      strcpy(form_a3_n3, s);
      strcpy(form_a3_n4, s);
      strcpy(form_a3_n5, s);
      strcpy(form_a4_n4, s);
      strcpy(form_a4_n5, s);
      strcpy(form_a5_n5, s);
      break;
      

   case TOTEX:
   case TOPDL:
      strcpy(s, "\\item %s");

      strcpy(form_t1_n1, s);
      strcpy(form_t1_n2, s);
      strcpy(form_t1_n3, s);
      strcpy(form_t1_n4, s);
      strcpy(form_t1_n5, s);
      strcpy(form_t2_n2, s);
      strcpy(form_t2_n3, s);
      strcpy(form_t2_n4, s);
      strcpy(form_t2_n4, s);
      strcpy(form_t3_n3, s);
      strcpy(form_t3_n4, s);
      strcpy(form_t3_n5, s);
      strcpy(form_t4_n4, s);
      strcpy(form_t4_n5, s);
      strcpy(form_t5_n5, s);

      strcpy(form_a1_n1, s);
      strcpy(form_a1_n2, s);
      strcpy(form_a1_n3, s);
      strcpy(form_a1_n4, s);
      strcpy(form_a1_n5, s);
      strcpy(form_a2_n2, s);
      strcpy(form_a2_n3, s);
      strcpy(form_a2_n4, s);
      strcpy(form_a2_n5, s);
      strcpy(form_a3_n3, s);
      strcpy(form_a3_n4, s);
      strcpy(form_a3_n5, s);
      strcpy(form_a4_n4, s);
      strcpy(form_a4_n5, s);
      strcpy(form_a5_n5, s);
      break;
      

   case TOINF:
      strcpy(s, "%s");

      strcpy(form_t1_n1, s);
      strcpy(form_t1_n2, s);
      strcpy(form_t1_n3, s);
      strcpy(form_t1_n4, s);
      strcpy(form_t1_n5, s);
      strcpy(form_t2_n2, s);
      strcpy(form_t2_n3, s);
      strcpy(form_t2_n4, s);
      strcpy(form_t2_n4, s);
      strcpy(form_t3_n3, s);
      strcpy(form_t3_n4, s);
      strcpy(form_t3_n5, s);
      strcpy(form_t4_n4, s);
      strcpy(form_t4_n5, s);
      strcpy(form_t5_n5, s);

      strcpy(form_a1_n1, s);
      strcpy(form_a1_n2, s);
      strcpy(form_a1_n3, s);
      strcpy(form_a1_n4, s);
      strcpy(form_a1_n5, s);
      strcpy(form_a2_n2, s);
      strcpy(form_a2_n3, s);
      strcpy(form_a2_n4, s);
      strcpy(form_a2_n5, s);
      strcpy(form_a3_n3, s);
      strcpy(form_a3_n4, s);
      strcpy(form_a3_n5, s);
      strcpy(form_a4_n4, s);
      strcpy(form_a4_n5, s);
      strcpy(form_a5_n5, s);
      break;
      

                                          /* New in r6pl15 [NHz] */
   case TOKPS:
      strcpy(form_t1_n1, " %s newline");
      strcpy(form_t1_n2, "    %s newline");
      strcpy(form_t1_n3, "       %s newline");
      strcpy(form_t1_n4, "          %s newline");
      strcpy(form_t1_n5, "             %s newline");
      strcpy(form_t2_n2, " %s newline");
      strcpy(form_t2_n3, "    %s newline");
      strcpy(form_t2_n4, "       %s newline");
      strcpy(form_t2_n5, "          %s newline");
      strcpy(form_t3_n3, " %s newline");
      strcpy(form_t3_n4, "    %s newline");
      strcpy(form_t3_n5, "      %s newline");
      strcpy(form_t4_n4, " %s newline");
      strcpy(form_t4_n5, "   %s newline");
      strcpy(form_t5_n5, " %s newline");

      strcpy(form_a1_n1, " %s newline");
      strcpy(form_a1_n2, "    %s newline");
      strcpy(form_a1_n3, "       %s newline");
      strcpy(form_a1_n4, "          %s newline");
      strcpy(form_a1_n5, "             %s newline");
      strcpy(form_a2_n2, " %s newline");
      strcpy(form_a2_n3, "    %s newline");
      strcpy(form_a2_n4, "       %s newline");
      strcpy(form_a2_n5, "          %s newline");
      strcpy(form_a3_n3, " %s newline");
      strcpy(form_a3_n4, "    %s newline");
      strcpy(form_a3_n5, "       %s newline");
      strcpy(form_a4_n4, " %s newline");
      strcpy(form_a4_n5, "    %s newline");
      strcpy(form_a5_n5, " %s newline");
      break;
      

   default:
      strcpy(form_t1_n1, " %s");
      strcpy(form_t1_n2, "    %s");
      strcpy(form_t1_n3, "       %s");
      strcpy(form_t1_n4, "          %s");
      strcpy(form_t1_n5, "             %s");
      strcpy(form_t2_n2, " %s");
      strcpy(form_t2_n3, "    %s");
      strcpy(form_t2_n4, "       %s");
      strcpy(form_t2_n5, "          %s");
      strcpy(form_t3_n3, " %s");
      strcpy(form_t3_n4, "    %s");
      strcpy(form_t3_n5, "       %s");
      strcpy(form_t4_n4, " %s");
      strcpy(form_t4_n5, "    %s");
      strcpy(form_t5_n5, " %s");

      strcpy(form_a1_n1, " %s");
      strcpy(form_a1_n2, "    %s");
      strcpy(form_a1_n3, "       %s");
      strcpy(form_a1_n4, "          %s");
      strcpy(form_a1_n5, "             %s");
      strcpy(form_a2_n2, " %s");
      strcpy(form_a2_n3, "    %s");
      strcpy(form_a2_n4, "       %s");
      strcpy(form_a2_n5, "          %s");
      strcpy(form_a3_n3, " %s");
      strcpy(form_a3_n4, "    %s");
      strcpy(form_a3_n5, "       %s");
      strcpy(form_a4_n4, " %s");
      strcpy(form_a4_n5, "    %s");
      strcpy(form_a5_n5, " %s");
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
   }

   if (subtocs1_depth <= 0 || subtocs1_depth > 9)
      subtocs1_depth = 9;

   if (subtocs2_depth <= 0 || subtocs2_depth > 9)
      subtocs2_depth = 9;

   if (subtocs3_depth <= 0 || subtocs3_depth > 9)
      subtocs3_depth = 9;

   if (subtocs4_depth <= 0 || subtocs4_depth > 9)
       subtocs4_depth = 9;


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

GLOBAL BOOLEAN check_module_toc_pass1(void)
{
   int       i,            /* counter */
             j;            /* cunter */
   char      s[512],       /* */
             sTyp[32],     /* */
             sNode[256];   /* */
   BOOLEAN   ret = TRUE;   /* */
   BOOLEAN   checkString;  /* */


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
      show_status_info("Checking nodes, labels and aliases...");
      
      for (i = 1; i <= p1_lab_counter; i++)
      {
         for (j = i + 1; j <= p1_lab_counter; j++)
         {
            if (strcmp(lab[i]->name, lab[j]->name) == 0)
            {
               sprintf(s, "label \"%s\" used twice", lab[i]->name);
               fatal_message(s);

               sNode[0] = EOS;
               strcpy(sTyp, "as a label");
               
               if (lab[i]->is_node)
                  strcpy(sTyp, "as a node");
               
               if (lab[i]->is_alias)
                  strcpy(sTyp, "as an alias");

               if (!lab[i]->is_node)
                  sprintf(sNode, " in node '%s'", toc[lab[i]->tocindex]->name);
               
               sprintf(s, "1. %s%s", sTyp, sNode);
               note_message(s);

               sNode[0] = EOS;
               strcpy(sTyp, "as a label");

               if (lab[j]->is_node)
                  strcpy(sTyp, "as a node");

               if (lab[j]->is_alias)
                  strcpy(sTyp, "as an alias");

               if (!lab[j]->is_node)
                  sprintf(sNode, " in node '%s'", toc[lab[j]->tocindex]->name);

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
         show_status_info("Checking HTML file names...");

         for (i = 0; i < p1_toc_counter; i++)
         {
            for (j = i + 1; j < p1_toc_counter; j++)
            {
               checkString = FALSE;

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
                  sprintf(s, "file name \"%s\" used in \"%s\" and \"%s\"",
                     toc[i]->filename,
                     toc[i]->name,
                     toc[j]->name);

                  fatal_message(s);
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

GLOBAL BOOLEAN check_module_toc_pass2(void)
{
   int    i;       /* counter */
   char   s[512];  /* */
   
   
   show_status_info("");
   show_status_info("Checking usage of labels and aliases...");
   
   for (i = 1; i < p1_lab_counter; i++)
   {
      if (!lab[i]->referenced)
      {
         if (!lab[i]->is_node)
         {
            sprintf(s, "label/alias '%s' in node '%s' wasn't referenced",
               lab[i]->name,
               toc[lab[i]->tocindex]->name);

            note_message(s);
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


   /* -------------------------------------------------------------- */
   /* Zeiger auf den aktuellen Node, Subnode und Subsubnode          */
   /* Mit diesen Variablen kann man toc[] direkt adressieren         */
   /* -------------------------------------------------------------- */
   
   curr_n1_index = 0;
   curr_n2_index = 0;
   curr_n3_index = 0;
   curr_n4_index = 0;                     /* [GS] */


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
   
   p2_toc_n1 = 0;
   p2_toc_n2 = 0;
   p2_toc_n3 = 0;
   p2_toc_n4 = 0;
   p2_toc_n5 = 0;
   
   p1_apx_n1 = 0;
   p1_apx_n2 = 0;
   p1_apx_n3 = 0;
   p1_apx_n4 = 0;
   p1_apx_n5 = 0;

   p2_apx_n1 = 0;
   p2_apx_n2 = 0;
   p2_apx_n3 = 0;
   p2_apx_n4 = 0;
   p2_apx_n5 = 0;


   /* -------------------------------------------------------------- */
   /* Hier nun die Nummern, wie sie im Inhaltsverzeichis erscheinen  */
   /* -------------------------------------------------------------- */
   
   p1_toc_nr1 = 0;
   p1_toc_nr2 = 0;
   p1_toc_nr3 = 0;
   p1_toc_nr4 = 0;
   p1_toc_nr5 = 0;
   
   p1_apx_nr1 = 0;
   p1_apx_nr2 = 0;
   p1_apx_nr3 = 0;
   p1_apx_nr4 = 0;
   p1_apx_nr5 = 0;


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
   
   called_subsubsubsubnode = FALSE;       /* [GS] */


   /* -------------------------------------------------------------- */
   /* p1_toc_counter enthaelt die Anzahl der in pass1() eingelesenen */
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


   /* -------------------------------------------------------------- */
   /* Die Zeichen setzen, die beim Referenzieren vor und nach einem  */
   /* gefundenen Label erlaubt sind.                                 */
   /* -------------------------------------------------------------- */

   sprintf(allowed_next_chars, "\033 !\"#$%%&'()*+,-./:;<=>?@[\\]^_`{|}~%c%c%c", TILDE_C, NBSP_C, INDENT_C);
   
   strcpy(allowed_prev_chars, allowed_next_chars);


   uses_tableofcontents = FALSE;          /* r5pl12 */

   current_chapter_name[0] = EOS;         /* r5pl16 */
   current_chapter_nr[0]   = EOS;         /* r5pl16 */

   footer_buffer[0] = EOS;                /* r6pl2 */

   subtocs1_depth = 9;                    /*r6pl2*/
   subtocs2_depth = 9;                    /*r6pl2*/
   subtocs3_depth = 9;                    /*r6pl2*/
   subtocs4_depth = 9;                    /*r6pl2*/

   no_auto_toptocs_icons = FALSE;         /*r6pl13*/

   strcpy(html_modern_width, "128");      /*r6pl8*/
   
   html_modern_backcolor[0]  = EOS;       /*r6pl6*/

   strcpy(html_frames_width, "128");      /*r6pl8*/
   strcpy(html_frames_height, "64");      /*r6pl9*/
   
   html_frames_backcolor[0]  = EOS;       /*r6pl6*/
   html_frames_textcolor[0]  = EOS;       /*r6pl9*/
   html_frames_linkcolor[0]  = EOS;       /*r6pl9*/
   html_frames_alinkcolor[0] = EOS;       /*r6pl9*/
   html_frames_vlinkcolor[0] = EOS;       /*r6pl9*/
   html_frames_position      = POS_LEFT;  /*r6pl9*/
   html_frames_backimage[0]  = EOS;
   html_name_prefix[0]       = EOS;       /*r6pl12*/

   p1_toctype = TOC_NONE;                 /*r6pl5*/
   p2_toctype = TOC_NONE;                 /*r6pl5*/

   sHtmlPropfontStart[0] = EOS;           /*r6pl7*/
   sHtmlPropfontEnd[0]   = EOS;           /*r6pl7*/

   sHtmlMonofontStart[0] = EOS;           /*r6pl7*/
   sHtmlMonofontEnd[0]   = EOS;           /*r6pl7*/

   html_frames_toc_title = NULL;          /* 6.5.16 */
   html_frames_con_title = NULL;          /* 6.5.16 */
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
      um_free(*var);
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
/*
   r6.3.19[vj]: Der folgende Code wurde auskommentiert, um zu ueberpruefen,
   ob sich hieraus ein Geschwindigkeitsvorteil erlangen laesst. Wird der
   Speicher hier nicht freigegeben, wird das spaeter um_exit tun,
   das die Speicherbereiche viel effizienter freigeben kann.
   
   Bitte nicht loeschen, da er spaeter vielleicht wieder rein kommt!

   register int   i;  / counter /


   for (i = MAXTOCS - 1; i >= 0; i--)
   {
      if (toc[i] != NULL)
      {
         free_toc_data(&(toc[i]->counter_command));
         free_toc_data(&(toc[i]->keywords));
         free_toc_data(&(toc[i]->description));
         free_toc_data(&(toc[i]->robots));
         free_toc_data(&(toc[i]->helpid));
         free_toc_data(&(toc[i]->image));
         free_toc_data(&(toc[i]->icon));
         free_toc_data(&(toc[i]->icon_active));
         free_toc_data(&(toc[i]->icon_text));
         free_toc_data(&(toc[i]->raw_header_filename));
         free_toc_data(&(toc[i]->raw_footer_filename));

         um_free(toc[i]);
         
         toc[i] = NULL;
      }
   }

   for (i = MAXLABELS - 1; i >= 0; i--)
   {
      if (lab[i] != NULL)
      {
         um_free(lab[i]);
      }
   }

                                          / New in V6.5.9 [NHz] /
   for (i = MAXSTYLES - 1; i >= 0; i--)
   {
      if (style[i] != NULL)
      {
         um_free(style[i]);
      }
   }
*/

}       /* exit_module_toc */


/* +++ EOF +++ */
