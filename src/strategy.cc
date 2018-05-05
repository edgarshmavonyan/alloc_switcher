#include "alloc_switcher/strategy.h"

void* RuntimeHeap::Alloc(std::size_t size) {
    if (size == 0)
        size = 1;
    return ::malloc(size);
}

void RuntimeHeap::Free(void *ptr) {
    if (ptr)
        ::free(ptr);
}

void* CurrentMemoryManager::Alloc(std::size_t size) {
    return MemoryManagerSwitcher::Alloc(size);
}

void CurrentMemoryManager::Free(void *ptr) {
    MemoryManagerSwitcher::Free(ptr);
}
