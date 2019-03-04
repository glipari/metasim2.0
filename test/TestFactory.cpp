#include <vector>
#include <factory.hpp>
#include <catch.hpp>

class A {
    std::string name;
    int index;
public:
    A(const std::string &n, int i) { name = n; index = i; }
    std::string getName() const { return name; }
    int getIndex() const  { return index; }

    virtual std::string getParam() const = 0;
    
};

class B : public A {
    std::string param;
public:
    B(const std::string &n, const std::string &p) : A(n, 1) { param = p; }

    static std::unique_ptr<A> create(std::vector<std::string> &params) {
        if (params.size() > 0)
            return std::unique_ptr<A>(new B("This is B", params[0]));
        else
            return std::unique_ptr<A>(new B("This is B", ""));
    }

    virtual std::string getParam() const { return param; }
};
    
class C : public A {
public:
    C(const std::string &n) : A(n, 2) {}
    
    static std::unique_ptr<A> create(std::vector<std::string> &params) {
        return std::unique_ptr<A>(new C("This is C"));
    }

    virtual std::string getParam() const { return "Error"; }
};


TEST_CASE("Factory1", "factory1")
{
    std::vector<std::string> parameters;
    
    FACT(A).regCreateFn("B", &B::create);
    FACT(A).regCreateFn("C", &C::create);

    SECTION("check type") {
    
        auto ptr1 = FACT(A).create("B", parameters);
        auto ptr2 = FACT(A).create("C", parameters);
        
        REQUIRE(ptr1->getIndex() == 1);
        REQUIRE(ptr2->getIndex() == 2);
    }
    SECTION("check parameters") {
        parameters.push_back("First");
        parameters.push_back("Second");
        
        auto ptr1 = FACT(A).create("B", parameters);
        auto ptr2 = FACT(A).create("C", parameters);
        
        REQUIRE(ptr1->getParam() == "First");
        REQUIRE(ptr2->getParam() == "Error");
    }
}
