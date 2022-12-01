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
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        } else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};


```