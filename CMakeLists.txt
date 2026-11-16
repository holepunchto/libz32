cmake_minimum_required(VERSION 4.0)

find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-fuzz REQUIRED PATHS node_modules/cmake-fuzz)
find_package(cmake-prelude REQUIRED PATHS node_modules/cmake-prelude)
find_package(cmake-test REQUIRED PATHS node_modules/cmake-test)

project(z32 LANGUAGES C VERSION 0.0.0)

fetch_package("github:holepunchto/libutf")

add_library_targets(
  z32
  HEADERS
    include/z32.h
  FEATURES
    c_std_99
  SOURCES
    src/z32.c
  LINK
    utf::headers
)

if(UNIX)
  target_link_libraries(
    z32_headers
    INTERFACE
      m
  )
endif()

add_test_subdirectory(test)
