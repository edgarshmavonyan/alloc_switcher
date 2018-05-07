#pragma once
#include "alloc_switcher/allocatedOn.h"


class RuntimeHeap {
public:
    static void* Alloc(std::size_t size);
    static void Free(void* ptr);
};