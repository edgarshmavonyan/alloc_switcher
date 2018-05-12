cmake_minimum_required(VERSION 3.8)
project(alloc_stack)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -fsanitize=address)

include_directories(stack_allocator/include)
include_directories(alloc_switcher/include)

add_subdirectory(stack_allocator)
add_subdirectory(alloc_switcher)
set(SOURCE_FILES main.cpp)
add_executable(alloc_stack ${SOURCE_FILES})
target_link_libraries(alloc_stack alloc_switcher_src stackAllocator_src)