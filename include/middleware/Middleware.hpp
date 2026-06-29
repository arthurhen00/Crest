#pragma once

#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"

#include <functional>

namespace middleware {

using Next = std::function<void(http::HttpRequest&, http::HttpResponse&)>;
using Middleware = std::function<void(http::HttpRequest&, http::HttpResponse&, Next)>;

}