/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : tp.c
*  Symbol prefix: tp
*
*  Description  : This module contains routines which handle the environment
*                 Routinen, die die Ausgabe der zahlreichen Umgebungen
*                 verwalten und fuer token_output() vorbereiten
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
*  Co-Authors   : Norbert Hanz (NHz), Ulf Dunkel (fd), Gerhard Stoll (ggs)
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
*  2009:
*    fd  Jun 04: !docinfo [translator] introduced
*  2010:
*    fd  Mar 02: - html_footer(): notes added and mailto: handling enhanced
*                - webmastername    -> domain_name
*                - webmasterurl     -> domain_link
*                - webmasteremail   -> contact_name
*                - webmastermailurl -> contact_link
*    fd  Mar 05: file tidied up
*  2013:
*    fd  Oct 23: - <h1> on HTML5 now uses class UDO_h1_align_center| UDO_h1_align_right
*                - <h2> on HTML5 now uses class UDO_h2_align_center| UDO_h2_align_right
*    fd  Oct 31: c_gif_output() renamed: c_html_image_output()
*  2014
*    ggs Apr 20: Add Node6
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
#include "udoport.h"
#include "constant.h"
#include "udo_type.h"
#include "udointl.h"
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
#include "udomem.h"
#include "lang.h"

#include "export.h"
#include "tp.h"





/*******************************************************************************
*
*     LOCAL / GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  init_docinfo_data():
*     Anpassung der Daten fuer die Titelseite samt Anforderung des benoetigten Speichers
*
*  Out:
*     - TRUE: OK
*     - error
*
******************************************|************************************/

LOCAL _BOOL init_docinfo_data(const char *data, char **var, int allow_empty)
{
	char *buffer;
	size_t len;

	len = strlen(data) * sizeof(char);
	len *= 2;							/* We need space if some text will be replace */
	len++;								/* End of string */

	buffer = (char *) malloc(len);

	if (buffer != NULL)					/* Check if the buffer could be allocated */
	{
		/* First we copy the data to the buffer, this prevents bug #16 with modern compilers */
		strcpy(buffer, data);

		del_whitespaces(buffer);
		c_divis(buffer);
		c_vars(buffer);
		c_tilde(buffer);
		c_styles(buffer);
		del_internal_styles(buffer);
		replace_udo_tilde(buffer);
		replace_udo_nbsp(buffer);
		replace_udo_quotes(buffer);
		delete_all_divis(buffer);

		if (buffer[0] == EOS && !allow_empty)
		{
			free(buffer);
			error_empty_docinfo();
			return FALSE;
		}

		*var = buffer;

		return TRUE;
	}

	/* An error occured when allocating the buffer */
	bFatalErrorDetected = TRUE;
	return FALSE;
}





/*******************************************************************************
*
*  set_show_variable():
*     Setzen von Informationen fuer Variablen
*
*  Notes:
*     Die Daten stehen in token[]. Ich habe die Funktion hier herein
*     gepackt, da ich keine neue C-Datei eroeffnen wollte.
*     
*     !show_variable [format] [foo]
*
*  Out:
*     - TRUE: OK
*
******************************************|************************************/

GLOBAL _BOOL set_show_variable(void)
{
	char s[512];
	char *cont;
	char *data;
	char inhalt[512];
	size_t contlen;

	tokcpy2(s, ArraySize(s));

	contlen = strlen(token[1]);

	contlen = get_brackets_ptr(s, &cont, &data);

	if (contlen == 0 || cont == NULL || data == NULL)
	{
		error_syntax_error();
		return FALSE;
	}

	inhalt[0] = EOS;
	strncpy(inhalt, cont, contlen);
	inhalt[contlen] = EOS;
	del_whitespaces(inhalt);

	if (strcmp(inhalt, "source_filename") == 0)
	{
		show_variable.source_filename = TRUE;
		return TRUE;
	}

	return FALSE;
}





/*******************************************************************************
*
*  set_mainlayout():
*     Setzen von Informationen fuer das Layout (neue Version)
*
*  Notes:
*     Die Daten stehen in token[]. Ich habe die Funktion hier herein
*     gepackt, da ich keine neue C-Datei eroeffnen wollte.
*     Hier werden Vorgaben gemacht, wenn der Nutzer keine Angaben zum
*     Layout macht.
*
*  Out:
*     - TRUE: OK
*
******************************************|************************************/

GLOBAL _BOOL set_mainlayout(void)
{
	int i;

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

	for (i = 0; i <= TOC_MAXDEPTH; i++)
		laydat.nodesize[i] = 0;

	return TRUE;
}





/*******************************************************************************
*
*  free_titdat():
*     reset all content of titdat[]
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void free_titdat(char **var)
{
	if (*var != NULL)
	{
		free(*var);
		*var = NULL;
	}
}





/*******************************************************************************
*
*  set_doclayout():
*     Setzen von Informationen fuer das Layout (neue Version)
*
*  Notes:
*     Die Daten stehen in token[]. Ich habe die Funktion hier herein
*     gepackt, da ich keine neue C-Datei eroeffnen wollte.
*
*     !doclayout [format] [foo]
*
*  Out:
*     - TRUE: OK
*     - error
*
******************************************|************************************/

GLOBAL _BOOL set_doclayout(void)
{
	char s[512];
	char *cont_format;
	char *cont_content;
	char *data;
	char format[512];
	char content[512];
	char *page;
	char page2[2];
	struct size_brackets contlen;
	char node[20];
	int i;

	tokcpy2(s, ArraySize(s));

	contlen = get_two_brackets_ptr(s, &cont_format, &cont_content, &data);

	if (contlen.format == 0 || contlen.content == 0 || cont_content == NULL || cont_format == NULL || data == NULL)
	{
		error_syntax_error();
		return FALSE;
	}

	format[0] = EOS;
	strncpy(format, cont_format, contlen.format);
	format[contlen.format] = EOS;
	del_whitespaces(format);

	content[0] = EOS;
	strncpy(content, cont_content, contlen.content);
	content[contlen.content] = EOS;
	del_whitespaces(content);

	if (strcmp(content, "paper") == 0)
	{
		if (str_for_desttype(format, TRUE) > 0)
		{
			/* Layout festlegen */
			free_titdat(&(laydat.paper));
			init_docinfo_data(data, &(laydat.paper), FALSE);
		}
		return TRUE;
	}

	if (strcmp(content, "propfontname") == 0)
	{
		if (str_for_desttype(format, TRUE) > 0)
		{
			/* Set proportional font */
			free_titdat(&(laydat.propfontname));
			init_docinfo_data(data, &(laydat.propfontname), FALSE);
		}
		return TRUE;
	}

	if (strcmp(content, "propfontsize") == 0)
	{
		if (str_for_desttype(format, TRUE) > 0)
		{
			/* Set size of proportional font */
			laydat.propfontsize = atoi(data);
		}
		return TRUE;
	}

	if (strcmp(content, "monofontname") == 0)
	{
		if (str_for_desttype(format, TRUE) > 0)
		{
			/* Set aquidistant font */
			free_titdat(&(laydat.monofontname));
			init_docinfo_data(data, &(laydat.monofontname), FALSE);
		}
		return TRUE;
	}

	if (strcmp(content, "monofontsize") == 0)
	{
		if (str_for_desttype(format, TRUE) > 0)
		{
			/* Set size of the aquidistant font */
			laydat.monofontsize = atoi(data);
		}
		return TRUE;
	}

	for (i = TOC_NODE1; i < TOC_MAXDEPTH; i++)
	{
		sprintf(node, "node%dsize", i + 1);
		if (strcmp(content, node) == 0)
		{
			if (str_for_desttype(format, TRUE) > 0)
			{
				/* Set size of node */
				laydat.nodesize[i + 1] = atoi(data);
			}
			return TRUE;
		}
	}

	/* Specialities for Postscript */
	if (strcmp(content, "openMode") == 0)
	{
		free_titdat(&(laydat.pagemode));
		if (strstr(data, "Outlines"))
			init_docinfo_data("/UseOutlines", &(laydat.pagemode), FALSE);
		else if (strstr(data, "Thumbs"))
			init_docinfo_data("/UseThumbs", &(laydat.pagemode), FALSE);
		else if (strstr(data, "Fullscreen"))
			init_docinfo_data("/FullScreen", &(laydat.pagemode), FALSE);
		else
			init_docinfo_data("/UseNone", &(laydat.pagemode), FALSE);

		free_titdat(&(laydat.openpage));
		page = strstr(data, "Page=");
		if (page != NULL)
		{
			page2[0] = *(page + 5);
			page2[1] = EOS;
			init_docinfo_data(page2, &(laydat.openpage), FALSE);
		} else
		{
			init_docinfo_data("1", &(laydat.openpage), FALSE);
		}

		free_titdat(&(laydat.hidetoolbar));
		if (strstr(data, "HideToolbar"))
			init_docinfo_data("true", &(laydat.hidetoolbar), FALSE);
		else
			init_docinfo_data("false", &(laydat.hidetoolbar), FALSE);

		free_titdat(&(laydat.hidemenubar));
		if (strstr(data, "HideMenubar"))
			init_docinfo_data("true", &(laydat.hidemenubar), FALSE);
		else
			init_docinfo_data("false", &(laydat.hidemenubar), FALSE);

		free_titdat(&(laydat.viewerpreferences));
		if (strstr(data, "OneColumn"))
			init_docinfo_data("/OneColumn", &(laydat.viewerpreferences), FALSE);
		else if (strstr(data, "ColumnLeft"))
			init_docinfo_data("/TwoColumnLeft", &(laydat.viewerpreferences), FALSE);
		else if (strstr(data, "ColumnRight"))
			init_docinfo_data("/TwoColumnRight", &(laydat.viewerpreferences), FALSE);
		else
			init_docinfo_data("/SinglePage", &(laydat.viewerpreferences), FALSE);

		free_titdat(&(laydat.fitwindow));
		if (strstr(data, "Title"))
			init_docinfo_data("true", &(laydat.fitwindow), FALSE);
		else
			init_docinfo_data("false", &(laydat.fitwindow), FALSE);

		return TRUE;
	}

	return FALSE;
}





/*******************************************************************************
*
*  set_docinfo():
*     set document information for title page (new approach) 
*
*  Notes:
*     The data can be found in token[]. In former versions of UDO, e.g. the 
*     app name was defined using "!program UDO", now with "!docinfo [program] UDO".
*
*  Out:
*     - TRUE: OK
*     - error
*
******************************************|************************************/

GLOBAL _BOOL set_docinfo(void)
{
	char s[MYFILE_FULL_LEN * 2];
	char *cont;
	char *data;
	char inhalt[512];
	char *buffer;

	char sDriv[MYFILE_DRIV_LEN + 1];
	char sPath[MYFILE_PATH_LEN + 1];
	char sFile[MYFILE_NAME_LEN + 1];
	char sSuff[MYFILE_SUFF_LEN + 1];

	size_t contlen;
	_UWORD bitcnt;

	tokcpy2(s, ArraySize(s));
	if (desttype == TOKPS)
		node2postscript(s, KPS_PS2DOCINFO);

	contlen = get_brackets_ptr(s, &cont, &data);

	if (contlen == 0 || cont == NULL || data == NULL)
	{
		error_syntax_error();
		return FALSE;
	}

	inhalt[0] = EOS;
	strncpy(inhalt, cont, contlen);
	inhalt[contlen] = EOS;
	del_whitespaces(inhalt);

	if (desttype == TOKPS)
		node2postscript(data, KPS_DOCINFO2PS);


	/* --- authorimage --- */

	if (strcmp(inhalt, "authorimage") == 0)
	{
		del_whitespaces(data);

		if (data[0] == EOS)
		{
			error_empty_docinfo();
		} else
		{
			path_adjust_separator(data);
			change_sep_suffix(data, sDocImgSuffix);
			buffer = strdup(data);
			if (buffer != NULL)
			{
				titdat.authorimage = buffer;
				if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
				{
					replace_char(titdat.authorimage, '\\', '/');
					/* Ausmasse nicht ermitteln -> da */
					/* ueber c_html_image_output() ausgegeben wird  */
				}
			} else
			{
				bFatalErrorDetected = TRUE;
			}
		}

		return TRUE;
	}

	/* --- authoricon --- */

	if (strcmp(inhalt, "authoricon") == 0)
	{
		del_whitespaces(data);

		if (data[0] == EOS)
		{
			error_empty_docinfo();
		} else
		{
			/* Endung abschneiden und mit !html_img_suffix ersetzen */
			fsplit(data, sDriv, sPath, sFile, sSuff);
			sprintf(data, "%s%s%s", sPath, sFile, sDocImgSuffix);
			path_adjust_separator(data);

			buffer = strdup(data);
			if (buffer != NULL)
			{
				titdat.authoricon = buffer;
				if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
				{
					replace_char(titdat.authoricon, '\\', '/');
					get_picture_size(data, NULL, &titdat.authoriconWidth, &titdat.authoriconHeight, &bitcnt);
				}
			} else
			{
				bFatalErrorDetected = TRUE;
			}
		}
		return TRUE;
	}

	/* --- authoricon_active --- */

	if (strcmp(inhalt, "authoricon_active") == 0)
	{
		del_whitespaces(data);

		if (data[0] == EOS)
		{
			error_empty_docinfo();
		} else
		{
			/* Endung abschneiden und mit !html_img_suffix ersetzen */
			fsplit(data, sDriv, sPath, sFile, sSuff);
			sprintf(data, "%s%s%s", sPath, sFile, sDocImgSuffix);
			path_adjust_separator(data);

			buffer = strdup(data);
			if (buffer != NULL)
			{
				titdat.authoricon_active = buffer;
				if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
				{
					replace_char(titdat.authoricon_active, '\\', '/');
					get_picture_size(data, NULL, &titdat.authoriconActiveWidth, &titdat.authoriconActiveHeight, &bitcnt);
				}
			} else
			{
				bFatalErrorDetected = TRUE;
			}
		}
		return TRUE;
	}

	/* --- programimage --- */

	if (strcmp(inhalt, "programimage") == 0)
	{
		del_whitespaces(data);

		if (data[0] == EOS)
		{
			error_empty_docinfo();
		} else
		{
			path_adjust_separator(data);
			change_sep_suffix(data, sDocImgSuffix);
			buffer = strdup(data);
			if (buffer != NULL)
			{
				titdat.programimage = buffer;
				if (desttype == TOHTM || desttype == TOMHH || desttype == TOHAH)
				{
					replace_char(titdat.programimage, '\\', '/');
					/* Ausmasse nicht ermitteln -> da */
					/* ueber c_html_image_output() ausgegeben wird  */
				}
			} else
			{
				bFatalErrorDetected = TRUE;
			}
		}

		return TRUE;
	}

	/* --- title --- */

	if (strcmp(inhalt, "title") == 0)
	{
		free_titdat(&(titdat.title));
		init_docinfo_data(data, &(titdat.title), FALSE);
		return TRUE;
	}

	/* --- program --- */

	if (strcmp(inhalt, "program") == 0)
	{
		free_titdat(&(titdat.program));
		init_docinfo_data(data, &(titdat.program), FALSE);
		return TRUE;
	}

	/* --- version --- */

	if (strcmp(inhalt, "version") == 0)
	{
		free_titdat(&(titdat.version));
		init_docinfo_data(data, &(titdat.version), FALSE);
		return TRUE;
	}

	/* --- date --- */

	if (strcmp(inhalt, "date") == 0)
	{
		free_titdat(&(titdat.date));
		init_docinfo_data(data, &(titdat.date), FALSE);
		return TRUE;
	}

	/* --- author --- */

	if (strcmp(inhalt, "author") == 0)
	{
		free_titdat(&(titdat.author));
		init_docinfo_data(data, &(titdat.author), FALSE);
		return TRUE;
	}

	/* --- address --- */

	if (strcmp(inhalt, "address") == 0)
	{
		if (address_counter < MAXADDRESS)
		{
			address_counter++;
			init_docinfo_data(data, &(titdat.address[address_counter]), FALSE);
		}
		return TRUE;
	}

	/* --- keywords --- */

	if (strcmp(inhalt, "keywords") == 0)
	{
		free_titdat(&(titdat.keywords));
		init_docinfo_data(data, &(titdat.keywords), FALSE);
		return TRUE;
	}

	/* --- description --- */

	if (strcmp(inhalt, "description") == 0)
	{
		free_titdat(&(titdat.description));
		init_docinfo_data(data, &(titdat.description), FALSE);
		return TRUE;
	}

	/* --- robots --- */

	if (strcmp(inhalt, "robots") == 0)
	{
		free_titdat(&(titdat.robots));
		init_docinfo_data(data, &(titdat.robots), FALSE);

		if (strcmp(titdat.robots, "none") != 0)
		{
			if (strcmp(titdat.robots, "noindex") != 0)
			{
				if (strcmp(titdat.robots, "index") != 0)
				{
					if (strcmp(titdat.robots, "nofollow") != 0)
					{
						if (strcmp(titdat.robots, "follow") != 0)
						{
							/* For HTML Apple Help */
							if (strcmp(titdat.robots, "keywords") != 0)
							{
								/* For HTML Apple Help */
								if (strcmp(titdat.robots, "segments") != 0)
								{
									/* For HTML Apple Help */
									if (strcmp(titdat.robots, "anchors") != 0)
									{
										error_syntax_error();
										titdat.robots = NULL;
										return TRUE;
									}
								}
							}
						}
					}
				}
			}
		}

		return TRUE;
	}

	/* --- company --- */

	if (strcmp(inhalt, "company") == 0)
	{
		free_titdat(&(titdat.company));
		init_docinfo_data(data, &(titdat.company), FALSE);
		return TRUE;
	}

	/* --- category --- */

	if (strcmp(inhalt, "category") == 0)
	{
		free_titdat(&(titdat.category));
		init_docinfo_data(data, &(titdat.category), FALSE);
		return TRUE;
	}

	/* --- stgdatabase --- */

	/* Spezialitaeten fuer ST-Guide */
	if (strcmp(inhalt, "stgdatabase") == 0)
	{
		free_titdat(&(titdat.stg_database));
		init_docinfo_data(data, &(titdat.stg_database), TRUE);
		return TRUE;
	}

	/* --- drcstatusline --- */

	/* Spezialitaeten fuer DRC */
	if (strcmp(inhalt, "drcstatusline") == 0)
	{
		free_titdat(&(titdat.drc_statusline));
		init_docinfo_data(data, &(titdat.drc_statusline), FALSE);
		return TRUE;
	}

	/* --- htmltitle --- */

	/* Spezialitaeten fuer HTML */
	if (strcmp(inhalt, "htmltitle") == 0)
	{
		free_titdat(&(titdat.htmltitle));
		init_docinfo_data(data, &(titdat.htmltitle), FALSE);
		return TRUE;
	}

	/* --- domain_name --- */

	if (strcmp(inhalt, "webmastername") == 0)
	{
		warning_message(_("!docinfo [webmastername] is deprecated, use !docinfo [domain_name] instead"));
		strcpy(inhalt, "domain_name");
	}
	if (strcmp(inhalt, "domain_name") == 0)
	{
		free_titdat(&(titdat.domain_name));
		init_docinfo_data(data, &(titdat.domain_name), FALSE);
		return TRUE;
	}

	/* --- domain_link --- */

	if (strcmp(inhalt, "webmasterurl") == 0)
	{
		warning_message(_("!docinfo [webmasterurl] is deprecated, use !docinfo [domain_link] instead"));
		strcpy(inhalt, "domain_link");
	}
	if (strcmp(inhalt, "domain_link") == 0)
	{
		del_whitespaces(data);			/* nicht init_...!!! */
		convert_tilde(data);
		if (data[0] == EOS)
		{
			error_empty_docinfo();
		} else
		{
			buffer = strdup(data);
			if (buffer != NULL)
			{
				free_titdat(&(titdat.domain_link));
				titdat.domain_link = buffer;
			} else
			{
				bFatalErrorDetected = TRUE;
			}
		}
		return TRUE;
	}

	/* --- contact_name --- */

	if (strcmp(inhalt, "webmasteremail") == 0)
	{
		warning_message(_("!docinfo [webmasteremail] is deprecated, use !docinfo [contact_name] instead"));
		strcpy(inhalt, "contact_name");
	}
	if (strcmp(inhalt, "contact_name") == 0)
	{
		free_titdat(&(titdat.contact_name));
		init_docinfo_data(data, &(titdat.contact_name), FALSE);
		return TRUE;
	}

	/* --- contact_link --- */

	if (strcmp(inhalt, "webmastermailurl") == 0)
	{
		warning_message(_("!docinfo [webmastermailurl] is deprecated, use !docinfo [contact_link] instead"));
		strcpy(inhalt, "contact_link");
	}
	if (strcmp(inhalt, "contact_link") == 0)
	{
		free_titdat(&(titdat.contact_link));
		init_docinfo_data(data, &(titdat.contact_link), FALSE);
		return TRUE;
	}

	/* --- appletitle --- */

	/* Spezialitaeten fuer HTML Apple Help */
	if (strcmp(inhalt, "appletitle") == 0)
	{
		free_titdat(&(titdat.appletitle));
		init_docinfo_data(data, &(titdat.appletitle), TRUE);
		return TRUE;
	}

	/* --- appleicon --- */

	if (strcmp(inhalt, "appleicon") == 0)
	{
		free_titdat(&(titdat.appleicon));
		init_docinfo_data(data, &(titdat.appleicon), TRUE);
		return TRUE;
	}

	/* --- translator --- */

	if (strcmp(inhalt, "translator") == 0)
	{
		free_titdat(&(titdat.translator));
		init_docinfo_data(data, &(titdat.translator), TRUE);
		return TRUE;
	}

	/* --- distributor --- */

	if (strcmp(inhalt, "distributor") == 0)
	{
		free_titdat(&(titdat.distributor));
		init_docinfo_data(data, &(titdat.distributor), TRUE);
		return TRUE;
	}

	error_message(_("unknown !docinfo: %s"), inhalt);

	return FALSE;
}





/*******************************************************************************
*
*  c_maketitle():
*     creates and outputs title page of the document
*
*  Out:
*     -
*
******************************************|************************************/

GLOBAL void c_maketitle(void)
{
	int i;
	char n[512];
	char s1[128];
	char s2[256];

	_BOOL has_author;
	_BOOL has_program;
	_BOOL has_title;
	_BOOL has_version;
	_BOOL has_date;
	_BOOL has_authorimage;
	_BOOL has_programimage;
	_BOOL has_address;
	_BOOL has_company;
	_BOOL has_translator;
	_BOOL has_distributor;

	if (called_maketitle)				/* this function has been used already? */
	{
		error_called_twice("!maketitle");
		return;
	}

	called_maketitle = TRUE;			/* set flag when this function is used */

	has_author = titdat.author != NULL;
	has_authorimage = titdat.authorimage != NULL;
	has_address = address_counter > 0;
	has_program = titdat.program != NULL;
	has_programimage = titdat.programimage != NULL;
	has_title = titdat.title != NULL;
	has_version = titdat.version != NULL;
	has_date = titdat.date != NULL;
	has_company = titdat.company != NULL;
	has_translator = titdat.translator != NULL;
	has_distributor = titdat.distributor != NULL;

	if (!(has_author ||
		  has_authorimage ||
		  has_program ||
		  has_programimage ||
		  has_title ||
		  has_version ||
		  has_date ||
		  has_address ||
		  has_company ||
		  has_translator ||
		  has_distributor))
	{
		error_message(_("no title data available"));
		return;
	}


	switch (desttype)					/* which output format? */
	{
	case TOTEX:
	case TOPDL:
		outln("\\begin{titlepage}");
		outln("\\begin{center}");

		if (has_title)
		{
			voutlnf("{\\Large %s} \\\\", titdat.title);
			outln("\\bigskip");
		}

		if (has_programimage)
		{
			if (desttype == TOTEX)
			{
				switch (iTexVersion)
				{
				case TEX_LINDNER:
				case TEX_STRUNK:
					c_begin_center();
					c_img_output(titdat.programimage, "", FALSE, TRUE);
					c_end_center();
					break;
				case TEX_EMTEX:
				case TEX_MIKTEX:
					c_begin_center();
					c_msp_output(titdat.programimage, "", FALSE);
					c_end_center();
					break;
				case TEX_TETEX:
					c_begin_center();
					c_eps_output(titdat.programimage, "", FALSE);
					c_end_center();
					break;
				}
			} else
			{
				c_begin_center();
				c_png_output(titdat.programimage, "", FALSE);
				c_end_center();
			}
		}

		if (has_program)
		{
			voutlnf("{\\Huge %s} \\\\", titdat.program);
			outln("\\bigskip");
		}

		if (has_version)
		{
			voutlnf("{\\large %s} \\\\", titdat.version);
			outln("\\bigskip");
		}

		if (has_date)
		{
			voutlnf("{\\large %s} \\\\", titdat.date);
		}

		if (has_author || has_authorimage)
		{
			outln("\\vfill");
			voutlnf("%s\\\\", get_lang()->by);
			outln("\\medskip");
		}

		if (has_authorimage)
		{
			if (desttype == TOTEX)
			{
				switch (iTexVersion)
				{
				case TEX_LINDNER:
				case TEX_STRUNK:
					c_begin_center();
					c_img_output(titdat.authorimage, "", FALSE, TRUE);
					c_end_center();
					break;
				case TEX_EMTEX:
				case TEX_MIKTEX:
					c_begin_center();
					c_msp_output(titdat.authorimage, "", FALSE);
					c_end_center();
					break;
				case TEX_TETEX:
					c_begin_center();
					c_eps_output(titdat.authorimage, "", FALSE);
					c_end_center();
					break;
				}
			} else
			{
				c_begin_center();
				c_png_output(titdat.authorimage, "", FALSE);
				c_end_center();
			}
		}

		if (has_author)
		{
			voutlnf("%s \\\\", titdat.author);
		}

		if (has_company)
		{
			outln("\\vfill");
			voutlnf("%s\\\\", get_lang()->fur);
			outln("\\medskip");
			voutlnf("%s \\\\", titdat.company);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					voutlnf("%s \\\\", titdat.address[i]);
				}
			}
		}

		if (has_translator)
		{
			outln("\\vfill");
			voutlnf("%s\\\\", get_lang()->translator);
			outln("\\medskip");
			voutlnf("%s \\\\", titdat.translator);
		}

		if (has_distributor)
		{
			outln("\\vfill");
			voutlnf("%s\\\\", get_lang()->distributor);
			outln("\\medskip");
			voutlnf("%s \\\\", titdat.distributor);
		}

		outln("\\end{center}");
		outln("\\end{titlepage}");
		break;

	case TOLYX:
		outln("\\layout Title");
		outln("\\fill_top");
		outln("");

		if (has_title)
		{
			outln("\\layout Section*");
			outln("\\align center");
			voutlnf("%s", titdat.title);
			outln("\\newline");
			outln("");
		}

		if (has_programimage)
		{
			c_begin_center();
			c_eps_output(titdat.programimage, "", FALSE);
			c_end_center();
		}

		if (has_program)
		{
			voutlnf("\\size giant %s", titdat.program);
			outln("");
		}

		if (has_version)
		{
			outln("\\layout Subsection*");
			outln("\\align center");
			voutlnf("%s", titdat.version);
			outln("");
		}

		if (has_date)
		{
			outln("\\layout Subsection*");
			outln("\\align center");
			voutlnf("%s", titdat.date);
			outln("");
		}

		if (has_author || has_authorimage)
		{
			outln("\\fill_bottom");
			outln("\\layout Subsubsection*");
			outln("\\align center");
			outln("");
			voutlnf("%s", get_lang()->by);
			outln("");
		}

		if (has_authorimage)
		{
			outln("\\align center");
			c_eps_output(titdat.authorimage, "", FALSE);
			outln("");
		}

		if (has_author)
		{
			outln("\\fill_bottom");
			outln("\\layout Subsection*");
			outln("\\align center");
			outln("");
			voutlnf("%s", titdat.author);
			outln("");
		}

		if (has_company)
		{
			outln("\\fill_bottom");
			outln("\\layout Subsubsection*");
			outln("\\align center");
			voutlnf("%s", get_lang()->fur);
			outln("");
			outln("\\layout Subsection*");
			outln("\\align center");
			outln("");
			voutlnf("%s", titdat.company);
			outln("");
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					outln("\\layout Subsection*");
					outln("\\align center");
					voutlnf("%s", titdat.address[i]);
					outln("");
				}
			}
		}

		if (has_translator)
		{
			outln("\\fill_bottom");
			outln("\\layout Subsubsection*");
			outln("\\align center");
			outln("");
			voutlnf("%s", get_lang()->translator);
			outln("");
			outln("\\layout Subsection*");
			outln("\\align center");
			outln("");
			voutlnf("%s", titdat.translator);
			outln("");
		}

		if (has_distributor)
		{
			outln("\\fill_bottom");
			outln("\\layout Subsubsection*");
			outln("\\align center");
			outln("");
			voutlnf("%s", get_lang()->distributor);
			outln("");
			outln("\\layout Subsection*");
			outln("\\align center");
			outln("");
			voutlnf("%s", titdat.distributor);
			outln("");
		}
		break;

	case TOINF:
		outln("@titlepage");
		outln("@sp 1");

		if (has_title)
		{
			voutlnf("@center @titlefont{%s}", titdat.title);
			outln("@sp 1");
		}

		if (has_program)
		{
			voutlnf("@center @titlefont{%s}", titdat.program);
			outln("@sp 1");
		}

		if (has_version)
		{
			voutlnf("@center %s", titdat.version);
			outln("@sp 1");
		}

		if (has_date)
		{
			voutlnf("@center %s", titdat.date);
			outln("@sp 1");
		}

		if (has_author)
		{
			outln("@sp 10");
			voutlnf("@center %s", get_lang()->by);
			outln("@sp 1");
			voutlnf("@center %s", titdat.author);
		}

		if (has_company)
		{
			outln("@sp 10");
			voutlnf("@center %s", get_lang()->fur);
			outln("@sp 1");
			voutlnf("@center %s", titdat.company);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					voutlnf("@center %s", titdat.address[i]);
				}
			}
		}

		if (has_translator)
		{
			outln("@sp 10");
			voutlnf("@center %s", get_lang()->translator);
			outln("@sp 1");
			voutlnf("@center %s", titdat.translator);
		}

		if (has_distributor)
		{
			outln("@sp 10");
			voutlnf("@center %s", get_lang()->distributor);
			outln("@sp 1");
			voutlnf("@center %s", titdat.distributor);
		}

		outln("@end titlepage");
		break;

	case TOSTG:
		stg_out_endnode();
		toc_table[p2_toc_counter]->ignore_toptoc = TRUE;
		voutlnf("@node \"%s\"", get_lang()->title);
		stg_headline("", get_lang()->title, FALSE);
		outln("");
		outln("@autorefoff");

		if (has_title)
		{
			outlncenter(titdat.title);
			outln("");
		}

		if (has_programimage)
		{
			strcpy(n, titdat.programimage);
			change_sep_suffix(n, ".img");
			c_begin_center();
			c_img_output(n, "", FALSE, TRUE);
			c_end_center();
		}

		if (has_program)
		{
			outlncenter(titdat.program);
			outln("");
		}

		if (has_version)
			outlncenter(titdat.version);

		if (has_date)
			outlncenter(titdat.date);

		if (has_author || has_authorimage)
		{
			outln("");
			outlncenter(get_lang()->by);
		}

		if (has_authorimage)
		{
			strcpy(n, titdat.authorimage);
			change_sep_suffix(n, ".img");
			c_begin_center();
			c_img_output(n, "", FALSE, TRUE);
			c_end_center();
		}

		if (has_author)
		{
			outln("");
			outlncenter(titdat.author);
		}

		if (has_company)
		{
			outln("");
			outlncenter(get_lang()->fur);
			outln("");
			outlncenter(titdat.company);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					outlncenter(titdat.address[i]);
				}
			}
		}

		if (has_translator)
		{
			outln("");
			outlncenter(get_lang()->translator);
			outln("");
			outlncenter(titdat.translator);
		}

		if (has_distributor)
		{
			outln("");
			outlncenter(get_lang()->distributor);
			outln("");
			outlncenter(titdat.distributor);
		}

		outln("@autorefon");
		outln("");

		if (uses_tableofcontents)
		{
			outln("");
			outlncenter(get_lang()->contents);
		}
#if 0
		/* no @endnode here, so the user can add raw cmds to title page */
		outln("@endnode");
		outln("");
		outln("");
#endif
		stg_need_endnode = TRUE;
		break;

	case TOAMG:
		stg_out_endnode();
		voutlnf("@node \"%s\" \"%s\"", get_lang()->title, titleprogram);
		stg_headline("", get_lang()->title, FALSE);
		outln("");

		if (has_title)
		{
			outlncenter(titdat.title);
			outln("");
		}

		if (has_program)
		{
			outlncenter(titdat.program);
			outln("");
		}

		if (has_version)
			outlncenter(titdat.version);

		if (has_date)
			outlncenter(titdat.date);

		if (has_author)
		{
			outln("");
			outlncenter(get_lang()->by);
			outln("");
			outlncenter(titdat.author);
		}

		if (has_company)
		{
			outln("");
			outlncenter(get_lang()->fur);
			outln("");
			outlncenter(titdat.company);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					outlncenter(titdat.address[i]);
				}
			}
		}

		if (has_translator)
		{
			outln("");
			outlncenter(get_lang()->translator);
			outln("");
			outlncenter(titdat.translator);
		}

		if (has_distributor)
		{
			outln("");
			outlncenter(get_lang()->distributor);
			outln("");
			outlncenter(titdat.distributor);
		}

		outln("");

		if (uses_tableofcontents)
		{
			outln("");
			outlncenter(get_lang()->contents);
		}
#if 0
		/* no @endnode here, so the user can add raw cmds to title page */
		outln("@endnode");
		outln("");
		outln("");
#endif
		stg_need_endnode = TRUE;
		break;

	case TOPCH:
		/* written during c_tableofcontents; see pch_titlepage() */
		break;

	case TODRC:
		n[0] = EOS;
		if (has_title)
		{
			strcat(n, titdat.title);
			strcat(n, " ");
		}
		if (has_program)
		{
			strcat(n, titdat.program);
		}
		del_whitespaces(n);
		if (n[0] == EOS)
		{
			strcpy(n, get_lang()->unknown);
		}
		voutlnf("%%%% 1, %s", n);

		/* Eigene Titelseitenroutine, damit die Zentrierung klappt */
		if (has_title)
		{
			outlncenterfill(titdat.title);
			outln("");
		}

		if (has_program)
		{
			outlncenterfill(titdat.program);
			outln("");
		}

		if (has_version)
			outlncenterfill(titdat.version);

		if (has_date)
			outlncenterfill(titdat.date);

		if (has_author)
		{
			outln("");
			outlncenterfill(get_lang()->by);
			outln("");
			outlncenterfill(titdat.author);
		}

		if (has_company)
		{
			outln("");
			outlncenterfill(get_lang()->fur);
			outln("");
			outlncenterfill(titdat.company);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					outlncenterfill(titdat.address[i]);
				}
			}
			outln("");
		}

		if (has_translator)
		{
			outln("");
			outlncenterfill(get_lang()->translator);
			outln("");
			outlncenterfill(titdat.translator);
		}

		if (has_distributor)
		{
			outln("");
			outlncenterfill(get_lang()->distributor);
			outln("");
			outlncenterfill(titdat.distributor);
		}

		outln("");
		break;

	case TOASC:
	case TOMAN:
		if (has_title)
		{
			outlncenter(titdat.title);
			outln("");
		}

		if (has_program)
		{
			outlncenter(titdat.program);
			outln("");
		}

		if (has_version)
			outlncenter(titdat.version);

		if (has_date)
			outlncenter(titdat.date);

		if (has_author)
		{
			outln("");
			outlncenter(get_lang()->by);
			outln("");
			outlncenter(titdat.author);
		}

		if (has_company)
		{
			outln("");
			outlncenter(get_lang()->fur);
			outln("");
			outlncenter(titdat.company);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					outlncenter(titdat.address[i]);
				}
			}
			outln("");
		}

		if (has_translator)
		{
			outln("");
			outlncenter(get_lang()->translator);
			outln("");
			outlncenter(titdat.translator);
		}

		if (has_distributor)
		{
			outln("");
			outlncenter(get_lang()->distributor);
			outln("");
			outlncenter(titdat.distributor);
		}

		outln("");
		outln("");

		if (desttype == TOMAN)
		{
			c_newpage();
		}
		break;

	case TOSRC:
	case TOSRP:
		memset(n, '#', 62);
		n[62] = EOS;
		voutlnf("%s  %s", sSrcRemOn, n);

		if (has_title)
		{
			strcpy(s1, titdat.title);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
			outln("    #");
		}

		if (has_program)
		{
			strcpy(s1, titdat.program);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
			outln("    #");
		}

		if (has_version)
		{
			strcpy(s1, titdat.version);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
		}

		if (has_date)
		{
			strcpy(s1, titdat.date);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
		}

		if (has_author)
		{
			outln("    #");
			/* YYY fd:20071108: the next output should be localized! */
			strcpy(s1, "Copyright (C) by");
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
			outln("    #");
			strcpy(s1, titdat.author);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
		}

		if (has_company)
		{
			outln("    #");
			strcpy(s1, get_lang()->fur);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
			outln("    #");
			strcpy(s1, titdat.company);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					strcpy(s1, titdat.address[i]);
					stringcenter(s1, 60);
					voutlnf("    # %s", s1);
				}
			}
			outln("    #");
		}

		if (has_translator)
		{
			outln("    #");
			strcpy(s1, get_lang()->translator);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
			outln("    #");
			strcpy(s1, titdat.translator);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
		}

		if (has_distributor)
		{
			outln("    #");
			strcpy(s1, get_lang()->distributor);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
			outln("    #");
			strcpy(s1, titdat.distributor);
			stringcenter(s1, 60);
			voutlnf("    # %s", s1);
		}

		voutlnf("    %s %s", n, sSrcRemOff);
		break;

	case TORTF:
		outln(rtf_par);

		if (has_title)
		{
			voutlnf("\\qc{\\fs%d %s}%s%s", iDocPropfontSize + 14, titdat.title, rtf_par, rtf_parpard);
		}

		if (has_programimage)
		{
			outln(rtf_par);
			c_begin_center();
			c_bmp_output(titdat.programimage, "", FALSE);
			c_end_center();
		}

		if (has_program)
		{
			voutlnf("\\qc{\\fs%d %s}%s%s", iDocPropfontSize + 38, titdat.program, rtf_par, rtf_parpard);
		}

		if (has_version)
		{
			voutlnf("\\qc{\\fs%d %s}%s", iDocPropfontSize + 6, titdat.version, rtf_parpard);
		}

		if (has_date)
		{
			voutlnf("\\qc{\\fs%d %s}%s", iDocPropfontSize + 6, titdat.date, rtf_parpard);
		}

		if (has_author || has_address)
		{
			for (i = 0; i < ((has_company ? 22 : 25) - address_counter); i++)
				out(rtf_par);
			outln(rtf_par);
		}

		if (has_author || has_authorimage)
		{
			voutlnf("\\qc{%s}%s%s", get_lang()->by, rtf_par, rtf_parpard);
		}

		if (has_authorimage)
		{
			outln(rtf_par);
			c_begin_center();
			c_bmp_output(titdat.authorimage, "", FALSE);
			c_end_center();
		}

		if (has_author)
		{
			voutlnf("\\qc{%s}%s", titdat.author, rtf_parpard);
		}

		if (has_company)
		{
			voutlnf("%s \\qc{%s}%s%s", rtf_par, get_lang()->fur, rtf_par, rtf_parpard);
			voutlnf("\\qc{%s}%s", titdat.company, rtf_parpard);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					voutlnf("\\qc{%s}%s", titdat.address[i], rtf_parpard);
				}
			}
		}

		if (has_translator)
		{
			voutlnf("%s \\qc{%s}%s%s", rtf_par, get_lang()->translator, rtf_par, rtf_par);
			voutlnf("\\qc{%s}%s", titdat.translator, rtf_par);
		}

		if (has_distributor)
		{
			voutlnf("%s \\qc{%s}%s%s", rtf_par, get_lang()->distributor, rtf_par, rtf_par);
			voutlnf("\\qc{%s}%s", titdat.distributor, rtf_par);
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
		voutlnf("${\\footnote $ %s}", get_lang()->title);
		voutlnf("K{\\footnote K %s}", get_lang()->title);

		if (!no_buttons)
		{
			outln(win_browse);
			outln("!{\\footnote ! DisableButton(\"BTN_UP\") }");
			for (i = 0; i < iNumWinButtons; i++)
				voutlnf("!{\\footnote ! DisableButton(\"%s\") }", sDocWinButtonName[i]);
		}

		if (has_title)
		{
			voutlnf("\\qc{\\fs%d %s}\\par\\pard", iDocPropfontSize + 6, titdat.title);
		}

		if (has_programimage)
		{
			outln(rtf_par);
			c_begin_center();
			c_bmp_output(titdat.programimage, "", FALSE);
			c_end_center();
		}

		if (has_program)
		{
			voutlnf("\\qc{\\fs%d %s}\\par\\pard", iDocPropfontSize + 26, titdat.program);
		}

		if (has_version)
			voutlnf("\\qc{%s}\\par\\pard", titdat.version);

		if (has_date)
			voutlnf("\\qc{%s}\\par\\pard", titdat.date);

		if (has_author || has_authorimage)
		{
			voutlnf("\\par\\qc{%s}\\par\\pard", get_lang()->by);
		}

		if (has_authorimage)
		{
			outln(rtf_par);
			c_begin_center();
			c_bmp_output(titdat.authorimage, "", FALSE);
			c_end_center();
		}

		if (has_author)
		{
			voutlnf("\\qc{%s}\\par\\pard", titdat.author);
		}

		if (has_company)
		{
			voutlnf("\\par\\qc{%s}\\par\\pard", get_lang()->fur);
			voutlnf("\\qc{%s}\\par\\pard", titdat.company);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					if (strncmp(titdat.address[i], "http://", 7) == 0 || strncmp(titdat.address[i], "https://", 8) == 0)
					{
						voutlnf("\\qc{{\\uldb %s}{\\v !ShellExecuteA(0, \"open\", \"%s\", \"\", \"\", 1)}}\\par\\pard",
								titdat.address[i], titdat.address[i]);
					} else if (strchr(titdat.address[i], '@') != NULL)
					{
						voutlnf
							("\\qc{{\\uldb %s}{\\v !ShellExecuteA(0, \"open\", \"mailto:%s\", \"\", \"\", 1)}}\\par\\pard",
							 titdat.address[i], titdat.address[i]);
					} else
					{
						voutlnf("\\qc{%s}\\par\\pard", titdat.address[i]);
					}
				}
			}
		}

		if (has_translator)
		{
			voutlnf("\\par\\qc{%s}\\par\\pard", get_lang()->translator);
			voutlnf("\\qc{%s}\\par\\pard", titdat.translator);
		}

		if (has_distributor)
		{
			voutlnf("\\par\\qc{%s}\\par\\pard", get_lang()->distributor);
			voutlnf("\\qc{%s}\\par\\pard", titdat.distributor);
		}

		outln("\\par\\par");

		if (uses_tableofcontents)
		{
			node2NrWinhelp(n, 0);
			voutlnf("\\qc{{\\uldb %s}{\\v %s}}\\par\\pard", get_lang()->contents, n);
		}

		outln("}\\page");
		break;

	case TOAQV:
		check_endnode();

		outln("");
		outln("{");
		voutlnf("#{\\footnote # %s}", WIN_TITLE_NODE_NAME);
		voutlnf("${\\footnote $ %s}", get_lang()->title);
		voutlnf("K{\\footnote K %s}", get_lang()->title);

		if (!no_buttons)
		{
			outln(win_browse);
			outln("!{\\footnote ! DisableButton(\"BTN_UP\") }");
		}

		if (has_title)
		{
			voutlnf("\\qc %s\\par\\pard\\par", titdat.title);
		}

		if (has_programimage)
		{
			outln(rtf_par);
			c_begin_center();
			c_bmp_output(titdat.programimage, "", FALSE);
			c_end_center();
		}

		if (has_program)
		{
			voutlnf("\\qc\\fs%d %s\\par\\pard\\plain", iDocPropfontSize + 26, titdat.program);
		}

		if (has_version)
			voutlnf("\\qc %s\\par\\pard", titdat.version);

		if (has_date)
			voutlnf("\\qc %s\\par\\pard", titdat.date);

		if (has_author || has_authorimage)
		{
			voutlnf("\\par\\qc %s\\par\\pard", get_lang()->by);
		}

		if (has_authorimage)
		{
			outln(rtf_par);
			c_begin_center();
			c_bmp_output(titdat.authorimage, "", FALSE);
			c_end_center();
		}

		if (has_author)
		{
			voutlnf("\\qc %s\\par\\pard", titdat.author);
		}

		if (has_company)
		{
			voutlnf("\\par\\qc %s\\par\\pard", get_lang()->fur);
			voutlnf("\\qc %s\\par\\pard", titdat.company);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					voutlnf("\\qc %s\\par\\pard", titdat.address[i]);
				}
			}
		}

		if (has_translator)
		{
			voutlnf("\\par\\qc %s\\par\\pard", get_lang()->translator);
			voutlnf("\\qc %s\\par\\pard", titdat.translator);
		}

		if (has_distributor)
		{
			voutlnf("\\par\\qc %s\\par\\pard", get_lang()->distributor);
			voutlnf("\\qc %s\\par\\pard", titdat.distributor);
		}

		outln("\\par\\par");
		if (uses_tableofcontents)
		{
			voutlnf("\\qc {\\uldb %s}{\\v %s}\\par\\pard", get_lang()->contents, get_lang()->contents);
		}

		outln("}\\page");
		break;

	case TOHAH:
	case TOHTM:
	case TOMHH:
		outln("<div id=\"udo_titlepage\">");

		if (has_title)
		{
#if 0
			if (html_doctype == HTML5)
			{
				voutlnf("<h2 class=\"UDO_h2_align_center\">%s</h2>", titdat.title);
			} else
#endif
			{
				voutlnf("<h2 align=\"center\">%s</h2>", titdat.title);
			}
		}

		if (has_programimage)
		{
			c_begin_center();
			c_html_image_output(titdat.programimage, "");
			c_end_center();
		}

		if (has_program)
		{
#if 0
			if (html_doctype == HTML5)
			{
				voutlnf("<h1 class=\"UDO_h1_align_center\">%s</h1>", titdat.program);
			} else
#endif
			{
				voutlnf("<h1 align=\"center\">%s</h1>", titdat.program);
			}
		}

		if (has_version || has_date || has_author || has_address)
		{
#if 0
			if (html_doctype == HTML5)
			{
				outln("<p class=\"UDO_p_align_center\">");
			} else
#endif
			{
				outln("<p align=\"center\">");
			}
		}

		if (has_version)
		{
			voutlnf("%s%s", titdat.version, xhtml_br);
		}

		if (has_date)
		{
			voutlnf("%s%s", titdat.date, xhtml_br);
		}

		if (has_author || has_authorimage)
		{
			voutlnf("%s%s%s", xhtml_br, get_lang()->by, xhtml_br);
		}

		if (has_authorimage)
		{
			c_begin_center();
			c_html_image_output(titdat.authorimage, "");
			c_end_center();
			if (has_author || has_address)
			{
#if 0
				if (html_doctype == HTML5)
				{
					outln("<p class=\"UDO_p_align_center\">");
				} else
#endif
				{
					outln("<p align=\"center\">");
				}
			}
		}

		if (has_author)
		{
			voutlnf("%s%s", titdat.author, xhtml_br);
		}

		if (has_company)
		{
			voutlnf("%s%s%s", xhtml_br, get_lang()->fur, xhtml_br);
			voutlnf("%s%s", titdat.company, xhtml_br);
		}

		if (has_address)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					if (strncmp(titdat.address[i], "http://", 7) == 0 || strncmp(titdat.address[i], "https://", 8) == 0)
					{
						if (html_frames_layout)
							voutlnf("<a href=\"%s\" target=\"_top\">%s</a>%s", titdat.address[i], titdat.address[i],
									xhtml_br);
						else
							voutlnf("<a href=\"%s\">%s</a>%s", titdat.address[i], titdat.address[i], xhtml_br);
					} else if (strchr(titdat.address[i], '@') != NULL)
					{
						voutlnf("<a href=\"mailto:%s\">%s</a>%s", titdat.address[i], titdat.address[i], xhtml_br);
					} else
					{
						voutlnf("%s%s", titdat.address[i], xhtml_br);
					}
				}
			}
		}

		if (has_translator)
		{
			voutlnf("%s%s%s", xhtml_br, get_lang()->translator, xhtml_br);
			voutlnf("%s%s", titdat.translator, xhtml_br);
		}

		if (has_distributor)
		{
			voutlnf("%s%s%s", xhtml_br, get_lang()->distributor, xhtml_br);
			voutlnf("%s%s", titdat.distributor, xhtml_br);
		}

		if (has_version || has_date || has_author || has_address || has_translator || has_distributor)
		{
			outln("<p>");
		}

		if (uses_tableofcontents)
		{
			outln(xhtml_hr);
			outln("");
		}

		outln("</div>");
		break;

	case TOTVH:
		outln("");
		voutlnf(".topic %s=0", get_lang()->title);
		outln("");

		if (has_title)
		{
			outlncenter(titdat.title);
			outln("");
		}

		if (has_program)
		{
			outlncenter(titdat.program);
			outln("");
		}

		if (has_version)
			outlncenter(titdat.version);

		if (has_date)
			outlncenter(titdat.date);

		if (has_author)
		{
			outln("");
			outlncenter(get_lang()->by);
			outln("");
			outlncenter(titdat.author);
		}

		if (has_company)
		{
			outln("");
			outlncenter(get_lang()->fur);
			outln("");
			outlncenter(titdat.company);
		}

		if (address_counter > 0)
		{
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					outlncenter(titdat.address[i]);
				}
			}
		}

		if (has_translator)
		{
			outln("");
			outlncenter(get_lang()->translator);
			outln("");
			outlncenter(titdat.translator);
		}

		if (has_distributor)
		{
			outln("");
			outlncenter(get_lang()->distributor);
			outln("");
			outlncenter(titdat.distributor);
		}

		outln("");
		outln("");

		if (uses_tableofcontents)
		{
			sprintf(s1, "%s", get_lang()->contents);
			sprintf(s2, "{%s:%s}", get_lang()->contents, get_lang()->contents);
			strcpy(n, get_lang()->contents);
			strcenter(n, zDocParwidth);
			replace_once(n, s1, s2);
			outln(n);
		}

		outln("");
		break;

	case TOKPS:
		outln("/acty acty 50 sub def");
		outln("newline");

		if (has_title)
		{
			outln("14 changeFontSize");
			voutlnf("(%s) Center setAlign", titdat.title);
		}

		if (has_programimage)
		{
			c_begin_center();
			c_eps_output(titdat.programimage, "", FALSE);
			c_end_center();
		}

		if (has_program)
		{
			outln("22 changeFontSize");
			outln("newline");
			voutlnf("(%s) Center setAlign", titdat.program);
		}

		if (has_version)
		{
			outln("14 changeFontSize");
			outln("newline");
			voutlnf("(%s) Center setAlign", titdat.version);
		}

		if (has_date)
		{
			outln("newline");
			voutlnf("(%s) Center setAlign", titdat.date);
			outln("11 changeFontSize");
		}

		if (has_author || has_authorimage)
		{
			outln("currentpoint exch pop lowermargin 125 add lt");
			outln("{");
			outln("  /acty lowermargin 125 add def");
			outln("}");
			outln("{");
			outln("  /acty lowermargin 200 add def");
			outln("} ifelse");
			outln("newline");
			voutlnf("(%s) Center setAlign newline", get_lang()->by);
		}

		if (has_authorimage)
		{
			c_begin_center();
			c_eps_output(titdat.authorimage, "", FALSE);
			c_end_center();
		}

		if (has_author)
		{
			voutlnf("(%s) Center setAlign", titdat.author);
		}

		if (has_company)
		{
			outln("newline");
			voutlnf("(%s) Center setAlign newline", get_lang()->fur);
			voutlnf("(%s) Center setAlign", titdat.company);
		}

		if (has_address)
		{
			outln("newline");
			for (i = 1; i <= address_counter; i++)
			{
				if (titdat.address[i] != NULL)
				{
					voutlnf("(%s) Center setAlign newline", titdat.address[i]);
				}
			}
			outln("newline");
		}

		if (has_translator)
		{
			outln("newline");
			voutlnf("(%s) Center setAlign newline", get_lang()->translator);
			voutlnf("(%s) Center setAlign", titdat.translator);
		}

		if (has_distributor)
		{
			outln("newline");
			voutlnf("(%s) Center setAlign newline", get_lang()->distributor);
			voutlnf("(%s) Center setAlign", titdat.distributor);
		}

		c_newpage();
		outln("newline");
		break;
	}
}





/*******************************************************************************
*
*  pch_titlepage():
*     output title page for Pure C Help
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void pch_titlepage(void)
{
	int i;

	if (titdat.title != NULL)
	{
		outlncenter(titdat.title);
		outln("");
	}

	if (titdat.program != NULL)
	{
		outlncenter(titdat.program);
		outln("");
	}

	if (titdat.version != NULL)
	{
		outlncenter(titdat.version);
	}

	if (titdat.date != NULL)
	{
		outlncenter(titdat.date);
	}

	if (titdat.author != NULL)
	{
		outln("");
		outlncenter(get_lang()->by);
		outln("");
		outlncenter(titdat.author);
	}

	if (titdat.company != NULL)
	{
		outln("");
		outlncenter(get_lang()->fur);
		outln("");
		outlncenter(titdat.company);
	}

	if (address_counter > 0)
	{
		for (i = 1; i <= address_counter; i++)
		{
			if (titdat.address[i] != NULL)
			{
				outlncenter(titdat.address[i]);
			}
		}
	}

	if (titdat.translator != NULL)
	{
		outln("");
		outlncenter(get_lang()->translator);
		outln("");
		outlncenter(titdat.translator);
	}

	if (titdat.distributor != NULL)
	{
		outln("");
		outlncenter(get_lang()->distributor);
		outln("");
		outlncenter(titdat.distributor);
	}

	outln("");
}





/*******************************************************************************
*
*  init_titdat():
*     initialize this module (tp)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void init_titdat(void)
{
	int i;

	titdat.title = NULL;
	titdat.program = NULL;
	titdat.date = NULL;
	titdat.version = NULL;
	titdat.author = NULL;

	for (i = 0; i < MAXADDRESS; i++)
	{
		titdat.address[i] = NULL;
	}

	titdat.keywords = NULL;
	titdat.description = NULL;
	titdat.robots = NULL;
	titdat.company = NULL;
	titdat.category = NULL;
	titdat.htmltitle = NULL;
	titdat.domain_name = NULL;
	titdat.domain_link = NULL;
	titdat.contact_name = NULL;
	titdat.contact_link = NULL;
	titdat.programimage = NULL;
	titdat.appletitle = NULL;
	titdat.appleicon = NULL;
	titdat.authorimage = NULL;
	titdat.authoricon = NULL;
	titdat.authoricon_active = NULL;
	titdat.authoriconWidth = 0;
	titdat.authoriconHeight = 0;
	titdat.authoriconActiveWidth = 0;
	titdat.authoriconActiveHeight = 0;

	titdat.drc_statusline = NULL;
	titdat.stg_database = NULL;
	titdat.translator = NULL;
	titdat.distributor = NULL;
}





/*******************************************************************************
*
*  init_module_tp():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_tp(void)
{
	uses_maketitle = FALSE;
	called_maketitle = FALSE;
	address_counter = 0;

	titleprogram[0] = EOS;

	init_titdat();
	set_mainlayout();
}





/*******************************************************************************
*
*  init_module_tp_pass2():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void init_module_tp_pass2(void)
{
	titleprogram[0] = EOS;

	if (titdat.title != NULL)
	{
		strcat(titleprogram, titdat.title);
		strcat(titleprogram, " ");
	}

	if (titdat.program != NULL)
	{
		strcat(titleprogram, titdat.program);
	}

	del_whitespaces(titleprogram);
}





/*******************************************************************************
*
*  exit_module_tp():
*     reset all content of titdat.[]
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void exit_module_tp(void)
{
	int i;

	free_titdat(&(titdat.title));
	free_titdat(&(titdat.program));
	free_titdat(&(titdat.date));
	free_titdat(&(titdat.version));
	free_titdat(&(titdat.author));

	for (i = address_counter; i >= 1; i--)
	{
		free_titdat(&(titdat.address[i]));
	}

	free_titdat(&(titdat.keywords));
	free_titdat(&(titdat.description));
	free_titdat(&(titdat.company));
	free_titdat(&(titdat.category));
	free_titdat(&(titdat.htmltitle));
	free_titdat(&(titdat.domain_name));
	free_titdat(&(titdat.domain_link));
	free_titdat(&(titdat.contact_name));
	free_titdat(&(titdat.contact_link));
	free_titdat(&(titdat.programimage));
	free_titdat(&(titdat.authorimage));
	free_titdat(&(titdat.authoricon));
	free_titdat(&(titdat.authoricon_active));

	free_titdat(&(titdat.drc_statusline));
	free_titdat(&(titdat.stg_database));
	free_titdat(&(titdat.translator));
	free_titdat(&(titdat.distributor));
	free_titdat(&(titdat.robots));
	free_titdat(&(titdat.appletitle));
	free_titdat(&(titdat.appleicon));

	free_titdat(&(laydat.paper));
	free_titdat(&(laydat.propfontname));
	free_titdat(&(laydat.monofontname));
	free_titdat(&(laydat.pagemode));
	free_titdat(&(laydat.openpage));
	free_titdat(&(laydat.hidetoolbar));
	free_titdat(&(laydat.hidemenubar));
	free_titdat(&(laydat.viewerpreferences));
	free_titdat(&(laydat.fitwindow));
}
