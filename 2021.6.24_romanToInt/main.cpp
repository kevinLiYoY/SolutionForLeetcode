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
class RomanToInt
{
public:
    int get(std::string &roman)
    {
        for (int c : roman)
        {
            m_iAns += get_col(c);
        }
        m_iCur = 0; //reset
        return m_iAns;
    }
private:
    std::unordered_map<char, int> table =
    {
        {'I',   1},
        {'V',   5},
        {'X',   10},
        {'L',   50},
        {'C',   100},
        {'D',   500},
        {'M',   1000}
    };

    int get_col(char c) //获取当前字符对应的数字
    {
        int last = m_iCur;
        auto iter = table.find(c);
        if(iter != table.end())
        {
            m_iCur = iter->second;
            //std::cout << "last: " << last <<" cur: " << m_iCur << std::endl;
            if(m_iCur > last) //通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例,即当前数值大于上一次取值时，需特殊处理，如IV表示 V - I = 4
            {
                m_iCur = m_iCur - (2 * last);
            }
            //std::cout << "Characters: " << c <<" cur: " << m_iCur << std::endl;
            return m_iCur;
        }
        std::cout << "Characters: " << c <<" not found, phrase error! " << std::endl;
        return 0;
    }
private:
    int m_iAns = 0;
    int m_iCur = 0;
};

int romanToInt(string str)
{
    RomanToInt romanToInt;
    int result = romanToInt.get(str);
    return result;
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

        int result = romanToInt(input);
        std::cout << "****************************************************Result: " << result << std::endl;
    }

    return 0;
}

