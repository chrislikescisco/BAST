cmake_minimum_required(VERSION 3.27)
project(BAST)

set(CMAKE_CXX_STANDARD 20)

add_executable(BAST main.cpp
        basedball.h
        basedball.cpp)

set(INCLUDE_DIRECTORIES ./)
include_directories(include)