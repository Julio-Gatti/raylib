#pragma once

#ifdef __cplusplus
#else
#include <stdbool.h>
#endif

typedef void (*xcommand_t)(int argc, char *argv[]);

#ifdef __cplusplus
extern "C"
{
#endif
    bool Cmd_Exists(const char *cmd_name);
#ifdef __cplusplus
}
#endif
