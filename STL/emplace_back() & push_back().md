
####  异同点
* 如果参数是左值，两个调用的都是copy constructor 
* 如果参数是右值，两个调用的都是move constructor（C++ 11后push_back也支持右值） 
* 最主要的区别是，emplace_back支持in-place construction，也就是说emplace_back(10, “test”)可以只调用一次constructor
* 而push_back(MyClass(10, “test”))必须多一次构造和析构
####  需要澄清的一些误解
* emplace_back的效率比push_back高，无论什么情况下都高，所以可以无脑用。从上面1、2点可以看到，两者其实没有区别
* push_back不支持右值参数，不能调用move constructor，效率低。由C++ Reference可以得知，C98是没有右值形参的，但C++11已经增加了。
* emplace_back的优势是右值时的效率优化。这是最大的误解，emplace_back的最大优势是它可以直接在vector的内存中去构建对象，不用在外面构造完了再copy或者move进去！！！

#### 使用建议
* 左值用push_back 
* 右值用emplace_back 
* 局部变量尽量使用emplace_backin-place构建，不要先构建再拷贝或移动。
```
std::cout << "--------------------------------push_back rvalue:" << std::endl;
vec_bc.push_back(BaseClass("b3", 1));
// vec_bc.push_back("b4_1");// 不能通过编译
```
#### 结果分析
可以看到，emplace和push对于右值是没有差异的，左值也是没有差异的，调用的构造函数类型和数量都是一样的。
区别在于b1_1这种构造方式，emplace_back只调用一次普通构造函数，push_back直接不支持这种操作。

#### 先来看两者的实现源码：
```c++
void push_back(const value_type& __x)
{
if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
{
_Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish, __x);
++this->_M_impl._M_finish;
}
else
#if __cplusplus >= 201103L
_M_emplace_back_aux(__x);
#else
_M_insert_aux(end(), __x);
#endif
}



void push_back(value_type&& __x)
{
emplace_back(std::move(__x));
}



#if __cplusplus >= 201103L
template<typename _Tp, typename _Alloc>
template<typename... _Args>
void vector<_Tp, _Alloc>::emplace_back(_Args&&... __args)
{
if (this->_M_impl._M_finish != this->_M_impl._M_end_of_storage)
{
_Alloc_traits::construct(this->_M_impl, this->_M_impl._M_finish, std::forward<_Args>(__args)...);
++this->_M_impl._M_finish;
}
else
_M_emplace_back_aux(std::forward<_Args>(__args)...);
}
#endif
```

当参数是左值时，push_back和emplace_back的区别在于后者对参数多进行了一个std::forward操作
当参数是右值时，push_back其实是调用的emplace_back实现的。
所以什么时候该用什么就很明显了。
