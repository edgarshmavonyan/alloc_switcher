#pragma once
#include <iostream>


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