cmake_minimum_required(VERSION 3.15)
project(Lab_10 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(PR_10.1 PR_10.2 tests)

# Executables
add_executable(Lab_10_1 PR_10.1/Lab_10_1.cpp)
add_executable(Lab_10_2 PR_10.2/Lab_10_2.cpp)

# Testing
enable_testing()

add_executable(UnitTest_10_1 tests/UnitTest_10_1.cpp)
add_test(NAME Test_10_1 COMMAND UnitTest_10_1)

add_executable(UnitTest_10_2 tests/UnitTest_10_2.cpp)
add_test(NAME Test_10_2 COMMAND UnitTest_10_2)
