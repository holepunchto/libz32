cmake_minimum_required(VERSION 3.22)

project(z32 C)

if(NOT TARGET utf)
  add_subdirectory(vendor/libutf EXCLUDE_FROM_ALL)
endif()

add_library(z32 OBJECT)

set_target_properties(
  z32
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ON
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
    $<TARGET_PROPERTY:utf,INTERFACE_INCLUDE_DIRECTORIES>
)

add_library(z32_shared SHARED $<TARGET_OBJECTS:z32>)

set_target_properties(
  z32_shared
  PROPERTIES
  OUTPUT_NAME z32
  WINDOWS_EXPORT_ALL_SYMBOLS ON
)

target_link_libraries(
  z32_shared
  PUBLIC
    z32
)

if(UNIX)
  target_link_libraries(
    z32_shared
    PRIVATE
      m
  )
endif()

add_library(z32_static STATIC)

set_target_properties(
  z32_static
  PROPERTIES
  OUTPUT_NAME z32
  PREFIX lib
)

target_link_libraries(
  z32_static
  PUBLIC
    z32
)

if(UNIX)
  target_link_libraries(
    z32_static
    PRIVATE
      m
  )
endif()

install(TARGETS z32_shared z32_static)

install(FILES include/z32.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
endif()
