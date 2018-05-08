#include "udosh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <import.h>
#include <constant.h>
#include <file.h>
#include <msg.h>
#include <udo.h>
#include <export.h>
#include <gui.h>
#include "guish.h"
#include "misc.h"
#include "resource.rh"

LOCAL int last_percent;
LOCAL HWND statusHwnd;

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

GLOBAL void show_status_info(const char *s)
{
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		if (s != NULL && *s != '\0' && statusHwnd != NULL)
		{
			SetDlgItemText(statusHwnd, IDC_STATUS_INFO, s);
			UpdateWindow(GetDlgItem(statusHwnd, IDC_STATUS_INFO));
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void show_status_loginfo(const char *s)
{
	_BOOL flag = FALSE;

	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		flag = TRUE;
	}
	if (!flag || !bNoLogfile)
	{
		logln(s);
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void show_status_pass(const char *s)
{
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		if (s != NULL && *s != '\0')
		{
			SetDlgItemText(statusHwnd, IDC_STATUS_PASS, s);
			UpdateWindow(GetDlgItem(statusHwnd, IDC_STATUS_PASS));
			show_status_info(" ");
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void show_status_udo2udo(FILE_LINENO Pass2Lines, const char *s)
{
	show_status_file_2(Pass2Lines, s);
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void show_status_node(const char *numbers, const char *name)
{
	UNUSED(numbers);
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		if (name != NULL && *name != '\0')
		{
			SetDlgItemText(statusHwnd, IDC_STATUS_NODE, name);
			UpdateWindow(GetDlgItem(statusHwnd, IDC_STATUS_NODE));
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void show_status_file_1(FILE_LINENO Pass1Lines, const char *s)
{
	UNUSED(Pass1Lines);
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		if (s != NULL && *s != '\0')
		{
			SetDlgItemText(statusHwnd, IDC_STATUS_FILE, s);
			UpdateWindow(GetDlgItem(statusHwnd, IDC_STATUS_FILE));
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void show_status_file_2(FILE_LINENO Pass2Lines, const char *s)
{
	show_status_file_1(Pass2Lines, s);
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void show_status_percent(FILE_LINENO Pass1Lines, FILE_LINENO Pass2Lines)
{
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		Status_SetRange(0, Pass1Lines);
		Status_SetPos(Pass2Lines);
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void show_status_errors(const char *s)
{
	UNUSED(s);
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void show_logln_message(const char *s)
{
	/* Dummy-Routine */
	UNUSED(s);
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void warning_err_logfile(void)
{
	error_open_logfile(file_lookup(sLogfull));
	MessageBoxParam(statusHwnd, MB_ICONERROR | MB_OK, MAKEINTRESOURCE(IDS_ERR_CREATE_LOG));
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void warning_err_treefile(void)
{
	error_open_treefile(file_lookup(sTreefull));
	MessageBoxParam(statusHwnd, MB_ICONERROR | MB_OK, MAKEINTRESOURCE(IDS_ERR_CREATE_TREE));
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void warning_err_uprfile(void)
{
	error_open_uprfile(file_lookup(sUPRfull));
	MessageBoxParam(statusHwnd, MB_ICONERROR | MB_OK, MAKEINTRESOURCE(IDS_ERR_CREATE_UPR));
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void warning_err_hypfile(void)
{
	error_open_hypfile(file_lookup(sHypfull));
	MessageBoxParam(statusHwnd, MB_ICONERROR | MB_OK, MAKEINTRESOURCE(IDS_ERR_CREATE_HYPHEN));
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void warning_err_destination(void)
{
	MessageBoxParam(statusHwnd, MB_ICONERROR | MB_OK, MAKEINTRESOURCE(IDS_ERR_CREATE_OUTPUT));
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void multitasking_interrupt(void)
{
	MSG msg;
	
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (!IsWindow(statusHwnd) || !IsDialogMessage(statusHwnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void unregistered_copyright(void)
{
	/* Dummy-Funktion */
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL _BOOL break_action(void)
{
	if (!IsWindow(statusHwnd))
	{
		bBreakHappened = TRUE;
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void ProgressSetRange(HWND hwnd, LONG minVal, LONG maxVal)
{
	if (maxVal < minVal)
		maxVal = minVal;
	SetWindowLong(hwnd, 0, minVal);
	SetWindowLong(hwnd, sizeof(LONG), maxVal);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ProgressGetRange(HWND hwnd, LONG *minVal, LONG *maxVal)
{
	*minVal = GetWindowLong(hwnd, 0);
	*maxVal = GetWindowLong(hwnd, sizeof(LONG));
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ProgressSetPos(HWND hwnd, LONG pos)
{
	SetWindowLong(hwnd, 2 * sizeof(LONG), pos);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ProgressGetPos(HWND hwnd, LONG *pos)
{
	*pos = GetWindowLong(hwnd, 2 * sizeof(LONG));
}

/*** ---------------------------------------------------------------------- ***/

LOCAL LRESULT CALLBACK progress_wndproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		ProgressSetRange(hwnd, 0, 1);
		ProgressSetPos(hwnd, 0);
		break;
	
	case WM_ERASEBKGND:
		return 0;
	
	case WM_PAINT:
		{
			HDC hdc;
			PAINTSTRUCT ps;
			RECT r;
			HBRUSH brush, oldBrush;
			LONG pos, minVal, maxVal;
			
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &r);
			ProgressGetRange(hwnd, &minVal, &maxVal);
			ProgressGetPos(hwnd, &pos);
			if (pos < minVal)
				pos = minVal;
			else if (pos > maxVal)
				pos = maxVal;
			if (maxVal != minVal)
				r.right = r.left + ((r.right - r.left) * (pos - minVal)) / (maxVal - minVal);
			brush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = SelectObject(hdc, brush);
			FillRect(hdc, &r, brush);
			DeleteObject(SelectObject(hdc, oldBrush));
			EndPaint(hwnd, &ps);
		}
		break;
	}
	
	return DefWindowProc(hwnd, message, wParam, lParam);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL INT_PTR CALLBACK status_dialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char cancel[128];
	
	UNUSED(wParam);
	UNUSED(lParam);
	
	switch (message)
	{
	case WM_CREATE:
		break;
	
	case WM_COMMAND:
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
		}
		break;
		
	case WM_INITDIALOG:
		CenterWindow(hwnd);
		SetDlgItemText(hwnd, IDC_STATUS_PASS, "");
		SetDlgItemText(hwnd, IDC_STATUS_INFO, "");
		SetDlgItemText(hwnd, IDC_STATUS_FILE, "");
		SetDlgItemText(hwnd, IDC_STATUS_NODE, "");
		LoadString(GetInstance(), IDS_CANCEL, cancel, sizeof(cancel));
		SetDlgItemText(hwnd, IDCANCEL, cancel);
		last_percent = -1;
		return TRUE;

	case WM_CLOSE:
		EndDialog(hwnd, IDCANCEL);
		DestroyWindow(hwnd);
		return TRUE;

	case WM_DESTROY:
		statusHwnd = NULL;
		break;
	}
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Status_Open(HWND parent)
{
	statusHwnd = CreateDialog(GetInstance(), MAKEINTRESOURCE(IDD_STATUS_DIALOG), parent, status_dialog);
	ShowWindow(statusHwnd, SW_SHOW);
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Status_Wait(void)
{
	MSG msg;
	char ok[128];
	
	if (statusHwnd != NULL)
	{
		LoadString(GetInstance(), IDS_OK, ok, sizeof(ok));
		SetDlgItemText(statusHwnd, IDCANCEL, ok);
		while (IsWindow(statusHwnd) && GetMessage(&msg, NULL, 0, 0))
		{
			if (!IsDialogMessage(statusHwnd, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Status_Close(void)
{
	if (statusHwnd != NULL)
	{
		DestroyWindow(statusHwnd);
		statusHwnd = NULL;
	}
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL BOOL Status_Init(void)
{
	WNDCLASS wndclass;
	
	wndclass.style = CS_PARENTDC;
	wndclass.lpfnWndProc = progress_wndproc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 3 * sizeof(LONG);
	wndclass.hInstance = GetInstance();
	wndclass.hIcon = NULL;
	wndclass.hCursor = NULL;
	wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = MY_PROGRESS_CONTROL;
	RegisterClass(&wndclass);
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Status_Exit(void)
{
	UnregisterClass(MY_PROGRESS_CONTROL, GetInstance());
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Status_SetRange(LONG minVal, LONG maxVal)
{
	ProgressSetRange(GetDlgItem(statusHwnd, IDC_STATUS_PROGRESS), minVal, maxVal);
}

/*** ---------------------------------------------------------------------- ***/

GLOBAL void Status_SetPos(LONG pos)
{
	ProgressSetPos(GetDlgItem(statusHwnd, IDC_STATUS_PROGRESS), pos);
	RedrawWindow(GetDlgItem(statusHwnd, IDC_STATUS_PROGRESS), NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
}
