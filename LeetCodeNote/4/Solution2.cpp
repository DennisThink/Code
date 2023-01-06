#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;
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


int main(int argc,char * argv[])
{
   {
        std::vector<int> v1={1,3};
        std::vector<int> v2={2};
        Solution solu;
        std::cout<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={1,2};
        std::vector<int> v2={3,4};
        Solution solu;
        std::cout<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={1};
        std::vector<int> v2={};
        Solution solu;
        std::cout<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={3};
        std::vector<int> v2={-2,-1};
        Solution solu;
        std::cout<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={2,3,4};
        std::vector<int> v2={1};
        Solution solu;
        std::cout<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={2};
        std::vector<int> v2={1,3,4};
        Solution solu;
        std::cout<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    return 0;
}