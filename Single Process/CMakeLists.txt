cmake_minimum_required(VERSION 3.10.2)
project(Final_Project)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)
find_package(Boost REQUIRED)

add_executable(DivFindSP src/DivFinder_main.cpp
				src/DivFinder.cpp	include/DivFinder.h
               src/DivFinderSP.cpp	include/DivFinderSP.h)
			   
add_executable(DivFindT src/DivFinderT_main.cpp
				src/DivFinder.cpp	include/DivFinder.h
				src/DivFinderT.cpp	include/DivFinderT.h)

target_include_directories(DivFindSP PRIVATE src include)
target_include_directories(DivFindT PRIVATE src include)


target_link_libraries(DivFindT PRIVATE OpenMP::OpenMP_CXX)

INCLUDE(FindPkgConfig)
#pkg_search_module(CRYPTOPP REQUIRED libcrypto++ >= 6)
#pkg_search_module(BOOST REQUIRED libboost-dev)
