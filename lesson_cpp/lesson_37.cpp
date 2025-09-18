#include <iostream>

// 15.4 capture of this

// 15.5 default-capture and capture with initialization

struct S {
    int a = 5;

    void get_function (int i) {

        std::string s ="abccde";
        // since c++ 14  
        // auto f = [s = std::move(s)]() {

        auto f = [i, &s = std::as_const(s)]() { // allways yon can got const &
            std::cout << s[i] << '\n';
        };
        return f;
    }
 
};

int main() {

    int a = 1;

    std::string ss = "abcde"; 


    {
        std::string s ="abccde";

        auto g = [=]() {return s[i]; }; // [=] все по const, [&] захвват всего по ссылке

        // auto h = [&s](int i) {return s[i]; };
    }

    std::sort(v.begin(), v.end(), [](const auto& x, const auto& y) {return x[0] < y[0]; }); 
    
    auto f = S().get_function(1);
    auto ff = S().get_function(2);

    ff();
    f();  

}