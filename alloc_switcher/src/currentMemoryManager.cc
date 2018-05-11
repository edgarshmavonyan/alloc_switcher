#include "alloc_switcher/currentMemoryManager.h"
#include "alloc_switcher/memoryManagerSwitcher.h"


void* CurrentMemoryManager::Alloc(std::size_t size) {
    return globalSwitcher.Alloc(size);
}

void CurrentMemoryManager::Free(void *ptr) {
    globalSwitcher.Free(ptr);
}