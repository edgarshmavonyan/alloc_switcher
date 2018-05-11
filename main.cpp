#include <iostream>
#include <list>
#include "xorlist/xorlist.h"
#include "test/testTime.h"
#include "test/testGeneration.h"
#include "alloc_switcher/memoryManagerSwitcher.h"
#include "alloc_switcher/stackMemoryManager.h"

int main() {
    auto sequence = generateInsert(1000000);
    auto stackManager = new StackMemoryManager;


    globalSwitcher.setManager(stackManager);

    clock_t t = clock();
    doInsertTesting(sequence);
    std::cout << "Stack time: " << double(clock() - t)/CLOCKS_PER_SEC << std::endl;

    globalSwitcher.deleteManager();

    t = clock();
    doInsertTesting(sequence);
    std::cout << "Heap time: " << double(clock() - t)/CLOCKS_PER_SEC << std::endl;

    delete stackManager;
    return 0;
}