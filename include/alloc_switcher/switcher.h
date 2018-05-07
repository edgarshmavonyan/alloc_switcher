#pragma once
#include <alloc_switcher/memoryManager.h>


class MemoryManagerSwitcher {
private:
    static MemoryManager* currentManager;

    static void* _defaultNew(std::size_t size) noexcept (false);
    static void _defaultDelete(void* ptr) noexcept;
public:
    MemoryManagerSwitcher() = delete;
    MemoryManagerSwitcher(const MemoryManagerSwitcher&) = delete;
    MemoryManagerSwitcher& operator=(const MemoryManagerSwitcher&) = delete;

    static void setManager(MemoryManager* ptr);
    static void deleteManager();

    static void* Alloc(std::size_t size) noexcept(false);
    static void Free(void* ptr);
};