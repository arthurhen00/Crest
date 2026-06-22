#pragma once

#include "network/TcpServer.hpp"
#include "http/HttpParser.hpp"
#include "router/Router.hpp"

namespace http {

class HttpServer {
public:
  HttpServer(int port, router::Router &router);

  void start();
private:
  network::TcpServer server_;
  router::Router& router_;
  HttpParser parser_;

  void handle(network::TcpConnection &connection);
};

}