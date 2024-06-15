cmake_minimum_required(VERSION 3.28)
project(moderna_logging)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED true)
set (CMAKE_CXX_SCAN_FOR_MODULES true)

add_library(moderna_logging)
if (NOT moderna_thread_plus)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/libs/thread-plus EXCLUDE_FROM_ALL)
endif()

file (
  GLOB moderna_logging_src
  "${CMAKE_CURRENT_LIST_DIR}/src/*.ccm"
)
target_sources(moderna_logging 
  PUBLIC 
    FILE_SET CXX_MODULES FILES ${moderna_logging_src}
)
target_link_libraries(moderna_logging PRIVATE moderna_thread_plus)

if (
  EXISTS ${CMAKE_CURRENT_LIST_DIR}/../test-lib/CMakeLists.txt 
  AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/../../cmake/CMakeLists.txt 
  AND PROJECT_IS_TOP_LEVEL
)
  include (CTest)
  include (${CMAKE_CURRENT_LIST_DIR}/../../cmake/CMakeLists.txt)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../test-lib test-lib)
  add_test_asan_tsan_usan_ubsan(
    moderna_logging_tests
    ${CMAKE_CURRENT_LIST_DIR}/tests/tests.cpp 
    LIBRARIES moderna_test_lib moderna_logging
  )
  add_executable(
    bench
    ${CMAKE_CURRENT_LIST_DIR}/tests/benchmark.cpp
  )
  target_link_libraries(bench PUBLIC moderna_logging)
elseif ( PROJECT_IS_TOP_LEVEL )
  message("Clone Moderna Library to Test")
endif()