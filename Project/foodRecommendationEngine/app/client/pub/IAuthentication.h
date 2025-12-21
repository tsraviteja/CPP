#pragma once

#include <iostream>

#include "UserDataType.h"

namespace foodRecommendationEngine { namespace app { namespace client {

class IAutentication
{
public:
    /**
     * Destructor
     */
    virtual ~IAutentication() {}

    /**
     * @brief checks for correct user logged in or not
     * 
     * @param id [in] -user Id
     * @param password [in] - user password
     * @param userType [in] - user type enum
     * @return bool - true if valid user otherwise false
     */
    virtual bool login(const u_int32_t &id, const std::string &password, 
            const  foodRecommendationEngine::app::client::dataType::UserType &userType) = 0;

    /**
     * @brief logout the current user from activity
     * 
     * @param id [in] -user Id
     * @return bool - true if user logout successfully other wise false
     */
    virtual bool logout(const u_int32_t &id) = 0;
};

}}} // namespace foodRecommendationEngine::app::client
