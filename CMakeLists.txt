cmake_minimum_required(VERSION 3.16)
project(lmaobench)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin")

file(
    GLOB_RECURSE BENCH_SOURCES
    CONFIGURE_DEPENDS
    benchmarks/*.cpp
)

add_executable(
    lmaobench
    src/main.cpp
    ${BENCH_SOURCES}
)

target_include_directories(lmaobench PRIVATE include)
