//g++ -O -g -fsanitize=address Solution.cpp

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;
class Solution {
public:
    string multiply(string num1, string num2) {
        assert(num1.length() < 110);
        assert(num2.length() < 110);
        int Num1Length= num1.length();
        std::string strResult = "";
        for(int num1Index = Num1Length-1;
            num1Index >= 0 ;
            num1Index--)
        {
            std::string strCur = multiply(num2,num1[num1Index]);
            strResult = add(strResult,strCur);
            num2+='0';
        }
        return trimLeftZero(strResult);
    }

private:
    std::string trimLeftZero(std::string num1)
    {
        int index = 0;
        while(index < num1.length())
        {
            if(num1[index]=='0')
            {
                index++;
            }
            else
            {
                break;
            }
            
        }
        if(index < num1.length())
        {
            return num1.substr(index,num1.length()-index);
        }
        else
        {
            return "0";
        }
    } 
    std::string multiply(string num1,char ch){
        assert('0'<=ch);
        assert(ch <= '9');
        //assert( num1.length() < 110);
        if(num1.empty() ||
           ch == '0')
        {
            return "0";
        }

        const int CH_ARRAY_SIZE=256;
        char chResult[CH_ARRAY_SIZE]={0};
        int numIndex= num1.length()-1;
        int chIndex = CH_ARRAY_SIZE-1;

        int nCarry = 0;
        int nPos = 0;
        int nValue = 0;
        int nCharValue = ch-'0';
        
        while(numIndex >= 0)
        {
            nValue = (num1[numIndex]-'0')*nCharValue;
            nPos = (nValue+nCarry)  % 10;
            nCarry = (nValue+nCarry) / 10;
            chResult[chIndex] = '0'+nPos;
            numIndex--;
            chIndex--;
        }
        std::string strResult;
        if(nCarry != 0)
        {
            chResult[chIndex] = '0'+nCarry;
            strResult = std::string(chResult+chIndex,CH_ARRAY_SIZE-chIndex);
        }
        else
        {
            strResult = std::string(chResult+chIndex+1,CH_ARRAY_SIZE-chIndex-1);
        }
        return strResult;
    }

    std::string add(std::string num1,std::string num2){
        int num1Length = num1.length();
        int num2Length = num2.length();
        
        const int CH_ARRAY_SIZE=256;
        char chResult[CH_ARRAY_SIZE]={0};
        int chIndex = CH_ARRAY_SIZE-1;
        
        int nCarry = 0;
        int nPos = 0;
        int nValue = 0;
        while(num1Length > 0 && num2Length > 0)
        {
            nValue = (num1[num1Length-1]-'0')+(num2[num2Length-1]-'0');
            nPos = (nValue+nCarry)%10;
            nCarry = (nValue+nCarry)/10;
            assert(nPos<10);

            chResult[chIndex]='0'+nPos;
            
            num1Length--;
            num2Length--;
            chIndex--;
        }

        while(num1Length > 0)
        {
            nValue = (num1[num1Length-1]-'0');
            nPos = (nValue+nCarry)%10;
            nCarry = (nValue+nCarry)/10;

            chResult[chIndex]='0'+nPos;
            num1Length--;
            chIndex--;
        }

        while(num2Length > 0)
        {
            nValue = (num2[num2Length-1]-'0');
            nPos = (nValue+nCarry)%10;
            nCarry = (nValue+nCarry)/10;

            chResult[chIndex]='0'+nPos;
            num2Length--;
            chIndex--;
        }
        
        std::string strResult;
        if(nCarry != 0)
        {
            chResult[chIndex] = '0'+nCarry;
            strResult = std::string(chResult+chIndex,CH_ARRAY_SIZE-chIndex);
        }
        else
        {
            strResult = std::string(chResult+chIndex+1,CH_ARRAY_SIZE-chIndex-1);
        }
        return strResult;
    }
};


int main(int argc,char * argv[])
{
    std::cout<<argc<<argv[0]<<std::endl;
    Solution solu;
    std::cout<<solu.multiply("1","2")<<std::endl;
    std::cout<<solu.multiply("3","2")<<std::endl;
    std::cout<<solu.multiply("10","2")<<std::endl;
    std::cout<<solu.multiply("12","21")<<std::endl;
    std::cout<<solu.multiply("123","456")<<std::endl;
    std::cout<<solu.multiply("123","0")<<std::endl;
    {
        std::string Num1 = "327627058702778602539273796517171833851621821801164203772344061466";
        std::string Num2 = "43826220310628268637074692938715119932983147093078095467672675187190581895716023823681540707347276446528399";
        std::cout<<solu.multiply(Num1,Num2)<<std::endl;
    }
    //std::cout<<solu.multiply("6964594125027226699998128707627435007621143975736747759751","333791918659904899647584436187733004125181273682766434")<<std::endl;
    return 0;
}