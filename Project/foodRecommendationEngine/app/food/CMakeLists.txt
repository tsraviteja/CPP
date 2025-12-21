cmake_minimum_required(VERSION 3.22.1)
project(FoodRecommendationEngine VERSION 0.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../pub)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/logger/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/timeStamp/inc)

find_package(GTest REQUIRED)
include_directories(($(GTEST_INCLUDE_DIR)))

add_executable(FoodStandard test/ItemGtest.cpp
                            src/Item.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/logger/src/Logger.cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}/../../../framework/timeStamp/src/TimeStamp.cpp)

target_link_libraries(FoodStandard gtest gtest_main pthread)
