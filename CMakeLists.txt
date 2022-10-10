cmake_minimum_required(VERSION 3.21)
project(binding_of_briatte C)

set(CMAKE_C_STANDARD 11)

include_directories(sources/file_mapping)

#link sdl2
INCLUDE_DIRECTORIES(  /opt/homebrew/Cellar/sdl2/2.24.1/include)
LINK_DIRECTORIES(  /opt/homebrew/Cellar/sdl2/2.24.1/lib)

file(GLOB LIBRARIES "/opt/homebrew/Cellar/sdl2/2.24.1/lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

add_executable(binding_of_briatte
        sources/file_mapping/file_mapping.c
        sources/file_mapping/file_mapping.h
        main.c sdlTest/sedlTest.c sdlTest/sedlTest.h)


TARGET_LINK_LIBRARIES(binding_of_briatte  ${LIBRARIES})