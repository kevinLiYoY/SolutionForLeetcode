#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <vector>
#include <cmath>

using namespace std;

struct BoardPos
{
    int mRow;
    int mCol;

    BoardPos()
        :mRow(0),
        mCol(0)
    {

    }

    BoardPos(int row, int col)
        :mRow(row),
        mCol(col)
    {

    }

    BoardPos& operator=(const BoardPos &otherPos)
    {
        if(this == &otherPos)
        {
            return *this;
        }
        this->mRow = otherPos.mRow;
        this->mCol = otherPos.mCol;
        return *this;
    }

    bool operator==(const BoardPos &otherPos)
    {
        if(this == &otherPos)
        {
            return true;
        }
        if((this->mRow == otherPos.mRow) && (this->mCol == otherPos.mCol))
        {
            return true;
        }
        return false;
    }
};

vector<BoardPos> findCharFirstPos(const vector<vector<char>>& board, char ch)
{
    vector<BoardPos> firstCharPos;
    for(int row = 0; row < board.size(); ++row)
    {
        for(int col = 0; col < board.at(row).size(); ++col)
        {
            if(board.at(row).at(col) == ch)
            {
                firstCharPos.push_back(std::move(BoardPos(row, col)));
            }
        }
    }
    return firstCharPos;
}

//start with the first pos to search all around, to check the next matched character pos.
bool searchWordTrack(const vector<vector<char>>& board, const BoardPos &firstPos, const string &word)
{
    BoardPos offset[4]; //the below order shall not change, if not so, the option calculate should change along with below order changes
    offset[0].mRow = 0; offset[0].mCol = 1;     //right
    offset[1].mRow = 1; offset[1].mCol = 0;     //down
    offset[2].mRow = 0; offset[2].mCol = -1;    //left
    offset[3].mRow = -1; offset[3].mCol = 0;    //up

    stack<BoardPos> posTrack;
    //std::cout << "iterFirstPos row: " << firstPos.mRow << " iterFirstPos col: " << firstPos.mCol << std::endl;
    BoardPos herePos(firstPos.mRow, firstPos.mCol);
    const int lastOption = 3;
    int option = 0;
    int jumpOption = -1;
    auto iter = word.begin();
    ++iter; //move to next character
    while((iter != word.end()) && ((herePos.mRow != board.size()) || (herePos.mCol != board.at(herePos.mRow).size())))
    {
        while((iter != word.end()) && (option <= lastOption))
        {
            if(option != jumpOption)
            {
                int row = herePos.mRow + offset[option].mRow;
                int col = herePos.mCol + offset[option].mCol;
                //std::cout << "herePos row: " << herePos.mRow << " , " << herePos.mCol << " move to " << row << " , " << col << std::endl;
                if(row < board.size() && col < board.at(row).size()) //check whether if the pos out of the board range
                {
                    if(board.at(row).at(col) == *iter)
                    {
                        herePos.mRow = row;
                        herePos.mCol = col;
                        posTrack.push(herePos);
                        //std::cout << "found option: "<< *iter << " pos: " << row << " , " << col << std::endl;
                        ++iter; //move to next character
                        break;
                    }
                }
            }
            ++option;
        }

        if(option <= lastOption) //found the matched character
        {
            switch (option)
            {
            case 0:
                jumpOption = 2; //from right, so ignore the next item left searching
                break;
            case 2:
                jumpOption = 0; //from left, so ignore the next item right searching
                break;
            case 1:
                jumpOption = 3; //from down, so ignore the next item up searching
                break;
            case 3:
                jumpOption = 1; //from up, so ignore the next item dpwn searching
                break;
            default:
                //do nothing
                break;
            }
            option = 0; //reset the option before next searching start
        }
        else
        {
            if(posTrack.empty())
            {
                return false;
            }
            BoardPos lastPos = posTrack.top();
            posTrack.pop();
            //std::cout << "@@@@@old option: " << option << std::endl;
            if(lastPos == herePos)
            {
                --iter; //track go back, so move to last character
                continue;
            }
            else if(lastPos.mRow == herePos.mRow)
            {
                option = 2 + lastPos.mCol - herePos.mCol;
            }
            else
            {
                option = 3 + lastPos.mRow - herePos.mRow;
            }
            //std::cout << "@@@@new option: " << option << std::endl;
            herePos = lastPos;
        }
    }
    return true;
}
  

//input the parsed substring and the board as reference, find the word from board, if found return true, otherwise return false;
bool findWordParsed(const vector<vector<char>>& board, const string &word)
{
    std::cout << "findWordParsed: " << word << std::endl;
    bool result =  false;
    auto iter = word.begin();
    vector<BoardPos> firstCharPos = findCharFirstPos(board, *iter);
    if(firstCharPos.size() == 0)
    {
        return false; //did not found first character match
    }

    auto iterFirstPos = firstCharPos.begin();
    while(iterFirstPos != firstCharPos.end()) //first character found
    {
        result = searchWordTrack(board, *iterFirstPos, word);
        if(result)
        {
            return true; //if found return the result, otherwise continue to check the next first pos.
        }
        ++iterFirstPos;
    }
    return false;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
{
    vector<string> items;
    auto iter = words.begin();
    while(iter != words.end())
    {
        bool result = findWordParsed(board, *iter);
        if(result)
        {
            items.push_back(*iter);
        }
        ++iter;
    }
    return items;
}


int main()
{
    string input;
    while(1)
    {
        std::cout << "Please inputs a character string here to trigger the test function, enter character 'E' or 'e' to exit: " << std::endl;
        getline(cin, input); //std::cin >> input;
        if((input == "E") || (input == "e"))
        {
            break;
        }

        //test case 1
        vector<vector<char>> board = 
        {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
        };

        vector<string> words = 
        {
            "oath",
            "aakl",
            "eatht",
            "aerv",
            "oeiiflvrenaa"
        };

        std::cout << "input: "<< input << std::endl;
        vector<string> items = findWords(board, words);

        auto iter = items.begin();
        while(iter != items.end())
        {
            std::cout << "****************************************************Result: " << *iter << std::endl;
            ++iter;
        }

        //test case 2
        board = 
        {
            {'n','a','a','n'},
            {'e','t','c','e'},
            {'i','g','k','r'},
            {'h','f','l','p'},
            {'n','a','a','n'},
            {'e','t','c','l'},
            {'i','p','l','r'},
            {'m','f','l','v'},
            {'n','a','a','n'},
            {'e','t','f','e'},
            {'i','g','k','r'},
            {'h','f','l','v'}
        };

        words = 
        {
            "oath",
            "aakl",
            "eatht",
            "aerv",
            "oeiiflvrenaa",
            "neihneimneihflvrenvrlnprenaa",
            "natgf",
            "lcte",
            "aatgf",
            "vrkfanvllct"
        };

        items = findWords(board, words);

        iter = items.begin();
        while(iter != items.end())
        {
            std::cout << "****************************************************Result: " << *iter << std::endl;
            ++iter;
        }
    }

    return 0;
}

