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

vector<int> twoSum(vector<int>& nums, int target)
{
    vector<int> result;
    for(int i = 0; i < nums.size(); ++i)
    {
        int tmpI = nums.at(i);
        for(int j = i + 1; j < nums.size(); ++j)
        {
            if(nums.at(i) + nums.at(j) == target)
            {
                result.push_back(i);
                result.push_back(j);
                break;
            }
        }
    }
    return result;
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
        std::cout << "Please input an number for the target of two number sum." << std::endl;
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

        vector<int> items = twoSum(muns, k);
        auto iter = items.begin();
        while(iter != items.end())
        {
            std::cout << "****************************************************Result: " << *iter << std::endl;
            ++iter;
        }
    }

    return 0;
}

