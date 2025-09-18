#include <iostream>

int main() {
    int a = 1;
    int& b = a;
    // int& c = 2;
    // int&& d = a;
    int&& d = 2;

    int&& e = 5;
    int& g = e;
    int&& h = std::move(e);
 
    const int&& i = 5;   
    const int&& j = (const int&&)(a);   
      
}  

template <typename T>
std::remove_reference_t<T>&& move(T&& x) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(x);
} 