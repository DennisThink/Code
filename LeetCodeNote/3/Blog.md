# LeetCode 3 无重复字符的最长子串

## 1. 题目
![题目链接](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)

给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

```
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
```

```
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
```

```
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```
    
## 2. 思路分析

### 2.1 思路1
经过分析，题目是寻找最长的无重复子串。 所以第一种思路是
1. 先找到所有的子串；
2. 对每个子串进行判断，是否有重复；
3. 如果没有重复，则计算长度，保留最大的；
4. 如果有重复，则跳过。

### 2.2 思路2
经过对 `思路1` 的分析，有很多的判断是重复的，比如对于从 [1,4]和[1，6]的子串判断过程中,[1,4]的范围内是重复判断了的。所以我们从左向右遍历，对已经遍历的字符进行记录，
1. 如果当前字符没有出现在已经遍历的字符中，将当前字符加入，计算并更新长度。
2. 如果当前字符已经出现在已经遍历的字符中，则将匹配位置以及其前面的字符删除，然后将当前的字符加入。
重复1,2两个步骤，直至所有字符遍历完成。

## 3. 代码呈现 

### 3.1 思路1
在LeetCode中国上，这个思路因为耗时太久，会无法通过测试。
```cpp
class Solution {
public:
    bool hasSameChar(const std::string& strValue,const int nStart,const int nEnd)
    {
        std::string strCheck;
        for(int i = nStart; i< nEnd ; i++)
        {
            if(string::npos != strCheck.find(strValue[i]))
            {
                return true;
            }
            else
            {
                strCheck+=strValue[i];
            }
        }
        return false;
    }
    int lengthOfLongestSubstring(string s) {
        int nResult = 0;
        std::string strFind;
        int nLen = s.length();
        for(int index = 0; index < nLen; index++)
        {
            for(int j = index+1; j <= nLen ; j++)
            {
                if(hasSameChar(s,index,j))
                {

                }
                else
                {
                    nResult = std::max(nResult,j-index);
                }
                
            }
        }
        return nResult;        
    }
};
```


### 3.2 思路2
```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int nResult = 0;
        std::string strFind;
        int nLen = s.length();
        for(int index = 0; index < nLen; index++)
        {
            char chCur = s[index];
            auto findIndex = strFind.find(chCur);
            if(findIndex == string::npos)
            {
                strFind += chCur;
                if(strFind.length() > nResult)
                {
                    nResult = strFind.length();
                }
            }
            else
            {
                /* code */
                strFind = strFind.substr(findIndex+1,strFind.length()-findIndex);
                strFind += chCur;
            }
        }
        return nResult;        
    }
};
```