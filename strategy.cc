#include "strategy.h"

void* RuntimeHeap::Alloc(std::size_t size) {
    if (size == 0)
        size = 1;
    // unsafe
    return ::malloc(size);
    /*
    void* p;
    while ((p = ::malloc(size)) == nullptr) {
        std::new_handler newHandler = std::get_new_handler();
        if (newHandler)
            newHandler();
        else
            throw std::bad_alloc();
    }
    return p;
    */
}

void RuntimeHeap::Free(void *ptr) {
    if (ptr)
        ::free(ptr);
}

void* CurrentMemoryManager::Alloc(std::size_t size) {
    return globalSwitcher.Alloc(size);
}

void CurrentMemoryManager::Free(void *ptr) {
    globalSwitcher.Free(ptr);
}