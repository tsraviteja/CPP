#pragma once

#include <iostream>

#include "UserDataType.h"

namespace DataType = foodRecommendationEngine::app::client::dataType;

namespace foodRecommendationEngine { namespace app { namespace client {

class INotification
{
public:
    virtual ~INotification() {}
    virtual std::string getNotification(const int &employeeId) = 0;
    virtual bool notifyEmployee(const DataType::NotificationType &notificationType,
                                const std::string &item) = 0;
    virtual bool deleteNotification(const int &employeeId) = 0; 
};

}}} // namespace foodRecommendationEngine::app::client
