#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <vector>
#include <sstream>

using namespace std;

//input the parsed substring and calculate then output the result as a long type. eg: input 2+3, return 5;
long calculateParsed(string str)
{
    std::cout << "calculateParsed: " << str << std::endl;
    string subStr;
    string subType;
    vector<string> items;
    auto iter = str.begin();
    while (iter != str.end())
    {
        switch (*iter)
        {
        case '+':
        case '-':
            subType = *iter;
            items.push_back(subType);
            break;
        default:
            subStr += *iter;
            if(((iter + 1) == str.end()) || (*(iter + 1) == '+') || (*(iter + 1) == '-'))
            {
                items.push_back(subStr);
                subStr.clear();
            }
            break;
        }
        
        ++iter;
    }

    stringstream strStream;
    long first = 0;
    long second = 0;
    auto iterVec = items.begin();
    strStream << *iterVec;
    strStream >> first;
    while(iterVec != items.end())
    {
        if(*iterVec == "+")
        {
            strStream.clear();
            strStream << *(++iterVec);
            strStream >> second;
            first += second;
            continue;
        }
        else if(*iterVec == "-")
        {
            strStream.clear();
            strStream << *(++iterVec);
            strStream >> second;
            first -= second;
            continue;
        }

        ++iterVec;
    }
    return first;
}

long calculate(string input)
{
    stack<string> mystack;
    string subStr;
    string subType;
    long result = 0;
    auto iter = input.begin();
    while(iter != input.end())
    {
        if(*iter == '(')
        {
            subType = *iter;
            mystack.push(subType);
        }
        else if(*iter == ')')
        {
            if(mystack.size() != 0)
            {
                if(mystack.top() != "(")
                {
                    subStr = mystack.top();
                    mystack.pop();
                    result = calculateParsed(subStr);
                    if(mystack.size() != 0)
                    {
                        if(mystack.top() == "(")
                        {
                            mystack.pop();
                        }
                        if((mystack.size() != 0) && (mystack.top() != "("))
                        {
                            mystack.top() += to_string(result);
                        }
                        else
                        {
                            mystack.push(to_string(result));
                        }
                    }
                    else
                    {
                        mystack.push(to_string(result));
                    }
                }
                else
                {
                    mystack.pop();
                }
            }
        }
        else if(*iter == ' ')
        {
            //do nothing
        }
        else
        {
            if((mystack.size() != 0) && (mystack.top() != "("))
            {
                mystack.top() += *iter;
            }
            else
            {
                subStr = *iter;
                mystack.push(subStr);
            }
        }
        ++iter;
    }

    if(mystack.size() != 0)
    {
        result = calculateParsed(mystack.top());
    }
    return result;
}



int main()
{
    string input;
    while(1)
    {
        std::cout << "Please inputs a calculate string here, enter character 'E' or 'e' to exit: " << std::endl;
        getline(cin, input); //std::cin >> input;
        if((input == "E") || (input == "e"))
        {
            break;
        }
        std::cout << "input: "<< input << std::endl;
        long result = calculate(input);
        std::cout << "Result: " << result << std::endl;
    }

    return 0;
}

