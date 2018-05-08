void CenterWindow(GtkWidget *hwnd);

void my_fsplit(const char *cs, char *drive, char *path, char *filename, char *suffix);
int choose_file(GtkWidget *parent, char **name, gboolean must_exist, const char *title, const char *filter);

gboolean strreplace(char *source, const char *replace, const char *by);

void show_dialog(GtkWidget *parent, const char *type, const char *message, void (*ok_fn)(GtkWidget *widget, gpointer user_data), gpointer user_data);
