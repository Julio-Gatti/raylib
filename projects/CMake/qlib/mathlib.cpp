#include "mathlib.h"

vec_t vec2::dot(const vec2 &w) const noexcept
{
    return (x * w.x) + (y * w.y);
}

vec_t vec3::dot(const vec3 &w) const noexcept
{
    return (x * w.x) + (y * w.y) + (z * w.z);
}

vec_t vec4::dot(const vec4 &w) const noexcept
{
    return (x * w.x) + (y * w.y) + (z * w.z) + (this->w * w.w);
}

vec2 &vec2::normalize() noexcept
{
    value_type len = magnitude();

    if (abs(len) < epsilon()) {
        return *this;
    }

    len = 1.0 / len;
    x *= len;
    y *= len;

    return *this;
}

vec3 &vec3::normalize() noexcept
{
    value_type len = magnitude();

    if (abs(len) < epsilon()) {
        return *this;
    }

    len = 1.0 / len;
    x *= len;
    y *= len;
    z *= len;

    return *this;
}

vec4 &vec4::normalize() noexcept
{
    value_type len = magnitude();

    if (abs(len) < epsilon()) {
        return *this;
    }

    len = 1.0 / len;
    x *= len;
    y *= len;
    z *= len;
    w *= len;

    return *this;
}

vec_t vec2::magnitude() const noexcept
{
    return sqrtf((x * x) + (y * y));
}

vec_t vec3::magnitude() const noexcept
{
    return sqrtf((x * x) + (y * y) + (z * z));
}

vec_t vec4::magnitude() const noexcept
{
    return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

std::string vec2::string() const
{
    char s[32];

    snprintf(s, sizeof(s), "\"%f %f\"", x, y);

    return s;
}

std::string vec3::string() const
{
    char s[32];

    snprintf(s, sizeof(s), "\"%f %f %f\"", x, y, z);

    return s;
}

std::string vec4::string() const
{
    char s[32];

    snprintf(s, sizeof(s), "\"%f %f %f %f\"", x, y, z, w);

    return s;
}
