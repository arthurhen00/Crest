#include "middleware/LoggerMiddleware.hpp"

#include <iostream>
#include <chrono>

namespace middleware {

Middleware LoggerMiddleware::create() {
  return [](http::HttpRequest& request, http::HttpResponse& response, Next next) {
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "[REQUEST] " << request.method << " " << request.path << std::endl;

    next(request, response);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "[RESPONSE] " << request.method << " " << request.path << " " << duration.count() << "ms" << std::endl;
  };
}

}