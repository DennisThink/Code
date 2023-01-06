/**
 * @file mem_leak.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>
void MemLeakOne()
{
    char * pChar = new char;
}

void MemLeakTwo(int x)
{
    char * pChar = new char;
    if(x == 0)
    {
        delete pChar;
    }
}

void MemLeakThree()
{
    char * pChar = new char[12];
    delete []pChar;
}
int main(int argc,char * argv[])
{
    MemLeakOne();
    MemLeakTwo(2);
    MemLeakThree();
    return 0;
}