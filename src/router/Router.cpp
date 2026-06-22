#include "router/Router.hpp"

#include <iostream>

namespace router {

void Router::get(const std::string &path, Handler handler) {
  std::cout << "[Router] register " << "GET " << path << std::endl;

  routes_.push_back({"GET", path, handler});
}

void Router::post(const std::string &path, Handler handler) {
  std::cout << "[Router] register " << "POST " << path << std::endl;

  routes_.push_back({"POST", path, handler});
}

bool Router::handle(http::HttpRequest &request, http::HttpResponse &response) {
  std::cout << "[Router] method=" << request.method << " path=" << request.path << std::endl;

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

}