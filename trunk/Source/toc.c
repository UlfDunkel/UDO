/*	############################################################
	# @(#) toc.c
	# @(#)
	# @(#) Copyright (c) 1995-2001 by Dirk Hagedorn
	# @(#) Dirk Hagedorn (udo@dirk-hagedorn.de)
	#
	# This program is free software; you can redistribute it and/or
	# modify it under the terms of the GNU General Public License
	# as published by the Free Software Foundation; either version 2
	# of the License, or (at your option) any later version.
	# 
	# This program is distributed in the hope that it will be useful,
	# but WITHOUT ANY WARRANTY; without even the implied warranty of
	# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	# GNU General Public License for more details.
	# 
	# You should have received a copy of the GNU General Public License
	# along with this program; if not, write to the Free Software
	# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
	#
	#	Routinen, die sich um Kapitel, Labels, Aliase,
	#	dem Inhaltsverzeichnis und der automatischen
	#	Referenzierung kuemmern
	#
	#	Eine ausfuehrliche Variablenbeschreibung befindet sich
	#	init_module_toc();
	#
	############################################################	*/

#ifndef ID_TOC_C
#define ID_TOC_C
const char *id_toc_c= "@(#) toc.c       12.06.1999";
#endif

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


/*	############################################################
	# Makros & Konstanten
	############################################################	*/
#define	TOC_TOC		0	/* Inhaltsverzeichnis	*/
#define	TOC_NODE1	1	/* !node				*/
#define	TOC_NODE2	2	/* !subnode				*/
#define	TOC_NODE3	3	/* !subsubnode			*/
#define	TOC_NODE4	4	/* !subsubsubnode		*/
#define	TOC_NONE	5	/* weder noch			*/

LOCAL const char *FRAME_NAME_TOC="UDOtoc";
LOCAL const char *FRAME_NAME_CON="UDOcon";

LOCAL const char *FRAME_FILE_TOC="00toc";
LOCAL const char *FRAME_FILE_CON="00con";

LOCAL const char *HTML_LABEL_CONTENTS="UDOTOC";

/*	############################################################
	# lokale Variablen
	############################################################	*/
LOCAL BOOLEAN	toc_available;				/* Inhaltsverzeichnis existiert		*/
LOCAL BOOLEAN	apx_available;				/* Anhang existiert					*/

LOCAL TOCITEM	*toc[MAXTOCS];				/* Zeiger auf Inhaltsverzeichnis	*/
LOCAL int		p1_toc_counter;				/* Zaehler fuer das toc[]-Array		*/
LOCAL int		p2_toc_counter;

LOCAL int		p1_toctype;					/* Typ des aktuellen Kapitels		*/
LOCAL int		p2_toctype;					/* Typ des aktuellen Kapitels		*/

LOCAL LABEL		*lab[MAXLABELS];			/* Array mit Zeigern auf Labels		*/
LOCAL int		p1_lab_counter;				/* Zaehler							*/
LOCAL int		p2_lab_counter;				/* Zaehler, 2. Durchgang			*/

LOCAL REFERENCE	refs[MAXREFERENCES+1];		/* Referenzen	*/
LOCAL int		refs_counter;				/* Zaehler		*/

LOCAL int		p1_toc_n1, p1_toc_n2, p1_toc_n3, p1_toc_n4;	/* absolut */
LOCAL int		p1_apx_n1, p1_apx_n2, p1_apx_n3, p1_apx_n4;

LOCAL int		p1_toc_nr1, p1_toc_nr2, p1_toc_nr3, p1_toc_nr4;	/* Anzeige */
LOCAL int		p1_apx_nr1, p1_apx_nr2, p1_apx_nr3, p1_apx_nr4;

LOCAL int		p2_toc_n1, p2_toc_n2, p2_toc_n3, p2_toc_n4;
LOCAL int		p2_apx_n1, p2_apx_n2, p2_apx_n3, p2_apx_n4;

LOCAL int		curr_n1_index;
LOCAL int		curr_n2_index;
LOCAL int		curr_n3_index;

LOCAL int		last_n1_index;		/* toc[]-Indizes fuer Titelzeilen	*/
LOCAL int		last_n2_index;
LOCAL int		last_n3_index;
LOCAL int		last_n4_index;

LOCAL int		active_nodetype;	/* Flag fuer check_endnode()		*/

LOCAL char		form_t1_n1[80], form_t1_n2[80], form_t1_n3[80], form_t1_n4[80];
LOCAL char		form_t2_n2[80], form_t2_n3[80], form_t2_n4[80];
LOCAL char		form_t3_n3[80], form_t3_n4[80];
LOCAL char		form_t4_n4[80];

LOCAL char		form_a1_n1[80], form_a1_n2[80], form_a1_n3[80], form_a1_n4[80];
LOCAL char		form_a2_n2[80], form_a2_n3[80], form_a2_n4[80];
LOCAL char		form_a3_n3[80], form_a3_n4[80];
LOCAL char		form_a4_n4[80];

LOCAL char		toc_list_top[64], toc_list_end[64];	/*r6pl2*/
LOCAL char		use_toc_list_commands;				/*r6pl2*/

LOCAL char		allowed_next_chars[64];	/* r5pl10 */
LOCAL char		allowed_prev_chars[64];

LOCAL char		footer_buffer[512];		/* Puffer fuer den Footer */	/*r6pl2 */

LOCAL char		html_target[64];


/*	############################################################
	# Prototypen lokaler Funktionen
	############################################################	*/
LOCAL void output_aliasses ( void );

LOCAL BOOLEAN add_ref ( const char *r );
LOCAL void replace_refs ( char *s );
LOCAL void string2reference ( char *ref, const LABEL *l, const BOOLEAN for_toc,
							 const char *pic, const unsigned int uiW, const unsigned int uiH  );

LOCAL BOOLEAN output_raw_file ( const char *filename );

LOCAL void stg_header ( const char *numbers, const char *nodename, BOOLEAN is_popup );

LOCAL void pch_headline ( char *s );
LOCAL void pch_bottomline ( void );
LOCAL void output_pch_header ( const char *numbers, const char *name );

LOCAL void tvh_bottomline ( void );
LOCAL void output_vision_header ( const char *numbers, const char *name );

LOCAL void output_texinfo_node ( const char *name );

LOCAL void win_headline ( char *name, BOOLEAN popup );
LOCAL void output_win_header ( const char *name, const BOOLEAN insivisble );

LOCAL char *get_html_filename ( const int tocindex, char *s );

LOCAL void output_html_meta ( BOOLEAN keywords );
LOCAL void output_html_doctype ( void );
LOCAL BOOLEAN html_new_file ( void );
LOCAL void get_giflink_data ( const int index, char *name, unsigned int *width, unsigned int *height );
LOCAL void html_index_giflink ( const int idxEnabled, const int idxDisabled, const char *sep );
LOCAL void html_home_giflink ( const int idxEnabled, const int idxDisabled, const char *sep );
LOCAL void html_back_giflink ( const int idxEnabled, const int idxDisabled, const char *sep );
LOCAL void html_hb_line ( BOOLEAN head );
LOCAL void html_node_bar_modern ( void );
LOCAL void html_node_bar_frames ( void );

LOCAL void set_inside_node1 ( void );
LOCAL void make_node ( const BOOLEAN popup, const BOOLEAN invisible );
LOCAL void set_inside_node2 ( void );
LOCAL void make_subnode ( const BOOLEAN popup, const BOOLEAN invisible );
LOCAL void set_inside_node3 ( void );
LOCAL void make_subsubnode( const BOOLEAN popup, const BOOLEAN invisible );
LOCAL void set_inside_node4 ( void );
LOCAL void make_subsubsubnode( const BOOLEAN popup, const BOOLEAN invisible );

LOCAL void tocline_make_bold ( char *s, const int depth );
LOCAL void tocline_handle_1st ( BOOLEAN *f );
LOCAL void convert_toc_item ( TOCITEM *t );
LOCAL void output_appendix_line ( void );
LOCAL void toc_link_output ( const int depth ); /* New in r6pl16 [NHz] */
LOCAL void toc_output ( const int depth );
LOCAL void apx_output ( const int depth );
LOCAL void subtoc_output ( const int depth );
LOCAL void subapx_output ( const int depth );
LOCAL void subsubtoc_output ( const int depth );
LOCAL void subsubapx_output ( const int depth );
LOCAL void subsubsubtoc_output ( void );
LOCAL void subsubsubapx_output ( void );

LOCAL void do_toc ( const int depth );
LOCAL void do_subtoc ( const int depth );
LOCAL void do_subsubtoc ( const int depth );
LOCAL void do_subsubsubtoc ( void );

LOCAL void do_toptoc ( const int current_node );

LOCAL int get_toccmd_depth ( void );

LOCAL TOCITEM *init_new_toc_entry ( const int toctype, const BOOLEAN invisible );
LOCAL BOOLEAN add_toc_to_toc ( void );

LOCAL void free_toc_data ( char **var );

/*	------------------------------------------------------------------	*/

/*	############################################################
	#
	# Zu welchem Node gehoert ein Label (fuer ST-Guide, Texinfo, Pure-C-Help)
	#
	#
	# ->	link:	Name des Linkstexts
	# <-	node:	Name des Nodes, in dem das Label benutzt wird
	#		ti:		TOC-Index des Nodes/Labels/Alias
	#		li:		LAB-Index des Nodes/Labels/Alias
	#		isnode:	TRUE:	ist ein Label
	#				FALSE:	ist ein Node oder Alias
	#		TRUE:	Label existiert
	#		FALSE:	Label existiert nicht
	#
	############################################################	*/
GLOBAL BOOLEAN is_node_link ( const char *link, char *node, int *ti, BOOLEAN *isnode, int *li )
{
	register int i;
	BOOLEAN ret= FALSE;
	
	node[0]= EOS;
	*isnode= FALSE;
	
	if (link[0]==EOS)
	{	return FALSE;
	}
	
	for (i=1; i<=p1_lab_counter; i++)
	{	if (strcmp(lab[i]->name, link)==0)
		{	if (lab[i]->is_node)
			{	*isnode= TRUE;
			}
			*li= i;
			*ti= lab[i]->tocindex;
			lab[i]->referenced = TRUE;
			strcpy(node, toc[*ti]->name);
			ret= TRUE;
			break;
		}
	}

	return ret;
}	/* is_node_link */

GLOBAL int getLabelIndexFromTocIndex ( int *li, const int ti )
{
	*li= toc[ti]->labindex;
	return *li;
}


LOCAL void output_helpid(int tocindex)
{
	char	s[256];
	
	s[0] = '\0';
	if ( toc[tocindex]->helpid!=NULL )
	{
		strcpy(s, toc[tocindex]->helpid);
	} else if (use_auto_helpids)
	{
		node2WinAutoID(s, toc[tocindex]->name);
	}
	if (s[0] != '\0')
	{
		switch(desttype)
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
			case TOHTM:
			case TOMHH:
				label2html(s);	/*r6pl2*/
				voutlnf("<a name=\"%s\"></a>", s);
				break;	
			case TOLDS:
				voutlnf("<label id=\"%s\">", s);
				break;	
			case TOTEX:	/* r5pl9 */
			case TOPDL:
				voutlnf("\\label{%s}", s);
				break;
			case TOLYX:	/* <???> */
				break;
		}
	}
}

/*	############################################################
	#
	# Aliasse eines Kapitels ausgeben. Diese muessen nach der
	# Node-Angabe erfolgen.
	#
	############################################################	*/
LOCAL void output_aliasses ( void )
{
	register int i;
	int start;
	char	s[256], keyword[256];

	/* Fuer Pure C Help und Turbo Vision Help werden die Aliasse zusammen */
	/* mit *nodes ausgegeben */

#if 1
	start= toc[p2_toc_counter]->labindex;	/* r6pl2 */
#else
	start= 1;
#endif

	if (start<=0)
	{	return;
	}
	
	for (i=start; i<=p1_lab_counter; i++)
	{	/* r5pl6: aktuellen Zaehler mit Alias-Zugehoerigkeit vergleichen */
		if ( lab[i]->is_alias && p2_toc_counter==lab[i]->tocindex )
		{	switch(desttype)
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
					strcpy(s, lab[i]->name);
					del_internal_styles(s);
					convert_tilde(s);
					if (use_alias_inside_index && !no_index)
					{	strcpy(keyword, s);
						winspecials2ascii(keyword);
						voutlnf("K{\\footnote K %s}", keyword);
					}
					alias2NrWinhelp(s, i);
					voutlnf("#{\\footnote # %s}", s);
					if (bDocWinOldKeywords)
					{	strcpy(s, lab[i]->name);
						del_internal_styles(s);
						node2winhelp(s);
						voutlnf("#{\\footnote # %s}", s);
					}
					break;
				case TORTF:
					strcpy(s, lab[i]->name);
					del_internal_styles(s);
					convert_tilde(s);
					if (use_alias_inside_index && !no_index)
					{	strcpy(keyword, s);
						winspecials2ascii(keyword);
						voutlnf("{\\xe\\v %s}", keyword);
					}
					break;
				case TOHTM:
				case TOMHH:
					strcpy(s, lab[i]->name);
					convert_tilde(s);
					label2html(s);	/* r6pl2 */
					voutlnf("<a name=\"%s\"></a>", s);
					break;	
				case TOLDS:
					strcpy(s, lab[i]->name);
					convert_tilde(s);
					voutlnf("<label id=\"%s\">", s);
					break;	
				case TOTEX:	/* r5pl9 */
				case TOPDL:
					strcpy(s, lab[i]->name);
					convert_tilde(s);
					label2tex(s);
					voutlnf("\\label{%s}", s);
					break;
				case TOLYX:	/* <???> */
					break;
					
			}
		}
	}

	/* r6pl2: Jump-ID ausgeben */
	output_helpid(p2_toc_counter);

}	/* output_aliasses */



/*	############################################################
	# allgemeine Referenz-Routinen
	# Bei Formaten, bei denen Nodes und Labels selbstaendig
	# referenziert werden muessen, koennen folgende Routinen
	# benutzt werden.
	############################################################	*/
GLOBAL void reset_refs ( void )
{
	register int i;

	if ( refs_counter>=0 )
	{	for (i=0; i<=refs_counter; i++)
		{	refs[i].entry[0]= EOS;
			refs[i].magic[0]= EOS;
		}
	}
	
	refs_counter= -1;
}	/* reset_refs */


LOCAL BOOLEAN add_ref ( const char *r )
{
	if (refs_counter<MAXREFERENCES)
	{	refs_counter++;
	
		if (refs_counter+OFFSET_REF==(int) '~')		/* r5pl8 */
		{	refs_counter++;
		}
		if (refs_counter+OFFSET_REF==(int) '\177')	/* r5pl8 */
		{	refs_counter++;
		}

		sprintf(refs[refs_counter].magic, "\033%c%c\033",
			C_REF_MAGIC, refs_counter+OFFSET_REF);
		strcpy(refs[refs_counter].entry, r);
	
		return TRUE;
	}
	
	return FALSE;
}	/* add_ref */


LOCAL void replace_refs ( char *s )
{
	register int i;
	if (refs_counter>=0)
	{	for (i=0; i<=refs_counter; i++)
		{	replace_once(s, refs[i].magic, refs[i].entry);
		}
	}
}	/* replace_refs */


LOCAL void string2reference ( char *ref, const LABEL *l, const BOOLEAN for_toc,
							 const char *pic, const unsigned int uiW, const unsigned int uiH  )
{
	char	s[512], n[512], sNoSty[512], hfn[512], sGifSize[80];
	int		ti, ui;
	BOOLEAN	same_file= FALSE;
	char 	*htmlfilename, suff[MYFILE_SUFF_LEN+1];

	ref[0]= EOS;
	
	switch (desttype)
	{
		case TOWIN:
		case TOWH4:
		case TOAQV:
			strcpy(n, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);
			if (l->is_node)
			{	node2NrWinhelp(s, l->labindex);
			}
			else
			{	if (l->is_alias)
				{	alias2NrWinhelp(s, l->labindex);
				}
				else
				{	label2NrWinhelp(s, l->labindex);
				}
			}
			if (l->is_popup)
			{	sprintf(ref, "{\\ul %s}{\\v %s}", n, s);
			}
			else
			{	sprintf(ref, "{\\uldb %s}{\\v %s}", n, s);
			}
			break;

		case TOIPF:	/* r6pl7 */
			strcpy(n, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);
			if (l->is_node)
			{	node2NrIPF(s, l->labindex);
			}
			else
			{	ui= l->tocindex;
				node2NrIPF(s, toc[ui]->labindex);
			}
			sprintf(ref, ":link refid=%s reftype=hd.%s:elink.", s, n);	/*r6pl8*/
			break;

		case TOSTG:	/* r5pl16 */
			if (l->ignore_links)
			{	strcpy(n, l->name);
				replace_udo_tilde(n);
				replace_udo_nbsp(n);
				node2stg(n);
				sprintf(ref, "@{\"%s\" link \"%s\"}", n, n);
			}
			else
			{	/* wie bei default */
				strcpy(ref, l->name);
				replace_udo_tilde(ref);
				replace_udo_nbsp(ref);
			}
			break;

		case TOAMG:
			strcpy(s, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);
			if (l->is_node)
			{	strcpy(n, l->name);
			}
			else
			{	ti= l->tocindex;
				strcpy(n, lab[toc[ti]->labindex]->name);
			}
			replace_udo_tilde(n);
			replace_udo_nbsp(n);
			node2stg(n);
			sprintf(ref, "@{\"%s\" link \"%s\"}", s, n);
			break;

		case TOTVH:
			strcpy(n, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);
			strcpy(s, n);
			node2vision(s);
			sprintf(ref, "{%s:%s}", n, s);
			break;

		case TOPCH:
			strcpy(n, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);

			if ( strchr(n, '"')!=NULL )
			{	strcpy(s, n);
				node2pchelp(s);
				sprintf(ref, "\\link(\"%s\")%s\\#", s, n);
			}
			else
			{	sprintf(ref, "\\#%s\\#", n);
			}

			if (!for_toc)
			{	/* r5pl10: Referenz als Platzhalter anlegen, damit der */
				/* Blocksatz korrekt wird. */
				insert_placeholder(ref, ref, ref, n);
			}
			break;

		case TOLDS:
			strcpy(n, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);
			sprintf(ref, "<ref id=\"%s\" name=\"%s\">", n, n);
			break;

		case TOINF:
			strcpy(n, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);
			node2texinfo(n);
			sprintf(ref, "* %s::", n);
			break;

		case TOHTM:
		case TOMHH:
			strcpy(n, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);

			strcpy(sNoSty, n);
			del_html_styles(sNoSty);
			label2html(sNoSty);
			
			ti= l->tocindex;

			/* Hier auch das Mergen beachten! */
			ui= ti;	/* upper index = toc index */
			if (html_merge_node4 && toc[ti]->toctype==TOC_NODE4)
			{	ui= toc[ti]->up_n3_index;
			}
			if (html_merge_node3 && toc[ti]->toctype==TOC_NODE3)
			{	ui= toc[ti]->up_n2_index;
			}
			if (html_merge_node2 && toc[ti]->toctype==TOC_NODE2)
			{	ui= toc[ti]->up_n1_index;
			}
			if (html_merge_node1)
			{	ui= 0;
			}

			if (ui==0)
			{	strcpy(hfn, outfile.name);
				htmlfilename= hfn;
			}
			else
			{
#if 1
				sprintf(hfn, "%s%s", html_name_prefix, toc[ui]->filename);
				htmlfilename= hfn;
#else
				htmlfilename= toc[ui]->filename;
#endif
			}

			/* Feststellen, ob die Referenz im gleichen File liegt */
			if (strcmp(htmlfilename, outfile.name)==0)
			{	same_file= TRUE;
			}
			
			/* New in r6pl16 [NHz] */
				if(strchr(htmlfilename, '.') != NULL)
					strcpy(suff, "");
				else
					strcpy(suff, outfile.suff);
			
			if (pic[0]!=EOS)
			{	/* Fuer Kopf- oder Fusszeile */
				if (no_images)	/*r6pl2*/
				{	if (l->is_node || l->is_alias)
					{	sprintf(ref, "<a href=\"%s%s\"%s>%s</a>",
							/* Changed in r6pl16 [NHz] */
							htmlfilename, suff, html_target, n);
					}
					else
					{	sprintf(ref, "<a href=\"%s%s#%s\"%s>%s</a>",
							/* Changed in r6pl16 [NHz] */
							htmlfilename, suff, sNoSty, html_target, n);
					}
				}
				else
				{	
					sGifSize[0]= EOS;
					if (uiW!=0 && uiH!=0)
					{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
					}
					if (l->is_node || l->is_alias)
					{	sprintf(ref, "<a href=\"%s%s\"%s><img src=\"%s\" alt=\"%s\" border=\"0\"%s></a>",
							/* Changed in r6pl16 [NHz] */
							htmlfilename, suff, html_target, pic, n, sGifSize);
					}
					else
					{	sprintf(ref, "<a href=\"%s%s#%s\"%s><img src=\"%s\" alt=\"%s\" border=\"0\"%s></a>",
							/* Changed in r6pl16 [NHz] */
							htmlfilename, suff, sNoSty, html_target, pic, n, sGifSize);
					}
				}
			}
			else
			{	if (l->is_node || l->is_alias)
				{	if (same_file)
					{	sprintf(ref, "<a href=\"#%s\"%s>%s</a>",
							sNoSty, html_target, n);
					}
					else
					{	/* Hier muss noch unterschieden werden, wenn	*/
						/* gemerged wird. Dann ein # einfuegen!!!!		*/
						/* ti oben bereits aus tocindex gesetzt			*/
						if	(	(html_merge_node2 && toc[ti]->n2>0)
							||	(html_merge_node3 && toc[ti]->n3>0)
							||	(html_merge_node4 && toc[ti]->n4>0)
							)
						{	sprintf(ref, "<a href=\"%s%s#%s\"%s>%s</a>",
								/* Changed in r6pl16 [NHz] */
								htmlfilename, suff, sNoSty, html_target, n);
						}
						else
						{	sprintf(ref, "<a href=\"%s%s\"%s>%s</a>",
								/* Changed in r6pl16 [NHz] */
								htmlfilename, suff, html_target, n);
						}
					}
				}
				else
				{	sprintf(ref, "<a href=\"%s%s#%s\"%s>%s</a>",
						/* Changed in r6pl16 [NHz] */
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
			strcpy(n, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);
			/* Changed in r6.2pl1 [NHz] */
			sprintf(ref, "{\\pdfstartlink goto num %d\n%s\\pdfendlink}",
				l->labindex, n);
			break;

		/* New in r6pl15 [NHz] */
		case TOKPS:
			strcpy(n, l->name);
			replace_udo_tilde(n);
			replace_udo_nbsp(n);

			if ( strpbrk(n, " :;\\()/")!=NULL )
			{	strcpy(s, n);
				node2postscript(n, KPS_CONTENT); /* New in r6pl16 [NHz] */
				node2postscript(s, KPS_NAMEDEST); /* Changed in r6pl16 [NHz] */
				sprintf(ref, " (%s) /%s 0 0 0 Link", n, s);
			}
			else
			{	sprintf(ref, " (%s) /%s 0 0 0 Link", n, n);
			}

			if (!for_toc)
			{	/* r5pl10: Referenz als Platzhalter anlegen, damit der */
				/* Blocksatz korrekt wird. */
				insert_placeholder(ref, ref, ref, n);
			}
			break;

		default:
			strcpy(ref, l->name);
			replace_udo_tilde(ref);
			replace_udo_nbsp(ref);
			break;
	}

}	/* string2reference */



GLOBAL void auto_references ( char *s, const BOOLEAN for_toc, const char *pic,
							 const unsigned int uiWidth, const unsigned int uiHeight)
{
	register int i;
	char	the_ref[512], *pos, *ptr, *found_pos, *searchpos;
	char	nextchar, prevchar;
	int found_lab;
	size_t	found_len, ll;
	BOOLEAN	ref_it;
	BOOLEAN	ignore_it;
	BOOLEAN next_ok, prev_ok;
	BOOLEAN found_one, found_ok;
	LABEL *labptr;

	if (bDocAutorefOff)
	{	return;
	}

	if (desttype==TOINF && !for_toc)
	{	/* Automatische Referenzen werden nur fuer Inhaltsverzeichnisse */
		/* gesetzt. Andere Referenzen muessen wie bei TeX mit !link */
		/* manuell erzeugt werden! */
		return;
	}

	reset_refs();
	
	do
	{
		found_lab= -1;
		found_len= 0;
		found_pos= s;
	
		for (i=1; i<MAXLABELS; i++)
		{
			labptr= lab[i];
			
			if (labptr==NULL)
			{	break;
			}

			if ( for_toc || (!for_toc && !labptr->ignore_links) )	/* r5pl15 */
			{
				searchpos= s;
				
				found_one= TRUE;
				found_ok= FALSE;

				while ( found_one && !found_ok )
				{
					ptr= searchpos;

					while ( (pos=strstr(ptr, labptr->name))!=NULL )
					{
						ignore_it= FALSE;
					
						if ( (pos-2>=s) )
						{	if ( pos[-2]=='\033' && pos[-1]<'\010')	/* r5pl9: vorher <' ' */
							{	ptr= pos+2;
								ignore_it= TRUE;
							}
						}
					
						if (!ignore_it)
						{	break;
						}
					}
				
					if ( pos!=NULL )
					{
						found_one= TRUE;
						
						ll= labptr->len;	/* r5pl10: Laenge wird in add_label() vorberechnet */

						if ( ll > found_len )
						{
							nextchar= pos[ll];
							if (pos==s)
							{	prevchar= EOS;
							}
							else
							{	prevchar= pos[-1];
							}
						
							prev_ok= ( prevchar==EOS || strchr(allowed_prev_chars, prevchar)!=NULL );
							next_ok= ( nextchar==EOS || strchr(allowed_next_chars, nextchar)!=NULL );
							
							if ( prev_ok && next_ok )
							{	found_lab= i;
								found_len= ll;
								found_pos= pos;
								found_ok= TRUE;
							}
							else
							{	searchpos= pos+1;
								found_ok= FALSE;
							}
						}
						else
						{	searchpos= pos+1;
							found_ok= FALSE;
						}/* ll > found_len */
					}
					else
					{	/* pos==NULL */
						found_one= FALSE;
						found_ok= FALSE;
						searchpos+= labptr->len;
					}

				}/* while (!found_and_ok) */

			}/* !ignore_links */

		}/* for */

		if (found_lab >= 0)
		{	ref_it= TRUE;
			lab[found_lab]->referenced= TRUE;	/* r6pl9 */

			/* Hier dafuer sorgen, dass nicht innerhalb eines Nodes */
			/* referenziert wird, wenn man nicht im Inhaltsverzeichnis ist */

			if (!for_toc)
			{	if (p2_toc_counter==lab[found_lab]->tocindex)
				{	ref_it= FALSE;
				}
			}
			
			if (ref_it)
			{	string2reference(the_ref, lab[found_lab], for_toc, pic, uiWidth, uiHeight);
				add_ref(the_ref);
			}
			else
			{	add_ref(lab[found_lab]->name);
			}
			
			replace_once(found_pos, lab[found_lab]->name, refs[refs_counter].magic);

		}/* found_lab>=0 */
		
	}	while (found_lab>=0);

	replace_refs(s);
	
}	/* auto_references */



/*	############################################################
	#
	# Ende eines Kapitels testen und ggf. setzen
	#
	############################################################	*/
GLOBAL void check_endnode ( void )
{
	if (active_nodetype!=TOC_NONE)
	{
		switch (active_nodetype)
		{	case TOC_NODE1:
				if (use_auto_subtocs)
				{	do_subtoc(subtocs1_depth);
				}
				break;
			case TOC_NODE2:
				if (use_auto_subsubtocs)
				{	do_subsubtoc(subtocs2_depth);
				}
				break;
			case TOC_NODE3:
				if (use_auto_subsubsubtocs)
				{	do_subsubsubtoc();
				}
				break;
		}

#if 0
		about_unregistered();	/* wird nun am Anfang eines jeden Nodes ausgegeben */
#endif

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
			case TOHTM:
			case TOMHH:
				break;
		}
		
		active_nodetype= TOC_NONE;
		bInsidePopup= FALSE;
	}
	
}	/* check_endnode */


/*	############################################################
	#
	#	Raw-Header einlesen und unverÑndert ausgeben (r6pl10)
	#
	############################################################	*/
LOCAL BOOLEAN output_raw_file ( const char *filename )
{
	MYTEXTFILE *file;
	char s[1024], old_filename[512], tmp_filename[512];
	size_t len;

	strcpy(old_filename, filename);
	strcpy(tmp_filename, filename);

	build_include_filename(tmp_filename, "");

	file = myTextOpen(tmp_filename);
	
	if (!file)
	{
		strcpy(tmp_filename, old_filename);
		file = myTextOpen(tmp_filename);
	}

	if (!file)
	{
		return FALSE;
	}

	while (myTextGetline(s, 1024, file))
	{
		len= strlen(s);
		while (  (len>0) && (((UCHAR) s[len-1])<=32) )
		{	s[len-1]= EOS;
			len--;
		}
		outln(s);
	}

	myTextClose(file);

	return TRUE;

}	/* output_raw_file */


GLOBAL void check_output_raw_header ( void )
{
	if (!toc[p2_toc_counter]->ignore_raw_header)
	{
		if (toc[p2_toc_counter]->raw_header_filename!=NULL)
		{
			output_raw_file(toc[p2_toc_counter]->raw_header_filename);
		}
		else
		{
			if (sDocRawHeaderFilename[0]!=EOS)
			{
				output_raw_file(sDocRawHeaderFilename);
			}
		}
	}

}	/* check_output_raw_header */


GLOBAL void check_output_raw_footer ( BOOLEAN lastNode )
{
	int offset= 1;

	if (lastNode)
	{
		offset= 0;
	}

	/* p2_toc_counter bereits hochgezaehlt, daher 1 abziehen,	*/
	/* aber nur dann, wenn es nicht der letzte Node ist (bei	*/
	/* !end_document tritt das auf)!!!!							*/

	if (!toc[p2_toc_counter-offset]->ignore_raw_footer)
	{
		if (toc[p2_toc_counter-offset]->raw_footer_filename!=NULL)
		{
			output_raw_file(toc[p2_toc_counter-offset]->raw_footer_filename);
		}
		else
		{
			if (sDocRawFooterFilename[0]!=EOS)
			{
				output_raw_file(sDocRawFooterFilename);
			}
		}
	}

}	/* check_output_raw_footer */


/*	############################################################
	#
	# Topline fuer die formatierte ASCII-Ausgabe
	# darf NICHT outln() aufrufen, da sonst Rekursion
	#
	############################################################	*/
GLOBAL void man_headline ( void )
{
	char	n[256];
	char	s1[256];
	size_t	spaces, s1l;
	
	if (no_headlines)
	{	return;
	}
	
	if (titdat.program==NULL)
	{	return;
	}
	
	if (sDocManType[0]!=EOS)
	{	sprintf(s1, "%s%s(%s)%s", BOLD_ON, titdat.program, sDocManType, BOLD_OFF);
	}
	else
	{	sprintf(s1, "%s%s%s", BOLD_ON, titdat.program, BOLD_OFF);
	}
	
	s1l=strlen(s1) - strlen(BOLD_ON) - strlen(BOLD_OFF);
	
	spaces= zDocParwidth-2*s1l;

	sprintf(n, "%s%*s%-*s", s1, (int) spaces, "", (int) s1l, s1);

	c_internal_styles(n);

	fprintf(outfile.file, " %s\n\n", n);
	
	iManPageLines= 2;
	
}	/*man_headline*/


GLOBAL void man_bottomline ( void )
{
	char n[256];

	sprintf(n, "- %d -", iManPagePages+1);
	strcenter(n, zDocParwidth);	
	fprintf(outfile.file, "\n%s\n\n", n);

}	/* man_bottomline */


/*	############################################################
	#
	# Topline fuer den ST-Guide
	#
	############################################################	*/
GLOBAL void stg_headline ( const char *numbers, const char *nodename )
{
	char	n[512], s[512];
	size_t	i, sooft, platz_links, sl;

	do_toptoc(toc[p2_toc_counter]->toctype);

	if (no_headlines) return;

	strcpy(s, numbers);

	if (s[0]!=EOS)
	{	strcat(s, " ");
	}
	
	if (nodename[0]==EOS)
	{	tokcat(s, 512);
	}
	else
	{	strcat(s, nodename);
	}

	replace_udo_quotes(s);
	delete_all_divis(s);

	replace_2at_by_1at(s);

	if (titdat.program!=NULL)
	{	sl= strlen(titdat.program);
	}
	else
	{	sl= 0;
	}
		
	platz_links= zDocParwidth-sl-1;
	
	if (toklen(s)>platz_links)
	{	n[0]= EOS;
		strncat(n, s, platz_links-4);	/*r6pl4: 2 Leerzeichen */
		strcat(n, "...  ");
	}
	else
	{	strcpy(n, s);
		sooft= zDocParwidth-toklen(s)-sl;
	
		for (i=0; i<sooft; i++)
		{	strcat(n, " ");			/* <???>: Optimierbar! */
		}
	}

	replace_1at_by_2at(s);

	if (titdat.program!=NULL)
	{	strcat(n, titdat.program);
	}
	
	c_internal_styles(n);
	replace_udo_tilde(n);
	replace_udo_nbsp(n);
	
	if (desttype==TOSTG)
		voutlnf("@{U}%s@{u}", n);
	else
		voutlnf("@{U}%s@{UU}", n);

	outln("");

}	/* stg_headline */


LOCAL void stg_header ( const char *numbers, const char *nodename, BOOLEAN is_popup )
{
	char	n[512];
	int ti;
	BOOLEAN flag;

	output_aliasses();
	
	ti= p2_toc_counter;
	
	if (ti>=0)
	{
		if (toc[ti]->ignore_links)
		{	outln("@noref");
		}
		
		if (use_chapter_images && toc[ti]->image!=NULL)
		{	
			strcpy(n, toc[ti]->image);
			change_sep_suffix(n, ".img");
			c_begin_center();	/* R6r5pl1 */
			flag= c_img_output(n, "", FALSE);
			c_end_center();
			if (flag)
			{	return;
			}
		}
	}

	if (!is_popup)	
	{	stg_headline(numbers, nodename);
	}

}	/* stg_header */




/*	############################################################
	#
	# Topline und Bottomlines fuer PC-HELP
	#
	############################################################	*/
LOCAL void pch_headline ( char *s )
{
	char	n[512];
	size_t	i, sooft, platz_links, pl;
	
	if (no_headlines)
	{	return;
	}

	pl=0;
	if (titdat.program!=NULL)
	{	pl= strlen(titdat.program);
	}

	platz_links= zDocParwidth-pl-1;
	
	if (strlen(s)>platz_links)
	{	n[0]= EOS;
		strncat(n, s, platz_links-3);
		strcat(n, "...");
	}
	else
	{	strcpy(n, s);
		sooft= zDocParwidth-strlen(s)-pl;
	
		for (i=0; i<sooft; i++)
		{	strcat(n, " ");		/* <???> optimierbar */
		}
	}

	/* r5pl6: Abfragen, ob Programmname vorhanden ist */
	if (titdat.program!=NULL)
	{	if (uses_tableofcontents)
		{	strcat(n, PCH_LINK);	
			strcat(n, titdat.program);
			strcat(n, PCH_LINK);
		}
		else
		{	strcat(n, titdat.program);
		}
	}
	
	replace_udo_quotes(n);
	delete_all_divis(n);
	c_internal_styles(n);
	replace_udo_tilde(n);
	replace_udo_nbsp(n);
	
	outln(n);

	output_ascii_line("-", zDocParwidth);
	
}	/*pch_headline*/



LOCAL void pch_bottomline ( void )
{
	int		ci, pi, ni, ui;
	char	s[256];
	char	*up, *pp, *np;	/*r6pl2: ueber Zeiger, Umkopieren unnoetig */
	
	if (no_bottomlines)
	{	return;
	}

	up= pp= np= NULL;

	if (uses_tableofcontents)		/*r6pl2*/
	{	up= lang.contents;
		pp= lang.contents;
	}
	
	ci=p2_toc_counter;
	pi=toc[ci]->prev_index;
	ni=toc[ci]->next_index;
	ui= 0;

	switch(toc[ci]->toctype)
	{	case TOC_NODE2:	ui= toc[ci]->up_n1_index;	break;
		case TOC_NODE3:	ui= toc[ci]->up_n2_index;	break;
		case TOC_NODE4:	ui= toc[ci]->up_n3_index;	break;
	}
	
	if (ui>0)	up= toc[ui]->name;
	if (pi>0)	pp= toc[pi]->name;
	if (ni>0)	np= toc[ni]->name;

	output_ascii_line("-", zDocParwidth);

	if (up!=NULL)
	{	if (strchr(up, '"')!=NULL)
		{	strcpy(s, up);
			node2pchelp(s);
			voutlnf("[^^^^] \\link(\"%s\")%s\\# ", s, up);
		}
		else
		{	voutlnf("[^^^^] \\#%s\\#", up);
		}
	}
	
	if (pp!=NULL)
	{	if (strchr(pp, '"')!=NULL)
		{	strcpy(s, pp);
			node2pchelp(s);
			voutlnf("[<<<<] \\link(\"%s\")%s\\# ", s, pp);
		}
		else
		{	voutlnf("[<<<<] \\#%s\\#", pp);
		}
	}

	if (np!=NULL)		
	{	if (np[0]!=EOS)
		{	if (strchr(np, '"')!=NULL)
			{	strcpy(s, np);
				node2pchelp(s);
				voutlnf("[>>>>] \\link(\"%s\")%s\\# ", s, np);
			}
			else
			{	voutlnf("[>>>>] \\#%s\\#", np);
			}
		}
	}
	
	outln("");

}	/* pch_bottomline */


LOCAL void output_pch_header ( const char *numbers, const char *name )
{
	char 	n[256], q[256];
	int start;
	register int i;

	outln("");
	outln("screen(");

#if 1
	start= toc[p2_toc_counter]->labindex;
#else
	start= 1;
#endif

	for (i=start; i<MAXLABELS; i++)
	{	if ( lab[i]!=NULL )
		{	if ( lab[i]->tocindex==p2_toc_counter )
			{	strcpy(q, lab[i]->name);
				node2pchelp(q);
				sprintf(n, "  capsensitive(\"%s\")", q);
				if ( i+1<MAXLABELS && lab[i+1]!=NULL )
				{	if ( lab[i+1]->tocindex==p2_toc_counter )
					{	strcat(n, ",");
					}
				}
				replace_all_copyright(n);
				replace_udo_tilde(n);
				replace_udo_nbsp(n);
				outln(n);
			}
			else
			{	if (lab[i]->tocindex>p2_toc_counter)	/* r5pl6 */
				{	break;
				}
			}
		}
		else
		{	break;
		}
	}
	
	outln(")");

	do_toptoc(toc[p2_toc_counter]->toctype);

	sprintf(n, "%s%s", numbers, name);
	pch_headline(n);
	outln("");

}	/* output_pch_header */




/*	############################################################
	#
	# Headline und Bottomlines fuer Turbo-Vision-Help
	#
	############################################################	*/
GLOBAL void tvh_headline ( const char *s )
{
	char n[256];
	size_t	nl;
	
	sprintf(n, " %s \334", s);
	outln(n);
	nl=strlen(n);
	
	strcpy(n, "  ");
	while (strlen(n)<nl)
	{	strcat(n, "\337");
	}
	outln(n);
	outln("");
	
}	/* tvh_headline */


LOCAL void tvh_bottomline ( void )
{
	int		ci, pi, ni, ui;
	char	up[256], pp[256], np[256];
	char	up2[256], pp2[256], np2[256];
	
	if (no_bottomlines)
	{	return;
	}

	c_hline();

	strcpy(up, lang.contents);
	strcpy(pp, lang.contents);
	np[0]= EOS;
	
	ci=p2_toc_counter;
	pi=toc[ci]->prev_index;
	ni=toc[ci]->next_index;
	ui= 0;

	switch(toc[ci]->toctype)
	{	case TOC_NODE2:	ui= toc[ci]->up_n1_index;	break;
		case TOC_NODE3:	ui= toc[ci]->up_n2_index;	break;
		case TOC_NODE4:	ui= toc[ci]->up_n3_index;	break;
	}
	
	if (ui>0)	strcpy(up, toc[ui]->name);
	if (pi>0)	strcpy(pp, toc[pi]->name);
	if (ni>0)	strcpy(np, toc[ni]->name);
	
	strcpy(up2, up);	node2vision(up2);
	strcpy(pp2, pp);	node2vision(pp2);
	strcpy(np2, np);	node2vision(np2);


	voutlnf("  { \036 :%s}", up2);
	voutf(" {%s:%s}", "\021\304", pp2);

	if (np[0]!=EOS)
	{	voutlnf("\301{%s:%s}", "\304\020", np2);
	}
	else
	{	outln("\331");
	}

	outln("");

}	/* tvh_bottomline */


/*	############################################################
	# Turbo-Vision-Help-Node-Header erzeugen
	############################################################	*/
LOCAL void output_vision_header ( const char *numbers, const char *name )
{
	char n[512], l[512];
	register int i;
	size_t nl;
	
	strcpy(n, ".topic ");

	for (i=1; i<MAXLABELS; i++)
	{	if (lab[i]!=NULL)
		{	if ( lab[i]->tocindex==p2_toc_counter )
			{	strcpy(l, lab[i]->name);
				node2vision(l);
				strcat(n, l);
				strcat(n, ",");
			}
			else
			{	if (lab[i]->tocindex>p2_toc_counter)	/* r5pl6 */
				{	break;
				}
			}
		}
		else
		{	break;
		}
	}

	/* Letztes Komma im .topic entfernen */
	nl= strlen(n);
	if ( n[nl-1]==',' )
	{	n[nl-1]= EOS;
	}

	outln(n);
	
	sprintf(n, "%s%s", numbers, name);
	tvh_headline(n);

}	/* output_vision_header */



/*	############################################################
	#
	# Nodeline fuer Texinfo
	#
	############################################################	*/
LOCAL void output_texinfo_node ( const char *name )
{
	int ci, pi, ni, ui;
	char n[512], pp[256], np[256], up[256];
	
	strcpy(n, name);
	strcpy(up, "Top");
	strcpy(np, "");		/* r5pl8: vorher "Top" */
	strcpy(pp, "Top");

	ci= p2_toc_counter;
	pi= toc[ci]->prev_index;
	ni= toc[ci]->next_index;
	ui= 0;
	switch(toc[ci]->toctype)
	{	case TOC_NODE2:	ui= toc[ci]->up_n1_index;	break;
		case TOC_NODE3:	ui= toc[ci]->up_n2_index;	break;
		case TOC_NODE4:	ui= toc[ci]->up_n3_index;	break;
	}

	if (ui>0)	strcpy(up, toc[ui]->name);
	if (pi>0)	strcpy(pp, toc[pi]->name);
	if (ni>0)	strcpy(np, toc[ni]->name);

	node2texinfo(n);
	node2texinfo(np);
	node2texinfo(pp);
	node2texinfo(up);
	
	outln("");

	voutlnf("@node %s, %s, %s, %s", n, np, pp, up);

}	/* output_texinfo_node */




/*	############################################################
	#
	# Topline fuer WinHelp
	#
	############################################################	*/
LOCAL void win_headline ( char *name, BOOLEAN popup )
{
	char n[512], fs[32];
	int	ti;
	
	ti= p2_toc_counter;
	
	if (use_chapter_images)
	{	
		if (ti>=0 && toc[ti]->image!=NULL)
		{	strcpy(n, toc[ti]->image);
			c_begin_center(); 	/* r6pl1 */
			c_bmp_output(n, "", FALSE);
			c_end_center();		/* r6pl1 */
			return;
		}
	}

	/* r5pl16: Headlines wirklich unterdruecken */
	if (no_headlines || toc[ti]->ignore_headline || (no_popup_headlines && popup))
	{	return;
	}
	
	c_win_styles(name);

	if (!popup)
	{	outln("\\keepn");
	}

	do_toptoc(toc[ti]->toctype);	/*r6pl5*/

	sprintf(fs, "\\fs%d", iDocPropfontSize + 14);

	if (popup)
	{	voutlnf("{%s{\\b %s}}\\par\\pard\\par", fs, name);
	}
	else
	{	voutlnf("{%s{\\b\\sa20\\sb20 %s}}\\par\\pard\\par", fs, name);
	}

}	/* win_headline */



LOCAL void output_win_header ( const char *name, const BOOLEAN invisible )
{
	char 	n[512], f[512], cbb[512];
	int		ci, ui;
	char	hlp_name[256];

	const char *btn_disable= "!{\\footnote ! DisableButton(\"BTN_UP\") }";
	const char *btn_enable= "!{\\footnote ! EnableButton(\"BTN_UP\");";
	const char *btn_change= "ChangeButtonBinding(\"BTN_UP\", \"JumpID(%s, `%s') \") }";

	if (desttype==TOAQV)	/* r5pl6 */
	{	strcpy(hlp_name, "qchPath");
	}
	else
	{	sprintf(hlp_name, "`%s.hlp'", outfile.name);
	}

	strcpy(n, name);
	del_internal_styles(n);	/* r5pl3 */

	outln("{");
	
	if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)	/* r5pl10 */
	{	strcpy(f, n);
		winspecials2ascii(f);
		voutlnf("K{\\footnote K %s}", f);
	}

	if (bDocWinOldKeywords)
	{	strcpy(f, n);
		node2winhelp(f);
		voutlnf("#{\\footnote # %s}", f);
	}

	node2NrWinhelp(f, toc[p2_toc_counter]->labindex);	/* r6pl2 */
	voutlnf("#{\\footnote # %s}", f);
	if (toc[p2_toc_counter]->mapping>=0)
	{	voutlnf("#{\\footnote # %d}", toc[p2_toc_counter]->mapping);
	}
	voutlnf("${\\footnote $ %s}", n);	/* r5pl3 */

	if (!no_buttons)	/* r6pl8 */
	{
		if (!invisible)	/* r5pl12: versteckte Kapitel nicht mit in die Browse-Sequence einbinden */
		{	outln(win_browse);
		}

		cbb[0]= EOS;
		ci= p2_toc_counter;
		ui= 0;
		switch(toc[ci]->toctype)
		{	case TOC_NODE2:	ui= toc[ci]->up_n1_index;	break;
			case TOC_NODE3:	ui= toc[ci]->up_n2_index;	break;
			case TOC_NODE4:	ui= toc[ci]->up_n3_index;	break;
		}

		if (ui==0)
		{	if (called_tableofcontents)
			{
				node2NrWinhelp(n, 0);
				sprintf(cbb, btn_change, hlp_name, n);	/* r5pl6 */
				outln(btn_enable);
				outln(cbb);
			}
			else
			{	outln(btn_disable);
			}
		}
		else
		{
			node2NrWinhelp(n, toc[ui]->labindex);
			sprintf(cbb, btn_change, hlp_name, n);	/* r5pl6 */
			outln(btn_enable);
			outln(cbb);
		}
	}
	
}	/* output_win_header */





/*	########################################################################
	# Dateinamen fuer HTML abhaengig vom aktuellen Node ermitteln. UDO
	# splittet die Files selbstaendig und benoetigt u.a. fuer die
	# Referenzen einen eindeutigen Dateinamen. Daher gelangen die Nummern
	# der Kapitel in den Dateinamen. Problem: Ab Kapitel 255 ist's mit der
	# Eindeutigkeit vorbei. Zurueckgeliefert wird nur der Name, kein Suffix
	########################################################################	*/
LOCAL char *get_html_filename ( const int tocindex, char *s )
{	
	/*
		The buffer in tmp_n? is with 17 chars a bit small.
		I inserted the following constant to easier use.
		The buffer increase was neccesary because it of
		bug #0000026 and perhaps #0000004.
		Perhaps its better to check if this buffer is big
		enough! Will try this later [vj]
	*/
	#define	MAX_TMP_NX	50
	char tmp_n1[MAX_TMP_NX], tmp_n2[MAX_TMP_NX], tmp_n3[MAX_TMP_NX], tmp_n4[MAX_TMP_NX];
	int ti;
	int hexwidth;	/* r6pl2 */

#if USE_LONG_FILENAMES
	if (!bForceShort)
	{
		hexwidth= 3;		/* -> 001002003004.html */
	}
	else
	{
		hexwidth= 2;		/* -> 01020304.htm */
	}
#else
	if (bForceLong)	/*r6pl2*/
	{	hexwidth= 3;		/* -> 001002003004.html */
	}
	else
	{	hexwidth= 2;		/* -> 01020304.htm */
	}
#endif

	ti= tocindex;

	if (outfile.file!=stdout || (bTestmode && outfile.full[0]!=EOS) )
	{
		s[0]= EOS;

		tmp_n1[0]= EOS;
		tmp_n2[0]= EOS;
		tmp_n3[0]= EOS;
		tmp_n4[0]= EOS;
		
		if (html_merge_node1)				/* Nodes nicht splitten */
		{	strcpy(tmp_n1, outfile.name);	/* Verweis auf Hauptfile */
		}
		else
		{
			ti= tocindex;					/* default */

#if 0	/* Nur zum Debuggen */
			if (ti<0)
			{	fprintf(stderr, "ti<0\n");
			}
			if (ti>MAXTOCS)
			{	fprintf(stderr, "ti>MAXTOCS\n");
			}
			if (toc[tocindex]==NULL)
			{	fprintf(stderr, "toc[tocindex]==NULL\n");
			}
#endif
			switch (toc[tocindex]->toctype)
			{
				case TOC_NODE4:
					if (html_merge_node4)	ti= toc[tocindex]->up_n3_index;
					if (html_merge_node3)	ti= toc[tocindex]->up_n2_index;
					if (html_merge_node2)	ti= toc[tocindex]->up_n1_index;
					break;
				case TOC_NODE3:
					if (html_merge_node3)	ti= toc[tocindex]->up_n2_index;
					if (html_merge_node2)	ti= toc[tocindex]->up_n1_index;
					break;
				case TOC_NODE2:
					if (html_merge_node2)	ti= toc[tocindex]->up_n1_index;
					break;
			}

			if (toc[ti]->filename[0]!=EOS)
			{	
				/* New in r6pl16 [NHz] */
				{
					char dummy[50], name[50], suff[10];
				
					fsplit(toc[ti]->filename, dummy, dummy, name, suff);
		
					if(strcmp(suff, ""))
						sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, name, suff);
					else
						sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);
				}

				strcpy(tmp_n1, toc[ti]->filename);
			}
			else
			{	if (toc[ti]->appendix)
				{	sprintf(tmp_n1, "_%c", 'a' + toc[ti]->n1 - 1);
				}
				else
				{	if (toc[ti]->n1==0)
					{	strcpy(tmp_n1, old_outfile.name);
					}
					else
					{	sprintf(tmp_n1, "%0*x", hexwidth, toc[ti]->n1);
					}
				}
				if (toc[ti]->n2>0 && !html_merge_node2)	
				{	sprintf(tmp_n2, "%0*x", hexwidth, toc[ti]->n2);
				}
		
				if (toc[ti]->n3>0 && !html_merge_node3)
				{	sprintf(tmp_n3, "%0*x", hexwidth, toc[ti]->n3);
				}

				if (toc[ti]->n4>0 && !html_merge_node4)
				{	sprintf(tmp_n4, "%0*x", hexwidth, toc[ti]->n4);
				}
			}
		}
#if 0
		sprintf(s, "%s%s%s%s%s", html_name_prefix, tmp_n1, tmp_n2, tmp_n3, tmp_n4);
#else
		sprintf(s, "%s%s%s%s", tmp_n1, tmp_n2, tmp_n3, tmp_n4);
#endif
	}
	else
	{
#if USE_LONG_FILENAMES
		if (!bForceShort)
		{	strcpy(s, "stdout.html");	/* r5pl11 */
		}
		else
		{	strcpy(s, "stdout.htm");	/* r5pl11 */
		}
#else
		if (bForceLong)
		{	strcpy(s, "stdout.html");	/* r5pl11 */
		}
		else
		{	strcpy(s, "stdout.htm");	/* r5pl11 */
		}
#endif
	}


	if (s[0]==EOS)
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

}	/*get_html_filename*/




/*	############################################################
	# Neue Datei fuer HTML anlegen, Header und Metainfos ausgeben
	# wird nur fuer das jeweils aktuelle Kapitel aufgerufen
	# (durch html_new_file())
	############################################################	*/
LOCAL BOOLEAN html_make_file ( void )
{
#if 0
	int ti= p2_toc_counter;
#endif

	if (outfile.name[0]==EOS)
	{	return FALSE;
	}

	if (bOutOpened)
	{	fclose(outfile.file);	/* close the already opened file */
		bOutOpened= FALSE;
	}

#if 0
	if (html_use_folders)
	{	
		if (toc[ti]->dirname[0]!=EOS)
		{	sprintf(outfile.path, "%s%s", old_outfile.path, toc[ti]->dirname);
		}
		else
		{	sprintf(outfile.path, "%s%04X", old_outfile.path, toc[ti]->n1);
		}
		
		if (toc[ti]->toctype==TOC_NODE1)
		{	/* Verzeichnis anlegen, falls nicht vorhanden */
			if (toc[ti]->n2==0 && toc[ti]->n3==0 && toc[ti]->n4==0)
			{	char sDir[512];
				sprintf(sDir, "%s%s", outfile.driv, outfile.path);
				my_mkdir(sDir);
			}
		}

		strcat(outfile.path, "\\");
	}
#endif

	/* New in r6pl16 [NHz] */
	{
		char dummy[50], name[50], suff[10];

		strcpy(name, outfile.name);
		fsplit(outfile.name, dummy, dummy, name, suff);

		if(strcmp(suff, ""))
		{
			sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, name, suff);
		}
		else
			sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);
	}
/*	sprintf(outfile.full, "%s%s%s%s", outfile.driv, outfile.path, outfile.name, outfile.suff);*/

	if (!bTestmode)	
	{	outfile.file= myFwopen(outfile.full, TOHTM);
		if (!outfile.file)
		{	error_open_outfile(outfile.full);
			warning_err_destination();
			bErrorDetected= TRUE;
			bFatalErrorDetected= TRUE;
			return FALSE;
		}
		bOutOpened= TRUE;
		save_upr_entry_outfile(outfile.full);
	}

	return TRUE;
}	/* html_make_file */

/* <???> <meta name="Subject" content="..."> */
/* <???> <meta name="Modification-Date" content="..."> */
/* <???> <meta name="Expiration-Date" content="..."> */
/* <???> <meta name="Language" content="..."> */


LOCAL void output_html_meta ( BOOLEAN keywords )
{
	int ti=0, i, li;

	char s[512], htmlname[512], sTarget[512]="\0";
	char backpage[256], href[256], alt[256], *tok;

	if (!html_ignore_8bit)
	{	outln("<meta http-equiv=\"Content-Type\" content=\"text/html;charset=iso-8859-1\">");
	}

	/* New in r6pl16 [NHz] */
	voutlnf("<meta http-equiv=\"Content-Language\" content=\"%s\">", lang.html_lang);
	outln("<meta http-equiv=\"Content-Style-Type\" content=\"text/css\">");
	outln("<meta http-equiv=\"Content-Script-Type\" content=\"text/javascript\">");

	voutlnf("<meta name=\"Generator\" content=\"UDO %s.%s PL%s for %s\">",
			UDO_REL, UDO_SUBVER,
			UDO_PL,
			UDO_OS);

	if (titdat.author!=NULL)
	{	voutlnf("<meta name=\"Author\" content=\"%s\">", titdat.author);
	}

	if (keywords)
	{	ti= p2_toc_counter;
		if (ti>=0)
		{
			if (toc[ti]->keywords!=NULL)
			{	voutlnf("<meta name=\"Keywords\" content=\"%s\">",
						toc[ti]->keywords);
			}
			if (toc[ti]->description!=NULL)
			{	voutlnf("<meta name=\"Description\" content=\"%s\">",
						toc[ti]->description);
			}

		}
	}

	/*r6pl5: <link>-Tag */
	if (titdat.webmasteremail!=NULL)
	{	voutlnf("<meta name=\"Email\" content=\"%s\">", titdat.webmasteremail);
		voutlnf("<link rev=\"made\" href=\"mailto:%s\" title=\"E-Mail\">", titdat.webmasteremail);
		/* New in r6pl16 [NHz] */
		voutlnf("<link rel=\"author\" href=\"mailto:%s\" title=\"E-Mail\">", titdat.webmasteremail);
	}


	/* New in r6pl15 [NHz] */
	if (html_frames_layout)
	{	sprintf(sTarget, " target=\"UDOcon\"");
	}

	/* New in r6pl16 [NHz] */
	toc_link_output(1);
	toc_link_output(2);
	toc_link_output(3);
	toc_link_output(4);

	if (old_outfile.name[0]!=EOS)
	{	/* Changed in r6pl16 [NHz] */
		/* Feststellen, ob die Referenz im gleichen File liegt */
		if (strcmp(old_outfile.name, outfile.name)!=0)
		{
			voutlnf("<link rel=\"start\" href=\"%s%s\"%s title=\"%s\">", old_outfile.name, outfile.suff, sTarget, lang.html_start);
			/* Special for CAB */
			voutlnf("<link rel=\"home\" href=\"%s%s\"%s title=\"%s\">", old_outfile.name, outfile.suff, sTarget, lang.html_start);
			if (uses_tableofcontents)
			{	/* New in r6pl15 [NHz] */
				voutlnf("<link rel=\"contents\" href=\"%s%s#UDOTOC\"%s title=\"%s\">", old_outfile.name, outfile.suff, sTarget, lang.contents);
				/* Special for CAB */
				voutlnf("<link rel=\"toc\" href=\"%s%s#UDOTOC\"%s title=\"%s\">", old_outfile.name, outfile.suff, sTarget, lang.contents);
			}
		}
	}

	/* Andere moegliche Angaben laut SelfHTML 6.0:
	* <link rev=relation href="http://www.autorshome.de/" title="Autoren-Homepage">
	* <link rel=index href="stichwrt.htm" title="Stichwortverzeichnis">
	* <link rel=glossary href="glossar.htm" title="Begriffs-Glossar">
	* <link rel=copyright href="rechte.htm" title="Copyright">
	* <link rel=next href="augsburg.htm" title="nÑchste Seite">
	* <link rel=previous href="aachen.htm" title="vorherige Seite">
	* <link rel=help href="hilfe.htm" title="Orientierungshilfe">
	* <link rel=bookmark href="hinweis.htm" title="Neuorientierung">
	*/


	/* New in r6pl16 [NHz] */
	/* Output of Link-Rel 'up' */
	/* is going to same place than !html_backpage */

	if(sDocHtmlBackpage[0] != EOS)
	{
		strcpy(backpage, sDocHtmlBackpage);
		tok = strtok(backpage, "\'");
		strcpy(href, tok);
		del_right_spaces(href);
		tok = strtok(NULL, "\'");
		if(tok != NULL)
		{
			strcpy(alt, tok);
			auto_quote_chars(alt, TRUE);
		}
		else
			strcpy(alt, href);

		/* Special for CAB */
		voutlnf("<link rel=\"up\" href=\"%s\" title=\"%s\">", href, alt);
	}

	/* New in r6pl15 [NHz] */
	/* Output of Link-Rel 'first' */

	i= toc[ti]->prev_index;

	if (i>0)
	{	/* First Node -> No Link */
		li= toc[1]->labindex;

		strcpy(s, lab[li]->name);
		get_html_filename(lab[li]->tocindex, htmlname);

		/* Special for CAB */
		/* Changed in r6.2pl1 [NHz] / Fixed Bug #0000039 */
		if(strchr(htmlname, '.') != NULL)
			voutlnf("<link rel=\"first\" href=\"%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, sTarget, s);
		else
			voutlnf("<link rel=\"first\" href=\"%s%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, outfile.suff, sTarget, s);
	}


	/* New in r6pl15 [NHz] */
	/* Output of Link-Rel 'prev' */

	if (i>0)
	{
		li= toc[i]->labindex;
		strcpy(s, lab[li]->name);
		get_html_filename(lab[li]->tocindex, htmlname);

		/* Changed in r6.2pl1 [NHz] / Fixed Bug #0000039 */
		if(strchr(htmlname, '.') != NULL)
		{
			voutlnf("<link rel=\"prev\" href=\"%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, sTarget, s);
			/* Special for CAB */
			voutlnf("<link rel=\"previous\" href=\"%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, sTarget, s);
		}
		else
		{
			voutlnf("<link rel=\"prev\" href=\"%s%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, outfile.suff, sTarget, s);
			/* Special for CAB */
			voutlnf("<link rel=\"previous\" href=\"%s%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, outfile.suff, sTarget, s);
		}
	}

	/* Output of Link-Rel 'next' */

	i= toc[ti]->next_index;

	if (i>1)
	{
		li= toc[i]->labindex;
		strcpy(s, lab[li]->name);
		get_html_filename(lab[li]->tocindex, htmlname);

		/* Changed in r6.2pl1 [NHz] / Fixed Bug #0000039*/
		if(strchr(htmlname, '.') != NULL)
			voutlnf("<link rel=\"next\" href=\"%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, sTarget, s);
		else
			voutlnf("<link rel=\"next\" href=\"%s%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, outfile.suff, sTarget, s);
	}

	/* New in r6pl15 [NHz] */
	/* Output of Link-Rel 'last' */

	if (i>1)
	{
		if(use_about_udo)
		{
			li= toc[p1_toc_counter]->labindex;
			li--;
		}
		else
			li= toc[p1_toc_counter]->labindex;
		strcpy(s, lab[li]->name);
		get_html_filename(lab[li]->tocindex, htmlname);

		/* Special for CAB */
		/* Changed in r6.2pl1 [NHz] / Fixed Bug #0000039 */
		if(strchr(htmlname, '.') != NULL)
			voutlnf("<link rel=\"last\" href=\"%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, sTarget, s);
		else
			voutlnf("<link rel=\"last\" href=\"%s%s%s\"%s title=\"%s\">", html_name_prefix, htmlname, outfile.suff, sTarget, s);
	}

	/* New in r6pl15 [NHz] */
	/* Output of Link-Rel 'copyright' */
	/* Link shows to 'About UDO'; maybe changed in future times */

	if(use_about_udo)
	{
		li= toc[p1_toc_counter]->labindex;
		strcpy(s, lab[li]->name);
		get_html_filename(lab[li]->tocindex, htmlname);

		if(strcmp(htmlname, outfile.name)!=0) /* Changed in r6pl16 [NHz] */
			voutlnf("<link rel=\"copyright\" href=\"%s%s\"%s title=\"%s\">", htmlname, outfile.suff, sTarget, s);
	}

	/* New in r6pl15 [NHz] */
	/* Link for overall stylesheet-file */
	if(sDocStyle[0] != EOS)	
		voutlnf("<link rel=\"stylesheet\" type=\"text/css\" href=\"%s\">", sDocStyle);
	/* Link for overall javascript-file */
	if(sDocScript[0] != EOS)
	{
		voutlnf("<script language=\"JavaScript\" src=\"%s\" type=\"text/javascript\">", sDocScript);
		outln("</script>");
	}

	/* New in r6pl15 [NHz] */
	/* Link for overall FavIcon */
	if(sDocFavIcon[0] != EOS)	
		voutlnf("<link rel=\"shortcut icon\" href=\"%s\">", sDocFavIcon);

}	/* output_html_meta */


LOCAL void output_html_doctype ( void )
{
	/* Changed in r6pl16 [NHz] */
	switch(html_doctype)
	{
		case HTML_OLD:
			outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">");
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
			outln("<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>");
			outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"");
		 	outln("        \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
			break;
		case XHTML_TRANS:
			outln("<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>");
			outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"");
		 	outln("        \"http://www.w3.org/TR/xhtml1/DTD/xhtm1-transitional.dtd\">");
			break;
	}
		
	voutlnf("<!-- last modified on %s -->", lang.short_today);
		
}	/* output_html_doctype */



LOCAL BOOLEAN html_new_file ( void )
{
	char t[512], xml_lang[15];

	if (outfile.file==stdout && !bTestmode)
	{	return TRUE;
	}

	/* Bisherige Datei erst einmal schliessen */
	check_endnode();
	voutf("%s", sHtmlPropfontEnd);
	check_output_raw_footer(FALSE);	/*r6pl10*/
	outln("</body></html>");

	/* Dateinamen der neuen Datei ermitteln */
#if 1
	sprintf(outfile.name, "%s%s", html_name_prefix, toc[p2_toc_counter]->filename);
#else
	strcpy(outfile.name, toc[p2_toc_counter]->filename);
#endif

	if (!html_make_file())	/* r6pl4 */
	{	return FALSE;
	}

	output_html_doctype();

	/* Header anlegen, Aktueller Node ist bekannt */
	
	/* Changed in r6pl16 [NHz] */
	if(html_doctype >= XHTML_STRICT)
		sprintf(xml_lang, " xml:lang=\"%s\"", lang.html_lang);
	else
		xml_lang[0] = EOS;
	voutlnf("<html lang=\"%s\"%s>", lang.html_lang, xml_lang);
/*	outln("<html>");*/
	outln("<head>");
	outln("<title>");

	if (desttype==TOHTM)
	{
		if (titdat.htmltitle!=NULL && titdat.htmltitle[0]!=EOS)
		{	strcpy(t, titdat.htmltitle);	/*r6pl5*/
		}
		else
		{	strcpy(t, titleprogram);
		}
	}
	else
	{	t[0]= EOS;
	}

	if ( toc[p2_toc_counter]!=NULL )
	{		if (t[0]!=EOS)
		{	strcat(t, ": ");
		}
		strcat(t, toc[p2_toc_counter]->name);
	}
	outln(t);

	outln("</title>");
	output_html_meta(TRUE);
	outln("</head>");
	
	if ( toc[p2_toc_counter]!=NULL )
	{	out("<body");
		if (toc[p2_toc_counter]->backimage[0]!=EOS)
		{	voutf(" background=\"%s\"", toc[p2_toc_counter]->backimage);
		}
		if (toc[p2_toc_counter]->backcolor[0]!=EOS)
		{	voutf(" bgcolor=\"%s\"", toc[p2_toc_counter]->backcolor);
		}
		if (toc[p2_toc_counter]->textcolor[0]!=EOS)
		{	voutf(" text=\"%s\"", toc[p2_toc_counter]->textcolor);
		}
		if (toc[p2_toc_counter]->linkcolor[0]!=EOS)
		{	voutf(" link=\"%s\"", toc[p2_toc_counter]->linkcolor);
		}
		if (toc[p2_toc_counter]->alinkcolor[0]!=EOS)
		{	voutf(" alink=\"%s\"", toc[p2_toc_counter]->alinkcolor);
		}
		if (toc[p2_toc_counter]->vlinkcolor[0]!=EOS)
		{	voutf(" vlink=\"%s\"", toc[p2_toc_counter]->vlinkcolor);
		}
		outln(">");
	}
	else
	{	outln("<body>");
	}

	check_output_raw_header();	/*r6pl10*/

	outln(sHtmlPropfontStart);

	output_aliasses();	/* r5pl9 */

	if (desttype==TOHTM)
	{	html_headline();
	}
	else
	{	hh_headline();
	}

	return TRUE;
}	/* html_new_file */


GLOBAL void output_html_header ( const char *t )
{
	/* Wird nur fuer die Titelseite/Inhaltsverzeichnis benutzt */
	char xml_lang[15];
	
	output_html_doctype();	/* r6pl2 */
	/* Changed in r6pl16 [NHz] */
	if(html_doctype >= XHTML_STRICT)
		sprintf(xml_lang, " xml:lang=\"%s\"", lang.html_lang);
	else
		xml_lang[0] = EOS;
	voutlnf("<html lang=\"%s\"%s>", lang.html_lang, xml_lang);
/*	outln("<html>");*/
	outln("<head>");
	outln("<title>");
	outln(t);
	outln("</title>");

	/* New in r6pl16 [NHz]
           Fixed: added real title (from <title> Tag) [vj]
        */
	voutlnf("<meta name=\"AppleTitle\" content=\"%s\">", t);

	output_html_meta(TRUE);	/*r6pl5: auch Keywords auf der ersten Seite erlauben */
	outln("</head>");

	out("<body");

	if (sDocBackImage[0]!=EOS)
	{	if (!no_images)	/*r6pl2*/
		{	voutf(" background=\"%s\"", sDocBackImage);
		}
	}
	if (sDocBackColor[0]!=EOS)
	{	voutf(" bgcolor=\"%s\"", sDocBackColor);
	}
	if (sDocTextColor[0]!=EOS)
	{	voutf(" text=\"%s\"", sDocTextColor);
	}
	if (sDocLinkColor[0]!=EOS)
	{	voutf(" link=\"%s\"", sDocLinkColor);
	}
	if (sDocAlinkColor[0]!=EOS)
	{	voutf(" alink=\"%s\"", sDocAlinkColor);
	}
	if (sDocVlinkColor[0]!=EOS)
	{	voutf(" vlink=\"%s\"", sDocVlinkColor);
	}

	voutlnf(">");

	check_output_raw_header();	/*r6pl10*/

	voutlnf("%s", sHtmlPropfontStart);

}	/*output_html_header*/


LOCAL void get_giflink_data ( const int index, char *name, unsigned int *width, unsigned int *height )
{
	name[0]= EOS;
	*width= *height= 0;

	switch (index)
	{
		case GIF_HM_INDEX:
			strcpy(name, GIF_HM_NAME);
			*width= uiGifHmWidth;
			*height= uiGifHmHeight;
			break;
		case GIF_UP_INDEX:
			strcpy(name, GIF_UP_NAME);
			*width= uiGifUpWidth;
			*height= uiGifUpHeight;
			break;
		case GIF_LF_INDEX:
			strcpy(name, GIF_LF_NAME);
			*width= uiGifLfWidth;
			*height= uiGifLfHeight;
			break;
		case GIF_RG_INDEX:
			strcpy(name, GIF_RG_NAME);
			*width= uiGifRgWidth;
			*height= uiGifRgHeight;
			break;
		case GIF_NOHM_INDEX:
			strcpy(name, GIF_NOHM_NAME);
			*width= uiGifNoHmWidth;
			*height= uiGifNoHmHeight;
			break;
		case GIF_NOUP_INDEX:
			strcpy(name, GIF_NOUP_NAME);
			*width= uiGifNoUpWidth;
			*height= uiGifNoUpHeight;
			break;
		case GIF_NOLF_INDEX:
			strcpy(name, GIF_NOLF_NAME);
			*width= uiGifNoLfWidth;
			*height= uiGifNoLfHeight;
			break;
		case GIF_NORG_INDEX:
			strcpy(name, GIF_NORG_NAME);
			*width= uiGifNoRgWidth;
			*height= uiGifNoRgHeight;
			break;
		case GIF_GER_INDEX:
			strcpy(name, GIF_GER_NAME);
			*width= uiGifGerWidth;
			*height= uiGifGerHeight;
			break;
		case GIF_ENG_INDEX:
			strcpy(name, GIF_ENG_NAME);
			*width= uiGifEngWidth;
			*height= uiGifEngHeight;
			break;
	}

}	/* get_giflink_data */


LOCAL void html_index_giflink ( const int idxEnabled, const int idxDisabled, const char *sep )
{
	char sTarget[64], sFile[64], sGifSize[80], sGifName[256];
	unsigned int uiW, uiH;

	sTarget[0]= sGifSize[0]= EOS;

	if (html_frames_layout)
	{	sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
		sprintf(sFile, "%s%s", html_name_prefix, FRAME_FILE_CON);
	}
	else
	{	sTarget[0]= EOS;
		strcpy(sFile, old_outfile.name);
	}


	if (uses_tableofcontents)
	{
		if (no_images)	/*r6pl2*/
		{	voutlnf("%s<a href=\"%s%s#%s\"%s>%s</a>",
				sep, sFile, outfile.suff, HTML_LABEL_CONTENTS, sTarget, " ^^^" /* lang.contents */);
		}
		else
		{

			get_giflink_data(idxEnabled, sGifName, &uiW, &uiH);
			sGifSize[0]= EOS;
			if (uiW!=0 && uiH!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<a href=\"%s%s#%s\"%s><img src=\"%s\" alt=\"%s\" border=\"0\"%s></a>",
						sFile, outfile.suff, HTML_LABEL_CONTENTS, sTarget, sGifName, lang.contents,
						sGifSize);
		}
	}
	else
	{
		if (no_images)
		{	voutlnf("%s ^^^", sep);
		}
		else
		{
			get_giflink_data(idxDisabled, sGifName, &uiW, &uiH);
			sGifSize[0]= EOS;
			if (uiW!=0 && uiH!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" border=\"0\"%s>", sGifName, sGifSize);
		}
	}

}	/* html_index_giflink */



LOCAL void html_home_giflink ( const int idxEnabled, const int idxDisabled, const char *sep )
{
	char sTarget[64], sFile[64];
	char sGifSize[128], sGifName[256];
	unsigned int uiW, uiH;

	if (toc[p2_toc_counter]->toctype==TOC_TOC)
	{	/* r6pl7: Im Inhaltsverzeichnis Link auf !html_backpage mit Home-Symbol */

		sTarget[0]= EOS;

		if (html_frames_layout)
		{	sprintf(sTarget, " target=\"_top\"");
		}

		if (no_images)
		{	voutlnf("%s%s", sep, lang.html_home);
		}
		else
		{	/* Button disabled ausgeben */
			get_giflink_data(idxDisabled, sGifName, &uiW, &uiH);
			sGifSize[0]= EOS;
			if (uiW!=0 && uiH!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" alt=\"%s\" border=\"0\"%s>", sGifName, lang.html_home, sGifSize);
		}
	}
	else
	{
		if (html_frames_layout)
		{	sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
			sprintf(sFile, "%s%s", html_name_prefix, FRAME_FILE_CON);
		}
		else
		{	sTarget[0]= EOS;
			strcpy(sFile, old_outfile.name);
		}
	
		if (no_images)	/*r6pl2*/
		{	voutlnf("%s<a href=\"%s%s\"%s>%s</a>", sep, sFile, outfile.suff, sTarget, lang.html_home);
		}
		else
		{
			get_giflink_data(idxEnabled, sGifName, &uiW, &uiH);
			sGifSize[0]= EOS;
			if (uiW!=0 && uiH!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<a href=\"%s%s\"%s><img src=\"%s\" alt=\"%s\" border=\"0\"%s></a>",
						sFile, outfile.suff, sTarget, sGifName, lang.html_home, sGifSize);
		}
	}

}	/* html_home_giflink */


LOCAL void html_back_giflink ( const int idxEnabled, const int idxDisabled, const char *sep )
{
	char target[64], backpage[256], href[256], alt[256], *tok;
	char sGifSize[128], sGifName[256];
	unsigned int uiW, uiH;

	target[0]= sGifName[0]= EOS;

	if (sDocHtmlBackpage[0]!=EOS)
	{
		/* New in r6pl16 [NHz] */
		strcpy(backpage, sDocHtmlBackpage);
		tok = strtok(backpage, "\'");
		strcpy(href, tok);
		del_right_spaces(href);
		tok = strtok(NULL, "\'");
		if(tok != NULL)
		{
			strcpy(alt, tok);
			auto_quote_chars(alt, TRUE);
		}
		else
			strcpy(alt, href);

		if (html_frames_layout)
		{	sprintf(target, " target=\"_top\"");
		}

		/* Changed in r6pl16 [NHz] */
		if (no_images)
		{	voutlnf("%s<a href=\"%s\"%s>%s</a>",
						sep, href, target, alt);
		} /* changed */
		else
		{
			get_giflink_data(idxEnabled, sGifName, &uiW, &uiH);
			sGifSize[0]= EOS;
			if (uiW!=0 && uiH!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			/* Changed in r6pl16 [NHz] */
			voutlnf("<a href=\"%s\"%s><img src=\"%s\" alt=\"%s\" border=\"0\"%s></a>",
						href, target, sGifName, alt, sGifSize);
		}
	}
	else
	{
		if (no_images)
		{	voutlnf("%s^^^", sep);
		}
		else
		{	/* Diabled Button ausgeben */
			get_giflink_data(idxDisabled, sGifName, &uiW, &uiH);
			sGifSize[0]= EOS;
			if (uiW!=0 && uiH!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" border=\"0\"%s>", sGifName, sGifSize);
		}
	}

}	/* html_back_giflink */



LOCAL void html_hb_line ( BOOLEAN head )
{
	int i, ti, li;
	char s[512], anchor[512], sGifSize[128], sGifFile[128], sTarget[64], *colptr;
	BOOLEAN old_autorefoff;
	BOOLEAN	for_main_file;
	unsigned int uiW, uiH;

	/* Herausfinden, fuer welchen Node die Kopf- und Fusszeile	*/
	/* ausgegeben werden soll. Beim mergen ist der Index nicht	*/
	/* immer gleich dem Nodezaehler im 2. Durchlauf!			*/

	/* Um das Tildenproblem zu loesen, muss ueber lab[]			*/
	/* gegangen werden, da nur dort die Tilden noch nicht		*/
	/* bearbeitet wurden und nur so die Referenzen fuer die		*/
	/* Kopfzeilen gefunden werden!								*/

	ti = p2_toc_counter;
	
	if (ti>0)
	{	if (html_merge_node4)
		{	ti= last_n3_index;
			if (ti<=0)	ti=last_n2_index;	
			if (ti<=0)	ti=last_n1_index;	
		}
		if (html_merge_node3)
		{	ti= last_n2_index;
			if (ti<=0)	ti=last_n1_index;	
		}
		if (html_merge_node2)
		{	ti= last_n1_index;
		}
		if (html_merge_node1)
		{	ti= 0;
		}
	}

	for_main_file= (toc[ti]->toctype==TOC_TOC);

	/* ------------------------------------------- */
	/* ignore_headline/ignore_bottomline testen    */
	/* ------------------------------------------- */
	if (head && toc[ti]->ignore_headline)		/* r5pl12 */
	{	return;
	}

	if (!head && toc[ti]->ignore_bottomline)	/* r5pl12 */
	{	return;
	}

	old_autorefoff= bDocAutorefOff;
	bDocAutorefOff= FALSE;

	if (!head)
	{
		if (!html_modern_layout && !html_frames_layout)
		{
			if (!((no_footers || toc[ti]->ignore_footer) && (no_bottomlines || toc[ti]->ignore_bottomline)))
			{	outln(HTML_HR);
			}
		}
	}


#if 1
	colptr= NULL;
	if (html_modern_layout)	colptr= html_modern_backcolor;
	if (html_frames_layout)	colptr= html_frames_backcolor;

	if(colptr)
	{
		s[0]= EOS;
		if (colptr[0]!=EOS)
		{	sprintf(s, " bgcolor=\"%s\"", colptr);
		}
		voutlnf("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%%\"%s><tr><td valign=\"top\">", s);
	}
#endif

	/* ------------------------------------------------ */
	/* Verweis auf die Homepage erzeugen				*/
	/* ------------------------------------------------ */
	html_home_giflink(GIF_HM_INDEX, GIF_NOHM_INDEX, "[ ");


	/* ------------------------------------------------ */
	/* Verweis auf das uebergeordnete Kapitel erzeugen	*/
	/* ------------------------------------------------ */
	switch (toc[ti]->toctype)
	{	case TOC_TOC:		/* Verweis auf Backpage erzeugen */
			html_back_giflink(GIF_UP_INDEX, GIF_NOUP_INDEX, "| ");
			break;
		case TOC_NODE1:		/* Weiter nach oben geht es nicht */
#if 0
			if (no_images)
			{	outln("| ^^^");
			}
			else
			{
				get_giflink_data(GIF_NOUP_INDEX, s, &uiW, &uiH);
				sGifSize[0]= EOS;
				if (uiW!=0 && uiH!=0)
				{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
				}
				voutlnf("<img src=\"%s\" border=\"0\"%s>", s, sGifSize);
			}
#else
			/* Verweis auf index.htm erzeugen */
			html_index_giflink(GIF_UP_INDEX, GIF_NOUP_INDEX, "| ");
#endif
			break;
		case TOC_NODE2:	/* Verweis auf aktuellen !node */
			li= toc[last_n1_index]->labindex;
			strcpy(s, lab[li]->name);
#if 1
			string2reference(anchor, lab[li], TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
			replace_once(s, lab[li]->name, anchor);
#else
			replace_udo_quotes(s);
			auto_references(s, TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
#endif
			if (no_images)
			{	/* replace_once(s, ">", ">^^^ "); */
				replace_once(s, lab[li]->name, " ^^^");
				strinsert(s, "| ");
			}
			outln(s);
			break;
		case TOC_NODE3:	/* Verweis auf aktuellen !subnode */
			li= toc[last_n2_index]->labindex;
			strcpy(s, lab[li]->name);
#if 1
			string2reference(anchor, lab[li], TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
			replace_once(s, lab[li]->name, anchor);
#else
			replace_udo_quotes(s);
			auto_references(s, TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
#endif
			if (no_images)
			{	/* replace_once(s, ">", ">^^^ "); */
				replace_once(s, lab[li]->name, " ^^^");
				strinsert(s, "| ");
			}
			outln(s);
			break;
		case TOC_NODE4:	/* Verweis auf aktuellen !subsubnode */
			li= toc[last_n3_index]->labindex;
			strcpy(s, lab[li]->name);
#if 1
			string2reference(anchor, lab[li], TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
			replace_once(s, lab[li]->name, anchor);
#else
			replace_udo_quotes(s);
			auto_references(s, TRUE, GIF_UP_NAME, uiGifUpWidth, uiGifUpHeight);
#endif
			if (no_images)
			{	/* replace_once(s, ">", ">^^^ "); */
				replace_once(s, lab[li]->name, " ^^^");
				strinsert(s, "| ");
			}
			outln(s);
			break;
	}
	

	/* --------------------------------------------------- */
	/* Verweis auf die vorherige Seite erzeugen            */
	/* default:                 das letzte Kapitel         */
	/* !html_merge_node1:       kein Aufruf dieser Routine */
	/* !html_merge_node2:		der letzte !node           */
	/* !html_merge_node3:		der letzte !subnode        */
	/* --------------------------------------------------- */
	if (for_main_file)
	{
#if 1
		/* Deaktivierten Link/Bild ausgeben */
		if (no_images)
		{	outln("| &lt;&lt;&lt;");
		}
		else
		{
			get_giflink_data(GIF_NOLF_INDEX, s, &uiW, &uiH);
			sGifSize[0]= EOS;
			if (uiW!=0 && uiH!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" border=\"0\"%s>", s, sGifSize);
		}
#else
		html_back_giflink(GIF_LF_INDEX, GIF_NOLF_INDEX, "| ");
#endif
	}
	else
	{	i= toc[ti]->prev_index;

		if (i==0)
		{	/* Erster Node -> Zurueck zum Hauptfile */
			html_home_giflink(GIF_LF_INDEX, GIF_NOLF_INDEX, "| ");
		}
		else
		{	if (i>0)
			{
				li= toc[i]->labindex;
				strcpy(s, lab[li]->name);
#if 1
				string2reference(anchor, lab[li], TRUE, GIF_LF_NAME, uiGifLfWidth, uiGifLfHeight);
				replace_once(s, lab[li]->name, anchor);
#else
				replace_udo_quotes(s);
				auto_references(s, TRUE, GIF_LF_NAME, uiGifLfWidth, uiGifLfHeight);
#endif
				if (no_images)
				{	/* replace_once(s, ">", ">&lt;&lt;&lt; "); */
					replace_once(s, lab[li]->name, " &lt;&lt;&lt;"); /* [voja][R6PL17] deleted the + at "+replace_once" call */
					strinsert(s, "| ");
				}
				outln(s);
			}
			else
			{
#if 1
				/* disabled nach links */
				if (no_images)
				{	outln("| &lt;&lt;&lt;");
				}
				else
				{
					get_giflink_data(GIF_NOLF_INDEX, s, &uiW, &uiH);
					sGifSize[0]= EOS;
					if (uiW!=0 && uiH!=0)
					{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
					}
					voutlnf("<img src=\"%s\" border=\"0\"%s>", s, sGifSize);
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
	i= 0;
	
	if (for_main_file)
	{	if (p1_toc_counter>0 &&!html_merge_node1)
		{	i= 1;
		}
	}
	else
	{	i= toc[ti]->next_index;
		if (i>0)
		{	if (html_merge_node2)
			{	if (toc[i]->toctype!=TOC_NODE1)
				{	i= 0;
				}
			}
			else
			{	if (html_merge_node3)
				{	if (toc[i]->toctype!=TOC_NODE1 && toc[i]->toctype!=TOC_NODE2)
					{	i= 0;
					}
				}
				else
				{	if (html_merge_node4)
					{	if (toc[i]->toctype!=TOC_NODE1 && toc[i]->toctype!=TOC_NODE2  && toc[i]->toctype!=TOC_NODE3)
						{	i= 0;
						}
					}
				}
			}
		}
	}

	if (i>0)
	{
		li= toc[i]->labindex;
		strcpy(s, lab[li]->name);
#if 1
		string2reference(anchor, lab[li], TRUE, GIF_RG_NAME, uiGifRgWidth, uiGifRgHeight);
		replace_once(s, lab[li]->name, anchor);
#else
		replace_udo_quotes(s);
		auto_references(s, TRUE, GIF_RG_NAME, uiGifRgWidth, uiGifRgHeight);
#endif
		if (no_images)
		{	/* replace_once(s, "</a>", " &gt;&gt;&gt;</a>"); */
			replace_once(s, lab[li]->name, " &gt;&gt;&gt;");
			strinsert(s, "| ");
		}
		outln(s);
	}
	else
	{	/* disabled nach rechts */
		if (no_images)
		{	outln("| &gt;&gt;&gt;");
		}
		else
		{
			get_giflink_data(GIF_NORG_INDEX, s, &uiW, &uiH);
			sGifSize[0]= EOS;
			if (uiW!=0 && uiH!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("<img src=\"%s\" border=\"0\"%s>", s, sGifSize);
		}
	}

	if (html_modern_layout || html_frames_layout)
	{
		if (iDocHtmlSwitchLanguage>=0 && sDocHtmlSwitchLanguage[0]!=EOS)
		{
#if 1
			outln("</td><td valign=\"top\" align=\"right\">");
#endif
			if (no_images)
			{
				switch (iDocHtmlSwitchLanguage)
				{
					case TOGER:	voutlnf("<a href=\"%s\">Deutsch</a>", sDocHtmlSwitchLanguage);	break;
					case TOENG:	voutlnf("<a href=\"%s\">English</a>", sDocHtmlSwitchLanguage);	break;
				}
			}
			else
			{
				if (html_frames_layout)
				{	strcpy(sTarget, " target=\"_top\"");
				}
				else
				{	sTarget[0]= EOS;
				}
				sGifSize[0]= EOS;
				switch (iDocHtmlSwitchLanguage)
				{
					case TOGER:
						get_giflink_data(GIF_GER_INDEX, sGifFile, &uiW, &uiH);
						if (uiW!=0 && uiH!=0)
						{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
						}
						/* Changed in r6pl16 [NHz] */
						voutlnf("<a href=\"%s\"%s><img src=\"%s\" alt=\"Deutsch\" title=\"To the german version of this document\" border=\"0\"%s></a>",
							sDocHtmlSwitchLanguage, sTarget, sGifFile, sGifSize);
						break;
					case TOENG:
						get_giflink_data(GIF_ENG_INDEX, sGifFile, &uiW, &uiH);
						if (uiW!=0 && uiH!=0)
						{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
						}
						/* Changed in r6pl16 [NHz] */
						voutlnf("<a href=\"%s\"%s><img src=\"%s\" alt=\"English\" title=\"Zur englischen Version dieses Dokumentes\" border=\"0\"%s></a>",
								sDocHtmlSwitchLanguage, sTarget, sGifFile, sGifSize);
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
	{	outln("]");
	}

	if (head)
	{	if (!html_modern_layout && !html_frames_layout)
		{	outln(HTML_HR);
		}
	}

	bDocAutorefOff= old_autorefoff;

}	/* html_hb_line */



LOCAL void html_node_bar_modern ( void )
{
	register int i;
	int li;
	unsigned int uiW, uiH;
	char the_ref[1024], *ptrImg, *ptr;
	char *noImg= "";
	char sGifSize[80], sAlignOn[128], sAlignOff[128];
	
	sGifSize[0]= EOS;

#if 1
	voutlnf("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"%s\">", html_modern_width);
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
			break;
	}
#else
	strcpy(sAlignOn, "<center>");
	strcpy(sAlignOff, "</center>");
#endif



	if (p2_toc_counter==0 && titdat.authoricon_active!=NULL)
	{
			if (titdat.authoriconActiveWidth!=0 && titdat.authoriconActiveHeight!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconActiveWidth, titdat.authoriconActiveHeight);
			}
			voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" border=\"0\"%s></a>%s",
				sAlignOn, old_outfile.name, outfile.suff, titdat.authoricon_active, sGifSize, sAlignOff);
	}
	else
	{
		if (titdat.authoricon!=NULL)
		{
			if (titdat.authoriconWidth!=0 && titdat.authoriconHeight!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconWidth, titdat.authoriconHeight);
			}
			voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" border=\"0\"%s></a>%s",
				sAlignOn, old_outfile.name, outfile.suff, titdat.authoricon, sGifSize, sAlignOff);
		}
	}

	if (toc[0]->icon!=NULL)		/*r6pl13*/
	{
		ptrImg= noImg;
		uiW= uiH= 0;
		if (toc[0]->icon!=NULL)
		{	ptrImg= toc[0]->icon;
			uiW= toc[0]->uiIconWidth;
			uiH= toc[0]->uiIconHeight;
		}
		if (toc[0]->icon_active!=NULL)
		{	if (p2_toc_counter==0)
			{	ptrImg= toc[0]->icon_active;
				uiW= toc[0]->uiIconActiveWidth;
				uiH= toc[0]->uiIconActiveHeight;
			}
		}
		if (ptrImg!=noImg)
		{	sGifSize[0]= EOS;
			if (uiW!=0 && uiH!=0)
			{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
			}
			voutlnf("%s<a href=\"%s%s\"><img src=\"%s\" border=\"0\"%s></a>%s",
				sAlignOn, old_outfile.name, outfile.suff, ptrImg, sGifSize, sAlignOff);	/*r6pl13*/
		}
	}
	
	for (i=1; i<=p1_toc_counter; i++)
	{
		if (toc[i]!=NULL)
		{
			if (toc[i]->toctype==TOC_NODE1 && !toc[i]->invisible)
			{
				convert_toc_item(toc[i]);
				li= toc[i]->labindex;

				ptrImg= noImg;
				uiW= uiH= 0;
				if (toc[i]->icon!=NULL)
				{	ptrImg= toc[i]->icon;
					uiW= toc[i]->uiIconWidth;
					uiH= toc[i]->uiIconHeight;
				}
				if (toc[i]->icon_active!=NULL)
				{	if (toc[i]->n1 == p2_toc_n1)
					{	ptrImg= toc[i]->icon_active;
						uiW= toc[i]->uiIconActiveWidth;
						uiH= toc[i]->uiIconActiveHeight;
					}
				}
				string2reference(the_ref, lab[li], FALSE, ptrImg, uiW, uiH);
				if (ptrImg!=noImg && toc[i]->icon_text!=NULL)
				{	ptr= strstr(the_ref, "</a>");
					if (ptr!=NULL)
					{	strinsert(ptr, toc[i]->icon_text);
						strinsert(ptr, "<br>");
					}
				}
				voutlnf("%s%s%s", sAlignOn, the_ref, sAlignOff);	/*r6pl3*/
			}
		}
		else
		{	break;
		}
	}

#if 1
	outln("</table>");
#endif
	
}	/* html_node_bar_modern */



GLOBAL void html_save_frameset ( void )
{
	char add[1024], add2[128], s[512], f1[512], f2[512];

	/* New in r6pl16 [NHz] */
	if(html_doctype >= XHTML_STRICT)
	{
		outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD XHTML 1.0 Frameset//EN\"");
 		outln("        \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd\">");
		voutlnf("<html lang=\"%s\" xml:lang=\"%s\">", lang.html_lang, lang.html_lang);
	}
	else
	{
		outln("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Frameset//EN\"");
 		outln("        \"http://www.w3.org/TR/html4/frameset.dtd\">");
		voutlnf("<html lang=\"%s\">", lang.html_lang);
	}
/*	output_html_doctype();
	outln("<html>");*/
	outln("<head>");
	output_html_meta(TRUE);
	if (titdat.htmltitle!=NULL && titdat.htmltitle[0]!=EOS)
	{	voutlnf("<title>%s</title>", titdat.htmltitle);	/*r6pl5*/
	}
	else
	{	voutlnf("<title>%s</title>", titleprogram);
	}
	outln("</head>");

	add[0]= EOS;
	if (html_frames_noborder)	strcat(add, " border=\"0\" frameborder=\"0\" framespacing=\"0\"");

	add2[0]= EOS;
	if (html_frames_noresize)	strcat(add2, " noresize");
	if (html_frames_noscroll)	strcat(add2, " scrolling=\"no\"");
	sprintf(f1, "\t<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\"%s>",
			html_name_prefix, FRAME_FILE_TOC, outfile.suff, FRAME_NAME_TOC, add2);

	sprintf(f2, "\t<frame src=\"%s%s%s\" name=\"%s\" marginwidth=\"0\" marginheight=\"0\">",
			html_name_prefix, FRAME_FILE_CON, outfile.suff, FRAME_NAME_CON);

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

	/* New in r6pl15 [NHz] */

	/* Noframes for browsers who do not know frames */
	outln("<noframes>");
	c_maketitle();

	c_tableofcontents();

	/* Set both to FALSE in order that the title page and the

			table of contents will be written in the frame again */

	called_maketitle= FALSE;

	called_tableofcontents= FALSE;
	outln("</noframes>");
	outln("</html>");

	/* Das Inhaltverzeichnis fÅr den linken Frame ausgeben */

#if 1
	sprintf(outfile.name, "%s%s", html_name_prefix, FRAME_FILE_TOC);
#else
	strcpy(outfile.name, FRAME_FILE_TOC);
#endif
	if (!html_make_file())
	{	return;
	}
	output_html_doctype();
	outln("<html>");
	outln("<head>");
	voutlnf("<title>%s</title>", lang.contents);
	output_html_meta(FALSE);
	outln("</head>");
	add[0]= EOS;
	if (html_frames_backimage[0]!=EOS)
	{	sprintf(s, " background=\"%s\"", html_frames_backimage);
		strcat(add, s);
	}
	if (html_frames_backcolor[0]!=EOS)
	{	sprintf(s, " bgcolor=\"%s\"", html_frames_backcolor);
		strcat(add, s);
	}
	if (html_frames_linkcolor[0]!=EOS)
	{	sprintf(s, " link=\"%s\"", html_frames_linkcolor);
		strcat(add, s);
	}
	if (html_frames_alinkcolor[0]!=EOS)
	{	sprintf(s, " alink=\"%s\"", html_frames_alinkcolor);
		strcat(add, s);
	}
	if (html_frames_vlinkcolor[0]!=EOS)
	{	sprintf(s, " vlink=\"%s\"", html_frames_vlinkcolor);
		strcat(add, s);
	}
	voutlnf("<body%s class=\"frame_toc\">", add); /* Changed in r6pl16 [NHz] */

	outln(sHtmlPropfontStart);
	html_node_bar_frames();
	voutlnf("%s</body></html>", sHtmlPropfontEnd);

	/* Neue Datei fÅr das erste Kapitel anlegen */

	sprintf(outfile.name, "%s%s", html_name_prefix, FRAME_FILE_CON);
	html_make_file();

}	/* html_save_frameset */ 


LOCAL void html_node_bar_frames ( void )
{
	register int i;
	int li;
	unsigned int uiW, uiH;
	char the_ref[1024], *ptr, *ptrImg, sGifSize[80];
	char  alignOn[128], alignOff[128], divOn[32], divOff[32], rowOn[16], rowOff[16];
	char *noImg= "";

	switch (html_frames_position)
	{
		case POS_LEFT:
		case POS_RIGHT:
			divOn[0]= divOff[0]= rowOn[0]= rowOff[0]= EOS;
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
					break;
			}
			outln(divOn);
			outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\">");
			outln(rowOn);
			break;
		default:
			sprintf(alignOn, "<td nowrap>%s", sHtmlPropfontStart);
			sprintf(alignOff, "%s</td>", sHtmlPropfontEnd);
			strcpy(rowOn, "<tr>");
			strcpy(rowOff, "</tr>");
			switch (html_frames_alignment)
			{
				case ALIGN_LEFT:
					divOn[0]= EOS;
					divOff[0]= EOS;
					break;
				case ALIGN_CENT:
					strcpy(divOn, "<div align=\"center\">");
					strcpy(divOff, "</div>");
					break;
				case ALIGN_RIGH:
					strcpy(divOn, "<div align=\"right\">");
					strcpy(divOff, "</div>");
					break;
			}
			outln(divOn);
			outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\">");
			outln(rowOn);
			break;
	}

	
	if (titdat.authoricon!=NULL)
	{
		sGifSize[0]= EOS;
		if (titdat.authoriconWidth!=0 && titdat.authoriconHeight!=0)
		{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", titdat.authoriconWidth, titdat.authoriconHeight);
		}
		voutlnf("%s<a href=\"%s%s%s\" target=\"%s\"><img src=\"%s%s\" alt=\"\" border=\"0\"%s></a>%s",
			alignOn, html_name_prefix, FRAME_FILE_CON, outfile.suff,
			FRAME_NAME_CON, titdat.authoricon, "" /*sDocImgSuffix*/, sGifSize, alignOff);
	}
	
	for (i=1; i<=p1_toc_counter; i++)
	{
		if (toc[i]!=NULL)
		{
			if (toc[i]->toctype==TOC_NODE1 && !toc[i]->invisible)
			{
				convert_toc_item(toc[i]);
				li= toc[i]->labindex;

				ptrImg= noImg;
				uiW= uiH= 0;
				if (toc[i]->icon!=NULL)
				{	ptrImg= toc[i]->icon;
					uiW= toc[i]->uiIconWidth;
					uiH= toc[i]->uiIconHeight;
				}
				if (toc[i]->icon_active!=NULL)
				{	if (toc[i]->n1 == p2_toc_n1)
					{	ptrImg= toc[i]->icon_active;
						uiW= toc[i]->uiIconActiveWidth;
						uiH= toc[i]->uiIconActiveHeight;
					}
				}
				string2reference(the_ref, lab[li], FALSE, ptrImg, uiW, uiH);

				/* Im Inhaltsverzeichnis DARF nicht <a href="#..."> stehen! */
				/* kleiner Zwischenhack, da Frames mit gemergten Nodes wohl */
				/* niemand ernsthaft verwenden werden wird. */
				ptr= strstr(the_ref, "href=\"#");
				if (ptr!=NULL)
				{	ptr+= 6;
					strinsert(ptr, outfile.suff);
					strinsert(ptr, FRAME_FILE_CON);
					strinsert(ptr, html_name_prefix);
				}
				if (ptrImg!=noImg && toc[i]->icon_text!=NULL)
				{	ptr= strstr(the_ref, "</a>");
					if (ptr!=NULL)
					{	strinsert(ptr, toc[i]->icon_text);
						strinsert(ptr, "<br>");
					}
				}
				voutlnf("%s%s%s", alignOn, the_ref, alignOff);
			}
		}
		else
		{	break;
		}
	}

	outln(rowOff);
	outln("</table>");
	outln(divOff);

}	/* html_node_bar_frames */


GLOBAL void html_headline ( void )
{
	char bgCmd[512];

	if (html_modern_layout)
	{
		bgCmd[0]= EOS;
		if (html_modern_backimage[0]!=EOS)
		{	sprintf(bgCmd, " background=\"%s\"", html_modern_backimage);
		}
		outln("<table border=\"0\" cellspacing=\"0\" cellpadding=\"0\" width=\"100%\">");
		outln("<tr>");
		if (html_modern_backcolor[0]!=EOS)
		{	voutlnf("<td valign=\"top\" width=\"%s\" bgcolor=\"%s\"%s>%s",
				html_modern_width, html_modern_backcolor, bgCmd,
				sHtmlPropfontStart);
		}
		else
		{	voutlnf("<td valign=\"top\" width=\"%s\"%s>%s", html_modern_width, bgCmd,
						sHtmlPropfontStart);
		}
		html_node_bar_modern();
		voutlnf("%s</td>", sHtmlPropfontEnd);
#if 0
		outln("<td valign=\"top\" width=\"8\">&nbsp;</td>");	/*r6pl3*/
#endif
		voutlnf("<td valign=\"top\" width=\"100%%\">%s", sHtmlPropfontStart);
	}

	if (!no_headlines)
	{	html_hb_line(TRUE);
	}

#if 1
	if (html_modern_layout || html_frames_layout)
	{
		outln("<table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" width=\"100%\"><tr>");
		voutlnf("<td valign=\"top\" width=\"8\">&nbsp;</td><td valign=\"top\" width=\"100%%\">%s", sHtmlPropfontStart);
	}
#endif
}	/* html_headline */


GLOBAL void html_bottomline ( void )
{
	if (html_modern_layout)
	{
		voutlnf("%s", sHtmlPropfontEnd);
		html_footer();
#if 1
		outln("</td></tr></table>");
#endif
		if (!no_bottomlines)
		{	html_hb_line(FALSE);
		}
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
		{	html_hb_line(FALSE);
		}
		return;
	}

	html_footer();
	if (!no_bottomlines)
	{	html_hb_line(FALSE);
	}

}	/* html_bottomline */



GLOBAL void html_footer ( void )
{
	BOOLEAN has_name, has_email, has_url, has_mailurl;
	BOOLEAN has_counter;
	char s[512];

	if (no_footers || toc[p2_toc_counter]->ignore_footer)
	{	return;
	}

	has_counter=	(toc[p2_toc_counter]->counter_command!=NULL);
	has_name=		(titdat.webmastername!=NULL);
	has_email=		(titdat.webmasteremail!=NULL);
	has_url=		(titdat.webmasterurl!=NULL);
	has_mailurl=	(titdat.webmastermailurl!=NULL);

	if (has_counter || has_name || has_email || has_url || has_mailurl)
	{	outln(HTML_HR);
	}

	/* r6pl4: Counterkommando ausgeben */
	if (has_counter)
	{
		outln(toc[p2_toc_counter]->counter_command);
	}

	if (footer_buffer[0]!=EOS)
	{	outln(footer_buffer);
		return;
	}
	

	if (!has_name && !has_email && !has_url && !has_mailurl)
	{	no_footers= TRUE;
		return;
	}

	sprintf(footer_buffer, "<address>%sCopyright &copy; ", sHtmlPropfontStart);

	s[0]= EOS;
	if (has_name)
	{
		if (has_url && (has_email || has_mailurl))
		{
			if (has_mailurl && has_email)
			{	sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"%s\">%s</a>)",
					titdat.webmasterurl, titdat.webmastername,
					titdat.webmastermailurl, titdat.webmasteremail);
			}
			else
			{
				if (has_mailurl)
				{	/* Keine sinvolle Ausgabe moeglich */
				}
				else
				{	sprintf(s, "<a href=\"%s\">%s</a> (<a href=\"mailto:%s\">%s</a>)",
						titdat.webmasterurl, titdat.webmastername,
						titdat.webmasteremail, titdat.webmasteremail);
				}
			}

		}

		if (has_url && !has_email && !has_mailurl)
		{	sprintf(s, "<a href=\"%s\">%s</a>",
				 titdat.webmasterurl, titdat.webmastername);
		}

		if (!has_url && (has_email || has_mailurl))
		{
			if (has_mailurl)
			{	sprintf(s, "<a href=\"%s\">%s</a>",
					titdat.webmastermailurl, titdat.webmastername);
			}
			else
			{	sprintf(s, "<a href=\"mailto:%s\">%s</a>",
					titdat.webmasteremail, titdat.webmastername);
			}
		}
		
		if (!has_url && !has_email && !has_mailurl)
		{	strcpy(s, titdat.webmastername);
		}
	}
	else
	{
		if (has_email || has_mailurl)
		{
			if (has_mailurl)
			{	sprintf(s, "<a href=\"%s\">%s</a>",
					titdat.webmastermailurl, titdat.webmasteremail);
			}
			else
			{	sprintf(s, "<a href=\"mailto:%s\">%s</a>",
					titdat.webmasteremail, titdat.webmasteremail);
			}
		}
		else
		{	if (has_url)
			{	sprintf(s, "<a href=\"%s\">%s</a>",
					titdat.webmasterurl, titdat.webmasterurl);
			}
		}
	}

	strcat(footer_buffer, s);
	strcat(footer_buffer, "<br> ");
    
	strcpy(s, lang.update);
	auto_quote_chars(s, TRUE);
	strcat(footer_buffer, s);
	strcat(footer_buffer, " ");
	strcat(footer_buffer, lang.today);
	strcat(footer_buffer, sHtmlPropfontEnd);
	strcat(footer_buffer, "</address>");

	outln(footer_buffer);

}	/* html_footer */



/*	############################################################
	#
	# Spezielles fuer HTML Help
	#
	############################################################	*/

GLOBAL void hh_headline ( void )
{
#if 0
	if (!no_headlines)
	{	html_hb_line(TRUE);
	}
#endif
}	/* hh_headline */


GLOBAL void hh_bottomline ( void )
{
#if 0
	if (!no_bottomlines)
	{	html_hb_line(FALSE);
	}
#endif
}	/* hh_bottomline */



LOCAL void print_htmlhelp_contents ( FILE *file, const char *indent, const int ti )
{
	char filename[512], tocname[512];

	if (ti>0)
	{
		get_html_filename(ti, filename);
		strcpy(tocname, toc[ti]->name);
	}
	else
	{
		strcpy(filename, old_outfile.name);
		tocname[0]= EOS;
		if (tocname[0]==EOS && titleprogram[0]!=EOS)	strcpy(tocname, titleprogram);
		if (tocname[0]==EOS && called_tableofcontents)	strcpy(tocname, lang.contents);
		if (tocname[0]==EOS && called_maketitle)		strcpy(tocname, lang.title);
	}
	del_html_styles(tocname);
	
	fprintf(file, "%s<LI> <OBJECT type=\"text/sitemap\">\n", indent);
	fprintf(file, "%s\t<param name=\"Name\" value=\"%s\">\n", indent, tocname);
	fprintf(file, "%s\t<param name=\"Local\" value=\"%s%s\">\n", indent, filename, outfile.suff);
	fprintf(file, "%s\t</OBJECT>\n", indent);

}	/* print_htmlhelp_contents */


GLOBAL BOOLEAN save_htmlhelp_contents ( const char* filename )
{
	FILE *file;

	register int i;
	BOOLEAN last_n= TRUE;
	BOOLEAN last_sn= FALSE;
	BOOLEAN last_ssn= FALSE;
	BOOLEAN last_sssn= FALSE;
	BOOLEAN inApx= FALSE;

	file= myFwopen(filename, FTHHC);

	if (!file)
	{	return FALSE;
	}

	save_upr_entry_outfile(filename);

	fprintf(file, "<!DOCTYPE HTML PUBLIC \"-//IETF//DTD HTML//EN\">\n");
	fprintf(file, "<HTML>\n");
	fprintf(file, "<HEAD>\n");
	fprintf(file, "<meta name=\"GENERATOR\" content=\"UDO Release %s.%s Patchlevel %s for %s\">\n",
						UDO_REL, UDO_SUBVER, UDO_PL, UDO_OS);
	fprintf(file, "<!-- Sitemap 1.0 -->\n");
	fprintf(file, "</HEAD><BODY>\n");
	fprintf(file, "<UL>\n");

	print_htmlhelp_contents(file, "\t", 0);	/* r6pl10: Eintrag fuer erste Seite */
	fprintf(file, "</UL>\n<UL>\n");

	for (i=1; i<=p1_toc_counter; i++)
	{
		if (toc[i]!=NULL && !toc[i]->invisible)
		{
			convert_toc_item(toc[i]);

			if ( !inApx && toc[i]->appendix)
			{	/* r6pl13: Anhang mit ausgeben, hier den ersten Node im Anhang */
				inApx= TRUE;
				if (last_n)		fprintf(file, "</UL>\n");
				if (last_sn)	fprintf(file, "\t</UL>\n</UL>\n");
				if (last_ssn)	fprintf(file, "\t\t</UL>\n\t</UL>\n</UL>\n");
				if (last_sssn)	fprintf(file, "\t\t\t</UL>\n\t\t</UL>\n\t</UL>\n</UL>\n");
				last_n= last_sn= last_ssn= last_sssn= FALSE;
#if 0
				fprintf(file, "<UL>\t<LI> <OBJECT type=\"text/sitemap\">\n");
				fprintf(file, "\t\t<param name=\"Name\" value=\"%s\">\n", lang.appendix);
				fprintf(file, "\t\t</OBJECT>\n");
#endif
				fprintf(file, "<UL>\n");
			}


			if ( toc[i]->n1 != 0 )
			{
				if ( toc[i]->toctype==TOC_NODE1 )
				{	/* Ein Kapitel */	

					if (last_sn)	{	fprintf(file, "\t</UL>\n");							last_sn= FALSE;		}
					if (last_ssn)	{	fprintf(file, "\t\t</UL>\n\t</UL>\n");				last_ssn= FALSE;	}
					if (last_sssn)	{	fprintf(file, "\t\t\t</UL>\n\t\t</UL>\n\t</UL>\n");	last_sssn= FALSE;	}
					last_n= TRUE;
					print_htmlhelp_contents(file, "\t", i);

				}/* TOC_NODE1 */
					
					
				if ( toc[i]->toctype==TOC_NODE2 )
				{	/* Ein Abschnitt */
					if (last_n)		{	fprintf(file, "\t<UL>\n");					last_n= FALSE;		}
					if (last_ssn)	{	fprintf(file, "\t\t</UL>\n");				last_ssn= FALSE;	}
					if (last_sssn)	{	fprintf(file, "\t\t\t</UL>\n\t\t</UL>\n");	last_sssn= FALSE;	}
					last_sn= TRUE;
					print_htmlhelp_contents(file, "\t\t", i);

				}/* TOC_NODE2 */
					
				if ( toc[i]->toctype==TOC_NODE3 )
				{	/* Ein Unterabschnitt */
					if (last_n)		{	fprintf(file, "<UL>\n\t<UL>\n");	last_n= FALSE;		}
					if (last_sn)	{	fprintf(file, "\t\t<UL>\n");		last_sn= FALSE;		}
					if (last_sssn)	{	fprintf(file, "\t\t\t</UL>\n");		last_sssn= FALSE;	}
					last_ssn= TRUE;
					print_htmlhelp_contents(file, "\t\t\t", i);

				}/* TOC_NODE3 */
					
					
				if ( toc[i]->toctype==TOC_NODE4 )
				{	/* Ein Paragraph */
					if (last_n)		{	fprintf(file, "\t<UL>\n\t\t<UL>\n\t\t\t<UL>\n");	last_n= FALSE;		}
					if (last_sn)	{	fprintf(file, "\t<UL>\n\t\t<UL>\n");				last_sn= FALSE;		}
					if (last_ssn)	{	fprintf(file, "\t\t\t<UL>\n");						last_ssn= FALSE;	}
					last_sssn= TRUE;
					print_htmlhelp_contents(file, "\t\t\t\t", i);

				}/* TOC_NODE4 */

			}/* toc[i]->n1 > 0 */

		}/* toc[i]!=NULL && !toc[i]->invisible */

	}/* for */


	if (last_sn)	fprintf(file, "\t</UL>\n</UL>\n");
	if (last_ssn)	fprintf(file, "\t\t</UL>\n\t</UL>\n");
	if (last_sssn)	fprintf(file, "\t\t\t</UL>\n\t\t</UL>\n\t</UL>\n");

#if 0
	if (inApx)		fprintf(file, "</UL>\n");
#endif

	fprintf(file, "</UL>\n");
	fprintf(file, "</BODY></HTML>\n");

	fclose(file);

	return TRUE;

}	/* save_htmlhelp_contents */


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


GLOBAL BOOLEAN save_htmlhelp_index ( const char* filename )
{
	FILE *file;
	size_t i;
	int j;
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
	fprintf(file, "<HTML>\n");
	fprintf(file, "<HEAD>\n");
	fprintf(file, "<meta name=\"GENERATOR\" content=\"UDO Release %s.%s Patchlevel %s for %s\">\n",
						UDO_REL, UDO_SUBVER, UDO_PL, UDO_OS);
	if (titdat.author != NULL)
		fprintf(file, "<meta name=\"Author\" content=\"%s\">\n", titdat.author);
	fprintf(file, "<!-- Sitemap 1.0 -->\n");
	fprintf(file, "</HEAD>\n");
	fprintf(file, "<BODY>\n");
	fprintf(file, "<UL>\n");

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
		get_html_filename(html_index[i].toc_index, htmlname);
		fprintf(file, "<LI> <OBJECT type=\"text/sitemap\"> <param name=\"Name\" value=\"%s\"> <param name=\"Local\" value=\"%s%s\"> </OBJECT> </LI>\n",
			html_index[i].tocname,
			htmlname, outfile.suff);
	}
	
	fprintf(file, "</UL>\n");
	fprintf(file, "</BODY>\n");
	fprintf(file, "</HTML>\n");
	fclose(file);
	
	um_free((void *) html_index);
	
	return TRUE;
}	/* save_htmlhelp_index */


/*	############################################################
	#
	# Kapitelkommandos
	#
	############################################################	*/
LOCAL void set_inside_node1 ( void )
{
	active_nodetype= TOC_NODE1;
}

LOCAL void make_node ( const BOOLEAN popup, const BOOLEAN invisible )
{
	char 	n[512], name[512], stgname[512], numbers[512], nameNoSty[512];
	char	map[64], sGifSize[80];
	int		ti, chapter, nr1;
	BOOLEAN	flag;
	BOOLEAN	do_index;

	if (p2_toc_counter>=MAXTOCS)	/* r5pl2 */
	{	bBreakInside= TRUE;
		return;
	}

	tokcpy2(name, 512);
	strcpy(stgname, name);	/* r5pl14 */

	if (name[0]==EOS)
	{	error_missing_parameter("!node");
		return;
	}

	p2_lab_counter++;		/*r6pl2*/
	p2_toctype= TOC_NODE1;	/*r6pl5*/
	
	if (desttype==TOHTM && !html_merge_node1)
	{	check_endnode();
		html_bottomline();
	}

	if (desttype==TOMHH)
	{	check_endnode();
		hh_bottomline();
	}

	check_styles(name);			/*r6pl3*/
	c_styles(name);
	switch (desttype)			/*r5pl3*/
	{	case TOWIN:
		case TOWH4:
		case TOAQV:	c_win_styles(name);	break;
		case TORTF:	c_rtf_styles(name);	c_rtf_quotes(name);	break;
		default:	c_internal_styles(name); break;
	}
	replace_udo_quotes(name);
	delete_all_divis(name);
	replace_udo_tilde(name);
	replace_udo_nbsp(name);


	check_endnode();
	check_styleflags();
	check_environments_node();

	if (bInsideAppendix)
	{	p2_apx_n1++;
		p2_apx_n2= 0;
		p2_apx_n3= 0;
		p2_apx_n4= 0;
	}
	else
	{	p2_toc_n1++;
		p2_toc_n2= 0;
		p2_toc_n3= 0;
		p2_toc_n4= 0;
	}

	p2_toc_counter++;
	curr_n1_index= p2_toc_counter;
	curr_n2_index= 0;
	curr_n3_index= 0;
	
	last_n1_index= p2_toc_counter;
	last_n2_index= 0;
	last_n3_index= 0;
	last_n4_index= 0;

	nr1= toc[p2_toc_counter]->nr1;
	(bInsideAppendix) ? (chapter= nr1) : (chapter= nr1+toc_offset);

	n[0]= EOS;
	numbers[0]= EOS;

	if (!invisible)
	{	if (bInsideAppendix)
		{	sprintf(numbers, "%c", 'A'+ nr1 - 1);
		}
		else
		{	sprintf(numbers, "%d", chapter);	/* r5pl7: chapter statt nr1 */
		}
	}

	if (bVerbose)
	{	sprintf(sInfMsg, "[%s] ", numbers);
		show_status_node(sInfMsg);
	}
	
	if (no_numbers || invisible)
	{	numbers[0]= EOS;
	}
	else
	{	strcat(numbers, " ");
	}
	
	strcpy(current_chapter_name, name);
	strcpy(current_chapter_nr, numbers);
	
	do_index= (use_nodes_inside_index && !no_index &&
					!toc[p2_toc_counter]->ignore_index);	/* r5pl10 */
	
	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
			set_inside_node1();
			if (invisible)
			{	(use_style_book)	? voutlnf("\n\\chapter*{%s}", name)
									: voutlnf("\n\\section*{%s}", name);
			}
			else
			{	(use_style_book)	? voutlnf("\n\\chapter{%s}", name)
									: voutlnf("\n\\section{%s}", name);
			}
			label2tex(name);				/*r6pl2*/
			voutlnf("\\label{%s}", name);	/*r6pl2*/
			output_aliasses();

			if (desttype==TOPDL)	/*r6pl8*/
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
			{	(use_style_book)	? outln("Chapter")
									: outln("Section*");
			}
			else
			{	(use_style_book)	? outln("Chapter")
									: outln("Section");
			}
			indent2space(name);
			outln(name);
			break;
			
		case TOINF:
			set_inside_node1();
			output_texinfo_node(name);
			if (bInsideAppendix)
			{	voutlnf("@appendix %s", name);
			}
			else
			{	(invisible) ? 	(voutlnf("@chapheading %s", name))
							:	(voutlnf("@chapter %s", name));
			}
			break;

		case TOTVH:
			set_inside_node1();
			if (numbers[0]!=EOS) strcat(numbers, " ");
			output_vision_header(numbers, name);
			break;

		case TOSTG:
			set_inside_node1();
			bInsidePopup= popup;

			replace_2at_by_1at(name);

			node2stg(name);

			outln("");
			if ( !do_index )
			{	outln("@indexoff");
			}
			if (popup)
			{	voutlnf("@pnode \"%s\"", name);
			}
			else
			{	voutlnf("@node \"%s\"", name);
			}
			if ( !do_index )
			{	outln("@indexon");
			}

			if (!popup)
			{	if (called_tableofcontents)
				{	outln("@toc \"Main\"");
				}
			}
			stg_header(numbers, stgname, popup);
			break;

		case TOAMG:
			set_inside_node1();

			replace_2at_by_1at(name);

			node2stg(name);

			outln("");
			if (titleprogram[0]!=EOS)
			{	voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
			}
			else
			{	voutlnf("@node \"%s\" \"%s\"", name, name);
			}

			if (called_tableofcontents)
			{	outln("@toc \"Main\"");
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
			{	(bInsideAppendix)	?	sprintf(n, "%s %s", lang.appendix, numbers)
									:	sprintf(n, "%s %s", lang.chapter, numbers);
				del_right_spaces(n);
				output_ascii_line("=", zDocParwidth);
				outln(n);
				outln("");
				outln(name);
				output_ascii_line("=", zDocParwidth);
			}
			else
			{	if (numbers[0]!=EOS) strcat(numbers, " ");
				sprintf(n, "%s%s", numbers, name);
				outln(n);
				output_ascii_line("*", strlen(n));
			}
			outln("");
			break;

		case TOKPS:
			set_inside_node1();

			if (use_style_book)
			{	(bInsideAppendix)	?	sprintf(n, "%s %s", lang.appendix, numbers)
									:	sprintf(n, "%s %s", lang.chapter, numbers);
				del_right_spaces(n);
				if (n[0]!=EOS) strcat(n, " ");
				strcat(n, name);
				outln("25 changeFontSize");
			}
			else
			{	if (numbers[0]!=EOS) strcat(numbers, " ");
				sprintf(n, "%s%s", numbers, name);
				/* Changed in r6pl16 [NHz] */
				/* Nodesize ist set on discrete value */
				voutlnf("%d changeFontSize", laydat.node1size);
			}
			node2postscript(name, KPS_NAMEDEST); /* Changed in r6pl16 [NHz] */
			voutlnf("/NodeName (%s %.*s) def", lang.chapter, (int)(75L-strlen(titdat.author)), n); /* Changed in r6pl16 [NHz] */
			outln("newline");
			voutlnf("/%s NameDest", name); /* New in r6pl15 [NHz] */
			outln("Bon");
			voutlnf("(%s) udoshow", n);
			outln("Boff");
			outln("newline");
			voutlnf("%d changeFontSize", laydat.propfontsize); /* Changed in r6pl15 [NHz] */
			break;

		case TODRC:
			set_inside_node1();
			outln("%%*");
			if (p2_toc_counter+1<=p1_toc_counter && toc[p2_toc_counter+1]->toctype==TOC_NODE2)
			{	voutlnf("%%%% 0, %d, 0, 0, %d, %s", p2_toc_counter+10, iDrcFlags, name);
			}
			else
			{	voutlnf("%%%% 0, 0, 0, 0, %d, %s", iDrcFlags, name);
			}
			outln("%%*");
			outln("");
			break;

		case TOIPF:
			set_inside_node1();
			node2NrIPF(n, toc[p2_toc_counter]->labindex);	/* r6pl2 */
			map[0]= EOS;
			if (toc[p2_toc_counter]->mapping>=0)
			{	sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
			}
			if (bInsideAppendix)
			{	voutlnf(":h1 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
			}
			else
			{	voutlnf(":h1 id=%s%s.%s%s", n, map, numbers, name);
			}
			break;
    		
		case TOSRC:
		case TOSRP:
			set_inside_node1();
			outln("");
			outln("");
			memset(n, '#', 62); n[62]= EOS;
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
			{	c_newpage();
			}
		
			outln(rtf_pardpar);
			
			/* r6pl6: Indizes fuer RTF */
			if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
			{	strcpy(n, name);
				winspecials2ascii(n);
				voutf("{\\xe\\v %s}", n);
			}

			output_aliasses();

			if (use_style_book)
			{	if (bInsideAppendix)
				{	if (invisible)
					{	voutlnf("%s\\fs%d %s %s\\par %s\\fs%d %s\\par\\pard", rtf_inv_chapt, iDocPropfontSize + 28, lang.appendix, numbers, rtf_inv_chapt, iDocPropfontSize + 28, name);
					}
					else
					{	voutlnf("%s\\fs%d %s %s\\par %s\\fs%d %s\\par\\pard", rtf_inv_chapt, iDocPropfontSize + 28, lang.appendix, numbers, rtf_chapt, iDocPropfontSize + 28, name);
					}
				}
				else
				{	if (invisible)
					{	voutlnf("%s\\fs%d %s %s\\par %s\\fs%d %s\\par\\pard", rtf_inv_chapt, iDocPropfontSize + 28, lang.chapter, numbers, rtf_inv_chapt, iDocPropfontSize + 28, name);
					}
					else
					{	voutlnf("%s\\fs%d %s %s\\par %s\\fs%d %s\\par\\pard", rtf_inv_chapt, iDocPropfontSize + 28, lang.chapter, numbers, rtf_chapt, iDocPropfontSize + 28, name);
					}
				}
			}
			else
			{
				if (numbers[0]==EOS)
				{	if (invisible)
					{	/* Changed in r6pl16 [NHz] */
						/* Nodesize ist set on discrete value */
						voutlnf("%s %s\\fs%d %s%s", rtf_plain, rtf_inv_node1, laydat.node1size, name, rtf_parpard);
					}
					else
					{	/* Changed in r6pl16 [NHz] */
						/* Nodesize ist set on discrete value */
						voutlnf("%s %s\\fs%d %s%s", rtf_plain, rtf_node1, laydat.node1size, name, rtf_parpard);
					}
				}
				else
				{	if (invisible)
					{	/* Changed in r6pl16 [NHz] */
						/* Nodesize ist set on discrete value */
						voutlnf("%s %s\\fs%d %s  %s%s", rtf_plain, rtf_inv_node1, laydat.node1size, numbers, name, rtf_parpard);
					}
					else
					{	/* Changed in r6pl16 [NHz] */
						/* Nodesize ist set on discrete value */
						voutlnf("%s %s\\fs%d %s  %s%s", rtf_plain, rtf_node1, laydat.node1size, numbers, name, rtf_parpard);
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
			{	(bInsideAppendix)	?	sprintf(n, "%s %s\\par %s", lang.appendix, numbers, name)
									:	sprintf(n, "%s %s\\par %s", lang.chapter, numbers, name);
			}
			else
			{	if (numbers[0]!=EOS) strcat(numbers, "\\~\\~");
				sprintf(n, "%s%s", numbers, name);
			}
			win_headline(n, popup);
			break;

		case TOPCH:
			set_inside_node1();
			if (numbers[0]!=EOS) strcat(numbers, " ");
			output_pch_header(numbers, name);
			break;

		case TOHTM:
		case TOMHH:
			ti= p2_toc_counter;

			if (!html_merge_node1)
			{	if (!html_new_file()) return;
			}
			else
			{	output_aliasses();
				outln(HTML_HR);		/* r5pl6 */
			}
			set_inside_node1();
			flag= FALSE;

			do_toptoc(TOC_NODE1);	/*r6pl5*/

			if (use_chapter_images)
			{	
				if (ti>=0 && toc[ti]->image!=NULL)
				{	sGifSize[0]= EOS;
					if (toc[ti]->uiImageWidth!=0 && toc[ti]->uiImageHeight!=0)
					{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"",
							toc[ti]->uiImageWidth, toc[ti]->uiImageHeight);
					}
					voutlnf("<h%d><p align=\"center\">", html_nodesize);	/* r5pl4 */
					voutlnf("<img src=\"%s%s\" alt=\"%s%s\"%s>",
						toc[ti]->image, sDocImgSuffix, numbers, name, sGifSize);
					voutlnf("</p></h%d>", html_nodesize);				/* r5pl4 */
					flag= TRUE;
				}
			}

			if (!flag && !toc[ti]->ignore_title)
			{	
				strcpy(nameNoSty, name);
				del_html_styles(nameNoSty);
				label2html(nameNoSty);	/*r6pl2*/
				voutlnf("<h%d><a name=\"%s\">%s%s</a></h%d>",
							html_nodesize, nameNoSty, numbers, name, html_nodesize);	/* r5pl4 */
			}
			break;

		case TOLDS:
			set_inside_node1();
			(use_style_book)	?	voutlnf("<chapter>%s<label id=\"%s\">", name, name)
								:	voutlnf("<sect>%s<label id=\"%s\">", name, name);
			output_aliasses();	/* r5pl8 */
			outln("<p>");
			break;

		case TOHPH:
			set_inside_node1();
			(use_style_book)	?	voutlnf("<chapter>%s", name)
								:	voutlnf("<s1>%s", name);
			output_aliasses();
			break;
	}

	about_unregistered();

}	/*make_node*/


/* r5pl15: Texinfo kennt keine versteckten Kapitel, daher wird bei den	*/
/* node_iv-Funktionen als Invisible-Flag statt TRUE der Wert von		*/
/* (desttype!=TOINF) benutzt. Kurz und elegant, nicht?					*/

GLOBAL void c_node ( void )
{	make_node (FALSE, FALSE);
}	/* c_node */

GLOBAL void c_node_iv ( void )
{	make_node (FALSE, (desttype!=TOINF));	/* r5pl15 */
}	/* c_node */

GLOBAL void c_pnode ( void )
{	make_node (TRUE, FALSE);
}	/* c_pnode */

GLOBAL void c_pnode_iv ( void )
{	make_node (TRUE, (desttype!=TOINF));	/* r5pl15 */
}	/* c_pnode */




LOCAL void set_inside_node2 ( void )
{
	active_nodetype= TOC_NODE2;
}

LOCAL void make_subnode ( const BOOLEAN popup, const BOOLEAN invisible )
{
	char 	n[512], name[512], stgname[512], hx_start[16], hx_end[16], sTemp[512];
	char	numbers[512], nameNoSty[512];
	char	map[64], sGifSize[80];
	int		ti, ui, chapter, nr1, nr2;
	BOOLEAN	flag;
	BOOLEAN do_index;
	
	if (p2_toc_counter>=MAXTOCS)	/* r5pl2 */
	{	bBreakInside= TRUE;
		return;
	}

	tokcpy2(name, 512);
	strcpy(stgname, name);

	if (name[0]==EOS)
	{	error_missing_parameter("!subnode");
		return;
	}
	
	p2_lab_counter++;		/*r6pl2*/
	p2_toctype= TOC_NODE2;	/*r6pl5*/

	if (desttype==TOHTM && !html_merge_node2)
	{	check_endnode();
		html_bottomline();
	}

	if (desttype==TOMHH)
	{	check_endnode();
		hh_bottomline();
	}

	check_styles(name);			/*r6pl3*/
	c_styles(name);
	switch (desttype)			/* r5pl3 */
	{	case TOWIN:
		case TOWH4:
		case TOAQV:	c_win_styles(name);	break;
		case TORTF:	c_rtf_styles(name);	c_rtf_quotes(name);	break;
		default:	c_internal_styles(name); break;
	}
	replace_udo_quotes(name);
	delete_all_divis(name);
	replace_udo_tilde(name);
	replace_udo_nbsp(name);

	check_endnode();	
	check_styleflags();
	check_environments_node();

	if (bInsideAppendix)
	{	p2_apx_n2++;
		p2_apx_n3= 0;
		p2_apx_n4= 0;
	}
	else
	{	p2_toc_n2++;
		p2_toc_n3= 0;
		p2_toc_n4= 0;
	}
	
	p2_toc_counter++;
	curr_n2_index= p2_toc_counter;
	curr_n3_index= 0;

	last_n2_index= p2_toc_counter;
	last_n3_index= 0;
	last_n4_index= 0;

	nr1= toc[p2_toc_counter]->nr1;
	nr2= toc[p2_toc_counter]->nr2;
	(bInsideAppendix) ? (chapter= nr1) : (chapter= nr1+toc_offset);

	n[0]= EOS;
	numbers[0]= EOS;

	if (!invisible)
	{	if (bInsideAppendix)
		{	sprintf(numbers, "%c.%d", 'A'+nr1-1, nr2+subtoc_offset);
		}
		else
		{	sprintf(numbers, "%d.%d", chapter, nr2+subtoc_offset);
		}
	}
	
	if (bVerbose)
	{	sprintf(sInfMsg, "[%s] ", numbers);
		show_status_node(sInfMsg);
	}
	
	if (no_numbers || invisible)
	{	numbers[0]= EOS;
	}
	else
	{	strcat(numbers, " ");
	}

	strcpy(current_chapter_name, name);
	strcpy(current_chapter_nr, numbers);

	do_index= (use_nodes_inside_index && !no_index &&
					!toc[p2_toc_counter]->ignore_index);	/* r5pl10 */

	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
			set_inside_node2();
			if (invisible)
			{	(use_style_book)	? voutlnf("\n\\section*{%s}", name)
									: voutlnf("\n\\subsection*{%s}", name );
			}
			else
			{	(use_style_book)	? voutlnf("\n\\section{%s}", name)
									: voutlnf("\n\\subsection{%s}", name);
			}
			label2tex(name);				/*r6pl2*/
			voutlnf("\\label{%s}", name);	/*r6pl2*/
			output_aliasses();
			if (desttype==TOPDL)	/*r6pl8*/
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
			{	(use_style_book)	? outln("Section*")
									: outln("Subsection*");
			}
			else
			{	(use_style_book)	? outln("Section")
									: outln("Subsection");
			}
			indent2space(name);
			outln(name);
			break;
		case TOINF:
			set_inside_node2();
			output_texinfo_node(name);
			if (bInsideAppendix)
			{	voutlnf("@appendixsec %s", name);
			}
			else
			{	(invisible) ? 	(voutlnf("@heading %s", name))
							:	(voutlnf("@section %s", name));
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
			if ( !do_index )
			{	outln("@indexoff");
			}
			if (popup)
			{	voutlnf("@pnode \"%s\"", name);
			}
			else
			{	voutlnf("@node \"%s\"", name);
			}
			if ( !do_index )
			{	outln("@indexon");
			}

			/* r5pl6: up_n1_index wird statt der alten Abfrage benutzt */
			if (!popup)
			{	ui= toc[p2_toc_counter]->up_n1_index;
				if (ui>0)
				{	strcpy(sTemp, toc[ui]->name);
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
			{	voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
			}
			else
			{	voutlnf("@node \"%s\" \"%s\"", name, name);
			}

			/* r5pl6: up_n1_index wird statt der alten Abfrage benutzt */
			ui= toc[p2_toc_counter]->up_n1_index;
			if (ui>0)
			{	strcpy(sTemp, toc[ui]->name);
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
			node2NrIPF(n, toc[p2_toc_counter]->labindex);	/* r6pl2 */
			map[0]= EOS;
			if (toc[p2_toc_counter]->mapping>=0)
			{	sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
			}
			if (bInsideAppendix)
			{	voutlnf(":h2 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
			}
			else
			{	voutlnf(":h2 id=%s%s.%s%s", n, map, numbers, name);
			}
			break;
    		

		case TOKPS:
			set_inside_node2();

			if (use_style_book)
			{	(bInsideAppendix)	?	sprintf(n, "%s %s", lang.appendix, numbers)
									:	sprintf(n, "%s %s", lang.chapter, numbers);
				del_right_spaces(n);
				if (n[0]!=EOS) strcat(n, " ");
				strcat(n, name);
				outln("18 changeFontSize");
			}
			else
			{	if (numbers[0]!=EOS) strcat(numbers, " ");
				sprintf(n, "%s%s", numbers, name);
				/* Changed in r6pl16 [NHz] */
				voutlnf("%d changeFontSize", laydat.node2size);
			}
			outln("newline");
			node2postscript(name, KPS_NAMEDEST); /* Changed in r6pl16 [NHz] */
			voutlnf("/%s NameDest", name); /* New in r6pl15 [NHz] */
			outln("Bon");
			voutlnf("(%s) udoshow", n);
			outln("Boff");
			outln("newline");
			voutlnf("%d changeFontSize", laydat.propfontsize); /* Changed in r6pl15 [NHz] */
			break;

		case TODRC:
			set_inside_node2();
			outln("%%*");
			if (p2_toc_counter+1<=p1_toc_counter && toc[p2_toc_counter+1]->toctype==TOC_NODE3)
			{	voutlnf("%%%% %d, %d, 0, 0, %d, %s", last_n1_index+10, p2_toc_counter+100, iDrcFlags, name);
			}
			else
			{	voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n1_index+10, iDrcFlags, name);
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

			/* r6pl6: Indizes fÅr RTF */
			if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
			{	strcpy(n, name);
				winspecials2ascii(n);
				voutf("{\\xe\\v %s}", n);
			}

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
				{	/* Changed in r6pl16 [NHz] */
					/* Nodesize ist set on discrete value */
					sprintf(n, "%s\\fs%d", rtf_inv_node2, laydat.node2size);
				}
				else
				{	/* Changed in r6pl16 [NHz] */
					/* Nodesize ist set on discrete value */
					sprintf(n, "%s\\fs%d", rtf_node2, laydat.node2size);
				}
			}

			if (numbers[0]==EOS)
			{	voutlnf("%s %s %s%s", rtf_plain, n, name, rtf_parpard);
			}
			else
			{	voutlnf("%s %s %s  %s%s", rtf_plain, n, numbers, name, rtf_parpard);
			}
			voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);	/* r5pl6 */
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

		case TOHTM:
		case TOMHH:
			ti= p2_toc_counter;

			if (!html_merge_node2)
			{	if (!html_new_file()) return;
				if (!toc[ti]->ignore_title)
				{	sprintf(hx_start, "<h%d>", html_nodesize);
					sprintf(hx_end, "</h%d>", html_nodesize);
				}
			}
			else
			{	if (!toc[ti]->ignore_title)
				{	sprintf(hx_start, "<h%d>", html_nodesize+1);
					sprintf(hx_end, "</h%d>", html_nodesize+1);
				}
				output_aliasses();
			}
			set_inside_node2();
			flag= FALSE;

			
			do_toptoc(TOC_NODE2);	/*r6pl5*/

			if (use_chapter_images)
			{	ti= p2_toc_counter;
				if (ti>=0 && toc[ti]->image!=NULL)
				{	sGifSize[0]= EOS;
					if (toc[ti]->uiImageWidth!=0 && toc[ti]->uiImageHeight!=0)
					{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"",
							toc[ti]->uiImageWidth, toc[ti]->uiImageHeight);
					}
					voutlnf("%s<p align=\"center\">", hx_start);
					voutlnf("<img src=\"%s%s\" alt=\"%s%s\"%s>",
						toc[ti]->image, sDocImgSuffix, numbers, name, sGifSize);
					voutlnf("</p>%s", hx_end);
					flag= TRUE;
				}
			}

			if (!flag)
			{	strcpy(nameNoSty, name);
				del_html_styles(nameNoSty);
				label2html(nameNoSty);	/*r6pl2*/
				voutlnf("%s<a name=\"%s\">%s%s</a>%s",
					hx_start, nameNoSty, numbers, name, hx_end);
			}
			break;

		case TOLDS:
			(use_style_book)	?	voutlnf("<sect>%s<label id=\"%s\">", name, name)
								:	voutlnf("<sect1>%s<label id=\"%s\">", name, name);
			output_aliasses();	/* r5pl8 */
			outln("<p>");
			break;

		case TOHPH:
			set_inside_node2();
			(use_style_book)	?	voutlnf("<s1>%s", name)
								:	voutlnf("<s2>%s", name);
			output_aliasses();
			break;
	}

	about_unregistered();

}	/*make_subnode*/


GLOBAL void c_subnode ( void )
{	make_subnode (FALSE, FALSE);
}	/* c_subnode */

GLOBAL void c_subnode_iv ( void )
{	make_subnode (FALSE, (desttype!=TOINF));	/* r5pl15 */
}	/* c_subnode */

GLOBAL void c_psubnode ( void )
{	make_subnode (TRUE, FALSE);
}	/* c_psubnode */

GLOBAL void c_psubnode_iv ( void )
{	make_subnode (TRUE, (desttype!=TOINF));	/* r5pl15 */
}	/* c_psubnode */


LOCAL void set_inside_node3 ( void )
{
	active_nodetype= TOC_NODE3;
}

LOCAL void make_subsubnode( const BOOLEAN popup, const BOOLEAN invisible )
{
	char 	n[512], name[512], stgname[512], hx_start[16], hx_end[16], sTemp[512];
	char	numbers[512], nameNoSty[512];
	char	map[64], sGifSize[80];
	int		ti, ui, chapter, nr1, nr2, nr3;
	BOOLEAN	flag;
	BOOLEAN	do_index;
	
	if (p2_toc_counter>=MAXTOCS)	/* r5pl2 */
	{	bBreakInside= TRUE;
		return;
	}

	tokcpy2(name, 512);
	strcpy(stgname, name);	/* r5pl14 */

	if (name[0]==EOS)
	{	error_missing_parameter("!subsubnode");
		return;
	}
	
	p2_lab_counter++;		/*r6pl2*/
	p2_toctype= TOC_NODE3;	/*r6pl5*/

	if (desttype==TOHTM && !html_merge_node3)
	{	check_endnode();
		html_bottomline();
	}

	if (desttype==TOMHH)
	{	check_endnode();
		hh_bottomline();
	}

	check_styles(name);			/*r6pl3*/
	c_styles(name);
	switch (desttype)			/* r5pl3 */
	{	case TOWIN:
		case TOWH4:
		case TOAQV:	c_win_styles(name);	break;
		case TORTF:	c_rtf_styles(name);	c_rtf_quotes(name);	break;
		default:	c_internal_styles(name); break;
	}
	replace_udo_quotes(name);
	delete_all_divis(name);
	replace_udo_tilde(name);
	replace_udo_nbsp(name);

	check_endnode();
	check_styleflags();
	check_environments_node();

	if (bInsideAppendix)
	{	p2_apx_n3++;
		p2_apx_n4= 0;
	}
	else
	{	p2_toc_n3++;
		p2_toc_n4= 0;
	}
	
	p2_toc_counter++;
	curr_n3_index= p2_toc_counter;

	last_n3_index= p2_toc_counter;
	last_n4_index= 0;

	nr1= toc[p2_toc_counter]->nr1;
	nr2= toc[p2_toc_counter]->nr2;
	nr3= toc[p2_toc_counter]->nr3;
	(bInsideAppendix) ? (chapter= nr1) : (chapter= nr1+toc_offset);

	n[0]= EOS;
	numbers[0]= EOS;

	if (!invisible)
	{	if (bInsideAppendix)
	{	sprintf(numbers, "%c.%d.%d", 'A'+nr1-1, nr2+subtoc_offset, nr3+subsubtoc_offset);
		}
		else
		{	sprintf(numbers, "%d.%d.%d", chapter, nr2+subtoc_offset, nr3+subsubtoc_offset);
		}
	}
	
	if (bVerbose)
	{	sprintf(sInfMsg, "[%s] ", numbers);
		show_status_node(sInfMsg);
	}

	if (no_numbers || invisible)
	{	numbers[0]= EOS;
	}
	else
	{	strcat(numbers, " ");
	}

	strcpy(current_chapter_name, name);
	strcpy(current_chapter_nr, numbers);

	do_index= (use_nodes_inside_index && !no_index &&
					!toc[p2_toc_counter]->ignore_index);	/* r5pl10 */

	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
			set_inside_node3();
			if (invisible)
			{	(use_style_book)	? voutlnf("\n\\subsection*{%s}", name)
									: voutlnf("\n\\subsubsection*{%s}", name);
			}
			else
			{	(use_style_book)	? voutlnf("\n\\subsection{%s}", name)
									: voutlnf("\n\\subsubsection{%s}", name);
			}
			label2tex(name);				/*r6pl2*/
			voutlnf("\\label{%s}", name);	/*r6pl2*/
			if (desttype==TOPDL)	/*r6pl8*/
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
			{	(use_style_book)	? outln("Subsection*")
									: outln("Subsubsection*");
			}
			else
			{	(use_style_book)	? outln("Subsection")
									: outln("Subsubsection");
			}
			indent2space(name);
			outln(name);
			break;
		case TOINF:
			set_inside_node3();
			output_texinfo_node(name);
			if (bInsideAppendix)
			{	voutlnf("@appendixsubsec %s", name);
			}
			else
			{	(invisible) ? 	(voutlnf("@subheading %s", name))
							:	(voutlnf("@subsection %s", name));
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
			if ( !do_index )
			{	outln("@indexoff");
			}
			if (popup)
			{	voutlnf("@pnode \"%s\"", name);
			}
			else
			{	voutlnf("@node \"%s\"", name);
			}
			if ( !do_index )
			{	outln("@indexon");
			}
			
			/* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
			if (!popup)
			{	ui= toc[p2_toc_counter]->up_n2_index;
				if (ui>0)
				{	strcpy(sTemp, toc[ui]->name);
					node2stg(sTemp);
					replace_2at_by_1at(sTemp);
					voutlnf("@toc \"%s\"", sTemp);
				}
			}
			stg_header(numbers, stgname, popup);	/* r5pl14: stgname statt "" */
			break;

		case TOAMG:
			set_inside_node3();
			replace_2at_by_1at(name);
			node2stg(name);

			outln("");
			if (titleprogram[0]!=EOS)
			{	voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
			}
			else
			{	voutlnf("@node \"%s\" \"%s\"", name, name);
			}
			
			/* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
			ui= toc[p2_toc_counter]->up_n2_index;
			if (ui>0)
			{	strcpy(sTemp, toc[ui]->name);
				node2stg(sTemp);
				replace_2at_by_1at(sTemp);
				voutlnf("@toc \"%s\"", sTemp);
			}
			stg_header(numbers, stgname, FALSE);	/* r5pl14: stgname statt "" */
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
			node2NrIPF(n, toc[p2_toc_counter]->labindex);	/* r6pl2 */
			map[0]= EOS;
			if (toc[p2_toc_counter]->mapping>=0)
			{	sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
			}
			if (bInsideAppendix)
			{	voutlnf(":h3 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
			}
			else
			{	voutlnf(":h3 id=%s%s.%s%s", n, map, numbers, name);
			}
			break;
    		

		case TOKPS:
			set_inside_node3();

			if (use_style_book)
			{	(bInsideAppendix)	?	sprintf(n, "%s %s", lang.appendix, numbers)
									:	sprintf(n, "%s %s", lang.chapter, numbers);
				del_right_spaces(n);
				if (n[0]!=EOS) strcat(n, " ");
				strcat(n, name);
				outln("14 changeFontSize");
			}
			else
			{	if (numbers[0]!=EOS) strcat(numbers, " ");
				sprintf(n, "%s%s", numbers, name);
				/* Changed in r6pl16 [NHz] */
				voutlnf("%d changeFontSize", laydat.node3size);
			}
			outln("newline");
			node2postscript(name, KPS_NAMEDEST); /* Changed in r6pl16 [NHz] */
			voutlnf("/%s NameDest", name); /* New in r6pl15 [NHz] */
			outln("Bon");
			voutlnf("(%s) udoshow", n);
			outln("Boff");
			outln("newline");
			voutlnf("%d changeFontSize", laydat.propfontsize); /* Changed in r6pl15 [NHz] */
			break;

		case TODRC:
			set_inside_node3();
			outln("%%*");
			if (p2_toc_counter+1<=p1_toc_counter && toc[p2_toc_counter+1]->toctype==TOC_NODE4)
			{	voutlnf("%%%% %d, %d, 0, 0, %d, %s", last_n2_index+100, p2_toc_counter+1000, iDrcFlags, name);
			}
			else
			{	voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n2_index+100, iDrcFlags, name);
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

			/* r6pl6: Indizes fÅr RTF */
			if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
			{	strcpy(n, name);
				winspecials2ascii(n);
				voutf("{\\xe\\v %s}", n);
			}

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
				{	/* Changed in r6pl16 [NHz] */
					/* Nodesize ist set on discrete value */
					sprintf(n, "%s\\fs%d", rtf_inv_node3, laydat.node3size);
				}
				else
				{	/* Changed in r6pl16 [NHz] */
					/* Nodesize ist set on discrete value */
					sprintf(n, "%s\\fs%d", rtf_node3, laydat.node3size);
				}
			}
			if (numbers[0]==EOS)
			{	voutlnf("%s %s %s%s", rtf_plain, n, name, rtf_parpard);
			}
			else
			{	voutlnf("%s %s %s  %s%s", rtf_plain, n, numbers, name, rtf_parpard);
			}

			voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);	/* r5pl6 */
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

		case TOHTM:
		case TOMHH:
			ti= p2_toc_counter;

			if (!html_merge_node3)
			{	if (!html_new_file()) return;
				if (!toc[ti]->ignore_title)
				{	sprintf(hx_start, "<h%d>", html_nodesize);
					sprintf(hx_end, "</h%d>", html_nodesize);
				}
			}
			else
			{	if (!toc[ti]->ignore_title)
				{	sprintf(hx_start, "<h%d>", html_nodesize+2);
					sprintf(hx_end, "</h%d>", html_nodesize+2);
				}
				output_aliasses();
			}

			set_inside_node3();
			flag= FALSE;
						
			if (use_chapter_images)
			{
				ti= p2_toc_counter;
				if (ti>=0 && toc[ti]->image!=NULL)
				{	sGifSize[0]= EOS;
					if (toc[ti]->uiImageWidth!=0 && toc[ti]->uiImageHeight!=0)
					{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"",
							toc[ti]->uiImageWidth, toc[ti]->uiImageHeight);
					}
					voutlnf("%s<p align=\"center\">", hx_start);
					voutlnf("<img src=\"%s%s\" alt=\"%s%s\"%s>",
						toc[ti]->image, sDocImgSuffix, numbers, name, sGifSize);
					voutlnf("</p>%s", hx_end);
					flag= TRUE;
				}
			}

			do_toptoc(TOC_NODE3);	/*r6pl5*/

			if (!flag)
			{
				strcpy(nameNoSty, name);
				del_html_styles(nameNoSty);
				label2html(nameNoSty);	/*r6pl2*/
				voutlnf("%s<a name=\"%s\">%s%s</a>%s",
					hx_start, nameNoSty, numbers, name, hx_end);
			}
			break;

		case TOLDS:
			set_inside_node3();
			(use_style_book)	?	voutlnf("<sect1>%s<label id=\"%s\">", name, name)
								:	voutlnf("<sect2>%s<label id=\"%s\">", name, name);
			output_aliasses();	/* r5pl8 */
			outln("<p>");
			break;

		case TOHPH:
			set_inside_node3();
			(use_style_book)	?	voutlnf("<s2>%s", name)
								:	voutlnf("<s3>%s", name);
			output_aliasses();
			break;
	}

	about_unregistered();

}	/*make_subsubnode*/


GLOBAL void c_subsubnode ( void )
{	make_subsubnode (FALSE, FALSE);
}	/* c_subsubnode */

GLOBAL void c_subsubnode_iv ( void )
{	make_subsubnode (FALSE, (desttype!=TOINF));	/* r5pl15 */
}	/* c_subsubnode */

GLOBAL void c_psubsubnode ( void )
{	make_subsubnode (TRUE, FALSE);
}	/* c_psubsubnode */

GLOBAL void c_psubsubnode_iv ( void )
{	make_subsubnode (TRUE, (desttype!=TOINF));	/* r5pl15 */
}	/* c_psubsubnode */


LOCAL void set_inside_node4 ( void )
{
	active_nodetype= TOC_NODE4;
}

LOCAL void make_subsubsubnode( const BOOLEAN popup, const BOOLEAN invisible )
{
	char 	n[512], name[512], stgname[512], hx_start[16], hx_end[16], sTemp[512];
	char	numbers[512], nameNoSty[512];
	char	map[64], sGifSize[80];
	int		ti, ui, chapter, nr1, nr2, nr3, nr4;
	BOOLEAN	flag;
	BOOLEAN	do_index;
	
	if (p2_toc_counter>=MAXTOCS)	/* r5pl2 */
	{	bBreakInside= TRUE;
		return;
	}

	tokcpy2(name, 512);
	strcpy(stgname, name);	/* r5pl14 */

	if (name[0]==EOS)
	{	error_missing_parameter("!subsubsubnode");
		return;
	}
	
	p2_lab_counter++;		/*r6pl2*/
	p2_toctype= TOC_NODE4;	/*r6pl5*/

	if (desttype==TOHTM && !html_merge_node4)
	{	check_endnode();
		html_bottomline();
	}

	if (desttype==TOMHH)
	{	check_endnode();
		hh_bottomline();
	}

	check_styles(name);			/*r6pl3*/
	c_styles(name);
	switch (desttype)			/* r5pl3 */
	{	case TOWIN:
		case TOWH4:
		case TOAQV:	c_win_styles(name);	break;
		case TORTF:	c_rtf_styles(name);	c_rtf_quotes(name);	break;
		default:	c_internal_styles(name); break;
	}
	replace_udo_quotes(name);
	delete_all_divis(name);
	replace_udo_tilde(name);
	replace_udo_nbsp(name);

	check_endnode();
	check_styleflags();
	check_environments_node();

	if (bInsideAppendix)
	{	p2_apx_n4++;
	}
	else
	{	p2_toc_n4++;
	}
	
	p2_toc_counter++;

	last_n4_index= p2_toc_counter;

	nr1= toc[p2_toc_counter]->nr1;
	nr2= toc[p2_toc_counter]->nr2;
	nr3= toc[p2_toc_counter]->nr3;
	nr4= toc[p2_toc_counter]->nr4;
	(bInsideAppendix) ? (chapter= nr1) : (chapter= nr1+toc_offset);

	n[0]= EOS;
	numbers[0]= EOS;

	if (!invisible)
	{	if (bInsideAppendix)
		{	sprintf(numbers, "%c.%d.%d.%d", 'A'+nr1-1, nr2+subtoc_offset, nr3+subsubtoc_offset, nr4+subsubsubtoc_offset);
		}
		else
		{	sprintf(numbers, "%d.%d.%d.%d", chapter, nr2+subtoc_offset, nr3+subsubtoc_offset, nr4+subsubsubtoc_offset);
		}
	}
	
	if (bVerbose)
	{	sprintf(sInfMsg, "[%s] ", numbers);
		show_status_node(sInfMsg);
	}

	if (no_numbers || invisible)
	{	numbers[0]= EOS;
	}
	else
	{	strcat(numbers, " ");
	}

	strcpy(current_chapter_name, name);
	strcpy(current_chapter_nr, numbers);
	
	do_index= (use_nodes_inside_index && !no_index &&
					!toc[p2_toc_counter]->ignore_index);	/* r5pl10 */
	
	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
			set_inside_node4();
			if (invisible)
			{	(use_style_book)	? voutlnf("\n\\subsubsection*{%s}", name)
									: voutlnf("\n\\paragraph*{%s}", name);
			}
			else
			{	(use_style_book)	? voutlnf("\n\\subsubsection{%s}", name)
									: voutlnf("\n\\paragraph{%s}", name);
			}
			label2tex(name);				/*r6pl2*/
			voutlnf("\\label{%s}", name);	/*r6pl2*/
			output_aliasses();
			if (desttype==TOPDL)	/*r6pl8*/
			{
				voutlnf("\\pdfdest num %d fitbh", p2_lab_counter);
				voutlnf("\\pdfoutline goto num %d count 0 {%s}", p2_lab_counter, name);
			}
			break;

		case TOLYX:
			set_inside_node4();
			out("\\layout ");
			if (invisible)
			{	(use_style_book)	? outln("Subsubsection*")
									: outln("Paragraph*");
			}
			else
			{	(use_style_book)	? outln("Subsubsection")
									: outln("Paragraph");
			}
			indent2space(name);
			outln(name);
			break;

		case TOINF:
			set_inside_node4();
			output_texinfo_node(name);
			if (bInsideAppendix)
			{	voutlnf("@appendixsubsubsec %s", name);
			}
			else
			{	(invisible) ? 	(voutlnf("@subsubheading %s", name))
							:	(voutlnf("@subsubsection %s", name));
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
			if ( !do_index )
			{	outln("@indexoff");
			}
			if (popup)
			{	voutlnf("@pnode \"%s\"", name);
			}
			else
			{	voutlnf("@node \"%s\"", name);
			}
			if ( !do_index )
			{	outln("@indexon");
			}

			/* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
			if (!popup)
			{	ui= toc[p2_toc_counter]->up_n3_index;
				if (ui>0)
				{	strcpy(sTemp, toc[ui]->name);
					node2stg(sTemp);
					replace_2at_by_1at(sTemp);
					voutlnf("@toc \"%s\"", sTemp);
				}
			}
			stg_header(numbers, stgname, popup);	/* r5pl14: stgname statt "" */
			break;

		case TOAMG:
			set_inside_node4();
			replace_2at_by_1at(name);
			node2stg(name);

			outln("");
			if (titleprogram[0]!=EOS)
			{	voutlnf("@node \"%s\" \"%s - %s\"", name, titleprogram, name);
			}
			else
			{	voutlnf("@node \"%s\" \"%s\"", name, name);
			}

			/* r5pl6: up_n2_index wird statt der alten Abfrage benutzt */
			ui= toc[p2_toc_counter]->up_n3_index;
			if (ui>0)
			{	strcpy(sTemp, toc[ui]->name);
				node2stg(sTemp);
				replace_2at_by_1at(sTemp);
				voutlnf("@toc \"%s\"", sTemp);
			}
			stg_header(numbers, stgname, FALSE);	/* r5pl14: stgname statt "" */
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
			node2NrIPF(n, toc[p2_toc_counter]->labindex);	/* r6pl2 */
			map[0]= EOS;
			if (toc[p2_toc_counter]->mapping>=0)
			{	sprintf(map, " res=%d", toc[p2_toc_counter]->mapping);
			}
			if (bInsideAppendix)
			{	voutlnf(":h4 id=%s%s.%s %s%s", n, map, lang.appendix, numbers, name);
			}
			else
			{	voutlnf(":h4 id=%s%s.%s%s", n, map, numbers, name);
			}
			break;
    		

		case TOKPS:
			set_inside_node4();

			if (use_style_book)
			{	(bInsideAppendix)	?	sprintf(n, "%s %s", lang.appendix, numbers)
									:	sprintf(n, "%s %s", lang.chapter, numbers);
				del_right_spaces(n);
				if (n[0]!=EOS) strcat(n, " ");
				strcat(n, name);
				outln("11 changeFontSize");
			}
			else
			{	if (numbers[0]!=EOS) strcat(numbers, " ");
				sprintf(n, "%s%s", numbers, name);
				/* Changed in r6pl16 [NHz] */
				voutlnf("%d changeFontSize", laydat.node4size);
			}
			node2postscript(name, KPS_NAMEDEST); /* Changed in r6pl16 [NHz] */
			voutlnf("/%s NameDest", name); /* New in r6pl15 [NHz] */
			outln("newline");
			outln("Bon");
			voutlnf("(%s) udoshow", n);
			outln("Boff");
			outln("newline");
			voutlnf("%d changeFontSize", laydat.propfontsize); /* Changed in r6pl15 [NHz] */
			break;

		case TODRC:
			set_inside_node4();
			outln("%%*");
			voutlnf("%%%% %d, 0, 0, 0, %d, %s", last_n3_index+1000, iDrcFlags, name);
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

			/* r6pl6: Indizes fÅr RTF */
			if (use_nodes_inside_index && !no_index && !toc[p2_toc_counter]->ignore_index)
			{	strcpy(n, name);
				winspecials2ascii(n);
				voutf("{\\xe\\v %s}", n);
			}

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
				{	/* Changed in r6pl16 [NHz] */
					/* Nodesize ist set on discrete value */
					sprintf(n, "%s\\fs%d", rtf_inv_node4, laydat.node4size);
				}
				else
				{	/* Changed in r6pl16 [NHz] */
					/* Nodesize ist set on discrete value */
					sprintf(n, "%s\\fs%d", rtf_node4, laydat.node4size);
				}
			}

			if (numbers[0]==EOS)
			{	voutlnf("%s %s %s%s", rtf_plain, n, name, rtf_parpard);
			}
			else
			{	voutlnf("%s %s %s  %s%s", rtf_plain, n, numbers, name, rtf_parpard);
			}
			voutlnf("%s %s\\fs%d %s", rtf_plain, rtf_norm, iDocPropfontSize, rtf_par);	/* r5pl6 */
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

		case TOHTM:
		case TOMHH:
			ti= p2_toc_counter;

			if (!html_merge_node4)
			{	if (!html_new_file()) return;
				if (!toc[ti]->ignore_title)
				{	sprintf(hx_start, "<h%d>", html_nodesize);
					sprintf(hx_end, "</h%d>", html_nodesize);
				}
			}
			else
			{	if (!toc[ti]->ignore_title)
				{	sprintf(hx_start, "<h%d>", html_nodesize+3);
					sprintf(hx_end, "</h%d>", html_nodesize+3);
				}
				output_aliasses();
			}

			set_inside_node4();
			flag= FALSE;
						
			if (use_chapter_images)
			{
				ti= p2_toc_counter;
				if (ti>=0 && toc[ti]->image!=NULL)
				{	sGifSize[0]= EOS;
					if (toc[ti]->uiImageWidth!=0 && toc[ti]->uiImageHeight!=0)
					{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"",
							toc[ti]->uiImageWidth, toc[ti]->uiImageHeight);
					}
					voutlnf("%s<p align=\"center\">", hx_start);
					voutlnf("<img src=\"%s%s\" alt=\"%s%s\"%s>",
						toc[ti]->image, sDocImgSuffix, numbers, name, sGifSize);
					voutlnf("</p>%s", hx_end);
					flag= TRUE;
				}
			}

			do_toptoc(TOC_NODE4);	/*r6pl5*/

			if (!flag)
			{
				strcpy(nameNoSty, name);
				del_html_styles(nameNoSty);
				label2html(nameNoSty);	/*r6pl2*/
				voutlnf("%s<a name=\"%s\">%s%s</a>%s",
					hx_start, nameNoSty, numbers, name, hx_end);
			}
			break;

		case TOLDS:
			set_inside_node4();
			(use_style_book)	?	voutlnf("<sect2>%s<label id=\"%s\">", name, name)
								:	voutlnf("<sect3>%s<label id=\"%s\">", name, name);
			output_aliasses();	/* r5pl8 */
			outln("<p>");
			break;

		case TOHPH:
			set_inside_node4();
			(use_style_book)	?	voutlnf("<s3>%s", name)
								:	voutlnf("<s4>%s", name);
			output_aliasses();
			break;
	}

	about_unregistered();

}	/*make_subsubsubnode*/


GLOBAL void c_subsubsubnode ( void )
{	make_subsubsubnode (FALSE, FALSE);
}	/* c_subsubsubnode */

GLOBAL void c_subsubsubnode_iv ( void )
{	make_subsubsubnode (FALSE, (desttype!=TOINF));	/* r5pl15 */
}	/* c_subsubsubnode */

GLOBAL void c_psubsubsubnode ( void )
{	make_subsubsubnode (TRUE, FALSE);
}	/* c_psubsubsubnode */

GLOBAL void c_psubsubsubnode_iv ( void )
{	make_subsubsubnode (TRUE, (desttype!=TOINF));	/* r5pl15 */
}	/* c_psubsubsubnode */


GLOBAL void c_endnode ( void )
{
	check_endnode();
}	/* c_endnode */



/*	############################################################
	# r6pl5: neue Kommandos
	############################################################	*/
GLOBAL void c_begin_node ( void )
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
		default:
			warning_node_too_deep();
			c_subsubsubnode();
			break;
	}

}	/* c_begin_node */


GLOBAL void c_begin_node_iv ( void )
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
		default:
			warning_node_too_deep();
			c_subsubsubnode_iv();	
			break;
	}

}	/* c_begin_node_iv */


GLOBAL void c_begin_pnode ( void )
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
		default:
			warning_node_too_deep();
			c_psubsubsubnode();	
			break;
	}

}	/* c_begin_pnode */


GLOBAL void c_begin_pnode_iv ( void )
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
		default:
			warning_node_too_deep();
			c_psubsubsubnode_iv();	
			break;
	}

}	/* c_begin_pnode_iv */

GLOBAL void c_end_node ( void )
{
	check_endnode();

	switch (p2_toctype)
	{
		case TOC_NODE1:	p2_toctype= TOC_NONE;	break;
		case TOC_NODE2:	p2_toctype= TOC_NODE1;	break;
		case TOC_NODE3:	p2_toctype= TOC_NODE2;	break;
		case TOC_NODE4:	p2_toctype= TOC_NODE3;	break;
	}

}	/* c_end_node */



/*	############################################################
	#
	#	Inhaltsverzeichnis(se) ausgeben
	#
	#	r5pl6: Kapitel werden direkt referenziert. Der
	#	zeitraubende Weg ueber auto_references() entfaellt.
	#
	############################################################	*/
LOCAL void tocline_make_bold ( char *s, const int depth )
{
	if (depth>1)	/* r6pl5: >1 statt ==1 */
	{
		switch (desttype)
		{
			case TOHTM:
			case TOMHH:
#if 1
				qreplace_once(s, "<li>", 4, "<li><b>", 7);
				qreplace_last(s, "</li>", 5, "</b></li>", 9);
#else
				/* ergibt <b><li>...</li></b>, was falsch ist */
				strinsert(s, BOLD_ON);
				strcat(s, BOLD_OFF);
				c_internal_styles(s);
#endif
				break;
			case TOWIN:
			case TOWH4:
			case TOAQV:
				strinsert(s, BOLD_ON);
				strcat(s, BOLD_OFF);
				c_win_styles(s);
				break;
			
/*			case TOKPS:
				strinsert(s, "14 changeFontSize Bon ");
				strcat(s, " Boff 11 changeFontSize changeBaseFont");
				break;*/
		}
	}

}	/* tocline_make_bold */


LOCAL void tocline_handle_1st ( BOOLEAN *f )
{
	if (*f)
	{	switch (desttype)
		{	case TOINF:
				outln("@menu");
				break;
			case TOHTM:
			case TOMHH:
			case TOTEX:
			case TOPDL:
				outln(toc_list_top);
				break;
		}
		*f= FALSE;
	}

}	/* tocline_handle_1st */



LOCAL void convert_toc_item ( TOCITEM *t )
{
	if (!t->converted)
	{	replace_macros(t->name);
		c_internal_styles(t->name);
		replace_udo_quotes(t->name);
		delete_all_divis(t->name);
		replace_udo_tilde(t->name);
		replace_udo_nbsp(t->name);
		t->converted= TRUE;
	}

}	/* convert_toc_name */


/* New in r6pl15 [NHz] */
/* Output of bookmarks for postscript/PDF */
GLOBAL BOOLEAN bookmarks_ps ( void )
{
	register int i;
	int li, apxstart;
	char s[128], n[128];

	if (p1_toc_counter<=0)
	{	return FALSE;
	}

	apxstart= 1;

	for (i=1; i<=p1_toc_counter; i++)
	{
		if (toc[i]!=NULL && !toc[i]->invisible)
		{
			convert_toc_item(toc[i]);

			if ( toc[i]->appendix )
			{
				apxstart= i;	/* fuer unten merken */
				break;			/* r5pl6: Es kann nur einen Anhang geben */
			}
			else
			{	if ( toc[i]->n1 != 0 )
				{
					if ( toc[i]->toctype==TOC_NODE1 )
					{	/* Ein Kapitel */	

						li= toc[i]->labindex;

						strcpy(s, lab[li]->name);
						/* Changed in r6pl16 [NHz] */
						strcpy(n, lab[li]->name);
						node2postscript(n, KPS_BOOKMARK);
						node2postscript(s, KPS_NAMEDEST);
						voutlnf("(%d %s) /%s %d Bookmarks",
											toc[i]->nr1+toc_offset,
											n, s,
											toc[i]->count_n2);
					}/* TOC_NODE1 */
					
					
					if ( toc[i]->toctype==TOC_NODE2 )
					{	/* Ein Abschnitt */

						li= toc[i]->labindex;

						strcpy(s, lab[li]->name);
						/* Changed in r6pl16 [NHz] */
						strcpy(n, lab[li]->name);
						node2postscript(n, KPS_BOOKMARK);
						node2postscript(s, KPS_NAMEDEST);
						voutlnf("(%d.%d %s) /%s %d Bookmarks",
											toc[i]->nr1+toc_offset,
											toc[i]->nr2+subtoc_offset,
											n, s,
											toc[i]->count_n3);
					}/* TOC_NODE2 */
					
					if ( toc[i]->toctype==TOC_NODE3 )
					{	/* Ein Unterabschnitt */

						li= toc[i]->labindex;

						strcpy(s, lab[li]->name);
						/* Changed in r6pl16 [NHz] */
						strcpy(n, lab[li]->name);
						node2postscript(n, KPS_BOOKMARK);
						node2postscript(s, KPS_NAMEDEST);
						voutlnf("(%d.%d.%d %s) /%s %d Bookmarks",
											toc[i]->nr1+toc_offset,
											toc[i]->nr2+subtoc_offset,
											toc[i]->nr3+subsubtoc_offset,
											n, s,
											toc[i]->count_n4);
					}/* TOC_NODE3 */
				
					if ( toc[i]->toctype==TOC_NODE4 )
					{	/* Ein Paragraph */

						li= toc[i]->labindex;

						strcpy(s, lab[li]->name);
						/* Changed in r6pl16 [NHz] */
						strcpy(n, lab[li]->name);
						node2postscript(n, KPS_BOOKMARK);
						node2postscript(s, KPS_NAMEDEST);
						voutlnf("(%d.%d.%d.%d %s) /%s 0 Bookmarks",
											toc[i]->nr1+toc_offset,
											toc[i]->nr2+subtoc_offset,
											toc[i]->nr3+subsubtoc_offset,
											toc[i]->nr4+subsubsubtoc_offset,
											n, s);
					}/* TOC_NODE4 */


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

			if ( toc[i]->appendix )
			{
				if ( toc[i]->n1 != 0 )
				{
					if ( toc[i]->toctype==TOC_NODE1 )
					{	/* Ein Kapitel */	

						li= toc[i]->labindex;

						strcpy(s, lab[li]->name);
						/* Changed in r6pl16 [NHz] */
						strcpy(n, lab[li]->name);
						node2postscript(n, KPS_BOOKMARK);
						node2postscript(s, KPS_NAMEDEST);
						voutlnf("(%c %s) /%s %d Bookmarks",
											'A'-1+toc[i]->nr1+toc_offset,
											n, s,
											toc[i]->count_n2);
					}/* TOC_NODE1 */
					
					
					if ( toc[i]->toctype==TOC_NODE2 )
					{	/* Ein Abschnitt */

						li= toc[i]->labindex;

						strcpy(s, lab[li]->name);
						/* Changed in r6pl16 [NHz] */
						strcpy(s, lab[li]->name);
						strcpy(n, lab[li]->name);
						node2postscript(n, KPS_BOOKMARK);
						node2postscript(s, KPS_NAMEDEST);
						voutlnf("(%c.%2d %s) /%s %d Bookmarks",
											'A'-1+toc[i]->nr1+toc_offset,
											toc[i]->nr2+subtoc_offset,
											n, s,
											toc[i]->count_n3);
					}/* TOC_NODE2 */
					
					if ( toc[i]->toctype==TOC_NODE3 )
					{	/* Ein Unterabschnitt */

						li= toc[i]->labindex;

						strcpy(s, lab[li]->name);
						/* Changed in r6pl16 [NHz] */
						strcpy(n, lab[li]->name);
						node2postscript(n, KPS_BOOKMARK);
						node2postscript(s, KPS_NAMEDEST);
						voutlnf("(%c.%2d.%2d %s) /%s %d Bookmarks",
											'A'-1+toc[i]->nr1+toc_offset,
											toc[i]->nr2+subtoc_offset,
											toc[i]->nr3+subsubtoc_offset,
											n, s,
											toc[i]->count_n4);
					}/* TOC_NODE3 */
				
					if ( toc[i]->toctype==TOC_NODE4 )
					{	/* Ein Paragraph */

						li= toc[i]->labindex;

						strcpy(s, lab[li]->name);
						/* Changed in r6pl16 [NHz] */
						strcpy(n, lab[li]->name);
						node2postscript(n, KPS_BOOKMARK);
						node2postscript(s, KPS_NAMEDEST);
						voutlnf("(%c.%2d.%2d.%2d %s) /%s 0 Bookmarks",
											'A'-1+toc[i]->nr1+toc_offset,
											toc[i]->nr2+subtoc_offset,
											toc[i]->nr3+subsubtoc_offset,
											toc[i]->nr4+subsubsubtoc_offset,
											n, s);
					}/* TOC_NODE4 */

				}/* toc[i]->n1 > 0 */

			}/* !toc[i]->appendix */

		}/* toc[i]!=NULL && !toc[i]->invisible */

	}/* for */

	outln("");

	return TRUE;
}	/* bookmarks_ps */


/* New in r6pl16 [NHz] */
LOCAL void toc_link_output ( const int depth )
{
	register int i;
	char	*htmlfilename, hfn[512], suff[12], sTarget[512]="\0";

	if (html_frames_layout)
	{	sprintf(sTarget, " target=\"UDOcon\"");
	}
	
	if (p1_toc_counter<=0)
	{	return;
	}

	for (i=1; i<=p1_toc_counter; i++)
	{
		if (toc[i]!=NULL && !toc[i]->invisible)
		{
			convert_toc_item(toc[i]);

			if ( toc[i]->n1 != 0 )
			{
				switch (depth)
				{
					case 1:
						if (( toc[i]->toctype==TOC_NODE1 ) && !(toc[i]->appendix ))
						{	/* Ein Kapitel */	
		
							sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
							htmlfilename= hfn;

							/* Feststellen, ob die Referenz im gleichen File liegt */
							if ((html_merge_node1==FALSE) && (strcmp(htmlfilename, outfile.name)!=0))
							{
								if(strchr(htmlfilename, '.') != NULL)
									strcpy(suff, "");
								else
									strcpy(suff, outfile.suff);

								voutlnf("<link rel=\"chapter\" href=\"%s%s\"%s title=\"%d %s\">", htmlfilename, suff, sTarget, toc[i]->nr1+toc_offset, toc[i]->name);
							}
						}/* TOC_NODE1 */
						break;
				
					case 2:
						if ( toc[i]->toctype==TOC_NODE2 )
						{	/* Ein Unterkapitel */	

							/* Changed in r6.2pl1 [NHz]; I'm not sure, if this makes sense, but it doesn't disturb */
							if((toc[toc[i]->up_n1_index]->nr1+toc_offset == toc[last_n1_index]->nr1+toc_offset) &&
									(toc[i]->up_n1_index == last_n1_index))
							{
								sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
								htmlfilename= hfn;

								/* Feststellen, ob die Referenz im gleichen File liegt */
								if ((html_merge_node2==FALSE) && (strcmp(htmlfilename, outfile.name)!=0))
								{
									if(strchr(htmlfilename, '.') != NULL)
										strcpy(suff, "");
									else
										strcpy(suff, outfile.suff);

									voutlnf("<link rel=\"section\" href=\"%s%s\"%s title=\"%d.%d %s\">", htmlfilename, suff, sTarget, toc[i]->nr1+toc_offset, toc[i]->nr2+subtoc_offset, toc[i]->name);
								}
							}
						}/* TOC_NODE2 */
						break;
				
					case 3:
						if ( toc[i]->toctype==TOC_NODE3 )
						{	/* Ein Unterunterkapitel */	

							/* Changed in r6.2pl1 [NHz] */
							if((toc[toc[i]->up_n2_index]->nr2+subtoc_offset == toc[last_n2_index]->nr2+subtoc_offset) &&
									(toc[i]->up_n2_index == last_n2_index))
							{
								sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
								htmlfilename= hfn;

								/* Feststellen, ob die Referenz im gleichen File liegt */
								if ((html_merge_node3==FALSE) && (strcmp(htmlfilename, outfile.name)!=0))
								{
									if(strchr(htmlfilename, '.') != NULL)
										strcpy(suff, "");
									else
										strcpy(suff, outfile.suff);

									voutlnf("<link rel=\"subsection\" href=\"%s%s\"%s title=\"%d.%d.%d %s\">", htmlfilename, suff, sTarget, toc[i]->nr1+toc_offset, toc[i]->nr2+subtoc_offset, toc[i]->nr3+subsubtoc_offset, toc[i]->name);
								}
							}
						}/* TOC_NODE3 */
						break;

					case 4:
						if (( toc[i]->toctype==TOC_NODE1 ) && ( toc[i]->appendix ))
						{	/* Ein Unterunterunterkapitel */	

							sprintf(hfn, "%s%s", html_name_prefix, toc[i]->filename);
							htmlfilename= hfn;

							/* Feststellen, ob die Referenz im gleichen File liegt */
							if ((html_merge_node1==FALSE) && (strcmp(htmlfilename, outfile.name)!=0))
							{
								if(strchr(htmlfilename, '.') != NULL)
									strcpy(suff, "");
								else
									strcpy(suff, outfile.suff);

								voutlnf("<link rel=\"appendix\" href=\"%s%s\"%s title=\"%c %s\">", htmlfilename, suff, sTarget, 'A'-1+toc[i]->nr1, toc[i]->name);
							}
						}/* TOC_NODE1 */
						break;
				
				}/* switch */

			}/* toc[i]->n1 > 0 */

		}/* toc[i]!=NULL && !toc[i]->invisible */

	}/* for */

}	/* toc_link_output */


LOCAL void toc_output ( const int depth )
{
	register int i;
	int li;
	char	n[512], ref[512];
	BOOLEAN	leerzeile= FALSE;
	BOOLEAN last_n= TRUE;
	BOOLEAN last_sn= FALSE;
	BOOLEAN last_ssn= FALSE;
	BOOLEAN last_sssn= FALSE;
	BOOLEAN	first= TRUE;
	BOOLEAN old;
	
	if (desttype==TOLYX)
	{	return;
	}

	if (p1_toc_counter<=0)
	{	return;
	}

	old= bDocAutorefOff;
	bDocAutorefOff= FALSE;

	for (i=1; i<=p1_toc_counter; i++)
	{
		if (toc[i]!=NULL && !toc[i]->invisible)
		{
			convert_toc_item(toc[i]);

			if ( toc[i]->appendix )
			{	break;	/* r5pl6: Es kann nur einen Anhang geben */
			}
			else
			{	if ( toc[i]->n1 != 0 )
				{
					if ( toc[i]->toctype==TOC_NODE1 )
					{	/* Ein Kapitel */	

						if ( (leerzeile) && (depth>1) )
						{	switch(desttype)
							{	case TOWIN:
								case TOWH4:
								case TOAQV:	outln(rtf_par);	break;
								case TOHTM:
								case TOMHH:	outln("<br>&nbsp;");	break;
								case TOTEX:
								case TOPDL:	break;
								default:	outln(""); break;
							}
							/* leerzeile= FALSE; */
						}
						
						if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
						{	if (last_sn)
							{	outln(toc_list_end);
								last_sn= FALSE;
							}
							if (last_ssn)
							{	voutlnf("%s%s", toc_list_end, toc_list_end);
								last_ssn= FALSE;
							}
							if (last_sssn)
							{	voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
								last_sssn= FALSE;
							}
							last_n= TRUE;
						}

						li= toc[i]->labindex;
						string2reference(ref, lab[li], TRUE, "", 0, 0);

						if (no_numbers)
						{	sprintf(n, form_t1_n1, ref);
						}
						else
						{	sprintf(n, form_t1_n1, toc[i]->nr1+toc_offset, ref);
						}
						
						tocline_make_bold(n, depth);

						tocline_handle_1st(&first);

						outln(n);
						leerzeile= TRUE;
					}/* TOC_NODE1 */
					
					
					if (depth>1)
					{
						if ( toc[i]->toctype==TOC_NODE2 )
						{	/* Ein Abschnitt */
							if (use_toc_list_commands)	/*r6pl2: vorher desttype==TOHTM */
							{	if (last_n)
								{	outln(toc_list_top);
									last_n= FALSE;
								}
								if (last_ssn)
								{	outln(toc_list_end);
									last_ssn= FALSE;
								}
								if (last_sssn)
								{	voutlnf("%s%s", toc_list_end, toc_list_end);
									last_sssn= FALSE;
								}
								last_sn= TRUE;
							}

							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_t1_n2, ref);
							}
							else
							{	sprintf(n, form_t1_n2, toc[i]->nr1+toc_offset,
														toc[i]->nr2+subtoc_offset, ref);
							}

							tocline_handle_1st(&first);

							outln(n);
						}/* TOC_NODE2 */
					}	/* depth>1 */
					
					if (depth>2)
					{
						if ( toc[i]->toctype==TOC_NODE3 )
						{	/* Ein Unterabschnitt */
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_n)
								{	voutlnf("%s%s", toc_list_top, toc_list_top);
									last_n= FALSE;
								}
								if (last_sn)
								{	outln(toc_list_top);
									last_sn= FALSE;
								}
								if (last_sssn)
								{	outln(toc_list_end);
									last_sssn= FALSE;
								}
								last_ssn= TRUE;
							}

							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_t1_n3, ref);
							}
							else
							{	sprintf(n, form_t1_n3, toc[i]->nr1+toc_offset,
														toc[i]->nr2+subtoc_offset,
														toc[i]->nr3+subsubtoc_offset, ref);
							}

							tocline_handle_1st(&first);

							outln(n);

						}/* TOC_NODE3 */
					}	/* depth>2 */
					
					
					if (depth>3)
					{
						if ( toc[i]->toctype==TOC_NODE4 )
						{	/* Ein Paragraph */
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_n)
								{	voutlnf("%s%s%s", toc_list_top, toc_list_top, toc_list_top);
									last_n= FALSE;
								}
								if (last_sn)
								{	voutlnf("%s%s", toc_list_top, toc_list_top);
									last_sn= FALSE;
								}
								if (last_ssn)
								{	outln(toc_list_top);
									last_ssn= FALSE;
								}
								last_sssn= TRUE;
							}

							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_t1_n4, ref);
							}
							else
							{	sprintf(n, form_t1_n4,
									toc[i]->nr1+toc_offset,
									toc[i]->nr2+subtoc_offset,
									toc[i]->nr3+subsubtoc_offset,
									toc[i]->nr4+subsubsubtoc_offset,
									ref);
							}

							tocline_handle_1st(&first);

							outln(n);

						}/* TOC_NODE4 */

					}/* if (depth>3) */

				}/* toc[i]->n1 > 0 */

			}/* !toc[i]->appendix */

		}/* toc[i]!=NULL && !toc[i]->invisible */

	}/* for */

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
		case TOTEX:
		case TOPDL:
			if (last_sn)	outln(toc_list_end);
			if (last_ssn)	voutlnf("%s%s", toc_list_end, toc_list_end);
			if (last_sssn)	voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
			outln(toc_list_end);
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			outln("\\par ");
			break;
		case TOINF:
			if (!apx_available && !no_index && bCalledIndex && use_udo_index)
			{	outln("");
				voutlnf("* %s::", lang.index);
			}
			outln("@end menu");
			break;
		case TOSTG:
		case TOAMG:
			if (!apx_available)
			{	outln("");
			}
			break;
	}

	bDocAutorefOff= old;	
}	/* toc_output */



LOCAL void apx_output ( const int depth )
{
	register int i;
	int li;
	char	n[512], ref[512];
	BOOLEAN	leerzeile= FALSE;
	BOOLEAN last_n= TRUE;
	BOOLEAN last_sn= FALSE;
	BOOLEAN last_ssn= FALSE;
	BOOLEAN last_sssn= FALSE;
	BOOLEAN first= TRUE;

	BOOLEAN old;
	
	if (desttype==TOLYX)
	{	return;
	}

	if (p1_toc_counter<=0)
	{	return;
	}

	if (!apx_available)		/* r5pl16 */
	{	return;
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

			if ( toc[i]->appendix )
			{	if ( toc[i]->n1 != 0 )
				{
					if ( toc[i]->toctype==TOC_NODE1 )
					{	/* Ein Kapitel */

						if ( (leerzeile) && (depth>1) )
						{	switch(desttype)
							{	case TOHTM:
								case TOMHH:	outln("<br>&nbsp;");	break;
								case TOWIN:
								case TOWH4:
								case TOAQV:	outln(rtf_par);	break;
								case TOTEX:
								case TOPDL:	break;
								default:	outln(""); break;
							}
							/* leerzeile= FALSE; */
						}

						if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
						{	if (last_sn)
							{	outln(toc_list_end);
								last_sn= FALSE;
							}
							if (last_ssn)
							{	voutlnf("%s%s", toc_list_end, toc_list_end);
								last_ssn= FALSE;
							}
							if (last_sssn)
							{	voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
								last_sssn= FALSE;
							}
							last_n= TRUE;
						}
						
						li= toc[i]->labindex;
						string2reference(ref, lab[li], TRUE, "", 0, 0);

						if (no_numbers)
						{	sprintf(n, form_a1_n1, ref);
						}
						else
						{	sprintf(n, form_a1_n1, 'A'-1+toc[i]->nr1, ref);
						}

						tocline_make_bold(n, depth);
						tocline_handle_1st(&first);

						outln(n);
						leerzeile= TRUE;
					}
					
					if (depth>1)
					{
						if ( toc[i]->toctype==TOC_NODE2 )
						{	/* Ein Abschnitt */
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_n)
								{	outln(toc_list_top);
									last_n= FALSE;
								}
								if (last_ssn)
								{	outln(toc_list_end);
									last_ssn= FALSE;
								}
								if (last_sssn)
								{	voutlnf("%s%s", toc_list_end, toc_list_end);
									last_sssn= FALSE;
								}
								last_sn= TRUE;
							}
							
							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_a1_n2, ref);
							}
							else
							{	sprintf(n, form_a1_n2, 'A'-1+toc[i]->nr1, toc[i]->nr2, ref);
							}

							tocline_handle_1st(&first);
							outln(n);
						}
					}	/* depth>1 */
						
					if (depth>2)
					{
						if ( toc[i]->toctype==TOC_NODE3 )
						{	/* Ein Unterabschnitt */
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_n)
								{	voutlnf("%s%s", toc_list_top, toc_list_top);
									last_n= FALSE;
								}
								if (last_sn)
								{	outln(toc_list_top);
									last_sn= FALSE;
								}
								if (last_sssn)
								{	outln(toc_list_end);
									last_sssn= FALSE;
								}
								last_ssn= TRUE;
							}
							
							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_a1_n3, ref);
							}
							else
							{	sprintf(n, form_a1_n3, 'A'-1+toc[i]->nr1, toc[i]->nr2, toc[i]->nr3, ref);
							}

							tocline_handle_1st(&first);
							outln(n);
						}/* TOC_NODE3 */
					}	/* depth>2 */
					
					if (depth>3)
					{
						if ( toc[i]->toctype==TOC_NODE4 )
						{	/* Ein Paragraph */
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_n)
								{	voutlnf("%s%s%s", toc_list_top, toc_list_top, toc_list_top);
									last_n= FALSE;
								}
								if (last_sn)
								{	voutlnf("%s%s", toc_list_top, toc_list_top);
									last_sn= FALSE;
								}
								if (last_ssn)
								{	outln(toc_list_top);
									last_ssn= FALSE;
								}
								last_sssn= TRUE;
							}
							
							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_a1_n4, ref);
							}
							else
							{	sprintf(n, form_a1_n4,
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
				}/* toc[i]->n1!=0 */
			}/* toc[i]->appendix */
		}
	}

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
		case TOTEX:
		case TOPDL:
			if (last_sn)	outln(toc_list_end);
			if (last_ssn)	voutlnf("%s%s", toc_list_end, toc_list_end);
			if (last_sssn)	voutlnf("%s%s%s", toc_list_end, toc_list_end, toc_list_end);
			outln(toc_list_end);
			break;
		case TOINF:
			if (!no_index && bCalledIndex && use_udo_index)
			{	outln("");
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
}	/* apx_output */


LOCAL void subtoc_output ( const int depth )
{
	register int i;
	int li;
	char	n[512], ref[512];
	BOOLEAN last_sn= FALSE;
	BOOLEAN last_ssn= FALSE;
	BOOLEAN last_sssn= FALSE;
	BOOLEAN output_done= FALSE;
	BOOLEAN first= TRUE;
	BOOLEAN old;
	
	if (desttype==TOLYX)
	{	return;
	}

	if ( p1_toc_counter<=0 )
	{	return;
	}
	
	if ( toc[p2_toc_counter]->ignore_subtoc )	/* r5pl6 */
	{	return;
	}

	old= bDocAutorefOff;
	bDocAutorefOff= FALSE;

	for (i=last_n1_index; i<=p1_toc_counter; i++)
	{
		/* r5pl10: langwierige Indizierung vermeiden */
		toc[i]= toc[i];

		if (toc[i]!=NULL && !toc[i]->invisible)
		{
			convert_toc_item(toc[i]);

			if ( toc[i]->appendix )
			{	break;	/* r5pl6: Nach dem ersten Anhang-Node kommt nichts mehr */
			}
			
			if ( toc[i]->n1>p2_toc_n1 )
			{	break;	/* r5pl6: Das waren alle */
			}

			if ( toc[i]->n1!=0 )
			{
				if ( toc[i]->n1 == p2_toc_n1 )
				{
					if ( toc[i]->toctype==TOC_NODE2 )
					{	/* Ein Abschnitt */
						if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
						{	if (last_ssn)
							{	outln(toc_list_end);
								last_ssn= FALSE;
							}
							if (last_sssn)
							{	voutlnf("%s%s", toc_list_end, toc_list_end);
								last_sssn= FALSE;
							}
							last_sn= TRUE;
						}

						li= toc[i]->labindex;
						string2reference(ref, lab[li], TRUE, "", 0, 0);

						if (no_numbers)
						{	sprintf(n, form_t2_n2, ref);
						}
						else
						{	sprintf(n, form_t2_n2, toc[i]->nr1+toc_offset,
													toc[i]->nr2+subtoc_offset, ref);
						}

						tocline_handle_1st(&first);
						outln(n);
						output_done=TRUE;
					}
						
					if (depth>1)
					{
						if ( toc[i]->toctype==TOC_NODE3 )
						{	/* Ein Unterabschnitt */
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_sn)
								{	outln(toc_list_top);
									last_sn= FALSE;
								}
								if (last_sssn)
								{	outln(toc_list_end);
									last_sssn= FALSE;
								}
								last_ssn= TRUE;
							}

							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_t2_n3, ref);
							}
							else
							{	sprintf(n, form_t2_n3, toc[i]->nr1+toc_offset,
														toc[i]->nr2+subtoc_offset,
														toc[i]->nr3+subsubtoc_offset,
														ref);
							}

							tocline_handle_1st(&first);
							outln(n);
							output_done=TRUE;
						}/* TOC_NODE3 */
					}	/* depth>1 */
						
					if (depth>2)
					{
						if ( toc[i]->toctype==TOC_NODE4 )
						{	/* Ein Paragraph */
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_sn)
								{	outln(toc_list_top);
									last_sn= FALSE;
								}
								if (last_ssn)
								{	outln(toc_list_top);
									last_ssn= FALSE;
								}
								last_sssn= TRUE;
							}

							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_t2_n4, ref);
							}
							else
							{	sprintf(n, form_t2_n4,
									toc[i]->nr1+toc_offset,
									toc[i]->nr2+subtoc_offset,
									toc[i]->nr3+subsubtoc_offset,
									toc[i]->nr4+subsubsubtoc_offset,
									ref);
							}

							tocline_handle_1st(&first);
							outln(n);
							output_done=TRUE;
						}/* TOC_NODE4 */
					}	/* depth>2 */
				}
			}
		}
	}
	
	if (output_done)
	{	switch(desttype)
		{	case TOHTM:
			case TOMHH:
				if (last_sssn)
				{	voutlnf("%s%s", toc_list_end, toc_list_end);
				}
				if (last_ssn)
				{	outln(toc_list_end);
				}
				outln(toc_list_end);
				outln(HTML_BR);
				break;
			case TOTEX:
			case TOPDL:
				if (last_sssn)
				{	voutlnf("%s%s", toc_list_end, toc_list_end);
				}
				if (last_ssn)
				{	outln(toc_list_end);
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
}	/* subtoc_output */	



LOCAL void subapx_output ( const int depth )
{
	register int i;
	int li;
	char	n[512], ref[512];
	BOOLEAN last_sn= FALSE;
	BOOLEAN last_ssn= FALSE;
	BOOLEAN last_sssn= FALSE;
	BOOLEAN output_done= FALSE;
	BOOLEAN first= TRUE;

	BOOLEAN old;
	
	if (desttype==TOLYX)
	{	return;
	}

	if ( p1_toc_counter<=0 )
	{	return;
	}

	if ( toc[p2_toc_counter]->ignore_subtoc )	/* r5pl6 */
	{	return;
	}

	old= bDocAutorefOff;
	bDocAutorefOff= FALSE;

	for (i=last_n1_index; i<=p1_toc_counter; i++)
	{
		/* r5pl10: langwierige Indizierung vermeiden */
		toc[i]= toc[i];

		if (toc[i]!=NULL && !toc[i]->invisible)
		{
			convert_toc_item(toc[i]);

			if ( toc[i]->appendix && toc[i]->n1!=0 )
			{
				if ( toc[i]->n1>p2_apx_n1 )
				{	break;	/* r5pl6: das waren dann alle */
				}
				
				if ( toc[i]->n1 == p2_apx_n1 )
				{
					if ( toc[i]->toctype==TOC_NODE2 )
					{	/* Ein Abschnitt */
						if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
						{	if (last_ssn)
							{	outln(toc_list_end);
								last_ssn= FALSE;
							}
							if (last_sssn)
							{	voutlnf("%s%s", toc_list_end, toc_list_end);
								last_sssn= FALSE;
							}
							last_sn= TRUE;
						}
						
						li= toc[i]->labindex;
						string2reference(ref, lab[li], TRUE, "", 0, 0);

						if (no_numbers)
						{	sprintf(n, form_a2_n2, ref);
						}
						else
						{	sprintf(n, form_a2_n2, 'A'-1+toc[i]->nr1, toc[i]->nr2, ref);
						}

						tocline_handle_1st(&first);
						outln(n);
						output_done= TRUE;
					}
						
					if (depth>1)
					{
						if ( toc[i]->toctype==TOC_NODE3 )
						{	/* Ein Unterabschnitt */
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_sn)
								{	outln(toc_list_top);
									last_sn= FALSE;
								}
								if (last_sssn)
								{	outln(toc_list_end);
									last_sssn= FALSE;
								}
								last_ssn= TRUE;
							}
							
							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_a2_n3, ref);
							}
							else
							{	sprintf(n, form_a2_n3, 'A'-1+toc[i]->nr1, toc[i]->nr2, toc[i]->nr3, ref);
							}

							tocline_handle_1st(&first);
							outln(n);
							output_done= TRUE;
						}/* TOC_NODE3 */
					}	/* depth>1 */
						
					if (depth>2)
					{
						if ( toc[i]->toctype==TOC_NODE4 )
						{	/* Ein Paragraph */
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_sn)
								{	outln(toc_list_top);
									last_sn= FALSE;
								}
								if (last_ssn)
								{	outln(toc_list_top);
									last_ssn= FALSE;
								}
								last_sssn= TRUE;
							}
							
							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_a2_n4, ref);
							}
							else
							{	sprintf(n, form_a2_n4,
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
					}	/* depth>2 */
				}
			}
		}
	}

	if (output_done)
	{	switch(desttype)
		{
			case TOHTM:
			case TOMHH:
				if (last_ssn)
				{	outln(toc_list_end);
				}
				if (last_sssn)
				{	voutlnf("%s%s", toc_list_end, toc_list_end);
				}
				outln(toc_list_end);
				outln(HTML_BR);
				break;
			case TOTEX:
			case TOPDL:
				if (last_ssn)
				{	outln(toc_list_end);
				}
				if (last_sssn)
				{	voutlnf("%s%s", toc_list_end, toc_list_end);
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
}	/*subapx_output*/


LOCAL void subsubtoc_output ( const int depth )
{
	register int i;
	int li;
	char	n[512], ref[512];
	BOOLEAN last_ssn= FALSE;
	BOOLEAN last_sssn= FALSE;
	BOOLEAN output_done= FALSE;
	BOOLEAN first= TRUE;
	BOOLEAN old;
	
	if (desttype==TOLYX)
	{	return;
	}

	if ( p1_toc_counter<=0 )
	{	return;
	}

	if ( toc[p2_toc_counter]->ignore_subtoc )	/* r5pl6 */
	{	return;
	}
	
	if ( last_n2_index==0 )	/* r5pl6 */
	{	return;				/* Wer benutzt !subsubtoc in einem Node? */
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

			if ( toc[i]->appendix )
			{	break;	/* r5pl6: Nach dem ersten Anhang-Node kommt nichts mehr */
			}
			
			if ( toc[i]->n1>p2_toc_n1 )
			{	break;	/* r5pl6: Das waren dann alle */
			}

			if ( toc[i]->n1!=0 )
			{
				if ( toc[i]->n1 == p2_toc_n1 )
				{
					if ( toc[i]->n2>p2_toc_n2 )
					{	break;	/* r5pl6: Das waren dann alle */
					}
					
					if ( toc[i]->n2==p2_toc_n2 )
					{
						if ( toc[i]->toctype==TOC_NODE3 )
						{	/* Ein Unterabschnitt */

							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_sssn)
								{	outln(toc_list_end);
									last_sssn= FALSE;
								}
								last_ssn= TRUE;
							}

							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_t3_n3, ref);
							}
							else
							{	sprintf(n, form_t3_n3, toc[i]->nr1+toc_offset,
														toc[i]->nr2+subtoc_offset,
														toc[i]->nr3+subsubtoc_offset,
														ref);
							}

							tocline_handle_1st(&first);
							outln(n);
							output_done= TRUE;
						}/* TOC_NODE3 */
						
						if (depth>1)
						{	if ( toc[i]->toctype==TOC_NODE4 )
							{	/* Ein Paragraph */

								if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
								{	if (last_ssn)
									{	outln(toc_list_top);
										last_ssn= FALSE;
									}
									last_sssn= TRUE;
								}

								li= toc[i]->labindex;
								string2reference(ref, lab[li], TRUE, "", 0, 0);

								if (no_numbers)
								{	sprintf(n, form_t3_n4, ref);
								}
								else
								{	sprintf(n, form_t3_n4,
										toc[i]->nr1+toc_offset,
										toc[i]->nr2+subtoc_offset,
										toc[i]->nr3+subsubtoc_offset,
										toc[i]->nr4+subsubsubtoc_offset,
										ref);
								}

								tocline_handle_1st(&first);
								outln(n);
								output_done= TRUE;
							}/* TOC_NODE4 */
						}
					}
				}
			}
		}
	}

	if (output_done)
	{	switch(desttype)
		{
			case TOHTM:
			case TOMHH:
				if (last_sssn)	outln(toc_list_end);
				outln(toc_list_end);
				outln(HTML_BR);
				break;
			case TOTEX:
			case TOPDL:
				if (last_sssn)	outln(toc_list_end);
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
}	/*subsubtoc_output*/



LOCAL void subsubapx_output ( const int depth )
{
	register int i;
	int li;
	char	n[512], ref[512];
	BOOLEAN last_ssn= FALSE;
	BOOLEAN last_sssn= FALSE;
	BOOLEAN output_done= FALSE;
	BOOLEAN first= TRUE;
	BOOLEAN old;
	
	if (desttype==TOLYX)
	{	return;
	}

	if ( p1_toc_counter<=0 )
	{	return;
	}

	if ( toc[p2_toc_counter]->ignore_subtoc )	/* r5pl6 */
	{	return;
	}

	if ( last_n2_index==0 )	/* r5pl6 */
	{	return;				/* Wer benutzt !subsubtoc in einem Node? */
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

			if ( toc[i]->appendix && toc[i]->n1!=0 )
			{
				if (  toc[i]->n1>p2_apx_n1 )
				{	break;	/* r5pl6: Das waren dann alle */
				}
				
				if ( toc[i]->n1 == p2_apx_n1 )
				{
					if ( toc[i]->n2>p2_apx_n2 )
					{	break;	/* r5pl6: Das waren dann alle */
					}

					if ( toc[i]->n2==p2_apx_n2 )
					{
						if ( toc[i]->toctype==TOC_NODE3 )
						{	/* Ein Unterabschnitt */
						
							if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
							{	if (last_sssn)
								{	outln(toc_list_end);
									last_sssn= FALSE;
								}
								last_ssn= TRUE;
							}

							li= toc[i]->labindex;
							string2reference(ref, lab[li], TRUE, "", 0, 0);

							if (no_numbers)
							{	sprintf(n, form_a3_n3, ref);
							}
							else
							{	sprintf(n, form_a3_n3, 'A'-1+toc[i]->nr1, toc[i]->nr2, toc[i]->nr3, ref);
							}

							tocline_handle_1st(&first);
							outln(n);
							output_done= TRUE;
						}/* TOC_NODE3 */

						if (depth>1)
						{	if ( toc[i]->toctype==TOC_NODE4 )
							{	/* Ein Paragraph */

								if (use_toc_list_commands)	/* r6pl2: vorher: desttype==TOHTM */
								{	if (last_ssn)
									{	outln(toc_list_top);
										last_ssn= FALSE;
									}
									last_sssn= TRUE;
								}

								li= toc[i]->labindex;
								string2reference(ref, lab[li], TRUE, "", 0, 0);

								if (no_numbers)
								{	sprintf(n, form_a3_n4, ref);
								}
								else
								{	sprintf(n, form_a3_n4,
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
					}
				}
			}
		}
	}

	if (output_done)
	{	switch(desttype)
		{
			case TOHTM:
			case TOMHH:
				if (last_sssn)	outln(toc_list_end);
				outln(toc_list_end);
				outln(HTML_BR);
				break;
			case TOTEX:
			case TOPDL:
				if (last_sssn)	outln(toc_list_end);
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
}	/*subsubapx_output*/


LOCAL void subsubsubtoc_output ( void )
{
	register int i;
	int li;
	char	n[512], ref[512];
	BOOLEAN output_done= FALSE;
	BOOLEAN first= TRUE;
	BOOLEAN old;
	
	if (desttype==TOLYX)
	{	return;
	}

	if ( p1_toc_counter<=0 )
	{	return;
	}

	if ( toc[p2_toc_counter]->ignore_subtoc )	/* r5pl6 */
	{	return;
	}
	
	if ( last_n2_index==0 )	/* r5pl6 */
	{	return;				/* Wer benutzt !subsubsubtoc in einem Node? */
	}

	if ( last_n3_index==0 )	/* r5pl6 */
	{	return;				/* Wer benutzt !subsubsubtoc in einem Subnode? */
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

			if ( toc[i]->appendix )
			{	break;	/* r5pl6: Nach dem ersten Anhang-Node kommt nichts mehr */
			}
			
			if ( toc[i]->n1>p2_toc_n1 )
			{	break;	/* r5pl6: Das waren dann alle */
			}

			if ( toc[i]->n1!=0 )
			{
				if ( toc[i]->n1 == p2_toc_n1 )
				{
					if ( toc[i]->n2>p2_toc_n2 )
					{	break;	/* r5pl6: Das waren dann alle */
					}
					
					if ( toc[i]->n2==p2_toc_n2 )
					{
						if ( toc[i]->n3>p2_toc_n3 )
						{	break;	/* r5pl6: Das waren dann alle */
						}
						
						if ( toc[i]->n3==p2_toc_n3 )
						{
							if ( toc[i]->toctype==TOC_NODE4 )
							{	/* Ein Paragraph */

								li= toc[i]->labindex;
								string2reference(ref, lab[li], TRUE, "", 0, 0);

								if (no_numbers)
								{	sprintf(n, form_t4_n4, ref);
								}
								else
								{	sprintf(n, form_t4_n4,
										toc[i]->nr1+toc_offset,
										toc[i]->nr2+subtoc_offset,
										toc[i]->nr3+subsubtoc_offset,
										toc[i]->nr4+subsubsubtoc_offset,
										ref);
								}

								tocline_handle_1st(&first);
								outln(n);
								output_done= TRUE;
							}/* TOC_NODE4 */
						}
					}
				}
			}
		}
	}

	if (output_done)
	{	switch(desttype)
		{
			case TOHTM:
			case TOMHH:
				outln(toc_list_end);
				outln(HTML_BR);
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
}	/*subsubsubtoc_output*/


LOCAL void subsubsubapx_output ( void )
{
	register int i;
	int li;
	char	n[512], ref[512];
	BOOLEAN output_done= FALSE;
	BOOLEAN first= TRUE;
	BOOLEAN old;

	if (desttype==TOLYX)
	{	return;
	}

	if ( p1_toc_counter<=0 )
	{	return;
	}

	if ( toc[p2_toc_counter]->ignore_subtoc )	/* r5pl6 */
	{	return;
	}

	if ( last_n2_index==0 )	/* r5pl6 */
	{	return;				/* Wer benutzt !subsubsubtoc in einem Node? */
	}

	if ( last_n3_index==0 )	/* r5pl6 */
	{	return;				/* Wer benutzt !subsubsubtoc in einem Subnode? */
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

			if ( toc[i]->appendix && toc[i]->n1!=0 )
			{
				if (  toc[i]->n1>p2_apx_n1 )
				{	break;	/* r5pl6: Das waren dann alle */
				}
				
				if ( toc[i]->n1 == p2_apx_n1 )
				{
					if ( toc[i]->n2>p2_apx_n2 )
					{	break;	/* r5pl6: Das waren dann alle */
					}

					if ( toc[i]->n2==p2_apx_n2 )
					{
						if ( toc[i]->n3>p2_apx_n3 )
						{	break;	/* r5pl6: Das waren alle */
						}
						
						if ( toc[i]->n3==p2_apx_n3 )
						{
							if ( toc[i]->toctype==TOC_NODE4 )
							{	/* Ein Paragraph */

								li= toc[i]->labindex;
								string2reference(ref, lab[li], TRUE, "", 0, 0);

								if (no_numbers)
								{	sprintf(n, form_a4_n4, ref);
								}
								else
								{	sprintf(n, form_a4_n4,
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
						}
					}
				}
			}
		}
	}

	if (output_done)
	{	switch(desttype)
		{
			case TOHTM:
			case TOMHH:
				outln(toc_list_end);
				outln(HTML_BR);
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
}	/*subsubsubapx_output*/



LOCAL void do_toc ( const int depth )
{
	if (desttype==TORTF)
	{	return;
	}

	toc_output(depth);

	if (apx_available)
	{	output_appendix_line();	/*r6pl2*/
		apx_output(depth);
	}

}	/* do_toc */


LOCAL void do_subtoc ( const int depth )
{
	if (desttype==TORTF)
	{	return;
	}
	(bInsideAppendix) ? subapx_output(depth) : subtoc_output(depth);
}	/* do_subtoc */


LOCAL void do_subsubtoc ( const int depth )
{
	if (desttype==TORTF)
	{	return;
	}
	(bInsideAppendix) ? subsubapx_output(depth) : subsubtoc_output(depth);
}	/* do_subtoc */

LOCAL void do_subsubsubtoc ( void )
{
	if (desttype==TORTF)
	{	return;
	}
	(bInsideAppendix) ? subsubsubapx_output() : subsubsubtoc_output();
}	/* do_subtoc */


LOCAL void do_toptoc ( const int currdepth )
{
	char s[512], sIndent[512], sTarget[64], sFile[64];

	if (!use_auto_toptocs)
	{	return;
	}

	if (html_merge_node1 )
	{	return;
	}

	if (html_merge_node2 && currdepth>=TOC_NODE2 )
	{	return;
	}

	if (html_merge_node3 && currdepth>=TOC_NODE3 )
	{	return;
	}

	if (html_merge_node4 && currdepth>=TOC_NODE4 )
	{	return;
	}

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
			if (no_images || no_auto_toptocs_icons)
			{	strcpy(sIndent, "&nbsp;");
			}
			else
			{	sprintf(sIndent, "<img src=\"%s\" width=\"%u\" height=\"%u\">", GIF_FS_NAME, uiGifFsWidth, uiGifFsHeight);
			}

			if (html_frames_layout)
			{	sprintf(sTarget, " target=\"%s\"", FRAME_NAME_CON);
				sprintf(sFile, "%s%s", html_name_prefix, FRAME_FILE_CON);
			}
			else
			{	sTarget[0]= EOS;
				strcpy(sFile, old_outfile.name);
			}

			if (currdepth>=TOC_NODE1)
			{
				if (titdat.htmltitle!=NULL)
				{	strcpy(s, titdat.htmltitle);
				}
				else
				{	strcpy(s, titleprogram);
				}

				if (no_images)
				{	voutlnf("<tt>+&nbsp;</tt>&nbsp;<a href=\"%s%s\"%s>%s</a>",
						sFile, outfile.suff, sTarget, s);
				}
				else
				{	voutlnf("<img src=\"%s\" width=\"%u\" height=\"%u\">&nbsp;<a href=\"%s%s\"%s>%s</a>",
						GIF_FO_NAME, uiGifFoWidth, uiGifFoHeight, sFile, outfile.suff, sTarget, s);
				}
			}
			if (currdepth>=TOC_NODE2 && last_n1_index>0)
			{	strcpy(s, toc[last_n1_index]->name);
				auto_references(s, TRUE, "", 0, 0);
				if (no_images)
				{	voutlnf("<br><tt>|--+&nbsp;</tt>&nbsp;%s", s);
				}
				else
				{	voutlnf("<br>%s<img src=\"%s\" width=\"%u\" height=\"%u\">&nbsp;%s",
						sIndent, GIF_FO_NAME, uiGifFoWidth, uiGifFoHeight, s);
				}
			}
			if (currdepth>=TOC_NODE3 && last_n2_index>0)
			{	strcpy(s, toc[last_n2_index]->name);
				auto_references(s, TRUE, "", 0, 0);
				if (no_images)
				{	voutlnf("<br><tt>&nbsp;&nbsp;&nbsp;|--+&nbsp;</tt>&nbsp;%s", s);
				}
				else
				{	voutlnf("<br>%s%s<img src=\"%s\" width=\"%u\" height=\"%u\">&nbsp;%s",
						sIndent, sIndent, GIF_FO_NAME, uiGifFoWidth, uiGifFoHeight, s);
				}
			}
			if (currdepth>=TOC_NODE4 && last_n3_index>0)
			{	strcpy(s, toc[last_n3_index]->name);
				auto_references(s, TRUE, "", 0, 0);
				if (no_images)
				{	voutlnf("<br><tt>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;|--+&nbsp;</tt>&nbsp;%s", s);
				}
				else
				{	voutlnf("<br>%s%s%s<img src=\"%s\" width=\"%u\" height=\"%u\">&nbsp;%s",
						sIndent, sIndent, sIndent, GIF_FO_NAME, uiGifFoWidth, uiGifFoHeight, s);
				}
			}
			outln(HTML_HR);
			break;
		
		case TOWIN:
		case TOWH4:
		case TOAQV:
			if (currdepth==TOC_NODE1)
			{	/* Hier muesste ein Verweis auf den ersten Node hin */
				/* Dies koennte das Inhaltsverzeichnis, die */
				/* Titelseite oder ein sonstiger erster Node sein!? */
				return;
			}
			if (currdepth>=TOC_NODE2 && last_n1_index>0)
			{	strcpy(s, toc[last_n1_index]->name);
				auto_references(s, TRUE, "", 0, 0);
				voutlnf("\\{bmc %s\\} %s", BMP_FO_NAME, s);
			}
			if (currdepth>=TOC_NODE3 && last_n2_index>0)
			{	strcpy(s, toc[last_n2_index]->name);
				auto_references(s, TRUE, "", 0, 0);
				voutlnf("\\par\\li400\\{bmc %s\\} %s", BMP_FO_NAME, s);
			}
			if (currdepth>=TOC_NODE4 && last_n3_index>0)
			{	strcpy(s, toc[last_n3_index]->name);
				auto_references(s, TRUE, "", 0, 0);
				voutlnf("\\par\\li800\\{bmc %s\\} %s", BMP_FO_NAME, s);
			}
			outln("\\par\\par");
			break;

		case TOSTG:
		case TOAMG:
			if (currdepth>=TOC_NODE1 && uses_tableofcontents)
			{
				if (!no_images && !no_auto_toptocs_icons)
				{	voutlnf("@image %s 1", IMG_FO_NAME);
				}
				voutlnf("   %s", lang.contents);
			}
			if (currdepth>=TOC_NODE2 && last_n1_index>0)
			{
				if (!no_images && !no_auto_toptocs_icons)
				{	voutlnf("@image %s 4", IMG_FO_NAME);
				}
				voutlnf("      %s", toc[last_n1_index]->name);
			}
			if (currdepth>=TOC_NODE3 && last_n2_index>0)
			{
				if (!no_images && !no_auto_toptocs_icons)
				{	voutlnf("@image %s 7", IMG_FO_NAME);
				}
				voutlnf("         %s", toc[last_n2_index]->name);
			}
			if (currdepth>=TOC_NODE4 && last_n3_index>0)
			{
				if (!no_images && !no_auto_toptocs_icons)
				{	voutlnf("@image %s 10", IMG_FO_NAME);
				}
				voutlnf("            %s", toc[last_n3_index]->name);
			}
			outln("");
			break;

		case TOPCH:
			if (currdepth>=TOC_NODE1 && (uses_tableofcontents || uses_maketitle))
			{	voutlnf("\001 \\#%s\\#", lang.contents);
			}
			if (currdepth>=TOC_NODE2 && last_n1_index>0)
			{	voutlnf("    \001 \\#%s\\#", toc[last_n1_index]->name);
			}
			if (currdepth>=TOC_NODE3 && last_n2_index>0)
			{	voutlnf("        \001 \\#%s\\#", toc[last_n2_index]->name);
			}
			if (currdepth>=TOC_NODE4 && last_n3_index>0)
			{	voutlnf("            \001 \\#%s\\#", toc[last_n3_index]->name);
			}
			output_ascii_line("-", zDocParwidth);
			break;
	}

}	/* do_toptoc */


LOCAL int get_toccmd_depth ( void )
{
	register int i;
	int ret;
	
	for (i=1; i<token_counter; i++)
	{
		if (strcmp(token[i], "!depth")==0)
		{
			if (i+1<token_counter)
			{	ret= atoi(token[i+1]);
				if (ret<=0)	ret= 9;
				if (ret>9)	ret= 9;
				return ret;
			}
		}
	}

	return 0;	/* bei 0 werden die Defaultwerte (z.B. subtocs1_depth) benutzt */

}	/* get_toccmd_depth */


GLOBAL void c_toc ( void )
{
	BOOLEAN flag= FALSE;
	int d;
	
	if ( is_for_desttype(&flag, "!toc") )
	{
		d= get_toccmd_depth();
		if (d==0)
		{	if (use_short_tocs)
			{	d=1;
			}
			else
			{	d=9;
			}
		}

		if (desttype==TOINF)
		{	d= 1;
		}
		do_toc(d);
	}
	
}	/* c_toc */


GLOBAL void c_subtoc ( void )
{
	BOOLEAN flag= FALSE;
	int d;
	
	/* token[0] enthaelt das !sub*toc-Kommando */
	if ( is_for_desttype(&flag, token[0]) )
	{
		switch (active_nodetype)
		{
			case TOC_NODE1:
				d= get_toccmd_depth();
				if (d==0)	d= subtocs1_depth;
				do_subtoc(d);
				break;
			case TOC_NODE2:
				d= get_toccmd_depth();
				if (d==0)	d= subtocs2_depth;
				do_subsubtoc(d);
				break;
			case TOC_NODE3:
				do_subsubsubtoc();
				break;
		}
	}

}	/* c_subtoc */


#if 0	/*	---------------------------------------------------------	*/
GLOBAL void c_subtoc ( void )
{
	BOOLEAN flag= FALSE;
	int d;
	
	if ( is_for_desttype(&flag, "!subtoc") )
	{
		d= get_toccmd_depth();
		if (d==0)	d= subtocs1_depth;
		do_subtoc(d);
	}
}	/* c_subtoc */

GLOBAL void c_subsubtoc ( void )
{
	BOOLEAN flag= FALSE;
	int d;
	
	if ( is_for_desttype(&flag, "!subsubtoc") )
	{
		d= get_toccmd_depth();
		if (d==0)	d= subtocs2_depth;
		do_subsubtoc(d);
	}
}	/* c_subsubtoc */


GLOBAL void c_subsubsubtoc ( void )
{
	BOOLEAN flag= FALSE;
	
	if ( is_for_desttype(&flag, "!subsubsubtoc") )
	{	do_subsubsubtoc();
	}
}	/* c_subsubsubtoc */
#endif	/*	---------------------------------------------------------	*/


GLOBAL void c_listoffigures ( void )
{
	check_endnode();
	
	switch(desttype)
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
}	/* c_listoffigures */


GLOBAL void c_listoftables ( void )
{
	check_endnode();
	
	switch(desttype)
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
}	/* c_listoftables */



LOCAL void output_appendix_line ( void )
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
			out("  ");	outln(lang.appendix);
			out("  ");	output_ascii_line("=", strlen(lang.appendix));
			outln("");
			break;
		case TOASC:
		case TOPCH:
			outln("");
			outln(lang.appendix);
			output_ascii_line("=", strlen(lang.appendix));
			outln("");
			break;
		case TODRC:	/* <???> */
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			voutlnf("{\\b %s}\\par\\pard\\par", lang.appendix);
			break;
		case TOHTM:
		case TOMHH:
			voutlnf("<h1>%s</h1>", lang.appendix);
			break;
		case TOTEX:	/* <???> */
		case TOPDL:	/* <???> */
			break;
	}
	
}	/* output_appendix_line */


GLOBAL void c_tableofcontents ( void )
{
	char	n[256], name[256], hlp_name[256];
	int		i;
	int 	depth;

	if (called_tableofcontents)
	{	return;
	}

	called_tableofcontents= TRUE;
	
	check_endnode();

	depth= get_toccmd_depth();	/*r6pl2*/
	if (depth==0)
	{	if (use_short_tocs)			/*r6pl5*/
		{	depth= 1;
		}
		else
		{	depth= 9;
		}
	}

	
	switch(desttype)
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
			outln("\\begin_inset LatexDel \\tableofcontents");
			outln("\\end_inset");
			break;
		case TOINF:
			outln("@ifinfo");
			n[0]= EOS;
			if (toc[1]!=NULL)
			{	strcpy(name, toc[1]->name);
				node2texinfo(name);
				sprintf(n, "@node Top, %s, (dir), (dir)", name);
			}
			output_helpid(0);
			outln(n);
			
			if (called_maketitle)
			{	if ( titdat.title!=NULL)	voutlnf("@center %s @*", titdat.title);
				if ( titdat.program!=NULL)	voutlnf("@center %s @*", titdat.program);
				if ( titdat.version!=NULL)	voutlnf("@center %s @*", titdat.version);
				if ( titdat.date!=NULL)		voutlnf("@center %s @*", titdat.date);
				if ( titdat.author!=NULL )
				{	outln("@sp 1");
					voutlnf("@center %s", lang.by);
					outln("@sp 1");
					voutlnf("@center %s @*", titdat.author);
				}
				if ( address_counter>0)
				{	for (i=1; i<=address_counter; i++)
					{	if (titdat.address[i]!=NULL)
						{	voutlnf("@center %s @*", titdat.address[i]);
						}
					}
				}
				outln("@center ");
				outln("@sp 1");
			}

			outln(lang.contents);
			outln("");			
			
			if (toc_available)
			{	toc_output(1);	/* immer 1 */
			}
			if (apx_available)
			{	output_appendix_line();
				apx_output(1);	/* immer 1 */
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
				{	voutlnf("@node Main \"%s - %s\"", titleprogram, lang.contents);
				}
				else
				{	voutlnf("@node Main \"%s\"", lang.contents);
				}
			}

			if (called_maketitle)
			{	voutlnf("@toc \"%s\"", lang.title);
			}
			output_helpid(0);
			stg_headline("", lang.contents);

			if (toc_available)
			{	toc_output(depth);
			}
			if (apx_available)
			{	output_appendix_line();
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
			out("  ");	outln(n);
			out("  ");	output_ascii_line("=", strlen(n));
			outln("");

			if (toc_available)
			{	toc_output(depth);
			}
			if (apx_available)
			{	output_appendix_line();
				apx_output(depth);
			}
			outln("");
			break;

		case TOASC:
			if (toc_available)
			{
				if (use_style_book)
				{	output_ascii_line("=", zDocParwidth);
					outln(lang.contents);
					output_ascii_line("=", zDocParwidth);
				}
				else
				{	outln(lang.contents);
					output_ascii_line("=", strlen(lang.contents));
				}
				
				outln("");
				toc_output(depth);
				outln("");
			}
			if (apx_available)
			{	output_appendix_line();
				apx_output(depth);
				outln("");
			}
			break;

		case TODRC:	/* <???> */
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
			
			if (!no_buttons)	/* r6pl8 */
			{	outln(win_browse);
			
				if (desttype==TOAQV)	/* r5pl6 */
				{	strcpy(hlp_name, "qchPath");
				}
				else
				{	sprintf(hlp_name, "`%s.hlp'", outfile.name);
				}
			
				if ( called_maketitle )
				{	outln("!{\\footnote ! EnableButton(\"BTN_UP\");");
					voutlnf("ChangeButtonBinding(\"BTN_UP\", \"JumpID(%s, `%s')\") }",
						hlp_name, WIN_TITLE_NODE_NAME);
				}
				else
				{	outln("!{\\footnote ! DisableButton(\"BTN_UP\") }");
				}
			}
			
			if (toc_available)
			{	outln("\\keepn");	/* r6pl11*/
				sprintf(n, "\\fs%d", iDocPropfontSize + 14);
				voutlnf("{%s\\b %s}\\par\\pard\\par", n, lang.contents);
				toc_output(depth);
			}

			if (apx_available)
			{	output_appendix_line();
				apx_output(depth);
			}

			outln("}\\page");
			break;

		case TOPCH:
			if (titdat.program!=NULL)
			{	voutlnf("screen(capsensitive(\"%s\"), capsensitive(\"%s\"))",
							titdat.program, lang.contents);
			}
			else
			{	voutlnf("screen(capsensitive(\"%s\"), capsensitive(\"%s\"))",
							lang.unknown, lang.contents);
			}
			output_helpid(0);
			pch_headline(lang.contents);
			outln("");
			if (uses_maketitle)
			{	pch_titlepage();
			}
			outln("");
			if (toc_available)
			{	outln(lang.contents);
				output_ascii_line("=", strlen(lang.contents));
				outln("");
				toc_output(depth);
			}
			if (apx_available)
			{	output_appendix_line();
				apx_output(depth);
			}
			outln("");
			outln("\\end");
			outln("");
			break;

		case TOHTM:
		case TOMHH:
			output_helpid(0);
			if (toc_available)
			{	voutlnf("<h1><a name=\"%s\">%s</a></h1>", HTML_LABEL_CONTENTS, lang.contents);
				toc_output(depth);
				outln(HTML_BR);
			}
			if (apx_available)
			{	output_appendix_line();
				apx_output(depth);
				outln(HTML_BR);
			}
			outln(HTML_BR);
			break;	/* r5pl4 */
		
		case TOKPS:
			/* New in r6pl15 [NHz] */
			if (toc_available)
			{	outln("newline");

				voutlnf("/NodeName (%s) def", lang.contents);
				voutlnf("20 changeFontSize (%s) udoshow newline %d changeFontSize", lang.contents, laydat.propfontsize); /* Changed in r6pl15 [NHz] */
				toc_output(depth);
			}

			if (apx_available)
			{	output_appendix_line();
				apx_output(depth);
			}
			
			if (toc_available)
				c_newpage();

/*			check_endnode();

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
	
}	/*c_tableofcontents*/




/*	############################################################
	#
	# Ein Label im zweiten Durchgang ausgeben
	#
	############################################################	*/
GLOBAL void c_label ( void )
{
	char 	sLabel[512], sTemp[512];

	/* Tokens umkopieren */
	tokcpy2(sLabel, 512);

	if (sLabel[0]==EOS)
	{	error_missing_parameter(CMD_LABEL);
		return;
	}

	p2_lab_counter++;	/*r6pl2*/

	replace_udo_quotes(sLabel);
	convert_tilde(sLabel);
	
	switch(desttype)
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
			{	voutlnf("@symbol ari \"%s\"", sLabel);
			}
			else
			{	voutlnf("@symbol ar \"%s\"", sLabel);
			}
			break;
		case TOHTM:
		case TOMHH:
			label2html(sLabel);							/* r6pl2 */
			voutlnf("<a name=\"%s\"></a>", sLabel);		/* r5pl14 */
			break;
		case TOLDS:
			voutlnf("<label id=\"%s\">", sLabel);
			break;
		case TOWIN:
		case TOWH4:
		case TOAQV:
			if (use_label_inside_index && !no_index)	/* r5pl10 */
			{	voutf("K{\\footnote K %s}", sLabel);
			}
			if (bDocWinOldKeywords)
			{	strcpy(sTemp, sLabel);
				del_internal_styles(sTemp);
				node2winhelp(sTemp);
				voutlnf("#{\\footnote # %s}", sTemp);
			}
			label2NrWinhelp(sLabel, p2_lab_counter);
			voutf("#{\\footnote # %s}", sLabel);
			break;
		case TORTF:
			if (use_label_inside_index && !no_index)	/* r6pl6 */
			{	voutf("{\\xe\\v %s}", sLabel);
			}
			break;

		/* New in r6pl15 [NHz] */
		case TOKPS:
			node2postscript(sLabel, FALSE);
			voutlnf("/%s NameDest", sLabel);
			/* Must be changed if (!label ...) is possible */
			break;
	}

}	/* c_label */


GLOBAL void c_alias ( void )
{
	p2_lab_counter++;	/*r6pl2*/
}	/* c_alias */


/*	############################################################
	#
	# Ein Label der internen Liste hinzufuegen
	# label:	String
	# isn:		TRUE: Ein Kapitel, FALSE: nur Label
	# isp:		TRUE: Ein Popup
	# tocindex:	Position des Labels in toc[]
	#
	############################################################	*/
GLOBAL int add_label ( const char *label, const BOOLEAN isn, const BOOLEAN isp )
{
	LABEL	*labptr;

	/* r5pl6: Labels werden nun bei allen Formaten eingefuegt, da	*/
	/* sonst *toc_output() falsche Ergebnisse liefert, da dort		*/
	/* ueber den Label-Index direkt referenziert wird.				*/
	
	if (p1_lab_counter+1>=MAXLABELS)	/* Noch Platz in der Liste? */
	{	error_too_many_label();
		return FALSE;
	}

	/* rel6pl2: Leeres Label abweisen */
#if 1
	if (label[0]==EOS)
	{	return FALSE;
	}
#endif
	
	labptr= (LABEL *) um_malloc(sizeof(LABEL)+1);
	
	if (labptr==NULL)					/* Kein Speicher mehr frei? */
	{	error_malloc_failed();
		return FALSE;
	}

	/* New in r6pl15 [NHz] */

	/* Set label in project file */

	if(!isn) /* Only labels which aren't nodes */

		save_upr_entry_label (sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine );

	p1_lab_counter++;
	lab[p1_lab_counter]= labptr;
	
	strcpy( labptr->name, label);
	replace_udo_quotes(labptr->name);
	labptr->len= strlen(labptr->name);	/* r5pl10 */

	labptr->labindex= p1_lab_counter;	/* r6pl2 */
	labptr->is_node= isn;
	labptr->is_alias= FALSE;
	labptr->is_popup= isp;

	labptr->tocindex= p1_toc_counter;
	labptr->ignore_links= FALSE;
	labptr->ignore_index= FALSE;
	labptr->referenced= FALSE;			/* r6pl9 */

	if (pflag[PASS1].inside_apx)
	{	labptr->appendix= TRUE;
		labptr->n1= p1_apx_n1;
		labptr->n2= p1_apx_n2;
		labptr->n3= p1_apx_n3;
		labptr->n4= p1_apx_n4;
	}
	else
	{	labptr->appendix= FALSE;
		labptr->n1= p1_toc_n1;
		labptr->n2= p1_toc_n2;
		labptr->n3= p1_toc_n3;
		labptr->n4= p1_toc_n4;
	}

	return p1_lab_counter;

}	/* add_label */



/*	############################################################
	#
	# Einen Alias der internen Liste hinzufuegen
	# Ein Alias ist ein Zweitname (Drittname, ...) eines Nodes
	#
	############################################################	*/
GLOBAL BOOLEAN add_alias ( const char *alias, const BOOLEAN isp )
{
	LABEL	*labptr;

	/* r5pl9: Aliase fuer alle Formate sichern */

	if (p1_lab_counter+1>=MAXLABELS)	/* Noch Platz in der Liste? */
	{	error_too_many_alias();
		return FALSE;
	}
	
	/* rel6pl2: Leeren Alias abweisen */
#if 1
	if (alias[0]==EOS)
	{	return FALSE;
	}
#endif

	labptr= (LABEL *) um_malloc(sizeof(LABEL)+1);
	
	if (labptr==NULL)					/* Kein Speicher mehr frei? */
	{	error_malloc_failed();
		return FALSE;
	}

	/* New in r6pl15 [NHz] */

	/* Set alias in project file */

	save_upr_entry_alias (sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine );

	p1_lab_counter++;
	lab[p1_lab_counter]= labptr;
	
	strcpy( labptr->name, alias);
	replace_udo_quotes(labptr->name);
	labptr->len= strlen(labptr->name);	/* r5pl10 */

	labptr->labindex= p1_lab_counter;	/* r6pl2 */
	labptr->is_node= FALSE;
	labptr->is_alias= TRUE;
	labptr->is_popup= isp;

	labptr->tocindex= p1_toc_counter;
	labptr->ignore_links= FALSE;
	labptr->ignore_index= FALSE;
	labptr->referenced= FALSE;			/* r6pl9 */

	if (pflag[PASS1].inside_apx)
	{	labptr->appendix= TRUE;
		labptr->n1= p1_apx_n1;
		labptr->n2= p1_apx_n2;
		labptr->n3= p1_apx_n3;
		labptr->n4= p1_apx_n4;
	}
	else
	{	labptr->appendix= FALSE;
		labptr->n1= p1_toc_n1;
		labptr->n2= p1_toc_n2;
		labptr->n3= p1_toc_n3;
		labptr->n4= p1_toc_n4;
	}

	return TRUE;

}	/* add_alias */


/*	############################################################
	#
	# Inhaltsverzeichnis erweitern
	#
	############################################################	*/
GLOBAL void set_ignore_headline ( void )	/* r5pl12 */
{
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	
	toc[p1_toc_counter]->ignore_headline= TRUE;
	
}	/* set_ignore_headline */


GLOBAL void set_ignore_bottomline ( void )	/* r6pl10 */
{
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	
	toc[p1_toc_counter]->ignore_bottomline= TRUE;
	
}	/* set_ignore_bottomline */


GLOBAL void set_raw_header_filename ( void )
{
	char *ptr, s[512];
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;
	
	strcpy(s, token[1]);

	if (p1_toc_counter==0)
	{
		strcpy(sDocRawHeaderFilename, s);
	}
	else
	{
		ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));
		if (!ptr)
		{	error_malloc_failed();
			bFatalErrorDetected= TRUE;
		}
		else
		{
			strcpy(ptr, s);
			toc[p1_toc_counter]->raw_header_filename= ptr;
		}
	}

}	/* set_raw_header_filename */


GLOBAL void set_raw_footer_filename ( void )
{
	char *ptr, s[512];
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;
	
	strcpy(s, token[1]);

	if (p1_toc_counter==0)
	{
		strcpy(sDocRawFooterFilename, s);
	}
	else
	{
		ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));
		if (!ptr)
		{	error_malloc_failed();
			bFatalErrorDetected= TRUE;
		}
		else
		{
			strcpy(ptr, s);
			toc[p1_toc_counter]->raw_footer_filename= ptr;
		}
	}

}	/* set_raw_footer_filename */


GLOBAL void set_ignore_raw_header ( void )	/* r6pl10 */
{
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	
	toc[p1_toc_counter]->ignore_raw_header= TRUE;
	
}	/* set_ignore_raw_header */


GLOBAL void set_ignore_raw_footer ( void )	/* r6pl10 */
{
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	
	toc[p1_toc_counter]->ignore_raw_footer= TRUE;
	
}	/* set_ignore_raw_footer */


GLOBAL void set_ignore_footer ( void )	/* r6pl2 */
{
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	
	toc[p1_toc_counter]->ignore_footer= TRUE;
	
}	/* set_ignore_footer */


GLOBAL void set_ignore_title ( void )	/* r6pl13 */
{
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	
	toc[p1_toc_counter]->ignore_title= TRUE;
	
}	/* set_ignore_title */

GLOBAL void set_ignore_links ( void )	/* r5pl8 */
{
	int li;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	
	toc[p1_toc_counter]->ignore_links= TRUE;
	
	li= toc[p1_toc_counter]->labindex;

	if (li>0)
	{	lab[li]->ignore_links= TRUE;
	}
	
}	/* set_ignore_links */


GLOBAL void set_ignore_index ( void )	/* r5pl10 */
{
	int li;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	
	toc[p1_toc_counter]->ignore_index= TRUE;
	
	li= toc[p1_toc_counter]->labindex;

	if (li>0)
	{	lab[li]->ignore_index= TRUE;
	}
	
}	/* set_ignore_index */


GLOBAL void set_ignore_subtoc ( void )	/* r5pl6 */
{

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	
	toc[p1_toc_counter]->ignore_subtoc= TRUE;
	
}	/* set_ignore_subtoc */


GLOBAL void set_helpid ( void )
{
	char id[512], *ptr;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	strcpy(id, token[1]);
	
	/* <???> Hier pruefen, ob nur A-Z, a-z, 0-9 und _ benutzt werden */

	ptr= (char *) um_malloc(1+strlen(id)*sizeof(char));
	
	if (!ptr)
	{	error_malloc_failed();
		bFatalErrorDetected= TRUE;
	}
	else
	{	strcpy(ptr, id);
		toc[p1_toc_counter]->helpid= ptr;
	}

	bUseIdMapFileC= TRUE;	/* r6pl8: bei Verwendung auch die Datei erzeugen! */

}	/* set_helpid */


GLOBAL void set_mapping ( void )
{
	char map[512];
	int m;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	strcpy(map, token[1]);

	/* <???> Hier pruefen, ob nur 0-9 benutzt wird */

	m= atoi(token[1]);

	if (m>=0)
	{
		toc[p1_toc_counter]->mapping= m;
		bUseIdMapFileC= TRUE;	/* r6pl8: bei Verwendung auch die Datei erzeugen! */
	}
	else
	{
		error_wrong_mapping();
	}

}	/* set_mapping */


/* New in r6pl16 [NHz] */
GLOBAL void set_html_doctype ( void )
{
	char s[512];

	tokcpy2(s, 512);

	if (strcmp(s, "Old")==0)
	{	html_doctype= HTML_OLD;
	}

	if (strcmp(s, "Strict")==0)
	{	html_doctype= HTML_STRICT;
	}

	if (strcmp(s, "Transitional")==0)
	{	html_doctype= HTML_TRANS;
	}

	if (strcmp(s, "XHTML Strict")==0)
	{	html_doctype= XHTML_STRICT;
	}

	if (strcmp(s, "XHTML Transitional")==0)
	{	html_doctype= XHTML_TRANS;
	}

}	/* set_html_doctype */


GLOBAL void set_html_frames_layout ( void )
{
	char s[512];

	html_frames_layout= TRUE;

	tokcpy2(s, 512);

	if (strstr(s, "noresize")!=NULL)
	{	html_frames_noresize= TRUE;
	}

	if (strstr(s, "noborder")!=NULL)
	{	html_frames_noborder= TRUE;
	}

	if (strstr(s, "noscrolling")!=NULL)
	{	html_frames_noscroll= TRUE;
	}

}	/* set_html_frames_layout */


GLOBAL void set_html_counter_command ( void )
{
	char k[512], *ptr;

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	tokcpy2(k, 512);

	ptr= (char *) um_malloc(1+strlen(k)*sizeof(char));
	
	if (!ptr)
	{	error_malloc_failed();
		bFatalErrorDetected= TRUE;
	}
	else
	{	strcpy(ptr, k);
		toc[p1_toc_counter]->counter_command= ptr;
	}
	
}	/* set_html_counter_command */


GLOBAL void set_html_filename ( void )
{
	char *ptr;
	
	if (desttype!=TOHTM)	return;

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;
	
	fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);

	ptr= toc[p1_toc_counter]->filename;
	ptr[0]= EOS;
	/* Nur den Dateinamen benutzen, nicht den Pfad! */
	strncat(ptr, tmp_name, MAX_FILENAME_LEN);

	/* New in r6pl16 [NHz] */
	if(strcmp(tmp_suff, ""))
		strncat(ptr, tmp_suff, 6);

}	/* set_html_filename */


GLOBAL void set_html_filename_prefix ( void )
{
	if (desttype!=TOHTM)	return;

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;
	
	strcpy(html_name_prefix, token[1]);

}	/* set_html_filename_prefix */


GLOBAL void set_html_dirname ( void )
{
	char *ptr;
	
	if (desttype!=TOHTM)	return;

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;
	
	fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);

	if (tmp_path[0]==EOS && tmp_name[0]!=EOS)
	{	strcpy(tmp_path, tmp_name);
	}

	if (tmp_path[0]!=EOS)
	{	ptr= toc[p1_toc_counter]->dirname;
		ptr[0]= EOS;
		strncat(ptr, tmp_name, MAX_FILENAME_LEN);
	}

}	/* set_html_dirname */


GLOBAL void set_html_switch_language ( void )
{
	if (desttype!=TOHTM && desttype!=TOMHH)
	{	return;
	}

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	iDocHtmlSwitchLanguage= -1;
	sDocHtmlSwitchLanguage[0]= EOS;

	if (strstr(token[1], "german"))
	{	iDocHtmlSwitchLanguage= TOGER;
	}	else
	if (strstr(token[1], "english"))
	{	iDocHtmlSwitchLanguage= TOENG;
	}

	if (iDocHtmlSwitchLanguage>=0)
	{
		token[1][0]= EOS;
		tokcpy2(sDocHtmlSwitchLanguage, 256);
	}

}	/* set_html_switch_language */


GLOBAL void set_html_color ( const int which )
{
	char color[256], *ptr;
	BOOLEAN ret;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	color[0]= EOS;

	qdelete_once(token[1], "[", 1);
	qdelete_last(token[1], "]", 1);

	if (token[1][0]=='#')
	{	strcpy(color, token[1]);
		ret= TRUE;
	}
	else
	{	ret= get_html_color(token[1], color);
	}

	if (ret)
	{
		if (p1_toc_counter==0)
		{
			ptr= sDocBackColor;	/* default */
			switch (which)
			{
				case HTML_COLOR_BACK:	ptr= sDocBackColor;		break;
				case HTML_COLOR_TEXT:	ptr= sDocTextColor;		break;
				case HTML_COLOR_LINK:	ptr= sDocLinkColor;		break;
				case HTML_COLOR_ALINK:	ptr= sDocAlinkColor;	break;
				case HTML_COLOR_VLINK:	ptr= sDocVlinkColor;	break;
			}
		}
		else
		{
			ptr= toc[p1_toc_counter]->backcolor;
			switch (which)
			{
				case HTML_COLOR_BACK:	ptr= toc[p1_toc_counter]->backcolor;	break;
				case HTML_COLOR_TEXT:	ptr= toc[p1_toc_counter]->textcolor;	break;
				case HTML_COLOR_LINK:	ptr= toc[p1_toc_counter]->linkcolor;	break;
				case HTML_COLOR_ALINK:	ptr= toc[p1_toc_counter]->alinkcolor;	break;
				case HTML_COLOR_VLINK:	ptr= toc[p1_toc_counter]->vlinkcolor;	break;
			}
		}
		ptr[0]= EOS;
		if (color[0]!=EOS)
		{	strncat(ptr, color, MAX_COLOR_LEN);
		}
	}
	else
	{	error_unknown_color(token[1]);
	}

}	/* set_html_color */


#if 0
GLOBAL void set_html_backcolor ( void )
{
	char color[256], *ptr;
	BOOLEAN ret;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	color[0]= EOS;

	qdelete_once(token[1], "[", 1);
	qdelete_last(token[1], "]", 1);

	if (token[1][0]=='#')
	{	strcpy(color, token[1]);
		ret= TRUE;
	}
	else
	{	ret= get_html_color(token[1], color);
	}

	if (ret)
	{	if (p1_toc_counter==0)
		{	ptr= sDocBackColor;
		}
		else
		{	ptr= toc[p1_toc_counter]->backcolor;
		}
		ptr[0]= EOS;
		if (color[0]!=EOS)
		{	strncat(ptr, color, MAX_COLOR_LEN);
		}
	}
	else
	{	error_unknown_color(token[1]);
	}

}	/* set_html_backcolor */


GLOBAL void set_html_textcolor ( void )
{
	char color[256], *ptr;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	color[0]= EOS;

	qdelete_once(token[1], "[", 1);
	qdelete_last(token[1], "]", 1);

	if (token[1][0]=='#')
	{	strcpy(color, token[1]);
	}
	else
	{	get_html_color(token[1], color);
	}

	if (color[0]!=EOS)
	{
		if (p1_toc_counter==0)
		{	ptr= sDocTextColor;
		}
		else
		{	ptr= toc[p1_toc_counter]->textcolor;
		}
		ptr[0]= EOS;
		strncat(ptr, color, MAX_COLOR_LEN);
	}
}


GLOBAL void set_html_linkcolor ( void )
{
	char color[256], *ptr;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	color[0]= EOS;

	qdelete_once(token[1], "[", 1);
	qdelete_last(token[1], "]", 1);

	if (token[1][0]=='#')
	{	strcpy(color, token[1]);
	}
	else
	{	get_html_color(token[1], color);
	}

	if (color[0]!=EOS)
	{
		if (p1_toc_counter==0)
		{	ptr= sDocLinkColor;
		}
		else
		{	ptr= toc[p1_toc_counter]->linkcolor;
		}
		ptr[0]= EOS;
		strncat(ptr, color, MAX_COLOR_LEN);
	}
}

GLOBAL void set_html_alinkcolor ( void )
{
	char color[256], *ptr;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	color[0]= EOS;

	qdelete_once(token[1], "[", 1);
	qdelete_last(token[1], "]", 1);

	if (token[1][0]=='#')
	{	strcpy(color, token[1]);
	}
	else
	{	get_html_color(token[1], color);
	}

	if (color[0]!=EOS)
	{
		if (p1_toc_counter==0)
		{	ptr= sDocAlinkColor;
		}
		else
		{	ptr= toc[p1_toc_counter]->alinkcolor;
		}
		ptr[0]= EOS;
		strncat(ptr, color, MAX_COLOR_LEN);
	}
}

GLOBAL void set_html_vlinkcolor ( void )
{
	char color[256], *ptr;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	color[0]= EOS;

	qdelete_once(token[1], "[", 1);
	qdelete_last(token[1], "]", 1);

	if (token[1][0]=='#')
	{	strcpy(color, token[1]);
	}
	else
	{	get_html_color(token[1], color);
	}

	if (color[0]!=EOS)
	{
		if (p1_toc_counter==0)
		{	ptr= sDocVlinkColor;
		}
		else
		{	ptr= toc[p1_toc_counter]->vlinkcolor;
		}
		ptr[0]= EOS;
		strncat(ptr, color, MAX_COLOR_LEN);
	}
}	/* set_html_vlinkcolor */
#endif



GLOBAL void set_html_backimage ( void )
{
	char *ptr, *dest;
	char sTemp[512];

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	if (p1_toc_counter==0)
	{	dest= sDocBackImage;
	}
	else
	{	dest= toc[p1_toc_counter]->backimage;
	}


	if (token[1][0]=='\"')
	{
		tokcpy2(sTemp, 512);
		ptr= strchr(sTemp+1, '\"');		/* zweites " suchen */

		if (ptr)
		{	ptr[0]= EOS;
			strcpy(dest, sTemp+1);
		}
		else
		{	strcpy(dest, sTemp);
		}
	}
	else
	{
		strcpy(dest, token[1]);
	}

	/* dest[0]= EOS;	*/
	/* strncat(dest, sTemp, MAX_IMAGE_LEN);	*/

	/* Hier muessen immer / benutzt werden! */
	replace_char(dest, "\\", "/");

}	/* set_html_backimage */



/* New in r6pl15 [NHz] */
GLOBAL void set_html_style ( void )
{
	char *ptr, *dest;
	char sTemp[512];

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	if (p1_toc_counter==0)
	{	dest= sDocStyle;
	}
	else
	{	dest= toc[p1_toc_counter]->style_name;
	}


	if (token[1][0]=='\"')
	{
		tokcpy2(sTemp, 512);
		ptr= strchr(sTemp+1, '\"');		/* zweites " suchen */

		if (ptr)
		{	ptr[0]= EOS;
			strcpy(dest, sTemp+1);
		}
		else
		{	strcpy(dest, sTemp);
		}
	}
	else
	{
		strcpy(dest, token[1]);
	}

	/* dest[0]= EOS;	*/
	/* strncat(dest, sTemp, MAX_IMAGE_LEN);	*/

	/* Hier muessen immer / benutzt werden! */
	replace_char(dest, "\\", "/");

}	/* set_html_style */


/* New in r6pl15 [NHz] */
GLOBAL void set_html_script ( void )
{
	char *ptr, *dest;
	char sTemp[512];

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	if (p1_toc_counter==0)
	{	dest= sDocScript;
	}
	else
	{	dest= toc[p1_toc_counter]->script_name;
	}


	if (token[1][0]=='\"')
	{
		tokcpy2(sTemp, 512);
		ptr= strchr(sTemp+1, '\"');		/* zweites " suchen */

		if (ptr)
		{	ptr[0]= EOS;
			strcpy(dest, sTemp+1);
		}
		else
		{	strcpy(dest, sTemp);
		}
	}
	else
	{
		strcpy(dest, token[1]);
	}

	/* dest[0]= EOS;	*/
	/* strncat(dest, sTemp, MAX_IMAGE_LEN);	*/

	/* Hier muessen immer / benutzt werden! */
	replace_char(dest, "\\", "/");

}	/* set_html_script */



/* New in r6pl15 [NHz] */
GLOBAL void set_html_favicon ( void )
{
	char *ptr, *dest;
	char sTemp[512];

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	if (p1_toc_counter==0)
	{	dest= sDocFavIcon;
	}
	else
	{	dest= toc[p1_toc_counter]->favicon_name;
	}


	if (token[1][0]=='\"')
	{
		tokcpy2(sTemp, 512);
		ptr= strchr(sTemp+1, '\"');		/* zweites " suchen */

		if (ptr)
		{	ptr[0]= EOS;
			strcpy(dest, sTemp+1);
		}
		else
		{	strcpy(dest, sTemp);
		}
	}
	else
	{
		strcpy(dest, token[1]);
	}

	/* dest[0]= EOS;	*/
	/* strncat(dest, sTemp, MAX_IMAGE_LEN);	*/

	/* Hier muessen immer / benutzt werden! */
	replace_char(dest, "\\", "/");

}	/* set_html_favicon */


GLOBAL void set_html_keywords ( void )
{
#define HTML_KW_SIZE    2048
	char k[HTML_KW_SIZE], *ptr, oldk[HTML_KW_SIZE], *oldptr; /* Buffer increased from 1kB to 2kB */
	size_t newsize;

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	tokcpy2(k, HTML_KW_SIZE);
	c_vars(k);
	qdelete_all(k, "!-", 2);

	auto_quote_chars(k, TRUE);
	replace_udo_quotes(k);

	if (toc[p1_toc_counter]->keywords!=NULL)
	{	/* r6pl5: Keywords bereits vorhanden, neue anhaengen */
		oldptr= toc[p1_toc_counter]->keywords;
		strcpy(oldk, oldptr);
		newsize= strlen(oldk) + strlen(k) + 3;

		ptr= (char *) realloc(oldptr, newsize);
		if (!ptr)
		{	error_malloc_failed();
			bFatalErrorDetected= TRUE;
		}
		else
		{	
			sprintf(ptr, "%s, %s", oldk, k);
			toc[p1_toc_counter]->keywords= ptr;
		}
	}
	else
	{	ptr= (char *) um_malloc(1+strlen(k)*sizeof(char));
	
		if (!ptr)
		{	error_malloc_failed();
			bFatalErrorDetected= TRUE;
		}
		else
		{	strcpy(ptr, k);
			toc[p1_toc_counter]->keywords= ptr;
		}
	}
	
}	/* set_html_keyword */


GLOBAL void set_html_description ( void )
{
	char d[1024], *ptr, oldd[1024], *oldptr;
	size_t newsize;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	tokcpy2(d, 1024);
	c_vars(d);
	qdelete_all(d, "!-", 2);

	auto_quote_chars(d, TRUE);
	replace_udo_quotes(d);

	if (toc[p1_toc_counter]->description!=NULL)
	{	/* r6pl5: description bereits vorhanden, neue anhaengen */
		oldptr= toc[p1_toc_counter]->description;
		strcpy(oldd, oldptr);
		newsize= strlen(oldd) + strlen(d) + 2;

		ptr= (char *) realloc(oldptr, newsize);
		if (!ptr)
		{	error_malloc_failed();
			bFatalErrorDetected= TRUE;
		}
		else
		{	
			sprintf(ptr, "%s %s", oldd, d);
			toc[p1_toc_counter]->description= ptr;
		}
	}
	else
	{	ptr= (char *) um_malloc(1+strlen(d)*sizeof(char));
	
		if (!ptr)
		{	error_malloc_failed();
			bFatalErrorDetected= TRUE;
		}
		else
		{	strcpy(ptr, d);
			toc[p1_toc_counter]->description= ptr;
		}
	}
	
}	/* set_html_description */


GLOBAL void set_html_special_color ( char *hc )
{
	char color[256];
	BOOLEAN ret;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	color[0]= EOS;

	qdelete_once(token[1], "[", 1);
	qdelete_last(token[1], "]", 1);

	if (token[1][0]=='#')
	{	strcpy(color, token[1]);
		ret= TRUE;
	}
	else
	{	ret= get_html_color(token[1], color);
	}

	if (ret)
	{	hc[0]= EOS;
		if (color[0]!=EOS)
		{	strncat(hc, color, MAX_COLOR_LEN);
		}
	}
	else
	{	error_unknown_color(token[1]);
	}

}	/* set_html_special_color */


GLOBAL void set_html_modern_width ( void )
{
	int width;

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	/*r6pl8: Falls z.B. 30%, dann komplett umkopieren */
	if (strstr(token[1], "%")!=NULL)
	{
		strcpy(html_modern_width, token[1]);
	}
	else
	{
		width= atoi(token[1]);
		if (width<0)	width= 128;
		sprintf(html_modern_width, "%d", width);
	}

}	/* set_html_modern_width */


GLOBAL void set_html_modern_alignment ( void )
{
	char s[256];

	tokcpy2(s, 256);

	if (strstr(s, "center")!=NULL)
	{	html_modern_alignment= ALIGN_CENT;
		return;
	}

	if (strstr(s, "left")!=NULL)
	{	html_modern_alignment= ALIGN_LEFT;
		return;
	}

	if (strstr(s, "right")!=NULL)
	{	html_modern_alignment= ALIGN_RIGH;
		return;
	}

}	/* set_html_modern_alignment */



GLOBAL void set_html_modern_backimage ( void )
{
	char *ptr;
	char sTemp[512];

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	if (token[1][0]=='\"')
	{
		tokcpy2(sTemp, 512);
		ptr= strchr(sTemp+1, '\"');		/* zweites " suchen */

		if (ptr)
		{	ptr[0]= EOS;
			strcpy(html_modern_backimage, sTemp+1);
		}
		else
		{	strcpy(html_modern_backimage, sTemp);
		}
	}
	else
	{
		strcpy(html_modern_backimage, token[1]);
	}

	/* Hier muessen immer / benutzt werden! */
	replace_char(html_modern_backimage, "\\", "/");

}	/* set_html_modern_backimage */



GLOBAL void set_html_frames_width ( void )
{
	int width;

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	/*r6pl8: Falls z.B. 30%, dann komplett umkopieren */
	if (strstr(token[1], "%")!=NULL)
	{
		strcpy(html_frames_width, token[1]);
	}
	else
	{
		width= atoi(token[1]);
		if (width<0)	width= 128;
		sprintf(html_frames_width, "%d", width);
	}

}	/* set_html_frames_width */

GLOBAL void set_html_frames_height ( void )
{
	int height;

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	/*r6pl8: Falls z.B. 30%, dann komplett umkopieren */
	if (strstr(token[1], "%")!=NULL)
	{
		strcpy(html_frames_height, token[1]);
	}
	else
	{
		height= atoi(token[1]);
		if (height<0)	height= 64;
		sprintf(html_frames_height, "%d", height);
	}

}	/* set_html_frames_height */


GLOBAL void set_html_frames_position ( void )
{
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	if (strstr(token[1], "left")!=NULL)
	{	html_frames_position= POS_LEFT;
		return;
	}

	if (strstr(token[1], "right")!=NULL)
	{	html_frames_position= POS_RIGHT;
		return;
	}

	if (strstr(token[1], "top")!=NULL)
	{	html_frames_position= POS_TOP;
		return;
	}

	if (strstr(token[1], "bottom")!=NULL)
	{	html_frames_position= POS_BOTTOM;
		return;
	}

}	/* set_html_frames_position */


GLOBAL void set_html_frames_alignment ( void )
{
	char s[256];

	tokcpy2(s, 256);

	if (strstr(s, "center")!=NULL)
	{	html_frames_alignment= ALIGN_CENT;
		return;
	}

	if (strstr(s, "left")!=NULL)
	{	html_frames_alignment= ALIGN_LEFT;
		return;
	}

	if (strstr(s, "right")!=NULL)
	{	html_frames_alignment= ALIGN_RIGH;
		return;
	}

}	/* set_html_frames_alignment */


GLOBAL void set_html_frames_backimage ( void )
{
	char *ptr;
	char sTemp[512];

	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	if (token[1][0]=='\"')
	{
		tokcpy2(sTemp, 512);
		ptr= strchr(sTemp+1, '\"');		/* zweites " suchen */

		if (ptr)
		{	ptr[0]= EOS;
			strcpy(html_frames_backimage, sTemp+1);
		}
		else
		{	strcpy(html_frames_backimage, sTemp);
		}
	}
	else
	{
		strcpy(html_frames_backimage, token[1]);
	}

	/* Hier muessen immer / benutzt werden! */
	replace_char(html_frames_backimage, "\\", "/");

}	/* set_html_frames_backimage */


GLOBAL void set_html_button_alignment ( void )
{
	char s[256];

	tokcpy2(s, 256);

	if (strstr(s, "center")!=NULL)
	{	html_button_alignment= ALIGN_CENT;
		return;
	}

	if (strstr(s, "left")!=NULL)
	{	html_button_alignment= ALIGN_LEFT;
		return;
	}

	if (strstr(s, "right")!=NULL)
	{	html_button_alignment= ALIGN_RIGH;
		return;
	}

}	/* set_html_button_alignment */


GLOBAL void set_chapter_image ( void )
{
	char s[512], *ptr;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;
	
	fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
	sprintf(s, "%s%s%s", tmp_driv, tmp_path, tmp_name);

	if (desttype==TOHTM || desttype==TOMHH)
	{	replace_char(s, "\\", "/");	/*r6pl4*/
	}

	ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));
	
	if (!ptr)
	{	error_malloc_failed();
		bFatalErrorDetected= TRUE;
		return;
	}

	strcpy(ptr, s);
	toc[p1_toc_counter]->image= ptr;
	
	if (desttype!=TOHTM && desttype!=TOMHH)
	{	return;
	}

	/* Ausmasse des Icons ermitteln, falls es ein GIF ist */
	/* In s[] steht noch der Dateiname ohne Endung */
	if (strcmp(sDocImgSuffix, ".gif")!=0)
	{	return;
	}

	strinsert(s, old_outfile.path);
	strinsert(s, old_outfile.driv);
	strcat(s, ".gif");
	path_adjust_separator(s);
	get_gif_size(s, &toc[p1_toc_counter]->uiImageWidth, &toc[p1_toc_counter]->uiImageHeight);

}	/* set_chapter_image */



GLOBAL void set_chapter_icon ( void )
{
	char s[512], *ptr;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;
	
	fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
	sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);
	
	if (desttype==TOHTM || desttype==TOMHH)
	{	replace_char(s, "\\", "/");	/*r6pl4*/
	}

	ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));
	
	if (!ptr)
	{	error_malloc_failed();
		bFatalErrorDetected= TRUE;
		return;
	}

	strcpy(ptr, s);
	toc[p1_toc_counter]->icon= ptr;

	if (desttype!=TOHTM)
	{	return;
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
			error_read_gif(s);
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

}	/* set_chapter_icon */


GLOBAL void set_chapter_icon_active ( void )
{
	char s[512], *ptr;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;
	
	fsplit(token[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
	sprintf(s, "%s%s%s%s", tmp_driv, tmp_path, tmp_name, sDocImgSuffix);
	
	if (desttype==TOHTM || desttype==TOMHH)
	{	replace_char(s, "\\", "/");	/*r6pl4*/
	}

	ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));
	
	if (!ptr)
	{	error_malloc_failed();
		bFatalErrorDetected= TRUE;
		return;
	}

	strcpy(ptr, s);
	toc[p1_toc_counter]->icon_active= ptr;

	if (desttype!=TOHTM)
	{	return;
	}

	/* Ausmasse des Icons ermitteln, falls es ein GIF ist */
	/* In s[] steht noch der Dateiname ohne Endung */
	if (strcmp(sDocImgSuffix, ".gif")!=0)
	{	return;
	}

	strinsert(s, old_outfile.path);
	strinsert(s, old_outfile.driv);
	path_adjust_separator(s);
	get_gif_size(s, &toc[p1_toc_counter]->uiIconActiveWidth, &toc[p1_toc_counter]->uiIconActiveHeight);

}	/* set_chapter_icon_active */


GLOBAL void set_chapter_icon_text ( void )
{
	char s[512], *ptr;
	
	if (p1_toc_counter<0)	return;
	if (toc[p1_toc_counter]==NULL)	return;
	if (token[1][0]==EOS)	return;

	tokcpy2(s, 512);
	auto_quote_chars(s, TRUE);
	
	ptr= (char *) um_malloc(1+strlen(s)*sizeof(char));
	
	if (!ptr)
	{	error_malloc_failed();
		bFatalErrorDetected= TRUE;
	}
	else
	{	strcpy(ptr, s);
		toc[p1_toc_counter]->icon_text= ptr;
	}

}	/* set_chapter_icon_text */


/* Das Inhaltsverzeichnis selber in toc[] einsetzen */	/* r5pl6 */
/* Wird fuer Formate benoetigt, die toc[0] benutzen */
LOCAL BOOLEAN add_toc_to_toc ( void )
{
	TOCITEM	*tocptr;

	tocptr= (TOCITEM *) um_malloc(sizeof(TOCITEM));
	
	if (tocptr==NULL)
	{	return FALSE;
	}
	
	memset(tocptr, 0, sizeof(TOCITEM));
	
	strcpy(tocptr->name,	lang.contents);
	strcpy(tocptr->filename, FRAME_FILE_CON);

	tocptr->invisible=		TRUE;
	tocptr->toctype=		TOC_TOC;

	tocptr->prev_index=		0;
	tocptr->next_index=		1;

	tocptr->mapping = -1;
	
	toc[0]= tocptr;

	return TRUE;

}	/* add_toc_to_toc */


GLOBAL void toc_init_lang(void)
{
	strcpy(toc[0]->name, lang.contents);
}


LOCAL TOCITEM *init_new_toc_entry ( const int toctype, const BOOLEAN invisible )
{
	TOCITEM	*tocptr;

	if (p1_toc_counter>=MAXTOCS)		/* r5pl2 */
	{	error_too_many_node();
		bBreakInside= TRUE;
		return NULL;
	}

	tocptr= (TOCITEM *) um_malloc(sizeof(TOCITEM));
	
	if (tocptr==NULL)
	{	return NULL;
	}
	
	tokcpy2(tocptr->name, MAX_NODE_LEN+1);
	
	if (tocptr->name[0]==EOS)			/* r5pl14 */
	{	error_fatal_error("missing node name");
		bFatalErrorDetected= TRUE;
		um_free(tocptr);
		return NULL;
	}


	/* New in r6pl15 [NHz] */

	/* Set node in project file */

	save_upr_entry_node (toctype, sCurrFileName, strchr(current_node_name_sys, ' ')+1, uiCurrFileLine );

#if 1
	c_styles(tocptr->name);

	switch (desttype)					/* r5pl3 */
	{	case TOWIN:
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
			break;
	}
#endif

	if (desttype==TOPCH)
	{	replace_all_copyright(tocptr->name);
	}
	
	tocptr->toctype=			toctype;
	tocptr->converted=			FALSE;
	tocptr->ignore_subtoc=		FALSE;
	tocptr->ignore_links=		FALSE;
	tocptr->ignore_index=		FALSE;
	tocptr->ignore_title=		FALSE;	/*r6pl13*/
	tocptr->ignore_headline=	FALSE;
	tocptr->ignore_bottomline=	FALSE;
	tocptr->raw_header_filename= NULL;	/*r6pl10*/
	tocptr->raw_footer_filename= NULL;	/*r6pl10*/
	tocptr->ignore_raw_header=	FALSE;	/*r6pl10*/
	tocptr->ignore_raw_footer=	FALSE;	/*r6pl10*/
	tocptr->ignore_footer=		FALSE;	/*r6pl2*/
	tocptr->filename[0]=		EOS;
	tocptr->dirname[0]=			EOS;
	tocptr->counter_command=	NULL;
	tocptr->keywords=			NULL;
	tocptr->description=		NULL;	/*r6pl5*/
	tocptr->helpid=				NULL;
	tocptr->mapping=			-1;
	tocptr->image=				NULL;
	tocptr->uiImageWidth=		0;
	tocptr->uiImageHeight=		0;
	tocptr->icon=				NULL;
	tocptr->uiIconWidth=		0;
	tocptr->uiIconHeight=		0;
	tocptr->icon_active=		NULL;
	tocptr->uiIconActiveWidth=	0;
	tocptr->uiIconActiveHeight=	0;
	tocptr->icon_text=			NULL;
	tocptr->has_children=		FALSE;	/*r6pl5*/
	tocptr->count_n2=			0;		/*r6pl8*/
	tocptr->count_n3=			0;		/*r6pl8*/
	tocptr->count_n4=			0;		/*r6pl8*/
	strcpy(tocptr->backimage, sDocBackImage);
	strcpy(tocptr->backcolor, sDocBackColor);
	strcpy(tocptr->textcolor, sDocTextColor);
	strcpy(tocptr->linkcolor, sDocLinkColor);
	strcpy(tocptr->alinkcolor, sDocAlinkColor);
	strcpy(tocptr->vlinkcolor, sDocVlinkColor);

	/* r5pl15: Texinfo kennt keine versteckten Nodes, daher fuer */
	/* Texinfo das invisible-Flag immer aus FALSE setzen. */
	if (desttype==TOINF)
	{	tocptr->invisible= FALSE;
	}
	else
	{	tocptr->invisible= invisible;
	}

	p1_toctype= toctype;

	return tocptr;
}	/* init_new_toc_entry */



/* Nicht LOCAL: wird von abo.c und udo.c benutzt! */
GLOBAL BOOLEAN add_node_to_toc ( const BOOLEAN popup, const BOOLEAN invisible )
{
	TOCITEM	*tocptr;
	int		li;

	tocptr= init_new_toc_entry (TOC_NODE1, invisible);

	if (tocptr==NULL)
	{	return FALSE;
	}
	
	all_nodes++;

	/* ----------------------------------------------------	*/
	/* r5pl6: Listenartige Verkettung erzeugen				*/
	/* ----------------------------------------------------	*/
	/* noch ist p1_toc_counter nich inkrementiert worden,	*/
	/* zeigt daher auf den letzten (Sub(Sub))Node			*/

	tocptr->prev_index= p1_toc_counter;

	/* Bei HTML muss das Mergen beachtet werden! Der		*/
	/* Vorgaenger wird daher auf den letzten *Node gesetzt	*/
	if (desttype==TOHTM)
	{
		if (html_merge_node4 && last_n3_index>0)
		{	tocptr->prev_index= last_n3_index;
		}
		if (html_merge_node3 && last_n2_index>0)
		{	tocptr->prev_index= last_n2_index;
		}
		if (html_merge_node2 && last_n1_index>0)
		{	tocptr->prev_index= last_n1_index;
		}
		if (html_merge_node1)
		{	tocptr->prev_index= 0;
		}
	}

	/* Den Nachfolger des Vorgaengers setzen: auf diesen	*/
	
	toc[p1_toc_counter]->next_index= p1_toc_counter+1;
	
	if (desttype==TOHTM)
	{
		/* Wenn Subsubsubnode gemerged werden, dann muss	*/
		/* beim letzten Subsubnode dieser Node als			*/
		/* naechster Index eingetragen werden!				*/
		if (html_merge_node4 && last_n3_index>0)
		{	toc[last_n3_index]->next_index= p1_toc_counter+1;
		}

		/* Wenn Subsubnodes gemerged werden, dann muss beim	*/
		/* letzten Subnode dieser Node als naechster		*/
		/* Index eingetragen werden!						*/
		if (html_merge_node3 && last_n2_index>0)
		{	toc[last_n2_index]->next_index= p1_toc_counter+1;
		}

		/* Werden Subnodes gemerged, so muss beim letzten Node	*/
		/* dieser Node als naechster Index eingetragen werden!	*/
		if (html_merge_node2 && last_n1_index>0)
		{	toc[last_n1_index]->next_index= p1_toc_counter+1;
		}
	}
	
	/* Der Zeiger auf den Nachfolger muss vom Nachfolger	*/
	/* gesetzt werden.										*/
	tocptr->next_index= 0;

	/* Hilfsvariablen setzen fuer die uebergeordneten Nodes	*/
	tocptr->up_n1_index= 0;
	tocptr->up_n2_index= 0;
	tocptr->up_n3_index= 0;

	last_n1_index= p1_toc_counter+1;
	last_n2_index= 0;
	last_n3_index= 0;
	last_n4_index= 0;
	/* ----------------------------------------------------	*/

	p1_toc_counter++;
	toc[p1_toc_counter]= tocptr;

	if (pflag[PASS1].inside_apx)
	{	apx_available= TRUE;
		p1_apx_n1++;
		p1_apx_n2= 0;
		p1_apx_n3= 0;
		p1_apx_n4= 0;
		tocptr->appendix= TRUE;
		tocptr->n1= p1_apx_n1;
		tocptr->n2= p1_apx_n2;
		tocptr->n3= p1_apx_n3;
		tocptr->n4= p1_apx_n4;
		if (!invisible)
		{	p1_apx_nr1++;
			p1_apx_nr2= 0;
			p1_apx_nr3= 0;
			p1_apx_nr4= 0;
			tocptr->nr1= p1_apx_nr1;
			tocptr->nr2= p1_apx_nr2;
			tocptr->nr3= p1_apx_nr3;
			tocptr->nr4= p1_apx_nr4;
		}
	}
	else
	{	toc_available= TRUE;
		p1_toc_n1++;
		p1_toc_n2= 0;
		p1_toc_n3= 0;
		p1_toc_n4= 0;
		tocptr->appendix= FALSE;
		tocptr->n1= p1_toc_n1;
		tocptr->n2= p1_toc_n2;
		tocptr->n3= p1_toc_n3;
		tocptr->n4= p1_toc_n4;
		if (!invisible)
		{	p1_toc_nr1++;
			p1_toc_nr2= 0;
			p1_toc_nr3= 0;
			p1_toc_nr4= 0;
			tocptr->nr1= p1_toc_nr1;
			tocptr->nr2= p1_toc_nr2;
			tocptr->nr3= p1_toc_nr3;
			tocptr->nr4= p1_toc_nr4;
		}
	}

	if (desttype==TOHTM || desttype==TOMHH)
	{	/* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
		/* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */
		get_html_filename(p1_toc_counter, tocptr->filename);
	}

	li= add_label(tocptr->name, TRUE, popup);

	if (li>=0)
	{	tocptr->labindex= li;
	}


	return TRUE;	
}	/*add_node_to_toc*/



GLOBAL BOOLEAN add_subnode_to_toc ( const BOOLEAN popup, const BOOLEAN invisible )
{
	TOCITEM	*tocptr;
	int li;

	if (last_n1_index==0)
	{	error_node2_not_allowed();
		return FALSE;
	}

	tocptr= init_new_toc_entry (TOC_NODE2, invisible);

	if (tocptr==NULL)
	{	return FALSE;
	}

	all_subnodes++;
	
	/* ----------------------------------------------------	*/
	/* r5pl6: Listenartige Verkettung erzeugen				*/
	/* ----------------------------------------------------	*/
	/* noch ist p1_toc_counter nich inkrementiert worden, 	*/
	/* zeigt daher auf den letzten (Sub(Sub))Node			*/
	/* Bei HTML muss das Mergen beachtet werden!			*/
	tocptr->prev_index= p1_toc_counter;

	if (desttype==TOHTM)
	{
		if (html_merge_node4 && last_n3_index>0)
		{	tocptr->prev_index= last_n3_index;
		}
		if (html_merge_node3 && last_n2_index>0)
		{	tocptr->prev_index= last_n2_index;
		}
		if (html_merge_node2 && last_n1_index>0)
		{	tocptr->prev_index= last_n1_index;
		}
		if (html_merge_node1)
		{	tocptr->prev_index= 0;
		}
	}

	/* Den Nachfolger des Vorgaengers setzen, also auf		*/
	/* bzw. bei !html_merge... auf die letzten				*/

	toc[p1_toc_counter]->next_index= p1_toc_counter+1;

	if (desttype==TOHTM)
	{
		/* Wenn Subsubsubnode gemerged werden, dann muss	*/
		/* beim letzten Subsubnode dieser Subnode als		*/
		/* naechster Index eingetragen werden!				*/
		if (html_merge_node4 && last_n3_index>0)
		{	toc[last_n3_index]->next_index= p1_toc_counter+1;
		}

		/* Wenn Subsubnodes gemerged werden, dann muss beim	*/
		/* letzten Subnode dieser Subnode als naechster		*/
		/* Index eingetragen werden!						*/
		if (html_merge_node3 && last_n2_index>0)
		{	toc[last_n2_index]->next_index= p1_toc_counter+1;
		}
	}

	/* Der Zeiger auf den Nachfolger muss vom Nachfolger	*/
	/* gesetzt werden.										*/
	tocptr->next_index= 0;

	/* Merken, dass der uebergeordnete Kinder hat */
	/* und die Anzahl der Subnodes erhoehen */
	if (last_n1_index>0)
	{	toc[last_n1_index]->has_children=	TRUE;	/*r6pl5*/
		toc[last_n1_index]->count_n2++;				/*r6pl8*/
	}

	/* Hilfsvariablen setzen fuer die uebergeordneten Nodes	*/
	tocptr->up_n1_index=	last_n1_index;
	tocptr->up_n2_index=	0;
	tocptr->up_n3_index=	0;

	last_n2_index=	p1_toc_counter+1;
	last_n3_index=	0;
	last_n4_index=	0;
	/* ----------------------------------------------------	*/

	/* Zaehler hochsetzen und Zeiger in das Array kopieren	*/
	p1_toc_counter++;
	toc[p1_toc_counter]= tocptr;

	if (pflag[PASS1].inside_apx)
	{	apx_available= TRUE;
		p1_apx_n2++;
		p1_apx_n3= 0;
		p1_apx_n4= 0;
		tocptr->appendix= TRUE;
		tocptr->n1= p1_apx_n1;
		tocptr->n2= p1_apx_n2;
		tocptr->n3= p1_apx_n3;
		tocptr->n4= p1_apx_n4;
		if (!invisible)
		{	p1_apx_nr2++;
			p1_apx_nr3= 0;
			p1_apx_nr4= 0;
			tocptr->nr1= p1_apx_nr1;
			tocptr->nr2= p1_apx_nr2;
			tocptr->nr3= p1_apx_nr3;
			tocptr->nr4= p1_apx_nr4;
		}
	}
	else
	{	toc_available= TRUE;
		p1_toc_n2++;
		p1_toc_n3= 0;
		p1_toc_n4= 0;
		tocptr->appendix= FALSE;
		tocptr->n1= p1_toc_n1;
		tocptr->n2= p1_toc_n2;
		tocptr->n3= p1_toc_n3;
		tocptr->n4= p1_toc_n4;
		if (!invisible)
		{	p1_toc_nr2++;
			p1_toc_nr3= 0;
			p1_toc_nr4= 0;
			tocptr->nr1= p1_toc_nr1;
			tocptr->nr2= p1_toc_nr2;
			tocptr->nr3= p1_toc_nr3;
			tocptr->nr4= p1_toc_nr4;
		}
	}

	if (desttype==TOHTM || desttype==TOMHH)
	{	/* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
		/* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */
		get_html_filename(p1_toc_counter, tocptr->filename);
	}

	li= add_label(tocptr->name, TRUE, popup);

	if (li>=0)
	{	tocptr->labindex= li;
	}

	return TRUE;	

}	/*add_subnode_to_toc*/



GLOBAL BOOLEAN	add_subsubnode_to_toc ( const BOOLEAN popup, const BOOLEAN invisible )
{
	TOCITEM	*tocptr;
	int li;

	if (last_n2_index==0)
	{	error_node3_not_allowed();
		return FALSE;
	}

	tocptr= init_new_toc_entry (TOC_NODE3, invisible);

	if (tocptr==NULL)
	{	return FALSE;
	}

					
	all_subsubnodes++;

	/* ----------------------------------------------------	*/
	/* r5pl6: Listenartige Verkettung erzeugen				*/
	/* ----------------------------------------------------	*/
	/* noch ist p1_toc_counter nich inkrementiert worden und	*/
	/* zeigt daher auf den letzten (Sub(Sub))Node			*/
	tocptr->prev_index= p1_toc_counter;

	if (desttype==TOHTM)
	{
		if (html_merge_node4 && last_n3_index>0)
		{	tocptr->prev_index= last_n3_index;
		}
		if (html_merge_node3 && last_n2_index>0)
		{	tocptr->prev_index= last_n2_index;
		}
		if (html_merge_node2 && last_n1_index>0)
		{	tocptr->prev_index= last_n1_index;
		}
		if (html_merge_node1)
		{	tocptr->prev_index= 0;
		}
	}

	/* Den Nachfolger des Vorgaengers setzen: auf diesen	*/
	toc[p1_toc_counter]->next_index= p1_toc_counter+1;

	/* Merken, dass der uebergeordnete Kinder hat */
	/* und die Anzahl der Subsubnodes erhoehen */
	if (last_n2_index>0)
	{	toc[last_n2_index]->has_children=	TRUE;	/*r6pl5*/
		toc[last_n2_index]->count_n3++;				/*r6pl8*/
	}

	if (desttype==TOHTM)
	{
		/* Wenn Subsubsubnodes gemerged werden, dann muss	*/
		/* beim letzten Subsubnode dieser Subsubnode als	*/
		/* naechster Index eingetragen werden!				*/
		if (html_merge_node4 && last_n3_index>0)
		{	toc[last_n3_index]->next_index= p1_toc_counter+1;
		}
	}

	/* Der Zeiger auf den Nachfolger muss vom Nachfolger	*/
	/* gesetzt werden.										*/
	tocptr->next_index= 0;

	/* Hilfsvariablen setzen fuer die uebergeordneten Nodes	*/
	tocptr->up_n1_index=	last_n1_index;
	tocptr->up_n2_index=	last_n2_index;
	tocptr->up_n3_index=	0;

	last_n3_index= p1_toc_counter+1;
	last_n4_index= 0;
	/* ----------------------------------------------------	*/

	p1_toc_counter++;
	toc[p1_toc_counter]= tocptr;

	if (pflag[PASS1].inside_apx)
	{	apx_available= TRUE;
		p1_apx_n3++;
		p1_apx_n4= 0;
		tocptr->appendix= TRUE;
		tocptr->n1= p1_apx_n1;
		tocptr->n2= p1_apx_n2;
		tocptr->n3= p1_apx_n3;
		tocptr->n4= p1_apx_n4;
		if (!invisible)
		{	p1_apx_nr3++;
			p1_apx_nr4= 0;
			tocptr->nr1= p1_apx_nr1;
			tocptr->nr2= p1_apx_nr2;
			tocptr->nr3= p1_apx_nr3;
			tocptr->nr4= p1_apx_nr4;
		}
	}
	else
	{	toc_available= TRUE;
		p1_toc_n3++;
		p1_toc_n4= 0;
		tocptr->appendix= FALSE;
		tocptr->n1= p1_toc_n1;
		tocptr->n2= p1_toc_n2;
		tocptr->n3= p1_toc_n3;
		tocptr->n4= p1_toc_n4;
		{	p1_toc_nr3++;
			p1_toc_nr4= 0;
			tocptr->nr1= p1_toc_nr1;
			tocptr->nr2= p1_toc_nr2;
			tocptr->nr3= p1_toc_nr3;
			tocptr->nr4= p1_toc_nr4;
		}
	}

	if (desttype==TOHTM || desttype==TOMHH)
	{	/* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
		/* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */
		get_html_filename(p1_toc_counter, tocptr->filename);
	}

	li= add_label(tocptr->name, TRUE, popup);

	if (li>=0)
	{	tocptr->labindex= li;
	}

	return TRUE;
}	/*add_subsubnode_to_toc*/



GLOBAL BOOLEAN	add_subsubsubnode_to_toc ( const BOOLEAN popup, const BOOLEAN invisible )
{
	TOCITEM	*tocptr;
	int li;

	if (last_n3_index==0)
	{	error_node4_not_allowed();
		return FALSE;
	}

	tocptr= init_new_toc_entry (TOC_NODE4, invisible);

	if (tocptr==NULL)
	{	return FALSE;
	}
					
	all_subsubsubnodes++;
	
	called_subsubsubnode= TRUE;		/* r5pl6 */

	/* ----------------------------------------------------	*/
	/* r5pl6: Listenartige Verkettung erzeugen				*/
	/* ----------------------------------------------------	*/
	/* noch ist p1_toc_counter nicht inkrementiert worden 	*/
	/* und zeigt daher auf den letzten (Sub(Sub))Node		*/
	tocptr->prev_index= p1_toc_counter;

	if (desttype==TOHTM)
	{
		if (html_merge_node4 && last_n3_index>0)
		{	tocptr->prev_index= last_n3_index;
		}
		if (html_merge_node3 && last_n2_index>0)
		{	tocptr->prev_index= last_n2_index;
		}
		if (html_merge_node2 && last_n1_index>0)
		{	tocptr->prev_index= last_n1_index;
		}
		if (html_merge_node1)
		{	tocptr->prev_index= 0;
		}
	}

	/* Den Nachfolger des Vorgaengers setzen: auf diesen	*/
	toc[p1_toc_counter]->next_index= p1_toc_counter+1;

	/* Merken, dass der uebergeordnete Kinder hat */
	/* und die Anzahl der Subsubsubnodes erhoehen */
	if (last_n3_index>0)
	{	toc[last_n3_index]->has_children=	TRUE;	/*r6pl5*/
		toc[last_n3_index]->count_n4++;				/*r6pl8*/
	}

	/* Der Zeiger auf den Nachfolger muss vom Nachfolger	*/
	/* gesetzt werden.										*/
	tocptr->next_index= 0;

	/* Hilfsvariablen setzen fuer die uebergeordneten Nodes	*/
	tocptr->up_n1_index= last_n1_index;
	tocptr->up_n2_index= last_n2_index;
	tocptr->up_n3_index= last_n3_index;

	last_n4_index= p1_toc_counter+1;
	/* ----------------------------------------------------	*/

	p1_toc_counter++;
	toc[p1_toc_counter]= tocptr;

	if (pflag[PASS1].inside_apx)
	{	apx_available= TRUE;
		p1_apx_n4++;
		tocptr->appendix= TRUE;
		tocptr->n1= p1_apx_n1;
		tocptr->n2= p1_apx_n2;
		tocptr->n3= p1_apx_n3;
		tocptr->n4= p1_apx_n4;
		if (!invisible)
		{	p1_apx_nr4++;
			tocptr->nr1= p1_apx_nr1;
			tocptr->nr2= p1_apx_nr2;
			tocptr->nr3= p1_apx_nr3;
			tocptr->nr4= p1_apx_nr4;
		}
	}
	else
	{	toc_available= TRUE;
		p1_toc_n4++;
		tocptr->appendix= FALSE;
		tocptr->n1= p1_toc_n1;
		tocptr->n2= p1_toc_n2;
		tocptr->n3= p1_toc_n3;
		tocptr->n4= p1_toc_n4;
		{	p1_toc_nr4++;
			tocptr->nr1= p1_toc_nr1;
			tocptr->nr2= p1_toc_nr2;
			tocptr->nr3= p1_toc_nr3;
			tocptr->nr4= p1_toc_nr4;
		}
	}

	if (desttype==TOHTM || desttype==TOMHH)
	{	/* Den Dateinamen ermitteln, in dem dieser Node definiert ist */
		/* Vor r6pl2 wurde er erst waehrend der Referenzierung ermittelt */
		get_html_filename(p1_toc_counter, tocptr->filename);
	}

	li= add_label(tocptr->name, TRUE, popup);

	if (li>=0)
	{	tocptr->labindex= li;
	}

	return TRUE;
}	/*add_subsubsubnode_to_toc*/



GLOBAL BOOLEAN toc_begin_node (const BOOLEAN popup, const BOOLEAN invisible)
{
	BOOLEAN ret;

	switch(p1_toctype)
	{
		case TOC_NONE:	ret= add_node_to_toc(popup, invisible);				break;
		case TOC_NODE1:	ret= add_subnode_to_toc(popup, invisible);			break;
		case TOC_NODE2:	ret= add_subsubnode_to_toc(popup, invisible);		break;
		case TOC_NODE3:	ret= add_subsubsubnode_to_toc(popup, invisible);	break;
		default:		ret= add_subsubsubnode_to_toc(popup, invisible);	break;
	}

	return ret;

}	/* toc_begin_node */


GLOBAL void toc_end_node (void)
{
	switch(p1_toctype)
	{
		case TOC_NODE1:	p1_toctype= TOC_NONE;	break;
		case TOC_NODE2:	p1_toctype= TOC_NODE1;	break;
		case TOC_NODE3:	p1_toctype= TOC_NODE2;	break;
		case TOC_NODE4:	p1_toctype= TOC_NODE3;	break;
	}

}	/* toc_end_node */


GLOBAL int is_current_node(int tocindex)
{
	return tocindex == p2_toc_counter;
}


GLOBAL int get_toc_counter(void)
{
	return p2_toc_counter;
}


/*	############################################################
	#
	#	Dateien mit den Jump-IDs ausgeben fuer C und Pascal
	#
	############################################################	*/
typedef struct _tWinMapData
{
	char remOn[16], remOff[16];
	char cmd[32];					/* #define			const		*/
	char varOp[16];					/*					=			*/
	char hexPre[16], hexSuf[16];	/* 0x				$			*/
	char compiler[32];				/* C, Pascal, Visual-Basic, ...	*/
}	tWinMapData;


LOCAL BOOLEAN save_the_map ( const char *filename, const char *suffix, tWinMapData *data )
{
	register int i;
	int map;
	char hid[256], f[512];
	FILE *file;
	
	strcpy(f, filename);
	strcat(f, suffix);

	file= fopen(f, "w");
	if (!file)
	{	return FALSE;
	}

	save_upr_entry_outfile(f);
	
	fprintf(file, "%s mapping of %s for %s, made with UDO%s %s\n\n",
		data->remOn, outfile.full, data->compiler, UDO_REL, data->remOff);

	for (i=0; i<=p1_toc_counter; i++)
	{
		hid[0]= EOS;

		if (toc[i]->helpid!=NULL)
		{	strcpy(hid, toc[i]->helpid);
		}
		else
		{
			if (use_auto_helpids)
			{
				node2WinAutoID(hid, toc[i]->name);
			}
		}

		map= -1;

		if (toc[i]->mapping>=0)
		{	map= toc[i]->mapping;
		}

		if (hid[0]!=EOS || map>=0 || desttype==TOWH4)
		{
			if (hid[0]==EOS)
			{
				node2NrWinhelp(hid, toc[i]->labindex);
			}

			strinsert(hid, sDocWinPrefixID);

			if (map<0)
			{	map= 0x1000+i;
			}

			fprintf(file, "%s %-*s%s\t%s%04X%s\t%s %s %s\n",
						data->cmd,
						MAX_HELPID_LEN+1,
						hid,
						data->varOp,
						data->hexPre,
						map,
						data->hexSuf,
						data->remOn,
						toc[i]->name,
						data->remOff
				);
		}
	}

	fclose(file);
	
	return TRUE;	
}


GLOBAL BOOLEAN save_winhelp_map_c ( void )
{
	tWinMapData data;
	BOOLEAN flag;

	memset(&data, 0, sizeof(data));
	strcpy(data.cmd, "#define");
	strcpy(data.hexPre, "0x");
	strcpy(data.remOn, "/*");
	strcpy(data.remOff, "*/");
	strcpy(data.compiler, "C");

	flag= save_the_map (sMapNoSuff, ".hpc", &data);

	return flag;
}	/* save_winhelp_map_c */


GLOBAL BOOLEAN save_winhelp_map_pas ( void )
{
	tWinMapData data;
	BOOLEAN flag;

	memset(&data, 0, sizeof(data));
	strcpy(data.cmd, "const");
	strcpy(data.varOp, "=");
	strcpy(data.hexPre, "$");
	strcpy(data.hexSuf, ";");
	strcpy(data.remOn, "(*");
	strcpy(data.remOff, "*)");
	strcpy(data.compiler, "Pascal");

	flag= save_the_map (sMapNoSuff, ".hpp", &data);

	return flag;
}	/* save_winhelp_map_pas */


GLOBAL BOOLEAN save_winhelp_map_vb ( void )
{
	tWinMapData data;
	BOOLEAN flag;

	memset(&data, 0, sizeof(data));
	strcpy(data.cmd, "Public Const");
	strcpy(data.varOp, "=");
	strcpy(data.hexPre, "&h");
	strcpy(data.hexSuf, "");
	strcpy(data.remOn, "'");
	strcpy(data.remOff, "");
	strcpy(data.compiler, "Visual Basic");

	flag= save_the_map (sMapNoSuff, ".hpb", &data);

	return flag;
}	/* save_winhelp_map_vb */


GLOBAL BOOLEAN save_winhelp_map_gfa ( void )
{
	tWinMapData data;
	BOOLEAN flag;

	memset(&data, 0, sizeof(data));
	strcpy(data.cmd, "Public Const");
	strcpy(data.varOp, "=");
	strcpy(data.hexPre, "&h");
	strcpy(data.hexSuf, "");
	strcpy(data.remOn, "'");
	strcpy(data.remOff, "");
	strcpy(data.compiler, "GFA-Basic");

	flag= save_the_map (sMapNoSuff, ".hpg", &data);

	return flag;
}	/* save_winhelp_map_gfa */


GLOBAL BOOLEAN save_winhelp4_cnt ( void )
{
	FILE *cntfile;

	register int i;
	int li, apxstart;
	char sName[512], sMisc[512], sID[128];
	BOOLEAN n1HadChildren= FALSE;
	BOOLEAN n2HadChildren= FALSE;
	BOOLEAN n3HadChildren= FALSE;

	cntfile= myFwopen(sCntfull, FTCNT);
	
	if (cntfile == NULL)
	{	return FALSE;
	}

	save_upr_entry_outfile(sCntfull);

	if (p1_toc_counter > 0)
	{
		fprintf(cntfile, ":Base %s.hlp>main\n", outfile.name);
		fprintf(cntfile, ":Index %s.hlp\n", outfile.name);
	
		strcpy(sMisc, titleprogram);
		win2sys(sMisc);
		if (sMisc[0]!=EOS)
		{	fprintf(cntfile, ":Title %s\n", sMisc);
		}
	
		if (uses_tableofcontents)
		{	node2NrWinhelp(sMisc, 0);
			fprintf(cntfile, "1 %s=%s\n", lang.contents, sMisc);
		}
		
		apxstart= 1;
	
		for (i=1; i<=p1_toc_counter; i++)
		{
			if (toc[i]!=NULL && !toc[i]->invisible)
			{
				convert_toc_item(toc[i]);
	
				if ( toc[i]->appendix )
				{
					apxstart= i;	/* fuer unten merken */
					break;			/* r5pl6: Es kann nur einen Anhang geben */
				}
				else
				{	if ( toc[i]->n1 != 0 )
					{
						if ( toc[i]->toctype==TOC_NODE1 )
						{	/* Ein Kapitel */	
	
							li= toc[i]->labindex;
							node2NrWinhelp(sID, li);
							if (no_numbers)
							{	strcpy(sName, toc[i]->name);
							}
							else
							{	sprintf(sName, "[%d] %s",
									toc[i]->nr1+toc_offset,
									toc[i]->name);
							}
							win2sys(sName);
							if (n1HadChildren || toc[i]->has_children)
							{	fprintf(cntfile, "1 %s\n", sName);
								fprintf(cntfile, "2 %s=%s\n", sName, sID);
								n1HadChildren= TRUE;
							}
							else
							{	fprintf(cntfile, "1 %s=%s\n", sName, sID);
							}
	
							n2HadChildren= FALSE;
							n3HadChildren= FALSE;
						}/* TOC_NODE1 */
						
						
						if ( toc[i]->toctype==TOC_NODE2 )
						{	/* Ein Abschnitt */
							li= toc[i]->labindex;
							node2NrWinhelp(sID, li);
							if (no_numbers)
							{	strcpy(sName, toc[i]->name);
							}
							else
							{	sprintf(sName, "[%d.%d] %s",
									toc[i]->nr1+toc_offset,
									toc[i]->nr2+subtoc_offset,
									toc[i]->name);
							}
							win2sys(sName);
							if (n2HadChildren || toc[i]->has_children)
							{	fprintf(cntfile, "2 %s\n", sName);
								fprintf(cntfile, "3 %s=%s\n", sName, sID);
								n2HadChildren= TRUE;
							}
							else
							{	fprintf(cntfile, "2 %s=%s\n", sName, sID);
							}
	
							n3HadChildren= FALSE;
						}/* TOC_NODE2 */
						
						if ( toc[i]->toctype==TOC_NODE3 )
						{	/* Ein Unterabschnitt */
							li= toc[i]->labindex;
							node2NrWinhelp(sID, li);
							if (no_numbers)
							{	strcpy(sName, toc[i]->name);
							}
							else
							{	sprintf(sName, "[%d.%d.%d] %s",
									toc[i]->nr1+toc_offset,
									toc[i]->nr2+subtoc_offset,
									toc[i]->nr3+subsubtoc_offset,
									toc[i]->name);
							}
							win2sys(sName);
							if (n3HadChildren || toc[i]->has_children)
							{	fprintf(cntfile, "3 %s\n", sName);
								fprintf(cntfile, "4 %s=%s\n", sName, sID);
								n3HadChildren= TRUE;
							}
							else
							{	fprintf(cntfile, "3 %s=%s\n", sName, sID);
							}
						}/* TOC_NODE3 */
					
						if ( toc[i]->toctype==TOC_NODE4 )
						{	/* Ein Paragraph */
							li= toc[i]->labindex;
							node2NrWinhelp(sID, li);
							if (no_numbers)
							{	strcpy(sName, toc[i]->name);
							}
							else
							{	sprintf(sName, "[%d.%d.%d.%d] %s",
									toc[i]->nr1+toc_offset,
									toc[i]->nr2+subtoc_offset,
									toc[i]->nr3+subsubtoc_offset,
									toc[i]->nr4+subsubsubtoc_offset,
									toc[i]->name);
							}
							win2sys(sName);
							fprintf(cntfile, "4 %s=%s\n", sName, sID);
						}/* TOC_NODE4 */
	
	
					}/* toc[i]->n1 > 0 */
	
				}/* !toc[i]->appendix */
	
			}/* toc[i]!=NULL && !toc[i]->invisible */
	
		}/* for */
	
	
		if (apx_available)
		{
			n1HadChildren= FALSE;
			n2HadChildren= FALSE;
			n3HadChildren= FALSE;
		
			fprintf(cntfile, "1 %s\n", lang.appendix);
		
			for (i=apxstart; i<=p1_toc_counter; i++)
			{
				if (toc[i]!=NULL && !toc[i]->invisible)
				{
					convert_toc_item(toc[i]);
		
					if ( toc[i]->appendix )
					{
						if ( toc[i]->n1 != 0 )
						{
							if ( toc[i]->toctype==TOC_NODE1 )
							{	/* Ein Kapitel */	
		
								li= toc[i]->labindex;
								node2NrWinhelp(sID, li);
								if (no_numbers)
								{	strcpy(sName, toc[i]->name);
								}
								else
								{	sprintf(sName, "[%c] %s",
										'A'-1+toc[i]->nr1,
										toc[i]->name);
								}
								win2sys(sName);
								if (n1HadChildren || toc[i]->has_children)
								{	fprintf(cntfile, "2 %s\n", sName);
									fprintf(cntfile, "3 %s=%s\n", sName, sID);
									n1HadChildren= TRUE;
								}
								else
								{	fprintf(cntfile, "2 %s=%s\n", sName, sID);
								}
		
								n2HadChildren= FALSE;
								n3HadChildren= FALSE;
		
							}/* TOC_NODE1 */
							
							
							if ( toc[i]->toctype==TOC_NODE2 )
							{	/* Ein Abschnitt */
								li= toc[i]->labindex;
								node2NrWinhelp(sID, li);
								if (no_numbers)
								{	strcpy(sName, toc[i]->name);
								}
								else
								{	sprintf(sName, "[%c.%d] %s",
										'A'-1+toc[i]->nr1,
										toc[i]->nr2,
										toc[i]->name);
								}
								win2sys(sName);
								if (n2HadChildren || toc[i]->has_children)
								{	fprintf(cntfile, "3 %s\n", sName);
									fprintf(cntfile, "4 %s=%s\n", sName, sID);
									n2HadChildren= TRUE;
								}
								else
								{	fprintf(cntfile, "3 %s=%s\n", sName, sID);
								}
		
								n3HadChildren= FALSE;
		
							}/* TOC_NODE2 */
							
							if ( toc[i]->toctype==TOC_NODE3 )
							{	/* Ein Unterabschnitt */
								li= toc[i]->labindex;
								node2NrWinhelp(sID, li);
								if (no_numbers)
								{	strcpy(sName, toc[i]->name);
								}
								else
								{	sprintf(sName, "[%c.%d.%d] %s",
										'A'-1+toc[i]->nr1,
										toc[i]->nr2,
										toc[i]->nr3,
										toc[i]->name);
								}
								win2sys(sName);
								if (n3HadChildren || toc[i]->has_children)
								{	fprintf(cntfile, "4 %s\n", sName);
									fprintf(cntfile, "5 %s=%s\n", sName, sID);
									n3HadChildren= TRUE;
								}
								else
								{	fprintf(cntfile, "4 %s=%s\n", sName, sID);
								}
							}/* TOC_NODE3 */
						
							if ( toc[i]->toctype==TOC_NODE4 )
							{	/* Ein Paragraph */
								li= toc[i]->labindex;
								node2NrWinhelp(sID, li);
								if (no_numbers)
								{	strcpy(sName, toc[i]->name);
								}
								else
								{	sprintf(sName, "[%c.%d.%d.%d] %s",
										'A'-1+toc[i]->nr1,
										toc[i]->nr2,
										toc[i]->nr3,
										toc[i]->nr4,
										toc[i]->name);
								}
								win2sys(sName);
								fprintf(cntfile, "5 %s=%s\n", sName, sID);
							}/* TOC_NODE4 */
		
		
						}/* toc[i]->n1 > 0 */
		
					}/* !toc[i]->appendix */
		
				}/* toc[i]!=NULL && !toc[i]->invisible */
		
			}/* for */
		}
	}
	
	fclose(cntfile);
	return TRUE;
}	/* save_winhelp4_cnt */



/*	############################################################
	#
	# Formatstrings fuer die Inhaltsverzeichnisse initialisieren
	# Dies muss geschehen, wenn der Status von !no_numbers
	# bekannt ist, d.h. zwischen pass1() und pass2()
	#
	############################################################	*/
LOCAL void init_toc_forms_numbers ( void )
{
	switch (desttype)
	{
		case TOAQV:
		case TOWIN:
			strcpy(form_t1_n1, "\\li320\\fi-320\\tx320 %d\\tab{%s}\\par\\pard");
/* 560 */	strcpy(form_t1_n2, "\\li880\\fi-560\\tx880 %d.%d\\tab{%s}\\par\\pard");
/* 920 */	strcpy(form_t1_n3, "\\li1800\\fi-920\\tx1800 %d.%d.%d\\tab{%s}\\par\\pard");
/*1000 */	strcpy(form_t1_n4, "\\li2800\\fi-1000\\tx2800 %d.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t2_n2, "\\li480\\fi-480\\tx480 %d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t2_n3, "\\li1400\\fi-920\\tx1400 %d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t2_n4, "\\li2400\\fi-1000\\tx2400 %d.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t3_n3, "\\li880\\fi-880\\tx880 %d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t3_n4, "\\li1800\\fi-920\\tx1800 %d.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t4_n4, "\\li880\\fi-880\\tx880 %d.%d.%d.%d\\tab{%s}\\par\\pard");

			strcpy(form_a1_n1, "\\li320\\fi-320\\tx320 %c\\tab{%s}\\par\\pard");
/* 560 */	strcpy(form_a1_n2, "\\li880\\fi-560\\tx880 %c.%d\\tab{%s}\\par\\pard");
/* 920 */	strcpy(form_a1_n3, "\\li1800\\fi-920\\tx1800 %c.%d.%d\\tab{%s}\\par\\pard");
/*1000 */	strcpy(form_a1_n4, "\\li2800\\fi-1000\\tx2800 %c.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a2_n2, "\\li480\\fi-480\\tx480 %c.%d\\tab{%s}\\par\\pard");
			strcpy(form_a2_n3, "\\li1400\\fi-920\\tx1400 %c.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a2_n4, "\\li2400\\fi-1000\\tx2400 %c.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a3_n3, "\\li880\\fi-880\\tx880 %c.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a3_n4, "\\li1800\\fi-920\\tx1800 %c.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a4_n4, "\\li880\\fi-880\\tx880 %c.%d.%d.%d\\tab{%s}\\par\\pard");
			break;

		case TOWH4:
			strcpy(form_t1_n1, "\\li300\\fi-300\\tx300 %d\\tab{%s}\\par\\pard");
/* 560 */	strcpy(form_t1_n2, "\\li800\\fi-500\\tx800 %d.%d\\tab{%s}\\par\\pard");
/* 920 */	strcpy(form_t1_n3, "\\li1600\\fi-800\\tx1600 %d.%d.%d\\tab{%s}\\par\\pard");
/*1000 */	strcpy(form_t1_n4, "\\li2600\\fi-1000\\tx2600 %d.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t2_n2, "\\li400\\fi-400\\tx400 %d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t2_n3, "\\li1300\\fi-920\\tx1300 %d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t2_n4, "\\li2200\\fi-1000\\tx2200 %d.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t3_n3, "\\li800\\fi-800\\tx800 %d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t3_n4, "\\li1600\\fi-920\\tx1600 %d.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_t4_n4, "\\li800\\fi-800\\tx800 %d.%d.%d.%d\\tab{%s}\\par\\pard");

			strcpy(form_a1_n1, "\\li300\\fi-300\\tx300 %c\\tab{%s}\\par\\pard");
/* 560 */	strcpy(form_a1_n2, "\\li800\\fi-500\\tx800 %c.%d\\tab{%s}\\par\\pard");
/* 920 */	strcpy(form_a1_n3, "\\li1600\\fi-800\\tx1600 %c.%d.%d\\tab{%s}\\par\\pard");
/*1000 */	strcpy(form_a1_n4, "\\li2600\\fi-1000\\tx2600 %c.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a2_n2, "\\li400\\fi-400\\tx400 %c.%d\\tab{%s}\\par\\pard");
			strcpy(form_a2_n3, "\\li1300\\fi-920\\tx1300 %c.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a2_n4, "\\li2200\\fi-1000\\tx2200 %c.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a3_n3, "\\li800\\fi-800\\tx800 %c.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a3_n4, "\\li1600\\fi-920\\tx1600 %c.%d.%d.%d\\tab{%s}\\par\\pard");
			strcpy(form_a4_n4, "\\li800\\fi-800\\tx800 %c.%d.%d.%d\\tab{%s}\\par\\pard");
			break;

		case TOHTM:
		case TOMHH:
			strcpy(form_t1_n1, "<li>%2d %s</li>");
			strcpy(form_t1_n2, "<li>%2d.%d %s</li>");
			strcpy(form_t1_n3, "<li>%2d.%d.%d %s</li>");
			strcpy(form_t1_n4, "<li>%2d.%d.%d.%d %s</li>");
			strcpy(form_t2_n2, form_t1_n2);
			strcpy(form_t2_n3, form_t1_n3);
			strcpy(form_t2_n4, form_t1_n4);
			strcpy(form_t3_n3, form_t1_n3);
			strcpy(form_t3_n4, form_t1_n4);
			strcpy(form_t4_n4, form_t1_n4);

			strcpy(form_a1_n1, "<li>%c %s</li>");
			strcpy(form_a1_n2, "<li>%c.%d %s</li>");
			strcpy(form_a1_n3, "<li>%c.%d.%d %s</li>");
			strcpy(form_a1_n4, "<li>%c.%d.%d.%d %s</li>");
			strcpy(form_a2_n2, form_a1_n2);
			strcpy(form_a2_n3, form_a1_n3);
			strcpy(form_a2_n4, form_a1_n4);
			strcpy(form_a3_n3, form_a1_n3);
			strcpy(form_a3_n4, form_a1_n4);
			strcpy(form_a4_n4, form_a1_n4);
			break;

		case TOTEX:
		case TOPDL:
			strcpy(form_t1_n1, "\\item %d %s");
			strcpy(form_t1_n2, "\\item %d.%d %s");
			strcpy(form_t1_n3, "\\item %d.%d.%d %s");
			strcpy(form_t1_n4, "\\item %d.%d.%d.%d %s");
			strcpy(form_t2_n2, form_t1_n2);
			strcpy(form_t2_n3, form_t1_n3);
			strcpy(form_t2_n4, form_t1_n4);
			strcpy(form_t3_n3, form_t1_n3);
			strcpy(form_t3_n4, form_t1_n4);
			strcpy(form_t4_n4, form_t1_n4);

			strcpy(form_a1_n1, "\\item %d %s");
			strcpy(form_a1_n2, "\\item %d.%d %s");
			strcpy(form_a1_n3, "\\item %d.%d.%d %s");
			strcpy(form_a1_n4, "\\item %d.%d.%d.%d %s");
			strcpy(form_a2_n2, form_t1_n2);
			strcpy(form_a2_n3, form_t1_n3);
			strcpy(form_a2_n4, form_t1_n4);
			strcpy(form_a3_n3, form_t1_n3);
			strcpy(form_a3_n4, form_t1_n4);
			strcpy(form_a4_n4, form_t1_n4);
			break;
		
		/* New in r6pl15 [NHz] */
		case TOKPS:
			strcpy(form_t1_n1, "(%2d ) udoshow %s newline");
			strcpy(form_t1_n2, "(   %2d.%d ) udoshow %s newline");
			strcpy(form_t1_n3, "(         %2d.%d.%d ) udoshow  %s newline");
			strcpy(form_t1_n4, "(               %2d.%d.%d.%d ) udoshow %s newline");
			strcpy(form_t2_n2, "(%2d.%d ) udoshow %s newline");
			strcpy(form_t2_n3, "(      %2d.%d.%d ) udoshow %s newline");
			strcpy(form_t2_n4, "(            %2d.%d.%d.%d ) udoshow %s newline");
			strcpy(form_t3_n3, "(%2d.%d.%d ) udoshow %s newline");
			strcpy(form_t3_n4, "(         %2d.%d.%d.%d ) udoshow %s newline");
			strcpy(form_t4_n4, "(%2d.%d.%d.%d ) udoshow %s newline");

			strcpy(form_a1_n1, "( %c ) udoshow %s newline");
			strcpy(form_a1_n2, "(    %c.%d ) udoshow %s newline");
			strcpy(form_a1_n3, "(         %c.%d.%d ) udoshow  %s newline");
			strcpy(form_a1_n4, "(                 %c.%d.%d.%d ) udoshow %s newline");
			strcpy(form_a2_n2, "( %c.%d ) udoshow %s newline");
			strcpy(form_a2_n3, "(      %c.%d.%d ) udoshow %s newline");
			strcpy(form_a2_n4, "(              %c.%d.%d.%d ) udoshow %s newline");
			strcpy(form_a3_n3, "( %c.%d.%d ) udoshow %s newline");
			strcpy(form_a3_n4, "(         %c.%d.%d.%d ) udoshow %s newline");
			strcpy(form_a4_n4, "( %c.%d.%d.%d ) udoshow %s newline");
			break;
		
/*		case TOKPS:
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
			strcpy(form_t2_n2, "%2d.%d  %s");
			strcpy(form_t2_n3, "     %2d.%d.%d  %s");
			strcpy(form_t2_n4, "            %2d.%d.%d.%d  %s");
			strcpy(form_t3_n3, "%2d.%d.%d  %s");
			strcpy(form_t3_n4, "       %2d.%d.%d.%d  %s");
			strcpy(form_t4_n4, "%2d.%d.%d.%d  %s");

			strcpy(form_a1_n1, " %c  %s");
			strcpy(form_a1_n2, "    %c.%d  %s");
			strcpy(form_a1_n3, "         %c.%d.%d  %s");
			strcpy(form_a1_n4, "                %c.%d.%d.%d  %s");
			strcpy(form_a2_n2, " %c.%d  %s");
			strcpy(form_a2_n3, "    %c.%d.%d  %s");
			strcpy(form_a2_n4, "           %c.%d.%d.%d  %s");
			strcpy(form_a3_n3, " %c.%d.%d  %s");
			strcpy(form_a3_n4, "        %c.%d.%d.%d  %s");
			strcpy(form_a4_n4, " %c.%d.%d.%d  %s");
			break;
	}

}	/* init_toc_forms_numbers */


LOCAL void init_toc_forms_no_numbers ( void )
{
	char s[32];
	
	switch(desttype)
	{	case TOAQV:
		case TOWIN:
		case TOWH4:
			strcpy(form_t1_n1, "{%s}\\par\\pard");
			strcpy(form_t1_n2, "\\li560{%s}\\par\\pard");
			strcpy(form_t1_n3, "\\li1120{%s}\\par\\pard");
			strcpy(form_t1_n4, "\\li1680{%s}\\par\\pard");
			strcpy(form_t2_n2, "{%s}\\par\\pard");
			strcpy(form_t2_n3, "\\li560{%s}\\par\\pard");
			strcpy(form_t2_n4, "\\li1120{%s}\\par\\pard");
			strcpy(form_t3_n3, "{%s}\\par\\pard");
			strcpy(form_t3_n4, "\\li560{%s}\\par\\pard");
			strcpy(form_t4_n4, "{%s}\\par\\pard");

			strcpy(form_a1_n1, form_t1_n1);
			strcpy(form_a1_n2, form_t1_n2);
			strcpy(form_a1_n3, form_t1_n3);
			strcpy(form_a1_n4, form_t1_n4);
			strcpy(form_a2_n2, form_t2_n2);
			strcpy(form_a2_n3, form_t2_n3);
			strcpy(form_a2_n4, form_t2_n4);
			strcpy(form_a3_n3, form_t3_n3);
			strcpy(form_a3_n4, form_t3_n4);
			strcpy(form_a4_n4, form_t4_n4);
			break;

		case TOHTM:
		case TOMHH:
			strcpy(s, "<li>%s</li>");
			
			strcpy(form_t1_n1, s);
			strcpy(form_t1_n2, s);
			strcpy(form_t1_n3, s);
			strcpy(form_t1_n4, s);
			strcpy(form_t2_n2, s);
			strcpy(form_t2_n3, s);
			strcpy(form_t2_n4, s);
			strcpy(form_t3_n3, s);
			strcpy(form_t3_n4, s);
			strcpy(form_t4_n4, s);

			strcpy(form_a1_n1, s);
			strcpy(form_a1_n2, s);
			strcpy(form_a1_n3, s);
			strcpy(form_a1_n4, s);
			strcpy(form_a2_n2, s);
			strcpy(form_a2_n3, s);
			strcpy(form_a2_n4, s);
			strcpy(form_a3_n3, s);
			strcpy(form_a3_n4, s);
			strcpy(form_a4_n4, s);
			break;

		case TOTEX:
		case TOPDL:
			strcpy(s, "\\item %s");
			
			strcpy(form_t1_n1, s);
			strcpy(form_t1_n2, s);
			strcpy(form_t1_n3, s);
			strcpy(form_t1_n4, s);
			strcpy(form_t2_n2, s);
			strcpy(form_t2_n3, s);
			strcpy(form_t2_n4, s);
			strcpy(form_t3_n3, s);
			strcpy(form_t3_n4, s);
			strcpy(form_t4_n4, s);

			strcpy(form_a1_n1, s);
			strcpy(form_a1_n2, s);
			strcpy(form_a1_n3, s);
			strcpy(form_a1_n4, s);
			strcpy(form_a2_n2, s);
			strcpy(form_a2_n3, s);
			strcpy(form_a2_n4, s);
			strcpy(form_a3_n3, s);
			strcpy(form_a3_n4, s);
			strcpy(form_a4_n4, s);
			break;

		case TOINF:
			strcpy(s, "%s");

			strcpy(form_t1_n1, s);
			strcpy(form_t1_n2, s);
			strcpy(form_t1_n3, s);
			strcpy(form_t1_n4, s);
			strcpy(form_t2_n2, s);
			strcpy(form_t2_n3, s);
			strcpy(form_t2_n4, s);
			strcpy(form_t3_n3, s);
			strcpy(form_t3_n4, s);
			strcpy(form_t4_n4, s);

			strcpy(form_a1_n1, s);
			strcpy(form_a1_n2, s);
			strcpy(form_a1_n3, s);
			strcpy(form_a1_n4, s);
			strcpy(form_a2_n2, s);
			strcpy(form_a2_n3, s);
			strcpy(form_a2_n4, s);
			strcpy(form_a3_n3, s);
			strcpy(form_a3_n4, s);
			strcpy(form_a4_n4, s);
			break;
		
		/* New in r6pl15 [NHz] */
		case TOKPS:
			strcpy(form_t1_n1, " %s newline");
			strcpy(form_t1_n2, "    %s newline");
			strcpy(form_t1_n3, "       %s newline");
			strcpy(form_t1_n4, "          %s newline");
			strcpy(form_t2_n2, " %s newline");
			strcpy(form_t2_n3, "    %s newline");
			strcpy(form_t2_n4, "       %s newline");
			strcpy(form_t3_n3, " %s newline");
			strcpy(form_t3_n4, "    %s newline");
			strcpy(form_t4_n4, " %s newline");

			strcpy(form_a1_n1, " %s newline");
			strcpy(form_a1_n2, "    %s newline");
			strcpy(form_a1_n3, "       %s newline");
			strcpy(form_a1_n4, "          %s newline");
			strcpy(form_a2_n2, " %s newline");
			strcpy(form_a2_n3, "    %s newline");
			strcpy(form_a2_n4, "       %s newline");
			strcpy(form_a3_n3, " %s newline");
			strcpy(form_a3_n4, "    %s newline");
			strcpy(form_a4_n4, " %s newline");
			break;
		
		default:
			strcpy(form_t1_n1, " %s");
			strcpy(form_t1_n2, "    %s");
			strcpy(form_t1_n3, "       %s");
			strcpy(form_t1_n4, "          %s");
			strcpy(form_t2_n2, " %s");
			strcpy(form_t2_n3, "    %s");
			strcpy(form_t2_n4, "       %s");
			strcpy(form_t3_n3, " %s");
			strcpy(form_t3_n4, "    %s");
			strcpy(form_t4_n4, " %s");

			strcpy(form_a1_n1, " %s");
			strcpy(form_a1_n2, "    %s");
			strcpy(form_a1_n3, "       %s");
			strcpy(form_a1_n4, "          %s");
			strcpy(form_a2_n2, " %s");
			strcpy(form_a2_n3, "    %s");
			strcpy(form_a2_n4, "       %s");
			strcpy(form_a3_n3, " %s");
			strcpy(form_a3_n4, "    %s");
			strcpy(form_a4_n4, " %s");
			break;
	}

}	/* init_toc_forms_no_numbers */



GLOBAL void init_module_toc_pass2 ( void )
{
	char sF[128], sS[128];

	form_t1_n1[0]= EOS;		form_t1_n2[0]= EOS;		form_t1_n3[0]= EOS;
	form_a1_n1[0]= EOS;		form_a1_n2[0]= EOS;		form_a1_n3[0]= EOS;

	form_t2_n2[0]= EOS;		form_t2_n3[0]= EOS;
	form_a2_n2[0]= EOS;		form_a2_n3[0]= EOS;

	form_t3_n3[0]= EOS;
	form_a3_n3[0]= EOS;

	if (no_numbers)
	{	init_toc_forms_no_numbers();
	}
	else
	{	init_toc_forms_numbers();
	}

	/*r6pl5: die Reinkarnation von !use_short_tocs*/
	if (use_short_tocs)
	{	subtocs1_depth= 1;
		subtocs2_depth= 1;
		subtocs3_depth= 1;
	}

	if (subtocs1_depth<=0 || subtocs1_depth>9)
	{	subtocs1_depth= 9;
	}

	if (subtocs2_depth<=0 || subtocs2_depth>9)
	{	subtocs2_depth= 9;
	}

	if (subtocs3_depth<=0 || subtocs3_depth>9)
	{	subtocs3_depth= 9;
	}
	
	/* Die Formatkommando angeben, die fuer die Inhaltsausgabe */
	/* verwendet werden, um die Einrueckungen der Listen */
	/* zu erzeugen */
	switch (desttype)	/* r6pl2 */
	{
		case TOHTM:
		case TOMHH:
			/* Changed in r6pl16 [NHz] */
			strcpy(toc_list_top,	"<ul class=\"content\">");
			strcpy(toc_list_end,	"</ul>");
			use_toc_list_commands= TRUE;
			break;
		case TOTEX:
		case TOPDL:
			strcpy(toc_list_top,	"\\begin{itemize}\n\\itemsep 0pt\n\\parsep 0pt\n\\parskip 0pt");
			strcpy(toc_list_end,	"\\end{itemize}");
			use_toc_list_commands= TRUE;
			break;
		default:
			toc_list_top[0]= EOS;
			toc_list_end[0]= EOS;
			use_toc_list_commands= FALSE;
			break;
	}

	if (html_frames_layout)
	{	sprintf(html_target, " target=\"%s\"", FRAME_NAME_CON);
	}
	else
	{	html_target[0]= EOS;
	}

	/* Font-Tags vorbestimmen */

	sF[0]= 0;
	sS[0]= 0;
	sHtmlPropfontStart[0]= EOS;
	sHtmlPropfontEnd[0]= EOS;
	iDocHtmlPropfontSize= 0;

	if (sDocHtmlPropfontName[0]!=EOS)
	{	sprintf(sF, " face=\"%s\"", sDocHtmlPropfontName);
	}
	if (sDocHtmlPropfontSize[0]!=EOS)
	{	sprintf(sS, " size=\"%s\"", sDocHtmlPropfontSize);
		iDocHtmlPropfontSize= atoi(sDocHtmlPropfontSize);
	}

	if (sF[0]!=EOS || sS[0]!=EOS)
	{	sprintf(sHtmlPropfontStart, "<font%s%s>", sF, sS);
		strcpy(sHtmlPropfontEnd, "</font>");
	}

	sF[0]= 0;
	sS[0]= 0;
	sHtmlMonofontStart[0]= EOS;
	sHtmlMonofontEnd[0]= EOS;
	iDocHtmlMonofontSize= 0;

	if (sDocHtmlMonofontName[0]!=EOS)
	{	sprintf(sF, " face=\"%s\"", sDocHtmlMonofontName);
	}
	if (sDocHtmlMonofontSize[0]!=EOS)
	{	sprintf(sS, " size=\"%s\"", sDocHtmlMonofontSize);
		iDocHtmlMonofontSize= atoi(sDocHtmlMonofontSize);
	}

	if (sF[0]!=EOS || sS[0]!=EOS)
	{	sprintf(sHtmlMonofontStart, "<font%s%s>", sF, sS);
		strcpy(sHtmlMonofontEnd, "</font>");
	}

}	/* init_module_toc_pass2 */


/*	############################################################
	#
	# Modulcheck
	#
	############################################################	*/
GLOBAL BOOLEAN check_module_toc_pass1 ( void )
{
	int i, j;
	char s[512], sTyp[32], sNode[256];
	BOOLEAN ret= TRUE;
	BOOLEAN checkString;

	/* Schauen, ob bei Hypertextformaten Dinge eindeutig benutzt werden */
	switch (desttype)
	{
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
			for (i=1; i<=p1_lab_counter; i++)
			{
				for (j=i+1; j<=p1_lab_counter; j++)
				{
					if (strcmp(lab[i]->name, lab[j]->name)==0)
					{
						sprintf(s, "label \"%s\" used twice", lab[i]->name);
						fatal_message(s);

						sNode[0]= EOS;
						strcpy(sTyp, "as a label");
						if (lab[i]->is_node)
						{	strcpy(sTyp, "as a node");
						}
						if (lab[i]->is_alias)
						{	strcpy(sTyp, "as an alias");
						}
						if (!lab[i]->is_node)
						{	sprintf(sNode, " in node '%s'", toc[lab[i]->tocindex]->name);
						}
						sprintf(s, "1. %s%s", sTyp, sNode);
						note_message(s);

						sNode[0]= EOS;
						strcpy(sTyp, "as a label");
						if (lab[j]->is_node)
						{	strcpy(sTyp, "as a node");
						}
						if (lab[j]->is_alias)
						{	strcpy(sTyp, "as an alias");
						}
						if (!lab[j]->is_node)
						{	sprintf(sNode, " in node '%s'", toc[lab[j]->tocindex]->name);
						}
						sprintf(s, "2. %s%s", sTyp, sNode);
						note_message(s);

						ret= FALSE;
					}
				}
			}
			break;
	}

	/* Doppelt vergebene HTML-Dateinamen testen, dabei das Mergen non Nodes beachten */
	/* Werden Nodes in einer Datei vereint, dann besitzen die unteren Ebenen den */
	/* gleichen Dateinamen wie die obere Ebene! r6pl13 */

	switch (desttype)
	{
		case TOHTM:
		case TOMHH:
			if (!html_merge_node1)
			{
				show_status_info("Checking HTML file names...");

				for (i=0; i<p1_toc_counter; i++)
				{
					for (j=i+1; j<p1_toc_counter; j++)
					{
						checkString= FALSE;

						if (html_merge_node4)
						{
							checkString= ( (toc[i]->n1 != toc[j]->n1) || (toc[i]->n2 != toc[j]->n2) || (toc[i]->n3 != toc[j]->n3));
						}

						if (html_merge_node3)
						{
							checkString= ( (toc[i]->n1 != toc[j]->n1) || (toc[i]->n2 != toc[j]->n2) );
						}

						if (html_merge_node2)
						{
							checkString= (toc[i]->n1 != toc[j]->n1);
						}


						if (checkString && strcmp(toc[i]->filename, toc[j]->filename)==0)
						{
							sprintf(s, "file name \"%s\" used in \"%s\" and \"%s\"",
								toc[i]->filename,
								toc[i]->name,
								toc[j]->name);
	
							fatal_message(s);
							ret= FALSE;
						}
					}
				}
			}
			break;
	}

	return ret;

}	/* check_module_toc_pass1 */


GLOBAL BOOLEAN check_module_toc_pass2 ( void )
{
	int i;
	char s[512];

	show_status_info("");
	show_status_info("Checking usage of labels and aliases...");
	for (i=1; i<p1_lab_counter; i++)
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
}	/* check_module_toc_pass2 */



/*	############################################################
	#
	# Modulinit
	#
	############################################################	*/
GLOBAL void init_module_toc ( void )
{
	register int i;

	/*	--------------------------------------------------------------	*/
	/*	In diesen Flags merkt sich UDO, welche Art von Node gerade		*/
	/*	aktiv ist (!node, !subnode, etc.)								*/
	/*	--------------------------------------------------------------	*/
	active_nodetype= TOC_NONE;


	/*	--------------------------------------------------------------	*/
	/*	toc_offset enthaelt einen Offset fuer die Kapitelnumerierung	*/
	/*	Das erste Kapitel erhaelt dann die Nummer (1+toc_offset)		*/
	/*	toc_offset kann auch negativ werden.							*/
	/*	Die anderen Offsets entsprechend								*/
	/*	--------------------------------------------------------------	*/
	toc_offset= 0;
	subtoc_offset= 0;
	subsubtoc_offset= 0;
	subsubsubtoc_offset= 0;


	/*	--------------------------------------------------------------	*/
	/*	Zeiger auf den aktuellen Node, Subnode und Subsubnode			*/
	/*	Mit diesen Variablen kann man toc[] direkt adressieren			*/
	/*	--------------------------------------------------------------	*/
	curr_n1_index= 0;
	curr_n2_index= 0;
	curr_n3_index= 0;


	/*	--------------------------------------------------------------	*/
	/*	Wenn auch nur ein Node existiert, dann kann ein !toc			*/
	/*	ausgegeben werden. toc_available wird dann TRUE					*/
	/*	--------------------------------------------------------------	*/
	toc_available= FALSE;
	apx_available= FALSE;


	/*	--------------------------------------------------------------	*/
	/*	Hier werden die absoluten Kapitelnummern vermerkt. Diese		*/
	/*	Nummern weichen von den Nummern in den Inhaltsverzeichnissen	*/
	/*	ab, falls unsichtbare Nodes (!node*) benutzt werden.			*/
	/*	Beispiele:														*/
	/*	1  Node:        n1=1, n2=0, n3=0, n4=0							*/
	/*	1.2  Node:      n1=1, n2=2, n3=0, n4=0							*/
	/*	1.2.3  Node:    n1=1, n2=2, n3=3, n4=0							*/
	/*	1.2.3.4  Node:  n1=1, n2=2, n3=3, n4=4							*/
	/*	--------------------------------------------------------------	*/
	p1_toc_n1= 0;	p1_toc_n2= 0;	p1_toc_n3= 0;	p1_toc_n4= 0;
	p1_apx_n1= 0;	p1_apx_n2= 0;	p1_apx_n3= 0;	p1_apx_n4= 0;

	p2_toc_n1= 0;	p2_toc_n2= 0;	p2_toc_n3= 0;	p2_toc_n4= 0;
	p2_apx_n1= 0;	p2_apx_n2= 0;	p2_apx_n3= 0;	p2_apx_n4= 0;


	/*	--------------------------------------------------------------	*/
	/*	Hier nun die Nummern, wie sie im Inhaltsverzeichis erscheinen	*/
	/*	--------------------------------------------------------------	*/
	p1_toc_nr1= 0;	p1_toc_nr2= 0;	p1_toc_nr3= 0;	p1_toc_nr4= 0;
	p1_apx_nr1= 0;	p1_apx_nr2= 0;	p1_apx_nr3= 0;	p1_apx_nr4= 0;



	/*	--------------------------------------------------------------	*/
	/*	In diesen Variablen werden die Indizes der letzten Kapitel		*/
	/*	gesichert. Sie sind sehr wichtig, um die Links zu den 			*/
	/*	uebergeordneten Kapiteln in Hypertexten ohne lange Sucherei		*/
	/*	erstellen zu koennen.											*/
	/*	--------------------------------------------------------------	*/
	last_n1_index= 0;
	last_n2_index= 0;
	last_n3_index= 0;
	last_n4_index= 0;


	/*	--------------------------------------------------------------	*/
	/*	Dieses Flag wird TRUE gesetzt, wenn das Inhaltsverzeichnis		*/
	/*	mit !tableofcontents aufgerufen wird. Nodes koenne dann auf		*/
	/*	dieses Inhaltsverzeichnis verweisen (z.B: ST-Guide per @toc)	*/
	/*	--------------------------------------------------------------	*/
	called_tableofcontents= FALSE;
	
	/*	--------------------------------------------------------------	*/
	/*	Dieses Flag wird TRUE gesetzt, wenn die vierte Gliederungs-		*/
	/*	Ebene benutzt wird. In der LaTeX-Preambel mussen dann einige	*/
	/*	Befehle zusaetzlich ausgegeben werden.							*/
	/*	--------------------------------------------------------------	*/
	called_subsubsubnode= FALSE;


	/*	--------------------------------------------------------------	*/
	/*	p1_toc_counter enthaelt die Anzahl der in pass1() eingelesenen	*/
	/*	Eintraege fuer das toc[]-Array. Nach pass1() enthaelt			*/
	/*	toc[p1_toc_counter] die Daten des letzten Kapitels.				*/
	/*	p2_toc_counter ist entsprechend ein Zaehler fuer den pass2().	*/
	/*	Waehren pass2() zeigt p2_toc_counter auf den aktuellen Eintrag	*/
	/*	des toc[]-Arrays.												*/
	/*	--------------------------------------------------------------	*/
	p1_toc_counter= 0;
	p2_toc_counter=	0;	


	/*	--------------------------------------------------------------	*/
	/*	toc[]-Array ausnullen und Inhaltsverzeichnis "eintragen"		*/
	/*	--------------------------------------------------------------	*/
	for (i=0; i<MAXTOCS; toc[i++]= NULL) ;
	add_toc_to_toc();	/* r5pl6 */


	/*	--------------------------------------------------------------	*/
	/*	lab[]-Array mit den Daten der referenzierbaren Stellen des		*/
	/*	Dokumentes ausnullen und Zaehler zuruecksetzen.					*/
	/*	--------------------------------------------------------------	*/
	for (i=0; i<MAXLABELS; lab[i++]= NULL) ;
	p1_lab_counter= 0;
	p2_lab_counter= 0;

	/*	--------------------------------------------------------------	*/
	/*	Kapitelzaehler zuruecksetzen									*/
	/*	--------------------------------------------------------------	*/
	
	all_nodes= 0;			/* r5pl7 */
	all_subnodes= 0;
	all_subsubnodes= 0;
	all_subsubsubnodes= 0;


	/*	--------------------------------------------------------------	*/
	/*	Die Zeichen setzen, die beim Referenzieren vor und nach einem	*/
	/*	gefundenen Label erlaubt sind.									*/
	/*	--------------------------------------------------------------	*/

	sprintf(allowed_next_chars, "\033 !\"#$%%&'()*+,-./:;<=>?@[\\]^_`{|}~%c%c%c", TILDE_C, NBSP_C, INDENT_C);
	strcpy(allowed_prev_chars, allowed_next_chars);


	uses_tableofcontents= FALSE;	/* r5pl12 */
	
	current_chapter_name[0]= EOS;	/* r5pl16 */
	current_chapter_nr[0]= EOS;		/* r5pl16 */
	
	footer_buffer[0]= EOS;			/* r6pl2 */

	subtocs1_depth= 9;				/*r6pl2*/
	subtocs2_depth= 9;				/*r6pl2*/
	subtocs3_depth= 9;				/*r6pl2*/

	no_auto_toptocs_icons= FALSE;	/*r6pl13*/

	strcpy(html_modern_width, "128");		/*r6pl8*/
	html_modern_backcolor[0]= EOS;			/*r6pl6*/

	strcpy(html_frames_width, "128");		/*r6pl8*/
	strcpy(html_frames_height, "64");		/*r6pl9*/
	html_frames_backcolor[0]= EOS;			/*r6pl6*/
	html_frames_textcolor[0]= EOS;			/*r6pl9*/
	html_frames_linkcolor[0]= EOS;			/*r6pl9*/
	html_frames_alinkcolor[0]= EOS;			/*r6pl9*/
	html_frames_vlinkcolor[0]= EOS;			/*r6pl9*/
	html_frames_position= POS_LEFT;			/*r6pl9*/
	html_frames_backimage[0]= EOS;
	html_name_prefix[0]= EOS;				/*r6pl12*/

	p1_toctype= TOC_NONE;	/*r6pl5*/
	p2_toctype= TOC_NONE;	/*r6pl5*/

	sHtmlPropfontStart[0]= EOS;		/*r6pl7*/
	sHtmlPropfontEnd[0]= EOS;		/*r6pl7*/

	sHtmlMonofontStart[0]= EOS;		/*r6pl7*/
	sHtmlMonofontEnd[0]= EOS;		/*r6pl7*/

}	/* init_module_toc */


LOCAL void free_toc_data ( char **var )
{
	if (*var!=NULL)
	{	um_free(*var);
		*var= NULL;
	}
}


GLOBAL void exit_module_toc ( void )
{
	register int i;

	for (i=MAXTOCS-1; i>=0; i--)
	{
		if (toc[i]!=NULL)
		{
			free_toc_data( &(toc[i]->counter_command) );
			free_toc_data( &(toc[i]->keywords) );
			free_toc_data( &(toc[i]->description) );
			free_toc_data( &(toc[i]->helpid) );
			free_toc_data( &(toc[i]->image) );
			free_toc_data( &(toc[i]->icon) );
			free_toc_data( &(toc[i]->icon_active) );
			free_toc_data( &(toc[i]->icon_text) );
			free_toc_data( &(toc[i]->raw_header_filename) );
			free_toc_data( &(toc[i]->raw_footer_filename) );
			um_free(toc[i]);
			toc[i]= NULL;
		}
	}

	for (i=MAXLABELS-1; i>=0; i--)
	{
		if (lab[i]!=NULL)
		{
			um_free(lab[i]);
		}
	}

}	/* exit_module_toc */


/*	############################################################
	# toc.c
	############################################################	*/

