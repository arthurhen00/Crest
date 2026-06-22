#pragma once

#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"

#include <functional>
#include <string>

namespace router {

using Handler = std::function<void(http::HttpRequest&, http::HttpResponse&)>;

struct Route {
  std::string method;
  std::string path;

  Handler handler;

};

}