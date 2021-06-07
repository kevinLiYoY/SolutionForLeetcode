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

//方法1：使用库函数sstream 实现类型转换
//方法2：不使用库函数，实现类型转换

void Trim(string &str)//去掉数字无关字符
{
    size_t firstPos = std::string::npos;
    size_t lastPos = std::string::npos;
    bool negative = false;
    for(int i = 0; i < str.size(); ++i)
    {
        if(firstPos == std::string::npos)
        {
            if(str.at(i) == '-')
            {
                negative = true; 
            }
            if(isdigit(str.at(i)))
            {
                firstPos = i;
            }
        }
        if((firstPos != std::string::npos) && (lastPos == std::string::npos))
        {
            if(!isdigit(str.at(i)) && (str.at(i) != '.'))
            {
                lastPos = i - 1;
                break;
            }
            else if(i == (str.size() - 1))
            {
                lastPos = i;
                break;
            }
        }
    }
    if((firstPos != std::string::npos) && (lastPos != std::string::npos))
    {
        if(negative)
        {
            str = "-" + str.substr(firstPos, (lastPos - firstPos + 1));
        }
        else
        {
            str = str.substr(firstPos, (lastPos - firstPos + 1));
        }

        const string strMax = "2147483647";
        const string strMin = "-2147483648";
        if(str.size() >= strMax.size())
        {
            if(!negative && (str > strMax))
            {
                str = strMax;
            }
            else if(negative && (str > strMin))
            {
                str = strMin;
            }
        }
    }
    else //if not found any digit clear all the characters
    {
        str.clear();
    }
}

int myAtoi(string input) //不支持小数点版本（符合原题）
{
    Trim(input); //get the first valid digit string

    int result = 0;
    std::stringstream strm;
    strm.clear();
    strm << input;
    strm >> result; // string switch to digit
    std::cout << "strTmp: " << input << " result: " << result << std::endl;
    return result;
}

double myAtoi2(string input) //支持小数点版本（拓展）
{
    Trim(input); //get the first valid digit string
    bool negative = false;
    bool decimal = false;
    double result = 0;
    double curCoefficient = 1;
    auto iter = input.begin();
    while(iter != input.end()) //string switch to digit
    {
        switch(*iter)
        {
        case '0':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
            }
            else
            {
                result = (result * 10);
            }
            break;
        case '1':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
                result = result + (curCoefficient * 1);
            }
            else
            {
                result = (result * 10) + 1;
            }
            break;
        case '2':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
                result = result + (curCoefficient * 2);
            }
            else
            {
                result = (result * 10) + 2;
            }
            break;
        case '3':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
                result = result + (curCoefficient * 3);
            }
            else
            {
                result = (result * 10) + 3;
            }
            break;
        case '4':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
                result = result + (curCoefficient * 4);
            }
            else
            {
                result = (result * 10) + 4;
            }
            break;
        case '5':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
                result = result + (curCoefficient * 5);
            }
            else
            {
                result = (result * 10) + 5;
            }
            break;
        case '6':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
                result = result + (curCoefficient * 6);
            }
            else
            {
                result = (result * 10) + 6;
            }
            break;
        case '7':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
                result = result + (curCoefficient * 7);
            }
            else
            {
                result = (result * 10) + 7;
            }
            break;
        case '8':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
                result = result + (curCoefficient * 8);
            }
            else
            {
                result = (result * 10) + 8;
            }
            break;
        case '9':
            if(decimal)
            {
                curCoefficient = curCoefficient * 0.1;
                result = result + (curCoefficient * 9);
            }
            else
            {
                result = (result * 10) + 9;
            }
            break;
        case '+':
            negative = false;
            break;
        case '-':
            negative = true;
            break;
        case '.':
            if(!decimal)
            {
                decimal = true;
            }
            else
            {
                 goto label; //multiple character '.', break current loop
            }
            break;
        default:
            break;
        }
        ++iter;
    }

    label:
    if(negative)
    {
        result = -result;
    }

    std::cout << "strTmp2: " << input << " result2: " << result << std::endl;
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

        int result = myAtoi(input);
        std::cout << "****************************************************Result: " << result << std::endl;

        double dresult = myAtoi2(input);
        std::cout << "****************************************************Result2: " << dresult << std::endl;
    }

    return 0;
}

