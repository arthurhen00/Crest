#include "router/Router.hpp"

#include <iostream>

namespace router {

void Router::get(const std::string &path, Handler handler) {
  routes_.push_back({"GET", path, handler});
}

void Router::post(const std::string &path, Handler handler) {
  routes_.push_back({"POST", path, handler});
}

bool Router::handle(http::HttpRequest &request, http::HttpResponse &response) {
  for (auto& route : routes_) {
    request.params.clear();

    if (matcher_.match(route, request)) {
      route.handler(request, response);
      return true;
    }
  }

  response.status(404);
  response.body("Route not found");

  return false;
}

void Router::printRoutes() const {
    std::cout << "[ROUTER] registered routes:\n";

    for (const auto& route : routes_) {
      std::cout << "  " << route.method << "  " << route.path << std::endl;
    }
}

}