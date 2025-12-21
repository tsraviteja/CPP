#include "ErrorDescription.h"
#include "Mysql.h"
#include "Logger.h"

using Logger = foodRecommendationEngine::framework::logger::Logger;

namespace foodRecommendationEngine { namespace app { namespace server {

//***********************************************/
//**************Mysql public method**************/
//***********************************************/

Mysql::Mysql()
{
    Logger::debug("Mysql::Mysql - constructed");
}

MYSQL *Mysql::getMysqlConnector(const std::string &host,
                                const std::string &user,
                                const std::string &password,
                                const std::string &database,
                                std::string &errorDescription)
{
    Logger::debug("Mysql::getMysqlConnector - entering");
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (conn == nullptr)
    {
        errorDescription = MysqlErrorDescription::FAILED_TO_INIT;
    }

    if (conn != nullptr && mysql_real_connect(conn, host.c_str(), user.c_str(),
                                              password.c_str(), database.c_str(), 0, NULL, 0) == NULL)
    {
        errorDescription = MysqlErrorDescription::CONNECTION_FAILED;
        mysql_close(conn);
    }
    Logger::debug("Mysql::getMysqlConnector - exiting");
    return conn;
}
}}}
