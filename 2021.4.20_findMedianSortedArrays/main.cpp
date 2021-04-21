#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

//方法1：检索数组1， 将数组2依数字大小顺序插入到数组1中直至中位数index，输出此index对应的数字。

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
{
    double result = 0.0;
    if((nums1.empty()) && (nums2.empty()))
    {
        //std::cout << "Error: the input parameters do not meet the requirements" << std::endl;
        return result;
    }

    if(nums1.empty())
    {
        int count = nums2.size();
        int index = count / 2;
        if((count % 2) == 0)
        {
            result = (nums2.at(index) + nums2.at(--index)) / 2;
        }
        else
        {
            result = nums2.at(index);
        }
        return result;
    }

    if(nums2.empty())
    {
        int count = nums1.size();
        int index = count / 2;
        if((count % 2) == 0)
        {
            result = (nums1.at(index) + nums1.at(--index)) / 2;
        }
        else
        {
            result = nums1.at(index);
        }
        return result;
    }

    int count = nums1.size() + nums2.size();
    int index = count / 2;
    int curIndex = 0;
    int pos1 = 0;
    int pos2 = 0;
    auto iter = nums1.begin();
    auto iter2 = nums2.begin();
    while((iter != nums1.end()) || (iter2 != nums2.end()))
    {
        //std::cout << " iter: " << *iter << " iter2: " << *iter2 << " curIndex: " << curIndex << std::endl;
        if((iter != nums1.end()) && (iter2 != nums2.end()))
        {
            if(*iter > *iter2) 
            {
                if((curIndex == (index - 1)) && ((count % 2) == 0))
                {
                    pos1 = *iter2;
                }

                if(curIndex == index)
                {
                    pos2 = *iter2;
                    break;
                }
                ++iter2;
            }
            else
            {
                if((curIndex == (index - 1)) && ((count % 2) == 0))
                {
                    pos1 = *iter;
                }

                if(curIndex == index)
                {
                    pos2 = *iter;
                    break;
                }
                ++iter; //move to next position
            }
        }
        else if(iter == nums1.end())
        {
            if((curIndex == (index - 1)) && ((count % 2) == 0))
            {
                pos1 = *iter2;
            }

            if(curIndex == index)
            {
                pos2 = *iter2;
                break;
            }
            ++iter2;
        }
        else
        {
            if((curIndex == (index - 1)) && ((count % 2) == 0))
            {
                pos1 = *iter;
            }

            if(curIndex == index)
            {
                pos2 = *iter;
                break;
            }
            ++iter; //move to next position
        }
        ++curIndex;
    }

    if((count % 2) == 0)
    {
        result = (double)(pos1 + pos2) / 2;
    }
    else
    {
        result = pos2;
    }
    return result;
}


int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter numbers which are separated by space to fill the nums1, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        stringstream strStream;
        strStream << input;
        int item = 0;
        vector<int> muns1;
        while(strStream >> item)
        {
            muns1.push_back(item);
            //std::cout << "pushback: "<< item << std::endl;
        }

        std::cout << "Please enter numbers which are separated by space to fill the nums2, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        strStream.clear();
        strStream << input;
        item = 0;
        vector<int> muns2;
        while(strStream >> item)
        {
            muns2.push_back(item);
            //std::cout << "pushback: "<< item << std::endl;
        }

        double result = findMedianSortedArrays(muns1, muns2);
        std::cout << "****************************************************Result: " << result << std::endl;
        
    }

    return 0;
}

