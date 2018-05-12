#pragma once
#include "stackallocator/stackAllocator.h"
#include "memoryManager.h"

class StackMemoryManager: public MemoryManager {
public:
    StackMemoryManager(): MemoryManager(), _allocator() {}
    void* Alloc(std::size_t size) override;
    void Free(void* ptr) override;
    ~StackMemoryManager() override {}
private:
    StackAllocator<char> _allocator;
};