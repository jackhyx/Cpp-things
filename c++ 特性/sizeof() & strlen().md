#### sizeof()与strlen()的区别：

* sizeof()是运算符，确切的说是一个编译时运算符，参数可以是数组、指针、类型、对象、函数等
用于统计类型或者变量所占的内存字节数,由于在编译时计算，因此sizeof不能用来返回动态分配的内存空间的大小。


* strlen()是C标准库中的字符串函数，要在运行时才能计算。参数必须是字符型指针（char*）, 且必须是以'\0'结尾的
它的功能是：返回字符串的长度。该字符串可能是自己定义的，也可能是内存中随机的，该函数实际完成的功能是从代表该字符串的第一个地址开始遍历，直到遇到结束符'\0'。返回的长度大小不包括'\0'。


#### 实例
-------------------------------------------------------------------------------
char *str = "hello";
strlen(str); //它的值是5，因为hello这个字符串有5个字符

sizeof(str); //它的值是4，因为char *是一个指针类型，它占4个字节。

sizeof("hello"); //它的值是5，是因为hello有5个字符，每一个字符占1个字节。

-------------------------------------------------------------------------------
int a[2] = {0};
sizeof(a); //它的值是8，因为a中有2个int型变量，每个int型占4个字节，所以8字节

strlen(a) //a相当于一个指针，但是strlen只能接受char*类型，所以编译时出错

-------------------------------------------------------------------------------
char arr[10] = "Hello";
int len_one = strlen(arr); //它的值是5 strlen只关心存储的数据内容，不关心空间的大小和类型

int len_two =sizeof(arr); // 它的值是10 sizeof返回定义arr数组时，编译器为其分配的数组空间大小，不关心里面存了多少数据（10x1

-------------------------------------------------------------------------------
char * parr =new char[10];
int len_one = strlen(parr); //它的值是3实际上每次运行可能不一样，这取决于parr里面存了什么（从parr[0]开始直到遇到第一个'\0'结束）

int len_two = sizeof(parr); //结果实际上本意是想计算parr所指向的动态内存空间的大小，
// 但是事与愿违，sizeof认为parr是个字符指针，因此返回的是该指针所占的空间（指针的存储用的是长整型，所以为4）

int len_three = sizeof(*parr); //由于*parr所代表的是parr所指的地址空间存放的字符，所以长度为1 字符串的第一位所占的内存空间，是char类

-------------------------------------------------------------------------------


####
数组作为参数传给函数时传的是指针而不是数组，传递的是数组的首地址，

fun(char [8])
fun(char [])
都等价于 fun(char *)

在C++里参数传递数组永远都是传递指向数组首元素的指针，编译器不知道数组的大小
如果想在函数内知道数组的大小， 需要这样做：
进入函数后用memcpy拷贝出来，长度由另一个形参传进去

fun(unsiged char *p1, int len)
{
unsigned char* buf = new unsigned char[len+1]
memcpy(buf, p1, len);
}


面试题：定义一个空的数据类型，里面没有任何成员变量和成员函数，对该类型求sizeof，得到的结果是多少？

答案：是1，为什么不是0？空类型的实例中不包含任何信息，本来求sizeof应该是0，
但是当我们声明该类型的实例时，它必须在内存中占有一定的空间，否则无法使用这些实例（也就不能求sizeof了），
至于占用多少内存  

##由编译器决定，Visual Studio中每个空类型的实例占用1字节的空间##

扩展1：如果在该类型中添加一个构造函数和析构函数，再求sizeof，得到的结果是多少？

答案：还是1。

##调用构造函数和析构函数只需要知道函数的地址即可，而这些地址只与类型相关，而与类型的实例无关，编译器也不会因为这两个函数而在实例内添加任何额外的信息##

注：不管添加的是构造函数还是析构函数还是其它任何类型的函数，都是这个结果。

扩展2：那如果把析构函数标记为虚函数呢？

答案：C++的编译器一旦发现一个类型中有虚函数，就会为该类型生成虚函数表
##在该类型的每一个实例中添加一个指向虚函数表的指针##
在32位机器上，一个指针占4字节空间，因此求sizeof得到4；如果是64位则为8



