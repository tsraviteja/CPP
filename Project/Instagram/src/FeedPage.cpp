#include "Feedpage.h"

Feedpage::Feedpage(std::string username, InstagramJsonFileHandling *instagramFileHandling)
{
    this->username = username;
    instagramUserPostdataFile = "../InstagramDataStorage/InstagramUserPosts.json";
    this->instagramFileHandling = instagramFileHandling;
    instagramJsonPostData = instagramFileHandling->getInstagramJsonFileData(instagramUserPostdataFile);
    userIndex = 0;
    totalNumberOfPost = instagramJsonPostData["Usersposts"].size();
}

PostInfo Feedpage::firtPostInInstagram()
{
    PostInfo postData;
    postData.post = "";
    postData.posterName = "";

    if (totalNumberOfPost > 0)
    {
        postData.post = instagramJsonPostData["Usersposts"][userIndex]["post"];
        postData.posterName = instagramJsonPostData["Usersposts"][userIndex]["postedBy"];
    }
    return postData;
}

PostInfo Feedpage::moveToNextPost()
{
    PostInfo postData;
    postData.post = "";
    postData.posterName = "";
    userIndex++;

    if (userIndex < totalNumberOfPost)
    {
        postData.post = instagramJsonPostData["Usersposts"][userIndex]["post"];
        postData.posterName = instagramJsonPostData["Usersposts"][userIndex]["postedBy"];
    }
    return postData;
}

PostInfo Feedpage::moveBackToPreviousPost()
{
    PostInfo postData;
    postData.post = "";
    postData.posterName = "";
    userIndex--;

    if (userIndex >= 0)
    {
        postData.post = instagramJsonPostData["Usersposts"][userIndex]["post"];
        postData.posterName = instagramJsonPostData["Usersposts"][userIndex]["postedBy"];
    }
    return postData;
}

bool Feedpage::isPostedMessageWasAlreadyLiked(PostInfo postData)
{
    bool isPostWasLikedByUser = false;
    for (auto userPostData : instagramJsonPostData["Usersposts"])
    {
        if (userPostData["post"] == postData.post && userPostData["postedBy"] == postData.posterName)
        {
            for (auto liker : userPostData["likedBy"])
            {
                if (username == liker)
                {
                    isPostWasLikedByUser = true;
                    break;
                }
            }
        }
        if (isPostWasLikedByUser)
        {
            break;
        }
    }
    return isPostWasLikedByUser;
}

void Feedpage::doLikePost(PostInfo postData)
{
    for (auto &userPostData : instagramJsonPostData["Usersposts"])
    {
        if (userPostData["post"] == postData.post && userPostData["postedBy"] == postData.posterName)
        {
            nlohmann::ordered_json &likeBy = userPostData["likedBy"];
            likeBy.push_back(username);
            instagramFileHandling->writeInstagramJsonFileData(instagramUserPostdataFile, instagramJsonPostData);
            break;
        }
    }
}

void Feedpage::removeLikeFromPost(PostInfo postData)
{
    for (auto &userPostData : instagramJsonPostData["Usersposts"])
    {
        if (userPostData["post"] == postData.post && userPostData["postedBy"] == postData.posterName)
        {
            nlohmann::ordered_json &likeBy = userPostData["likedBy"];
            likeBy.erase(std::remove(likeBy.begin(), likeBy.end(), username), likeBy.end());
            instagramFileHandling->writeInstagramJsonFileData(instagramUserPostdataFile, instagramJsonPostData);
            break;
        }
    }
}

bool Feedpage::likePost(PostInfo postData)
{
    instagramJsonPostData = instagramFileHandling->getInstagramJsonFileData(instagramUserPostdataFile);
    bool ispostWasAlreadyLikedByUser = isPostedMessageWasAlreadyLiked(postData);
    bool likeStatus = true;

    if (ispostWasAlreadyLikedByUser)
    {
        likeStatus = false;
        removeLikeFromPost(postData);
    }
    else
    {
        doLikePost(postData);
    }
    return likeStatus;
}
