void CenterWindow(HWND hwnd);

void DlgGetText(HWND hwnd, int id, char *buf, int maxlen);
void DlgSetText(HWND hwnd, int id, char *buf);
BOOL DlgGetButton(HWND hwnd, int id);
void DlgSetButton(HWND hwnd, int id, BOOL check);
void DlgEnable(HWND hwnd, int id, BOOL enable);

void my_fsplit(const char *cs, char *drive, char *path, char *filename, char *suffix);
int choose_file(HWND parent, char *name, size_t maxSize, BOOL must_exist, const char *title, const char *filter);

BOOL strreplace(char *source, const char *replace, const char *by);

int MessageBoxParam(HWND parent, UINT style, const char *format, ...);
