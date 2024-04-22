#include "cmd.h"

#include <string.h>

struct cmd_function_s
{
    char *name;
    xcommand_t function;
    struct cmd_function_s *next;
#ifdef __cplusplus
#endif
};
typedef struct cmd_function_s cmd_function_t;

static cmd_function_t *cmd_functions;

bool Cmd_Exists(const char *cmd_name)
{
    cmd_function_t *cmd;

    for (cmd = cmd_functions; cmd; cmd = cmd->next)
    {
        if (strcasecmp(cmd_name, cmd->name) == 0)
            return true;
    }

    return false;
}
