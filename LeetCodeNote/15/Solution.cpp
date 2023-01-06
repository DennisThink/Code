#include <iostream>
#include <vector>

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
    std::vector<int> GetArray() const {return m_array;};
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
        if (this->GetCount() != other.GetCount())
        {
            return true;
        }
        for (std::size_t index = 0; index < GetCount(); index++)
        {
            if (this->m_array[index] != other.m_array[index])
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
    }

    for (auto item : elemSet)
    {
        resultElems.push_back(item);
    }
    return resultElems;
}


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        std::vector<OneResultElem> allElems = Combination(nums.size(),3);
        std::set<OneResultElem> setElem;
        for(const auto item:allElems)
        {
            int nSum = 0;
            std::vector<int> indexArray=item.GetArray();
            if(nums[indexArray[0]]+nums[indexArray[1]]+nums[indexArray[2]]==0)
            {
                auto elem = std::vector<int>{nums[indexArray[0]],nums[indexArray[1]],nums[indexArray[2]]};
                std::sort(elem.begin(),elem.end());
                setElem.insert(OneResultElem(elem));
            }
        }

        for(auto item:setElem)
        {
            result.push_back(item.GetArray());
        }

        return result;
    }
};

int main(int argc,char * argv[])
{
    {
        std::vector<int> nums={-1, 0, 1, 2, -1, -4};
        Solution solu;
        auto result = solu.threeSum(nums);
        for(auto item:result)
        {
            std::cout<<"[";
            for(auto index:item)
            {
                std::cout<<index<<",";
            }
            std::cout<<"]"<<std::endl;
        }
    }

    return 0;
}