#pragma once

#include <string>
#include <unordered_map>

namespace http {

class HttpResponse {
public:

  HttpResponse();

  void status(int code);
  void body(const std::string &content);
  void json(const std::string &content);
  void text(const std::string &content);
  void header(const std::string &key, const std::string &value);

  std::string build() const;

private:
  int status_;
  std::unordered_map<std::string, std::string> headers_;
  std::string body_;

  std::string statusMessage() const;
};

}