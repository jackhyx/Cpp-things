
https://oi-wiki.org/string/match/
https://github.com/xiaobaiTech/golangFamily
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
#### 剑指 Offer II 020. 回文子字符串的个数 * 动态规划 & 中心扩展双指针
给定一个字符串 s ，请计算这个字符串中有多少个回文子字符串。
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

示例 1：

输入：s = "abc"
输出：3
解释：三个回文子串: "a", "b", "c"
```c++
class Solution {
public:
    int countSubstrings(string s) {

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
public:
    Node* flatten(Node* head) {
        
    }
};
```
#### 剑指 Offer II 029. 排序的循环链表
给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素 insertVal ，使这个列表仍然是循环升序的。
给定的可以是这个列表中任意一个顶点的指针，并不一定是这个列表中最小元素的指针。
如果有多个满足条件的插入位置，可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。
如果列表为空（给定的节点是 null），需要创建一个循环有序列表并返回这个节点。否则。请返回原先给定的节点。
我这里区分了几种情况，分别进行处理：

若链表为空，则直接创建节点，自己的next指向到自己；
若链表只有1个节点，则该放在该节点的后面即可；（其实这个可以去掉，在第3、4步骤里也可以处理）；
循环查找插入的位置，若大于等于当前节点的值，且小于等于下一个节点的值，则插入，然后返回；插入的位置没有区别，我们找到第一个符合条件的就行；（按照那个匹配条件可能找不到插入的位置，这里也存储下最大值的那个节点，方便在第4个步骤中使用）；
若循环中没有找到对应的位置，说明该值可能更小或者更大，插入到链表的最大值和最小值中间即可；
C++代码如下：
```c++


class Solution {
public:
    Node *insert(Node *head, int insertVal) {
        auto node = new Node(insertVal);
        if (head == nullptr) {
            // 若链表为空，则创建一个节点，自己的next指向到自己，形成循环链表
            node->next = node;
            return node;
        }
        if (head->next == head) {
            // 整个链表只有一个节点时，不分升序降序，直接插入到最后
            node->next = head->next;
            head->next = node;
            return head;
        }
        auto maxNode = head; // 数值最大的那个节点
        auto curNode = head; // 循环时使用
        do {
            if (insertVal >= curNode->val && insertVal <= curNode->next->val) {
                // 找到插入的位置
                node->next = curNode->next;
                curNode->next = node;
                return head;
            }
            if (curNode->val >= maxNode->val) {
                // 最大值可能存在连续多个，这里只保留最后的那个
                maxNode = curNode;
            }
            curNode = curNode->next;
        } while (curNode != head);

        // 若在上面的循环中没有找到插入的位置，
        // 说明insertVal可能比最大值还要大，或者比最小值还要小
        // 无论insertVal是更大还是更小，都放在maxNode的后面即可
        node->next = maxNode->next;
        maxNode->next = node;
        return head;
    }
};
```
```c++
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node *node = new Node(insertVal);
        if (head == nullptr) {
            node->next = node;
            return node;
        }
        if (head->next == head) {
            head->next = node;
            node->next = head;
            return head;
        }
        Node *curr = head, *next = head->next;
        while (next != head) {
            if (insertVal >= curr->val && insertVal <= next->val) {
                break;
            }
            if (curr->val > next->val) {
                if (insertVal > curr->val || insertVal < next->val) {
                    break;
                }
            }
            curr = curr->next;
            next = next->next;
        }
        curr->next = node;
        node->next = next;
        return head;
    }
};


```
```c++
class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node* node = new Node(insertVal);
        if (head == nullptr) {
            node->next = node;
            return node;
        }
        if (head->next == head) {
            head->next = node;
            node->next = head;
            return head;
        }
        Node* cur = head;
        Node* next = head->next;
        while(next != head) {
            if (insertVal >= cur->val && insertVal <= next->val) break;
            if (cur->val > next->val) {
                if(insertVal > cur->val || insertVal < next->val) break;
            }
            cur = cur->next;
            next = next->next;
        }
        cur->next = node;
        node->next = next;
        return head;
    }
};  
```
#### 剑指 Offer II 030. 插入、删除和随机访问都是 O(1) 的容器
设计一个支持在平均 时间复杂度 O(1) 下，执行以下操作的数据结构：
insert(val)：当元素 val 不存在时返回 true ，并向集合中插入该项，否则返回 false 。
remove(val)：当元素 val 存在时返回 true ，并从集合中移除该项，否则返回 false 。
getRandom：随机返回现有集合中的一项。每个元素应该有 相同的概率 被返回。
示例 :
```c++

class RandomizedSet {
    unordered_map<int, int> umap;
    vector<int> vec;
public:
    RandomizedSet() {

    }
    
    bool insert(int val) {
        if (umap.count(val) == 0) {
            umap[val] = vec.size();
            vec.push_back(val);
            return true;
        }
        return false;
    }
    
    bool remove(int val) {
        if (umap.count(val)) {
            int temp = vec[vec.size() - 1];
            umap[temp] = umap[val];
            swap(temp, vec[umap[val]]);
            umap.erase(val);
            vec.pop_back();
            return true;
        }
        return false;
    }
    
    int getRandom() {
        int index = rand() % (vec.size());
        return vec[index];
    }
};

```
#### 剑指 Offer II 031. 最近最少使用缓存
运用所掌握的数据结构，设计和实现一个  LRU (Least Recently Used，最近最少使用) 缓存机制 。
实现 LRUCache 类：
LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。
```c++
class LRUCache {
private:
    int cap;
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int,int>>::iterator> map;
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if(map.find(key) == map.end()) return -1;
        auto key_val = *map[key];
        cache.erase(map[key]);
        cache.push_front(key_val);
        map[key] = cache.begin();
        
        return key_val.second;
    }
    
    void put(int key, int value) {
        if (map.find(key) == map.end()) {
            if(cache.size() == cap) {
                map.erase(cache.back().first);
                cache.pop_back();
            }
        } else {
            cache.erase(map[key]);
        }
        cache.push_front({key, value});
        map[key] = cache.begin();
    }
};
```
#### 剑指 Offer II 033. 变位词组
给定一个字符串数组 strs ，将 变位词 组合在一起。 可以按任意顺序返回结果列表。
注意：若两个字符串中每个字符出现的次数都相同，则称它们互为变位词。

示例 1:

输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
```c++
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> map;
        for(auto &str : strs) {
            auto key = str;
            sort(key.begin(), key.end());
            map[key].push_back(str);
        }
        for(auto item = map.begin(); item != map.end(); item++) {
            result.push_back(item->second);
        }
        return result;
    }
};
```
#### 剑指 Offer II 035. 最小时间差
给定一个 24 小时制（小时:分钟 "HH:MM"）的时间列表，找出列表中任意两个时间的最小时间差并以分钟数表示。
示例 1：
输入：timePoints = ["23:59","00:00"]
输出：1
示例 2：

输入：timePoints = ["00:00","23:59","00:00"]
输出：0
提示：

2 <= timePoints <= 2 * 104
timePoints[i] 格式为 "HH:MM"
```c++
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        if (timePoints.size() > 24 * 60) return 0;
        vector<int> mins;
        for (auto t : timePoints)
            mins.push_back(stoi(t.substr(0, 2)) * 60 + stoi(t.substr(3)));
        sort(mins.begin(), mins.end());
        mins.push_back(mins[0] + 24 * 60);
        int res = 24 * 60;
        for (int i = 1; i < mins.size(); ++i)
            res = min(res, mins[i] - mins[i - 1]);
        return res;
    }
};
```
```c++
class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {

    }
};
```
#### 150. 逆波兰表达式求值
根据 逆波兰表示法，求表达式的值。
有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。
注意 两个整数之间的除法只保留整数部分。
可以保证给定的逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。


示例 1：

输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
```c
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                int num1 = st.top();
                st.pop();
                int num2 = st.top();
                st.pop();
                if (tokens[i] == "+") st.push(num2 + num1);
                if (tokens[i] == "-") st.push(num2 - num1);
                if (tokens[i] == "*") st.push(num2 * num1);
                if (tokens[i] == "/") st.push(num2 / num1);
            } else {
                st.push(stoi(tokens[i]));
            }
        }
        int result = st.top();
        st.pop(); // 把栈里最后一个元素弹出（其实不弹出也没事）
        return result;
    }
};


```
#### 剑指 Offer II 037. 小行星碰撞
给定一个整数数组 asteroids，表示在同一行的小行星。

对于数组中的每一个元素，其绝对值表示小行星的大小，正负表示小行星的移动方向（正表示向右移动，负表示向左移动）。每一颗小行星以相同的速度移动。

找出碰撞后剩下的所有小行星。碰撞规则：两个行星相互碰撞，较小的行星会爆炸。如果两颗行星大小相同，则两颗行星都会爆炸。两颗移动方向相同的行星，永远不会发生碰撞。
输入：asteroids = [5,10,-5]
输出：[5,10]
解释：10 和 -5 碰撞后只剩下 10 。 5 和 10 永远不会发生碰撞。
示例 2：

```c
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st;
        for (auto aster : asteroids) {
            bool alive = true;
            while (alive && aster < 0 && !st.empty() && st.back() > 0) {
                alive = st.back() < -aster; // aster 是否存在
                if (st.back() <= -aster) {  // 栈顶行星爆炸
                    st.pop_back();
                }
            }
            if (alive) {
                st.push_back(aster);
            }
        }
        return st;
    }
};

```
```c++
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> st;
        for(auto &aster : asteroids) {
            bool alive = true;
            while(alive && !st.empty() && st.back() > 0 && aster < 0) {
                alive = st.back() < -aster ? true : false;
                if(st.back() <= -aster) {
                    st.pop_back();
                }
            }
            if(alive) st.push_back(aster);
        }
        return st;
    }
};    
```
#### 剑指 Offer II 039. 直方图最大矩形面积
给定非负整数数组 heights ，数组中的数字用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
求在该柱状图中，能够勾勒出来的矩形的最大面积。

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {

    }
};
```
#### 剑指 Offer II 038. 每日温度
请根据每日 气温 列表 temperatures ，重新生成一个列表，要求其对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0 来代替。

示例 1:

输入: temperatures = [73,74,75,71,69,72,76,73]
输出: [1,1,4,2,1,1,0,0]
```c++

```
#### 剑指 Offer II 039. 直方图最大矩形面积
给定非负整数数组 heights ，数组中的数字用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int res = 0;
        st.push(0);
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        
        for(int i = 1; i < heights.size(); i++) {
            while(heights[i] < heights[st.top()]) {
                int h = heights[st.top()];
                st.pop();
                int w = i - st.top() - 1;
                res = max(res, w * h);
            }
            st.push(i);
        }
        return res;
    }
};    
```
#### 剑指 Offer II 040. 矩阵中最大的矩形
给定一个由 0 和 1 组成的矩阵 matrix ，找出只包含 1 的最大矩形，并返回其面积。

注意：此题 matrix 输入格式为一维 01 字符串数组。
```c++
class Solution {
public:
   // Helper from LC 84
        int largestRectangleArea(vector<int>& heights) {
            heights.push_back(0);
            int N = heights.size();
            stack<int> stk;
            int maxArea = 0;
            for (int i = 0; i < N; i++) {
                while (!stk.empty() && heights[i] < heights[stk.top()]) {
                    auto height = heights[stk.top()];
                    stk.pop();
                    int width = stk.empty() ? i : i - stk.top() - 1;
                    maxArea = max(maxArea, height * width);
                }
                
                stk.push(i);
            }  
    
            return maxArea;     
        }

    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() or matrix[0].empty()) {
            return 0;
        }
        int maxArea = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> heights(n, 0);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '0') {
                    heights[j] = 0;
                } else {
                    heights[j] += 1;
                }
            }
            maxArea = max(maxArea, largestRectangleArea(heights));
        }

        return maxArea;
    }
};


```
````c++
class Solution {
public:
    int largest(vector<int> heights) { // 不要传引用
        stack<int> st;
        int res = 0;
        st.push(0);
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        
        for(int i = 1; i < heights.size(); i++) {
            while(heights[i] < heights[st.top()]) {
                int h = heights[st.top()];
                st.pop();
                int w = i - st.top() - 1;
                res = max(res, w * h);
            }
            st.push(i);
        }
        return res;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty()) return 0;
        int res = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> heights(n, 0);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if (matrix[i][j] == '0') heights[j] = 0;
                else heights[j]++;
            }
            res = max(res, largest(heights));
        }
        return res;
    }
};
````
#### 剑指 Offer II 041. 滑动窗口的平均值
给定一个整数数据流和一个窗口大小，根据该滑动窗口的大小，计算滑动窗口里所有数字的平均值。
实现 MovingAverage 类：
MovingAverage(int size) 用窗口大小 size 初始化对象。
double next(int val) 成员函数 next 每次调用的时候都会往滑动窗口增加一个整数，请计算并返回数据流中最后 size 个值的移动平均值，即滑动窗口里所有数字的平均值。

示例：

输入：
inputs = ["MovingAverage", "next", "next", "next", "next"]
inputs = [[3], [1], [10], [3], [5]]
输出：
[null, 1.0, 5.5, 4.66667, 6.0]

解释：
MovingAverage movingAverage = new MovingAverage(3);
movingAverage.next(1); // 返回 1.0 = 1 / 1
movingAverage.next(10); // 返回 5.5 = (1 + 10) / 2
movingAverage.next(3); // 返回 4.66667 = (1 + 10 + 3) / 3
movingAverage.next(5); // 返回 6.0 = (10 + 3 + 5) / 3
```c++
class MovingAverage {
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {

    }
    
    double next(int val) {

    }
};

```
#### 剑指 Offer II 042. 最近请求次数
写一个 RecentCounter 类来计算特定时间范围内最近的请求。
请实现 RecentCounter 类：
RecentCounter() 初始化计数器，请求数为 0 。
int ping(int t) 在时间 t 添加一个新请求，其中 t 表示以毫秒为单位的某个时间，并返回过去 3000 毫秒内发生的所有请求数（包括新请求）。确切地说，返回在 [t-3000, t] 内发生的请求数。
保证 每次对 ping 的调用都使用比之前更大的 t 值。

示例：

输入：
inputs = ["RecentCounter", "ping", "ping", "ping", "ping"]
inputs = [[], [1], [100], [3001], [3002]]
输出：
[null, 1, 2, 3, 3]

解释：
RecentCounter recentCounter = new RecentCounter();
recentCounter.ping(1);     // requests = [1]，范围是 [-2999,1]，返回 1
recentCounter.ping(100);   // requests = [1, 100]，范围是 [-2900,100]，返回 2
recentCounter.ping(3001);  // requests = [1, 100, 3001]，范围是 [1,3001]，返回 3
recentCounter.ping(3002);  // requests = [1, 100, 3001, 3002]，范围是 [2,3002]，返回 3
```c++
class RecentCounter {
public:
    RecentCounter() {

    }
    
    int ping(int t) {

    }
};

```

#### 剑指 Offer II 043. 往完全二叉树添加节点
完全二叉树是每一层（除最后一层外）都是完全填充（即，节点数达到最大，第 n 层有 2n-1 个节点）的，并且所有的节点都尽可能地集中在左侧。
设计一个用完全二叉树初始化的数据结构 CBTInserter，它支持以下几种操作：
CBTInserter(TreeNode root) 使用根节点为 root 的给定树初始化该数据结构；
CBTInserter.insert(int v)  向树中插入一个新节点，节点类型为 TreeNode，值为 v 。使树保持完全二叉树的状态，并返回插入的新节点的父节点的值；
CBTInserter.get_root() 将返回树的根节点。
```c++
class CBTInserter {
    vector<TreeNode*> vec;
public:
    CBTInserter(TreeNode* root) {
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty()) {
            TreeNode* node = que.front();
            que.pop();
            vec.push_back(node);
            if(node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    
    int insert(int v) {
        TreeNode* thisNode = new TreeNode(v);
        vec.push_back(thisNode);
        int n = vec.size();
        TreeNode* father = vec[n / 2 - 1];
        if (n % 2) {
            father->right = thisNode;
        } else father->left = thisNode;
        return father->val;
    }
    
    TreeNode* get_root() {
        return vec[0];
    }
};
```
#### 剑指 Offer II 044. 二叉树每层的最大值
给定一棵二叉树的根节点 root ，请找出该二叉树中每一层的最大值。

示例1：
输入: root = [1,3,2,5,3,null,9]
输出: [1,3,9]
解释:
1
/ \
3   2
/ \   \  
5   3   9
```c++
class Solution {
public:
    vector<int> largestValues(TreeNode* root) {
        queue<TreeNode*> que;
        vector<int> result;
        if(root != nullptr) que.push(root);
        while(!que.empty()) {
            int size = que.size();
            int maxVal = INT_MIN;
            for(int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                maxVal = max(maxVal, node->val);
                if(node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
            result.push_back(maxVal);
        }
        return result;
    }
};
```
#### 剑指 Offer II 045. 二叉树最底层最左边的值
给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。

假设二叉树中至少有一个节点。
```c++
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode*> que;
        que.push(root);
        int bottomLeft = 0;
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; ++i) {
                TreeNode* node = que.front();
                que.pop();
                if (i == 0) {
                    bottomLeft = node->val;
                }
                if (node->left != nullptr) {
                    que.push(node->left);
                }
                if (node->right != nullptr) {
                    que.push(node->right);
                }
            }
        }    
        return bottomLeft;   
    }
};
```
```c++
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if (root == nullptr) return 0;
        queue<TreeNode*> que;
        int res = 0;
        if(root) que.push(root);
        while(!que.empty()) {
            int size = que.size();
            for(int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (i == 0) res = node->val;
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
        }
        return res;
    }
};
```
#### 剑指 Offer II 046. 二叉树的右侧视图
给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
```c++
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        queue<TreeNode*> que;
        vector<int> result;
        if(root != nullptr) que.push(root);
        while(!que.empty()) {
            int size = que.size();
           
            for(int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if(i == size - 1) result.push_back(node->val);
               
                if(node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
         
        }
        return result;
    }
};
```

#### 剑指 Offer II 047. 二叉树剪枝
给定一个二叉树 根节点 root ，树的每个节点的值要么是 0，要么是 1。请剪除该二叉树中所有节点的值为 0 的子树。
节点 node 的子树为 node 本身，以及所有 node 的后代。
```c++
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if(root == nullptr) return nullptr;

        root->left = pruneTree(root->left);
        root->right = pruneTree(root->right);
        if(root->val == 0 && root->left == nullptr && root->right == nullptr) return nullptr;

        return root;
    }
};
```
#### 剑指 Offer II 048. 序列化与反序列化二叉树
序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
```c++
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        
    }
};
```
#### 剑指 Offer II 049. 从根节点到叶节点的路径数字之和
给定一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。

每条从根节点到叶节点的路径都代表一个数字：

例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
计算从根节点到叶节点生成的 所有数字之和 。

叶节点 是指没有子节点的节点。
```c++
class Solution {
    int result;
    vector<int> path;
    int vecortToInt(vector<int>& vec) {
        int sum = 0;
        for(int i = 0; i < vec.size(); i++) {
            sum = sum * 10 + vec[i];
        } 
        return sum;
    }
    void traverse(TreeNode* cur) {
        if(!cur->left && !cur->right) {
            result += vecortToInt(path);
            return;
        }
        if(cur->left) {
            path.push_back(cur->left->val);
            traverse(cur->left);
            path.pop_back();
        }
        if(cur->right) {
            path.push_back(cur->right->val);
            traverse(cur->right);
            path.pop_back();
        }
        return ;
    }
public:
    int sumNumbers(TreeNode* root) {
        path.clear();
        if(root == nullptr) return 0;
        path.push_back(root->val);
        traverse(root);
        return result;
    }
};
```
#### 剑指 Offer II 050. 向下的路径节点之和
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。
路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
```c++
 */
class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
    
    }
};
```
29. 两数相除
    给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 dividend 除以除数 divisor 得到的商。

整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2

#### 316. 去除重复字母
给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。



示例 1：

输入：s = "bcabc"


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
#### 862. 和至少为 K 的最短子数组
给你一个整数数组 nums 和一个整数 k ，找出 nums 中和至少为 k 的 最短非空子数组 ，并返回该子数组的长度。如果不存在这样的 子数组 ，返回 -1 。

子数组 是数组中 连续 的一部分。

#### 303. 区域和检索 - 数组不可变
给定一个整数数组  nums，处理以下类型的多个查询:

计算索引 left 和 right （包含 left 和 right）之间的 nums 元素的 和 ，其中 left <= right
实现 NumArray 类：

NumArray(int[] nums) 使用数组 nums 初始化对象
int sumRange(int i, int j) 返回数组 nums 中索引 left 和 right 之间的元素的 总和 ，包含 left 和 right 两点（也就是 nums[left] + nums[left + 1] + ... + nums[right] )


#### 面试题 04.02. 最小高度树
给定一个有序整数数组，元素各不相同且按升序排列，编写一个算法，创建一棵高度最小的二叉搜索树。

示例:
给定有序数组: [-10,-3,0,5,9],

一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：

          0 
         / \ 
       -3   9 
       /   / 
     -10  5 

#### 85. 最大矩形
给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。

 