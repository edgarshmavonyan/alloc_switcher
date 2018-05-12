#pragma once
#include "alloc_switcher/standardMemoryManager.h"


class SingletonBase {
private:
    MemoryManager* currentManager;
public:
    SingletonBase();
    SingletonBase(const SingletonBase&) = delete;
    SingletonBase& operator=(const SingletonBase&) = delete;
    ~SingletonBase();

    void setManager(MemoryManager* ptr);
    void deleteManager();
    void* Alloc(std::size_t size) noexcept(false);
    void Free(void* ptr) noexcept;
};