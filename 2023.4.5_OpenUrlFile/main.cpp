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
#include <fstream>
#include <algorithm>
#include <limits.h>
#include <random>
#include <time.h>
#include <Windows.h>


using namespace std;

class SaveImgLocal
{
public:
    SaveImgLocal(std::string &pathUrlFile)
    :m_sPathUrlFile(pathUrlFile)
    ,m_vFileNames(std::vector<std::string>())
    {

    }

    ~SaveImgLocal()
    {

    }

    void writeImgLocal(const std::string &pathSave)
    {
        if(createFilesPath())
        {
            std::string urlPath;
            std::string localPath;
            for(std::string &strUrlFile : m_vFileNames)
            {
                urlPath = "start " + strUrlFile;
                system(urlPath.c_str());
                // ShellExecute(NULL, "open", (LPCWSTR)urlPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
            }
        }
    }

private:
    bool createFilesPath()
    {
        std::ifstream ssIn;
        ssIn.open(m_sPathUrlFile, std::ios::in);
        if(!ssIn.is_open())
        {
            return false;
        }

        std::string strLine;
        while(std::getline(ssIn, strLine))
        {
            m_vFileNames.push_back(strLine);
        }
        return true;
    }
private:
    std::string m_sPathUrlFile;
    std::vector<std::string> m_vFileNames;
};


int main()
{
    // std::string urlPath = "start https://api.zzzmh.cn/bz/v3/getUrl/604caf7f880511ebb6edd017c2d2eca229";
    // system(urlPath.c_str());

    std::string imgPath("D:/MyPersonalProject/SolutionForLeetcode/2023.4.5_OpenUrlFile/img.txt");
    SaveImgLocal saveImgLocal(imgPath);

    std::string sSavePath("D:/MyPersonalProject/SolutionForLeetcode/2023.4.5_OpenUrlFile/imgSave");
    saveImgLocal.writeImgLocal(sSavePath);
    return 0;
}

