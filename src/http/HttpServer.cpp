#include "http/HttpServer.hpp"

namespace http {

HttpServer::HttpServer(int port, router::Router &router)
: server_(port), router_(router) {}

void HttpServer::start() {
  server_.start(
    [this](network::TcpConnection& connection) {
      handle(connection);
    }
  );
}

void HttpServer::handle(network::TcpConnection &connection) {
  auto raw = connection.read();
  auto request = parser_.parse(raw);
  HttpResponse response;

  router_.handle(request, response);

  connection.write(response.build());
}

}