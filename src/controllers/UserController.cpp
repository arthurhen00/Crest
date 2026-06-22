#include "controllers/UserController.hpp"

void UserController::getUsers(http::HttpRequest&, http::HttpResponse &response) {
  response.json(
    R"([
        {
            "id":1,
            "name":"Arthur"
        }
    ])"
  );
}