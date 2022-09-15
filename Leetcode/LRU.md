/*
    分析上面的操作过程，要让 put 和 get 方法的时间复杂度为 O(1)，我们可以总结出 cache 这个数据结构必要的条件：
    1、显然 cache 中的元素必须有时序，以区分最近使用的和久未使用的数据，当容量满了之后要删除最久未使用的那个元素腾位置。
    2、我们要在 cache 中快速找某个 key 是否已存在并得到对应的 val；
    3、每次访问 cache 中的某个 key，需要将这个元素变为最近使用的，也就是说 cache 要支持在任意位置快速插入和删除元素。
    那么，什么数据结构同时符合上述条件呢？哈希表查找快，但是数据无固定顺序；链表有顺序之分，插入删除快，但是查找慢。所以结合一下，形成一种新的数据结构：哈希链表 LinkedHashMap。
*/
```c++

class LRUCache {
private:
    int cap;    // 最大容量
    list<pair<int, int>> cache;  // 双向链表，节点存放的是<key, value>
    unordered_map<int, list<pair<int, int>>::iterator> map; // 哈希表，存放key及其在双向链表中的节点位置（迭代器）

public:
    LRUCache(int capacity) : cap(capacity) {
        // c++11新特性，相当于
        // cap = capacity;
    }

    // 定义：如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1
    int get(int key) {
        if(!map.count(key)){
            // 没找到key
            return -1;
        }
        // 将 key 变为最近使用：队头位置是最近使用，队尾位置是最久未使用
        auto key_value = *map[key]; // map[key]是双端列表迭代器，所以要解*，获得的是pair<int,int>(key, value)
        cache.erase(map[key]);  // 在双向链表中删除key所在的节点
        cache.push_front(key_value);    // 将key_value插入到队头
        map[key] = cache.begin();   // 重新链接哈希表中key和双端列表key所在节点的对应关系

        return key_value.second;
    }

    // 定义：如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
    void put(int key, int value) {
        if(!map.count(key)){
            // 找不到key
            if(cache.size() == cap){
                // 双端队列满了，逐出最久未使用的队尾元素
                map.erase(cache.back().first);  // 哈希表逐出
                cache.pop_back();   // 双端队列逐出
            }
        } else{
            // 存在，变更其数据值value
            cache.erase(map[key]);
          }
        // 向缓存中队头位置插入{key, value}
        cache.push_front({key, value});
        map[key] = cache.begin();
    }
};
```
```c++
/ 总的思想就是 哈希双向链表
struct Node
{
    int key;
    int value;
    Node* pre;
    Node* next;
    // 构造函数初始化
    Node(int key, int value) : key(key), value(value), pre(nullptr), next(nullptr){}
};

class LRUCache {
private:
    int size;// 缓冲区大小
    Node* head;
    Node* tail;
    map<int, Node*> p;

public:
    LRUCache(int capacity) {
        this->size = capacity;
        head = nullptr;
        tail = nullptr;
    }
// 获取缓冲区中 key 对应的 value
    int get(int key) {
        // 1.当该 key 值存在
        if(p.count(key) > 0)
        {
            // 删除该 key 对应的原来节点
            Node* cur = p[key];
            int value = cur->value;
            remove(cur);   // 这里仅仅删除哈希双向链表中的节点，不必删除哈希表中的                 
            // 将节点重现插入到缓冲区的头部
            setHead(cur);                     
            return value;
        }
        // 2.当该 key 值不存在
        return -1;
    }
// 将key-value值存入缓冲区
    void put(int key, int value) {
        // 1.当该 key 值存在
        if(p.count(key) > 0)
        {
            // 删除该 key 对应的原来节点
            Node* cur = p[key];
            cur->value = value;
            remove(cur);    // 这里仅仅删除哈希双向链表中的节点，不必删除哈希表中的                                
            // 将节点重现插入到缓冲区的头部
            setHead(cur);
        }
        else// 2.当该 key 值不存在
        {
            Node* node = new Node(key, value);
            // 判断当前缓冲区大小已经满了
            if(p.size() >= size)
            {
                // 删除尾部节点
                map<int, Node*>::iterator it = p.find(tail->key);// 返回迭代器类型
                remove(tail);
                p.erase(it);// 这里erase 函数参数是迭代器类型，所以上面需要使用迭代器类型
                // 将新节点插入到缓冲区的头部
            }
            //else 此时因为动作和上面重复，所以直接合并使用
            //还没有满：将新节点插入到缓冲区的头部
            {
                setHead(node);
                p[key] = node;
            }
        }
    }

    // 删除当前节点
    void remove(Node* cur)
    {
        // 当前节点是 head
        if(cur == head)
            head = cur->next;
        else if(cur == tail)// 当前节点是 tail
            tail = cur->pre;
        else// 当前节点是一般节点
        {
            cur->pre->next = cur->next;
            cur->next->pre = cur->pre;
        }
    }
    // 将当前节点插入到头部
    void setHead(Node* cur)
    {
        cur->next = head;
        if(head != nullptr)
            head->pre = cur;
        head = cur;//重现更新head

        if(tail==nullptr)
            tail = head;
    }
};
```
```c++
class LRUCache {
private:
    int cap;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> map;
public:
    LRUCache(int capacity) : cap(capacity) {
    }

    int get(int key) {
        if (map.find(key) == map.end()) return -1;
        auto key_value = *map[key];
        cache.erase(map[key]);
        cache.push_front(key_value);
        map[key] = cache.begin();
        return key_value.second;
    }

    void put(int key, int value) {
        if (map.find(key) == map.end()) {
            if (cache.size() == cap) {
                map.erase(cache.back().first);
                cache.pop_back();
            }
        }
        else {
            cache.erase(map[key]);
        }
        cache.push_front({key, value});
        map[key] = cache.begin();
    }

};

```

```