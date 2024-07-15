#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm> //std::all_of
#include <cctype> //std::isdigital

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

std::string calculate(std::string &first, std::string &second, std::string &op)
{
    long lFirst = stol(first);
    long lSecond = stol(second);
    long result = 0;

    if(op == "+")
    {
        result = lFirst + lSecond;
    }
    else if(op == "-")
    {
        result = lFirst - lSecond;
    }
    else if(op == "*")
    {
        result = lFirst * lSecond;
    }
    else if(op == "/")
    {
        result = lFirst / lSecond;
    }
    else
    {
        std::cout << "Operate did not support.";
    }

    return std::to_string(result);
}

int main()
{
    // string input;
    // while(1)
    // {
    //     std::cout << "Please inputs a calculate string here, enter character 'E' or 'e' to exit: " << std::endl;
    //     getline(cin, input); //std::cin >> input;
    //     if((input == "E") || (input == "e"))
    //     {
    //         break;
    //     }
    //     std::cout << "input: "<< input << std::endl;
    //     long result = calculate(input);
    //     std::cout << "Result: " << result << std::endl;
    // }

    std::string strInput("1+2*(1+(14+5*2)-3)+( 6 + 8 ) + 1");
    std::vector<std::string> valItem;
    std::string strTmp;
    auto it = strInput.begin();
    while(it != strInput.end())
    {
        if(std::isspace(*it))
        {
            ++it;
            continue;
        }
        
        if(std::isdigit(*it))
        {
            strTmp.push_back(*it);
            if(it + 1 == strInput.end())
            {
                valItem.push_back(strTmp);
                strTmp.clear();
            }
        }
        else
        {
            if(!strTmp.empty())
            {
                valItem.push_back(strTmp);
                strTmp.clear();
            }
            valItem.push_back(std::string(1, *it));
        }

        ++it;
    }

    std::map<std::string, uint16_t> perforce = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};
    std::stack<std::string> myStack;
    for(std::string &str : valItem)
    {
        if(std::all_of(str.begin(), str.end(), std::isdigit))
        {
            if(myStack.size() != 0)
            {
                auto item = perforce.find(myStack.top());
                if(item != perforce.end())
                {
                    std::string op = myStack.top();
                    myStack.pop();
                    std::string first = myStack.top();
                    if(item->second == 2)
                    {
                        std::string ret = calculate(first, str, myStack.top());
                    }
                }
            }
            else
            {
                myStack.push(str);
            }
        }
        else if(str == ")")
        {
            myStack.push(str);
        }
        else
        {
            myStack.push(str);
        }
        std::cout << "val:" << str << std::endl;
    }

    return 0;
}

