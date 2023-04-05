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

int getSubArray(int n, int m, int k, std::string &strVal)
{
    if(k <= 1)
    {
        for(int i = m + 1; i <= n; ++i)
        {
            std::cout << strVal << i << ";" << std::endl;
        }

        std::size_t pos = strVal.rfind(',');
        if(pos != std::string::npos)
        {
            strVal = strVal.erase(pos, strVal.size() - pos);
            pos = strVal.rfind(',');
            if(pos != std::string::npos)
            {
                pos = pos + 1;
                strVal = strVal.erase(pos, strVal.size() - pos);
            }
        }
        return 0;
    }

    for(int j = m + 1; j <= n; ++j)
    {
        strVal += std::to_string(j);
        strVal += ",";
        getSubArray(n, j, k - 1, strVal);
    }
    std::size_t posis = strVal.rfind(',');
    if(posis != std::string::npos)
    {
        strVal = strVal.erase(posis, strVal.size() - posis);
        posis = strVal.rfind(',');
        if(posis != std::string::npos)
        {
            posis = posis + 1;
            strVal = strVal.erase(posis, strVal.size() - posis);
        }
        else
        {
            strVal.clear();
        }
    }
    
    return 0;
}

int process(int n, int k)
{
    if(n < 0 || k < 0 || n < k)
    {
        std::cout << "intput error" << std::endl;
        return 0;
    }
    
     int m = 0;
     std:;string strVal;
     int ret = getSubArray(n, m, k, strVal);
     return ret;
}


int main()
{
    int ret = process(10, 3);
    return 0;
}

