#include <iostream>

// 14 Vocabulary types and erasure idiom

// pair, tuple, variant, any, optional  

// 14.1 Unions

struct S {
    int i;
    double d;
    std::string  str;
};


// template <typename T> можно, но нахуя ...
union U {
    int i;
    // int ii;
    double d;   
    std::string str;

    U(): i(0){}
    ~U() {}
};

int main() {
    std::cout << sizeof(S) << " " << sizeof(U) <<std::endl;

    U u;
  
    new (&u.str) std::string("abc");
    u.i = 5;


    // std::cout << u.ii << "\n"; // anwser = 5;
    std::cout << u.str << "\n";
    u.str.~basic_string<char>();
}