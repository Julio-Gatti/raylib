#pragma once

#include "quakedef.h"

#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef vec_t vec4_t[4];

#ifdef __cplusplus
template <typename T = vec_t>
struct tvec {
    using value_type = T;
    using size_type  = size_t;

    static constexpr T epsilon() noexcept
    {
        return static_cast<T>(0.0001);
    }
};
#endif

struct vec2
#ifdef __cplusplus
    : tvec<vec_t>
#endif
{
    union {
        struct {
            vec_t x;
            vec_t y;
        };
        struct {
            vec_t r;
            vec_t g;
        };
    };

#ifdef __cplusplus
    inline vec2() noexcept {}
    constexpr explicit vec2(vec_t xy) noexcept : x(xy), y(xy) {}

    /// Cross product
    vec2 cross(const vec2 &w) const noexcept;
    /// Dot product
    vec_t dot(const vec2 &w) const noexcept;
    vec2 &negate() noexcept;
    /// Normalize (in place)
    vec2 &normalize() noexcept;
    /// Length
    vec_t magnitude() const noexcept;

    std::string string() const;
    inline operator std::string() const { return string(); }
#endif
};

struct vec3
#ifdef __cplusplus
    : tvec<vec_t>
#endif
{
    union {
        struct {
            vec_t x;
            vec_t y;
            vec_t z;
        };
        struct {
            vec_t r;
            vec_t g;
            vec_t b;
        };
    };

#ifdef __cplusplus
    inline vec3() noexcept {}
    constexpr explicit vec3(vec_t xyz) noexcept : x(xyz), y(xyz), z(xyz) {}

    /// Cross product
    vec3 cross(const vec2 &w) const noexcept;
    /// Dot product
    vec_t dot(const vec3 &w) const noexcept;
    vec3 &negate() noexcept;
    /// Normalize (in place)
    vec3 &normalize() noexcept;
    /// Length
    vec_t magnitude() const noexcept;

    std::string string() const;
    inline operator std::string() const { return string(); }
#endif
};

struct vec4
#ifdef __cplusplus
    : tvec<vec_t>
#endif
{
    union {
        struct {
            vec_t x;
            vec_t y;
            vec_t z;
            vec_t w;
        };
        struct {
            vec_t r;
            vec_t g;
            vec_t b;
            vec_t a;
        };
    };

#ifdef __cplusplus
    inline vec4() noexcept {}
    constexpr explicit vec4(vec_t xyzw) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}

    /// Cross product
    vec4 cross(const vec2 &w) const noexcept;
    /// Dot product
    vec_t dot(const vec4 &w) const noexcept;
    vec4 &negate() noexcept;
    /// Normalize (in place)
    vec4 &normalize() noexcept;
    /// Length
    vec_t magnitude() const noexcept;

    std::string string() const;
    inline operator std::string() const { return string(); }
#endif
};
