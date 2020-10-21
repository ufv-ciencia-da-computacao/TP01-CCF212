cmake_minimum_required(VERSION 2.6)
project(main)
set(CMAKE_BUILD_TYPE Debug)
set(SOURCE_FILES ./benchmark/lib/benchmark.h ./benchmark/lib/benchmark.c ./patricia/lib/patricia.c ./patricia/lib/patricia.h ./tst/lib/tst.c ./tst/lib/tst.h main.c)
add_executable(main ${SOURCE_FILES})

