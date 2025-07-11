cmake_minimum_required(VERSION 3.16)
project(lmaobench)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    lmaobench
    src/main.cpp
    benchmarks/syscall.cpp
)

target_include_directories(lmaobench PRIVATE include)
