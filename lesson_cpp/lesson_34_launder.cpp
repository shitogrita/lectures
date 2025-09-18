#include <iostream>

// 14.3 Launder
 
struct S {
    const int x;
};

/* 
union U {
    S s;
    float f;
    U() {}
};
*/

int main() {
    S* s = new S{1};

    //new(&u.s) S{1};
    std::cout << s->x << std::endl;

    new(s) S{2};
    std::cout << std::launder(s)->x << std::endl; // UB, may be 1 
}
