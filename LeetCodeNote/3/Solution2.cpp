#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool hasSameChar(const std::string& strValue,const int nStart,const int nEnd)
    {
        std::string strCheck;
        for(int i = nStart; i< nEnd ; i++)
        {
            if(string::npos != strCheck.find(strValue[i]))
            {
                return true;
            }
            else
            {
                strCheck+=strValue[i];
            }
        }
        return false;
    }
    int lengthOfLongestSubstring(string s) {
        int nResult = 0;
        std::string strFind;
        int nLen = s.length();
        for(int index = 0; index < nLen; index++)
        {
            for(int j = index+1; j <= nLen ; j++)
            {
                if(hasSameChar(s,index,j))
                {

                }
                else
                {
                    nResult = std::max(nResult,j-index);
                }
                
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
     {
        std::string str1=" ";
        std::cout<<solu.lengthOfLongestSubstring(str1)<<std::endl;
    }
    {
        std::string str1="au";
        std::cout<<solu.lengthOfLongestSubstring(str1)<<std::endl;
    }
    return 0;
}