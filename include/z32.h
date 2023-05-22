#ifndef Z32_H
#define Z32_H

#include <stddef.h>
#include <stdint.h>
#include <utf.h>

#ifdef __cplusplus
extern "C" {
#endif

int
z32_encode (const uint8_t *buffer, size_t buffer_len, utf8_t *string, size_t *string_len);

int
z32_decode (const utf8_t *string, size_t string_len, uint8_t *buffer, size_t *buffer_len);

#ifdef __cplusplus
}
#endif

#endif // Z32_H
