#include "alloc_switcher/memoryManagerSwitcher.h"

MemoryManagerSwitcher::MemoryManagerSwitcher() :
        currentManager(new(::malloc(sizeof(StandardMemoryManager))) StandardMemoryManager()) {}

MemoryManagerSwitcher::~MemoryManagerSwitcher() {
    while (currentManager) {
        auto temp = currentManager;
        currentManager = currentManager->previous;
        temp->~MemoryManager();
        ::free(temp);
    }
}

void MemoryManagerSwitcher::setManager(MemoryManager *ptr) {
    ptr->previous = currentManager;
    currentManager = ptr;
}

void MemoryManagerSwitcher::deleteManager() {
    if (currentManager)
        currentManager = currentManager->previous;
}

void* MemoryManagerSwitcher::Alloc(std::size_t size) noexcept(false) {
    if (!currentManager)
        currentManager = new(::malloc(sizeof(StandardMemoryManager))) StandardMemoryManager();

    auto ptr = static_cast<char*>(currentManager->Alloc(size + sizeof(MemoryManager*)));
    new(ptr) MemoryManager*(currentManager);
    return ptr + sizeof(MemoryManager*);
}

void MemoryManagerSwitcher::Free(void *ptr) noexcept {
    auto usedManager = static_cast<MemoryManager**>(ptr) - 1;
    (*usedManager)->Free(static_cast<void*>(usedManager));
}

MemoryManagerSwitcher globalSwitcher;