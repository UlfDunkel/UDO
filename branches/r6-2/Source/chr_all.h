/*	############################################################
	# @(#) chr_all.h
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
	# @(#) Allgemeine Uebersetzungstabellen
	############################################################	*/

#include	"portab.h"

#ifndef ID_CHR_ALL_H
#define	ID_CHR_ALL_H
const char *id_chr_all_h= "@(#) chr_all.h   25.11.1997";
#endif

/*	------------------------------------------------------------	*/

typedef struct _quoteinfo
{
	char c;
	char quoted[32];
}	QUOTEINFO;

/*	------------------------------------------------------------	*/

#define	MAXTEX7BIT	15
LOCAL /*const*/ QUOTEINFO tex7bit[MAXTEX7BIT]=
{
	{	'\025',	"\\S{}"				},	/* Paragraph unter DOS und OS/2 */
	{	'\"',	"{\\symbol{34}}"	},
	{	'#',	"\\#"				},
	{	'$',	"\\$"				},
	{	'%',	"\\%"				},
	{	'&',	"\\&"				},
	{	'<',	"$<$"				},
	{	'>',	"$>$"				},
	{	'\\',	"$\\backslash$"		},
	{	'_',	"\\_"				},
	{	'{',	"\\{"				},
	{	'|',	"$\\mid$"			},
	{	'}',	"\\}"				},
	{	'^',	"{\\symbol{94}}"	},
	{	'`',	"{\\symbol{96}}"	},
#if 0
	{	'[',	"{\\symbol{91}}"	},
	{	']',	"{\\symbol{93}}"	}
#endif
};

/*	------------------------------------------------------------	*/

#define	MAXRTF7BIT	4
LOCAL /*const*/ QUOTEINFO rtf7bit[MAXRTF7BIT]=
{
	{	'\025',		"\\'A7"	},	/* Paragraph unter DOS und OS/2 */
	{	'{',		"\\{"	},
	{	'}',		"\\}"	},
	{	'\\',		"\\\\"	}
};

/*	------------------------------------------------------------	*/

#define	MAXWIN7BIT	4
LOCAL /*const*/ QUOTEINFO win7bit[MAXWIN7BIT]=
{
	{	'\025',		"\\'A7"	},	/* Paragraph unter DOS und OS/2 */
	{	'{',		"\\{"	},
	{	'}',		"\\}"	},
	{	'\\',		"\\\\"	}
};

/*	------------------------------------------------------------	*/

#define	MAXHTML7BIT	5
LOCAL /*const*/ QUOTEINFO html7bit[MAXHTML7BIT]=
{
	{	'\025',		"&sect;"	},	/* Paragraph unter DOS und OS/2 */
	{	'&',		"&amp;"		},
	{	'<',		"&lt;"		},
	{	'>',		"&gt;"		},
	{	'\"',		"&quot;"	}
};

/*	------------------------------------------------------------	*/

#define	MAXHTAG7BIT	3
LOCAL /*const*/ QUOTEINFO htag7bit[MAXHTAG7BIT]=
{
	{	'&',		"&&"		},
	{	'<',		"&<"		},
	{	'\\',		"&\\"		}
};

/*	------------------------------------------------------------	*/

#define	MAXLDS7BIT	9
LOCAL /*const*/ QUOTEINFO lds7bit[MAXLDS7BIT]=
{
	{	'\025',		"&sect;"	},	/* Paragraph unter DOS und OS/2 */
	{	'&',		"&amp;"		},
	{	'<',		"&lt;"		},
	{	'>',		"&gt;"		},
	{	'$',		"&dollar;"	},
	{	'#',		"&num;"		},
	{	'%',		"&percnt;"	},
	{	'\"',		"&dquot;"	},
	{	'~',		"&tilde;"	}
};

/*	------------------------------------------------------------	*/

#define	MAXLYX7BIT	1
LOCAL /*const*/ QUOTEINFO lyx7bit[MAXLYX7BIT]=
{
	{	'\\',		"\\backslash"INDENT_S	},
};

/*	------------------------------------------------------------	*/

#define	MAXIPF7BIT	3
LOCAL /*const*/ QUOTEINFO ipf7bit[MAXIPF7BIT]=
{
	{	':',		"&colon."	},
	{	'&',		"&amp."		},
	{	'.',		"&per."		},
};



typedef struct _unitable
{
	char	uni[8];
	char	win[16];
	char	tex[16];
	char	html[16];
	char	lyx[4];		/* PL14 */
}	UNITABLE;

#define	UNITABLESIZE	63

LOCAL const UNITABLE unitab[UNITABLESIZE]=
{
	{	"(!\"a)",	"\\'E4",	"\\\"a",	"&auml;",	"\0xE4"	},
	{	"(!\"e)",	"\\'EB",	"\\\"{e}",	"&euml;",	"\0xEB"	},
	{	"(!\"i)",	"\\'EF",	"\\\"{i}",	"&iuml;",	"\0xEF"	},
	{	"(!\"o)",	"\\'F6",	"\\\"o",	"&ouml;",	"\0xF6"	},
	{	"(!\"u)",	"\\'FC",	"\\\"u",	"&uuml;",	"\0xFC"	},
	{	"(!\"y)",	"\\'FF",	"\\\"{y}",	"&yuml;",	"\0xFF"	},
	{	"(!\"s)",	"\\'DF",	"{\\ss}",	"&szlig;",	"\0xDF"	},
	{	"(!\"A)",	"\\'C4",	"\\\"A",	"&Auml;",	"\0xC4"	},
	{	"(!\"E)",	"\\'CB",	"\\\"{E}",	"&Euml;",	"\0xCB"	},
	{	"(!\"I)",	"\\'CF",	"\\\"{I}",	"&Iuml;",	"\0xCF"	},
	{	"(!\"O)",	"\\'D6",	"\\\"O",	"&Ouml;",	"\0xD6"	},
	{	"(!\"U)",	"\\'DC",	"\\\"U",	"&Uuml;",	"\0xDC"	},	/* 12 */

	{	"(!'a)",	"\\'E1",	"\\'{a}",	"&aacute;",	"\0xE1"	},
	{	"(!'e)",	"\\'E9",	"\\'{e}",	"&eacute;",	"\0xE9"	},
	{	"(!'i)",	"\\'ED",	"\\'{i}",	"&iacute;",	"\0xED"	},
	{	"(!'o)",	"\\'F3",	"\\'{o}",	"&oacute;",	"\0xF3"	},
	{	"(!'u)",	"\\'FA",	"\\'{u}",	"&uacute;",	"\0xFA"	},
	{	"(!'y)",	"\\'FD",	"\\'{y}",	"&yacute;",	"\0xFD"	},
	{	"(!'A)",	"\\'C1",	"\\'{A}",	"&Aacute;",	"\0xC1"	},
	{	"(!'E)",	"\\'C9",	"\\'{E}",	"&Eacute;",	"\0xC9"	},
	{	"(!'I)",	"\\'CD",	"\\'{I}",	"&Iacute;",	"\0xCD"	},
	{	"(!'O)",	"\\'D3",	"\\'{O}",	"&Oacute;",	"\0xD3"	},
	{	"(!'U)",	"\\'DA",	"\\'{U}",	"&Uacute;",	"\0xDA"	},
	{	"(!'Y)",	"\\'DD",	"\\'{Y}",	"&Yacute;",	"\0xDD"	},	/* 12 */

	{	"(!`a)",	"\\'E0",	"\\`{a}",	"&agrave;",	"\0xE0"	},
	{	"(!`e)",	"\\'E8",	"\\`{e}",	"&egrave;",	"\0xE8"	},
	{	"(!`i)",	"\\'EC",	"\\`{i}",	"&igrave;",	"\0xEC"	},
	{	"(!`o)",	"\\'F2",	"\\`{o}",	"&ograve;",	"\0xF2"	},
	{	"(!`u)",	"\\'F9",	"\\`{u}",	"&ugrave;",	"\0xF9"	},
	{	"(!`A)",	"\\'C0",	"\\`{A}",	"&Agrave;",	"\0xC0"	},
	{	"(!`E)",	"\\'C8",	"\\`{E}",	"&Egrave;",	"\0xC8"	},
	{	"(!`I)",	"\\'CC",	"\\`{I}",	"&Igrave;",	"\0xCC"	},
	{	"(!`O)",	"\\'D2",	"\\`{O}",	"&Ograve;",	"\0xD2"	},
	{	"(!`U)",	"\\'D9",	"\\`{U}",	"&Ugrave;",	"\0xD9"	},	/* 10 */

	{	"(!^a)",	"\\'E2",	"\\^{a}",	"&acirc;",	"\0xE2"	},
	{	"(!^e)",	"\\'EA",	"\\^{e}",	"&ecirc;",	"\0xEA"	},
	{	"(!^i)",	"\\'EE",	"\\^{i}",	"&icirc;",	"\0xEE"	},
	{	"(!^o)",	"\\'F4",	"\\^{o}",	"&ocirc;",	"\0xF4"	},
	{	"(!^u)",	"\\'FB",	"\\^{u}",	"&ucirc;",	"\0xFB"	},
	{	"(!^A)",	"\\'C2",	"\\^{A}",	"&Acirc;",	"\0xC2"	},
	{	"(!^E)",	"\\'CA",	"\\^{E}",	"&Ecirc;",	"\0xCA"	},
	{	"(!^I)",	"\\'CE",	"\\^{I}",	"&Icirc;",	"\0xCE"	},
	{	"(!^O)",	"\\'D4",	"\\^{O}",	"&Ocirc;",	"\0xD4"	},
	{	"(!^U)",	"\\'DB",	"\\^{U}",	"&Ucirc;",	"\0xDB"	},	/* 10 */

	{	"(!~a)",	"\\'E3",	"\\~{a}",	"&atilde;",	"\0xE3"	},
	{	"(!~n)",	"\\'F1",	"\\~{n}",	"&ntilde;",	"\0xF1"	},
	{	"(!~o)",	"\\'F5",	"\\~{o}",	"&otilde;",	"\0xF5"	},
	{	"(!~A)",	"\\'C3",	"\\~{A}",	"&Atilde;",	"\0xC3"	},
	{	"(!~N)",	"\\'D1",	"\\~{N}",	"&Ntilde;",	"\0xD1"	},
	{	"(!~O)",	"\\'D5",	"\\~{O}",	"&Otilde;",	"\0xD5"	},	/*  6 */

	{	"(!.a)",	"\\'E5",	"{\\aa}",	"&aring;",	"\0xE5"	},
	{	"(!.A)",	"\\'C5",	"{\\AA}",	"&Aring;",	"\0xC5"	},	/*  2 */

	{	"(!&ae)",	"\\'E6",	"{\\ae}",	"&aelig;",	"\0xE6"	},
	{	"(!&AE)",	"\\'C6",	"{\\AE}",	"&AElig;",	"\0xC6"	},
	{	"(!&oe)",	"\\'9C",	"{\\oe}",	"&#156;",	"\0x9C"	},
	{	"(!&OE)",	"\\'8C",	"{\\OE}",	"&#140;",	"\0x8C"	},	/*  4 */

	{	"(!,c)",	"\\'E7",	"\\c{c}",	"&ccedil;",	"\0xE7"	},
	{	"(!,C)",	"\\'C7",	"\\c{C}",	"&Ccedil;",	"\0xC7"	},	/*  2 */

	{	"(!_a)",	"\\'AA",	"\\b{a}",	"&#170;",	"\0xAA"	},
	{	"(!_o)",	"\\'BA",	"\\b{o}",	"&#186;",	"\0xBA"	},	/*  2 */

	{	"(!\\o)",	"\\'F8",	"{\\o}",	"&oslash;",	"\0xF8"	},
	{	"(!\\O)",	"\\'D8",	"{\\O}",	"&Oslash;",	"\0xD8"	},	/*  2 */

	{	"(!#S)",	"\\'A7",	"\\S{}",	"&sect;",	"\0xA7"	},
};


/*	############################################################
	# chr_all.h
	############################################################	*/

