#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>

using namespace std;

//采用拓片重叠法，每次将一个建筑物叠加到已存在的天际线投影上，运算出当前的天际线结果，直至所有建筑物都运算完成。

class Build
{
public:
    Build(long left, long right, long height)
        :mLeft(left)
        ,mRight(right)
        ,mHeight(height)
    {

    }
    
    ~Build()
    {

    }

    Build& operator=(const Build &otherBuild)
    {
        if(this == &otherBuild)
        {
            return *this;
        }
        this->mLeft = otherBuild.mLeft;
        this->mRight = otherBuild.mRight;
        this->mHeight = otherBuild.mHeight;
        return *this;
    }

    bool operator<(const Build &otherBuild)
    {
        return this->mLeft <= otherBuild.mLeft;
    }

    bool operator>(const Build &otherBuild)
    {
        return this->mLeft >= otherBuild.mLeft;
    }

    inline int getLeftX()
    {
        return mLeft;
    }

    inline int getRightX()
    {
        return mRight;
    }

    inline int getHeight()
    {
        return mHeight;
    }

private:
    int mLeft;
    int mRight;
    int mHeight;
};

//return sorted build list
vector<Build> buildingsParse(vector<vector<int>>& buildings)
{
    vector<Build> buildList;
    auto iter = buildings.begin();
    while(iter != buildings.end())
    {
        if((*iter).size() != 3)
        {
            std::cout << "buildingsParse: with error size, break parse" << std::endl;
            break;
        }

        int leftX = (*iter).at(0);
        int rightX = (*iter).at(1);
        int height = (*iter).at(2);
        std::cout << "buildingsParse: create build:" << leftX <<"," << rightX <<"," << height << std::endl;
        buildList.emplace_back(leftX, rightX, height);
        ++iter;
    }
    std::sort(buildList.begin(), buildList.end());
    return std::move(buildList);
}

vector<vector<int>> getSkyline(vector<vector<int>>& buildings)
{
    vector<Build> builds = buildingsParse(buildings);
    list<vector<int>> resultList;

    for(int i = 0; i < builds.size(); ++i)
    {
        Build temp1 = builds.at(i);
        int leftX = temp1.getLeftX();
        int height = temp1.getHeight();
        int rightX = temp1.getRightX();
        // std::cout << "getSkyline build: " << leftX <<"," << rightX <<"," << height << std::endl;

        list<vector<int>>::iterator iter = resultList.begin();
        static int curHeight = 0;
        bool bFondOverlapping = false;
        while(iter != resultList.end()) //loop all the current pos
        {
            // std::cout << "current pos:" << (*iter).at(0) <<"," << (*iter).at(1) << std::endl;
            if(leftX <= (*iter).at(0)) //has overlapping
            {
                bFondOverlapping = true;
                if((*iter).at(1) != 0) //not the last pos of current sky line
                {
                    if(height > (*iter).at(1))
                    {
                        if(rightX < (*iter).at(0))
                        {
                            vector<int> vecTmp = {leftX, height};
                            resultList.insert(iter, vecTmp);
                            // std::cout << "push_back pos 4.0:" << leftX <<"," << height << std::endl;
                            vector<int> vecTmp1 = {rightX, curHeight};
                            resultList.insert(iter, vecTmp1);
                            // std::cout << "push_back pos 4.1:" << rightX <<"," << curHeight << std::endl;
                        }
                        else
                        {
                            (*iter).at(1) = height;
                            curHeight = height;
                            // std::cout << "replace pos 4.2:" << (*iter).at(0) <<"," << height << std::endl;
                        }
                    }
                    else
                    {
                        //the height less than current height, which does not affect the sky line, do nothing
                    }
                }
                else //the last pos of current sky line
                {
                    if(rightX >= (*iter).at(0))
                    {
                        if(height < curHeight)
                        {
                            vector<int> vecTmp = {(*iter).at(0), height};
                            resultList.insert(iter, vecTmp);
                            curHeight = height;
                            // std::cout << "push_back pos 3.0:" << (*iter).at(0) <<"," << height << std::endl;
                        }
                        else if (height > curHeight)
                        {
                            vector<int> vecTmp = {leftX, height};
                            resultList.insert(iter, vecTmp);
                            curHeight = height;
                            // std::cout << "push_back pos 3.1:" << (*iter).at(0) <<"," << height << std::endl;
                        }

                        (*iter).at(0) = rightX;
                        // std::cout << "replace pos 3.2:" << rightX <<"," << 0 << std::endl;
                    }
                    else
                    {
                        if(height > curHeight)
                        {
                            vector<int> vecTmp = {leftX, height};
                            resultList.insert(iter, vecTmp);
                            // std::cout << "push_back pos 3.3:" << leftX <<"," << height << std::endl;

                            vector<int> vecTmp1 = {rightX, curHeight};
                            resultList.insert(iter, vecTmp1);
                            // std::cout << "push_back pos 3.4:" << rightX <<"," << curHeight << std::endl;
                        }
                    }
                }
            }
            ++iter;
        }

        if(!bFondOverlapping) //not found any the overlapping pos, so create a new sky line.
        {
            vector<int> vecTmp = {leftX, height};
            resultList.push_back(std::move(vecTmp));
            curHeight = height;
            // std::cout << "push_back pos 1:" << leftX <<"," << height << std::endl;
            vecTmp = {rightX, 0};
            resultList.push_back(std::move(vecTmp));
            // std::cout << "push_back pos 2:" << rightX <<"," << 0 << std::endl;
        }
    }
    
    vector<vector<int>> result;
    std::copy(resultList.begin(), resultList.end(), std::back_inserter(result));
    return result;
}


int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter numbers which are separated by space to fill the builds, enter character 'E' or 'e' to exit: " << std::endl;
        getline(cin, input); //std::cin >> input;
        if((input == "E") || (input == "e"))
        {
            break;
        }

        stringstream strStream;
        strStream << input;
        int item = 0;
        vector<int> muns;
        vector<vector<int>> buildings;
        int index = 0;
        while(strStream >> item)
        {
            muns.push_back(item);
            ++index;
            if(index % 3 == 0)
            {
                index = 0;
                buildings.push_back(muns);
                muns.clear();
            }
        }
        
        std::cout << "input: "<< input << std::endl;
        vector<vector<int>> result = getSkyline(buildings);
        auto iter = result.begin();
        while(iter != result.end())
        {
            std::cout << "****************************************************Result X: " << (*iter).at(0) << ", Y: " << (*iter).at(1) << std::endl;
            ++iter;
        }
    }

    return 0;
}

