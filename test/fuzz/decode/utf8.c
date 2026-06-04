#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../../include/z32.h"

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  // z32 decodes 8 characters to 5 bytes, rounding down for partial chunks.
  size_t buffer_len = (size_t) floor((double) size * 5.0 / 8.0);
  uint8_t *buffer = buffer_len > 0 ? malloc(buffer_len) : NULL;

  int err = z32_decode_utf8((const utf8_t *) data, size, buffer, &buffer_len);

  if (err == 0) {
    assert(buffer_len == (size_t) floor((double) size * 5.0 / 8.0));

    if (buffer_len > 0) {
      // Re-encode the decoded bytes; the result must decode back identically.
      size_t string_len = (size_t) ceil((double) buffer_len * 8.0 / 5.0);
      utf8_t *string = malloc(string_len);

      err = z32_encode_utf8(buffer, buffer_len, string, &string_len);

      assert(err == 0);

      size_t roundtrip_len = buffer_len;
      uint8_t *roundtrip = malloc(roundtrip_len);

      err = z32_decode_utf8(string, string_len, roundtrip, &roundtrip_len);

      assert(err == 0);
      assert(roundtrip_len == buffer_len);
      assert(memcmp(roundtrip, buffer, buffer_len) == 0);

      free(roundtrip);
      free(string);
    }
  }

  free(buffer);

  return 0;
}
