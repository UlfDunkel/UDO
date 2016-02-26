#include "udosh.h"
#include <shellapi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "resource.rh"
#include "shconfig.h"
#include "help.h"
#include "misc.h"
#include "dbgmsg.h"

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

#define MAXDESTTYPE          26           /* Anzahl Ausgabeformate */

#endif /* UDO_INTEGRATED */


#ifdef __GNUC__
#  define NOINLINE __attribute__((noinline))
#else
#  define NOINLINE /**/
#endif



typedef struct _formatdata
{
	FormatInfo Dest;
	FormatInfo Param1;
	FormatInfo Param2;
	FormatInfo Final;
} FormatData;


typedef struct _shell_dialog
{
	BOOL	m_use_test;
	BOOL	m_use_verb;
	BOOL	m_hold_key;
	BOOL	m_warnings;
	BOOL	m_use_check;
	BOOL	m_use_dir;
	BOOL	m_use_quiet;
	
	BOOL	m_use_log;
	BOOL	m_use_hyp;
	BOOL	m_use_tree;
	BOOL	m_use_map_c;
	BOOL	m_use_map_pas;
	BOOL	m_use_map_vb;
	BOOL	m_use_map_gfa;
	BOOL	m_use_upr;
	BOOL	m_use_idx;
	
	BOOL	m_force_long;
	BOOL	m_force_short;
	BOOL	m_fast_autoref;
	
#define MAX_SYM 12
	char m_symbol[MAX_SYM][128];
	BOOL m_use_sym[MAX_SYM];

	char m_file_source[MAX_PATH];
	char m_file_dest[MAX_PATH];
	char m_file_param1[MAX_PATH];
	char m_file_param2[MAX_PATH];
	char m_file_final[MAX_PATH];

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
	char m_file_log[MAX_PATH];
	/* complete path to final result file */
	char m_file_hyp[MAX_PATH];
	/* complete file to generated tree file */
	char m_file_tree[MAX_PATH];
	/* complete path to generated C header file */
	char m_file_map_c[MAX_PATH];
	/* complete path to generated Pascal header file */
	char m_file_map_pas[MAX_PATH];
	/* complete path to generated VB header file */
	char m_file_map_vb[MAX_PATH];
	/* complete path to generated GFA header file */
	char m_file_map_gfa[MAX_PATH];
	/* complete path to generated UPR project file */
	char m_file_upr[MAX_PATH];

	/* Path to UDO executable, when called externally */
	char m_app_udo[MAX_PATH];
	/* path to default text editor for logfiles etc. */
	char m_edi_udo[MAX_PATH];
	
	/* path to our help file */
	char udosh_helpfile[MAX_PATH];
	/* path to UDO help file */
	char udo_helpfile[MAX_PATH];
	/* topic of command index */
	char udo_help_commands[MAX_PATH];
	int m_use_udo;
	
	BOOL	m_always_on_top;
	BOOL	m_create_dirs;
	
	FormatData m_formatdata[MAXDESTTYPE];

	char m_inifilename[MAX_PATH];
	HWND hwnd;
	HACCEL haccel;
	HWND mainHwnd;
} SHELL_DIALOG;

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

static FormatConst const formatconst[MAXDESTTYPE] =
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
		"latex.exe",
		NULL,
		NULL,
		".dvi",
		NULL,
		"--tex",
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
		"pdflatex.exe",
		NULL,
		NULL,
		".pdf",
		NULL,
		"--pdflatex",
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
		"tvhc.exe",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		"--vision",
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
		"ipfc.exe",
		NULL,
		NULL,
		NULL,
		NULL,
		".inf",
		"iview.exe",
		"--ipf",
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
		"lyx.exe",
		"--lyx",
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
		USE_UDO_EDITOR_EDIT_DEST | USE_UDO_EDITOR_EDIT_PARAM1 | USE_UDO_EDITOR_EDIT_PARAM2 | USE_UDO_EDITOR_EDIT_FINAL,
	},
};

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

#if 0
static void DebugBox(const char *format, ...)
{
	char str[1024];
	va_list args;

	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);
	MessageBox(NULL, str, "Debug", MB_OK | MB_ICONSTOP);
}
#endif

/*** ---------------------------------------------------------------------- ***/

LOCAL void cursor_working(_BOOL active)
{
	SetCursor(LoadCursor(NULL, active ? IDC_WAIT : IDC_ARROW));
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL INT_PTR CALLBACK about_dialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HBITMAP hBitmap;
	HICON hIcon;
	WORD notifyCode;
	char buf[256];
	
	UNUSED(lParam);
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_INITDIALOG:
		CenterWindow(hwnd);
		hBitmap = LoadBitmap(GetInstance(), MAKEINTRESOURCE(IDB_WEBLINK));
		SendDlgItemMessage(hwnd, IDC_WEBLINK, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
		hBitmap = LoadBitmap(GetInstance(), MAKEINTRESOURCE(IDB_EMAIL));
		SendDlgItemMessage(hwnd, IDC_EMAILLINK, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
		hIcon = LoadIcon(GetInstance(), MAKEINTRESOURCE(IDR_MAINFRAME));
		SendDlgItemMessage(hwnd, IDC_UDO_ICON, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
		return TRUE;
	case WM_CLOSE:
		EndDialog(hwnd, IDCANCEL);
		DestroyWindow(hwnd);
		return TRUE;
	case WM_COMMAND:
		notifyCode = HIWORD(wParam);
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			DestroyWindow(hwnd);
			return TRUE;
		case IDOK:
			EndDialog(hwnd, IDOK);
			DestroyWindow(hwnd);
			break;
		case IDC_EMAILLINK:
		case IDC_EMAIL:
			if (notifyCode == BN_CLICKED)
			{
				strcpy(buf, "mailto:");
				DlgGetText(hwnd, IDC_EMAIL, buf + 7, sizeof(buf) - 7);
				strcat(buf, "?subject=UDO Shell for Windows");
				ShellExecute(NULL, "open", buf, NULL, NULL, SW_SHOWNORMAL);
			}
			break;
		case IDC_WEBLINK:
		case IDC_URL:
			if (notifyCode == BN_CLICKED)
			{
				DlgGetText(hwnd, IDC_URL, buf, sizeof(buf));
				ShellExecute(NULL, "open", buf, NULL, NULL, SW_SHOWNORMAL);
			}
			break;
		}
		break;
	case WM_DESTROY:
		hBitmap = (HBITMAP)(DWORD_PTR)SendDlgItemMessage(hwnd, IDC_WEBLINK, BM_GETIMAGE, IMAGE_BITMAP, 0);
		DeleteObject(hBitmap);
		hBitmap = (HBITMAP)(DWORD_PTR)SendDlgItemMessage(hwnd, IDC_EMAILLINK, STM_GETIMAGE, IMAGE_BITMAP, 0);
		DeleteObject(hBitmap);
		hIcon = (HICON)(DWORD_PTR)SendDlgItemMessage(hwnd, IDC_UDO_ICON, STM_GETIMAGE, IMAGE_ICON, 0);
		DeleteObject(hIcon);
		break;
	}
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void About(HWND parent)
{
	DialogBox(NULL, MAKEINTRESOURCE(IDD_ABOUTBOX), parent, about_dialog);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL BOOL file_available(const char *cs)
{
	FILE *file;

	file = fopen(cs, "rb");
	if (file == NULL)
		return FALSE;
	fclose(file);
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void backslash2slash(char *s)
{
	size_t i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '\\')
			s[i] = '/';
	}
}

/*** ---------------------------------------------------------------------- ***/

LOCAL BOOL NOINLINE change_dir(const char *cs)
{
	char driv[MAX_PATH];
	char path[MAX_PATH];
	char name[MAX_PATH];
	char suff[MAX_PATH];
	size_t sl;

	my_fsplit(cs, driv, path, name, suff);

	sprintf(name, "%s%s", driv, path);

	sl = strlen(name);
	if (sl > 0)
	{
		if (name[sl-1] == '\\' || name[sl-1] == '/')
			name[sl-1] = '\0';
		return SetCurrentDirectory(name);
	}

	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL BOOL NOINLINE make_dir(const char *cs)
{
	char driv[MAX_PATH];
	char path[MAX_PATH];
	char name[MAX_PATH];
	char suff[MAX_PATH];
	size_t sl;

	my_fsplit(cs, driv, path, name, suff);

	sprintf(name, "%s%s", driv, path);

	sl = strlen(name);
	if (sl > 0)
	{
		if (name[sl-1] == '\\' || name[sl-1] == '/')
			name[sl-1] = '\0';
		return CreateDirectory(name, NULL);
	}

	return FALSE;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL BOOL NOINLINE add_mru(SHELL_DIALOG *sd, const char *filename)
{
	int i, j;
	char *tmp;
	char **new_mru;
	
	if (*filename != '\0')
	{
		for (i = 0; i < sd->n_mru; i++)
		{
			if (stricmp(filename, sd->mru_list[i]) == 0)
			{
				tmp = sd->mru_list[i];
				for (j = i-1; j >= 0; j--)
					sd->mru_list[j+1] = sd->mru_list[j];
				sd->mru_list[0] = tmp;
				return TRUE;
			}
		}
		tmp = (char *)malloc(strlen(filename) + 1);
		if (tmp == NULL)
			return FALSE;
		strcpy(tmp, filename);
		if (sd->max_mru != 0 && sd->n_mru >= sd->max_mru)
		{
			--sd->n_mru;
			free(sd->mru_list[sd->n_mru]);
		} else
		{
			if (sd->mru_list == NULL)
			{
				new_mru = (char **)malloc(sizeof(char *));
			} else
			{
				new_mru = (char **)realloc((void *)sd->mru_list, (sd->n_mru + 1) * sizeof(char *));
			}
			if (new_mru == NULL)
			{
				free(tmp);
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

LOCAL void NOINLINE reset_mru(SHELL_DIALOG *sd)
{
	int i;
	
	SendDlgItemMessage(sd->hwnd, IDC_FILE_SOURCE, CB_RESETCONTENT, 0, 0);
	for (i = 0; i < sd->n_mru; i++)
		SendDlgItemMessage(sd->hwnd, IDC_FILE_SOURCE, CB_ADDSTRING, 0, (LPARAM)sd->mru_list[i]);
	SendDlgItemMessage(sd->hwnd, IDC_FILE_SOURCE, CB_SETCURSEL, 0, 0);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void NOINLINE UpdateData(SHELL_DIALOG *sd, BOOL update)
{
	int i;

	if (update)
	{
		DlgGetText(sd->hwnd, IDC_FILE_SOURCE, sd->m_file_source, sizeof(sd->m_file_source));
		DlgGetText(sd->hwnd, IDC_FILE_DEST, sd->m_file_dest, sizeof(sd->m_file_dest));
		DlgGetText(sd->hwnd, IDC_FILE_PARAM1, sd->m_file_param1, sizeof(sd->m_file_param1));
		DlgGetText(sd->hwnd, IDC_FILE_PARAM2, sd->m_file_param2, sizeof(sd->m_file_param2));
		DlgGetText(sd->hwnd, IDC_FILE_FINAL, sd->m_file_final, sizeof(sd->m_file_final));

		sd->m_use_test = DlgGetButton(sd->hwnd, IDC_CHECK_TEST);
		sd->m_use_verb = DlgGetButton(sd->hwnd, IDC_CHECK_VERB);
		sd->m_hold_key = DlgGetButton(sd->hwnd, IDC_CHECK_KEY);
		sd->m_warnings = DlgGetButton(sd->hwnd, IDC_CHECK_WARN);
		sd->m_use_check = DlgGetButton(sd->hwnd, IDC_CHECK_CHECK);
		sd->m_use_dir = DlgGetButton(sd->hwnd, IDC_CHECK_DIR);
		sd->m_force_long = DlgGetButton(sd->hwnd, IDC_CHECK_FORCE_LONG);
		sd->m_force_short = DlgGetButton(sd->hwnd, IDC_CHECK_FORCE_SHORT);
		sd->m_fast_autoref = DlgGetButton(sd->hwnd, IDC_CHECK_FAST_AUTOREF);

		sd->m_use_hyp = DlgGetButton(sd->hwnd, IDC_CHECK_HYP);
		sd->m_use_log = DlgGetButton(sd->hwnd, IDC_CHECK_LOG);
		sd->m_use_tree = DlgGetButton(sd->hwnd, IDC_CHECK_TREE);
		sd->m_use_map_c = DlgGetButton(sd->hwnd, IDC_CHECK_MAP_C);
		sd->m_use_map_pas = DlgGetButton(sd->hwnd, IDC_CHECK_MAP_PAS);
		sd->m_use_map_vb = DlgGetButton(sd->hwnd, IDC_CHECK_MAP_VB);
		sd->m_use_map_gfa = DlgGetButton(sd->hwnd, IDC_CHECK_MAP_GFA);
		sd->m_use_upr = DlgGetButton(sd->hwnd, IDC_CHECK_UPR);

		for (i = 0; i < MAX_SYM; i++)
		{
			sd->m_use_sym[i] = DlgGetButton(sd->hwnd, IDC_CHECK_SYM1 + i);
			DlgGetText(sd->hwnd, IDC_EDIT_SYM1 + i, sd->m_symbol[i], sizeof(sd->m_symbol[i]));
		}
		
		sd->m_format = SendDlgItemMessage(sd->hwnd, IDC_FORMAT_COMBO, CB_GETCURSEL, 0, 0);
		if (sd->m_format < 0)
			sd->m_format = 0;
		else if (sd->m_format >= MAXDESTTYPE)
			sd->m_format = MAXDESTTYPE - 1;
	} else
	{
		DlgSetText(sd->hwnd, IDC_FILE_SOURCE, sd->m_file_source);
		DlgSetText(sd->hwnd, IDC_FILE_DEST, sd->m_file_dest);
		DlgSetText(sd->hwnd, IDC_FILE_PARAM1, sd->m_file_param1);
		DlgSetText(sd->hwnd, IDC_FILE_PARAM2, sd->m_file_param2);
		DlgSetText(sd->hwnd, IDC_FILE_FINAL, sd->m_file_final);

		DlgSetButton(sd->hwnd, IDC_CHECK_TEST, sd->m_use_test);
		DlgSetButton(sd->hwnd, IDC_CHECK_VERB, sd->m_use_verb);
		DlgSetButton(sd->hwnd, IDC_CHECK_KEY, sd->m_hold_key);
		DlgSetButton(sd->hwnd, IDC_CHECK_WARN, sd->m_warnings);
		DlgSetButton(sd->hwnd, IDC_CHECK_CHECK, sd->m_use_check);
		DlgSetButton(sd->hwnd, IDC_CHECK_DIR, sd->m_use_dir);
		DlgSetButton(sd->hwnd, IDC_CHECK_FORCE_LONG, sd->m_force_long);
		DlgSetButton(sd->hwnd, IDC_CHECK_FORCE_SHORT, sd->m_force_short);
		DlgSetButton(sd->hwnd, IDC_CHECK_FAST_AUTOREF, sd->m_fast_autoref);

		DlgSetButton(sd->hwnd, IDC_CHECK_HYP, sd->m_use_hyp);
		DlgSetButton(sd->hwnd, IDC_CHECK_LOG, sd->m_use_log);
		DlgSetButton(sd->hwnd, IDC_CHECK_TREE, sd->m_use_tree);
		DlgSetButton(sd->hwnd, IDC_CHECK_MAP_C, sd->m_use_map_c);
		DlgSetButton(sd->hwnd, IDC_CHECK_MAP_PAS, sd->m_use_map_pas);
		DlgSetButton(sd->hwnd, IDC_CHECK_MAP_VB, sd->m_use_map_vb);
		DlgSetButton(sd->hwnd, IDC_CHECK_MAP_GFA, sd->m_use_map_gfa);
		DlgSetButton(sd->hwnd, IDC_CHECK_UPR, sd->m_use_upr);

		for (i = 0; i < MAX_SYM; i++)
		{
			DlgSetButton(sd->hwnd, IDC_CHECK_SYM1 + i, sd->m_use_sym[i]);
			DlgSetText(sd->hwnd, IDC_EDIT_SYM1 + i, sd->m_symbol[i]);
		}
		SendDlgItemMessage(sd->hwnd, IDC_FORMAT_COMBO, CB_SETCURSEL, sd->m_format, 0);
	}
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE set_udo_editor(SHELL_DIALOG *sd, const char *old_editor)
{
	int i;
	char driv[MAX_PATH];
	char path[MAX_PATH];
	char name[MAX_PATH];
	char suff[MAX_PATH];

	my_fsplit(sd->m_edi_udo, driv, path, name, suff);
	for (i = 0; i < MAXDESTTYPE; i++)
	{
		if (formatconst[i].use_udo_editor & USE_UDO_EDITOR_EXEC_DEST)
		{
			if (sd->m_formatdata[i].Dest.Application[0] == '\0' ||
				strcmp(sd->m_formatdata[i].Dest.Application, old_editor) == 0)
			{
				strcpy(sd->m_formatdata[i].Dest.Application, sd->m_edi_udo);
				if (sd->m_format == i)
					SetDlgItemText(sd->hwnd, IDC_EXEC_DEST, name);
			}
		}
		if (formatconst[i].use_udo_editor & USE_UDO_EDITOR_EDIT_DEST)
		{
			if (sd->m_formatdata[i].Dest.Editor[0] == '\0' ||
				strcmp(sd->m_formatdata[i].Dest.Editor, old_editor) == 0)
			{
				strcpy(sd->m_formatdata[i].Dest.Editor, sd->m_edi_udo);
				if (sd->m_format == i)
					SetDlgItemText(sd->hwnd, IDC_EDIT_DEST, name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EXEC_PARAM1) && sd->m_formatdata[i].Param1.Suffix[0] != '\0')
		{
			if (sd->m_formatdata[i].Param1.Application[0] == '\0' ||
				strcmp(sd->m_formatdata[i].Param1.Application, old_editor) == 0)
			{
				strcpy(sd->m_formatdata[i].Param1.Application, sd->m_edi_udo);
				if (sd->m_format == i)
					SetDlgItemText(sd->hwnd, IDC_EXEC_PARAM1, name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EDIT_PARAM1) && sd->m_formatdata[i].Param1.Suffix[0] != '\0')
		{
			if (sd->m_formatdata[i].Param1.Editor[0] == '\0' ||
				strcmp(sd->m_formatdata[i].Param1.Editor, old_editor) == 0)
			{
				strcpy(sd->m_formatdata[i].Param1.Editor, sd->m_edi_udo);
				if (sd->m_format == i)
					SetDlgItemText(sd->hwnd, IDC_EDIT_PARAM1, name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EXEC_PARAM2) && sd->m_formatdata[i].Param2.Suffix[0] != '\0')
		{
			if (sd->m_formatdata[i].Param2.Application[0] == '\0' ||
				strcmp(sd->m_formatdata[i].Param2.Application, old_editor) == 0)
			{
				strcpy(sd->m_formatdata[i].Param2.Application, sd->m_edi_udo);
				if (sd->m_format == i)
					SetDlgItemText(sd->hwnd, IDC_EXEC_PARAM2, name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EDIT_PARAM2) && sd->m_formatdata[i].Param2.Suffix[0] != '\0')
		{
			if (sd->m_formatdata[i].Param2.Editor[0] == '\0' ||
				strcmp(sd->m_formatdata[i].Param2.Editor, old_editor) == 0)
			{
				strcpy(sd->m_formatdata[i].Param2.Editor, sd->m_edi_udo);
				if (sd->m_format == i)
					SetDlgItemText(sd->hwnd, IDC_EDIT_PARAM2, name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EXEC_FINAL) && sd->m_formatdata[i].Final.Suffix[0] != '\0')
		{
			if (sd->m_formatdata[i].Final.Application[0] == '\0' ||
				strcmp(sd->m_formatdata[i].Final.Application, old_editor) == 0)
			{
				strcpy(sd->m_formatdata[i].Final.Application, sd->m_edi_udo);
				if (sd->m_format == i)
					SetDlgItemText(sd->hwnd, IDC_EXEC_FINAL, name);
			}
		}
		if ((formatconst[i].use_udo_editor & USE_UDO_EDITOR_EDIT_FINAL) && sd->m_formatdata[i].Final.Suffix[0] != '\0')
		{
			if (sd->m_formatdata[i].Final.Editor[0] == '\0' ||
				strcmp(sd->m_formatdata[i].Final.Editor, old_editor) == 0)
			{
				strcpy(sd->m_formatdata[i].Final.Editor, sd->m_edi_udo);
				if (sd->m_format == i)
					SetDlgItemText(sd->hwnd, IDC_EDIT_FINAL, name);
			}
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

LOCAL BOOL NOINLINE find_application_for(const char *filename, char *application)
{
	HINSTANCE h;
	char exe[MAX_PATH];
	
	if (*filename != '\0' && *application == '\0')
	{
		*exe = '\0';
		h = FindExecutable(filename, NULL, exe);
		if ((UINT)(DWORD_PTR)h >= HINSTANCE_ERROR)
		{
			if (*exe == '\0')
				GetModuleFileName(h, exe, sizeof(exe));
			if (stricmp(filename, exe) != 0)
			{
				strcpy(application, exe);
				return TRUE;
			}
		}
	}
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL BOOL NOINLINE find_application(SHELL_DIALOG *sd)
{
	return find_application_for(sd->m_file_dest, sd->m_formatdata[sd->m_format].Dest.Application) |
		   find_application_for(sd->m_file_param1, sd->m_formatdata[sd->m_format].Param1.Application) |
		   find_application_for(sd->m_file_param2, sd->m_formatdata[sd->m_format].Param2.Application) |
		   find_application_for(sd->m_file_final, sd->m_formatdata[sd->m_format].Final.Application);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE adjust_buttons(SHELL_DIALOG *sd)
{
	char driv[MAX_PATH];
	char path[MAX_PATH];
	char name[MAX_PATH];
	char suff[MAX_PATH];

#if UDO_INTEGRATED
	if (sd->m_use_udo == USE_UDO_INT)
	{
		SetDlgItemText(sd->hwnd, IDC_EXEC_SOURCE, "UDO");
	} else
#endif
	{
		my_fsplit(sd->m_app_udo, driv, path, name, suff);
		SetDlgItemText(sd->hwnd, IDC_EXEC_SOURCE, name);
	}
	
	my_fsplit(sd->m_edi_udo, driv, path, name, suff);
	SetDlgItemText(sd->hwnd, IDC_EDIT_SOURCE, name);
	SetDlgItemText(sd->hwnd, IDC_BUTTON_LOG, name);
	SetDlgItemText(sd->hwnd, IDC_BUTTON_HYP, name);
	SetDlgItemText(sd->hwnd, IDC_BUTTON_TREE, name);
	SetDlgItemText(sd->hwnd, IDC_BUTTON_UPR, name);
	SetDlgItemText(sd->hwnd, IDC_BUTTON_MAP_C, name);
	SetDlgItemText(sd->hwnd, IDC_BUTTON_MAP_PAS, name);
	SetDlgItemText(sd->hwnd, IDC_BUTTON_MAP_VB, name);
	SetDlgItemText(sd->hwnd, IDC_BUTTON_MAP_GFA, name);

	my_fsplit(sd->m_formatdata[sd->m_format].Dest.Application, driv, path, name, suff); 	SetDlgItemText(sd->hwnd, IDC_EXEC_DEST, name);
	my_fsplit(sd->m_formatdata[sd->m_format].Dest.Editor, driv, path, name, suff);			SetDlgItemText(sd->hwnd, IDC_EDIT_DEST, name);
	my_fsplit(sd->m_formatdata[sd->m_format].Param1.Application, driv, path, name, suff);	SetDlgItemText(sd->hwnd, IDC_EXEC_PARAM1, name);
	my_fsplit(sd->m_formatdata[sd->m_format].Param1.Editor, driv, path, name, suff); 		SetDlgItemText(sd->hwnd, IDC_EDIT_PARAM1, name);
	my_fsplit(sd->m_formatdata[sd->m_format].Param2.Application, driv, path, name, suff);	SetDlgItemText(sd->hwnd, IDC_EXEC_PARAM2, name);
	my_fsplit(sd->m_formatdata[sd->m_format].Param2.Editor, driv, path, name, suff);		SetDlgItemText(sd->hwnd, IDC_EDIT_PARAM2, name);
	my_fsplit(sd->m_formatdata[sd->m_format].Final.Application, driv, path, name, suff);	SetDlgItemText(sd->hwnd, IDC_EXEC_FINAL, name);
	my_fsplit(sd->m_formatdata[sd->m_format].Final.Editor, driv, path, name, suff); 		SetDlgItemText(sd->hwnd, IDC_EDIT_FINAL, name);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE check_output_files(SHELL_DIALOG *sd)
{
	DlgEnable(sd->hwnd, IDC_EXEC_DEST, file_available(sd->m_file_dest));
	DlgEnable(sd->hwnd, IDC_EDIT_DEST, file_available(sd->m_file_dest));
	DlgEnable(sd->hwnd, IDC_EXEC_PARAM1, file_available(sd->m_file_param1));
	DlgEnable(sd->hwnd, IDC_EDIT_PARAM1, file_available(sd->m_file_param1));
	DlgEnable(sd->hwnd, IDC_EXEC_PARAM2, file_available(sd->m_file_param2));
	DlgEnable(sd->hwnd, IDC_EDIT_PARAM2, file_available(sd->m_file_param2));
	DlgEnable(sd->hwnd, IDC_EXEC_FINAL, file_available(sd->m_file_final));
	DlgEnable(sd->hwnd, IDC_EDIT_FINAL, file_available(sd->m_file_final));
	DlgEnable(sd->hwnd, IDC_BUTTON_LOG, file_available(sd->m_file_log));
	DlgEnable(sd->hwnd, IDC_BUTTON_HYP, file_available(sd->m_file_hyp));
	DlgEnable(sd->hwnd, IDC_BUTTON_TREE, file_available(sd->m_file_tree));
	DlgEnable(sd->hwnd, IDC_BUTTON_MAP_C, file_available(sd->m_file_map_c));
	DlgEnable(sd->hwnd, IDC_BUTTON_MAP_PAS, file_available(sd->m_file_map_pas));
	DlgEnable(sd->hwnd, IDC_BUTTON_MAP_VB, file_available(sd->m_file_map_vb));
	DlgEnable(sd->hwnd, IDC_BUTTON_MAP_GFA, file_available(sd->m_file_map_gfa));
	DlgEnable(sd->hwnd, IDC_BUTTON_UPR, file_available(sd->m_file_upr));
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE adjust_other_files(SHELL_DIALOG *sd)
{
	char driv[MAX_PATH];
	char path[MAX_PATH];
	char name[MAX_PATH];
	char suff[MAX_PATH];
	char namlow[MAX_PATH];
	char slog[MAX_PATH];
	char shyp[MAX_PATH];
	char stre[MAX_PATH];

	my_fsplit(sd->m_file_dest, driv, path, name, suff);

	strcpy(slog, formatconst[sd->m_format].log_suffix);
	strcpy(shyp, slog); shyp[2] = 'h';
	strcpy(stre, slog); stre[2] = 't';

	/* logfile bestimmen */
	sprintf(sd->m_file_log, "%s%s%s%s", driv, path, name, slog);

	/* hypfile bestimmen */
	sprintf(sd->m_file_hyp, "%s%s%s%s", driv, path, name, shyp);

	/* treefile bestimmen */
	sprintf(sd->m_file_tree, "%s%s%s%s", driv, path, name, stre);

	/* UPR file bestimmen */
	sprintf(sd->m_file_upr, "%s%s%s%s", driv, path, name, ".upr");

	/* mapfiles bestimmen */
	sprintf(sd->m_file_map_c, "%s%s%s%s", driv, path, name, ".hpc");
	sprintf(sd->m_file_map_pas, "%s%s%s%s", driv, path, name, ".hpp");
	sprintf(sd->m_file_map_gfa, "%s%s%s%s", driv, path, name, ".hpg");
	sprintf(sd->m_file_map_vb, "%s%s%s%s", driv, path, name, ".hpb");

	/* Parameter-Datei #1 bestimmen */
	sd->m_file_param1[0] = '\0';
	if (sd->m_formatdata[sd->m_format].Param1.Suffix[0] != '\0')
	{
		strcpy(namlow, name);
		if (sd->m_formatdata[sd->m_format].Param1.LowerCase)
			strlwr(namlow);
		if (strcmp(sd->m_formatdata[sd->m_format].Param1.Suffix, "%") != 0)
			strcpy(suff, sd->m_formatdata[sd->m_format].Param1.Suffix);
		sprintf(sd->m_file_param1, "%s%s%s%s", driv, path, namlow, suff);
	}

	/* Parameter-Datei #2 bestimmen */
	sd->m_file_param2[0] = '\0';
	if (sd->m_formatdata[sd->m_format].Param2.Suffix[0] != '\0')
	{
		strcpy(namlow, name);
		if (sd->m_formatdata[sd->m_format].Param2.LowerCase)
			strlwr(namlow);
		if (strcmp(sd->m_formatdata[sd->m_format].Param2.Suffix, "%") != 0)
			strcpy(suff, sd->m_formatdata[sd->m_format].Param2.Suffix);
		sprintf(sd->m_file_param2, "%s%s%s%s", driv, path, namlow, suff);
	}

	/* Ergebnis-Datei bestimmen */
	sd->m_file_final[0] = '\0';
	if (sd->m_formatdata[sd->m_format].Final.Suffix[0] != '\0')
	{
		strcpy(namlow, name);
		if (sd->m_formatdata[sd->m_format].Final.LowerCase)
			strlwr(namlow);
		if (strcmp(sd->m_formatdata[sd->m_format].Final.Suffix, "%") != 0)
			strcpy(suff, sd->m_formatdata[sd->m_format].Final.Suffix);
		sprintf(sd->m_file_final, "%s%s%s%s", driv, path, namlow, suff);
	}

	UpdateData(sd, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE adjust_files(SHELL_DIALOG *sd)
{
	char driv[MAX_PATH];
	char path[MAX_PATH];
	char name[MAX_PATH];
	char suff[MAX_PATH];
	char namlow[MAX_PATH];
	char addpath[MAX_PATH];

	UpdateData(sd, TRUE);

	sd->m_file_dest[0] = '\0';

	if (sd->m_file_source[0] != '\0')
	{
		my_fsplit(sd->m_file_source, driv, path, name, suff);

		if (!sd->m_force_short || formatconst[sd->m_format].def_ext_short == NULL)
			strcpy(suff, formatconst[sd->m_format].def_ext_long);
		else
			strcpy(suff, formatconst[sd->m_format].def_ext_short);
		strcpy(addpath, formatconst[sd->m_format].addpath);

		if (sd->m_use_dir)
		{
			strcat(path, addpath);
			strcat(path, "\\");
		}

		/* destfile bestimmen */
		strcpy(namlow, name);
		if (sd->m_formatdata[sd->m_format].Dest.LowerCase)
		{
			strlwr(namlow);
		}

		if (sd->m_formatdata[sd->m_format].Dest.Suffix[0] != '\0')
		{
			if (strcmp(sd->m_formatdata[sd->m_format].Dest.Suffix, "%") != 0)
				strcpy(suff, sd->m_formatdata[sd->m_format].Dest.Suffix);
		}

		sprintf(sd->m_file_dest, "%s%s%s%s", driv, path, namlow, suff);

		adjust_other_files(sd);
	}

	UpdateData(sd, FALSE);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL BOOL ProfileReadString(const char *inifilename, const char *section, const char *entry, char *str, size_t maxlen)
{
	return GetPrivateProfileString(section, entry, str, str, maxlen, inifilename) != 0;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ProfileReadBool(const char *inifilename, const char *section, const char *entry, BOOL *val)
{
	char buf[20];
	
	GetPrivateProfileString(section, entry, *val ? "TRUE" : "FALSE", buf, sizeof(buf), inifilename);
	if (strcmp(buf, "TRUE") == 0 || strcmp(buf, "1") == 0)
		*val = TRUE;
	else
		*val = FALSE;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ProfileReadInt(const char *inifilename, const char *section, const char *entry, int *val)
{
	char buf[20];

	itoa(*val, buf, 10);
	GetPrivateProfileString(section, entry, buf, buf, sizeof(buf), inifilename);
	*val = (int)strtol(buf, NULL, 0);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE ReadFormatInfo(const char *inifilename, const char *name, const char *type, FormatInfo *data)
{
	char key[80];

	sprintf(key, "%s.%s.Application", name, type);
	ProfileReadString(inifilename, "Format", key, data->Application, sizeof(data->Application));
	sprintf(key, "%s.%s.Args", name, type);
	ProfileReadString(inifilename, "Format", key, data->Args, sizeof(data->Args));
	sprintf(key, "%s.%s.Editor", name, type);
	ProfileReadString(inifilename, "Format", key, data->Editor, sizeof(data->Editor));
	sprintf(key, "%s.%s.Suffix", name, type);
	ProfileReadString(inifilename, "Format", key, data->Suffix, sizeof(data->Suffix));
	sprintf(key, "%s.%s.LowerCase", name, type);
	ProfileReadBool(inifilename, "Format", key, &data->LowerCase);
	sprintf(key, "%s.%s.UnixPath", name, type);
	ProfileReadBool(inifilename, "Format", key, &data->UnixPath);
	sprintf(key, "%s.%s.Wait", name, type);
	ProfileReadBool(inifilename, "Format", key, &data->Wait);
}
/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE ReadFormatData(const char *inifilename, int format, FormatData *data)
{
	if (formatconst[format].dest_suff != NULL && data->Dest.Suffix[0] == '\0')
		strcpy(data->Dest.Suffix, formatconst[format].dest_suff);
	if (formatconst[format].dest_app != NULL && data->Dest.Application[0] == '\0')
		strcpy(data->Dest.Application, formatconst[format].dest_app);
	if (formatconst[format].param1_suff != NULL && data->Param1.Suffix[0] == '\0')
		strcpy(data->Param1.Suffix, formatconst[format].param1_suff);
	if (formatconst[format].param1_app != NULL && data->Param1.Application[0] == '\0')
		strcpy(data->Param1.Application, formatconst[format].param1_app);
	if (formatconst[format].param2_suff != NULL && data->Param2.Suffix[0] == '\0')
		strcpy(data->Param2.Suffix, formatconst[format].param2_suff);
	if (formatconst[format].param2_app != NULL && data->Param2.Application[0] == '\0')
		strcpy(data->Param2.Application, formatconst[format].param2_app);
	if (formatconst[format].final_suff != NULL && data->Final.Suffix[0] == '\0')
		strcpy(data->Final.Suffix, formatconst[format].final_suff);
	if (formatconst[format].final_app != NULL && data->Final.Application[0] == '\0')
		strcpy(data->Final.Application, formatconst[format].final_app);
	switch (formatconst[format].type)
	{
	case TOWH4:
		if (data->Param1.Args[0] == '\0')
			strcpy(data->Param1.Args, "-x");
		break;
	}
	ReadFormatInfo(inifilename, formatconst[format].name, "Dest", &data->Dest);
	ReadFormatInfo(inifilename, formatconst[format].name, "Param1", &data->Param1);
	ReadFormatInfo(inifilename, formatconst[format].name, "Param2", &data->Param2);
	ReadFormatInfo(inifilename, formatconst[format].name, "Final", &data->Final);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE ReadProfile(SHELL_DIALOG *sd)
{
	int i;
	char driv[MAX_PATH];
	char path[MAX_PATH];
	char name[MAX_PATH];
	char suff[MAX_PATH];
	char exe[MAX_PATH];
	
	if (GetModuleFileName(GetInstance(), exe, sizeof(exe)))
	{
		my_fsplit(exe, driv, path, name, suff);
	} else
	{
		*driv = '\0';
		*path = '\0';
		strcpy(name, "udosh");
	}
	sprintf(sd->m_inifilename, "%s%s%s%s", driv, path, name, ".ini");
	
	ProfileReadString(sd->m_inifilename, "Shell", "Source", sd->m_file_source, sizeof(sd->m_file_source));
	ProfileReadString(sd->m_inifilename, "Shell", "Destination", sd->m_file_dest, sizeof(sd->m_file_dest));

	i = 0;
	for (;;)
	{
		++i;
		sprintf(name, "Source%d", i);
		*path = '\0';
		if (!ProfileReadString(sd->m_inifilename, "MRU", name, path, sizeof(path)))
			break;
		add_mru(sd, path);
	}
	
	ProfileReadBool(sd->m_inifilename, "Shell", "UseTest", &sd->m_use_test);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseVerbose", &sd->m_use_verb);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseHold", &sd->m_hold_key);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseWarnings", &sd->m_warnings);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseCheck", &sd->m_use_check);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseDir", &sd->m_use_dir);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseQuiet", &sd->m_use_quiet);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseForceLong", &sd->m_force_long);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseForceShort", &sd->m_force_short);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseFastAutoref", &sd->m_fast_autoref);
	
	ProfileReadBool(sd->m_inifilename, "Shell", "UseLog", &sd->m_use_log);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseHyp", &sd->m_use_hyp);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseTree", &sd->m_use_tree);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseMapC", &sd->m_use_map_c);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseMapPas", &sd->m_use_map_pas);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseMapVB", &sd->m_use_map_vb);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseMapGFA", &sd->m_use_map_gfa);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseUPR", &sd->m_use_upr);
	ProfileReadBool(sd->m_inifilename, "Shell", "UseIdx", &sd->m_use_idx);
	
	ProfileReadBool(sd->m_inifilename, "Shell", "AlwaysOnTop", &sd->m_always_on_top);
	ProfileReadBool(sd->m_inifilename, "Shell", "CreateDirs", &sd->m_create_dirs);
	
	for (i = 0; i < MAX_SYM; i++)
	{
		sprintf(name, "Name%d", i);
		ProfileReadString(sd->m_inifilename, "Symbol", name, sd->m_symbol[i], sizeof(sd->m_symbol[i]));
		sprintf(name, "Use%d", i);
		ProfileReadBool(sd->m_inifilename, "Symbol", name, &sd->m_use_sym[i]);
	}

	ProfileReadInt(sd->m_inifilename, "Shell", "Format", &sd->m_format);

	ProfileReadString(sd->m_inifilename, "UDO", "Application", sd->m_app_udo, sizeof(sd->m_app_udo));
	ProfileReadInt(sd->m_inifilename, "UDO", "ApplicationType", &sd->m_use_udo);
	ProfileReadString(sd->m_inifilename, "UDO", "Editor", sd->m_edi_udo, sizeof(sd->m_edi_udo));
	ProfileReadString(sd->m_inifilename, "UDO", "Helpfile", sd->udo_helpfile, sizeof(sd->udo_helpfile));
	ProfileReadString(sd->m_inifilename, "UDO", "Command Index", sd->udo_help_commands, sizeof(sd->udo_help_commands));
	
	for (i = 0; i < MAXDESTTYPE; i++)
	{
		ReadFormatData(sd->m_inifilename, i, &sd->m_formatdata[i]);
	}

	for (i = 0; i < MAXDESTTYPE; i++)
	{
		if (sd->m_format == formatconst[i].type)
		{
			sd->m_format = i;
			break;
		}
	}
	if (i >= MAXDESTTYPE)
		sd->m_format = 0;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void ProfileWriteString(const char *inifilename, const char *section, const char *entry, const char *str)
{
	WritePrivateProfileString(section, entry, str, inifilename);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ProfileWriteBool(const char *inifilename, const char *section, const char *entry, BOOL val)
{
	WritePrivateProfileString(section, entry, val ? "TRUE" : "FALSE", inifilename);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ProfileWriteInt(const char *inifilename, const char *section, const char *entry, int val)
{
	char buf[20];
	
	itoa(val, buf, 10);
	WritePrivateProfileString(section, entry, buf, inifilename);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE WriteFormatInfo(const char *inifilename, const char *name, const char *type, const FormatInfo *data)
{
	char key[80];

	sprintf(key, "%s.%s.Application", name, type);
	ProfileWriteString(inifilename, "Format", key, data->Application);
	sprintf(key, "%s.%s.Args", name, type);
	ProfileWriteString(inifilename, "Format", key, data->Args);
	sprintf(key, "%s.%s.Editor", name, type);
	ProfileWriteString(inifilename, "Format", key, data->Editor);
	sprintf(key, "%s.%s.Suffix", name, type);
	ProfileWriteString(inifilename, "Format", key, data->Suffix);
	sprintf(key, "%s.%s.LowerCase", name, type);
	ProfileWriteBool(inifilename, "Format", key, data->LowerCase);
	sprintf(key, "%s.%s.UnixPath", name, type);
	ProfileWriteBool(inifilename, "Format", key, data->UnixPath);
	sprintf(key, "%s.%s.Wait", name, type);
	ProfileWriteBool(inifilename, "Format", key, data->Wait);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE WriteFormatData(const char *inifilename, int format, const FormatData *data)
{
	WriteFormatInfo(inifilename, formatconst[format].name, "Dest", &data->Dest);
	WriteFormatInfo(inifilename, formatconst[format].name, "Param1", &data->Param1);
	WriteFormatInfo(inifilename, formatconst[format].name, "Param2", &data->Param2);
	WriteFormatInfo(inifilename, formatconst[format].name, "Final", &data->Final);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE WriteProfile(SHELL_DIALOG *sd)
{
	int i;
	char name[40];

	ProfileWriteString(sd->m_inifilename, "Shell", "Source", sd->m_file_source);
	ProfileWriteString(sd->m_inifilename, "Shell", "Destination", sd->m_file_dest);

	for (i = 0; i < sd->n_mru; i++)
	{
		sprintf(name, "Source%d", sd->n_mru - i);
		ProfileWriteString(sd->m_inifilename, "MRU", name, sd->mru_list[i]);
	}
	
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseTest", sd->m_use_test);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseVerbose", sd->m_use_verb);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseHold", sd->m_hold_key);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseWarnings", sd->m_warnings);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseCheck", sd->m_use_check);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseDir", sd->m_use_dir);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseQuiet", sd->m_use_quiet);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseForceLong", sd->m_force_long);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseForceShort", sd->m_force_short);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseFastAutoref", sd->m_fast_autoref);

	ProfileWriteBool(sd->m_inifilename, "Shell", "UseLog", sd->m_use_log);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseHyp", sd->m_use_hyp);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseTree", sd->m_use_tree);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseMapC", sd->m_use_map_c);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseMapPas", sd->m_use_map_pas);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseMapVB", sd->m_use_map_vb);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseMapGFA", sd->m_use_map_gfa);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseUPR", sd->m_use_upr);
	ProfileWriteBool(sd->m_inifilename, "Shell", "UseIdx", sd->m_use_idx);

	ProfileWriteBool(sd->m_inifilename, "Shell", "AlwaysOnTop", sd->m_always_on_top);
	ProfileWriteBool(sd->m_inifilename, "Shell", "CreateDirs", sd->m_create_dirs);

	for (i = 0; i < MAX_SYM; i++)
	{
		sprintf(name, "Name%d", i);
		ProfileWriteString(sd->m_inifilename, "Symbol", name, sd->m_symbol[i]);
		sprintf(name, "Use%d", i);
		ProfileWriteBool(sd->m_inifilename, "Symbol", name, sd->m_use_sym[i]);
	}

	ProfileWriteInt(sd->m_inifilename, "Shell", "Format", formatconst[sd->m_format].type);

	ProfileWriteString(sd->m_inifilename, "UDO", "Application", sd->m_app_udo);
	ProfileWriteInt(sd->m_inifilename, "UDO", "ApplicationType", sd->m_use_udo);
	ProfileWriteString(sd->m_inifilename, "UDO", "Editor", sd->m_edi_udo);
	ProfileWriteString(sd->m_inifilename, "UDO", "Helpfile", sd->udo_helpfile);
	ProfileWriteString(sd->m_inifilename, "UDO", "Command Index", sd->udo_help_commands);
	
	for (i = 0; i < MAXDESTTYPE; i++)
	{
		WriteFormatData(sd->m_inifilename, i, &sd->m_formatdata[i]);
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void NOINLINE ShowWindowsError(HWND parent, ...)
{
	DWORD error;
	char mb[1024];
	va_list args;
	
	error = GetLastError();
	va_start(args, parent);
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), mb, sizeof(mb), &args);
	va_end(args);
	MessageBox(parent, mb, NULL, MB_ICONERROR | MB_OK);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL int NOINLINE StartProgram(SHELL_DIALOG *sd, char *cmd, BOOL Wait)
{
	BOOL ret;
	STARTUPINFO startInfo;
	PROCESS_INFORMATION procInfo;
	DWORD exitCode;
	int retCode;
	DWORD fdwCreate;
	
	memset(&startInfo, 0, sizeof(startInfo));
	startInfo.cb = sizeof(startInfo);
	startInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	startInfo.wShowWindow = SW_SHOWNORMAL;
	startInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	startInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	startInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
	fdwCreate = CREATE_DEFAULT_ERROR_MODE | CREATE_NEW_CONSOLE;
	ret = CreateProcess(NULL, cmd, NULL, NULL, FALSE, fdwCreate, NULL, NULL, &startInfo, &procInfo);
	if (ret == FALSE)
	{
		ShowWindowsError(sd->hwnd, cmd);
		retCode = -1;
	} else
	{
		if (Wait)
		{
			for (;;)
			{
				MSG msg;
				
				if (WaitForSingleObject(procInfo.hProcess, 10) == WAIT_OBJECT_0)
					break;
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					if (sd->haccel == NULL || !TranslateAccelerator(sd->mainHwnd, sd->haccel, &msg))
					{
						if (!IsDialogMessage(sd->hwnd, &msg))
						{
							TranslateMessage(&msg);
							DispatchMessage(&msg);
							if (msg.message == WM_QUIT)
							{
								PostMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
								break;
							}
						}
					}
				}
			}
			GetExitCodeProcess(procInfo.hProcess, &exitCode);
			retCode = (int)exitCode;
		} else
		{
			retCode = 0;
		}
		CloseHandle(procInfo.hThread);
		CloseHandle(procInfo.hProcess);
	}
	return retCode;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void NOINLINE ChangeAOT(SHELL_DIALOG *sd)
{
	UpdateData(sd, TRUE);

	if (sd->m_always_on_top)
	{
		SetWindowPos(GetParent(sd->hwnd), HWND_TOPMOST, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE);
	} else
	{
		SetWindowPos(GetParent(sd->hwnd), HWND_NOTOPMOST, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE);
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL BOOL NOINLINE Configure_Format(SHELL_DIALOG *sd, int radio, BOOL choose_app)
{
	CONFIG_DIALOG dlg;

	UpdateData(sd, TRUE);
	
	strcpy(dlg.udosh_helpfile, sd->udosh_helpfile);

	dlg.m_dest = sd->m_formatdata[sd->m_format].Dest;
	dlg.m_param1 = sd->m_formatdata[sd->m_format].Param1;
	dlg.m_param2 = sd->m_formatdata[sd->m_format].Param2;
	dlg.m_final = sd->m_formatdata[sd->m_format].Final;

	dlg.m_radio = radio;
	dlg.choose_app = choose_app;
	
	if (Config_Dialog(sd->hwnd, &dlg) == IDOK)
	{
		sd->m_formatdata[sd->m_format].Dest = dlg.m_dest;
		sd->m_formatdata[sd->m_format].Param1 = dlg.m_param1;
		sd->m_formatdata[sd->m_format].Param2 = dlg.m_param2;
		sd->m_formatdata[sd->m_format].Final = dlg.m_final;

		set_udo_editor(sd, sd->m_edi_udo);
		UpdateData(sd, FALSE);
		adjust_files(sd);
		find_application(sd);
		adjust_buttons(sd);
		check_output_files(sd);
		return TRUE;
	}
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE Configure_Settings(SHELL_DIALOG *sd)
{
	SETTING_DIALOG dlg;
	
	dlg.always_on_top = sd->m_always_on_top;
	dlg.create_dirs = sd->m_create_dirs;
	dlg.use_udo = sd->m_use_udo;
	strcpy(dlg.udosh_helpfile, sd->udosh_helpfile);
	strcpy(dlg.udo_helpfile, sd->udo_helpfile);
	strcpy(dlg.udo_help_commands, sd->udo_help_commands);
	if (Setting_Dialog(sd->hwnd, &dlg) == IDOK)
	{
		sd->m_always_on_top = dlg.always_on_top;
		sd->m_create_dirs = dlg.create_dirs;
		sd->m_use_udo = dlg.use_udo;
		strcpy(sd->udo_helpfile, dlg.udo_helpfile);
		strcpy(sd->udo_help_commands, dlg.udo_help_commands);
		adjust_buttons(sd);
		ChangeAOT(sd);
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void NOINLINE ChooseSource(SHELL_DIALOG *sd)
{
	char title[256];
	char select[256];
	
	LoadString(GetInstance(), IDS_CHOOSE_SOURCE, title, sizeof(title));
	LoadString(GetInstance(), IDS_SELECT_SOURCE, select, sizeof(select));
	UpdateData(sd, TRUE);
	if (choose_file(sd->hwnd, sd->m_file_source, sizeof(sd->m_file_source), TRUE, title, select))
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

LOCAL void NOINLINE ChangeSource(SHELL_DIALOG *sd)
{
	UpdateData(sd, TRUE);
	add_mru(sd, sd->m_file_source);
	reset_mru(sd);
	UpdateData(sd, FALSE);
	adjust_files(sd);
	adjust_buttons(sd);
	check_output_files(sd);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE ChooseDest(SHELL_DIALOG *sd)
{
	char title[256];
	char select[256];
	
	LoadString(GetInstance(), IDS_CHOOSE_DEST, title, sizeof(title));
	LoadString(GetInstance(), IDS_SELECT_DEST, select, sizeof(select));
	UpdateData(sd, TRUE);
	if (choose_file(sd->hwnd, sd->m_file_dest, sizeof(sd->m_file_dest), FALSE, title, select))
	{
		UpdateData(sd, FALSE);
		adjust_other_files(sd);
		adjust_buttons(sd);
		check_output_files(sd);
	}
}

/*** ---------------------------------------------------------------------- ***/

static BOOL control_pressed(void)
{
	SHORT ks;
	ks = GetKeyState(VK_CONTROL);
	return (ks & 0x8000) != 0;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE EditAny(SHELL_DIALOG *sd, UINT type_id, UINT which_id, const char *filename, char *editor)
{
	char cmd[MAX_PATH * 2 + 3];
	char old_editor[MAX_PATH];
	int ret;
	char title[256];
	char select[256];
	char which[256];
	char type[256];
	
	UpdateData(sd, TRUE);
	if (control_pressed() || *editor == '\0')
	{
		/* Control gedrueckt: 128 = High Order Bit */
		strcpy(cmd, editor);
		strcpy(old_editor, editor);
		
		LoadString(GetInstance(), IDS_CHOOSE_EDITOR, title, sizeof(title));
		LoadString(GetInstance(), which_id, which, sizeof(which));
		strreplace(title, "%s", which);
		LoadString(GetInstance(), IDS_SELECT_PROGRAM, select, sizeof(select));
		if (choose_file(sd->hwnd, cmd, sizeof(cmd), TRUE, title, select))
		{
			strcpy(editor, cmd);
			UpdateData(sd, FALSE);
			if (editor == sd->m_edi_udo)
				set_udo_editor(sd, old_editor);
			adjust_buttons(sd);
		}
		return;
	}

	if (*filename == '\0')
	{
		if (editor == sd->m_edi_udo)
			MessageBoxParam(sd->hwnd, MB_OK | MB_ICONEXCLAMATION, MAKEINTRESOURCE(IDS_NO_SOURCE_SELECTED));
		return;
	}

	if (!file_available(filename))
	{
		LoadString(GetInstance(), type_id, type, sizeof(type));
		ret = MessageBoxParam(sd->hwnd, MB_YESNO | MB_ICONQUESTION, MAKEINTRESOURCE(IDS_FILE_NOT_AVAILABLE), type, filename);
		if (ret != IDYES)
			return;
	}

	change_dir(filename);

	if (strchr(filename, ' ') != NULL)
	{
		sprintf(cmd, "%s \"%s\"", editor, filename);
	} else
	{
		sprintf(cmd, "%s %s", editor, filename);
	}

	StartProgram(sd, cmd, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void EditSource(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_SOURCE, IDS_WHICH_SOURCE, sd->m_file_source, sd->m_edi_udo);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void EditDest(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_DESTINATION, IDS_WHICH_DESTINATION, sd->m_file_dest, sd->m_formatdata[sd->m_format].Dest.Editor);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void EditParam1(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_PARAMETER, IDS_WHICH_PARAMETER, sd->m_file_param1, sd->m_formatdata[sd->m_format].Param1.Editor);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void EditParam2(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_PARAMETER, IDS_WHICH_PARAMETER, sd->m_file_param2, sd->m_formatdata[sd->m_format].Param2.Editor);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void EditFinal(SHELL_DIALOG *sd)
{
	EditAny(sd, IDS_TYPE_RESULT, IDS_WHICH_RESULT, sd->m_file_final, sd->m_formatdata[sd->m_format].Final.Editor);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL int NOINLINE ExecSource(SHELL_DIALOG *sd)
{
	char cmd[MAX_PATH * 3];
	UINT ret;
	int i;
	char title[256];
	char select[256];
	
	UpdateData(sd, TRUE);
	if (control_pressed() || (sd->m_file_source[0] != '\0' && sd->m_app_udo[0] == '\0'
#if UDO_INTEGRATED
		&& sd->m_use_udo != USE_UDO_INT
#endif
		))
	{
		/* Control gedrueckt: 128 = High Order Bit */
		strcpy(cmd, sd->m_app_udo);

		LoadString(GetInstance(), IDS_CHOOSE_UDO, title, sizeof(title));
		LoadString(GetInstance(), IDS_SELECT_PROGRAM, select, sizeof(select));
		if (choose_file(sd->hwnd, cmd, sizeof(cmd), TRUE, title, select))
		{
			strcpy(sd->m_app_udo, cmd);
			UpdateData(sd, FALSE);
			adjust_buttons(sd);
		}
		return -1;
	}

	if (sd->m_file_source[0] == '\0')
	{
		MessageBoxParam(sd->hwnd, MB_OK | MB_ICONEXCLAMATION, MAKEINTRESOURCE(IDS_NO_SOURCE_SELECTED));
		return -1;
	}

	if (sd->m_file_dest[0] == '\0')
	{
		MessageBoxParam(sd->hwnd, MB_OK | MB_ICONEXCLAMATION, MAKEINTRESOURCE(IDS_NO_DEST_SELECTED));
		return -1;
	}

	if (!file_available(sd->m_file_source))
	{
		MessageBoxParam(sd->hwnd, MB_OK | MB_ICONEXCLAMATION, MAKEINTRESOURCE(IDS_SOURCE_NOT_AVAILABLE), sd->m_file_source);
		return -1;
	}

	if (change_dir(sd->m_file_dest) == FALSE)
	{
		if (sd->m_create_dirs)
			ret = IDOK;
		else
			ret = MessageBoxParam(sd->hwnd, MB_OKCANCEL | MB_ICONQUESTION, MAKEINTRESOURCE(IDS_MAKEDIR));

		if (ret == IDOK)
		{
			/* Verzeichnis anlegen */
			if (make_dir(sd->m_file_dest) == FALSE)
			{
				MessageBoxParam(sd->hwnd, MB_OK | MB_ICONSTOP, MAKEINTRESOURCE(IDS_ERR_MAKEDIR));
				return -1;
			}
		} else
		{
			return -1;
		}
	}
	
	if (change_dir(sd->m_file_dest) == FALSE)
	{
		MessageBoxParam(sd->hwnd, MB_OK | MB_ICONSTOP, MAKEINTRESOURCE(IDS_ERR_NODIR));
		return -1;
	}
	
	cursor_working(TRUE);
	
#if UDO_INTEGRATED
	if (sd->m_use_udo == USE_UDO_INT)
	{
		init_udo_vars();
		no_stderr_output = TRUE;
		bNoLogfile = !sd->m_use_log;
		bCheckMisc = sd->m_use_check;
		bNoHypfile = !sd->m_use_hyp;
		bUseTreefile = sd->m_use_tree;
		bUseUPRfile = sd->m_use_upr;
		bNoIdxfile = !sd->m_use_idx;
		bVerbose = sd->m_use_verb;
		/* bHoldKey = sd->m_hold_key; */
		bNoWarnings = !sd->m_warnings;
		bNoIdxfile = !sd->m_use_idx;
		bBeQuiet = sd->m_use_quiet;
		bForceLong = sd->m_force_long;
		bForceShort = sd->m_force_short;
#if USE_KWSET
		bNoFastAutoref = !sd->m_fast_autoref;
#endif
		bTestmode = sd->m_use_test;
		bUseIdMapFileC = sd->m_use_map_c;
		bUseIdMapFilePas = sd->m_use_map_pas;
		bUseIdMapFileVB = sd->m_use_map_vb;
		bUseIdMapFileGFA = sd->m_use_map_gfa;
		for (i = 0; i < MAX_SYM; i++)
		{
			if (sd->m_use_sym[i] && sd->m_symbol[i][0] != '\0')
			{
				add_udosymbol(sd->m_symbol[i]);
			}
		}
		desttype = formatconst[sd->m_format].type;
		strcpy(outfile.full, sd->m_file_dest);
		strcpy(infile.full, sd->m_file_source);
		my_fsplit(infile.full, infile.driv, infile.path, infile.name, infile.suff);
		my_fsplit(outfile.full, outfile.driv, outfile.path, outfile.name, outfile.suff);
		dest_special_adjust();
		Status_Open(sd->hwnd);
		if (udo(infile.full) == FALSE || bErrorDetected || get_error_counter() > 0)
			ret = 1;
		else
			ret = 0;
		exit_udo_vars();
		if (sd->m_hold_key)
			Status_Wait();
		Status_Close();
	} else
#endif
	{
		strcpy(cmd, sd->m_app_udo);
		strcat(cmd, " ");
		strcat(cmd, formatconst[sd->m_format].udo_switch);
		strcat(cmd, " ");
	
		if (!sd->m_use_log) 	strcat(cmd, "-l ");
		if (sd->m_use_check)	strcat(cmd, "--check ");
		if (!sd->m_use_hyp) 	strcat(cmd, "-y ");
		if (sd->m_use_tree) 	strcat(cmd, "--tree ");
		if (sd->m_use_upr)		strcat(cmd, "--save-upr ");
		if (!sd->m_use_idx)		strcat(cmd, "--no-idxfile ");
		if (sd->m_use_verb) 	strcat(cmd, "--verbose ");
		if (sd->m_hold_key) 	strcat(cmd, "--hold ");
		if (!sd->m_warnings)	strcat(cmd, "-W ");
		if (sd->m_use_quiet)	strcat(cmd, "-q ");
		if (sd->m_force_long)	strcat(cmd, "--force-long ");
		if (sd->m_force_short)	strcat(cmd, "--force-short ");
		if (!sd->m_fast_autoref)	strcat(cmd, "--no-fast-auto ");
		if (sd->m_use_test)		strcat(cmd, "--test ");
		
		for (i = 0; i < MAX_SYM; i++)
		{
			if (sd->m_use_sym[i] && sd->m_symbol[i][0] != '\0')
			{
				strcat(cmd, "-D ");
				strcat(cmd, sd->m_symbol[i]);
				strcat(cmd, " ");
			}
		}
	
		if (sd->m_use_map_c)	strcat(cmd, "--map ");
		if (sd->m_use_map_pas)	strcat(cmd, "--map-pas ");
		if (sd->m_use_map_gfa)	strcat(cmd, "--map-gfa ");
		if (sd->m_use_map_vb)	strcat(cmd, "--map-vb ");
	
		/* Kommandozeile noch mit Ziel-/Quelldatei vervollstaendigen */
		strcat(cmd, "-o ");
	
		if (strchr(sd->m_file_dest, ' ') != NULL)
		{
			strcat(cmd, "\"");
			strcat(cmd, sd->m_file_dest);
			strcat(cmd, "\"");
		} else
		{
			strcat(cmd, sd->m_file_dest);
		}
	
		strcat(cmd, " ");
	
		if (strchr(sd->m_file_source, ' ') != NULL)
		{
			strcat(cmd, "\"");
			strcat(cmd, sd->m_file_source);
			strcat(cmd, "\"");
		} else
		{
			strcat(cmd, sd->m_file_source);
		}
		
		ret = StartProgram(sd, cmd, TRUE);
	}
	if (find_application(sd))
		adjust_buttons(sd);
	check_output_files(sd);
	
	cursor_working(FALSE);
	
	return ret;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE ExecAny(SHELL_DIALOG *sd, int type_id, const char *filename, FormatInfo *info)
{
	char cmd[MAX_PATH * 2 + 3];
	char f[MAX_PATH * 2 + 3];
	char type[256];
	
	UpdateData(sd, TRUE);

	if (filename[0] == '\0')
		return;

	if (control_pressed() || info->Application[0] == '\0')
	{
		/* Control gedrueckt: 128 = High Order Bit */
		find_application_for(filename, info->Application);
		Configure_Format(sd, type_id, TRUE);
		return;
	}

	if (!file_available(filename))
	{
		type_id = type_id == 0 ? IDS_TYPE_DESTINATION :
			type_id == 3 ? IDS_TYPE_RESULT :
			IDS_TYPE_PARAMETER;
		LoadString(GetInstance(), type_id, type, sizeof(type));
		MessageBoxParam(sd->hwnd, MB_OK | MB_ICONEXCLAMATION, MAKEINTRESOURCE(IDS_FILE_NOT_AVAILABLE2), type, filename);
		return;
	}

	change_dir(filename);
	strcpy(f, filename);
	if (info->UnixPath)
	{
		backslash2slash(f);
	}

	if (strchr(f, ' ') != NULL)
	{
		sprintf(cmd, "%s %s \"%s\"", info->Application, info->Args, f);
	} else
	{
		sprintf(cmd, "%s %s %s", info->Application, info->Args, f);
	}

	StartProgram(sd, cmd, info->Wait);
	if (find_application(sd))
		adjust_buttons(sd);
	check_output_files(sd);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ExecDest(SHELL_DIALOG *sd)
{
	ExecAny(sd, 0, sd->m_file_dest, &sd->m_formatdata[sd->m_format].Dest);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ExecParam1(SHELL_DIALOG *sd)
{
	ExecAny(sd, 1, sd->m_file_param1, &sd->m_formatdata[sd->m_format].Param1);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ExecParam2(SHELL_DIALOG *sd)
{
	ExecAny(sd, 2, sd->m_file_param2, &sd->m_formatdata[sd->m_format].Param2);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ExecFinal(SHELL_DIALOG *sd)
{
	ExecAny(sd, 3, sd->m_file_final, &sd->m_formatdata[sd->m_format].Final);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void NOINLINE ViewFile(SHELL_DIALOG *sd, const char *filename, UINT type_id)
{
	char cmd[MAX_PATH * 2];
	char type[256];
	
	UpdateData(sd, TRUE);

	if (filename[0] == '\0')
		return;

	if (sd->m_edi_udo[0] == '\0')
	{
		MessageBoxParam(sd->hwnd, MB_OK | MB_ICONEXCLAMATION, MAKEINTRESOURCE(IDS_NO_EDITOR));
		return;
	}

	if (!file_available(filename))
	{
		LoadString(GetInstance(), type_id, type, sizeof(type));
		MessageBoxParam(sd->hwnd, MB_OK | MB_ICONEXCLAMATION, MAKEINTRESOURCE(IDS_FILE_NOT_AVAILABLE2), type, filename);
		return;
	}

	change_dir(filename);
	if (strchr(filename, ' ') != NULL)
	{
		sprintf(cmd, "%s \"%s\"", sd->m_edi_udo, filename);
	} else
	{
		sprintf(cmd, "%s %s", sd->m_edi_udo, filename);
	}
	StartProgram(sd, cmd, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ViewLog(SHELL_DIALOG *sd)
{
	ViewFile(sd, sd->m_file_log, IDS_TYPE_LOG);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ViewHyp(SHELL_DIALOG *sd)
{
	ViewFile(sd, sd->m_file_hyp, IDS_TYPE_HYPHEN);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ViewTree(SHELL_DIALOG *sd)
{
	ViewFile(sd, sd->m_file_tree, IDS_TYPE_TREE);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ViewMapC(SHELL_DIALOG *sd)
{
	ViewFile(sd, sd->m_file_map_c, IDS_TYPE_MAP);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ViewMapPas(SHELL_DIALOG *sd)
{
	ViewFile(sd, sd->m_file_map_pas, IDS_TYPE_MAP);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ViewMapVb(SHELL_DIALOG *sd)
{
	ViewFile(sd, sd->m_file_map_vb, IDS_TYPE_MAP);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ViewMapGfa(SHELL_DIALOG *sd)
{
	ViewFile(sd, sd->m_file_map_gfa, IDS_TYPE_MAP);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ViewUpr(SHELL_DIALOG *sd)
{
	ViewFile(sd, sd->m_file_upr, IDS_TYPE_PROJECT);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL INT_PTR CALLBACK main_dialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SHELL_DIALOG *sd;
	WORD notifyCode;
	int i;
	
#if DBG_MESSAGES
	dbg_message("dlg", message, wParam, lParam);
#endif

	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_INITDIALOG:
		sd = (SHELL_DIALOG *)lParam;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (DWORD_PTR)sd);
		sd->hwnd = hwnd;
		{
			RECT r;
			HWND parent;

			GetWindowRect(hwnd, &r);
			parent = GetParent(hwnd);
			AdjustWindowRect(&r, GetWindowLong(parent, GWL_STYLE), TRUE);
			SetWindowPos(parent, NULL, 0, 0, r.right - r.left, r.bottom - r.top, SWP_NOMOVE | SWP_NOREDRAW | SWP_NOZORDER);
			CenterWindow(parent);
			CenterWindow(hwnd);
		}

		SendDlgItemMessage(hwnd, IDC_FORMAT_COMBO, CB_RESETCONTENT, 0, 0);
		for (i = 0; i < MAXDESTTYPE; i++)
		{ 
			SendDlgItemMessage(hwnd, IDC_FORMAT_COMBO, CB_ADDSTRING, 0, (LPARAM)formatconst[i].name);
		}
		
		reset_mru(sd);
		UpdateData(sd, FALSE);

		if (*sd->m_file_dest == '\0')
			adjust_files(sd);
		else
			adjust_other_files(sd);
		adjust_buttons(sd);
		check_output_files(sd);
		
		ChangeAOT(sd);
		
		return TRUE;

	case WM_CLOSE:
		EndDialog(hwnd, IDCANCEL);
		DestroyWindow(hwnd);
		return TRUE;

	case WM_COMMAND:
		notifyCode = HIWORD(wParam);
		sd = (SHELL_DIALOG *)(DWORD_PTR)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			DestroyWindow(hwnd);
			return TRUE;

		case IDOK:
			break;

		case IDM_OPT_CONFIGURATION:
			Configure_Format(sd, 0, FALSE);
			break;
			
		case IDM_OPT_SETTINGS:
			Configure_Settings(sd);
			break;
		
		case IDC_FILE_SOURCE:
			if (notifyCode == CBN_SELCHANGE)
				ChangeSource(sd);
			break;
				
		case IDC_CHOOSE_SOURCE:
			if (notifyCode == BN_CLICKED)
				ChooseSource(sd);
			break;

		case IDC_CHOOSE_DEST:
			if (notifyCode == BN_CLICKED)
				ChooseDest(sd);
			break;

		case IDC_EDIT_SOURCE:
			if (notifyCode == BN_CLICKED)
				EditSource(sd);
			break;

		case IDC_EDIT_DEST:
			if (notifyCode == BN_CLICKED)
				EditDest(sd);
			break;

		case IDC_EDIT_PARAM1:
			if (notifyCode == BN_CLICKED)
				EditParam1(sd);
			break;

		case IDC_EDIT_PARAM2:
			if (notifyCode == BN_CLICKED)
				EditParam2(sd);
			break;

		case IDC_EDIT_FINAL:
			if (notifyCode == BN_CLICKED)
				EditFinal(sd);
			break;

		case IDC_EXEC_SOURCE:
			if (notifyCode == BN_CLICKED)
				ExecSource(sd);
			break;

		case IDC_EXEC_DEST:
			if (notifyCode == BN_CLICKED)
				ExecDest(sd);
			break;

		case IDC_EXEC_PARAM1:
			if (notifyCode == BN_CLICKED)
				ExecParam1(sd);
			break;

		case IDC_EXEC_PARAM2:
			if (notifyCode == BN_CLICKED)
				ExecParam2(sd);
			break;

		case IDC_EXEC_FINAL:
			if (notifyCode == BN_CLICKED)
				ExecFinal(sd);
			break;

		case IDC_BUTTON_LOG:
			if (notifyCode == BN_CLICKED)
				ViewLog(sd);
			break;

		case IDC_BUTTON_HYP:
			if (notifyCode == BN_CLICKED)
				ViewHyp(sd);
			break;

		case IDC_BUTTON_TREE:
			if (notifyCode == BN_CLICKED)
				ViewTree(sd);
			break;

		case IDC_BUTTON_MAP_C:
			if (notifyCode == BN_CLICKED)
				ViewMapC(sd);
			break;

		case IDC_BUTTON_MAP_PAS:
			if (notifyCode == BN_CLICKED)
				ViewMapPas(sd);
			break;

		case IDC_BUTTON_MAP_VB:
			if (notifyCode == BN_CLICKED)
				ViewMapVb(sd);
			break;

		case IDC_BUTTON_MAP_GFA:
			if (notifyCode == BN_CLICKED)
				ViewMapGfa(sd);
			break;

		case IDC_BUTTON_UPR:
			if (notifyCode == BN_CLICKED)
				ViewUpr(sd);
			break;

		case IDC_CHECK_DIR:
		case IDC_CHECK_FORCE_LONG:
		case IDC_CHECK_FORCE_SHORT:
			if (notifyCode == BN_CLICKED)
			{
				adjust_files(sd);
				adjust_buttons(sd);
				check_output_files(sd);
			}
			break;
		
		case IDC_CHECK_FAST_AUTOREF:
			if (notifyCode == BN_CLICKED)
			{
			}
			break;
		
		case IDC_FORMAT_COMBO:
			if (notifyCode == CBN_SELENDOK)
			{
				adjust_files(sd);
				adjust_buttons(sd);
				check_output_files(sd);
			}
			break;
		}
		break;
	}
	return FALSE;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL SHELL_DIALOG *NOINLINE ShellDialog_New(void)
{
	SHELL_DIALOG *sd;
	int i;

	sd = (SHELL_DIALOG *)malloc(sizeof(*sd));
	if (sd != NULL)
	{
		memset(sd, 0, sizeof(*sd));
		
		sd->m_use_test = FALSE;
		sd->m_use_verb = FALSE;
		sd->m_hold_key = FALSE;
		sd->m_warnings = TRUE;
		sd->m_use_check = FALSE;
		sd->m_use_dir = FALSE;
		sd->m_use_quiet = FALSE;
		sd->m_force_long = FALSE;
		sd->m_force_short = FALSE;
		sd->m_fast_autoref = TRUE;
		
		sd->m_use_log = TRUE;
		sd->m_use_hyp = TRUE;
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
			sd->m_symbol[i][0] = '\0';
		}
		
		sd->m_file_source[0] = '\0';
		sd->m_file_dest[0] = '\0';
		sd->m_file_param1[0] = '\0';
		sd->m_file_param2[0] = '\0';
		sd->m_file_final[0] = '\0';
		sd->m_format = -1;

		sd->mru_list = NULL;
		sd->n_mru = 0;
		sd->max_mru = 0;
		
		sd->m_file_log[0] = '\0';
		sd->m_file_hyp[0] = '\0';
		sd->m_file_tree[0] = '\0';
		sd->m_file_map_c[0] = '\0';
		sd->m_file_map_pas[0] = '\0';
		sd->m_file_map_vb[0] = '\0';
		sd->m_file_map_gfa[0] = '\0';
		sd->m_file_upr[0] = '\0';

		strcpy(sd->m_app_udo, "udo.exe");
		sd->m_edi_udo[0] = '\0';
		switch (PRIMARYLANGID(GetUserDefaultUILanguage()))
		{
		case LANG_GERMAN:
			strcpy(sd->udosh_helpfile, "udoshde.chm");
			snprintf(sd->udo_helpfile, sizeof(sd->udo_helpfile), "udo%sde.chm", UDO_REL);
			strcpy(sd->udo_help_commands, "Befehlsindex");
			break;
		default:
			strcpy(sd->udosh_helpfile, "udoshen.chm");
			snprintf(sd->udo_helpfile, sizeof(sd->udo_helpfile), "udo%sen.chm", UDO_REL);
			strcpy(sd->udo_help_commands, "Command Index");
			break;
		}
		LoadString(GetInstance(), IDS_UDO_HELPFILE, sd->udo_helpfile, sizeof(sd->udo_helpfile));
		LoadString(GetInstance(), IDS_UDO_HELP_COMMANDS, sd->udo_help_commands, sizeof(sd->udo_help_commands));
		sd->m_use_udo = UDO_INTEGRATED ? USE_UDO_INT : USE_UDO_APP;
		
#define InitFormatInfo(fi, wait) \
		(fi)->Application[0] = '\0'; \
		(fi)->Args[0] = '\0'; \
		(fi)->Editor[0] = '\0'; \
		(fi)->Suffix[0] = '\0'; \
		(fi)->LowerCase = FALSE; \
		(fi)->UnixPath = FALSE; \
		(fi)->Wait = wait

		for (i = 0; i < MAXDESTTYPE; i++)
		{
			InitFormatInfo(&sd->m_formatdata[i].Dest, FALSE);
			InitFormatInfo(&sd->m_formatdata[i].Param1, TRUE);
			InitFormatInfo(&sd->m_formatdata[i].Param2, TRUE);
			InitFormatInfo(&sd->m_formatdata[i].Final, FALSE);
		}
#undef InitFormatInfo

		sd->m_inifilename[0] = '\0';
		sd->hwnd = NULL;
	}

	return sd;
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void NOINLINE ShellDialog_Delete(SHELL_DIALOG *sd)
{
	int i;
	
	if (sd != NULL)
	{
		if (sd->mru_list != NULL)
		{
			for (i = 0; i < sd->n_mru; i++)
				free(sd->mru_list[i]);
			free(sd->mru_list);
		}
		free(sd);
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL LRESULT CALLBACK mainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SHELL_DIALOG *sd;
	
#if DBG_MESSAGES
	dbg_message("main", message, wParam, lParam);
#endif
	switch (message)
	{
	case WM_CREATE:
		{
			HMENU menu;
			char strAbout[100];

			menu = GetSystemMenu(hwnd, FALSE);
			if (LoadString(NULL, IDS_ABOUTBOX, strAbout, sizeof(strAbout)) != 0)
			{
				AppendMenu(menu, MF_SEPARATOR, 0, 0);
				AppendMenu(menu, MF_STRING, IDM_ABOUTBOX, strAbout);
			}
			EnableMenuItem(menu, SC_MAXIMIZE, MF_GRAYED);
			EnableMenuItem(menu, SC_SIZE, MF_GRAYED);
		}
		/* CenterWindow(hwnd); */
		sd = (SHELL_DIALOG *)(((CREATESTRUCT *)lParam)->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (DWORD_PTR)sd);
		sd->mainHwnd = hwnd;
		break;

	case WM_COMMAND:
		sd = (SHELL_DIALOG *)(DWORD_PTR)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		switch (LOWORD(wParam))
		{
		case IDM_FILE_OPEN:
			PostMessage(GetWindow(hwnd, GW_CHILD), WM_COMMAND, MAKEWPARAM(IDC_CHOOSE_SOURCE, BN_CLICKED), 0);
			break;

		case IDM_FILE_SAVE:
			PostMessage(GetWindow(hwnd, GW_CHILD), WM_COMMAND, MAKEWPARAM(IDC_CHOOSE_DEST, BN_CLICKED), 0);
			break;

		case IDM_APP_EXIT:
			DestroyWindow(hwnd);
			return TRUE;

		case IDM_OPT_CONFIGURATION:
			PostMessage(GetWindow(hwnd, GW_CHILD), WM_COMMAND, MAKEWPARAM(IDM_OPT_CONFIGURATION, 0), 0);
			break;
		
		case IDM_OPT_SETTINGS:
			PostMessage(GetWindow(hwnd, GW_CHILD), WM_COMMAND, MAKEWPARAM(IDM_OPT_SETTINGS, 0), 0);
			break;
		
		case IDM_HELP_CONTENTS:
			Help_Contents(hwnd, sd->udosh_helpfile);
			break;

		case IDM_HELP_INDEX:
			Help_Index(hwnd, sd->udosh_helpfile);
			break;

		case IDM_HELP_UDO:
			Help_Contents(hwnd, sd->udo_helpfile);
			break;

		case IDM_HELP_UDO_INDEX:
			Help_Show(hwnd, sd->udo_helpfile, sd->udo_help_commands);
			break;

		case IDM_HELP_ABOUT:
			About(hwnd);
			break;
		}
		break;

	case WM_CLOSE:
		sd = (SHELL_DIALOG *)(DWORD_PTR)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		DestroyWindow(sd->hwnd);
		DestroyWindow(hwnd);
		return TRUE;

	case WM_DESTROY:
		PostQuitMessage(0);
		return FALSE;

	case WM_NCDESTROY:
		break;

	case WM_PARENTNOTIFY:
		switch (LOWORD(wParam))
		{
		case WM_DESTROY:
			DestroyWindow(hwnd);
			break;
		}
		break;

	case WM_SYSCOMMAND:
		switch (LOWORD(wParam) & 0xfff0)
		{
		case IDM_ABOUTBOX:
			About(hwnd);
			break;
		}
		break;

	case WM_SETFOCUS:
		PostMessage(GetWindow(hwnd, GW_CHILD), WM_SETFOCUS, (WPARAM)hwnd, 0);
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void NOINLINE ParseCommandLine(SHELL_DIALOG *sd, const char *lpszCmdLine)
{
	size_t sl;
	
	if (lpszCmdLine != NULL && *lpszCmdLine != '\0')
	{
		strcpy(sd->m_file_source, lpszCmdLine);
		if (sd->m_file_source[0] == '"')
		{
			strcpy(sd->m_file_source, sd->m_file_source + 1);
			sl = strlen(sd->m_file_source);
			if (sl > 0 && sd->m_file_source[sl - 1] == '"')
				sd->m_file_source[sl - 1] = '\0';
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int cmdShow)
{
	MSG MainMsg;
	HMENU menu;
	SHELL_DIALOG *sd;
	char title[256];
	
	UNUSED(hPrevInstance);
	UNUSED(cmdShow);

#if DBG_MESSAGES
	dbg_message_open();
#endif

	if (!hPrevInstance)
	{
		WNDCLASS wndclass;

		wndclass.style = CS_BYTEALIGNCLIENT | CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wndclass.lpfnWndProc = mainWndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;
		wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH) (COLOR_APPWORKSPACE + 1);
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = "udosh";

		RegisterClass(&wndclass);
#if UDO_INTEGRATED
		Status_Init();
#endif
	}

	sd = ShellDialog_New();

	if (sd != NULL)
	{
		sd->haccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCEL));
		
		menu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MAIN_MENU));
		
		LoadString(hInstance, IDS_WINDOW_TITLE, title, sizeof(title));
		sd->mainHwnd = CreateWindowEx(
			WS_EX_DLGMODALFRAME,
			"udosh",
			title,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			0, /* parent */
			menu, /* menu */
			hInstance,
			(LPVOID)sd);
	
		ReadProfile(sd);
		ParseCommandLine(sd, lpszCmdLine);
		add_mru(sd, sd->m_file_source);
		CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_MAIN_DIALOG), sd->mainHwnd, main_dialog, (LPARAM) sd);

		if (sd->hwnd == NULL)
		{
			ShowWindowsError(NULL, NULL);
		} else
		{
			ShowWindow(sd->mainHwnd, cmdShow);

			UpdateWindow(sd->hwnd);

			while (GetMessage(&MainMsg, NULL, 0, 0))
			{
				if (sd->haccel == NULL || !TranslateAccelerator(sd->mainHwnd, sd->haccel, &MainMsg))
				{
					if (!IsDialogMessage(sd->hwnd, &MainMsg))
					{
						TranslateMessage(&MainMsg);
						DispatchMessage(&MainMsg);
					}
				}
			}
		}
		WriteProfile(sd);
		Help_Exit();
		DestroyWindow(sd->mainHwnd);
		ShellDialog_Delete(sd);
	}

#if DBG_MESSAGES
	dbg_message_close();
#endif

	if (!hPrevInstance)
	{
#if UDO_INTEGRATED
		Status_Exit();
#endif
		UnregisterClass("udosh", hInstance);
	}
	
	return 0;
}
