#include <iostream>
#include <string>
#include <vector>

// XI. Move-semantics and rvalue-references

// 11.1 Introduction, problem cases

// 11.2 std::move function  

// 11.3 Rvalue-reference, move-operations

class String {
    private: 
        char* arr;
        size_t sz;
        size_t cap;
    public:
        String(const String& s);
        String(String&& s): arr(s.arr), sz(s.sz), cap(s.cap) {
            s.arr = nullptr;
            s.cap = 0;  
            s.sz = 0;
        }
        String& operator=(String&& s) {
            String news(std::move(s));
            swap(news);
            return *this;  
        }
};

template <typename T>
void swap(T& x, T& y) {
    T t = std::move(x);
    x = std::move(y);
    y = std::move(t);
}

template <typename... Args>
void emplace_back(const Args&... args) {
    if (cap == sz) {  
        reserve(2 * sz) 
    }
    new (arr + sz) T(args...);
    + sz;

}

std::string f() {
    return std::string("abcdef");
}
  
int main() {
    std::vector<std::string> v;
    //v.push_back(std::string("abcdefg"));
 
    // Args: int, const cahr*


    std::string s = "abc";
    std::string ss = std::move(s);

    v.emplace_back(std::move(ss)); 

     
     
} 