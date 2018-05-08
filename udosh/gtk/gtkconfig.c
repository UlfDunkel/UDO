#include "udogtk.h"
#include "gtkconfig.h"
#include "help.h"
#include "misc.h"
#if UDO_INTEGRATED
#include <version.h>
#endif


/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void UpdateConfigData(CONFIG_DIALOG *cd, gboolean update)
{
	if (update)
	{
		cd->m_current.LowerCase = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cd->lowercase_button));
		cd->m_current.UnixPath = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cd->unixpath_button));
		cd->m_current.Wait = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cd->wait_button));
		g_free(cd->m_current.Suffix);
		cd->m_current.Suffix = g_strdup(gtk_entry_get_text(GTK_ENTRY(cd->suffix_entry)));
		g_free(cd->m_current.Application);
		cd->m_current.Application = g_strdup(gtk_entry_get_text(GTK_ENTRY(cd->application_entry)));
		g_free(cd->m_current.Args);
		cd->m_current.Args = g_strdup(gtk_entry_get_text(GTK_ENTRY(cd->args_entry)));
	} else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cd->lowercase_button), cd->m_current.LowerCase);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cd->unixpath_button), cd->m_current.UnixPath);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cd->wait_button), cd->m_current.Wait);
		gtk_entry_set_text(GTK_ENTRY(cd->suffix_entry), fixnull(cd->m_current.Suffix));
		gtk_entry_set_text(GTK_ENTRY(cd->application_entry), fixnull(cd->m_current.Application));
		gtk_entry_set_text(GTK_ENTRY(cd->args_entry), fixnull(cd->m_current.Args));
		/* calling that here will immedialety trigger the "clicked" signal again */
		/* gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cd->dest_radio[cd->m_radio]), TRUE); */
	}
}

/*** ---------------------------------------------------------------------- ***/

static void GetData(CONFIG_DIALOG *cd, int radio)
{
	char *suff;

	if (!empty(cd->m_current.Suffix))
	{
		if (cd->m_current.Suffix[0] != '.' && strcmp(cd->m_current.Suffix, "%") != 0)
		{
			suff = g_strconcat(".", cd->m_current.Suffix, NULL);
			g_free(cd->m_current.Suffix);
			cd->m_current.Suffix = suff;
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

static void SetData(CONFIG_DIALOG *cd, int radio)
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

static void ChangeRadio(CONFIG_DIALOG *cd, int radio)
{
	int old;

	old = cd->m_radio;
	UpdateConfigData(cd, TRUE);
	GetData(cd, old);
	SetData(cd, radio);
	UpdateConfigData(cd, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

static void ChooseApp(GtkWidget *widget, void *userdata)
{
	CONFIG_DIALOG *cd = (CONFIG_DIALOG *)userdata;
	char *title;
	const char *type;
	
	UNUSED(widget);
	UpdateConfigData(cd, TRUE);
	
	type = cd->m_radio == 0 ? IDS_TYPE_DESTINATION :
		cd->m_radio == 3 ? IDS_TYPE_RESULT :
		IDS_TYPE_PARAMETER;
	title = g_strdup_printf(_("Choose application for %s file..."), type);
	if (choose_file(cd->hwnd, &cd->m_current.Application, TRUE, title, IDS_SELECT_PROGRAM))
	{
		check_desktop_file(&cd->m_current.Application);
		UpdateConfigData(cd, FALSE);
	}
	g_free(title);
}

/*** ---------------------------------------------------------------------- ***/

static void config_dialog_destroyed(GtkWidget *widget, void *userdata)
{
	CONFIG_DIALOG *cd = (CONFIG_DIALOG *)userdata;
	UNUSED(widget);
	g_free(cd);
}

/*** ---------------------------------------------------------------------- ***/

static void config_dialog_response(GtkWidget *widget, int response, void *userdata)
{
	CONFIG_DIALOG *cd = (CONFIG_DIALOG *)userdata;
	
	UNUSED(widget);
	switch (response)
	{
	case GTK_RESPONSE_OK:
	case GTK_RESPONSE_YES:
		if (cd->ok)
		{
			UpdateConfigData(cd, TRUE);
			GetData(cd, cd->m_radio);
			cd->ok(cd, cd->userdata, TRUE);
		}
		gtk_widget_destroy(cd->hwnd);
		break;
	case GTK_RESPONSE_DELETE_EVENT:
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_CLOSE:
	case GTK_RESPONSE_NO:
		if (cd->ok)
		{
			UpdateConfigData(cd, TRUE);
			GetData(cd, cd->m_radio);
			cd->ok(cd, cd->userdata, FALSE);
		}
		gtk_widget_destroy(cd->hwnd);
		break;
	case GTK_RESPONSE_HELP:
		Help_Show(cd->hwnd, cd->udosh_helpfile, "FormatConfiguration");
		break;
	}
}

/*** ---------------------------------------------------------------------- ***/

static void config_dialog_dest_clicked_0(GtkWidget *widget, void *userdata)
{
	CONFIG_DIALOG *cd = (CONFIG_DIALOG *)userdata;
	UNUSED(widget);
	ChangeRadio(cd, 0);
}

/*** ---------------------------------------------------------------------- ***/

static void config_dialog_dest_clicked_1(GtkWidget *widget, void *userdata)
{
	CONFIG_DIALOG *cd = (CONFIG_DIALOG *)userdata;
	UNUSED(widget);
	ChangeRadio(cd, 1);
}

/*** ---------------------------------------------------------------------- ***/

static void config_dialog_dest_clicked_2(GtkWidget *widget, void *userdata)
{
	CONFIG_DIALOG *cd = (CONFIG_DIALOG *)userdata;
	UNUSED(widget);
	ChangeRadio(cd, 2);
}

/*** ---------------------------------------------------------------------- ***/

static void config_dialog_dest_clicked_3(GtkWidget *widget, void *userdata)
{
	CONFIG_DIALOG *cd = (CONFIG_DIALOG *)userdata;
	UNUSED(widget);
	ChangeRadio(cd, 3);
}

/*** ---------------------------------------------------------------------- ***/

void Config_Dialog_Run(CONFIG_DIALOG *cd, void (*ok)(CONFIG_DIALOG *cd, void *userdata, gboolean apply), void *userdata)
{
	cd->ok = ok;
	cd->userdata = userdata;
	
	SetData(cd, cd->m_radio);
	UpdateConfigData(cd, FALSE);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cd->dest_radio[cd->m_radio]), TRUE);
	
	gtk_signal_connect(GTK_OBJECT(cd->dest_radio[0]), "clicked", GTK_SIGNAL_FUNC(config_dialog_dest_clicked_0), (gpointer) cd);
	gtk_signal_connect(GTK_OBJECT(cd->dest_radio[1]), "clicked", GTK_SIGNAL_FUNC(config_dialog_dest_clicked_1), (gpointer) cd);
	gtk_signal_connect(GTK_OBJECT(cd->dest_radio[2]), "clicked", GTK_SIGNAL_FUNC(config_dialog_dest_clicked_2), (gpointer) cd);
	gtk_signal_connect(GTK_OBJECT(cd->dest_radio[3]), "clicked", GTK_SIGNAL_FUNC(config_dialog_dest_clicked_3), (gpointer) cd);

	gtk_signal_connect(GTK_OBJECT(cd->choose_app_button), "clicked", GTK_SIGNAL_FUNC(ChooseApp), (gpointer) cd);

	gtk_signal_connect(GTK_OBJECT(cd->hwnd), "response", GTK_SIGNAL_FUNC(config_dialog_response), (gpointer) cd);
	
	gtk_signal_connect(GTK_OBJECT(cd->hwnd), "destroy", GTK_SIGNAL_FUNC(config_dialog_destroyed), (gpointer) cd);
	
	if (cd->parent != NULL)
		gtk_window_set_transient_for(GTK_WINDOW(cd->hwnd), GTK_WINDOW(cd->parent));
	
	gtk_widget_show(cd->hwnd);
	CenterWindow(cd->hwnd);
	
	gtk_window_present(GTK_WINDOW(cd->hwnd));

	if (cd->choose_app)
		gtk_signal_emit_by_name(GTK_OBJECT(cd->choose_app_button), "clicked", NULL);
}

/*** ---------------------------------------------------------------------- ***/

CONFIG_DIALOG *Config_Dialog_New(GtkWidget *parent)
{
	CONFIG_DIALOG *dlg;
	GtkWidget *dialog_vbox, *dialog_hbox, *vbox1, *vbox2, *hbox1, *hbox2, *hbox3, *vbox3;
	GtkWidget *frame;
	GtkWidget *button;
	GtkWidget *label;
	GSList *radiobutton_group = NULL;
	GdkPixbuf *icon;
	
	dlg = g_new0(CONFIG_DIALOG, 1);
	if (dlg == NULL)
		return NULL;
	parent = gtk_widget_get_toplevel(parent);
	dlg->parent = parent;
	
	dlg->hwnd = gtk_dialog_new();
	gtk_container_set_border_width (GTK_CONTAINER (dlg->hwnd), 5);
	gtk_window_set_type_hint (GTK_WINDOW (dlg->hwnd), GDK_WINDOW_TYPE_HINT_DIALOG);
	icon = app_icon();
	gtk_window_set_icon(GTK_WINDOW(dlg->hwnd), icon);
	gdk_pixbuf_unref(icon);
	gtk_window_set_title(GTK_WINDOW(dlg->hwnd), _("Format Configuration"));
	g_object_set_data(G_OBJECT(dlg->hwnd), "udoshell_window_type", NO_CONST("config-dialog"));
	
	dialog_vbox = gtk_dialog_get_content_area(GTK_DIALOG(dlg->hwnd));
	gtk_widget_show (dialog_vbox);

	hbox1 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox1);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), hbox1, TRUE, TRUE, 0);

	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_box_pack_start (GTK_BOX (hbox1), frame, TRUE, TRUE, 0);

	vbox1 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox1);
	gtk_container_add (GTK_CONTAINER (frame), vbox1);

	dlg->dest_radio[0] = button = gtk_radio_button_new_with_mnemonic (NULL, _("Destination"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox1), button, TRUE, TRUE, 0);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (button), radiobutton_group);
	radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (button));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);

	dlg->dest_radio[1] = button = gtk_radio_button_new_with_mnemonic (NULL, _("Parameter #1"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox1), button, TRUE, TRUE, 0);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (button), radiobutton_group);
	radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (button));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);

	dlg->dest_radio[2] = button = gtk_radio_button_new_with_mnemonic (NULL, _("Parameter #2"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox1), button, TRUE, TRUE, 0);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (button), radiobutton_group);
	radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (button));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);

	dlg->dest_radio[3] = button = gtk_radio_button_new_with_mnemonic (NULL, _("Result"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox1), button, TRUE, TRUE, 0);
	gtk_radio_button_set_group (GTK_RADIO_BUTTON (button), radiobutton_group);
	radiobutton_group = gtk_radio_button_get_group (GTK_RADIO_BUTTON (button));
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button), TRUE);

	label = gtk_label_new (_("File type"));
	gtk_widget_show (label);
	gtk_frame_set_label_widget (GTK_FRAME (frame), label);
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);

	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_box_pack_start (GTK_BOX (hbox1), frame, TRUE, TRUE, 0);

	vbox2 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox2);
	gtk_container_add (GTK_CONTAINER (frame), vbox2);

	hbox2 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox2);
	gtk_box_pack_start (GTK_BOX (vbox2), hbox2, TRUE, TRUE, 0);

	label = gtk_label_new (_("Suffix:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (hbox2), label, TRUE, TRUE, 0);

	dlg->suffix_entry = gtk_entry_new ();
	gtk_widget_show (dlg->suffix_entry);
	gtk_box_pack_start (GTK_BOX (hbox2), dlg->suffix_entry, TRUE, TRUE, 0);

	dlg->lowercase_button = gtk_check_button_new_with_mnemonic (_("lowercase file names"));
	gtk_widget_show (dlg->lowercase_button);
	gtk_box_pack_start (GTK_BOX (vbox2), dlg->lowercase_button, TRUE, TRUE, 0);

	dlg->unixpath_button = gtk_check_button_new_with_mnemonic (_("Unix path for application"));
	gtk_widget_show (dlg->unixpath_button);
	gtk_box_pack_start (GTK_BOX (vbox2), dlg->unixpath_button, TRUE, TRUE, 0);

	dlg->wait_button = gtk_check_button_new_with_mnemonic (_("Wait for completion"));
	gtk_widget_show (dlg->wait_button);
	gtk_box_pack_start (GTK_BOX (vbox2), dlg->wait_button, TRUE, TRUE, 0);

	label = gtk_label_new (_("Options"));
	gtk_widget_show (label);
	gtk_frame_set_label_widget (GTK_FRAME (frame), label);
	gtk_label_set_use_markup (GTK_LABEL (label), TRUE);

	vbox3 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox3);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), vbox3, TRUE, TRUE, 0);

	hbox3 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox3);
	gtk_box_pack_start (GTK_BOX (vbox3), hbox3, TRUE, TRUE, 0);

	dlg->application_entry = gtk_entry_new ();
	gtk_widget_show (dlg->application_entry);
	gtk_box_pack_start (GTK_BOX (hbox3), dlg->application_entry, TRUE, TRUE, 0);
	gtk_entry_set_invisible_char (GTK_ENTRY (dlg->application_entry), 9679);

	dlg->choose_app_button = gtk_button_new_with_mnemonic (_("..."));
	gtk_widget_show (dlg->choose_app_button);
	gtk_box_pack_start (GTK_BOX (hbox3), dlg->choose_app_button, FALSE, FALSE, 0);
	gtk_widget_set_size_request(dlg->choose_app_button, 30, -1);

	label = gtk_label_new (_("Args:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox3), label, TRUE, TRUE, 0);

	dlg->args_entry = gtk_entry_new ();
	gtk_widget_show (dlg->args_entry);
	gtk_box_pack_start (GTK_BOX (vbox3), dlg->args_entry, TRUE, TRUE, 0);
	gtk_entry_set_invisible_char (GTK_ENTRY (dlg->args_entry), 9679);

	dialog_hbox = gtk_dialog_get_action_area(GTK_DIALOG(dlg->hwnd));
	gtk_widget_show (dialog_hbox);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_hbox), GTK_BUTTONBOX_END);

	dlg->help_button = button = gtk_button_new_from_stock(GTK_STOCK_HELP);
	gtk_dialog_add_action_widget(GTK_DIALOG(dlg->hwnd), button, GTK_RESPONSE_HELP);
	gtk_widget_show(button);
	gtk_widget_set_can_default(button, TRUE);
	gtk_button_box_set_child_secondary(GTK_BUTTON_BOX(dialog_hbox), button, TRUE);
	
	dlg->cancel_button = button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
	gtk_widget_show(button);
	gtk_widget_set_can_default(button, TRUE);
	gtk_dialog_add_action_widget(GTK_DIALOG(dlg->hwnd), button, GTK_RESPONSE_CANCEL);
	
	dlg->ok_button = button = gtk_button_new_from_stock(GTK_STOCK_OK);
	gtk_widget_show(button);
	gtk_widget_set_can_default(button, TRUE);
	gtk_dialog_add_action_widget(GTK_DIALOG(dlg->hwnd), button, GTK_RESPONSE_OK);
	
	return dlg;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void UpdateSettingData(SETTING_DIALOG *dlg, gboolean update)
{
	if (update)
	{
		dlg->always_on_top = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(dlg->always_on_top_button));
		dlg->create_dirs = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(dlg->create_dirs_button));
		dlg->use_udo = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(dlg->use_udo_button)) ? USE_UDO_INT : USE_UDO_APP;
		g_free(dlg->udo_helpfile);
		dlg->udo_helpfile = g_strdup(gtk_entry_get_text(GTK_ENTRY(dlg->udo_helpfile_entry)));
		g_free(dlg->udo_help_commands);
		dlg->udo_help_commands = g_strdup(gtk_entry_get_text(GTK_ENTRY(dlg->udo_help_commands_entry)));
	} else
	{
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dlg->always_on_top_button), dlg->always_on_top);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dlg->create_dirs_button), dlg->create_dirs);
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(dlg->use_udo_button), dlg->use_udo == USE_UDO_INT);
		gtk_widget_set_sensitive(dlg->use_udo_button, UDO_INTEGRATED);
		gtk_entry_set_text(GTK_ENTRY(dlg->udo_helpfile_entry), fixnull(dlg->udo_helpfile));
		gtk_entry_set_text(GTK_ENTRY(dlg->udo_help_commands_entry), fixnull(dlg->udo_help_commands));
	}
}

/*** ---------------------------------------------------------------------- ***/

static void setting_dialog_destroyed(GtkWidget *widget, void *userdata)
{
	SETTING_DIALOG *sd = (SETTING_DIALOG *)userdata;
	UNUSED(widget);
	g_free(sd);
}

/*** ---------------------------------------------------------------------- ***/

static void setting_dialog_response(GtkWidget *widget, int response, void *userdata)
{
	SETTING_DIALOG *sd = (SETTING_DIALOG *)userdata;
	
	UNUSED(widget);
	switch (response)
	{
	case GTK_RESPONSE_OK:
	case GTK_RESPONSE_YES:
		if (sd->ok)
		{
			UpdateSettingData(sd, TRUE);
			sd->ok(sd, sd->userdata, TRUE);
		}
		gtk_widget_destroy(sd->hwnd);
		break;
	case GTK_RESPONSE_DELETE_EVENT:
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_CLOSE:
	case GTK_RESPONSE_NO:
		if (sd->ok)
		{
			UpdateSettingData(sd, TRUE);
			sd->ok(sd, sd->userdata, FALSE);
		}
		gtk_widget_destroy(sd->hwnd);
		break;
	case GTK_RESPONSE_HELP:
		Help_Show(sd->hwnd, sd->udosh_helpfile, "Settings");
		break;
	}
}

/*** ---------------------------------------------------------------------- ***/

static void ChooseHelp(GtkWidget *widget, void *userdata)
{
	SETTING_DIALOG *sd = (SETTING_DIALOG *)userdata;
	const char *title;
	
	UNUSED(widget);
	UpdateSettingData(sd, TRUE);
	title = _("Choose UDO Help file...");
	if (choose_file(sd->hwnd, &sd->udo_helpfile, TRUE, title, IDS_SELECT_HELP))
	{
		UpdateSettingData(sd, FALSE);
	}
}

/*** ---------------------------------------------------------------------- ***/

SETTING_DIALOG *Setting_Dialog_New(GtkWidget *parent)
{
	SETTING_DIALOG *sd;
	char *buf, *version;
	GtkWidget *dialog_vbox, *dialog_hbox, *vbox1, *vbox2, *hbox1, *vbox3;
	GtkWidget *button;
	GtkWidget *label;
	GdkPixbuf *icon;
	
	sd = g_new0(SETTING_DIALOG, 1);
	if (sd == NULL)
		return NULL;
	parent = gtk_widget_get_toplevel(parent);
	sd->parent = parent;

	sd->hwnd = gtk_dialog_new ();
	gtk_container_set_border_width (GTK_CONTAINER (sd->hwnd), 5);
	gtk_window_set_type_hint (GTK_WINDOW (sd->hwnd), GDK_WINDOW_TYPE_HINT_DIALOG);
	icon = app_icon();
	gtk_window_set_icon(GTK_WINDOW(sd->hwnd), icon);
	gdk_pixbuf_unref(icon);
	gtk_window_set_title (GTK_WINDOW (sd->hwnd), _("Shell Options"));
	g_object_set_data(G_OBJECT(sd->hwnd), "udoshell_window_type", NO_CONST("setting-dialog"));
	
#if UDO_INTEGRATED
	version = g_strdup_printf(" (%s)", UDO_VERSION_STRING_OS);
#else
	version = g_strdup("");
#endif

	dialog_vbox = gtk_dialog_get_content_area(GTK_DIALOG(sd->hwnd));
	gtk_widget_show (dialog_vbox);

	sd->always_on_top_button = button = gtk_check_button_new_with_mnemonic (_("Shell always on top"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), button, TRUE, TRUE, 0);

	sd->create_dirs_button = button = gtk_check_button_new_with_mnemonic (_("Create directories"));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), button, TRUE, TRUE, 0);
	
	buf = g_strdup_printf(_("Use integrated UDO%s"), version);
	sd->use_udo_button = button = gtk_check_button_new_with_mnemonic (buf);
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), button, TRUE, TRUE, 0);
	g_free(buf);
	
	hbox1 = gtk_hbox_new (FALSE, 0);
	gtk_widget_show (hbox1);
	gtk_box_pack_start (GTK_BOX (dialog_vbox), hbox1, TRUE, FALSE, 0);

	vbox1 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox1);
	gtk_box_pack_start (GTK_BOX (hbox1), vbox1, FALSE, FALSE, 0);

	label = gtk_label_new (_("UDO Helpfile:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox1), label, TRUE, TRUE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 10, 0);

	label = gtk_label_new (_("Topic:"));
	gtk_widget_show (label);
	gtk_box_pack_start (GTK_BOX (vbox1), label, FALSE, FALSE, 0);
	gtk_misc_set_alignment (GTK_MISC (label), 0, 0.5);
	gtk_misc_set_padding (GTK_MISC (label), 10, 0);

	vbox2 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox2);
	gtk_box_pack_start (GTK_BOX (hbox1), vbox2, TRUE, TRUE, 0);

	sd->udo_helpfile_entry = gtk_entry_new ();
	gtk_widget_show (sd->udo_helpfile_entry);
	gtk_box_pack_start (GTK_BOX (vbox2), sd->udo_helpfile_entry, TRUE, TRUE, 0);

	sd->udo_help_commands_entry = gtk_entry_new ();
	gtk_widget_show (sd->udo_help_commands_entry);
	gtk_box_pack_start (GTK_BOX (vbox2), sd->udo_help_commands_entry, TRUE, TRUE, 0);

	vbox3 = gtk_vbox_new (FALSE, 0);
	gtk_widget_show (vbox3);
	gtk_box_pack_start (GTK_BOX (hbox1), vbox3, FALSE, FALSE, 0);

	sd->udo_choose_udo_helpfile_button = button = gtk_button_new_with_mnemonic (_("..."));
	gtk_widget_show (button);
	gtk_box_pack_start (GTK_BOX (vbox3), button, FALSE, FALSE, 0);
	gtk_widget_set_size_request (button, 30, -1);

	dialog_hbox = gtk_dialog_get_action_area(GTK_DIALOG(sd->hwnd));
	gtk_widget_show (dialog_hbox);
	gtk_button_box_set_layout (GTK_BUTTON_BOX (dialog_hbox), GTK_BUTTONBOX_END);

	sd->help_button = button = gtk_button_new_from_stock(GTK_STOCK_HELP);
	gtk_dialog_add_action_widget(GTK_DIALOG(sd->hwnd), button, GTK_RESPONSE_HELP);
	gtk_widget_show(button);
	gtk_widget_set_can_default(button, TRUE);
	gtk_button_box_set_child_secondary(GTK_BUTTON_BOX(dialog_hbox), button, TRUE);
	
	sd->cancel_button = button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
	gtk_widget_show(button);
	gtk_widget_set_can_default(button, TRUE);
	gtk_dialog_add_action_widget(GTK_DIALOG(sd->hwnd), button, GTK_RESPONSE_CANCEL);
	
	sd->ok_button = button = gtk_button_new_from_stock(GTK_STOCK_OK);
	gtk_widget_show(button);
	gtk_widget_set_can_default(button, TRUE);
	gtk_dialog_add_action_widget(GTK_DIALOG(sd->hwnd), button, GTK_RESPONSE_OK);
	
	g_free(version);

	return sd;
}

/*** ---------------------------------------------------------------------- ***/

void Setting_Dialog_Run(SETTING_DIALOG *sd, void (*ok)(SETTING_DIALOG *sd, void *userdata, gboolean apply), void *userdata)
{
	sd->ok = ok;
	sd->userdata = userdata;
	
	CenterWindow(sd->hwnd);
		
	UpdateSettingData(sd, FALSE);

	gtk_signal_connect(GTK_OBJECT(sd->hwnd), "response", GTK_SIGNAL_FUNC(setting_dialog_response), (gpointer) sd);

	gtk_signal_connect(GTK_OBJECT(sd->udo_choose_udo_helpfile_button), "clicked", GTK_SIGNAL_FUNC(ChooseHelp), (gpointer) sd);
	
	gtk_signal_connect(GTK_OBJECT(sd->hwnd), "destroy", GTK_SIGNAL_FUNC(setting_dialog_destroyed), (gpointer) sd);
	
	if (sd->parent != NULL)
		gtk_window_set_transient_for(GTK_WINDOW(sd->hwnd), GTK_WINDOW(sd->parent));
	
	gtk_widget_show(sd->hwnd);
	gtk_window_present(GTK_WINDOW(sd->hwnd));
}
