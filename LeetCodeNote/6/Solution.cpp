
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows <= 1)
        {
            return s;
        }
        const int nStep = 2*numRows-2;
        std::string strResult;
        for(int index = 0; index < numRows ; index++)
        {
            int nFirst = index;
            int nSecond = nStep-nFirst;
            if(nFirst == 0 || nFirst == numRows-1)
            {
                while(nFirst < s.length())
                {
                    strResult+=s[nFirst];
                    nFirst+=nStep;
                }
            }
            else
            {
                while(nSecond < s.length())
                {
                    if(nFirst < s.length())
                    {
                        strResult+=s[nFirst];
                        nFirst+=nStep;
                    }
                    if(nSecond < s.length())
                    {
                        strResult+=s[nSecond];
                        nSecond+=nStep;
                    }
                }
                while(nFirst < s.length())
                {
                    strResult+=s[nFirst];
                    nFirst+=nStep;
                }
            }
        }
        return strResult;
    }
};

int main(int argc,char * argv[])
{
    Solution solu;
    std::string strInput = "LEETCODEISHIRING";
    std::string strOutput="LCIRETOESIIGEDHN";//3
    std::string strOutput1="LDREOEIIECIHNTSG";//4
    if(strOutput == solu.convert(strInput,3))
    {
        std::cout<<"Good"<<std::endl;
    }
    else
    {
        std::cout<<"bad"<<std::endl;
    }

    if(strOutput1 == solu.convert(strInput,4))
    {
        std::cout<<"Good"<<std::endl;
    }
    else
    {
        std::cout<<"bad"<<std::endl;
    }
    return 0;
}