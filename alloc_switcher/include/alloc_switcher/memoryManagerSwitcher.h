#pragma once
#include "singletonBase.h"


class MemoryManagerSwitcher {
public:
    MemoryManagerSwitcher() = delete;
    MemoryManagerSwitcher(const MemoryManagerSwitcher&) = delete;
    static SingletonBase& instance();
};

constexpr auto globalSwitcher = &MemoryManagerSwitcher::instance;