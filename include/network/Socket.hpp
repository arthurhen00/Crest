#pragma once

#include "SocketTypes.hpp"

#include <netinet/in.h>
#include <string>

namespace network {

class Socket {
public:
  Socket();
  Socket(SocketType fd);
  ~Socket();

  Socket(const Socket&) = delete;
  Socket& operator=(const Socket&) = delete;

  Socket(Socket &&other) noexcept;
  Socket& operator=(Socket &&other) noexcept;

  void bind(const sockaddr_in &addr);
  void listen(int backlog);
  Socket accept();

  void connect(const sockaddr_in &addr);
  
  void send(const std::string &data);
  std::string receive();
  
  void close();
  
  SocketType getFd() const;
  bool isValid() const;

private:
  SocketType fd_;
};

}