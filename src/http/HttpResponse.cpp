#include "http/HttpResponse.hpp"

namespace http {

HttpResponse::HttpResponse()
: status_(200) {
  headers_["Content-Type"] = "text/plain";
}

void HttpResponse::status(int code) {
  status_ = code;
}

void HttpResponse::body(const std::string &content) {
  body_ = content;
}

void HttpResponse::json(const std::string &content) {
  header("Content-type", "application/json");
  body_ = content;
}

void HttpResponse::text(const std::string &content) {
  header("Content-type", "text/plain");
  body_ = content;
}

void HttpResponse::header(const std::string &key, const std::string &value) {
  headers_[key] = value;
}

std::string HttpResponse::statusMessage() const {
  switch (status_) {
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
    "HTTP/1.1 " +
    std::to_string(status_) +
    " " +
    statusMessage() +
    "\r\n";

  for (const auto& [key, value] : headers_) {
    response +=
      key +
      ": " +
      value +
      "\r\n";
  }

  response +=
    "Content-Length: " +
    std::to_string(body_.size()) +
    "\r\n";

  response +=
    "\r\n";

  response += body_;

  return response;
}

}