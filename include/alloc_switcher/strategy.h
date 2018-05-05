#pragma once
#include <iostream>
#include "alloc_switcher/switcher.h"

template<typename Strategy>
class AllocatedOn {
    using _allocationStrategy = Strategy;
public:
    void* operator new(std::size_t size) {
        return _allocationStrategy::Alloc(size);
    }
    void operator delete(void* ptr) {
        _allocationStrategy::Free(ptr);
    }
};

class RuntimeHeap {
public:
    static void* Alloc(std::size_t size);
    static void Free(void* ptr);
};

class CurrentMemoryManager {
public:
    static void* Alloc(std::size_t size);
    static void Free(void* ptr);
};


