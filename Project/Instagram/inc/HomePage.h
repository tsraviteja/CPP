#include "IHomepage.h"
#include "InstagramJsonFileHandling.h"

class Homepage : public IHomepage
{
public:
    Homepage(std::string username, InstagramJsonFileHandling *instagramFileHandling);
    bool postAMessage() override;
    bool displayMyPost() override;

protected:
    void displayLikes(nlohmann::ordered_json likesByUsers);
    nlohmann::ordered_json getUserPostDataInJsonFormat(std::string post);

private:
    InstagramJsonFileHandling *instagramFileHandling;
    std::string instagramUserPostdataFile, username;
    nlohmann::ordered_json instagramJsonPostData;
};
