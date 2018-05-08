/*****************************************************************************
 * HELP.C
 *****************************************************************************/

#include "udosh.h"
#include "help.h"
#include <stdlib.h>
#include <string.h>


#ifdef HELP_SUPPORT_CHM
#include "htmlhelp.h"

typedef HWND (WINAPI *HTMLHELP_TYPE)(HWND, LPCTSTR, UINT, DWORD_PTR);
LOCAL HINSTANCE hhctrl;
LOCAL HTMLHELP_TYPE p_htmlhelp;
LOCAL DWORD htmlhelpCookie;
#endif

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

#ifdef HELP_SUPPORT_CHM

LOCAL void exit_htmlhelp(void)
{
	if (hhctrl != NULL && hhctrl != (HINSTANCE)-1)
	{
		(*p_htmlhelp)(NULL, NULL, HH_UNINITIALIZE, (DWORD_PTR) htmlhelpCookie);
		FreeLibrary(hhctrl);
		hhctrl = NULL;
		p_htmlhelp = 0;
	}
}

/*** ---------------------------------------------------------------------- ***/

LOCAL int have_htmlhelp(void)
{
	if (p_htmlhelp != 0)
		return TRUE;
	if (hhctrl == NULL)
	{
		UINT old_error_mode;
		
		old_error_mode = SetErrorMode(SEM_NOOPENFILEERRORBOX);
		
		hhctrl = LoadLibrary("HHCTRL.OCX");
		if (hhctrl == NULL)
			hhctrl = (HINSTANCE) -1;
		SetErrorMode(old_error_mode);
	}
	if (hhctrl == (HINSTANCE)-1)
		return FALSE;
#ifdef _UNICODE
	p_htmlhelp = (HTMLHELP_TYPE)GetProcAddress(hhctrl, "HtmlHelpW");
#else
	p_htmlhelp = (HTMLHELP_TYPE)GetProcAddress(hhctrl, "HtmlHelpA");
#endif
	if (p_htmlhelp == NULL)
	{
		FreeLibrary(hhctrl);
		hhctrl = (HINSTANCE)-1;
		return FALSE;
	}
	
	(*p_htmlhelp)(NULL, NULL, HH_INITIALIZE, (DWORD_PTR) &htmlhelpCookie);

	return TRUE;
}

#endif /* HELP_SUPPORT_CHM */

/*** ---------------------------------------------------------------------- ***/

LOCAL int file_found(char *filename)
{
	HANDLE h;
	char path[MAX_PATH];
	char *p;
	
	h = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h != INVALID_HANDLE_VALUE)
	{
		CloseHandle(h);
		return TRUE;
	}
	GetModuleFileName(GetInstance(), path, sizeof(path));
	p = strrchr(path, '\\');
	if (p == NULL)
		p = strrchr(path, '/');
	if (p == NULL)
		p = path;
	else
		++p;
	strcpy(p, filename);
	h = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h != INVALID_HANDLE_VALUE)
	{
		CloseHandle(h);
		strcpy(filename, path);
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

GLOBAL BOOL Help_Show(HWND parent, const char *filename, const char *entry)
{
	BOOL found;
	char *my_help_name;
	char *p;
	int type;
	
	if ((my_help_name = (char *)malloc(MAX_PATH)) == NULL)
		return FALSE;
	type = -1;

	strcpy(my_help_name, filename);
	found = file_found(my_help_name);
	p = strrchr(my_help_name, '.');
	if (found)
	{
		if (p != NULL)
		{
			if (stricmp(p, ".hlp") == 0)
				type = 0;
#ifdef HELP_SUPPORT_CHM
			if (stricmp(p, ".chm") == 0 && have_htmlhelp())
				type = 1;
#endif
		}
	}
	
	if (p == NULL)
		p = my_help_name + strlen(my_help_name);
	if (!found)
	{
		strcpy(p, ".hlp");
		if (file_found(my_help_name))
		{
			found = TRUE;
			type = 0;
		}
	}
#ifdef HELP_SUPPORT_CHM
	if (!found)
	{
		strcpy(p, ".chm");
		if (file_found(my_help_name))
		{
			found = TRUE;
			if (have_htmlhelp())
				type = 1;
		}
	}
#endif

	if (found && type == 0)
	{
		if (entry == NULL)
		{
			WinHelp(parent, my_help_name, HELP_PARTIALKEY, (DWORD_PTR) "");
		} else if (IS_INTRESOURCE(entry))
		{
			WinHelp(parent, my_help_name, HELP_CONTEXT, (DWORD_PTR) entry);
		} else if (strcmp(entry, "$Contents") == 0)
		{
			WinHelp(parent, my_help_name, HELP_CONTEXT, (DWORD_PTR) "UDOTOC");
		} else if (strcmp(entry, "$Index") == 0)
		{
			WinHelp(parent, my_help_name, HELP_PARTIALKEY, (DWORD_PTR) "");
		} else if (strcmp(entry, "$Help") == 0)
		{
			WinHelp(parent, my_help_name, HELP_HELPONHELP, 0);
		} else
		{
			WinHelp(parent, my_help_name, HELP_KEY, (DWORD_PTR) entry);
		}
	}

#ifdef HELP_SUPPORT_CHM
	if (found && type == 1)
	{
		/* DWORD dwCookie; */
		HWND help_hwnd;
		
		/* (*htmlhelp_addr)(NULL, NULL, HH_INITIALIZE, (DWORD_PTR) &dwCookie); */
		if (entry == NULL)
		{
			help_hwnd = (*p_htmlhelp)(parent, my_help_name, HH_DISPLAY_INDEX, (DWORD_PTR) "");
		} else if (strcmp(entry, "$Contents") == 0)
		{
			help_hwnd = (*p_htmlhelp)(parent, my_help_name, HH_DISPLAY_TOC, (DWORD_PTR) NULL);
		} else if (strcmp(entry, "$Index") == 0)
		{
			help_hwnd = (*p_htmlhelp)(parent, my_help_name, HH_DISPLAY_INDEX, (DWORD_PTR) "");
		} else if (strcmp(entry, "$Help") == 0)
		{
			help_hwnd = (*p_htmlhelp)(parent, my_help_name, HH_DISPLAY_TOC, (DWORD_PTR) NULL);
		} else
		{
			HH_AKLINK link;
			
			memset(&link, 0, sizeof(link));
			link.cbStruct = sizeof(link);
			link.fReserved = FALSE;
			link.pszKeywords = entry;
			link.pszUrl = NULL;
			link.pszMsgText = NULL;
			link.pszMsgTitle = NULL;
			link.pszWindow = NULL;
			link.fIndexOnFail = TRUE;
			/* (*p_htmlhelp)(parent, my_help_name, HH_DISPLAY_TOPIC, (DWORD_PTR) NULL); */
			help_hwnd = (*p_htmlhelp)(parent, my_help_name, HH_KEYWORD_LOOKUP, (DWORD_PTR) &link);
			/* help_hwnd = (*p_htmlhelp)(parent, my_help_name, HH_DISPLAY_TOC, (DWORD_PTR) entry); */
		}
		if (help_hwnd != NULL)
		{
#if 0
			MSG msg;
			
			while (GetMessage(&msg, NULL, 0, 0))
			{
				if (!(*p_htmlhelp)(NULL, NULL, HH_PRETRANSLATEMESSAGE, (DWORD_PTR) &msg))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				if (!IsWindow(help_hwnd))
					break;
			}
#endif
		}
	}
#endif /* HELP_SUPPORT_CHM */
	free(my_help_name);
	if (!found)
	{
		MessageBox(parent, "No help file found", NULL, MB_ICONERROR | MB_OK);
	}
	return found;
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Help_Index(HWND parent, const char *filename)
{
	Help_Show(parent, filename, "$Index");
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Help_Contents(HWND parent, const char *filename)
{
	Help_Show(parent, filename, "$Contents");
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Help_Using_Help(HWND parent, const char *filename)
{
	Help_Show(parent, filename, "$Help");
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Help_Exit(void)
{
#ifdef HELP_SUPPORT_CHM
	exit_htmlhelp();
#endif
}
