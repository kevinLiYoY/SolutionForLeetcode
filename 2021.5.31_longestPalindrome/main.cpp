#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

//方法1：使用栈及顺序列表，通过栈记录当前已录入的数据，顺序列表作为当前字串顺序，以此实现最大回文字串输出。

bool duplicateCharCheck(const char item, std::stack<char> &oderList)
{
    if(!oderList.empty())
    {
        const char lastItem = oderList.top();
        std::cout << " last item: " << lastItem << " check item: " << item << std::endl;

        if(lastItem == item)
        {
            return true;
        }
    }
    return false;
}

string longestPalindrome(string strInput)
{
    string maxResult("");
    if(strInput.empty())
    {
        return maxResult;
    }
    maxResult.push_back(*(strInput.begin()));
    list<char> tmpList;
    std::stack<char> oderList;
    auto iter = strInput.begin();
    while(iter != strInput.end())
    {
        bool isDuplicateChar = duplicateCharCheck(*iter, oderList);
        if(isDuplicateChar)
        {
            oderList.pop();
            if(tmpList.back() == *iter)
            {
                tmpList.pop_back();
            }
            tmpList.push_back(*iter);
            tmpList.push_front(*iter);
        }
        else
        {
            if(tmpList.size() > maxResult.size())
            {
                std::cout << "before maxResult1: " << maxResult << std::endl;
                maxResult.clear();
                maxResult.assign(tmpList.begin(), tmpList.end());
                std::cout << "after maxResult2: " << maxResult << std::endl;
                std::stack<char>().swap(oderList); //clearStack
            }
            tmpList.clear();
            if(!oderList.empty())
            {
                tmpList.push_back(*iter);
            }
            //check next
            isDuplicateChar = duplicateCharCheck(*(iter + 1), oderList);
            if(isDuplicateChar)
            {
                ++iter;
                continue;
            }
            oderList.push(*iter);
        }
        ++iter;
    }

    if(!tmpList.empty())
    {
        if(tmpList.size() > maxResult.size())
        {
            std::cout << "before maxResult: " << maxResult << std::endl;
            maxResult.clear();
            maxResult.assign(tmpList.begin(), tmpList.end());
            std::cout << "after maxResult: " << maxResult << std::endl;
        }
        tmpList.clear();
    }
    return maxResult;
}

int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter characters as a string, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        string longest = longestPalindrome(input);
        std::cout << "****************************************************Result: " << longest << std::endl;
    }

    return 0;
}

