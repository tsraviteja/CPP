#include "Notification.h"

#include "Logger.h"

using Logger = foodRecommendationEngine::framework::logger::Logger;
using RequestType = foodRecommendationEngine::app::server::RequestType;
using StatusCode = foodRecommendationEngine::app::server::StatusCode;

namespace foodRecommendationEngine{ namespace app { namespace client {


Notification::Notification(std::shared_ptr<IHandler> handler) : handler_(handler)
{
    Logger::debug("Notification::Notification - constructed");
}


std::string Notification::getNotification(const int &employeeId)
{
    Logger::debug("Notification::getNotification - entering");
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;
    requestMessage.query = "select message from Notification where employeeId = " + std::to_string(employeeId);
    auto response = handler_->handleRequest(requestMessage);
    std::string notificationMessage = "";
    if (response["status_code"] == StatusCode::OK)
    {
        setResponse(notificationMessage, response);
    }
    Logger::debug("Notification::getNotification - exiting");
    return notificationMessage;
}

void Notification::setResponse(std::string  &response, const nlohmann::ordered_json &jsondata)
{
    Logger::debug("Notification::setResponse - entering");
    if (jsondata.contains("body"))
    {
        for (const auto &message : jsondata["body"])
        {
            response += message["message"];
            response += "\n";
        }
    }
    Logger::debug("Notification::setResponse - exiting");
}

bool Notification::notifyEmployee(const dataType::NotificationType &notificationType,
                        const std::string &item)
{
    Logger::debug("Notification::notifyEmployee - entering");
    auto notificationMessage = getNotificationMessage(notificationType, item);
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::POST;
    auto result = false;
    auto allEmployeeId = getAllEmployeeId();
    if (allEmployeeId.contains("body"))
    {
        for (const auto &employeeId : allEmployeeId["body"])
        {
            int id = employeeId["id"];
            requestMessage.query = "insert into Notification values(" + std::to_string(id) + ",'" + notificationMessage + "')";
            auto response = handler_->handleRequest(requestMessage);
            if (response["status_code"] == StatusCode::CREATED)
            {
                result = true;
            }
        }
    }
    Logger::debug("Notification::notifyEmployee - exiting");
    return result;
}

bool Notification::deleteNotification(const int &employeeId)
{
    Logger::debug("Notification::deleteNotification - entering");
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::DELETE;
    requestMessage.query = "delete from Notification where employeeId = " + std::to_string(employeeId);
    auto response = handler_->handleRequest(requestMessage);
    auto result = false;
    if (response["status_code"] == StatusCode::OK)
    {
        result = true;
    }
    Logger::debug("Notification::deleteNotification - exiting");
    return result;
}

nlohmann::ordered_json Notification::getAllEmployeeId()
{
    Logger::debug("Notification::getEmployeeId - entering");
    Server::RequestMessage requestMessage;
    requestMessage.type = RequestType::GET;
    requestMessage.query = "select id from User where role = 'Employee'";
    nlohmann::ordered_json allEmployeeId;
    auto response = handler_->handleRequest(requestMessage);
    if (response["status_code"] == StatusCode::OK)
    {
        allEmployeeId = response;
    }
    Logger::debug("Notification::getEmployeeId - exiting");
    return allEmployeeId;
}

std::string Notification::getNotificationMessage(const dataType::NotificationType &notificationType,
                                    const std::string &item)
{
    Logger::debug("Notification::getNotificationMessage - entering");
    std::string notificationMessage;

    if (notificationType == dataType::NotificationType::ITEM_ADDED)
    {
        notificationMessage = "Item " +item + " is added into the menu";
    }
    else if (notificationType == dataType::NotificationType::ITEM_UPDATED)
    {
        notificationMessage = "Item " + item + " is updated in menu please check";
    }
    else if (notificationType == dataType::NotificationType::ITEM_DELETED)
    {
        notificationMessage = "Item " + item + " is deleted in menu please check";
    }

    Logger::debug("Notification::getNotificationMessage - exiting");
    return notificationMessage;
} 

}}} // namespace foodRecommendationEngine::app::client
