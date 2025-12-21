#pragma once
#include "IInstagramJonFileHandling.h"

class InstagramJsonFileHandling : public IInstagramJsomnFileHandling
{
public:
    nlohmann::ordered_json getInstagramJsonFileData(const std::string filename) override;
    bool writeInstagramJsonFileData(const std::string filename, nlohmann::ordered_json instagramJsonData) override;
};