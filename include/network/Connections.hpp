#pragma once

#include <netinet/in.h>
#include <sys/socket.h>

namespace network {

constexpr int kDomain   = AF_INET;
constexpr int kFamily   = kDomain;
constexpr int kType     = SOCK_STREAM;  ///< TCP
constexpr int kProtocol = 0;
constexpr int kAllInterfaces = INADDR_ANY;

}