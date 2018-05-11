#include "runtimeHeap.h"

template<typename T>
class Mallocator {
public:
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    Mallocator() = default;

    template<typename U>
    explicit Mallocator(const Mallocator<U>&) {}

    ~Mallocator() = default;

    template<typename U>
    Mallocator& operator=(const Mallocator<U>&) {return *this;}

    template<class U>
    struct rebind {
        typedef Mallocator<U> other;
    };

    pointer allocate(std::size_t elementNumber) {
        return reinterpret_cast<pointer>(RuntimeHeap::Alloc(elementNumber * sizeof(T)));
    }

    void deallocate(pointer ptr, size_t) {
        RuntimeHeap::Free(ptr);
    }

    bool friend operator==(const Mallocator& first, const Mallocator& other) {
        return true;
    }

    bool friend operator!=(const Mallocator& first, const Mallocator& other) {
        return false;
    }
};

template<typename T>
auto shared_deleter = [](T* ptr) {
    ptr->~T();
    RuntimeHeap::Free(ptr);
};