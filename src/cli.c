/**(TAB=0)**********************************************************************
*
*  Project name : UDO
*  Module name  : cli.c
*  Symbol prefix: cli
*
*  Description  : functions for command line interpreter version of UDO
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
*  Co-Authors   : Ulf Dunkel (fd)
*  Write access : fd
*
*  Notes        : Please add yourself as co-author when you change this file.
*
*-------------------------------------------------------------------------------
*  Things to do : - check if this huge 'string' can be handled in a way which 
*                   does not make Linux gcc complain (in -pedantic mode only):
*
*                  "string length '2968' is greater than the length '509' ISO C90
*                   compilers are required to support"
*
*-------------------------------------------------------------------------------
*  History:
*
*  2010:
*    fd  Feb 17: new file header
*                - hp82iso() and stuff removed
*                - mac2iso() and stuff removed
*                - tos2iso() and stuff removed
*    fd  Feb 19: id_charset_h removed
*    fd  Feb 22: void, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 23: UDO_PL -> UDO_BUILD (no more patchlevels)
*    fd  Mar 05: file tidied up
*    fd  Mar 06: read_cliopt_file() decomposes arguments from read file (finally)
*    fd  Mar 12: using my_str...()
# 2013:
*   tho Jun 18: reverted above change with parsing command file,
*               because no attempt was made to correctly parse quoted arguments
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
#include <string.h>
#include <stdlib.h>
#include "udoport.h"
#include "version.h"
#include "constant.h"
#include "udo_type.h"
#include "udointl.h"
#include "file.h"
#include "cfg.h"
#include "msg.h"
#include "udo.h"
#include "udosym.h"
#include "udomem.h"
#include "img.h"
#ifdef HAVE_SETLOCALE
#include <locale.h>
#endif

#ifdef __TOS__
#ifdef USE_PCTOS
#include <tos.h>
#else
#include <mintbind.h>
#endif
#endif

#include "export.h"
#include "gui.h"
#include "str.h"						/* my_str...() */





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef struct _cliopt					/* command line options */
{
	const char *longname;				/* lange Option */
	const char *shortname;				/* kurze Option */
	char type;							/* Typ: b=Boolean, c=char[] */
	_BOOL needs2;						/* folgt der Option ein Parameter? */
	void *var;							/* Variable, die geaendert wird */
	int val;							/* Wert, der bei Benutzung zugewiesen wird */
} CLIOPT;





/*******************************************************************************
*
*     UNINITIALIZED VARIABLES
*
******************************************|************************************/

static char const strPrgname[] = "udo";	/* der Name dieses Programms */

LOCAL _BOOL bHoldKey;
LOCAL _BOOL bShowArgs;
LOCAL _BOOL bShowHelp;
LOCAL _BOOL bShowVersion;
LOCAL _BOOL bDumpImages;
LOCAL int last_percent;





/*******************************************************************************
*
*     INITIALIZED VARIABLES
*
******************************************|************************************/

LOCAL const CLIOPT cliopt[] = {
	/* longname            shortname  type need2  var                val  */
	/* ------------------------------------------------------------------ */
	{ "--asc",             "-a",      'b', FALSE, &desttype,         TOASC },
	{ "--amg",             "",        'b', FALSE, &desttype,         TOAMG },
	{ "--argv",            "",        'b', FALSE, &bShowArgs,        TRUE },
	{ "--check",           "",        'b', FALSE, &bCheckMisc,       TRUE },
	{ "--c",               "-c",      'b', FALSE, &desttype,         TOSRC },
	{ "--drc",             "",        'b', FALSE, &desttype,         TODRC },
	{ "--dump-images",     "",        'b', FALSE, &bDumpImages,      TRUE },
	{ "--force-long",      "",        'b', FALSE, &bForceLong,       TRUE },
	{ "--force-short",     "",        'b', FALSE, &bForceShort,      TRUE },
#if USE_KWSET
	{ "--no-fastautoref",  "",        'b', FALSE, &bNoFastAutoref,   TRUE },
#endif
	{ "--hold",            "-H",      'b', FALSE, &bHoldKey,         TRUE },
	{ "--help",            "",        'b', FALSE, &bShowHelp,        TRUE },
	{ "--helptag",         "-g",      'b', FALSE, &desttype,         TOHPH },
	{ "--html",            "-h",      'b', FALSE, &desttype,         TOHTM },
	{ "--hah",             "",        'b', FALSE, &desttype,         TOHAH },
	{ "--htmlhelp",        "-hh",     'b', FALSE, &desttype,         TOMHH },
	{ "--info",            "-i",      'b', FALSE, &desttype,         TOINF },
	{ "--ipf",             "",        'b', FALSE, &desttype,         TOIPF },
	{ "--linuxdoc",        "-x",      'b', FALSE, &desttype,         TOLDS },
	{ "--lyx",             "",        'b', FALSE, &desttype,         TOLYX },
	{ "--man",             "-m",      'b', FALSE, &desttype,         TOMAN },
	{ "--map",             "",        'b', FALSE, &bUseIdMapFileC,   TRUE },
	{ "--map-pas",         "",        'b', FALSE, &bUseIdMapFilePas, TRUE },
	{ "--map-vb",          "",        'b', FALSE, &bUseIdMapFileVB,  TRUE },
	{ "--map-gfa",         "",        'b', FALSE, &bUseIdMapFileGFA, TRUE },
	{ "--no-hypfile",      "-y",      'b', FALSE, &bNoHypfile,       TRUE },
	{ "--no-idxfile",      "-d",      'b', FALSE, &bNoIdxfile,       TRUE },
	{ "--no-logfile",      "-l",      'b', FALSE, &bNoLogfile,       TRUE },
	{ "--no-warnings",     "-W",      'b', FALSE, &bNoWarnings,      TRUE },
	{ "--no-warningslines","-Wl",     'b', FALSE, &bNoWarningsLines, TRUE },
	{ "--nroff",           "-n",      'b', FALSE, &desttype,         TONRO },
	{ "--outfile",         "-o",      'c', TRUE,  outfile.full,      0 },
	{ "--pascal",          "-P",      'b', FALSE, &desttype,         TOSRP },
	{ "--pass1-only",      "",        'b', FALSE, &no_pass2,         TRUE },
	{ "--pdflatex",        "-f",      'b', FALSE, &desttype,         TOPDL },
	{ "--ps",              "",        'b', FALSE, &desttype,         TOKPS },
	{ "--pchelp",          "-p",      'b', FALSE, &desttype,         TOPCH },
	{ "--quiet",           "-q",      'b', FALSE, &bBeQuiet,         TRUE },
	{ "--quickview",       "--aqv",   'b', FALSE, &desttype,         TOAQV },
	{ "--rtf",             "-r",      'b', FALSE, &desttype,         TORTF },
	{ "--stg",             "-s",      'b', FALSE, &desttype,         TOSTG },
	{ "--save-upr",        "",        'b', FALSE, &bUseUPRfile,      TRUE },
	{ "--test",            "",        'b', FALSE, &bTestmode,        TRUE },
	{ "--tex",             "-t",      'b', FALSE, &desttype,         TOTEX },
	{ "--txt",             "-a",      'b', FALSE, &desttype,         TOASC },
	{ "--tree",            "",        'b', FALSE, &bUseTreefile,     TRUE },
	{ "--udo",             "-u",      'b', FALSE, &desttype,         TOUDO },
	{ "--verbose",         "",        'b', FALSE, &bVerbose,         TRUE },
	{ "--version",         "",        'b', FALSE, &bShowVersion,     TRUE },
	{ "--vision",          "-v",      'b', FALSE, &desttype,         TOTVH },
	{ "--win",             "-w",      'b', FALSE, &desttype,         TOWIN },
	{ "--win4",            "-4",      'b', FALSE, &desttype,         TOWH4 },

	/* list terminator */
	{ "", "", 'c', FALSE, NULL, 0 }
};



/*******************************************************************************
*
*     LOCAL / GLOBAL FUNCTIONS
*
******************************************|************************************/

/*******************************************************************************
*
*  show_status_info():
*     Ausgabe von Informationen auf die Standardausgabe
*
*  Notes:
*     (aber nur falls ein Outfile geoeffnet wurde, der Testmodus aktiv ist und 
*     UDO nicht ruhig gestellt wurde)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_info(const char *s)
{
	if ((bOutOpened || bTestmode) && !bBeQuiet)
		fprintf(stdout, "%s\n", s);
}





/*******************************************************************************
*
*  show_status_loginfo():
*     Ausgabe von Informationen auf die Standardausgabe
*
*  Notes:
*     (aber nur falls ein Outfile geoeffnet wurde, der Testmodus aktiv ist und 
*     UDO nicht ruhig gestellt wurde)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_loginfo(const char *s)
{
	_BOOL flag = FALSE;

	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		fprintf(stdout, "%s\n", s);
		flag = TRUE;
	}

	if (!flag || !bNoLogfile)
		logln(s);
}





/*******************************************************************************
*
*  show_status_pass():
*     show status about pass just started
*
*  Notes:
*     (aber nur falls ein Outfile geoeffnet wurde, der Testmodus aktiv ist und 
*     UDO nicht ruhig gestellt wurde)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_pass(const char *s)
{
	if ((bOutOpened || bTestmode) && !bBeQuiet)
		fprintf(stdout, "%s\n", s);
}





/*******************************************************************************
*
*  show_status_udo2udo():
*     Ausgabe von Informationen auf die Standardausgabe
*
*  Notes:
*     (aber nur falls ein Outfile geoeffnet wurde, der Testmodus aktiv ist und 
*     UDO nicht ruhig gestellt wurde)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_udo2udo(FILE_LINENO Pass2Lines, const char *s)
{
	UNUSED(Pass2Lines);
	if ((bOutOpened || bTestmode) && !bBeQuiet)
		fprintf(stdout, _("Reading %s\n"), s);
}





/*******************************************************************************
*
*  show_status_node():
*     show status about current node
*
*  Notes:
*     (aber nur falls ein Outfile geoeffnet wurde, der Testmodus aktiv ist und 
*     UDO nicht ruhig gestellt wurde)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_node(const char *numbers, const char *name)
{
	UNUSED(name);
	if ((bOutOpened || bTestmode) && !bBeQuiet)
		fprintf(stdout, "%s", numbers);
}





/*******************************************************************************
*
*  show_status_file_1():
*     show status about file just being opened during pass1()
*
*  Notes:
*     does nothing in cli interface
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_file_1(FILE_LINENO Pass1Lines, const char *s)
{
	UNUSED(Pass1Lines);
	UNUSED(s);
}





/*******************************************************************************
*
*  show_status_file_2():
*     show status about file just being opened during pass2()
*
*  Notes:
*     (aber nur falls ein Outfile geoeffnet wurde, der Testmodus aktiv ist und 
*     UDO nicht ruhig gestellt wurde)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_file_2(FILE_LINENO Pass2Lines, const char *s)
{
	UNUSED(Pass2Lines);
	if ((bOutOpened || bTestmode) && !bBeQuiet)
		fprintf(stdout, "(%s) ", s);
}





/*******************************************************************************
*
*  show_status_percent():
*     show status about progress during pass2()
*
*  Notes:
*     (aber nur falls ein Outfile geoeffnet wurde, der Testmodus aktiv ist und 
*     UDO nicht ruhig gestellt wurde)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_percent(FILE_LINENO Pass1Lines, FILE_LINENO Pass2Lines)
{
	int percent;

	percent = 0;

	if (Pass1Lines > 0)
		percent = (int) ((100 * Pass2Lines) / Pass1Lines);

	if ((bOutOpened || bTestmode) && !bBeQuiet && percent != last_percent)
	{
		if (bVerbose)
			fprintf(stdout, "\n%3d%% ", percent);
		else
			fprintf(stdout, "%3d%%\010\010\010\010", percent);

		fflush(stdout);
		last_percent = percent;
	}
}





/*******************************************************************************
*
*  show_status_errors():
*     Ausgabe von Informationen auf die Standardausgabe
*
*  Notes:
*     (aber nur falls ein Outfile geoeffnet wurde, der Testmodus aktiv ist und 
*     UDO nicht ruhig gestellt wurde)
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_errors(const char *s)
{
	if ((bOutOpened || bTestmode) && !bBeQuiet)
		fprintf(stdout, "%s\n", s);
}





/*******************************************************************************
*
*  show_logln_message():
*     Ausgabe von Informationen auf die Standardausgabe
*
*  Notes:
*     Dummy function!
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_logln_message(const char *s)
{
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		/*
		 * suppress cases were output has already been written to stderr
		 */
		if ((!bNoLogfile || !no_stderr_output) && fLogfile != stderr)
		{
			fprintf(stdout, "%s\n", s);
			fflush(stdout);
		}
	}
}





/*******************************************************************************
*
*  warning_err_logfile():
*     wrapper function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_err_logfile(void)
{
	error_open_logfile(file_lookup(sLogfull));
}





/*******************************************************************************
*
*  warning_err_treefile():
*     wrapper function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_err_treefile(void)
{
	error_open_treefile(file_lookup(sTreefull));
}





/*******************************************************************************
*
*  warning_err_uprfile():
*     wrapper function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_err_uprfile(void)
{
	error_open_uprfile(file_lookup(sUPRfull));
}





/*******************************************************************************
*
*  warning_err_hypfile():
*     wrapper function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_err_hypfile(void)
{
	error_open_hypfile(file_lookup(sHypfull));
}





/*******************************************************************************
*
*  warning_err_idxfile():
*     wrapper function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_err_idxfile(void)
{
	error_open_idxfile(file_lookup(sIdxfull));
}





/*******************************************************************************
*
*  warning_err_destination():
*     dummy function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void warning_err_destination(void)
{
}





/*******************************************************************************
*
*  multitasking_interrupt():
*     dummy function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void multitasking_interrupt(void)
{
}





/*******************************************************************************
*
*  break_action():
*     dummy function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL _BOOL break_action(void)
{
	return FALSE;
}





/*******************************************************************************
*
*  show_version():
*     zeigt die Versionsnummer dieses Programms
*
*  Return:
*     -
*
******************************************|************************************/

/* ------------------------------------------------------------------------- */

static void compiler_version(char *buf)
{
#define bitvers (sizeof(int) < 4 ? "16-bit" : sizeof(void *) >= 16 ? "128-bit" : sizeof(void *) >= 8 ? "64-bit" : "32-bit")
#define stringify1(x) #x
#define stringify(x) stringify1(x)

#if defined(_MSC_VER)
#  if _MSC_VER >= 2000
	sprintf(buf, "MS Visual Studio, Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1900
	sprintf(buf, "Visual Studio 2015, Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1800
	sprintf(buf, "Visual Studio 2013, Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1700
	sprintf(buf, "Visual Studio 2012, Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1600
	sprintf(buf, "Visual Studio 2010 Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1500
	sprintf(buf, "Visual Studio 2008 Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1400
	sprintf(buf, "Visual Studio 2005 Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1310
	sprintf(buf, "Visual Studio 2003 Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1300
	sprintf(buf, "Visual Studio 2002 Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1200
	sprintf(buf, "Visual Studio 6.0 Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  elif _MSC_VER >= 1100
	sprintf(buf, "Visual Studio 5.0 Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  else
	sprintf(buf, "Ancient VC++ Compiler-Version %d.%d (%s)", _MSC_VER / 100, _MSC_VER % 100, bitvers);
#  endif
#elif defined(__INTEL_COMPILER)
	sprintf(buf, "ICC version %d.%d.%d (%s)", __INTEL_COMPILER / 100, (__INTEL_COMPILER / 10) %10), __INTEL_COMPILER % 10, bitvers);
#elif defined(__clang_version__)
	sprintf(buf, "clang version %s (%s)", __clang_version__, bitvers);
#elif defined(__clang__)
	sprintf(buf, "clang version %s.%s.%s (%s)", stringify(__clang_major__), stringify(__clang_minor__), stringify(__clang_patchlevel__), bitvers);
#elif defined(__GNUC__)
	sprintf(buf, "GNU-C version %s.%s.%s (%s)", stringify(__GNUC__), stringify(__GNUC_MINOR__), stringify(__GNUC_PATCHLEVEL__), bitvers);
#elif defined(__AHCC__)
	sprintf(buf, "AHCC version %d.%02x (%s)", __AHCC__ >> 8, __AHCC__ & 0xff, bitvers);
#elif defined(__PUREC__)
	sprintf(buf, "Pure-C version %d.%02x (%s)", __PUREC__ >> 8, __PUREC__ & 0xff, bitvers);
#elif defined(SOZOBON)
	sprintf(buf, "SOZOBON-C V2.00x10 (%s)", bitvers);
#else
	sprintf(buf, "Unknown Compiler (%s)", bitvers);
#endif

#undef bitvers
#undef stringify1
#undef stringify
}


LOCAL NOINLINE void show_version(void)
{
	char buf[512];
	
	fprintf(stdout, "UDO %s, %s %s\n", UDO_VERSION_STRING_OS, compile_date, compile_time);
	fprintf(stdout, "%s\n", COPYRIGHT);
	compiler_version(buf);
	fprintf(stdout, _("Using %s\n"), buf);
	fprintf(stdout, _("UDO is Open Source (see %s for further information).\n"), UDO_URL);
}




/*******************************************************************************
*
*  show_usage():
*     gibt Auskunft ueber den Gebrauch dieses Programm
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL NOINLINE void show_usage(void)
{
	fprintf(stdout, _("usage: %s [-acdDghHilmnpPqrstvwWxy@] [-o outfile] file\n"), strPrgname);
}




/*******************************************************************************
*
*  show_help():
*     show UDO help page, listing all commands
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL const char *const help_strings[] = {
	N_("formats:"),
	N_("-a,    --asc           convert to ASCII"),
	N_("       --amg           convert to AmigaGuide"),
	N_("--aqv, --quickview     convert to Apple QuickView"),
	N_("-c,    --c             generate C sourcecode"),
	N_("       --drc           convert to David's Readme Compiler format"),
	N_("-f     --pdflatex      generate PDFLaTeX sourcecode"),
	N_("-g,    --helptag       convert to HP Helptag SGML"),
	N_("-h,    --html          convert to HTML"),
	N_("       --hah           convert to HTML Apple Help"),
	N_("-hh,   --htmlhelp      convert to HTML-Help"),
	N_("-i,    --info          convert to GNU Texinfo"),
	N_("       --ipf           convert to OS/2 IPF format"),
	N_("       --lyx           convert to LyX"),
	N_("-m,    --man           convert to a manualpage"),
	N_("-n,    --nroff         convert to nroff"),
	N_("-p,    --pchelp        convert to Pure C Help"),
	N_("-P,    --pascal        generate Pascal sourcecode"),
	N_("       --ps            convert to PostScript"),
	N_("-r,    --rtf           convert to RTF"),
	N_("-s,    --stg           convert to ST-Guide"),
	N_("-t,    --tex           convert to LaTeX"),
	N_("-u,    --udo           collect all files and save in UDO format"),
	N_("-v,    --vision        convert to Turbo Vision Help"),
	N_("-w,    --win           convert to WinHelp"),
	N_("-4,    --win4          convert to WinHelp4"),
	N_("-x,    --linuxdoc      convert to Linuxdoc SGML"),
	N_("output files:"),
	N_("       --force-long    save always long filenames"),
	N_("       --force-short   save always short filenames"),
	N_("-d,    --no-idxfile    don't generate index file (.ux?)"),
	N_("-y,    --no-hypfile    don't generate hyphen file (.uh?)"),
	N_("-l,    --no-logfile    don't generate logfile (.ul?)"),
	N_("       --map           generate C header file with jump id's for WinHelp"),
	N_("       --map-pas       generate Pascal header file with jump id's for WinHelp"),
	N_("       --map-vb        generate VB header file with jump id's for WinHelp"),
	N_("       --map-gfa       generate GFA header file with jump id's for WinHelp"),
	N_("-o F,  --outfile F     write to file F"),
	N_("       --save-upr      create project file (.upr)"),
	N_("       --tree          generate tree file (.ut?)"),
	N_("others:"),
	N_("       --check         activate checkings"),
	N_("-D sym,--define sym    set symbol <sym>"),
	N_("-H,    --hold          press key when udo finishes"),
	N_("-q,    --quiet         suppress output to stdout and stderr"),
	N_("       --test          use test mode (no outfile will be saved)"),
	N_("       --verbose       verbose mode"),
	N_("-W,    --no-warnings   suppress warnings"),
	N_("-Wl,   --no-warningslines   suppress warnings for line lengths"),
	N_("-@ F                   read options from file F"),
	N_("       --help          show this helppage and exit"),
	N_("       --version       show version of UDO and exit"),

};

LOCAL void show_help(void)
{
	size_t i;

	show_version();
	show_usage();
	fprintf(stdout, "\n");
	for (i = 0; i < ArraySize(help_strings); i++)
		fprintf(stdout, "%s\n", _(help_strings[i]));
}





/*******************************************************************************
*
*  wait_on_keypress():
*     Auf Tastendruck warten, falls Option gesetzt wurde
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL NOINLINE void wait_on_keypress(void)
{
	char input[256];

	if (bHoldKey)
	{
		fprintf(stdout, _("\nPress <RETURN>...\n"));
		fgets(input, (int) sizeof(input), stdin);
	}
}





/*******************************************************************************
*
*  getcliopt():
*     evaluate command line commands
*
*  Return:
*     0: no error
*    >0: error
*
******************************************|************************************/

LOCAL NOINLINE _BOOL read_cliopt_file(const char *name);

LOCAL NOINLINE _BOOL getcliopt(int *counter, const char *arg, const char *argnext, const _BOOL from_file)
{
	register int i;
	_BOOL found = FALSE;
	i = 0;

	while ((cliopt[i].longname[0] != EOS) && (found == FALSE))
	{
		if (strcmp(arg, cliopt[i].longname) == 0 ||
			(cliopt[i].shortname[0] != EOS && strcmp(arg, cliopt[i].shortname) == 0))
		{
			found = TRUE;

			if (cliopt[i].var != NULL)
			{
				switch (cliopt[i].type)
				{
				case 'b':				/* _BOOL */
					*(_BOOL *) cliopt[i].var = cliopt[i].val;
					break;

				case 'c':				/* char */
					*(char *) cliopt[i].var = 0;

					if (cliopt[i].needs2)
					{
						if (argnext != NULL)
						{
							*counter = *counter + 1;
							strcpy((char *) cliopt[i].var, argnext);
						}
					} else
					{
						strcpy((char *) cliopt[i].var, "");
					}
					break;
				}
			}
		}

		i++;
	}

	if (!found)
	{
		if (arg[0] != '-')				/* no option */
		{
			strcpy(infile.full, arg);
			found = TRUE;
		} else
		{
			/* --- read options from file --- */
			if ((strcmp(arg, "-@") == 0) && !from_file)
			{
				if (argnext != NULL)
				{
					*counter = *counter + 1;
					found = read_cliopt_file(argnext);
				} else					/* <???> Fehlermeldung */
				{
					found = FALSE;
				}
			} else if (strcmp(arg, "-D") == 0 || strcmp(arg, "--define") == 0)
			{
				/* --- set symbol --- */
				if (argnext != NULL)
				{
					*counter = *counter + 1;
					add_udosymbol(argnext);
					found = TRUE;
				} else					/* <???> Fehlermeldung */
				{
					found = FALSE;
				}
			} else
			{
				fprintf(stdout, _("%s: unknown option! %s\n"), strPrgname, arg);
			}
		}
	}

	return found;
}



/*******************************************************************************
*
*  read_cliopt_file():
*     read command file, even when given by CLI command "-@"
*
*  Return:
*     0: no error
*    >0: error
*
******************************************|************************************/

#define   MAX_FILE_ARGV   256

LOCAL NOINLINE _BOOL read_cliopt_file(const char *name)
{
	char *fargv[MAX_FILE_ARGV + 1];		/* array of argument values */
	char *ptr;							/* into read string */
	char *mp;
	FILE *file;
	char opt[256];						/* read buffer */
	size_t sl;							/* string length */
	int counter = -1;
	int i;

	file = fopen(name, "r");

	if (!file)
		return FALSE;

	while (fgets(opt, 256, file))		/* read file in blocks of 256 */
	{
		sl = strlen(opt);

		while (sl > 0 && opt[sl - 1] < ' ')	/* TRIM right */
		{
			opt[sl - 1] = EOS;
			sl--;
		}

		ptr = opt;
		/* TRIM left */
		while (*ptr != EOS && (*ptr == ' ' || *ptr == '\t'))
			ptr++;

		sl = strlen(ptr);

		while (sl > 0)
		{
			if (counter + 1 < MAX_FILE_ARGV)
			{
				for (i = 0; i < (int) sl; i++)	/* find end of 'token' */
				{
					if (ptr[i] == ' ' || ptr[i] == '\t')
						break;
				}

				if (i > 0)				/* token found */
				{						/* get space for it */
					mp = (char *) malloc((i + 1) * sizeof(char));

					if (mp)				/* malloc succeeded */
					{
						counter++;		/* increase counter of recognized arguments */
						fargv[counter] = mp;	/* mp points into fargv[] array */
						/* copy the found argument from string into array */
						strncpy(fargv[counter], ptr, i);
						fargv[counter][i] = EOS;	/* close C string! */
						while (ptr[i] == ' ' || ptr[i] == '\t')
							i++;
						ptr += i;		/* shorten string */
					}
				}
			}

			sl -= i;					/* decrease string length counter */
		}
	}

	fclose(file);

	i = 0;

	while (i <= counter)
	{
		getcliopt(&i, fargv[i], (i + 1 <= counter) ? fargv[i + 1] : NULL, TRUE);
		i++;
	}

	for (i = counter; i >= 0; i--)
	{
		if (fargv[i] != NULL)
		{
			free(fargv[i]);
			fargv[i] = NULL;
		}
	}

	return TRUE;
}





/*******************************************************************************
*
*  main():
*     THE main routine
*
*  Return:
*     0: no error
*    >0: error
*
******************************************|************************************/

int main(int argc, const char **argv)
{
	int i;
	char nam[32];
	_BOOL cliok;

#ifdef __TOS__
	Pdomain(1);
#endif

	mem_test_start();

#ifdef HAVE_SETLOCALE
	setlocale(LC_ALL, "");
#endif

#ifdef ENABLE_NLS
	bindtextdomain(GETTEXT_PACKAGE, xs_get_locale_dir());
	textdomain(GETTEXT_PACKAGE);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
#endif

	mem_print_alloc_errors = error_malloc_failed;

	/* --- init global variables --- */

	init_udo_vars();
	sprintf(nam, "UDO Version %s", UDO_REL);

	init_module_config("", nam, UDO_OS);

	read_profile();

	outfile.file = stdout;
	infile.file = stdin;

	desttype = TOASC;
	bNoLogfile = FALSE;
	bNoHypfile = FALSE;
	bNoIdxfile = FALSE;
	bBeQuiet = FALSE;
	bVerbose = FALSE;
	bTestmode = FALSE;
	bUseTreefile = FALSE;
	bUseUPRfile = FALSE;
	bUseIdMapFileC = FALSE;
	bUseIdMapFilePas = FALSE;
	bUseIdMapFileVB = FALSE;
	bUseIdMapFileGFA = FALSE;
	bNoWarnings = FALSE;
	bNoWarningsLines = FALSE;
	bForceLong = FALSE;
	bForceShort = FALSE;
#if USE_KWSET
	bNoFastAutoref = FALSE;
#endif
	bCheckMisc = FALSE;
	bHoldKey = FALSE;
	bShowArgs = FALSE;
	bShowVersion = FALSE;
	bShowHelp = FALSE;
	bDumpImages = FALSE;

	no_stderr_output = FALSE;
	no_pass2 = FALSE;

	last_percent = -1;

	outfile.full[0] = EOS;
	infile.full[0] = EOS;
	sLogfull = 0;


	/* --- now evaluate command line parameters --- */

	i = 1;
	cliok = TRUE;

	while ((cliok) && (i < argc) && (argv[i] != NULL))
	{
		cliok = getcliopt(&i, argv[i], (i < argc) ? argv[i + 1] : NULL, FALSE);
		i++;
	}


	if (bShowArgs)
	{
		i = 1;

		while (i < argc)
		{
			fprintf(stdout, "%2d: %s\n", i, argv[i]);
			i++;
		}
	} else if (bShowHelp)
	{
		show_help();
	} else if (bShowVersion)
	{
		show_version();
	} else if (bDumpImages)
	{
		dump_all_images();
	} else
	{									/* Leere Kommandozeile uebergeben oder kein Infile */
		if (i == 1 || infile.full[0] == EOS)
		{
			show_version();
			show_usage();
			fprintf(stdout, _("          use --help for more information\n"));
		} else
		{
			fsplit(infile.full, infile.driv, infile.path, infile.name, infile.suff);

			if (outfile.full[0] != EOS)
			{
				fsplit(outfile.full, outfile.driv, outfile.path, outfile.name, outfile.suff);

				if (strcmp(outfile.name, "!") == 0)
					dest_adjust();
				else
					dest_special_adjust();
			} else
			{
				bNoLogfile = TRUE;
				bNoHypfile = TRUE;
				dest_special_adjust();
			}

			udo(infile.full);			/* <???> informativeren Exitcode ermitteln */
		}
	}

	exit_udo_vars();

#ifdef ENABLE_NLS
	xs_locale_exit();
#endif

	mem_test_end();						/* clean up allocated memory */

	wait_on_keypress();

	if (!cliok || bErrorDetected || get_error_counter() > 0)
		return 1;

	return 0;
}
