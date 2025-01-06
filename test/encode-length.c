#include <assert.h>
#include <string.h>

#include "../include/z32.h"

#define test_encode_length(buffer, expected) \
  { \
    size_t buffer_len = strlen(buffer); \
    size_t string_len = 0; \
    int err = z32_encode_utf8((uint8_t *) buffer, buffer_len, NULL, &string_len); \
    assert(err == 0); \
    assert(string_len == expected); \
  };

int
main() {
  test_encode_length("a", 2);
  test_encode_length("ab", 4);
  test_encode_length("abc", 5);
  test_encode_length("abcd", 7);
  test_encode_length("abcde", 8);
}
