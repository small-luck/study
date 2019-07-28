/*
    观察者模式：定义了对象间一对多的依赖关系，让多个观察者对象同时
    监听某一个主题对象（被观察者）。当主题对象的状态发生变化时，会
    通知观察者对象，让它们能自动更新

    应用背景：当应用程序的某一部分更新时，同时需要更新其它部分的应用程序，
    于是就形成一种依赖关系。可以使用的方法：让被改变者反复检查改变者是否
    发生改变。但是这种方法有很大的问题：
        1. 占用大量的CPU资源去查询
        2. 依赖于检测时间的更新间隔，可能不会立即获取

    博客订阅的例子，当博主发表新文章时，即博主状态发送了变化，那些订阅的读者
    就会通知，然后进行相应的动作，比如去看文章，或者收藏起来。博主与读者之间存在
    一对多的依赖关系

    博客类中有一个观察者链表（即订阅者），当博客的状态发送变化时，通过notify成员
    函数通知所有的观察者告诉他们博客更新了，而观察者通过updaye成员函数获取博客的
    状态信息
*/   
#include <iostream>
#include <list>

//观察者
class Observer {
public:
    Observer() {}
    virtual ~Observer() {}

    virtual void Update() = 0;
};

//博客
class Blog {
public:
    Blog() {}
    virtual ~Blog() {}

    void Attach(Observer *observer) {
        m_observers.push_back(observer);
    }

    void Remove(Observer *observer) {
        m_observers.remove(observer);
    }

    void Notify()   //通知观察者
    {
       for(auto o : m_observers) {
            o->Update();
       }
    }

    virtual void SetStatus(std::string s) {
        m_status = s;           //设置状态
    }

    virtual std::string GetStatus() {
        return m_status;        //获得状态
    }

private:
    std::list<Observer*> m_observers;   //观察者链表
protected:
    std::string m_status;   //状态
};

//具体博客类
class BlogCSDN : public Blog {
private:
    std::string m_name; //博主名称

public:
    BlogCSDN(std::string name) : m_name(name) {}
    virtual ~BlogCSDN() {}

    void SetStatus(std::string s) {
        m_status = "CSDN通知：" + m_name + s;
    }
    std::string GetStatus() {
        return m_status;
    }
};

//具体观察者
class ObserverBlog : public Observer {
private:
    std::string m_name; //观察者名称
    Blog *m_blog;       //观察的博客，当然以链表形式更好，就可以观察多个博客

public:
    ObserverBlog(std::string name, Blog *blog) : m_name(name), m_blog(blog) {}
    virtual ~ObserverBlog() {}

    void Update() { //获得更新状态
        std::string status = m_blog->GetStatus();
        std::cout << m_name << "--------" << status << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    Blog *blog = new BlogCSDN("wuzhekai1985");
    Observer *observer1 = new ObserverBlog("tutupig", blog);
    blog->Attach(observer1);

    Observer *observer2 = new ObserverBlog("liupei", blog);
    blog->Attach(observer2);

    blog->SetStatus("发表设计模式C++实现（15）——观察者模式");
    blog->Notify();

    delete blog;
    delete observer1;
    delete observer2;

    return 0;
}