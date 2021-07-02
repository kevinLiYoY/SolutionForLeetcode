#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <limits.h>

using namespace std;

//方法1, 遍历并求出当前和，并依据三数和为零求出空缺位置数值，在余下的数字中寻找目标值，如果找到，则放入输出结果列表中

bool findMatchNum(int iMatchSum, int index, vector<int>& nums)
{
    vector<int>::iterator iter = std::find(nums.begin() + index, nums.end(), iMatchSum);
    if(iter != nums.end())
    {
        return true;
    }
    return false;
}

vector<vector<int>> threeSum(vector<int>& nums)
{
    vector<vector<int>> result;
    vector<int> integerGrp;
    
    //依目要求不可以包含重复的三元组，因此对不同index相同值需要去重
    std::sort(nums.begin(), nums.end()); //先对input 进行排序，保证相同三元组元素顺序一致
    // vector<int>::iterator iter = std::unique(nums.begin(), nums.end());
    // nums.erase(iter, nums.end());

    for(int i = 0; i < nums.size(); ++i)
    {
        integerGrp.clear();
        int curNum = nums.at(i);
        for(int j = i + 1; j < nums.size(); ++j)
        {
            int subNum = nums.at(j);
            int iMatchSum = (0 - (curNum + subNum));
            bool bIsFound = findMatchNum(iMatchSum, j + 1, nums); //注意，寻找匹配值需要从当前pos后一个位置(j + 1)开始
            if(bIsFound)
            {
                integerGrp.push_back(curNum);
                integerGrp.push_back(subNum);
                integerGrp.push_back(iMatchSum);
                if(std::find(result.begin(), result.end(), integerGrp) == result.end()) //未找到相同三元组则插入，找到则跳过
                {
                    result.push_back(integerGrp);
                }
                integerGrp.clear();
            }
        }
        //std::cout << "strFirst: "<< strFirst << " strSecond:" << strSecond << std::endl;
    }
    return result;
}


int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter integer separated by space, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        stringstream strStream;
        strStream << input;
        int item;
        vector<int> muns;
        while(strStream >> item)
        {
            muns.push_back(item);
            //std::cout << "pushback: "<< item << std::endl;
        }

        std::cout << "****************************************************Result: " << std::endl;
        vector<vector<int>> result = threeSum(muns);
        auto iter = result.begin();
        while(iter != result.end())
        {
            vector<int>::iterator iterGrp = iter->begin();
            while(iterGrp != iter->end())
            {
                std::cout << *iterGrp << ", ";
                ++iterGrp;
            }
            std::cout << std::endl;
            ++iter;
        }
        
    }

    return 0;
}

