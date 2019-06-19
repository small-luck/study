/*
  对象适配器
  案例分析：
  世界各国插座标准都不尽相同，甚至同一国家的不同地区也可能不一样。例如，中国一般使用两脚扁型，而俄罗斯使用的是双脚圆形。
  那么，如果去俄罗斯旅游，就会出现一个问题：我们带去的充电器为两脚扁型，而他们提供的插座为双脚圆形，如何给手机充电呢？
  总不能为了旅客而随意更改墙上的插座吧，而且俄罗斯人一直都这么使用，并且用的很好。俗话说入乡随俗，那么只能自己想办法解决了。
  其实这个问题的解决方式很简单 - 适配器模式，只需要提供一个电源转化器即可。该转化器的一端符合俄罗斯标准，可以插到俄罗斯的
  插座上，另一端符合中国标准，可以供我们的手机充电器使用。
*/
#include <iostream>

//创建目标接口
class RussiaSocket {
    public:
        //使用双脚圆形充电（暂不实现）
        virtual void Charge() = 0;
};

//创建适配者
//自带的充电器-两脚扁型
class OwnCharger {
    public:
        void ChargeWithFeetFlat() {
            std::cout << "OwnCharger::ChargeWithFeetFlat" << std::endl;
        }
};


//创建适配器
class PowerAdapter : public RussiaSocket {
    public:
        PowerAdapter() : m_pCharger(new OwnCharger()) {}
        virtual ~PowerAdapter() {}

        void Charge() {
            //使用自带的充电器充电
            m_pCharger->ChargeWithFeetFlat();
        }
        
    private:
        OwnCharger *m_pCharger; //持有需要被适配的接口对象-自带的充电器
};


int main(int argc, char const * argv [ ])
{
    //创建适配器
    RussiaSocket *pAdapter = new PowerAdapter();

    //充电
    pAdapter->Charge();

    delete pAdapter;
    pAdapter = NULL;

    return 0;
}
