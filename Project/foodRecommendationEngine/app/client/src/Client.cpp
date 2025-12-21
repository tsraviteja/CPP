
#include "Admin.h"
#include "Authentication.h"
#include "Chef.h"
#include "ClientInjection.h"
#include "Engine.h"
#include "Employee.h"
#include "Handler.h"
#include "Notification.h"
#include "UserChoice.h"
#include "UserInput.h"

namespace DataType = foodRecommendationEngine::app::client::dataType;

using Admin = foodRecommendationEngine::app::client::Admin;
using UserChoice = foodRecommendationEngine::app::client::choice::UserChoice;
using AdminChoice = foodRecommendationEngine::app::client::choice::AdminChoice;
using Authentication = foodRecommendationEngine::app::client::Authentication;
using Chef = foodRecommendationEngine::app::client::Chef;
using ChefChoice = foodRecommendationEngine::app::client::choice::ChefChoice;
using ClientInjection = foodRecommendationEngine::app::client::injection;
using Engine = foodRecommendationEngine::app::client::Engine;
using Employee = foodRecommendationEngine::app::client::Employee;
using EmployeeChoice = foodRecommendationEngine::app::client::choice::EmployeeChoice;
using FoodItem = foodRecommendationEngine::app::food::foodItem;
using Handler = foodRecommendationEngine::app::client::Handler;
using IEngine = foodRecommendationEngine::app::client::IEngine;
using IHandler = foodRecommendationEngine::app::client::IHandler;
using MealType = foodRecommendationEngine::app::food::MealType;
using Notification = foodRecommendationEngine::app::client::Notification;
using RecommendedFoodItem = foodRecommendationEngine::app::client::engineDataType::RecommendedFoodItem;
using Option = foodRecommendationEngine::app::client::choice::Option;
using UserInput = foodRecommendationEngine::framework::core::UserIput;

ClientInjection injection;
std::shared_ptr<UserInput> userInput;

void readFoodItem(FoodItem &item)
{
    std::cout << "========================== FoodItem Details ==========================" << std::endl;
    item.id = userInput->takeInputFromUser<int>("Enter Item Id :");
    item.name = userInput->takeStringInputFromUser("Enter Item name :");
    item.price = userInput->takeInputFromUser<double>("Enter Item price :");
    auto mealType = userInput->takeInputChoiceFromUser(MealType::MIN, MealType::MAX,
                                                       "MealType are \n1.Breakfast\n2.Lunch\n3.Dinner\nSelect meal type :");
    item.mealType = MealType(mealType);
    auto isAvailable = userInput->takeInputChoiceFromUser(0, 1, 
                        "Item available status \n1.yes\n2.no\nEnter Item availability status :");
    item.isAvailable = isAvailable == 1 ? true : false;
}

void readUserData(DataType::UserData &data)
{
    std::cout << "========================== UserDeatils ==========================" << std::endl;
    data.id = userInput->takeInputFromUser<int>("Enter Id :");
    data.name = userInput->takeStringInputFromUser("Enter name :");
    data.password = userInput->takeStringInputFromUser("Enter password :");
    auto minimumChoice = static_cast<int>(UserChoice::USER_MIN);
    auto maximumChoice = static_cast<int>(UserChoice::USER_MAX);
    auto role = userInput->takeInputChoiceFromUser(minimumChoice,
                                                   maximumChoice,
                            "The user role :\n1.Chef\n2.Employee\nSelect the role :");

    auto userRole = DataType::UserType(role+1);
    data.role = userRole;
}

void displayDialyMenuItem(const std::vector<DataType::DialyMenuItemData> &dailyMenuItem, const MealType &mealType)
{
    auto mealTypeLiteral = foodRecommendationEngine::app::food::MealTypeLiteral.at(mealType);
    std::cout << "\n\n=================== " << mealTypeLiteral << " DailymenuItemList "
              << "=====================\n\n";
    std::cout << "Index" << std::setw(16) << "DailyMenuItemId" << std::setw(16) << "ItemId";
    std::cout << std::setw(16) << "MealType" << std::endl;
    std::cout << "\n===========================================================\n" << std::endl;

    auto count = 1;
    auto dailyMenuItemCount = dailyMenuItem.size();
    for(auto &item : dailyMenuItem)
    {
        std::cout << "  ";
        std::cout << count << std::setw(16 - (count/10));
        std::cout << item.dailyMenuItemId << std::setw(16);
        std::cout << item.itemId << std::setw(16);
        std::cout << item.mealType << std::endl;
        count++;
    }
}

void displayEmployeeResponse(const std::vector<DataType::EmployeeResponse> &employeeResponse)
{
    std::cout << "\n\n======================== VotingList =========================\n\n";
    std::cout << "Index" << std::setw(16) << "ItemId" << std::setw(16) << "MealType" << std::setw(20) << "TotalVotes"<< std::endl;
    std::cout << "\n=============================================================\n" << std::endl;

    auto count = 1;
    for (const auto &response : employeeResponse)
    {
        std::cout << "  ";
        std::cout << count << std::setw(16 - (count/10));
        std::cout << response.itemId << std::setw(18);
        std::cout << response.mealType << std::setw(16);
        std::cout << response.totalVotes << std::endl;
        count++;
    }
}

void displayMenuItems(const std::vector<std::shared_ptr<
                    foodRecommendationEngine::app::food::Item>> &menuList)
{
    std::cout << "\n\n====================================== MenuList "
              << "=======================================\n\n";
    std::cout << "Index" << std::setw(16) << "ItemId" << std::setw(16) << "ItemName";
    std::cout << std::setw(16) << "Price" << std::setw(16) << "MealType" << std::setw(16) << "IsAvailable" << std::endl;
    std::cout << "\n=======================================================================================\n" << std::endl;

    const auto menuItemCount = menuList.size();
    int count = 1;

    for(auto &item : menuList)
    {
        std::string isAvailable = (item->getItemIsAvailable() == true) ? "Yes" : "No";
        auto mealType = foodRecommendationEngine::app::food::MealTypeLiteral.at(item->getItemMealType());
        std::cout << "  ";
        std::cout << count << std::setw(16 - (count/10));
        std::cout << item->getItemId() << std::setw(17);
        std::cout << item->getItemName() << std::setw(16);
        std::cout << item->getItemPrice() << std::setw(16);
        std::cout << mealType << std::setw(11);
        std::cout << isAvailable << std::endl;
        count++;
    }
    std::cout<< "\n";
}

void displayRecommendedFoodItems(const std::vector<RecommendedFoodItem> &recommendedFoodItems)
{
    std::cout << "\n\n==================================== Recommended FoodItem List "
             << "========================================\n\n";

    std::cout << "Index" << std::setw(12) << "ItemId" << std::setw(12) << "ItemName" << std::setw(28);
    std::cout << "AveargeCompositeScore = " << "(AveargeRating + AverageSentimentalScore) / 2" << std::endl;

    std::cout << "\n================================================================="
              << "======================================\n" << std::endl;

    const auto menuItemCount = recommendedFoodItems.size();
    int count = 1;

    for(auto &recommendedFoodItem : recommendedFoodItems)
    {
        std::cout << "  ";
        std::cout << count << std::setw(12 - (count/10));
        std::cout << recommendedFoodItem.item->getItemId() << std::setw(11);
        std::cout << recommendedFoodItem.item->getItemName() << std::setw(18);
        std::cout << recommendedFoodItem.averageCompositeScore << std::setw(14)
                  << " = (" << recommendedFoodItem.averageRating << " + "
                  << recommendedFoodItem.averageSentimentalScore << ") / 2" << std::endl;
        count++;
    }
    std::cout<< "\n"; 
}

void deleteMenuItem()
{
    std::cout << "========================== Delete MenuItem ==========================" << std::endl;
    int itemId = userInput->takeInputFromUser<int>("Enter ItemId for delete :");
    auto result = injection.admin->deleteMenuItem(itemId);
    if (result)
    {
        std::cout << "Item deleted successfully!!!" << std::endl;
    }
    else
    {
        std::cout << "Failed to delete Item!!!" << std::endl;
    }
}

void updateMenuItem()
{
    FoodItem item;
    readFoodItem(item);
    auto result = injection.admin->updateMenuItem(item);
    if (result)
    {
        std::cout << "Menu Item updated successfully!!!" << std::endl;
    }
    else
    {
        std::cout << "Failed to update Menu Item!!!" << std::endl;
    }
}

void addMenuItem()
{
    FoodItem item;
    readFoodItem(item);
    auto result = injection.admin->addMenuItem(item);
    if (result)
    {
        std::cout << "Menu Item added successfully!!!" << std::endl;
        injection.notification->notifyEmployee(DataType::NotificationType::ITEM_ADDED,
                                               item.name);
    }
    else
    {
        std::cout << "Failed to add Menu Item!!!" << std::endl;
    }
}

void deleteUser()
{
    std::cout << "========================== Delete User ==========================" << std::endl;
    int id = userInput->takeInputFromUser<int>("Enter UserId for delete :");
    auto result = injection.admin->deleteUser(id);
    if (result)
    {
        std::cout << "user deleted successfully!!!" << std::endl;
    }
    else
    {
        std::cout << "Failed to delete user!!!" << std::endl;
    }
}

void addUser()
{
    DataType::UserData data;
    readUserData(data);
    auto result = injection.admin->addUser(data);
    if (result)
    {
        std::cout << "user added successfully!!!" << std::endl;
    }
    else
    {
        std::cout << "Failed to add user!!!" << std::endl;
    }
}


void readFeedbackData(DataType::FeedbackData &feedbackData)
{
    std::cout << "\n========================== Feedback ==========================" << std::endl;
    feedbackData.itemId = userInput->takeInputFromUser<int>("Enter Item Id :");
    feedbackData.rating = userInput->takeInputFromUser<double>("Enter rating :");
    feedbackData.comment = userInput->takeStringInputFromUser("Enter feedback comment :");
    feedbackData.momRecipe = userInput->takeStringInputFromUser("Please share your mom's recipe :");
}

void providFeedback()
{
    DataType::FeedbackData feedbackData;
    readFeedbackData(feedbackData);
    feedbackData.employeeId = injection.employee->getId();
    auto result = injection.employee->provideFeedback(feedbackData);
    if (result)
    {
        std::cout << "Feedback is submitted successfully!!!" << std::endl;
    }
    else
    {
        std::cout << "failed to submit the feedback may be item doesn't exists in Menu!!!" << std::endl;
    }
}


void readMealType(MealType &mealType)
{
    std::cout << "\n";
    auto selectedMealType = userInput->takeInputChoiceFromUser(MealType::MIN, MealType::MAX,
                                       "MealType are \n1.Breakfast\n2.Lunch\n3.Dinner\nSelect meal type :");
    mealType = MealType(selectedMealType);
}

void voteForDailyMenuItem()
{
    std::cout << "\n================= Vote For DailymenuItem ===================" << std::endl;
    auto itemId = userInput->takeInputFromUser<int>("Enter Item Id for vote :");
    auto result = injection.employee->voteForDailyMenuItem(itemId);
    if (result)
    {
        std::cout << "Voting is Successful!" << std::endl;
    }
    else
    {
        std::cout << "Voting is Failed may be alreday voted or Item Id not exists!" << std::endl;
    }
}

void employeePage()
{
    while (true)
    {
        std::cout << "\n/********************************************************" << std::endl;
        std::cout << "                        Employee                           " << std::endl;
        std::cout << "********************************************************/" << std::endl;

        auto id = injection.employee->getId();
        auto notificationMessage = injection.notification->getNotification(id);
        if (!notificationMessage.empty())
        {
            std::cout << "Notification :\n"<< notificationMessage << std::endl;
            injection.notification->deleteNotification(id);
        }

        std::cout << "\n1.ViewMenuItem\n2.ViewDailyMenuItem\n3.ProvideFeedback\n4.VoteForDailyMenu";
        std::cout << "\n5.Exit\n";

        int choice = userInput->takeInputFromUser<int>("Select your choice :");
        auto employeeChoice = EmployeeChoice(choice);

        MealType mealType;

        switch (employeeChoice)
        {
            case EmployeeChoice::VIEW_MENU : 
                                {
                                    auto menuList = injection.admin->viewMenuList();
                                    displayMenuItems(menuList);
                                    break;
                                }

            case EmployeeChoice::VIEW_DAILY_MENU : 
                                {
                                    readMealType(mealType);
                                    auto dailyMenuItemList = injection.employee->viewDailyMenuItem(mealType);
                                    displayDialyMenuItem(dailyMenuItemList, mealType);
                                    break;
                                }

            case EmployeeChoice::PROVIDE_FEED_BACK : providFeedback();
                                                     break;

            case EmployeeChoice::VOTE_FOR_DAILY_MENU : voteForDailyMenuItem();
                                                        break;

            case EmployeeChoice::EMPOLYEE_EXIST : {
                                                    std::cout << "Employee Existed!!!" << std::endl;
                                                    return;
                                                  }

            default : std::cout << "Invalid choice trye again!" << std::endl;
                      break;
        }
    }
}

void readRollOutmenuItemData(DataType::RollOutMenuItemData &data)
{
    std::cout << "\n";
    data.itemId = userInput->takeInputFromUser<int>("Enter itemId :");
    auto mealType = userInput->takeInputChoiceFromUser(MealType::MIN, MealType::MAX,
                                                       "MealType are \n1.Breakfast\n2.Lunch\n3.Dinner\nSelect your choice :");
    data.mealType = MealType(mealType);
}

void rollOutDailyMenuItem()
{
    while (true)
    {
        std::cout << "\n========================== RolloutMenuItem ==========================" << std::endl;
        auto choice = userInput->takeInputChoiceFromUser(Option::YES, Option::NO,
                                                         "Enter 1 for Yes to add or 2 for NO to rollout dailyMenuItem :");
        auto UserChoice = Option(choice);
        if (UserChoice == Option::YES)
        {
            DataType::RollOutMenuItemData rollOutDailyMenuItemData;
            readRollOutmenuItemData(rollOutDailyMenuItemData);
            auto result = injection.chef->rollOutDialyMenuItem(rollOutDailyMenuItemData);
            if (result)
            {
                std::cout << "item is rollout succesfully!!!" << std::endl;
            }
            else
            {
                std::cout << "item failed to rollout!!!" << std::endl;
            }
        }
        else
        {
            break;
        }
    }
}

void chefPage()
{
    while (true)
    {
        std::cout << "\n/********************************************************" << std::endl;
        std::cout << "                         Chef                            " << std::endl;
        std::cout << "********************************************************/" << std::endl;

        std::cout << "\n1.ViewMenuItem\n2.RecommendedItemsFromEngine\n3.RollOutDailymenuItem\n4.ViewEmployeeResponse\n5.Exit\n";

        int choice = userInput->takeInputFromUser<int>("Select your choice :");
        auto chefChoice = ChefChoice(choice);
        MealType mealType;

        switch (chefChoice)
        {
            case ChefChoice::VIEW_MENU_ITEM :
                            {
                                auto menuList = injection.chef->viewMenuList();
                                displayMenuItems(menuList);
                                break;
                            }
            
            case ChefChoice::RECOMMENDED_ITEMS_FROM_ENGINE :
                            {
                                readMealType(mealType);
                                auto recommendedFoodItems = injection.chef->getRecommendedItemsFromEngine(mealType);
                                displayRecommendedFoodItems(recommendedFoodItems);
                                break;
                            }

            case ChefChoice::ROLL_OUT_DAILY_MENU_ITEM :
                            {
                                rollOutDailyMenuItem();
                                break;
                            }

            case ChefChoice::VIEW_EMPLOYEE_RESPONSE :
                            {
                                auto employeeResponse = injection.chef->viewEmployeeResponse();
                                displayEmployeeResponse(employeeResponse);
                                break;
                            }

            case ChefChoice::CHEF_EXIT :
                            {
                                std::cout << "Chef exited !!!" << std::endl;
                                return;
                            }

            default : std::cout << "Invalid Choice try agian!!!" << std::endl;
                      break;
        }
    }
}

void adminPage()
{
    while (true)
    {
        std::cout << "\n/********************************************************" << std::endl;
        std::cout << "                         Admin                           " << std::endl;
        std::cout << "********************************************************/" << std::endl;

        std::cout << "\n1.AddUser\n2.DeleteUser\n3.AddMenuItem\n4.UpdateMenuItem";
        std::cout << "\n5.DeleteMenuItem\n6.ViewMenuItem\n7.Exit\n";

        int choice = userInput->takeInputFromUser<int>("Select your choice :");
        auto adminChoice = AdminChoice(choice);

        switch (adminChoice)
        {
            case AdminChoice::ADD_USER :
                            addUser();
                            break;

            case AdminChoice::DELETE_UESR :
                            deleteUser();
                            break;

            case AdminChoice::ADD_MENU_ITEM :
                            addMenuItem(); 
                            break;

            case AdminChoice::UPDATE_MENU_ITEM :
                            updateMenuItem();
                            break;

            case AdminChoice::DELETE_MENU_ITEM :
                            deleteMenuItem();  
                            break;

            case AdminChoice::DISPLAY_MENU_ITEM :
                            {
                                auto menuList = injection.admin->viewMenuList();
                                displayMenuItems(menuList);
                                break;
                            }

            case AdminChoice::ADMIN_EXIST :
                            {
                                std::cout << "Admin exited!!!" << std::endl;
                                return;
                            }

            default : std::cout << "Invalid Choice try agian!!!" << std::endl;
                      break;
        }
    }
}

void readUserCrendentialsData(DataType::UserCredentailData &crendentialData)
{
    std::cout<<"\n";
    crendentialData.id = userInput->takeInputFromUser<int>("Enter your Id :");
    crendentialData.password = userInput->takeStringInputFromUser("Enter Password :");
}

bool validateUser(DataType::UserType &userType,
                  DataType::UserCredentailData &crendentialData)
{
    std::cout << "\n========================== Login ==========================" << std::endl;
    readUserCrendentialsData(crendentialData);
    auto isValidUser = injection.authentication->login(crendentialData.id,
                                                       crendentialData.password, userType);
    return isValidUser;
}

void initialize(std::shared_ptr<IHandler> &handler, std::shared_ptr<IEngine> &engine)
{
    injection.admin = std::make_shared<Admin>(handler);
    injection.authentication = std::make_shared<Authentication>(handler);
    injection.chef = std::make_shared<Chef>(handler, engine);
    injection.employee = std::make_shared<Employee>(handler);
    injection.notification = std::make_shared<Notification>(handler);
}

/************************** Welcome to Cafeteria *****************************/
int main()
{
    auto startClient = true;
    std::shared_ptr<IHandler> handler = std::make_shared<Handler>();
    std::shared_ptr<IEngine> engine = std::make_shared<Engine>(handler);
    initialize(handler, engine);
    userInput = std::make_shared<UserInput>();

    while (startClient)
    {
        std::cout << "\n/********************************************************" << std::endl;
        std::cout << "                   Welcome To Cafeteria                  " << std::endl;
        std::cout << "********************************************************/" << std::endl;

        std::cout << "\n1.Admin\n2.Chef\n3.Employee\n4.Exit";
        int choice = userInput->takeInputFromUser<int>("\nEnter your choice :");

        auto user = DataType::UserType(choice);
        auto userChoice = UserChoice(choice);
        DataType::UserCredentailData crendentialData;
        bool isValidUser;
        switch (userChoice)
        {
            case UserChoice::ADMIN : isValidUser = validateUser(user, crendentialData);
                                     if (isValidUser)
                                     {
                                        std::cout << "Admin login sucessful!" << std::endl;
                                        injection.admin->setId(crendentialData.id);
                                        adminPage();
                                     }
                                     else
                                     {
                                        std::cout << "Invalid User or wrong crendentails!!!" << std::endl;
                                     }
                                     break;

            case UserChoice::CHEF : isValidUser = validateUser(user, crendentialData);
                                    if (isValidUser)
                                    {
                                        std::cout << "Chef login sucessful!" << std::endl;
                                        injection.chef->setId(crendentialData.id);
                                        chefPage();
                                    }
                                    else
                                    {
                                        std::cout << "Invalid User or wrong crendentails!!!" << std::endl;
                                    }
                                    break;

            case UserChoice::EMPOLYEE : isValidUser = validateUser(user, crendentialData);
                                        if (isValidUser)
                                        {
                                            std::cout << "Employee login sucessful!" << std::endl;
                                            injection.employee->setId(crendentialData.id);
                                            employeePage();
                                        }
                                        else
                                        {
                                            std::cout << "Invalid User or wrong crendentails!!!" << std::endl;
                                        }
                                        break;

            case UserChoice::USER_EXIT : startClient = false;
                                         break;

            default : std::cout << "Invalid choice, try again!!!" << std::endl;
                      break;
        }
    }
    return 0;
}
