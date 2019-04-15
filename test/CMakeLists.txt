cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wunused -Werror")

include_directories(../src)

add_executable(dlist_test ../src/dlist.c dlist_test.c)
