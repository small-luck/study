#include <iostream>
#include <functional>

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

void print_single(int i)
{
    std::cout << i << std::endl;
}

void print_double(int i) 
{
    std::cout << i * 2 << std::endl;
}


int main(int argc, char const * argv [ ])
{
    Foo *f = new Foo();
    f->set_printcb(print_single);
    f->Print();

    f->set_printcb(print_double);
    f->Print();
    return 0;
}

