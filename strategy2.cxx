/*
    策略模式与简单工厂模式结合，使代码具有可读性和高可用

    以下代码实例中，以游戏角色不同的攻击方式为不同的策略，游戏角色即为执行
    不同策略的环境角色
*/
#include <iostream>

//抽象策略类，提供一个接口
class Hurt {
public:
    virtual void blood() = 0;
};

//具体的策略实现类，具体实现接口，ADC持续普通攻击
class AdcHurt : public Hurt {
public:
    void blood() override {
        std::cout << "Adc hurt, Blood loss" << std::endl;
    }
};

//具体的策略实现类，具体实现接口，Apc技能攻击
class ApcHurt : public Hurt {
public:
    void blood() override {
        std::cout << "Apc hurt, Blood loss" << std::endl;
    }
};

//环境角色类 游戏角色战士 传入一个策略指针参数
class Soldier {
public:
    Soldier(Hurt *hurt) : m_pHurt(hurt) {}

    //再不同策略下，该游戏角色表现出不同的攻击
    void attack() {
        m_pHurt->blood();
    }

private:
    Hurt *m_pHurt;
};

//定义策略标签
typedef enum {
    Hurt_Type_Adc,
    Hurt_Type_Apc,
    Hurt_Type_Num
}HurtType;

//环境角色类 游戏角色法师，传入一个策略标签参数
class Mage {
public:
    Mage(HurtType type) {
        switch(type) {
            case Hurt_Type_Adc:
                m_pHurt = new AdcHurt();
                break;
            case Hurt_Type_Apc:
                m_pHurt = new ApcHurt();
            default:
            break;
        }
    }

    ~Mage() {
        delete m_pHurt;
        m_pHurt = nullptr;
        std::cout << "~Mage()" << std::endl;
    }

private:
    Hurt *m_pHurt;
};

//环境角色类 游戏角色弓箭手 实现模板传递策略
template<typename T>
class Archer {
public:
    void attack() {
        m_hurt.blood();
    }

private:
    T m_hurt;
};

int main(int argc, char const *argv[])
{
    Archer<ApcHurt>* arc = new Archer<ApcHurt>;
    arc->attack();

    delete arc;
    arc = nullptr;

    return 0;
}