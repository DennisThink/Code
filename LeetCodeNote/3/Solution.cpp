#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int nResult = 0;
        std::string strFind;
        int nLen = s.length();
        for(int index = 0; index < nLen; index++)
        {
            char chCur = s[index];
            auto findIndex = strFind.find(chCur);
            if(findIndex == string::npos)
            {
                strFind += chCur;
                if(strFind.length() > nResult)
                {
                    nResult = strFind.length();
                }
            }
            else
            {
                /* code */
                strFind = strFind.substr(findIndex+1,strFind.length()-findIndex);
                strFind += chCur;
            }
        }
        return nResult;        
    }
};


int main(int argc,char * argv[])
{
    Solution solu;
    {
        std::string str1="abcabcbb";
        std::cout<<solu.lengthOfLongestSubstring(str1)<<std::endl;
    }
    {
        std::string str1="bbbbbbb";
        std::cout<<solu.lengthOfLongestSubstring(str1)<<std::endl;
    }
      {
        std::string str1="pwwkew";
        std::cout<<solu.lengthOfLongestSubstring(str1)<<std::endl;
    }
    return 0;
}