/*****************************************************************************
 * HELP.H
 *****************************************************************************/

#ifndef __HELP_H__
#define __HELP_H__

#define HELP_SUPPORT_CHM 1

#define HELP_FILE "udosh.chm"

BOOL Help_Show(HWND parent, const char *filename, const char *entry);
void Help_Contents(HWND parent, const char *filename);
void Help_Index(HWND parent, const char *filename);
void Help_Using_Help(HWND parent, const char *filename);
void Help_Exit(void);

#endif /* __HELP_H__ */
