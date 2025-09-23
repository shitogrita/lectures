#include <iostream>
#include <vector> 
#include <memory>
// 16 SFINAE idiom, template metaprogramming and compile-time computations.

// 16.1 idea and basic example of SFINAE

// SFINAE = Substitution Failure Is not An Error !

// 16.5 is_constructible, is_assigble ect. implementations

struct S {
    size_t size() & {
        return 0;
    }
};

template <typename T> 
auto f(const T& x) -> decltype(T().size()) {
    std::cout <<  1 << '\n';
    return 1;
}

size_t f(...) {
    std::cout << 2 << '\n';
    return 2;
}

// 16.2 Check of method presence in a class

// decltype: value -> its type
// declcal: type -> value of its type

// 16.3 integral_constatn, true type and false type 

// 16.4 std::enable_if and its usage

using std::declval;

template <typename T, T value_>
struct integral_construct {
    static const T value = value_;
};

struct true_type: public integral_construct<bool, true> {};
struct false_type: public integral_construct<bool, false> {};

template <typename T, typename... Args>
struct has_method_construct {
  private:
    // constexpr auto f(int) ->decltype(T().construct(Args()...), int()) {
    template <typename TT, typename... AArgs, typename = decltype(declval<TT>().construct(declval<AArgs>()...), int())>
    static true_type f(int);
    template <typename...>
    static false_type f(...);
  public:
    // static cost bool value = sizeoff(f<T, Args...>(0)) == sizeoff(int) ;
    using type = decltype(f<T, Args...>(0));
};

template <typename T, typename... Args>
bool has_method_construct_v = std::is_same_v<typename has_method_construct<T, Args...>::type, true_type>;

template <typename T, typename... Args>
struct is_constructible{
  private:
    // constexpr auto f(int) ->decltype(T().construct(Args()...), int()) {
    template <typename TT, typename... AArgs, typename = decltype(TT(declval<AArgs>()...))>
    static true_type f(int);
    template <typename...>
    static false_type f(...);
  public:
    // static cost bool value = sizeoff(f<T, Args...>(0)) == sizeoff(int) ;
    static const bool value = decltype(f<T, Args...>(0))::value;
};

template <typename T, typename... Args>
bool is_constructible_v = is_constructible<T, Args...>::value;

template <typename T>
struct is_copy_constructible{
  private:
    // constexpr auto f(int) ->decltype(T().construct(Args()...), int()) {
    template <typename TT, typename = decltype(TT(declval<const TT&>()))>
    static true_type f(int);
    template <typename...>
    static false_type f(...);
  public:
    // static cost bool value = sizeoff(f<T, Args...>(0)) == sizeoff(int) ;
    static const bool value = decltype(f<T>(0))::value;
};

template <typename T, typename... Args>
bool is_copy_constructible_v = is_copy_constructible<T>::value;

template <typename T>
struct is_mothrow_move_constructible{
  private:
    // constexpr auto f(int) ->decltype(T().construct(Args()...), int()) {
    template <typename TT, typename = enable_if_t<noexcept(TT(declval<TT>()))>>
    static true_type f(int);
    template <typename...>
    static false_type f(...);
  public:
    // static cost bool value = sizeoff(f<T, Args...>(0)) == sizeoff(int) ;
    static const bool value = decltype(f<T>(0))::value;
};

// WRONG!!!
template <typename T>
bool is_mothrow_move_constructible_v = is_move_constructible<T>
    && noexcept(T(declval<T>()) );


struct Test {
    void construct(int, int);
    void construct(double);
    void construct(const std::string&);
};

int main() {
    std::vector<int> v{1, 2, 3};
    f(v);  
    f(1);

    S s;
    f(s);

    std::cout << has_method_construct_v<Test, int, int> << '\n';  

    std::cout << is_constructible_v<std::string, int> << '\n';
    std::cout << is_constructible_v<std::string, int, char> << '\n';

    std::cout << is_copy_constructible_v<std::unique_ptr<int>> << '\n';

}
