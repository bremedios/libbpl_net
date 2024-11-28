cmake_minimum_required(VERSION 3.25)

project(test_udpserver)

set(CMAKE_CXX_STANDARD 20)


include_directories(../libbpl_net/include)
add_executable(test_udpserver main.cpp)

target_link_libraries(test_udpserver PRIVATE bpl_net)
