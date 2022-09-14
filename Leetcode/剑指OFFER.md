

#### 由数据范围反推算法复杂度以及算法内容
![img.png](img.png)



#### 剑指 Offer II 004. 只出现一次的数字
给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
示例 1：
输入：nums = [2,2,3,2]
输出：3
示例 2：
输入：nums = [0,1,0,1,0,1,100]
输出：100
1 <= nums.length <= 3 * 104
-231 <= nums[i] <= 231 - 1
nums 中，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次
进阶：你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
* 不符合要求 空间复杂度O(N) 时间复杂度O(N）
```c++ 
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> umap;
        int result = 0;
        for(int i = 0; i < nums.size(); i++) {
            umap[nums[i]]++;
        }
        for(auto &x : nums) {
            if (umap[x] == 1) result = x;
        }
        return result;
    }
};
```
```c++

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        for (int i = 0; i < 32; ++i) {
            int total = 0;
            for (int num: nums) {
                total += ((num >> i) & 1);
            }
            if (total % 3) {
                ans |= (1 << i);
            }
        }
        return ans;
    }
};
```
```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; i++) { // 因为nums[i]是32位整数，
        // 所以针对每一位的对应二进制数值求和
            int sum = 0;
            for (int num : nums) {
                sum += ((num >> i) & 1); // 提取从右往左数第i位的数值，将所有nums[i]
                // 二进制下的第i位数值进行求和
            }
            if (sum % 3 == 1) { // 如果没办法被3整除，那么说明落单的那个数的第i位是1不是0
                res |= (1 << i);
            }
        }
        return res; // 输出结果
    }
};
```
```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; i++) {
            int sum = 0;
            for (auto &num : nums) {
                sum += ((num >> i) & 1);
            }
            if (sum % 3) {
                res |= (1 << i);
            }
        }
        return res;
    }
};
```
### 剑指 Offer II 005. 单词长度的最大乘积
给定一个字符串数组 words，请计算当两个字符串 words[i] 和 words[j] 不包含相同字符时，它们长度的乘积的最大值。假设字符串中只包含英语的小写字母。如果没有不包含相同字符的一对字符串，返回 0。

示例 1:

输入: words = ["abcw","baz","foo","bar","fxyz","abcdef"]
输出: 16
解释: 这两个单词为 "abcw", "fxyz"。它们不包含相同字符，且长度的乘积最大。
```c++
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int length = words.size();
        vector<int> masks(length);
        for (int i = 0; i < length; i++) {
            string word = words[i];
            int wordLength = word.size();
            for (int j = 0; j < wordLength; j++) {
                masks[i] |= 1 << (word[j] - 'a');
            }
        }
        int maxProd = 0;
        for (int i = 0; i < length; i++) {
            for (int j = i + 1; j < length; j++) {
                if ((masks[i] & masks[j]) == 0) {
                    maxProd = max(maxProd, int(words[i].size() * words[j].size()));
                }
            }
        }
        return maxProd;
    }
};
```
```c++
class Solution {
public:
    int maxProduct(vector<string>& words) {
        
    }
};
```
#### 剑指 Offer II 008. 和大于等于 target 的最短子数组
给定一个含有 n 个正整数的数组和一个正整数 target 。
找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

示例 1：
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
```c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = 0;
        int minValue = INT_MAX;
        int subLength = 0;
        for (int i = 0, j = 0; i < nums.size(); i++) {
            sum += nums[i];
            while(sum >= target) {
                subLength = i - j + 1;
                sum -= nums[j++];
                minValue = min(subLength,minValue)
            }
        }
        return minValue;
    }
};
```

### 剑指 Offer II 007. 数组中和为 0 的三个数
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请
你返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。
```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        // 找出a + b + c = 0
        // a = nums[i], b = nums[left], c = nums[right]
        for (int i = 0; i < nums.size(); i++) {
            // 排序之后如果第一个元素已经大于零，那么无论如何组合都不可能凑成三元组，直接返回结果就可以了
            if (nums[i] > 0) {
                return result;
            }
            // 错误去重方法，将会漏掉-1,-1,2 这种情况
            /*
            if (nums[i] == nums[i + 1]) {
                continue;
            }
            */
            // 正确去重方法
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while (right > left) {
                // 去重复逻辑如果放在这里，0，0，0 的情况，可能直接导致 right<=left 了，从而漏掉了 0,0,0 这种三元组
                /*
                while (right > left && nums[right] == nums[right - 1]) right--;
                while (right > left && nums[left] == nums[left + 1]) left++;
                */
                if (nums[i] + nums[left] + nums[right] > 0) {
                    right--;
                } else if (nums[i] + nums[left] + nums[right] < 0) {
                    left++;
                } else {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    // 去重逻辑应该放在找到一个三元组之后
                    while (right > left && nums[right] == nums[right - 1]) right--;
                    while (right > left && nums[left] == nums[left + 1]) left++;

                    // 找到答案时，双指针同时收缩
                    right--;
                    left++;
                }
            }

        }
        return result;
    }
};
```

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        
    }
}
```
#### 剑指 Offer II 009. 乘积小于 K 的子数组 * 注意细节
给定一个正整数数组 nums和整数 k ，请找出该数组内乘积小于 k 的连续的子数组的个数。
示例 1:

输入: nums = [10,5,2,6], k = 100
输出: 8
解释: 8 个乘积小于 100 的子数组分别为: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]。
需要注意的是 [10,5,2] 并不是乘积小于100的子数组。
```c++
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(k == 0 || k == 1) return 0;
        int sum = 1;
        int res = 0;
        for (int i = 0, j = 0; i < nums.size(); i++) {
            sum = sum * nums[i];
            while(sum >= K) {
                sum /= nums[j];
                j++;
            }
            res += i - j + 1;
        }
        return res;
    }
};
```
#### 剑指 Offer II 010. 和为 k 的子数组
给定一个整数数组和一个整数 k ，请找到该数组中和为 k 的连续子数组的个数。
示例 1：

输入:nums = [1,1,1], k = 2
输出: 2
解释: 此题 [1,1] 与 [1,1] 为两种不同的情况
```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int pre = 0;
        int res = 0;
        unordered_map<int, int> umap;
        umap[0] = 1;
        for (auto & num : nums) {
            pre += num;
            if(umap.find(pre - k) != umap.end()) {
                res += umap[pre - k];
            }
            umap[pre]++;
        }
        return res;
    }
};
```
#### 剑指 Offer II 011. 0 和 1 个数相同的子数组
给定一个二进制数组 nums , 找到含有相同数量的 0 和 1 的最长连续子数组，并返回该子数组的长度。

示例 1：
输入: nums = [0,1]
输出: 2
说明: [0, 1] 是具有相同数量 0 和 1 的最长连续子数组。
```c++
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int maxLength = 0;
        unordered_map<int, int> mp;
        int counter = 0;
        mp[counter] = -1;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            if (num == 1) {
                counter++;
            } else {
                counter--;
            }
            if (mp.count(counter)) {
                int prevIndex = mp[counter];
                maxLength = max(maxLength, i - prevIndex);
            } else {
                mp[counter] = i;
            }
        }
        return maxLength;
    }
};
```


```c++
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i ++ )
            s[i] = s[i - 1] + (nums[i - 1] == 0 ? -1 : 1);

        unordered_map<int, int> hash;
        int res = 0;
        for (int i = 0; i <= n; i ++ )
        {
            if (hash.count(s[i]))
                res = max(res, i - hash[s[i]]);
            // 只有当s[i]在前面没出现过的时候，存下s[i]和其下标
            if (!hash.count(s[i]))
                hash[s[i]] = i;
        }
        return res;
    }
};

```
```c++
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> umap;
        umap[0] = -1; // 
        int sum = 0;
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i] ? 1 : -1;
            if (umap.find(sum) != umap.end()) ans = max(ans, i - umap[sum]);
            else umap[sum] = i;
        }
        return ans;
    }
};
```
#### 304. 二维区域和检索 - 矩阵不可变
给定一个二维矩阵 matrix，以下类型的多个请求：

计算其子矩形范围内元素的总和，该子矩阵的 左上角 为 (row1, col1) ，右下角 为 (row2, col2) 。
实现 NumMatrix 类：

NumMatrix(int[][] matrix) 给定整数矩阵 matrix 进行初始化
int sumRegion(int row1, int col1, int row2, int col2) 返回 左上角 (row1, col1) 、右下角 (row2, col2) 所描述的子矩阵的元素 总和 。
```c++
/一维
class NumMatrix {
public:
    vector<vector<int>> sums;

    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m > 0) {
            int n = matrix[0].size();
            sums.resize(m, vector<int>(n + 1));
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    sums[i][j + 1] = sums[i][j] + matrix[i][j];
                }
            }
        }
    }
    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        for (int i = row1; i <= row2; i++) {
            sum += sums[i][col2 + 1] - sums[i][col1];
        }
        return sum;
    }
};
/二维
class NumMatrix {
public:
    vector<vector<int>> sums;

    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m > 0) {
            int n = matrix[0].size();
            sums.resize(m + 1, vector<int>(n + 1));
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    sums[i + 1][j + 1] = sums[i][j + 1] + sums[i + 1][j] - sums[i][j] + matrix[i][j];
                }
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return sums[row2 + 1][col2 + 1] - sums[row1][col2 + 1] - sums[row2 + 1][col1] + sums[row1][col1];
    }
};
```
```c++
class NumMatrix {
    vector<vector<int>> sums;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        if (m > 0) {
            sums.resize(m + 1, vector<int>(n + 1, 0));
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    sums[i + 1][j + 1] = sums[i][j + 1] + sums[i + 1][j] - sums[i][j] + matrix[i][j];
                }
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sums[row2 + 1][col2 + 1] - sums[row1][col2 + 1] - sums[row2 + 1][col1] + sums[row1][col1];
    }
};
```
#### 剑指 Offer II 014. 字符串中的变位词
给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的某个变位词。
换句话说，第一个字符串的排列之一是第二个字符串的 子串 。

示例 1：
输入: s1 = "ab" s2 = "eidbaooo"
输出: True
解释: s2 包含 s1 的排列之一 ("ba").
```c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> umap;
        for(auto &c : s1) umap[c]++;
        for(int i = 0, j = 0; i < s2.size(); i++) {
            umap[s2[i]]--;
            while(umap[s2[i]] < 0) {
                umap[s2[j]]++;
                j++;
            }
            if (i - j + 1 == s1.size()) return true;
        }
        return false;
    }
};
```
#### 剑指 Offer II 015. 字符串中的所有变位词
给定两个字符串 s 和 p，找到 s 中所有 p 的 变位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
变位词 指字母相同，但排列不同的字符串。
示例 1：
输入: s = "cbaebabacd", p = "abc"
输出: [0,6]
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的变位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的变位词。
```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> umap1;
        unordered_map<char, int> umap2;
        for (auto &c : p) {
            umap1[c]++;
        } 
        vector<int> result;
        for(int i = 0, j = 0; i < s.size(); i++) {
            umap2[s[i]] ++;
            while(umap2[s[i]] > umap1[s[i]]) {
                map2[s[j++]]--;
            }
            if(i - j + 1 == p.size()) result.push_back(i);
        }
        return result;
    }
};
```
###  剑指 Offer II 016. 不含重复字符的最长子字符串
给定一个字符串 s ，请你找出其中不含有重复字符的 最长连续子字符串 的长度。
示例 1:
输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子字符串是 "abc"，所以其长度为 3。   
```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> umap;
        int res = 0;
        for (int i = 0, j = 0; i < s.size(); i++) {
            umap[s[i]]++;
            while(umap[s[i]] > 1) {
                umap[s[j]]--;
                j++;
            }
            res = max(res, i - j + 1);
        }
        return res;
    }
};
```

#### 剑指 Offer II 021. 删除链表的倒数第 n 个结点
给定一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
```c++
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* fast = head;
        ListNode* slow = dummy;
        for(int i = 0; i < n; i++) {
            fast = fast->next;
        }
        while(fast) {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return dummy->next;
    }
};
```

#### 剑指 Offer II 025. 链表中的两数相加
给定两个 非空链表 l1和 l2 来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。
可以假设除了数字 0 之外，这两个数字都不会以零开头。
```c++
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1, s2;
        while(l1) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        while(l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        ListNode* pre = nullptr;
        int carry = 0;
        while(!s1.empty() || !s2.empty() || carry != 0) {
            int sum = carry;
            if(!s1.empty()) sum += s1.top(), s1.pop();
            if(!s2.empty()) sum += s2.top(), s2.pop();
            ListNode* node = new ListNode(sum % 10);
            node->next = pre;
            pre = node;
            carry = sum / 10;
        }
        return pre;
    }
};
```

#### 剑指 Offer II 027. 回文链表
给定一个链表的 头节点 head ，请判断其是否为回文链表。
如果一个链表是回文，那么链表节点序列从前往后看和从后往前看是相同的。
示例 1：

输入: head = [1,2,3,3,2,1]
输出: true
示例 2：

输入: head = [1,2]
输出: false
```c++
class Solution {
    public:
    bool isPalindrome(ListNode* head) {
        
    }
};
```
#### 剑指 Offer II 028. 展平多级双向链表
多级双向链表中，除了指向下一个节点和前一个节点指针之外，它还有一个子链表指针，可能指向单独的双向链表。这些子列表也可能会有一个或多个自己的子项，依此类推，生成多级数据结构，如下面的示例所示。

给定位于列表第一级的头节点，请扁平化列表，即将这样的多级双向链表展平成普通的双向链表，使所有结点出现在单级双链表中。


```c++
class Solution {
public:
    Node* flatten(Node* head) {
        if(!head)
            return NULL;
        Node* ch = flatten(head->child);
        Node* right = flatten(head->next);
        head->child = NULL;
        if(ch)
        {
            head->next = ch;
            ch->prev = head;
            while(ch->next)
                ch = ch->next;
            ch->next = right;
            if(right)
                right->prev = ch;
        }
        return head;
    }
};
class Solution {
public:
    Node* flatten(Node* head) {
        function<Node*(Node*)> dfs = [&](Node* node) {
            Node* cur = node;
            // 记录链表的最后一个节点
            Node* last = nullptr;

            while (cur) {
                Node* next = cur->next;
                //  如果有子节点，那么首先处理子节点
                if (cur->child) {
                    Node* child_last = dfs(cur->child);

                    next = cur->next;
                    //  将 node 与 child 相连
                    cur->next = cur->child;
                    cur->child->prev = cur;

                    //  如果 next 不为空，就将 last 与 next 相连
                    if (next) {
                        child_last->next = next;
                        next->prev = child_last;
                    }

                    // 将 child 置为空
                    cur->child = nullptr;
                    last = child_last;
                }
                else {
                    last = cur;
                }
                cur = next;
            }
            return last;
        };

        dfs(head);
        return head;
    }
};

Node* flatten(Node* head) {
        Node* cur = head;
        while(cur != nullptr && cur->child == nullptr) cur = cur->next; //找到有分支的结点
        if(cur == nullptr) return head; //当递归到最后的一条时，直接返回头结点，不用去连接上一条的结点
        Node* newHead = flatten(cur->child); //处理后的链表的头结点
        Node* tailNode = foundTail(newHead); //处理后的链表的尾结点
        //处理后的新链表插入上一层链表中
        newHead->prev = cur;
        if(cur->next) {
            tailNode->next = cur->next;
            cur->next->prev = tailNode;
        }
        cur->next = newHead;
        cur->child = nullptr;        
        return head;
    }
    //找到链表的最后一个节点
    Node* foundTail(Node* head) {
        if(head == nullptr || head->next == nullptr) return head;
        Node* cur = head;
        while(cur->next) cur = cur->next;
        return cur;
    }

class Solution {
public:
    Node* flatten(Node* head) {
        if(head == nullptr) return nullptr;
        Node* node = head;
        while(node != nullptr) {
            // 孩子不为空
            if(node -> child != nullptr) {
                Node* next = node -> next;
                Node* child = flatten(node -> child);
                // 扁平化
                node -> next = child;
                child -> prev = node;
                // 孩子要去掉
                node -> child = nullptr;
                if(next != nullptr) {
                    // 遍历到当前扁平化的尾部
                    while(node -> next != nullptr) {
                        node = node -> next;
                    }
                    // 和之前的next连接
                    node -> next = next;
                    next -> prev = node;
                }
            }
            node = node -> next;
        }
        return head;
    }
};

```
```c++
class Solution {
public:
    Node* flatten(Node* head) {
        Node* p = nullptr;
        stack<Node*> s;
        if(head) s.push(head);
        while(s.size()){
            auto now = s.top(); s.pop();
            if(p) p->next = now;
            now->prev = p;
            p = now;
            if(p->next) s.push(p->next);
            if(p->child) s.push(p->child);
            p->child = nullptr;
        }
        return head;
    }
};
class Solution {
public:
    Node* flatten(Node* head) {
        stack<Node*> stk; //创建一个栈用来存放有child节点的下一个节点
        Node* p = head;   //此指针循环遍历多级链表

        if(!head)return head;//如果链表为空直接返回

        while(p || !stk.empty()){    //当栈为空并且p的下一个节点为空时就退出循环
            if(p->child){
                if(p->next)stk.push(p->next);//如果是p->child不为空就将p的下一个节点入栈
                p->child->prev = p;         //将孩子节点的前指针指向p
                p->next = p->child;         //将p的next指针指向p的孩子节点
                p->child = nullptr;         //将p的child指针指向空
            }
            if(p->next==nullptr&&!stk.empty()){     //如果指针下一个节点为空，看看栈中是否还有元素
                p->next = stk.top();                //如果有元素说明这个多级双向链表并没有循环遍历完毕
                stk.top()->prev = p;
                stk.pop();
            }
            p = p->next;          
        }
        return head;
    }
};

class Solution {
public:
    Node* flatten(Node* head) {
        Node* node = head;
        stack<Node*> s;
        while(node != nullptr) {
            // 孩子不为空
            if(node -> child != nullptr) {
                if(node -> next != nullptr) {
                    s.push(node -> next);
                }
                Node* child = node -> child;
                // 扁平化
                node -> next = child;
                child -> prev = node;
                // 孩子要去掉
                node -> child = nullptr;
            }
            if(node -> next == nullptr && !s.empty()) {
                Node* next = s.top();
                s.pop();
                node -> next = next;
                next -> prev = node;
            }
            node = node -> next;
        }
        return head;
    }
};

```
```c++
class Solution {
   Node* findTail(Node* head) {
       if(head == nullptr || head->next == nullptr) return head;
       Node* cur = head;
       while(cur->next) cur = cur->next;
       return cur;
   }
public:
    Node* flatten(Node* head) {
        Node* cur = head;
        while(cur && cur->child == nullptr) cur = cur->next;
        if (cur == nullptr) return head;
        Node* newHead = flatten(cur->child);
        Node* tailNode = findTail(newHead);
        newHead->prev = cur;
        if(cur->next) {
            tailNode->next = cur->next;
            cur->next->prev = tailNode;
        }
        cur->next = newHead;
        cur->child = nullptr;
        return head;
    }
};
```

#### 剑指 Offer II 076. 数组中的第 k 大的数字
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:
输入: [3,2,1,5,6,4] 和 k = 2
输出: 5
```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {

    }
};
```