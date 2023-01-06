# LeetCode 4 寻找两个有序数组的中位数

## 1. 题目 
![题目链接](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/)

给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。

请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。

示例 1:

```
nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0
```

示例 2:

```
nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5
```

## 2. 思路
### 2.1 思路1
因为两个数组都是排好序的，所以第一想到的思路是将两个排好序的数组先做一个合并，然后对合并后的数组求中位数。

## 3.代码实现

### 3.1 思路1
```
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if(nums1.empty())
        {
            return GetVecMedium(nums2);
        }
        if(nums2.empty())
        {
            return GetVecMedium(nums1);
        }
        int index1 = 0;
        int index2 = 0;
        std::vector<int> resultVec;
        while(index1 < nums1.size() && index2 < nums2.size())
        {
            if(nums1[index1] <= nums2[index2])
            {
                resultVec.push_back(nums1[index1]);
                index1++;
            }
            else
            {
                resultVec.push_back(nums2[index2]);
                index2++;
            }
        }

        while(index1 < nums1.size())
        {
            resultVec.push_back(nums1[index1]);
            index1++;
        }

        while(index2 < nums2.size())
        {
            resultVec.push_back(nums2[index2]);
            index2++;
        }
        return GetVecMedium(resultVec);
    }

    double GetVecMedium(std::vector<int>& curVec)
    {
        int nCount = curVec.size();
        if(nCount > 0)
        {
            if(nCount%2!=0)
            {
                return double(curVec[nCount/2]);
            }
            else
            {
                return double(curVec[nCount/2]+curVec[(nCount-1)/2])/2;
            }
        }
        return 0.0;
    }
};
```