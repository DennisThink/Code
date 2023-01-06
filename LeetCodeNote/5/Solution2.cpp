#include <iostream>
#include <string>
#include <vector>
using namespace std;

//子串暴力法，时间太长，无法通过
class Solution
{
  public:
    string longestPalindrome(string s)
    {
        std::string strResult;
        for(std::size_t index = 0 ; index < s.length() ;index++)
        {
            for(std::size_t subIndex = index;subIndex < s.length();subIndex++)
            {
                //std::string strSub = s.substr(index,subIndex-index);
                if(isPalindrome(s,index,subIndex))
                {
                    if(subIndex - index >= strResult.length())
                    {
                        strResult = s.substr(index,subIndex-index+1);
                    }
                }
            }
        }
        return strResult;
    }

  private:
    bool isPalindrome(const std::string& str,std::size_t leftIndex,std::size_t rightIndex)
    {
        if(leftIndex == rightIndex)
        {
            return true;
        }
        while(leftIndex <= rightIndex)
        {
            if(str[leftIndex] == str[rightIndex])
            {
                leftIndex++;
                rightIndex--;
            }
            else
            {
                return false;
            }
        }
        if(leftIndex > rightIndex)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main(int argc, char *argv[])
{
    Solution solu;
    std::cout << solu.longestPalindrome("babad") << std::endl;
    std::cout << solu.longestPalindrome("cbbd") << std::endl;
    std::cout << solu.longestPalindrome("a") << std::endl;
    return 0;
}