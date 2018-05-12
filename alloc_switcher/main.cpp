#include <iostream>
#include "alloc_switcher/singletonBase.h"
#include "alloc_switcher/loggingMemoryManager.h"

int main() {
    auto logging = new LoggingMemoryManager;

    globalSwitcher.setManager(logging);
    auto my_int = new int(5);
    globalSwitcher.deleteManager();

    delete my_int;
    delete logging;
    return 0;
}