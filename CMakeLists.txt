cmake_minimum_required(VERSION 3.22)
project(mysmallDb)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
        src/*.h
        src/*.cpp
        )

add_executable(mysmallDb ${SOURCES})
