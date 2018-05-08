#include "udogtk.h"
#include <import.h>
#include <constant.h>
#include <chr.h>
#include <file.h>
#include <msg.h>
#include <udo.h>
#include <export.h>
#include <gui.h>
#include "guish.h"
#include "misc.h"

typedef struct {
	GtkWidget *parent;
	GtkWidget *hwnd;
	
	long minVal;
	long maxVal;
	long pos;
	
	GtkWidget *pass_label;
	GtkWidget *info_label;
	GtkWidget *file_label;
	GtkWidget *node_label;
	GtkWidget *msg_window;
	GtkWidget *msg_text;
	GtkTextMark *end_mark;
	
	GtkWidget *progress_bar;
	GtkWidget *cancel_button;
} Status;

static Status *status;
static gboolean cancel_pressed;
static gboolean status_done;

#define get_main_wind() NULL

/*** ---------------------------------------------------------------------- ***/

static char *fix_udo_to_utf8(const char *s)
{
	char *txt;
	
	/*
	 * UDO currently is very inconsistent with text passed to the log functions.
	 * Sometimes they are already recoded to the target character set,
	 * sometimes they contain filenames in the locale encoding and
	 * sometime they contain input text in the source encoding.
	 * Try to convert everything to utf8 before displaying it.
	 */
	if (s == NULL)
		return NULL;
	if (g_utf8_validate(s, -1, NULL))
		return g_strdup(s);
	txt = g_locale_to_utf8(s, -1, NULL, NULL, NULL);
	if (txt != NULL)
		return txt;
	txt = g_convert(s, -1, "UTF-8", chr_codepage_charset_name(iEncodingSource), NULL, NULL, NULL);
	return txt;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

void show_status_info_force(const char *s, gboolean force)
{
	char *msg;
	
	if (((bOutOpened || bTestmode) && !bBeQuiet) || force)
	{
		if (!empty(s) && status != NULL)
		{
			msg = fix_udo_to_utf8(s);
			if (msg != NULL)
			{
				gtk_label_set_text(GTK_LABEL(status->info_label), msg);
				gdk_window_process_updates(gtk_widget_get_window(status->hwnd), TRUE);
				g_free(msg);
			}
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

void show_status_info(const char *s)
{
	show_status_info_force(s, FALSE);
}

/*** ---------------------------------------------------------------------- ***/

void show_status_loginfo(const char *s)
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

void show_status_pass(const char *s)
{
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		if (!empty(s) && status != NULL)
		{
			gtk_label_set_text(GTK_LABEL(status->pass_label), s);
			gtk_label_set_text(GTK_LABEL(status->info_label), "");
			gdk_window_process_updates(gtk_widget_get_window(status->hwnd), TRUE);
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

void show_status_udo2udo(FILE_LINENO Pass2Lines, const char *s)
{
	show_status_file_2(Pass2Lines, s);
}

/*** ---------------------------------------------------------------------- ***/

void show_status_node(const char *numbers, const char *name)
{
	char *msg;
	
	UNUSED(numbers);
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		if (!empty(name))
		{
			msg = fix_udo_to_utf8(name);
			if (msg != NULL)
			{
				gtk_label_set_text(GTK_LABEL(status->node_label), msg);
				gdk_window_process_updates(gtk_widget_get_window(status->hwnd), TRUE);
				g_free(msg);
			}
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

void show_status_file_1(FILE_LINENO Pass1Lines, const char *s)
{
	char *msg;
	
	UNUSED(Pass1Lines);
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		if (!empty(s))
		{
			msg = fix_udo_to_utf8(s);
			if (msg != NULL)
			{
				gtk_label_set_text(GTK_LABEL(status->file_label), msg);
				gdk_window_process_updates(gtk_widget_get_window(status->hwnd), TRUE);
				g_free(msg);
			}
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

void show_status_file_2(FILE_LINENO Pass2Lines, const char *s)
{
	show_status_file_1(Pass2Lines, s);
}

/*** ---------------------------------------------------------------------- ***/

void show_status_percent(FILE_LINENO Pass1Lines, FILE_LINENO Pass2Lines)
{
	if ((bOutOpened || bTestmode) && !bBeQuiet)
	{
		Status_SetRange(0, Pass1Lines);
		Status_SetPos(Pass2Lines);
	}
}

/*** ---------------------------------------------------------------------- ***/

void show_status_errors(const char *s)
{
	UNUSED(s);
}

/*** ---------------------------------------------------------------------- ***/

void show_logln_message(const char *s)
{
	char *msg;
	GtkTextIter iter;
	GtkTextBuffer *buffer;
	
	if (!empty(s) && status != NULL)
	{
		msg = fix_udo_to_utf8(s);
		if (msg != NULL)
		{
			buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(status->msg_text));
			gtk_text_buffer_get_iter_at_mark(buffer, &iter, status->end_mark);
			if (gtk_text_buffer_get_line_count(buffer) != 0)
				gtk_text_buffer_insert(buffer, &iter, "\n", -1);
			gtk_text_buffer_insert(buffer, &iter, msg, -1);
			gtk_widget_show(status->msg_window);
			gtk_text_view_scroll_mark_onscreen(GTK_TEXT_VIEW(status->msg_text), status->end_mark);
			g_free(msg);
			gdk_window_process_updates(gtk_widget_get_window(status->hwnd), TRUE);
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

void warning_err_logfile(void)
{
	error_open_logfile(file_lookup(sLogfull));
	show_dialog(get_main_wind(), GTK_STOCK_DIALOG_ERROR, _("UDO can't create log file"), NULL, NULL);
}

/*** ---------------------------------------------------------------------- ***/

void warning_err_treefile(void)
{
	error_open_treefile(file_lookup(sTreefull));
	show_dialog(get_main_wind(), GTK_STOCK_DIALOG_ERROR, _("UDO can't create tree file"), NULL, NULL);
}

/*** ---------------------------------------------------------------------- ***/

void warning_err_uprfile(void)
{
	error_open_uprfile(file_lookup(sUPRfull));
	show_dialog(get_main_wind(), GTK_STOCK_DIALOG_ERROR, _("UDO can't create project file"), NULL, NULL);
}

/*** ---------------------------------------------------------------------- ***/

void warning_err_hypfile(void)
{
	error_open_hypfile(file_lookup(sHypfull));
	show_dialog(get_main_wind(), GTK_STOCK_DIALOG_ERROR, _("UDO can't create hyphen file"), NULL, NULL);
}

/*** ---------------------------------------------------------------------- ***/

void warning_err_destination(void)
{
	show_dialog(get_main_wind(), GTK_STOCK_DIALOG_ERROR, _("UDO can't create output file"), NULL, NULL);
}

/*** ---------------------------------------------------------------------- ***/

void multitasking_interrupt(void)
{
	while (gtk_events_pending() && !gtk_main_iteration())
		;
}

/*** ---------------------------------------------------------------------- ***/

void unregistered_copyright(void)
{
	/* Dummy-Funktion */
}

/*** ---------------------------------------------------------------------- ***/

_BOOL break_action(void)
{
	return cancel_pressed;
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void status_update(Status *status)
{
	double fraction;
	
	if (status->pos < status->minVal)
		status->pos = status->minVal;
	else if (status->pos > status->maxVal)
		status->pos = status->maxVal;
	if (status->maxVal != status->minVal)
	{
		fraction = 1.0 * (double)(status->pos - status->minVal) / (double)(status->maxVal - status->minVal);
		gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(status->progress_bar), fraction);
		gtk_widget_queue_draw(status->progress_bar);
		gdk_window_process_updates(gtk_widget_get_window(status->hwnd), TRUE);
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void status_destroyed(GtkWidget *widget, void *userdata)
{
	UNUSED(widget);
	if (userdata == status)
	{
		status = NULL;
		if (!status_done)
			cancel_pressed = TRUE;
	}
	g_free(userdata);
}

/*** ---------------------------------------------------------------------- ***/

static void status_response(GtkDialog *dialog, gint response_id, gpointer userdata)
{
	UNUSED(dialog);
	UNUSED(userdata);
	
	switch (response_id)
	{
	case GTK_RESPONSE_OK:
	case GTK_RESPONSE_APPLY:
	case GTK_RESPONSE_ACCEPT:
	case GTK_RESPONSE_YES:
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_CLOSE:
	case GTK_RESPONSE_NO:
	case GTK_RESPONSE_DELETE_EVENT:
		if (status != NULL)
			gtk_widget_destroy(status->hwnd);
		break;
	}
}

/*** ---------------------------------------------------------------------- ***/

void Status_Open(GtkWidget *parent)
{
	GtkWidget *dialog;
	GtkWidget *label;
	GtkWidget *button;
	GtkWidget *vbox, *hbox;
	GtkTextIter iter;
	
	status = g_new0(Status, 1);
	status_done = FALSE;
	cancel_pressed = FALSE;
	
	parent = gtk_widget_get_toplevel(parent);

	status->parent = parent;
	status->hwnd = dialog = gtk_dialog_new();
	g_object_set_data(G_OBJECT(status->hwnd), "udoshell_window_type", NO_CONST("status-dialog"));
	status->minVal = 0;
	status->maxVal = 1;
	
	vbox = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
	status->pass_label = label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
	gtk_misc_set_alignment(GTK_MISC(label), 0.5, 0.5);
	gtk_label_set_use_markup(GTK_LABEL(label), FALSE);
	gtk_widget_show(label);
	
	status->info_label = label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
	gtk_misc_set_alignment(GTK_MISC(label), 0.5, 0.5);
	gtk_label_set_use_markup(GTK_LABEL(label), FALSE);
	gtk_widget_show(label);
	
	status->file_label = label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
	gtk_misc_set_alignment(GTK_MISC(label), 0.5, 0.5);
	gtk_label_set_use_markup(GTK_LABEL(label), FALSE);
	gtk_widget_show(label);
	
	status->node_label = label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
	gtk_misc_set_alignment(GTK_MISC(label), 0.5, 0.5);
	gtk_label_set_use_markup(GTK_LABEL(label), FALSE);
	gtk_widget_show(label);
	
	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, TRUE, 0);
	gtk_misc_set_alignment(GTK_MISC(label), 0.5, 0.5);
	gtk_label_set_use_markup(GTK_LABEL(label), FALSE);
	gtk_widget_show(label);
	
	status->progress_bar = gtk_progress_bar_new();
	gtk_progress_bar_set_bar_style(GTK_PROGRESS_BAR(status->progress_bar), GTK_PROGRESS_CONTINUOUS);
	gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(status->progress_bar), GTK_PROGRESS_LEFT_TO_RIGHT);
	gtk_box_pack_start(GTK_BOX(vbox), status->progress_bar, FALSE, TRUE, 0);
	gtk_widget_show(status->progress_bar);
	
	hbox = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(hbox), 0);
	gtk_widget_show(hbox);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, TRUE, TRUE, 0);
	
	status->msg_window = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(status->msg_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(status->msg_window), GTK_SHADOW_IN);
	status->msg_text = gtk_text_view_new();
	gtk_widget_show(status->msg_text);
	gtk_text_buffer_get_iter_at_offset(gtk_text_view_get_buffer(GTK_TEXT_VIEW(status->msg_text)), &iter, -1);
	status->end_mark = gtk_text_buffer_create_mark(gtk_text_view_get_buffer(GTK_TEXT_VIEW(status->msg_text)), NULL, &iter, FALSE);
	gtk_container_add(GTK_CONTAINER(status->msg_window), status->msg_text);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(status->msg_text), FALSE);
	gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(status->msg_text), GTK_WRAP_NONE); 
	gtk_widget_set_can_focus(status->msg_text, FALSE);
	gtk_box_pack_start(GTK_BOX(hbox), status->msg_window, TRUE, TRUE, 0);
	
	status->cancel_button = button = gtk_button_new_from_stock(GTK_STOCK_CANCEL);
	gtk_dialog_add_action_widget(GTK_DIALOG(dialog), button, GTK_RESPONSE_CANCEL);
	
	gtk_widget_set_can_default(button, TRUE);
	gtk_widget_show(button);
	gtk_widget_grab_focus(button);
	
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 10);
	gtk_window_set_title(GTK_WINDOW(dialog), gl_program_name);

	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(parent));
	CenterWindow(dialog);
	
	gtk_widget_show(dialog);
	
	gtk_signal_connect(GTK_OBJECT(dialog), "destroy", GTK_SIGNAL_FUNC(status_destroyed), (gpointer) status);

	gtk_signal_connect(GTK_OBJECT(dialog), "response", GTK_SIGNAL_FUNC(status_response), (gpointer) status);
	
	gtk_window_present(GTK_WINDOW(dialog));
}

/*** ---------------------------------------------------------------------- ***/

void Status_Wait(void)
{
	if (status != NULL)
	{
		status_done = TRUE;
		gtk_button_set_label(GTK_BUTTON(status->cancel_button), GTK_STOCK_OK);
		while (status != NULL)
		{
			gtk_dialog_run(GTK_DIALOG(status->hwnd));
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

void Status_Close(void)
{
	if (status != NULL)
		gtk_widget_destroy(status->hwnd);
}

/*** ---------------------------------------------------------------------- ***/

gboolean Status_Init(void)
{
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

void Status_Exit(void)
{
	if (status != NULL)
		gtk_widget_destroy(status->hwnd);
}

/*** ---------------------------------------------------------------------- ***/

void Status_SetRange(long minVal, long maxVal)
{
	if (status != NULL)
	{
		if (maxVal < minVal)
			maxVal = minVal;
		status->minVal = minVal;
		status->maxVal = maxVal;
		status_update(status);
	}
}

/*** ---------------------------------------------------------------------- ***/

void Status_SetPos(long pos)
{
	if (status != NULL)
	{
		status->pos = pos;
		status_update(status);
	}
}
