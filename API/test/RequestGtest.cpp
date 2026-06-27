#include "Request.h"

#include <gtest/gtest.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <memory>

using Request = API::Request;
using StatusCode = API::StatusCode;

const std::string BASE_URL = "http://localhost:8080/StudentDetails";

class GivenAnRequest : public ::testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;

protected:
    std::shared_ptr<Request> request_;
    pid_t serverPid_ = -1;

    bool StartJsonServer();
    void StopJsonServer();
    void removeDataFromJsonServer();
};

void GivenAnRequest::SetUp()
{
    ASSERT_TRUE(StartJsonServer()) << "Failed to launch or connect to json-server";
    request_ = std::make_shared<Request>();
}

void GivenAnRequest::TearDown()
{
    removeDataFromJsonServer();
    StopJsonServer();
}

void GivenAnRequest::removeDataFromJsonServer()
{
    auto response = request_->get(BASE_URL.c_str());
    if (response.first == StatusCode::OK)
    {
        for (const auto &student : response.second["body"])
        {
            int studentId = student["id"];
            std::string deleteUrl = BASE_URL + "/" + std::to_string(studentId);
            request_->delete$(deleteUrl.c_str());
        }
    }
}

bool GivenAnRequest::StartJsonServer()
{
    bool isServerReady = false;
    serverPid_ = fork();

    if (serverPid_ == 0)
    {
        if (chdir("../.node_modules") != 0) 
        {
            _exit(127);
        }

        int logFile = open("../.build/server.log", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (logFile >= 0) 
        {
            dup2(logFile, STDOUT_FILENO);
            dup2(logFile, STDERR_FILENO);
            close(logFile);
        }

        const char *argv[] = {
            "npm",
            "run",
            "json-server",
            nullptr};

        execvp("npm", const_cast<char *const *>(argv));
        _exit(127);   
    }
    else if (serverPid_ > 0)
    {
        for (int attempt = 0; attempt < 20 && !isServerReady; ++attempt)
        {
            std::string checkCmd = "curl -sSf " + BASE_URL + " > /dev/null 2>&1";
            if (std::system(checkCmd.c_str()) == 0)
            {
                isServerReady = true;
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }
    }

    return isServerReady;
}

void GivenAnRequest::StopJsonServer()
{
    if (serverPid_ > 0)
    {
        kill(serverPid_, SIGTERM);
        waitpid(serverPid_, nullptr, 0);
        serverPid_ = -1;

        std::system("fuser -k 8080/tcp > /dev/null 2>&1");
    }
}

/*********** Tests for get method **********/
TEST_F(GivenAnRequest, WhenGetRequestIsCallledWithValidUrl_ThenReturnsStatusCode200)
{
    auto response = request_->get(BASE_URL.c_str());
    EXPECT_EQ(StatusCode::OK, response.first);
    EXPECT_TRUE(response.second.contains("body"));
}

TEST_F(GivenAnRequest, WhenGetRequestIsCallledWithInvalidUrl_ThenReturnsStatusCode404)
{
    auto response = request_->get("http://localhost:8080/InvalidUrl");
    EXPECT_EQ(StatusCode::NOT_FOUND, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenGetRequestIsCallledWithServerDown_ThenReturnsStatusCode503)
{
    StopJsonServer();
    auto response = request_->get(BASE_URL.c_str());
    EXPECT_EQ(StatusCode::SERVICE_UNAVAILABLE, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenGetRequestIsCallledWithNonExistingResource_ThenReturnsStatusCode404)
{
    std::string invalidUrl = BASE_URL + "/999";
    auto response = request_->get(invalidUrl.c_str());
    EXPECT_EQ(StatusCode::NOT_FOUND, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenGetRequestIsCallledWithExistingResource_ThenReturnsStatusCode200)
{
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    auto postResponse = request_->post(BASE_URL.c_str(), requestBody);
    ASSERT_EQ(StatusCode::CREATED, postResponse.first);

    std::string targetUrl = BASE_URL + "/108";
    auto response = request_->get(targetUrl.c_str());
    EXPECT_EQ(StatusCode::OK, response.first);
    EXPECT_TRUE(response.second.contains("body"));
    EXPECT_EQ(API::json::parse(requestBody).dump(), response.second["body"].dump());
}

/************* Tests for post method ***********/
TEST_F(GivenAnRequest, WhenPostRequestIsCallledWithValidUrlAndBody_ThenReturnsStatusCode201)
{
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    auto response = request_->post(BASE_URL.c_str(), requestBody);
    EXPECT_EQ(StatusCode::CREATED, response.first);
    EXPECT_TRUE(response.second.contains("body"));
    EXPECT_EQ(API::json::parse(requestBody).dump(), response.second["body"].dump());
}

TEST_F(GivenAnRequest, WhenPostRequestIsCallledWithInvalidUrl_ThenReturnsStatusCode404)
{
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    auto response = request_->post("http://localhost:8080/InvalidUrl", requestBody);
    EXPECT_EQ(StatusCode::NOT_FOUND, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenPostRequestIsCallledWithServerDown_ThenReturnsStatusCode503)
{
    StopJsonServer();
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    auto response = request_->post(BASE_URL.c_str(), requestBody);
    EXPECT_EQ(StatusCode::SERVICE_UNAVAILABLE, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

/************* Tests for put method ***********/
TEST_F(GivenAnRequest, WhenPutRequestIsCallledWithValidUrlAndBody_ThenReturnsStatusCode200)
{
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    auto postResponse = request_->post(BASE_URL.c_str(), requestBody);
    ASSERT_EQ(StatusCode::CREATED, postResponse.first);

    std::string updatedRequestBody = R"({
                        "name": "Ranveer Singh",
                        "id": 108,
                        "age": 24
                    })";

    std::string targetUrl = BASE_URL + "/108";
    auto putResponse = request_->put(targetUrl.c_str(), updatedRequestBody);
    EXPECT_EQ(StatusCode::OK, putResponse.first);
    EXPECT_TRUE(putResponse.second.contains("body"));
    EXPECT_EQ(API::json::parse(updatedRequestBody).dump(), putResponse.second["body"].dump());
}

TEST_F(GivenAnRequest, WhenPutRequestIsCallledWithInvalidUrl_ThenReturnsStatusCode404)
{
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    auto response = request_->put("http://localhost:8080/InvalidUrl", requestBody);
    EXPECT_EQ(StatusCode::NOT_FOUND, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenPutRequestIsCallledWithServerDown_ThenReturnsStatusCode503)
{
    StopJsonServer();
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    std::string targetUrl = BASE_URL + "/108";
    auto response = request_->put(targetUrl.c_str(), requestBody);
    EXPECT_EQ(StatusCode::SERVICE_UNAVAILABLE, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenPutRequestIsCallledWithNonExistingResource_ThenReturnsStatusCode404)
{
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    std::string targetUrl = BASE_URL + "/999";
    auto response = request_->put(targetUrl.c_str(), requestBody);
    EXPECT_EQ(StatusCode::NOT_FOUND, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

/************* Tests for patch method ***********/
TEST_F(GivenAnRequest, WhenPatchRequestIsCallledWithValidUrlAndBody_ThenReturnsStatusCode200)
{
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    auto postResponse = request_->post(BASE_URL.c_str(), requestBody);
    ASSERT_EQ(StatusCode::CREATED, postResponse.first);

    std::string patchRequestBody = R"({
                        "age": 24
                    })";

    std::string targetUrl = BASE_URL + "/108";
    auto patchResponse = request_->patch(targetUrl.c_str(), patchRequestBody);
    EXPECT_EQ(StatusCode::OK, patchResponse.first);
    EXPECT_TRUE(patchResponse.second.contains("body"));
    EXPECT_EQ(24, patchResponse.second["body"]["age"]);
}

TEST_F(GivenAnRequest, WhenPatchRequestIsCallledWithInvalidUrl_ThenReturnsStatusCode404)
{
    std::string requestBody = R"({
                        "age": 24
                    })";

    auto response = request_->patch("http://localhost:8080/InvalidUrl", requestBody);
    EXPECT_EQ(StatusCode::NOT_FOUND, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenPatchRequestIsCallledWithServerDown_ThenReturnsStatusCode503)
{
    StopJsonServer();
    std::string requestBody = R"({
                        "age": 24
                    })";

    std::string targetUrl = BASE_URL + "/108";
    auto response = request_->patch(targetUrl.c_str(), requestBody);
    EXPECT_EQ(StatusCode::SERVICE_UNAVAILABLE, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenPatchRequestIsCallledWithNonExistingResource_ThenReturnsStatusCode404)
{
    std::string requestBody = R"({
                        "age": 24
                    })";

    std::string targetUrl = BASE_URL + "/999";
    auto response = request_->patch(targetUrl.c_str(), requestBody);
    EXPECT_EQ(StatusCode::NOT_FOUND, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

/************* Tests for delete$ method ***********/
TEST_F(GivenAnRequest, WhenDeleteRequestIsCallledWithValidUrl_ThenReturnsStatusCode200)
{
    std::string requestBody = R"({
                        "name": "Ranveer",
                        "id": 108,
                        "age": 23
                    })";

    auto postResponse = request_->post(BASE_URL.c_str(), requestBody);
    ASSERT_EQ(StatusCode::CREATED, postResponse.first);

    std::string targetUrl = BASE_URL + "/108";
    auto deleteResponse = request_->delete$(targetUrl.c_str());
    EXPECT_EQ(StatusCode::OK, deleteResponse.first);
}

TEST_F(GivenAnRequest, WhenDeleteRequestIsCallledWithInvalidUrl_ThenReturnsStatusCode404)
{
    auto response = request_->delete$("http://localhost:8080/InvalidUrl");
    EXPECT_EQ(StatusCode::NOT_FOUND, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenDeleteRequestIsCallledWithServerDown_ThenReturnsStatusCode503)
{
    StopJsonServer();
    std::string targetUrl = BASE_URL + "/108";
    auto response = request_->delete$(targetUrl.c_str());
    EXPECT_EQ(StatusCode::SERVICE_UNAVAILABLE, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}

TEST_F(GivenAnRequest, WhenDeleteRequestIsCallledWithNonExistingResource_ThenReturnsStatusCode404)
{
    std::string targetUrl = BASE_URL + "/999";
    auto response = request_->delete$(targetUrl.c_str());
    EXPECT_EQ(StatusCode::NOT_FOUND, response.first);
    EXPECT_TRUE(response.second.contains("errorMessage"));
}
