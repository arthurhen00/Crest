#pragma once

#include "Route.hpp"

namespace router {

class RouteMatcher {

public:
  bool match(const Route &route, http::HttpRequest &request);

};


}