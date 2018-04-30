#include "switcher.h"

void* StandardMemoryManager::Alloc(std::size_t size) noexcept(false) {
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

void StandardMemoryManager::Free(void *ptr) noexcept {
    if (ptr)
        ::free(ptr);
}

void MemoryManagerSwitcher::setManager(IMemoryManager *ptr) {
    currentManager = ptr;
}

IMemoryManager* MemoryManagerSwitcher::getManager() {
    if (currentManager == nullptr) {
        auto ptr = (StandardMemoryManager*) ::malloc(sizeof(StandardMemoryManager));
        new(ptr) StandardMemoryManager();
        firstManager = currentManager = (IMemoryManager*) ptr;
    }
    return currentManager;
}

MemoryManagerSwitcher::~MemoryManagerSwitcher() {
    if (firstManager != nullptr)
        ::free(firstManager);
}

MemoryManagerSwitcher globalSwitcher;

void* operator new(std::size_t size) noexcept(false) {
    std::cout << "My new\n";
    std::cout << size << ' ' << __LINE__ << std::endl;
    return globalSwitcher.getManager()->Alloc(size);
}

void operator delete(void* ptr) noexcept {
    std::cout << "I deallocate it in my delete, bitches" << std::endl;
    globalSwitcher.getManager()->Free(ptr);
}

/*
void* operator new(std::size_t size, const std::nothrow_t&) noexcept {
    void* p = nullptr;
    try {
        p = ::operator new(size);
    } catch (...) {}
    return p;
}

void* operator new[](std::size_t size) noexcept(false) {
    return ::operator new(size);
}

void* operator new[](std::size_t size, const std::nothrow_t&) noexcept {
    void* p = nullptr;
    try {
        p = ::operator new[](size);
    } catch (...) {}
    return p;
}

void operator delete(void* ptr, const std::nothrow_t&) noexcept {
    ::operator delete(ptr);
}

void operator delete(void* ptr, std::size_t) noexcept {
    ::operator delete(ptr);
}

void operator delete[](void* ptr) noexcept {
    ::operator delete(ptr);
}

void operator delete[](void* ptr, const std::nothrow_t&) noexcept {
    ::operator delete[](ptr);
}

void operator delete[](void* ptr, std::size_t) noexcept {
    ::operator delete[](ptr);
}
*/