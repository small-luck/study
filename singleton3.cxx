//单例模式 饿汉模式 类加载时就分配空间 以空间换时间 线程安全，不需要加锁
//为什么饿汉模式是线程安全的？
//因为在饿汉模式下，单例模式在加载类的时候就定义了一个对象，分配了空间。后面不管哪个线程调用get_instance函数，
//获取的都是这个对象的指针，所以线程是安全的，不需要在get_instance中加锁。
#include <iostream>

class singleton {
	public:
		static singleton* get_instance() {
			std::cout << "get_instance()" << std::endl;
			return instance;
		}

		void print() {
			std::cout << "call print function" << std::endl;
		}
	private:
		singleton() {
			std::cout << "singleton()" << std::endl;
		}

		static singleton* instance;
};
singleton* singleton::instance = new singleton();

int main(int argc, char const *argv[])
{
	singleton* p1 = singleton::get_instance();
	singleton* p2 = singleton::get_instance();

	std::cout << "p1 = " << p1 << std::endl;
	std::cout << "p2 = " << p2 << std::endl;

	p1->print();
	return 0;
}