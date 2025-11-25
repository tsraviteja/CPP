#include <memory>

#include "Request.h"

int main()
{
    std::unique_ptr<API::IRequest> request = std::make_unique<API::Request>();
    auto result = request->get("http://localhost:8080/StudentDetails");
    std::cout << result.first << std::endl;
    std::cout << result.second.dump(4) << std::endl;

    std::string requestBody = R"({
                                    "age": 25
                                 })";
    result = request->patch("http://localhost:8080/StudentDetails/102", requestBody);
    std::cout << result.first << std::endl;
    std::cout << result.second.dump(4) << std::endl;


    requestBody = R"({
                        "name": "Ranveer",
                        "id": "105",
                        "age": 23

                    })";
    result = request->post("http://localhost:8080/StudentDetails", requestBody);
    std::cout << result.first << std::endl;
    std::cout << result.second.dump(4) << std::endl;

    requestBody = R"({
                        "name": "Ranveer",
                        "age": 26
                    })";
    result = request->put("http://localhost:8080/StudentDetails/102", requestBody);
    std::cout << result.first << std::endl;
    std::cout << result.second.dump(4) << std::endl;

    result = request->delete$("http://localhost:8080/StudentDetails/105");
    std::cout << result.first << std::endl;
    std::cout << result.second.dump(4) << std::endl;

    return 0;
}
