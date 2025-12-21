#pragma once

#include "INotification.h"

#include "Handler.h"

namespace foodRecommendationEngine { namespace app { namespace client {

class Notification : public INotification
{
public:
    explicit Notification(std::shared_ptr<IHandler> handler);

    std::string getNotification(const int &employeeId) override;
    bool notifyEmployee(const DataType::NotificationType &notificationType,
                        const std::string &item) override;
    bool deleteNotification(const int &employeeId) override;

    nlohmann::ordered_json getAllEmployeeId();
    std::string getNotificationMessage(const dataType::NotificationType &notificationType,
                                       const std::string &item); 
    void setResponse(std::string  &response, const nlohmann::ordered_json &jsondata);

private:
    std::shared_ptr<IHandler> handler_;
};

}}} // namespace foodRecommendationEngine::app::client