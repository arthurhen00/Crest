#include "http/HttpResponse.hpp"

namespace http {

HttpResponse::HttpResponse()
: status_(200), contentType_("text/plain") {}

void HttpResponse::status(int code) {
  status_ = code;
}

void HttpResponse::body(const std::string &content) {
  body_ = content;
}

void HttpResponse::json(const std::string &content) {
  contentType_ = "application/json";
  body_ = content;
}

std::string HttpResponse::statusMessage() const {
  switch(status_) {
    case 200:
      return "OK";

    case 201:
      return "Created";

    case 400:
      return "Bad Request";

    case 404:
      return "Not Found";

    case 500:
      return "Internal Server Error";

    default:
      return "";
  }
}

std::string HttpResponse::build() const {
  std::string response;

  response +=
    "HTTP/1.1 "
    +
    std::to_string(status_)
    +
    " "
    +
    statusMessage()
    +
    "\r\n";

  response +=
    "Content-Type: "
    +
    contentType_
    +
    "\r\n";

  response +=
    "Content-Length: "
    +
    std::to_string(body_.size())
    +
    "\r\n";

  response +=
    "\r\n";

  response += body_;

  return response;
}

}