#include "mockInstgramJsonFileHandling.h"
#include "Homepage.h"
#include "Instagram.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

class GivenHomePage : public ::testing::Test
{
protected:
    nlohmann::ordered_json userData;

    void SetUp() override
    {
        userData = {
            {"Usersposts", nlohmann::ordered_json::array({{{"post", "I Like mangoes"},
                                                           {"postedBy", "rahul"},
                                                           {"likedBy", nlohmann::ordered_json::array({"ravi", "rahul"})}}})}};
    }

    void TearDown() override {}
};

TEST_F(GivenHomePage, whenUserDoesnothaveAnyPost)
{
    std::string username = "Ajay";
    MockInstagramJsonFileHandling instagramFileHandling;
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).Times(2).WillRepeatedly(Return(userData));
    Homepage homepage(username, &instagramFileHandling);

    bool isAnyPostFound = homepage.displayMyPost();
    ASSERT_FALSE(isAnyPostFound);
}

TEST_F(GivenHomePage, whenUserHadPostedAnyPost)
{
    std::string username = "rahul";
    MockInstagramJsonFileHandling instagramFileHandling;
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).Times(2).WillRepeatedly(Return(userData));
    Homepage homepage(username, &instagramFileHandling);

    bool isAnyPostFound = homepage.displayMyPost();
    ASSERT_TRUE(isAnyPostFound);
}
