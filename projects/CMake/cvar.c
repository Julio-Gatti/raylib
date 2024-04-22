#include "cvar.h"
#include "cmd.h"

#include <stdarg.h>
#include <stdlib.h>

static cvar_t *cvar_vars;

int Con_Printf(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    int n = vprintf(fmt, args);
    va_end(args);

    return n;
}

void Cvar_RegisterVariable(cvar_t *variable)
{
    // char *oldstr;

    // first check to see if it has allready been defined
    if (Cvar_FindVar(variable->name))
    {
        Con_Printf("Can't register variable %s, already defined\n", variable->name);
        return;
    }

    // check for overlap with a command
    if (Cmd_Exists(variable->name))
    {
        Con_Printf("Cvar_RegisterVariable: %s is a command\n", variable->name);
        return;
    }

    // copy the value off, because future sets will Z_Free it
    // oldstr = variable->string;
    // variable->string = malloc(strlen(variable->string) + 1);
    // strcpy(variable->string, oldstr);

    if (variable->flags & CVAR_INTEGER)
    {
        variable->integer = atoi(variable->string);
    }
    else if (variable->flags & CVAR_FLOAT)
    {
        variable->value = (float)atof(variable->string);
    }
    else
    {
        variable->integer = atoi(variable->string);
    }

#ifndef NDEBUG
    //printf("%s \"%s\" (%f)\n", variable->name, variable->string, variable->value);
#endif

    // link the variable in
    variable->next = cvar_vars;
    cvar_vars = variable;
}

void Cvar_WriteVariables(FILE *f)
{
    cvar_t *var;

    for (var = cvar_vars; var; var = var->next)
        if (var->flags & CVAR_ARCHIVE)
            fprintf(f, "%s \"%s\"\n", var->name, var->string);
}

cvar_t *Cvar_FindVar(const char *var_name)
{
    cvar_t *var;

    for (var = cvar_vars; var; var = var->next)
        if (!strcmp(var_name, var->name))
            return var;

    return NULL;
}
