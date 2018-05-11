#include "alloc_switcher/stackMemoryManager.h"

void* StackMemoryManager::Alloc(std::size_t size) {
    return (void*) _allocator.allocate(size);
}

void StackMemoryManager::Free(void *ptr) {
    _allocator.deallocate((char*) ptr, 1);
}