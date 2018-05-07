cmake_minimum_required(VERSION 3.10)
project(alloc_switcher_src)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES new.cc switcher.cc runtimeHeap.cc currentMemoryManager.cc)

add_library(alloc_switcher_src STATIC ${SOURCE_FILES})