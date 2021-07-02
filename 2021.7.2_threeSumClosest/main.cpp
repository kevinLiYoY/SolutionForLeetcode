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

//方法1, 遍历并求出当前和，

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

//官方解题，使用双指针减少时间复杂度
int threeSumClosest2(vector<int>& nums, int target)
{
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int best = 1e7;

    // 根据差值的绝对值来更新答案
    auto update = [&](int cur) 
    {
        if (abs(cur - target) < abs(best - target))
        {
            best = cur;
        }
    };

    // 枚举 a
    for (int i = 0; i < n; ++i)
    {
        // 保证和上一次枚举的元素不相等
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        // 使用双指针枚举 b 和 c
        int j = i + 1, k = n - 1;
        while (j < k)
        {
            int sum = nums[i] + nums[j] + nums[k];
            // 如果和为 target 直接返回答案
            if (sum == target)
            {
                return target;
            }
            update(sum);
            if (sum > target)
            {
                // 如果和大于 target，移动 c 对应的指针
                int k0 = k - 1;
                // 移动到下一个不相等的元素
                while (j < k0 && nums[k0] == nums[k])
                {
                    --k0;
                }
                k = k0;
            }
            else
            {
                // 如果和小于 target，移动 b 对应的指针
                int j0 = j + 1;
                // 移动到下一个不相等的元素
                while (j0 < k && nums[j0] == nums[j])
                {
                    ++j0;
                }
                j = j0;
            }
        }
    }
    return best;
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
        result = threeSumClosest2(muns, target);
        std::cout << "****************************************************Result2: " << result << std::endl;
    }

    return 0;
}

