cmake_minimum_required(VERSION 3.8)
project(shell_master)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        AS1.pdf
        Makefile
        README.md
        shell.c
        util.h)

include_directories(.)

add_executable(shell_master ${SOURCE_FILES})