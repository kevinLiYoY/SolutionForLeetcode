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

//方法1，字符消耗法
/***********************************
    将正则表达式分解成 枚举：StrType中的类型, 然后依序使用分解得的正则规则将目标字串中的字符进行匹配，匹配上后从目标字串中去除，未匹配上则直接返回 false.
以此逐一消耗掉目标字串直至空,表明全部匹配成功。
***********************************/
class MyRegex
{
    enum StrType
    {
        eUnknown,
        eAllCharGreaterThan0,   //.*
        eACharGreaterThan0,     //x*
        eOneChar,               //.
        eStaticStr,             //abc
        eMax 
    };

    struct RegexStr
    {
        RegexStr(string characters, StrType strType)
            :m_characters(characters)
            ,m_strType(strType)
        {

        }
        string m_characters;
        StrType m_strType;
    };

    struct strDynamic
    {
        strDynamic(string characters, int regexSymbolIndex)
            :m_characters(characters)
            ,m_regexSymbolIndex(regexSymbolIndex)
        {

        }
        string m_characters;
        int m_regexSymbolIndex;
    };

public:
    MyRegex(string str)
        :m_regex(str)
    {
        getRegexSymbol();
    }

    bool isMatch(string strInput) //正则规则匹配
    {
        string::size_type curPosition = 0;
        bool bHasDynamic = false;
        string strTmp;
        std::stack<strDynamic> listStrDynamic;
        for(int i = 0; i < m_regexSymbol.size(); ++i) //第一轮匹配
        {
            switch(m_regexSymbol.at(i).m_strType)
            {
            case StrType::eAllCharGreaterThan0:
                bHasDynamic = true;
                if(i == (m_regexSymbol.size() - 1))
                {
                    strInput.clear();
                    return true;
                }
                break;
            case StrType::eACharGreaterThan0:
            {
                curPosition = strInput.find((m_regexSymbol.at(i).m_characters).at(0));
                if(curPosition != string::npos)
                {
                    if(!bHasDynamic)
                    {
                        if(curPosition != 0)
                        {
                            return false;
                        }
                    }
                
                    if((curPosition + 1) < strInput.size())
                    {
                        strInput = strInput.substr(curPosition + 1, (strInput.size() - curPosition - 1));
                    }
                    else
                    {
                        strInput.clear();
                        return true;
                    }
                    while((strInput.size() != 0) && (strInput.at(0) == (m_regexSymbol.at(i).m_characters).at(0)))
                    {
                        strInput = strInput.substr(1, (strInput.size() - 1));
                    }
                }
                if(bHasDynamic) //当前位置存在通配符，栈存所有可能的匹配位置
                {
                    strTmp = strInput;
                    while(1)
                    {
                        curPosition = strTmp.find((m_regexSymbol.at(i).m_characters).at(0));
                        if(curPosition != string::npos)
                        {
                            listStrDynamic.push(strDynamic(strTmp, i));
                            //std::cout << "listStrDynamic push: " << strTmp << " index: " << i << std::endl;
                            if((curPosition + 1) < strTmp.size())
                            {
                                strTmp = strTmp.substr(curPosition + 1, (strTmp.size() - curPosition - 1));
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                    bHasDynamic = false;
                }
                break;
            }
            case StrType::eOneChar:
            {
                if(bHasDynamic)
                {
                    break;
                }
                strInput = strInput.substr(1, (strInput.size() - 1));
                
                break;
            }
            case StrType::eStaticStr:
            {
                curPosition = strInput.find(m_regexSymbol.at(i).m_characters);
                if(!bHasDynamic)
                {
                    if(curPosition != 0)
                    {
                        return false;
                    }
                }
                
                if(curPosition == string::npos)
                {
                    if(!listStrDynamic.empty())
                    {
                        strDynamic strDic = listStrDynamic.top();
                        listStrDynamic.pop();
                        strInput = strDic.m_characters;
                        i = strDic.m_regexSymbolIndex;
                        continue;
                    }
                    return false;
                }

                if((curPosition + m_regexSymbol.at(i).m_characters.size()) < strInput.size())
                {
                    strInput = strInput.substr(curPosition + m_regexSymbol.at(i).m_characters.size(), (strInput.size() - curPosition - m_regexSymbol.at(i).m_characters.size()));
                }
                else
                {
                    strInput.clear();
                    return true;
                }

                if(bHasDynamic) //当前位置存在通配符，栈存所有可能的匹配位置
                {
                    strTmp = strInput;
                    while(1)
                    {
                        curPosition = strTmp.find(m_regexSymbol.at(i).m_characters);
                        if(curPosition != string::npos)
                        {
                            listStrDynamic.push(strDynamic(strTmp, i));
                            //std::cout << "listStrDynamic push: " << strTmp << " index: " << i << std::endl;
                            if((curPosition + 1) < strTmp.size())
                            {
                                strTmp = strTmp.substr(curPosition + 1, (strTmp.size() - curPosition - 1));
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                    bHasDynamic = false;
                }
                break;
            }
            default:
                break;
            }

            //std::cout << "strInput: " << strInput << " regexSymbol: " << m_regexSymbol.at(i).m_characters << " Type: " << m_regexSymbol.at(i).m_strType << std::endl;
        }

        if(!strInput.empty())
        {
            while(true) //第一轮未匹配成功，检索栈存中所有可能的匹配位置进行第二轮匹配尝试
            {
                if(listStrDynamic.empty())
                {
                    break;
                }
                strDynamic strDic = listStrDynamic.top();
                listStrDynamic.pop();
                strInput = strDic.m_characters;
                bHasDynamic = true;
                for(int i = strDic.m_regexSymbolIndex; i < m_regexSymbol.size(); ++i)
                {
                    switch(m_regexSymbol.at(i).m_strType)
                    {
                    case StrType::eAllCharGreaterThan0:
                        bHasDynamic = true;
                        if(i == (m_regexSymbol.size() - 1))
                        {
                            strInput.clear();
                            return true;
                        }
                        break;
                    case StrType::eACharGreaterThan0:
                    {
                        curPosition = strInput.find((m_regexSymbol.at(i).m_characters).at(0));
                        if(!bHasDynamic)
                        {
                            if(curPosition != 0)
                            {
                                return false;
                            }
                        }

                        if(curPosition != string::npos)
                        {
                            if((curPosition + 1) < strInput.size())
                            {
                                strInput = strInput.substr(curPosition + 1, (strInput.size() - curPosition - 1));
                            }
                            else
                            {
                                strInput.clear();
                                return true;
                            }
                            while((strInput.size() != 0) && (strInput.at(0) == (m_regexSymbol.at(i).m_characters).at(0)))
                            {
                                strInput = strInput.substr(1, (strInput.size() - 1));
                            }
                        }
                        if(bHasDynamic)
                        {
                            bHasDynamic = false;
                        }
                        break;
                    }
                    case StrType::eOneChar:
                    {
                        if(bHasDynamic)
                        {
                            break;
                        }
                        strInput = strInput.substr(1, (strInput.size() - 1));
                        
                        break;
                    }
                    case StrType::eStaticStr:
                    {
                        curPosition = strInput.find(m_regexSymbol.at(i).m_characters);
                        if(!bHasDynamic)
                        {
                            if(curPosition != 0)
                            {
                                return false;
                            }
                        }
                        
                        if(curPosition == string::npos)
                        {
                            if(!listStrDynamic.empty())
                            {
                                strDynamic strDic = listStrDynamic.top();
                                listStrDynamic.pop();
                                strInput = strDic.m_characters;
                                i = strDic.m_regexSymbolIndex;
                                continue;
                            }
                            return false;
                        }
                        if((curPosition + m_regexSymbol.at(i).m_characters.size()) < strInput.size())
                        {
                            strInput = strInput.substr(curPosition + m_regexSymbol.at(i).m_characters.size(), (strInput.size() - curPosition - m_regexSymbol.at(i).m_characters.size()));
                        }
                        else
                        {
                            strInput.clear();
                            return true;
                        }

                        if(bHasDynamic)
                        {
                            bHasDynamic = false;
                        }
                        break;
                    }
                    default:
                        break;
                    }

                    //std::cout << "***********strInput: " << strInput << " regexSymbol: " << m_regexSymbol.at(i).m_characters << " Type: " << m_regexSymbol.at(i).m_strType << std::endl;
                }
            }
            return false;
        }
        return true;
    }

private:
    void getRegexSymbol() //分解正则表达式规则
    {
        string strTmp;
        for (char c : m_regex)
        {
            if(isalpha(c))
            {
                if(!strTmp.empty() && !isalpha(strTmp.back()))
                {
                    StrType strType = getRegexType(strTmp);
                    m_regexSymbol.push_back(RegexStr(strTmp, strType));
                    
                    strTmp.clear();
                }
            }
            else if(c == '.')
            {
                if(!strTmp.empty())
                {
                    StrType strType = getRegexType(strTmp);
                    m_regexSymbol.push_back(RegexStr(strTmp, strType));
                    strTmp.clear();
                }
            }
            else
            {
                if(!strTmp.empty())
                {
                    char str = strTmp.back();
                    strTmp.pop_back();
                    if(!strTmp.empty())
                    {
                        StrType strType = getRegexType(strTmp);
                        m_regexSymbol.push_back(RegexStr(strTmp, strType));
                        strTmp.clear();
                    }
                    strTmp.push_back(str);
                }
            }
            strTmp.push_back(c);
        }
        if(!strTmp.empty())
        {
            StrType strType = getRegexType(strTmp);
            m_regexSymbol.push_back(RegexStr(strTmp, strType));
            strTmp.clear();
        }
    }

    StrType getRegexType(const string &strRegex) //获取分解得的正则规则类型
    {
        if(strRegex.empty())
        {
            return StrType::eUnknown;
        }

        if((strRegex.find('.') != string::npos) && (strRegex.find('*') != string::npos))
        { 
            return StrType::eAllCharGreaterThan0;
        }
        else if(strRegex.find('.') != string::npos)
        {
            return StrType::eOneChar;
        }
        else if(strRegex.find('*') != string::npos)
        {
            return StrType::eACharGreaterThan0;
        }

        return StrType::eStaticStr;
    }

private:
    string m_regex;
    std::vector<RegexStr> m_regexSymbol;
};

bool isMatch(string str, string regx)
{
    MyRegex myRegex(regx);
    bool result = myRegex.isMatch(str);
    return result;
}


int main()
{
    string input;
    string regex;
    while(1)
    {
        std::cout << "Please enter characters as a string, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        std::cout << "Please enter characters as Regex, input here: " << std::endl;
        getline(cin, regex);

        bool result = isMatch(input, regex);
        std::cout << "****************************************************Result: " << (result ? "true" : "false") << std::endl;

    }

    return 0;
}

