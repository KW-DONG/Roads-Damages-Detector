#include "gtu7.h"
#include <vector>
#include <iostream>
#include <regex>

void GTU7::threadLoop()
{
    while (mRun) {
        getMessage();
    }
}

void GTU7::getMessage()
{
    if (mSerialCallback == nullptr) return;
    std::string data = receive();
    //std::cout << data << std::endl;
    std::vector<std::string> vStr;
    std::string delimiter = ",";
    size_t pos = data.find("$GPGLL");
    if (pos != std::string::npos)
    {
        std::string croppedStr = data.substr(pos, data.length());
        for (int i = 0; i < 5 && pos != std::string::npos; i++)
        {
            pos = croppedStr.find(delimiter);
            std::string sub = croppedStr.substr(0, pos);
            if (sub.size() == 0)
                return;
            std::cout << "sub: " << sub << std::endl;
            vStr.push_back(sub);
            croppedStr.erase(0, pos + delimiter.length());
        }

        std::cout << "Found" << vStr.size() << std::endl;
        double lat = vStr[2] == "N" ? std::stod(vStr[1]) : -std::stod(vStr[1]);
        double lon = vStr[4] == "W" ? std::stod(vStr[3]) : -std::stod(vStr[3]);
        std::cout << "latitude: " << lat << " longitude: " << lon << std::endl;
        mSerialCallback->next(lat, lon);
    }
}

void GTU7::start(std::string& portName)
{
    if (open(portName.c_str(),115200,0,8,1,1))
    {
        mThread = std::thread(&GTU7::threadLoop, this);
        mRun = true;
    }
}

void GTU7::stop()
{
    if (mRun == true)
    {
        mRun = false;
        mThread.join();
    }
}
