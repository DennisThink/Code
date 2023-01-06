#include <string>
#include <stack>
#include <iostream>
using std::string;

class Solution
{
  public:
    bool isValid(string s)
    {
        std::stack<char> chStack;
        std::size_t sLen = s.length();
        for (std::size_t i = 0; i < sLen; i++)
        {
            switch (s[i])
            {
            case '(':
            {
                chStack.push(s[i]);
            }
            break;
            case ')':
            {
                if (!chStack.empty())
                {
                    if (chStack.top() == '(')
                    {
                        chStack.pop();
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
            break;
            case '[':
            {
                chStack.push(s[i]);
            }
            break;
            case ']':
            {
                if (!chStack.empty())
                {
                    if (chStack.top() == '[')
                    {
                        chStack.pop();
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
            break;

            case '{':
            {
                chStack.push(s[i]);
            }
            break;
            case '}':
            {
                if (!chStack.empty())
                {
                    if (chStack.top() == '{')
                    {
                        chStack.pop();
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
            break;
            default:
            {
                return false;
            }
            }
        }

        if (chStack.empty())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main(int argc, char *argv[])
{
    Solution solu;
    {
        std::string str1 = "()";
        std::cout << solu.isValid(str1) << std::endl;
    }

    {
        std::string str1 = "()[]{}";
        std::cout << solu.isValid(str1) << std::endl;
    }

    {
        std::string str1 = "(]";
        std::cout << solu.isValid(str1) << std::endl;
    }

    {
        std::string str1 = "([)]";
        std::cout << solu.isValid(str1) << std::endl;
    }
    return 0;
}