/**********************************************************
 * @file IRequest.h
 * @brief IRequest class header file to define the interface for API request operations.
 * @date  27-06-2026
 **********************************************************/

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
     * @return Response - returns status code along with json data.
     */
    virtual Response get(const char *url) = 0;

    /**
     * @brief POST API Request call the specified URL along request body.
     * 
     * @param url [in] - Requested URL.
     * @param requestBody [in] - post request body.
     * @return Response - returns status code along with json data.
     */
    virtual Response post(const char *url, const std::string &requestBody) = 0;

    /**
     * @brief PATCH API Request call the specified URL along request body.
     * 
     * @param url [in] - Requested URL.
     * @param requestBody [in] - patch request body.
     * @return Response - returns status code along with json data.
     */
    virtual Response patch(const char *url, const std::string & requestBody) = 0;

    /**
     * @brief PUT API Request call the specified URL along request body.
     * 
     * @param url [in] - Requested URL.
     * @param requestBody [in] - put request body.
     * @return Response - returns status code along with json data.
     */
    virtual Response put(const char *url, const std::string & requestBody) = 0;

    /**
     * @brief DELETE API Request call for the specified URL.
     * 
     * @param url [in] - Requested URL.
     * @return Response - returns status code along with json data.
     */
    virtual Response delete$(const char *url) = 0;
};

} // namespace API
