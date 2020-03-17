cmake_minimum_required(VERSION 3.0.0)
project(prime_server)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenMP REQUIRED)
find_package(Boost REQUIRED)

include_directories(include)

add_executable(prime_server
  main.cpp
  src/PrimeServer.cpp
  include/PrimeServer.hpp
  src/DivFinder.cpp
  include/DivFinder.h
  src/DivFinderT.cpp
  include/DivFinderT.h
  src/TCPConn.cpp
  include/TCPConn.hpp
)

target_link_libraries(prime_server PRIVATE OpenMP::OpenMP_CXX -lpthread)
#target_link_libraries(prime_server PRIVATE OpenMP::OpenMP_CXX)