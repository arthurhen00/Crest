#pragma once

#include "router/Router.hpp"
#include "middleware/Middleware.hpp"

#include <memory>
#include <vector>

namespace http {
class HttpServer;
}

namespace app {

class Application {

public:
  Application();
  ~Application();

  void listen(int port);

  void get(const std::string &path, router::Handler handler);
  void post(const std::string &path, router::Handler handler);
  void use(middleware::Middleware middleware);
  void handle(http::HttpRequest &request, http::HttpResponse &response);

private:
  router::Router router_;
  std::unique_ptr<http::HttpServer> server_;
  std::vector<middleware::Middleware> middlewares_;

};


}