#include "udosh.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "resource.rh"
#include "shconfig.h"
#include "help.h"
#include "misc.h"
#if UDO_INTEGRATED
#include <version.h>
#endif


/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void UpdateConfigData(CONFIG_DIALOG *cd, BOOL update)
{
	if (update)
	{
		cd->m_current.LowerCase = DlgGetButton(cd->hwnd, IDC_CHECK_LOWERCASE);
		cd->m_current.UnixPath = DlgGetButton(cd->hwnd, IDC_CHECK_UNIXPATH);
		cd->m_current.Wait = DlgGetButton(cd->hwnd, IDC_CHECK_WAIT);
		DlgGetText(cd->hwnd, IDC_EDIT_SUFFIX, cd->m_current.Suffix, sizeof(cd->m_current.Suffix));
		DlgGetText(cd->hwnd, IDC_FILE_APP, cd->m_current.Application, sizeof(cd->m_current.Application));
		DlgGetText(cd->hwnd, IDC_FILE_ARGS, cd->m_current.Args, sizeof(cd->m_current.Args));
	} else
	{
		DlgSetButton(cd->hwnd, IDC_CHECK_LOWERCASE, cd->m_current.LowerCase);
		DlgSetButton(cd->hwnd, IDC_CHECK_UNIXPATH, cd->m_current.UnixPath);
		DlgSetButton(cd->hwnd, IDC_CHECK_WAIT, cd->m_current.Wait);
		DlgSetText(cd->hwnd, IDC_EDIT_SUFFIX, cd->m_current.Suffix);
		DlgSetText(cd->hwnd, IDC_FILE_APP, cd->m_current.Application);
		DlgSetText(cd->hwnd, IDC_FILE_ARGS, cd->m_current.Args);
		CheckRadioButton(cd->hwnd, IDC_RADIO_DEST, IDC_RADIO_FINAL, IDC_RADIO_DEST + cd->m_radio);
	}
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void GetData(CONFIG_DIALOG *cd, int radio)
{
	char suff[MAX_PATH];

	if (cd->m_current.Suffix[0] != '\0')
	{
		if (cd->m_current.Suffix[0] != '.' && strcmp(cd->m_current.Suffix, "%") != 0)
		{
			strcpy(suff, ".");
			strcat(suff, cd->m_current.Suffix);
			strcpy(cd->m_current.Suffix, suff);
		}
	}

	switch (radio)
	{
	case 0: /* Zieldatei */
		cd->m_dest = cd->m_current;
		break;
	case 1: /* Parameterdatei */
		cd->m_param1 = cd->m_current;
		break;
	case 2: /* Parameterdatei #2 */
		cd->m_param2 = cd->m_current;
		break;
	case 3: /* Ergebnisdatei */
		cd->m_final = cd->m_current;
		break;
	}
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void SetData(CONFIG_DIALOG *cd, int radio)
{
	cd->m_radio = radio;
	switch (radio)
	{
	case 0: /* Zieldatei */
		cd->m_current = cd->m_dest;
		break;
	case 1: /* Parameterdatei */
		cd->m_current = cd->m_param1;
		break;
	case 2: /* Parameterdatei #2 */
		cd->m_current = cd->m_param2;
		break;
	case 3: /* Ergebnisdatei */
		cd->m_current = cd->m_final;
		break;
	}
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ChangeRadio(CONFIG_DIALOG *cd, int radio)
{
	int old;

	old = cd->m_radio;
	UpdateConfigData(cd, TRUE);
	GetData(cd, old);
	SetData(cd, radio);
	UpdateConfigData(cd, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

LOCAL void ChooseApp(CONFIG_DIALOG *cd)
{
	char cmd[MAX_PATH];
	char title[256];
	char select[256];
	char type[256];
	UINT type_id;
	
	UpdateConfigData(cd, TRUE);
	strcpy(cmd, cd->m_current.Application);
	
	LoadString(GetInstance(), IDS_CHOOSE_APPLICATION, title, sizeof(title));
	type_id = cd->m_radio == 0 ? IDS_TYPE_DESTINATION :
		cd->m_radio == 3 ? IDS_TYPE_RESULT :
		IDS_TYPE_PARAMETER;
	LoadString(GetInstance(), type_id, type, sizeof(type));
	strreplace(title, "%s", type);
	LoadString(GetInstance(), IDS_SELECT_PROGRAM, select, sizeof(select));
	if (choose_file(cd->hwnd, cmd, sizeof(cmd), TRUE, title, select))
	{
		strcpy(cd->m_current.Application, cmd);
		UpdateConfigData(cd, FALSE);
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL INT_PTR CALLBACK config_dialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CONFIG_DIALOG *cd;
	WORD notifyCode;

	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_INITDIALOG:
		cd = (CONFIG_DIALOG *)lParam;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (DWORD_PTR)cd);
		cd->hwnd = hwnd;
		CenterWindow(hwnd);
		
		UpdateConfigData(cd, FALSE);
		if (cd->choose_app)
			PostMessage(cd->hwnd, WM_COMMAND, MAKEWPARAM(IDC_CHOOSE_APP, BN_CLICKED), 0);
		return TRUE;

	case WM_CLOSE:
		EndDialog(hwnd, IDCANCEL);
		DestroyWindow(hwnd);
		return TRUE;

	case WM_COMMAND:
		notifyCode = HIWORD(wParam);
		cd = (CONFIG_DIALOG *)(DWORD_PTR)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			return TRUE;

		case IDOK:
			UpdateConfigData(cd, TRUE);
			GetData(cd, cd->m_radio);
			EndDialog(hwnd, IDOK);
			return TRUE;

		case IDHELP:
			if (notifyCode == BN_CLICKED)
				Help_Show(hwnd, cd->udosh_helpfile, "FormatConfiguration");
			break;
		
		case IDC_CHOOSE_APP:
			if (notifyCode == BN_CLICKED)
				ChooseApp(cd);
			break;
			
		case IDC_CHECK_WAIT:
			if (notifyCode == BN_CLICKED)
				UpdateConfigData(cd, TRUE);
			break;
			
		case IDC_RADIO_DEST:
		case IDC_RADIO_PARAM1:
		case IDC_RADIO_PARAM2:
		case IDC_RADIO_FINAL:
			if (notifyCode == BN_CLICKED)
				ChangeRadio(cd, LOWORD(wParam) - IDC_RADIO_DEST);
			break;
		}
		break;
	}
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

int Config_Dialog(HWND parent, CONFIG_DIALOG *cd)
{
	SetData(cd, cd->m_radio);
	return DialogBoxParam(GetInstance(), MAKEINTRESOURCE(IDD_CONFIG_DIALOG), parent, config_dialog, (LPARAM)cd);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

LOCAL void UpdateSettingData(SETTING_DIALOG *dlg, BOOL update)
{
	if (update)
	{
		dlg->always_on_top = DlgGetButton(dlg->hwnd, IDC_CHECK_AOT);
		dlg->create_dirs = DlgGetButton(dlg->hwnd, IDC_CREATE_DIRS);
		dlg->use_udo = DlgGetButton(dlg->hwnd, IDC_USE_UDO) ? USE_UDO_INT : USE_UDO_APP;
		DlgGetText(dlg->hwnd, IDC_UDO_HELPFILE, dlg->udo_helpfile, sizeof(dlg->udo_helpfile));
		DlgGetText(dlg->hwnd, IDC_UDO_HELP_COMMANDS, dlg->udo_help_commands, sizeof(dlg->udo_help_commands));
	} else
	{
		DlgSetButton(dlg->hwnd, IDC_CHECK_AOT, dlg->always_on_top);
		DlgSetButton(dlg->hwnd, IDC_CREATE_DIRS, dlg->create_dirs);
		DlgSetButton(dlg->hwnd, IDC_USE_UDO, dlg->use_udo == USE_UDO_INT);
		EnableWindow(GetDlgItem(dlg->hwnd, IDC_USE_UDO), UDO_INTEGRATED);
		DlgSetText(dlg->hwnd, IDC_UDO_HELPFILE, dlg->udo_helpfile);
		DlgSetText(dlg->hwnd, IDC_UDO_HELP_COMMANDS, dlg->udo_help_commands);
	}
}

/*** ---------------------------------------------------------------------- ***/

LOCAL INT_PTR CALLBACK setting_dialog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SETTING_DIALOG *dlg;
	WORD notifyCode;
	char buf[100];
	char title[256];
	char select[256];
	
	switch (message)
	{
	case WM_CREATE:
		break;

	case WM_INITDIALOG:
		dlg = (SETTING_DIALOG *)lParam;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (DWORD_PTR)dlg);
		dlg->hwnd = hwnd;
		CenterWindow(hwnd);
		
		UpdateSettingData(dlg, FALSE);
#if UDO_INTEGRATED
		sprintf(buf, "(%s)", UDO_VERSION_STRING_OS);
#else
		buf[0] = '\0';
#endif
		SetDlgItemText(hwnd, IDC_INT_UDO_VERSION, buf);
		return TRUE;

	case WM_CLOSE:
		EndDialog(hwnd, IDCANCEL);
		DestroyWindow(hwnd);
		return TRUE;

	case WM_COMMAND:
		notifyCode = HIWORD(wParam);
		dlg = (SETTING_DIALOG *)(DWORD_PTR)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			return TRUE;

		case IDOK:
			UpdateSettingData(dlg, TRUE);
			EndDialog(hwnd, IDOK);
			return TRUE;
		
		case IDC_CHOOSE_UDO_HELPFILE:
			if (notifyCode == BN_CLICKED)
			{
				UpdateSettingData(dlg, TRUE);
				LoadString(GetInstance(), IDS_CHOOSE_HELP, title, sizeof(title));
				LoadString(GetInstance(), IDS_SELECT_HELP, select, sizeof(select));
				if (choose_file(hwnd, dlg->udo_helpfile, sizeof(dlg->udo_helpfile), TRUE, title, select))
				{
					UpdateSettingData(dlg, FALSE);
				}
			}
			break;
		
		case IDHELP:
			if (notifyCode == BN_CLICKED)
				Help_Show(hwnd, dlg->udosh_helpfile, "Settings");
			break;
		}
		break;
	}
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

int Setting_Dialog(HWND parent, SETTING_DIALOG *dlg)
{
	return DialogBoxParam(GetInstance(), MAKEINTRESOURCE(IDD_SETTING_DIALOG), parent, setting_dialog, (LPARAM)dlg);
}
