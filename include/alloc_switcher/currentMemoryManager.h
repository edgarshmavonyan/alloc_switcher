#pragma once
#include <iostream>


class CurrentMemoryManager {
public:
    static void* Alloc(std::size_t size);
    static void Free(void* ptr);
};


