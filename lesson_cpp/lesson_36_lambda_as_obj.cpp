#include <iostream>

// 15.3 Lambda functions as object

template <typename T>
void g(const T&) = delete;
int main() {
    int a = 1;

    auto f = [a](int x, int y) {
         return a + x < y;
    };
     
    std::cout << typeid(f).name();
}