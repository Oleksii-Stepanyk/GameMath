#ifndef SYSTEM_CHECK_H
#define SYSTEM_CHECK_H

#include <inttypes.h>

static_assert(sizeof(float) == sizeof(uint32_t), "float must be 32-bit");
static_assert(sizeof(double) == sizeof(uint64_t), "double must be 64-bit");

#endif // SYSTEM_CHECK_H