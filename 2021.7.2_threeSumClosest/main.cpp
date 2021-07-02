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

int threeSumClosest(vector<int>& nums, int target)
{
    int result = 0;
    //std::sort(nums.begin(), nums.end()); //先对input 进行排序
    // vector<int>::iterator iter = std::unique(nums.begin(), nums.end());
    // nums.erase(iter, nums.end());
    int iMinSum = INT_MAX;
    for(int i = 0; i < nums.size(); ++i)
    {
        int firstNum = nums.at(i);
        for(int j = i + 1; j < nums.size(); ++j)
        {
            int secondNum = nums.at(j);
            for(int k = j + 1; k < nums.size(); ++k)
            {
                int threeNum = nums.at(k);
                int curSumClosest = abs((firstNum + secondNum + threeNum) - target); //取绝对值
                //std::cout << "curSumClosest: "<< curSumClosest << " iMinSum:" << iMinSum << std::endl;
                if(iMinSum > curSumClosest)
                {
                    iMinSum = curSumClosest;
                    result = firstNum + secondNum + threeNum;
                    //std::cout << "strFirst: "<< firstNum << " strSecond:" << secondNum << " threeNum:" << threeNum << std::endl;
                }
            }
        }
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

        std::cout << "Please input an number for the target here:" << std::endl;
        int target = 0;
        std::cin >> target;
        cin.ignore();

        int result = threeSumClosest(muns, target);
        std::cout << "****************************************************Result: " << result << std::endl;
    }

    return 0;
}

