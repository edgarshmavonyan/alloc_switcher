#pragma once
#include <iostream>

class IMemoryManager {
public:
    virtual void* Alloc(std::size_t size) = 0;
    virtual void Free(void* ptr) = 0;
};

class MemoryManagerSwitcher {
private:
    IMemoryManager* currentManager;

    void* _defaultNew(std::size_t size) noexcept (false);
    void _defaultDelete(void* ptr) noexcept;
public:
    MemoryManagerSwitcher(): currentManager(nullptr) {}

    MemoryManagerSwitcher(const MemoryManagerSwitcher&) = delete;
    MemoryManagerSwitcher& operator=(const MemoryManagerSwitcher&) = delete;

    void setManager(IMemoryManager* ptr);

    void* Alloc(std::size_t size) noexcept(false);
    void Free(void* ptr) noexcept;

    ~MemoryManagerSwitcher() = default;
};

extern MemoryManagerSwitcher globalSwitcher;