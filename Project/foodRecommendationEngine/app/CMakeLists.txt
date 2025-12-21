cmake_minimum_required(VERSION 3.22.1)
project(FoodRecommendationEngine VERSION 0.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/client/pub
                    ${CMAKE_CURRENT_SOURCE_DIR}/client/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/server/pub
                    ${CMAKE_CURRENT_SOURCE_DIR}/server//inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/../.lib
                    ${CMAKE_CURRENT_SOURCE_DIR}/../framework/core/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/../framework/logger/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/../framework/timeStamp/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/food/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/food/pub)

message("Current directory is : ${CMAKE_SOURCE_DIR}")

add_executable(server  server//src/Server.cpp
                       server//src/Mysql.cpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/../framework/timeStamp/src/TimeStamp.cpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/../framework/logger/src/Logger.cpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/../framework/core/src/Utility.cpp)

target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/server//resource)

target_link_libraries(server mysqlclient)

add_executable(client  client/src/Client.cpp
                       client/src/Handler.cpp
                       client/src/Admin.cpp
                       client/src/Authentication.cpp
                       client/src/Chef.cpp
                       client/src/Engine.cpp
                       client/src/Employee.cpp
                       client/src/Notification.cpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/food//src/Item.cpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/../framework/logger/src/Logger.cpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/../framework/timeStamp/src/TimeStamp.cpp
                       ${CMAKE_CURRENT_SOURCE_DIR}/../framework/core/src/Utility.cpp)

