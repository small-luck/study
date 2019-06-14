/*
    策略模式：定义一系列的算法，把它们封装起来，并且使他们可以相互替换。
    策略模式为了适应不同的需求，只把变化点封装了，这个封装点就是实现不同需求的算法

    strategy（抽象策略角色）: 定义所有支持的算法的公共接口。context使用这个接口来
    调用concretestrategy定义的某个算法

    concreteStrategy（具体策略角色）：实现Strategy接口的具体算法

    Context（环境角色）：使用一个ConcreteStrategy对象来配置；维护一个对Strategy
    对象的引用，同时可以定义接口来让strategy访问它的数据
*/

#include <iostream>

//The abstract strategy
class Strategy {
public:
    virtual void AlgotithmInterface() = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void AlgotithmInterface() {
        std::cout << "I am from ConcreteStrategyA" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void AlgotithmInterface() {
        std::cout << "I am from ConcreteStrategyB" << std::endl;
    }
};

class ConcreteStrategyC : public Strategy {
public:
    void AlgotithmInterface() {
        std::cout << "I am from ConcreteStrategyC" << std::endl;
    }
};

class Context {
public:
    Context(Strategy *pstrategyArg) : pStrategy(pstrategyArg) {

    }

    void ContextInterface() {
        pStrategy->AlgotithmInterface();
    }

private:
    Strategy *pStrategy;
};

int main(int argc, char const *argv[])
{
    Strategy *pStrategyA = new ConcreteStrategyA();
    Strategy *pStrategyB = new ConcreteStrategyB();

    Context *pContextA = new Context(pStrategyA);
    Context *pContextB = new Context(pStrategyB);

    pContextA->ContextInterface();
    pContextB->ContextInterface();

    if (pStrategyA) {
        delete pStrategyA;
        pStrategyA = NULL;
    }

    if (pContextB) {
        delete pStrategyB;
        pStrategyB = NULL;
    }

    if (pContextA) {
        delete pContextA;
        pContextA = NULL;
    }

    if (pContextB) {
        delete pContextB;
        pContextB = NULL;
    }
    return 0;
}