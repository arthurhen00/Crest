#include "http/HttpRequest.hpp"

namespace http {

std::string HttpRequest::getHeader(const std::string &key) const {
  auto it = headers.find(key);

  if (it == headers.end()) {
      return "";
  }

  return it->second;
}

std::string HttpRequest::getParam(const std::string &key) const {
  auto it = params.find(key);

  if (it == params.end()) {
      return "";
  }

  return it->second;
}

std::string HttpRequest::getQuery(const std::string &key) const {
  auto it = query.find(key);

  if (it == query.end()) {
      return "";
  }

  return it->second;
}

}