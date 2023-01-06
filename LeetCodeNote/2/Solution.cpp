/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
//g++ -O -g -fsanitize=address Solution.cpp

#include <iostream>
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //ListNode* l1R = ReverseList(l1);
        //ListNode* l2R = ReverseList(l2);
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
public:

    void PrintList(ListNode* pList)
    {
        std::cout<<std::endl;
        while(pList)
        {
            std::cout<<pList->val<<"->";
            pList=pList->next;
        }
        std::cout<<std::endl;
    }

    ListNode* StringToList(std::string value)
    {
        ListNode* pResult = new ListNode(0);
        ListNode* pNext = pResult;
        for(int index = 0 ; 
           index < value.length();
           index++)
        {
            ListNode* pNew = new ListNode(value[index]-'0');
            pNext->next = pNew;
            pNew->next  = nullptr;
            pNext = pNext->next;
        }
        
        ListNode* pFree = pResult;
        pResult = pResult->next;
        delete pFree;

        return pResult;
    }
    void FreeListNode(ListNode* pNew)
    {
        while(pNew)
        {
            ListNode* pFree = pNew;
            pNew=pNew->next;
            delete pFree;
        }
    }
};

int main(int argc,char * argv[])
{
    Solution solu;
    {
        std::string str1="18";
        std::string str2="0";
        ListNode* p1 = solu.StringToList(str1);
        solu.PrintList(p1);
        ListNode* p2 = solu.StringToList(str2);
        ListNode* pResult = solu.addTwoNumbers(p1,p2);
        solu.PrintList(pResult);  

        solu.FreeListNode(p1);
        solu.FreeListNode(p2);
        solu.FreeListNode(pResult);      
    }

    {
        std::string str1="243";
        std::string str2="564";
        ListNode* p1 = solu.StringToList(str1);
        solu.PrintList(p1);
        ListNode* p2 = solu.StringToList(str2);
        ListNode* pResult = solu.addTwoNumbers(p1,p2);
        
        solu.FreeListNode(p1);
        solu.FreeListNode(p2);
        
        solu.PrintList(pResult);
        solu.FreeListNode(pResult);  
    
        //ListNode* pR2 = solu.ReverseList(pResult);
        
    }
    return 0;
}