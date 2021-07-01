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

string getComonPre(string strF, string strS)
{
    string strCom;
    auto iterF = strF.begin();
    auto iterS = strS.begin();
    while((iterF != strF.end()) && (iterS != strS.end()))
    {
        if(*iterF != *iterS)
        {
            break;
        }
        strCom.push_back(*iterF);
        ++iterF;
        ++iterS;
    }
    return strCom;
}

string longestCommonPrefix(vector<string>& strs)
{
    string result;
    string strFirst = strs.at(0);
    string strSecond;
    for(int i = 1; i < strs.size(); ++i)
    {
        strSecond = strs.at(i);
        //std::cout << "strFirst: "<< strFirst << " strSecond:" << strSecond << std::endl;
        if(result.empty())
        {
            result = getComonPre(strFirst, strSecond);
        }
        else
        {
            result = getComonPre(result, strSecond);
        }
        if(result.empty())
        {
            break;
        }
    }
    return result;
}


int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter string separated by space, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        stringstream strStream;
        strStream << input;
        string item;
        vector<string> muns;
        while(strStream >> item)
        {
            muns.push_back(item);
            //std::cout << "pushback: "<< item << std::endl;
        }

        string result = longestCommonPrefix(muns);
        std::cout << "****************************************************Result: " << result << std::endl;
    }

    return 0;
}

