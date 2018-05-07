#include "alloc_switcher/loggingMemoryManager.h"


void* LoggingMemoryManager::Alloc(std::size_t size) {
    auto ptr = StandardMemoryManager::Alloc(size);
    std::cout << "allocation " << size << ' ' << ptr << std::endl;
    return ptr;
}

void LoggingMemoryManager::Free(void *ptr) {
    std::cout << "deallocation " << ptr << std::endl;
    StandardMemoryManager::Free(ptr);
}