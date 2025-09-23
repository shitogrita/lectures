#include <iostream>
#include <functional>

// 15.6 std::function since c++11

// 15.7 std::bind and its usage

// 15.8 std::invoke, std::invoke_result

bool greater(int x, int y) {
    return x > y;
}
 
struct Equal {
    bool operator()(int x, int y) const {
        return x == y;
    }
};

struct S {
    bool not_equal(int x, int y) const {
        return x != y; 
    }
};

template <typename T> 
void f(const T&) = delete;

void test_bind() {
    std::function<bool(int, int)> compare = [](int x, int y) {return x < y; };

    auto compare_wiht_zero = std::bind(compare,0, std::placeholders::_2);

    // f(compare_wiht_zero);

    auto reverse_compare = std::bind(compare, std::placeholders::_2, std::placeholders::_1);   
    std::cout << compare(1, 2) << '\n ';

    std::cout << compare_wiht_zero(-1) << '\n ';
    /* 
    f = greater;
 
    std::cout << f(1, 2) << '\n ';
  
    f = Equal();

    std::cout << f(1, 2) << '\n ';

    std::function<bool(const S&, int, int)> ff = &S::not_equal; // why &S
    */
}

int main() { 
    
    // invoke 

    std::function<bool(int, int)> compare = [](int x, int y) {return x < y; };

    std::cout << std::invoke(comapre, 1, 2) << "\n";

    std::cout << std::invoke(Equal(), 1, 2) << "\n";

    auto not_equal = &S::not_equal;
 

    S S;
    (s.*not_equal)(s, 1, 2);  

    std::cout << std::invoke(not_equal, s, 1, 2) << "\n";
}     