#ifndef CRASHHANDLER_H
#define CRASHHANDLER_H

#if defined (_WINDOWS) && !defined(SN_TARGET_PSP2) && !defined(PLATFORM_NX_ARM) && !defined(PLATFORM_NX)
#include <windows.h>
#include <Dbghelp.h>
#include <tchar.h>

LONG WINAPI unhandled_handler(struct _EXCEPTION_POINTERS* apExceptionInfo);
#endif

#endif