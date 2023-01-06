#include <iostream>
#include <string>
#include <vector>
using std::string;
class Solution {
public:
    int romanToInt(string s) {
        std::vector<int> allValue;
        int oneSum=0;//所有1的和
        for(std::size_t i = 0 ; i < s.length() ; i++)
        {
            int nValue = getCharValue(s[i]);
            if(nValue == 1)
            {
                oneSum+=1;
            }
            else
            {
                if(oneSum != 0)
                {
                    allValue.push_back(oneSum);
                    oneSum=0;
                }
                allValue.push_back(nValue);
            }
        }
        if(oneSum != 0)
        {
            allValue.push_back(oneSum);
            oneSum=0;
        }

        int value = 0;
        for(std::size_t i = 0 ; i < allValue.size();)
        {
            if(i<allValue.size()-1)
            {
                if(allValue[i] < allValue[i+1])
                {
                    value -= allValue[i];
                    value += allValue[i+1];
                    i+=2;      
                }
                else
                {
                    value += allValue[i];
                    i++;
                }
            }
            else
            {
                value += allValue[i];
                i++;
            }
        }
        return value;
    }
private:
    int getCharValue(char ch){
        switch (ch)
        {
            case 'I':
                {
                    return 1;
                }
                break;
            case 'V':
                {
                    return 5;
                }break;
            case 'X':
                {
                    return 10;
                }break;
            case 'L':
                {
                    return 50;
                }break;
            case 'C':
                {
                    return 100;
                }break;
            case 'D':
                {
                    return 500;
                }break;
            case 'M':
                {
                    return 1000;
                }break;
            default:
                {
                    return 0;
                }break;
        }
    }
};

int main(int argc,char* argv[])
{
    Solution solu;
    {
        std::string str1="III";
        std::cout<<"STR:  "<<str1<<"  "<<solu.romanToInt(str1)<<std::endl;
    }
     {
        std::string str1="IV";
        std::cout<<"STR:  "<<str1<<"  "<<solu.romanToInt(str1)<<std::endl;
    }
     {
        std::string str1="IX";
        std::cout<<"STR:  "<<str1<<"  "<<solu.romanToInt(str1)<<std::endl;
    }
     {
        std::string str1="LVIII";
        std::cout<<"STR:  "<<str1<<"  "<<solu.romanToInt(str1)<<std::endl;
    }
     {
        std::string str1="MCMXCIV";
        std::cout<<"STR:  "<<str1<<"  "<<solu.romanToInt(str1)<<std::endl;
    }
    return 0;
}