#include "cvar.h"

#include <cstring>

cvar_s::cvar_s(const char *name, const char *string, flags_t flags, const char *description) : flags(flags)
{
    size_t cap = strlen(name) + 1;
    this->name = new char[cap];
    strncpy(this->name, name, cap);

    cap          = strlen(string) + 1;
    this->string = new char[cap];
    strncpy(this->string, string, cap);

    Cvar_RegisterVariable(this);
}

cvar_s::cvar_s(const char *name, const std::string &string, flags_t flags, const char *description) : flags(flags)
{
    size_t cap = strlen(name) + 1;
    this->name = new char[cap];
    strncpy(this->name, name, cap);

    cap          = string.length() + 1;
    this->string = new char[cap];
    strncpy(this->string, string.c_str(), cap);

    Cvar_RegisterVariable(this);
}

cvar_s::~cvar_s()
{
    if (name) {
        delete[] name;
    }
}
