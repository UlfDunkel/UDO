#ifndef UDO_INTEGRATED
#  define UDO_INTEGRATED 0
#endif

#define USE_UDO_APP 0
#define USE_UDO_INT 1
#define USE_UDO_DLL 2

typedef struct _formatinfo
{
	char Application[MAX_PATH];
	char Args[MAX_PATH];
	char Editor[MAX_PATH];
	char Suffix[MAX_PATH];
	BOOL LowerCase;
	BOOL UnixPath;
	BOOL Wait;
} FormatInfo;

typedef struct _config_dialog
{
	HWND	hwnd;
	char	udosh_helpfile[MAX_PATH];
	
	int		m_radio;
	BOOL	choose_app;
	
	FormatInfo m_current;
	
	FormatInfo m_dest;
	FormatInfo m_param1;
	FormatInfo m_param2;
	FormatInfo m_final;
} CONFIG_DIALOG;


typedef struct _setting_dialog
{
	HWND	hwnd;
	
	BOOL	always_on_top;
	BOOL	create_dirs;
	int		use_udo;
	char	udosh_helpfile[MAX_PATH];
	char	udo_helpfile[MAX_PATH];
	char	udo_help_commands[MAX_PATH];
} SETTING_DIALOG;


int Config_Dialog(HWND parent, CONFIG_DIALOG *cd);
int Setting_Dialog(HWND parent, SETTING_DIALOG *dlg);
