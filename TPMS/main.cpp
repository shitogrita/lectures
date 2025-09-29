#include "mutex.h"
#include <iostream>
#include <thread>
#include <vector>

void test_mutex() {
    mutex m;
    int counter = 0;

    auto worker = [&]() {
        for (int i = 0; i < 10000; ++i) {
            m.lock();
            ++counter;
            m.unlock();
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i)
        threads.emplace_back(worker);

    for (auto& t : threads) t.join();

    std::cout << "counter = " << counter << std::endl;
}

int main() {
    test_mutex();
}