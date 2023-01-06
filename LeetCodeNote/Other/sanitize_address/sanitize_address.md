# -fsanitize=address 参数作用

在C++的开发中，我们经常会遇到很多和内存有关的错误。其实使用编译器的一些检查功能，可以帮助我们一定程度上减少这样的错误,下面我们介绍一下
`-fsanitize=address` 的作用以及一些用法。

## 1.参数介绍

介绍的部分参考:[链接](https://clang.llvm.org/docs/AddressSanitizer.html)

## 2.主要检查的方面

1. Out-of-bounds accesses to heap, stack and globals
2. Use-after-free
3. Use-after-return (runtime flag ASAN_OPTIONS=detect_stack_use_after_return=1)
4. Use-after-scope (clang flag -fsanitize-address-use-after-scope)
5. Double-free, invalid free
6. Memory leaks (experimental)

## 3.代码示例

### 3.1 检查地址访问越界
```cpp
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
```

程序的输出:
![](https://www.dennisthink.com/wp-content/uploads/2019/03/out_of_bounds.png)


### 3.2 检查释放后再次使用变量
* 代码

```cpp
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
```

* 程序输出:
![](https://www.dennisthink.com/wp-content/uploads/2019/03/user_after_free.png)

## 3.3 内存泄露

程序代码:
```cpp
//g++ -O0 -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize=address ./Out_of_bounds.cpp
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
```

* 编译警告:
![](https://www.dennisthink.com/wp-content/uploads/2019/03/mem_leak_warn.png)

* 程序输出:
![](https://www.dennisthink.com/wp-content/uploads/2019/03/mem_leak2.png)