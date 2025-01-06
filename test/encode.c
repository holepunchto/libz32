#include <assert.h>
#include <string.h>
#include <utf.h>

#include "../include/z32.h"

#define test_encode(buffer, expected) \
  { \
    size_t buffer_len = strlen(buffer); \
    size_t string_len = buffer_len * 2; \
    char string[string_len]; \
    int err = z32_encode_utf8((uint8_t *) buffer, buffer_len, (utf8_t *) string, &string_len); \
    assert(err == 0); \
    assert(string_len == strlen(expected)); \
    assert(strncmp(string, expected, string_len) == 0); \
  };

int
main() {
  test_encode("a", "cr");
  test_encode("ab", "cfty");
  test_encode("abc", "cftgg");
  test_encode("abcd", "cftgg3y");
  test_encode("abcde", "cftgg3df");
}
