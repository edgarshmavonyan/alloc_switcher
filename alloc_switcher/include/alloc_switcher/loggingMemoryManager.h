#pragma once
#include "standardMemoryManager.h"


class LoggingMemoryManager: public StandardMemoryManager {
    using StandardMemoryManager::Alloc;
    using StandardMemoryManager::Free;
public:
    void* Alloc(std::size_t size) override;
    void Free(void* ptr) override;
    ~LoggingMemoryManager() override = default;
};