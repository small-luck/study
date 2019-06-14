/*
    工厂方法模式：和简单工厂模式差不多，但是解决了简单工厂模式每增加一个
    产品子类，都必须修改工厂类方法的问题。解决的方法是增加了工厂的数量，
    每个工厂对应一个产品。

    缺点：当产品数量过于多，并且一个所有的类又必须添加一种方法，则会非常麻烦
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
    virtual Product* Create() = 0;
};

class Factory_A : public Factory {
public:
    Product* Create() {
        return new Product_A();
    }
};

class Factory_B : public Factory {
public:
    Product* Create() {
        return new Product_B();
    }
};

int main(int argc, char const *argv[])
{
    Factory_A* fa = new Factory_A();
    Factory_B* fb = new Factory_B();

    fa->Create()->show();
    fb->Create()->show();
    return 0;
}
