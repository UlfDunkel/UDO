/*	############################################################
	# @(#) str.c
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

#ifndef ID_STR_C
#define	ID_STR_C
const char *id_str_c= "@(#) str.c       10.03.1997";
#endif

#include "import.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "portab.h"

#include "export.h"
#include "str.h"
#include "version.h"

#include "msg.h"

/*
	#################################################################
	#
	# strcat und strcpy Wrapper, die Puffergrenzen checken k”nnen
	#
	#################################################################
*/

GLOBAL char *um_strcpy(char *dest, const char *src, size_t max, const char *place)
{
	char errbuf[120];
	size_t slen; /* Temporaere Variable, fuer die Laenge von src */
	
	if ( dest == NULL )
	{
		sprintf(errbuf, "um_strcpy: dest is NULL: %s", place);
		loglnposprintf ("Warning", errbuf);
		return dest;
	}
	if ( src == NULL )
	{
		sprintf(errbuf, "um_strcpy: src is NULL: %s", place);
		loglnposprintf ("Warning", errbuf);
		dest[0]=EOS;
		return dest;
	}

	slen=(size_t)strlen(src); /* Stringlänge bestimmen */
	if (((size_t)slen+1)<max) /* Testen obs  */
	{
		return strcpy(dest, src);
	}
	else
	{
		dest[0]=EOS;
		sprintf(errbuf, "um_strcpy: buffer overrun prevented: %s: %d>%d", place, slen+1, max);
		loglnposprintf ("Warning", errbuf);
		return dest;
	}
}

GLOBAL char *um_strncpy(char *dest, const char *src, size_t n, size_t max, const char *place)
{
	char errbuf[120];

	if ( dest == NULL )
	{
		sprintf(errbuf, "um_strncpy: dest is NULL: %s", place);
		loglnposprintf ("Warning", errbuf);
		return dest;
	}
	if ( src == NULL )
	{
		sprintf(errbuf, "um_strncpy: src is NULL: %s", place);
		loglnposprintf ("Warning", errbuf);
		dest[0]=EOS;
		return dest;
	}

	if ((n+1)<max)
	{
		return strncpy(dest, src, n);
	}
	else
	{
		dest[0]=EOS;
		sprintf(errbuf, "um_strncpy: buffer overrun prevented: %s: %d>%d", place, n+1, max);
		loglnposprintf ("Warning", errbuf);
		return dest;
	}
}

GLOBAL char *um_strcat(char *dest, const char *src, size_t max, const char *place)
{
	char errbuf[120];
	size_t dlen, slen;

	if ( dest == NULL )
	{
		sprintf(errbuf, "um_strcat: dest is NULL: %s", place);
		loglnposprintf ("Warning", errbuf);
		return dest;
	}
	if ( src == NULL )
	{
		sprintf(errbuf, "um_strcat: src is NULL: %s", place);
		loglnposprintf ("Warning", errbuf);
		return dest;
	}

	dlen=(size_t)strlen(dest);
	slen=(size_t)strlen(src);
	
	if ((dlen+slen+1)<max)
	{
		return strcat(dest, src);
	}
	else
	{
		dest[0]=EOS;
		sprintf(errbuf, "um_strcat: buffer overrun prevented: %s: %d>%d", place, dlen+slen+1, max);
		loglnposprintf ("Warning", errbuf);
		return dest;
	}
}

GLOBAL char *um_strncat(char *dest, const char *src, size_t n, size_t max, const char *place)
{
	char errbuf[120];
	size_t dlen;

	if ( dest == NULL )
	{
		sprintf(errbuf, "um_strncat: dest is NULL: %s", place);
		loglnposprintf ("Warning", errbuf);
		return dest;
	}
	if ( src == NULL )
	{
		sprintf(errbuf, "um_strncat: src is NULL: %s", place);
		loglnposprintf ("Warning", errbuf);
		return dest;
	}

	dlen=strlen(dest);
	if ((dlen+n+1)<max)
	{
		return strncat(dest, src, n);
	}
	else
	{
		dest[0]=EOS;
		sprintf(errbuf, "um_strncat: buffer overrun prevented: %s: %d>%d", place, dlen+n+1, max);
		loglnposprintf("Warning", errbuf);
		return dest;
	}
}

/*	############################################################
	#
	# Anhaengen von Strings und Zeichen
	#
	############################################################	*/
/*	----------------------------------------------------------------------
	chrcat()
	Aufgabe: Anhaengen eines Zeichens an einen String
	----------------------------------------------------------------------	*/
GLOBAL char *chrcat (char *dest, const char c)
{
	char one[2]={0,0};

	one[0]= c;
	return(strcat(dest, one));
}	/* chrcat */



/*	############################################################
	#
	# Einfuegen von Strings
	#
	############################################################	*/
/*	------------------------------------------------------------
	strinsert() fuegt am Anfang von <s> den String <ins> ein
	->	string: String, in dem eingefuegt werden soll
		insert:	einzufuegender String
	<-	Zeiger auf <string>
	------------------------------------------------------------	*/
GLOBAL char *strinsert ( char *string, const char *insert)
{
	char	*start;
	size_t	sl, il;
	
	if ( insert[0]=='\0' )
	{	return string;
	}
	
	sl= strlen(string);
	il= strlen(insert);

	/* Platz schaffen fuer neues und dorthin kopieren */
	start= string;
	memmove(string+il, string, sl+1);
	memcpy(start, insert, il);
	
	return string;
}	/*strinsert*/



/*	############################################################
	#
	# Ersetzen von einzelnen Zeichen
	#
	############################################################	*/
/*	------------------------------------------------------------
	replace_char() ersetzt in <string> das erste Zeichen von
	<replace> durch das erste Zeichen von <by>
	------------------------------------------------------------	*/
GLOBAL void replace_char ( char *string, const char *replace, const char *by )
{
	char *ptr;
	
	ptr= string;

	while (*ptr!=EOS)
	{
		if (*ptr==*replace)
		{	*ptr= *by;
		}
		ptr++;
	}

}	/* replace_char */



/*	############################################################
	#
	# Ersetzen von Strings
	#
	############################################################	*/

/*	------------------------------------------------------------
	replace_once() ersetzt in <s> einmal <rep> durch <by>
	->	source: String, in dem ersetzt werden soll
		rep:	zu ersetzender String
		by:		neuer String
	<-	1:	String wurde ersetzt
		0:	String nicht gefunden
	------------------------------------------------------------	*/
GLOBAL int replace_once ( char *source, const char *replace, const char *by)
{
	char 	*found;
	size_t	rlen, blen, flen;
	
	if ( source[0]=='\0' )		return 0;
	if ( replace[0]=='\0' )		return 0;
	
	if ( (found= strstr(source, replace))==NULL )	return 0;

	rlen=strlen(replace);
	flen= strlen(found);

	/* Zu Ersetzendes entfernen */
	memmove(found, found+rlen, flen-rlen+1);

	/* Platz schaffen fuer neues und dorthin kopieren */
	if ( by[0]!=EOS )
	{	blen= strlen(by);
		flen= strlen(found);
		memmove(found+blen, found, flen+1);
		memcpy(found, by, blen);
	}
	
	return 1;
}	/*replace_once*/


/*	------------------------------------------------------------
	replace_last() ersetzt in <s> das letzte <rep> durch <by>
	------------------------------------------------------------	*/
GLOBAL int replace_last ( char *source, const char *replace, const char *by)
{
	char *found, *look, *last;

	if ( source[0]=='\0' )		return 0;
	if ( replace[0]=='\0' )		return 0;
	
	look= source;
	last= NULL;

	while ( (found= strstr(look, replace))!=NULL )
	{	look= found+1;
		last= found;
	}

	if (last!=NULL)
	{	return ( replace_once(last, replace, by) );
	}
	
	return 0;
}	/* replace_last */



/*	------------------------------------------------------------
	replace_all() ersetzt in <s> alle <rep> durch <by>
	------------------------------------------------------------	*/
GLOBAL int replace_all ( char *source, const char *replace, const char *by)
{
	char 	*found;
	size_t	rlen, blen, flen, i;
	
	if ( source[0]=='\0' )		return 0;
	if ( replace[0]=='\0' )		return 0;

	if ( (found= strstr(source, replace))==NULL )	return 0;

	rlen=strlen(replace);
	blen= strlen(by);

	if (rlen==blen)
	{
		while ( found!=NULL )
		{
			for (i=0; i<blen; i++)
			{	found[i]= by[i];
			}
			found= strstr(found+blen, replace);
		}
		return 1;
	}

	while ( found!=NULL )
	{
		flen= strlen(found);

		/* Zu Ersetzendes entfernen */
		memmove(found, found+rlen, flen-rlen+1);
	
		/* Platz schaffen fuer neues und dorthin kopieren */
		if ( by[0]!=EOS )
		{	flen= strlen(found);
			memmove(found+blen, found, flen+1);
			memcpy(found, by, blen);
			found= strstr(found+blen, replace);
		}
		else
		{	found= strstr(found, replace);
		}
	}
	
	return 1;
}	/*replace_all*/



/*	############################################################
	#
	# Ersetzen von Strings (schnelle Variante) r6pl2
	#
	############################################################	*/

/*	------------------------------------------------------------
	qreplace_once() ersetzt in <s> einmal <rep> durch <by>
	Im Gegensatz zu replace_one() sind die Laengen der Strings
	bekannt (kein strlen() noetig). Dadurch	ist diese Routine
	schneller als replace_one(): "q" steht fuer "quick"
	->	source:		String, in dem ersetzt werden soll
		replace:	zu ersetzender String
		rlen:		strlen(replace)
		by:			neuer String
		blen:		strlen(by)
	<-	1:	String wurde ersetzt
		0:	String nicht gefunden
	------------------------------------------------------------	*/
GLOBAL int qreplace_once (	char *source,
							const char *replace,
							const size_t rlen,
							const char *by,
							const size_t blen
						)
{
	char 	*found;
	size_t	flen;

#if CHECK_REPLACE_LEN
	if (rlen!=strlen(replace))
	{	fprintf(stdout, "Fehler in qreplace_once:\n");
		fprintf(stdout, "rlen= %d\n", rlen);
		fprintf(stdout, "strlen(%s)= %d\n", replace, strlen(replace));
	}
	if (blen!=strlen(by))
	{	fprintf(stdout, "Fehler in qreplace_once:\n");
		fprintf(stdout, "blen= %d\n", blen);
		fprintf(stdout, "strlen(%s)= %d\n", by, strlen(by));
	}
#endif
	
	if ( source[0]=='\0' )		return 0;
	if ( replace[0]=='\0' )		return 0;

	if ( (found= strstr(source, replace))==NULL )	return 0;

	flen= strlen(found);

	/* Zu Ersetzendes entfernen */
	memmove(found, found+rlen, flen-rlen+1);

	/* Platz schaffen fuer neues und dorthin kopieren */
	if ( by[0]!=EOS )
	{	flen= strlen(found);
		memmove(found+blen, found, flen+1);
		memcpy(found, by, blen);
	}
	
	return 1;
}	/* qreplace_once */


/*	------------------------------------------------------------
	qreplace_last() ersetzt in <s> das letzte <rep> durch <by>
	------------------------------------------------------------	*/
GLOBAL int qreplace_last (	char *source,
							const char *replace,
							const size_t rlen,
							const char *by,
							const size_t blen
						)
{
	char *found, *look, *last;

#if CHECK_REPLACE_LEN
	if (rlen!=strlen(replace))
	{	fprintf(stdout, "Fehler in qreplace_last:\n");
		fprintf(stdout, "rlen= %d\n", rlen);
		fprintf(stdout, "strlen(%s)= %d\n", replace, strlen(replace));
	}
	if (blen!=strlen(by))
	{	fprintf(stdout, "Fehler in qreplace_last:\n");
		fprintf(stdout, "blen= %d\n", blen);
		fprintf(stdout, "strlen(%s)= %d\n", by, strlen(by));
	}
#endif

	if ( source[0]=='\0' )		return 0;
	if ( replace[0]=='\0' )		return 0;
	
	look= source;
	last= NULL;

	while ( (found= strstr(look, replace))!=NULL )
	{	look= found+1;
		last= found;
	}

	if (last!=NULL)
	{	return ( qreplace_once(last, replace, rlen, by, blen) );
	}
	
	return 0;
}	/* qreplace_last */



/*	------------------------------------------------------------
	qreplace_all() ersetzt in <s> alle <rep> durch <by>
	------------------------------------------------------------	*/
GLOBAL int qreplace_all (	char *source,
							const char *replace,
							const size_t rlen,
							const char *by,
							const size_t blen
						)
{
	char 	*found;
	size_t	flen, i;

#if CHECK_REPLACE_LEN
	if (rlen!=strlen(replace))
	{	fprintf(stdout, "Fehler in qreplace_all:\n");
		fprintf(stdout, "rlen= %d\n", rlen);
		fprintf(stdout, "strlen(%s)= %d\n", replace, strlen(replace));
	}
	if (blen!=strlen(by))
	{	fprintf(stdout, "Fehler in qreplace_all:\n");
		fprintf(stdout, "blen= %d\n", blen);
		fprintf(stdout, "strlen(%s)= %d\n", by, strlen(by));
	}
#endif
	
	if ( source[0]=='\0' )		return 0;
	if ( replace[0]=='\0' )		return 0;

	if ( (found= strstr(source, replace))==NULL )	return 0;

	if (rlen==blen)
	{
		while ( found!=NULL )
		{
			for (i=0; i<blen; i++)
			{	found[i]= by[i];
			}
			found= strstr(found+blen, replace);
		}
		return 1;
	}

	while ( found!=NULL )
	{	flen= strlen(found);

		/* Zu Ersetzendes entfernen */
		memmove(found, found+rlen, flen-rlen+1);
	
		/* Platz schaffen fuer neues und dorthin kopieren */
		if ( by[0]!=EOS )
		{	flen= strlen(found);
			memmove(found+blen, found, flen+1);
			memcpy(found, by, blen);
			found= strstr(found+blen, replace);
		}
		else
		{	found= strstr(found, replace);
		}
		
	}

	return 1;
}	/* qreplace_all */





/*	############################################################
	#
	# Loeschen von Strings
	#
	############################################################	*/
GLOBAL int delete_once ( char *source, const char *to_delete )
{
	return(replace_once (source, to_delete, ""));
}

GLOBAL int delete_last ( char *source, const char *to_delete )
{
	return(replace_last (source, to_delete, ""));
}

GLOBAL int delete_all ( char *source, const char *to_delete )
{
	return(replace_all (source, to_delete, ""));
}


GLOBAL int qdelete_once ( char *source, const char *to_delete, const size_t dlen )
{
	return ( qreplace_once (source, to_delete, dlen, "", 0) );
}

GLOBAL int qdelete_last ( char *source, const char *to_delete, const size_t dlen )
{
	return ( qreplace_last (source, to_delete, dlen, "", 0) );
}

GLOBAL int qdelete_all ( char *source, const char *to_delete, const size_t dlen )
{
	return ( qreplace_all (source, to_delete, dlen, "", 0) );
}



/*	------------------------------------------------------------
	del_right_spaces() entfernt Leerzeichen am Ende
	------------------------------------------------------------	*/
GLOBAL void del_right_spaces ( char *s )
{
	size_t	sl;
	
	sl= strlen(s);

	while (	(sl>0) && (s[sl-1]==' ') )
	{	s[sl-1]= EOS;
		sl--;
	}

}	/* del_right_spaces */



/*	------------------------------------------------------------
	del_whitespaces() entfernt Leerzeichen und Tabs am Anfang
	und Ende des uebergebenen Strings.
	------------------------------------------------------------	*/
GLOBAL void del_whitespaces ( char *s)
{
	size_t	sl;
	
	/* Neue Methode: schneller */
	
	char *p1st = s;
	
	while (*p1st != EOS && (*p1st == ' ' || *p1st == '\t') )
	{	++p1st;
	}

	sl = strlen(p1st);
	
	if (*p1st != EOS && s != p1st)
	{	
		memmove(s, p1st, sl+1);
	}
	
	/* Rechts TAB's und Leerzeichen entfernen */
	if (sl > 0)
	{
		p1st = s + sl - 1;
		while (*p1st == ' ' || *p1st == '\t')
			--p1st;
		p1st[1] = EOS;
	}
}	/*del_whitespaces*/


/*	--------------------------------------------------------------
	get_brackets_ptr()
	Ermittelt aus einem String wie "!raw [ stg, tex ] foo bar"
	oder "!docinfo [author] Dirk Hagedorn" den Zeiger auf das
	erste Zeichen hinter der ersten [ und die Anzahl der Zeichen,
	die bis zur ersten ] folgen.
	->	s:		Der zu untersuchende String
	<-	cont:	Zeiger auf das erste Zeichen des Inhalts
		data:	Zeiger auf das erste Zeichen der Daten
		0:		fehlerhafte Syntax (keine [ und ] gefunden)
		sonst:	Laenge des Inhaltes
	--------------------------------------------------------------	*/
GLOBAL size_t get_brackets_ptr ( char *s, char **cont, char **data )
{
	char *ptr;
	size_t len;
	
	ptr= s;
	*cont= NULL;
	*data= NULL;
	len= 0;
	
	while (*ptr!=EOS)
	{
		if (*ptr=='[')
		{	*cont= ptr+1;
		}
		
		if (*ptr==']')
		{	if (*cont!=NULL)
			{	*data= ptr+1;
				len= ptr - *cont;
			}
			return len;
		}
		
		ptr++;
	}

	return 0;	
	
}	/* get_brackets_ptr */


/* New since r6pl15 [NHz] */
/*	--------------------------------------------------------------
	get_two_brackets_ptr()
	Ermittelt aus einem String wie "!doclayout [ ps, rtf ] [paper] foo bar"
	die Zeiger auf die ersten Zeichen hinter den ersten [ und die
	Anzahl der Zeichen, die bis zur ersten ] folgen.
	->	s:		Der zu untersuchende String
	<-	cont_format:	Zeiger auf das erste Zeichen der Formate
	    cont_content: Zeiger auf das erste Zeichen des Inhalts
		data:	Zeiger auf das erste Zeichen der Daten
		0:		fehlerhafte Syntax (keine [ und ] gefunden)
		sonst:	Laenge des Inhaltes
	--------------------------------------------------------------	*/
GLOBAL struct size_brackets get_two_brackets_ptr ( char *s, char **cont_format, char **cont_content, char **data )
{
	char *ptr;
	struct size_brackets len;
	BOOLEAN firstend;
	
	ptr= s;
	*cont_format= NULL;
	*cont_content= NULL;
	*data= NULL;
	len.format= 0;
	len.content= 0;
	
	firstend = FALSE;

	while (*ptr!=EOS)
	{
		if ((*ptr=='[') && (!firstend))
		{	*cont_format= ptr+1;
		}
		
		else if ((*ptr==']') && (!firstend))
		{	firstend = TRUE;
			len.format= ptr - *cont_format;
		}
		
		else if ((*ptr=='[') && (firstend))
		{	*cont_content= ptr+1;
		}

		else if ((*ptr==']') && (firstend))
		{	if (*cont_content!=NULL)
			{	*data= ptr+1;
				len.content= ptr - *cont_content;
			}
			return len;
		}
		
		ptr++;
	}

	return len;	
	
}	/* get_two_brackets_ptr */


/*	--------------------------------------------------------------
	get_8bit_ptr() ermittelt die Position des ersten 8-Bit-Chars
	eines Strings.
	->	s:	Zeiger auf den String
	<-	Zeiger auf das erste 8-Bit-Zeichen bzw. NULL, wenn kein
		8-Bit-Zeichen enthalten ist.
	--------------------------------------------------------------	*/
GLOBAL char *get_8bit_ptr ( char *s )
{
	char *ptr;
	
	ptr= s;
	
	while ( *ptr!=EOS )
	{	if ( (UCHAR) *ptr > 127 )
		{	return ptr;
		}
		ptr++;
	}
	
	return NULL;
}


/*	--------------------------------------------------------------
	get_section_ptr() ermittelt die Position des ersten
	Paragraphen-Zeichens eines Strings, dass bei DOS und OS/2
	unter \025 zu finden ist
	->	s:	Zeiger auf den String
	<-	Zeiger auf das Zeichen bzw. NULL, wenn nicht enthalten
	--------------------------------------------------------------	*/
GLOBAL char *get_section_ptr ( char *s )
{
	char *ptr;
	
	ptr= s;
	
	while ( *ptr!=EOS )
	{	if ( (UCHAR) *ptr == '\025' )
		{	return ptr;
		}
		ptr++;
	}
	
	return NULL;
}	/* get_section_ptr */


/*	--------------------------------------------------------------
	get_1stchar_ptr() ermittelt die Position des ersten Zeichens,
	das sich von ' ' und '\t' unterscheidet.
	->	s:	Zeiger auf den String
	<-	Zeiger auf das erste Zeichen oder NULL, wenn der String
		leer oder nur Blanks und/der TABs enthaelt
	--------------------------------------------------------------	*/
GLOBAL char *get_1stchar_ptr ( char *s )
{
	char *ptr;
	
	ptr= s;
	
	while ( *ptr!=EOS )
	{	if ( *ptr!=' ' && *ptr!='\t' )
		{	return ptr;
		}
		ptr++;
	}
	
	return NULL;
}



/*	############################################################
	#
	# Umwandlungsroutinen
	#
	############################################################	*/

/*	----------------------------------------------
	TABs in Leerzeichen umwandeln und dabei die
	Tabposition beachten
	----------------------------------------------	*/
GLOBAL void tabs2spaces (char *s, const int tw)
{
	char n[1024], one[2]={0, 0};
	size_t i, nl;

	/* r6pl2: Wenn !bDocTabwidth==0 dann nicht ersetzen! */
	if (tw==0)
	{	return;
	}

	n[0]= EOS;
	nl= 0;
	
	for (i=0; i<strlen(s); i++)
	{	if (s[i]=='\t')
		{	do
			{	strcat(n, " ");
				nl++;
			}	while ( (nl % tw)!=0 );
		}
		else
		{	one[0]= s[i];
			strcat(n, one);
			nl++;
		}
	}

	strcpy(s, n);	

}	/* tabs2spaces */



/*	----------------------------------------------
	Dezimalzahlen in roemische Zahlen umwandeln
	I =    1     IV      =    4
	V =    5     IX      =    9
	X =   10     XL      =   40
	L =   50     XC      =   90
	C =  100     CD      =  400
	D =  500     CM      =  900
	M = 1000     MCMXCVI = 1996
	----------------------------------------------	*/

GLOBAL char *itoroman ( int value, char *string )
{
	int	t, c, d, o, i;
	
	static const char *cent[]=	{	"", "c", "cc", "ccc", "cd", "d", "dc", "dcc", "dccc", "cm"	};
	static const char *deci[]=	{	"", "x", "xx", "xxx", "xl", "l", "lx", "lxx", "lxxx", "xc"	};
	static const char *ones[]=	{	"", "i", "ii", "iii", "iv", "v", "vi", "vii", "viii", "ix"	};

	string[0]= '\0';

	if (value<=0)
	{	return(string);
	}
	
	t= value/1000;
	c= (value-t*1000)/100;
	d= (value-t*1000-c*100)/10;
	o= (value-t*1000-c*100-d*10);
	
	
	for (i=0; i<t; i++)	strcat(string, "m") ;

	strcat(string, cent[c]);	
	strcat(string, deci[d]);	
	strcat(string, ones[o]);	
	
	return(string);
}	/* itoroman */


/*	----------------------------------------------
	String in Grossbuchstaben umwandeln
	----------------------------------------------	*/
GLOBAL void my_strupr ( char *string )
{
#if HAVE_STRUPR
	strupr(string);
#else
	size_t i;
	if (string[0]==EOS)
	{	return;
	}
	
	for (i=0; i<strlen(string); i++)
	{	if ( string[i]>='a' && string[i]<='z' )
		{
			string[i] = (char)toupper(string[i]);
		}
	}
#endif
}	/* my_strupr */

/*	----------------------------------------------
	String in Kleinbuchstaben umwandeln
	----------------------------------------------	*/
GLOBAL void my_strlwr ( char *string )
{
#if HAVE_STRLWR
	strlwr(string);
#else
	size_t i;
	if (string[0]==EOS)
	{	return;
	}
	
	for (i=0; i<strlen(string); i++)
	{	if ( string[i]>='A' && string[i]<='Z' )
		{
			string[i] = (char)tolower(string[i]);
		}
	}
#endif
}	/* my_strlwr */


/*	----------------------------------------------
	Strings caseinsensitiv vergleichen
	----------------------------------------------	*/
GLOBAL int my_stricmp ( const char *s1, const char *s2 )
{

#if HAVE_STRICMP
	  return stricmp(s1, s2);
#elif HAVE_STRCASECMP
	  return strcasecmp(s1, s2);
#else
	  return strcmp(s1, s2);
#endif

}	/* my_stricmp */

/*	----------------------------------------------
	Strings caseinsensitiv vergleichen
	max. n Zeichen
	----------------------------------------------	*/
GLOBAL int my_strnicmp ( const char *s1, const char *s2, size_t len )
{

#if HAVE_STRNICMP
	return strnicmp(s1, s2, len);
#else
	return strncmp(s1, s2, len);
#endif

}	/* my_stricmp */

/*	############################################################
	# str.c
	############################################################	*/

