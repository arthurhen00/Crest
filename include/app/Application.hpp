#pragma once


#include "router/Router.hpp"
#include <memory>

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

private:
  router::Router router_;
  std::unique_ptr<http::HttpServer> server_;

};


}