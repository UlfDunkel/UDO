#ifndef CONSTANT_H
#define CONSTANT_H

/*	############################################################
	# @(#) constant.h
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

#define	TOASC			0		/* ASCII					*/
#define	TOMAN			1		/* ASCII (formatiert)		*/
#define	TOSTG			2		/* ST-Guide-Quelltext		*/
#define	TOTEX			3		/* LaTeX					*/
#define	TORTF			4		/* RTF						*/
#define	TOPCH			5		/* PC-HELP					*/
#define	TOHTM			6		/* HTML (World Wide Web)	*/
#define	TOWIN			7		/* Windows-Hilfe			*/
#define	TOINF			8		/* GNU-Texinfo				*/
#define	TOTVH			9		/* Turbo-Vision-Help		*/
#define	TOLDS			10		/* Linuxdoc-SGML			*/
#define	TOAQV			11		/* Apple-QuickView			*/	/* PL6    */
#define	TOHPH			12		/* HP Helptag SGML			*/	/* PL10   */
#define	TOLYX			13		/* LyX						*/	/* PL13   */
#define	TONRO			14		/* nroff, was auch immer	*/	/* PL15   */
#define	TOSRC			15		/* C-Sourcecode				*/	/* PL16   */
#define	TOSRP			16		/* Pascal-Sourcecode		*/	/* Pl16   */
#define	TOIPF			17		/* OS/2-IPF-Format			*/	/* r6pl2  */
#define	TODRC			18		/* Dave's Readme Compiler	*/	/* r6pl2  */
#define	TOMHH			19		/* HTMLHelp					*/	/* r6pl2  */
#define	TOPDL			20		/* PDFLaTeX					*/	/* r6pl8  */
#define	TOWH4			21		/* WinHelp4					*/	/* r6pl8  */
#define	TOUDO			22		/* UDO-Format				*/	/* r6pl9  */
#define	TOKPS			23		/* Krueger's PostScript		*/	/* r6pl11 */
#define	TOAMG			24		/* AmigaGuide				*/	/* r6pl12 */
#define	MAXDESTTYPE		25		/* Anzahl Ausgabeformate	*/

#define	TOGER			0		/* Deutsch					*/
#define	TOENG			1		/* Englisch					*/
#define	TOFRA			2		/* Franzoesisch				*/
#define	TOITA			3		/* Italienisch				*/
#define	TOSPA			4		/* Spanisch					*/
#define	TOSWE			5		/* Schwedisch				*/
#define	TOPOR			6		/* Portugiesisch			*/
#define	TODUT			7		/* Hollaendisch				*/
#define	TODAN			8		/* Daenisch					*/
#define	TONOR			9		/* Norwegisch				*/
#define	TOFIN			10		/* Finnisch					*/

#define	MAXDESTLANG		7		/* Anzahl Ausgabesprachen	*/


/*	############################################################
	# Konstanten fuer Dateitypen, die in myFwopen() und myFwbopen()
	# aus file.h verwendet werden.
	############################################################	*/

#define	FTGIF			32		/* Filetype GIF					*/	/* fuer myFwopen() */
#define	FTIMG			33		/* Filetype GEM-Image			*/
#define	FTEPS			34		/* Filetype EPS					*/
#define	FTJPG			35		/* Filetype JPEG				*/
#define	FTBMP			36		/* Filetype Windows-Bitmap		*/
#define	FTHPJ			37		/* Filetype WinHelp-Project		(ASCII)	*/
#define	FTHHP			38		/* Filetype HTML-Help-Project	(ASCII)	*/
#define	FTHHK			39		/* Filetype HTML-Help-Index		(HTML)	*/
#define	FTHHC			40		/* Filetype HTML-Help-Contents	(HTML)	*/
#define	FTCNT			41		/* Filetype WinHelp-Contents	(ASCII)	*/


/*	############################################################
	#	Umgebungen
	############################################################	*/

#define	MAXENVLEVEL		10		/* max. Umgebungstiefe	*/


#define	ENV_NONE			0x00	/* keine Umgebung		*/	/*r6pl2*/
#define	ENV_ITEM			0x01	/* itemize				*/
#define	ENV_ENUM			0x02	/* enumerate			*/
#define	ENV_DESC			0x03	/* description			*/
#define	ENV_LIST			0x04	/* ?list				*/
#define	ENV_CENT			0x05	/* center				*/
#define	ENV_QUOT			0x06	/* quote				*/
#define	ENV_RIGH			0x07	/* flushright			*/
#define	ENV_LEFT			0x08	/* flushleft			*/
									/* Platz fuer neue		*/
#define	ENV_VERBATIM		0x10	/* verbatim				*/	/*r6pl2*/
#define	ENV_RAW				0x11	/* raw					*/	/*r6pl2*/
#define	ENV_TABLE			0x12	/* table				*/	/*r6pl2*/
#define	ENV_SOURCECODE		0x13	/* sourcecode			*/	/*r6pl2*/
#define	ENV_COMMENT			0x14	/* comment				*/	/*r6pl2*/
#define	ENV_LINEDRAW		0x15	/* linedraw				*/	/*r6pl5*/
#define	ENV_PREFORMATTED	0x16	/* wie verbatim			*/	/*r6pl5*/

#define	LIST_NORMAL		0		/* Listen-Typ			*/
#define	LIST_BOLD		1
#define	LIST_ITALIC		2
#define	LIST_TYPEWRITER	3

#define	TEX_NONE		0		/* default				*/
#define	TEX_LINDNER		1		/* Lindner-TeX (Atari)	*/
#define	TEX_STRUNK		2		/* CS-TeX (Atari)		*/
#define	TEX_EMTEX		3		/* emTeX (DOS, OS/2)	*/
#define	TEX_MIKTEX		4		/* MikTeX (Win32)		*/
#define	TEX_TETEX		5		/* teTeX (UN*X)			*/

#define	ALIGN_CENT		0		/* alignment-Befehle	*/
#define	ALIGN_LEFT		1
#define	ALIGN_RIGH		2

#define	POS_LEFT		0		/* Frames-Positionen	*/
#define	POS_RIGHT		1
#define	POS_TOP			2
#define	POS_BOTTOM		3

#define	PASS1			0
#define	PASS2			1
#define	PASSU			2

#define	LINELEN			4092	/* max. Zeilenlaenge */
#define	MAX_TOKEN_LEN	199		/* max. Tokenlaenge, v6.3.9: 199 (alt: 128) */
#define	MAX_TOKENS		800		/* max. Worte in einem Absatz */

#define	CNNS_LEN		LINELEN /* 6.3.11 [vj] needed for current_node_name_sys (see toc.h) */

#define	MAXZEILE		70		/* max. Laenge einer Ausgabezeile */
#define	SHORTZEILE		64		/* meckern bei weniger Zeichen */

#define	MAXFILECOUNTER	16		/* max. gleichzeitig geoeffnete Files */


#ifdef __TOS__
#define	MAXTOCS			16383	/* max. Eintraege im Inhaltsverzeichnis r6pl13: vorher 4096 */
#define	MAXLABELS		32767	/* max. Labels (!label) r6pl13: vorher 8192*/
#define MAXSTYLES		32767	/* max. Anzahl an Stylesheets insgesamt / New in V6.5.9 [NHz] */
#else
#define	MAXTOCS			32768	/* max. Eintraege im Inhaltsverzeichnis r6pl13: vorher 4096 */
#define	MAXLABELS		65536	/* max. Labels (!label) r6pl13: vorher 8192*/
#define MAXSTYLES		65536	/* max. Anzahl an Stylesheets insgesamt / New in V6.5.9 [NHz] */
#endif
								
#define	MAXHYPHEN		4096	/* max. Trennregeln mit !hyphen */	/* PL6 */

#if 0
#define	MAXMACROS		130		/* max. Makros (!macro) */
#define	MAXDEFS			130		/* max. Makros (!define) */
#else
#define	MAXMACROS		1024	/* max. Makros (!macro) */
#define	MAXDEFS			1024	/* max. Makros (!define) */
#endif

#define MAX_UDOSYMBOLS		128		/* r6pl5: vorher 32 */
#define	MAX_UDOSYMBOL_LEN	32		/* PL10 */


#define	OFFSET_PHOLD	33		/* ESC/Magic/#+offset/ESC	*/
#define	MAXPHOLDS		300		/* max. Platzhalter pro Absatz r6.3.16[vj]: changed from 200 to 300 */

#define	OFFSET_SPECCMD	33		/* ESC/Magic/#+offset/ESC	*/
#define	MAXSPECCMDS		200		/* max. Platzhalter pro Absatz */

#define	OFFSET_REF		33		/* ESC/Magic/#+offset/ESC	*/
#define	MAXREFERENCES	200		/* maximal soviel Referenzen pro Absatz */

#define	MAXSILBEN		32		/* max. Silben in einem Wort */


/*	############################################################
	# Ein paar aussagekraeftigere Makros
	############################################################	*/

#define	NODE_NORMAL		FALSE
#define	NODE_POPUP		TRUE

#define	NODE_VISIBLE	FALSE
#define	NODE_INVISIBLE	TRUE

#define	VERB_NORMAL		0
#define	VERB_SMALL		1
#define	VERB_TINY		2
#define	VERB_LARGE		3
#define	VERB_HUGE		4

/*	############################################################
	# Index-Konstanten
	############################################################	*/
#define	GIF_HM_INDEX	0
#define	GIF_UP_INDEX	1
#define	GIF_RG_INDEX	2
#define	GIF_LF_INDEX	3
#define	GIF_NOHM_INDEX	4
#define	GIF_NOUP_INDEX	5
#define	GIF_NORG_INDEX	6
#define	GIF_NOLF_INDEX	7
#define	GIF_GER_INDEX	8
#define	GIF_ENG_INDEX	9

#define	HTML_COLOR_BACK				0
#define	HTML_COLOR_TEXT				1
#define	HTML_COLOR_LINK				2
#define	HTML_COLOR_VLINK			3
#define	HTML_COLOR_ALINK			4
#define	HTML_MODERN_COLOR_BACK		5
#define	HTML_MODERN_COLOR_TEXT		6
#define	HTML_MODERN_COLOR_LINK		7
#define	HTML_MODERN_COLOR_VLINK		8
#define	HTML_MODERN_COLOR_ALINK		9

/* New in r6pl16 [NHz] */
#define HTML_OLD	0
#define HTML_STRICT	1
#define HTML_TRANS	2
#define HTML_FRAME	3
#define XHTML_STRICT	4
#define XHTML_TRANS	5
#define XHTML_FRAME	6

/*	############################################################
	# Dateinamen und Sonstiges
	############################################################	*/
#define	GIF_HM_NAME		"udo_hm.gif"
#define	GIF_UP_NAME		"udo_up.gif"
#define	GIF_LF_NAME		"udo_lf.gif"
#define	GIF_RG_NAME		"udo_rg.gif"
#define	GIF_NOHM_NAME	"udo_nohm.gif"
#define	GIF_NOUP_NAME	"udo_noup.gif"
#define	GIF_NOLF_NAME	"udo_nolf.gif"
#define	GIF_NORG_NAME	"udo_norg.gif"
#define	GIF_TP_NAME		"udo_tp.gif"
#define	GIF_FC_NAME		"udo_fc.gif"
#define	GIF_FO_NAME		"udo_fo.gif"
#define	GIF_FS_NAME		"udo_fs.gif"
#define	GIF_MW_NAME		"udo_mw.gif"
#define	GIF_GER_NAME	"udo_ger.gif"
#define	GIF_ENG_NAME	"udo_eng.gif"

#define	BMP_FC_NAME		"udo_fc.bmp"
#define	BMP_FO_NAME		"udo_fo.bmp"
#define	BMP_MW_NAME		"udo_mw.bmp"
#define	IMG_FC_NAME		"udo_fc.img"
#define	IMG_FO_NAME		"udo_fo.img"
#define	IMG_MW_NAME		"udo_mw.img"

#define	WIN_TITLE_NODE_NAME	"UDON0000"	/* vgl. chr.c: node2NrWinhelp() */
#define	WIN_UDO_NODE_NAME	"UDONFFFF"	/* vgl. chr.c: node2NrWinhelp() */


/*	############################################################
	# Hintergrundfarben
	############################################################	*/
#define	BC_BLACK	0
#define	BC_GRAY		1
#define	BC_SILVER	2
#define	BC_WHITE	3
#define	BC_MAROON	4
#define	BC_RED		5
#define	BC_PURPLE	6
#define	BC_FUCHSIA	7
#define	BC_GREEN	8
#define	BC_LIME		9
#define	BC_OLIVE	10
#define	BC_YELLOW	11
#define	BC_NAVY		12
#define	BC_BLUE		13
#define	BC_TEAL		14
#define	BC_AQUA		15
#define	BC_NONE		16



/*	############################################################
	# Sonderzeichen
	############################################################	*/
#define	META_C		'!'			/* Metazeichen					*/
#define	META_S		"!"

#define	QUOTE_C		'/'			/* Quotezeichen					*/
#define	QUOTE_S		"/"

#define	VERB_S		"+"			/* Default-Zeichen fuer \verb...*/
#define	VERB_C		'+'			/* Default-Zeichen fuer \verb...*/


/*	############################################################
	# Interne ESC-Sequenzen
	#
	# markiert werden Schriftstile, Referenzen, Platzhalter,
	# Trennzeichen, feste Leerzeichen
	#
	############################################################	*/

#define	C_STYLE_MAGIC		'\001'
#define	ESC_STYLE_MAGIC		"\033\001"

#define	C_REF_MAGIC			'\002'
#define	ESC_REF_MAGIC		"\033\002"

#define	C_PHOLD_MAGIC		'\003'
#define	ESC_PHOLD_MAGIC		"\033\003"

#define	C_SPECCMD_MAGIC		'\004'
#define	ESC_SPECCMD_MAGIC	"\033\004"

#define	C_COLOR_ON_MAGIC	'\005'
#define	ESC_COLOR_ON_MAGIC	"\033\005"

#define	C_COLOR_OFF_MAGIC	'\006'
#define	ESC_COLOR_OFF_MAGIC	"\033\006"

#define	TEMPO_S			"\033\007\001\033"		/* temporaere Zeichen	*/
#define	TEMPO_S2		"\033\007\002\033"		/* temporaere Zeichen	*/
#define	TEMPO_S_LEN		4
#define	TEMPO_S2_LEN	4

/* New in V6.5.5 [NHz] */
#define KPSPO_S		"\033\007\003\033"		/* Parenthis for Postscript */
#define KPSPO_S_LEN		4
#define KPSPC_S		"\033\007\004\033"
#define KPSPC_S_LEN		4
#define KPSEO_S		"\033\007\005\033"
#define KPSEO_S_LEN		4
#define KPSEC_S		"\033\007\006\033"
#define KPSEC_S_LEN		4

#define	NBSP_C			'\027'		/* internes festes Leerzeichen	*/
#define	NBSP_S			"\027"
#define	NBSP_S_LEN		1

#define	TILDE_C			'\030'		/* interne Tilde				*/
#define	TILDE_S			"\030"
#define	TILDE_S_LEN		1

#define	INDENT_C		'\031'		/* internes festes Leerzeichen	*/
#define	INDENT_S		"\031"		/* fuer Einrueckungen			*/
#define	INDENT_S_LEN	1

#define	DIVIS_C			'\032'		/* internes Trennzeichen		*/
#define	DIVIS_S			"\032"
#define	DIVIS_S_LEN		1


#define	ESC_C			'\033'		/* Escape-Zeichen = \e			*/
#define	ESC_S			"\033"


/*	############################################################
	# Umlaute
	############################################################	*/

#ifdef __TOS__
	#define	BETA_C		'\341'		/* IBM-SZ (Beta) */
	#define	BETA_S		"\341"
	#define	BETA_S_LEN	1
	#define	ALPHA_S		"\340"
	#define	ALPHA_S_LEN	1
	#define COPY_S		"\275"
	#define	COPY_S_LEN	1
#endif	/* __TOS__ */


#ifdef __MSDOS__
	#define	BETA_C		'\341'		/* IBM-SZ (Beta) */
	#define	BETA_S		"\341"
	#define	BETA_S_LEN	1
	#define	ALPHA_S		"\340"
	#define	ALPHA_S_LEN	1
	#define COPY_S		"\275"
	#define	COPY_S_LEN	1
#endif	/* __MSDOS__ */


#ifdef __HPUX_ROMAN8__
	#define	BETA_C		'\336'
	#define	BETA_S		"beta"
	#define	BETA_S_LEN	4
	#define	ALPHA_S		"alpha"
	#define	ALPHA_S_LEN	5
	#define	COPY_S		"(c)"
	#define	COPY_S_LEN	3
#endif	/* __HPUX_ROMAN8__ */


#ifdef __NEXTSTEP__
	#define	BETA_C		'\373'	/* kein Beta, daher sz nehmen */
	#define	BETA_S		"\373"
	#define	BETA_S_LEN	1
	#define	ALPHA_S		"alpha"
	#define	ALPHA_S_LEN	5
	#define COPY_S		"\240"
	#define	COPY_S_LEN	1
#endif	/* __MSDOS__ */


#if defined(__MACOS__) || defined(__MACOSX__) || defined(__BEOS__)
	#define	BETA_C		'\247'		/* kein Beta, daher sz nehmen */
	#define	BETA_S		"\247"
	#define	BETA_S_LEN	1
	#define	ALPHA_S		"alpha"		/* kein Alpha */
	#define	ALPHA_S_LEN	5
	#define	COPY_S		"\251"
	#define	COPY_S_LEN	1
#endif	/* __MACOS__ */


#if USE_LATIN1_CHARSET
	#define	BETA_C		'\337'
	#define	BETA_S		"beta"
	#define	BETA_S_LEN	4
	#define	ALPHA_S		"alpha"
	#define	ALPHA_S_LEN	5
	#define	COPY_S		"(c)"
	#define	COPY_S_LEN	3
#endif	/* USE_LATIN1_CHARSET */


/*	############################################################
	# constant.h
	############################################################	*/

#endif /* CONSTANT_H */
