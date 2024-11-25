cmake_minimum_required(VERSION 3.25)

project(netproj)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(libbpl_net)
add_subdirectory(test_udpserver)
add_subdirectory(test_udpclient)
