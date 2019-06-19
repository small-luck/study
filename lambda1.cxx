#include <iostream>
    
int main(int argc, char const * argv [ ])
{
    int a = 1, b = 2;
    auto multi = [](int a, int b) {
        b = a + a + a;
        return  a+b;
    };

    std::cout << multi(a, b) << std::endl;
    return 0;
}