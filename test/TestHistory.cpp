#include "catch.hpp"
#include <iostream>
#include <history.hpp>

using namespace std;

// template <class C>
// void print(C& c)
// {
//   typedef typename C::iterator CI;
//   CI i;
//   cout << '[';
//   for (i = c.begin(); i != c.end(); ++i) {
//     cout << *i << " ";
//   }
//   cout << ']' << endl;
// }


TEST_CASE("Testing the history container", "[history]")
{
    history<int> h1(10);
    
    for (register int i = 0; i < 10; i++) {
        h1.push_back(i);
    }
    //print(h1);
    REQUIRE(h1.front() == 9);
    REQUIRE(h1.back() == 0);
    // cout << "Front=" << h1[0] << endl;
    // cout << "Back=" << h1[9] << endl;
    for (register int i = 10; i < 20; i++) {
        h1.push_back(i);
    }
    //print(h1);
    // cout << "Front=" << h1.front() << endl;
    // cout << "Back=" << h1.back() << endl;
    REQUIRE(h1.front() == 19);
    REQUIRE(h1.back() == 10);
}
