/*
    移动构造，C++11新特性
*/
#include <iostream>
#include <vector>
#include <string>

class test {
    public:
        test(std::vector<std::string> &_vec) {
            for(auto &i : _vec) {
                vec.push_back(std::move(i));
            }
        }

        std::vector<std::string> vec;
};

int main(int argc, char const * argv [ ])
{
    /*起初，右值{"123", "456", "789", "012", "345"} 都归属于左值temp*/
    std::vector<std::string> temp = {"123", "456", "789", "012", "345"};
    for (auto &i : temp) {
        std::cout << "old element = " << i << std::endl;
    }
    std::cout << "=================" << std::endl;

    /*由类test的构造函数，更改右值的所有者为类test的对象*/
    test tt(temp);
    for (auto &i : temp) {
        std::cout << "new element = " << i << std::endl;
    }
    std::cout << "=================" << std::endl;
    
    for (auto &i : tt.vec) {
        std::cout << "vec element = " << i << std::endl;
    }
    
    return 0;
}

