void Status_Open(GtkWidget *parent);
void Status_Wait(void);
void Status_Close(void);
gboolean Status_Init(void);
void Status_Exit(void);
void Status_SetRange(long minVal, long maxVal);
void Status_SetPos(long pos);

void show_status_info_force(const char *s, gboolean force);
