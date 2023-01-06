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

        int nums1LeftIndex = 0;
        int nums1RightIndex = nums1.size()-1;

        int nums2LeftIndex = 0;
        int nums2RightIndex = nums2.size()-1;
        
        int nNum1OperaCount = 0;
        int nNum2OperaCount = 0;

        std::cout<<__LINE__<<std::endl;
        while( nums1LeftIndex <= nums1RightIndex && nums2LeftIndex <= nums2RightIndex)
        {
            if(nums1[nums1LeftIndex] <= nums2[nums2LeftIndex])
            {
                nums1LeftIndex+=1;
                nNum1OperaCount+=1;
                std::cout<<__LINE__<<std::endl;
            }
            else
            {
                nums2LeftIndex+=1;
                nNum2OperaCount+=1;
                std::cout<<__LINE__<<std::endl;
            }

            if(nums1[nums1RightIndex] >= nums2[nums2RightIndex])
            {
                nums1RightIndex-=1;
                nNum1OperaCount+=1;
                std::cout<<__LINE__<<std::endl;
            }
            else
            {
                nums2RightIndex-=1;
                nNum2OperaCount+=1;
                std::cout<<__LINE__<<std::endl;
            }
        }

        if(nums1LeftIndex > nums1RightIndex)
        {
            std::cout<<"Num1 Finished:"<<std::endl;
        }
        else
        {
            std::cout<<"Num1 Not Finished:"<<std::endl;
        }

        if(nums2LeftIndex > nums2RightIndex)
        {
            std::cout<<"Num2 Finished:"<<std::endl;
        }
        else
        {
            std::cout<<"Num2 Not Finished:"<<std::endl;
        }
        
        int nSum2 = nums2LeftIndex+nums2RightIndex;
        int nSum1 = nums1LeftIndex+nums1RightIndex;
        std::cout<<"COUNT:  "<<nNum1OperaCount<<"   "<<nNum2OperaCount<<std::endl;
        std::cout<<"SUM:  "<<nSum1<<"  "<<nSum2<<std::endl;
        //第一个遍历完了
        if(nNum1OperaCount == nums1.size())
        {
            //第二个也遍历完了
            if( nNum2OperaCount == nums2.size())
            {
                //assert(nums1.size()%2==1);
                //assert(nums2.size()%2==1);
                return double(nums1[(nums1.size()-1)/2]+nums2[(nums2.size()-1)/2])/2;
            }
            else 
            {
                if(nSum2%2 != 0)
                {
                    return double(nums2[nSum2/2]+nums2[nSum2/2+1])/2;
                }
                else
                {
                    return double(nums2[nSum2/2]);
                }
            }
        }
        else
        {
            if(nSum1%2 != 0)
            {
                return double(nums1[nSum1/2]+nums1[nSum1/2+1])/2;
            }
            else
            {
                return double(nums1[nSum1/2]);
            }
        }
        std::cout<<nums1LeftIndex<<"  "<<nums1RightIndex<<std::endl;
        std::cout<<nums2LeftIndex<<"  "<<nums2RightIndex<<std::endl;
        std::cout<<nNum1OperaCount<<"  "<<nNum2OperaCount<<std::endl;
        std::cout<<"Here"<<std::endl;
        return 0.0;
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
        std::cout<<"Media: "<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={1,2};
        std::vector<int> v2={3,4};
        Solution solu;
        std::cout<<"Media: "<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={1};
        std::vector<int> v2={};
        Solution solu;
        std::cout<<"Media: "<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={3};
        std::vector<int> v2={-2,-1};
        Solution solu;
        std::cout<<"Media: "<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={2,3,4};
        std::vector<int> v2={1};
        Solution solu;
        std::cout<<"Media: "<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    {
        std::vector<int> v1={2};
        std::vector<int> v2={1,3,4};
        Solution solu;
        std::cout<<"Media: "<<solu.findMedianSortedArrays(v1,v2)<<std::endl;
    }
    return 0;
}