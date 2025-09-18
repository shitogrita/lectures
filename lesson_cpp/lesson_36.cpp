#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

// Lambda functions and elements of functional programming 
// 15.1 General idea and basic syntax

// 15.2 capture lists in lambda function s

struct MyCocmpare {
    bool operator() (int x, int y) const {
        return std::abs(x - 5) < std::abs(y - 5);
    }
};

auto get_compare() {
    return [](int x, int y) {return x*x < y*y; }; // r-value
}

void test1() {  

    std::vector<int> v{4, 6, 3, 2, 7, 1, 9, 8};

    auto f  =  [](int x, int y) -> bool {
        return std::abs(x - 5) < std::abs(y - 5);
    };

    std::map<int, int, decltype(f) > m;
    /*
        auto f  =  [](int x, int y) -> bool{
        return std::abs(x - 5) < std::abs(y - 5);
    }; 
    */


    std::sort(v.begin(), v.end(), get_compare());
       

    [ ](int x) {
        std::cout << x << "\n";
    }(5);

    for (const auto& x: v) {
        std::cout << x << std::endl; 
    }
} 

int main() {
    
    int a = 1;

    int b = 2;

    [a](int x) mutable { // a is copy и констаннтность автоматически навещиваеться 
        std::cout << x + a << "\n";
        ++a;  
    }(5);

    [&a, b](int x) { // a is not copy and will be change и константность не навезиваеться автоматически 
        std::cout << x + a << "\n";
        ++a, ++b;  
    }(5);
}