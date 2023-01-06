/**
 * @file Out_of_bounds.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

//Out-of-bounds accesses to heap, stack and globals
//g++ -O0 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address ./Out_of_bounds.cpp
#include <iostream>
char g_ch[5]={0};
int main(int argc,char * argv[])
{
    std::cout<<g_ch[5]<<std::endl;
    char ch_local[6]={0};
    
    std::cout<<ch_local[6]<<std::endl;
    for(int i = 0 ; i < 7 ; i++)
    {
        std::cout<<ch_local[i]<<std::endl;
    }

    char * pChar = new char[5];
    for(int i = 0 ; i < 7 ; i++)
    {
        std::cout<<pChar[i]<<std::endl;
    }
    delete [] pChar;
    return 0;
}