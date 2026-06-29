#include "network/TcpConnection.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>

namespace network {

TcpConnection::TcpConnection(Socket socket) 
: socket_(std::move(socket)) {}

TcpConnection::TcpConnection(TcpConnection &&other) noexcept 
: socket_(std::move(other.socket_)) {}

TcpConnection& TcpConnection::operator=(TcpConnection &&other) noexcept {
  if (this != &other) {
    socket_ = std::move(other.socket_);
  }

  return *this;
}

std::string TcpConnection::read() {
  return socket_.receive();
}

void TcpConnection::write(const std::string &data) {
  socket_.send(data);
}

SocketType TcpConnection::getFd() const {
  return socket_.getFd();
}

std::string TcpConnection::getIp() const {
  sockaddr_in addr{};
  socklen_t len = sizeof(addr);

  if (getpeername(socket_.getFd(), (sockaddr*)&addr, &len) < 0) {
    return "unknown";
  }

  return inet_ntoa(addr.sin_addr);
}

int TcpConnection::getPort() const {
  sockaddr_in addr{};
  socklen_t len = sizeof(addr);

  if (getpeername(socket_.getFd(), (sockaddr*)&addr, &len) < 0) {
    return -1;
  }

  return ntohs(addr.sin_port);
}

}