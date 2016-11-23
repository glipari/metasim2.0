#include <vector>
#include <factory.hpp>
#include <catch.hpp>

class A {
    std::string name;
    int index;
public:
    A(const std::string &n, int i) { name = n; index = i; }
    std::string getName() { return name; }
    int getIndex()   { return index; }
};

class B : public A {
public:
    B(const std::string &n) : A(n, 1) {}

    static std::auto_ptr<A> create(std::vector<std::string> &params) {
        return std::auto_ptr<A>(new B("This is B"));
    }
};
    
class C : public A {
public:
    C(const std::string &n) : A(n, 2) {}
    
    static std::auto_ptr<A> create(std::vector<std::string> &params) {
        return std::auto_ptr<A>(new C("This is C"));
    }
};
    

TEST_CASE("Factory", "factory1")
{
    std::vector<std::string> parameters;
    
    FACT(A).regCreateFn("B", &B::create);
    FACT(A).regCreateFn("C", &C::create);

    std::auto_ptr<A> ptr1 = FACT(A).create("B", parameters);
    std::auto_ptr<A> ptr2 = FACT(A).create("C", parameters);

    REQUIRE(ptr1->getIndex() == 1);
    REQUIRE(ptr2->getIndex() == 2);
}
