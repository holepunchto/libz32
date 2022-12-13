#include <assert.h>
#include <string.h>

#include "../include/z32.h"

#define test_encode(buffer, expected) \
  { \
    size_t buffer_len = strlen(buffer); \
    size_t string_len = buffer_len * 2; \
    char string[string_len]; \
    int err = z32_encode(buffer, buffer_len, string, &string_len); \
    assert(err == 0); \
    assert(string_len == strlen(expected)); \
    assert(strcmp(string, expected) == 0); \
  };

int
main () {
  test_encode("a", "cr");
  test_encode("ab", "cfty");
  test_encode("abc", "cftgg");
  test_encode("abcd", "cftgg3y");
  test_encode("abcde", "cftgg3df");
}