#pragma once

#include "TcpConnection.hpp"

#include <functional>

namespace network {

class TcpServer {

public:
  using Handler = std::function<void(TcpConnection&)>;
  TcpServer(int port);
  
  void start(Handler handler);

private:
  Socket socket_;

  int port_;
};

}