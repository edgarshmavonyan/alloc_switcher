#include "switcher.h"


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
    if (currentManager == nullptr)
        return _defaultNew(size);
    return currentManager->Alloc(size);
}

void MemoryManagerSwitcher::Free(void *ptr) noexcept {
    // incorrect
    if (currentManager == nullptr)
        _defaultDelete(ptr);
    currentManager->Free(ptr);
}

MemoryManagerSwitcher globalSwitcher;

void* operator new(std::size_t size) noexcept(false) {
    std::cout << "My new\n";
    return globalSwitcher.Alloc(size);
}

void operator delete(void* ptr) noexcept {
    std::cout << "I deallocate it in my delete, bitches" << std::endl;
    globalSwitcher.Free(ptr);
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