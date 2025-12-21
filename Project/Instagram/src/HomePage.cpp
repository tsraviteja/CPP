#include "Homepage.h"

Homepage::Homepage(std::string username, InstagramJsonFileHandling *instagramFileHandling)
{
    this->username = username;
    this->instagramFileHandling = instagramFileHandling;
    instagramUserPostdataFile = "../InstagramDataStorage/InstagramUserPosts.json";
    instagramJsonPostData = instagramFileHandling->getInstagramJsonFileData(instagramUserPostdataFile);
}

nlohmann::ordered_json Homepage::getUserPostDataInJsonFormat(std::string post)
{
    nlohmann::ordered_json userPostData = {
        {"post", post},
        {"postedBy", username},
        {"likedBy", nlohmann::ordered_json::array()}};
    return userPostData;
}

bool Homepage::postAMessage()
{
    std::string post;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\nPost a message :";
    std::getline(std::cin, post);

    nlohmann::ordered_json userPostData = getUserPostDataInJsonFormat(post);
    instagramJsonPostData["Usersposts"].push_back(userPostData);
    instagramFileHandling->writeInstagramJsonFileData(instagramUserPostdataFile, instagramJsonPostData);
    return true;
}

void Homepage::displayLikes(nlohmann::ordered_json likesByUsers)
{
    std::cout << "LikedBy :";
    if (likesByUsers.size() > 0)
    {
        for (auto username : likesByUsers)
        {
            std::cout << username << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "none" << std::endl;
    }
}

bool Homepage::displayMyPost()
{
    instagramJsonPostData = instagramFileHandling->getInstagramJsonFileData(instagramUserPostdataFile);
    bool isAnyPostFoundOnUsername = false;
    for (auto postdata : instagramJsonPostData["Usersposts"])
    {
        if (postdata["postedBy"] == username)
        {
            isAnyPostFoundOnUsername = true;
            std::cout << "\nPost :" << postdata["post"] << std::endl;
            displayLikes(postdata["likedBy"]);
        }
    }
    return isAnyPostFoundOnUsername;
}
