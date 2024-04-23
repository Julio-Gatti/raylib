#include "console.h"
#include "cmd.h"
#include "cvar.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
BOOL SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes)
{
}
#endif

const char *con_input_prefix = "]";

int Con_Tokenize(char *c, char *argv[], size_t argmax)
{
    assert(c != NULL);

    int argc = 0;

    // assume some kind of termination
    for (; *c; ++c) {
        // CR or LF
        if (*c == '\r' || *c == '\n') {
            *c = '\0';
            return argc;
        }
        // single line comment
        else if (*c == '#') {
            *c = '\0';
            return argc;
        }
        // whitespace
        else if (*c == ' ' || *c == '\t') {
            // skip until
            *c = '\0';
            continue;
        }
        // normal character
        else {
            // argument
            if (argc < argmax) {
                argv[argc++] = c;
                for (; *c; ++c) {
                    // CR or LF
                    if (*c == '\r' || *c == '\n') {
                        *c = '\0';
                        return argc;
                    }
                    // whitespace
                    else if (*c == ' ' || *c == '\t') {
                        *c = '\0';
                        break;
                    }
                }
            }
        }
    }

    return argc;
}

int Con_Printf(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    int n = vprintf(fmt, args);
    va_end(args);

    return n;
}

void Con_Submit(char *input, size_t size, uint *len)
{
    assert(input != NULL);

    if (input[0] == '\0') {
        return;
    }

    char *argv[32];
    int argc = Con_Tokenize(input, argv, sizeof(argv) / sizeof(argv[0]));

    for (cmd_function_t *cmd = cmd_functions; cmd; cmd = cmd->next) {
        if (strcasecmp(cmd->name, input) == 0) {
            cmd->function(argc, argv);
            memset(input, '\0', size);
            if (len) {
                *len = '\0';
            }
            return;
        }
    }

    cvar_t *var = Cvar_FindVar(argv[0]);
    if (var) {
        if (argc > 1) {
            free(var->string);
            size_t size = strlen(argv[1] + 1);
            var->string = malloc(size);
            strncpy(var->string, argv[1], size);
            if (var->flags & CVAR_FLOAT) {
                var->value = atof(var->string);
            } else if (var->flags & CVAR_BOOLEAN) {
                var->boolean = var->string[0] != 'f';
            } else {
                var->integer = atoi(var->string);
            }
        } else {
            Con_Printf("%s is \"%s\"\n", var->name, var->string);
        }
        memset(input, '\0', size);
        if (len) {
            *len = '\0';
        }
        return;
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
    Con_Printf("unknown command: %s\n", input);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    memset(input, '\0', size);
    if (len) {
        *len = '\0';
    }
}

void Con_Complete(char *input, size_t size, uint *len)
{
    assert(input != NULL);
}

int Con_Exec(const char *path)
{
    assert(path != NULL);

    FILE *f;
    char line[MAX_STRING_CHARS];

    if ((f = fopen(path, "r")) == NULL) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
        Con_Printf("error: %s\n", strerror(errno));
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        return false;
    }

    while (fgets(line, sizeof(line), f)) {
        Con_Submit(line, sizeof(line), NULL);
    }

    return true;
}
