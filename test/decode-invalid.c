#include <assert.h>
#include <string.h>

#include "../include/z32.h"

#define test_decode_invalid(string) \
  { \
    size_t string_len = strlen(string); \
    size_t buffer_len = string_len; \
    char buffer[buffer_len]; \
    int err = z32_decode(string, string_len, buffer, &buffer_len); \
    assert(err != 0); \
  };

int
main () {
  test_decode_invalid("v");
}