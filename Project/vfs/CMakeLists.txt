cmake_minimum_required(VERSION 3.22.1)
project(VFSProject VERSION 1.0.0)


# Set the source files using file globbing
file(GLOB SOURCES "app/*.cpp" "src/*.cpp")
file(GLOB TEST_SOURCES "test/*.cpp" "src/*.cpp")


include_directories(vfs/inc)

# Add executable target
add_executable(vfs ${SOURCES})

# Setup testing
enable_testing()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})

# Add test cpp file
add_executable(runtest
${TEST_SOURCES})

target_link_libraries(runtest gtest gtest_main gmock pthread)