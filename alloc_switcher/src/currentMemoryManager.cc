#include "alloc_switcher/currentMemoryManager.h"
#include "alloc_switcher/memoryManagerSwitcher.h"


void* CurrentMemoryManager::Alloc(std::size_t size) {
    return MemoryManagerSwitcher::instance().Alloc(size);
}

void CurrentMemoryManager::Free(void *ptr) {
    MemoryManagerSwitcher::instance().Free(ptr);
}