/*	############################################################
	# @(#) chr.c
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
#ifndef ID_CHARS_C
#define	ID_CHARS_C
const char *id_chr_c= "@(#) chr.c       22.04.1999";
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "portab.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "commands.h"
#include "msg.h"
#include "str.h"
#include "sty.h"
#include "udo.h"
#include "chr_all.h"
#include "chr_ttf.h"
#include "ansi2dos.h"

#ifdef __TOS__
#include	"chr_tos.h"
#else
#include	"tos2iso.h"
#endif

#ifdef __MSDOS__
#include	"chr_437.h"
#else
#include	"437iso.h"
#endif

#ifdef __MSDOS850__
#include	"chr_850.h"
#else
#include	"850iso.h"
#endif

#ifdef __HPUX_ROMAN8__
#include	"chr_hp8.h"
#else
#include	"hp82iso.h"
#endif

#if __NEXTSTEP__
#include	"chr_next.h"
#else
#include	"next2iso.h"
#endif

/* #if __BEOS__				*/
/* #include	"chr_utf8.h"	*/
/* #else					*/
/* #include	"utf82iso.h"	*/
/* #endif					*/

#include	"utf82iso.h"

#if __MACOS__
#include	"chr_mac.h"
#else
#include	"mac2iso.h"
#endif

#if	USE_LATIN1_CHARSET
#include	"chr_iso.h"
#endif

#include "export.h"
#include "chr.h"

/*	------------------------------------------------------------	*/
#ifndef MAXTEX7BIT
#error	"MAXTEX7BIT not defined!"
#endif

#ifndef	MAXRTF7BIT
#error	"MAXRTF7BIT not defined!"
#endif

#ifndef	MAXWIN7BIT
#error	"MAXWIN7BIT not defined!"
#endif

#ifndef	MAXHTML7BIT
#error	"MAXHTML7BIT not defined!"
#endif

#ifndef	MAXLDS7BIT
#error	"MAXLDS7BIT not defined!"
#endif

#ifndef	MAXHTAG7BIT
#error	"MAXHTAG7BIT not defined!"
#endif

/*	############################################################
	# lokale Variablen
	############################################################	*/

LOCAL BOOLEAN last_aqc_verb;
LOCAL int texinfo_np_counter;	/* Non-Printable-Texinfo-Node-Counter ;-) */


/*	############################################################
	# lokale Prototypen
	############################################################	*/
LOCAL void uni2misc ( char *s );

LOCAL void iso2system ( char *s );
LOCAL void iso2sys ( char *s );

#ifndef __MACOS__
LOCAL void mac2iso ( char *s );
#endif

#ifndef __NEXTSTEP__
LOCAL void next2iso ( char *s );
#endif

LOCAL void tos2iso ( char *s );

#ifndef __HPUX_ROMAN8__
LOCAL void hp82iso ( char *s );
#endif

LOCAL void specials2ascii ( char *s );
LOCAL void specials2ipf ( char *s );
LOCAL void specials2info ( char *s );
LOCAL void specials2win ( char *s );
LOCAL void specials2rtf ( char *s );
LOCAL void texvar2ascii ( char *s );

LOCAL void c_quotes_apostrophes ( char *s,
		const char *aon, const char *aoff,
		const char *qon, const char *qoff );

LOCAL void str2manbold( char *d, const char *s );
LOCAL void str2manunder( char *d, const char *s );


/*	--------------------------------------------------------------	*/


/*	############################################################
	#
	# Deutsches SZ umwandeln
	#
	############################################################	*/

GLOBAL void convert_sz ( char *s )
{
# ifdef __TOS__
	replace_char(s, "\341", "\236");
# else

# if !defined(__MSDOS__) && !defined(__MSDOS850__)
	replace_char(s, "\236", "\341");

#else
	UNUSED(s);
#endif
#endif
}	/* convert_sz */



/*	############################################################
	#
	#	Universellen Zeichensatz in den Systemzeichensatz
	#	bzw. in eines der Zielformate umwandeln.
	#
	############################################################	*/
GLOBAL void uni2ascii ( char *s )
{
	register int i;
	
	if ( s[0]==EOS )
	{	return;
	}

	if ( strstr(s, "(!")==NULL )
	{	return;
	}


	for (i=0; i<UNI2SYSTABSIZE; i++)
	{	replace_all(s, uni2sys[i].uni, (const char *) uni2sys[i].system);
	}

	if (no_umlaute)
	{	umlaute2ascii(s);
	}

}	/* uni2ascii */


LOCAL void uni2misc ( char *s )
{
	register int i;
	
	if ( s[0]==EOS )
	{	return;
	}

	if ( strstr(s, "(!")==NULL )
	{	return;
	}

	switch (desttype)
	{
		case TOTEX:
		case TOPDL:
			for (i=0; i<UNITABLESIZE; i++) replace_all(s, unitab[i].uni, unitab[i].tex) ;
			break;

		case TOHTM:
		case TOMHH:
		case TOLDS:
		case TOHPH:
			for (i=0; i<UNITABLESIZE; i++) replace_all(s, unitab[i].uni, unitab[i].html) ;
			break;

		case TOWIN:
		case TOWH4:
		case TOAQV:
		case TORTF:
			for (i=0; i<UNITABLESIZE; i++) replace_all(s, unitab[i].uni, unitab[i].win) ;
			break;

		case TOPCH:	/* PL10: wie bei uni2ascii */
			for (i=0; i<UNI2SYSTABSIZE; i++)
			{	replace_all(s, uni2sys[i].uni, (const char *) uni2sys[i].system);
			}

			if (no_umlaute)
			{	umlaute2ascii(s);
			}
			break;

		case TOLYX:		/* PL14 */
			for (i=0; i<UNITABLESIZE; i++) replace_all(s, unitab[i].uni, unitab[i].lyx) ;
			break;
	}
	
}	/* uni2misc */



/*	############################################################
	#
	#	ISO-Zeichensatz in den jeweiligen Systemzeichensatz
	#	umwandeln (!code_iso)
	#	iso2system() wandelt IMMER um, iso2sys() nur dann, wenn
	#	nicht in einen Font umgewandelt wird, der nicht ANSI
	#	als Basiszeichensatz verwendet (RTF, WinHelp)
	############################################################	*/

LOCAL void iso2system ( char *s )
{
	/* Optimierter Suchmethode, ohne zeitraubendes strlen() */
	char *ptr;
	int idx;
	
	ptr= s;
	
	while (*ptr!=EOS)
	{
		if ( ((UCHAR) *ptr) > 127 )
		{	idx= ((UCHAR) *ptr)-128;
			if ( iso2sys_item[idx].sys!=EOS )
			{	*ptr= iso2sys_item[idx].sys;
			}
			else
			{	warning_cannot_recode(*ptr, "Latin1", "system charset");
				*ptr= '?';
			}
		}
#ifdef __MSDOS__
		else
		{
			if ( *ptr == '\247' )
			{	*ptr= '\025';
			}
		}
#endif
#ifdef __MSDOS850__
		else
		{
			if ( *ptr == '\247' )
			{	*ptr= '\025';
			}
		}
#endif
		ptr++;
	}

}	/* iso2system */


LOCAL void iso2sys ( char *s )
{
	if (iCharset==CODE_LAT1)	/* PL14: TOLYX */
	{	if ( desttype==TOWIN || desttype==TOWH4 || desttype==TORTF || desttype==TOAQV || desttype==TOLYX )
		{	return;
		}
	}
	
#if USE_LATIN1_CHARSET
		/* r6pl2: System benutzt Latin1-Zeichensatz? Dann ist */
		/* eine weitere Umwandlung/Kontroll unnoetig! */
		UNUSED(s);
		return;
#else
	iso2system(s);
#endif
}	/* iso2sys */



/*	############################################################
	#
	#	Mac-Zeichensatz in ISO-Zeichensatz umwandeln (!code_mac)
	#
	############################################################	*/

#ifndef __MACOS__

LOCAL void mac2iso ( char *s )
{
	/* Optimierter Suchmethode, ohne zeitraubendes strlen() */
	char *ptr;
	int idx;
	
	ptr= s;
	
	while (*ptr!=EOS)
	{
		if ( ((UCHAR) *ptr) > 127 )
		{	idx= ((UCHAR) *ptr)-128;
			if ( mac2iso_item[idx].iso!=EOS )
			{	*ptr= mac2iso_item[idx].iso;
			}
			else
			{	warning_cannot_recode(*ptr, "MacOS", "Latin1");
				*ptr= '?';
			}
		}
		ptr++;
	}
}	/* mac2iso */

#endif	/* __MACOS__ */


/*	############################################################
	#
	#	UTF-8 in ISO-Zeichensatz umwandeln (!code [utf-8])
	#
	############################################################	*/

/* #ifndef __BEOS__ */

LOCAL void utf82iso ( char *s )
{
	/* Optimierter Suchmethode, ohne zeitraubendes strlen() */
	char *ptr, sUTF[16], onechar[1];
	int i, bytes;
	BOOLEAN found;
	
	ptr= s;
	
	if (*ptr==EOS)
	{	return;
	}

	strcpy(onechar, " ");
	
	while (*ptr!=EOS)
	{
		if ( ((UCHAR) *ptr > 127) && (((UCHAR) *ptr & 0xC0) != 0x80 ) )
		{
			/* UTF-8-Zeichen gefunden, nun herausfinden, wieviele Bytes insgesamt vorliegen */
			bytes= ((UCHAR) *ptr >> 5) & 0x03;

			switch (bytes)
			{
				case 2:
					/* 0xC.. , also zwei Bytes */
					if (ptr[1]!=EOS)
					{
						found= FALSE;
						for (i=0; i<128; i++)
						{
							if ((UCHAR) ptr[0]==utf82iso_item[i].utf8[0] && (UCHAR) ptr[1]==utf82iso_item[i].utf8[1])
							{
								onechar[0]= utf82iso_item[i].latin1;
								qreplace_once(ptr, (char *) utf82iso_item[i].utf8, 2, onechar, 1);
								found= TRUE;
								break;
							}
						}
						if (!found)
						{
							sprintf(sUTF, "%X %X", ptr[0], ptr[1]);
							warning_cannot_recode_utf8(sUTF, "Latin1");
							ptr++;
						}
					}
					break;
				case 3:
					if (ptr[1]!=EOS && ptr[2]!=EOS)
					{	/* 0xE.. , also drei Bytes */
						sprintf(sUTF, "%X %X %X", ptr[0], ptr[1], ptr[2]);
						warning_cannot_recode_utf8(sUTF, "Latin1");
						ptr+= 2;
					}
					break;
				default:
					warning_cannot_recode(*ptr, "UTF-8", "Latin1");
					break;

			}

		}
		ptr++;
	}
}	/* utf82iso */

/* #endif */	/* __BEOS__ */

	
/*	##################################################################
	#
	#	NextStep-Zeichensatz in ISO-Zeichensatz umwandeln (!code_next)
	#
	##################################################################	*/

#ifndef __NEXTSTEP__

LOCAL void next2iso ( char *s )
{
	/* Optimierter Suchmethode, ohne zeitraubendes strlen() */
	char *ptr;
	int idx;
	
	ptr= s;
	
	while (*ptr!=EOS)
	{
		if ( ((UCHAR) *ptr) > 127 )
		{	idx= ((UCHAR) *ptr)-128;
			if ( next2iso_item[idx].iso!=EOS )
			{	*ptr= next2iso_item[idx].iso;
			}
			else
			{	warning_cannot_recode(*ptr, "NeXTSTep", "Latin1");
				*ptr= '?';
			}
		}
		ptr++;
	}
}	/* next2iso */

#endif	/* __NEXTSTEP__ */



/*	############################################################
	#
	#	Atari-Zeichensatz nach ISO umwandeln (!code_tos)
	#
	############################################################	*/

#ifndef __TOS__

LOCAL void tos2iso ( char *s )
{
	/* Optimierter Suchmethode, ohne zeitraubendes strlen() */
	char *ptr;
	int idx;
	
	ptr= s;
	
	while (*ptr!=EOS)
	{
		if ( ((UCHAR) *ptr) > 127 )
		{	idx= ((UCHAR) *ptr)-128;
			if ( tos2iso_item[idx].iso!=EOS )
			{	*ptr= tos2iso_item[idx].iso;
			}
			else
			{	warning_cannot_recode(*ptr, "TOS", "Latin1");
				*ptr= '?';
			}
		}
		ptr++;
	}
}	/* tos2iso */

#endif	/* __TOS__ */


/*	############################################################
	#
	#	Codepage 437 nach ISO umwandeln (!code [cp437])
	#
	############################################################	*/

#ifndef	__MSDOS__

LOCAL void cp437iso ( char *s )
{
	/* Optimierter Suchmethode, ohne zeitraubendes strlen() */
	char *ptr;
	int idx;
	
	ptr= s;
	
	while (*ptr!=EOS)
	{
		if ( ((UCHAR) *ptr) > 127 )
		{	idx= ((UCHAR) *ptr)-128;
			if ( cp437iso_item[idx].iso!=EOS )
			{	*ptr= cp437iso_item[idx].iso;
			}
			else
			{	warning_cannot_recode(*ptr, "cp437", "Latin1");
				*ptr= '?';
			}
		}
		ptr++;
	}
}	/* cp437iso */


#endif	/* __MSDOS__ */


/*	############################################################
	#
	#	Codepage 850 nach ISO umwandeln (!code [cp437])
	#
	############################################################	*/

#ifndef	__MSDOS850__

LOCAL void cp850iso ( char *s )
{
	/* Optimierter Suchmethode, ohne zeitraubendes strlen() */
	char *ptr;
	int idx;
	
	ptr= s;
	
	while (*ptr!=EOS)
	{
		if ( ((UCHAR) *ptr) > 127 )
		{	idx= ((UCHAR) *ptr)-128;
			if ( cp850iso_item[idx].iso!=EOS )
			{	*ptr= cp850iso_item[idx].iso;
			}
			else
			{	warning_cannot_recode(*ptr, "cp850", "Latin1");
				*ptr= '?';
			}
		}
		ptr++;
	}
}	/* cp850iso */

#endif	/* __MSDOS850__ */


#if !defined(__MSDOS__) && !defined(__MSDOS850__)
LOCAL void section2iso ( char *s )
{
	char *ptr;
	
	ptr= s;
	
	while (*ptr!=EOS)
	{
		if ( ((UCHAR) *ptr) == '\025' )
		{	*ptr= '\247';
		}
		ptr++;
	}
}	/* section2iso */
#endif


/*	############################################################
	#
	#	HP-Roman-8-Zeichensatz nach ISO umwandeln (!code_hp8)
	#
	############################################################	*/

#ifndef __HPUX_ROMAN8__

LOCAL void hp82iso ( char *s )
{
	/* Optimierter Suchmethode, ohne zeitraubendes strlen() */
	char *ptr;
	int idx;
	
	ptr= s;
	
	while (*ptr!=EOS)
	{
		if ( ((UCHAR) *ptr) > 127 )
		{	idx= ((UCHAR) *ptr)-128;
			if ( hp82iso_item[idx].iso!=EOS )
			{	*ptr= hp82iso_item[idx].iso;
			}
			else
			{	warning_cannot_recode(*ptr, "HP Roman 8", "Latin1");
				*ptr= '?';
			}
		}
		ptr++;
	}
}	/* hp82iso */

#endif	/* __HPUX_ROMAN8__ */



GLOBAL void recode ( char *zeile, int char_set )	/* PL6 */
{
	char *ptr;	/*r6pl2: es wird zunaechst das erste 8-Bit-Zeichen */
				/* gesucht, da in *2iso() und iso2sys() nicht die */
				/* 7-Bit-Zeichen zweimal uebersprungen werden muessen */
				/* Ist kein 8-Bit-Zeichen enthalten, so spart man sich */
				/* zwei Aufrufe mit nutzlosen 128-Schritt-Schleifen */
	
	switch (char_set)
	{

#if !USE_LATIN1_CHARSET
		case CODE_LAT1:
			iso2sys(zeile);
			break;
#endif

#ifndef __MACOS__
		case CODE_MAC:
			ptr= get_8bit_ptr(zeile);
			if (ptr)
			{	mac2iso(ptr);
				iso2sys(ptr);
			}
			break;
#endif

#ifndef	__TOS__
		case CODE_TOS:
			ptr= get_8bit_ptr(zeile);
			if (ptr)
			{	tos2iso(ptr);
				iso2sys(ptr);
			}
			break;
#endif

#ifndef	__MSDOS__
		case CODE_437:
			ptr= get_8bit_ptr(zeile);
			if (ptr)
			{	cp437iso(ptr);
				iso2sys(ptr);
			}
			ptr= get_section_ptr(zeile);
			if (ptr)
			{	section2iso(ptr);
			}
			break;
#endif

#ifndef	__MSDOS850__
		case CODE_850:
			ptr= get_8bit_ptr(zeile);
			if (ptr)
			{	cp850iso(ptr);
				iso2sys(ptr);
			}
/*			ptr= get_section_ptr(zeile);
			if (ptr)
			{	section2iso(ptr);
			}
*/
			break;
#endif

#ifndef	__HPUX_ROMAN8__
		case CODE_HP8:
			ptr= get_8bit_ptr(zeile);
			if (ptr)
			{	hp82iso(ptr);
				iso2sys(ptr);
			}
			break;
#endif

#ifndef	__NEXTSTEP__
		case CODE_NEXT:
			ptr= get_8bit_ptr(zeile);
			if (ptr)
			{	next2iso(ptr);
				iso2sys(ptr);
			}
			break;
#endif

/* #ifndef	__BEOS__ */
		case CODE_UTF8:
			ptr= get_8bit_ptr(zeile);
			if (ptr)
			{	utf82iso(ptr);
				iso2sys(ptr);
			}
			break;
/* #endif */
	}

}	/* recode */


LOCAL void recode_allways ( char *zeile, int char_set )	/* PL8 */
{
	switch (char_set)
	{

#if !USE_LATIN1_CHARSET
		case CODE_LAT1:
			iso2system(zeile);
			break;
#endif

#ifndef __MACOS__
		case CODE_MAC:
			mac2iso(zeile);
			iso2system(zeile);
			break;
#endif

#ifndef	__TOS__
		case CODE_TOS:
			tos2iso(zeile);
			iso2system(zeile);
			break;
#endif

#ifndef	__MSDOS__
		case CODE_437:
			cp437iso(zeile);
			iso2system(zeile);
			break;
#endif

#ifndef	__MSDOS850__
		case CODE_850:
			cp850iso(zeile);
			iso2system(zeile);
			break;
#endif

#ifndef	__HPUX_ROMAN8__
		case CODE_HP8:
			hp82iso(zeile);
			iso2system(zeile);
			break;
#endif

#ifndef	__NEXTSTEP__
		case CODE_NEXT:
			next2iso(zeile);
			iso2system(zeile);
			break;
#endif
	}

}	/* recode_allways */


/*	############################################################
	#
	# String mit Windows-Zeichen wieder zurueckwandeln
	# (wird fuer die TITLE-Option benoetigt)
	#
	############################################################	*/
GLOBAL void win2sys ( char *s )
{
	register int i;
	char one[2];
	char four[5];
	char *ptr;
	
	if (s[0]==EOS)
	{	return;
	}
	
	strcpy(one, " ");
	
	for (i=0; i<128; i++)
	{	if ( chrtab[i].ansi[0]=='\\' )
		{	one[0]= chrtab[i].system;
			replace_all(s, chrtab[i].ansi, one);
		}
	}
	
	/* Noch das sz anpassen */
	replace_char(s, "\236", "\341");

	/* Nicht umwandelbare Zeichen entfernen */
	strcpy(four, "    ");
	while ( (ptr=strstr(s, "\\'"))!=NULL )
	{	four[0]= ptr[0];
		four[1]= ptr[1];
		four[2]= ptr[2];
		four[3]= ptr[3];
		delete_all(s, four);
	}
	
}	/* win2sys */


/*	############################################################
	#
	# String mit HTML-Zeichen in Systemzeichen wandeln
	#
	############################################################	*/
GLOBAL void html2sys ( char *s )
{
	register int i;
	char one[2];
	
	if (s[0]==EOS)
	{	return;
	}
	
	strcpy(one, " ");
	
	for (i=0; i<128; i++)
	{
		one[0]= chrtab[i].system;
		replace_all(s, chrtab[i].html, one);
	}

	for (i=0; i<MAXHTML7BIT; i++)
	{
		one[0]= html7bit[i].c;
		replace_all(s, html7bit[i].quoted, one);
	}
	
}	/* html2sys */


/*	############################################################
	#
	# String mit Windows-Zeichen in DOS-Zeichen wandeln
	#
	############################################################	*/
GLOBAL void ansi2dos ( char *s )
{
	register int idx;
	char *ptr;
	
	ptr= s;

	while (*ptr!=EOS)
	{
		if ((UCHAR) *ptr > 127)
		{	idx= ((UCHAR) *ptr)-128;
			if ( ansi2dos_item[idx].dos!=EOS )
			{	*ptr= ansi2dos_item[idx].dos;
			}
			/*
			else
			{	warning_cannot_recode(*ptr, "Latin1", "system charset");
				*ptr= '?';
			}
			*/
		}
		ptr++;
	}
}	/* ansi2dos */




/*	############################################################
	#
	# Breiten von Strings in twip (1/1440" bzw. 1/20 pt)
	# berechnen fuer WinHelp.
	#
	############################################################	*/
GLOBAL int calc_ttf_twip ( const char *s, const int font, const int style )
{
	int pixel, twip;
	size_t i;
	char d[512];
	
	if ( s[0]==EOS )
	{	return(0);
	}
	
	strcpy(d, s);
	recode_allways(d, iCharset);
	strcat(d, "W");					/* Breitenausgleiche */

	pixel= 0;
	
	switch (font)
	{	
		case TTF_TIMES:
		{	switch (style)
			{
				case TTF_BOLD:
					for (i=0; i<strlen(d); i++)
					{	pixel+= width_times_11_bold[(UCHAR) d[i]];
						pixel++;
					}
					break;
				case TTF_ITALIC:
					for (i=0; i<strlen(d); i++)
					{	pixel+= width_times_11_italic[(UCHAR) d[i]];
						pixel++;
					}
					break;
				default:
					for (i=0; i<strlen(d); i++)
					{	pixel+= width_times_11_regular[(UCHAR) d[i]];
						pixel++;
					}
					break;
			}
			break;
		}

		case TTF_COURIER:
		{	switch (style)
			{
				case TTF_BOLD:
					for (i=0; i<strlen(d); i++)
					{	pixel+= width_courier_10_bold[(UCHAR) d[i]];
						pixel++;
					}
					break;
				case TTF_ITALIC:
					for (i=0; i<strlen(d); i++)
					{	pixel+= width_courier_10_italic[(UCHAR) d[i]];
						pixel++;
					}
					break;
				default:
					for (i=0; i<strlen(d); i++)
					{	pixel+= width_courier_10_regular[(UCHAR) d[i]];
						pixel++;
					}
					break;
			}
			break;
		}

		default:
		{	switch (style)
			{
				case TTF_BOLD:
					for (i=0; i<strlen(d); i++)
					{	pixel+= width_arial_10_bold[(UCHAR) d[i]];
						pixel++;
					}
					break;
				case TTF_ITALIC:
					for (i=0; i<strlen(d); i++)
					{	pixel+= width_arial_10_italic[(UCHAR) d[i]];
						pixel++;
					}
					break;
				default:
					for (i=0; i<strlen(d); i++)
					{	pixel+= width_arial_10_regular[(UCHAR) d[i]];
						pixel++;
					}
					break;
			}
			break;
		}
	}

	/* pt	= pixel * 72 / 100						*/
	/* twip	= pixel * 72 / 100 * 20 = pixel * 14.4	*/
	/* passt aber nicht, daher etwas mehr!			*/

	twip= (int) (pixel*14.4);
	
	return(twip);
}	/* calc_ttf_twip */


/*	############################################################
	#
	# Normale Ersetzungsroutinen, die unerlaubte Zeichen aus
	# Nodes entfernen und UDO-Spezialitaeten bearbeiten
	#
	############################################################	*/


/*	------------------------------------------------------------
	replace_udo_quotes
	UDO-Befehle muessen gequotet werden, falls sie im Text
	vorkommen sollen. Beispiel: !/node statt !node
	<->	s:	String
	------------------------------------------------------------	*/
GLOBAL void replace_udo_quotes (char *s)
{
	qreplace_all(s, "!/", 2, "!", 1);			/* !/     -> !    */
}	/* replace_udo_quotes */



/*	------------------------------------------------------------
	replace_all_copyright()
	Bei Pure C Help wird bei Copyright auf die Borland-Seite
	verwiesen, und nicht auf einen eigenen Node. Daher die
	Zeichenkette anpassen. Nicht schoen, aber zweckmaessig.
	<->	s:	String
	------------------------------------------------------------	*/
GLOBAL void replace_all_copyright (char *s)
{
	if (desttype==TOPCH)
	{
		qreplace_all(s, "Copyright", 9, "Copy-Right", 10);
	}
}	/* replace_all_copyright */


/*	------------------------------------------------------------
	delete_all_divis()
	Loeschen UDO-interner Trennmarken
	<->	s:	String mit Trennmarken
	------------------------------------------------------------	*/
GLOBAL void delete_all_divis ( char *s )
{
	qdelete_all(s, DIVIS_S, DIVIS_S_LEN);
}	/* delete_all_divis */



/*	------------------------------------------------------------
	Umwandeln von Leerzeichen in feste Leerzeichen und umgekehrt
	------------------------------------------------------------	*/
GLOBAL void indent2space ( char * s)
{
	#if (INDENT_S_LEN==1)
		replace_char(s, INDENT_S, " ");
	#else
		qreplace_all(s, INDENT_S, INDENT_S_LEN, " ", 1);
	#endif
}

GLOBAL void space2indent ( char * s)
{
	#if (INDENT_S_LEN==1)
		replace_char(s, " ", INDENT_S);
	#else
		qreplace_all(s, " ", 1, INDENT_S, INDENT_S_LEN);
	#endif
}


GLOBAL void nbsp2space ( char * s)
{
	#if (NBSP_S_LEN==1)
		replace_char(s, NBSP_S, " ");
	#else
		qreplace_all(s, NBSP_S, NBSP_S_LEN, " ", 1);
	#endif
}

GLOBAL void space2nbsp ( char * s)
{
	#if (NBSP_S_LEN==1)
		replace_char(s, " ", NBSP_S);
	#else
		qreplace_all(s, " ", 1, NBSP_S, NBSP_S_LEN);
	#endif
}


/*	------------------------------------------------------------
	umlaute2ascii()
	Ersetzen von deutschen Umlauten durch die 7bit-Versionen
	<->	s:	String, in dem Umlaute ersetzt werden sollen
	------------------------------------------------------------	*/
GLOBAL void umlaute2ascii ( char *s )
{
	int id;
	size_t	i;
	char	one[2]= {0, 0};

	if (s[0]==EOS)
	{	return;
	}

	i= 0;

	while (s[i]!=EOS)
	{	if ( ((UCHAR) s[i]) > 127 )
		{	id= ((UCHAR) s[i])-128;
			if (chrtab[id].ascii[0]!=EOS)
			{	one[0]= s[i];
				replace_all(s+i, one, chrtab[id].ascii);
			}
		}
		i++;
	}
}	/* umlaute2ascii */



/*	------------------------------------------------------------
	label2tex()
	Ersetzen bzw. Loeschen aller Zeichen, die in einem Label
	von LaTeX "\label{...}" nicht vorkommen duerfen. 
	<->	s:	String, in dem bereits Sonderzeichen an LaTeX
			angepasst wurden.
	------------------------------------------------------------	*/
GLOBAL void label2tex ( char *s )
{
	qreplace_all(s, "{\\\"a}",	4,	"ae",	2);
	qreplace_all(s, "{\\\"o}",	4,	"oe",	2);
	qreplace_all(s, "{\\\"u}",	4,	"ue",	2);
	qreplace_all(s, "{\\\"s}",	4,	"ss",	2);
	qreplace_all(s, "{\\\"A}",	4,	"Ae",	2);
	qreplace_all(s, "{\\\"O}",	4,	"Oe",	2);
	qreplace_all(s, "{\\\"U}",	4,	"Ue",	2);
	qreplace_all(s, "\\_",	2,	"-",	1);
	qreplace_all(s, "_",	1,	"-",	1);
	qreplace_all(s, "#",	1,	"035-",	4);
	qreplace_all(s, "$",	1,	"036-",	4);
	qreplace_all(s, "%",	1,	"037-",	4);
	qreplace_all(s, "&",	1,	"038-",	4);
	qreplace_all(s, "~",	1,	"126-",	4);
	qreplace_all(s, "^",	1,	"094-",	4);
	qreplace_all(s, "{",	1,	"123-",	4);
	qreplace_all(s, "}",	1,	"125-",	4);

	qdelete_all(s, "\\", 1);
	qreplace_all(s, "\"'",	2,	"'",	1);
	qreplace_all(s, "\"`",	2,	"`",	1);
}	/* label2tex */



/*	------------------------------------------------------------
	label2html() (r6pl2)
	Ersetzen bzw. Loeschen aller Zeichen, die in einem Anchor
	von HTML nicht vorkommen duerfen. Gemaess SGML companion
	sind erlaubt: "a-z", "A-Z", "0-9", "$+.-_". Alle anderen
	Codes werden durch _xx dargestellt (_ und Hexcode)
	HTML-4.0-Spec:	"ID and NAME tokens must begin with a letter
					([A-Za-z]) and may be followed by any number
					of letters, digits ([0-9]), hyphens ("-"),
					underscores ("_"), colons (":"), and
					periods (".")."
	Beispiel: "Ein Label" -> "Ein_20Label"
	------------------------------------------------------------	*/
GLOBAL void label2html ( char *s )
{
	char *ptr, val[16];
	char one[2]= {0, 0};

	ptr= s;

	while (*ptr!=EOS)
	{
		if (*ptr>='a' && *ptr<='z')	goto LABEL2HTML_NEXT;
		if (*ptr>='A' && *ptr<='Z')	goto LABEL2HTML_NEXT;
		if (*ptr>='0' && *ptr<='9')	goto LABEL2HTML_NEXT;
		if (*ptr=='-')	goto LABEL2HTML_NEXT;
		if (*ptr=='_')	goto LABEL2HTML_NEXT;
		if (*ptr==':')	goto LABEL2HTML_NEXT;
		if (*ptr=='.')	goto LABEL2HTML_NEXT;
		
		sprintf(val, "_%X", (UCHAR) *ptr);
		one[0]= *ptr;
		replace_once(ptr, one, val);
		
		LABEL2HTML_NEXT:
		ptr++;
	}

	/* Labelname muss mit einem Buchstaben beginnen (siehe Spec) */
	if (*s>='a' && *s<='z')	return;
	if (*s>='A' && *s<='Z')	return;
	strinsert(s, "UDO_");
	
}	/* label2html */


/*	------------------------------------------------------------
	node2winhelp
	Indexnamen fuer WinHelp. WinHelp mag keine Umlaute und
	Sonderzeichen in einer Referenz. Leerzeichen werden durch
	Underscores ersetzt, alles andere durch Hexwerte.
	------------------------------------------------------------	*/
GLOBAL void node2winhelp (char *n)
{
	char t[512], v[32];
	size_t i;

	if ( n[0]==EOS) return;
	
	umlaute2ascii(n);
	replace_udo_quotes(n);
	delete_all_divis(n);

	t[0]= EOS;	
	for (i=0; i<strlen(n); i++)
	{	
		if ( (n[i]>='0' && n[i]<='9') || (n[i]>='a' && n[i]<='z') || (n[i]>='A' && n[i]<='Z') )
		{	chrcat(t, n[i]);
		}
		else
		{	if ( n[i]==' ' || n[i]=='_' )	/* PL10: || n[i]=='_' */
			{	chrcat(t, '_');
			}
			else
			{	sprintf(v, "_%X", (UCHAR) n[i]);
				strcat(t, v);
			}
		}
	}

	/*	PL6: Workaround. Der HC stuerzt bei sehr langen Strings ab.	*/
	if (strlen(t)>80)
	{	t[81]= EOS;
	}

	strcpy(n, t);
	
}	/* node2winhelp */



/*	------------------------------------------------------------
	node2WinAutoID
	------------------------------------------------------------	*/
GLOBAL void node2WinAutoID (char *id, const char *n)
{
	char s[512];
	size_t i;

	id[0]= EOS;

	if ( n[0]==EOS) return;
	
	strcpy(s, n);
	win2sys(s);
	umlaute2ascii(s);
	replace_udo_quotes(s);
	delete_all_divis(s);

	id[0]= EOS;	
	for (i=0; i<strlen(s); i++)
	{	
		if ( (s[i]>='0' && s[i]<='9') || (s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || s[i]=='_' )
		{	chrcat(id, s[i]);
		}
	}

}	/* node2WinID */


/*	------------------------------------------------------------
	node2NrWinhelp
	->	li:	interne Labelnummer (lab[]->, nicht toc[]->!!)
	<->	s:	Der Node-Kontextstring
	------------------------------------------------------------	*/
GLOBAL void node2NrWinhelp ( char *s, int li )
{	sprintf(s, "UDON%05X", li+1);
}

/*	------------------------------------------------------------
	alias2NrWinhelp
	->	li:	interne Labelnummer (lab[]->, nicht toc[]->!!)
	<->	s:	Der Node-Kontextstring
	------------------------------------------------------------	*/
GLOBAL void alias2NrWinhelp ( char *s, int li )
{	sprintf(s, "UDOA%05X", li+1);
}

/*	------------------------------------------------------------
	label2NrWinhelp
	->	li:	interne Labelnummer (lab[]->, nicht toc[]->!!)
	<->	s:	Der Label-Kontextstring
	------------------------------------------------------------	*/
GLOBAL void label2NrWinhelp ( char *s, int li )
{	sprintf(s, "UDOL%05X", li+1);
}


/*	------------------------------------------------------------
	node2NrIPF
	->	li:	interne Labelnummer (lab[]->, nicht toc[]->!!)
	<->	s:	Der Node-Kontextstring
	------------------------------------------------------------	*/
GLOBAL void node2NrIPF ( char *s, int li )
{	sprintf(s, "UDON%05X", li+1);
}

/*	------------------------------------------------------------
	alias2NrIPF
	->	li:	interne Labelnummer (lab[]->, nicht toc[]->!!)
	<->	s:	Der Node-Kontextstring
	------------------------------------------------------------	*/
GLOBAL void alias2NrIPF ( char *s, int li )
{	sprintf(s, "UDOA%05X", li+1);
}

/*	------------------------------------------------------------
	label2NrIPF
	->	li:	interne Labelnummer (lab[]->, nicht toc[]->!!)
	<->	s:	Der Label-Kontextstring
	------------------------------------------------------------	*/
GLOBAL void label2NrIPF ( char *s, int li )
{	sprintf(s, "UDOL%05X", li+1);
}


/*	------------------------------------------------------------
	node2pchelp()
	Pure-C-Help mag keine Anfuehrungszeichen
	<->	s:	String, der als Label oder Node benutzt werden soll.
	------------------------------------------------------------	*/
GLOBAL void node2pchelp ( char *s )
{
	qreplace_all(s, "\"", 1, "_0x20_", 6);
}	/* node2pchelp */



/*	------------------------------------------------------------
	node2stg() / index2stg()
	Ersetzen bzw. Loeschen aller Zeichen, die in einem Label
	des ST-Guide (@symbol ari "..." nicht vorkommen duerfen. 
	Die Funktionen sind noch identisch, aber das kann sich
	ja irgendwann einmal aendern.
	<->	s:	String, der als Label oder Node benutzt werden soll.
	------------------------------------------------------------	*/
GLOBAL void node2stg ( char *s )
{
	qreplace_all(s, "\"", 1, "\\\"", 2);
}	/* node2stg */

GLOBAL void index2stg ( char *s )
{
	qreplace_all(s, "\"", 1, "\\\"", 2);
}	/* index2stg */


/*	------------------------------------------------------------
	replace_2at_by_1at() / replace_1at_by_2at()
	@@ durch @ setzen bzw. @ durch @@
	<->	s:	String, der als Label oder Node benutzt werden soll.
	------------------------------------------------------------	*/
GLOBAL void replace_2at_by_1at ( char *s )
{
	qreplace_all(s, "@@", 2, "@", 1);
}	/* replace_2at_by_1at */


GLOBAL void replace_1at_by_2at ( char *s )
{
	qreplace_all(s, "@", 1, "@@", 2);
}	/* replace_2at_by_1at */



/*	------------------------------------------------------------
	node2vision()
	In einem Topic fuer Turbo Vision Help duerfen nur Zeichen
	vorkommen, die auch in C oder Pascal als Funktionsnamen
	erlaubt sind.
	<->	s:	String
	------------------------------------------------------------	*/
GLOBAL void node2vision (char *n)
{
	/* genau wie bei node2winhelp */
	/* Strings werden noch nicht gekuerzt */
	/* <???> Testen, ob TVH mit langen Namen klarkommt */
	
	char t[512], v[32];
	size_t i;

	if ( n[0]==EOS) return;
	
	umlaute2ascii(n);
	replace_udo_quotes(n);
	delete_all_divis(n);
	replace_udo_tilde(n);
	replace_udo_nbsp(n);

	t[0]= EOS;	
	for (i=0; i<strlen(n); i++)
	{	
		if ( (n[i]>='0' && n[i]<='9') || (n[i]>='a' && n[i]<='z') || (n[i]>='A' && n[i]<='Z') )
		{	chrcat(t, n[i]);
		}
		else
		{	if ( n[i]==' ' || n[i]=='_' )
			{	chrcat(t, '_');
			}
			else
			{	sprintf(v, "_%X", (UCHAR) n[i]);
				strcat(t, v);
			}
		}
	}

	strcpy(n, t);

}	/* node2vision */





/*	------------------------------------------------------------
	node2texinfo()
	In einem @node duerfen bei Texinfo einige Zeichen nicht
	auftauchen. Diese werden entfernt. PL15: Wenn der Titel
	hingegen keine alphanumerischen Zeichen enthaelt, so werden
	alle Zeichen im Titel durch Ascii/Hexcodes ersetzt.
	<->	s:	String (Kapitelueberschrift)
	------------------------------------------------------------	*/
GLOBAL void node2texinfo (char *s)
{
	size_t	sl, i;
	char d[512], a[32], c;
	BOOLEAN has_an;				/* has_alphanumeric */
	
	if ( s[0]==EOS) return;
	
	replace_udo_quotes(s);
	delete_all_divis(s);


	qreplace_all(s, "@dots{}", 7, "...", 3);
	qreplace_all(s, "@minus{}", 8, "-", 1);

	sl= strlen(s);
	has_an= FALSE;
	for (i=0; i<sl; i++)
	{	c= s[i];
		if ( (c>='A' && c<='Z') || (c>='a' && c<='z') || (c>='0' && c<='9') )
		{	has_an= TRUE;
			break;
		}
	}

	if (has_an)
	{	/* Die folgenden Zeichen mag Info nicht in einem String */	
		qdelete_all(s, ",", 1);
		qdelete_all(s, ";", 1);
		qdelete_all(s, ":", 1);
		qdelete_all(s, "'", 1);
		qdelete_all(s, "`", 1);
		qdelete_all(s, "\"", 1);
		qdelete_all(s, ")", 1);
		qdelete_all(s, "(", 1);

		/* Einen Punkt am Ende des Titels mag Info gar nicht */
		sl= strlen(s);
		while ( sl>0 && s[sl-1]=='.')
		{	s[sl-1]= EOS;
			sl--;
		}
		qreplace_all(s, ". ", 2, ".", 1);

		/* Nun noch die doppelten Leerzeichen herausschmeissen */	
		while ( qreplace_all(s, "  ", 2, " ", 1) ) ;
	}
	else
	{	/* PL15: ASCII-Codes einsetzen */
		sl= strlen(s);
		strcpy(d, s);
		s[0]= EOS;

		for (i=0; i<sl; i++)
		{	sprintf(a, "%d-", d[i]);
			strcat(s, a);
		}
		/* Noch das letzte "-" entfernen */
		s[strlen(s)-1]= EOS;		
	}
	
}	/* node2texinfo */



/*	------------------------------------------------------------
	Umwandlung von Tilden (feste Leerzeichen) und quotierten
	Tilden (Tilden):
		c_tilde():				Tilden und quotierte Tilden
								durch interne Sequenzen ersetzen.
		replace_udo_tilde():	Interne Sequenz durch Befehle
								ersetzen, die im jeweiligen
								Format eine Tilde (~) anzeigen.
		replace_udo_nbsp():		Interne Sequenz fuer ein festes
								Leerzeichen durch jeweiligen
								Formatbefehl ersetzen.
		convert_tilde():		Alles in einem Abwasch erledigen
	------------------------------------------------------------	*/
GLOBAL void c_tilde ( char *s )
{
	qreplace_all(s, "!~", 2, TILDE_S, TILDE_S_LEN);	/* Tilde ~ */
	#if (NBSP_S_LEN==1)
		replace_char(s, "~", NBSP_S);	/* non breaking space */
	#else
		qreplace_all(s, "~", 1, NBSP_S, NBSP_S_LEN);	/* non breaking space */
	#endif

}	/*c_tilde*/


GLOBAL void replace_udo_tilde ( char * s)
{
	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
			qreplace_all(s, TILDE_S, TILDE_S_LEN, "\\symbol{126}", 12);
			break;
		case TOLYX:
			qreplace_all(s, TILDE_S, TILDE_S_LEN, "~", 1);
			break;
		case TOLDS:
			qreplace_all(s, TILDE_S, TILDE_S_LEN, "&tilde;", 7);
			break;
		default:
			#if (TILDE_S_LEN==1)
				replace_char(s, TILDE_S, "~");
			#else
				qreplace_all(s, TILDE_S, TILDE_S_LEN, "~", 1);
			#endif
			break;			
	}
}	/* replace_udo_tilde */



GLOBAL void replace_udo_nbsp ( char * s)
{
	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
			#if (NBSP_S_LEN==1)
				replace_char(s, NBSP_S, "~");
			#else
				qreplace_all(s, NBSP_S, NBSP_S_LEN, "~", 1);
			#endif
			break;
		case TOLYX:
			qreplace_all(s, NBSP_S, NBSP_S_LEN, "\\protected_separator ", 21);
			break;
		case TOWIN:
		case TOWH4:
		case TORTF:
		case TOAQV:
			qreplace_all(s, NBSP_S, NBSP_S_LEN, "\\~", 2);
			break;
		case TOHTM:
		case TOMHH:
			qreplace_all(s, NBSP_S, NBSP_S_LEN, "&nbsp;", 6);
			break;
		case TOIPF:
			qreplace_all(s, NBSP_S, NBSP_S_LEN, "&rbl.", 5);	/* r6pl7 */
			break;
		default:
			#if (NBSP_S_LEN==1)
				replace_all(s, NBSP_S, " ");
			#else
				qreplace_all(s, NBSP_S, NBSP_S_LEN, " ", 1);
			#endif
			break;			
	}
}	/* replace_udo_nbsp */


GLOBAL void convert_tilde ( char *s )
{
	c_tilde(s);
	replace_udo_tilde(s);
	replace_udo_nbsp(s);
}	/* convert_tilde */


/*	------------------------------------------------------------
	c_divis()
	Ersetzen der UDO-Trennmarke !- durch eine interne Marke
	<->	s:	String
	------------------------------------------------------------	*/
GLOBAL void c_divis ( char *s )
{
	switch (desttype)
	{
		case TOTEX:
		case TOPDL:
			qreplace_all(s, "!-", 2, "\\-", 2);
			break;
		case TORTF:
			qreplace_all(s, "!-", 2, "\\-", 2);	/*r6pl5*/
			break;
		case TOSTG:
		case TOAMG:
		case TOASC:
		case TODRC:
		case TOMAN:
		case TONRO:
		case TOPCH:
		case TOSRC:
		case TOSRP:
			qreplace_all(s, "!-", 2, DIVIS_S, DIVIS_S_LEN);
			break;
		default:
			qdelete_all(s, "!-", 2);
			break;
	}
}	/* c_divis */



/*	------------------------------------------------------------
	specials2ascii()
	Ersetzen von UDO-Spezialbefehlen durch ASCII-Versionen
	<->	s:	String
	------------------------------------------------------------	*/
LOCAL void specials2ascii ( char *s )
{
	qreplace_all(s, "!..", 3, "...", 3);
	
	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "-", 1);
	qreplace_all(s, "--", 2, "-", 1);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}

/*	------------------------------------------------------------
	specials2ipf()
	Ersetzen von UDO-Spezialbefehlen durch IPF-Versionen
	<->	s:	String
	------------------------------------------------------------	*/
LOCAL void specials2ipf ( char *s )
{
	qreplace_all(s, "!&per.&per.", 11, "&per.&per.&per.", 15);
	
	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "-", 1);
	qreplace_all(s, "--", 2, "-", 1);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}

/*	------------------------------------------------------------
	specials2info()
	Ersetzen von UDO-Spezialbefehlen durch Texinfo-Versionen
	<->	s:	String
	------------------------------------------------------------	*/
LOCAL void specials2info ( char *s )
{
	qreplace_all(s, "!..", 3, "@dots{}", 7);
	
	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "@minus{}", 8);
	qreplace_all(s, "--", 2, "@minus{}", 8);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}


/*	------------------------------------------------------------
	specials2win()
	Ersetzen von UDO-Spezialbefehlen durch WinHelp-Versionen
	<->	s:	String
	------------------------------------------------------------	*/
LOCAL void specials2win ( char *s )
{
	qreplace_all(s, "!..", 3, "\\'85", 4);

	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "\\'97", 4);
	qreplace_all(s, "--", 2, "\\'96", 4);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}	/* specials2win */


/*	------------------------------------------------------------
	specials2win()
	Ersetzen von UDO-Spezialbefehlen durch WinHelp-Versionen
	<->	s:	String
	------------------------------------------------------------	*/
LOCAL void specials2rtf ( char *s )
{
	qreplace_all(s, "!..", 3, "\\'85", 4);

	qreplace_all(s, "(---)", 5, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "(--)", 4, TEMPO_S2, TEMPO_S2_LEN);
	qreplace_all(s, "---", 3, "\\emdash", 7);
	qreplace_all(s, "--", 2, "\\endash", 7);
	qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "---", 3);
	qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "--", 2);
}	/* specials2rtf */


GLOBAL void winspecials2ascii ( char *s )
{
	/* die obigen Sonderzeichen wieder in ASCII-Notation ausgeben */
	/* der Suchen-Dialog von WinHelp stellt die Sonderzeichen */
	/* und typographischen Anfuehrungszeichen falsch dar. */

	qreplace_all(s, "\\'85", 4, "...", 3);
	qreplace_all(s, "\\'97", 4, "-", 1);
	qreplace_all(s, "\\'96", 4, "-", 1);

	qreplace_all(s, "\\'84", 4, "\"", 1);
	qreplace_all(s, "\\'93", 4, "\"", 1);
	qreplace_all(s, "\\'94", 4, "\"", 1);
}	/* winspecials2ascii */



/*	------------------------------------------------------------
	texvar2ascii()
	Ersetzen von Platzhaltern, die nur fuer die LaTeX-Ausgabe
	interessant sind, durch die ASCII-Versionen
	<->	s:	String
	------------------------------------------------------------	*/
LOCAL void texvar2ascii ( char *s )
{
	if ( strstr(s, "(!")==NULL )	return;
	
	qreplace_all(s, "(!TeX)", 6, "TeX", 3);
	qreplace_all(s, "(!LaTeX)", 8, "LaTeX", 5);
	qreplace_all(s, "(!LaTeXe)", 9, "LaTeX2e", 7);
	qreplace_all(s, "(!copyright)", 12, "(c)", 3);

	qreplace_all(s, "(!alpha)", 8, "alpha", 5);
	qreplace_all(s, "(!beta)", 7, "beta", 4);
}	/* texvar2ascii */



/*	------------------------------------------------------------
	c_rtf_quotes()
	"\rquote " durch "\rquote  " ersetzen, falls kein Leerzeichen
	folgt, was direkt vor der Ausgabe einer Zeile geschehen muss.
	Grund: c_vars() wird vor str2tok() aufgerufen, wodurch beim
	       Zusammenbasteln der Zeile in token_output() die
	       hinteren Leerzeichen verlorengehen.
	------------------------------------------------------------	*/
GLOBAL void c_rtf_quotes ( char *s )
{
	qreplace_all(s, "\\lquote", 7,		"\\lquote ", 8);
	qreplace_all(s, "\\ldblquote", 10,	"\\ldblquote ", 11);

	qreplace_all(s, "\\rquote", 7,		"\\rquote ", 8);
	qreplace_all(s, "\\rdblquote", 10,	"\\rdblquote ", 11);

	qreplace_all(s, "\\emdash", 7,	"\\emdash ", 8);
	qreplace_all(s, "\\endash", 7,	"\\endash ", 8);

}	/* c_rtf_quotes */




/*	------------------------------------------------------------
	c_quotes_apostrophes()
	Ersetzen doppelter Anfuehrungszeichen und Apostrophe durch
	die jeweiligen Systemzeichen.
	->	aon:	Oeffnendes Apostroph
		aoff:	Schliessendes Apostroph
		qon:	Oeffnendes Anfuehrungszeichen
		qoff:	Schliessendes Anfuehrungszeichen
	------------------------------------------------------------	*/
LOCAL void c_quotes_apostrophes ( char *s,
		const char *aon, const char *aoff,
		const char *qon, const char *qoff )
{
	while (strstr(s, "''")!=NULL)
	{	(b1stApost) ? replace_once(s, "''", aon) : replace_once(s, "''", aoff);
		b1stApost= !b1stApost;
	}
	
	while (strstr(s, "\"\"")!=NULL)
	{	(b1stQuote) ? replace_once(s, "\"\"", qon) : replace_once(s, "\"\"", qoff);
		b1stQuote= !b1stQuote;
	}
	
}	/* c_quotes_apostrophes */




/*	------------------------------------------------------------
	c_vars()
	Ersetzen von vordefinierten Platzhaltern und speziellen
	Zeichenfolgen wie "", '', !.. oder (--)
	<->	s:	String
	------------------------------------------------------------	*/
GLOBAL void c_vars ( char *s )
{
	replace_all(s, "(!today)", lang.today);
	replace_all(s, "(!short_today)", lang.short_today);

	/* Anfuehrungszeichen und Apostrophe */

	qreplace_all(s, "(\"\")", 4, TEMPO_S, TEMPO_S_LEN);
	qreplace_all(s, "('')", 4, TEMPO_S2, TEMPO_S2_LEN);

	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
			switch (destlang)
			{	case TOGER:	c_quotes_apostrophes(s, "`", "'", "\"`", "\"'");	break;
				default:	c_quotes_apostrophes(s, "`", "'", "``", "''");		break;
			}
			qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\\symbol{34}\\symbol{34}", 22);
			qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "\\symbol{39}\\symbol{39}", 22);
			break;
		case TOLYX:
			switch (destlang)
			{
				case TOGER:
					c_quotes_apostrophes(s,
						"'", "'",
						"\\begin_inset"INDENT_S"Quotes"INDENT_S"gld\\end_inset"INDENT_S,
						"\\begin_inset"INDENT_S"Quotes"INDENT_S"grd\\end_inset"INDENT_S);
					break;				
				case TOFRA:
					c_quotes_apostrophes(s,
						"'", "'",
						"\\begin_inset"INDENT_S"Quotes"INDENT_S"fld\\end_inset"INDENT_S,
						"\\begin_inset"INDENT_S"Quotes"INDENT_S"frd\\end_inset"INDENT_S);
					break;				
				default:
					c_quotes_apostrophes(s,
						"'", "'",
						"\\begin_inset"INDENT_S"Quotes"INDENT_S"eld\\end_inset"INDENT_S,
						"\\begin_inset"INDENT_S"Quotes"INDENT_S"erd\\end_inset"INDENT_S);
					break;
			}
			break;
		case TORTF:
			if (no_quotes)
			{
				qreplace_all(s, "\"\"", 2, "\"", 1);
				qreplace_all(s, "''", 2, "'", 1);
			}
			else
			{	/* PL6 */
				/* Ohne schliessende Leerzeichen, damit nicht Tokens daraus werden! */
				/* Die Leerzeichen werden in c_rtf_quotes() hinzugefuegt!			*/
				c_quotes_apostrophes(s, "\\lquote", "\\rquote", "\\ldblquote", "\\rdblquote");
			}
			qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
			qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
			break;
		case TOWIN:
		case TOAQV:
			if (no_quotes)
			{
				qreplace_all(s, "\"\"", 2, "\"", 1);
				qreplace_all(s, "''", 2, "'", 1);
			}
			else
			{	switch (destlang)
				{	case TOGER:	c_quotes_apostrophes(s, "{\\'91}", "{\\'92}", "{\\'84}", "{\\'93}");	break;
					default:	c_quotes_apostrophes(s, "\\'91", "\\'92", "\\'93", "\\'94");	break;
				}
			}
			qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
			qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
			break;
		case TOLDS:	
			c_quotes_apostrophes(s, "`", "'", "``", "''");
			qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
			qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
			break;
		case TOHPH:	
			c_quotes_apostrophes(s, "`", "'", "<quote>", "<\\quote>");
			qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
			qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
			break;
		case TOHTM:	/*r6pl5*/
		case TOMHH:
			c_quotes_apostrophes(s, "`", "'", "&quot;", "&quot;");
			qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "&quot;&quot;", 12);
			qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
			break;
		default:
			c_quotes_apostrophes(s, "`", "'", "\"", "\"");
			qreplace_all(s, TEMPO_S, TEMPO_S_LEN, "\"\"", 2);
			qreplace_all(s, TEMPO_S2, TEMPO_S2_LEN, "''", 2);
			break;
	}


	/* Sonstiges */
	switch(desttype)
	{
		case TOTEX:
		case TOPDL:
			qreplace_all(s, "!..", 3, "\\ldots ", 7);
			qreplace_all(s, "(---)", 5, "-{}-{}-", 7);
			qreplace_all(s, "(--)", 4, "-{}-", 4);
			qreplace_all(s, "(!grin)", 7, "\\verb/;-)/", 10);
			qreplace_all(s, "(!laugh)", 8, "\\verb/:-)/", 10);
			qreplace_all(s, "(!TeX)", 6, "\\TeX{}", 6);
			qreplace_all(s, "(!LaTeX)", 8, "\\LaTeX{}", 8);
			if (bTex2e)
			{	qreplace_all(s, "(!LaTeXe)", 9, "\\LaTeXe{}", 9);
			}
			else
			{	qreplace_all(s, "(!LaTeXe)", 9, "\\LaTeX{}2${}_{\\textstyle\\varepsilon}$", 37);
			}
			qreplace_all(s, "(!copyright)", 12, "\\copyright{}", 12);
			qreplace_all(s, "(!alpha)", 8, "$\\alpha$", 8);
			qreplace_all(s, "(!beta)", 7, "$\\beta$", 7);
			break;
		case TOLYX:
			replace_all(s, "(!grin)", "\\family"INDENT_S"typewriter"INDENT_S";-)\\family"INDENT_S"default"INDENT_S);
			replace_all(s, "(!laugh)", "\\family"INDENT_S"typewriter"INDENT_S":-)\\family"INDENT_S"default"INDENT_S);
			specials2ascii(s);
			texvar2ascii(s);
			break;
		case TOINF:
			qreplace_all(s, "(!grin)", 7, "@code{;-)}", 10);
			qreplace_all(s, "(!laugh)", 8, "@code{:-)}", 10);
			qreplace_all(s, "(!TeX)", 6, "@TeX{}", 6);
			qreplace_all(s, "(!copyright)", 12, "@copyright{}", 12);
			specials2info(s);
			texvar2ascii(s);
			break;
		case TOSTG:
		case TOAMG:
		case TOPCH:
			qreplace_all(s, "(!copyright)", 12, COPY_S, COPY_S_LEN);
			qreplace_all(s, "(!grin)", 7, ";-)", 3);
			qreplace_all(s, "(!laugh)", 8, ":-)", 3);
			qreplace_all(s, "(!alpha)", 8, ALPHA_S, ALPHA_S_LEN);
			qreplace_all(s, "(!beta)", 7, BETA_S, BETA_S_LEN);
			specials2ascii(s);
			texvar2ascii(s);
			break;
		case TOASC:
		case TODRC:
		case TOMAN:
		case TONRO:
		case TOTVH:	/* PL10 */
		case TOSRC:	/* PL16 */
		case TOSRP:
			qreplace_all(s, "(!grin)", 7, ";-)", 3);
			qreplace_all(s, "(!laugh)", 8, ":-)", 3);
			qreplace_all(s, "(!alpha)", 8, ALPHA_S, ALPHA_S_LEN);
			qreplace_all(s, "(!beta)", 7, BETA_S, BETA_S_LEN);
			specials2ascii(s);
			texvar2ascii(s);
			break;
		case TOIPF:
			qreplace_all(s, "(!grin)", 7, ";-)", 3);
			qreplace_all(s, "(!laugh)", 8, "&colon.-)", 9);
			qreplace_all(s, "(!alpha)", 8, ALPHA_S, ALPHA_S_LEN);
			qreplace_all(s, "(!beta)", 7, BETA_S, BETA_S_LEN);
			specials2ipf(s);
			texvar2ascii(s);
			break;
		case TORTF:
			qreplace_all(s, "(!grin)", 7, "{\\f1 ;-)}", 9);
			qreplace_all(s, "(!laugh)", 8, "{\\f1 :-)}", 9);
			qreplace_all(s, "(!alpha)", 8, "alpha", 5);
			qreplace_all(s, "(!beta)", 7, "beta", 4);
			qreplace_all(s, "(!copyright)", 12, "\\'A9", 4);
			specials2rtf(s);
			texvar2ascii(s);
			break;
		case TOWIN:
		case TOAQV:
			qreplace_all(s, "(!grin)", 7, "{\\f1 ;-)}", 9);
			qreplace_all(s, "(!laugh)", 8, "{\\f1 :-)}", 9);
			qreplace_all(s, "(!alpha)", 8, "{\\f2 a}", 7);
			qreplace_all(s, "(!beta)", 7, "{\\f2 b}", 7);
			qreplace_all(s, "(!copyright)", 12, "\\'A9", 4);
			specials2win(s);
			texvar2ascii(s);
			break;
		case TOWH4:
			qreplace_all(s, "(!grin)", 7, "{\\f1 ;-)}", 9);
			qreplace_all(s, "(!laugh)", 8, "{\\f1 :-)}", 9);
			qreplace_all(s, "(!alpha)", 8, "{\\f2 a}", 7);
			qreplace_all(s, "(!beta)", 7, "{\\f2 b}", 7);
			qreplace_all(s, "(!copyright)", 12, "\\'A9", 4);
			specials2ascii(s);
			texvar2ascii(s);
			break;
		case TOHTM:
		case TOMHH:
			qreplace_all(s, "(!grin)", 7, "<TT>;-)</TT>", 12);
			qreplace_all(s, "(!laugh)", 8, "<TT>:-)</TT>", 12);
			qreplace_all(s, "(!copyright)", 12, "&copy;", 6);
			specials2ascii(s);
			texvar2ascii(s);
			break;
		case TOLDS:
			qreplace_all(s, "(!grin)", 7, "<tt/;-)/", 8);
			qreplace_all(s, "(!laugh)", 8, "<tt/:-)/", 8);
			specials2ascii(s);
			texvar2ascii(s);
			break;
		case TOHPH:
			qreplace_all(s, "(!grin)", 7, "<ex>;-)<\\ex>", 12);
			qreplace_all(s, "(!laugh)", 8, "<ex>:-)<\\ex>", 12);
			specials2ascii(s);
			texvar2ascii(s);
			break;
	}
}	/* c_vars */



/*	############################################################
	#
	#	(interne) Texteffekte fuer Manualpages anpassen
	#
	############################################################	*/
LOCAL void str2manbold( char *d, const char *s )
{
	size_t	i;
	char	c[2]={0,0};
	
	d[0]= EOS;

	if (s[0]==EOS)
	{	return;
	}
	
	for (i=0; i<strlen(s); i++)
	{	c[0]=s[i];
		strcat(d, c);
		strcat(d, "\010");
		strcat(d, c);
	}
	
}	/* str2manbold */


LOCAL void str2manunder( char *d, const char *s )
{
	size_t	i;
	char	c[2]={0,0};
	
	d[0]= EOS;

	if (s[0]==EOS)
	{	return;
	}
	
	for (i=0; i<strlen(s); i++)
	{	strcat(d, "_\010");
		c[0]=s[i];
		strcat(d, c);
	}
	
}	/* str2manunder */


GLOBAL void c_man_styles ( char *s )
{
	char *ptr;
	char alt[512], neu[512];
	char *start;
	char s_char[2]={0,0};
	BOOLEAN	bold_active= styleflag.bold;
	BOOLEAN under_active= styleflag.underlined;
	BOOLEAN replace_it= FALSE;

	if (s[0]==EOS)	return;

	/* ptr zeigt jeweils auf das erste Zeichen des Stylemagic \033\001 */
	/* UDO ersetzt Befehle wie (!B) zunaechst durch eigene Escape-Befehle */
	/* ESC-001-xxx-ESC, wobei xxx den jeweiligen Stil angibt */
	
	ptr= strstr(s, STYLEMAGIC);
	if (ptr==NULL)	return;
	
	start=ptr;

	alt[0]= EOS;

	do	
	{
		if (ptr[0]!=STYLEMAGIC[0] && ptr[0]!=STYLEMAGIC[1])
		{	if (bold_active || under_active)
			{	s_char[0]= ptr[0];
				strcat(alt, s_char);
			}
		}	else
		if (ptr[0]==STYLEMAGIC[0] && ptr[1]==STYLEMAGIC[1])
		{	switch (ptr[2])		
			{	case C_BOLD_ON:
					bold_active= TRUE;
					alt[0]= EOS;
					ptr+= 3;
					start= ptr+1;
					break;
				case C_BOLD_OFF:
					bold_active= FALSE;
					ptr+= 3;
					str2manbold(neu, alt);
					replace_it= TRUE;
					break;
				case C_UNDER_ON:
					under_active= TRUE;
					alt[0]= EOS;
					ptr+= 3;
					start= ptr+1;
					break;
				case C_UNDER_OFF:
					under_active= FALSE;
					ptr+= 3;
					str2manunder(neu, alt);
					replace_it= TRUE;
					break;
			}	/*switch*/
		}	/* if...else */
		
		if (replace_it)
		{	replace_once(start, alt, neu);
			ptr+= (strlen(neu)-strlen(alt));
			alt[0]= EOS;
			replace_it= FALSE;
		}

		ptr++;		

	}	while (ptr[0]!=EOS);
	
}	/* c_man_styles */


/*	############################################################
	#
	# Automatisches Quoten von kritischen Zeichen dort, wo kein
	# (!V)/(!v) benutzt wird und kein !tex, !=tex etc. am
	# Zeilenanfang steht.
	#
	############################################################	*/

typedef struct
{
	const char		cmd[20];	/* String PL6: vorher UCHAR */
	const size_t	cmdlen;		/* Laenge des Kommandos (need speed ;-))*/
	const char		abb[20];	/* Kommandoabkuerzung */
	const size_t	abblen;		/* Laenge der Abkuerzung */
}	QUOTECOMMAND;



/* Es wird zwar unten mit strncmp() getestet, ob das Kommando */
/* gequotet werden muss, allerdings muss nach dem Kommando */
/* Ein Leerzeichen oder ein Tab auftreten, damit die Abfrage */
/* TRUE liefert. Daher muessen hier sowohl !node als auch */
/* !node* angegeben werden! */

# define	MAXQUOTECMD	39

LOCAL const QUOTECOMMAND quotecommand[MAXQUOTECMD]=
{
	{	"!node",				5,	"!n",		2	},
	{	"!subnode",				8,	"!sn",		3	},
	{	"!subsubnode",			11,	"!ssn",		4	},
	{	"!subsubsubnode",		14,	"!sssn",	5	},
	{	"!pnode",				6,	"!p",		2	},
	{	"!psubnode",			9,	"!ps",		3	},
	{	"!psubsubnode",			12,	"!pss",		4	},
	{	"!psubsubsubnode",		15,	"!psss",	5	},
	{	"!node*",				6,	"!n*",		3	},
	{	"!subnode*",			9,	"!sn*",		4	},
	{	"!subsubnode*",			12,	"!ssn*",	5	},
	{	"!subsubsubnode*",		15,	"!sssn*",	6	},
	{	"!pnode*",				7,	"!p*",		3	},
	{	"!psubnode*",			10,	"!ps*",		4	},
	{	"!psubsubnode*",		13,	"!pss*",	5	},
	{	"!psubsubsubnode*",		16,	"!psss*",	6	},
	{	"!begin_node",			11,	"!bn",		3	},
	{	"!begin_pnode",			12,	"!bp",		3	},
	{	"!begin_node*",			12,	"!bn*",		4	},
	{	"!begin_pnode*",		13,	"!bp*",		4	},
	{	"!item",				5,	"!i",		2	},
	{	"!index",				6,	"!x",		2	},
	{	"!image",				6,	"",			0	},
	{	"!image*",				7,	"",			0	},
	{	"!table_caption",		14,	"",			0	},
	{	"!table_caption*",		15,	"",			0	},	/* r6pl1 */
	{	"!begin_xlist",			12,	"!bxl",		4	},	/* wegen des Inhalts der eckigen Klammern!	*/
	{	"!begin_blist",			12,	"!bbl",		4	},	/* Fehlen die hier, so bekommt c_begin_list */
	{	"!begin_ilist",			12,	"!bil",		4	},	/* einen String, der c_vars(), aber nicht	*/
	{	"!begin_tlist",			12,	"!btl",		4	},	/* auto_quote_chars() durchlaufen hat!!!	*/
	{	"!heading",				8,	"!h",		2	},
	{	"!subheading",			11,	"!sh",		3	},
	{	"!subsubheading",		14,	"!ssh",		4	},
	{	"!subsubsubheading",	17,	"!sssh",	5	},
	{	"!macro",				6,	"",			0	},
	{	"!hyphen",				7,	"",			0	},
	{	"!label",				6,	"",			0	},
	{	"!alias",				6,	"",			0	},
	{	"!docinfo",				8,	"",			0	},
};


GLOBAL void auto_quote_chars ( char *s, BOOLEAN all )
{
	register int i,	tabidx;
	char *ptr, *oldptr;
	char *ptr_quoted, s_temp[32];
	char s_char[2]={0,0};
	BOOLEAN aqc_verb;
	BOOLEAN	found= FALSE;
	size_t	cmplen, sl_verb_on, sl_verb_off;
	
	if (s[0]==EOS)
	{	return;
	}

	if (no_umlaute)
	{	umlaute2ascii(s);
	}

	switch(desttype)
	{	case TOASC:	/* Hier muss nicht gequotet werden! */
		case TODRC:
		case TOMAN:
		case TONRO:
		case TOSTG:
		case TOAMG:
		case TOTVH:
		case TOINF:
		case TOSRC:
		case TOSRP:
#ifdef __TOS__
			replace_all(s, BETA_S, "\236");
#endif
#ifdef __MSDOS__
			replace_all(s, "\236", "\341");
#endif
#ifdef __MSDOS850__
			replace_all(s, "\236", "\341");
#endif
			if ( bDocUniversalCharsetOn )
			{	uni2ascii(s);
			}

#if 1
			/* r6pl2: Neue Version: immer quoten 						*/
			/* nicht auf !raw !stg testen, da dies im wichtigen pass2() */
			/* nicht auftreten kann, da vorher die Zeilen mit 			*/
			/* c_special_commands() bearbeitet werden.					*/
			
			if (desttype==TOSTG)
			{
				replace_1at_by_2at(s);
				return;
			}
			if (desttype==TOINF)
			{
				qreplace_all(s, "@", 1, "@@", 2);
				qreplace_all(s, "}", 1, "@}", 2);
				qreplace_all(s, "{", 1, "@{", 2);
				return;
			}
			if (desttype==TOTVH)	/* r5pl10 */
			{
				qreplace_all(s, "{", 1, "{{", 2);
				return;
			}
#else
			/* Alte Version */
			if (desttype==TOSTG)
			{	if (strncmp(s, "!stg", 4)!=0)
				{	replace_all(s, "@", "@@");
				}
				return;
			}
			if (desttype==TOINF)
			{	if (strncmp(s, "!info", 5)!=0)
				{	replace_all(s, "@", "@@");
					replace_all(s, "}", "@}");
					replace_all(s, "{", "@{");
				}
				return;
			}
			if (desttype==TOTVH)	/* r5pl10 */
			{	if (strncmp(s, "!tvh", 4)!=0)
				{	replace_all(s, "{", "{{");
				}
			}
#endif
			return;
	}	
	
	ptr= s;

	if (!all)
	{	/* Wenn in der Zeile ein Kommando steht, dann nur den Rest	*/
		/* quoten, wenn das Kommando einen Parameter enthaelt,		*/
		/* der gequotet werden muss!									*/
		if ( s[0]==META_C && s[1]>='a' && s[1]<='z' )
		{
			for (i=0; i<MAXQUOTECMD; i++)
			{
				cmplen= quotecommand[i].cmdlen;
				if (strncmp(s, quotecommand[i].cmd, cmplen)==0)
				{	/* Das naechste Zeichen muss aber Space oder Tab sein! */
					if ( s[cmplen]==' ' || s[cmplen]=='\t')
					{	found= TRUE;
						ptr+= cmplen;
						break;
					}
				}
				if ( (cmplen= quotecommand[i].abblen) >0 )
				{	/*r6pl12: Abkuerzungen auch beachten */
					if (strncmp(s, quotecommand[i].abb, cmplen)==0)
					{	/* Das naechste Zeichen muss aber Space oder Tab sein! */
						if ( s[cmplen]==' ' || s[cmplen]=='\t')
						{	found= TRUE;
							ptr+= cmplen;
							break;
						}
					}
				}

			}
			if (!found)
			{	return;
			}
		}
	}

	ptr_quoted= NULL;
	s_temp[0]=EOS;
	s_char[0]= EOS;
	aqc_verb= last_aqc_verb;	/* Pl13: vorher = TRUE */

	sl_verb_on= CMD_STYLELEN;
	sl_verb_off= CMD_STYLELEN;
	
	while (ptr[0]!=EOS)
	{
		/* PL13: Innerhalb (!V)...(!v) Leerzeichen durch interne  */
		/* feste Leerzeichen ersetzen, damit token_output() nicht */
		/* \verb+...+ umbricht.                                   */
		if ( desttype==TOTEX || desttype==TOPDL )
		{	{	if ( aqc_verb || styleflag.verbatim)
				{	if (ptr[0]==' ')
					{	ptr[0]= INDENT_C;
						goto NO_QUOTE_NEEDED;
					}
				}
			}
		}

		/* Das Alphabet und die Ziffern muessen nie gequotet werden!	*/
		/* Also einfach den ganzen Rotz ueberspringen					*/
		if (ptr[0]==' ')				goto NO_QUOTE_NEEDED;
		if (ptr[0]>='a' && ptr[0]<='z')	goto NO_QUOTE_NEEDED;
		if (ptr[0]>='A' && ptr[0]<='Z')	goto NO_QUOTE_NEEDED;
		if (ptr[0]>='0' && ptr[0]<='9')	goto NO_QUOTE_NEEDED;

		if ( (desttype==TOTEX || desttype==TOPDL) && !all)	
		{	if (strncmp(ptr, CMD_VERB_ON, sl_verb_on)==0)
			{	/* Optimierung durch Hochzaehlen von ptr */
				aqc_verb= TRUE;
				ptr+= (sl_verb_on-1);
				goto NO_QUOTE_NEEDED;
			}
			if (strncmp(ptr, CMD_VERB_OFF, sl_verb_off)==0)
			{	/* Optimierung durch Hochzaehlen von ptr */
				aqc_verb= FALSE;
				ptr+= (sl_verb_off-1);
				goto NO_QUOTE_NEEDED;
			}
		}

		/* Sonderbehandlung fuer doppelte Anfuehrungszeichen und Apostrophe*/
		if (ptr[0]=='\"' && ptr[1]=='\"')
		{	/* Doppelquotes: "" */
			ptr++;
			goto NO_QUOTE_NEEDED;
		}

		if (ptr[0]=='(' && ptr[1]=='\"' && ptr[2]=='\"' && ptr[3]==')')
		{	/* Gequotete Quotes: ("") */
			ptr+= 3;
			goto NO_QUOTE_NEEDED;
		}

		if (ptr[0]=='(' && ptr[1]=='\'' && ptr[2]=='\'' && ptr[3]==')')
		{	/* Gequotete Apostrophe: ('') */
			ptr+= 3;
			goto NO_QUOTE_NEEDED;
		}
		
		
		/* Sonderbehandlung fuer Platzhalter, welche spaeter	*/
		/* gequotet werden (macro, define, link, index)			*/
		/* PL6: aber nicht in verbatim-Umgebungen!				*/

		/* Dabei beruecksichtigen, dass Klammern innerhalb		*/
		/* durch ein Ausrufungszeichen gequotet werden.			*/		

		if ( pflag[PASS2].env!=ENV_VERBATIM )
		{
			if (ptr[0]=='(' && ptr[1]==META_C && ptr[2]!=QUOTE_C)
			{
				oldptr= ptr;	/* Pointer sichern */
				ptr++;
				while ( ptr[0]!=EOS && ptr[0]!=')' )
				{	if ( ptr[0]=='!' && ptr[1]==')' )
					{	ptr++;	/* gequotete Klammer ueberspringen */
					}
					ptr++;
				}	

				if (ptr[0]==EOS)
				{	/* PL16: Falls der Pointer auf das Ende zeigt, dann */
					/* ist etwas schiefgelaufen oder aber es handelte */
					/* sich gar nicht um einen Parameter (z.B. "(!)") */
					/* In dem Falle den alten Pointer restaurieren */
					ptr= oldptr;
					ptr++;
				}
				else
				{	/* Optimierung: Position weitersetzen und Rest ueberspringen */
					ptr--;
					goto NO_QUOTE_NEEDED;
				}
			}
		}
		

		switch (desttype)
		{
			case TOTEX:
			case TOPDL:
				if ( (all) || (!styleflag.verbatim && !aqc_verb) )
				{
					found= FALSE;
					
					if ( ((UCHAR) ptr[0]) > 127 )
					{	tabidx= ((UCHAR) ptr[0])-128;
						if ( chrtab[tabidx].tex[0]!=EOS )
						{	ptr_quoted= chrtab[tabidx].tex;
							found= TRUE;
						}
					}
					else
					{	for (i=0; i<MAXTEX7BIT; i++)
						{	if ( ( /*(UCHAR)*/ ptr[0])==tex7bit[i].c)
							{	ptr_quoted= tex7bit[i].quoted;
								found= TRUE;
								break;
							}
						}
					}
					
					if (!found)
					{ 	if ( (UCHAR) ptr[0]>=127 )
						{	warning_no_texchar(ptr[0]);	/* PL12 */
							sprintf(s_temp, "$\\symbol{%d}$", (UCHAR) ptr[0]);
							ptr_quoted= s_temp;
						}
					}
				}
				break;
			
			case TOLYX:
				found= FALSE;
				for (i=0; i<MAXLYX7BIT; i++)
				{	if ( ( /*(UCHAR)*/ ptr[0])==lyx7bit[i].c)
					{	ptr_quoted= lyx7bit[i].quoted;
						found= TRUE;
						break;
					}
				}
				if (!found)
				{
				}
				break;
				
			case TOIPF:
				found= FALSE;
				for (i=0; i<MAXIPF7BIT; i++)
				{	if ( ( /*(UCHAR)*/ ptr[0])==ipf7bit[i].c)
					{	ptr_quoted= ipf7bit[i].quoted;
						found= TRUE;
						break;
					}
				}
				if (!found)
				{
				}
				break;

			case TORTF:
				found= FALSE;
				if ( ((UCHAR) ptr[0]) > 127 )
				{	/* Wie bei WinHelp */
					if (iCharset!=CODE_LAT1)
					{	tabidx= ((UCHAR) ptr[0])-128;
						if ( chrtab[tabidx].ansi[0]!=EOS )
						{	ptr_quoted= chrtab[tabidx].ansi;
							found= TRUE;
						}
						else
						{	warning_cannot_recode(ptr[0], "system charset", "Windows ANSI");
							ptr[0]= '?';
						}
					}
					if (!found)
					{	sprintf(s_temp, "\\'%X", (UCHAR) ptr[0]);
						ptr_quoted= s_temp;
					}
				}
				else
				{	for (i=0; i<MAXRTF7BIT; i++)
					{	if ( ( ptr[0])==rtf7bit[i].c)
						{	ptr_quoted= rtf7bit[i].quoted;
							found= TRUE;
							break;
						}
					}
				}
				if (!found)
				{
				}
				break;
				
			case TOKPS:
				found= FALSE;
				if ( ((UCHAR) ptr[0]) > 127 )
				{	
					if (iCharset!=CODE_LAT1)
					{	tabidx= ((UCHAR) ptr[0])-128;
						if ( chrtab[tabidx].ps[0]!=EOS )
						{	ptr_quoted= chrtab[tabidx].ps;
							found= TRUE;
						}
						else
						{	warning_cannot_recode(ptr[0], "system charset", "Windows ANSI");
							ptr[0]= '?';
						}
					}
					if (!found)
					{	sprintf(s_temp, "\\%03o", (UCHAR) ptr[0]);
						ptr_quoted= s_temp;
					}
				}
#if 0
				else
				{
#define	MAXPS7BIT	3
LOCAL /*const*/ QUOTEINFO ps7bit[MAXPS7BIT]=
{
	{	'(',		"\\("	},
	{	')',		"\\)"	},
	{	'\\',		"\\\\"	}
};
					for (i=0; i<MAXPS7BIT; i++)
					{	if ( ( ptr[0])==ps7bit[i].c)
						{	ptr_quoted= ps7bit[i].quoted;
							found= TRUE;
							break;
						}
					}
				}
#endif
				if (!found)
				{
				}
				break;

			case TOWIN:
			case TOWH4:
			case TOAQV:
				found= FALSE;
				if ( ((UCHAR) ptr[0]) > 127 )
				{	if (iCharset!=CODE_LAT1)
					{	tabidx= ((UCHAR) ptr[0])-128;
						if ( chrtab[tabidx].ansi[0]!=EOS )
						{	ptr_quoted= chrtab[tabidx].ansi;
							found= TRUE;
						}
						else
						{	warning_cannot_recode(ptr[0], "system charset", "Windows ANSI");
							ptr[0]= '?';
						}
					}
					if (!found)
					{	sprintf(s_temp, "\\'%X", ((UCHAR) ptr[0]) );
						ptr_quoted= s_temp;
					}
				}
				else
				{	for (i=0; i<MAXWIN7BIT; i++)
					{	if ( (/*(UCHAR)*/ ptr[0])==win7bit[i].c)
						{	ptr_quoted= win7bit[i].quoted;
							found= TRUE;
							break;
						}
					}
				}
				if (!found)
				{
				}
				break;
				
			case TOPCH:
				if (ptr[0]=='\\')
				{	strcpy(s_temp, "\\\\");
					ptr_quoted= s_temp;
				}
				break;

			case TOHTM:
			case TOMHH:
				found= FALSE;
				if ( ((UCHAR) ptr[0]) > 127 )
				{	if (!html_ignore_8bit)
					{	tabidx= ((UCHAR) ptr[0])-128;
						if ( chrtab[tabidx].html[0]!=EOS )
						{	ptr_quoted= chrtab[tabidx].html;
							found= TRUE;
						}
						else
						{	warning_no_isochar(ptr[0]);
						}
					}
				}
				else
				{	for (i=0; i<MAXHTML7BIT; i++)
					{	if ( ptr[0]==html7bit[i].c)
						{	ptr_quoted= html7bit[i].quoted;
							found= TRUE;
							break;
						}
					}
				}
				if (!found)
				{
				}
				break;

			case TOLDS:
				found= FALSE;
				if ( ((UCHAR) ptr[0]) > 127 )
				{	tabidx= ((UCHAR) ptr[0])-128;
					if ( chrtab[tabidx].html[0]!=EOS )
					{	ptr_quoted= chrtab[tabidx].html;
						found= TRUE;
					}
					else
					{	warning_no_isochar(ptr[0]);
					}
				}
				else
				{	for (i=0; i<MAXLDS7BIT; i++)
					{	if ( (ptr[0])==lds7bit[i].c)
						{	ptr_quoted= lds7bit[i].quoted;
							found= TRUE;
							break;
						}
					}
				}
				if (!found)
				{
				}
				break;

			case TOHPH:
				found= FALSE;
				if ( ((UCHAR) ptr[0]) > 127 )
				{	tabidx= ((UCHAR) ptr[0])-128;
					if ( chrtab[tabidx].html[0]!=EOS )
					{	ptr_quoted= chrtab[tabidx].html;
						found= TRUE;
					}
					else
					{	warning_no_isochar(ptr[0]);
					}
				}
				else
				{	for (i=0; i<MAXHTAG7BIT; i++)
					{	if ( ptr[0]==htag7bit[i].c)
						{	ptr_quoted= htag7bit[i].quoted;
							found= TRUE;
							break;
						}
					}
				}
				if (!found)
				{
				}
				break;
		}

		if (ptr_quoted!=NULL && ptr_quoted[0]!=EOS)
		{	s_char[0]= ptr[0];
			replace_once(ptr, s_char, ptr_quoted);
			cmplen= strlen(ptr_quoted);
			ptr= ptr + cmplen - 1;
			s_char[0]= EOS;
			s_temp[0]= EOS;
			ptr_quoted= NULL;
		}
		
		NO_QUOTE_NEEDED:

		ptr++;
	}

	if ( bDocUniversalCharsetOn )
	{	uni2misc(s);
	}

	if (iUdopass==PASS2)
	{
		last_aqc_verb= aqc_verb;	/* PL13: Status sichern */
	}
	else
	{
		/* r6pl9: In pass1() werden nur Kommandozeilen beachtet.	*/
		/* Wird last_aqc_verb nicht zurueckgesetzt, dann kracht es!	*/
		last_aqc_verb= FALSE;
	}
	
} /* auto_quote_chars */


GLOBAL void auto_quote_texindex ( char *s )
{
	if (desttype==TOTEX || desttype==TOPDL)
	{
#if 0
		qreplace_all(s, "{\\\"a}",	5, "\\\"a",	3);		/* {\"a} -> \"a */
		qreplace_all(s, "{\\\"o}",	5, "\\\"o",	3);		/* {\"o} -> \"o */
		qreplace_all(s, "{\\\"u}",	5, "\\\"u",	3);		/* {\"u} -> \"u */
		qreplace_all(s, "{\\\"A}",	5, "\\\"A",	3);		/* {\"A} -> \"A */
		qreplace_all(s, "{\\\"O}",	5, "\\\"O",	3);		/* {\"O} -> \"O */
		qreplace_all(s, "{\\\"U}",	5, "\\\"U",	3);		/* {\"U} -> \"U */
#endif
		qreplace_all(s, "\"`",	2, "\"\"`",	3);			/* "` -> \"` */
		qreplace_all(s, "\"'",	2, "\"\"'",	3);			/* "' -> \"' */
		qreplace_all(s, "!",	1, "\"!",	2);			/* !  -> "! */
		qreplace_all(s, "@",	1, "\"@",	2);			/* @  -> "@ */
		qreplace_all(s, "|",	1, "\"|",	2);			/* |  -> "| */
	}
}



/*	############################################################
	# Zeichen fuer die Linedraw-Umgebung anpassen (nur RTF)
	############################################################	*/
GLOBAL void auto_quote_linedraw ( char *s )
{
	register int i;
	char *ptr, *quoted;
	char sTemp[32];
	char sChar[2]={0,0};

	ptr= s;

	while (ptr[0]!=EOS)
	{

		if ( ((UCHAR) ptr[0]) > 127 )
		{	sprintf(sTemp, "\\'%X", (UCHAR) ptr[0]);
			sChar[0]= ptr[0];
			qreplace_once(ptr, sChar, 1, sTemp, 4);
			ptr+= 3;
		}
		else
		{	
			for (i=0; i<MAXRTF7BIT; i++)
			{	if ( ( ptr[0])==rtf7bit[i].c)
				{	quoted= rtf7bit[i].quoted;
					sChar[0]= ptr[0];
					replace_once(ptr, sChar, quoted);
					ptr= ptr + strlen(quoted) - 1 ;
					break;
				}
			}
		}

		ptr++;
	
	}	/*while*/

}	/* auto_quote_linedraw */



/*	############################################################
	# Modulinitialisierung
	############################################################	*/
GLOBAL void init_module_chars ( void )
{
	last_aqc_verb= FALSE;
	texinfo_np_counter= 0;
}


/*	############################################################
	# chars.c
	############################################################	*/

