#### string_view
string_view 是C++17所提供的用于处理只读字符串的轻量对象。这里后缀 view 的意思是只读的视图。

通过调用 string_view 构造器可将字符串转换为 string_view 对象。
string 可隐式转换为 string_view。
string_view 是只读的轻量对象，它对所指向的字符串没有所有权。
string_view通常用于函数参数类型，可用来取代 const char* 和 const string&。
string_view 代替 const string&，可以避免不必要的内存分配。
string_view的成员函数即对外接口与 string 相类似，但只包含读取字符串内容的部分。
string_view::substr()的返回值类型是string_view，不产生新的字符串，不会进行内存分配。
string::substr()的返回值类型是string，产生新的字符串，会进行内存分配。
```c++
#include <string>
#include<iostream>
using namespace std;
 
 int main()
 {
     string_view a = "12345";
     string_view b = a.substr(1, 2);
     cout<<b<<endl;    //输出：23
     string c = b.data();
     cout<<c<<endl;    //输出：2345
     return 0;
 }
 
//string_view的substr可以类似string.substr一样返回一个新的视图。
//但是当对这个新的视图获取其data时，实际上是返回的从视图的起点一直到原始字符串结束的所有字符。
```
### 使用陷阱
* string_view范围内的字符可能不包含\0
```c++
#include <iostream>
#include <string_view>

int main() {
    std::string_view str{"abc", 1};
    std::cout << str.data() << std::endl;
    return 0;
}
```

本来是要打印a，但输出了abc。这是因为字符串相关的函数都有一条兼容C的约定：\0代表字符串的结尾。
上面的程序打印从开始到字符串结束的所有字符，虽然str包含的有效字符是a，但cout认\0。
好在这块内存空间有合法的字符串结尾符，如果str指向的是一个没有\0的字符数组，程序很有可能会出现内存问题，所以我们在将string_view类型的数据传入接收字符串的函数时要非常小心。

* 从[const] char*构造string_view对象时间复杂度O(n)
这是因为获取字符串的长度需要从头开始遍历。如果对[const] char*类型仅仅是一些O(1)的操作，相比直接使用[const] char*，转为string_view是没有性能优势的。只不过是相比const string&，string_view少了拷贝的损耗。
实际上我们完全可以用[const] char*接收所有的字符串，但这个类型太底层了，不便使用。在某些情况下，我们转为string_view可能仅仅是想用其中的一些函数，比如substr。

* string_view指向的内容的生命周期可能比其本身短
string_view并不拥有其指向内容的所有权，用Rust的术语来说，它仅仅是暂时borrow（借用）了它。如果拥有者提前释放了，你还在使用这些内容，那会出现内存问题，
* 这跟悬挂指针(dangling pointer)或悬挂引用（dangling references）很像。Rust专门有套机制在编译时分析变量的生命期，保证borrow的资源在使用期间不会被释放，但C++没有这样的检查，需要人工保证。下面列出一些典型的问题情况：
```c++
    std::string_view sv = std::string{"hello world"};
    string_view foo() {
        std::string s{"hello world"};
        return string_view{s};
    }
    auto id(std::string_view sv) { return sv; }
    
    int main() {
    std::string s = "hello";
    auto sv = id(s + " world");
    }
```

string_view解决了一些痛点，但同时也引入了指针和引用的一些老问题。
C++标准并没有对这个类型做太多的约束，这引来的问题是我们可以像平常的变量一样以多种方式使用它，如，可以传参，可以作为函数返回值，可以做普遍变量，甚至我们可以放到容器里。
随着使用场景的复杂，人工是很难保证指向的内容的生命周期足够长。所以，推荐的使用方式：仅仅作为函数参数，因为如果该参数仅仅在函数体内使用而不传递出去，这样使用是安全的。