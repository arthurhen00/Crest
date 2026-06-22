#include "http/HttpRequest.hpp"

namespace http {

std::string HttpRequest::getHeader(const std::string &key) const {
  auto it = headers.find(key);
  
  if (it == headers.end()) {
      return "";
  }

  return it->second;
}

bool HttpRequest::hasHeader(const std::string &key) const {
  return headers.find(key) != headers.end();
}

}