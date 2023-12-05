cmake_minimum_required(VERSION 3.10)
project(CachedIO)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(cio-test src/cio_base.cpp src/cio_reader.cpp src/cio_writer.cpp test/main.cpp)
