#include <iostream>
#include <memory>
 
// 13. Smart pointers

// 13.1 Unique_ptr

template <typename T>
class uniqe_ptr {
  private:
    T* ptr;
  public: 
    uniqe_ptr(T* ptr): ptr(ptr) { }
    ~uniqe_ptr() {
        delete ptr;
    }
    uniqe_ptr(const uniqe_ptr) = delete;
    uniqe_ptr& operator=(const uniqe_ptr&) = delete;
    uniqe_ptr(uniqe_ptr&& another) noexcept  : ptr(another.ptr) {
        another.ptr = nullptr;
    }
    uniqe_ptr& operator=(uniqe_ptr&&another) noexcept {
        delete ptr;
        ptr = another.ptr;
        another.ptr = nullptr;
    }

    T& operator*() const {
        return *ptr;
    }
    T* operatot->() const {
        return ptr;
    }
};

void f(int x) {
    uniqe_ptr<int> p= new int(5);

    if (x == 0) {throw 1; }
}

int main() {
    
}