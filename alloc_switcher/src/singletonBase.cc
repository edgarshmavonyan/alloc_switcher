#include "alloc_switcher/singletonBase.h"

SingletonBase::SingletonBase() :
        currentManager(new(::malloc(sizeof(StandardMemoryManager))) StandardMemoryManager()) {}

SingletonBase::~SingletonBase() {
    while (currentManager) {
        auto temp = currentManager;
        currentManager = currentManager->previous;
        temp->~MemoryManager();
        ::free(temp);
    }
}

void SingletonBase::setManager(MemoryManager *ptr) {
    ptr->previous = currentManager;
    currentManager = ptr;
}

void SingletonBase::deleteManager() {
    if (currentManager)
        currentManager = currentManager->previous;
}

void* SingletonBase::Alloc(std::size_t size) noexcept(false) {
    if (!currentManager)
        currentManager = new(::malloc(sizeof(StandardMemoryManager))) StandardMemoryManager();

    auto ptr = static_cast<char*>(currentManager->Alloc(size + sizeof(MemoryManager*)));
    new(ptr) MemoryManager*(currentManager);
    return ptr + sizeof(MemoryManager*);
}

void SingletonBase::Free(void *ptr) noexcept {
    auto usedManager = static_cast<MemoryManager**>(ptr) - 1;
    (*usedManager)->Free(static_cast<void*>(usedManager));
}