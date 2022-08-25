#### 使用名称空间

#### 别名指定

```c++
typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;

using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;
```
* 可读性
```c++
typedef void (*FP) (int, const std::string&);

using FP = void (*) (int, const std::string&);

typedef std::string (Foo::* fooMemFnPtr) (const std::string&);

using fooMemFnPtr = std::string (Foo::*) (const std::string&);
```

* alias templates, 模板别名。
```c++
template <typename T>
using Vec = MyVector<T, MyAlloc<T>>;
// usage
Vec<int> vec;

template<class T>
using ptr = T*;
// 名称 'ptr<T>' 现在是指向 T 指针的别名
```

#### 重新声明派生类成员权限
当一个派生类私有继承基类时，基类的public和protected数据成员在派生类中是private的形式，
如果想让这些继承而来的数据成员作为public或者protected成员，可以用using来重新声明。
using声明语句中名字的访问权限由该using声明语句之前的访问说明符决定。
```c++
class Basic{
public:
int a;
int b;
};
class Bulk : private Basic{
public:
using Basic::a;
protected:
using Basic::b;
};
```

#### 派生类覆盖重载部分函数
* 因为派生类可以重载继承自基类的成员函数，所以如果派生类希望所有的重载版本对于它都是可见的，那么它就要覆盖所有版本或者一个也不覆盖。
* 但是，有时一个类仅需要覆盖重载部分函数，若覆盖所有函数，就太繁琐了。 只要为重载的成员函数提供一条using声明，这样我们就无需覆盖基类中的每一个版本了。
```c++
#include <iostream>
#include <vector>
 
class A {
 public:
  A() :m_(0) {}
  A(int n) :m_(n) {}
  virtual void show() {
    std::cout << "A show" << std::endl;
  }
  virtual void show(int n) {
    std::cout << "A show int " << n << std::endl;
  }
 
  void test() {
    std::cout << "A test" << std::endl;
  }
  void test(int n) {
    std::cout << "A show test " << n << std::endl;
  }
  int m_;
};
 
class AA : public A {
 public:
  using A::A;     // 场景2
  using A::show;  // 场景3
  using A::test;  // 场景3
  virtual void show() {
    std::cout << "AA show" << std::endl;
  }
  void test() {
    std::cout << "AA test" << std::endl;
  }
};
 
int main() {
  AA aa;
  aa.show();
  aa.test();
  aa.show(1);
  aa.test(1);
 
  return 0;
}
```


