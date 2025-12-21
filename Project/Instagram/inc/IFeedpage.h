#pragma once
#include <iostream>

struct PostInfo
{
    std::string post, posterName;
};

class IFeedpage
{
public:
    virtual PostInfo moveToNextPost() = 0;
    virtual PostInfo moveBackToPreviousPost() = 0;
    virtual bool likePost(PostInfo postData) = 0;
    virtual PostInfo firtPostInInstagram() = 0;
};
