#include <iostream>
#include <vector>
#include <type_traits>

// 16.4 std::enable_if 

template <bool B, typename T = void >
struct enable_if {

};

template <typename T >
struct enable_if<true, T> {
    using type =  void;
};

template <bool B, typename T = void >
using enble_if_t = typename enable_if<B, T>::type;

template <typename T, typename = enable_if_t<std::is_class_v<T>>>
void f(const T&) {
    std::cout << 1;
}

void f(...) {
    std::cout << 2;
}

int main() {
    std::string s("abc");
    f(s);
    f(1);
}