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


//insert and erase elements keep the order by minimum to maximum. Equivalent elements remain in list order. 
//before insert and erase elements should using the STL function list.sort() for sort elements first.
bool listInsertByOrder(const int insrtNum, const int eraseNum, list<int> &oderList)
{
    if(oderList.empty())
    {
        return false;
    }
    
    //std::cout << "insrtNum item: " << insrtNum << " erase item: " << eraseNum << std::endl;
    static bool bIsSorted = false;
    if(!bIsSorted)
    {
        //Sorts the elements of this list order
        oderList.sort();
        bIsSorted = true;
    }

    if(insrtNum == eraseNum)
    {
        return true;
    }

    bool bInserted = false;
    if(insrtNum <= oderList.front())
    {
        oderList.push_front(insrtNum);
        bInserted = true;
    }
    else if(insrtNum >= oderList.back())
    {
        oderList.push_back(insrtNum);
        bInserted = true;
    }

    bool bErased = false;
    auto iter = oderList.begin();
    while(iter != oderList.end())
    {
        //std::cout << "listInsertByOrder item: " << *iter << std::endl;
        if(*iter >= insrtNum && !bInserted)
        {
            iter = oderList.insert(iter, insrtNum);
            bInserted = true;
            //std::cout << "insert item: " << insrtNum << std::endl;
        }

        if(*iter == eraseNum && !bErased)
        {
            //std::cout << "erase item: " << *iter << std::endl;
            iter = oderList.erase(iter);
            bErased = true;
            continue;
        }
        ++iter;
    }
    return true;
}

vector<int> maxSlidingWindow(vector<int>& nums, int k)
{
    if((nums.empty()) || (k < 1) || (nums.size() < k))
    {
        std::cout << "Error: the input parameters do not meet the requirements" << std::endl;
    }

    queue<int> queueSliding;
    list<int> oderSliding;
    vector<int> maxResult;
    auto iter = nums.begin();
    while(iter != nums.end())
    {
        if(queueSliding.size() < k) //fully loaded the num into list and queue first;
        {
            queueSliding.push(*iter);
            oderSliding.push_back(*iter);
            if(queueSliding.size() == k)
            {
                oderSliding.sort();
                maxResult.push_back(oderSliding.back()); //the order of max is the last element in the list
                //std::cout << "push result item0: " << oderSliding.back() << std::endl;
            }
        }
        else
        {
            int toeraseNum = queueSliding.front();
            listInsertByOrder(*iter, toeraseNum, oderSliding);
            queueSliding.pop();
            queueSliding.push(*iter);
            maxResult.push_back(oderSliding.back()); //the order of max is the last element in the list
            //std::cout << "push result item: " << oderSliding.back() << std::endl;
        }
        ++iter; //sliding window move to next position
    }
    return maxResult;
}


int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter numbers which are separated by space to fill the num window, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
        break;
        }
        std::cout << "Please input a number for the width of sliding window." << std::endl;
        int k = 0;
        std::cin >> k;
        cin.ignore();

        stringstream strStream;
        strStream << input;
        int item = 0;
        vector<int> muns;
        while(strStream >> item)
        {
            muns.push_back(item);
            //std::cout << "pushback: "<< item << std::endl;
        }

        vector<int> items = maxSlidingWindow(muns, k);

        auto iter = items.begin();
        while(iter != items.end())
        {
            std::cout << "****************************************************Result: " << *iter << std::endl;
            ++iter;
        }
    }

    return 0;
}

