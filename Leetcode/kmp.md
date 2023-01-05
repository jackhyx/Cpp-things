
### 28. 找出字符串中第一个匹配项的下标
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果 needle 不是 haystack 的一部分，则返回  -1 。
示例 1：
输入：haystack = "sadbutsad", needle = "sad"
输出：0
解释："sad" 在下标 0 和 6 处匹配。
第一个匹配项的下标是 0 ，所以返回 0 。
```c++
class Solution {
    void getNext(vector<int>& next, const string& s) {
        next[0] = 0;
        for(int i = 1, j = 0; i < s.size(); i++) {
            while(j > 0 && s[i] != s[j]) {
                j = next[j - 1];
            }
            if(s[i] == s[j]) j++;
            next[i] = j;
        }
    }
public:
    int strStr(string haystack, string needle) {
        int m = haystack.size(), n = needle.size();
        if(n == 0) return 0;
        vector<int> next(n);
        getNext(next, needle);
        for(int i = 0, j = 0; i < m; i++) {
            while(j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            if(haystack[i] == needle[j]) j++;
            if(j == n) return i - n + 1;
        }
        return -1;
    }
};
```

459. 重复的子字符串
给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。
示例 1:
输入: s = "abab"
输出: true
解释: 可由子串 "ab" 重复两次构成。
```c++
class Solution {
    void getNext(vector<int>& next, const string& s) {
        next[0] = 0;
        for(int i = 1, j = 0; i < s.size(); i++) {
            while(j > 0 && s[i] != s[j]) {
                j = next[j - 1];
            }
            if(s[i] == s[j]) j++;
            next[i] = j;
        }
    }
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();
        vector<int> next(n);
        getNext(next, s);
        if(next[n - 1] != 0 && n % (n - next[n - 1]) == 0) return true;
        return false;
    }
};
```