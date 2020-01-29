cmake_minimum_required(VERSION 3.13)
project(cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp dns.cpp main.cpp dns.h epoll.cpp epoll.h)