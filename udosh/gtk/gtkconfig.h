#ifndef UDO_INTEGRATED
#  define UDO_INTEGRATED 0
#endif

#define USE_UDO_APP 0
#define USE_UDO_INT 1
#define USE_UDO_DLL 2

typedef struct _formatinfo
{
	char *Application;
	char *Args;
	char *Editor;
	char *Suffix;
	gboolean LowerCase;
	gboolean UnixPath;
	gboolean Wait;
} FormatInfo;

typedef struct _config_dialog CONFIG_DIALOG;
struct _config_dialog
{
	GtkWidget *parent;
	GtkWidget *hwnd;
	const char *udosh_helpfile;
	void (*ok)(CONFIG_DIALOG *, void *userdata, gboolean apply);
	void *userdata;
	
	int m_radio;
	gboolean choose_app;
	
	FormatInfo m_current;
	
	FormatInfo m_dest;
	FormatInfo m_param1;
	FormatInfo m_param2;
	FormatInfo m_final;
	
	GtkWidget *lowercase_button;
	GtkWidget *unixpath_button;
	GtkWidget *wait_button;
	GtkWidget *suffix_entry;
	GtkWidget *application_entry;
	GtkWidget *choose_app_button;
	GtkWidget *args_entry;
	GtkWidget *dest_radio[4];
	
	GtkWidget *ok_button;
	GtkWidget *cancel_button;
	GtkWidget *help_button;
};


typedef struct _setting_dialog SETTING_DIALOG;
struct _setting_dialog
{
	GtkWidget *parent;
	GtkWidget *hwnd;
	void (*ok)(SETTING_DIALOG *, void *userdata, gboolean apply);
	void *userdata;
	
	gboolean always_on_top;
	gboolean create_dirs;
	int use_udo;
	const char *udosh_helpfile;
	char *udo_helpfile;
	char *udo_help_commands;
	
	GtkWidget *always_on_top_button;
	GtkWidget *create_dirs_button;
	GtkWidget *use_udo_button;
	GtkWidget *udo_helpfile_entry;
	GtkWidget *udo_choose_udo_helpfile_button;
	GtkWidget *udo_help_commands_entry;
	
	GtkWidget *ok_button;
	GtkWidget *cancel_button;
	GtkWidget *help_button;
};


CONFIG_DIALOG *Config_Dialog_New(GtkWidget *parent);
void Config_Dialog_Run(CONFIG_DIALOG *cd, void (*ok)(CONFIG_DIALOG *cd, void *userdata, gboolean apply), void *userdata);

SETTING_DIALOG *Setting_Dialog_New(GtkWidget *parent);
void Setting_Dialog_Run(SETTING_DIALOG *cd, void (*ok)(SETTING_DIALOG *cd, void *userdata, gboolean apply), void *userdata);
