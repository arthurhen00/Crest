#include "router/RouteMatcher.hpp"

#include <sstream>
#include <vector>

namespace router {

static std::vector<std::string> split(const std::string &value) {
  std::vector<std::string> result;
  std::stringstream ss(value);
  std::string part;

  while (std::getline(ss, part, '/')) {
    if (!part.empty()) {
      result.push_back(part);
    }
  }

  return result;
}

bool RouteMatcher::match(const Route &route, http::HttpRequest &request) {
  if (route.method != request.method) {
    return false;
  }

  auto routeParts = split(route.path);
  auto requestParts = split(request.path);

  if (routeParts.size() != requestParts.size()) {
    return false;
  }

  for (size_t i = 0; i < routeParts.size(); i++) {
    auto& r = routeParts[i];
    auto& p = requestParts[i];
    
    if (r[0] == ':') {
      request.params[r.substr(1)] = p;
    } else {
      if (r != p) {
        return false;
      }
    }
  }

  return true;
}

}