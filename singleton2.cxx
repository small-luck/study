#include <iostream>
#include <pthread.h>
//单例模式，懒汉模式，加锁，嵌套一个析构类
class singleton {
    public:
        static singleton* get_instance() {
            if (instance == NULL) {
                pthread_mutex_lock(&mutex);
                instance = new singleton();
                std::cout << "对象创建成功" << std::endl;
                pthread_mutex_unlock(&mutex);
            } else {
                std::cout << "对象已经创建成功，无须再建" << std::endl;
            }
            return instance;
        }

        static pthread_mutex_t mutex;

    private:
        singleton() {
            pthread_mutex_init(&mutex, NULL);
            std::cout << "singleton()" << std::endl;
        }
        static singleton* instance;        

        //创建一个内部类，实现释放申请的资源
        class GC {
            public:
                ~GC() {
                    if (instance != NULL) {
                        std::cout << "释放申请的资源" << std::endl;
                        delete instance;
                        instance = NULL;
                    }
                }
        };
        static GC gc;   //定义静态成员变量，当程序结束时，系统自动调用析构函数
};
singleton* singleton::instance = NULL;
pthread_mutex_t singleton::mutex;

int main(int argc, char const *argv[])
{
    singleton* p1 = singleton::get_instance();
    singleton* p2 = singleton::get_instance();

    return 0;
}