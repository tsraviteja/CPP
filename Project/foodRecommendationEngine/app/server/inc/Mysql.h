#pragma once

#include <iostream>
#include <mysql/mysql.h>

namespace foodRecommendationEngine { namespace app { namespace server {
class Mysql
{
public:

    explicit Mysql();

    /**
     * @brief gets db object connected to the database for
     * provided the details
     *
     * @param host [in] - db host name
     * @param user [in] - db user name
     * @param password [in] - password set by user in db
     * @param database [in] - databse name to get connection
     * @param errorDescription [in/out] - errormessage will updated when connection or initialize fails
     * @return  MYSQL * [out] - A db connector pointer will be returned.
     */
    MYSQL *getMysqlConnector(const std::string &host,
                             const std::string &user,
                             const std::string &password,
                             const std::string &database,
                             std::string &errorDescription);
};
}}} // namespace foodRecommendationEngine::app::server
