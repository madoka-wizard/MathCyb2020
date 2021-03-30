cmake_minimum_required(VERSION 3.17)
project(MathCyb2020)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(MathCyb2020
        block.h block.cpp
        blockchain.h blockchain.cpp
        main.cpp
        )
