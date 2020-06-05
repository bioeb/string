cmake_minimum_required(VERSION 3.10)

project(StringTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(stringTest
  stringTest.cpp
  BioebString.cpp
  BioebString.h
  )

target_include_directories(stringTest PRIVATE "${PROJECT_BINARY_DIR}")

enable_testing()

add_test(TokenTest1 stringTest)
