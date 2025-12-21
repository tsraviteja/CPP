#pragma once
#include "nlohmann/json.hpp"

class IInstagramJsomnFileHandling
{
public:
    virtual nlohmann::ordered_json getInstagramJsonFileData(const std::string filename) = 0;
    virtual bool writeInstagramJsonFileData(const std::string filename, nlohmann::ordered_json instagramJsonData) = 0;
};
