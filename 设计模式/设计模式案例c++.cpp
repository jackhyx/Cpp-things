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
