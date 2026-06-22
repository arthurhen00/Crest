#include "network/TcpConnection.hpp"

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

}