#include <iostream>
#include <vector>
#include <string>

 
template <typename T>
class MyAllocator: public std::allocator<T> {
    public: 
        template <typename U>
        MyAllocator(const MyAllocator<U>& ) {

        }
        T* allocate(size_t count) const {
            std::cout <<  "allocate\n";
            return ::operator new(count * sizeoff(T));
        }
        void deallocate(T* ptr, size_t /* count */) {
            ::operator delete(ptr);
        }
        template <typename... Args>
        void construct(T* ptr, const Args&... args) {
            new(ptr) T(args...);
        }
        void destroy(T* ptr) {
            ptr->~T();
        }
}; 

// 10.8 Scoped Allocators

template <typename OuterAlloc, typename... Inner Alloc>
struct scoped_allocator_adapter: public OutherAlloc{
private:
    scoped_allocator_adapter<InnerAlloc...> inner_alloc;
public:
    template <typename T, typename... Args> 
    void construct(T* ptr, const Args&... Args) {
        if (/* elem if type T can be created with instance of InnerAlloc */) {
            new(ptr) T(args..., inner_alloc);
        }
        else () {
            new(ptr) T(args...);
        }
    }
};

int main() {
    // using MyString = std::basic_string<char, std::char_traits<char>, MyAllocator<char>>;
    using MyVector = std::vector<int, MyAllocator<int>>;
    // std::vector<MyVector, MyAllocator<MyVector>> v;   

    MyAllocator<MyVector> outer_alloc;
    MyAllocator<int> inner_alloc(outer_alloc);  

    std::vector<MyVector, std::scoped_allocator_adapte<MyAllocator<MyVector>, MyAllocator<int>>> v(outer_alloc);
    v.push_back(MyVector(1));
}



// 10.9 alignments

struct alignas(8)S {
    int x;
    double y;
    int z;  
    // int double int 24 bits
    // int int double 16 bitd

};

int main() {  

    std::cout << sizeof(S);

    std::cout << alignof(S); // 8
 


}