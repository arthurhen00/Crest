#pragma once

#include "network/TcpServer.hpp"
#include "http/HttpParser.hpp"
#include "app/Application.hpp"

namespace http {

class HttpServer {
public:
  HttpServer(int port, app::Application &app);

  void start();
private:
  network::TcpServer server_;
  app::Application &app_;
  HttpParser parser_;

  void handle(network::TcpConnection &connection);
};

}