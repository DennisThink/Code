#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
       int nResult = 0;
        const int defaultValue = -1;
        int indexArray[63];
        for(int i = 0 ; i < 63; i ++)
        {
            indexArray[i]=defaultValue;
        }
        std::size_t nCount = s.length();
        int nCurLength = 0;
        for (std::size_t i = 0; i < nCount; i++)
        {
            std::size_t index = countIndex(s[i]);
            if (indexArray[index] == defaultValue)
            {
                indexArray[index] = i;
                ++nCurLength;
                nResult = std::max(nResult, nCurLength);
            }
            else
            {
                nResult = std::max(nResult, nCurLength);
                std::size_t nStartIndex = indexArray[index];
                nCurLength = i - nStartIndex;
                for (std::size_t j = 0; j < 63; j++)
                {
                    if (indexArray[j] < nStartIndex)
                    {
                        indexArray[j] = defaultValue;
                    }
                }
                indexArray[index] = i;
            }
        }
        nResult = std::max(nResult, nCurLength);
        return nResult;
    }

    std::size_t countIndex(char ch)
    {
        if('0'<=ch && ch <= '9')
        {
            return ch-'0';
        }
        if('A' <=ch && ch <='z')
        {
            return 10+ch-'A';
        }
        return 62;
    }
};

int main(int argc, char *argv[])
{
    Solution solu;
    {
        std::string str1 = "abcabcbb";
        std::cout << solu.lengthOfLongestSubstring(str1) << std::endl;
    }
    {
        std::string str1 = "bbbbbbb";
        std::cout << solu.lengthOfLongestSubstring(str1) << std::endl;
    }
    {
        std::string str1 = "pwwkew";
        std::cout << solu.lengthOfLongestSubstring(str1) << std::endl;
    }
    {
        std::string str1 = " ";
        std::cout << solu.lengthOfLongestSubstring(str1) << std::endl;
    }
    {
        std::string str1 = "au";
        std::cout << solu.lengthOfLongestSubstring(str1) << std::endl;
    }
    return 0;
}