cmake_minimum_required(VERSION 3.25)

project(bpl_net)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

find_package(CURL REQUIRED)

include_directories(include)

set(PUBLIC_HEADER include/bpl/net/Http.h include/bpl/net/Udp.h include/bpl/net/AddrInfo.h)
set(SOURCE_FILES src/Http.cpp src/Udp.cpp src/AddrInfo.cpp)

add_library(bpl_net SHARED ${SOURCE_FILES} ${PUBLIC_HEADER} )
target_link_libraries(bpl_net PRIVATE ${CURL_LIBRARIES} bpl_storage)

install(TARGETS bpl_net DESTINATION lib)
install(FILES include/bpl/net/Http.h DESTINATION include/bpl/net)
install(FILES include/bpl/net/Udp.h DESTINATION include/bpl/net)
install(FILES include/bpl/net/AddrInfo.h DESTINATION include/bpl/net)
