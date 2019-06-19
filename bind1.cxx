#include <iostream>
#include <functional>

/*
    std::bind
    由类的成员函数构造bind对象
*/

//在<>中声明回调的类型，void是函数的返回值类型，int是参数类型
typedef std::function<void(int)> Callback_Fun;


class Foo {
    public:
        void Print() {
            if (print_fun) {
                print_fun(num);
            }
        }

        void set_printcb(Callback_Fun cb) {
            print_fun = cb;
        }

    private:
        Callback_Fun print_fun = nullptr;
        int num = 10;
};

class Mytest {
    public:
        void test_print(int i) {
            std::cout << "i = " << i << std::endl;
        }
};

int main(int argc, char *argv[])
{
    Foo *f = new Foo();
    Mytest *test = new Mytest();

    f->set_printcb(std::bind(&Mytest::test_print, test, std::placeholders::_1));
    f->Print();

    delete f;
    f = nullptr;

    delete test;
    test = nullptr;
    
    return 0;
}
