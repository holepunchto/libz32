#include <assert.h>
#include <string.h>
#include <utf.h>

#include "../include/z32.h"

#define test_decode(string, expected) \
  { \
    size_t string_len = strlen(string); \
    size_t buffer_len = string_len; \
    uint8_t buffer[buffer_len]; \
    int err = z32_decode_utf8((utf8_t *) string, string_len, buffer, &buffer_len); \
    assert(err == 0); \
    assert(buffer_len == strlen(expected)); \
    assert(strncmp((char *) buffer, expected, buffer_len) == 0); \
  };

int
main() {
  test_decode("cr", "a");
  test_decode("cfty", "ab");
  test_decode("cftgg", "abc");
  test_decode("cftgg3y", "abcd");
  test_decode("cftgg3df", "abcde");
}
