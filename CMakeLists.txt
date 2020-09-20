cmake_minimum_required (VERSION 2.8.11)
project (socket_demo)


SET(CMAKE_CXX_STANDARD 17)


ADD_EXECUTABLE( bare_bones_tcp_serv
    main_test_tcp_serv.cpp
    bare_bones_tcp_server.cpp )

ADD_EXECUTABLE( bare_bones_tcp_client
    main_test_tcp_client.cpp
    bare_bones_tcp_client.cpp )

#TARGET_LINK_LIBRARIES( socket_example LINK_PUBLIC ${Boost_LIBRARIES} )

# compile as static library
add_library(bare_bones_tcp_server_lib STATIC bare_bones_tcp_server.cpp)
set_target_properties(bare_bones_tcp_server_lib  PROPERTIES OUTPUT_NAME "bbtcpserver")
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
install(TARGETS bare_bones_tcp_server_lib 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(FILES bare_bones_tcp_server.h DESTINATION include/bbtcpserver)