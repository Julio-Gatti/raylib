#include "cmd.h"
#include "console.h"

#include <cstring>

static void help_fn(int argc, char *argv[])
{
    cmd_function_t *cmd;

    for (cmd = cmd_functions; cmd; cmd = cmd->next) {
        Con_Printf("%s\n", cmd->name);
    }
}
static cmd_function_t help_cmd = {"help", help_fn};

static void parse_fn(int argc, char *argv[])
{
    for (int i = 0; i < argc; ++i) {
        printf("%d: %s\n", i, argv[i]);
    }
    printf("\n");
}
static cmd_function_t parse_cmd = {"parse", parse_fn};

cmd_function_s::cmd_function_s(const char *name, xcommand_t function, flags_t flags, const char *description)
    : function(function), flags(flags), description(description)
{
    size_t cap = strlen(name) + 1;
    this->name = new char[cap];
    strncpy(this->name, name, cap);

#ifndef NDEBUG
    Con_Printf("void %s %p\n", name, function);
#endif

    // link the function in
    this->next    = cmd_functions;
    cmd_functions = this;
}

cmd_function_s::~cmd_function_s()
{
    if (name) {
        delete[] name;
    }
}
