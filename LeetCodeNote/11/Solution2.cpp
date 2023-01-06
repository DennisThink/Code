#include <iostream>
#include <vector>
using std::vector;
class Solution {
public:
    int maxArea(vector<int>& height) {
        int leftIndex = 0;
        int rightIndex = height.size()-1;
        int nMax = 0;
        while(leftIndex<rightIndex)
        {
            int nCur = getArea(height,leftIndex,rightIndex);
            if(nCur > nMax)
            {
                nMax = nCur;
            }
            
            if(height[leftIndex] <= height[rightIndex])
            {
                int nCurValue = height[leftIndex];
                while(leftIndex < rightIndex && height[leftIndex] <= nCurValue)
                {
                    leftIndex++;
                }
            }
            else
            {
                int nCurValue = height[rightIndex];
                while(leftIndex < rightIndex && height[rightIndex] <= nCurValue)
                {
                    rightIndex--;
                }
            }
        }
        return nMax;
    }

private:
    int getArea(const vector<int>& height,std::size_t leftIndex,std::size_t rightIndex)
    {
        int nWidth = rightIndex-leftIndex;
        int nHeight = std::min(height[leftIndex],height[rightIndex]);
        return nWidth*nHeight;
    }
};


class Solution2 {
public:
    int maxArea(vector<int>& height) {
        int leftIndex = 0;
        int rightIndex = height.size()-1;
        int nMax = 0;
        while(leftIndex<rightIndex)
        {
            int nCur = getArea(height,leftIndex,rightIndex);
            if(nCur > nMax)
            {
                nMax = nCur;
            }
            
            if(height[leftIndex] <= height[rightIndex])
            {
                leftIndex++;
            }
            else
            {
                rightIndex--;
            }
        }
        return nMax;
    }

private:
    int getArea(const vector<int>& height,std::size_t leftIndex,std::size_t rightIndex)
    {
        int nWidth = rightIndex-leftIndex;
        int nHeight = std::min(height[leftIndex],height[rightIndex]);
        return nWidth*nHeight;
    }
};
int main(int argc,char * argv[])
{
   {
       vector<int> curVec={1,8,6,2,5,4,8,3,7};
Solution solu;
    std::cout<<solu.maxArea(curVec)<<std::endl;
   } 
    return 0;
}