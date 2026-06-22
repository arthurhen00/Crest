#include "app/Application.hpp"

#include "controllers/UserController.hpp"

int main() {
    app::Application app;

    app.get("/users", UserController::getUsers);

    app.listen(8080);
}