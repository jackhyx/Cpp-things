array容器和数组的区别与联系
联系：

都使用连续空间存储元素，可以进行随机访问
元素个数都固定
区别：

数组是不安全的，array是比较安全的，array避免访问越界
array提供了更好的数据访问机制，即可以使用front()和back()以及at()访问方式，使得访问更加安全。而数组只能通过下标访问，在写程序中很容易出现越界的错误
array容器支持迭代器，访问遍历更加方便
array提供了size()和Empty()，而数组只能通过sizeof()/strlen()以及遍历计数来获取大小和是否为空


#### array的迭代器
#### array大小(容量)相关方法
* size()——元素个数
* max_size()——最多能容纳元素个数：
* empty()——检查array是否为空
* array常用操作
* at()——访问array元素
* front()——访问array头元素
* back()——访问array尾元素
* data()——返回指向array中第一个元素的指针
* fill(n)——使用n填充array
* swap()——交换两个array容器中的元素
* array容器和数组的区别与联系
