#include <iostream>
#include <functional>

// 15.6 std::function since c++11

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

int main() {
    std::function<bool(int, int)> f = [](int x, int y) {return x < y; };

    std::cout << f(1, 2) << '\n ';

    f = greater;

    std::cout << f(1, 2) << '\n ';

    f = Equal();

    std::cout << f(1, 2) << '\n ';

    std::function<bool(const S&, int, int)> ff = &S::not_equal; // why &S
}
