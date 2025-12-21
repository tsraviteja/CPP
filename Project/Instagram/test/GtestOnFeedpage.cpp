#include "mockInstgramJsonFileHandling.h"
#include "Feedpage.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Return;

class GivenFeedpage : public ::testing::Test
{

protected:
    nlohmann::ordered_json userData;

    void SetUp() override
    {
        userData = {
            {"Usersposts", nlohmann::ordered_json::array({{{"post", "I Like mangoes"},
                                                           {"postedBy", "rahul"},
                                                           {"likedBy", nlohmann::ordered_json::array({"ravi", "rahul"})}},
                                                          {{"post", "I Like pizza"},
                                                           {"postedBy", "ravi"},
                                                           {"likedBy", nlohmann::ordered_json::array({"rahul"})}}})}};
    }
    void TearDown() override {}
};

TEST_F(GivenFeedpage, whenFeedPageOpensUserSeeFirstPost)
{
    const std::string username = "ravi", post = "I Like mangoes", postedBy = "rahul";
    MockInstagramJsonFileHandling instagramFileHandling;
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).Times(1).WillRepeatedly(Return(userData));
    Feedpage feedpage(username, &instagramFileHandling);

    PostInfo postData = feedpage.firtPostInInstagram();
    ASSERT_EQ(post, postData.post);
    ASSERT_EQ(postedBy, postData.posterName);
}

TEST_F(GivenFeedpage, whenUserWantsToSeeNextPost)
{
    const std::string username = "ravi", post = "I Like pizza", postedBy = "ravi";
    MockInstagramJsonFileHandling instagramFileHandling;
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).Times(1).WillRepeatedly(Return(userData));
    Feedpage feedpage(username, &instagramFileHandling);

    PostInfo postData = feedpage.moveToNextPost();
    ASSERT_EQ(post, postData.post);
    ASSERT_EQ(postedBy, postData.posterName);
}

TEST_F(GivenFeedpage, WhenUserSeeNoPostFoundOnNextPost)
{
    const std::string username = "ravi", post = "", postedBy = "";
    MockInstagramJsonFileHandling instagramFileHandling;
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).Times(1).WillRepeatedly(Return(userData));
    Feedpage feedpage(username, &instagramFileHandling);

    PostInfo postData = feedpage.moveToNextPost();
    ASSERT_EQ("I Like pizza", postData.post);
    ASSERT_EQ("ravi", postData.posterName);

    postData = feedpage.moveToNextPost();
    ASSERT_EQ(post, postData.post);
    ASSERT_EQ(postedBy, postData.posterName);
}

TEST_F(GivenFeedpage, WhenUserWantToSeeThePreviousPost)
{
    const std::string username = "ravi";
    MockInstagramJsonFileHandling instagramFileHandling;
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).Times(1).WillRepeatedly(Return(userData));
    Feedpage feedpage(username, &instagramFileHandling);

    PostInfo postData = feedpage.moveToNextPost();
    ASSERT_EQ("I Like pizza", postData.post);
    ASSERT_EQ("ravi", postData.posterName);

    postData = feedpage.moveBackToPreviousPost();
    ASSERT_EQ("I Like mangoes", postData.post);
    ASSERT_EQ("rahul", postData.posterName);
}

TEST_F(GivenFeedpage, WhenUserlikesThePost)
{
    const std::string username = "vinay";
    MockInstagramJsonFileHandling instagramFileHandling;
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).Times(2).WillRepeatedly(Return(userData));
    EXPECT_CALL(instagramFileHandling, writeInstagramJsonFileData(_, _)).WillOnce(Return(true));
    Feedpage feedpage(username, &instagramFileHandling);

    PostInfo postData = feedpage.firtPostInInstagram();
    ASSERT_EQ("I Like mangoes", postData.post);
    ASSERT_EQ("rahul", postData.posterName);

    bool likeStatus = feedpage.likePost(postData);
    ASSERT_TRUE(likeStatus);
}

TEST_F(GivenFeedpage, WhenUserTryToDoLikeOnSamePostThenLikeIsRemoved)
{
    const std::string username = "ravi";

    MockInstagramJsonFileHandling instagramFileHandling;
    EXPECT_CALL(instagramFileHandling, getInstagramJsonFileData(_)).Times(2).WillRepeatedly(Return(userData));
    EXPECT_CALL(instagramFileHandling, writeInstagramJsonFileData(_, _)).WillOnce(Return(true));
    Feedpage feedpage(username, &instagramFileHandling);

    PostInfo postData = feedpage.firtPostInInstagram();
    ASSERT_EQ("I Like mangoes", postData.post);
    ASSERT_EQ("rahul", postData.posterName);

    bool likeStatus = feedpage.likePost(postData);
    ASSERT_FALSE(likeStatus);
}

// g++ -I ../inc ../src/*.cpp ../test/GtestOnFeedpage.cpp -lgtest -lgmock -lgtest_main -lpthread -o gtest
