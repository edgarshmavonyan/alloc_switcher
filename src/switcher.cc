#include "alloc_switcher/switcher.h"

MemoryManager::~MemoryManagerInterface() = default;

MemoryManager* MemoryManagerSwitcher::currentManager = nullptr;

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

void MemoryManagerSwitcher::setManager(MemoryManager *ptr) {
    ptr->previous = currentManager;
    currentManager = ptr;
}

void MemoryManagerSwitcher::deleteManager() {
    if (currentManager)
        currentManager = currentManager->previous;
}

void* MemoryManagerSwitcher::Alloc(std::size_t size) noexcept(false) {
    char* ptr;

    if (!currentManager)
        ptr = static_cast<char*>(_defaultNew(size + sizeof(MemoryManager*)));

    else
        ptr = static_cast<char*>(currentManager->Alloc(size + sizeof(MemoryManager*)));

    new(ptr) MemoryManager*(currentManager);
    return ptr + sizeof(MemoryManager*);
}

void MemoryManagerSwitcher::Free(void *ptr) {
    auto usedManager = static_cast<MemoryManager**>(ptr) - 1;

    if (*usedManager == nullptr)
        _defaultDelete(static_cast<void*>(usedManager));

    else
        (*usedManager)->Free(static_cast<void*>(usedManager));
}