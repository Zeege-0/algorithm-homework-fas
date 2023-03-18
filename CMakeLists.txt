cmake_minimum_required(VERSION 3.17)
project(FAS VERSION 0.1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -fno-rtti -Wzero-as-null-pointer-constant")
message(STATUS "Build type ${CMAKE_BUILD_TYPE}")
message(STATUS "Using ${CMAKE_CXX_COMPILER}")

add_executable(pagerank src/pagerank.cpp)
