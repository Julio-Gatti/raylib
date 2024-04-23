#pragma once

#ifdef __cplusplus
#include <cassert>
#include <cstddef>
#include <string>
#else
// C99
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
// Pre C99
// enum qboolean {true,false};
#endif

typedef unsigned char byte; ///< Unsigned byte (0 to 255, at least 8 bits)
typedef unsigned int uint;  ///< Unsigned integer (0 to `UINT_MAX`, 32 bits)

#define MAX_STRING_CHARS 1024

#define KEY_TILDE KEY_GRAVE
