/**
 * @file use_after_return.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <iostream>
char * GetBuf()
{
    char chBuf[128]={0};
    return chBuf+1;
}
int main(int argc,char * argv[])
{
    char * pBuf = GetBuf();
    *pBuf='9';
    std::cout<<*pBuf<<std::endl;
    return 0;
}