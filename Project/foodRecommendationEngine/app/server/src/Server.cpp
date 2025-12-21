#include <fstream>
#include <iostream>
#include <ostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <thread>

#include "Logger.h"
#include "nlohmann/json.hpp"
#include "Mysql.h"
#include "ServerDataType.h"
#include "Utility.h"

#define PORT 8080
#define BUFFER_SIZE 1024

const std::string dbDetailsFilePath = "../app/server/standard/resource/dbDetails.json";
MYSQL *dbConnector;

using Logger = foodRecommendationEngine::framework::logger::Logger;
using Mysql = foodRecommendationEngine::app::server::Mysql;
using RequestType = foodRecommendationEngine::app::server::RequestType;
using StatusCode = foodRecommendationEngine::app::server::StatusCode;
using Utility = foodRecommendationEngine::framework::core::Utility;

void deleteRequest(const int &client_socket, const std::string &query)
{
    Logger::debug("Server::deleteRequest - entering");
    nlohmann::ordered_json response;

    if (mysql_query(dbConnector, query.c_str()))
    {
        Logger::error("Failed to execute query: " + query);
        response["status_code"] = StatusCode::BAD_REQUEST;
        response["error_message"] = "Failed execute the delete request";
    }
    else
    {
        response["status_code"] = StatusCode::OK;
        response["success_message"] = "Deleted is Successful!";
    }

    auto responseMessage = response.dump();
    send(client_socket, responseMessage.c_str(), responseMessage.size(), 0);
    Logger::debug("Server::deleteRequest - exiting");
}

void getRequest(const int &client_socket, const std::string &query)
{
    Logger::debug("Server::getRequest - entering");
    nlohmann::ordered_json response;

    if (mysql_query(dbConnector, query.c_str()))
    {
        Logger::error("Failed to execute query: " + query);
        response["status_code"] = StatusCode::BAD_REQUEST;
        response["error_message"] = "Failed execute the get request";
    }
    else
    {
        response["status_code"] = StatusCode::NOT_FOUND;
        MYSQL_RES *result = mysql_store_result(dbConnector);
        auto numOfRows = mysql_num_rows(result);

        if (numOfRows > 0)
        {
            response["status_code"] = StatusCode::OK;
            response["body"]  = nlohmann::json::array();

            MYSQL_ROW row;
            MYSQL_FIELD *field = mysql_fetch_field(result);
            auto numOfFields = mysql_num_fields(result);

            while (row = mysql_fetch_row(result))
            {
                nlohmann::ordered_json jsonRow;
                for (int index = 0; index < numOfFields; index++)
                {
                    auto fieldname = field[index].name;
                    if (row[index])
                    {
                        auto parserResult = Utility::parseToInteger(row[index]);
                        if (parserResult.first)
                        {
                            jsonRow[fieldname] = parserResult.second;
                        }
                        else
                        {
                            jsonRow[fieldname] = row[index];
                        }
                    }
                    else
                    {
                        jsonRow[fieldname] = "";
                    }
                }
                response["body"].push_back(jsonRow);
            }
        }
        else
        {
            response["error_message"] = "Failed to get the data as it is not exists!!!";
        }
        mysql_free_result(result);
    }
    auto responseMessage = response.dump(4);
    send(client_socket, responseMessage.c_str(), responseMessage.size(), 0);
    Logger::debug("Server::getRequest - exiting");
}

void patchRequest(const int &client_socket, const std::string &query)
{

    Logger::debug("Server::patchRequest - entering");
    nlohmann::ordered_json response;

    if (mysql_query(dbConnector, query.c_str()))
    {
        Logger::error("Failed to execute query: " + query);
        response["status_code"] = StatusCode::BAD_REQUEST;
        response["error_message"] = "Failed execute the update request";
    }
    else
    {
        response["status_code"] = StatusCode::OK;
        response["success_message"] = "Update is Successful!";
    }

    auto responseMessage = response.dump();
    send(client_socket, responseMessage.c_str(), responseMessage.size(), 0);
    Logger::debug("Server::patchRequest - exiting");
}

void postRequest(const int &client_socket, const std::string &query)
{
    Logger::debug("Server::postRequest - entering");
    nlohmann::ordered_json response;

    if (mysql_query(dbConnector, query.c_str()))
    {
        Logger::error("Failed to execute query: " + query);
        response["status_code"] = StatusCode::BAD_REQUEST;
        response["error_message"] = "Failed execute the post request";
    }
    else
    {
        response["status_code"] = StatusCode::CREATED;
        response["success_message"] = "Creation is Successful!";
    }

    auto responseMessage = response.dump();
    send(client_socket, responseMessage.c_str(), responseMessage.size(), 0);
    Logger::debug("Server::postRequest - exiting");
}

void handleClientRequest(int client_socket)
{
    char buffer[BUFFER_SIZE] = {0};
    while (true)
    {
        std::memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived <= 0)
        {
            std::cout << "Client disconnected or error occurred." << std::endl;
            return;
        }

        std::string value = buffer;
        if (!value.empty())
        {
            auto query = value.substr(1, value.length());
            auto queryType = (RequestType)(static_cast<int>(value[0]) - 48);

            if (queryType == RequestType::GET)
            {
                std::thread getThreadRequest(getRequest, client_socket, query);
                getThreadRequest.detach();
            }
            else if (queryType == RequestType::DELETE)
            {
                std::thread deleteThreadRequest(deleteRequest, client_socket, query);
                deleteThreadRequest.detach();
            }
            else if (queryType == RequestType::PATCH)
            {
                std::thread pacthThreadRequest(patchRequest, client_socket, query);
                pacthThreadRequest.detach();
            }
            else if (queryType == RequestType::POST)
            {
                std::thread postThreadRequest(postRequest, client_socket, query);
                postThreadRequest.detach();
            }
        }
    }
    close(client_socket);
}

void readDbDetails(nlohmann::ordered_json &dbDetails)
{
    std::ifstream dbfile(dbDetailsFilePath);
    if (dbfile.is_open())
    {
        dbfile >> dbDetails;
        dbfile.close();
    }
}

void initialize()
{
    Mysql mysql;
    nlohmann::ordered_json dbDetails;
    std::string errorDescription;

    readDbDetails(dbDetails);
    if (!dbDetails.empty())
    {
        std::string host = dbDetails["host"];
        std::string userName = dbDetails["user_name"];
        std::string password = dbDetails["password"];
        std::string database = dbDetails["database"];
        dbConnector = mysql.getMysqlConnector(host, userName, password, database, errorDescription);
        if (!errorDescription.empty())
        {
            Logger::debug("Server::initialize - db connection got failed");
        }
    }
    else
    {
        Logger::error("Server::initialize - dbDetails are not able to read");
    }
}

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    initialize();

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        Logger::error("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        Logger::error("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 5) < 0)
    {
        Logger::error("not listenting");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while(true)
    {
        // Accept an incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            Logger::error("Failed to accept connection");
            continue;
        }

        std::thread requestHandler(handleClientRequest, new_socket);
        requestHandler.detach();
    }

    mysql_close(dbConnector);
    close(server_fd);
    return 0;
}
