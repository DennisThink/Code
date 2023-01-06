# LeetCode1 两数之和

## 1.题目

[原文链接](https://leetcode-cn.com/problems/two-sum/)

给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:

>
>给定 nums = [2, 7, 11, 15], target = 9   
>
> 因为 nums[0] + nums[1] = 2 + 7 = 9     
> 所以返回 [0, 1]

## 2.题目分析

### 2.1 思路1
第一个能够想到的思路，是做一个二重循环，对数组中的元素进行遍历，检查任意两个元素是否可以计算出目标结果。

### 2.2 思路2
对于每个值，计算其对应的差(target-curvalue)，然后看这个差是不是在该数组中,使用map来查找。

## 3.代码
### 3.1 思路1的代码
```cpp
class Solution
{
  public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        int nCount = nums.size();
        for (int outIndex = 0; outIndex < nCount; outIndex++)
        {
            for (int inIndex = outIndex + 1; inIndex < nCount; inIndex++)
            {
                if (nums[outIndex] + nums[inIndex] == target)
                {
                    return std::vector<int>{outIndex, inIndex};
                }
            }
        }
        return std::vector<int>();
    }
};
```

### 3.2 思路2的代码
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        std::map<int,int> valueIndexMap;
        int nCount = nums.size();
        for(int index = 0;index < nCount ; index++)
        {
            int otherValue = target - nums[index];
            auto findIndex = valueIndexMap.find(otherValue);
            if(findIndex != valueIndexMap.end())
            {
                return std::vector<int>{findIndex->second,index};
            }
            else
            {
                valueIndexMap.insert(std::pair<int,int>(nums[index],index));
            }
        }
        return std::vector<int>{};
    }
};
```

完整的代码请参考:https://github.com/DennisThink/LeetCodeNote
`