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

//方法1：分组法，将每个字符取出后依次放入各自group中，然后再依次序汇总所有group中值，例如：P 放入group 1，A放入group 2，...到最大行数后反向寻找组号，然后分别依序从这四个组中取一行进行重新组装输出。
/*
P     I    N
A   L S  I G
Y A   H R
P     I
*/

string convert(string strInput, int numRows)
{
    std::vector<string> group(numRows);
    auto iter = strInput.begin();
    int curRow = 0;
    bool bRoundTrip = false;
    while(iter != strInput.end())
    {
        if(curRow == (numRows -1))
        {
            bRoundTrip = true;
        }
        if(curRow == 0)
        {
            bRoundTrip = false;
        }
        group[curRow].push_back(*iter);
        if(bRoundTrip)
        {
            --curRow;
        }
        else
        {
            ++curRow;
        }
        ++iter;
    }

    string sResult;
    for(int i = 0; i < group.size(); ++i)
    {
        sResult.append(group.at(i));
    }
    return sResult;
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
        std::cout << "Please input an number for the row." << std::endl;
        int row = 0;
        std::cin >> row;
        cin.ignore();

        string longest = convert(input, row);
        std::cout << "****************************************************Result: " << longest << std::endl;
    }

    return 0;
}

