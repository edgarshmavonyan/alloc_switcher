#pragma once
#include <iostream>
#include "switcher.h"

template<typename Strategy>
class AllocatedOn {
    using _allocationStrategy = Strategy;
public:
    void* operator new(std::size_t size) {
        std::cout << "My created new " << size << '\n';
        return _allocationStrategy::Alloc(size);
    }
    void operator delete(void* ptr) {
        std::cout << "My created delete \n";
        return _allocationStrategy::Free(ptr);
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