#include <iostream>

template <typename T> 
std::remove_reference_t<T>&& move(T&& x) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(x);
}

// 11.11 move_if_noexcept
 
// if move-constructor is deleted, we should return faalse, but will generated CE
template <typename T>
T f() noexcept; // rvalue

template <typename T> 
std::conditional_t<noexcept(T(f<T>())), T&&, const T&> move_if_noexcept(T& x) noexcept {
    return std::move(x);
} 

// 11.8 Perfect forwarding problem

template <typename T>
T&& Forward(std::remove_reference_t<T>& x) {
    return static_cast<T&&>(x);
} 

template <typename T>
T&& Forward(std::remove_reference_t<T>&& x) {
    static_assert(!std::is_lvalue_reference_v<T>);
    return static_cast<T&&>(x);
} 
 
template <typename... Args>
void emplace_back(const Args&... args) {
    if (cap == sz) {reserve(2*sz);}
    new (arr + sz) T(std::forward<Args>(args)...);
    ++sz;
}  

struct Base {
    virtual ~Base() {}
};

struct Derived : public Base { 
};

int main() {
    Base d = Derived(); // полиморфоное поведение 
}   


// 11.10 reference qualifiers


struct Data {
    Data(const std::string& s): data(s) {}
    
    std::string getData()    & {
        return data;
    }

  privet:
    std::string data;
};

void f(Data&& x) {
    std::string data = x.getData();
}