// 建造者模式
//Product.h 
#ifndef _PRODUCT_H_ 
#define _PRODUCT_H_ 

class Product 
{ 
public: 
Product(); 
~Product(); 
void ProducePart(); 
protected:  // 可以被继承访问
private: 
}; 

class ProductPart 
{ 
public: 
ProductPart(); 
~ProductPart(); 
ProductPart* BuildPart(); 
protected: 
private: 
}; 
#endif //~_PRODUCT_H_


//Component.cpp
#include "Component.h" 
// 一系列函数的定义
Component::Component() 
{ 
} 

Component::~Component() 
{ 
} 

void Component::Add(const Component&
com)
{ 
} 

Component* Component::GetChild(int index) 
{ 
 return 0;
} 

void Component::Remove(const Component& 
com)
{ 
}


//Builder.h 
#ifndef _BUILDER_H_ 
#define _BUILDER_H_ 
#include <string>
using namespace std; 
class Product; 
// Builder基类
class Builder 
{ 
public: 
virtual ~Builder(); 
// 都声明为纯虚函数
virtual void BuildPartA(const string& 
buildPara) = 0; 
virtual void BuildPartB(const string& 
buildPara) = 0; 
virtual void BuildPartC(const string& 
buildPara) = 0; 
virtual Product* GetProduct() = 0;
// 保护：可以被继承访问，不能被外部访问；
protected: 
Builder(); 
private: 
}; 

// ConcreteBuilder : Builder子类
class ConcreteBuilder:public Builder 
{ 
public: 
ConcreteBuilder(); 
~ConcreteBuilder(); 
void BuildPartA(const string& 
buildPara);
void BuildPartB(const string& buildPara);
void BuildPartC(const string& buildPara);
Product* GetProduct(); 
protected: 
private: 
}; 
#endif //~_BUILDER_H_


//Builder.cpp 
#include "Builder.h" 
#include "Product.h" 
#include <iostream> 
using namespace std; 
// 实际实现
Builder::Builder() 
{ 
} 
Builder::~Builder() 
{ 
} 
ConcreteBuilder::ConcreteBuilder() 
{ 
} 
ConcreteBuilder::~ConcreteBuilder() 
{ 
} 
void ConcreteBuilder::BuildPartA(const string& buildPara) 
{ 
 cout<<"Step1:Build PartA..."<<buildPara<<endl; 
} 
void ConcreteBuilder::BuildPartB(const string& buildPara) 
{ 
 cout<<"Step1:Build PartB..."<<buildPara<<endl; 
} 
void ConcreteBuilder::BuildPartC(const string& buildPara) 
{ 
 cout<<"Step1:Build PartC..."<<buildPara<<endl; 
} 

Product* ConcreteBuilder::GetProduct() 
{ 
 BuildPartA("pre-defined"); 
 BuildPartB("pre-defined"); 
 BuildPartC("pre-defined"); 
return new Product(); 
}

//Director.h 
#ifndef _DIRECTOR_H_ 
#define _DIRECTOR_H_ 
class Builder; 
class Director 
{ 
public: 
Director(Builder* bld); 
~Director(); 
void Construct();
protected: 
private: 
Builder* _bld; 
}; 
#endif //~_DIRECTOR_H_


//Director.cpp 
#include "director.h" 
#include "Builder.h" 
Director::Director(Builder* bld)
{ 
_bld = bld; 
} 
Director::~Director() 
{ 
 
} 
void Director::Construct() 
{ 
 _bld->BuildPartA("user-defined"); 
 _bld->BuildPartB("user-defined"); 
 _bld->BuildPartC("user-defined"); 
}
// 强调的是一步步创建对象，并通过相同的创建过程可以获得不同的结果对象
//main.cpp 
#include "Builder.h" 
#include "Product.h" 
#include "Director.h" 
#include <iostream> 
using namespace std; 
int main(int argc,char* argv[])
{ 
Director* d = new Director(new ConcreteBuilder()); 
d->Construct();
return 0;
}


// 原型模式
//Prototype.h 
#ifndef _PROTOTYPE_H_ 
#define _PROTOTYPE_H_ 
class Prototype 
{ 
public: 
 virtual ~Prototype(); 
virtual Prototype* Clone() const = 0; 
protected: 
 Prototype(); 
private: 
}; 
class ConcretePrototype:public Prototype 
{ 
public: 
 ConcretePrototype(); 
 ConcretePrototype(const 
ConcretePrototype& cp); 
 ~ConcretePrototype(); 
Prototype* Clone() const; 
protected: 
private: 
}; 
#endif //~_PROTOTYPE_H_ 


//Prototype.cpp
#include "Prototype.h" 
#include <iostream> 
using namespace std; 
Prototype::Prototype() 
{ 
} 
Prototype::~Prototype() 
{ 
} 
Prototype* Prototype::Clone() const 
{ 
 return 0;
} 
ConcretePrototype::ConcretePrototype() 
{ 
} 
ConcretePrototype::~ConcretePrototype() 
{ 
} 
ConcretePrototype::ConcretePrototype(const ConcretePrototype& cp) 
{ 
 cout<<"ConcretePrototype copy ..."<<endl;
} 
Prototype* ConcretePrototype::Clone() const 
{ 
return new ConcretePrototype(*this); 
}


//main.cpp 
#include "Prototype.h" 
#include <iostream> 
using namespace std; 
int main(int argc,char* argv[])
{ 
Prototype* p = new ConcretePrototype(); 
Prototype* p1 = p->Clone(); 
 return 0;
}


// 桥接模式
//Abstraction.h
#ifndef _ABSTRACTION_H_
#define _ABSTRACTION_H_
class AbstractionImp; 

class Abstraction 
{ 
public: 
virtual ~Abstraction(); 
virtual void Operation() = 0; 
protected: 
Abstraction();
private: 
}; 

class RefinedAbstraction:public Abstraction 
{ 
public: 
RefinedAbstraction(AbstractionImp* imp); 
~RefinedAbstraction(); 
void Operation();
protected: 
private: 
AbstractionImp* _imp; //
}; 
#endif //~_ABSTRACTION_H_

//Abstraction.cpp 
#include "Abstraction.h" 
#include "AbstractionImp.h" 
#include <iostream> 
using namespace std; 
Abstraction::Abstraction() 
{ 
} 
Abstraction::~Abstraction() 
{ 
} 
RefinedAbstraction::RefinedAbstraction(AbstractionImp* imp)
{ 
_imp = imp; 
} 
RefinedAbstraction::~RefinedAbstraction() 
{ 
} 
void RefinedAbstraction::Operation() 
{ 
 _imp->Operation(); 
} 

//AbstractionImp.h 
#ifndef _ABSTRACTIONIMP_H_ 
#define _ABSTRACTIONIMP_H_ 
class AbstractionImp 
{ 
public: 
virtual ~AbstractionImp(); 
virtual void Operation() = 0; 
protected: 
AbstractionImp(); 
private: 
}; 

class ConcreteAbstractionImpA:public AbstractionImp
{ 
public: 
ConcreteAbstractionImpA(); 
~ConcreteAbstractionImpA(); 
virtual void Operation();
protected: 
private: 
}; 

class ConcreteAbstractionImpB:public AbstractionImp
{ 
public: 
ConcreteAbstractionImpB(); 
~ConcreteAbstractionImpB(); 
virtual void Operation();
protected: 
private: 
}; 
#endif //~_ABSTRACTIONIMP_H_ 

//AbstractionImp.cpp 
#include "AbstractionImp.h" 
#include <iostream> 
using namespace std; 
AbstractionImp::AbstractionImp() 
{ 
} 
AbstractionImp::~AbstractionImp() 
{ 
} 
void AbstractionImp::Operation() 
{ 
 cout<<"AbstractionImp....imp..."<<endl; 
} 
ConcreteAbstractionImpA::ConcreteAbstractionImpA() 
{ 
} 
ConcreteAbstractionImpA::~ConcreteAbstractionImpA() 
{ 
} 
void ConcreteAbstractionImpA::Operation() 
{ 
 cout<<"ConcreteAbstractionImpA...."<<endl; 
} 
ConcreteAbstractionImpB::ConcreteAbstractionImpB() 
{ 
} 
ConcreteAbstractionImpB::~ConcreteAbstractionImpB() 
{ 
} 
void ConcreteAbstractionImpB::Operation() 
{ 
 cout<<"ConcreteAbstractionImpB...."<<endl; 
}

//main.cpp 
#include "Abstraction.h" 
#include "AbstractionImp.h" 
#include <iostream> 
using namespace std; 
int main(int argc,char* argv[])
{ 
AbstractionImp* imp = new ConcreteAbstractionImpA(); 
Abstraction* abs = new RefinedAbstraction(imp); 
abs->Operation(); 
 
 return 0;
}

#include <bits/stdc++.h>

//
//桥接模式
//关键代码：将实现独立出来，抽象类依赖现实类。
//以下示例中，将各类App、各类手机独立开来，实现各种App和各种手机的自由桥接/组合
//


//抽象App类，提供接口
class App {
public:
    virtual ~App() = default;

    virtual void run() = 0;
};

//具体的App实现类
class GameApp : public App {
public:
    void run() override {
        std::cout << "GameApp Running" << std::endl;
    }
};

//具体的App实现类
class TranslateApp : public App {
public:
    void run() override {
        std::cout << "TranslateApp Running" << std::endl;
    }
};

//抽象手机类，提供接口
class MobilePhone {
public:
    virtual ~MobilePhone() = default;

    //构造函数不能定义为虚函数.有兴趣的可以思考一下why.
    MobilePhone(const std::shared_ptr<App> pApp) : m_pApp(pApp) {}

    virtual void appRun() = 0;

protected:
    //由于继承类要使用该对象,因此不能定义为private类型
    std::shared_ptr<App> m_pApp;//持有一个实现的引用.类通过该对象实现app与手机的桥接
};

//具体的手机实现类
class XiaoMi : public MobilePhone {
public:
    XiaoMi(const std::shared_ptr<App> pApp) : MobilePhone(pApp) {}

    void appRun() override {
        std::cout << "XiaoMi: ";
        m_pApp->run();
    }
};

//具体的手机实现类
class HuaWei : public MobilePhone {
public:
    HuaWei(const std::shared_ptr<App> pApp) : MobilePhone(pApp) {}

    void appRun() override {
        std::cout << "HuaWei: ";
        m_pApp->run();
    }
};

int main() {
    std::shared_ptr<App> pGameApp = std::make_shared<GameApp>();//实现部分
    std::shared_ptr<MobilePhone> pXiaoMi = std::make_shared<XiaoMi>(pGameApp);//抽象部分
    pXiaoMi->appRun();

    std::shared_ptr<App> pTranslateApp = std::make_shared<TranslateApp>();//实现部分
    pXiaoMi = std::make_shared<XiaoMi>(pTranslateApp);//抽象部分
    pXiaoMi->appRun();

    std::cout << std::string(50, '-') << std::endl;

    std::shared_ptr<MobilePhone> pHuaWei = std::make_shared<HuaWei>(pGameApp);
    pHuaWei->appRun();

    pHuaWei = std::make_shared<HuaWei>(pTranslateApp);
    pHuaWei->appRun();

    return 0;
    //运行结果:
    //XiaoMi: GameApp Running
    //XiaoMi: TranslateApp Running
    //--------------------------------------------------
    //HuaWei: GameApp Running
    //HuaWei: TranslateApp Running
}




// 适配器模式
//Adapter.h 
#ifndef _ADAPTER_H_ 
#define _ADAPTER_H_ 
class Target 
{ 
public: 
Target(); 
virtual ~Target();
virtual void Request(); 
}; 

class Adaptee
{ 
public: 
Adaptee();
~Adaptee();
void SpecificRequest(); 
}; 

class Adapter:public Target 
{ 
public: 
Adapter(Adaptee* ade); 
~Adapter(); 
void Request(); 
private: 
Adaptee* _ade;
}; 
#endif //~_ADAPTER_H_ 


//Adapter.cpp 
#include "Adapter.h" 
#include <iostream> 
Target::Target()
{ 
} 
Target::~Target()
{ 
} 
void Target::Request() 
{ 
 std::cout<<"Target::Request"<<std::endl; 
} 
Adaptee::Adaptee() 
{ 
} 
Adaptee::~Adaptee() 
{ 
} 
void Adaptee::SpecificRequest()
{ 
 std::cout<<"Adaptee::SpecificRequest"<<std::endl; 
} 
Adapter::Adapter(Adaptee* ade)
{ 
 this->_ade = ade;
} 
Adapter::~Adapter() 
{ 
} 
void Adapter::Request() 
{ 
 _ade->SpecificRequest(); 
}

//main.cpp 
#include "Adapter.h" 
#include <iostream> 
using namespace std; 
int main(int argc,char* argv[])
{ 
Adaptee* ade = new Adaptee;
Target* adt = new Adapter(ade);
adt->Request();
return 0;
} 


// 装饰器模式

#include <bits/stdc++.h>

//
//装饰模式
//关键代码：
// 1.Component 类充当抽象角色，不应该具体实现
// 2.修饰类引用和继承 Component 类，具体扩展类重写父类方法。
//

using namespace std;

//抽象构件（Component）角色：给出一个抽象接口，以规范准备接收附加责任的对象。
class Component {
public:
    virtual ~Component() = default;

    virtual void configuration() = 0;
};

//具体构件（Concrete Component）角色：定义一个将要接收附加责任的类。
class Car : public Component {
public:
    void configuration() override {
        std::cout << "A Car" << std::endl;
    }
};

//装饰（Decorator）角色：持有一个构件（Component）对象的实例，
// 并实现一个与抽象构件接口一致的接口。
class DecorateCar : public Component {
public:
    DecorateCar(std::shared_ptr<Component> car) : m_pCar(car) {}

    void configuration() override {
        m_pCar->configuration();
    }

private:
    std::shared_ptr<Component> m_pCar;
};

//具体装饰（Concrete Decorator）角色：负责给构件对象添加上附加的责任。
class DecorateLED : public DecorateCar {
public:
    DecorateLED(std::shared_ptr<Component> car) : DecorateCar(car) {}

    void configuration() override {
        DecorateCar::configuration();
        //or add other somthing
        addLED();
    }

private:
    void addLED() {
        std::cout << "Install LED" << std::endl;
    }
};

//具体装饰（Concrete Decorator）角色：负责给构件对象添加上附加的责任。
class DecoratePC : public DecorateCar {
public:
    DecoratePC(std::shared_ptr<Component> car) : DecorateCar(car) {}

    void configuration() override {
        DecorateCar::configuration();
        addPC();
    }

private:
    void addPC() {
        std::cout << "Install PC" << std::endl;
    }
};

//具体装饰（Concrete Decorator）角色：负责给构件对象添加上附加的责任。
class DecorateEPB : public DecorateCar {
public:
    DecorateEPB(std::shared_ptr<Component> car) : DecorateCar(car) {}

    void configuration() override {
        DecorateCar::configuration();
        addEPB();
    }

private:
    void addEPB() {
        std::cout << "Install Electrical Park Brake" << std::endl;
    }
};

int main() {
    std::shared_ptr<Car> car = std::make_shared<Car>();
    std::shared_ptr<DecorateLED> ledCar = std::make_shared<DecorateLED>(car);//装饰一层
    ledCar->configuration();

    std::cout << std::string(30, '-') << std::endl;

    std::shared_ptr<DecoratePC> pcCar = std::make_shared<DecoratePC>(ledCar);//装饰二层
    std::shared_ptr<DecorateEPB> epbCar = std::make_shared<DecorateEPB>(pcCar);//装饰三层
    epbCar->configuration();

    return 0;
    //运行结果如下:
    //A Car
    //Install LED
    //------------------------------
    //A Car
    //Install LED
    //Install PC
    //Install Electrical Park Brake
}

//Composite.h
#ifndef COMPOSITE_H 
#define COMPOSITE_H 
#include <list> 
// 组合中的抽象基类
class Component 
{ 
public: 
 Component(){} 
 virtual ~Component(){} 
 // 纯虚函数,只提供接口,没有默认的实现
 virtual void Operation() = 0; 
 // 虚函数,提供接口,有默认的实现就是什么都不做
 virtual void Add(Component* pChild); 
 virtual void Remove(Component* pChild); 
 virtual Component* GetChild(int nIndex); 
}; 
// 派生自 Component,是其中的叶子组件的基类
class Leaf 
 : public Component 
{ 
public: 
 Leaf(){} 
 virtual ~Leaf(){} 
 virtual void Operation(); 
}; 
// 派生自 Component,是其中的含有子件的组件的基类
class Composite 
 : public Component 
{ 
public: 
 Composite(){} 
 virtual ~Composite(); 
 virtual void Operation(); 
 virtual void Add(Component* pChild); 
 virtual void Remove(Component* pChild); 
 virtual Component* GetChild(int nIndex); 
private: 
 // 采用 list 容器去保存子组件
 std::list<Component*> m_ListOfComponent; 
}; 
#endif

//Composite.cpp 
#include "Composite.h" 
#include <iostream> 
#include <algorithm> 
/*------------------------------------------------------------------- 
 Component 成员函数的实现
-------------------------------------------------------------------*/
void Component::Add(Component* pChild) 
{ 
} 
void Component::Remove(Component* pChild) 
{ 
} 
Component* Component::GetChild(int nIndex) 
{ 
 return NULL; 
} 
/*------------------------------------------------------------------- 
 Leaf 成员函数的实现
-------------------------------------------------------------------*/
void Leaf::Operation() 
{ 
 std::cout << "Operation by leaf\n"; 
} 
/*------------------------------------------------------------------- 
 Composite 成员函数的实现
-------------------------------------------------------------------*/
Composite::~Composite() 
{ 
 std::list<Component*>::iterator iter1, iter2, temp; 
PDF created with pdfFactory trial version www.pdffactory.com
 for (iter1 = m_ListOfComponent.begin(), iter2 = m_ListOfComponent.end(); 
 iter1 != iter2; 
 ) 
 { 
 temp = iter1; 
 ++iter1; 
 delete (*temp); 
 } 
} 
void Composite::Add(Component* pChild) 
{ 
 m_ListOfComponent.push_back(pChild); 
} 
void Composite::Remove(Component* pChild) 
{ 
 std::list<Component*>::iterator iter; 
 iter = find(m_ListOfComponent.begin(), m_ListOfComponent.end(), pChild); 
 if (m_ListOfComponent.end() != iter) 
 { 
 m_ListOfComponent.erase(iter); 
 } 
} 
Component* Composite::GetChild(int nIndex) 
{ 
 if (nIndex <= 0 || nIndex > m_ListOfComponent.size()) 
 return NULL; 
 std::list<Component*>::iterator iter1, iter2; 
 int i; 
 for (i = 1, iter1 = m_ListOfComponent.begin(), iter2 = m_ListOfComponent.
end(); 
 iter1 != iter2; 
 ++iter1, ++i) 
 { 
 if (i == nIndex) 
 break; 
 } 
 return *iter1; 
} 

void Composite::Operation() 
{ 
 std::cout << "Operation by Composite\n"; 
 std::list<Component*>::iterator iter1, iter2; 
 for (iter1 = m_ListOfComponent.begin(), iter2 = m_ListOfComponent.end(); 
 iter1 != iter2; 
 ++iter1) 
 { 
 (*iter1)->Operation(); 
 } 
}

#include "Composite.h" 
#include <stdlib.h> 
int main() 
{ 
 Leaf *pLeaf1 = new Leaf(); 
 Leaf *pLeaf2 = new Leaf(); 
 Composite* pComposite = new Composite; 
 pComposite->Add(pLeaf1); 
 pComposite->Add(pLeaf2); 
 pComposite->Operation(); 
 pComposite->GetChild(2)->Operation(); 
 delete pComposite; 
}


#include <bits/stdc++.h>

//抽象享元基类
class Flyweight {
public:
    virtual void display(const int iX, const int iY) = 0;

    Flyweight() = default;

    virtual ~Flyweight() = default;

protected:
    std::string m_strColor;
};


//共享类
class SharedConcreteFlyweightWhite : public Flyweight {
public:
    void display(const int iX, const int iY) override {
        std::cout << "I am a " << m_strColor
                  << " Chess,my coordinate is (" << iX << "," << iY << ")."
                  << std::endl;
    }

    SharedConcreteFlyweightWhite() {
        m_strColor = "White";
    }

    ~SharedConcreteFlyweightWhite() = default;
};


class SharedConcreteFlyweightBlack : public Flyweight {
public:
    void display(const int iX, const int iY) override {
        std::cout << "I am a black Chess,my coordinate is ("
                  << iX << "," << iY << ")" << std::endl;
    }

    SharedConcreteFlyweightBlack() : Flyweight() {
        m_strColor = "Black";
    }

    ~SharedConcreteFlyweightBlack() = default;
};


//非享元角色
class UnsharedConcreteFlyweightChessbox : public Flyweight {
public:
    void display(const int iX, const int iY) override {
        std::cout << "I am a " << m_strColor
                  << " chessbox,my coordinate is ("
                  << iX << "," << iY << ")" << std::endl;
    }

    UnsharedConcreteFlyweightChessbox() : Flyweight() {
        m_strColor = "Yellow";
    }

    ~UnsharedConcreteFlyweightChessbox() = default;
};


//享元工厂
const std::string BLACKCHESS = "Black";
const std::string WHITECHESS = "White";

class FlyweightFactory {
private:
    std::map<std::string, std::shared_ptr<Flyweight>> m_mapFlyweight;
public:
    // strKey is defined class name or surname of class
    std::shared_ptr<Flyweight> getFlyweight(const std::string strKey) {
        //if find return FlyWeight object whose key is equal,otherwise new object and insert into map
        if (m_mapFlyweight.end() != m_mapFlyweight.find(strKey))
            return m_mapFlyweight[strKey];
        if (strKey == BLACKCHESS) {
            auto pointer = std::make_shared<SharedConcreteFlyweightBlack>();
            m_mapFlyweight[strKey] = pointer;
            return pointer;
        } else if (strKey == WHITECHESS) {
            auto pointer = std::make_shared<SharedConcreteFlyweightWhite>();
            m_mapFlyweight[strKey] = pointer;
            return pointer;
        } else {
            std::cout << "The key is Error!" << std::endl;
            return nullptr;
        }
    }

    size_t getFlyweightCount() {
        return m_mapFlyweight.size();
    }
};


int main() {
    FlyweightFactory objFactory;
    auto objBlack = objFactory.getFlyweight(BLACKCHESS);
    objBlack->display(3, 5);

    auto objBlack1 = objFactory.getFlyweight(BLACKCHESS);
    objBlack1->display(1, 4);

    std::cout << "Now,total chess count " << objFactory.getFlyweightCount() << std::endl;

    auto objWhite = objFactory.getFlyweight(WHITECHESS);
    objWhite->display(9, 9);

    std::cout << "Now,total chess count " << objFactory.getFlyweightCount() << std::endl;

    auto objWhite1 = objFactory.getFlyweight(WHITECHESS);
    objWhite1->display(8, 8);

    std::cout << "Now,total chess count " << objFactory.getFlyweightCount() << std::endl;

    UnsharedConcreteFlyweightChessbox unshChessbox;
    unshChessbox.display(1, 2);

    std::cout << "Now,total chess count " << objFactory.getFlyweightCount() << std::endl;

    return 0;
    //运行结果如下：
    //I am a black Chess,my coordinate is (3,5)
    //I am a black Chess,my coordinate is (1,4)
    //Now,total chess count 1
    //I am a White Chess,my coordinate is (9,9).
    //Now,total chess count 2
    //I am a White Chess,my coordinate is (8,8).
    //Now,total chess count 2
    //I am a Yellow chessbox,my coordinate is (1,2)
    //Now,total chess count 2
}


//Flyweight.h
#ifndef FLYWEIGHT_H 
#define FLYWEIGHT_H 
#include <string> 
#include <list> 
typedef std::string STATE; 
// 享元基类
class Flyweight 
{ 
public: 
virtual ~Flyweight(){} 
STATE GetIntrinsicState(); 
virtual void Operation(STATE& ExtrinsicState) = 0; 
protected: 
Flyweight(const STATE& state) 
:m_State(state) 
{ 
} 
private: 
 STATE m_State;  // 享元基类维护的一个变量
}; 
//享元工厂
class FlyweightFactory 
{ 
public: 
 FlyweightFactory(){} 
 ~FlyweightFactory(); 
 Flyweight* GetFlyweight(const STATE& key); 
private: 
 std::list<Flyweight*> m_listFlyweight; 享元工厂维护的对象池
// 
class ConcreateFlyweight 
 : public Flyweight 
{ 
public: 
 ConcreateFlyweight(const STATE& state) 
 : Flyweight(state) 
 { 
 } 
 virtual ~ConcreateFlyweight(){} 
 virtual void Operation(STATE& ExtrinsicState); 
}; 
#endif

//Flyweight.cpp
#include "FlyWeight.h" 
#include <iostream> 
inline STATE Flyweight::GetIntrinsicState() 
{ 
 return m_State; 
} 
FlyweightFactory::~FlyweightFactory() 
{ 
 std::list<Flyweight*>::iterator iter1, iter2, temp; 
 for (iter1 = m_listFlyweight.begin(), iter2 = m_listFlyweight.end(); 
 iter1 != iter2; 
 ) 
 { 
 temp = iter1; 
 ++iter1; 
 delete (*temp); 
 } 
 m_listFlyweight.clear(); 
} 

Flyweight* FlyweightFactory::GetFlyweight(const STATE& key) 
{ 
 std::list<Flyweight*>::iterator iter1, iter2; 
 for (iter1 = m_listFlyweight.begin(), iter2 = m_listFlyweight.end(); 
 iter1 != iter2; 
 ++iter1) 
 { 
 if ((*iter1)->GetIntrinsicState() == key) 
 { 
 std::cout << "The Flyweight:" << key << " already exits"<< std::endl; 
 return (*iter1); 
 } 
 } 
 std::cout << "Creating a new Flyweight:" << key << std::endl; 
 Flyweight* flyweight = new ConcreateFlyweight(key); 
 m_listFlyweight.push_back(flyweight); 
} 

void ConcreateFlyweight::Operation(STATE& ExtrinsicState) 
{ 
}

#include "FlyWeight.h" 
int main() 
{ 
 FlyweightFactory flyweightfactory; 
 flyweightfactory.GetFlyweight("hello"); 
 flyweightfactory.GetFlyweight("world"); 
 flyweightfactory.GetFlyweight("hello"); 
 system("pause"); 
 return 0; 
}



// 代理模式
//代理模式:提供一种代理来控制其他对象的访问
#include <iostream>
using namespace std;

class AbstractCommonInterface {
public:
    virtual void run() = 0;
};
//下面是操作系统类
class MySystem :public AbstractCommonInterface{
public:
    virtual void run() {
        cout << "系统启动" << endl;
    }
};

//代理： 启动系统必须要权限验证,不是所以的人都可以来启动我的系统,必须要提供用户名和密码
class MySystemProxy :public AbstractCommonInterface {
public:
    MySystemProxy(string userName, string password) {
        this->mUserName = userName;
        this->mPassword = password;
        pMySystem = new MySystem;
    }

    bool checkUserNameAndPassword() {
        if (mUserName == "admin" && mPassword == "admin") {
            return true;
        }
        return false;
    }
    virtual void run() {
        if (checkUserNameAndPassword() == true) {
            cout << "启动成功" << endl;
            this->pMySystem->run();
        }
        else {
            cout << "用户名或者密码错误,权限不足" << endl;
        }
    }
    ~MySystemProxy() {
        if (pMySystem != NULL) {
            delete pMySystem;
        }
    }
private:
    string mUserName;
    string mPassword;
    MySystem* pMySystem;
};
void test01() {
    MySystemProxy* proxy = new MySystemProxy("admin", "admin");
    proxy->run();
}

int main()
{
    test01();
}


//Originator.h
#ifndef _ORIGINATOR_H_
#define _ORIGINATOR_H_
#include <string>

#include "Memento.h"
    class Originator
    {
    public:
        std::string getState() const
        {
            return state;
        }

        void setState(const std::string& state)
        {
            this->state = state;
        }

        //保存一个状态对象Memento   即用当前状态的值去创建一个Memento然后将其返回
        Memento SaveStateMemento()
        {
            return Memento(state);
        }

        //通过备忘录对象，恢复状态
        void getStateFromMemento(Memento memento)
        {
            state = memento.getState();
        }
    private:
        std::string state;
    };
#endif

//Memento.h
#ifndef _MEMENTO_H_
#define _MEMENTO_H_
#include <string>
    class Memento
    {
    public:
        explicit Memento(const std::string& state)
                : state(state)
        {
        }

        std::string getState() const
        {
            return state;
        }

    private:
        std::string state;
    };

#endif

//Caretaker.h
#ifndef _CARETAKER_H_
#define _CARETAKER_H_

#include <vector>
#include "Memento.h"
    class Caretaker
    {
    public:
        void add(Memento memento)
        {
            mementoList.push_back(memento);
        }

        //获取到第index个Originator的备忘录对象（即备忘录状态）
        Memento get(int index)
        {
            return mementoList[index];
        }
    private:
        //在mementoList中会有很多备忘录对象
        std::vector<Memento> mementoList;
    };
#endif

//main.h
#include <iostream>
#include "Originator.h"
#include "Caretaker.h"
    using namespace std;
    int main(int argc, char* argv[])
    {
        Originator originator;
        Caretaker caretaker;
        originator.setState("状态1，攻击力为100");

        //保存当前状态
        caretaker.add(originator.SaveStateMemento());

        //受到debuff，攻击力下降
        originator.setState("状态2，攻击力为80");
        //保存状态
        caretaker.add(originator.SaveStateMemento());

        cout << "当前的状态：" << originator.getState()<<endl;
        cout << "debuff时间结束，回到状态1" << endl;
        originator.getStateFromMemento(caretaker.get(0));
        cout << "恢复到状态1后的状态：" << originator.getState();
        return 0;
    }

#include <bits/stdc++.h>

//
//备忘录模式
//关键代码：Memento类、Originator类、Caretaker类；
// Originator类不与Memento类耦合，而是与Caretaker类耦合
//


//需要保存的信息
//此处将需要保存的信息提取出来放在一个结构体中
//也可以不用放在结构体中，直接作为类的成员变量
    typedef struct {
        int nHp;//血量
        int nMp;//蓝量
        int nAttack;//攻击
    }GameValue;


//备忘录类
    class Memento{
    public:
        Memento(const GameValue& gameValue):m_gameValue(gameValue){}

        //函数前后均加const
        //前const:返回的变量不可修改
        //后const:该函数readonly,表示该类的this指针为const类型，
        // 不能改变类的成员变量的值
        const GameValue& getValue() const{
            return m_gameValue;
        }


        //Memento() = delete;
        //Memento(const Memento &) = delete;
        //Memento &operator=(const Memento &) = delete;

    private:
        GameValue m_gameValue;
    };

//管理者角色
    class Caretaker
    {
    public:
        const std::shared_ptr<Memento> GetState(const std::string& key) {
            return mData[key];
        }
        void SetState(const std::string& key,
                      std::shared_ptr<Memento> pMemento) {
            mData[key] = pMemento;
        }

    private:
        //此处考虑在map中存储指针,而非直接存储对象
        std::map<std::string,std::shared_ptr<Memento>> mData;
    };

//发起人角色
    class Hero{
    public:
        Hero()
                :m_gameValue{100,100,100}{
        }

        Hero(const GameValue& gameValue)
                :m_gameValue(gameValue){
        }

        //保存当前信息
        void saveState(const std::string& key) {
            m_Caretaker.SetState(key, std::make_shared<Memento>(m_gameValue));
        }

        //恢复信息
        const void resumeState(const std::string& key) {
            m_gameValue = m_Caretaker.GetState(key)->getValue();
        }

        void battle()
        {
            m_gameValue.nHp = rand()%100;
            m_gameValue.nMp = rand()%100;
            m_gameValue.nAttack = rand()%100;
        }

        void showState() {
            std::cout<<"血量："<<m_gameValue.nHp<<std::endl
                     <<"蓝量："<<m_gameValue.nMp<<std::endl
                     <<"攻击："<<m_gameValue.nAttack<<std::endl;
        }

    private:
        GameValue m_gameValue;
        Caretaker m_Caretaker;//常规对象,没有必要用指针
    };

    int main()
    {
        Hero hero;

        std::cout<<"----战斗前-----"<<std::endl;
        hero.showState();
        std::cout<<std::endl;
        hero.saveState("战斗前");

        hero.battle();
        std::cout<<"-----战斗1后-----"<<std::endl;
        hero.showState();
        std::cout<<std::endl;
        hero.saveState("战斗1后");

        hero.battle();
        std::cout<<"-----战斗2后-----"<<std::endl;
        hero.showState();
        hero.saveState("战斗2后");
        std::cout<<std::endl;

        hero.battle();
        std::cout<<"-----战斗3后-----"<<std::endl;
        hero.showState();
        hero.saveState("战斗3后");
        std::cout<<std::endl;

        hero.resumeState("战斗1后");
        std::cout<<"-----恢复战斗1结果-----"<<std::endl;
        hero.showState();
        std::cout<<std::endl;

        hero.resumeState("战斗前");
        std::cout<<"-----恢复战斗前-----"<<std::endl;
        hero.showState();
        std::cout<<std::endl;

        return 0;
        //运行结果如下:
        //----战斗前-----
        //血量：100
        //蓝量：100
        //攻击：100
        //
        //-----战斗1后-----
        //血量：83
        //蓝量：86
        //攻击：77
        //
        //-----战斗2后-----
        //血量：15
        //蓝量：93
        //攻击：35
        //
        //-----战斗3后-----
        //血量：86
        //蓝量：92
        //攻击：49
        //
        //-----恢复战斗1结果-----
        //血量：83
        //蓝量：86
        //攻击：77
        //
        //-----恢复战斗前-----
        //血量：100
        //蓝量：100
        //攻击：100
    }


//命令模式
#include <iostream>
#include <queue>
#include <Windows.h>
    using namespace std;

//协议处理类    （请求类）
    class HandleClinetProtocal
    {
    public:
        //处理增加金币
        void AddMoney()
        {
            cout << "给玩家增加金币" << endl;
        }
        //处理增加钻石
        void AddDiamond()
        {
            cout << "给玩家增加钻石" << endl;
        }
        //处理玩家装备
        void AddEquipment()
        {
            cout << "给玩家穿装备" << endl;
        }
        //玩家升级
        void AddLevel()
        {
            cout << "给玩家升级" << endl;
        }
    };

//命令接口
    class AbstractCommand
    {
    public:
        //相当于execute（）
        virtual void handle() = 0;
    };


//下面是把每个功能都封装为一个请求对象
//处理增加金币请求
    class AddMoneyCommand:public AbstractCommand
    {
    public:
        AddMoneyCommand(HandleClinetProtocal* protocal)
        {
            this->pProtocol = protocal;
        }
        virtual void handle()
        {
            this->pProtocol->AddMoney();
        }
    public:
        HandleClinetProtocal* pProtocol;
    };

//处理增加钻石请求
    class AddDiamondCommand :public AbstractCommand
    {
    public:
        AddDiamondCommand(HandleClinetProtocal* protocal)
        {
            this->pProtocol = protocal;
        }
        virtual void handle()
        {
            this->pProtocol->AddDiamond();
        }
    public:
        HandleClinetProtocal* pProtocol;
    };

//处理玩家装备请求
    class AddEquipmentCommand :public AbstractCommand
    {
    public:
        AddEquipmentCommand(HandleClinetProtocal* protocal)
        {
            this->pProtocol = protocal;
        }
        virtual void handle()
        {
            this->pProtocol->AddEquipment();
        }
    public:
        HandleClinetProtocal* pProtocol;
    };

//处理玩家升级请求
    class AddLevelCommand :public AbstractCommand
    {
    public:
        AddLevelCommand(HandleClinetProtocal* protocal)
        {
            this->pProtocol = protocal;
        }
        virtual void handle()
        {
            this->pProtocol->AddLevel();
        }
    public:
        HandleClinetProtocal* pProtocol;
    };

//服务器程序   （命令调用类）
    class Server
    {
    public:
        //将请求对象放入处理队列
        void addRequest(AbstractCommand* command)
        {
            mCommands.push(command);
        }

        //启动处理程序
        void startHandle()
        {
            while (!mCommands.empty())
            {
                Sleep(2000);
                AbstractCommand* command = mCommands.front();
                command->handle();
                mCommands.pop();
            }
        }
        queue<AbstractCommand*> mCommands;
    };

    void test01()
    {
        HandleClinetProtocal* protocal = new HandleClinetProtocal;
        //客户端增加金币的请求
        AbstractCommand* addmoney = new AddMoneyCommand(protocal);
        //客户端增加钻石的请求
        AbstractCommand* adddiamond = new AddDiamondCommand(protocal);
        //客户端穿装备的请求
        AbstractCommand* addequipment = new AddEquipmentCommand(protocal);
        //客户端升级请求
        AbstractCommand* addlevel = new AddLevelCommand(protocal);

        //将客户端的请求加入到请求队列中
        Server* server = new Server;
        server->addRequest(addmoney);
        server->addRequest(adddiamond);
        server->addRequest(addequipment);
        server->addRequest(addlevel);

        //服务器开始处理请求
        server->startHandle();
    }


    int main()
    {
        test01();
        return 0;
    }


#include <iostream>
#include <list>

    class Man;
    class Woman;
    using namespace std;

    class Action
    {
    public:
        virtual void getManResult(Man* man) =0;
        virtual void getWomanResult(Woman* woman) =0;

    private:
    };

    class Success:public Action
    {
    public:
        void getManResult(Man* man) override
        {
            cout << "男人的给的评价该歌手是很成功" << endl;
        }

        void getWomanResult(Woman* woman) override
        {
            cout << "女人的给的评价该歌手是很成功" << endl;
        }
    };

    class Fail :public Action
    {
    public:
        void getManResult(Man* man) override
        {
            cout << "男人的给的评价该歌手是失败" << endl;
        }

        void getWomanResult(Woman* woman) override
        {
            cout << "女人的给的评价该歌手是失败" << endl;
        }
    };

    class Person
    {
    public:
        //提供一个方法让访问者可以访问
        virtual void accept(Action* action) = 0;
    };

//这里用用到了双分派，即首先在客户端程序中，将具体的状态作为参数传递进Man中（第一次分派）
//然后在Man中调用作为参数的“具体方法” getManResult同时将自己作为参数传入完成第二次分派
    class Man:public Person
    {
    public:
        void accept(Action* action) override
        {
            action->getManResult(this);
        }
    };

    class Woman: public Person
    {
    public:
        void accept(Action* action) override
        {
            action->getWomanResult(this);
        }
    };

//数据结构，管理很多人（Man、Woman）用来装符合某一个评价的所有人
    class ObjectStructure
    {
    public:
        //添加到list
        void attach(Person* p)
        {
            persons.push_back(p);
        }
        //移除
        void detach(Person* p)
        {
            persons.remove(p);
            delete p;
        }

        //显示测评情况
        void display(Action* action)
        {
            for (auto value : persons)
            {
                value->accept(action);
            }
        }
    private:
        list<Person*> persons;
    };

    int main(int argc, char* argv[])
    {
        //创建ObjectStructure（可以创建很多个不同的ObjectStructure来代表不同评价，然后把同样评价的人放到一个ObjectStructure中）
        auto* objectStructure = new ObjectStructure;
        objectStructure->attach(new Man);
        objectStructure->attach(new Woman);

        //假如歌手获得成功
        auto* success = new Success;
        objectStructure->display(success);
        cout << "=======================" << endl;
        //假如歌手失败了
        Fail* fail = new Fail;
        objectStructure->display(fail);
        return 0;
    }

    package builder

    import "fmt"

// 建造者接口
    type Builder interface {
        Part1()
        Part2()
        Part3()
    }

// 管理类
    type Director struct {
        builder Builder
    }

// 构造函数
    func NewDirector(builder Builder) *Director {
        return &Director{
                builder: builder,
        }
    }

// 建造
    func (d *Director) Construct() {
        d.builder.Part1()
        d.builder.Part2()
        d.builder.Part3()
    }

    type Builder struct {}

    func (b *Builder) Part1() {
        fmt.Println("part1")
    }

    func (b *Builder) Part2() {
        fmt.Println("part2")
    }

    func (b *Builder) Part3() {
        fmt.Println("part3")
    }