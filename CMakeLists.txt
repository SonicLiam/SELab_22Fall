cmake_minimum_required(VERSION 3.16)
project(SELab_22Fall)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(SELab_22Fall main.cpp src/input.cpp src/execute.cpp src/judge.cpp src/output.cpp)
