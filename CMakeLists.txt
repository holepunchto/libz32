cmake_minimum_required(VERSION 3.22)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

project(z32 C)

add_library(z32 OBJECT)

set_target_properties(
  z32
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE 1
)

target_sources(
  z32
  INTERFACE
    include/z32.h
  PRIVATE
    src/z32.c
)

target_include_directories(
  z32
  PUBLIC
    include
)

add_library(z32_shared SHARED $<TARGET_OBJECTS:z32>)

set_target_properties(
  z32_shared
  PROPERTIES
  OUTPUT_NAME z32
)

add_library(z32_static STATIC $<TARGET_OBJECTS:z32>)

set_target_properties(
  z32_static
  PROPERTIES
  OUTPUT_NAME z32
)

install(TARGETS z32_shared z32_static)

install(FILES include/z32.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()
  add_subdirectory(test)
endif()
