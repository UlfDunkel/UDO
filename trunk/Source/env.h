/*	############################################################
	# @(#) env.h
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
	# Konstanten
	############################################################	*/

#define	ENV_IND_ASC_QUOT	5		/* Einrueckungstiefen der Umgebungen */
#define	ENV_IND_RTF_QUOT	567
#define	ENV_IND_WIN_QUOT	454

#define	ENV_IND_ASC_ITEM	5
#define	ENV_IND_RTF_ITEM	567
#define	ENV_IND_WIN_ITEM	567

#define	ENV_IND_ASC_ENUM	5
#define	ENV_IND_RTF_ENUM	567
#define	ENV_IND_WIN_ENUM	567

#define	ENV_IND_ASC_DESC	5
#define	ENV_IND_RTF_DESC	567
#define	ENV_IND_WIN_DESC	567


/*	############################################################
	# globale Variablen
	############################################################	*/
GLOBAL int		iEnvLevel;					/* Zaehler fuer Umgebungen			*/
GLOBAL int		iEnvType[MAXENVLEVEL+1];	/* Typ der Umgebung (ENV_ITEM, ...	*/
GLOBAL int		iEnvIndent[MAXENVLEVEL+1];	/* Einrueckungstiefe einer Umgebung	*/
GLOBAL BOOLEAN	bEnvShort[MAXENVLEVEL+1];	/* Zusammengequetscht?				*/
GLOBAL BOOLEAN	bEnv1stItem[MAXENVLEVEL+1];	/* Ist das naechste !item das erste? */
GLOBAL BOOLEAN	bEnv1stPara[MAXENVLEVEL+1];	/* Erster Absatz des !item?			*/

GLOBAL int		iItemLevel;					/* Zaehler fuer itemize-Umgebungen	*/
GLOBAL int		iEnumLevel;					/* Zaehler fuer enumerate-Umgeb.	*/
GLOBAL int		iDescLevel;					/* Zaehler fuer description-Umgeb.	*/
GLOBAL int		iListLevel;					/* Zaehler fuer xlist-Umgebungen	*/

GLOBAL BOOLEAN bCalledEndDocument;
GLOBAL BOOLEAN bCalledBeginDocument;


/*	############################################################
	# globale Prototypen
	############################################################	*/
GLOBAL void check_environments_node ( void );

GLOBAL void output_begin_verbatim ( void );
GLOBAL void output_end_verbatim ( void );

GLOBAL void output_begin_linedraw ( void );
GLOBAL void output_end_linedraw ( void );

GLOBAL void output_begin_sourcecode ( void );
GLOBAL void output_end_sourcecode ( void );

GLOBAL void output_begin_comment ( void );
GLOBAL void output_end_comment ( void );

GLOBAL int strlen_indent ( void );
GLOBAL void strcat_indent ( char *s );
GLOBAL void strcpy_indent ( char *s );


GLOBAL void c_begin_quote ( void );
GLOBAL void c_end_quote ( void );

GLOBAL void c_begin_center ( void );
GLOBAL void c_end_center ( void );

GLOBAL void c_begin_flushright ( void );
GLOBAL void c_end_flushright ( void );

GLOBAL void c_begin_flushleft ( void );
GLOBAL void c_end_flushleft ( void );

GLOBAL void c_begin_itemize ( void );
GLOBAL void c_begin_enumerate ( void );
GLOBAL void c_begin_description ( void );
GLOBAL void c_begin_xlist ( void );
GLOBAL void c_begin_blist ( void );
GLOBAL void c_begin_ilist ( void );
GLOBAL void c_begin_tlist ( void );

GLOBAL void c_item ( void );

GLOBAL void c_end_xlist ( void );
GLOBAL void c_end_blist ( void );
GLOBAL void c_end_ilist ( void );
GLOBAL void c_end_tlist ( void );
GLOBAL void c_end_description ( void );
GLOBAL void c_end_enumerate ( void );
GLOBAL void c_end_itemize ( void );

GLOBAL void c_begin_document ( void );
GLOBAL void c_end_document ( void );

GLOBAL void c_begin_appendix ( void );
GLOBAL void c_end_appendix ( void );



GLOBAL void init_module_env ( void );
GLOBAL void init_env_itemchar ( void );


/*	############################################################
	# env.h
	############################################################	*/

