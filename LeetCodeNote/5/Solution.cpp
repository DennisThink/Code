#include <iostream>
#include <string>
#include <vector>
using namespace std;

//中心扩展算法
class Solution
{
  public:
    string longestPalindrome(string s)
    {
        if (s.empty())
        {
            return "";
        }

        std::vector<std::string> allResult;
        std::string strResult;
        int nLeftIndex = 0;
        int nRightIndex = 0;
        int nResultLeft = 0;
        int nResultRight = 0;
        for (int index = 0; index < s.length(); index++)
        {
            //字符串的长度为奇数，且以s[index]为中心
            {
                nLeftIndex = index;
                nRightIndex = index;
                nResultLeft = -1;
                nResultRight = -1;
                while (nLeftIndex >= 0 && nRightIndex < s.length())
                {
                    if (s[nLeftIndex] == s[nRightIndex])
                    {
                        nResultLeft = nLeftIndex;
                        nResultRight = nRightIndex;

                        nLeftIndex--;
                        nRightIndex++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (-1 != nResultLeft && -1 != nResultRight)
                {
                    std::string strCur =
                        s.substr(nResultLeft, nResultRight - nResultLeft + 1);
                    if (strCur.length() >= strResult.length())
                    {
                        strResult = strCur;
                        allResult.push_back(strCur);
                    }
                }
            }
            //字符串的长度为偶数，且以(index+0.5)为中心
            {
                nLeftIndex = index;
                nRightIndex = index + 1;
                nResultLeft = -1;
                nResultRight = -1;
                while (nLeftIndex >= 0 && nRightIndex < s.length())
                {
                    if (s[nLeftIndex] == s[nRightIndex])
                    {
                        nResultLeft = nLeftIndex;
                        nResultRight = nRightIndex;

                        nLeftIndex--;
                        nRightIndex++;
                    }
                    else
                    {
                        break;
                    }
                }
                if (-1 != nResultLeft && -1 != nResultRight)
                {
                    std::string strCur =
                        s.substr(nResultLeft, nResultRight - nResultLeft + 1);
                    if (strCur.length() >= strResult.length())
                    {
                        strResult = strCur;
                        allResult.push_back(strCur);
                    }
                }
            }
        }
        return strResult;
    }
};

int main(int argc, char *argv[])
{
    Solution solu;
    std::cout << solu.longestPalindrome("babad") << std::endl;
    std::cout << solu.longestPalindrome("cbbd") << std::endl;
    return 0;
}