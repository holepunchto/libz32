cmake_minimum_required(VERSION 4.0)

find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-fuzz REQUIRED PATHS node_modules/cmake-fuzz)

project(z32 C)

fetch_package("github:holepunchto/libutf")

get_property(shared GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS)

add_library(z32 OBJECT)

set_target_properties(
  z32
  PROPERTIES
  C_STANDARD 99
  POSITION_INDEPENDENT_CODE ${shared}
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

if(shared)
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

install(TARGETS z32_static)

if(shared)
  install(TARGETS z32_shared)
endif()

install(FILES include/z32.h DESTINATION include)

if(PROJECT_IS_TOP_LEVEL)
  enable_testing()

  add_subdirectory(test)
endif()
