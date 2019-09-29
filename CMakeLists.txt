cmake_minimum_required(VERSION 3.15)
project(myAppPJ)

set(CMAKE_CXX_STANDARD 98)

SET(CMAKE_CXX_FLAGS -pthread)

add_executable(myAppPJ src/main.cpp src/client.cpp include/client.h src/server.cpp include/server.h src/threadshandler.cpp include/threadshandler.h src/watcher.cpp include/watcher.h)