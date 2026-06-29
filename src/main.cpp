#include "app/Application.hpp"
#include "middleware/LoggerMiddleware.hpp"
#include "controllers/UserController.hpp"

int main() {
    app::Application app;

    app.use(middleware::LoggerMiddleware::create());

    app.get("/users", UserController::getUsers);
    app.get("/users/:id", UserController::getUser);

    app.listen(8080);
}