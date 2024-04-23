#include "console.h"
#include "cmd.h"

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

    int argc     = 1;
    char *argv[] = {input};

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
