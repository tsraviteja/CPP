#include <memory>

#include "gtest/gtest.h"
#include "Item.h"

using Item = foodRecommendationEngine::app::food::Item;

static const uint32_t ITEM_ID = 123;
static const std::string ITEM_NAME = "Roti";
static const double ITEM_PRICE = 40; 

////////////////////////////////////////////
//
// class GivenAItem 
//
////////////////////////////////////////////

class GivenAItem : public ::testing::Test
{
    public:
    virtual void SetUp() override;
    virtual void TearDown() override;

    protected:
    std::shared_ptr<Item> item_;
};

void GivenAItem::SetUp()
{
    item_ = std::make_shared<Item>();
}

void GivenAItem::TearDown() {}

/************** Test for getItemId method **************/
TEST_F(GivenAItem, WhenGetItemIdIsCalled_ThenItemIdIsReturned)
{
    item_->setItemId(ITEM_ID);
    auto result = item_->getItemId();
    EXPECT_EQ(ITEM_ID, result);
}

/************** Test for getItemName method **************/
TEST_F(GivenAItem, WhenGetItemNameIsCalled_ThenItemNameIsReturned)
{
    item_->setItemName(ITEM_NAME);
    auto result = item_->getItemName();
    EXPECT_EQ(ITEM_NAME, result);
}

/************** Test for getItemPrice method **************/
TEST_F(GivenAItem, WhenGetItemPriceIsCalled_ThenItemPriceIsReturned)
{
    item_->setItemPrice(ITEM_PRICE);
    auto result = item_->getItemPrice();
    EXPECT_EQ(ITEM_PRICE, result);
}

/************** Test for setItemId method **************/
TEST_F(GivenAItem, WhenSetItemIdIsCalled_ThenItemIdIsUpdated)
{
    item_->setItemId(ITEM_ID);
    auto result = item_->getItemId();
    EXPECT_EQ(ITEM_ID, result);
}

/************** Test for setItemName method **************/
TEST_F(GivenAItem, WhensetItemNameIsCalled_ThenItemNameIsUpdated)
{
    item_->setItemName(ITEM_NAME);
    auto result = item_->getItemName();
    EXPECT_EQ(ITEM_NAME, result);
}

/************** Test for setItemPrice method **************/
TEST_F(GivenAItem, WhenSetItemPriceIsCalled_ThenItemPriceIsUpdated)
{
    item_->setItemPrice(ITEM_PRICE);
    auto result = item_->getItemPrice();
    EXPECT_EQ(ITEM_PRICE, result);
}
