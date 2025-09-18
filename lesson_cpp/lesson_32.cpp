#include <iostream>

// 13.2 shared_ptr 

template <typename T>
class shared_ptr {
  private:
    T* ptr = nullptr;
    size_t* counter = nullptr;

    template <typename U>
    struct ControlBlock {
        size_t shared_counter;
        size_t weak_counter;
        U object;
    };

    template <typename U>
    class weak_ptr;

    ControlBlock<T>* cptr = nullptr;

    template <typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&&... args);

    struct make_shared_t;

    template <typename... Args>
    shared_ptr(make_shared_t, ControlBlock<T>* storage_ptr): 
        cptr(storage_ptr) {
         
    }

  public:
    shared_ptr() {}
    shared_ptr(T* ptr): 
        ptr(ptr), counter(new size_t(1)) { }
    shared_ptr(const shared_ptr& other):
        ptr(other.ptr), count(other.count) {
            ++*counter;
    }
    shared_ptr(shared_ptr&& other):
        ptr(other.ptr), counter(other.counter) {
            other.ptr = nullptr;
            other.counter = nullptr;
    }
    
    T& operator*() const{
        return *ptr;
    }
    T* operator->() const{
        return ptr;
    }

    size_t use_count() const {
        return *counter;
    }

    ~shared_ptr() {
        --cptr->shared_count;
        if (cptr->shared_counter > 0) {
            --cptr->counter;
            return; 
        }
        if (cptr->weak_counter == 0) {
            delete cptr;
            return;
        }
        cptr-.object.~T();
    }
};
 
// 13.5 weak_ptr

template <typename T>
class weak_ptr {
  private:
    ControlBlock<T>* cptr = nullptr; 
  public: 
    weak_ptr(const shared_ptr<T>& ptr):
        cptr(ptr.cptr) {}
    
    bool expired() const {
        return cptr->counter > 0;
    }
     
    ~weak_ptr() {
        --cptr->weak_counter;
        if (cptr->shared_count == 0 && cptr->weak_counter == 0) {
            // deallocate
        }
    }
    
    shared_ptr<T> lock() const {

    }
};

// 13.3 make_shared, make_uniqe

struct S {
    int x = 0;
    std::string str;

    S(int x, const std::string& str): x(x), str(str) {}
}; 

template <typename T,typename Alloc, typename... Args>
shared_ptr<T> mallocate_shared(Alloc& alloc, Args&&... args) { 
    
} 

// since c++11
template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) { 
    return allocate_shared(std::allocator<T>(), std::forward<Args>(args)...);
    // auto ptr = new ControlBlock<T>{1,  T{std::forward<Args>(args)...}};
    // return shared_ptr<T> (shared_ptr::make_shared_t(), ptr);
}

// since c++14
template <typename T, typename... Args>
uniqe_ptr<T> make_uniqe(Args&&... args) {
    return uniqe_ptr<T>(new T(std::forward<Args>(args)...));
}


  
int main() {
    int* p = new int(5);

    shared_ptr<int> sp = p;
    shared_ptr<int> ssp = p;

    auto sp = make_shared<S>(5, "abc");
    // shared_ptr<int> = ssp = p;

}


// 13.5 weak_ptr


  