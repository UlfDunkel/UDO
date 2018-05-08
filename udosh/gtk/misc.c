#include "udogtk.h"
#include "misc.h"


/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void warning_dialog_dismiss_cb(GtkWidget *widget, gpointer user_data)
{
	GtkWidget *shell = GTK_WIDGET(widget);

	UNUSED(user_data);
	shell = gtk_widget_get_toplevel(shell);
	gtk_widget_destroy(shell);
	check_toplevels(shell);
}

/*** ---------------------------------------------------------------------- ***/

void show_dialog(GtkWidget *parent, const char *type, const char *message, void (*ok_fn)(GtkWidget *widget, gpointer user_data), gpointer user_data)
{
	char *msg = g_strdup(message);
	char *head;
	GtkWidget *dialog;
	GtkWidget *label = 0;
	GtkWidget *ok = 0;
	GtkWidget *cancel = 0;
	int center = 100;
	
	UNUSED(type);
	while (parent && !gtk_widget_get_window(parent))
		parent = gtk_widget_get_parent(parent);

 	if (!parent /* || !gtk_widget_get_window(parent) */)	/* too early to pop up transient dialogs */
	{
		fprintf(stderr, _("%s: too early for dialog?\n"), gl_program_name);
		fprintf(stderr, "%s: %s\n", gl_program_name, message);
		return;
	}

	dialog = gtk_dialog_new();
	g_object_set_data(G_OBJECT(dialog), "udoshell_window_type", NO_CONST("message-dialog"));
	
	head = msg;
	while (head)
	{
		char *s = strchr(head, '\n');

		if (s)
			*s = 0;

		{
			label = gtk_label_new(head);
			gtk_label_set_selectable(GTK_LABEL(label), TRUE);
			if (center <= 0)
				gtk_misc_set_alignment(GTK_MISC(label), 0.0, 0.5);
			gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), label, TRUE, TRUE, 0);
			gtk_widget_show(label);
		}

		if (s)
			head = s + 1;
		else
			head = 0;

		center--;
	}

	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_content_area(GTK_DIALOG(dialog))), label, TRUE, TRUE, 0);
	gtk_widget_show(label);

	label = gtk_hbutton_box_new();
	gtk_box_pack_start(GTK_BOX(gtk_dialog_get_action_area(GTK_DIALOG(dialog))),
					   label, TRUE, TRUE, 0);

	if (ok_fn != NULL)
	{
		cancel = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
		gtk_container_add(GTK_CONTAINER(label), cancel);
	}

	ok = gtk_button_new_from_stock(GTK_STOCK_OK);
	gtk_container_add(GTK_CONTAINER(label), ok);

	gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
	gtk_window_set_title(GTK_WINDOW(dialog), gl_program_name);
	gtk_widget_set_can_default(ok, TRUE);
	gtk_widget_show(ok);
	gtk_widget_grab_focus(ok);

	if (cancel)
	{
		gtk_widget_set_can_default(cancel, TRUE);
		gtk_widget_show(cancel);
	}
	gtk_widget_show(label);
	gtk_widget_show(dialog);

	if (ok_fn != NULL)
	{
		gtk_signal_connect(GTK_OBJECT(ok), "clicked", GTK_SIGNAL_FUNC(ok_fn), user_data);
		gtk_signal_connect(GTK_OBJECT(cancel), "clicked", GTK_SIGNAL_FUNC(warning_dialog_dismiss_cb), user_data);
	} else
	{
		gtk_signal_connect(GTK_OBJECT(ok), "clicked", GTK_SIGNAL_FUNC(warning_dialog_dismiss_cb), user_data);
	}

	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent));

	gtk_window_present(GTK_WINDOW(dialog));
	g_free(msg);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

void CenterWindow(GtkWidget *hwnd)
{
	gtk_window_set_position(GTK_WINDOW(hwnd), GTK_WIN_POS_CENTER);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

void my_fsplit(const char *cs, char *drive, char *path, char *filename, char *suffix)
{
	char wrk[PATH_MAX];
	char *p;
	
	*drive = '\0';
	*path = '\0';
	*filename = '\0';
	*suffix = '\0';

	if (empty(cs))
		return;
	
	strncpy(wrk, cs, sizeof(wrk) - 1);
	wrk[sizeof(wrk) - 1] = '\0';
	
	/* Drive ermitteln und abschneiden */
	if (wrk[0] != '\0' && wrk[1] == ':' )
	{
		strcpy(drive, "a:");
		drive[0] = wrk[0];
		memmove(wrk, wrk + 2, strlen(wrk + 2) + 1);
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
	}

	/* Jetzt noch aus dem Filenamen den Suffix extrahieren */
	if ((p = strrchr(filename, '.')) != NULL)
	{
		strcpy(suffix, p);
		*p = '\0';
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

typedef struct file_chooser {
	GtkFileChooserDialog *selector;
	char **name;
	gboolean ok;
	gboolean done;
} FILE_CHOOSER;

static GtkFileChooserDialog *choose_file_selector;

/*** ---------------------------------------------------------------------- ***/

static void choose_file_ok(GtkWidget *button, gpointer user_data)
{
	FILE_CHOOSER *info = (FILE_CHOOSER *)user_data;
	GtkFileChooserDialog *selector = info->selector;
	const char *path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(selector));
	
	UNUSED(button);
	g_free(*(info->name));
	*(info->name) = g_strdup(path);
	
	info->done = TRUE;
	info->ok = TRUE;
	gtk_widget_hide(GTK_WIDGET(selector));
	check_toplevels(GTK_WIDGET(selector));
}

/*** ---------------------------------------------------------------------- ***/

static void choose_file_destroyed(GtkWidget *button, gpointer user_data)
{
	FILE_CHOOSER *info = (FILE_CHOOSER *)user_data;
	UNUSED(button);
	g_free(info);
	choose_file_selector = NULL;
}

/*** ---------------------------------------------------------------------- ***/

static void choose_file_cancel(GtkWidget *button, gpointer user_data)
{
	FILE_CHOOSER *info = (FILE_CHOOSER *)user_data;

	UNUSED(button);
	info->done = TRUE;
	info->ok = FALSE;
	gtk_widget_hide(GTK_WIDGET(info->selector));
	check_toplevels(GTK_WIDGET(info->selector));
}

/*** ---------------------------------------------------------------------- ***/

static void choose_file_close(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
	UNUSED(event);
	choose_file_cancel(widget, user_data);
}

/*** ---------------------------------------------------------------------- ***/

static void choose_file_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
	switch (response_id)
	{
	case GTK_RESPONSE_OK:
	case GTK_RESPONSE_APPLY:
	case GTK_RESPONSE_ACCEPT:
	case GTK_RESPONSE_YES:
		choose_file_ok(GTK_WIDGET(dialog), user_data);
		break;
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_CLOSE:
	case GTK_RESPONSE_NO:
		choose_file_cancel(GTK_WIDGET(dialog), user_data);
		break;
	case GTK_RESPONSE_DELETE_EVENT:
		choose_file_close(GTK_WIDGET(dialog), NULL, user_data);
		break;
	}
}

/*** ---------------------------------------------------------------------- ***/

static gboolean filter_exe(const GtkFileFilterInfo *filter_info, gpointer userdata)
{
	FILE_CHOOSER *info = (FILE_CHOOSER *)userdata;
	GFile *file;
	gboolean ret = FALSE;
	
	UNUSED(info);
	
	if (!(filter_info->contains & GTK_FILE_FILTER_FILENAME))
		return FALSE;
	if (g_pattern_match_simple("*.exe", filter_info->filename))
		return TRUE;
	if (g_pattern_match_simple("*.cmd", filter_info->filename))
		return TRUE;
	if (g_pattern_match_simple("*.bat", filter_info->filename))
		return TRUE;
	if (g_pattern_match_simple("*.desktop", filter_info->filename))
		return TRUE;
	file = g_file_new_for_path(filter_info->filename);
	if (file != NULL)
	{
		GFileInfo *fileinfo = g_file_query_info(file, "access::*", G_FILE_QUERY_INFO_NONE, NULL, NULL);
		if (fileinfo != NULL)
		{
			if (g_file_info_has_attribute(fileinfo, G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE))
				ret = TRUE;
			g_object_unref(fileinfo);
		}
		g_object_unref(file);
	}
	return ret;
}

/*** ---------------------------------------------------------------------- ***/

int choose_file(GtkWidget *parent, char **name, gboolean must_exist, const char *title, const char *filter)
{
	GtkFileChooserDialog *selector;
	FILE_CHOOSER *info;
	GSList *filters, *f;
	
	parent = gtk_widget_get_toplevel(parent);

	if (choose_file_selector == NULL)
		choose_file_selector = GTK_FILE_CHOOSER_DIALOG(
			gtk_file_chooser_dialog_new(title,
			GTK_WINDOW(parent),
			GTK_FILE_CHOOSER_ACTION_OPEN,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
			GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
			NULL));
	selector = choose_file_selector;
	g_object_set_data(G_OBJECT(selector), "udoshell_window_type", NO_CONST("fileselector"));
	
	if (!empty(*name))
		gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(selector), *name);

	info = g_new0(FILE_CHOOSER, 1);
	info->name = name;
	info->selector = selector;
	info->ok = FALSE;
	info->done = FALSE;
	gtk_signal_connect(GTK_OBJECT(selector), "response", GTK_SIGNAL_FUNC(choose_file_response), (gpointer) info);
	gtk_signal_connect(GTK_OBJECT(selector), "destroy", GTK_SIGNAL_FUNC(choose_file_destroyed), (gpointer) info);

	if (must_exist)
		gtk_file_chooser_set_action(GTK_FILE_CHOOSER(selector), GTK_FILE_CHOOSER_ACTION_OPEN);
	else
		gtk_file_chooser_set_action(GTK_FILE_CHOOSER(selector), GTK_FILE_CHOOSER_ACTION_SAVE);

	gtk_window_set_title(GTK_WINDOW(selector), title);
	gtk_window_set_modal(GTK_WINDOW(selector), TRUE);
	gtk_widget_show(GTK_WIDGET(selector));

	/*
	 * clear old list of filters
	 */
	filters = gtk_file_chooser_list_filters(GTK_FILE_CHOOSER(selector));
	for (f = filters; f != NULL; f = f->next)
		gtk_file_chooser_remove_filter(GTK_FILE_CHOOSER(selector), (GtkFileFilter *)f->data);
	g_slist_free(filters);

	/*
	 * create new list of filters
	 */
	if (!empty(filter))
	{
		char **filterlist = g_strsplit(filter, "\n", 0);
		int i, j;
		char *displayname;
		GtkFileFilter *filefilter;
		char **patterns;
		
		for (i = 0; filterlist != NULL && filterlist[i] != NULL; i++)
		{
			if (empty(filterlist[i]))
				continue;
			filefilter = gtk_file_filter_new();
			displayname = strchr(filterlist[i], '|');
			if (displayname != NULL)
			{
				*displayname++ = '\0';
				gtk_file_filter_set_name(filefilter, displayname);
			} else
			{
				gtk_file_filter_set_name(filefilter, filterlist[i]);
			}
			patterns = g_strsplit(filterlist[i], " ", 0);
			for (j = 0; patterns != NULL && patterns[j] != NULL; j++)
			{
				if (strcmp(patterns[j], "*.*") == 0)
					strcpy(patterns[j], "*");
				if (strcmp(patterns[j], "*.exe") == 0)
					gtk_file_filter_add_custom(filefilter, GTK_FILE_FILTER_FILENAME, filter_exe, (gpointer) info, NULL);
				else
					gtk_file_filter_add_pattern(filefilter, patterns[j]);
			}
			g_strfreev(patterns);
			gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(selector), filefilter);
		}
		g_strfreev(filterlist);
	}
	
	while (choose_file_selector != NULL && !info->done)
	{
		if (gtk_main_iteration())
			break;
	}
	if (choose_file_selector != NULL && info->done && info->ok)
	{
		return TRUE;
	}
	return FALSE;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

gboolean strreplace(char *source, const char *replace, const char *by)
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
