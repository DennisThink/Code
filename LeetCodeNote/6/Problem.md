将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

```
L   C   I   R
E T O E S I I G
E   D   H   N
```

之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。
```
0,     4,    8,     12     (0,{4}) 4=2*3-2
1, [3],5,[7],9,[11],13 15  (1,3,{4})
2,     6,    10,    14,    (2,{4})
```
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


0,     6,      12, (0,{6}) 6=2*[4]-2
1,  5, 7,  ,11,13, (1,5,{6})
2,4,   8,10,   14, (2,4,{6})
3,     9,      15, (3,{6})


L       I    
E     E S     G
E   D   H   N
T O     I I
C       R

0,       8,         16, (0,{8}) 8=2*[5]-2
1,    7, 9,      15,17, (1,7,{8})
2,  6,   10,  14,   18, (2,6,{8})
3,5      11,13      19, (3,5,{8})
4,       12,            (4,{8})
```