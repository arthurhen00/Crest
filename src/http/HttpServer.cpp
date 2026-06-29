#include "http/HttpServer.hpp"

namespace http {

HttpServer::HttpServer(int port, app::Application &app)
: server_(port), app_(app) {}

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

  request.remoteAddress = connection.getIp();
  request.remotePort = connection.getPort();

  HttpResponse response;

  app_.handle(request, response);

  connection.write(response.build());
}

}