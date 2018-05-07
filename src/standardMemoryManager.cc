#include "alloc_switcher/standardMemoryManager.h"


void* StandardMemoryManager::Alloc(std::size_t size) {
    if (size == 0)
        size = 1;
    void* p;

    while ((p = ::malloc(size)) == nullptr) {
        std::new_handler newHandler = std::get_new_handler();
        if (newHandler)
            newHandler();
        else
            throw std::bad_alloc();
    }
    return p;
}

void StandardMemoryManager::Free(void *ptr) {
    if (ptr)
        ::free(ptr);
}