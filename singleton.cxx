#include <iostream>
//单例模式
//1. 懒汉，非线程安全
class singleton {
    public:
        static singleton* get_instance() {
            if (instance == NULL) {
                instance = new singleton();
                std::cout << "对象创建成功" << std::endl;
            } else {
                std::cout << "对象已经创建成功，无须再建" << std::endl;
            }
            return instance;
        }

    private:
        singleton() {   //将构造函数私有化
            std::cout << "singleton()" << std::endl;
        }  
        static singleton *instance;
};
singleton* singleton::instance = NULL;

int main(int argc, char const *argv[])
{
    singleton *p1 = singleton::get_instance();
    singleton *p2 = singleton::get_instance();

    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    return 0;
}