#### 函数介绍
包含头文件:#include<string.h>;
函数原型: void *memset(void *s , int ch , size_t n );
解释:
The memset() function fills the first n bytes of the memory area pointed to by s with the constant byte c.
将s所指向的某一块内存的前n个字节替换成c, 并返回指向内存s 的指针;
注意:
* s  可以为数组和结构体;
* ch 可以为数字，其对应ASCII的数值, 也可以为任意字符’’;
* n  为长度, 为无符号整型变量;
#### 函数作用和意义:
在一段内存块中填充某一个给定的值，常用于较大的对结构体和数组的清零操作.
例子
* 初始化字符串列表
```
/* memset example */
#include <stdio.h>
#include <string.h>

    int main ()
    {
        char str[] = "almost every programmer should know memset!";
        memset (str,'-',6);
        puts (str);
        return 0;
    }

输出为: ------ every programmer should know memset!.
```
* 初始化整型数组

#include<string.h>
#include<iostream>

```   
    int main()
        {
        int iBuf[10];
        memset(iBuf, 0, sizeof(int) * 10);
        for (int i = 0; i < 10; ++i)
        {
        std::cout<<iBuf[i];
        }
        std::cout<<std::endl;
        
        return 0;
    }

输出: 0000000000
```
* 初始化结构体
```
#include<string.h>
#include<iostream>
#include<stdlib.h>

    int main()
    {
    struct sample_struct
    {
    char csName[16];
    int iSeq;
    int iType;
    }stTest;
    // struct sample_strcut stTest;
    memset(&stTest,0,sizeof(struct sample_struct));
    for (int i=0;i<16;i++)
    {
    std::cout<<stTest.csName[i];
    }
    std::cout<<std::endl;
    std::cout<<stTest.iSeq<<stTest.iType<<std::endl;
    return 0;
    }

输出:

00
```
#### 注意事项
* 对字符指针所指区域初始化, 必须先分配内存;
```
#include<string.h>
#include<iostream>
#include<stdlib.h>

int main()
{
char* pBuf = (char *)malloc(sizeof(char) * 10);

if (pBuf != NULL)
{
memset(pBuf, 97, sizeof(char) * 10);		// 97的ASCII值对应的是字符a
for (int i = 0; i < 10; ++i)
{
std::cout<<pBuf[i];
}
std::cout<<std::endl;

	free(pBuf);
	pBuf = NULL;
}

return 0;
}
 
输出: aaaaaaaaaa
```
* memset中的第三个参数 n 最好使用sizeof操作符，因为每个系统下对类型长度的定义可能不一样.
* 返回指向s所在内存的指针是为了实现链式编程.
*  memset是按照　字节　为单位进行初始化的, 对于单字节数据类型char可以随意赋值, 对于多字节数据类型则只能赋值为0.
```
#include<string.h>
#include<iostream>

int main()
{
int arr[10];
memset(arr,1,sizeof(int)*10);
for(int i=0; i<10;i++)
{
std::cout<<arr[i]<<" ";
}
std::cout<<std::endl;
return 0;
}
```
输出:16843009 16843009 16843009 16843009 16843009 16843009 16843009 16843009 16843009 16843009
由于int占4个字节(byte)，因此"1"对应的二进制(32bits下)为"00000000 00000000 00000000 00000001"(4bytes)，塞到1byte(8bit)的中，高位被舍弃了。所以，填入数组中的值是"00000001"。然而总共有10×4=40个byte，所以数组每一个元素都是00000001 00000001 0000001 0000001 也就是　0x01010101=16843009