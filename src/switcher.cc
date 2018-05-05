#include "alloc_switcher/switcher.h"


IMemoryManager* MemoryManagerSwitcher::currentManager = nullptr;

void* MemoryManagerSwitcher::_defaultNew(std::size_t size) noexcept(false) {
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

void MemoryManagerSwitcher::_defaultDelete(void *ptr) noexcept {
    if (ptr)
        ::free(ptr);
}

void MemoryManagerSwitcher::setManager(IMemoryManager *ptr) {
    currentManager = ptr;
}

void* MemoryManagerSwitcher::Alloc(std::size_t size) noexcept(false) {
    char* ptr;

    if (currentManager == nullptr)
        ptr = static_cast<char*>(_defaultNew(size + sizeof(IMemoryManager*)));

    else
        ptr = static_cast<char*>(currentManager->Alloc(size + sizeof(IMemoryManager*)));

    new(ptr) IMemoryManager*(currentManager);
    return ptr + sizeof(IMemoryManager*);
}

void MemoryManagerSwitcher::Free(void *ptr) {
    auto usedManager = static_cast<IMemoryManager**>(ptr) - 1;

    if (*usedManager == nullptr)
        _defaultDelete(static_cast<void*>(usedManager));

    else
        (*usedManager)->Free(static_cast<void*>(usedManager));
}