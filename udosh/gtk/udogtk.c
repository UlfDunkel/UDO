#include "udogtk.h"
#include "gtkconfig.h"
#include "help.h"
#include "misc.h"

#include "icons/udosh.h"
#include "icons/mail.h"
#include "icons/weblink.h"

#define EMAIL_ADR "admin@tho-otto.de"

#if UDO_INTEGRATED

#include <import.h>
#include <constant.h>
#include <file.h>
#include <udo.h>
#include <udosym.h>
#include <msg.h>
#include <gui.h>
#include "guish.h"
#include <export.h>

#else

/* must match definitions from UDOs constant.h */
#define TOASC                 0           /* ASCII */
#define TOMAN                 1           /* ASCII (formatiert) */
#define TOSTG                 2           /* ST-Guide-Quelltext */
#define TOTEX                 3           /* LaTeX */
#define TORTF                 4           /* RTF */
#define TOPCH                 5           /* PC-HELP */
#define TOHTM                 6           /* HTML (World Wide Web) */
#define TOWIN                 7           /* Windows-Hilfe */
#define TOINF                 8           /* GNU-Texinfo */
#define TOTVH                 9           /* Turbo-Vision-Help */
#define TOLDS                10           /* Linuxdoc-SGML */
#define TOAQV                11           /* Apple-QuickView */
#define TOHPH                12           /* HP Helptag SGML */
#define TOLYX                13           /* LyX */
#define TONRO                14           /* nroff, was auch immer */
#define TOSRC                15           /* C-Sourcecode */
#define TOSRP                16           /* Pascal-Sourcecode */
#define TOIPF                17           /* OS/2-IPF-Format */
#define TODRC                18           /* Dave's Readme Compiler */
#define TOMHH                19           /* HTMLHelp */
#define TOPDL                20           /* PDFLaTeX */
#define TOWH4                21           /* WinHelp4 */
#define TOUDO                22           /* UDO-Format */
#define TOKPS                23           /* Krueger's PostScript */
#define TOAMG                24           /* AmigaGuide */
#define TOHAH                25           /* HTML Apple Help */

#endif /* UDO_INTEGRATED */


char const gl_program_name[] = "udosh";
static gboolean have_console;
static int gtk_inited;

static char *geom_arg;
static gboolean bShowArgs;
static gboolean bShowVersion;
static gboolean bShowHelp;
static gboolean bHoldKey;
static char *outfile_name;
#if !UDO_INTEGRATED
static int desttype;
static gboolean bForceLong;
static gboolean bForceShort;
static gboolean bCheckMisc;
static gboolean bForceLong;
static gboolean bForceShort;
#endif




typedef struct _formatdata
{
	FormatInfo Dest;
	FormatInfo Param1;
	FormatInfo Param2;
	FormatInfo Final;
} FormatData;


typedef struct _formatconst {
	int type;
	const char *name;
	const char *log_suffix;
	const char *def_ext_long;
	const char *def_ext_short;
	const char *addpath;
	const char *dest_suff;
	const char *dest_app;
	const char *param1_suff;
	const char *param1_app;
	const char *param2_suff;
	const char *param2_app;
	const char *final_suff;
	const char *final_app;
	const char *udo_switch;
	const char *udo_short_switch;
	unsigned int use_udo_editor;
} FormatConst;
#define USE_UDO_EDITOR_EXEC_DEST   0x0001
#define USE_UDO_EDITOR_EDIT_DEST   0x0002
#define USE_UDO_EDITOR_EXEC_PARAM1 0x0004
#define USE_UDO_EDITOR_EDIT_PARAM1 0x0008
#define USE_UDO_EDITOR_EXEC_PARAM2 0x0010
#define USE_UDO_EDITOR_EDIT_PARAM2 0x0020
#define USE_UDO_EDITOR_EXEC_FINAL  0x0040
#define USE_UDO_EDITOR_EDIT_FINAL  0x0080

/*
 * order in the list of formats does not matter,
 * except for the first entry which is the default
 * format if none is specified and thus should be
 * ASCII to be consistent with the cli interface
 */
static FormatConst const formatconst[] =
{
	{
		TOASC,
		"ASCII",
		".ula",
		".txt",
		NULL,
		"ascii",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--asc",
		"-a",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2 | USE_UDO_EDITOR_EDIT_FINAL
	},
	{
		TOWIN,
		"WinHelp",
		".ulw",
		".rtf",
		NULL,
		"winhelp",
		"%",
		NULL,
		".hpj",
		"hcp.exe",
		".err",
		"hcw.exe",
		".hlp",
		"winhlp32.exe",
		"--win",
		"-w",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOWH4,
		"WinHelp4",
		".ul4",
		".rtf",
		NULL,
		"winhelp4",
		NULL,
		NULL,
		".hpj",
		"hcrtf.exe",
		".err",
		"hcw.exe",
		".hlp",
		"winhlp32.exe",
		"--win4",
		"-4",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOHTM,
		"HTML",
		".ulh",
		".html",
		".htm",
		"html",
		"%",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--html",
		"-h",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2 | USE_UDO_EDITOR_EDIT_FINAL
	},
	{
		TOMHH,
		"HTML Help",
		".ulh",
		".html",
		".htm",
		"htmlhelp",
		"%",
		NULL,
		".hhp",
		"hhc.exe",
		".log",
		"hhw.exe",
		".chm",
		"hh.exe",
		"--htmlhelp",
		"-hh",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TORTF,
		"RTF",
		".ulr",
		".rtf",
		NULL,
		"rtf",
		"%",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--rtf",
		"-r",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOTEX,
		"LaTeX",
		".ult",
		".tex",
		NULL,
		"latex",
		NULL,
		NULL,
		".tex",
		"latex",
		".log",
		NULL,
		".dvi",
		NULL,
		"--tex",
		"-t",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOPDL,
		"PDFLaTeX",
		".ulf",
		".tex",
		NULL,
		"pdflatex",
		NULL,
		NULL,
		".tex",
		"pdflatex",
		".log",
		NULL,
		".pdf",
		NULL,
		"--pdflatex",
		"-f",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOINF,
		"Texinfo",
		".uli",
		".texi",
		".tex",
		"texinfo",
		"%",
		"makeinfo",
		NULL,
		NULL,
		NULL,
		NULL,
		".info",
		"info",
		"--info",
		"-i",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOMAN,
		"Manpage",
		".ulm",
		".man",
		NULL,
		"manpage",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--man",
		"-m",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2 | USE_UDO_EDITOR_EDIT_FINAL
	},
	{
		TOSTG,
		"ST-Guide",
		".uls",
		".stg",
		NULL,
		"stguide",
		"%",
		"hcp.ttp",
		NULL,
		NULL,
		NULL,
		NULL,
		".hyp",
		"hypview",
		"--stg",
		"-s",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOPCH,
		"Pure C Help",
		".ulp",
		".scr",
		NULL,
		"pchelp",
		".cmd",
		"pcc.ttp",
		NULL,
		NULL,
		NULL,
		NULL,
		".hlp",
		"pc_help.prg",
		"--pchelp",
		"-p",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOTVH,
		"Turbo Vision Help",
		".ulv",
		".txt",
		NULL,
		"tvhelp",
		"%",
		"tvhc",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--vision",
		"-v",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOLDS,
		"Linuxdoc SGML",
		".ulx",
		".sgml",
		".sgm",
		"linuxdoc",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--linuxdoc",
		"-x",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOAQV,
		"Apple Quickview",
		".ulq",
		".rtf",
		NULL,
		"quickvw",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		".hyp",
		"hyperion.exe",
		"--aqv",
		NULL,
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TODRC,
		"DRC",
		".uld",
		".drc",
		NULL,
		"drc",
		"%",
		"rcom.exe",
		NULL,
		NULL,
		NULL,
		NULL,
		".exe",
		"start",
		"--drc",
		NULL,
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2
	},
	{
		TOIPF,
		"OS/2 IPF",
		".uli",
		".ipf",
		NULL,
		"ipf",
		"%",
		"ipfc",
		NULL,
		NULL,
		NULL,
		NULL,
		".inf",
		"iview",
		"--ipf",
		NULL,
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2,
	},
	{
		TOLYX,
		"LyX",
		".ull",
		".lyx",
		NULL,
		"lyx",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"%",
		"lyx",
		"--lyx",
		NULL,
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2,
	},
	{
		TONRO,
		"NROFF",
		".ul1",
		".1",
		NULL,
		"nroff",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--nroff",
		"-n",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2 | USE_UDO_EDITOR_EDIT_FINAL,
	},
	{
		TOSRC,
		"C",
		".ulc",
		".c",
		NULL,
		"c",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--c",
		"-c",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2 | USE_UDO_EDITOR_EDIT_FINAL,
	},
	{
		TOSRP,
		"Pascal",
		".ulp",
		".pas",
		NULL,
		"pascal",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--pascal",
		"-P",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2 | USE_UDO_EDITOR_EDIT_FINAL,
	},
	{
		TOUDO,
		"UDO",
		".ulu",
		".udo",
		NULL,
		"udo",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--udo",
		"-u",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2 | USE_UDO_EDITOR_EDIT_FINAL,
	},
	{
		TOKPS,
		"Postscript",
		".ulp",
		".ps",
		NULL,
		"ps",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"%",
		"gsview.exe",
		"--ps",
		NULL,
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2,
	},
	{
		TOAMG,
		"AmigaGuide",
		".ulg",
		".guide",
		".gui",
		"amguide",
		"%",
		"winguide.exe",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--amg",
		NULL,
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2,
	},
	{
		TOHPH,
		"HP HelpTag SGML",
		".ulg",
		".sgml",
		".sgm",
		"helptag",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--helptag",
		"-g",
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2,
	},
	{
		TOHAH,
		"AppleHelp",
		".ulh",
		".html",
		".htm",
		"applehelp",
		"%",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--hah",
		NULL,
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2 | USE_UDO_EDITOR_EDIT_FINAL,
	}
};
#define MAXDESTTYPE ((int)ArraySize(formatconst))


typedef struct _shell_dialog
{
	char *m_geometry;
	
	gboolean m_use_test;
	gboolean m_use_verb;
	gboolean m_hold_key;
	gboolean m_warnings;
	gboolean m_warnings_lines;
	gboolean m_use_check;
	gboolean m_use_dir;
	gboolean m_use_quiet;
	
	gboolean m_use_log;
	gboolean m_use_hyphen;
	gboolean m_use_tree;
	gboolean m_use_map_c;
	gboolean m_use_map_pas;
	gboolean m_use_map_vb;
	gboolean m_use_map_gfa;
	gboolean m_use_upr;
	gboolean m_use_idx;
	
	gboolean m_force_long;
	gboolean m_force_short;
	gboolean m_fast_autoref;
	
#define MAX_SYM 12
	char *m_symbol[MAX_SYM];
	gboolean m_use_sym[MAX_SYM];

	char *m_file_source;
	char *m_file_dest;
	char *m_file_param1;
	char *m_file_param2;
	char *m_file_final;

	char **mru_list;
	int n_mru;
	int max_mru;
	
	/*
	 * currently selected format.
	 * this is an index into formatdata array,
	 * and does NOT correspond to UDOs TOxxx constants.
	 */
	int m_format;

	/* complete path to generated logfile */
	char *m_file_log;
	/* complete path to final result file */
	char *m_file_hyphen;
	/* complete file to generated tree file */
	char *m_file_tree;
	/* complete path to generated C header file */
	char *m_file_map_c;
	/* complete path to generated Pascal header file */
	char *m_file_map_pas;
	/* complete path to generated VB header file */
	char *m_file_map_vb;
	/* complete path to generated GFA header file */
	char *m_file_map_gfa;
	/* complete path to generated UPR project file */
	char *m_file_upr;

	/* Path to UDO executable, when called externally */
	char *m_app_udo;
	/* path to default text editor for logfiles etc. */
	char *m_edi_udo;
	
	/* path to our help file */
	char *udosh_helpfile;
	/* path to UDO help file */
	char *udo_helpfile;
	/* topic of command index */
	char *udo_help_commands;
	int m_use_udo;
	
	gboolean m_always_on_top;
	gboolean m_create_dirs;
	
	FormatData m_formatdata[MAXDESTTYPE];

	char *m_inifilename;
	GKeyFile *m_inifile;
	
	GtkWidget *hwnd;
	
	GtkWidget *format_combo;
	GtkWidget *file_source_combo;
	GtkWidget *select_source_button;
	GtkWidget *file_dest_entry;
	GtkWidget *select_dest_button;
	GtkWidget *file_param1_entry;
	GtkWidget *file_param2_entry;
	GtkWidget *file_final_entry;
	
	GtkWidget *exec_source_button;
	GtkWidget *edit_source_button;
	GtkWidget *exec_dest_button;
	GtkWidget *edit_dest_button;
	GtkWidget *exec_param1_button;
	GtkWidget *edit_param1_button;
	GtkWidget *exec_param2_button;
	GtkWidget *edit_param2_button;
	GtkWidget *exec_final_button;
	GtkWidget *edit_final_button;
	
	GtkWidget *use_test_button;
	GtkWidget *use_verb_button;
	GtkWidget *hold_key_button;
	GtkWidget *warnings_button;
	GtkWidget *warnings_lines_button;
	GtkWidget *use_check_button;
	GtkWidget *use_dir_button;
	GtkWidget *force_long_button;
	GtkWidget *force_short_button;
	GtkWidget *fast_autoref_button;
	GtkWidget *use_log_button;
	GtkWidget *use_hyphen_button;
	GtkWidget *use_tree_button;
	GtkWidget *use_map_c_button;
	GtkWidget *use_map_pas_button;
	GtkWidget *use_map_vb_button;
	GtkWidget *use_map_gfa_button;
	GtkWidget *use_upr_button;
	GtkWidget *use_sym_button[MAX_SYM];
	GtkWidget *symbol_entry[MAX_SYM];
	
	GtkWidget *edit_log_button;
	GtkWidget *edit_hyphen_button;
	GtkWidget *edit_tree_button;
	GtkWidget *edit_map_c_button;
	GtkWidget *edit_map_pas_button;
	GtkWidget *edit_map_vb_button;
	GtkWidget *edit_map_gfa_button;
	GtkWidget *edit_upr_button;

	GtkTooltips *tooltips;
} SHELL_DIALOG;


static gboolean set_desttype(const char *option_name, const char *value, gpointer data, GError *error)
{
	int i;
	
	UNUSED(value);
	UNUSED(data);
	UNUSED(error);
	while (*option_name == '-')
		option_name++;
	for (i = 0; i < MAXDESTTYPE; i++)
	{
		if (formatconst[i].udo_switch != NULL &&
			strcmp(option_name, formatconst[i].udo_switch + 2) == 0)
		{
			desttype = formatconst[i].type;
			return TRUE;
		}
		if (formatconst[i].udo_short_switch != NULL &&
			strcmp(option_name, formatconst[i].udo_short_switch + 1) == 0)
		{
			desttype = formatconst[i].type;
			return TRUE;
		}
	}
	/* handle 2nd long options */
	if (strcmp(option_name, "quickview") == 0)
	{
		desttype = TOAQV;
		return TRUE;
	}
	if (strcmp(option_name, "hh") == 0)
	{
		desttype = TOMHH;
		return TRUE;
	}
	if (strcmp(option_name, "w4") == 0)
	{
		desttype = TOWH4;
		return TRUE;
	}
	return FALSE;
}


static gboolean set_symbol(const char *option_name, const char *value, gpointer data, GError *error)
{
	int i;
	SHELL_DIALOG *sd = (SHELL_DIALOG *)data;
	
	UNUSED(option_name);
	UNUSED(error);
	for (i = 0; i < MAX_SYM; i++)
	{
		if (sd->m_symbol[i] == NULL)
		{
			sd->m_symbol[i] = g_strdup(value);
			sd->m_use_sym[i] = TRUE;
			return TRUE;
		}
	}
	return FALSE;
}

static GOptionEntry const format_options[] = {
	{ "asc", 'a', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to ASCII"), NULL },
	{ "amg", 0, G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to AmigaGuide"), NULL },
	{ "aqv", 0, G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to Apple QuickView"), NULL },
	{ "quickview", 0, G_OPTION_FLAG_NO_ARG | G_OPTION_FLAG_HIDDEN, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to Apple QuickView"), NULL },
	{ "c", 'c', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("generate C sourcecode"), NULL },
	{ "drc", 0, G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to David's Readme Compiler format"), NULL },
	{ "pdflatex", 'f', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("generate PDFLaTeX sourcecode"), NULL },
	{ "helptag", 'g', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to HP Helptag SGML"), NULL },
	{ "html", 'h', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to HTML"), NULL },
	{ "hah", 0, G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to HTML Apple Help"), NULL },
	{ "htmlhelp", 0, G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to HTML-Help"), NULL },
	{ "hh", 0, G_OPTION_FLAG_NO_ARG | G_OPTION_FLAG_HIDDEN, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to HTML-Help"), NULL },
	{ "info", 'i', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to GNU Texinfo"), NULL },
	{ "ipf", 0, G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to OS/2 IPF format"), NULL },
	{ "lyx", 0, G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to LyX"), NULL },
	{ "man", 'm', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to a manualpage"), NULL },
	{ "nroff", 'n', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to nroff"), NULL },
	{ "pchelp", 'p', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to Pure C Help"), NULL },
	{ "pascal", 'P', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("generate Pascal sourcecode"), NULL },
	{ "ps", 0, G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to PostScript"), NULL },
	{ "rtf", 'r', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to RTF"), NULL },
	{ "stg", 's', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to ST-Guide"), NULL },
	{ "tex", 't', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to LaTeX"), NULL },
	{ "udo", 'u', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("collect all files and save in UDO format"), NULL },
	{ "vision", 'v', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to Turbo Vision Help"), NULL },
	{ "win", 'w', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to WinHelp"), NULL },
	{ "win4", '4', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to WinHelp4"), NULL },
	{ "linuxdoc", 'x', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, set_desttype, N_("convert to Linuxdoc SGML"), NULL },
	
	{ NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL, NULL }
};

static GOptionEntry const output_options[] = {
	{ "force-long", 0, 0, G_OPTION_ARG_NONE, &bForceLong, N_("save always long filenames"), NULL },
	{ "force-short", 0, 0, G_OPTION_ARG_NONE, &bForceLong, N_("save always short filenames"), NULL },
	{ "no-idxfile", 'd', 0, G_OPTION_ARG_NONE, &bNoIdxfile, N_("don't generate index file (.ux?)"), NULL },
	{ "no-hypfile", 'y', 0, G_OPTION_ARG_NONE, &bNoHypfile, N_("don't generate hyphen file (.uh?)"), NULL },
	{ "no-logfile", 'l', 0, G_OPTION_ARG_NONE, &bNoLogfile, N_("don't generate logfile (.ul?)"), NULL },
	{ "map", 0, 0, G_OPTION_ARG_NONE, &bUseIdMapFileC, N_("generate C header file with jump id's for WinHelp"), NULL },
	{ "map-pas", 0, 0, G_OPTION_ARG_NONE, &bUseIdMapFilePas, N_("generate Pascal header file with jump id's for WinHelp"), NULL },
	{ "map-vb", 0, 0, G_OPTION_ARG_NONE, &bUseIdMapFileVB, N_("generate Visual-Basic header file with jump id's for WinHelp"), NULL },
	{ "map-gfa", 0, 0, G_OPTION_ARG_NONE, &bUseIdMapFileGFA, N_("generate GFA header file with jump id's for WinHelp"), NULL },
	{ "output", 'o', 0, G_OPTION_ARG_FILENAME, &outfile_name, N_("write to file FILE"), "FILE" },
	{ "save-upr", 0, 0, G_OPTION_ARG_NONE, &bUseUPRfile, N_("create project file (.upr)"), NULL },
	{ "tree", 0, 0, G_OPTION_ARG_NONE, &bUseTreefile, N_("generate tree file (.ut?)"), NULL },
	
	{ NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL, NULL }
};

static GOptionEntry const options[] = {
	{ "geometry", 0, 0, G_OPTION_ARG_STRING, &geom_arg, N_("Sets the client geometry of the main window"), N_("GEOMETRY") },
	{ "version", 0, 0, G_OPTION_ARG_NONE, &bShowVersion, N_("Show version information and exit"), NULL },
	{ "help", '?', G_OPTION_FLAG_HIDDEN, G_OPTION_ARG_NONE, &bShowHelp, N_("Show help information and exit"), NULL },
	{ "check", 0, 0, G_OPTION_ARG_NONE, &bCheckMisc, N_("activate checkings"), NULL },
	{ "define", 'D', 0, G_OPTION_ARG_CALLBACK, set_symbol, N_("activate checkings"), NULL },
	{ "hold", 'H', 0, G_OPTION_ARG_NONE, &bHoldKey, N_("press key when udo finishs"), NULL },
	{ "quiet", 'q', 0, G_OPTION_ARG_NONE, &bBeQuiet, N_("suppress output to stdout and stderr"), NULL },
	{ "test", 0, 0, G_OPTION_ARG_NONE, &bTestmode, N_("use test mode (no outfile will be saved)"), NULL },
	{ "verbose", 0, 0, G_OPTION_ARG_NONE, &bVerbose, N_("verbose mode"), NULL },
	{ "no-warnings", 0, 0, G_OPTION_ARG_NONE, &bNoWarnings, N_("suppress warnings"), NULL },
	{ "no-warningslines", 0, 0, G_OPTION_ARG_NONE, &bNoWarningsLines, N_("suppress warnings for line lengths"), NULL },
	/* -@ FILE not supported in GUI */
	
	{ NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL, NULL }
};

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void cursor_working(SHELL_DIALOG *sd, gboolean active)
{
	GdkWindow *win = gtk_widget_get_window(sd->hwnd);
	GdkCursor *cursor = active ? gdk_cursor_new(GDK_WATCH) : NULL;
	gdk_window_set_cursor(win, cursor);
}

/*** ---------------------------------------------------------------------- ***/

static void g_freep(char **str)
{
	if (*str != NULL)
	{
		g_free(*str);
		*str = NULL;
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void show_url(GtkWidget *widget, void *userdata)
{
	char *str;
	
	UNUSED(userdata);
	str = g_strdup(PACKAGE_URL);
#ifdef G_PLATFORM_WIN32
	{
		gunichar2 *wstr = g_utf8_to_utf16(str, -1, NULL, NULL, NULL);
		UNUSED(widget);
		ShellExecuteW(NULL, L"open", wstr, NULL, NULL, SW_SHOWNORMAL);
		g_free(wstr);
	}
#else
	gtk_show_uri(gtk_widget_get_screen(widget), str, GDK_CURRENT_TIME, NULL);
#endif
}

/*** ---------------------------------------------------------------------- ***/

static gboolean on_event_url(GtkWidget *widget, GdkEvent *event, void *userdata)
{
	UNUSED(event);
	show_url(widget, userdata);
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

static gboolean on_activate_url(GtkWidget *widget, gchar *uri, void *userdata)
{
	UNUSED(uri);
	show_url(widget, userdata);
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void show_email(GtkWidget *widget, void *userdata)
{
	char *str;
	
	UNUSED(userdata);
	str = g_strdup_printf("mailto:%s?subject=UDO Shell for Gtk", EMAIL_ADR);
#ifdef G_PLATFORM_WIN32
	{
		gunichar2 *wstr = g_utf8_to_utf16(str, -1, NULL, NULL, NULL);
	    UNUSED(widget);
		ShellExecuteW(NULL, L"open", wstr, NULL, NULL, SW_SHOWNORMAL);
		g_free(wstr);
	}
#else
	gtk_show_uri(gtk_widget_get_screen(widget), str, GDK_CURRENT_TIME, NULL);
#endif
}

/*** ---------------------------------------------------------------------- ***/

static gboolean on_event_email(GtkWidget *widget, GdkEvent *event, void *userdata)
{
	UNUSED(event);
	show_email(widget, userdata);
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

static gboolean on_activate_email(GtkWidget *widget, gchar *uri, void *userdata)
{
	UNUSED(uri);
	show_email(widget, userdata);
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void About(GtkWidget *parent)
{
	GtkWidget *dialog;
	GtkWidget *dialog_vbox, *dialog_hbox, *vbox1, *vbox2, *hbox1, *hbox2, *hbox3;
	GtkWidget *label;
	GdkPixbuf *icon;
	GtkWidget *image;
	GtkWidget *ok;
	GtkWidget *eventbox;
	char *str;
	
	parent = gtk_widget_get_toplevel(parent);

	dialog = gtk_dialog_new ();
	gtk_container_set_border_width (GTK_CONTAINER (dialog), 5);
	gtk_window_set_type_hint (GTK_WINDOW (dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
	gtk_dialog_set_has_separator (GTK_DIALOG (dialog), FALSE);
	icon = app_icon();
	gtk_window_set_icon(GTK_WINDOW(dialog), icon);
	gdk_pixbuf_unref(icon);
	gtk_window_set_title(GTK_WINDOW(dialog), _("About UDO Shell"));
	g_object_set_data(G_OBJECT(dialog), "udoshell_window_type", NO_CONST("about-dialog"));

	dialog_vbox = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	gtk_widget_show (dialog_vbox);

	hbox1 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox1);
	gtk_box_pack_start(GTK_BOX(dialog_vbox), hbox1, TRUE, TRUE, 0);

	vbox1 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox1);
	gtk_box_pack_start (GTK_BOX (hbox1), vbox1, TRUE, TRUE, 0);

	str = g_strdup_printf(_("UDO Shell for Gtk\nVersion %s, June 2013\n\nCopyright \xC2\xA9 1997-2013 by\n\nThorsten Otto\nKatharinenstr. 14\nD-45131 Essen\nGermany\n"), UDOSH_VERSION);
	label = gtk_label_new(str);
	g_free(str);
	gtk_label_set_selectable(GTK_LABEL(label), TRUE);
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox1), label, TRUE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 10, 0);

	hbox2 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox2);
	gtk_box_pack_start (GTK_BOX (vbox1), hbox2, TRUE, TRUE, 0);

	label = gtk_label_new (_("Email:"));
	gtk_widget_show (label);
	gtk_label_set_selectable(GTK_LABEL(label), TRUE);
	gtk_box_pack_start (GTK_BOX (hbox2), label, FALSE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 10, 0);

	label = gtk_label_new (NULL);
	str = g_strdup_printf("<a href=\"mailto:%s?subject=UDO Shell for Gtk\">%s</a>", EMAIL_ADR, EMAIL_ADR);
	gtk_label_set_markup(GTK_LABEL(label), str);
	g_freep(&str);
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (hbox2), label, TRUE, TRUE, 0);
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 10, 0);
	gtk_label_set_selectable(GTK_LABEL(label), TRUE);
	g_signal_connect((gpointer)label, "activate-link", G_CALLBACK(on_activate_email), NULL);
	
	vbox2 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox2);
	gtk_box_pack_start (GTK_BOX (hbox1), vbox2, TRUE, TRUE, 0);

	icon = gdk_pixbuf_new_from_inline(-1, udosh_data, FALSE, NULL);
	image = gtk_image_new_from_pixbuf(icon);
	gtk_widget_show (image);
	gtk_box_pack_start (GTK_BOX (vbox2), image, TRUE, TRUE, 0);
	gdk_pixbuf_unref(icon);

	icon = gdk_pixbuf_new_from_inline(-1, email_data, FALSE, NULL);
	image = gtk_image_new_from_pixbuf(icon);
	gtk_widget_show (image);
	gdk_pixbuf_unref(icon);
	gtk_misc_set_alignment (GTK_MISC (image), 0.5, 0.89);
	eventbox = gtk_event_box_new();
	gtk_widget_show(eventbox);
	gtk_container_add(GTK_CONTAINER(eventbox), image);
	gtk_box_pack_start (GTK_BOX (vbox2), eventbox, TRUE, TRUE, 0);
	g_signal_connect((gpointer)eventbox, "button-press-event", G_CALLBACK(on_event_email), NULL);
	
	hbox3 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox3);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), hbox3, TRUE, TRUE, 0);

	label = gtk_label_new (NULL);
	str = g_strdup_printf(("WWW: <a href=\"%s\">%s</a>"), PACKAGE_URL, PACKAGE_URL);
	gtk_label_set_markup(GTK_LABEL(label), str);
	g_freep(&str);
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (hbox3), label, TRUE, TRUE, 0);
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 10, 0);
	gtk_label_set_selectable(GTK_LABEL(label), TRUE);
	g_signal_connect((gpointer)label, "activate-link", G_CALLBACK(on_activate_url), NULL);
	
	icon = gdk_pixbuf_new_from_inline(-1, weblink_data, FALSE, NULL);
	image = gtk_image_new_from_pixbuf(icon);
	gdk_pixbuf_unref(icon);
	gtk_widget_show (image);
	eventbox = gtk_event_box_new();
	gtk_widget_show(eventbox);
	gtk_container_add(GTK_CONTAINER(eventbox), image);
	gtk_box_pack_start (GTK_BOX (hbox3), eventbox, TRUE, TRUE, 0);
	g_signal_connect((gpointer)eventbox, "button-press-event", G_CALLBACK(on_event_url), NULL);

	dialog_hbox = gtk_dialog_get_action_area(GTK_DIALOG(dialog));
	ok = gtk_button_new_from_stock(GTK_STOCK_OK);
	gtk_widget_show (ok);
	gtk_container_add(GTK_CONTAINER(dialog_hbox), ok);
	
	gtk_signal_connect_object(GTK_OBJECT(ok), "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy), dialog);
	
	if (parent != NULL)
		gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent));
	
	CenterWindow(dialog);
	gtk_window_present(GTK_WINDOW(dialog));
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static gboolean file_available(const char *cs)
{
	FILE *file;

	if (empty(cs))
		return FALSE;
	file = fopen(cs, "rb");
	if (file == NULL)
		return FALSE;
	fclose(file);
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void backslash2slash(char *s)
{
	size_t i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '\\')
			s[i] = '/';
	}
}

/*** ---------------------------------------------------------------------- ***/

static gboolean NOINLINE change_dir(const char *cs)
{
	char *path;
	gboolean ret;
	
	path = g_path_get_dirname(cs);
	ret = g_chdir(path) == 0;
	g_free(path);
	return ret;
}

/*** ---------------------------------------------------------------------- ***/

static gboolean NOINLINE make_dir(const char *cs)
{
	char *path;
	gboolean ret;
	
	path = g_path_get_dirname(cs);
	ret = g_mkdir(path, 0755) == 0;
	g_free(path);
	return ret;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static gboolean NOINLINE add_mru(SHELL_DIALOG *sd, const char *filename)
{
	int i, j;
	char *tmp;
	char **new_mru;
	
	if (!empty(filename))
	{
		for (i = 0; i < sd->n_mru; i++)
		{
			if (filename_cmp(filename, sd->mru_list[i]) == 0)
			{
				tmp = sd->mru_list[i];
				for (j = i-1; j >= 0; j--)
					sd->mru_list[j+1] = sd->mru_list[j];
				sd->mru_list[0] = tmp;
				return TRUE;
			}
		}
		tmp = g_strdup(filename);
		if (tmp == NULL)
			return FALSE;
		if (sd->max_mru != 0 && sd->n_mru >= sd->max_mru)
		{
			--sd->n_mru;
			g_freep(&sd->mru_list[sd->n_mru]);
		} else
		{
			if (sd->mru_list == NULL)
			{
				new_mru = g_new(char *, 1);
			} else
			{
				new_mru = g_renew(char *, sd->mru_list, sd->n_mru + 1);
			}
			if (new_mru == NULL)
			{
				g_free(tmp);
				return FALSE;
			}
			sd->mru_list = new_mru;
		}
		for (i = sd->n_mru - 1; i >= 0; i--)
			sd->mru_list[i + 1] = sd->mru_list[i];
		sd->mru_list[0] = tmp;
		++sd->n_mru;
	}
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE reset_mru(SHELL_DIALOG *sd)
{
	int i, n;
	
	n = gtk_tree_model_iter_n_children(gtk_combo_box_get_model(GTK_COMBO_BOX(sd->file_source_combo)), NULL);
	for (i = 0; i < n; i++)
		gtk_combo_box_remove_text(GTK_COMBO_BOX(sd->file_source_combo), 0);
	for (i = 0; i < sd->n_mru; i++)
		gtk_combo_box_append_text(GTK_COMBO_BOX(sd->file_source_combo), sd->mru_list[i]);
	gtk_combo_box_set_active(GTK_COMBO_BOX(sd->file_source_combo), 0);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void chomp(char **str)
{
	if (*str != NULL)
	{
		g_strchomp(*str);
		g_strchug(*str);
	}
	if (empty(*str))
	{
		g_freep(str);
	}
}

/*** ---------------------------------------------------------------------- ***/

static int format_index_from_type(int type)
{
	int i;

	for (i = 0; i < MAXDESTTYPE; i++)
	{
		if (type == formatconst[i].type)
		{
			return i;
		}
	}
	return format_index_from_type(TOASC);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE UpdateData(SHELL_DIALOG *sd, gboolean update)
{
	int i;

	if (update)
	{
		g_free(sd->m_file_source);
		sd->m_file_source = gtk_combo_box_get_active_text(GTK_COMBO_BOX(sd->file_source_combo));
		chomp(&sd->m_file_source);
		g_free(sd->m_file_dest);
		sd->m_file_dest = g_strdup(gtk_entry_get_text(GTK_ENTRY(sd->file_dest_entry)));
		chomp(&sd->m_file_dest);
		g_free(sd->m_file_param1);
		sd->m_file_param1 = g_strdup(gtk_entry_get_text(GTK_ENTRY(sd->file_param1_entry)));
		chomp(&sd->m_file_param1);
		g_free(sd->m_file_param2);
		sd->m_file_param2 = g_strdup(gtk_entry_get_text(GTK_ENTRY(sd->file_param2_entry)));
		chomp(&sd->m_file_param2);
		g_free(sd->m_file_final);
		sd->m_file_final = g_strdup(gtk_entry_get_text(GTK_ENTRY(sd->file_final_entry)));
		chomp(&sd->m_file_final);

		sd->m_use_test = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_test_button));
		sd->m_use_verb = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_verb_button));
		sd->m_hold_key = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->hold_key_button));
		sd->m_warnings = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->warnings_button));
		sd->m_warnings_lines = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->warnings_lines_button));
		sd->m_use_check = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_check_button));
		sd->m_use_dir = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_dir_button));
		sd->m_force_long = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->force_long_button));
		sd->m_force_short = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->force_short_button));
		sd->m_fast_autoref = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->fast_autoref_button));

		sd->m_use_log = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_log_button));
		sd->m_use_hyphen = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_hyphen_button));
		sd->m_use_tree = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_tree_button));
		sd->m_use_map_c = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_map_c_button));
		sd->m_use_map_pas = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_map_pas_button));
		sd->m_use_map_vb = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_map_vb_button));
		sd->m_use_map_gfa = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_map_gfa_button));
		sd->m_use_upr = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_upr_button));

		for (i = 0; i < MAX_SYM; i++)
		{
			sd->m_use_sym[i] = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(sd->use_sym_button[i]));
			g_free(sd->m_symbol[i]);
			sd->m_symbol[i] = g_strdup(gtk_entry_get_text(GTK_ENTRY(sd->symbol_entry[i])));
			chomp(&sd->m_symbol[i]);
		}
		
		sd->m_format = gtk_combo_box_get_active(GTK_COMBO_BOX(sd->format_combo));
		if (sd->m_format < 0)
			sd->m_format = 0;
		else if (sd->m_format >= MAXDESTTYPE)
			sd->m_format = MAXDESTTYPE - 1;
	} else
	{
		/* gtk_combo_box_set_active_text(GTK_COMBO_BOX(sd->file_source_combo), sd->m_file_source); */
		gtk_entry_set_text(GTK_ENTRY(sd->file_dest_entry), fixnull(sd->m_file_dest));
		gtk_entry_set_text(GTK_ENTRY(sd->file_param1_entry), fixnull(sd->m_file_param1));
		gtk_entry_set_text(GTK_ENTRY(sd->file_param2_entry), fixnull(sd->m_file_param2));
		gtk_entry_set_text(GTK_ENTRY(sd->file_final_entry), fixnull(sd->m_file_final));

		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_test_button), sd->m_use_test);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_verb_button), sd->m_use_verb);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->hold_key_button), sd->m_hold_key);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->warnings_button), sd->m_warnings);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->warnings_lines_button), sd->m_warnings_lines);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_check_button), sd->m_use_check);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_dir_button), sd->m_use_dir);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->force_long_button), sd->m_force_long);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->force_short_button), sd->m_force_short);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->fast_autoref_button), sd->m_fast_autoref);

		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_log_button), sd->m_use_log);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_hyphen_button), sd->m_use_hyphen);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_tree_button), sd->m_use_tree);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_map_c_button), sd->m_use_map_c);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_map_pas_button), sd->m_use_map_pas);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_map_vb_button), sd->m_use_map_vb);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_map_gfa_button), sd->m_use_map_gfa);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_upr_button), sd->m_use_upr);

		for (i = 0; i < MAX_SYM; i++)
		{
			gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(sd->use_sym_button[i]), sd->m_use_sym[i]);
			gtk_entry_set_text(GTK_ENTRY(sd->symbol_entry[i]), fixnull(sd->m_symbol[i]));
		}
		gtk_combo_box_set_active(GTK_COMBO_BOX(sd->format_combo), sd->m_format);
	}
}

/*** ---------------------------------------------------------------------- ***/

static char *g_base_exename(const char *path)
{
	char *name;
	char *p;
	
	if (empty(path))
		return g_strdup("");
	name = g_path_get_basename(path);
	if (strcmp(name, ".") == 0)
		*name = '\0';
	if ((p = strrchr(name, '.')) != NULL)
	{
		if (filename_cmp(p, ".exe") == 0 ||
			filename_cmp(p, ".com") == 0 ||
			filename_cmp(p, ".cmd") == 0 ||
			filename_cmp(p, ".bat") == 0 ||
			filename_cmp(p, ".desktop") == 0)
		*p = '\0';
	}
	return name;
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE set_udo_editor(SHELL_DIALOG *sd, const char *old_editor)
{
	int i;
	char *name;

	old_editor = fixnull(old_editor);
	name = g_base_exename(sd->m_edi_udo);
	for (i = 0; i < MAXDESTTYPE; i++)
	{
		if (formatconst[i].use_udo_editor & USE_UDO_EDITOR_EXEC_DEST)
		{
			if (empty(sd->m_formatdata[i].Dest.Application) ||
				strcmp(sd->m_formatdata[i].Dest.Application, old_editor) == 0)
			{
				g_free(sd->m_formatdata[i].Dest.Application);
				sd->m_formatdata[i].Dest.Application = g_strdup(sd->m_edi_udo);
				if (sd->m_format == i)
					gtk_button_set_label(GTK_BUTTON(sd->exec_dest_button), name);
			}
		}
		if (formatconst[i].use_udo_editor & USE_UDO_EDITOR_EDIT_DEST)
		{
			if (empty(sd->m_formatdata[i].Dest.Editor) ||
				strcmp(sd->m_formatdata[i].Dest.Editor, old_editor) == 0)
			{
				g_free(sd->m_formatdata[i].Dest.Editor);
				sd->m_formatdata[i].Dest.Editor = g_strdup(sd->m_edi_udo);
				if (sd->m_format == i)
					gtk_button_set_label(GTK_BUTTON(sd->edit_dest_button), name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EXEC_PARAM1) && !empty(sd->m_formatdata[i].Param1.Suffix))
		{
			if (empty(sd->m_formatdata[i].Param1.Application) ||
				strcmp(sd->m_formatdata[i].Param1.Application, old_editor) == 0)
			{
				g_free(sd->m_formatdata[i].Param1.Application);
				sd->m_formatdata[i].Param1.Application = g_strdup(sd->m_edi_udo);
				if (sd->m_format == i)
					gtk_button_set_label(GTK_BUTTON(sd->exec_param1_button), name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EDIT_PARAM1) && !empty(sd->m_formatdata[i].Param1.Suffix))
		{
			if (empty(sd->m_formatdata[i].Param1.Editor) ||
				strcmp(sd->m_formatdata[i].Param1.Editor, old_editor) == 0)
			{
				g_free(sd->m_formatdata[i].Param1.Editor);
				sd->m_formatdata[i].Param1.Editor = g_strdup(sd->m_edi_udo);
				if (sd->m_format == i)
					gtk_button_set_label(GTK_BUTTON(sd->edit_param1_button), name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EXEC_PARAM2) && !empty(sd->m_formatdata[i].Param2.Suffix))
		{
			if (empty(sd->m_formatdata[i].Param2.Application) ||
				strcmp(sd->m_formatdata[i].Param2.Application, old_editor) == 0)
			{
				g_free(sd->m_formatdata[i].Param2.Application);
				sd->m_formatdata[i].Param2.Application = g_strdup(sd->m_edi_udo);
				if (sd->m_format == i)
					gtk_button_set_label(GTK_BUTTON(sd->exec_param2_button), name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EDIT_PARAM2) && !empty(sd->m_formatdata[i].Param2.Suffix))
		{
			if (empty(sd->m_formatdata[i].Param2.Editor) ||
				strcmp(sd->m_formatdata[i].Param2.Editor, old_editor) == 0)
			{
				g_free(sd->m_formatdata[i].Param2.Editor);
				sd->m_formatdata[i].Param2.Editor = g_strdup(sd->m_edi_udo);
				if (sd->m_format == i)
					gtk_button_set_label(GTK_BUTTON(sd->edit_param2_button), name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EXEC_FINAL) && !empty(sd->m_formatdata[i].Final.Suffix))
		{
			if (empty(sd->m_formatdata[i].Final.Application) ||
				strcmp(sd->m_formatdata[i].Final.Application, old_editor) == 0)
			{
				g_free(sd->m_formatdata[i].Final.Application);
				sd->m_formatdata[i].Final.Application = g_strdup(sd->m_edi_udo);
				if (sd->m_format == i)
					gtk_button_set_label(GTK_BUTTON(sd->exec_final_button), name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EDIT_FINAL) && !empty(sd->m_formatdata[i].Final.Suffix))
		{
			if (empty(sd->m_formatdata[i].Final.Editor) ||
				strcmp(sd->m_formatdata[i].Final.Editor, old_editor) == 0)
			{
				g_free(sd->m_formatdata[i].Final.Editor);
				sd->m_formatdata[i].Final.Editor = g_strdup(sd->m_edi_udo);
				if (sd->m_format == i)
					gtk_button_set_label(GTK_BUTTON(sd->edit_final_button), name);
			}
		}
	}
	g_free(name);
}

/*** ---------------------------------------------------------------------- ***/

static gboolean NOINLINE find_application_for(const char *filename, FormatInfo *info)
{
	if (!empty(filename) && empty(info->Application))
	{
#ifdef __WIN32__
		char exe[PATH_MAX];
		HINSTANCE h;
		
		*exe = '\0';
		h = FindExecutable(filename, NULL, exe);
		if ((UINT)(DWORD_PTR)h >= HINSTANCE_ERROR)
		{
			if (*exe == '\0')
				GetModuleFileName(h, exe, sizeof(exe));
			if (filename_cmp(filename, exe) != 0)
			{
				g_free(info->Application);
				info->Application = g_strdup(exe);
				return TRUE;
			}
		}
#endif
#ifdef GDK_WINDOWING_X11
		{
			GAppInfo *app_info;
			GFile *file;
			char *path;
			GError *error = NULL;
			
			file = g_file_new_for_path(filename);

			app_info = g_file_query_default_handler(file, NULL, &error);
			g_clear_error(&error);
			
			g_object_unref(file);
			if (app_info == NULL)
			    return FALSE;
			path = g_strdup(g_app_info_get_executable(app_info));
			/* TODO: use g_app_info_get_commandline(app_info), and parse it */
			g_object_unref(app_info);
			if (path == NULL)
				return FALSE;
			if (filename_cmp(filename, path) != 0)
			{
				g_free(info->Application);
				info->Application = path;
				return TRUE;
			}
			g_free(path);
		}
#endif
 	}
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE ShowWindowsError(GtkWidget *parent, GError **error)
{
	show_dialog(parent, GTK_STOCK_DIALOG_ERROR, error && *error && (*error)->message ? (*error)->message : "", NULL, NULL);
	g_clear_error(error);
}

/*** ---------------------------------------------------------------------- ***/

static gboolean NOINLINE find_application(SHELL_DIALOG *sd)
{
	return find_application_for(sd->m_file_dest, &sd->m_formatdata[sd->m_format].Dest) |
		   find_application_for(sd->m_file_param1, &sd->m_formatdata[sd->m_format].Param1) |
		   find_application_for(sd->m_file_param2, &sd->m_formatdata[sd->m_format].Param2) |
		   find_application_for(sd->m_file_final, &sd->m_formatdata[sd->m_format].Final);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE adjust_buttons(SHELL_DIALOG *sd)
{
	char *name;

#if UDO_INTEGRATED
	if (sd->m_use_udo == USE_UDO_INT)
	{
		gtk_button_set_label(GTK_BUTTON(sd->exec_source_button), "UDO");
	} else
#endif
	{
		name = g_base_exename(sd->m_app_udo);
		gtk_button_set_label(GTK_BUTTON(sd->exec_source_button), name);
		g_free(name);
	}
	
	name = g_base_exename(sd->m_edi_udo);
	gtk_button_set_label(GTK_BUTTON(sd->edit_source_button), name);
	gtk_button_set_label(GTK_BUTTON(sd->edit_log_button), name);
	gtk_button_set_label(GTK_BUTTON(sd->edit_hyphen_button), name);
	gtk_button_set_label(GTK_BUTTON(sd->edit_tree_button), name);
	gtk_button_set_label(GTK_BUTTON(sd->edit_upr_button), name);
	gtk_button_set_label(GTK_BUTTON(sd->edit_map_c_button), name);
	gtk_button_set_label(GTK_BUTTON(sd->edit_map_pas_button), name);
	gtk_button_set_label(GTK_BUTTON(sd->edit_map_vb_button), name);
	gtk_button_set_label(GTK_BUTTON(sd->edit_map_gfa_button), name);
	g_free(name);
	
	name = g_base_exename(sd->m_formatdata[sd->m_format].Dest.Application);
	gtk_button_set_label(GTK_BUTTON(sd->exec_dest_button), name);
	g_free(name);
	
	name = g_base_exename(sd->m_formatdata[sd->m_format].Dest.Editor);
	gtk_button_set_label(GTK_BUTTON(sd->edit_dest_button), name);
	g_free(name);
	
	name = g_base_exename(sd->m_formatdata[sd->m_format].Param1.Application);
	gtk_button_set_label(GTK_BUTTON(sd->exec_param1_button), name);
	g_free(name);
	
	name = g_base_exename(sd->m_formatdata[sd->m_format].Param1.Editor);
	gtk_button_set_label(GTK_BUTTON(sd->edit_param1_button), name);
	g_free(name);
	
	name = g_base_exename(sd->m_formatdata[sd->m_format].Param2.Application);
	gtk_button_set_label(GTK_BUTTON(sd->exec_param2_button), name);
	g_free(name);
	
	name = g_base_exename(sd->m_formatdata[sd->m_format].Param2.Editor);
	gtk_button_set_label(GTK_BUTTON(sd->edit_param2_button), name);
	g_free(name);
	
	name = g_base_exename(sd->m_formatdata[sd->m_format].Final.Application);
	gtk_button_set_label(GTK_BUTTON(sd->exec_final_button), name);
	g_free(name);
	
	name = g_base_exename(sd->m_formatdata[sd->m_format].Final.Editor);
	gtk_button_set_label(GTK_BUTTON(sd->edit_final_button), name);
	g_free(name);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE check_output_files(SHELL_DIALOG *sd)
{
	gtk_widget_set_sensitive(sd->exec_dest_button, file_available(sd->m_file_dest));
	gtk_widget_set_sensitive(sd->edit_dest_button, file_available(sd->m_file_dest));
	gtk_widget_set_sensitive(sd->exec_param1_button, file_available(sd->m_file_param1));
	gtk_widget_set_sensitive(sd->edit_param1_button, file_available(sd->m_file_param1));
	gtk_widget_set_sensitive(sd->exec_param2_button, file_available(sd->m_file_param2));
	gtk_widget_set_sensitive(sd->edit_param2_button, file_available(sd->m_file_param2));
	gtk_widget_set_sensitive(sd->exec_final_button, file_available(sd->m_file_final));
	gtk_widget_set_sensitive(sd->edit_final_button, file_available(sd->m_file_final));
	gtk_widget_set_sensitive(sd->edit_log_button, file_available(sd->m_file_log));
	gtk_widget_set_sensitive(sd->edit_hyphen_button, file_available(sd->m_file_hyphen));
	gtk_widget_set_sensitive(sd->edit_tree_button, file_available(sd->m_file_tree));
	gtk_widget_set_sensitive(sd->edit_map_c_button, file_available(sd->m_file_map_c));
	gtk_widget_set_sensitive(sd->edit_map_pas_button, file_available(sd->m_file_map_pas));
	gtk_widget_set_sensitive(sd->edit_map_vb_button, file_available(sd->m_file_map_vb));
	gtk_widget_set_sensitive(sd->edit_map_gfa_button, file_available(sd->m_file_map_gfa));
	gtk_widget_set_sensitive(sd->edit_upr_button, file_available(sd->m_file_upr));
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE adjust_other_files(SHELL_DIALOG *sd)
{
	char driv[PATH_MAX];
	char path[PATH_MAX];
	char name[PATH_MAX];
	char suff[PATH_MAX];
	char *namlow;
	char slog[PATH_MAX];
	char shyp[PATH_MAX];
	char stre[PATH_MAX];

	my_fsplit(sd->m_file_dest, driv, path, name, suff);

	strcpy(slog, formatconst[sd->m_format].log_suffix);
	strcpy(shyp, slog); shyp[2] = 'h';
	strcpy(stre, slog); stre[2] = 't';

	/* determine name of log file */
	g_free(sd->m_file_log);
	sd->m_file_log = g_strdup_printf("%s%s%s%s", driv, path, name, slog);

	/* determine name of hyphen file */
	g_free(sd->m_file_hyphen);
	sd->m_file_hyphen = g_strdup_printf("%s%s%s%s", driv, path, name, shyp);

	/* determine name of tree file */
	g_free(sd->m_file_tree);
	sd->m_file_tree = g_strdup_printf("%s%s%s%s", driv, path, name, stre);

	/* determine names of map files */
	g_free(sd->m_file_map_c);
	sd->m_file_map_c = g_strdup_printf("%s%s%s%s", driv, path, name, ".hpc");
	g_free(sd->m_file_map_pas);
	sd->m_file_map_pas = g_strdup_printf("%s%s%s%s", driv, path, name, ".hpp");
	g_free(sd->m_file_map_gfa);
	sd->m_file_map_gfa = g_strdup_printf("%s%s%s%s", driv, path, name, ".hpg");
	g_free(sd->m_file_map_vb);
	sd->m_file_map_vb = g_strdup_printf("%s%s%s%s", driv, path, name, ".hpb");

	/* deterine name of UPR file */
	g_free(sd->m_file_upr);
	sd->m_file_upr = g_strdup_printf("%s%s%s%s", driv, path, name, ".upr");

	/* Parameter-Datei #1 bestimmen */
	g_free(sd->m_file_param1);
	sd->m_file_param1 = NULL;
	if (!empty(sd->m_formatdata[sd->m_format].Param1.Suffix))
	{
		if (sd->m_formatdata[sd->m_format].Param1.LowerCase)
			namlow = g_utf8_strdown(name, -1);
		else
			namlow = g_strdup(name);
		if (strcmp(sd->m_formatdata[sd->m_format].Param1.Suffix, "%") != 0)
			strcpy(suff, sd->m_formatdata[sd->m_format].Param1.Suffix);
		sd->m_file_param1 = g_strdup_printf("%s%s%s%s", driv, path, namlow, suff);
		g_freep(&namlow);
	}

	/* Parameter-Datei #2 bestimmen */
	g_freep(&sd->m_file_param2);
	if (!empty(sd->m_formatdata[sd->m_format].Param2.Suffix))
	{
		if (sd->m_formatdata[sd->m_format].Param2.LowerCase)
			namlow = g_utf8_strdown(name, -1);
		else
			namlow = g_strdup(name);
		if (strcmp(sd->m_formatdata[sd->m_format].Param2.Suffix, "%") != 0)
			strcpy(suff, sd->m_formatdata[sd->m_format].Param2.Suffix);
		sd->m_file_param2 = g_strdup_printf("%s%s%s%s", driv, path, namlow, suff);
		g_freep(&namlow);
	}

	/* Ergebnis-Datei bestimmen */
	g_freep(&sd->m_file_final);
	if (!empty(sd->m_formatdata[sd->m_format].Final.Suffix))
	{
		if (sd->m_formatdata[sd->m_format].Final.LowerCase)
			namlow = g_utf8_strdown(name, -1);
		else
			namlow = g_strdup(name);
		if (strcmp(sd->m_formatdata[sd->m_format].Final.Suffix, "%") != 0)
			strcpy(suff, sd->m_formatdata[sd->m_format].Final.Suffix);
		sd->m_file_final = g_strdup_printf("%s%s%s%s", driv, path, namlow, suff);
		g_freep(&namlow);
	}

	if (sd->hwnd != NULL)
		UpdateData(sd, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE generate_destfile(SHELL_DIALOG *sd)
{
	char driv[PATH_MAX];
	char path[PATH_MAX];
	char name[PATH_MAX];
	char suff[PATH_MAX];
	char *namlow;

	g_freep(&sd->m_file_dest);

	if (!empty(sd->m_file_source))
	{
		my_fsplit(sd->m_file_source, driv, path, name, suff);

		if (!sd->m_force_short || formatconst[sd->m_format].def_ext_short == NULL)
			strcpy(suff, formatconst[sd->m_format].def_ext_long);
		else
			strcpy(suff, formatconst[sd->m_format].def_ext_short);

		if (sd->m_use_dir && !empty(formatconst[sd->m_format].addpath))
		{
			strcat(path, formatconst[sd->m_format].addpath);
			strcat(path, G_DIR_SEPARATOR_S);
		}

		/* destfile bestimmen */
		if (sd->m_formatdata[sd->m_format].Dest.LowerCase)
			namlow = g_utf8_strdown(name, -1);
		else
			namlow = g_strdup(name);

		if (!empty(sd->m_formatdata[sd->m_format].Dest.Suffix))
		{
			if (strcmp(sd->m_formatdata[sd->m_format].Dest.Suffix, "%") != 0)
				strcpy(suff, sd->m_formatdata[sd->m_format].Dest.Suffix);
		}

		sd->m_file_dest = g_strdup_printf("%s%s%s%s", driv, path, namlow, suff);
		g_freep(&namlow);
		
		adjust_other_files(sd);
	}
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE adjust_files(SHELL_DIALOG *sd)
{
	UpdateData(sd, TRUE);
	generate_destfile(sd);
	UpdateData(sd, FALSE);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void NOINLINE ShellDialog_Delete(SHELL_DIALOG *sd)
{
	int i;
	
	if (sd != NULL)
	{
		if (sd->mru_list != NULL)
		{
			for (i = 0; i < sd->n_mru; i++)
				g_freep(&sd->mru_list[i]);
			g_free(sd->mru_list);
		}
		sd->mru_list = NULL;
		g_freep(&sd->m_file_source);
		g_freep(&sd->m_file_dest);
		g_freep(&sd->m_file_param1);
		g_freep(&sd->m_file_param2);
		g_freep(&sd->m_file_final);
		g_freep(&sd->m_file_log);
		g_freep(&sd->m_file_hyphen);
		g_freep(&sd->m_file_tree);
		g_freep(&sd->m_file_map_c);
		g_freep(&sd->m_file_map_pas);
		g_freep(&sd->m_file_map_gfa);
		g_freep(&sd->m_file_map_vb);
		g_freep(&sd->m_file_upr);
		g_freep(&sd->m_edi_udo);
		g_freep(&sd->m_app_udo);
		g_freep(&sd->udosh_helpfile);
		g_freep(&sd->udo_helpfile);
		g_freep(&sd->udo_help_commands);
		g_freep(&sd->m_inifilename);
		if (sd->m_inifile != NULL)
		{
			g_key_file_free(sd->m_inifile);
			sd->m_inifile = NULL;
		}
		
		for (i = 0; i < MAX_SYM; i++)
			g_freep(&sd->m_symbol[i]);
		
		for (i = 0; i < MAXDESTTYPE; i++)
		{
			g_freep(&sd->m_formatdata[i].Dest.Application);
			g_freep(&sd->m_formatdata[i].Dest.Editor);
			g_freep(&sd->m_formatdata[i].Dest.Suffix);
			g_freep(&sd->m_formatdata[i].Dest.Args);
			g_freep(&sd->m_formatdata[i].Param1.Application);
			g_freep(&sd->m_formatdata[i].Param1.Editor);
			g_freep(&sd->m_formatdata[i].Param1.Suffix);
			g_freep(&sd->m_formatdata[i].Param1.Args);
			g_freep(&sd->m_formatdata[i].Param2.Application);
			g_freep(&sd->m_formatdata[i].Param2.Editor);
			g_freep(&sd->m_formatdata[i].Param2.Suffix);
			g_freep(&sd->m_formatdata[i].Param2.Args);
			g_freep(&sd->m_formatdata[i].Final.Application);
			g_freep(&sd->m_formatdata[i].Final.Editor);
			g_freep(&sd->m_formatdata[i].Final.Suffix);
			g_freep(&sd->m_formatdata[i].Final.Args);
		}
		
		if (sd->tooltips != NULL)
			gtk_object_unref(GTK_OBJECT(sd->tooltips));
		sd->tooltips = NULL;

		g_free(sd);
	}
}

/*** ---------------------------------------------------------------------- ***/

static void shell_destroyed(GtkWidget *w, void *userdata)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)userdata;

	UNUSED(w);
	Help_Exit();
	ShellDialog_Delete(sd);
#if UDO_INTEGRATED
	Status_Exit();
#endif
}

/*** ---------------------------------------------------------------------- ***/

static void quit_force(GtkWidget *w, void *userdata)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)userdata;

	UNUSED(w);
	gtk_widget_destroy(sd->hwnd);
	check_toplevels(NULL);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static gboolean ProfileReadString(GKeyFile *inifile, const char *section, const char *entry, char **str)
{
	char *buf;
	GError *error = NULL;
	
	buf = g_key_file_get_string(inifile, section, entry, &error);
	g_clear_error(&error);
	if (buf != NULL)
	{
		chomp(&buf);
		g_free(*str);
		*str = buf;
		return TRUE;
	}
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

static void ProfileReadBool(GKeyFile *inifile, const char *section, const char *entry, gboolean *val)
{
	char *buf;
	GError *error = NULL;
	
	buf = g_key_file_get_string(inifile, section, entry, &error);
	g_clear_error(&error);
	if (buf != NULL)
	{
		chomp(&buf);
		if (buf != NULL && (strcmp(buf, "TRUE") == 0 || strcmp(buf, "1") == 0))
			*val = TRUE;
		else
			*val = FALSE;
		g_free(buf);
	}
}

/*** ---------------------------------------------------------------------- ***/

static void ProfileReadInt(GKeyFile *inifile, const char *section, const char *entry, int *val)
{
	char *buf;
	GError *error = NULL;

	buf = g_key_file_get_string(inifile, section, entry, &error);
	g_clear_error(&error);
	if (buf != NULL)
	{
		chomp(&buf);
		if (buf == NULL)
			*val = 0;
		else
			*val = (int)strtol(buf, NULL, 0);
		g_free(buf);
	}
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE ReadFormatInfo(GKeyFile *inifile, const char *name, const char *type, FormatInfo *data)
{
	char key[80];

	sprintf(key, "%s.%s.Application", name, type);
	ProfileReadString(inifile, "Format", key, &data->Application);
	sprintf(key, "%s.%s.Args", name, type);
	ProfileReadString(inifile, "Format", key, &data->Args);
	sprintf(key, "%s.%s.Editor", name, type);
	ProfileReadString(inifile, "Format", key, &data->Editor);
	sprintf(key, "%s.%s.Suffix", name, type);
	ProfileReadString(inifile, "Format", key, &data->Suffix);
	sprintf(key, "%s.%s.LowerCase", name, type);
	ProfileReadBool(inifile, "Format", key, &data->LowerCase);
	sprintf(key, "%s.%s.UnixPath", name, type);
	ProfileReadBool(inifile, "Format", key, &data->UnixPath);
	sprintf(key, "%s.%s.Wait", name, type);
	ProfileReadBool(inifile, "Format", key, &data->Wait);
}
/*** ---------------------------------------------------------------------- ***/

static void NOINLINE ReadFormatData(GKeyFile *inifile, int format, FormatData *data)
{
	if (formatconst[format].dest_suff != NULL && empty(data->Dest.Suffix))
		data->Dest.Suffix = g_strdup(formatconst[format].dest_suff);
	if (formatconst[format].dest_app != NULL && empty(data->Dest.Application))
		data->Dest.Application = g_strdup(formatconst[format].dest_app);
	if (formatconst[format].param1_suff != NULL && empty(data->Param1.Suffix))
		data->Param1.Suffix = g_strdup(formatconst[format].param1_suff);
	if (formatconst[format].param1_app != NULL && empty(data->Param1.Application))
		data->Param1.Application = g_strdup(formatconst[format].param1_app);
	if (formatconst[format].param2_suff != NULL && empty(data->Param2.Suffix))
		data->Param2.Suffix = g_strdup(formatconst[format].param2_suff);
	if (formatconst[format].param2_app != NULL && empty(data->Param2.Application))
		data->Param2.Application = g_strdup(formatconst[format].param2_app);
	if (formatconst[format].final_suff != NULL && empty(data->Final.Suffix))
		data->Final.Suffix = g_strdup(formatconst[format].final_suff);
	if (formatconst[format].final_app != NULL && empty(data->Final.Application))
		data->Final.Application = g_strdup(formatconst[format].final_app);
	switch (formatconst[format].type)
	{
	case TOWH4:
		if (empty(data->Param1.Args))
			data->Param1.Args = g_strdup("-x");
		break;
	}
	ReadFormatInfo(inifile, formatconst[format].name, "Dest", &data->Dest);
	ReadFormatInfo(inifile, formatconst[format].name, "Param1", &data->Param1);
	ReadFormatInfo(inifile, formatconst[format].name, "Param2", &data->Param2);
	ReadFormatInfo(inifile, formatconst[format].name, "Final", &data->Final);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE ReadProfile(SHELL_DIALOG *sd)
{
	int i;
	char *path;
	char name[80];
	GError *error = NULL;
	GKeyFile *inifile;
	int desttype;
	
	sd->m_inifilename = g_build_filename(g_get_user_config_dir(), "udosh.ini", NULL);
	inifile = sd->m_inifile = g_key_file_new();
	g_key_file_load_from_file(inifile, sd->m_inifilename, G_KEY_FILE_KEEP_COMMENTS, &error);
	g_clear_error(&error);
	
	ProfileReadString(inifile, "Shell", "Geometry", &sd->m_geometry);
	ProfileReadString(inifile, "Shell", "Source", &sd->m_file_source);
	ProfileReadString(inifile, "Shell", "Destination", &sd->m_file_dest);

	i = 0;
	for (;;)
	{
		++i;
		sprintf(name, "Source%d", i);
		path = NULL;
		if (!ProfileReadString(inifile, "MRU", name, &path))
			break;
		add_mru(sd, path);
		g_free(path);
	}
	
	ProfileReadBool(inifile, "Shell", "UseTest", &sd->m_use_test);
	ProfileReadBool(inifile, "Shell", "UseVerbose", &sd->m_use_verb);
	ProfileReadBool(inifile, "Shell", "UseHold", &sd->m_hold_key);
	ProfileReadBool(inifile, "Shell", "UseWarnings", &sd->m_warnings);
	ProfileReadBool(inifile, "Shell", "UseWarningsLines", &sd->m_warnings_lines);
	ProfileReadBool(inifile, "Shell", "UseCheck", &sd->m_use_check);
	ProfileReadBool(inifile, "Shell", "UseDir", &sd->m_use_dir);
	ProfileReadBool(inifile, "Shell", "UseQuiet", &sd->m_use_quiet);
	ProfileReadBool(inifile, "Shell", "UseForceLong", &sd->m_force_long);
	ProfileReadBool(inifile, "Shell", "UseForceShort", &sd->m_force_short);
	ProfileReadBool(inifile, "Shell", "UseFastAutoref", &sd->m_fast_autoref);
	
	ProfileReadBool(inifile, "Shell", "UseLog", &sd->m_use_log);
	ProfileReadBool(inifile, "Shell", "UseHyp", &sd->m_use_hyphen);
	ProfileReadBool(inifile, "Shell", "UseTree", &sd->m_use_tree);
	ProfileReadBool(inifile, "Shell", "UseMapC", &sd->m_use_map_c);
	ProfileReadBool(inifile, "Shell", "UseMapPas", &sd->m_use_map_pas);
	ProfileReadBool(inifile, "Shell", "UseMapVB", &sd->m_use_map_vb);
	ProfileReadBool(inifile, "Shell", "UseMapGFA", &sd->m_use_map_gfa);
	ProfileReadBool(inifile, "Shell", "UseUPR", &sd->m_use_upr);
	ProfileReadBool(inifile, "Shell", "UseIdx", &sd->m_use_idx);
	
	ProfileReadBool(inifile, "Shell", "AlwaysOnTop", &sd->m_always_on_top);
	ProfileReadBool(inifile, "Shell", "CreateDirs", &sd->m_create_dirs);
	
	for (i = 0; i < MAX_SYM; i++)
	{
		sprintf(name, "Name%d", i);
		ProfileReadString(inifile, "Symbol", name, &sd->m_symbol[i]);
		sprintf(name, "Use%d", i);
		ProfileReadBool(inifile, "Symbol", name, &sd->m_use_sym[i]);
	}

	desttype = formatconst[sd->m_format].type;
	ProfileReadInt(inifile, "Shell", "Format", &desttype);
	sd->m_format = format_index_from_type(desttype);

	ProfileReadString(inifile, "UDO", "Application", &sd->m_app_udo);
	ProfileReadInt(inifile, "UDO", "ApplicationType", &sd->m_use_udo);
	ProfileReadString(inifile, "UDO", "Editor", &sd->m_edi_udo);
	ProfileReadString(inifile, "UDO", "Helpfile", &sd->udo_helpfile);
	ProfileReadString(inifile, "UDO", "Command Index", &sd->udo_help_commands);
	
	for (i = 0; i < MAXDESTTYPE; i++)
	{
		ReadFormatData(inifile, i, &sd->m_formatdata[i]);
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void ProfileWriteString(GKeyFile *inifile, const char *section, const char *entry, const char *str)
{
	g_key_file_set_string(inifile, section, entry, fixnull(str));
}

/*** ---------------------------------------------------------------------- ***/

static void ProfileWriteBool(GKeyFile *inifile, const char *section, const char *entry, gboolean val)
{
	g_key_file_set_string(inifile, section, entry, val ? "TRUE" : "FALSE");
}

/*** ---------------------------------------------------------------------- ***/

static void ProfileWriteInt(GKeyFile *inifile, const char *section, const char *entry, int val)
{
	g_key_file_set_integer(inifile, section, entry, val);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE WriteFormatInfo(GKeyFile *inifile, const char *name, const char *type, const FormatInfo *data)
{
	char key[80];

	sprintf(key, "%s.%s.Application", name, type);
	ProfileWriteString(inifile, "Format", key, data->Application);
	sprintf(key, "%s.%s.Args", name, type);
	ProfileWriteString(inifile, "Format", key, data->Args);
	sprintf(key, "%s.%s.Editor", name, type);
	ProfileWriteString(inifile, "Format", key, data->Editor);
	sprintf(key, "%s.%s.Suffix", name, type);
	ProfileWriteString(inifile, "Format", key, data->Suffix);
	sprintf(key, "%s.%s.LowerCase", name, type);
	ProfileWriteBool(inifile, "Format", key, data->LowerCase);
	sprintf(key, "%s.%s.UnixPath", name, type);
	ProfileWriteBool(inifile, "Format", key, data->UnixPath);
	sprintf(key, "%s.%s.Wait", name, type);
	ProfileWriteBool(inifile, "Format", key, data->Wait);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE WriteFormatData(GKeyFile *inifile, int format, const FormatData *data)
{
	WriteFormatInfo(inifile, formatconst[format].name, "Dest", &data->Dest);
	WriteFormatInfo(inifile, formatconst[format].name, "Param1", &data->Param1);
	WriteFormatInfo(inifile, formatconst[format].name, "Param2", &data->Param2);
	WriteFormatInfo(inifile, formatconst[format].name, "Final", &data->Final);
}

/*** ---------------------------------------------------------------------- ***/

static gboolean NOINLINE WriteProfile(SHELL_DIALOG *sd)
{
	int i;
	char name[40];
	gsize len;
	char *data;
	FILE *fp;
	gboolean ret = FALSE;
	GKeyFile *inifile;
	
	inifile = sd->m_inifile;
	
	ProfileWriteString(inifile, "Shell", "Source", sd->m_file_source);
	ProfileWriteString(inifile, "Shell", "Destination", sd->m_file_dest);

	for (i = 0; i < sd->n_mru; i++)
	{
		sprintf(name, "Source%d", sd->n_mru - i);
		ProfileWriteString(inifile, "MRU", name, sd->mru_list[i]);
	}
	
	ProfileWriteBool(inifile, "Shell", "UseTest", sd->m_use_test);
	ProfileWriteBool(inifile, "Shell", "UseVerbose", sd->m_use_verb);
	ProfileWriteBool(inifile, "Shell", "UseHold", sd->m_hold_key);
	ProfileWriteBool(inifile, "Shell", "UseWarnings", sd->m_warnings);
	ProfileWriteBool(inifile, "Shell", "UseWarningsLines", sd->m_warnings_lines);
	ProfileWriteBool(inifile, "Shell", "UseCheck", sd->m_use_check);
	ProfileWriteBool(inifile, "Shell", "UseDir", sd->m_use_dir);
	ProfileWriteBool(inifile, "Shell", "UseQuiet", sd->m_use_quiet);
	ProfileWriteBool(inifile, "Shell", "UseForceLong", sd->m_force_long);
	ProfileWriteBool(inifile, "Shell", "UseForceShort", sd->m_force_short);
	ProfileWriteBool(inifile, "Shell", "UseFastAutoref", sd->m_fast_autoref);

	ProfileWriteBool(inifile, "Shell", "UseLog", sd->m_use_log);
	ProfileWriteBool(inifile, "Shell", "UseHyp", sd->m_use_hyphen);
	ProfileWriteBool(inifile, "Shell", "UseTree", sd->m_use_tree);
	ProfileWriteBool(inifile, "Shell", "UseMapC", sd->m_use_map_c);
	ProfileWriteBool(inifile, "Shell", "UseMapPas", sd->m_use_map_pas);
	ProfileWriteBool(inifile, "Shell", "UseMapVB", sd->m_use_map_vb);
	ProfileWriteBool(inifile, "Shell", "UseMapGFA", sd->m_use_map_gfa);
	ProfileWriteBool(inifile, "Shell", "UseUPR", sd->m_use_upr);
	ProfileWriteBool(inifile, "Shell", "UseIdx", sd->m_use_idx);

	ProfileWriteBool(inifile, "Shell", "AlwaysOnTop", sd->m_always_on_top);
	ProfileWriteBool(inifile, "Shell", "CreateDirs", sd->m_create_dirs);

	for (i = 0; i < MAX_SYM; i++)
	{
		sprintf(name, "Name%d", i);
		ProfileWriteString(inifile, "Symbol", name, sd->m_symbol[i]);
		sprintf(name, "Use%d", i);
		ProfileWriteBool(inifile, "Symbol", name, sd->m_use_sym[i]);
	}

	ProfileWriteInt(inifile, "Shell", "Format", formatconst[sd->m_format].type);

	ProfileWriteString(inifile, "UDO", "Application", sd->m_app_udo);
	ProfileWriteInt(inifile, "UDO", "ApplicationType", sd->m_use_udo);
	ProfileWriteString(inifile, "UDO", "Editor", sd->m_edi_udo);
	ProfileWriteString(inifile, "UDO", "Helpfile", sd->udo_helpfile);
	ProfileWriteString(inifile, "UDO", "Command Index", sd->udo_help_commands);
	
	for (i = 0; i < MAXDESTTYPE; i++)
	{
		WriteFormatData(inifile, i, &sd->m_formatdata[i]);
	}
	
	data = g_key_file_to_data(inifile, &len, NULL);
	
	fp = fopen(sd->m_inifilename, "wb");
	if (fp != NULL)
	{
		if (fwrite(data, 1, len, fp) == len)
			ret = TRUE;
		fclose(fp);
	}
	g_free(data);
	if (ret == FALSE)
	{
		char *msg = g_strdup_printf(_("Can't write Settings:\n%s\n%s\nQuit anyway?"), sd->m_inifilename, g_strerror(errno));
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_ERROR, msg, quit_force, sd);
		g_free(msg);
		return FALSE;
	}
	return TRUE;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static int NOINLINE StartProgram(SHELL_DIALOG *sd, char **argv, gboolean Wait)
{
	gboolean ret;
	int retCode = -1;
	GError *error = NULL;
	GPid pid;
	GSpawnFlags flags;
	char *std_output = NULL;
	char *std_error = NULL;
	
	flags = G_SPAWN_SEARCH_PATH;
	if (Wait)
	{
		ret = g_spawn_sync(NULL, argv, NULL, flags, NULL, NULL, &std_output, &std_error, &retCode, &error);
		g_free(std_output);
		g_free(std_error);
	} else
	{
		ret = g_spawn_async(NULL, argv, NULL, flags, NULL, NULL, &pid, &error);
	}
	if (ret == FALSE)
	{
		ShowWindowsError(sd->hwnd, &error);
	}
	return retCode;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void NOINLINE ChangeAOT(SHELL_DIALOG *sd)
{
	UpdateData(sd, TRUE);

	gtk_window_set_keep_above(GTK_WINDOW(sd->hwnd), sd->m_always_on_top);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/


static void config_dialog_ok(CONFIG_DIALOG *dlg, void *userdata, gboolean apply)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)userdata;

	if (apply)
	{
		sd->m_formatdata[sd->m_format].Dest = dlg->m_dest;
		sd->m_formatdata[sd->m_format].Param1 = dlg->m_param1;
		sd->m_formatdata[sd->m_format].Param2 = dlg->m_param2;
		sd->m_formatdata[sd->m_format].Final = dlg->m_final;
	
		set_udo_editor(sd, sd->m_edi_udo);
		UpdateData(sd, FALSE);
		adjust_files(sd);
		find_application(sd);
		adjust_buttons(sd);
		check_output_files(sd);
	}
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE Configure_Format(SHELL_DIALOG *sd, int radio, gboolean choose_app)
{
	CONFIG_DIALOG *dlg;

	UpdateData(sd, TRUE);
	
	dlg = Config_Dialog_New(sd->hwnd);
	
	dlg->udosh_helpfile = sd->udosh_helpfile;

	dlg->m_dest = sd->m_formatdata[sd->m_format].Dest;
	dlg->m_param1 = sd->m_formatdata[sd->m_format].Param1;
	dlg->m_param2 = sd->m_formatdata[sd->m_format].Param2;
	dlg->m_final = sd->m_formatdata[sd->m_format].Final;

	dlg->m_radio = radio;
	dlg->choose_app = choose_app;
	
	Config_Dialog_Run(dlg, config_dialog_ok, sd);
}

/*** ---------------------------------------------------------------------- ***/

static void setting_dialog_ok(SETTING_DIALOG *dlg, void *userdata, gboolean apply)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)userdata;

	if (apply)
	{
		sd->m_always_on_top = dlg->always_on_top;
		sd->m_create_dirs = dlg->create_dirs;
		sd->m_use_udo = dlg->use_udo;
		g_free(sd->udo_helpfile);
		sd->udo_helpfile = g_strdup(dlg->udo_helpfile);
		g_free(sd->udo_help_commands);
		sd->udo_help_commands = g_strdup(dlg->udo_help_commands);
		adjust_buttons(sd);
		ChangeAOT(sd);
	}
	g_free(dlg->udo_help_commands);
	dlg->udo_help_commands = NULL;
	g_free(dlg->udo_helpfile);
	dlg->udo_helpfile = NULL;
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE Configure_Settings(SHELL_DIALOG *sd)
{
	SETTING_DIALOG *dlg;
	
	dlg = Setting_Dialog_New(sd->hwnd);
	
	dlg->always_on_top = sd->m_always_on_top;
	dlg->create_dirs = sd->m_create_dirs;
	dlg->use_udo = sd->m_use_udo;
	dlg->udosh_helpfile = sd->udosh_helpfile;
	dlg->udo_helpfile = g_strdup(sd->udo_helpfile);
	dlg->udo_help_commands = g_strdup(sd->udo_help_commands);
	Setting_Dialog_Run(dlg, setting_dialog_ok, sd);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void NOINLINE ChooseSource(SHELL_DIALOG *sd)
{
	UpdateData(sd, TRUE);
	if (choose_file(sd->hwnd, &sd->m_file_source, TRUE, _("Choose UDO source file..."), IDS_SELECT_SOURCE))
	{
		add_mru(sd, sd->m_file_source);
		reset_mru(sd);
		UpdateData(sd, FALSE);
		adjust_files(sd);
		adjust_buttons(sd);
		check_output_files(sd);
	}
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE ChangeSource(SHELL_DIALOG *sd)
{
	UpdateData(sd, TRUE);
	add_mru(sd, sd->m_file_source);
	adjust_files(sd);
	adjust_buttons(sd);
	check_output_files(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE ChooseDest(SHELL_DIALOG *sd)
{
	UpdateData(sd, TRUE);
	if (choose_file(sd->hwnd, &sd->m_file_dest, FALSE, _("Choose destination file..."), IDS_SELECT_DEST))
	{
		UpdateData(sd, FALSE);
		adjust_other_files(sd);
		adjust_buttons(sd);
		check_output_files(sd);
	}
}

/*** ---------------------------------------------------------------------- ***/

static gboolean control_pressed(void)
{
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

static SHELL_DIALOG *get_shell_dialog(GtkWidget *widget)
{
	while (widget && gtk_widget_get_parent(widget))
		widget = gtk_widget_get_parent(widget);
	if (widget == NULL || gtk_widget_get_window(widget) == NULL)
		return NULL;
	return (SHELL_DIALOG *)g_object_get_data(G_OBJECT(widget), "shell-dialog");
}

/*** ---------------------------------------------------------------------- ***/

static void edit_any_ok_cb(GtkWidget *widget, gpointer user_data)
{
	char **argv = (char **)user_data;
	SHELL_DIALOG *sd;
	char *curdir = g_get_current_dir();
	
	change_dir(argv[1]);

	sd = get_shell_dialog(widget);
	if (sd != NULL)
		StartProgram(sd, argv, FALSE);
	g_strfreev(argv);
	g_chdir(curdir);
	g_free(curdir);
}

/*** ---------------------------------------------------------------------- ***/

void check_desktop_file(char **filename)
{
	if (g_pattern_match_simple("*.desktop", *filename))
	{
#ifdef G_OS_UNIX
		GAppInfo *app_info;
		char *path;
		
		app_info = (GAppInfo *)g_desktop_app_info_new_from_filename(*filename);
		if (app_info != NULL)
		{
			path = g_strdup(g_app_info_get_executable(app_info));
			if (!empty(path))
			{
				g_free(*filename);
				*filename = path;
				path = NULL;
			}
			g_free(path);
		}
		g_object_unref(app_info);
#endif
	}
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE EditAny(SHELL_DIALOG *sd, const char *type, const char *which, char *const *filename, char **editor, gboolean default_editor)
{
	char *old_editor;
	char *title;
	char *argv[4];
	int argc;
	
	UpdateData(sd, TRUE);
	if (control_pressed() || empty(*editor))
	{
		old_editor = g_strdup(*editor);
		
		title = g_strdup_printf(_("Choose editor for %s files..."), which);
		if (choose_file(sd->hwnd, editor, TRUE, title, IDS_SELECT_PROGRAM))
		{
			check_desktop_file(editor);
			UpdateData(sd, FALSE);
			if (default_editor)
				set_udo_editor(sd, old_editor);
			adjust_buttons(sd);
		}
		g_free(old_editor);
		g_free(title);
		return;
	}

	if (empty(*filename))
	{
		if (default_editor)
			show_dialog(sd->hwnd, GTK_STOCK_DIALOG_WARNING, _("Please select a source file first!"), NULL, NULL);
		return;
	}

	argc = 0;
	argv[argc++] = *editor;
	argv[argc++] = (char *)NO_CONST(*filename);
	argv[argc] = NULL;
	
	if (!file_available(*filename))
	{
		char *msg = g_strdup_printf(_("The %s file\n%s\ndoesn't exist.\nStart the editor anyway?"), type, *filename);
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_QUESTION, msg, edit_any_ok_cb, g_strdupv(argv));
		g_free(msg);
	} else
	{
		edit_any_ok_cb(sd->hwnd, g_strdupv(argv));
	}
}

/*** ---------------------------------------------------------------------- ***/

static void EditSource(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_SOURCE, _("UDO and log"), &sd->m_file_source, &sd->m_edi_udo, TRUE);
}

/*** ---------------------------------------------------------------------- ***/

static void EditDest(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_DESTINATION, _("destination"), &sd->m_file_dest, &sd->m_formatdata[sd->m_format].Dest.Editor, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

static void EditParam1(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_PARAMETER, _("parameter"), &sd->m_file_param1, &sd->m_formatdata[sd->m_format].Param1.Editor, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

static void EditParam2(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_PARAMETER, _("parameter"), &sd->m_file_param2, &sd->m_formatdata[sd->m_format].Param2.Editor, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

static void EditFinal(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_RESULT, _("result"), &sd->m_file_final, &sd->m_formatdata[sd->m_format].Final.Editor, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

static void copy_options_to_globals(SHELL_DIALOG *sd)
{
	bTestmode = sd->m_use_test;
	bVerbose = sd->m_use_verb;
	/* we keep the status window open instead of waiting for keypress */
	/* bHoldKey = sd->m_hold_key; */
	bNoWarnings = !sd->m_warnings;
	bNoWarningsLines = !sd->m_warnings_lines;
	bCheckMisc = sd->m_use_check;
	bBeQuiet = sd->m_use_quiet;

	bNoLogfile = !sd->m_use_log;
	bNoHypfile = !sd->m_use_hyphen;
	bUseTreefile = sd->m_use_tree;
	bUseIdMapFileC = sd->m_use_map_c;
	bUseIdMapFilePas = sd->m_use_map_pas;
	bUseIdMapFileVB = sd->m_use_map_vb;
	bUseIdMapFileGFA = sd->m_use_map_gfa;
	bUseUPRfile = sd->m_use_upr;
	bNoIdxfile = !sd->m_use_idx;
	bForceLong = sd->m_force_long;
	bForceShort = sd->m_force_short;
#if USE_KWSET
	bNoFastAutoref = !sd->m_fast_autoref;
#endif
	desttype = formatconst[sd->m_format].type;
}

/*** ---------------------------------------------------------------------- ***/

static void exec_source_run_cb(GtkWidget *widget, gpointer user_data)
{
	int i;
	char *argv[50 + 2 * MAX_SYM];
	int argc;
	SHELL_DIALOG *sd = get_shell_dialog(widget);
	char *curdir = g_get_current_dir();
	
	if (sd == NULL)
		return;
	UNUSED(user_data);

	if (change_dir(sd->m_file_dest) == FALSE)
	{
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_ERROR, _("Directory doesn't exist!?"), NULL, NULL);
	} else
	{
		cursor_working(sd, TRUE);
		
#if UDO_INTEGRATED
		if (sd->m_use_udo == USE_UDO_INT)
		{
			char *errors_str;
			char *warnings_str;
			char *notes_str;
			gboolean dowait;
			int val;
			char *msg;
			
			init_udo_vars();
			no_stderr_output = TRUE;
			copy_options_to_globals(sd);
			for (i = 0; i < MAX_SYM; i++)
			{
				if (sd->m_use_sym[i] && !empty(sd->m_symbol[i]))
				{
					add_udosymbol(sd->m_symbol[i]);
				}
			}
			strcpy(outfile.full, sd->m_file_dest);
			strcpy(infile.full, sd->m_file_source);
			my_fsplit(infile.full, infile.driv, infile.path, infile.name, infile.suff);
			my_fsplit(outfile.full, outfile.driv, outfile.path, outfile.name, outfile.suff);
			dest_special_adjust();
			Status_Open(sd->hwnd);
			dowait = sd->m_hold_key;
			if (udo(infile.full) == FALSE || bErrorDetected || get_error_counter() > 0)
				dowait = TRUE;
			if (get_warning_counter() > 0 || get_note_counter() || get_error_counter() > 0)
			{
				dowait = TRUE;
				
				if ((val = get_error_counter()) > 0)
					errors_str = g_strdup_printf(_("%d Errors"), val);
				else
					errors_str = NULL;
				if ((val = get_warning_counter()) > 0)
					warnings_str = g_strdup_printf(_("%d Warnings"), val);
				else
					warnings_str = NULL;
				if ((val = get_note_counter()) > 0)
					notes_str = g_strdup_printf(_("%d Notes"), val);
				else
					notes_str = NULL;
				msg = g_strconcat(
					errors_str ? errors_str : "",
					errors_str && (warnings_str || notes_str) ? ", " : "",
					warnings_str ? warnings_str : "",
					(errors_str || warnings_str) && notes_str ? ", " : "",
					notes_str ? notes_str : "",
					NULL);
				show_status_info_force(msg, TRUE);
				g_free(msg);
				g_free(notes_str);
				g_free(warnings_str);
				g_free(errors_str);
			}
			exit_udo_vars();
			if (dowait)
				Status_Wait();
			Status_Close();
		} else
#endif
		{
			argc = 0;
			argv[argc++] = sd->m_app_udo;
			argv[argc++] = (char *)NO_CONST(formatconst[sd->m_format].udo_switch);
			
			if (!sd->m_use_log) 	argv[argc++] = (char *)NO_CONST("-l");
			if (sd->m_use_check)	argv[argc++] = (char *)NO_CONST("--check");
			if (!sd->m_use_hyphen) 	argv[argc++] = (char *)NO_CONST("-y");
			if (sd->m_use_tree) 	argv[argc++] = (char *)NO_CONST("--tree");
			if (sd->m_use_upr)		argv[argc++] = (char *)NO_CONST("--save-upr");
			if (!sd->m_use_idx)		argv[argc++] = (char *)NO_CONST("--no-idxfile");
			if (sd->m_use_verb) 	argv[argc++] = (char *)NO_CONST("--verbose");
			if (sd->m_hold_key) 	argv[argc++] = (char *)NO_CONST("--hold");
			if (!sd->m_warnings)	argv[argc++] = (char *)NO_CONST("--no-warnings");
			if (!sd->m_warnings_lines)	argv[argc++] = (char *)NO_CONST("-Wl");
			if (sd->m_use_quiet)	argv[argc++] = (char *)NO_CONST("-q");
			if (sd->m_force_long)	argv[argc++] = (char *)NO_CONST("--force-long");
			if (sd->m_force_short)	argv[argc++] = (char *)NO_CONST("--force-short");
			if (!sd->m_fast_autoref)	argv[argc++] = (char *)NO_CONST("--no-fast-auto");
			if (sd->m_use_test)		argv[argc++] = (char *)NO_CONST("--test");
			
			for (i = 0; i < MAX_SYM; i++)
			{
				if (sd->m_use_sym[i] && !empty(sd->m_symbol[i]))
				{
					argv[argc++] = (char *)NO_CONST("-D");
					argv[argc++] = sd->m_symbol[i];
				}
			}
		
			if (sd->m_use_map_c)	argv[argc++] = (char *)NO_CONST("--map");
			if (sd->m_use_map_pas)	argv[argc++] = (char *)NO_CONST("--map-pas");
			if (sd->m_use_map_gfa)	argv[argc++] = (char *)NO_CONST("--map-gfa");
			if (sd->m_use_map_vb)	argv[argc++] = (char *)NO_CONST("--map-vb");
		
			/* Kommandozeile noch mit Ziel-/Quelldatei vervollstaendigen */
			argv[argc++] = (char *)NO_CONST("-o");
			argv[argc++] = sd->m_file_dest;
			
			argv[argc++] = sd->m_file_source;
			argv[argc] = NULL;
			
			/* ret = */ StartProgram(sd, argv, TRUE);
		}
		if (find_application(sd))
			adjust_buttons(sd);
		check_output_files(sd);
		
		cursor_working(sd, FALSE);
	}
	g_chdir(curdir);
	g_free(curdir);
}

/*** ---------------------------------------------------------------------- ***/

static void exec_source_makedir_cb(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG * sd = get_shell_dialog(widget);
	
	if (sd == NULL)
		return;
	/* Verzeichnis anlegen */
	if (make_dir(sd->m_file_dest) == FALSE)
	{
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_ERROR, _("Couldn't make directory!"), NULL, NULL);
		return;
	}
	exec_source_run_cb(sd->hwnd, user_data);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE ExecSource(SHELL_DIALOG *sd)
{
	char *curdir;

	UpdateData(sd, TRUE);
	if (control_pressed() || (!empty(sd->m_file_source) && empty(sd->m_app_udo)
#if UDO_INTEGRATED
		&& sd->m_use_udo != USE_UDO_INT
#endif
		))
	{
		if (choose_file(sd->hwnd, &sd->m_app_udo, TRUE, _("Choose UDO binary..."), IDS_SELECT_PROGRAM))
		{
			check_desktop_file(&sd->m_app_udo);
			UpdateData(sd, FALSE);
			adjust_buttons(sd);
		}
		return;
	}

	if (empty(sd->m_file_source))
	{
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_WARNING, _("Please select a source file first!"), NULL, NULL);
		return;
	}

	if (empty(sd->m_file_dest))
	{
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_WARNING, _("No destination file available!"), NULL, NULL);
		return;
	}

	if (!file_available(sd->m_file_source))
	{
		char *msg = g_strdup_printf(_("The source file\n%s\ndoesn't exist!"), sd->m_file_source);
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_WARNING, msg, NULL, NULL);
		g_free(msg);
		return;
	}

	curdir = g_get_current_dir();
	if (change_dir(sd->m_file_dest) == FALSE)
	{
		if (sd->m_create_dirs)
		{
			exec_source_makedir_cb(sd->hwnd, NULL);
		} else
		{
			const char *msg = _("The destination directory doesn't exist.\nMake directory now to prevent UDO from\ndisplaying an error message?");
			show_dialog(sd->hwnd, GTK_STOCK_DIALOG_QUESTION, msg, exec_source_makedir_cb, NULL);
		}
	} else
	{
		exec_source_run_cb(sd->hwnd, NULL);
	}
	g_chdir(curdir);
	g_free(curdir);
}

/*** ---------------------------------------------------------------------- ***/

static void NOINLINE ExecAny(SHELL_DIALOG *sd, int type_id, char *const *filename, FormatInfo *info)
{
	char *f;
	const char *type;
	char **argv;
	char **args;
	int i, argc;
	char *curdir;
	
	UpdateData(sd, TRUE);

	if (empty(*filename))
		return;

	if (control_pressed() || empty(info->Application))
	{
		find_application_for(*filename, info);
		Configure_Format(sd, type_id, TRUE);
		return;
	}

	if (!file_available(*filename))
	{
		char *msg;
		
		type = type_id == 0 ? IDS_TYPE_DESTINATION :
			type_id == 3 ? IDS_TYPE_RESULT :
			IDS_TYPE_PARAMETER;
		msg = g_strdup_printf(_("The %s file\n%s\ndoesn't exist."), type, *filename);
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_WARNING, msg, NULL, NULL);
		g_free(msg);
		return;
	}

	curdir = g_get_current_dir();
	change_dir(*filename);
	f = g_strdup(*filename);
	if (info->UnixPath)
	{
		backslash2slash(f);
	}

	args = NULL;
	argc = 0;
	if (!empty(info->Args))
	{
		g_shell_parse_argv(info->Args, &argc, &args, NULL);
	}
	argc += 2;
	argv = g_new(char *, argc + 1);
	
	argc = 0;
	argv[argc++] = info->Application;
	for (i = 0; args != NULL && args[i] != NULL; i++)
		argv[argc++] = args[i];
	argv[argc++] = f;
	argv[argc] = NULL;

	StartProgram(sd, argv, info->Wait);

	if (args != NULL)
		g_strfreev(args);
	g_free(argv);
	g_free(f);

	if (find_application(sd))
		adjust_buttons(sd);
	check_output_files(sd);
	g_chdir(curdir);
	g_free(curdir);
}

/*** ---------------------------------------------------------------------- ***/

static void ExecDest(SHELL_DIALOG *sd)
{
	ExecAny(sd, 0, &sd->m_file_dest, &sd->m_formatdata[sd->m_format].Dest);
}

/*** ---------------------------------------------------------------------- ***/

static void ExecParam1(SHELL_DIALOG *sd)
{
	ExecAny(sd, 1, &sd->m_file_param1, &sd->m_formatdata[sd->m_format].Param1);
}

/*** ---------------------------------------------------------------------- ***/

static void ExecParam2(SHELL_DIALOG *sd)
{
	ExecAny(sd, 2, &sd->m_file_param2, &sd->m_formatdata[sd->m_format].Param2);
}

/*** ---------------------------------------------------------------------- ***/

static void ExecFinal(SHELL_DIALOG *sd)
{
	ExecAny(sd, 3, &sd->m_file_final, &sd->m_formatdata[sd->m_format].Final);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void NOINLINE ViewFile(SHELL_DIALOG *sd, char *const *filename, const char *type)
{
	char *argv[10];
	int argc;
	char *curdir;
	
	UpdateData(sd, TRUE);

	if (empty(*filename))
		return;

	if (empty(sd->m_edi_udo))
	{
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_WARNING, _("You haven't defined an editor for UDO files!\nClick the upper right button while pressing\nthe ctrl key to choose an editor."), NULL, NULL);
		return;
	}

	if (!file_available(*filename))
	{
		char *msg = g_strdup_printf(_("The %s file\n%s\ndoesn't exist."), type, *filename);
		show_dialog(sd->hwnd, GTK_STOCK_DIALOG_ERROR, msg, NULL, NULL);
		g_free(msg);
		return;
	}

	curdir = g_get_current_dir();
	change_dir(*filename);
	argc = 0;
	argv[argc++] = sd->m_edi_udo;
	argv[argc++] = (char *)NO_CONST(*filename);
	argv[argc] = NULL;
	StartProgram(sd, argv, FALSE);
	g_chdir(curdir);
	g_free(curdir);
}

/*** ---------------------------------------------------------------------- ***/

static void ViewLog(SHELL_DIALOG *sd)
{
	ViewFile(sd, &sd->m_file_log, _("log"));
}

/*** ---------------------------------------------------------------------- ***/

static void ViewHyphen(SHELL_DIALOG *sd)
{
	ViewFile(sd, &sd->m_file_hyphen, _("hyphenation pattern"));
}

/*** ---------------------------------------------------------------------- ***/

static void ViewTree(SHELL_DIALOG *sd)
{
	ViewFile(sd, &sd->m_file_tree, _("tree"));
}

/*** ---------------------------------------------------------------------- ***/

static void ViewMapC(SHELL_DIALOG *sd)
{
	ViewFile(sd, &sd->m_file_map_c, _("map"));
}

/*** ---------------------------------------------------------------------- ***/

static void ViewMapPas(SHELL_DIALOG *sd)
{
	ViewFile(sd, &sd->m_file_map_pas, _("map"));
}

/*** ---------------------------------------------------------------------- ***/

static void ViewMapVb(SHELL_DIALOG *sd)
{
	ViewFile(sd, &sd->m_file_map_vb, _("map"));
}

/*** ---------------------------------------------------------------------- ***/

static void ViewMapGfa(SHELL_DIALOG *sd)
{
	ViewFile(sd, &sd->m_file_map_gfa, _("map"));
}

/*** ---------------------------------------------------------------------- ***/

static void ViewUpr(SHELL_DIALOG *sd)
{
	ViewFile(sd, &sd->m_file_upr, _("project"));
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static SHELL_DIALOG *NOINLINE ShellDialog_New(void)
{
	SHELL_DIALOG *sd;
	int i;

	sd = g_new0(SHELL_DIALOG, 1);
	if (sd == NULL)
		return NULL;
	
	sd->m_geometry = g_strdup("+0+0");
	
	sd->m_use_test = FALSE;
	sd->m_use_verb = TRUE;
	sd->m_hold_key = TRUE;
	sd->m_warnings = TRUE;
	sd->m_warnings_lines = TRUE;
	sd->m_use_check = FALSE;
	sd->m_use_dir = FALSE;
	sd->m_use_quiet = FALSE;
	sd->m_force_long = FALSE;
	sd->m_force_short = FALSE;
	sd->m_fast_autoref = TRUE;
	
	sd->m_use_log = TRUE;
	sd->m_use_hyphen = TRUE;
	sd->m_use_tree = FALSE;
	sd->m_use_map_c = FALSE;
	sd->m_use_map_pas = FALSE;
	sd->m_use_map_vb = FALSE;
	sd->m_use_map_gfa = FALSE;
	sd->m_use_upr = FALSE;
	sd->m_use_idx = TRUE;
	
	sd->m_always_on_top = FALSE;
	sd->m_create_dirs = FALSE;
	
	for (i = 0; i < MAX_SYM; i++)
	{
		sd->m_use_sym[i] = FALSE;
		sd->m_symbol[i] = NULL;
	}
	
	sd->m_file_source = NULL;
	sd->m_file_dest = NULL;
	sd->m_file_param1 = NULL;
	sd->m_file_param2 = NULL;
	sd->m_file_final = NULL;
	sd->m_format = format_index_from_type(TOASC);

	sd->mru_list = NULL;
	sd->n_mru = 0;
	sd->max_mru = 0;
	
	sd->m_file_log = NULL;
	sd->m_file_hyphen = NULL;
	sd->m_file_tree = NULL;
	sd->m_file_map_c = NULL;
	sd->m_file_map_pas = NULL;
	sd->m_file_map_vb = NULL;
	sd->m_file_map_gfa = NULL;
	sd->m_file_upr = NULL;

	sd->m_app_udo = g_strdup("udo");
	sd->m_edi_udo = NULL;
	sd->udosh_helpfile = g_strdup(_("udoshen.chm"));
	sd->udo_helpfile = g_strdup_printf(_("udo%sen.chm"), UDO_REL);
	sd->udo_help_commands = g_strdup(_("Command Index"));
	sd->m_use_udo = UDO_INTEGRATED ? USE_UDO_INT : USE_UDO_APP;
	
#define InitFormatInfo(fi, wait) \
	(fi)->Application = NULL; \
	(fi)->Args = NULL; \
	(fi)->Editor = NULL; \
	(fi)->Suffix = NULL; \
	(fi)->LowerCase = FALSE; \
	(fi)->UnixPath = TRUE; \
	(fi)->Wait = wait

	for (i = 0; i < MAXDESTTYPE; i++)
	{
		InitFormatInfo(&sd->m_formatdata[i].Dest, FALSE);
		InitFormatInfo(&sd->m_formatdata[i].Param1, TRUE);
		InitFormatInfo(&sd->m_formatdata[i].Param2, TRUE);
		InitFormatInfo(&sd->m_formatdata[i].Final, FALSE);
	}
#undef InitFormatInfo

	sd->m_inifilename = NULL;
	sd->hwnd = NULL;

	return sd;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void on_select_source(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ChooseSource(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_select_destination(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ChooseDest(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_exec_source(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ExecSource(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_exec_dest(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ExecDest(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_exec_param1(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ExecParam1(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_exec_param2(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ExecParam2(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_exec_final(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ExecFinal(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_source(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	EditSource(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_dest(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	EditDest(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_param1(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	EditParam1(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_param2(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	EditParam2(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_final(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	EditFinal(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_log(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ViewLog(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_hyphen(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ViewHyphen(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_tree(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ViewTree(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_map_c(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ViewMapC(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_map_pas(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ViewMapPas(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_map_vb(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ViewMapVb(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_map_gfa(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ViewMapGfa(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_edit_upr(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ViewUpr(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_dir_adjust(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	adjust_files(sd);
	adjust_buttons(sd);
	check_output_files(sd);
}

/*** ---------------------------------------------------------------------- ***/

static gboolean on_format_changed(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	adjust_files(sd);
	adjust_buttons(sd);
	check_output_files(sd);
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static gboolean on_source_changed(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	ChangeSource(sd);
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void on_quit(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	if (!WriteProfile(sd))
		return;
	quit_force(widget, sd);
}

/*** ---------------------------------------------------------------------- ***/

static gboolean wm_toplevel_close_cb(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	UNUSED(event);
	on_quit(widget, user_data);
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void on_format_configuration(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	Configure_Format(sd, 0, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

static void on_settings(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	Configure_Settings(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void on_help_contents(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	Help_Contents(sd->hwnd, sd->udosh_helpfile);
}

/*** ---------------------------------------------------------------------- ***/

static void on_help_index(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	Help_Index(sd->hwnd, sd->udosh_helpfile);
}

/*** ---------------------------------------------------------------------- ***/

static void on_help_udo(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	Help_Contents(sd->hwnd, sd->udo_helpfile);
}

/*** ---------------------------------------------------------------------- ***/

static void on_help_command_index(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	Help_Show(sd->hwnd, sd->udo_helpfile, sd->udo_help_commands);
}

/*** ---------------------------------------------------------------------- ***/

static void on_about(GtkWidget *widget, gpointer user_data)
{
	SHELL_DIALOG *sd = (SHELL_DIALOG *)user_data;
	UNUSED(widget);
	About(sd->hwnd);
}

/*** ---------------------------------------------------------------------- ***/

GdkPixbuf *app_icon(void)
{
	return gdk_pixbuf_new_from_inline(-1, udosh_data, FALSE, NULL);
}

/*** ---------------------------------------------------------------------- ***/

static void create_shell_dialog(SHELL_DIALOG *sd)
{
	GtkWidget *vbox, *hbox, *vbox2, *hbox2, *hbox3, *vbox3;
	GtkWidget *hbox5, *frame, *table;
	GtkWidget *menubar;
	GtkWidget *submenu;
	GtkWidget *item;
	GtkWidget *image;
	GtkWidget *label, *button;
	GtkAccelGroup *accel_group;
	int i;
	GdkPixbuf *icon;
	
	sd->tooltips = gtk_tooltips_new();
	gtk_object_ref(GTK_OBJECT(sd->tooltips));
	gtk_object_sink(GTK_OBJECT(sd->tooltips));
	
	accel_group = gtk_accel_group_new ();
	
	sd->hwnd = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_object_set_data(G_OBJECT(sd->hwnd), "shell-dialog", sd);
	g_object_set_data(G_OBJECT(sd->hwnd), "udoshell_window_type", NO_CONST("shell-dialog"));
	gtk_window_set_title(GTK_WINDOW(sd->hwnd), _("UDO Shell"));
	icon = app_icon();
	gtk_window_set_icon(GTK_WINDOW(sd->hwnd), icon);
	gdk_pixbuf_unref(icon);
	gtk_window_set_role(GTK_WINDOW(sd->hwnd), "udoshell");
	
	vbox = gtk_vbox_new (FALSE, 0);
	gtk_widget_show(vbox);
	gtk_container_add (GTK_CONTAINER (sd->hwnd), vbox);
 	
	menubar = gtk_menu_bar_new();
	gtk_widget_show(menubar);
	gtk_box_pack_start(GTK_BOX (vbox), menubar, FALSE, FALSE, 0);

	item = gtk_menu_item_new_with_mnemonic(_("_File"));
	gtk_widget_show(item);
	gtk_container_add(GTK_CONTAINER(menubar), item);
	submenu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);

	item = gtk_image_menu_item_new_with_mnemonic(_("Select Source..."));
	gtk_widget_show(item);
	gtk_container_add(GTK_CONTAINER(submenu), item);
	gtk_widget_add_accelerator(item, "activate", accel_group, GDK_O, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	image = gtk_image_new_from_stock("gtk-open", GTK_ICON_SIZE_MENU);
	gtk_widget_show(image);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_select_source), (gpointer) sd);
 
	item = gtk_image_menu_item_new_with_mnemonic (_("Select Destination..."));
	gtk_widget_show (item);
	gtk_container_add(GTK_CONTAINER(submenu), item);
	gtk_widget_add_accelerator(item, "activate", accel_group, GDK_S, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
	image = gtk_image_new_from_stock("gtk-save", GTK_ICON_SIZE_MENU);
	gtk_widget_show(image);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(item), image);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_select_destination), (gpointer) sd);

	item = gtk_separator_menu_item_new();
	gtk_widget_show(item);
	gtk_container_add(GTK_CONTAINER(submenu), item);
	gtk_widget_set_sensitive(item, FALSE);

	item = gtk_image_menu_item_new_from_stock("gtk-quit", accel_group);
	gtk_widget_show(item);
	gtk_container_add(GTK_CONTAINER(submenu), item);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_quit), (gpointer) sd);

	item = gtk_menu_item_new_with_mnemonic(_("_Options"));
	gtk_widget_show(item);
	gtk_container_add(GTK_CONTAINER(menubar), item);
	submenu = gtk_menu_new ();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);

	item = gtk_menu_item_new_with_mnemonic(_("_Format Configuration..."));
	gtk_widget_show(item);
	gtk_container_add(GTK_CONTAINER(submenu), item);
	gtk_widget_add_accelerator(item, "activate", accel_group, GDK_F, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_format_configuration), (gpointer) sd);

	item = gtk_image_menu_item_new_with_mnemonic (_("_Settings..."));
	gtk_widget_show (item);
	gtk_container_add (GTK_CONTAINER (submenu), item);
	gtk_widget_add_accelerator (item, "activate", accel_group, GDK_S, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
	image = gtk_image_new_from_stock ("gtk-properties", GTK_ICON_SIZE_MENU);
	gtk_widget_show (image);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_settings), (gpointer) sd);

	item = gtk_menu_item_new_with_mnemonic(_("_Help"));
	gtk_widget_show(item);
	gtk_container_add(GTK_CONTAINER(menubar), item);
	submenu = gtk_menu_new ();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);

	item = gtk_image_menu_item_new_with_mnemonic (_("_Contents"));
	gtk_widget_show (item);
	gtk_container_add (GTK_CONTAINER (submenu), item);
	image = gtk_image_new_from_stock ("gtk-info", GTK_ICON_SIZE_MENU);
	gtk_widget_show (image);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_help_contents), (gpointer) sd);

	item = gtk_image_menu_item_new_with_mnemonic (_("_Index"));
	gtk_widget_show (item);
	gtk_container_add (GTK_CONTAINER (submenu), item);
	image = gtk_image_new_from_stock ("gtk-index", GTK_ICON_SIZE_MENU);
	gtk_widget_show (image);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_help_index), (gpointer) sd);

	item = gtk_separator_menu_item_new ();
	gtk_widget_show (item);
	gtk_container_add (GTK_CONTAINER (submenu), item);
	gtk_widget_set_sensitive (item, FALSE);

	item = gtk_image_menu_item_new_with_mnemonic (_("UDO Help"));
	gtk_widget_show (item);
	gtk_container_add (GTK_CONTAINER (submenu), item);
	image = gtk_image_new_from_stock ("gtk-help", GTK_ICON_SIZE_MENU);
	gtk_widget_show (image);
	gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM (item), image);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_help_udo), (gpointer) sd);

	item = gtk_image_menu_item_new_with_mnemonic (_("UDO Command Index"));
	gtk_widget_show (item);
	gtk_container_add (GTK_CONTAINER (submenu), item);
	image = gtk_image_new_from_stock ("gtk-execute", GTK_ICON_SIZE_MENU);
	gtk_widget_show (image);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_help_command_index), (gpointer) sd);

	item = gtk_separator_menu_item_new ();
	gtk_widget_show (item);
	gtk_container_add (GTK_CONTAINER (submenu), item);
	gtk_widget_set_sensitive (item, FALSE);

	item = gtk_image_menu_item_new_with_mnemonic (_("_About"));
	gtk_widget_show (item);
	gtk_container_add (GTK_CONTAINER (submenu), item);
	image = gtk_image_new_from_stock ("gtk-about", GTK_ICON_SIZE_MENU);
	gtk_widget_show (image);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item), image);
	g_signal_connect((gpointer)item, "activate", G_CALLBACK(on_about), (gpointer) sd);

	
	hbox = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox);
	gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, TRUE, 0);

	vbox2 = gtk_vbox_new (TRUE, 0);
	gtk_widget_show (vbox2);
	gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, FALSE, 0);

	label = gtk_label_new (_("Source:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox2), label, TRUE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 5, 0);

	label = gtk_label_new (_("Dest:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox2), label, TRUE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 5, 0);

	label = gtk_label_new (_("Param #1:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox2), label, TRUE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 5, 0);

	label = gtk_label_new (_("Param #2:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox2), label, TRUE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 5, 0);

	label = gtk_label_new (_("Result:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox2), label, TRUE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 5, 0);

	vbox2 = gtk_vbox_new (TRUE, 0);
	gtk_widget_show (vbox2);
	gtk_box_pack_start (GTK_BOX (hbox), vbox2, TRUE, TRUE, 0);

	hbox2 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox2);
	gtk_box_pack_start (GTK_BOX (vbox2), hbox2, TRUE, TRUE, 0);

	sd->file_source_combo = gtk_combo_box_new_text ();
	gtk_widget_show (sd->file_source_combo);
	gtk_box_pack_start (GTK_BOX (hbox2), sd->file_source_combo, TRUE, TRUE, 0);

	sd->select_source_button = button = gtk_button_new_with_mnemonic (_("..."));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (hbox2), button, FALSE, FALSE, 0);
	gtk_widget_set_size_request(button, 30, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Select source file"), NULL);
	
	hbox2 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox2);
	gtk_box_pack_start (GTK_BOX (vbox2), hbox2, TRUE, TRUE, 0);

	sd->file_dest_entry = gtk_entry_new ();
	gtk_widget_show (sd->file_dest_entry);
	gtk_box_pack_start (GTK_BOX (hbox2), sd->file_dest_entry, TRUE, TRUE, 0);

	sd->select_dest_button = button = gtk_button_new_with_mnemonic (_("..."));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (hbox2), button, FALSE, FALSE, 0);
	gtk_widget_set_size_request(button, 30, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Select destination file"), NULL);

	sd->file_param1_entry = gtk_entry_new ();
	gtk_widget_show (sd->file_param1_entry);
	gtk_box_pack_start (GTK_BOX (vbox2), sd->file_param1_entry, TRUE, TRUE, 0);
	gtk_editable_set_editable (GTK_EDITABLE (sd->file_param1_entry), FALSE);

	sd->file_param2_entry = gtk_entry_new ();
	gtk_widget_show (sd->file_param2_entry);
	gtk_box_pack_start (GTK_BOX (vbox2), sd->file_param2_entry, TRUE, TRUE, 0);
	gtk_editable_set_editable (GTK_EDITABLE (sd->file_param2_entry), FALSE);

	sd->file_final_entry = gtk_entry_new ();
	gtk_widget_show (sd->file_final_entry);
	gtk_box_pack_start (GTK_BOX (vbox2), sd->file_final_entry, TRUE, TRUE, 0);
	gtk_editable_set_editable (GTK_EDITABLE (sd->file_final_entry), FALSE);

	vbox2 = gtk_vbox_new (TRUE, 0);
	gtk_widget_show (vbox2);
	gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, FALSE, 0);

	sd->exec_source_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run UDO"), NULL);

	sd->exec_dest_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run application for destination"), NULL);

	sd->exec_param1_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run application for parameter file #1"), NULL);

	sd->exec_param2_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run application for parameter file #2"), NULL);

	sd->exec_final_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run application for result"), NULL);

	vbox2 = gtk_vbox_new (TRUE, 0);
	gtk_widget_show (vbox2);
	gtk_box_pack_start (GTK_BOX (hbox), vbox2, FALSE, FALSE, 0);

	sd->edit_source_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run editor with source file"), NULL);
	
	sd->edit_dest_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run editor with destination"), NULL);

	sd->edit_param1_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run editor with paramater file #1"), NULL);

	sd->edit_param2_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run editor with paramater file #2"), NULL);

	sd->edit_final_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox2), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Run editor with result file"), NULL);

	hbox2 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox2);
	gtk_box_pack_start (GTK_BOX (vbox), hbox2, TRUE, TRUE, 0);

	vbox2 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox2);
	gtk_box_pack_start (GTK_BOX (hbox2), vbox2, TRUE, TRUE, 0);

	hbox5 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox5);
	gtk_box_pack_start (GTK_BOX (vbox2), hbox5, FALSE, FALSE, 0);

	label = gtk_label_new_with_mnemonic (_("_Format:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (hbox5), label, FALSE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 5, 0);

	sd->format_combo = gtk_combo_box_new_text ();
	gtk_widget_show (sd->format_combo);
	gtk_box_pack_start (GTK_BOX (hbox5), sd->format_combo, TRUE, TRUE, 0);
	gtk_label_set_mnemonic_widget (GTK_LABEL (label), sd->format_combo);

	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_box_pack_start (GTK_BOX (vbox2), frame, TRUE, TRUE, 0);
	label = gtk_label_new (_("Symbols"));
	gtk_widget_show (label);
	gtk_frame_set_label_widget (GTK_FRAME (frame), label);

	table = gtk_table_new (6, 4, FALSE);
	gtk_widget_show (table);
	gtk_container_add (GTK_CONTAINER (frame), table);

	sd->use_sym_button[0] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[0]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[0], 0, 1, 0, 1, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[1] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[1]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[1], 0, 1, 1, 2, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[2] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[2]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[2], 0, 1, 2, 3, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[3] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[3]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[3], 0, 1, 3, 4, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[4] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[4]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[4], 0, 1, 4, 5, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[5] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[5]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[5], 0, 1, 5, 6, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->symbol_entry[0] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[0]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[0], 1, 2, 0, 1, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[1] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[1]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[1], 1, 2, 1, 2, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[2] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[2]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[2], 1, 2, 2, 3, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[3] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[3]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[3], 1, 2, 3, 4, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[4] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[4]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[4], 1, 2, 4, 5, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[5] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[5]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[5], 1, 2, 5, 6, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->use_sym_button[6] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[6]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[6], 2, 3, 0, 1, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[7] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[7]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[7], 2, 3, 1, 2, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[8] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[8]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[8], 2, 3, 2, 3, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[9] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[9]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[9], 2, 3, 3, 4, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[10] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[10]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[10], 2, 3, 4, 5, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->use_sym_button[11] = gtk_check_button_new_with_mnemonic (_("-D"));
	gtk_widget_show (sd->use_sym_button[11]);
	gtk_table_attach (GTK_TABLE (table), sd->use_sym_button[11], 2, 3, 5, 6, (GtkAttachOptions) (0), (GtkAttachOptions) (0), 0, 0);

	sd->symbol_entry[6] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[6]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[6], 3, 4, 0, 1, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[7] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[7]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[7], 3, 4, 1, 2, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[8] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[8]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[8], 3, 4, 2, 3, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[9] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[9]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[9], 3, 4, 3, 4, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[10] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[10]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[10], 3, 4, 4, 5, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);

	sd->symbol_entry[11] = gtk_entry_new ();
	gtk_widget_show (sd->symbol_entry[11]);
	gtk_table_attach (GTK_TABLE (table), sd->symbol_entry[11], 3, 4, 5, 6, (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), (GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
	
	for (i = 0; i < MAX_SYM; i++)
	{
		gtk_tooltips_set_tip(sd->tooltips, sd->symbol_entry[i], _("Set the symbol `symbol' which can be tested in the source file with !ifset"), NULL);
	}
	
	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_box_pack_start (GTK_BOX (hbox2), frame, TRUE, TRUE, 0);
	label = gtk_label_new (_("Options"));
	gtk_widget_show (label);
	gtk_frame_set_label_widget (GTK_FRAME (frame), label);
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);

	hbox3 = gtk_hbox_new(FALSE, 0);
	gtk_widget_show (hbox3);
	gtk_container_add (GTK_CONTAINER (frame), hbox3);

	vbox3 = gtk_vbox_new(FALSE, 0);
	gtk_widget_show (vbox3);
	gtk_container_add (GTK_CONTAINER (hbox3), vbox3);

	sd->use_test_button = button = gtk_check_button_new_with_mnemonic (_("Test Mode"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Test syntax only, don't generate output file"), NULL);

	sd->hold_key_button = button = gtk_check_button_new_with_mnemonic (_("Press key"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Wait for keypress when UDO finishes"), NULL);

	sd->use_verb_button = button = gtk_check_button_new_with_mnemonic (_("Verbose"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Print some status information while converting the source file"), NULL);

	sd->warnings_button = button = gtk_check_button_new_with_mnemonic (_("Warnings"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Show warning messages"), NULL);

	sd->warnings_lines_button = button = gtk_check_button_new_with_mnemonic (_("Line Warnings"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Show warning messages for lines that are too short or long"), NULL);

	sd->use_check_button = button = gtk_check_button_new_with_mnemonic (_("Check"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Activate some additional checks"), NULL);

	sd->use_dir_button = button = gtk_check_button_new_with_mnemonic (_("Into Folder"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Create output file(s) in subdirectory"), NULL);

	sd->force_long_button = button = gtk_check_button_new_with_mnemonic (_("Force long"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Try to use long filenames even on operating systems that normally do not support them"), NULL);

	sd->force_short_button = button = gtk_check_button_new_with_mnemonic (_("Force short"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Force use of short filenames"), NULL);

	sd->fast_autoref_button = button = gtk_check_button_new_with_mnemonic (_("Fast autoref"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Use newer, faster algorithm for automatic searching of references"), NULL);

	vbox3 = gtk_vbox_new(FALSE, 0);
	gtk_widget_show (vbox3);
	gtk_container_add (GTK_CONTAINER (hbox3), vbox3);

	sd->use_log_button = button = gtk_check_button_new_with_mnemonic (_("Log file"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Create a log file"), NULL);

	sd->use_hyphen_button = button = gtk_check_button_new_with_mnemonic (_("Hyphen file"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Create a hyphen file"), NULL);

	sd->use_tree_button = button = gtk_check_button_new_with_mnemonic (_("Tree file"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Create a tree file with the include structure"), NULL);

	sd->use_map_c_button = button = gtk_check_button_new_with_mnemonic (_("C Map"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Create a header file for C with the WinHelp-Jump-IDs"), NULL);

	sd->use_map_pas_button = button = gtk_check_button_new_with_mnemonic (_("Pascal Map"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Create a map file with the WinHelp-Jump-IDs for Pascal/Delphi"), NULL);

	sd->use_map_vb_button = button = gtk_check_button_new_with_mnemonic (_("VB Map"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Create a map file with the WinHelp-Jump-IDs for Visual Basic"), NULL);

	sd->use_map_gfa_button = button = gtk_check_button_new_with_mnemonic (_("GFA Map"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Create a map file with the WinHelp-Jump-IDs for GFA Basic"), NULL);

	sd->use_upr_button = button = gtk_check_button_new_with_mnemonic (_("UPR file"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Save a file with the suffix .upr with a list of all source files, include files and generated files"), NULL);

	label = gtk_label_new (NULL);
	gtk_widget_show (label);
	gtk_box_pack_start(GTK_BOX(vbox3), label, TRUE, TRUE, 0);
	
	label = gtk_label_new (NULL);
	gtk_widget_show (label);
	gtk_box_pack_start(GTK_BOX(vbox3), label, TRUE, TRUE, 0);
	
	vbox3 = gtk_vbox_new(FALSE, 0);
	gtk_widget_show (vbox3);
	gtk_container_add (GTK_CONTAINER (hbox3), vbox3);

	sd->edit_log_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Start the editor with the log file"), NULL);

	sd->edit_hyphen_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Start the editor with the hyphen file"), NULL);

	sd->edit_tree_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Start the editor with the tree file"), NULL);

	sd->edit_map_c_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Start the editor with the C header file"), NULL);

	sd->edit_map_pas_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Start the editor with the Pascal header file"), NULL);

	sd->edit_map_vb_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Start the editor with the VisualBasic header file"), NULL);

	sd->edit_map_gfa_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Start the editor with the GFA header file"), NULL);

	sd->edit_upr_button = button = gtk_button_new_with_mnemonic (_("program"));
	gtk_widget_show (button);
	gtk_box_pack_start(GTK_BOX(vbox3), button, TRUE, TRUE, 0);
	gtk_widget_set_size_request(button, 80, -1);
	gtk_tooltips_set_tip(sd->tooltips, button, _("Start the editor with the project file"), NULL);

	label = gtk_label_new (NULL);
	gtk_widget_show (label);
	gtk_box_pack_start(GTK_BOX(vbox3), label, TRUE, TRUE, 0);
	
	label = gtk_label_new (NULL);
	gtk_widget_show (label);
	gtk_box_pack_start(GTK_BOX(vbox3), label, TRUE, TRUE, 0);
	
	for (i = 0; i < MAXDESTTYPE; i++)
		gtk_combo_box_append_text(GTK_COMBO_BOX(sd->format_combo), formatconst[i].name);

	reset_mru(sd);
	UpdateData(sd, FALSE);

	if (empty(sd->m_file_dest))
		adjust_files(sd);
	else
		adjust_other_files(sd);
	adjust_buttons(sd);
	check_output_files(sd);
	
	ChangeAOT(sd);
		
	gtk_window_add_accel_group (GTK_WINDOW (sd->hwnd), accel_group);

	g_signal_connect((gpointer)sd->file_source_combo, "changed", G_CALLBACK(on_source_changed), (gpointer) sd);
	g_signal_connect((gpointer)sd->select_source_button, "clicked", G_CALLBACK(on_select_source), (gpointer) sd);
	g_signal_connect((gpointer)sd->select_dest_button, "clicked", G_CALLBACK(on_select_destination), (gpointer) sd);
	g_signal_connect((gpointer)sd->exec_source_button, "clicked", G_CALLBACK(on_exec_source), (gpointer) sd);
	g_signal_connect((gpointer)sd->exec_dest_button, "clicked", G_CALLBACK(on_exec_dest), (gpointer) sd);
	g_signal_connect((gpointer)sd->exec_param1_button, "clicked", G_CALLBACK(on_exec_param1), (gpointer) sd);
	g_signal_connect((gpointer)sd->exec_param2_button, "clicked", G_CALLBACK(on_exec_param2), (gpointer) sd);
	g_signal_connect((gpointer)sd->exec_final_button, "clicked", G_CALLBACK(on_exec_final), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_source_button, "clicked", G_CALLBACK(on_edit_source), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_dest_button, "clicked", G_CALLBACK(on_edit_dest), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_param1_button, "clicked", G_CALLBACK(on_edit_param1), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_param2_button, "clicked", G_CALLBACK(on_edit_param2), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_final_button, "clicked", G_CALLBACK(on_edit_final), (gpointer) sd);
	g_signal_connect((gpointer)sd->format_combo, "changed", G_CALLBACK(on_format_changed), (gpointer) sd);
	g_signal_connect((gpointer)sd->use_dir_button, "clicked", G_CALLBACK(on_dir_adjust), (gpointer) sd);
	g_signal_connect((gpointer)sd->force_long_button, "clicked", G_CALLBACK(on_dir_adjust), (gpointer) sd);
	g_signal_connect((gpointer)sd->force_short_button, "clicked", G_CALLBACK(on_dir_adjust), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_log_button, "clicked", G_CALLBACK(on_edit_log), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_hyphen_button, "clicked", G_CALLBACK(on_edit_hyphen), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_tree_button, "clicked", G_CALLBACK(on_edit_tree), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_map_c_button, "clicked", G_CALLBACK(on_edit_map_c), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_map_pas_button, "clicked", G_CALLBACK(on_edit_map_pas), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_map_vb_button, "clicked", G_CALLBACK(on_edit_map_vb), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_map_gfa_button, "clicked", G_CALLBACK(on_edit_map_gfa), (gpointer) sd);
	g_signal_connect((gpointer)sd->edit_upr_button, "clicked", G_CALLBACK(on_edit_upr), (gpointer) sd);

	gtk_signal_connect(GTK_OBJECT(sd->hwnd), "delete_event", GTK_SIGNAL_FUNC(wm_toplevel_close_cb), (gpointer) sd);
	gtk_signal_connect(GTK_OBJECT(sd->hwnd), "destroy", GTK_SIGNAL_FUNC(shell_destroyed), (gpointer) sd);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void check_console(void)
{
#ifdef G_PLATFORM_WIN32
	CONSOLE_SCREEN_BUFFER_INFO ci;
	
	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_ERROR_HANDLE), &ci))
	{
#ifdef G_OS_UNIX
		/* G_PLATFORM_WIN32 + G_OS_UNIX = CYGWIN */
		have_console = TRUE;
#endif
	} else
	{
		have_console = TRUE;
	}
#endif /* G_PLATFORM_WIN32 */

#ifdef G_OS_UNIX
	have_console = isatty(0);
#endif
}

/*** ---------------------------------------------------------------------- ***/

static int toplevels_open_except(GtkWidget *top)
{
	GList *tops, *l;
	int num_open;
	
	tops = gtk_window_list_toplevels();
	for (l = tops, num_open = 0; l != NULL; l = l->next)
		if (l->data != top)
		{
			if (gtk_widget_get_visible(GTK_WIDGET(l->data)) &&
				g_object_get_data(G_OBJECT(l->data), "udoshell_window_type") != NULL)
			{
				num_open++;
			}
		}
	g_list_free(tops);
	return num_open;
}

/*** ---------------------------------------------------------------------- ***/

void check_toplevels(GtkWidget *toplevel)
{
	int num_open;
	
	if ((num_open = toplevels_open_except(toplevel)) == 0)
	{
		gtk_main_quit();
	}
}

/*** ---------------------------------------------------------------------- ***/

static void message_destroyed(GtkWidget *w, gpointer user_data)
{
	UNUSED(user_data);
	check_toplevels(w);
}

/*** ---------------------------------------------------------------------- ***/

static GtkWidget *show_message(SHELL_DIALOG *sd, const gchar *title, const gchar *text, gboolean big)
{
	GtkWidget *dialog, *vbox, *label;
	GtkWidget *button;
	GtkWidget *scroll;
	
	dialog = gtk_dialog_new();
	g_object_set_data(G_OBJECT(dialog), "udoshell_window_type", NO_CONST("message"));
	gtk_signal_connect(GTK_OBJECT(dialog), "destroy", GTK_SIGNAL_FUNC(message_destroyed), sd);
	gtk_window_set_title(GTK_WINDOW(dialog), title);
	gtk_window_set_modal(GTK_WINDOW(dialog), FALSE);
	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_MOUSE);
	
	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(vbox), 15);
	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), vbox, TRUE, TRUE, 0);

	label = gtk_label_new(text);
	gtk_label_set_selectable(GTK_LABEL(label), TRUE);
	if (big)
	{
		scroll = gtk_scrolled_window_new(NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
		gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scroll), label);
		gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);
	} else
	{
		gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
	}
	
	button = gtk_button_new_from_stock(GTK_STOCK_OK);
	gtk_dialog_add_action_widget(GTK_DIALOG(dialog), button, GTK_RESPONSE_CANCEL);
	gtk_signal_connect_object(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(gtk_widget_destroy), dialog);
	
	gtk_button_box_set_layout(GTK_BUTTON_BOX(gtk_dialog_get_action_area(GTK_DIALOG(dialog))), GTK_BUTTONBOX_SPREAD);

	gtk_widget_set_can_default(button, TRUE);
	gtk_widget_grab_default(button);

	if (big)
		gtk_window_set_default_size(GTK_WINDOW(dialog), 640, 400);
	gtk_widget_show_all(dialog);

	return dialog;
}

/*** ---------------------------------------------------------------------- ***/

static gboolean init_gtk(SHELL_DIALOG *sd);

/*
 * write a message to stdout/stderr if we are attached to a tty,
 * otherwise pop up a dialog
 */
static void write_console(SHELL_DIALOG *sd, const char *s, gboolean to_stderr, gboolean big)
{
	if (have_console || !init_gtk(sd))
	{
		char *desc;
		
		fflush(stdout);
		fflush(stderr);
		desc = g_locale_from_utf8(s, -1, NULL, NULL, NULL);
		if (desc)
			fputs(desc, to_stderr ? stderr : stdout);
		else
			fputs(s, to_stderr ? stderr : stdout);
		g_free(desc);
	} else
	{
		show_message(sd, to_stderr ? _("Error") : _("Warning"), s, big);
	}
}

/*** ---------------------------------------------------------------------- ***/

static gboolean init_gtk(SHELL_DIALOG *sd)
{
	int argc;
	char *argv[6];
	char **argvp;
	
	if (gtk_inited == 0)
	{
		gtk_set_locale();
		gdk_threads_init();
		argc = 0;
		argv[argc++] = (char *)NO_CONST(gl_program_name);
		argv[argc] = NULL;
		argvp = argv;
		if (!gtk_init_check(&argc, &argvp))
		{
			char *msg;
			
			gtk_inited = 2;
			msg = g_strdup_printf(_("%s: error initializing GTK (wrong display?)\n"), gl_program_name);
			write_console(sd, msg, TRUE, FALSE);
		} else
		{
			gtk_inited = 1;
		}
	}
	return gtk_inited == 1;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static gboolean NOINLINE ParseCommandLine(SHELL_DIALOG *sd, int *argc, char ***argv)
{
	GOptionContext *context;
	GOptionGroup *gtk_group;
	GError *error = NULL;
	gboolean retval;
	GOptionGroup *format_group;
	GOptionGroup *output_group;
	GOptionGroup *main_group;
	int new_format;
	gboolean format_changed;
	
	/*
	 * Glib's option parser requires global variables,
	 * copy options read from INI file there.
	 */
	bShowArgs = FALSE;
	bShowVersion = FALSE;
	bShowHelp = FALSE;
	copy_options_to_globals(sd);
	bHoldKey = FALSE;
	
	gtk_group = gtk_get_option_group(FALSE);
	context = g_option_context_new(_("[FILE]"));
	main_group = g_option_group_new(NULL, NULL, NULL, sd, NULL);
	g_option_context_set_main_group(context, main_group);
	g_option_context_set_summary(context, _("GTK Shell for UDO"));
	g_option_context_add_group(context, gtk_group);
	g_option_context_add_main_entries(context, options, GETTEXT_PACKAGE);
	format_group = g_option_group_new("format", N_("Format options"), N_("Show format options"), sd, NULL);
	g_option_group_set_translation_domain(format_group, GETTEXT_PACKAGE);
	g_option_group_add_entries(format_group, format_options);
	g_option_context_add_group(context, format_group);
	output_group = g_option_group_new("output", N_("Output options"), N_("Show output options"), sd, NULL);
	g_option_group_set_translation_domain(output_group, GETTEXT_PACKAGE);
	g_option_group_add_entries(output_group, output_options);
	g_option_context_add_group(context, output_group);
	
	/*
	 * disable automatic handling of --help from Glib because
	 * - the short option 'h' conflicts with our short option for --html
	 * - we may want to redirect the message to a dialog box
	 */
	g_option_context_set_help_enabled(context, FALSE);
	
	retval = g_option_context_parse(context, argc, argv, &error);
	if (bShowHelp)
	{
		char *msg = g_option_context_get_help(context, FALSE, NULL);
		write_console(sd, msg, FALSE, TRUE);
		g_free(msg);
	}
	g_option_context_free(context);
	
	if (retval == FALSE)
	{
		char *msg = g_strdup_printf("%s: %s\n", gl_program_name, error && error->message ? error->message : _("error parsing command line"));
		write_console(sd, msg, TRUE, FALSE);
		g_free(msg);
		g_clear_error(&error);
		return FALSE;
	}
	
	if (!empty(geom_arg))
	{
		g_free(sd->m_geometry);
		sd->m_geometry = geom_arg;
		geom_arg = NULL;
	}
	
	/*
	 * copy global options back to status var
	 */
	sd->m_use_test = bTestmode;
	sd->m_use_verb = bVerbose;
	if (bHoldKey)
		sd->m_hold_key = bHoldKey;
	sd->m_warnings = !bNoWarnings;
	sd->m_warnings_lines = !bNoWarningsLines;
	sd->m_use_check = bCheckMisc;
	sd->m_use_quiet = bBeQuiet;
	
	sd->m_use_log = !bNoLogfile;
	sd->m_use_hyphen = !bNoHypfile;
	sd->m_use_tree = bUseTreefile;
	sd->m_use_map_c = bUseIdMapFileC;
	sd->m_use_map_pas = bUseIdMapFilePas;
	sd->m_use_map_vb = bUseIdMapFileVB;
	sd->m_use_map_gfa = bUseIdMapFileGFA;
	sd->m_use_upr = bUseUPRfile;
	sd->m_use_idx = !bNoIdxfile;
	sd->m_force_long = bForceLong;
	sd->m_force_short = bForceShort;
#if USE_KWSET
	sd->m_fast_autoref = !bNoFastAutoref;
#endif
	new_format = format_index_from_type(desttype);
	format_changed = new_format != sd->m_format;
	sd->m_format = new_format;
	
	if (*argc > 1)
	{
		sd->m_file_source = g_strdup((*argv)[1]);
	}
	if ((empty(outfile_name) && empty(sd->m_file_dest)) || format_changed)
		generate_destfile(sd);

	if (!empty(outfile_name))
	{
		g_free(sd->m_file_dest);
		sd->m_file_dest = outfile_name;
		outfile_name = NULL;
	}
	
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void show_version(SHELL_DIALOG *sd)
{
	char *msg = g_strdup_printf(
		"UDO GTK Shell Version %s\n"
#if UDO_INTEGRATED
		"UDO %s, %s %s\n"
#endif
		"%s\n"
		"UDO is Open Source (see %s for further information).\n",
		UDOSH_VERSION,
#if UDO_INTEGRATED
		UDO_VERSION_STRING_OS, compile_date, compile_time,
#endif
		COPYRIGHT,
		UDO_URL);
	write_console(sd, msg, FALSE, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

static NOINLINE void wait_on_keypress(void)
{
   char input[256];

   if (bHoldKey)
   {
      fprintf(stdout, _("\nPress <RETURN>...\n"));
      fgets(input, sizeof(input), stdin);
   }
}

/*** ---------------------------------------------------------------------- ***/

static void fix_fds(void)
{
	/* Bad Things Happen if stdin, stdout, and stderr have been closed
	   (as by the `sh incantation "attraction >&- 2>&-").  When you do
	   that, the X connection gets allocated to one of these fds, and
	   then some random library writes to stderr, and random bits get
	   stuffed down the X pipe, causing "Xlib: sequence lost" errors.
	   So, we cause the first three file descriptors to be open to
	   /dev/null if they aren't open to something else already.  This
	   must be done before any other files are opened (or the closing
	   of that other file will again free up one of the "magic" first
	   three FDs.)

	   We do this by opening /dev/null three times, and then closing
	   those fds, *unless* any of them got allocated as #0, #1, or #2,
	   in which case we leave them open.  Gag.

	   Really, this crap is technically required of *every* X program,
	   if you want it to be robust in the face of "2>&-".
	 */
#ifdef G_OS_WIN32
#define NULL_DEV "nul"
#endif
#ifdef G_OS_UNIX
#define NULL_DEV "/dev/null"
#endif

	int fd0 = open(NULL_DEV, O_RDWR);
	int fd1 = open(NULL_DEV, O_RDWR);
	int fd2 = open(NULL_DEV, O_RDWR);

	if (fd0 > 2)
		close(fd0);
	if (fd1 > 2)
		close(fd1);
	if (fd2 > 2)
		close(fd2);
}

/*** ---------------------------------------------------------------------- ***/

#if defined(G_OS_WIN32) && defined(_MSC_VER)
static void myInvalidParameterHandler(const wchar_t *expression,
   const wchar_t *function,
   const wchar_t *file,
   unsigned int line, 
   uintptr_t pReserved)
{
	if (function && file)
		wprintf(L"Invalid parameter detected in function %s. File: %s Line: %d\n", function, file, line);
	if (expression)
		wprintf(L"Expression: %s\n", expression);
	(void) pReserved;
}
#endif /* G_OS_WIN32 */

/*** ---------------------------------------------------------------------- ***/

int main(int argc, char **argv)
{
	SHELL_DIALOG *sd;
	
	check_console();
	fix_fds();

#ifdef HAVE_SETLOCALE
	setlocale(LC_ALL, "");
#endif

#ifdef G_OS_WIN32
	g_win32_get_windows_version();
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#ifdef _MSC_VER
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
	_set_invalid_parameter_handler(myInvalidParameterHandler);
#endif
#endif
	
#ifdef ENABLE_NLS
	bindtextdomain(GETTEXT_PACKAGE, xs_get_locale_dir());
	textdomain(GETTEXT_PACKAGE);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
#endif

	sd = ShellDialog_New();
	if (sd == NULL)
		return 1;

	ReadProfile(sd);
	if (!ParseCommandLine(sd, &argc, &argv))
		return 1;
	
	if (bShowArgs)
	{
		/* too late here, they are already clobbered by GTK */
	} else if (bShowHelp)
	{
		/* already handled in ParseCommandLine() */
	} else if (bShowVersion)
	{
		show_version(sd);
	} else
	{
		if (!init_gtk(sd))
			return 1;
#if UDO_INTEGRATED
		Status_Init();
#endif
		
		Help_Init();
		
		add_mru(sd, sd->m_file_source);
		create_shell_dialog(sd);
	
		if (sd->hwnd == NULL)
		{
			gtk_exit(1);
		}
		
		gtk_window_parse_geometry(GTK_WINDOW(sd->hwnd), sd->m_geometry);
		
		gtk_window_present(GTK_WINDOW(sd->hwnd));
	}
	
	if (toplevels_open_except(NULL) != 0)
	{
		GDK_THREADS_ENTER();
		
		bHoldKey = FALSE;
		
		gtk_main();
		
		GDK_THREADS_LEAVE();
	}
	
	wait_on_keypress();

	return 0;
}
