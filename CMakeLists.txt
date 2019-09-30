cmake_minimum_required(VERSION 3.14)
project(perfectNumbers C)

set(CMAKE_C_STANDARD 99)

add_executable(perfectNumbers perfect-number-tester.c perfect-numbers.c)
target_link_libraries(perfectNumbers m)
