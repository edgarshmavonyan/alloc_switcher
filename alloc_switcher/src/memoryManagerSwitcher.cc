#include "alloc_switcher/memoryManagerSwitcher.h"

SingletonBase& MemoryManagerSwitcher::instance() {
    static SingletonBase _instance;
    return _instance;
}