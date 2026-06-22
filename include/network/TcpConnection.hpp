#pragma once

#include "Socket.hpp"

namespace network {

class TcpConnection {
public:
  TcpConnection(Socket socket);

  TcpConnection(const TcpConnection&) = delete;
  TcpConnection& operator=(const TcpConnection&) = delete;

  TcpConnection(TcpConnection &&other) noexcept;
  TcpConnection& operator=(TcpConnection &&other) noexcept;

  std::string read();
  void write(const std::string &data);

  SocketType getFd() const;

private:
  Socket socket_;
};

}