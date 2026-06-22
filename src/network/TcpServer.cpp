#include "network/TcpServer.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>

namespace network {

TcpServer::TcpServer(int port) : port_(port) {}

void TcpServer::start(Handler handler) {
  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port_);

  socket_.bind(address);
  socket_.listen(10);

  while( 1 ) {
    Socket clientSocket = socket_.accept();

    TcpConnection connection(std::move(clientSocket));

    handler(connection);
  }
}

}