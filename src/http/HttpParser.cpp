#include "http/HttpParser.hpp"

#include <sstream>

namespace http {

HttpRequest HttpParser::parse(const std::string &raw) {
  HttpRequest request;

  std::stringstream stream(raw);
  std::string line;

  bool firstLine = true;

  while (std::getline(stream, line)) {
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }

    if (firstLine) {
      parseStartLine(line, request);
      firstLine = false;
      continue;
    }

    if (line.empty()) {
      break;
    }

    parseHeader(line, request);
  }

  return request;
}



void HttpParser::parseStartLine(const std::string &line, HttpRequest &request) {
  std::stringstream ss(line);
  ss >> request.method >> request.path >> request.version;
}



void HttpParser::parseHeader(const std::string &line, HttpRequest &request) {
  auto separator = line.find(':');

  if(separator == std::string::npos) {
    return;
  }

  std::string key = line.substr(0, separator);
  std::string value = line.substr(separator + 1);

  while (!value.empty() && value.front() == ' ') {
    value.erase(0,1);
  }

  request.headers[key] = value;
}

}