/// @file
/// @see
/// https://github.com/id-Software/Quake/blob/master/WinQuake/cvar.h

#pragma once

#include "quakedef.h"

#if __cplusplus
#include <cstdio>
#include <cstring>
#include <string>
#else
#include <stdio.h>
#include <string.h>
#endif

enum {
    CVAR_ARCHIVE = 1 << 0,
    CVAR_SERVER  = 1 << 1,
    CVAR_INTEGER = 1 << 2,
    CVAR_FLOAT   = 1 << 3,
    CVAR_BOOLEAN = 1 << 4,
    CVAR_STRING  = 1 << 5,
    CVAR_CHEAT   = 1 << 6,
};

/// Console variable
struct cvar_s {
    char *name;
    char *string;
    union {
        struct
        {
            bool archive;
            bool server;
        };
        unsigned int flags;
    };
    union {
        float value;
        int integer;
        bool boolean;
    };
    struct cvar_s *next;

#ifdef __cplusplus
    typedef unsigned int flags_t;

    cvar_s(const cvar_s &) = delete;
    cvar_s(const char *name, const char *string, flags_t flags = 0, const char *description = "");
    cvar_s(const char *name, const std::string &string, flags_t flags = 0, const char *description = "");
    ~cvar_s();

    cvar_s &operator=(const char *s) noexcept;
    cvar_s &operator=(const std::string &s) noexcept;
    cvar_s &operator=(float f) noexcept;
    cvar_s &operator=(int i) noexcept;
    cvar_s &operator=(bool b) noexcept;

    /// @name Type
    /// @{
    const char *type_name() const noexcept;
    constexpr bool is_boolean() const noexcept { return flags & CVAR_BOOLEAN; }
    constexpr bool is_integer() const noexcept { return flags & CVAR_INTEGER; }
    constexpr bool is_float() const noexcept { return flags & CVAR_FLOAT; }
    constexpr bool is_string() const noexcept { return flags & CVAR_STRING; }
    /// @}

    /// @name Implicit cast
    /// @{
    constexpr operator const char *() const noexcept { return string; }
    constexpr operator float() const noexcept { return value; }
    constexpr operator int() const noexcept { return integer; }
    constexpr operator bool() const noexcept { return boolean; }
    /// @}

    /// Explicit cast as conversion
    inline explicit operator std::string() const
    {
        return string;
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
extern "C" {
#endif

void Cvar_RegisterVariable(cvar_t *variable);
void Cvar_WriteVariables(FILE *f);
cvar_t *Cvar_FindVar(const char *var_name);

#if __cplusplus
}
#endif

#ifdef __cplusplus
/// Template console variable
template <typename T>
struct tcvar_t : cvar_t {
    using super      = cvar_t;
    using value_type = T;

    tcvar_t(const char *name, float value, flags_t flags = 0, const char *description = "")
        : super(name, std::to_string(value), flags | CVAR_FLOAT, description) {}

    tcvar_t(const char *name, int integer, flags_t flags = 0, const char *description = "")
        : super(name, std::to_string(integer), flags | CVAR_INTEGER, description) {}

    tcvar_t(const char *name, bool boolean, flags_t flags = 0, const char *description = "")
        : super(name, std::to_string(boolean), flags | CVAR_BOOLEAN, description) {}

    tcvar_t(const char *name, const char *string, flags_t flags = 0, const char *description = "")
        : super(name, string, flags, description) {}

    tcvar_t &operator=(bool b) noexcept
    {
        super::operator=(b);
        return *this;
    }
    tcvar_t &operator=(int i) noexcept
    {
        super::operator=(i);
        return *this;
    }
    tcvar_t &operator=(float f) noexcept
    {
        super::operator=(f);
        return *this;
    }
};
#endif
