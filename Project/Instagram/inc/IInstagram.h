#pragma once

class IInstagram
{
public:
    virtual bool signin() = 0;
    virtual bool signup() = 0;
    virtual bool forgotpassword() = 0;
};
