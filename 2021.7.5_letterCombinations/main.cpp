#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <cmath>
#include <map>
#include <sstream>
#include <algorithm>
#include <limits.h>

using namespace std;

//方法1, 构造递归找出所有组合
class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        vector<string> result;
        if(digits.empty())
        {
            return result;
        }
        reset();
        pickList(digits, result);
        return result;
    }

private:
    std::map<char, string> g_table = 
    {
        {'0',     ""},
        {'1',     ""},
        {'2',     "abc"},
        {'3',     "def"},
        {'4',     "ghi"},
        {'5',     "jkl"},
        {'6',     "mno"},
        {'7',     "pqrs"},
        {'8',     "tuv"},
        {'9',     "wxyz"}
    };

    void pickList(string digits, vector<string> &result) //构造递归
    {
        //std::cout<< "m_index:" << m_index << " digit:" << digits.at(m_index) << std::endl;
        if(m_index < (digits.size() - 1))
        {
            std::map<char, string>::iterator iterTab = g_table.find(digits.at(m_index));
            if(iterTab != g_table.end())
            {
                string characters = iterTab->second;
                //std::cout<< "character0:" << characters << std::endl;
                for(int i = 0; i < characters.size(); ++i)
                {
                    m_strResult.push_back(characters.at(i));
                    //std::cout<< "char0:" << characters.at(i) << " m_strResult:" << m_strResult << std::endl;
                    ++m_index;
                    pickList(digits, result);
                }
                if(!m_strResult.empty())
                {
                    m_strResult.pop_back();
                }
                if(m_index >= 1)
                {
                    --m_index;
                }
            }
        }
        else if(m_index == (digits.size() - 1))
        {
            std::map<char, string>::iterator iterTab = g_table.find(digits.at(m_index));
            if(iterTab != g_table.end())
            {
                string characters = iterTab->second;
                //std::cout<< "character1:" << characters << std::endl;
                string strTmp;
                for(int i = 0; i < characters.size(); ++i)
                {
                    strTmp = m_strResult;
                    strTmp.push_back(characters.at(i));
                    result.push_back(strTmp);
                    //std::cout<< "char1:" << characters.at(i) << " strTmp:" << strTmp << std::endl;
                }
                if(!m_strResult.empty())
                {
                    m_strResult.pop_back();
                }
                if(m_index >= 1)
                {
                    --m_index;
                }
            }
        }
        else
        {
            reset();
        }
    }

    void reset()
    {
        m_index = 0;
        m_strResult.clear();
    }

    int m_index = 0;
    string m_strResult;
};



int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter integer separated by space, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }
        Solution solution;
        std::vector<string> result = solution.letterCombinations(input);
        std::cout << "****************************************************Result: " << std::endl;
        auto iter = result.begin();
        while(iter != result.end())
        {
            std::cout << *iter << ", ";
            ++iter;
        }
        std::cout << std::endl;
    }

    return 0;
}

