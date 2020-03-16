cmake_minimum_required(VERSION 3.0.0)
project(prime_server)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(prime_server
  main.cpp
  src/PrimeServer.cpp
  include/PrimeServer.hpp
  src/TCPConn.cpp
  include/TCPConn.hpp
)

target_link_libraries(prime_server -lpthread)