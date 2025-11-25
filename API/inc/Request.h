#pragma once

#include <curl/curl.h>

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
     * @brief initalizes the curl.
     */
    bool initializeServer();

    /**
     * @brief clear server response.
     */
    void clearServerResponse();

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
    CURL *curl;
    std::string serverResponse;
};
}
