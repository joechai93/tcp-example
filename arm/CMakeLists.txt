
cmake_minimum_required (VERSION 3.0)
project (socket_demo)

SET(CMAKE_SYSTEM_NAME Linux)

# comment these out if dont want arm
SET(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
SET(CMAKE_ASM_COMPILER arm-linux-gnueabihf-gcc)

SET(CMAKE_LIBRARY_ARCHITECTURE arm-linux-gnueablihf)
SET(CMAKE_FIND_ROOT_PATH /opt/cross-pi-libs)
include_directories("/opt/cross-pi-libs/include")
link_directories("/opt/cross-pi-libs/include")


SET(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 3.3.4 REQUIRED NO_MODULE)

ADD_EXECUTABLE( bare_bones_tcp_serv
    ${CMAKE_SOURCE_DIR}/../main_test_tcp_serv.cpp
    ${CMAKE_SOURCE_DIR}/../bare_bones_tcp_server.cpp )

ADD_EXECUTABLE( bare_bones_tcp_client
    ${CMAKE_SOURCE_DIR}/../main_test_tcp_client.cpp
    ${CMAKE_SOURCE_DIR}/../bare_bones_tcp_client.cpp )


target_compile_options(bare_bones_tcp_client PRIVATE -O3 )

target_link_libraries(bare_bones_tcp_serv
    PRIVATE
        Eigen3::Eigen)
