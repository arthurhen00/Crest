#include "app/Application.hpp"

#include "controllers/UserController.hpp"

int main() {
    app::Application app;

    app.get("/users", UserController::getUsers);

    app.get("/users/:id", UserController::getUser);

    app.listen(8080);
}