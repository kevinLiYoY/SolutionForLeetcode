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

//方法1，对照表法
/***********************************
 * 对照表
***********************************/
class IntToRoman
{
public:
    string get(int num)
    {
        std::stack<string> numbers;
        int curNum = 0;
        int curMultiple = 1; //当前整10权
        while(1)
        {
            if(num == 0)
            {
                break;
            }
            curNum = num % 10;
            string strtmp = get_str(curNum, curMultiple);
            numbers.push(strtmp);
            num = num / 10;
            curMultiple = curMultiple * 10;
        }
        string result;
        while (!numbers.empty())
        {
            result += numbers.top();
            numbers.pop();
        }
        
        return result;
    }
private:
    std::unordered_map<int, char> table =
    {
        {1,     'I'},
        {5,     'V'},
        {10,    'X'},
        {50,    'L'},
        {100,   'C'},
        {500,   'D'},
        {1000,  'M'}
    };

    string get_str(int curNum, int curMultiple)
    {
        string result("");
        if((curNum < 4) && (curNum > 0))
        {
            auto iter = table.find(curMultiple);
            if(iter != table.end())
            {
                for(int i = 0; i < curNum; ++i)
                {
                    result.push_back(iter->second);
                }
            }
        }
        else if(curNum == 4)
        {
            auto iter = table.find(curMultiple);
            if(iter != table.end())
            {
                result.push_back(iter->second);
            }
            iter = table.find((curMultiple * 5));
            if(iter != table.end())
            {
                result.push_back(iter->second);
            }
        }
        else if((curNum >= 5) && (curNum < 9))
        {
            auto iter = table.find((curMultiple * 5));
            if(iter != table.end())
            {
                result.push_back(iter->second);
            }
            iter = table.find(curMultiple);
            if(iter != table.end())
            {
                for(int i = 0; i < (curNum - 5); ++i)
                {
                    result.push_back(iter->second);
                }
            }
        }
        else if(curNum == 9)
        {
            auto iter = table.find(curMultiple);
            if(iter != table.end())
            {
                result.push_back(iter->second);
            }
            iter = table.find((curMultiple * 10));
            if(iter != table.end())
            {
                result.push_back(iter->second);
            }
        }
        //std::cout << "curNum: " << curNum << " curMultiple: " << curMultiple << " Characters: " << result << std::endl;
        return result;
    }
};

string intToRoman(int num)
{
    IntToRoman intToRoman;
    string result = intToRoman.get(num);
    return result;
}


int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter any characters to continue, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        std::cout << "Please input an number here:" << std::endl;
        int k = 0;
        std::cin >> k;
        cin.ignore();

        string result = intToRoman(k);
        std::cout << "****************************************************Result: " << result << std::endl;
    }

    return 0;
}

