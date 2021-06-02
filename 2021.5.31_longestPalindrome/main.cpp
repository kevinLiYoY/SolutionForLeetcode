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

//方法1：中心拓展法。

//方法2： 使用动态规划，完成最大回文扫描。

pair<int, int> expandAroundCenter(const string& s, int left, int right)
{
    while (left >= 0 && right < s.size() && s[left] == s[right])
    {
        --left;
        ++right;
    }
    return {left + 1, right - 1};
}

string longestPalindrome(string strInput)
{
    int start = 0, end = 0;
    for (int i = 0; i < strInput.size(); ++i)
    {
        auto [left1, right1] = expandAroundCenter(strInput, i, i);  //取一个字符开始向两边扩展，应对有对称中心的情形，例如如下字符中的‘d’: ada
        auto [left2, right2] = expandAroundCenter(strInput, i, i + 1);  //取两个相邻字符开始向两边扩展，应对无对称中心情形，例如如下字符：abba
        if (right1 - left1 > end - start)
        {
            start = left1;
            end = right1;
        }
        if (right2 - left2 > end - start)
        {
            start = left2;
            end = right2;
        }
    }
    return strInput.substr(start, end - start + 1);
}

//动态规划方法，取自解答，用于学习
string longestPalindrome2(string strInput)
{
    const size_t len = strInput.size();
    if(len < 2)
    {
        return strInput;
    }

    int maxLen = 1;
    int begin = 0;
    // dp[i][j] 表示 s[i..j] 是否是回文串
    vector<vector<int>> dp(len, vector<int>(len));
    // 初始化：所有长度为 1 的子串都是回文串
    for (int i = 0; i < len; ++i)
    {
        dp[i][i] = true;
    }
    // 递推开始
    // 枚举子字串，长度2~len，枚举自底向顶，保证迭代依赖值已知
    for (int L = 2; L <= len; ++L) 
    {
        // i 枚举左边界, j 枚举右边界；循环枚举当前子串长度中所有可能的回文，即区间[i, ]
        for (int i = 0; i < len; ++i)
        {
            // 由 L 和 i 可以确定右边界，即 j - i + 1 = L 得，维持总长度为子串长度
            int j = L + i - 1;
            // 如果右边界越界，就可以退出当前循环
            if (j >= len) 
            {
                break;
            }

            if (strInput[i] != strInput[j])
            {
                dp[i][j] = false;
            }
            else
            {
                if (j - i < 3)
                {
                    dp[i][j] = true;
                }
                else 
                {
                    dp[i][j] = dp[i + 1][j - 1];
                }
            }

            // 只要 dp[i][L] == true 成立，就表示子串 s[i..L] 是回文，此时记录回文长度和起始位置
            if (dp[i][j] && j - i + 1 > maxLen)
            {
                maxLen = j - i + 1;
                begin = i;
            }
        }
    }
    return strInput.substr(begin, maxLen);
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

        string longest = longestPalindrome(input);
        std::cout << "****************************************************Result: " << longest << std::endl;

        longest = longestPalindrome2(input);
        std::cout << "****************************************************Result2: " << longest << std::endl;
    }

    return 0;
}

