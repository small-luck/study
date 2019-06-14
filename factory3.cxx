/*
    抽象工厂模式：因为简单工厂模式和工厂方法模式要求产品子类必须是同一类型的，拥有共同
    的方法，这就限制了产品子类的扩展。
    于是抽象工厂模式将同一类的产品子类归为一类，让他们继承同一个抽象子类。

    优点：
    1. 封装了产品的创建，不需要知道具体是哪种产品，只需要知道是哪个工厂就行了
    2. 可以支持不同类型的产品，灵活性更强

    缺点：
    1. 结构臃肿。如果产品类型比较多，或者产品族类比较多，非常难于管理
    2. 每次如果添加一组产品，那么所有工厂类都必须添加一个方法，这样违背了开放-封闭原则
*/

#include <iostream>

class Product1 {
public:
    virtual void show() = 0;
};

class Product_A1 : public Product1 {
public:
    void show() {
        std::cout << "Product_A1" << std::endl;
    }
};

class Product_B1 : public Product1 {
public:
    void show() {
        std::cout << "Product_B1" << std::endl;
    }
};

class Product2 {
public:
    virtual void show() = 0;
};

class Product_A2 : public Product2 {
public:
    void show() {
        std::cout << "Product_A2" << std::endl;
    }
};

class Product_B2 : public Product2 {
public:
    void show() {
        std::cout << "Product_B2" << std::endl;
    }
};

class Factory {
public:
    virtual Product1 *create1() = 0;
    virtual Product2 *create2() = 0;
};

class FactoryA : public Factory {
public:
    Product1 *create1() {
        return new Product_A1();
    }

    Product2 *create2() {
        return new Product_A2();
    }
};

class FactoryB : public Factory {
public:
    Product1 *create1() {
        return new Product_B1();
    }

    Product2 *create2() {
        return new Product_B2();
    }
};

int main(int argc, char const *argv[])
{
    FactoryA *fa = new FactoryA();
    fa->create1()->show();
    fa->create2()->show();

    FactoryB *fb = new FactoryB();
    fb->create1()->show();
    fb->create2()->show();

    return 0;
}