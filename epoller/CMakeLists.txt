#

cmake_minimum_required(VERSION 3.0.0)

project(server)

add_executable(server_epoll server.cpp epoller.cpp)