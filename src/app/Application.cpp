#include "app/Application.hpp"
#include "http/HttpServer.hpp"

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
  server_ = std::make_unique<http::HttpServer>(port, router_);
  server_->start();
}

}