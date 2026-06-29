cmake_minimum_required(VERSION 3.20)

project(MiniRestServer
    VERSION 1.0
    LANGUAGES CXX
)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(SOURCES
    src/main.cpp

    src/app/Application.cpp

    src/controllers/UserController.cpp

    src/http/HttpParser.cpp
    src/http/HttpRequest.cpp
    src/http/HttpResponse.cpp
    src/http/HttpServer.cpp

    src/middleware/LoggerMiddleware.cpp

    src/network/Socket.cpp
    src/network/TcpServer.cpp
    src/network/TcpConnection.cpp

    src/router/RouteMatcher.cpp
    src/router/Router.cpp
)


add_executable(
    server
    ${SOURCES}
)


target_include_directories(
    server
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)


target_compile_options(
    server
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)


set_target_properties(
    server
    PROPERTIES
        OUTPUT_NAME "server"
)