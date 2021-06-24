cmake_minimum_required(VERSION "3.18")
project("cgcs_ulog_demo")

set(C_STANDARD "11")
set(CFLAGS "-Wall -Werror -pedantic-errors")

set(CMAKE_C_STANDARD ${C_STANDARD})
set(CMAKE_C_FLAGS ${CFLAGS})

add_executable("cgcs_ulog_demo" "cgcs_ulog_demo.c")
target_link_libraries("cgcs_ulog_demo" LINK_PUBLIC "cgcs_ulog")
