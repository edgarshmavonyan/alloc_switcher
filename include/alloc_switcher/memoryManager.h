#pragma once
#include <iostream>


class MemoryManager {
public:
    MemoryManager* previous = nullptr;
    virtual void* Alloc(std::size_t size) = 0;
    virtual void Free(void* ptr) = 0;
    virtual ~MemoryManager() = 0;
};