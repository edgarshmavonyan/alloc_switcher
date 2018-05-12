cmake_minimum_required(VERSION 3.10)
project(alloc_switcher_src)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES new.cc singletonBase.cc runtimeHeap.cc currentMemoryManager.cc standardMemoryManager.cc memoryManager.cc memoryManagerSwitcher.cc loggingMemoryManager.cc stackMemoryManager.cc)

add_library(alloc_switcher_src STATIC ${SOURCE_FILES})