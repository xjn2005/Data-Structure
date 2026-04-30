#include <iostream>

#include "ds/disjoint_set/disjoint_set.hpp"

int main() {
    ds::disjoint_set::DisjointSet dsu(6);
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    std::cout << "0 and 2 connected: " << std::boolalpha << dsu.connected(0, 2) << '\n';
    std::cout << "2 and 4 connected: " << std::boolalpha << dsu.connected(2, 4) << '\n';
    std::cout << "component size of 1: " << dsu.componentSize(1) << '\n';

    return 0;
}
