#include "cvar.h"
#include "console.h"

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

cvar_s &cvar_s::operator=(const char *s) noexcept
{
    assert(s != nullptr);

    delete[] this->string;
    size_t size  = strlen(s) + 1;
    this->string = new char[size];
    strncpy(this->string, s, size);

    if (this->is_integer()) {
        this->integer = atoi(s);
    } else if (this->is_float()) {
        this->value = atof(s);
    } else if (this->is_boolean()) {
        this->boolean = s;
    }

    return *this;
}

cvar_s &cvar_s::operator=(const std::string &s) noexcept
{
    delete[] this->string;
    size_t size  = s.length() + 1;
    this->string = new char[size];
    strncpy(this->string, s.data(), size);

    if (this->is_integer()) {
        this->integer = atoi(s.data());
    } else if (this->is_float()) {
        this->value = atof(s.data());
    } else if (this->is_boolean()) {
        this->boolean = s.data();
    }

#ifndef NDEBUG
    Con_Printf("%s = \"%s\"\n", this->name, s.c_str());
#endif

    return *this;
}

cvar_s &cvar_s::operator=(const float f) noexcept
{
    if (this->is_integer()) {
        this->integer = f;
    } else if (this->is_float()) {
        this->value = f;
    } else if (this->is_boolean()) {
        this->boolean = f;
    }

    delete[] this->string;
    size_t size  = 32;
    this->string = new char[size];
    snprintf(this->string, size, "%f", f);

#ifndef NDEBUG
    Con_Printf("%s = %f\n", this->name, f);
#endif

    return *this;
}

cvar_s &cvar_s::operator=(const int i) noexcept
{
    if (this->is_integer()) {
        this->integer = i;
    } else if (this->is_float()) {
        this->value = i;
    } else if (this->is_boolean()) {
        this->boolean = i;
    }

    delete[] this->string;
    size_t size  = 32;
    this->string = new char[size];
    snprintf(this->string, size, "%d", i);

    return *this;
}

cvar_s &cvar_s::operator=(const bool b) noexcept
{
    if (this->is_integer()) {
        this->integer = b;
    } else if (this->is_float()) {
        this->value = b;
    } else if (this->is_boolean()) {
        this->boolean = b;
    }

    delete[] this->string;
    size_t size  = 8;
    this->string = new char[size];
    strncpy(this->string, b ? "true" : "false", size);

    return *this;
}

const char *cvar_s::type_name() const noexcept
{
    if (is_boolean())
        return "bool";
    else if (is_integer())
        return "int";
    else if (is_float())
        return "float";
    else
        return "char*";
}
