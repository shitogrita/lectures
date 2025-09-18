#include <iostream>
#include <cstdlib>

void* operator new(size_t n) {
    std::cout << "allocated " <<  n << std::endl;
    return malloc(n);  
}
 
void operator delete(void* ptr) noexcept {
    std::cout << "deallocated (no size)" << std::endl;
    free(ptr);
}

void operator delete(void* ptr, size_t n) {
    std::cout << "deallocated" << n << std::endl;
    free(ptr);
}

void* operator new[](size_t n) {
    std::cout << "allocated arr" << n << std::endl;
    return malloc(n);
}

void operator delete[](void* ptr) {
    std::cout << "deallocated arr[]" << std::endl;
    free(ptr);
}
struct S {
    int x = 0;
    double d = 0.0;
    static void* operator new(size_t n) {
        std::cout << "allocated " << std::endl;
        return malloc(n);
    }
}
int main() {
    
    int* p = new int[5];
    delete[] p;

    double* pd = new double(3.14);
    delete pd;
}

 


--------------------------------------------------------------------------------------------

template <typename T> 
class allocated {
    public:
        T* allocate(size_t count) const {
            return ::operator new(count * sizeoff(T));
        }
        void deallocated(T* ptr, size_t /* count */) {
            ::operator delete(ptr);
        }
        template <typename ...Args>
        void construct(T* ptr, const Args&... args) {
            new(ptr) T(args...);
        } 
        void destoy(T* ptr) {
            ptr->~T();
        }
};


template <typename T, typename Alloc >

class vector {
    Vector(size_t count, const Alloc& alloc = Alloc()): alloc(alloc) {
        reserve(count);
        for (size_t i = 0; i < count ; ++ i) {
            alloc.construct(arr + i , value);
        }
    }
}