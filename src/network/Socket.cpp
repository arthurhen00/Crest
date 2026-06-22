#include "network/Socket.hpp"
#include "network/Connections.hpp"

#include <sys/socket.h>
#include <unistd.h>
#include <stdexcept>

namespace network {

Socket::Socket() {
  fd_ = socket(kDomain, kType, kProtocol);

  if (fd_ == invalidSocket) {
    throw std::runtime_error("socket creation failed");
  }
}

Socket::Socket(SocketType fd) : fd_(fd) { 
  if (fd_ == invalidSocket) {
    throw std::runtime_error("invalid socket");
  }
}

Socket::~Socket() {
  close();
}

Socket::Socket(Socket &&other) noexcept {
  fd_ = other.fd_;
  other.fd_ = invalidSocket;
}


Socket& Socket::operator=(Socket &&other) noexcept {
  if (this != &other) {
    close();

    fd_ = other.fd_;
    other.fd_ = invalidSocket;
  }

  return *this;
}

void Socket::bind(const sockaddr_in &addr) {
  if (::bind(fd_, (sockaddr*)&addr, sizeof(addr)) < 0) {
    throw std::runtime_error("bind failed");
  }
}

void Socket::listen(int backlog) {
  if (::listen(fd_, backlog) < 0) {
    throw std::runtime_error("listen failed");
  }
}

Socket Socket::accept() {
  SocketType client = ::accept(fd_, nullptr, nullptr);

  if (client == invalidSocket) {
    throw std::runtime_error("accept failed");
  }

  return Socket(client);
}

void Socket::connect(const sockaddr_in &address) {
  if (::connect(fd_, (sockaddr*)&address, sizeof(address)) < 0) {
      throw std::runtime_error("connect failed");
  }
}

void Socket::send(const std::string &data) {
  size_t total = 0;

  while (total < data.size()) {
    int sent = ::send(fd_, data.data() + total, data.size() - total, 0);

    if (sent <= 0) {
      throw std::runtime_error("send failed");
    }

    total += sent;
  }
}

std::string Socket::receive() {
  char buffer[4096];

  int bytes = ::recv(fd_, buffer, sizeof(buffer), 0);

  if (bytes <= 0) {
    return "";
  }

  return std::string(buffer, bytes);
}

void Socket::close() {
  if (isValid()) {
    ::close(fd_);
    fd_ = invalidSocket;
  }
}

SocketType Socket::getFd() const {
  return fd_;
}

bool Socket::isValid() const {
  return fd_ != invalidSocket;
}

}