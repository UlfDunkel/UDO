/*	############################################################
	# @(#) par.c
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
#ifndef ID_PAR_C
#define ID_PAR_C
const char *id_par_c= "@(#) par.c       19.07.1999";
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "portab.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "chr.h"
#include "file.h"
#include "msg.h"
#include "str.h"
#include "sty.h"
#include "toc.h"
#include "udo.h"
#include "img.h"

#include "export.h"
#include "par.h"
#include "udomem.h"


/*	############################################################
	# lokale Variablen
	############################################################	*/

#define	MAX_PARAMETERS	9

LOCAL char Param[MAX_PARAMETERS+1][1024];
LOCAL char Space[MAX_PARAMETERS+1][64];

LOCAL HYPHEN	*hyphen[MAXHYPHEN];	/* Array mit Zeigern auf Trennregeln	*/

LOCAL MACROS	*macros[MAXMACROS];	/* Array auf Zeiger mit Makros			*/

LOCAL DEFS		*defs[MAXDEFS];		/* Array auf Zeiger mit defines			*/

LOCAL PLACEHOLDER	phold[MAXPHOLDS+1];	/* Platzhalter	*/
LOCAL int			phold_counter;

LOCAL SPECCMD		speccmd[MAXSPECCMDS+1];	/* Platzhalter	*/
LOCAL int			speccmd_counter;

/*	############################################################
	# lokale Funktionen
	############################################################	*/

LOCAL void del_param_quotes (char *s);
LOCAL int get_nr_of_parameters ( const char *cmd, char *s );
LOCAL void reset_parameters ( void );
LOCAL int extract_parameters ( char *s, const char *cmd, const int count );
LOCAL int get_parameters ( char *s, const char *search, const int count );

LOCAL void adjust_params_inside ( char * s);

LOCAL BOOLEAN convert_link_lds ( char *s, const char *p0, char *p1, char *p2, const char *link );
LOCAL BOOLEAN convert_link_stg ( char *s, const char *p0, char *p1, char *p2, const char *link );
LOCAL BOOLEAN convert_link_pch ( char *s, const char *p0, char *p1, char *p2, const char *link );
LOCAL BOOLEAN convert_link_tex ( char *s, const char *p0, char *p1, char *p2 );
LOCAL BOOLEAN convert_link_pdf ( char *s, const char *p0, char *p1, char *p2, const char *link );
LOCAL BOOLEAN convert_link_lyx ( char *s, const char *p0, char *p1, char *p2 );
LOCAL BOOLEAN convert_link_tvh ( char *s, const char *p0, char *p1, char *p2 );
LOCAL BOOLEAN convert_link_info ( char *s, const char *p0, char *p1, char *p2, const char *link );
LOCAL BOOLEAN convert_link_ipf ( char *s, const char *p0, char *p1, char *p2, const char *link );
LOCAL BOOLEAN convert_link_etc ( char *s, const char *p0, char *p1, char *p2, const char *link );

LOCAL void c_link ( char *s, BOOLEAN inside_b4_macro );
LOCAL void c_url ( char *s, BOOLEAN inside_b4_macro );
LOCAL void c_xlink ( char *s, BOOLEAN inside_b4_macro );
LOCAL void c_ilink ( char *s, const BOOLEAN inside_b4_macro );
LOCAL void c_plink ( char *s, const BOOLEAN inside_b4_macro );
LOCAL void c_nolink ( char *s, const BOOLEAN inside_b4_macro );
LOCAL void c_comment ( char *s, const BOOLEAN inside_b4_macro );

LOCAL BOOLEAN c_index ( char *s, const BOOLEAN inside_b4_macro);
LOCAL BOOLEAN c_single_index ( char *s, const BOOLEAN inside_b4_macro);
LOCAL BOOLEAN c_double_index ( char *s, const BOOLEAN inside_b4_macro );
LOCAL BOOLEAN c_tripple_index ( char *s, const BOOLEAN inside_b4_macro );
LOCAL BOOLEAN c_quadruple_index ( char *s, const BOOLEAN inside_b4_macro );

LOCAL void c_internal_image ( char *s, const BOOLEAN inside_b4_macro );

LOCAL BOOLEAN c_single_raw ( char *s, const BOOLEAN inside_b4_macro );
LOCAL BOOLEAN c_double_raw ( char *s, const BOOLEAN inside_b4_macro );
LOCAL void c_internal_raw ( char *s, const BOOLEAN inside_b4_macro );

LOCAL BOOLEAN md_uses_parameters ( const char *s );



/*	############################################################
	#
	#	Parameter aus einem String extrahieren, der die
	#	Syntax (!command [text] [text] [text]) besitzt
	#	->	s:	eine komplette Zeile
	#		cmd:		das Kommando ohne "(!": link, plink, xlink
	#		Param[0]:	Kompletter Aufbau des Kommandos in der Zeile (original)
	#		Param[i]:	i. Parameter (global)
	#	<-	TRUE:	Korrekter Aufbau
	#		FALSE:	Fehlerhafter Aufbau oder Kommando nicht
	#				gefunden
	#
	############################################################	*/

LOCAL void del_param_quotes (char *s)
{
	qreplace_all(s, "!)", 2, ")", 1);
	qreplace_all(s, "!]", 2, "]", 1);
}


/*	------------------------------------------------------------
	Anzahl der Parameter eines Kommandos ermitteln, das so
	aufgebaut ist: (!command [p1] [p2] [...])
	------------------------------------------------------------	*/
LOCAL int get_nr_of_parameters ( const char *cmd, char *s )
{
	int count= 0;
	char *pos;
	char search[128];
	
	sprintf(search, "(!%s", cmd);
		
	if ( (pos=strstr(s, search))==NULL )
	{	return 0;
	}

	pos+= strlen(search);
	
	/* Die erste geschlossene Klammer suchen, vor der kein ! steht */

	while( pos[0]!=')' || (pos[0]==')' && pos[-1]=='!') )
	{	switch(pos[0])
		{	case EOS:
				error_unexpected_eol();
				return 0;
			case ']':
				if (pos[-1]!='!')
				{	count++;
				}
				break;
		}
		pos++;
	}
	
	return count;
	
}	/* get_nr_of_parameters */


LOCAL void reset_parameters ( void )
{
	int i;
	
	for (i=0; i<MAX_PARAMETERS; Param[i++][0]= EOS) ;
	for (i=0; i<MAX_PARAMETERS; Space[i++][0]= EOS) ;

}	/* reset_parameters */



LOCAL int extract_parameters ( char *s, const char *cmd, const int count )
{
	int i;
	char *pos, search[128];

	sprintf(search, "(!%s", cmd);	/* PL3 */
	
	if ( (pos=strstr(s, search))==NULL )
	{	return 0;
	}

	reset_parameters();

	pos+= strlen(search);

	i= 0;

	while (i<count)		
	{	/* Anfang "[" des Parameters bestimmen		*/
		/* und die Zeichen ermitteln, die bis dahin	*/
		/* im Quelltext auftauchen					*/
		while( (pos[0]!='[') && (pos[0]!=EOS) )
		{	chrcat(Space[i], pos[0]);
			pos++;
		}
		if (pos[0]==EOS)
		{	error_unexpected_eol();
			return 0;
		}

		/* Pointer auf erstes Zeichen des Parameters setzen */
		/* und bis zur naechsten Klammer lesen, die nicht	*/
		/* duch ein Ausrufungszeichen gequotet ist.			*/
		pos++;

		while( (pos[0]!=']' || (pos[0]==']' && pos[-1]=='!')) && (pos[0]!=EOS) )
		{	chrcat(Param[i+1], pos[0]);
			pos++;
		}
		
		if (pos[0]==EOS)
		{	error_unexpected_eol();
			return 0;
		}
	
		pos++;
		i++;
	}

	/* Zeichen lesen, die bis zum Ende des Kommandos auftauchen */
	
#if 1
	while( (pos[0]!=')') && (pos[0]!=EOS) )
	{	chrcat(Space[count], pos[0]);
		pos++;
	}
#else
	while( (pos[0]!=')') && (pos[0]!=EOS) )
	{	chrcat(Space[count+1], pos[0]);
		pos++;
	}
#endif

	if (pos[0]==EOS)
	{	error_unexpected_eol();
		return 0;
	}

	return i ;	/* PL14: Anzahl der Parameter statt BOOLEAN */
}	/* extract_parameters */


LOCAL int get_parameters ( char *s, const char *search, const int count )
{
	int i, params;
	
	params=extract_parameters(s, search, count);
	
	if (params==0)
	{	return 0;
	}

#if 0
	if (params!=count)
	{	error "was nun?"
	}
#endif

	sprintf(Param[0], "(!%s%s", search, Space[0]);
	
	if (params>0)
	{	for(i=1; i<=params; i++)
		{	strcat(Param[0], "[");
			strcat(Param[0], Param[i]);
			strcat(Param[0], "]");
			strcat(Param[0], Space[i]);
			del_param_quotes(Param[i]);	
		}
	}
	
	strcat(Param[0], ")");

	return params;		/* PL14: Anzahl der Parameter statt BOOLEAN */
}	/* get_parameters */



/*	------------------------------------------------------------
	Diese Funktion dient zur Anpassung von Makros und Definitionen,
	die Variablen enthalten. Beispiel:

	!macro Maus (!1) (!2) @ (!3), (!1)_(!2)@(!3).maus.de
	MausNet:	(!Maus [Dirk] [Hagedorn] [MK2])

	cmd   =	Maus
	entry =	(!1) (!2) @ (!3), (!1)_(!2)@(!3).maus.de
	s     =	Der String mit dem Makro

	---->

	MausNet: Dirk Hagedorn @ MK2, Dirk_Hagedorn@MK2.maus.de
	------------------------------------------------------------	*/
GLOBAL void replace_variables ( char *s, const char *cmd, const char *entry)
{
	int parms, i;
	char p[16], without[128], *ptr;
	BOOLEAN flag;

	/* PL10: (!macro) vorher loeschen */
	sprintf(without, "(!%s)", cmd);
	delete_all(s, without);

	flag = TRUE;
	while ( flag && (parms= get_nr_of_parameters(cmd, s))>0 )
	{
		if (parms>MAX_PARAMETERS)
		{	error_too_many_parameters();
			return;
		}	

		get_parameters(s, cmd, parms);

		/* r6pl2: ptr statt s benutzen, damit die Parameter nur ab */
		/* der Stelle des/r Makros/Definition ersetzt werden und */
		/* nicht bereits davor. */
		/* Trotzdem werden auch (!1) etc. ersetzt, die nach den */
		/* Parameter-Befehle stehen. Dies wuerde aber einen */
		/* unheimlichen Umstand bedeuten (Ausschneiden, Ersetzen, */
		/* wieder Einfuegen: fuer jedes etwaige vorhandene Makro) */
		/* Da aber (!0) ... (!9) eh verboten sind, wird hier keine */
		/* Ruecksicht auf die Pappenheimer genommen, die UDO-Befehle */
		/* nicht quoten wollen, wie z.B. mit (!/0), (!/1) etc. */

		ptr= strstr(s, Param[0]);

		if ( replace_all(ptr, Param[0], entry) )	/* r6pl2: ptr statt s */
		{
			qdelete_all(ptr, "(!0)", 4);	/* r6pl2 */
			for (i=0; i<MAX_PARAMETERS; i++)
			{
				sprintf(p, "(!%d)", i+1);
				if (parms>i)
				{	auto_quote_chars(Param[i+1], TRUE);		/* <???> */
					replace_all(ptr, p, Param[i+1]);
				}
				else
				{
					qdelete_all(ptr, p, 4);
				}
			}
		}
		else
		{	flag= FALSE;
		}
	}

	if (!flag)
	{	sprintf(without, "!%s", cmd);
		error_replace_param(without);
	}

}	/* replace_variables */



/*	############################################################
	#
	# Spezielle Formatbefehle als Platzhalter im Text einbauen
	# Die Formatbefehle enthalten keinen sichtbaren Text!
	#
	############################################################	*/
GLOBAL void reset_speccmds ( void )
{
	int i;

	if (speccmd_counter>=0)
	{
		for (i=0; i<speccmd_counter; i++)
		{
			if ( speccmd[i].entry!=NULL )
			{	um_free(speccmd[i].entry);
				speccmd[i].entry= NULL;
			}
			
			speccmd[i].magic[0]= EOS;
		}
	}

	speccmd_counter= -1;

}	/* reset_speccmds */



GLOBAL BOOLEAN add_speccmd ( char *entry )
{
	size_t	sl;
	char	*ptr;
	
	if (speccmd_counter<MAXSPECCMDS)
	{
		speccmd_counter++;

		sl= strlen(entry);
		ptr= (char *) ( um_malloc(sl*sizeof(char)+1) );
		if (ptr==NULL)
		{	error_malloc_failed();
			speccmd_counter--;
			return FALSE;
		}
		
		if (speccmd_counter+OFFSET_SPECCMD==(int) '~')
		{	speccmd_counter++;
		}
		if (speccmd_counter+OFFSET_SPECCMD==(int) '\177')
		{	speccmd_counter++;
		}

		sprintf(speccmd[speccmd_counter].magic, "\033%c%c\033",
			C_SPECCMD_MAGIC, speccmd_counter+OFFSET_SPECCMD);
		
		
		speccmd[speccmd_counter].entry= ptr;
		
		strcpy(speccmd[speccmd_counter].entry, entry);

		return TRUE;
	}
	
	return FALSE;
}	/* add_speccmd */



GLOBAL BOOLEAN insert_speccmd ( char *s, const char *rep, char *entry )
{
	if ( add_speccmd(entry) )
	{	if ( replace_once(s, rep, speccmd[speccmd_counter].magic) )
		{	return TRUE;
		}
	}
	
	return FALSE;
}


GLOBAL void replace_speccmds ( char *s )
{
	register int i;
	int replaced= -1;

	if (speccmd_counter>=0)
	{
		if ( strstr(s, ESC_SPECCMD_MAGIC)==NULL)
		{	return;
		}	

#if 1
		/* PL10: Rueckwaerts ersetzen, da ein Platzhalter auch in	*/
		/* einem Platzhalter stecken kann!							*/
		for (i=speccmd_counter; i>=0; i--)
#else
		for (i=0; i<=speccmd_counter; i++)
#endif
		{	if ( replace_once(s, speccmd[i].magic, speccmd[i].entry) )
			{	speccmd[i].magic[0]= EOS;
				replaced++;
			}
		}
		if (replaced==speccmd_counter)
		{	reset_speccmds();
		}
	}

}	/* replace_speccmds */




/*	############################################################
	#
	# Links und andere interne Kommandos bearbeiten, was
	# VOR dem Tokenisieren passieren muss!
	# Aufbau: (!link [text] [destination])
	#
	############################################################	*/
GLOBAL void reset_placeholders ( void )
{
	int i;

	if (phold_counter>=0)
	{
		for (i=0; i<phold_counter; i++)
		{
			if ( phold[i].entry!=NULL )
			{	um_free(phold[i].entry);
				phold[i].entry= NULL;
			}
			
			if ( phold[i].text!=NULL )
			{	um_free(phold[i].text);
				phold[i].text= NULL;
			}
			
			phold[i].magic[0]= EOS;
		}
	}

	phold_counter= -1;

}	/* reset_placeholders */



GLOBAL BOOLEAN add_placeholder ( char *entry, char *rawtext )
{
	size_t	el, tl;
	char	*eptr, *tptr;
	
	if (phold_counter<MAXPHOLDS)
	{
		phold_counter++;

		el= strlen(entry);
		eptr= (char *) ( um_malloc(el*sizeof(char)+1) );
		if (eptr==NULL)
		{	error_malloc_failed();
			phold_counter--;
			return FALSE;
		}
		
		tl= strlen(rawtext);
		tptr= (char *) ( um_malloc (tl*sizeof(char)+1) );
		if (tptr==NULL)
		{	error_malloc_failed();
			um_free(eptr);
			phold_counter--;
			return FALSE;
		}

		if (phold_counter+OFFSET_PHOLD==(int) '~')		/* PL8 */
		{	phold_counter++;
		}
		if (phold_counter+OFFSET_PHOLD==(int) '\177')	/* PL8 */
		{	phold_counter++;
		}

		sprintf(phold[phold_counter].magic, "\033%c%c\033",
			C_PHOLD_MAGIC, phold_counter+OFFSET_PHOLD);
		
		
		phold[phold_counter].entry= eptr;
		phold[phold_counter].text= tptr;
		
		strcpy(phold[phold_counter].entry, entry);
		strcpy(phold[phold_counter].text, rawtext);

		return TRUE;
	}
	
	return FALSE;
}	/* add_placeholder */



GLOBAL BOOLEAN insert_placeholder ( char *s, const char *rep, char *entry, char *rawtext )
{
	if ( add_placeholder(entry, rawtext) )
	{	if ( replace_once(s, rep, phold[phold_counter].magic) )
		{	return TRUE;
		}
	}
	
	return FALSE;
}


GLOBAL void replace_placeholders ( char *s )
{
	register int i;
	int replaced= -1;

	if (phold_counter>=0)
	{
		if ( strstr(s, ESC_PHOLD_MAGIC)==NULL)
		{	return;
		}	

		/* PL10: Rueckwaerts ersetzen, da ein Platzhalter auch in	*/
		/* einem Platzhalter stecken kann!							*/
		for (i=phold_counter; i>=0; i--)
		{	if ( replace_once(s, phold[i].magic, phold[i].entry) )
			{	phold[i].magic[0]= EOS;
				replaced++;
			}
		}
		if (replaced==phold_counter)
		{	reset_placeholders();
		}
	}

}	/* replace_placeholders */


GLOBAL void replace_placeholders_text ( char *s )
{
	register int i;

	if (phold_counter>=0)
	{
		if ( strstr(s, ESC_PHOLD_MAGIC)==NULL)
		{	return;
		}	

		for (i=0; i<=phold_counter; i++)
		{	replace_once(s, phold[i].magic, phold[i].text);
		}
	}
}	/* replace_placeholders_text */


GLOBAL size_t pholdlen ( int i )
{
	if ( i>=0 && i<=MAXPHOLDS )
	{
		if ( phold[i].text!= NULL )
		{
			return(strlen(phold[i].text));
		}
	}
	
	return 0;
}	/* pholdlen */




LOCAL void adjust_params_inside ( char * s)
{
	replace_macros(s);
	c_divis(s);
	c_vars(s);
	c_styles(s);
}


LOCAL BOOLEAN convert_link_lds ( char *s, const char *p0, char *p1, char *p2, const char *link )
{
	char s_entry[1024], old_entry[1024];
	char *ptr;
	BOOLEAN flag;
	
	strcpy(s_entry, p2);
	c_tilde(s_entry);
	replace_udo_quotes(s_entry);

	convert_tilde(p1);
	convert_tilde(p2);
	replace_udo_quotes(p1);
	replace_udo_quotes(p2);
	strcpy(old_entry, p2);

	auto_references(s_entry, TRUE, "", 0, 0);		/* auch Links innerhalb der Seite ermoeglichen */
	/* Trick: Schauen, ob nun "> im Eintrag steht und dann */
	/* ab dort den Link einsetzen. */
	flag= FALSE;
	if ( (ptr=strstr(s_entry, "name=\"")) != NULL )
	{	flag= replace_once(ptr, old_entry, p1);
	}

	if (!flag)
	{	error_undefined_link(link);
		strcpy(s_entry, p1);	/* PL9 */
	}
	
	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return TRUE;
	}

	return FALSE;
}	/* convert_link_lds */


LOCAL BOOLEAN convert_link_stg ( char *s, const char *p0, char *p1, char *p2, const char *link )
{
	char nodename[256], s_entry[256];
	int ti, li;
	BOOLEAN isnode;
	BOOLEAN flag;

	c_tilde(p2);
	replace_udo_quotes(p2);
	
	flag= is_node_link(p2, nodename, &ti, &isnode, &li);

	replace_udo_tilde(p2);
	replace_udo_nbsp(p2);

	convert_tilde(p1);
	replace_udo_quotes(p1);

 	if (flag)
	{
		node2stg(p1);
		node2stg(p2);
		
		replace_2at_by_1at(p1);			/*r6pl2*/
		replace_2at_by_1at(p2);			/*r6pl2*/
		replace_2at_by_1at(nodename);	/*r6pl2*/

		/* r6pl15: links auf gleiche node mag ST-Guide nicht */
		if (isnode && is_current_node(ti))
		{
			strcpy(s_entry, p1);
		} else
		{
			if (!isnode)
			{	/* PL9: Links auf Labels sind etwas besonderes */
				sprintf(s_entry, "@{\"%s\" link \"%s\" \"%s\"}",
					p1, nodename, p2);
			}
			else
			{	sprintf(s_entry, "@{\"%s\" link \"%s\"}",
							p1, p2);
			}
		}
	}


	if (!flag)
	{	/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}
	
	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return TRUE;
	}

	return FALSE;

}	/* convert_link_stg */



LOCAL BOOLEAN convert_link_pch ( char *s, const char *p0, char *p1, char *p2, const char *link )
{
	char nodename[256], s_entry[256];
	int ti, li;
	BOOLEAN isnode;
	BOOLEAN flag;

	c_tilde(p2);
	replace_udo_quotes(p2);
	
	flag= is_node_link(p2, nodename, &ti, &isnode, &li);

	replace_udo_tilde(p2);
	replace_udo_nbsp(p2);

	convert_tilde(p1);
	replace_udo_quotes(p1);

	if (flag)
	{	node2pchelp(p2);
		sprintf(s_entry, "\\link(\"%s\")%s\\#", p2, p1);
	}
	else
	{	/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}
	
	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return TRUE;
	}

	return FALSE;

}	/* convert_link_pch */



LOCAL BOOLEAN convert_link_tex ( char *s, const char *p0, char *p1, char *p2 )
{
	char s_entry[1024];
	int li, ti;
	BOOLEAN isnode;
	char nodename[256];
	
	convert_tilde(p1);
	convert_tilde(p2);
	replace_udo_quotes(p1);
	replace_udo_quotes(p2);
	label2tex(p2);
	
	is_node_link(p2, nodename, &ti, &isnode, &li);

	sprintf(s_entry, "%s (%s \\ref{%s})", p1, lang.see, p2);

	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return TRUE;
	}

	return FALSE;
}	/* convert_link_tex */


LOCAL BOOLEAN convert_link_pdf ( char *s, const char *p0, char *p1, char *p2, const char *link )
{
	char nodename[256], s_entry[256];
	int ti, li, dest;
	BOOLEAN isnode;
	BOOLEAN flag;

	c_tilde(p2);
	replace_udo_quotes(p2);
	
	flag= is_node_link(p2, nodename, &ti, &isnode, &li);

	convert_tilde(p1);
	replace_udo_quotes(p1);

	if (flag)
	{	if (isnode)
		{	dest= ti;
		}
		else
		{	dest= li;
		}
		/* Changed in r6.2pl1 [NHz] */
		sprintf(s_entry, "{\\pdfstartlink goto num %d\n%s\\pdfendlink}",
			dest, p1);
	}
	else
	{	/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}
	
	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return TRUE;
	}

	return FALSE;
}	/* convert_link_pdf */


LOCAL BOOLEAN convert_link_lyx ( char *s, const char *p0, char *p1, char *p2 )
{
	char s_entry[1024];
	int li, ti;
	BOOLEAN isnode;
	char nodename[256];
	
	is_node_link(p2, nodename, &ti, &isnode, &li);

	sprintf(s_entry,
		"%s (%s \n\\begin_inset LatexDel \\ref{%s}\n\n\\end_inset\n\n)",
		p1, lang.see, p2);
		
	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return TRUE;
	}
	
	return FALSE;
}


LOCAL BOOLEAN convert_link_tvh ( char *s, const char *p0, char *p1, char *p2 )
{
	char s_entry[1024];
	int li, ti;
	BOOLEAN isnode;
	char nodename[256];
	
	is_node_link(p2, nodename, &ti, &isnode, &li);

	node2vision(p2);
	sprintf(s_entry, "{%s:%s}", p1, p2);

	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return TRUE;
	}
	
	return FALSE;
}	/* convert_link_tvh */


LOCAL BOOLEAN convert_link_info ( char *s, const char *p0, char *p1, char *p2, const char *link )
{
	char nodename[256], s_entry[256];
	int ti, li;
	BOOLEAN isnode;
	BOOLEAN flag;

	c_tilde(p2);
	replace_udo_quotes(p2);
	
	flag= is_node_link(p2, nodename, &ti, &isnode, &li);

	convert_tilde(p1);
	replace_udo_quotes(p1);

	replace_udo_tilde(p2);
	replace_udo_nbsp(p2);
	node2texinfo(p2);

	if (flag)
	{
		if (isnode)
		{	strcpy(nodename, p2);
		}
		else
		{	node2texinfo(nodename);
		}

		sprintf(s_entry, "%s (@xref{%s})", p1, nodename);
	}
	else
	{	/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}
	
	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return TRUE;
	}

	return FALSE;

}	/* convert_link_info */


LOCAL BOOLEAN convert_link_ipf ( char *s, const char *p0, char *p1, char *p2, const char *link )
{
	char nodename[256], s_entry[256], s_id[256];
	int ti, li;
	BOOLEAN isnode;
	BOOLEAN flag;

	c_tilde(p2);
	replace_udo_quotes(p2);
	
	flag= is_node_link(p2, nodename, &ti, &isnode, &li);

	convert_tilde(p1);
	replace_udo_quotes(p1);

	if (flag)
	{	getLabelIndexFromTocIndex(&li, ti);
		node2NrIPF(s_id, li);
		sprintf(s_entry, ":link reftype=hd refid=%s.%s:elink.", s_id, p1);
	}
	else
	{	/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}
	
	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return TRUE;
	}

	return FALSE;

}	/* convert_link_ipf */


/* New in r6pl15 [NHz] */
LOCAL BOOLEAN convert_link_ps ( char *s, const char *p0, char *p1, char *p2, const char *link )
{
	char nodename[256], s_entry[256];
	int ti, li;
	BOOLEAN isnode;
	BOOLEAN flag;

	/* Internal Link for Postscript */
	flag= is_node_link(p2, nodename, &ti, &isnode, &li);


	convert_tilde(p1);
	if (flag)
	{	if (p2[0]==EOS)
		{	strcpy(p2, Param[1]);
		}
		replace_udo_quotes(p2);	/* r6pl2 */
		replace_udo_quotes(p1);	/* r6pl2 */
		sprintf(s_entry, ") udoshow (%s) /%s 0 255 0 Link (", p1, p2);
	}

	else

	{	/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}

	

	if ( insert_placeholder(s, p0, s_entry, p1) )
	{	return(TRUE);
	}

	return FALSE;

}	/* convert_link_ps */


LOCAL BOOLEAN convert_link_etc ( char *s, const char *p0, char *p1, char *p2, const char *link )
{
	char nodename[256], s_entry[256];
	char lq[16], rq[16];
	int ti, li;
	BOOLEAN isnode;
	BOOLEAN flag;

	c_tilde(p2);
	replace_udo_quotes(p2);
	
	flag= is_node_link(p2, nodename, &ti, &isnode, &li);

	replace_udo_tilde(p2);
	replace_udo_nbsp(p2);

	/* Deleted in r6.2pl1 [NHz] / Bug #00000030 */
	/* 	convert_tilde(p1); */
	replace_udo_quotes(p1);

	if (flag)
	{
		if (no_links)
		{	/* r6pl6: Links unterdruecken */
			strcpy(s_entry, p1);
		}
		else
		{	if (desttype==TORTF)	/*r6pl6: die richtigen benutzen */
			{	strcpy(lq, "\\ldblquote");
				strcpy(rq, "\\rdblquote");
			}
			else
			{	strcpy(lq, "\"");
				strcpy(rq, "\"");
			}

			if (!isnode)
			{	/* PL9: Links auf Labels sind etwas besonderes */
				sprintf(s_entry, "%s (%s %s%s%s)", p1, lang.see, lq, nodename, rq);
			}
			else
			{	sprintf(s_entry, "%s (%s %s%s%s)", p1, lang.see, lq, p2, rq);
			}
		}
	}


	if (!flag)
	{	/* Node, Alias oder Label nicht definiert */
		error_undefined_link(link);
		strcpy(s_entry, p1);
	}
	
	if ( replace_once(s, p0, s_entry) )
	{	return TRUE;
	}

	return FALSE;
	
}	/* convert_link_etc */



LOCAL void c_link ( char *s, BOOLEAN inside_b4_macro )
{
	int pnr=0;
	char s_entry[1024], old_entry[1024], link[1024];
	char *ptr;
	BOOLEAN linkerror;
	BOOLEAN flag;
	BOOLEAN	old_autorefoff;

	old_autorefoff= bDocAutorefOff;
	bDocAutorefOff= FALSE;
	
	linkerror = FALSE;
	while ( !linkerror && ((pnr=get_parameters(s, "link", 2))==2) )
	{
		strcpy(link, Param[2]);
		del_whitespaces(Param[1]);
		del_whitespaces(Param[2]);


		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);	
				auto_quote_chars(Param[2], TRUE);
			}
		
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		switch(desttype)
		{
			case TOHTM:
			case TOMHH:
				strcpy(s_entry, Param[2]);
				c_tilde(s_entry);
				replace_udo_quotes(s_entry);

				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				strcpy(old_entry, Param[2]);

				auto_references(s_entry, TRUE, "", 0, 0);		/* auch Links innerhalb der Seite ermoeglichen */

				/* Trick: Schauen, ob nun "> im Eintrag steht und dann */
				/* ab dort den Link einsetzen. */
				flag= FALSE;
				if ( (ptr=strstr(s_entry, "\">")) != NULL )
				{	flag= replace_once(ptr, old_entry, Param[1]);
				}

				if (!flag)
				{	error_undefined_link(link);
					strcpy(s_entry, Param[1]);	/* PL9 */
				}
				
				linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
				break;

			case TOWIN:	/* 0.41 */
			case TOWH4:
			case TOAQV:
				strcpy(s_entry, Param[2]);
				c_tilde(s_entry);
				replace_udo_quotes(s_entry);

				convert_tilde(Param[1]);
				convert_tilde(Param[2]);
				replace_udo_quotes(Param[1]);
				replace_udo_quotes(Param[2]);
				strcpy(old_entry, Param[2]);

				auto_references(s_entry, TRUE, "", 0, 0);		/* auch Links innerhalb der Seite ermoeglichen */

				/* Trick: Schauen, ob nun {\uldb im Eintrag steht und dann */
				/* ab dort den Link einsetzen. */
				flag= FALSE;

				ptr=strstr(s_entry, "{\\uldb");
				
				if ( ptr==NULL )	/* PL8: Links auf Popups erlauben */
				{	ptr=strstr(s_entry, "{\\ul");
				}

				if ( ptr != NULL )
				{	flag= replace_once(ptr, old_entry, Param[1]);
				}
				
				if (!flag)
				{	error_undefined_link(link);
					strcpy(s_entry, Param[1]);	/* PL9 */
				}
				
				linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
				break;
			case TOLDS:
				linkerror= !convert_link_lds(s, Param[0], Param[1], Param[2], link);
				break;
			case TOSTG:
			case TOAMG:
				linkerror= !convert_link_stg(s, Param[0], Param[1], Param[2], link);
				break;
			case TOTEX:
				linkerror= !convert_link_tex(s, Param[0], Param[1], Param[2]);
				break;
			case TOPDL:
				linkerror= !convert_link_pdf(s, Param[0], Param[1], Param[2], link);
				break;
			case TOLYX:
				linkerror= !convert_link_lyx(s, Param[0], Param[1], Param[2]);
				break;
			case TOTVH:
				linkerror= !convert_link_tvh(s, Param[0], Param[1], Param[2]);
				break;
			case TOPCH:	/* PL9 */
				linkerror= !convert_link_pch(s, Param[0], Param[1], Param[2], link);
				break;
			case TOINF:
				linkerror= !convert_link_info(s, Param[0], Param[1], Param[2], link);
				break;
			case TOIPF:
				linkerror= !convert_link_ipf(s, Param[0], Param[1], Param[2], link);
				break;

			/* New in r6pl15 [NHz] */
			/* Internal Link for Postscript */
			case TOKPS:
				linkerror= !convert_link_ps(s, Param[0], Param[1], Param[2], link);
				break;

			default:
				linkerror= !convert_link_etc(s, Param[0], Param[1], Param[2], link);
				break;
		}
	}
	
	if (linkerror)
	{	replace_once(s, Param[0], Param[1]);
		error_replace_param("!link");
	}
	
	if (pnr!=0 && pnr!=2)
	{	error_wrong_nr_parameters("!link");
	}

	bDocAutorefOff= old_autorefoff;
}	/*c_link*/


LOCAL void c_url ( char *s, BOOLEAN inside_b4_macro )
{
	int pnr=0, url_len, i;
	/* Changed in r6pl17 [NHz] / s_entry (1024 to 4096 bytes), url_rtf (512 to 2048 bytes) */
	char s_entry[4096], url_rtf[2048], rtf0[4];

	char rtf1[]="00d0c9ea79f9bace118c8200aa004ba90b0200000003000000";
	char rtf2[]="e0c9ea79f9bace118c8200aa004ba90b";
	char rtf3[]="000000";
	char rtf4[]="0000";
	BOOLEAN linkerror= FALSE;

	while ( !linkerror && ((pnr=get_parameters(s, "url", 2))==2) )
	{
		del_whitespaces(Param[1]);	/* PL9 */

		/* Wird ein leerer Parameter benutzt, den	*/
		/* den ersten auch als zweiten verwenden.	*/
		if (Param[2][0]==EOS)
		{	strcpy(Param[2], Param[1]);
		}

		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);
			}

			adjust_params_inside(Param[1]);
		}
		
		if (no_urls)
		{	replace_all(s, Param[0], Param[1]);
		}
		else
		{
 			switch(desttype)
 			{
 				case TOHTM:
				case TOMHH:
 					convert_tilde(Param[1]);
					if (Param[2][0]==EOS)
					{	strcpy(Param[2], Param[1]);
					}
					replace_udo_quotes(Param[2]);	/* r6pl2 */
					replace_udo_quotes(Param[1]);	/* r6pl2 */
					if (html_frames_layout)
					{	sprintf(s_entry, "<a href=\"%s\" target=\"_top\">%s</a>", Param[2], Param[1]);
					}
					else
					{	sprintf(s_entry, "<a href=\"%s\">%s</a>", Param[2], Param[1]);
					}
 					linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
 					break;

					/* New in r6pl15 [NHz] */
					/* Weblink for Postscript/PDF */
				case TOKPS:
  				convert_tilde(Param[1]);
					if (Param[2][0]==EOS)
					{	strcpy(Param[2], Param[1]);
					}
					replace_udo_quotes(Param[2]);
					replace_udo_quotes(Param[1]);
					sprintf(s_entry, ") udoshow (%s) (%s) 0 0 255 WebLink (", Param[1], Param[2]);
   				linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
					break;

					/* New in r6pl15 [NHz] */
					/* Weblink for WinHelp */
				case TOWIN:

				case TOWH4:
  				convert_tilde(Param[1]);
					if (Param[2][0]==EOS)
					{	strcpy(Param[2], Param[1]);
					}
					replace_udo_quotes(Param[2]);
					replace_udo_quotes(Param[1]);
					sprintf(s_entry, "{\\ul (%s)}{\\v !ExecFile((%s))}", Param[1], Param[2]);
   				linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
					break;

					/* New in r6pl15 [NHz] */
					/* Weblink for Richtext Format */
				case TORTF:
  				convert_tilde(Param[1]);

					/* New in r6.2pl1 [NHz] / Bug #00000029 */
					c_rtf_quotes(Param[1]);

					if (Param[2][0]==EOS)
					{	strcpy(Param[2], Param[1]);
					}
					replace_udo_quotes(Param[2]);
					replace_udo_quotes(Param[1]);

					/* Changed in r6.2pl1 [NHz] */ 					auto_quote_chars(Param[2], TRUE); 					url_len = (int)strlen(Param[2]);

					rtf0[0]=EOS;
					url_rtf[0]=EOS;

					for(i=0;i<url_len;i++)
					{	if(Param[2][i] == '\\') 						{	i += 2;
							rtf0[0]=EOS;
							strncpy(rtf0, Param[2]+i, 2);
							i++; 						} 						else 							sprintf(rtf0, "%x", (int)Param[2][i]); 
						strcat(url_rtf, rtf0);
						strcat(url_rtf, "00");
					}

					sprintf(s_entry, "{\\field{\\*\\fldinst {HYPERLINK \"%s\"}{{\\*\\datafield %s%s%x%s%s%s}}}\n{\\fldrslt {\\cs15\\ul\\cf2 %s}}}", Param[2], rtf1, rtf2, (url_len+1)*2, rtf3, url_rtf, rtf4, Param[1]);

   				linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
					break;

   			default:
   				convert_tilde(Param[1]);
					replace_udo_quotes(Param[1]);	/* r6pl2 */
					replace_udo_quotes(Param[2]);	/* r6pl2 */
					linkerror= !insert_placeholder(s, Param[0], Param[1], Param[1]);
 					break;
   			}	/*switch*/
   		}	/* if (no_urls) */

	}	/* while */

	if (linkerror)
	{	replace_once(s, Param[0], Param[1]);
		error_replace_param("!url");
	}

	if (pnr!=0 && pnr!=2)
	{	error_wrong_nr_parameters("!url");
	}

}	/*c_url*/


LOCAL void c_xlink ( char *s, BOOLEAN inside_b4_macro )
{
	int pnr=0;
	char s_entry[1024];
	char wnode[1024], wfile[1024], *ptr;
	BOOLEAN linkerror= FALSE;

	while ( !linkerror && ((pnr=get_parameters(s, "xlink", 2))==2) )
	{
		del_whitespaces(Param[1]);	/* PL9 */

		/* PL6: Wird ein leerer Parameter benutzt, den	*/
		/* den ersten auch als zweiten verwenden.		*/
		if (Param[2][0]==EOS && desttype!=TOHTM && desttype!=TOMHH)
		{	strcpy(Param[2], Param[1]);
		}


		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);
			}

			adjust_params_inside(Param[1]);
		}
		
		if (no_xlinks)
		{	replace_all(s, Param[0], Param[1]);
		}
		else
		{
   			switch(desttype)
   			{
				case TOSTG:
				case TOAMG:
   					convert_tilde(Param[1]);
   					convert_tilde(Param[2]);
   					replace_2at_by_1at(Param[2]);
   					replace_2at_by_1at(Param[1]);
					replace_udo_quotes(Param[2]);	/* r6pl2 */
					replace_udo_quotes(Param[1]);	/* r6pl2 */
   					node2stg(Param[2]);
   					node2stg(Param[1]);
   					sprintf(s_entry, "@{\"%s\" link \"%s\"}", Param[1], Param[2]);
   					
   					linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
   					break;
   				case TOHTM:
				case TOMHH:
   					convert_tilde(Param[1]);
					if (Param[2][0]==EOS)
					{	strcpy(Param[2], Param[1]);
					}
					replace_udo_quotes(Param[2]);	/* r6pl2 */
					replace_udo_quotes(Param[1]);	/* r6pl2 */
					if (html_frames_layout)
					{	sprintf(s_entry, "<a href=\"%s\" target=\"_top\">%s</a>", Param[2], Param[1]);
					}
					else
					{	sprintf(s_entry, "<a href=\"%s\">%s</a>", Param[2], Param[1]);
					}
   					linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
   					break;
   				case TOLDS:
   					convert_tilde(Param[1]);
   					convert_tilde(Param[2]);
					replace_udo_quotes(Param[1]);	/* r6pl2 */
					replace_udo_quotes(Param[2]);	/* r6pl2 */
   					sprintf(s_entry, "<htmlurl url=\"%s\" name=\"%s\">", Param[2], Param[1]);
   					linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
   					break;
   				case TOPCH:
   					convert_tilde(Param[1]);
   					convert_tilde(Param[2]);
					replace_udo_quotes(Param[1]);	/* r6pl2 */
					replace_udo_quotes(Param[2]);	/* r6pl2 */
   					sprintf(s_entry, "\\#%s\\#", Param[1]);
   					linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
   					break;
   				case TOWIN:
				case TOWH4:
   				case TOAQV:
   					/* PL8: Der erste Teil muss auch angepasst werden */
   					convert_tilde(Param[1]);
   					convert_tilde(Param[2]);
					replace_udo_quotes(Param[1]);	/* r6pl2 */
					replace_udo_quotes(Param[2]);	/* r6pl2 */
   					ptr= strchr(Param[2], '@');
   					if (ptr!=NULL)
	   				{	ptr[0]= EOS;
	   					strcpy(wnode, Param[2]);
	   					strcpy(wfile, ptr+1);
	   					if (wnode[0]!=EOS && wfile[0]!=EOS)
	   					{	node2winhelp(wnode);
		   					sprintf(s_entry, "{\\uldb %s}{\\v %s@%s}", Param[1], wnode, wfile);
		   					linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
	   					}
	   					else
	   					{	if (wnode[0]!=EOS)
	   						{	error_xlink_win_topic();
			   					linkerror= !replace_once(s, Param[0], Param[1]);
	   						}
	   						if (wfile[0]!=EOS)
	   						{	error_xlink_win_file();
			   					linkerror= !replace_once(s, Param[0], Param[1]);
	   						}
	   					}
	   				}
	   				else
	   				{	error_xlink_win_syntax();
	   					linkerror= !replace_once(s, Param[0], Param[1]);
	   				}
  					break;

					/* New in r6pl15 [NHz] */
					/* Filelink for Postscript */
					case TOKPS:
   					convert_tilde(Param[1]);
						if (Param[2][0]==EOS)
						{	strcpy(Param[2], Param[1]);
						}
						replace_udo_quotes(Param[2]);	/* r6pl2 */
						replace_udo_quotes(Param[1]);	/* r6pl2 */
						sprintf(s_entry, ") udoshow (%s) (%s) %s 255 0 0 FileLink (", Param[1], Param[2], "/Null");
   					linkerror= !insert_placeholder(s, Param[0], s_entry, Param[1]);
						break;

   				default:
   					convert_tilde(Param[1]);
						replace_udo_quotes(Param[1]);	/* r6pl2 */
						replace_udo_quotes(Param[2]);	/* r6pl2 */
						linkerror= !insert_placeholder(s, Param[0], Param[1], Param[1]);
   					break;
   			}	/*switch*/
   		}	/* if (no_xlinks) */

	}	/* while */

	if (linkerror)
	{	replace_once(s, Param[0], Param[1]);
		error_replace_param("!xlink");
	}

	if (pnr!=0 && pnr!=2)
	{	error_wrong_nr_parameters("!xlink");
	}

}	/*c_xlink*/



/*	--------------------------------------------------------------
	c_ilink()
	Umwandeln des (!ilink [] [] []) Kommandos in einer Zeile.
	->	inside_b4_macro:	Sind bereits Makros in dieser Zeile
							umgewandelt worden?
	<->	s:					komplette Zeile
	--------------------------------------------------------------
	Kommandosyntax: (!ilink [filename] [alternativtext] [linkziel])
	--------------------------------------------------------------	*/
LOCAL void c_ilink ( char *s, const BOOLEAN inside_b4_macro )
{
	int pnr=0;
	char s_entry[1024], img_entry[1024], old_entry[1024], link[1024];
	char *ptr;
	BOOLEAN flag;
	BOOLEAN linkerror;
	BOOLEAN	old_autorefoff;

	old_autorefoff= bDocAutorefOff;
	bDocAutorefOff= FALSE;

	linkerror = FALSE;
	while ( !linkerror && ((pnr=get_parameters(s, "ilink", 3))==3) )
	{
		strcpy(link, Param[3]);
		del_whitespaces(Param[1]);
		del_whitespaces(Param[2]);
		del_whitespaces(Param[3]);
		
		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[2], TRUE);	
				auto_quote_chars(Param[3], TRUE);	
			}
		
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
			adjust_params_inside(Param[3]);
		}

		fsplit(Param[1], tmp_driv, tmp_path, tmp_name, tmp_suff);

		replace_udo_quotes(Param[2]);
		replace_udo_quotes(Param[3]);

		switch(desttype)
		{
			case TOHTM:
			case TOMHH:
				strcpy(tmp_suff, sDocImgSuffix);
				sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
				replace_char(Param[1], "\\", "/");

				strcpy(s_entry, Param[3]);
				c_tilde(s_entry);
				replace_udo_quotes(s_entry);

				convert_tilde(Param[2]);
				convert_tilde(Param[3]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[3]);
				strcpy(old_entry, Param[3]);

				auto_references(s_entry, TRUE, "", 0, 0);		/* auch innerhalb des Nodes linken (TRUE)! */

				/* Trick/Hack: Schauen, ob nun "> im Eintrag steht und dann */
				/* ab dort den Image-Eintrag setzen. */

				flag= FALSE;

				if ( (ptr=strstr(s_entry, "\">")) != NULL )
				{	if (no_images)	/* r6pl2 */
					{	strcpy(img_entry, Param[2]);
					}
					else
					{	sprintf(img_entry, "<img src=\"%s\" alt=\"%s\" border=\"0\">",
							Param[1], Param[2]);
					}
					flag= replace_once(ptr, old_entry, img_entry);
				}
				
				if (!flag)
				{	error_undefined_link(link);
					strcpy(s_entry, Param[2]);	/* PL9 */
				}
				
				linkerror= !insert_placeholder(s, Param[0], s_entry, Param[2]);
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				strcpy(tmp_suff, ".bmp");
				sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
				replace_char(Param[1], "\\", "/");

				strcpy(s_entry, Param[3]);
				c_tilde(s_entry);
				replace_udo_quotes(s_entry);

				convert_tilde(Param[2]);
				convert_tilde(Param[3]);
				replace_udo_quotes(Param[2]);
				replace_udo_quotes(Param[3]);
				strcpy(old_entry, Param[3]);

				auto_references(s_entry, TRUE, "", 0, 0);		/* auch innerhalb des Nodes linken (TRUE)! */

				/* Trick: Schauen, ob nun {\uldb im Eintrag steht und dann */
				/* ab dort den Image-Text einsetzen. */
				flag= FALSE;
				if ( (ptr=strstr(s_entry, "{\\uldb")) != NULL )
				{	if (no_images)	/*r6pl2*/
					{	strcpy(img_entry, Param[2]);
					}
					else
					{	sprintf(img_entry, "\\{bmc %s\\}", Param[1]);
					}
					flag= replace_once(ptr, old_entry, img_entry);
				}
				
				if (!flag)
				{	error_undefined_link(link);
					strcpy(s_entry, Param[2]);	/* PL9 */
				}
				
				linkerror= !insert_placeholder(s, Param[0], s_entry, Param[2]);
				break;

			case TOLDS:
				linkerror= !convert_link_lds(s, Param[0], Param[2], Param[3], link);
				break;
			case TOSTG:
			case TOAMG:
				linkerror= !convert_link_stg(s, Param[0], Param[2], Param[3], link);
				break;
			case TOTEX:
			case TOPDL:
				linkerror= !convert_link_tex(s, Param[0], Param[2], Param[3]);
				break;
			case TOLYX:
				linkerror= !convert_link_lyx(s, Param[0], Param[2], Param[3]);
				break;
			case TOTVH:
				linkerror= !convert_link_tvh(s, Param[0], Param[2], Param[3]);
				break;
			default:
				linkerror= !convert_link_etc(s, Param[0], Param[2], Param[3], link);
				break;
		}
	}
	
	if (linkerror)
	{	replace_once(s, Param[0], Param[2]);
		error_replace_param("!ilink");
	}

	if (pnr!=0 && pnr!=3)
	{	error_wrong_nr_parameters("!ilink");
	}

	bDocAutorefOff= old_autorefoff;

}	/*c_ilink*/



LOCAL void c_plink ( char *s, const BOOLEAN inside_b4_macro )
{
	int pnr=0;
	char s_entry[1024];
	BOOLEAN linkerror= FALSE;

	while ( !linkerror && (pnr=get_parameters(s, "plink", 2))==2 )
	{

		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);	
				auto_quote_chars(Param[2], TRUE);	
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		switch (desttype)
		{
			case TOTEX:
			case TOPDL:
				label2tex(Param[2]);
				sprintf(s_entry, "%s (%s %s \\pageref{%s})",
					Param[1], lang.see, lang.page, Param[2]);
				linkerror= !replace_once(s, Param[0], s_entry);
				break;
			case TOLYX:
				sprintf(s_entry,
					"%s (%s %s \n\\begin_inset LatexDel \\pageref{%s}\n\n\\end_inset\n\n)",
					Param[1], lang.see, lang.page, Param[2]);
				if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
				{	linkerror= TRUE;
					replace_once(s, Param[0], s_entry);
				}
				break;
			default:
				linkerror= !replace_once(s, Param[0], Param[1]);
		}
	}

	if (pnr!=0 && pnr!=2)
	{	error_wrong_nr_parameters("!plink");
	}

	if (linkerror)
	{	error_replace_param("!plink");
	}

}	/*c_plink*/


LOCAL void c_nolink ( char *s, const BOOLEAN inside_b4_macro )
{
	int pnr=0;
	char s_entry[1024];
	BOOLEAN linkerror= FALSE;

	while ( !linkerror && (pnr=get_parameters(s, "nolink", 1))==1 )
	{
		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);	
				auto_quote_chars(Param[2], TRUE);	
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		switch (desttype)
		{
			case TOSTG:
			case TOAMG:
				replace_2at_by_1at(Param[1]);
				sprintf(s_entry, "@{\"%s\" ignore}", Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
				{	linkerror= TRUE;
					replace_once(s, Param[0], Param[1]);
				}
				break;

			default:
				if (!insert_placeholder(s, Param[0], Param[1], Param[1]))
				{	linkerror= TRUE;
					replace_once(s, Param[0], Param[1]);
				}
				break;
		}
	}

	if (pnr!=0 && pnr!=1)
	{	error_wrong_nr_parameters("!nolink");
	}

	if (linkerror)
	{	error_replace_param("!nolink");
	}

}	/*c_nolink*/



LOCAL void c_comment ( char *s, const BOOLEAN inside_b4_macro )
{
	int pnr=0;
	char s_entry[1024];
	BOOLEAN linkerror= FALSE;

	while ( !linkerror && (pnr=get_parameters(s, "comment", 1))==1 )
	{
		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);	
				auto_quote_chars(Param[2], TRUE);	
			}
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		switch (desttype)
		{
			case TOHTM:
			case TOMHH:
				sprintf(s_entry, "<!-- %s -->", Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
				{	linkerror= TRUE;
					replace_once(s, Param[0], Param[1]);
				}
				break;

			case TOSRC:
			case TOSRP:
				sprintf(s_entry, "%s %s %s", sSrcRemOn, Param[1], sSrcRemOff);
				if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
				{	linkerror= TRUE;
					replace_once(s, Param[0], Param[1]);
				}
				break;

			case TOWIN:
			case TOWH4:
			case TORTF:
			case TOAQV:
				sprintf(s_entry, "{\\*\\%s}", Param[1]);
				if (!insert_placeholder(s, Param[0], s_entry, Param[1]))
				{	linkerror= TRUE;
					replace_once(s, Param[0], Param[1]);
				}
				break;

			default:
				if (use_comments)
				{	sprintf(s_entry, "(%s)", Param[1]);
					if (!replace_once(s, Param[0], s_entry))
					{	linkerror= TRUE;
						replace_once(s, Param[0], Param[1]);
					}
				}
				else
				{	if (!delete_once(s, Param[0]))
					{	linkerror= TRUE;
					}
				}
				break;
		}
	}

	if (pnr!=0 && pnr!=1)
	{	error_wrong_nr_parameters("comment");
	}

	if (linkerror)
	{	error_replace_param("comment");
	}

}	/*c_comment*/



LOCAL BOOLEAN c_index ( char *s, const BOOLEAN inside_b4_macro )
{
	char s_tidx[256], s_entry[256], upr_entry[512];
	char keyword[256];
	BOOLEAN ret= TRUE;

	if ( get_parameters(s, "index", 1) )
	{
		strcpy(s_tidx, Param[1]);

		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);	
				auto_quote_chars(s_tidx, TRUE);	
			}
		
			adjust_params_inside(Param[1]);
		}

		/* New in r6pl15 [NHz] */

		/* Set index in project file */

		sprintf(upr_entry, "%s", Param[1]); 

		save_upr_entry_index ( 1, sCurrFileName, upr_entry, uiCurrFileLine );

		if (no_index)
		{	ret= replace_once(s, Param[0], Param[1]);
		}
		else
		{
			bCalledIndex= TRUE;	/* PL9 */
			
			switch (desttype)
			{
				case TOTEX:
				case TOPDL:
					auto_quote_texindex(s_tidx);
					sprintf(s_entry, "\\index{%s}", s_tidx);
					ret= delete_once(s, Param[0]);
					break;
				case TORTF:
					sprintf(s_entry, "{\\xe\\v %s}", Param[1]);
					/* Changed in r6pl15 [NHz] */

					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					/* ret= delete_once(s, Param[0]);*/
					break;
				case TOWIN:
				case TOWH4:
				case TOAQV:
					convert_tilde(Param[1]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					strcpy(keyword, Param[1]);
					winspecials2ascii(keyword);	/* PL9 */
					sprintf(s_entry, "{K{\\footnote K %s}}", keyword);
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOSTG:
				case TOAMG:
					delete_all_divis(Param[1]);
					convert_tilde(Param[1]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					if (iUdopass==PASS2 && bInsideDocument)
					{	index2stg(Param[1]);
						voutlnf("@index \"%s\"", Param[1]);
					}
					ret= delete_once(s, Param[0]);	/*r6pl9: Soll nicht angezeigt werden*/
					break;
				case TOINF:
					if (iUdopass==PASS2 && bInsideDocument)
					{	voutlnf("@cindex %s", Param[1]);
						add_idxlist_item(Param[1], "", "");
					}
					ret= delete_once(s, Param[0]);
					break;
				case TOHPH:
					sprintf(s_entry, "<idx>%s<\\idx>", Param[1]);
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOASC:
					delete_all_divis(Param[1]);
					convert_tilde(Param[1]);
					replace_udo_quotes(Param[1]);
					if (iUdopass==PASS2)
					{	add_idxlist_item(Param[1], "", "");
					}
					ret= delete_once(s, Param[0]);
					break;
				case TOMHH:
					if (iUdopass==PASS2)
					{	output_htmlhelp_index(1, Param[1], "", "");
					}
					ret= delete_once(s, Param[0]);
					break;

				default:
					ret= delete_once(s, Param[0]);
					break;
			}

		}
	}

	if (!ret)
	{	error_replace_param("!index");
		return FALSE;
	}
	
	return TRUE;
}	/*c_index */


/* PL15: Die Nummer des Pass wird geprueft, damit bei Formaten, die die */
/* Indexbefehle direkt ausgeben, nicht am Anfang der Zieldatei die */
/* gesamten Indizes landen. */
/* r6pl2: Stilbefehle und Umlaute werden umgewandelt */

LOCAL BOOLEAN c_single_index ( char *s, const BOOLEAN inside_b4_macro )
{
	char s_tidx[256], s_entry[256], upr_entry[512];
	char keyword[256];
	BOOLEAN ret= TRUE;

	if ( get_parameters(s, "idx", 1) )
	{
		strcpy(s_tidx, Param[1]);

		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);	
				auto_quote_chars(s_tidx, TRUE);	
			}
		
			adjust_params_inside(Param[1]);
		}

		/* New in r6pl15 [NHz] */

		/* Set index in project file */

		sprintf(upr_entry, "%s", Param[1]); 

		save_upr_entry_index ( 1, sCurrFileName, upr_entry, uiCurrFileLine );

		if (no_index)
		{	ret= replace_once(s, Param[0], Param[1]);
		}
		else
		{
			bCalledIndex= TRUE;	/* PL9 */
			
			switch (desttype)
			{
				case TOTEX:
				case TOPDL:
					auto_quote_texindex(s_tidx);
					sprintf(s_entry, "%s\\index{%s}", Param[1], s_tidx);
					ret= replace_once(s, Param[0], s_entry);
					break;
				case TORTF:
					sprintf(s_entry, "{\\xe\\v %s}%s", Param[1], Param[1]);
					ret= replace_once(s, Param[0], s_entry);
					break;
				case TOWIN:
				case TOWH4:
				case TOAQV:
					convert_tilde(Param[1]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					strcpy(keyword, Param[1]);
					winspecials2ascii(keyword);	/* PL9 */
					sprintf(s_entry, "{K{\\footnote K %s}}%s", keyword, Param[1]);
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOSTG:
				case TOAMG:
					delete_all_divis(Param[1]);
					convert_tilde(Param[1]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					if (iUdopass==PASS2 && bInsideDocument)
					{	index2stg(Param[1]);
						voutlnf("@index \"%s\"", Param[1]);
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOINF:
					if (iUdopass==PASS2 && bInsideDocument)
					{	voutlnf("@cindex %s", Param[1]);
						add_idxlist_item(Param[1], "", "");
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOHPH:
					sprintf(s_entry, "<idx>%s<\\idx>%s", Param[1], Param[1]);
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOASC:
					delete_all_divis(Param[1]);
					convert_tilde(Param[1]);
					replace_udo_quotes(Param[1]);
					if (iUdopass==PASS2)
					{	add_idxlist_item(Param[1], "", "");
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOMHH:
					if (iUdopass==PASS2)
					{	output_htmlhelp_index(1, Param[1], "", "");
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				default:
					ret= replace_once(s, Param[0], Param[1]);
					break;
			}

		}
	}

	if (!ret)
	{	error_replace_param("!idx");
		return FALSE;
	}
	
	return TRUE;
}	/*c_single_index */


LOCAL BOOLEAN c_double_index ( char *s, const BOOLEAN inside_b4_macro )
{
	char s_entry[1024], upr_entry[512];
	BOOLEAN ret= TRUE;

	if ( get_parameters(s, "idx", 2) )
	{

		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);	
				auto_quote_chars(Param[2], TRUE);	
			}	
			
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		/* New in r6pl15 [NHz] */

		/* Set index in project file */

		sprintf(upr_entry, "%s:%s", Param[1], Param[2]); 

		save_upr_entry_index ( 2, sCurrFileName, upr_entry, uiCurrFileLine );

		if (no_index)
		{	ret= replace_once(s, Param[0], Param[1]);
		}
		else
		{
			bCalledIndex= TRUE;	/* PL9 */

			switch (desttype)
			{
				case TOTEX:
				case TOPDL:
					auto_quote_texindex(Param[2]);
					sprintf(s_entry, "%s\\index{%s}", Param[1], Param[2]);
					ret= replace_once(s, Param[0], s_entry);
					break;
				case TORTF:	/* PL9 */
					sprintf(s_entry, "{\\xe\\v %s}%s", Param[2], Param[1]);
					ret= replace_once(s, Param[0], s_entry);
					break;
				case TOWIN:
				case TOWH4:
				case TOAQV:
					convert_tilde(Param[1]);
					convert_tilde(Param[2]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					del_internal_styles(Param[2]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					replace_udo_quotes(Param[2]);
					winspecials2ascii(Param[2]);	/* PL9 */
					sprintf(s_entry, "{K{\\footnote K %s}}%s", Param[2], Param[1]);
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOSTG:	/* PL 9 */
				case TOAMG:
					delete_all_divis(Param[1]);
					delete_all_divis(Param[2]);
					convert_tilde(Param[1]);
					convert_tilde(Param[2]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					del_internal_styles(Param[2]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					replace_udo_quotes(Param[2]);
					if (iUdopass==PASS2 && bInsideDocument)
					{	index2stg(Param[2]);
						voutlnf("@index \"%s\"", Param[2]);
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOINF:	/* PL 9 */
					if (iUdopass==PASS2 && bInsideDocument)
					{	voutlnf("@cindex %s", Param[2]);
						add_idxlist_item(Param[2], "", "");
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOHPH:
					sprintf(s_entry, "<idx>%s<\\idx>%s", Param[2], Param[1]);
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOASC:
					delete_all_divis(Param[1]);
					delete_all_divis(Param[2]);
					convert_tilde(Param[1]);
					convert_tilde(Param[2]);
					replace_udo_quotes(Param[1]);
					replace_udo_quotes(Param[2]);
					if (iUdopass==PASS2)
					{	add_idxlist_item(Param[2], "", "");
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOMHH:
					if (iUdopass==PASS2)
					{	output_htmlhelp_index(1, Param[2], "", "");
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				default:
					ret= replace_once(s, Param[0], Param[1]);
					break;
			}
		}
	}

	if (!ret)
	{	error_replace_param("!idx");
		return FALSE;
	}

	return TRUE;
}	/*c_double_index */


LOCAL BOOLEAN c_tripple_index ( char *s, const BOOLEAN inside_b4_macro )
{
	char s_entry[1024], upr_entry[512];
	BOOLEAN ret= TRUE;

	if ( get_parameters(s, "idx", 3) )
	{
		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);	
				auto_quote_chars(Param[2], TRUE);	
				auto_quote_chars(Param[3], TRUE);	
			}
		
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
			adjust_params_inside(Param[3]);
		}

		/* New in r6pl15 [NHz] */

		/* Set index in project file */

		sprintf(upr_entry, "%s:%s:%s", Param[1], Param[2], Param[3]); 

		save_upr_entry_index ( 3, sCurrFileName, upr_entry, uiCurrFileLine );

		if (no_index)
		{	ret= replace_once(s, Param[0], Param[1]);
		}
		else
		{
			bCalledIndex= TRUE;	/* PL9 */

			switch (desttype)
			{
				case TOTEX:
				case TOPDL:
					auto_quote_texindex(Param[2]);
					auto_quote_texindex(Param[3]);
					if (use_mirrored_indices)
					{	sprintf(s_entry, "%s\\index{%s!%s}\\index{%s!%s}",
							Param[1], Param[2], Param[3], Param[3], Param[2]);
					}
					else
					{	sprintf(s_entry, "%s\\index{%s!%s}", Param[1], Param[2], Param[3]);
					}
					ret= replace_once(s, Param[0], s_entry);
					break;
				case TORTF:
					if (use_mirrored_indices)
					{	sprintf(s_entry, "{\\xe\\v %s\\:%s}{\\xe\\v %s\\:%s}%s",
							Param[2], Param[3], Param[3], Param[2], Param[1]);
					}
					else
					{	sprintf(s_entry, "{\\xe\\v %s\\:%s}%s", Param[2], Param[3], Param[1]);
					}
					ret= replace_once(s, Param[0], s_entry);
					break;
				case TOWIN:
				case TOWH4:
				case TOAQV:
					convert_tilde(Param[1]);
					convert_tilde(Param[2]);
					convert_tilde(Param[3]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					del_internal_styles(Param[2]);	/*r6pl2*/
					del_internal_styles(Param[3]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					replace_udo_quotes(Param[2]);
					replace_udo_quotes(Param[3]);
					winspecials2ascii(Param[2]);
					winspecials2ascii(Param[3]);
					if (use_mirrored_indices)
					{	sprintf(s_entry, "{K{\\footnote K %s, %s}}{K{\\footnote K %s, %s}}%s",
							Param[2], Param[3], Param[3], Param[2], Param[1]);
					}
					else
					{	sprintf(s_entry, "{K{\\footnote K %s, %s}}%s", Param[2], Param[3], Param[1]);
					}
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOSTG:	/* PL 9 */
				case TOAMG:
					delete_all_divis(Param[1]);
					delete_all_divis(Param[2]);
					delete_all_divis(Param[3]);
					convert_tilde(Param[1]);
					convert_tilde(Param[2]);
					convert_tilde(Param[3]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					del_internal_styles(Param[2]);	/*r6pl2*/
					del_internal_styles(Param[3]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					replace_udo_quotes(Param[2]);
					replace_udo_quotes(Param[3]);
					if (iUdopass==PASS2 && bInsideDocument)
					{	index2stg(Param[2]);
						index2stg(Param[3]);
						voutlnf("@index \"%s, %s\"", Param[2], Param[3]);
						if (use_mirrored_indices)
						{	voutlnf("@index \"%s, %s\"", Param[3], Param[2]);
						}
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOINF:
					if (iUdopass==PASS2 && bInsideDocument)
					{
						voutlnf("@cindex %s, %s", Param[2], Param[3]);
						add_idxlist_item(Param[2], Param[3], "");
						if (use_mirrored_indices)
						{	voutlnf("@cindex %s, %s", Param[3], Param[2]);
							add_idxlist_item(Param[3], Param[2], "");
						}
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOHPH:
					sprintf(s_entry, "<idx>%s, %s<\\idx>%s", Param[2], Param[3], Param[1]);
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOASC:
					delete_all_divis(Param[1]);
					delete_all_divis(Param[2]);
					delete_all_divis(Param[3]);
					convert_tilde(Param[1]);
					convert_tilde(Param[2]);
					convert_tilde(Param[3]);
					replace_udo_quotes(Param[1]);
					replace_udo_quotes(Param[2]);
					replace_udo_quotes(Param[3]);
					if (iUdopass==PASS2)
					{	add_idxlist_item(Param[2], Param[3], "");
						if (use_mirrored_indices)
						{	add_idxlist_item(Param[3], Param[2], "");
						}
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOMHH:
					if (iUdopass==PASS2)
					{	output_htmlhelp_index(2, Param[2], Param[3], "");
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				default:
					ret= replace_once(s, Param[0], Param[1]);
					break;
			}
		}
	}

	if (!ret)
	{	error_replace_param("!idx");
		return FALSE;
	}
	
	return TRUE;

}	/*c_tripple_index */


LOCAL BOOLEAN c_quadruple_index ( char *s, const BOOLEAN inside_b4_macro )
{
	char s_entry[1024], upr_entry[512];
	BOOLEAN ret= TRUE;

	if ( get_parameters(s, "idx", 4) )
	{
		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[1], TRUE);	
				auto_quote_chars(Param[2], TRUE);
				auto_quote_chars(Param[3], TRUE);
				auto_quote_chars(Param[4], TRUE);
			}

			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
			adjust_params_inside(Param[3]);
			adjust_params_inside(Param[4]);
		}

		/* New in r6pl15 [NHz] */

		/* Set index in project file */

		sprintf(upr_entry, "%s:%s:%s:%s", Param[1], Param[2], Param[3], Param[4]); 

		save_upr_entry_index ( 4, sCurrFileName, upr_entry, uiCurrFileLine );

		if (no_index)
		{	ret= replace_once(s, Param[0], Param[1]);
		}
		else
		{
			bCalledIndex= TRUE;	/* PL9 */

			switch (desttype)
			{
				case TOTEX:
				case TOPDL:
					auto_quote_texindex(Param[2]);
					auto_quote_texindex(Param[3]);
					auto_quote_texindex(Param[4]);
					sprintf(s_entry, "%s\\index{%s!%s!%s}", Param[1], Param[2], Param[3], Param[4]);
					ret= replace_once(s, Param[0], s_entry);
					break;
				case TORTF:	/* PL9 */
					sprintf(s_entry, "{\\xe\\v %s\\:%s\\:%s}%s", Param[2], Param[3], Param[4], Param[1]);
					ret= replace_once(s, Param[0], s_entry);
					break;
				case TOWIN:
				case TOWH4:
				case TOAQV:
					convert_tilde(Param[1]);
					convert_tilde(Param[2]);
					convert_tilde(Param[3]);
					convert_tilde(Param[4]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					del_internal_styles(Param[2]);	/*r6pl2*/
					del_internal_styles(Param[3]);	/*r6pl2*/
					del_internal_styles(Param[4]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					replace_udo_quotes(Param[2]);
					replace_udo_quotes(Param[3]);
					replace_udo_quotes(Param[4]);
					winspecials2ascii(Param[2]);	/* PL9 */
					winspecials2ascii(Param[3]);	/* PL9 */
					winspecials2ascii(Param[4]);	/* PL9 */
					sprintf(s_entry, "{K{\\footnote K %s, %s, %s}}%s", Param[2], Param[3], Param[4], Param[1]);
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOSTG:	/* PL 9 */
				case TOAMG:
					delete_all_divis(Param[1]);
					delete_all_divis(Param[2]);
					delete_all_divis(Param[3]);
					delete_all_divis(Param[4]);
					convert_tilde(Param[1]);
					convert_tilde(Param[2]);
					convert_tilde(Param[3]);
					convert_tilde(Param[4]);
					del_internal_styles(Param[1]);	/*r6pl2*/
					del_internal_styles(Param[2]);	/*r6pl2*/
					del_internal_styles(Param[3]);	/*r6pl2*/
					del_internal_styles(Param[4]);	/*r6pl2*/
					replace_udo_quotes(Param[1]);
					replace_udo_quotes(Param[2]);
					replace_udo_quotes(Param[3]);
					replace_udo_quotes(Param[4]);
					if (iUdopass==PASS2 && bInsideDocument)
					{	index2stg(Param[2]);
						index2stg(Param[3]);
						index2stg(Param[4]);
						voutlnf("@index \"%s, %s, %s\"", Param[2], Param[3], Param[4]);
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOINF:	/* PL 9 */
					if (iUdopass==PASS2 && bInsideDocument)
					{	voutlnf("@cindex %s, %s, %s", Param[2], Param[3], Param[4]);
						add_idxlist_item(Param[2], Param[3], Param[4]);
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOHPH:
					sprintf(s_entry, "<idx>%s, %s, %s<\\idx>%s", Param[2], Param[3], Param[4], Param[1]);
					if ( !insert_placeholder(s, Param[0], s_entry, s_entry) )
					{	ret= FALSE;
						replace_once(s, Param[0], s_entry);
					}
					break;
				case TOASC:
					delete_all_divis(Param[1]);
					delete_all_divis(Param[2]);
					delete_all_divis(Param[3]);
					delete_all_divis(Param[4]);
					convert_tilde(Param[1]);
					convert_tilde(Param[2]);
					convert_tilde(Param[3]);
					convert_tilde(Param[4]);
					replace_udo_quotes(Param[1]);
					replace_udo_quotes(Param[2]);
					replace_udo_quotes(Param[3]);
					replace_udo_quotes(Param[4]);
					if (iUdopass==PASS2)
					{	add_idxlist_item(Param[2], Param[3], Param[4]);
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				case TOMHH:
					if (iUdopass==PASS2)
					{	output_htmlhelp_index(3, Param[2], Param[3], Param[4]);
					}
					ret= replace_once(s, Param[0], Param[1]);
					break;
				default:
					ret= replace_once(s, Param[0], Param[1]);
					break;
			}
		}
	}

	if (!ret)
	{	error_replace_param("!idx");
		return FALSE;
	}
	
	return TRUE;
}	/*c_quadruple_index */


GLOBAL void c_internal_index ( char *s, const BOOLEAN inside_b4_macro )
{
	int nr;
	BOOLEAN flag;
	BOOLEAN has_idx, has_index;

	
	has_idx = (strstr(s, "(!idx")!=NULL);
	has_index = (strstr(s, "(!index")!=NULL);

	if (has_idx)
	{
		do
		{	
			nr=get_nr_of_parameters(CMD_IDX, s);
			
			switch(nr)
			{
				case 0:		flag= FALSE;
							break;
				case 1:		flag= c_single_index(s, inside_b4_macro);
							break;
				case 2: 	flag= c_double_index(s, inside_b4_macro);
							break;
				case 3: 	flag= c_tripple_index(s, inside_b4_macro);
							break;
				case 4: 	flag= c_quadruple_index(s, inside_b4_macro);
							break;
				default:	error_wrong_nr_parameters("!idx");
							flag= FALSE;
							break;
			}

		}	while (flag==TRUE);
	}

	if (has_index)	/* r6pl6: Unterstuetzung fuer (!index [...]) */
	{
		do
		{	
			nr=get_nr_of_parameters("index", s);
			
			switch (nr)
			{
				case 0:		flag= FALSE;
							break;
				case 1:		flag= c_index(s, inside_b4_macro);
							break;
				default:	error_wrong_nr_parameters("!index");
							flag= FALSE;
							break;
			}

		}	while (flag==TRUE);
	}

}	/* c_internal_index */


LOCAL void c_internal_image ( char *s, const BOOLEAN inside_b4_macro )
{
	int pnr=0;
	char s_entry[1024], sGifSize[80], sGifName[512];
	BOOLEAN flag;
	unsigned int uiW, uiH;

	flag = FALSE;
	while ( !flag && ((pnr=get_parameters(s, "img", 2))==2) )
	{
		if (inside_b4_macro)
		{
			if (desttype!=TOSTG)
			{	auto_quote_chars(Param[2], TRUE);	
			}
		
			adjust_params_inside(Param[1]);
			adjust_params_inside(Param[2]);
		}

		fsplit(Param[1], tmp_driv, tmp_path, tmp_name, tmp_suff);
		
		replace_udo_quotes(Param[2]);

		switch(desttype)
		{
			case TOHTM:
			case TOMHH:
				strcpy(tmp_suff, sDocImgSuffix);
				sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
				path_adjust_separator(Param[1]);
				uiW= uiH= 0;
				sGifSize[0]= EOS;
				if (!no_img_size)
				{
					if (my_stricmp(tmp_suff, ".gif")==0)
					{
						strcpy(sGifName, Param[1]);
						strinsert(sGifName, old_outfile.path);
						strinsert(sGifName, old_outfile.driv);
						path_adjust_separator(sGifName);

						if (!get_gif_size(sGifName, &uiW, &uiH))
						{	error_read_gif(sGifName);
						}
					}
				}
				if (uiW!=0 && uiH!=0)
				{	sprintf(sGifSize, " width=\"%u\" height=\"%u\"", uiW, uiH);
				}
				replace_char(Param[1], "\\", "/");
				if (no_images)	/*r6pl2*/
				{	strcpy(s_entry, Param[2]);
				}
				else
				{	sprintf(s_entry, "<img src=\"%s\" alt=\"%s\"%s>",
						Param[1], Param[2], sGifSize);
				}
				flag= !insert_placeholder(s, Param[0], s_entry, Param[2]);
				break;
			case TOHPH:
				strcpy(tmp_suff, sDocImgSuffix);
				sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
				replace_char(Param[1], "\\", "/");
				if (no_images)	/*r6pl2*/
				{	strcpy(s_entry, Param[2]);
				}
				else
				{	sprintf(s_entry, "<graphic>%s<\\graphic>", Param[1]);
				}
				flag= !insert_placeholder(s, Param[0], s_entry, Param[2]);
				break;
			case TOWIN:
			case TOWH4:
			case TOAQV:
				strcpy(tmp_suff, ".bmp");
				sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
				replace_char(Param[1], "\\", "/");
				if (no_images)	/*r6pl2*/
				{	strcpy(s_entry, Param[2]);
				}
				else
				{	sprintf(s_entry, " \\{bmc %s\\}", Param[1]);
				}
				flag= !insert_placeholder(s, Param[0], s_entry, Param[2]);
				break;
			case TOIPF:	/*r6pl8*/
				strcpy(tmp_suff, ".bmp");
				sprintf(Param[1], "%s%s%s%s", tmp_driv, tmp_path, tmp_name, tmp_suff);
				if (no_images)	/*r6pl2*/
				{	strcpy(s_entry, Param[2]);
				}
				else
				{	sprintf(s_entry, "\n:artwork runin name='%s'.\n", Param[1]);
				}
				flag= !insert_placeholder(s, Param[0], s_entry, Param[2]);
				break;
			/* New in r6.3pl3 [NHz] */
			case TORTF:
				strcpy(s_entry, "");
				flag= !insert_placeholder(s, Param[0], s_entry, Param[2]);
				break;
			default:
				strcpy(s_entry, Param[2]);
				flag= !insert_placeholder(s, Param[0], s_entry, Param[2]);
				break;
		}
	}
	
	if (flag)
	{	replace_once(s, Param[0], Param[2]);
		error_replace_param("!img");
	}

	if (pnr!=0 && pnr!=2)
	{	error_wrong_nr_parameters("!img");
	}

}	/*c_internal_image*/


#if 0 /* alte Version */
LOCAL void c_internal_raw ( char *s, const BOOLEAN inside_b4_macro )
{
	int pnr;
	BOOLEAN flag;

	UNUSED(inside_b4_macro);
	flag = FALSE;
	while ( !flag && ((pnr=get_parameters(s, "raw", 1))==1) )
	{
		flag= !insert_placeholder(s, Param[0], Param[1], Param[1]);
	}
	
	if (flag)
	{	replace_once(s, Param[0], Param[1]);
		error_replace_param("!raw");
	}

	if (pnr!=0 && pnr!=2)
	{	error_wrong_nr_parameters("!raw");
	}

}
#endif


LOCAL BOOLEAN c_single_raw ( char *s, const BOOLEAN inside_b4_macro )
{
	BOOLEAN flag;

	UNUSED(inside_b4_macro);
	if ( get_parameters(s, "raw", 1) )
	{
		flag= insert_placeholder(s, Param[0], Param[1], Param[1]);

		if (!flag)
		{	replace_once(s, Param[0], Param[1]);
			error_replace_param("!raw");
			return FALSE;
		}

	}

	return TRUE;

}	/* c_single_raw */


LOCAL BOOLEAN c_double_raw ( char *s, const BOOLEAN inside_b4_macro )
{
	BOOLEAN flag;

	UNUSED(inside_b4_macro);
	if ( get_parameters(s, "raw", 2) )
	{
		if (str_for_desttype(Param[1]))
		{
			flag= insert_placeholder(s, Param[0], Param[2], Param[2]);

			if (!flag)
			{	delete_once(s, Param[0]);
				error_replace_param("!raw");
				return FALSE;
			}
		}
		else
		{
			delete_once(s, Param[0]);
		}
	}

	return TRUE;

}	/* c_double_raw */


LOCAL void c_internal_raw ( char *s, const BOOLEAN inside_b4_macro )
{
	int nr;
	BOOLEAN flag;
	BOOLEAN has_raw;
	
	has_raw = (strstr(s, "(!raw")!=NULL);

	if (has_raw)
	{
		do
		{	
			nr=get_nr_of_parameters("raw", s);
			
			switch(nr)
			{
				case 0:		flag= FALSE;
							break;
				case 1:		flag= c_single_raw(s, inside_b4_macro);
							break;
				case 2: 	flag= c_double_raw(s, inside_b4_macro);
							break;
				default:	error_wrong_nr_parameters("!raw");
							flag= FALSE;
							break;
			}

		}	while (flag);
	}

}	/* c_internal_raw */


GLOBAL void c_commands_inside ( char *s, const BOOLEAN inside_b4_macro )
{
	if ( strstr(s, "(!")==NULL )
	{	/* Optimierung */
		return;
	}
	
	c_link(s, inside_b4_macro);
	c_url(s, inside_b4_macro);
	c_xlink(s, inside_b4_macro);
	c_ilink(s, inside_b4_macro);
	c_plink(s, inside_b4_macro);
	c_nolink(s, inside_b4_macro);
	c_comment(s, inside_b4_macro);
	c_internal_index(s, inside_b4_macro);
	c_internal_image(s, inside_b4_macro);
	c_internal_raw(s, inside_b4_macro);

}	/* c_commands_inside */



/*	################################################################
	#
	# Silbentrennregeln hinzufuegen und im Text ersetzen
	#
	################################################################	*/
GLOBAL void replace_hyphens ( char *s )
{
	UINT h;
	
	if (hyphen_counter<=0)	return;

	for (h=0; h<hyphen_counter; h++)
	{
		if (hyphen[h]!=NULL)
		{
			replace_all(s, hyphen[h]->solo, hyphen[h]->hyphen);
		}
	}
}	/* replace_hyphens */


GLOBAL void add_hyphen ( void )
{
	HYPHEN *p;
	
	switch(desttype)
	{
		case TOWIN:
		case TOWH4:
		case TOAQV:
		case TORTF:
		case TOHTM:
		case TOMHH:
			return;	/* Hier werden keine Trennregeln benoetigt */
	}
	
	if (hyphen_counter>=MAXHYPHEN)
	{	error_too_many_hyphens();
		return;
	}
	
	if (token_counter<=1)
	{	error_missing_parameter("!hyphen");
		return;
	}
	
	p= (HYPHEN *) um_malloc(sizeof(HYPHEN));
	
	if (p==NULL)
	{	error_malloc_failed();
		return;
	}

	tokcpy2(p->hyphen, HYPHEN_LEN+1);
	tokcpy2(p->solo, HYPHEN_LEN+1);

	if (desttype==TOTEX || desttype==TOPDL)
	{	/* Die Tokens sind leider vorher schon durch c_vars gelaufen */
		/* Dabei wurden auch (!ck) usw. bereits in "ck umgewandelt */
		/* Problem: replace_hyphens() findet Dru"cker dann nicht */
		qdelete_all(p->solo, "\\-", 2);
	}
	else
	{	delete_all_divis(p->solo);
	}

	hyphen[hyphen_counter]= p;
	
	hyphen_counter++;

}	/* add_hyphen */



/*	############################################################
	# Testen, ob Makro/Definition Parameter benutzt
	############################################################	*/
LOCAL BOOLEAN md_uses_parameters ( const char *s )
{
	if (strstr(s, "(!0)")!=NULL)	return TRUE;	/* r6pl2 */
	if (strstr(s, "(!1)")!=NULL)	return TRUE;
	if (strstr(s, "(!2)")!=NULL)	return TRUE;
	if (strstr(s, "(!3)")!=NULL)	return TRUE;
	if (strstr(s, "(!4)")!=NULL)	return TRUE;
	if (strstr(s, "(!5)")!=NULL)	return TRUE;
	if (strstr(s, "(!6)")!=NULL)	return TRUE;
	if (strstr(s, "(!7)")!=NULL)	return TRUE;
	if (strstr(s, "(!8)")!=NULL)	return TRUE;
	if (strstr(s, "(!9)")!=NULL)	return TRUE;

	return FALSE;
}

/*	############################################################
	#
	# Ein Makro hinzufuegen
	#
	############################################################	*/
GLOBAL void replace_macros ( char *s )
{
	UINT i;

	if (strstr(s, "(!")==NULL)
	{	return;
	}
	
	for (i=0; i<macro_counter; i++)
	{	if (macros[i]!=NULL)
		{
			if (macros[i]->vars)
			{	replace_variables(s, macros[i]->name, macros[i]->entry);
			}
			else
			{	replace_all(s, macros[i]->name, macros[i]->entry);
			}
		}
	}

}	/*replace_macros*/


GLOBAL BOOLEAN add_macro ( void )
{
	int i;
	MACROS *p;
	char entry[512];

	/* Die Daten stehen in token[] */
	
	if (macro_counter>=MAXMACROS)
	{	error_too_many_macros();
		return FALSE;
	}

	/* Nur !macro in der Zeile? */	
	if (token_counter<=1)
	{	error_missing_parameter(CMD_MACRO);
		return FALSE;
	}

	/* PL10: Makro-Name zu lang? */	
	if (strlen(token[1])>MACRO_NAME_LEN)
	{	error_long_macro_name(MACRO_NAME_LEN);
		return FALSE;
	}

	p= (MACROS *) um_malloc(sizeof(MACROS));
	
	if (p==NULL)
	{	error_malloc_failed();
		return FALSE;
	}

	entry[0]= EOS;

	if (token_counter>=2)
	{	for (i=2; i<token_counter; i++)
		{	strcat(entry, token[i]);
			if (i<token_counter-1)
			{	strcat(entry, " ");
			}
		}
	}

	auto_quote_chars(entry, FALSE);
	replace_macros(entry);
	replace_defines(entry);
	c_divis(entry);
	c_vars(entry);


	/* PL10: Inhalt zu lang? */
	if (strlen(entry)>MACRO_CONT_LEN)
	{	error_long_macro_cont(MACRO_CONT_LEN);
		um_free(p);
		return FALSE;
	}

	strcpy(p->entry, entry);

	if ( md_uses_parameters(p->entry) )	/* PL8 */
	{	/* Makro mit Parametern */
		strcpy(p->name, token[1]);
		p->vars= TRUE;
	}
	else
	{	/* normales Makros */
		sprintf(p->name, "(!%s)", token[1]);
		token[1][0]= EOS;
		p->vars= FALSE;
	}
	
	macros[macro_counter]= p;
	macro_counter++;

	return TRUE;	
}	/* add_macro */



/*	############################################################
	#
	# Eine Definition hinzufuegen
	#
	############################################################	*/
GLOBAL void replace_defines ( char *s )
{
	UINT	i;

	if (strstr(s, "(!")==NULL)
	{	return;
	}
	
	for (i=0; i<define_counter; i++)
	{	if (defs[i]!=NULL)
		{	if (defs[i]->vars)
			{	replace_variables(s, defs[i]->name, defs[i]->entry);
			}
			else
			{	replace_all(s, defs[i]->name, defs[i]->entry);
			}
		}
	}
	
}	/*replace_defines*/


GLOBAL BOOLEAN add_define ( void )
{
	int i;
	DEFS *p;
	char entry[512];

	/* Die Daten stehen in token[] */
	
	if (define_counter>=MAXDEFS)
	{	error_too_many_defines();
		return FALSE;
	}

	/* Nur !define in der Zeile? */	
	if (token_counter<=1)
	{	error_missing_parameter(CMD_DEFINE);
		return FALSE;
	}

	/* PL10: Definitions-Name zu lang? */	
	if (strlen(token[1])>DEFINE_NAME_LEN)
	{	error_long_define_name(DEFINE_NAME_LEN);
		return FALSE;
	}


	p= (DEFS *) um_malloc(sizeof(DEFS));
	
	if (p==NULL)
	{	error_malloc_failed();
		return FALSE;
	}

	entry[0]= EOS;

	if (token_counter>=2)
	{	for (i=2; i<token_counter; i++)
		{	strcat(entry, token[i]);
			if (i<token_counter-1)
			{	strcat(entry, " ");
			}
		}
	}
	
	/* PL10: Inhalt zu lang? */
	if (strlen(entry)>DEFINE_CONT_LEN)
	{	error_long_define_cont(DEFINE_CONT_LEN);
		um_free(p);
		return FALSE;
	}
	
	strcpy(p->entry, entry);

	/* Schauen, ob der !define Parameter enthalten soll */

	if ( md_uses_parameters(p->entry) )	/* PL12 */
	{	/* Definition mit Parametern */
		strcpy(p->name, token[1]);
		p->vars= TRUE;
	}
	else
	{	/* normale Definition */
		sprintf(p->name, "(!%s)", token[1]);
		token[1][0]= EOS;
		p->vars= FALSE;
	}
	
	defs[define_counter]= p;
	define_counter++;

	return TRUE;	
}	/* add_define */




/*	############################################################
	#
	# Modulinit
	#
	############################################################	*/
GLOBAL void init_module_par ( void )
{
	int i;
	
	/* Dafuer sorgen, dass alle geleert werden */
	phold_counter= -1;
	for (i=0; i<MAXPHOLDS; i++)
	{	phold[i].magic[0]= EOS;
		phold[i].entry= NULL;
		phold[i].text= NULL;
	}

	hyphen_counter= 0;
	for (i=0; i<MAXHYPHEN; hyphen[i++]= NULL) ;

	macro_counter= 0;
	for (i=0; i<MAXMACROS; macros[i++]= NULL) ;

	define_counter= 0;
	for (i=0; i<MAXDEFS; defs[i++]= NULL) ;

}	/* init_module_par */


GLOBAL void exit_module_par ( void )
{
	int	i;

	for (i=MAXMACROS-1; i>=0; i--)
	{	if (macros[i]!=NULL)
		{	um_free(macros[i]);
		}
	}

	for (i=MAXDEFS-1; i>=0; i--)
	{	if (defs[i]!=NULL)
		{	um_free(defs[i]);
		}
	}

	for (i=MAXHYPHEN-1; i>=0; i--)
	{	if (hyphen[i]!=NULL)
		{	um_free(hyphen[i]);
		}
	}

	reset_placeholders();

}	/* exit_module_par */


/*	############################################################
	# par.c
	############################################################	*/
