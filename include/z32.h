#ifndef Z32_H
#define Z32_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int
z32_encode (const char *buffer, size_t buffer_len, char *string, size_t *string_len);

int
z32_decode (const char *string, size_t string_len, char *buffer, size_t *buffer_len);

#ifdef __cplusplus
}
#endif

#endif // Z32_H
