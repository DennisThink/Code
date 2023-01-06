# LeetCode2 两数相加

## 1.题目

[原文链接](https://leetcode-cn.com/problems/add-two-numbers/))

给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。

如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。

您可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例：

输入：(2 -> 4 -> 3) + (5 -> 6 -> 4)
输出：7 -> 0 -> 8
原因：342 + 465 = 807

## 2.题目分析

题目的做法与我们小时候做加法列竖式是一样的思路，需要注意的地方是链表元素的顺序。

## 3.代码
### 3.1 思路1的代码
```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* l1R = l1;
        ListNode* l2R = l2;
        ListNode* pResult=new ListNode(0);
        ListNode* pNext = pResult;
        int nValue = 0;
        int nPos = 0;
        int nCarry = 0;
        while(l1R && l2R)
        {
            nValue = l1R->val+l2R->val+nCarry;
            nPos = nValue%10;
            nCarry = nValue/10;
            ListNode* pNew = new ListNode(nPos);
            
            pNext->next = pNew;
            pNew->next = nullptr;
            pNext = pNext->next;

            l1R = l1R->next;
            l2R = l2R->next;
        }
        
        while(l1R)
        {
            nValue = l1R->val+nCarry;
            nPos = nValue%10;
            nCarry = nValue/10;
            ListNode* pNew = new ListNode(nPos);
        
            pNext->next = pNew;
            pNew->next = nullptr;
            pNext = pNext->next;

            l1R = l1R->next;
        }

        while(l2R)
        {
            nValue = l2R->val+nCarry;
            nPos = nValue%10;
            nCarry = nValue/10;
            ListNode* pNew = new ListNode(nPos);
            
            pNext->next = pNew;
            pNew->next = nullptr;
            pNext = pNext->next;

            l2R = l2R->next;
        }

        if(nCarry > 0)
        {
            ListNode* pNew = new ListNode(nCarry);

            pNext->next = pNew;
            pNew->next = nullptr;
            pNext = pNext->next;
        }
        
        ListNode* pFree = pResult;
        pResult = pResult->next;
        delete pFree;
        
        return (pResult);
    }
}
```



完整的代码请参考:https://github.com/DennisThink/LeetCodeNote
