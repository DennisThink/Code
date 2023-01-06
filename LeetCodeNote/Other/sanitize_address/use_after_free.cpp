/**
 * @file use_after_free.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */
//g++ -O0 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address ./Out_of_bounds.cpp

#include <iostream>
int main(int argc,char* argv[])
{
    char * pChar = new char;
    *pChar = '1';
    std::cout<<*pChar<<std::endl;
    delete pChar;
    *pChar = '2';
    std::cout<<*pChar<<std::endl;
    return 0;
}