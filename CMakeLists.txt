cmake_minimum_required(VERSION 3.22)
project(tribbleDb)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        src/*.h
        src/*.cpp
        )

add_executable(tribbleDb ${SOURCES})
