if(TARGET z32_shared)
  set(library z32::shared)
else()
  set(library z32::static)
endif()

add_test_executables(
  decode.c
  decode-invalid.c
  decode-length.c
  encode.c
  encode-length.c
  LINK
    ${library}
)

add_subdirectory(fuzz)
