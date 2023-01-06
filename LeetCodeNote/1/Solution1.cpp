/**
 * @file Solution1.cpp
 * @author your name (dennismi1024@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-02
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <vector>
#include <iostream>
using namespace std;
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

int main(int argc, char *argv[])
{
    {
        std::vector<int> vec1 = {2, 7, 11, 15};
        Solution solu;
        auto result = solu.twoSum(vec1, 9);
        for (const auto &item : result)
        {
            std::cout << item << " ";
        }
        std::cout << endl;
    }
    {
        std::vector<int> vec1 = {2, 7, 7, 15};
        Solution solu;
        auto result = solu.twoSum(vec1, 14);
        for (const auto &item : result)
        {
            std::cout << item << " ";
        }
        std::cout << endl;
    }
    return 0;
}