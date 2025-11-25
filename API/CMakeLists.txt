cmake_minimum_required(VERSION 3.28.0)

project(APIRequest VERSION 0.1)

find_package(CURL REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc
                    ${CMAKE_CURRENT_SOURCE_DIR}/pub
                    ${CMAKE_CURRENT_SOURCE_DIR}/../.lib)

add_executable(RequestAPI src/main.cpp
                          src/Request.cpp)

target_link_libraries(RequestAPI PRIVATE CURL::libcurl)
