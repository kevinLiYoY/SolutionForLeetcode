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

//方法1，穷举法
/***********************************
    将所有的容器大小计算出来找出最大值
***********************************/

//方法2，双指针移动法
/***********************************
    将首尾两位置开始计算容器大小。移动高度较小一边的指针，直至首位指针相同（相同意为重合），输出最大值
***********************************/
int maxArea(vector<int>& height)
{
    int result = 0;
    int maxArea = 0;
    for(int i = 0; i < height.size(); ++i)
    {
        for(int j = 1; j < height.size(); ++j)
        {
            result = (j - i) * (min(height.at(i), height.at(j)));
            maxArea = max(result, maxArea);
        }
    }
    return maxArea;
}

int maxArea2(vector<int>& height)
{
    int result = 0;
    int maxArea = 0;
    int leftPos = 0;
    int rightPos = height.size() - 1;
    while(leftPos != rightPos)
    {
        result = (rightPos - leftPos) * (min(height.at(leftPos), height.at(rightPos)));
        maxArea = max(result, maxArea);
        if(height.at(leftPos) > height.at(rightPos))
        {
            --rightPos;
        }
        else
        {
            ++leftPos;
        }
    }
    return maxArea;
}


int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter numbers which are separated by space to fill the heights, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        stringstream strStream;
        strStream << input;
        int item = 0;
        vector<int> heights;
        while(strStream >> item)
        {
            heights.push_back(item);
            //std::cout << "pushback: "<< item << std::endl;
        }

        int result = maxArea(heights);
        std::cout << "****************************************************Result: " << result << std::endl;

        result = maxArea2(heights);
        std::cout << "****************************************************Result2: " << result << std::endl;
    }

    return 0;
}

