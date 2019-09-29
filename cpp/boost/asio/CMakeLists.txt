cmake_minimum_required(VERSION 2.8.9)  
project(hlp/cpp/boost/asio)  

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost COMPONENTS system)
find_package(Boost COMPONENTS thread)

include_directories(SYSTEM ${Boost_INCLUDE_DIR})


file( GLOB TCP_EX_SOURCES "tcp/*.cpp")
foreach(tcp_ex_source ${TCP_EX_SOURCES})
  string( REPLACE ".cpp" "" namepath ${tcp_ex_source} )
  get_filename_component(fname ${namepath} NAME)
  set(name tcp_${fname})
  add_executable( ${name} ${tcp_ex_source} )
  target_compile_options(${name} PRIVATE -lboost_system -lboost_thread -pthread)
  target_link_libraries(${name} ${Boost_LIBRARIES})
  target_link_libraries(${name} ${CMAKE_THREAD_LIBS_INIT} )

endforeach(tcp_ex_source ${TEST_SOURCES})


