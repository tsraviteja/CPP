cmake_minimum_required(VERSION 3.22.1)
project(FoodRecommendationEngine VERSION 0.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/../pub
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../.lib
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../food/pub
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../food/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../server/pub
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/core/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/logger/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/timeStamp/inc)

find_package(GTest REQUIRED)
include_directories(($(GTEST_INCLUDE_DIR)))

add_executable(ClientTest  test/AdminGtest.cpp
                           test/AuthenticationGtest.cpp
                           test/ChefGtest.cpp
                           test/EmployeeGtest.cpp
                           test/NotificationGtest.cpp
                           src/Admin.cpp
                           src/Authentication.cpp
                           src/Chef.cpp
                           src/Engine.cpp
                           src/Employee.cpp
                           src/Notification.cpp
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../food/src/Item.cpp
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/core/src/Utility.cpp
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/logger/src/Logger.cpp
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/timeStamp/src/TimeStamp.cpp)

target_link_libraries(ClientTest gtest gmock gtest_main pthread)