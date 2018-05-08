/*****************************************************************************
 * HELP.H
 *****************************************************************************/

#ifndef __HELP_H__
#define __HELP_H__

#define HELP_SUPPORT_CHM 1

gboolean Help_Show(GtkWidget *parent, const char *filename, const char *entry);
void Help_Contents(GtkWidget *parent, const char *filename);
void Help_Index(GtkWidget *parent, const char *filename);
void Help_Using_Help(GtkWidget *parent, const char *filename);
void Help_Exit(void);
void Help_Init(void);

#endif /* __HELP_H__ */
