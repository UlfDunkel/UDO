#include "udosh.h"
#include <commdlg.h>
#include <cderr.h>
#include <stdio.h>
#include "misc.h"

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

GLOBAL int MessageBoxParam(HWND parent, UINT style, const char *format, ...)
{
	char str[2048];
	va_list args;
	char format_buf[1024];
	
	va_start(args, format);
	if (IS_INTRESOURCE(format))
	{
		LoadString(GetInstance(), (UINT)((ULONG_PTR)(format) & 0xffff), format_buf, sizeof(format_buf));
		format = format_buf;
	}
	vsprintf(str, format, args);
	va_end(args);
	return MessageBox(parent, str, NULL, style);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

GLOBAL void CenterWindow(HWND hwnd)
{
	RECT r;
	RECT p;
	RECT mainrect;
	HWND parent;
	
	parent = GetParent(hwnd);
	GetWindowRect(hwnd, &r);
	if (parent == NULL)
	{
		p.left = 0;
		p.top = 0;
		p.right = GetSystemMetrics(SM_CXFULLSCREEN);
		p.bottom = GetSystemMetrics(SM_CYFULLSCREEN);
		mainrect = p;
	} else
	{
		GetClientRect(parent, &p);
		GetWindowRect(parent, &mainrect);
	}
	if (GetWindowLong(hwnd, GWL_STYLE) & WS_CHILD)
		SetWindowPos(hwnd, NULL, p.left + ((p.right - p.left) - (r.right - r.left)) / 2, p.top + ((p.bottom - p.top) - (r.bottom - r.top)) / 2, r.right - r.left, r.bottom - r.top, SWP_NOSIZE | SWP_NOREDRAW | SWP_NOZORDER);
	else
		SetWindowPos(hwnd, NULL, mainrect.left + ((p.right - p.left) - (r.right - r.left)) / 2, mainrect.top + ((p.bottom - p.top) - (r.bottom - r.top)) / 2, r.right - r.left, r.bottom - r.top, SWP_NOSIZE | SWP_NOREDRAW | SWP_NOZORDER);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

GLOBAL void DlgGetText(HWND hwnd, int id, char *buf, int maxlen)
{
	int len;

	len = GetDlgItemText(hwnd, id, buf, maxlen - 1);
	buf[len] = '\0';
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void DlgSetText(HWND hwnd, int id, char *buf)
{
	SetDlgItemText(hwnd, id, buf);
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL BOOL DlgGetButton(HWND hwnd, int id)
{
	return IsDlgButtonChecked(hwnd, id) == BST_CHECKED;
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void DlgSetButton(HWND hwnd, int id, BOOL check)
{
	CheckDlgButton(hwnd, id, check ? BST_CHECKED : BST_UNCHECKED);
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void DlgEnable(HWND hwnd, int id, BOOL enable)
{
	EnableWindow(GetDlgItem(hwnd, id), enable);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

GLOBAL void my_fsplit(const char *cs, char *drive, char *path, char *filename, char *suffix)
{
	char wrk[MAX_PATH];
	char *p;
	
	strncpy(wrk, cs, sizeof(wrk) - 1);
	wrk[sizeof(wrk) - 1] = '\0';
	
	/* Drive ermitteln und abschneiden */
	if (wrk[0] != '\0' && wrk[1] == ':' )
	{
		strcpy(drive, "a:");
		drive[0] = wrk[0];
		memmove(wrk, wrk + 2, strlen(wrk + 2) + 1);
	} else
	{
		*drive = '\0';
	}

	/* Filenamen ermitteln und abschneiden */
	strcpy(filename, wrk);
	p = strrchr(wrk, '\\');
	if (p == NULL)
		p = strrchr(wrk, '/');
	if (p != NULL)
	{
		strcpy(filename, p + 1);
		p[1] = '\0';
		strcpy(path, wrk);
	} else
	{
		strcpy(filename, wrk);
		*path = '\0';
	}

	/* Jetzt noch aus dem Filenamen den Suffix extrahieren */
	if ((p = strrchr(filename, '.')) != NULL)
	{
		strcpy(suffix, p);
		*p = '\0';
	} else
	{
		*suffix = '\0';
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL int choose_file(HWND parent, char *name, size_t maxSize, BOOL must_exist, const char *title, const char *filter)
{
	DWORD dw;
	OPENFILENAME ofn;
	char fdriv[MAX_PATH];
	char fpath[MAX_PATH];
	char fname[MAX_PATH];
	char fsuff[MAX_PATH];

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = parent;
	ofn.hInstance = GetInstance();
	ofn.lpstrFilter = filter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter = 0;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = fname;
	ofn.nMaxFile = maxSize;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = title;
	ofn.Flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	if (must_exist)
		ofn.Flags |= OFN_FILEMUSTEXIST;
	ofn.nFileOffset = 0;
	ofn.nFileExtension = 0;
	ofn.lpstrDefExt = 0;
	ofn.lCustData = 0;
	ofn.lpfnHook = NULL;
	ofn.lpTemplateName = NULL;

	my_fsplit(name, fdriv, fpath, fname, fsuff);
	strcat(fname, fsuff);
	if (name[0] != '\0')
	{
		sprintf(fsuff, "%s%s", fdriv, fpath);
		strcpy(fpath, fsuff);
		ofn.lpstrInitialDir = fpath;
	}

	if (GetOpenFileName(&ofn))
	{
		strcpy(name, ofn.lpstrFile);
		return TRUE;
	}

	dw = CommDlgExtendedError();
#ifdef OPENFILENAME_SIZE_VERSION_400
	if (dw == CDERR_STRUCTSIZE)
	{
		ofn.lStructSize = OPENFILENAME_SIZE_VERSION_400;
		if (GetOpenFileName(&ofn))
		{
			strcpy(name, ofn.lpstrFile);
			return TRUE;
		}
	
		dw = CommDlgExtendedError();
	}
#endif

	if (dw != 0)
	{
		char buf[100];
		
		sprintf(buf, "CommDlgExtendedError: %lu $%lx", dw, dw);
		MessageBox(parent, buf, NULL, MB_OK | MB_ICONSTOP);
	}

	return FALSE;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

GLOBAL BOOL strreplace(char *source, const char *replace, const char *by)
{
	char 	*found;
	size_t	rlen, blen, flen;
	
	if (replace[0] == '\0')
		return FALSE;
	
	if ((found = strstr(source, replace)) == NULL)
		return FALSE;

	rlen = strlen(replace);
	flen = strlen(found);

	/* Zu Ersetzendes entfernen */
	memmove(found, found + rlen, flen - rlen + 1);

	/* Platz schaffen fuer neues und dorthin kopieren */
	if (by != NULL && by[0] != '\0')
	{
		blen = strlen(by);
		flen -= rlen;
		memmove(found + blen, found, flen + 1);
		memcpy(found, by, blen);
	}
	
	return TRUE;
}
