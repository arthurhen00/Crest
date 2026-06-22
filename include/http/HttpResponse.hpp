#pragma once

#include <string>

namespace http {

class HttpResponse {
public:

  HttpResponse();

  void status(int code);
  void body(const std::string &content);
  void json(const std::string &content);
  std::string build() const;

private:
  int status_;
  std::string body_;
  std::string contentType_;

  std::string statusMessage() const;
};

}