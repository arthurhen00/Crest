#pragma once

#include "Route.hpp"
#include "RouteMatcher.hpp"

#include <vector>

namespace router {

class Router {
public:
  void get(const std::string &path, Handler handler);
  void post(const std::string &path, Handler handler);

  bool handle(http::HttpRequest &request, http::HttpResponse &response);

  void printRoutes() const;

private:
  std::vector<Route> routes_;
  RouteMatcher matcher_;
};

}