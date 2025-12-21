#include "InstagramJsonFileHandling.h"
#include <fstream>
#include <ostream>

nlohmann::ordered_json InstagramJsonFileHandling::getInstagramJsonFileData(const std::string filename)
{
    nlohmann::ordered_json instagramJsonData = "{}";

    std::ifstream inputFile(filename);
    if (inputFile.is_open())
    {
        inputFile >> instagramJsonData;
    }
    return instagramJsonData;
}

bool InstagramJsonFileHandling::writeInstagramJsonFileData(const std::string filename, nlohmann::ordered_json instagramJsonData)
{
    std::ofstream inputFile(filename);
    bool fileWritingStatus = false;

    if (inputFile.is_open())
    {
        inputFile << std::setw(4) << instagramJsonData;
        fileWritingStatus = true;
    }
    return fileWritingStatus;
}
