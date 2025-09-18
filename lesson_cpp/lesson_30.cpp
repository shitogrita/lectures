// 11.11 

void reserve(size_t n) {
    if (n <= capacity) return n;
    T* newarr = AllocTraits::allocate(alloc, n);

    size_t i = 0;

    try {
        for (size_t i = 0; i < sz; i ++) {
            AllocTraits::construct(alloc, newarr + i, std::move(arr[i]));
        }  
        // std::uninitialized_copy(arr, arr + sz, newarr);
    } catch (...) {
        for (size_t j = 0; j < i; j ++) {
            AllocTraits::destroy(alloc, newarr + j);
        }  
        AllocTraits::deallocate(alloc, newarr, n);
        throw;
    }

    for (size_t i = 0; i < sz; ++i) {
        AllocTraits::destroy(alloc, arr + i); 
    }
}

// 12 Type deduction (sice c++ 11)

// 12.1 auto keyword  

int main() {
    std::unordered_map<int, std::string> m;
    m[1] = "src";
 
    auto&& x = y;
    for (auto& p: m)
}

template <typename T, typename U>
auto&& f(const T& x, const U& y) {
    return x>y? x, y;
}
  // =
void g(const auto& x) { // (since c++ 20 or 23)
}

// 12.2 decltype  (declared type)

template <typename Container>
decltype(auto) get_at(Container& container, size_t index) { // (c++ 14)
//auto get_at(Container& container, size_t index) -> decltype(containers[index]) {  (c++ 11)
//decltype(container[index]) get_at(Container& container, size_t index) {
    return container[index];
} 
  
// if expr is lvalue of type T, then decltype returns T&
// if expr is prvalue of type T, then decltype returns T
// if expr is xvalue of type T, then decltype returns T&&
