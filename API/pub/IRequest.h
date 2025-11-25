#pragma once

#include <iostream>

#include "RequestDataType.h"

namespace API {

class IRequest
{
public:
    /**
     * Destructor
     */
    virtual ~IRequest() {}

    /**
     * @brief GET API Request call for the specified URL.
     * 
     * @param url [in] - Requested URL.
     * @return std::pair<int, json> - returns status code along with json data.
     */
    virtual std::pair<int, json> get(const char *url) = 0;

    /**
     * @brief POST API Request call the specified URL along request body.
     * 
     * @param url [in] - Requested URL.
     * @param requestBody [in] - post request body.
     * @return std::pair<int, json> - returns status code along with json data.
     */
    virtual std::pair<int, json> post(const char *url, const std::string &requestBody) = 0;

    /**
     * @brief PATCH API Request call the specified URL along request body.
     * 
     * @param url [in] - Requested URL.
     * @param requestBody [in] - patch request body.
     * @return std::pair<int, json> - returns status code along with json data.
     */
    virtual std::pair<int, json> patch(const char *url, const std::string & requestBody) = 0;

    /**
     * @brief PUT API Request call the specified URL along request body.
     * 
     * @param url [in] - Requested URL.
     * @param requestBody [in] - put request body.
     * @return std::pair<int, json> - returns status code along with json data.
     */
    virtual std::pair<int, json> put(const char *url, const std::string & requestBody) = 0;

    /**
     * @brief DELETE API Request call for the specified URL.
     * 
     * @param url [in] - Requested URL.
     * @return std::pair<int, json> - returns status code along with json data.
     */
    virtual std::pair<int, json> delete$(const char *url) = 0;
};

}
