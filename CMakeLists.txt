cmake_minimum_required(VERSION 3.24)
project(buffer)

set(CMAKE_CXX_STANDARD 17)

add_executable(buffer main.cpp int_sorted.cpp int_sorted.h int_buffer.cpp int_buffer.h)
