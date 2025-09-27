cmake_minimum_required(VERSION 3.14)
project(TwelveProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0") 

add_library(twelve_lib
    src/array.cpp
    src/twelve.cpp
)

target_include_directories(twelve_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(twelve
    src/main.cpp
)

target_link_libraries(twelve
    PRIVATE
    twelve_lib
)

target_include_directories(twelve
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(test_twelve
    test/test_twelve.cpp
    test/main.cpp
)

target_link_libraries(test_twelve
    PRIVATE
    twelve_lib
    GTest::gtest_main
)

target_include_directories(test_twelve
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(test_twelve)