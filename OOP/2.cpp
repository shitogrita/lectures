
template <typename... Args>
void construct(T* p, const Args&... args) noexcept( noexcept( T( args...))) {
    new (p) T(args...);
}

void dectroy(T* p){
    p->~T();
}

template <class T>
struct allocator {
    T* Allocate (size_t n){
        return ::operator new(n* sizeof(T));
    }
    void deallocate (T* p, site_t n) {
        ::operator delete(p);
    }
}

using value_type = T;

  
/*
p->~T()
::operator delete(param) p;
*/



// ALLOCATOR TRAITS 

template <typename alloc> 
struct allocator_traits {
    static Alloc::value_type* allocate(Alloc& alloc, size_t n ) {
        return alloc.allocate(n);
    }
    // ?
    Alloc alloc;
    size_t sz;
    size_t cp;
    T* arr;
}

void push_back(const T& x) {
    using traits = std::allocator_tarits<Alloc>;
    if (sz < cp) {
        T* newarr = traits::allocate(cp <<= 1);
        for (size_t i = 0; i < sz ; ++i) {
            traits::construct( newarr + i, arr[i]);
            // std::move 
            traits::destory(arr + i);
        }
        traits::deallocate(arr, sz);
        arr = newarr;
    }
    traits::construct(newarr + sz++, x);
}