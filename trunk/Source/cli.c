/*	############################################################
	# @(#) cli.c (Kommandozeilen-Version)
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
#ifndef ID_CLI_C
#define ID_CLI_C
const char *id_cli_c= "@(#) cli.c       21.08.1998";
#endif

#include	"import.h"
#include	<stdio.h>	
#include	<string.h>	
#include	<stdlib.h>
#include	"portab.h"
#include	"version.h"
#include	"constant.h"
#include	"udo_type.h"
#include	"file.h"
#include	"cfg.h"
#include	"msg.h"
#include	"udo.h"
#include        "udomem.h"

#ifdef __TOS__
	#ifdef USE_PCTOS
		#include <tos.h>
	#else
		#include	<mintbind.h>
	#endif
#endif

#include	"export.h"
#include	"gui.h"


/*	############################################################
	# Typen
	############################################################	*/
typedef enum
{
	DEUTSCH,
	ENGLISH
} t_lang;




/*	############################################################
	# Variablen
	############################################################	*/
LOCAL char		strPrgname[33];	/* der Name dieses Programms */
LOCAL t_lang	eLanguage;		/* Sprache */

LOCAL BOOLEAN	bHoldKey;
LOCAL BOOLEAN	bShowArgs;
LOCAL BOOLEAN   bShowHelp;
LOCAL BOOLEAN   bShowVersion;
LOCAL BOOLEAN	bShowIdent;
LOCAL int last_percent;

#define	PRGNAME		"udo"
#define	COPYRIGHT	"Copyright (c) 1995-2001 by Dirk Hagedorn (UDO is Open Source)"


/*	############################################################
	# lokale Prototypen
	############################################################	*/
LOCAL void show_ident ( void );
LOCAL void show_version ( void );
LOCAL void show_usage ( void );
LOCAL void show_use_help ( void );
LOCAL void show_help ( void );
LOCAL void show_unknown ( const char *s );
LOCAL void wait_on_keypress ( void );

LOCAL int getcliopt ( int *counter, const char *arg, const char *argnext, const BOOLEAN from_file );


/*	############################################################
	# Optionen
	############################################################	*/
typedef struct _cliopt
{
	char		longname[16];		/* lange Option								*/
	char		shortname[6];		/* kurze Option								*/
	char		type;				/* Typ: b=Boolean, c=char[]					*/
	BOOLEAN	needs2;					/* folgt der Option ein Parameter?			*/
	void			*var;			/* Variable, die geaendert wird				*/
	int			val;				/* Wert, der bei Benutzung zugewiesen wird	*/
}	CLIOPT;


LOCAL const CLIOPT cliopt[]=
{
	{	"--asc",			"-a",		'b',	FALSE,	&desttype,			TOASC	},
	{	"--amg",			"",			'b',	FALSE,	&desttype,			TOAMG	},
	{	"--argv",			"",			'b',	FALSE,	&bShowArgs,			TRUE	},
	{	"--check",			"",			'b',	FALSE,	&bCheckMisc,		TRUE	},
	{	"--c",				"-c",		'b',	FALSE,	&desttype,			TOSRC	},
	{	"--drc",			"",			'b',	FALSE,	&desttype,			TODRC	},
	{	"--force-long",		"",			'b',	FALSE,	&bForceLong,		TRUE	},
	{	"--force-short",	"",			'b',	FALSE,	&bForceShort,		TRUE	},
	{	"--hold",			"-H",		'b',	FALSE,	&bHoldKey,			TRUE	},
	{	"--help",			"",			'b',	FALSE,	&bShowHelp,			TRUE	},
	{	"--helptag",		"-g",		'b',	FALSE,	&desttype,			TOHPH	},
	{	"--html",			"-h",		'b',	FALSE,	&desttype,			TOHTM	},
	{	"--htmlhelp",		"-hh",		'b',	FALSE,	&desttype,			TOMHH	},
	{	"--ident",			"",			'b',	FALSE,	&bShowIdent,		TRUE	},
	{	"--info",			"-i",		'b',	FALSE,	&desttype,			TOINF	},
	{	"--ipf",			"",			'b',	FALSE,	&desttype,			TOIPF	},
	{	"--linuxdoc",		"-x",		'b',	FALSE,	&desttype,			TOLDS	},
	{	"--lyx",			"",			'b',	FALSE,	&desttype,			TOLYX	},
	{	"--man",			"-m",		'b',	FALSE,	&desttype,			TOMAN	},
	{	"--map",			"",			'b',	FALSE,	&bUseIdMapFileC,	TRUE	},
	{	"--map-pas",		"",			'b',	FALSE,	&bUseIdMapFilePas,	TRUE	},
	{	"--map-vb",			"",			'b',	FALSE,	&bUseIdMapFileVB,	TRUE	},
	{	"--map-gfa",		"",			'b',	FALSE,	&bUseIdMapFileGFA,	TRUE	},
	{	"--no-hypfile",		"-y",		'b',	FALSE,	&bNoHypfile,		TRUE	},
	{	"--no-idxfile",		"-d",		'b',	FALSE,	&bNoIdxfile,		TRUE	},
	{	"--no-logfile",		"-l",		'b',	FALSE,	&bNoLogfile,		TRUE	},
	{	"--no-warnings",	"-W",		'b',	FALSE,	&bNoWarnings,		TRUE	},
	{	"--nroff",			"-n",		'b',	FALSE,	&desttype,			TONRO	},
	{	"--outfile",		"-o",		'c',	TRUE,	outfile.full,		0		},
	{	"--pascal",			"-P",		'b',	FALSE,	&desttype,			TOSRP	},
	{	"--pdflatex",		"-f",		'b',	FALSE,	&desttype,			TOPDL	},
	{	"--ps",				"",			'b',	FALSE,	&desttype,			TOKPS	},
	{	"--pchelp",			"-p",		'b',	FALSE,	&desttype,			TOPCH	},
	{	"--quiet",			"-q",		'b',	FALSE,	&bBeQuiet,			TRUE	},
	{	"--quickview",		"--aqv",	'b',	FALSE,	&desttype,			TOAQV	},
	{	"--rtf",			"-r",		'b',	FALSE,	&desttype,			TORTF	},
	{	"--stg",			"-s",		'b',	FALSE,	&desttype,			TOSTG	},
	{	"--save-upr",		"",			'b',	FALSE,	&bUseUPRfile,		TRUE	},
	{	"--test",			"",			'b',	FALSE,	&bTestmode,			TRUE	},
	{	"--tex",			"-t",		'b',	FALSE,	&desttype,			TOTEX	},
	{	"--txt",			"-a",		'b',	FALSE,	&desttype,			TOASC	},
	{	"--tree",			"",			'b',	FALSE,	&bUseTreefile,		TRUE	},
	{	"--udo",			"-u",		'b',	FALSE,	&desttype,			TOUDO	},
	{	"--verbose",		"",			'b',	FALSE,	&bVerbose,			TRUE	},
	{	"--version",		"",			'b',	FALSE,	&bShowVersion,		TRUE	},
	{	"--vision",			"-v",		'b',	FALSE,	&desttype,			TOTVH	},
	{	"--win",			"-w",		'b',	FALSE,	&desttype,			TOWIN	},
	{	"--win4",			"-4",		'b',	FALSE,	&desttype,			TOWH4	},

	/* Endekennung */
	{	"",					"",			'c',	FALSE,	NULL,				0		},
};


/*	----------------------------------------------------------------------
	Programm-Ausgaben
	----------------------------------------------------------------------	*/
LOCAL const char	*Usage[]=
{	"Gebrauch: %s [-acdDghHilmnpPqrstvwWxy@] [-o outfile] file",
	"usage: %s [-acdDghHilmnpPqrstvwWxy@] [-o outfile] file"
};

LOCAL const char	*Use_Help[]=
{	"          Mehr Hilfe mit --help",
	"          use --help for more information"
};

LOCAL const char	*Prog_Help[]=
{
	"-a,    --asc           ins ASCII-Format konvertieren\n"
	"       --amg           ins AmigaGuide-Format konvertieren\n"
	"--aqv, --quickview     ins Apple-QuickView-Format konvertieren\n"
	"-c,    --c             C-Sourcecode erzeugen\n"
	"       --check         Ueberpruefungen aktivieren\n"
	"       --drc           ins David's-Readme-Compiler-Format konvertieren\n"
	"-d,    --noidxfile     kein Indexfile (.ux?) anlegen\n"
	"-D sym                 Symbol <sym> setzen\n"
	"       --force-long    immer lange Dateinamen erzeugen\n"
	"       --force-short   immer kurze Dateinamen erzeugen\n"
	"-f     --pdflatex      ins PDFLaTeX-Format konvertieren\n"
	"-g,    --helptag       ins HP-Helptag-SGML-Format konvertieren\n"
	"-h,    --html          ins HTML-Format konvertieren\n"
	"-hh,   --htmlhelp      ins HTML-Help-Format konvertieren\n"
	"-H,    --hold          am Ende auf Tastendruck warten\n"
	"-i,    --info          ins GNU-Texinfo-Format konvertieren\n"
	"       --ipf           ins OS/2-IPF-Format konvertieren\n"
	"       --lyx           ins LyX-Format konvertieren\n"
	"-l,    --nologfile     kein Logfile (.ul?) anlegen\n"
	"-m,    --man           in eine Manualpage konvertieren\n"
	"       --map           C-Headerfile mit WinHelp-Jump-IDs erzeugen\n"
	"       --map-pas       Pascal-Headerfile mit WinHelp-Jump-IDs erzeugen\n"
	"       --map-vb        VB-Headerfile mit WinHelp-Jump-IDs erzeugen\n"
	"       --map-gfa       GFA-Headerfile mit WinHelp-Jump-IDs erzeugen\n"
	"-n,    --nroff         ins nroff-Format konvertieren\n"
	"-o F,  --outfile F     Ausgaben in die Datei F schreiben\n"
	"-p,    --pchelp        ins Pure-C-Help-Quelltextformat konvertieren\n"
	"-P,    --pascal        Pascal-Sourcecode erzeugen\n"
	"       --ps            ins PostScript-Format konvertieren\n"
	"-q,    --quiet         Ausgaben auf stdout und stderr unterdruecken\n"
	"-r,    --rtf           ins Rich Text Format konvertieren\n"
	"       --save-upr      Projekt-Datei (.upr) ausgeben\n"
	"-s,    --stg           ins ST-Guide-Quelltextformat konvertieren\n"
	"       --test          Testmodus (kein Outfile erzeugen)\n"
	"-t,    --tex           ins LaTeX-Format konvertieren\n"
	"       --tree          Include-Baum (.ut?) ausgeben\n"
  "       --verbose       ausfuehrliche Konvertierungs-Infos anzeigen\n"
	"-u,    --udo           Dateien sammeln und in einer UDO-Datei sichern\n"
	"-v,    --vision        ins Turbo-Vision-Help-Format konvertieren\n"
	"-w,    --win           ins WinHelp-Quelltextformat konvertieren\n"
	"-w4,   --win4          ins WinHelp4-Quelltextformat konvertieren\n"
	"-W,    --no-warnings   Warnungen unterdruecken\n"
	"-x,    --linuxdoc      ins Linuxdoc-SGML-Format konvertieren\n"
	"-y,    --no-hypfile    kein Hyphenfile (.uh?) anlegen\n"
	"-@ F                   Optionen aus der Datei F lesen\n"
	"       --help          diese Informationen anzeigen und beenden\n"
  "       --version       Versionsinformationen anzeigen und beenden",




	"-a,    --asc           convert to ASCII\n"
	"       --amg           convert to AmigaGuide\n"
	"--aqv, --quickview     convert to Apple QuickView\n"
	"-c,    --c             generate C sourcecode\n"
	"       --check         activate checkings\n"
	"       --drc           convert to David's Readme Compiler format\n"
	"-d,    --no-idxfile    don't generate index file (.ux?)\n"
	"-D sym                 set symbol <sym>\n"
	"       --force-long    save always long filenames\n"
	"       --force-short   save always short filenames\n"
	"-f     --pdflatex      generate PDFLaTeX sourcecode\n"
	"-g,    --helptag       convert to HP Helptag SGML\n"
	"-h,    --html          convert to HTML\n"
	"-hh,   --htmlhelp      convert to HTML-Help\n"
	"-H,    --hold          press key when udo finishs\n"
	"-i,    --info          convert to GNU Texinfo\n"
	"       --ipf           convert to OS/2 IPF format\n"
	"       --lyx           convert to LyX\n"
	"-l,    --no-logfile    don't generate logfile (.ul?)\n"
	"-m,    --man           convert to a manualpage\n"
	"       --map           generate C header file with jump id's for WinHelp\n"
	"       --map-pas       generate Pascal header file with jump id's for WinHelp\n"
	"       --map-vb        generate VB header file with jump id's for WinHelp\n"
	"       --map-gfa       generate GFA header file with jump id's for WinHelp\n"
	"-n,    --nroff         convert to nroff\n"
	"-o F,  --outfile F     write to file F\n"
	"-p,    --pchelp        convert to Pure C Help\n"
	"-P,    --pascal        generate Pascal sourcecode\n"
	"       --ps            convert to PostScript\n"
	"-q,    --quiet         suppress output to stdout and stderr\n"
	"-r,    --rtf           convert to RTF\n"
	"       --save-upr      create project file (.upr)\n"
	"-s,    --stg           convert to ST-Guide\n"
	"       --test          use test mode (no outfile will be saved)\n"
	"-t,    --tex           convert to LaTeX\n"
	"       --tree          generate tree file (.ut?)\n"
	"-u,    --udo           collect all files and save in UDO format\n"
  "       --verbose       verbose mode\n"
	"-v,    --vision        convert to Turbo Vision Help\n"
	"-w,    --win           convert to WinHelp\n"
	"-w4,   --win4          convert to WinHelp4\n"
	"-W,    --no-warnings   suppress warnings\n"
	"-x,    --linuxdoc      convert to Linuxdoc SGML\n"
	"-y,    --no-hypfile    don't generate hyphen file (.uh?)\n"
	"-@ F                   read options from file F\n"
	"       --help          show this helppage and exit\n"
  "       --version       show version of UDO and exit\n"
};

LOCAL const char *No_Option[]=
{	"Unbekannte Option!",
	"unknown option!"
};


/*	############################################################
	#
	# Ausgaberoutinen (call back's)
	#
	############################################################	*/
/*	----------------------------------------------------------------------
	Ausgabe von Informationen auf die Standardausgabe, aber nur falls
	ein Outfile geoeffnet wurde, der Testmodus aktiv ist und UDO nicht
	ruhig gestellt wurde
	----------------------------------------------------------------------	*/
GLOBAL void show_status_info ( const char *s )
{
	if ( (bOutOpened || bTestmode) && !bBeQuiet )
	{	fprintf(stdout, "%s\n", s);
	}
}

GLOBAL void show_status_loginfo ( const char *s )
{
	BOOLEAN flag= FALSE;
	if ( (bOutOpened || bTestmode) && !bBeQuiet )
	{	fprintf(stdout, "%s\n", s);
		flag= TRUE;
	}

	if (!flag || !bNoLogfile)
	{	logln(s);
	}
}

GLOBAL void show_status_pass ( const char *s )
{
	if ( (bOutOpened || bTestmode) && !bBeQuiet )
	{	fprintf(stdout, "%s\n", s);
	}
}

GLOBAL void show_status_udo2udo ( const char *s )
{
	if ( (bOutOpened || bTestmode) && !bBeQuiet )
	{	fprintf(stdout, "Reading %s\n", s);
	}
}

GLOBAL void show_status_node ( const char *s )
{
	if ( (bOutOpened || bTestmode) && !bBeQuiet )
	{	fprintf(stdout, "%s", s);
	}
}

GLOBAL void show_status_file_1 ( const char *s )
{
	/* Dummy-Routine */
	UNUSED(s);
}

GLOBAL void show_status_file_2 ( const char *s )
{
	if ( (bOutOpened || bTestmode) && !bBeQuiet )
	{	fprintf(stdout, "(%s) ", s);
	}
}

GLOBAL void show_status_percent ( unsigned long Pass1Lines, unsigned long Pass2Lines )
{
	int percent;
	
	percent= 0;
	if (Pass1Lines>0)
	{	percent= (int) ((100*Pass2Lines)/Pass1Lines);
	}
	
	if ( (bOutOpened || bTestmode) && !bBeQuiet && percent != last_percent)
	{	if (bVerbose)
		{	fprintf(stdout, "\n%3d%% ", percent);
		}
		else
		{	fprintf(stdout, "%3d%%\010\010\010\010", percent);
		}
		fflush(stdout);
		last_percent = percent;
	}
}

GLOBAL void show_status_errors ( const char *s )
{
	if ( (bOutOpened || bTestmode) && !bBeQuiet )
	{
		fprintf(stdout, "%s\n", s);
	}
}


GLOBAL void show_logln_message ( const char *s )
{
	/* Dummy-Routine */
	UNUSED(s);
}


/*	######################################################################
	#
	# Dummyfunktionen (call back's)
	#
	######################################################################	*/
GLOBAL void warning_err_logfile ( void )
{	error_open_logfile(sLogfull);
}

GLOBAL void warning_err_treefile ( void )
{	error_open_treefile(sTreefull);
}

GLOBAL void warning_err_uprfile ( void )
{	error_open_uprfile(sUPRfull);
}

GLOBAL void warning_err_hypfile ( void )
{	error_open_hypfile(sHypfull);
}

GLOBAL void warning_err_idxfile ( void )
{	error_open_idxfile(sIdxfull);
}

GLOBAL void warning_err_destination ( void )
{	/* Dummy-Funktion */
}

GLOBAL void multitasking_interrupt ( void )
{	/* Dummy-Funktion */
}

GLOBAL void unregistered_copyright ( void )
{	/* Dummy-Funktion */
}

GLOBAL void cursor_working ( void )
{	/* Dummy-Funktion */
}

GLOBAL void cursor_active ( void )
{	/* Dummy-Funktion */
}

GLOBAL BOOLEAN break_action ( void )
{	return FALSE;
}


/*	######################################################################
	#
	# Programm-Informationen und Fehlermeldungen
	#
	######################################################################	*/


/*	----------------------------------------------------------------------
	show_version() zeigt die Versionsnummer dieses Programms
	----------------------------------------------------------------------	*/
LOCAL void show_version ( void )
{
	fprintf(stdout, "\n%s\n", strPrgname);
	fprintf(stdout, "Release %s.%s Patchlevel %s for %s, %s %s\n",
				UDO_REL, UDO_SUBVER, UDO_PL, UDO_OS, compile_date, compile_time);
	fprintf(stdout, "%s\n", COPYRIGHT);
}

extern const char *id_abo_c;
extern const char *id_cfg_c;
extern const char *id_chr_c;
extern const char *id_env_c;
extern const char *id_fsplit_c;
extern const char *id_img_c;
extern const char *id_msg_c;
extern const char *id_str_c;
extern const char *id_sty_c;
extern const char *id_tab_c;
extern const char *id_toc_c;
extern const char *id_tp_c;
extern const char *id_udo_c;

extern const char *id_img_html_h;
extern const char *id_img_win_h;
extern const char *id_img_stg_h;
extern const char *id_charset_h;

#ifndef __HPUX_ROMAN8__
extern const char *id_hp82iso_h;
#endif

#if !defined(__MACOS__) && !defined(__MACOSX__)
extern const char *id_mac2iso_h;
#endif

#if !defined(__TOS__)
extern const char *id_tos2iso_h;
#endif

/*	----------------------------------------------------------------------
	show_ident() listet die Identstrings
	----------------------------------------------------------------------	*/
LOCAL void show_ident ( void )
{
	show_version();
	fprintf(stdout, "\n");
	fprintf(stdout, "%s\n", id_abo_c+5);
	fprintf(stdout, "%s\n", id_cfg_c+5);
	fprintf(stdout, "%s\n", id_chr_c+5);
	fprintf(stdout, "%s\n", id_cli_c+5);
	fprintf(stdout, "%s\n", id_env_c+5);
	fprintf(stdout, "%s\n", id_fsplit_c+5);
	fprintf(stdout, "%s\n", id_img_c+5);
	fprintf(stdout, "%s\n", id_msg_c+5);
	fprintf(stdout, "%s\n", id_str_c+5);
	fprintf(stdout, "%s\n", id_sty_c+5);
	fprintf(stdout, "%s\n", id_toc_c+5);
	fprintf(stdout, "%s\n", id_tab_c+5);
	fprintf(stdout, "%s\n", id_tp_c+5);
	fprintf(stdout, "%s\n", id_udo_c+5);

	fprintf(stdout, "\n");

	fprintf(stdout, "%s\n", id_charset_h+5);
	fprintf(stdout, "%s\n", id_img_html_h+5);
	fprintf(stdout, "%s\n", id_img_win_h+5);
	fprintf(stdout, "%s\n", id_img_stg_h+5);

#ifndef __HPUX_ROMAN8__
	fprintf(stdout, "%s\n", id_hp82iso_h+5);
#endif

#if !defined(__MACOS__) && !defined(__MACOSX__)
	fprintf(stdout, "%s\n", id_mac2iso_h+5);
#endif

#if !defined(__TOS__)
	fprintf(stdout, "%s\n", id_tos2iso_h+5);
#endif

}	/* show_ident */


/*	----------------------------------------------------------------------
	show_usage() gibt Auskunft ueber den Gebrauch dieses Programm
	----------------------------------------------------------------------	*/
LOCAL void show_usage ( void )
{	char s[256];
	sprintf(s, Usage[eLanguage], strPrgname);
	fprintf(stdout, "%s\n", s);
}

/*	----------------------------------------------------------------------
	show_use_help() gibt einen Hinweis auf "--help" aus
	----------------------------------------------------------------------	*/
LOCAL void show_use_help ( void )
{	fprintf(stdout, "%s\n", Use_Help[eLanguage]);
}

/*	----------------------------------------------------------------------
	show_help() gibt einen Hilfstext zu diesem Programm aus
	----------------------------------------------------------------------	*/
LOCAL void show_help ( void )
{	show_version();
	show_usage();
	fprintf(stdout, "\n%s\n", Prog_Help[eLanguage]);
}


LOCAL void show_unknown ( const char *s )
{
	fprintf(stdout, "%s: %s %s\n", strPrgname, No_Option[eLanguage], s);
}


/*	######################################################################
	# Auf Tastendruck warten, falls Option gesetzt wurde
	######################################################################	*/
LOCAL void wait_on_keypress ( void )
{
	char input[256];
	
	if (bHoldKey)
	{	if (eLanguage==DEUTSCH)
		{	fprintf(stdout, "\n<RETURN> druecken...\n");
		}
		else
		{	fprintf(stdout, "\nPress <RETURN>...\n");
		}
		fgets(input, 256, stdin);
	}

}	/* wait_on_keypress */



/*	######################################################################
	# Optionen ermitteln, nun auch per "-@ F" aus einer Datei
	######################################################################	*/

#define	MAX_FILE_ARGV	256

LOCAL BOOLEAN read_cliopt_file ( const char *name )
{
	char *fargv[MAX_FILE_ARGV+1], *ptr, *mp;
	FILE *file;
	char opt[256];
	size_t sl;
	int counter= -1;
	int i;
	
	file= fopen(name, "r");
	if (!file)
	{	return FALSE;
	}

	while ( fgets(opt, 256, file) )
	{
		sl= strlen(opt);
		while ( sl>0 && opt[sl-1]<' ' )
		{	opt[sl-1]= EOS;
			sl--;
		}
		ptr= opt;
		while ( *ptr!=EOS && (*ptr==' ' || *ptr=='\t') )
		{	ptr++;
		}
		sl= strlen(ptr);
		if (sl>0)
		{	if ( counter+1<MAX_FILE_ARGV )
			{	mp= (char *) um_malloc ( sl * sizeof(char) + 1 );
				if (mp)
				{	counter++;
					fargv[counter]= mp;
					strcpy(fargv[counter], ptr);
				}
			}
		}
	}
	
	fclose(file);

	i= 0;
	while(i<=counter)
	{	getcliopt(&i, fargv[i], (i+1<=counter) ? fargv[i+1] : NULL, TRUE);
		i++;
	}
	
	for (i=counter; i>=0; i--)
	{	if (fargv[i]!=NULL)
		{	um_free(fargv[i]);
			fargv[i]= NULL;
		}
	}
	
	return TRUE;

}	/* read_cliopt_file */



LOCAL BOOLEAN getcliopt ( int *counter, const char *arg, const char *argnext, const BOOLEAN from_file )
{
	register int i;
	BOOLEAN found= FALSE;
	
	i= 0;

	while ( cliopt[i].longname[0]!=EOS )
	{
		if	(	strcmp(arg, cliopt[i].longname)==0 ||
				(	cliopt[i].shortname[0]!=EOS &&
					strcmp(arg, cliopt[i].shortname)==0
				)
			)
		{
			found= TRUE;

			if ( cliopt[i].var!=NULL )			
			{	switch ( cliopt[i].type )
				{
					case 'b':	/* BOOLEAN */
						*(BOOLEAN *) cliopt[i].var= cliopt[i].val;
						break;
					case 'c':	/* char */
						*(char *) cliopt[i].var= 0;
						if ( cliopt[i].needs2 )
						{	if ( argnext!=NULL )
							{ 	*counter = *counter + 1;
								strcpy( (char *) cliopt[i].var, argnext);
							}
						}
						else
						{	strcpy( (char *) cliopt[i].var, "");
						}
						break;
				}
			}
		}

		i++;
	}	

	if (!found)
	{
		if ( arg[0]!='-' )
		{	strcpy(infile.full, arg);
			found= TRUE;
		}
		else
		{
			if (strcmp(arg, "-@")==0 && !from_file)
			{	if (argnext!=NULL)
				{	*counter= *counter + 1;
					found= read_cliopt_file(argnext);
				}
				else
				{	/* <???> Fehlermeldung */
					found= FALSE;
				}
			}	else
			if (strcmp(arg, "-D")==0)
			{	if (argnext!=NULL)
				{	*counter= *counter + 1;
					add_udosymbol(argnext);
					found= TRUE;
				}
				else
				{	/* <???> Fehlermeldung */
					found= FALSE;
				}
			}
			else
			{	show_unknown(arg);
			}
		}
	}
	
	return found;

}	/* getcliopt */



/*	######################################################################
	# Hauptroutine
	######################################################################	*/
int main ( int argc, const char *argv[] )
{
	int		i;
	char	nam[32], *ptr;
	BOOLEAN cliok;

	/* ---Programmnamen ermitteln--- */
#ifdef __TOS__
	Pdomain(1);
	strcpy(strPrgname, PRGNAME);
#else
	((argv[0][0]!=0)) ?	strcpy(strPrgname, argv[0]) : strcpy(strPrgname, PRGNAME);
#endif

	/* globale Variablen initialisieren */
	init_vars();
	sprintf(nam, "UDO Release %s", UDO_REL);
#ifdef __WIN32__
	init_module_config("udo32.ini", nam, UDO_OS);
#else
	init_module_config("udo.ini", nam, UDO_OS);
#endif
	read_profile();
	
	outfile.file= stdout;
	infile.file= stdin;

	eLanguage= ENGLISH;				/* default ist Englisch */

	desttype= TOASC;
	bNoLogfile= FALSE;
	bNoHypfile= FALSE;
	bNoIdxfile= FALSE;
	bBeQuiet= FALSE;
	bVerbose= FALSE;
	bTestmode= FALSE;
	bUseTreefile= FALSE;
	bUseUPRfile= FALSE;
	bUseIdMapFileC= FALSE;
	bUseIdMapFilePas= FALSE;
	bUseIdMapFileVB= FALSE;
	bUseIdMapFileGFA= FALSE;
	bNoWarnings= FALSE;
	bForceLong= FALSE;
	bForceShort= FALSE;
	bCheckMisc= FALSE;
	bHoldKey = FALSE;
	bShowArgs = FALSE;
	bShowVersion = FALSE;
	bShowHelp = FALSE;
	bShowIdent = FALSE;
	last_percent = -1;
	
	outfile.full[0]= EOS;
	infile.full[0]= EOS;
	sLogfull[0]= EOS;
	
	no_stderr_output= FALSE;		/* r5pl9 */

	if ( (ptr=getenv("LANG"))!=NULL )
	{	if ( strstr(ptr, "german") )
		{	eLanguage=DEUTSCH;
		}
	}

	if ( (ptr=getenv("LC_ALL"))!=NULL )
	{	if ( strstr(ptr, "german") )
		{	eLanguage=DEUTSCH;
		}
	}
	
	if ( (ptr=getenv("LC_MESSAGES"))!=NULL )
	{	if ( strstr(ptr, "german") )
		{	eLanguage=DEUTSCH;
		}
	}


	/* Kommandozeile auswerten */
	i= 1;
	cliok= TRUE;

	while ( (cliok) && (i<argc) && (argv[i] != NULL) )
	{
		cliok= getcliopt(&i, argv[i], (i<argc) ? argv[i+1] : NULL, FALSE);
		i++;
	}	/*while*/


	/* r6pl6: Kommandos anzeigen */
	if (bShowArgs)
	{
		i= 1;
		while ( i<argc )
		{
			fprintf(stdout, "%2d: %s\n", i, argv[i]);
			i++;
		}	/*while*/
	} else if (bShowHelp)
	{
		show_help();
	} else if (bShowVersion)
	{
		show_version();
	} else if (bShowIdent)
	{
		show_ident();
	} else
	{
		if ( i==1 || infile.full[0]==EOS )
		{	/* Leere Kommandozeile uebergeben oder kein Infile*/
			show_version();
			show_usage();
			show_use_help();
		}
		else
		{
			fsplit(infile.full, infile.driv, infile.path, infile.name, infile.suff);
	
			if (outfile.full[0]!=EOS)
			{	fsplit(outfile.full, outfile.driv, outfile.path, outfile.name, outfile.suff);
				if ( strcmp(outfile.name, "!")==0 )
				{	dest_adjust();
				}
				else
				{	dest_special_adjust();
				}
			}
			else
			{	bNoLogfile= TRUE;
				bNoHypfile= TRUE;
			}
	
			if (desttype==TOUDO)
			{
				udo2udo(infile.full);
			}
			else
			{	
				udo(infile.full);	/* <???> informativeren Exitcode ermitteln */
			}
		}
	}
		
	/* Added Debug information of Memory Management */
	printf("Memory statistic: %d malloc, %d free\n", um_malloc_count, um_free_count);

	wait_on_keypress();
	
	if (!cliok || bErrorDetected || get_error_counter() > 0)
	{	return 1;
	}

	return 0;

}	/* main */
