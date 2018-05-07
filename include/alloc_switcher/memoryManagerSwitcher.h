#pragma once
#include "alloc_switcher/standardMemoryManager.h"


class MemoryManagerSwitcher {
private:
    MemoryManager* currentManager;
public:
    MemoryManagerSwitcher();
    MemoryManagerSwitcher(const MemoryManagerSwitcher&) = delete;
    MemoryManagerSwitcher& operator=(const MemoryManagerSwitcher&) = delete;
    ~MemoryManagerSwitcher();

    void setManager(MemoryManager* ptr);
    void deleteManager();
    void* Alloc(std::size_t size) noexcept(false);
    void Free(void* ptr) noexcept;
};

extern MemoryManagerSwitcher globalSwitcher;