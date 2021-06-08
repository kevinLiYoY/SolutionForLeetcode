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

//方法1：转换为字串进行处理
//方法2：不转换成字串处理

bool isPalindrome(int input)
{
    string strTmp;
    std::stringstream strm;
    strm << input;
    strm >> strTmp; // digit switch to string
    int indexFirst = 0;
    int indexLast = strTmp.size() - 1;
    while(indexFirst < indexLast)
    {
        if(strTmp.at(indexFirst++) != strTmp.at(indexLast--))
        {
            return false;
        }
    }
    return true;
}

bool isPalindrome2(int input)
{
    if(input < 0)
    {
        return false;
    }
    vector<int> numbers;
    int curNum = 0;
    while(1)
    {
        if(input == 0)
        {
            break;
        }
        curNum = input % 10;
        numbers.push_back(curNum);
        //std::cout << "numbers push_back: " << curNum << std::endl;
        input = input / 10;
    }

    int indexFirst = 0;
    int indexLast = numbers.size() - 1;
    while(indexFirst < indexLast)
    {
        if(numbers.at(indexFirst++) != numbers.at(indexLast--))
        {
            return false;
        }
    }
    return true;
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

        std::cout << "Please input a number here: " << std::endl;
        int row = 0;
        std::cin >> row;
        cin.ignore();
        bool result = isPalindrome(row);
        std::cout << "****************************************************Result: " << (result ? "true" : "false") << std::endl;

        result = isPalindrome2(row);
        std::cout << "****************************************************Result2: " << (result ? "true" : "false") << std::endl;
    }

    return 0;
}

