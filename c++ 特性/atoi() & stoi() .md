## c++中的atoi()和stoi()函数的用法和区别

# 相同点：

atoi()和stoi()都是C++的字符处理函数，把# 数字字符串转换成int输出 #
头文件都是#include<string>

# 不同点：

atoi()的参数是 const char*,因此对于一个字符串str我们必须调用 c_str()的方法把这个string转换成 const char*类型的
而stoi()的参数是const string*,不需要转化为 const char*；

stoi()会做范围检查，默认范围是在int的范围内的，如果超出范围的话则会runtime error！
而atoi()不会做范围检查，如果超出范围的话，超出上界，则输出上界，超出下界，则输出下界；

C 库函数 - strtol()
C 标准库 - <stdlib.h> C 标准库 - <stdlib.h>

描述
C 库函数 long int strtol(const char *str, char **endptr, int base) 把参数 str 所指向的字符串根据给定的 base 转换为一个长整数（类型为 long int 型），base 必须介于 2 和 36（包含）之间，或者是特殊值 0。

声明
下面是 strtol() 函数的声明。

long int strtol(const char *str, char **endptr, int base)
参数
str -- 要转换为长整数的字符串。
endptr -- 对类型为 char* 的对象的引用，其值由函数设置为 str 中数值后的下一个字符。
base -- 基数，必须介于 2 和 36（包含）之间，或者是特殊值 0。
返回值
该函数返回转换后的长整数，如果没有执行有效的转换，则返回一个零值。

实例
下面的实例演示了 strtol() 函数的用法。

#include <stdio.h>
#include <stdlib.h>

int main()
{
   char str[30] = "2030300 This is test";
   char *ptr;
   long ret;

   ret = strtol(str, &ptr, 10);
   printf("数字（无符号长整数）是 %ld\n", ret);
   printf("字符串部分是 |%s|", ptr);

   return(0);
}
让我们编译并运行上面的程序，这将产生以下结果：

数字（无符号长整数）是 2030300
字符串部分是 | This is test|
