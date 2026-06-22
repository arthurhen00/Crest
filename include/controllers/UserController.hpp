#pragma once

#include "router/Router.hpp"

class UserController {

public:
  static void getUsers(http::HttpRequest &request, http::HttpResponse &response);
  static void getUser(http::HttpRequest &request, http::HttpResponse &response);

};