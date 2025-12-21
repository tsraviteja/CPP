#pragma once

#include <iostream>
#include <memory>

#include "IAdmin.h"
#include "IAuthentication.h"
#include "IChef.h"
#include "IEmployee.h"
#include "INotification.h"

namespace foodRecommendationEngine { namespace app { namespace client {

struct injection
{
    std::shared_ptr<foodRecommendationEngine::app::client::IAdmin> admin;
    std::shared_ptr<foodRecommendationEngine::app::client::IAutentication> authentication;
    std::shared_ptr<foodRecommendationEngine::app::client::IChef> chef;
    std::shared_ptr<foodRecommendationEngine::app::client::IEmployee> employee;
    std::shared_ptr<foodRecommendationEngine::app::client::INotification> notification;
};

}}} // namespace foodRecommendationEngine::app::client
