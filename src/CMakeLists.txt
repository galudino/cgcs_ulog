cmake_minimum_required(VERSION "3.18")
project("cgcs_ulog")

set(C_STANDARD "11") # C11
set(CFLAGS "-Wall -Werror -pedantic-errors")

set(CMAKE_C_STANDARD "${C_STANDARD}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS}")

add_library("cgcs_ulog" "cgcs_ulog.h" "cgcs_ulog.c")
add_compile_options("cgcs_ulog" PUBLIC "-fblocks")
target_include_directories("cgcs_ulog" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
