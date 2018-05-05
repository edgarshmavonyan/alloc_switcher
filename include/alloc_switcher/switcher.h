#pragma once
#include <iostream>

class IMemoryManager {
public:
    virtual void* Alloc(std::size_t size) = 0;
    virtual void Free(void* ptr) = 0;
};

class MemoryManagerSwitcher {
private:
    static IMemoryManager* currentManager;

    static void* _defaultNew(std::size_t size) noexcept (false);
    static void _defaultDelete(void* ptr) noexcept;
public:
    MemoryManagerSwitcher() = delete;
    MemoryManagerSwitcher(const MemoryManagerSwitcher&) = delete;
    MemoryManagerSwitcher& operator=(const MemoryManagerSwitcher&) = delete;

    static void setManager(IMemoryManager* ptr);

    static void* Alloc(std::size_t size) noexcept(false);
    static void Free(void* ptr);
};