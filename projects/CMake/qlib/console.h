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

/// @name Output
/// @{

int Con_Printf(const char *fmt, ...);

/// @}

/// @name Input
/// @{

extern const char* con_input_prefix;

/// Tokenize command-line arguments
/// @return Argument count
int Con_Tokenize(char *c, char *argv[], size_t argmax);
void Con_Submit(char *input, size_t size, uint *len);
void Con_Complete(char *input, size_t size, uint *len);
int Con_Exec(const char *path);

/// @}

#if __cplusplus
}
namespace Console
{
}
#endif
