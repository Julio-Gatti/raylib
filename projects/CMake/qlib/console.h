#pragma once

#include "quakedef.h"

#if __cplusplus
extern "C" {
#endif

#ifndef _WIN32
typedef unsigned char BOOL;
typedef unsigned short WORD;
typedef HANDLE;
BOOL SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes);
#endif

/// Output
int Con_Printf(const char *fmt, ...);
/// Input
void Con_Submit(char *input, size_t size, uint *len);
void Con_Complete(char *input, size_t size, uint *len);
int Con_Exec(const char *path);

#if __cplusplus
}
#endif
