cmake_minimum_required(VERSION 3.5)
project(mini-excel)

file(GLOB C_HEADERS *.h)
file(GLOB C_SOURCES *.c)
set(SOURCE_FILES ${C_SOURCES})
add_executable(mini-excel ${SOURCE_FILES})

if (UNIX)
  add_definitions(-DCMAKE_C_COMPILER="${CMAKE_C_COMPILER}")
  add_custom_command(TARGET mini-excel POST_BUILD COMMAND cp ${C_HEADERS} ${CMAKE_CURRENT_BINARY_DIR})
endif()
