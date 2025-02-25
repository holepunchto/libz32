#ifndef Z32_H
#define Z32_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <utf.h>

#ifdef __cplusplus
extern "C" {
#endif

static const char z32__alphabet[32] = "ybndrfg8ejkmcpqxot1uwisza345h769";

static const char z32__inverse_alphabet[256] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, 25, 26, 27, 30, 29, 7, 31, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 24, 1, 12, 3, 8, 5, 6, 28, 21, 9, 10, -1, 11, 2, 16, 13, 14, 4, 22, 17, 19, -1, 20, 15, 0, 23, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

static inline int
z32__encode_utf8(const uint8_t *buffer, size_t buffer_len, utf8_t *string, size_t *string_len) {
  size_t len = (size_t) ceil((double) buffer_len * 8.0 / 5.0);

  if (string == NULL) {
    *string_len = len;
    return 0;
  }

  if (*string_len < len) return -1;

  bool terminate = *string_len > len;

  *string_len = len;

  size_t k = 0;

  for (size_t i = 0, n = buffer_len; i < n; i += 5) {
    uint8_t chunk[5];

    for (size_t j = 0; j < 5; j++) {
      chunk[j] = i + j < n ? buffer[i + j] : 0;
    }

    string[k++] = z32__alphabet[(chunk[0] & 0xf8) >> 3];
    string[k++] = z32__alphabet[(chunk[0] & 0x07) << 2 | (chunk[1] & 0xc0) >> 6];

    if (i + 1 >= n) break;

    string[k++] = z32__alphabet[(chunk[1] & 0x3e) >> 1];
    string[k++] = z32__alphabet[(chunk[1] & 0x01) << 4 | (chunk[2] & 0xf0) >> 4];

    if (i + 2 >= n) break;

    string[k++] = z32__alphabet[(chunk[2] & 0x0f) << 1 | (chunk[3] & 0x80) >> 7];

    if (i + 3 >= n) break;

    string[k++] = z32__alphabet[(chunk[3] & 0x7c) >> 2];
    string[k++] = z32__alphabet[(chunk[3] & 0x03) << 3 | (chunk[4] & 0xe0) >> 5];

    if (i + 4 >= n) break;

    string[k++] = z32__alphabet[chunk[4] & 0x1f];
  }

  if (terminate) string[k] = '\0';

  return 0;
}

static inline int
z32__encode_utf16le(const uint8_t *buffer, size_t buffer_len, utf16_t *string, size_t *string_len) {
  size_t len = (size_t) ceil((double) buffer_len * 8.0 / 5.0);

  if (string == NULL) {
    *string_len = len;
    return 0;
  }

  if (*string_len < len) return -1;

  bool terminate = *string_len > len;

  *string_len = len;

  size_t k = 0;

  for (size_t i = 0, n = buffer_len; i < n; i += 5) {
    uint8_t chunk[5];

    for (size_t j = 0; j < 5; j++) {
      chunk[j] = i + j < n ? buffer[i + j] : 0;
    }

    string[k++] = z32__alphabet[(chunk[0] & 0xf8) >> 3];
    string[k++] = z32__alphabet[(chunk[0] & 0x07) << 2 | (chunk[1] & 0xc0) >> 6];

    if (i + 1 >= n) break;

    string[k++] = z32__alphabet[(chunk[1] & 0x3e) >> 1];
    string[k++] = z32__alphabet[(chunk[1] & 0x01) << 4 | (chunk[2] & 0xf0) >> 4];

    if (i + 2 >= n) break;

    string[k++] = z32__alphabet[(chunk[2] & 0x0f) << 1 | (chunk[3] & 0x80) >> 7];

    if (i + 3 >= n) break;

    string[k++] = z32__alphabet[(chunk[3] & 0x7c) >> 2];
    string[k++] = z32__alphabet[(chunk[3] & 0x03) << 3 | (chunk[4] & 0xe0) >> 5];

    if (i + 4 >= n) break;

    string[k++] = z32__alphabet[chunk[4] & 0x1f];
  }

  if (terminate) string[k] = '\0';

  return 0;
}

static inline int
z32__decode_utf8(const utf8_t *string, size_t string_len, uint8_t *buffer, size_t *buffer_len) {
  size_t len = (size_t) floor((double) string_len * 5.0 / 8.0);

  if (buffer == NULL) {
    *buffer_len = len;
    return 0;
  }

  if (*buffer_len < len) return -1;

  *buffer_len = len;

  size_t k = 0;

  for (size_t i = 0, n = string_len; i < n; i += 8) {
    char chunk[8];

    for (size_t j = 0; j < 8; j++) {
      chunk[j] = i + j < n ? z32__inverse_alphabet[string[i + j]] : 0;

      if (chunk[j] == (char) -1) return -1;
    }

    buffer[k++] = (chunk[0] << 3) | (chunk[1] >> 2);

    if (i + 1 >= n) break;

    buffer[k++] = (chunk[1] << 6) | (chunk[2] << 1) | (chunk[3] >> 4);

    if (i + 3 >= n) break;

    buffer[k++] = (chunk[3] << 4) | (chunk[4] >> 1);

    if (i + 4 >= n) break;

    buffer[k++] = (chunk[4] << 7) | (chunk[5] << 2) | (chunk[6] >> 3);

    if (i + 6 >= n) break;

    buffer[k++] = (chunk[6] << 5) | chunk[7];
  }

  return 0;
}

static inline int
z32__decode_utf16le(const utf16_t *string, size_t string_len, uint8_t *buffer, size_t *buffer_len) {
  size_t len = (size_t) floor((double) string_len * 5.0 / 8.0);

  if (buffer == NULL) {
    *buffer_len = len;
    return 0;
  }

  if (*buffer_len < len) return -1;

  *buffer_len = len;

  size_t k = 0;

  for (size_t i = 0, n = string_len; i < n; i += 8) {
    char chunk[8];

    for (size_t j = 0; j < 8; j++) {
      chunk[j] = i + j < n ? z32__inverse_alphabet[string[i + j]] : 0;

      if (chunk[j] == (char) -1) return -1;
    }

    buffer[k++] = (chunk[0] << 3) | (chunk[1] >> 2);

    if (i + 1 >= n) break;

    buffer[k++] = (chunk[1] << 6) | (chunk[2] << 1) | (chunk[3] >> 4);

    if (i + 3 >= n) break;

    buffer[k++] = (chunk[3] << 4) | (chunk[4] >> 1);

    if (i + 4 >= n) break;

    buffer[k++] = (chunk[4] << 7) | (chunk[5] << 2) | (chunk[6] >> 3);

    if (i + 6 >= n) break;

    buffer[k++] = (chunk[6] << 5) | chunk[7];
  }

  return 0;
}

int
z32_encode_utf8(const uint8_t *buffer, size_t buffer_len, utf8_t *string, size_t *string_len) {
  return z32__encode_utf8(buffer, buffer_len, string, string_len);
}

int
z32_decode_utf8(const utf8_t *string, size_t string_len, uint8_t *buffer, size_t *buffer_len) {
  return z32__decode_utf8(string, string_len, buffer, buffer_len);
}

int
z32_encode_utf16le(const uint8_t *buffer, size_t buffer_len, utf16_t *string, size_t *string_len) {
  return z32__encode_utf16le(buffer, buffer_len, string, string_len);
}

int
z32_decode_utf16le(const utf16_t *string, size_t string_len, uint8_t *buffer, size_t *buffer_len) {
  return z32__decode_utf16le(string, string_len, buffer, buffer_len);
}

#ifdef __cplusplus
}
#endif

#endif // Z32_H
