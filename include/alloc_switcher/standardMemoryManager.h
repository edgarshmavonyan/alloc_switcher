#pragma once
#include "memoryManager.h"


class StandardMemoryManager: public MemoryManager {
public:
    void* Alloc(std::size_t size) override;
    void Free(void* ptr) override;
    ~StandardMemoryManager() override = default;
};