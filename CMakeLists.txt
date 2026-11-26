cmake_minimum_required(VERSION 3.15)
project(Lab_10 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(tests)

add_executable(Lab_10_1_A PR_10.1_A/Lab_10_1_A.cpp)
add_executable(Lab_10_1_B PR_10.1_B/Lab_10_1_B.cpp)
add_executable(Lab_10_2_A PR_10.2_A/Lab_10_2_A.cpp)
add_executable(Lab_10_2_B PR_10.2_B/Lab_10_2_B.cpp)

enable_testing()

add_executable(UnitTest_10_1_A PR_10.1_A/UnitTest_10_1_A.cpp)
add_test(NAME Test_10_1_A COMMAND UnitTest_10_1_A)

add_executable(UnitTest_10_1_B PR_10.1_B/UnitTest_10_1_B.cpp)
add_test(NAME Test_10_1_B COMMAND UnitTest_10_1_B)

add_executable(UnitTest_10_2_A PR_10.2_A/UnitTest_10_2_A.cpp)
add_test(NAME Test_10_2_A COMMAND UnitTest_10_2_A)

add_executable(UnitTest_10_2_B PR_10.2_B/UnitTest_10_2_B.cpp)
add_test(NAME Test_10_2_B COMMAND UnitTest_10_2_B)
