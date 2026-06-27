/**********************************************************
 * @file Request.cpp
 * @brief Request class implementation file to perform the API request operations.
 * @date  27-06-2026
 **********************************************************/

#include "Request.h"

namespace API {

//***************************************************/
//******** Request constructor & destructor *********/
//***************************************************/

Request::Request()
{
    if (initializeServer())
    {
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, storeReponseDataOfServer);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &serverResponse_);
    }
}

Request::~Request()
{
    curl_easy_cleanup(curl_);
    curl_global_cleanup();
}

//***************************************************/
//************ iRequest Public methods **************/
//***************************************************/

std::pair<int, json> Request::get(const char *url)
{
    std::lock_guard<std::mutex> lock(curlMutex_);
    std::pair<int, json> response;
    response.second = {
        {"body", {}},
        {"errorMessage", ""}
    };

    response.first = StatusCode::SERVICE_UNAVAILABLE;
    response.second["errorMessage"] = "Service Unavailable!";

    clearServerResponse();

    curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curl_, CURLOPT_URL, url);

    CURLcode curlCode;
    long statusCode = 0;

    curlCode = curl_easy_perform(curl_);
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &statusCode);

    if (curlCode == CURLE_OK)
    {
        if (statusCode == StatusCode::OK)
        {
            response.first = StatusCode::OK;
            response.second["body"] = json::parse(serverResponse_);
            response.second["errorMessage"].clear();
            clearServerResponse();
        }
        else
        {
            response.first = statusCode;
            response.second["errorMessage"] = "Failed to get the data!";
        }
    }
    return response;
}

std::pair<int, json> Request::post(const char *url, const std::string &requestBody)
{
    std::lock_guard<std::mutex> lock(curlMutex_);
    std::pair<int, json> response;
    response.second = {
        {"body", {}},
        {"errorMessage", ""}
    };

    response.first = StatusCode::SERVICE_UNAVAILABLE;
    response.second["errorMessage"] = "Service Unavailable!";

    clearServerResponse();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl_, CURLOPT_URL, url);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, requestBody.c_str());
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, requestBody.size());

    CURLcode curlCode;
    long statusCode = 0;

    curlCode = curl_easy_perform(curl_);
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &statusCode);

    curl_slist_free_all(headers);
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, NULL);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, NULL);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, 0);

    if (curlCode == CURLE_OK)
    {
        if (statusCode == StatusCode::OK || statusCode == StatusCode::CREATED)
        {
            response.first = statusCode;
            response.second["body"] = json::parse(serverResponse_);
            response.second["errorMessage"].clear();
            clearServerResponse();
        }
        else
        {
            response.first = statusCode;
            response.second["errorMessage"] = "POST request failed!";
        }
    }

    return response;
}

std::pair<int, json> Request::patch(const char *url, const std::string &requestBody)
{
    std::lock_guard<std::mutex> lock(curlMutex_);
    std::pair<int, json> response;
    response.second = {
        {"body", {}},
        {"errorMessage", ""}
    };

    response.first = StatusCode::SERVICE_UNAVAILABLE;
    response.second["errorMessage"] = "Service Unavailable!";

    clearServerResponse();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "PATCH");
    curl_easy_setopt(curl_, CURLOPT_URL, url);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, requestBody.c_str());
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, requestBody.size());

    CURLcode curlCode;
    long statusCode = 0;

    curlCode = curl_easy_perform(curl_);
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &statusCode);

    curl_slist_free_all(headers);
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, NULL);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, NULL);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, 0);

    if (curlCode == CURLE_OK)
    {
        
        if (statusCode == StatusCode::OK)
        {
            response.first = StatusCode::OK;
            response.second["body"] = json::parse(serverResponse_);
            response.second["errorMessage"].clear();
            clearServerResponse();
        }
        else
        {
            response.first = statusCode;
            response.second["errorMessage"] = "PATCH request failed!";
        }
    }
    return response;
}

std::pair<int, json> Request::put(const char *url, const std::string &requestBody)
{
    std::lock_guard<std::mutex> lock(curlMutex_);
    std::pair<int, json> response;
    response.second = {
        {"body", {}},
        {"errorMessage", ""}
    };

    response.first = StatusCode::SERVICE_UNAVAILABLE;
    response.second["errorMessage"] = "Service Unavailable!";

    clearServerResponse();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl_, CURLOPT_URL, url);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, requestBody.c_str());
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, requestBody.size());

    CURLcode curlCode;
    long statusCode = 0;

    curlCode = curl_easy_perform(curl_);
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &statusCode);

    curl_slist_free_all(headers);
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, NULL);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, NULL);
    curl_easy_setopt(curl_, CURLOPT_POSTFIELDSIZE, 0);

    if (curlCode == CURLE_OK)
    {
        
        if (statusCode == StatusCode::OK)
        {
            response.first = StatusCode::OK;
            response.second["body"] = json::parse(serverResponse_);
            response.second["errorMessage"].clear();
            clearServerResponse();
        }
        else
        {
            response.first = statusCode;
            response.second["errorMessage"] = "PATCH request failed!";
        }
    }
    return response;
}

std::pair<int, json> Request::delete$(const char *url)
{
    std::lock_guard<std::mutex> lock(curlMutex_);
    std::pair<int, json> response;
    response.second = {
        {"body", {}},
        {"errorMessage", ""}
    };

    response.first = StatusCode::SERVICE_UNAVAILABLE;
    response.second["errorMessage"] = "Service Unavailable!";

    clearServerResponse();

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl_, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(curl_, CURLOPT_URL, url);

    CURLcode curlCode;
    long statusCode = 0;
    curlCode = curl_easy_perform(curl_);
    curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &statusCode);

    curl_slist_free_all(headers);
    curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, NULL);

    if (curlCode == CURLE_OK)
    {
        if (statusCode == StatusCode::OK)
        {
            response.first = statusCode;
            if (!serverResponse_.empty())
            {
                response.second["body"] = json::parse(serverResponse_);
            }
            clearServerResponse();
        }
        else
        {
            response.first = statusCode;
            response.second["errorMessage"] = "DELETE request failed!";
        }
    }
    return response;
}

//***************************************************/
//************ Request Public methods ***************/
//***************************************************/

bool Request::initializeServer()
{
    auto result = false;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_ = curl_easy_init();
    if (curl_)
    {
        result = true;
    }
    return result;
}

void Request::clearServerResponse()
{
    serverResponse_.clear();
}

size_t Request::storeReponseDataOfServer(char *serverResponse_,
                                         size_t sizeOfDataElement,
                                         size_t numberOfDataMember,
                                         std::string *storeResponseData)
{
    storeResponseData->append(serverResponse_, (sizeOfDataElement * numberOfDataMember));
    return (sizeOfDataElement * numberOfDataMember);
}

} // namespace API
