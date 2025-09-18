template <typename T, typename Alloc >

class vector {
    Vector(size_t count, const Alloc& alloc = Alloc()): alloc(alloc) {
        reserve(count);
        for (size_t i = 0; i < count ; ++ i) {
            alloc.construct(arr + i , value);
        }
    }
}
 
p->~T();
::operator delete(param) p;

new_handler 
get_new_handler
set_new_hasdler(f);



template <class T>  // class? 
struct allocator {
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

}

