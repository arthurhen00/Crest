#include "router/Router.hpp"

namespace router {

std::string Router::makeKey(const std::string &method, const std::string &path) {
  return method + ":" + path;
}

void Router::get(const std::string &path, Handler handler) {
  routes_[makeKey("GET", path)] = handler;
}

void Router::post(const std::string &path, Handler handler) {
  routes_[makeKey("POST", path)] = handler;
}

bool Router::handle(http::HttpRequest &request, http::HttpResponse &response) {
  auto key = makeKey(request.method, request.path);
  auto it = routes_.find(key);

  if (it == routes_.end()) {
    response.status(404);
    response.body("Route not found");

    return false;
  }

  it->second(request, response);

  return true;
}

}