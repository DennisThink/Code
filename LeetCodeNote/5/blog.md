# LeetCode 5 最长回文子串

## 1. 题目
[题目链接](https://leetcode-cn.com/problems/longest-palindromic-substring/submissions/)

给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。

示例 2：

输入: "cbbd"
输出: "bb"

    
## 2. 思路分析

### 2.1 思路1(暴力法)
暴力法，先确定所有的子串，然后对子串进行回文判断。
此方法是
1. 先求出子串的边界。
2. 再确定是否回文(从两边向中心判断)

### 2.2 思路2(中心扩展法)
经过分析，因为回文串是有中心的，那么我们可以
1. 先确定回文中心。
2. 向两边扩展，在扩展的过程中，判断是否为回文(从中心向两边判断)
3. 需要注意的是回文串的字符数可能为奇数或者偶数，需要分别处理。

## 3. 代码呈现 

### 3.1 思路1
这个方法的时间复杂度太高，在LeetCode上没有办法通过测试。
```cpp
//子串暴力法，时间太长，无法通过
class Solution
{
  public:
    string longestPalindrome(string s)
    {
        std::string strResult;
        for(std::size_t index = 0 ; index < s.length() ;index++)
        {
            for(std::size_t subIndex = index;subIndex < s.length();subIndex++)
            {
                //std::string strSub = s.substr(index,subIndex-index);
                if(isPalindrome(s,index,subIndex))
                {
                    if(subIndex - index >= strResult.length())
                    {
                        strResult = s.substr(index,subIndex-index+1);
                    }
                }
            }
        }
        return strResult;
    }

  private:
    bool isPalindrome(const std::string& str,std::size_t leftIndex,std::size_t rightIndex)
    {
        if(leftIndex == rightIndex)
        {
            return true;
        }
        while(leftIndex <= rightIndex)
        {
            if(str[leftIndex] == str[rightIndex])
            {
                leftIndex++;
                rightIndex--;
            }
            else
            {
                return false;
            }
        }
        if(leftIndex > rightIndex)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
```

### 3.2 思路2
```cpp
//中心扩展算法
class Solution
{
  public:
    string longestPalindrome(string s)
    {
        if (s.empty())
        {
            return "";
        }

        std::vector<std::string> allResult;
        std::string strResult;
        int nLeftIndex = 0;
        int nRightIndex = 0;
        int nResultLeft = 0;
        int nResultRight = 0;
        for (int index = 0; index < s.length(); index++)
        {
            //字符串的长度为奇数，且以s[index]为中心
            {
                nLeftIndex = index;
                nRightIndex = index;
                nResultLeft = -1;
                nResultRight = -1;
                while (nLeftIndex >= 0 && nRightIndex < s.length())
                {
                    if (s[nLeftIndex] == s[nRightIndex])
                    {
                        nResultLeft = nLeftIndex;
                        nResultRight = nRightIndex;

                        nLeftIndex--;
                        nRightIndex++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (-1 != nResultLeft && -1 != nResultRight)
                {
                    std::string strCur =
                        s.substr(nResultLeft, nResultRight - nResultLeft + 1);
                    if (strCur.length() >= strResult.length())
                    {
                        strResult = strCur;
                        allResult.push_back(strCur);
                    }
                }
            }
            //字符串的长度为偶数，且以(index+0.5)为中心
            {
                nLeftIndex = index;
                nRightIndex = index + 1;
                nResultLeft = -1;
                nResultRight = -1;
                while (nLeftIndex >= 0 && nRightIndex < s.length())
                {
                    if (s[nLeftIndex] == s[nRightIndex])
                    {
                        nResultLeft = nLeftIndex;
                        nResultRight = nRightIndex;

                        nLeftIndex--;
                        nRightIndex++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (-1 != nResultLeft && -1 != nResultRight)
                {
                    std::string strCur =
                        s.substr(nResultLeft, nResultRight - nResultLeft + 1);
                    if (strCur.length() >= strResult.length())
                    {
                        strResult = strCur;
                        allResult.push_back(strCur);
                    }
                }
            }
        }
        return strResult;
    }
};
```