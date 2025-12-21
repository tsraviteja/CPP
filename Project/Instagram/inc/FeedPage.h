#include "IFeedpage.h"
#include "InstagramJsonFileHandling.h"
#include "nlohmann/json.hpp"

class Feedpage : public IFeedpage
{
public:
    Feedpage(std::string username, InstagramJsonFileHandling *instagramFileHandling);
    PostInfo moveToNextPost() override;
    PostInfo moveBackToPreviousPost() override;
    bool likePost(PostInfo postData) override;
    PostInfo firtPostInInstagram() override;

protected:
    void doLikePost(PostInfo postData);
    void removeLikeFromPost(PostInfo postData);
    bool isPostedMessageWasAlreadyLiked(PostInfo postData);

protected:
    InstagramJsonFileHandling *instagramFileHandling;
    std::string instagramUserPostdataFile, username;
    nlohmann::ordered_json instagramJsonPostData;
    int userIndex, totalNumberOfPost;
};
