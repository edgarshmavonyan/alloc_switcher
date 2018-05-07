#include "alloc_switcher/currentMemoryManager.h"
#include "alloc_switcher/switcher.h"


void* CurrentMemoryManager::Alloc(std::size_t size) {
    return MemoryManagerSwitcher::Alloc(size);
}

void CurrentMemoryManager::Free(void *ptr) {
    MemoryManagerSwitcher::Free(ptr);
}