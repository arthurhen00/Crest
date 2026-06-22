#pragma once

#include "HttpRequest.hpp"

#include <string>

namespace http {

class HttpParser {
public:
  HttpRequest parse(const std::string &raw);

private:
  void parseStartLine(const std::string &line, HttpRequest &request);
  void parseHeader(const std::string &line, HttpRequest &request);
};

}