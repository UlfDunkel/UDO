/*	############################################################
	# @(#) tp.c
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
	############################################################	*/

#ifndef ID_TP_C
#define ID_TP_C
const char *id_tp_c= "@(#) tp.c        11.02.1999";
#endif

#include "import.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "portab.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "chr.h"
#include "env.h"
#include "file.h"
#include "img.h"
#include "msg.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"

#include "export.h"
#include "tp.h"


/*	############################################################
	# lokale Variablen
	############################################################	*/

/*	############################################################
	# lokale Prototypen
	############################################################	*/
LOCAL BOOLEAN init_docinfo_data ( char *data, char **var, int allow_empty );
LOCAL void init_titdat ( void );
LOCAL void free_titdat ( char **var );

/* New in r6pl16 [NHz] */
/*	############################################################
	#
	# Main-Layout
	#
	############################################################	*/
/*	--------------------------------------------------------------
	set_mainlayout()
	Setzen von Informationen fuer das Layout (neue Version)
	Die Daten stehen in token[]. Ich habe die Funktion hier herein
	gepackt, da ich keine neue C-Datei eroeffnen wollte.
	Hier werden Vorgaben gemacht, wenn der Nutzer keine Angaben zum
	Layout macht.
	<-	TRUE:	OK
		sonst:	Fehler
	--------------------------------------------------------------	*/
GLOBAL BOOLEAN set_mainlayout ( void )
{
	/* Fixed Bug #0000040 in r6.2pl2 [NHz] */
	init_docinfo_data("A4PORTRAIT", &(laydat.paper), FALSE);

	init_docinfo_data("Times New Roman", &(laydat.propfontname), FALSE);
	laydat.propfontsize = 11;
	init_docinfo_data("Courier New", &(laydat.monofontname), FALSE);
	laydat.monofontsize = 11;
	init_docinfo_data("/UseNone", &(laydat.pagemode), FALSE);
	init_docinfo_data("/SinglePage", &(laydat.viewerpreferences), FALSE);
	init_docinfo_data("false", &(laydat.fitwindow), FALSE);
	init_docinfo_data("1", &(laydat.openpage), FALSE);
	init_docinfo_data("false", &(laydat.hidetoolbar), FALSE);
	init_docinfo_data("false", &(laydat.hidemenubar), FALSE);
	/* New in r6pl16 [NHz] */
	laydat.node1size = 0;
	laydat.node2size = 0;
	laydat.node3size = 0;
	laydat.node4size = 0;

	return TRUE;
}


/* New in r6pl15 [NHz] */
/*	############################################################
	#
	# Doc-Layout
	#
	############################################################	*/
/*	--------------------------------------------------------------
	set_doclayout()
	Setzen von Informationen fuer das Layout (neue Version)
	Die Daten stehen in token[]. Ich habe die Funktion hier herein
	gepackt, da ich keine neue C-Datei eroeffnen wollte.
	!doclayout [format] [foo]".
	<-	TRUE:	OK
		sonst:	Fehler
	--------------------------------------------------------------	*/
GLOBAL BOOLEAN set_doclayout ( void )
{
	char s[512], *cont_format, *cont_content, *data, format[512], content[512];
	char *page, page2[2];
	struct size_brackets contlen;

	tokcpy2(s);
	
	contlen= get_two_brackets_ptr(s, &cont_format, &cont_content, &data);
	
	if (contlen.format==0 || contlen.content==0 || cont_content==NULL || cont_format==NULL || data==NULL)
	{	error_syntax_error();
		return FALSE;
	}

	format[0]= EOS;	
	strncpy(format, cont_format, contlen.format);
	format[contlen.format]= EOS;
	del_whitespaces(format);

	content[0]= EOS;	
	strncpy(content, cont_content, contlen.content);
	content[contlen.content]= EOS;
	del_whitespaces(content);

	if (strcmp(content, "paper")==0)
	{	if ( str_for_desttype(format) )
		{	/* Layout festlegen */
			init_docinfo_data(data, &(laydat.paper), FALSE);
		}
		return TRUE;
	}
	
	if (strcmp(content, "propfontname")==0)
	{	if ( str_for_desttype(format) )
		{	/* Set proportional font */
			init_docinfo_data(data, &(laydat.propfontname), FALSE);
		}
		return TRUE;
	}
	
	if (strcmp(content, "propfontsize")==0)
	{	if ( str_for_desttype(format) )
		{	/* Set size of proportional font */
			laydat.propfontsize = atoi(data);
		}
		return TRUE;
	}

	if (strcmp(content, "monofontname")==0)
	{	if ( str_for_desttype(format) )
		{	/* Set aquidistant font */
			init_docinfo_data(data, &(laydat.monofontname), FALSE);
		}
		return TRUE;
	}
	
	if (strcmp(content, "monofontsize")==0)
	{	if ( str_for_desttype(format) )
		{	/* Set size of the aquidistant font */
			laydat.monofontsize = atoi(data);
		}
		return TRUE;
	}
	
	/* New in r6pl16 [NHz] */
	if (strcmp(content, "node1size")==0)
	{	if ( str_for_desttype(format) )
		{	/* Set size of node */
			laydat.node1size = atoi(data);
		}
		return TRUE;
	}
	
	if (strcmp(content, "node2size")==0)
	{	if ( str_for_desttype(format) )
		{	/* Set size of subnode */
			laydat.node2size	= atoi(data);
		}
		return TRUE;
	}
	
	if (strcmp(content, "node3size")==0)
	{	if ( str_for_desttype(format) )
		{	/* Set size of subsubnode */
			laydat.node3size	= atoi(data);
		}
		return TRUE;
	}
	
	if (strcmp(content, "node4size")==0)
	{	if ( str_for_desttype(format) )
		{	/* Set size of subsubsubnode */
			laydat.node4size	= atoi(data);
		}
		return TRUE;
	}

	/* Specialities for Postscript */
	if (strcmp(content, "openMode")==0)
	{	if (strstr(data, "Outlines"))
			init_docinfo_data("/UseOutlines", &(laydat.pagemode), FALSE);
		else if (strstr(data, "Thumbs"))
			init_docinfo_data("/UseThumbs", &(laydat.pagemode), FALSE);
		else if (strstr(data, "Fullscreen"))
			init_docinfo_data("/FullScreen", &(laydat.pagemode), FALSE);
		else
			init_docinfo_data("/UseNone", &(laydat.pagemode), FALSE);

		page = strstr(data, "Page=");
		if (page != NULL)
		{
			page2[0] = *(page+5);
			page2[1] = EOS;
			init_docinfo_data(page2, &(laydat.openpage), FALSE);
		}
		else
			init_docinfo_data("1", &(laydat.openpage), FALSE);

		if (strstr(data, "HideToolbar"))
			init_docinfo_data("true", &(laydat.hidetoolbar), FALSE);
		else
			init_docinfo_data("false", &(laydat.hidetoolbar), FALSE);

		if (strstr(data, "HideMenubar"))
			init_docinfo_data("true", &(laydat.hidemenubar), FALSE);
		else
			init_docinfo_data("false", &(laydat.hidemenubar), FALSE);

		if (strstr(data, "OneColumn"))
			init_docinfo_data("/OneColumn", &(laydat.viewerpreferences), FALSE);
		else if (strstr(data, "ColumnLeft"))
			init_docinfo_data("/TwoColumnLeft", &(laydat.viewerpreferences), FALSE);
		else if (strstr(data, "ColumnRight"))
			init_docinfo_data("/TwoColumnRight", &(laydat.viewerpreferences), FALSE);
		else
			init_docinfo_data("/SinglePage", &(laydat.viewerpreferences), FALSE);
		
		if (strstr(data, "Title"))
			init_docinfo_data("true", &(laydat.fitwindow), FALSE);
		else
			init_docinfo_data("false", &(laydat.fitwindow), FALSE);
		return TRUE;
	}

	return FALSE;

}	/* set_doclayout */


/*	############################################################
	#
	# Titelseite
	#
	############################################################	*/
/*	--------------------------------------------------------------
	init_docinfo_data()
	Anpassung der Daten fuer die Titelseite samt Anforderung des
	benoetigten Speichers
	->	data:	Zeiger auf den Inhalt
		var:	Zeiger auf die Variable
	--------------------------------------------------------------	*/
LOCAL BOOLEAN init_docinfo_data ( char *data, char **var, int allow_empty )
{
	/* [voja][R6PL17] I needed to do the buffer creation first in this function,
	   elsewise you can't use memmove with compilers like GCC 3.x and
	   MS VS .net. An segmentation fault will occur (Bug #0000016).
	   I guess this is because of better memory protection techniques:
	   The *data coming in can be an constant(!) value. I think these compilers
	   write constant variable allocations to a protected memory region.
	   Writing to this region will crash...
	*/
	char *buffer;
	
	buffer= (char *) malloc (strlen(data)*sizeof(char)+1);

	if (buffer) /* Check if the buffer could be allocated */
	{
		/* We copy now first the data to the buffer, this prevents
		   bug #0000016 with modern compilers */
		strcpy(buffer, data);
		del_whitespaces(buffer);		/* Parameter was data */
		c_divis(buffer);				/* Parameter was data */
		c_vars(buffer);					/* Parameter was data */
		c_tilde(buffer);				/* Parameter was data */
		c_styles(buffer);				/* Parameter was data */
		del_internal_styles(buffer);	/* Parameter was data */
		replace_udo_tilde(buffer);		/* Parameter was data */
		replace_udo_nbsp(buffer);		/* Parameter was data */
		replace_udo_quotes(buffer);		/* Parameter was data */
		delete_all_divis(buffer);		/* Parameter was data */

		if (data[0]==EOS && !allow_empty)
		{	error_empty_docinfo();
			return FALSE;
		}

		*var=buffer;
		
		return TRUE;
	}

	/* An error occured when allocating the buffer */
	error_malloc_failed();
	bFatalErrorDetected= TRUE;
	return FALSE;

}	/* init_docinfo_data */



/*	--------------------------------------------------------------
	set_docinfo()
	Setzen von Informationen fuer die Titelseite (neue Version)
	Die Daten stehen in token[]. Frueher setzte man bspw. den
	Programmnamen mit "!program UDO", nun mit
	"!docinfo [program] UDO".
	<-	TRUE:	OK
		sonst:	Fehler
	--------------------------------------------------------------	*/
GLOBAL BOOLEAN set_docinfo ( void )
{
	char s[512], *cont, *data, inhalt[512], *buffer;
	char sDriv[512], sPath[512], sFile[512], sSuff[512];
	size_t contlen;

	tokcpy2(s);
	
	contlen= get_brackets_ptr(s, &cont, &data);
	
	if (contlen==0 || cont==NULL || data==NULL)
	{	error_syntax_error();
		return FALSE;
	}

	inhalt[0]= EOS;	
	strncpy(inhalt, cont, contlen);
	inhalt[contlen]= EOS;
	del_whitespaces(inhalt);

	if (strcmp(inhalt, "authorimage")==0)
	{	del_whitespaces(data);
		if (data[0]==EOS)
		{	error_empty_docinfo();
		}
		else
		{	path_adjust_separator(data);
			buffer= (char *) malloc ( strlen(data)*sizeof(char)+1 );
			if (buffer)
			{	strcpy(buffer, data);
				titdat.authorimage= buffer;
				if (desttype==TOHTM || desttype==TOMHH)
				{	replace_char(titdat.authorimage, "\\", "/");	/*r6pl4*/
					/* r6pl9: Ausmasse nicht ermitteln -> da */
					/* ueber c_gif_output() ausgegeben wird  */
				}
			}
			else
			{	error_malloc_failed();
				bFatalErrorDetected= TRUE;
			}
		}
		return TRUE;
	}

	if (strcmp(inhalt, "authoricon")==0)	/*r6pl6*/
	{	del_whitespaces(data);
		if (data[0]==EOS)
		{	error_empty_docinfo();
		}
		else
		{	/* r6pl12: Endung abschneiden und mit !html_img_suffix ersetzen */
			fsplit(data, sDriv, sPath, sFile, sSuff);
			sprintf(data, "%s%s%s", sPath, sFile, sDocImgSuffix);
			path_adjust_separator(data);
			buffer= (char *) malloc ( strlen(data)*sizeof(char)+1 );
			if (buffer)
			{	strcpy(buffer, data);
				titdat.authoricon= buffer;
				if (desttype==TOHTM || desttype==TOMHH)
				{	replace_char(titdat.authoricon, "\\", "/");
					if (my_stricmp(sDocImgSuffix, ".gif")==0)
					{	/* r6pl9: Ausmasse ermitteln */
						strinsert(data, old_outfile.path);
						strinsert(data, old_outfile.driv);
						/* strcat(data, ".gif"); */
						path_adjust_separator(data);
						if (!get_gif_size(data, &titdat.authoriconWidth, &titdat.authoriconHeight))
						{	error_read_gif(data);
						}
					}
				}
			}
			else
			{	error_malloc_failed();
				bFatalErrorDetected= TRUE;
			}
		}
		return TRUE;
	}

	if (strcmp(inhalt, "authoricon_active")==0)	/*r6pl13*/
	{	del_whitespaces(data);
		if (data[0]==EOS)
		{	error_empty_docinfo();
		}
		else
		{	/* r6pl12: Endung abschneiden und mit !html_img_suffix ersetzen */
			fsplit(data, sDriv, sPath, sFile, sSuff);
			sprintf(data, "%s%s%s", sPath, sFile, sDocImgSuffix);
			path_adjust_separator(data);
			buffer= (char *) malloc ( strlen(data)*sizeof(char)+1 );
			if (buffer)
			{	strcpy(buffer, data);
				titdat.authoricon_active= buffer;
				if (desttype==TOHTM || desttype==TOMHH)
				{	replace_char(titdat.authoricon_active, "\\", "/");
					if (my_stricmp(sDocImgSuffix, ".gif")==0)
					{	/* r6pl9: Ausmasse ermitteln */
						strinsert(data, old_outfile.path);
						strinsert(data, old_outfile.driv);
						/* strcat(data, ".gif"); */
						path_adjust_separator(data);
						if (!get_gif_size(data, &titdat.authoriconActiveWidth, &titdat.authoriconActiveHeight))
						{	error_read_gif(data);
						}
					}
				}
			}
			else
			{	error_malloc_failed();
				bFatalErrorDetected= TRUE;
			}
		}
		return TRUE;
	}

	if (strcmp(inhalt, "programimage")==0)
	{	del_whitespaces(data);
		if (data[0]==EOS)
		{	error_empty_docinfo();
		}
		else
		{	path_adjust_separator(data);
			buffer= (char *) malloc ( strlen(data)*sizeof(char)+1 );
			if (buffer)
			{	strcpy(buffer, data);
				titdat.programimage= buffer;
				if (desttype==TOHTM || desttype==TOMHH)
				{	replace_char(titdat.programimage, "\\", "/");	/*r6pl4*/
					/* r6pl9: Ausmasse nicht ermitteln -> da */
					/* ueber c_gif_output() ausgegeben wird  */
				}
			}
			else
			{	error_malloc_failed();
				bFatalErrorDetected= TRUE;
			}
		}
		return TRUE;
	}

	if (strcmp(inhalt, "title")==0)
	{	init_docinfo_data(data, &(titdat.title), FALSE);
		return TRUE;
	}

	if (strcmp(inhalt, "program")==0)
	{	init_docinfo_data(data, &(titdat.program), FALSE);
		return TRUE;
	}

	if (strcmp(inhalt, "version")==0)
	{	init_docinfo_data(data, &(titdat.version), FALSE);
		return TRUE;
	}

	if (strcmp(inhalt, "date")==0)
	{	init_docinfo_data(data, &(titdat.date), FALSE);
		return TRUE;
	}

	if (strcmp(inhalt, "author")==0)
	{	init_docinfo_data(data, &(titdat.author), FALSE);
		return TRUE;
	}

	if (strcmp(inhalt, "address")==0)
	{	if (address_counter<MAXADDRESS)
		{	address_counter++;
			init_docinfo_data(data, &(titdat.address[address_counter]), FALSE);
		}
		return TRUE;
	}

	/* New in r6pl15 [NHz] */
	if (strcmp(inhalt, "keywords")==0)
	{	init_docinfo_data(data, &(titdat.keywords), FALSE);
		return TRUE;
	}

	/* New in r6pl15 [NHz] */
	if (strcmp(inhalt, "description")==0)
	{	init_docinfo_data(data, &(titdat.description), FALSE);
		return TRUE;
	}

	/* Spezialitaeten fuer ST-Guide */
	if (strcmp(inhalt, "stgdatabase")==0)	/*r6pl4*/
	{	init_docinfo_data(data, &(titdat.stg_database), TRUE);
		return TRUE;
	}

	/* Spezialitaeten fuer DRC */
	if (strcmp(inhalt, "drcstatusline")==0)	/*r6pl4*/
	{	init_docinfo_data(data, &(titdat.drc_statusline), FALSE);
		return TRUE;
	}

	/* Spezialitaeten fuer HTML */
	if (strcmp(inhalt, "htmltitle")==0)
	{	init_docinfo_data(data, &(titdat.htmltitle), FALSE);
		return TRUE;
	}

	if (strcmp(inhalt, "webmastername")==0)
	{	init_docinfo_data(data, &(titdat.webmastername), FALSE);
		return TRUE;
	}

	if (strcmp(inhalt, "webmasteremail")==0)
	{	init_docinfo_data(data, &(titdat.webmasteremail), FALSE);
		return TRUE;
	}

	if (strcmp(inhalt, "webmastermailurl")==0)
	{	init_docinfo_data(data, &(titdat.webmastermailurl), FALSE);
		return TRUE;
	}

	if (strcmp(inhalt, "webmasterurl")==0)
	{	del_whitespaces(data);	/* nicht init_...!!! */
		convert_tilde(data);
		if (data[0]==EOS)
		{	error_empty_docinfo();
		}
		else
		{	buffer= (char *) malloc ( strlen(data)*sizeof(char)+1 );
			if (buffer)
			{	strcpy(buffer, data);
				titdat.webmasterurl= buffer;
			}
			else
			{	error_malloc_failed();
				bFatalErrorDetected= TRUE;
			}
		}
		return TRUE;
	}

	error_unknown_docinfo(inhalt);
	
	return FALSE;

}	/* set_docinfo */



GLOBAL void c_maketitle ( void )
{
	int i;
	char n[512], s1[128], s2[128];
	BOOLEAN	has_author,
			has_program,
			has_title,
			has_version,
			has_date,
			has_authorimage,
			has_programimage,
			has_address;

	if (called_maketitle)
	{	error_called_twice("!maketitle");	/*r6pl2*/
		return;
	}

	called_maketitle= TRUE;

	has_author= 		(titdat.author!=NULL);
	has_address= 		(address_counter>0);
	has_program= 		(titdat.program!=NULL);
	has_title= 			(titdat.title!=NULL);
	has_version= 		(titdat.version!=NULL);
	has_date= 			(titdat.date!=NULL);
	has_authorimage=	(titdat.authorimage!=NULL);
	has_programimage= 	(titdat.programimage!=NULL);

	if ( !(	has_author ||
			has_program ||
			has_title ||
			has_version ||
			has_date ||
			has_authorimage ||
			has_programimage ||
			has_address)
		)
	{
		error_missing_title_data();	/* r6pl2 */
		return;
	}


	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
			outln("\\begin{titlepage}");
			outln("\\begin{center}");
			if (has_title)
			{	voutlnf("{\\Large %s} \\\\", titdat.title);
				outln("\\bigskip");
			}
			
			if ( has_programimage )
			{	switch (iTexVersion)
				{	case TEX_LINDNER:
					case TEX_STRUNK:
						c_begin_center();
						c_img_output(titdat.programimage, "", FALSE);
						c_end_center();
						break;
					case TEX_EMTEX:
						c_begin_center();
						c_msp_output(titdat.programimage, "", FALSE);
						c_end_center();
						break;
					case TEX_TETEX:
						c_begin_center();
						c_eps_output(titdat.programimage, "", ".eps", FALSE);
						c_end_center();
						break;
				}
			}
			else
			{	if (has_program)
				{	voutlnf("{\\Huge %s} \\\\", titdat.program);
					outln("\\bigskip");
				}
			}
			
			if (has_version)
			{	voutlnf("{\\large %s} \\\\", titdat.version);
				outln("\\bigskip");
			}
			if (has_date)
			{	voutlnf("{\\large %s} \\\\", titdat.date);
			}

			if ( has_author || has_authorimage )
			{	voutlnf("\\vfill\n%s\\\\\n\\medskip", lang.by);
			}

			if ( has_authorimage )
			{	switch (iTexVersion)
				{	case TEX_LINDNER:
					case TEX_STRUNK:
						c_begin_center();
						c_img_output(titdat.authorimage, "", FALSE);
						c_end_center();
						break;
					case TEX_EMTEX:
						c_begin_center();
						c_msp_output(titdat.authorimage, "", FALSE);
						c_end_center();
						break;
					case TEX_TETEX:
						c_begin_center();
						c_eps_output(titdat.authorimage, "", ".eps", FALSE);
						c_end_center();
						break;
				}
			}

			if (has_author)
			{	voutlnf("%s \\\\", titdat.author);
			}

			if (has_address)
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	voutlnf("%s \\\\", titdat.address[i]);
					}
				}
			}
			
			outln("\\end{center}");
			outln("\\end{titlepage}");
			break;
		
		case TOLYX:
			outln("\\layout Title");
			outln("\\fill_top");
			outln("");
			if (has_title)
			{	voutlnf("\\layout Section*\n\\align center\n%s\n\\newline\n", titdat.title);
			}
			if (has_program)
			{	voutlnf("\\size giant %s\n", titdat.program);
			}
			if (has_version)
			{	voutlnf("\\layout Subsection*\n\\align center\n%s\n", titdat.version);
			}
			if (has_date)
			{	voutlnf("\\layout Subsection*\n\\align center\n%s\n", titdat.date);
			}
			if (has_author)
			{	voutlnf("\\fill_bottom\n\\layout Subsubsection*\n\\align center\n\n%s\n", lang.by);
				voutlnf("\\layout Subsection*\n\\align center\n\n%s\n", titdat.author);
			}
			if (has_address)
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	voutlnf("\\layout Subsection*\n\\align center\n%s\n", titdat.address[i]);
					}
				}
			}
			break;
		
		case TOINF:
			outln("@titlepage");
			outln("@sp 1");
			if (has_title)
			{	voutlnf("@center @titlefont{%s}", titdat.title);
				outln("@sp 1");
			}
			if (has_program)
			{	voutlnf("@center @titlefont{%s}", titdat.program);
				outln("@sp 1");
			}
			if (has_version)
			{	voutlnf("@center %s", titdat.version);
				outln("@sp 1");
			}
			if (has_date)
			{	voutlnf("@center %s", titdat.date);
				outln("@sp 1");
			}
			if (has_author)
			{	outln("@sp 10");
				voutlnf("@center %s", lang.by);
				outln("@sp 1");
				voutlnf("@center %s", titdat.author);
			}
			if (has_address)
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	voutlnf("@center %s", titdat.address[i]);
					}
				}
			}
			outln("@end titlepage");
			break;

		case TOSTG:
			outln("");
			voutlnf("@node \"%s\"", lang.title);
			stg_headline("", lang.title);
			outln("");

			outln("@autorefoff");
			if (has_title)
			{	outlncenter(titdat.title);
				outln("");
			}

			if (has_programimage)
			{	strcpy(n, titdat.programimage);
				change_sep_suffix(n, ".img");	/* PL6 */
				c_begin_center();
				c_img_output(n, "", FALSE);
				c_end_center();
			}
			else
			{	if (has_program)
				{	outlncenter(titdat.program);
					outln("");
				}
			}

			if (has_version)	outlncenter(titdat.version);
			if (has_date)		outlncenter(titdat.date);

			if ( has_author || has_authorimage )
			{	outln("");
				outlncenter(lang.by);
			}

			if ( has_authorimage )
			{	strcpy(n, titdat.authorimage);
				change_sep_suffix(n, ".img");	/* PL6 */
				c_begin_center();
				c_img_output(n, "", FALSE);
				c_end_center();
			}

			if ( has_author )
			{	outln("");
				outlncenter(titdat.author);
			}

			if ( has_address )
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	outlncenter(titdat.address[i]);
					}
				}
			}
			outln("@autorefon");
			outln("");
			
			if (uses_tableofcontents)
			{	outln("");
				outlncenter(lang.contents);
			}
			outln("@endnode");
			outln("");
			break;

		case TOAMG:
			outln("");
			voutlnf("@node \"%s\" \"%s\"", lang.title, titleprogram);
			stg_headline("", lang.title);
			outln("");

			if (has_title)
			{	outlncenter(titdat.title);
				outln("");
			}

			if (has_program)
			{	outlncenter(titdat.program);
				outln("");
			}

			if (has_version)	outlncenter(titdat.version);
			if (has_date)		outlncenter(titdat.date);

			if ( has_author )
			{	outln("");
				outlncenter(lang.by);
				outln("");
				outlncenter(titdat.author);
			}

			if ( has_address )
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	outlncenter(titdat.address[i]);
					}
				}
			}
			outln("");
			
			if (uses_tableofcontents)
			{	outln("");
				outlncenter(lang.contents);
			}
			outln("@endnode");
			outln("");
			break;

		case TOPCH:
			/* Titelseite erfolgt bei PC-HELP bei tableofcontents... */
			break;

		case TODRC:
			n[0]= EOS;
			if (has_title)
			{	strcat(n, titdat.title);
				strcat(n, " ");
			}
			if (has_program)
			{	strcat(n, titdat.program);
			}
			del_whitespaces(n);
			if (n[0]==EOS)
			{	strcpy(n, lang.unknown);
			}
			voutlnf("%%%% 1, %s", n);

			/*r6pl5: Eigene Titelseitenroutine, damit die Zentrierung klappt */

			if ( has_title )
			{	outlncenterfill(titdat.title);
				outln("");
			}
			if ( has_program )
			{	outlncenterfill(titdat.program);
				outln("");
			}
			if ( has_version )	outlncenterfill(titdat.version);
			if ( has_date )		outlncenterfill(titdat.date);

			if ( has_author )
			{	outln("");
				outlncenterfill(lang.by);
				outln("");
				outlncenterfill(titdat.author);
			}

			if ( has_address )
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	outlncenterfill(titdat.address[i]);
					}
				}
				outln("");
			}
			outln("");
			break;
		
		case TOASC:
		case TOMAN:
			if ( has_title )
			{	outlncenter(titdat.title);
				outln("");
			}
			if ( has_program )
			{	outlncenter(titdat.program);
				outln("");
			}
			if ( has_version )	outlncenter(titdat.version);
			if ( has_date )		outlncenter(titdat.date);

			if ( has_author )
			{	outln("");
				outlncenter(lang.by);
				outln("");
				outlncenter(titdat.author);
			}

			if ( has_address )
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	outlncenter(titdat.address[i]);
					}
				}
				outln("");
			}
			outln("");
			outln("");
			if (desttype==TOMAN)
			{	c_newpage();
			}
			break;

		case TOSRC:
		case TOSRP:
			memset(n, '#', 62);	n[62]= EOS;
			voutlnf("%s  %s", sSrcRemOn, n);
			if ( has_title )
			{	strcpy(s1, titdat.title);
				stringcenter(s1, 60);
				voutlnf("    # %s", s1);
				outln("    #");
			}
			if ( has_program )
			{	strcpy(s1, titdat.program);
				stringcenter(s1, 60);
				voutlnf("    # %s", s1);
				outln("    #");
			}
			if ( has_version )
			{	strcpy(s1, titdat.version);
				stringcenter(s1, 60);
				voutlnf("    # %s", s1);
			}
			if ( has_date )
			{	strcpy(s1, titdat.date);
				stringcenter(s1, 60);
				voutlnf("    # %s", s1);
			}
			if ( has_author )
			{	outln("    #");
				strcpy(s1, "Copyright (C) by");
				stringcenter(s1, 60);
				voutlnf("    # %s", s1);
				outln("    #");
				strcpy(s1, titdat.author);
				stringcenter(s1, 60);
				voutlnf("    # %s", s1);
			}

			if ( has_address )
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	strcpy(s1, titdat.address[i]);
						stringcenter(s1, 60);
						voutlnf("    # %s", s1);
					}
				}
				outln("    #");
			}
			voutlnf("    %s %s", n, sSrcRemOff);
			break;

		case TORTF:
			outln(rtf_par);
			outln("\\qc ");
			if ( has_title )
			{	voutlnf("{\\fs%d %s}%s%s", iDocPropfontSize + 14, titdat.title, rtf_par, rtf_par);
			}
			if ( has_program )
			{	voutlnf("{\\fs%d %s}%s%s", iDocPropfontSize + 38, titdat.program, rtf_par, rtf_par);
			}
			if ( has_version )
			{	voutlnf("{\\fs%d %s}%s", iDocPropfontSize + 6, titdat.version, rtf_par);
			}
			if ( has_date )
			{	voutlnf("{\\fs%d %s}%s", iDocPropfontSize + 6, titdat.date, rtf_par);
			}
			if ( has_author || has_address )
			{	for (i=0; i<(25-address_counter); i++) out(rtf_par) ;
				outln(rtf_par);
			}
			if (has_author)
			{	voutlnf("%s%s%s", lang.by, rtf_par, rtf_par);
				voutlnf("%s%s", titdat.author, rtf_par);
			}
			if ( has_address )
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	voutlnf("%s%s", titdat.address[i], rtf_par);
					}
				}
			}
			outln("\\ql");
			outln("\\page");
			break;

		case TOWIN:
		case TOWH4:
			check_endnode();
			
			outln("");		
			outln("{");	
			voutlnf("#{\\footnote # %s}", WIN_TITLE_NODE_NAME);
			voutlnf("${\\footnote $ %s}", lang.title);
			voutlnf("K{\\footnote K %s}", lang.title);
			if (!no_buttons)	/* r6pl8 */
			{	outln(win_browse);
				outln("!{\\footnote ! DisableButton(\"BTN_UP\") }");
			}

			if ( has_title )
			{	voutlnf("\\qc{\\fs%d %s}\\par\\pard", iDocPropfontSize + 6, titdat.title);
			}

			if ( has_programimage )
			{	outln("\\par");
				c_begin_center();
				c_bmp_output(titdat.programimage, "", FALSE);
				c_end_center();
			}
			else
			{	if ( has_program )
				{	voutlnf("\\qc{\\fs%d %s}\\par\\pard", iDocPropfontSize + 26, titdat.program);
				}
			}
			
			if ( has_version )	voutlnf("\\qc{%s}\\par\\pard", titdat.version);
			if ( has_date )		voutlnf("\\qc{%s}\\par\\pard", titdat.date);

			if ( has_author || has_authorimage)
			{	voutlnf("\\par\\qc{%s}\\par\\pard", lang.by);
			}

			if ( has_authorimage )
			{	outln("\\par");
				c_begin_center();
				c_bmp_output(titdat.authorimage, "", FALSE);
				c_end_center();
			}

			if ( has_author )
			{	voutlnf("\\qc{%s}\\par\\pard", titdat.author);
			}

			if ( has_address )
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	voutlnf("\\qc{%s}\\par\\pard", titdat.address[i]);
					}
				}
			}

			outln("\\par\\par");
			if (uses_tableofcontents)
			{	node2NrWinhelp(n, 0);
				voutlnf("\\qc{{\\uldb %s}{\\v %s}}\\par\\pard", lang.contents, n);
			}
			outln("}\\page");
			break;

		case TOAQV:
			check_endnode();
			
			outln("");		
			outln("{");	
			voutlnf("#{\\footnote # %s}", WIN_TITLE_NODE_NAME);
			voutlnf("${\\footnote $ %s}", lang.title);
			voutlnf("K{\\footnote K %s}", lang.title);

			if (!no_buttons)	/* r6pl8 */
			{	outln(win_browse);
				outln("!{\\footnote ! DisableButton(\"BTN_UP\") }");
			}

			if ( has_title )
			{	voutlnf("\\qc %s\\par\\pard\\par", titdat.title);
			}

			if ( has_programimage )
			{	outln("\\par");
				c_begin_center();
				c_bmp_output(titdat.programimage, "", FALSE);
				c_end_center();
			}
			else
			{	if ( has_program )
				{	voutlnf("\\qc\\fs%d %s\\par\\pard\\plain", iDocPropfontSize + 26, titdat.program);
				}
			}

			if ( has_version )	voutlnf("\\qc %s\\par\\pard", titdat.version);
			if ( has_date )		voutlnf("\\qc %s\\par\\pard", titdat.date);

			if ( has_author || has_authorimage )
			{	voutlnf("\\par\\qc %s\\par\\pard", lang.by);
			}

			if ( has_authorimage )
			{	outln("\\par");
				c_begin_center();
				c_bmp_output(titdat.authorimage, "", FALSE);
				c_end_center();
			}

			if ( has_author )
			{	voutlnf("\\qc %s\\par\\pard", titdat.author);
			}

			if ( has_address )
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	voutlnf("\\qc %s\\par\\pard", titdat.address[i]);
					}
				}
			}

			outln("\\par\\par");
			if (uses_tableofcontents)
			{	voutlnf("\\qc {\\uldb %s}{\\v %s}\\par\\pard", lang.contents, lang.contents);
			}
			outln("}\\page");
			break;

		case TOHTM:
		case TOMHH:
			if ( has_title )
			{	voutlnf("<h2 align=\"center\">%s</h2>", titdat.title);
			}
			
			if ( has_programimage )
			{	c_begin_center();
				c_gif_output(titdat.programimage, "", sDocImgSuffix, 0);
				c_end_center();
			}
			else
			{	if ( has_program )
				{	voutlnf("<h1 align=\"center\">%s</h1>", titdat.program);
				}
			}

			if (has_version || has_date || has_author || has_address)
			{	outln("<p align=\"center\">");
			}

			if ( has_version )
			{	voutlnf("%s<br>", titdat.version);
			}
			if ( has_date )
			{	voutlnf("%s<br>", titdat.date);
			}
			if ( has_author || has_authorimage )
			{	voutlnf("<br>%s<br>", lang.by);
			}
			if ( has_authorimage )
			{	c_begin_center();
				c_gif_output(titdat.authorimage, "", sDocImgSuffix, 0);
				c_end_center();
				if (has_author || has_address)
				{	outln("<p align=\"center\">");
				}
			}
			if ( has_author )
			{	voutlnf("%s<br>", titdat.author);
			}
			
			if ( has_address )
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	voutlnf("%s<br>", titdat.address[i]);
					}
				}
			}

			if (has_version || has_date || has_author || has_address)
			{	outln("<p>");
			}

			if (uses_tableofcontents)
			{	outln(HTML_HR);
			}

			break;

		case TOTVH:
			outln("");
			voutlnf(".topic %s=0", lang.title);
			outln("");
			
			if ( has_title )
			{	outlncenter(titdat.title);
				outln("");
			}

			if ( has_program )
			{	outlncenter(titdat.program);
				outln("");
			}

			if ( has_version )	outlncenter(titdat.version);
			if ( has_date )		outlncenter(titdat.date);

			if ( has_author )
			{	outln("");
				outlncenter(lang.by);
				outln("");
				outlncenter(titdat.author);
			}

			if (address_counter>0)
			{	for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	outlncenter(titdat.address[i]);
					}
				}
			}

			outln("");
			outln("");

			if (uses_tableofcontents)
			{	sprintf(s1, "%s", lang.contents);	/* PL10: Leerzeichen davor */
				sprintf(s2, "{%s:%s}", lang.contents, lang.contents);
				strcpy(n, lang.contents);
				strcenter(n, zDocParwidth);
				replace_once(n, s1, s2);
				outln(n);
			}

			outln("");
			break;
		
		/* New in r6pl15 [NHz] */
		/* Title-Page for Postscript */
		case TOKPS:
			outln("/acty acty 50 sub def");
			outln("newline");
			if ( has_title )
			{	outln("14 changeFontSize");
				voutlnf("(%s) Center setAlign", titdat.title);
			}
			if ( has_program )
			{	outln("22 changeFontSize");
				outln("newline");
				voutlnf("(%s) Center setAlign", titdat.program);
			}
			if ( has_version )
			{	outln("14 changeFontSize");
				outln("newline");
				voutlnf("(%s) Center setAlign", titdat.version);
			}
			if ( has_date )
			{	outln("newline");
				voutlnf("(%s) Center setAlign", titdat.date);
				outln("11 changeFontSize");
			}

			if ( has_author )
			{	outln("currentpoint exch pop lowermargin 125 add lt");
				outln("{");
				outln("  /acty lowermargin 125 add def");
				outln("}");
				outln("{");
				outln("  /acty lowermargin 200 add def");
				outln("} ifelse");
				outln("newline");
				voutlnf("(%s) Center setAlign newline", lang.by);
				voutlnf("(%s) Center setAlign", titdat.author);
			}

			if ( has_address )
			{	outln("newline");
				for (i=1; i<=address_counter; i++)
				{	if (titdat.address[i]!=NULL)
					{	voutlnf("(%s) Center setAlign newline", titdat.address[i]);
					}
				}
				outln("newline");
			}
			c_newpage();
			break;

	}
	
}	/*c_maketitle*/


GLOBAL void pch_titlepage ( void )
{
	int i;
	
	if ( titdat.title!=NULL )
	{	outlncenter(titdat.title);
		outln("");
	}

	if ( titdat.program!=NULL )
	{	outlncenter(titdat.program);
		outln("");
	}

	if ( titdat.version!=NULL )
	{	outlncenter(titdat.version);
	}

	if ( titdat.date!=NULL )
	{	outlncenter(titdat.date);
	}

	if ( titdat.author!=NULL )
	{	outln("");
		outlncenter(lang.by);
		outln("");
		outlncenter(titdat.author);
	}

	if (address_counter>0)
	{	for (i=1; i<=address_counter; i++)
		{	if (titdat.address[i]!=NULL)
			{	outlncenter(titdat.address[i]);
			}
		}
	}

	outln("");
	
}	/* pch_titlepage */



/*	############################################################
	# Modulinit
	############################################################	*/
LOCAL void init_titdat ( void )
{
	int i;
	
	titdat.title= NULL;
	titdat.program= NULL;
	titdat.date= NULL;
	titdat.version= NULL;
	titdat.author= NULL;

	for (i=0; i<MAXADDRESS; i++)
	{	titdat.address[i]= NULL;
	}
	
	titdat.keywords= NULL; /* New in r6pl15 [NHz] */
	titdat.description= NULL; /* New in r6pl15 [NHz] */
	titdat.htmltitle= NULL;
	titdat.webmastername= NULL;
	titdat.webmasteremail= NULL;
	titdat.webmastermailurl= NULL;
	titdat.webmasterurl= NULL;
	titdat.programimage= NULL;
	titdat.authorimage= NULL;
	titdat.authoricon= NULL;
	titdat.authoricon_active= NULL;
	titdat.authoriconWidth= 0;
	titdat.authoriconHeight= 0;
	titdat.authoriconActiveWidth= 0;
	titdat.authoriconActiveHeight= 0;

	titdat.drc_statusline= NULL;
	titdat.stg_database= NULL;
}


GLOBAL void init_module_tp ( void )
{
	uses_maketitle=		FALSE;
	called_maketitle=	FALSE;
	address_counter=	0;

	titleprogram[0]=	EOS;
	
	init_titdat();
}


GLOBAL void init_module_tp_pass2 ( void )
{
	titleprogram[0]= EOS;

	if (titdat.title!=NULL)
	{	strcat(titleprogram, titdat.title);
		strcat(titleprogram, " ");
	}

	if (titdat.program!=NULL)
	{	strcat(titleprogram, titdat.program);
	}
	
	del_whitespaces(titleprogram);
}


LOCAL void free_titdat ( char **var )
{
	if (*var!=NULL)
	{	free(*var);
		*var= NULL;
	}
}


GLOBAL void exit_module_tp ( void )
{
	int i;
	
	free_titdat(&(titdat.title));
	free_titdat(&(titdat.program));
	free_titdat(&(titdat.date));
	free_titdat(&(titdat.version));
	free_titdat(&(titdat.author));	

	for (i=address_counter; i>=1; i--)
	{	free_titdat(&(titdat.address[i]));
	}
	
	free_titdat(&(titdat.keywords)); /* New in r6pl15 [NHz] */
	free_titdat(&(titdat.description)); /* New in r6pl15 [NHz] */
	free_titdat(&(titdat.htmltitle));
	free_titdat(&(titdat.webmastername));
	free_titdat(&(titdat.webmasteremail));
	free_titdat(&(titdat.webmastermailurl));
	free_titdat(&(titdat.webmasterurl));
	free_titdat(&(titdat.programimage));
	free_titdat(&(titdat.authorimage));
	free_titdat(&(titdat.authoricon));
	free_titdat(&(titdat.authoricon_active));

	free_titdat(&(titdat.drc_statusline));	
	free_titdat(&(titdat.stg_database));	
}


/*	############################################################
	# tp.c
	############################################################	*/

