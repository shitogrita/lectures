
// c++ 17
// 12.3 Structured bindings and tuples

std::pair<int, std::string> p{3, "abc"};

auto [key, value] = p;
std::cout << key << " " << value << std::endl;
 
S s;

auto& [x, y] = s;

for (auto& [key, value]: m) {

}

// tuple for more than 2, like 
std::tuple<int, std::string, double> t{1,"aabc", 0.5}
auto& [x,y,z] = t;

std::get<0>(t) = 3;
std::get<int>(t) = 3;

// 12.4 std::common_type(наименьщий общий тип) implementation

// decltype: expression -> its type
// declval: type -> expression of this type 

template <typename T>
class BigClass {
    // ...  
};

// incomplete type
struct SS; 

template <typename T>
class C{
    C() = delete;
};

template <typename T>
std::add_rvalue_reference_t<T> declval() noexcept;

template <typename... Types>
struct common_type {
    using type = typename common_type<Head, typename common_type<Tail...>::type>::type;
};

template <typename T, typename U>
struct common_type<T, U> {
    using type = std::remove_reference_t<decltype(true ? std::declval<T>(): std::declval<U>())>; 
};

struct Granny {};

struct Mother: public Granny {};

struct Father: public Granny {};


template <typename... Types>
using common_type_t = typenmae common_type<Types... >::type;

int main() {
    C <common_type< Granny, Father> >(); // наимменьший предок 

} 
