/*	############################################################
	# @(#) toc.h
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
	############################################################	*/

/*	############################################################
	# Typen
	############################################################	*/

#define	MAX_LABEL_LEN		128
#define	MAX_NODE_LEN		199 /* v6.3.9 (old: 128) */
#define	MAX_FILENAME_LEN	64
#define	MAX_IMAGE_LEN		128
#define	MAX_COLOR_LEN		16
#define	MAX_HELPID_LEN		16

#ifndef __UDOTOC__
#define __UDOTOC__

/*	--------------------------------------------------
	Labels: Sprungmarken, die referenziert werden
	--------------------------------------------------	*/
typedef struct _label
{
	char	name[MAX_LABEL_LEN+1];		/* Name eines Labels 	*/
	int		labindex;		/* lab[1]==1, lab[2]==2 etc.		*/
	size_t	len;			/* Laenge des Labels				*/
	int		n1;				/* ist in diesem Kapitel definiert	*/
	int		n2;				/* ... Abschnitt					*/
	int		n3;				/* ... Unterabschnitt				*/
	int		n4;				/* ... Unterabschnitt				*/
	BOOLEAN	appendix;		/* Das Label steht im Anhang		*/
	BOOLEAN is_node;		/* Das Label ist die Ueberschrift	*/
	BOOLEAN is_popup;		/* Der Node soll ein Popup sein		*/
	BOOLEAN is_alias;		/* Nur ein Zweitname des Nodes		*/
	int		tocindex;		/* Gehoert zum Node "toc[tocindex]"	*/
	BOOLEAN	ignore_links;	/* Keine Links auf dieses anlegen	*/	/* r5pl8 */
	BOOLEAN	ignore_index;	/* Keine Links auf dieses anlegen	*/	/* r5pl8 */
	BOOLEAN	referenced;		/* Wurde es referenziert?			*/	/* r6pl9 */
}	LABEL, *pLABEL;


/*	--------------------------------------------------
	Eintraege fuer das Inhaltsverzeichnis
	--------------------------------------------------	*/
typedef struct _tocitem
{
	char	name[MAX_NODE_LEN+1];			/* Der Eintrag selber				*/
	int		n1;								/* Kapitelnummer (absolut)			*/
	int		n2;								/* Abschnittnummer (absolut)		*/
	int		n3;								/* Unterabschnittnummer	(absolut)	*/
	int		n4;								/* Unterabschnittnummer	(absolut)	*/
	int		nr1, nr2, nr3, nr4;				/* Inhaltsverzeichnis-Nummern		*/
	BOOLEAN	appendix;						/* Steht im Anhang					*/
	int		toctype;						/* !node, !subnode oder !subsubnode	*/
	char	filename[MAX_FILENAME_LEN+1];	/* HTML-Filename					*/	/* r5pl3 */
	char	dirname[MAX_FILENAME_LEN+1];	/* HTML-Verzeichnisname				*/	/* r6pl6 */
	char	*keywords;						/* HTML-Keywords					*/	/* r5pl3 */
	char	*description;					/* HTML-Description					*/	/* r6pl5 */
	char	*counter_command;				/* HTML-Kommandos fuer Counter		*/	/* r5pl4 */
	char	backcolor[MAX_COLOR_LEN+1];		/* HTML <BODY BGCOLOR=...>			*/	/* r6pl1 */
	char	textcolor[MAX_COLOR_LEN+1];		/* HTML <BODY TEXT=...>				*/	/* r6pl1 */
	char	linkcolor[MAX_COLOR_LEN+1];		/* HTML <BODY LINK=...>				*/	/* r6pl1 */
	char	alinkcolor[MAX_COLOR_LEN+1];	/* HTML <BODY ALINK=...>			*/	/* r6pl1 */
	char	vlinkcolor[MAX_COLOR_LEN+1];	/* HTML <BODY VLINK=...>			*/	/* r6pl1 */
	char	modern_backcolor[MAX_COLOR_LEN+1];	/* HTML <BODY BGCOLOR=...>		*/	/* r6pl12 */
	char	modern_textcolor[MAX_COLOR_LEN+1];	/* HTML <BODY TEXT=...>			*/	/* r6pl12 */
	char	modern_linkcolor[MAX_COLOR_LEN+1];	/* HTML <BODY LINK=...>			*/	/* r6pl12 */
	char	modern_alinkcolor[MAX_COLOR_LEN+1];	/* HTML <BODY ALINK=...>		*/	/* r6pl12 */
	char	modern_vlinkcolor[MAX_COLOR_LEN+1];	/* HTML <BODY VLINK=...>		*/	/* r6pl12 */
	char	backimage[MAX_IMAGE_LEN+1];		/* HTML <BODY BACKGROUND=...>		*/	/* r6pl1 */
	char	style_name[MAX_IMAGE_LEN+1]; 			/* HTML <STYLE> r6pl15 [NHz] */

	char	script_name[MAX_IMAGE_LEN+1]; 		/* HTML <SCRIPT> r6pl15 [NHz] */

	char	favicon_name[MAX_IMAGE_LEN+1]; 		/* HTML <FAVICON> r6pl15 [NHz] */

	char	*image;							/* Grafik anstelle Kapitelnamen		*/
	unsigned int uiImageWidth;				/* Breite und Hoehe des Bildes		*/ 
	unsigned int uiImageHeight;
	char	*icon;							/* Icon fuer modernes Layout		*/
	unsigned int uiIconWidth;				/* Breite und Hoehe des Icons		*/ 
	unsigned int uiIconHeight;
	char	*icon_active;					/* Icon fuer    -""- (aktive Seite)	*/
	unsigned int uiIconActiveWidth;			/* Breite und Hoehe des Icons		*/ 
	unsigned int uiIconActiveHeight;
	char	*icon_text;						/* Icontext fuer modernes Layout	*/
	char	*helpid;						/* Eine Jump-ID, wie ein Alias		*/
	int		mapping;						/* Eine Jump-ID fuer WinHelp/IPF	*/	/* r6pl7 */
	BOOLEAN	invisible;			/* Nicht ins Inhaltsverzeichnis		*/
	BOOLEAN	converted;			/* Bereits Makros etc. angepasst?	*/
	int		labindex;			/* lab[]-Position					*/	/* r5pl6 */
	int		prev_index;			/* toc[]-Position des HTML-Vorgaengers	*/	/* r5pl6 */
	int		next_index;			/* toc[]-Position des HTML-Nachfolgers	*/	/* r5pl6 */
	int		up_n1_index;		/* toc[]-Position oberhalb			*/
	int		up_n2_index;
	int		up_n3_index;
	int		count_n2;			/* Anzahl enthaltener Subnodes		*/	/* r6pl8 */
	int		count_n3;			/* Anzahl enthaltener Subsubnodes	*/	/* r6pl8 */
	int		count_n4;			/* Anzahl enthaltener Subsubsub...	*/	/* r6pl8 */
	BOOLEAN	ignore_subtoc;		/* !use_auto_subtoc's ignorieren	*/	/* r5pl6 */
	BOOLEAN	ignore_links;		/* Keine Links auf dieses anlegen	*/	/* r5pl8 */
	BOOLEAN	ignore_index;		/* Keinen Indexeintrag anlegen		*/	/* r5pl10 */
	BOOLEAN	ignore_title;		/* Keine Ueberschrift erzeugen		*/	/* r6pl13 */
	BOOLEAN	ignore_headline;	/* Keine Kopfzeile erzeugen			*/	/* r5pl12 */
	BOOLEAN	ignore_bottomline;	/* Keine Fusszeile erzeugen			*/	/* r5pl12 */
	BOOLEAN	ignore_footer;		/* Keinen Footer erzeugen			*/	/* r6pl2 */
	char	*raw_header_filename;										/* r6pl10*/
	char	*raw_footer_filename;										/* r6pl10*/
	BOOLEAN	ignore_raw_header;	/* Keinen Userdef-Header einlesen?	*/	/* r6pl10 */
	BOOLEAN	ignore_raw_footer;	/* Keinen Userdef-Footer einlesen?	*/	/* r6pl10 */
	BOOLEAN has_children;		/* Hat der Node einen Subnode etc.?	*/

}	TOCITEM, *pTOCITEM;


/*	--------------------------------------------------
	Platzhalter fuer automatische Referenzen
	--------------------------------------------------	*/
typedef struct _reference
{
	char	magic[6];				/* Eine Steuermarke <ESC><0x80+nr> */
	char	entry[MAX_TOKEN_LEN*2];	/* ergibt max. 256 Zeichen         */
}	REFERENCE;


#endif /* __UDOTOC__ */


/*	############################################################
	# globale Variablen
	############################################################	*/
GLOBAL int		toc_offset;					/* Offsets fuer Kapitelnumerierung, Default=0	*/
GLOBAL int		subtoc_offset;
GLOBAL int		subsubtoc_offset;
GLOBAL int		subsubsubtoc_offset;

GLOBAL int		all_nodes, all_subnodes, all_subsubnodes, all_subsubsubnodes;

GLOBAL BOOLEAN	bInsideAppendix,		/* Ist UDO im Anhang?					*/
				bInsideDocument,		/* Ist UDO im Dokument selber?			*/
				bInsidePopup;			/* In einem Popup-Node?					*/

GLOBAL BOOLEAN	called_tableofcontents;	/* Wurde toc ausgegeben? (@toc) */
GLOBAL BOOLEAN	called_subsubsubnode;

GLOBAL BOOLEAN	uses_tableofcontents;	/* !tableofcontents wird benutzt */

/* 
 * 6.3.11 [vj]
 * This is needed, because current_node_name_sys needs to buffer a lot of stuff!
 */
GLOBAL char		current_node_name_sys[CNNS_LEN];
/*GLOBAL char		current_node_name_sys[MAX_NODE_LEN+1];*/ /* New in r6pl15 [NHz] */
GLOBAL char		current_chapter_name[MAX_NODE_LEN+1];
GLOBAL char		current_chapter_nr[32];

GLOBAL int		subtocs1_depth;			/*r6pl2*/
GLOBAL int		subtocs2_depth;			/*r6pl2*/
GLOBAL int		subtocs3_depth;			/*r6pl2*/

GLOBAL char		sHtmlPropfontStart[256];	/*r6pl7*/
GLOBAL char		sHtmlPropfontEnd[16];		/*r6pl7*/

GLOBAL char		sHtmlMonofontStart[256];	/*r6pl7*/
GLOBAL char		sHtmlMonofontEnd[16];		/*r6pl7*/

/*	############################################################
	# globale Funktionen
	############################################################	*/
GLOBAL BOOLEAN is_node_link ( const char *link, char *node, int *ti, BOOLEAN *isnode, int *li );
GLOBAL int getLabelIndexFromTocIndex ( int *li, const int ti );

GLOBAL void reset_refs ( void );
GLOBAL void auto_references ( char *s, const BOOLEAN for_toc, const char *pic,
							 const unsigned int uiWidth, const unsigned int uiHeight);

GLOBAL void check_endnode ( void );

GLOBAL void check_output_raw_header ( void );
GLOBAL void check_output_raw_footer ( BOOLEAN lastNode );

GLOBAL void man_headline ( void );
GLOBAL void man_bottomline ( void );
GLOBAL void stg_headline ( const char *numbers, const char *nodename );
GLOBAL void tvh_headline ( const char *s );
GLOBAL void output_html_header ( const char *t );
GLOBAL void html_save_frameset ( void );
GLOBAL void html_headline ( void );
GLOBAL void html_bottomline ( void );
GLOBAL void html_footer ( void );

GLOBAL void hh_headline ( void );
GLOBAL void hh_bottomline ( void );
GLOBAL BOOLEAN save_htmlhelp_contents ( const char* filename );
GLOBAL BOOLEAN save_htmlhelp_index ( const char* filename );

/*	############################################################
	# Kapitelkommandos
	############################################################	*/
GLOBAL void c_node ( void );
GLOBAL void c_node_iv ( void );
GLOBAL void c_pnode ( void );
GLOBAL void c_pnode_iv ( void );

GLOBAL void c_subnode ( void );
GLOBAL void c_subnode_iv ( void );
GLOBAL void c_psubnode ( void );
GLOBAL void c_psubnode_iv ( void );

GLOBAL void c_subsubnode ( void );
GLOBAL void c_subsubnode_iv ( void );
GLOBAL void c_psubsubnode ( void );
GLOBAL void c_psubsubnode_iv ( void );

GLOBAL void c_subsubsubnode ( void );
GLOBAL void c_subsubsubnode_iv ( void );
GLOBAL void c_psubsubsubnode ( void );
GLOBAL void c_psubsubsubnode_iv ( void );

GLOBAL void c_endnode ( void );

GLOBAL void c_begin_node ( void );
GLOBAL void c_begin_node_iv ( void );
GLOBAL void c_begin_pnode ( void );
GLOBAL void c_begin_pnode_iv ( void );

GLOBAL void c_end_node ( void );

/*	############################################################
	# Inhaltsverzeichnis(se) ausgeben
	############################################################	*/
GLOBAL void c_toc ( void );
GLOBAL void c_subtoc ( void );
/*	GLOBAL void c_subsubtoc ( void );		*/
/*	GLOBAL void c_subsubsubtoc ( void );	*/

GLOBAL void c_listoffigures ( void );
GLOBAL void c_listoftables ( void );
GLOBAL void c_tableofcontents ( void );

GLOBAL BOOLEAN bookmarks_ps ( void );

/*	############################################################
	# Ein Label im zweiten Durchgang ausgeben
	############################################################	*/
GLOBAL void c_label ( void );
GLOBAL void c_alias ( void );

/*	############################################################
	# Sonstiges
	############################################################	*/
GLOBAL BOOLEAN add_label ( const char *label, const BOOLEAN isn, const BOOLEAN isp );
GLOBAL BOOLEAN add_alias ( const char *alias, const BOOLEAN isp );


/*	############################################################
	# Inhaltsverzeichnis erweitern
	############################################################	*/
GLOBAL void set_ignore_headline ( void );
GLOBAL void set_ignore_bottomline ( void );
GLOBAL void set_raw_header_filename ( void );
GLOBAL void set_ignore_raw_header ( void );
GLOBAL void set_raw_footer_filename ( void );
GLOBAL void set_ignore_raw_footer ( void );
GLOBAL void set_ignore_footer ( void );
GLOBAL void set_ignore_title ( void );
GLOBAL void set_ignore_links ( void );
GLOBAL void set_ignore_index ( void );
GLOBAL void set_ignore_subtoc ( void );
GLOBAL void set_ignore_popup_title ( void );
GLOBAL void set_helpid ( void );
GLOBAL void set_mapping ( void );
GLOBAL void set_html_doctype ( void );	/* New in r6pl16 [NHz] */
GLOBAL void set_html_header_date ( void );	/* New feature #0000054 in V6.5.2 [NHz] */
GLOBAL void set_html_frames_layout ( void );
GLOBAL void set_html_filename ( void );
GLOBAL void set_html_switch_language ( void );
GLOBAL void set_html_filename_prefix ( void );
GLOBAL void set_html_dirname ( void );
GLOBAL void set_html_counter_command ( void );
GLOBAL void set_html_keywords ( void );
GLOBAL void set_html_description ( void );
GLOBAL void set_html_color ( const int which );
#if 0
	GLOBAL void set_html_backcolor ( void );
	GLOBAL void set_html_textcolor ( void );
	GLOBAL void set_html_linkcolor ( void );
	GLOBAL void set_html_alinkcolor ( void );
	GLOBAL void set_html_vlinkcolor ( void );
#endif
GLOBAL void set_html_backimage ( void );
GLOBAL void set_html_style ( void );
GLOBAL void set_html_script ( void );
GLOBAL void set_html_favicon ( void );
GLOBAL void set_html_special_color ( char *hc );
GLOBAL void set_html_modern_width ( void );
GLOBAL void set_html_modern_alignment ( void );
GLOBAL void set_html_modern_backimage ( void );
GLOBAL void set_html_frames_width ( void );
GLOBAL void set_html_frames_height ( void );
GLOBAL void set_html_frames_alignment ( void );
GLOBAL void set_html_frames_position ( void );
GLOBAL void set_html_frames_backimage ( void );
GLOBAL void set_html_button_alignment ( void );
GLOBAL void set_chapter_image ( void );
GLOBAL void set_chapter_icon ( void );
GLOBAL void set_chapter_icon_active ( void );
GLOBAL void set_chapter_icon_text ( void );

GLOBAL BOOLEAN add_node_to_toc ( const BOOLEAN popup, const BOOLEAN invisible );
GLOBAL BOOLEAN add_subnode_to_toc ( const BOOLEAN popup, const BOOLEAN invisible );
GLOBAL BOOLEAN add_subsubnode_to_toc ( const BOOLEAN popup, const BOOLEAN invisible );
GLOBAL BOOLEAN add_subsubsubnode_to_toc ( const BOOLEAN popup, const BOOLEAN invisible );

GLOBAL BOOLEAN toc_begin_node (const BOOLEAN popup, const BOOLEAN invisible);
GLOBAL void toc_end_node (void);
GLOBAL int is_current_node(int tocindex);
GLOBAL int get_toc_counter(void);
GLOBAL void toc_init_lang(void);



/*	############################################################
	#	Dateien mit den Jump-IDs ausgeben fuer div. Compiler
	############################################################	*/
GLOBAL BOOLEAN save_winhelp_map_c ( void );
GLOBAL BOOLEAN save_winhelp_map_pas ( void );
GLOBAL BOOLEAN save_winhelp_map_vb ( void );
GLOBAL BOOLEAN save_winhelp_map_gfa ( void );

GLOBAL BOOLEAN save_winhelp4_cnt ( void );

/*	############################################################
	# Modulcheck
	############################################################	*/
GLOBAL BOOLEAN check_module_toc_pass1 ( void );
GLOBAL BOOLEAN check_module_toc_pass2 ( void );

/*	############################################################
	# Modulfunktionen
	############################################################	*/
GLOBAL void init_module_toc_pass2 ( void );
GLOBAL void init_module_toc ( void );
GLOBAL void exit_module_toc ( void );

/*	############################################################
	# toc.h
	############################################################	*/

