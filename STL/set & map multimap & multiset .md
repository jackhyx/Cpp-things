### set和multiset介绍

* set和multiset以底层红黑树为结构
* set的key和value是合一的，value就是key # 通过比较key插入平衡二叉树 # 
* 可以通过迭代器，从小到大输出key，也就是所谓的自动排序，二叉树以及排好序了 # 
* 禁止通过迭代器修改key，否则二叉树结构变化了，如果希望修改一个元素值，必须先删除原有的元素，再插入新的元素。

#### set的特性：
* 所以元素都会根据元素的键值# 自动排序 # 
* set元素的键值就是实值，实值就是键值。set不允许两个元素有相同的键值。 
* 底层直接用红黑树实现，然后通过中序遍历，即可返回键值由小到大的排列。 
* 不允许相同的元素存在，底层采用RB-tree的insert_unique() 独一无二的插入，当插入的元素已经存在于集合中，那么将忽略 
* 而mulitiset采用inset_equal()实现，允许相同的key存在于集合之中。

### map和multimap介绍
* 所有元素都会根据元素的键值（key）自动被排序。 
* map的所有元素都是pair，同时拥有实值(value)和键值(key)。pair的第一个元素是key，第二个是value。map不允许两个元素拥有相同的键值，multimap允许。 
* map迭代器不允许改变map的元素的key，否则破坏map排序。但是可以修改value，例如键是学生，值是学生的成绩单，那么成绩应该可以变。所以迭代器允许修改value而不允许修改key。 
* 底层通过红黑树实现。


#### map的实现
* map的特性是所有元素会根据键值进行自动排序。map中所有的元素都是pair，拥有键值(key)和实值(value)两个部分，并且不允许元素有相同的key 
* 一旦map的key确定了，那么是无法修改的，但是可以修改这个key对应的value，因此map的迭代器既不是constant iterator，也不是mutable iterator 
* 标准STL map的底层机制是RB-tree（红黑树），另一种以hash table为底层机制实现的称为hash_map。 
* map的在构造时默认采用递增排序key，也使用alloc配置器配置空间大小，需要注意的是在插入元素时，调用的是红黑树中的insert_unique()方法，而非insert_euqal()（multimap使用）

```
#include <map>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    map<string, int> maps;
    //插入若干元素
    maps["jack"] = 1;
    maps["jane"] = 2;
    maps["july"] = 3;
    //以pair形式插入
    pair<string, int> p("david", 4);
    maps.insert(p);
    //迭代输出元素
    map<string, int>::iterator iter = maps.begin();
    for (; iter != maps.end(); ++iter)
    {
        cout << iter->first << " ";
        cout << iter->second << "--"; //david 4--jack 1--jane 2--july 3--
    }
    cout << endl;
    //使用subscipt操作取实值
    int num = maps["july"];
    cout << num << endl; // 3
    //查找某key
    iter = maps.find("jane");
    if(iter != maps.end())
        cout << iter->second << endl; // 2
    //修改实值
    iter->second = 100;
    int num2 = maps["jane"]; // 100
    cout << num2 << endl;

    return 0;
}
```

* 需要注意的是subscript（下标）操作既可以作为左值运用（修改内容）也可以作为右值运用（获取实值）。例如：
* maps["abc"] = 1; // 左值运用
* int num = masp["abd"]; //右值运用
```
无论如何，subscript操作符都会先根据键值找出实值，源码如下：
...T& operator[](const key_type& k){    
    return (*((insert(value_type(k, T()))).first)).second;
}...
代码运行过程是：首先根据键值和实值做出一个元素，这个元素的实值未知，因此产生一个与实值型别相同的临时对象替代：
value_type(k, T());
Copy to clipboardErrorCopied
再将这个对象插入到map中，并返回一个pair：
pair<iterator,bool> insert(value_type(k, T()));
Copy to clipboardErrorCopied
pair第一个元素是迭代器，指向当前插入的新元素，如果插入成功返回true，此时对应左值运用，根据键值插入实值
插入失败（重复插入）返回false，此时返回的是已经存在的元素，则可以取到它的实值

(insert(value_type(k, T()))).first; //迭代器
*((insert(value_type(k, T()))).first); //解引用
(*((insert(value_type(k, T()))).first)).second; //取出实值
由于这个实值是以引用方式传递，因此作为左值或者右值都可以


map<string,int> imap;
pair<string,int> tmp("A",1);
imap.insert(tmp);
imap[string("B")]=2;//  当“[ ]”返回的元素作为左值运用时，如果没有‘B’，则在红黑树中插入这个节点，如果有‘B’，则返回指向这个节点的迭代器 
int second=imp[string("C")];
map<string,int>::iterator imapIter=imap.begin();
while(imapIter!=imap.end())
{
  cout<<(*imapIter).first<<" "<<(*imapIter).second<<endl;
  imapIter++;
}

T& operator[](const key_type& k) {//中括号里面输入key，找出对应的值，如果没有则创建对应的key
return (*((insert(value_type(k, T()))).first)).second;
```
#### 注意的点：
* map内部是将Key和Value包装成pair对象操作，所以当使用插入操作的时候，必须将key和Value通用保证成pair对象插入。如同mymap.insert( pair<string , int>("david" , 5) ); 
* typedef pair<const Key, T> value_type中的key为const型别，所以不允许迭代器修改key的值，也就是说一个节点的key只可赋值一次而已，但是可以修改value数值

* T& operator[](const key_type& k)[]里面输入参数是key，返回是value的引用 
* 首先value_type(k, T())将key和value合成一个pair临时对象，然后插入红黑树，并返回一个pair对象，first是迭代器（key不存在则指向新节点，存在则指向老节点），second是成功与否
* 然后通过迭代器获取pair元素的第二个值的引用 
* 如果key存在，则修改其value，如果key不存在，则插入key并且用填入value。总之这里返回的时候value的引用。当做左值，则修改，当做右值则读取。

* 注意map的迭代器指向的是节点，节点里面Value_filed是pair对象。所以通过迭代器的(*mymapIter)是获取了节点中的pair对象，然后通过.运算符获取其中的key和value。

* []运算符重载是map特有的方法，mulitimap里面并没有重载这个方法。


