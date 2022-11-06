cmake_minimum_required(VERSION 3.21)
project(binding_of_briatte C)

set(CMAKE_C_STANDARD 99)

add_executable(binding_of_briatte main.c sources/file_mapping/file_mapping.c)
