#include <iostream>
#include "switcher.h"
#include "strategy.h"

class StrategyInheritor: public AllocatedOn<CurrentMemoryManager> {
private:
    int some_value;
};

int main() {
    auto a = new StrategyInheritor;
    delete a;
//    auto a = new int[5];
//    operator delete(a, 5);
    return 0;
}