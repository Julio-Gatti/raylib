#include "cmd.h"

#include <string.h>

cmd_function_t *cmd_functions;

bool Cmd_Exists(const char *cmd_name)
{
    cmd_function_t *cmd;

    for (cmd = cmd_functions; cmd; cmd = cmd->next) {
        if (strcasecmp(cmd_name, cmd->name) == 0)
            return true;
    }

    return false;
}
