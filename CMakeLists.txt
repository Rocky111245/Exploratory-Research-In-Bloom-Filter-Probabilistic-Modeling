cmake_minimum_required(VERSION 3.26)
project(s C)

set(CMAKE_C_STANDARD 23)

add_executable(s main.c
        Functions.c
        Functions.h)
