add_test_executables(
  decode.c
  decode-invalid.c
  decode-length.c
  encode.c
  encode-length.c
  LINK
    z32::<TYPE>
)

add_subdirectory(fuzz)
