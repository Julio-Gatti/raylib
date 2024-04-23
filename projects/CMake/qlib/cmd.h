#pragma once

#include "quakedef.h"

typedef void (*xcommand_t)(int argc, char *argv[]);

struct cmd_function_s {
    char *name;
    xcommand_t function;
    unsigned int flags;
    const char *description;
    struct cmd_function_s *next;
#ifdef __cplusplus
    typedef unsigned int flags_t;

    cmd_function_s(const char *name, xcommand_t function, flags_t flags = 0, const char *description = "");
    ~cmd_function_s();
#endif
};
typedef struct cmd_function_s cmd_function_t;

#ifdef __cplusplus
extern "C" {
#endif
extern cmd_function_t *cmd_functions;

bool Cmd_Exists(const char *cmd_name);
#ifdef __cplusplus
}
#endif
