#include <math.h>

#include "../include/z32.h"

static const char z32_alphabet[] = "ybndrfg8ejkmcpqxot1uwisza345h769";

static const char z32_inverse_alphabet[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, 25, 26, 27, 30, 29, 7, 31, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 24, 1, 12, 3, 8, 5, 6, 28, 21, 9, 10, -1, 11, 2, 16, 13, 14, 4, 22, 17, 19, -1, 20, 15, 0, 23};

int
z32_encode (const char *buffer, size_t buffer_len, char *string, size_t *string_len) {
  size_t len = (size_t) ceil((double) buffer_len * 8.0 / 5.0);

  if (string == NULL) {
    *string_len = len;
    return 0;
  }

  if (*string_len < len + 1) return -1;

  *string_len = len;

  size_t k = 0;

  for (size_t i = 0, n = buffer_len; i < n; i += 5) {
    char chunk[5];

    for (size_t j = 0; j < 5; j++) {
      chunk[j] = i + j < n ? buffer[i + j] : 0;
    }

    string[k++] = z32_alphabet[(chunk[0] & 0xf8) >> 3];
    string[k++] = z32_alphabet[(chunk[0] & 0x07) << 2 | (chunk[1] & 0xc0) >> 6];

    if (i + 1 >= n) break;

    string[k++] = z32_alphabet[(chunk[1] & 0x3e) >> 1];
    string[k++] = z32_alphabet[(chunk[1] & 0x01) << 4 | (chunk[2] & 0xf0) >> 4];

    if (i + 2 >= n) break;

    string[k++] = z32_alphabet[(chunk[2] & 0x0f) << 1 | (chunk[3] & 0x80) >> 7];

    if (i + 3 >= n) break;

    string[k++] = z32_alphabet[(chunk[3] & 0x7c) >> 2];
    string[k++] = z32_alphabet[(chunk[3] & 0x03) << 3 | (chunk[4] & 0xe0) >> 5];

    if (i + 4 >= n) break;

    string[k++] = z32_alphabet[chunk[4] & 0x1f];
  }

  string[k] = '\0';

  return 0;
}

int
z32_decode (const char *string, size_t string_len, char *buffer, size_t *buffer_len) {
  size_t len = (size_t) floor((double) string_len * 5.0 / 8.0);

  if (buffer == NULL) {
    *buffer_len = len;
    return 0;
  }

  if (*buffer_len < len + 1) return -1;

  *buffer_len = len;

  size_t k = 0;

  for (size_t i = 0, n = string_len; i < n; i += 8) {
    char chunk[8];

    for (size_t j = 0; j < 8; j++) {
      chunk[j] = i + j < n ? z32_inverse_alphabet[string[i + j]] : 0;

      if (chunk[j] == -1) return -1;
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
