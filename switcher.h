#pragma once
#include <iostream>

class IMemoryManager {
public:
    virtual void* Alloc(std::size_t size) = 0;
    virtual void Free(void* ptr) = 0;
};

class StandardMemoryManager: public IMemoryManager {
public:
    void* Alloc(std::size_t size) noexcept(false) override;
    void Free(void* ptr) noexcept override;
};

class MemoryManagerSwitcher {
private:
    IMemoryManager* firstManager;

    IMemoryManager* currentManager;
public:
    MemoryManagerSwitcher(): firstManager(nullptr), currentManager(nullptr) {}

    MemoryManagerSwitcher(const MemoryManagerSwitcher&) = delete;

    MemoryManagerSwitcher& operator=(const MemoryManagerSwitcher&) = delete;

    void setManager(IMemoryManager* ptr);

    IMemoryManager* getManager();

    ~MemoryManagerSwitcher();
};

extern MemoryManagerSwitcher globalSwitcher;