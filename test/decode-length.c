#include <assert.h>
#include <string.h>
#include <utf.h>

#include "../include/z32.h"

#define test_decode_length(string, expected) \
  { \
    size_t string_len = strlen(string); \
    size_t buffer_len = 0; \
    int err = z32_decode((utf8_t *) string, string_len, NULL, &buffer_len); \
    assert(err == 0); \
    assert(buffer_len == expected); \
  };

int
main () {
  test_decode_length("cr", 1);
  test_decode_length("cfty", 2);
  test_decode_length("cftgg", 3);
  test_decode_length("cftgg3y", 4);
  test_decode_length("cftgg3df", 5);
}
