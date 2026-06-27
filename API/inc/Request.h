/**********************************************************
 * @file Request.h
 * @brief Request class header file to perform the API request operations.
 * @date  27-06-2026
 **********************************************************/

#pragma once

#include <curl/curl.h>
#include <mutex>

#include "IRequest.h"

namespace API {

class Request : public IRequest
{
public:
    /**
     * Cosntructor
     */
    explicit Request();

    /**
     * Destructor
     */
    ~Request();

    std::pair<int, json> get(const char *url) override;
    std::pair<int, json> post(const char *url, const std::string &requestBody) override;
    std::pair<int, json> patch(const char *url, const std::string & requestBody) override;
    std::pair<int, json> put(const char *url, const std::string & requestBody) override;
    std::pair<int, json> delete$(const char *url) override;

    /**
     * @brief clear server response.
     */
    void clearServerResponse();

    /**
     * @brief initalizes the curl.
     */
    bool initializeServer();

    /**
     * @brief Call back method to store the response.
     * 
     * @param serverReponse [in] - response data from server
     * @param sizeOfDataElement [in] - size of data element in reponse
     * @param numberOfDataMember [in] - number of data memeber in response
     * @param storeResponeData [in/out] - stores the response data from server response
     */
    static size_t storeReponseDataOfServer(char *serverResponse,
                                           size_t sizeOfDataElement,
                                           size_t numberOfDataMember,
                                           std::string *storeResponseData);

private:
    CURL *curl_;
    std::mutex curlMutex_;
    std::string serverResponse_;
};
} // namespace API
