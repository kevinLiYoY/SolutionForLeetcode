#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
#include <algorithm>
#include <limits.h>
#include <random>
#include <time.h>
#include <Windows.h>


using namespace std;

int getSubArrayMinNum(int* arrays, const int length, const int target, int k)
{
    if(arrays == nullptr)
    {
        return 0;
    }
    for(int p = 0; p < length; ++p)
    {
        if(arrays[p] >= target)
        {
            return 1;
        }

        int sum = 0;
        for(int i = 0; i <= k; ++i) //递归寻找满足条件的相加个数
        {
            if((p + 1) >= length)
            {
                break;
            }
            sum += arrays[p + i];
        }
        if(sum >= target)
        {
            return k + 1;
        }
    }
    if(k > length)
    {
        return 0;
    }
    return getSubArrayMinNum(arrays, length, target, k + 1);
}

int process(int* arrays, const int length, const int target)
{
    if(arrays == nullptr)
    {
        std::cout << "intput error" << std::endl;
        return 0;
    }
    
     int k = 0;
     int count = getSubArrayMinNum(arrays, length, target, k);
     return count;
}


int main()
{
    int arrays[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int count = process(arrays, 12, 28);
    std::cout << "count:" << count << std::endl;
    return 0;
}

