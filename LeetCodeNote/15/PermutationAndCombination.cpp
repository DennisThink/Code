#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
using std::vector;

class OneResultElem
{
  public:
    explicit OneResultElem(const std::vector<int> &orgResult) : m_array(orgResult){};

    virtual ~OneResultElem(){};

    std::size_t GetCount() const { return m_array.size(); };
    std::vector<int> GetArray() const {return m_array;}
    OneResultElem InsertAt(const std::size_t index, const int value) const
    {
        std::vector<int> newVec;
        for (int i = 0; i < index; i++)
        {
            newVec.push_back(m_array[i]);
        }
        newVec.push_back(value);
        for (int i = index; i < GetCount(); i++)
        {
            newVec.push_back(m_array[i]);
        }
        return OneResultElem(newVec);
    };

    OneResultElem SubElem(const int nPrefix)
    {
        std::vector<int> newVec;
        if (nPrefix > GetCount())
        {
            return OneResultElem(newVec);
        }
        for (int i = 0; i < nPrefix; i++)
        {
            newVec.push_back(m_array[i]);
        }
        return OneResultElem(newVec);
    }

    //获取组合使用
    OneResultElem SortSubElem(const int nPrefix)
    {
        std::vector<int> newVec;
        if (nPrefix > GetCount())
        {
            return OneResultElem(newVec);
        }
        for (int i = 0; i < nPrefix; i++)
        {
            newVec.push_back(m_array[i]);
        }
        std::sort(newVec.begin(),newVec.end());
        return OneResultElem(newVec);
    }

    //实现去重，相同元素返回false，不同元素返回true
    bool operator<(const OneResultElem &other) const
    {
        if (this->GetCount() < other.GetCount())
        {
            return true;
        }
        for (std::size_t index = 0; index < GetCount(); index++)
        {
            if (this->m_array[index] < other.m_array[index])
            {
                return true;
            }
        }
        return false;
    }

    std::string ToString() const
    {
        std::string strResult;
        for (const auto &item : m_array)
        {
            strResult += std::to_string(item);
            strResult += ",";
        }
        return "(" + strResult.substr(0, strResult.length() - 1) + ")";
    }

  private:
    std::vector<int> m_array;
};
std::vector<OneResultElem> Permutation(const int nTotal, const int nSelectElem)
{
    std::vector<OneResultElem> resultElems;
    if (nTotal <= 0)
    {
        return resultElems;
    }
    if (nTotal == 1)
    {
        resultElems.push_back(OneResultElem(std::vector<int>(0)));
        return resultElems;
    }
    std::vector<int> orgVec;
    for (int i = 0; i < nTotal; i++)
    {
        orgVec.push_back(i);
    }

    std::vector<OneResultElem> allElem;
    std::vector<OneResultElem> nextAllElem;
    nextAllElem.push_back(OneResultElem(std::vector<int>{orgVec[0]}));
    for (std::size_t index = 1; index < orgVec.size(); index++)
    {
        allElem = nextAllElem;
        nextAllElem.clear();
        for (const auto elem : allElem)
        {
            for (std::size_t i = 0; i <= elem.GetCount(); i++)
            {
                nextAllElem.push_back(elem.InsertAt(i, orgVec[index]));
            }
        }
        allElem = nextAllElem;
    }

    std::set<OneResultElem> elemSet;
    for (auto item : allElem)
    {
        elemSet.insert(item.SubElem(nSelectElem));
    }

    for (auto item : elemSet)
    {
        resultElems.push_back(item);
    }
    return resultElems;
}


std::vector<OneResultElem> Combination(const int nTotal, const int nSelectElem)
{
    std::vector<OneResultElem> resultElems;
    if (nTotal <= 0)
    {
        return resultElems;
    }
    if (nTotal == 1)
    {
        resultElems.push_back(OneResultElem(std::vector<int>(0)));
        return resultElems;
    }
    std::vector<int> orgVec;
    for (int i = 0; i < nTotal; i++)
    {
        orgVec.push_back(i);
    }

    std::vector<OneResultElem> allElem;
    std::vector<OneResultElem> nextAllElem;
    nextAllElem.push_back(OneResultElem(std::vector<int>{orgVec[0]}));
    for (std::size_t index = 1; index < orgVec.size(); index++)
    {
        allElem = nextAllElem;
        nextAllElem.clear();
        for (const auto elem : allElem)
        {
            for (std::size_t i = 0; i <= elem.GetCount(); i++)
            {
                nextAllElem.push_back(elem.InsertAt(i, orgVec[index]));
            }
        }
        allElem = nextAllElem;
    }

    std::set<OneResultElem> elemSet;
    for (auto item : allElem)
    {
        elemSet.insert(item.SortSubElem(nSelectElem));
        {
            std::cout << "------------------" << std::endl;
            for (const auto elem : elemSet)
            {
                std::cout << elem.ToString() << std::endl;
            }
        }
    }

    for (auto item : elemSet)
    {
        resultElems.push_back(item);
    }
    return resultElems;
}



int main2(int argc, char *argv[])
{
    std::vector<int> orgVec = {1, 2, 3};
    OneResultElem elem(orgVec);
    std::cout << elem.ToString() << std::endl;
    std::vector<OneResultElem> allElem;
    std::vector<OneResultElem> nextAllElem;
    nextAllElem.push_back(OneResultElem(std::vector<int>{orgVec[0]}));
    for (std::size_t index = 1; index < orgVec.size(); index++)
    {
        allElem = nextAllElem;
        nextAllElem.clear();
        for (const auto elem : allElem)
        {
            for (std::size_t i = 0; i <= elem.GetCount(); i++)
            {
                nextAllElem.push_back(elem.InsertAt(i, orgVec[index]));
            }
        }
        allElem = nextAllElem;
    }
    std::cout << "------------------" << std::endl;
    for (const auto elem : allElem)
    {
        std::cout << elem.ToString() << std::endl;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    while(true)
    {
        int x = 0;
        int y = 0;
        std::cout<<"Input X"<<std::endl;
        std::cin>>x;
        std::cout<<"Input Y"<<std::endl;
        std::cin>>y;
        auto allElem = Permutation(x, y);
        std::cout << "------------------" << std::endl;
        for (const auto elem : allElem)
        {
            std::cout << elem.ToString() << std::endl;
        }
    }

    {
        auto allElem = Permutation(3, 2);
        std::cout << "------------------" << std::endl;
        for (const auto elem : allElem)
        {
            std::cout << elem.ToString() << std::endl;
        }
    }

    {
        auto allElem = Permutation(4, 2);
        std::cout << "------------------" << std::endl;
        for (const auto elem : allElem)
        {
            std::cout << elem.ToString() << std::endl;
        }
    }

    {
        auto allElem = Combination(3, 3);
        std::cout << "------------------" << std::endl;
        for (const auto elem : allElem)
        {
            std::cout << elem.ToString() << std::endl;
        }
    }

    {
        auto allElem = Combination(3, 2);
        std::cout << "------------------" << std::endl;
        for (const auto elem : allElem)
        {
            std::cout << elem.ToString() << std::endl;
        }
    }

    {
        auto allElem = Combination(4, 2);
        std::cout << "------------------" << std::endl;
        for (const auto elem : allElem)
        {
            std::cout << elem.ToString() << std::endl;
        }
    }
    return 0;
}