#pragma once

#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"

#include <functional>
#include <unordered_map>
#include <string>

namespace router {

using Handler = std::function<void(http::HttpRequest&, http::HttpResponse&)>;

class Router {
public:
  void get(const std::string &path, Handler handler);
  void post(const std::string &path, Handler handler);

  bool handle(http::HttpRequest &request, http::HttpResponse &response);
private:
  std::unordered_map<std::string, Handler> routes_;
  std::string makeKey(const std::string &method, const std::string &path);
};

}