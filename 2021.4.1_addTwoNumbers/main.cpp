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

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode *node = new ListNode();
    ListNode *curNode = nullptr;
    int nextVal = 0;
    while(l1 != nullptr || l2 != nullptr)
    {
        int val1 = 0;
        int val2 = 0;
        if(l1 != nullptr)
        {
            val1 = l1->val;
            l1 = l1->next;
        }
        if(l2 != nullptr)
        {
            val2 = l2->val;
            l2 = l2->next;
        }
        // std::cout << "v1: "<< val1 << " val2: " << val2 << " nextval: " << nextVal<< std::endl;
        int val = val1 + val2 + nextVal;
        nextVal = 0;
        if(val >= 10)
        {
            val = val - 10;
            nextVal = 1;
        }
        if(curNode == nullptr)
        {
            node->val = val;
            curNode = node;
        }
        else
        {
            curNode->next = new ListNode(val);
            curNode = curNode->next;
        }
    }

    if(nextVal != 0) //for the last num max of 10
    {
        curNode->next = new ListNode(nextVal);
        curNode = curNode->next;
    }
    return node;
}

int main()
{
    string input;
    while(1)
    {
        std::cout << "Please enter numbers which are separated by space to fill the lin1, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        stringstream strStream;
        strStream << input;
        int item = 0;
        ListNode* l1 = new ListNode();
        ListNode *curNode = nullptr;
        while(strStream >> item)
        {
            if(curNode == nullptr)
            {
                l1->val = item;
                curNode = l1;
            }
            else
            {
                curNode->next = new ListNode(item);
                curNode = curNode->next;
            }
        }

        std::cout << "Please enter numbers which are separated by space to fill the lin2, enter character 'E' or 'e' to exit, input here: " << std::endl;
        input.clear();
        getline(cin, input);
        if((input == "E") || (input == "e"))
        {
            break;
        }

        strStream.clear();
        strStream << input;
        item = 0;
        ListNode* l2 = new ListNode();
        curNode = nullptr;
        while(strStream >> item)
        {
            if(curNode == nullptr)
            {
                l2->val = item;
                curNode = l2;
            }
            else
            {
                curNode->next = new ListNode(item);
                curNode = curNode->next;
            }
        }

        ListNode *items = addTwoNumbers(l1, l2);
        while(items != nullptr)
        {
            std::cout << "****************************************************Result: " << items->val << std::endl;
            items = items->next;
        }
    }

    return 0;
}

