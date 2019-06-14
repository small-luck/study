/*
	简单工厂模式
	一般应用于多种同类型类的情况，将这些类隐藏起来，再提供同一的接口，便于维护和修改

	优点：
		1. 隐藏了的对象创建的细节，将产品的实例化推迟到子类中实现
		2. 方便添加新的产品子类，每次只需要修改工厂类传递的类型值
		3. 遵循了依赖倒转原则

	缺点：
		1. 要求产品子类的类型差不多，使用的方法名都相同
		2. 每添加一个产品篇子类，都必须在工厂类中添加一个判断分支，违反了
		开发封闭原则（软件实体（类，模块，函数）可以扩展，但是不能修改）
*/
#include <iostream>

class Product {
	public:
		virtual void show() = 0;
};

class Product_A : public Product {
	public:
		void show() {
			std::cout << "Product_A" << std::endl;
		}
};

class Product_B : public Product {
	public:
		void show() {
			std::cout << "Product_B" << std::endl;
		}
};

class Factory {
	public:
		Product* Create(int i) {
			switch(i) {
				case 1:
					return new Product_A();
					break;
				case 2:
					return new Product_B();
					break;
				default:
					break;
			}
			return NULL;
		}
};

int main(int argc, char const *argv[])
{
	Factory *factory = new Factory();
	factory->Create(1)->show();
	factory->Create(2)->show();
	return 0;
}