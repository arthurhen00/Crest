#include "controllers/UserController.hpp"

void UserController::getUsers(http::HttpRequest &request, http::HttpResponse &response) {
  std::string name = request.query["name"];
  std::string age = request.query["age"];

  response.json(
    std::string(R"({
      "query_name": ")")
    + name +
    R"(",
      "query_age": ")"
    + age +
    R"("
    })"
  );
}

void UserController::getUser(http::HttpRequest &request, http::HttpResponse &response) {
  auto id = request.params["id"];

  response.json(
    std::string(R"({
      "route_id": ")")
    + id +
    R"("
    })"
  );
}