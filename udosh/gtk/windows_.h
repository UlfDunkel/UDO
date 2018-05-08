#if defined(_WIN32) && !defined(__WIN32__)
#define __WIN32__ 1
#endif
#if defined(_WIN64) && !defined(__WIN64__)
# define __WIN64__ 1
#endif

#ifdef __WIN32__

#define WIN32_LEAN_AND_MEAN
#define STRICT
#define WINVER 0x0500
#define __SIMPLE_LOCALES__
#include <windows.h>
#include <shellapi.h>
#include <commdlg.h>
#include <cderr.h>


#define GetInstance()  ((HINSTANCE)GetModuleHandle(NULL))

#undef MAKEWPARAM
#define MAKEWPARAM(l, h) ((WPARAM)(((WORD)((DWORD_PTR)(l) & 0xffff)) | (((DWORD)((WORD)((DWORD_PTR)(h) & 0xffff)) << 16))))

#undef IS_INTRESOURCE
#define IS_INTRESOURCE(_r) ((((ULONG_PTR)(_r)) >> 16) == 0)

#endif /* __WIN32__ */
