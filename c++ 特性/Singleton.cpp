#include <bits/stdc++.h>

//线程安全/内存安全的懒汉单例模式
//智能指针+双检锁 or 智能指针+call_once

//===============================//
// 采用智能指针，双检锁
// 基于 shared_ptr, 用了C++比较倡导的 RAII思想，用对象管理资源
// 当 shared_ptr 析构的时候，new 出来的对象也会被 delete掉，以此避免内存泄漏。
// 加了锁，使用互斥量来达到线程安全。
// 这里使用了两个if判断语句的技术称为双检锁；好处是，只有判断指针为空的时候才加锁，
// 避免每次调用 get_instance的方法都加锁，锁的开销毕竟还是有点大的

class Singleton{
public:
    typedef std::shared_ptr<Singleton> Ptr;

    //析构函数定义为public
    ~Singleton(){
        std::cout<<"Destructor called!"<<std::endl;
    }
    Singleton(Singleton&) =delete;
    Singleton& operator=(const Singleton&) =delete;

    static Ptr get_instance(){

        // DCL "double checked lock"
        if(m_instance_ptr==nullptr){//第一次检查
            std::lock_guard<std::mutex> lk(m_mutex);
            if(m_instance_ptr == nullptr){//第二次检查
                m_instance_ptr = std::shared_ptr<Singleton>(new Singleton);
                //由于构造函数是private,因此下面这种写法行不通
                //m_instance_ptr = std::make_shared<Singleton>();
            }
        }
        return m_instance_ptr;
    }

    void use() const { std::cout << "in use" << std::endl; }


private:
    Singleton(){
        std::cout<<"Constructor called!"<<std::endl;
    }
    static Ptr m_instance_ptr;
    static std::mutex m_mutex;//由于需要在static函数中调用，因此定义为static
};
//静态成员变量初始化
Singleton::Ptr Singleton::m_instance_ptr = nullptr;
std::mutex Singleton::m_mutex;



//===============================//
//采用智能指针+call_once
//linux平台，CMakelists.txt需要
//target_link_libraries(NEAME,-pthread)才能使用call_once

class Singleton {
private:
    Singleton() {
        std::cout << "Constructor called!" << std::endl;
    }

    static void createInstance() {
        m_instance_ptr = std::shared_ptr<Singleton>(new Singleton);
    }

public:
    typedef std::shared_ptr<Singleton> Ptr;

    ~Singleton() {
        std::cout << "Destructor called!" << std::endl;
    }

    static std::shared_ptr<Singleton> get_instance() {
        static std::once_flag s_flag;
        //std::call_once(s_flag, createInstance);
        std::call_once(s_flag, [] { m_instance_ptr = std::shared_ptr<Singleton>(new Singleton); });
        return m_instance_ptr;
    }

    void use() const { std::cout << "in use" << std::endl; }

private:
    static std::shared_ptr<Singleton> m_instance_ptr;

};

//静态成员变量初始化
Singleton::Ptr Singleton::m_instance_ptr = nullptr;

int main() {
    Singleton::Ptr instance = Singleton::get_instance();
    Singleton::Ptr instance2 = Singleton::get_instance();
    instance->use();
    return 0;

    //两种情况下的运行结果:
    //Constructor called!
    //in use
    //Destructor called!
}

//在某些平台（与编译器和指令集架构有关），双检锁会失效！
//观察上面智能指针+双检锁的代码，表面上这段代码是没有问题的，但实际还是存在问题，来源于CPU的乱序执行，c++中new分为两步：
//
//1.分配内存
//2.调用构造函数
//
//所以 pInst = new T();这句代码分为三步：
//
//1.分配内存
//2.在内存的位置上调用构造函数
//3.将内存的地址复制给pInst
//
//在这三步中，2和3的顺序是可以颠倒的。也就是说，完全有可能出现pInst的值已经不是nullptr，但对象仍然没有构造完毕，这时候如果出现另外一个对GetInstance的并发调用，此时第一个if内的pInst已经不为nullptr。所以这个调用会直接返回尚未构造完全的对象的地址以提供给用户使用。那么这个程序就存在崩溃的可能性。
//
//上面代码中的第2中方法:智能指针+call_once的模式理论上可以避免上面的问题，查找资料，还没有查找到相关的介绍，因此可以理解为能够避免双检锁失效的问题。
/
