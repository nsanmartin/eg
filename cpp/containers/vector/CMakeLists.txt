cmake_minimum_required(VERSION 3.2)  
project(eg-containters-vector)  
enable_testing()

include_directories(.)
include_directories(../../tests)

file( GLOB TEST_SOURCES "tests/*.cpp")
foreach(testssource ${TEST_SOURCES})
  string( REPLACE ".cpp" "" testnamepath ${testssource} )
  get_filename_component(testname ${testnamepath} NAME)
  add_executable( ${testname} ${testssource} ${SOURCES} )
  add_test(NAME ${testname} COMMAND  ${testname})
endforeach(testssource ${TEST_SOURCES})
