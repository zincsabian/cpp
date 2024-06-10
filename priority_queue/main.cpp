#include "priority_queue.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

// luogu P3378 【模板】堆

int main() {
    int n;
    std::cin >> n;
    PriorityQueue<int> Q;
    for (; n--; ) {
        int opt;
        std::cin >> opt;
        if (opt == 1) {
            int x;
            std::cin >> x;
            Q.push(-x);
        } 
        else if (opt == 2) {
            std::cout << -Q.top() << '\n';
        }
        else {
            if (!Q.empty())
                Q.pop();
        }
    }
}