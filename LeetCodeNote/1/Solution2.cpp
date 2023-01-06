/**
 * @file Solution2.cpp
 * @author dennisthink (dennismi1024@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <vector>
#include <map>
#include <iostream>
using namespace std;
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

int main(int argc,char * argv[])
{
    std::vector<int> vec1 = {2,7,11,15};
    Solution solu;
    auto result = solu.twoSum(vec1,9);
    for(const auto& item:result)
    {   
        std::cout<<item<<" ";
    }
    std::cout<<endl;
    return 0;
}