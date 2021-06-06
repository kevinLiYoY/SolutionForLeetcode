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

//方法1：将输入数用字串格式存储，逆序输出结果

int reverse(int input)
{
    string strTmp;
    std::stringstream strm;
    strm << input;
    strm >> strTmp;
    string result;

    bool negative = false;
    if(strTmp.front() == '-')
    {
        result.push_back(strTmp.front());
        strTmp = strTmp.substr(1, strTmp.size());
        negative = true;
    }
    for(int i = (strTmp.size() -1); i >= 0; --i)
    {
        result.push_back(strTmp.at(i));
    }
    const string strMax = "2147483647";
    const string strMin = "-2147483648";

    if(result.size() >= strMax.size())
    {
        if((!negative && (result > strMax)) || (negative && (result > strMin)))
        {
            return 0;
        }
    }
    
    int out = 0;
    strm.clear();
    strm << result;
    strm >> out;
    std::cout << "result: " << result << " out: " << out << std::endl;
    return out;
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
        std::cout << "Please input a number here." << std::endl;
        int row = 0;
        std::cin >> row;
        cin.ignore();

        int result = reverse(row);
        std::cout << "****************************************************Result: " << result << std::endl;
    }

    return 0;
}

