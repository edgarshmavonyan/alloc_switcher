cmake_minimum_required(VERSION 3.10)
project(alloc_switcher)

set(CMAKE_CXX_STANDARD 14)

#add_library(alloc_switcher STATIC main.cpp)
add_executable(alloc_switcher main.cpp switcher.cc strategy.cc)