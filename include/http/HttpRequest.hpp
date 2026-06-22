#pragma once

#include <string>
#include <unordered_map>

namespace http {

class HttpRequest {
public:
  std::string method;
  std::string path;
  std::string version;

  std::unordered_map<std::string, std::string> headers;
  
  std::string body;

  std::string getHeader(const std::string &key) const;
  bool hasHeader(const std::string &key) const;
};

}