#### C++ struct和class的区别
*  相同点
两者都拥有成员函数、公有和私有部分
任何可以使用class完成的工作，同样可以使用struct完成;

* 不同点
struct默认是公有的，class则默认是私有的
class默认是private继承，而struct模式是public继承
class 可以使用模板，而 struct 不能


#### 引申：C++和C的struct区别

C语言中：struct是用户自定义数据类型（UDT）
C++中 : struct是抽象数据类型（ADT），支持成员函数的定义，（C++中的struct能继承，能实现多态）
C中struct是没有权限的设置的，且struct中只能是一些变量的集合体，可以封装数据却不可以隐藏数据，而且成员不可以是函数
C++中，struct增加了访问权限，且可以和类一样有成员函数，成员默认访问说明符为public（为了与C兼容）

struct作为类的一种特例是用来自定义数据结构的。一个结构标记声明后，在C中必须在结构标记前加上struct，才能做结构类型名（除：typedef struct class{};）
C++中结构体标记（结构体名）可以直接作为结构体类型名使用，此外结构体struct在C++中被当作类的一种特例
