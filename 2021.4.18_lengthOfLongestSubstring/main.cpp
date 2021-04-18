#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

//方法1：使用字串记录当前无重复字符的字串，每增加一个字符，检查当前字串中是否已存在字符，如已存在，则移除在此位置之前的所有字符，并更新当前字串，直至所有字符扫描完成。

int lengthOfLongestSubstring(string s)
{
    string curSubStr;
    int maxSize = 0;
    if(s.empty())
    {
        std::cout << "Error: the input parameters do not meet the requirements" << std::endl;
    }

    auto iter = s.begin();
    while(iter != s.end())
    {
        if(maxSize < curSubStr.size())
        {
            maxSize = curSubStr.size();
        }

        string::size_type index = curSubStr.find(*iter);
        if(index != s.npos) //fully loaded the num into list and queue first;
        {
            curSubStr = curSubStr.substr((index + 1), (curSubStr.size() - index));
        }
        curSubStr += *iter;
        ++iter; //sliding window move to next position
    }
    return maxSize;
}


int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter the characters, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        int maxLength = lengthOfLongestSubstring(input);
        std::cout << "****************************************************Result: " << maxLength << std::endl;
    }

    return 0;
}

