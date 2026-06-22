#include "http/HttpParser.hpp"

#include <sstream>

namespace http {

HttpRequest HttpParser::parse(const std::string &raw) {
  HttpRequest request;

  std::stringstream stream(raw);
  std::string line;

  bool first = true;
  bool body = false;

  while (std::getline(stream, line)) {
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }

    if (body) {
      request.body += line;
      continue;
    }

    if (first) {
      parseStartLine(line, request);
      first = false;
      continue;
    }

    if (line.empty()) {
      body = true;
      continue;
    }

    parseHeader(line, request);
  }

  parseUrl(request);

  return request;
}



void HttpParser::parseStartLine(const std::string &line, HttpRequest &request) {
  std::stringstream ss(line);
  ss >> request.method >> request.path >> request.version;
}



void HttpParser::parseHeader(const std::string &line, HttpRequest &request) {
  auto separator = line.find(':');

  if (separator == std::string::npos) {
    return;
  }

  std::string key = line.substr(0, separator);
  std::string value = line.substr(separator + 1);

  while (!value.empty() && value.front() == ' ') {
    value.erase(0,1);
  }

  request.headers[key] = value;
}

void HttpParser::parseUrl(HttpRequest &request) {
  auto pos = request.path.find('?');

  if (pos == std::string::npos) {
    return;
  }

  std::string query = request.path.substr(pos + 1);
  request.path = request.path.substr(0, pos);

  parseQuery(query, request);
}

void HttpParser::parseQuery(const std::string &query, HttpRequest &request) {
  std::stringstream ss(query);
  std::string item;

  while (std::getline(ss, item, '&')) {
    auto pos = item.find('=');

    if (pos == std::string::npos) {
      continue;
    }

    request.query[item.substr(0, pos)] = item.substr(pos + 1);
  }
}

}