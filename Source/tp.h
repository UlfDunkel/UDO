/*	############################################################
	# @(#) tp.h
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

#define	MAXADDRESS	20

#ifndef UDO_TP_H
#define UDO_TP_H

/*	--------------------------------------------------
	Titelseite
	--------------------------------------------------	*/
typedef struct _titledata			/* ---- Titelseiteninfos ----		*/
{
	char	*title;					/* Titelzeile		*/
	char	*program;				/* Programmname		*/
	char	*date;					/* Datum			*/
	char	*version;				/* Version			*/
	char	*author;				/* Name des Autors	*/
	char	*address[MAXADDRESS+1];	/* Adresse 			*/
	char	*webmastername;			/* Fuer HTML		*/
	char	*webmasteremail;		/* Fuer HTML		*/
	char	*webmastermailurl;		/* Fuer HTML		*/
	char	*webmasterurl;			/* Fuer HTML		*/
	char	*programimage;			/* Bilder statt 	*/
	char	*authorimage;			/* ... Text			*/
	char	*authoricon;			/* -> Modern/Frames	*/
	char	*authoricon_active;		/* -> Modern/Frames	*/
	unsigned int authoriconWidth;
	unsigned int authoriconHeight;
	unsigned int authoriconActiveWidth;
	unsigned int authoriconActiveHeight;
	char	*drc_statusline;
	char	*stg_database;
	char	*htmltitle;				/* <title>			*/

}	TITLEDATA;

#endif /* UDO_TP_H */

/*	############################################################
	# globale Variablen
	############################################################	*/
GLOBAL int			address_counter;
GLOBAL BOOLEAN		called_maketitle;
GLOBAL BOOLEAN		uses_maketitle;

GLOBAL TITLEDATA	titdat;

GLOBAL char			titleprogram[512];

/*	############################################################
	# globale Funktionen
	############################################################	*/
GLOBAL BOOLEAN set_docinfo ( void );
GLOBAL void c_maketitle ( void );
GLOBAL void pch_titlepage ( void );

GLOBAL void init_module_tp ( void );
GLOBAL void init_module_tp_pass2 ( void );
GLOBAL void exit_module_tp ( void );

/*	############################################################
	# tp.h
	############################################################	*/

