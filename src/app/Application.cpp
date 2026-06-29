#include "app/Application.hpp"
#include "http/HttpServer.hpp"

#include <iostream>

namespace app {

Application::Application() {}

Application::~Application() = default;

void Application::get(const std::string &path, router::Handler handler) {
  router_.get(path, handler);
}

void Application::post(const std::string &path, router::Handler handler) {
  router_.post(path, handler);
}

void Application::listen(int port) {
  std::cout << "[SERVER]\n";
  std::cout << "  Listening on: 0.0.0.0:" << port << std::endl;

  router_.printRoutes();

  server_ = std::make_unique<http::HttpServer>(port, *this);
  server_->start();
}

void Application::use(middleware::Middleware middleware) {
  middlewares_.push_back(middleware);
}

void Application::handle(http::HttpRequest &request, http::HttpResponse &response) {
  size_t index = 0;
  middleware::Next next;

  next = [&](http::HttpRequest &req, http::HttpResponse &res) {
    if (index < middlewares_.size()) {
      auto current = middlewares_[index++];

      current(req, res, next);
    } else {
      router_.handle(req, res);
    }
  };

  next(request, response);
}

}