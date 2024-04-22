/// @file
/// @see
/// https://github.com/id-Software/Quake/blob/master/WinQuake/cvar.h

#pragma once

#if __cplusplus
    #include <cstdio>
    #include <cstring>
    #include <string>
#else
    #include <stdbool.h>
    #include <stdio.h>
    #include <string.h>
#endif

enum
{
    CVAR_ARCHIVE = 1 << 0,
    CVAR_SERVER  = 1 << 1,
    CVAR_INTEGER = 1 << 2,
    CVAR_FLOAT   = 1 << 3,
    CVAR_BOOLEAN = 1 << 4,
};

struct cvar_s
{
    char *name;
    char *string;
    union
    {
        struct
        {
            bool archive;
            bool server;
        };
        unsigned int flags;
    };
    union
    {
        float value;
        int integer;
        bool boolean;
    };
    struct cvar_s *next;

#ifdef __cplusplus
    typedef unsigned int flags_t;

    cvar_s(const char *name, const char *string, flags_t flags = 0, const char *description = "");
    cvar_s(const char *name, const std::string &string, flags_t flags = 0, const char *description = "");
    ~cvar_s();

    constexpr operator const char *() const noexcept
    {
        return string;
    }
    inline operator std::string() const
    {
        return string;
    }
    constexpr operator float() const noexcept
    {
        return value;
    }
    constexpr operator int() const noexcept
    {
        return integer;
    }
    constexpr operator bool() const noexcept
    {
        return boolean;
    }

    inline bool operator==(const char *s) const
    {
        return strcmp(this->string, s) == 0;
    }
    inline bool operator!=(const char *s) const
    {
        return strcmp(this->string, s) != 0;
    }
#endif
};
typedef struct cvar_s cvar_t;

#if __cplusplus
extern "C"
{
#endif
    int Con_Printf(const char *fmt, ...);
    void Cvar_RegisterVariable(cvar_t *variable);
    void Cvar_WriteVariables(FILE *f);
    cvar_t *Cvar_FindVar(const char *var_name);
#if __cplusplus
}
#endif

#ifdef __cplusplus
template <typename T>
struct tcvar_t : public cvar_t
{
    using super = cvar_t;

    tcvar_t(const char *name, float value, flags_t flags = 0, const char *description = "")
        : super(name, std::to_string(value), flags | CVAR_FLOAT, description)
    {
    }
    tcvar_t(const char *name, int value, flags_t flags = 0, const char *description = "")
        : super(name, std::to_string(value), flags | CVAR_INTEGER, description)
    {
    }
    tcvar_t(const char *name, bool value, flags_t flags = 0, const char *description = "")
        : super(name, std::to_string(value), flags | CVAR_BOOLEAN, description)
    {
    }
};
#endif
