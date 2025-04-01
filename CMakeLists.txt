cmake_minimum_required(VERSION 3.10)
project(AlgoPack)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add main source file
add_library(LinkedList main.cpp)

# Add Google Test
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable
add_executable(test_linkedlist tests/test_linkedlist.cpp)
target_link_libraries(test_linkedlist LinkedList ${GTEST_LIBRARIES} pthread)

# Add test
add_test(NAME LinkedListTests COMMAND test_linkedlist)
