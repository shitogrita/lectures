#include <iostream>
#include <any>

// 14.4 std::any (since c++17)

// type erasure idiom

class any {
  private:
    void* storage; 

    struct Base {     
        virtual ~Base() {}
    };

    template <typename T>   
    struct Derived: public Base {
        T value;

        Derived(const T& value): value(value) { }

        Base* get_copy() override {
            return new Derived<T>(value);
        }
    };

    Base* storage = nullptr; 

  public:

    template <typename U>
    any(const U& value): storage(new U(value)): storage(new Derived<U> (value)) { }

    ~any() {
        delete storage;
    }

    any(const any& a): storage(a.storage->get_copy()) { }
    
    // TODO: distinguish between const U& and const any& 
    template <typename U>
    any& operator=(const U& value) {
        delete storage;
        storage = new.Derived<U>(value); 
    }
};

int main() {

}