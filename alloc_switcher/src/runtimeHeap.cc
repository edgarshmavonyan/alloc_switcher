#include "alloc_switcher/runtimeHeap.h"


void* RuntimeHeap::Alloc(std::size_t size) {
    if (size == 0)
        size = 1;
    return ::malloc(size);
}

void RuntimeHeap::Free(void *ptr) {
    if (ptr)
        ::free(ptr);
}