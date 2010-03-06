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
*  Things to do : -
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
*    fd  Feb 22: VOID, SBYTE, UBYTE, SWORD, UWORD, SLONG, ULONG introduced
*    fd  Feb 23: UDO_PL -> UDO_BUILD (no more patchlevels)
*    fd  Mar 05: file tidied up
*    fd  Mar 06: read_cliopt_file() decomposes arguments from read file (finally)
*
******************************************|************************************/

/*******************************************************************************
*
*     CONSTANTS
*
******************************************|************************************/

#ifndef ID_CLI_C
#define ID_CLI_C
const char *id_cli_c = "@(#) cli.c       $DATE$";
#endif





/*******************************************************************************
*
*     INCLUDE FILES
*
******************************************|************************************/

#include   "import.h"
#include   <stdio.h>   
#include   <string.h>   
#include   <stdlib.h>
#include   "portab.h"
#include   "version.h"
#include   "constant.h"
#include   "udo_type.h"
#include   "file.h"
#include   "cfg.h"
#include   "msg.h"
#include   "udo.h"
#include  "udomem.h"

#ifdef __TOS__
   #ifdef USE_PCTOS
      #include <tos.h>
   #else
      #include   <mintbind.h>
   #endif
#endif

#include   "export.h"
#include   "gui.h"





/*******************************************************************************
*
*     EXTERNAL REFERENCES
*
******************************************|************************************/

extern const char  *id_abo_c;
extern const char  *id_cfg_c;
extern const char  *id_chr_c;
extern const char  *id_env_c;
extern const char  *id_fsplit_c;
extern const char  *id_img_c;
extern const char  *id_lang_c;            /* V6.5.18 */
extern const char  *id_msg_c;
extern const char  *id_str_c;
extern const char  *id_sty_c;
extern const char  *id_tab_c;
extern const char  *id_toc_c;
extern const char  *id_toc_html_c;        /* V6.5.20 [gs] */
extern const char  *id_tp_c;
extern const char  *id_udo_c;
extern const char  *id_udomem_c;          /* V6.5.20 [gs] */
extern const char  *id_img_html_h;
extern const char  *id_img_win_h;
extern const char  *id_img_stg_h;





/*******************************************************************************
*
*     MACRO DEFINITIONS
*
******************************************|************************************/

#define PRGNAME   "udo"





/*******************************************************************************
*
*     TYPE DEFINITIONS
*
******************************************|************************************/

typedef enum                              /* supported UDO CLI languages */
{
   DEUTSCH,
   ENGLISH
}  t_lang;


typedef struct _cliopt                    /* command line options */
{
   char     *longname;                    /* lange Option */
   char     *shortname;                   /* kurze Option */
   char      type;                        /* Typ: b=Boolean, c=char[] */
   BOOLEAN   needs2;                      /* folgt der Option ein Parameter? */
   void     *var;                         /* Variable, die geaendert wird */
   int       val;                         /* Wert, der bei Benutzung zugewiesen wird */
}  CLIOPT;





/*******************************************************************************
*
*     UNINITIALIZED VARIABLES
*
******************************************|************************************/

LOCAL char      strPrgname[33];           /* der Name dieses Programms */
LOCAL t_lang    eLanguage;                /* Sprache */

LOCAL BOOLEAN   bHoldKey;
LOCAL BOOLEAN   bShowArgs;
LOCAL BOOLEAN   bShowHelp;
LOCAL BOOLEAN   bShowVersion;
LOCAL BOOLEAN   bShowIdent;
LOCAL int       last_percent;





/*******************************************************************************
*
*     LOCAL PROTOTYPES
*
******************************************|************************************/

LOCAL void show_ident(void);
LOCAL void show_version(void);
LOCAL void show_usage(void);
LOCAL void show_use_help(void);
LOCAL void show_help(void);
LOCAL void show_unknown(const char *s);
LOCAL void wait_on_keypress(void);
LOCAL int  getcliopt(int *counter, const char *arg, const char *argnext, const BOOLEAN from_file);





/*******************************************************************************
*
*     INITIALIZED VARIABLES
*
******************************************|************************************/

LOCAL const CLIOPT cliopt[] =
{  /* longname            shortname  type need2   var               val  */
   /* ------------------------------------------------------------------ */
   { "--asc",              "-a",    'b',  FALSE, &desttype,         TOASC },
   { "--amg",              "",      'b',  FALSE, &desttype,         TOAMG },
   { "--argv",             "",      'b',  FALSE, &bShowArgs,        TRUE  },
   { "--check",            "",      'b',  FALSE, &bCheckMisc,       TRUE  },
   { "--c",                "-c",    'b',  FALSE, &desttype,         TOSRC },
   { "--drc",              "",      'b',  FALSE, &desttype,         TODRC },
   { "--force-long",       "",      'b',  FALSE, &bForceLong,       TRUE  },
   { "--force-short",      "",      'b',  FALSE, &bForceShort,      TRUE  },
   { "--hold",             "-H",    'b',  FALSE, &bHoldKey,         TRUE  },
   { "--help",             "",      'b',  FALSE, &bShowHelp,        TRUE  },
   { "--helptag",          "-g",    'b',  FALSE, &desttype,         TOHPH },
   { "--html",             "-h",    'b',  FALSE, &desttype,         TOHTM },
   { "--hah",              "",      'b',  FALSE, &desttype,         TOHAH },   /* V6.5.17 */
   { "--htmlhelp",         "-hh",   'b',  FALSE, &desttype,         TOMHH },
   { "--ident",            "",      'b',  FALSE, &bShowIdent,       TRUE  },
   { "--info",             "-i",    'b',  FALSE, &desttype,         TOINF },
   { "--ipf",              "",      'b',  FALSE, &desttype,         TOIPF },
   { "--linuxdoc",         "-x",    'b',  FALSE, &desttype,         TOLDS },
   { "--lyx",              "",      'b',  FALSE, &desttype,         TOLYX },
   { "--man",              "-m",    'b',  FALSE, &desttype,         TOMAN },
   { "--map",              "",      'b',  FALSE, &bUseIdMapFileC,   TRUE  },
   { "--map-pas",          "",      'b',  FALSE, &bUseIdMapFilePas, TRUE  },
   { "--map-vb",           "",      'b',  FALSE, &bUseIdMapFileVB,  TRUE  },
   { "--map-gfa",          "",      'b',  FALSE, &bUseIdMapFileGFA, TRUE  },
   { "--no-hypfile",       "-y",    'b',  FALSE, &bNoHypfile,       TRUE  },
   { "--no-idxfile",       "-d",    'b',  FALSE, &bNoIdxfile,       TRUE  },
   { "--no-logfile",       "-l",    'b',  FALSE, &bNoLogfile,       TRUE  },
   { "--no-warnings",      "-W",    'b',  FALSE, &bNoWarnings,      TRUE  },
   { "--no-warningslines", "-Wl",   'b',  FALSE, &bNoWarningsLines, TRUE  },
   { "--nroff",            "-n",    'b',  FALSE, &desttype,         TONRO },
   { "--outfile",          "-o",    'c',  TRUE,   outfile.full,     0     },
   { "--pascal",           "-P",    'b',  FALSE, &desttype,         TOSRP },
   { "--pdflatex",         "-f",    'b',  FALSE, &desttype,         TOPDL },
   { "--ps",               "",      'b',  FALSE, &desttype,         TOKPS },
   { "--pchelp",           "-p",    'b',  FALSE, &desttype,         TOPCH },
   { "--quiet",            "-q",    'b',  FALSE, &bBeQuiet,         TRUE  },
   { "--quickview",        "--aqv", 'b',  FALSE, &desttype,         TOAQV },
   { "--rtf",              "-r",    'b',  FALSE, &desttype,         TORTF },
   { "--stg",              "-s",    'b',  FALSE, &desttype,         TOSTG },
   { "--save-upr",         "",      'b',  FALSE, &bUseUPRfile,      TRUE  },
   { "--test",             "",      'b',  FALSE, &bTestmode,        TRUE  },
   { "--tex",              "-t",    'b',  FALSE, &desttype,         TOTEX },
   { "--txt",              "-a",    'b',  FALSE, &desttype,         TOASC },
   { "--tree",             "",      'b',  FALSE, &bUseTreefile,     TRUE  },
   { "--udo",              "-u",    'b',  FALSE, &desttype,         TOUDO },
   { "--verbose",          "",      'b',  FALSE, &bVerbose,         TRUE  },
   { "--version",          "",      'b',  FALSE, &bShowVersion,     TRUE  },
   { "--vision",           "-v",    'b',  FALSE, &desttype,         TOTVH },
   { "--win",              "-w",    'b',  FALSE, &desttype,         TOWIN },
   { "--win4",             "-4",    'b',  FALSE, &desttype,         TOWH4 },

                                          /* list terminator */
   { "",                   "",      'c',  FALSE,  NULL,            0      }
};



LOCAL const char *Usage[] =               /* program output: usage */
{
   "Gebrauch: %s [-acdDghHilmnpPqrstvwWxy@] [-o outfile] file",
   "usage: %s [-acdDghHilmnpPqrstvwWxy@] [-o outfile] file"
};



LOCAL const char *Use_Help[] =            /* program output: use --help */
{
   "          Mehr Hilfe mit --help",
   "          use --help for more information"
};

LOCAL const char *Prog_Help[] =           /* program output: list of controls */
{
   "-a,    --asc             ins ASCII-Format konvertieren\n"
   "       --amg             ins AmigaGuide-Format konvertieren\n"
   "--aqv, --quickview       ins Apple-QuickView-Format konvertieren\n"
   "-c,    --c               C-Sourcecode erzeugen\n"
   "       --check           Ueberpruefungen aktivieren\n"
   "       --drc             ins David's-Readme-Compiler-Format konvertieren\n"
   "-d,    --noidxfile       kein Indexfile (.ux?) anlegen\n"
   "-D sym                   Symbol <sym> setzen\n"
   "       --force-long      immer lange Dateinamen erzeugen\n"
   "       --force-short     immer kurze Dateinamen erzeugen\n"
   "-f     --pdflatex        ins PDFLaTeX-Format konvertieren\n"
   "-g,    --helptag         ins HP-Helptag-SGML-Format konvertieren\n"
   "-h,    --html            ins HTML-Format konvertieren\n"
   "       --hah             ins HTML-Apple-Help-Format konvertieren\n"    /* V6.5.17 */
   "-hh,   --htmlhelp        ins HTML-Help-Format konvertieren\n"
   "-H,    --hold            am Ende auf Tastendruck warten\n"
   "-i,    --info            ins GNU-Texinfo-Format konvertieren\n"
   "       --ipf             ins OS/2-IPF-Format konvertieren\n"
   "       --lyx             ins LyX-Format konvertieren\n"
   "-l,    --nologfile       kein Logfile (.ul?) anlegen\n"
   "-m,    --man             in eine Manualpage konvertieren\n"
   "       --map             C-Headerfile mit WinHelp-Jump-IDs erzeugen\n"
   "       --map-pas         Pascal-Headerfile mit WinHelp-Jump-IDs erzeugen\n"
   "       --map-vb          VB-Headerfile mit WinHelp-Jump-IDs erzeugen\n"
   "       --map-gfa         GFA-Headerfile mit WinHelp-Jump-IDs erzeugen\n"
   "-n,    --nroff           ins nroff-Format konvertieren\n"
   "-o F,  --outfile F       Ausgaben in die Datei F schreiben\n"
   "-p,    --pchelp          ins Pure-C-Help-Quelltextformat konvertieren\n"
   "-P,    --pascal          Pascal-Sourcecode erzeugen\n"
   "       --ps              ins PostScript-Format konvertieren\n"
   "-q,    --quiet           Ausgaben auf stdout und stderr unterdruecken\n"
   "-r,    --rtf             ins Rich Text Format konvertieren\n"
   "       --save-upr        Projekt-Datei (.upr) ausgeben\n"
   "-s,    --stg             ins ST-Guide-Quelltextformat konvertieren\n"
   "       --test            Testmodus (kein Outfile erzeugen)\n"
   "-t,    --tex             ins LaTeX-Format konvertieren\n"
   "       --tree            Include-Baum (.ut?) ausgeben\n"
   "       --verbose         ausfuehrliche Konvertierungs-Infos anzeigen\n"
   "-u,    --udo             Dateien sammeln und in einer UDO-Datei sichern\n"
   "-v,    --vision          ins Turbo-Vision-Help-Format konvertieren\n"
   "-w,    --win             ins WinHelp-Quelltextformat konvertieren\n"
   "-w4,   --win4            ins WinHelp4-Quelltextformat konvertieren\n"
   "-W,    --no-warnings     Warnungen unterdruecken\n"
   "-Wl,   --no-warningslines   Warnungen fuer Zeilenlaenge unterdruecken\n"
   "-x,    --linuxdoc        ins Linuxdoc-SGML-Format konvertieren\n"
   "-y,    --no-hypfile      kein Hyphenfile (.uh?) anlegen\n"
   "-@ F                     Optionen aus der Datei F lesen\n"
   "       --help            diese Informationen anzeigen und beenden\n"
   "       --version         Versionsinformationen anzeigen und beenden",




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
   "       --hah           convert to HTML Apple Help\n"                  /* V6.5.17 */
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
   "-Wl,   --no-warningslines   suppress warnings for line lengths\n"
   "-x,    --linuxdoc      convert to Linuxdoc SGML\n"
   "-y,    --no-hypfile    don't generate hyphen file (.uh?)\n"
   "-@ F                   read options from file F\n"
   "       --help          show this helppage and exit\n"
   "       --version       show version of UDO and exit\n"
};



LOCAL const char *No_Option[] =           /* program output: unknown option */
{
   "Unbekannte Option!",
   "unknown option!"
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

GLOBAL void show_status_info(

const char  *s)  /* */
{
   if ( (bOutOpened || bTestmode) && !bBeQuiet )
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

GLOBAL void show_status_loginfo(

const char  *s)             /* */
{
   BOOLEAN   flag = FALSE;  /* */
   
   
   if ( (bOutOpened || bTestmode) && !bBeQuiet )
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

GLOBAL void show_status_pass(

const char  *s)  /* */
{
   if ( (bOutOpened || bTestmode) && !bBeQuiet )
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

GLOBAL void show_status_udo2udo(

const char  *s)
{
   if ( (bOutOpened || bTestmode) && !bBeQuiet )
      fprintf(stdout, "Reading %s\n", s);
}





/*******************************************************************************
*
*  show_status_node():
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

GLOBAL void show_status_node(

const char  *s)  /* */
{
   if ( (bOutOpened || bTestmode) && !bBeQuiet )
      fprintf(stdout, "%s", s);
}





/*******************************************************************************
*
*  show_status_file_1():
*     Ausgabe von Informationen auf die Standardausgabe
*
*  Notes:
*     Dummy function!
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void show_status_file_1(

const char  *s)  /* */
{
   UNUSED(s);
}





/*******************************************************************************
*
*  show_status_file_2():
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

GLOBAL void show_status_file_2(

const char  *s)  /* */
{
   if ( (bOutOpened || bTestmode) && !bBeQuiet )
      fprintf(stdout, "(%s) ", s);
}





/*******************************************************************************
*
*  show_status_percent():
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

GLOBAL void show_status_percent(

ULONG    Pass1Lines,  /* */
ULONG    Pass2Lines)  /* */
{
   int   percent;     /* */


   percent = 0;
   
   if (Pass1Lines > 0)
      percent = (int)( (100 * Pass2Lines) / Pass1Lines);

   if ( (bOutOpened || bTestmode) && !bBeQuiet && percent != last_percent)
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

GLOBAL void show_status_errors(

const char  *s)  /* */
{
   if ( (bOutOpened || bTestmode) && !bBeQuiet )
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

GLOBAL void show_logln_message(

const char  *s)  /* */
{
   UNUSED(s);
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
   error_open_logfile(sLogfull);
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
   error_open_treefile(sTreefull);
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
   error_open_uprfile(sUPRfull);
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
   error_open_hypfile(sHypfull);
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
   error_open_idxfile(sIdxfull);
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
*  unregistered_copyright():
*     dummy function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void unregistered_copyright(void)
{
}





/*******************************************************************************
*
*  cursor_working():
*     dummy function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void cursor_working(void)
{
}





/*******************************************************************************
*
*  cursor_active():
*     dummy function
*
*  Return:
*     -
*
******************************************|************************************/

GLOBAL void cursor_active(void)
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

GLOBAL BOOLEAN break_action(void)
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

LOCAL void show_version(void)
{
                                          /* v6.4.1[vj]: commented out (wished by Ulrich Kretschmer) */
/* fprintf(stdout, "\n%s\n", strPrgname); */

   fprintf(stdout, "UDO Version %s.%s %s for %s, %s %s\n",
      UDO_REL, UDO_SUBVER, UDO_BUILD, UDO_OS, compile_date, compile_time);
            
   fprintf(stdout, "%s\n", COPYRIGHT);
   sprintf(sInfMsg, "UDO is Open Source (see %s for further information).\n", UDO_URL);
   fprintf(stdout, sInfMsg);
}






/*******************************************************************************
*
*  show_ident():
*     listet die Identstrings
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void show_ident(void)
{
   show_version();
   
   fprintf(stdout, "\n");
   
   fprintf(stdout, "%s\n", id_abo_c      + 5);
   fprintf(stdout, "%s\n", id_cfg_c      + 5);
   fprintf(stdout, "%s\n", id_chr_c      + 5);
   fprintf(stdout, "%s\n", id_cli_c      + 5);
   fprintf(stdout, "%s\n", id_env_c      + 5);
   fprintf(stdout, "%s\n", id_fsplit_c   + 5);
   fprintf(stdout, "%s\n", id_img_c      + 5);
   fprintf(stdout, "%s\n", id_lang_c     + 5);
   fprintf(stdout, "%s\n", id_msg_c      + 5);
   fprintf(stdout, "%s\n", id_str_c      + 5);
   fprintf(stdout, "%s\n", id_sty_c      + 5);
   fprintf(stdout, "%s\n", id_toc_c      + 5);
   fprintf(stdout, "%s\n", id_toc_html_c + 5);
   fprintf(stdout, "%s\n", id_tab_c      + 5);
   fprintf(stdout, "%s\n", id_tp_c       + 5);
   fprintf(stdout, "%s\n", id_udo_c      + 5);
   fprintf(stdout, "%s\n", id_udomem_c   + 5);

   fprintf(stdout, "\n");

   fprintf(stdout, "%s\n", id_img_html_h + 5);
   fprintf(stdout, "%s\n", id_img_win_h  + 5);
   fprintf(stdout, "%s\n", id_img_stg_h  + 5);
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

LOCAL void show_usage(void)
{
   char   s[256];  /* */
   
   sprintf(s, Usage[eLanguage], strPrgname);
   fprintf(stdout, "%s\n", s);
}





/*******************************************************************************
*
*  show_use_help():
*     show a hint on "--help"
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void show_use_help(void)
{
   fprintf(stdout, "%s\n", Use_Help[eLanguage]);
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

LOCAL void show_help(void)
{
   show_version();
   show_usage();
   fprintf(stdout, "\n%s\n", Prog_Help[eLanguage]);
}





/*******************************************************************************
*
*  show_unknown():
*     ??? (description missing)
*
*  Return:
*     -
*
******************************************|************************************/

LOCAL void show_unknown(

const char  *s)  /* */
{
   fprintf(stdout, "%s: %s %s\n", strPrgname, No_Option[eLanguage], s);
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

LOCAL void wait_on_keypress(void)
{
   char   input[256];  /* */


   if (bHoldKey)
   {
      if (eLanguage == DEUTSCH)
         fprintf(stdout, "\n<RETURN> druecken...\n");
      else
         fprintf(stdout, "\nPress <RETURN>...\n");
         
      fgets(input, 256, stdin);
   }
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

LOCAL BOOLEAN read_cliopt_file(

const char  *name)                      /* ^ filename */
{
   char     *fargv[MAX_FILE_ARGV + 1],  /* array of argument values */
            *ptr,                       /* ^ into read string */
            *mp;                        /* */
   FILE     *file;                      /* ^ file */
   char      opt[256];                  /* read buffer */
   SLONG     sl;                        /* string length */
   int       counter = -1;              /* */
   int       i;                         /* counter for chars in ptr */
   

   file = fopen(name, "r");
   
   if (!file)
      return FALSE;

   while (fgets(opt, 256, file))          /* read file in blocks of 256 */
   {
      sl = strlen(opt);
      
      while (sl > 0 && opt[sl - 1] < ' ') /* TRIM right */
      {
         opt[sl - 1] = EOS;
         sl--;
      }
      
      ptr = opt;
                                          /* TRIM left */
      while (*ptr != EOS && (*ptr == ' ' || *ptr == '\t') )
         ptr++;
         
      sl = strlen(ptr);
      
      while (sl > 0)
      {
         if (counter + 1 < MAX_FILE_ARGV)
         {
            for (i = 0; i < sl; i++)      /* find end of 'token' */
            {
               if (ptr[i] == ' ' || ptr[i] == '\t')
                  break;
            }

            if (i > 0)                    /* token found */
            {                             /* get space for it */
               mp = (char *)um_malloc((i + 1) * sizeof(char));
            
               if (mp)                    /* malloc succeeded */
               {
                  counter++;              /* increase counter of recognized arguments */
                  fargv[counter] = mp;    /* mp points into fargv[] array */
                                          /* copy the found argument from string into array */
                  strncpy(fargv[counter], ptr, i);
                  fargv[counter][i] = EOS;/* close C string! */
                  ptr += i + 1;           /* shorten string */
               }
            }
         }
         
         sl -= i + 1;                     /* decrease string length counter */
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
         um_free(fargv[i]);
         fargv[i] = NULL;
      }
   }

   return TRUE;
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

LOCAL BOOLEAN getcliopt(

int              *counter,        /* */
const char       *arg,            /* */
const char       *argnext,        /* */
const BOOLEAN     from_file)      /* */
{
   register int   i;              /* */
   BOOLEAN        found = FALSE;  /* */

   i = 0;

   while ( (cliopt[i].longname[0] != EOS) && (found == FALSE) )
   {
      if (    strcmp(arg, cliopt[i].longname) == 0 
           || (cliopt[i].shortname[0] != EOS && strcmp(arg, cliopt[i].shortname) == 0)
         )
      {
         found = TRUE;

         if (cliopt[i].var != NULL)
         {
            switch (cliopt[i].type)
            {
            case 'b':                     /* BOOLEAN */
               *(BOOLEAN *)cliopt[i].var = cliopt[i].val;
               break;
               
            case 'c':                     /* char */
               *(char *)cliopt[i].var = 0;
               
               if (cliopt[i].needs2)
               {
                  if (argnext != NULL)
                  {
                     *counter = *counter + 1;
                     strcpy((char *)cliopt[i].var, argnext);
                  }
               }
               else
               {
                  strcpy((char *)cliopt[i].var, "");
               }
               
            }  /* switch () */
         }
      }

      i++;
   }   


   if (!found)
   {
      if (    (arg[0] != '-')             /* no option */ 
           && (arg[0] != '%')             /* no shell placeholder */
           && (stricmp(arg, "udo") != 0)  /* no shell program name */
         )
      {
         strcpy(infile.full, arg);
         found = TRUE;
      }
      else
      {
                                          /* --- read options from file --- */
         if (strcmp(arg, "-@") == 0 && !from_file)
         {
            if (argnext != NULL)
            {
               *counter = *counter + 1;
               found = read_cliopt_file(argnext);
            }
            else                          /* <???> Fehlermeldung */
            {
               found = FALSE;
            }
         }
         else if (strcmp(arg, "-D") == 0) /* --- set symbol --- */
         {
            if (argnext != NULL)
            {
               *counter = *counter + 1;
               add_udosymbol(argnext);
               found = TRUE;
            }
            else                          /* <???> Fehlermeldung */
            {
               found = FALSE;
            }
         }
         else
         {
            show_unknown(arg);
         }
      }
   }

   return found;
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

int main(

int          argc,     /* # of arguments from command line */
const char  *argv[])   /* arguments */
{
   int       i;        /* */
   char      nam[32],  /* */
            *ptr;      /* */
   BOOLEAN   cliok;    /* */


   init_um();                             /* init UDO memory management first, */
                                          /* or um_malloc() cannot be used! */


   /* --- get program name --- */

#ifdef __TOS__
   Pdomain(1);
   strcpy(strPrgname, PRGNAME);
#else
   ((argv[0][0] != 0)) ? strcpy(strPrgname, argv[0]) : strcpy(strPrgname, PRGNAME);
#endif


   /* --- init global variables --- */
   
   init_vars();
   sprintf(nam, "UDO Version %s", UDO_REL);
   
#ifdef __WIN32__
   init_module_config("udo32.ini", nam, UDO_OS);
#else
   init_module_config("udo.ini", nam, UDO_OS);
#endif

   read_profile();

   outfile.file = stdout;
   infile.file  = stdin;

   eLanguage = ENGLISH;                   /* default is English */

   desttype         = TOASC;
   bNoLogfile       = FALSE;
   bNoHypfile       = FALSE;
   bNoIdxfile       = FALSE;
   bBeQuiet         = FALSE;
   bVerbose         = FALSE;
   bTestmode        = FALSE;
   bUseTreefile     = FALSE;
   bUseUPRfile      = FALSE;
   bUseIdMapFileC   = FALSE;
   bUseIdMapFilePas = FALSE;
   bUseIdMapFileVB  = FALSE;
   bUseIdMapFileGFA = FALSE;
   bNoWarnings      = FALSE;
   bNoWarningsLines = FALSE;
   bForceLong       = FALSE;
   bForceShort      = FALSE;
   bCheckMisc       = FALSE;
   bHoldKey         = FALSE;
   bShowArgs        = FALSE;
   bShowVersion     = FALSE;
   bShowHelp        = FALSE;
   bShowIdent       = FALSE;
   
   no_stderr_output = FALSE;

   last_percent = -1;

   outfile.full[0] = EOS;
   infile.full[0]  = EOS;
   sLogfull[0]     = EOS;


   if ( (ptr = getenv("LANG")) != NULL)
   {
      if (strstr(ptr, "german"))
         eLanguage = DEUTSCH;
   }

   if ( (ptr = getenv("LC_ALL")) != NULL)
   {
      if (strstr(ptr, "german"))
         eLanguage = DEUTSCH;
   }

   if ( (ptr = getenv("LC_MESSAGES")) != NULL)
   {
      if (strstr(ptr, "german"))
         eLanguage = DEUTSCH;
   }


   /* --- now evaluate command line parameters --- */
   
   i = 1;
   cliok = TRUE;

   while ( (cliok) && (i < argc) && (argv[i] != NULL) )
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
   }
   else if (bShowHelp)
   {
      show_help();
   }
   else if (bShowVersion)
   {
      show_version();
   }
   else if (bShowIdent)
   {
      show_ident();
   }
   else
   {                                      /* Leere Kommandozeile uebergeben oder kein Infile */
      if (i == 1 || infile.full[0] == EOS)
      {
         show_version();
         show_usage();
         show_use_help();
      }
      else
      {
         fsplit(infile.full, infile.driv, infile.path, infile.name, infile.suff);

         if (outfile.full[0] != EOS)
         {
            fsplit(outfile.full, outfile.driv, outfile.path, outfile.name, outfile.suff);
            
            if (strcmp(outfile.name, "!") == 0)
            {
               dest_adjust();
            }
            else
            {
               dest_special_adjust();
            }
         }
         else
         {
            bNoLogfile = TRUE;
            bNoHypfile = TRUE;
         }

         if (desttype == TOUDO)
         {
            udo2udo(infile.full);
         }
         else
         {
            udo(infile.full);             /* <???> informativeren Exitcode ermitteln */
         }
      }
   }

   exit_um();                             /* clean up allocated memory */

   wait_on_keypress();

   if (!cliok || bErrorDetected || get_error_counter() > 0)
      return 1;

   return 0;
}


/* +++ EOF +++ */
