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
#include <random>
#include <time.h>
#include <Windows.h>


using namespace std;

//方法1, 构造红球、篮球摇号器
class RandomCreater
{
public:
    RandomCreater(int min, int max)
    {
        for(int i = min; i <= max; ++i) //构造范围内可选球编号
        {
            m_numBlock.push_back(i);
        }
    }

    ~RandomCreater()
    {
        m_numBlock.clear();
    }

    int getRandomNum()
    {
        int index = createRandomNum(0, m_numBlock.size() - 1); //创建随机index
        // std::cout << "index:" << index << " count:" << m_numBlock.size() << std::endl;
        int i = 0;
        int num = 0;
        std::list<int>::iterator iter = m_numBlock.begin();
        while(iter != m_numBlock.end())
        {
            if(i == index)
            {
                num = *iter;
                iter = m_numBlock.erase(iter); //抽取列表中index对应的值，并从列表中移除
                // if(iter == m_numBlock.end())
                // {
                //     break;
                // }
                break;
            }
            ++i;
            ++iter;
        }
        return num;
    }

private:
    int createRandomNum(int rangeMin, int rangeMax)
    {
        std::uniform_int_distribution<int> uRandom(rangeMin, rangeMax);
        std::default_random_engine eng(static_cast<unsigned int>(time(nullptr)));
        return uRandom(eng);
    }
private:
    std::list<int> m_numBlock; 
};



int main()
{
    std::vector<int> redResult;
    std::stringstream ss;
    for(int i = 0; i < 10; ++i) //创建10组随机数
    {
        RandomCreater redRandomCreater(1, 33);
        RandomCreater blueRandomCreater(1, 16);

        redResult.clear();
        for(int m = 0; m < 7; ++m) //创建6个红球
        {
            int red = redRandomCreater.getRandomNum();
            redResult.push_back(red);
            Sleep(125);
        }

        std::sort(redResult.begin(), redResult.end()); //排序

        ss.clear();
        ss.str("");
        std::vector<int>::const_iterator iter = redResult.begin();
        while(iter != redResult.end())
        {
            ss << *iter;
            if(iter != redResult.end() - 1)
            {
                ss << " ";
            }
            else
            {
                ss << "*";
            }
            ++iter;
        }

        for(int n = 1; n < 2; ++n) //创建1个蓝球
        {
            Sleep(125);
            int blue = blueRandomCreater.getRandomNum();
            ss << blue;
        }

        std::cout << ss.str() << std::endl;
    }

    return 0;
}

