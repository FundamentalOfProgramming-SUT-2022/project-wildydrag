cmake_minimum_required(VERSION 3.24)
project(root C)

set(CMAKE_C_STANDARD 11)

add_executable(root
        main.c test.c test2.c)
