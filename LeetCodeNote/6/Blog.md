
# LeetCode 6 Z 字形变换

## 1. 题目
[题目链接](https://leetcode-cn.com/problems/zigzag-conversion/)

将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

```
L   C   I   R
E T O E S I I G
E   D   H   N
```

之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
示例 1:

输入: s = "LEETCODEISHIRING", numRows = 3
输出: "LCIRETOESIIGEDHN"
示例 2:

输入: s = "LEETCODEISHIRING", numRows = 4
输出: "LDREOEIIECIHNTSG"
解释:

```
L     D     R
E   O E   I I
E C   I H   N
T     S     G
```

## 2.思路
### 2.1 思路1

首先对 
#### 2.1.1 观察1
> 比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如
>```
>0,     4,    8,     12     (0,{4}) 4=2*3-2
>1, [3],5,[7],9,[11],13 15  (1,3,{4})
>2,     6,    10,    14,    (2,{4})
>```

进行分析,经过分析，我们将每一行的数据分组，可以分析出以下几个结论
1. 当行数为3的时候，分组的间隔为4
2. 列的起始，分别为(0,1,3,2)

#### 2.1.2 观察2


观察行数为**4**的分组
```
0,     6,      12, (0,{6}) 6=2*[4]-2
1,  5, 7,  ,11,13, (1,5,{6})
2,4,   8,10,   14, (2,4,{6})
3,     9,      15, (3,{6})
```
可以得出的结论
1. 当行数为4的时候，间隔为6.
2. 列的起始分别为(0,1,5,2,4,3,)
   
#### 2.1.3 观察3

观察行数为**5**的分组
```
0,       8,         16, (0,{8}) 8=2*[5]-2
1,    7, 9,      15,17, (1,7,{8})
2,  6,   10,  14,   18, (2,6,{8})
3,5      11,13      19, (3,5,{8})
4,       12,            (4,{8})
```

可以得出结论:
1. 行数为5的时候，间隔为8
2. 列的起始为值分别为(0,1,7,2,6,3,5,4)

思路总结：
1. 经过分析和总结，间隔=2×行数-2。因为每列的元素个数为行数，斜线的元素个数也为行数。每列和斜线有一个元素重合，而斜线的最后一个元素，又恰好是第一行的开始元素，所以刚好差2。
2. 每行的开始索引为间隔减去每行的第一个元素的索引值。
3. 有两个开始索引的位置只出现在中间的行，所以对首行和末行分别处理。


## 3.代码实现
### 3.1 思路1的代码实现

```cpp
class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows <= 1)
        {
            return s;
        }
        //计算间隔
        const int nStep = 2*numRows-2;
        std::string strResult;
        //对每一行进行处理
        for(int index = 0; index < numRows ; index++)
        {
            int nFirst = index;
            int nSecond = nStep-nFirst;
            //第一行或者最后一行
            if(nFirst == 0 || nFirst == numRows-1)
            {
                while(nFirst < s.length())
                {
                    strResult+=s[nFirst];
                    nFirst+=nStep;
                }
            }
            else
            {
                //处理中间的行
                while(nSecond < s.length())
                {
                    //第一个开始索引
                    if(nFirst < s.length())
                    {
                        strResult+=s[nFirst];
                        nFirst+=nStep;
                    }
                    //第二个开始索引
                    if(nSecond < s.length())
                    {
                        strResult+=s[nSecond];
                        nSecond+=nStep;
                    }
                }
                while(nFirst < s.length())
                {
                    strResult+=s[nFirst];
                    nFirst+=nStep;
                }
            }
        }
        return strResult;
    }
};
```