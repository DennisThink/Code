#include <iostream>
#include <vector>
using std::vector;
class Solution {
public:
    int maxArea(vector<int>& height) {
        std::size_t heightCount = height.size();
        int nMax = 0;
        for(std::size_t index = 0; index < heightCount; index++)
        {
            for(std::size_t rightIndex = index+1; rightIndex < heightCount ; rightIndex++){
                int nCurArea =getArea(height,index,rightIndex) ;
                if( nCurArea > nMax){
                    nMax = nCurArea;
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

int main(int argc,char * argv[])
{
   {
       vector<int> curVec={1,8,6,2,5,4,8,3,7};
Solution solu;
    std::cout<<solu.maxArea(curVec)<<std::endl;
   } 
    return 0;
}