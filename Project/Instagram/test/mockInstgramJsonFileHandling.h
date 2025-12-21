#pragma once
#include <gmock/gmock.h>
#include <iostream>
#include "nlohmann/json.hpp"
#include "InstagramJsonFileHandling.h"

class MockInstagramJsonFileHandling : public InstagramJsonFileHandling
{
public:
    MOCK_METHOD(nlohmann::ordered_json, getInstagramJsonFileData, (const std::string), (override));
    MOCK_METHOD(bool, writeInstagramJsonFileData, (const std::string, nlohmann::ordered_json), (override));
};
