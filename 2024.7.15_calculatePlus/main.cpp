#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include <algorithm> //std::all_of
#include <cctype> //std::isdigital

using namespace std;

std::string calculate(std::string &first, std::string &second, std::string &op)
{
    // std::cout << "first:" << first << ", second:" << second << ", op:" << op << std::endl;
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
        std::cout << "Operate: " << op << " did not support.";
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

    // std::string strInput("1+2*(1+(14+5*2)-3)+( 6 + 8 ) + 1");
    // std::string strInput("1 + 2 * ( 12 * ( 3 * (5 * 2 + 2 * 2) - 3 )) + ( 3 * 6 * 1 - 2 ) * ( 2 + 2) + 1"); //括号内优先级暂未处理
    std::string strInput("1 + 2 * ( 12 * ( 3 * ( 5 * 2 + 2 * 2 ) ) ) + ( 3 * 6 * 1 - 2 ) * ( 2 + 2) + 1");
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

    std::map<std::string, uint16_t> precedence = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}};
    std::stack<std::string> myStack;
    for(std::string &str : valItem)
    {
        std::cout << "itemVal:" << str << std::endl;
        if(std::all_of(str.begin(), str.end(), ::isdigit))
        {
            if(myStack.size() != 0)
            {
                auto item = precedence.find(myStack.top());
                if(item != precedence.end())
                {
                    std::string op = myStack.top();
                    if(item->second == 2) //高优先级先处理，低优先级待后续运算符解释后再决定是否执行运送，例如运输式：1+2*3，需解析到2*3先执行运输
                    {
                        myStack.pop();
                        std::string first = myStack.top(); //已排除以下情形：（1+2）+3，（1+2）+（3+2），（2+3）*（3+2），此时top一定是数字
                        myStack.pop();
                        std::cout << "000 first:" << first << ", second:" << str << ", op:" << op << std::endl;
                        std::string res = calculate(first, str, op);
                        std::cout << "000 res:" << res << std::endl;
                        myStack.push(res); //运算结果先放回待运输栈中
                    }
                    else
                    {
                        myStack.push(str); //低优先级运输式暂不处理
                    }
                }
                else
                {
                    myStack.push(str); //非运输符或低优先级运输式暂不处理
                }
            }
            else
            {
                myStack.push(str); //待运输栈中无运输符暂不处理
            }
        }
        else if(str == ")") //遇右括号，需将括号内容优先完整运算
        {
            if(myStack.size() != 0)
            {
                while(myStack.top() != "(") //直至找到左括号退出
                {
                    std::string second = myStack.top(); //此时top一定是数字
                    myStack.pop();
                    std::string op = myStack.top(); //一定是运算式
                    myStack.pop();
                    std::string first = myStack.top(); //此时top一定是数字
                    myStack.pop();
                    std::cout << "111 first:" << first << ", second:" << second << ", op:" << op << std::endl;
                    std::string res = calculate(first, second, op);
                    std::cout << "111 res:" << res << std::endl;
                    if(myStack.top() == "(")
                    {
                        myStack.pop(); //移除左括号
                        myStack.push(res); //运算结果先放回待运输栈中
                        break;
                    }
                    else
                    {
                        myStack.push(res); //运算结果先放回待运输栈中
                    }
                }
            }
        }
        else
        {
            myStack.push(str); //低优先级运算值，运算符及左括号暂存入待运算栈中
        }
    }

    // while(myStack.size() != 0)
    // {
    //     std::cout << "top:" << myStack.top() << std::endl;
    //     myStack.pop();
    // }

    std::stack<std::string> stackReversed;
    while(myStack.size() != 0)
    {
        std::string second = myStack.top();
        myStack.pop();
        if(myStack.size() == 0)
        {
            stackReversed.push(second); //待运算栈反向
            break;
        }
        std::string op = myStack.top(); //一定是运算式
        myStack.pop();
        auto item = precedence.find(op);
        if(item != precedence.end())
        {
            if(item->second == 2) //高优先级先处理，低优先级待后续运算符解释后再决定是否执行运算，例如运输式：1+2*3，需解析到2*3先执行运输
            {
                std::string first = myStack.top(); //此时top一定是数字
                myStack.pop();
                std::cout << "222 first:" << first << ", second:" << second << ", op:" << op << std::endl;
                std::string res = calculate(first, second, op);
                std::cout << "222 res:" << res << std::endl;
                myStack.push(res);
                continue;
            }
        }
        stackReversed.push(second); //待运算栈反向
        stackReversed.push(op);
    }

    // while(stackReversed.size() != 0)
    // {
    //     std::cout << "top:" << stackReversed.top() << std::endl;
    //     stackReversed.pop();
    // }

    //高优先级已处理，此处按顺序执行运算
    while(stackReversed.size() > 1)
    {
        std::string first = stackReversed.top();
        stackReversed.pop();
        std::string op = stackReversed.top(); //一定是运算式
        stackReversed.pop();
        std::string second = stackReversed.top();
        stackReversed.pop();
        std::cout << "333 first:" << first << ", second:" << second << ", op:" << op << std::endl;
        std::string res = calculate(first, second, op);
        std::cout << "333 res:" << res << std::endl;
        stackReversed.push(res);
    }

    long result = stol(stackReversed.top());
    std::cout << "result:" << result << std::endl;

    return 0;
}

