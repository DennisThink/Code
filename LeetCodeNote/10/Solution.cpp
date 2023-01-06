#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define DE_LINE std::cout<<__LINE__<<std::endl;
class Solution {
public:
    bool isMatch2(string s, string p) {
        int sIndex = 0;
        int pIndex = 0;
        if(p == ".*")
        {
            return true;
        }
        while(pIndex < p.length() && sIndex < s.length())
        {
            //.匹配任意一个字符
            if(p[pIndex] == '.')
            {
                pIndex++;
                sIndex++;
            }
            
            //匹配上了
            if(p[pIndex]==s[sIndex])
            {
                if(pIndex+1 < p.length())
                {
                    if(p[pIndex+1]=='*')
                    {
                        sIndex++;
                    }
                    else
                    {
                        sIndex++;
                        pIndex++;
                    }
                }
                else
                {
                    sIndex++;
                    pIndex++;
                }
            }
            else 
            {
                if(pIndex+1 < p.length())
                {
                    if(p[pIndex+1]=='*')
                    {
                        pIndex+=2;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        }
        if(pIndex == p.length() && sIndex == s.length())
        {
            return true;   
        }
        else
        {
            if(pIndex == p.length()-2 && p[pIndex+1]=='*')
            {
                return true;
            }
            return false;
        }
    }

    struct Match_t
    {
        char m_ch;
        bool m_bCopy;//可以被拷贝
        bool m_bZero;//可以0匹配
        Match_t(char ch,bool bCopy=false,bool bZero=false)
        {
            m_ch = ch;
            m_bCopy = bCopy;
            m_bZero = bZero;
        }

        void Print()
        {
            std::cout<<m_ch<<" Copy:"<<m_bCopy<<"  Zero:"<<m_bZero<<std::endl;
        }
    };

    //根据.和*计算匹配个数
    bool isMatch(string s,string p)
    {
        std::vector<Match_t> matchVec;
        int pIndex = 0;
        while(pIndex < p.length())
        {
            if(pIndex < p.length()-1 && p[pIndex+1]=='*')
            {
                matchVec.push_back(Match_t(p[pIndex],true,true));
                pIndex+=2;
                DE_LINE
            }
            else
            {
                matchVec.push_back(Match_t(p[pIndex]));
                pIndex++;
                DE_LINE
            }
        }

        std::cout<<"Parse Vec Begin"<<std::endl;
        for(auto item:matchVec)
        {
            item.Print();
        }
        std::cout<<"Parse Vec End"<<std::endl;

        int sIndex = 0;
        int matchIndex = 0;
        while( !s.empty() && !matchVec.empty() && matchIndex < matchVec.size())
        {
            auto matchValue=matchVec[matchIndex];
          
            //字符完全匹配
            if(matchValue.m_ch == s[sIndex])
            {
                s.erase(sIndex,1);
                matchValue.Print();
                std::cout<<s[sIndex]<<"  "<<__LINE__<<std::endl;
                //不能拷贝，matchIndex++
                if(!(matchValue.m_bCopy))
                {
                   std::cout<<__LINE__<<std::endl;
                   matchVec.erase(matchVec.begin()+matchIndex);
                }  
                else
                {
                    std::cout<<__LINE__<<std::endl;
                }      
            }
            else
            {
                //不是.
                if(matchValue.m_ch != '.')
                {
                    //可以忽略，跳过当前匹配
                    if(matchValue.m_bZero)
                    {
                        matchValue.Print();
                        std::cout<<s[sIndex]<<"  "<<__LINE__<<std::endl;
                        matchVec.erase(matchVec.begin());
                        //matchIndex++;
                    }
                    //不可以忽略，匹配失败
                    else
                    {
                        matchValue.Print();
                        std::cout<<s[sIndex]<<"  "<<__LINE__<<std::endl;
                        return false;
                    }
                }
                //是.
                else
                {
                    //.并且可以拷贝，比较.之后的字符
                    if(matchValue.m_bCopy)
                    {
                        sIndex++;
                        if(matchIndex<matchVec.size())
                        {
                            matchIndex++;
                        }
                    }
                    else
                    {
                        //. 匹配任意字符
                        std::cout<<__LINE__<<std::endl;
                        //matchIndex++;
                        matchVec.erase(matchVec.begin());
                        sIndex++;
                    }
                }
            }
        }

        if(sIndex != s.length())
        {
            std::cout<<__LINE__<<std::endl;
            return false;
        }
        else 
        {
            if(matchIndex == matchVec.size())
            {
                std::cout<<__LINE__<<std::endl;
                return true;
            }
            else
            {
                while(matchIndex < matchVec.size())
                {
                    if(matchVec[matchIndex].m_bZero)
                    {
                        matchIndex++;
                    }
                    else
                    {
                        std::cout<<__LINE__<<std::endl;
                        return false;
                    }
                }
            }
        }
        std::cout<<__LINE__<<std::endl;
        return true;
    }
};


int main(int argc,char * argv[])
{
    Solution solu;
    /*if(solu.isMatch("aa","a"))
    {
        std::cout<<"bad"<<std::endl;
    }
    else
    {
        std::cout<<"good"<<std::endl;
    }

    if(solu.isMatch("aa","a*"))
    {
        std::cout<<"good"<<std::endl;
    }
    else
    {
        std::cout<<"bad"<<std::endl;
    }

    if(solu.isMatch("ab",".*"))
    {
        std::cout<<"good"<<std::endl;
    }
    else
    {
        std::cout<<"bad"<<std::endl;
    }
    
    if(solu.isMatch("aab","c*a*b"))
    {
        std::cout<<"good"<<std::endl;
    }
    else
    {
        std::cout<<"bad"<<std::endl;
    }*/

    /*if(solu.isMatch("mississippi","mis*is*p*."))
    {
       std::cout<<"good"<<std::endl;
    }
    else
    {
        std::cout<<"bad"<<std::endl;
    }*/

    if(solu.isMatch("ab",".*c"))
    {
       std::cout<<"Not Passed"<<std::endl;
    }
    else
    {
        std::cout<<"Passed "<<std::endl;
    }

    if(solu.isMatch("ab",".*"))
    {
       std::cout<<"Passed"<<std::endl;
    }
    else
    {
        std::cout<<"Not Passed "<<std::endl;
    }
    return 0;
}