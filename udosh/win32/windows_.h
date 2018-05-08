#define WIN32_LEAN_AND_MEAN
#define STRICT
#define WINVER 0x0500
#define __SIMPLE_LOCALES__
#include <windows.h>


#define UNUSED(x) (void)(x)
#define LOCAL static
#define GLOBAL
#define GetInstance()  ((HINSTANCE)GetModuleHandle(NULL))


#undef MAKEWPARAM
#define MAKEWPARAM(l, h) ((WPARAM)(((WORD)((DWORD_PTR)(l) & 0xffff)) | (((DWORD)((WORD)((DWORD_PTR)(h) & 0xffff)) << 16))))

#undef IS_INTRESOURCE
#define IS_INTRESOURCE(_r) ((((ULONG_PTR)(_r)) >> 16) == 0)
