cmake_minimum_required(VERSION 3.10)
project(alloc_switcher)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_subdirectory(src)

add_executable(alloc_switcher main.cpp)
target_link_libraries(alloc_switcher alloc_switcher_src)