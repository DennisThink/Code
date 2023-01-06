
#include <vector>
#include <iostream>
#include <string>
using std::string;
using std::vector;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty())
        {
            return "";
        }
        if(strs.size() == 1)
        {
            return strs[0];
        }
        std::string strResult = strs[0];
        for(int index = 1 ; index < strs.size();index++)
        {
            strResult = CommonPrefix(strResult,strs[index]);
        }        
        return strResult;
    }

public:
    string CommonPrefix(const std::string strLeft,const std::string strRight){
        std::string strResult;
        int index = 0;
        while(index < strLeft.length() && index < strRight.length())
        {
            if(strLeft[index] == strRight[index])
            {
                strResult+=strLeft[index];
            }
            else
            {
                break;
            }
            index++;
        }
        return strResult;
    }
};


int main(int argc,char * argv[]){
    Solution solu;
    std::vector<std::string> curVec={"flower","flow","flight"};
    std::cout<<solu.longestCommonPrefix(curVec)<<std::endl;
    return 0;
}
